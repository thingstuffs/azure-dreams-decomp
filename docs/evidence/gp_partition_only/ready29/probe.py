#!/usr/bin/env python3
"""Private all-generic ready26 + two partition-only collector owners rehearsal."""

from __future__ import annotations

from collections import Counter
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import traceback

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
FROZEN = ROOT / "work/native_lane/gp_ready26_cd/stage"
FROZEN_RECEIPT = ROOT / "work/native_lane/gp_ready26_cd/receipt.json"
TOOLS = ROOT / "work/native_lane/gp_partition_only_tools/candidate/tools"
COHORT = ROOT / "work/native_lane/gp_cd_contract/cohort"
GENERIC = ROOT / "work/native_lane/selfinc_local_guard/candidate/maspsx.py"
STAGE = HERE / "stage"
RECEIPT = HERE / "receipt.json"
PINS = HERE / "input_pins.json"
IMAGE = "build/slus_006.14"
NEW = (
    ("accessors_814c8", "src/c8_accessors_owned.c", "slus/code",
     ("func_8003F5D4", "func_8003F5E0"), "c8_accessors.c"),
    ("table_counters_b1b_b1c", "src/b1b_b1c_table_owned.c", "slus/code2",
     ("func_80048DA0",), "b1b_b1c_table.c"),
)
EXPECTED_TOOL_HASHES = {
    "build/slus_modules.py": "7ad5248f055c79b9a71b4f64eec8fe3626291f99006f7a8598417595fdccf05e",
    "build/slus_partitions.py": "1e484e42d7678e493b7dcd078282fe882c8c94ca58b749b2c5f19af35b7caf17",
    "build/configure.py": "5728f7979b573c189c05817aa48b94b98bbf45566a3e6d982dc658861279f4fd",
    "fidelity/slus_iso.py": "e1f39d20c7791c545cdea29a95452a4931365ab75f38af0797f39454f8d38f2a",
}
PRODUCTION_FILES = (
    "config/slus_modules.json", "config/slus_partitions.json", "config/names.tsv",
    "build_slus/build.ninja", "build_slus/build/slus_006.14", "baserom/slus_006.14",
    "src/slus/code.c", "src/slus/code2.c", "tools/build/configure.py",
    "tools/build/slus_modules.py", "tools/build/slus_partitions.py",
    "tools/build/slus_data_pieces.py", "tools/build/cc.sh", "tools/build/ccproc.py",
    "tools/fidelity/aspsx_diff.py", "tools/fidelity/slus_iso.py",
    "tools/maspsx/maspsx.py", "tools/verify.py",
)

sys.path[:0] = [str(ROOT / "tools"), str(ROOT / "tools/build"), str(ROOT / "tools/fidelity")]
from row_db import edges_of  # noqa: E402
from fidelity.objread import read_elf  # noqa: E402
from slus_data_pieces import verify_data_pieces  # noqa: E402
import aspsx_diff as A  # noqa: E402
import verify  # noqa: E402
from unittest.mock import patch  # noqa: E402


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def load_module(label: str, path: Path):
    spec = importlib.util.spec_from_file_location(label, path)
    if spec is None or spec.loader is None:
        raise RuntimeError("cannot load private helper: " + str(path))
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


def helpers():
    h = load_module("ready29_cd_helper", ROOT / "work/native_lane/gp_cd_cohort_link/probe.py")
    r = load_module("ready29_ready18_helper", ROOT / "work/native_lane/gp_ready18_cd_contract/probe.py")
    a = load_module("ready29_all858_helper", ROOT / "work/native_lane/gp_all858_probe/probe.py")
    return h, r, a


def snap_production() -> dict:
    edges = edges_of((ROOT / "build_slus/build.ninja").read_text())
    return {
        "files": {name: sha(ROOT / name) for name in PRODUCTION_FILES},
        "active_objects": {e["out"]: sha(ROOT / "build_slus" / e["out"]) for e in edges},
        "physical": len(edges),
    }


