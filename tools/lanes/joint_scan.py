#!/usr/bin/env python3
"""Joint-erasure scan: subsets of a row's pins erased TOGETHER, scored over the recorded recipe and
its admissible cells / flag variants.

    python3 tools/lanes/joint_scan.py scan  [--mode cells|flags|flags2|stack] [--workers 12]
                                            [--max-pins 20] [--pair-pins 8] [--only id,id]
    python3 tools/lanes/joint_scan.py build <dir> [--mode ...]
    python3 tools/apply_candidates.py <dir> --transform t70_joint --workers 1 --cells <dir>/cells.jsonl

Why.  `tools/pin_cells_scan.py` erases ONE site at a time over the admissible cells and flag
variants; `tools/pin_sites.py --subsets` erases subsets at the RECORDED recipe only, and its ledger
(2026-09-12) predates most of the tree.  Round 31's lesson (t69_prologue) is that pins that hold
one mechanism fall only together.  This scan takes the subsets a joint mechanism would produce -
the whole set, every same-macro group, every same-variable group, and the pairs of rows with few
pins - and scores each over the recorded recipe PLUS the pool the lone scan uses for that mode.

Pools (from tools/pin_cells_scan.py): `cells` = the other stock cells; `flags` = FLAGS on the
recorded cell; `flags2` = FLAGS2 (rows already carrying a flag skipped); `stack` = one more flag on
rows carrying exactly one.  The recorded recipe is always in the pool, so a subset exact there is a
plain landing (apply_candidates lands it without a cell switch: exact at the recorded cell).

Cost: each subset is screened with the cc1 listing (tools/xform/screen.py, ~15 ms) at every pool
recipe against the pinned text's listing there; only an identical listing goes to the byte scorer.
A listing identical at the recipe means identical bytes; the converse is not guaranteed, so a
subset whose bytes match through a differing listing is missed here (the lone scan's stage 2 has no
such gap).  Rows with at most --exhaustive-pins pins get every subset of size two or more.

One line per row in ledger/pins_joint_<mode>.jsonl, keyed on (id, in_sha, cfg): resumable.  Hits
record the site indices, macros and the first exact recipe.  `build` writes the largest exact subset
per row (preferring the recorded recipe, then a -G0-matching cell) as a candidate plus cells.jsonl.
Landing goes through apply_candidates' `--cells` path (pin_cells_land rules 1-2 re-checked there).
"""
import argparse, collections, itertools, json, sys, time, threading
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools"))
from common import LEDGER, rows, clean_path, sha_text, read_jsonl          # noqa: E402
from pin_census import sites_of                                           # noqa: E402
from pin_sites import erase_many                                          # noqa: E402
import pin_cells_scan as pcs                                              # noqa: E402
sys.path.insert(0, str(ROOT / "tools/xform"))
from screen import compile_s                                             # noqa: E402

MODES = {"cells": 0, "flags": 1, "flags2": 2, "stack": 3, "custom": 4}
# flag discovery (2026-09-18): flags no earlier scan screened; codegen-relevant on gcc 2.x, all accepted by
# every stock cell.  `--mode custom --flags-list "..."` overrides.  Pilot on ~100 rows first (round-12 lesson).
FLAGS3 = ["-g", "-O3", "-fno-delayed-branch", "-finline-functions", "-fno-inline", "-fpcc-struct-return",
          "-freg-struct-return", "-fvolatile", "-fno-defer-pop", "-fomit-frame-pointer", "-mno-gpopt",
          "-mlong-calls", "-fshort-enums", "-fcaller-saves", "-mabicalls"]
CUSTOM_FLAGS = list(FLAGS3)
LATE = pcs.LATE


TAG = [""]


def out_path(mode):
    return LEDGER / f"pins_joint_{mode}{TAG[0]}.jsonl"


def pool_for(row, mode):
    fl = MODES[mode]
    if fl == 4:
        have = set(row["cfg"].split())
        pool = [f"{row['cfg']} {F}" for F in CUSTOM_FLAGS if F not in have]
    elif fl:
        pool = pcs.flag_pool(row, fl)
    else:
        pool = [c for c in pcs.CELLS if c != row["cfg"] and not c.startswith(LATE)]
    return pool


