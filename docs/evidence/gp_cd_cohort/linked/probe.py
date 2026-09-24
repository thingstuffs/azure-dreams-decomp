#!/usr/bin/env python3
"""Private generated-link proof for the eight-function CD cohort owner."""

from __future__ import annotations

import hashlib
import json
import os
import shutil
import subprocess
import sys
import traceback
from pathlib import Path
from unittest.mock import patch

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
STAGE = HERE / "stage"
CANDIDATE = ROOT / "work/native_lane/gp_cd_contract/combined8"
PRIVATE_HEADER = ROOT / "work/native_lane/gp_cd_contract/include/slus/cd_cohort_types.h"
GENERIC = ROOT / "work/native_lane/selfinc_local_guard/candidate/maspsx.py"
PINS = HERE / "input_pins.json"
RECEIPT = HERE / "receipt.json"
OWNER = "cd_command_state"
OWNER_SOURCE = f"src/{OWNER}_owned.c"
OWNER_OBJECT = f"build/src/{OWNER}_owned.o"
PART_SOURCE = f"build/partition_sources/code2__{OWNER}.c"
IMAGE = "build/slus_006.14"
WHOLE_STEMS = ("w_8003E34C", "w_8003E4FC", "w_8003E758", "w_8003F2A4",
               "w_8003F368", "w_8003F5AC", "w_8003F624")
WHOLE_FUNCTIONS = tuple("func_" + stem.rsplit("_", 1)[1] for stem in WHOLE_STEMS)
OWNER_FUNCTIONS = (*WHOLE_FUNCTIONS, "func_8003F240")
BASELINE_COMMIT = "89b14658"

sys.path[:0] = [str(ROOT / "tools"), str(ROOT / "tools/build"), str(ROOT / "tools/fidelity")]
from fidelity.slus_iso import SlusView  # noqa: E402
from fidelity.objread import read_elf  # noqa: E402
from row_db import edges_of  # noqa: E402
from slus_modules import load_manifest, logical_edges, plan_asset_carves  # noqa: E402
from slus_data_pieces import verify_data_pieces  # noqa: E402
from slus_partitions import (load_plan, project_edges, connected_context,
                             expected_units, check_emitted, validate_context,
                             read_aliases)  # noqa: E402
import aspsx_diff as A  # noqa: E402
import verify  # noqa: E402


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def sha(path: Path) -> str:
    return digest(path.read_bytes())


def pinned_inputs() -> dict[str, str]:
    pins = json.loads(PINS.read_text())
    if not pins or any(sha(ROOT / relative) != expected for relative, expected in pins.items()):
        changed = [name for name, expected in pins.items() if sha(ROOT / name) != expected]
        raise RuntimeError("reviewed input changed: " + repr(changed))
    return pins


def production_snapshot() -> dict:
    head = subprocess.check_output(("git", "rev-parse", "HEAD"), cwd=ROOT,
                                   text=True).strip()
    if not head.startswith(BASELINE_COMMIT):
        raise RuntimeError("production baseline changed: " + head)
    pins = pinned_inputs()
    graph = ROOT / "build_slus/build.ninja"
    physical = edges_of(graph.read_text())
    if len(physical) != 869 or len({e["out"] for e in physical}) != 869:
        raise RuntimeError("current production graph is not 869 unique physical outputs")
    files = ("config/slus_modules.json", "config/slus_partitions.json",
             "config/names.tsv", "build_slus/build.ninja",
             "ledger/splits/slus.build.ninja", "ledger/splits/slus.jsonl",
             "build_slus/build/slus_006.14", "baserom/slus_006.14",
             "src/slus/code.c", "src/slus/code2.c",
             "tools/build/configure.py", "tools/build/slus_modules.py",
             "tools/build/slus_data_pieces.py", "tools/build/slus_partitions.py",
             "tools/fidelity/slus_iso.py", "tools/fidelity/aspsx_diff.py",
             "tools/verify.py", "include/slus/cd_state.h",
             *(f"src/slus/{stem}.c" for stem in WHOLE_STEMS))
    return {"head": head, "input_pins": pins,
            "files": {name: sha(ROOT / name) for name in files},
            "active_objects": {e["out"]: sha(ROOT / "build_slus" / e["out"])
                               for e in physical}}


