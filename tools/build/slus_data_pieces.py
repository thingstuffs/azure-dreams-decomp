#!/usr/bin/env python3
"""Conservatively split named global .sdata/.sbss symbols in ELF32 MIPS REL.

No instruction or relocation entry is rewritten.  Original section indices
and symbol indices are preserved; each selected symbol gets a new section and
value zero.  All unselected bytes in the emptied source section must be zero
alignment bytes with no symbol or relocation target.
"""

from __future__ import annotations

import hashlib
from pathlib import Path
import argparse
import json
import os
import tempfile
import re
import struct

ELF_HEADER = struct.Struct("<16sHHIIIIIHHHHHH")
SECTION = struct.Struct("<IIIIIIIIII")
SYMBOL = struct.Struct("<IIIBBH")
REL = struct.Struct("<II")
SHT_PROGBITS, SHT_SYMTAB, SHT_STRTAB, SHT_RELA, SHT_NOBITS, SHT_REL = 1, 2, 3, 4, 8, 9
STB_GLOBAL, STT_NOTYPE, STT_OBJECT, STT_FUNC, STT_SECTION = 1, 0, 1, 2, 3
EM_MIPS, ET_REL = 8, 1
SMALL_DATA_FLAGS = 0x10000003  # SHF_WRITE | SHF_ALLOC | SHF_MIPS_GPREL
MAX_NOBITS_BYTES = 16 * 1024 * 1024
NEW_NAME = re.compile(r"^\.(sdata|sbss)\.([A-Za-z_][A-Za-z0-9_]*)$")


def _sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def _align(value: int, alignment: int) -> int:
    return (value + alignment - 1) & ~(alignment - 1)


def _power2(value: int) -> bool:
    return value > 0 and value & (value - 1) == 0


def _cstring(table: bytes, offset: int, what: str) -> str:
    if offset >= len(table):
        raise ValueError(f"{what}: string-table offset out of range")
    end = table.find(b"\0", offset)
    if end < 0:
        raise ValueError(f"{what}: unterminated string")
    try:
        return table[offset:end].decode("ascii")
    except UnicodeDecodeError as exc:
        raise ValueError(f"{what}: non-ASCII name") from exc


