#!/usr/bin/env python3
"""Private ready18 + CD8 generated-link rehearsal; run only after CD standalone gate."""

from __future__ import annotations

import hashlib
import importlib.util
import json
import os
import re
import shutil
import subprocess
import sys
import traceback
from pathlib import Path


HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
STAGE = HERE / "stage"
READY = ROOT / "work/native_lane/gp_ready18_cd_contract"
CD = ROOT / "work/native_lane/gp_cd_contract/combined8"
CD_LINK = ROOT / "work/native_lane/gp_cd_cohort_link"
GENERIC = ROOT / "work/native_lane/selfinc_local_guard/candidate/maspsx.py"
RECEIPT = HERE / "receipt.json"
LOG = HERE / "build.log"
OWNER = "cd_command_state"
OWNER_STEM = OWNER + "_owned"
OWNER_OBJECT = f"build/src/{OWNER_STEM}.o"
OLD_TUS = ("w_80047E78_owned", "w_80053CFC_owned", "gp_shared_8152c",
           "gp_d92c_owned", "gp_order_bytes_owner", "w_8004437C_pair",
           "w_8003FAD4", "w_80041588", "w_80041AB0", "w_80043CD0",
           "w_8004AB7C", "w_8004DCEC_owned")
GENERIC_TUS = (*OLD_TUS, OWNER_STEM)
WHOLE_STEMS = ("w_8003E34C", "w_8003E4FC", "w_8003E758", "w_8003F2A4",
               "w_8003F368", "w_8003F5AC", "w_8003F624")
PROVENANCE_FILES = ("tools/configure.py", "tools/slus_modules.py",
                    "tools/slus_partitions.py", "tools/slus_data_pieces.py",
                    "tools/cc.sh", "tools/ccproc.py", "include/slus/cd_state.h",
                    "include/slus/cd_cohort_types.h", "config/names.tsv",
                    "config/slus_modules.json", "config/slus_partitions.json",
                    f"src/{OWNER_STEM}.c", *(f"src/{stem}.c" for stem in WHOLE_STEMS))


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def digest_json(value: object) -> str:
    return hashlib.sha256(json.dumps(value, sort_keys=True).encode()).hexdigest()


def read_json(path: Path) -> dict:
    return json.loads(path.read_text())


def load_harness():
    source = CD_LINK / "probe.py"
    spec = importlib.util.spec_from_file_location("private_cd_link_harness", source)
    if spec is None or spec.loader is None:
        raise RuntimeError("standalone CD harness is unavailable")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    if module.ROOT != ROOT or module.CANDIDATE != CD or module.OWNER != OWNER:
        raise RuntimeError("standalone CD harness identity changed")
    return module


def load_ready_probe():
    source = READY / "probe.py"
    spec = importlib.util.spec_from_file_location("private_ready18_probe", source)
    if spec is None or spec.loader is None:
        raise RuntimeError("ready18 proof module is unavailable")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    if module.ROOT != ROOT or module.READY != ROOT / "work/native_lane/gp_ready_combined":
        raise RuntimeError("ready18 proof module identity changed")
    return module


