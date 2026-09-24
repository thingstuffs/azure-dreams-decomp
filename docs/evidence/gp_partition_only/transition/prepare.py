#!/usr/bin/env python3
"""Build a private, reviewable ready29 GP transition patch; never edit production."""

from __future__ import annotations

from collections import Counter
import difflib
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
STAGE = ROOT / "work/native_lane/gp_ready29_collectors/stage"
READY = ROOT / "work/native_lane/gp_ready29_collectors"
TOOLS = ROOT / "work/native_lane/gp_partition_only_tools"
CAND = TOOLS / "candidate/tools"
CENSUS = TOOLS / "census_fixture"
ASM_TESTS = TOOLS / "assembler_tests_candidate"
HYGIENE = TOOLS / "source_hygiene"
CANONICAL = TOOLS / "canonical_sources"
GUARD = ROOT / "work/native_lane/selfinc_local_guard/candidate"
FIXTURE = HERE / "configure_fixture"
PAYLOAD = HERE / "payload"
CHECKROOT = HERE / "patch_checkroot"
PATCH = HERE / "transition.patch"
INVENTORY = HERE / "inventory.json"
BASELINE = "b4130ec4d7ab9500e86a594aa3606b71fa1611b6"
ASSEMBLER_HASHES = {
    "tools/maspsx/maspsx.py": "d3e6ec7d120abe00f963c82258dfdeb0e228774adce646177525f1dbed925caf",
    "tools/maspsx/maspsx/__init__.py": "28e45bbcf00fc90dc0645250f233b73f96ad11d06a2f8230ce533fc2fafbbfbe",
}
ASM_TEST_NAMES = (
    "test_branch_delay_lui.py", "test_casesi_jumptable.py",
    "test_funcaddr_split.py", "test_funcaddr_split_branch_delay.py",
    "test_main_endgame_closures.py", "test_store_delay.py",
    "test_uses_gp_extern.py",
)


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def file_sha(path: Path) -> str:
    return sha(path.read_bytes())


def read_json(path: Path):
    return json.loads(path.read_text())


def relative(path: Path) -> str:
    return str(path.relative_to(ROOT))