def pins() -> dict:
    ready = json.loads(FROZEN_RECEIPT.read_text())
    if (ready.get("status") != "MATCH" or ready["graph"]["physical"] != 858
            or ready["graph"]["logical"] != 884 or not ready["image"]["retail_exact"]):
        raise RuntimeError("frozen ready26 gate is incomplete")
    if sha(FROZEN / IMAGE) != ready["image"]["sha256"]:
        raise RuntimeError("frozen image drift")
    for relative, expected in EXPECTED_TOOL_HASHES.items():
        if sha(TOOLS / relative) != expected:
            raise RuntimeError("unfrozen partition-only build tool: " + relative)
    prior_edges = edges_of((FROZEN / "build.ninja").read_text().replace(
        ": cc_guarded_private ", ": cc "))
    if len(prior_edges) != 858:
        raise RuntimeError("frozen graph differs")
    input_hashes = {
        "ready26_receipt": sha(FROZEN_RECEIPT),
        "ready26_probe": sha(ROOT / "work/native_lane/gp_ready26_cd/probe.py"),
        "ready26_stage_files": {name: sha(FROZEN / name) for name in (
            "build.ninja", "config/slus_modules.json", "config/slus_partitions.json",
            "config/names.tsv", "tools/configure.py", "tools/slus_modules.py",
            "tools/slus_partitions.py", "tools/slus_data_pieces.py", IMAGE)},
        "ready26_active_objects": {e["out"]: sha(FROZEN / e["out"]) for e in prior_edges},
        "candidate_build_tools": {name: sha(TOOLS / name) for name in EXPECTED_TOOL_HASHES},
        "candidate_sources": {name: sha(COHORT / name) for name in
                              ("c8_accessors.c", "b1b_b1c_table.c")},
        "generic_cli": sha(GENERIC),
        "generic_package": sha(GENERIC.parent / "maspsx/__init__.py"),
        "helper_scripts": {name: sha(ROOT / name) for name in (
            "work/native_lane/gp_ready18_cd_contract/probe.py",
            "work/native_lane/gp_cd_cohort_link/probe.py",
            "work/native_lane/gp_all858_probe/probe.py")},
        "production": snap_production(),
    }
    if PINS.exists() and json.loads(PINS.read_text()) != input_hashes:
        raise RuntimeError("frozen baseline input pins differ")
    PINS.write_text(json.dumps(input_hashes, indent=2, sort_keys=True) + "\n")
    return input_hashes


def safe_write(relative: str, content: bytes | str) -> None:
    path = STAGE / relative
    if not path.parent.resolve().is_relative_to(STAGE.resolve()):
        raise RuntimeError("private stage write escapes: " + relative)
    path.parent.mkdir(parents=True, exist_ok=True)
    if path.is_dir():
        raise RuntimeError("private stage file is a directory: " + relative)
    if path.exists() or path.is_symlink():
        path.unlink()
    path.write_bytes(content if isinstance(content, bytes) else content.encode())


def module_entries() -> list[dict]:
    c8 = {
        "name": NEW[0][0], "source": NEW[0][1], "members": [], "partition_only": True,
        "headers": ["include/common.h"],
        "recipe": {"ccver": "2.7.2", "ccflags": "", "asflags": ""},
        "data": [{"symbol": "D_800814C8", "asset": "assets/54240.bin",
                  "offset": 0xA88, "size": 4, "vram": 0x800814C8,
                  "bytes": "00000000", "section": ".sdata"}],
        "evidence": "docs/evidence/gp_cd_cohort.md",
    }
    b = {
        "name": NEW[1][0], "source": NEW[1][1], "members": [], "partition_only": True,
        "headers": ["include/common.h"],
        "recipe": {"ccver": "2.8.1", "ccflags": "", "asflags": ""},
        "data": [{"symbol": symbol, "asset": "assets/54240.bin", "offset": offset,
                  "size": 1, "vram": vram, "bytes": "00", "section": ".sdata." + symbol}
                 for symbol, offset, vram in (
                     ("D_80080B1B", 0xDB, 0x80080B1B),
                     ("D_80080B1C", 0xDC, 0x80080B1C))],
        "data_pieces": [{"symbol": symbol, "source_section": ".sdata", "alignment": 1}
                        for symbol in ("D_80080B1B", "D_80080B1C")],
        "evidence": "docs/evidence/gp_cd_cohort.md",
    }
    return [c8, b]


