#!/usr/bin/env python3
"""The byte oracle of the name scope: which disc locations a names.tsv row can be keyed to, shown by bytes.

    python3 tools/name_scope_oracle.py [--root .] [--obj build/obj] [--containers DIR] functions BATCH.tsv [--out FILE]
    python3 tools/name_scope_oracle.py [...] check BATCH.tsv
    python3 tools/name_scope_oracle.py [...] data BATCH.tsv

It reads the objects under --obj (the current full build; an object is current when every input source's sha256
equals its proof receipt) and the retail containers (--containers, read only) at run time.  It never writes retail
bytes or disassembly anywhere: the report holds locations, offsets, sizes and sha256 digests of relocation-masked
object bytes only.

Function row (old func_<addr>, new name, address A).  The defining objects are the current objects that define the old
symbol, built from a source that defines the new name or the old symbol.  Each defining source has home rows (the
rows whose sources, by Sources.paths_of, include it).  The location of A in a home row is
home.foff + (A - the row's real load address); it is a key when a defining object's relocation-masked bytes match the
container there.  Refusals: a defining source with no keyed location or no home row; no key at all; two keys in one
real image; (across rows) a location that two function names claim.

Data row (old D_<addr>).  A location counts only when bytes show that code naming the row reaches it: a placed
function whose current object carries a HI16/LO16 pair against the old symbol decodes, in the container at the
placement, to A (resolved address = decoded pair in the container - decoded pair in the object); or a current object
that defines the symbol matches at its defining source's own placement.  A reference from code of a loaded image to the
resident-engine band is credited to the engine of the code's own container when exactly one real image of that
container spans A, and is marked `resident`: an inference, not shown by bytes.

Batch TSV: address, symbol, new_name, scope, ... (a migration batch); the first four columns are read.
"""
from __future__ import annotations

import argparse
import collections
import hashlib
import json
import os
import pickle
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import name_scope as N  # noqa: E402

CONTAINER_FILES = {'main': 'MAIN_MAIN.BIN', 'town': 'TOWN_TOWN.BIN', 'dungeon': 'DUNGEON_DUNGEON.BIN',
                   'ovmovie': 'OVMOVIE.BIN'}
# relocated bytes (little endian byte index -> kept bits): R_MIPS_32 all four bytes, JMP26 the opcode byte's top six
# bits, HI16/LO16/GPREL16 the opcode half
MASK = {2: (0, 0, 0, 0), 4: (0, 0, 0, 0xFC), 5: (0, 0, 0xFF, 0xFF), 6: (0, 0, 0xFF, 0xFF), 7: (0, 0, 0xFF, 0xFF)}
R_HI16, R_LO16 = 5, 6
MIN_FUNCTION_BYTES = 8
ENGINE_BAND = (0x80088760, 0x8014C800)


# ---------------------------------------------------------------- objects

