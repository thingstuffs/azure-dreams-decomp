#!/usr/bin/env python3
"""One-folder extern wave: local extern declarations -> owning folder headers, proven by complete-TU identity.

    extern_wave.py --folder src/engine/audio --out DIR [--skip-list FILE] [--workers 4] [--data] [--dry-run]

Steps (a lane runs this and reviews receipt.json / holds.tsv / folder.patch):
  1. Plan the folder's TUs with tools/headers (plan.py): which local declarations an owning-header include
     replaces, and the static holds (no C definition, conflicting types, hand-written header gaps, ...).
     Only the owning headers this folder needs are (re)generated; hand-written headers are never written.
  2. Snapshot every registered physical TU whose include closure contains a file the wave may write (the
     needed headers and the folder TUs with edits): raw object, canonical assembly and canonical object.
  3. Write the needed headers, byte-decide each (TU, header) include at the TU's recipe (prove.py), apply
     the accepted TU edits and drop headers nothing uses.
  4. Recapture the proof set.  A changed TU is rolled back: its own edit first; when the TU is unedited (or
     still changes) every changed header in its closure is restored together with the folder TUs that
     depended on it.  Repeats until every TU is identical.
  5. Debt ratchet: an edited file whose per-function lexical debt rises (tools/lint/debt_check) is restored.
  6. Writes receipt.json, holds.tsv (TU, header, reason), files.tsv (local externs before/after),
     folder.patch and wave.log.

--skip-list names files other lanes own (one path per line; .c or .h).  A needed header in the skip list
holds every TU that needs it.  Data externs move only with --data (README: tree-wide data waits for data
naming).  Every file the wave touches is restored on --dry-run, an interrupt or an error.
"""
from __future__ import annotations

import argparse
import difflib
import hashlib
import json
import sys
import time
from collections import Counter, defaultdict
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent), str(HERE.parent / 'lint'), str(HERE.parent / 'typing')]

import plan as P          # noqa: E402
import rewrite as R       # noqa: E402

TENTATIVE = ('not_a_physical_tu', 'slus_partition_unit')
KEYS = ('raw_sha256', 'canonical_assembly_sha256', 'canonical_object_sha256')


def sha(text):
    return hashlib.sha256(text.encode('utf-8', 'surrogateescape')).hexdigest()


def read(root, rel):
    p = Path(root) / rel
    return p.read_bytes().decode('utf-8', 'surrogateescape') if p.exists() else None


def write(root, rel, text):
    p = Path(root) / rel
    if text is None:
        if p.exists():
            p.unlink()
        return
    p.parent.mkdir(parents=True, exist_ok=True)
    p.write_bytes(text.encode('utf-8', 'surrogateescape'))


def debt(rel, text):
    import debt_check as D
    res = D.analyze(rel, text)
    return {k: dict(v['counts']) for k, v in res['scopes'].items()}


def local_externs(rel, text):
    return sum(v['local_externs'] for v in debt(rel, text).values())


def debt_rises(rel, before, after):
    b, a = debt(rel, before), debt(rel, after)
    return [k for k, counts in a.items() if any(n > b.get(k, {}).get(c, 0) for c, n in counts.items())]


def identical(a, b):
    return 'error' not in a and 'error' not in b and all(a[k] == b[k] for k in KEYS)


def dependencies(root, physical, workers, cache=None):
    """{physical TU: set of files in its preprocessor closure} (clang -MM, as tu_identity).

    With `cache` (a .json.gz path) a TU is rescanned only when it or a file of its recorded closure is
    newer than the scan, or its recipe changed."""
    import gzip
    import tu_identity as T
    old = {}
    if cache and Path(cache).exists():
        try:
            old = json.loads(gzip.decompress(Path(cache).read_bytes()))
        except (OSError, ValueError):
            old = {}
    root = Path(root)
    mtimes = {}

    def mtime(rel):
        if rel not in mtimes:
            try:
                mtimes[rel] = (root / rel).stat().st_mtime_ns
            except OSError:
                mtimes[rel] = -1
        return mtimes[rel]

    deps, todo = {}, []
    for p in sorted(physical):
        rec = old.get(p)
        if rec and rec['recipe'] == physical[p] and all(0 <= mtime(f) <= rec['time'] for f in rec['deps'] + [p]):
            deps[p] = set(rec['deps']) | {p}
        else:
            todo.append(p)
    stamp = time.time_ns()
    with ProcessPoolExecutor(max_workers=workers) as ex:
        for rel, ds in ex.map(T._mm, [(str(root), p, physical[p]) for p in todo], chunksize=32):
            deps[rel] = set(ds) | {rel}
            old[rel] = {'recipe': physical[rel], 'deps': sorted(ds), 'time': stamp}
    if cache and todo:
        Path(cache).parent.mkdir(parents=True, exist_ok=True)
        Path(cache).write_bytes(gzip.compress(json.dumps({k: v for k, v in old.items() if k in physical},
                                                         sort_keys=True).encode()))
    return deps


