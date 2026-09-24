#!/usr/bin/env python3
"""Three fixed F240 compiler arms, preserving raw RTL dumps for inspection."""

from __future__ import annotations

import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess

ROOT = Path(__file__).resolve().parents[4]
HERE = Path(__file__).resolve().parent
SOURCE = ROOT / "work/native_lane/gp_cd_contract/cohort/f240_owned.c"
INCLUDE = ROOT / "work/native_lane/gp_cd_contract/include"
SOURCE_SHA256 = "fd2520894739effd99a2ae2ca6299bb9681902bab774d8713c6852f779e17cdf"
ARMS = {
    "A_cdk_noexp": ("2.7.2-cdk", ("-G32", "-fno-expensive-optimizations")),
    "B_281_noexp": ("2.8.1", ("-G32", "-fno-expensive-optimizations")),
    "C_cdk_exp": ("2.7.2-cdk", ("-G32",)),
}
KEY_INSNS = {"7": "queue_hi", "8": "queue_lo", "9": "head_load",
             "11": "add_31", "12": "mask_31", "15": "stride_shift_1",
             "17": "stride_add", "18": "stride_shift_3", "20": "entry_address",
             "23": "return_load"}


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def key_order(path: Path) -> list[str]:
    ids = re.findall(r"(?m)^\((?:insn|jump_insn)\s+(\d+)\s", path.read_text())
    return [KEY_INSNS[number] for number in ids if number in KEY_INSNS]


def assembly_ops(path: Path) -> tuple[list[str], int]:
    body = path.read_text().split("func_8003F240:", 1)[1].split("\t.end\tfunc_8003F240", 1)[0]
    ops = [match.group(1) for line in body.splitlines()
           if (match := re.match(r"\s+([a-z][a-z0-9.]*)\t", line))]
    return ops, body.count("#nop")


def run() -> dict:
    if sha(SOURCE) != SOURCE_SHA256:
        raise ValueError("F240 owner source changed")
    results = {}
    for label, (version, flags) in ARMS.items():
        directory = HERE / label
        directory.mkdir(exist_ok=True)
        source = directory / "f240_owned.c"
        shutil.copy2(SOURCE, source)
        compiler_dir = ROOT / "toolchain/compilers" / f"gcc-{version}"
        gcc = compiler_dir / "gcc"
        cmd = [str(gcc), f"-B{compiler_dir}/", "-S", "-O2", *flags,
               "-da", "-I", str(INCLUDE), "-w", source.name,
               "-o", "f240_owned.s"]
        proc = subprocess.run(cmd, cwd=directory, capture_output=True, text=True)
        (directory / "compile.log").write_text(proc.stdout + proc.stderr)
        if proc.returncode:
            raise RuntimeError(f"{label}: compiler exited {proc.returncode}: {proc.stderr[-2000:]}")
        dumps = sorted(p for p in directory.iterdir()
                       if p.is_file() and p.name.startswith("f240_owned.c.") and p.suffix != ".c")
        if not dumps:
            raise RuntimeError(f"{label}: -da created no RTL dumps")
        orders = {pass_name: key_order(directory / f"f240_owned.c.{pass_name}")
                  for pass_name in ("rtl", "flow", "combine", "sched", "sched2")}
        before_sched = "regmove" if (directory / "f240_owned.c.regmove").exists() else "combine"
        orders[before_sched] = key_order(directory / f"f240_owned.c.{before_sched}")
        ops, load_delay_marker = assembly_ops(directory / "f240_owned.s")
        sched_text = (directory / "f240_owned.c.sched").read_text()
        scheduled_cycles = int(re.search(r";; total time = (\d+)", sched_text).group(1))
        results[label] = {"compiler": version, "flags": list(flags),
                          "source_sha256": sha(source), "gcc_sha256": sha(gcc),
                          "assembly_sha256": sha(directory / "f240_owned.s"),
                          "rtl_key_order": orders, "assembly_ops": ops,
                          "assembly_load_delay_nop_marker": load_delay_marker,
                          "first_scheduler_cycles": scheduled_cycles,
                          "dump_files": [{"name": p.name, "sha256": sha(p), "bytes": p.stat().st_size}
                                         for p in dumps]}
    for label, arm in results.items():
        pre = arm["rtl_key_order"]["regmove" if label != "B_281_noexp" else "combine"]
        assert pre.index("queue_hi") < pre.index("queue_lo") < pre.index("head_load")
        scheduled = arm["rtl_key_order"]["sched"]
        if label == "C_cdk_exp":
            assert scheduled.index("queue_hi") < scheduled.index("head_load") < scheduled.index("queue_lo")
            assert arm["assembly_ops"][:3] == ["lui", "lbu", "addiu"]
            assert arm["assembly_load_delay_nop_marker"] == 0
            assert arm["first_scheduler_cycles"] == 11
        else:
            assert scheduled.index("head_load") < scheduled.index("queue_hi") < scheduled.index("queue_lo")
            assert arm["assembly_ops"][:3] == ["lbu", "addu", "andi"]
            assert arm["assembly_load_delay_nop_marker"] == 1
            assert arm["first_scheduler_cycles"] == 12
    report = {"source": str(SOURCE.relative_to(ROOT)), "source_sha256": SOURCE_SHA256,
              "private_header_sha256": {p.name: sha(p) for p in sorted((INCLUDE / "slus").glob("cd_*.h"))},
              "arms": results}
    (HERE / "compile_receipt.json").write_text(json.dumps(report, indent=2) + "\n")
    return report


if __name__ == "__main__":
    result = run()
    for name, arm in result["arms"].items():
        print(name, arm["compiler"], arm["flags"], "dumps", len(arm["dump_files"]))
