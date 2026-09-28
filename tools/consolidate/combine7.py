"""combine7.py -> cand7/ + cand7/MANIFEST.tsv + results/p7_combined.jsonl: every phase-7 row with all of its
   transforms applied to the CURRENT src text, verified once (check: cc1 listing + verify.py byte score)."""
import json, sys, hashlib, re, os, glob
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import *
import consolidate as C, room, slots
from check import check
LANE_ = Path(__file__).resolve().parent.parent
O296 = C.load(LANE_ / "objects/D_800E296C.json"); O137 = C.load(LANE_ / "objects/D_80013714.json")
R = row_index()
sets = {"rec": {"dungeon/func_810AFA04", "dungeon/func_81324774"}}
sets["slots"] = {"%s/%s" % tuple(Path(p).parts[-2:]) for p in glob.glob(str(LANE_ / "cand7s/*/*.c"))}
sets["slots"] = {x[:-2] for x in sets["slots"]}
sets["floor"] = {json.loads(l)["id"] for l in open(LANE_ / "results/p7_floor.jsonl") if json.loads(l).get("ok")}
sets["flags"] = {json.loads(l)["id"] for l in open(LANE_ / "results/p3_D_80013714_s.jsonl") if json.loads(l).get("ok")}
ids = sorted({x for v in sets.values() for x in v})
def one(rid):
    r = R[rid]; src = clean_path(r); t = src.read_text(errors="replace"); sha = hashlib.sha256(src.read_bytes()).hexdigest()
    n, notes = t, []
    for k in ("rec", "slots", "floor", "flags"):
        if rid not in sets[k]: continue
        if k == "rec": n2, why = n.replace('#include "records/Rec_D_800814A8.h"\n', ""), "drop Rec_D_800814A8.h include"
        elif k == "slots": n2, why = slots.rewrite(n)
        elif k == "floor":
            code = "".join(n[a:b] for a, b in C.code_spans(n)); n2, why = n, []
            if re.search(r"\bD_800E296C\b", code):
                n2, w = C.rewrite(n2, O296); why.append("296C: %s" % w)
            if n2 is not None and re.search(r"\bD_800E2970\b", code):
                n2, w = room.rewrite(n2); why.append("2970: %s" % w)
            why = " / ".join(why)
        else: n2, why = C.rewrite(n, O137)
        if n2 is None: return {"id": rid, "ok": False, "refused": "%s: %s" % (k, why)}
        n = n2; notes.append("%s: %s" % (k, why))
    rec = check(r, n, score=True); rec.update(note=" | ".join(notes), src_sha=sha, sets=[k for k in sets if rid in sets[k]])
    ok = (rec.get("score") or {}).get("exact")
    if not ok and rec.get("abs_listing") == "identical" and rec.get("listing") != "build-error": rec["rebaseline_slus"] = True
    if ok or rec.get("rebaseline_slus"):
        d = LANE_ / "cand7" / r["container"]; d.mkdir(parents=True, exist_ok=True)
        (d / src.name).write_text(n); (d / (src.name + ".base_sha")).write_text(sha)
        rec.update(ok=True, path="%s/%s" % (r["container"], src.name))
    else: rec["ok"] = False
    return rec
if __name__ == "__main__":
    recs = []
    with ProcessPoolExecutor(6) as ex, open(LANE_ / "results/p7_combined.jsonl", "w") as fh:
        for rec in ex.map(one, ids): fh.write(json.dumps(rec) + "\n"); recs.append(rec)
    with open(LANE_ / "cand7/MANIFEST.tsv", "w") as fh:
        fh.write("# row\tpath\tverified_src_sha\tplan\trebaseline\n")
        for r in recs:
            if r.get("ok"): fh.write("%s\t%s\t%s\t%s\t%s\n" % (r["id"], r["path"], r["src_sha"], "+".join(r["sets"]), "rebaseline" if r.get("rebaseline_slus") else ""))
    print(len(recs), "rows,", sum(1 for r in recs if r.get("ok")), "ok"); [print("NOT OK", r["id"], r.get("refused") or (r.get("listing"), r.get("score"), (r.get("err") or "")[:200])) for r in recs if not r.get("ok")]
