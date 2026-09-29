#!/usr/bin/env python3
"""prio.py - the global-allocation priority table of ONE text at a cfg: who outranks whom, and who got what.

    cd work/native_lane/<lane>
    python3 <KIT>/prio.py <row> <candidate.c|pinned|erased> [--cfg CFG] [--top N] [--all]

Register-allocation rows end at "which allocno comes first in `global.c allocno_compare`?".  Round-80
lane `r80_cell_c1b` answered that with a private `prio.py` (dump, regex the `.lreg`/`.greg`, compute
`floor_log2(refs) * refs / live * 10000`); `why.py --pass greg` compares TWO texts, this prints ONE
(a candidate at a foreign cell, where there is no pinned text to compare with).

One `-da` compile (`kitlib.dumps`, at `--cfg` when given: this compile only, nothing written), then per
allocno, in the order `global.c` allocates them: pseudo, the C variable it is (when `alloc_sim` can
name it), refs, live length, calls crossed, floor_log2(refs), the priority
(`alloc_sim.priority`, int truncation of the double - the same number `allocno_compare` sorts on) and
the hard register the `.greg` dispositions give it.  `--all` also lists the local-allocation pseudos
(`in block` in the `.lreg`), which never reach global.c.  `computed order` = the rank the priority
alone gives (descending, ties by pseudo); it is flagged `!` where the dump's own allocno order
disagrees (size/quantity effects the formula here does not model).
"""
from __future__ import annotations

import argparse
import math
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import kitlib                                                             # noqa: E402

HEAD = ["rank", "pseudo", "variable", "refs", "live", "calls", "floor_log2", "priority", "computed", "got"]


def floor_log2(n):
    return 0 if n <= 0 else int(math.floor(math.log2(n)))


def priority_rows(lreg, greg, names=None, sim=None, include_local=False):
    """[[rank, pseudo, name, refs, live, calls, floor_log2, priority, computed-order, got]] from `-da`
    `.lreg` / `.greg` text.

    `rank` is the dump's allocno order (the `;; N regs to allocate` list); allocnos not in it (local
    pseudos, `in block`) follow, marked rank `-`, and only with `include_local`.  `names` is
    {pseudo: variable}.  `sim` is `alloc_sim` (injected by the tests)."""
    if sim is None:
        kitlib.add_paths()
        import alloc_sim as sim                                          # noqa: E402
    names = names or {}
    order, disp = sim.parse_greg(greg)
    stats = sim.parse_lreg(lreg)
    local = {p for p, st in stats.items() if "in block" in st.get("note", "")}
    rows = []
    for p in order:
        st = stats.get(p, {})
        rows.append((p, st.get("n_refs", 0), st.get("live_length", -1), st.get("calls_crossed", 0)))
    ranked = {p for p in order}
    if include_local or not order:
        for p in sorted(stats):
            if p not in ranked and (include_local or p not in local):
                st = stats[p]
                rows.append((p, st["n_refs"], st["live_length"], st["calls_crossed"]))
    prio = {p: sim.priority(n, L) for p, n, L, _ in rows}
    pool = [p for p, *_ in rows if p in ranked] or [p for p, *_ in rows]
    comp = {p: i for i, p in enumerate(sorted(pool, key=lambda q: (-prio[q], q)))}   # among the allocnos only
    out = []
    for i, (p, n, L, c) in enumerate(rows):
        hard = disp.get(p)
        got = sim.reg_name(hard) if hard is not None and hard >= 0 else ("spilled" if p in disp or p in ranked else "-")
        rank = i if p in ranked else "-"
        flag = "!" if rank != "-" and comp[p] != rank else ""
        out.append([rank, p, names.get(p, ""), n, L, c, floor_log2(n), prio[p],
                    "%d%s" % (comp[p], flag) if p in comp else "-", got])
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("row_id")
    ap.add_argument("text", help="candidate .c, or 'pinned' / 'erased'")
    ap.add_argument("--cfg", help="compile at this cfg instead of the row's (this compile only)")
    ap.add_argument("--top", type=int, default=40, help="most allocnos to print (default 40)")
    ap.add_argument("--all", action="store_true", help="include local-allocation pseudos")
    a = ap.parse_args(argv)

    lane = kitlib.bootstrap()
    row = kitlib.row_of(a.row_id)
    if a.text in ("pinned", "erased"):
        base = kitlib.base_text(row, lane)
        stem, text = a.text, base if a.text == "pinned" else kitlib.erased_text(base)
    else:
        p = Path(a.text)
        if not p.is_file():
            raise SystemExit("prio.py: no such file %s (or say 'pinned' / 'erased')" % p)
        stem, text = p.stem, p.read_text(errors="replace")
    rowc = kitlib.row_at_cfg(row, a.cfg)
    d = kitlib.dumps(rowc, text, want={"greg", "lreg"})
    if d is None or d.get("error"):
        raise SystemExit("prio.py: DOES NOT BUILD at %s\n%s" % (rowc["cfg"], (d or {}).get("error") or ""))
    if "greg" not in d or "lreg" not in d:
        raise SystemExit("prio.py: this recipe produced no .greg/.lreg dump")
    kitlib.add_paths()
    import alloc_sim                                                     # noqa: E402
    from common import parse_cfg                                         # noqa: E402
    fp = alloc_sim.FIRST.get(parse_cfg(rowc["cfg"])[0])
    dp = alloc_sim.decl_pseudos(text, fp) if fp else None
    names = {v: k for k, v in ((dp or {}).get("map") or {}).items()}
    rows = priority_rows(d["lreg"], d["greg"], names, alloc_sim, include_local=a.all)
    print("# prio %s  %s at %s   (global.c allocno_compare: floor_log2(refs) * refs / live * 10000)"
          % (row["id"], stem, rowc["cfg"]))
    if fp is None:
        print("# (alloc_sim.FIRST has no FIRST_PSEUDO_REGISTER for this cell: variable names unavailable)")
    print(kitlib.fmt_table(HEAD, rows[:a.top]))
    if len(rows) > a.top:
        print("   ... %d more (raise --top)" % (len(rows) - a.top))


if __name__ == "__main__":
    main()
