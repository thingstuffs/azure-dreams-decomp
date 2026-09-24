#!/usr/bin/env python3
"""Refresh the private 18-function rehearsal on the CD-contract baseline."""

from __future__ import annotations

import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[3]
HERE = Path(__file__).resolve().parent
STAGE = HERE / "stage"
READY = ROOT / "work/native_lane/gp_ready_combined"
GUARD = ROOT / "work/native_lane/gp_order_bytes_guard_link"
PAIR = ROOT / "work/native_lane/gp_af3_pair_link"
GENERIC = ROOT / "work/native_lane/selfinc_local_guard/candidate/maspsx.py"
PREPARED = ("w_8003FAD4", "w_80041588", "w_80041AB0", "w_80043CD0", "w_8004AB7C")
NEW_MODULES = ("w_80047E78_owned", "w_80053CFC_owned", "gp_shared_8152c",
               "gp_d92c_owned", "gp_order_bytes_owner", "w_8004437C_pair")
MESSAGE = ROOT / "work/native_lane/gp_81550_partition"
CANDIDATE = MESSAGE / "candidate_small"
MESSAGE_NAME = "message_mode_81550"
MESSAGE_STEM = "w_8004DCEC_owned"
MESSAGE_SOURCE = f"src/{MESSAGE_STEM}.c"
MESSAGE_MEMBER_STEMS = ("w_8004DCEC", "w_8004DE88", "w_8004DF8C")
MESSAGE_FUNCTIONS = ("func_8004DCE0", "func_8004DCEC", "func_8004DE88", "func_8004DF8C")
MESSAGE_DATA = (("D_8008154C", 0xB0C, 0x8008154C),
                ("D_80081550", 0xB10, 0x80081550))
GENERIC_TUS = (*NEW_MODULES, *PREPARED, MESSAGE_STEM)
RECIPE_MOVES = ("w_8003D92C", *PREPARED, "w_8004450C")
OLD_DCEC_FLAGS = "-fno-schedule-insns -fno-delayed-branch"
BASELINE_COMMIT = "89b14658"
HISTORICAL = ROOT / "work/native_lane/gp_ready18_rebased_81554/receipt.json"
HISTORICAL_SHA256 = "008870714fd30469af92515e2d01abfadfe20b68bc04652e3f8f4380142f8a45"
CURRENT_PINS = {
    "tools/build/configure.py": "bab4b98f03b89c771c04d1ea3d937b1868c9cb24ebb0f7741a413546f43d51df",
    "tools/build/slus_data_pieces.py": "d72b0b7c9c910315dc1c344f64af6b6799d7036ee0709533d09422cbf28daea2",
    "tools/build/slus_modules.py": "69b68d32d0d2aef22f947bb985b067234c382d33a218d5517e21c496effc1b80",
    "tools/fidelity/aspsx_diff.py": "385c3d7ef4f10df3892c0b18653ca91edf14fdbe6ebac76452f0ea2c93a48d72",
    "tools/fidelity/prove_slus_ownership.py": "150a0313a0debadeeb86d6540e01c1e78e00650b1ef60e4e82c5c5466be5ac83",
    "tools/fidelity/slus_iso.py": "941818aa3d830c22c6182ad61dbdf34949a464cb0e2964b6afcef66d3b24dd95",
    "tools/slus_module_context.py": "ff9b39ef5f3f1625139d159750f035469828b14f7a9d36128e6e8adf6117953e",
    "tools/slus_module_evidence.py": "e86e46a050d0a2695b108d2c1351dd7c5fdcee9d37a01b85c0af17569af6230e",
    "tools/verify.py": "e9397d1b834aee8cacf4f2ef70d1bd61d451b8f49e2d44ada9a49d594b1fc34f",
    "include/slus/cd_state.h": "993ba6df16dd90218f278f09a180a1db6a8f8a3bfa3a03c41c0df73e684e3614",
    "src/slus/w_8003E34C.c": "98e8469122c514137781b87db5418652b536c4dbd19eae7918cf2c2a74662300",
    "src/slus/w_8003E4FC.c": "41db07c2944560af8d0f6fcc59c7e54a277315e2e2d5f80680050ddabdb90409",
    "src/slus/w_8003E758.c": "fc94a723170a1bbdd181980c8ec2038c1781a605ac58690e434440dc160ace3c",
    "src/slus/w_8003F2A4.c": "f88540f16d97fc219ae138ac63346a5e869fddc7e399b822943d29a7a67b9e51",
    "src/slus/w_8003F368.c": "c9c83f2e4c7932b08bbaf18cd3730d75fcbf6b5053c4882bc386324d97abbccb",
    "src/slus/w_8003F5AC.c": "a085b8463e5e6e819ad253960920d3fcf5f0616245397b2aad88f24006389ace",
    "src/slus/w_8003F624.c": "5a54136dec09906ac59b15668bf204e56572e83b2bdf74ffc6691640388df447",
}

