#!/usr/bin/env python3
"""Bounded exact-word caller scan for the three unregistered MAIN routines."""

from __future__ import annotations

import hashlib
import json
import struct
import subprocess
import sys
from collections import Counter
from pathlib import Path


HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
sys.path.insert(0, str(ROOT / "tools/fidelity"))
from audit_main_kernel import ROWS  # noqa: E402


BINARIES = {
    "slus": ROOT / "baserom/slus_006.14",
    "main": ROOT / "work/disc/containers/MAIN_MAIN.BIN",
    "town": ROOT / "work/disc/containers/TOWN_TOWN.BIN",
    "dungeon": ROOT / "work/disc/containers/DUNGEON_DUNGEON.BIN",
    "ovmovie": ROOT / "work/disc/containers/OVMOVIE.BIN",
}
PROVEN_MAIN_DEVKIT_START = 0x269000
PROVEN_MAIN_DEVKIT_END = 0x275800
PROVEN_MAIN_DEVKIT_VMA = 0x80400000
DERIVED_MAIN_BOOT_START = 0x25D000
DERIVED_MAIN_BOOT_END = 0x272000
DERIVED_MAIN_BOOT_DELTA = 0x7FDB0000
CALLER_BLOCK = (0x2716D0, 0x2717A0)
CALLER_FUNCTIONS = (
    (0x2716DC, 0x271730, "caller_804086DC"),
    (0x271768, 0x271798, "caller_80408768"),
)
EXPECTED_SLICES = {
    "func_800217C8": "3b175235864c739f6d9fa48c4589d1f3631317a5aac4855140ac2bb0bf9eef6e",
    "func_800218A0": "bf2101ffd41591f38a4f0dd260b22289c6eeb3e8b91416c96dd686bbef1fb1a0",
    "func_80021958": "00fb85f0f54031f2fa57511044aefda649acbccb70d413f5903165dae51000a8",
}


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def relative(path: Path) -> str:
    return str(path.relative_to(ROOT))


def split_rows(kind: str) -> list[dict]:
    if kind == "slus":
        return []
    path = ROOT / "ledger/splits" / f"{kind}.jsonl"
    return [json.loads(line) for line in path.read_text().splitlines() if line.strip()]


def covering_rows(rows: list[dict], offset: int) -> list[dict]:
    hits = []
    for row in rows:
        if not isinstance(row.get("foff"), int) or not isinstance(row.get("size"), int):
            continue
        if row["foff"] <= offset < row["foff"] + row["size"]:
            hits.append({"id": row.get("func_vram"), "foff": row["foff"],
                         "size": row["size"], "vram": row.get("vram"),
                         "result": row.get("result")})
    return hits


def location(kind: str, offset: int, rows: list[dict]) -> dict:
    out = {"split_rows": covering_rows(rows, offset)}
    if kind == "main":
        if PROVEN_MAIN_DEVKIT_START <= offset < PROVEN_MAIN_DEVKIT_END:
            out["proven_devkit_vma"] = PROVEN_MAIN_DEVKIT_VMA + offset - PROVEN_MAIN_DEVKIT_START
        if DERIVED_MAIN_BOOT_START <= offset < DERIVED_MAIN_BOOT_END:
            out["main_boot_derived_vma"] = DERIVED_MAIN_BOOT_DELTA + offset
        for lo, hi, name in CALLER_FUNCTIONS:
            if lo <= offset < hi:
                out["disassembled_caller_block"] = name
    elif kind == "town":
        out["row_derived_vmas"] = [r["vram"] + offset - r["foff"] for r in out["split_rows"]]
        if CALLER_BLOCK[0] <= offset < CALLER_BLOCK[1]:
            out["same_offset_as_main_caller_block"] = True
    elif kind == "slus" and offset >= 0x800:
        out["resident_segment_vma"] = 0x8002D000 + offset - 0x800
    return out


def variants() -> dict[str, dict]:
    out = {}
    for name, offset, size, synthetic in ROWS:
        assert synthetic == DERIVED_MAIN_BOOT_DELTA + offset
        actual = PROVEN_MAIN_DEVKIT_VMA + offset - PROVEN_MAIN_DEVKIT_START
        out[name] = {"file_offset": offset, "size": size, "main_boot_derived_vma": synthetic,
                     "proven_devkit_link_vma": actual,
                     "uncached_aliases": [synthetic | 0x20000000, actual | 0x20000000]}
    return out


