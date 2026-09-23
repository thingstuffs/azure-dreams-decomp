#!/usr/bin/env python3
"""diff.py - the unified cc1-listing diff of a candidate against the pinned (or erased, or any) text.

    python3 <KIT>/diff.py <row> <candidate.c|erased|pinned> [--vs pinned|erased|FILE] [--ctx N] [--score]

26 lanes of round 73 wrote this same 10-line wrapper (`ldiff.py`, `lst.py`, `sd.py`, `dd.py`, ...)
around `screen.compile_s` + `difflib.unified_diff`.  `lab.py` already computes it for every variant
(`experiments/<func>/<name>.diff`); this prints it for one file, on demand.

`-` lines are the reference listing (`--vs`, default the PINNED text = retail's order on a byte-exact
row), `+` lines the candidate's.  The last line is the distance `lab.py` logs (changed listing lines).
`--score` also runs the byte scorer (`tools/verify.py`) whatever the distance, and journals that
measurement to `lab_log.jsonl`; without `--score` nothing is written anywhere - it is a viewer.
"""
from __future__ import annotations

import argparse
import difflib
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import kitlib                                                             # noqa: E402


def render(ref, cand, ctx=3, ref_name="pinned", cand_name="candidate"):
    """Unified diff lines of two normalised listings; [] when identical; None if either failed."""
    if ref is None or cand is None:
        return None
    return list(difflib.unified_diff(ref, cand, ref_name, cand_name, lineterm="", n=ctx))


def distance(lines):
    return None if lines is None else sum(
        1 for l in lines if l[:1] in "+-" and not l.startswith(("+++", "---")))


def text_of(arg, row, lane):
    """'pinned' / 'erased' / a path -> (name, text)."""
    if arg in ("pinned", "erased"):
        base = kitlib.base_text(row, lane)
        return arg, base if arg == "pinned" else kitlib.erased_text(base)
    p = Path(arg)
    if not p.is_file():
        raise SystemExit("diff.py: no such file %s (or say 'pinned' / 'erased')" % arg)
    return p.stem, p.read_text(errors="replace")


def run(row, ref_text, cand_text, ctx=3, ref_name="pinned", cand_name="candidate", listing=None):
    """(diff lines or None, distance).  `listing(row, text)` defaults to `screen.compile_s`."""
    if listing is None:
        kitlib.add_paths()
        from screen import compile_s as listing                         # noqa: E402
    lines = render(listing(row, ref_text), listing(row, cand_text), ctx, ref_name, cand_name)
    return lines, distance(lines)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("row_id")
    ap.add_argument("candidate", help="candidate .c, or 'erased' / 'pinned'")
    ap.add_argument("--vs", default="pinned", help="reference: pinned (default), erased, or a .c file")
    ap.add_argument("--ctx", type=int, default=3, help="context lines (default 3)")
    ap.add_argument("--score", action="store_true", help="also byte-score the candidate (journalled)")
    a = ap.parse_args()

    lane = kitlib.bootstrap()
    row = kitlib.row_of(a.row_id)
    ref_name, ref = text_of(a.vs, row, lane)
    cand_name, cand = text_of(a.candidate, row, lane)
    lines, dist = run(row, ref, cand, a.ctx, ref_name, cand_name)
    if lines is None:
        print("DOES NOT BUILD (%s)" % ("the reference" if kitlib.screen_for(row, ref).target is None
                                       else "the candidate"))
    else:
        for l in lines:
            print(l)
        if not lines:
            print("(listings identical)")
    print("%-28s dist %-5s pins %-3s vs %s   [%s]"
          % (cand_name, "-" if dist is None else dist, len(kitlib.sites(cand)), ref_name, row["cfg"]))
    if a.score:
        v = kitlib.score_at(row, cand)
        sc = kitlib.score_fields(v)
        print("%-28s score %s" % (cand_name, json.dumps(sc)))
        kitlib.log_append(lane, {"row": row["id"], "variant": cand_name, "kind": "diff-score",
                                 "distance": dist if ref_name == "pinned" else None, "score": sc,
                                 "status": "exact" if sc.get("exact") else "scored",
                                 "pins": len(kitlib.sites(cand)),
                                 "note": "diff.py --score" + ("" if ref_name == "pinned" else " (dist vs %s)" % ref_name)})


if __name__ == "__main__":
    main()
