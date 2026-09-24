#!/usr/bin/env python3
"""Reproduce the frozen before/after CDK assembly proof from saved sources."""

from __future__ import annotations

import hashlib
import json
from pathlib import Path
import shutil
import subprocess

HERE = Path(__file__).resolve().parent
ROOT = next((parent for parent in HERE.parents
             if (parent / "toolchain/compilers/gcc-2.7.2-cdk/gcc").is_file()), None)
TOOLS = next((parent for parent in HERE.parents
              if (parent / "live_fixture/include/common.h").is_file()), None)
if ROOT is None or TOOLS is None:
    raise RuntimeError("cannot locate compiler or private include fixture")
INCLUDE = TOOLS / "live_fixture/include"
CCDIR = ROOT / "toolchain/compilers/gcc-2.7.2-cdk"
BUILD = HERE / "reproduction_build"
RECEIPT = HERE / "reproduction_receipt.json"


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def pins() -> dict:
    headers = {str(path.relative_to(INCLUDE)): sha(path)
               for path in sorted(INCLUDE.rglob("*")) if path.is_file()}
    if "common.h" not in headers or not {"game.h", "globals.h", "include_asm.h"} <= headers.keys():
        raise RuntimeError("required include headers are missing")
    return {
        "gcc_sha256": sha(CCDIR / "gcc"),
        "cc1_sha256": sha(CCDIR / "cc1"),
        "include_sha256": headers,
        "reproducer_sha256": sha(Path(__file__)),
        "original_receipt_sha256": sha(HERE / "receipt.json"),
    }


def main() -> None:
    original = json.loads((HERE / "receipt.json").read_text())
    if (original.get("status") != "MATCH" or original.get("production_modified")
            or original.get("frozen_fixtures_modified") or len(original.get("records", [])) != 4):
        raise RuntimeError("original source hygiene proof differs")
    expected = {"w_80041AB0.c", "w_8004AB7C.c", "gp_d92c_owned.c", "w_8003FAD4.c"}
    if {Path(r["source"]).name for r in original["records"]} != expected:
        raise RuntimeError("original source set differs")

    before_pins = pins()
    if BUILD.is_symlink():
        raise RuntimeError("unsafe reproduction output link")
    if BUILD.exists():
        shutil.rmtree(BUILD)
    BUILD.mkdir()
    (BUILD / ".ignore").write_text("*\n")
    results = []
    for prior in original["records"]:
        name = Path(prior["source"]).name
        if prior["compiler"] != str(CCDIR / "gcc") or prior["flags"] != "-S -O2 -w":
            raise RuntimeError("original compiler or flags differ: " + name)
        if not prior["compiler_assembly_identical"]:
            raise RuntimeError("original assembly proof was not exact: " + name)
        arms = {}
        for arm in ("before", "after"):
            saved_source = HERE / arm / name
            saved_assembly = HERE / arm / (name + ".s")
            if (sha(saved_source) != prior[arm + "_sha256"]
                    or sha(saved_assembly) != prior[arm + "_assembly_sha256"]):
                raise RuntimeError("original snapshot hash differs: " + name + ":" + arm)
            outdir = BUILD / arm
            outdir.mkdir(exist_ok=True)
            shutil.copyfile(saved_source, outdir / name)
            cmd = [str(CCDIR / "gcc"), "-B" + str(CCDIR) + "/", "-S", "-O2",
                   "-I" + str(INCLUDE), "-w", name, "-o", name + ".s"]
            proc = subprocess.run(cmd, cwd=outdir, capture_output=True, text=True)
            (outdir / (name + ".log")).write_text(proc.stdout + proc.stderr)
            if proc.returncode:
                raise RuntimeError("compiler failed: " + name + ":" + arm + ":" + proc.stderr)
            actual = outdir / (name + ".s")
            if sha(actual) != prior[arm + "_assembly_sha256"] or actual.read_bytes() != saved_assembly.read_bytes():
                raise RuntimeError("recompiled assembly differs from original: " + name + ":" + arm)
            arms[arm] = actual.read_bytes()
        if arms["before"] != arms["after"]:
            raise RuntimeError("recompiled before/after assembly differs: " + name)
        results.append({
            "source": prior["source"],
            "before_sha256": prior["before_sha256"],
            "after_sha256": prior["after_sha256"],
            "assembly_sha256": hashlib.sha256(arms["after"]).hexdigest(),
            "raw_compiler_assembly_identical": True,
            "matches_original_assembly": True,
        })
    if pins() != before_pins:
        raise RuntimeError("compiler, headers, reproducer, or original receipt changed during reproduction")
    receipt = {
        "status": "REPRODUCED",
        "original_receipt": "receipt.json",
        "compiler_flags": "-S -O2 -w",
        "pins": before_pins,
        "records": results,
        "production_modified": False,
        "frozen_snapshots_modified": False,
    }
    temporary = RECEIPT.with_suffix(".json.tmp")
    temporary.write_text(json.dumps(receipt, indent=2, sort_keys=True) + "\n")
    temporary.replace(RECEIPT)
    print(json.dumps({"status": receipt["status"], "sources": len(results),
                      "gcc_sha256": before_pins["gcc_sha256"],
                      "cc1_sha256": before_pins["cc1_sha256"]}, sort_keys=True))


if __name__ == "__main__":
    main()
