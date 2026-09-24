#!/usr/bin/env python3
"""Lost-compiler hunt B: tables for gcc2 trunk snapshots (1997-04..08) run through epilogue_model's psyq leg.

Brief: work/fidelity/LOSTCC_B_BRIEF.md; report: docs/evidence/fidelity_lostcc_B_trunk_bisect.md.
Builds: work/fidelity/lostcc/B/build_one.sh (manifest builds.json); runs: work/fidelity/lostcc/B/run2.sh, one journal
per cc1 at work/fidelity/lostcc/B/runs/<label>.jsonl (the same 603 rows as step 1c: every row that was at a 2.8-era
cell then).

A row is RETAIL-exact under a cc1 when genuine ASPSX 2.79 assembles that cc1's output (driven through the row's
registered driver, cpp and flags) to the row's maspsx object at its REGISTERED recipe, which the gate proves equal
to retail (`maspsx_exact` is re-checked per row: epilogue_model's maspsx leg is the per-row scorer's verdict).
`psyq` = the candidate's output as emitted; `psyq_t272` = after gcc 2.7.2's epilogue rule (only meaningful for
cc1s from after 1997-07-11, which fill the return; for text-epilogue cc1s it is the same text).

Row groups (computed from the journals, so they follow the registry at run time):
  cdk-exact   rows the genuine-equivalent cdk cc1 reproduces as emitted in THIS batch (step 1c: 424)
  H           step 1c's 131 epilogue-helper rows (work/fidelity/step1c/cdk_not_exact_epilogue_rows.tsv), split by
              whether the row is still at a 2.8-era cell (H28) or has since moved to cdk with new natural C (Hcdk)
  C20         the 20 step-1c rows already genuine-exact at their 2.8-era cell but not at cdk
  nosplit     rows whose flags carry -mno-split-addresses (cdk and PsyQ 4.0/4.1 reject the flag)

    python3 tools/fidelity/trunk_bisect_report.py [--runs DIR] [--tsv OUT.tsv]
"""
from __future__ import annotations

import argparse
import json
from collections import Counter
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
BDIR = ROOT / "work/fidelity/lostcc/B"
CELLS_2X = ("2.8.0", "2.8.1", "2.91.66", "2.95.2")


def load(p: Path) -> dict:
    out = {}
    for l in p.read_text().splitlines():
        if l.strip():
            r = json.loads(l)
            out[r["row"]] = r
    return out


def exact(r: dict, tag: str = "psyq", ver: str = "2.79") -> bool:
    """epilogue_model's verdict, only where the maspsx leg is the scorer-exact registered object."""
    if not r or r.get("status") != "ok" or r.get("maspsx_exact") is not True:
        return False
    x = dict((r.get("res") or {}).get(tag) or {})
    x.pop("same_as_input", None)
    v = x.get(ver)
    return bool(v and v.get("exact"))


def compiled(r: dict) -> bool:
    return bool(r) and r.get("status") == "ok" and "psyq" in (r.get("res") or {}) and not r.get("psyq_err")


PIN = None


def pinned(rid: str) -> bool:
    """Does the row's current C carry inline-asm scaffolding (ASM_KEEP*/ASM_REG pins, __asm__/asm statements)?
    Such rows' code depends on how the compiler treats ASM_OPERANDS (combine.c force_to_mode changed at r14287),
    which retail's original C never exercised: they are no evidence about the 1997 toolchain."""
    import re
    import sys
    global PIN
    if PIN is None:
        sys.path.insert(0, str(ROOT / "tools"))
        from common import rows, clean_path
        PIN = {"_by": {r["id"]: r for r in rows()}, "_cp": clean_path}
    if rid not in PIN:
        r = PIN["_by"].get(rid)
        txt = Path(PIN["_cp"](r)).read_text(errors="replace") if r else ""
        PIN[rid] = bool(re.search(r"\bASM_KEEP\w*|\bASM_REG\b|__asm__|\basm\s*\(", txt))
    return PIN[rid]