def main() -> None:
    target = variants()
    main_image = BINARIES["main"].read_bytes()
    for name, item in target.items():
        lo = item["file_offset"]
        item["slice_sha256"] = sha(main_image[lo:lo + item["size"]])
        if item["slice_sha256"] != EXPECTED_SLICES[name]:
            raise ValueError(f"target slice changed: {name}")
    target_addresses = {}
    for name, item in target.items():
        for spelling, addr in (("main_boot_derived_vma", item["main_boot_derived_vma"]),
                               ("proven_devkit_link_vma", item["proven_devkit_link_vma"]),
                               ("derived_uncached_alias", item["uncached_aliases"][0]),
                               ("devkit_uncached_alias", item["uncached_aliases"][1])):
            target_addresses[addr] = {"target": name, "spelling": spelling}
    fields = {}
    for addr, item in target_addresses.items():
        fields.setdefault((addr >> 2) & 0x3FFFFFF, []).append(item | {"address": addr})

    binary_inputs = {}
    jump_hits = []
    pointer_hits = []
    for kind, path in BINARIES.items():
        data = path.read_bytes()
        rows = split_rows(kind)
        binary_inputs[kind] = {"path": relative(path), "size": len(data), "sha256": sha(data)}
        for index, (word,) in enumerate(struct.iter_unpack("<I", data[:len(data) & ~3])):
            opcode = word >> 26
            if opcode not in (2, 3):
                continue
            candidates = fields.get(word & 0x3FFFFFF)
            if not candidates:
                continue
            offset = index * 4
            loc = location(kind, offset, rows)
            pc = loc.get("proven_devkit_vma")
            if pc is None and len(loc.get("row_derived_vmas", [])) == 1:
                pc = loc["row_derived_vmas"][0]
            decoded = ((pc + 4) & 0xF0000000 | ((word & 0x3FFFFFF) << 2)) if pc is not None else None
            jump_hits.append({"binary": kind, "file_offset": offset, "word": word,
                              "mnemonic": "jal" if opcode == 3 else "j",
                              "low_28_target": (word & 0x3FFFFFF) << 2,
                              "decoded_target_if_mapped": decoded,
                              "target_candidates": candidates, "location": loc})
        for address, item in target_addresses.items():
            needle = struct.pack("<I", address)
            start = 0
            while True:
                offset = data.find(needle, start)
                if offset < 0:
                    break
                context_lo = max(0, (offset & ~3) - 12)
                context_hi = min(len(data), (offset & ~3) + 16)
                context = [word[0] for word in struct.iter_unpack(
                    "<I", data[context_lo:context_hi & ~3])]
                pointer_hits.append({"binary": kind, "file_offset": offset,
                                     "word_aligned": offset % 4 == 0, "address": address,
                                     "target": item["target"], "spelling": item["spelling"],
                                     "context_offset": context_lo, "context_words": context,
                                     "location": location(kind, offset, rows)})
                start = offset + 1

    # The MAIN code block is in the devkit-linked 0x80400000 module, despite
    # main_boot's synthetic 0x8002xxxx names. Check the TOWN copy byte-for-byte.
    lo, hi = CALLER_BLOCK
    main_block = main_image[lo:hi]
    town_block = BINARIES["town"].read_bytes()[lo:hi]
    if main_block != town_block:
        raise ValueError("MAIN/TOWN caller block is no longer byte-identical")
    expected_jumps = {0x271704: 0x804088A0, 0x27170C: 0x80408958,
                      0x271778: 0x80408958, 0x271780: 0x804087C8}
    for kind in ("main", "town"):
        actual = {x["file_offset"]: x["decoded_target_if_mapped"]
                  for x in jump_hits if x["binary"] == kind}
        if actual != expected_jumps or len([x for x in jump_hits if x["binary"] == kind]) != 4:
            raise ValueError(f"{kind} direct-jump map changed: {actual}")
    if [(x["binary"], x["file_offset"], x["address"]) for x in pointer_hits] != [
        ("town", 0x79D890, 0x80021958)
    ]:
        raise ValueError("exact pointer-word hit set changed")
    (HERE / "main_callsite_block.bin").write_bytes(main_block)
    (HERE / "town_callsite_block.bin").write_bytes(town_block)
    pointer_context = BINARIES["town"].read_bytes()[0x79D880:0x79D8A0]
    (HERE / "town_pointer_block.bin").write_bytes(pointer_context)
    for kind in ("main", "town"):
        binary = HERE / f"{kind}_callsite_block.bin"
        vma = PROVEN_MAIN_DEVKIT_VMA + lo - PROVEN_MAIN_DEVKIT_START
        with (HERE / f"{kind}_callsite_block.disasm.txt").open("w") as out:
            subprocess.run(["mipsel-linux-gnu-objdump", "-D", "-b", "binary", "-m", "mips:3000",
                            "-EL", f"--adjust-vma=0x{vma:08X}", str(binary)],
                           check=True, stdout=out, text=True)

    source_paths = [ROOT / "tools/fidelity/audit_main_kernel.py",
                    ROOT / "docs/evidence/main_kernel_coverage_audit.md",
                    ROOT / "docs/evidence/konami_assertion_sites.md",
                    ROOT / "config/overlays/main_boot.overlay.yaml",
                    ROOT / "config/overlays/main_menu_t8.overlay.yaml",
                    ROOT / "config/slus_006.14.yaml",
                    *(ROOT / "ledger/splits" / f"{kind}.jsonl" for kind in ("main", "town", "dungeon", "ovmovie"))]
    receipt = {
        "scope": "read-only exact J/JAL field and exact 32-bit word scan over five held binaries",
        "script_sha256": sha(Path(__file__).read_bytes()),
        "sources_sha256": {relative(path): sha(path.read_bytes()) for path in source_paths},
        "binary_inputs": binary_inputs,
        "targets": target,
        "jump_hits": jump_hits,
        "pointer_hits": pointer_hits,
        "counts": {"jump_hits_by_binary": dict(Counter(x["binary"] for x in jump_hits)),
                   "pointer_hits_by_binary": dict(Counter(x["binary"] for x in pointer_hits))},
        "main_town_caller_block": {"file_extent": [lo, hi], "size": hi - lo,
                                   "main_sha256": sha(main_block), "town_sha256": sha(town_block),
                                   "byte_identical": main_block == town_block,
                                   "proven_devkit_link_vma": PROVEN_MAIN_DEVKIT_VMA + lo - PROVEN_MAIN_DEVKIT_START},
        "town_pointer_context": {"file_extent": [0x79D880, 0x79D8A0],
                                 "sha256": sha(pointer_context)},
    }
    (HERE / "receipt.json").write_text(json.dumps(receipt, indent=2) + "\n")
    print(json.dumps({"counts": receipt["counts"], "block_equal": main_block == town_block,
                      "jump_hits": len(jump_hits), "pointer_hits": len(pointer_hits)}, indent=2))


if __name__ == "__main__":
    main()
