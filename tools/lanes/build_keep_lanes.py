#!/usr/bin/env python3
"""Build luna keep lanes (round 23's recipe): each row names its nearest live keep, its class at combine, the
pass whose wiring first differs, what the kept variable holds, and the scorer residue of erasing it alone.

    python3 tools/lanes/build_keep_lanes.py [--pool ROWS.txt | --max-residue 3] [--classes ops,late] [--per 12] LANE...

Round 23 measured 2 of 48 (4%) on rows picked by residue alone: near misses by assembly distance were
equivalences CSE is entitled to use. Pick by class as well (docs/LANE_KIT.md, the census rule). Without --pool
the pool comes from the t53k journal: rows unchanged since it measured them whose nearest single keep erasure
has an assembly residue of at most --max-residue, fewest pins first. --classes filters either pool by that
site's class at combine. Each lane gets base/, out/, rows.md, BRIEF.md (tools/lanes/keep_lane_brief.md) and
PROMPT.txt; launch with tools/lanes/launch_lane.sh. Moved from the session scratchpad in round 24.
"""
import argparse
import hashlib
import json
import re
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import rows, clean_path, sha_text
from pin_census import sites_of
from pin_sites import erase_many
from verify import verify
from served import served_rows, assert_unserved

R = {r["id"]: r for r in rows()}

CLS = {
    "ops": "operations differ at combine: without the keep, CSE or combine folds the value into its uses "
           "(a constant substituted, two loads merged, an arithmetic result reused).",
    "wiring": "same operations, different data flow at combine: without the keep, CSE substitutes the source "
              "register for the copy (canon_reg keeps the oldest equivalent register).",
    "late": "identical through combine; the difference appears later (the pass named), usually allocation or "
            "scheduling order around the kept value.",
    "order": "same operations in another order at combine.",
}


def kind(var, before):
    m = list(re.finditer(r"(?<![.>\w])\b%s\s*(=|[-+|&^*/]=|<<=|>>=)(?!=)\s*([^;]*);" % re.escape(var), before))
    if not m:
        return "no plain assignment before it (initialiser, parameter or loop header)"
    op, rhs = m[-1].group(1), m[-1].group(2).strip()
    return "`%s %s %s;`" % (var, op, rhs[:80])


def nearest(d, s):
    """The journal's keep site nearest retail, if the current text still has a keep there."""
    ks = [x for x in d.get("sites") or [] if x.get("asm") is not None]
    if not ks:
        return None
    best = min(ks, key=lambda x: x["asm"])
    if best["site"] >= len(s) or not s[best["site"]][1].startswith("ASM_KEEP"):
        return None
    return best