def run(*argv: str) -> str:
    env = os.environ.copy()
    env.pop("AZURE_MASPSX", None)
    env.pop("AZURE_MASPSX_COMPANION", None)
    result = subprocess.run(argv, cwd=STAGE, env=env, capture_output=True, text=True)
    output = result.stdout + result.stderr
    if result.returncode:
        raise RuntimeError(f"{' '.join(argv)} exited {result.returncode}: {output[-4000:]}")
    return output


def materialize(name: str) -> None:
    """Detach a SlusView directory and its file links before any private write."""
    path = STAGE / name
    if path.is_symlink():
        source = path.resolve()
        if not source.is_dir():
            raise RuntimeError("expected directory link: " + name)
        path.unlink()
        shutil.copytree(source, path, symlinks=False)
    if not path.is_dir() or not path.resolve().is_relative_to(STAGE.resolve()):
        raise RuntimeError("unsafe stage directory: " + name)
    for child in sorted(path.rglob("*")):
        if child.is_symlink():
            source = child.resolve()
            if not source.is_file():
                raise RuntimeError("unexpected nested directory link: " + str(child))
            data = source.read_bytes()
            mode = source.stat().st_mode & 0o777
            child.unlink()
            child.write_bytes(data)
            child.chmod(mode)
    if any(child.is_symlink() for child in path.rglob("*")):
        raise RuntimeError("stage still contains links: " + name)


def private_write(relative: str, content: bytes | str) -> None:
    target = STAGE / relative
    if not target.parent.resolve().is_relative_to(STAGE.resolve()):
        raise RuntimeError("private write escapes stage: " + relative)
    target.parent.mkdir(parents=True, exist_ok=True)
    if target.is_dir():
        raise RuntimeError("private file path is a directory: " + relative)
    if target.is_symlink() or target.exists():
        target.unlink()
    target.write_bytes(content if isinstance(content, bytes) else content.encode())


def candidate_contract(module: dict) -> None:
    if module["name"] != OWNER or module["source"] != OWNER_SOURCE:
        raise RuntimeError("candidate owner identity differs")
    if module["recipe"] != {"ccver": "2.7.2-cdk", "ccflags": "-G32", "asflags": ""}:
        raise RuntimeError("candidate recipe differs from reviewed CDK -G32")
    if tuple(m["id"] for m in module["members"]) != tuple("slus/" + s for s in WHOLE_STEMS):
        raise RuntimeError("candidate whole-member identities differ")
    if tuple(m["source"] for m in module["members"]) != tuple(f"src/{s}.c" for s in WHOLE_STEMS):
        raise RuntimeError("candidate whole-member source paths differ")
    if tuple(f for m in module["members"] for f in m["functions"]) != WHOLE_FUNCTIONS:
        raise RuntimeError("candidate whole-member function sets differ")
    if len(module["data"]) != 11 or len(module["data_pieces"]) != 11:
        raise RuntimeError("candidate does not describe eleven data pieces")
    if {d["symbol"] for d in module["data"]} != {p["symbol"] for p in module["data_pieces"]}:
        raise RuntimeError("candidate data-piece coverage differs")
    if "include/slus/cd_cohort_types.h" not in module["headers"]:
        raise RuntimeError("candidate omits CD header")


