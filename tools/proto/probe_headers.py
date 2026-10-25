#!/usr/bin/env python3
"""Prove one header transaction at a time over every physical consumer.

Consumer discovery combines the quoted include graph and clang -MM (including
generated SLUS partition parents). Compilation uses at most four workers.
"""
import argparse
from concurrent.futures import ProcessPoolExecutor
from dataclasses import asdict
import hashlib
import json
import os
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT), str(ROOT / 'tools'), str(ROOT / 'tools/typing'), str(Path(__file__).resolve().parent)]
from tools.proto import prototypes as P
import layout_compile_identity as L
from layout_dependencies import consumer_paths, include_parents
from probe_sources import capture, native_errors, same
from tu_identity import _mm as _unlimited_mm
from tools.headers.prove import _gcc_s as _unlimited_gcc_s
from tools.build.compile_slots import acquire


def _gcc_s(*args):
    with acquire():
        return _unlimited_gcc_s(*args)


def _mm(job):
    with acquire():
        return _unlimited_mm(job)


def inspect(job):
    path, recipe, before = job
    errors = native_errors(path)
    if before is not None:
        delta = errors - before['native_errors']
        if delta:
            return path, dict(error='; '.join(delta), reason='native_type_error', native_errors=errors)
    result = capture(path, recipe)
    result['native_errors'] = errors
    if before is None and recipe['container'] != 'slus' and 'error' not in result:
        assembly, error = _gcc_s(ROOT, path, recipe, (ROOT / path).read_text())
        if assembly is not None:
            result['fast_assembly_sha256'] = hashlib.sha256(assembly).hexdigest()
    return path, result


