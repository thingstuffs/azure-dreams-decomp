"""drive8x.py KEY -> results/t3_KEY.jsonl + cand8x/: task-3 rewrite (records8) on top of the phase-8 text (draft8/ if
   present, else src), verified with check() (lane inc/: new shared headers inlined).  Rows in draft8 whose draft
   depends on the new game.h/globals.h (hand rows) are skipped."""
import json, sys, hashlib, re
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import *
from check import check
import records8
LANE_ = Path(__file__).resolve().parent.parent; R = row_index(); KEY = sys.argv[1]
SYM = records8.OBJ[KEY]["SYM"]
SKIP = {"dungeon/func_800AFA68", "slus/w_8004D5D0", "slus/code2"}
def one(r):
    rid = r["id"]; src = clean_path(r); d = LANE_ / "draft8" / (rid + ".c")
    t = d.read_text() if d.is_file() else src.read_text(errors="replace")
    if rid in SKIP: return {"id": rid, "ok": False, "refused": "hand row"}
    for nat in (True, False):
        n, why = records8.rewrite2(KEY, t, nat)
        if n is None: return {"id": rid, "ok": False, "refused": why}
        rec = check(r, n, score=True); rec.update(note=why, src_sha=hashlib.sha256(src.read_bytes()).hexdigest())
        if (rec.get("score") or {}).get("exact") or "natural" not in why: break
    ok = (rec.get("score") or {}).get("exact")
    if not ok and rec.get("abs_listing") == "identical" and rec.get("listing") != "build-error": rec["rebaseline_slus"] = True
    rec["ok"] = bool(ok or rec.get("rebaseline_slus"))
    if rec["ok"]:
        p = LANE_ / "cand8x" / (rid + ".c"); p.parent.mkdir(parents=True, exist_ok=True); p.write_text(n); rec.pop("diff", None)
    return rec
if __name__ == "__main__":
    todo = [r for r in R.values() if re.search(r"\b%s\b" % SYM, clean_path(r).read_text(errors="replace"))]
    recs = []
    with ProcessPoolExecutor(12) as ex, open(LANE_ / "results" / ("t3_%s.jsonl" % KEY), "w") as fh:
        for rec in ex.map(one, todo): fh.write(json.dumps(rec) + "\n"); recs.append(rec)
    print(KEY, len(recs), "rows", sum(r["ok"] for r in recs), "ok")
    for r in recs:
        if not r["ok"]: print("  NOT OK", r["id"], r.get("refused") or (r.get("listing"), r.get("score"), (r.get("err") or "")[:160], (r.get("diff") or [])[:4]))
