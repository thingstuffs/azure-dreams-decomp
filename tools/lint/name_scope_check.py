#!/usr/bin/env python3
"""Report-only lint for the optional `scope` column of config/names.tsv (tools/name_scope.py).

    python3 tools/lint/name_scope_check.py [--root .] [--list] [--list-unresolved]

Lists the rows that would need a scope (their load address holds more than one object) and the rows whose scope
does not resolve.  It always exits 0; the counts are on the summary line, which is the last line printed.

A row needs a scope when its address
  * carries more than one row (several names at one address), or
  * carries one row, but two or more objects can be meant there: a function name where two or more home rows start
    at the address, or contain it and belong to a source file that defines two or more functions (such a row may
    hold an entry there; an upper bound, counted separately from rows that start there); a data name where two or
    more rows contain it.  Objects are home rows: a placed copy and its home are one object.
Each row of the table is one function (old symbol func_<addr>) or one data object (D_<addr>).

A scope does not resolve when
  grammar      the cell is not `container:0xHEX[,...]` sorted, unique, without spaces, tabs or #;
  location     a location lies inside no home row of its container (Geometry.owner);
  definition   a function row's home source defines neither the new name nor the old symbol;
  evidence     the evidence of a scoped row contains a # (parsers cut a line at the first #).
A row with a scope the table has no need for (single-object address) is not an error.

Summary fields: rows, addresses, multi_name (addresses, rows), need_scope (rows, addresses) = multi_name + one_row
(heads_only = start at the address, upper = also contained in a multi-function source), scoped rows, and one count
per resolution failure.
"""
from __future__ import annotations

import argparse
import collections
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import name_scope as N  # noqa: E402

# a function definition: a declarator at column 0 whose parameter list is followed by a body brace
DEFINITION = re.compile(r'^[A-Za-z_][\w \t\*]*\b([A-Za-z_]\w*)\s*\([^;]*?\)\s*\n?\s*\{', re.M)

BANDS = (
    ('scene band 0x80016000', 0x80016000, 0x80024000),
    ('selector/exe 0x80024000', 0x80024000, 0x80088760),
    ('resident engines', 0x80088760, 0x8014C800),
    ('monster banks', 0x8014C800, 0x80200000),
    ('devkit 0x807xxxxx', 0x80700000, 0x80800000),
)


def band_of(address):
    for name, lo, hi in BANDS:
        if lo <= address < hi:
            return name
    return 'other'


class Sources:
    """Function definitions of the home source of a row (ledger/layout.jsonl path), read on demand."""

    def __init__(self, root):
        self.root = Path(root)
        self.path = {}
        with open(self.root / 'ledger/layout.jsonl') as fh:
            for line in fh:
                if line.strip():
                    x = json.loads(line)
                    self.path[x['id']] = x['path']
        self._defs = {}

    def definitions(self, row_id):
        path = self.path.get(row_id)
        if path is None:
            return None
        if path not in self._defs:
            try:
                text = (self.root / path).read_text(errors='replace')
            except OSError:
                self._defs[path] = None
            else:
                self._defs[path] = {m[1] for m in DEFINITION.finditer(text)}, len(DEFINITION.findall(text))
        return self._defs[path]

    def multi_function(self, row):
        found = self.definitions(row['id'])
        return bool(found) and found[1] >= 2


def analyse(root):
    root = Path(root)
    table = N.NameTable.read(root)
    geometry = N.Geometry(root)
    sources = Sources(root)
    report = collections.OrderedDict()
    rows = table.rows
    report['rows'] = len(rows)
    report['addresses'] = len(table.by_addr)
    multi_name = {a for a, v in table.by_addr.items() if len(v) > 1}
    report['multi_name_addresses'] = len(multi_name)
    report['multi_name_rows'] = sum(len(table.by_addr[a]) for a in multi_name)

    heads, upper = set(), set()
    for address, group in table.by_addr.items():
        if address in multi_name:
            continue
        kind = 'data' if group[0].old.startswith('D_') else 'code'
        if geometry.multi_object(address, kind, lambda home: False):
            heads.add(address)
        if address in heads or geometry.multi_object(address, kind, sources.multi_function):
            upper.add(address)
    need = {}
    for address in multi_name | upper:
        for row in table.by_addr[address]:
            need[row.line] = row
    heads_rows = sum(len(table.by_addr[a]) for a in heads)
    report['one_row_heads_only_addresses'] = len(heads)
    report['one_row_heads_only_rows'] = heads_rows
    report['one_row_upper_addresses'] = len(upper)
    report['one_row_upper_rows'] = sum(len(table.by_addr[a]) for a in upper)
    report['need_scope_rows_upper'] = len(need)
    report['need_scope_addresses_upper'] = len(multi_name | upper)
    report['need_scope_rows_heads_only'] = report['multi_name_rows'] + heads_rows
    report['need_scope_addresses_heads_only'] = len(multi_name | heads)
    unscoped = [r for r in need.values() if not r.scope]
    report['need_scope_unscoped_rows'] = len(unscoped)
    bands = collections.Counter(band_of(r.addr) for r in need.values())
    report['bands'] = dict(sorted(bands.items()))

    scoped = [r for r in rows if r.scope]
    report['scoped_rows'] = len(scoped)
    problems = [('grammar', '%s:%d' % ('config/names.tsv', n), msg) for n, msg in table.errors]
    for row in scoped:
        where = 'config/names.tsv:%d' % row.line
        if '#' in row.evidence:
            problems.append(('evidence', where, 'evidence of a scoped row contains #'))
        for loc in row.scope:
            owned = geometry.owner(loc)
            if owned is None:
                problems.append(('location', where, '%s lies inside no home row' % (loc,)))
            elif row.old.startswith('func_'):
                found = sources.definitions(owned[1])
                if found is not None and not ({row.new, row.old} & found[0]):
                    problems.append(('definition', where, '%s (%s) defines neither %s nor %s'
                                     % (loc, owned[1], row.new, row.old)))
    report['problems'] = collections.Counter(p[0] for p in problems)
    return report, need, problems


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', default=str(Path(__file__).resolve().parents[2]))
    ap.add_argument('--list', action='store_true', help='print every row that would need a scope')
    ap.add_argument('--list-unresolved', action='store_true', help='print every scope that does not resolve')
    a = ap.parse_args(argv)
    report, need, problems = analyse(a.root)
    if a.list:
        for number in sorted(need):
            r = need[number]
            print('NEED config/names.tsv:%d 0x%08X %s %s%s' % (number, r.addr, r.old, r.new,
                                                              ' (scoped)' if r.scope else ''))
    if a.list_unresolved:
        for kind, where, message in problems:
            print('UNRESOLVED %s %s: %s' % (kind, where, message))
    print('name_scope: rows %(rows)d addresses %(addresses)d; multi_name %(multi_name_addresses)d addresses '
          '%(multi_name_rows)d rows; need_scope %(need_scope_rows_upper)d rows on %(need_scope_addresses_upper)d '
          'addresses (heads only: %(need_scope_rows_heads_only)d rows on %(need_scope_addresses_heads_only)d); '
          'unscoped %(need_scope_unscoped_rows)d; scoped %(scoped_rows)d' % report
          + '; unresolved %d (%s)' % (sum(report['problems'].values()),
                                      ', '.join('%s %d' % kv for kv in sorted(report['problems'].items())) or 'none')
          + '; bands ' + ', '.join('%s %d' % kv for kv in report['bands'].items()))
    return 0


if __name__ == '__main__':
    sys.exit(main())
