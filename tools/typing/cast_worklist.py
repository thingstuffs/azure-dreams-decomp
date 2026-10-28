#!/usr/bin/env python3
"""Tree-wide pointer-cast census and per-folder worklists for the cast wave (read-only).

    cast_worklist.py --out DIR [--prefix src/town ...] [--skip-list FILE ...] [--workers 8]

Each registered physical TU is parsed once (cast_ast) and run through all three planners on its current text:
  fold     cast_fold.scan_function   raw sites on typed bases (casts each fold removes, by debt_check's lexer)
  retype   view_swap.plan_function   one-view void * / u8 * locals (net casts after any added value cast)
  pool     parameters whose only record casts name one type (not applied: prototype lanes own them)
  views    view_swap census rows (decided against every shared type seen anywhere)

Outputs:
  files.tsv              per file: casts (debt_check), fold sites/casts, retype casts, parameter pool, top refusal
  folders.tsv            per folder (src/<a>/<b>): the same totals, in-flight overlap, ordered by estimated yield
  views.tsv              per view: file, size, casts, operands, decision, shared type / reason
  views_by_shared.tsv    evidenced/unique views grouped by shared type
  worklists/<folder>.tsv the files a lane works, highest yield first
  summary.json
The estimate is an upper bound: lanes keep only edits whose physical TU stays identical (cast_wave.py).
"""
from __future__ import annotations

import argparse
import collections
from concurrent.futures import ProcessPoolExecutor
import json
from pathlib import Path
import sys

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent), str(HERE.parent / 'lint'), str(HERE.parent / 'readability')]
import cast_ast as A  # noqa: E402
import cast_fold as F  # noqa: E402
import view_swap as V  # noqa: E402

_SEEN_SHARED = set()


def casts_in(text):
    import score as c
    tokens = c.lex(text)
    pairs, _ = c.pairs_of(tokens)
    return len(c.cast_sites(tokens, pairs))


def job(args):
    root, rel, recipe = args
    try:
        unit, error = A.clang_unit(root, rel, recipe)
    except Exception as exc:
        return {'tu': rel, 'error': str(exc)[-300:]}
    if unit is None:
        return {'tu': rel, 'error': error}
    files = collections.defaultdict(lambda: {'fold_sites': 0, 'fold_casts': 0, 'retype_vars': 0, 'retype_casts': 0,
                                             'refused': collections.Counter(), 'pool': collections.Counter()})
    src_files = set()
    for file, fn in unit.functions():
        if not file.startswith('src/'):
            continue
        src_files.add(file)
        text = unit.text(file)
        sites, refused = F.scan_function(unit, file, fn)
        row = files[file]
        for s in F.select_edits(sites).get(file, []):
            row['fold_sites'] += 1
            row['fold_casts'] += casts_in(s['old']) - casts_in(s['new'])
        row['refused'].update(refused)
        plans, pool = V.plan_function(unit, file, fn, text)
        row['retype_vars'] += len(plans)
        row['retype_casts'] += sum(p['casts'] for p in plans)
        row['pool'].update(pool)
    census = V.view_census_unit(unit, src_files)
    shared = {k: v for k, v in census['shared'].items() if k not in _SEEN_SHARED}
    _SEEN_SHARED.update(shared)
    for row in files.values():
        row['refused'] = dict(row['refused'])
        row['pool'] = dict(row['pool'])
    return {'tu': rel, 'error': error, 'files': dict(files), 'views': census['views'], 'shared': shared}