sys.path[:0] = [str(ROOT / "tools"), str(ROOT / "tools/build"), str(ROOT / "tools/fidelity")]
from slus_iso import SlusView  # noqa: E402
from slus_modules import load_manifest, logical_edges, plan_asset_carves  # noqa: E402
from slus_partitions import load_plan, project_edges, validate_context, read_aliases  # noqa: E402
from slus_partitions import connected_context, expected_units, check_emitted  # noqa: E402
from row_db import edges_of  # noqa: E402
from objread import read_elf  # noqa: E402
import verify  # noqa: E402
import aspsx_diff as A  # noqa: E402


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def run(*argv: str) -> str:
    env = os.environ.copy()
    env.pop("AZURE_MASPSX", None)
    env.pop("AZURE_MASPSX_COMPANION", None)
    p = subprocess.run(argv, cwd=STAGE, env=env, text=True, capture_output=True)
    output = p.stdout + p.stderr
    if p.returncode:
        raise RuntimeError(f"{' '.join(argv)} exited {p.returncode}:\n{output[-5000:]}")
    return output


def materialize(name: str) -> None:
    path = STAGE / name
    if path.is_symlink():
        original = path.resolve()
        if not original.is_dir():
            raise RuntimeError("expected directory symlink: " + name)
        path.unlink()
        shutil.copytree(original, path, symlinks=False)
    if not path.is_dir() or not path.resolve().is_relative_to(STAGE.resolve()):
        raise RuntimeError("unsafe staged directory: " + name)
    for child in sorted(path.rglob("*")):
        if child.is_symlink():
            original = child.resolve()
            if not original.is_file():
                raise RuntimeError("unexpected nested directory symlink: " + str(child))
            data = original.read_bytes()
            mode = original.stat().st_mode & 0o777
            child.unlink()
            child.write_bytes(data)
            child.chmod(mode)
    if any(child.is_symlink() for child in path.rglob("*")):
        raise RuntimeError("unmaterialized staged symlink: " + name)


def production_snapshot() -> dict:
    """Fingerprint every active object and the production inputs this view reads."""
    head = subprocess.check_output(["git", "rev-parse", "HEAD"], cwd=ROOT, text=True).strip()
    assert head.startswith(BASELINE_COMMIT), f"unexpected baseline commit: {head}"
    assert all(sha(ROOT / path) == digest for path, digest in CURRENT_PINS.items()), \
        "current tool/CD input differs from reviewed 89b14658 baseline"
    pinned = ROOT / "ledger/splits/slus.build.ninja"
    physical = edges_of(pinned.read_text())
    assert len(physical) == 869
    paths = ["config/slus_modules.json", "config/slus_partitions.json",
             "config/names.tsv", "tools/build/configure.py",
             "ledger/splits/slus.build.ninja", "build_slus/build.ninja",
             "ledger/maspsx_dependence.jsonl",
             "build_slus/build/slus_006.14", "baserom/slus_006.14",
             "src/slus/code.c", "src/slus/code2.c",
             "src/slus/w_80041134_owned.c", "src/slus/w_80050DA8_owned.c",
             "src/slus/sort_rank_81540_owned.c",
             "src/slus/w_8004DCA8_owned.c", "src/slus/w_8004DCA8.c",
             "src/slus/w_8004DD2C.c", "src/slus/w_8004DDE4.c",
             "src/slus/w_8004E130.c", "include/slus/list_cursor_e0.h",
             "include/slus/saved_value_b98.h", "include/slus/sort_rank_81540.h",
             "include/slus/command_slots_81554.h", *CURRENT_PINS]
    return {"head": head, "files": {p: sha(ROOT / p) for p in dict.fromkeys(paths)},
            "active_objects": {e["out"]: sha(ROOT / "build_slus" / e["out"])
                               for e in physical}}


def historical_change_check(current: dict) -> dict:
    assert sha(HISTORICAL) == HISTORICAL_SHA256, "historical ready18 receipt changed"
    old = json.loads(HISTORICAL.read_text())["production_before"]
    changed_files = {path: {"old": digest, "current": current["files"][path]}
                     for path, digest in old["files"].items()
                     if current["files"].get(path) != digest}
    assert set(changed_files) == {"tools/build/configure.py"}, changed_files
    assert old["active_objects"] == current["active_objects"], \
        "production active object differs from historical ready18 baseline"
    return {"historical_receipt_sha256": HISTORICAL_SHA256,
            "changed_existing_pins": changed_files,
            "new_current_pins": {path: current["files"][path]
                                 for path in CURRENT_PINS if path not in old["files"]},
            "active_objects_unchanged": len(old["active_objects"])}


