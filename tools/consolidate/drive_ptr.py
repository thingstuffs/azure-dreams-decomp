"""drive_ptr.py OBJ [--only ids] -> results/p3_ptr_<OBJ>.jsonl, cand3/<container>/<file>.c
   Rows of the tree whose text holds a local pointer to the (already consolidated) object: consolidate.rewrite_pointers
   mode direct (pointer removed, var.field), then mode typed (Type *p = &var; p->field).  ok = verify.py exact."""
import json, sys, hashlib, re, os
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import *
import consolidate as C
from check import check
LANE_ = Path(__file__).resolve().parent.parent
NAME = sys.argv[1]; OBJ = C.load(LANE_ / "objects" / (NAME + ".json"))
ONLY = set(sys.argv[sys.argv.index("--only") + 1].split(",")) if "--only" in sys.argv else None
busy = set(l.strip() for l in open(LANE_ / "BUSY_ROWS3.txt") if l.strip())
R = row_index()
rx = re.compile(r"=\s*[^;=]*&\s*\(?\s*%s\b" % OBJ["var"])
ids = [rid for rid, r in R.items() if rid not in busy and (ONLY is None or rid in ONLY)
       and clean_path(r).is_file() and rx.search(clean_path(r).read_text(errors="replace"))]
def one(rid):
    r = R[rid]; src = clean_path(r); t = src.read_text(errors="replace")
    sha = hashlib.sha256(src.read_bytes()).hexdigest(); last = None; why = []
    for mode in ("direct", "typed"):
        new, note = C.rewrite_pointers(t, OBJ, mode)
        if new is None: why.append("%s: %s" % (mode, note)); continue
        rec = check(r, new, score=True); rec.update(mode=mode, note=note, src_sha=sha, why=why); last = rec
        if (rec.get("score") or {}).get("exact"):
            d = LANE_ / "cand3" / r["container"]; d.mkdir(parents=True, exist_ok=True)
            (d / src.name).write_text(new); (d / (src.name + ".base_sha")).write_text(sha)
            rec.update(ok=True, path="%s/%s" % (r["container"], src.name), plan=[[NAME, "ptr-" + mode]]); return rec
    if last is None: return {"id": rid, "refused": "; ".join(why)}
    last["ok"] = False; return last
if __name__ == "__main__":
    out = LANE_ / "results" / ("p3_ptr_%s.jsonl" % NAME)
    from collections import Counter; Cn = Counter()
    with ProcessPoolExecutor(6) as ex, open(out, "w") as fh:
        for rec in ex.map(one, ids):
            fh.write(json.dumps(rec) + "\n"); Cn[("ok:" + rec["mode"]) if rec.get("ok") else ("refused" if rec.get("refused") else "miss")] += 1
    print(out.name, len(ids), dict(Cn))
