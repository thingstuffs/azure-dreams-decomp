#!/usr/bin/env python3
"""Isolated all-active-SLUS generic-assembler inventory on the ready26 stage."""

from __future__ import annotations

from collections import Counter
from difflib import SequenceMatcher
import hashlib
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
GENERIC = ROOT / "work/native_lane/selfinc_local_guard/candidate/maspsx.py"
GENERIC_PACKAGE = GENERIC.parent / "maspsx/__init__.py"
STAGE = HERE / "stage"
PINS = HERE / "baseline_pins.json"
RECEIPT = HERE / "receipt.json"
IMAGE = "build/slus_006.14"
PRODUCTION_FILES = (
    "config/slus_modules.json", "config/slus_partitions.json",
    "build_slus/build.ninja", "build_slus/build/slus_006.14",
    "baserom/slus_006.14", "src/slus/code.c", "src/slus/code2.c",
    "tools/build/configure.py", "tools/build/slus_data_pieces.py",
    "tools/fidelity/aspsx_diff.py", "tools/maspsx/maspsx.py",
)

sys.path[:0] = [str(ROOT / "tools"), str(ROOT / "tools/build"), str(ROOT / "tools/fidelity")]
from row_db import edges_of  # noqa: E402
from slus_modules import load_manifest  # noqa: E402
from slus_data_pieces import verify_data_pieces  # noqa: E402
from objread import read_elf  # noqa: E402
import aspsx_diff as A  # noqa: E402


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def sha(path: Path) -> str:
    return digest(path.read_bytes())


def physical_edges(stage: Path) -> tuple[list[dict], int]:
    text = (stage / "build.ninja").read_text()
    guarded = len(re.findall(r"(?m)^build \S+: cc_guarded_private ", text))
    normalized = text.replace(": cc_guarded_private ", ": cc ")
    edges = edges_of(normalized)
    if len(edges) != 858 or guarded != 13 or len({e["out"] for e in edges}) != 858:
        raise RuntimeError(f"ready26 active graph differs: {len(edges)} edges, {guarded} guarded")
    return edges, guarded


def production_snapshot() -> dict[str, str]:
    return {name: sha(ROOT / name) for name in PRODUCTION_FILES}


def freeze_or_verify_inputs(edges: list[dict]) -> dict:
    receipt = json.loads(FROZEN_RECEIPT.read_text())
    if (receipt.get("status") != "MATCH" or receipt.get("graph", {}).get("physical") != 858
            or not receipt.get("image", {}).get("retail_exact")):
        raise RuntimeError("ready26 source receipt is not a completed retail gate")
    pins = {
        "ready26_receipt_sha256": sha(FROZEN_RECEIPT),
        "generic_cli_sha256": sha(GENERIC),
        "generic_package_sha256": sha(GENERIC_PACKAGE),
        "probe_sha256": sha(Path(__file__)),
        "ready26_stage_files": {name: sha(FROZEN / name) for name in (
            "build.ninja", "config/slus_modules.json", "config/slus_partitions.json",
            "tools/cc.sh", "tools/ccproc.py", "tools/slus_data_pieces.py",
            IMAGE, "build/slus_006.14.elf")},
        "ready26_active_objects": {e["out"]: sha(FROZEN / e["out"]) for e in edges},
        "production_files": production_snapshot(),
    }
    if pins["ready26_stage_files"][IMAGE] != receipt["image"]["sha256"]:
        raise RuntimeError("frozen ready26 stage image differs from its receipt")
    if PINS.exists():
        if json.loads(PINS.read_text()) != pins:
            raise RuntimeError("frozen baseline pins differ from current inputs")
    else:
        PINS.write_text(json.dumps(pins, indent=2, sort_keys=True) + "\n")
    return pins


def safe_stage_output(relative: str) -> Path:
    target = STAGE / relative
    if not target.parent.resolve().is_relative_to(STAGE.resolve()):
        raise RuntimeError("output path escapes cloned stage: " + relative)
    if target.is_symlink() or not target.is_file():
        raise RuntimeError("expected private regular output: " + relative)
    return target


def clone_and_invalidate(edges: list[dict]) -> None:
    if STAGE.is_symlink():
        raise RuntimeError("refusing symlink trial stage")
    if STAGE.exists():
        shutil.rmtree(STAGE)
    shutil.copytree(FROZEN, STAGE, symlinks=True)
    if sha(STAGE / "build.ninja") != sha(FROZEN / "build.ninja"):
        raise RuntimeError("cloned Ninja graph differs from frozen ready26")
    for edge in edges:
        safe_stage_output(edge["out"]).unlink()
    if any((STAGE / e["out"]).exists() for e in edges):
        raise RuntimeError("one or more active outputs survived invalidation")


def generic_env() -> dict[str, str]:
    env = os.environ.copy()
    env.pop("AZURE_MASPSX", None)
    env["AZURE_MASPSX_COMPANION"] = str(GENERIC)
    return env


