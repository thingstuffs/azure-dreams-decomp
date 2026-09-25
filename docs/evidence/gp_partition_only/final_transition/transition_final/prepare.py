#!/usr/bin/env python3
"""Prepare private GP57 + sink retirement + refreshed-control final packet."""

from __future__ import annotations

from collections import Counter
import difflib
import hashlib
import json
from pathlib import Path
import shutil
import subprocess

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
GP57 = ROOT / "work/native_lane/gp_partition_only_tools/transition"
RETIRE = ROOT / "work/native_lane/gp_partition_only_tools/retire_sink"
CONTROLS = ROOT / "work/native_lane/gp_partition_only_tools/controls_refresh"
PAYLOAD = HERE / "payload"
CHECKROOT = HERE / "patch_checkroot"
SUPPCHECK = HERE / "supplemental_checkroot"
CONTROLCHECK = HERE / "controls_checkroot"
INPUTS = HERE / "inputs"
PATCH = HERE / "combined.patch"
INVENTORY = HERE / "inventory.json"
RECEIPT = HERE / "review_receipt.json"
BASELINE = "b4130ec4d7ab9500e86a594aa3606b71fa1611b6"
EXPECTED_GP57_PATCH = "1edc3b64c5d0a359ecfa1774420f2a5585756c57bd467ab053c7c1d522554400"
EXPECTED_RETIRED_PACKAGE = "b89099797be1352d3122455164062d428dcc74529344a919d169e05f663afc52"
PACKAGE = "tools/maspsx/maspsx/__init__.py"
TEST = "tools/maspsx/tests/test_fold_selfinc_la.py"
CLI = "tools/maspsx/maspsx.py"
CONTROL_TARGETS = (
    "tools/fidelity/aspsx_diff.py",
    "tools/fidelity/maspsx_trace.py",
)
CONTROL_HASHES = {
    "tools/fidelity/aspsx_diff.py": "34ea90ca45d1a3753851145b9731a728da3214fc640def9a12592f27731d5338",
    "tools/fidelity/maspsx_trace.py": "cae6004277b9fc15f706a045195e6e96d185c34bdcc422b06393aafffa6ad0c9",
}


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def file_sha(path: Path) -> str:
    return digest(path.read_bytes())


def read_json(path: Path) -> dict:
    return json.loads(path.read_text())


def relative(path: Path) -> str:
    return str(path.relative_to(ROOT))


def reset_private(path: Path) -> None:
    if path.is_symlink():
        raise RuntimeError("unsafe private output link: " + str(path))
    if path.exists():
        shutil.rmtree(path)
    path.mkdir(parents=True)


