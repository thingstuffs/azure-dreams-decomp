#!/usr/bin/env python3
"""Private eight-function CD owner and unactivated module/partition proposal."""

from __future__ import annotations

import hashlib
import json
import re
import sys
import traceback
from pathlib import Path


HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
COHORT = HERE.parent / "cohort"
FRAGMENTS = HERE / "fragments"
MEMBERS_DIR = HERE / "members"
AGGREGATOR = HERE / "combined8.c"
OWNER = HERE / "cd_command_state_owned.c"
PART_SOURCE = HERE / "code2__cd_command_state.c"
RECEIPT = HERE / "receipt.json"
MODULE = HERE / "module.json"
MANIFEST = HERE / "candidate_manifest.json"
PARTITIONS = HERE / "candidate_partitions.json"
INPUTS = (
    ("e34c", "e34c_driver_view.c", "func_8003E34C"),
    ("e4fc", "w_8003E4FC_owned.c", "func_8003E4FC"),
    ("e758", "e758_prefix_view.c", "func_8003E758"),
    ("f240", "f240_owned.c", "func_8003F240"),
    ("f2a4", "f2a4_queue_view.c", "func_8003F2A4"),
    ("f368", "f368_address_views.c", "func_8003F368"),
    ("f5ac", "f5ac_driver_view.c", "func_8003F5AC"),
    ("f624", "w_8003F624_owned.c", "func_8003F624"),
)
WHOLE_MEMBERS = tuple(item for item in INPUTS if item[0] != "f240")
EXPECTED = sorted(item[2] for item in INPUTS)
RECIPE = {"ccver": "2.7.2-cdk", "ccflags": "-G32", "asflags": ""}
D3_DECLARATIONS = {
    "e758": "extern u8  D_800814D3[2];\n",
    "f368": "extern u8 D_800814D3[2];\n",
    "f624": "extern u8 D_800814D3[8];\n",
}

sys.path.insert(0, str(HERE.parent))
import probe as P  # noqa: E402
import slus_modules as M  # noqa: E402
import slus_partitions as S  # noqa: E402


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def write_json(path: Path, value: dict) -> None:
    path.write_text(json.dumps(value, indent=2, sort_keys=True) + "\n")


def make_sources() -> dict:
    FRAGMENTS.mkdir(exist_ok=True)
    MEMBERS_DIR.mkdir(exist_ok=True)
    private_include = HERE.parent / "include"
    if not (HERE / "include").exists():
        (HERE / "include").symlink_to(private_include, target_is_directory=True)
    if (HERE / "include").resolve() != private_include.resolve():
        raise RuntimeError("combined include view is not the shared private CD header directory")

    first = (COHORT / INPUTS[0][1]).read_text()
    definitions = "".join(first.splitlines(keepends=True)[1:12])
    if len(definitions.splitlines()) != 11 or any(" = " not in s for s in definitions.splitlines()):
        raise RuntimeError("canonical eleven shared definitions changed")
    chunks = ['#include "slus/cd_cohort_types.h"\n', definitions,
              "\nextern u8 D_800814D3[2];\n\n"]
    owner_chunks = list(chunks)
    input_hashes, fragment_hashes, member_hashes = {}, {}, {}
    for short, filename, function in INPUTS:
        source = COHORT / filename
        original = source.read_text()
        if original.count(definitions) != 1:
            raise RuntimeError(filename + ": shared definitions differ or repeat")
        fragment = original.replace(definitions, "", 1)
        d3 = D3_DECLARATIONS.get(short)
        if d3:
            if fragment.count(d3) != 1:
                raise RuntimeError(filename + ": D3 declaration changed")
            fragment = fragment.replace(d3, "", 1)
        name = "Control_CD" if short == "e4fc" else function
        body = re.search(r"(?m)^(?:void|s32|u8)\s+" + name + r"\s*\(", original)
        if body is None:
            raise RuntimeError(filename + ": function start not found")
        suffix = original[body.start():]
        if fragment.count(suffix) != 1 or not fragment.endswith(suffix):
            raise RuntimeError(filename + ": function body was altered")
        path = FRAGMENTS / (short + ".c")
        path.write_text(fragment)
        chunks += ["/* " + filename + " */\n", fragment, "\n"]
        if short == "f240":
            PART_SOURCE.write_text(suffix)
            owner_chunks.append('#include "../build/partition_sources/code2__cd_command_state.c"\n')
        else:
            member_name = "w_" + function[5:] + ".c"
            member_path = MEMBERS_DIR / member_name
            member_path.write_text(fragment)
            member_hashes[member_name] = sha(member_path)
            owner_chunks.append('#include "' + member_name + '"\n')
        input_hashes[filename] = sha(source)
        fragment_hashes[path.name] = sha(path)
    AGGREGATOR.write_text("".join(chunks))
    OWNER.write_text("".join(owner_chunks))
    return {"inputs_sha256": input_hashes, "fragments_sha256": fragment_hashes,
            "member_candidates_sha256": member_hashes,
            "aggregator_sha256": sha(AGGREGATOR),
            "owner_template_sha256": sha(OWNER), "code2_part_sha256": sha(PART_SOURCE),
            "shared_definitions_sha256": hashlib.sha256(definitions.encode()).hexdigest()}


