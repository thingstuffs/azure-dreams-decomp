#!/usr/bin/env python3
"""Conservative, build-root-relative support for grouped SLUS C modules.

This module does not register modules or modify splat products. A caller supplies
the optional manifest and wires the returned physical inputs into its build.
All paths in a manifest and all generated paths are relative to the passed root
(the current working directory by default, normally a SLUS build root).
"""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import subprocess
from pathlib import Path, PurePosixPath


_PATH = re.compile(r"[A-Za-z0-9_./-]+\Z")
_IDENT = re.compile(r"[A-Za-z_][A-Za-z0-9_]*\Z")
_NAME = re.compile(r"[A-Za-z0-9_-]+\Z")
_FLAGS = re.compile(r"[-A-Za-z0-9_./=+ ]*\Z")
EDGE_KEYS = ("src", "out", "ccver", "ccflags", "asflags")


class ModuleError(ValueError):
    """Unsafe, ambiguous, or unsupported module plan."""


def _keys(value, required, where):
    if not isinstance(value, dict) or set(value) != set(required):
        raise ModuleError(f"{where}: expected keys {sorted(required)}")


def _path(value, where, prefix=None, suffix=None):
    if not isinstance(value, str) or not _PATH.fullmatch(value):
        raise ModuleError(f"{where}: unsafe path {value!r}")
    p = PurePosixPath(value)
    if str(p) != value or p.is_absolute() or any(x in (".", "..") for x in p.parts):
        raise ModuleError(f"{where}: unsafe path {value!r}")
    if prefix and (not p.parts or p.parts[0] != prefix):
        raise ModuleError(f"{where}: expected a {prefix}/ path")
    if suffix and p.suffix != suffix:
        raise ModuleError(f"{where}: expected {suffix} suffix")
    return value


def _ident(value, where):
    if not isinstance(value, str) or not _IDENT.fullmatch(value):
        raise ModuleError(f"{where}: invalid identifier {value!r}")
    return value


def _recipe(value, where):
    _keys(value, ("ccver", "ccflags", "asflags"), where)
    if not isinstance(value["ccver"], str) or not re.fullmatch(r"[A-Za-z0-9_.-]+", value["ccver"]):
        raise ModuleError(f"{where}: invalid ccver")
    for key in ("ccflags", "asflags"):
        if not isinstance(value[key], str) or not _FLAGS.fullmatch(value[key]):
            raise ModuleError(f"{where}: unsafe {key}")
    return dict(value)


def _data_record(datum, where):
    _keys(datum, ("symbol", "asset", "offset", "size", "vram", "bytes", "section"), where)
    _ident(datum["symbol"], where + ".symbol")
    asset = _path(datum["asset"], where + ".asset", "assets", ".bin")
    if len(PurePosixPath(asset).parts) != 2:
        raise ModuleError(f"{where}: only flat assets/*.bin are supported")
    if not re.fullmatch(r"[0-9A-Fa-f]+", PurePosixPath(asset).stem):
        raise ModuleError(f"{where}: asset stem must be its hexadecimal ROM offset")
    offset, size, vram = (datum[k] for k in ("offset", "size", "vram"))
    if any(type(x) is not int for x in (offset, size, vram)) or offset < 0 or size <= 0 or not 0 <= vram <= 0xFFFFFFFF:
        raise ModuleError(f"{where}: invalid offset, size, or vram")
    raw = datum["bytes"]
    if not isinstance(raw, str) or not re.fullmatch(r"[0-9A-Fa-f]+", raw) or len(raw) != 2 * size:
        raise ModuleError(f"{where}: bytes must encode exactly size bytes")
    section = datum["section"]
    if not isinstance(section, str) or not re.fullmatch(r"\.(?:sdata|sbss)(?:\.[A-Za-z_][A-Za-z0-9_]*)?", section):
        raise ModuleError(f"{where}: unsupported data section {section!r}")
    if section.startswith(".sbss") and any(bytes.fromhex(raw)):
        raise ModuleError(f"{where}: .sbss storage must be zero")
    return dict(datum, bytes=raw.lower())