def source_inputs() -> tuple[list[dict], dict, dict]:
    baseline = load_manifest(ROOT / "config/slus_modules.json")
    assert len(baseline) == 23
    command = ROOT / "work/native_lane/gp_81554_partition"
    command_link = json.loads((command / "receipt.json").read_text())
    assert baseline[-1]["name"] == "command_slots_81554"
    assert baseline[-1] == load_manifest(command / "stage/config/slus_modules.json")[-1]
    assert sha(ROOT / "src/slus" / Path(baseline[-1]["source"]).name) == command_link["stage_owner_sha256"]
    assert sha(ROOT / "include/slus/command_slots_81554.h") == command_link["candidate_sha256"]["include/slus/command_slots_81554.h"]
    for member in baseline[-1]["members"]:
        filename = Path(member["source"]).name
        assert sha(ROOT / "src/slus" / filename) == command_link["candidate_sha256"][filename]
    assert sha(ROOT / "build_slus/build/src/w_8004DCA8_owned.o") == command_link["built_owner_object_sha256"]
    prior_ready = load_manifest(READY / "candidate_manifest.json")
    prior_guard = load_manifest(GUARD / "manifest.json")
    prior_pair = load_manifest(PAIR / "manifest.json")
    assert len(prior_ready) == 20 and len(prior_guard) == 18 and len(prior_pair) == 20
    additions = [*prior_ready[16:], prior_guard[-1], prior_pair[-1]]
    assert tuple(m["source"].removeprefix("src/").removesuffix(".c") for m in additions) == NEW_MODULES
    message_module = {
        "name": MESSAGE_NAME, "source": MESSAGE_SOURCE,
        "members": [{"id": f"slus/{stem}", "source": f"src/{stem}.c",
                     "functions": [f"func_{stem.rsplit('_', 1)[1]}"]}
                    for stem in MESSAGE_MEMBER_STEMS],
        "headers": ["include/common.h", "include/slus/message_mode_81550.h"],
        "recipe": {"ccver": "2.7.2-cdk", "ccflags": "", "asflags": ""},
        "data": [{"symbol": name, "asset": "assets/54240.bin", "offset": offset,
                  "size": 4, "vram": vram, "bytes": "00000000", "section": ".sdata"}
                 for name, offset, vram in MESSAGE_DATA],
        "evidence": "docs/evidence/gp_81550_partition.md",
    }
    assert message_module == load_manifest(MESSAGE / "stage/config/slus_modules.json")[-1]
    additions.append(message_module)
    assert not {m["name"] for m in additions} & {m["name"] for m in baseline}
    assert not {m["source"] for m in additions} & {m["source"] for m in baseline}
    manifest = json.loads((ROOT / "config/slus_modules.json").read_text())
    manifest["modules"].extend(additions)
    sources = {}
    hashes = {}
    old_hashes = json.loads((READY / "source_hashes.json").read_text())
    for path in sorted((READY / "sources").glob("*.c")):
        stem = path.stem
        sources[stem] = path
        hashes[stem] = sha(path)
    assert len(sources) == 10
    for stem in PREPARED:
        assert hashes[stem] == old_hashes[f"slus/{stem}"]["prepared"]
        assert sha(ROOT / f"src/slus/{stem}.c") == old_hashes[f"slus/{stem}"]["current"]
    assert hashes["w_80053CFC"] == old_hashes["w_80053CFC_repaired"]
    sources["gp_order_bytes_owner"] = GUARD / "gp_order_bytes_owner.c"
    guard_receipt = json.loads((GUARD / "receipt.json").read_text())
    assert sha(sources["gp_order_bytes_owner"]) == guard_receipt["source_equal"]["candidate_sha256"]
    for stem in ("w_8004437C", "w_8004450C", "w_8004437C_pair"):
        sources[stem] = PAIR / "stage/src" / f"{stem}.c"
    pair_receipt = json.loads((PAIR / "receipt.json").read_text())
    for stem in ("w_8004437C", "w_8004450C"):
        assert sha(sources[stem]) == pair_receipt["inputs"]["candidate_sources"][stem]
    assert sha(sources["w_8004437C_pair"]) == pair_receipt["inputs"]["private_aggregator_sha256"]
    direct = json.loads((MESSAGE / "final_direct_receipt.json").read_text())
    assert direct["generic_vs_genuine"] == {
        "exact": True, "diff": 0, "len_m": 156, "len_g": 156, "missing": []}
    assert tuple(direct["physical_functions"]) == MESSAGE_FUNCTIONS
    for stem in (*MESSAGE_MEMBER_STEMS, MESSAGE_STEM):
        path = CANDIDATE / f"{stem}.c"
        assert sha(path) == direct["candidate_sha256"][f"{stem}.c"]
        sources[stem] = path
    header = CANDIDATE / "include/slus/message_mode_81550.h"
    assert sha(header) == direct["candidate_sha256"]["include/slus/message_mode_81550.h"]
    review = json.loads((MESSAGE / "primary_review.json").read_text())
    assert review["script_view_bytes"] == 2 and not review["b6c_storage_owned"]
    for path, digest in review["review_sources_sha256"].items():
        assert sha(ROOT / path) == digest
    for stem, path in sources.items():
        hashes[stem] = sha(path)
    guard_pkg = sha(GENERIC.parent / "maspsx/__init__.py")
    assert guard_pkg == "28e45bbcf00fc90dc0645250f233b73f96ad11d06a2f8230ce533fc2fafbbfbe"
    inputs = {
        "production_manifest_sha256": sha(ROOT / "config/slus_modules.json"),
        "command_81554_receipt_sha256": sha(command / "receipt.json"),
        "command_81554_owner_object_sha256": command_link["built_owner_object_sha256"],
        "production_partition_sha256": sha(ROOT / "config/slus_partitions.json"),
        "production_symbols_sha256": sha(ROOT / "config/slus_006.14.symbols.txt"),
        "production_configure_sha256": sha(ROOT / "tools/build/configure.py"),
        "production_image_sha256": sha(ROOT / "build_slus/build/slus_006.14"),
        "retail_sha256": sha(ROOT / "baserom/slus_006.14"),
        "guarded_cli_sha256": sha(GENERIC), "guarded_package_sha256": guard_pkg,
        "source_sha256": hashes,
        "source_provenance": {stem: str(path.relative_to(ROOT)) for stem, path in sources.items()},
        "message_header_sha256": sha(header),
        "message_direct_receipt_sha256": sha(MESSAGE / "final_direct_receipt.json"),
        "b6c_primary_review_sha256": sha(MESSAGE / "primary_review.json"),
    }
    assert inputs["production_image_sha256"] == inputs["retail_sha256"]
    return additions, manifest, {"paths": sources, "hashes": hashes, "inputs": inputs}


