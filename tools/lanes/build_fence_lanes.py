#!/usr/bin/env python3
"""Build luna fence lanes: each row names its nearest live fence, the pass that decides it and the pairs the
scheduler reorders without it (round 19's packs: 28% exact at 7-15 pins, 15% at 16-29, 7% at 32-89, 22% on
rows whose only fences are memory barriers; re-lanes of rows an earlier lane failed, 9%).

    python3 tools/lanes/build_fence_lanes.py --pool ROWS.txt [--take N] [--per 12] LANE...
    python3 tools/lanes/build_fence_lanes.py --pool ROWS.txt --relane [--per 12] LANE...
    python3 tools/lanes/build_fence_lanes.py --pool ROWS.txt --study-only

ROWS.txt is a file of row ids. Fresh mode keeps the pool's order (the first --take), puts rows of the same token
shape into one lane next to each other and splits the rows evenly, or --per a lane. --relane sorts the pool by
pin count, takes --per a lane and quotes under each row the verdict of the earlier fence lane that had it
(last_message.txt, else REPORT.md). The study (two compiles per fence) is cached by row text sha in --study.
Each lane gets base/, out/, rows.md, BRIEF.md (tools/lanes/fence_lane_brief.md) and PROMPT.txt; launch with
tools/lanes/launch_lane.sh. Moved from the session scratchpad (build_fence_lanes19.py, build_fence_lanes20.py)
in round 24.
"""
import argparse
import glob
import json
import re
import sys
import tempfile
from multiprocessing import Pool
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/xform"))
sys.path.insert(0, str(Path(__file__).resolve().parent))
from served import served_rows, assert_unserved
from common import rows, clean_path, sha_text
from pin_census import sites_of
from pin_sites import erase_many
from verify import verify
import phase_census as pc
import sched_trace as st

PASSES = ["combine", "sched", "lreg", "greg", "sched2", "jump2", "dbr"]
FENCES = ("ASM_SCHED_BARRIER", "ASM_MEM_BARRIER")
R = {r["id"]: r for r in rows()}

HINT = {
    "sched": "the first scheduler (sched1): without the fence, two insns become co-ready and their priority "
             "(or a tie) orders them differently. A fence is a full dependency cut; a statement permutation cannot "
             "stand in for it. Look for the REAL dependency or block boundary the original had between the pair.",
    "sched2": "the second scheduler (after allocation): the pair below reorders once registers are assigned.",
    "dbr": "delay-slot filling (reorg.c): a volatile asm stops reorg's search, so the fence decides which insn fills "
           "a branch or call delay slot. Look at the branch/call structure and what sits next to it.",
    "jump2": "the second jump pass (cross-jumping / branch threading): the fence keeps two tails from merging or "
             "a branch from being redirected. The fence lanes' CFG shapes (direct returns, polarity, direct stores in "
             "both arms) are this class.",
    "combine": "operations already differ at combine (CSE or combine saw through something the fence hid).",
    "greg": "global allocation.", "lreg": "local allocation.", "none": "(no stream difference found in these passes)",
}


def study(rid):
    r = R[rid]
    t = clean_path(r).read_text(errors="replace")
    s = sites_of(t)
    base = pc.compile_dumps(r, t)
    if base is None:
        return rid, None
    bf = {p: pc.features(x) for p, x in base["dumps"].items()}
    best = None
    for i, k in enumerate(s):
        if k[1] not in FENCES:
            continue
        after = pc.compile_dumps(r, erase_many(t, [k], clean_notes=True))
        if after is None:
            continue
        d = st.distance(base["asm"], after["asm"])
        if d == 0:
            continue                      # dies alone: T2's, not a lane's
        if best is None or d < best[0]:
            best = (d, i, k, after)
    if best is None:
        return rid, None
    d, i, k, after = best
    first = next((p for p in PASSES if p in bf and p in after["dumps"]
                  and bf[p][0] != pc.features(after["dumps"][p])[0]), "none")
    diag = st.diagnose({"assembly": base["asm"], "dumps": base["dumps"]},
                       {"assembly": after["asm"], "dumps": after["dumps"]})
    inv = []
    for ph in ("sched", "sched2"):
        for x in diag["phases"].get(ph, {}).get("inversions", [])[:3]:
            inv.append((ph, x["a"], x["b"], x["after_decision"].get("cause")))
    return rid, dict(site=i, line=k[5], dist=d, first=first, inv=inv, npins=len(s), macro=k[1])