def var_of(site):
    """The variable a site pins: KEEP/USE take it as the macro argument, REG names it in the
    declaration the erasure leaves behind (`void *target`)."""
    kind, macro, arg = site[0], site[1], site[2]
    if kind == "reg" and len(site) > 6 and site[6]:
        return site[6].replace("*", " ").split()[-1]
    return arg


def subsets_of(sites, pair_pins, exhaustive_pins):
    """Size >= 2 subsets: every one on rows with at most `exhaustive_pins` pins, else the whole set,
    the same-macro and same-variable groups, and the pairs on rows with at most `pair_pins`."""
    n = len(sites)
    if n <= exhaustive_pins:
        # singles included: their hits calibrate the listing screen against the lone scan's stage 2
        return [idx for k in range(1, n + 1) for idx in itertools.combinations(range(n), k)]
    out, seen = [], set()

    def add(idx):
        idx = tuple(sorted(set(idx)))
        if len(idx) >= 2 and idx not in seen:
            seen.add(idx); out.append(idx)

    add(range(n))                                                     # the whole set
    by_macro = collections.defaultdict(list); by_arg = collections.defaultdict(list)
    for i, s in enumerate(sites):
        by_macro[s[1]].append(i)
        by_arg[var_of(s)].append(i)                                # the pinned variable, REG or KEEP
    for g in list(by_macro.values()) + list(by_arg.values()):
        add(g)
    if n <= pair_pins:
        for a, b in itertools.combinations(range(n), 2):
            add((a, b))
    return out


ADMISSIBLE = {"cells": pcs.OUT, "flags": pcs.FLAGS_OUT, "flags2": pcs.FLAGS2_OUT, "stack": pcs.STACK_OUT}
_ADM = {}


def admissible(mode):
    """The lone scan's stage-1 result (recipes at which the PINNED text is exact), keyed on
    (id, in_sha, cfg) - reused when fresh so the pool costs nothing here."""
    if mode not in _ADM:
        d = {}
        path = ADMISSIBLE.get(mode)
        if path and path.exists():
            for r in read_jsonl(path):
                d[(r["id"], r["in_sha"], r["cfg"])] = r["cells"]
        _ADM[mode] = d
    return _ADM[mode]


def listing(row, cfg, text):
    s = compile_s(dict(row, cfg=cfg), text)
    if s is not None and "-g" in cfg.split():
        s = [ln for ln in s if not ln.startswith(".stab")]           # -g: stabs carry no code
    return s


def scan_row(job):
    row, mode, pair_pins, exhaustive_pins = job
    t0 = time.time()
    text = clean_path(row).read_text(errors="replace")
    sites = sites_of(text)
    rec = {"id": row["id"], "cfg": row["cfg"], "in_sha": sha_text(text), "pins": len(sites),
           "mode": mode, "pool": [], "tested": 0, "screen_hits": 0, "hits": [], "secs": 0.0}
    try:
        adm = admissible(mode).get((row["id"], rec["in_sha"], row["cfg"]))
        if adm is None:
            adm = [c for c in pool_for(row, mode) if pcs.score(row, f"{c} {pcs.INC}", text).get("exact")]
            rec["pool_computed"] = True
        pool = [row["cfg"]] + [c for c in adm if not c.startswith(LATE)]
        rec["pool"] = pool
        base = {c: listing(row, c, text) for c in pool}
        pool = [c for c in pool if base[c] is not None]
        for idx in subsets_of(sites, pair_pins, exhaustive_pins):
            cand = erase_many(text, [sites[i] for i in idx], clean_notes=True)
            rec["tested"] += 1
            for c in pool:
                s = listing(row, c, cand)
                if s is None or s != base[c]:
                    continue
                rec["screen_hits"] += 1
                if pcs.score(row, f"{c} {pcs.INC}", cand).get("exact"):
                    rec["hits"].append({"sites": list(idx), "macros": [sites[i][1] for i in idx], "cell": c})
                    break
    except Exception as e:                                             # noqa: BLE001
        rec["error"] = repr(e)
    rec["secs"] = round(time.time() - t0, 1)
    return rec


