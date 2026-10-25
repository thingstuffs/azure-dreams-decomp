#!/usr/bin/env python3
"""Write bounded retail disassembly for named functions, using registered rows."""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parents[2]


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('symbols', nargs='+')
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--container')
    ap.add_argument('--source', help='require the registered physical source home')
    args = ap.parse_args()
    args.out.mkdir(parents=True, exist_ok=True)
    names = {}
    for line in (ROOT / 'config/names.tsv').read_text().splitlines():
        cols = line.split('\t')
        if len(cols) >= 3 and not line.startswith('#'):
            names.setdefault(cols[2], set()).add(cols[1])
    rows = list(map(json.loads, (ROOT / 'ledger/rows.jsonl').open()))
    homes = {r['id']: r['path'] for r in map(json.loads, (ROOT / 'ledger/layout.jsonl').open())}
    homes.update({r['member_id']: r['tu_new'] for r in
                  map(json.loads, (ROOT / 'ledger/layout_inline.jsonl').open())})
    index = []
    for symbol in args.symbols:
        aliases = names.get(symbol, {symbol})
        matches = [r for r in rows if (r.get('true_name') in aliases or r['func'] in aliases)
                   and (not args.container or r['container'] == args.container)
                   and (not args.source or homes.get(r['id']) == args.source)]
        if len(matches) != 1:
            raise SystemExit(symbol + ': ambiguous or missing row: ' + str([r['id'] for r in matches]))
        row = matches[0]
        address = row.get('true_name') or row['func']
        start = int(address.removeprefix('func_'), 16)
        container = 'work/disc/containers/' + '_'.join([row['container'].upper()] * 2) + '.BIN'
        args_list = ['mipsel-linux-gnu-objdump', '-D', '--no-show-raw-insn', '-b', 'binary', '-m', 'mips:3000', '-EL',
                     '--adjust-vma=' + str(start - row['foff']), '--start-address=' + str(start),
                     '--stop-address=' + str(start + row['size']), container]
        listing = subprocess.check_output(args_list, cwd=ROOT, text=True)
        dest = args.out / (symbol + '.retail.txt')
        if len(listing.encode()) > 2_000_000:
            raise SystemExit('listing exceeds delivery limit')
        dest.write_text(listing)
        with (ROOT / container).open('rb') as stream:
            stream.seek(row['foff'])
            digest = hashlib.sha256(stream.read(row['size'])).hexdigest()
        index.append(dict(symbol=symbol, row=row['id'], start=hex(start), size=row['size'],
                          container=container, offset=row['foff'], retail_sha256=digest,
                          listing=dest.name))
        print(symbol, row['id'], row['size'])
    (args.out / 'index.json').write_text(json.dumps(index, indent=2, sort_keys=True) + '\n')


if __name__ == '__main__':
    main()