def clone_and_stage(h, p) -> tuple[list[dict], list[dict]]:
    if STAGE.is_symlink():
        raise RuntimeError("refusing linked stage")
    if STAGE.exists():
        shutil.rmtree(STAGE)
    shutil.copytree(FROZEN, STAGE, symlinks=True)
    h.STAGE = STAGE
    h.HERE = HERE / "cd8"
    h.HERE.mkdir(exist_ok=True)
    for directory in ("src", "config", "include", "tools"):
        h.materialize(directory)
    for name in ("build/configure.py", "build/slus_modules.py", "build/slus_partitions.py"):
        safe_write("tools/" + Path(name).name, (TOOLS / name).read_bytes())
    # The frozen ready26 stage already contains private recipe overrides for
    # its grouped whole rows. Carry those unchanged onto the new build adapter.
    prior_configure = (FROZEN / "tools/configure.py").read_text()
    anchor = 'cfiles = sorted(glob.glob("src/*.c"))'
    block = prior_configure.split('CC_VER.update({', 1)[1].split(anchor, 1)[0]
    override = 'CC_VER.update({' + block
    if (override.count('CC_VER.update({') != 2 or
            len(re.findall(r'(?m)^    "src/[^\n]+": \("2\.7\.2-cdk",', override)) != 15):
        raise RuntimeError("frozen ready26 recipe overrides differ")
    candidate_configure = (STAGE / "tools/configure.py").read_text()
    if candidate_configure.count(anchor) != 1 or 'CC_VER.update({' in candidate_configure:
        raise RuntimeError("candidate configure insertion point differs")
    safe_write("tools/configure.py", candidate_configure.replace(anchor, override + anchor, 1))
    # The C bodies remain canonical fragments. New aggregators supply only
    # ordinary storage and the declaration used by the extracted code2 part.
    safe_write(NEW[0][1], '#include "common.h"\n\nint D_800814C8 = 0;\n\n'
               '#include "../build/partition_sources/code__accessors_814c8.c"\n')
    safe_write(NEW[1][1], '#include "common.h"\n\nextern u8 D_80080B18[];\n'
               'u8 D_80080B1B = 0;\nu8 D_80080B1C = 0;\n\n'
               '#include "../build/partition_sources/code2__table_counters_b1b_b1c.c"\n')
    # The frozen CD member's old comment claimed a >8-byte D3 neighbour. The
    # actual shared declaration is D3[2]; only this comment changes here.
    f624 = STAGE / "src/w_8003F624.c"
    text = f624.read_text()
    old = ("/* dual-access global: sb-store of D_800814D4 via $gp scalar, but address-of\n"
           " * (for CdControlB's param pointer) goes through a >8B neighbour symbol\n"
           " * D_800814D3[1] == &D_800814D4, forcing hi/lo codegen for the address-of. */")
    new = ("/* D_800814D4 uses a GP-relative scalar store. CdControlB's parameter\n"
           " * address uses D_800814D3[1], an external address view of the\n"
           " * adjacent byte within the observed two-byte D3 access span. */")
    if text.count(old) != 1:
        raise RuntimeError("reviewed F624 comment changed")
    safe_write("src/w_8003F624.c", text.replace(old, new))
    manifest = json.loads((STAGE / "config/slus_modules.json").read_text())
    if len(manifest["modules"]) != 31:
        raise RuntimeError("ready26 module registry differs")
    manifest["modules"].extend(module_entries())
    safe_write("config/slus_modules.json", json.dumps(manifest, indent=2) + "\n")
    plan_doc = json.loads((STAGE / "config/slus_partitions.json").read_text())
    code = next(x for x in plan_doc["parents"] if x["id"] == "slus/code")
    code2 = next(x for x in plan_doc["parents"] if x["id"] == "slus/code2")
    if (len(code["parts"]), len(code2["parts"])) != (5, 2):
        raise RuntimeError("ready26 collector plan differs")
    code["parts"].append({"module": NEW[0][0], "functions": list(NEW[0][3])})
    code2["parts"].append({"module": NEW[1][0], "functions": list(NEW[1][3])})
    safe_write("config/slus_partitions.json", json.dumps(plan_doc, indent=2) + "\n")
    modules = p.slus_modules.load_manifest(STAGE / "config/slus_modules.json")
    plan = p.load_plan(STAGE / "config/slus_partitions.json")
    if len(modules) != 33 or len(plan) != 2 or modules[-2:] != module_entries():
        raise RuntimeError("partition-only registry/plan failed to decode")
    return modules, plan


