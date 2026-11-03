#!/usr/bin/env python3
"""Static votes for the type-flow solver: typed anchors label holders the runtime never reached.

    type_flow_static.py census    --graph G --rt RT --out DIR [--respell hidden_edges.tsv] [--kinds kinds.json]
    type_flow_static.py calibrate --graph G --rt RT --out DIR [--respell ...] [--kinds ...]
    type_flow_static.py dryrun    --graph G --rt RT --out DIR [--respell ...] [--kinds ...]
                                  [--seed-tsv ...] [--rt-seeds] [--scope ...] [--no-static]
    type_flow_static.py yield     --graph G --solve DIR [--baseline DIR] [--views views.tsv] --out DIR
    type_flow_static.py select    --solve DIR --baseline DIR [--scope src/town ...] [--max-files 40] --out batches.txt

The runtime solver (type_flow_solve.py) labels a holder with the heap / RAM cells the native port saw in it and
proves every cast it keeps or adds against those cells.  A function the campaign never ran, or a line it never
reached, has no cells: nothing seeds it and every cast in it is `unproven`, so no component through it is whole.
This module adds STATIC cells for exactly those holders, from the declared types around them, without changing
what the runtime decides.

Anchors (an edge between an open holder X - int, void *, byte / scalar pointer, generated S_ view - with no runtime
cells and a holder Y whose declared type is a named record pointer, or which carries runtime cells of one type):
  slot_rt      X = P:cb#j of a callback installed into a slot whose parameter j carries the runtime cells of the
               slot's other callbacks (one type, share >= 0.75)                                     strong
  slot_typed   X = P:cb#j, the slot's declared function-pointer type names parameter j              strong
  caller_all   X = P:f#i and every argument edge into it passes the same named type                 strong
  kind         X = arg0 of an update callback in a static object kind (object_kinds.py) whose other
               callbacks' arg0 carry one type (runtime or declared)                                 strong
  rt_flow      Y is an open holder with runtime cells of one type (a caller that ran, an unreached line)  strong
  caller       a typed argument into X (not every caller typed)                                     medium
  callee       X is passed to a parameter declared with a named type                                medium
  return       X <- R:g with a named return type                                                    medium
  returned     X = R:f returns a holder of a named type                                             medium
  member       X <- F:Rec.m (a named member type) / X stored into it                                 medium
  store        X = F:Rec.m (an open member) <- a holder of a named type                             medium
  global       X <- G:sym / &G:sym of a named type                                                  medium
  flow         X <- a local or parameter of a named type (init / assign in one function)            medium
  cmp          X compared with a holder of a named type                                             weak
An edge whose explicit pointer cast names another record is no anchor (the source spells a different object); a
cast to a generated view, void * or a byte pointer is.  Offset edges (X = Y + K) anchor X at (T, K): the cell is
typed only where T has an embedded record at K.

Propagation: each anchored holder passes its anchors along coupling edges (offset 0, the solver's own adjacency)
to open holders without runtime cells, up to 4 hops.  It stops at runtime-labelled holders, at holders whose own
direct anchors disagree, and at generic hubs (a void * parameter whose body never views it, or more than 12
coupling edges).

Admission (a label becomes static cells only when):
  - every anchor reaching the holder names the same type (else `static_mixed`: one cell per type, so the solver's
    polymorphism check makes the holder a boundary), and
  - one strong anchor reaches it, or two independent anchors (different anchor holders in different functions,
    or of different kinds).  Weak anchors never admit alone.
Admitted labels become cells ('static', T, off) voted by T (each anchor holder one voter).  Runtime cells always
win: a holder with runtime cells never gets static cells, static cells never retype a named declaration (only
open holders are labelled), and a static label that disagrees with a neighbour's runtime type stops that
component growing (runtime_other boundary).  A cast proved only by static cells has evidence `static_ok`; a
component that is whole only with such evidence is `static_whole` (bridge: `static_bridge`).

calibrate: leave-one-out against the runtime: for every open parameter that HAS runtime cells, the anchors it would
get with its own cells hidden, compared with its runtime type - precision per anchor kind and per admission rule.
"""
from __future__ import annotations

import argparse
import collections
import csv
import json
import os
from pathlib import Path
import re
import sys

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent)]
import type_flow_solve as S  # noqa: E402

STRONG = {'slot_rt', 'slot_typed', 'caller_all', 'kind', 'rt_flow'}
MEDIUM = {'caller', 'callee', 'return', 'returned', 'member', 'store', 'global', 'slot_cb'}
WEAK = {'cmp', 'flow'}          # flow: calibration precision 0.46 (local-to-local spellings disagree)
PROP_HOPS = int(os.environ.get('TYPE_FLOW_STATIC_HOPS', '4'))
HUB_DEGREE = 12
OPEN = S.OPEN
BaseRuntime = S.Runtime           # captured before a static dryrun swaps S.Runtime


# --------------------------------------------------------------------------- installer respelling (simulation)

def load_respell(path, only=('data_alias',)):
    """hidden_edges.tsv rows (installer_file, installer, callback_file, callback, source_spelling, name_used)."""
    rows = []
    for r in csv.DictReader(open(path), delimiter='\t'):
        if r.get('source_spelling') in only and r.get('name_used'):
            rows.append(r)
    return rows


