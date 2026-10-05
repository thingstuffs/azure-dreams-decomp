#!/usr/bin/env python3
"""Earlier lanes' FEWER-PIN texts that scored close to retail, for rows that are still pinned (round 94).

    python3 tools/lanes/old_nearmiss.py [--max-total 4] [--top 2]

Reads every work/native_lane/*/lab_log.jsonl (lab.py's log) and prints, per pinned row, the best entries whose pin count
is below the row's current count and whose scorer total is <= --max-total: row, pins now, pins then, total, lane,
variant, cfg. The total is from the lane's own base text and cell - re-score it on the current base before trusting it.
Why: r94_opus_p32 solved dungeon/func_800C4A80 16 -> 0 from r86_opus_up's 0-pin text (total 2) that no lane had used
since; fidelity cleanups (prototypes, widths, gotos) change rows under such texts, so old near-misses go stale-but-close.
The variant's file lives under the lane's cand/, experiments/<func>/ or c/ directory (find -name '<variant>.c').
"""
import argparse, collections, glob, json, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from pin_census import sites_of

ap = argparse.ArgumentParser(); ap.add_argument("--max-total", type=int, default=4); ap.add_argument("--top", type=int, default=2)
a = ap.parse_args()
pinned = {}
for f in glob.glob(str(ROOT / "src/*/*.c")):
    n = len(sites_of(open(f, errors="replace").read()))
    if n: pinned["/".join(f.split("/")[-2:])[:-2]] = n
best = collections.defaultdict(list)
for lf in glob.glob(str(ROOT / "work/native_lane/*/lab_log.jsonl")):
    lane = lf.split("/")[-2]
    for line in open(lf, errors="replace"):
        try: d = json.loads(line)
        except ValueError: continue
        r = d.get("row"); sc = d.get("score")
        if r not in pinned or not isinstance(sc, dict) or not isinstance(sc.get("total"), int): continue
        p = d.get("pins")
        if not isinstance(p, int) or p >= pinned[r]: continue
        best[r].append((sc["total"], p, lane, str(d.get("variant")), d.get("cfg", "")))
out = []
for r, l in best.items():
    seen = set()
    for t, p, lane, v, c in sorted(l):
        if t > a.max_total or (lane, v) in seen: continue
        seen.add((lane, v)); out.append((t, -(pinned[r] - p), r, pinned[r], p, lane, v, c))
        if len([x for x in seen]) >= a.top: break
print("row\tpins_now\tpins_then\ttotal\tlane\tvariant\tcfg")
for t, _, r, n, p, lane, v, c in sorted(out):
    print(r, n, p, t, lane, v, c, sep="\t")