def run(*argv: str, generic: bool = False, log: str | None = None) -> str:
    env = os.environ.copy()
    env.pop("AZURE_MASPSX", None)
    env.pop("AZURE_MASPSX_COMPANION", None)
    if generic:
        env["AZURE_MASPSX_COMPANION"] = str(GENERIC)
    proc = subprocess.run(argv, cwd=STAGE, env=env, capture_output=True, text=True)
    output = proc.stdout + proc.stderr
    if log:
        (HERE / log).write_text(output)
    if proc.returncode:
        raise RuntimeError(f"{' '.join(argv)} exited {proc.returncode}: {output[-6000:]}")
    return output


def graph_and_sources(p, modules: list[dict], plan: list[dict]) -> tuple[list[dict], dict]:
    configure_log = run("python3", "tools/configure.py", log="configure.log")
    source_targets = [f"build/partition_sources/{parent}__{owner}.c" for parent, owner in
                      (("code", NEW[0][0]), ("code2", NEW[1][0]))]
    render_log = run("ninja", *source_targets, log="partition_render.log")
    alias = p.read_aliases(STAGE / "config/names.tsv")
    for name, _, parent_id, functions, source in NEW:
        parent = next(x for x in plan if x["id"] == parent_id)
        body = (STAGE / "src" / ("code.c" if parent_id == "slus/code" else "code2.c")).read_text()
        direct = (COHORT / source).read_text()
        found_parent, found_direct = p.spans(body, alias), p.spans(direct, alias)
        if any(body[found_parent[f][0]:found_parent[f][2]].strip() !=
               direct[found_direct[f][0]:found_direct[f][2]].strip() for f in functions):
            raise RuntimeError("canonical collector bodies differ from direct probe: " + name)
        fragment = (STAGE / source_targets[0 if parent_id == "slus/code" else 1]).read_text()
        found_fragment = p.spans(fragment, alias)
        if set(found_fragment) != set(functions):
            raise RuntimeError("rendered collector fragment function set differs: " + name)
        for f in functions:
            if (fragment[found_fragment[f][0]:found_fragment[f][2]].strip() !=
                    direct[found_direct[f][0]:found_direct[f][2]].strip()):
                raise RuntimeError("rendered collector body differs from direct probe: " + f)
    ninja = (STAGE / "build.ninja").read_text()
    physical = edges_of(ninja)
    old_ninja = (FROZEN / "build.ninja").read_text().replace(": cc_guarded_private ", ": cc ")
    old = edges_of(old_ninja)
    old_out, new_out = ({e["out"] for e in x} for x in (old, physical))
    added = {f"build/{Path(source).with_suffix('.o')}" for _, source, _, _, _ in NEW}
    if len(old) != 858 or len(physical) != 860 or old_out - new_out or new_out - old_out != added:
        raise RuntimeError("physical graph is not 858 + 2 = 860")
    original_modules = p.slus_modules.load_manifest(FROZEN / "config/slus_modules.json")
    original_plan = p.load_plan(FROZEN / "config/slus_partitions.json")
    old_logical = p.slus_modules.logical_edges(p.project_edges(old, original_plan), original_modules)
    logical = p.slus_modules.logical_edges(p.project_edges(physical, plan), modules)
    if len(old_logical) != len(logical) or len(logical) != 884 or old_logical != logical:
        raise RuntimeError("logical rows or recipes changed")
    p.validate_context(plan, modules, logical, STAGE / "raw/slus", alias)
    expected = p.expected_units(plan, modules)
    selected = {m["source"]: set(f for parent in plan for part in parent["parts"]
                                 if part["module"] == m["name"] for f in part["functions"])
                for m in modules[-2:]}
    if selected != {NEW[0][1]: set(NEW[0][3]), NEW[1][1]: set(NEW[1][3])}:
        raise RuntimeError("partition-only physical function scopes differ")
    if expected["src/code.c"] != p.expected_units(original_plan, original_modules)["src/code.c"] - set(NEW[0][3]):
        raise RuntimeError("code remainder expected scope differs")
    if expected["src/code2.c"] != p.expected_units(original_plan, original_modules)["src/code2.c"] - set(NEW[1][3]):
        raise RuntimeError("code2 remainder expected scope differs")
    slots = [s for carve in p.slus_modules.plan_asset_carves(modules, STAGE)
             for s in carve["slots"] if s["kind"] == "module_data"]
    new_slots = [s for s in slots if s["object"] in added]
    if len(new_slots) != 3 or {s["symbols"][0] for s in new_slots} != {
            "D_800814C8", "D_80080B1B", "D_80080B1C"}:
        raise RuntimeError("new data carve slots differ")
    return physical, {"configure_log_sha256": digest(configure_log.encode()),
                      "partition_render_log_sha256": digest(render_log.encode()),
                      "physical": len(physical), "logical": len(logical),
                      "added_outputs": sorted(added),
                      "code_remainder_functions": len(expected["src/code.c"]),
                      "code2_remainder_functions": len(expected["src/code2.c"]),
                      "new_data_slots": new_slots,
                      "generated_sources": {source: sha(STAGE / source) for source in source_targets}}