def pinned_inputs() -> dict:
    head = subprocess.check_output(["git", "rev-parse", "HEAD"], cwd=ROOT, text=True).strip()
    if head != BASELINE:
        changed = subprocess.check_output(
            ["git", "diff", "--name-only", BASELINE, head], cwd=ROOT, text=True).splitlines()
        if not changed or any(not name.startswith("docs/") for name in changed):
            raise RuntimeError("production code changed after reviewed baseline: " + repr(changed))
    ready = read_json(READY / "receipt.json")
    if (ready.get("status") != "MATCH" or ready["graph"]["physical"] != 860
            or ready["graph"]["logical"] != 884 or ready["measured"] != {
                "functions": 29, "words": 1949, "data_records": 70,
                "genuine_version": "2.79", "retail_masks": 0}):
        raise RuntimeError("ready29 retail/genuine/data receipt differs")
    if (file_sha(STAGE / "build/slus_006.14") != ready["build"]["image_sha256"]
            or not ready["build"]["retail_exact"] or not ready["build"]["sha1_gate"]):
        raise RuntimeError("ready29 image does not match its full gate")
    pins = read_json(TOOLS / "tool_pins.json")
    if len(pins) != 9:
        raise RuntimeError("expected nine frozen tool candidates")
    for target, digest in pins.items():
        if file_sha(CAND / target.removeprefix("tools/")) != digest:
            raise RuntimeError("frozen tool candidate changed: " + target)
    for target, digest in ASSEMBLER_HASHES.items():
        path = GUARD / target.removeprefix("tools/maspsx/")
        if file_sha(path) != digest:
            raise RuntimeError("guarded generic assembler changed: " + target)
    portable = read_json(TOOLS / "portable_regression_receipt.json")
    if portable["status"] != "PASS" or portable["total"] != {
            "tests": 187, "passed": 187, "failed": 0, "errors": 0, "skipped": 0}:
        raise RuntimeError("portable nine-tool regression differs")
    asm_receipt = read_json(ASM_TESTS / "receipt.json")
    if (asm_receipt["status"] != "PRIVATE_TEST_MIGRATION_PASS"
            or asm_receipt["runs"]["private_candidate"]["tests"] != 418
            or asm_receipt["runs"]["private_candidate"]["failures"] != 0):
        raise RuntimeError("guarded assembler candidate unit proof differs")
    for name in ASM_TEST_NAMES:
        record = asm_receipt["test_updates"]["modified_files"][name]
        if file_sha(ASM_TESTS / "tools/maspsx/tests" / name) != record["private_sha256"]:
            raise RuntimeError("assembler test candidate changed: " + name)
        if file_sha(ROOT / "tools/maspsx/tests" / name) != record["production_sha256"]:
            raise RuntimeError("production assembler test baseline changed: " + name)
    census = read_json(CENSUS / "census_setup_receipt.json")
    if (census["status"] != "PREPARED" or census["ready29_stage_sha256"] !=
            ready["build"]["image_sha256"]
            or census["counts"]["slus"] != 884):
        raise RuntimeError("complete registry fixture differs")
    if file_sha(CENSUS / "ledger/rows.jsonl") != census["registry_sha256"]:
        raise RuntimeError("complete registry rows hash differs")
    if file_sha(CENSUS / "ledger/splits/slus.build.ninja") != file_sha(STAGE / "build.ninja"):
        raise RuntimeError("census pinned Ninja differs from ready29")
    return {
        "code_baseline_commit": BASELINE,
        "current_docs_only_commit": head,
        "ready29_receipt_sha256": file_sha(READY / "receipt.json"),
        "ready29_stage_image_sha256": ready["build"]["image_sha256"],
        "ready29_stage_ninja_sha256": file_sha(STAGE / "build.ninja"),
        "nine_tool_candidate_sha256": pins,
        "guarded_assembler_sha256": ASSEMBLER_HASHES,
        "portable_regression_receipt_sha256": file_sha(TOOLS / "portable_regression_receipt.json"),
        "assembler_test_receipt_sha256": file_sha(ASM_TESTS / "receipt.json"),
        "census_setup_receipt_sha256": file_sha(CENSUS / "census_setup_receipt.json"),
        "source_hygiene_receipt_sha256": file_sha(HYGIENE / "receipt.json"),
        "source_hygiene_reproducer_sha256": file_sha(HYGIENE / "reproduce.py"),
        "source_hygiene_reproduction_receipt_sha256": file_sha(HYGIENE / "reproduction_receipt.json"),
        "canonical_source_probe_sha256": file_sha(CANONICAL / "probe.py"),
        "canonical_source_receipt_sha256": file_sha(CANONICAL / "receipt.json"),
    }


def verify_final_configure() -> dict:
    stage_text = (STAGE / "tools/configure.py").read_text()
    core_text = (CAND / "build/configure.py").read_text()
    anchor = 'cfiles = sorted(glob.glob("src/*.c"))'
    if stage_text.count(anchor) != 1 or core_text.count(anchor) != 1:
        raise RuntimeError("final configure anchor differs")
    scoped = stage_text.split('CC_VER.update({', 1)[1].split(anchor, 1)[0]
    override = 'CC_VER.update({' + scoped
    recipe_lines = re.findall(r'(?m)^    "src/[^\n]+": \("2\.7\.2-cdk",', override)
    if override.count("CC_VER.update({") != 2 or len(recipe_lines) != 15:
        raise RuntimeError("ready29 final compiler policy is not the exact fifteen overrides")
    if stage_text.replace(override, "", 1) != core_text:
        raise RuntimeError("ready29 final configure is not frozen core plus the fifteen overrides")
    if file_sha(FIXTURE / "build.ninja") != file_sha(STAGE / "build.ninja"):
        raise RuntimeError("fresh configure fixture did not reproduce ready29 Ninja")
    if file_sha(CENSUS / "ledger/splits/slus.build.ninja") != file_sha(FIXTURE / "build.ninja"):
        raise RuntimeError("census pinned Ninja differs from fresh configure fixture")
    return {
        "core_candidate_sha256": file_sha(CAND / "build/configure.py"),
        "final_policy_sha256": file_sha(STAGE / "tools/configure.py"),
        "recipe_override_count": len(recipe_lines),
        "fresh_generated_ninja_sha256": file_sha(FIXTURE / "build.ninja"),
        "ready29_ninja_byte_equal": True,
    }


