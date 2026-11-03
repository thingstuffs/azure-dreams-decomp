#!/usr/bin/env python3
"""Per-placement call binding: which linked function each retail call site really reaches, image by image.

    bind.py [--root R] IMAGE...        print the bound calls of these images as JSON (no codemap needed;
                                       SLUS targets stay `unresolved` here - codemap.py refresh binds them)

A function name is not an identity here: the same `func_<addr>` symbol is defined in many banks (relocated
copies, shared monster code, overlay slots), and a placement's relocations are rebound to other addresses
at link time.  The binding therefore comes from the link itself:

  * `build/.state/link/<tag>/image.map` places every unit object (`<i>.o`, unit i of the image's
    `build/.state/images/<tag>.json`) section by section; the k-th `.text*` input section of unit i is the
    k-th `.text*` section of that unit's recipe object (`build/obj/<recipe>.o`; a rebind renames the
    sections, never reorders them), so every linked function gets its address and recipe symbol;
  * a call site is the caller function's linked address plus the site's offset; the `jal` word read there
    from the linked image (`build/<tag>.bin`, the retail bytes) gives the real target;
  * the target is bound to the function starting there in the caller's own image (`own_image`), else to
    the function starting there in an image of the same container that can be resident with it (no
    address overlap with the caller's image) or in the SLUS (`resident`).  Several candidate bodies at one
    address are `ambiguous` (which bank is loaded is not pinned by the link);
  * a caller linked at a placeholder base below 0x80000000 (check images of rows whose load view is not
    registered) makes its `jal` carry the wrong upper nibble: the target is retried in KSEG0 (`nibble_*`);
  * a target inside a recorded load region (`ledger/instance_load_regions.jsonl`, `config/link/*/*.json`
    headers) that holds the caller is the function at that region's file offset, even when its unit is linked
    at another (placeholder) address (`placeholder_base`: the devkit programs of MAIN/TOWN, whose rows keep
    0x8001xxxx ids but run at 0x80400000 / 0x80700000);
  * a target inside a SLUS function or data span that starts no function is `slus_interior` (callee = the
    containing SLUS symbol, no recipe): the caller was linked against another SLUS build;
  nothing there is `unresolved`.
SLUS callers bind by symbol inside the SLUS (`slus_symbol`; SLUS names are unique there).
"""
from __future__ import annotations

import argparse
import bisect
import json
from pathlib import Path
import re
import struct
import sys

HERE = Path(__file__).resolve()
sys.path.insert(0, str(HERE.parents[1] / 'build'))
import affected as A    # noqa: E402  (ELF reader)

PIECE = re.compile(r'^(\.\S+)\s+0x([0-9a-f]+)\s+0x([0-9a-f]+) load address 0x([0-9a-f]+)', re.M)
INPUT = re.compile(r'^ (\.text\S*)\s+0x([0-9a-f]+)\s+0x([0-9a-f]+) (\S+)$', re.M)
UNIT = re.compile(r'/(\d+)\.o$')


def parse_map(text):
    """(pieces [(vma, size, lma)], text inputs [(section, addr, size, unit index or object path)])."""
    cut = text.find('Linker script and memory map')
    body = text[cut:] if cut >= 0 else text
    pieces = [(int(v, 16), int(s, 16), int(l, 16)) for _, v, s, l in PIECE.findall(body)]
    inputs = []
    for name, addr, size, obj in INPUT.findall(body):
        m = UNIT.search(obj)
        inputs.append((name, int(addr, 16), int(size, 16), int(m[1]) if m else obj))
    return pieces, inputs


def text_functions(blob):
    """Ordered `.text*` sections of an object: [(section, [(symbol, value, size)])]."""
    sections, cstr = A._elf_sections(blob)
    facts = A.elf_facts(blob)
    by_index = {}
    for sym in facts['symbols']:
        if sym['type'] == 2 and sym['name']:
            by_index.setdefault(sym['shndx'], []).append((sym['name'], sym['value'], sym['size']))
    return [(s['name'], sorted(by_index.get(s['index'], []), key=lambda x: x[1]))
            for s in sections if s['name'].startswith('.text') and s['type'] == 1]


