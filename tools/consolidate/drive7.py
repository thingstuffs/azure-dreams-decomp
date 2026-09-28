"""drive7.py [--only ids] -> results/p7_floor.jsonl, $CANDDIR/<container>/<file>.c (+ .base_sha)
   D_800E296C (consolidate scalar spec) + D_800E2970 (room.py) onto shared/dungeon_floor.h, one text per row."""
import json, sys, hashlib, re, os
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import *
import consolidate as C, room
from check import check
LANE_ = Path(__file__).resolve().parent.parent
O296 = C.load(LANE_ / "objects/D_800E296C.json")
busy = set(l.strip() for l in open(LANE_ / "BUSY_ROWS5.txt") if l.strip())
R = row_index()
ONLY = set(sys.argv[sys.argv.index("--only") + 1].split(",")) if "--only" in sys.argv else None
ids = [json.loads(l)["id"] for l in open(LANE_ / "census/c800E29.jsonl")]
ids = [i for i in dict.fromkeys(ids) if i in R and i not in busy and (ONLY is None or i in ONLY)]
def one(rid):
    r = R[rid]; src = clean_path(r); t = src.read_text(errors="replace")
    sha = hashlib.sha256(src.read_bytes()).hexdigest()
    code = "".join(t[a:b] for a, b in C.code_spans(t))
    has = {s for s in ("D_800E296C", "D_800E2970") if re.search(r"\b%s\b" % s, code)}
    if not has: return {"id": rid, "refused": "no code reference"}
    n, notes = t, []
    if "D_800E296C" in has:
        n2, why = C.rewrite(n, O296)
        if n2 is None: return {"id": rid, "refused": "D_800E296C: " + why, "present": sorted(has)}
        n = n2; notes.append("296C: " + why)
    if "D_800E2970" in has:
        n2, why = room.rewrite(n)
        if n2 is None: return {"id": rid, "refused": "D_800E2970: " + why, "present": sorted(has)}
        n = n2; notes.append("2970: " + why)
    rec = check(r, n, score=True); rec.update(note=" | ".join(notes), src_sha=sha, present=sorted(has))
    if (rec.get("score") or {}).get("exact"):
        d = LANE_ / os.environ.get("CANDDIR", "cand7f") / r["container"]; d.mkdir(parents=True, exist_ok=True)
        (d / src.name).write_text(n); (d / (src.name + ".base_sha")).write_text(sha)
        rec.update(ok=True, path="%s/%s" % (r["container"], src.name))
    else: rec["ok"] = False
    return rec
if __name__ == "__main__":
    out = LANE_ / "results" / ("p7_floor%s.jsonl" % os.environ.get("TAG", ""))
    from collections import Counter; Cn = Counter()
    with ProcessPoolExecutor(6) as ex, open(out, "w") as fh:
        for rec in ex.map(one, ids):
            fh.write(json.dumps(rec) + "\n")
            Cn["ok" if rec.get("ok") else ("refused" if rec.get("refused") else "miss")] += 1
    print(dict(Cn))