def respell_installs(g, rows):
    """Rewrite an installer's `&alias` / `alias` value into the callback designator it names (FN:<key>), as the
    installer-names respelling will.  Returns (rewritten edges, rows matched)."""
    by_file = collections.defaultdict(list)
    for i, e in enumerate(g.edges):
        if e.get('src'):
            by_file[e['file']].append(i)
    done, matched = 0, 0
    for r in rows:
        cb = S.fn_key(g, r['callback'], r['callback_file'])
        if not g.fn_def(cb):
            continue
        name = r['name_used']
        want = {'G:' + name, '&G:' + name, '&G:' + name + '[]'}
        hit = False
        for i in by_file.get(r['installer_file'], ()):
            e = g.edges[i]
            if e['src'] in want and e['fn'].split('@')[0] == r['installer']:
                e['src'] = '&FN:' + cb
                e['respelled'] = name
                done += 1
                hit = True
        matched += hit
    return done, matched


# --------------------------------------------------------------------------- anchors

def canon(g, t):
    r = g.resolve(t) if t else ''
    return r if r.endswith('*') and r[:-1].startswith('rec:') and not r.endswith('**') else None


def node_fn(node):
    if node.startswith(('P:', 'R:', 'L:')):
        body = node[2:]
        return body.rpartition('#')[0] if node.startswith('P:') else body.split(':')[0]
    return ''


class Labeller:
    """Anchors and propagated static labels over one solver's adjacency."""

    def __init__(self, g, rt, solver, kinds=None, blind=None):
        self.g, self.rt, self.S = g, rt, solver
        self.blind = blind              # calibration: the node whose own runtime cells are hidden
        self.kinds = kinds or {}
        self._rt_type = {}
        self._hub = {}

    # runtime identity of a holder, read through the base class (never through the static wrapper / caches)
    def rt_cells(self, node):
        if node == self.blind or (self.blind == '*' and self.is_open(node)):
            return collections.Counter()
        return BaseRuntime.pointer_cells(self.rt, node)

    def rt_type(self, node):
        if node in self._rt_type:
            return self._rt_type[node]
        cells = self.rt_cells(node)
        tv = collections.Counter()
        for cell, n in cells.items():
            w, _ = BaseRuntime.winner(self.rt, cell)
            if w:
                tv[w] += n
        res = None
        if tv:
            best = max(tv, key=lambda t: (tv[t], t))
            share = tv[best] / sum(tv.values())
            res = (best, share, bool(cells))
        elif cells:
            res = (None, 0.0, True)
        self._rt_type[node] = res
        return res

    def decl(self, node, e=None):
        g = self.g
        d = g.declared(node)
        if not d and e is not None:
            d = e.get('dt') if e['dst'] == node else e.get('st')
        return d or ''

    def is_open(self, node, e=None):
        if S.is_fn(node) or node.startswith('&'):
            return False
        return self.g.cls(self.decl(node, e)) in OPEN

    def labelable(self, node, e=None):
        return self.is_open(node, e) and not self.rt_cells(node)

    def spelled_other(self, e, t):
        """The edge spells a cast to a named record other than t: not an anchor."""
        for c in list(e.get('casts') or []) + list(e.get('acasts') or []):
            if '*' not in c:
                continue
            ct = canon(self.g, c)
            if ct and self.g.cls(c) == 'real' and ct != t:
                return True
        return False

    def anchor_kind(self, x, y, e, kind):
        if kind == 's':
            return 'slot'
        k = e['k']
        if k == 'cmp':
            return 'cmp'
        if k == 'arg':
            if e['dst'] == x and x.startswith('P:'):
                return 'caller'
            if e['dst'] == y and y.startswith('P:'):
                return 'callee'
            if re.search(r'#\d+$', e['dst']):
                return 'callee' if e['dst'] == y else 'caller'
            return 'flow'
        if k == 'ret':
            return 'returned' if x.startswith('R:') else 'return'
        if y.startswith('R:'):
            return 'return'
        if y.startswith(('F:', '&F:')):
            return 'member'
        if x.startswith('F:'):
            return 'store'
        if y.startswith(('G:', '&G:')):
            return 'global'
        return 'flow'

    def direct_for(self, x):
        """[(type, anchor holder, kind, off)] of one labelable holder: its typed neighbours."""
        g, S_ = self.g, self.S
        res = []
        for kind, i, y in S_.adj.get(x, ()):
            e = g.edges[i]
            if kind == 'e' and e['k'] not in ('init', 'assign', 'arg', 'ret', 'cmp'):
                continue
            if not self.labelable(x, e if kind == 'e' else None):
                return []
            t, ak = None, None
            dy = self.decl(y, e if kind == 'e' else None)
            if g.cls(dy) == 'real':
                t = canon(g, dy)
                ak = self.anchor_kind(x, y, e, kind)
                if ak == 'slot':
                    if x.startswith('P:') and not y.startswith('P:'):
                        ak = 'slot_typed'        # the slot's declared parameter type
                    elif y.startswith('P:') and not x.startswith('P:'):
                        ak = 'slot_cb'           # the slot parameter, typed by one installed callback
                    else:
                        ak = 'flow'
            else:
                r = self.rt_type(y)
                if r and r[0] and r[1] >= 0.75:
                    t = r[0]
                    ak = 'slot_rt' if kind == 's' and x.startswith('P:') else 'rt_flow'
            if not t or not ak or (kind == 'e' and self.spelled_other(e, t)):
                continue
            res.append((t, y, ak, 0))
        for i in S_.offset_adj.get(x, ()):
            e = g.edges[i]
            if e['dst'] != x or not e.get('src') or e['off'] <= 0 or not self.labelable(x, e):
                continue
            y = e['src']
            dy = self.decl(y, e)
            if g.cls(dy) != 'real':
                continue
            t = canon(g, dy)
            if not t or self.spelled_other(e, t):
                continue
            size = g.size(t[4:-1]) or 0
            off = e['off'] % size if size else e['off']
            res.append((t, y, 'caller' if e['k'] == 'arg' else 'flow', off))
        # caller_all: every argument edge into an open parameter passes the same named type
        if x.startswith('P:') and res:
            incoming = [g.edges[i] for k, i, _ in S_.adj.get(x, ()) if k == 'e' and g.edges[i]['k'] == 'arg'
                        and g.edges[i]['dst'] == x]
            typed = {(y, t) for t, y, k, o in res if k in ('caller', 'rt_flow') and o == 0}
            srcs = {y for y, _ in typed}
            if incoming and len({t for _, t in typed}) == 1 and all(e['src'] in srcs for e in incoming):
                res = [(t, y, 'caller_all' if k == 'caller' else k, o) for t, y, k, o in res]
        if x in self.kinds and self.labelable(x):
            t, voters = self.kinds[x]
            res.append((t, 'kind:' + voters, 'kind', 0))
        return res

    def direct(self):
        """node -> [(type, anchor_id, kind, off)] for every labelable holder with a typed neighbour."""
        out = {}
        for x in set(self.S.adj) | set(self.S.offset_adj) | set(self.kinds):
            if x.startswith(('P:', 'L:', 'F:', 'R:')) or re.search(r'#(\d+|ret)$', x):
                r = self.direct_for(x)
                if r:
                    out[x] = r
        return out

    def hub(self, node, anchors):
        if node in self._hub:
            return self._hub[node]
        self._hub[node] = h = self._hub_(node, anchors)
        return h

    def _hub_(self, node, anchors):
        g = self.g
        if len({a[0] for a in anchors.get(node, ()) if a[2] not in WEAK}) > 1:
            return True
        deg = len(self.S.adj.get(node, ()))
        if deg > HUB_DEGREE:
            return True
        if g.cls(g.declared(node)) == 'void' and node.startswith('P:'):
            # a void * parameter its own body never views: generic (memset-like) - it may carry anything
            if not any(u['ctx'] in ('member', 'raw') for u in g.by_node_uses.get(node, ())):
                return True
        return False

    def label(self):
        """node -> {'anchors': [(type, anchor, kind, off, hops)], ...} for direct and propagated labels."""
        direct = self.direct()
        labels = collections.defaultdict(list)
        for x, anchors in direct.items():
            for t, y, k, off in anchors:
                labels[x].append((t, y, k, off, 0))
        for x, anchors in direct.items():
            if self.hub(x, direct):
                continue
            items = [(t, y, k, off) for t, y, k, off in anchors if off == 0 and k not in WEAK]
            if not items:
                continue
            seen = {x}
            frontier = [x]
            for hop in range(1, PROP_HOPS + 1):
                nxt = []
                for n in frontier:
                    for kind, i, m in self.S.adj.get(n, ()):
                        if m in seen:
                            continue
                        e = self.g.edges[i]
                        if kind == 'e' and e['k'] not in ('init', 'assign', 'arg', 'ret'):
                            continue
                        if not self.labelable(m, e if kind == 'e' else None):
                            continue
                        if kind == 'e' and any(self.spelled_other(e, t) for t, _, _, _ in items):
                            continue
                        seen.add(m)
                        for t, y, k, off in items:
                            labels[m].append((t, y, k, off, hop))
                        if not self.hub(m, direct):
                            nxt.append(m)
                frontier = nxt
                if not frontier:
                    break
        return labels


