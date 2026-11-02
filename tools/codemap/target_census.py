#!/usr/bin/env python3
"""What an address-named callee really is: resolve every retail call target (and every never-called
address declaration) against all linked images, the SLUS link and the recorded load regions.

    target_census.py [--root R] --names NAMES.tsv --out OUT.tsv [--contexts CTX.tsv]

NAMES.tsv: first column a declared name (func_<addr> / D_<addr> / a case variant), optional second column a
group label.  The census reads build/codemap.db (call_bind, retail_call, image_unit) plus the link maps and
linked images under build/.state/link (bind.py layouts, check images included) and the SLUS ELF/map.

For each (name, caller image) context the target address T is resolved in this order:
  start        a linked function starts at T in some image (own image, a same-container image, another
               container, or the SLUS); C or assembler by the unit kind
  region       T lies in a recorded load region (ledger/instance_load_regions.jsonl, config/link/*/*.json
               headers) whose file offset holds a linked function start in some image of that container,
               i.e. the function is linked at another (placeholder) base
  library      T is inside a Sony library object of the SLUS (asm/psyq/...): an exported entry without a
               symbol, or an interior label
  mid          T is inside a linked function or data span (with containing symbol, delta and the word there)
  nowhere      no image, region or SLUS span covers T
A caller linked below 0x80000000 (placeholder base) gets its jal target's upper nibble corrected to 0x8.
"""
from __future__ import annotations

import argparse
import bisect
import collections
import csv
import json
from pathlib import Path
import re
import sqlite3
import struct
import sys

HERE = Path(__file__).resolve()
TOOLS = HERE.parents[1]
sys.path[:0] = [str(TOOLS / 'codemap'), str(TOOLS / 'build')]
import bind  # noqa: E402
import affected as A  # noqa: E402

ADDR = re.compile(r'^(?:func|D)_([0-9A-Fa-f]{8})$')
MAP_INPUT = re.compile(r'^ (\.\S+)\s*\n?\s+0x([0-9a-f]+)\s+0x([0-9a-f]+) (\S+)$', re.M)


def name_address(name):
    m = ADDR.match(name)
    return int(m[1], 16) if m else None


def word_class(word):
    """Coarse class of one MIPS word: prologue / return / branch-or-jump / zero / other."""
    if word is None:
        return 'none'
    if word == 0:
        return 'nop'
    op = word >> 26
    if op == 9 and (word >> 16) & 0x3FF == (29 << 5 | 29) and word & 0x8000:
        return 'prologue'          # addiu sp, sp, -n
    if word == 0x03E00008:
        return 'jr_ra'
    if op in (2, 3):
        return 'jal' if op == 3 else 'j'
    return 'insn'


def mask_word(w):
    """A word with its relocatable fields cleared (jal/j targets, lui and non-stack imm16)."""
    op = w >> 26
    if op in (2, 3):
        return w & 0xFC000000
    if op == 15:
        return w & 0xFFFF0000
    if op in (8, 9, 13, 32, 33, 34, 35, 36, 37, 38, 40, 41, 42, 43, 46) and (w >> 21) & 31 not in (29, 30):
        return w & 0xFFFF0000
    return w


def masked(blob, off, size):
    """Words with relocatable fields cleared: jal/j targets, lui immediates, and the %lo immediate of an
    instruction whose base register a lui set earlier in the span (struct offsets stay significant)."""
    n = max(0, min(size, len(blob) - off)) // 4
    out, hi = [], set()
    for w in struct.unpack_from('<%dI' % n, blob, off):
        op, rs, rt = w >> 26, (w >> 21) & 31, (w >> 16) & 31
        if op in (2, 3):
            out.append(w & 0xFC000000)
        elif op == 15:
            hi.add(rt)
            out.append(w & 0xFFFF0000)
        elif op in (8, 9, 13, 32, 33, 34, 35, 36, 37, 38, 40, 41, 42, 43, 46) and rs in hi:
            out.append(w & 0xFFFF0000)
            if op in (8, 9, 13) or op < 40:
                hi.discard(rt) if rt != rs else None
        else:
            out.append(w)
    return tuple(out)


