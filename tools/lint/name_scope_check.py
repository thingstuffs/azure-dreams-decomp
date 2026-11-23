#!/usr/bin/env python3
"""Lint for the optional `scope` column of config/names.tsv (tools/name_scope.py), with a ratchet.

    python3 tools/lint/name_scope_check.py [--root .] [--list] [--list-unresolved]
                                           [--baseline FILE] [--fail-new] [--write-baseline]

Lists the rows that need a scope and the rows whose scope does not resolve; the counts are on the summary line, which
is the last line printed.  Without --fail-new it always exits 0.

A row needs a scope when its address
  * carries more than one row (several names at one address), or
  * carries one row, but two or more objects can be meant there: a function name where two or more home rows start
    at the address, or contain it and belong to a source file that defines two or more functions (such a row may
    hold an entry there; an upper bound, counted separately from rows that start there); a data name where the
    address maps to two or more disc locations over the real images (config/link views whose vma is real RAM and the
    ledger/instance_load_regions regions).  Objects are home rows: a placed copy and its home are one object.
Each row of the table is one function (old symbol func_<addr>) or one data object (D_<addr>).

A scope does not resolve when
  grammar      the cell is not `container:0xHEX[,...]` sorted, unique, without spaces, tabs or #;
  evidence     the evidence of a scoped row contains a # (parsers cut a line at the first #);
  renormalise  a location lies in a placed copy: `tools/name_scope.py renormalise` moves it to its home;
  location     function: a location lies inside no home row of its container; data: no real image of its container
               maps it back to the row's address;
  alignment    function: the home row's load address + (location - home file offset) is not the row's address;
  definition   function: no source of the home row (layout, link-graph units, module members, inline members,
               c_path) defines the new name or the old symbol;
  image        data: two locations in one (container, image delta);
  entry        data: a location that is a function row's location or the first byte of a home code row;
  duplicate    one location carries two names.
A row with a scope the table has no need for (single-object address) is not an error.

Ratchet: tools/lint/name_scope_baseline.json holds the counts and the (addr, old, new) anchors of the unscoped rows
that need a scope.  --fail-new exits 1 on an unscoped need row that is not in the baseline (a new row, or a scoped row
that lost its scope) and on any scope that does not resolve; --write-baseline rewrites the file from the table.
Retiring a row or scoping it only shrinks the set.  This lint is not part of any gate.

Summary fields: rows, addresses, multi_name (addresses, rows), need_scope (rows, addresses) = multi_name + one_row
(heads_only = start at the address, upper = also contained in a multi-function source), scoped rows, and one count
per resolution failure.
"""
from __future__ import annotations

import argparse
import collections
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import name_scope as N  # noqa: E402

DEFINITION = N.DEFINITION
BASELINE = 'tools/lint/name_scope_baseline.json'
BASELINE_SCHEMA = 'name-scope-baseline.v1'

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


class Sources(N.Sources):
    """The sources of a row (every place the tree records one), and the multi-function test of its layout source."""

    def definitions_of_row(self, row_id):
        """(defined names, count) of the layout source of the row: what the need rule counts."""
        path = self.layout.get(row_id)
        return None if path is None else self.definitions(path)

    def multi_function(self, row):
        found = self.definitions_of_row(row['id'])
        return bool(found) and found[1] >= 2

    def defines_any(self, row_id, names):
        """True/False: some source of the row defines one of the names; None when no source can be read."""
        known = False
        for path in sorted(self.paths_of(row_id)):
            found = self.definitions(path)
            if found is not None:
                known = True
                if found[0] & set(names):
                    return True
        return False if known else None


def is_code(row):
    return not row.old.startswith('D_')


def need_rows(table, geometry, sources, report=None):
    """{line: row} of the rows that need a scope: the function rule (several names at the address, or several objects
    there) and the data rule (several names, or two or more image locations)."""
    multi_name = {a for a, v in table.by_addr.items() if len(v) > 1}
    heads, upper = set(), set()
    for address, group in table.by_addr.items():
        if address in multi_name:
            continue
        kind = 'code' if is_code(group[0]) else 'data'
        if kind == 'data':
            if geometry.multi_object(address, 'data'):
                heads.add(address)
                upper.add(address)
            continue
        if geometry.multi_object(address, kind, lambda home: False):
            heads.add(address)
        if address in heads or geometry.multi_object(address, kind, sources.multi_function):
            upper.add(address)
    need = {}
    for address in multi_name | upper:
        for row in table.by_addr[address]:
            need[row.line] = row
    if report is not None:
        report['multi_name_addresses'] = len(multi_name)
        report['multi_name_rows'] = sum(len(table.by_addr[a]) for a in multi_name)
        heads_rows = sum(len(table.by_addr[a]) for a in heads)
        report['one_row_heads_only_addresses'] = len(heads)
        report['one_row_heads_only_rows'] = heads_rows
        report['one_row_upper_addresses'] = len(upper)
        report['one_row_upper_rows'] = sum(len(table.by_addr[a]) for a in upper)
        report['need_scope_rows_upper'] = len(need)
        report['need_scope_addresses_upper'] = len(multi_name | upper)
        report['need_scope_rows_heads_only'] = report['multi_name_rows'] + heads_rows
        report['need_scope_addresses_heads_only'] = len(multi_name | heads)
    return need


