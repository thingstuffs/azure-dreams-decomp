#!/usr/bin/env python3
"""The image key of a config/names.tsv row: an optional 5th column, `scope`.

A load address is not one object: the town scene images all load at 0x80016000, the selector images at 0x80024000
and the monster banks 0x6000 apart, so `func_<addr>` names a different function in each image.  The disc location of
an object's first byte in its home image, `<container>:0x<file offset>`, is unique and stable, and it is what a scope
holds:

    # Columns (TAB-separated): addr  old_name  new_name  evidence  [scope]
    0x800160F8  func_800160F8  apply_first_choice_position  ...  town:0x51E0F8
    0x8002407C  func_8002407C  apply_random_actor_value_adjustment  ...  dungeon:0x188E87C,dungeon:0x191E87C

    scope := loc ("," loc)*        loc := container ":0x" HEX        sorted, no spaces

An empty scope is valid where the address holds one object.  At an address that holds several objects an unscoped
row is a legacy row: its build meaning is unchanged (the name still lowers to its old symbol), but an address ->
name lookup must not apply it to an image whose home does not define it, so name_at() answers None there.

The location comes from what the tree already records: every ledger row (ledger/rows.jsonl) has a container, a file
offset, a size and the load address of its first byte (true_name, else a func_<addr> row spelling), and a placed copy
names its home row (source_row).  The location of address A in row R is

    home(R).foff + (A - R.load_address)

so a placement in another image resolves to the object it copies.  Rows of the `slus` container carry no file
offset and have no location.

    parse_scope(text)             -> tuple of Location (ScopeError on a malformed cell; '' -> ())
    format_scope(locations)       -> the cell: sorted, unique, no spaces
    Geometry(root)                the rows: location_of(row_id, addr), owner(location), objects_at(addr, kind),
                                  multi_object(addr, kind)
    NameTable.read(root)          the names.tsv rows with their scope: name_at(old, location, geometry)

    python3 tools/name_scope.py locate ROW_ID ADDRESS | owner CONTAINER:0xOFFSET | at OLD_SYMBOL CONTAINER:0xOFFSET
"""
from __future__ import annotations

import argparse
import bisect
import collections
import json
import re
import sys
from pathlib import Path

CONTAINERS = ('main', 'town', 'dungeon', 'ovmovie', 'slus')
LOC = re.compile(r'(main|town|dungeon|ovmovie|slus):0x([0-9A-Fa-f]+)')
SYMBOL = re.compile(r'(?:func|D)_([0-9A-Fa-f]{8})$')
LOAD_CONTAINERS = ('main', 'town', 'dungeon', 'ovmovie')     # containers whose rows carry a file offset


class ScopeError(ValueError):
    pass


class Location(collections.namedtuple('Location', 'container offset')):
    __slots__ = ()

    def __str__(self):
        return '%s:0x%X' % (self.container, self.offset)


def parse_location(text):
    m = LOC.fullmatch(text.strip())
    if not m:
        raise ScopeError('not a location (want <container>:0x<hex file offset>): %r' % text)
    return Location(m[1], int(m[2], 16))


def parse_scope(text):
    """The locations of a scope cell, in the order written; '' is no scope.  Raises ScopeError on anything the
    grammar does not allow (a space, an empty element, a repeat, an unsorted list)."""
    if text is None or text == '':
        return ()
    if text != text.strip() or ' ' in text or '\t' in text or '#' in text:
        raise ScopeError('scope holds a space, tab or #: %r' % text)
    locations = tuple(parse_location(part) for part in text.split(','))
    if len(set(locations)) != len(locations):
        raise ScopeError('scope repeats a location: %r' % text)
    if list(locations) != sorted(locations):
        raise ScopeError('scope is not sorted: %r' % text)
    return locations


def format_scope(locations):
    """The cell for these locations: unique, sorted, no spaces, `container:0xHEX` with upper-case hex."""
    return ','.join(str(loc) for loc in sorted(set(Location(*x) for x in locations)))


def symbol_address(symbol):
    m = SYMBOL.match(symbol or '')
    return int(m[1], 16) if m else None


# ---------------------------------------------------------------- the rows' geometry

