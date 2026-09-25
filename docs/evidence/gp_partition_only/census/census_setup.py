#!/usr/bin/env python3
"""Clone the frozen live proof into a private complete-registry census root."""

from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import sys

from live_ownership_probe import production_snapshot, sha

HERE = Path(__file__).resolve().parent
REPO = HERE.parents[2]
LIVE = HERE / "live_fixture"
FIXTURE = HERE / "census_fixture"
RUNNER = HERE / "census_runner.py"
OVERLAYS = ("main", "town", "dungeon", "ovmovie")
SPLITS = OVERLAYS + ("dungeon_engine",)
GENERIC = REPO / "work/native_lane/selfinc_local_guard/candidate"
GFILES = ("maspsx.py", "maspsx/__init__.py")


def copy_file(source: Path, target: Path) -> None:
    target.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(source, target)
    if sha(source) != sha(target):
        raise RuntimeError("private copy differs: " + str(target))


def relink(path: Path, target: Path) -> None:
    if not path.is_symlink():
        raise RuntimeError("expected cloned private symlink: " + str(path))
    path.unlink()
    path.symlink_to(target, target_is_directory=True)
    if path.resolve() != target.resolve():
        raise RuntimeError("relinked target differs: " + str(path))


def tree_hashes(path: Path) -> dict:
    return {str(p.relative_to(path)): sha(p)
            for p in sorted(path.rglob("*")) if p.is_file() and not p.is_symlink()}


def overlay_pins() -> dict:
    files = {}
    for group in OVERLAYS:
        for kind in ("src", "raw"):
            root = REPO / kind / group
            files[kind + "/" + group] = tree_hashes(root)
    files["config/overlays"] = tree_hashes(REPO / "config/overlays")
    files["ledger/splits"] = {name: sha(REPO / "ledger/splits" / (name + ".jsonl"))
                               for name in SPLITS}
    files["config/func_sizes.json"] = sha(REPO / "config/func_sizes.json")
    return files


def fixture_overlay_pins() -> dict:
    files = {}
    for group in OVERLAYS:
        for kind in ("src", "raw"):
            files[kind + "/" + group] = tree_hashes(FIXTURE / kind / group)
    files["config/overlays"] = tree_hashes(FIXTURE / "config/overlays")
    files["ledger/splits"] = {name: sha(FIXTURE / "ledger/splits" / (name + ".jsonl"))
                               for name in SPLITS}
    files["config/func_sizes.json"] = sha(FIXTURE / "config/func_sizes.json")
    return files


