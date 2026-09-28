"""drive8.py [IDS_FILE] -> results/p8_view.jsonl: check() every row that names gameWork/GameWork or includes
   shared/game_work.h, with its respelled text (draft8/ when respell8 changed it, else the src text), against
   the lane inc/ (new game_work.h).  Non-row files (plural partitions / module .c) are listed as `nonrow`."""
import json, sys, hashlib, re, subprocess
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import *
from check import check
LANE_ = Path(__file__).resolve().parent.parent
R = row_index()
def ids():
    if len(sys.argv) > 1: return [l.strip() for l in open(sys.argv[1]) if l.strip()]
    fs = subprocess.run(["grep", "-rlE", r"gameWork|GameWork|shared/game_work\.h", "src", "--include=*.c"], cwd=REPO, capture_output=True, text=True).stdout.split()
    return sorted("%s/%s" % (Path(f).parent.name, Path(f).stem) for f in fs)
def one(rid):
    src = REPO / "src" / (rid + ".c")
    if rid not in R: return {"id": rid, "nonrow": True}
    d = LANE_ / "draft8" / (rid + ".c")
    t = d.read_text() if d.is_file() else src.read_text(errors="replace")
    rec = check(R[rid], t, score=True)
    rec.update(src_sha=hashlib.sha256(src.read_bytes()).hexdigest(), changed=d.is_file())
    ok = (rec.get("score") or {}).get("exact")
    if not ok and rec.get("abs_listing") == "identical": rec["rebaseline_slus"] = True
    rec["ok"] = bool(ok or rec.get("rebaseline_slus"))
    rec.pop("diff", None) if rec["ok"] else None
    return rec
if __name__ == "__main__":
    I = ids(); out = LANE_ / "results" / ("p8_view.jsonl" if len(sys.argv) < 3 else sys.argv[2]); out.parent.mkdir(exist_ok=True)
    n = ok = 0
    with ProcessPoolExecutor(12) as ex, open(out, "w") as fh:
        for rec in ex.map(one, I, chunksize=4):
            fh.write(json.dumps(rec) + "\n"); n += 1; ok += rec.get("ok", False)
    print(n, "ids", ok, "ok")