def jal_target(word, site):
    if word >> 26 != 3:
        return None
    return ((site + 4) & 0xF0000000) | ((word & 0x03FFFFFF) << 2)


class ImageLayout:
    """Linked functions of one image: address -> (recipe, symbol, size), plus its occupied ranges."""

    def __init__(self, name, tag, units, map_text, binary, objects, unit_offsets=None):
        self.name, self.tag = name, tag
        self.container = name.split('/')[0]
        pieces, inputs = parse_map(map_text)
        self.pieces = pieces
        self.binary = binary
        self.functions = {}            # address -> (recipe, symbol, size)
        self.located = {}              # (recipe, symbol) -> linked address of its section start
        self.offsets = {}              # container file offset -> linked function address (unit_offsets given)
        self.errors = []
        seen = {}
        unit_base = {}
        for section, addr, size, unit in inputs:
            if not isinstance(unit, int) or unit >= len(units):
                continue
            # C units link `.text.*` (per-function sections), assembly units their plain `.text`.
            plain = section == '.text'
            k = seen.get((unit, plain), 0)
            seen[(unit, plain)] = k + 1
            rid = units[unit]
            layout = objects(rid)
            mine = [x for x in layout or () if (x[0] == '.text') == plain]
            if k >= len(mine):
                self.errors.append('unit %d: no section %d in %s' % (unit, k, rid))
                continue
            unit_base.setdefault(unit, addr)
            for symbol, value, fsize in mine[k][1]:
                self.functions[addr + value] = (rid, symbol, fsize)
                self.located.setdefault((rid, symbol), addr)
                if unit_offsets and unit_offsets[unit] is not None:
                    self.offsets[unit_offsets[unit] + addr + value - unit_base[unit]] = addr + value
        self.address_offset = {a: o for o, a in self.offsets.items()}
        self._offset_starts = sorted(self.address_offset)
        self._starts = None

    def file_offset(self, address):
        """Container file offset of a linked address inside one of this image's functions (None if unknown)."""
        i = bisect.bisect_right(self._offset_starts, address) - 1
        if i >= 0:
            start = self._offset_starts[i]
            rid, symbol, size = self.functions[start]
            if address < start + max(size, 4):
                return self.address_offset[start] + address - start
        return None

    def containing(self, address):
        """(start, (recipe, symbol, size)) of the linked function whose extent holds `address`, else None."""
        if self._starts is None:
            self._starts = sorted(self.functions)
        i = bisect.bisect_right(self._starts, address) - 1
        if i >= 0:
            start = self._starts[i]
            if address < start + max(self.functions[start][2], 4):
                return start, self.functions[start]
        return None

    def ranges(self):
        return [(v, v + s) for v, s, _ in self.pieces if s]

    def overlaps(self, other):
        a = sorted(self.ranges())
        b = sorted(other.ranges())
        i = j = 0
        while i < len(a) and j < len(b):
            if a[i][0] < b[j][1] and b[j][0] < a[i][1]:
                return True
            if a[i][1] <= b[j][1]:
                i += 1
            else:
                j += 1
        return False

    def word_at(self, address):
        for vma, size, lma in self.pieces:
            if vma <= address < vma + size:
                off = lma + address - vma
                if off + 4 <= len(self.binary):
                    return struct.unpack_from('<I', self.binary, off)[0]
        return None


