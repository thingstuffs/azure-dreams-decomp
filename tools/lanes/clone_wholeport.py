#!/usr/bin/env python3
"""Whole-text clone port (round 77): replay a solved row's OUT text on a sibling whose pinned text is the
exemplar's BASE token-for-token up to identifiers and numbers.

    python3 tools/lanes/clone_wholeport.py <stage-lane> [--lanes-glob 'r6*,r7*'] [--workers 8] [--dry-run]

WHY.  clone_transfer.py splices the exemplar's base->out HUNKS into the sibling.  A structural rewrite (r77_opus_c1:
a stack struct split into locals, a pinned temp dissolved, 25 hunks) leaves the spliced candidates uncompilable, and
family 0 went 0/9 through it.  When the sibling is the same token stream as the exemplar's base (identifiers and
numbers aside), no splicing is needed: map exemplar token -> sibling token over the aligned streams and apply the map
to the whole OUT text.  That took 3 family-0 siblings 9 -> 0 in seconds.

MATCH.  skeleton = the comment-free token stream with every non-keyword identifier -> I and every number -> N.  A
pinned row whose current text has the same skeleton as some exemplar base is a candidate; the identifier map must be
a function (one exemplar token -> one sibling token), else refused.  Out tokens the base never had stay literal.
JUDGE.  verify.py byte-exact at the sibling's own recipe, and fewer pin sites than the sibling's current text.
Stages out/<container>/<name>.c + .base_sha (+ base/ copy) under work/native_lane/<stage-lane>, then writes
last_message.txt so land_finished2 lands it.  Exemplars: every lane matching the glob with base/ and out/ where out
has fewer pin sites than base.
"""
import sys, re, glob, tempfile, argparse
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from common import rows, clean_path, sha_text
from verify import verify
from pin_census import sites_of

KW = set("""auto break case char const continue default do double else enum extern float for goto if int long register
return short signed sizeof static struct switch typedef union unsigned void volatile while __inline__ inline
ASM_REG ASM_KEEP ASM_KEEP_NV ASM_USE ASM_USE_NV ASM_SCHED_BARRIER ASM_CLOBBER ASM_KEEP_DEP_NV NON_MATCHING
include define ifdef ifndef endif else elif""".split())
TOK = re.compile(r'[A-Za-z_]\w*|0[xX][0-9A-Fa-f]+|\d+|\S')
WORD = re.compile(r'[A-Za-z_]\w*|0[xX][0-9A-Fa-f]+|\d+')


def toks(t):
    t = re.sub(r'/\*.*?\*/', '', t, flags=re.S)
    t = re.sub(r'//[^\n]*', '', t)
    return TOK.findall(t)


def skel(ts):
    return tuple('N' if x[0].isdigit() else ('I' if (x[0].isalpha() or x[0] == '_') and x not in KW else x) for x in ts)


def port(base, out, cur):
    tb, ts = toks(base), toks(cur)
    if len(tb) != len(ts):
        return None
    m = {}
    for a, b in zip(tb, ts):
        if a == b:
            continue
        if m.setdefault(a, b) != b:
            return None
    return WORD.sub(lambda mo: m.get(mo.group(0), mo.group(0)), out)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("lane")
    ap.add_argument("--lanes-glob", default="r6*,r7*")
    ap.add_argument("--workers", type=int, default=8)
    ap.add_argument("--dry-run", action="store_true")
    a = ap.parse_args()
    by = {r["id"]: r for r in rows()}
    cur = {}
    for rid, r in by.items():
        p = clean_path(r)
        if r["container"] == "ovmovie" or not p.exists():
            continue
        t = p.read_text(errors="replace")
        n = len(sites_of(t))
        if n:
            cur[rid] = (t, n, skel(toks(t)))
    index = {}
    for rid, (t, n, s) in cur.items():
        index.setdefault(s, []).append(rid)
    ex = []
    for g in a.lanes_glob.split(","):
        for o in glob.glob(str(ROOT / "work/native_lane" / g / "out/*/*.c")):
            o = Path(o)
            b = o.parents[2] / "base" / o.parent.name / o.name
            if not b.exists():
                continue
            bt, ot = b.read_text(errors="replace"), o.read_text(errors="replace")
            if len(sites_of(ot)) < len(sites_of(bt)):
                ex.append((o.parent.name + "/" + o.stem, o.parents[2].name, bt, ot))
    jobs = {}
    for rep, lane, bt, ot in ex:
        for sid in index.get(skel(toks(bt)), []):
            if sid != rep and sid not in jobs:
                cand = port(bt, ot, cur[sid][0])
                if cand is not None and len(sites_of(cand)) < cur[sid][1]:
                    jobs[sid] = (rep, lane, cand)
    print(f"{len(ex)} exemplars, {len(cur)} pinned rows, {len(jobs)} skeleton-matched candidates")
    if a.dry_run:
        for sid, (rep, lane, _) in sorted(jobs.items()):
            print(" ", sid, "<-", lane, rep)
        return

    def judge(item):
        sid, (rep, lane, cand) = item
        row = by[sid]
        with tempfile.TemporaryDirectory() as td:
            f = Path(td) / Path(row["c_path"]).name
            f.write_text(cand)
            v = verify(row, f, include_root=(ROOT / "include").resolve())
        return sid, rep, lane, cand, bool(v.get("exact"))

    staged = 0
    D = ROOT / "work/native_lane" / a.lane
    with ThreadPoolExecutor(a.workers) as pool:
        for sid, rep, lane, cand, ok in pool.map(judge, sorted(jobs.items())):
            print("exact" if ok else "miss ", sid, "<-", lane, rep, cur[sid][1], "->", len(sites_of(cand)))
            if not ok:
                continue
            c, n = sid.split("/")
            for sub, txt in (("out", cand), ("base", cur[sid][0])):
                d = D / sub / c
                d.mkdir(parents=True, exist_ok=True)
                (d / f"{n}.c").write_text(txt)
            (D / "out" / c / f"{n}.c.base_sha").write_text(sha_text(cur[sid][0]) + "\n")
            staged += 1
    if staged:
        (D / "last_message.txt").write_text(f"clone_wholeport: {staged} rows staged (verify exact at the row's recipe)\n")
    print(f"staged {staged}")


if __name__ == "__main__":
    main()