def all_generic_build(physical: list[dict]) -> dict:
    for edge in physical:
        path = STAGE / edge["out"]
        if path.is_symlink():
            raise RuntimeError("active object is symlink: " + edge["out"])
        if path.exists():
            path.unlink()
    outputs = [e["out"] for e in physical]
    compile_log = run("ninja", "-j", "4", *outputs, generic=True, log="all_objects_build.log")
    absent = [out for out in outputs if not (STAGE / out).is_file()]
    if absent:
        raise RuntimeError("all-generic build omitted active objects: " + repr(absent[:10]))
    object_hashes = {out: sha(STAGE / out) for out in outputs}
    link_log = run("ninja", "-j", "4", IMAGE, log="full_image_link.log")
    if any(sha(STAGE / out) != value for out, value in object_hashes.items()):
        raise RuntimeError("normal generated link rebuilt an active object")
    gate_log = run("ninja", "build/slus_006.14.ok", log="sha1_gate.log")
    if any(sha(STAGE / out) != value for out, value in object_hashes.items()):
        raise RuntimeError("SHA1 gate rebuilt an active object")
    image = STAGE / IMAGE
    if (image.read_bytes() != (ROOT / "baserom/slus_006.14").read_bytes()
            or not (STAGE / "build/slus_006.14.ok").is_file()):
        raise RuntimeError("all-generic ready29 image or SHA1 gate differs from retail")
    return {"rebuilt_objects": len(outputs), "object_build_log_sha256": digest(compile_log.encode()),
            "link_log_sha256": digest(link_log.encode()),
            "gate_log_sha256": digest(gate_log.encode()),
            "image_sha256": sha(image), "retail_exact": True, "sha1_gate": True,
            "new_owner_object_sha256": {out: object_hashes[out] for out in sorted(object_hashes)
                                         if out in {f"build/{Path(x[1]).with_suffix('.o')}" for x in NEW}}}


def object_and_closure_proof(a, p, physical: list[dict], modules: list[dict], plan: list[dict]) -> dict:
    a.FROZEN, a.STAGE = FROZEN, STAGE
    old = edges_of((FROZEN / "build.ninja").read_text().replace(": cc_guarded_private ", ": cc "))
    old_by_out = {e["out"]: e for e in old}
    shared = sorted(set(old_by_out) & {e["out"] for e in physical} -
                    {"build/src/code.o", "build/src/code2.o"})
    changed = []
    raw_only = 0
    for output in shared:
        result = a.object_comparison(old_by_out[output])
        if (result["function_changes"] or result["data_changes"]
                or result["canonical_relocation_changes"]["removed_count"]
                or result["canonical_relocation_changes"]["added_count"]):
            changed.append(output)
        if result["object_bytes_changed"]:
            raw_only += 1
    if len(shared) != 856 or changed:
        raise RuntimeError("outside physical object semantics changed: " + repr(changed[:12]))
    old_plan = p.load_plan(FROZEN / "config/slus_partitions.json")
    old_modules = p.slus_modules.load_manifest(FROZEN / "config/slus_modules.json")
    old_expected = p.expected_units(old_plan, old_modules)
    expected = p.expected_units(plan, modules)
    remainders = {}
    for parent, removed in (("code", set(NEW[0][3])), ("code2", set(NEW[1][3]))):
        source = f"src/{parent}.c"
        old_view = A.View(read_elf((FROZEN / f"build/src/{parent}.o").read_bytes()))
        new_view = A.View(read_elf((STAGE / f"build/src/{parent}.o").read_bytes()))
        keep = expected[source]
        if (set(old_view.funcs) != old_expected[source] or set(new_view.funcs) != keep
                or old_expected[source] - keep != removed):
            raise RuntimeError("collector remainder emitted function set differs: " + parent)
        cmp = A.compare_units(old_view, new_view, sorted(keep))
        if not cmp["exact"] or cmp["missing"]:
            raise RuntimeError("collector remainder tokens changed: " + parent)
        remainders[parent] = {"functions": len(keep), "words": cmp["len_m"],
                              "removed": sorted(removed), "exact": True}
    connected_parents, connected_owners = p.connected_context("slus/code", plan, modules)
    connected_expected = p.expected_units(connected_parents, connected_owners)
    emitted = {}
    for source, wanted in connected_expected.items():
        object_path = STAGE / "build" / Path(source).with_suffix(".o")
        obj = read_elf(object_path.read_bytes())
        emitted[source] = [name for name, symbol in obj.symbols.items()
                           if symbol[2] == "func" and symbol[0]
                           and (symbol[0] == ".text" or symbol[0].startswith(".text."))]
    p.check_emitted(connected_expected, emitted)
    return {"outside_objects": len(shared), "outside_semantic_changes": changed,
            "outside_raw_hash_changes": raw_only, "collector_remainders": remainders,
            "connected_parents": sorted(x["id"] for x in connected_parents),
            "connected_owners": sorted(x["name"] for x in connected_owners),
            "connected_functions": sum(len(x) for x in connected_expected.values()),
            "no_duplicate_function_storage": True}


