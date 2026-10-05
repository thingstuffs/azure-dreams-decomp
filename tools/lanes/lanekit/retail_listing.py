#!/usr/bin/env python3
"""(round 93, written by Fable lane r93_fable_c9858) usage: python3 tools/retail_listing.py <row> <cand.c> [--cfg CFG] > out.txt
Prints the byte scorer's generated listing (v["text"]) for a text; on the pinned (exact) text that is retail's listing."""
import sys, os
sys.path.insert(0, str(_ROOT / "tools/lanes/lanekit"))
import kitlib
row_id, path = sys.argv[1], sys.argv[2]
cfg = sys.argv[sys.argv.index("--cfg")+1] if "--cfg" in sys.argv else None
lane = kitlib.bootstrap(); row = kitlib.row_of(row_id)
text = open(path).read()
v = kitlib.score_at(row, text, cfg=cfg or row["cfg"], diff=True)
print("# score:", {k: v[k] for k in v if k != "text"})
print(v["text"])