def projected_rows() -> dict:
    sys.path[:0] = [str(CAND), str(CAND / "build"), str(ROOT / "tools")]
    from row_db import edges_of
    from slus_modules import load_manifest, logical_edges, plan_asset_carves
    from slus_partitions import load_plan, project_edges, validate_context, read_aliases
    ninja = (STAGE / "build.ninja").read_text()
    modules = load_manifest(STAGE / "config/slus_modules.json")
    plan = load_plan(STAGE / "config/slus_partitions.json")
    physical = edges_of(ninja)
    logical = logical_edges(project_edges(physical, plan), modules)
    census_edges = [json.loads(line) for line in
                    (CENSUS / "ledger/splits/slus.jsonl").read_text().splitlines() if line]
    if len(physical) != 860 or len(logical) != 884 or logical != census_edges:
        raise RuntimeError("full logical SLUS projection differs from candidate census")
    validate_context(plan, modules, logical, STAGE / "raw/slus",
                     read_aliases(STAGE / "config/names.tsv"))
    previous = [json.loads(line) for line in
                (ROOT / "ledger/splits/slus.jsonl").read_text().splitlines() if line]
    if len(previous) != 884 or {x["src"] for x in logical} != {x["src"] for x in previous}:
        raise RuntimeError("logical source identities changed")
    old_by_src = {x["src"]: x for x in previous}
    recipe_changes = [x["src"] for x in logical if x != old_by_src[x["src"]]]
    if len(recipe_changes) != 15 or any(
            x["asflags"] != old_by_src[x["src"]]["asflags"] for x in logical):
        raise RuntimeError("unexpected compiler policy or assembler-flag changes")
    data = [(m["name"], d) for m in modules for d in m["data"]]
    if len(modules) != 33 or len(data) != 70 or len({d["symbol"] for _, d in data}) != 70:
        raise RuntimeError("data registry count or symbol ownership differs")
    by_asset = {}
    for module, datum in data:
        by_asset.setdefault(datum["asset"], []).append((datum["offset"], datum["offset"] + datum["size"],
                                                         module, datum["symbol"]))
    for asset, items in by_asset.items():
        items.sort()
        if any(a[1] > b[0] for a, b in zip(items, items[1:])):
            raise RuntimeError("overlapping owned data records in " + asset)
    plan_asset_carves(modules, STAGE)
    all_rows = [json.loads(line) for line in
                (CENSUS / "ledger/rows.jsonl").read_text().splitlines() if line]
    previous_rows = [json.loads(line) for line in
                     (ROOT / "ledger/rows.jsonl").read_text().splitlines() if line]
    if (len(all_rows) != 6767 or len(previous_rows) != 6767
            or {x["id"] for x in all_rows} != {x["id"] for x in previous_rows}):
        raise RuntimeError("complete registry row identities differ")
    original = {x["id"]: x for x in previous_rows}
    changed = [x["id"] for x in all_rows if x != original[x["id"]]]
    if changed != ["slus/" + Path(source).stem for source in recipe_changes]:
        raise RuntimeError("complete registry rows differ beyond exact fifteen SLUS recipes")
    return {
        "modules": modules, "plan": plan,
        "physical": len(physical), "logical": len(logical),
        "registry_rows": len(all_rows),
        "recipe_changed_sources": recipe_changes,
        "owned_data_records": len(data),
        "new_keyed_asflags": 0,
        "duplicate_owned_storage": 0,
    }


