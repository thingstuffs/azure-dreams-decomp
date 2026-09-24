#!/usr/bin/env python3
"""Run candidate partition-only and existing suites in one interpreter."""

from __future__ import annotations

import hashlib
import io
import json
import os
from pathlib import Path
import sys
import unittest

HERE = Path(__file__).resolve().parent
ROOT = HERE / "portable_regression_testroot"
PRODUCTION = HERE.parents[2]
TOOLS = ROOT / "tools"
LOG = HERE / "portable_regression.log"
RECEIPT = HERE / "portable_regression_receipt.json"
PINS = HERE / "tool_pins.json"
PINNED_INPUTS = (
    ROOT / "build_slus/build.ninja",
    ROOT / "baserom/slus_006.14",
    ROOT / "build_slus/config/slus_modules.json",
    ROOT / "build_slus/config/slus_partitions.json",
)
PRODUCTION_INPUTS = (
    PRODUCTION / "config/slus_modules.json",
    PRODUCTION / "config/slus_partitions.json",
    PRODUCTION / "build_slus/build.ninja",
    PRODUCTION / "build_slus/build/slus_006.14",
    PRODUCTION / "baserom/slus_006.14",
)


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def all_tests(suite):
    for item in suite:
        if isinstance(item, unittest.TestSuite):
            yield from all_tests(item)
        else:
            yield item


def module_paths() -> dict[str, str]:
    wanted = {
        "slus_modules": TOOLS / "build/slus_modules.py",
        "slus_partitions": TOOLS / "build/slus_partitions.py",
        "slus_module_context": TOOLS / "slus_module_context.py",
        "slus_module_evidence": TOOLS / "slus_module_evidence.py",
        "row_db": TOOLS / "row_db.py",
        "fidelity.prove_slus_ownership": TOOLS / "fidelity/prove_slus_ownership.py",
        "fidelity.certify_slus_module": TOOLS / "fidelity/certify_slus_module.py",
        "fidelity.slus_iso": TOOLS / "fidelity/slus_iso.py",
    }
    actual = {}
    for name, expected in wanted.items():
        module = sys.modules.get(name)
        if module is None:
            raise RuntimeError("combined test did not import " + name)
        resolved = Path(module.__file__).resolve()
        if resolved != expected.resolve():
            raise RuntimeError("combined test loaded another copy of " + name + ": " + str(resolved))
        actual[name] = str(resolved.relative_to(ROOT.resolve()))
    return actual


def main() -> dict:
    assert ROOT.is_dir() and TOOLS.is_dir()
    pins = json.loads(PINS.read_text())
    assert len(pins) == 9
    for name, expected in pins.items():
        if sha(ROOT / name) != expected:
            raise RuntimeError("candidate tool pin differs: " + name)
    before = {str(path.relative_to(ROOT)): sha(path) for path in PINNED_INPUTS}
    production_before = {str(path.relative_to(PRODUCTION)): sha(path)
                         for path in PRODUCTION_INPUTS}
    os.chdir(ROOT)
    sys.path[:0] = [str(TOOLS), str(TOOLS / "build"), str(TOOLS / "tests")]
    loader = unittest.TestLoader()
    sections = (
        ("slus", "test_slus_*.py", 165),
        ("configure", "test_configure_slus_*.py", 8),
        ("aspsx_diff", "test_aspsx_diff.py", 14),
    )
    suite = unittest.TestSuite()
    selected = {}
    for label, pattern, expected in sections:
        part = loader.discover(start_dir=str(TOOLS / "tests"), pattern=pattern,
                               top_level_dir=str(TOOLS / "tests"))
        ids = [test.id() for test in all_tests(part)]
        if len(ids) != expected or len(set(ids)) != expected:
            raise RuntimeError(f"{label} discovery differs: {len(ids)} vs {expected}")
        selected[label] = ids
        suite.addTests(part)
    if sum(len(ids) for ids in selected.values()) != 187:
        raise RuntimeError("combined 187-test scope differs")
    imports_before = module_paths()
    stream = io.StringIO()
    result = unittest.TextTestRunner(stream=stream, verbosity=2).run(suite)
    output = stream.getvalue()
    LOG.write_text(output)
    imports_after = module_paths()
    if imports_after != imports_before:
        raise RuntimeError("combined tests changed candidate import identity")
    for name, expected in pins.items():
        if sha(ROOT / name) != expected:
            raise RuntimeError("candidate tool changed during combined tests: " + name)
    after = {str(path.relative_to(ROOT)): sha(path) for path in PINNED_INPUTS}
    if after != before:
        raise RuntimeError("pinned fixture input changed during combined tests")
    production_after = {str(path.relative_to(PRODUCTION)): sha(path)
                        for path in PRODUCTION_INPUTS}
    if production_after != production_before:
        raise RuntimeError("production code/config/build inputs changed during combined tests")
    failed = [test.id() for test, _ in result.failures]
    errors = [test.id() for test, _ in result.errors]
    skipped = [test.id() for test, _ in result.skipped]
    if result.testsRun != 187 or not result.wasSuccessful() or failed or errors or skipped:
        raise RuntimeError("combined tests did not pass: " + output[-4000:])
    record = {
        "status": "PASS", "scope": "single-interpreter candidate regression",
        "total": {"tests": result.testsRun, "passed": result.testsRun,
                  "failed": 0, "errors": 0, "skipped": 0},
        "sections": {name: {"tests": len(ids), "test_ids": ids}
                     for name, ids in selected.items()},
        "new_tests": {"build": 5, "evidence": 9, "total": 14},
        "tool_pins": pins,
        "portable_test_sha256": {name: sha(TOOLS / "tests" / name)
                                 for name in ("test_slus_partition_only_build.py",
                                              "test_slus_partition_only_evidence.py")},
        "resolved_candidate_imports": imports_after,
        "fixture_input_sha256": before,
        "production_input_sha256": production_before,
        "log_sha256": sha(LOG),
        "runner_sha256": sha(Path(__file__)),
        "production_files_written": False,
    }
    RECEIPT.write_text(json.dumps(record, indent=2, sort_keys=True) + "\n")
    return record


if __name__ == "__main__":
    report = main()
    print(json.dumps({"status": report["status"], "total": report["total"],
                      "sections": {name: item["tests"] for name, item in report["sections"].items()}},
                     sort_keys=True))