def parse_object(blob):
    """{syms: [(name, value, size, type, bind, section)], rels: {section: [(offset, type, symbol index)]},
    secs: {index: (name, type, file offset, size)}} of an ELF32 little-endian object, or None."""
    if blob[:4] != b'\x7fELF':
        return None
    shoff, = struct.unpack_from('<I', blob, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from('<HHH', blob, 0x2E)
    heads = []
    for i in range(shnum):
        name, typ, _flags, _addr, off, size, link, info, _align, _ent = struct.unpack_from('<10I', blob, shoff + i * shentsize)
        heads.append((name, typ, off, size, link, info))

    def cstr(base, i):
        return blob[base + i:blob.index(b'\0', base + i)].decode('latin1')

    names = [cstr(heads[shstrndx][2], h[0]) for h in heads]
    syms, rels = [], {}
    for h in heads:
        if h[1] == 2:
            strtab = heads[h[4]]
            for j in range(h[3] // 16):
                nm, val, sz, info, _o, ndx = struct.unpack_from('<IIIBBH', blob, h[2] + j * 16)
                syms.append((cstr(strtab[2], nm), val, sz, info & 0xF, info >> 4, ndx))
    for h in heads:
        if h[1] == 9:
            rels[h[5]] = [(o, i & 0xFF, i >> 8) for o, i in (struct.unpack_from('<II', blob, h[2] + j * 8)
                                                            for j in range(h[3] // 8))]
    return dict(syms=syms, rels=rels, secs={i: (names[i], h[1], h[2], h[3]) for i, h in enumerate(heads)})


class Objects:
    """The objects of a build directory: symbols, relocations, input sources and whether each is current."""

    def __init__(self, directory, root, cache=None):
        self.dir = Path(directory)
        self.root = Path(root)
        self.index = {}
        self._sha = {}
        if cache and Path(cache).is_file():
            try:
                self.index = pickle.loads(Path(cache).read_bytes())
            except Exception:
                self.index = {}
        if not self.index:
            self._scan()
            if cache:
                Path(cache).write_bytes(pickle.dumps(self.index))
        self.defs = collections.defaultdict(list)             # defined symbol -> [object name]
        for name, e in self.index.items():
            if e['cur'] and not e['stale']:
                for nm, val, sz, typ, bind, ndx in e['syms']:
                    if bind in (0, 1) and 0 < ndx < 0xFF00:
                        self.defs[nm].append(name)

    def _source_sha(self, root, rel):
        if rel not in self._sha:
            try:
                self._sha[rel] = hashlib.sha256((root / rel).read_bytes()).hexdigest()
            except OSError:
                self._sha[rel] = None
        return self._sha[rel]

    def _scan(self):
        root = self.root
        for path in sorted(self.dir.glob('*.o')):
            try:
                e = parse_object(path.read_bytes())
            except Exception:
                continue
            if e is None:
                continue
            receipt = path.with_suffix('.proof.json')
            inputs = []
            if receipt.is_file():
                try:
                    data = json.loads(receipt.read_text())
                except ValueError:
                    data = {}
                inputs = [(k, v) for k, v in (data.get('inputs') or {}).items()
                          if k.endswith(('.c', '.s')) and k.startswith(('src/', 'overlays/'))]
            e['cur'] = [k for k, v in inputs if self._source_sha(root, k) == v]
            e['stale'] = [k for k, v in inputs if self._source_sha(root, k) != v]
            self.index[path.name] = e

    def blob(self, name):
        return (self.dir / name).read_bytes()

    def symbol_bytes(self, name, symbol):
        """(masked data, mask, section index, value) of a defined symbol, relocated fields masked; None when it has no
        bytes."""
        e = self.index[name]
        for nm, val, sz, typ, bind, ndx in e['syms']:
            if nm == symbol and 0 < ndx < 0xFF00:
                _sn, st, off, ssz = e['secs'][ndx]
                if not sz:
                    later = [v for n2, v, s2, t2, b2, n3 in e['syms'] if n3 == ndx and v > val]
                    sz = (min(later) if later else ssz) - val
                if st == 8 or sz <= 0:
                    return None
                blob = self.blob(name)
                data = bytearray(blob[off + val:off + val + sz])
                mask = bytearray(b'\xff' * sz)
                for ro, rt, _rs in e['rels'].get(ndx, ()):
                    if val <= ro < val + sz:
                        for k, m in enumerate(MASK.get(rt, (0, 0, 0, 0))):
                            if ro - val + k < sz:
                                mask[ro - val + k] &= m
                return bytes(data), bytes(mask), ndx, val
        return None


class Containers:
    """The retail containers, read at run time and never copied anywhere."""

    def __init__(self, directory):
        self.dir = Path(directory)
        self._bytes = {}

    def get(self, container):
        if container not in self._bytes:
            self._bytes[container] = (self.dir / CONTAINER_FILES[container]).read_bytes()
        return self._bytes[container]

    def matches(self, container, offset, data, mask):
        blob = self.get(container)
        if offset < 0 or offset + len(data) > len(blob):
            return False
        window = blob[offset:offset + len(data)]
        return all((window[i] & mask[i]) == (data[i] & mask[i]) for i in range(len(data)))

    def word(self, container, offset):
        blob = self.get(container)
        return struct.unpack_from('<I', blob, offset)[0] if 0 <= offset and offset + 4 <= len(blob) else None


def masked_digest(data, mask):
    return hashlib.sha256(bytes(d & m for d, m in zip(data, mask))).hexdigest()


# ---------------------------------------------------------------- the oracle

class Oracle:
    def __init__(self, root, objects, containers, geometry=None, sources=None):
        self.root = Path(root)
        self.objects = objects
        self.containers = containers
        self.geometry = geometry or N.Geometry(self.root)
        self.sources = sources or N.Sources(self.root, self.geometry.rows)
        self.path_homes = collections.defaultdict(set)
        for rid, r in self.geometry.rows.items():
            if r.get('source_row') or r.get('foff') is None or r.get('container') not in N.LOAD_CONTAINERS:
                continue
            for path in self.sources.paths_of(rid):
                self.path_homes[path].add(rid)
            self.path_homes['src/%s/%s.c' % (r['container'], r.get('func'))].add(rid)
        self._placements_of = collections.defaultdict(list)
        for p in self.geometry.images.placements:
            self._placements_of[p.home].append(p)

    # -- functions
    def defining_objects(self, old, new):
        """[(object, defining .c sources, masked bytes tuple)] for the current objects of the old symbol."""
        out = []
        for name in self.objects.defs.get(old, ()):
            e = self.objects.index[name]
            if not any(s[0] == old and s[3] == 2 for s in e['syms']):
                continue
            defined = [p for p in e['cur'] if p.endswith('.c') and (self.sources.definitions(p) or (set(),))[0] & {new, old}]
            if defined:
                sb = self.objects.symbol_bytes(name, old)
                if sb and len(sb[0]) >= MIN_FUNCTION_BYTES:
                    out.append((name, defined, sb))
        return out

    def images_of(self, location):
        return sorted(im.name for im in self.geometry.images.with_foff(location.container, location.offset))

    def function_keys(self, address, old, new):
        """One row's result: {'status': 'keyed' | 'refused', 'reason', 'keys': [Location], 'detail': {...}}."""
        objs = self.defining_objects(old, new)
        if not objs:
            return dict(status='refused', reason='no_current_object', keys=[], detail={})
        sources = sorted({p for _n, ds, _sb in objs for p in ds})
        keys, unkeyed, nohome = {}, [], []
        for path in sources:
            homes = self.path_homes.get(path, set())
            if not homes:
                nohome.append(path)
                continue
            got = False
            for hid in sorted(homes):
                home = self.geometry.rows[hid]
                base = self.geometry.base_of(home)
                if base is None or not base <= address < base + (home.get('size') or 0):
                    continue
                loc = N.Location(home['container'], home['foff'] + (address - base))
                for name, ds, sb in objs:
                    if path in ds and self.containers.matches(loc.container, loc.offset, sb[0], sb[1]):
                        entry = keys.setdefault(loc, dict(home=hid, objects=set(), size=len(sb[0]),
                                                          sha256=masked_digest(sb[0], sb[1])))
                        entry['objects'].add(name)
                        got = True
            if not got:
                unkeyed.append(path)
        detail = dict(keys={str(k): dict(home=v['home'], size=v['size'], sha256=v['sha256'],
                                         objects=len(v['objects'])) for k, v in sorted(keys.items())},
                      sources=sources, unkeyed=unkeyed, no_home=nohome)
        if nohome:
            return dict(status='refused', reason='source_without_home_row', keys=[], detail=detail)
        if unkeyed:
            return dict(status='refused', reason='source_without_key', keys=sorted(keys), detail=detail)
        if not keys:
            return dict(status='refused', reason='no_aligned_bytes', keys=[], detail=detail)
        per_image = collections.Counter(im for loc in keys for im in self.images_of(loc))
        if any(n > 1 for n in per_image.values()):
            return dict(status='refused', reason='two_locations_in_one_image', keys=sorted(keys), detail=detail)
        return dict(status='keyed', reason='', keys=sorted(keys), detail=detail)

    # -- data
    def _function_refs(self, symbol):
        """Decoded HI16/LO16 pairs against `symbol` inside the functions of current objects:
        [(object, function name, function value, hi offset, lo offset, section, object's pair value)]."""
        out = []
        for name, e in self.objects.index.items():
            if not e['cur'] or e['stale'] or not any(s[0] == symbol for s in e['syms']):
                continue
            funcs = collections.defaultdict(list)
            for nm, val, sz, typ, bind, ndx in e['syms']:
                if typ == 2 and 0 < ndx < 0xFF00:
                    funcs[ndx].append((val, sz, nm))
            blob = self.objects.blob(name)
            for ndx, rels in e['rels'].items():
                last_hi = {}
                for ro, rt, rs in rels:
                    if rs >= len(e['syms']):
                        continue
                    if rt == R_HI16:
                        last_hi[rs] = ro
                    elif rt == R_LO16 and e['syms'][rs][0] == symbol and rs in last_hi:
                        owner = [f for f in funcs.get(ndx, ()) if f[0] <= ro < f[0] + max(f[1], 1)]
                        if owner:
                            soff = e['secs'][ndx][2]
                            hi = struct.unpack_from('<I', blob, soff + last_hi[rs])[0] & 0xFFFF
                            lo = struct.unpack_from('<I', blob, soff + ro)[0] & 0xFFFF
                            pair = (hi << 16) + (lo - 0x10000 if lo & 0x8000 else lo)
                            out.append((name, owner[0][2], owner[0][0], last_hi[rs] - owner[0][0], ro - owner[0][0],
                                        ndx, pair))
        return out

    def data_evidence(self, address, old, new):
        """{Location: {'reference': n, 'definition': n, 'resident': bool}} for the locations bytes show, plus a list
        of reference items that did not decode (kind, count)."""
        found = collections.defaultdict(lambda: dict(reference=0, definition=0, resident=False))
        undecoded = collections.Counter()
        for name, fname, fval, hi_off, lo_off, ndx, pair in self._function_refs(old):
            e = self.objects.index[name]
            srcs = [p for p in e['cur'] if p.endswith('.c')]
            if not any(new in (self.sources.definitions(p) or (set(),))[0] or self._spells(p, new) for p in srcs):
                undecoded['not_spelled_by_the_object_sources'] += 1
                continue
            homes = [(hid, self.geometry.base_of(self.geometry.rows[hid])) for p in srcs for hid in self.path_homes.get(p, ())]
            homes = [(h, b) for h, b in homes if b is not None and fname.startswith('func_')
                     and b <= int(fname[5:], 16) < b + (self.geometry.rows[h].get('size') or 0)]
            if not homes:
                undecoded['no_home'] += 1
                continue
            entry_address = int(fname[5:], 16)
            for hid, base in homes:
                placements = self._placements_of.get(hid, []) or [N.Placement(hid, hid, self.geometry.rows[hid]['container'],
                                                                             self.geometry.rows[hid]['foff'], base,
                                                                             self.geometry.rows[hid].get('size') or 0, '', 0)]
                for p in placements:
                    if p.body_offset:
                        undecoded['body_offset'] += 1
                        continue
                    site = p.foff + (entry_address - base)
                    hi, lo = self.containers.word(p.container, site + hi_off), self.containers.word(p.container, site + lo_off)
                    if hi is None or lo is None:
                        undecoded['outside'] += 1
                        continue
                    lo16 = lo & 0xFFFF
                    ahl = ((hi & 0xFFFF) << 16) + (lo16 - 0x10000 if lo16 & 0x8000 else lo16)
                    if (ahl - pair) & 0xFFFFFFFF != address:
                        undecoded['rebound'] += 1
                        continue
                    loc_off = p.foff + (address - p.vma)
                    if any(im.delta == p.vma - p.foff and im.has_foff(loc_off)
                           for im in self.geometry.images.with_foff(p.container, p.foff)):
                        found[N.Location(p.container, loc_off)]['reference'] += 1
                    elif ENGINE_BAND[0] <= address < ENGINE_BAND[1] and not ENGINE_BAND[0] <= p.vma < ENGINE_BAND[1]:
                        spans = {im.location(address) for im in self.geometry.images.at_vma(address)
                                 if im.container == p.container}
                        if len(spans) == 1:
                            loc = spans.pop()
                            found[loc]['reference'] += 1
                            found[loc]['resident'] = True
                        else:
                            undecoded['resident_ambiguous'] += 1
                    else:
                        undecoded['slot'] += 1
        for name in self.objects.defs.get(old, ()):
            e = self.objects.index[name]
            srcs = [p for p in e['cur'] if p.endswith('.c') and self._spells(p, new)]
            sb = self.objects.symbol_bytes(name, old) if srcs else None
            if not sb or not any(sb[1]):
                continue
            for p in srcs:
                for hid in self.path_homes.get(p, ()):
                    base = self.geometry.base_of(self.geometry.rows[hid])
                    if base is None:
                        continue
                    for pl in self._placements_of.get(hid, []):
                        loc_off = pl.foff + (address - pl.vma)
                        if self.containers.matches(pl.container, loc_off, sb[0], sb[1]) and any(
                                im.delta == pl.vma - pl.foff and im.has_foff(loc_off)
                                for im in self.geometry.images.with_foff(pl.container, pl.foff)):
                            found[N.Location(pl.container, loc_off)]['definition'] += 1
        return dict(found), dict(undecoded)

    def _spells(self, path, name):
        try:
            return name in (self.root / path).read_text(errors='replace')
        except OSError:
            return False

    def data_keys(self, address, old, new):
        found, undecoded = self.data_evidence(address, old, new)
        keys = sorted(found)
        detail = dict(keys={str(k): dict(v) for k, v in sorted(found.items())}, undecoded=undecoded)
        if not keys:
            return dict(status='refused', reason='no_proven_location', keys=[], detail=detail)
        return dict(status='keyed', reason='', keys=keys, detail=detail)

    def keys(self, address, old, new):
        return self.data_keys(address, old, new) if old.startswith('D_') else self.function_keys(address, old, new)


def location_collisions(results):
    """{location: names} for locations that two function names (or two data names) claim: [(row key, ...)] results are
    {(address, old, new): result}; every claimant of a collided location is refused by the caller."""
    claims = collections.defaultdict(set)
    for (address, old, new), res in results.items():
        if res['status'] == 'keyed':
            for loc in res['keys']:
                claims[loc].add((old.startswith('D_'), new))
    return {loc: sorted(n for _d, n in who) for loc, who in claims.items() if len({n for _d, n in who}) > 1}


# ---------------------------------------------------------------- batches

def read_batch(path):
    rows = []
    with open(path) as fh:
        header = fh.readline()
        for line in fh:
            cols = line.rstrip('\n').split('\t')
            if len(cols) >= 4 and cols[0].startswith('0x'):
                rows.append(dict(addr=int(cols[0], 16), old=cols[1], new=cols[2],
                                 scope=N.parse_scope(cols[3]) if cols[3] else ()))
    return rows


def open_oracle(args):
    root = Path(args.root)
    objects = Objects(args.obj or root / 'build/obj', root, args.index_cache)
    containers = Containers(args.containers or root / 'work/disc/containers')
    return Oracle(root, objects, containers)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', default=str(Path(__file__).resolve().parents[1]))
    ap.add_argument('--obj', help='object directory (default <root>/build/obj); read only')
    ap.add_argument('--containers', help='retail container directory (default <root>/work/disc/containers); read only')
    ap.add_argument('--index-cache', help='a file to keep the parsed object index in (outside the tree)')
    sub = ap.add_subparsers(dest='cmd', required=True)
    for name in ('functions', 'check', 'data'):
        p = sub.add_parser(name)
        p.add_argument('batch')
        p.add_argument('--out', help='write the report (JSON lines: locations, sizes, digests only)')
    a = ap.parse_args(argv)
    oracle = open_oracle(a)
    rows = read_batch(a.batch)
    results = {}
    for r in rows:
        if (a.cmd == 'data') == r['old'].startswith('D_') or a.cmd == 'check':
            results[(r['addr'], r['old'], r['new'])] = oracle.keys(r['addr'], r['old'], r['new'])
    report = []
    bad = collections.Counter()
    by_key = {(r['addr'], r['old'], r['new']): r for r in rows}
    clash = location_collisions(results)
    for key, res in results.items():
        want = by_key[key]['scope']
        reason = res['reason'] if res['status'] != 'keyed' else ''
        if res['status'] == 'keyed' and any(loc in clash for loc in res['keys']):
            reason = 'location_collision'
        elif res['status'] == 'keyed' and tuple(res['keys']) != tuple(want):
            reason = 'differs_from_batch'
        bad[reason or 'ok'] += 1
        report.append(dict(addr='0x%08X' % key[0], old=key[1], new=key[2], result=reason or 'ok',
                           keys=[str(k) for k in res['keys']], batch=[str(k) for k in want], detail=res['detail']))
    if a.out:
        Path(a.out).write_text(''.join(json.dumps(x, sort_keys=True) + '\n' for x in report))
    print('oracle %s: %s' % (a.cmd, ', '.join('%s %d' % kv for kv in sorted(bad.items()))))
    return 1 if a.cmd == 'check' and set(bad) - {'ok'} else 0


if __name__ == '__main__':
    sys.exit(main())