def admit(g, anchors):
    """(status, type, reason) of one holder's anchors: admitted / mixed / single / weak."""
    by_type = collections.defaultdict(list)
    for t, y, k, off, hop in anchors:
        if k in WEAK:
            continue
        by_type[(t, off)].append((y, k, hop))
    if not by_type:
        return 'weak', None, 'weak_only'
    if len({t for t, _ in by_type}) > 1 or len(by_type) > 1:
        return 'mixed', None, 'anchors_disagree'
    (t, off), items = next(iter(by_type.items()))
    kinds = {k for _, k, _ in items}
    if kinds & STRONG:
        return 'admitted', (t, off), 'strong:' + ','.join(sorted(kinds & STRONG))
    anchors_ = {y for y, _, _ in items}
    fns = {node_fn(y) for y in anchors_}
    if len(anchors_) >= 2 and (len(fns) >= 2 or len(kinds) >= 2):
        return 'admitted', (t, off), 'independent:' + ','.join(sorted(kinds))
    return 'single', (t, off), 'single:' + ','.join(sorted(kinds))


def primary_kind(anchors):
    ks = {k for _, _, k, _, _ in anchors}
    for k in ('slot_rt', 'slot_typed', 'kind', 'caller_all', 'rt_flow', 'caller', 'callee', 'member', 'store',
              'return', 'returned', 'global', 'flow', 'slot_cb', 'cmp'):
        if k in ks:
            return k
    return '?'


