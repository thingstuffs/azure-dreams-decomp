#!/usr/bin/env python3
"""(round 93, written by Fable lane r93_fable_c9858) usage: python3 tools/listing.py <row> <text.c> > out.s
Prints the normalised cc1 listing (screen.compile_s) of a text; on the pinned exact text it is retail's instruction order."""
import sys
from pathlib import Path
_ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(_ROOT / "tools/lanes/lanekit")); sys.path.insert(0, str(_ROOT / "tools/xform")); sys.path.insert(0, str(_ROOT / "tools"))
import kitlib, screen
kitlib.bootstrap(); row = kitlib.row_of(sys.argv[1])
lines = screen.compile_s(row, open(sys.argv[2]).read())
if lines is None: sys.exit("does not build")
print("\n".join(lines))