def data_piece_plan(module) -> list[dict]:
    """Validate an opt-in named-section plan and return exact physical pieces."""
    if not isinstance(module, dict):
        raise ModuleError("module: expected an object")
    if "data_pieces" not in module:
        return []
    allowed = {"name", "source", "members", "headers", "recipe", "data", "evidence", "data_pieces"}
    if set(module) - allowed:
        raise ModuleError(f"module: unexpected keys {sorted(set(module) - allowed)}")
    name = module.get("name")
    if not isinstance(name, str) or not _NAME.fullmatch(name):
        raise ModuleError("module: invalid name")
    pieces, data = module["data_pieces"], module.get("data")
    if not isinstance(pieces, list) or not pieces:
        raise ModuleError(f"{name}: data_pieces must be a nonempty list")
    if not isinstance(data, list):
        raise ModuleError(f"{name}: data must be a list")
    by_symbol = {}
    for i, raw in enumerate(data):
        datum = _data_record(raw, f"{name}.data[{i}]")
        symbol = datum["symbol"]
        if symbol in by_symbol:
            raise ModuleError(f"{name}: duplicate data symbol {symbol}")
        by_symbol[symbol] = datum
    plan, seen = [], set()
    for i, piece in enumerate(pieces):
        where = f"{name}.data_pieces[{i}]"
        _keys(piece, ("symbol", "source_section", "alignment"), where)
        symbol = _ident(piece["symbol"], where + ".symbol")
        if symbol in seen:
            raise ModuleError(f"{where}: duplicate piece {symbol}")
        seen.add(symbol)
        if symbol not in by_symbol:
            raise ModuleError(f"{where}: no data record for {symbol}")
        source_section = piece["source_section"]
        if source_section not in (".sdata", ".sbss"):
            raise ModuleError(f"{where}: unsupported source_section {source_section!r}")
        alignment = piece["alignment"]
        if type(alignment) is not int or not 1 <= alignment <= 0x1000 or alignment & (alignment - 1):
            raise ModuleError(f"{where}: alignment must be a power of two from 1 to 0x1000")
        datum = by_symbol[symbol]
        section = source_section + "." + symbol
        if datum["section"] != section:
            raise ModuleError(f"{where}: {symbol} destination section must be {section}")
        if datum["vram"] % alignment:
            raise ModuleError(f"{where}: {symbol} VMA is not aligned to {alignment}")
        plan.append({"symbol": symbol, "size": datum["size"], "section": section,
                     "alignment": alignment, "source_section": source_section})
    missing = set(by_symbol) - seen
    if missing:
        raise ModuleError(f"{name}: missing data piece(s) for {sorted(missing)}")
    return plan


