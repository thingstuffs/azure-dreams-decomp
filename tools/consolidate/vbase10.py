"""vbase10.py: tools/verify.py over ALL rows of the CURRENT tree exactly as apply10's full mode calls it (live include)
   -> results/verify_baseline10.jsonl.  A pre-existing non-exact row would revert the full run."""
import sys, json
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
REPO = Path(__file__).resolve().parents[4]
sys.path.insert(0, str(REPO / "tools"))
import os; os.chdir(REPO)
from common import rows, ROOT
from verify import verify
R = {r["id"]: r for r in rows()}
def one(rid):
    return rid, verify(R[rid], ROOT / "src" / R[rid]["container"] / (rid.split("/", 1)[1] + ".c"), include_root=ROOT / "include")
bad = 0
with ThreadPoolExecutor(16) as ex, open(REPO / "work/native_lane/r78_types_p10/results/verify_baseline10.jsonl", "w") as fh:
    for rid, v in ex.map(one, sorted(R)):
        fh.write(json.dumps({"id": rid, "exact": bool(v.get("exact")), "status": v.get("status"), "total": v.get("total")}) + "\n")
        bad += not v.get("exact")
print(len(R), "rows", bad, "not exact")