class Slus:
    """SLUS symbols, input sections (object paths) and bytes."""

    def __init__(self, root):
        self.ok = False
        elf = root / 'build_slus/build/slus_006.14.elf'
        mapf = root / 'build_slus/build/slus_006.14.map'
        binf = root / 'build_slus/build/slus_006.14'
        if not (elf.is_file() and mapf.is_file() and binf.is_file()):
            return
        facts = A.elf_facts(elf.read_bytes())
        self.funcs = {}
        self.labels = collections.defaultdict(list)
        for s in facts['symbols']:
            if s['name'] and s['type'] == 2 and not s['name'].endswith('.NON_MATCHING'):
                self.funcs.setdefault(s['value'], (s['name'], s['size']))
            elif s['name'] and s['value'] >= 0x80000000:
                self.labels[s['value']].append(s['name'])
        text = mapf.read_text(errors='replace')
        text = text[max(0, text.find('Linker script and memory map')):]
        self.inputs = sorted((int(a, 16), int(z, 16), sec, obj) for sec, a, z, obj in MAP_INPUT.findall(text)
                             if int(z, 16) and int(a, 16) >= 0x80000000)
        self.starts = [x[0] for x in self.inputs]
        self.blob = binf.read_bytes()
        self.t_addr, self.t_size = struct.unpack_from('<II', self.blob, 0x18)
        fs = sorted(self.funcs.items())
        self.fstarts = [a for a, _ in fs]
        self.flist = fs
        self.ok = True

    def word(self, a):
        off = a - self.t_addr + 0x800
        if self.t_addr <= a < self.t_addr + self.t_size and off + 4 <= len(self.blob):
            return struct.unpack_from('<I', self.blob, off)[0]
        return None

    def input_at(self, a):
        i = bisect.bisect_right(self.starts, a) - 1
        while i >= 0:
            b, z, sec, obj = self.inputs[i]
            if b <= a < b + z:
                return self.inputs[i]
            if b + z <= a and i < len(self.inputs) - 1 and self.inputs[i][0] < a - 0x100000:
                break
            i -= 1
            if i >= 0 and self.inputs[i][0] + 0x200000 < a:
                break
        return None

    def func_containing(self, a):
        i = bisect.bisect_right(self.fstarts, a) - 1
        if i >= 0:
            start, (name, size) = self.flist[i]
            if start <= a < start + max(size, 4):
                return start, name, size
        return None

    def end(self):
        return self.t_addr + self.t_size


def load_regions(root):
    """[(container, foff, size, base, label)] from instance load regions and link-list headers."""
    out = []
    path = root / 'ledger/instance_load_regions.jsonl'
    if path.is_file():
        for line in path.read_text().splitlines():
            if line.strip():
                r = json.loads(line)
                out.append((r['container'], int(r['foff']), int(r['size']), int(r['base']), r.get('method', '')))
    for p in sorted((root / 'config/link').glob('*/*.json')):
        try:
            d = json.loads(p.read_text())
        except ValueError:
            continue
        try:
            out.append((d['container'], int(str(d['foff']), 0), int(str(d['size']), 0), int(str(d['vma']), 0),
                        'linklist ' + p.name))
        except (KeyError, TypeError, ValueError):
            continue
    return out


