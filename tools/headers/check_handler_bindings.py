"""Check that a callback's C spelling preserves its address in every placement.

A resolved C definition can live at several addresses. ccproc maps a readable
identifier to one canonical symbol, so replacing an address alias with that
identifier also requires this independent binding check.
"""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
import csv
import json
from pathlib import Path
import re
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'gate'))
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'build'))
import linklist
import name_inputs


class BindingIndex:
    def __init__(self, root, *, tables=None, names=None, resident=None):
        self.root = Path(root)
        self.tables = linklist.load(self.root) if tables is None else tables
        self.names = name_inputs.table(self.root / 'config/names.tsv') if names is None else names
        self.resident = {} if resident is None else resident
        if resident is None:
            catalog = self.root / 'config/slus_006.14.symbols.txt'
            if catalog.exists():
                for line in catalog.read_text().splitlines():
                    match = re.match(r'(\w+)\s*=\s*(0x[0-9a-fA-F]+);', line)
                    if match:
                        self.resident[match[1]] = int(match[2], 16)
        self.placements = defaultdict(list)
        for entry in self.tables[2].values():
            self.placements[entry['tu']].append(entry)

    def address(self, name):
        canonical = self.names.get(name, name)
        match = re.fullmatch(r'(?:func_|D_)([0-9a-fA-F]{8})', canonical)
        return int(match[1], 16) if match else self.resident.get(canonical)

    def check(self, path, old, new):
        before, after = self.address(old), self.address(new)
        result = dict(path=path, symbol=old, definition=new,
                      canonical_before='' if before is None else hex(before),
                      canonical_after='' if after is None else hex(after))
        if before is None or after is None:
            return dict(result, status='UNKNOWN_CANONICAL_ADDRESS',
                        evidence='No exact name-table or resident-catalog address; review the binding')
        failures = []
        if before != after:
            for entry in self.placements[path]:
                try:
                    # Use the same ordered rules as the actual object rebinder.
                    left = linklist._binding(self.tables, entry, before)
                    right = linklist._binding(self.tables, entry, after)
                except ValueError as error:
                    failures.append(entry['image'] + ': ' + str(error))
                    continue
                if left != right:
                    failures.append(entry['image'] + ': ' + hex(left) + ' -> ' + hex(right))
            if not self.placements[path]:
                failures.append('No registered placement; canonical literals differ')
        return dict(result, status='PLACEMENT_ADDRESS_ALIAS' if failures else 'SAME_BINDING',
                    evidence=' | '.join(failures) if failures else
                    'Canonical literals equal or every registered placement binds both to the same address')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[2])
    parser.add_argument('--map', type=Path, required=True, help='TSV with path, symbol and definition columns')
    parser.add_argument('--out', type=Path, required=True)
    args = parser.parse_args()
    index = BindingIndex(args.root)
    with args.map.open() as stream:
        rows = [index.check(row['path'], row['symbol'], row['definition'])
                for row in csv.DictReader(stream, delimiter='\t')]
    args.out.parent.mkdir(parents=True, exist_ok=True)
    with args.out.open('w') as stream:
        fields = ['path', 'symbol', 'definition', 'canonical_before', 'canonical_after', 'status', 'evidence']
        writer = csv.DictWriter(stream, delimiter='\t', fieldnames=fields)
        writer.writeheader()
        writer.writerows(rows)
    counts = dict(Counter(row['status'] for row in rows))
    print(json.dumps(counts, sort_keys=True))
    return 0 if all(row['status'] == 'SAME_BINDING' for row in rows) else 1


if __name__ == '__main__':
    raise SystemExit(main())
