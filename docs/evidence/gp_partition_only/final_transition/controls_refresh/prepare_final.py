#!/usr/bin/env python3
"""Preserve the first control failure and make a detached revised fixture."""

from __future__ import annotations

import hashlib
import json
import os
from pathlib import Path
import shutil
import sys


HERE = Path(__file__).resolve().parent
LANE = HERE.parent
OLD = HERE / "fixture"
NEW = HERE / "fixture_final"


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main() -> None:
    if NEW.exists():
        raise RuntimeError("revised control fixture already exists")
    sys.path.insert(0, str(LANE))
    from live_ownership_probe import production_snapshot
    initial = json.loads((HERE / "prepare_receipt.json").read_text())
    original_run = json.loads((HERE / "run_receipt.json").read_text())
    if original_run["status"] != "FAIL" or len(original_run["failed_controls"]) != 1 or \
            "plain slus/code" not in original_run["failed_controls"][0]:
        raise RuntimeError("historical first failure is not preserved")
    if sha(OLD / "tools/fidelity/aspsx_diff.py") != initial["tool_pins"]["aspsx_diff.py"]["after"]:
        raise RuntimeError("first fixture tools changed")
    before = production_snapshot()
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
    tool_pins = {}
    for name in ("aspsx_diff.py", "maspsx_trace.py"):
        source = HERE / "tools/fidelity" / name
        target = NEW / "tools/fidelity" / name
        shutil.copyfile(source, target)
        if sha(source) != sha(target):
            raise RuntimeError("revised control tool copy differs: " + name)
        tool_pins[name] = {"before": sha(OLD / "tools/fidelity" / name),
                           "after": sha(target)}
    for name, digest in initial["historical_casesi_pins"].items():
        if sha(NEW / "work/maspsx_jtbl" / name) != digest:
            raise RuntimeError("historical casesi input changed: " + name)
    if sha(NEW / "ledger/rows.jsonl") != initial["registry_sha256"]:
        raise RuntimeError("revised fixture registry changed")
    after = production_snapshot()
    if before != after:
        raise RuntimeError("production changed during revised control fixture setup")
    receipt = {
        "schema": 1, "status": "PREPARED",
        "initial_run_receipt_sha256": sha(HERE / "run_receipt.json"),
        "initial_run_log_sha256": sha(HERE / "run.log"),
        "registry_sha256": initial["registry_sha256"],
        "historical_casesi_pins": initial["historical_casesi_pins"],
        "tool_pins": tool_pins,
        "relinked_symlinks": relinked,
        "production_unchanged": True,
    }
    (HERE / "prepare_final_receipt.json").write_text(json.dumps(receipt, indent=2) + "\n")
    print(json.dumps({key: receipt[key] for key in
                      ("status", "registry_sha256", "production_unchanged")}, indent=2))


if __name__ == "__main__":
    main()
