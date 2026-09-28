"""listing9.py [all|draft|IDS] [OUT]: cc1 listing identity at each row's cfg: OLD = src + live include/, NEW = draft9
   text (else src) + lane inc_full/ (complete post-apply include tree: globals.h without D_80084808, sound_volume.h),
   the readable name volumeScale spelled D_80084808 in both text and header (ccproc does it after cc1), .file lines
   and `.extern` sizes of the respelled symbols compared after absolute-address normalisation."""
import json, sys, re, os
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import listing, row_index, REPO
LANE = Path(__file__).resolve().parent.parent
R = row_index()
INC = LANE / "inc_full_d"          # inc_full with volumeScale spelled D_80084808
strip = lambda s: [l for l in (s or "").splitlines() if not l.lstrip().startswith((".file", "#"))]
def absn(lines):
    f = lambda m: "0x%08X" % (int(m.group(2), 16) + int(m.group(3) or 0))
    return [re.sub(r"\b(D|func)_([0-9A-F]{8})([+-]\d+)?", f, l) for l in lines if not l.lstrip().startswith(".extern")]
def one(rid):
    src = REPO / "src" / (rid + ".c")
    if not src.is_file(): return {"id": rid, "missing": True}
    r = dict(R.get(rid) or {"id": rid, "cfg": "2.7.2-cdk"}); r["kind"] = "overlay"
    d = LANE / "draft9" / (rid + ".c"); new = d.read_text() if d.is_file() else src.read_text(errors="replace")
    new = re.sub(r"\bvolumeScale\b", "D_80084808", new)
    a = listing(r, src.read_text(errors="replace")); b = listing(r, new, include=INC)
    rec = {"id": rid, "draft": d.is_file(), "old": a is not None, "new": b is not None}
    rec["identical"] = a is not None and b is not None and strip(a) == strip(b)
    if not rec["identical"] and a is not None and b is not None:
        rec["abs_identical"] = absn(strip(a)) == absn(strip(b))
        ea = sorted(l.strip() for l in strip(a) if l.strip().startswith(".extern")); eb = sorted(l.strip() for l in strip(b) if l.strip().startswith(".extern"))
        rec["extern_diff"] = [sorted(set(ea) - set(eb)), sorted(set(eb) - set(ea))]
        import difflib
        rec["diff"] = [l for l in difflib.unified_diff(strip(a), strip(b), lineterm="", n=0) if not l.startswith(("---", "+++", "@@"))][:8]
    return rec
if __name__ == "__main__":
    import shutil
    if INC.exists(): shutil.rmtree(INC)
    shutil.copytree(LANE / "inc_full", INC)
    for p in INC.rglob("*.h"): p.write_text(re.sub(r"\bvolumeScale\b", "D_80084808", p.read_text()))
    arg = sys.argv[1] if len(sys.argv) > 1 else "draft"
    ids = sorted(R) if arg == "all" else sorted(str(p.relative_to(LANE / "draft9"))[:-2] for p in (LANE / "draft9").rglob("*.c")) if arg == "draft" else [l.split()[0] for l in open(arg) if l.strip()]
    out = LANE / "results" / (sys.argv[2] if len(sys.argv) > 2 else "l9_%s.jsonl" % arg)
    n = same = 0; bad = []
    with ProcessPoolExecutor(14) as ex, open(out, "w") as fh:
        for rec in ex.map(one, ids, chunksize=8):
            fh.write(json.dumps(rec) + "\n"); n += 1; same += rec.get("identical", False)
            if not rec.get("identical"): bad.append(rec)
    print(n, "ids", same, "identical")
    for b in bad[:40]: print("  ", json.dumps({k: b.get(k) for k in ("id", "draft", "old", "new", "abs_identical", "extern_diff", "diff")})[:400])