def new_data_proof(h, modules: list[dict]) -> list[dict]:
    cd_old_stage, cd_old_here = h.STAGE, h.HERE
    h.STAGE, h.HERE = STAGE, HERE / "cd8"
    output = h.run("mipsel-linux-gnu-readelf", "-Ws", str(STAGE / "build/slus_006.14.elf"))
    by_name = {}
    for line in output.splitlines():
        fields = line.split()
        if len(fields) >= 8 and fields[0].rstrip(":").isdigit():
            by_name.setdefault(fields[-1], []).append(fields)
    image = (STAGE / IMAGE).read_bytes()
    load_address = int.from_bytes(image[0x18:0x1C], "little")
    generated = (STAGE / "config/generated/slus_006.14.undefined_syms.txt").read_text()
    filtered = (STAGE / "build/slus_006.14.undefined_syms.modules.txt").read_text()
    schema = sys.modules["slus_modules"]
    if sha(Path(schema.__file__)) != EXPECTED_TOOL_HASHES["build/slus_modules.py"]:
        raise RuntimeError("new data proof is not using the pinned candidate schema")
    slots = [slot for carve in schema.plan_asset_carves(modules, STAGE)
             for slot in carve["slots"] if slot["kind"] == "module_data"]
    results = []
    for module in modules[-2:]:
        path = STAGE / "build" / Path(module["source"]).with_suffix(".o")
        obj = read_elf(path.read_bytes())
        if module.get("data_pieces"):
            verify_data_pieces(path, module)
        for datum in module["data"]:
            name, section = datum["symbol"], datum["section"]
            entries = by_name.get(name, [])
            symbol = obj.symbols.get(name)
            expected = bytes.fromhex(datum["bytes"])
            first = min(x["offset"] for x in module["data"] if x["section"] == section)
            offset = datum["offset"] - first
            chunk = obj.sections.get(section, b"")[offset:offset + datum["size"]]
            asset = (STAGE / datum["asset"]).read_bytes()[datum["offset"]:datum["offset"] + datum["size"]]
            image_at = 0x800 + datum["vram"] - load_address
            image_bytes = image[image_at:image_at + datum["size"]]
            matching_slots = [s for s in slots if s["object"] == f"build/{Path(module['source']).with_suffix('.o')}"
                              and name in s["symbols"]]
            assignment = f"{name} = 0x{datum['vram']:08X};"
            valid = (len(entries) == 1 and int(entries[0][1], 16) == datum["vram"]
                     and entries[0][4] == "GLOBAL" and entries[0][6] != "ABS"
                     and symbol is not None and symbol[:3] == (section, offset, "global")
                     and chunk == asset == image_bytes == expected and len(matching_slots) == 1
                     and assignment in generated and assignment not in filtered)
            if not valid:
                raise RuntimeError("new linked data ownership differs: " + name)
            results.append({"symbol": name, "module": module["name"],
                            "vram": f"0x{datum['vram']:08X}", "asset_offset": datum["offset"],
                            "section": section, "size": datum["size"],
                            "payload": expected.hex(), "linked_section": entries[0][6],
                            "exact": True})
    h.STAGE, h.HERE = cd_old_stage, cd_old_here
    if len(results) != 3:
        raise RuntimeError("new data record count differs")
    return results


