#!/usr/bin/env python3
"""Invoke the unmodified private prover CLI with genuine ASPSX's short scratch root."""

import os
from pathlib import Path
import runpy
import shutil
import sys

ROOT = Path.cwd()
sys.path.insert(0, str(ROOT / "tools"))
from fidelity import aspsx_diff as A

if len(sys.argv) < 2 or sys.argv[1] not in ("ownership", "certificate"):
    raise SystemExit("usage: prover_cli.py {ownership|certificate} <original CLI args>")
target = {"ownership": "prove_slus_ownership.py",
          "certificate": "certify_slus_module.py"}[sys.argv[1]]
scratch = Path("/tmp") / ("gp33_a_" + str(os.getpid()))
if scratch.exists():
    raise RuntimeError("genuine scratch collision")
scratch.mkdir()
A.TMP = scratch
A._SLUS = None
sys.argv = ["tools/fidelity/" + target, *sys.argv[2:]]
try:
    runpy.run_path(str(ROOT / "tools/fidelity" / target), run_name="__main__")
finally:
    shutil.rmtree(scratch)
