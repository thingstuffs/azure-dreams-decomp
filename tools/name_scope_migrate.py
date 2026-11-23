#!/usr/bin/env python3
"""Replay migration batches onto config/names.tsv: write the scope cell (column 5) of each row the oracle keys.

    python3 tools/name_scope_migrate.py [--root .] [--obj build/obj] [--containers DIR] [--index-cache FILE]
                                        [--refusals FILE] [--write] BATCH.tsv [BATCH.tsv ...]

A batch row is (address, symbol, new_name, scope, ...).  Rows are anchored on (address, symbol), never on a line
number.  For each row:
  * the row (address, symbol, new_name) exists once: the oracle (tools/name_scope_oracle.py) is run on the current
    tree and must key it to exactly the batch's scope;
  * no row has that new name any more but a row at (address, symbol) that no batch row anchors has been renamed: the
    oracle is re-run on it with its current name, and it is keyed when it gives the batch's scope; it is reported as
    "renamed since the batch was written".  The name alone is never a reason to refuse.
Refused, with the reason in the refusals file (never forced): anchor_gone, ambiguous_anchor, oracle_refused:<why>,
oracle_differs, renamed_oracle_differs, ambiguous_renamed, scope_conflict (the row already holds another scope),
location_collision (another name claims one of its locations), evidence_has_hash.
A row that already holds the batch's scope is counted as already_scoped and left alone.  Only column 5 is written.
Without --write nothing is written.
"""
from __future__ import annotations

import argparse
import collections
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import name_scope as N  # noqa: E402
import name_scope_oracle as O  # noqa: E402


def migrate(text, batches, oracle):
    """(new text, accepted, refusals, counts).  batches = [(batch name, [batch rows])]; accepted = [(batch, row, scope,
    renamed from)]; refusals = [(batch, batch row, reason, detail)]."""
    table = N.NameTable.parse(text)
    anchored = {(r['addr'], r['old'], r['new']) for _b, rows in batches for r in rows}
    exact = collections.defaultdict(list)
    for row in table.rows:
        exact[(row.addr, row.old, row.new)].append(row)
    used, accepted, refusals = set(), [], []
    counts = collections.Counter()

    def refuse(batch, r, reason, detail=''):
        refusals.append((batch, r, reason, detail))
        counts[(batch, reason.split(':')[0])] += 1

    for batch, rows in batches:
        for r in rows:
            key = (r['addr'], r['old'], r['new'])
            found, renamed = exact.get(key, []), None
            if len(found) > 1:
                refuse(batch, r, 'ambiguous_anchor', '%d rows' % len(found))
                continue
            if not found:
                candidates = [c for c in table.by_addr.get(r['addr'], ())
                              if c.old == r['old'] and (c.addr, c.old, c.new) not in anchored and c.line not in used]
                if not candidates:
                    refuse(batch, r, 'anchor_gone')
                    continue
                keyed = []
                for c in candidates:
                    res = oracle.keys(c.addr, c.old, c.new)
                    if res['status'] == 'keyed' and tuple(res['keys']) == tuple(r['scope']):
                        keyed.append(c)
                if len(keyed) != 1:
                    refuse(batch, r, 'ambiguous_renamed' if keyed else 'renamed_oracle_differs',
                           ', '.join(c.new for c in (keyed or candidates)))
                    continue
                found, renamed = keyed, r['new']
                res = oracle.keys(found[0].addr, found[0].old, found[0].new)
            else:
                res = oracle.keys(*key)
            row = found[0]
            if res['status'] != 'keyed':
                refuse(batch, r, 'oracle_refused:' + res['reason'])
                continue
            if tuple(res['keys']) != tuple(r['scope']):
                refuse(batch, r, 'oracle_differs', ','.join(str(k) for k in res['keys']))
                continue
            if '#' in row.evidence:
                refuse(batch, r, 'evidence_has_hash')
                continue
            if row.scope == tuple(r['scope']):
                counts[(batch, 'already_scoped')] += 1
                continue
            if row.scope:
                refuse(batch, r, 'scope_conflict', N.format_scope(row.scope))
                continue
            used.add(row.line)
            accepted.append((batch, row, tuple(r['scope']), renamed))
    # a location may carry one name: every claimant of a shared location is refused
    claims = collections.defaultdict(set)
    for row in table.rows:
        for loc in row.scope:
            claims[loc].add(row.new)
    for _b, row, scope, _r in accepted:
        for loc in scope:
            claims[loc].add(row.new)
    clash = {loc for loc, names in claims.items() if len(names) > 1}
    kept = []
    for item in accepted:
        batch, row, scope, renamed = item
        if clash & set(scope):
            refuse(batch, dict(addr=row.addr, old=row.old, new=row.new, scope=scope), 'location_collision',
                   ','.join(str(l) for l in sorted(clash & set(scope))))
        else:
            kept.append(item)
            counts[(batch, 'renamed' if renamed else 'scoped')] += 1
    lines = text.split('\n')
    for _b, row, scope, _r in kept:
        cols = lines[row.line - 1].split('\t')
        cols += [''] * (4 - len(cols))
        cols = cols[:4] + [N.format_scope(scope)] + cols[5:]
        lines[row.line - 1] = '\t'.join(cols)
    return '\n'.join(lines), kept, refusals, counts


def write_refusals(path, refusals):
    with open(path, 'w') as fh:
        fh.write('batch\taddress\tsymbol\tnew_name\tscope\treason\tdetail\n')
        for batch, r, reason, detail in refusals:
            fh.write('\t'.join([batch, '0x%08X' % r['addr'], r['old'], r['new'], N.format_scope(r['scope']), reason,
                                detail]) + '\n')


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', default=str(Path(__file__).resolve().parents[1]))
    ap.add_argument('--obj', help='object directory (default <root>/build/obj); read only')
    ap.add_argument('--containers', help='retail container directory (default <root>/work/disc/containers); read only')
    ap.add_argument('--index-cache')
    ap.add_argument('--refusals', help='write the refused rows and their reasons here')
    ap.add_argument('--write', action='store_true')
    ap.add_argument('batch', nargs='+')
    a = ap.parse_args(argv)
    root = Path(a.root)
    oracle = O.open_oracle(argparse.Namespace(root=a.root, obj=a.obj, containers=a.containers, index_cache=a.index_cache))
    batches = [(Path(b).stem.split('_')[0], O.read_batch(b)) for b in a.batch]
    path = root / 'config/names.tsv'
    new, kept, refusals, counts = migrate(path.read_text(), batches, oracle)
    for batch, rows in batches:
        print('%s: %d rows; %s' % (batch, len(rows), ', '.join('%s %d' % (k[1], v) for k, v in sorted(counts.items())
                                                            if k[0] == batch) or 'nothing'))
    for _b, row, scope, renamed in kept:
        if renamed:
            print('renamed since the batch was written: config/names.tsv:%d %s (batch had %s)' % (row.line, row.new, renamed))
    if a.refusals:
        write_refusals(a.refusals, refusals)
    if a.write and kept:
        N.write_atomic(path, new)
    return 0


if __name__ == '__main__':
    sys.exit(main())