class World:
    def __init__(self, root, db):
        self.root, self.db = root, db
        self.images = {n: dict(tag=t, output=o, kind=k, start=s, size=z, vma=v)
                       for n, t, o, k, s, z, v in db.execute('SELECT name, tag, output, kind, start, size, vma FROM image')}
        self.units = collections.defaultdict(list)       # image -> unit dicts
        for img, idx, rec, func, kind, off, size, vma, rows in db.execute(
                'SELECT image, idx, recipe, func, kind, off, size, vma, rows FROM image_unit'):
            self.units[img].append(dict(idx=idx, recipe=rec, func=func, kind=kind, off=off, size=size, vma=vma,
                                        rows=json.loads(rows or '[]')))
        rows = [(n, s['tag'], s['output']) for n, s in self.images.items() if s['kind'] != 'slus']
        self.layouts = bind.load_layouts(root, rows, bind.object_sections(root))
        self.slus = Slus(root)
        self.regions = load_regions(root)
        self.containers = {}
        for name, spec in self.images.items():
            cont = name.split('/')[0]
            if cont in self.containers or spec['kind'] != 'image':
                continue
            try:
                ispec = json.loads((root / 'build/.state/images' / (spec['tag'] + '.json')).read_text())
                self.containers[cont] = (root / ispec['container']).read_bytes()
            except (OSError, KeyError, ValueError):
                pass
        self._clones = None
        self.slus_files = set()
        for (src,) in db.execute("SELECT physical FROM recipe WHERE family = 'slus'"):
            self.slus_files.add(src)
        # every linked function start: address -> [(image, recipe, symbol, size, kind)]
        self.starts = collections.defaultdict(list)
        # container file offset -> [(image, recipe, symbol, address)]
        self.by_off = collections.defaultdict(list)
        self.spans = collections.defaultdict(list)       # image -> sorted [(addr, size, recipe, symbol)]
        for name, lay in self.layouts.items():
            kinds = {u['recipe']: u for u in self.units[name]}
            container = name.split('/')[0]
            for addr, (rid, sym, size) in lay.functions.items():
                u = kinds.get(rid)
                kind = u['kind'] if u else '?'
                self.starts[addr].append((name, rid, sym, size, kind))
                self.spans[name].append((addr, size, rid, sym))
            for off, addr in lay.offsets.items():          # per-unit container offsets (bind.ImageLayout)
                rid, sym, size = lay.functions[addr]
                u = kinds.get(rid)
                self.by_off[(container, off)].append((name, rid, sym, addr, u['kind'] if u else '?'))
            self.spans[name].sort()

    def user_images(self, name):
        """[(image, rows)] of the recipes whose sources declare or use `name` (one per container, real first)."""
        files = {f for (f,) in self.db.execute('SELECT DISTINCT file FROM decl WHERE name = ?', (name,))}
        files |= {f for (f,) in self.db.execute('SELECT DISTINCT tu FROM decl WHERE name = ?', (name,))}
        recs = set()
        for f in files:
            recs |= {r for (r,) in self.db.execute('SELECT id FROM recipe WHERE source = ? OR physical = ?', (f, f))}
            recs |= {r for (r,) in self.db.execute('SELECT recipe FROM tu_dep WHERE path = ?', (f,))}
        out, seen = [], set()
        for img in sorted(self.units, key=lambda i: (not self.real(i), i)):
            for u in self.units[img]:
                if u['recipe'] in recs:
                    key = (img.split('/')[0], self.real(img))
                    if key not in seen:
                        seen.add(key)
                        out.append((img, u['rows']))
        if not out and files & self.slus_files:
            out.append(('slus/slus_bin', []))
        return out

    def clone_of(self, cont, off, min_words=6):
        """(image, symbol) of a linked C unit whose masked words equal the code at container offset `off`."""
        if self._clones is None:
            self._clones = collections.defaultdict(list)
            for img, units in self.units.items():
                c = img.split('/')[0]
                blob = self.containers.get(c)
                if blob is None:
                    continue
                for u in units:
                    if u['kind'] != 'c' or u['off'] is None or not u['size'] or u['size'] < 4 * min_words:
                        continue
                    ws = masked(blob, u['off'], u['size'])
                    self._clones[ws[:min_words]].append((img, u['func'], ws))
        blob = self.containers.get(cont)
        if blob is None:
            return None
        head = masked(blob, off, 4 * min_words)
        for img, func, ws in self._clones.get(head, ()):
            if masked(blob, off, 4 * len(ws)) == ws:
                return (img, func)
        return None

    def rows_of(self, image, recipe):
        for u in self.units.get(image, ()):
            if u['recipe'] == recipe:
                return u['rows']
        return []

    def containing(self, image, a):
        sp = self.spans.get(image, ())
        i = bisect.bisect_right(sp, (a, 1 << 40)) - 1
        if i >= 0 and sp[i][0] <= a < sp[i][0] + max(sp[i][1], 4):
            return sp[i]
        return None

    def word(self, image, a):
        lay = self.layouts.get(image)
        return lay.word_at(a) if lay else None

    def real(self, image):
        return self.images.get(image, {}).get('kind') == 'image'

    def resolve(self, target, caller_image=None, caller_off=None):
        """List of evidence dicts for target T seen from caller_image (may be None)."""
        ev = []
        container = caller_image.split('/')[0] if caller_image else None
        for img, rid, sym, size, kind in self.starts.get(target, ()):
            if img == caller_image:
                scope = 'own_image'
            elif img.split('/')[0] == container:
                scope = 'same_container'
            else:
                scope = 'other_container'
            ev.append(dict(cls='start', scope=scope, image=img, recipe=rid, symbol=sym, kind=kind,
                           rows=self.rows_of(img, rid), real=self.real(img)))
        if self.slus.ok and target in self.slus.funcs:
            sym, size = self.slus.funcs[target]
            inp = self.slus.input_at(target)
            obj = inp[3] if inp else '?'
            ev.append(dict(cls='start', scope='slus', image='slus/slus_bin', symbol=sym, object=obj,
                           kind='library' if '/psyq/' in obj else ('asm' if '/asm/' in obj else 'c')))
        regions = self.regions
        if caller_off is not None and container:
            # The caller's own program first: a region that holds the caller and covers the target.
            own = [r for r in regions if r[0] == container and r[1] <= caller_off < r[1] + r[2]
                   and r[3] <= target < r[3] + r[2]]
            if own:
                regions = own
        for cont, foff, size, base, label in regions:
            if base <= target < base + size and (container is None or cont == container or cont == 'main'
                                                 or container == 'slus'):
                off = foff + target - base
                for img, rid, sym, addr, kind in self.by_off.get((cont, off), ()):
                    if addr == target:
                        continue
                    ev.append(dict(cls='region', scope=cont, image=img, recipe=rid, symbol=sym, kind=kind,
                                   linked_at=hex(addr), off=hex(off), region='%s@%s' % (hex(foff), hex(base)),
                                   rows=self.rows_of(img, rid), real=self.real(img)))
                if not any(e['cls'] == 'region' and e.get('off') == hex(off) for e in ev) and \
                        not any(e['cls'] == 'start' and e['image'].split('/')[0] == cont for e in ev):
                    ev.append(dict(cls='region_gap', scope=cont, off=hex(off), region='%s@%s' % (hex(foff), hex(base)),
                                   label=label[:40]))
        if not any(e['cls'] == 'start' for e in ev):
            # SLUS spans: resident under every overlay
            if self.slus.ok and self.slus.t_addr <= target < self.slus.end():
                inp = self.slus.input_at(target)
                fn = self.slus.func_containing(target)
                w = self.slus.word(target)
                d = dict(cls='mid', scope='slus', word=hex(w) if w is not None else None, wclass=word_class(w))
                if inp:
                    d.update(section=inp[2], object=inp[3], delta=hex(target - inp[0]))
                    if '/psyq/' in inp[3]:
                        d['cls'] = 'library'
                if fn:
                    d.update(symbol=fn[1], fdelta=hex(target - fn[0]))
                labels = self.slus.labels.get(target)
                if labels:
                    d['labels'] = labels[:3]
                ev.append(d)
            # every image of the caller's container that covers T
            seen = set()
            for img in self.layouts:
                if container and img.split('/')[0] != container:
                    continue
                c = self.containing(img, target)
                if c and (c[2], c[3]) not in seen:
                    seen.add((c[2], c[3]))
                    w = self.word(img, target)
                    ev.append(dict(cls='mid', scope=img, recipe=c[2], symbol=c[3], fdelta=hex(target - c[0]),
                                   word=hex(w) if w is not None else None, wclass=word_class(w),
                                   real=self.real(img)))
        if not ev:
            ev.append(dict(cls='nowhere'))
        return ev



