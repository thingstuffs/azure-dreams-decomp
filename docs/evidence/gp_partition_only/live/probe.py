#!/usr/bin/env python3
"""Run the real two-owner ownership proof in a detached ready29 repository."""

from __future__ import annotations

import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import sys
import time


HERE = Path(__file__).resolve().parent
REPO = HERE.parents[2]
STAGE_DIR = REPO / "work/native_lane/gp_ready29_collectors"
STAGE = STAGE_DIR / "stage"
READY_RECEIPT = STAGE_DIR / "receipt.json"
PINS = HERE / "tool_pins.json"
CANDIDATE = HERE / "candidate"
GENERIC = REPO / "work/native_lane/selfinc_local_guard/candidate"
FIXTURE = HERE / "live_fixture"
NAMES = ("accessors_814c8", "table_counters_b1b_b1c")
GENERIC_HASHES = {
    "maspsx.py": "d3e6ec7d120abe00f963c82258dfdeb0e228774adce646177525f1dbed925caf",
    "maspsx/__init__.py": "28e45bbcf00fc90dc0645250f233b73f96ad11d06a2f8230ce533fc2fafbbfbe",
}
PRODUCTION_FILES = (
    "config/slus_modules.json", "config/slus_partitions.json", "config/names.tsv",
    "build_slus/build.ninja", "build_slus/build/slus_006.14",
    "src/slus/code.c", "src/slus/code2.c",
    "tools/build/configure.py", "tools/build/slus_modules.py",
    "tools/build/slus_partitions.py", "tools/row_db.py",
    "tools/slus_module_context.py", "tools/slus_module_evidence.py",
    "tools/fidelity/prove_slus_ownership.py",
    "tools/fidelity/certify_slus_module.py", "tools/fidelity/slus_iso.py",
    "tools/fidelity/aspsx_diff.py", "tools/verify.py",
    "tools/maspsx/maspsx.py", "tools/maspsx/maspsx/__init__.py",
)


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def install(source: Path, target: Path) -> None:
    target.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(source, target)
    if sha(source) != sha(target):
        raise RuntimeError("copy differs: " + str(target))


def relative_link(path: Path, target: Path) -> None:
    if path.exists() or path.is_symlink():
        if not path.is_symlink():
            raise RuntimeError("expected replaceable symlink: " + str(path))
        path.unlink()
    path.symlink_to(target, target_is_directory=True)
    if path.resolve() != target.resolve():
        raise RuntimeError("private link differs: " + str(path))


def snapshot_edges(ninja_text: str) -> list[dict]:
    """Parse only the production object set before private imports exist."""
    edges, current = [], None
    for raw in ninja_text.splitlines():
        match = re.match(r"^build (\S+): cc (\S+)", raw)
        if match:
            current = {"out": match.group(1), "src": match.group(2),
                       "ccver": "2.7.2", "ccflags": "", "asflags": ""}
            edges.append(current)
            continue
        if current is not None:
            match = re.match(r"^\s+(ccver|ccflags|asflags) = ?(.*)$", raw)
            if match:
                current[match.group(1)] = match.group(2).strip()
            elif not raw.startswith(" ") and raw.strip():
                current = None
    return edges


def production_snapshot() -> dict:
    edges = snapshot_edges((REPO / "build_slus/build.ninja").read_text())
    return {
        "files": {name: sha(REPO / name) for name in PRODUCTION_FILES},
        "objects": {edge["out"]: sha(REPO / "build_slus" / edge["out"]) for edge in edges},
        "physical": len(edges),
    }


def source_pins() -> dict:
    ready = json.loads(READY_RECEIPT.read_text())
    if ready.get("status") != "MATCH" or ready.get("production_unchanged") is not True:
        raise RuntimeError("ready29 has no clean retail-gate receipt")
    if ready["graph"]["physical"] != 860 or ready["graph"]["logical"] != 884:
        raise RuntimeError("ready29 graph counts changed")
    pinned = json.loads(PINS.read_text())
    for name, expected in pinned.items():
        if sha(CANDIDATE / name) != expected:
            raise RuntimeError("candidate tool differs from frozen pin: " + name)
    for name, expected in GENERIC_HASHES.items():
        if sha(GENERIC / name) != expected:
            raise RuntimeError("guarded generic differs from frozen pin: " + name)
    stage_files = (
        "build.ninja", "config/slus_modules.json", "config/slus_partitions.json",
        "config/names.tsv", "src/code.c", "src/code2.c",
        "src/c8_accessors_owned.c", "src/b1b_b1c_table_owned.c",
        "build/slus_006.14", "build/slus_006.14.elf",
    )
    edge_outputs = [e["out"] for e in snapshot_edges((STAGE / "build.ninja").read_text())]
    if len(edge_outputs) != 860 or len(set(edge_outputs)) != 860:
        raise RuntimeError("stage physical output set changed")
    return {
        "ready_receipt": sha(READY_RECEIPT),
        "ready_pins": sha(STAGE_DIR / "input_pins.json"),
        "stage_files": {name: sha(STAGE / name) for name in stage_files},
        "stage_objects": {name: sha(STAGE / name) for name in edge_outputs},
        "candidate_tools": pinned,
        "guarded_generic": GENERIC_HASHES,
    }


