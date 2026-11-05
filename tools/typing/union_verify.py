#!/usr/bin/env python3
"""Conservative first-pass review of the union ledger.

Only a zero-access member is enough for an automated retire candidate.
Same-object proof is deliberately manual and requires creator/callback evidence.
"""
from __future__ import annotations

import argparse
import csv
import json
from pathlib import Path


def verify(rows):
    for row in rows:
        if (row.get('count_basis') == 'retired_historical' or
                row.get('status') == 'proven-by-bytes' or
                (row.get('status') in {'proven', 'unproven', 'retire'} and
                 row.get('evidence', '').startswith('UNION:')) or
                row.get('retired_to_cast') or
                row.get('evidence', '').startswith('Retired to')):
            verdict = row['status']
        elif row['kind'] == 'zero_init_idiom':
            row['status'] = 'proven'
            row['evidence'] = 'Round 118 accepted compiler lever; tracked separately from overlays.'
            verdict = 'round118_trade'
        else:
            unused = [m['name'] for m in row['members']
                      if sum(row['uses'][m['name']].values()) == 0]
            if unused:
                row['status'] = 'retire'
                row['evidence'] = ('No spelled member access found for ' + ', '.join(unused)
                                   + '; inspect aliases/macros before editing.')
                verdict = 'retire_candidate'
            else:
                row['status'] = 'unproven'
                row['evidence'] = ('Spelled access to every member; same-object and '
                                   'creator/callback proof still required.')
                verdict = 'unproven'
        used = ','.join(f'{m["name"]}:{sum(row["uses"][m["name"]].values())}'
                        for m in row['members'])
        yield row, used, verdict


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--ledger', type=Path, default=Path('ledger/unions.jsonl'))
    parser.add_argument('--report', type=Path, default=Path('build/union_verify.tsv'))
    args = parser.parse_args()
    rows = [json.loads(line) for line in args.ledger.read_text().splitlines() if line.strip()]
    reviewed = list(verify(rows))
    args.ledger.write_text(''.join(json.dumps(row, sort_keys=True) + '\n' for row, _, _ in reviewed))
    args.report.parent.mkdir(parents=True, exist_ok=True)
    with args.report.open('w', newline='') as stream:
        writer = csv.writer(stream, delimiter='\t', lineterminator='\n')
        writer.writerow(['id', 'kind', 'members_used', 'verdict', 'evidence'])
        for row, used, verdict in reviewed:
            writer.writerow([row['id'], row['kind'], used, verdict, row['evidence']])
    print(f'{len(reviewed)} reviewed; {sum(row["status"] == "retire" for row, _, _ in reviewed)} retire candidates')


if __name__ == '__main__':
    main()
