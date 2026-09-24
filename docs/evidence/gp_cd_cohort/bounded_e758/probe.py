#!/usr/bin/env python3
"""Generated-build proof for bounded-view E758 under one generic owner edge."""

from __future__ import annotations

import hashlib
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
RECEIPT = HERE / "receipt.json"
CANDIDATE = ROOT / "docs/evidence/gp_cd_contract/next_probes/e758_owned_bounded_views.c"
MODULE_PLAN = ROOT / "docs/evidence/gp_data_pieces/candidate_module.json"
GENERIC = ROOT / "work/native_lane/selfinc_local_guard/candidate/maspsx.py"
IMAGE = "build/slus_006.14"
OLD_OBJECT = "build/src/w_8003E758.o"
OWNER_OBJECT = "build/src/w_8003E758_owned.o"
FRAGMENT = "src/w_8003E758.c"
AGGREGATOR = "src/w_8003E758_owned.c"

sys.path[:0] = [str(ROOT / "tools"), str(ROOT / "tools/build"), str(ROOT / "tools/fidelity")]
from fidelity.slus_iso import SlusView  # noqa: E402
from fidelity.objread import read_elf  # noqa: E402
from row_db import edges_of  # noqa: E402
from slus_modules import load_manifest, logical_edges, plan_asset_carves  # noqa: E402
from slus_data_pieces import verify_data_pieces  # noqa: E402
import slus_partitions as partitions  # noqa: E402


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def file_hash(path: Path) -> str:
    return digest(path.read_bytes())


def run(*args: str, env=None) -> str:
    actual = dict(os.environ) if env is None else env
    if env is None:
        actual.pop("AZURE_MASPSX", None)
        actual.pop("AZURE_MASPSX_COMPANION", None)
    result = subprocess.run(args, cwd=STAGE, env=actual, capture_output=True, text=True)
    output = result.stdout + result.stderr
    if result.returncode:
        raise RuntimeError(f"{' '.join(args)} failed ({result.returncode}): {output[-5000:]}")
    return output


def production_snapshot() -> dict[str, str]:
    paths = (
        "config/slus_modules.json", "config/slus_partitions.json",
        "src/slus/w_8003E758.c", "include/slus/cd_state.h",
        "tools/build/configure.py", "tools/build/slus_modules.py",
        "tools/build/slus_data_pieces.py", "tools/fidelity/slus_iso.py",
        "build_slus/build.ninja", "build_slus/build/slus_006.14",
        "baserom/slus_006.14",
    )
    return {path: file_hash(ROOT / path) for path in paths}


def private_write(relative: str, content: bytes | str) -> None:
    target = STAGE / relative
    if not target.parent.resolve().is_relative_to(STAGE.resolve()):
        raise RuntimeError("staged source parent escapes trial root: " + relative)
    if target.is_dir():
        raise RuntimeError("staged source path is a directory: " + relative)
    if target.is_symlink() or target.exists():
        target.unlink()
    target.write_bytes(content if isinstance(content, bytes) else content.encode())


def candidate_sources() -> tuple[str, str, bytes]:
    original = CANDIDATE.read_bytes()
    text = original.decode()
    lines = text.splitlines(keepends=True)
    definitions = lines[1:9]
    symbols = ("D_800814D0", "D_800814D4", "D_800814CC", "D_80081450",
               "D_80080AD0", "D_80080AD2", "D_80080AD4", "D_80080AD8")
    if lines[0] != '#include "slus/cd_state.h"\n' or len(definitions) != len(symbols):
        raise RuntimeError("bounded source does not have the expected eight definitions")
    for line, symbol in zip(definitions, symbols):
        if not re.search(r"\b" + symbol + r"\s*=\s*(?:0|\{0\});", line):
            raise RuntimeError("bounded definition changed: " + symbol)
    fragment = lines[0] + "".join(lines[9:])
    aggregator = ('#include "slus/cd_state.h"\n' + "".join(definitions)
                  + '\n#include "w_8003E758.c"\n')
    func = "void func_8003E758(void)"
    if func not in fragment or fragment[fragment.index(func):] != text[text.index(func):]:
        raise RuntimeError("bounded function body changed while moving definitions")
    return fragment, aggregator, original


def function_words(path: Path) -> tuple[int, str]:
    obj = read_elf(path.read_bytes())
    name = ".text.func_8003E758"
    body = obj.sections.get(name)
    sym = obj.symbols.get("func_8003E758")
    if body is None or sym is None or sym[0] != name or sym[2] != "func":
        raise RuntimeError("E758 function section/symbol absent from owner object")
    return len(body) // 4, digest(body)


