#!/usr/bin/env python3
"""erase.py - what each pin holds, and which pins fall together.  Run this before writing shapes.

Five sol lanes hand-rolled `itertools.combinations` over `pin_sites.erase_many` +
`variant_screen.Screen.distance` (`probe_subsets.py`, `pair_scan.py`, `search_orders.py`,
`joint_local.py`, `subset_scan.py`), and the astra lane that ran the shared subset scan as its FIRST
step on every row solved 3 of 5.  This is that scan, lane-scoped, bounded, writing nothing outside
the lane and touching no ledger.

    cd work/native_lane/<lane>
    python3 <repo>/tools/lanes/lanekit/erase.py dungeon/func_8009612C
    python3 <repo>/tools/lanes/lanekit/erase.py dungeon/func_8009612C --mode subset --budget 60
    python3 <repo>/tools/lanes/lanekit/erase.py dungeon/func_8009612C --variant experiments/f/v3.c
    python3 <repo>/tools/lanes/lanekit/erase.py dungeon/func_80D150D0 --variant cand.c --cfg "2.7.2-cdk-G0"

Modes (each includes the one before it):
  lone    every site erased ALONE, with its note and its statement
  all     plus all pins erased together
  pair    plus every pair (rows up to --pair-pins sites)          [default]
  subset  plus the same-macro and same-variable groups, and every subset on small rows
          (`tools/lanes/joint_scan.py`'s own subset rule, reused, not re-derived)

`--variant FILE` runs the scan on a candidate you have already written instead of the row's base -
the pins that are still there after your change, and what they now hold.  That is the mid-row
question ("which of the four is left holding it?"), and it was the one the hand-rolled scans could
not answer.

Distances are cc1 listing lines changed against the PINNED text, ~15 ms each; the byte scorer is
never called here - except with `--cfg CFG`: at a foreign cell the pinned listing is not retail's, so
each erasure is byte-SCORED as the row at CFG instead (`kitlib.score_at`, total = words wrong; 4 threads,
5-20 s each, no ledger write; mode defaults to `all`, and `none` = the text as it stands is shown).  A pair FALLS TOGETHER when erasing both leaves a residue no larger than either
alone (`duck_brief.fall_together`, the same rule the duck uses): those pins are one mechanism and
one candidate has to move both.  The table is written to `erase_<func>.md` in the lane.
"""
from __future__ import annotations

import argparse
import sys
import time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import kitlib                                                             # noqa: E402

DEFAULT_BUDGET = 60          # cc1 listings; about one second per twenty on a warm box


def site_label(s):
    kind, macro, arg = s[0], s[1], s[2]
    return "%s(%s)" % (macro, arg) if kind == "stmt" else "%s %s" % (macro, arg)


def total_of(v):
    """The byte scorer's `total` (words wrong), or None when it did not score."""
    t = (v or {}).get("total")
    return t if isinstance(t, (int, float)) else (0 if (v or {}).get("exact") else None)


def scan(row_id, lane=None, mode="pair", budget=DEFAULT_BUDGET, pair_pins=8, variant=None, cfg=None,
         workers=4, score_at=None):
    lane = kitlib.bootstrap(lane)
    row = kitlib.row_of(row_id)
    if cfg == row["cfg"]:
        cfg = None
    rowc = kitlib.row_at_cfg(row, cfg) if cfg else None
    score_at = score_at or kitlib.score_at
    base = kitlib.base_text(row, lane)
    text = Path(variant).read_text(errors="replace") if variant else base
    sites = kitlib.sites(text)
    sc = kitlib.screen_for(row, base)
    if sc.target is None:
        raise SystemExit("erase: the row's pinned text does not build")
    if not sites:
        return {"row": row["id"], "func": row["func"], "variant": variant, "sites": [], "lines": [], "lone": {},
                "all": None, "subsets": [], "spent": 0, "n": 0, "cfg": cfg, "here": None}

    lines = text.splitlines()
    spent = [0]

    def batch(texts):
        """Distances (listing, or byte totals at `cfg`) of `texts`, in order; counts against the budget."""
        spent[0] += len(texts)
        if not cfg:
            return [sc.distance(t) for t in texts]
        with ThreadPoolExecutor(workers) as ex:
            return [total_of(v) for v in ex.map(lambda t: score_at(rowc, t), texts)]

    def dist(t):
        return batch([t])[0]

    here = dist(text) if cfg else None
    lone = dict(enumerate(batch([kitlib.erase(text, [s]) for s in sites])))

    alld = dist(kitlib.erase(text, sites)) if mode in ("all", "pair", "subset") else None

    subsets = []
    if mode in ("pair", "subset"):
        kitlib.add_paths()
        from joint_scan import subsets_of                                # noqa: E402
        n = len(sites)
        want = subsets_of(sites, pair_pins if mode == "pair" else max(pair_pins, n),
                          6 if mode == "subset" else 0)
        want = [idx for idx in want if 2 <= len(idx) < n]
        want.sort(key=len)
        want = want[:max(0, budget - spent[0])]
        subsets = list(zip(want, batch([kitlib.erase(text, [sites[i] for i in idx]) for idx in want])))

    return {"row": row["id"], "func": row["func"], "variant": variant, "sites": sites,
            "lines": lines, "lone": lone, "all": alld, "subsets": subsets, "spent": spent[0],
            "n": len(sites), "cfg": cfg, "here": here}


