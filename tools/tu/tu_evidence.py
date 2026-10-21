#!/usr/bin/env python3
"""Sweep the 402 one-link images for original translation-unit evidence.

For every analysis unit (one-link image; MAIN split into its two load images)
this writes UNIT.json with the function list, J1 groups (shared anonymous string
literals), B1 duplicate-literal witnesses, B2 nonzero .rdata fills, post-text
.data fills, bss-candidate reference order, file-name anchors, pool-order
inversions and contradictions.  See tu_lib.py for the model.

usage: tu_evidence.py --out DIR [--root ROOT] [--image IMG ...] [--workers N]
Outputs: DIR/units/<unit>.json, DIR/summary.tsv, DIR/summary.json, DIR/skipped.json
Deterministic: same inputs give byte-identical outputs.
"""
import argparse
import json
import os
import sys
import time
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import tu_lib as T  # noqa: E402

# Self-test: the tu5 hand-written specs (verified on retail bytes) must equal
# the geometry derived from the committed maps.
TU5_SPECS = {
    'main/ll34_269000_80400000': dict(rdata=(0x269000, 0x2698A0), text_lo=0x2698A0, delta=0x80400000 - 0x269000),
    'main/image_25c800': dict(rdata=(0x25C800, 0x25D924), text_lo=0x25D924, delta=0x8001F800 - 0x25C800),
    'slus/slus_bin': dict(rdata=(0x800, 0x6B60), text_lo=0x72A8, delta=0x8002D000 - 0x800),
    'town/engine': dict(rdata=(0xB000, 0xD54C), text_lo=0xD54C, delta=0x80088760 - 0xB000),
    'dungeon/engine': dict(rdata=(0xA3000, 0xA3D40), text_lo=0xA3D40, delta=0x80088760 - 0xA3000),
    'dungeon/bank_1001000': dict(rdata=(0x1001000, 0x10010A8), text_lo=0x10010A8, delta=0x8016A800 - 0x1001000),
}

_REPO = None


def _init(root):
    global _REPO
    os.nice(0)
    _REPO = T.Repo(root)


def _work(args):
    u, out = args
    t = time.time()
    res = T.analyse(_REPO, u)
    res['summary']['seconds'] = round(time.time() - t, 2)
    path = Path(out) / 'units' / (u['unit'].replace('/', '__') + '.json')
    secs = res['summary'].pop('seconds')
    path.write_text(json.dumps(res, indent=0, sort_keys=True) + '\n')
    return res['summary'], secs


def selftest(units):
    by = {u['unit']: u for u in units}
    bad = []
    for name, spec in TU5_SPECS.items():
        u = by.get(name)
        if u is None:
            continue
        got = dict(rdata=tuple(u['rdata']), text_lo=u['text'][0], delta=u['delta'])
        if got != spec:
            bad.append((name, got, spec))
    if bad:
        raise SystemExit('geometry self-test failed: %r' % bad)
    return len([n for n in TU5_SPECS if n in by])


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=HERE.parents[1])
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--image', action='append', default=[])
    ap.add_argument('--workers', type=int, default=8)
    args = ap.parse_args(argv)
    t0 = time.time()
    repo = T.Repo(args.root)
    maps = repo.maps()
    images = repo.one_link_images()
    if len(images) != 402:
        print('warning: one-link image count %d != 402' % len(images), file=sys.stderr)
    if args.image:
        images = [i for i in images if i in args.image]
    units, skipped = T.units(repo, maps, images)
    if not args.image:
        print('geometry self-test: %d tu5 specs equal' % selftest(units))
    (args.out / 'units').mkdir(parents=True, exist_ok=True)
    summaries = []
    with ProcessPoolExecutor(max_workers=max(1, min(8, args.workers)), initializer=_init,
                             initargs=(str(args.root),)) as ex:
        for s, secs in ex.map(_work, [(u, str(args.out)) for u in units], chunksize=4):
            summaries.append(s)
    summaries.sort(key=lambda s: s['unit'])
    cols = list(summaries[0])
    with open(args.out / 'summary.tsv', 'w') as f:
        f.write('\t'.join(cols) + '\n')
        for s in summaries:
            f.write('\t'.join(str(s[c]) if not isinstance(s[c], list) else ','.join(s[c]) for c in cols) + '\n')
    (args.out / 'summary.json').write_text(json.dumps(summaries, indent=1, sort_keys=True) + '\n')
    (args.out / 'skipped.json').write_text(json.dumps(skipped, indent=1, sort_keys=True) + '\n')
    tot = {k: sum(s[k] for s in summaries) for k in ('functions', 'j1_groups', 'functions_in_j1_groups',
                                                      'b1_witnesses', 'b2_fills', 'b2_mapped', 'contradictions',
                                                      'pool_order_inversions', 'data_fills')}
    print(json.dumps(dict(images=len(images), units=len(units), skipped=len(skipped), seconds=round(time.time() - t0, 1),
                          **tot)))


if __name__ == '__main__':
    main()
