"""tidy137.py: collapse consolidate's pointer-cast chains on D_80013714 in cand7 texts; re-verify changed rows,
   keep a tidied text only when it verifies exact."""
import re, sys, json
from pathlib import Path
from concurrent.futures import ProcessPoolExecutor
sys.path.insert(0, str(Path(__file__).parent))
from cc import row_index
from check import check
LANE_ = Path(__file__).resolve().parent.parent; R = row_index()
T = r"(\w+(?: \w+)?)"
def tidy(t):
    t = re.sub(r"\(\*\(%s \*\)\(\(%s \*\)\(&D_80013714\)\)\)" % (T, T), r"(*(\1 *)&D_80013714)", t)
    t = re.sub(r"\(\(%s \*\)\(&D_80013714\)\)" % T, r"((\1 *)&D_80013714)", t)
    t = re.sub(r"\(\*\((?:u16|unsigned short) \*\)&D_80013714\)", "D_80013714", t)
    return t
def one(line):
    rid, path = line.split("\t")[:2]; p = LANE_ / "cand7" / path; t = p.read_text(); n = tidy(t)
    if n == t: return None
    rec = check(R[rid], n); ok = (rec.get("score") or {}).get("exact")
    if ok: p.write_text(n)
    return rid, ok
lines = [l for l in open(LANE_ / "cand7/MANIFEST.tsv") if not l.startswith("#") and "flags" in l.split("\t")[3]]
with ProcessPoolExecutor(6) as ex:
    for r in ex.map(one, lines):
        if r: print(*r)