def new_genuine_proof(modules: list[dict]) -> list[dict]:
    A.TMP = HERE / "collector_aspsx"
    A.TMP.mkdir(exist_ok=True)
    A.SLUS_ELF = STAGE / "build/slus_006.14.elf"
    A.SLUS_BIN = ROOT / "baserom/slus_006.14"
    A._SLUS = None
    records = []
    for (name, source, _parent, functions, _direct), module in zip(NEW, modules[-2:]):
        out = HERE / "genuine" / name
        out.mkdir(parents=True, exist_ok=True)
        row = {"id": "slus/" + name, "kind": "slus", "container": "slus",
               "c_path": source, "cell": module["recipe"]["ccver"],
               "flags": module["recipe"]["ccflags"],
               "row_asflags": module["recipe"]["asflags"]}
        with patch.object(verify, "MASPSX", GENERIC):
            fresh, error = verify._compile_slus_source(
                row, STAGE / source, out, STAGE / "include", root=STAGE)
        if fresh is None:
            raise RuntimeError("fresh collector generic compile: " + str(error))
        asm = verify.postprocess_slus((out / "a.s").read_text(), root=STAGE, names_only=True)
        lnk, error = A.run_aspsx(A.aspsx_input(asm), "2.79", ["-q"], out)
        if lnk is None:
            raise RuntimeError("fresh collector genuine assembly: " + str(error))
        (out / "genuine.lnk").write_bytes(lnk)
        obj_generic, obj_built = read_elf(fresh.read_bytes()), read_elf(
            (STAGE / "build" / Path(source).with_suffix(".o")).read_bytes())
        if module.get("data_pieces"):
            generic = A.data_piece_view(obj_generic, module)
            built = A.data_piece_view(obj_built, module)
            genuine = A.data_piece_view(A.read_lnk(lnk), module, generic, A.aliases(asm))
        else:
            generic, built = A.View(obj_generic), A.View(obj_built)
            genuine = A.View(A.read_lnk(lnk), generic, A.aliases(asm))
        if any(set(view.funcs) != set(functions) for view in (generic, built, genuine)):
            raise RuntimeError("collector whole physical TU scope differs: " + name)
        gb = A.compare_units(generic, built, functions)
        gg = A.compare_units(generic, genuine, functions)
        retail = {label: A.retail_compare(view, functions, "slus")
                  for label, view in (("fresh_generic", generic), ("built_generic", built),
                                      ("genuine", genuine))}
        if (not gb["exact"] or not gg["exact"] or gb["len_m"] != gb["len_g"]
                or gg["len_m"] != gg["len_g"] or
                any(value != {"diff": 0, "masked": 0, "checked": len(functions)}
                    for value in retail.values())):
            raise RuntimeError("new owner generic/genuine/retail mismatch: " + name)
        records.append({"owner": name, "functions": list(functions), "words": gg["len_m"],
                        "recipe": module["recipe"], "assembly_sha256": sha(out / "a.s"),
                        "fresh_generic_sha256": sha(fresh),
                        "built_generic_sha256": sha(STAGE / "build" / Path(source).with_suffix(".o")),
                        "genuine_lnk_sha256": digest(lnk),
                        "generic_vs_built": {k: gb[k] for k in ("exact", "diff", "len_m", "len_g", "missing")},
                        "generic_vs_genuine": {k: gg[k] for k in ("exact", "diff", "len_m", "len_g", "missing")},
                        "retail": retail})
    if sum(x["words"] for x in records) != 17:
        raise RuntimeError("new collector word count differs from 6 + 11")
    return records