def linked_data_symbols(module: dict) -> list[dict]:
    result = subprocess.run(("mipsel-linux-gnu-readelf", "-Ws", str(STAGE / "build/slus_006.14.elf")),
                            capture_output=True, text=True, check=True)
    by_name: dict[str, list[tuple[int, str, str]]] = {}
    for line in result.stdout.splitlines():
        fields = line.split()
        if len(fields) < 8 or not fields[0].rstrip(":").isdigit():
            continue
        try:
            address = int(fields[1], 16)
        except ValueError:
            continue
        by_name.setdefault(fields[-1], []).append((address, fields[4], fields[6]))
    image = (STAGE / IMAGE).read_bytes()
    load_address = int.from_bytes(image[0x18:0x1C], "little")
    proved = []
    for datum in module["data"]:
        name = datum["symbol"]
        entries = by_name.get(name, [])
        if len(entries) != 1:
            raise RuntimeError(f"{name}: expected one linked symbol, found {entries}")
        address, bind, section = entries[0]
        if address != datum["vram"] or bind != "GLOBAL" or not section.isdigit():
            raise RuntimeError(f"{name}: wrong VMA/binding/section {entries[0]}")
        image_offset = 0x800 + address - load_address
        expected = bytes.fromhex(datum["bytes"])
        if image[image_offset:image_offset + datum["size"]] != expected:
            raise RuntimeError(f"{name}: linked initializer differs")
        proved.append({"symbol": name, "vram": f"0x{address:08X}",
                       "size": datum["size"], "section_index": int(section)})
    return proved