def ninja(targets: list[str], log_name: str, keep_going: bool) -> int:
    command = ["ninja", "-C", str(STAGE), "-j", "4"]
    if keep_going:
        command += ["-k", "0"]
    command += targets
    log = HERE / log_name
    with log.open("w") as handle:
        result = subprocess.run(command, cwd=ROOT, env=generic_env(),
                                stdout=handle, stderr=subprocess.STDOUT, text=True)
    return result.returncode


def alloc_data(obj) -> dict[str, bytes]:
    return {section: payload for section, payload in obj.sections.items()
            if not section.startswith(".text")}


def canonical_relocations(view: A.View) -> list[tuple]:
    result = []
    for section, offset, rtype, target, addend in view.obj.relocs:
        result.append((section, offset, rtype, view.canon(target, addend)))
    return sorted(result, key=repr)


def function_difference(old: A.View, new: A.View, name: str) -> dict | None:
    if name not in old.funcs:
        return {"function": name, "kind": "added", "new_words": len(new.tokens(name))}
    if name not in new.funcs:
        return {"function": name, "kind": "removed", "old_words": len(old.tokens(name))}
    before, after = old.tokens(name), new.tokens(name)
    if before == after:
        return None
    result = {"function": name, "kind": "token_change", "old_words": len(before),
              "new_words": len(after)}
    if len(before) == len(after):
        sites = [i for i, (a, b) in enumerate(zip(before, after)) if a != b]
        result.update({"equal_length_mismatch_count": len(sites),
                       "equal_length_mismatch_sites": sites[:32]})
    else:
        diagnostic = A.compare_units(old, new, [name])
        aligned = SequenceMatcher(None, before, after, autojunk=False).get_opcodes()
        result["unequal_length_alignment"] = {
            "method": "SequenceMatcher over canonical aspsx_diff tokens; descriptive, not gate distance",
            "a_compare_units_diff_diagnostic": diagnostic["diff"],
            "regions": [{"tag": tag, "old": [a1, a2], "new": [b1, b2]}
                        for tag, a1, a2, b1, b2 in aligned if tag != "equal"][:32],
        }
    result["old_first_tokens"] = [repr(x) for x in before[:4]]
    result["new_first_tokens"] = [repr(x) for x in after[:4]]
    return result


def object_comparison(edge: dict) -> dict:
    relative = edge["out"]
    before_path, after_path = FROZEN / relative, STAGE / relative
    before_bytes, after_bytes = before_path.read_bytes(), after_path.read_bytes()
    old_obj, new_obj = read_elf(before_bytes), read_elf(after_bytes)
    old, new = A.View(old_obj), A.View(new_obj)
    names = sorted(set(old.funcs) | set(new.funcs))
    function_changes = [change for name in names
                        if (change := function_difference(old, new, name)) is not None]
    old_data, new_data = alloc_data(old_obj), alloc_data(new_obj)
    data_sections = sorted(set(old_data) | set(new_data))
    data_changes = [{"section": section, "old_bytes": len(old_data.get(section, b"")),
                     "new_bytes": len(new_data.get(section, b"")),
                     "old_sha256": digest(old_data.get(section, b"")),
                     "new_sha256": digest(new_data.get(section, b""))}
                    for section in data_sections if old_data.get(section) != new_data.get(section)]
    old_rel, new_rel = canonical_relocations(old), canonical_relocations(new)
    removed_rel = list((Counter(map(repr, old_rel)) - Counter(map(repr, new_rel))).elements())
    added_rel = list((Counter(map(repr, new_rel)) - Counter(map(repr, old_rel))).elements())
    old_text = {name: body for name, body in old_obj.sections.items() if name.startswith(".text")}
    new_text = {name: body for name, body in new_obj.sections.items() if name.startswith(".text")}
    changed_text_sections = [name for name in sorted(set(old_text) | set(new_text))
                             if old_text.get(name) != new_text.get(name)]
    return {"out": relative, "src": edge["src"], "recipe": {key: edge[key]
            for key in ("ccver", "ccflags", "asflags")},
            "old_object_sha256": digest(before_bytes), "new_object_sha256": digest(after_bytes),
            "object_bytes_changed": before_bytes != after_bytes,
            "old_function_count": len(old.funcs), "new_function_count": len(new.funcs),
            "function_changes": function_changes, "data_changes": data_changes,
            "canonical_relocation_changes": {"removed_count": len(removed_rel),
                                             "added_count": len(added_rel),
                                             "removed_examples": removed_rel[:16],
                                             "added_examples": added_rel[:16]},
            "changed_raw_text_sections": changed_text_sections,
            "unknown_relocations": {"old": old_obj.unknown, "new": new_obj.unknown}}


def data_piece_proofs(edges: list[dict]) -> list[dict]:
    modules = load_manifest(STAGE / "config/slus_modules.json")
    by_output = {f"build/{Path(m['source']).with_suffix('.o')}": m
                 for m in modules if m.get("data_pieces")}
    results = []
    for edge in edges:
        module = by_output.get(edge["out"])
        if module is None:
            continue
        path = STAGE / edge["out"]
        try:
            receipt = verify_data_pieces(path, module)
            results.append({"out": edge["out"], "module": module["name"], "valid": True,
                            "receipt_sha256": sha(path.with_suffix(".data-pieces.json")),
                            "unsplit_sha256": sha(path.with_suffix(".unsplit.o")),
                            "pieces": len(module["data_pieces"])})
        except Exception as exc:
            results.append({"out": edge["out"], "module": module["name"],
                            "valid": False, "error": str(exc)})
    return results