def groups(ref: dict) -> dict:
    tsv = [l.split("\t") for l in (ROOT / "work/fidelity/step1c/cdk_not_exact_epilogue_rows.tsv").read_text().splitlines()[1:]]
    H = [p[0] for p in tsv if p[3].startswith("_")]
    C20 = [p[0] for p in tsv if not p[3].startswith("_")]
    s424 = []
    p = ROOT / "work/fidelity/step1c/cdk_full.jsonl"
    if p.exists():
        s424 = [k for k, r in load(p).items() if exact(r)]
    return {
        "cdk-exact": sorted(k for k, r in ref.items() if exact(r)),
        "step1c-424": sorted(s424),
        "H28": sorted(i for i in H if ref.get(i, {}).get("cell") in CELLS_2X),
        "Hcdk": sorted(i for i in H if ref.get(i, {}).get("cell") not in CELLS_2X),
        "C20": sorted(C20),
        "nosplit": sorted(k for k, r in ref.items() if "-mno-split-addresses" in r.get("cfg", "")),
        "H28-pinfree": sorted(i for i in H if ref.get(i, {}).get("cell") in CELLS_2X and not pinned(i)),
        "all": sorted(ref),
    }


def order_key(label: str):
    import re
    m = re.match(r"r(\d+)", label)
    return (0, 0, label) if label == "cdk" else ((1, int(m.group(1)), label) if m else (2, 0, label))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--runs", default=str(BDIR / "runs"))
    ap.add_argument("--tsv", default=str(BDIR / "matrix.tsv"))
    ap.add_argument("--ref", default="cdk", help="reference journal label (the cdk cc1)")
    a = ap.parse_args()
    runs = {p.stem: load(p) for p in sorted(Path(a.runs).glob("*.jsonl"))}
    ref = runs[a.ref]
    G = groups(ref)
    labels = sorted(runs, key=order_key)
    man = {}
    mp = BDIR / "builds.json"
    if mp.exists():
        for b in json.loads(mp.read_text())["builds"]:
            if "svn" in b:
                man[b["svn"]] = b
    cc1_of = {}
    lp = BDIR / "run_labels.tsv"
    if lp.exists():
        for l in lp.read_text().splitlines()[1:]:
            k, v = l.split("\t")
            cc1_of[k] = ROOT / v

    def cc1_sha(lab):
        import hashlib
        p = cc1_of.get(lab)
        if not p or not p.exists():
            return ""
        if p.read_bytes()[:2] == b"#!":             # a -fno-exceptions wrapper: hash the cc1 it execs
            import re as _re
            m = _re.search(r"exec (\S+)", p.read_text())
            p = Path(m.group(1)) if m else p
        return hashlib.sha256(p.read_bytes()).hexdigest()[:16]

    # consistency: every journal must have seen the same row texts and cfgs as the reference
    drift = {}
    for lab in labels:
        d = [k for k in ref if k in runs[lab] and (runs[lab][k].get("cfg") != ref[k].get("cfg") or
             (runs[lab][k].get("src_sha") and ref[k].get("src_sha") and runs[lab][k]["src_sha"] != ref[k]["src_sha"]))]
        if d:
            drift[lab] = d
    print("## Group sizes\n")
    print(" | ".join(f"{g} {len(v)}" for g, v in G.items()))
    if drift:
        print("\nDRIFT (row text or cfg differs from the reference journal):",
              {k: (len(v), v[:3]) for k, v in drift.items()})
    print("\n## Per snapshot (retail-exact with genuine ASPSX 2.79; twin = .ent..end bodies identical to cdk's)\n")
    hdr = ["cc1", "date", "cc1 sha256", "compiled/603", "cdk-exact: exact / twin", "step1c-424: exact",
           "H28: exact / t272 / only-epi / twin cdk", "H28 pin-free: exact / t272", "Hcdk: exact", "C20: exact / t272", "nosplit: exact / t272",
           "all: exact / t272", "epilogue forms (multi-reg filled/text)"]
    print("| " + " | ".join(hdr) + " |")
    print("|" + "---|" * len(hdr))
    for lab in labels:
        R = runs[lab]
        def n(g, tag="psyq"):
            return sum(exact(R.get(i), tag) for i in G[g])
        def twin(g):
            return sum(1 for i in G[g] if R.get(i, {}).get("psyq_s_sha") and R[i]["psyq_s_sha"] == ref.get(i, {}).get("psyq_s_sha"))
        epi = Counter()
        for r in R.values():
            for k, v in (r.get("psyq_epi") or {}).items():
                epi[k] += v
        import re
        m = re.match(r"r(\d+)", lab)
        b = man.get("r" + m.group(1)) if m else None
        only_epi = sum(1 for i in G["H28"] if R.get(i, {}).get("psyq_s_equal_t272"))
        print(f"| {lab} | {b['date'] if b else ''} | {cc1_sha(lab)} | "
              f"{sum(compiled(r) for r in R.values())} | {n('cdk-exact')} / {twin('cdk-exact')} | {n('step1c-424')} | "
              f"{n('H28')} / {n('H28', 'psyq_t272')} / {only_epi} / {twin('H28')} | "
              f"{n('H28-pinfree')} / {n('H28-pinfree', 'psyq_t272')} | {n('Hcdk')} | "
              f"{n('C20')} / {n('C20', 'psyq_t272')} | {n('nosplit')} / {n('nosplit', 'psyq_t272')} | "
              f"{n('all')} / {n('all', 'psyq_t272')} | {epi.get('filled', 0)}/{epi.get('text', 0)} |")

    # per-row matrix over the H28 + C20 + nosplit rows
    rows = sorted(set(G["H28"]) | set(G["C20"]) | set(G["nosplit"]) | set(G["Hcdk"]))
    with open(a.tsv, "w") as fh:
        fh.write("row\tgroup\tpinned\tcell\tcfg\t" + "\t".join(labels) + "\n")
        for i in rows:
            grp = "H28" if i in G["H28"] else "Hcdk" if i in G["Hcdk"] else "C20" if i in G["C20"] else "nosplit"
            cells = []
            for lab in labels:
                r = runs[lab].get(i)
                if not compiled(r):
                    cells.append("err")
                    continue
                e, t = exact(r), exact(r, "psyq_t272")
                cells.append(("E" if e else "T" if t else ".") + ("=" if r.get("psyq_s_sha") == ref.get(i, {}).get("psyq_s_sha") else ""))
            fh.write(f"{i}\t{grp}\t{int(pinned(i))}\t{ref[i].get('cell')}\t{ref[i].get('cfg')}\t" + "\t".join(cells) + "\n")
    print(f"\nper-row matrix: {a.tsv}  (E = exact as emitted, T = exact after the t272 rule only, . = neither, "
          f"= suffix: body identical to cdk's, err = no cc1 output)")

    # body changes between consecutive snapshots (which rows move where)
    print("\n## Rows whose cc1 bodies change between consecutive trunk snapshots (all 603 rows / H28; exact = as emitted, "
          "t272 = after the 2.7.2 epilogue rule)\n")
    import re as _re
    seq = [l for l in labels if _re.fullmatch(r"r\d+", l) or l.endswith("noeh")]
    # the as-built April snapshots carry trunk's flag_exceptions = 1 default; compare the -fno-exceptions runs there
    seq = [l for l in seq if not (l + "noeh" in runs)]
    for x, y in zip(seq, seq[1:]):
        ch = [i for i in ref if runs[x].get(i, {}).get("psyq_s_sha") and runs[y].get(i, {}).get("psyq_s_sha")
              and runs[x][i]["psyq_s_sha"] != runs[y][i]["psyq_s_sha"]]
        chh = [i for i in ch if i in G["H28"]]
        gained = [i for i in G["H28"] if exact(runs[y].get(i), "psyq_t272") and not exact(runs[x].get(i), "psyq_t272")]
        lost = [i for i in G["H28"] if exact(runs[x].get(i), "psyq_t272") and not exact(runs[y].get(i), "psyq_t272")]
        pf = sum(1 for i in gained if not pinned(i))
        print(f"- {x} -> {y}: {len(ch)} rows change ({len(chh)} H28); H28 t272-exact gained {len(gained)} ({pf} pin-free), lost {len(lost)}"
              + (f"; gained {', '.join(gained[:6])}" if gained else "") + (f"; lost {', '.join(lost[:6])}" if lost else ""))


if __name__ == "__main__":
    main()
