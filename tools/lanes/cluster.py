#!/usr/bin/env python3
"""Pin clusters of a big row: 3-5 sites that plausibly fall together, for a CLUSTER pack (round 76).

    python3 tools/lanes/cluster.py dungeon/func_8132E2FC [--size 3-5] [--near 25] [--top 5]

Why.  Rows with 8+ pins (128 rows, 1,691 pins on 2026-09-23) fail as whole functions: gpt-6-astra went 0/5 on
rows with 11+ pins of residue, while the r75_astra_p* packs, which accepted partial landings, took 30 pins to 15.
A cluster pack (tools/lanes/build_class_pack.py --rows ... --cluster 3-5) briefs a lane on ONE cluster and asks for
a partial landing - the other pins stay - so the residue is a new text and is served again later (the tier guard of
tools/lanes/served.py keys a serve on the text sha AND the cluster, so re-serving is by design).

How a cluster is chosen (pure, unit tested; sites are tools/pin_census.sites_of tuples
(kind, macro, arg, start, end, line_no, repl)):
  1. same-variable groups (the pinned variable: KEEP/USE argument, or the REG declaration's name; the
     tools/lanes/joint_scan.py rule "pins that hold one mechanism fall only together") - cut to --size by
     line proximity, or grown to it with the nearest other sites within --near lines;
  2. line windows: every run of consecutive sites (by line) of a size in --size spanning at most --near lines.
Ranked: variable groups first, then the smaller mean line gap (span / (size - 1)), then the larger size, then the
earlier line.  The
k-th best is `--cluster-rank k` in build_class_pack.py, so successive packs can take different clusters.
"""
import argparse
import sys
from pathlib import Path


def var_of(site):
    """The pinned variable (joint_scan.var_of, repeated here to avoid importing the cell-scan machinery)."""
    kind, arg = site[0], site[2]
    if kind == "reg" and len(site) > 6 and site[6]:
        return site[6].replace("*", " ").split()[-1]
    return arg


def _span(sites, idx):
    lines = [sites[i][5] for i in idx]
    return max(lines) - min(lines)


def pick_clusters(sites, kmin=3, kmax=5, near=25):
    """Ranked [(idx tuple, reason)] of clusters of kmin..kmax sites; [] when the row has fewer than kmin."""
    n = len(sites)
    if n < kmin:
        return []
    order = sorted(range(n), key=lambda i: (sites[i][5], sites[i][3]))
    cands = {}

    def add(idx, var_based, why):
        idx = tuple(sorted(set(idx)))
        if not (kmin <= len(idx) <= kmax):
            return
        key = (0 if var_based else 1, round(_span(sites, idx) / (len(idx) - 1), 3), -len(idx),
               min(sites[i][5] for i in idx))
        if idx not in cands or key < cands[idx][0]:
            cands[idx] = (key, why)

    groups = {}
    for i in order:
        groups.setdefault(var_of(sites[i]), []).append(i)
    for var, g in groups.items():
        if len(g) < 2 or not var:                          # argless pins (SCHED_BARRIER) share no variable
            continue
        if len(g) > kmax:                                  # cut: the tightest windows of kmax
            for j in range(len(g) - kmax + 1):
                w = g[j:j + kmax]
                if _span(sites, w) <= near:
                    add(w, True, "same variable `%s`" % var)
        elif len(g) >= kmin:
            if _span(sites, g) <= near:
                add(g, True, "same variable `%s`" % var)
        else:                                              # grow with the nearest other sites
            rest = sorted((i for i in range(n) if i not in g),
                          key=lambda i: min(abs(sites[i][5] - sites[j][5]) for j in g))
            grown = list(g)
            for i in rest:
                if len(grown) >= kmin:
                    break
                if min(abs(sites[i][5] - sites[j][5]) for j in grown) <= near:
                    grown.append(i)
            if len(grown) >= kmin and _span(sites, grown) <= near:
                add(grown, True, "same variable `%s` + nearest sites" % var)
    for size in range(kmin, kmax + 1):
        for j in range(n - size + 1):
            w = order[j:j + size]
            if _span(sites, w) <= near:
                add(w, False, "%d consecutive sites within %d lines" % (size, _span(sites, w)))
    if not cands:                                          # nothing within --near: the tightest kmin window
        best = min((order[j:j + kmin] for j in range(n - kmin + 1)), key=lambda w: _span(sites, w))
        add(best, False, "tightest %d sites (%d lines; none within --near)" % (kmin, _span(sites, best)))
    return [(idx, why) for idx, (key, why) in sorted(cands.items(), key=lambda kv: kv[1][0])]


def disjoint(ranked):
    """The ranked clusters with no site shared with a better-ranked one (successive packs of one row)."""
    used, out = set(), []
    for idx, why in ranked:
        if used.isdisjoint(idx):
            out.append((idx, why))
            used |= set(idx)
    return out


def main(argv=None):
    root = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
    sys.path.insert(0, str(root / "tools"))
    from common import rows, clean_path
    from pin_census import sites_of
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("row")
    ap.add_argument("--size", default="3-5")
    ap.add_argument("--near", type=int, default=25)
    ap.add_argument("--top", type=int, default=5)
    a = ap.parse_args(argv)
    kmin, kmax = (int(x) for x in (a.size.split("-") + a.size.split("-"))[:2])
    r = {x["id"]: x for x in rows()}[a.row]
    sites = sites_of(clean_path(r).read_text(errors="replace"))
    print("%s: %d pins" % (a.row, len(sites)))
    for k, (idx, why) in enumerate(disjoint(pick_clusters(sites, kmin, kmax, a.near))[:a.top]):
        print("  rank %d  %s  --  %s" % (k, ", ".join("%s(%s)@%d" % (sites[i][1], sites[i][2], sites[i][5]) for i in idx), why))
    return 0


if __name__ == "__main__":
    sys.exit(main())