# --------------------------------------------------------------------------- object kinds (static)

def load_kinds(path, g, rt):
    """object_kinds.py report kinds.json -> {P:cb#0: (type, voters)} for kinds whose other callbacks' arg0 agree."""
    out = {}
    if not path:
        return out
    data = json.load(open(path))
    kinds = data['kinds'] if isinstance(data, dict) and 'kinds' in data else data
    for k in kinds:
        nodes = []
        for c in k.get('callbacks', []):
            if c.get('role') != 'update':
                continue
            name = c['func'].split('@')[0]
            key = S.fn_key(g, name, c.get('file', ''))
            if g.fn_def(key):
                nodes.append('P:%s#0' % key)
        if len(nodes) < 2:
            continue
        votes = collections.Counter()
        for n in nodes:
            d = g.declared(n)
            cells = BaseRuntime.pointer_cells(rt, n)
            if cells:
                tv = collections.Counter()
                for cell, cnt in cells.items():
                    w, _ = BaseRuntime.winner(rt, cell)
                    if w:
                        tv[w] += cnt
                if tv:
                    votes[max(tv, key=lambda t: (tv[t], t))] += 1
            elif g.cls(d) == 'real':
                votes[canon(g, d)] += 1
        votes.pop(None, None)
        if len(votes) != 1:
            continue
        t = next(iter(votes))
        for n in nodes:
            out[n] = (t, '%s(%d)' % (k.get('kind', '?'), votes[t]))
    return out


# --------------------------------------------------------------------------- solver integration

class StaticRuntime(BaseRuntime):
    """Runtime whose open, unlabelled holders may carry admitted static cells ('static', T, off)."""

    static_cells = {}
    static_votes = {}

    def pointer_cells(self, node):
        c = BaseRuntime.pointer_cells(self, node)
        if c or not self.static_cells:
            return c
        s = self.static_cells.get(node)
        return collections.Counter(s) if s else c

    def cell_votes(self, cell):
        if cell[0] != 'static':
            return BaseRuntime.cell_votes(self, cell)
        t, off = cell[1], cell[2]
        voters = self.static_votes.get((t, 0)) or {'static'}
        if off == 0:
            return {t: voters}
        g = self.g
        rec = t[4:-1]
        emb = {g.resolve(ft) + '*' for _, ft in g.leaves(rec, off)
               if g.cls(ft) == 'record' and g.cls(g.resolve(ft) + '*') == 'real'}
        return {v: voters for v in emb}

    def cast_ok(self, cells, off, t):
        v = BaseRuntime.cast_ok(self, cells, off, t)
        if v == 'correct' and cells and all(c[0] == 'static' for c in cells):
            return 'static_ok'
        return v


def install_static(g, rt, solver, kinds=None, out=None):
    """Label, admit and attach static cells to rt; returns (labels, admitted rows)."""
    lab = Labeller(g, rt, solver, kinds=kinds)
    labels = lab.label()
    cells, votes, rows = {}, collections.defaultdict(set), []
    for node, anchors in labels.items():
        status, tt, reason = admit(g, anchors)
        rows.append({'node': node, 'status': status, 'type': S.canon_display(g, tt[0]) if tt else '',
                     'off': '0x%X' % tt[1] if tt else '', 'reason': reason, 'kind': primary_kind(anchors),
                     'anchors': len({a[1] for a in anchors}), 'min_hops': min(a[4] for a in anchors),
                     'declared': g.declared(node), 'file': g.home(node) or '',
                     'anchor_list': ' '.join(sorted({'%s:%s' % (a[2], a[1]) for a in anchors})[:6])})
        if status == 'admitted':
            t, off = tt
            cells[node] = {('static', t, off): len({a[1] for a in anchors})}
            votes[(t, 0)].update('static:' + a[1] for a in anchors)
        elif status == 'mixed':
            ts = {(a[0], a[3]) for a in anchors if a[2] not in WEAK}
            cells[node] = {('static', t, off): 1 for t, off in ts}
            for t, off in ts:
                votes[(t, 0)].add('static:mixed')
    rt.static_cells = cells
    rt.static_votes = dict(votes)
    return labels, rows


def static_seeds(g, rt, rows):
    """Seeds for admitted open parameters and for admitted locals the body views (casts to fold)."""
    seeds = []
    for r in rows:
        if r['status'] != 'admitted' or r['off'] != '0x0':
            continue
        n = r['node']
        if n.startswith('P:'):
            key, _, i = n[2:].rpartition('#')
            d = g.fn_def(key)
            if not d or not i.isdigit():
                continue
            seeds.append({'src': 'static:' + r['kind'], 'file': d['file'], 'function': key.split('@')[0],
                          'arg': i, 'target': r['type'], 'hold': 'static', 'reason': r['reason'],
                          'cur': g.declared(n), 'node_key': n})
        elif n.startswith('L:') and g.by_node_uses.get(n):
            key = n[2:].split(':')[0]
            d = g.fn_def(key)
            if not d:
                continue
            seeds.append({'src': 'static:' + r['kind'], 'file': d['file'], 'function': key.split('@')[0],
                          'arg': n.split(':', 2)[2], 'target': r['type'], 'hold': 'static', 'reason': r['reason'],
                          'cur': g.declared(n), 'node_key': n})
    return seeds


