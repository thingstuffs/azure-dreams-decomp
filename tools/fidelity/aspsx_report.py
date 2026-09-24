#!/usr/bin/env python3
"""Tables for docs/evidence/fidelity_step1_aspsx_diff.md from the genuine-ASPSX differential journal
(work/fidelity/aspsx_diff.jsonl, written by tools/fidelity/aspsx_diff.py), plus the list files:

  work/fidelity/maspsx_dependent.tsv   rows exact through maspsx, under NO genuine ASPSX version
  work/fidelity/pass_dependents.tsv    one line per (maspsx behaviour, dependent row)
  work/fidelity/gp_extern_rows.tsv     rows whose retail bytes $gp-address a symbol the TU does not define

    python3 tools/fidelity/aspsx_report.py [--journal PATH] [--out-dir work/fidelity] > tables.md
"""
import argparse
import collections
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
VERSIONS = ["2.56", "2.67", "2.77", "2.79", "2.81", "2.86"]
CONTAINERS = ["slus", "main", "town", "dungeon", "ovmovie"]
CELLS = ["2.6.3", "2.7.2", "2.7.2-cdk", "2.8.0", "2.8.1", "2.91.66", "2.95.2"]
C = collections.Counter


def table(head, rows):
    out = ["| " + " | ".join(head) + " |", "|" + "|".join("---" for _ in head) + "|"]
    out += ["| " + " | ".join(str(x) for x in r) + " |" for r in rows]
    return "\n".join(out)


