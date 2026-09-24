#!/usr/bin/env python3
"""Detached normal-build, complete ownership, and retained-placement proof."""

from __future__ import annotations

import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import time

HERE = Path(__file__).resolve().parent
REPO = HERE.parents[3]
STAGE = REPO / "work/native_lane/gp_ready29_collectors/stage"
PAYLOAD = REPO / "work/native_lane/gp_partition_only_tools/transition/payload"
GENERIC = REPO / "work/native_lane/selfinc_local_guard/candidate"
HYGIENE = REPO / "work/native_lane/gp_partition_only_tools/source_hygiene"
CANONICAL = REPO / "work/native_lane/gp_partition_only_tools/canonical_sources"
FIXTURE = HERE / "fixture"
PYTHON = REPO / ".venv/bin/python"
COMPILER_MODEL_ROW = "slus/konami_runtime_w_80033D54"
PLACEMENT = ("list_cursor_e0", "runtime_directory")
STAGE_EXPECTED = {"physical": 860, "logical": 884, "modules": 33, "data": 70}
PIN_FILES = (
    "config/slus_modules.json", "config/slus_partitions.json", "config/names.tsv",
    "ledger/splits/slus.build.ninja", "ledger/splits/slus.jsonl", "ledger/rows.jsonl",
    "src/slus/code.c", "src/slus/code2.c", "tools/build/configure.py",
    "tools/build/slus_modules.py", "tools/build/slus_partitions.py", "tools/row_db.py",
    "tools/slus_module_context.py", "tools/slus_module_evidence.py",
    "tools/fidelity/prove_slus_ownership.py", "tools/fidelity/certify_slus_module.py",
    "tools/fidelity/slus_iso.py", "tools/maspsx/maspsx.py",
    "tools/maspsx/maspsx/__init__.py", "build_slus/build.ninja",
    "build_slus/build/slus_006.14",
)


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def digest_paths(root: Path, paths: list[Path]) -> dict:
    return {str(path.relative_to(root)): sha(path) for path in paths}


def data_files(root: Path) -> list[Path]:
    return sorted(p for p in root.rglob("*") if p.is_file() and not p.is_symlink())


def edges(ninja: str) -> list[str]:
    return re.findall(r"(?m)^build (\S+): cc \S+", ninja)


def production_snapshot() -> dict:
    names = sorted(set(PIN_FILES) | {str(p.relative_to(PAYLOAD)) for p in data_files(PAYLOAD)}
                   | {record["source"] for record in json.loads((HYGIENE / "receipt.json").read_text())["records"]})
    paths = [REPO / name for name in names]
    for name in PIN_FILES:
        if not (REPO / name).is_file():
            raise RuntimeError("missing production input " + name)
    outputs = edges((REPO / "build_slus/build.ninja").read_text())
    objects = [REPO / "build_slus" / name for name in outputs]
    return {"files": {name: sha(path) if path.is_file() else None for name, path in zip(names, paths)},
            "objects": digest_paths(REPO, objects), "physical": len(outputs)}


