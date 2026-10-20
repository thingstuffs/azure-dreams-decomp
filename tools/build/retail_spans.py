"""Resolve checked retail spans from a user's extracted files or ISO9660 disc.

The committed form contains only a disc file id, offset, length and SHA-256.
Materialisation is explicit: gate fingerprints continue to hash committed JSON.
Directory ids end in '/' and denote ISO9660 directory data, not host paths.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import sys

FILES = {'SLUS_006.14': 'baserom/slus_006.14',
         'MAIN/MAIN.BIN': 'work/disc/containers/MAIN_MAIN.BIN',
         'TOWN/TOWN.BIN': 'work/disc/containers/TOWN_TOWN.BIN',
         'DUNGEON/DUNGEON.BIN': 'work/disc/containers/DUNGEON_DUNGEON.BIN',
         'OVMOVIE.BIN': 'work/disc/containers/OVMOVIE.BIN'}


def validate_span(span):
    if not isinstance(span, dict) or set(span) != {'file', 'offset', 'length', 'sha256'}:
        raise ValueError('retail span needs file, offset, length and sha256')
    name = span['file']
    if (not isinstance(name, str) or not re.fullmatch(r'[A-Z0-9_./-]+', name)
            or name.startswith('/') or any(p in ('', '.', '..') for p in name.rstrip('/').split('/'))):
        raise ValueError('unsafe retail disc file id')
    if (type(span['offset']) is not int or type(span['length']) is not int
            or span['offset'] < 0 or not 0 < span['length'] <= 16 * 1024 * 1024):
        raise ValueError('invalid retail span bounds')
    if not isinstance(span['sha256'], str) or not re.fullmatch('[0-9a-f]{64}', span['sha256']):
        raise ValueError('invalid retail span sha256')


class RetailReader:
    def __init__(self, root, disc=None):
        self.root = Path(root)
        self.disc_path = Path(disc or os.environ.get('AZURE_CLEAN_DISC') or
                              self.root / 'bin/Azure Dreams.bin')
        self.disc = None
        self.files = {}

    def close(self):
        for stream in self.files.values():
            stream.close()
        if self.disc is not None:
            self.disc.close()

    def __enter__(self):
        return self

    def __exit__(self, *args):
        self.close()

    def read(self, span):
        validate_span(span)
        name, offset, size = (span[k] for k in ('file', 'offset', 'length'))
        local = self.root / FILES[name] if name in FILES else None
        if local is not None and local.is_file():
            if name not in self.files:
                self.files[name] = local.open('rb')
            stream = self.files[name]
            stream.seek(offset)
            raw = stream.read(size)
        else:
            if self.disc is None:
                # Load tools/gate/disc_slice.py by path: putting tools/gate on sys.path would let its copies of
                # configure/source_layout shadow the tools/ modules for the rest of the process.
                import importlib.util
                spec = importlib.util.spec_from_file_location(
                    'disc_slice', Path(__file__).resolve().parents[1] / 'gate' / 'disc_slice.py')
                disc_slice = importlib.util.module_from_spec(spec)
                spec.loader.exec_module(disc_slice)
                self.disc = disc_slice.Disc(self.disc_path)
            if name.endswith('/'):
                extent = self.disc.root
                for part in name.rstrip('/').split('/'):
                    lba, length, directory = self.disc.directory(extent)[part]
                    if not directory:
                        raise ValueError('retail directory id names a file')
                    extent = (lba, length)
                if offset + size > extent[1]:
                    raise ValueError('retail span outside ISO directory')
                raw = self.disc.logical(extent[0], offset, size)
            else:
                raw = self.disc.slice(name, offset, size)
        if len(raw) != size or hashlib.sha256(raw).hexdigest() != span['sha256']:
            raise ValueError('retail span length/sha256 mismatch: ' + name)
        return raw

    def materialize(self, value):
        if isinstance(value, list):
            return [self.materialize(v) for v in value]
        if not isinstance(value, dict):
            return value
        if '$retail' not in value:
            return {k: self.materialize(v) for k, v in value.items()}
        if set(value) != {'$retail', 'format'}:
            raise ValueError('invalid retail marker keys')
        raw = self.read(value['$retail'])
        style = value['format']
        if style == 'hex':
            return raw.hex()
        if style == 'hex_upper':
            return raw.hex().upper()
        if isinstance(style, dict) and set(style) == {'kind', 'prefix', 'width', 'uppercase'}:
            if (style['kind'] != 'int_hex' or style['prefix'] not in ('0x', '0X', '')
                    or type(style['width']) is not int or not 1 <= style['width'] <= len(raw)*2
                    or type(style['uppercase']) is not bool):
                raise ValueError('invalid retail integer format')
            digits = format(int.from_bytes(raw, 'little'), '0' + str(style['width']) + ('X' if style['uppercase'] else 'x'))
            return style['prefix'] + digits
        if style == 'u8_list':
            return list(raw)
        if style == 'u32le':
            if len(raw) != 4:
                raise ValueError('retail scalar word must be four bytes')
            return int.from_bytes(raw, 'little')
        if style == 'u32le_list':
            if len(raw) % 4:
                raise ValueError('retail words must be aligned')
            return [int.from_bytes(raw[i:i+4], 'little') for i in range(0, len(raw), 4)]
        raise ValueError('unknown retail materialisation format')


def load_json(path, root=None):
    path = Path(path)
    doc = json.loads(path.read_text())
    if root is None:
        # Resolve config symlinks in build_slus views to the authority root.
        root = path.resolve().parent.parent
    with RetailReader(root) as reader:
        return reader.materialize(doc)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('path', type=Path)
    parser.add_argument('--root', type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(load_json(args.path, args.root), indent=2))


if __name__ == '__main__':
    main()