def proof_set(root, edited, physical, deps):
    from layout_dependencies import consumer_paths, include_parents
    edited = set(edited)
    quoted = consumer_paths(root, edited, parents=include_parents(root)) & set(physical)
    return sorted(quoted | {t for t, ds in deps.items() if ds & edited})


def plan_folder(root, files, data, skip):
    plan = P.build(root, scope_files=files, include_data=data)
    hof = lambda r: plan.fn_for_def(r.definition).header      # noqa: E731
    jobs, static_holds = {}, []
    for rel, tp in sorted(plan.tus.items()):
        for h, why in sorted(tp.holds.items()):
            static_holds.append((rel, h, why))
        if not (tp.add or tp.stale):
            continue
        orig = plan.corpus.text(rel)
        edit = R.tu_edit(tp, hof)
        blocked = [h for h in edit['add'] if h in skip]
        if blocked:
            for h in blocked:
                static_holds.append((rel, h, 'header_in_skip_list'))
            edit = dict(edit, add=[h for h in edit['add'] if h not in skip],
                        remove=[x for x in edit['remove'] if x[0] not in skip])
        if R.edit_tu(orig, edit) == orig:
            continue
        jobs[rel] = (orig, edit)
    texts = header_texts(root, plan, {rel: e['add'] for rel, (o, e) in jobs.items()})
    return plan, jobs, texts, static_holds