def load_manifest(path) -> list[dict]:
    """Load and validate a version-1 manifest; a missing path means no modules."""
    path = Path(path)
    if not path.exists():
        return []
    doc = json.loads(path.read_text())
    _keys(doc, ("version", "modules"), "manifest")
    if type(doc["version"]) is not int or doc["version"] != 1 or not isinstance(doc["modules"], list):
        raise ModuleError("manifest: expected version 1 and a modules list")
    seen_names, seen_sources, seen_object_stems, seen_rows, seen_functions, seen_symbols = (set() for _ in range(6))
    modules = []
    for i, module in enumerate(doc["modules"]):
        where = f"modules[{i}]"
        module_keys = ("name", "source", "members", "headers", "recipe", "data", "evidence")
        _keys(module, module_keys + (("data_pieces",) if "data_pieces" in module else ()), where)
        name = module["name"]
        if not isinstance(name, str) or not _NAME.fullmatch(name) or name in seen_names:
            raise ModuleError(f"{where}: invalid or duplicate name {name!r}")
        seen_names.add(name)
        source = _path(module["source"], where + ".source", "src", ".c")
        if source in seen_sources:
            raise ModuleError(f"{where}: duplicate source {source}")
        seen_sources.add(source)
        source_stem = PurePosixPath(source).stem
        if source_stem in seen_object_stems:
            raise ModuleError(f"{where}: duplicate generated object stem {source_stem}")
        seen_object_stems.add(source_stem)
        recipe = _recipe(module["recipe"], where + ".recipe")
        headers = module["headers"]
        if not isinstance(headers, list) or len(headers) != len(set(map(str, headers))):
            raise ModuleError(f"{where}: headers must be a unique list")
        headers = [_path(p, where + ".headers", "include", ".h") for p in headers]
        evidence = _path(module["evidence"], where + ".evidence", "docs", ".md")
        if not evidence.startswith("docs/evidence/"):
            raise ModuleError(f"{where}: evidence must be under docs/evidence/")
        if not isinstance(module["members"], list) or not module["members"]:
            raise ModuleError(f"{where}: members must be nonempty")
        members = []
        for j, member in enumerate(module["members"]):
            mw = f"{where}.members[{j}]"
            _keys(member, ("id", "source", "functions"), mw)
            row_id = member["id"]
            if not isinstance(row_id, str) or not re.fullmatch(r"slus/[A-Za-z0-9_]+", row_id) or row_id in seen_rows:
                raise ModuleError(f"{mw}: invalid or duplicate row id {row_id!r}")
            seen_rows.add(row_id)
            member_source = _path(member["source"], mw + ".source", "src", ".c")
            member_stem = PurePosixPath(member_source).stem
            if row_id != f"slus/{member_stem}":
                raise ModuleError(f"{mw}: row id must match source stem")
            if member_source in seen_sources or member_source == source:
                raise ModuleError(f"{mw}: duplicate source {member_source}")
            seen_sources.add(member_source)
            if member_stem in seen_object_stems:
                raise ModuleError(f"{mw}: duplicate generated object stem {member_stem}")
            seen_object_stems.add(member_stem)
            funcs = member["functions"]
            if not isinstance(funcs, list) or not funcs:
                raise ModuleError(f"{mw}: functions must be nonempty")
            for f in funcs:
                _ident(f, mw + ".functions")
                if f in seen_functions:
                    raise ModuleError(f"{mw}: duplicate function {f}")
                seen_functions.add(f)
            members.append({"id": row_id, "source": member_source, "functions": list(funcs)})
        data = module["data"]
        if not isinstance(data, list):
            raise ModuleError(f"{where}: data must be a list")
        parsed_data = []
        for j, datum in enumerate(data):
            dw = f"{where}.data[{j}]"
            parsed = _data_record(datum, dw)
            symbol = parsed["symbol"]
            if symbol in seen_symbols:
                raise ModuleError(f"{dw}: duplicate symbol {symbol}")
            seen_symbols.add(symbol)
            parsed_data.append(parsed)
        parsed_module = {"name": name, "source": source, "members": members, "headers": headers,
                         "recipe": recipe, "data": parsed_data, "evidence": evidence}
        if "data_pieces" in module:
            parsed_module["data_pieces"] = [dict(piece) if isinstance(piece, dict) else piece
                                            for piece in module["data_pieces"]] if isinstance(module["data_pieces"], list) else module["data_pieces"]
        data_sections(parsed_module)
        modules.append(parsed_module)
    return modules


def module_for_row(modules, row_id):
    """Return the owning module, or None for an ordinary logical row."""
    return next((m for m in modules for member in m["members"] if member["id"] == row_id), None)


