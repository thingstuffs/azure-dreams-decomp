#!/usr/bin/env python3
"""Map runtime source lines between two trees without modifying either tree.

    rt_linemap.py --old-root OLD --root CURRENT --out lines.json.gz

Equal blocks and equal-length replacements map by position. Deleted or resized
replacement lines remain unmapped; users of this map must report that loss.
"""
from __future__ import annotations

import argparse
import difflib
import gzip
import json
from pathlib import Path


class LineMap:
    def __init__(self, maps=None, missing=()):
        self.maps = maps or {}
        self.missing = set(missing)

    def line(self, file, line):
        if not line:
            return line
        if file in self.missing:
            return None
        mapping = self.maps.get(file)
        if mapping is None:
            return line
        return mapping[line] if 0 < line < len(mapping) else None

    def write(self, path):
        path = Path(path)
        op = gzip.open if path.suffix == '.gz' else open
        with op(path, 'wt') as stream:
            json.dump(dict(version=1, maps=self.maps, missing=sorted(self.missing)), stream)

    @classmethod
    def read(cls, path):
        path = Path(path)
        op = gzip.open if path.suffix == '.gz' else open
        with op(path, 'rt') as stream:
            data = json.load(stream)
        if data.get('version') != 1:
            raise ValueError('unsupported line-map version')
        return cls(data['maps'], data.get('missing', ()))


def build(old, new):
    old, new = Path(old), Path(new)
    maps, missing = {}, []
    for top in ('src', 'include'):
        for path in sorted((old / top).rglob('*')):
            if path.suffix not in ('.c', '.h', '.inc') or not path.is_file():
                continue
            relative = path.relative_to(old).as_posix()
            current = new / relative
            if not current.is_file():
                missing.append(relative)
                continue
            before, after = path.read_bytes(), current.read_bytes()
            if before == after:
                continue
            left, right = before.decode('latin-1').splitlines(), after.decode('latin-1').splitlines()
            mapping = [None] * (len(left) + 1)
            for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, left, right, autojunk=False).get_opcodes():
                if tag == 'equal' or (tag == 'replace' and i2 - i1 == j2 - j1):
                    for offset in range(i2 - i1):
                        mapping[i1 + offset + 1] = j1 + offset + 1
            maps[relative] = mapping
    return LineMap(maps, missing)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--old-root', required=True, type=Path)
    parser.add_argument('--root', required=True, type=Path)
    parser.add_argument('--out', required=True, type=Path)
    args = parser.parse_args(argv)
    mapping = build(args.old_root, args.root)
    mapping.write(args.out)
    print(json.dumps(dict(changed_files=len(mapping.maps), missing_files=len(mapping.missing))))


if __name__ == '__main__':
    main()