def header_texts(root, plan, accepted):
    """{header: text} for the headers the TUs in `accepted` ({tu: [headers]}) include: a header that does
    not exist is generated whole; an existing one (hand-written or once generated, since edited by hand)
    only gains the declarations those TUs need, appended after its own text."""
    names = defaultdict(set)
    for rel, hs in accepted.items():
        tp = plan.tus.get(rel)
        for h in hs:
            names[h] |= set(tp.append.get(h, ())) if tp else set()
    texts = {}
    for h in sorted(names):
        old = read(root, h)
        if old is None:
            texts[h] = R.header_text(plan, h)
        elif h in plan.existing and names[h]:
            texts[h] = R.append_text(plan, h, names[h], old)
    return texts


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=HERE.parents[1])
    ap.add_argument('--folder', required=True, help='src/<...> folder (its .c files, not subfolders)')
    ap.add_argument('--recursive', action='store_true', help='include the .c files of subfolders too')
    ap.add_argument('--file', nargs='*', default=[], help='restrict to these files inside the folder')
    ap.add_argument('--skip-list', type=Path, help='files owned by other lanes (one path per line)')
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--workers', type=int, default=4)
    ap.add_argument('--data', action='store_true', help='also move data externs (opt-in)')
    ap.add_argument('--deps-cache', type=Path, help='reuse clang -MM closures across runs (.json.gz)')
    ap.add_argument('--dry-run', action='store_true', help='plan, byte-decide and prove; restore every file')
    args = ap.parse_args(argv)
    if not 1 <= args.workers <= 6:
        ap.error('between 1 and 6 workers on this host')
    root = args.root.resolve()
    sys.path.insert(0, str(root / 'tools'))
    import layout_compile_identity as L
    import prove
    import tu_identity as T
    out = args.out
    out.mkdir(parents=True, exist_ok=True)
    logf = open(out / 'wave.log', 'a')

    def log(msg):
        line = time.strftime('%H:%M:%S ') + msg
        print(line, flush=True)
        logf.write(line + '\n')
        logf.flush()

    folder = args.folder.rstrip('/')
    skip = set()
    if args.skip_list:
        skip = {l.strip() for l in args.skip_list.read_text().splitlines() if l.strip() and not l.startswith('#')}
    pattern = '**/*.c' if args.recursive else '*.c'
    allf = sorted(p.relative_to(root).as_posix() for p in (root / folder).glob(pattern))
    files = [f for f in allf if f not in skip and (not args.file or f in args.file or Path(f).name in args.file)]
    log(f'{folder}: {len(files)} files ({len(set(allf) & skip)} skipped), data={args.data}')
    plan, jobs, texts, holds = plan_folder(root, files, args.data, skip)
    log(f'plan: {len(jobs)} TUs with edits, {len(texts)} headers to write (new or appended), {len(holds)} static holds')
    physical, _members = L.recipes(root)
    changed_headers = [h for h, t in texts.items() if read(root, h) != t]
    original = {f: read(root, f) for f in list(jobs) + list(texts)}
    if not jobs:
        (out / 'receipt.json').write_text(json.dumps({'folder': folder, 'files': len(files), 'jobs': 0}, indent=1))
        _tsv(out / 'holds.tsv', ('tu', 'header', 'reason'), holds)
        log('nothing to do')
        return 0
    try:
        deps = dependencies(root, physical, args.workers, args.deps_cache)
        log('dependency closures of %d physical TUs' % len(physical))
        tus = proof_set(root, set(jobs) | set(changed_headers), physical, deps)
        log(f'proof set: {len(tus)} physical TUs (headers rewritten: {len(changed_headers)})')
        before = {r['source']: r for r in T.capture(root, tus, physical, args.workers)}
        bad_before = sorted(t for t, r in before.items() if 'error' in r)
        if bad_before:
            log('baseline capture errors (edits they see are rolled back): %s' % bad_before[:5])
        # 3. headers + byte decision + TU edits
        for h, t in texts.items():
            write(root, h, t)
        recipes, _ = L.recipes(root)
        verdicts = prove.run(root, jobs, recipes, workers=args.workers, log=log)
        accepted = {}
        seen_by_physical = set().union(*deps.values()) if deps else set()
        for rel, v in verdicts.items():
            # prove.py's -S filter cannot compile SLUS partitions or members of a physical TU; their edits
            # are decided by the complete-TU identity of the physical TUs that see them (step 4).
            hs = v.get('holds', {})
            if hs and all(w in TENTATIVE for w in hs.values()) and rel in seen_by_physical:
                v['accept'] = sorted(set(v.get('accept', [])) | set(hs))
                v['holds'] = {}
                v['tentative'] = True
        for rel, (orig, edit) in sorted(jobs.items()):
            v = verdicts.get(rel, {'accept': [], 'holds': {}})
            for h, why in sorted(v.get('holds', {}).items()):
                holds.append((rel, h, why))
            new = R.edit_tu(orig, edit, v['accept'])
            if not v['accept'] and edit.get('drop'):
                new = R.edit_tu(orig, dict(edit, add=[]), [])
            write(root, rel, new)
            accepted[rel] = v['accept']
        def sync_headers():
            """Headers carry exactly what the TUs still edited need (unused new headers are not created)."""
            kept = {rel: accepted[rel] for rel in jobs if read(root, rel) != original[rel]}
            for h in texts:
                write(root, h, original[h])
            for h, t in header_texts(root, plan, kept).items():
                write(root, h, t)

        def restore(rel, header, why):
            if read(root, rel) != original[rel]:
                write(root, rel, original[rel])
                holds.append((rel, header, why))

        # 4. proof + rollback, 5. debt ratchet; repeated until the final state is the proven state
        sync_headers()
        rounds = 0
        while True:
            rounds += 1
            if rounds > 8:
                raise RuntimeError('rollback did not converge')
            edited = {f for f in original if read(root, f) != original[f]}
            check = [t for t in tus if (deps.get(t, {t}) | {t}) & edited]   # capture errors fail too
            after = {r['source']: r for r in T.capture(root, check, physical, args.workers)}
            failed = [t for t in check if not identical(before[t], after[t])]
            log(f'proof round {rounds}: {len(check) - len(failed)}/{len(check)} TUs identical'
                + (f'; changed: {failed[:6]}' if failed else ''))
            if not failed:
                rises = [rel for rel in sorted(jobs) if read(root, rel) != original[rel]
                         and debt_rises(rel, original[rel], read(root, rel))]
                if not rises:
                    break
                for rel in rises:
                    restore(rel, '*', 'debt_rise')
                    log('debt rise, restored ' + rel)
                sync_headers()
                continue
            for t in failed:
                mine = (deps.get(t, set()) | {t}) & edited
                own = [f for f in mine if f.endswith('.c')]
                hdrs = [f for f in mine if f.endswith('.h')]
                if not own and not hdrs:
                    raise RuntimeError(f'{t} changed without an edited input: {after[t].get("error", "")[:200]}')
                if own and rounds == 1 and len(own) > 1:
                    # several edited members/partitions of one physical TU: keep each that leaves it identical
                    edits = {f: read(root, f) for f in own}
                    for f in own:
                        write(root, f, original[f])
                    if not identical(before[t], T._capture((str(root), t, physical[t]))):
                        for f in own:      # a header change alone already changes it: next round
                            holds.append((f, '*', 'tu_identity_changed:' + t))
                        continue
                    for f in sorted(own):
                        write(root, f, edits[f])
                        if identical(before[t], T._capture((str(root), t, physical[t]))):
                            continue
                        restore(f, '*', 'tu_identity_changed:' + t)
                    log(f'per-file retry in {t}: kept {sum(read(root, f) != original[f] for f in own)}/{len(own)}')
                    continue
                for f in own:
                    restore(f, '*', 'tu_identity_changed:' + t)
                if own and rounds == 1:
                    continue        # first try the TU's own edit; its headers only if it still changes
                for h in hdrs:
                    for rel, (orig, edit) in jobs.items():
                        if h in accepted.get(rel, []):
                            restore(rel, h, 'header_consumer_changed:' + t)
            sync_headers()
        # 6. receipt
        final = {f: read(root, f) for f in original}
        changed = sorted(f for f in original if final[f] != original[f])
        rows = []
        for f in sorted(f for f in changed if f.endswith('.c')):
            rows.append((f, local_externs(f, original[f]), local_externs(f, final[f]), sha(original[f]),
                         sha(final[f])))
        before_total = sum(local_externs(f, read(root, f) if f not in original else original[f]) for f in files)
        after_total = sum(local_externs(f, read(root, f)) for f in files)
        patch = []
        for f in changed:
            patch.extend(difflib.unified_diff((original[f] or '').splitlines(True), (final[f] or '').splitlines(True),
                                              'a/' + f if original[f] is not None else '/dev/null', 'b/' + f))
        (out / 'folder.patch').write_text(''.join(patch))
        _tsv(out / 'holds.tsv', ('tu', 'header', 'reason'), holds)
        _tsv(out / 'files.tsv', ('file', 'local_externs_before', 'local_externs_after', 'sha256_before',
                                 'sha256_after'), rows)
        proven = sorted(t for t in tus if t not in bad_before)
        receipt = {
            'folder': folder, 'data': args.data, 'files': len(files), 'skipped': sorted(set(allf) & skip),
            'tus_with_edits': len(jobs), 'files_changed': len([f for f in changed if f.endswith('.c')]),
            'headers_changed': [f for f in changed if f.endswith('.h')],
            'local_externs_before': before_total, 'local_externs_after': after_total,
            'proof_set': len(tus), 'proof_rounds': rounds, 'baseline_capture_errors': bad_before,
            'holds_by_reason': dict(Counter(w.split(':')[0] for _, _, w in holds).most_common()),
            'proven_identical_tus': len(proven),
            'tentative_tus_kept': sorted(r for r, v in verdicts.items() if v.get('tentative')
                                         and read(root, r) != original[r]),
        }
        (out / 'receipt.json').write_text(json.dumps(receipt, indent=1, sort_keys=True) + '\n')
        log(f'local externs {before_total} -> {after_total}; {receipt["files_changed"]} files, '
            f'{len(receipt["headers_changed"])} headers changed; holds {receipt["holds_by_reason"]}')
        if args.dry_run:
            raise KeyboardInterrupt
        return 0
    except KeyboardInterrupt:
        for f, text in original.items():
            if read(root, f) != text:
                write(root, f, text)
        log('dry run / interrupted: every file restored')
        return 0 if args.dry_run else 130
    except BaseException:
        for f, text in original.items():
            if read(root, f) != text:
                write(root, f, text)
        log('failed: every file restored')
        raise


def _tsv(path, header, rows):
    with open(path, 'w') as fh:
        fh.write('\t'.join(header) + '\n')
        for r in rows:
            fh.write('\t'.join(str(x).replace('\t', ' ').replace('\n', ' ') for x in r) + '\n')


if __name__ == '__main__':
    sys.exit(main())
