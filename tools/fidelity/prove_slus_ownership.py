#!/usr/bin/env python3
"""Prove declared SLUS data ownership without granting module-cleanup placement.

The complete image, object section bytes, symbol offsets/VMAs and every member's
unmasked genuine-ASPSX comparison must agree. This receipt does not certify L4.
Run under the shared landing lock when recording authoritative evidence.
"""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import time

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
from common import rows
from slus_module_context import modules, fingerprint
from slus_module_evidence import digest, verifier_fingerprint
from fidelity.slus_iso import SlusView
from fidelity import aspsx_diff as A


def symbols(path):
    result = subprocess.check_output(['mipsel-linux-gnu-nm', '-n', '--defined-only', str(path)], text=True)
    return {parts[2]: {'address': int(parts[0], 16), 'kind': parts[1]}
            for line in result.splitlines() if len(parts := line.split()) == 3}


def prove(names):
    declared = {m['name']: m for m in modules()}
    selected = [declared[name] for name in names]
    by_id = {r['id']: r for r in rows()}
    ids = [member['id'] for module in selected for member in module['members']]
    initial = {rid: fingerprint(by_id[rid]) for rid in ids}
    tool_fp = verifier_fingerprint()
    data = {}
    with tempfile.TemporaryDirectory(prefix='slus_ownership_') as temp:
        view = SlusView(Path(temp) / 'build')
        gate = view.calibrate()
        if gate['result'] != 'MATCH':
            raise ValueError('full retail gate failed: ' + str(gate))
        recipe = (view.dest / 'build.ninja').read_bytes()
        if recipe != (ROOT / 'ledger/splits/slus.build.ninja').read_bytes():
            raise ValueError('generated recipe differs from the pinned build')
        image = (view.dest / 'build/slus_006.14').read_bytes()
        linked = symbols(view.dest / 'build/slus_006.14.elf')
        for module in selected:
            records = module['data']
            if not records:
                raise ValueError('module has no owned data: ' + module['name'])
            obj = view.dest / 'build' / Path(module['source']).with_suffix('.o')
            own = symbols(obj)
            section = Path(temp) / 'section.bin'
            subprocess.run(['mipsel-linux-gnu-objcopy', '-O', 'binary', '-j', '.sdata', str(obj), str(section)], check=True)
            actual = section.read_bytes()
            expected = b''.join(bytes.fromhex(d['bytes']) for d in records)
            if actual != expected:
                raise ValueError('object .sdata bytes or size differ: ' + module['name'])
            offset = 0
            proofs = []
            for datum in records:
                name = datum['symbol']
                if name not in own or own[name]['kind'].upper() == 'A' or own[name]['address'] != offset:
                    raise ValueError('object ownership/offset differs: ' + name)
                if name not in linked or linked[name]['kind'].upper() == 'A' or linked[name]['address'] != datum['vram']:
                    raise ValueError('linked ownership/address differs: ' + name)
                foff = int(Path(datum['asset']).stem, 16) + datum['offset']
                if image[foff:foff + datum['size']] != bytes.fromhex(datum['bytes']):
                    raise ValueError('linked data bytes differ: ' + name)
                proofs.append(dict(datum, object_offset=offset, linked_kind=linked[name]['kind']))
                offset += datum['size']
            data[module['name']] = {'section': '.sdata', 'size': len(actual), 'bytes': actual.hex(), 'symbols': proofs}
    old_versions = A.VERSIONS
    A.VERSIONS = ['2.79']
    try:
        results = {}
        for module in selected:
            for member in module['members']:
                rid = member['id']
                record = A.process_row(by_id[rid])
                genuine = record.get('genuine', {}).get('2.79', {})
                expected = {'diff': 0, 'masked': 0, 'checked': len(member['functions'])}
                if (record.get('status') != 'ok' or record.get('maspsx_exact') is not True
                        or record.get('selfcheck') is not True or genuine.get('exact') is not True
                        or genuine.get('retail') != [0, 0] or record.get('maspsx_retail') != expected
                        or record.get('module_fingerprint') != initial[rid]):
                    raise ValueError('member proof failed: ' + json.dumps(record))
                results[rid] = record
                print(rid + ': genuine and retail exact', flush=True)
    finally:
        A.VERSIONS = old_versions
    if verifier_fingerprint() != tool_fp or any(fingerprint(by_id[rid]) != initial[rid] for rid in ids):
        raise ValueError('verification inputs changed while proving ownership')
    return {'schema': 1, 'at': time.strftime('%Y-%m-%dT%H:%M:%SZ', time.gmtime()),
            'purpose': 'data ownership only; no L4/L5 placement certificate',
            'modules': names, 'module_fingerprints': initial, 'tool_fingerprint': tool_fp,
            'recipe_sha256': hashlib.sha256(recipe).hexdigest(),
            'image_sha1': hashlib.sha1(image).hexdigest(), 'gate': gate, 'data': data, 'rows': results}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('modules', nargs='+')
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    receipt = prove(args.modules)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    pending = args.output.with_suffix('.tmp')
    pending.write_text(json.dumps(receipt, indent=2) + '\n')
    pending.replace(args.output)
    print(json.dumps({'modules': len(receipt['modules']), 'rows': len(receipt['rows']),
                      'gate': receipt['gate'], 'image_sha1': receipt['image_sha1']}))


if __name__ == '__main__':
    main()