def prepare() -> tuple[list[dict], list[dict], dict]:
    production_before = production_snapshot()
    historical_changes = historical_change_check(production_before)
    additions, manifest, source_info = source_inputs()
    if STAGE.exists():
        shutil.rmtree(STAGE)
    view = SlusView(STAGE)
    control = view.calibrate()
    assert control["result"] == "MATCH"
    for name in ("src", "config", "tools", "include"):
        materialize(name)
    assert not any((STAGE / n).is_symlink() for n in ("src", "config", "tools", "include"))
    staged_current = {}
    for production_path in CURRENT_PINS:
        if production_path.startswith("tools/build/"):
            stage_path = "tools/" + Path(production_path).name
        elif production_path.startswith("src/slus/"):
            stage_path = "src/" + Path(production_path).name
        elif production_path.startswith("include/"):
            stage_path = production_path
        else:
            continue  # Fidelity tools are imported from ROOT, checked in production_snapshot.
        staged_current[stage_path] = sha(STAGE / stage_path)
        assert staged_current[stage_path] == CURRENT_PINS[production_path], \
            f"staged tool/CD input is stale: {stage_path}"
    for stem, path in source_info["paths"].items():
        target = STAGE / f"src/{stem}.c"
        assert not target.is_symlink()
        target.write_bytes(path.read_bytes())
        assert sha(target) == source_info["hashes"][stem]
    header = STAGE / "include/slus/message_mode_81550.h"
    assert not header.exists()
    header.write_bytes((CANDIDATE / "include/slus/message_mode_81550.h").read_bytes())
    assert sha(header) == source_info["inputs"]["message_header_sha256"]
    config = STAGE / "tools/configure.py"
    text = config.read_text()
    anchor = 'cfiles = sorted(glob.glob("src/*.c"))'
    assert text.count(anchor) == 1
    overrides = "CC_VER.update({\n" + "".join(
        f'    "src/{stem}.c": ("2.7.2-cdk", ""),\n'
        for stem in (*RECIPE_MOVES, "w_8004DCEC")) + "})\n"
    config.write_text(text.replace(anchor, overrides + anchor, 1))
    manifest_path = STAGE / "config/slus_modules.json"
    plan_before = load_plan(ROOT / "config/slus_partitions.json")
    assert load_plan(STAGE / "config/slus_partitions.json") == plan_before
    plan_path = STAGE / "config/slus_partitions.json"
    plan_doc = json.loads(plan_path.read_text())
    code = next(p for p in plan_doc["parents"] if p["id"] == "slus/code")
    assert "func_8004DCE0" in code["functions"]
    code["parts"].append({"module": MESSAGE_NAME, "functions": ["func_8004DCE0"]})
    plan_path.write_text(json.dumps(plan_doc, indent=2) + "\n")
    plan = load_plan(plan_path)
    assert len(plan) == len(plan_before)
    for old, new in zip(plan_before, plan):
        assert old["id"] == new["id"]
        if old["id"] == "slus/code":
            assert old["parts"] == new["parts"][:-1]
            assert {k: old[k] for k in old if k != "parts"} == {
                k: new[k] for k in new if k != "parts"}
        else:
            assert old == new
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n")
    modules = load_manifest(manifest_path)
    assert len(modules) == 30 and modules[:23] == load_manifest(ROOT / "config/slus_modules.json")
    plans = plan_asset_carves(modules, STAGE)
    (HERE / "manifest.json").write_text(manifest_path.read_text())
    receipt = {"control": control, "inputs": source_info["inputs"],
               "baseline_changes": historical_changes,
               "stage_current_inputs": staged_current,
               "private_manifest_sha256": sha(manifest_path),
               "private_configure_sha256": sha(config),
               "production_before": production_before,
               "partition_plan_sha256": sha(plan_path),
               "modules": {"baseline": 23, "trial": 30,
                           "new": [m["name"] for m in additions]},
               "asset_plan_count": len(plans)}
    return modules, plan, receipt


