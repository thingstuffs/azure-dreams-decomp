#!/usr/bin/env python3
"""Which current function a foreign program's import corresponds to: twin alignment of call targets.

    foreign_twins.py [--root R] (--header include/dungeon/stale_bank_imports.h | --ranges 'dungeon 0x129B000-0x12C5000')
                     --out IDS.tsv [--min-votes 2]

Needs a built tree (build/.state/link link maps: bind.py layouts) and its build/codemap.db.

A foreign program (tools/headers/foreign_imports.py: a header with a `foreign-program:` marker) calls
addresses of the build it was linked against.  Where one of its C units is a relocation-masked twin of a
unit linked in a live image or of a SLUS function (target_census.masked: jal/j targets, lui and lui-paired
%lo immediates cleared; struct offsets kept), the n-th jal of the foreign unit and the n-th jal of the
live twin call the same function.  Every such pair votes (foreign target -> live target); the live target
with the most votes, a function start with a readable name, is the import's current-build counterpart.

A pair must be each other's strongest partner, and its delta must match the delta of a neighbouring aligned
import (code moves in runs); otherwise the strongest candidate with a neighbour's delta is taken, else the strongest one, marked `probably`.

Output TSV: foreign call target address, comment (`current <name> (0x..., +0x1210; N twin call pairs)`), ready
for foreign_imports.py --identities (looked up by the import's address, placeholder nibble corrected).  Evidence only: the import keeps its address spelling (bytes).
"""
from __future__ import annotations

import argparse
import collections
import re
import sqlite3
import struct
import sys
from pathlib import Path

HERE = Path(__file__).resolve()
sys.path[:0] = [str(HERE.parent), str(HERE.parents[1] / 'codemap'), str(HERE.parents[1] / 'build')]
import foreign_imports as F  # noqa: E402
import target_census as T  # noqa: E402


def jals(blob, off, size):
    out = []
    for i in range(size // 4):
        if off + 4 * i + 4 > len(blob):
            break
        w = struct.unpack_from('<I', blob, off + 4 * i)[0]
        if w >> 26 == 3:
            out.append(0x80000000 | ((w & 0x3FFFFFF) << 2))
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=HERE.parents[2])
    ap.add_argument('--header', help='an import header with a foreign-program marker (or give --ranges)')
    ap.add_argument('--ranges', help='"container 0xLO-0xHI; ..." instead of a header marker')
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--min-votes', type=int, default=2)
    a = ap.parse_args(argv)
    root = a.root.resolve()
    if a.ranges:
        ranges = [(c, int(x, 16), int(y, 16)) for c, x, y in F.RANGE.findall(a.ranges)]
    else:
        prog = [p for p in F.programs(root) if p['header'] == a.header]
        if not prog:
            raise SystemExit('no foreign-program marker in %s' % a.header)
        ranges = prog[0]['ranges']
    db = sqlite3.connect('file:%s?mode=ro' % (root / 'build/codemap.db'), uri=True)
    world = T.World(root, db)
    readable = T.readable_names(root)
    inside = lambda cont, off: any(c == cont and lo <= off < hi for c, lo, hi in ranges)  # noqa: E731
    # every linked C function (one per container offset; bind.ImageLayout function granularity) and every SLUS
    # function, by masked words
    idx = collections.defaultdict(list)
    seen = set()
    starts = {}                                         # live address -> readable name
    for img, lay in world.layouts.items():
        cont = img.split('/')[0]
        blob = world.containers.get(cont)
        if blob is None:
            continue
        live = world.real(img)
        units = [u for u in world.units.get(img, ()) if u['kind'] == 'c' and u['off'] is not None and u['vma']]
        bases = {u['recipe']: u for u in units}
        if live:
            for addr, (rid, sym, size) in lay.functions.items():
                starts.setdefault(addr, readable.get(sym, sym))
        for addr, (rid, sym, size) in lay.functions.items():
            u = bases.get(rid)
            if u is None or not size or size < 24 or not u['vma'] <= addr < u['vma'] + u['size']:
                continue
            off = u['off'] + addr - u['vma']
            key = (cont, off)
            if key in seen:
                continue
            seen.add(key)
            idx[T.masked(blob, off, size)].append((cont, off, size, inside(cont, off)))
    slus = world.slus
    if slus.ok:
        for addr, (name, size) in slus.funcs.items():
            starts.setdefault(addr, readable.get(name, name))
            if size >= 24 and slus.t_addr <= addr < slus.end():
                off = addr - slus.t_addr + 0x800
                idx[T.masked(slus.blob, off, size)].append(('slus', off, size, False))
    pairs = collections.defaultdict(collections.Counter)
    for group in idx.values():
        foreign = [g for g in group if g[3]]
        live = [g for g in group if not g[3]]
        for f in foreign:
            jf = jals(world.containers[f[0]], f[1], f[2])
            for l in live:
                bl = slus.blob if l[0] == 'slus' else world.containers[l[0]]
                for x, y in zip(jf, jals(bl, l[1], l[2])):
                    if x != y:
                        pairs[x][y] += 1
    best = {}
    for x in sorted(pairs):
        cands = sorted(((v, y) for y, v in pairs[x].items() if y in starts), reverse=True)
        if not cands or cands[0][0] < a.min_votes:
            continue
        v, y = cands[0]
        # mutual best: the live function's own strongest foreign partner is this address (a twin pair whose
        # call lists do not line up votes for neighbours too)
        back = max((pairs[x2].get(y, 0), x2) for x2 in pairs if y in pairs[x2])
        if back[1] == x:
            best[x] = (v, y, cands)
    # delta consistency: code moves in runs, so an import's delta must match a neighbouring import's delta
    # (the nearest aligned address below or above it); otherwise take the strongest candidate that does
    order = sorted(best)
    out = {}
    for i, x in enumerate(order):
        near = {best[order[j]][1] - order[j] for j in (i - 1, i + 1) if 0 <= j < len(order)}
        for v, y in best[x][2]:
            if v >= a.min_votes and (y - x in near or not near):
                out[x] = (v, y, True)
                break
        else:
            v, y, _c = best[x]
            out[x] = (v, y, False)          # no candidate shares a neighbour's delta: reported as unconfirmed
    with a.out.open('w') as fh:
        fh.write('# address\tcomment (live counterpart, delta, votes)\n')
        hits = 0
        for x in sorted(out):
            v, y, ok = out[x]
            hits += 1
            delta = y - x
            fh.write('0x%08X\t%s %s (0x%08X, %s0x%X; %d twin call pairs%s)\n' % (
                x, 'current' if ok else 'probably', starts[y], y, '+' if delta >= 0 else '-', abs(delta), v,
                '' if ok else '; delta not shared by a neighbouring import'))
    print('foreign_twins: %d foreign call targets aligned' % hits)
    return 0


if __name__ == '__main__':
    sys.exit(main())