def run_rehearsal() -> dict:
    before = pins()
    h, r, a = helpers()
    # Candidate modules are loaded under private names; production tooling is
    # intentionally left untouched. The build stage gets the reviewed copies.
    sys.path.insert(0, str(TOOLS / "build"))
    candidate_modules = load_module("ready29_candidate_modules", TOOLS / "build/slus_modules.py")
    candidate_partitions = load_module("ready29_candidate_partitions", TOOLS / "build/slus_partitions.py")
    # The data-piece verifier and projected ASPSX view import this name lazily.
    # Bind that import to the exact candidate schema used by the stage graph.
    sys.modules["slus_modules"] = candidate_modules
    candidate_partitions.slus_modules = candidate_modules
    candidate_partitions.load_manifest = candidate_modules.load_manifest
    candidate_partitions.logical_edges = candidate_modules.logical_edges
    modules, plan = clone_and_stage(h, candidate_partitions)
    physical, graph = graph_and_sources(candidate_partitions, modules, plan)
    build = all_generic_build(physical)
    objects = object_and_closure_proof(a, candidate_partitions, physical, modules, plan)
    r.STAGE, r.HERE = STAGE, HERE / "ready18"
    r.HERE.mkdir(exist_ok=True)
    old_data = r.data_proof(modules[:30])
    old_genuine = r.genuine_proof(modules[:30])
    if len(old_data) != 56 or not all(x["exact"] for x in old_data):
        raise RuntimeError("ready18 owned data changed")
    if (len(old_genuine) != 12 or sum(len(x["functions"]) for x in old_genuine) != 18
            or sum(x["generic_vs_genuine"]["len_m"] for x in old_genuine) != 891):
        raise RuntimeError("ready18 fresh genuine scope changed")
    for item in old_genuine:
        if (not item["generic_vs_built"]["exact"] or not item["generic_vs_genuine"]["exact"]
                or any(v != {"diff": 0, "masked": 0, "checked": len(item["functions"])}
                       for v in item["retail"].values())):
            raise RuntimeError("ready18 generic/genuine/retail changed: " + item["physical"])
    h.STAGE, h.HERE = STAGE, HERE / "cd8"
    cd_data = h.linked_data_proof(modules[30])
    cd_genuine = h.genuine_owner_proof(modules[30])
    new_data = new_data_proof(h, modules)
    new_genuine = new_genuine_proof(modules)
    if (len(cd_data), cd_genuine["words"], len(cd_genuine["functions"]),
            len(new_data), sum(x["words"] for x in new_genuine)) != (11, 1041, 8, 3, 17):
        raise RuntimeError("fresh 29-function/70-record scope differs")
    for item in old_data:
        if not item["exact"]:
            raise RuntimeError("old data proof not exact")
    after = snap_production()
    if after != before["production"]:
        raise RuntimeError("production code/config/build bytes or objects changed")
    if pins() != before:
        raise RuntimeError("frozen stage, tool, source, or assembler inputs changed")
    result = {
        "status": "MATCH", "scope": "private all-generic 860-physical-object ready29 rehearsal",
        "pins_sha256": sha(PINS), "production_unchanged": True,
        "stage": str(STAGE.relative_to(ROOT)), "graph": graph, "build": build,
        "objects": objects,
        "source_hashes": {name: sha(STAGE / name) for name in (
            "src/c8_accessors_owned.c", "src/b1b_b1c_table_owned.c",
            "src/w_8003F624.c", "config/slus_modules.json",
            "config/slus_partitions.json", "tools/configure.py",
            "tools/slus_modules.py", "tools/slus_partitions.py")},
        "comment_only_f624": True,
        "fresh_ready18_genuine": old_genuine, "fresh_ready18_data": old_data,
        "fresh_cd8_genuine": cd_genuine, "fresh_cd8_data": cd_data,
        "fresh_collectors_genuine": new_genuine, "fresh_collectors_data": new_data,
        "measured": {"functions": 29, "words": 1949, "data_records": 70,
                     "genuine_version": "2.79", "retail_masks": 0},
        "scope_limit": "Private generated full SLUS build with all 860 active C objects using the guarded generic assembler.",
    }
    RECEIPT.write_text(json.dumps(result, indent=2, sort_keys=True) + "\n")
    return result


if __name__ == "__main__":
    try:
        outcome = run_rehearsal()
        print(json.dumps({"status": outcome["status"], "physical": outcome["graph"]["physical"],
                          "logical": outcome["graph"]["logical"],
                          "measured": outcome["measured"], "image": outcome["build"]["image_sha256"]},
                         sort_keys=True))
    except Exception as exc:
        RECEIPT.write_text(json.dumps({"status": "ERROR", "error": str(exc),
                                       "traceback": traceback.format_exc()}, indent=2) + "\n")
        raise