def transition_pins() -> dict:
    ready = json.loads((STAGE.parent / "receipt.json").read_text())
    if (ready.get("status") != "MATCH" or ready.get("graph", {}).get("physical") != 860
            or ready.get("graph", {}).get("logical") != 884):
        raise RuntimeError("ready29 receipt is not the 860/884 retail-exact stage")
    if sha(STAGE / "build/slus_006.14") != ready["build"]["image_sha256"]:
        raise RuntimeError("ready29 image differs from its receipt")
    if (STAGE / "build/slus_006.14").read_bytes() != (REPO / "baserom/slus_006.14").read_bytes():
        raise RuntimeError("ready29 stage differs from retail")
    payload_files = data_files(PAYLOAD)
    stage_inputs = []
    for name in ("src", "include", "config"):
        stage_inputs.extend(data_files(STAGE / name))
    stage_inputs.extend([STAGE / "build.ninja", STAGE / "build/slus_006.14",
                         STAGE / "build/slus_006.14.elf"])
    stage_outputs = edges((STAGE / "build.ninja").read_text())
    if len(stage_outputs) != 860 or len(set(stage_outputs)) != 860:
        raise RuntimeError("ready29 physical edge set changed")
    stage_objects = [STAGE / name for name in stage_outputs]
    generic = [GENERIC / "maspsx.py", GENERIC / "maspsx/__init__.py"]
    hygiene_receipt = json.loads((HYGIENE / "receipt.json").read_text())
    if hygiene_receipt.get("status") != "MATCH" or any(
            record["compiler_assembly_identical"] is not True or
            sha(STAGE / "src" / Path(record["source"]).name) != record["before_sha256"] or
            sha(HYGIENE / "after" / Path(record["source"]).name) != record["after_sha256"]
            for record in hygiene_receipt["records"]):
        raise RuntimeError("four-source hygiene proof or byte pins changed")
    canonical_receipt = json.loads((CANONICAL / "receipt.json").read_text())
    if canonical_receipt.get("status") != "MATCH_EXCEPT_FILE_METADATA" or len(canonical_receipt.get("proposed_sources", {})) != 4:
        raise RuntimeError("canonical-source proof lacks four reviewed sources")
    if any(record["identical_except_file_metadata"] is not True for record in canonical_receipt["records"]):
        raise RuntimeError("canonical owner compiler streams differ beyond file metadata")
    hygiene_by_source = {Path(record["source"]).name: record for record in hygiene_receipt["records"]}
    for record in canonical_receipt["records"]:
        expected_before = (hygiene_by_source[record["owner"]]["after_sha256"]
                           if record["owner"] in hygiene_by_source
                           else sha(STAGE / "src" / record["owner"]))
        if record["before_source_sha256"] != expected_before:
            raise RuntimeError("canonical owner starting source differs: " + record["owner"])
    if any(sha(CANONICAL / "after" / name) != digest
           for name, digest in canonical_receipt["proposed_sources"].items()):
        raise RuntimeError("canonical source overlay differs from its receipt")
    return {"ready_receipt": sha(STAGE.parent / "receipt.json"),
            "payload": digest_paths(PAYLOAD, payload_files),
            "stage_inputs": digest_paths(STAGE, stage_inputs),
            "stage_objects": digest_paths(STAGE, stage_objects),
            "generic": digest_paths(GENERIC, generic),
            "hygiene_receipt": sha(HYGIENE / "receipt.json"),
            "hygiene": {record["source"]: record["after_sha256"] for record in hygiene_receipt["records"]},
            "canonical_receipt": sha(CANONICAL / "receipt.json"),
            "canonical": {"src/slus/" + name: digest
                          for name, digest in canonical_receipt["proposed_sources"].items()}}


def copy(source: Path, target: Path) -> None:
    target.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(source, target)
    if sha(source) != sha(target):
        raise RuntimeError("copy differs: " + str(target))


