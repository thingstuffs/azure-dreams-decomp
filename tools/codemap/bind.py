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
    address are `ambiguous` (which bank is loaded is not pinned by the link); nothing there is
    `unresolved`.
SLUS callers bind by symbol inside the SLUS (`slus_symbol`; SLUS names are unique there).
"""
from __future__ import annotations

import argparse
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

    def __init__(self, name, tag, units, map_text, binary, objects):
        self.name, self.tag = name, tag
        self.container = name.split('/')[0]
        pieces, inputs = parse_map(map_text)
        self.pieces = pieces
        self.binary = binary
        self.functions = {}            # address -> (recipe, symbol, size)
        self.located = {}              # (recipe, symbol) -> linked address of its section start
        self.errors = []
        seen = {}
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
            for symbol, value, fsize in mine[k][1]:
                self.functions[addr + value] = (rid, symbol, fsize)
                self.located.setdefault((rid, symbol), addr)

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

    def __init__(self, images, slus=None):
        self.images = images                    # name -> ImageLayout
        self.slus = slus or {}                  # address -> (recipe, symbol, size) of the SLUS
        self.by_address = {}
        for layout in images.values():
            for address, fn in layout.functions.items():
                self.by_address.setdefault(address, []).append((layout, fn))

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
        own = layout.functions.get(target)
        if own is not None:
            return [(target, layout.name, own[0], own[1], 'own_image')]
        cands = [(other.name, fn) for other, fn in self.by_address.get(target, ())
                 if other is not layout and other.container == layout.container and not layout.overlaps(other)]
        if target in self.slus:
            cands.append(('slus/slus_bin', self.slus[target]))
        if not cands:
            return [(target, None, None, None, 'unresolved')]
        how = 'resident' if len({(fn[0], fn[1]) for _, fn in cands}) == 1 else 'ambiguous'
        return [(target, name, fn[0], fn[1], how) for name, fn in cands]


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
                             (root / output).read_bytes(), objects)
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
    binder = Binder(layouts)
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
