"""drive9g.py: task 3b - local view pointers onto gameWork (OPEN_ITEMS #10 class): consolidate.rewrite_pointers (mode
   direct, then typed) with the flat spec objects/gameWork.json, then respell8 (phase-8 member paths:
   gameWork.unk_0XX in 0x018..0x1DB -> gameWork.view....).  check() against the lane inc/ (= the live shared headers).
   -> results/t3g.jsonl, cand9g/"""
import json, sys, hashlib, re
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import row_index, clean_path
import consolidate as C
from check import check
from respell8 import respell, suspects
LANE = Path(__file__).resolve().parent.parent
NAME = sys.argv[1] if len(sys.argv) > 1 else "gameWork"; OBJ = C.load(LANE / "objects" / (NAME + ".json")); R = row_index()
SKIP = {"dungeon/func_800AFA68", "slus/w_8004D5D0", "slus/code2", "slus/code"}
rx = re.compile(r"=\s*[^;=]*&\s*\(?\s*%s\b" % OBJ["var"])
def one(rid):
    r = R[rid]; src = clean_path(r); t = src.read_text(errors="replace")
    sha = hashlib.sha256(src.read_bytes()).hexdigest(); last = None; why = []
    for mode in ("direct", "typed"):
        new, note = C.rewrite_pointers(t, OBJ, mode)
        if new is None: why.append("%s: %s" % (mode, note)); continue
        new, _ = respell(new)
        if suspects(new): why.append("%s: flat field left %s" % (mode, suspects(new)[:2])); continue
        rec = check(r, new, score=True); rec.update(mode=mode, note=note, src_sha=sha, why=why); last = rec
        if (rec.get("score") or {}).get("exact"):
            p = LANE / ("cand9g" if NAME == "gameWork" else "cand9_" + NAME) / (rid + ".c"); p.parent.mkdir(parents=True, exist_ok=True); p.write_text(new)
            rec.update(ok=True); rec.pop("diff", None); return rec
    if last is None: return {"id": rid, "ok": False, "refused": "; ".join(why)}
    last["ok"] = False; return last
if __name__ == "__main__":
    ids = sorted(rid for rid, r in R.items() if rid not in SKIP and clean_path(r).is_file() and rx.search(clean_path(r).read_text(errors="replace")))
    from collections import Counter; Cn = Counter()
    with ProcessPoolExecutor(12) as ex, open(LANE / ("results/t3g.jsonl" if NAME == "gameWork" else "results/t3_%s.jsonl" % NAME), "w") as fh:
        for rec in ex.map(one, ids):
            fh.write(json.dumps(rec) + "\n"); Cn[("ok:" + rec["mode"]) if rec.get("ok") else ("refused" if rec.get("refused") else "miss")] += 1
    print(len(ids), dict(Cn))
