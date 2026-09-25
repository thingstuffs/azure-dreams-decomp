#!/usr/bin/env python3
"""Final combined ownership/certifier rerun after validation-only controls refresh."""

from __future__ import annotations

import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import time

import combined as B

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
BASE = HERE / "combined_fixture"
FINAL = HERE / "combined_final_fixture"
CONTROLS = ROOT / "work/native_lane/gp_partition_only_tools/controls_refresh"
PYTHON = ROOT / ".venv/bin/python"
MODEL = "slus/konami_runtime_w_80033D54"
CERTS = ("list_cursor_e0", "runtime_directory")
TOOL_NAMES = ("aspsx_diff.py", "maspsx_trace.py")
FINAL_CONTROL_SHA = "5b775f530d62f9a02bd9c5717e833945b6a9346e730e51c4d2f401e5467d8e27"
MIGRATED_TEST = "tools/maspsx/tests/test_fold_selfinc_la.py"


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def write_json(path: Path, value: dict) -> None:
    path.write_text(json.dumps(value, indent=2, sort_keys=True) + "\n")


def base_snapshot() -> dict:
    ownership = json.loads((HERE / "combined_receipt.json").read_text())
    if ownership.get("status") != "PASS" or ownership.get("owners") != 33:
        raise RuntimeError("combined pre-refresh baseline is not complete")
    frozen = json.loads((HERE / "combined_frozen_before.json").read_text())
    outputs = sorted(frozen["objects"])
    names = ("build_slus/build.ninja", "build_slus/build/slus_006.14",
             "tools/fidelity/aspsx_diff.py", "tools/fidelity/maspsx_trace.py",
             "tools/maspsx/maspsx.py", "tools/maspsx/maspsx/__init__.py",
             "toolchain/maspsx/maspsx.py", "toolchain/maspsx/maspsx/__init__.py",
             "config/slus_modules.json", "config/slus_partitions.json",
             "ledger/splits/slus.build.ninja", "ledger/splits/slus.jsonl", "ledger/rows.jsonl")
    return {"files": {name: sha(BASE / name) for name in names},
            "objects": {name: sha(BASE / "build_slus" / name) for name in outputs},
            "physical": len(outputs)}


def input_pins() -> dict:
    prior = json.loads((HERE / "combined_source_pins.json").read_text())
    if B.source_pins() != prior:
        raise RuntimeError("frozen GP57/retired-assembler source pins changed")
    initial = json.loads((CONTROLS / "prepare_receipt.json").read_text())
    prep = json.loads((CONTROLS / "prepare_final_receipt.json").read_text())
    final = json.loads((CONTROLS / "final_run_receipt.json").read_text())
    if (sha(CONTROLS / "final_run_receipt.json") != FINAL_CONTROL_SHA
            or initial.get("status") != "PREPARED" or prep.get("status") != "PREPARED"
            or final.get("status") != "PASS" or final.get("passed_controls") != 60
            or final.get("failed_controls") != [] or final.get("controls_return") != 0
            or final.get("production_unchanged") is not True
            or final.get("prepare_receipt_sha256") != sha(CONTROLS / "prepare_final_receipt.json")
            or final.get("tool_pins") != prep.get("tool_pins")
            or set(prep.get("tool_pins", {})) != set(TOOL_NAMES)):
        raise RuntimeError("frozen final controls chain is not complete")
    for name in TOOL_NAMES:
        if sha(CONTROLS / "tools/fidelity" / name) != prep["tool_pins"][name]["after"]:
            raise RuntimeError("controls refresh tool changed: " + name)
        if (sha(BASE / "tools/fidelity" / name) != initial["tool_pins"][name]["before"]
                or initial["tool_pins"][name]["after"] != prep["tool_pins"][name]["before"]):
            raise RuntimeError("combined baseline tool differs: " + name)
    payload = dict(prior["gp57_inputs"]["payload"])
    if payload["tools/maspsx/maspsx/__init__.py"] != prior["gp57_inputs"]["generic"]["maspsx/__init__.py"]:
        raise RuntimeError("GP57 payload does not start from guarded package")
    payload["tools/maspsx/maspsx/__init__.py"] = sha(HERE / "candidate/maspsx/__init__.py")
    payload[MIGRATED_TEST] = sha(HERE / "test_fixture" / MIGRATED_TEST)
    for name in TOOL_NAMES:
        payload["tools/fidelity/" + name] = prep["tool_pins"][name]["after"]
    if len(payload) != len(prior["gp57_inputs"]["payload"]) + 3:
        raise RuntimeError("combined payload count differs")
    return {"combined_receipt_sha256": sha(HERE / "combined_receipt.json"),
            "combined_source_pins_sha256": sha(HERE / "combined_source_pins.json"),
            "retirement_receipt_sha256": sha(HERE / "receipt.json"),
            "controls_prepare_receipt_sha256": sha(CONTROLS / "prepare_final_receipt.json"),
            "controls_final_receipt_sha256": FINAL_CONTROL_SHA,
            "validation_tools": {name: prep["tool_pins"][name]["after"] for name in TOOL_NAMES},
            "retired_cli_sha256": sha(HERE / "candidate/maspsx.py"),
            "retired_package_sha256": sha(HERE / "candidate/maspsx/__init__.py"),
            "payload": payload,
            "prover_wrapper_sha256": sha(B.FULL / "prover_cli.py")}


