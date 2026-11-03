#!/usr/bin/env python3
"""Replay a proven batch's source edits only when every original hash agrees.

Run from the destination root. This deliberately leaves the derived ledger
to prove_batch.sh; a replay always needs fresh batch/native/debt proof.
For typed files changed since the source snapshot, rerun guarded_routes.py.
"""
import argparse
from collections import defaultdict
import csv
import hashlib
from pathlib import Path


def prepare(root, rows):
    """Validate the entire replay before returning any changed source text."""
    root = Path(root).resolve()
    by_file = defaultdict(list)
    for row in rows:
        file = Path(row['file'])
        if file.is_absolute() or '..' in file.parts or not file.parts or file.parts[0] not in ('src', 'include'):
            raise ValueError(('outside_source_tree', str(file)))
        by_file[row['file']].append(row)
    prepared = {}
    for file, edits in by_file.items():
        path = (root / file).resolve()
        if not path.is_relative_to(root):
            raise ValueError(('outside_root', file))
        original = path.read_text()
        digest = hashlib.sha256(original.encode()).hexdigest()
        if any(row['source_sha256'] != digest for row in edits):
            raise ValueError(('stale_source_rerun_planner', file))
        text, previous = original, len(original) + 1
        for row in sorted(edits, key=lambda r: -int(r['start'])):
            a, b = int(row['start']), int(row['end'])
            if not 0 <= a <= b <= len(original) or b > previous or a == previous:
                raise ValueError(('overlap_or_invalid_span', file, a, b))
            if original[a:b] != row['old']:
                raise ValueError(('stale_span', file, a))
            text = text[:a] + row['new'] + text[b:]
            previous = a
        prepared[path] = text
    return prepared


def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('applied_tsv',type=Path)
    ap.add_argument('--root',type=Path,default=Path('.'))
    ap.add_argument('--apply',action='store_true')
    args=ap.parse_args()
    root=args.root.resolve()
    with args.applied_tsv.open() as input_file:
        prepared = prepare(root, csv.DictReader(input_file, delimiter='\t'))
    if args.apply:
        for path,text in prepared.items():
            path.write_text(text)
    print(('applied' if args.apply else 'checked'),len(prepared),'source files; fresh batch proof required')


if __name__=='__main__':
    main()
