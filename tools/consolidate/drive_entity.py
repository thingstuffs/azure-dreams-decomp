"""drive_entity.py [--only ids] [--ovr name=ctype:signed,...] -> results/p5_entity<TAG>.jsonl, cand5/<container>/<file>.c
   Rows whose text uses Rec_D_800E3D7C: entity.rewrite onto Entity (include/shared/entity.h); ok = verify.py exact
   (or a SLUS relocation-only difference, flagged rebaseline_slus)."""
import json, sys, hashlib, re, os
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import *
import entity
from check import check
LANE_ = Path(__file__).resolve().parent.parent
RECNAMES = os.environ.get("RECS", "Rec_D_800E3D7C").split(",")
ONLY = set(sys.argv[sys.argv.index("--only") + 1].split(",")) if "--only" in sys.argv else None
OVR = {}
if "--ovr" in sys.argv:
    for kv in sys.argv[sys.argv.index("--ovr") + 1].split(","):
        k, v = kv.split("="); ty, sg = v.split(":"); OVR[k] = (ty.replace("_", " "), sg == "1")
busy = set(l.strip() for l in open(LANE_ / "BUSY_ROWS5.txt") if l.strip())
R = row_index()
ids = [rid for rid, r in R.items() if rid not in busy and (ONLY is None or rid in ONLY)
       and clean_path(r).is_file() and any(n in clean_path(r).read_text(errors="replace") for n in RECNAMES)]
INC = os.environ.get("TYPES_INC")
def one(rid):
    r = R[rid]; src = clean_path(r); t = src.read_text(errors="replace")
    sha = hashlib.sha256(src.read_bytes()).hexdigest()
    new, notes = t, []
    for rn in RECNAMES:
        if rn not in new: continue
        n2, note = entity.rewrite(new, str(REPO / "include/records" / (rn + ".h")), OVR or None, rn)
        if n2 is None: return {"id": rid, "refused": "%s: %s" % (rn, note)}
        new = n2; notes.append("%s: %s" % (rn, note))
    note = " | ".join(notes)
    tries = []
    fv, fnote = entity.fold_views(new, OVR or None)
    if fv is not None: tries.append((fv, note + " | views: " + fnote, [["EntityRec", "natural"], ["EntityRec", "views"]]))
    tries.append((new, note, [["EntityRec", "natural"]]))
    for new, note, plan in tries:
        rec = check(r, new, score=True); rec.update(note=note, src_sha=sha, plan=plan)
        if not (rec.get("score") or {}).get("exact") and rec.get("abs_listing") == "identical" and rec.get("listing") != "build-error":
            rec["rebaseline_slus"] = True
        if (rec.get("score") or {}).get("exact") or rec.get("rebaseline_slus"): break
    ok = (rec.get("score") or {}).get("exact") or rec.get("rebaseline_slus")
    rec["ok"] = bool(ok)
    if ok and not os.environ.get("NOSTAGE"):
        d = LANE_ / os.environ.get("CANDDIR", "cand5") / r["container"]; d.mkdir(parents=True, exist_ok=True)
        (d / src.name).write_text(new); (d / (src.name + ".base_sha")).write_text(sha)
        rec["path"] = "%s/%s" % (r["container"], src.name)
    return rec
if __name__ == "__main__":
    out = LANE_ / "results" / ("p5_entity%s.jsonl" % os.environ.get("TAG", ""))
    from collections import Counter; Cn = Counter()
    with ProcessPoolExecutor(6) as ex, open(out, "w") as fh:
        for rec in ex.map(one, ids):
            fh.write(json.dumps(rec) + "\n"); Cn["ok" if rec.get("ok") else ("refused" if rec.get("refused") else "miss")] += 1
    print(out.name, len(ids), dict(Cn))