def scope_generic(ninja: str) -> str:
    rule = ("rule cc_guarded_private\n"
            f"  command = AZURE_MASPSX_COMPANION={GENERIC} tools/cc.sh $in $out $ccver \"$ccflags\" \"$asflags\"\n"
            "  description = CC-GUARDED-PRIVATE $in\n\n")
    assert ninja.count("rule cc\n") == 1
    ninja = ninja.replace("rule cc\n", rule + "rule cc\n", 1)
    for stem in GENERIC_TUS:
        old = f"build build/src/{stem}.o: cc src/{stem}.c"
        new = f"build build/src/{stem}.o: cc_guarded_private src/{stem}.c"
        assert ninja.count(old) == 1, stem
        ninja = ninja.replace(old, new, 1)
    actual = re.findall(r"(?m)^build build/src/([^\n ]+)\.o: cc_guarded_private ", ninja)
    assert len(actual) == len(GENERIC_TUS) == 12 and set(actual) == set(GENERIC_TUS)
    return ninja


def link_symbols(names: set[str]) -> dict:
    output = run("mipsel-linux-gnu-readelf", "-Ws", str(STAGE / "build/slus_006.14.elf"))
    result = {name: [] for name in names}
    for line in output.splitlines():
        fields = line.split()
        if len(fields) >= 8 and fields[-1] in names:
            result[fields[-1]].append({"address": int(fields[1], 16),
                                        "binding": fields[4], "section": fields[6]})
    return result


def data_proof(modules: list[dict]) -> list[dict]:
    names = {d["symbol"] for m in modules for d in m["data"]}
    linked = link_symbols(names)
    generated = (STAGE / "config/generated/slus_006.14.undefined_syms.txt").read_text()
    filtered = (STAGE / "build/slus_006.14.undefined_syms.modules.txt").read_text()
    image = (STAGE / "build/slus_006.14").read_bytes()
    results = []
    plans = plan_asset_carves(modules, STAGE)
    for m in modules:
        if not m["data"]:
            continue
        obj_path = STAGE / "build" / Path(m["source"]).with_suffix(".o")
        obj = read_elf(obj_path.read_bytes())
        for d in m["data"]:
            name = d["symbol"]
            section = d["section"]
            first_offset = next(x["offset"] for x in m["data"] if x["section"] == section)
            offset = d["offset"] - first_offset
            owned = obj.symbols.get(name)
            object_bytes = obj.sections.get(section, b"")[offset:offset + d["size"]]
            asset_bytes = (STAGE / d["asset"]).read_bytes()[d["offset"]:d["offset"] + d["size"]]
            image_offset = d["vram"] - 0x8002D000 + 0x800
            image_bytes = image[image_offset:image_offset + d["size"]]
            slot = next(s for p in plans if p["asset"] == d["asset"]
                        for s in p["slots"] if s["kind"] == "module_data" and name in s["symbols"])
            assignment = f"{name} = 0x{d['vram']:08X};"
            result = {"symbol": name, "module": m["name"], "section": section,
                      "object": owned, "linked": linked[name], "asset_offset": d["offset"],
                      "asset_bytes": asset_bytes.hex(), "object_bytes": object_bytes.hex(),
                      "image_bytes": image_bytes.hex(), "carve": slot,
                      "generated_assignment": assignment in generated,
                      "filtered_assignment_absent": assignment not in filtered}
            result["exact"] = (
                owned is not None and owned[:2] == (section, offset) and
                len(linked[name]) == 1 and linked[name][0]["address"] == d["vram"] and
                linked[name][0]["section"] != "ABS" and
                asset_bytes == object_bytes == image_bytes == bytes.fromhex(d["bytes"]) and
                slot["section"] == section and
                slot["object"] == f"build/{Path(m['source']).with_suffix('.o')}" and
                result["generated_assignment"] and result["filtered_assignment_absent"])
            if name == "D_80080AF3":
                result["exact"] &= owned[2] == "global" and linked[name][0]["binding"] == "GLOBAL"
            if name == "D_80080AFC":
                result["exact"] &= owned[2] == "local" and linked[name][0]["binding"] == "LOCAL"
            results.append(result)
    assert len(results) == sum(len(m["data"]) for m in modules) == 56
    new = [r for r in results if r["module"] == MESSAGE_NAME]
    assert len(new) == 2 and {r["symbol"] for r in new} == {
        "D_8008154C", "D_80081550"} and all(r["exact"] for r in new)
    active_command = [r for r in results if r["module"] == "command_slots_81554"]
    assert len(active_command) == 2 and {r["symbol"] for r in active_command} == {
        "D_80081554", "D_80081558"} and all(r["exact"] for r in active_command)
    return results


