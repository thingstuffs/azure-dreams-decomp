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
busy = set(l.strip() for l in open(LANE_ / "BUSY_ROWS5.txt") if l.strip())
R = row_index()
ids = []
for o in OBJS.values(): ids += [json.loads(l)["id"] for l in open(LANE_ / "census" / o["census"])]
for n, o in OBJS.items():      # rows already on the object's name that still hold a local pointer to it
    if "type" in o:
        rxp = re.compile(r"=\s*[^;=]*&\s*\(?\s*%s\b" % o["var"])
        ids += [rid for rid, r in R.items() if clean_path(r).is_file() and rxp.search(clean_path(r).read_text(errors="replace"))]
ids = [i for i in dict.fromkeys(ids) if i in R and i not in busy and (ONLY is None or i in ONLY)]
def apply(t, plan):
    notes = []
    for name, how in plan:
        if how == "view":
            n, why = rewrite_blk(t, loose=True)
        elif OBJS[name].get("kind") == "entity":
            import entity
            n, whys = t, []
            for rn in OBJS[name]["recs"]:
                if rn not in n: continue
                n2, w2 = entity.rewrite(n, str(REPO / "include/records" / (rn + ".h")), None, rn)
                if n2 is None: n = None; whys.append(w2); break
                n = n2; whys.append(w2)
            why = "; ".join(whys)
        elif "function" in OBJS[name]:
            n, why = C.rewrite_funcaddr(t, OBJS[name])
        else:
            n, why = C.rewrite(t, OBJS[name])
        if n is None: return None, "%s: %s" % (name, why)
        t = n; notes.append("%s[%s]: %s" % (name, how, why))
    return t, " | ".join(notes)
def one(rid):
    r = R[rid]; src = clean_path(r); t = src.read_text(errors="replace")
    sha = hashlib.sha256(src.read_bytes()).hexdigest()
    code = "".join(t[a:b] for a, b in C.code_spans(t))
    present = [n for n in NAMES if "syms" in OBJS[n] and re.search(r"\b(%s)\b" % OBJS[n]["syms"], code)]
    ptr_objs = [n for n in NAMES if "type" in OBJS[n]]
    if not present and not any(re.search(r"&\s*\(?\s*%s\b" % OBJS[n]["var"], code) for n in ptr_objs):
        return {"id": rid, "refused": "no code reference"}
    plans = [[(n, "natural") for n in present]]
    if "dungeonStatus" in present:
        plans.append([(n, "view" if n == "dungeonStatus" else "natural") for n in present])
    if len(present) > 1:
        for n in present: plans += [[(n, "natural")]] + ([[(n, "view")]] if n == "dungeonStatus" else [])
    if present: plans.append([])     # the local-pointer fold alone
    # every plan is tried first with the local-pointer idiom folded as well (direct, then typed), then without
    full = []
    for plan in plans:
        for pm in ("direct", "typed", None):
            full.append((plan, pm))
    last = None; refusals = []; seen = set()
    for plan, pm in full:
        text, note = apply(t, plan)
        if text is None: refusals.append(note); continue
        if pm:
            got = False
            for n in ptr_objs:
                if re.search(r"&\s*\(?\s*%s\b" % OBJS[n]["var"], text):
                    t2, n2 = C.rewrite_pointers(text, OBJS[n], pm)
                    if t2 is not None: text, note, got = t2, note + " | %s[ptr-%s]: %s" % (n, pm, n2), True
            if not got: continue
            plan = plan + [("ptr", pm)]
        if text == t or text in seen: continue
        seen.add(text)
        rec = check(r, text, score=True); rec.update(plan=plan, note=note, src_sha=sha, refusals=refusals)
        last = rec
        if not (rec.get("score") or {}).get("exact") and rec.get("abs_listing") == "identical" and rec.get("listing") != "build-error":
            rec["rebaseline_slus"] = True       # identical bytes after link; only relocation symbol names moved
        if (rec.get("score") or {}).get("exact") or rec.get("rebaseline_slus"):
            d = LANE_ / os.environ.get("CANDDIR", "cand3") / r["container"]; d.mkdir(parents=True, exist_ok=True)
            (d / src.name).write_text(text); (d / (src.name + ".base_sha")).write_text(sha)
            rec.update(ok=True, path="%s/%s" % (r["container"], src.name), present=present); return rec
    if last is None: return {"id": rid, "refused": "; ".join(refusals), "present": present}
    last.update(ok=False, present=present); return last
if __name__ == "__main__":
    out = LANE_ / "results" / ("p3_%s%s.jsonl" % ("_".join(NAMES), os.environ.get("TAG", "")))
    from collections import Counter; Cn = Counter()
    with ProcessPoolExecutor(6) as ex, open(out, "w") as fh:
        for rec in ex.map(one, ids):
            fh.write(json.dumps(rec) + "\n")
            if rec.get("ok"):
                landed = tuple(sorted("%s:%s" % p for p in rec["plan"])); Cn[landed] += 1
            else: Cn["refused" if rec.get("refused") else "miss"] += 1
    for k, v in sorted(Cn.items(), key=lambda x: -x[1]): print(v, k)
