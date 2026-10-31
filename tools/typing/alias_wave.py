#!/usr/bin/env python3
"""One-folder alias wave: typed parameter aliases, cast folds, view field synthesis and redundant-cast
removal, each TU proven byte-identical, rolled back per plan, with a receipt.

    alias_wave.py --folder src/town/shop --out DIR [--skip-list FILE] [--workers 4]
                  [--stages alias,fold,synth,fold,redundant] [--min-casts 2] [--dry-run]

Stages run in order, each planned with clang against the current text (param_alias.py for alias / synth /
redundant, cast_fold.py for fold), so a later stage sees the earlier one's result:

  alias      `void *P` read through `((V *)P)` -> `V *P = P_arg;` at the top of the body (prototype kept)
  fold       `*(T *)((u8 *)p + K)` -> `p->member` on typed bases (now including the aliased locals)
  synth      raw accesses at pad offsets of a file-local generated view get `unk_K` members (offset-neutral)
  redundant  casts to the operand's own type, and `(T *)vp` stored into a `T *` variable, are dropped

Proof: every physical TU that compiles a touched file is captured before and after
(layout_compile_identity.capture_one: raw object, canonical assembly and canonical object SHA-256).  A TU
that is not identical is restored to its original text and retried plan by plan: each alias plan (with the
folds it exposes) and each synth plan is applied alone and kept only when the TU stays identical.  A file is
restored when any function's lexical debt (tools/lint/debt_check classes) would rise.  Headers are never
edited.  Outputs: receipt.json, changes.jsonl, folder.patch, wave.log, timing.json.
"""
from __future__ import annotations

import argparse
import collections
from concurrent.futures import ProcessPoolExecutor
import difflib
import functools
import json
from pathlib import Path
import sys
import time

HERE = Path(__file__).resolve().parent


def _paths(root):
    for p in (HERE, root / 'tools' / 'typing', root / 'tools', root / 'tools' / 'lint'):
        if str(p) not in sys.path:
            sys.path.append(str(p))
    import layout_compile_identity as L
    if not hasattr(L.recipes, 'cache_info'):
        L.recipes = functools.lru_cache(maxsize=4)(L.recipes)