def make_proposal() -> dict:
    module = json.loads((COHORT / "module.json").read_text())
    module.update(name="cd_command_state", source="src/cd_command_state_owned.c",
                  members=[{"id": "slus/w_" + function[5:],
                            "source": "src/w_" + function[5:] + ".c",
                            "functions": [function]}
                           for _, _, function in WHOLE_MEMBERS],
                  headers=["include/common.h", "include/slus/cd_state.h",
                           "include/slus/cd_cohort_types.h"],
                  recipe=RECIPE, evidence="docs/evidence/gp_cd_contract.md")
    write_json(MODULE, module)
    manifest = json.loads((ROOT / "config/slus_modules.json").read_text())
    manifest["modules"].append(module)
    write_json(MANIFEST, manifest)
    plan = json.loads((ROOT / "config/slus_partitions.json").read_text())
    code2 = [parent for parent in plan["parents"] if parent["id"] == "slus/code2"]
    if len(code2) != 1 or any("func_8003F240" in part["functions"] for part in code2[0]["parts"]):
        raise RuntimeError("code2 partition state changed")
    code2[0]["parts"].append({"module": module["name"], "functions": ["func_8003F240"]})
    write_json(PARTITIONS, plan)
    rendered = S.render_parent(code2[0], (ROOT / "src/slus/code2.c").read_text())
    if rendered["parts"][module["name"]] != PART_SOURCE.read_text():
        raise RuntimeError("unchanged code2 F240 partition does not equal candidate function body")
    parsed_modules = M.load_manifest(MANIFEST)
    parsed_plan = S.load_plan(PARTITIONS)
    if len(parsed_modules) != len(manifest["modules"]) or len(parsed_plan) != len(plan["parents"]):
        raise RuntimeError("candidate module or partition schema failed")
    edges = [json.loads(line) for line in (ROOT / "ledger/splits/slus.jsonl").read_text().splitlines()
             if line]
    aliases = S.read_aliases(ROOT / "config/names.tsv")
    S.validate_context(parsed_plan, parsed_modules, edges, ROOT / "raw/slus", aliases)
    if len(M.data_piece_plan(module)) != 11 or len(module["members"]) != 7:
        raise RuntimeError("candidate module coverage differs")
    return {"module_sha256": sha(MODULE), "manifest_sha256": sha(MANIFEST),
            "partition_plan_sha256": sha(PARTITIONS),
            "rendered_code2_part_sha256": sha(PART_SOURCE),
            "candidate_modules": len(parsed_modules), "candidate_parents": len(parsed_plan),
            "partition_context_validated": True,
            "whole_members": [member["id"] for member in module["members"]],
            "code2_part": ["func_8003F240"], "data_pieces": 11}


