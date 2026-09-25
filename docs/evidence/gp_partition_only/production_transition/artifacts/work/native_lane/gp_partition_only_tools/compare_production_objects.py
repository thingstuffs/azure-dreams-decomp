#!/usr/bin/env python3
"""Compare active SLUS objects with the final private proof without rebuilding."""

from collections import Counter
import hashlib
import json
from pathlib import Path
import struct
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
FIXTURE = HERE / "retire_sink/combined_final_fixture"
OUT = HERE / "production_object_comparison.json"
sys.path[:0] = [str(ROOT / "tools"), str(ROOT / "tools/fidelity")]
from row_db import edges_of
from objread import read_elf


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def file_sha(path: Path) -> str:
    return sha(path.read_bytes())


def normalized_digest(obj) -> str:
    record = {
        "fmt": obj.fmt,
        "sections": {name: data.hex() for name, data in sorted(obj.sections.items())},
        "symbols": obj.symbols,
        "relocs": obj.relocs,
        "func_extents": obj.func_extents,
        "unknown": obj.unknown,
    }
    return sha(json.dumps(record, sort_keys=True, separators=(",", ":")).encode())


def elf_sections(data: bytes) -> tuple[dict[str, tuple], list[tuple[int, int, str]]]:
    if data[:6] != b"\x7fELF\x01\x01":
        raise ValueError("expected ELF32 little-endian object")
    shoff = struct.unpack_from("<I", data, 0x20)[0]
    ehsize = struct.unpack_from("<H", data, 0x28)[0]
    entsize, count, strings_index = struct.unpack_from("<HHH", data, 0x2E)
    headers = [struct.unpack_from("<IIIIIIIIII", data, shoff + index * entsize)
               for index in range(count)]
    strings = headers[strings_index]
    string_table = data[strings[4]:strings[4] + strings[5]]

    def section_name(offset: int) -> str:
        end = string_table.index(b"\0", offset)
        return string_table[offset:end].decode("latin1")

    result = {}
    regions = [(0, ehsize, "ELF header"), (shoff, shoff + count * entsize, "section headers")]
    for header in headers:
        name = section_name(header[0])
        if name in result:
            raise ValueError("duplicate ELF section name: " + name)
        kind, offset, size = header[1], header[4], header[5]
        body = b"" if kind == 8 else data[offset:offset + size]
        result[name] = (header, body)
        if kind != 8 and size:
            regions.append((offset, offset + size, name or "null section"))
    return result, regions


def changed_regions(left: bytes, right: bytes) -> list[str]:
    left_sections, left_regions = elf_sections(left)
    right_sections, right_regions = elf_sections(right)
    if set(left_sections) != set(right_sections):
        raise ValueError("ELF section names differ")
    changed = set()
    for name in left_sections:
        header_a, body_a = left_sections[name]
        header_b, body_b = right_sections[name]
        if body_a != body_b:
            changed.add(name or "null section")
        if header_a != header_b:
            changed.add("section headers")
    if left[:52] != right[:52]:
        changed.add("ELF header")
    # Account for layout padding or non-section bytes as well as section data.
    def region_at(index: int, regions: list[tuple[int, int, str]]) -> str:
        for start, end, name in regions:
            if start <= index < end:
                return name
        return "unmapped bytes"
    for index in range(max(len(left), len(right))):
        a = left[index] if index < len(left) else None
        b = right[index] if index < len(right) else None
        if a != b:
            changed.add(region_at(index, left_regions))
            changed.add(region_at(index, right_regions))
    return sorted(changed)


def main() -> None:
    if OUT.exists():
        raise ValueError("refusing to overwrite object comparison receipt")
    ninja = ROOT / "build_slus/build.ninja"
    private_ninja = FIXTURE / "build_slus/build.ninja"
    edges = edges_of(ninja.read_text())
    if len(edges) != 860 or len({edge["out"] for edge in edges}) != 860:
        raise ValueError("active physical edge count or identities changed")
    records = []
    raw_counts = Counter()
    region_counts = Counter()
    for edge in edges:
        output = edge["out"]
        active_path = ROOT / "build_slus" / output
        private_path = FIXTURE / "build_slus" / output
        active = active_path.read_bytes()
        private = private_path.read_bytes()
        a, b = read_elf(active), read_elf(private)
        fields = ("fmt", "sections", "symbols", "relocs", "func_extents", "unknown")
        different_fields = [name for name in fields if getattr(a, name) != getattr(b, name)]
        if different_fields:
            raise ValueError(f"parsed object differs for {output}: {different_fields}")
        same_bytes = active == private
        raw_counts["same" if same_bytes else "different"] += 1
        changed = [] if same_bytes else changed_regions(active, private)
        region_counts.update(changed)
        records.append({
            "output": output,
            "active_sha256": sha(active),
            "private_sha256": sha(private),
            "active_bytes": len(active),
            "private_bytes": len(private),
            "raw_bytes_equal": same_bytes,
            "parsed_fields_equal": True,
            "normalized_sha256": normalized_digest(a),
            "raw_changed_regions": changed,
        })
    result = {
        "schema": 1,
        "status": "PARSED_OBJECTS_EQUAL",
        "interpretation": "All active objects match the final private proof in objread code/data sections, relevant symbols, relocations, function extents and unknown-relocation diagnostics. Raw ELF differences are retained below by region; raw object byte equality is not claimed.",
        "active_ninja_sha256": file_sha(ninja),
        "private_ninja_sha256": file_sha(private_ninja),
        "row_db_sha256": file_sha(ROOT / "tools/row_db.py"),
        "objread_sha256": file_sha(ROOT / "tools/fidelity/objread.py"),
        "script_sha256": file_sha(Path(__file__)),
        "physical_objects": len(records),
        "raw_object_counts": dict(raw_counts),
        "raw_changed_region_object_counts": dict(sorted(region_counts.items())),
        "objects": records,
    }
    OUT.write_text(json.dumps(result, indent=2) + "\n")
    print(json.dumps({key: result[key] for key in
                      ("status", "physical_objects", "raw_object_counts",
                       "raw_changed_region_object_counts")}))


if __name__ == "__main__":
    main()