def _parse(data: bytes) -> dict:
    if len(data) < ELF_HEADER.size:
        raise ValueError("truncated ELF header")
    h = ELF_HEADER.unpack_from(data)
    ident = h[0]
    if ident[:4] != b"\x7fELF" or ident[4:7] != b"\x01\x01\x01":
        raise ValueError("requires ELF32 little-endian version 1")
    if (h[1], h[2], h[3]) != (ET_REL, EM_MIPS, 1):
        raise ValueError("requires ET_REL EM_MIPS version 1")
    if h[4] != 0 or h[5] != 0 or h[9] != 0 or h[10] != 0:
        raise ValueError("program headers or nonzero ELF entry are unsupported")
    shoff, ehsize, shentsize, shnum, shstrndx = h[6], h[8], h[11], h[12], h[13]
    if (ehsize != ELF_HEADER.size or shentsize != SECTION.size or shnum == 0
            or shstrndx in (0, 0xFFFF) or shstrndx >= shnum
            or shoff < ehsize or shoff + shnum * shentsize > len(data)):
        raise ValueError("unsupported section header layout or extended indices")
    sections = [list(SECTION.unpack_from(data, shoff + i * shentsize)) for i in range(shnum)]
    if sections[0] != [0] * 10:
        raise ValueError("non-null section zero or extended section count unsupported")
    if any(s[1] == SHT_RELA for s in sections):
        raise ValueError("SHT_RELA relocations are unsupported")
    if any(s[1] == 18 for s in sections):
        raise ValueError("extended symbol section indices are unsupported")
    for i, s in enumerate(sections[1:], 1):
        if not _power2(s[8]):
            raise ValueError(f"section {i}: non-power-of-two alignment")
        if s[1] == SHT_NOBITS and s[5] > MAX_NOBITS_BYTES:
            raise ValueError(f"section {i}: NOBITS extent exceeds bounded splitter scope")
        if s[1] != SHT_NOBITS and s[4] + s[5] > len(data):
            raise ValueError(f"section {i}: payload out of range")
        if s[3] != 0:
            raise ValueError(f"section {i}: nonzero section address unsupported")
    shstr = sections[shstrndx]
    if shstr[1] != SHT_STRTAB or shstr[5] == 0:
        raise ValueError("section-name string table missing")
    shstr_bytes = data[shstr[4]:shstr[4] + shstr[5]]
    if shstr_bytes[-1] != 0:
        raise ValueError("section-name string table lacks terminal NUL")
    names = [_cstring(shstr_bytes, s[0], f"section {i}") for i, s in enumerate(sections)]
    if len(set(names[1:])) != shnum - 1:
        raise ValueError("duplicate existing section names")
    symtabs = [i for i, s in enumerate(sections) if s[1] == SHT_SYMTAB]
    if len(symtabs) != 1:
        raise ValueError("requires exactly one SHT_SYMTAB")
    sym_idx = symtabs[0]
    sym_sh = sections[sym_idx]
    if (sym_sh[9] != SYMBOL.size or sym_sh[5] % SYMBOL.size
            or sym_sh[6] >= shnum or sections[sym_sh[6]][1] != SHT_STRTAB):
        raise ValueError("unsupported symbol table layout")
    str_sh = sections[sym_sh[6]]
    strtab = data[str_sh[4]:str_sh[4] + str_sh[5]]
    symraw = data[sym_sh[4]:sym_sh[4] + sym_sh[5]]
    symbols = []
    for i in range(len(symraw) // SYMBOL.size):
        item = SYMBOL.unpack_from(symraw, i * SYMBOL.size)
        if item[5] == 0xFFFF or (item[5] >= 0xFF00 and item[5] not in (0xFFF1, 0xFFF2)):
            raise ValueError(f"symbol {i}: extended/reserved index unsupported")
        if 0 < item[5] < 0xFF00 and item[5] >= shnum:
            raise ValueError(f"symbol {i}: section index out of range")
        symbols.append({"index": i, "name": _cstring(strtab, item[0], f"symbol {i}"),
                        "value": item[1], "size": item[2], "bind": item[3] >> 4,
                        "type": item[3] & 15, "shndx": item[5]})
    return {"header": h, "sections": sections, "names": names, "symbols": symbols,
            "symtab_index": sym_idx, "shstr_index": shstrndx,
            "shstr_bytes": shstr_bytes, "symraw": symraw}


def _payload(data: bytes, sh: list[int]) -> bytes:
    if sh[1] == SHT_NOBITS:
        if sh[5] > MAX_NOBITS_BYTES:
            raise ValueError("NOBITS extent exceeds bounded splitter scope")
        return b"\0" * sh[5]
    return data[sh[4]:sh[4] + sh[5]]


def _rel_addend(data: bytes, target_sh: list[int], offset: int, rtype: int,
                entries: list[tuple[int, int]], position: int, sym_index: int) -> int:
    if target_sh[1] == SHT_NOBITS or offset + 4 > target_sh[5]:
        raise ValueError("relocation to selected symbol has no readable four-byte site")
    word = struct.unpack_from("<I", data, target_sh[4] + offset)[0]
    low = word & 0xFFFF
    signed = lambda x: x - 0x10000 if x & 0x8000 else x  # noqa: E731
    if rtype == 2:  # R_MIPS_32
        return word if word < 0x80000000 else word - 0x100000000
    if rtype == 4:  # R_MIPS_26
        return (word & 0x03FFFFFF) << 2
    if rtype in (6, 7):  # R_MIPS_LO16 / R_MIPS_GPREL16
        return signed(low)
    if rtype == 5:  # R_MIPS_HI16: pair with the next LO16 of this symbol
        for later_off, later_info in entries[position + 1:]:
            if later_info >> 8 == sym_index and later_info & 255 == 6:
                if later_off + 4 > target_sh[5]:
                    raise ValueError("HI16 pair has out-of-range LO16 site")
                lo_word = struct.unpack_from("<I", data, target_sh[4] + later_off)[0]
                addend = (low << 16) + signed(lo_word & 0xFFFF)
                return addend if addend < 0x80000000 else addend - 0x100000000
        raise ValueError("HI16 relocation to moved symbol has no LO16 pair")
    raise ValueError(f"unsupported relocation type {rtype} to moved symbol")


def split_elf(data: bytes, pieces: list[dict]) -> tuple[bytes, dict]:
    """Split explicit global data spans into new named sections.

    Each piece requires ``symbol``, positive ``size``, unique ``section``,
    ``source_section`` and explicit power-of-two ``alignment``.  The original section's alignment is
    an upper bound.  Relocations into a moved symbol must have a nonnegative
    implicit addend within that symbol's declared span.
    """
    if not isinstance(data, bytes) or not isinstance(pieces, list) or not pieces:
        raise ValueError("bytes input and at least one piece are required")
    parsed = _parse(data)
    sections, names, symbols = parsed["sections"], parsed["names"], parsed["symbols"]
    sym_by_name = {}
    for symbol in symbols:
        if symbol["name"]:
            sym_by_name.setdefault(symbol["name"], []).append(symbol)
    selected = {}
    destination_names = set()
    source_indices = set()
    for index, piece in enumerate(pieces):
        if not isinstance(piece, dict) or set(piece) != {"symbol", "size", "section", "alignment", "source_section"}:
            raise ValueError(f"piece {index}: require symbol,size,section,alignment,source_section only")
        symbol_name, size, new_name, alignment, source_name = (piece[k] for k in
                                                  ("symbol", "size", "section", "alignment", "source_section"))
        if not isinstance(symbol_name, str) or not symbol_name or symbol_name in selected:
            raise ValueError(f"piece {index}: empty or duplicate symbol")
        matches = sym_by_name.get(symbol_name, [])
        if len(matches) != 1:
            raise ValueError(f"piece {index}: symbol absent or ambiguous: {symbol_name}")
        symbol = matches[0]
        if (symbol["bind"] != STB_GLOBAL or symbol["type"] not in (STT_NOTYPE, STT_OBJECT)
                or not 0 < symbol["shndx"] < len(sections)):
            raise ValueError(f"piece {index}: requires a defined GLOBAL non-FUNC data symbol")
        source_index = symbol["shndx"]
        old_name = names[source_index]
        if source_name != old_name:
            raise ValueError(f"piece {index}: source_section differs from actual {old_name}")
        old = sections[source_index]
        if old_name not in (".sdata", ".sbss") or old[1] != (
                SHT_PROGBITS if old_name == ".sdata" else SHT_NOBITS):
            raise ValueError(f"piece {index}: source must be .sdata PROGBITS or .sbss NOBITS")
        if old[2] != SMALL_DATA_FLAGS:
            raise ValueError(f"piece {index}: unsupported source section flags {old[2]:#x}")
        if old[6] != 0 or old[7] != 0 or old[9] != 0:
            raise ValueError(f"piece {index}: unsupported source sh_link/sh_info/sh_entsize")
        if old[5] > 16 * 1024 * 1024:
            raise ValueError(f"piece {index}: source data extent exceeds bounded splitter scope")
        if not isinstance(new_name, str) or not NEW_NAME.fullmatch(new_name) or not new_name.startswith(old_name + "."):
            raise ValueError(f"piece {index}: destination must be a matching named small-data section")
        if new_name in names or new_name in destination_names:
            raise ValueError(f"piece {index}: destination section collision: {new_name}")
        if (not isinstance(size, int) or isinstance(size, bool) or size <= 0
                or not isinstance(alignment, int) or isinstance(alignment, bool)
                or not _power2(alignment) or alignment > old[8]):
            raise ValueError(f"piece {index}: positive size and bounded power-of-two alignment required")
        start = symbol["value"]
        if (start % alignment or start + size > old[5]
                or symbol["size"] not in (0, size)):
            raise ValueError(f"piece {index}: span, alignment, or recorded symbol size differs")
        selected[symbol_name] = {"symbol": symbol, "source_index": source_index,
                                 "start": start, "size": size, "section": new_name,
                                 "alignment": alignment, "piece_index": index}
        destination_names.add(new_name)
        source_indices.add(source_index)
    if len(sections) + len(pieces) >= 0xFF00:
        raise ValueError("new section indices require unsupported extended encoding")

    gaps = {}
    for source_index in sorted(source_indices):
        source_name = names[source_index]
        old = sections[source_index]
        own = sorted((item for item in selected.values() if item["source_index"] == source_index),
                     key=lambda item: item["start"])
        defined = [sym for sym in symbols if sym["shndx"] == source_index and sym["type"] != STT_SECTION]
        if {sym["name"] for sym in defined} != {item["symbol"]["name"] for item in own} or len(defined) != len(own):
            raise ValueError(f"{source_name}: unselected or unnamed non-section defined symbol")
        if any(sym["type"] == STT_SECTION and sym["value"] != 0
               for sym in symbols if sym["shndx"] == source_index):
            raise ValueError(f"{source_name}: nonzero section-symbol base unsupported")
        content = _payload(data, old)
        cursor = 0
        ranges = []
        for item in own:
            if item["start"] < cursor:
                raise ValueError(f"{source_name}: selected spans overlap")
            if item["start"] > cursor:
                if any(content[cursor:item["start"]]):
                    raise ValueError(f"{source_name}: nonzero unselected alignment bytes")
                ranges.append({"start": cursor, "end": item["start"]})
            cursor = item["start"] + item["size"]
        if cursor < old[5]:
            if any(content[cursor:old[5]]):
                raise ValueError(f"{source_name}: nonzero trailing alignment bytes")
            ranges.append({"start": cursor, "end": old[5]})
        gaps[source_name] = {"old_section_index": source_index, "old_size": old[5],
                             "kind": "NOBITS" if old[1] == SHT_NOBITS else "PROGBITS",
                             "discarded_alignment_ranges": ranges,
                             "discarded_alignment_bytes": sum(r["end"]-r["start"] for r in ranges),
                             "all_discarded_bytes_zero": True}

    relocation_count = 0
    selected_relocations = []
    for rel_index, sh in enumerate(sections):
        if sh[1] != SHT_REL:
            continue
        if (sh[9] != REL.size or sh[5] % REL.size or sh[6] != parsed["symtab_index"]
                or sh[7] >= len(sections)):
            raise ValueError(f"relocation section {rel_index}: unsupported layout")
        raw = _payload(data, sh)
        entries = [REL.unpack_from(raw, offset) for offset in range(0, len(raw), REL.size)]
        if sh[7] in source_indices and entries:
            raise ValueError(f"relocation section {rel_index}: relocation originates in moved data")
        for position, (r_offset, r_info) in enumerate(entries):
            relocation_count += 1
            sym_index = r_info >> 8
            if sym_index >= len(symbols):
                raise ValueError(f"relocation section {rel_index}: bad symbol index")
            symbol = symbols[sym_index]
            if symbol["shndx"] not in source_indices:
                continue
            item = selected.get(symbol["name"])
            if (item is None or item["symbol"]["index"] != sym_index
                    or symbol["bind"] != STB_GLOBAL or symbol["type"] not in (STT_NOTYPE, STT_OBJECT)):
                raise ValueError(f"relocation section {rel_index}: relocation targets old section/local base")
            addend = _rel_addend(data, sections[sh[7]], r_offset, r_info & 255,
                                 entries, position, sym_index)
            if not 0 <= addend < item["size"]:
                raise ValueError(f"relocation section {rel_index}: addend enters discarded alignment or another symbol")
            selected_relocations.append({"relocation_section": names[rel_index],
                                         "offset": r_offset, "symbol": symbol["name"],
                                         "type": r_info & 255, "addend": addend})

    new_shstr = bytearray(parsed["shstr_bytes"])
    new_names = {}
    new_sections = []
    moved = []
    for piece in pieces:
        item = selected[piece["symbol"]]
        old = sections[item["source_index"]]
        new_index = len(sections) + len(new_sections)
        new_names[item["section"]] = len(new_shstr)
        new_shstr.extend(item["section"].encode("ascii") + b"\0")
        content = _payload(data, old)[item["start"]:item["start"] + item["size"]]
        new_sections.append([new_names[item["section"]], old[1], old[2], 0, 0,
                             item["size"], 0, 0, item["alignment"], 0])
        item["new_index"] = new_index
        item["content"] = content
        moved.append({"symbol": piece["symbol"], "old_section": names[item["source_index"]],
                      "old_section_index": item["source_index"], "old_offset": item["start"],
                      "size": item["size"], "alignment": item["alignment"],
                      "new_section": item["section"], "new_section_index": new_index,
                      "content_sha256": _sha(content), "content_hex": content.hex(),
                      "old_symbol_size": item["symbol"]["size"]})

    symraw = bytearray(parsed["symraw"])
    for item in selected.values():
        offset = item["symbol"]["index"] * SYMBOL.size
        struct.pack_into("<I", symraw, offset + 4, 0)
        struct.pack_into("<H", symraw, offset + 14, item["new_index"])
    all_sections = [list(s) for s in sections] + new_sections
    payloads = []
    for i, sh in enumerate(sections):
        if i in source_indices:
            all_sections[i][5] = 0
            payloads.append(b"")
        elif i == parsed["shstr_index"]:
            all_sections[i][5] = len(new_shstr)
            payloads.append(bytes(new_shstr))
        elif i == parsed["symtab_index"]:
            payloads.append(bytes(symraw))
        else:
            payloads.append(_payload(data, sh) if sh[1] != SHT_NOBITS else b"")
    payloads.extend(item["content"] if sections[item["source_index"]][1] != SHT_NOBITS else b""
                    for piece in pieces for item in [selected[piece["symbol"]]])
    output = bytearray(data[:ELF_HEADER.size])
    for i, sh in enumerate(all_sections):
        if i == 0:
            continue
        aligned = _align(len(output), sh[8])
        output.extend(b"\0" * (aligned - len(output)))
        sh[4] = len(output)
        if sh[1] != SHT_NOBITS:
            if len(payloads[i]) != sh[5]:
                raise AssertionError("internal section payload length mismatch")
            output.extend(payloads[i])
    shoff = _align(len(output), 4)
    output.extend(b"\0" * (shoff - len(output)))
    for sh in all_sections:
        output.extend(SECTION.pack(*sh))
    struct.pack_into("<I", output, 0x20, shoff)
    struct.pack_into("<H", output, 0x30, len(all_sections))
    result = bytes(output)

    # Independent parse and byte preservation checks on the emitted object.
    check = _parse(result)
    if check["names"][:len(names)] != names or check["names"][len(names):] != [p["section"] for p in pieces]:
        raise AssertionError("original section indices or appended section names changed")
    for i, old in enumerate(sections):
        if i in source_indices:
            if check["sections"][i][5] != 0:
                raise AssertionError("old moved section was not emptied")
        elif i not in (parsed["shstr_index"], parsed["symtab_index"]):
            if _payload(data, old) != _payload(result, check["sections"][i]):
                raise AssertionError(f"original section {i} payload changed")
    for i, old in enumerate(sections):
        if old[1] == SHT_REL and _payload(data, old) != _payload(result, check["sections"][i]):
            raise AssertionError("relocation entry payload changed")
    if len(check["symbols"]) != len(symbols):
        raise AssertionError("symbol order/count changed")
    for before, after in zip(symbols, check["symbols"]):
        if before["index"] in {x["symbol"]["index"] for x in selected.values()}:
            item = selected[before["name"]]
            if {k: after[k] for k in ("name", "size", "bind", "type")} != {
                    k: before[k] for k in ("name", "size", "bind", "type")} or (
                    after["value"], after["shndx"]) != (0, item["new_index"]):
                raise AssertionError("selected symbol mutation exceeded shndx/value")
        elif before != after:
            raise AssertionError("unselected symbol changed")
    receipt = {"schema": 1, "input_sha256": _sha(data), "output_sha256": _sha(result),
               "original_section_count": len(sections), "new_section_count": len(all_sections),
               "original_symbol_count": len(symbols), "relocation_entries": relocation_count,
               "selected_relocations": selected_relocations,
               "relocation_entries_unchanged": True, "original_nondata_payloads_unchanged": True,
               "symbol_indices_and_order_unchanged": True,
               "moved": moved, "emptied_source_sections": gaps,
               "text_section_sha256": {name: _sha(_payload(data, sections[i])) for i, name in enumerate(names)
                                        if name.startswith(".text")},
               "boundaries": {"program_headers": 0, "symtabs": 1, "rela": 0,
                              "extended_indices": False}}
    return result, receipt


def _module_plan(module: dict) -> list[dict]:
    from slus_modules import data_piece_plan

    if not isinstance(module, dict) or not isinstance(module.get("name"), str):
        raise ValueError("module must be a validated manifest record with a name")
    plan = data_piece_plan(module)
    if not isinstance(plan, list):
        raise ValueError("data_piece_plan must return a list")
    return plan


def _paths(path: Path) -> tuple[Path, Path, Path]:
    path = Path(os.path.abspath(path))
    raw = path.with_suffix(".unsplit.o")
    receipt = path.with_suffix(".data-pieces.json")
    if len({path, raw, receipt}) != 3:
        raise ValueError("object and sidecar paths collide")
    _reject_symlink_ancestors(path.parent)
    for output in (path, raw, receipt):
        if output.is_symlink():
            raise ValueError(f"symlink object or sidecar refused: {output}")
    return path, raw, receipt


def _reject_symlink_ancestors(path: Path) -> None:
    for component in (path, *path.parents):
        if component.is_symlink():
            raise ValueError(f"symlink output parent refused: {component}")


def _read_regular(path: Path) -> bytes:
    if path.is_symlink() or not path.is_file():
        raise ValueError(f"missing or non-regular object/sidecar: {path}")
    return path.read_bytes()


def _core_hash() -> str:
    return _sha(Path(__file__).read_bytes())


def _expected_receipt(module: dict, plan: list[dict], original: bytes) -> tuple[bytes, dict]:
    transformed, proof = split_elf(original, plan)
    receipt = {
        "schema": 1,
        "module": module["name"],
        "plan": plan,
        "core_sha256": _core_hash(),
        "pre_object_sha256": _sha(original),
        "post_object_sha256": _sha(transformed),
        "split_elf": proof,
    }
    return transformed, receipt


def _stage_bytes(path: Path, data: bytes, mode: int) -> Path:
    """Stage complete bytes beside an output, preserving its file mode."""
    fd, name = tempfile.mkstemp(prefix=f".{path.name}.", suffix=".tmp", dir=path.parent)
    staged = Path(name)
    try:
        with os.fdopen(fd, "wb") as stream:
            stream.write(data)
            stream.flush()
            os.fsync(stream.fileno())
        os.chmod(staged, mode)
        return staged
    except BaseException:
        staged.unlink(missing_ok=True)
        raise


def apply_data_pieces(path: Path, module: dict) -> dict | None:
    """Split a newly compiled raw object, retaining it and an exact receipt.

    A module with no data-piece plan leaves the object and sidecars untouched.
    A normal recompile may leave sidecars from the prior epoch; those generated
    files are replaced only after the new raw object passes full validation.
    Validation and all temporary writes finish before publication.
    """
    plan = _module_plan(module)
    if not plan:
        return None
    path, raw_path, receipt_path = _paths(path)
    original = _read_regular(path)
    for sidecar in (raw_path, receipt_path):
        if sidecar.exists() and not sidecar.is_file():
            raise ValueError(f"non-regular data-piece sidecar refused: {sidecar}")
    # This also refuses applying twice to a previously split object, even if
    # the old sidecars were removed or altered.
    transformed, receipt = _expected_receipt(module, plan, original)
    encoded = (json.dumps(receipt, sort_keys=True, indent=2) + "\n").encode("utf-8")
    mode = path.stat().st_mode & 0o777
    staged: list[Path] = []
    try:
        for target, content, output_mode in (
                (raw_path, original, mode), (path, transformed, mode),
                (receipt_path, encoded, 0o644)):
            staged.append(_stage_bytes(target, content, output_mode))
        for output in (path, raw_path, receipt_path):
            if output.is_symlink():
                raise ValueError(f"symlink data-piece output appeared during staging: {output}")
        # Each generated artifact is replaced atomically.  Publishing the
        # final object last makes an interrupted epoch fail verification.
        os.replace(staged[0], raw_path)
        os.replace(staged[2], receipt_path)
        os.replace(staged[1], path)
    finally:
        for temp in staged:
            temp.unlink(missing_ok=True)
    return receipt


def verify_data_pieces(path: Path, module: dict) -> dict | None:
    """Recompute the split from the retained original and compare every byte."""
    plan = _module_plan(module)
    if not plan:
        path, raw_path, receipt_path = _paths(path)
        _read_regular(path)
        if raw_path.exists() or receipt_path.exists():
            raise ValueError("unplanned module has data-piece sidecars")
        return None
    path, raw_path, receipt_path = _paths(path)
    actual = _read_regular(path)
    original = _read_regular(raw_path)
    receipt_bytes = _read_regular(receipt_path)
    try:
        recorded = json.loads(receipt_bytes)
    except (UnicodeDecodeError, json.JSONDecodeError) as exc:
        raise ValueError("invalid data-piece receipt JSON") from exc
    expected_object, expected_receipt = _expected_receipt(module, plan, original)
    if actual != expected_object:
        raise ValueError("data-piece object differs from recomputed split")
    if recorded != expected_receipt:
        raise ValueError("data-piece receipt differs from recomputed proof")
    if receipt_bytes != (json.dumps(expected_receipt, sort_keys=True, indent=2) + "\n").encode("utf-8"):
        raise ValueError("data-piece receipt bytes differ from canonical encoding")
    return expected_receipt


def _write_stamp(path: Path, receipt: dict | None, object_path: Path) -> None:
    """Publish a verification stamp only after the object has been rechecked."""
    path = Path(os.path.abspath(path))
    if path.is_symlink():
        raise ValueError("symlink stamp refused")
    _reject_symlink_ancestors(path.parent)
    path.parent.mkdir(parents=True, exist_ok=True)
    _reject_symlink_ancestors(path.parent)
    object_hash = _sha(_read_regular(Path(object_path)))
    if receipt is not None and object_hash != receipt["post_object_sha256"]:
        raise ValueError("object changed after verification")
    data = (json.dumps({"schema": 1, "verified": True,
                        "module": None if receipt is None else receipt["module"],
                        "post_object_sha256": object_hash},
                       sort_keys=True) + "\n").encode("utf-8")
    staged = _stage_bytes(path, data, 0o644)
    try:
        os.replace(staged, path)
    finally:
        staged.unlink(missing_ok=True)


def main(argv: list[str] | None = None) -> int:
    from slus_modules import load_manifest

    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--manifest", required=True, type=Path)
    parser.add_argument("--module", required=True)
    parser.add_argument("--object", required=True, type=Path)
    parser.add_argument("--verify", action="store_true")
    parser.add_argument("--stamp", type=Path)
    args = parser.parse_args(argv)
    modules = load_manifest(args.manifest)
    matches = [item for item in modules if item["name"] == args.module]
    if len(matches) != 1:
        raise ValueError(f"manifest module absent or ambiguous: {args.module}")
    if args.stamp is not None and not args.verify:
        raise ValueError("--stamp requires --verify")
    receipt = (verify_data_pieces if args.verify else apply_data_pieces)(args.object, matches[0])
    if args.stamp is not None:
        _write_stamp(args.stamp, receipt, args.object)
    print(json.dumps({"module": args.module, "applied": receipt is not None,
                      "verified": args.verify, "post_object_sha256":
                      None if receipt is None else receipt["post_object_sha256"]}, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