def logical_edges(physical_edges, modules) -> list[dict]:
    """Expand module C edges back to the original five-field per-row edge records."""
    by_source = {m["source"]: m for m in modules}
    out, seen = [], set()
    for edge in physical_edges:
        if not isinstance(edge, dict) or any(k not in edge for k in EDGE_KEYS):
            raise ModuleError("physical edge must contain src/out/ccver/ccflags/asflags")
        src = _path(edge["src"], "edge.src", "src", ".c")
        target = _path(edge["out"], "edge.out", suffix=".o")
        if src in seen:
            raise ModuleError(f"duplicate physical edge {src}")
        seen.add(src)
        base = {k: edge[k] for k in EDGE_KEYS}
        module = by_source.get(src)
        if not module:
            out.append(base)
            continue
        if {k: edge[k] for k in ("ccver", "ccflags", "asflags")} != module["recipe"]:
            raise ModuleError(f"{src}: physical recipe differs from module manifest")
        if PurePosixPath(target).stem != PurePosixPath(src).stem:
            raise ModuleError(f"{src}: output name does not match module source")
        for member in module["members"]:
            out.append(dict(src=member["source"],
                            out=str(PurePosixPath(target).with_name(PurePosixPath(member["source"]).stem + ".o")),
                            ccver=edge["ccver"], ccflags=edge["ccflags"], asflags=edge["asflags"]))
    missing = set(by_source) - seen
    if missing:
        raise ModuleError(f"missing physical module edge(s): {sorted(missing)}")
    sources = [e["src"] for e in out]
    if len(sources) != len(set(sources)):
        raise ModuleError("physical edges overlap logical member sources")
    return sorted(out, key=lambda e: e["src"])


def _out_dir(out_dir):
    text = _path(str(out_dir), "out_dir")
    p = PurePosixPath(text)
    if len(p.parts) < 2:
        raise ModuleError("out_dir must lie under a build directory (e.g. build/module_assets)")
    return p


def _prepare_output(root, relative):
    """Create an output parent only when existing path components remain in root."""
    dest = root / relative
    if not dest.parent.resolve().is_relative_to(root):
        raise ModuleError(f"output escapes root: {dest}")
    dest.parent.mkdir(parents=True, exist_ok=True)
    if not dest.parent.resolve().is_relative_to(root):
        raise ModuleError(f"output escapes root: {dest}")
    if dest.is_symlink():
        dest.unlink()
    return dest


def data_sections(module) -> dict[str, list[dict]]:
    """Group records by real input section; each section has one ordered span."""
    if not isinstance(module, dict) or not isinstance(module.get("name"), str) or not isinstance(module.get("data"), list):
        raise ModuleError("module: expected name and data list")
    pieces = data_piece_plan(module)
    named = {piece["section"] for piece in pieces}
    sections, seen_symbols = {}, set()
    for i, raw in enumerate(module["data"]):
        datum = _data_record(raw, f"{module['name']}.data[{i}]")
        if datum["symbol"] in seen_symbols:
            raise ModuleError(f"{module['name']}: duplicate data symbol {datum['symbol']}")
        seen_symbols.add(datum["symbol"])
        section = datum["section"]
        if section not in ((".sdata", ".sbss") if not pieces else named):
            raise ModuleError(f"{module['name']}: unsupported data section {section!r}")
        sections.setdefault(section, []).append(raw)
    for section, records in sections.items():
        if len({d["asset"] for d in records}) != 1:
            raise ModuleError(f"{module['name']}: one {section} section cannot span multiple assets")
        if any(a["offset"] + a["size"] != b["offset"] or a["vram"] + a["size"] != b["vram"]
               for a, b in zip(records, records[1:])):
            raise ModuleError(f"{module['name']}: multiple {section} definitions must be contiguous and ordered")
    return sections


def _unique_owned_data(modules):
    """Validate direct callers' module data and reject cross-module ownership."""
    seen = set()
    result = []
    for module in modules:
        sections = data_sections(module)
        for records in sections.values():
            for datum in records:
                symbol = datum["symbol"]
                if symbol in seen:
                    raise ModuleError(f"duplicate data ownership of {symbol}")
                seen.add(symbol)
        result.append((module, sections))
    return result


