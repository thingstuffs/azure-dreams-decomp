"""check9.py: check() every draft9 row (listing identity through ccproc with the lane names table + verify.py byte
   score with the lane shared headers inlined).  ok = exact, or a SLUS row whose listing is identical once symbols are
   absolute addresses (rebaseline after the image gate).  -> results/final9.jsonl"""
import json, sys, hashlib
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import row_index, clean_path, REPO
from check import check
LANE = Path(__file__).resolve().parent.parent; R = row_index()
def one(rid):
    t = (LANE / "draft9" / (rid + ".c")).read_text()
    rec = check(R[rid], t)
    ok = bool((rec.get("score") or {}).get("exact"))
    if not ok and rec.get("abs_listing") == "identical": rec["rebaseline_slus"] = True
    rec["ok"] = ok or bool(rec.get("rebaseline_slus"))
    rec["src_sha"] = hashlib.sha256((REPO / "src" / (rid + ".c")).read_bytes()).hexdigest()
    rec["cand_sha"] = hashlib.sha256(t.encode()).hexdigest()
    return rec
if __name__ == "__main__":
    ids = sorted(str(p.relative_to(LANE / "draft9"))[:-2] for p in (LANE / "draft9").rglob("*.c"))
    ids = [i for i in ids if i in R]
    n = ok = 0
    with ProcessPoolExecutor(12) as ex, open(LANE / "results/final9.jsonl", "w") as fh:
        for rec in ex.map(one, ids, chunksize=2):
            fh.write(json.dumps(rec) + "\n"); n += 1; ok += rec["ok"]
            if not rec["ok"]: print("NOT OK", rec["id"], rec.get("listing"), rec.get("score"), (rec.get("err") or "")[:150], (rec.get("diff") or [])[:3])
    print(n, "rows", ok, "ok")
