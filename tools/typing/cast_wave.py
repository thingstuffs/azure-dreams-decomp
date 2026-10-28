#!/usr/bin/env python3
"""One-folder pointer-cast wave: plan, apply, prove complete-TU identity, roll back, write a receipt.

    cast_wave.py --folder src/town/minigame --out work/cast_wave/town_minigame [--skip-list FILE] [--workers 8]

Steps (the lane only runs this and reviews receipt.json / report.md):
  1. Every physical TU that compiles a folder file is captured (tu_identity / layout_compile_identity.capture_one:
     raw object, canonical assembly and canonical object SHA-256).
  2. Stages are applied in order, each planned against the current text:
       retype  view_swap.retype: one-view void * / u8 * locals take the view type, `(V *)x` -> `x`;
       fold    cast_fold: `*(T *)((u8 *)p + K)` -> `p->member` on typed bases (run twice: a retype or an
               inner fold can expose an outer site).
  3. Each touched TU is recaptured.  A TU that is not identical is retried with fewer stages (fold only,
     then retype only); a TU still not identical is restored to its original text.
  4. A file is also restored when any function's lexical debt (tools/lint/debt_check classes) would rise.
  5. receipt.json records per file: casts before/after, stages kept, TU identity verdicts, sha256 of the
     original and final text; changes.jsonl is the per-site change list; folder.patch is the diff.

Files are only edited inside --folder, never headers.  --skip-list names files other lanes own (one per line).
Nothing is left running; the proof compiles happen in this process's own pool.
"""
from __future__ import annotations

import argparse
import collections
import difflib
import hashlib
import json
from pathlib import Path
import sys
import time
from concurrent.futures import ProcessPoolExecutor

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent), str(HERE.parent / 'lint')]
import cast_fold as F  # noqa: E402
import view_swap as V  # noqa: E402

STAGE_SETS = (('retype', 'fold', 'fold'), ('fold', 'fold'), ('retype',))


def sha(text):
    return hashlib.sha256(text.encode()).hexdigest()


def debt(rel, text):
    import debt_check as D
    res = D.analyze(rel, text)
    return {k: dict(v['counts']) for k, v in res['scopes'].items()}


def casts_of(rel, text):
    return sum(v['pointer_casts'] for v in debt(rel, text).values())


def debt_rises(rel, before, after):
    """Function keys whose any debt class rises (new functions never appear: edits stay inside bodies)."""
    b, a = debt(rel, before), debt(rel, after)
    bad = []
    for key, counts in a.items():
        old = b.get(key, {})
        if any(n > old.get(k, 0) for k, n in counts.items()):
            bad.append(key)
    return bad


def run_stages(root, files, stages, workers, log):
    """Apply stages to the current text of `files`; returns per-file change records."""
    changes = collections.defaultdict(list)
    for stage in stages:
        if stage == 'retype':
            plans, pool, errors = V.retype(root, files, workers)
            V.apply_plans(root, plans)
            for p in plans:
                changes[p['file']].append({'stage': 'retype', 'func': p['func'], 'var': p['var'],
                                           'type': p['type'], 'casts': p['casts'], 'line': p['line']})
            log('retype: %d variables, %d casts' % (len(plans), sum(p['casts'] for p in plans)))
        else:
            edits, refused, errors = F.plan(root, files, workers)
            F.apply_edits(root, edits)
            n = 0
            for f, sites in edits.items():
                for s in sites:
                    changes[f].append({'stage': 'fold', 'func': s['func'], 'line': s['line'], 'old': s['old'],
                                       'new': s['new'], 'path': s['path'], 'record': s['record']})
                    n += 1
            log('fold: %d sites' % n)
        for tu, err in errors:
            log('parse error %s: %s' % (tu, err))
    return changes


def identical(a, b):
    return 'error' not in a and 'error' not in b and all(
        a[k] == b[k] for k in ('raw_sha256', 'canonical_assembly_sha256', 'canonical_object_sha256'))


