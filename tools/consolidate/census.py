"""Compile every row that references the target symbols; keep the listing lines that touch them.
   out: census/<tag>.jsonl  {id, cfg, lines:[...], hi_bases:n}"""
import json, re, sys, subprocess
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import *
TAG, PAT = sys.argv[1], sys.argv[2]
LANE_ = Path(__file__).resolve().parent.parent
busy = set(l.strip() for l in open(LANE_ / "BUSY_ROWS5.txt") if l.strip())
R = row_index()
files = {}
for c in ("slus", "main", "town", "dungeon", "ovmovie"):
    rxf = re.compile(PAT)
    out = [str(f) for f in (REPO / "src" / c).glob("*.c") if rxf.search(f.read_text(errors="replace"))]
    for f in out: files[(c, Path(f).name)] = f
todo = [r for r in R.values() if (r["container"], Path(r["c_path"]).name) in files]
rx = re.compile(PAT)
def one(r):
    t = clean_path(r).read_text(errors="replace")
    s = listing(r, t)
    if s is None: return {"id": r["id"], "cfg": r["cfg"], "error": True}
    from flow import scan
    acc = scan(s, re.compile(r"D_[0-9A-F]{8}") if False else re.compile(PAT.rstrip("\\b") if False else r"D_[0-9A-F]{8}"))
    acc = [x for x in acc if rx.search(x[1])]
    body = [l.strip() for l in s.splitlines() if not l.lstrip().startswith(("#", ".")) or l.lstrip().startswith((".word", ".half", ".byte"))]
    # keep lines touching the target and the line that uses a register loaded by %hi/la of it
    keep = [l for l in body if rx.search(l)]
    return {"id": r["id"], "cfg": r["cfg"], "busy": r["id"] in busy, "lines": keep, "listing_lines": len(body), "acc": acc}
if __name__ == "__main__":
    (LANE_ / "census").mkdir(exist_ok=True)
    with ProcessPoolExecutor(8) as ex, open(LANE_ / "census" / (TAG + ".jsonl"), "w") as fh:
        for rec in ex.map(one, todo, chunksize=4):
            fh.write(json.dumps(rec) + "\n")
    print(TAG, len(todo), "rows")
