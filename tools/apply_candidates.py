#!/usr/bin/env python3
"""Land candidate files produced outside the sweep machinery (agent lanes, experiments) the same
way a sweep would: verify each through tools/verify.py, copy the exact ones into src/, journal
every verdict in ledger/sweeps/<transform>.jsonl (in_sha/out_sha/outcome, resumable).

    python3 tools/apply_candidates.py <dir> --transform t9_labelcall [--workers 4] [--dry-run]

<dir> holds <container>/<basename>.c candidates.  A candidate identical to the current src text
is 'noop'; one that is not exact is 'mismatch' (nothing written); an exact one replaces src/ and
is 'applied'.  Touched windows still need the window gate afterwards (tools/build/gate_all.py).
"""
import argparse, json, sys, time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, LEDGER, rows, append_jsonl, sha_text, clean_path
from verify import verify

INCLUDE = ROOT / "include"

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("dir"); ap.add_argument("--transform", required=True); ap.add_argument("--workers", type=int, default=4)
    ap.add_argument("--dry-run", action="store_true")
    a = ap.parse_args()
    by = {}
    for r in rows():
        by[(r["container"], Path(r["c_path"]).name)] = r
    cands = sorted(Path(a.dir).glob("*/*.c"))
    journal = LEDGER / "sweeps" / f"{a.transform}.jsonl"
    def one(p):
        r = by.get((p.parent.name, p.name))
        if not r: return {"candidate": str(p.relative_to(ROOT)), "outcome": "unknown-row"}
        cur = clean_path(r).read_text(errors="replace"); new = p.read_text(errors="replace")
        rec = {"id": r["id"], "transform": a.transform, "in_sha": sha_text(cur), "size": r["size"], "source": str(Path(a.dir).relative_to(ROOT)) if Path(a.dir).is_relative_to(ROOT) else a.dir}
        if new == cur: return dict(rec, outcome="noop")
        v = verify(r, p.resolve(), include_root=INCLUDE)   # the scorer runs in the gate root: absolute paths only
        rec.update({"exact": v.get("exact"), "status": v.get("status"), "class": v.get("class"), "total": v.get("total"), "secs": v.get("secs")})
        if v.get("exact"):
            if not a.dry_run:
                clean_path(r).write_text(new)
            return dict(rec, outcome="applied", out_sha=sha_text(new), lines_delta=new.count("\n") - cur.count("\n"))
        return dict(rec, outcome="mismatch" if v.get("status") == "ok" else "build-failed", err=(v.get("err") or "")[:200].replace(str(ROOT), "<repo>"))
    tally = {}; t0 = time.time()
    with ThreadPoolExecutor(max_workers=a.workers) as ex:
        for rec in ex.map(one, cands):
            rec["at"] = time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())
            if not a.dry_run: append_jsonl(journal, rec)
            tally[rec["outcome"]] = tally.get(rec["outcome"], 0) + 1
            print(f"{rec.get('id', rec.get('candidate')):32} {rec['outcome']:12} {rec.get('class') or ''} {rec.get('total') if rec.get('total') is not None else ''}")
    print(f"done {len(cands)} in {time.time()-t0:.0f}s: {tally}" + (" (dry run: nothing written)" if a.dry_run else ""))

if __name__ == "__main__":
    main()