def plan_asset_carves(modules, root=Path.cwd(), out_dir="build/module_assets") -> list[dict]:
    """Read assets, validate bytes and layout, and return deterministic ordered slots.

    Chunks describe inputs and objects; this function does not write either one.
    """
    root, out = Path(root), _out_dir(out_dir)
    build_dir = out.parts[0]
    exe = root / "baserom/slus_006.14"
    load_address = None
    if exe.is_file():
        with exe.open("rb") as f:
            head = f.read(0x20)
        if len(head) < 0x20 or head[:8] != b"PS-X EXE":
            raise ModuleError("baserom/slus_006.14: invalid PS-X EXE header")
        load_address = int.from_bytes(head[0x18:0x1C], "little")
    grouped = {}
    for module, sections in _unique_owned_data(modules):
        for records in sections.values():
            grouped.setdefault(records[0]["asset"], []).append((module, records))
    plans = []
    for asset in sorted(grouped):
        asset_path = root / asset
        raw = asset_path.read_bytes()
        groups = sorted(grouped[asset], key=lambda pair: pair[1][0]["offset"])
        prev = 0
        slots = []
        stem = PurePosixPath(asset).stem

        def chunk(start, end):
            if start == end:
                return
            label = f"{stem}_{start:06X}_{end:06X}"
            slots.append({"kind": "chunk", "start": start, "end": end,
                          "input": str(out / (label + ".bin")),
                          "object": str(out / (label + ".o")), "section": ".data"})

        for module, records in groups:
            start = records[0]["offset"]
            end = records[-1]["offset"] + records[-1]["size"]
            if start < prev:
                raise ModuleError(f"{asset}: overlapping definitions at offset {start}")
            if end > len(raw):
                raise ModuleError(f"{asset}: definition exceeds {len(raw)}-byte asset")
            for d in records:
                got = raw[d["offset"]:d["offset"] + d["size"]]
                if got != bytes.fromhex(d["bytes"]):
                    raise ModuleError(f"{d['symbol']}: initializer bytes differ from {asset} at {d['offset']}")
                if load_address is not None:
                    expected = load_address + int(stem, 16) + d["offset"] - 0x800
                    if d["vram"] != expected:
                        raise ModuleError(f"{d['symbol']}: VMA {d['vram']:#x} differs from EXE mapping {expected:#x}")
            chunk(prev, start)
            slots.append({"kind": "module_data", "start": start, "end": end,
                          "module": module["name"],
                          "object": str(PurePosixPath(build_dir) / PurePosixPath(module["source"]).with_suffix(".o")),
                          "section": records[0]["section"], "symbols": [d["symbol"] for d in records]})
            prev = end
        chunk(prev, len(raw))
        plans.append({"asset": asset, "asset_object": str(PurePosixPath(build_dir) / PurePosixPath(asset).with_suffix(".o")),
                      "asset_size": len(raw), "asset_sha256": hashlib.sha256(raw).hexdigest(), "slots": slots})
    return plans


def materialize_asset_chunks(plans, root=Path.cwd(), assemble=False) -> list[dict]:
    """Write planned chunk binaries; optionally run the stock binary-object command."""
    root = Path(root).resolve()
    made = []
    for plan in plans:
        raw = (root / plan["asset"]).read_bytes()
        if len(raw) != plan["asset_size"] or hashlib.sha256(raw).hexdigest() != plan["asset_sha256"]:
            raise ModuleError(f"{plan['asset']}: asset changed since planning")
        for slot in plan["slots"]:
            if slot["kind"] != "chunk":
                continue
            dest = _prepare_output(root, slot["input"])
            dest.write_bytes(raw[slot["start"]:slot["end"]])
            if assemble:
                object_path = _prepare_output(root, slot["object"])
                subprocess.run(("mipsel-linux-gnu-ld", "--relocatable", "--format=binary",
                                "-o", str(object_path), str(dest)), check=True)
            made.append(slot)
    return made