def check_inputs() -> tuple[dict, dict]:
    gp = read_json(GP57 / "inventory.json")
    retire = read_json(RETIRE / "receipt.json")
    head = subprocess.check_output(["git", "rev-parse", "HEAD"], cwd=ROOT, text=True).strip()
    if head != BASELINE:
        changed = subprocess.check_output(
            ["git", "diff", "--name-only", BASELINE, head], cwd=ROOT, text=True).splitlines()
        if not changed or any(not name.startswith("docs/") for name in changed):
            raise RuntimeError("code changed since reviewed baseline")
    if (gp["status"] != "PRIVATE_REVIEW_READY" or gp["production_applied"]
            or gp["total_changed_or_new_files"] != 57
            or gp["inputs"]["code_baseline_commit"] != BASELINE
            or gp["patch_sha256"] != EXPECTED_GP57_PATCH
            or file_sha(GP57 / "transition.patch") != EXPECTED_GP57_PATCH
            or not gp["patch_replay_exact"]):
        raise RuntimeError("frozen GP57 packet differs")
    if (retire["status"] != "PRIVATE_PASS_RETIREMENT_PROBE_PASS"
            or retire["candidate_package_sha256"] != EXPECTED_RETIRED_PACKAGE
            or retire["candidate_cli_sha256"] != gp["inputs"]["guarded_assembler_sha256"][CLI]
            or not retire["former_consumer"]["guarded_retired_and_final_object_byte_equal"]
            or retire["unit_tests"]["tests"] != 418
            or retire["unit_tests"]["failures"] or retire["unit_tests"]["errors"]):
        raise RuntimeError("sink retirement evidence differs")
    supplement = retire["supplemental_patch"]
    if (supplement["files"] != [PACKAGE, TEST]
            or not supplement["replay_exact"]
            or file_sha(RETIRE / "supplemental.patch") != supplement["sha256"]
            or file_sha(RETIRE / "candidate/maspsx/__init__.py") != EXPECTED_RETIRED_PACKAGE
            or file_sha(RETIRE / "test_fixture/tools/maspsx/tests/test_fold_selfinc_la.py")
            != supplement["retired_test_after_sha256"]):
        raise RuntimeError("two-file sink retirement supplement differs")
    if file_sha(GP57 / "payload" / CLI) != retire["candidate_cli_sha256"]:
        raise RuntimeError("retired candidate CLI differs from GP57")
    if file_sha(GP57 / "payload" / PACKAGE) != retire["guarded_package_sha256"]:
        raise RuntimeError("supplement does not start from GP57 guarded package")
    if file_sha(ROOT / TEST) != supplement["retired_test_before_sha256"]:
        raise RuntimeError("synthetic test production baseline differs")
    for record in gp["files"]:
        path = ROOT / record["target"]
        current = path.read_bytes() if path.is_file() else None
        if (digest(current) if current is not None else None) != record["before_sha256"]:
            raise RuntimeError("GP57 production before-hash differs: " + record["target"])
        if current is not None:
            base = subprocess.check_output(["git", "show", BASELINE + ":" + record["target"]], cwd=ROOT)
            if base != current:
                raise RuntimeError("GP57 target differs from reviewed code baseline: " + record["target"])
        if file_sha(GP57 / "payload" / record["target"]) != record["after_sha256"]:
            raise RuntimeError("GP57 payload changed: " + record["target"])
    if subprocess.check_output(["git", "show", BASELINE + ":" + TEST], cwd=ROOT) != (ROOT / TEST).read_bytes():
        raise RuntimeError("retirement synthetic test differs from reviewed code baseline")
    return gp, retire


def check_controls() -> tuple[dict, dict]:
    review = read_json(CONTROLS / "root_review.json")
    run = read_json(CONTROLS / "final_run_receipt.json")
    setup = read_json(CONTROLS / "prepare_final_receipt.json")
    if (review.get("status") != "REVIEWED" or review.get("controls") != 60
            or review.get("skips") != 0 or review.get("production_changed")
            or set(review.get("files", {})) != set(CONTROL_TARGETS)
            or review["control_receipt_sha256"] != file_sha(CONTROLS / "final_run_receipt.json")
            or review["controls_log_sha256"] != file_sha(CONTROLS / "final_run.log")):
        raise RuntimeError("root-reviewed refreshed controls differ")
    if (run.get("status") != "PASS" or run.get("controls_return") != 0
            or run.get("passed_controls") != 60 or run.get("failed_controls")
            or not run.get("production_unchanged")
            or run.get("log_sha256") != file_sha(CONTROLS / "final_run.log")
            or run.get("prepare_receipt_sha256") != file_sha(CONTROLS / "prepare_final_receipt.json")
            or setup.get("status") != "PREPARED"):
        raise RuntimeError("actual 60-control run differs")
    if any(line.startswith("SKIP  ") for line in (CONTROLS / "final_run.log").read_text().splitlines()):
        raise RuntimeError("refreshed controls have skipped cases")
    for target in CONTROL_TARGETS:
        name = Path(target).name
        record = review["files"][target]
        if (file_sha(ROOT / target) != record["production_before_sha256"]
                or subprocess.check_output(["git", "show", BASELINE + ":" + target], cwd=ROOT)
                != (ROOT / target).read_bytes()
                or file_sha(CONTROLS / target) != CONTROL_HASHES[target]
                or record["after_sha256"] != CONTROL_HASHES[target]
                or setup["tool_pins"][name]["after"] != CONTROL_HASHES[target]
                or run["tool_pins"][name]["after"] != CONTROL_HASHES[target]
                or not record["measurement_executable_ast_equal"]):
            raise RuntimeError("control tool source or AST review differs: " + target)
    return review, run