def cached_study(ids, path):
    old = json.load(open(path)) if path.exists() else {}
    shas = {rid: sha_text(clean_path(R[rid]).read_text(errors="replace")) for rid in ids}
    todo = [rid for rid in ids if rid not in old or (old[rid] or {}).get("sha") != shas[rid]]
    with Pool(8) as p:
        for rid, a in p.map(study, todo):
            old[rid] = dict(a, sha=shas[rid]) if a else {"sha": shas[rid], "none": True}
    path.parent.mkdir(parents=True, exist_ok=True)
    json.dump(old, open(path, "w"), indent=1)
    print("studied", len(todo), "rows; reused", len(ids) - len(todo))
    return {rid: (None if old[rid].get("none") else old[rid]) for rid in ids}


def prev_verdict(rid, skip):
    """The earlier fence lane's one-line verdict on this row (last_message.txt), else a REPORT excerpt."""
    name = rid.split("/")[1]
    for L in sorted(glob.glob(str(ROOT / "work/native_lane/fences*"))):
        if Path(L).name in skip or not Path(L, "base", rid + ".c").exists():
            continue
        lm = Path(L, "last_message.txt")
        if lm.exists():
            for line in lm.read_text(errors="replace").splitlines():
                if name in line and len(line.strip()) > len(rid) + 10:
                    return Path(L).name, line.strip()[:700]
        rp = Path(L, "REPORT.md")
        if rp.exists():
            t = rp.read_text(errors="replace")
            i = t.find(name)
            if i >= 0:
                j = t.find("\n#", i + 1)
                return Path(L).name, re.sub(r"\s+", " ", t[i:(j if j > 0 else i + 900)])[:700]
        return Path(L).name, "(no verdict found in its REPORT)"
    return None, None


