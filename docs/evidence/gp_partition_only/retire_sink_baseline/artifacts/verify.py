#!/usr/bin/env python3
"""Reproduce the retired-pass private tests and exact final-recipe consumer object."""

from __future__ import annotations

import difflib
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
BASE = ROOT / "work/native_lane/selfinc_local_guard/candidate"
MIGRATED = ROOT / "work/native_lane/gp_partition_only_tools/assembler_tests_candidate"
FINAL = ROOT / "work/native_lane/gp_partition_only_tools/full_ownership/fixture"
PAYLOAD = ROOT / "work/native_lane/gp_partition_only_tools/transition/payload"
PYTHON = ROOT / ".venv/bin/python"
CAND = HERE / "candidate"
TEST = HERE / "test_fixture"
TEST_NAME = "test_fold_selfinc_la.py"
ROW_ID = "slus/w_8004AB7C"


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def write_json(path: Path, value: dict) -> None:
    path.write_text(json.dumps(value, indent=2, sort_keys=True) + "\n")


def fixture_inputs() -> dict:
    paths = {
        "guarded_cli": BASE / "maspsx.py",
        "guarded_package": BASE / "maspsx/__init__.py",
        "candidate_cli": CAND / "maspsx.py",
        "candidate_package": CAND / "maspsx/__init__.py",
        "final_source": FINAL / "src/slus/w_8004AB7C.c",
        "final_build_source": FINAL / "build_slus/src/w_8004AB7C.c",
        "final_ninja": FINAL / "build_slus/build.ninja",
        "final_pinned_ninja": FINAL / "ledger/splits/slus.build.ninja",
        "final_registry": FINAL / "ledger/rows.jsonl",
        "final_object": FINAL / "build_slus/build/src/w_8004AB7C.o",
        "final_57_pins": ROOT / "work/native_lane/gp_partition_only_tools/full_ownership/input_pins.json",
        "migrated_test_base": MIGRATED / "tools/maspsx/tests" / TEST_NAME,
        "candidate_test": TEST / "tools/maspsx/tests" / TEST_NAME,
        "census_summary": ROOT / "work/native_lane/gp_partition_only_tools/census_report/summary.json",
    }
    return {name: sha(path) for name, path in paths.items()}


def production_inputs() -> dict:
    names = ("tools/maspsx/maspsx.py", "tools/maspsx/maspsx/__init__.py",
             "tools/maspsx/tests/test_fold_selfinc_la.py", "src/slus/w_8004AB7C.c",
             "build_slus/build/src/w_8004AB7C.o")
    return {name: sha(ROOT / name) for name in names}


