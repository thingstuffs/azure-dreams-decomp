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

    Images(root)                  the real images: config/link views and ledger/instance_load_regions regions;
                                  a data object is (image, load address), written image.foff + (A - image.vma)
    Sources(root)                 the C sources of a row (layout, link-graph units, module members, inline members)
    renormalise_text(text, g)     scope locations that now lie in a placement, moved to their home

    python3 tools/name_scope.py locate ROW_ID ADDRESS | owner CONTAINER:0xOFFSET | at OLD_SYMBOL CONTAINER:0xOFFSET
                                | renormalise [--write]

The load address of a row's first byte is its own entry in a real config/link view, else the delta of the real image
holding its file offset, else its true_name; the spelling of its id is never used (a row id can spell a row-space
address that no code ever ran at).  A placed copy P of a home H holds address A at

    H.foff + s(P) + (A - P.vma)           s(P) = the home's body_offset when P holds only the home's body, else 0
"""
from __future__ import annotations

import argparse
import bisect
import collections
import glob
import json
import os
import re
import sys
import tempfile
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


# ---------------------------------------------------------------- real images

RAM = (0x80000000, 0x80800000)
ROW_SPACE_DELTAS = (0x7FFE0000, 0x80080000, 0x7FDB0000)     # deltas of the row-space spellings of rows


def is_real_vma(foff, vma):
    """A load address code can run at: in RAM and not a row-space spelling (row-space deltas above 0x80200000)."""
    if vma is None or not RAM[0] <= vma < RAM[1]:
        return False
    return not (foff is not None and vma - foff in ROW_SPACE_DELTAS and vma >= 0x80200000)


def _int(value):
    if value is None:
        return None
    return int(value, 16) if isinstance(value, str) else int(value)


class Image(collections.namedtuple('Image', 'name container foff size vma source')):
    __slots__ = ()

    @property
    def delta(self):
        return self.vma - self.foff

    def has_vma(self, address):
        return self.vma <= address < self.vma + self.size

    def has_foff(self, offset):
        return self.foff <= offset < self.foff + self.size

    def location(self, address):
        """image.foff + (A - image.vma): the disc location of a load address in this image."""
        return Location(self.container, self.foff + (address - self.vma))


class Placement(collections.namedtuple('Placement', 'row home container foff vma size image body_offset')):
    """A link entry that runs a row's bytes at vma: its own home (row == home) or a placed copy."""
    __slots__ = ()


