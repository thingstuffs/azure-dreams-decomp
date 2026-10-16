#!/usr/bin/env python3
"""Standalone, hash-guarded package applier. Dry-run always wins over live."""
from __future__ import annotations
import argparse
import hashlib
import json
import os
from pathlib import Path
import tempfile


def digest(data):
    return hashlib.sha256(data).hexdigest()


def safe_path(root, rel):
    p = Path(rel)
    if p.is_absolute() or not p.parts or '..' in p.parts: raise ValueError('unsafe path: '+rel)
    path = root/p
    if path.is_symlink(): raise ValueError('symlink target: '+rel)
    if not path.resolve().is_relative_to(root.resolve()): raise ValueError('path escapes root: '+rel)
    return path


def apply(package, root, live=False, dry_run=False):
    package, root = Path(package).resolve(), Path(root).resolve()
    manifest = json.loads((package/'manifest.json').read_text())
    if manifest.get('schema') != 'typefold-package-v1': raise ValueError('unsupported package schema')
    entries = manifest['files']; seen = set(); staged = []
    for e in entries:
        rel = e['path']
        if rel in seen: raise ValueError('duplicate destination: '+rel)
        seen.add(rel); target = safe_path(root, rel)
        before = target.read_bytes() if target.exists() else None
        current = digest(before) if before is not None else None
        payload = safe_path(package, e['payload']).read_bytes()
        if digest(payload) != e['after_sha256']: raise ValueError('payload hash mismatch: '+rel)
        if current not in (e['before_sha256'], e['after_sha256']): raise ValueError('before hash mismatch: '+rel)
        staged.append((target, before, payload, current != e['after_sha256']))
    for e in manifest.get('guards', []):
        target = safe_path(root, e['path'])
        actual = digest(target.read_bytes()) if target.exists() else None
        if actual != e['sha256']: raise ValueError('dependency hash mismatch: '+e['path'])
    changed = sum(ch for _,_,_,ch in staged)
    mode = 'dry-run' if dry_run or not live else 'live'
    if mode == 'live':
        written = []
        try:
            for target, before, payload, change in staged:
                if not change: continue
                target.parent.mkdir(parents=True, exist_ok=True)
                # Recheck immediately before replacement (preflight cannot eliminate races).
                current = target.read_bytes() if target.exists() else None
                if current != before: raise ValueError('destination changed after preflight: '+str(target))
                write_atomic(target, payload)
                written.append((target, before))
        except BaseException:
            for target, before in reversed(written):
                if before is None: target.unlink()
                else: write_atomic(target, before)
            raise
    return {'mode':mode, 'changed':changed, 'files':len(entries), 'guards':len(manifest.get('guards', []))}


def write_atomic(target, data):
    fd, temp = tempfile.mkstemp(prefix='.typefold-', dir=target.parent)
    try:
        with os.fdopen(fd, 'wb') as f: f.write(data)
        if target.exists(): os.chmod(temp, target.stat().st_mode & 0o777)
        else: os.chmod(temp, 0o644)
        os.replace(temp, target)
    finally:
        if os.path.exists(temp): os.unlink(temp)


def main(argv=None):
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--root', required=True, type=Path)
    p.add_argument('--live', action='store_true')
    p.add_argument('--dry-run', action='store_true')
    args = p.parse_args(argv)
    try: result = apply(Path(__file__).resolve().parent, args.root, args.live, args.dry_run)
    except (ValueError, OSError, KeyError) as e: p.exit(1, str(e)+'\n')
    print(json.dumps(result, sort_keys=True))

if __name__ == '__main__': main()