def minimally_serialized_slus_rows() -> Path:
    """Keep baseline bytes for every unchanged row in the complete projection."""
    baseline = (ROOT / "ledger/splits/slus.jsonl").read_bytes().splitlines(keepends=True)
    candidate = (CENSUS / "ledger/splits/slus.jsonl").read_bytes().splitlines(keepends=True)
    if len(baseline) != 884 or len(candidate) != 884:
        raise RuntimeError("incomplete SLUS ledger projection")
    output = []
    changed = 0
    for original_line, candidate_line in zip(baseline, candidate, strict=True):
        original, proposed = json.loads(original_line), json.loads(candidate_line)
        if original["src"] != proposed["src"] or set(original) != set(proposed):
            raise RuntimeError("SLUS ledger order or fields changed")
        if original == proposed:
            output.append(original_line)
            continue
        changed += 1
        ordered = {key: proposed[key] for key in original}
        line = json.dumps(ordered, ensure_ascii=False, separators=(",", ":")).encode() + b"\n"
        if json.loads(line) != proposed:
            raise RuntimeError("minimal SLUS ledger serialization differs")
        output.append(line)
    if changed != 15 or any(output[i] != baseline[i] for i in range(884)
                            if json.loads(baseline[i]) == json.loads(candidate[i])):
        raise RuntimeError("unchanged SLUS ledger line rewritten")
    result = HERE / "serialized_slus.jsonl"
    result.write_bytes(b"".join(output))
    if [json.loads(line) for line in result.read_bytes().splitlines()] != [
            json.loads(line) for line in candidate]:
        raise RuntimeError("minimally serialized SLUS projection is incomplete")
    return result


def workflow_appendix() -> Path:
    source = TOOLS / "SLUS_MODULES.md"
    baseline = (ROOT / "docs/SLUS_MODULES.md").read_bytes()
    proposed = source.read_bytes()
    if not proposed.startswith(baseline) or proposed == baseline:
        raise RuntimeError("workflow candidate is not production baseline plus appendix")
    appendix = proposed[len(baseline):]
    if not appendix.startswith(b"\n## Owners made entirely from collector fragments\n"):
        raise RuntimeError("unexpected workflow appendix")
    return source