def current(rid, last):
    """(text, sites, nearest keep) when the row is unchanged since t53k measured it, else None."""
    r, d = R.get(rid), last.get(rid)
    if not r or not d or not clean_path(r).exists():
        return None
    t = clean_path(r).read_text(errors="replace")
    if hashlib.sha256(t.encode()).hexdigest() != d.get("in_sha"):
        return None
    s = sites_of(t)
    best = nearest(d, s)
    return (t, s, best) if best else None


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("lanes", nargs="+")
    ap.add_argument("--pool")
    ap.add_argument("--max-residue", type=int, default=3)
    ap.add_argument("--classes", help="comma list of classes at combine: ops, wiring, late, order")
    ap.add_argument("--per", type=int, default=12)
    ap.add_argument("--repack", action="store_true",
                    help="admit rows already served by a lane (a deliberate retry pack)")
    ap.add_argument("--dry-run", action="store_true",
                    help="print the pack composition and the stats; write nothing")
    a = ap.parse_args()
    classes = set(a.classes.split(",")) if a.classes else None
    last = {}
    for line in open(ROOT / "ledger/sweeps/t53k_keep.jsonl"):
        d = json.loads(line)
        last[d["id"]] = d
    if a.pool:
        pool = [l.strip() for l in open(a.pool) if l.strip()]
    else:
        cand = []
        for rid in last:
            c = current(rid, last)
            if c and c[2]["asm"] <= a.max_residue:
                cand.append((len(c[1]), rid))
        pool = [rid for _, rid in sorted(cand)]
    served = served_rows()
    nserved = sum(1 for rid in pool if rid in served)
    if not a.repack:
        pool = [rid for rid in pool if rid not in served]
    print("pool %d rows | served by an earlier lane: %d" % (len(pool), nserved))
    brief = (ROOT / "tools/lanes/keep_lane_brief.md").read_text()
    it = iter(pool)
    for name in a.lanes:
        out = ["# Rows (erase the keep named here; the residue is the scorer diff of that one erasure)\n"]
        chunk, n = [], 0
        for rid in it:
            c = current(rid, last)
            if not c or (classes and c[2].get("cls") not in classes):
                continue
            t, s, best = c
            r, k = R[rid], s[best["site"]]
            with tempfile.TemporaryDirectory() as td:
                f = Path(td) / Path(r["c_path"]).name
                f.write_text(erase_many(t, [k], clean_notes=True))
                v = verify(r, f, regions=True)
            if v.get("exact"):
                continue                               # dies alone: T2's
            dd = v.get("text", "")
            chunk.append((rid, t))
            var = re.match(r"\s*(\w+)", k[2]).group(1)
            first = (best.get("first") or {}).get("abs") or "none"
            reg = [l for l in dd.splitlines() if l.strip() and not l.startswith(("NOTE", "##"))][:14]
            out.append(f"## {rid}\n- cell `{r['cfg']}`, {r['size']} B, {len(s)} pins; erase `{k[1]}({k[2]})` at line {k[5]} "
                       f"(of this row's keeps, the one whose lone erasure is nearest retail: assembly distance "
                       f"{best.get('asm')})\n- class at combine **{best.get('cls')}**, wiring first differs at "
                       f"**{first}**: {CLS.get(best.get('cls'), '')}\n- `{var}` holds: {kind(var, t[:k[3]])}\n"
                       "```\n" + "\n".join(reg) + "\n```\n")
            n += 1
            if n == a.per:
                break
        if n == 0:
            print(name, "no rows left")
            break
        assert_unserved([rid for rid, _ in chunk], a.repack)   # never re-serve a row by accident
        if a.dry_run:
            print(name, n, "rows (dry run, nothing written):", ", ".join(rid for rid, _ in chunk))
            continue
        L = ROOT / "work/native_lane" / name
        assert not (L / "last_message.txt").exists(), name
        (L / "out").mkdir(parents=True, exist_ok=True)
        for rid, t in chunk:
            cont, nm = rid.split("/")
            (L / "base" / cont).mkdir(parents=True, exist_ok=True)
            (L / "base" / cont / (nm + ".c")).write_text(t)
            (L / "base" / cont / (nm + ".c.base_sha")).write_text(sha_text(t))
        (L / "rows.md").write_text("\n".join(out))
        (L / "BRIEF.md").write_text(brief.replace("@LANE@", name).replace("@NROWS@", str(n))
                                    .replace("@ROOT@", str(ROOT)).replace("@HOME@", str(Path.home())))
        (L / "PROMPT.txt").write_text(f"FIRST RULE: run every compiler command as `cd work/native_lane/{name} && ...`; "
                                      f"gcc -da writes its dumps into the current directory, and lanes have left dozens "
                                      f"of dump files at the repo root.\nRead work/native_lane/{name}/BRIEF.md and follow it "
                                      f"exactly. Work only inside work/native_lane/{name}/ and never write files at the repo "
                                      f"root. When done, end with one line per row: row, result, the change in one sentence, "
                                      f"the mechanism in one sentence, the generator rule in one sentence, and what did not work.\n")
        print(name, n, "rows")


if __name__ == "__main__":
    main()
