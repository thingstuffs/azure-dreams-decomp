#!/usr/bin/env python3
"""Prepare one-pass retirement candidate without touching production or frozen fixtures."""

from __future__ import annotations

import difflib
import hashlib
import json
from pathlib import Path
import shutil
import subprocess

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
BASE = ROOT / "work/native_lane/selfinc_local_guard/candidate"
TEST_BASE = ROOT / "work/native_lane/gp_partition_only_tools/assembler_tests_candidate"
CAND = HERE / "candidate"
TEST = HERE / "test_fixture"
CLI_SHA = "d3e6ec7d120abe00f963c82258dfdeb0e228774adce646177525f1dbed925caf"
PACKAGE_SHA = "28e45bbcf00fc90dc0645250f233b73f96ad11d06a2f8230ce533fc2fafbbfbe"
TEST_PATCH_SHA = "4b9ee5cb58fcc4b367da73bfd585d5fcce28aca1625fc362f3f610dd8e5d3430"
MIGRATED_TEST_SHA = "80b9372b1db8fb2ca1bdc9a893f1d5c78a15bd581bf02e0da011394194fcc4f8"
METHOD = "    def _sink_call_separated_la(self, res):\n"
NEXT_METHOD = "    def _expand_smalldata_la(self, res):\n"
CALL = "        res = self._sink_call_separated_la(res)\n"


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main() -> None:
    if CAND.exists() or TEST.exists():
        raise RuntimeError("private candidate or test fixture already exists")
    if sha(BASE / "maspsx.py") != CLI_SHA or sha(BASE / "maspsx/__init__.py") != PACKAGE_SHA:
        raise RuntimeError("guarded generic starting bytes changed")
    census = json.loads((ROOT / "work/native_lane/gp_partition_only_tools/census_report/summary.json").read_text())
    record = census["pass_probe"]["_sink_call_separated_la"]
    if census["rows"] != 6767 or record != {
            "fired_rows": [], "fired_units": [], "required_rows": [], "required_units": []}:
        raise RuntimeError("reconciled census no longer supports retirement probe")
    old = (BASE / "maspsx/__init__.py").read_text()
    if old.count(METHOD) != 1 or old.count(NEXT_METHOD) != 1 or old.count(CALL) != 1:
        raise RuntimeError("pass definition or callsite is not unique")
    start = old.index(METHOD)
    end = old.index(NEXT_METHOD, start)
    new = old[:start] + old[end:]
    new = new.replace(CALL, "", 1)
    if "_sink_call_separated_la" in new:
        raise RuntimeError("pass reference remains in retired package")
    CAND.mkdir()
    (CAND / "maspsx").mkdir()
    shutil.copy2(BASE / "maspsx.py", CAND / "maspsx.py")
    (CAND / "maspsx/__init__.py").write_text(new)
    patch = "".join(difflib.unified_diff(old.splitlines(True), new.splitlines(True),
        fromfile="a/tools/maspsx/maspsx/__init__.py",
        tofile="b/tools/maspsx/maspsx/__init__.py"))
    (HERE / "removal.patch").write_text(patch)
    shutil.copytree(TEST_BASE / "tools/maspsx/tests", TEST / "tools/maspsx/tests",
                    ignore=shutil.ignore_patterns("__pycache__", "*.pyc"))
    (TEST / "tools/maspsx/__init__.py").write_text("")
    (TEST / "tools/maspsx/maspsx.py").symlink_to(CAND / "maspsx.py")
    (TEST / "toolchain/maspsx").mkdir(parents=True)
    (TEST / "toolchain/maspsx/maspsx.py").symlink_to(CAND / "maspsx.py")
    (TEST / "config").mkdir()
    for name in ("sibcall_syms.txt", "noreturn_syms.txt"):
        shutil.copy2(ROOT / "config" / name, TEST / "config" / name)
    before_tests = {str(p.relative_to(TEST_BASE)): sha(p) for p in
                    sorted(TEST_BASE.joinpath("tools/maspsx/tests").rglob("*"))
                    if p.is_file() and not p.is_symlink()}
    after_tests = {str(p.relative_to(TEST)): sha(p) for p in
                   sorted(TEST.joinpath("tools/maspsx/tests").rglob("*"))
                   if p.is_file() and not p.is_symlink()}
    if before_tests != after_tests:
        raise RuntimeError("migrated test fixture copy differs")
    test_patch = HERE / "test_migration.patch"
    if sha(test_patch) != TEST_PATCH_SHA:
        raise RuntimeError("synthetic regression migration changed")
    subprocess.run(["patch", "-p1", "--batch", "--forward", "-i", str(test_patch)],
                   cwd=TEST, check=True, capture_output=True, text=True)
    migrated = TEST / "tools/maspsx/tests/test_fold_selfinc_la.py"
    if sha(migrated) != MIGRATED_TEST_SHA:
        raise RuntimeError("migrated synthetic regression differs")
    changed_tests = {name for name, digest in before_tests.items()
                     if sha(TEST / name) != digest}
    if changed_tests != {"tools/maspsx/tests/test_fold_selfinc_la.py"}:
        raise RuntimeError("unexpected migrated test change: " + repr(changed_tests))
    receipt = {"status": "PREPARED", "census_rows": census["rows"],
        "census_summary_sha256": sha(ROOT / "work/native_lane/gp_partition_only_tools/census_report/summary.json"),
        "guarded_cli_sha256": CLI_SHA, "guarded_package_sha256": PACKAGE_SHA,
        "candidate_cli_sha256": sha(CAND / "maspsx.py"),
        "candidate_package_sha256": sha(CAND / "maspsx/__init__.py"),
        "removal_patch_sha256": sha(HERE / "removal.patch"),
        "migrated_test_files": len(after_tests),
        "unchanged_test_files": len(after_tests) - len(changed_tests),
        "migrated_test_patch_sha256": TEST_PATCH_SHA,
        "migrated_test_sha256": MIGRATED_TEST_SHA,
        "deleted_method_lines": old[start:end].count("\n"),
        "removed_call_count": 1,
        "candidate_has_retired_reference": False}
    (HERE / "prepare_receipt.json").write_text(json.dumps(receipt, indent=2) + "\n")
    print(json.dumps(receipt, indent=2))


if __name__ == "__main__":
    main()
