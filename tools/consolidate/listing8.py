"""listing8.py [all|set|IDS] [OUT]: cc1-listing identity at each row's cfg: OLD = src text + live include/, NEW = the
   phase-8 text (draft8/ else src) + lane inc_full/ (the complete post-apply include tree) as the ONLY include dir.
   Identical listing = identical assembler input = identical object.  Covers what verify.py cannot simulate in a lane
   (the scorer always puts the live include/ first).  SLUS rows are compiled as plain TUs at their cfg."""
import json, sys, subprocess, re, os
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import listing, row_index, REPO
LANE = Path(__file__).resolve().parent.parent
R = row_index()
strip = lambda s: [l for l in (s or "").splitlines() if not l.lstrip().startswith((".file", "#"))]
def ids(arg):
    if arg == "all": return sorted(R)
    if arg == "set":
        fs = subprocess.run(["grep", "-rlE", r"gameWork|GameWork|game_work\.h|S_80083178|D_80083178|D_80083CE8", "src", "--include=*.c"], cwd=REPO, capture_output=True, text=True).stdout.split()
        return sorted({"%s/%s" % (Path(f).parent.name, Path(f).stem) for f in fs} | {str(p.relative_to(LANE / "draft8"))[:-2] for p in (LANE / "draft8").rglob("*.c")})
    return [l.split()[0] for l in open(arg) if l.strip()]
def one(rid):
    src = REPO / "src" / (rid + ".c")
    if not src.is_file(): return {"id": rid, "missing": True}
    r = dict(R.get(rid) or {"id": rid, "cfg": "2.7.2-cdk"}); r["kind"] = "overlay"
    d = LANE / "draft8" / (rid + ".c"); new = d.read_text() if d.is_file() else src.read_text(errors="replace")
    a = listing(r, src.read_text(errors="replace")); b = listing(r, new, include=LANE / "inc_full")
    rec = {"id": rid, "draft": d.is_file(), "old": a is not None, "new": b is not None}
    rec["identical"] = a is not None and b is not None and strip(a) == strip(b)
    if a is not None and b is not None and not rec["identical"]:
        import difflib
        rec["diff"] = [l for l in difflib.unified_diff(strip(a), strip(b), lineterm="", n=0) if not l.startswith(("---", "+++", "@@"))][:10]
    return rec
if __name__ == "__main__":
    arg = sys.argv[1] if len(sys.argv) > 1 else "set"
    out = LANE / "results" / (sys.argv[2] if len(sys.argv) > 2 else "l8_%s.jsonl" % arg)
    n = same = 0; bad = []
    with ProcessPoolExecutor(14) as ex, open(out, "w") as fh:
        for rec in ex.map(one, ids(arg), chunksize=8):
            fh.write(json.dumps(rec) + "\n"); n += 1; same += rec.get("identical", False)
            if not rec.get("identical"): bad.append(rec)
    print(n, "ids", same, "identical")
    for b in bad[:40]: print("  ", json.dumps(b)[:400])