def prepare() -> tuple[list[dict], list[dict], SlusView, dict]:
    baseline = load_manifest(ROOT / "config/slus_modules.json")
    baseline_plan = load_plan(ROOT / "config/slus_partitions.json")
    if len(baseline) != 23 or len(baseline_plan) != 2:
        raise RuntimeError("baseline manifest or partition count changed")
    module = json.loads((CANDIDATE / "module.json").read_text())
    candidate_contract(module)
    if STAGE.is_symlink():
        raise RuntimeError("refusing symlink stage")
    if STAGE.exists():
        shutil.rmtree(STAGE)
    view = SlusView(STAGE)
    control = view.calibrate()
    if control != {"result": "MATCH", "words_diff": 0}:
        raise RuntimeError("private baseline calibration failed: " + repr(control))
    for directory in ("src", "include", "config", "tools"):
        materialize(directory)
    configure = STAGE / "tools/configure.py"
    configure_text = configure.read_text()
    anchor = 'cfiles = sorted(glob.glob("src/*.c"))'
    if configure_text.count(anchor) != 1:
        raise RuntimeError("cannot place scoped CD recipe override in private configure")
    overrides = "CC_VER.update({\n" + "".join(
        f'    "src/{stem}.c": ("2.7.2-cdk", "-G32"),\n'
        for stem in WHOLE_STEMS) + "})\n"
    private_write("tools/configure.py", configure_text.replace(anchor, overrides + anchor, 1))
    private_write(OWNER_SOURCE, (CANDIDATE / Path(OWNER_SOURCE).name).read_bytes())
    for stem in WHOLE_STEMS:
        private_write(f"src/{stem}.c", (CANDIDATE / "members" / f"{stem}.c").read_bytes())
    private_write("include/slus/cd_cohort_types.h", PRIVATE_HEADER.read_bytes())
    stage_manifest = json.loads((STAGE / "config/slus_modules.json").read_text())
    stage_manifest["modules"].append(module)
    candidate_manifest = json.loads((CANDIDATE / "candidate_manifest.json").read_text())
    if stage_manifest != candidate_manifest:
        raise RuntimeError("candidate manifest changed the baseline or final module")
    private_write("config/slus_modules.json", json.dumps(stage_manifest, indent=2) + "\n")
    modules = load_manifest(STAGE / "config/slus_modules.json")
    if len(modules) != 24 or modules[:-1] != baseline or modules[-1] != module:
        raise RuntimeError("private registry does not preserve 23 baseline owners")
    stage_plan = json.loads((STAGE / "config/slus_partitions.json").read_text())
    code2 = next(p for p in stage_plan["parents"] if p["id"] == "slus/code2")
    if any(part["module"] == OWNER for p in stage_plan["parents"] for part in p["parts"]):
        raise RuntimeError("candidate partition already present in baseline")
    code2["parts"].append({"module": OWNER, "functions": ["func_8003F240"]})
    candidate_plan = json.loads((CANDIDATE / "candidate_partitions.json").read_text())
    if stage_plan != candidate_plan:
        raise RuntimeError("candidate partition alters more than code2 F240 ownership")
    private_write("config/slus_partitions.json", json.dumps(stage_plan, indent=2) + "\n")
    plan = load_plan(STAGE / "config/slus_partitions.json")
    if [p for p in plan if p["id"] == "slus/code"] != [p for p in baseline_plan if p["id"] == "slus/code"]:
        raise RuntimeError("existing code partition plan changed")
    return modules, plan, view, {"control": control, "manifest_sha256": sha(STAGE / "config/slus_modules.json"),
                           "partition_sha256": sha(STAGE / "config/slus_partitions.json"),
                           "private_configure_sha256": sha(configure),
                           "recipe_override_members": list(WHOLE_STEMS)}


