#!/usr/bin/env python3
"""Prove an anchored manual/prototype transaction and roll it back on failure."""
import argparse
from concurrent.futures import ProcessPoolExecutor
from dataclasses import fields
import hashlib
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT), str(ROOT / 'tools'), str(Path(__file__).resolve().parent)]
from tools.proto import prototypes as P
import layout_compile_identity as L
from layout_dependencies import consumer_paths, include_parents
from probe_sources import capture, native_errors, same


def inspect(job):
    path, recipe = job
    return path, dict(capture(path, recipe), native_errors=native_errors(path))


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--manual', type=Path, required=True)
    ap.add_argument('--edits', type=Path)
    ap.add_argument('--out', type=Path, required=True)
    args = ap.parse_args()
    if not args.manual.is_file():
        ap.error('--manual must name an existing TSV')
    if args.edits is not None and not args.edits.is_file():
        ap.error('--edits must name an existing TSV')
    if args.out.exists():
        raise SystemExit('use a new proof directory')
    args.out.mkdir(parents=True)
    (args.out / '.ignore').write_text('baseline/\n')
    rows = P.table(args.manual)
    keys = {f.name for f in fields(P.Edit)}
    edits = []
    for row in P.table(args.edits) if args.edits else []:
        values = {k: v for k, v in row.items() if k in keys}
        values['occurrences'] = int(values.get('occurrences') or 1)
        edits.append(P.Edit(**values))
    paths = {r['file'] for r in rows} | {e.file for e in edits}
    if not paths:
        ap.error('transaction has no manual or declaration edits')
    originals = {p: (ROOT / p).read_text() for p in paths}
    texts = dict(originals)
    for r in rows:
        if texts[r['file']].count(r['before']) != 1:
            raise SystemExit('manual anchor not unique: ' + r['file'] + ':' + r['function'])
        texts[r['file']] = texts[r['file']].replace(r['before'], r['after'], 1)
    for path in {e.file for e in edits}:
        texts[path] = P.rewrite(texts[path], [e for e in edits if e.file == path])
    physical, _ = L.recipes(ROOT)
    users = set(physical) & consumer_paths(ROOT, paths, parents=include_parents(ROOT))
    # Production dependency records supplement the quoted include graph with
    # generated physical inputs and preprocessor-discovered dependencies.
    for folder in ('recipes', 'slus-recipes'):
        for spec in (ROOT / 'build/.state' / folder).glob('*.json'):
            doc = json.loads(spec.read_text())
            if paths & (set(doc['dependencies']) | {doc.get('source', '')}):
                users.update(set(physical) & {doc.get('source', '')})
    if any(p.startswith('src/') and p not in users for p in paths):
        raise SystemExit('edited source has no physical proof recipe')
    for p, text in originals.items():
        backup = args.out / 'baseline' / p
        backup.parent.mkdir(parents=True, exist_ok=True)
        backup.write_text(text)
    (args.out / 'consumers.json').write_text(json.dumps(sorted(users), indent=2) + '\n')
    print(json.dumps(dict(phase='baseline', files=len(paths), consumers=len(users))), flush=True)
    with ProcessPoolExecutor(max_workers=4) as pool:
        jobs = [(p, physical[p]) for p in sorted(users)]
        before = dict(pool.map(inspect, jobs))
        (args.out / 'before.jsonl').write_text(''.join(json.dumps(r, sort_keys=True) + '\n' for r in before.values()))
        if any('error' in r for r in before.values()):
            raise SystemExit('baseline compile failed')
        try:
            for p, text in texts.items():
                (ROOT / p).write_text(text)
            print(json.dumps(dict(phase='after', consumers=len(users))), flush=True)
            after = dict(pool.map(inspect, jobs))
            (args.out / 'after.jsonl').write_text(''.join(json.dumps(r, sort_keys=True) + '\n' for r in after.values()))
            failures = [dict(source=p, error=after[p].get('error', ''),
                             identity_equal='error' not in after[p] and same(before[p], after[p]),
                             new_native_errors=list(after[p]['native_errors'] - before[p]['native_errors']))
                        for p in sorted(users) if 'error' in after[p] or not same(before[p], after[p])
                        or after[p]['native_errors'] - before[p]['native_errors']]
            (args.out / 'failures.json').write_text(json.dumps(failures, indent=2) + '\n')
            if failures:
                raise ValueError('transaction rejected: ' + ', '.join(r['source'] for r in failures))
        except BaseException:
            for p, text in originals.items():
                (ROOT / p).write_text(text)
            raise
    receipts = [dict(source=p, raw_equal=True, canonical_assembly_equal=True,
                     canonical_object_equal=True, new_native_errors=0,
                     source_sha256=hashlib.sha256((ROOT / p).read_bytes()).hexdigest(),
                     **{k: v for k, v in before[p].items() if k.endswith('sha256')})
                for p in sorted(users)]
    (args.out / 'proof.jsonl').write_text(''.join(json.dumps(r, sort_keys=True) + '\n' for r in receipts))
    print(json.dumps(dict(accepted=True, changed_files=len(paths), consumers=len(users))), flush=True)


if __name__ == '__main__':
    main()
