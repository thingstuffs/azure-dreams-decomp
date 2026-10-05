#!/usr/bin/env python3
"""(round 93, written by Fable lane r93_fable_c9858) usage: python3 tools/ccerr.py <row> <text.c>
Compiles a text with the row's cell exactly as screen.compile_s does and prints the preprocessor / cc1 stderr
(lab.py only says 'no-build')."""
import sys, subprocess, tempfile
from pathlib import Path as _P
_ROOT = _P(__file__).resolve().parents[3]
from pathlib import Path
sys.path.insert(0, str(_ROOT / "tools/lanes/lanekit")); sys.path.insert(0, str(_ROOT / "tools/xform")); sys.path.insert(0, str(_ROOT / "tools"))
import kitlib, screen
from common import parse_cfg
kitlib.bootstrap(); row = kitlib.row_of(sys.argv[1]); text = open(sys.argv[2]).read()
cell, flags = parse_cfg(row["cfg"]); D = screen.ROOT / "toolchain/compilers" / ("gcc-" + cell)
with tempfile.TemporaryDirectory(prefix="ccerr_") as td:
    d = Path(td); f = d / Path(row["c_path"]).name; f.write_text(text)
    r = subprocess.run([str(D / "gcc"), "-B" + str(D) + "/", "-E", "-O2", *flags, "-I" + str(screen.INCLUDE), "-w", f.name, "-o", "f.i"], cwd=d, capture_output=True, text=True)
    print("cpp rc", r.returncode); print(r.stderr[:3000])
    if r.returncode == 0:
        r = subprocess.run([str(D / "cc1"), "f.i", "-quiet", "-O2", *flags, "-o", "f.s"], cwd=d, capture_output=True, text=True)
        print("cc1 rc", r.returncode); print(r.stderr[:4000])