def token_shape(rid):
    t = re.sub(r"/\*.*?\*/|//[^\n]*", "", clean_path(R[rid]).read_text(errors="replace"), flags=re.S)
    return re.sub(r"\s+", "", re.sub(r"\b[A-Za-z_]\w*\b", "I", re.sub(r"\b0x[0-9A-Fa-f]+\b|\b\d+\b", "N", t)))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("lanes", nargs="*")
    ap.add_argument("--pool", required=True)
    ap.add_argument("--take", type=int)
    ap.add_argument("--per", type=int)
    ap.add_argument("--relane", action="store_true")
    ap.add_argument("--study", default=str(ROOT / "work/native_lane/fence_study.json"))
    ap.add_argument("--study-only", action="store_true")
    ap.add_argument("--repack", action="store_true",
                    help="admit rows already served by a lane (a deliberate retry pack)")
    ap.add_argument("--dry-run", action="store_true",
                    help="print the pack composition and the stats; write nothing")
    a = ap.parse_args()
    ids = [l.split()[0] for l in open(a.pool) if l.strip() and not l.startswith("#")]
    # --relane IS a retry pack (rows an earlier fence lane failed), so it implies --repack
    repack = a.repack or a.relane
    served = served_rows()
    nserved = sum(1 for rid in ids if rid in served)
    if not repack:
        ids = [rid for rid in ids if rid not in served]
    print("pool %d rows | served by an earlier lane: %d" % (len(ids), nserved))
    if a.relane:
        ids.sort(key=lambda rid: len(sites_of(clean_path(R[rid]).read_text(errors="replace"))))
        ids = ids[:(a.per or 12) * max(len(a.lanes), 1)]
    elif a.take:
        ids = ids[:a.take]
    res = cached_study(ids, Path(a.study))
    if a.study_only or not a.lanes:
        return
    good = [rid for rid in ids if res.get(rid)]
    if not a.relane:                       # rows with the same token shape go to the same lane, next to each other
        first, pos = {}, {rid: i for i, rid in enumerate(good)}
        for i, rid in enumerate(good):
            first.setdefault(token_shape(rid), i)
        good.sort(key=lambda rid: (first[token_shape(rid)], pos[rid]))
    per = a.per or -(-len(good) // len(a.lanes))
    brief = (ROOT / "tools/lanes/fence_lane_brief.md").read_text()
    live = sum(sum(s[1] == "ASM_SCHED_BARRIER" for s in sites_of(p.read_text(errors="replace")))
               for p in (ROOT / "src").glob("*/*.c"))
    for li, name in enumerate(a.lanes):
        mine = good[li * per:(li + 1) * per]
        if not mine:
            print(name, "no rows left")
            break
        assert_unserved(mine, repack)                   # never re-serve a row by accident
        if a.dry_run:
            print(name, len(mine), "rows (dry run, nothing written):", ", ".join(mine))
            continue
        L = ROOT / "work/native_lane" / name
        assert not (L / "last_message.txt").exists(), name
        (L / "out").mkdir(parents=True, exist_ok=True)
        out = ["# Rows (erase the fence named here; the residue is the scorer diff of that one erasure)\n"]
        for rid in mine:
            r = R[rid]
            t = clean_path(r).read_text(errors="replace")
            x = res[rid]
            k = sites_of(t)[x["site"]]
            with tempfile.TemporaryDirectory() as td:
                f = Path(td) / Path(r["c_path"]).name
                f.write_text(erase_many(t, [k], clean_notes=True))
                dd = verify(r, f, regions=True).get("text", "")
            cont, nm = rid.split("/")
            (L / "base" / cont).mkdir(parents=True, exist_ok=True)
            (L / "base" / cont / (nm + ".c")).write_text(t)
            (L / "base" / cont / (nm + ".c.base_sha")).write_text(sha_text(t))
            reg = [l for l in dd.splitlines() if l.strip() and not l.startswith(("NOTE", "##"))][:14]
            pairs = "".join(f"  - {ph}: `{p}` / `{q}` ({cause})\n" for ph, p, q, cause in x["inv"])
            pl, pv = prev_verdict(rid, set(a.lanes)) if a.relane else (None, None)
            out.append(f"## {rid}\n- cell `{r['cfg']}`, {r['size']} B, {x['npins']} pins; erase the "
                       f"`{x.get('macro', 'ASM_SCHED_BARRIER')}` at line {x['line']} (of this row's fences, the one "
                       f"whose lone erasure is nearest retail: assembly distance {x['dist']})\n"
                       f"- decided at **{x['first']}**: {HINT.get(x['first'], '')}\n"
                       + (f"- reordered pairs without the fence (insn a / insn b, cause):\n{pairs}" if pairs else "")
                       + (f"- an earlier lane ({pl}) did not solve it; its verdict: {pv}\n" if pl else "")
                       + "```\n" + "\n".join(reg) + "\n```\n")
        (L / "rows.md").write_text("\n".join(out))
        b = (brief.replace("@LANE@", name).replace("@NROWS@", str(len(mine))).replace("@LIVE@", str(live))
                  .replace("@ROOT@", str(ROOT)).replace("@HOME@", str(Path.home())))
        if a.relane:
            b = b.replace("## What is wanted\n", "## What is wanted\n\nEvery row here was given to an earlier fence "
                          "lane that did not solve it; its verdict is quoted under the row. Start past the directions "
                          "it measured, and use the deciding pass named for the row.\n", 1)
        (L / "BRIEF.md").write_text(b)
        (L / "PROMPT.txt").write_text(f"FIRST RULE: run every compiler command as `cd work/native_lane/{name} && ...`; "
                                      f"gcc -da writes its dumps into the current directory, and lanes have left "
                                      f"dozens of dump files at the repo root.\n"
                                      f"Read work/native_lane/{name}/BRIEF.md and follow it exactly. Work only inside "
                                      f"work/native_lane/{name}/ and never write files at the repo root. When done, end "
                                      f"with one line per row: row, result, the change in one sentence, the mechanism in "
                                      f"one sentence, the generator rule in one sentence, and what did not work.\n")
        print(name, len(mine), "rows")
    print("pool", len(ids), "usable", len(good))


if __name__ == "__main__":
    main()