def check_supplement_replay(retire: dict) -> None:
    reset_private(SUPPCHECK)
    for target, source in (
            (PACKAGE, GP57 / "payload" / PACKAGE),
            (TEST, ROOT / TEST)):
        dest = SUPPCHECK / target
        dest.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(source, dest)
    applied = subprocess.run(
        ["patch", "-p1", "--batch", "-d", str(SUPPCHECK), "-i", str(RETIRE / "supplemental.patch")],
        capture_output=True, text=True)
    (HERE / "supplemental_apply.log").write_text(applied.stdout + applied.stderr)
    if applied.returncode:
        raise RuntimeError("supplemental patch replay failed: " + applied.stderr)
    for target, expected in (
            (PACKAGE, RETIRE / "candidate/maspsx/__init__.py"),
            (TEST, RETIRE / "test_fixture/tools/maspsx/tests/test_fold_selfinc_la.py")):
        if (SUPPCHECK / target).read_bytes() != expected.read_bytes():
            raise RuntimeError("supplemental patch replay bytes differ: " + target)


def check_controls_replay() -> None:
    reset_private(CONTROLCHECK)
    for target in CONTROL_TARGETS:
        dest = CONTROLCHECK / target
        dest.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(ROOT / target, dest)
    applied = subprocess.run(
        ["patch", "-p1", "--batch", "-d", str(CONTROLCHECK),
         "-i", str(CONTROLS / "controls.patch")], capture_output=True, text=True)
    (HERE / "controls_apply.log").write_text(applied.stdout + applied.stderr)
    if applied.returncode:
        raise RuntimeError("controls patch replay failed: " + applied.stderr)
    for target in CONTROL_TARGETS:
        if (CONTROLCHECK / target).read_bytes() != (CONTROLS / target).read_bytes():
            raise RuntimeError("controls patch replay bytes differ: " + target)


