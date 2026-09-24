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
CELLS = ["2.6.3", "2.7.2", "2.7.2-cdk", "2.8.0", "2.8.1", "2.91.66", "2.95.2", "mixed"]
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


def physical_units(r):
    """An absent field is a legacy single-stream row, not an empty plural proof."""
    units = r.get("physical_units")
    if units is None:
        return []
    if not isinstance(units, list) or not units:
        raise ValueError(f"{r.get('row')}: physical_units must be nonempty")
    return units


def ownerwise_exact(r):
    units = physical_units(r)
    if units:
        common = set(units[0].get("exact_versions") or [])
        for unit in units[1:]:
            common.intersection_update(unit.get("exact_versions") or [])
        if common != set(r.get("exact_versions") or []):
            raise ValueError(f"{r.get('row')}: common genuine versions disagree with physical units")
    measured = all(bool(unit.get("exact_versions")) for unit in units) if units else bool(r.get("exact_versions"))
    if units and "ownerwise_exact_versions" in r and bool(r["ownerwise_exact_versions"]) != measured:
        raise ValueError(f"{r.get('row')}: ownerwise genuine exactness disagrees with physical units")
    return measured


def dependent_units(r):
    units = physical_units(r)
    return [unit for unit in units if not unit.get("exact_versions")] if units else (
        [r] if not r.get("exact_versions") else [])


def unit_source(unit):
    return unit.get("source") or unit.get("physical_source") or unit.get("c_path") or "?"


