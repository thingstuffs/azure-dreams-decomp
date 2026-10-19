#!/usr/bin/env python3
"""Capture/compare every physical TU in a layout map at its registered recipe.

Run --snapshot FILE on the B17 source tree, apply the reviewed layout transaction,
then run --compare FILE.  Objects stay in a temporary build directory; the JSONL
receipt records only hashes and relative paths.  Non-home native members are
refused so that one physical TU is never silently proved as two row compiles.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile

from layout_apply import path, rows
from layout_identity import canonical, digest, reassemble
from source_layout import ROOT, registry, row_relative, slus_source


def maps(table):
    data = rows(table)
    if not data:
        raise ValueError('empty tree')
    first = data[0]
    if {'current_path', 'proposed_path'} <= first.keys():
        old_key, new_key = 'current_path', 'proposed_path'
    elif {'source_tu', 'proposed_tu'} <= first.keys():
        old_key, new_key = 'source_tu', 'proposed_tu'
    else:
        raise ValueError('tree needs current_path/proposed_path or source_tu/proposed_tu')
    result = {}
    for row in data:
        old, new = row.get(old_key, ''), row.get(new_key, '')
        if not old or not new or old == new:
            continue
        path(old, 'src'); path(new, 'src')
        if old in result and result[old] != new:
            raise ValueError('conflicting source path: ' + old)
        result[old] = new
    if not result:
        raise ValueError('tree has no moves')
    return result


def recipes(root):
    root = Path(root).resolve()
    from gate import overlay_module_gate as G
    from slus_module_context import modules as slus_modules
    reg = registry(root)
    physical = {}
    member_paths = set()
    for module in G.load_modules(root):
        cell, flags = G.module_recipe(module)
        physical[module['source']] = {'kind': 'overlay_module', 'container': module['container'],
                                      'cell': cell, 'flags': list(flags), 'asflags': []}
        member_paths.update(x['source'] for x in G.all_members(module))
    for module in slus_modules(root):
        if not module['members']:
            continue
        source = slus_source(module['source'], root).relative_to(root).as_posix()
        row = reg[module['members'][0]['id']]
        physical[source] = {'kind': 'slus_module', 'container': 'slus', 'cell': row['cell'],
                            'flags': row['flags'].split(), 'asflags': (row.get('row_asflags') or '').split(),
                            'row_id': row['id']}
        member_paths.update(slus_source(x['source'], root).relative_to(root).as_posix()
                            for x in module['members'])
    for rid, row in reg.items():
        if row.get('source_row'):
            continue
        source = row_relative(row, root)
        if source in member_paths or source in physical:
            continue
        physical[source] = {'kind': 'row', 'container': row['container'], 'cell': row['cell'],
                            'flags': row['flags'].split(), 'asflags': (row.get('row_asflags') or '').split(),
                            'row_id': rid}
    return physical, member_paths


def command(args, *, cwd, data=None, env=None):
    result = subprocess.run(list(map(str, args)), cwd=cwd, input=data, capture_output=True, env=env)
    if result.returncode:
        raise ValueError('compile command failed: ' + result.stderr.decode(errors='replace')[-500:])
    return result.stdout


def capture_one(root, rel, recipe):
    root = Path(root).resolve()
    source = root / rel
    if not source.is_file():
        raise ValueError('missing physical TU: ' + rel)
    if b'__FILE__' in source.read_bytes() or b'__LINE__' in source.read_bytes():
        raise ValueError('path-sensitive C macro: ' + rel)
    (root / 'build_ovl').mkdir(exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='layout-compile-', dir=root / 'build_ovl') as td:
        workspace = Path(td)
        if recipe['container'] == 'slus':
            import verify
            row = registry(root)[recipe['row_id']]
            out, error = verify._compile_slus_source(row, source, workspace / 'raw', root / 'include', root)
            if error:
                raise ValueError(rel + ': ' + error)
            raw = out.read_bytes()
            stream = (out.parent / 'a.proc.s').read_bytes()
        else:
            cc = root / 'toolchain/compilers' / ('gcc-' + recipe['cell'])
            asm = workspace / 'source.s'
            flags = recipe['flags']
            if '-O2' not in flags:
                flags = ['-O2', *flags]
            command([cc / 'gcc', '-B' + str(cc) + '/', '-S', *flags,
                     '-I' + str(root / 'include'), '-w', source, '-o', asm], cwd=root)
            stream = command([sys.executable, root / 'tools/build/ccproc.py',
                              '--names-tsv', root / 'config/names.tsv'], cwd=root,
                             data=asm.read_bytes())
            raw_dir = workspace / 'raw'
            raw_dir.mkdir()
            # A stable family census is sufficient for before/after object
            # identity; the scoped gate remains responsible for retail MATCH.
            reassemble(root, stream, raw_dir, recipe['container'])
            raw = (raw_dir / 'canonical.o').read_bytes()
        canonical_stream = canonical(stream)
        clean_dir = workspace / 'normalized'
        clean_dir.mkdir()
        clean_sha = reassemble(root, canonical_stream, clean_dir,
                               recipe['container'] if recipe['container'] != 'slus' else 'main')
    return {'source': rel, 'kind': recipe['kind'], 'recipe': recipe,
            'raw_sha256': digest(raw), 'canonical_assembly_sha256': digest(canonical_stream),
            'canonical_object_sha256': clean_sha}


def run(root, table, *, snapshot=None, compare=None):
    root = Path(root).resolve()
    mapping = maps(table)
    physical, members = recipes(root)
    prior = {}
    if compare:
        for line in Path(compare).read_text().splitlines():
            record = json.loads(line)
            if record['old'] in prior:
                raise ValueError('duplicate snapshot TU: ' + record['old'])
            prior[record['old']] = record
        if set(prior) != set(mapping):
            raise ValueError('snapshot map differs')
    records = []
    for old, new in sorted(mapping.items()):
        rel = new if compare else old
        if not (root / rel).is_file():
            raise ValueError('expected ' + ('post-move' if compare else 'pre-move') + ' physical TU: ' + rel)
        if rel in members:
            raise ValueError('non-home native member in tree: ' + rel)
        recipe = physical.get(rel)
        if recipe is None:
            raise ValueError('no registered physical recipe: ' + rel)
        current = capture_one(root, rel, recipe)
        record = {'old': old, 'new': new, **current}
        if compare:
            before = prior[old]
            if before['new'] != new:
                raise ValueError('destination changed since snapshot: ' + old)
            if before['recipe'] != record['recipe']:
                raise ValueError('recipe changed: ' + old)
            record['raw_equal'] = before['raw_sha256'] == record['raw_sha256']
            record['canonical_assembly_equal'] = before['canonical_assembly_sha256'] == record['canonical_assembly_sha256']
            record['canonical_object_equal'] = before['canonical_object_sha256'] == record['canonical_object_sha256']
            if not record['canonical_assembly_equal'] or not record['canonical_object_equal']:
                raise ValueError('object changed beyond file metadata: ' + old)
        records.append(record)
    if snapshot:
        dest = Path(snapshot)
        if dest.exists():
            raise ValueError('snapshot already exists: ' + str(dest))
        dest.parent.mkdir(parents=True, exist_ok=True)
        dest.write_text(''.join(json.dumps(x, separators=(',', ':')) + '\n' for x in records))
    return {'physical_tus': len(records), 'canonical_equal': sum(x.get('canonical_object_equal', False) for x in records),
            'raw_equal': sum(x.get('raw_equal', False) for x in records),
            'receipt_sha256': digest(Path(snapshot).read_bytes()) if snapshot else None}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('tree', type=Path)
    ap.add_argument('--root', type=Path, default=ROOT)
    mode = ap.add_mutually_exclusive_group(required=True)
    mode.add_argument('--snapshot', type=Path)
    mode.add_argument('--compare', type=Path)
    args = ap.parse_args()
    print(json.dumps(run(args.root, args.tree, snapshot=args.snapshot, compare=args.compare), sort_keys=True))


if __name__ == '__main__':
    main()
