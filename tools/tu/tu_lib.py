"""Shared geometry and retail-byte evidence for original translation-unit recovery.

Geometry comes only from committed accounting:
  * the one-link image set is tools/link/combined.py's selection (60 town load
    views, every dungeon bank, both engines) plus the SLUS, MAIN and OVMOVIE
    file views - 402 images;
  * each image's complete byte map (link/<container>/<image>.tsv, read through
    tools/byte_map_format.py) gives its extent, VMA and ordered code entries;
  * per image, psylink order is .rdata, .text, .data: the bytes before the first
    code entry are the image's .rdata, the bytes after the last code entry are
    its .data/.sdata (the maps do not distinguish the two) and .bss is not in
    the file;
  * SLUS sections come from config/slus_006.14.yaml (game rodata, game text,
    resident data) and the PS-X EXE header.

Evidence (all re-checkable byte facts):
  J1  two functions loading the same anonymous string literal are one TU, with
      every function between them (a TU's .text is contiguous);
  J2  a TU-private literal (string or jump table) inside the private-literal pool
      interval of a proven group belongs to that TU, and so do its users;
  B1  equal string contents at two addresses lie in two TUs;
  B2  a nonzero .rdata alignment fill ends an object's .rdata block; it maps to a
      text edge through TU-private literals only (strings and jump tables);
  M   pool order equals text order (consistency check, never absorbed).
"""
from __future__ import annotations

import json
import re
import struct
import sys
from collections import defaultdict
from pathlib import Path

CONTAINER_FILES = {
    'main': 'work/disc/containers/MAIN_MAIN.BIN',
    'town': 'work/disc/containers/TOWN_TOWN.BIN',
    'dungeon': 'work/disc/containers/DUNGEON_DUNGEON.BIN',
    'ovmovie': 'work/disc/containers/OVMOVIE.BIN',
    'slus': 'baserom/slus_006.14',
}
FILE_VIEWS = ('slus/slus_bin', 'main/main_bin', 'ovmovie/ovmovie_bin')
# MAIN is one file view holding several load images; analyse the children that
# carry their own VMA.  The 0x21968 run is a partial engine instance whose
# .rdata is not in the file.
MAIN_CHILDREN = ('main/image_25c800', 'main/ll34_269000_80400000')
JR_RA = 0x03E00008
FILE_NAME = re.compile(rb'^[A-Za-z0-9_./\\-]+\.[cChHsS]$')


def num(x):
    if x is None:
        return None
    return int(x, 16) if isinstance(x, str) else int(x)


# ----------------------------------------------------------------- repository

class Repo:
    """Read-only view of the committed accounting a sweep needs."""

    def __init__(self, root):
        self.root = Path(root).resolve()
        sys.path[:0] = [str(self.root / 'tools'), str(self.root / 'tools/link')]
        self._blobs = {}
        self.rows = {}
        for line in open(self.root / 'ledger/rows.jsonl'):
            r = json.loads(line)
            self.rows[r['id']] = r
        self.layout = {}
        for line in open(self.root / 'ledger/layout.jsonl'):
            r = json.loads(line)
            self.layout[r['id']] = r['path']
        self.path_ids = defaultdict(list)
        for i, p in self.layout.items():
            self.path_ids[p].append(i)
        self.inlined = set()
        p = self.root / 'ledger/layout_inline.jsonl'
        if p.exists():
            for line in open(p):
                if line.strip():
                    self.inlined.add(json.loads(line)['member_id'])
        self.module_of = {}
        p = self.root / 'config/overlays/modules.json'
        if p.exists():
            for m in json.loads(p.read_text())['modules']:
                for a in m['members'] + m.get('data_members', []):
                    self.module_of[a['id']] = m['key']
        self.rows_by_container = defaultdict(list)
        for r in self.rows.values():
            if isinstance(r.get('foff'), int) and r.get('row_kind') != 'data':
                self.rows_by_container[r['container']].append(r)
        for v in self.rows_by_container.values():
            v.sort(key=lambda r: r['foff'])
        self.data_rows = defaultdict(dict)
        for r in self.rows.values():
            if r.get('row_kind') == 'data' and isinstance(r.get('foff'), int):
                self.data_rows[r['container']][r['foff']] = r
        self.slus_symbols = {}
        p = self.root / 'config/slus_006.14.symbols.txt'
        if p.exists():
            for line in open(p):
                m = re.match(r'\s*([A-Za-z_][\w.$]*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;(.*)', line)
                if m:
                    self.slus_symbols[int(m[2], 16)] = (m[1], 'func' in m[3])

    def blob(self, container):
        if container not in self._blobs:
            self._blobs[container] = (self.root / CONTAINER_FILES[container]).read_bytes()
        return self._blobs[container]

    def maps(self):
        from byte_map_format import load_documents
        return {d['image']: d for d, _ in load_documents(self.root / 'link', self.root)}

    def one_link_images(self):
        from graph import Graph
        from combined import selected_images
        docs = Graph(self.root / 'config/link_graph').documents()
        return list(FILE_VIEWS) + selected_images(docs)

    def home_path(self, home):
        return self.layout.get(home) or (self.rows.get(home) or {}).get('c_path')


