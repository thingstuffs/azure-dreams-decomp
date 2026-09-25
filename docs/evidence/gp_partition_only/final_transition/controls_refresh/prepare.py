#!/usr/bin/env python3
"""Detach the final candidate fixture for control-only validation."""

from __future__ import annotations

import hashlib
import json
import os
from pathlib import Path
import shutil


HERE = Path(__file__).resolve().parent
LANE = HERE.parent
REPO = HERE.parents[3]
SOURCE = LANE / "census_final_fixture"
DEST = HERE / "fixture"
TOOLS = ("aspsx_diff.py", "maspsx_trace.py")
CASES = ("sw_base.o", "sw_preserve.o", "sw.proc.s", "sw.c")


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main() -> None:
    if DEST.exists():
        raise RuntimeError("control fixture already exists")
    import sys
    sys.path.insert(0, str(LANE))
    from live_ownership_probe import production_snapshot
    before = production_snapshot()
    shutil.copytree(SOURCE, DEST, symlinks=True,
                    ignore=shutil.ignore_patterns("__pycache__", "*.pyc"))
    (DEST / ".ignore").write_text("*\n")
    old_root, new_root = str(SOURCE.resolve()), str(DEST.resolve())
    relinked = []
    for path in DEST.rglob("*"):
        if not path.is_symlink():
            continue
        target = str(path.readlink())
        if target == old_root or target.startswith(old_root + os.sep):
            path.unlink()
            path.symlink_to(new_root + target[len(old_root):])
            relinked.append(str(path.relative_to(DEST)))
    tool_pins = {}
    for name in TOOLS:
        source = HERE / "tools/fidelity" / name
        target = DEST / "tools/fidelity" / name
        shutil.copyfile(source, target)
        if sha(source) != sha(target):
            raise RuntimeError("private tool copy differs: " + name)
        tool_pins[name] = {"before": sha(SOURCE / "tools/fidelity" / name),
                           "after": sha(target)}
    cases = {}
    target_root = DEST / "work/maspsx_jtbl"
    target_root.mkdir(parents=True, exist_ok=False)
    for name in CASES:
        source = REPO / "work/maspsx_jtbl" / name
        target = target_root / name
        shutil.copyfile(source, target)
        if sha(source) != sha(target):
            raise RuntimeError("historical casesi object copy differs: " + name)
        cases[name] = sha(target)
    if sha(DEST / "ledger/rows.jsonl") != sha(SOURCE / "ledger/rows.jsonl"):
        raise RuntimeError("control fixture changed the registered row set")
    for path in DEST.rglob("*"):
        if path.is_symlink():
            target = str(path.readlink())
            if target == old_root or target.startswith(old_root + os.sep):
                raise RuntimeError("control fixture symlink still points to frozen source")
    after = production_snapshot()
    if before != after:
        raise RuntimeError("production changed during control fixture setup")
    receipt = {
        "status": "PREPARED", "schema": 1,
        "source_fixture_receipt_sha256": sha(SOURCE / "final_source_fixture_receipt.json"),
        "registry_sha256": sha(DEST / "ledger/rows.jsonl"),
        "tool_pins": tool_pins,
        "historical_casesi_pins": cases,
        "relinked_symlinks": relinked,
        "production_unchanged": True,
    }
    (HERE / "prepare_receipt.json").write_text(json.dumps(receipt, indent=2) + "\n")
    print(json.dumps({key: receipt[key] for key in
                      ("status", "registry_sha256", "production_unchanged")}, indent=2))


if __name__ == "__main__":
    main()
