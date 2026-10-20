#!/usr/bin/env python3
"""Complete-TU object identity for a typed-field rewrite (no moves, no renames of files).

    snapshot  --edit FILE... [--header H...] --receipt R.jsonl   before the rewrite
    compare   --receipt R.jsonl [--results OUT.jsonl]               after the rewrite

The proof set is every registered physical TU whose preprocessor dependency closure contains an edited file:
the union of tools/layout_dependencies.consumer_paths (quoted includes) and a `clang -MM` closure over every
physical TU (catches macro-selected includes).  Each TU is compiled at its registered recipe through
layout_compile_identity.capture_one (the LL7 identity primitive): raw object SHA-256 plus canonical assembly
and canonical object SHA-256.  A rewrite is accepted only when every TU is raw- and canonical-equal.
"""
from __future__ import annotations

import argparse
from concurrent.futures import ProcessPoolExecutor
import json
import os
from pathlib import Path
import subprocess
import sys

HERE = Path(__file__).resolve().parent
TOOLS = HERE.parent
sys.path[:0] = [str(TOOLS)]


def _mm(args):
    root, rel = args
    res = subprocess.run(['clang', '--target=mipsel-unknown-none', '-w', '-MM', '-I', 'include', rel],
                         cwd=root, capture_output=True, text=True)
    deps = res.stdout.replace('\\\n', ' ').split(':', 1)[-1].split()
    return rel, [d for d in deps if d != rel]


def proof_set(root, edited, physical, workers=6):
    """Registered physical TUs that see any edited path."""
    from layout_dependencies import consumer_paths, include_parents
    edited = set(edited)
    quoted = consumer_paths(root, edited, parents=include_parents(root)) & set(physical)
    closure = set()
    with ProcessPoolExecutor(max_workers=workers) as ex:
        for rel, deps in ex.map(_mm, [(str(root), p) for p in sorted(physical)], chunksize=32):
            if rel in edited or edited & {os.path.normpath(d) for d in deps}:
                closure.add(rel)
    return sorted(quoted | closure), sorted(quoted ^ closure)


def _capture(args):
    root, rel, recipe = args
    import layout_compile_identity as L
    try:
        return L.capture_one(root, rel, recipe)
    except Exception as exc:  # recorded, never silently passed
        return {'source': rel, 'error': str(exc)[-400:]}


def capture(root, tus, physical, workers):
    with ProcessPoolExecutor(max_workers=workers) as ex:
        return list(ex.map(_capture, [(str(root), t, physical[t]) for t in tus]))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('mode', choices=('snapshot', 'compare'))
    ap.add_argument('--root', type=Path, default=TOOLS.parent)
    ap.add_argument('--edit', nargs='*', default=[])
    ap.add_argument('--tu', nargs='*', default=[], help='explicit physical TUs (skip closure discovery)')
    ap.add_argument('--receipt', type=Path, required=True)
    ap.add_argument('--results', type=Path)
    ap.add_argument('--workers', type=int, default=6)
    args = ap.parse_args(argv)
    root = args.root.resolve()
    import layout_compile_identity as L
    physical, _members = L.recipes(root)
    if args.mode == 'snapshot':
        if args.receipt.exists():
            raise SystemExit('receipt exists: %s' % args.receipt)
        if args.tu:
            tus, diff = sorted(args.tu), []
        else:
            tus, diff = proof_set(root, args.edit, physical, args.workers)
        recs = capture(root, tus, physical, args.workers)
        args.receipt.parent.mkdir(parents=True, exist_ok=True)
        with open(args.receipt, 'w') as fh:
            for r in recs:
                r['edited'] = sorted(args.edit)
                fh.write(json.dumps(r, sort_keys=True) + '\n')
        errs = [r for r in recs if 'error' in r]
        print(json.dumps({'tus': len(recs), 'errors': len(errs), 'closure_only_or_quoted_only': diff[:20]}))
        return 1 if errs else 0
    before = [json.loads(l) for l in args.receipt.read_text().splitlines() if l.strip()]
    tus = [r['source'] for r in before]
    after = {r['source']: r for r in capture(root, tus, physical, args.workers)}
    out, bad = [], []
    for b in before:
        a = after[b['source']]
        rec = {'source': b['source']}
        if 'error' in a or 'error' in b:
            rec['error'] = a.get('error') or b.get('error')
            bad.append(rec)
        else:
            rec['raw_equal'] = a['raw_sha256'] == b['raw_sha256']
            rec['canonical_assembly_equal'] = a['canonical_assembly_sha256'] == b['canonical_assembly_sha256']
            rec['canonical_object_equal'] = a['canonical_object_sha256'] == b['canonical_object_sha256']
            rec['after_raw_sha256'] = a['raw_sha256']
            if not (rec['raw_equal'] and rec['canonical_object_equal'] and rec['canonical_assembly_equal']):
                bad.append(rec)
        out.append(rec)
    if args.results:
        args.results.write_text(''.join(json.dumps(r, sort_keys=True) + '\n' for r in out))
    print(json.dumps({'tus': len(out), 'identical': len(out) - len(bad), 'changed_or_error': [r['source'] for r in bad][:50]}))
    return 1 if bad else 0


if __name__ == '__main__':
    sys.exit(main())
