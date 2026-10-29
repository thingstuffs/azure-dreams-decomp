#!/usr/bin/env python3
"""Census: does the typing proof compile the same object the build links?

    census_proof_flags.py [--root R] [--sample N] [--workers 8] [--json OUT] [--no-compile]

The proof map (`layout_compile_identity.recipes`) records, per physical TU, a cell, cc flags and maspsx
`asflags`; `capture_one` compiles it with `gcc -S` -> ccproc -> `layout_identity.reassemble` (maspsx
with container-wide noreturn/sibcall tables) at the cell, cc flags and maspsx flags of every linked
production recipe of the source (`production_compiles`; it used to pass NO maspsx flags).
The build compiles the same source through `build_ovl/tools/cc.sh <cell> <ccflags> <maspsx flags>` with the
recipe's own evidence files.

Static part (no compile): every ordinary row TU in the proof map joined with its linked production
recipe(s) on source; counts of cell / cc-flag / maspsx-flag disagreements.

Measured part (compiles, in the given root; build/obj must be the root's current build):
  capture_vs_build   capture_one raw object sha == production object sha (build/obj)?
  flag_matters       the production recipe compiled with the disputed maspsx flag(s) removed
                     == production object?  (equal: the flag never fires in that TU)
Overlay rows only (SLUS rows have their own capture path).
"""
from __future__ import annotations

import argparse
from collections import Counter
from concurrent.futures import ProcessPoolExecutor
import hashlib
import json
import os
from pathlib import Path
import random
import sys
import time

HERE = Path(__file__).resolve()
sys.path.insert(0, str(HERE.parent))
import affected as A    # noqa: E402


def _capture(args):
    root, rel, recipe = args
    sys.path[:0] = [str(Path(root) / 'tools')]
    os.chdir(root)
    import layout_compile_identity as L
    try:
        res = L.capture_one(root, rel, recipe)
        return rel, dict(res.get('variant_raw_sha256') or {}, primary=res['raw_sha256']), None
    except Exception as exc:
        return rel, None, str(exc)[-300:]


def static_join(root, graph):
    sys.path[:0] = [str(root / 'tools'), str(root / 'tools/gate')]
    import layout_compile_identity as L
    physical, _ = L.recipes(root)
    linked = set()
    for spec in graph.images.values():
        linked.update(spec['recipes'])
    by_source = {}
    for rid, spec in graph.recipes.items():
        if spec['_family'] == 'overlay' and not spec.get('projection') and 'module' not in spec and rid in linked:
            by_source.setdefault(spec['source'], []).append(rid)
    rows, counts, kinds = [], Counter(), Counter()
    for rel, proof in sorted(physical.items()):
        if proof['kind'] != 'row' or proof['container'] == 'slus':
            continue
        for rid in by_source.get(rel, []):
            args = graph.recipes[rid]['args']
            cell, ccflags = args[0], args[1].split() if len(args) > 1 else []
            asflags = args[2].split() if len(args) > 2 else []
            pflags = [f for f in proof['flags'] if f != '-O2']
            diff = dict(cell=cell != proof['cell'], ccflags=[f for f in ccflags if f != '-O2'] != pflags,
                        asflags=sorted(asflags) != sorted(proof['asflags']))
            counts['pairs'] += 1
            for k, v in diff.items():
                counts[k + '_differs'] += bool(v)
            if diff['asflags']:
                kinds['proof=%s build=%s' % (' '.join(proof['asflags']) or '[]', ' '.join(asflags) or '[]')] += 1
            rows.append(dict(source=rel, recipe=rid, proof=proof, build_asflags=asflags, **diff))
    return physical, rows, counts, kinds


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=A.DEFAULT_ROOT)
    ap.add_argument('--sample', type=int, default=0, help='measure N random disputed TUs (0 = all)')
    ap.add_argument('--workers', type=int, default=8)
    ap.add_argument('--seed', type=int, default=1029)
    ap.add_argument('--no-compile', action='store_true')
    ap.add_argument('--all', action='store_true',
                    help='measure capture_vs_build for every row pair, not only the asflag-disputed ones')
    ap.add_argument('--json', type=Path)
    args = ap.parse_args(argv)
    root = args.root.resolve()
    graph = A.Graph(root)
    physical, rows, counts, kinds = static_join(root, graph)
    disputed = [r for r in rows if r['asflags']]
    result = dict(static=dict(counts), asflag_kinds=dict(kinds.most_common()),
                  disputed_tus=len({r['source'] for r in disputed}))
    if not args.no_compile and disputed:
        todo = list(rows if args.all else disputed)
        if args.sample and args.sample < len(todo):
            todo = random.Random(args.seed).sample(todo, args.sample)
        os.nice(10)
        started = time.monotonic()
        build = {}
        for r in todo:
            path = root / graph.recipes[r['recipe']]['output']
            build[r['recipe']] = hashlib.sha256(path.read_bytes()).hexdigest() if path.is_file() else None
        sources = sorted({r['source'] for r in todo})
        with ProcessPoolExecutor(max_workers=args.workers) as ex:
            caps = {rel: (sha, err) for rel, sha, err in
                    ex.map(_capture, [(str(root), rel, physical[rel]) for rel in sources], chunksize=4)}
        t_capture = time.monotonic() - started
        run = 'build/.affected/census-%d' % os.getpid()
        tasks = []
        for r in todo:
            spec = dict(graph.recipes[r['recipe']])
            keep = [f for f in r['build_asflags'] if f in r['proof']['asflags']] if r['asflags'] else r['build_asflags']
            spec['args'] = [spec['args'][0], spec['args'][1], ' '.join(keep)]
            tasks.append(dict(op='compile', key=r['recipe'], id=r['recipe'], run=run, family='overlay', spec=spec))
        (root / run).mkdir(parents=True, exist_ok=True)
        pool = A.Workers(root, args.workers)
        try:
            stripped = {t['key']: res for t, res in zip(tasks, pool.map(tasks))}
        finally:
            pool.close()
            import shutil
            shutil.rmtree(root / run, ignore_errors=True)
        t_total = time.monotonic() - started
        tally, examples = Counter(), {}
        for r in todo:
            sha_build = build[r['recipe']]
            cap, err = caps[r['source']]
            cap = None if err else cap.get(r['recipe'], cap['primary'])
            res = stripped[r['recipe']]
            c = 'capture_error' if err else 'capture_equal' if cap == sha_build else 'capture_differs'
            if r['asflags']:
                f = 'strip_error' if 'error' in res else 'flag_inert' if res['sha256'] == sha_build else 'flag_matters'
            else:
                f = 'rebuild_error' if 'error' in res else 'rebuild_equal' if res['sha256'] == sha_build \
                    else 'rebuild_differs'
            tally[c] += 1
            tally[f] += 1
            tally[c + '+' + f] += 1
            key = c + '+' + f + ('' if r['asflags'] else ' (flags agree: ' + (' '.join(r['build_asflags']) or '[]') + ')')
            examples.setdefault(key, []).append(r['source'])
        result['measured'] = dict(tus=len(todo), tally=dict(sorted(tally.items())),
                                  examples={k: v[:12] for k, v in sorted(examples.items())},
                                  seconds_capture=round(t_capture, 1), seconds_total=round(t_total, 1))
    text = json.dumps(result, indent=1, sort_keys=True)
    if args.json:
        args.json.write_text(text + '\n')
    print(text)
    return 0


if __name__ == '__main__':
    sys.exit(main())