class Images:
    """The real images of the tree: every config/link view whose vma is real RAM and every load region of
    ledger/instance_load_regions.jsonl (pseudo images - row-space vmas, KSEG1 mirrors - are left out), and the link
    entries that place rows in them.  Built from the files in `root`, or from lists (tests)."""

    def __init__(self, images=(), placements=()):
        self.real = sorted((im for im in images if im.vma is not None and is_real_vma(im.foff, im.vma)),
                           key=lambda im: (im.vma, im.container, im.foff))
        self.placements = [p for p in placements if is_real_vma(p.foff, p.vma)]
        self._vmas = [im.vma for im in self.real]
        self._max_size = max([im.size for im in self.real] or [0])
        self._by_container = collections.defaultdict(list)
        for im in self.real:
            self._by_container[im.container].append(im)
        self.entry = {}                      # row id -> its first real link entry
        for p in self.placements:
            self.entry.setdefault(p.row, p)
        self._copies = collections.defaultdict(list)       # container -> [(foff, end, placement)] sorted
        for p in self.placements:
            if p.row != p.home:
                self._copies[p.container].append((p.foff, p.foff + p.size, p))
        for entries in self._copies.values():
            entries.sort(key=lambda e: e[:2])
        self._copy_keys = {c: [e[0] for e in v] for c, v in self._copies.items()}
        self._copy_max = max([e[1] - e[0] for v in self._copies.values() for e in v] or [1])

    @classmethod
    def read(cls, root):
        root = Path(root)
        images, placements = [], []
        for path in sorted(glob.glob(str(root / 'config/link/*/*.json'))):
            if path.endswith('copy_links.json'):
                continue
            with open(path) as fh:
                view = json.load(fh)
            if not isinstance(view, dict) or 'image' not in view or 'container' not in view:
                continue
            foff, vma = _int(view.get('foff')), _int(view.get('vma'))
            images.append(Image(view['image'], view['container'], foff, _int(view.get('size')), vma, 'link'))
            for e in view.get('entries') or ():
                if e.get('kind') is None and e.get('row'):
                    placements.append(Placement(e['row'], e.get('home') or e['row'], view['container'],
                                                _int(e['foff']), _int(e.get('vma')), e.get('size') or 0,
                                                view['image'], e.get('body_offset') or 0))
        regions = root / 'ledger/instance_load_regions.jsonl'
        if regions.is_file():
            with open(regions) as fh:
                for line in fh:
                    if line.strip():
                        x = json.loads(line)
                        images.append(Image('region:%s:0x%X' % (x['container'], x['foff']), x['container'],
                                            x['foff'], x['size'], x['base'], 'region'))
        return cls(images, placements)

    @classmethod
    def empty(cls):
        return cls()

    def at_vma(self, address):
        """Real images whose vma span holds the load address."""
        out = []
        j = bisect.bisect_right(self._vmas, address) - 1
        while j >= 0 and self._vmas[j] > address - max(self._max_size, 1):
            if self.real[j].has_vma(address):
                out.append(self.real[j])
            j -= 1
        return out

    def with_foff(self, container, offset):
        return [im for im in self._by_container.get(container, ()) if im.has_foff(offset)]

    def locations_of(self, address):
        """{Location: [image names]}: the distinct disc locations a load address can mean, over the real images."""
        out = collections.defaultdict(list)
        for im in self.at_vma(address):
            out[im.location(address)].append(im.name)
        return dict(out)

    def multi_object(self, address):
        return len(self.locations_of(address)) >= 2

    def real_base(self, row_id):
        e = self.entry.get(row_id)
        return None if e is None else e.vma

    def body_shift(self, placement):
        """s(P): the home's body_offset when the placement holds only the home's body, else 0."""
        if placement.row == placement.home:
            return 0
        home = self.entry.get(placement.home)
        if home is not None and home.body_offset and placement.size == home.size - home.body_offset:
            return home.body_offset
        return 0

    def copy_at(self, location):
        """The placed copy (a link entry whose row is not its home) whose bytes hold the disc location, or None."""
        entries = self._copies.get(location.container)
        if not entries:
            return None
        keys = self._copy_keys[location.container]
        j = bisect.bisect_right(keys, location.offset) - 1
        while j >= 0 and entries[j][0] > location.offset - self._copy_max:
            if entries[j][0] <= location.offset < entries[j][1]:
                return entries[j][2]
            j -= 1
        return None


# ---------------------------------------------------------------- the rows' geometry