def main() -> dict:
    gp, retire = check_inputs()
    controls_review, controls_run = check_controls()
    check_supplement_replay(retire)
    check_controls_replay()
    for directory in (PAYLOAD, CHECKROOT, INPUTS):
        reset_private(directory)
    source_files = {r["target"]: GP57 / "payload" / r["target"] for r in gp["files"]}
    source_files[PACKAGE] = RETIRE / "candidate/maspsx/__init__.py"
    source_files[TEST] = RETIRE / "test_fixture/tools/maspsx/tests/test_fold_selfinc_la.py"
    for target in CONTROL_TARGETS:
        source_files[target] = CONTROLS / target
    if len(source_files) != 60:
        raise RuntimeError("final target set is not exactly 60 files")
    original_records = {r["target"]: r for r in gp["files"]}
    records = []
    diffs = []
    for target in sorted(source_files):
        old_path = ROOT / target
        old = old_path.read_bytes() if old_path.is_file() else b""
        new = source_files[target].read_bytes()
        if old == new or not new.endswith(b"\n") or (old and not old.endswith(b"\n")):
            raise RuntimeError("empty or non-newline final delta: " + target)
        payload = PAYLOAD / target
        payload.parent.mkdir(parents=True, exist_ok=True)
        payload.write_bytes(new)
        baseline = CHECKROOT / target
        baseline.parent.mkdir(parents=True, exist_ok=True)
        if old:
            baseline.write_bytes(old)
        prior = original_records.get(target)
        if prior:
            if (prior["before_sha256"] != (digest(old) if old else None)
                    or prior["state"] != ("changed" if old else "new")):
                raise RuntimeError("GP57 target baseline differs: " + target)
            category = prior["category"]
            context = {key: prior[key] for key in ("role", "module", "modules", "functions", "data_symbols", "refinement", "canonical_repair")
                       if key in prior}
        else:
            if target == TEST:
                if digest(old) != retire["supplemental_patch"]["retired_test_before_sha256"]:
                    raise RuntimeError("retirement synthetic test baseline differs")
                category = "assembler_test"
            elif target in CONTROL_TARGETS:
                if digest(old) != controls_review["files"][target]["production_before_sha256"]:
                    raise RuntimeError("control tool production baseline differs: " + target)
                category = "validation_controls"
            else:
                raise RuntimeError("unreviewed additional target: " + target)
            context = {}
        delta = "".join(difflib.unified_diff(
            old.decode().splitlines(keepends=True), new.decode().splitlines(keepends=True),
            fromfile="a/" + target if old else "/dev/null", tofile="b/" + target, n=3))
        if not delta:
            raise RuntimeError("empty combined diff: " + target)
        diffs.append(delta)
        records.append({
            "target": target, "category": category, "state": "changed" if old else "new",
            "source": relative(source_files[target]), "before_sha256": digest(old) if old else None,
            "after_sha256": digest(new), "before_bytes": len(old), "after_bytes": len(new),
            "sink_retirement_override": target in (PACKAGE, TEST),
            "controls_refresh_override": target in CONTROL_TARGETS, **context,
        })
    PATCH.write_text("".join(diffs))
    gitcheck = subprocess.run(["git", "apply", "--check", str(PATCH)], cwd=ROOT,
                              capture_output=True, text=True)
    (HERE / "git_apply_check.log").write_text(gitcheck.stdout + gitcheck.stderr)
    if gitcheck.returncode:
        raise RuntimeError("git apply --check failed: " + gitcheck.stderr[-3000:])
    replay = subprocess.run(["patch", "-p1", "--batch", "-d", str(CHECKROOT), "-i", str(PATCH)],
                            capture_output=True, text=True)
    (HERE / "patch_replay.log").write_text(replay.stdout + replay.stderr)
    if replay.returncode:
        raise RuntimeError("combined private patch replay failed: " + replay.stderr[-3000:])
    if any((CHECKROOT / r["target"]).read_bytes() != (PAYLOAD / r["target"]).read_bytes()
           for r in records):
        raise RuntimeError("combined private patch replay bytes differ")
    for name, source in (
            ("gp57_inventory.json", GP57 / "inventory.json"),
            ("retirement_receipt.json", RETIRE / "receipt.json"),
            ("retirement_supplemental.patch", RETIRE / "supplemental.patch"),
            ("retirement_report.md", RETIRE / "REPORT.md"),
            ("combined_build_receipt.json", RETIRE / "combined_receipt.json"),
            ("overlay_gate_receipt.json", RETIRE / "overlay_gate/receipt.json"),
            ("controls.patch", CONTROLS / "controls.patch"),
            ("controls_root_review.json", CONTROLS / "root_review.json"),
            ("controls_prepare_final.py", CONTROLS / "prepare_final.py"),
            ("controls_run_final.py", CONTROLS / "run_final.py"),
            ("controls_prepare_final_receipt.json", CONTROLS / "prepare_final_receipt.json"),
            ("controls_final_run_receipt.json", CONTROLS / "final_run_receipt.json"),
            ("controls_final_run.log", CONTROLS / "final_run.log")):
        shutil.copyfile(source, INPUTS / name)
        if file_sha(source) != file_sha(INPUTS / name):
            raise RuntimeError("packaged evidence bytes differ: " + name)
    category_counts = dict(Counter(r["category"] for r in records))
    if category_counts != {**gp["category_counts"], "assembler_test": 8,
                           "validation_controls": 2}:
        raise RuntimeError("combined categories differ: " + repr(category_counts))
    combined = read_json(RETIRE / "combined_receipt.json")
    overlay = read_json(RETIRE / "overlay_gate/receipt.json")
    if (combined.get("status") != "PASS" or combined.get("owners") != 33
            or combined.get("physical_objects_rebuilt") != 860
            or not combined.get("full_image_retail_exact")
            or not combined.get("all_objects_equal_frozen_gp57")
            or combined.get("retired_package_sha256") != EXPECTED_RETIRED_PACKAGE
            or overlay.get("gate_exit_code") != 0
            or overlay.get("journal", {}).get("windows") != 2175
            or overlay.get("journal", {}).get("latest_results") != {"MATCH": 2175}):
        raise RuntimeError("linked combined-build or overlay evidence differs")
    inventory = {
        "status": "PRIVATE_COMBINED_PACKET_READY", "production_applied": False,
        "code_baseline_commit": BASELINE, "current_docs_only_commit":
            subprocess.check_output(["git", "rev-parse", "HEAD"], cwd=ROOT, text=True).strip(),
        "base_gp57_patch_sha256": file_sha(GP57 / "transition.patch"),
        "base_gp57_inventory_sha256": file_sha(GP57 / "inventory.json"),
        "supplemental_patch_sha256": file_sha(RETIRE / "supplemental.patch"),
        "retirement_receipt_sha256": file_sha(RETIRE / "receipt.json"),
        "controls_patch_sha256": file_sha(CONTROLS / "controls.patch"),
        "controls_root_review_sha256": file_sha(CONTROLS / "root_review.json"),
        "controls_run_receipt_sha256": file_sha(CONTROLS / "final_run_receipt.json"),
        "controls_run_log_sha256": file_sha(CONTROLS / "final_run.log"),
        "combined_build_receipt_sha256": file_sha(RETIRE / "combined_receipt.json"),
        "overlay_gate_receipt_sha256": file_sha(RETIRE / "overlay_gate/receipt.json"),
        "guarded_cli_sha256": file_sha(PAYLOAD / CLI),
        "retired_package_sha256": file_sha(PAYLOAD / PACKAGE),
        "retired_synthetic_test_sha256": file_sha(PAYLOAD / TEST),
        "files": records, "category_counts": category_counts,
        "total_changed_or_new_files": len(records), "patch_sha256": file_sha(PATCH),
        "payload_manifest_sha256": digest("".join(
            r["target"] + "\0" + r["after_sha256"] + "\n" for r in records).encode()),
        "git_apply_check": "PASS", "private_patch_replay_exact": True,
        "supplemental_replay_exact": True, "controls_replay_exact": True,
        "linked_retired_build_and_ownership_gate": "PASS",
        "linked_overlay_windows_match": 2175,
        "linked_controls_passed_without_skips": 60,
        "final_packet_ownership_audit": "PENDING_SEPARATE_EVIDENCE",
        "expected_final_ownership_receipt": "work/native_lane/gp_partition_only_tools/transition_final/final_ownership_audit.json",
    }
    INVENTORY.write_text(json.dumps(inventory, indent=2, sort_keys=True) + "\n")
    review = {
        "status": "PACKAGED_PENDING_FINAL_OWNERSHIP_AUDIT", "production_applied": False,
        "patch_sha256": inventory["patch_sha256"],
        "inventory_sha256": file_sha(INVENTORY),
        "payload_manifest_sha256": inventory["payload_manifest_sha256"],
        "files": len(records), "git_apply_check": True,
        "patch_replay_exact": True, "supplemental_replay_exact": True,
        "controls_replay_exact": True,
        "before_hashes_match_gp57_and_production": True,
        "guarded_cli_unchanged": inventory["guarded_cli_sha256"] == retire["candidate_cli_sha256"],
        "retired_package_sha256": inventory["retired_package_sha256"],
        "retired_test_sha256": inventory["retired_synthetic_test_sha256"],
        "retirement_unit_tests": retire["unit_tests"]["tests"],
        "former_consumer_object_byte_equal": retire["former_consumer"]["guarded_retired_and_final_object_byte_equal"],
        "controls_passed_without_skips": controls_run["passed_controls"],
        "linked_retired_build_and_ownership_gate": "PASS",
        "linked_overlay_windows_match": 2175,
        "final_packet_ownership_audit": "PENDING",
        "expected_final_ownership_receipt": inventory["expected_final_ownership_receipt"],
    }
    RECEIPT.write_text(json.dumps(review, indent=2, sort_keys=True) + "\n")
    return review


if __name__ == "__main__":
    print(json.dumps(main(), sort_keys=True))