# ------------------------------------------------------------------- geometry

def slus_geometry(root):
    """Game .rdata/.text/.data extents from the splat layout and EXE header."""
    segs = []
    for line in open(Path(root) / 'config/slus_006.14.yaml'):
        m = re.match(r'\s*- \[(0x[0-9a-fA-F]+)(?:,\s*([\w]+))?(?:,\s*([^\]]+))?\]', line)
        if m:
            segs.append((int(m[1], 16), m[2] or '', (m[3] or '').strip()))
    head = (Path(root) / CONTAINER_FILES['slus']).read_bytes()[:0x800]
    load, tsize = struct.unpack_from('<II', head, 0x18)
    gp = None
    for line in open(Path(root) / 'config/slus_006.14.yaml'):
        m = re.match(r'\s*gp_value:\s*(0x[0-9a-fA-F]+)', line)
        if m:
            gp = int(m[1], 16)
    rd_lo = next(o for o, t, n in segs if o == 0x800)
    rd_hi = next(o for o, t, n in segs if t == 'data' and n.startswith('psyq/'))
    tx_lo = next(o for o, t, n in segs if t == 'c')
    tx_hi = next(o for o, t, n in segs if o > tx_lo and t == 'asm' and n.startswith('psyq/'))
    data_lo = next(o for o, t, n in segs if o > tx_hi and t == 'bin' and o >= 0x3e000)
    return dict(delta=load - 0x800, rdata=(rd_lo, rd_hi), text=(tx_lo, tx_hi), data=(data_lo, 0x800 + tsize),
                gp=gp)


def code_entry(e):
    return 'kind' not in e or e['kind'] == 'code_region'


def units(repo, maps, images=None):
    """Analysis units for the one-link images (MAIN split into its load images)."""
    out, skipped = [], []
    for image in images or repo.one_link_images():
        if image == 'main/main_bin':
            for child in MAIN_CHILDREN:
                out.append(overlay_unit(repo, maps[child], parent=image))
            skipped.append(dict(image=image, unit='main/main_bin@21968',
                                reason='instance_partial engine slice: its .rdata is not in the file'))
            continue
        if image == 'slus/slus_bin':
            out.append(slus_unit(repo, maps[image]))
            continue
        d = maps[image]
        u = overlay_unit(repo, d, parent=image)
        if u is None:
            skipped.append(dict(image=image, unit=image, reason='no code entries'))
        else:
            out.append(u)
    return out, skipped