class Geometry:
    """Load address <-> disc location, from ledger/rows.jsonl (rows, placements and their homes) and the real images."""

    def __init__(self, root, rows=None, images=None):
        self.root = Path(root)
        if rows is None:
            rows = []
            with open(self.root / 'ledger/rows.jsonl') as fh:
                for line in fh:
                    if line.strip():
                        rows.append(json.loads(line))
            if images is None:
                images = Images.read(self.root)
        self.images = images if images is not None else Images.empty()
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
    def base_of(self, row):
        """The load address of the row's first byte: its own entry in a real config/link view, else the delta of the
        real image holding its file offset, else its true_name; None otherwise (the spelling of the id is never used)."""
        base = self.images.real_base(row.get('id'))
        if base is not None:
            return base
        container, foff = row.get('container'), row.get('foff')
        if foff is not None and container in LOAD_CONTAINERS:
            deltas = {im.delta for im in self.images.with_foff(container, foff)}
            if len(deltas) == 1:
                return foff + deltas.pop()
        address = symbol_address(row.get('true_name'))
        if address is not None and is_real_vma(foff if foff is not None else 0, address):
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
        """Location of `address` as the row holds it: home foff + s + (address - the row's load address).  A placement
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
        entry = self.images.entry.get(row_id)
        shift = self.images.body_shift(entry) if entry is not None else 0
        return Location(home['container'], home['foff'] + shift + (address - base))

    def normalise(self, location):
        """The home location of a location that lies in a placed copy: H.foff + s(P) + (offset - P.foff); a location
        that lies in no copy is returned as it is."""
        copy = self.images.copy_at(location)
        if copy is None or copy.home not in self.rows:
            return location
        home = self.home(copy.home)
        if home.get('foff') is None:
            return location
        return Location(home['container'], home['foff'] + self.images.body_shift(copy) + (location.offset - copy.foff))

    def in_placement(self, location):
        return self.images.copy_at(location) is not None

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
        """Two or more objects a load address can mean.  Data: two or more distinct disc locations of the address over
        the real images (when the tree has any); function: as objects_at."""
        if kind == 'data' and self.images.real:
            return self.images.multi_object(address)
        return len(self.objects_at(address, kind, multi_function)) >= 2

    def starts_at(self, address, location, kind='code'):
        """Whether a row or placement starts at the address in the image of the location (code), or a real image
        maps the location to the address (data)."""
        if kind == 'data':
            return not self.images.real or any(im.location(address) == location for im in self.images.at_vma(address))
        for row in self.rows_containing(address):
            if self.base_of(row) == address and self.location_of(row['id'], address) == location:
                return True
        return False


# ---------------------------------------------------------------- the C sources of a row

DEFINITION = re.compile(r'^[A-Za-z_][\w \t\*]*\b([A-Za-z_]\w*)\s*\([^;]*?\)\s*\n?\s*\{', re.M)


def definitions_in(text):
    """(names of the functions a C text defines, their count): a declarator at column 0 followed by a body brace."""
    return {m[1] for m in DEFINITION.finditer(text)}, len(DEFINITION.findall(text))


class Sources:
    """The C source files of a row: ledger/layout.jsonl, the link-graph units and module members, the inline members
    of a merged unit and the row's own c_path.  `definitions(path)` are the functions a file defines."""

    def __init__(self, root, rows=None):
        self.root = Path(root)
        self.layout = {}
        self.units = collections.defaultdict(set)
        self.inline = collections.defaultdict(set)
        self.rows = rows if rows is not None else {}
        self._defs = {}
        self._load()

    def _jsonl(self, path):
        if path.is_file():
            with open(path) as fh:
                for line in fh:
                    if line.strip():
                        yield json.loads(line)

    def _load(self):
        for x in self._jsonl(self.root / 'ledger/layout.jsonl'):
            self.layout[x['id']] = x['path']
        modules = {}
        for path in sorted(glob.glob(str(self.root / 'config/link_graph/tus.*.jsonl'))):
            for x in self._jsonl(Path(path)):
                if x['id'].startswith('module/'):
                    modules[x['id'][7:]] = x['source']
                else:
                    self.units[x['id']].add(x['source'])
        for path in sorted(glob.glob(str(self.root / 'ledger/modules/*.json'))):
            with open(path) as fh:
                data = json.load(fh)
            if isinstance(data, dict) and data.get('module') in modules:
                for member in data.get('members') or ():
                    self.units[member].add(modules[data['module']])
        for x in self._jsonl(self.root / 'ledger/layout_inline.jsonl'):
            self.inline[x['member_id']].update((x['tu_new'], x['member']))

    def paths_of(self, row_id):
        found = set(self.units.get(row_id, ())) | set(self.inline.get(row_id, ()))
        if row_id in self.layout:
            found.add(self.layout[row_id])
        row = self.rows.get(row_id)
        if row and row.get('c_path'):
            found.add(row['c_path'])
        return found

    def definitions(self, path):
        """(set of defined names, count) of a source file, or None when it cannot be read."""
        if path not in self._defs:
            try:
                self._defs[path] = definitions_in((self.root / path).read_text(errors='replace'))
            except OSError:
                self._defs[path] = None
        return self._defs[path]


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
        """The configured name of symbol `old` at the disc location.  With a geometry: the location is first moved to
        its home when it lies in a placed copy; then the row whose scope lists it; else the one unscoped row, only
        when no row of the symbol is scoped, the symbol's address holds a single object, and a row or placement
        starts at the address in the asked image; else None.  Never another image's name."""
        rows = self.by_old.get(old, ())
        if geometry is not None:
            location = geometry.normalise(location)
        for row in rows:
            if location in row.scope:
                return row.new
        unscoped = [r for r in rows if not r.scope]
        if len(unscoped) == 1 and not any(r.scope for r in rows):
            if geometry is not None:
                address = unscoped[0].addr
                kind = 'data' if old.startswith('D_') else 'code'
                if geometry.multi_object(address, kind, multi_function):
                    return None
                if not geometry.starts_at(address, location, kind):
                    return None
            return unscoped[0].new
        return None


