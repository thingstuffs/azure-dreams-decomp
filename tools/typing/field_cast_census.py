#!/usr/bin/env python3
"""Field-retype census: explicit casts applied to an untyped member of a named struct.

    field_cast_census.py --out DIR [--folder src] [--workers 4]

A site is `(T *)e->f` / `(T *)e.f` (also through parentheses and `*(T *)e->f`) where member f of a named,
non-generated record R is declared `void *` or a byte pointer.  When the casts on R.f agree on one record type T,
retyping the member (`T *f;` in R's header) makes every such cast redundant: layout_swap.py's fold stage then
removes them, and the new member type is identity evidence (an anchor) for views of T.

Outputs: field_casts.tsv (record, member, member type, header, target, casts, files, other targets),
summary.json.  Read-only: nothing under src/ or include/ is written.
"""
from __future__ import annotations

import argparse
import collections
from concurrent.futures import ProcessPoolExecutor
import json
from pathlib import Path
import re
import sys

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent)]
import cast_ast as A  # noqa: E402
import cast_fold as F  # noqa: E402
import field_census as C  # noqa: E402

GENERATED = re.compile(r'^(?:S_(?:func_)?[0-9A-Fa-f]{8}\w*|Rec_func_\w+|Row_\w+|R\d+_\w+|@.*)$')


def scan_tu(args):
    root, rel, recipe, files = args
    try:
        unit, error = A.clang_unit(root, rel, recipe)
    except Exception as exc:
        return {'tu': rel, 'error': str(exc)[-300:], 'sites': []}
    if unit is None:
        return {'tu': rel, 'error': error, 'sites': []}
    sites = []
    for f, fn in unit.functions(set(files)):
        for node, parent in A.walk(fn):
            if node.get('kind') != 'CStyleCastExpr':
                continue
            target = C.qtype(node)
            tkey = unit.T.record(target) if unit.T.resolve(target).endswith('*') and \
                not unit.T.resolve(target).endswith('**') else None
            if not tkey:
                continue
            op = A.kids(node)[0]
            while op.get('kind') in ('ParenExpr', 'ImplicitCastExpr') and A.kids(op):
                op = A.kids(op)[0]
            if op.get('kind') != 'MemberExpr':
                continue
            base = A.kids(op)[0]
            bt = C.qtype(base)
            rkey = unit.T.record(bt)
            if not rkey or GENERATED.match(rkey):
                continue
            mt = unit.canon(C.qtype(op))
            if not (mt == 'void*' or (mt.endswith('*') and mt[:-1] in A.BYTE_POINTEES)):
                continue
            sites.append({'file': f, 'func': fn.get('name'), 'line': node.get('_l'), 'record': rkey,
                          'header': unit.record_files.get(rkey, ''), 'member': op.get('name'),
                          'member_type': mt, 'target': tkey, 'target_generated': bool(GENERATED.match(tkey))})
    return {'tu': rel, 'error': error, 'sites': sites}


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=HERE.parents[1])
    ap.add_argument('--folder', default='src')
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--workers', type=int, default=4)
    args = ap.parse_args(argv)
    root = args.root.resolve()
    sys.path.insert(0, str(root / 'tools'))
    files = F.folder_files(root, args.folder)
    tus, _ = F.physical_for(root, files)
    jobs = [(str(root), tu, recipe, files) for tu, recipe in sorted(tus.items())]
    seen, sites, errors = set(), [], []
    with ProcessPoolExecutor(max_workers=max(1, args.workers)) as ex:
        for res in ex.map(scan_tu, jobs, chunksize=4):
            if res['error']:
                errors.append((res['tu'], res['error']))
            for s in res['sites']:
                k = (s['file'], s['line'], s['func'], s['member'], s['target'])
                if k not in seen:
                    seen.add(k)
                    sites.append(s)
    groups = collections.defaultdict(lambda: collections.Counter())
    gfiles = collections.defaultdict(set)
    meta = {}
    for s in sites:
        k = (s['record'], s['member'])
        groups[k][s['target']] += 1
        gfiles[k].add(s['file'])
        meta[k] = (s['member_type'], s['header'])
    args.out.mkdir(parents=True, exist_ok=True)
    rows = []
    for k, targets in groups.items():
        top, n = targets.most_common(1)[0]
        rows.append((n, k, top, targets))
    rows.sort(key=lambda r: -r[0])
    with open(args.out / 'field_casts.tsv', 'w') as fh:
        fh.write('record\tmember\tmember_type\theader\ttarget\tcasts\tfiles\tall_casts\tother_targets\n')
        for n, (rec, mem), top, targets in rows:
            others = ','.join('%s:%d' % t for t in targets.most_common() if t[0] != top)
            fh.write('%s\t%s\t%s\t%s\t%s\t%d\t%d\t%d\t%s\n' % (rec, mem, meta[(rec, mem)][0], meta[(rec, mem)][1],
                                                           top, n, len(gfiles[(rec, mem)]),
                                                           sum(targets.values()), others))
    with open(args.out / 'sites.jsonl', 'w') as fh:
        for s in sites:
            fh.write(json.dumps(s, sort_keys=True) + '\n')
    summary = {'sites': len(sites), 'members': len(rows), 'errors': errors[:20],
               'single_target_casts': sum(r[0] for r in rows if len(r[3]) == 1)}
    (args.out / 'summary.json').write_text(json.dumps(summary, indent=2) + '\n')
    print(json.dumps({k: summary[k] for k in ('sites', 'members', 'single_target_casts')}))
    return 0


if __name__ == '__main__':
    sys.exit(main())
