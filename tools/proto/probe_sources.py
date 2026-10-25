#!/usr/bin/env python3
"""Apply independent source-only transactions after complete-TU object identity.

Retains only raw + canonical-assembly + canonical-object equal changes. A failed
file is retried one declaration at a time, so one promotion-sensitive call does
not prevent independent declarations in that TU from becoming checked.
"""
import argparse
from concurrent.futures import ProcessPoolExecutor, as_completed
from dataclasses import asdict
import hashlib
import json
from pathlib import Path
import re
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT), str(ROOT / 'tools')]
from tools.proto import prototypes as P
import layout_compile_identity as L
from tools.build.compile_slots import acquire


def same(before, after):
    return all(before[k] == after[k] for k in
               ('raw_sha256', 'canonical_assembly_sha256', 'canonical_object_sha256'))


def capture(path, recipe):
    try:
        with acquire():
            return L.capture_one(ROOT, path, recipe)
    except Exception as exc:
        return {'error': str(exc).replace(str(ROOT) + '/', '')}


def diagnostic_keys(stderr, root):
    """Keep errors tied to their source/function/column when lines move.

    Comparing message counts alone can let a removed outer-call error mask
    an identical new inner-call error. Declaration edits preserve body text,
    so source text and columns give stable anchors without line numbers.
    """
    from collections import Counter
    from bisect import bisect_right
    from itertools import accumulate
    cache, keys = {}, Counter()
    for match in re.finditer(r'(?m)^(.*?):(\d+):(\d+): (?:fatal )?error: (.*)$', stderr):
        filename, line, column, message = match.groups()
        target = Path(filename)
        target = target if target.is_absolute() else root / target
        try:
            name = target.resolve().relative_to(root.resolve()).as_posix()
        except ValueError:
            name = target.name
        if target not in cache:
            try:
                text = target.read_text(errors='replace')
                scan = P.cscan.scan(text)
                lines = text.splitlines(keepends=True)
                functions = [item for item in scan.items if item.kind == 'def']
                cache[target] = (lines, list(accumulate(map(len, lines), initial=0)),
                                 functions, [item.start for item in functions])
            except OSError:
                cache[target] = ([], [0], [], [])
        lines, offsets, functions, starts = cache[target]
        row = int(line) - 1
        context = lines[row].rstrip('\r\n') if 0 <= row < len(lines) else ''
        offset = offsets[row] + int(column) - 1 if 0 <= row < len(lines) else 0
        owner = ''
        index = bisect_right(starts, offset) - 1
        if index >= 0 and offset < functions[index].end:
            owner = functions[index].decls[0].name
        key = json.dumps([name, owner, P.compact(context), int(column), message], ensure_ascii=True)
        keys[key] += 1
    return keys


def native_errors(path, root=ROOT):
    with acquire():
        result = subprocess.run(['clang', '--target=mipsel-unknown-none', '-fsyntax-only', '-std=gnu89',
                                 '-Wno-everything', '-Werror=incompatible-pointer-types',
                                 '-Werror=int-conversion', '-ferror-limit=0', '-Iinclude', path],
                                cwd=root, text=True, capture_output=True)
    errors = diagnostic_keys(result.stderr, root)
    if result.returncode and not errors:
        raise RuntimeError(path + ": native compiler failed without a located diagnostic")
    return errors