def genuine_proof(modules: list[dict]) -> list[dict]:
    A.TMP = HERE / "a"
    A.TMP.mkdir(exist_ok=True)
    A.SLUS_ELF = STAGE / "build/slus_006.14.elf"
    A.SLUS_BIN = ROOT / "baserom/slus_006.14"
    A._SLUS = None
    mapping = {Path(m["source"]).stem: [f for member in m["members"]
                                         for f in member["functions"]] for m in modules[23:]}
    mapping[MESSAGE_STEM] = list(MESSAGE_FUNCTIONS)
    mapping.update({stem: ["func_" + stem.rsplit("_", 1)[1]] for stem in PREPARED})
    assert len(mapping) == 12 and sum(map(len, mapping.values())) == 18
    records = []
    for stem, funcs in mapping.items():
        m = next((m for m in modules[23:] if Path(m["source"]).stem == stem), None)
        recipe = m["recipe"] if m else {"ccver": "2.7.2-cdk", "ccflags": "", "asflags": ""}
        out = HERE / "genuine" / stem
        out.mkdir(parents=True, exist_ok=True)
        row = {"id": f"slus/{stem}", "kind": "slus", "container": "slus",
               "c_path": f"src/{stem}.c",
               "cell": recipe["ccver"],
               "flags": recipe["ccflags"], "row_asflags": recipe["asflags"]}
        with patch.object(verify, "MASPSX", GENERIC):
            compiled, error = verify.compile_slus(row, STAGE / f"src/{stem}.c", out,
                                                   include_root=STAGE / "include")
        if compiled is None:
            raise RuntimeError(f"{stem}: fresh generic compile: {error}")
        generic = A.View(A.read_elf(compiled.read_bytes()))
        built = A.View(A.read_elf((STAGE / f"build/src/{stem}.o").read_bytes()))
        if set(generic.funcs) != set(funcs) or set(built.funcs) != set(funcs):
            raise RuntimeError(f"{stem}: fresh/built physical function set differs from declared scope")
        asm = verify.postprocess_slus((out / "a.s").read_text(), names_only=True)
        mode = ["-q"] if stem == MESSAGE_STEM else ["-q", "-0"]
        lnk, error = A.run_aspsx(A.aspsx_input(asm), "2.79", mode, out)
        if lnk is None:
            raise RuntimeError(f"{stem}: genuine ASPSX: {error}")
        (out / "genuine.lnk").write_bytes(lnk)
        genuine = A.View(A.read_lnk(lnk), generic, A.aliases(asm))
        if stem == MESSAGE_STEM:
            for func in funcs:
                genuine.add_unit(func, generic)
        gb = A.compare_units(generic, built, funcs)
        gg = A.compare_units(generic, genuine, funcs)
        retail = {name: A.retail_compare(view, funcs, "slus")
                  for name, view in (("generic", generic), ("genuine", genuine))}
        records.append({"physical": stem, "functions": funcs, "recipe": recipe,
                        "generic_vs_built": {key: gb[key] for key in ("exact", "diff", "len_m", "len_g", "missing")},
                        "generic_vs_genuine": {key: gg[key] for key in ("exact", "diff", "len_m", "len_g", "missing")},
                        "retail": retail, "assembly_sha256": sha(out / "a.s"),
                        "generic_obj_sha256": sha(compiled),
                        "genuine_lnk_sha256": sha(out / "genuine.lnk"), "genuine_mode": mode})
        (HERE / "genuine_receipt.json").write_text(json.dumps(records, indent=2) + "\n")
    assert sum(r["generic_vs_genuine"]["len_m"] for r in records) == 891
    return records


