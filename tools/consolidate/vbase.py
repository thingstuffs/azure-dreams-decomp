"""vbase.py: tools/verify.py over ALL rows of the current tree (live src + include), exactly as apply9 calls it."""
import json, os, sys, time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
LANE = Path(__file__).resolve().parent.parent; REPO = LANE.parent.parent.parent
sys.path.insert(0, str(REPO / "tools")); os.chdir(REPO)
from common import rows, ROOT
from verify import verify
R = {r["id"]: r for r in rows()}
def one(rid):
    v = verify(R[rid], ROOT / "src" / R[rid]["container"] / (rid.split("/", 1)[1] + ".c"), include_root=ROOT / "include")
    return {"id": rid, "exact": bool(v.get("exact")), "status": v.get("status"), "total": v.get("total"), "err": (v.get("err") or "")[-200:]}
t0 = time.time(); bad = 0
with ThreadPoolExecutor(16) as ex, open(LANE / "results/verify_baseline9.jsonl", "w") as fh:
    for rec in ex.map(one, sorted(R)):
        fh.write(json.dumps(rec) + "\n"); bad += not rec["exact"]
print(len(R), "rows", bad, "not exact", round(time.time() - t0), "s")