def concise_retail(item: dict) -> dict:
    result = {key: item.get(key) for key in ("present", "actual_words", "retail_words",
                                           "length_equal", "exact_unmasked")}
    result["masked_count"] = len(item.get("masked_indices", []))
    result["unmasked_mismatch_count"] = len(item.get("unmasked_mismatch_sites", []))
    if "aligned_lcs" in item:
        result["aligned_lcs"] = {key: item["aligned_lcs"].get(key)
                                 for key in ("status", "substitutions", "indels", "total")
                                 if key in item["aligned_lcs"]}
    return result


def main() -> None:
    HERE.mkdir(parents=True, exist_ok=True)
    sources = make_sources()
    proposal = make_proposal()
    P.HERE = HERE
    A = P.A
    A.TMP = ROOT / "work/native_lane/cdj8"
    A.TMP.mkdir(exist_ok=True)
    A.SLUS_ELF = ROOT / "build_slus/build/slus_006.14.elf"
    A.SLUS_BIN = ROOT / "baserom/slus_006.14"
    A._SLUS = None
    stem = "w_8003E758"
    P.RECIPES["src/" + stem + ".c"] = dict(P.RECIPES["src/" + stem + ".c"], **RECIPE)
    legs, report = P.compile_legs(stem, AGGREGATOR, "candidate")
    scope = report["functions"]
    if scope != EXPECTED:
        raise RuntimeError(f"emitted function set differs: {scope}")
    module = json.loads(MODULE.read_text())
    views = {name: A.data_piece_view(view.obj, module) for name, view in legs.items()}
    output = HERE / "objects" / stem / "candidate"
    per_function = {}
    for function in scope:
        extent = P.EXTENTS[function]
        detailed = {name: P.B.retail_detail(view, function, extent, output,
                                            "projected_" + name, P.ALIGN)
                    for name, view in views.items()}
        measured = {name: concise_retail(item) for name, item in detailed.items()}
        per_function[function] = {"retail_words": extent["bytes"] // 4, "legs": measured}
        unmatched = {name: item for name, item in detailed.items() if not item["exact_unmasked"]}
        if unmatched:
            per_function[function]["full_unmatched_retail_detail"] = unmatched
    expected_words = sum(x["retail_words"] for x in per_function.values())
    if expected_words != 1041:
        raise RuntimeError(f"retail scope is {expected_words} words, expected 1041")
    comparison = P.B.compare(views["generic"], views["genuine"], scope)
    exact = {name: all(per_function[f]["legs"][name]["exact_unmasked"] for f in scope)
             for name in legs}
    record = {"status": "MEASURED", "scope": scope, "retail_words": expected_words,
              "recipe": RECIPE, "sources": sources, "proposal": proposal,
              "object_hashes": report["hashes"],
              "cohort_header_sha256": sha(HERE.parent / "include/slus/cd_cohort_types.h"),
              "per_function": per_function,
              "generic_vs_genuine": {k: comparison.get(k) for k in
                                     ("exact", "pair_token_diff_diagnostic", "left_words",
                                      "right_words", "missing_right", "delay_only", "classes")},
              "generic_vs_genuine_regions": comparison.get("regions", [])[:14],
              "retail_exact_all": exact, "production_sources_unchanged": True}
    write_json(RECEIPT, record)
    print(json.dumps({"functions": len(scope), "retail_words": expected_words,
                      "exact": exact}, sort_keys=True), flush=True)
    if not exact["generic"] or not exact["genuine"] or not comparison["exact"]:
        raise RuntimeError("combined eight-function private code is not retail exact")


if __name__ == "__main__":
    try:
        main()
    except Exception as exc:
        if not RECEIPT.exists():
            write_json(RECEIPT, {"status": "ERROR", "error": str(exc),
                                 "traceback": traceback.format_exc()})
        raise