def closure_proof(modules: list[dict], plan: list[dict]) -> dict:
    parents, owners = connected_context("slus/code", plan, modules)
    expected_names = {"list_cursor_e0", "saved_value_b98", "sort_rank_81540",
                      "command_slots_81554", MESSAGE_NAME}
    assert {p["id"] for p in parents} == {"slus/code", "slus/code2"}
    assert {m["name"] for m in owners} == expected_names
    expected = expected_units(parents, owners)
    counts = {source: len(functions) for source, functions in expected.items()}
    assert counts == {
        "src/code.c": 151, "src/code2.c": 23,
        "src/w_80041134_owned.c": 3, "src/w_80050DA8_owned.c": 3,
        "src/sort_rank_81540_owned.c": 2,
        "src/w_8004DCA8_owned.c": 5, MESSAGE_SOURCE: 4,
    }
    assert sum(counts.values()) == 191
    emitted = {}
    for source in expected:
        obj = read_elf((STAGE / "build/src" / (Path(source).stem + ".o")).read_bytes())
        emitted[source] = [name for name, symbol in obj.symbols.items()
                           if symbol[2] == "func" and symbol[0] and
                           (symbol[0] == ".text" or symbol[0].startswith(".text."))]
    check_emitted(expected, emitted)
    return {"parents": [p["id"] for p in parents],
            "owners": [m["name"] for m in owners],
            "function_counts": counts, "total_functions": 191,
            "collector_genuine_exact_claim": False}


