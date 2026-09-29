#!/usr/bin/env python3
"""regcmp.py - how many NAMED variables land in a different register than in a reference text.

    cd work/native_lane/<lane>
    python3 <KIT>/regcmp.py <row> <candidate.c> [--ref ref.c] [--cfg CFG]
    python3 <KIT>/regcmp.py <row> <candidate.c> --subsets [--max-pins 8] [--top 12]

On a big register-allocation row the listing distance is a coarse progress measure: one moved
allocno shifts dozens of lines.  Round-80 lane `r80_opus_r2` ranked candidates instead by the number
of C variables (the ones `alloc_sim` can name) whose hard register differs from the reference text's
(`pcmp.py`), and ran every subset of pin removals through that count (`combo.py`).  This is both,
on `prio.py`'s table (`prio.priority_rows`), in-process.

Default reference = the row's current src text (`kitlib.base_text`, the pinned/retail-shaped one).  Every
mismatching variable prints as `name: was -> now (refs/live=priority)`, then the count.  Temporaries
that have no C name are ignored: their pseudo numbers move with every edit.

`--subsets` erases every subset of the candidate's LIVE pins (`kitlib.sites` / `kitlib.erase`, the
helpers `erase.py` uses; at most `--max-pins` sites, else it refuses - 2^n compiles), ranks each erased
text by the same count (fewest first, then fewest pins erased) and writes the texts to `regcmp/` in the
lane.  One `-da` compile per subset, nothing else is written and no ledger is touched.
"""
from __future__ import annotations

import argparse
import itertools
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import kitlib                                                             # noqa: E402
import prio                                                               # noqa: E402

MAX_PINS = 8
NO_BUILD = 10 ** 6


def reg_table(rows):
    """{variable: (refs, live, priority, got)} from `prio.priority_rows` output; unnamed pseudos dropped."""
    return {r[2]: (r[3], r[4], r[7], r[9]) for r in rows if r[2]}


def mismatches(ref, cand):
    """[(name, ref_reg, cand_reg, refs, live, priority)] for variables in BOTH tables with different
    registers, sorted by name.  A variable missing from either table is not counted (renamed/erased)."""
    return [(k, ref[k][3], v[3], v[0], v[1], v[2])
            for k, v in sorted(cand.items()) if k in ref and ref[k][3] != v[3]]


def fmt_mismatch(m):
    return "%s: %s -> %s (%d/%d=%d)" % m


def table_of(row, text, cfg=None):
    """The named-variable register table of `text` compiled at `cfg` (default: the row's own), or None."""
    rowc = kitlib.row_at_cfg(row, cfg)
    d = kitlib.dumps(rowc, text, want={"greg", "lreg"})
    if d is None or d.get("error") or "greg" not in d or "lreg" not in d:
        return None
    kitlib.add_paths()
    import alloc_sim                                                     # noqa: E402
    from common import parse_cfg                                         # noqa: E402
    fp = alloc_sim.FIRST.get(parse_cfg(rowc["cfg"])[0])
    dp = alloc_sim.decl_pseudos(text, fp) if fp else None
    names = {v: k for k, v in ((dp or {}).get("map") or {}).items()}
    return reg_table(prio.priority_rows(d["lreg"], d["greg"], names, alloc_sim))


def subset_indices(n):
    """Every subset of range(n) as a tuple, smallest first (the empty subset = erase nothing)."""
    return [c for r in range(n + 1) for c in itertools.combinations(range(n), r)]


def rank_subsets(results):
    """[(bad_count, erased_count, idx, mismatch_list)] sorted: fewest mismatches, then fewest pins erased."""
    return sorted(results, key=lambda r: (r[0], r[1], r[2]))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("row_id")
    ap.add_argument("candidate")
    ap.add_argument("--ref", help="reference text (default: the row's current src text)")
    ap.add_argument("--cfg", help="compile at this cfg instead of the row's")
    ap.add_argument("--subsets", action="store_true", help="rank every subset of the candidate's pin removals")
    ap.add_argument("--max-pins", type=int, default=MAX_PINS, help="most pin sites --subsets accepts (2^n compiles)")
    ap.add_argument("--top", type=int, default=12, help="subsets to print (default 12)")
    a = ap.parse_args(argv)

    lane = kitlib.bootstrap()
    row = kitlib.row_of(a.row_id)
    cpath = Path(a.candidate)
    if not cpath.is_file():
        raise SystemExit("regcmp.py: no such file %s" % cpath)
    text = cpath.read_text(errors="replace")
    if a.ref:
        if not Path(a.ref).is_file():
            raise SystemExit("regcmp.py: no such file %s" % a.ref)
        reftext = Path(a.ref).read_text(errors="replace")
    else:
        reftext = kitlib.base_text(row, lane)
    ref = table_of(row, reftext, a.cfg)
    if ref is None:
        raise SystemExit("regcmp.py: the reference does not build (or made no .greg/.lreg dump)")

    if not a.subsets:
        cand = table_of(row, text, a.cfg)
        if cand is None:
            raise SystemExit("regcmp.py: %s DOES NOT BUILD" % cpath.name)
        bad = mismatches(ref, cand)
        print("# regcmp %s  %s vs %s" % (row["id"], cpath.name, a.ref or "src text"))
        for m in bad:
            print("  " + fmt_mismatch(m))
        print("%d variable(s) in a different register (%d compared)" % (len(bad), len(set(ref) & set(cand))))
        return

    sites = kitlib.sites(text)
    if len(sites) > a.max_pins:
        raise SystemExit("regcmp.py --subsets: %d pin sites = 2^%d compiles; raise --max-pins to insist"
                         % (len(sites), len(sites)))
    out = lane / "regcmp"
    out.mkdir(parents=True, exist_ok=True)
    res = []
    for idx in subset_indices(len(sites)):
        t = kitlib.erase(text, [sites[i] for i in idx]) if idx else text
        (out / ("%s_%s.c" % (cpath.stem, "_".join(map(str, idx)) or "none"))).write_text(t)
        cand = table_of(row, t, a.cfg)
        ms = mismatches(ref, cand) if cand is not None else None
        res.append((len(ms) if ms is not None else NO_BUILD, len(idx), idx, ms))
    print("# regcmp --subsets %s  %s: %d pin sites, %d subsets" % (row["id"], cpath.name, len(sites), len(res)))
    for bad, n, idx, ms in rank_subsets(res)[:a.top]:
        what = "does not build" if ms is None else " ".join(m[0] for m in ms)
        print("%s  erase[%s]  %s" % ("X" if ms is None else bad, ",".join(map(str, idx)) or "-", what))


if __name__ == "__main__":
    main()