def main() -> None:
    head = subprocess.check_output(("git", "rev-parse", "--short", "HEAD"), cwd=ROOT, text=True).strip()
    if head != "89b14658":
        raise RuntimeError("production baseline changed: " + head)
    if not GENERIC.is_file():
        raise RuntimeError("generic assembler candidate absent")
    before = production_snapshot()
    retail = (ROOT / "baserom/slus_006.14").read_bytes()
    if (ROOT / "build_slus" / IMAGE).read_bytes() != retail:
        raise RuntimeError("production SLUS image is not retail exact")
    baseline_edges = edges_of((ROOT / "build_slus/build.ninja").read_text())
    if len(baseline_edges) != 869 or sum(e["out"] == OLD_OBJECT for e in baseline_edges) != 1:
        raise RuntimeError("current physical baseline is not 869 edges with one E758 object")
    if STAGE.is_symlink():
        raise RuntimeError("refusing symlink stage")
    if STAGE.exists():
        shutil.rmtree(STAGE)
    view = SlusView(STAGE)
    control = view.calibrate()
    if control != {"result": "MATCH", "words_diff": 0}:
        raise RuntimeError("private baseline failed calibration: " + str(control))
    outside = sorted(e["out"] for e in baseline_edges if e["out"] != OLD_OBJECT)
    if len(outside) != 868 or len(set(outside)) != 868:
        raise RuntimeError("outside object set is not 868 unique objects")
    outside_hashes = {path: file_hash(STAGE / path) for path in outside}
    fragment, aggregator, candidate_original = candidate_sources()
    private_write(FRAGMENT, fragment)
    if (STAGE / AGGREGATOR).exists():
        raise RuntimeError("owner aggregator already exists in stage")
    private_write(AGGREGATOR, aggregator)
    module = json.loads(MODULE_PLAN.read_text())
    module["headers"] = ["include/common.h", "include/slus/cd_state.h"]
    doc = json.loads((STAGE / "config/slus_modules.json").read_text())
    if len(doc["modules"]) != 23 or any(m["name"] == module["name"] for m in doc["modules"]):
        raise RuntimeError("private module baseline is not 23 owners")
    doc["modules"].append(module)
    private_write("config/slus_modules.json", json.dumps(doc, indent=2) + "\n")
    parsed = load_manifest(STAGE / "config/slus_modules.json")
    if len(parsed) != 24:
        raise RuntimeError("candidate manifest does not register 24 owners")
    owner_module = parsed[-1]
    carves = plan_asset_carves(parsed, STAGE)
    slots = [slot for plan in carves if plan["asset"] == "assets/54240.bin"
             for slot in plan["slots"] if slot["kind"] == "module_data"
             and slot["object"] == OWNER_OBJECT]
    if len(slots) != 8 or {s["symbols"][0] for s in slots} != {d["symbol"] for d in owner_module["data"]}:
        raise RuntimeError("candidate carve does not own exactly eight named slots")

    configure_log = run("python3", "tools/configure.py")
    graph = (STAGE / "build.ninja").read_text()
    physical = edges_of(graph)
    old_outputs = {e["out"] for e in baseline_edges}
    new_outputs = {e["out"] for e in physical}
    if (len(physical) != 869 or old_outputs - new_outputs != {OLD_OBJECT}
            or new_outputs - old_outputs != {OWNER_OBJECT}):
        raise RuntimeError("generated graph does not replace exactly one physical E758 edge")
    partition_plan = partitions.load_plan(STAGE / "config/slus_partitions.json")
    projected = partitions.project_edges(physical, partition_plan)
    logical = logical_edges(projected, parsed)
    ledger = [json.loads(line) for line in (ROOT / "ledger/splits/slus.jsonl").read_text().splitlines() if line]
    if len(logical) != 884 or logical != ledger:
        raise RuntimeError("projected logical recipes differ from the current 884-row ledger")
    view = SlusView(STAGE)
    if len(view.modules) != 24:
        raise RuntimeError("SlusView did not load private module")
    owner_path = STAGE / OWNER_OBJECT
    if owner_path.exists():
        owner_path.unlink()
    env = dict(os.environ)
    env.pop("AZURE_MASPSX", None)
    env.pop("AZURE_MASPSX_COMPANION", None)
    env["AZURE_MASPSX_COMPANION"] = str(GENERIC)
    rc, compile_log = view._ninja([OWNER_OBJECT], env=env)
    if rc or "CC src/w_8003E758_owned.c" not in compile_log:
        raise RuntimeError("generic owner compile failed: " + compile_log[-2500:])
    owner_before_link = file_hash(owner_path)
    word_count, function_sha = function_words(owner_path)
    if word_count != 698:
        raise RuntimeError(f"generic owner has {word_count} E758 words, expected 698")
    split_receipt = verify_data_pieces(owner_path, owner_module)
    rc, link_log = view._ninja([IMAGE])
    if rc:
        raise RuntimeError("generated Ninja link failed: " + link_log[-3000:])
    owner_after_link = file_hash(owner_path)
    if owner_after_link != owner_before_link or "CC src/w_8003E758_owned.c" in link_log:
        raise RuntimeError("link silently rebuilt the owner under stock assembler")
    image = (STAGE / IMAGE).read_bytes()
    if image != retail:
        first = next((i for i, (a, b) in enumerate(zip(image, retail)) if a != b), None)
        raise RuntimeError(f"private image differs from retail: first offset {first}")
    rc, gate_log = view._ninja(["build/slus_006.14.ok"])
    if rc or not (STAGE / "build/slus_006.14.ok").is_file():
        raise RuntimeError("generated SHA-1 target failed: " + gate_log[-2000:])
    if file_hash(owner_path) != owner_before_link:
        raise RuntimeError("generated SHA-1 target rebuilt the generic owner")
    after_split = verify_data_pieces(owner_path, owner_module)
    if after_split != split_receipt:
        raise RuntimeError("split receipt changed during link")
    changed = [path for path in outside if file_hash(STAGE / path) != outside_hashes[path]]
    if changed:
        raise RuntimeError(f"outside objects changed: {changed[:8]}")
    linked = linked_data_symbols(owner_module)
    if production_snapshot() != before:
        raise RuntimeError("production inputs changed during private trial")
    sidecars = {suffix: file_hash(STAGE / f"build/src/w_8003E758_owned{suffix}")
                for suffix in (".unsplit.o", ".data-pieces.json", ".data-pieces.ok")}
    record = {
        "status": "MATCH", "head": head, "stage": str(STAGE.relative_to(ROOT)),
        "control": control, "image_sha256": digest(image), "retail_sha256": digest(retail),
        "physical_edges": len(physical), "logical_edges": len(logical),
        "outside_objects_checked": len(outside), "outside_objects_changed": changed,
        "owner_object_sha256_before_link": owner_before_link,
        "owner_object_sha256_after_link": owner_after_link,
        "owner_unsplit_sha256": sidecars[".unsplit.o"],
        "sidecar_sha256": sidecars,
        "function_words": word_count, "function_section_sha256": function_sha,
        "linked_data": linked, "data_piece_receipt_sha256": sidecars[".data-pieces.json"],
        "source_sha256": {"candidate": digest(candidate_original), "fragment": digest(fragment.encode()),
                          "aggregator": digest(aggregator.encode()),
                          "cd_state_header": file_hash(ROOT / "include/slus/cd_state.h"),
                          "private_manifest": file_hash(STAGE / "config/slus_modules.json")},
        "tools_sha256": {"configure": file_hash(ROOT / "tools/build/configure.py"),
                         "slus_modules": file_hash(ROOT / "tools/build/slus_modules.py"),
                         "slus_data_pieces": file_hash(ROOT / "tools/build/slus_data_pieces.py"),
                         "slus_iso": file_hash(ROOT / "tools/fidelity/slus_iso.py"),
                         "stock_maspsx": file_hash(ROOT / "tools/maspsx/maspsx.py"),
                         "generic_maspsx": file_hash(GENERIC)},
        "production_inputs_unchanged": True,
        "configure_log_tail": configure_log[-500:], "compile_log_tail": compile_log[-1500:],
        "link_log_tail": link_log[-1800:], "sha1_gate_log_tail": gate_log[-600:],
    }
    RECEIPT.write_text(json.dumps(record, indent=2, sort_keys=True) + "\n")
    print("Bounded E758 private generated build: retail MATCH; owner generic 698 words", flush=True)


if __name__ == "__main__":
    try:
        main()
    except Exception as exc:
        RECEIPT.write_text(json.dumps({"status": "ERROR", "error": str(exc),
                                       "traceback": traceback.format_exc()}, indent=2) + "\n")
        raise