def checked_inputs(H) -> tuple[dict, dict, dict]:
    ready = read_json(READY / "receipt.json")
    direct = read_json(CD / "receipt.json")
    standalone = read_json(CD_LINK / "receipt.json")
    if not ready.get("full_gate") or ready.get("edges", {}).get("physical") != 864:
        raise RuntimeError("ready18 baseline is not the completed 864-object gate")
    if (direct.get("scope") is None or len(direct["scope"]) != 8
            or direct.get("retail_words") != 1041
            or not direct.get("retail_exact_all", {}).get("generic")
            or not direct.get("retail_exact_all", {}).get("genuine")):
        raise RuntimeError("frozen combined-eight direct proof changed")
    if (standalone.get("status") != "MATCH" or not standalone.get("image", {}).get("retail_exact")
            or standalone.get("physical_edges") != 863
            or standalone.get("logical_edges") != 884
            or standalone.get("owner_genuine", {}).get("words") != 1041):
        raise RuntimeError("standalone CD full-link gate has not passed")
    H.candidate_contract(read_json(CD / "module.json"))
    source_hashes = direct["sources"]["inputs_sha256"]
    for name, expected in source_hashes.items():
        if sha(CD.parent / "cohort" / name) != expected:
            raise RuntimeError("combined-eight source drift: " + name)
    for name, key in (("module.json", "module_sha256"),
                      ("candidate_manifest.json", "manifest_sha256"),
                      ("candidate_partitions.json", "partition_plan_sha256")):
        if sha(CD / name) != direct["proposal"][key]:
            raise RuntimeError("combined-eight proposal drift: " + name)
    for name, key in (("cd_command_state_owned.c", "owner_template_sha256"),
                      ("code2__cd_command_state.c", "code2_part_sha256")):
        if sha(CD / name) != direct["sources"][key]:
            raise RuntimeError("combined-eight generated source drift: " + name)
    if sha(CD / "combined8.c") != direct["sources"]["aggregator_sha256"]:
        raise RuntimeError("combined-eight measured source drift")
    for name, expected in direct["sources"]["member_candidates_sha256"].items():
        if sha(CD / "members" / name) != expected:
            raise RuntimeError("combined-eight canonical member drift: " + name)
    if sha(CD.parent / "include/slus/cd_cohort_types.h") != direct["cohort_header_sha256"]:
        raise RuntimeError("combined-eight shared CD header drift")
    if sha(GENERIC) != ready["inputs"]["guarded_cli_sha256"]:
        raise RuntimeError("private generic assembler drifted from ready18 proof")
    if sha(GENERIC.parent / "maspsx/__init__.py") != ready["inputs"]["guarded_package_sha256"]:
        raise RuntimeError("private generic assembler package drifted from ready18 proof")
    for relative, field in (("config/slus_modules.json", "private_manifest_sha256"),
                            ("tools/configure.py", "private_configure_sha256"),
                            ("config/slus_partitions.json", "partition_plan_sha256")):
        if sha(READY / "stage" / relative) != ready[field]:
            raise RuntimeError("retained ready18 stage input drift: " + relative)
    if sha(READY / "stage/build/slus_006.14") != ready["image"]["sha256"]:
        raise RuntimeError("ready18 retained stage image differs from its receipt")
    if sha(CD_LINK / "stage/build/slus_006.14") != standalone["image"]["sha256"]:
        raise RuntimeError("standalone CD retained stage image differs from its receipt")
    for record in ready["genuine"]:
        if (not record["generic_vs_built"]["exact"]
                or not record["generic_vs_genuine"]["exact"]
                or any(x != {"diff": 0, "masked": 0, "checked": len(record["functions"])}
                       for x in record["retail"].values())):
            raise RuntimeError("ready18 per-owner proof is incomplete")
    if len(ready["genuine"]) != 12 or sum(len(x["functions"]) for x in ready["genuine"]) != 18:
        raise RuntimeError("ready18 expected twelve physical TUs/eighteen functions")
    if sum(x["generic_vs_genuine"]["len_m"] for x in ready["genuine"]) != 891:
        raise RuntimeError("ready18 expected 891 proven words")
    before = H.production_snapshot()
    if before != standalone.get("production_after"):
        raise RuntimeError("production baseline differs from reviewed standalone CD gate")
    prior = ready.get("production_after", {})
    if (prior.get("head") != before["head"]
            or prior.get("active_objects") != before["active_objects"]
            or any(sha(ROOT / name) != expected for name, expected in prior.get("files", {}).items())):
        raise RuntimeError("production baseline differs from reviewed ready18 gate")
    return ready, direct, standalone


def private_write(relative: str, content: bytes | str) -> None:
    target = STAGE / relative
    if not target.parent.resolve().is_relative_to(STAGE.resolve()):
        raise RuntimeError("private write escapes cloned stage: " + relative)
    target.parent.mkdir(parents=True, exist_ok=True)
    if target.is_symlink() or target.exists():
        target.unlink()
    target.write_bytes(content if isinstance(content, bytes) else content.encode())