def hygiene_overlay() -> tuple[dict[str, Path], dict]:
    """Bind refined text to frozen ready29 bytes and raw compiler evidence."""
    receipt = read_json(HYGIENE / "receipt.json")
    if (receipt.get("status") != "MATCH" or receipt.get("production_modified")
            or receipt.get("frozen_fixtures_modified") or len(receipt.get("records", [])) != 4):
        raise RuntimeError("source hygiene receipt differs")
    reproduced = read_json(HYGIENE / "reproduction_receipt.json")
    repins = reproduced.get("pins", {})
    gccdir = ROOT / "toolchain/compilers/gcc-2.7.2-cdk"
    include = TOOLS / "live_fixture/include"
    current_headers = {str(path.relative_to(include)): file_sha(path)
                       for path in sorted(include.rglob("*")) if path.is_file()}
    if (reproduced.get("status") != "REPRODUCED"
            or reproduced.get("production_modified")
            or reproduced.get("frozen_snapshots_modified")
            or repins.get("original_receipt_sha256") != file_sha(HYGIENE / "receipt.json")
            or repins.get("reproducer_sha256") != file_sha(HYGIENE / "reproduce.py")
            or repins.get("gcc_sha256") != file_sha(gccdir / "gcc")
            or repins.get("cc1_sha256") != file_sha(gccdir / "cc1")
            or repins.get("include_sha256") != current_headers
            or len(reproduced.get("records", [])) != 4):
        raise RuntimeError("independent source hygiene reproduction differs")
    reproduced_by_source = {r["source"]: r for r in reproduced["records"]}
    expected = {
        "src/slus/w_80041AB0.c", "src/slus/w_8004AB7C.c",
        "src/slus/gp_d92c_owned.c", "src/slus/w_8003FAD4.c",
    }
    overlay = {}
    records = {}
    for record in receipt["records"]:
        target = record["source"]
        if target not in expected or target in overlay:
            raise RuntimeError("source hygiene target differs: " + target)
        name = Path(target).name
        stage_source = STAGE / "src" / name
        before = HYGIENE / "before" / name
        after = HYGIENE / "after" / name
        before_asm = HYGIENE / "before" / (name + ".s")
        after_asm = HYGIENE / "after" / (name + ".s")
        if (stage_source.read_bytes() != before.read_bytes()
                or file_sha(before) != record["before_sha256"]
                or file_sha(after) != record["after_sha256"]
                or not record["compiler_assembly_identical"]
                or file_sha(before_asm) != record["before_assembly_sha256"]
                or file_sha(after_asm) != record["after_assembly_sha256"]
                or before_asm.read_bytes() != after_asm.read_bytes()
                or record["flags"] != "-S -O2 -w"):
            raise RuntimeError("source hygiene proof differs: " + target)
        replay = reproduced_by_source.get(target)
        if (replay is None or replay["before_sha256"] != record["before_sha256"]
                or replay["after_sha256"] != record["after_sha256"]
                or replay["assembly_sha256"] != record["after_assembly_sha256"]
                or not replay["raw_compiler_assembly_identical"]
                or not replay["matches_original_assembly"]):
            raise RuntimeError("source hygiene reproduction record differs: " + target)
        overlay[target] = after
        records[target] = {
            "ready29_source_sha256": record["before_sha256"],
            "refined_source_sha256": record["after_sha256"],
            "raw_compiler_assembly_sha256": record["after_assembly_sha256"],
            "raw_compiler_assembly_identical": True,
            "receipt": relative(HYGIENE / "receipt.json"),
            "reproduction_receipt": relative(HYGIENE / "reproduction_receipt.json"),
        }
    if set(overlay) != expected:
        raise RuntimeError("source hygiene set incomplete")

    destination = HERE / "inputs/source_hygiene"
    if destination.is_symlink():
        raise RuntimeError("unsafe source hygiene package link")
    if destination.exists():
        shutil.rmtree(destination)
    destination.mkdir(parents=True)
    for name in ("probe.py", "receipt.json", "reproduce.py", "reproduction_receipt.json"):
        shutil.copyfile(HYGIENE / name, destination / name)
    for arm in ("before", "after"):
        (destination / arm).mkdir()
        for name in sorted(Path(target).name for target in expected):
            for suffix in ("", ".s"):
                source = HYGIENE / arm / (name + suffix)
                shutil.copyfile(source, destination / arm / (name + suffix))
                if file_sha(source) != file_sha(destination / arm / (name + suffix)):
                    raise RuntimeError("packaged source hygiene proof differs")
    for name in ("probe.py", "receipt.json", "reproduce.py", "reproduction_receipt.json"):
        if file_sha(destination / name) != file_sha(HYGIENE / name):
            raise RuntimeError("packaged source hygiene proof differs: " + name)
    return overlay, records