def graph_and_asset_proof(modules: list[dict], plan: list[dict]) -> tuple[list[dict], dict]:
    configured = run("python3", "tools/configure.py")
    partition_render_log = run("ninja", PART_SOURCE)
    if (STAGE / PART_SOURCE).read_bytes() != (CANDIDATE / f"code2__{OWNER}.c").read_bytes():
        raise RuntimeError("generated F240 partition part differs from reviewed source")
    physical = edges_of((STAGE / "build.ninja").read_text())
    baseline = edges_of((ROOT / "build_slus/build.ninja").read_text())
    old_outputs = {e["out"] for e in baseline}
    new_outputs = {e["out"] for e in physical}
    removed = {f"build/src/{stem}.o" for stem in WHOLE_STEMS}
    if (len(baseline) != 869 or len(physical) != 863 or old_outputs - new_outputs != removed
            or new_outputs - old_outputs != {OWNER_OBJECT}):
        raise RuntimeError("physical graph is not exact seven-whole-to-one-owner replacement")
    logical = logical_edges(project_edges(physical, plan), modules)
    baseline_modules = load_manifest(ROOT / "config/slus_modules.json")
    baseline_plan = load_plan(ROOT / "config/slus_partitions.json")
    old_logical = logical_edges(project_edges(baseline, baseline_plan), baseline_modules)
    ledger = [json.loads(line) for line in (ROOT / "ledger/splits/slus.jsonl").read_text().splitlines() if line]
    if len({len(logical), len(old_logical), len(ledger)}) != 1:
        raise RuntimeError("logical row count changed")
    if len(logical) != 884 or old_logical != ledger:
        raise RuntimeError("baseline logical registry differs from current ledger")
    old_by_src = {edge["src"]: edge for edge in old_logical}
    differences = [(edge, old_by_src[edge["src"]]) for edge in logical
                   if edge != old_by_src[edge["src"]]]
    if {new["src"] for new, _ in differences} != {f"src/{stem}.c" for stem in WHOLE_STEMS}:
        raise RuntimeError("logical recipe changes exceed the seven CD whole rows")
    for new, old in differences:
        if {key: new[key] for key in ("ccver", "ccflags", "asflags")} != modules[-1]["recipe"]:
            raise RuntimeError("member logical recipe not CDK -G32")
        if any(new[key] != old[key] for key in ("src", "out")):
            raise RuntimeError("logical row identity changed")
    validate_context(plan, modules, logical, STAGE / "raw/slus",
                     read_aliases(STAGE / "config/names.tsv"))
    carves = plan_asset_carves(modules, STAGE)
    owner_slots = [slot for carve in carves if carve["asset"] == "assets/54240.bin"
                   for slot in carve["slots"] if slot["kind"] == "module_data"
                   and slot["object"] == OWNER_OBJECT]
    if len(owner_slots) != 11 or {slot["symbols"][0] for slot in owner_slots} != {
            datum["symbol"] for datum in modules[-1]["data"]}:
        raise RuntimeError("carver does not allocate eleven individual CD data pieces")
    return physical, {"configure_log": configured,
                      "partition_render_log": partition_render_log,
                      "logical_edges": len(logical),
                      "recipe_differences": differences, "removed_outputs": sorted(removed),
                      "added_output": OWNER_OBJECT, "owner_asset_slots": owner_slots}


