#!/usr/bin/env python3
"""Inferred original-file grouping beyond the proven literal spans (decision 72(b)).

Model: every function is a token in home space (its home row; unregistered code is
a token of its own).  Each image's text is a sequence of tokens and every pair of
neighbours is a GAP.  A gap is a JOIN (same original file) or a CUT (file edge).
Evidence about a gap is aggregated in home space, so a decision holds in every
image that links the same two neighbours (cross-image chain consistency).

Decisive (string literals, tu_evidence.py; hidden by --hide-strings):
  J1   gaps inside a shared-literal span          -> join, proven
  B12  exact B1/B2 edge                           -> cut, proven
  B12i interval B1/B2 edge (a cut lies inside)    -> no group may contain both ends

Inferred (byte facts read with a model; never decisive):
  CX   cross-image object order: in another (non-bank) image a neighbour sits next to a
       function this image places elsewhere (a linker links whole objects) -> cut
  CXB  the same between two dungeon banks (template TUs: one function text recurs in
       different orders inside one bank file)                              -> weak cut
  CXP  neighbours linked by different image sets (per-view recompiles give variant
       slots inside one file, e.g. town lshop.c)                           -> weak cut
  CL   call locality: a callee (> 16 B) with no co-resident caller (SLUS/engine) whose
       callers all lie within W functions of it (per bank: never pooled)  -> join span
  PD   private data: a .data/.sdata/.bss address whose users lie within W -> join span
  PR   private non-string, non-jump-table .rdata shared within W          -> join span
  XB   co-linked block: <= XB_MAX functions in >= 2 images, always adjacent,
       CX-cut on both sides                                               -> join span
  D2   nonzero .data fill mapped through private data (exact)             -> weak cut
  RC   registered compiler cell differs (72(c): artefacts inside proven spans)
                                                                          -> weak cut
  A join against a CX cut is a CONFLICT and is not taken.

Levels (rule pd4_cl2, chosen on the Psy-Q library holdout, see validation.json):
  proven          only J1 joins;
  inferred-strong a PD span of width <= 4 or a CL span of width <= 2 (or XB) covers the
                  gap and no weak cut does (library holdout precision 0.94);
  inferred-weak   any other join (holdout 0.87).
Proven edges are hard: a proven cut is never crossed, a proven span never split, and an
interval edge drops every inferred join inside its interval.

Validation (--validate -> validation.json): leave-strings-out against J1/B1/B2, the SLUS
Psy-Q library holdout (object boundaries from the splat segments), a Bayes projection to
game priors, and agreement with the existing native modules (modelled cohorts, not truth).

usage: infer_groups.py --evidence EVDIR --out DIR [--root ROOT] [--window 8]
                       [--rule pd4_cl2] [--validate]
Outputs: groups.tsv, gaps.tsv, per_image_inferred.tsv, batches.tsv, infer_totals.json,
         validation.json (with --validate).
"""
from __future__ import annotations

import argparse
import json
import re
import struct
import sys
from collections import Counter, defaultdict
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import tu_lib as T  # noqa: E402

LEVELS = ('proven', 'inferred-strong', 'inferred-weak')
RESIDENT = {'slus/slus_bin': None, 'slus/psyq_library': None, 'town/engine': 'town', 'dungeon/engine': 'dungeon'}
TINY = 20              # bytes: stubs, getters and trampolines (<= 16 B) recur everywhere
XB_MAX = 8             # longest co-linked block taken as one file
JOIN_KINDS = ('CL', 'PD', 'PR', 'XB')


def _w(e, kind, width):
    return any(k == kind and w <= width for k, w in e['spans'])


# strong-join predicates, chosen by measured holdout precision (see REPORT / validation.json)
STRONG_RULES = {
    'two_kinds': lambda e, kinds, sk: len(kinds) >= 2 or bool(kinds & sk),
    'pd4_or_clpd': lambda e, kinds, sk: _w(e, 'PD', 4) or {'CL', 'PD'} <= kinds or bool(kinds & sk),
    'pd4': lambda e, kinds, sk: _w(e, 'PD', 4) or bool(kinds & sk),
    'pd2_cl2': lambda e, kinds, sk: _w(e, 'PD', 2) or _w(e, 'CL', 2) or bool(kinds & sk),
    'clpd4': lambda e, kinds, sk: (_w(e, 'PD', 4) and _w(e, 'CL', 4)) or bool(kinds & sk),
    'pd4_cl2': lambda e, kinds, sk: _w(e, 'PD', 4) or _w(e, 'CL', 2) or bool(kinds & sk),
}


def h(x):
    return int(x, 16)


def bank(unit):
    return unit.startswith('dungeon/bank_')


def witness(e, kind, what):
    (e['cut'] if kind == 'CX' else e['weakcut']).add('%s:%s' % (kind, what))