class Binder:
    """Bind retail call sites of every image (see the module docstring)."""

    def __init__(self, images, slus=None, regions=None, slus_spans=None):
        self.images = images                    # name -> ImageLayout
        self.slus = slus or {}                  # address -> (recipe, symbol, size) of the SLUS
        self.regions = regions or []            # [(container, file offset, size, base address)]
        self.slus_spans = sorted(slus_spans or [])   # [(start, size, symbol)] of every SLUS function/data symbol
        self.by_address = {}
        self.by_offset = {}                     # (container, file offset) -> [(layout, fn, linked address)]
        self._overlap = {}                      # layouts are fixed for this binder's lifetime
        for layout in images.values():
            for address, fn in layout.functions.items():
                self.by_address.setdefault(address, []).append((layout, fn))
            for off, address in layout.offsets.items():
                self.by_offset.setdefault((layout.container, off), []).append(
                    (layout, layout.functions[address], address))

    def _overlaps(self, layout, other):
        key = (layout, other) if id(layout) < id(other) else (other, layout)
        if key not in self._overlap:
            self._overlap[key] = layout.overlaps(other)
        return self._overlap[key]

    def bind(self, layout, caller_recipe, caller, offset):
        """[(target, callee_image, callee_recipe, callee_symbol, how)] for one call site in one image."""
        start = layout.located.get((caller_recipe, caller))
        if start is None:
            return [(None, None, None, None, 'caller_not_linked')]
        site = start + offset          # abi offsets are section-relative
        word = layout.word_at(site)
        target = jal_target(word, site) if word is not None else None
        if target is None:
            return [(None, None, None, None, 'not_jal')]
        prefix = ''
        found = self._direct(layout, target, prefix)
        if found is None and site >> 28 != 8 and target >> 28 != 8:
            # Placeholder link base below KSEG0: the jal keeps the low 28 bits of the real target.
            target, prefix = (target & 0x0FFFFFFF) | 0x80000000, 'nibble_'
            found = self._direct(layout, target, prefix)
        if found is None:
            found = self._placeholder(layout, site, target) or self._image_interior(layout, target) \
                or self._slus_interior(target)
            if found and prefix:
                found = [x[:4] + (prefix + x[4],) for x in found]
        return found or [(target, None, None, None, prefix + 'unresolved')]

    def bind_resident_caller(self, target, real=None):
        """Bindings of a SLUS call (the SLUS is resident under every overlay): every overlay image whose function
        starts at the target (`overlay_entry`, one row per (recipe, symbol); `real` limits the images), else the SLUS
        span there (`slus_asm` / `slus_interior`), else the overlay functions whose extent holds it
        (`overlay_interior`: the SLUS was linked against another overlay build), else `unresolved`."""
        seen = {}
        for other, fn in self.by_address.get(target, ()):
            if real is None or other.name in real:
                seen.setdefault((fn[0], fn[1]), (target, other.name, fn[0], fn[1], 'overlay_entry'))
        if seen:
            return list(seen.values())
        found = self._slus_interior(target)
        if found:
            return found
        inside = {}
        for other in self.images.values():
            if real is not None and other.name not in real:
                continue
            hit = other.containing(target)
            if hit is not None:
                start, (rid, symbol, size) = hit
                inside.setdefault((rid, symbol), (target, other.name, rid, '%s+0x%X' % (symbol, target - start),
                                                  'overlay_interior'))
        return list(inside.values()) or [(target, None, None, None, 'unresolved')]

    def _direct(self, layout, target, prefix):
        own = layout.functions.get(target)
        if own is not None:
            return [(target, layout.name, own[0], own[1], prefix + 'own_image')]
        cands = [(other.name, fn) for other, fn in self.by_address.get(target, ())
                 if other is not layout and other.container == layout.container and not self._overlaps(layout, other)]
        if target in self.slus:
            cands.append(('slus/slus_bin', self.slus[target]))
        if not cands:
            return None
        how = 'resident' if len({(fn[0], fn[1]) for _, fn in cands}) == 1 else 'ambiguous'
        return [(target, name, fn[0], fn[1], prefix + how) for name, fn in cands]

    def _placeholder(self, layout, site, target):
        """The function at the target's file offset in the caller's own load region, linked elsewhere."""
        here = layout.file_offset(site)
        if here is None:
            return None
        for container, foff, size, base in self.regions:
            if container != layout.container or not (foff <= here < foff + size and base <= target < base + size):
                continue
            hits = self.by_offset.get((container, foff + target - base), ())
            if hits:
                own = [h for h in hits if h[0] is layout] or hits
                seen = {}
                for other, fn, address in own:
                    seen.setdefault((fn[0], fn[1]), (target, other.name, fn[0], fn[1], 'placeholder_base'))
                return list(seen.values())
        return None

    def _image_interior(self, layout, target):
        """The inside of a function of the caller's image or of a same-container image that can be resident with
        it (`image_interior`; one row per containing function): the caller was linked against another build."""
        out = []
        for other in [layout] + [o for o in self.images.values() if o is not layout and o.container == layout.container
                                 and not self._overlaps(layout, o)]:
            hit = other.containing(target)
            if hit is not None:
                start, (rid, symbol, size) = hit
                out.append((target, other.name, rid, '%s+0x%X' % (symbol, target - start), 'image_interior'))
        seen = {}
        for row in out:
            seen.setdefault((row[2], row[3]), row)
        return list(seen.values()) or None

    def _slus_interior(self, target):
        """A SLUS span covering the target: the start of an assembler/library symbol no SLUS recipe defines
        (`slus_asm`), or the inside of a function or data span (`slus_interior`)."""
        i = bisect.bisect_right(self.slus_spans, (target, 1 << 40, '')) - 1
        named = [sp[2] for sp in self.slus_spans[max(0, i - 8):i + 1] if sp[0] == target and ':' not in sp[2]]
        if named:
            return [(target, 'slus/slus_bin', None, named[0], 'slus_asm')]
        while i >= 0:
            start, size, symbol = self.slus_spans[i]
            if start == target:
                return [(target, 'slus/slus_bin', None, symbol, 'slus_asm')]
            if start < target < start + max(size, 4):
                return [(target, 'slus/slus_bin', None, '%s+0x%X' % (symbol, target - start), 'slus_interior')]
            if target - start > 0x40000:
                break
            i -= 1
        return None


