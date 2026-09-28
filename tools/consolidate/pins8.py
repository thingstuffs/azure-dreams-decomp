"""pins8.py: pin effect check for every draft8/ row that carries pins.  For each pin alone and all together: erase
   it in the OLD (src, live include) and NEW (draft8, inc_full) text and compare the two cc1 listings.  Identical
   for every subset = the phase-8 respell changes no pin's effect, so it frees none.  A subset whose listings
   differ is a candidate freed pin (then scored with verify)."""
import json, sys
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import listing, row_index, REPO
import kitlib
LANE = Path(__file__).resolve().parent.parent; R = row_index()
strip = lambda s: [l for l in (s or "").splitlines() if not l.lstrip().startswith((".file", "#"))]
def one(rid):
    old = (REPO / "src" / (rid + ".c")).read_text(errors="replace"); new = (LANE / "draft8" / (rid + ".c")).read_text()
    so, sn = kitlib.sites(old), kitlib.sites(new)
    if not sn: return None
    r = dict(R.get(rid) or {"id": rid, "cfg": "2.7.2-cdk"}); r["kind"] = "overlay"
    if len(so) != len(sn): return {"id": rid, "pins": len(sn), "error": "site count differs %d/%d" % (len(so), len(sn))}
    subs = [[i] for i in range(len(sn))] + ([list(range(len(sn)))] if len(sn) > 1 else [])
    diff = []
    for sub in subs:
        a = listing(r, kitlib.erase(old, [so[i] for i in sub])); b = listing(r, kitlib.erase(new, [sn[i] for i in sub]), include=LANE / "inc_full")
        if a is None or b is None or strip(a) != strip(b): diff.append((sub, a is None, b is None))
    return {"id": rid, "pins": len(sn), "subsets": len(subs), "differs": diff}
if __name__ == "__main__":
    ids = sorted(str(p.relative_to(LANE / "draft8"))[:-2] for p in (LANE / "draft8").rglob("*.c"))
    n = 0
    with ProcessPoolExecutor(14) as ex, open(LANE / "results/pins8.jsonl", "w") as fh:
        for o in ex.map(one, ids, chunksize=4):
            if o is None: continue
            n += 1; fh.write(json.dumps(o) + "\n")
            if o.get("differs") or o.get("error"): print(o)
    print(n, "pinned rows checked")
