#!/usr/bin/env python3
"""Row lists for the r76 fair model A/B (docs/evidence/r76_measurement_protocol.md).  Builds nothing, launches nothing.

    python3 tools/lanes/ab_plan.py [--per-band 40] [--pack 5] [--seed 76] [--out docs/evidence]

Writes
  <out>/r76_ab_rows.json   {lane: [row ids]} for pool.py --rows-json (select one arm with --lanes) and for the
                           Agent-tool arms (build_class_pack.py --rows ... then kit_pack.py).  Lane names
                           r76_<arm>_<band>_<k>; pack k holds the SAME rows in every arm (a paired design).
  <out>/r76_ab_plan.json   the pool counts, the seed, and the rows per band with their pin counts and status.

The pool, per band, from the current tree (pinned rows, not ovmovie, not slus):
  1-2, 3-7  whole-function packs: rows no kit-era strong lane (astra/opus, lane r68_* on) served at the current
            text (tools/lanes/served.py strong_kit_pool: `never` or `older-text`) AND no launched lane of ANY arm's
            tier (luna6, sol6, astra, opus, sonnet) served whole at the current text - so pool.py's default tier
            guard refuses no row in any arm and the arms stay matched.
  8+        CLUSTER packs (--cluster 3-5): a whole-function serve does not block a cluster serve (the served key
            includes the scope), so every 8+ row is eligible unless an arm's tier already served it as a cluster
            at the current text.  (Its `status` column still says whether a strong kit lane served it whole.)
Rows are drawn per band by a seeded shuffle (not by pin count, which would bias a band toward its edge).
"""
import argparse
import json
import random
import sys
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(Path(__file__).resolve().parent))
import served  # noqa: E402

ARMS = ("luna6", "sol6", "astra", "opus", "sonnet")
BANDS = (("b12", "1-2"), ("b37", "3-7"), ("b8c", "8+"))


def eligible(texts, root=ROOT, arms=ARMS):
    """[{row, pins, band, status}] of the A/B pool (see the module docstring)."""
    sk = served.strong_kit_serves(root)
    hit = set()
    for r in served.serve_records(root):
        cur = texts.get(r["row"])
        if not r["launched"] or r["tier"] not in arms or cur is None or r["sha"] != cur[0]:
            continue
        if (r["scope"] == "whole") == (cur[1] < 8):     # whole serves block whole packs, cluster serves cluster packs
            hit.add(r["row"])
    out = []
    for rid, (sha, pins, container) in sorted(texts.items()):
        if pins == 0 or container in ("ovmovie", "slus") or rid in hit:
            continue
        recs = sk.get(rid, [])
        if pins < 8 and any(r["sha"] == sha for r in recs):
            continue
        out.append({"row": rid, "pins": pins, "band": served.band_of(pins),
                    "status": "older-text" if recs and not any(r["sha"] == sha for r in recs)
                    else ("served-whole-at-this-text" if recs else "never")})
    return out


def draw(rows, per_band, pack, seed, arms=ARMS):
    """({lane: rows}, {band: [chosen rows]}): per band a seeded shuffle, cut to per_band, split into packs."""
    rng = random.Random(seed)
    lanes, chosen = {}, {}
    for tag, band in BANDS:
        b = sorted(r["row"] for r in rows if r["band"] == band)
        rng.shuffle(b)
        b = b[:per_band - per_band % pack] if len(b) >= per_band else b[:len(b) - len(b) % pack]
        chosen[band] = b
        for k in range(len(b) // pack):
            for arm in arms:
                lanes["r76_%s_%s_%d" % (arm, tag, k + 1)] = b[k * pack:(k + 1) * pack]
    return lanes, chosen


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--per-band", type=int, default=40)
    ap.add_argument("--pack", type=int, default=5)
    ap.add_argument("--seed", type=int, default=76)
    ap.add_argument("--out", default=str(ROOT / "docs/evidence"))
    a = ap.parse_args(argv)
    texts = served.current_texts()
    pool = served.strong_kit_pool(texts=texts)
    ok = eligible(texts)
    lanes, chosen = draw(ok, a.per_band, a.pack, a.seed)
    info = {rid: p for p in ok for rid in [p["row"]]}
    counts = {}
    for p in pool + ok:
        counts.setdefault(p["band"], {"strong_kit_pool": 0, "eligible": 0, "eligible_pins": 0, "never": 0})
    for p in pool:
        counts[p["band"]]["strong_kit_pool"] += 1
    for p in ok:
        c = counts[p["band"]]
        c["eligible"] += 1
        c["eligible_pins"] += p["pins"]
        c["never"] += p["status"] == "never"
    plan = {"schema": "azure-clean.r76-ab-plan.v1", "seed": a.seed, "per_band": a.per_band, "pack": a.pack,
            "arms": list(ARMS), "bands": {band: tag for tag, band in BANDS}, "pool_counts": counts,
            "rows": {band: [{"row": r, "pins": info[r]["pins"], "status": info[r]["status"]} for r in rs]
                     for band, rs in chosen.items()}}
    out = Path(a.out)
    (out / "r76_ab_rows.json").write_text(json.dumps(lanes, indent=0) + "\n")
    (out / "r76_ab_plan.json").write_text(json.dumps(plan, indent=1) + "\n")
    for band, c in counts.items():
        print("band %-4s strong-kit pool %3d, eligible %3d (%d pins, %d never served), drawn %d" % (
            band, c["strong_kit_pool"], c["eligible"], c["eligible_pins"], c["never"], len(chosen.get(band, []))))
    print("%d lanes (%d arms) -> %s" % (len(lanes), len(ARMS), out / "r76_ab_rows.json"))
    return 0


if __name__ == "__main__":
    sys.exit(main())
