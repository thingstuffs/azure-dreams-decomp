#!/usr/bin/env python3
"""Separate extern metadata's scheduling effect from actual GP relocations."""
from pathlib import Path
import hashlib
import json
import re
import subprocess

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
FIXTURE = HERE.parent / "census_final_fixture"
BUILD = FIXTURE / "build_slus"
CCDIR = ROOT / "toolchain/compilers/gcc-2.7.2"
PYTHON = ROOT / ".venv/bin/python"

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

def run(cmd, *, cwd=BUILD, text=None):
    p = subprocess.run([str(x) for x in cmd], input=text, cwd=cwd,
                       capture_output=True, encoding="utf-8")
    if p.returncode:
        raise RuntimeError(str(cmd) + "\n" + p.stderr)
    return p.stdout

def disassembly(path):
    text = run(["mipsel-linux-gnu-objdump", "-dr", path])
    return "\n".join(line for line in text.splitlines()
                     if "file format" not in line).strip()

def main():
    (HERE / ".ignore").write_text("*\n")
    inputs = [BUILD / "build/partition_sources/code.c",
              FIXTURE / "tools/build/ccproc.py",
              FIXTURE / "tools/fidelity/maspsx_trace.py",
              FIXTURE / "tools/maspsx/maspsx.py",
              FIXTURE / "tools/maspsx/maspsx/__init__.py", CCDIR / "gcc", CCDIR / "cc1"]
    pins = {str(p): sha(p) for p in inputs}
    raw = HERE / "raw.s"
    run([CCDIR / "gcc", "-B" + str(CCDIR) + "/", "-S", "-O2", "-w",
         "-I" + str(FIXTURE / "include"), "build/partition_sources/code.c", "-o", raw])
    stream = run([PYTHON, FIXTURE / "tools/build/ccproc.py"], text=raw.read_text())
    (HERE / "pipeline.s").write_text(stream)
    variants = {"normal": [], "strip_externs": ["--strip-externs"],
                "disable_store_delay": ["--disable", "_expand_store_to_symbol_in_delay"]}
    records = {}
    for arm, extra in variants.items():
        cmd = [PYTHON, FIXTURE / "tools/fidelity/maspsx_trace.py", "--trace", HERE / (arm + ".trace.json"),
               *extra, "--", "--aspsx-version=2.79", "--dont-force-G0",
               "-I" + str(BUILD), "-I" + str(FIXTURE / "include"), "-EL", "-march=r3000", "-G8"]
        output = run(cmd, text=stream)
        (HERE / (arm + ".s")).write_text(output)
        obj = HERE / (arm + ".o")
        run([*cmd, "--run-assembler", "--gnu-as-path=mipsel-linux-gnu-as", "-o", obj], text=stream)
        reloc = run(["mipsel-linux-gnu-readelf", "-r", obj])
        (HERE / (arm + ".relocations.txt")).write_text(reloc)
        (HERE / (arm + ".disasm.txt")).write_text(disassembly(obj) + "\n")
        records[arm] = {"listing_sha256": sha(HERE / (arm + ".s")), "object_sha256": sha(obj),
                        "gprel_relocations": len(re.findall(r"\bR_MIPS_GPREL\w*", reloc)),
                        "fired": json.loads((HERE / (arm + ".trace.json")).read_text())["fired"]}
    same_ablation_listing = (HERE / "strip_externs.s").read_bytes() == (HERE / "disable_store_delay.s").read_bytes()
    baseline_match = disassembly(HERE / "normal.o") == disassembly(BUILD / "build/src/code.o")
    assert baseline_match, "fresh normal stream differs from measured pipeline object"
    assert same_ablation_listing, "extern stripping has additional output effects"
    assert records["normal"]["gprel_relocations"] == 0
    assert records["strip_externs"]["gprel_relocations"] == records["disable_store_delay"]["gprel_relocations"] == 0
    assert "_expand_store_to_symbol_in_delay" in records["normal"]["fired"]
    assert "_expand_store_to_symbol_in_delay" not in records["strip_externs"]["fired"]
    assert pins == {str(p): sha(p) for p in inputs}
    receipt = {"status": "ATTRIBUTED", "scope": "SLUS code remainder only",
               "recipe": "2.7.2 default G8, O2; guarded maspsx 2.79",
               "fresh_normal_matches_measured_object_disassembly_and_relocations": baseline_match,
               "extern_strip_equals_disable_store_delay_listing": same_ablation_listing,
               "finding": "extern metadata enables the store-delay rewrite; this ablation is not evidence of a GP addressing difference",
               "records": records, "inputs": pins, "inputs_unchanged": True,
               "raw_compiler_sha256": sha(raw), "pipeline_sha256": sha(HERE / "pipeline.s")}
    (HERE / "receipt.json").write_text(json.dumps(receipt, indent=2) + "\n")
    print(json.dumps(receipt, indent=2))

if __name__ == "__main__":
    main()