class Geometry:
    """Load address <-> disc location, from ledger/rows.jsonl (rows, placements and their homes)."""

    def __init__(self, root, rows=None):
        self.root = Path(root)
        if rows is None:
            rows = []
            with open(self.root / 'ledger/rows.jsonl') as fh:
                for line in fh:
                    if line.strip():
                        rows.append(json.loads(line))
        self.rows = {r['id']: r for r in rows}
        self._by_start = []        # [(load address, row)] for rows that run from a load address, sorted
        self._by_foff = collections.defaultdict(list)    # container -> [(foff, end, row id)] of home rows
        self.max_size = 0
        for r in rows:
            base = self.base_of(r)
            if base is not None and r.get('container') in LOAD_CONTAINERS and r.get('foff') is not None:
                self._by_start.append((base, r['id']))
                self.max_size = max(self.max_size, r.get('size') or 0)
            if r.get('foff') is not None and not r.get('source_row'):
                self._by_foff[r['container']].append((r['foff'], r['foff'] + (r.get('size') or 0), r['id']))
        self._by_start.sort()
        self._starts = [b for b, _ in self._by_start]
        for entries in self._by_foff.values():
            entries.sort()
        self._max_home = max([e[1] - e[0] for v in self._by_foff.values() for e in v] or [1])
        self._foffs = {c: [e[0] for e in v] for c, v in self._by_foff.items()}

    # -- one row
    @staticmethod
    def base_of(row):
        """The load address of the row's first byte: true_name, else the func_<addr> spelling of its id."""
        for key in ('true_name', 'func'):
            address = symbol_address(row.get(key))
            if address is not None:
                return address
        return None

    def home(self, row_id):
        """The home row of a row: source_row followed to a row that has none (a cycle ends the walk)."""
        seen = set()
        row = self.rows[row_id]
        while row.get('source_row') and row['id'] not in seen and row['source_row'] in self.rows:
            seen.add(row['id'])
            row = self.rows[row['source_row']]
        return row

    def location_of(self, row_id, address):
        """Location of `address` as the row holds it: home foff + (address - the row's load address).  A placement
        resolves to its home.  None when the row has no file offset or load address (the slus container) or the
        address lies outside the row."""
        row = self.rows.get(row_id)
        if row is None:
            raise KeyError(row_id)
        home = self.home(row_id)
        base = self.base_of(row)
        if base is None or home.get('foff') is None or row.get('container') not in LOAD_CONTAINERS:
            return None
        if not 0 <= address - base < max(row.get('size') or 0, 1):
            return None
        return Location(home['container'], home['foff'] + (address - base))

    def owner(self, location):
        """(row id, home row id) of the home row that holds the location (the smallest one when rows nest), or
        None.  The row id is the human-readable handle of the object."""
        entries = self._by_foff.get(location.container)
        if not entries:
            return None
        i = bisect.bisect_right(self._foffs[location.container], location.offset)
        best = None
        j = i - 1
        while j >= 0 and entries[j][0] > location.offset - self._max_home:
            foff, end, rid = entries[j]
            if foff <= location.offset < end and (best is None or end - foff < best[0]):
                best = (end - foff, rid)
            j -= 1
        return None if best is None else (best[1], self.home(best[1])['id'])

    # -- one address
    def rows_containing(self, address):
        """Every row (home or placement) whose bytes include the load address, as (row, row's base) pairs."""
        out = []
        j = bisect.bisect_right(self._starts, address) - 1
        while j >= 0 and self._starts[j] > address - max(self.max_size, 1):
            base, rid = self._by_start[j]
            row = self.rows[rid]
            if base <= address < base + (row.get('size') or 0):
                out.append(row)
            j -= 1
        return out

    def objects_at(self, address, kind='code', multi_function=None):
        """The distinct objects (home row ids) a load address can mean, over every image.

        A function (kind 'code') is meant by a row that starts at the address, or by a row of a source file that
        defines two or more functions and contains it (multi_function(home row) says which; None counts every row,
        an upper bound).  Data (kind 'data') is meant by any row that contains it.  The result is the set of home
        row ids: a placed copy and its home are one object."""
        out = set()
        for row in self.rows_containing(address):
            home = self.home(row['id'])
            if kind == 'data' or self.base_of(row) == address or multi_function is None or multi_function(home):
                out.add(home['id'])
        return out

    def multi_object(self, address, kind='code', multi_function=None):
        return len(self.objects_at(address, kind, multi_function)) >= 2


# ---------------------------------------------------------------- the names table

class NameRow(collections.namedtuple('NameRow', 'line addr old new evidence scope')):
    __slots__ = ()


class NameTable:
    """config/names.tsv rows: addr, old symbol, new name, evidence and the optional scope (parsed; a malformed
    cell is kept in `errors`, never raised)."""

    def __init__(self, rows, errors=()):
        self.rows = list(rows)
        self.errors = list(errors)
        self.by_old = collections.defaultdict(list)
        self.by_addr = collections.defaultdict(list)
        for row in self.rows:
            self.by_old[row.old].append(row)
            self.by_addr[row.addr].append(row)

    @classmethod
    def parse(cls, text):
        rows, errors = [], []
        for number, line in enumerate(text.splitlines(), 1):
            cols = line.split('\t')
            if len(cols) < 3 or line.startswith('#') or not cols[0].startswith('0x'):
                continue
            try:
                address = int(cols[0], 16)
            except ValueError:
                continue
            raw = cols[4] if len(cols) > 4 else ''
            try:
                scope = parse_scope(raw)
            except ScopeError as err:
                scope = ()
                errors.append((number, str(err)))
            rows.append(NameRow(number, address, cols[1], cols[2], cols[3] if len(cols) > 3 else '', scope))
        return cls(rows, errors)

    @classmethod
    def read(cls, root):
        return cls.parse((Path(root) / 'config/names.tsv').read_text())

    def name_at(self, old, location, geometry=None, multi_function=None):
        """The configured name of symbol `old` at the disc location: the row whose scope lists it; else the one
        unscoped row when the symbol's address holds a single object (geometry given); else None.  Never another
        image's name."""
        for row in self.by_old.get(old, ()):
            if location in row.scope:
                return row.new
        unscoped = [r for r in self.by_old.get(old, ()) if not r.scope]
        if len(unscoped) == 1 and not any(r.scope for r in self.by_old[old]):
            if geometry is not None:
                address = unscoped[0].addr
                kind = 'data' if old.startswith('D_') else 'code'
                if geometry.multi_object(address, kind, multi_function):
                    return None
            return unscoped[0].new
        return None


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', default=str(Path(__file__).resolve().parents[1]))
    sub = ap.add_subparsers(dest='cmd', required=True)
    p = sub.add_parser('locate')
    p.add_argument('row')
    p.add_argument('address')
    p = sub.add_parser('owner')
    p.add_argument('location')
    p = sub.add_parser('at')
    p.add_argument('old')
    p.add_argument('location')
    a = ap.parse_args(argv)
    g = Geometry(a.root)
    if a.cmd == 'locate':
        print(g.location_of(a.row, int(a.address, 16)))
    elif a.cmd == 'owner':
        print(g.owner(parse_location(a.location)))
    else:
        print(NameTable.read(a.root).name_at(a.old, parse_location(a.location), g))
    return 0


if __name__ == '__main__':
    sys.exit(main())
