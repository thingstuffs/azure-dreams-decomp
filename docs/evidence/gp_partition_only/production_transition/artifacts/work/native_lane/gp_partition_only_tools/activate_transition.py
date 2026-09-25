#!/usr/bin/env python3
"""Guarded production activation for the reviewed GP/SLUS transition.

This is deliberately opt-in. It applies the exact patch and leaves every artifact
in place on failure; it never commits or rolls production back.
"""
from __future__ import annotations

import argparse
import fcntl
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import time

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
TRANSITION = HERE / "transition"
PATCH = TRANSITION / "transition.patch"
INVENTORY = TRANSITION / "inventory.json"
REVIEW = HERE / "root_transition_review.json"
FULL_PROOF = HERE / "full_ownership/receipt.json"
FULL_OWNERSHIP = HERE / "full_ownership/ownership_receipt.json"
OVERLAY_PROOF = HERE / "overlay_gate/receipt.json"
PROOF_INPUT_PINS = HERE / "full_ownership/input_pins.json"
MODEL_ROW = "slus/konami_runtime_w_80033D54"
PLACEMENTS = ("list_cursor_e0", "runtime_directory")


def sha_bytes(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def sha(path: Path) -> str:
    return sha_bytes(path.read_bytes())


def read_json(path: Path):
    return json.loads(path.read_text())


def write_json(path: Path, value: dict) -> None:
    temp = path.with_suffix(path.suffix + ".tmp")
    temp.write_text(json.dumps(value, indent=2, sort_keys=True) + "\n")
    temp.replace(path)


def command(args: list[str], *, cwd: Path = ROOT, env: dict | None = None,
            log: Path | None = None) -> subprocess.CompletedProcess:
    if log is None:
        result = subprocess.run(args, cwd=cwd, env=env, text=True,
                                stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        output = result.stdout
    else:
        with log.open("w") as stream:
            stream.write("command: " + " ".join(args) + "\n")
            stream.flush()
            result = subprocess.run(args, cwd=cwd, env=env, text=True,
                                    stdout=stream, stderr=subprocess.STDOUT)
        output = log.read_text(errors="replace")
    if result.returncode:
        tail = output[-5000:]
        raise RuntimeError(f"command failed ({result.returncode}): {' '.join(args)}\n{tail}")
    return result


def logged_status(args: list[str], path: Path, env: dict[str, str]) -> int:
    with path.open("w") as stream:
        stream.write("command: " + " ".join(args) + "\n")
        stream.flush()
        result = subprocess.run(args, cwd=ROOT, env=env, text=True,
                                stdout=stream, stderr=subprocess.STDOUT)
    return result.returncode


def failed_tests(path: Path) -> list[str]:
    return sorted(set(re.findall(r"^(?:FAIL|ERROR): (.*)$", path.read_text(errors="replace"), re.M)))


def base_env() -> dict[str, str]:
    env = dict(os.environ)
    for key in ("AZURE_MASPSX", "AZURE_MASPSX_COMPANION", "PYTHONPATH"):
        env.pop(key, None)
    return env


def clean_tree() -> None:
    status = subprocess.check_output(
        ["git", "status", "--porcelain", "--untracked-files=all"], cwd=ROOT, text=True
    )
    if status:
        raise RuntimeError("production worktree is not clean before activation:\n" + status[:4000])


def inventory_state() -> tuple[dict, list[dict]]:
    review = read_json(REVIEW)
    inv = read_json(INVENTORY)
    payloads = inv.get("files")
    if not isinstance(payloads, list) or not payloads:
        raise RuntimeError("transition inventory has no payload file list")
    if (sha(PATCH) != review.get("patch_sha256")
            or sha(INVENTORY) != review.get("inventory_sha256")
            or inv.get("patch_sha256") != review.get("patch_sha256")
            or review.get("checked_payloads", review.get("files")) != len(payloads)
            or inv.get("total_changed_or_new_files") != len(payloads)):
        raise RuntimeError("reviewed patch/inventory hashes or payload count do not agree")
    baseline_ok = review.get("current_baseline_matches",
                             review.get("before_hashes_match_gp57_and_production"))
    origins_ok = review.get("source_payloads_match_recorded_origins",
                            review.get("patch_replay_exact") and review.get("supplemental_replay_exact", True))
    apply_ok = review.get("git_apply_check") is True or inv.get("git_apply_check") == "PASS"
    if not (baseline_ok is True and origins_ok is True and apply_ok):
        raise RuntimeError("transition review does not attest baseline, origins, and apply check")
    seen = set()
    for item in payloads:
        target = Path(item["target"])
        if target.is_absolute() or ".." in target.parts or target.as_posix() in seen:
            raise RuntimeError("unsafe or repeated transition target: " + item.get("target", "?"))
        seen.add(target.as_posix())
        payload = TRANSITION / "payload" / target
        if not payload.is_file() or sha(payload) != item["after_sha256"]:
            raise RuntimeError("transition payload does not match inventory: " + target.as_posix())
    return review, payloads


def target_hashes(payloads: list[dict], *, require_after: bool = False) -> dict[str, str | None]:
    result = {}
    for item in payloads:
        name = item["target"]
        path = ROOT / name
        current = sha(path) if path.is_file() else None
        expected = item["after_sha256"] if require_after else item["before_sha256"]
        if current != expected:
            raise RuntimeError(f"target precondition differs for {name}: {current} != {expected}")
        result[name] = current
    return result


def private_evidence(payloads: list[dict]) -> dict:
    full = read_json(FULL_PROOF)
    own = read_json(FULL_OWNERSHIP)
    overlay = read_json(OVERLAY_PROOF)
    module_file = TRANSITION / "payload/config/slus_modules.json"
    owners = [m["name"] for m in read_json(module_file)["modules"]]
    combined = "owners" in full
    owner_count = full.get("owners") if combined else full.get("modules")
    physical_count = full.get("physical_objects_rebuilt") if combined else full.get("physical")
    image_exact = full.get("full_image_retail_exact") if combined else full.get("normal_image_retail_exact")
    graph_exact = full.get("pinned_graph_equal") if combined else full.get("pinned_ninja_equal")
    if (full.get("status") != "PASS" or full.get("production_unchanged") is not True
            or owner_count != len(owners) or physical_count != 860
            or image_exact is not True or graph_exact is not True):
        raise RuntimeError("final private full-ownership proof receipt is incomplete")
    if (own.get("modules") != owners or own.get("gate", {}).get("result") != "MATCH"
            or own.get("compiler_model", {}).get("explicit_rows") != [MODEL_ROW]
            or sha(FULL_OWNERSHIP) != full.get("ownership_receipt_sha256")):
        raise RuntimeError("private ownership proof does not match the complete candidate and explicit model row")
    certs = full.get("certificates", full.get("placement_certificates", {}))
    if not all(name in certs for name in PLACEMENTS):
        raise RuntimeError("private proof receipt omits one of the required placements")
    expected = overlay.get("expected_candidate_sha256")
    if (overlay.get("gate_exit_code") != 0 or overlay.get("all_latest_match") is False
            or overlay.get("journal", {}).get("all_latest_match") is not True
            or overlay.get("candidate_unchanged") is not True
            or overlay.get("production_inputs_unchanged") is not True
            or overlay.get("candidate_before_sha256") != expected
            or overlay.get("candidate_after_sha256") != expected):
        raise RuntimeError("private full-window gate receipt is not a clean candidate-bound pass")
    targets = {item["target"]: item for item in payloads}
    cli = targets.get("tools/maspsx/maspsx.py")
    package = targets.get("tools/maspsx/maspsx/__init__.py")
    if (not cli or not package or cli["after_sha256"] != expected.get("cli")
            or package["after_sha256"] != expected.get("package")):
        raise RuntimeError("reviewed transition does not contain the exact privately gated assembler pair")
    private_journal = OVERLAY_PROOF.parent / "journal.jsonl"
    if sha(private_journal) != overlay.get("journal", {}).get("journal_sha256"):
        raise RuntimeError("private overlay journal no longer matches its receipt")
    expected_windows = {}
    for line in private_journal.read_text().splitlines():
        if line.strip():
            record = json.loads(line)
            expected_windows[record["window"]] = record
    if (len(expected_windows) != 2175 or len(expected_windows) != overlay.get("journal", {}).get("windows")
            or any(r.get("result") != "MATCH" for r in expected_windows.values())):
        raise RuntimeError("private candidate gate lacks the complete 2,175-window MATCH identity set")
    pins = read_json(PROOF_INPUT_PINS)
    expected_payload = {item["target"]: item["after_sha256"] for item in payloads}
    if "payload" in pins:
        pinned_payload = pins["payload"]
    elif "gp57_inputs" in pins:
        gp57 = pins["gp57_inputs"]
        pinned_payload = dict(gp57["payload"])
        pinned_payload["tools/maspsx/maspsx.py"] = pins["retired_cli"]
        pinned_payload["tools/maspsx/maspsx/__init__.py"] = pins["retired_package"]
        retirement = read_json(PROOF_INPUT_PINS.parent / "receipt.json")
        if (sha(PROOF_INPUT_PINS.parent / "receipt.json") != pins.get("retirement_receipt")
                or retirement.get("input_hashes", {}).get("candidate_test") is None):
            raise RuntimeError("combined proof pins lack the reviewed migrated-test receipt")
        pinned_payload["tools/maspsx/tests/test_fold_selfinc_la.py"] = retirement["input_hashes"]["candidate_test"]
    else:
        raise RuntimeError("full proof inputs do not contain a complete reviewed payload map")
    if pinned_payload != expected_payload:
        raise RuntimeError("full ownership inputs do not pin every selected transition payload byte")
    proof_pins_hash = (full.get("source_pins_before_after_sha256") if combined
                       else full.get("source_input_pins_sha256"))
    if sha(PROOF_INPUT_PINS) != proof_pins_hash:
        raise RuntimeError("full ownership receipt is not bound to its complete source/tool input pins")
    if own.get("recipe_sha256", own.get("normal_ninja_sha256")) != (
            full.get("normal_ninja_sha256") if combined else full.get("normal_generated_ninja_sha256")):
        raise RuntimeError("full proof and ownership receipt use different generated SLUS recipes")
    return {"full_proof_sha256": sha(FULL_PROOF),
            "ownership_receipt_sha256": sha(FULL_OWNERSHIP),
            "overlay_gate_receipt_sha256": sha(OVERLAY_PROOF),
            "proof_input_pins_sha256": sha(PROOF_INPUT_PINS),
            "modules": owners, "private_overlay_windows": sorted(expected_windows),
            "assembler_sha256": expected}


def apply_preflight(payloads: list[dict]) -> None:
    clean_tree()
    target_hashes(payloads)
    command(["git", "apply", "--check", str(PATCH)])


def snapshot_slus_inputs(rows_path: Path, split_path: Path, output_path: Path) -> None:
    rows = [json.loads(line) for line in rows_path.read_text().splitlines() if line.strip()]
    sources = {}
    for row in rows:
        if row.get("kind") != "slus":
            continue
        path = ROOT / "src/slus" / Path(row["c_path"]).name
        sources[row["id"]] = sha(path) if path.is_file() else None
    edges = [json.loads(line) for line in split_path.read_text().splitlines() if line.strip()]
    write_json(output_path, {"source_sha256_by_row": sources, "edges_by_source":
        {edge["src"]: {k: edge[k] for k in ("src", "out", "ccver", "ccflags", "asflags")}
         for edge in edges}})


def changed_slus_rows(previous_rows: Path, previous_inputs: Path) -> tuple[list[str], list[str], dict]:
    old = {r["id"]: r for r in (json.loads(line) for line in previous_rows.read_text().splitlines() if line.strip())}
    new = {r["id"]: r for r in (json.loads(line) for line in (ROOT / "ledger/rows.jsonl").read_text().splitlines() if line.strip())}
    if old.keys() != new.keys():
        raise RuntimeError("transition changed row identities; refusing automatic cache rebaseline")
    prior_inputs = read_json(previous_inputs)
    old_edges = prior_inputs["edges_by_source"]
    new_edges = {edge["src"]: {k: edge[k] for k in ("src", "out", "ccver", "ccflags", "asflags")}
                 for edge in (json.loads(line) for line in
                              (ROOT / "ledger/splits/slus.jsonl").read_text().splitlines() if line.strip())}
    if old_edges.keys() != new_edges.keys():
        raise RuntimeError("transition changed logical SLUS edge identities; refusing automatic cache rebaseline")
    by_source = {PurePathKey(row["c_path"]): rid for rid, row in new.items()
                 if row.get("kind") == "slus"}
    registry_changed = {rid for rid in old if old[rid] != new[rid] and new[rid].get("kind") == "slus"}
    source_changed = set()
    old_sources = prior_inputs["source_sha256_by_row"]
    for rid, row in new.items():
        if row.get("kind") != "slus":
            continue
        path = ROOT / "src/slus" / Path(row["c_path"]).name
        digest = sha(path) if path.is_file() else None
        if old_sources.get(rid) != digest:
            source_changed.add(rid)
    recipe_changed_sources = {src for src in old_edges if old_edges[src] != new_edges[src]}
    recipe_changed = set()
    for source in recipe_changed_sources:
        row_id = by_source.get(PurePathKey(source))
        if row_id is None:
            raise RuntimeError("changed logical edge has no registry row: " + source)
        recipe_changed.add(row_id)
    changed = registry_changed | source_changed | recipe_changed
    changed = {rid for rid in changed if new[rid].get("kind") == "slus"}
    change_facts = {"registry_changed_rows": sorted(registry_changed),
                    "source_changed_rows": sorted(source_changed),
                    "recipe_changed_rows": sorted(recipe_changed)}
    if not changed:
        return [], [], change_facts
    sys.path.insert(0, str(ROOT / "tools"))
    from slus_module_context import membership, partition_context
    individual, grouped = [], []
    for rid in sorted(changed):
        parents, owners, _ = partition_context(new[rid])
        module = None if parents else membership(new[rid])
        (grouped if parents or module else individual).append(rid)
    return sorted(individual), sorted(grouped), change_facts


def PurePathKey(value: str) -> str:
    return Path(value).as_posix()


def rebaseline(rows: list[str], run_dir: Path) -> dict:
    if not rows:
        return {"changed_nonmodule_slus_rows": [], "grouped_rows_covered_by_ownership": [],
                "dry_run": [], "applied": []}
    ids = ",".join(rows)
    cmd = [sys.executable, "tools/verify.py", "--rebaseline-slus", ids, "--dry-run"]
    dry = command(cmd, env=base_env()).stdout
    dry_records = [json.loads(line) for line in dry.splitlines() if line.strip()]
    if sorted(r["id"] for r in dry_records) != rows or any(r.get("outcome") != "dry-run" for r in dry_records):
        raise RuntimeError("SLUS cache rebaseline dry run refused one or more changed nonmodule rows")
    cmd = [sys.executable, "tools/verify.py", "--rebaseline-slus", ids]
    applied_text = command(cmd, env=base_env()).stdout
    applied = [json.loads(line) for line in applied_text.splitlines() if line.strip()]
    if sorted(r["id"] for r in applied) != rows or any(r.get("outcome") != "rebaselined" for r in applied):
        raise RuntimeError("SLUS cache rebaseline did not update every approved nonmodule row")
    return {"changed_nonmodule_slus_rows": rows, "dry_run": dry_records, "applied": applied}


def latest_slus_gate() -> dict:
    path = ROOT / "ledger/gate_slus.jsonl"
    records = [json.loads(line) for line in path.read_text().splitlines() if line.strip()]
    if not records or records[-1].get("result") != "MATCH":
        raise RuntimeError("last production SLUS SHA-1 gate record is not MATCH")
    return records[-1]


def run_overlay_gate(run_id: str, run_dir: Path, payloads: list[dict],
                     expected_windows: list[str]) -> dict:
    exp = "gp_transition_" + re.sub(r"[^A-Za-z0-9_]", "_", run_id)
    build = ROOT / ("build_ovl_" + exp)
    if build.exists() or build.is_symlink():
        raise RuntimeError("isolated overlay build root already exists; refusing reuse: " + str(build))
    before = target_hashes(payloads, require_after=True)
    env = base_env()
    env.update({"EXP": exp, "SRCROOT": str(ROOT / "src")})
    command(["bash", "tools/build/mk_ovl_root.sh"], env=env,
            log=run_dir / "overlay_root.log")
    gate_env = base_env()
    assembler = str(ROOT / "tools/maspsx/maspsx.py")
    gate_env.update({"AZURE_MASPSX": assembler, "AZURE_MASPSX_COMPANION": assembler,
                     "GATE_BUILD_ROOT": build.name,
                     "GATE_JOURNAL": str(run_dir / "overlay_journal.jsonl")})
    command([sys.executable, "tools/build/gate_all.py", "--all", "--workers", "4"],
            env=gate_env, log=run_dir / "overlay_gate.log")
    after = target_hashes(payloads, require_after=True)
    if before != after:
        raise RuntimeError("transition targets changed during the forced overlay-window gate")
    latest = {}
    for line in (run_dir / "overlay_journal.jsonl").read_text().splitlines():
        if line.strip():
            record = json.loads(line)
            latest[record["window"]] = record
    if not latest or any(r.get("result") != "MATCH" for r in latest.values()):
        raise RuntimeError("post-activation forced overlay gate has an empty or non-MATCH journal")
    line_count = sum(bool(line.strip()) for line in (run_dir / "overlay_journal.jsonl").read_text().splitlines())
    if sorted(latest) != expected_windows or line_count != len(latest):
        raise RuntimeError("forced overlay gate did not produce one fresh result for every reviewed window")
    candidate_after = {"cli": sha(ROOT / "tools/maspsx/maspsx.py"),
                       "package": sha(ROOT / "tools/maspsx/maspsx/__init__.py")}
    candidate_before = {"cli": before["tools/maspsx/maspsx.py"],
                        "package": before["tools/maspsx/maspsx/__init__.py"]}
    if candidate_before != candidate_after:
        raise RuntimeError("installed assembler candidate hashes changed during the overlay gate")
    return {"exp": exp, "build_root": build.name, "windows": len(latest),
            "window_identity_sha256": sha_bytes("\n".join(sorted(latest)).encode()),
            "latest_results": {"MATCH": len(latest)},
            "journal_sha256": sha(run_dir / "overlay_journal.jsonl"),
            "candidate_sha256_before": candidate_before,
            "candidate_sha256_after": candidate_after,
            "transition_targets_unchanged": True}


def check_certificates() -> dict:
    sys.path.insert(0, str(ROOT / "tools"))
    from slus_module_context import modules
    from slus_module_evidence import certificate_reason
    declared = {m["name"]: m for m in modules()}
    results = {}
    for name in PLACEMENTS:
        module = declared.get(name)
        path = ROOT / "ledger/modules" / (name + ".json")
        if module is None or not path.is_file():
            raise RuntimeError("required placement certificate missing: " + name)
        cert = read_json(path)
        reason = certificate_reason(module, cert)
        if reason is not None or cert.get("gate", {}).get("result") != "MATCH":
            raise RuntimeError(f"placement certificate is stale or failed: {name}: {reason}")
        results[name] = {"sha256": sha(path), "reason": None,
                          "recipe_sha256": cert["gate"]["recipe_sha256"]}
    return results


def activate(run_dir: Path, run_id: str, payloads: list[dict], evidence: dict,
             previous_rows: Path, previous_inputs: Path, receipt: dict) -> None:
    receipt["phase"] = "apply_exact_patch"
    write_json(run_dir / "activation_receipt.json", receipt)
    command(["git", "apply", str(PATCH)], log=run_dir / "apply.log")
    receipt["patch_state"] = "applied"
    receipt["applied_target_sha256"] = target_hashes(payloads, require_after=True)
    receipt["phase"] = "production_slus_build"
    write_json(run_dir / "activation_receipt.json", receipt)

    env = base_env()
    command([sys.executable, "-m", "unittest", "discover", "-s", "tools/tests",
             "-p", "test_slus*.py"], env=env, log=run_dir / "slus_tests.log")
    command([sys.executable, "-m", "unittest", "discover", "-s", "tools/tests",
             "-p", "test_configure_slus*.py"], env=env, log=run_dir / "configure_slus_tests.log")
    test_env = dict(env, PYTHONPATH=str(ROOT / "tools/maspsx"))
    suite = [sys.executable, "-m", "unittest", "discover", "-s", "tools/maspsx/tests", "-t", "."]
    candidate_rc = logged_status(suite, run_dir / "maspsx_tests.log", test_env)
    summary = re.search(r"^Ran (\d+) tests? in ",
                        (run_dir / "maspsx_tests.log").read_text(errors="replace"), re.M)
    if candidate_rc != 0 or failed_tests(run_dir / "maspsx_tests.log") or not summary or int(summary.group(1)) != 418:
        raise RuntimeError("complete 418-test candidate assembler suite did not pass")
    command([sys.executable, "-m", "unittest", "-v", "tools.maspsx.tests.test_fold_selfinc_la"],
            env=test_env, log=run_dir / "maspsx_selfinc_test.log")
    command(["bash", "tools/build/mk_slus_root.sh"], env=env,
            log=run_dir / "slus_root.log")
    command([sys.executable, "tools/configure.py"], cwd=ROOT / "build_slus", env=env,
            log=run_dir / "slus_configure.log")
    ninja = ROOT / "build_slus/build.ninja"
    pinned = ROOT / "ledger/splits/slus.build.ninja"
    full = read_json(FULL_PROOF)
    expected_ninja = full.get("normal_ninja_sha256", full.get("normal_generated_ninja_sha256"))
    if ninja.read_bytes() != pinned.read_bytes() or sha(ninja) != expected_ninja:
        raise RuntimeError("normal configure did not reproduce the reviewed complete SLUS recipe")
    command([sys.executable, "tools/row_db.py", "check"], env=env,
            log=run_dir / "row_db_configured.log")
    command(["bash", "tools/build/build_slus.sh", "-j", "2"], env=env,
            log=run_dir / "slus_build.log")
    gate = latest_slus_gate()
    image = ROOT / "build_slus/build/slus_006.14"
    if image.read_bytes() != (ROOT / "baserom/slus_006.14").read_bytes():
        raise RuntimeError("normal SLUS build image differs from retail")
    receipt["slus_gate"] = {"result": gate["result"], "recipe_sha256": gate.get("recipe_sha256"),
                            "physical_units": gate.get("tus"), "image_sha256": sha(image)}

    receipt["phase"] = "forced_global_overlay_gate"
    write_json(run_dir / "activation_receipt.json", receipt)
    receipt["overlay_gate"] = run_overlay_gate(
        run_id, run_dir, payloads, evidence["private_overlay_windows"])

    receipt["phase"] = "cache_rebaseline_before_ownership"
    changed, grouped, change_facts = changed_slus_rows(previous_rows, previous_inputs)
    cache_result = rebaseline(changed, run_dir)
    cache_result["grouped_rows_covered_by_ownership"] = grouped
    cache_result.update(change_facts)
    receipt["cache_rebaseline"] = cache_result
    command([sys.executable, "tools/row_db.py", "check"], env=env,
            log=run_dir / "row_db_after_rebaseline.log")

    receipt["phase"] = "full_33_owner_proof"
    write_json(run_dir / "activation_receipt.json", receipt)
    manifest = read_json(ROOT / "config/slus_modules.json")
    owners = [m["name"] for m in manifest["modules"]]
    proof_path = run_dir / "ownership_receipt.json"
    command([sys.executable, "tools/fidelity/prove_slus_ownership.py", *owners,
             "--compiler-model-row", MODEL_ROW, "--output", str(proof_path)],
            env=env, log=run_dir / "ownership.log")
    proof = read_json(proof_path)
    if (proof.get("modules") != owners or proof.get("gate", {}).get("result") != "MATCH"
            or proof.get("compiler_model", {}).get("explicit_rows") != [MODEL_ROW]
            or proof.get("recipe_sha256") != sha(ninja) or not proof.get("rows")):
        raise RuntimeError("production ownership proof lacks complete rows, explicit model row, or retail gate")
    receipt["ownership"] = {"sha256": sha(proof_path), "modules": len(owners),
                            "rows": len(proof["rows"]), "recipe_sha256": proof["recipe_sha256"],
                            "image_sha1": proof["image_sha1"], "model_rows": [MODEL_ROW]}

    receipt["phase"] = "placement_certificates"
    write_json(run_dir / "activation_receipt.json", receipt)
    for name in PLACEMENTS:
        command([sys.executable, "tools/fidelity/certify_slus_module.py", name,
                 "--reviewer", "codex", "--write"], env=env,
                log=run_dir / ("certify_" + name + ".log"))
    receipt["placement_certificates"] = check_certificates()
    command([sys.executable, "tools/row_db.py", "check"], env=env,
            log=run_dir / "row_db_final.log")
    if sha(FULL_PROOF) != evidence["full_proof_sha256"] or sha(OVERLAY_PROOF) != evidence["overlay_gate_receipt_sha256"]:
        raise RuntimeError("private approval evidence changed during activation")
    if target_hashes(payloads, require_after=True) != receipt["applied_target_sha256"]:
        raise RuntimeError("reviewed target bytes changed during activation")

    receipt["phase"] = "await_fresh_production_census"
    receipt["status"] = "PASS_GATES_CENSUS_PENDING"
    receipt["fresh_production_census"] = {
        "required": True, "input_path": None,
        "reason": "private census fingerprints bind different absolute roots/cache inputs; run a fresh production-root census after cache rebaseline",
        "dependency_ledger_imported": False,
        "levels_and_status_refresh": "deferred until provenance-checked dependency import",
        "followup": "root-owned fresh census, provenance review/import, then levels.py, status.py, row_db.py check and certificate_reason revalidation"}
    receipt["end_utc"] = time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())
    write_json(run_dir / "activation_receipt.json", receipt)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--execute", action="store_true",
                        help="explicitly opt in to applying the reviewed patch and running production gates")
    parser.add_argument("--check", action="store_true",
                        help="read-only validation of the selected reviewed packet and private proof receipts")
    parser.add_argument("--packet-dir", type=Path, default=HERE / "transition",
                        help="reviewed packet directory containing transition.patch, inventory.json, and payload/")
    parser.add_argument("--patch", type=Path,
                        help="exact reviewed patch path; relative paths are resolved under --packet-dir")
    parser.add_argument("--review", type=Path, default=HERE / "root_transition_review.json",
                        help="review receipt for the selected packet")
    parser.add_argument("--full-proof", type=Path, default=HERE / "full_ownership/receipt.json")
    parser.add_argument("--ownership-proof", type=Path, default=HERE / "full_ownership/ownership_receipt.json")
    parser.add_argument("--overlay-proof", type=Path, default=HERE / "overlay_gate/receipt.json")
    parser.add_argument("--proof-input-pins", type=Path, default=HERE / "full_ownership/input_pins.json")
    args = parser.parse_args()
    global TRANSITION, PATCH, INVENTORY, REVIEW, FULL_PROOF, FULL_OWNERSHIP, OVERLAY_PROOF, PROOF_INPUT_PINS
    TRANSITION = args.packet_dir.resolve()
    if args.patch:
        PATCH = args.patch if args.patch.is_absolute() else TRANSITION / args.patch
        PATCH = PATCH.resolve()
    else:
        patches = [p for p in (TRANSITION / "transition.patch", TRANSITION / "combined.patch",
                               TRANSITION / "final.patch") if p.is_file()]
        if len(patches) > 1:
            print("Several candidate patch files exist; select one with --patch.", file=sys.stderr)
            return 2
        PATCH = patches[0] if patches else TRANSITION / "transition.patch"
    INVENTORY = TRANSITION / "inventory.json"
    REVIEW = args.review.resolve()
    FULL_PROOF = args.full_proof.resolve()
    FULL_OWNERSHIP = args.ownership_proof.resolve()
    OVERLAY_PROOF = args.overlay_proof.resolve()
    PROOF_INPUT_PINS = args.proof_input_pins.resolve()
    if args.check:
        try:
            review, payloads = inventory_state()
            evidence = private_evidence(payloads)
            clean_tree()
            target_hashes(payloads)
            command(["git", "apply", "--check", str(PATCH)])
            print(json.dumps({"status": "READ_ONLY_PREFLIGHT_PASS",
                              "payload_count": len(payloads),
                              "patch_sha256": review["patch_sha256"],
                              "inventory_sha256": review["inventory_sha256"],
                              "private_overlay_windows": len(evidence["private_overlay_windows"]),
                              "target_state": "all_before_hashes_match"}, indent=2))
            return 0
        except Exception as exc:
            print(f"Read-only preflight failed: {exc}", file=sys.stderr)
            return 1
    if not args.execute:
        print("Refusing activation: use --check for read-only validation, or pass --execute only after separate owner/user approval.", file=sys.stderr)
        return 2

    run_id = time.strftime("%Y%m%dT%H%M%SZ", time.gmtime()) + f"_{os.getpid()}"
    run_dir = HERE / "activation_runs" / run_id
    run_dir.mkdir(parents=True, exist_ok=False)
    (run_dir / ".ignore").write_text("*\n")
    lock_path = ROOT / "build_ovl/work/land.lock"
    phase = "read_only_preflight"
    receipt = {"schema": 1, "status": "RUNNING", "run_id": run_id,
               "started_utc": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()),
               "patch_state": "not_applied", "phase": phase,
               "approval": "external decision; --execute is only a technical opt-in"}
    try:
        review, payloads = inventory_state()
        evidence = private_evidence(payloads)
        apply_preflight(payloads)
        lock_path.parent.mkdir(parents=True, exist_ok=True)
        with lock_path.open("a+") as lock:
            fcntl.flock(lock.fileno(), fcntl.LOCK_EX | fcntl.LOCK_NB)
            phase = "locked_preflight"
            apply_preflight(payloads)
            evidence = private_evidence(payloads)
            receipt.update({"phase": phase, "review_sha256": sha(REVIEW),
                            "patch_sha256": review["patch_sha256"],
                            "inventory_sha256": review["inventory_sha256"],
                            "payload_count": len(payloads), "candidate_evidence": evidence,
                            "before_target_sha256": target_hashes(payloads),
                            "pre_transition_rows_sha256": sha(ROOT / "ledger/rows.jsonl")})
            previous_rows = run_dir / "pre_transition_rows.jsonl"
            previous_rows.write_bytes((ROOT / "ledger/rows.jsonl").read_bytes())
            previous_inputs = run_dir / "pre_transition_slus_inputs.json"
            snapshot_slus_inputs(ROOT / "ledger/rows.jsonl", ROOT / "ledger/splits/slus.jsonl", previous_inputs)
            write_json(run_dir / "activation_receipt.json", receipt)
            activate(run_dir, run_id, payloads, evidence, previous_rows, previous_inputs, receipt)
        print(json.dumps({"status": receipt["status"], "receipt": str(run_dir / "activation_receipt.json")}, indent=2))
        return 0
    except Exception as exc:
        if run_dir.exists():
            try:
                _, payloads = inventory_state()
                after_count = sum(1 for item in payloads
                                  if (ROOT / item["target"]).is_file()
                                  and sha(ROOT / item["target"]) == item["after_sha256"])
                state = ("applied" if after_count == len(payloads) else
                         "partial" if after_count else "not_applied")
            except Exception:
                state = receipt.get("patch_state", "unknown")
            failure = dict(receipt, status="FAILED", phase=receipt.get("phase", phase),
                           patch_state=state, error_type=type(exc).__name__, error=str(exc),
                           failed_utc=time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()),
                           recovery="No automatic rollback was attempted; inspect the receipt and live tree.")
            write_json(run_dir / "failure_receipt.json", failure)
        failed_phase = receipt.get("phase", phase)
        print(f"Activation failed during {failed_phase}: {exc}", file=sys.stderr)
        if run_dir.exists():
            print("Failure receipt: " + str(run_dir / "failure_receipt.json"), file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