def check_scopes(table, geometry, sources):
    """The scoped rows that do not resolve: [(kind, where, message)]."""
    problems = [('grammar', 'config/names.tsv:%d' % n, msg) for n, msg in table.errors]
    holders = collections.defaultdict(set)
    function_locations = set()
    for row in table.rows:
        for loc in row.scope:
            holders[loc].add(row.new)
            if is_code(row):
                function_locations.add(loc)
    for loc, names in sorted(holders.items()):
        if len(names) > 1:
            problems.append(('duplicate', 'config/names.tsv', '%s carries %s' % (loc, ', '.join(sorted(names)))))
    for row in (r for r in table.rows if r.scope):
        where = 'config/names.tsv:%d' % row.line
        if '#' in row.evidence:
            problems.append(('evidence', where, 'evidence of a scoped row contains #'))
        if is_code(row):
            check_function_row(row, where, geometry, sources, problems)
        else:
            check_data_row(row, where, geometry, function_locations, problems)
    return problems


def check_function_row(row, where, geometry, sources, problems):
    for loc in row.scope:
        if geometry.in_placement(loc):
            problems.append(('renormalise', where, '%s lies in a placed copy: now %s' % (loc, geometry.normalise(loc))))
            continue
        owned = geometry.owner(loc)
        if owned is None:
            problems.append(('location', where, '%s lies inside no home row' % (loc,)))
            continue
        home = geometry.rows[owned[1]]
        base = geometry.base_of(home)
        if base is None or base + (loc.offset - home['foff']) != row.addr:
            problems.append(('alignment', where, '%s: %s loads at %s, so the location holds %s, not 0x%08X'
                             % (loc, owned[1], 'nothing' if base is None else '0x%08X' % base,
                                'nothing' if base is None else '0x%08X' % (base + loc.offset - home['foff']), row.addr)))
        if row.old.startswith('func_') and sources.defines_any(owned[1], {row.new, row.old}) is False:
            problems.append(('definition', where, '%s (%s) defines neither %s nor %s'
                             % (loc, owned[1], row.new, row.old)))


def check_data_row(row, where, geometry, function_locations, problems):
    deltas = collections.Counter()
    for loc in row.scope:
        maps = [im for im in geometry.images.with_foff(loc.container, loc.offset)
                if im.vma + (loc.offset - im.foff) == row.addr]
        if not maps:
            problems.append(('location', where, '%s lies in no real image that maps it to 0x%08X' % (loc, row.addr)))
            continue
        if geometry.in_placement(loc):
            problems.append(('renormalise', where, '%s lies in a placed copy: now %s' % (loc, geometry.normalise(loc))))
        for delta in {im.delta for im in maps}:
            deltas[(loc.container, delta)] += 1
        owned = geometry.owner(loc)
        starts_code = owned is not None and geometry.rows[owned[1]]['foff'] == loc.offset \
            and not geometry.rows[owned[1]].get('data_kind')
        if loc in function_locations or starts_code:
            problems.append(('entry', where, '%s is the location of a function' % (loc,)))
    for (container, delta), n in sorted(deltas.items()):
        if n > 1:
            problems.append(('image', where, '%d locations in one image delta of %s (0x%X)' % (n, container, delta)))


# ---------------------------------------------------------------- the ratchet

def anchors(rows):
    """Sorted [addr, old, new] anchors (one per row) of table rows."""
    return sorted(['0x%08X' % r.addr, r.old, r.new] for r in rows)


def baseline_document(need, rows):
    unscoped = [r for r in need.values() if not r.scope]
    return collections.OrderedDict([
        ('schema', BASELINE_SCHEMA),
        ('counts', collections.OrderedDict([('need_scope_rows', len(need)), ('unscoped_need_rows', len(unscoped)),
                                            ('names_rows', len(rows))])),
        ('unscoped', anchors(unscoped)),
    ])


def baseline_text(document):
    """The baseline file text: the counts, then one anchor per line."""
    head = json.dumps({k: document[k] for k in ('schema', 'counts')}, indent=1)[:-2]
    lines = ',\n'.join('  ' + json.dumps(a) for a in document['unscoped'])
    return head + ',\n "unscoped": [\n' + lines + '\n ]\n}\n'