def cmd_scan(a):
    TAG[0] = f"_{a.tag}" if a.tag else ""
    path = out_path(a.mode)
    done = {}
    if path.exists():
        for r in read_jsonl(path):
            done[r["id"]] = r
    keep = set(a.only.split(",")) if a.only else None
    fl = MODES[a.mode]
    if a.flags_list:
        CUSTOM_FLAGS[:] = a.flags_list.split()
    todo = []
    for r in rows():
        if r["container"] in ("slus", "ovmovie") or not r.get("stock") or (keep and r["id"] not in keep):
            continue
        if fl == 2 and pcs.stacked(r):
            continue
        if fl == 3 and len(pcs.opt_flags(r)) != 1:
            continue
        p = clean_path(r)
        if not p.exists():
            continue
        text = p.read_text(errors="replace")
        sites = sites_of(text)
        if len(sites) < a.min_pins or len(sites) > a.max_pins:
            continue
        prev = done.get(r["id"])
        if prev and prev["in_sha"] == sha_text(text) and prev["cfg"] == r["cfg"]:
            continue
        todo.append(r)
    todo.sort(key=lambda r: r.get("size") or 0)
    print(f"{len(todo)} rows to scan ({a.mode})", flush=True)
    lock, n, nh, t0 = threading.Lock(), 0, 0, time.time()
    with ThreadPoolExecutor(a.workers) as ex:
        for rec in ex.map(scan_row, [(r, a.mode, a.pair_pins, a.exhaustive_pins) for r in todo]):
            with lock, path.open("a") as f:
                f.write(json.dumps(rec) + "\n")
            n += 1; nh += bool(rec["hits"])
            if n % 25 == 0:
                print(f"{n}/{len(todo)} rows with a hit {nh} {time.time() - t0:.0f}s", flush=True)
    print(f"done {n} rows with a hit {nh} {time.time() - t0:.0f}s")


def cmd_build(a):
    TAG[0] = f"_{a.tag}" if getattr(a, "tag", "") else ""
    by = {r["id"]: r for r in rows()}
    d = Path(a.dir); d.mkdir(parents=True, exist_ok=True)
    cells, stale, pins = [], 0, 0
    for rec in read_jsonl(out_path(a.mode)):
        if not rec.get("hits") or rec["id"] not in by:
            continue
        row = by[rec["id"]]; text = clean_path(row).read_text(errors="replace")
        if sha_text(text) != rec["in_sha"] or row["cfg"] != rec["cfg"]:
            stale += 1; continue
        g0 = "-G0" in row["cfg"]
        best = max(rec["hits"], key=lambda h: (len(h["sites"]), h["cell"] == row["cfg"],
                                               ("-G0" in h["cell"]) == g0))
        if best["cell"].startswith(LATE):
            continue
        sites = sites_of(text)
        c, name = rec["id"].split("/"); (d / c).mkdir(exist_ok=True)
        (d / c / (name + ".c")).write_text(erase_many(text, [sites[i] for i in best["sites"]], clean_notes=True))
        (d / c / (name + ".c.base_sha")).write_text(rec["in_sha"])
        cells.append({"id": rec["id"], "to": best["cell"], "hits": len(best["sites"]), "joint": True})
        pins += len(best["sites"])
    (d / "cells.jsonl").write_text("".join(json.dumps(x) + "\n" for x in cells))
    print(f"rows {len(cells)}, pins in the chosen subsets {pins}, stale {stale}")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("scan"); s.add_argument("--mode", default="cells", choices=sorted(MODES))
    s.add_argument("--workers", type=int, default=12); s.add_argument("--only")
    s.add_argument("--max-pins", type=int, default=30, help="rows with more pins are skipped")
    s.add_argument("--pair-pins", type=int, default=20, help="pairs only on rows with at most this many pins")
    s.add_argument("--exhaustive-pins", type=int, default=10, help="every subset on rows with at most this many pins")
    s.add_argument("--flags-list", help="custom mode: the flags to add to the recorded recipe, space-separated")
    s.add_argument("--min-pins", type=int, default=2, help="custom mode may take 1 (singles are then the lone scan)")
    s.add_argument("--tag", default="", help="ledger suffix, so custom runs with different flag lists keep separate journals")
    b = sub.add_parser("build"); b.add_argument("dir"); b.add_argument("--mode", default="cells", choices=sorted(MODES))
    b.add_argument("--tag", default="")
    a = ap.parse_args()
    {"scan": cmd_scan, "build": cmd_build}[a.cmd](a)


if __name__ == "__main__":
    main()