# ---------------------------------------------------------------- classification
STUB = {0xA0: 'A', 0xB0: 'B', 0xC0: 'C'}


def bios_stub(world, image, target, slus_word=None):
    """'B(5Ch)' when the words at target are a PsyQ BIOS call stub (li t2,0xA0/B0/C0; jr t2; li t1,n)."""
    lay = world.layouts.get(image) if image else None
    words = [lay.word_at(target + 4 * k) if lay else None for k in range(3)]
    if words[0] is None:
        return None
    if words[0] >> 16 == 0x240A and (words[0] & 0xFFFF) in STUB and words[1] == 0x01400008 \
            and words[2] >> 16 == 0x2409:
        return '%s(%02Xh)' % (STUB[words[0] & 0xFFFF], words[2] & 0xFFFF)
    return None


def container_word(world, cont, off):
    blob = world.containers.get(cont)
    if blob is None or off + 4 > len(blob):
        return None
    return struct.unpack_from('<I', blob, off)[0]


def classify(world, name, rows, readable):
    """(class, detail) for one name from its census rows (dicts with caller_image, target, evidence)."""
    best = None
    rank = ['LIB', 'C_SAME', 'C_REBOUND', 'C_COPY', 'C_PLACEHOLDER', 'DEV_LIB', 'DEV_COPY', 'MISSING', 'C_STALE_ROW',
            'C_OTHER_CONTAINER', 'LIB_INTERIOR', 'FOREIGN_SLUS', 'FOREIGN_IMAGE', 'NOWHERE']
    for r in rows:
        ev = r['evidence']
        cont = r['caller_image'].split('/')[0] if r['caller_image'] else None
        t = int(r['target'], 16)
        got = None
        starts = [e for e in ev if e['cls'] == 'start']
        slus = [e for e in starts if e['scope'] == 'slus']
        same = [e for e in starts if e['scope'] in ('own_image', 'same_container') and e.get('real')]
        if cont == 'slus':
            same = [e for e in starts if e.get('real')]
        if slus and slus[0]['kind'] == 'library':
            got = ('LIB', '%s (%s)' % (slus[0]['symbol'], slus[0]['object'].split('build/')[-1]))
        elif slus:
            got = ('C_SAME', 'slus %s -> %s' % (slus[0]['symbol'], readable.get(slus[0]['symbol'], slus[0]['symbol'])))
        elif same:
            e = same[0]
            canonical = e['symbol'].startswith('func_') and int(e['symbol'][5:13], 16) == t
            spelled = name_address(name)
            got = ('C_REBOUND' if spelled is not None and spelled != t and canonical else
                   'C_SAME' if canonical else 'C_COPY',
                   '%s %s -> %s rows %s%s' % (e['image'], e['symbol'], readable.get(e['symbol'], e['symbol']),
                                              ','.join(e.get('rows', [])[:2]),
                                              '' if canonical else ' (placement of that home linked at %s)' % hex(t)))
        if got is None:
            reg = [e for e in ev if e['cls'] == 'region' and e.get('real')]
            if reg:
                e = reg[0]
                got = ('C_PLACEHOLDER', '%s linked at %s (row %s, canonical %s); true address %s in region %s' % (
                    e['symbol'], e['linked_at'], ','.join(e.get('rows', [])[:1]), readable.get(e['symbol'], e['symbol']),
                    hex(t), e['region']))
        if got is None:
            gaps = [e for e in ev if e['cls'] == 'region_gap']
            lib = [e for e in ev if e['cls'] == 'library']
            if lib:
                e = lib[0]
                got = ('LIB_INTERIOR', '%s+%s' % (e['object'].split('build/')[-1], e.get('delta')))
            elif gaps and any(e['cls'] == 'mid' and e['scope'] != 'slus' for e in ev) is False:
                e = gaps[0]
                foff, base = (int(x, 16) for x in e['region'].split('@'))
                off = int(e['off'], 16)
                words = [container_word(world, e['scope'], off + 4 * k) for k in range(3)]
                stub = None
                if words[0] is not None and words[0] >> 16 == 0x240A and (words[0] & 0xFFFF) in STUB \
                        and words[1] == 0x01400008 and (words[2] or 0) >> 16 == 0x2409:
                    stub = '%s(%02Xh)' % (STUB[words[0] & 0xFFFF], words[2] & 0xFFFF)
                copy = world.clone_of(e['scope'], off)
                if stub:
                    got = ('DEV_LIB', 'BIOS stub %s at %s off %s' % (stub, hex(t), e['off']))
                elif copy:
                    got = ('DEV_COPY', 'masked copy of %s (%s) at %s off %s' % (copy[1], copy[0], hex(t), e['off']))
                elif word_class(words[0]) == 'prologue':
                    got = ('MISSING', 'function start (addiu sp) at %s off %s in region %s, no C row' % (
                        hex(t), e['off'], e['region']))
                else:
                    got = ('FOREIGN_IMAGE', 'not a function start (%s) at %s off %s in region %s' % (
                        word_class(words[0]), hex(t), e['off'], e['region']))
        if got is None:
            chk = [e for e in starts if not e.get('real') and e['scope'] != 'slus']
            other = [e for e in starts if e.get('real') and e['scope'] == 'other_container']
            mids = [e for e in ev if e['cls'] == 'mid']
            if chk:
                e = chk[0]
                got = ('C_STALE_ROW', '%s rows %s (only in a check image: no registered load view)' % (
                    e['symbol'], ','.join(e.get('rows', [])[:2])))
            elif other:
                e = other[0]
                got = ('C_OTHER_CONTAINER', '%s %s rows %s' % (e['image'], e['symbol'], ','.join(e.get('rows', [])[:2])))
            elif any(e['scope'] == 'slus' for e in mids):
                e = [e for e in mids if e['scope'] == 'slus'][0]
                got = ('FOREIGN_SLUS', 'inside SLUS %s+%s (%s, %s)' % (e.get('symbol'), e.get('fdelta'),
                                                                     e.get('object', '?').split('build/')[-1], e.get('wclass')))
            elif mids:
                e = sorted(mids, key=lambda e: not e.get('real'))[0]
                got = ('FOREIGN_IMAGE', 'inside %s %s+%s (%s)' % (e['scope'], e['symbol'], e['fdelta'], e['wclass']))
            elif any(e['cls'] == 'region_gap' for e in ev):
                e = [e for e in ev if e['cls'] == 'region_gap'][0]
                got = ('FOREIGN_IMAGE', 'uncovered off %s in region %s' % (e['off'], e['region']))
            else:
                got = ('NOWHERE', 'no image, region or SLUS span covers %s' % hex(t))
        if r.get('nibble_fixed'):
            got = (got[0], got[1] + ' [jal target %s: placeholder caller base, nibble corrected]' % r['nibble_fixed'])
        if best is None or rank.index(got[0]) < rank.index(best[0]):
            best = got
    return best or ('NOWHERE', 'no address')