def supplemental_patch() -> dict:
    test_old = (MIGRATED / "tools/maspsx/tests" / TEST_NAME).read_text()
    test_new = (TEST / "tools/maspsx/tests" / TEST_NAME).read_text()
    if test_old == test_new:
        raise RuntimeError("synthetic retirement regression was not migrated")
    test_patch = "".join(difflib.unified_diff(test_old.splitlines(True), test_new.splitlines(True),
        fromfile="a/tools/maspsx/tests/" + TEST_NAME,
        tofile="b/tools/maspsx/tests/" + TEST_NAME))
    patch = (HERE / "removal.patch").read_text() + test_patch
    (HERE / "supplemental.patch").write_text(patch)
    check = HERE / "patch_check"
    if check.exists():
        shutil.rmtree(check)
    old_package = BASE / "maspsx/__init__.py"
    for source, target in ((old_package, check / "tools/maspsx/maspsx/__init__.py"),
                           (MIGRATED / "tools/maspsx/tests" / TEST_NAME,
                            check / "tools/maspsx/tests" / TEST_NAME)):
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(source, target)
    result = subprocess.run(["patch", "-p1", "--batch", "--forward", "-i",
                             str(HERE / "supplemental.patch")], cwd=check,
                            stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    (HERE / "patch_replay.log").write_text(result.stdout)
    if result.returncode:
        raise RuntimeError("private two-file patch replay failed: " + result.stdout[-1000:])
    if sha(check / "tools/maspsx/maspsx/__init__.py") != sha(CAND / "maspsx/__init__.py"):
        raise RuntimeError("replayed package differs from candidate")
    if sha(check / "tools/maspsx/tests" / TEST_NAME) != sha(TEST / "tools/maspsx/tests" / TEST_NAME):
        raise RuntimeError("replayed test differs from private migrated test")
    return {"path": str((HERE / "supplemental.patch").relative_to(ROOT)),
            "sha256": sha(HERE / "supplemental.patch"),
            "files": ["tools/maspsx/maspsx/__init__.py",
                      "tools/maspsx/tests/" + TEST_NAME],
            "replay_exact": True,
            "retired_test_before_sha256": sha(MIGRATED / "tools/maspsx/tests" / TEST_NAME),
            "retired_test_after_sha256": sha(TEST / "tools/maspsx/tests" / TEST_NAME)}


def test_suite() -> dict:
    command = [str(PYTHON), "-m", "unittest", "discover",
               "-s", str(TEST / "tools/maspsx/tests"), "-t", str(TEST)]
    env = dict(os.environ)
    env["PYTHONDONTWRITEBYTECODE"] = "1"
    env["PYTHONPATH"] = str(CAND)
    env.pop("AZURE_MASPSX", None)
    env.pop("AZURE_MASPSX_COMPANION", None)
    with (HERE / "unit.log").open("w") as log:
        result = subprocess.run(command, cwd=ROOT, env=env, stdout=log, stderr=subprocess.STDOUT)
    content = (HERE / "unit.log").read_text()
    match = re.search(r"Ran (\d+) tests in", content)
    if result.returncode != 0 or not match or int(match.group(1)) != 418 or not content.rstrip().endswith("OK"):
        raise RuntimeError("retired candidate migrated tests failed: " + content[-1400:])
    if not (TEST / "tools/maspsx/maspsx.py").is_symlink() or not (
            TEST / "toolchain/maspsx/maspsx.py").is_symlink():
        raise RuntimeError("private test CLI paths are not bound to candidate")
    for name in ("tools/maspsx/maspsx.py", "toolchain/maspsx/maspsx.py"):
        if (TEST / name).resolve() != (CAND / "maspsx.py").resolve():
            raise RuntimeError("test CLI resolves outside candidate: " + name)
    return {"tests": int(match.group(1)), "failures": 0, "errors": 0,
            "log_sha256": sha(HERE / "unit.log"),
            "candidate_cli_and_package_bound": True,
            "command": " ".join(command)}


def consumer() -> dict:
    rows = [json.loads(line) for line in (FINAL / "ledger/rows.jsonl").read_text().splitlines() if line]
    row = next(x for x in rows if x["id"] == ROW_ID)
    if row["cell"] != "2.7.2-cdk" or row["flags"] != "" or row.get("row_asflags") not in (None, ""):
        raise RuntimeError("former consumer registered recipe differs")
    if (FINAL / "build_slus/build.ninja").read_bytes() != (FINAL / "ledger/splits/slus.build.ninja").read_bytes():
        raise RuntimeError("final fixture build graph is not the pinned recipe")
    if (FINAL / "src/slus/w_8004AB7C.c").read_bytes() != (
            PAYLOAD / "src/slus/w_8004AB7C.c").read_bytes():
        raise RuntimeError("former consumer is not the frozen final source")
    ninja = (FINAL / "build_slus/build.ninja").read_text()
    edge = re.search(r"(?m)^build build/src/w_8004AB7C\.o: cc src/w_8004AB7C\.c[^\n]*\n"
                     r"  ccver = ([^\n]*)\n  ccflags = ([^\n]*)\n  asflags = ([^\n]*)", ninja)
    if not edge or edge.groups() != ("2.7.2-cdk", "", ""):
        raise RuntimeError("former consumer Ninja edge differs from registered recipe")
    reference = FINAL / "build_slus/build/src/w_8004AB7C.o"
    object_hashes = {}
    for name, cli in (("guarded", BASE / "maspsx.py"), ("retired", CAND / "maspsx.py")):
        out = HERE / ("former_" + name + ".o")
        env = dict(os.environ)
        env["AZURE_MASPSX"] = str(cli)
        env.pop("AZURE_MASPSX_COMPANION", None)
        command = ["bash", "tools/cc.sh", "src/w_8004AB7C.c", str(out),
                   "2.7.2-cdk", "", ""]
        with (HERE / ("former_" + name + ".log")).open("w") as log:
            result = subprocess.run(command, cwd=FINAL / "build_slus", env=env,
                                    stdout=log, stderr=subprocess.STDOUT)
        if result.returncode or not out.is_file():
            raise RuntimeError("former consumer " + name + " compile failed")
        object_hashes[name] = sha(out)
    object_hashes["final_fixture"] = sha(reference)
    if len(set(object_hashes.values())) != 1:
        raise RuntimeError("former consumer object differs at final recipe: " + repr(object_hashes))
    return {"row": ROW_ID, "recipe": "2.7.2-cdk", "flags": "", "asflags": "",
            "source_sha256": sha(FINAL / "src/slus/w_8004AB7C.c"),
            "object_sha256": object_hashes["retired"],
            "guarded_retired_and_final_object_byte_equal": True,
            "object_bytes": reference.stat().st_size,
            "retail_exact_fixture_receipt_sha256": sha(ROOT / "work/native_lane/gp_partition_only_tools/full_ownership/receipt.json")}


def main() -> None:
    start_inputs = fixture_inputs()
    start_prod = production_inputs()
    prep = json.loads((HERE / "prepare_receipt.json").read_text())
    if prep["status"] != "PREPARED" or prep["candidate_cli_sha256"] != start_inputs["candidate_cli"] or (
            prep["candidate_package_sha256"] != start_inputs["candidate_package"]):
        raise RuntimeError("prepared candidate bytes changed")
    census = json.loads((ROOT / "work/native_lane/gp_partition_only_tools/census_report/summary.json").read_text())
    probe = census["pass_probe"]["_sink_call_separated_la"]
    if probe != {"fired_rows": [], "fired_units": [], "required_rows": [], "required_units": []}:
        raise RuntimeError("full census no longer reports zero sink uses")
    patch = supplemental_patch()
    tests = test_suite()
    former = consumer()
    if fixture_inputs() != start_inputs or production_inputs() != start_prod:
        raise RuntimeError("frozen fixture or production inputs changed during verification")
    receipt = {"schema": 1, "status": "PRIVATE_PASS_RETIREMENT_PROBE_PASS",
        "scope": "no production change, no full global gate, no pass retirement activated",
        "census_rows": census["rows"], "census_summary_sha256": start_inputs["census_summary"],
        "pass_probe": probe, "candidate_cli_sha256": start_inputs["candidate_cli"],
        "candidate_package_sha256": start_inputs["candidate_package"],
        "guarded_cli_sha256": start_inputs["guarded_cli"],
        "guarded_package_sha256": start_inputs["guarded_package"],
        "supplemental_patch": patch, "unit_tests": tests, "former_consumer": former,
        "input_hashes_before_after_equal": True, "production_inputs_before_after_equal": True,
        "input_hashes": start_inputs, "production_inputs": start_prod}
    write_json(HERE / "receipt.json", receipt)
    print(json.dumps({k: receipt[k] for k in ("status", "candidate_package_sha256",
                                      "unit_tests", "former_consumer")}, indent=2))


if __name__ == "__main__":
    main()