def overlay_unit(repo, d, parent):
    container = d['container']
    lo, size = num(d['foff']), num(d['size'])
    hi = lo + size
    ents = sorted(d['entries'], key=lambda e: num(e['foff']))
    code = [e for e in ents if code_entry(e)]
    if not code:
        return None
    vma = num(d.get('vma'))
    if vma is None:
        # file view: derive the delta from registered rows; require one constant
        deltas = set()
        for e in code:
            for r in rows_in(repo, container, num(e['foff']), num(e['foff']) + e['size']):
                tn = r.get('true_name') or ''
                if re.fullmatch(r'func_[0-9A-F]{8}', tn):
                    deltas.add(int(tn[5:], 16) - r['foff'])
        if len(deltas) != 1:
            return None
        delta = deltas.pop()
    else:
        delta = vma - lo
    tx_lo = num(code[0]['foff'])
    tx_hi = num(code[-1]['foff']) + code[-1]['size']
    gaps = []
    entries = []
    for e in ents:
        f = num(e['foff'])
        if tx_lo <= f < tx_hi:
            if code_entry(e):
                entries.append(dict(foff=f, size=e['size'], row=e.get('row'), home=e.get('home'),
                                    kind='tu' if 'kind' not in e else 'code_region'))
            else:
                gaps.append(dict(foff=f, size=e['size'], kind=e['kind']))
    post = [dict(foff=num(e['foff']), size=e['size'], kind=e['kind']) for e in ents
            if num(e['foff']) >= tx_hi and e.get('kind') in ('data', 'asset')]
    pre = [dict(foff=num(e['foff']), size=e['size'], kind=e['kind']) for e in ents
           if num(e['foff']) < tx_lo and e.get('kind') in ('data', 'asset')]
    # the image's first/last code entry is a TU edge only when the bytes outside
    # the text are fully classified as non-code next to it
    before = [e for e in ents if num(e['foff']) < tx_lo]
    after = [e for e in ents if num(e['foff']) >= tx_hi]
    start_edge = all(e.get('kind') in ('data', 'asset', 'padding') for e in before)
    end_edge = bool(after) and after[0].get('kind') in ('data', 'asset', 'padding') or not after
    return dict(unit=d['image'], image=parent, container=container, extent=(lo, hi), delta=delta,
                rdata=(lo, tx_lo), text=(tx_lo, tx_hi), data=(tx_hi, hi), gp=None, entries=entries,
                text_gaps=gaps, pre_data=pre, post_data=post, start_edge=start_edge, end_edge=end_edge)


def slus_unit(repo, d):
    g = slus_geometry(repo.root)
    tx_lo, tx_hi = g['text']
    return dict(unit='slus/slus_bin', image='slus/slus_bin', container='slus', extent=(0, num(d['size'])),
                delta=g['delta'], rdata=g['rdata'], text=g['text'], data=g['data'], gp=g['gp'],
                entries=[], text_gaps=[], pre_data=[], post_data=[], slus=True, start_edge=True, end_edge=True)


def rows_in(repo, container, lo, hi):
    rs = repo.rows_by_container.get(container, [])
    import bisect
    keys = [r['foff'] for r in rs]
    i = bisect.bisect_left(keys, lo)
    out = []
    while i < len(rs) and rs[i]['foff'] < hi:
        out.append(rs[i])
        i += 1
    return out


def slus_function_rows(repo):
    """SLUS function vma -> (row id, source path) from the registered partitions."""
    out = {}
    for r in repo.rows.values():
        if r['container'] != 'slus':
            continue
        for name in [r.get('func')] + list(r.get('defs') or []):
            if name and re.fullmatch(r'func_[0-9A-F]{8}', name):
                out.setdefault(int(name[5:], 16), (r['id'], r['c_path']))
    return out