def folder_of(path):
    parts = path.split('/')
    return '/'.join(parts[:3]) if len(parts) > 3 else '/'.join(parts[:2]) if len(parts) > 2 else parts[0]


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=HERE.parents[1])
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--prefix', nargs='*', default=['src/'])
    ap.add_argument('--skip-list', type=Path, nargs='*', default=[], help='in-flight files of other lanes')
    ap.add_argument('--fold-survival', type=float, default=0.55,
                    help='expected fraction of fold casts surviving identity (pilot measurement)')
    ap.add_argument('--workers', type=int, default=6)
    args = ap.parse_args(argv)
    root = args.root.resolve()
    import layout_compile_identity as L
    import debt_check as D
    physical, _ = L.recipes(root)
    jobs = [(str(root), tu, recipe) for tu, recipe in sorted(physical.items())
            if any(tu.startswith(p) for p in args.prefix)]
    inflight = set()
    for p in args.skip_list:
        inflight |= {l.strip() for l in p.read_text().splitlines() if l.strip()}
    files, views, shared, errors = {}, {}, {}, []
    with ProcessPoolExecutor(max_workers=max(1, args.workers)) as ex:
        for res in ex.map(job, jobs, chunksize=8):
            if res.get('error'):
                errors.append((res['tu'], res['error']))
            for f, row in res.get('files', {}).items():
                files.setdefault(f, row)
            for k, v in res.get('views', {}).items():
                views.setdefault(k, v)
            for k, v in res.get('shared', {}).items():
                shared.setdefault(k, v)
    out = args.out
    (out / 'worklists').mkdir(parents=True, exist_ok=True)
    # current lexical cast counts
    casts = {}
    for f in files:
        try:
            res = D.analyze(f, (root / f).read_text())
            casts[f] = sum(v['counts']['pointer_casts'] for v in res['scopes'].values())
        except Exception:
            casts[f] = 0
    view_rows = []
    by_file_views = collections.defaultdict(collections.Counter)
    for k, v in sorted(views.items()):
        d = V.decide(v, shared)
        row = dict(v, **d)
        view_rows.append(row)
        by_file_views[v['file']][d['decision']] += v['casts']

    def est(row):
        return row['retype_casts'] + args.fold_survival * row['fold_casts']

    with open(out / 'files.tsv', 'w') as fh:
        fh.write('file\tcasts\tfold_sites\tfold_casts\tretype_vars\tretype_casts\tparam_pool_casts\t'
                 'view_casts_evidenced\tview_casts_unique\ttop_refusal\tinflight\n')
        for f in sorted(files, key=lambda f: (folder_of(f), -est(files[f]), f)):
            r = files[f]
            top = max(r['refused'].items(), key=lambda x: x[1])[0] if r['refused'] else ''
            fh.write('%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%s\t%s\n' % (
                f, casts[f], r['fold_sites'], r['fold_casts'], r['retype_vars'], r['retype_casts'],
                r['pool'].get('parameter:ok', 0), by_file_views[f].get('evidenced', 0),
                by_file_views[f].get('unique', 0), top, 'yes' if f in inflight else ''))
    folders = collections.defaultdict(lambda: collections.Counter())
    reasons = collections.defaultdict(collections.Counter)
    for f, r in files.items():
        k = folder_of(f)
        c = folders[k]
        c['files'] += 1
        c['casts'] += casts[f]
        c['fold_sites'] += r['fold_sites']
        c['fold_casts'] += r['fold_casts']
        c['retype_vars'] += r['retype_vars']
        c['retype_casts'] += r['retype_casts']
        c['param_pool_casts'] += r['pool'].get('parameter:ok', 0)
        c['inflight_files'] += f in inflight
        c['view_casts_evidenced'] += by_file_views[f].get('evidenced', 0)
        c['view_casts_unique'] += by_file_views[f].get('unique', 0)
        reasons[k].update(r['refused'])
        if r['fold_casts'] or r['retype_casts']:
            c['work_files'] += 1
    order = sorted(folders, key=lambda k: -(folders[k]['retype_casts'] + args.fold_survival * folders[k]['fold_casts']))
    cols = ['files', 'casts', 'work_files', 'retype_vars', 'retype_casts', 'fold_sites', 'fold_casts',
            'param_pool_casts', 'view_casts_evidenced', 'view_casts_unique', 'inflight_files']
    with open(out / 'folders.tsv', 'w') as fh:
        fh.write('rank\tfolder\testimated_casts\t' + '\t'.join(cols) + '\ttop_refusals\n')
        for i, k in enumerate(order, 1):
            c = folders[k]
            e = c['retype_casts'] + args.fold_survival * c['fold_casts']
            top = ','.join('%s:%d' % x for x in reasons[k].most_common(3))
            fh.write('%d\t%s\t%d\t%s\t%s\n' % (i, k, round(e), '\t'.join(str(c[x]) for x in cols), top))
    for k in order:
        rows = [f for f in files if folder_of(f) == k and (files[f]['fold_casts'] or files[f]['retype_casts'])]
        if not rows:
            continue
        with open(out / 'worklists' / (k.replace('/', '__') + '.tsv'), 'w') as fh:
            fh.write('file\tcasts\tretype_casts\tfold_sites\tfold_casts\tinflight\n')
            for f in sorted(rows, key=lambda f: -est(files[f])):
                r = files[f]
                fh.write('%s\t%d\t%d\t%d\t%d\t%s\n' % (f, casts[f], r['retype_casts'], r['fold_sites'],
                                                      r['fold_casts'], 'yes' if f in inflight else ''))
    with open(out / 'views.tsv', 'w') as fh:
        fh.write('file\tview\tsize\tcasts\tfields\toperands\tdecision\tshared\tdetail\n')
        for r in view_rows:
            detail = r.get('reason') or ','.join(r.get('candidates', [])[:6])
            if r['decision'] == 'ambiguous':
                detail = '%d candidates: %s' % (r.get('n', 0), detail)
            fh.write('%s\t%s\t%s\t%d\t%d\t%s\t%s\t%s\t%s\n' % (
                r['file'], r['view'], r.get('size'), r['casts'], len(r['fields']),
                ','.join('%s:%d' % x for x in sorted(r['operands'].items())), r['decision'], r.get('shared', ''), detail))
    groups = collections.defaultdict(lambda: collections.Counter())
    for r in view_rows:
        if r['decision'] in ('evidenced', 'unique'):
            g = groups[(r.get('shared'), r['decision'])]
            g['views'] += 1
            g['casts'] += r['casts']
            g[folder_of(r['file'])] += 1
    with open(out / 'views_by_shared.tsv', 'w') as fh:
        fh.write('shared\tdecision\tviews\tcasts\tfolders\n')
        for (s, d), g in sorted(groups.items(), key=lambda x: -x[1]['casts']):
            fl = ','.join('%s:%d' % (k, n) for k, n in g.most_common() if k not in ('views', 'casts'))
            fh.write('%s\t%s\t%d\t%d\t%s\n' % (s, d, g['views'], g['casts'], fl))
    decisions = collections.Counter()
    decision_casts = collections.Counter()
    by_folder_dec = collections.defaultdict(collections.Counter)
    for r in view_rows:
        decisions[r['decision']] += 1
        decision_casts[r['decision']] += r['casts']
        by_folder_dec[folder_of(r['file'])][r['decision']] += r['casts']
    with open(out / 'views_by_folder.tsv', 'w') as fh:
        keys = sorted(decisions)
        fh.write('folder\t' + '\t'.join(keys) + '\n')
        for k in sorted(by_folder_dec, key=lambda k: -sum(by_folder_dec[k].values())):
            fh.write(k + '\t' + '\t'.join(str(by_folder_dec[k][d]) for d in keys) + '\n')
    tot = collections.Counter()
    for c in folders.values():
        tot.update(c)
    all_reasons = collections.Counter()
    for c in reasons.values():
        all_reasons.update(c)
    summary = {'tus': len(jobs), 'files': len(files), 'errors': len(errors), 'error_sample': errors[:10],
               'totals': dict(tot), 'refusals': dict(all_reasons.most_common()),
               'views': dict(decisions), 'view_casts': dict(decision_casts), 'shared_types': len(shared),
               'fold_survival': args.fold_survival}
    (out / 'summary.json').write_text(json.dumps(summary, indent=2) + '\n')
    print(json.dumps({'files': len(files), 'totals': dict(tot), 'views': dict(decisions)}))
    return 0


if __name__ == '__main__':
    sys.exit(main())
