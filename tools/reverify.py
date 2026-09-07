#!/usr/bin/env python3
"""Re-verify every row whose clean text differs from the pinned raw text -> ledger/reverify.jsonl."""
import json, sys, time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, LEDGER, rows, append_jsonl, sha_text, raw_path
from verify import verify, gate_fallback
INCLUDE = ROOT / "include"
def one(r):
    cp = ROOT / "src" / r["container"] / Path(r["c_path"]).name
    v = gate_fallback(r, verify(r, cp, include_root=INCLUDE), raw=False)   # scorer, then the window gate over src/
    return {"id": r["id"], "exact": v.get("exact"), "status": v.get("status"), "class": v.get("class"), "err": (v.get("err") or "")[:160], "src_sha": sha_text(cp.read_text(errors="replace")),
            **({k: v[k] for k in ("proof", "gate", "window", "scorer_class", "scorer_total") if k in v})}
def main():
    workers = int(sys.argv[1]) if len(sys.argv) > 1 else 6
    todo = []
    for r in rows():
        if not r["exists"] or not r["stock"]: continue
        cp = ROOT / "src" / r["container"] / Path(r["c_path"]).name; up = raw_path(r)
        if cp.exists() and cp.read_bytes() != up.read_bytes(): todo.append(r)
    out = LEDGER / "reverify.jsonl"; out.write_text("")
    print(f"{len(todo)} transformed rows to re-verify", flush=True); t0 = time.time(); n = 0; bad = 0
    with ThreadPoolExecutor(max_workers=workers) as ex:
        for rec in ex.map(one, todo):
            append_jsonl(out, rec); n += 1; bad += 0 if (rec["exact"] or (rec["status"] == "ok" and rec["exact"] is None)) else 1
            if n % 500 == 0: print(f"{n}/{len(todo)} {time.time()-t0:.0f}s not-exact {bad}", flush=True)
    print(f"done {n} in {time.time()-t0:.0f}s: not-exact {bad}")
if __name__ == "__main__": main()
