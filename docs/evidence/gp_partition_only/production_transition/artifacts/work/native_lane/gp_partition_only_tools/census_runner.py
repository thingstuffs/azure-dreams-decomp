#!/usr/bin/env python3
"""Run unchanged private fidelity code with per-worker short ASPSX scratch.

The fixture must contain the complete current registry and both build roots.
No production module, source, verifier result, or assembler override is patched.
"""
from __future__ import annotations

import argparse
from concurrent.futures import ThreadPoolExecutor
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import time


def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--fixture', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--workers', type=int, default=4)
    parser.add_argument('--worker')
    parser.add_argument('--only', help='comma-separated probe IDs; omit for the complete census')
    args = parser.parse_args()
    fixture = args.fixture.resolve()
    out = args.output.resolve()
    if out == fixture or not out.is_relative_to(fixture.parent):
        raise ValueError('census output must be separate, within the private fixture parent')
    os.chdir(fixture)
    for name in ('AZURE_MASPSX', 'AZURE_MASPSX_COMPANION', 'PYTHONPATH'):
        os.environ.pop(name, None)
    sys.path[:0] = [str(fixture / 'tools'), str(fixture / 'tools/build'),
                   str(fixture / 'tools/fidelity')]
    import common
    from fidelity import aspsx_diff as A
    import verify
    if any(root != fixture for root in (common.ROOT, A.ROOT, verify.ROOT)):
        raise ValueError('census imported non-private tools')
    by_id = {row['id']: row for row in common.rows()}
    if len(by_id) != 6767:
        raise ValueError('fixture does not contain all 6767 registered rows')
    if args.worker:
        row = by_id[args.worker]
        scratch = Path(tempfile.mkdtemp(prefix='pgc_', dir='/tmp'))
        A.TMP = scratch
        A._SLUS = None
        record = None
        try:
            record = A.process_row(row)
            print(json.dumps(record, separators=(',', ':')), flush=True)
        finally:
            if record and record.get('status') == 'ok':
                shutil.rmtree(scratch)
            else:
                print('retained failed worker scratch: ' + str(scratch), file=sys.stderr)
        return

    if not 1 <= args.workers <= 8:
        raise ValueError('workers must be between one and eight')
    selected = list(by_id.values())
    if args.only:
        ids = args.only.split(',')
        if len(set(ids)) != len(ids) or not set(ids) <= set(by_id):
            raise ValueError('invalid probe row IDs')
        selected = [by_id[rid] for rid in ids]
    out.mkdir(parents=True, exist_ok=True)
    (out / '.ignore').write_text('*\n')
    if (out / 'journal.jsonl').exists():
        raise ValueError('output already contains a journal; choose a fresh run directory')
    sources = {row['id']: sha(common.clean_path(row)) for row in selected}
    fp = A.tool_fingerprint()
    runner = Path(__file__).resolve()
    runner_sha = sha(runner)
    versions = list(A.VERSIONS)
    registry_sha = sha(fixture / 'ledger/rows.jsonl')
    pair = ('maspsx.py', 'maspsx/__init__.py')
    assembler = {base + '/' + name: sha(fixture / base / name)
                 for base in ('tools/maspsx', 'toolchain/maspsx') for name in pair}
    for name in pair:
        if assembler['tools/maspsx/' + name] != assembler['toolchain/maspsx/' + name]:
            raise ValueError('trace and build assemblers differ')
    keys = {row['id']: A.row_key(row, common.clean_path(row).read_text(errors='replace'),
                                fp, row['cfg'], row.get('row_asflags') or '')
            for row in selected}
    inputs = {'fixture': str(fixture), 'runner_sha256': runner_sha,
              'registry_sha256': registry_sha, 'tool_fingerprint': fp,
              'versions': versions, 'assembler': assembler, 'source_sha256': sources,
              'rows': len(selected), 'whole_registry': not bool(args.only),
              'workers': args.workers}
    (out / 'inputs.json').write_text(json.dumps(inputs, indent=2) + '\n')

    def one(row):
        proc = subprocess.run(common.NICE + [sys.executable, str(runner),
            '--fixture', str(fixture), '--output', str(out), '--worker', row['id']],
            cwd=fixture, text=True, capture_output=True, timeout=3600)
        try:
            record = json.loads(proc.stdout.strip().splitlines()[-1])
            if proc.returncode or record.get('row') != row['id']:
                raise ValueError('worker result/exit mismatch')
        except (IndexError, ValueError):
            record = {'row': row['id'], 'kind': row['kind'], 'container': row['container'],
                      'status': 'error', 'err': (proc.stderr or proc.stdout)[-4000:]}
        if record.get('status') != 'ok':
            name = row['id'].replace('/', '__')
            (out / (name + '.log')).write_text(proc.stdout + proc.stderr)
        record['key'] = keys[row['id']]
        record['at'] = time.strftime('%Y-%m-%dT%H:%M:%SZ', time.gmtime())
        return record

    started = time.monotonic()
    counts = {}
    results = []
    with ThreadPoolExecutor(max_workers=args.workers) as pool, (out / 'journal.jsonl').open('w') as journal:
        for index, record in enumerate(pool.map(one, selected), 1):
            results.append(record)
            counts[record['status']] = counts.get(record['status'], 0) + 1
            journal.write(json.dumps(record, separators=(',', ':')) + '\n')
            journal.flush()
            if index % 100 == 0 or index == len(selected):
                print(json.dumps({'complete': index, 'selected': len(selected),
                                  'status': counts, 'elapsed': round(time.monotonic() - started)}), flush=True)
    if (sha(runner) != runner_sha or A.tool_fingerprint() != fp or A.VERSIONS != versions
            or sha(fixture / 'ledger/rows.jsonl') != registry_sha
            or {row['id']: sha(common.clean_path(row)) for row in selected} != sources
            or {name: sha(fixture / name) for name in assembler} != assembler):
        raise ValueError('census inputs changed during measurement')
    summary = {'status': 'MEASURED', 'rows': len(results), 'counts': counts,
               'whole_registry': not bool(args.only), 'journal_sha256': sha(out / 'journal.jsonl'),
               'inputs_sha256': sha(out / 'inputs.json'), 'unchanged_inputs': True,
               'maspsx_exact': sum(r.get('maspsx_exact') is True for r in results),
               'selfcheck': sum(r.get('selfcheck') is True for r in results),
               'genuine_exact_some_version': sum(bool(r.get('exact_versions')) for r in results),
               'elapsed_seconds': round(time.monotonic() - started, 1)}
    (out / 'receipt.json').write_text(json.dumps(summary, indent=2) + '\n')
    print(json.dumps(summary), flush=True)
    if counts.get('error') or summary['maspsx_exact'] != len(results) or summary['selfcheck'] != len(results):
        raise SystemExit(1)


if __name__ == '__main__':
    main()