def static_verdict(base):
    def verdict_of(g, rt, seeds_here, comp, res):
        v, changed = base(g, rt, seeds_here, comp, res)
        if v not in ('whole', 'bridge'):
            return v, changed
        static_ev = res['evidence'].get('static_ok', 0)
        static_nodes = [n for n in changed if getattr(rt, 'static_cells', {}).get(n)
                        and not BaseRuntime.pointer_cells(rt, n)]
        static_seed = any(str(s.get('src', '')).startswith('static:') for s in seeds_here)
        unproven_rt = [n for n in changed if not BaseRuntime.pointer_cells(rt, n) and not rt.static_cells.get(n)]
        if static_ev or static_nodes or static_seed:
            res['reasons'].add('static_evidence')
            res['static_nodes'] = len(static_nodes)
            res['unlabelled_nodes'] = len(unproven_rt)
            return 'static_' + v, changed
        return v, changed
    return verdict_of


def run_dryrun(a):
    """type_flow_solve.dryrun_main with static cells and seeds (and optionally the respelled installers)."""
    respell = load_respell(a.respell) if a.respell else []
    stats = {}
    orig = (S.Graph, S.Runtime, S.Solver, S.rt_seeds, S.verdict_of)

    class G2(orig[0]):
        def __init__(self, gdir):
            super().__init__(gdir)
            if respell:
                stats['respelled_edges'], stats['respell_rows_matched'] = respell_installs(self, respell)
                stats['respell_rows'] = len(respell)

    class Solver2(orig[2]):
        def __init__(self, g, rt):
            super().__init__(g, rt)
            if getattr(a, 'no_static', False) or getattr(rt, '_static_done', False):
                return
            rt._static_done = True
            kinds = load_kinds(a.kinds, g, rt) if a.kinds else {}
            labels, rows = install_static(g, rt, self, kinds=kinds)
            rt._static_rows = rows
            out = Path(a.out)
            out.mkdir(parents=True, exist_ok=True)
            S.write_tsv(out / 'static_labels.tsv', rows, ['node', 'status', 'type', 'off', 'reason', 'kind',
                                                         'anchors', 'min_hops', 'declared', 'file', 'anchor_list'])
            stats['labels'] = dict(collections.Counter(r['status'] for r in rows))
            stats['admitted_by_kind'] = dict(collections.Counter(r['kind'] for r in rows if r['status'] == 'admitted'))

    def rt_seeds2(g, rt, S0, share=0.75):
        extra, notes = (orig[3](g, rt, S0, share) if a.rt_seeds_orig else ([], []))
        if not getattr(a, 'no_static', False):
            have = {s['node_key'] for s in extra}
            st = [s for s in static_seeds(g, rt, getattr(rt, '_static_rows', [])) if s['node_key'] not in have]
            stats['static_seeds'] = len(st)
            extra = extra + st
        return extra, notes

    S.Graph, S.Runtime, S.Solver, S.rt_seeds = G2, StaticRuntime, Solver2, rt_seeds2
    S.verdict_of = static_verdict(orig[4])
    try:
        a.rt_seeds_orig = a.rt_seeds
        a.rt_seeds = True                  # the hook adds the static seeds; runtime seeds only when asked
        S.dryrun_main(a)
    finally:
        S.Graph, S.Runtime, S.Solver, S.rt_seeds, S.verdict_of = orig
    (Path(a.out) / 'static_stats.json').write_text(json.dumps(stats, indent=1))
    print(json.dumps(stats, indent=1))


# --------------------------------------------------------------------------- census / calibration

def load_base(a):
    g = S.Graph(a.graph)
    stats = {}
    if getattr(a, 'respell', None):
        rows = load_respell(a.respell)
        stats['respelled_edges'], stats['respell_rows_matched'] = respell_installs(g, rows)
        stats['respell_rows'] = len(rows)
    rt = StaticRuntime(a.rt, g)
    solver = S.Solver(g, rt)
    return g, rt, solver, stats


def census_main(a):
    g, rt, solver, stats = load_base(a)
    out = Path(a.out)
    out.mkdir(parents=True, exist_ok=True)
    kinds = load_kinds(a.kinds, g, rt) if a.kinds else {}
    labels, rows = install_static(g, rt, solver, kinds=kinds)
    S.write_tsv(out / 'static_labels.tsv', rows)
    # open holders with no runtime identity, by node class
    lab = Labeller(g, rt, solver)
    open_nodes = collections.Counter()
    for n in set(solver.adj) | set(g.decl):
        if n.startswith(('P:', 'L:', 'F:', 'R:')) and lab.labelable(n):
            open_nodes[n[0]] += 1
    summary = dict(stats, open_unlabelled=dict(open_nodes),
                   labels=dict(collections.Counter(r['status'] for r in rows)),
                   by_kind={k: dict(collections.Counter(r['status'] for r in rows if r['kind'] == k))
                            for k in sorted({r['kind'] for r in rows})},
                   by_node=dict(collections.Counter((r['node'][0], r['status']) for r in rows).most_common()))
    summary['by_node'] = {'%s/%s' % k: v for k, v in collections.Counter(
        (r['node'][0], r['status']) for r in rows).items()}
    # functions the campaign ran (entry cells or a call site seen) vs never ran
    ran = {node_fn(n) for n in rt.cells} | {k[0] for k in rt.site} | {k[2] for k in rt.site}
    defs = {k for k in g.functions}
    never = defs - ran
    summary['functions'] = {'defined': len(defs), 'ran': len(defs & ran), 'never_ran': len(never)}
    split = collections.defaultdict(collections.Counter)
    for r in rows:
        f = node_fn(r['node'])
        if not f:
            where = 'member/global'
        else:
            where = 'never_ran_fn' if f in never else 'ran_fn'
        split[where][r['status']] += 1
        if r['status'] == 'admitted':
            split[where + ':admitted_by_kind:' + r['kind']]['n'] += 1
    open_never = collections.Counter()
    for n in set(solver.adj) | set(g.decl):
        f = node_fn(n)
        if f in never and n.startswith(('P:', 'L:', 'R:')) and lab.labelable(n):
            open_never[n[0]] += 1
    summary['open_holders_in_never_ran_functions'] = dict(open_never)
    summary['labels_by_runtime_reach'] = {k: dict(v) for k, v in sorted(split.items())}
    (out / 'census.json').write_text(json.dumps(summary, indent=1))
    print(json.dumps(summary, indent=1))


