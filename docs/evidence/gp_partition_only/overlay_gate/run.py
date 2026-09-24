#!/usr/bin/env python3
"""Exact guarded-candidate unit and isolated full overlay-window gate."""

from __future__ import annotations

import hashlib
import json
import os
import re
import subprocess
import sys
import time
from collections import Counter
from pathlib import Path


HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
CANDIDATE = ROOT / "work/native_lane/selfinc_local_guard/candidate"
GENERIC_BEFORE = ROOT / "work/fidelity/gp_probe279/candidate"
CLI = CANDIDATE / "maspsx.py"
PACKAGE = CANDIDATE / "maspsx/__init__.py"
EXP = "guarded_20260924_sol"
BUILD = ROOT / f"build_ovl_{EXP}"
PYTHON = Path("<reference-repo>/.venv/bin/python")
EXPECTED = {
    "cli": "d3e6ec7d120abe00f963c82258dfdeb0e228774adce646177525f1dbed925caf",
    "package": "28e45bbcf00fc90dc0645250f233b73f96ad11d06a2f8230ce533fc2fafbbfbe",
}


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def candidate_hashes() -> dict[str, str]:
    return {"cli": sha(CLI.read_bytes()), "package": sha(PACKAGE.read_bytes())}


def tracked_snapshot() -> dict[str, object]:
    """Hash current tracked production inputs without traversing work/ or builds."""
    names = subprocess.check_output(
        ["git", "ls-files", "-z", "--", "src", "config", "tools", "include", "ledger/splits"],
        cwd=ROOT,
    ).split(b"\0")
    digest = hashlib.sha256()
    counts = Counter()
    for raw_name in sorted(x for x in names if x):
        name = os.fsdecode(raw_name)
        path = ROOT / name
        if path.is_symlink():
            content = b"link:" + os.fsencode(os.readlink(path))
        elif path.is_file():
            content = path.read_bytes()
        else:
            content = b"missing"
        digest.update(raw_name + b"\0" + sha(content).encode() + b"\0")
        counts[name.split("/", 1)[0]] += 1
    return {"sha256": digest.hexdigest(), "tracked_files": sum(counts.values()),
            "tracked_by_root": dict(sorted(counts.items()))}


def run_to_log(command: list[str], path: Path, env: dict[str, str]) -> int:
    with path.open("w") as log:
        log.write("command: " + " ".join(command) + "\n")
        log.flush()
        result = subprocess.run(command, cwd=ROOT, env=env,
                                stdout=log, stderr=subprocess.STDOUT)
    return result.returncode


def journal_summary() -> dict[str, object]:
    journal = HERE / "journal.jsonl"
    if not journal.exists():
        return {"lines": 0, "windows": 0, "latest_results": {}}
    latest = {}
    lines = 0
    for line in journal.read_text().splitlines():
        if not line.strip():
            continue
        rec = json.loads(line)
        latest[rec["window"]] = rec
        lines += 1
    return {"lines": lines, "windows": len(latest),
            "latest_results": dict(sorted(Counter(x["result"] for x in latest.values()).items())),
            "all_latest_match": bool(latest) and all(x["result"] == "MATCH" for x in latest.values()),
            "journal_sha256": sha(journal.read_bytes())}


def write(receipt: dict[str, object]) -> None:
    (HERE / "receipt.json").write_text(json.dumps(receipt, indent=2) + "\n")


def failed_tests(path: Path) -> list[str]:
    return sorted(set(re.findall(r"^(?:FAIL|ERROR): (.*)$", path.read_text(), re.M)))