def contexts(db, names):
    """name -> [(caller image, caller recipe, caller, offset, target)] from call_bind joined to retail_call."""
    rc = {}
    for recipe, caller, off, callee in db.execute("SELECT recipe, caller, offset, callee FROM retail_call"):
        if callee in names:
            rc[(recipe, caller, off)] = callee
    out = collections.defaultdict(list)
    for img, crec, caller, off, tgt, cimg, crcp, csym, how in db.execute('SELECT * FROM call_bind'):
        n = rc.get((crec, caller, off))
        if n is not None:
            out[n].append(dict(image=img, recipe=crec, caller=caller, off=off, target=tgt, how=how))
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=HERE.parents[2])
    ap.add_argument('--names', type=Path, required=True)
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--classes', type=Path, help='per-name class table (TSV)')
    a = ap.parse_args(argv)
    root = a.root.resolve()
    db = sqlite3.connect('file:%s?mode=ro' % (root / 'build/codemap.db'), uri=True)
    names = {}
    with a.names.open() as fh:
        for row in csv.reader(fh, delimiter='\t'):
            if row and not row[0].startswith('#') and row[0] != 'name':
                names[row[0]] = row[1] if len(row) > 1 else ''
    world = World(root, db)
    ctx = contexts(db, set(names))
    with a.out.open('w') as fh:
        w = csv.writer(fh, delimiter='\t', lineterminator='\n')
        w.writerow(['name', 'group', 'caller_image', 'caller_rows', 'caller_vma', 'target', 'nibble_fixed', 'evidence'])
        for name in sorted(names):
            cs = ctx.get(name, [])
            seen = set()
            todo = []
            for c in cs:
                t = c['target']
                if t is None:
                    continue
                key = (c['image'], t)
                if key in seen:
                    continue
                seen.add(key)
                lay = world.layouts.get(c['image'])
                cvma = lay.located.get((c['recipe'], c['caller'])) if lay else None
                coff = None
                for u in world.units.get(c['image'], ()):
                    if u['recipe'] == c['recipe'] and u['off'] is not None:
                        coff = u['off']
                todo.append((c['image'], world.rows_of(c['image'], c['recipe']), cvma, t, coff))
            if not todo:
                t = name_address(name)
                if t is not None:
                    imgs = world.user_images(name)
                    for img, rows in imgs or [(None, [])]:
                        todo.append((img, rows, None, t, None))
            for img, rows, cvma, t, coff in todo:
                fixed = ''
                if t < 0x80000000 or (t >> 28) == 0xA:
                    t2 = (t & 0x0FFFFFFF) | 0x80000000
                    fixed, t = hex(t), t2
                ev = world.resolve(t, img, coff)
                w.writerow([name, names[name], img or '', ','.join(rows), hex(cvma) if cvma else '', hex(t), fixed,
                            json.dumps(ev, sort_keys=True)])
    if a.classes:
        readable = readable_names(root)
        per = collections.defaultdict(list)
        with a.out.open() as fh:
            for row in csv.DictReader(fh, delimiter='\t'):
                row['evidence'] = json.loads(row['evidence'])
                per[row['name']].append(row)
        with a.classes.open('w') as fh:
            w = csv.writer(fh, delimiter='\t', lineterminator='\n')
            w.writerow(['name', 'group', 'class', 'callers', 'detail'])
            for name in sorted(names):
                rows = per.get(name, [])
                cls, detail = classify(world, name, rows, readable)
                callers = ','.join(sorted({x for r in rows for x in r['caller_rows'].split(',') if x})[:3])
                w.writerow([name, names[name], cls, callers, detail])
    return 0


def readable_names(root):
    """canonical symbol -> readable name (config/names.tsv)."""
    out = {}
    path = root / 'config/names.tsv'
    if path.is_file():
        for raw in path.read_text(errors='replace').splitlines():
            cols = raw.split('#', 1)[0].rstrip().split('\t')
            if len(cols) >= 3 and cols[1].strip() and cols[2].strip():
                out.setdefault(cols[1].strip(), cols[2].strip())
    return out


if __name__ == '__main__':
    sys.exit(main())