def check_links() -> int:
    count = 0
    for path in FINAL.rglob("*"):
        if not path.is_symlink():
            continue
        count += 1
        target = path.resolve()
        if target == BASE or BASE in target.parents or target == B.FROZEN or B.FROZEN in target.parents:
            raise RuntimeError("final copy links back to frozen private fixture: " + str(path))
    return count


def run(command: list[str], label: str, cwd: Path) -> None:
    print("START " + label, flush=True)
    env = dict(os.environ)
    for name in ("AZURE_MASPSX", "AZURE_MASPSX_COMPANION", "PYTHONPATH"):
        env.pop(name, None)
    start = time.monotonic()
    with (HERE / (label + ".log")).open("w") as log:
        result = subprocess.run(command, cwd=cwd, env=env, stdout=log, stderr=subprocess.STDOUT)
    if result.returncode:
        raise RuntimeError(label + " failed rc=" + str(result.returncode) + ": "
                           + (HERE / (label + ".log")).read_text()[-2500:])
    print("PASS " + label + " in " + str(round(time.monotonic() - start, 1)) + "s", flush=True)


def prepare() -> None:
    if FINAL.exists() or FINAL.is_symlink():
        raise RuntimeError("final controls fixture already exists")
    source = input_pins()
    old = base_snapshot()
    production = B.load_full().production_snapshot()
    shutil.copytree(BASE, FINAL, symlinks=True,
                    ignore=shutil.ignore_patterns("__pycache__", "*.pyc"))
    rewired = 0
    for path in FINAL.rglob("*"):
        if not path.is_symlink():
            continue
        raw = Path(os.readlink(path))
        target = raw if raw.is_absolute() else (path.parent / raw).resolve()
        if target == BASE or BASE in target.parents:
            replacement = FINAL / target.relative_to(BASE)
            path.unlink()
            path.symlink_to(replacement, target_is_directory=replacement.is_dir())
            rewired += 1
    if check_links() < 900:
        raise RuntimeError("not all copied fixture links were private")
    for name, digest in source["validation_tools"].items():
        shutil.copy2(CONTROLS / "tools/fidelity" / name, FINAL / "tools/fidelity" / name)
        if sha(FINAL / "tools/fidelity" / name) != digest:
            raise RuntimeError("validation-only tool copy differs: " + name)
    if (sha(FINAL / "tools/maspsx/maspsx/__init__.py") != source["retired_package_sha256"]
            or sha(FINAL / "toolchain/maspsx/maspsx/__init__.py") != source["retired_package_sha256"]):
        raise RuntimeError("retired assembler package changed in final copy")
    if base_snapshot() != old or B.load_full().production_snapshot() != production or input_pins() != source:
        raise RuntimeError("baseline, production or reviewed control inputs changed during copy")
    write_json(HERE / "final_source_pins.json", source)
    write_json(HERE / "final_base_before.json", old)
    write_json(HERE / "final_production_before.json", production)
    write_json(HERE / "final_prepare_receipt.json", {
        "status": "PREPARED", "fixture": str(FINAL.relative_to(ROOT)),
        "rewired_symlinks": rewired, "physical_objects": old["physical"],
        "validation_tools": source["validation_tools"],
        "production_unchanged": True, "combined_baseline_unchanged": True})
    print("PREPARED final controls fixture", flush=True)


