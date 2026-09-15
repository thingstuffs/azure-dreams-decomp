#!/usr/bin/env python3
"""Flag census: which per-row optimisation flags are fidelity debt, and which compensate for a C shape.

    python3 tools/flag_census.py [--workers 6] [--only id,id] [--out ledger/flag_census.jsonl]

Every row whose cfg carries a flag beyond the cell and -G0 (`-fno-strength-reduce`, `-fno-schedule-insns`,
`-O1`, `-G16`, ...) is compiled from its CURRENT text at the same cell WITHOUT those flags (all of them at
once, and, for rows with two or more, each one alone) and scored with the per-row scorer.  A row exact
without a flag carries that flag as debt: the round-26 big-row skeptic found `-fno-cse-skip-blocks` on
dungeon/func_818D4E68 redundant on the pinned text and `-fno-strength-reduce` on func_819B3414 replaced by a
loop spelling.  A row that is not exact without its flag has a flag that stands in for a shape (the flags
were chosen because they made the pinned text match: docs/PIN_MECHANISMS "Round 11"/"Round 12"); its
distance says how far.  Analysis only: nothing is written to src/ or the split tables.  A redundant flag
is removed through the existing cell-switch landing (`tools/apply_candidates.py --cells`, rules 1-2, the
`t30_cellpins` journal keeps `cell_from`).  Resumable: a row already journaled with the same in_sha and cfg
is skipped.  The scorer shares build_ovl with lanes and gates: run it when no gate is running.
"""
import argparse
import collections
import json
import sys
import time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from common import rows, clean_path, parse_cfg, sha_text, is_stock_cfg
from pin_census import sites_of
from verify import verify

INCLUDE = ROOT / "include"


def variants(cfg):
    """(label, cfg) pairs to test: all flags off; each flag alone off when there are several."""
    cell, flags = parse_cfg(cfg)
    extra = [f for f in flags if f != "-G0"]
    if not extra:
        return []
    base = [f for f in flags if f == "-G0"]
    out = [("all-off", " ".join([cell + ("-G0" if base else "")] ))]
    if len(extra) > 1:
        for f in extra:
            keep = [x for x in flags if x != f]
            out.append(("without " + f, " ".join([cell + ("-G0" if "-G0" in keep else "")] + [x for x in keep if x != "-G0"])))
    return out


def one(row):
    text = clean_path(row).read_text(errors="replace")
    rec = dict(id=row["id"], cfg=row["cfg"], in_sha=sha_text(text), pins=len(sites_of(text)), size=row["size"], tests=[])
    t0 = time.time()
    for label, cfg in variants(row["cfg"]):
        r2 = dict(row, cfg=cfg, cell=parse_cfg(cfg)[0], flags=" ".join(parse_cfg(cfg)[1]))
        try:
            v = verify(r2, clean_path(row), include_root=INCLUDE)
            rec["tests"].append(dict(label=label, cfg=cfg, exact=bool(v.get("exact")), total=v.get("total"),
                                     status=v.get("status"), cls=v.get("class")))
        except Exception as e:  # a scorer failure is a result, not a crash
            rec["tests"].append(dict(label=label, cfg=cfg, exact=False, total=None, status="error", error=str(e)[:200]))
    rec["secs"] = round(time.time() - t0, 1)
    rec["redundant"] = any(t["label"] == "all-off" and t["exact"] for t in rec["tests"])
    rec["at"] = time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())
    return rec


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--workers", type=int, default=6)
    ap.add_argument("--only")
    ap.add_argument("--out", default=str(ROOT / "ledger/flag_census.jsonl"))
    a = ap.parse_args()
    out = Path(a.out)
    done = {}
    if out.exists():
        for line in out.read_text().splitlines():
            if line.strip():
                d = json.loads(line)
                done[d["id"]] = (d["in_sha"], d["cfg"])
    only = set(a.only.split(",")) if a.only else None
    todo = []
    for r in rows():
        if only and r["id"] not in only:
            continue
        if not is_stock_cfg(r["cfg"]) or not variants(r["cfg"]) or not clean_path(r).exists():
            continue
        text = clean_path(r).read_text(errors="replace")
        if done.get(r["id"]) == (sha_text(text), r["cfg"]):
            continue
        todo.append(r)
    print("flag census: %d rows to test (%d already journaled)" % (len(todo), len(done)), flush=True)
    n = 0
    with ThreadPoolExecutor(max_workers=a.workers) as ex, out.open("a") as f:
        for rec in ex.map(one, todo):
            f.write(json.dumps(rec, separators=(",", ":")) + "\n"); f.flush()
            n += 1
            if n % 25 == 0:
                print("  %d/%d" % (n, len(todo)), flush=True)
    # summary over the whole journal
    recs = [json.loads(l) for l in out.read_text().splitlines() if l.strip()]
    c = collections.Counter(); byflag = collections.defaultdict(collections.Counter)
    for d in recs:
        key = "pinned" if d["pins"] else "pin-free"
        c[key] += 1
        c[key + (" redundant" if d["redundant"] else " needed")] += 1
        cell, flags = parse_cfg(d["cfg"])
        for fl in [x for x in flags if x != "-G0"]:
            byflag[fl]["rows"] += 1
            if d["redundant"]:
                byflag[fl]["redundant"] += 1
    print("rows", len(recs), dict(c))
    for fl, cc in sorted(byflag.items(), key=lambda kv: -kv[1]["rows"]):
        print("  %-32s rows %3d  redundant %3d" % (fl, cc["rows"], cc["redundant"]))


if __name__ == "__main__":
    main()
