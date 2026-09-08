#!/usr/bin/env python3
"""Apply one transform to every eligible row, verify each result, journal everything.

    python3 tools/sweep.py t1_boiler [--container X] [--sample N] [--limit N] [--workers 6] [--only id,id]

Input for a row = its current clean file (src/<container>/<name>.c) if present, else the pinned
upstream file.  A verified result is written to the clean file; a refusal or mismatch writes
nothing.  Journal: ledger/sweeps/<transform>.jsonl (resumable: a row whose input sha is already
journalled is skipped).
"""
import argparse, json, random, sys, tempfile, time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, LEDGER, rows, read_jsonl, append_jsonl, sha_text, raw_path, parse_cfg, is_stock_cfg, set_row_cfg
from verify import verify
import xform

INCLUDE = ROOT / "include"

def _scrub(t):
    """Error text goes into a tracked journal: no absolute paths."""
    return (t or "").replace(str(ROOT), "<repo>").replace(str(Path.home()), "<home>")

import threading
_CFG_LOCK = threading.Lock()
_CFG = {}
def rows_cfg(row_id):
    """The registry's current cfg for a row (the sweep's row copy may already carry the override)."""
    if not _CFG:
        for r in rows(): _CFG[r["id"]] = r["cfg"]
    return _CFG.get(row_id)
def rows_cfg_prev(row_id):
    return _CFG.get(row_id)

def clean_path(row):
    return ROOT / "src" / row["container"] / Path(row["c_path"]).name

def current_text(row):
    p = clean_path(row)
    return (p if p.exists() else raw_path(row)).read_text(errors="replace"), p.exists()

def one(args):
    T, row, cen = args
    text, from_clean = current_text(row)
    rec = {"id": row["id"], "transform": T.name, "in_sha": sha_text(text), "from_clean": from_clean, "size": row["size"]}
    why = T.eligible(text, row, cen)
    if why:
        return dict(rec, outcome="refused", reason=why)
    info = {}
    try:
        if getattr(T, "needs_verify", False):
            def vf(cand, cfg=None):
                # cfg: try the candidate at another STOCK cell (a row whose pinned cell was an artefact of
                # its scaffolding); the plugin reports the winning cfg in info["cfg"] and the sweep records it
                with tempfile.TemporaryDirectory() as td:
                    p = Path(td) / Path(row["c_path"]).name
                    p.write_text(cand)
                    r2 = row if not cfg else dict(row, cfg=cfg, cell=parse_cfg(cfg)[0], flags=" ".join(parse_cfg(cfg)[1]))
                    return verify(r2, p, include_root=INCLUDE)
            new, info = T.apply_verified(text, row, cen, vf)
        else:
            new = T.apply(text, row, cen)
    except Exception as e:  # a plugin bug is a refusal, never a crash of the sweep
        return dict(rec, outcome="refused", reason=f"apply error: {e!r}"[:200])
    rec.update(info)
    if new is not None and info.get("cfg") and info["cfg"] != row["cfg"]:
        if not is_stock_cfg(info["cfg"]):
            return dict(rec, outcome="refused", reason=f"non-stock cfg {info['cfg']}")
        row = dict(row, cfg=info["cfg"], cell=parse_cfg(info["cfg"])[0], flags=" ".join(parse_cfg(info["cfg"])[1]))
    if new is None and info.get("refused"):
        return dict(rec, outcome="refused", reason="; ".join(info["refused"])[:300])
    if new is None or new == text:
        return dict(rec, outcome="noop")
    with tempfile.TemporaryDirectory() as td:
        p = Path(td) / Path(row["c_path"]).name
        p.write_text(new)
        v = verify(row, p, include_root=INCLUDE)
    rec.update({"exact": v.get("exact"), "status": v.get("status"), "class": v.get("class"), "total": v.get("total"), "secs": v.get("secs"), "err": _scrub(v.get("err"))})
    if v.get("exact"):
        cp = clean_path(row); cp.parent.mkdir(parents=True, exist_ok=True); cp.write_text(new)
        if info.get("cfg") and rec.get("cfg_was") is None and info["cfg"] != rows_cfg(row["id"]):
            with _CFG_LOCK:      # the row database is read-modify-written: one correction at a time
                set_row_cfg(row["id"], info["cfg"], note=f"{T.name}: exact at this stock cell without scaffolding")
            rec["cfg_was"] = rows_cfg_prev(row["id"])
        return dict(rec, outcome="applied", out_sha=sha_text(new), lines_delta=new.count("\n") - text.count("\n"))
    return dict(rec, outcome="mismatch" if v.get("status") == "ok" else "build-failed")

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("transform"); ap.add_argument("--container"); ap.add_argument("--sample", type=int); ap.add_argument("--limit", type=int)
    ap.add_argument("--workers", type=int, default=6); ap.add_argument("--seed", type=int, default=1); ap.add_argument("--only")
    ap.add_argument("--force", action="store_true", help="re-run even when the row's current text is already journalled (a row whose src was reverted to a pre-transform text)")
    a = ap.parse_args()
    T = xform.load(a.transform)
    cen = {c["id"]: c for c in read_jsonl(LEDGER / "census.jsonl")}
    base = {b["id"]: b for b in read_jsonl(LEDGER / "baseline.jsonl")}
    rs = [r for r in rows() if r["exists"] and r["stock"] and (not a.container or r["container"] == a.container)]
    rs = [r for r in rs if base.get(r["id"], {}).get("exact") is True or (r["kind"] == "slus" and base.get(r["id"], {}).get("status") == "ok")]
    if a.only: keep = set(a.only.split(",")); rs = [r for r in rs if r["id"] in keep]
    if a.sample: random.seed(a.seed); rs = random.sample(rs, min(a.sample, len(rs)))
    if a.limit: rs = rs[:a.limit]
    (LEDGER / "sweeps").mkdir(exist_ok=True)
    journal = LEDGER / "sweeps" / f"{T.name}.jsonl"
    prior = read_jsonl(journal)
    done = {(j["id"], j["in_sha"]) for j in prior if j.get("outcome") in ("applied", "noop", "refused")}
    done |= {(j["id"], j["out_sha"]) for j in prior if j.get("outcome") == "applied" and j.get("out_sha")}   # already transformed
    jobs = []
    for r in rs:
        text, _ = current_text(r)
        if a.force or (r["id"], sha_text(text)) not in done: jobs.append((T, r, cen.get(r["id"], {})))
    print(f"{T.name}: {len(jobs)} rows to process ({len(rs) - len(jobs)} already journalled)", flush=True)
    t0 = time.time(); n = 0; tally = {}
    with ThreadPoolExecutor(max_workers=a.workers) as ex:
        for rec in ex.map(one, jobs):
            rec["at"] = time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()); append_jsonl(journal, rec); n += 1
            tally[rec["outcome"]] = tally.get(rec["outcome"], 0) + 1
            if n % 200 == 0: print(f"{n}/{len(jobs)} {time.time()-t0:.0f}s {tally}", flush=True)
    print(f"done {n} in {time.time()-t0:.0f}s: {tally}")

if __name__ == "__main__":
    main()