def linked_data_proof(module: dict) -> list[dict]:
    output = run("mipsel-linux-gnu-readelf", "-Ws", str(STAGE / "build/slus_006.14.elf"))
    by_name: dict[str, list[tuple[int, str, str]]] = {}
    for line in output.splitlines():
        fields = line.split()
        if len(fields) < 8 or not fields[0].rstrip(":").isdigit():
            continue
        try:
            address = int(fields[1], 16)
        except ValueError:
            continue
        by_name.setdefault(fields[-1], []).append((address, fields[4], fields[6]))
    obj = read_elf((STAGE / OWNER_OBJECT).read_bytes())
    image = (STAGE / IMAGE).read_bytes()
    load_address = int.from_bytes(image[0x18:0x1C], "little")
    asset = (STAGE / "assets/54240.bin").read_bytes()
    original_asset = (ROOT / "build_slus/assets/54240.bin").read_bytes()
    if asset != original_asset:
        raise RuntimeError("stage source asset changed; gap preservation is unproved")
    result = []
    for datum in module["data"]:
        name, section = datum["symbol"], datum["section"]
        entries = by_name.get(name, [])
        expected = bytes.fromhex(datum["bytes"])
        symbol = obj.symbols.get(name)
        section_bytes = obj.sections.get(section, b"")
        offset = datum["offset"]
        image_offset = 0x800 + datum["vram"] - load_address
        if (len(entries) != 1 or entries[0][0] != datum["vram"]
                or entries[0][1] != "GLOBAL"
                or not entries[0][2].isdigit() or symbol is None
                or symbol[:3] != (section, 0, "global")
                or section_bytes != expected
                or asset[offset:offset + datum["size"]] != expected
                or image[image_offset:image_offset + datum["size"]] != expected):
            raise RuntimeError("linked CD data ownership differs: " + name)
        result.append({"symbol": name, "vram": f"0x{datum['vram']:08X}",
                       "asset_offset": offset, "size": datum["size"],
                       "section": section, "payload_sha256": digest(expected),
                       "linked_section_index": int(entries[0][2])})
    if len(result) != 11:
        raise RuntimeError("linked CD data record count differs")
    return result


def code2_remainder_proof(plan: list[dict], modules: list[dict]) -> dict:
    expected = expected_units(plan, modules)["src/code2.c"]
    before = A.View(A.read_elf((ROOT / "build_slus/build/src/code2.o").read_bytes()))
    after = A.View(A.read_elf((STAGE / "build/src/code2.o").read_bytes()))
    if (set(before.funcs) - set(after.funcs) != {"func_8003F240"}
            or set(after.funcs) != expected or len(expected) != 22):
        raise RuntimeError("code2 remainder function coverage differs")
    compared = A.compare_units(before, after, sorted(expected))
    if not compared["exact"] or compared["missing"]:
        raise RuntimeError("unchanged code2 function tokens differ")
    return {"baseline_functions": len(before.funcs), "remainder_functions": len(after.funcs),
            "removed_function": "func_8003F240", "unchanged_words": compared["len_m"],
            "token_diff": compared["diff"], "exact": compared["exact"]}


def closure_proof(plan: list[dict], modules: list[dict]) -> dict:
    parents, owners = connected_context("slus/code2", plan, modules)
    if {p["id"] for p in parents} != {"slus/code", "slus/code2"}:
        raise RuntimeError("connected collector context differs")
    if {m["name"] for m in owners} != {
            "list_cursor_e0", "saved_value_b98", "sort_rank_81540",
            "command_slots_81554", OWNER}:
        raise RuntimeError("connected owner closure differs")
    expected = expected_units(parents, owners)
    counts = {source: len(functions) for source, functions in expected.items()}
    if counts != {"src/code.c": 152, "src/code2.c": 22,
                  "src/w_80041134_owned.c": 3, "src/w_80050DA8_owned.c": 3,
                  "src/sort_rank_81540_owned.c": 2,
                  "src/w_8004DCA8_owned.c": 5, OWNER_SOURCE: 8}:
        raise RuntimeError("connected physical function counts differ: " + repr(counts))
    emitted = {}
    for source in expected:
        obj = read_elf((STAGE / "build/src" / (Path(source).stem + ".o")).read_bytes())
        emitted[source] = [name for name, symbol in obj.symbols.items()
                           if symbol[2] == "func" and symbol[0]
                           and (symbol[0] == ".text" or symbol[0].startswith(".text."))]
    check_emitted(expected, emitted)
    if sum(counts.values()) != 195:
        raise RuntimeError("connected closure total differs")
    return {"parents": [p["id"] for p in parents],
            "owners": [m["name"] for m in owners], "counts": counts,
            "total_functions": 195, "whole_collector_genuine_claim": False}


