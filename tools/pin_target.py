#!/usr/bin/env python3
"""Order pinned rows by their measured probability of falling to the sweep.

    python3 tools/pin_target.py                 # every pinned row, best bet first
    python3 tools/pin_target.py --top 400       # just the best 400
    python3 tools/pin_target.py --explain       # the measured rates behind the ordering

An audit of the 1,624 rows `t15_shapes` has actually been run over (94 wins, 5.79% base)
measured which row properties predict a win.  Evidence does not: a row carrying assert or
naming evidence wins at 1.00x the base rate, and a row that already carried a
`do { } while (0)` at the pin wins at 0.54x.  **Mechanics do**, and strongly:

    pins_in == 1                 21.4%   3.69x      pins_in == 2      4.3%   0.74x
    size <= 128                  13.6%   2.36x      pins_in >= 3      0.4%   0.07x
    container main               20.7%   3.57x      size > 512        3.1%   0.54x
    pins_in == 1 AND size <= 256 23.4%   4.05x      container dungeon 3.5%   0.60x

The reading is that the sweep closes rows with ONE pin left and little else going on, and
that a row with three or more pins is essentially never closed in one pass - which is the
argument for partial removal: take a 5-pin row to 1 and it moves into the band that wins.

So a long run should spend its first hours where the yield is, and this emits that order.
It says nothing about WHICH statement to edit - the winning position is uniform over the
candidate set, so that part still has to be searched.
"""
import argparse, json, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from common import rows as ROWS, clean_path, LEDGER, read_jsonl
from pin_census import sites_of


def score(pins, size, container):
    """Relative expected yield, from the measured lifts above (multiplicative, uncalibrated)."""
    s = 1.0
    s *= {1: 3.69, 2: 0.74}.get(pins, 0.07)
    s *= 2.36 if size <= 128 else 1.6 if size <= 256 else 0.54 if size > 512 else 1.0
    s *= {"main": 3.57, "dungeon": 0.60}.get(container, 1.0)
    return s


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--top", type=int)
    ap.add_argument("--explain", action="store_true")
    a = ap.parse_args()
    if a.explain:
        print(__doc__)
        return
    strip = {j["id"]: j for j in read_jsonl(LEDGER / "pins_strip.jsonl")}
    out = []
    for r in ROWS():
        if r["container"] == "ovmovie":
            continue
        p = clean_path(r)
        if not p.exists():
            continue
        n = len(sites_of(p.read_text(errors="replace")))
        if not n:
            continue
        d = strip.get(r["id"], {}).get("total")
        out.append((-score(n, r["size"], r["container"]), d if d is not None else 9999, r["id"]))
    out.sort()
    for _, _, rid in (out[:a.top] if a.top else out):
        print(rid)


if __name__ == "__main__":
    main()