def rewrite_ordered_linker_script(text: str, plans) -> str:
    """Replace each exact raw-asset .data slot with planned chunk/data slots."""
    for plan in plans:
        old = plan["asset_object"] + "(.data);"
        slot = re.compile(r"(?m)^(?P<indent>[ \t]*)" + re.escape(old) + r"[ \t]*$")
        matches = list(slot.finditer(text))
        if len(matches) != 1:
            raise ModuleError(f"linker script needs one unambiguous slot for {old}")
        for item in plan["slots"]:
            if item["kind"] == "module_data":
                rendered = item["object"] + f"({item['section']});"
                if rendered in text:
                    raise ModuleError(f"linker script already contains module data slot {rendered}")
        # The original asset was one input section. Carving it creates new
        # boundaries, which must not acquire padding from an output SUBALIGN.
        # Retain the original directive for word-aligned carves; relax only the
        # containing output section when a new boundary violates that directive.
        headers = list(re.finditer(
            r"(?m)^[ \t]*\.[^{}\n]*\bSUBALIGN\(\s*(?P<alignment>[0-9]+)\s*\)[^{}\n]*\n[ \t]*\{",
            text[:matches[0].start()]))
        if headers:
            header = headers[-1]
            if "}" not in text[header.end():matches[0].start()]:
                alignment = int(header.group("alignment"))
                boundaries = [s["start"] for s in plan["slots"]][1:]
                if alignment > 1 and any(offset % alignment for offset in boundaries):
                    a, b = header.span("alignment")
                    text = text[:a] + "1" + text[b:]
                    matches = list(slot.finditer(text))
        indent = matches[0].group("indent")
        replacement = ("\n" + indent).join(s["object"] + f"({s['section']});" for s in plan["slots"])
        text = text[:matches[0].start()] + indent + replacement + text[matches[0].end():]
    return text


def filter_owned_symbols(text: str, modules) -> str:
    """Remove only registered absolute assignments, checking name and VMA."""
    owned = {d["symbol"]: d["vram"] for _, sections in _unique_owned_data(modules)
             for records in sections.values() for d in records}
    if not owned:
        return text
    lines, seen = [], set()
    for line in text.splitlines(keepends=True):
        match = re.fullmatch(r"\s*([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;\s*", line)
        if match and match.group(1) in owned:
            name = match.group(1)
            if name in seen or int(match.group(2), 16) != owned[name]:
                raise ModuleError(f"{name}: duplicate or wrong-address absolute assignment")
            seen.add(name)
            continue
        lines.append(line)
    missing = set(owned) - seen
    if missing:
        raise ModuleError(f"missing owned absolute assignment(s): {sorted(missing)}")
    return "".join(lines)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__)
    sub = ap.add_subparsers(dest="command", required=True)
    for name in ("assets", "orderld", "symbols"):
        p = sub.add_parser(name)
        p.add_argument("--manifest", required=True)
        p.add_argument("--root", default=".")
        if name != "symbols":
            p.add_argument("--out-dir", default="build/module_assets")
        if name != "assets":
            p.add_argument("--input", required=True)
            p.add_argument("--output", required=True)
        else:
            p.add_argument("--assemble", action="store_true")
    args = ap.parse_args(argv)
    root = Path(args.root).resolve()
    _path(args.manifest, "manifest", suffix=".json")
    if args.command != "assets":
        _path(args.input, "input")
        _path(args.output, "output")
    modules = load_manifest(root / args.manifest)
    if args.command == "assets":
        plan = plan_asset_carves(modules, root, args.out_dir)
        materialize_asset_chunks(plan, root, assemble=args.assemble)
        print(json.dumps(plan, sort_keys=True))
        return
    source = (root / args.input).read_text()
    if args.command == "orderld":
        plan = plan_asset_carves(modules, root, args.out_dir)
        output = rewrite_ordered_linker_script(source, plan)
    else:
        output = filter_owned_symbols(source, modules)
    dest = _prepare_output(root, args.output)
    dest.write_text(output)


if __name__ == "__main__":
    main()