def canonical_source_overlay(refined_sources: dict[str, Path]) -> tuple[dict[str, Path], dict]:
    """Move copied bodies into canonical rows, checking whole-TU raw assembly."""
    receipt = read_json(CANONICAL / "receipt.json")
    if receipt.get("status") != "MATCH_EXCEPT_FILE_METADATA" or len(receipt.get("records", [])) != 2:
        raise RuntimeError("canonical source proof differs")
    expected_owners = {
        "gp_d92c_owned.c": ("w_8003D92C.c", "2.7.2-cdk "),
        "gp_order_bytes_owner.c": ("w_80049F68.c", "2.7.2-cdk -fno-strength-reduce"),
    }
    expected_names = set(expected_owners) | {row for row, _ in expected_owners.values()}
    if set(receipt.get("proposed_sources", {})) != expected_names:
        raise RuntimeError("canonical proposed source set differs")
    overlay = {}
    records = {}
    for record in receipt["records"]:
        owner = record["owner"]
        if owner not in expected_owners or ("src/slus/" + owner) in overlay:
            raise RuntimeError("canonical owner differs: " + owner)
        row, recipe = expected_owners[owner]
        before = CANONICAL / "before" / owner
        after = CANONICAL / "after" / owner
        before_asm = CANONICAL / "before" / (owner + ".s")
        after_asm = CANONICAL / "after" / (owner + ".s")
        source_before = refined_sources.get("src/slus/" + owner, STAGE / "src" / owner)
        if (before.read_bytes() != source_before.read_bytes()
                or record["before_source_sha256"] != file_sha(before)
                or record["recipe"] != recipe
                or record["compiler_assembly_identical"]
                or not record["identical_except_file_metadata"]
                or record["before_assembly_sha256"] != file_sha(before_asm)
                or record["after_assembly_sha256"] != file_sha(after_asm)):
            raise RuntimeError("canonical source input or receipt differs: " + owner)
        old_lines = before_asm.read_bytes().splitlines(keepends=True)
        new_lines = after_asm.read_bytes().splitlines(keepends=True)
        is_file = lambda line: bool(re.match(rb"\s*\.file\s", line))
        old_meta = [line.decode().rstrip() for line in old_lines if is_file(line)]
        new_meta = [line.decode().rstrip() for line in new_lines if is_file(line)]
        old_body = b"".join(line for line in old_lines if not is_file(line))
        new_body = b"".join(line for line in new_lines if not is_file(line))
        if (old_body != new_body or sha(new_body) != record["instruction_and_directive_sha256"]
                or old_meta != record["file_metadata"]["before"]
                or new_meta != record["file_metadata"]["after"]
                or len(new_meta) != len(old_meta) + 1
                or new_meta[:len(old_meta)] != old_meta
                or row not in new_meta[-1]):
            raise RuntimeError("canonical owner differs beyond expected .file metadata: " + owner)
        if after.read_text().count('#include "' + row + '"') != 1:
            raise RuntimeError("canonical wrapper must include its one declared member: " + owner)
        for name in (owner, row):
            candidate = CANONICAL / "after" / name
            if file_sha(candidate) != receipt["proposed_sources"][name]:
                raise RuntimeError("canonical proposed source hash differs: " + name)
            target = "src/slus/" + name
            overlay[target] = candidate
            records[target] = {
                "previous_candidate_sha256": file_sha(source_before) if name == owner else file_sha(STAGE / "src" / name),
                "final_canonical_sha256": file_sha(candidate),
                "owner_whole_tu_non_file_assembly_sha256": record["instruction_and_directive_sha256"],
                "owner_assembly_difference": "one added .file 2 metadata directive",
                "receipt": relative(CANONICAL / "receipt.json"),
            }
    if set(overlay) != {"src/slus/" + name for name in expected_names}:
        raise RuntimeError("canonical source overlay incomplete")
    destination = HERE / "inputs/canonical_sources"
    if destination.is_symlink():
        raise RuntimeError("unsafe canonical source proof package link")
    if destination.exists():
        shutil.rmtree(destination)
    destination.mkdir(parents=True)
    for name in ("probe.py", "receipt.json"):
        shutil.copyfile(CANONICAL / name, destination / name)
    for arm in ("before", "after"):
        (destination / arm).mkdir()
        filenames = list(expected_owners) + [name + ".s" for name in expected_owners]
        if arm == "after":
            filenames += [row for row, _ in expected_owners.values()]
        for name in filenames:
            shutil.copyfile(CANONICAL / arm / name, destination / arm / name)
            if file_sha(CANONICAL / arm / name) != file_sha(destination / arm / name):
                raise RuntimeError("packaged canonical proof differs: " + name)
    for name in ("probe.py", "receipt.json"):
        if file_sha(CANONICAL / name) != file_sha(destination / name):
            raise RuntimeError("packaged canonical proof differs: " + name)
    return overlay, records


def source_context(target: str, modules: list[dict], plan: list[dict]) -> dict:
    if target.startswith("src/slus/"):
        source = "src/" + Path(target).name
        group = next((m for m in modules if m["source"] == source), None)
        role = "aggregator" if group else "whole_member"
        if group is None:
            group = next((m for m in modules for member in m["members"]
                          if member["source"] == source), None)
        if group is None:
            from slus_partitions import spans, read_aliases
            body = (STAGE / source).read_text()
            funcs = list(spans(body, read_aliases(STAGE / "config/names.tsv")))
            if not funcs:
                raise RuntimeError("changed standalone source has no canonical definitions: " + target)
            return {"role": "standalone", "module": None,
                    "functions": funcs, "data_symbols": []}
        if role == "aggregator":
            funcs = [f for member in group["members"] for f in member["functions"]]
            funcs += [f for parent in plan for part in parent["parts"]
                      if part["module"] == group["name"] for f in part["functions"]]
            symbols = [d["symbol"] for d in group["data"]]
        else:
            funcs = [f for member in group["members"] if member["source"] == source
                     for f in member["functions"]]
            symbols = []
        return {"role": role, "module": group["name"],
                "functions": funcs, "data_symbols": symbols}
    if target.startswith("include/"):
        return {"role": "header", "modules": [m["name"] for m in modules
                                              if target in m["headers"]]}
    return {}