def replace_link(path: Path, target: Path) -> None:
    if path.is_symlink() or path.is_file():
        path.unlink()
    elif path.is_dir():
        shutil.rmtree(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.symlink_to(target, target_is_directory=True)
    if path.resolve() != target.resolve():
        raise RuntimeError("private link differs: " + str(path))


def write_json(path: Path, value: dict) -> None:
    path.write_text(json.dumps(value, indent=2, sort_keys=True) + "\n")


def run(args: list[str], label: str, cwd: Path) -> None:
    print("START " + label, flush=True)
    env = dict(os.environ)
    for name in ("AZURE_MASPSX", "AZURE_MASPSX_COMPANION", "PYTHONPATH"):
        env.pop(name, None)
    start = time.monotonic()
    with (HERE / (label + ".log")).open("w") as log:
        result = subprocess.run(args, cwd=cwd, env=env, stdout=log, stderr=subprocess.STDOUT)
    if result.returncode:
        print((HERE / (label + ".log")).read_text()[-5000:], flush=True)
        raise RuntimeError(label + " failed with rc=" + str(result.returncode))
    print("PASS " + label + " in " + str(round(time.monotonic() - start, 1)) + "s", flush=True)


def prepare() -> None:
    if FIXTURE.exists() or FIXTURE.is_symlink():
        raise RuntimeError("private fixture already exists; refusing overwrite")
    if (HERE / ".ignore").read_text() != "*\n":
        raise RuntimeError("missing ignore guard for large private artifacts")
    before = production_snapshot()
    if before["physical"] != 869:
        raise RuntimeError("production baseline is no longer 869 physical outputs")
    pins = transition_pins()
    ignored = shutil.ignore_patterns("__pycache__", "*.pyc")
    FIXTURE.mkdir()
    shutil.copytree(REPO / "tools", FIXTURE / "tools", ignore=ignored)
    shutil.copytree(STAGE, FIXTURE / "build_slus", symlinks=True, ignore=ignored)
    shutil.copytree(STAGE / "src", FIXTURE / "src/slus", ignore=ignored)
    shutil.copytree(STAGE / "include", FIXTURE / "include", ignore=ignored)
    shutil.copytree(STAGE / "config", FIXTURE / "config", ignore=ignored)
    shutil.copytree(REPO / "raw/slus", FIXTURE / "raw/slus", ignore=ignored)
    shutil.copytree(REPO / "raw/include", FIXTURE / "raw/include", ignore=ignored)
    shutil.copytree(REPO / "ledger/cache/slus_dis", FIXTURE / "ledger/cache/slus_dis", ignore=ignored)
    copy(REPO / "ledger/cache/slus_obj.json", FIXTURE / "ledger/cache/slus_obj.json")
    copy(REPO / "PIN", FIXTURE / "PIN")
    for name in ("noreturn_syms", "sibcall_syms"):
        for source in sorted((REPO / "config").glob(name + "*.txt")):
            copy(source, FIXTURE / "config" / source.name)
    for source in sorted((REPO / "config/overlays").glob("*.as_flags.jsonl")):
        copy(source, FIXTURE / "config/overlays" / source.name)
    for name in ("tools/match.py", "tools/overlay_as_flags.py", "tools/overlay_evidence.py",
                 "tools/rowbase.py", "work/g3/overlay_func_compare.py", "config/names.tsv"):
        copy(REPO / "build_ovl" / name, FIXTURE / "build_ovl" / name)
    for name in PLACEMENT:
        module = next(m for m in json.loads((PAYLOAD / "config/slus_modules.json").read_text())["modules"]
                      if m["name"] == name)
        copy(REPO / module["evidence"], FIXTURE / module["evidence"])
    for source in data_files(PAYLOAD):
        relative = source.relative_to(PAYLOAD)
        copy(source, FIXTURE / relative)
        if relative.parts[0] == "config":
            copy(source, FIXTURE / "build_slus" / relative)
        if relative == Path("tools/build/configure.py"):
            copy(source, FIXTURE / "build_slus/tools/configure.py")
    for name, digest in pins["hygiene"].items():
        target = FIXTURE / name
        copy(HYGIENE / "after" / Path(name).name, target)
        if sha(target) != digest:
            raise RuntimeError("hygiene source copy differs: " + name)
    for name, digest in pins["canonical"].items():
        target = FIXTURE / name
        copy(CANONICAL / "after" / Path(name).name, target)
        if sha(target) != digest:
            raise RuntimeError("canonical source copy differs: " + name)
    shutil.copytree(REPO / "tools/maspsx", FIXTURE / "toolchain/maspsx", ignore=ignored)
    for name in ("maspsx.py", "maspsx/__init__.py"):
        copy(GENERIC / name, FIXTURE / "tools/maspsx" / name)
        copy(GENERIC / name, FIXTURE / "toolchain/maspsx" / name)
    (FIXTURE / "toolchain/compilers").symlink_to(REPO / "toolchain/compilers", target_is_directory=True)
    (FIXTURE / "toolchain/genuine").symlink_to(REPO / "toolchain/genuine", target_is_directory=True)
    (FIXTURE / ".venv").symlink_to(REPO / ".venv", target_is_directory=True)
    (FIXTURE / "baserom").symlink_to(REPO / "baserom", target_is_directory=True)
    for name, target in (("tools", FIXTURE / "tools/build"),
                         ("include", FIXTURE / "include"),
                         ("toolchain", FIXTURE / "toolchain"),
                         ("baserom", FIXTURE / "baserom"),
                         (".venv", FIXTURE / ".venv"),
                         ("raw/slus", FIXTURE / "raw/slus")):
        replace_link(FIXTURE / "build_slus" / name, target)
    src_view = FIXTURE / "build_slus/src"
    shutil.rmtree(src_view)
    src_view.mkdir()
    for source in sorted((FIXTURE / "src/slus").iterdir()):
        (src_view / source.name).symlink_to(source)
    (FIXTURE / "build_slus/.partition_src_view").write_text(
        "canonical per-file symlinks for SLUS partitions\n")
    for name, digest in pins["payload"].items():
        if name in pins["hygiene"] or name in pins["canonical"]:
            continue
        if sha(FIXTURE / name) != digest:
            raise RuntimeError("payload copy differs: " + name)
    for name, digest in pins["generic"].items():
        relative = Path(name)
        if sha(FIXTURE / "tools/maspsx" / relative) != digest or sha(FIXTURE / "toolchain/maspsx" / relative) != digest:
            raise RuntimeError("guarded generic copy differs: " + name)
    if sha(FIXTURE / "build_slus/build.ninja") != sha(PAYLOAD / "ledger/splits/slus.build.ninja"):
        raise RuntimeError("stage build graph and payload ledger differ")
    write_json(HERE / "production_before.json", before)
    write_json(HERE / "input_pins.json", pins)
    write_json(HERE / "prepare_receipt.json", {"schema": 1, "status": "PREPARED",
        "fixture": str(FIXTURE.relative_to(REPO)), "ready29_image_sha256": sha(STAGE / "build/slus_006.14"),
        "payload_files": len(pins["payload"]), "hygiene_sources": len(pins["hygiene"]),
        "canonical_sources": len(pins["canonical"]),
        "stage_objects": len(pins["stage_objects"]),
        "production_unchanged": production_snapshot() == before})
    if production_snapshot() != before or transition_pins() != pins:
        raise RuntimeError("source or production changed during fixture preparation")
    print("PREPARED 33-owner detached fixture", flush=True)


def refresh_canonical() -> None:
    """Refresh only the four canonical source organization files after a baseline run."""
    if not FIXTURE.is_dir() or not (HERE / "input_pins.json").is_file():
        raise RuntimeError("private fixture is not prepared")
    old = json.loads((HERE / "input_pins.json").read_text())
    current = transition_pins()
    if {k: v for k, v in current.items() if k not in ("canonical", "canonical_receipt")} != old:
        raise RuntimeError("other transition inputs changed before canonical source refresh")
    before = json.loads((HERE / "production_before.json").read_text())
    if production_snapshot() != before:
        raise RuntimeError("production changed before canonical source refresh")
    receipt = json.loads((CANONICAL / "receipt.json").read_text())
    for record in receipt["records"]:
        name = "src/slus/" + record["owner"]
        if sha(FIXTURE / name) != record["before_source_sha256"]:
            raise RuntimeError("private owner source is not canonical overlay predecessor: " + name)
    for name, digest in current["canonical"].items():
        copy(CANONICAL / "after" / Path(name).name, FIXTURE / name)
        if sha(FIXTURE / name) != digest or sha(FIXTURE / "build_slus/src" / Path(name).name) != digest:
            raise RuntimeError("canonical private source view differs: " + name)
    write_json(HERE / "input_pins.json", current)
    write_json(HERE / "canonical_refresh_receipt.json", {
        "status": "REFRESHED", "canonical_receipt_sha256": current["canonical_receipt"],
        "sources": current["canonical"], "production_unchanged": production_snapshot() == before})
    print("REFRESHED four canonical source files", flush=True)


def rebind_final_payload() -> None:
    """Bind the routing refresh only after it matches the reviewed canonical overlay."""
    old_prod = json.loads((HERE / "production_before.json").read_text())
    old_pins = json.loads((HERE / "input_pins.json").read_text())
    current_prod = production_snapshot()
    current_pins = transition_pins()
    if old_prod["physical"] != current_prod["physical"] or old_prod["objects"] != current_prod["objects"]:
        raise RuntimeError("production build or objects changed during routing refresh")
    if any(current_prod["files"].get(name) != digest for name, digest in old_prod["files"].items()):
        raise RuntimeError("previously monitored production file changed")
    new_production_keys = set(current_prod["files"]) - set(old_prod["files"])
    expected_new = {"src/slus/w_8003D92C.c", "src/slus/w_80049F68.c"}
    if new_production_keys != expected_new:
        raise RuntimeError("unexpected expansion of production snapshot: " + repr(new_production_keys))
    subprocess.run(["git", "diff", "--quiet", "HEAD", "--", *sorted(new_production_keys)],
                   cwd=REPO, check=True)
    changes = {key: {name for name in current_pins[key].keys() | old_pins[key].keys()
                     if current_pins[key].get(name) != old_pins[key].get(name)}
               for key in current_pins.keys() | old_pins.keys()
               if isinstance(current_pins.get(key), dict) and isinstance(old_pins.get(key), dict)}
    if {key: value for key, value in changes.items() if value} != {"payload": set(current_pins["canonical"])}:
        raise RuntimeError("payload changed outside four canonical source files: " + repr(changes))
    if any(current_pins["payload"][name] != digest or sha(FIXTURE / name) != digest
           for name, digest in current_pins["canonical"].items()):
        raise RuntimeError("final payload is not the exact pinned canonical overlay")
    write_json(HERE / "production_before.json", current_prod)
    write_json(HERE / "input_pins.json", current_pins)
    write_json(HERE / "final_payload_rebind_receipt.json", {
        "status": "REBOUND", "routing_updated_sources": sorted(current_pins["canonical"]),
        "production_snapshot_new_tracked_keys": sorted(new_production_keys),
        "other_candidate_inputs_unchanged": True, "production_unchanged": True})
    print("REBOUND exact canonical source payload and expanded production watch", flush=True)


def prove() -> None:
    if not (HERE / "prepare_receipt.json").is_file():
        raise RuntimeError("prepare first")
    before = json.loads((HERE / "production_before.json").read_text())
    pins = json.loads((HERE / "input_pins.json").read_text())
    if production_snapshot() != before or transition_pins() != pins:
        raise RuntimeError("production or candidate inputs changed before private proof")
    if sha(FIXTURE / "build_slus/build.ninja") != sha(FIXTURE / "ledger/splits/slus.build.ninja"):
        raise RuntimeError("private recipe changed before configure")
    run([str(PYTHON), "tools/configure.py"], "configure", FIXTURE / "build_slus")
    ninja_path = FIXTURE / "build_slus/build.ninja"
    if ninja_path.read_bytes() != (FIXTURE / "ledger/splits/slus.build.ninja").read_bytes():
        raise RuntimeError("normal generated Ninja differs from complete pinned ledger")
    if ninja_path.read_bytes() != (STAGE / "build.ninja").read_bytes():
        raise RuntimeError("normal generated Ninja differs from retail-exact ready29 graph")
    sys.path[:0] = [str(FIXTURE / "tools"), str(FIXTURE / "tools/build")]
    from row_db import edges_of
    from slus_modules import load_manifest, logical_edges
    from slus_partitions import load_plan, project_edges, read_aliases, validate_context
    modules = load_manifest(FIXTURE / "config/slus_modules.json")
    plan = load_plan(FIXTURE / "config/slus_partitions.json")
    physical = edges_of(ninja_path.read_text())
    logical = logical_edges(project_edges(physical, plan), modules)
    pinned = [json.loads(line) for line in (FIXTURE / "ledger/splits/slus.jsonl").read_text().splitlines() if line]
    if len(modules) != 33 or len(physical) != 860 or len(logical) != 884 or logical != pinned:
        raise RuntimeError("complete manifest/physical/logical ledger projection differs")
    validate_context(plan, modules, logical, FIXTURE / "raw/slus",
                     read_aliases(FIXTURE / "config/names.tsv"))
    if sum(len(m["data"]) for m in modules) != 70:
        raise RuntimeError("not all 70 data records are registered")
    registry = [json.loads(line) for line in (FIXTURE / "ledger/rows.jsonl").read_text().splitlines() if line]
    if len(registry) != 6767 or {row["id"] for row in registry} != {row["id"] for row in
            (json.loads(line) for line in (REPO / "ledger/rows.jsonl").read_text().splitlines() if line)}:
        raise RuntimeError("complete registry row identities differ")
    run(["ninja", "-C", str(FIXTURE / "build_slus"), "-j", "2", "build/slus_006.14"],
        "normal_build", FIXTURE)
    image = FIXTURE / "build_slus/build/slus_006.14"
    if image.read_bytes() != (REPO / "baserom/slus_006.14").read_bytes():
        raise RuntimeError("normal private build did not match the full retail image")
    stage_objects = pins["stage_objects"]
    changed_objects = [name for name, digest in stage_objects.items()
                       if sha(FIXTURE / "build_slus" / name) != digest]
    expected_metadata_objects = {"build/src/gp_d92c_owned.o", "build/src/gp_order_bytes_owner.o"}
    if set(changed_objects) - expected_metadata_objects:
        raise RuntimeError("normal build objects differ beyond canonical owner metadata: " + repr(changed_objects[:8]))
    from fidelity.objread import read_elf
    material = {}
    for name in sorted(expected_metadata_objects):
        old = read_elf((STAGE / name).read_bytes())
        new = read_elf((FIXTURE / "build_slus" / name).read_bytes())
        checks = {"allocated_sections": old.sections == new.sections,
                  "relocations": old.relocs == new.relocs,
                  "symbols": old.symbols == new.symbols,
                  "unknown_relocations": old.unknown == new.unknown}
        if not all(checks.values()):
            raise RuntimeError("canonical owner object changed allocated bytes, relocations or symbols: " + name + " " + repr(checks))
        material[name] = {"stage_sha256": stage_objects[name],
                          "normal_build_sha256": sha(FIXTURE / "build_slus" / name),
                          "exact_material": checks}
    owners = [module["name"] for module in modules]
    run([str(PYTHON), str(HERE / "prover_cli.py"), "ownership", *owners,
         "--compiler-model-row", COMPILER_MODEL_ROW,
         "--output", str(HERE / "ownership_receipt.json")], "ownership", FIXTURE)
    ownership = json.loads((HERE / "ownership_receipt.json").read_text())
    if (ownership.get("schema") != 5 or ownership.get("modules") != owners
            or ownership.get("gate", {}).get("result") != "MATCH"
            or ownership.get("compiler_model", {}).get("explicit_rows") != [COMPILER_MODEL_ROW]
            or ownership.get("recipe_sha256") != sha(ninja_path)
            or ownership.get("image_sha1") != hashlib.sha1(image.read_bytes()).hexdigest()):
        raise RuntimeError("full ownership receipt lacks the required scope or gate")
    if len(ownership.get("data", {})) != 33 or not ownership.get("rows"):
        raise RuntimeError("full ownership receipt omitted owner data or measured rows")
    certificates = {}
    for name in PLACEMENT:
        run([str(PYTHON), str(HERE / "prover_cli.py"), "certificate", name,
             "--reviewer", "codex", "--write"], "certify_" + name, FIXTURE)
        path = FIXTURE / "ledger/modules" / (name + ".json")
        cert = json.loads(path.read_text())
        if cert.get("module") != name or cert.get("gate", {}).get("result") != "MATCH":
            raise RuntimeError("placement recertification lacks private match: " + name)
        certificates[name] = {"sha256": sha(path), "schema": cert["schema"],
                              "members": cert["members"], "gate": cert["gate"]}
    after = production_snapshot()
    if before != after or transition_pins() != pins:
        raise RuntimeError("production or proposed input bytes changed during proof")
    for name, digest in pins["payload"].items():
        if name in pins["hygiene"] or name in pins["canonical"]:
            continue
        if sha(FIXTURE / name) != digest:
            raise RuntimeError("fixture payload input changed during proof: " + name)
    for name, digest in pins["hygiene"].items():
        if name in pins["canonical"]:
            continue
        if sha(FIXTURE / name) != digest:
            raise RuntimeError("fixture hygiene source changed during proof: " + name)
    for name, digest in pins["canonical"].items():
        if sha(FIXTURE / name) != digest:
            raise RuntimeError("fixture canonical source changed during proof: " + name)
    receipt = {"schema": 1, "status": "PASS", "purpose": "private final transition proof",
        "modules": len(owners), "physical": len(physical), "logical": len(logical),
        "registry": len(registry), "data_records": 70,
        "normal_generated_ninja_sha256": sha(ninja_path), "pinned_ninja_equal": True,
        "normal_image_sha256": sha(image), "normal_image_retail_exact": True,
        "normal_objects_equal_ready29_except_file_metadata": len(set(changed_objects) - expected_metadata_objects) == 0,
        "canonical_owner_object_material": material,
        "ownership_schema": ownership["schema"], "ownership_rows": len(ownership["rows"]),
        "ownership_receipt_sha256": sha(HERE / "ownership_receipt.json"),
        "compiler_model_explicit_rows": ownership["compiler_model"]["explicit_rows"],
        "placement_certificates": certificates, "production_unchanged": True,
        "source_input_pins_sha256": sha(HERE / "input_pins.json"),
        "prover_cli_wrapper_sha256": sha(HERE / "prover_cli.py"),
        "hygiene_receipt_sha256": pins["hygiene_receipt"],
        "canonical_receipt_sha256": pins["canonical_receipt"],
        "logs": {name: sha(HERE / (name + ".log")) for name in
                 ("configure", "normal_build", "ownership", *("certify_" + x for x in PLACEMENT))}}
    write_json(HERE / "receipt.json", receipt)
    print(json.dumps(receipt, indent=2, sort_keys=True), flush=True)


def postflight() -> None:
    """Persist the independently readable end-state hash snapshots."""
    receipt_path = HERE / "receipt.json"
    if not receipt_path.is_file():
        raise RuntimeError("full proof receipt is absent")
    receipt = json.loads(receipt_path.read_text())
    if receipt.get("status") != "PASS" or receipt.get("modules") != 33:
        raise RuntimeError("full proof receipt is incomplete")
    before_prod = json.loads((HERE / "production_before.json").read_text())
    before_pins = json.loads((HERE / "input_pins.json").read_text())
    after_prod = production_snapshot()
    after_pins = transition_pins()
    if after_prod != before_prod or after_pins != before_pins:
        raise RuntimeError("production or candidate inputs changed after final proof")
    write_json(HERE / "production_after.json", after_prod)
    write_json(HERE / "input_pins_after.json", after_pins)
    if sha(HERE / "production_before.json") != sha(HERE / "production_after.json"):
        raise RuntimeError("production before/after hash files differ")
    if sha(HERE / "input_pins.json") != sha(HERE / "input_pins_after.json"):
        raise RuntimeError("candidate input before/after hash files differ")
    receipt["postflight"] = {
        "at": time.strftime('%Y-%m-%dT%H:%M:%SZ', time.gmtime()),
        "production_before_after_sha256": sha(HERE / "production_before.json"),
        "source_tool_input_before_after_sha256": sha(HERE / "input_pins.json"),
        "production_equal": True, "candidate_inputs_equal": True,
        "final_payload_files": len(after_pins["payload"]),
        "stage_objects_pinned": len(after_pins["stage_objects"]),
    }
    write_json(receipt_path, receipt)
    print("POSTFLIGHT source/tool/input and production hashes equal", flush=True)


if __name__ == "__main__":
    if len(sys.argv) != 2 or sys.argv[1] not in ("prepare", "refresh_canonical", "rebind_final_payload", "prove", "postflight"):
        raise SystemExit("usage: run.py {prepare|refresh_canonical|rebind_final_payload|prove|postflight}")
    try:
        globals()[sys.argv[1]]()
    except Exception as exc:
        write_json(HERE / "failure_receipt.json", {"status": "ERROR", "phase": sys.argv[1],
            "type": type(exc).__name__, "message": str(exc), "at": time.strftime('%Y-%m-%dT%H:%M:%SZ', time.gmtime())})
        raise