def clone_and_overlay(H) -> tuple[list[dict], list[dict], dict]:
    if STAGE.is_symlink():
        raise RuntimeError("refusing symlink target stage")
    if STAGE.exists():
        shutil.rmtree(STAGE)
    shutil.copytree(READY / "stage", STAGE, symlinks=True)
    H.STAGE, H.HERE = STAGE, HERE
    for directory in ("src", "config", "include", "tools"):
        H.materialize(directory)
    configure = STAGE / "tools/configure.py"
    configure_text = configure.read_text()
    anchor = 'cfiles = sorted(glob.glob("src/*.c"))'
    if configure_text.count(anchor) != 1:
        raise RuntimeError("cannot add seven CD recipe overrides to private configure")
    overrides = "CC_VER.update({\n" + "".join(
        f'    "src/{stem}.c": ("2.7.2-cdk", "-G32"),\n'
        for stem in WHOLE_STEMS) + "})\n"
    private_write("tools/configure.py", configure_text.replace(anchor, overrides + anchor, 1))
    old_code_part = sha(STAGE / "build/partition_sources/code__message_mode_81550.c")
    old_objects = {stem: sha(STAGE / f"build/src/{stem}.o") for stem in OLD_TUS}
    module = read_json(CD / "module.json")
    H.candidate_contract(module)
    private_write(f"src/{OWNER_STEM}.c", (CD / f"{OWNER_STEM}.c").read_bytes())
    for stem in WHOLE_STEMS:
        private_write(f"src/{stem}.c", (CD / "members" / f"{stem}.c").read_bytes())
    private_write("include/slus/cd_cohort_types.h",
                  (CD.parent / "include/slus/cd_cohort_types.h").read_bytes())
    manifest_doc = read_json(STAGE / "config/slus_modules.json")
    if len(manifest_doc["modules"]) != 30 or manifest_doc["modules"][-1]["name"] != "message_mode_81550":
        raise RuntimeError("ready18 manifest baseline changed")
    manifest_doc["modules"].append(module)
    private_write("config/slus_modules.json", json.dumps(manifest_doc, indent=2) + "\n")
    modules = H.load_manifest(STAGE / "config/slus_modules.json")
    if len(modules) != 31 or modules[-1] != module:
        raise RuntimeError("merged module registry is not 31 owners")
    plan_doc = read_json(STAGE / "config/slus_partitions.json")
    code = next(p for p in plan_doc["parents"] if p["id"] == "slus/code")
    code2 = next(p for p in plan_doc["parents"] if p["id"] == "slus/code2")
    if not any(p["module"] == "message_mode_81550" and p["functions"] == ["func_8004DCE0"]
               for p in code["parts"]):
        raise RuntimeError("ready18 DCE0 code partition is absent")
    if any(p["module"] == OWNER for p in code2["parts"]):
        raise RuntimeError("CD code2 part already exists")
    code2["parts"].append({"module": OWNER, "functions": ["func_8003F240"]})
    private_write("config/slus_partitions.json", json.dumps(plan_doc, indent=2) + "\n")
    plan = H.load_plan(STAGE / "config/slus_partitions.json")
    if len(plan) != 2 or len(H.plan_asset_carves(modules, STAGE)) < 1:
        raise RuntimeError("merged partition/data plan did not validate")
    return modules, plan, {"ready18_code_part_sha256": old_code_part,
                           "ready18_generic_objects": old_objects,
                           "stage_initial_image_sha256": sha(STAGE / "build/slus_006.14")}


def scoped_ninja(ninja: str) -> str:
    rule = ("rule cc_guarded_private\n"
            f"  command = AZURE_MASPSX_COMPANION={GENERIC} tools/cc.sh $in $out $ccver "
            "\"$ccflags\" \"$asflags\"$data_piece_step\n"
            "  description = CC-GUARDED-PRIVATE $in\n\n")
    if ninja.count("rule cc\n") != 1 or "$data_piece_step" not in ninja:
        raise RuntimeError("generated compiler rule lacks the reviewed data-piece suffix")
    ninja = ninja.replace("rule cc\n", rule + "rule cc\n", 1)
    for stem in GENERIC_TUS:
        old = f"build build/src/{stem}.o: cc src/{stem}.c"
        new = f"build build/src/{stem}.o: cc_guarded_private src/{stem}.c"
        if ninja.count(old) != 1:
            raise RuntimeError("missing exact generic compiler edge: " + stem)
        ninja = ninja.replace(old, new, 1)
    actual = re.findall(r"(?m)^build build/src/([^\n ]+)\.o: cc_guarded_private ", ninja)
    if len(actual) != 13 or set(actual) != set(GENERIC_TUS):
        raise RuntimeError("selective generic compiler edge set differs")
    return ninja


