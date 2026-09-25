#!/usr/bin/env python3
"""Detach the 60-pass fixture and replace only its guarded assembler with retired bytes."""

from __future__ import annotations

import hashlib
import json
import os
from pathlib import Path
import shutil
import sys


HERE = Path(__file__).resolve().parent
LANE = HERE.parent
OLD = HERE / "fixture_final"
NEW = HERE / "fixture_retired"
CANDIDATE = LANE / "retire_sink/candidate"
ASSEMBLER_FILES = ("maspsx.py", "maspsx/__init__.py")
EXPECTED = {
    "maspsx.py": "d3e6ec7d120abe00f963c82258dfdeb0e228774adce646177525f1dbed925caf",
    "maspsx/__init__.py": "b89099797be1352d3122455164062d428dcc74529344a919d169e05f663afc52",
}


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def tree_digest(path: Path) -> str:
    h = hashlib.sha256()
    for file in sorted(path.rglob("*")):
        if file.is_file() and not file.is_symlink():
            h.update(str(file.relative_to(path)).encode())
            h.update(sha(file).encode())
    return h.hexdigest()


def source_pins(root: Path) -> dict:
    return {name: tree_digest(root / name) for name in
            ("src", "build_slus/src", "include", "raw/slus")}


def main() -> None:
    if NEW.exists():
        raise RuntimeError("retired control fixture already exists")
    sys.path.insert(0, str(LANE))
    from live_ownership_probe import production_snapshot
    previous = json.loads((HERE / "final_run_receipt.json").read_text())
    if previous["status"] != "PASS" or previous["passed_controls"] != 60:
        raise RuntimeError("frozen guarded 60-pass control run is unavailable")
    source_before = source_pins(OLD)
    before_production = production_snapshot()
    shutil.copytree(OLD, NEW, symlinks=True,
                    ignore=shutil.ignore_patterns("__pycache__", "*.pyc"))
    (NEW / ".ignore").write_text("*\n")
    old_root, new_root = str(OLD.resolve()), str(NEW.resolve())
    relinked = []
    for path in NEW.rglob("*"):
        if not path.is_symlink():
            continue
        target = str(path.readlink())
        if target == old_root or target.startswith(old_root + os.sep):
            path.unlink()
            path.symlink_to(new_root + target[len(old_root):])
            relinked.append(str(path.relative_to(NEW)))
    assembler = {}
    for name in ASSEMBLER_FILES:
        source = CANDIDATE / name
        if sha(source) != EXPECTED[name]:
            raise RuntimeError("retired candidate assembler changed: " + name)
        for base in ("tools/maspsx", "toolchain/maspsx"):
            old_path = OLD / base / name
            new_path = NEW / base / name
            before = sha(old_path)
            shutil.copyfile(source, new_path)
            after = sha(new_path)
            if after != EXPECTED[name]:
                raise RuntimeError("retired private assembler copy differs: " + str(new_path))
            assembler[base + "/" + name] = {"before": before, "after": after}
    control_tools = {}
    for name in ("aspsx_diff.py", "maspsx_trace.py"):
        before = sha(OLD / "tools/fidelity" / name)
        after = sha(NEW / "tools/fidelity" / name)
        if before != after:
            raise RuntimeError("control tool changed during assembler replacement: " + name)
        control_tools[name] = before
    source_after = source_pins(NEW)
    if source_after != source_before:
        raise RuntimeError("candidate source tree changed during assembler replacement")
    if sha(OLD / "ledger/rows.jsonl") != sha(NEW / "ledger/rows.jsonl"):
        raise RuntimeError("registered row set changed")
    for name, digest in json.loads((HERE / "prepare_final_receipt.json").read_text())["historical_casesi_pins"].items():
        if sha(NEW / "work/maspsx_jtbl" / name) != digest:
            raise RuntimeError("historical casesi input changed: " + name)
    after_production = production_snapshot()
    if before_production != after_production:
        raise RuntimeError("production changed during private retired fixture setup")
    receipt = {
        "schema": 1, "status": "PREPARED",
        "guarded_run_receipt_sha256": sha(HERE / "final_run_receipt.json"),
        "candidate_assembler": EXPECTED,
        "assembler_before_after": assembler,
        "control_tools_before_after_equal": control_tools,
        "source_trees_before": source_before,
        "source_trees_after": source_after,
        "registry_sha256": sha(NEW / "ledger/rows.jsonl"),
        "historical_casesi_pins": json.loads((HERE / "prepare_final_receipt.json").read_text())[
            "historical_casesi_pins"],
        "relinked_symlinks": relinked,
        "production_unchanged": True,
    }
    (HERE / "prepare_retired_receipt.json").write_text(json.dumps(receipt, indent=2) + "\n")
    print(json.dumps({key: receipt[key] for key in
                      ("status", "candidate_assembler", "production_unchanged")}, indent=2))


if __name__ == "__main__":
    main()
