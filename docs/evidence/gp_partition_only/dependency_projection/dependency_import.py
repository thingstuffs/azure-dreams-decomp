#!/usr/bin/env python3
"""Prepare a dependency projection, or validate a fresh production census.

This script never writes production files. A validated proposal can be reviewed
and installed under land.lock, followed by levels/status and certificate checks.
Private fixture keys are deliberately inadmissible for production validation.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
sys.path[:0] = [str(ROOT/'tools'), str(ROOT/'tools/fidelity')]
import aspsx_report as report


def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def read_lines(path):
    return [json.loads(line) for line in Path(path).read_text().splitlines() if line.strip()]


def unique(records, key):
    out = {r[key]: r for r in records}
    if len(out) != len(records):
        raise ValueError('duplicate identity: ' + key)
    return out


def validate_records(records, row_ids):
    by = unique(records, 'row')
    if set(by) != set(row_ids):
        raise ValueError('census does not cover exactly the registered identities')
    for rid, record in by.items():
        if (record.get('status') != 'ok' or record.get('maspsx_exact') is not True
                or record.get('selfcheck') is not True):
            raise ValueError('incomplete pipeline/trace proof: ' + rid)
        retail = record.get('maspsx_retail') or {}
        data_only = record.get('funcs') == record.get('words') == retail.get('checked') == 0
        if (retail.get('diff') != 0 or not isinstance(retail.get('checked'), int)
                or (not data_only and not 0 < retail['checked'] <= record.get('funcs', 0))):
            raise ValueError('incomplete unmasked retail comparator: ' + rid)
        if set(record.get('genuine', {})) != set(report.VERSIONS):
            raise ValueError('incomplete six-version measurement: ' + rid)
        if set(record.get('exact_versions', [])) != {
                v for v, g in record['genuine'].items() if g.get('exact') is True}:
            raise ValueError('genuine equality summary differs from records: ' + rid)
        # This checks plural-unit common-version accounting, not a fabricated
        # whole-row attribution from an individual owner's ablation.
        report.ownerwise_exact(record)
    return by


def load_run(directory, *, fresh=False):
    receipt = json.loads((directory/'receipt.json').read_text())
    inputs = json.loads((directory/'inputs.json').read_text())
    records = read_lines(directory/'journal.jsonl')
    if (receipt.get('journal_sha256') != sha(directory/'journal.jsonl')
            or receipt.get('inputs_sha256') != sha(directory/'inputs.json')
            or receipt.get('rows') != len(records)
            or receipt.get('whole_registry') is not True
            or receipt.get('unchanged_inputs') is not True):
        raise ValueError('census receipt/hash/coverage mismatch')
    registry = unique(read_lines(ROOT/'ledger/rows.jsonl'), 'id')
    by = validate_records(records, registry)
    if fresh:
        validate_fresh(inputs, by, registry)
    return inputs, by


def validate_fresh(inputs, by, registry):
    # Reject a reconciled private journal before interpreting its keys as live.
    if inputs.get('fixture') != str(ROOT.resolve()):
        raise ValueError('fresh production-root census required; private keys cannot be imported')
    if (ROOT/'build_slus/build/slus_006.14').read_bytes() != (ROOT/'baserom/slus_006.14').read_bytes():
        raise ValueError('production SLUS image differs from retail')
    if (inputs.get('whole_registry') is not True or inputs.get('rows') != len(registry)
            or inputs.get('registry_sha256') != sha(ROOT/'ledger/rows.jsonl')
            or inputs.get('runner_sha256') != sha(HERE/'census_runner.py')):
        raise ValueError('production registry/runner provenance differs')
    from fidelity import aspsx_diff as A
    import common
    if A.ROOT != ROOT or common.ROOT != ROOT:
        raise ValueError('validation imported a different repository')
    fp = A.tool_fingerprint()
    if inputs.get('tool_fingerprint') != fp or inputs.get('versions') != A.VERSIONS:
        raise ValueError('production tool fingerprint or genuine-version set changed')
    expected_pair = {base+'/'+name: sha(ROOT/base/name)
                     for base in ['tools/maspsx', 'toolchain/maspsx']
                     for name in ['maspsx.py', 'maspsx/__init__.py']}
    if inputs.get('assembler') != expected_pair:
        raise ValueError('production assembler binding changed')
    if set(inputs.get('source_sha256', {})) != set(registry):
        raise ValueError('incomplete production source bindings')
    linked = None
    for rid, row in registry.items():
        source = common.clean_path(row)
        if inputs['source_sha256'][rid] != sha(source):
            raise ValueError('production source changed: ' + rid)
        text = source.read_text(errors='replace')
        if by[rid].get('key') != A.row_key(row, text, fp, row['cfg'], row.get('row_asflags') or ''):
            raise ValueError('stale production measurement key: ' + rid)
        record = by[rid]
        if record['maspsx_retail']['checked'] != record['funcs']:
            # Ordinary gcc inline helpers can have an emitted function section
            # in the .o but no symbol in the linked retail image. Do not turn
            # that into a claim that the helper was directly retail-compared.
            if row['kind'] != 'slus' or record.get('physical_units'):
                raise ValueError('unreviewed partial retail scope: ' + rid)
            if linked is None:
                linked = A.read_elf((ROOT/'build_slus/build/slus_006.14.elf').read_bytes())
            obj = ROOT/'build_slus/build/src'/f'{Path(row["c_path"]).stem}.o'
            functions = A.functions(A.read_elf(obj.read_bytes()))
            mapped = set(functions) & set(linked.symbols)
            if len(functions) != record['funcs'] or len(mapped) != record['maspsx_retail']['checked']:
                raise ValueError('object/link scope does not explain retail comparator count: ' + rid)
    if A.tool_fingerprint() != fp:
        raise ValueError('production proof inputs changed during validation')


def project(by, old, source):
    dependent = {rid: r for rid, r in by.items() if not r.get('exact_versions')}
    if dependent.keys() - old.keys():
        raise ValueError('new dependent identities require attribution review: '
                         + ', '.join(sorted(dependent.keys()-old.keys())))
    projected = []
    for rid, record in sorted(dependent.items()):
        item = dict(old[rid])
        units = report.physical_units(record)
        if units:
            details = []
            for unit in report.dependent_units(record):
                cause, fixes = report.unit_cause(unit)
                details.append({'source': report.unit_source(unit), 'role': unit.get('role'),
                                'module': unit.get('module'), 'cause': cause,
                                'closest_version': unit.get('best'), 'ablations': fixes,
                                'functions': unit.get('functions'), 'fired': unit.get('fired')})
            item['cause'] = 'owner-specific: ' + '; '.join(sorted({u['cause'] for u in details}))
            item['attribution_scope'] = 'physical-unit'
            item['dependent_physical_units'] = details
            item['classification_note'] = ('Existing ladder blocks retained. Owner-only ablations do not '
                                           'establish whole-row or minimal per-pass source attribution.')
        else:
            item['cause'] = report.cause(record)[0]
            if item['cause'] != old[rid]['cause']:
                raise ValueError('changed single-stream cause requires review: ' + rid)
        item['source'] = source
        # Do not manufacture new L4 or L5 claims from the new partition representation.
        if item['kinds'] != old[rid]['kinds']:
            raise ValueError('unreviewed ladder classification change: ' + rid)
        projected.append(item)
    return projected, sorted(old.keys()-dependent.keys())


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--run', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--fresh-production', action='store_true')
    parser.add_argument('--source', required=True, help='durable evidence path for proposed ledger records')
    args = parser.parse_args()
    out = args.output.resolve()
    if not out.is_relative_to(HERE) or out == HERE:
        raise ValueError('output must be a fresh private directory under this lane')
    if out.exists():
        raise ValueError('refusing to overwrite proposal/evidence')
    old_path = ROOT/'ledger/maspsx_dependence.jsonl'
    old_bytes = old_path.read_bytes()
    inputs, by = load_run(args.run.resolve(), fresh=args.fresh_production)
    old = unique(read_lines(old_path), 'id')
    proposed, removed = project(by, old, args.source)
    out.mkdir()
    (out/'.ignore').write_text('*\n')
    (out/'maspsx_dependence.proposed.jsonl').write_text(''.join(json.dumps(r)+'\n' for r in proposed))
    assert old_path.read_bytes() == old_bytes
    result = {'status': 'FRESH_PRODUCTION_VALIDATED' if args.fresh_production else 'PRIVATE_PROJECTION_ONLY',
              'run_receipt_sha256': sha(args.run/'receipt.json'),
              'previous_ledger_sha256': hashlib.sha256(old_bytes).hexdigest(),
              'proposed_ledger_sha256': sha(out/'maspsx_dependence.proposed.jsonl'),
              'registered_rows': len(by), 'previous_dependencies': len(old),
              'proposed_dependencies': len(proposed), 'removed': removed, 'added': [],
              'retained_ladder_classifications_unchanged': True,
              'maspsx_retail_masked_words': sum(r['maspsx_retail']['masked'] for r in by.values()),
              'retail_scope_counts_differ': [{'row': r['row'], 'object_functions': r['funcs'],
                                               'retail_checked': r['maspsx_retail']['checked']}
                                              for r in by.values()
                                              if r['funcs'] != r['maspsx_retail']['checked']],
              'data_only_rows_without_instruction_comparison': [r['row'] for r in by.values()
                                                                 if r['funcs'] == r['words'] == 0],
              'production_written': False}
    (out/'receipt.json').write_text(json.dumps(result, indent=2)+'\n')
    print(json.dumps(result, indent=2))


if __name__ == '__main__':
    main()