def graph_proof(H, modules: list[dict], plan: list[dict]) -> tuple[list[dict], dict]:
    configured = H.run("python3", "tools/configure.py")
    partition_render_log = H.run("ninja", "build/partition_sources/code2__cd_command_state.c")
    part = STAGE / "build/partition_sources/code2__cd_command_state.c"
    if part.read_bytes() != (CD / "code2__cd_command_state.c").read_bytes():
        raise RuntimeError("new code2 F240 part differs from frozen private source")
    code_part = STAGE / "build/partition_sources/code__message_mode_81550.c"
    if sha(code_part) != sha(READY / "stage/build/partition_sources/code__message_mode_81550.c"):
        raise RuntimeError("ready18 DCE0 code part changed")
    ninja = scoped_ninja((STAGE / "build.ninja").read_text())
    private_write("build.ninja", ninja)
    physical = H.edges_of(ninja.replace(": cc_guarded_private ", ": cc "))
    ready_graph = (READY / "stage/build.ninja").read_text().replace(": cc_guarded_private ", ": cc ")
    baseline = H.edges_of(ready_graph)
    old_outputs, new_outputs = ({e["out"] for e in group} for group in (baseline, physical))
    removed = {f"build/src/{stem}.o" for stem in WHOLE_STEMS}
    if (len(baseline) != 864 or len(physical) != 858 or old_outputs - new_outputs != removed
            or new_outputs - old_outputs != {OWNER_OBJECT}):
        raise RuntimeError("merged physical graph is not 864 - 7 + 1 = 858")
    logical = H.logical_edges(H.project_edges(physical, plan), modules)
    ready_modules = H.load_manifest(READY / "stage/config/slus_modules.json")
    ready_plan = H.load_plan(READY / "stage/config/slus_partitions.json")
    old_logical = H.logical_edges(H.project_edges(baseline, ready_plan), ready_modules)
    old_by_source = {e["src"]: e for e in old_logical}
    if len(logical) != 884 or len(old_logical) != 884:
        raise RuntimeError("merged logical registry count differs")
    changes = [(edge, old_by_source[edge["src"]]) for edge in logical
               if edge != old_by_source[edge["src"]]]
    if {new["src"] for new, _ in changes} != {f"src/{stem}.c" for stem in WHOLE_STEMS}:
        raise RuntimeError("merged recipe changes exceed seven CD whole rows")
    H.validate_context(plan, modules, logical, STAGE / "raw/slus",
                       H.read_aliases(STAGE / "config/names.tsv"))
    owner_slots = [slot for asset in H.plan_asset_carves(modules, STAGE)
                   for slot in asset["slots"] if slot["kind"] == "module_data"
                   and slot["object"] == OWNER_OBJECT]
    if len(owner_slots) != 11:
        raise RuntimeError("merged asset plan does not have eleven CD slots")
    return physical, {"configure_log": configured.strip(),
                      "partition_render_log": partition_render_log.strip(),
                      "physical": len(physical),
                      "logical": len(logical), "removed_outputs": sorted(removed),
                      "added_output": OWNER_OBJECT,
                      "changed_logical_sources": sorted(new["src"] for new, _ in changes),
                      "owner_asset_slots": len(owner_slots)}