def site_retry(args):
    """Apply fold sites of one TU one at a time, keeping each that leaves the TU identical.

    `start` maps each file to a text already proven identical (a retype-only result, or the original).
    Returns (tu, {file: kept change records}, sites tried)."""
    root, tu, recipe, files, before, start = args
    import layout_compile_identity as L
    root = Path(root)
    for f in files:
        (root / f).write_text(start[f])
    kept, rejected, tried = collections.defaultdict(list), set(), 0
    while tried < 200:
        edits, _, _ = F.plan(root, files, 1)
        candidates = [s for f in sorted(edits) for s in edits[f]
                      if (s['file'], s['func'], s['old'], s['line']) not in rejected]
        if not candidates:
            break
        s = candidates[0]
        tried += 1
        saved = (root / s['file']).read_text()
        F.apply_edits(root, {s['file']: [s]})
        if identical(L.capture_one(root, tu, recipe), before):
            kept[s['file']].append({'stage': 'fold', 'func': s['func'], 'line': s['line'], 'old': s['old'],
                                    'new': s['new'], 'path': s['path'], 'record': s['record']})
        else:
            (root / s['file']).write_text(saved)
            rejected.add((s['file'], s['func'], s['old'], s['line']))
    return tu, dict(kept), tried


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=HERE.parents[1])
    ap.add_argument('--folder', required=True)
    ap.add_argument('--file', nargs='*', default=[], help='restrict to these files inside the folder')
    ap.add_argument('--skip-list', type=Path, help='files owned by other lanes (one path per line)')
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--workers', type=int, default=6)
    ap.add_argument('--stages', default='retype,fold,fold')
    ap.add_argument('--no-site-retry', action='store_true', help='skip the per-site fold retry')
    ap.add_argument('--dry-run', action='store_true', help='plan and report only; restore every file')
    args = ap.parse_args(argv)
    root = args.root.resolve()
    sys.path.insert(0, str(root / 'tools'))
    import layout_compile_identity as L
    import tu_identity as T
    out = args.out
    out.mkdir(parents=True, exist_ok=True)
    logf = open(out / 'wave.log', 'a')

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
    log('%s: %d files (%d skipped), %d physical TUs' % (args.folder, len(files), len(skip & set(
        F.folder_files(root, args.folder))), len(tus)))
    stages = tuple(s for s in args.stages.split(',') if s)
    tried = [stages] + [s for s in STAGE_SETS if s != stages and set(s) <= set(stages)]

    def tu_files(tu):
        if tu in original:
            return [tu]
        text = (root / tu).read_text(errors='replace')
        return [f for f in files if Path(f).name in text]

    try:
        changes = run_stages(root, files, stages, args.workers, log)
        touched = sorted(f for f in files if (root / f).read_text() != original[f])
        touched_tus = sorted({tu for tu in tus if set(tu_files(tu)) & set(touched)})
        log('touched %d files in %d TUs' % (len(touched), len(touched_tus)))
        if args.dry_run:
            raise KeyboardInterrupt
        # Baseline objects for the touched TUs at the original text.
        current = {f: (root / f).read_text() for f in touched}
        for f in touched:
            (root / f).write_text(original[f])
        before = {r['source']: r for r in T.capture(root, touched_tus, physical, args.workers)}
        for f in touched:
            (root / f).write_text(current[f])
        verdict = {}
        pending = touched_tus
        kept_stages = {}
        for attempt, stage_set in enumerate(tried):
            if attempt:
                # Retry failing TUs from their original text with fewer stages.
                retry_files = sorted({f for tu in pending for f in tu_files(tu)})
                for f in retry_files:
                    (root / f).write_text(original[f])
                for f in retry_files:
                    changes.pop(f, None)
                again = run_stages(root, retry_files, stage_set, args.workers, log)
                changes.update(again)
            after = {r['source']: r for r in T.capture(root, pending, physical, args.workers)}
            failed = []
            for tu in pending:
                b, a = before[tu], after[tu]
                ok = 'error' not in a and 'error' not in b and all(
                    a[k] == b[k] for k in ('raw_sha256', 'canonical_assembly_sha256', 'canonical_object_sha256'))
                verdict[tu] = {'identical': ok, 'stages': list(stage_set), 'error': a.get('error') or b.get('error')}
                if ok:
                    for f in tu_files(tu):
                        kept_stages[f] = list(stage_set)
                else:
                    failed.append(tu)
            log('attempt %d %s: %d/%d TUs identical' % (attempt, ','.join(stage_set), len(pending) - len(failed), len(pending)))
            pending = failed
            if not pending:
                break
        if 'fold' in stages and not args.no_site_retry:
            # Greedy per-site folds for every TU whose kept result lost the fold stage: on top of its
            # proven retype-only text, or from the original text when nothing passed.
            jobs = []
            for tu, v in verdict.items():
                if 'fold' in v['stages'] and v['identical']:
                    continue
                start = {f: ((root / f).read_text() if v['identical'] else original[f]) for f in tu_files(tu)}
                jobs.append((str(root), tu, physical[tu], tu_files(tu), before[tu], start))
            with ProcessPoolExecutor(max_workers=max(1, args.workers)) as ex:
                for tu, kept, tried_sites in ex.map(site_retry, jobs):
                    v = verdict[tu]
                    base_stages = v['stages'] if v['identical'] else []
                    if not v['identical']:
                        for f in tu_files(tu):
                            changes.pop(f, None)
                    for f in tu_files(tu):
                        changes[f] = [c for c in changes.get(f, []) if c['stage'] == 'retype'] + kept.get(f, [])
                        kept_stages[f] = base_stages + (['fold_sites'] if kept.get(f) else [])
                    n_kept = sum(map(len, kept.values()))
                    if not v['identical'] and not n_kept:
                        # Nothing survived: the TU is back at its original text.
                        v['rolled_back'] = True
                    v.update(identical=True, site_retry={'tried': tried_sites, 'kept': n_kept})
            pending = [tu for tu in pending if not verdict[tu]['identical']]
            log('site retry over %d TUs: %d sites kept' % (len(jobs), sum(
                verdict[tu].get('site_retry', {}).get('kept', 0) for tu in verdict)))
        for tu in pending:
            for f in tu_files(tu):
                (root / f).write_text(original[f])
                changes.pop(f, None)
                kept_stages.pop(f, None)
            verdict[tu]['rolled_back'] = True
        # Lexical debt must not rise in any function.
        receipt_files = {}
        for f in touched:
            text = (root / f).read_text()
            if text == original[f]:
                continue
            rises = debt_rises(f, original[f], text)
            if rises:
                (root / f).write_text(original[f])
                changes.pop(f, None)
                log('debt rise, restored %s: %s' % (f, rises[:3]))
                continue
            receipt_files[f] = {'casts_before': casts_of(f, original[f]), 'casts_after': casts_of(f, text),
                                'sha256_before': sha(original[f]), 'sha256_after': sha(text),
                                'stages': kept_stages.get(f), 'sites': len(changes.get(f, []))}
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
        receipt = {
            'folder': args.folder, 'root': str(root), 'files': len(files), 'skipped': sorted(skip & set(original)),
            'touched_tus': len(touched_tus), 'identical_tus': sum(1 for v in verdict.values() if v['identical']),
            'rolled_back_tus': sorted(tu for tu, v in verdict.items() if v.get('rolled_back')),
            'kept_files': len(receipt_files), 'casts_removed': removed, 'files_detail': receipt_files,
            'tu_verdicts': verdict,
        }
        (out / 'receipt.json').write_text(json.dumps(receipt, indent=2, sort_keys=True) + '\n')
        log('kept %d files, casts removed %d, rolled back TUs %d' % (len(receipt_files), removed,
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