def cause(r):
    """The maspsx behaviour a maspsx-dependent row needs, at its closest genuine version."""
    a = (r.get("attrib") or {}).get(r.get("best")) or {}
    fx = a.get("fix") or []
    if not fx:
        return "unexplained", fx
    singles = [f for f in fx if "+" not in f]
    pick = None
    for pref in ("no:_", "extern-abs", "drop:", "asv:", "no:all-fired"):
        pick = next((f for f in singles if f.startswith(pref)), None)
        if pick:
            break
    pick = pick or fx[0]
    if pick == "no:all-fired":
        return "several passes jointly: " + "+".join(r.get("fired") or []), fx
    if pick.startswith("no:"):
        return pick[3:], fx
    if pick == "extern-abs":
        return "small-extern $gp model (.extern sizes)", fx
    if pick.startswith("drop:"):
        return "row dial " + pick[5:], fx
    if pick.startswith("asv:"):
        return "maspsx --aspsx-version config " + pick[4:], fx
    return "combined: " + pick, fx


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--journal", default=str(ROOT / "work/fidelity/aspsx_diff.jsonl"))
    ap.add_argument("--out-dir", default=str(ROOT / "work/fidelity"))
    a = ap.parse_args()
    recs = [json.loads(l) for l in Path(a.journal).read_text().splitlines() if l.strip()]
    ok = [r for r in recs if r.get("status") == "ok"]
    out = Path(a.out_dir)
    P = print

    P("## Run\n")
    P(table(["records", "ok", "harness/compile errors", "maspsx leg exact (scorer / pinned object)", "self-check (traced maspsx = pipeline object)",
             "maspsx leg resolved against retail: 0 differing words"],
            [[len(recs), len(ok), len(recs) - len(ok), sum(1 for r in ok if r.get("maspsx_exact")),
              sum(1 for r in ok if r.get("selfcheck")), sum(1 for r in ok if (r.get("maspsx_retail") or {}).get("diff") == 0)]]))
    errs = C((r.get("err") or "")[:60] for r in recs if r.get("status") != "ok")
    if errs:
        P("\nErrors: " + "; ".join(f"{k} x{v}" for k, v in errs.most_common(8)))
    notex = [r["row"] for r in ok if not r.get("maspsx_exact")]
    if notex:
        P(f"\nmaspsx leg NOT exact ({len(notex)}; excluded from the fidelity counts): " + ", ".join(notex[:20]))
    base = [r for r in ok if r.get("maspsx_exact")]
    gex = [r for r in base if r.get("exact_versions")]
    dep = [r for r in base if not r.get("exact_versions")]
    cant = [r for r in dep if not any("err" not in g for g in (r.get("genuine") or {}).values())]
    P(f"\n**Rows exact under some genuine ASPSX: {len(gex)} / {len(base)}** ({100 * len(gex) / max(1, len(base)):.1f}%); "
      f"maspsx-dependent: {len(dep)} (of which genuine ASPSX cannot assemble the input at any version: {len(cant)}).")
    P("\nPer version (rows exact / rows assembled):\n")
    P(table(["version"] + VERSIONS,
            [["exact"] + [sum(1 for r in base if v in r.get("exact_versions", [])) for v in VERSIONS],
             ["assembled"] + [sum(1 for r in base if "err" not in (r.get("genuine") or {}).get(v, {"err": 1})) for v in VERSIONS],
             ["%hi/%lo syntax errors"] + [sum(1 for r in base if (r.get("genuine") or {}).get(v, {}).get("err_kind") == "hilo") for v in VERSIONS]]))

    P("\n## Rows exact under genuine ASPSX: container x cell x version\n")
    P("Cell: rows / exact under ANY version / exact per version 2.56, 2.67, 2.77, 2.79, 2.81, 2.86.\n")
    rows = []
    for cont in CONTAINERS:
        for cell in CELLS:
            rs = [r for r in base if r["container"] == cont and r.get("cell") == cell]
            if not rs:
                continue
            rows.append([cont, cell, len(rs), sum(1 for r in rs if r.get("exact_versions"))] +
                        [sum(1 for r in rs if v in r.get("exact_versions", [])) for v in VERSIONS])
        rs = [r for r in base if r["container"] == cont]
        rows.append([f"**{cont}**", "all", len(rs), sum(1 for r in rs if r.get("exact_versions"))] +
                    [sum(1 for r in rs if v in r.get("exact_versions", [])) for v in VERSIONS])
    rows.append(["**tree**", "all", len(base), len(gex)] + [sum(1 for r in base if v in r.get("exact_versions", [])) for v in VERSIONS])
    P(table(["container", "cell", "rows", "any"] + VERSIONS, rows))

    P("\n## Version sets (which genuine versions reproduce a row)\n")
    vs = C(",".join(r["exact_versions"]) or "none" for r in base)
    P(table(["exact under", "rows"], [[k.replace(",", ", ") if k != ",".join(VERSIONS) else "all six", v] for k, v in vs.most_common(12)]))
    P("\nOne global version per container (rows exact under that version / rows exact under ANY version):\n")
    rows = []
    for cont in CONTAINERS + ["tree"]:
        rs = [r for r in gex if cont == "tree" or r["container"] == cont]
        if not rs:
            continue
        rows.append([cont, len(rs)] + [sum(1 for r in rs if v in r["exact_versions"]) for v in VERSIONS] +
                    [sum(1 for r in rs if r["exact_versions"] == ["2.56"])])
    P(table(["container", "genuine-exact rows"] + VERSIONS + ["only 2.56"], rows))
    by_cell = collections.defaultdict(C)
    for r in gex:
        by_cell[r.get("cell")]["2.56" in r["exact_versions"]] += 1
    P("\nGenuine-exact rows that 2.56 also reproduces, by cell: " + ", ".join(
        f"{c} {by_cell[c][True]}/{by_cell[c][True] + by_cell[c][False]}" for c in CELLS if c in by_cell))

    P("\n## The -0 switch (unchecked div) and -G\n")
    divs = [r for r in base if r.get("has_div")]
    def modes(r):
        return {(r["genuine"][v].get("mode") or "") for v in r.get("exact_versions", [])}
    rows = []
    for tag, rs in (("--expand-div rows", [r for r in divs if "--expand-div" in (r.get("asflags") or "")]),
                    ("other div rows", [r for r in divs if "--expand-div" not in (r.get("asflags") or "")])):
        m = C()
        for r in rs:
            ms = modes(r)
            m["not genuine-exact" if not ms else "exact with -0" if all("-0" in x for x in ms) else
              "exact without -0" if all("-0" not in x for x in ms) else "either"] += 1
        rows.append([tag, len(rs), m["exact with -0"], m["exact without -0"], m["either"], m["not genuine-exact"]])
    P(table(["rows with div/rem", "rows", "exact only with -0", "exact only without -0", "either", "not genuine-exact"], rows))
    g0 = C()
    for r in gex:
        ms = modes(r)
        if any("-G0" in x for x in ms):
            g0["exact at -G0"] += 1
        elif r.get("cfg", "").find("-G0") >= 0:
            g0["cc1 -G0 but exact only at the default -G8"] += 1
    P(f"\n-G: {g0['exact at -G0']:,} genuine-exact rows were compiled by cc1 at -G0 and are exact with ASPSX `-G0`; "
      f"{g0['cc1 -G0 but exact only at the default -G8']} needed the ASPSX default -G8 instead.")
    n_equ = sum(1 for r in gex if modes(r) and all("equ" in x for x in modes(r)))
    P(f"\nC-side numeric address equates (`.set D_X, 0x...`, `D_X = 0x...`): genuine-exact rows that are exact ONLY when "
      f"the equates are assembled as constants (`.equ`), not as externals: {n_equ}. (Modes are tried externals first, "
      f"so a row whose recorded mode says `equ` failed as externals.)")

    P("\n## maspsx-dependent rows by the maspsx behaviour that made the difference\n")
    P("Attributed at each row's closest genuine version: the maspsx leg is re-run with one behaviour removed; the "
      "behaviour whose removal makes maspsx == genuine ASPSX is the cause. `unexplained` = no single or combined "
      "ablation reaches genuine.\n")
    cz = C(); lines = []; by_cause = collections.defaultdict(list)
    for r in dep:
        if r in cant:
            k, fx = "genuine ASPSX cannot assemble the input", []
        else:
            k, fx = cause(r)
        cz[k] += 1
        by_cause[k].append(r)
        g = (r.get("genuine") or {}).get(r.get("best"), {})
        lines.append("\t".join(str(x) for x in [r["row"], r["container"], r.get("cfg"), r.get("asflags") or "-", r.get("pins"),
                                                  r.get("best"), g.get("diff"), r.get("words"), k, ",".join(fx) or "-",
                                                  ",".join(f"{a}:{b}" for a, b in (r.get("classes") or {}).items()) or "-"]))
    (out / "maspsx_dependent.tsv").write_text("# row\tcontainer\tcfg\tasflags\tpins\tclosest_version\tdiff_words\twords\tcause\tablations_that_fix\tdiff_classes\n"
                                             + "\n".join(sorted(lines)) + "\n")
    rows = []
    for k, n in cz.most_common():
        rs = by_cause[k]
        rows.append([k, n, sum(1 for r in rs if (r.get("pins") or 0) == 0), sum(r.get("pins") or 0 for r in rs),
                     ", ".join(f"{c} {v}" for c, v in C(r["container"] for r in rs).most_common()),
                     ", ".join(f"{c} {v}" for c, v in C(r.get("cell") for r in rs).most_common(4))])
    P(table(["cause", "rows", "pin-free", "pins in these rows", "containers", "cells"], rows))

    P("\n## maspsx post-passes and helpers: where they fire, and who depends on them\n")
    P("fired = the pass changed maspsx's listing for the row; dependents = rows whose ONLY route to genuine ASPSX "
      "is removing this behaviour (its single ablation makes maspsx == genuine); neutral = fired on a row that some "
      "genuine version still reproduces (the pass imitates genuine ASPSX there, or its change is undone downstream).\n")
    fired = C(); neutral = C(); deps = collections.defaultdict(list)
    for r in base:
        for p in r.get("fired") or []:
            fired[p] += 1
            if r.get("exact_versions"):
                neutral[p] += 1
    for r in dep:
        a = (r.get("attrib") or {}).get(r.get("best")) or {}
        for f in a.get("fix") or []:
            if f.startswith("no:_"):
                deps[f[3:]].append(r["row"])
    plines = [f"{p}\t{rid}" for p in sorted(deps) for rid in sorted(deps[p])]
    for r in dep:
        a = (r.get("attrib") or {}).get(r.get("best")) or {}
        if "extern-abs" in (a.get("fix") or []):
            plines.append(f"small-extern-gp\t{r['row']}")
    (out / "pass_dependents.tsv").write_text("# maspsx behaviour\tdependent row\n" + "\n".join(plines) + "\n")
    names = sorted(set(fired) | set(deps), key=lambda p: (-len(deps.get(p, [])), -fired[p]))
    P(table(["pass / helper", "fired on rows", "dependents", "fired but genuine-exact"],
            [[f"`{p}`", fired[p], len(deps.get(p, [])), neutral[p]] for p in names]))

    P("\n## Small-extern `$gp` model (decision 3)\n")
    gp = [r for r in base if r.get("n_gp_externs")]
    fixed = [r for r in gp if "extern-abs" in (((r.get("attrib") or {}).get(r.get("best")) or {}).get("fix") or [])]
    syms = C()
    for r in gp:
        for s in r.get("gp_externs") or []:
            syms[s] += 1
    P(f"Rows whose maspsx object (= retail) addresses a symbol the TU does NOT define through `$gp`: **{len(gp)}** "
      f"({len(syms)} distinct symbols, {sum(r['n_gp_externs'] for r in gp)} row-symbol pairs). Genuine ASPSX 2.56-2.86 "
      f"never does this (every `.extern` absolute, `-G` included); so each of these rows is maspsx-dependent unless its TU "
      f"defines the symbol. Rows where withholding the `.extern` sizes alone makes maspsx == genuine: {len(fixed)}.\n")
    P(table(["container", "cell", "rows", "extern-abs alone reaches genuine"],
            [[c, cl, n, sum(1 for r in fixed if r["container"] == c and r.get("cell") == cl)]
             for (c, cl), n in sorted(C((r["container"], r.get("cell")) for r in gp).items())]))
    (out / "gp_extern_rows.tsv").write_text("# row\tcfg\tpins\tn_gp_externs\tsymbols\n" + "\n".join(
        f"{r['row']}\t{r.get('cfg')}\t{r.get('pins')}\t{r['n_gp_externs']}\t{','.join(r.get('gp_externs') or [])}"
        for r in sorted(gp, key=lambda r: r["row"])) + "\n")
    P("\nMost-shared symbols: " + ", ".join(f"{s} ({n})" for s, n in syms.most_common(12)))

    P("\n## Difference classes (maspsx vs the closest genuine version, maspsx-dependent rows)\n")
    cls = C()
    for r in dep:
        for k, v in (r.get("classes") or {}).items():
            cls[k] += 1
    P(table(["class", "rows"], cls.most_common()))
    P("\n## Pins\n")
    P(table(["", "rows", "pin-free rows", "pins"],
            [["genuine-exact", len(gex), sum(1 for r in gex if not r.get("pins")), sum(r.get("pins") or 0 for r in gex)],
             ["maspsx-dependent", len(dep), sum(1 for r in dep if not r.get("pins")), sum(r.get("pins") or 0 for r in dep)]]))


if __name__ == "__main__":
    main()