def render(res):
    kitlib.add_paths()
    from duck_brief import fall_together                                 # noqa: E402
    L = ["# Erasure table - %s%s" % (res["row"], "  (variant %s)" % res["variant"] if res["variant"] else ""),
         "", ("%d live pin sites; %d byte scores at %s; distances are the scorer's total (words wrong) "
              "at that cfg, the text as it stands scores %s." % (res["n"], res["spent"], res["cfg"], res.get("here"))
              if res.get("cfg") else
              "%d live pin sites; %d cc1 listings; distances are changed listing lines against the "
              "pinned text." % (res["n"], res["spent"])), ""]
    body = []
    for i, s in enumerate(res["sites"]):
        stmt = res["lines"][s[5] - 1].strip() if s[5] - 1 < len(res["lines"]) else ""
        stmt = stmt.split("/*")[0].strip()
        body.append([i, s[5], site_label(s), res["lone"][i], stmt[:60]])
    L += ["## Each pin alone", "", "```",
          kitlib.fmt_table(["#", "line", "pin", "dist alone", "statement"], body), "```", ""]
    if res["all"] is not None:
        worst = max((v for v in res["lone"].values() if v is not None), default=None)
        L += ["## All %d pins erased together: distance %s%s" % (
            res["n"], res["all"],
            "  (no more than the worst single, %s: they are ONE mechanism)" % worst
            if worst is not None and res["all"] is not None and res["all"] <= worst else ""), ""]
    if res["subsets"]:
        rows2, tog = [], []
        for idx, d in res["subsets"]:
            verdict = ""
            if len(idx) == 2:
                ft = fall_together(d, res["lone"][idx[0]], res["lone"][idx[1]])
                verdict = "FALL TOGETHER" if ft else "independent" if ft is False else "?"
                if ft:
                    tog.append(idx)
            else:
                best = min((res["lone"][i] for i in idx if res["lone"][i] is not None), default=None)
                if best is not None and d is not None and d <= best:
                    verdict = "FALL TOGETHER"
                    tog.append(idx)
            rows2.append(["{%s}" % ",".join(str(i) for i in idx), len(idx), d, verdict])
        L += ["## Subsets erased together", "", "```",
              kitlib.fmt_table(["sites", "k", "dist", "verdict"], rows2), "```", ""]
        if tog:
            L += ["Groups that fall together (one candidate must move all of each): "
                  + "; ".join("{%s}" % ",".join(str(i) for i in g) for g in tog), ""]
        else:
            L += ["No measured subset falls together: each pin is its own question.", ""]
    return "\n".join(L)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("row_id")
    ap.add_argument("--mode", choices=("lone", "all", "pair", "subset"), default=None,
                    help="default pair (all with --cfg: byte scores are 5-20 s each)")
    ap.add_argument("--budget", type=int, default=DEFAULT_BUDGET, help="cc1 listings (default %d)" % DEFAULT_BUDGET)
    ap.add_argument("--pair-pins", type=int, default=8, help="measure every pair up to this many sites")
    ap.add_argument("--variant", help="scan this candidate's remaining pins instead of the base")
    ap.add_argument("--cfg", help="byte-score each erasure at this cfg instead of listing distances (no ledger write)")
    a = ap.parse_args()
    t0 = time.time()
    res = scan(a.row_id, mode=a.mode or ("all" if a.cfg else "pair"), budget=a.budget, pair_pins=a.pair_pins,
               variant=a.variant, cfg=a.cfg)
    out = render(res)
    print(out)
    lane = kitlib.bootstrap()
    tag = res.get("func", "row") + ("_" + Path(a.variant).stem if a.variant else "") + ("_at_" + a.cfg.replace(" ", "_") if a.cfg else "")
    p = lane / ("erase_%s.md" % tag)
    p.write_text(out + "\n")
    print("(%d listings, %.1fs; written to %s)" % (res["spent"], time.time() - t0, p), file=sys.stderr)


if __name__ == "__main__":
    main()