def prepare() -> None:
    if FIXTURE.exists():
        raise RuntimeError("private census fixture already exists")
    live = json.loads((LIVE / "live_probe_receipt.json").read_text())
    if live.get("result") != "PASS" or live.get("ownership_schema") != 5:
        raise RuntimeError("frozen live ownership proof is unavailable")
    before = production_snapshot()
    if before["physical"] != 869:
        raise RuntimeError("production object count changed")
    sources = overlay_pins()
    shutil.copytree(LIVE, FIXTURE, symlinks=True,
                    ignore=shutil.ignore_patterns("__pycache__", "*.pyc"))
    (FIXTURE / ".ignore").write_text("*\n")
    (FIXTURE / "production_before_census.json").write_text(
        json.dumps(before, indent=2) + "\n")
    (FIXTURE / "overlay_source_pins.json").write_text(
        json.dumps(sources, indent=2) + "\n")
    for path, target in (
        ("build_slus/toolchain", FIXTURE / "toolchain"),
        ("build_slus/raw/slus", FIXTURE / "raw/slus"),
        ("build_slus/baserom", FIXTURE / "baserom"),
        ("build_slus/.venv", FIXTURE / ".venv"),
    ):
        relink(FIXTURE / path, target)
    for group in OVERLAYS:
        for kind in ("src", "raw"):
            shutil.copytree(REPO / kind / group, FIXTURE / kind / group,
                            ignore=shutil.ignore_patterns("__pycache__", "*.pyc"))
    shutil.copytree(REPO / "config/overlays", FIXTURE / "config/overlays",
                    dirs_exist_ok=True,
                    ignore=shutil.ignore_patterns("__pycache__", "*.pyc"))
    copy_file(REPO / "config/func_sizes.json", FIXTURE / "config/func_sizes.json")
    for name in SPLITS:
        copy_file(REPO / "ledger/splits" / (name + ".jsonl"),
                  FIXTURE / "ledger/splits" / (name + ".jsonl"))
    if fixture_overlay_pins() != sources:
        raise RuntimeError("overlay private copy differs from frozen source pins")
    (FIXTURE / "bin").symlink_to(REPO / "bin", target_is_directory=True)
    disc = FIXTURE / "work/disc"
    disc.mkdir(parents=True)
    (disc / "containers").symlink_to(REPO / "work/disc/containers", target_is_directory=True)
    (disc / "extract").symlink_to(REPO / "work/disc/extract", target_is_directory=True)
    for name in GFILES:
        expected = sha(GENERIC / name)
        if sha(FIXTURE / "tools/maspsx" / name) != expected:
            raise RuntimeError("private verifier default assembler differs")
        if sha(FIXTURE / "toolchain/maspsx" / name) != expected:
            raise RuntimeError("private build default assembler differs")
    if sha(FIXTURE / "build_slus/build.ninja") != sha(
            FIXTURE / "ledger/splits/slus.build.ninja"):
        raise RuntimeError("private SLUS pinned recipe differs")

    old_rows = {r["id"]: r for r in map(json.loads,
        (LIVE / "ledger/rows.jsonl").read_text().splitlines())}
    registry_log = HERE / "census_registry.log"
    with registry_log.open("w") as log:
        subprocess.run([sys.executable, "tools/registry.py"], cwd=FIXTURE,
                       stdout=log, stderr=subprocess.STDOUT, check=True)
    raw_registry = FIXTURE / "ledger/rows.jsonl"
    rows = [json.loads(line) for line in raw_registry.read_text().splitlines()]
    if len(rows) != 6767 or len({r["id"] for r in rows}) != 6767:
        raise RuntimeError("complete registry count/uniqueness differs")
    counts = Counter(r["container"] for r in rows)
    if counts["slus"] != 884 or counts["ovmovie"] != 22:
        raise RuntimeError("SLUS/movie registry scope differs")
    changes = {}
    retained_metadata = Counter()
    merged_rows = []
    for r in rows:
        old = old_rows.get(r["id"])
        if old is None:
            raise RuntimeError("registry added unexpected row: " + r["id"])
        differences = {k: [old.get(k), r.get(k)]
                       for k in set(old) | set(r) if old.get(k) != r.get(k)}
        if not differences:
            merged_rows.append(old)
            continue
        if r["container"] != "slus":
            allowed_metadata = {"cfg_corrected"}
            if r["id"] == "town/func_80614B88":
                allowed_metadata.add("row_asflags")
            if set(differences) - allowed_metadata:
                raise RuntimeError("unexpected overlay registry change: " + r["id"])
            for key in differences:
                retained_metadata[key] += 1
            merged_rows.append(old)
            continue
        if "cfg_corrected" in differences:
            if differences["cfg_corrected"] != [True, None]:
                raise RuntimeError("unexpected SLUS annotation change: " + r["id"])
            retained_metadata["cfg_corrected"] += 1
            differences.pop("cfg_corrected")
        if differences:
            changes[r["id"]] = differences
            merged = dict(old)
            for key in differences:
                merged[key] = r[key]
            merged_rows.append(merged)
        else:
            merged_rows.append(old)
    if len(changes) != 15 or any(not rid.startswith("slus/") for rid in changes):
        raise RuntimeError("registry rebase is not exactly 15 SLUS rows: " + str(len(changes)))
    if retained_metadata != Counter({"cfg_corrected": 428, "row_asflags": 1}):
        raise RuntimeError("historical row metadata difference count changed")
    allowed = {"cfg", "cell", "flags", "row_asflags", "stock"}
    if any(set(difference) - allowed for difference in changes.values()):
        raise RuntimeError("registry rebase changed non-recipe fields")
    raw_copy = FIXTURE / "ledger/rows.registry_raw.jsonl"
    shutil.copy2(raw_registry, raw_copy)
    raw_registry.write_text("".join(json.dumps(row, separators=(",", ":")) + "\n"
                                   for row in merged_rows))
    if len({row["id"] for row in merged_rows}) != 6767:
        raise RuntimeError("merged registry lost row identities")

    ovl_log = HERE / "census_mk_ovl_root.log"
    with ovl_log.open("w") as log:
        subprocess.run(["bash", "tools/build/mk_ovl_root.sh"], cwd=FIXTURE,
                       stdout=log, stderr=subprocess.STDOUT, check=True)
    if not (FIXTURE / "build_ovl/work/g3/overlay_func_compare.py").is_file():
        raise RuntimeError("private overlay root lacks comparator")
    if (FIXTURE / "build_ovl/overlays/main/first_pass_matched").resolve() != (
            FIXTURE / "src/main").resolve():
        raise RuntimeError("overlay source link escapes private fixture")
    if fixture_overlay_pins() != sources:
        raise RuntimeError("overlay sources changed while making private root")
    after = production_snapshot()
    (FIXTURE / "production_after_setup.json").write_text(
        json.dumps(after, indent=2) + "\n")
    if after != before:
        raise RuntimeError("production changed during private census setup")
    result = {
        "schema": 1, "status": "PREPARED",
        "live_proof_sha256": sha(LIVE / "ownership_receipt.json"),
        "ready29_stage_sha256": sha(FIXTURE / "build_slus/build/slus_006.14"),
        "registry_sha256": sha(FIXTURE / "ledger/rows.jsonl"),
        "runner_sha256": sha(RUNNER),
        "rows": len(rows), "counts": dict(counts),
        "recipe_rebased_rows": changes,
        "registry_raw_sha256": sha(raw_copy),
        "retained_production_row_metadata": dict(retained_metadata),
        "raw_registry_differences": {
            "total_rows": 444,
            "intended_slus_recipe_rows": len(changes),
            "cfg_corrected_annotation_rows": retained_metadata["cfg_corrected"],
            "town_80614B88_row_asflags_override_rows": retained_metadata["row_asflags"],
            "town_80614B88_override": "--aspsx-version=2.60",
        },
        "overlay_inputs_sha256": sha(FIXTURE / "overlay_source_pins.json"),
        "production_unchanged": True,
    }
    (FIXTURE / "census_setup_receipt.json").write_text(json.dumps(result, indent=2) + "\n")
    print(json.dumps({k: result[k] for k in ("status", "rows", "counts", "registry_sha256",
                                            "runner_sha256", "production_unchanged")}, indent=2))


