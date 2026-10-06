#!/usr/bin/env python3
"""showflip.py <row> '<json list of moves>' [text] - the listing diff (pinned/shipped vs text/what-if cc1) after moves."""
import sys, json
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
import flip
from whatif import STATE, kitlib, variant_screen
rowid = sys.argv[1]; moves = [tuple(m) for m in json.loads(sys.argv[2])]
row = kitlib.row_of(rowid); pinned = kitlib.base_text(row, flip.LANE)
text = kitlib.erased_text(pinned) if len(sys.argv) < 4 else Path(sys.argv[3]).read_text()
STATE["on"] = False; scr = variant_screen.Screen(row, pinned)
STATE["on"], STATE["env"] = True, flip.env_of(moves)
print("\n".join(scr.diff(text, context=2)))