def main() -> dict:
    pins = pinned_inputs()
    configure = verify_final_configure()
    projected = projected_rows()
    minimized_ledger = minimally_serialized_slus_rows()
    workflow = workflow_appendix()
    refined_sources, refinements = hygiene_overlay()
    canonical_sources, canonical_repairs = canonical_source_overlay(refined_sources)
    modules, plan = projected.pop("modules"), projected.pop("plan")
    if PAYLOAD.is_symlink() or CHECKROOT.is_symlink():
        raise RuntimeError("unsafe private output link")
    for directory in (PAYLOAD, CHECKROOT):
        if directory.exists():
            shutil.rmtree(directory)
        directory.mkdir()
    sources: list[tuple[str, Path, str]] = []
    for source in sorted((STAGE / "src").glob("*.c")):
        target = "src/slus/" + source.name
        proposed = canonical_sources.get(target, refined_sources.get(target, source))
        if not (ROOT / target).is_file() or proposed.read_bytes() != (ROOT / target).read_bytes():
            sources.append((target, proposed, "canonical_source"))
    for source in sorted((STAGE / "include").rglob("*")):
        if not source.is_file():
            continue
        target = "include/" + str(source.relative_to(STAGE / "include"))
        if not (ROOT / target).is_file() or source.read_bytes() != (ROOT / target).read_bytes():
            sources.append((target, source, "shared_header"))
    if (sum(kind == "canonical_source" for _, _, kind in sources),
            sum(kind == "shared_header" for _, _, kind in sources)) != (29, 2):
        raise RuntimeError("ready29 canonical source/header delta differs")
    for name in ("slus_modules.json", "slus_partitions.json"):
        sources.append(("config/" + name, STAGE / "config" / name, "module_plan"))
    sources.append(("docs/SLUS_MODULES.md", workflow, "workflow_doc"))
    tool_pins = read_json(TOOLS / "tool_pins.json")
    for target in tool_pins:
        source = STAGE / "tools/configure.py" if target == "tools/build/configure.py" else (
            CAND / target.removeprefix("tools/"))
        sources.append((target, source, "tool_adapter"))
    for name in ("test_slus_partition_only_build.py", "test_slus_partition_only_evidence.py"):
        sources.append(("tools/tests/" + name, CAND / "tests" / name, "portable_test"))
    sources += [
        ("tools/maspsx/maspsx.py", GUARD / "maspsx.py", "guarded_assembler"),
        ("tools/maspsx/maspsx/__init__.py", GUARD / "maspsx/__init__.py", "guarded_assembler"),
    ]
    for name in ASM_TEST_NAMES:
        sources.append(("tools/maspsx/tests/" + name,
                        ASM_TESTS / "tools/maspsx/tests" / name, "assembler_test"))
    sources += [
        ("ledger/splits/slus.build.ninja", CENSUS / "ledger/splits/slus.build.ninja", "complete_ledger"),
        ("ledger/splits/slus.jsonl", minimized_ledger, "complete_ledger"),
        ("ledger/rows.jsonl", CENSUS / "ledger/rows.jsonl", "complete_ledger"),
    ]
    if len({target for target, _, _ in sources}) != len(sources):
        raise RuntimeError("duplicate transition target")
    if any(kind == "guarded_assembler" and re.search(
            r"(?:D_800|func_800|0x800)", "".join(
                line[1:] for line in difflib.unified_diff(
                    (ROOT / target).read_text().splitlines(keepends=True),
                    source.read_text().splitlines(keepends=True))
                if line.startswith("+") and not line.startswith("+++")))
           for target, source, kind in sources):
        raise RuntimeError("assembler delta contains a source/address keyed special case")
    records = []
    diffs = []
    for target, source, kind in sources:
        src = ROOT / target
        old = src.read_bytes() if src.is_file() else b""
        new = source.read_bytes()
        if old == new:
            raise RuntimeError("listed transition file has no delta: " + target)
        if not new.endswith(b"\n") or (old and not old.endswith(b"\n")):
            raise RuntimeError("non-newline text needs explicit patch handling: " + target)
        dest = PAYLOAD / target
        dest.parent.mkdir(parents=True, exist_ok=True)
        dest.write_bytes(new)
        if old:
            check = CHECKROOT / target
            check.parent.mkdir(parents=True, exist_ok=True)
            check.write_bytes(old)
        else:
            (CHECKROOT / target).parent.mkdir(parents=True, exist_ok=True)
        before_text = old.decode("utf-8").splitlines(keepends=True)
        after_text = new.decode("utf-8").splitlines(keepends=True)
        delta = "".join(difflib.unified_diff(
            before_text, after_text, fromfile="a/" + target if old else "/dev/null",
            tofile="b/" + target, n=3))
        if not delta:
            raise RuntimeError("empty diff: " + target)
        diffs.append(delta)
        records.append({
            "target": target, "source": relative(source), "category": kind,
            "state": "changed" if old else "new",
            "before_sha256": sha(old) if old else None,
            "after_sha256": sha(new),
            "before_bytes": len(old), "after_bytes": len(new),
            **({"refinement": refinements[target]} if target in refinements else {}),
            **({"canonical_repair": canonical_repairs[target]} if target in canonical_repairs else {}),
            **source_context(target, modules, plan),
        })
    PATCH.write_text("".join(diffs))
    check = subprocess.run(["patch", "-p1", "--batch", "-d", str(CHECKROOT),
                            "-i", str(PATCH)], capture_output=True, text=True)
    (HERE / "patch_apply.log").write_text(check.stdout + check.stderr)
    if check.returncode:
        raise RuntimeError("private patch replay failed: " + (check.stdout + check.stderr)[-3000:])
    if any((CHECKROOT / r["target"]).read_bytes() != (PAYLOAD / r["target"]).read_bytes()
           for r in records):
        raise RuntimeError("private patch replay bytes differ")
    categories = dict(Counter(r["category"] for r in records))
    if categories != {
            "canonical_source": 29, "shared_header": 2, "module_plan": 2,
            "workflow_doc": 1,
            "tool_adapter": 9, "portable_test": 2, "guarded_assembler": 2,
            "assembler_test": 7, "complete_ledger": 3}:
        raise RuntimeError("transition file categories differ: " + repr(categories))
    inventory = {
        "status": "PRIVATE_REVIEW_READY", "production_applied": False,
        "inputs": pins, "configure": configure,
        "projection": projected,
        "files": records, "category_counts": categories,
        "total_changed_or_new_files": len(records),
        "patch_sha256": file_sha(PATCH),
        "patch_replay_exact": True,
        "source_hygiene_refinements": refinements,
        "canonical_source_repairs": canonical_repairs,
        "slus_ledger_unchanged_line_bytes_preserved": 869,
        "slus_ledger_rewritten_recipe_lines": 15,
        "new_config_pin_files": 0,
        "assembler_source_or_address_special_cases": 0,
        "remaining_activation_work": [
            "Review and apply this source/tool/test/assembler/ledger patch as one transaction.",
            "Run production-shaped configure and compare pinned Ninja and all 884 logical rows.",
            "Regenerate any other derived views or caches from the complete row registry.",
            "Run candidate-bound full SLUS, overlay, ownership, and dependency census gates before activation.",
        ],
    }
    INVENTORY.write_text(json.dumps(inventory, indent=2, sort_keys=True) + "\n")
    return inventory


if __name__ == "__main__":
    result = main()
    print(json.dumps({"status": result["status"], "files": result["total_changed_or_new_files"],
                      "categories": result["category_counts"],
                      "patch_sha256": result["patch_sha256"]}, sort_keys=True))