def calibrate_main(a):
    """Precision of static labels against the runtime, on open parameters that HAVE a runtime type (share >= 0.75).

    leave_one_out: hide one parameter's own cells; its direct anchors (runtime neighbours allowed) vs its type.
    leave_all_out: hide the runtime identity of every open holder (a never-run region: no rt_flow / slot_rt
    anchors survive), label and propagate as for real, compare every admitted parameter with its type.
    agree = the runtime winner, coview = a type the solver's cast evidence already accepts for those cells (>= 25%
    of the votes), disagree = anything else."""
    g, rt, solver, stats = load_base(a)
    out = Path(a.out)
    out.mkdir(parents=True, exist_ok=True)
    kinds = load_kinds(a.kinds, g, rt) if a.kinds else {}
    lab0 = Labeller(g, rt, solver, kinds=kinds)
    truth = {}
    for n in rt.cells:
        if lab0.is_open(n):
            r = lab0.rt_type(n)
            if r and r[0] and r[1] >= 0.75:
                truth[n] = r[0]

    def grade(n, t):
        if t == truth[n]:
            return 'agree'
        cells = BaseRuntime.pointer_cells(rt, n)
        return 'coview' if BaseRuntime.cast_ok(rt, cells, 0, S.canon_display(g, t)) == 'correct' else 'disagree'

    def prec(c):
        tot = c['agree'] + c['coview'] + c['disagree']
        return {'agree': c['agree'], 'coview': c['coview'], 'disagree': c['disagree'],
                'precision': round(c['agree'] / tot, 3) if tot else None,
                'precision_with_coview': round((c['agree'] + c['coview']) / tot, 3) if tot else None}
    rows = []
    summary = {'targets': len(truth)}
    for mode in ('leave_one_out', 'leave_all_out'):
        per_kind = collections.defaultdict(collections.Counter)
        per_rule = collections.defaultdict(collections.Counter)
        if mode == 'leave_all_out':
            lab = Labeller(g, rt, solver, kinds=kinds, blind='*')
            labels = lab.label()
        for n in sorted(truth):
            if mode == 'leave_one_out':
                lab = Labeller(g, rt, solver, kinds=kinds, blind=n)
                anchors = [(t, y, k, off, 0) for t, y, k, off in lab.direct_for(n)]
            else:
                anchors = labels.get(n, [])
            for t, y, k, off, hop in anchors:
                if off == 0 and hop == 0:
                    per_kind[k][grade(n, t)] += 1
            status, tt, reason = admit(g, anchors)
            per_rule['status:' + status]['n'] += 1
            if status == 'admitted':
                gr = grade(n, tt[0]) if tt[1] == 0 else 'disagree'
                per_rule['rule:' + reason.split(':')[0]][gr] += 1
                per_rule['primary:' + primary_kind(anchors)][gr] += 1
                per_rule['hops:%d' % min(x[4] for x in anchors)][gr] += 1
                per_rule['all_admitted'][gr] += 1
            rows.append({'mode': mode, 'node': n, 'runtime': S.canon_display(g, truth[n]), 'status': status,
                         'static': S.canon_display(g, tt[0]) if tt else '', 'reason': reason,
                         'grade': grade(n, tt[0]) if tt and status == 'admitted' else '',
                         'kinds': ','.join(sorted({x[2] for x in anchors}))})
        summary[mode] = {'per_anchor_kind': {k: prec(v) for k, v in sorted(per_kind.items())},
                         'per_admission': {k: (prec(v) if 'n' not in v else dict(v)) for k, v in sorted(per_rule.items())}}
    S.write_tsv(out / 'calibration.tsv', rows)
    (out / 'calibration.json').write_text(json.dumps(summary, indent=1))
    print(json.dumps(summary, indent=1))


# --------------------------------------------------------------------------- yield (casts, layouts, D11 views)

GEN_NAME = re.compile(r'\b(S_(?:func_)?[0-9A-Fa-f]{6,8}(?:_\d+)?)\b')