def load_layouts(root, image_rows, objects, log=None):
    """{image name: ImageLayout} for (name, tag, output) rows with a link map; unreadable ones skipped."""
    out = {}
    for name, tag, output in image_rows:
        spec_path = root / 'build/.state/images' / (tag + '.json')
        map_path = root / 'build/.state/link' / tag / 'image.map'
        if not spec_path.is_file() or not map_path.is_file() or not (root / output).is_file():
            continue
        spec = json.loads(spec_path.read_text())
        units = [u['recipe'] for u in spec['units']]
        layout = ImageLayout(name, tag, units, map_path.read_text(errors='replace'),
                             (root / output).read_bytes(), objects,
                             unit_offsets=[u.get('off') for u in spec['units']])
        if layout.errors and log:
            log('bind: %s: %s' % (name, layout.errors[0]))
        out[name] = layout
    return out


def slus_functions(root, slus_symbols):
    """{address: (recipe, symbol, size)} from the linked SLUS ELF, for symbols a SLUS recipe defines."""
    elf = root / 'build_slus/build/slus_006.14.elf'
    if not elf.is_file():
        return {}
    facts = A.elf_facts(elf.read_bytes())
    out = {}
    for sym in facts['symbols']:
        if sym['type'] == 2 and sym['name'] in slus_symbols:
            out[sym['value']] = (slus_symbols[sym['name']], sym['name'], sym['size'])
    return out


def load_regions(root):
    """[(container, file offset, size, base)] of every recorded load region and link-list header."""
    out = set()
    path = root / 'ledger/instance_load_regions.jsonl'
    if path.is_file():
        for line in path.read_text().splitlines():
            if line.strip():
                r = json.loads(line)
                out.add((r['container'], int(r['foff']), int(r['size']), int(r['base'])))
    for p in sorted((root / 'config/link').glob('*/*.json')):
        try:
            d = json.loads(p.read_text())
            out.add((d['container'], int(str(d['foff']), 0), int(str(d['size']), 0), int(str(d['vma']), 0)))
        except (ValueError, KeyError, TypeError, AttributeError):
            continue
    return sorted(out)