def read_baseline(path):
    try:
        data = json.loads(Path(path).read_text())
    except (OSError, ValueError):
        return None
    if not isinstance(data, dict) or data.get('schema') != BASELINE_SCHEMA:
        return None
    return data


def ratchet(need, baseline):
    """(new, gone): the unscoped need rows that the baseline does not hold (as rows), and the baseline anchors that no
    unscoped need row has any more (as anchors).  Anchors count with multiplicity."""
    have = collections.Counter(tuple(a) for a in baseline.get('unscoped', ()))
    new = []
    for row in sorted((r for r in need.values() if not r.scope), key=lambda r: r.line):
        key = ('0x%08X' % row.addr, row.old, row.new)
        if have[key] > 0:
            have[key] -= 1
        else:
            new.append(row)
    gone = sorted(list(k) for k, n in have.items() for _ in range(n))
    return new, gone


def analyse(root):
    root = Path(root)
    table = N.NameTable.read(root)
    geometry = N.Geometry(root)
    sources = Sources(root, geometry.rows)
    report = collections.OrderedDict()
    rows = table.rows
    report['rows'] = len(rows)
    report['addresses'] = len(table.by_addr)
    need = need_rows(table, geometry, sources, report)
    unscoped = [r for r in need.values() if not r.scope]
    report['need_scope_unscoped_rows'] = len(unscoped)
    report['need_function_rows'] = sum(1 for r in need.values() if is_code(r))
    report['need_data_rows'] = sum(1 for r in need.values() if not is_code(r))
    bands = collections.Counter(band_of(r.addr) for r in need.values())
    report['bands'] = dict(sorted(bands.items()))
    report['scoped_rows'] = sum(1 for r in rows if r.scope)
    problems = check_scopes(table, geometry, sources)
    report['problems'] = collections.Counter(p[0] for p in problems)
    return report, need, problems, table


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', default=str(Path(__file__).resolve().parents[2]))
    ap.add_argument('--list', action='store_true', help='print every row that would need a scope')
    ap.add_argument('--list-unresolved', action='store_true', help='print every scope that does not resolve')
    ap.add_argument('--baseline', help='the ratchet file (default: %s under --root)' % BASELINE)
    ap.add_argument('--fail-new', action='store_true',
                    help='exit 1 on an unscoped need row the baseline does not hold, or on an unresolved scope')
    ap.add_argument('--write-baseline', action='store_true', help='rewrite the baseline from the table')
    a = ap.parse_args(argv)
    report, need, problems, table = analyse(a.root)
    baseline_path = Path(a.baseline) if a.baseline else Path(a.root) / BASELINE
    if a.list:
        for number in sorted(need):
            r = need[number]
            print('NEED config/names.tsv:%d 0x%08X %s %s%s' % (number, r.addr, r.old, r.new,
                                                              ' (scoped)' if r.scope else ''))
    if a.list_unresolved:
        for kind, where, message in problems:
            print('UNRESOLVED %s %s: %s' % (kind, where, message))
    failed = False
    if a.write_baseline:
        baseline_path.write_text(baseline_text(baseline_document(need, table.rows)))
        print('baseline written: %s' % baseline_path)
    if a.fail_new:
        baseline = read_baseline(baseline_path)
        if baseline is None:
            print('RATCHET no readable baseline at %s' % baseline_path)
            failed = True
        else:
            new, gone = ratchet(need, baseline)
            for row in new:
                print('NEW config/names.tsv:%d 0x%08X %s %s: needs a scope and the baseline does not hold it'
                      % (row.line, row.addr, row.old, row.new))
            if gone:
                print('ratchet: %d baseline anchors no longer need a scope (shrink the baseline)' % len(gone))
            failed = bool(new) or bool(problems)
    print('name_scope: rows %(rows)d addresses %(addresses)d; multi_name %(multi_name_addresses)d addresses '
          '%(multi_name_rows)d rows; need_scope %(need_scope_rows_upper)d rows on %(need_scope_addresses_upper)d '
          'addresses (heads only: %(need_scope_rows_heads_only)d rows on %(need_scope_addresses_heads_only)d); '
          'unscoped %(need_scope_unscoped_rows)d; scoped %(scoped_rows)d' % report
          + '; unresolved %d (%s)' % (sum(report['problems'].values()),
                                      ', '.join('%s %d' % kv for kv in sorted(report['problems'].items())) or 'none')
          + '; bands ' + ', '.join('%s %d' % kv for kv in report['bands'].items()))
    return 1 if failed else 0


if __name__ == '__main__':
    sys.exit(main())