def functions(repo, u, data):
    """Ordered function list [(foff, end, row, home, origin)] over the unit's text."""
    tx_lo, tx_hi = u['text']
    starts = {}
    if u.get('slus'):
        frows = slus_function_rows(repo)
        for v, (rid, path) in frows.items():
            f = v - u['delta']
            if tx_lo <= f < tx_hi:
                starts[f] = (rid, rid, 'row')
        for v, (name, isfunc) in repo.slus_symbols.items():
            f = v - u['delta']
            if isfunc and tx_lo <= f < tx_hi and f not in starts:
                starts[f] = (None, None, 'symbol')
    else:
        for e in u['entries']:
            if e['kind'] == 'tu':
                starts[e['foff']] = (e['row'], e['home'], 'row')
            else:
                for r in rows_in(repo, u['container'], e['foff'], e['foff'] + e['size']):
                    if r['foff'] not in starts:
                        # a twin row's code is its source row's code (a placement of that home)
                        starts[r['foff']] = (r['id'], r.get('source_row') or r['id'], 'region_row')
                starts.setdefault(e['foff'], (None, None, 'region'))
    gap_set = [(g['foff'], g['foff'] + g['size']) for g in u['text_gaps']]
    off = tx_lo
    while off < tx_hi:
        if any(a <= off < b for a, b in gap_set):
            off += 4
            continue
        if struct.unpack_from('<I', data, off)[0] == JR_RA:
            nxt = off + 8
            while nxt < tx_hi and struct.unpack_from('<I', data, nxt)[0] == 0:
                nxt += 4
            if nxt < tx_hi and nxt not in starts and not any(a <= nxt < b for a, b in gap_set):
                starts[nxt] = (None, None, 'jr_ra')
            off += 8
        else:
            off += 4
    for a, b in gap_set:
        starts[a] = ('#gap', None, 'gap')
    keys = sorted(starts)
    out = []
    for i, a in enumerate(keys):
        b = keys[i + 1] if i + 1 < len(keys) else tx_hi
        row, home, origin = starts[a]
        if row == '#gap':
            continue
        out.append([a, b, row, home, origin])
    # unregistered starts inside a registered TU entry belong to that entry's source file
    owner = None
    for f in out:
        if f[4] == 'row' or f[4] == 'region_row':
            r = repo.rows.get(f[2]) or {}
            owner = (f[0], f[0] + (r.get('size') or (f[1] - f[0])), f[2], f[3])
        elif f[4] == 'jr_ra' and owner and owner[0] < f[0] < owner[1]:
            f[4] = 'inside:' + owner[2]
            f[3] = owner[3]
    return out


# ------------------------------------------------------------------ reference scan

LOADSTORE = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x28, 0x29, 0x2A, 0x2B, 0x2E, 0x32, 0x3A}


def _s16(x):
    return x - 0x10000 if x & 0x8000 else x


def _dest(w):
    op = w >> 26
    if op == 0:
        return (w >> 11) & 31
    if op in (0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F) or 0x20 <= op <= 0x26:
        return (w >> 16) & 31
    if op == 0x03:
        return 31
    if op == 0x12 and ((w >> 21) & 31) in (0, 2):
        return (w >> 16) & 31
    return None