def yield_main(a):
    g = S.Graph(a.graph)
    solve = Path(a.solve)
    Path(a.out).mkdir(parents=True, exist_ok=True)
    comps = list(csv.DictReader(open(solve / 'components.tsv'), delimiter='\t'))
    base = {}
    if a.baseline:
        for r in csv.DictReader(open(Path(a.baseline) / 'seeds.tsv'), delimiter='\t'):
            base[r.get('node') or ''] = r.get('outcome', '')
    labels = {}
    lp = Path(a.labels) if a.labels else solve / 'static_labels.tsv'
    if lp.exists():
        for r in csv.DictReader(open(lp), delimiter='\t'):
            labels[r['node']] = r
    accept = set(a.accept)
    by_folder = collections.defaultdict(collections.Counter)
    retyped = {}
    new_whole = collections.Counter()
    for r in comps:
        v = r['verdict']
        f = S.folder(r['folder_list'].split(' ')[0]) if r['folder_list'] else ''
        sub = '/'.join((r['folder_list'].split(' ')[0] or '').split('/')[:3])
        by_folder[sub][v] += 1
        if v in accept:
            by_folder[sub]['net_' + v] += int(r['net'])
            p = solve / 'components' / (r['component'] + '.json')
            if p.exists():
                d = json.load(open(p))
                for n, x in d['comp'].items():
                    if x.get('st') == 'retype':
                        retyped[n] = x.get('t')
                fresh = [sd for sd in d['seeds'] if not str(base.get(sd.get('node'), '')).startswith('whole')]
                if fresh or not base:
                    new_whole[v] += 1
    # generated views: uses on retyped nodes that the new type absorbs (member at the same offset) vs all uses
    uses_by_view = collections.defaultdict(list)
    for u in g.uses:
        if u['ctx'] != 'member':
            continue
        m = GEN_NAME.search(u.get('cast') or '')
        if m:
            uses_by_view[m.group(1)].append(u)
    decl_by_view = collections.defaultdict(set)
    for n, c in g.decl.items():
        for t in c:
            m = GEN_NAME.search(t)
            if m and n.startswith(('P:', 'L:', 'R:', 'F:')):
                decl_by_view[m.group(1)].add(n)
    views = {}
    if a.views:
        for r in csv.DictReader(open(a.views), delimiter='\t'):
            views[r['name']] = r
    rows = []
    gained = collections.Counter()
    gained_by = collections.defaultdict(collections.Counter)
    retire = collections.Counter()
    for name in sorted(set(uses_by_view) | set(decl_by_view)):
        us = uses_by_view.get(name, [])
        on_static = [u for u in us if (labels.get(u['node']) or {}).get('status') == 'admitted']
        decl_static = [n for n in decl_by_view.get(name, ()) if (labels.get(n) or {}).get('status') == 'admitted']
        hit = 0
        for u in us:
            tau = retyped.get(u['node'])
            if not tau:
                continue
            rec, vrec = g.record_of(tau), g.record_of(u['cast'])
            if g.same(u['cast'], tau) and u['off'] == 0:
                hit += 1
            elif rec and vrec and g.records.get(vrec):
                mo = [f[1] for f in g.records[vrec]['fields'] if f[0] == u['member']]
                hit += bool(mo and g.member_at(rec, u['off'] + mo[0], u['mtype']))
        decls_left = [n for n in decl_by_view.get(name, ()) if n not in retyped]
        retired = bool(us or decl_by_view.get(name)) and hit == len(us) and not decls_left
        vr = views.get(name) or {}
        rule = vr.get('rule', '')
        kinds = collections.Counter((labels.get(u['node']) or {}).get('kind', '') for u in on_static)
        kinds.update((labels.get(n) or {}).get('kind', '') for n in decl_static)
        row = {'view': name, 'rule': rule, 'blocker': vr.get('blocker', ''), 'folder': vr.get('folder', ''),
               'uses': len(us), 'uses_static_identity': len(on_static), 'uses_absorbed': hit,
               'decls': len(decl_by_view.get(name, ())), 'decls_static_identity': len(decl_static),
               'decls_left': len(decls_left), 'retired': int(retired),
               'anchor_kind': kinds.most_common(1)[0][0] if kinds else ''}
        rows.append(row)
        if on_static or decl_static:
            gained[rule or 'not_in_views'] += 1
            gained_by[rule or 'not_in_views'][row['anchor_kind']] += 1
        if retired:
            retire[(rule or 'not_in_views', '/'.join((vr.get('folder') or '').split('/')[:3]))] += 1
    S.write_tsv(Path(a.out) / 'view_yield.tsv', rows)
    d11 = [r for r in rows if r['rule'] == 'D11']
    summary = {
        'components': dict(collections.Counter(r['verdict'] for r in comps)),
        'accepted_components_new': dict(new_whole),
        'net_casts': {v: sum(int(r['net']) for r in comps if r['verdict'] == v) for v in accept},
        'removed': {v: sum(int(r['removed']) for r in comps if r['verdict'] == v) for v in accept},
        'by_folder': {k: dict(v) for k, v in sorted(by_folder.items())},
        'views_with_static_identity': dict(gained),
        'views_with_static_identity_by_kind': {k: dict(v) for k, v in gained_by.items()},
        'd11_views_in_tree': len(d11), 'd11_uses': sum(r['uses'] for r in d11),
        'd11_views_gaining_identity': sum(1 for r in d11 if r['uses_static_identity'] or r['decls_static_identity']),
        'd11_views_all_holders_identity': sum(1 for r in d11 if (r['uses'] + r['decls']) and
                                              r['uses_static_identity'] + r['decls_static_identity'] == r['uses'] + r['decls']),
        'd11_decls': sum(r['decls'] for r in d11),
        'd11_decls_gaining_identity': sum(r['decls_static_identity'] for r in d11),
        'd11_uses_gaining_identity': sum(r['uses_static_identity'] for r in d11),
        'views_retired': {'%s %s' % k: v for k, v in sorted(retire.items())},
        'views_retired_total': sum(retire.values()),
    }
    Path(a.out).mkdir(parents=True, exist_ok=True)
    (Path(a.out) / 'yield.json').write_text(json.dumps(summary, indent=1))
    print(json.dumps(summary, indent=1))



