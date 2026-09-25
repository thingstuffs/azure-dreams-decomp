#!/usr/bin/env python3
"""Stage the pre-validation-refresh sink-retirement proof without fixture trees."""

from __future__ import annotations

import gzip
import hashlib
import json
from pathlib import Path


HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
LANE = ROOT / "work/native_lane/gp_partition_only_tools/retire_sink"
OUT = HERE / "artifacts"
TEXT_REPLACEMENTS = (
    (str(ROOT), "<repo>", "repo_root"),
    (str(Path("<reference-repo>")), "<reference-repo>", "reference_repo_root"),
)

IN_LANE = (
    "REPORT.md", "receipt.json", "prepare_receipt.json", "prepare.py",
    "verify.py", "removal.patch", "supplemental.patch", "test_migration.patch",
    "unit.log", "patch_replay.log", "former_guarded.log", "former_retired.log",
    "former_guarded.o", "former_retired.o",
    "candidate/maspsx.py", "candidate/maspsx/__init__.py",
    "combined.py", "combined_receipt.json", "combined_prepare_receipt.json",
    "combined_ownership_receipt.json", "combined_source_pins.json",
    "combined_production_before.json", "combined_frozen_before.json",
    "combined_configure.log", "combined_rebuild.log", "combined_ownership.log",
    "combined_certify_list_cursor_e0.log",
    "combined_certify_runtime_directory.log",
    "combined_fixture/ledger/modules/list_cursor_e0.json",
    "combined_fixture/ledger/modules/runtime_directory.json",
    "overlay_gate/REPORT.md", "overlay_gate/receipt.json", "overlay_gate/run.py",
    "overlay_gate/journal.jsonl", "overlay_gate/gate.log", "overlay_gate/setup.log",
    "overlay_gate/unit.log", "overlay_gate/unit_before.log",
    "overlay_gate/unit_import.log", "overlay_gate/unit_selfinc.log",
)
EXTERNAL = (
    ("work/native_lane/gp_partition_only_tools/census_report/summary.json",
     "lineage/census_summary.json"),
    ("work/native_lane/gp_partition_only_tools/full_ownership/input_pins.json",
     "lineage/frozen_gp57_input_pins.json"),
    ("work/native_lane/gp_partition_only_tools/full_ownership/receipt.json",
     "lineage/frozen_gp57_ownership_receipt.json"),
    ("work/native_lane/gp_partition_only_tools/full_ownership/fixture/build_slus/build/src/w_8004AB7C.o",
     "former/frozen_final_w_8004AB7C.o"),
)


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def stage(src: Path, dest: Path) -> dict[str, object]:
    original = src.read_bytes()
    binary = src.suffix == ".o"
    replacements = {}
    if binary:
        archived = original
    else:
        value = original.decode("utf-8")
        for old, new, label in TEXT_REPLACEMENTS:
            replacements[label] = value.count(old)
            value = value.replace(old, new)
        archived = value.encode("utf-8")
        if any(old.encode() in archived for old, _, _ in TEXT_REPLACEMENTS):
            raise RuntimeError(f"unscrubbed workspace path: {dest}")
    compressed = (not binary and src.suffix in (".json", ".jsonl")
                  and len(archived) > 1_000_000)
    if compressed:
        archived = gzip.compress(archived, compresslevel=9, mtime=0)
        dest = dest.with_name(dest.name + ".gz")
    dest.parent.mkdir(parents=True, exist_ok=True)
    dest.write_bytes(archived)
    if digest(src.read_bytes()) != digest(original) or digest(dest.read_bytes()) != digest(archived):
        raise RuntimeError(f"changed during stage or archive write: {src}")
    return {
        "source_path": str(src.relative_to(ROOT)),
        "archive_path": str(dest.relative_to(HERE)),
        "original_sha256": digest(original),
        "archive_sha256": digest(archived),
        "original_bytes": len(original),
        "archive_bytes": len(archived),
        "format": "binary" if binary else ("deterministic_gzip_text" if compressed else "text"),
        "scrub_replacements": replacements,
    }


def main() -> None:
    if OUT.exists():
        raise RuntimeError("archive artifacts already exist; refusing to overwrite staged proof")
    records = [stage(LANE / name, OUT / name) for name in IN_LANE]
    records += [stage(ROOT / name, OUT / archived) for name, archived in EXTERNAL]
    records.sort(key=lambda item: item["archive_path"])
    index = {
        "schema": 1,
        "scope": "private sink-retirement baseline before validation-controls refresh; not final activation",
        "scrub": [{"source": label, "to": new} for _, new, label in TEXT_REPLACEMENTS],
        "gzip_rule": "UTF-8 .json/.jsonl text over 1,000,000 bytes, gzip level 9, mtime 0",
        "artifacts": records,
    }
    (HERE / "index.json").write_text(json.dumps(index, indent=2, sort_keys=True) + "\n")
    verify()
    print(f"staged and verified {len(records)} artifacts")


def verify() -> None:
    index = json.loads((HERE / "index.json").read_text())
    for item in index["artifacts"]:
        source = ROOT / item["source_path"]
        archived = HERE / item["archive_path"]
        if digest(source.read_bytes()) != item["original_sha256"]:
            raise RuntimeError(f"source hash changed: {source}")
        data = archived.read_bytes()
        if digest(data) != item["archive_sha256"] or len(data) != item["archive_bytes"]:
            raise RuntimeError(f"archive hash changed: {archived}")
        if item["format"] == "deterministic_gzip_text":
            data = gzip.decompress(data)
        if item["format"] != "binary":
            text = data.decode("utf-8")
            if any(old in text for old, _, _ in TEXT_REPLACEMENTS):
                raise RuntimeError(f"unscrubbed workspace path: {archived}")
    if len(index["artifacts"]) != len(IN_LANE) + len(EXTERNAL):
        raise RuntimeError("artifact count differs")


if __name__ == "__main__":
    main()