def scan(data, foff, size, delta, gp=None):
    """Yield (inst_foff, kind, address): lui+addiu/ori/load/store pairs and gp refs.

    Linear, no control flow: a split across a branch join is missed (conservative).
    """
    hi = {}
    words = struct.unpack_from('<%dI' % (size // 4), data, foff)
    for k, w in enumerate(words):
        off = foff + 4 * k
        op = w >> 26
        rs = (w >> 21) & 31
        if op == 0x0F:
            hi[(w >> 16) & 31] = (w & 0xFFFF) << 16
            continue
        imm = w & 0xFFFF
        if op in (0x09, 0x0D) and rs in hi:
            yield off, 'addr', (hi[rs] + (_s16(imm) if op == 0x09 else imm)) & 0xFFFFFFFF
        elif op in LOADSTORE and rs in hi:
            yield off, 'mem', (hi[rs] + _s16(imm)) & 0xFFFFFFFF
        elif op in LOADSTORE and gp is not None and rs == 28:
            yield off, 'gp', (gp + _s16(imm)) & 0xFFFFFFFF
        elif op == 0x09 and gp is not None and rs == 28:
            yield off, 'gpaddr', (gp + _s16(imm)) & 0xFFFFFFFF
        d = _dest(w)
        if d is not None:
            hi.pop(d, None)
        if w == JR_RA:
            hi.clear()


def text_string(data, off, limit):
    """NUL-terminated ASCII/Shift-JIS text of >= 2 bytes, else None."""
    end = data.find(b'\0', off, min(limit, off + 512))
    if end - off < 2:
        return None
    s = data[off:end]
    i = 0
    while i < len(s):
        c = s[i]
        if 0x20 <= c < 0x7F or c in (9, 10):
            i += 1
        elif 0xA1 <= c <= 0xDF:
            i += 1
        elif (0x81 <= c <= 0x9F or 0xE0 <= c <= 0xEF) and i + 1 < len(s) and \
                (0x40 <= s[i + 1] <= 0x7E or 0x80 <= s[i + 1] <= 0xFC):
            i += 2
        else:
            return None
    return s


def dirty_fills(data, lo, hi):
    """(fill_foff, nbytes, bytes) for text runs whose alignment tail is nonzero.

    gcc/ASPSX fill .align gaps inside a section with zeros; a nonzero tail marks
    the end of an object's section contribution.
    """
    off = lo + ((-lo) % 4)
    while off < hi:
        s = text_string(data, off, hi)
        if s is None:
            off += 4
            continue
        end = off + len(s) + 1
        tail = (-end) % 4
        if tail and end + tail <= hi and any(data[end:end + tail]):
            yield end, tail, bytes(data[end:end + tail])
        off = end + tail


class DSU:
    def __init__(self, n):
        self.p = list(range(n))

    def find(self, x):
        while self.p[x] != x:
            self.p[x] = self.p[self.p[x]]
            x = self.p[x]
        return x

    def union(self, a, b):
        a, b = self.find(a), self.find(b)
        if a != b:
            self.p[max(a, b)] = min(a, b)
            return True
        return False


# ------------------------------------------------------------------- analysis

def analyse(repo, u):
    data = repo.blob(u['container'])
    delta = u['delta']
    f2v = lambda f: f + delta
    rd_lo, rd_hi = u['rdata']
    tx_lo, tx_hi = u['text']
    da_lo, da_hi = u['data']
    funcs = functions(repo, u, data)
    n = len(funcs)
    v_rd = (f2v(rd_lo), f2v(rd_hi))
    v_da = (f2v(da_lo), f2v(da_hi))
    v_end = f2v(u['extent'][1])
    refs = [set() for _ in range(n)]            # .rdata addresses
    drefs = [set() for _ in range(n)]           # post-text .data/.sdata addresses
    users = defaultdict(set)
    kinds = defaultdict(set)
    data_users = defaultdict(set)               # post-text .data/.sdata addresses
    bss_users = defaultdict(set)                # beyond the image (bss candidates)
    calls = [set() for _ in range(n)]          # jal targets (vma)
    brefs = [set() for _ in range(n)]           # bss-candidate addresses
    xrefs = [set() for _ in range(n)]           # addresses outside this image (resident storage)
    for i, (a, b, *_rest) in enumerate(funcs):
        for w in struct.unpack_from('<%dI' % ((b - a) // 4), data, a):
            if w >> 26 == 0x03:
                calls[i].add(((f2v(a) & 0xF0000000) | ((w & 0x03FFFFFF) << 2)))
        for _, kind, addr in scan(data, a, b - a, delta, u.get('gp')):
            if v_rd[0] <= addr < v_rd[1]:
                refs[i].add(addr)
                users[addr].add(i)
                kinds[addr].add(kind)
            elif v_da[0] <= addr < v_da[1]:
                data_users[addr].add(i)
                drefs[i].add(addr)
            elif kind in ('gp', 'gpaddr') or v_end <= addr < v_end + 0x40000:
                if not (f2v(tx_lo) <= addr < f2v(tx_hi)):
                    bss_users[addr].add(i)
                    brefs[i].add(addr)
            elif not (f2v(tx_lo) <= addr < f2v(tx_hi)) and addr >= 0x80000000:
                xrefs[i].add(addr)
    # string literals and jump tables (TU-private)
    content = {}
    for a in users:
        s = text_string(data, a - delta, rd_hi)
        if s is not None:
            content[a] = s
    jtab = {}
    for a, us in users.items():
        if a in content or len(us) != 1:
            continue
        i = next(iter(us))
        fa, fb = f2v(funcs[i][0]), f2v(funcs[i][1])
        k, off = 0, a - delta
        while off + 4 <= rd_hi and fa <= struct.unpack_from('<I', data, off)[0] < fb:
            k += 1
            off += 4
        if k >= 2:
            jtab[a] = (i, k)
    strings = {a: u_ for a, u_ in users.items() if a in content}
    private = dict(strings)
    private.update({a: users[a] for a in jtab})
    # named-const caveat: literal address named, a data row, or stored as a word in data
    words = set()
    for lo, hi in [(rd_lo, rd_hi), (da_lo, da_hi)]:
        lo4 = lo + ((-lo) % 4)
        if hi > lo4:
            words.update(struct.unpack_from('<%dI' % ((hi - lo4) // 4), data, lo4))
    caveat = {}
    for a in strings:
        why = []
        if u.get('slus') and a in repo.slus_symbols and not repo.slus_symbols[a][0].startswith('D_'):
            why.append('named')
        if (a - delta) in repo.data_rows.get(u['container'], {}):
            why.append('data_row')
        if a in words:
            why.append('pointer_word')
        if kinds[a] == {'mem'}:
            why.append('loaded_not_addressed')
        if why:
            caveat[a] = why
    # J1 + J2 to a fixpoint
    dsu = DSU(n)
    changed = True
    while changed:
        changed = False
        for a, us in strings.items():
            lo, hi = min(us), max(us)
            for k in range(lo, hi):
                changed |= dsu.union(k, k + 1)
        groups = defaultdict(list)
        for i in range(n):
            groups[dsu.find(i)].append(i)
        for g, members in groups.items():
            if len(members) < 2:
                continue
            lits = [a for m in members for a in refs[m] if a in private]
            if len(lits) < 2:
                continue
            lo, hi = min(lits), max(lits)
            for a, us in private.items():
                if lo <= a <= hi:
                    for m in us:
                        changed |= dsu.union(g, m)
    groups = defaultdict(list)
    for i in range(n):
        groups[dsu.find(i)].append(i)
    group_of = {i: dsu.find(i) for i in range(n)}
    # M: pool order == text order, over private literals
    first = sorted((min(us), a) for a, us in private.items())
    inversions = [(hex(a1), hex(a2)) for (f1, a1), (f2, a2) in zip(first, first[1:]) if f2 > f1 and a2 < a1]
    # B1 duplicate string contents
    by = defaultdict(list)
    for a, s in content.items():
        by[s].append(a)
    edges, contradictions = [], []
    for s, addrs in by.items():
        if len(addrs) < 2:
            continue
        addrs.sort()
        for a1, a2 in zip(addrs, addrs[1:]):
            g1 = {group_of[m] for m in users[a1]}
            g2 = {group_of[m] for m in users[a2]}
            if g1 & g2:
                contradictions.append(dict(kind='B1_same_group', text=s.decode('latin1'), a1=hex(a1), a2=hex(a2)))
                continue
            left, right = max(users[a1]), min(users[a2])
            if right <= left:
                contradictions.append(dict(kind='B1_order', text=s.decode('latin1'), a1=hex(a1), a2=hex(a2)))
                continue
            edges.append(dict(kind='B1', left=left, right=right, at=hex(a2),
                              text=s.decode('latin1')[:40]))
    # B2 nonzero .rdata fills, mapped through private literals only
    fills = []
    for p, k, fill in dirty_fills(data, rd_lo, rd_hi):
        cut = f2v(p + k)
        below = [i for a, us in private.items() if a < cut for i in us]
        above = [i for a, us in private.items() if a >= cut for i in us]
        rec = dict(at=hex(cut), fill=fill.hex(), mapped=False)
        fills.append(rec)
        if not below or not above:
            rec['why'] = 'no private literal user on one side'
            continue
        left, right = max(below), min(above)
        if right <= left:
            contradictions.append(dict(kind='B2_order', at=hex(cut), left=left, right=right))
            rec['why'] = 'order'
            continue
        rec['mapped'] = True
        edges.append(dict(kind='B2', left=left, right=right, at=hex(cut), fill=fill.hex()))
    # an edge inside one J1 group is a model contradiction; such edges are dropped
    kept = []
    for e in edges:
        g = group_of[e['left']]
        if g == group_of[e['right']] and len(groups[g]) > 1:
            contradictions.append(dict(kind=e['kind'] + '_inside_group', at=e['at']))
            for f in fills:
                if f['at'] == e['at']:
                    f['mapped'], f['why'] = False, 'inside J1 group'
        else:
            kept.append(e)
    edges = kept
    # post-text .data/.sdata fills (object ends; mapping is suggestive: data may be global)
    dfills = []
    for p, k, fill in dirty_fills(data, da_lo, da_hi):
        cut = f2v(p + k)
        below = [i for a, us in data_users.items() if a < cut for i in us]
        above = [i for a, us in data_users.items() if a >= cut for i in us]
        rec = dict(at=hex(cut), fill=fill.hex())
        if below and above and min(above) > max(below):
            rec['suggests_edge_after'] = max(below)
            rec['suggests_edge_before'] = min(above)
        dfills.append(rec)
    # data/bss order consistency (suggestive)
    def order_inversions(us_map):
        fl = sorted((min(us), a) for a, us in us_map.items())
        return sum(1 for (f1, a1), (f2, a2) in zip(fl, fl[1:]) if f2 > f1 and a2 < a1)
    # file-name anchors (__FILE__ copies) in pool order
    anchors = []
    seen = set()
    for a in sorted(content):
        s = content[a]
        if FILE_NAME.match(s) and s not in seen:
            seen.add(s)
            anchors.append((a, s.decode('latin1')))
    names = [s.rsplit('/', 1)[-1].rsplit('\\', 1)[-1] for _, s in anchors]
    alpha = 'n/a' if len(names) < 2 else ('yes' if names == sorted(names) else 'no')
    group_anchor = {}
    for a, s in anchors:
        for m in users.get(a, ()):
            group_anchor.setdefault(group_of[m], s)
    multi = {g: m for g, m in groups.items() if len(m) > 1}
    gl = []
    for g, members in sorted(multi.items(), key=lambda kv: kv[1][0]):
        lits = sorted({x for m in members for x in refs[m] if x in strings})
        gl.append(dict(gid='g%04d' % members[0], first=members[0], last=members[-1], members=len(members),
                       literals=['%08X' % x for x in lits],
                       caveat=sorted({w for x in lits for w in caveat.get(x, [])}),
                       file_anchor=group_anchor.get(g, '')))
    summary = dict(
        unit=u['unit'], image=u['image'], container=u['container'], functions=n,
        start_edge=u['start_edge'], end_edge=u['end_edge'],
        rdata=[hex(x) for x in u['rdata']], text=[hex(x) for x in u['text']], data=[hex(x) for x in u['data']],
        delta=hex(delta), functions_with_rdata_refs=sum(1 for r in refs if r), literals=len(users),
        string_literals=len(content), jump_tables=len(jtab), j1_groups=len(gl),
        functions_in_j1_groups=sum(g['members'] for g in gl),
        j1_groups_named_const_caveat=sum(1 for g in gl if g['caveat']),
        b1_witnesses=sum(1 for e in edges if e['kind'] == 'B1'),
        b2_fills=len(fills), b2_mapped=sum(1 for f in fills if f['mapped']),
        pool_order_inversions=len(inversions), contradictions=len(contradictions),
        data_fills=len(dfills), data_refs=len(data_users), data_order_inversions=order_inversions(data_users),
        bss_refs=len(bss_users), bss_order_inversions=order_inversions(bss_users),
        file_anchors=len(anchors), alphabetical=alpha,
    )
    fl = [dict(i=i, foff=a, end=b, vma=f2v(a), row=row, home=home, origin=origin,
               group=('g%04d' % group_of[i]) if group_of[i] in multi else '',
               rdata=['%08X' % x for x in sorted(refs[i])], data=len(drefs[i]),
               calls=['%08X' % x for x in sorted(calls[i])], drefs=['%08X' % x for x in sorted(drefs[i])],
               brefs=['%08X' % x for x in sorted(brefs[i])], xrefs=['%08X' % x for x in sorted(xrefs[i])])
          for i, (a, b, row, home, origin) in enumerate(funcs)]
    return dict(summary=summary, functions=fl, groups=gl, edges=edges, fills=fills, data_fills=dfills,
                contradictions=contradictions, inversions=inversions,
                anchors=[('%08X' % a, s) for a, s in anchors],
                jump_tables={'%08X' % a: dict(fn=i, words=k) for a, (i, k) in jtab.items()},
                caveats={'%08X' % a: w for a, w in caveat.items()})