def prove() -> None:
    if not (HERE / "final_prepare_receipt.json").is_file():
        raise RuntimeError("prepare first")
    pins = json.loads((HERE / "final_source_pins.json").read_text())
    old = json.loads((HERE / "final_base_before.json").read_text())
    production = json.loads((HERE / "final_production_before.json").read_text())
    if input_pins() != pins or base_snapshot() != old or B.load_full().production_snapshot() != production:
        raise RuntimeError("reviewed inputs changed before final controls proof")
    if check_links() < 900:
        raise RuntimeError("final fixture has a link back to prior fixture")
    run([str(PYTHON), "tools/configure.py"], "final_configure", FINAL / "build_slus")
    ninja = FINAL / "build_slus/build.ninja"
    if ninja.read_bytes() != (FINAL / "ledger/splits/slus.build.ninja").read_bytes() or (
            ninja.read_bytes() != (BASE / "build_slus/build.ninja").read_bytes()):
        raise RuntimeError("final generated Ninja differs from pinned graph")
    run(["ninja", "-C", str(FINAL / "build_slus"), "-j", "2", "build/slus_006.14"],
        "final_build", FINAL)
    image = FINAL / "build_slus/build/slus_006.14"
    if image.read_bytes() != (ROOT / "baserom/slus_006.14").read_bytes():
        raise RuntimeError("final controls image differs from retail")
    changed_objects = [name for name, digest in old["objects"].items()
                       if sha(FINAL / "build_slus" / name) != digest]
    if changed_objects:
        raise RuntimeError("validation-only tool refresh changed C objects: " + repr(changed_objects[:8]))
    owners = [m["name"] for m in json.loads((FINAL / "config/slus_modules.json").read_text())["modules"]]
    if len(owners) != 33:
        raise RuntimeError("final manifest does not have 33 owners")
    run([str(PYTHON), str(B.FULL / "prover_cli.py"), "ownership", *owners,
         "--compiler-model-row", MODEL, "--output", str(HERE / "final_ownership_receipt.json")],
        "final_ownership", FINAL)
    ownership = json.loads((HERE / "final_ownership_receipt.json").read_text())
    if (ownership.get("schema") != 5 or ownership.get("modules") != owners
            or ownership.get("gate", {}).get("result") != "MATCH"
            or ownership.get("compiler_model", {}).get("explicit_rows") != [MODEL]
            or len(ownership.get("data", {})) != 33
            or ownership.get("recipe_sha256") != sha(ninja)):
        raise RuntimeError("final ownership scope, model or full gate differs")
    certs = {}
    for name in CERTS:
        run([str(PYTHON), str(B.FULL / "prover_cli.py"), "certificate", name,
             "--reviewer", "codex", "--write"], "final_certify_" + name, FINAL)
        target = FINAL / "ledger/modules" / (name + ".json")
        cert = json.loads(target.read_text())
        if cert.get("module") != name or cert.get("gate", {}).get("result") != "MATCH":
            raise RuntimeError("final private certifier failed: " + name)
        certs[name] = {"sha256": sha(target), "schema": cert["schema"],
                       "members": cert["members"]}
    if input_pins() != pins or base_snapshot() != old or B.load_full().production_snapshot() != production:
        raise RuntimeError("reviewed inputs changed during final controls proof")
    for name, digest in pins["validation_tools"].items():
        if sha(FINAL / "tools/fidelity" / name) != digest:
            raise RuntimeError("final validation tool changed: " + name)
    receipt = {"schema": 1, "status": "PASS",
        "purpose": "private final GP57 plus retired-sink ownership with validation-only controls refresh",
        "owners": 33, "ownership_schema": ownership["schema"],
        "measured_rows": len(ownership["rows"]), "physical_objects": len(old["objects"]),
        "physical_objects_rebuilt": json.loads((HERE / "combined_receipt.json").read_text())["physical_objects_rebuilt"],
        "final_rechecked_physical_objects": len(old["objects"]),
        "all_objects_equal_combined_baseline": True,
        "normal_ninja_sha256": sha(ninja), "pinned_graph_equal": True,
        "full_image_sha256": sha(image), "full_image_retail_exact": True,
        "explicit_compiler_model_rows": ownership["compiler_model"]["explicit_rows"],
        "ownership_receipt_sha256": sha(HERE / "final_ownership_receipt.json"),
        "certificates": certs, "validation_tools": pins["validation_tools"],
        "retired_package_sha256": pins["retired_package_sha256"],
        "source_pins_sha256": sha(HERE / "final_source_pins.json"),
        "source_pins_before_after_sha256": sha(HERE / "final_source_pins.json"),
        "production_unchanged": True, "combined_baseline_unchanged": True,
        "logs": {name: sha(HERE / (name + ".log")) for name in
                 ("final_configure", "final_build", "final_ownership",
                  *("final_certify_" + x for x in CERTS))}}
    write_json(HERE / "final_combined_receipt.json", receipt)
    print(json.dumps(receipt, indent=2, sort_keys=True), flush=True)


if __name__ == "__main__":
    if len(sys.argv) != 2 or sys.argv[1] not in ("prepare", "prove"):
        raise SystemExit("usage: final_controls.py {prepare|prove}")
    try:
        globals()[sys.argv[1]]()
    except Exception as exc:
        write_json(HERE / "final_failure_receipt.json", {
            "status": "ERROR", "phase": sys.argv[1], "type": type(exc).__name__,
            "message": str(exc), "at": time.strftime('%Y-%m-%dT%H:%M:%SZ', time.gmtime())})
        raise