MAP_INPUT = re.compile(r'^ (\.\S+)\s*\n?\s+0x([0-9a-f]+)\s+0x([0-9a-f]+) (\S+)$', re.M)


def slus_spans(root):
    """[(start, size, symbol)] of every sized SLUS ELF function/object symbol, then every linked input section
    without one (an assembler object's .text, a data blob) named `<object>:<section>` (SLUS interior binding)."""
    elf = root / 'build_slus/build/slus_006.14.elf'
    if not elf.is_file():
        return []
    facts = A.elf_facts(elf.read_bytes())
    spans = {(s['value'], s['size'], s['name']) for s in facts['symbols']
             if s['name'] and s['type'] in (1, 2) and s['size'] and s['value'] >= 0x80000000
             and not s['name'].endswith('.NON_MATCHING')}
    for s in facts['symbols']:          # unsized function labels (PsyQ objects): a start, sized to its section
        if s['name'] and s['type'] == 2 and not s['size'] and s['value'] >= 0x80000000:
            spans.add((s['value'], 4, s['name']))
    mapf = root / 'build_slus/build/slus_006.14.map'
    if mapf.is_file():
        text = mapf.read_text(errors='replace')
        text = text[max(0, text.find('Linker script and memory map')):]
        for section, start, size, obj in MAP_INPUT.findall(text):
            start, size = int(start, 16), int(size, 16)
            if size and start >= 0x80000000:
                spans.add((start, size, '%s:%s' % (Path(obj).stem, section)))
    return sorted(spans)


def slus_symbol_addresses(root):
    """{symbol: address} of every named SLUS ELF function symbol (library and assembler included)."""
    elf = root / 'build_slus/build/slus_006.14.elf'
    if not elf.is_file():
        return {}
    return {s['name']: s['value'] for s in A.elf_facts(elf.read_bytes())['symbols']
            if s['name'] and s['type'] == 2 and s['value'] >= 0x80000000}


def object_sections(root):
    cache = {}

    def get(rid):
        if rid not in cache:
            path = root / 'build/obj' / (rid + '.o')
            try:
                cache[rid] = text_functions(path.read_bytes())
            except (OSError, ValueError, struct.error, IndexError):
                cache[rid] = None
        return cache[rid]
    return get


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('images', nargs='+')
    ap.add_argument('--root', type=Path, default=HERE.parents[2])
    a = ap.parse_args(argv)
    root = a.root.resolve()
    sys.path.insert(0, str(HERE.parent))
    import abi
    g = A.Graph(root)
    rows = [(n, s['tag'], s['output']) for n, s in g.images.items()]
    objects = object_sections(root)
    layouts = load_layouts(root, rows, objects)
    binder = Binder(layouts, regions=load_regions(root), slus_spans=slus_spans(root))
    out = []
    for name in a.images:
        layout = layouts[name]
        for rid in sorted({fn[0] for fn in layout.functions.values()}):
            facts = abi.analyze_object((root / 'build/obj' / (rid + '.o')).read_bytes())
            for c in facts['calls']:
                if c['kind'] != 'call' or c['callee'] == '<indirect>':
                    continue
                for target, image, crid, csym, how in binder.bind(layout, rid, c['caller'], c['offset']):
                    out.append(dict(image=name, caller_recipe=rid, caller=c['caller'], offset=c['offset'],
                                    callee=c['callee'], target=hex(target) if target else None, callee_image=image,
                                    callee_recipe=crid, callee_symbol=csym, how=how, v0_use=c['v0_use']))
    print(json.dumps(out, indent=1))
    return 0


if __name__ == '__main__':
    sys.exit(main())
