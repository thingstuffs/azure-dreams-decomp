#!/usr/bin/env python3
"""Tables for docs/evidence/fidelity_asv_trial.md from work/fidelity/asv/asv_trial.jsonl
(tools/fidelity/asv_trial.py), plus the list files work/fidelity/asv/changed_rows.tsv and dial_rows.tsv.

    python3 tools/fidelity/asv_report.py [--journal PATH] > work/fidelity/asv/tables.md
"""
import argparse
import collections
import json
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(HERE))
OUT = ROOT / "work/fidelity/asv"
TRIAL = ["2.60", "2.77", "2.79", "2.81"]
CLASSES = ["same", "changed-exact", "stops-matching", "starts-matching", "changed-nonexact"]
CONT = ["slus", "main", "town", "dungeon", "ovmovie"]
PRED = {"sltu_at": "sltu_neg", "gp_allow_offset": "comm_off", "gp_allow_la": "la_small"}


def table(head, rows):
    out = ["| " + " | ".join(head) + " |", "|" + "---|" * len(head)]
    out += ["| " + " | ".join(str(c) for c in r) + " |" for r in rows]
    return "\n".join(out)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--journal", default=str(OUT / "asv_trial.jsonl"))
    a = ap.parse_args()
    recs = [json.loads(l) for l in Path(a.journal).read_text().splitlines() if l.strip()]
    ok = [r for r in recs if r.get("status") == "ok"]
    err = [r for r in recs if r.get("status") != "ok"]
    p = print

    p("## Headline\n")
    p(f"rows in the journal: {len(recs)}; measured: {len(ok)}; harness errors: {len(err)}")
    p(f"maspsx leg at 2.56 retail-exact (pipeline verdict): {sum(r['base_exact'] for r in ok)}; "
      f"self-check (traced 2.56 object == pipeline object): {sum(1 for r in ok if r.get('selfcheck'))} "
      f"(None: {sum(1 for r in ok if r.get('selfcheck') is None)}, False: {sum(1 for r in ok if r.get('selfcheck') is False)})\n")
    rows = []
    for v in TRIAL:
        c = collections.Counter(r["v"][v].get("class", "error") for r in ok)
        rows.append([f"**{v}**"] + [c.get(k, 0) for k in CLASSES] + [c.get("error", 0)])
    p(table(["global --aspsx-version"] + CLASSES + ["run error"], rows))
    same77 = sum(1 for r in ok if r["sha"].get("2.77") == r["sha"].get("2.79"))
    p(f"\n2.77 object == 2.79 object (sha): {same77} / {len(ok)} rows.\n")

    p("## Changed rows by container and cell\n")
    p("changed / stops-matching per version (rows with no change at any version omitted).\n")
    cells = collections.defaultdict(list)
    for r in ok:
        cells[(r["container"], r.get("cell") or r["cfg"])].append(r)
    rows = []
    for (co, ce), rs in sorted(cells.items(), key=lambda kv: (CONT.index(kv[0][0]) if kv[0][0] in CONT else 9, kv[0][1])):
        line = [co, ce, len(rs)]
        any_ = False
        for v in TRIAL:
            ch = sum(1 for r in rs if not r["v"][v].get("same", True))
            st = sum(1 for r in rs if r["v"][v].get("class") == "stops-matching")
            any_ |= ch > 0
            line.append(f"{ch} / {st}")
        if any_:
            rows.append(line)
    p(table(["container", "cell", "rows"] + [f"{v} changed / stops" for v in TRIAL], rows) if rows else "(none)")

    p("\n## Cause of each change (first version at which the object moves)\n")
    cc = collections.Counter()
    for r in ok:
        if r["cause"] != "none":
            cc[(r["cause"], r["v"]["2.79"].get("class"), r["v"]["2.81"].get("class"))] += 1
    p(table(["cause", "class at 2.79", "class at 2.81", "rows"], [[*k, n] for k, n in cc.most_common()]) if cc else "(no row changes)")

    p("\n## Static predictor vs measured change\n")
    p("predicted = maspsx's input has the construct the behaviour rewrites; moved = the object changes at the version that "
      "flips it (sltu_at at 2.60, gp_allow_offset 2.60 -> 2.79, gp_allow_la 2.79 -> 2.81).\n")
    rows = []
    for flag, key in PRED.items():
        pr = [r for r in ok if r["pred"][key]]
        mv = [r for r in ok if flag in r["cause"].split("+")]
        unp = [r["row"] for r in mv if not r["pred"][key]]
        rows.append([flag, len(pr), len(mv), sum(1 for r in mv if r["pred"][key]), len(unp), ", ".join(unp[:6])])
    p(table(["behaviour", "rows predicted", "rows moved", "moved & predicted", "moved, unpredicted", "examples"], rows))

    p("\n## maspsx passes that fire differently\n")
    fd = collections.Counter()
    for r in ok:
        for v in TRIAL:
            f = r["v"][v].get("fired")
            if f is not None:
                base = set(r["fired_base"]); new = set(f)
                for x in sorted(base - new):
                    fd[(v, "-" + x)] += 1
                for x in sorted(new - base):
                    fd[(v, "+" + x)] += 1
    p(table(["version", "pass (- stops firing, + starts)", "rows"], [[*k, n] for k, n in sorted(fd.items())]) if fd else "(none)")

    p("\n## Row version dials\n")
    rows = []
    dial = [r for r in ok if r.get("dial")]
    for r in sorted(dial, key=lambda r: (r["dial"], r["row"])):
        d = r["dial_drop"]
        def cls(v):
            x = d.get(v, {})
            s = x.get("class", "err")
            if "words_diff" in x:
                s += f" ({x['words_diff']} w)"
            return s
        rows.append([r["row"], r["dial"], r.get("cell"), r["v"]["2.79"]["class"], cls("2.56"), cls("2.79"),
                     "; ".join(f"{k} {a}->{b}" for k, (a, b) in d["config_delta_vs_dial"]["2.79"].items())])
    p(table(["row", "dial", "cell", "global 2.79, dial kept", "dial dropped @2.56", "dial dropped @2.79", "config dial -> 2.79"], rows) if rows else "(none)")

    OUT.mkdir(parents=True, exist_ok=True)
    with open(OUT / "changed_rows.tsv", "w") as fh:
        fh.write("row\tcontainer\tcell\tcause\t" + "\t".join(f"class@{v}" for v in TRIAL) + "\tpred\n")
        for r in ok:
            if r["cause"] != "none":
                fh.write("\t".join([r["row"], r["container"], str(r.get("cell")), r["cause"]] +
                                   [r["v"][v].get("class", "err") for v in TRIAL] + [json.dumps(r["pred"])]) + "\n")
    with open(OUT / "dial_rows.tsv", "w") as fh:
        fh.write("row\tdial\tcell\tglobal2.79_dial_kept\tdial_dropped@2.56\tdial_dropped@2.79\n")
        for r in dial:
            fh.write("\t".join([r["row"], r["dial"], str(r.get("cell")), r["v"]["2.79"]["class"],
                                r["dial_drop"].get("2.56", {}).get("class", "err"),
                                r["dial_drop"].get("2.79", {}).get("class", "err")]) + "\n")
    if err:
        p("\n## Harness errors\n")
        p(table(["row", "err"], [[r["row"], (r.get("err") or "")[:160].replace("|", "/")] for r in err[:40]]))


if __name__ == "__main__":
    main()
