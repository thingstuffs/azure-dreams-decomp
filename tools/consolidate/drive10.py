"""drive10.py [--nocheck] [IDS...]: fold10 over the views10 census rows (or IDS) on the current src text (or a
   draft10/ text when present with DRAFT=1); check() each changed text (listing + verify.py byte score against the
   lane inc/).  -> results/f10.jsonl, stage10/<row>.c for exact rows."""
import json, re, sys, hashlib, collections, os
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import row_index, REPO
from fold10 import fold
LANE = Path(__file__).resolve().parent.parent; R = row_index()
NOCHECK = "--nocheck" in sys.argv
SKIP = {"slus/code", "slus/code2", "slus/w_8003E34C", "dungeon/func_800AFA68", "slus/w_8004D5D0"}
OUT = os.environ.get("OUT", "f10")
def one(rid):
    src = REPO / "src" / (rid + ".c"); t = src.read_text(errors="replace")
    new, notes, ref = fold(t)
    rec = {"id": rid, "notes": notes, "refusals": ref, "src_sha": hashlib.sha256(src.read_bytes()).hexdigest()}
    if new is None or new == t: rec["ok"] = False; rec["unchanged"] = True; return rec
    if NOCHECK: rec["ok"] = None; return rec
    from check import check
    c = check(R[rid], new)
    ok = bool((c.get("score") or {}).get("exact"))
    rebase = (not ok) and c.get("abs_listing") == "identical"
    rec.update(listing=c.get("listing"), score=c.get("score"), err=(c.get("err") or "")[-200:], diff=c.get("diff"), ok=ok or rebase, rebaseline=rebase)
    if rec["ok"]:
        p = LANE / "stage10" / OUT / (rid + ".c"); p.parent.mkdir(parents=True, exist_ok=True); p.write_text(new)
        rec["cand_sha"] = hashlib.sha256(new.encode()).hexdigest()
    return rec
if __name__ == "__main__":
    ids = [a for a in sys.argv[1:] if not a.startswith("--")]
    if not ids: ids = [json.loads(l)["id"] for l in open(LANE / "census/views10.jsonl")]
    ids = [i for i in ids if i in R and i not in SKIP]
    C = collections.Counter(); REF = collections.Counter()
    with ProcessPoolExecutor(14) as ex, open(LANE / "results" / (OUT + ".jsonl"), "w") as fh:
        for rec in ex.map(one, ids, chunksize=2):
            fh.write(json.dumps(rec) + "\n")
            C["unchanged" if rec.get("unchanged") else ("changed" if rec["ok"] is None else ("ok" if rec["ok"] else ("build-error" if rec.get("listing") == "build-error" else "miss")))] += 1
            for r in rec["refusals"]: REF[re.sub(r"\b[a-z_][a-z_0-9]*\b(?=:)", "P", re.sub(r"0x[0-9A-F]+", "X", r))[:70]] += 1
    print(len(ids), dict(C))
    for k, v in REF.most_common(25): print("  %4d %s" % (v, k))