def verify() -> None:
    result = json.loads((FIXTURE / "census_setup_receipt.json").read_text())
    if result["status"] != "PREPARED" or sha(RUNNER) != result["runner_sha256"]:
        raise RuntimeError("census runner or setup changed")
    if sha(FIXTURE / "ledger/rows.jsonl") != result["registry_sha256"]:
        raise RuntimeError("private census registry changed")
    if sha(LIVE / "ownership_receipt.json") != result["live_proof_sha256"]:
        raise RuntimeError("frozen live proof changed")
    if fixture_overlay_pins() != json.loads(
            (FIXTURE / "overlay_source_pins.json").read_text()):
        raise RuntimeError("private overlay inputs changed")
    before = json.loads((FIXTURE / "production_before_census.json").read_text())
    after = production_snapshot()
    (FIXTURE / "production_after_census.json").write_text(
        json.dumps(after, indent=2) + "\n")
    if before != after:
        raise RuntimeError("production changed during private census")
    print(json.dumps({"status": "VERIFIED", "rows": result["rows"],
                      "production_objects": len(after["objects"]),
                      "production_unchanged": True}))


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("action", choices=("prepare", "verify"))
    args = parser.parse_args()
    if args.action == "prepare":
        prepare()
    else:
        verify()


if __name__ == "__main__":
    main()
