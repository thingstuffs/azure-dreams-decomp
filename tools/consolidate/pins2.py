"""pins2.py: for every staged cand2 row that still carries pin sites, erase each pin alone (and all together)
   in the MIGRATED text and in the tree text; a pin whose erasure is exact on the migrated text only is made
   removable by the type change.  -> results/pins2.jsonl"""
import json, sys, os
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import *
from check import inline_and_respell
import kitlib
LANE_ = Path(__file__).resolve().parent.parent
R = row_index()
recs = [json.loads(l) for l in open(LANE_ / "results" / os.environ.get("PINRES", "p2_multi.jsonl"))]
todo = []
for r in recs:
    if not r.get("ok"): continue
    cand = (LANE_ / os.environ.get("PINCAND", "cand2") / r["path"]).read_text()
    if kitlib.sites(cand): todo.append((r["id"], r["path"]))
def exact(row, text):
    v = kitlib.score_at(row, text); return bool(v.get("exact")), v.get("total")
def one(job):
    rid, path = job; row = R[rid]
    cand = (LANE_ / os.environ.get("PINCAND", "cand2") / path).read_text(); tree = clean_path(row).read_text()
    cs, ts = kitlib.sites(cand), kitlib.sites(tree)
    out = {"id": rid, "pins": len(cs), "cfg": row["cfg"], "hits": []}
    subsets = [[s] for s in cs] if len(cs) > 1 else []
    subsets.append(list(cs))
    for sub in subsets:
        e_c = inline_and_respell(kitlib.erase(cand, sub))
        ok_c, tot_c = exact(row, e_c)
        if ok_c:
            # the same pin(s) erased in the tree text (matched by line text)
            keys = {(s[1], s[2], s[6]) for s in sub}
            tsub = [s for s in ts if (s[1], s[2], s[6]) in keys]
            ok_t = exact(row, kitlib.erase(tree, tsub))[0] if len(tsub) == len(sub) else None
            out["hits"].append({"erased": [str(s)[:160] for s in sub], "tree_also_exact": ok_t, "text": e_c if len(sub) == len(cs) else None})
    return out
if __name__ == "__main__":
    print(len(todo), "pinned migrated rows")
    with ProcessPoolExecutor(6) as ex, open(LANE_ / "results" / os.environ.get("PINOUT", "pins2.jsonl"), "w") as fh:
        for o in ex.map(one, todo):
            fh.write(json.dumps(o) + "\n")
            if o["hits"]: print(o["id"], o["pins"], [(h["erased"][0][:70], h["tree_also_exact"]) for h in o["hits"]])
