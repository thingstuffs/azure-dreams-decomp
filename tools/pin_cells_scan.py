#!/usr/bin/env python3
"""Admissible cells per pinned row, and the pins that are dead at one of them.

    python3 tools/pin_cells_scan.py scan  [--workers 8] [--only id,id]     # resumable
    python3 tools/pin_cells_scan.py strip [--workers 8]                    # rows pin-free at a cell
    python3 tools/pin_cells_scan.py build [--plausible] <dir>              # hits -> candidates
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
`build --plausible` also builds hits at the FSF 2.6.3 / 2.7.2 / 2.8.0 / 2.8.1 cells: the full scan
(2026-09-12) found most leftover hits at 2.8.0, from rows recorded at 2.8.1-G0 and even 2.7.2-cdk-G0 -
a row's pinned text is exact at several cells and the pins had picked one. Hits at 2.95.2 / 2.91.66
(1999 compilers, after the game shipped) are recorded, never built.
`scan --flags` / `build --flags` (2026-09-13): the same two stages over the recorded cell plus one of
FLAGS (the compiler never changes), ledger pins_flags_admissible.jsonl. The tree already records
about 200 rows with such flags. A flag pilot on 32 lane dead ends found 1 admissible hit; the full
scan found 212 pins dead at a flag variant in 150 rows (landed in round 11).
`scan --flags2` / `build --flags2`: the second set, FLAGS2 (the scheduling pair for the fences,
-mno-split-addresses for 2.8.x rows, flags that change 2.6.3/2.7.2 codegen), ledger
pins_flags2_admissible.jsonl; rows already carrying an optimization flag are skipped (no stacking).
`scan --stack` / `build --stack` (owner, 2026-09-13: stacking yes, capped): a row that carries exactly
one optimization flag may take one more from either set (at most two); ledger
pins_flags_stack_admissible.jsonl; STATUS counts the rows with two.
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
FLAGS = ["-O1", "-fno-schedule-insns", "-fno-schedule-insns2", "-fno-strength-reduce", "-fno-cse-skip-blocks",
         "-fno-rerun-cse-after-loop", "-fno-expensive-optimizations", "-fno-caller-saves"]
FLAGS_OUT = LEDGER / "pins_flags_admissible.jsonl"
# the second flag set (2026-09-13): flags that change 2.6.3/2.7.2/2.7.2-cdk codegen (all of these do on a
# probe TU; on 2.8.x+ only the scheduling pair, -mno-split-addresses and -mmips-as do), the scheduling
# pair aimed at ASM_SCHED_BARRIER fences, -mno-split-addresses at the address-split pins of 2.8.x rows
# (the switch exists from 2.8.0; the tree already records one row with it).  Rows whose cfg already
# carries an optimization flag are skipped: flags are not stacked.
FLAGS2 = ["-fno-schedule-insns -fno-schedule-insns2", "-fforce-addr", "-fno-force-mem", "-fno-thread-jumps",
          "-fno-cse-follow-jumps", "-fno-peephole", "-fno-function-cse", "-mno-split-addresses", "-mmips-as"]
FLAGS2_OUT = LEDGER / "pins_flags2_admissible.jsonl"
SPLIT_ADDRESSES = ("2.8.0", "2.8.1", "2.91.66", "2.95.2")


STACK_OUT = LEDGER / "pins_flags_stack_admissible.jsonl"
# measured inert (2026-09-13, the --flags2 ledger's first 834 rows, 5.1 CPU-h): admissible on 232-834 rows
# and not one hit.  Each admissible cell is compiled in every stage-2 erasure call, so they only cost.
INERT = {"-fno-peephole", "-fno-function-cse", "-fno-thread-jumps", "-fno-force-mem", "-mmips-as"}


def opt_flags(row):
    return [t for t in row["cfg"].replace("+", " ").split()[1:] if t.startswith(("-f", "-O", "-m"))]


def flag_pool(row, flags):
    if flags == 1:
        return [f"{row['cfg']} {F}" for F in FLAGS if F not in row["cfg"].split()]
    if flags == 3:
        # stacking (owner, 2026-09-13: yes, capped): a row carrying exactly one optimization flag may
        # take one more from either set, never a flag it already has, never -O1 on top of a flag
        have = set(opt_flags(row))
        head = row["cfg"].split()[0].replace("-G0", "")
        return [f"{row['cfg']} {F}" for F in dict.fromkeys(FLAGS + FLAGS2)
                if F not in INERT and not set(F.split()) & have and F != "-O1" and "-O1" not in have
                and not (F == "-mno-split-addresses" and not head.startswith(SPLIT_ADDRESSES))]
    head = row["cfg"].split()[0].replace("-G0", "")
    return [f"{row['cfg']} {F}" for F in FLAGS2
            if F not in INERT and not (F == "-mno-split-addresses" and not head.startswith(SPLIT_ADDRESSES))]


def stacked(row):
    return any(t.startswith(("-f", "-O", "-m")) for t in row["cfg"].replace("+", " ").split()[1:])


def score(row, cfg, text):
    with tempfile.TemporaryDirectory() as td:
        f = Path(td) / Path(row["c_path"]).name
        f.write_text(text)
        return verify(dict(row, cfg=cfg), f)


def scan_row(row, flags=0):
    t0 = time.time()
    text = clean_path(row).read_text(errors="replace")
    # the 1999 compilers are recorded, never built (LATE): scanning them only costs
    pool = flag_pool(row, flags) if flags else [c for c in CELLS if c != row["cfg"] and not c.startswith(LATE)]
    cells = [c for c in pool if score(row, f"{c} {INC}", text).get("exact")]
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


def latest(path=OUT):
    out = {}
    if path.exists():
        for r in read_jsonl(path):
            out[r["id"]] = r
    return out


def cmd_scan(a):
    fl = 3 if a.stack else 2 if a.flags2 else 1 if a.flags else 0
    path = {0: OUT, 1: FLAGS_OUT, 2: FLAGS2_OUT, 3: STACK_OUT}[fl]
    done = latest(path)
    keep = set(a.only.split(",")) if a.only else None
    todo = []
    for r in rows():
        if r["container"] == "slus" or not r.get("stock") or (keep and r["id"] not in keep):
            continue
        if fl == 2 and stacked(r):
            continue
        if fl == 3 and len(opt_flags(r)) != 1:
            continue                         # stacking: exactly one flag already, at most two after
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
        for rec in ex.map(lambda r: scan_row(r, fl), todo):
            with lock, path.open("a") as f:
                f.write(json.dumps(rec) + "\n")
            n += 1; nh += len(rec["hits"])
            if n % 50 == 0:
                print(f"{n}/{len(todo)} hits {nh} {time.time() - t0:.0f}s", flush=True)
    print(f"done {n} hits {nh} {time.time() - t0:.0f}s")


LATE = ("2.91.66", "2.95.2")      # 1999 compilers, after the game shipped: recorded, never built
STRIP = LEDGER / "pins_cells_strip.jsonl"


def strip_row(job):
    """Every pin erased at once, scored over the row's plausible admissible cells."""
    row, rec = job
    text = clean_path(row).read_text(errors="replace")
    sites = sites_of(text)
    cand = erase_many(text, sites, clean_notes=True)
    cells = [c for c in rec["cells"] if not c.startswith(LATE)]
    out = {"id": row["id"], "in_sha": rec["in_sha"], "cfg": row["cfg"], "pins": len(sites), "cell": None}
    if cells and score(row, ",".join(f"{c} {INC}" for c in cells), cand).get("exact"):
        out["cell"] = next(c for c in cells if score(row, f"{c} {INC}", cand).get("exact"))
    return out