def retry_tu(args):
    """Plan-by-plan retry of one failing TU (its files start at their original text).

    Alias plans: with the folds they expose, else alone.  Synth plans: with their folds.  Redundant
    edits: as one group.  Each candidate is kept only when the TU stays identical."""
    root, tu, recipe, fl, before, stages, min_casts = args
    root = Path(root)
    _paths(root)
    import cast_fold as F
    import cast_wave as W
    import layout_compile_identity as L
    import param_alias as P
    recs_out, tried, kept, captures = [], 0, 0, 0

    def key(p):
        return (p['file'], p['func'], p.get('param'), p.get('view'), p.get('line'))

    for stage in [s for s in ('alias', 'synth', 'redundant') if s in stages]:
        plans, _, _ = P.plan(root, fl, [stage], min_casts, 1)
        units = [[key(p)] for p in plans] if stage != 'redundant' else ([[key(p) for p in plans]] if plans else [])
        for unit in units:
            if stage == 'alias':
                folds = [True, False] if 'fold' in stages else [False]
                variants = [(d, w) for d in ('first', 'last') for w in folds]
            else:
                variants = [('first', stage != 'redundant' and 'fold' in stages)]
            for decl_at, with_fold in variants:
                fresh, _, _ = P.plan(root, fl, [stage], min_casts, 1, decl_at)
                todo = [p for p in fresh if key(p) in set(unit)]
                if not todo:
                    break
                saved = {f: (root / f).read_text() for f in fl}
                tried += 1
                recs, _ = P.apply_plans(root, todo)
                fold_recs = []
                if with_fold:
                    edits, _, _ = F.plan(root, sorted({p['file'] for p in todo}), 1)
                    F.apply_edits(root, edits)
                    fold_recs = [{'kind': 'fold', 'file': f, 'func': s['func'], 'line': s['line'], 'old': s['old'],
                                  'new': s['new'], 'stage': 'fold', 'retry': True}
                                 for f, ss in edits.items() for s in ss]
                try:
                    res = L.capture_one(root, tu, recipe)
                except Exception as exc:
                    res = {'error': str(exc)}
                captures += 1
                if W.identical(before, res):
                    kept += 1
                    for p in recs:
                        p.pop('edits', None)
                        recs_out.append(dict(p, stage=stage, retry=True, with_fold=with_fold, decl_at=decl_at))
                    recs_out.extend(fold_recs)
                    break
                for f, t in saved.items():
                    (root / f).write_text(t)
    return tu, recs_out, tried, kept, captures


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=HERE.parents[1])
    ap.add_argument('--folder', required=True)
    ap.add_argument('--file', nargs='*', default=[])
    ap.add_argument('--skip-list', type=Path)
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--workers', type=int, default=4)
    ap.add_argument('--stages', default='alias,fold,synth,fold,redundant')
    ap.add_argument('--min-casts', type=int, default=2)
    ap.add_argument('--no-retry', action='store_true')
    ap.add_argument('--dry-run', action='store_true')
    args = ap.parse_args(argv)
    root = args.root.resolve()
    out = args.out.resolve()
    _paths(root)
    import cast_fold as F
    import cast_wave as W
    import param_alias as P
    import tu_identity as T
    out.mkdir(parents=True, exist_ok=True)
    logf = open(out / 'wave.log', 'a')
    timing = collections.Counter()

    def log(msg):
        line = time.strftime('%H:%M:%S ') + msg
        print(line, flush=True)
        logf.write(line + '\n')
        logf.flush()

    skip = set()
    if args.skip_list:
        skip = {l.strip() for l in args.skip_list.read_text().splitlines() if l.strip()}
    files = [f for f in F.folder_files(root, args.folder, args.file) if f not in skip]
    original = {f: (root / f).read_text() for f in files}
    tus, physical = F.physical_for(root, files)
    stages = [s for s in args.stages.split(',') if s]
    log('%s: %d files, %d physical TUs, stages %s' % (args.folder, len(files), len(tus), ','.join(stages)))

    def tu_files(tu):
        if tu in original:
            return [tu]
        text = (root / tu).read_text(errors='replace')
        return [f for f in files if Path(f).name in text]

    def run_stage(stage, subset, plans_only=None):
        """Plan and apply one stage over `subset`; returns the applied plan records."""
        t0 = time.time()
        if stage == 'fold':
            edits, refused, errors = F.plan(root, subset, args.workers)
            F.apply_edits(root, edits)
            recs = [{'kind': 'fold', 'file': f, 'func': s['func'], 'line': s['line'], 'old': s['old'],
                     'new': s['new'], 'casts': 2 if '(u8 *)' in s['old'] or '(char *)' in s['old'] else 1}
                    for f, ss in edits.items() for s in ss]
        else:
            plans, pool, errors = P.plan(root, subset, [stage], args.min_casts, args.workers)
            if plans_only is not None:
                plans = [p for p in plans if plans_only(p)]
            recs, skipped = P.apply_plans(root, plans)
            for p in recs:
                p.pop('edits', None)
            if skipped:
                log('%s: %d plans skipped (overlap)' % (stage, len(skipped)))
        timing['plan_' + stage] += time.time() - t0
        for tu, err in errors:
            log('parse error %s: %s' % (tu, err))
        log('%s: %d edits' % (stage, len(recs)))
        return recs

    def capture(tu_list):
        t0 = time.time()
        res = {r['source']: r for r in T.capture(root, sorted(tu_list), physical, args.workers)}
        timing['capture'] += time.time() - t0
        timing['captured_tus'] += len(tu_list)
        return res

    try:
        changes = collections.defaultdict(list)
        for i, stage in enumerate(stages):
            subset = files
            if stage in ('fold', 'synth') and 'alias' in stages[:i]:
                # After the alias stage only the aliased files can expose new folds or gaps.
                subset = [f for f in files if (root / f).read_text() != original[f]]
                if not subset:
                    continue
            for r in run_stage(stage, subset):
                changes[r['file']].append(dict(r, stage=stage))
        touched = sorted(f for f in files if (root / f).read_text() != original[f])
        touched_tus = sorted({tu for tu in tus if set(tu_files(tu)) & set(touched)})
        log('touched %d files in %d TUs' % (len(touched), len(touched_tus)))
        if args.dry_run:
            raise KeyboardInterrupt
        current = {f: (root / f).read_text() for f in touched}
        for f in touched:
            (root / f).write_text(original[f])
        before = capture(touched_tus)
        for f in touched:
            (root / f).write_text(current[f])
        after = capture(touched_tus)
        verdict, failed = {}, []
        for tu in touched_tus:
            ok = W.identical(before[tu], after[tu])
            verdict[tu] = {'identical': ok, 'mode': 'all' if ok else None,
                           'error': after[tu].get('error') or before[tu].get('error')}
            if not ok:
                failed.append(tu)
        log('all stages: %d/%d TUs identical' % (len(touched_tus) - len(failed), len(touched_tus)))
        # Per-plan retry of failing TUs: alias plans one at a time (each followed by a fold of its file),
        # then synth plans one at a time; redundant edits are retried as one group per TU.
        retry_jobs = []
        for tu in failed:
            for f in tu_files(tu):
                (root / f).write_text(original[f])
                changes.pop(f, None)
        if failed and not args.no_retry:
            jobs = [(str(root), tu, physical[tu], tu_files(tu), before[tu], stages, args.min_casts) for tu in failed]
            t0 = time.time()
            with ProcessPoolExecutor(max_workers=max(1, args.workers)) as ex:
                for tu, recs, tried, kept, captures in ex.map(retry_tu, jobs):
                    for r in recs:
                        changes[r['file']].append(r)
                    timing['captured_tus'] += captures
                    verdict[tu].update(retry={'tried': tried, 'kept': kept}, identical=True,
                                       mode='per_plan' if kept else 'rolled_back')
            timing['retry'] += time.time() - t0
            log('per-plan retry over %d TUs: %d plans kept' % (len(failed), sum(
                v.get('retry', {}).get('kept', 0) for v in verdict.values())))
        else:
            for tu in failed:
                verdict[tu]['mode'] = 'rolled_back'
        # Lexical debt must not rise in any function.
        receipt_files = {}
        for f in files:
            text = (root / f).read_text()
            if text == original[f]:
                changes.pop(f, None)
                continue
            rises = W.debt_rises(f, original[f], text)
            if rises:
                (root / f).write_text(original[f])
                changes.pop(f, None)
                log('debt rise, restored %s: %s' % (f, rises[:3]))
                continue
            receipt_files[f] = {'casts_before': W.casts_of(f, original[f]), 'casts_after': W.casts_of(f, text),
                                'sha256_before': W.sha(original[f]), 'sha256_after': W.sha(text),
                                'kinds': dict(collections.Counter(c['stage'] for c in changes.get(f, [])))}
        patch = []
        for f in sorted(receipt_files):
            patch.extend(difflib.unified_diff(original[f].splitlines(True), (root / f).read_text().splitlines(True),
                                              'a/' + f, 'b/' + f))
        (out / 'folder.patch').write_text(''.join(patch))
        with open(out / 'changes.jsonl', 'w') as fh:
            for f in sorted(receipt_files):
                for c in changes.get(f, []):
                    fh.write(json.dumps(dict(c, file=f), sort_keys=True) + '\n')
        removed = sum(r['casts_before'] - r['casts_after'] for r in receipt_files.values())
        by_stage = collections.Counter()
        for f in receipt_files:
            for c in changes.get(f, []):
                by_stage[c['stage']] += 1
        receipt = {'folder': args.folder, 'files': len(files), 'skipped': sorted(skip & set(
            F.folder_files(root, args.folder, args.file))), 'touched_tus': len(touched_tus),
            'identical_first_pass': len(touched_tus) - len(failed), 'retried_tus': len(failed),
            'rolled_back_tus': sorted(tu for tu, v in verdict.items() if v.get('mode') == 'rolled_back'),
            'kept_files': len(receipt_files), 'casts_removed': removed, 'edits_by_stage': dict(by_stage),
            'files_detail': receipt_files, 'tu_verdicts': verdict}
        (out / 'receipt.json').write_text(json.dumps(receipt, indent=2, sort_keys=True) + '\n')
        (out / 'timing.json').write_text(json.dumps(dict(timing), indent=1) + '\n')
        log('kept %d files, casts removed %d, first-pass identical %d/%d, rolled back %d' % (
            len(receipt_files), removed, len(touched_tus) - len(failed), len(touched_tus),
            len(receipt['rolled_back_tus'])))
        return 0
    except KeyboardInterrupt:
        for f, text in original.items():
            if (root / f).read_text() != text:
                (root / f).write_text(text)
        log('dry run / interrupted: every file restored')
        return 0 if args.dry_run else 130
    except BaseException:
        for f, text in original.items():
            if (root / f).read_text() != text:
                (root / f).write_text(text)
        log('failed: every file restored')
        raise


if __name__ == '__main__':
    sys.exit(main())