def main() -> int:
    if BUILD.exists() or BUILD.is_symlink():
        raise RuntimeError(f"isolated EXP root already exists: {BUILD}")
    if (HERE / "journal.jsonl").exists():
        raise RuntimeError("private journal already exists; refusing stale append")
    if not PYTHON.is_file():
        raise RuntimeError(f"missing fidelity virtualenv: {PYTHON}")
    receipt: dict[str, object] = {
        "candidate_paths": {"cli": str(CLI.relative_to(ROOT)),
                            "package": str(PACKAGE.relative_to(ROOT))},
        "expected_candidate_sha256": EXPECTED,
        "candidate_before_sha256": candidate_hashes(),
        "production_before": tracked_snapshot(),
        "exp": EXP,
        "build_root": str(BUILD.relative_to(ROOT)),
        "start_utc": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()),
    }
    if receipt["candidate_before_sha256"] != EXPECTED:
        raise RuntimeError("candidate hash changed before gate")
    write(receipt)
    try:
        env = dict(os.environ)
        env["PYTHONPATH"] = str(CANDIDATE)
        print("candidate import and unit suite", flush=True)
        receipt["import_exit_code"] = run_to_log(
            [str(PYTHON), "-c",
             "import maspsx; print(maspsx.__file__); "
             "assert maspsx.__file__.startswith(%r)" % str(CANDIDATE)],
            HERE / "unit_import.log", env)
        if receipt["import_exit_code"] != 0:
            return 1
        receipt["unit_exit_code"] = run_to_log(
            [str(PYTHON), "-m", "unittest", "discover", "-s", "tools/maspsx/tests", "-t", "."],
            HERE / "unit.log", env)
        before_env = dict(env, PYTHONPATH=str(GENERIC_BEFORE))
        receipt["generic_before_unit_exit_code"] = run_to_log(
            [str(PYTHON), "-m", "unittest", "discover", "-s", "tools/maspsx/tests", "-t", "."],
            HERE / "unit_before.log", before_env)
        receipt["candidate_failed_tests"] = failed_tests(HERE / "unit.log")
        receipt["generic_before_failed_tests"] = failed_tests(HERE / "unit_before.log")
        receipt["unit_failure_sets_equal"] = (
            receipt["candidate_failed_tests"] == receipt["generic_before_failed_tests"])
        receipt["selfinc_unit_exit_code"] = run_to_log(
            [str(PYTHON), "-m", "unittest", "-v", "tools.maspsx.tests.test_fold_selfinc_la"],
            HERE / "unit_selfinc.log", env)
        write(receipt)

        print("isolated overlay root setup", flush=True)
        setup_env = dict(os.environ)
        setup_env.update(EXP=EXP, SRCROOT=str(ROOT / "src"))
        receipt["setup_exit_code"] = run_to_log(
            ["bash", "tools/build/mk_ovl_root.sh"], HERE / "setup.log", setup_env)
        write(receipt)
        if receipt["setup_exit_code"] != 0:
            return 1

        print("forced full overlay gate with four workers", flush=True)
        gate_env = dict(os.environ)
        gate_env.update(AZURE_MASPSX=str(CLI), AZURE_MASPSX_COMPANION=str(CLI),
                        GATE_BUILD_ROOT=BUILD.name, GATE_JOURNAL=str(HERE / "journal.jsonl"))
        receipt["gate_env_binding"] = {k: gate_env[k] for k in
                                       ("AZURE_MASPSX", "AZURE_MASPSX_COMPANION",
                                        "GATE_BUILD_ROOT", "GATE_JOURNAL")}
        write(receipt)
        receipt["gate_exit_code"] = run_to_log(
            ["python3", "tools/build/gate_all.py", "--all", "--workers", "4"],
            HERE / "gate.log", gate_env)
        receipt["journal"] = journal_summary()
        return int(receipt["gate_exit_code"])
    finally:
        receipt["candidate_after_sha256"] = candidate_hashes()
        receipt["production_after"] = tracked_snapshot()
        receipt["candidate_unchanged"] = receipt["candidate_after_sha256"] == receipt["candidate_before_sha256"]
        receipt["production_inputs_unchanged"] = receipt["production_after"] == receipt["production_before"]
        receipt["end_utc"] = time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())
        write(receipt)


if __name__ == "__main__":
    sys.exit(main())