def prepare() -> None:
    if FIXTURE.exists():
        raise RuntimeError("private fixture already exists; refusing to overwrite")
    pins = source_pins()
    before = production_snapshot()
    if before["physical"] != 869:
        raise RuntimeError("production physical count changed")
    FIXTURE.mkdir()
    (FIXTURE / ".ignore").write_text("*\n")
    (FIXTURE / "production_before.json").write_text(json.dumps(before, indent=2) + "\n")
    (FIXTURE / "source_pins.json").write_text(json.dumps(pins, indent=2) + "\n")

    ignored = shutil.ignore_patterns("__pycache__", "*.pyc")
    shutil.copytree(REPO / "tools", FIXTURE / "tools", ignore=ignored)
    for name, expected in pins["candidate_tools"].items():
        install(CANDIDATE / name, FIXTURE / name)
        if sha(FIXTURE / name) != expected:
            raise RuntimeError("candidate overlay differs: " + name)
    for name, expected in GENERIC_HASHES.items():
        install(GENERIC / name, FIXTURE / "tools/maspsx" / name)
        if sha(FIXTURE / "tools/maspsx" / name) != expected:
            raise RuntimeError("generic tools copy differs: " + name)

    shutil.copytree(STAGE, FIXTURE / "build_slus", symlinks=True, ignore=ignored)
    shutil.copytree(STAGE / "src", FIXTURE / "src/slus", ignore=ignored)
    shutil.copytree(STAGE / "config", FIXTURE / "config", ignore=ignored)
    shutil.copytree(STAGE / "include", FIXTURE / "include", ignore=ignored)
    shutil.copytree(REPO / "raw/slus", FIXTURE / "raw/slus", ignore=ignored)
    shutil.copytree(REPO / "raw/include", FIXTURE / "raw/include", ignore=ignored)
    install(REPO / "PIN", FIXTURE / "PIN")
    for name in ("noreturn_syms", "sibcall_syms"):
        for path in sorted((REPO / "config").glob(name + "*.txt")):
            install(path, FIXTURE / "config" / path.name)
    overlays = REPO / "config/overlays"
    for path in sorted(overlays.glob("*.as_flags.jsonl")):
        install(path, FIXTURE / "config/overlays" / path.name)
    shutil.copytree(REPO / "ledger/cache/slus_dis", FIXTURE / "ledger/cache/slus_dis",
                    ignore=ignored)
    install(REPO / "ledger/cache/slus_obj.json", FIXTURE / "ledger/cache/slus_obj.json")
    install(REPO / "ledger/rows.jsonl", FIXTURE / "ledger/rows.jsonl")
    install(STAGE / "build.ninja", FIXTURE / "ledger/splits/slus.build.ninja")
    for name in (
        "tools/match.py", "tools/overlay_as_flags.py", "tools/overlay_evidence.py",
        "tools/rowbase.py", "work/g3/overlay_func_compare.py", "config/names.tsv",
    ):
        install(REPO / "build_ovl" / name, FIXTURE / "build_ovl" / name)

    (FIXTURE / "toolchain").mkdir()
    (FIXTURE / "toolchain/compilers").symlink_to(REPO / "toolchain/compilers",
                                                 target_is_directory=True)
    (FIXTURE / "toolchain/genuine").symlink_to(REPO / "toolchain/genuine",
                                               target_is_directory=True)
    for name in GENERIC_HASHES:
        install(GENERIC / name, FIXTURE / "toolchain/maspsx" / name)
    (FIXTURE / ".venv").symlink_to(REPO / ".venv", target_is_directory=True)
    (FIXTURE / "baserom").symlink_to(REPO / "baserom", target_is_directory=True)
    relative_link(FIXTURE / "build_slus/toolchain", FIXTURE / "toolchain")
    relative_link(FIXTURE / "build_slus/raw/slus", FIXTURE / "raw/slus")
    relative_link(FIXTURE / "build_slus/baserom", FIXTURE / "baserom")
    relative_link(FIXTURE / "build_slus/.venv", FIXTURE / ".venv")

    # Load the private build-side implementation to derive the authoritative
    # logical ledger. No row is synthesized or discarded.
    sys.path[:0] = [str(FIXTURE / "tools"), str(FIXTURE / "tools/build")]
    from row_db import edges_of
    from slus_modules import load_manifest, logical_edges
    from slus_partitions import load_plan, project_edges, read_aliases, validate_context
    modules = load_manifest(FIXTURE / "config/slus_modules.json")
    plan = load_plan(FIXTURE / "config/slus_partitions.json")
    physical = edges_of((FIXTURE / "build_slus/build.ninja").read_text())
    if physical != snapshot_edges((FIXTURE / "build_slus/build.ninja").read_text()):
        raise RuntimeError("private candidate row parser differs from snapshot")
    logical = logical_edges(project_edges(physical, plan), modules)
    if len(physical) != 860 or len(logical) != 884:
        raise RuntimeError("private edge projection changed")
    aliases = read_aliases(FIXTURE / "config/names.tsv")
    validate_context(plan, modules, logical, FIXTURE / "raw/slus", aliases)
    (FIXTURE / "ledger/splits/slus.jsonl").write_text(
        "".join(json.dumps(edge, sort_keys=True) + "\n" for edge in logical))
    if (FIXTURE / "ledger/splits/slus.build.ninja").read_bytes() != (
            FIXTURE / "build_slus/build.ninja").read_bytes():
        raise RuntimeError("private pinned recipe differs")
    for name in pins["stage_files"]:
        if sha(FIXTURE / "build_slus" / name) != pins["stage_files"][name]:
            raise RuntimeError("ready29 stage copy differs: " + name)
    for name, expected in pins["stage_objects"].items():
        if sha(FIXTURE / "build_slus" / name) != expected:
            raise RuntimeError("ready29 object copy differs: " + name)
    for name in pins["candidate_tools"]:
        if not (FIXTURE / name).is_file() or (FIXTURE / name).is_symlink():
            raise RuntimeError("candidate tool is not a private regular file: " + name)
    for name in GENERIC_HASHES:
        if sha(FIXTURE / "tools/maspsx" / name) != GENERIC_HASHES[name]:
            raise RuntimeError("private tools assembler differs")
        if sha(FIXTURE / "toolchain/maspsx" / name) != GENERIC_HASHES[name]:
            raise RuntimeError("private build assembler differs")
    if sha(FIXTURE / "src/slus/code.c") != sha(FIXTURE / "build_slus/src/code.c"):
        raise RuntimeError("private code source differs")
    if sha(FIXTURE / "src/slus/code2.c") != sha(FIXTURE / "build_slus/src/code2.c"):
        raise RuntimeError("private code2 source differs")
    after = production_snapshot()
    (FIXTURE / "production_after_prepare.json").write_text(json.dumps(after, indent=2) + "\n")
    if before != after:
        raise RuntimeError("production changed during private fixture preparation")
    report = {
        "schema": 1, "result": "PREPARED",
        "ready29_receipt_sha256": pins["ready_receipt"],
        "stage_graph": {"physical": len(physical), "logical": len(logical)},
        "module_count": len(modules), "partition_parents": len(plan),
        "candidate_tool_hashes": pins["candidate_tools"],
        "generic_hashes": GENERIC_HASHES,
        "production_unchanged": True,
    }
    (FIXTURE / "prepare_receipt.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))


def prove() -> None:
    if not (FIXTURE / "prepare_receipt.json").exists():
        raise RuntimeError("private fixture has not passed preparation")
    pins = json.loads((FIXTURE / "source_pins.json").read_text())
    if source_pins() != pins:
        raise RuntimeError("source pins changed before live proof")
    before = production_snapshot()
    if before != json.loads((FIXTURE / "production_before.json").read_text()):
        raise RuntimeError("production changed since private fixture preparation")
    if (FIXTURE / "ledger/splits/slus.build.ninja").read_bytes() != (
            FIXTURE / "build_slus/build.ninja").read_bytes():
        raise RuntimeError("private pinned graph drift")
    os.environ.pop("AZURE_MASPSX", None)
    os.environ.pop("AZURE_MASPSX_COMPANION", None)
    os.environ.pop("PYTHONPATH", None)
    os.chdir(FIXTURE)
    sys.path[:0] = [str(FIXTURE / "tools"), str(FIXTURE / "tools/build"),
                    str(FIXTURE / "tools/fidelity")]
    from common import ROOT as private_root
    from fidelity import aspsx_diff as A
    from fidelity import prove_slus_ownership as O
    import verify
    from slus_module_context import modules
    if private_root != FIXTURE or A.ROOT != FIXTURE or O.ROOT != FIXTURE:
        raise RuntimeError("proof imported a non-private root")
    if Path(A.__file__).resolve() != FIXTURE / "tools/fidelity/aspsx_diff.py":
        raise RuntimeError("proof imported non-private ASPSX comparator")
    if Path(verify.__file__).resolve() != FIXTURE / "tools/verify.py":
        raise RuntimeError("proof imported non-private verifier")
    if not set(NAMES).issubset({m["name"] for m in modules()}):
        raise RuntimeError("selected owners absent from private manifest")
    scratch = Path("/tmp") / ("po29_aspsx_" + str(os.getpid()))
    if scratch.exists():
        raise RuntimeError("ASPSX scratch collides")
    scratch.mkdir()
    A.TMP = scratch
    A._SLUS = None
    started = time.time()
    try:
        receipt = O.prove(list(NAMES))
    except Exception as exc:
        failure = {
            "schema": 1, "result": "ERROR",
            "exception_type": type(exc).__name__, "exception": str(exc),
            "scratch": str(scratch),
            "ready29_receipt_sha256": pins["ready_receipt"],
            "candidate_tool_hashes": pins["candidate_tools"],
            "guarded_generic_hashes": GENERIC_HASHES,
        }
        (FIXTURE / "failure_receipt.json").write_text(json.dumps(failure, indent=2) + "\n")
        (FIXTURE / "production_after_failure.json").write_text(
            json.dumps(production_snapshot(), indent=2) + "\n")
        raise
    else:
        shutil.rmtree(scratch)
    if receipt.get("schema") != 5 or receipt.get("modules") != list(NAMES):
        raise RuntimeError("live proof receipt has wrong selected owner scope")
    if receipt.get("gate", {}).get("result") != "MATCH":
        raise RuntimeError("live proof lacks retail gate")
    if set(receipt.get("rows", {})) != {"slus/code", "slus/code2"}:
        raise RuntimeError("live proof lacks real contributor records")
    for row in receipt["rows"].values():
        if row.get("status") != "ok" or not row.get("physical_units"):
            raise RuntimeError("contributor row lacks real physical measurements")
    (FIXTURE / "ownership_receipt.json").write_text(json.dumps(receipt, indent=2) + "\n")
    after = production_snapshot()
    (FIXTURE / "production_after_prove.json").write_text(json.dumps(after, indent=2) + "\n")
    if before != after:
        raise RuntimeError("production changed during private ownership proof")
    if source_pins() != pins:
        raise RuntimeError("source pins changed during live proof")
    for name, expected in pins["stage_files"].items():
        if sha(FIXTURE / "build_slus" / name) != expected:
            raise RuntimeError("private stage file changed during proof: " + name)
    for name, expected in pins["stage_objects"].items():
        if sha(FIXTURE / "build_slus" / name) != expected:
            raise RuntimeError("private staged object changed during proof: " + name)
    for name, expected in pins["candidate_tools"].items():
        if sha(FIXTURE / name) != expected:
            raise RuntimeError("private candidate tool changed during proof: " + name)
    for name, expected in GENERIC_HASHES.items():
        if sha(FIXTURE / "tools/maspsx" / name) != expected:
            raise RuntimeError("private verifier assembler changed during proof: " + name)
        if sha(FIXTURE / "toolchain/maspsx" / name) != expected:
            raise RuntimeError("private build assembler changed during proof: " + name)
    physical = receipt["physical_modules"]
    owners = {}
    for module in NAMES:
        descriptor = physical[module]
        owner_source = next(m["source"] for m in modules() if m["name"] == module)
        measurements = [unit for row in receipt["rows"].values()
                        for unit in row["physical_units"] if unit["source"] == owner_source]
        if len(measurements) != 1:
            raise RuntimeError("selected owner lacks unique physical measurement: " + module)
        unit = measurements[0]
        direct = unit["genuine"]["2.79"]["physical"]
        owners[module] = {
            "source": owner_source,
            "functions": descriptor["functions"],
            "words": direct["len_m"],
            "pipeline_retail": unit["maspsx_physical_retail"],
            "genuine": direct,
            "data_sections": list(receipt["data"][module]["sections"]),
        }
    summary = {
        "schema": 1, "result": "PASS", "duration_seconds": round(time.time() - started, 1),
        "selected_modules": list(NAMES), "collector_rows": sorted(receipt["rows"]),
        "ownership_schema": receipt["schema"], "retail_gate": receipt["gate"],
        "image_sha1": receipt["image_sha1"],
        "owners": owners,
        "collector_remainder_genuine_claimed": False,
        "receipt_sha256": sha(FIXTURE / "ownership_receipt.json"),
        "production_unchanged": True,
        "candidate_tool_hashes": pins["candidate_tools"],
        "guarded_generic_hashes": GENERIC_HASHES,
    }
    (FIXTURE / "live_probe_receipt.json").write_text(json.dumps(summary, indent=2) + "\n")
    print(json.dumps(summary, indent=2))


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("action", choices=("prepare", "prove"))
    args = parser.parse_args()
    if args.action == "prepare":
        prepare()
    else:
        prove()


if __name__ == "__main__":
    main()