class Model:
    def __init__(self, evidence, root, window=8, hide_strings=False, strong_kinds=None, units=None, repo=None,
                 ref_units=None, rule='pd4_cl2'):
        self.root = Path(root)
        self.repo = repo or T.Repo(root)
        self.W = window
        self.hide = hide_strings
        self.units = {}
        if units is not None:
            self.units = dict(units)
        else:
            for p in sorted((Path(evidence) / 'units').glob('*.json')):
                d = json.loads(p.read_text())
                self.units[d['summary']['unit']] = d
        self.ref_units = ref_units or {}
        self.rule = rule
        self.strong_kinds = set(strong_kinds if strong_kinds is not None else ('XB',))
        self.tok = {}
        self.seq = {}
        for name, d in self.units.items():
            s = []
            for f in d['functions']:
                s.append(f['home'] or '%s@%X' % (name, f['foff']))
            self.seq[name] = s
        self.occ = defaultdict(list)
        for name, s in self.seq.items():
            for i, t in enumerate(s):
                self.occ[t].append((name, i))
        self.pos = {name: defaultdict(list) for name in self.seq}
        for name, s in self.seq.items():
            for i, t in enumerate(s):
                self.pos[name][t].append(i)
        # ambiguous tokens: in-image duplicates anywhere, or tiny code
        self.ambiguous = set()
        for name, d in self.units.items():
            for i, f in enumerate(d['functions']):
                t = self.seq[name][i]
                if len(self.pos[name][t]) > 1 or f['end'] - f['foff'] < TINY:
                    self.ambiguous.add(t)
        self.recipe = {}
        for name, d in self.units.items():
            for i, f in enumerate(d['functions']):
                r = self.repo.rows.get(f['home'] or '') or self.repo.rows.get(f['row'] or '')
                if r:
                    self.recipe[self.seq[name][i]] = (r.get('cfg'), r.get('row_asflags') or '')

    # ------------------------------------------------------------ evidence
    def pair(self, name, i):
        s = self.seq[name]
        return (s[i], s[i + 1])

    def gap_evidence(self):
        """ev[(a, b)] -> dict(join=set(ids), cut=set(ids), weakcut=set(ids), adj=int, units=set())."""
        ev = defaultdict(lambda: dict(join=set(), cut=set(), weakcut=set(), proven_join=set(),
                                      proven_cut=set(), adj=0, units=set(), spans=[]))
        self.intervals = []     # (unit, left, right, id)
        for name, d in self.units.items():
            fns = d['functions']
            for i in range(len(fns) - 1):
                ev[self.pair(name, i)]['units'].add(name)
        # decisive literal evidence
        if not self.hide:
            for name, d in self.units.items():
                fns = d['functions']
                for g in d['groups']:
                    for i in range(g['first'], g['last']):
                        ev[self.pair(name, i)]['proven_join'].add('J1:%s#%s' % (name, g['gid']))
                for e in d['edges']:
                    eid = '%s:%s@%s' % (e['kind'], name, e['at'])
                    if e['right'] == e['left'] + 1:
                        ev[self.pair(name, e['left'])]['proven_cut'].add(eid)
                    else:
                        self.intervals.append((name, e['left'], e['right'], eid))
        self._cx(ev)
        self._spans(ev)
        self._weak_cuts(ev)
        return ev

    def _cx(self, ev):
        for name, s in self.seq.items():
            in_u = self.pos[name]
            for i in range(len(s) - 1):
                a, b = s[i], s[i + 1]
                e = ev[(a, b)]
                if a in self.ambiguous or b in self.ambiguous:
                    continue
                others = {u for u, _ in self.occ[a]} | {u for u, _ in self.occ[b]}
                others.discard(name)
                for v in sorted(others):
                    # dungeon banks are template TUs: the same function text recurs in
                    # different orders inside one bank file, so bank-vs-bank order is no
                    # object evidence (kept as the weak cut CXB)
                    kind = 'CXB' if bank(name) and bank(v) else 'CX'
                    pv = self.pos[v]
                    sv = self.seq[v]
                    pa, pb = pv.get(a, []), pv.get(b, [])
                    if len(pa) > 1 or len(pb) > 1:
                        continue
                    if pa and pb:
                        pa, pb = pa[0], pb[0]
                        if pb == pa + 1:
                            e['adj'] += 1
                        elif pb > pa + 1 and all(t not in in_u for t in sv[pa + 1:pb]):
                            pass
                        else:
                            witness(e, kind, '%s:%s' % ('order' if pb < pa else 'between', v))
                    elif pa:
                        pa = pa[0]
                        if pa + 1 >= len(sv):
                            continue
                        x = sv[pa + 1]
                        if x not in in_u or x in self.ambiguous or len(in_u[x]) != 1:
                            continue
                        px = in_u[x][0]
                        if px > i + 1 and all(t not in pv for t in s[i + 1:px]):
                            continue
                        witness(e, kind, 'next:%s' % v)
                    else:
                        pb = pb[0]
                        if pb == 0:
                            continue
                        y = sv[pb - 1]
                        if y not in in_u or y in self.ambiguous or len(in_u[y]) != 1:
                            continue
                        py = in_u[y][0]
                        if py < i and all(t not in pv for t in s[py + 1:i + 1]):
                            continue
                        witness(e, kind, 'prev:%s' % v)

    def _external(self):
        """Call targets and data addresses used from another co-resident image."""
        ext_calls = defaultdict(set)
        ext_data = defaultdict(set)
        for name, d in self.ref_units.items():
            for f in d['functions']:
                for c in f['calls']:
                    ext_calls[h(c)].add(name)
                for x in f.get('xrefs', []) + f.get('drefs', []) + f.get('brefs', []):
                    ext_data[h(x)].add(name)
        for name, d in self.units.items():
            starts = {f['vma'] for f in d['functions']}
            for f in d['functions']:
                for c in f['calls']:
                    v = h(c)
                    if v not in starts:
                        ext_calls[v].add(name)
                for x in f.get('xrefs', []):
                    ext_data[h(x)].add(name)
        return ext_calls, ext_data

    def _coresident(self, unit, users):
        """True when a co-resident image uses this unit's address (so the object is global).

        SLUS is resident under everything; an engine is resident under its family's
        views/banks; a view/bank/MAIN image is called into only by SLUS or its engine."""
        fam = RESIDENT.get(unit, 'x')
        if unit in RESIDENT:
            if fam is None:
                return any(u != unit for u in users)
            return any(u != unit and u.split('/')[0] == fam for u in users)
        family = unit.split('/')[0]
        return any(u == 'slus/slus_bin' or (RESIDENT.get(u) == family) for u in users)

    def _spans(self, ev):
        """CL / PD / PR join spans, aggregated per callee/data across images."""
        W = self.W
        ext_calls, ext_data = self._external()
        cand = defaultdict(list)     # (kind, key) -> [(unit, lo, hi)]
        bad = set()
        for name, d in self.units.items():
            fns = d['functions']
            idx = {f['vma']: f['i'] for f in fns}
            callers = defaultdict(set)
            for f in fns:
                for c in f['calls']:
                    j = idx.get(h(c))
                    if j is not None and j != f['i']:
                        callers[j].add(f['i'])
            seq = self.seq[name]
            for j, cs in callers.items():
                # a bank's homes are byte-identity classes shared by distinct template TUs:
                # never pool a callee's locality across banks
                key = ('CL', seq[j] + ('@' + name if bank(name) else ''))
                if fns[j]['end'] - fns[j]['foff'] < TINY:
                    continue    # stubs/trampolines are called from anywhere
                if self._coresident(name, ext_calls.get(fns[j]['vma'], ())):
                    bad.add(key)
                    continue
                lo, hi = min(cs | {j}), max(cs | {j})
                if hi - lo > W:
                    bad.add(key)
                    continue
                cand[key].append((name, lo, hi))
            # data / bss / non-string rodata users
            strings = set()
            for g in d['groups']:
                strings.update(g['literals'])
            jt = set(d['jump_tables'])
            users = defaultdict(set)
            for f in fns:
                for x in f['drefs'] + f['brefs']:
                    users[('PD', x)].add(f['i'])
                for x in f['rdata']:
                    if x in jt or x in strings:
                        continue
                    users[('PR', x)].add(f['i'])
            # string literals that tu_evidence did not group (single-user) are left out of PR
            content = self._strings(name, d)
            for (kind, x), us in users.items():
                if kind == 'PR' and x in content:
                    continue
                key = (kind, '%s:%s' % (name if kind != 'PD' or name not in RESIDENT else name, x))
                if len(us) < 2:
                    continue
                if kind == 'PD' and self._coresident(name, ext_data.get(h(x), ())):
                    bad.add(key)
                    continue
                lo, hi = min(us), max(us)
                if hi - lo > W:
                    bad.add(key)
                    continue
                cand[key].append((name, lo, hi))
        for key, occs in cand.items():
            if key in bad:
                continue
            sid = '%s:%s' % key
            width = max(hi - lo for _, lo, hi in occs)
            for name, lo, hi in occs:
                for i in range(lo, hi):
                    e = ev[self.pair(name, i)]
                    e['join'].add(sid)
                    e['spans'].append((key[0], width))
        self._xb(ev)

    def _strings(self, name, d):
        """Every .rdata address of this unit that holds a string (all users)."""
        if not hasattr(self, '_strcache'):
            self._strcache = {}
        if name in self._strcache:
            return self._strcache[name]
        s = d['summary']
        rd_lo, rd_hi = (h(x) for x in s['rdata'])
        delta = h(s['delta'])
        data = self.repo.blob(s['container'])
        out = set()
        for f in d['functions']:
            for x in f['rdata']:
                a = h(x) - delta
                if rd_lo <= a < rd_hi and T.text_string(data, a, rd_hi) is not None:
                    out.add(x)
        self._strcache[name] = out
        return out

    def _xb(self, ev):
        """Co-linked blocks: runs in >= 2 images, always adjacent, CX-cut on both sides."""
        for name, s in self.seq.items():
            n = len(s)
            i = 0
            while i < n:
                j = i
                while j + 1 < n:
                    e = ev[(s[j], s[j + 1])]
                    if e['cut'] or e['adj'] == 0:
                        break
                    j += 1
                if j > i and j - i + 1 <= XB_MAX:
                    left_cut = i == 0 or bool(ev[(s[i - 1], s[i])]['cut'])
                    right_cut = j == n - 1 or bool(ev[(s[j], s[j + 1])]['cut'])
                    multi = all(len({u for u, _ in self.occ[t]}) >= 2 for t in s[i:j + 1])
                    if left_cut and right_cut and multi and i > 0 and j < n - 1:
                        sid = 'XB:%s' % s[i]
                        for k in range(i, j):
                            ev[(s[k], s[k + 1])]['join'].add(sid)
                            ev[(s[k], s[k + 1])]['spans'].append(('XB', j - i))
                i = j + 1

    def _weak_cuts(self, ev):
        # CXP: neighbours linked by different image sets (non-bank, unambiguous).  Not
        # a strong cut: per-view recompiles of one source give variant slots (town
        # lshop.c's neighbours), so presence alone cannot separate objects.
        units_of = {t: frozenset(u for u, _ in occ) for t, occ in self.occ.items()}
        for (a, b), e in ev.items():
            if a in self.ambiguous or b in self.ambiguous or any(bank(u) for u in e['units']):
                continue
            if units_of.get(a) != units_of.get(b):
                e['weakcut'].add('CXP:%d/%d' % (len(units_of.get(a, ())), len(units_of.get(b, ()))))
        for name, s in self.seq.items():
            for i in range(len(s) - 1):
                ra, rb = self.recipe.get(s[i]), self.recipe.get(s[i + 1])
                if ra and rb and ra != rb:
                    ev[(s[i], s[i + 1])]['weakcut'].add('RC:%s|%s' % (ra[0], rb[0]))
        # D2: nonzero .data fills mapped through private data users (all users within W)
        W = self.W
        for name, d in self.units.items():
            fns = d['functions']
            users = defaultdict(set)
            for f in fns:
                for x in f['drefs']:
                    users[h(x)].add(f['i'])
            priv = {a: us for a, us in users.items() if max(us) - min(us) <= W}
            if not priv:
                continue
            addrs = sorted(priv)
            import bisect
            for df in d['data_fills']:
                cut = h(df['at'])
                k = bisect.bisect_left(addrs, cut)
                below = [i for a in addrs[:k] for i in priv[a]]
                above = [i for a in addrs[k:] for i in priv[a]]
                if not below or not above:
                    continue
                left, right = max(below), min(above)
                if right == left + 1:
                    ev[self.pair(name, left)]['weakcut'].add('D2:%s@%s' % (name, df['at']))

    # ------------------------------------------------------------ decisions
    def decide(self, ev):
        """gap -> (decision, level, ids).  decision: join | cut | conflict | none."""
        dec = {}
        for key, e in ev.items():
            if e['proven_join']:
                dec[key] = ('join', 'proven', sorted(e['proven_join']))
            elif e['proven_cut']:
                dec[key] = ('cut', 'proven', sorted(e['proven_cut']))
            elif e['cut'] and e['join']:
                # be conservative: an object-order cut against a locality join is no join
                dec[key] = ('conflict', '', sorted(e['cut'])[:2] + sorted(e['join'])[:3])
            elif e['cut']:
                dec[key] = ('cut', 'inferred-strong', sorted(e['cut'])[:4])
            elif e['join']:
                kinds = {x.split(':')[0] for x in e['join']}
                if e['weakcut']:
                    lvl = 'inferred-weak'
                elif STRONG_RULES[self.rule](e, kinds, self.strong_kinds):
                    lvl = 'inferred-strong'
                else:
                    lvl = 'inferred-weak'
                dec[key] = ('join', lvl, sorted(e['join'])[:6] + sorted(e['weakcut'])[:2])
            else:
                dec[key] = ('none', '', sorted(e['weakcut'])[:2])
        return dec

    def groups(self, ev, dec, max_level):
        """Per unit: list of (lo, hi, level, ids) groups at the given threshold."""
        rank = {l: k for k, l in enumerate(LEVELS)}
        out = {}
        for name, s in self.seq.items():
            n = len(s)
            joined = []
            for i in range(n - 1):
                d_, lvl, ids = dec[(s[i], s[i + 1])]
                joined.append(d_ == 'join' and rank[lvl] <= rank[max_level])
            # interval edges: drop inferred joins inside an interval a group would span
            for u, left, right, eid in self.intervals:
                if u != name:
                    continue
                if all(joined[left:right]):
                    for k in range(left, right):
                        if dec[(s[k], s[k + 1])][1] != 'proven':
                            joined[k] = False
            gs = []
            i = 0
            while i < n:
                j = i
                while j < n - 1 and joined[j]:
                    j += 1
                lv = 'proven'
                ids = set()
                for k in range(i, j):
                    _, l2, ii = dec[(s[k], s[k + 1])]
                    if rank[l2] > rank[lv]:
                        lv = l2
                    ids.update(x for x in ii if not x.startswith(('RC', 'D2')))
                gs.append((i, j, lv if j > i else '', sorted(ids)))
                i = j + 1
            out[name] = gs
        return out