def cmd_strip(a):
    """Rows with two or more pins: is the pin-free text exact at an admissible cell?"""
    by = {r["id"]: r for r in rows()}
    done = {(r["id"], r["in_sha"]) for r in read_jsonl(STRIP)} if STRIP.exists() else set()
    todo = []
    for rid, rec in latest().items():
        row = by.get(rid)
        if not row or not rec["cells"] or rec["pins"] < 2 or (rid, rec["in_sha"]) in done:
            continue
        if sha_text(clean_path(row).read_text(errors="replace")) != rec["in_sha"] or row["cfg"] != rec["cfg"]:
            continue
        todo.append((row, rec))
    print(f"{len(todo)} rows to strip", flush=True)
    n = hits = 0; t0 = time.time()
    with ThreadPoolExecutor(a.workers) as ex:
        for out in ex.map(strip_row, todo):
            with STRIP.open("a") as f:
                f.write(json.dumps(out) + "\n")
            n += 1; hits += bool(out["cell"])
            if n % 100 == 0:
                print(f"{n}/{len(todo)} pin-free at a cell {hits} {time.time() - t0:.0f}s", flush=True)
    print(f"done {n}, pin-free at an admissible cell {hits}, {time.time() - t0:.0f}s")


def cmd_build(a):
    by = {r["id"]: r for r in rows()}
    d = Path(a.dir); d.mkdir(parents=True, exist_ok=True)
    cells, stale, other = [], 0, 0
    fl = a.flags or a.flags2 or a.stack
    allowed = (lambda c: True) if fl else (lambda c: not c.startswith(LATE)) if a.plausible else (lambda c: c in CDK)
    strips = {r["id"]: r for r in read_jsonl(STRIP)} if STRIP.exists() and not fl else {}
    for rid, rec in sorted(latest(STACK_OUT if a.stack else FLAGS2_OUT if a.flags2 else FLAGS_OUT if a.flags else OUT).items()):
        s = strips.get(rid)
        if s and s["cell"] and allowed(s["cell"]) and rid in by and s["in_sha"] == rec["in_sha"]:
            row = by[rid]; text = clean_path(row).read_text(errors="replace")
            if sha_text(text) == s["in_sha"] and row["cfg"] == s["cfg"]:
                c, name = rid.split("/"); (d / c).mkdir(exist_ok=True)       # the whole row goes pin-free
                (d / c / (name + ".c")).write_text(erase_many(text, sites_of(text), clean_notes=True))
                (d / c / (name + ".c.base_sha")).write_text(s["in_sha"])
                cells.append({"id": rid, "to": s["cell"], "hits": s["pins"], "strip": True})
                continue
        hits = [h for h in rec["hits"] if allowed(h["cell"])]
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
    s.add_argument("--flags", action="store_true", help="flag variants of the recorded cell (ledger pins_flags_admissible.jsonl)")
    s.add_argument("--flags2", action="store_true", help="the second flag set, FLAGS2 (ledger pins_flags2_admissible.jsonl)")
    s.add_argument("--stack", action="store_true", help="a second flag on rows carrying exactly one (ledger pins_flags_stack_admissible.jsonl)")
    b = sub.add_parser("build"); b.add_argument("dir")
    b.add_argument("--flags", action="store_true", help="build the flag scan's hits (the compiler never changes)")
    b.add_argument("--flags2", action="store_true", help="build the second flag scan's hits")
    b.add_argument("--stack", action="store_true", help="build the stacking scan's hits")
    b.add_argument("--plausible", action="store_true",
                   help="also build hits at FSF 2.6.3/2.7.2/2.8.0/2.8.1 cells, not only CDK (never 2.91.66/2.95.2)")
    st = sub.add_parser("strip"); st.add_argument("--workers", type=int, default=8)
    a = ap.parse_args()
    {"scan": cmd_scan, "build": cmd_build, "strip": cmd_strip}[a.cmd](a)


if __name__ == "__main__":
    main()