# ---------------------------------------------------------------- renormalise

def renormalise_text(text, geometry):
    """Rewrite each scope location that now lies in a placed copy to its home location (the C6 formula).

    Returns (new text, changes, refusals): a change is (line, old scope, new scope); a refusal is (line, location,
    home location, the other name there) and leaves the row's scope as it was.  Only column 5 of a changed row is
    touched."""
    table = NameTable.parse(text)
    holders = collections.defaultdict(set)         # location -> names of the rows whose scope holds it
    for row in table.rows:
        for loc in row.scope:
            holders[loc].add(row.new)
    lines = text.split('\n')
    changes, refusals = [], []
    for row in table.rows:
        if not row.scope:
            continue
        moved, refused = [], False
        for loc in row.scope:
            home = geometry.normalise(loc)
            if home != loc:
                other = sorted(holders.get(home, set()) - {row.new})
                if other:
                    refusals.append((row.line, loc, home, other[0]))
                    refused = True
                    break
            moved.append(home)
        if refused:
            continue
        scope = format_scope(moved)
        if scope != format_scope(row.scope):
            cols = lines[row.line - 1].split('\t')
            cols[4] = scope
            lines[row.line - 1] = '\t'.join(cols)
            changes.append((row.line, format_scope(row.scope), scope))
    return '\n'.join(lines), changes, refusals


def write_atomic(path, text):
    path = Path(path)
    fd, tmp = tempfile.mkstemp(dir=str(path.parent), prefix='.' + path.name + '.')
    try:
        with os.fdopen(fd, 'w') as fh:
            fh.write(text)
        os.replace(tmp, path)
    except BaseException:
        if os.path.exists(tmp):
            os.unlink(tmp)
        raise


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
    p = sub.add_parser('renormalise', help='move scope locations that lie in a placed copy to their home location')
    p.add_argument('--write', action='store_true', help='write config/names.tsv (default: print only)')
    a = ap.parse_args(argv)
    g = Geometry(a.root)
    if a.cmd == 'locate':
        print(g.location_of(a.row, int(a.address, 16)))
    elif a.cmd == 'owner':
        print(g.owner(parse_location(a.location)))
    elif a.cmd == 'at':
        print(NameTable.read(a.root).name_at(a.old, parse_location(a.location), g))
    else:
        path = Path(a.root) / 'config/names.tsv'
        text = path.read_text()
        new, changes, refusals = renormalise_text(text, g)
        for line, old, scope in changes:
            print('RENORMALISE config/names.tsv:%d %s -> %s' % (line, old, scope))
        for line, loc, home, other in refusals:
            print('REFUSED config/names.tsv:%d %s -> %s: that location carries %s' % (line, loc, home, other))
        print('renormalise: %d changed, %d refused' % (len(changes), len(refusals)))
        if a.write and changes:
            write_atomic(path, new)
        return 1 if refusals else 0
    return 0


if __name__ == '__main__':
    sys.exit(main())
