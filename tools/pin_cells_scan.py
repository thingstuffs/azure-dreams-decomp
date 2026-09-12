#!/usr/bin/env python3
"""Admissible cells per pinned row, and the pins that are dead at one of them.

    python3 tools/pin_cells_scan.py scan  [--workers 8] [--only id,id]     # resumable
    python3 tools/pin_cells_scan.py build <dir>                            # CDK hits -> candidates
    python3 tools/apply_candidates.py <dir> --transform t30_cellpins --workers 1 --cells <dir>/cells.jsonl

A row's recorded cell is often only one of several at which its PINNED text is exact (2026-09-12:
96% of rows recorded at 2.8.1-G0 are also exact at 2.7.2-cdk-G0). Every pin search so far scored at
the recorded cell, so a pin that is dead at another admissible cell was never seen.

`scan`, stage 1: the row's admissible cells E (pinned text exact there; the recorded cell
excluded). Stage 2, when E is not empty: erase each pin alone and score over E in one multi-cell
call; on exact, name the first exact cell. One line per row in ledger/pins_cells_admissible.jsonl,
keyed on (id, in_sha): a row whose text changed is scanned again.

`build`: for every row whose text is unchanged since its scan and that has a pin dead at a CDK cell,
the single erasure goes to <dir>/<container>/<name>.c (+ .base_sha) and the cell to
<dir>/cells.jsonl (the cell with most hits, one keeping the row's -G0 setting first). Landing
rechecks tools/pin_cells_land.py rules 1-2; T2 at the new cell then does the greedy follow-up.
Hits at 2.95.2 / 2.91.66 (1999 compilers, after the game shipped) are recorded, never built.
"""
import argparse, collections, json, sys, tempfile, threading, time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, LEDGER, STOCK_CELLS, rows, clean_path, sha_text, read_jsonl
from verify import verify
from pin_census import sites_of
from pin_sites import erase_many

OUT = LEDGER / "pins_cells_admissible.jsonl"
INC = f"-I{(ROOT / 'include').resolve()}"
CELLS = sorted(STOCK_CELLS) + [c + "-G0" for c in sorted(STOCK_CELLS)]
CDK = ("2.7.2-cdk", "2.7.2-cdk-G0")


def score(row, cfg, text):
    with tempfile.TemporaryDirectory() as td:
        f = Path(td) / Path(row["c_path"]).name
        f.write_text(text)
        return verify(dict(row, cfg=cfg), f)


def scan_row(row):
    t0 = time.time()
    text = clean_path(row).read_text(errors="replace")
    cells = [c for c in CELLS if c != row["cfg"] and score(row, f"{c} {INC}", text).get("exact")]
    hits, sites = [], sites_of(text)
    if cells:
        multi = ",".join(f"{c} {INC}" for c in cells)
        for i, s in enumerate(sites):
            cand = erase_many(text, [s], clean_notes=True)
            if not score(row, multi, cand).get("exact"):
                continue
            for c in cells:
                if score(row, f"{c} {INC}", cand).get("exact"):
                    hits.append({"site": i, "macro": s[1], "cell": c})
                    break
    return {"id": row["id"], "cfg": row["cfg"], "in_sha": sha_text(text), "pins": len(sites),
            "cells": cells, "hits": hits, "secs": round(time.time() - t0, 1)}


def latest():
    out = {}
    if OUT.exists():
        for r in read_jsonl(OUT):
            out[r["id"]] = r
    return out


def cmd_scan(a):
    done = latest()
    keep = set(a.only.split(",")) if a.only else None
    todo = []
    for r in rows():
        if r["container"] == "slus" or not r.get("stock") or (keep and r["id"] not in keep):
            continue
        p = clean_path(r)
        if not p.exists():
            continue
        text = p.read_text(errors="replace")
        prev = done.get(r["id"])
        if sites_of(text) and not (prev and prev["in_sha"] == sha_text(text) and prev["cfg"] == r["cfg"]):
            todo.append(r)
    todo.sort(key=lambda r: r.get("size") or 0)
    print(f"{len(todo)} rows to scan", flush=True)
    lock, n, nh, t0 = threading.Lock(), 0, 0, time.time()
    with ThreadPoolExecutor(a.workers) as ex:
        for rec in ex.map(scan_row, todo):
            with lock, OUT.open("a") as f:
                f.write(json.dumps(rec) + "\n")
            n += 1; nh += len(rec["hits"])
            if n % 50 == 0:
                print(f"{n}/{len(todo)} hits {nh} {time.time() - t0:.0f}s", flush=True)
    print(f"done {n} hits {nh} {time.time() - t0:.0f}s")


def cmd_build(a):
    by = {r["id"]: r for r in rows()}
    d = Path(a.dir); d.mkdir(parents=True, exist_ok=True)
    cells, stale, other = [], 0, 0
    for rid, rec in sorted(latest().items()):
        hits = [h for h in rec["hits"] if h["cell"] in CDK]
        other += len(rec["hits"]) - len(hits)
        if not hits or rid not in by:
            continue
        row = by[rid]; text = clean_path(row).read_text(errors="replace")
        if sha_text(text) != rec["in_sha"] or row["cfg"] != rec["cfg"]:
            stale += 1; continue
        g0 = "-G0" in row["cfg"]; n = collections.Counter(h["cell"] for h in hits)
        cell = max(n, key=lambda c: (n[c], ("-G0" in c) == g0))
        site = next(h["site"] for h in hits if h["cell"] == cell)
        c, name = rid.split("/"); (d / c).mkdir(exist_ok=True)
        (d / c / (name + ".c")).write_text(erase_many(text, [sites_of(text)[site]], clean_notes=True))
        (d / c / (name + ".c.base_sha")).write_text(rec["in_sha"])
        cells.append({"id": rid, "to": cell, "hits": n[cell]})
    (d / "cells.jsonl").write_text("".join(json.dumps(x) + "\n" for x in cells))
    print(f"rows {len(cells)}, hit pins at the chosen cell {sum(x['hits'] for x in cells)}, "
          f"stale {stale}, non-CDK hits recorded, not built {other}")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("scan"); s.add_argument("--workers", type=int, default=8); s.add_argument("--only")
    b = sub.add_parser("build"); b.add_argument("dir")
    a = ap.parse_args()
    (cmd_scan if a.cmd == "scan" else cmd_build)(a)


if __name__ == "__main__":
    main()
