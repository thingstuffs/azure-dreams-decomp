#!/usr/bin/env python3
"""Make a separate four-source canonical repair fixture for two-row remeasurement."""

from __future__ import annotations

import hashlib
import json
import os
from pathlib import Path
import shutil

from live_ownership_probe import production_snapshot


HERE = Path(__file__).resolve().parent
OLD = HERE / "census_fixture"
NEW = HERE / "census_final_fixture"
AFTER = HERE / "transition/inputs/canonical_sources/after"
COMPAT = HERE / "census_transition_compatibility.json"
NAMES = ("gp_d92c_owned.c", "gp_order_bytes_owner.c",
         "w_8003D92C.c", "w_80049F68.c")


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main() -> None:
    if NEW.exists():
        raise RuntimeError("final-source fixture already exists")
    compat = json.loads(COMPAT.read_text())
    if compat["status"] != "COMPATIBLE_WITH_EXPLICIT_SOURCE_BRIDGE":
        raise RuntimeError("transition bridge is not established")
    canonical = json.loads((HERE / "transition/inputs/canonical_sources/receipt.json").read_text())
    original_receipt = json.loads((OLD / "census_setup_receipt.json").read_text())
    if original_receipt["status"] != "PREPARED":
        raise RuntimeError("frozen source fixture is unavailable")
    before_production = production_snapshot()
    shutil.copytree(OLD, NEW, symlinks=True,
                    ignore=shutil.ignore_patterns("__pycache__", "*.pyc"))
    (NEW / ".ignore").write_text("*\n")
    old_root = str(OLD.resolve())
    new_root = str(NEW.resolve())
    relinked = []
    for path in NEW.rglob("*"):
        if not path.is_symlink():
            continue
        target = str(path.readlink())
        if target == old_root or target.startswith(old_root + os.sep):
            replacement = new_root + target[len(old_root):]
            path.unlink()
            path.symlink_to(replacement)
            relinked.append(str(path.relative_to(NEW)))
    for path in NEW.rglob("*"):
        if path.is_symlink():
            target = str(path.readlink())
            if target == old_root or target.startswith(old_root + os.sep):
                raise RuntimeError("cloned link still targets frozen fixture: " + str(path))
    old_sources = {}
    new_sources = {}
    for name in NAMES:
        expected = canonical["proposed_sources"][name]
        source = AFTER / name
        if sha(source) != expected:
            raise RuntimeError("canonical payload source changed: " + name)
        old_sources[name] = sha(OLD / "src/slus" / name)
        for target in (NEW / "src/slus" / name, NEW / "build_slus/src" / name):
            shutil.copyfile(source, target)
            os.utime(target, None)
            if sha(target) != expected:
                raise RuntimeError("canonical private copy differs: " + str(target))
        new_sources[name] = expected
    for stem in ("gp_d92c_owned", "gp_order_bytes_owner"):
        object_path = NEW / "build_slus/build/src" / (stem + ".o")
        if not object_path.is_file():
            raise RuntimeError("expected compiled owner object is missing: " + str(object_path))
        object_path.unlink()
    after_production = production_snapshot()
    if after_production != before_production:
        raise RuntimeError("production changed during private canonical fixture preparation")
    result = {
        "schema": 1,
        "status": "PREPARED",
        "frozen_fixture_setup_sha256": sha(OLD / "census_setup_receipt.json"),
        "transition_compatibility_sha256": sha(COMPAT),
        "canonical_receipt_sha256": sha(HERE / "transition/inputs/canonical_sources/receipt.json"),
        "source_before_sha256": old_sources,
        "source_after_sha256": new_sources,
        "relinked_internal_symlinks": relinked,
        "invalidated_owner_objects": ["gp_d92c_owned.o", "gp_order_bytes_owner.o"],
        "registry_sha256": sha(NEW / "ledger/rows.jsonl"),
        "production_unchanged": True,
    }
    (NEW / "final_source_fixture_receipt.json").write_text(json.dumps(result, indent=2) + "\n")
    print(json.dumps({key: result[key] for key in
                      ("status", "registry_sha256", "production_unchanged")}, indent=2))


if __name__ == "__main__":
    main()