def inspect_fast(job):
    path, recipe, before = job
    delta = native_errors(path) - before['native_errors']
    if delta:
        return path, dict(error='; '.join(delta), reason='native_type_error', fast_equal=False)
    if before.get('fast_assembly_sha256'):
        assembly, error = _gcc_s(ROOT, path, recipe, (ROOT / path).read_text())
        if assembly is None:
            return path, dict(error=error, reason='prototype_compile_error', fast_equal=False)
        if hashlib.sha256(assembly).hexdigest() == before['fast_assembly_sha256']:
            return path, dict(fast_equal=True)
    result = capture(path, recipe)
    result['fast_equal'] = 'error' not in result and same(before, result)
    return path, result


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--scope', nargs='+', required=True)
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--skip', type=Path)
    ap.add_argument('--plan', type=Path, help='previously generated declaration plan')
    ap.add_argument('--consumers', type=Path, help='previous -MM union, after verifying quoted closure has not grown')
    args = ap.parse_args()
    for option in ('plan', 'skip', 'consumers'):
        path = getattr(args, option)
        if path is not None and not path.is_file():
            ap.error('--' + option + ' must name an existing input file')
    if args.out.exists():
        raise SystemExit('use a new batch directory')
    args.out.mkdir(parents=True)
    (args.out / 'process.json').write_text(json.dumps(dict(pid=os.getpid(), parent=os.getppid())) + '\n')
    (args.out / '.ignore').write_text('baseline/\n')
    if args.plan:
        records = P.table(args.plan)
        edits = [P.Edit(**{**r, 'occurrences': int(r.get('occurrences') or 1)}) for r in records
                 if any(r['file'] == p or r['file'].startswith(p.rstrip('/') + '/') for p in args.scope)]
        remaining, holds = records, []
    else:
        _, _, remaining, edits, holds = P.candidates(ROOT, args.scope,
            skip=P.table(args.skip) if args.skip else ())
    groups = {}
    for edit in edits:
        groups.setdefault(edit.file, []).append(edit)
    P.write_table(args.out / 'plan.tsv', [asdict(e) for e in edits], P.MAP_FIELDS)
    physical, _ = L.recipes(ROOT)
    parents = include_parents(ROOT)
    users = {h: set(physical) & consumer_paths(ROOT, {h}, parents=parents) for h in groups}
    print(json.dumps(dict(headers=len(groups), proposals=len(edits), phase='dependency_closure')), flush=True)
    accepted, rejected, proofs = [], [], []
    # A persistent pool keeps imports/recipe caches warm. Header writes are
    # sequential; each pool.map is fully drained before the next write.
    with ProcessPoolExecutor(max_workers=4) as pool:
        cached = json.loads(args.consumers.read_text()) if args.consumers else {}
        cache_valid = all(h in cached and users[h] <= set(cached[h]) <= set(physical) for h in groups)
        if cache_valid:
            users = {h: set(cached[h]) for h in groups}
        else:
            for source, deps in pool.map(_mm, [(str(ROOT), p, r) for p, r in sorted(physical.items())], chunksize=32):
                for header in set(deps) & groups.keys():
                    users[header].add(source)
        (args.out / 'consumers.json').write_text(json.dumps({h: sorted(v) for h, v in users.items()}, sort_keys=True, indent=2) + '\n')
        for index, (header, es) in enumerate(sorted(groups.items()), 1):
            sources = sorted(users[header])
            text = (ROOT / header).read_text()
            backup = args.out / 'baseline' / header
            backup.parent.mkdir(parents=True, exist_ok=True)
            backup.write_text(text)
            yes, no = [], []
            if not sources:
                no = [dict(file=header, symbol=e.symbol, reason='no_live_physical_consumer',
                           definition=e.definition, evidence=e.evidence) for e in es]
            else:
                before = dict(pool.map(inspect, [(p, physical[p], None) for p in sources]))
                baseline_errors = [p for p, r in before.items() if 'error' in r]
                def trial(proposals):
                    (ROOT / header).write_text(P.rewrite(text, proposals) if proposals else text)
                    after = dict(pool.map(inspect_fast, [(p, physical[p], before[p]) for p in sources]))
                    bad = [p for p, r in after.items() if not r['fast_equal']]
                    return after, bad
                try:
                    if baseline_errors:
                        no = [dict(file=header, symbol=e.symbol, reason='baseline_compile_error',
                                   evidence=baseline_errors[0] + ': ' + before[baseline_errors[0]]['error']) for e in es]
                    else:
                        after, bad = trial(es)
                        if not bad:
                            yes = es
                        else:
                            (ROOT / header).write_text(text)
                            for edit in es:
                                after, bad = trial(yes + [edit])
                                if not bad:
                                    yes.append(edit)
                                else:
                                    p = bad[0]
                                    result = after[p]
                                    no.append(dict(file=header, symbol=edit.symbol,
                                        reason=result.get('reason', 'prototype_compile_error' if 'error' in result else 'byte_change'),
                                        definition=edit.definition, evidence=p + ': ' + result.get('error', 'raw or canonical identity changed')))
                            after, bad = trial(yes)
                            if bad:
                                raise ValueError('final accepted header failed identity: ' + header)
                        if yes:
                            # The assembly prefilter only saves repeated raw
                            # assembly work. Every final header transaction
                            # still receives the complete three-part proof.
                            after = dict(pool.map(inspect, [(p, physical[p], before[p]) for p in sources]))
                            bad = [p for p, r in after.items() if 'error' in r or not same(before[p], r)]
                            if bad:
                                raise ValueError('complete final header identity failed: ' + header)
                            for p in sources:
                                r = before[p]
                                proofs.append(dict(header=header, source=p, raw_equal=True,
                                    canonical_assembly_equal=True, canonical_object_equal=True,
                                    raw_sha256=r['raw_sha256'],
                                    canonical_assembly_sha256=r['canonical_assembly_sha256'],
                                    canonical_object_sha256=r['canonical_object_sha256'], new_native_errors=0))
                except BaseException:
                    (ROOT / header).write_text(text)
                    raise
            accepted.extend(yes)
            rejected.extend(no)
            P.write_table(args.out / 'replay.tsv', [asdict(e) for e in accepted], P.MAP_FIELDS)
            P.write_table(args.out / 'holds.tsv', holds + rejected, P.HOLD_FIELDS)
            (args.out / 'proof.jsonl').write_text(''.join(json.dumps(p, sort_keys=True) + '\n' for p in proofs))
            print(json.dumps(dict(done=index, total=len(groups), header=header, consumers=len(sources),
                                  accepted=len(yes), rejected=len(no))), flush=True)
    summary = dict(remaining_before=len(remaining), declarations=sum(int(e.occurrences) for e in accepted),
                   changed_headers=len({e.file for e in accepted}), proofs=len(proofs), rejected=len(rejected), holds=len(holds))
    (args.out / 'summary.json').write_text(json.dumps(summary, indent=2, sort_keys=True) + '\n')
    (args.out / 'files.txt').write_text(''.join(p + '\n' for p in sorted({e.file for e in accepted})))
    print(json.dumps(summary), flush=True)


if __name__ == '__main__':
    main()