# ------------------------------------------------------------------ validation

def library_unit(repo):
    """Holdout: the SLUS Psy-Q library text, whose object boundaries are known
    independently (splat segments identified byte-for-byte against the SDK
    signatures, config/slus_006.14.yaml).  Returns (unit, truth_join, truth_cut)
    as index pairs.  Only the boundaries are used; no SDK bytes are read or kept
    beyond the retail image."""
    g = T.slus_geometry(repo.root)
    delta, gp = g['delta'], g['gp']
    lo, hi = g['text'][1], g['data'][0]
    segs = []
    for line in open(repo.root / 'config/slus_006.14.yaml'):
        m = re.match(r'\s*- \[(0x[0-9a-fA-F]+),\s*asm,\s*(psyq/[^\]]+)\]', line)
        if m and lo <= int(m[1], 16) < hi:
            # Psy-Q 4.0 ships BIOS_1/2/3 as LIBCD BIOS.OBJ and CDR_1/2 as CDREAD.OBJ
            # (documented on those segments); 4.6+ only split the naming
            segs.append((int(m[1], 16), re.sub(r'/(BIOS|CDR)_\d+$', r'/\1', m[2].strip())))
    segs.sort()
    data = repo.blob('slus')
    starts = sorted(v - delta for v, (n, f) in repo.slus_symbols.items() if f and lo <= v - delta < hi)
    starts = sorted(set(starts) | {a for a, _ in segs})
    def seg_of(off):
        k = None
        for a, name in segs:
            if a <= off:
                k = name
        return k
    fns = []
    for i, a in enumerate(starts):
        b = starts[i + 1] if i + 1 < len(starts) else hi
        calls, drefs, brefs, rdata, xrefs = set(), set(), set(), set(), set()
        for w in struct.unpack_from('<%dI' % ((b - a) // 4), data, a):
            if w >> 26 == 0x03:
                calls.add(((a + delta) & 0xF0000000) | ((w & 0x03FFFFFF) << 2))
        for _, kind, addr in T.scan(data, a, b - a, delta, gp):
            if g['rdata'][0] + delta <= addr < g['rdata'][1] + delta:
                rdata.add(addr)
            elif g['data'][0] + delta <= addr < g['data'][1] + delta:
                drefs.add(addr)
            elif kind in ('gp', 'gpaddr') or addr >= g['data'][1] + delta:
                brefs.add(addr)
        fns.append(dict(i=i, foff=a, end=b, vma=a + delta, row=None, home='lib@%X' % a, origin='lib',
                        group='', rdata=['%08X' % x for x in sorted(rdata)], data=len(drefs),
                        calls=['%08X' % x for x in sorted(calls)], drefs=['%08X' % x for x in sorted(drefs)],
                        brefs=['%08X' % x for x in sorted(brefs)], xrefs=[], seg=seg_of(a)))
    unit = dict(summary=dict(unit='slus/psyq_library', image='slus/slus_bin', container='slus',
                             rdata=[hex(x) for x in g['rdata']], delta=hex(delta)),
                functions=fns, groups=[], edges=[], jump_tables={}, data_fills=[])
    tj, tc = set(), set()
    for i in range(len(fns) - 1):
        (tj if fns[i]['seg'] == fns[i + 1]['seg'] else tc).add(i)
    return unit, tj, tc, len(segs)


def holdout(evidence, root, window, strong_kinds, repo=None, rule='pd4_cl2'):
    repo = repo or T.Repo(root)
    unit, tj, tc, nseg = library_unit(repo)
    refs = {}
    for p in sorted((Path(evidence) / 'units').glob('*.json')):
        d = json.loads(p.read_text())
        refs[d['summary']['unit']] = d
    m = Model(None, root, window=window, hide_strings=True, strong_kinds=strong_kinds,
              units={'slus/psyq_library': unit}, repo=repo, ref_units=refs, rule=rule)
    ev = m.gap_evidence()
    s = m.seq['slus/psyq_library']
    per = {}
    for kind in JOIN_KINDS:
        t = f = 0
        for i in range(len(s) - 1):
            if any(x.split(':')[0] == kind for x in ev[(s[i], s[i + 1])]['join']):
                t += i in tj
                f += i in tc
        per[kind] = dict(joins_on_true_join=t, joins_on_true_cut=f,
                         precision=round(t / (t + f), 3) if t + f else None)
    dec = m.decide(ev)
    rank = {l: k for k, l in enumerate(LEVELS)}
    lv = {}
    for lvl in ('inferred-strong', 'inferred-weak'):
        t = f = 0
        for i in range(len(s) - 1):
            d_, l2, _ = dec[(s[i], s[i + 1])]
            if d_ == 'join' and rank[l2] <= rank[lvl]:
                t += i in tj
                f += i in tc
        lv[lvl] = dict(joined_true=t, joined_false=f, precision=round(t / (t + f), 3) if t + f else None,
                       recall=round(t / len(tj), 3) if tj else None)
    return dict(functions=len(s), objects=nseg, true_join_gaps=len(tj), true_cut_gaps=len(tc),
                per_signal=per, levels=lv)


def truth(model):
    """String-literal truth per gap: join (inside J1), cut (exact edge), plus intervals."""
    tj, tc, iv = set(), set(), []
    for name, d in model.units.items():
        for g in d['groups']:
            for i in range(g['first'], g['last']):
                tj.add(model.pair(name, i))
        for e in d['edges']:
            if e['right'] == e['left'] + 1:
                tc.add(model.pair(name, e['left']))
            else:
                iv.append((name, e['left'], e['right']))
    return tj, tc, iv


def literal_loo(m):
    """Leave-strings-out: m was built with hide_strings=True; score against J1/B1/B2."""
    ev = m.gap_evidence()
    tj, tc, iv = truth(m)
    per = {}
    for kind in ('CX', 'CXP', 'CXB', 'RC', 'D2') + JOIN_KINDS:
        jt = jc = ct = cc = 0
        for key in tj | tc:
            e = ev[key]
            ids = e['join'] | e['cut'] | e['weakcut']
            if not any(x.split(':')[0] == kind for x in ids):
                continue
            says_join = kind in JOIN_KINDS
            if key in tj:
                jt += says_join
                ct += not says_join
            else:
                jc += says_join
                cc += not says_join
        per[kind] = dict(on_true_join=jt + ct, on_true_cut=jc + cc)
    dec = m.decide(ev)
    res = {}
    rank = {l: k for k, l in enumerate(LEVELS)}
    for lvl in ('inferred-strong', 'inferred-weak'):
        gs = m.groups(ev, dec, lvl)
        tp = fp = 0
        for key in tj:
            d_, l2, _ = dec[key]
            tp += d_ == 'join' and rank[l2] <= rank[lvl]
        for key in tc:
            d_, l2, _ = dec[key]
            fp += d_ == 'join' and rank[l2] <= rank[lvl]
        viol = sum(1 for name, left, right in iv for lo, hi, _, _ in gs[name] if lo <= left and right <= hi)
        spans = whole = 0
        for name, d in m.units.items():
            for g in d['groups']:
                spans += 1
                whole += any(lo <= g['first'] and g['last'] <= hi for lo, hi, _, _ in gs[name])
        res[lvl] = dict(true_join_gaps=len(tj), joined=tp, recall=round(tp / len(tj), 3) if tj else None,
                        true_cut_gaps=len(tc), false_joins=fp, interval_edges=len(iv), interval_violations=viol,
                        j1_span_occurrences=spans, j1_spans_reproduced_whole=whole)
    return dict(per_signal_on_truth=per, levels=res)


def module_agreement(m, ev, dec):
    """Sanity row against the existing native modules (prior modelled cohorts, NOT truth):
    inferred groups that straddle a module edge inside an image."""
    rank = {l: k for k, l in enumerate(LEVELS)}
    out = {}
    mod = m.repo.module_of
    for lvl in ('inferred-strong', 'inferred-weak'):
        gs = m.groups(ev, dec, lvl)
        straddle = inside = 0
        for name, groups in gs.items():
            fns = m.units[name]['functions']
            for lo, hi, glvl, _ in groups:
                if hi == lo:
                    continue
                keys = {mod.get(fns[k]['home'] or '') for k in range(lo, hi + 1)}
                if None in keys and len(keys) > 1 or len(keys - {None}) > 1:
                    straddle += 1
                elif keys != {None}:
                    inside += 1
        out[lvl] = dict(groups_inside_one_module=inside, groups_straddling_module_edge=straddle)
    return out


def bayes(t, f, nt, nc):
    """Projected precision for a game prior P(cut) from holdout likelihoods."""
    pj, pc = t / nt, f / nc
    return {('p_cut_%.1f' % q): round(pj * (1 - q) / (pj * (1 - q) + pc * q), 3) if pj + pc else None
            for q in (0.1, 0.3, 0.6)} | dict(likelihood_ratio=round(pj / pc, 1) if pc else None)


def validate(evidence, root, window, strong_kinds, rule):
    repo = T.Repo(root)
    v = dict(window=window, rule=rule, strong_kinds=sorted(strong_kinds))
    m = Model(evidence, root, window=window, hide_strings=True, strong_kinds=strong_kinds, rule=rule, repo=repo)
    v['literal_leave_strings_out'] = literal_loo(m)
    v['library_holdout'] = hl = holdout(evidence, root, window, strong_kinds, repo=repo, rule=rule)
    v['bayes_projection'] = {lvl: bayes(x['joined_true'], x['joined_false'], hl['true_join_gaps'],
                                        hl['true_cut_gaps']) for lvl, x in hl['levels'].items()}
    full = Model(evidence, root, window=window, strong_kinds=strong_kinds, rule=rule, repo=repo)
    ev = full.gap_evidence()
    v['existing_module_agreement'] = module_agreement(full, ev, full.decide(ev))
    return v


# ------------------------------------------------------------------ outputs

def clean(x):
    return str(x).replace('\t', ' ').replace('\n', ' ')


def emit(m, ev, dec, out, validation=None):
    """groups.tsv, gaps.tsv, batches.tsv, infer_totals.json."""
    import boundary_map as BM
    ctx = BM.Ctx(m.root)
    ctx.repo = m.repo
    repo = m.repo
    rank = {l: k for k, l in enumerate(LEVELS)}
    where = defaultdict(list)
    for name, d in m.units.items():
        for f in d['functions']:
            if f['home'] and f['origin'] in ('row', 'region_row'):
                where[f['home']].append((name, f['i']))
    # gaps.tsv: every decided gap in home space
    with open(out / 'gaps.tsv', 'w') as fh:
        fh.write('left\tright\tdecision\tlevel\tevidence\tcx_adjacent_images\tunits\n')
        for (a, b), e in sorted(ev.items()):
            d_, lvl, ids = dec[(a, b)]
            if d_ == 'none' and not ids:
                continue
            fh.write('\t'.join(map(clean, [a, b, d_, lvl, ','.join(ids), e['adj'], len(e['units'])])) + '\n')
    grouped = {lvl: m.groups(ev, dec, lvl) for lvl in LEVELS}
    all_paths = set()
    paths = {}
    for name, d in m.units.items():
        for f in d['functions']:
            p = ctx.path_of(f)
            paths[(name, f['i'])] = p
            if p:
                all_paths.add(p)
    # unique groups (ordered token tuple), strong threshold first then weak extensions
    uniq = {}
    for lvl in ('inferred-strong', 'inferred-weak'):
        for name, gs in sorted(grouped[lvl].items()):
            for lo, hi, glvl, ids in gs:
                if hi == lo:
                    continue
                key = tuple(m.seq[name][lo:hi + 1])
                if key in uniq:
                    uniq[key]['units'].append(name)
                    continue
                uniq[key] = dict(unit=name, lo=lo, hi=hi, level=glvl, ids=ids, units=[name], threshold=lvl)
    # strong groups inside a weak group
    for key, g in uniq.items():
        g['parent'] = ''
        if g['threshold'] == 'inferred-strong':
            for lo, hi, glvl, ids in grouped['inferred-weak'][g['unit']]:
                if lo <= g['lo'] and g['hi'] <= hi and (lo, hi) != (g['lo'], g['hi']):
                    g['parent'] = tuple(m.seq[g['unit']][lo:hi + 1])
    gid = {}
    for k, (key, g) in enumerate(sorted(uniq.items(), key=lambda kv: (rank[kv[1]['level']], kv[1]['unit'],
                                                                         kv[1]['lo']))):
        gid[key] = 'G%05d' % (k + 1)
    rows_out = []
    regions = load_regions(m.root)
    for key, g in uniq.items():
        name, lo, hi = g['unit'], g['lo'], g['hi']
        d = m.units[name]
        s = d['summary']
        fns = d['functions']
        unit_entries = defaultdict(list)
        for f in fns:
            if f['home']:
                unit_entries[f['home']].append(f['foff'])
        mflags = [BM.member_flags(ctx, s, fns, k, unit_entries) for k in range(lo, hi + 1)]
        jt = {v['fn'] for v in d['jump_tables'].values()}
        files = []
        for k in range(lo, hi + 1):
            p = paths[(name, k)] or '?'
            if p not in files:
                files.append(p)
        recipes = sorted({'%s%s' % (r[0], (' ' + r[1]) if r[1] else '') for _, r in mflags if r})
        flags = set()
        for k, (fl, _) in zip(range(lo, hi + 1), mflags):
            flags |= fl
            if k in jt:
                flags.add('member_has_jump_table')
        flags.discard('goto_or_volatile_body')       # 72(e): a moved goto is acceptable
        cells = {r for _, r in mflags if r}
        if s['container'] == 'slus':
            flags.add('slus_partition')
        elif any(c[1] for c in cells) or not {c[0] for c in cells} <= set(MEMBER_CELLS):
            flags.add('recipe_not_module_supported')
        elif len(cells) > 1 or not {c[0] for c in cells} <= set(MODULE_RECIPES):
            flags.add('mixed_registered_cells')        # 72(c): tu_merge spec "recipe" + prove
        if s['container'] != 'slus':
            flags.discard('main_data_import')          # replaced by the per-address classification below
            flags |= data_flags(m, regions, name, d, range(lo, hi + 1), paths)
        # own-home runs: contiguous rows homed here (the mergeable modules)
        runs, run = [], []
        for k in range(lo, hi + 1):
            f = fns[k]
            if f['row'] and f['row'] == f['home'] and f['origin'] in ('row', 'region_row'):
                run.append(k)
            else:
                if run:
                    runs.append(run)
                run = []
        if run:
            runs.append(run)
        if any(fns[k]['row'] != fns[k]['home'] for k in range(lo, hi + 1)):
            flags.add('member_is_placement')
        # cross-image placements of the own-home runs
        for r_ in runs:
            homes = [fns[k]['home'] for k in r_]
            for other in sorted({u for h_ in homes for u, _ in where[h_]} - {name}):
                pos = {}
                for h_ in homes:
                    hits = [i for u, i in where[h_] if u == other]
                    if len(hits) == 1:
                        pos[h_] = hits[0]
                seq = [pos.get(h_) for h_ in homes]
                if None in seq or seq != list(range(seq[0], seq[0] + len(seq))):
                    flags.add('cross_image_partial')
                else:
                    flags.add('needs_module_placements')
        mergeable = [r_ for r_ in runs if len(r_) >= 2]
        # alphabetical link order (decision 72(a)): __FILE__ anchors around the group bound its name
        anchors = [(x['first'], x['last'], x['file_anchor']) for x in d['groups'] if x.get('file_anchor')]
        own_name = sorted({a for f_, l_, a in anchors if lo <= f_ and l_ <= hi})
        before = [a for f_, l_, a in anchors if l_ < lo]
        after = [a for f_, l_, a in anchors if f_ > hi]
        name_hint = ('file ' + '/'.join(own_name) if own_name else
                     ('between %s and %s' % (before[-1] if before else '^', after[0] if after else '$'))
                     if anchors else '')
        level = g['level']
        rows_out.append(dict(
            group_id=gid[key], image=s['image'], unit=name, level=level, members=hi - lo + 1,
            first_row=BM.fn_label(fns[lo]), last_row=BM.fn_label(fns[hi]),
            member_rows=[BM.fn_label(fns[k]) for k in range(lo, hi + 1)], files=files,
            file_reduction=max(0, len([p for p in files if p != '?']) - 1),
            recipe=recipes, evidence=g['ids'], blockers=sorted(flags),
            mergeable_runs=[[BM.fn_label(fns[k]) for k in r_] for r_ in mergeable],
            parent=gid.get(g['parent'], ''), occurrences=len(g['units']), units=g['units'], name_hint=name_hint,
            foff_first='%X' % fns[lo]['foff'], foff_end='%X' % fns[hi]['end'], container=s['container']))
    rows_out.sort(key=lambda r: (rank[r['level']], r['group_id']))
    cols = ['image', 'group_id', 'level', 'container', 'members', 'files', 'recipe', 'evidence', 'blockers', 'file_count',
            'file_reduction', 'first_row', 'last_row', 'foff_first', 'foff_end', 'mergeable_runs', 'parent',
            'occurrences', 'units', 'name_hint', 'member_rows']
    with open(out / 'groups.tsv', 'w') as fh:
        fh.write('\t'.join(cols) + '\n')
        for r in rows_out:
            vals = dict(r, files=';'.join(r['files']), recipe=','.join(r['recipe']),
                        evidence=','.join(r['evidence'][:12]) + (' (+%d)' % (len(r['evidence']) - 12)
                                                              if len(r['evidence']) > 12 else ''),
                        blockers=','.join(r['blockers']), file_count=len(r['files']),
                        mergeable_runs='|'.join(';'.join(x) for x in r['mergeable_runs']),
                        units=','.join(r['units'][:6]) + (' (+%d)' % (len(r['units']) - 6)
                                                          if len(r['units']) > 6 else ''),
                        member_rows=';'.join(r['member_rows']))
            fh.write('\t'.join(clean(vals[c]) for c in cols) + '\n')
    # projected source-file counts
    def project(levels, mergeable_only=False):
        parent = {p: p for p in all_paths}

        def find(x):
            while parent[x] != x:
                parent[x] = parent[parent[x]]
                x = parent[x]
            return x
        for r in rows_out:
            if r['level'] not in levels:
                continue
            if r['parent'] and r['level'] != 'inferred-weak' and 'inferred-weak' in levels:
                continue     # its weak parent covers it
            sets = ([[ctx.path_of(dict(row=x, home=x, origin='row')) for x in run] for run in r['mergeable_runs']]
                    if mergeable_only else [r['files']])
            for fs in sets:
                fs = [p for p in fs if p in parent]
                for p in fs[1:]:
                    parent[find(p)] = find(fs[0])
        return len({find(p) for p in parent})
    per_unit = []
    totals = dict(source_files_now=len(all_paths))
    for label, lv in (('proven', {'proven'}), ('proven+strong', {'proven', 'inferred-strong'}),
                      ('proven+strong+weak', set(LEVELS))):
        totals['tu_level_files_' + label] = project(lv)
        totals['mergeable_files_' + label] = project(lv, mergeable_only=True)
    # per image
    for name, d in sorted(m.units.items()):
        fns = d['functions']
        ps = {paths[(name, f['i'])] for f in fns} - {None}
        row = dict(unit=name, image=d['summary']['image'], functions=len(fns), current_files=len(ps))
        for lvl in LEVELS:
            parent = {p: p for p in ps}

            def find(x):
                while parent[x] != x:
                    parent[x] = parent[parent[x]]
                    x = parent[x]
                return x
            for lo, hi, glvl, _ in grouped[lvl][name]:
                fs = [paths[(name, k)] for k in range(lo, hi + 1) if paths[(name, k)] in parent]
                for p in fs[1:]:
                    parent[find(p)] = find(fs[0])
            row['files_' + lvl] = len({find(p) for p in parent})
            row['groups_' + lvl] = len(grouped[lvl][name])
        per_unit.append(row)
    with open(out / 'per_image_inferred.tsv', 'w') as fh:
        cols2 = list(per_unit[0])
        fh.write('\t'.join(cols2) + '\n')
        for r in per_unit:
            fh.write('\t'.join(str(r[c]) for c in cols2) + '\n')
    cnt = Counter(r['level'] for r in rows_out)
    totals.update(groups_by_level=dict(cnt),
                  members_by_level={l: sum(r['members'] for r in rows_out if r['level'] == l and not
                                           (r['parent'] and l != 'inferred-weak')) for l in LEVELS},
                  clean_mergeable_by_level={l: sum(1 for r in rows_out if r['level'] == l and r['mergeable_runs']
                                                   and not set(r['blockers']) - SOFT) for l in LEVELS},
                  blockers=dict(Counter(b for r in rows_out for b in r['blockers'])),
                  gap_decisions=dict(Counter('%s/%s' % (d_[0], d_[1]) for d_ in dec.values())),
                  window=m.W, strong_kinds=sorted(m.strong_kinds))
    (out / 'infer_totals.json').write_text(json.dumps(totals, indent=1, sort_keys=True) + '\n')
    batches(rows_out, out)
    print(json.dumps(totals, indent=1, sort_keys=True))
    return rows_out, totals


# tools/gate/overlay_module_gate.module_recipe (with tu7's 2.6.3-G0) and the cells tu_merge can prove from
MODULE_RECIPES = ('2.7.2-cdk-G0', '2.7.2-G0', '2.7.2-cdk-G0 -O1', '2.6.3-G0')
MEMBER_CELLS = MODULE_RECIPES + ('2.7.2', '2.6.3', '2.7.2-cdk')
SLUS_RESIDENT = (0x8002D000, 0x80088760)


def load_regions(root):
    out = defaultdict(list)
    for fam in ('main', 'town', 'dungeon', 'ovmovie'):
        p = Path(root) / ('config/overlays/%s.rowbase.jsonl' % fam)
        if not p.exists():
            continue
        for line in p.read_text().splitlines():
            if line.strip().startswith('{'):
                r = json.loads(line)
                if r['base_confidence'] == 'proven':
                    out[fam].append((int(r['foff_start'], 0), int(r['foff_end'], 0), int(r['delta'], 0), r['region']))
    return out


_SRC = {}


def _named(root, path, v):
    """True when the member source spells the address as an import symbol (D_<addr>); an address
    built from a literal constant (e.g. a load base) is no import."""
    if path not in _SRC:
        p = Path(root) / path if path else None
        _SRC[path] = p.read_text(errors='replace') if p and p.is_file() else None
    t = _SRC[path]
    return True if t is None else ('D_%08X' % v) in t


def data_flags(m, regions, name, d, idx, paths=None):
    """Classify every address the members use against what tu_merge install can import."""
    fns = d['functions']
    fam = d['summary']['container']
    lo, hi = fns[idx[0]]['foff'], fns[idx[-1]]['end']
    own = [r for r in regions[fam] if r[0] <= lo and hi <= r[1]]
    if len(own) != 1:
        return {'no_proven_region'}
    rlo, rhi, delta, rname = own[0]
    elo, ehi = int(d['summary']['rdata'][0], 16), int(d['summary']['data'][1], 16)
    udelta = int(d['summary']['delta'], 16)
    flags = set()
    for k in idx:
        f = fns[k]
        for x in f['rdata'] + f['drefs'] + f['brefs'] + f.get('xrefs', []):
            v = int(x, 16)
            if rlo + delta <= v < rhi + delta or SLUS_RESIDENT[0] <= v < SLUS_RESIDENT[1]:
                continue
            if 0x80010000 <= v < 0x80010000 + 8340:
                continue                                   # SLUS-managed game-state region (runtime view)
            if paths is not None and not _named(m.root, paths.get((name, k)), v):
                continue
            if elo + udelta <= v < ehi + udelta:
                flags.add('image_data_outside_region')     # tu_merge region (widen to the link image)
                continue
            others = [r for r in regions[fam] if r[0] + r[2] <= v < r[1] + r[2] and r[3] != rname]
            if len(others) == 1:
                continue                                   # resident engine view (tu7 install)
            flags.add('main_engine_space_data' if fam == 'main' else 'bss_or_foreign_data')
    return flags


# blockers a codex lane can clear with tu_merge as extended by tu7
SOFT = {'mixed_registered_cells', 'needs_module_placements', 'member_is_placement', 'image_data_outside_region'}


def batches(rows_out, out, lo_files=10, hi_files=30):
    """Codex lane batches: disjoint mergeable groups, by confidence, one directory per batch."""
    cand = []
    for r in rows_out:
        if r['level'] == 'proven' or not r['mergeable_runs']:
            continue
        if set(r['blockers']) - SOFT:
            continue
        nfiles = sum(len(x) for x in r['mergeable_runs'])
        dirs = sorted({'/'.join(p.rsplit('/', 1)[0].split('/')[:3]) for p in r['files'] if p != '?'})
        cand.append(dict(r, nfiles=nfiles, dirkey=dirs[0] if dirs else '?'))
    # a weak group that contains strong groups is batched after them; never both
    strong_members = {x for r in cand if r['level'] == 'inferred-strong' for run in r['mergeable_runs'] for x in run}
    cand = [r for r in cand if r['level'] == 'inferred-strong' or
            not ({x for run in r['mergeable_runs'] for x in run} & strong_members)]
    out_rows = []
    for level in ('inferred-strong', 'inferred-weak'):
        by_dir = defaultdict(list)
        for r in cand:
            if r['level'] == level:
                by_dir[(r['container'], r['dirkey'])].append(r)
        k = 0
        for (cont, dk), rs in sorted(by_dir.items(), key=lambda kv: -sum(r['nfiles'] for r in kv[1])):
            rs.sort(key=lambda r: r['group_id'])
            cur, n = [], 0
            for r in rs:
                if cur and n + r['nfiles'] > hi_files:
                    out_rows.append((level, cont, dk, cur, n))
                    cur, n = [], 0
                cur.append(r)
                n += r['nfiles']
            if cur:
                out_rows.append((level, cont, dk, cur, n))
    # pack small directory batches of one level and container together (up to hi_files)
    packed = []
    for level in ('inferred-strong', 'inferred-weak'):
        big = [x for x in out_rows if x[0] == level and x[4] >= lo_files]
        small = sorted((x for x in out_rows if x[0] == level and x[4] < lo_files), key=lambda x: (x[1], -x[4]))
        for _, cont, dk, rs, n in big:
            packed.append(dict(level=level, container=cont, dirs=[dk], groups=list(rs), files=n))
        cur = None
        for _, cont, dk, rs, n in small:
            if cur and cur['container'] == cont and cur['files'] + n <= hi_files:
                cur['groups'] += rs
                cur['files'] += n
                cur['dirs'].append(dk)
            else:
                cur = dict(level=level, container=cont, dirs=[dk], groups=list(rs), files=n)
                packed.append(cur)
    with open(out / 'batches.tsv', 'w') as fh:
        fh.write('batch\tlevel\tcontainer\tdirectories\tgroups\tmember_files\tfile_reduction\tgroup_ids\tsoft_blockers\n')
        for k, b in enumerate(packed, 1):
            red = sum(len(x) - 1 for r in b['groups'] for x in r['mergeable_runs'])
            soft = sorted({x for r in b['groups'] for x in r['blockers']})
            fh.write('\t'.join(map(clean, ['B%03d' % k, b['level'], b['container'], ';'.join(b['dirs']),
                                           len(b['groups']), b['files'], red,
                                           ','.join(r['group_id'] for r in b['groups']), ','.join(soft)])) + '\n')
    return packed


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=HERE.parents[1])
    ap.add_argument('--evidence', type=Path, required=True)
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--window', type=int, default=8)
    ap.add_argument('--rule', default='pd4_cl2', choices=sorted(STRONG_RULES))
    ap.add_argument('--strong-kinds', default='XB', help='join kinds that alone are strong')
    ap.add_argument('--validate', action='store_true', help='also write validation.json')
    args = ap.parse_args(argv)
    args.out.mkdir(parents=True, exist_ok=True)
    strong = [x for x in args.strong_kinds.split(',') if x]
    m = Model(args.evidence, args.root, window=args.window, strong_kinds=strong, rule=args.rule)
    ev = m.gap_evidence()
    dec = m.decide(ev)
    emit(m, ev, dec, args.out)
    if args.validate:
        v = validate(args.evidence, args.root, args.window, strong, args.rule)
        (args.out / 'validation.json').write_text(json.dumps(v, indent=1, sort_keys=True) + '\n')
        print(json.dumps(v, indent=1, sort_keys=True))
    return 0


if __name__ == '__main__':
    sys.exit(main())