# --------------------------------------------------------------------------- select (apply batches)

def select_main(a):
    """Batches of static_whole transactions for type_flow_apply.py: new components only (no seed already whole in
    the baseline solve), inside --scope, optionally without module sources or member (F:) nodes, <= --max-files
    distinct files per batch.  Writes one line of component ids per batch."""
    solve = Path(a.solve)
    base = {}
    if a.baseline:
        for r in csv.DictReader(open(Path(a.baseline) / 'seeds.tsv'), delimiter='\t'):
            base[r.get('node') or ''] = r.get('outcome', '')
    seeds = collections.defaultdict(list)
    for r in csv.DictReader(open(solve / 'seeds.tsv'), delimiter='\t'):
        seeds[r['component']].append(r)
    cands, why = [], collections.Counter()
    for c in csv.DictReader(open(solve / 'components.tsv'), delimiter='\t'):
        if c['verdict'] not in a.verdicts:
            continue
        if any(str(base.get(s['node'], '')).startswith('whole') for s in seeds[c['component']]):
            why['baseline_whole'] += 1
            continue
        d = json.load(open(solve / 'components' / (c['component'] + '.json')))
        nodes = [n for n, v in d['comp'].items() if v.get('st') == 'retype']
        files = sorted(set(d['result']['files']))
        if a.scope and not all(f.startswith(tuple(a.scope)) or f.startswith('include/') for f in files):
            why['out_of_scope'] += 1
            continue
        if not a.allow_modules and any('/modules/' in f for f in files):
            why['module_source'] += 1
            continue
        if not a.members and any(n.startswith('F:') for n in nodes):
            why['member_node'] += 1
            continue
        if any(not n.startswith(('P:', 'L:', 'F:')) or re.match(r'^P:.*#\d+#(\d+|ret)$', n) for n in nodes):
            why['manual_node'] += 1
            continue
        if len(files) > a.max_files:
            why['too_many_files'] += 1
            continue
        cands.append((int(c['net']), c['component'], files))
    cands.sort()
    batches, cur, cur_files = [], [], set()
    for net, cid, files in cands:
        if cur and len(cur_files | set(files)) > a.max_files:
            batches.append(cur)
            cur, cur_files = [], set()
        cur.append(cid)
        cur_files |= set(files)
    if cur:
        batches.append(cur)
    Path(a.out).write_text(''.join(' '.join(b) + '\n' for b in batches))
    print(json.dumps({'candidates': len(cands), 'predicted_net': sum(n for n, _, _ in cands), 'batches': len(batches),
                      'skipped': dict(why)}, indent=1))

# --------------------------------------------------------------------------- CLI

def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest='cmd', required=True)
    for name in ('census', 'calibrate', 'dryrun'):
        p = sub.add_parser(name)
        p.add_argument('--graph', required=True)
        p.add_argument('--rt', required=True)
        p.add_argument('--out', required=True)
        p.add_argument('--respell', help='hidden_edges.tsv: simulate respelled data-alias installers')
        p.add_argument('--kinds', help='object_kinds.py report kinds.json (static object kinds)')
        if name == 'dryrun':
            p.add_argument('--holds', nargs='*')
            p.add_argument('--actor-holds', nargs='*')
            p.add_argument('--grades', nargs='*', default=['A'])
            p.add_argument('--seed-tsv', nargs='*')
            p.add_argument('--rt-seeds', action='store_true')
            p.add_argument('--scope', nargs='*')
            p.add_argument('--no-static', action='store_true', help='respell only (the runtime solve)')
    y = sub.add_parser('yield')
    y.add_argument('--graph', required=True)
    y.add_argument('--solve', required=True)
    y.add_argument('--baseline')
    y.add_argument('--views')
    y.add_argument('--labels', help='static_labels.tsv (default: the solve directory\'s)')
    y.add_argument('--accept', nargs='*', default=['whole', 'static_whole'])
    y.add_argument('--out', required=True)
    q = sub.add_parser('select')
    q.add_argument('--solve', required=True)
    q.add_argument('--baseline', help='the plain runtime solve: components with a seed already whole there are skipped')
    q.add_argument('--verdicts', nargs='*', default=['static_whole'])
    q.add_argument('--scope', nargs='*')
    q.add_argument('--max-files', type=int, default=40)
    q.add_argument('--allow-modules', action='store_true')
    q.add_argument('--members', action='store_true')
    q.add_argument('--out', required=True)
    a = ap.parse_args(argv)
    if a.cmd == 'select':
        return select_main(a)
    if a.cmd == 'dryrun':
        return run_dryrun(a)
    return {'census': census_main, 'calibrate': calibrate_main, 'yield': yield_main}[a.cmd](a)


if __name__ == '__main__':
    sys.exit(main())