def unit_cause(unit):
    if unit.get("exact_versions"):
        return "genuine-exact", []
    if not any("err" not in g for g in (unit.get("genuine") or {}).values()):
        return "genuine ASPSX cannot assemble the input", []
    return cause(unit)


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
    for r in base:
        ownerwise_exact(r)  # fail on inconsistent aggregate/owner claims
    gex = [r for r in base if r.get("exact_versions")]
    ownerwise = [r for r in base if not r.get("exact_versions") and ownerwise_exact(r)]
    dep = [r for r in base if not r.get("exact_versions") and not ownerwise_exact(r)]
    cant = [r for r in dep if any(
        not any("err" not in g for g in (unit.get("genuine") or {}).values())
        for unit in dependent_units(r))]
    P(f"\n**Rows exact under one common genuine ASPSX version: {len(gex)} / {len(base)}** "
      f"({100 * len(gex) / max(1, len(base)):.1f}%); "
      f"ownerwise genuine-exact with no common version: {len(ownerwise)}; "
      f"maspsx-dependent in at least one physical unit: {len(dep)} "
      f"(of which a dependent unit cannot assemble at any version: {len(cant)}).")
    modelled = [r for r in base if any(unit.get("compiler_model") or unit.get("model")
                                     for unit in physical_units(r))]
    if modelled:
        P(f"\nRows with a compiler-modelled physical stream: {len(modelled)}. "
          "Their genuine comparisons are after the named model, not direct unmodelled compiler evidence.")
    P("\nPer version (rows exact / rows assembled):\n")
    P(table(["version"] + VERSIONS,
            [["exact"] + [sum(1 for r in base if v in r.get("exact_versions", [])) for v in VERSIONS],
             ["assembled"] + [sum(1 for r in base if "err" not in (r.get("genuine") or {}).get(v, {"err": 1})) for v in VERSIONS],
             ["%hi/%lo syntax errors"] + [sum(1 for r in base if (r.get("genuine") or {}).get(v, {}).get("err_kind") == "hilo") for v in VERSIONS]]))

    P("\n## Rows exact under genuine ASPSX: container x cell x version\n")
    P("Cell: rows / exact under one COMMON version / ownerwise exact with no common version / "
      "exact per common version 2.56, 2.67, 2.77, 2.79, 2.81, 2.86. "
      "`mixed` means physical owners use different compiler cells.\n")
    rows = []
    for cont in CONTAINERS:
        for cell in CELLS:
            rs = [r for r in base if r["container"] == cont and r.get("cell") == cell]
            if not rs:
                continue
            rows.append([cont, cell, len(rs), sum(1 for r in rs if r.get("exact_versions")),
                         sum(1 for r in rs if r in ownerwise)] +
                        [sum(1 for r in rs if v in r.get("exact_versions", [])) for v in VERSIONS])
        rs = [r for r in base if r["container"] == cont]
        rows.append([f"**{cont}**", "all", len(rs), sum(1 for r in rs if r.get("exact_versions")),
                     sum(1 for r in rs if r in ownerwise)] +
                    [sum(1 for r in rs if v in r.get("exact_versions", [])) for v in VERSIONS])
    rows.append(["**tree**", "all", len(base), len(gex), len(ownerwise)] +
                [sum(1 for r in base if v in r.get("exact_versions", [])) for v in VERSIONS])
    P(table(["container", "cell", "rows", "common any", "ownerwise only"] + VERSIONS, rows))

    P("\n## Version sets (which genuine versions reproduce a row)\n")
    vs = C(",".join(r["exact_versions"]) or
           ("ownerwise, no common version" if r in ownerwise else "none") for r in base)
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
    single_base = [r for r in base if not physical_units(r)]
    single_gex = [r for r in gex if not physical_units(r)]
    if len(single_base) != len(base):
        P(f"Plural rows omitted from single-stream mode and flag statistics: {len(base) - len(single_base)}. "
          "Their effective modes and recipes are in physical_units.tsv.\n")
    divs = [r for r in single_base if r.get("has_div")]
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
    for r in single_gex:
        ms = modes(r)
        if any("-G0" in x for x in ms):
            g0["exact at -G0"] += 1
        elif r.get("cfg", "").find("-G0") >= 0:
            g0["cc1 -G0 but exact only at the default -G8"] += 1
    P(f"\n-G: {g0['exact at -G0']:,} genuine-exact rows were compiled by cc1 at -G0 and are exact with ASPSX `-G0`; "
      f"{g0['cc1 -G0 but exact only at the default -G8']} needed the ASPSX default -G8 instead.")
    n_equ = sum(1 for r in single_gex if modes(r) and all("equ" in x for x in modes(r)))
    P(f"\nC-side numeric address equates (`.set D_X, 0x...`, `D_X = 0x...`): genuine-exact rows that are exact ONLY when "
      f"the equates are assembled as constants (`.equ`), not as externals: {n_equ}. (Modes are tried externals first, "
      f"so a row whose recorded mode says `equ` failed as externals.)")

    physical_lines = []
    for r in base:
        for unit in physical_units(r):
            recipe = unit.get("recipe") or {}
            k, fx = unit_cause(unit)
            physical_lines.append("\t".join(str(x) for x in [
                r["row"], unit_source(unit), unit.get("role") or "-", unit.get("module") or "-",
                json.dumps(recipe, sort_keys=True, separators=(",", ":")),
                ",".join(unit.get("functions") or []),
                ",".join(unit.get("exact_versions") or []) or "-", unit.get("best") or "-",
                k, ",".join(fx) or "-", ",".join(unit.get("fired") or []) or "-",
                ",".join(unit.get("gp_externs") or []) or "-",
                unit.get("compiler_model") or unit.get("model") or "-",
            ]))
    (out / "physical_units.tsv").write_text(
        "# row\tsource\trole\tmodule\trecipe\tfunctions\texact_versions\tbest\tcause\towner_ablations\tfired_whole_unit\tgp_externs\tcompiler_model\n"
        + "\n".join(sorted(physical_lines)) + "\n")

    P("\n## maspsx-dependent rows by the maspsx behaviour that made the difference\n")
    P("For a legacy single-stream row, a listed ablation is a measured row fix. For a partitioned row, "
      "the cause is owner-specific and any ablation is listed only in physical_units.tsv; no owner fix "
      "is promoted to a whole-row fix. `unexplained` means no tested ablation reaches genuine for "
      "that measured unit.\n")
    cz = C(); lines = []; by_cause = collections.defaultdict(list)
    for r in dep:
        plural = bool(physical_units(r))
        if plural:
            owner_causes = sorted({unit_cause(unit)[0] for unit in dependent_units(r)})
            k, fx = "owner-specific: " + "; ".join(owner_causes), []
        elif r in cant:
            k, fx = "genuine ASPSX cannot assemble the input", []
        else:
            k, fx = cause(r)
        cz[k] += 1
        by_cause[k].append(r)
        g = {} if plural else (r.get("genuine") or {}).get(r.get("best"), {})
        lines.append("\t".join(str(x) for x in [r["row"], r["container"], r.get("cfg"), "mixed" if plural else r.get("asflags") or "-", r.get("pins"),
                                                  "owner-specific" if plural else r.get("best"), "-" if plural else g.get("diff"),
                                                  r.get("words"), k, ",".join(fx) or "-",
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
    P("fired = the pass changed a whole physical compilation unit's listing, counted once per logical row; "
      "it may have fired outside that row's scoped functions. Whole-row dependents below exclude owner-only "
      "ablations, which are listed separately in pass_dependents_physical.tsv.\n")
    fired = C(); neutral = C(); owner_neutral = C(); deps = collections.defaultdict(list)
    for r in base:
        for p in r.get("fired") or []:
            fired[p] += 1
            if r.get("exact_versions"):
                neutral[p] += 1
            elif r in ownerwise:
                owner_neutral[p] += 1
    for r in dep:
        if physical_units(r):
            continue
        a = (r.get("attrib") or {}).get(r.get("best")) or {}
        for f in a.get("fix") or []:
            if f.startswith("no:_"):
                deps[f[3:]].append(r["row"])
    plines = [f"{p}\t{rid}" for p in sorted(deps) for rid in sorted(deps[p])]
    for r in dep:
        if physical_units(r):
            continue
        a = (r.get("attrib") or {}).get(r.get("best")) or {}
        if "extern-abs" in (a.get("fix") or []):
            plines.append(f"small-extern-gp\t{r['row']}")
    (out / "pass_dependents.tsv").write_text("# maspsx behaviour\tdependent row\n" + "\n".join(plines) + "\n")
    owner_deps = collections.defaultdict(set)
    for r in dep:
        for unit in dependent_units(r) if physical_units(r) else []:
            a = (unit.get("attrib") or {}).get(unit.get("best")) or {}
            for fix in a.get("fix") or []:
                if fix.startswith("no:_"):
                    owner_deps[fix[3:]].add((r["row"], unit_source(unit)))
                elif fix == "extern-abs":
                    owner_deps["small-extern-gp"].add((r["row"], unit_source(unit)))
    (out / "pass_dependents_physical.tsv").write_text(
        "# maspsx behaviour\tlogical row\tphysical source\tscope\n" +
        "\n".join(f"{p}\t{row}\t{source}\towner-only"
                  for p in sorted(owner_deps) for row, source in sorted(owner_deps[p])) + "\n")
    names = sorted(set(fired) | set(deps) | set(owner_deps),
                   key=lambda p: (-len(deps.get(p, [])), -len(owner_deps.get(p, [])), -fired[p]))
    P(table(["pass / helper", "fired on logical rows", "whole-row dependents", "owner-only rows",
             "fired but common-version exact", "fired but ownerwise exact"],
            [[f"`{p}`", fired[p], len(set(deps.get(p, []))),
              len({row for row, _ in owner_deps.get(p, set())}), neutral[p], owner_neutral[p]]
             for p in names]))

    P("\n## Small-extern `$gp` model (decision 3)\n")
    gp = [r for r in base if r.get("n_gp_externs")]
    fixed = [r for r in gp if not physical_units(r) and
             "extern-abs" in (((r.get("attrib") or {}).get(r.get("best")) or {}).get("fix") or [])]
    owner_fixed = [r for r in gp if physical_units(r) and any(
        "extern-abs" in (((unit.get("attrib") or {}).get(unit.get("best")) or {}).get("fix") or [])
        for unit in dependent_units(r))]
    syms = C()
    for r in gp:
        for s in r.get("gp_externs") or []:
            syms[s] += 1
    P(f"Logical rows with a scoped physical unit that addresses an external symbol through `$gp`: **{len(gp)}** "
      f"({len(syms)} distinct symbols, {sum(r['n_gp_externs'] for r in gp)} unique row-symbol pairs). "
      f"Single-stream rows where withholding `.extern` sizes alone reaches genuine: {len(fixed)}; "
      f"plural rows with that result for at least one owner only: {len(owner_fixed)}. "
      "The latter is not a measured whole-row repair; owner symbols and causes are in physical_units.tsv.\n")
    P(table(["container", "cell", "rows", "single-stream extern-abs fixes", "owner-only extern-abs rows"],
            [[c, cl, n, sum(1 for r in fixed if r["container"] == c and r.get("cell") == cl),
              sum(1 for r in owner_fixed if r["container"] == c and r.get("cell") == cl)]
             for (c, cl), n in sorted(C((r["container"], r.get("cell")) for r in gp).items())]))
    (out / "gp_extern_rows.tsv").write_text("# row\tcfg\tpins\tn_gp_externs\tsymbols\n" + "\n".join(
        f"{r['row']}\t{r.get('cfg')}\t{r.get('pins')}\t{r['n_gp_externs']}\t{','.join(r.get('gp_externs') or [])}"
        for r in sorted(gp, key=lambda r: r["row"])) + "\n")
    P("\nMost-shared symbols: " + ", ".join(f"{s} ({n})" for s, n in syms.most_common(12)))

    P("\n## Difference classes (maspsx vs the closest genuine version, maspsx-dependent rows)\n")
    cls = C()
    for r in dep:
        keys = set((r.get("classes") or {}).keys())
        for unit in physical_units(r):
            keys.update((unit.get("classes") or {}).keys())
        for k in keys:
            cls[k] += 1
    P(table(["class", "rows"], cls.most_common()))
    P("\n## Pins\n")
    P(table(["", "rows", "pin-free rows", "pins"],
            [["genuine-exact", len(gex), sum(1 for r in gex if not r.get("pins")), sum(r.get("pins") or 0 for r in gex)],
             ["ownerwise exact, no common version", len(ownerwise), sum(1 for r in ownerwise if not r.get("pins")),
              sum(r.get("pins") or 0 for r in ownerwise)],
             ["maspsx-dependent", len(dep), sum(1 for r in dep if not r.get("pins")), sum(r.get("pins") or 0 for r in dep)]]))


if __name__ == "__main__":
    main()
