"""drive3.py OBJ1,OBJ2,... [--only ids]  -> results/p2_multi.jsonl, cand2/<container>/<file>.c (+ .base_sha)
   Every row that spells ANY of the objects by address gets all of their rewrites in one text, verified once.
   Tries, in order: every object natural; then with dungeonStatus on the phase-1 view spelling; then each
   object alone (the others left as D_).  ok = verify.py exact; the record says which objects landed."""
import json, sys, hashlib, re, os, itertools
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import *
import consolidate as C
from rewrite import rewrite_blk
from check import check
LANE_ = Path(__file__).resolve().parent.parent
NAMES = sys.argv[1].split(","); OBJS = {n: C.load(LANE_ / "objects" / (n + ".json")) for n in NAMES}
ONLY = set(sys.argv[sys.argv.index("--only") + 1].split(",")) if "--only" in sys.argv else None
busy = set(l.strip() for l in open(LANE_ / "BUSY_ROWS2.txt") if l.strip())
R = row_index()
ids = []
for o in OBJS.values(): ids += [json.loads(l)["id"] for l in open(LANE_ / "census" / o["census"])]
ids = [i for i in dict.fromkeys(ids) if i in R and i not in busy and (ONLY is None or i in ONLY)]
def apply(t, plan):
    notes = []
    for name, how in plan:
        if how == "view":
            n, why = rewrite_blk(t, loose=True)
        else:
            n, why = C.rewrite(t, OBJS[name])
        if n is None: return None, "%s: %s" % (name, why)
        t = n; notes.append("%s[%s]: %s" % (name, how, why))
    return t, " | ".join(notes)
def one(rid):
    r = R[rid]; src = clean_path(r); t = src.read_text(errors="replace")
    sha = hashlib.sha256(src.read_bytes()).hexdigest()
    code = "".join(t[a:b] for a, b in C.code_spans(t))
    present = [n for n in NAMES if re.search(r"\b(%s)\b" % OBJS[n]["syms"], code)]
    if not present: return {"id": rid, "refused": "no code reference"}
    plans = [[(n, "natural") for n in present]]
    if "dungeonStatus" in present:
        plans.append([(n, "view" if n == "dungeonStatus" else "natural") for n in present])
    if len(present) > 1:
        for n in present: plans += [[(n, "natural")]] + ([[(n, "view")]] if n == "dungeonStatus" else [])
    last = None; refusals = []
    for plan in plans:
        text, note = apply(t, plan)
        if text is None: refusals.append(note); continue
        rec = check(r, text, score=True); rec.update(plan=plan, note=note, src_sha=sha, refusals=refusals)
        last = rec
        if (rec.get("score") or {}).get("exact"):
            d = LANE_ / "cand2" / r["container"]; d.mkdir(parents=True, exist_ok=True)
            (d / src.name).write_text(text); (d / (src.name + ".base_sha")).write_text(sha)
            rec.update(ok=True, path="%s/%s" % (r["container"], src.name), present=present); return rec
    if last is None: return {"id": rid, "refused": "; ".join(refusals), "present": present}
    last.update(ok=False, present=present); return last
if __name__ == "__main__":
    out = LANE_ / "results" / ("p2_multi%s.jsonl" % os.environ.get("TAG", ""))
    from collections import Counter; Cn = Counter()
    with ProcessPoolExecutor(6) as ex, open(out, "w") as fh:
        for rec in ex.map(one, ids):
            fh.write(json.dumps(rec) + "\n")
            if rec.get("ok"):
                landed = tuple(sorted("%s:%s" % p for p in rec["plan"])); Cn[landed] += 1
            else: Cn["refused" if rec.get("refused") else "miss"] += 1
    for k, v in sorted(Cn.items(), key=lambda x: -x[1]): print(v, k)