def genuine_owner_proof(module: dict) -> dict:
    out = HERE / "genuine"
    out.mkdir(exist_ok=True)
    A.TMP = HERE / "a"
    A.TMP.mkdir(exist_ok=True)
    A.SLUS_ELF = STAGE / "build/slus_006.14.elf"
    A.SLUS_BIN = ROOT / "baserom/slus_006.14"
    A._SLUS = None
    row = {"id": f"slus/{OWNER}_owned", "kind": "slus", "container": "slus",
           "c_path": OWNER_SOURCE, "cell": module["recipe"]["ccver"],
           "flags": module["recipe"]["ccflags"],
           "row_asflags": module["recipe"]["asflags"]}
    with patch.object(verify, "MASPSX", GENERIC):
        fresh, error = verify._compile_slus_source(
            row, STAGE / OWNER_SOURCE, out, STAGE / "include", root=STAGE)
    if fresh is None:
        raise RuntimeError("fresh generic owner compile failed: " + str(error))
    asm = verify.postprocess_slus((out / "a.s").read_text(), root=STAGE, names_only=True)
    lnk, error = A.run_aspsx(A.aspsx_input(asm), "2.79", ["-q"], out)
    if lnk is None:
        raise RuntimeError("genuine owner assembly failed: " + str(error))
    (out / "genuine.lnk").write_bytes(lnk)
    generic = A.data_piece_view(A.read_elf(fresh.read_bytes()), module)
    built = A.data_piece_view(A.read_elf((STAGE / OWNER_OBJECT).read_bytes()), module)
    genuine = A.data_piece_view(A.read_lnk(lnk), module, generic, A.aliases(asm))
    for name in OWNER_FUNCTIONS:
        genuine.add_unit(name, generic)
    for label, view in (("fresh_generic", generic), ("built_generic", built), ("genuine", genuine)):
        if set(view.funcs) != set(OWNER_FUNCTIONS):
            raise RuntimeError(label + " whole owner function set differs: " + repr(set(view.funcs)))
    gb = A.compare_units(generic, built, OWNER_FUNCTIONS)
    gg = A.compare_units(generic, genuine, OWNER_FUNCTIONS)
    retail = {label: A.retail_compare(view, OWNER_FUNCTIONS, "slus")
              for label, view in (("fresh_generic", generic), ("built_generic", built),
                                  ("genuine", genuine))}
    if (not gb["exact"] or not gg["exact"]
            or (gb["len_m"], gb["len_g"], gg["len_m"], gg["len_g"]) != (1041,) * 4):
        raise RuntimeError("whole owner generic/genuine/linked words differ")
    if any(value != {"diff": 0, "masked": 0, "checked": 8} for value in retail.values()):
        raise RuntimeError("whole owner retail comparison differs")
    return {"functions": OWNER_FUNCTIONS, "words": 1041,
            "fresh_generic_sha256": sha(fresh),
            "linked_owner_sha256": sha(STAGE / OWNER_OBJECT),
            "assembly_sha256": sha(out / "a.s"),
            "genuine_lnk_sha256": digest(lnk),
            "generic_vs_built": {key: gb[key] for key in ("exact", "diff", "len_m", "len_g", "missing")},
            "generic_vs_genuine": {key: gg[key] for key in ("exact", "diff", "len_m", "len_g", "missing")},
            "retail": retail}


