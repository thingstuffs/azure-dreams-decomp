"""drive6.py [--only ids] [--score] -> results/p6<TAG>.jsonl, cand6/<container>/<file>.c
   Phase 6 header-update rows: every row that includes shared/record_ptrs.h or shared/tile_object.h (TYPES_INC =
   the lane inc/, where record_ptrs.h points D_800E3D7C / D_800814A8 at struct EntityRec and TileObject ends at 0x40).
   Candidate = the row minus its `#include "records/Rec_D_800E3D7C.h"` / Rec_D_800814A8.h line when the name is
   otherwise only in comments; `#include "shared/entity.h"` added when the row then needs the complete type.
   ok = the cc1 listing (lane headers, ccproc names) equals the current src's (identical assembler input), or, with
   --score, verify.py exact.  Changed texts are staged with .base_sha; unchanged rows are header-verify rows."""
import json, sys, hashlib, re, os
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import *
from check import check
LANE_ = Path(__file__).resolve().parent.parent
ONLY = set(sys.argv[sys.argv.index("--only") + 1].split(",")) if "--only" in sys.argv else None
SCORE = "--score" in sys.argv
RECS = ("Rec_D_800E3D7C", "Rec_D_800814A8")
busy = set(l.strip() for l in open(LANE_ / "BUSY_ROWS6.txt") if l.strip())
R = row_index()
def wanted(t):
    return any(h in t for h in ('"shared/record_ptrs.h"', '"shared/tile_object.h"', '"records/Rec_D_800E3D7C.h"', '"records/Rec_D_800814A8.h"'))
ids = [rid for rid, r in R.items() if rid not in busy and (ONLY is None or rid in ONLY)
       and clean_path(r).is_file() and wanted(clean_path(r).read_text(errors="replace"))]
def strip_code(t):
    return re.sub(r"//[^\n]*", "", re.sub(r"/\*.*?\*/", "", t, flags=re.S))
def candidate(t):
    notes = []
    for rn in RECS:
        inc = '#include "records/%s.h"\n' % rn
        if inc in t:
            if re.search(r"\b%s\b" % rn, strip_code(t.replace(inc, ""))):
                return None, "%s used in code" % rn
            t = t.replace(inc, ""); notes.append("drop " + rn)
    return t, ", ".join(notes)
def add_entity(t):
    if '"shared/entity.h"' in t: return None
    m = re.search(r'^#include "shared/record_ptrs.h"[^\n]*\n', t, re.M)
    if not m: return None
    return t[:m.start()] + '#include "shared/entity.h"\n' + t[m.start():]
def one(rid):
    r = R[rid]; src = clean_path(r); t = src.read_text(errors="replace")
    sha = hashlib.sha256(src.read_bytes()).hexdigest()
    new, note = candidate(t)
    if new is None: new, note = t, "kept (%s)" % note     # header-verify the row as it stands
    rec = check(r, new, score=SCORE)
    if rec.get("listing") == "build-error":
        n2 = add_entity(new)
        if n2 is not None:
            rec2 = check(r, n2, score=SCORE)
            if rec2.get("listing") != "build-error":
                new, rec, note = n2, rec2, (note + ", " if note else "") + "add entity.h"
    rec.update(note=note, src_sha=sha, changed=(new != t))
    ok = (rec.get("score") or {}).get("exact") if SCORE else (rec.get("listing") == "identical" and rec.get("extern_sizes") == "same")
    if not ok and r.get("kind") == "slus" and rec.get("abs_listing") == "identical": rec["rebaseline_slus"] = True
    rec["ok"] = bool(ok)
    if ok and new != t and not os.environ.get("NOSTAGE"):
        d = LANE_ / os.environ.get("CANDDIR", "cand6") / r["container"]; d.mkdir(parents=True, exist_ok=True)
        (d / src.name).write_text(new); (d / (src.name + ".base_sha")).write_text(sha)
        rec["path"] = "%s/%s" % (r["container"], src.name)
    return rec
if __name__ == "__main__":
    out = LANE_ / "results" / ("p6%s.jsonl" % os.environ.get("TAG", ""))
    from collections import Counter; Cn = Counter()
    with ProcessPoolExecutor(int(os.environ.get("JOBS", "6"))) as ex, open(out, "w") as fh:
        for rec in ex.map(one, ids):
            fh.write(json.dumps(rec) + "\n"); Cn[("ok" if rec.get("ok") else ("refused" if rec.get("refused") else "miss")) + ("/changed" if rec.get("changed") else "")] += 1
    print(out.name, len(ids), dict(Cn))
