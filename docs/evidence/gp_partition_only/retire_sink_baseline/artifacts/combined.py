#!/usr/bin/env python3
"""Full GP57 + retired-sink private build, ownership, and placement rehearsal."""

from __future__ import annotations

import hashlib
import importlib.util
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import time

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
FULL = ROOT / "work/native_lane/gp_partition_only_tools/full_ownership"
FROZEN = FULL / "fixture"
COMBINED = HERE / "combined_fixture"
CAND = HERE / "candidate"
PYTHON = ROOT / ".venv/bin/python"
MODEL = "slus/konami_runtime_w_80033D54"
CERTS = ("list_cursor_e0", "runtime_directory")


def load_full():
    spec = importlib.util.spec_from_file_location("full_ownership_run", FULL / "run.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def write_json(path: Path, value: dict) -> None:
    path.write_text(json.dumps(value, indent=2, sort_keys=True) + "\n")


def source_pins() -> dict:
    full = load_full()
    return {"gp57_inputs": full.transition_pins(),
            "retired_cli": sha(CAND / "maspsx.py"),
            "retired_package": sha(CAND / "maspsx/__init__.py"),
            "retirement_receipt": sha(HERE / "receipt.json"),
            "full_ownership_receipt": sha(FULL / "receipt.json"),
            "prover_wrapper": sha(FULL / "prover_cli.py")}


def frozen_snapshot() -> dict:
    pins = json.loads((FULL / "input_pins.json").read_text())
    outputs = sorted(pins["stage_objects"])
    files = ("build_slus/build.ninja", "build_slus/build/slus_006.14",
             "tools/maspsx/maspsx.py", "tools/maspsx/maspsx/__init__.py",
             "toolchain/maspsx/maspsx.py", "toolchain/maspsx/maspsx/__init__.py",
             "config/slus_modules.json", "config/slus_partitions.json",
             "ledger/splits/slus.build.ninja", "ledger/splits/slus.jsonl",
             "ledger/rows.jsonl")
    return {"files": {name: sha(FROZEN / name) for name in files},
            "objects": {name: sha(FROZEN / "build_slus" / name) for name in outputs},
            "physical": len(outputs)}


def check_private_links() -> int:
    count = 0
    for path in COMBINED.rglob("*"):
        if not path.is_symlink():
            continue
        count += 1
        target = path.resolve()
        if target == FROZEN or FROZEN in target.parents:
            raise RuntimeError("combined fixture links to frozen fixture: " + str(path))
    return count


def run(command: list[str], label: str, cwd: Path, env: dict | None = None) -> None:
    print("START " + label, flush=True)
    actual_env = dict(os.environ if env is None else env)
    for name in ("AZURE_MASPSX", "AZURE_MASPSX_COMPANION", "PYTHONPATH"):
        actual_env.pop(name, None)
    start = time.monotonic()
    with (HERE / (label + ".log")).open("w") as log:
        result = subprocess.run(command, cwd=cwd, env=actual_env, stdout=log, stderr=subprocess.STDOUT)
    if result.returncode:
        raise RuntimeError(label + " failed rc=" + str(result.returncode) + ": "
                           + (HERE / (label + ".log")).read_text()[-2500:])
    print("PASS " + label + " in " + str(round(time.monotonic() - start, 1)) + "s", flush=True)


def prepare() -> None:
    if COMBINED.exists() or COMBINED.is_symlink():
        raise RuntimeError("combined fixture already exists")
    if (HERE / ".ignore").read_text() != "*\n":
        raise RuntimeError("ignored output guard missing")
    private_receipt = json.loads((HERE / "receipt.json").read_text())
    if private_receipt.get("status") != "PRIVATE_PASS_RETIREMENT_PROBE_PASS":
        raise RuntimeError("candidate unit/consumer probe is not complete")
    source = source_pins()
    full_pins = json.loads((FULL / "input_pins.json").read_text())
    if source["gp57_inputs"] != full_pins or source["retired_cli"] != full_pins["generic"]["maspsx.py"]:
        raise RuntimeError("retired candidate does not match frozen GP57 lineage")
    if source["retired_package"] != private_receipt["candidate_package_sha256"]:
        raise RuntimeError("retired package changed after 418-test probe")
    full_receipt = json.loads((FULL / "receipt.json").read_text())
    if full_receipt.get("status") != "PASS" or full_receipt.get("modules") != 33:
        raise RuntimeError("GP57 full ownership fixture is not complete")
    frozen_before = frozen_snapshot()
    production_before = load_full().production_snapshot()
    shutil.copytree(FROZEN, COMBINED, symlinks=True,
                    ignore=shutil.ignore_patterns("__pycache__", "*.pyc"))
    for name, target in (("tools", COMBINED / "tools/build"),
                         ("include", COMBINED / "include"),
                         ("toolchain", COMBINED / "toolchain"),
                         ("baserom", COMBINED / "baserom"),
                         (".venv", COMBINED / ".venv"),
                         ("raw/slus", COMBINED / "raw/slus")):
        path = COMBINED / "build_slus" / name
        if not path.is_symlink():
            raise RuntimeError("expected copied build-root link: " + name)
        path.unlink()
        path.symlink_to(target, target_is_directory=True)
    src = COMBINED / "build_slus/src"
    if not src.is_dir() or src.is_symlink():
        raise RuntimeError("build source view is not a managed directory")
    for path in src.iterdir():
        if not path.is_symlink():
            raise RuntimeError("build source entry is not a copied symlink: " + str(path))
        path.unlink()
        path.symlink_to(COMBINED / "src/slus" / path.name)
    for name in ("tools/maspsx/maspsx/__init__.py", "toolchain/maspsx/maspsx/__init__.py"):
        target = COMBINED / name
        shutil.copy2(CAND / "maspsx/__init__.py", target)
        if sha(target) != source["retired_package"]:
            raise RuntimeError("combined assembler package differs: " + name)
    if sha(COMBINED / "tools/maspsx/maspsx.py") != source["retired_cli"] or (
            sha(COMBINED / "toolchain/maspsx/maspsx.py") != source["retired_cli"]):
        raise RuntimeError("combined assembler CLI differs")
    links = check_private_links()
    if frozen_snapshot() != frozen_before or load_full().production_snapshot() != production_before:
        raise RuntimeError("frozen fixture or production changed during combined preparation")
    write_json(HERE / "combined_source_pins.json", source)
    write_json(HERE / "combined_frozen_before.json", frozen_before)
    write_json(HERE / "combined_production_before.json", production_before)
    write_json(HERE / "combined_prepare_receipt.json", {
        "status": "PREPARED", "copied_fixture": str(COMBINED.relative_to(ROOT)),
        "rewired_symlinks": links, "physical_objects": frozen_before["physical"],
        "retired_package_sha256": source["retired_package"],
        "production_unchanged": True, "frozen_fixture_unchanged": True})
    print("PREPARED detached combined fixture", flush=True)


def prove() -> None:
    if not (HERE / "combined_prepare_receipt.json").is_file():
        raise RuntimeError("prepare first")
    source = json.loads((HERE / "combined_source_pins.json").read_text())
    frozen_before = json.loads((HERE / "combined_frozen_before.json").read_text())
    production_before = json.loads((HERE / "combined_production_before.json").read_text())
    if source_pins() != source or frozen_snapshot() != frozen_before or (
            load_full().production_snapshot() != production_before):
        raise RuntimeError("candidate, frozen fixture or production changed before combined proof")
    if check_private_links() < 900:
        raise RuntimeError("not all copied build links were rewired")
    run([str(PYTHON), "tools/configure.py"], "combined_configure", COMBINED / "build_slus")
    ninja = COMBINED / "build_slus/build.ninja"
    if ninja.read_bytes() != (COMBINED / "ledger/splits/slus.build.ninja").read_bytes() or (
            ninja.read_bytes() != (FROZEN / "build_slus/build.ninja").read_bytes()):
        raise RuntimeError("combined normal configure differs from GP57 pinned graph")
    outputs = sorted(frozen_before["objects"])
    if len(outputs) != 860:
        raise RuntimeError("expected 860 physical objects")
    for name in outputs:
        path = COMBINED / "build_slus" / name
        if not path.is_file():
            raise RuntimeError("copied physical object absent before forced rebuild: " + name)
        path.unlink()
    run(["ninja", "-C", str(COMBINED / "build_slus"), "-j", "2", "build/slus_006.14"],
        "combined_rebuild", COMBINED)
    image = COMBINED / "build_slus/build/slus_006.14"
    if image.read_bytes() != (ROOT / "baserom/slus_006.14").read_bytes():
        raise RuntimeError("combined full rebuilt image is not retail exact")
    changed = [name for name, digest in frozen_before["objects"].items()
               if sha(COMBINED / "build_slus" / name) != digest]
    if changed:
        raise RuntimeError("retired pass changed physical objects: " + repr(changed[:10]))
    owners = [m["name"] for m in json.loads((COMBINED / "config/slus_modules.json").read_text())["modules"]]
    if len(owners) != 33:
        raise RuntimeError("combined owner set differs")
    run([str(PYTHON), str(FULL / "prover_cli.py"), "ownership", *owners,
         "--compiler-model-row", MODEL, "--output", str(HERE / "combined_ownership_receipt.json")],
        "combined_ownership", COMBINED)
    ownership = json.loads((HERE / "combined_ownership_receipt.json").read_text())
    if (ownership.get("schema") != 5 or ownership.get("modules") != owners
            or ownership.get("gate", {}).get("result") != "MATCH"
            or ownership.get("compiler_model", {}).get("explicit_rows") != [MODEL]
            or len(ownership.get("data", {})) != 33
            or ownership.get("recipe_sha256") != sha(ninja)):
        raise RuntimeError("combined full ownership scope, model or gate differs")
    certs = {}
    for name in CERTS:
        run([str(PYTHON), str(FULL / "prover_cli.py"), "certificate", name,
             "--reviewer", "codex", "--write"], "combined_certify_" + name, COMBINED)
        target = COMBINED / "ledger/modules" / (name + ".json")
        cert = json.loads(target.read_text())
        if cert.get("module") != name or cert.get("gate", {}).get("result") != "MATCH":
            raise RuntimeError("combined placement certifier failed: " + name)
        certs[name] = {"sha256": sha(target), "schema": cert["schema"],
                       "members": cert["members"]}
    if source_pins() != source or frozen_snapshot() != frozen_before or (
            load_full().production_snapshot() != production_before):
        raise RuntimeError("candidate, frozen fixture or production changed during combined proof")
    if sha(COMBINED / "tools/maspsx/maspsx/__init__.py") != source["retired_package"] or (
            sha(COMBINED / "toolchain/maspsx/maspsx/__init__.py") != source["retired_package"]):
        raise RuntimeError("combined package changed during proof")
    receipt = {"schema": 1, "status": "PASS", "purpose": "private combined GP57 plus sink retirement rehearsal",
        "owners": 33, "ownership_schema": ownership["schema"],
        "measured_rows": len(ownership["rows"]), "physical_objects_rebuilt": len(outputs),
        "all_objects_equal_frozen_gp57": True,
        "normal_ninja_sha256": sha(ninja), "pinned_graph_equal": True,
        "full_image_sha256": sha(image), "full_image_retail_exact": True,
        "explicit_compiler_model_rows": ownership["compiler_model"]["explicit_rows"],
        "ownership_receipt_sha256": sha(HERE / "combined_ownership_receipt.json"),
        "certificates": certs,
        "retired_package_sha256": source["retired_package"],
        "guarded_cli_sha256": source["retired_cli"],
        "source_pins_before_after_sha256": sha(HERE / "combined_source_pins.json"),
        "production_unchanged": True, "frozen_fixture_unchanged": True,
        "logs": {name: sha(HERE / (name + ".log")) for name in
                 ("combined_configure", "combined_rebuild", "combined_ownership",
                  *("combined_certify_" + x for x in CERTS))}}
    write_json(HERE / "combined_receipt.json", receipt)
    print(json.dumps(receipt, indent=2, sort_keys=True), flush=True)


if __name__ == "__main__":
    if len(sys.argv) != 2 or sys.argv[1] not in ("prepare", "prove"):
        raise SystemExit("usage: combined.py {prepare|prove}")
    try:
        globals()[sys.argv[1]]()
    except Exception as exc:
        write_json(HERE / "combined_failure_receipt.json", {
            "status": "ERROR", "phase": sys.argv[1], "type": type(exc).__name__,
            "message": str(exc), "at": time.strftime('%Y-%m-%dT%H:%M:%SZ', time.gmtime())})
        raise