def main() -> dict:
    before = production_snapshot()
    retail = (ROOT / "baserom/slus_006.14").read_bytes()
    if (ROOT / "build_slus" / IMAGE).read_bytes() != retail:
        raise RuntimeError("production image is not retail exact")
    modules, plan, view, prepared = prepare()
    physical, graph = graph_and_asset_proof(modules, plan)
    if len(load_manifest(STAGE / "config/slus_modules.json")) != 24:
        raise RuntimeError("generated stage does not retain 24 private owners")
    owner_path = STAGE / OWNER_OBJECT
    if owner_path.exists():
        owner_path.unlink()
    env = os.environ.copy()
    env.pop("AZURE_MASPSX", None)
    env["AZURE_MASPSX_COMPANION"] = str(GENERIC)
    rc, compile_log = view._ninja([OWNER_OBJECT], env=env)
    (HERE / "owner_compile.log").write_text(compile_log)
    if rc or f"CC {OWNER_SOURCE}" not in compile_log:
        raise RuntimeError("selective generic owner compilation failed: " + compile_log[-2500:])
    split_before = verify_data_pieces(owner_path, modules[-1])
    owner_hash = sha(owner_path)
    rc, link_log = view._ninja([IMAGE])
    (HERE / "link.log").write_text(link_log)
    if rc or sha(owner_path) != owner_hash or f"CC {OWNER_SOURCE}" in link_log:
        raise RuntimeError("normal link failed or rebuilt owner under stock assembler: " + link_log[-2500:])
    image = (STAGE / IMAGE).read_bytes()
    if image != retail:
        first = next((i for i, (a, b) in enumerate(zip(image, retail)) if a != b), None)
        raise RuntimeError("private full image differs from retail: first offset " + repr(first))
    rc, gate_log = view._ninja(["build/slus_006.14.ok"])
    (HERE / "gate.log").write_text(gate_log)
    if rc or not (STAGE / "build/slus_006.14.ok").is_file() or sha(owner_path) != owner_hash:
        raise RuntimeError("generated SHA-1 gate failed or changed owner")
    if verify_data_pieces(owner_path, modules[-1]) != split_before:
        raise RuntimeError("owner data-piece proof changed during link")
    baseline_objects = before["active_objects"]
    new_outputs = {edge["out"] for edge in physical}
    outside = sorted((set(baseline_objects) & new_outputs) - {"build/src/code2.o"})
    changed = [output for output in outside if sha(STAGE / output) != baseline_objects[output]]
    if len(outside) != 861 or changed:
        raise RuntimeError("outside active object bytes differ: " + repr(changed[:8]))
    data = linked_data_proof(modules[-1])
    code2 = code2_remainder_proof(plan, modules)
    closure = closure_proof(plan, modules)
    genuine = genuine_owner_proof(modules[-1])
    after = production_snapshot()
    if after != before:
        raise RuntimeError("production inputs or active objects changed during private trial")
    result = {"status": "MATCH", "baseline_commit": before["head"],
              "production_before": before, "production_after": after,
              "production_unchanged": True,
              "stage": str(STAGE.relative_to(ROOT)),
              "image": {"retail_exact": True, "sha256": digest(image)},
              "modules": {"baseline": 23, "trial": 24},
              "physical_edges": len(physical), "logical_edges": graph["logical_edges"],
              "graph": graph, "prepared": prepared,
              "outside_objects": {"checked": len(outside), "changed": changed},
              "code2_remainder": code2, "connected_closure": closure,
              "owned_data": data, "owner_data_piece_receipt": split_before,
              "owner_genuine": genuine,
              "owner_object_sha256_before_link": owner_hash,
              "owner_object_sha256_after_link": sha(owner_path),
              "owner_sidecars_sha256": {
                  suffix: sha(STAGE / f"build/src/{OWNER}_owned{suffix}")
                  for suffix in (".unsplit.o", ".data-pieces.json", ".data-pieces.ok")},
              "scope_limit": "Private generic assembler for the new owner only; unchanged production recipes and stock link for all other objects."}
    RECEIPT.write_text(json.dumps(result, indent=2, sort_keys=True) + "\n")
    return result


if __name__ == "__main__":
    try:
        receipt = main()
        print(json.dumps({"status": receipt["status"], "physical": receipt["physical_edges"],
                          "logical": receipt["logical_edges"], "outside": receipt["outside_objects"],
                          "owner_words": receipt["owner_genuine"]["words"]}, indent=2))
    except Exception as exc:
        RECEIPT.write_text(json.dumps({"status": "ERROR", "error": str(exc),
                                       "traceback": traceback.format_exc()}, indent=2) + "\n")
        raise