def closure_proof(H, modules: list[dict], plan: list[dict]) -> dict:
    parents, owners = H.connected_context("slus/code2", plan, modules)
    names = {m["name"] for m in owners}
    if {p["id"] for p in parents} != {"slus/code", "slus/code2"} or names != {
            "list_cursor_e0", "saved_value_b98", "sort_rank_81540",
            "command_slots_81554", "message_mode_81550", OWNER}:
        raise RuntimeError("merged collector closure differs")
    expected = H.expected_units(parents, owners)
    counts = {source: len(functions) for source, functions in expected.items()}
    if counts != {"src/code.c": 151, "src/code2.c": 22,
                  "src/w_80041134_owned.c": 3, "src/w_80050DA8_owned.c": 3,
                  "src/sort_rank_81540_owned.c": 2, "src/w_8004DCA8_owned.c": 5,
                  "src/w_8004DCEC_owned.c": 4, f"src/{OWNER_STEM}.c": 8}:
        raise RuntimeError("merged collector emitted scope differs: " + repr(counts))
    emitted = {}
    for source in expected:
        obj = H.read_elf((STAGE / "build/src" / (Path(source).stem + ".o")).read_bytes())
        emitted[source] = [name for name, symbol in obj.symbols.items()
                           if symbol[2] == "func" and symbol[0]
                           and (symbol[0] == ".text" or symbol[0].startswith(".text."))]
    H.check_emitted(expected, emitted)
    if sum(counts.values()) != 198:
        raise RuntimeError("merged collector total function scope differs")
    return {"parents": sorted(p["id"] for p in parents), "owners": sorted(names),
            "function_counts": counts, "total_functions": 198,
            "whole_collector_genuine_claim": False}


