"""check10old.py: every `opt` manifest row checked against the CURRENT live include (TYPES_INC=include): the sample
   (--no-hdr) lands them before game_work.h changes.  -> results/opt_oldhdr10.jsonl"""
import os, sys, json
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import REPO, row_index
os.environ["TYPES_INC"] = str(REPO / "include")
from check import check
from concurrent.futures import ProcessPoolExecutor
LANE = Path(__file__).resolve().parent.parent; R = row_index()
def one(rid):
    c = check(R[rid], (LANE / "cand10" / (rid + ".c")).read_text())
    return {"id": rid, "listing": c.get("listing"), "score": c.get("score"), "exact": bool((c.get("score") or {}).get("exact"))}
if __name__ == "__main__":
    ids = [l.split("\t")[0] for l in open(LANE / "cand10/MANIFEST.tsv") if not l.startswith("#") and l.rstrip("\n").split("\t")[4].startswith("opt")]
    with ProcessPoolExecutor(14) as ex, open(LANE / "results/opt_oldhdr10.jsonl", "w") as fh:
        res = list(ex.map(one, ids, chunksize=2))
        for r in res: fh.write(json.dumps(r) + "\n")
    print(len(res), "opt rows", sum(r["exact"] for r in res), "exact against the live include;", [r for r in res if not r["exact"]][:5])
