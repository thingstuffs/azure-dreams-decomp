#!/usr/bin/env python3
"""Compare two compilations of a moved TU, including canonical object bytes.

GCC emits source filenames in `.file` directives. A leaf rename changes that
nonallocated ELF metadata even when every instruction and relocation is equal.
This proof removes only `.file` directives from both postprocessed assembly
streams, requires all remaining bytes equal, and assembles both streams with
the same maspsx invocation before comparing complete object bytes.
"""
from __future__ import annotations
import argparse
import hashlib
import os
from pathlib import Path
import re
import subprocess
import sys
import tempfile

from source_layout import ROOT

FILE_DIRECTIVE = re.compile(rb'(?m)^[ \t]*\.file(?:[ \t]+[^\n]*)?\n')


def digest(data):
    return hashlib.sha256(data).hexdigest()


def canonical(data):
    return FILE_DIRECTIVE.sub(b'', data)


def reassemble(root, data, directory, container):
    out = directory / 'canonical.o'
    env = dict(os.environ)
    for key in ('AZURE_MASPSX', 'AZURE_MASPSX_COMPANION', 'MASPSX_NORETURN_FILE',
                'MASPSX_SIBCALL_FILE'):
        env.pop(key, None)
    suffix = '.' + container if container != 'main' else ''
    bank = directory / 'noreturn_syms.bank.txt'
    env['MASPSX_NORETURN_FILE'] = str(bank if bank.is_file() else root / 'config' / ('noreturn_syms' + suffix + '.txt'))
    env['MASPSX_SIBCALL_FILE'] = str(root / 'config' / ('sibcall_syms' + suffix + '.txt'))
    command = [root / '.venv/bin/python', root / 'toolchain/maspsx/maspsx.py',
               '--aspsx-version=2.79', '--dont-force-G0', '--run-assembler',
               '--gnu-as-path=mipsel-linux-gnu-as', '-I' + str(root),
               '-I' + str(root / 'include'), '-EL', '-march=r3000', '-G8',
               '-o', out]
    result = subprocess.run(list(map(str, command)), input=data, capture_output=True, env=env, cwd=root)
    if result.returncode:
        raise ValueError('canonical assembly failed: ' + result.stderr.decode(errors='replace')[-500:])
    return digest(out.read_bytes())


def compare(root, name, before, after, container):
    root = Path(root).resolve()
    before, after = Path(before).resolve(), Path(after).resolve()
    raw_a, raw_b = ((p / 'module.o').read_bytes() for p in (before, after))
    asm_a, asm_b = ((p / 'sectioned.s').read_bytes() for p in (before, after))
    canon_a, canon_b = canonical(asm_a), canonical(asm_b)
    if canon_a != canon_b:
        raise ValueError(name + ': compiler streams differ beyond .file metadata')
    with tempfile.TemporaryDirectory(prefix='identity-', dir=root / 'build_ovl') as td:
        workspace = Path(td)
        for label, origin in (('pre', before), ('post', after)):
            directory = workspace / label
            directory.mkdir()
            evidence = origin / 'noreturn_syms.bank.txt'
            if evidence.is_file():
                (directory / evidence.name).write_bytes(evidence.read_bytes())
        object_a = reassemble(root, canon_a, workspace / 'pre', container)
        object_b = reassemble(root, canon_b, workspace / 'post', container)
    if object_a != object_b:
        raise ValueError(name + ': canonical objects differ')
    return {'tu': name, 'raw_before': digest(raw_a), 'raw_after': digest(raw_b),
            'raw_equal': raw_a == raw_b, 'canonical_object_before': object_a,
            'canonical_object_after': object_b, 'canonical_equal': True,
            'assembly_without_file_sha256': digest(canon_a)}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('name')
    ap.add_argument('before', type=Path)
    ap.add_argument('after', type=Path)
    ap.add_argument('--container', required=True, choices=('main', 'town', 'dungeon', 'ovmovie'))
    ap.add_argument('--root', type=Path, default=ROOT)
    args = ap.parse_args()
    record = compare(args.root, args.name, args.before, args.after, args.container)
    print('\t'.join(str(record[k]) for k in ('tu', 'raw_before', 'raw_after', 'raw_equal',
                                           'canonical_object_before', 'canonical_object_after',
                                           'canonical_equal', 'assembly_without_file_sha256')))


if __name__ == '__main__':
    main()
