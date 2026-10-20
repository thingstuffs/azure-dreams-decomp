#!/usr/bin/env python3
"""Portable records of validated overlay proofs; never placement authority.

Export requires all private artifacts and the existing full validator. Reading
needs only the summary, certificate and inputs used by the canonical fingerprint.
Missing compiler/retail inputs remain explicitly unchecked. No reader here grants
placement or changes the existing certificate validity/counts.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
SCHEMA = 'azure-overlay-certificate-summary.v1'
LIMIT = 50_000
KEY = re.compile(r'[A-Za-z0-9_]+')
SHA = re.compile(r'[0-9a-f]{64}')
FIELDS = {'schema', 'module', 'certificate_sha256', 'at', 'reviewer', 'members',
          'fingerprint', 'private_proof', 'module_result', 'windows'}


def encoded(value):
    return json.dumps(value, sort_keys=True, separators=(',', ':')).encode()


def sha_file(path):
    h = hashlib.sha256()
    with Path(path).open('rb') as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b''):
            h.update(block)
    return h.hexdigest()


def safe_path(root, name):
    rel = Path(name)
    if not rel.parts or rel.is_absolute() or '..' in rel.parts:
        raise ValueError('unsafe relative path')
    root = Path(root).resolve()
    path = root / rel
    for part in [path, *path.parents]:
        if part == root:
            break
        if part.is_symlink():
            raise ValueError('linked summary or proof path')
    if not path.resolve().is_relative_to(root):
        raise ValueError('path escapes root')
    return path


def paths(root, key):
    if not isinstance(key, str) or not KEY.fullmatch(key):
        raise ValueError('invalid overlay module key')
    return (safe_path(root, 'ledger/modules/overlay_' + key + '.json'),
            safe_path(root, 'ledger/certificate_summaries/overlay_' + key + '.json'))


def load_certificate(root, key):
    path, _ = paths(root, key)
    raw = path.read_bytes()
    cert = json.loads(raw)
    if (cert.get('module') != key or cert.get('kind') != 'overlay_module_placement'
            or not cert.get('reviewer') or not cert.get('at')
            or not isinstance(cert.get('members'), list)
            or not isinstance(cert.get('fingerprint'), dict)
            or not isinstance(cert.get('windows'), list)):
        raise ValueError('invalid overlay certificate identity')
    return cert, hashlib.sha256(raw).hexdigest()


def authorities(root, key):
    # Import lazily: listing absent summaries works without build prerequisites.
    from overlay_module_evidence import certificate_reason
    # The full validator imports the flat gate module. Reuse that exact module
    # so its process-local fingerprint observations can also serve this reader.
    import overlay_module_gate as gate
    module = next(m for m in gate.load_modules(root) if m['key'] == key)
    return module, gate, certificate_reason


def window_scopes(cert):
    result = []
    for window in cert['windows']:
        if (window.get('result') != 'MATCH'
                or not isinstance(window.get('file_start'), int)
                or not isinstance(window.get('file_end'), int)
                or window['file_end'] <= window['file_start']
                or not SHA.fullmatch(window.get('digest', ''))):
            raise ValueError('invalid successful window scope')
        result.append({k: window[k] for k in
                       ('config', 'result', 'file_start', 'file_end', 'digest')})
    if not result or len({w['config'] for w in result}) != len(result):
        raise ValueError('missing or duplicate window scope')
    return result


def proof_inventory(root, cert):
    """Hash every retained private file; only aggregate hashes are published."""
    inventory = {}
    for name in [cert['proof_dir'], *(w['proof_dir'] for w in cert['windows'])]:
        directory = safe_path(root, name)
        if not directory.is_dir():
            raise FileNotFoundError('private proof directory is missing')
        for path in sorted(directory.rglob('*')):
            rel = path.relative_to(Path(root).resolve()).as_posix()
            safe_path(root, rel)
            if path.is_file():
                inventory[rel] = {'sha256': sha_file(path), 'bytes': path.stat().st_size}
            elif not path.is_dir():
                raise ValueError('non-regular private proof artifact')
    if not inventory:
        raise ValueError('empty private proof inventory')
    return {'algorithm': 'sha256-canonical-inventory-v1',
            'sha256': hashlib.sha256(encoded(inventory)).hexdigest(),
            'files': len(inventory), 'bytes': sum(v['bytes'] for v in inventory.values())}


def validate_summary(doc, cert, certificate_sha, key):
    if not isinstance(doc, dict) or set(doc) != FIELDS or doc['schema'] != SCHEMA:
        raise ValueError('invalid summary schema')
    for field in ('at', 'reviewer', 'members', 'fingerprint'):
        if doc[field] != cert[field]:
            raise ValueError('summary certificate fields differ')
    if doc['module'] != key or doc['certificate_sha256'] != certificate_sha:
        raise ValueError('summary certificate binding differs')
    if doc['windows'] != window_scopes(cert):
        raise ValueError('summary window scopes differ')
    if doc['module_result'] != {'retail': 'MATCH', 'genuine_aspsx_2_79': 'MATCH', 'masked': 0}:
        raise ValueError('incomplete summary result')
    proof = doc['private_proof']
    if (not isinstance(proof, dict) or set(proof) != {'algorithm', 'sha256', 'files', 'bytes'}
            or proof['algorithm'] != 'sha256-canonical-inventory-v1'
            or not isinstance(proof['sha256'], str) or not SHA.fullmatch(proof['sha256'])
            or type(proof['files']) is not int or proof['files'] <= 0
            or type(proof['bytes']) is not int or proof['bytes'] <= 0):
        raise ValueError('invalid private proof digest')


def export_summary(root, key):
    """Publish only after the original full-proof validator succeeds."""
    root = Path(root).resolve()
    cert, certificate_sha = load_certificate(root, key)
    before = proof_inventory(root, cert)
    module, gate, certificate_reason = authorities(root, key)
    reason = certificate_reason(module, cert, root)
    if reason is not None:
        raise ValueError('full proof is not current: ' + reason)
    if (load_certificate(root, key) != (cert, certificate_sha)
            or proof_inventory(root, cert) != before
            or gate.fingerprint(module, root) != cert['fingerprint']):
        raise ValueError('certificate, inputs or private proof changed during export')
    doc = {'schema': SCHEMA, 'module': key, 'certificate_sha256': certificate_sha,
           **{k: cert[k] for k in ('at', 'reviewer', 'members', 'fingerprint')},
           'private_proof': before,
           'module_result': {'retail': 'MATCH', 'genuine_aspsx_2_79': 'MATCH', 'masked': 0},
           'windows': window_scopes(cert)}
    validate_summary(doc, cert, certificate_sha, key)
    raw = encoded(doc) + b'\n'
    if len(raw) >= LIMIT:
        raise ValueError('summary exceeds 50 KB bound')
    _, output = paths(root, key)
    output.parent.mkdir(parents=True, exist_ok=True)
    fd, temporary = tempfile.mkstemp(prefix=output.name + '.', dir=output.parent)
    try:
        with os.fdopen(fd, 'wb') as stream:
            stream.write(raw)
        os.replace(temporary, output)
    finally:
        if Path(temporary).exists():
            Path(temporary).unlink()
    return output


def summary_status(root, key):
    """A recorded/input state only. Never return a placement `valid` field."""
    state = {'module': key, 'recorded': 'absent', 'inputs': 'unavailable', 'replayed_here': False}
    try:
        _, path = paths(root, key)
        if not path.exists():
            return state
        if path.stat().st_size >= LIMIT:
            raise ValueError('oversize summary')
        doc = json.loads(path.read_text())
        cert, certificate_sha = load_certificate(root, key)
        validate_summary(doc, cert, certificate_sha, key)
    except (OSError, ValueError, TypeError, KeyError, AttributeError):
        return dict(state, recorded='invalid')
    state['recorded'] = 'bound'
    try:
        module, gate, _ = authorities(root, key)
        current = gate.fingerprint(module, root)
    except (OSError, subprocess.SubprocessError):
        return state
    except (ValueError, TypeError, KeyError, StopIteration, AttributeError):
        return dict(state, inputs='changed')
    return dict(state, inputs='current' if current == doc['fingerprint'] else 'changed')


def recorded_statuses(root=ROOT):
    return [summary_status(root, path.stem[len('overlay_'):]) for path in
            sorted((Path(root) / 'ledger/modules').glob('overlay_*.json'))]


def status_text(root=ROOT):
    if not (Path(root) / 'ledger/certificate_summaries').exists():
        return ''
    states = recorded_statuses(root)
    bound = [s for s in states if s['recorded'] == 'bound']
    current = sum(s['inputs'] == 'current' for s in bound)
    changed = sum(s['inputs'] == 'changed' for s in bound)
    unavailable = len(bound) - current - changed
    return (f'Portable overlay proof summaries: {len(bound)} bound to their certificates; '
            f'{current} inputs current, {changed} inputs changed, {unavailable} inputs not checked here; '
            f'{sum(s["recorded"] == "invalid" for s in states)} invalid, '
            f'{sum(s["recorded"] == "absent" for s in states)} absent. '
            'Full private proofs are not replayed by this summary check; '
            'these records do not change certificate placement or L4/L5 counts.')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=ROOT)
    commands = parser.add_subparsers(dest='command', required=True)
    export = commands.add_parser('export')
    export.add_argument('module')
    commands.add_parser('status')
    args = parser.parse_args()
    if args.command == 'status':
        print(json.dumps(recorded_statuses(args.root), indent=2))
        return 0
    try:
        output = export_summary(args.root, args.module)
    except (OSError, ValueError, TypeError, KeyError, StopIteration, subprocess.SubprocessError) as exc:
        print('summary export refused: ' + str(exc).replace(str(args.root.resolve()), '<root>'), file=sys.stderr)
        return 1
    print(output.relative_to(args.root.resolve()).as_posix())
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
