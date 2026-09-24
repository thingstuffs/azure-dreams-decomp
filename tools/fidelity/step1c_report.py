#!/usr/bin/env python3
"""Toolchain fidelity STEP 1c: tables for every held cc1 run through epilogue_model's psyq leg (measurement only).

Brief: work/fidelity/STEP1C_BRIEF.md; report: docs/evidence/fidelity_step1c_compiler_inventory.md.
Runner: work/fidelity/step1c/run_all.sh (one journal per compiler, work/fidelity/step1c/<label>.jsonl).

For each compiler: rows run / errors; the cc1 body twin rate against our cell's cc1 (`psyq_s_equal`: identical
`.ent`..`.end` bodies, comments dropped) per cell; the return forms it emits (`psyq_epi`: filled noreorder
`j $31 / addu $sp` vs reorder-mode text epilogue, in functions saving a register besides $31); and the genuine
ASPSX 2.79 leg against retail (the row's retail-exact maspsx object) as emitted (`psyq`) and after gcc 2.7.2's
epilogue rule (`psyq_t272`), next to our cell's cc1 (`base`, `t272`).

    python3 tools/fidelity/step1c_report.py [label ...]
"""
from __future__ import annotations

import json
import sys
from collections import Counter, defaultdict
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(HERE))
D = ROOT / "work/fidelity/step1c"
ORDER = ["sn280jp43", "trunk970802", "trunk970821", "trunk971023", "psyq41_full", "cdk_full", "psyq40", "psyq41",
         "sn16", "sn1", "gcc257",
         "gcc260", "s3040"]
CELLS_2X = ("2.8.0", "2.8.1", "2.91.66", "2.95.2")


def load(p):
    out = {}
    for l in p.read_text().splitlines():
        if l.strip():
            r = json.loads(l); out[r["row"]] = r
    return out


def exact(r, tag, ver="2.79"):
    x = dict((r.get("res") or {}).get(tag) or {})
    x.pop("same_as_input", None)
    v = x.get(ver)
    return bool(v and v.get("exact"))


def groups():
    dep = {}
    for l in (ROOT / "docs/evidence/fidelity_step1_maspsx_dependent.tsv").read_text().splitlines()[1:]:
        p = l.split("\t"); dep[p[0]] = p[8]
    step1 = load(ROOT / "work/fidelity/aspsx_diff.jsonl")

    def grp(r):
        if r["cell"] not in CELLS_2X:
            return "2.7.2-era control"
        if step1.get(r["row"], {}).get("exact_versions"):
            return "genuine-exact (control)"
        c = dep.get(r["row"], "")
        if c in ("_maybe_unfill_return_delay", "_unfill_via_load_delay"):
            return c
        return "other maspsx-dependent"
    return grp


def main():
    labels = sys.argv[1:] or [l for l in ORDER if (D / f"{l}.jsonl").exists()]
    grp = groups()
    print("## per compiler\n")
    print("| compiler | rows ok/run | twin with our cell (bodies equal) | multi-reg returns: filled / text / text-filled | "
          "ra-only returns: filled / text / text-filled | ASPSX 2.79 exact: base / t272 (our cc1) | psyq / psyq_t272 (this cc1) |")
    print("|---|---|---|---|---|---|---|")
    per = {}
    for lab in labels:
        rs = list(load(D / f"{lab}.jsonl").values())
        ok = [r for r in rs if r.get("status") == "ok" and "psyq" in (r.get("res") or {})]
        per[lab] = ok
        tw = defaultdict(lambda: [0, 0])
        for r in ok:
            tw[r["cell"]][0] += bool(r.get("psyq_s_equal")); tw[r["cell"]][1] += 1
        twin = ", ".join(f"{c} {a}/{b}" for c, (a, b) in sorted(tw.items()))
        ep = Counter()
        for r in ok:
            ep.update(r.get("psyq_epi") or {})
        print(f"| {lab} | {len(ok)}/{len(rs)} | {twin} | {ep['filled']} / {ep['text']} / {ep['text_filled']} | "
              f"{ep['ra_only_filled']} / {ep['ra_only_text']} / {ep['ra_only_text_filled']} | "
              f"{sum(exact(r, 'base') for r in ok)} / {sum(exact(r, 't272') for r in ok)} | "
              f"{sum(exact(r, 'psyq') for r in ok)} / {sum(exact(r, 'psyq_t272') for r in ok)} |")
    print("\n## by group (ASPSX 2.79 exact: base / t272 / psyq / psyq_t272; twin = bodies equal to our cell)\n")
    for lab in labels:
        G = defaultdict(list)
        for r in per[lab]:
            G[grp(r)].append(r)
        print(f"**{lab}**\n")
        print("| group | rows | twin | base | t272 | psyq | psyq_t272 |")
        print("|---|---|---|---|---|---|---|")
        for g in sorted(G, key=lambda k: -len(G[k])):
            rs = G[g]
            print(f"| {g} | {len(rs)} | {sum(bool(r.get('psyq_s_equal')) for r in rs)} | "
                  + " | ".join(str(sum(exact(r, t) for r in rs)) for t in ("base", "t272", "psyq", "psyq_t272")) + " |")
        print()
    errs = Counter()
    for lab in labels:
        for r in load(D / f"{lab}.jsonl").values():
            if r.get("status") != "ok":
                errs[(lab, (r.get("err") or "")[:80])] += 1
            elif "psyq_err" in r:
                errs[(lab, "psyq_err: " + r["psyq_err"][-80:])] += 1
    if errs:
        print("## errors\n")
        for (lab, e), n in sorted(errs.items()):
            print(f"- {lab}: {n} x `{e}`")


if __name__ == "__main__":
    main()
