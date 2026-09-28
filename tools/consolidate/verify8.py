"""verify8.py [all|IDS_FILE] [OUT]: tools/verify.py on every row's phase-8 text (draft8/ else src) with the lane's full
   include tree inc_full/ (new shared/game_work.h, game.h without struct S_80083178, globals.h without D_80083178)
   - the exact simulation of apply8's verify step.  Module rows cannot use a non-live include root: listed `module`."""
import json, sys, subprocess
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
LANE = Path(__file__).resolve().parent.parent; REPO = LANE.parent.parent.parent
sys.path.insert(0, str(REPO / "tools"))
import os; os.chdir(REPO)
from common import rows
from verify import verify
R = {r["id"]: r for r in rows()}
arg = sys.argv[1] if len(sys.argv) > 1 else "set"
if arg == "all": ids = sorted(R)
elif arg == "set":
    fs = subprocess.run(["grep", "-rlE", r"gameWork|GameWork|game_work\.h|S_80083178|D_80083178|D_80083CE8", "src", "--include=*.c"], capture_output=True, text=True).stdout.split()
    ids = sorted({"%s/%s" % (Path(f).parent.name, Path(f).stem) for f in fs} | {str(p.relative_to(LANE / "draft8"))[:-2] for p in (LANE / "draft8").rglob("*.c")})
else: ids = [l.split()[0] for l in open(arg) if l.strip()]
out = LANE / "results" / (sys.argv[2] if len(sys.argv) > 2 else "v8_%s.jsonl" % arg)
def one(rid):
    if rid not in R: return {"id": rid, "nonrow": True}
    r = R[rid]; d = LANE / "draft8" / (rid + ".c")
    f = d if d.is_file() else REPO / "src" / r["container"] / (rid.split("/", 1)[1] + ".c")
    v = verify(r, f, include_root=LANE / "inc_full")
    return {"id": rid, "draft": d.is_file(), "exact": bool(v.get("exact")), "status": v.get("status"), "total": v.get("total"), "err": (v.get("err") or "")[-200:]}
n = bad = 0
with ThreadPoolExecutor(12) as ex, open(out, "w") as fh:
    for rec in ex.map(one, ids):
        fh.write(json.dumps(rec) + "\n"); n += 1
        if not rec.get("exact") and not rec.get("nonrow"): bad += 1; print("NOT EXACT", rec)
print(n, "ids", bad, "not exact")