def run_rehearsal() -> dict:
    H = load_harness()
    ready, direct, standalone = checked_inputs(H)
    production_before = H.production_snapshot()
    modules, plan, prepared = clone_and_overlay(H)
    physical, graph = graph_proof(H, modules, plan)
    targets = [f"build/src/{stem}.o" for stem in GENERIC_TUS]
    for target in targets:
        path = STAGE / target
        if path.is_symlink():
            raise RuntimeError("private object target is a symlink: " + target)
        if path.exists():
            path.unlink()
    compile_log = H.run("ninja", "-j", "4", *targets)
    (HERE / "compile.log").write_text(compile_log)
    for stem in OLD_TUS:
        if sha(STAGE / f"build/src/{stem}.o") != prepared["ready18_generic_objects"][stem]:
            raise RuntimeError("ready18 generic owner changed under merged build: " + stem)
    owner_path = STAGE / OWNER_OBJECT
    owner_hash_before = sha(owner_path)
    if H.verify_data_pieces(owner_path, modules[-1]) != H.verify_data_pieces(
            CD_LINK / "stage" / OWNER_OBJECT, modules[-1]):
        raise RuntimeError("merged CD data-piece receipt differs from standalone gate")
    link_log = H.run("ninja", "-j", "4", "build/slus_006.14")
    LOG.write_text(link_log)
    if sha(owner_path) != owner_hash_before or f"CC src/{OWNER_STEM}.c" in link_log:
        raise RuntimeError("normal link rebuilt the CD owner")
    gate_log = H.run("ninja", "build/slus_006.14.ok")
    (HERE / "gate.log").write_text(gate_log)
    image = STAGE / "build/slus_006.14"
    retail = ROOT / "baserom/slus_006.14"
    if image.read_bytes() != retail.read_bytes() or not (STAGE / "build/slus_006.14.ok").exists():
        raise RuntimeError("merged image or generated SHA-1 gate differs from retail")
    if sha(owner_path) != owner_hash_before:
        raise RuntimeError("SHA-1 gate changed the CD owner object")
    ready_graph = (READY / "stage/build.ninja").read_text().replace(": cc_guarded_private ", ": cc ")
    old_outputs = {e["out"] for e in H.edges_of(ready_graph)}
    new_outputs = {e["out"] for e in physical}
    outside = sorted((old_outputs & new_outputs) - {"build/src/code2.o"})
    changed = [target for target in outside if sha(STAGE / target) != sha(READY / "stage" / target)]
    if len(outside) != 856 or changed:
        raise RuntimeError("merged outside objects changed: " + repr(changed[:10]))
    data = H.linked_data_proof(modules[-1])
    code2 = H.code2_remainder_proof(plan, modules)
    closure = closure_proof(H, modules, plan)
    R = load_ready_probe()
    R.STAGE = STAGE
    R.HERE = HERE / "r18"
    R.HERE.mkdir(exist_ok=True)
    fresh_ready18_data = R.data_proof(modules[:-1])
    if len(fresh_ready18_data) != 56 or not all(item["exact"] for item in fresh_ready18_data):
        raise RuntimeError("fresh merged ready18 data proof differs")
    fresh_ready18_genuine = R.genuine_proof(modules[:-1])
    if (len(fresh_ready18_genuine) != 12
            or sum(len(item["functions"]) for item in fresh_ready18_genuine) != 18
            or sum(item["generic_vs_genuine"]["len_m"] for item in fresh_ready18_genuine) != 891):
        raise RuntimeError("fresh merged ready18 genuine scope differs")
    for item in fresh_ready18_genuine:
        if (not item["generic_vs_built"]["exact"]
                or not item["generic_vs_genuine"]["exact"]
                or any(value != {"diff": 0, "masked": 0, "checked": len(item["functions"])}
                       for value in item["retail"].values())):
            raise RuntimeError("fresh merged ready18 genuine code differs: " + item["physical"])
    owner_genuine = H.genuine_owner_proof(modules[-1])
    if owner_genuine["words"] != 1041:
        raise RuntimeError("merged CD owner words differ")
    ready_functions = sum(len(x["functions"]) for x in fresh_ready18_genuine)
    ready_words = sum(x["generic_vs_genuine"]["len_m"] for x in fresh_ready18_genuine)
    if (ready_functions, ready_words, ready_functions + len(owner_genuine["functions"]),
            ready_words + owner_genuine["words"]) != (18, 891, 26, 1932):
        raise RuntimeError("merged 26-function/1932-word measured scope differs")
    production_after = H.production_snapshot()
    if production_after != production_before:
        raise RuntimeError("production inputs or objects changed during private rehearsal")
    stage_pins = {name: sha(STAGE / name) for name in PROVENANCE_FILES}
    result = {"status": "MATCH", "baseline_commit": production_before["head"],
              "production_snapshot_sha256": digest_json(production_before),
              "production_unchanged": True,
              "inputs": {"ready18_receipt_sha256": sha(READY / "receipt.json"),
                         "standalone_cd_receipt_sha256": sha(CD_LINK / "receipt.json"),
                         "combined8_receipt_sha256": sha(CD / "receipt.json"),
                         "combined8_source_sha256": direct["sources"],
                         "standalone_harness_sha256": sha(CD_LINK / "probe.py"),
                         "generic_cli_sha256": sha(GENERIC),
                         "stage_input_sha256": stage_pins},
              "prepared": prepared, "graph": graph,
              "selective_generic_tus": list(GENERIC_TUS),
              "owner_object_sha256_before_link": owner_hash_before,
              "owner_object_sha256_after_link": sha(owner_path),
              "image": {"retail_exact": True, "sha256": sha(image),
                        "sha1_gate": True},
              "outside_objects": {"checked": len(outside), "changed": changed},
              "code2_remainder": code2, "connected_closure": closure,
              "fresh_ready18_data": fresh_ready18_data,
              "fresh_ready18_genuine": fresh_ready18_genuine,
              "new_owned_data": data, "owner_genuine": owner_genuine,
              "measured_cohort": {"ready18_functions": ready_functions,
                                  "ready18_words": ready_words,
                                  "cd8_functions": len(owner_genuine["functions"]),
                                  "cd8_words": owner_genuine["words"],
                                  "total_functions": 26, "total_words": 1932},
              "scope_limit": "Selective generic assembly for thirteen physical TUs only."}
    RECEIPT.write_text(json.dumps(result, indent=2, sort_keys=True) + "\n")
    return result


if __name__ == "__main__":
    try:
        result = run_rehearsal()
        print(json.dumps({"status": result["status"], "physical": result["graph"]["physical"],
                          "logical": result["graph"]["logical"],
                          "functions": result["measured_cohort"]["total_functions"],
                          "words": result["measured_cohort"]["total_words"]}, sort_keys=True))
    except Exception as exc:
        RECEIPT.write_text(json.dumps({"status": "ERROR", "error": str(exc),
                                       "traceback": traceback.format_exc()}, indent=2) + "\n")
        raise