def worker(job):
    path, recipe, edits, out = job
    before_text = (ROOT / path).read_text()
    baseline = Path(out) / 'baseline' / path
    baseline.parent.mkdir(parents=True, exist_ok=True)
    baseline.write_text(before_text)
    before = capture(path, recipe)
    if 'error' in before:
        return path, [], [dict(file=path, symbol=e.symbol, reason='baseline_compile_error',
                               evidence=before['error']) for e in edits], {'source': path, **before}
    accepted, rejected = [], []
    errors_before = native_errors(path)
    try:
        (ROOT / path).write_text(P.rewrite(before_text, edits))
        after = capture(path, recipe)
        errors_after = native_errors(path) - errors_before
        if 'error' not in after and same(before, after) and not errors_after:
            accepted = edits
        else:
            (ROOT / path).write_text(before_text)
            for edit in edits:
                (ROOT / path).write_text(P.rewrite(before_text, accepted + [edit]))
                trial = capture(path, recipe)
                errors_trial = native_errors(path) - errors_before
                if 'error' not in trial and same(before, trial) and not errors_trial:
                    accepted.append(edit)
                else:
                    rejected.append(dict(file=path, symbol=edit.symbol,
                                         reason='prototype_compile_error' if 'error' in trial else
                                                'native_type_error' if errors_trial else 'byte_change',
                                         evidence=trial.get('error', '; '.join(errors_trial) if errors_trial else
                                                            'raw or canonical object changed'),
                                         definition=edit.definition))
            (ROOT / path).write_text(P.rewrite(before_text, accepted) if accepted else before_text)
            after = capture(path, recipe) if accepted else before
        if 'error' in after or not same(before, after):
            raise ValueError('final transaction identity failed: ' + str(after))
        receipt = dict(source=path, recipe=recipe, raw_equal=True,
                       canonical_assembly_equal=True, canonical_object_equal=True,
                       raw_sha256=before['raw_sha256'],
                       canonical_assembly_sha256=before['canonical_assembly_sha256'],
                       canonical_object_sha256=before['canonical_object_sha256'],
                       accepted=[e.symbol for e in accepted], rejected=[r['symbol'] for r in rejected],
                       source_sha256=hashlib.sha256((ROOT / path).read_bytes()).hexdigest())
        return path, accepted, rejected, receipt
    except Exception as exc:
        (ROOT / path).write_text(before_text)
        error = str(exc).replace(str(ROOT) + '/', '')
        return path, [], [dict(file=path, symbol=e.symbol, reason='transaction_error',
                               evidence=error) for e in edits], {'source': path, 'error': error}
    except BaseException:
        (ROOT / path).write_text(before_text)
        raise


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--scope', nargs='+', required=True)
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--wide-only', action='store_true')
    ap.add_argument('--symbols', nargs='+', default=[])
    ap.add_argument('--skip', type=Path)
    ap.add_argument('--plan', type=Path, help='previously generated declaration plan')
    args = ap.parse_args()
    for option in ('plan', 'skip'):
        path = getattr(args, option)
        if path is not None and not path.is_file():
            ap.error('--' + option + ' must name an existing TSV')
    if args.out.exists():
        raise SystemExit('use a new batch output directory')
    args.out.mkdir(parents=True)
    (args.out / '.ignore').write_text('baseline/\n')
    if args.plan:
        records = P.table(args.plan)
        edits = [P.Edit(**{**r, 'occurrences': int(r.get('occurrences') or 1)}) for r in records
                 if any(r['file'] == p or r['file'].startswith(p.rstrip('/') + '/') for p in args.scope)
                 and (not args.symbols or r['symbol'] in args.symbols)]
        remaining, holds = records, []
    else:
        _, _, remaining, edits, holds = P.candidates(ROOT, args.scope,
            skip=P.table(args.skip) if args.skip else (), wide_only=args.wide_only, symbols=args.symbols)
    P.write_table(args.out / 'plan.tsv', [asdict(e) for e in edits], P.MAP_FIELDS)
    physical, _ = L.recipes(ROOT)
    by_file = {}
    for e in edits:
        if e.file not in physical:
            holds.append(dict(file=e.file, symbol=e.symbol, reason='not_a_registered_physical_tu',
                              definition=e.definition, evidence=e.evidence))
        else:
            by_file.setdefault(e.file, []).append(e)
    accepted, rejected, proofs = [], [], []
    print(json.dumps(dict(remaining_before=len(remaining), proposed=len(edits), physical_tus=len(by_file))), flush=True)
    with ProcessPoolExecutor(max_workers=4) as pool:
        jobs = [pool.submit(worker, (p, physical[p], es, str(args.out))) for p, es in sorted(by_file.items())]
        for future in as_completed(jobs):
            path, yes, no, proof = future.result()
            accepted.extend(yes)
            rejected.extend(no)
            proofs.append(proof)
            P.write_table(args.out / 'replay.tsv', [asdict(e) for e in accepted], P.MAP_FIELDS)
            P.write_table(args.out / 'holds.tsv', holds + rejected, P.HOLD_FIELDS)
            (args.out / 'proof.jsonl').write_text(''.join(json.dumps(p, sort_keys=True) + '\n' for p in proofs))
            print(json.dumps(dict(done=len(proofs), total=len(by_file), source=path,
                                  accepted=len(yes), rejected=len(no))), flush=True)
    summary = dict(remaining_before=len(remaining), declarations=sum(int(e.occurrences) for e in accepted),
                   changed_files=len({e.file for e in accepted}), probed_tus=len(proofs),
                   rejected=len(rejected), holds=len(holds))
    (args.out / 'summary.json').write_text(json.dumps(summary, indent=2, sort_keys=True) + '\n')
    (args.out / 'files.txt').write_text(''.join(p + '\n' for p in sorted({e.file for e in accepted})))
    print(json.dumps(summary), flush=True)


if __name__ == '__main__':
    main()