def image_gate() -> dict:
    for name in ("build/slus_006.14.ok", IMAGE, "build/slus_006.14.elf"):
        path = STAGE / name
        if path.exists():
            if path.is_symlink() or not path.is_file():
                raise RuntimeError("unsafe derived gate output: " + name)
            path.unlink()
    code = ninja(["build/slus_006.14.ok"], "full_image_gate.log", keep_going=False)
    log = (HERE / "full_image_gate.log").read_text()
    image = STAGE / IMAGE
    retail = ROOT / "baserom/slus_006.14"
    result = {"exit_code": code, "gate_log_sha256": digest(log.encode()),
              "gate_log_tail": log.splitlines()[-30:],
              "new_image_exists": image.is_file(),
              "new_elf_exists": (STAGE / "build/slus_006.14.elf").is_file(),
              "sha1_stamp_exists": (STAGE / "build/slus_006.14.ok").is_file()}
    if image.is_file():
        result.update({"image_sha256": sha(image),
                       "retail_exact": image.read_bytes() == retail.read_bytes()})
    else:
        result["retail_exact"] = False
    return result


def main() -> dict:
    edges, guarded = physical_edges(FROZEN)
    pins = freeze_or_verify_inputs(edges)
    clone_and_invalidate(edges)
    build_code = ninja([edge["out"] for edge in edges], "all_objects_build.log", keep_going=True)
    objects = []
    missing = []
    errors = []
    for edge in edges:
        path = STAGE / edge["out"]
        if not path.is_file():
            missing.append(edge["out"])
            continue
        try:
            objects.append(object_comparison(edge))
        except Exception as exc:
            errors.append({"out": edge["out"], "error": str(exc)})
    pieces = data_piece_proofs(edges)
    gate = image_gate()
    # The frozen source and production input check runs after every trial mutation.
    freeze_or_verify_inputs(edges)
    changed_functions = [{"out": obj["out"], **item}
                         for obj in objects for item in obj["function_changes"]]
    semantic_changes = [obj["out"] for obj in objects
                        if obj["function_changes"] or obj["data_changes"]
                        or obj["canonical_relocation_changes"]["removed_count"]
                        or obj["canonical_relocation_changes"]["added_count"]]
    raw_only = [obj["out"] for obj in objects
                if obj["object_bytes_changed"] and obj["out"] not in semantic_changes]
    summary = {"active_physical_tus": len(edges), "previously_guarded_tus": guarded,
               "object_build_exit_code": build_code, "rebuilt_objects": len(objects),
               "missing_outputs": missing, "comparison_errors": errors,
               "raw_object_bytes_changed": sum(o["object_bytes_changed"] for o in objects),
               "semantic_changed_objects": len(semantic_changes),
               "changed_function_count": len(changed_functions),
               "function_set_changed_objects": sum(
                   any(f["kind"] != "token_change" for f in o["function_changes"]) for o in objects),
               "data_payload_changed_objects": sum(bool(o["data_changes"]) for o in objects),
               "canonical_relocation_changed_objects": sum(bool(
                   o["canonical_relocation_changes"]["removed_count"] or
                   o["canonical_relocation_changes"]["added_count"]) for o in objects),
               "raw_only_object_hash_changes": len(raw_only),
               "data_piece_modules_checked": len(pieces),
               "data_piece_modules_valid": sum(p["valid"] for p in pieces)}
    result = {"status": "MEASURED", "scope": "all 858 active ready26 physical SLUS C TUs",
              "pins_sha256": sha(PINS), "pins": pins,
              "stage": str(STAGE.relative_to(ROOT)), "summary": summary,
              "changed_outputs": semantic_changes,
              "changed_functions": changed_functions,
              "raw_only_hash_changed_outputs": raw_only,
              "all_object_comparisons": objects,
              "data_piece_proofs": pieces, "full_image_gate": gate,
              "all_objects_build_log_sha256": sha(HERE / "all_objects_build.log"),
              "production_and_frozen_inputs_unchanged": True,
              "classification_limits": (
                  "Function equality uses aspsx_diff canonical tokens. Unequal-length alignment "
                  "is a descriptive SequenceMatcher diagnostic, not the gate's canonical score. "
                  "Raw ELF hash-only changes do not count as instruction/data changes.")}
    RECEIPT.write_text(json.dumps(result, indent=2, sort_keys=True) + "\n")
    return result


if __name__ == "__main__":
    try:
        value = main()
        print(json.dumps({"status": value["status"], "summary": value["summary"],
                          "full_image_gate": value["full_image_gate"]}, indent=2))
    except Exception as exc:
        RECEIPT.write_text(json.dumps({"status": "ERROR", "error": str(exc),
                                       "traceback": traceback.format_exc()}, indent=2) + "\n")
        raise