def prove() -> dict:
    modules, plan, receipt = prepare()
    configured = run("python3", "tools/configure.py")
    assert load_plan(STAGE / "config/slus_partitions.json") == plan
    ninja = scope_generic((STAGE / "build.ninja").read_text())
    (STAGE / "build.ninja").write_text(ninja)
    physical = edges_of(ninja.replace(": cc_guarded_private ", ": cc "))
    baseline_physical = edges_of((ROOT / "ledger/splits/slus.build.ninja").read_text())
    old_outputs = {e["out"] for e in baseline_physical}
    new_outputs = {e["out"] for e in physical}
    additions = modules[23:]
    removed = {f"build/{Path(member['source']).with_suffix('.o')}"
               for module in additions for member in module["members"]}
    added = {f"build/{Path(module['source']).with_suffix('.o')}" for module in additions}
    expected_physical = len(baseline_physical) - len(removed) + len(added)
    assert len(removed) == 12 and len(added) == 7
    assert len(physical) == expected_physical == 864
    assert old_outputs - new_outputs == removed and new_outputs - old_outputs == added
    logical = logical_edges(project_edges(physical, plan), modules)
    historical = {edge["src"]: edge for edge in map(
        json.loads, (ROOT / "ledger/splits/slus.jsonl").read_text().splitlines())}
    validate_context(plan, modules, logical, STAGE / "raw/slus",
                     read_aliases(STAGE / "config/names.tsv"))
    baseline_modules = load_manifest(ROOT / "config/slus_modules.json")
    baseline_plan = load_plan(ROOT / "config/slus_partitions.json")
    baseline_logical = logical_edges(project_edges(baseline_physical, baseline_plan), baseline_modules)
    baseline_by_source = {edge["src"]: edge for edge in baseline_logical}
    baseline_history_differences = [(edge, historical[edge["src"]]) for edge in baseline_logical
                                    if edge != historical[edge["src"]]]
    assert baseline_history_differences == []
    differences = [(edge, baseline_by_source.get(edge["src"])) for edge in logical
                   if edge != baseline_by_source.get(edge["src"])]
    assert len(logical) == len(baseline_logical) == 884
    assert set(historical) == set(baseline_by_source) == {e["src"] for e in logical}
    assert {Path(edge["src"]).stem for edge, _ in differences} == {
        *RECIPE_MOVES, "w_8004DCEC"}
    assert len(differences) == 8
    for edge, old in differences:
        if edge["src"] == "src/w_8004DCEC.c":
            assert edge["ccver"] == old["ccver"] == "2.7.2-cdk"
            assert edge["ccflags"] == "" and old["ccflags"] == OLD_DCEC_FLAGS
            assert all(edge[k] == old[k] for k in ("src", "out", "asflags"))
        else:
            assert edge["ccver"] == "2.7.2-cdk" and old["ccver"] == "2.7.2"
            assert all(edge[k] == old[k] for k in ("src", "out", "ccflags", "asflags"))
    build = run("ninja", "-j", "4", "build/slus_006.14")
    (HERE / "build.log").write_text(build)
    prior_objects = {}
    for stem in GENERIC_TUS:
        if stem == MESSAGE_STEM:
            prior = MESSAGE / "owner_built.o"
        else:
            prior_dir = READY / "view" if stem in (*NEW_MODULES[:4], *PREPARED) else (
                GUARD / "stage" if stem == "gp_order_bytes_owner" else PAIR / "stage")
            prior = prior_dir / f"build/src/{stem}.o"
        current = STAGE / f"build/src/{stem}.o"
        prior_objects[stem] = {"prior_sha256": sha(prior), "combined_sha256": sha(current),
                               "identical": prior.read_bytes() == current.read_bytes()}
    assert len(prior_objects) == 12 and all(x["identical"] for x in prior_objects.values())
    image = STAGE / "build/slus_006.14"
    retail = ROOT / "baserom/slus_006.14"
    changed_outside = []
    baseline_objects = receipt["production_before"]["active_objects"]
    intentionally_changed = {f"build/src/{stem}.o" for stem in PREPARED}
    intentionally_changed.add("build/src/code.o")
    outside = sorted((old_outputs & new_outputs) - intentionally_changed)
    for output in outside:
        if sha(STAGE / output) != baseline_objects[output]:
            changed_outside.append(output)
    assert len(outside) == len(old_outputs) - len(removed) - len(PREPARED) - 1 == 851
    data = data_proof(modules)
    closure = closure_proof(modules, plan)
    genuine = genuine_proof(modules)
    live_gp = {r["id"] for r in map(
        json.loads, (ROOT / "ledger/maspsx_dependence.jsonl").read_text().splitlines())
        if r["cause"] == "small-extern $gp model (.extern sizes)" or
        r["cause"] == "combined: extern-abs+no:all-fired"}
    ready_ids = {f"slus/{member['source'].removeprefix('src/').removesuffix('.c')}"
                 for m in modules[23:] for member in m["members"]}
    ready_ids.update(f"slus/{stem}" for stem in PREPARED)
    assert len(ready_ids) == 17 and len(ready_ids & live_gp) == 12
    already_owned_ids = {member["id"] for member in baseline_modules[-1]["members"]}
    assert len(already_owned_ids) == 4 and not already_owned_ids & ready_ids
    production_after = production_snapshot()
    assert production_after == receipt["production_before"], "production inputs changed during private trial"
    result = {**receipt, "configure": configured.strip(),
              "edges": {"physical": len(physical), "logical": len(logical),
                        "differences": differences,
                        "baseline_historical_recipe_differences": baseline_history_differences,
                        "removed_outputs": sorted(removed), "added_outputs": sorted(added),
                        "delta_from_modules": len(added) - len(removed)},
              "generic_physical_tus": list(GENERIC_TUS),
              "proved_object_reuse": prior_objects,
              "build_tail": build.splitlines()[-10:],
              "image": {"retail_exact": image.read_bytes() == retail.read_bytes(),
                        "sha256": sha(image)},
              "outside_objects": {"checked": len(outside), "changed": changed_outside},
              "production_after": production_after,
              "production_unchanged": production_after == receipt["production_before"],
              "data": data, "genuine": genuine, "connected_closure": closure,
              "collector_context": {
                  "code_partition_contributes": ["func_8004DCE0"],
                  "code_remainder_functions": 151,
                  "whole_collector_genuine_exact_claim": False,
              },
              "b6c_review": {
                  "review": "work/native_lane/gp_81550_partition/b6c_primary_review.md",
                  "review_sha256": sha(MESSAGE / "b6c_primary_review.md"),
                  "used_script_view_bytes": 2,
                  "historical_allocation_size_claimed": False,
                  "storage_ownership_claimed": False,
                  "note": "Opcode 0x23 and sentinel lookahead use two bytes; the private char[2] view is accepted for this command path. Full historical allocation size and constness remain unclaimed.",
              },
              "scope_limit": "Private selective generic assembly only; not production readiness or a global assembler-transition gate.",
              "cohort": {"current_gp_count": len(live_gp),
                         "current_gp_ids": sorted(live_gp),
                         "ready_gp_ids": sorted(ready_ids & live_gp),
                         "ready_other_ids": sorted(ready_ids - live_gp),
                         "already_owned_gp_ids": sorted(already_owned_ids & live_gp),
                         "remaining_gp_ids": sorted(live_gp - ready_ids - already_owned_ids),
                         "remaining_gp_count": len(live_gp - ready_ids - already_owned_ids)}}
    result["full_gate"] = (result["image"]["retail_exact"] and
                           not changed_outside and all(d["exact"] for d in data) and
                           all(r["generic_vs_built"]["exact"] and
                               r["generic_vs_genuine"]["exact"] and
                               all(x == {"diff": 0, "masked": 0, "checked": len(r["functions"])}
                                   for x in r["retail"].values()) for r in genuine))
    (HERE / "receipt.json").write_text(json.dumps(result, indent=2) + "\n")
    if not result["full_gate"]:
        raise RuntimeError("private 18-function combined gate failed; inspect receipt.json")
    return result


if __name__ == "__main__":
    receipt = prove()
    print(json.dumps({"full_gate": receipt["full_gate"], "image": receipt["image"],
                      "edges": receipt["edges"], "generic_tus": len(receipt["generic_physical_tus"]),
                      "genuine_rows": sum(len(x["functions"]) for x in receipt["genuine"]),
                      "genuine_words": sum(x["generic_vs_genuine"]["len_m"] for x in receipt["genuine"]),
                      "data_symbols": len(receipt["data"]),
                      "cohort": receipt["cohort"]}, indent=2))
