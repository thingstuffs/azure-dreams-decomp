#!/usr/bin/env python3
"""Guarded source-only native package. Production proof belongs to land_packages."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import sys

P = Path(__file__).resolve().parent
CANONICAL = next((p for p in P.parents if (p/'tools/lanes/land_packages.py').is_file()
                  and (p/'ledger/rows.jsonl').is_file()), None)


def local(root, name):
    rel = Path(name)
    if rel.is_absolute() or '..' in rel.parts or not name:
        raise ValueError('unsafe path: ' + str(name))
    dest = root/rel
    if dest.is_symlink() or not dest.parent.resolve().is_relative_to(root):
        raise ValueError('mutable path escapes root: ' + str(name))
    return dest


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest() if path.is_file() else None


def apply(root, dry_run=False, live=False):
    root = root.resolve()
    live_root = Path(os.environ['LAND_LIVE_ROOT']).resolve() if os.environ.get('LAND_LIVE_ROOT') else CANONICAL
    if not live and (root == live_root or live_root is None and (root/'.git').exists()):
        raise ValueError('Refusing canonical live checkout without --live; use an isolated root.')
    inventory = json.loads((P/'package.sha256.json').read_text())
    for name, expected in inventory.items():
        if sha(local(P, name)) != expected:
            raise ValueError('package integrity drift: ' + name)
    manifest = json.loads((P/'manifest.json').read_text())
    for name, expected in manifest['protected_inputs'].items():
        if sha(local(root, name)) != expected:
            raise ValueError('protected input guard drift: ' + name)
    files = []
    for rec in json.loads((P/'files.json').read_text()):
        if not rec['path'].startswith('src/') or not rec['path'].endswith('.c'):
            raise ValueError('native package is source-only')
        src, dest = local(P, rec['file']), local(root, rec['path'])
        if sha(src) != rec['after']:
            raise ValueError('packaged source hash drift: ' + rec['path'])
        current = sha(dest)
        if current == rec['after']:
            continue
        if current != rec['before']:
            raise ValueError('source guard drift: ' + rec['path'])
        files.append((src, dest))
    # All files/guards are checked before the first write. A mixed before/after
    # state must be regenerated, rather than accepting an unmeasured combination.
    if files:
        if len(files) != len(json.loads((P/'files.json').read_text())):
            raise ValueError('partially applied native batch; regenerate and re-prove')
        sys.path[:0] = [str(root/'tools'), str(root/'tools/gate')]
        from gate import overlay_module_gate as G
        modules = {m['key']:m for m in G.load_modules(root)}
        for key, expected in manifest['module_fingerprints'].items():
            if G.fingerprint(modules[key], root, windows=False)['sha256'] != expected:
                raise ValueError('native module context drift: ' + key)
    print(json.dumps(dict(dry_run=dry_run, files=[str(p.relative_to(root)) for _,p in files],
                          reviewer='pending', proofs_required=manifest['certificates_requiring_renewal'])), flush=True)
    if not dry_run:
        for src, dest in files:
            shutil.copy2(src, dest)
        # The helper has always been source-only. Register its production proof
        # requirements explicitly when a complete landing transaction calls it.
        if files and os.environ.get('LAND_SKIP_PACKAGE_PROOF') == '1' and os.environ.get('LAND_PACKAGE_PROOF_CONTEXT'):
            sys.path.insert(0, str(root/'tools/lanes'))
            from package_proofs import defer_proof
            lane_receipts = [name for name in ('manifest.json','scores.json') if (P/name).is_file()]
            for key in manifest['certificates_requiring_renewal']:
                defer_proof(root, P, 'overlay-module', key, lane_receipts)
            for config in manifest.get('production_windows', []):
                defer_proof(root, P, 'overlay-window', config, lane_receipts)
        print('APPLIED source-only; review, production gates and renewal remain required.', flush=True)


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--root', required=True, type=Path)
    ap.add_argument('--dry-run', action='store_true')
    ap.add_argument('--live', action='store_true')
    args = ap.parse_args()
    apply(args.root, args.dry_run, args.live)


if __name__ == '__main__':
    main()
