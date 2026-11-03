#!/usr/bin/env python3
"""Component solver over the type-flow graph (type_flow.py graph), labelled with runtime identity.

    type_flow.py dryrun --graph DIR --rt RTDIR --holds H.tsv... [--actor-holds A.tsv...] --out DIR

Runtime labels (RTDIR = a --rtti campaign: fn_args.tsv, kinds_rt.json):
  every parameter node gets the cells it was observed carrying, (heap kind, offset) / (ram symbol, offset);
  `&G:sym` nodes carry ('ram', sym, 0).  A cell's type is voted by the declared types of every function
  observed receiving it (distinct functions; placeholders, generated views and private types do not vote), as
  opus_proto1 rt_select.  A cast `(T *)x` is *evidence-correct* when every cell x carries at that point
  (shifted by the offset added on the way) has T as its winner or as a co-view (>= 25% of the votes), or
  T is ObjectNodeHeader * at a pooled object's +0.  Byte and void pointer casts are *neutral* (layout-free).

Component: from each seed (a held (function, parameter) with its target type) the solver walks coupling
edges (offset-0 value flow: init, assign, argument, return, compare; function-pointer installs couple the
slot's parameters with the callback's).  A neighbour joins the component (retyped to the same target) when
its declared type is a placeholder (int, void *, byte / scalar pointer, generated S_ view) and it is not
polymorphic, or when it is a real type the runtime contradicts (its own cells vote for the target).  A
neighbour already of the target type is satisfied; any other neighbour is a boundary whose edge keeps or
gains a cast.  Components that share a retyped node are merged (one transaction).

Prediction per component (pointer casts as debt_check counts them: casts to a spelled pointer type):
  edges touching a retyped node: casts before vs casts needed after (compatible pointer types or void * need
  none; `p + K` keeps a byte cast unless the new record has a member at K);
  in-place uses: `((V *)p)->m` drops when the new type has the same member type at the same offset,
  `*(W *)((u8 *)p + K)` folds (2 casts) when it has W at K; plain `p->m` through the old record needs the
  same member in the new record, else a view cast (member_missing);
  integer arithmetic on an int holder that becomes a pointer is an arith risk (needs (s32) or byte casts).
H8/H9 runtime tables (RTDIR/pointees.tsv.gz, RTDIR/callsite_args.tsv.gz; off with TYPE_FLOW_RT_EXT=0):
  call-site cells label every argument edge with what that caller passed (a generic callee's per-caller kinds) and
  give the caller's holder (local, field, global) runtime cells; pointer values label field and global holders by
  the access site; installed functions (value class func) couple the slot holder at that site with the callback's
  parameters and return (`F:` / `G:` / `L:` slots, dispatch tables, `&fn` installs alike).  Every labelled holder
  with a real declared type votes for its cells.  `rt_seeds` adds seeds: integer parameters that receive a pointer
  at every call site, slot families whose installed callbacks disagree with the slot's runtime-voted type, and the
  placeholder caller holders feeding a multi-kind (generic) parameter, each with its own call-site target.

Verdicts: whole (net pointer casts fall, every cast left or added evidence-correct/neutral, no conflict,
no arity disagreement), bridge (owner ruling 10-31: every changed declaration runtime-backed or flow-backed,
casts may rise; each added cast is a bridge cast), hold (reason).
"""
from __future__ import annotations

import collections
import csv
import gzip
import json
import os
from pathlib import Path
import re
import sys

from type_flow_keys import FunctionKeys

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE)]

SCALAR_ALIAS = {
    'signed short': 'short', 'short int': 'short', 'signed short int': 'short',
    'unsigned short int': 'unsigned short', 'signed int': 'int', 'signed': 'int', 'long': 'int',
    'long int': 'int', 'signed long': 'int', 'unsigned': 'unsigned int', 'unsigned long': 'unsigned int',
    'unsigned long int': 'unsigned int',
}
INT4 = {'int', 'unsigned int', 'enum'}
INT_SMALL = {'short', 'unsigned short', 'char', 'signed char', 'unsigned char', '_Bool'}
BYTE = {'char', 'signed char', 'unsigned char'}
GENERATED = re.compile(r'(?:^|_)S_(?:func_)?[0-9A-Fa-f]{6,8}|^Rec_|^Row_|^R\d+_|^Func[0-9A-Fa-f]{8}|^FuncArg\d*$|'
                       r'^func_[0-9A-Fa-f]{8}_|^@|_pre$|^Unk[0-9A-Fa-f]{4,}|^D_[0-9A-F]{8}')
OPEN = {'int', 'void', 'byte', 'scalar', 'gen'}
POINTERS = {'void', 'byte', 'scalar', 'gen', 'real', 'private', 'pp', 'fnptr'}
BRIDGE_MEMBERS = os.environ.get('TYPE_FLOW_BRIDGE_MEMBERS') == '1'   # member_missing -> bridge view casts
CAP = int(os.environ.get('TYPE_FLOW_CAP', '1000'))
PRUNE = {'contradicted', 'member_missing', 'ambiguous_definition', 'arity', 'conflict', 'no_target'}
HOPS = 8


# --------------------------------------------------------------------------- graph

class Graph:
    def __init__(self, gdir):
        self.dir = Path(gdir)
        self.functions = collections.defaultdict(list)
        self.decl = collections.defaultdict(collections.Counter)
        self.edges, self.uses, self.int_uses, self.calls = [], [], [], []
        self.records, self.typedefs, self.protos = {}, {}, {}
        self.record_definitions = collections.defaultdict(set)
        self.ambiguous_records = set()
        seen_e, seen_u, seen_i, seen_c, seen_f = set(), set(), set(), set(), set()
        units = []
        for p in sorted((self.dir / 'tu').glob('*.json.gz')):
            with gzip.open(p, 'rt') as fh:
                text = fh.read()
            if '"/' in text:
                # absolute spellings of tree files (SLUS module members) -> tree-relative
                text = re.sub(r'"/(?:[^"/]+/)+?((?:src|include)/[^"]+)"', r'"\1"', text)
            if '/build_ovl/' in text:
                # generated SLUS partition input: attribute its sites to the registered TU
                tu = json.loads(text)['tu']
                text = re.sub(r'"(?:/[^"/]+)+/build_ovl/[^"]+"', json.dumps(tu), text)
            units.append(json.loads(text))
        keys = FunctionKeys(units)
        self.ambiguous_functions = keys.collisions
        for unit in units:
            d = keys.rewrite(unit)
            for f in d['functions']:
                k = (f['key'], f['file'], f['line'])
                if k not in seen_f:
                    seen_f.add(k)
                    self.functions[f['key']].append(f)
            for n, c in d['decl_types'].items():
                for t, m in c.items():
                    self.decl[n][t] += 1
            for e in d['edges']:
                k = (e['k'], e['dst'], e['src'], e['file'], e['line'], e.get('i'), tuple(e['casts']), e['off'])
                if k not in seen_e:
                    seen_e.add(k)
                    self.edges.append(e)
            for u in d['uses']:
                k = (u['ctx'], u['node'], u['file'], u['line'], u.get('cast'), u.get('member'), u['off'])
                if k not in seen_u:
                    seen_u.add(k)
                    self.uses.append(u)
            for u in d['int_uses']:
                k = (u['node'], u['op'], u['file'], u['line'])
                if k not in seen_i:
                    seen_i.add(k)
                    self.int_uses.append(u)
            for c in d['calls']:
                k = (c['caller'], c['callee'], c['file'], c['line'], c['nargs'])
                if k not in seen_c:
                    seen_c.add(k)
                    self.calls.append(c)
            for r, v in d['records'].items():
                definition = (v.get('file', ''), v.get('size'), json.dumps(v.get('fields', []), sort_keys=True))
                self.record_definitions[r].add(definition)
                if len(self.record_definitions[r]) > 1:
                    self.ambiguous_records.add(r)
                old = self.records.get(r)
                if old is None or (old['size'] != v['size'] and v['file'].startswith('include/')):
                    self.records[r] = v
            for t, v in d['typedefs'].items():
                self.typedefs.setdefault(t, v)
            for k, v in d['protos'].items():
                self.protos.setdefault(k, v)
        self.by_node_uses = collections.defaultdict(list)
        self.by_node_int = collections.defaultdict(list)
        for u in self.uses:
            self.by_node_uses[u['node']].append(u)
        for u in self.int_uses:
            self.by_node_int[u['node']].append(u)
        self.calls_to = collections.defaultdict(list)
        for c in self.calls:
            self.calls_to[c['callee']].append(c)
        self._resolve = {}
        idx = self.dir / 'index.json'
        self.root = Path(json.loads(idx.read_text()).get('root', '')) if idx.exists() else None
        self._lines = {}

    def lexical_casts(self, file, line):
        """Pointer casts debt_check sees on a source line (casts produced by macro expansion are not debt)."""
        if self.root is None:
            return None
        if file not in self._lines:
            try:
                self._lines[file] = (self.root / file).read_text(errors='replace').splitlines()
            except OSError:
                self._lines[file] = []
        lines = self._lines[file]
        if not (0 < line <= len(lines)):
            return None
        text = lines[line - 1]
        return len(re.findall(r'\(\s*(?:const\s+|volatile\s+|struct\s+|union\s+|unsigned\s+|signed\s+)*[A-Za-z_]\w*(?:\s+\w+)*\s*\*+\s*\)', text))

    # ---------------------------------------------------------------- types
    def resolve(self, t, depth=0):
        key = t
        if depth == 0 and key in self._resolve:
            return self._resolve[key]
        t = (t or '').strip()
        t = re.sub(r'\b(?:const|volatile|register)\b', '', t)
        t = re.sub(r'\s+', ' ', t).replace(' *', '*').replace('* ', '*').strip()
        m = re.match(r'^(.*)\[(\d*)\]$', t)
        if depth > 20:
            r = t
        elif re.search(r'\(\*[^)]*\)\s*\(', t):
            r = 'fnptr'
        elif re.search(r'\(\*[^)]*\)\s*\[', t):
            r = self.resolve(re.sub(r'\s*\(\*[^)]*\)\s*\[.*$', '', t), depth + 1) + '*'   # pointer to array
        elif t.endswith('*'):
            r = self.resolve(t[:-1], depth + 1) + '*'
        elif m:
            r = self.resolve(m.group(1), depth + 1) + '[' + m.group(2) + ']'
        elif t in self.typedefs:
            r = self.resolve(self.typedefs[t], depth + 1)
        elif t.startswith('enum '):
            r = 'enum'
        elif t.startswith(('struct ', 'union ')):
            # Extraction keys anonymous records by source location, while clang's
            # field type includes the enclosing record and an unnamed-at spelling.
            # Use the same key as the extractor so nested union leaves remain visible.
            from field_census import record_key
            r = 'rec:' + record_key(t)
        elif re.match(r'^[A-Za-z_]\w*$', t) and t in self.records:
            r = 'rec:' + t
        else:
            r = SCALAR_ALIAS.get(t, t)
        if depth == 0:
            self._resolve[key] = r
        return r

    def same(self, a, b):
        return bool(a) and bool(b) and self.resolve(a) == self.resolve(b)

    def cls(self, t):
        if not t:
            return 'unknown'
        r = self.resolve(t)
        if r in ('fnptr', 'fnptr*'):
            return 'fnptr'
        if r.endswith('**'):
            return 'pp'
        if r.endswith('*'):
            core = r[:-1]
            if core == 'void':
                return 'void'
            if core in BYTE:
                return 'byte'
            if core.startswith('rec:'):
                name = core[4:]
                spelled = re.sub(r'\b(?:const|volatile|struct|union)\b', '', t).replace('*', '').strip()
                if name in self.ambiguous_records:
                    return 'private'
                if GENERATED.search(name) or GENERATED.search(spelled):
                    return 'gen'
                rec = self.records.get(name)
                if rec and not rec.get('file', '').startswith('include/'):
                    return 'private'
                return 'real'
            return 'scalar'
        if r in INT4:
            return 'int'
        if r in INT_SMALL:
            return 'small'
        if r.startswith('rec:'):
            return 'record'
        return 'other'

    def record_of(self, t):
        r = self.resolve(t)
        if r.endswith('*') and not r.endswith('**') and r[:-1].startswith('rec:'):
            return r[4:-1]
        return None

    def leaves(self, rec, off, depth=0):
        """(path, type) of every member at byte offset `off` of record `rec`, outermost first."""
        lay = self.records.get(rec)
        if not lay or depth > 6:
            return
        for name, foff, ftype, bits in lay['fields']:
            if bits or not name:
                continue
            m = re.match(r'^(.*?)\s*\[(\d+)\]$', ftype.strip())
            if m:
                if foff == off:
                    yield name, ftype
                elt = m.group(1)
                esize = self.size(elt)
                if not esize:
                    continue
                if foff <= off < foff + esize * int(m.group(2)):
                    i, rel = divmod(off - foff, esize)
                    if rel == 0:
                        yield '%s[%d]' % (name, i), elt
                    sub = self.record_of(elt + ' *')
                    if sub:
                        for p, t in self.leaves(sub, rel, depth + 1):
                            yield '%s[%d].%s' % (name, i, p), t
                continue
            size = self.size(ftype) or 0
            if foff == off:
                yield name, ftype
            if size and foff <= off < foff + size:
                sub = self.record_of(ftype + ' *') if not self.resolve(ftype).endswith('*') else None
                if sub:
                    for p, t in self.leaves(sub, off - foff, depth + 1):
                        yield name + '.' + p, t

    def size(self, t):
        r = self.resolve(t)
        if r.endswith('*') or r == 'fnptr':
            return 4
        m = re.match(r'^(.*)\[(\d*)\]$', r)
        if m:
            inner = self.size(m.group(1))
            return inner * int(m.group(2)) if inner and m.group(2) else None
        if r in INT4 or r == 'float':
            return 4
        if r in ('short', 'unsigned short'):
            return 2
        if r in BYTE or r == '_Bool':
            return 1
        if r.startswith('rec:'):
            lay = self.records.get(r[4:])
            return lay['size'] if lay else None
        return None

    def member_at(self, rec, off, want):
        """Member path of `rec` at `off` whose type is exactly `want` (canonical), else None."""
        for p, t in self.leaves(rec, off):
            if self.same(t, want):
                return p
        return None

    # ---------------------------------------------------------------- nodes
    def fn_def(self, key):
        ds = self.functions.get(key) or []
        return ds[0] if ds else None

    def ambiguous_function(self, key):
        return key in self.ambiguous_functions or len({d['file'] for d in self.functions.get(key, [])}) > 1

    def declared(self, node):
        if node.startswith('P:'):
            key, _, i = node[2:].rpartition('#')
            d = self.fn_def(key)
            if d and i.isdigit() and int(i) < len(d['params']):
                return d['params'][int(i)]['type']
            if d:
                return ''
        if node.startswith('R:'):
            d = self.fn_def(node[2:])
            if d:
                return d['ret']
        if re.search(r'#(\d+|ret)$', node) and not node.startswith('P:'):
            holder, _, i = node.rpartition('#')
            ht = self.declared(holder)
            spelled = (ht or '').strip()
            guard = 0
            while spelled in self.typedefs and guard < 10:
                spelled = self.typedefs[spelled]
                guard += 1
            import type_flow as F
            if i == 'ret':
                m = re.match(r'^(.*?)\(\*', spelled or '')
                return m.group(1).strip() if m else ''
            m = re.search(r'\(\*\s*\w*\s*\)\s*(\(.*\))\s*$', spelled or '')
            ps = F.fn_param_types('x' + m.group(1)) if m else None
            if ps is not None and int(i) < len(ps):
                return ps[int(i)]
            return ''
        c = self.decl.get(node)
        return c.most_common(1)[0][0] if c else ''

    def home(self, node):
        """File that declares the node (definition for params/locals/returns, record file for fields)."""
        if node.startswith('P:'):
            d = self.fn_def(node[2:].rpartition('#')[0])
            return d['file'] if d else ''
        if node.startswith('R:'):
            d = self.fn_def(node[2:])
            return d['file'] if d else ''
        if node.startswith('L:'):
            d = self.fn_def(node[2:].split(':')[0])
            return d['file'] if d else ''
        if node.startswith(('F:', '&F:')):
            rec = node.split(':', 1)[1].split('.')[0]
            return (self.records.get(rec) or {}).get('file', '')
        return ''


def lexical_cap(g, site, n):
    """A cast that only exists inside a macro expansion is not lexical debt: cap by what the line spells."""
    if site.get('macro'):
        return 0
    lex = g.lexical_casts(site.get('file', ''), site.get('line') or 0)
    return n if lex is None else min(n, lex)


def folder(path):
    return os.path.dirname(path) if path else ''


def ptr_casts(casts):
    return sum(1 for c in casts if '*' in c)


# --------------------------------------------------------------------------- runtime

TOK = re.compile(r'^(.*)=(\d+)$')


def parse_values(v):
    out = []
    for t in (v or '').split(', '):
        t = t.strip()
        m = TOK.match(t)
        if not m:
            continue
        lab, n = m.group(1), int(m.group(2))
        if lab.startswith('scalar'):
            out.append((('scalar', '', 0), n))
        elif lab == 'null':
            out.append((('null', '', 0), n))
        elif lab.startswith('ram:'):
            s, _, off = lab[4:].partition('+')
            out.append((('ram', s, int(off, 16) if off else 0), n))
        elif re.match(r'^rk\d+', lab):
            k, _, off = lab.partition('+')
            out.append((('heap', k, int(off, 16) if off else 0), n))
        else:
            out.append((('other', lab, 0), n))
    return out


SITE_LINE_SLACK = 3


def parse_site_label(lab):
    """callsite_args.tsv cell label (rtti_merge cell_label vocabulary) -> fn_args-style cell key."""
    lab = lab.strip()
    if lab == 'null':
        return ('null', '', 0)
    if lab.startswith('scalar'):
        return ('scalar', '', 0)
    m = re.match(r'^(rk\d+)\+0x([0-9A-Fa-f]+)$', lab)
    if m:
        return ('heap', m.group(1), int(m.group(2), 16))
    m = re.match(r'^((?:src|include)/[^:]+):([A-Za-z_]\w*)$', lab)
    if m:
        return ('func', m.group(2), 0)
    if lab.startswith(('scratch', 'native', 'port:')):
        return ('other', lab.split('+')[0], 0)
    m = re.match(r'^([A-Za-z_]\w*)\+0x([0-9A-Fa-f]+)$', lab)
    if m:
        return ('ram', m.group(1), int(m.group(2), 16))
    if lab.startswith('ram:'):
        s, _, off = lab[4:].partition('+')
        return ('ram', s, int(off, 16) if off else 0)
    return ('other', lab, 0)


def parse_site_cells(text):
    out = collections.Counter()
    for t in (text or '').split(', '):
        lab, _, n = t.strip().rpartition('=')
        if lab and n.isdigit():
            out[parse_site_label(lab)] += int(n)
    return out


def pointee_cell(cls, target, off):
    """pointees.tsv value (class, target, offset) -> cell key."""
    o = int(off, 16) if off and off.startswith('0x') else 0
    if cls == 'heap':
        return ('heap', target, o)
    if cls in ('ram', 'global'):
        s, _, roff = target.partition('+')
        return ('ram', s, (int(roff, 16) if roff.startswith('0x') else 0) + o)
    if cls == 'func':
        return ('func', target.rpartition(':')[2], 0)
    if cls == 'null':
        return ('null', '', 0)
    return ('other', cls + ':' + target, 0)


def fn_key(graph, name, file):
    for d in graph.functions.get(name + '@' + file, []):
        return d['key']
    return name


class Runtime:
    def __init__(self, rt, graph):
        self.g = graph
        rt = Path(rt)
        self.cells = {}
        for r in csv.DictReader(open(rt / 'fn_args.tsv'), delimiter='\t'):
            if not r['file'].startswith('src/'):
                continue
            key = fn_key(graph, r['function'], r['file'])
            if graph.ambiguous_function(key):
                continue
            node = 'P:%s#%s' % (key, r['arg'])
            c = collections.Counter()
            for cell, n in parse_values(r['values']):
                c[cell] += n
            self.cells[node] = c
        self.votes = collections.defaultdict(lambda: collections.defaultdict(set))
        for node, c in self.cells.items():
            t = graph.declared(node)
            if graph.cls(t) != 'real':
                continue
            for cell in c:
                if cell[0] in ('heap', 'ram'):
                    self.votes[cell][graph.resolve(t)].add(node)
        kp = rt / 'kinds_rt.json'
        self.pooled = set()
        if kp.exists():
            for k in json.load(open(kp))['kinds']:
                if str(k.get('allocator', '')).startswith('allocate_flagged_object_node') or k.get('role') == 'pool':
                    self.pooled.add(k['id'])
                for rc in k.get('receivers', []):
                    key = fn_key(graph, rc['function'], rc.get('file', ''))
                    if graph.ambiguous_function(key):
                        continue
                    node = 'P:%s#%s' % (key, rc['arg'])
                    t = graph.declared(node)
                    if graph.cls(t) == 'real':
                        self.votes[('heap', k['id'], int(rc.get('offset', 0)))][graph.resolve(t)].add(node)
        self.ext = os.environ.get('TYPE_FLOW_RT_EXT', '1') != '0' and (
            (rt / 'callsite_args.tsv.gz').exists() or (rt / 'pointees.tsv.gz').exists())
        self.site = collections.defaultdict(list)          # (callee key, arg, caller key) -> [(line, cells)]
        self.site_any = collections.defaultdict(collections.Counter)   # (caller key, line, arg) -> cells, any callee
        self.derived = {}                                    # holder node -> cells (call sites / pointer values)
        self.slot_installs = []                              # (file, line, access, function key, count)
        self.held_values = collections.defaultdict(list)     # (file, line) -> [(access, cell, count)]
        if self.ext:
            self._load_ext(rt)
        self.layout_votes = self.layout_views()

    # ---------------------------------------------------------------- H8/H9 extension
    def _load_ext(self, rt):
        g = self.g
        cs = rt / 'callsite_args.tsv.gz'
        if cs.exists():
            with gzip.open(cs, 'rt') as fh:
                for r in csv.DictReader(fh, delimiter='\t'):
                    if not r['callee_file'].startswith(('src/', 'include/')) or not r['caller_file'].startswith('src/'):
                        continue
                    callee = fn_key(g, r['callee'], r['callee_file'])
                    caller = fn_key(g, r['caller'], r['caller_file'])
                    if g.ambiguous_function(callee) or g.ambiguous_function(caller):
                        continue
                    cells = parse_site_cells(r['cells'])
                    line = int(r['line'] or 0)
                    self.site[(callee, int(r['arg']), caller)].append((line, cells))
                    self.site_any[(caller, line, int(r['arg']))].update(cells)
        pt = rt / 'pointees.tsv.gz'
        if pt.exists():
            with gzip.open(pt, 'rt') as fh:
                for r in csv.DictReader(fh, delimiter='\t'):
                    if not r['file'].startswith('src/'):
                        continue
                    cell = pointee_cell(r['value_class'], r['value_target'], r['value_offset'])
                    n = int(r['count'] or 0)
                    if cell[0] == 'func':
                        f, _, name = r['value_target'].rpartition(':')
                        self.slot_installs.append((r['file'], int(r['line'] or 0), r['access'], fn_key(g, name, f), n))
                    self.held_values[(r['file'], int(r['line'] or 0))].append((r['access'], cell, n,
                                                                               r['class'], r['target'], r['offset']))
        # holder labels: a caller's argument holder takes the cells its call site passed
        for e in g.edges:
            if e['k'] != 'arg' or not e.get('src') or e['src'].startswith(('P:', 'FN:', '&FN:')):
                continue
            c = self.edge_cells(e)
            if c:
                # H9 labels the evaluated argument, so undo its arithmetic for the holder.
                cells = collections.Counter()
                for cell, count in c.items():
                    base = (cell[0], cell[1], cell[2] - e['off']) if cell[0] in ('heap', 'ram') else cell
                    cells[base] += count
                self.derived.setdefault(e['src'], collections.Counter()).update(cells)
        # field / global holders read or written at a site that saw exactly one pointer-typed holder
        by_site = collections.defaultdict(set)
        for e in g.edges:
            if e['k'] in ('init', 'assign') and e.get('src'):
                for end, t, acc in ((e['dst'], e.get('dt'), 'store'), (e['src'], e.get('st'), 'load')):
                    if end.startswith('F:') and g.cls(g.declared(end) or t) in POINTERS - {'fnptr'}:
                        by_site[(e['file'], e['line'], acc)].add(end)
        known = set(g.decl)
        for site, vals in self.held_values.items():
            for access, cell, n, cls, target, off in vals:
                if cls == 'ram' and cell[0] in ('heap', 'ram', 'null'):
                    sym, _, roff = target.partition('+')
                    if roff in ('', '0x0') and 'G:' + sym in known:      # a global's own word holds the pointer
                        self.derived.setdefault('G:' + sym, collections.Counter())[cell] += n
            for acc in ('load', 'store'):
                # a member holder: one pointer-typed member read (written) on the line, and the heap accesses of
                # that direction on the line all hit one object offset (so the value is that member's)
                holders = by_site.get(site + (acc,))
                rows = [v for v in vals if v[0] == acc and v[3] == 'heap']
                if not holders or len(holders) != 1 or len({v[5] for v in rows}) != 1:
                    continue
                h = next(iter(holders))
                for access, cell, n, cls, target, off in rows:
                    if cell[0] in ('heap', 'ram', 'null'):
                        self.derived.setdefault(h, collections.Counter())[cell] += n
        # a RAM cell nothing typed received is voted by the global that holds it (element / embedded record at
        # that offset of the global's own declared type)
        ram_cells = {cell for c in list(self.cells.values()) + list(self.derived.values()) for cell in c
                     if cell[0] == 'ram'}
        for rows in self.site.values():
            for _, c in rows:
                ram_cells.update(cell for cell in c if cell[0] == 'ram')
        for cell in ram_cells:
            if cell in self.votes:
                continue
            t = self.global_root_type(cell[1], cell[2])
            if t:
                self.votes[cell][t].add('G:' + cell[1])
        # labelled holders with a real declared type vote for their cells
        for node, c in self.derived.items():
            if node in self.cells:
                continue
            t = g.declared(node)
            if g.cls(t) != 'real':
                continue
            for cell in c:
                if cell[0] in ('heap', 'ram'):
                    self.votes[cell][g.resolve(t)].add(node)
        self.co_voted = self.co_votes()

    def co_votes(self):
        """Cells nothing typed received inherit the type of the cells they arrive with: a holder whose voted cells
        all win the same type (and carry at least half its observations) votes that type for its unvoted cells,
        as 'co:<holder>'.  Run once, after every direct vote."""
        add = []
        for node, c in list(self.cells.items()) + list(self.derived.items()):
            cells = {k: n for k, n in c.items() if k[0] in ('heap', 'ram')}
            if not cells:
                continue
            voted = {k: self.winner(k)[0] for k in cells if k in self.votes}
            winners = set(voted.values()) - {None}
            if len(winners) != 1 or sum(cells[k] for k in voted) * 2 < sum(cells.values()):
                continue
            t = winners.pop()
            add.extend((k, t, node) for k in cells if k not in self.votes)
        for k, t, node in add:
            self.votes[k][t].add('co:' + node)
        return len({k for k, _, _ in add})

    def layout_views(self):
        """Votes at observed/requested member offsets, grounded in declared record layouts.

        A record-valued member supplies its own pointer type. A cursor at a known
        member boundary also retains its containing record view. Pointer members
        are never followed, and neither padding nor a guessed header/body type is
        evidence. Direct receiver votes take precedence over these layout views.
        """
        g = self.g
        requested = collections.defaultdict(set)

        def request(cells, offset=0):
            for cell in cells:
                if cell[0] in ('heap', 'ram'):
                    requested[cell[:2]].add(cell[2] + offset)

        for cells in list(self.cells.values()) + list(self.derived.values()):
            request(cells)
        for rows in self.site.values():
            for _, cells in rows:
                request(cells)
        for edge in g.edges:
            if edge['off'] and edge.get('src'):
                request(self.pointer_cells(edge['src']), edge['off'])
        views = collections.defaultdict(lambda: collections.defaultdict(set))
        for base, votes in self.votes.items():
            for t, voters in votes.items():
                rec = g.record_of(t)
                size = g.size(t[:-1]) if rec else None
                grounded = {v for v in voters if not v.startswith('co:')}
                if not size or not grounded or g.cls(t) != 'real':
                    continue
                for offset in requested.get(base[:2], ()):
                    relative = offset - base[2]
                    if not 0 < relative < size:
                        continue
                    leaves = [(path, ft) for path, ft in g.leaves(rec, relative)
                              if not any(re.match(r'^(?:pad|unused)(?:_|\d|$)', part.split('[')[0])
                                         for part in path.split('.'))]
                    if not leaves:
                        continue
                    cell = base[:2] + (offset,)
                    embedded = {g.resolve(ft) + '*' for _, ft in leaves
                                if g.cls(ft) == 'record' and g.cls(g.resolve(ft) + '*') == 'real'}
                    for view in embedded or {t}:
                        views[cell][view].update(grounded)
        return views

    def cell_votes(self, cell):
        """Prefer directly observed types; use layout views where no receiver voted."""
        return self.votes.get(cell) or getattr(self, 'layout_votes', {}).get(cell, {})

    def global_root_type(self, sym, off):
        """Canonical `rec:T*` a pointer to `sym`+off has by the global's declared type, or None."""
        g = self.g
        decl = g.decl.get('G:' + sym)
        if not decl:
            return None
        t = decl.most_common(1)[0][0]
        r = g.resolve(t)
        total = g.size(t)
        if total is not None and not 0 <= off < total:
            return None                                 # the region label ran past the global
        m = re.match(r'^rec:(.*?)((?:\[\d*\])+)$', r)
        if m:                                           # array of records: an element boundary
            rec = m.group(1)
            size = g.size(rec)
            if size and off % size == 0 and g.cls(rec + ' *') == 'real':
                return 'rec:%s*' % rec
            return None
        rec = r[4:] if r.startswith('rec:') and not r.endswith('*') else None
        if not rec or g.cls(rec + ' *') != 'real':
            return None
        if off == 0:
            return 'rec:%s*' % rec
        for path, ft in g.leaves(rec, off):
            fr = g.resolve(ft)
            if fr.startswith('rec:') and not fr.endswith('*') and '[' not in fr and g.cls(ft + ' *') == 'real':
                return fr + '*'
        return None

    def sites_of(self, callee, arg):
        """[(caller, [(line, cells)])] of one callee argument."""
        if not hasattr(self, '_by_callee'):
            self._by_callee = collections.defaultdict(list)
            for (ce, a, caller), rows in self.site.items():
                self._by_callee[(ce, a)].append((caller, rows))
        return self._by_callee.get((callee, arg), [])

    def edge_cells(self, e):
        """Cells the call site of an argument edge passed (H9), or None."""
        if not self.ext or e.get('k') != 'arg':
            return None
        dst = e['dst']
        if dst.startswith('P:'):
            callee, _, i = dst[2:].rpartition('#')
            if not i.isdigit():
                return None
            rows = self.site.get((callee, int(i), e['fn']))
            if not rows:
                return None
            if len(rows) == 1:
                return rows[0][1]
            best = min(rows, key=lambda r: abs(r[0] - (e['line'] or 0)))
            return best[1] if abs(best[0] - (e['line'] or 0)) <= SITE_LINE_SLACK else None
        m = re.match(r'^(.*)#(\d+)$', dst)
        if m:                                   # indirect call through a slot holder
            for d in range(SITE_LINE_SLACK + 1):
                for ln in {(e['line'] or 0) + d, (e['line'] or 0) - d}:
                    c = self.site_any.get((e['fn'], ln, int(m.group(2))))
                    if c:
                        return c
        return None

    def winner(self, cell):
        v = self.cell_votes(cell)
        if not v:
            return None, 0.0
        best = max(v, key=lambda t: (len(v[t]), t))
        tot = sum(len(x) for x in v.values())
        return best, len(v[best]) / tot

    def pointer_cells(self, node):
        c = self.cells.get(node) or self.derived.get(node)
        if not c:
            m = re.match(r'^&G:([A-Za-z_]\w*)$', node)
            if m:
                return collections.Counter({('ram', m.group(1), 0): 1})
            return collections.Counter()
        return collections.Counter({k: n for k, n in c.items() if k[0] in ('heap', 'ram')})

    def scalar_share(self, node):
        c = self.cells.get(node) or self.derived.get(node)
        if not c:
            return None
        tot = sum(c.values())
        return sum(n for k, n in c.items() if k[0] == 'scalar') / tot if tot else None

    def node_type(self, node):
        """Runtime-voted type of a node: (canonical type, share, cells) or (None, 0, cells)."""
        cells = self.pointer_cells(node)
        tv = collections.Counter()
        for cell, n in cells.items():
            w, share = self.winner(cell)
            if w:
                tv[w] += n
        if not tv:
            return None, 0.0, cells
        best = max(tv, key=lambda t: (tv[t], t))
        return best, tv[best] / sum(tv.values()), cells

    def cast_ok(self, cells, off, t):
        """'correct' | 'neutral' | 'wrong' | 'unproven' for a cast to t of a value with these cells (+off)."""
        k = self.g.cls(t)
        if k in ('void', 'byte'):
            return 'neutral'
        if k in ('gen', 'scalar', 'pp'):
            return 'placeholder_view'     # the other end is still a generated/scalar view: retired when it is typed
        if not cells:
            return 'unproven'
        rt = self.g.resolve(t)
        bad = 0
        unproven = False
        for cell in cells:
            c2 = (cell[0], cell[1], cell[2] + off)
            v = self.cell_votes(c2)
            if c2[0] == 'heap' and c2[1] in self.pooled and c2[2] == 0 and rt == 'rec:ObjectNodeHeader*':
                continue
            if not v:
                unproven = True
                continue
            tot = sum(len(x) for x in v.values())
            if rt in v and (len(v[rt]) / tot >= 0.25 or max(len(x) for x in v.values()) == len(v[rt])):
                continue
            bad += 1
        return 'wrong' if bad else 'unproven' if unproven else 'correct'


def canon_display(g, t):
    """'rec:Foo*' -> 'Foo *' for reports."""
    r = g.resolve(t) if t else ''
    m = re.match(r'^rec:(.*?)(\*+)$', r)
    return (m.group(1) + ' ' + m.group(2)) if m else (t or '')


# --------------------------------------------------------------------------- components

def is_fn(node):
    """A function designator: `FN:f` (decayed) or `&FN:f` (explicit address-of, the same value)."""
    return bool(node) and node.startswith(('FN:', '&FN:'))


def fn_of(node):
    return node.split('FN:', 1)[1] if is_fn(node) else None


class Solver:
    def __init__(self, g, rt):
        self.g = g
        self.rt = rt
        self._labelled = set()
        self.member_needs = set()       # (target type, offset, member type, view member, view, node, site)
        self.adj = collections.defaultdict(list)
        self.offset_adj = collections.defaultdict(list)
        for i, e in enumerate(g.edges):
            if not e.get('src'):
                continue
            if e['k'] not in ('init', 'assign', 'arg', 'ret', 'cmp'):
                continue
            if e['off']:
                self.offset_adj[e['src']].append(i)
                self.offset_adj[e['dst']].append(i)
                continue
            self.adj[e['dst']].append(('e', i, e['src']))
            self.adj[e['src']].append(('e', i, e['dst']))
            dk = g.cls(e.get('dt'))
            if is_fn(e['src']) or (dk == 'fnptr' and g.cls(e.get('st')) == 'fnptr'):
                cb = fn_of(e['src'])
                self.couple_slot(e['dst'], cb, i, other=None if cb else e['src'])
        self.slots = collections.defaultdict(collections.Counter)   # slot holder -> installed function -> count
        self.slot_sites = collections.defaultdict(set)
        self.untyped_slots = collections.defaultdict(collections.Counter)
        self.couple_runtime_slots()

    def couple_slot(self, holder, cb, i, other=None):
        """Couple a function-pointer holder's parameters and return with a callback's (or another holder's).
        With the H8/H9 tables the slot parameter is labelled with every installed callback's cells, so a slot
        whose callbacks receive different kinds is polymorphic and stops a component instead of merging them."""
        derived = getattr(self.rt, 'derived', None) if getattr(self.rt, 'ext', False) else None
        for j in range(6):
            a = '%s#%d' % (holder, j)
            b = ('P:%s#%d' % (cb, j)) if cb else '%s#%d' % (other, j)
            if ('s', i, b) in self.adj[a]:
                continue
            self.adj[a].append(('s', i, b))
            self.adj[b].append(('s', i, a))
            if derived is not None and cb and self.rt.cells.get(b) and (cb, a) not in self._labelled:
                self._labelled.add((cb, a))
                derived.setdefault(a, collections.Counter()).update(self.rt.cells[b])
        a, b = holder + '#ret', ('R:' + cb) if cb else other + '#ret'
        if ('s', i, b) not in self.adj[a]:
            self.adj[a].append(('s', i, b))
            self.adj[b].append(('s', i, a))

    def couple_runtime_slots(self):
        """H8 installs: the function value seen at an access site couples the slot holder of that site."""
        g, rt = self.g, self.rt
        installs = getattr(rt, 'slot_installs', ())
        if not installs:
            return
        by_site = collections.defaultdict(list)
        for i, e in enumerate(g.edges):
            by_site[(e['file'], e['line'])].append(i)
        for file, line, access, fn, n in installs:
            if not g.fn_def(fn):
                continue
            holders = set()
            for i in by_site.get((file, line), ()):
                e = g.edges[i]
                if not e.get('src'):
                    continue
                if e['k'] in ('init', 'assign'):
                    if access == 'store' and g.cls(g.declared(e['dst']) or e.get('dt')) == 'fnptr':
                        holders.add((e['dst'], i))                     # store into the slot
                    elif access == 'store' and (is_fn(e['src']) or g.cls(e.get('st')) == 'fnptr'):
                        self.untyped_slots[e['dst']][fn] += n          # a function stored into a non-function holder
                    if access == 'load' and g.cls(g.declared(e['src']) or e.get('st')) == 'fnptr' and not is_fn(e['src']):
                        holders.add((e['src'], i))                     # load out of the slot
                elif e['k'] == 'arg' and access == 'load' and not e['dst'].startswith('P:'):
                    m = re.match(r'^(.*)#\d+$', e['dst'])
                    if m:
                        holders.add((m.group(1), i))                   # call through the slot
            for h, i in holders:
                if h.startswith(('FN:', '&')):
                    continue
                self.couple_slot(h, fn, i)
                self.slots[h][fn] += n
                self.slot_sites[h].add('%s:%d' % (file, line))

    scope = ()

    def in_scope(self, node):
        """A node is editable in a scoped solve when the file that declares it (or, for a slot parameter, the holder)
        lies under one of the scope prefixes; record members follow their record's header."""
        h = self.g.home(re.sub(r'#(\d+|ret)$', '', node) if not node.startswith(('P:', 'R:')) else node)
        return bool(h) and h.startswith(self.scope)

    def polymorphic(self, node):
        t, share, cells = self.rt.node_type(node)
        if cells and share < 0.75:
            return True
        srcs = set()
        for kind, i, other in self.adj.get(node, ()):
            e = self.g.edges[i]
            if kind == 'e' and e['dst'] == node:
                st = self.g.declared(other) or e.get('st')
                if self.g.cls(st) == 'real':
                    srcs.add(self.g.resolve(st))
        return len(srcs) >= 2

    def void_pays(self, node, tau):
        """A monomorphic void * holder joins only when its own body casts it to views the target spells."""
        rec = self.g.record_of(tau)
        for u in self.g.by_node_uses.get(node, ()):
            if u['ctx'] == 'member' and (self.g.same(u['cast'], tau) or rec):
                return True
            if u['ctx'] == 'raw' and rec and self.g.member_at(rec, u['off'], u['wtype']):
                return True
        return False

    def couples(self, node, other, e):
        """Pointer-relevant coupling (integer-to-integer flow only with runtime pointer evidence)."""
        a = self.g.cls(self.g.declared(node) or (e.get('dt') if e['dst'] == node else e.get('st')))
        b = self.g.cls(self.g.declared(other) or (e.get('dt') if e['dst'] == other else e.get('st')))
        if a in POINTERS or b in POINTERS:
            return True
        if a == 'int' and b == 'int':
            return bool(self.rt.pointer_cells(node) or self.rt.pointer_cells(other))
        return False

    def expand(self, seed, tau):
        comp = {}
        reasons = collections.Counter()
        boundary = []
        comp[seed] = {'t': tau, 'st': 'ok' if self.g.same(self.g.declared(seed), tau) else 'retype', 'seed': seed,
                      'from': self.g.declared(seed)}
        queue = [seed]
        depth = {seed: 0}
        nretype = 0
        while queue:
            n = queue.pop()
            t_n = comp[n]['t']
            for kind, i, m in self.adj.get(n, ()):
                if m in comp:
                    if comp[m]['st'] == 'retype' and not self.g.same(comp[m]['t'], t_n):
                        comp[m].setdefault('conflict', set()).add(t_n)
                    continue
                e = self.g.edges[i]
                if kind == 'e' and not self.couples(n, m, e):
                    continue
                dm = self.g.declared(m) or (e.get('st') if e['src'] == m else e.get('dt'))
                if not dm:
                    continue
                c = self.g.cls(dm)
                if self.g.same(dm, t_n):
                    comp[m] = {'t': t_n, 'st': 'ok', 'seed': seed}
                    continue
                if is_fn(m):
                    continue
                if m.startswith('&'):
                    boundary.append((i, m, 'address'))     # retyped only through its object's declaration
                    continue
                if depth.get(n, 0) >= HOPS:
                    boundary.append((i, m, 'hops'))
                    continue
                if self.scope and not self.in_scope(m):
                    boundary.append((i, m, 'scope'))       # owned by another lane: stays, its edge keeps a cast
                    continue
                cells = self.rt.pointer_cells(m)
                if cells:
                    rtype, share, _ = self.rt.node_type(m)
                    if rtype and not self.g.same(rtype, t_n) and share >= 0.5:
                        boundary.append((i, m, 'runtime_other'))
                        continue
                if c in OPEN:
                    if c == 'void' and self.g.cls(t_n) in POINTERS and (self.polymorphic(m) or not self.void_pays(m, t_n)):
                        boundary.append((i, m, 'generic_void' if self.polymorphic(m) else 'void_ok'))
                        continue
                    if c == 'int' and self.rt.scalar_share(m) not in (None, 0.0):
                        boundary.append((i, m, 'mixed_int'))
                        continue
                    if c == 'gen' and self.polymorphic(m):
                        boundary.append((i, m, 'generic_view'))
                        continue
                    comp[m] = {'t': t_n, 'st': 'retype', 'seed': seed, 'from': dm}
                    depth[m] = depth.get(n, 0) + 1
                    nretype += 1
                    queue.append(m)
                elif c in ('real', 'private'):
                    rtype, share, cells = self.rt.node_type(m)
                    flow_only = (not cells and m.startswith(('L:', 'F:')) and kind == 'e' and not e['casts']
                                 and not self.polymorphic(m) and self.g.cls(t_n) in ('real', 'private'))
                    if (rtype and self.g.same(rtype, t_n) and share >= 0.75) or flow_only:
                        comp[m] = {'t': t_n, 'st': 'retype', 'seed': seed, 'from': dm, 'mistyped': 1}
                        depth[m] = depth.get(n, 0) + 1
                        nretype += 1
                        queue.append(m)
                    else:
                        boundary.append((i, m, 'view'))
                else:
                    boundary.append((i, m, 'other:' + c))
                if nretype > CAP:
                    reasons['too_large'] += 1
                    return comp, boundary, reasons
        return comp, boundary, reasons

    # ---------------------------------------------------------------- evaluation
    def final(self, node, comp):
        if node in comp and comp[node]['st'] == 'retype':
            return comp[node]['t']
        return self.g.declared(node)

    def compatible(self, td, ts):
        g = self.g
        if g.same(td, ts):
            return True
        kd, ks = g.cls(td), g.cls(ts)
        if kd in POINTERS and ks in POINTERS and 'void' in (kd, ks) and 'fnptr' not in (kd, ks):
            return True
        if kd in ('int', 'small') and ks in ('int', 'small'):
            return True
        return False

    def evaluate(self, comp, boundary):
        g, rt = self.g, self.rt
        changed = {n for n, v in comp.items() if v['st'] == 'retype'}
        seed_ident = collections.defaultdict(collections.Counter)
        for n, v in comp.items():
            if v['st'] in ('retype', 'ok'):
                seed_ident[v.get('seed')].update(rt.pointer_cells(n))
        res = {'changed': len(changed), 'removed': 0, 'added': 0, 'remaining': 0, 'casts': [], 'reasons': set(),
               'files': set(), 'evidence': collections.Counter(), 'int_casts': 0,
               'node_reasons': collections.defaultdict(set)}
        cand_edges = set()
        for n in changed:
            for kind, i, m in self.adj.get(n, ()):
                if kind == 'e':
                    cand_edges.add(i)
            for i in self.offset_adj.get(n, ()):
                cand_edges.add(i)
        for i in sorted(cand_edges):
            e = g.edges[i]
            if e['src'] is None:
                continue
            td = self.final(e['dst'], comp) or e.get('dt')
            ts = self.final(e['src'], comp) or e.get('st')
            before = lexical_cap(g, e, ptr_casts(e['casts']) + ptr_casts(e.get('acasts', [])))
            kd, ks = g.cls(td), g.cls(ts)
            if e['off']:
                if ks in POINTERS:
                    rec = g.record_of(ts)
                    mem = None
                    if rec and kd in ('real', 'private', 'gen', 'scalar'):
                        mem = g.member_at(rec, e['off'], (td or '').rstrip().rstrip('*').strip())
                    size = g.size((ts or '').rstrip().rstrip('*').strip()) if rec else None
                    if mem:
                        after = 0
                    elif size and e['off'] % size == 0:
                        after = 0 if kd in ('void',) else 1       # `p + n` (header + 1 = body) keeps one view cast
                    elif kd in ('real', 'private', 'gen') and (g.size((td or '').rstrip().rstrip('*').strip()) or 0) \
                            and e['off'] % g.size((td or '').rstrip().rstrip('*').strip()) == 0:
                        after = 1                                  # `(T *)p - 1` (body - 1 = header)
                    elif kd in ('void', 'byte'):
                        after = 1
                    elif kd in POINTERS:
                        after = 2
                    else:
                        after = 0
                        res['int_casts'] += 1
                else:
                    after = 1 if kd in POINTERS else 0
            elif e.get('null'):
                after = 0
            elif self.compatible(td, ts):
                after = 0
            else:
                after = 1 if kd in POINTERS else 0
                if kd not in POINTERS and ks in POINTERS:
                    res['int_casts'] += 1
            d = after - before
            if d == 0 and not after:
                continue
            res['files'].add(e['file'])
            if d < 0:
                res['removed'] += -d
            elif d > 0:
                res['added'] += d
            if after:
                site = rt.edge_cells(e) if e['k'] == 'arg' else None
                site = collections.Counter({k: n for k, n in site.items() if k[0] in ('heap', 'ram')}) if site else None
                src_cells = site or rt.pointer_cells(e['src'])     # what this call site passed, else the holder's
                if not src_cells and e['src'] in comp:
                    src_cells = seed_ident.get(comp[e['src']].get('seed'), collections.Counter())
                # H9 already observes the final argument (including e['off']).
                cell_off = 0 if site else e['off']
                verdict = rt.cast_ok(src_cells, cell_off, td) if kd in POINTERS else 'int'
                res['evidence'][verdict] += after
                res['remaining'] += after
                if verdict == 'wrong' and d > 0:
                    for end in (e['dst'], e['src']):
                        if end in changed:
                            res['node_reasons'][end].add('contradicted')
                res['casts'].append({'file': e['file'], 'fn': e['fn'], 'line': e['line'], 'cast': canon_display(g, td),
                                     'new': d > 0, 'evidence': verdict, 'edge': e['k'], 'src': e['src'],
                                     'dst': e['dst'], 'off': e['off'], 'from_type': canon_display(g, ts),
                                     **({'cell_off': cell_off} if cell_off != e['off'] else {})})
        for n in changed:
            tau = comp[n]['t']
            rec = g.record_of(tau)
            for u in g.by_node_uses.get(n, ()):
                if u['ctx'] == 'member':
                    vrec = g.record_of(u['cast'])
                    hit = False
                    if g.same(u['cast'], tau) and u['off'] == 0:
                        hit = True
                    elif rec and vrec and g.records.get(vrec):
                        mo = [f[1] for f in g.records[vrec]['fields'] if f[0] == u['member']]
                        hit = bool(mo and g.member_at(rec, u['off'] + mo[0], u['mtype']))
                    if hit:
                        res['removed'] += lexical_cap(g, u, 1 + ptr_casts(u.get('inner_casts', [])))
                        res['files'].add(u['file'])
                elif u['ctx'] == 'raw':
                    if rec and g.member_at(rec, u['off'], u['wtype']):
                        res['removed'] += lexical_cap(g, u, 1 + ptr_casts(u.get('inner_casts', [])))
                        res['files'].add(u['file'])
                elif u['ctx'] == 'macc':
                    res['files'].add(u['file'])
                    if rec and u.get('rec') != rec and not g.member_at(rec, u['off'], u['mtype']):
                        res['added'] += 1
                        res['reasons'].add('member_missing'); res['node_reasons'][n].add('member_missing')
                        res['casts'].append({'file': u['file'], 'fn': u['fn'], 'line': u['line'],
                                             'cast': (u.get('rec') or '?') + ' *', 'new': True,
                                             'evidence': 'view_member_missing', 'edge': 'macc', 'src': n,
                                             'dst': u['member'], 'off': u['off'], 'from_type': canon_display(g, tau)})
                        self.member_needs.add((canon_display(g, tau), u['off'], u.get('mtype') or '', u['member'],
                                               u.get('rec') or '', n, '%s:%s' % (u['file'], u['line'])))
            if g.cls(comp[n].get('from', '')) == 'int' and g.by_node_int.get(n):
                res['reasons'].add('arith_risk')
                res['int_casts'] += len(g.by_node_int[n])
            if n.startswith(('P:', 'L:')):
                key = n[2:].rpartition('#')[0] if n.startswith('P:') else n[2:].split(':')[0]
                if g.ambiguous_function(key):
                    res['reasons'].add('ambiguous_definition'); res['node_reasons'][n].add('ambiguous_definition')
            if n.startswith('P:'):
                key = n[2:].rpartition('#')[0]
                d = g.fn_def(key)
                if d and not d['variadic']:
                    idx = int(n.rpartition('#')[2]) if n.rpartition('#')[2].isdigit() else 0
                    # only a call that does not pass this parameter at all disagrees about it
                    if any(c['nargs'] <= idx for c in g.calls_to.get(key, ()) if c['mode'] == 'direct'):
                        res['reasons'].add('arity'); res['node_reasons'][n].add('arity')
            if comp[n].get('conflict'):
                res['reasons'].add('conflict'); res['node_reasons'][n].add('conflict')
            h = g.home(n)
            if h:
                res['files'].add(h)
            if not comp[n]['t'] or g.cls(comp[n]['t']) in ('unknown', 'other', 'record'):
                res['reasons'].add('no_target'); res['node_reasons'][n].add('no_target')
        res['net'] = res['added'] - res['removed']
        return res


# --------------------------------------------------------------------------- seeds

def load_seeds(holds, actor_holds, grades=('A',)):
    seeds = []
    seen = set()
    for path in holds:
        for r in csv.DictReader(open(path), delimiter='\t'):
            if r.get('grade') not in grades:
                continue
            key = (r['function'], r['arg'])
            if key in seen:
                continue
            seen.add(key)
            seeds.append({'src': 'proto1', 'file': r['file'], 'function': r['function'], 'arg': r['arg'],
                          'target': r['target'], 'hold': r['hold'], 'reason': r['reason'], 'cur': r['cur_type']})
    for path in actor_holds:
        lane = 'A' if 'actor_a' in path else 'B' if 'actor_b' in path else 'C'
        for r in csv.DictReader(open(path), delimiter='\t'):
            reason = r.get('reason', '')
            rule = r.get('rule', '')
            if rule != 'R4' and not reason.startswith(('caller_type', 'direct_caller_incompatible')):
                continue
            key = (r['function'], r['arg'])
            if key in seen:
                continue
            seen.add(key)
            seeds.append({'src': 'actor:' + (r.get('lane') or lane), 'file': r['file'], 'function': r['function'],
                          'arg': r['arg'], 'target': '', 'hold': 'caller_type', 'reason': reason, 'cur': ''})
    return seeds


def node_for(g, s):
    if s.get('node_key'):
        return s['node_key']
    key = s['function']
    for d in g.functions.get(key + '@' + s['file'], []):
        key = d['key']
    return 'P:%s#%s' % (key, s['arg'])


def seed_target(g, rt, s, n):
    """Target type for a seed: the hold's evidence target, else the runtime vote."""
    tau = s.get('target') or ''
    if g.record_of(tau) in g.ambiguous_records:
        tau = ''
    rtype, share, cells = rt.node_type(n)
    s['rt_type'], s['rt_share'] = canon_display(g, rtype) if rtype else '', round(share, 2)
    if tau and g.cls(tau) == 'gen' and rtype and g.cls(rtype) == 'real' and share >= 0.75:
        return canon_display(g, rtype)
    if tau and g.cls(tau) not in ('unknown',):
        return tau
    if rtype and share >= 0.6:
        return canon_display(g, rtype)
    return ''


# --------------------------------------------------------------------------- runtime seeds (H8/H9)

def cells_type(rt, cells):
    """Runtime-voted type of a cell multiset: (canonical type, share) or (None, 0)."""
    tv = collections.Counter()
    for cell, n in cells.items():
        if cell[0] not in ('heap', 'ram'):
            continue
        w, _ = rt.winner(cell)
        if w:
            tv[w] += n
    if not tv:
        return None, 0.0
    best = max(tv, key=lambda t: (tv[t], t))
    return best, tv[best] / sum(tv.values())


def pointer_only(cells):
    """Every observation is a pointer (null allowed) and at least one is a heap/ram pointer."""
    kinds = {c[0] for c in cells}
    return bool(kinds & {'heap', 'ram'}) and not (kinds & {'scalar', 'func', 'other'})


def rt_seeds(g, rt, S, share=0.75):
    """Seeds the H8/H9 tables add, and the reasons other candidates stay unseeded (report rows)."""
    seeds, notes = [], []
    def add(src, node, target, reason, cells):
        if node.startswith('P:'):
            key, _, i = node[2:].rpartition('#')
            d = g.fn_def(key)
            if not d:
                return
            seeds.append({'src': src, 'file': d['file'], 'function': key.split('@')[0], 'arg': i, 'target': target,
                          'hold': src, 'reason': reason, 'cur': g.declared(node), 'node_key': node})
        elif node.startswith('L:'):
            key = node[2:].split(':')[0]
            d = g.fn_def(key)
            if not d:
                return
            seeds.append({'src': src, 'file': d['file'], 'function': key.split('@')[0], 'arg': node.split(':', 2)[2],
                          'target': target, 'hold': src, 'reason': reason, 'cur': g.declared(node), 'node_key': node})
    # 1. integer parameters that receive a pointer at every call site
    for node, c in rt.cells.items():
        if g.cls(g.declared(node)) != 'int' or not pointer_only(c):
            continue
        key, _, i = node[2:].rpartition('#')
        sites = rt.sites_of(key, int(i))
        if any(not pointer_only(cells) for _, rows in sites for _, cells in rows):
            notes.append(('rt_intptr', node, '', 'a call site passes a scalar'))
            continue
        tau, sh = cells_type(rt, c)
        if tau and sh >= share and g.cls(canon_display(g, tau)) == 'real':
            add('rt_intptr', node, canon_display(g, tau), 'pointer at every call site (%d sites)' % len(sites), c)
        else:
            notes.append(('rt_intptr', node, canon_display(g, tau) if tau else '', 'no typed voter for its cells'))
    # 2. slot families: installed callbacks and the slot, typed by the cells the callbacks receive
    for h, fns in S.slots.items():
        for j in range(6):
            members = ['P:%s#%d' % (f, j) for f in fns if g.fn_def(f) and j < len(g.fn_def(f)['params'])]
            if not members:
                continue
            cells = collections.Counter()
            for m in members:
                cells.update(rt.pointer_cells(m))
            tau, sh = cells_type(rt, cells)
            if not tau or sh < share or g.cls(canon_display(g, tau)) != 'real':
                if any(g.cls(g.declared(m)) in OPEN for m in members):
                    notes.append(('rt_slot', '%s#%d' % (h, j), canon_display(g, tau) if tau else '',
                                  'slot family without a typed majority (%d callbacks)' % len(members)))
                continue
            open_members = [m for m in members if g.cls(g.declared(m)) in OPEN and not g.same(g.declared(m), tau)]
            hj = '%s#%d' % (h, j)
            if g.cls(g.declared(hj)) in OPEN and not g.same(g.declared(hj), tau):
                open_members.append(hj)
            if open_members:
                m = next((x for x in open_members if x.startswith('P:')), None)
                if m:
                    add('rt_slot', m, canon_display(g, tau), 'slot %s (%d callbacks, %d placeholders)' % (
                        h, len(members), len(open_members)), cells)
    # 3. generic (multi-kind) parameters: each caller's placeholder holder takes its own call-site type
    for node in list(rt.cells):
        cells = rt.pointer_cells(node)
        if len({c[1] for c in cells if c[0] == 'heap'}) + len({c[1] for c in cells if c[0] == 'ram'}) < 2:
            continue
        tau, sh = cells_type(rt, cells)
        if tau and sh >= 0.75:
            continue
        for kind, i, src in S.adj.get(node, ()):
            e = g.edges[i]
            if kind != 'e' or e['k'] != 'arg' or e['dst'] != node or e['off'] or not src.startswith(('L:', 'P:')):
                continue
            if g.cls(g.declared(src) or e.get('st')) not in OPEN:
                continue
            ec = rt.edge_cells(e)
            if not ec or not pointer_only(ec):
                continue
            t2, sh2 = cells_type(rt, ec)
            if t2 and sh2 >= share and g.cls(canon_display(g, t2)) == 'real':
                add('rt_split', src, canon_display(g, t2), 'per-caller cells into generic %s' % node, ec)
            else:
                notes.append(('rt_split', src, canon_display(g, t2) if t2 else '', 'caller cells without a typed voter'))
    uniq, seen = [], set()
    for s in seeds:
        if s['node_key'] not in seen:
            seen.add(s['node_key'])
            uniq.append(s)
    return uniq, notes


def load_seed_tsv(paths):
    """Seeds from TSV rows with file, function, arg, target (a previous solve's seeds.tsv works)."""
    out = []
    for path in paths:
        for r in csv.DictReader(open(path), delimiter='\t'):
            node = r.get('node_key') or ''
            if not (r.get('file') or '').startswith('src/') or not ((r.get('arg') or '').isdigit() or node):
                continue
            out.append({'src': r.get('src') or Path(path).stem, 'file': r['file'], 'function': r['function'],
                        'arg': r['arg'], 'target': r.get('target') or '', 'hold': r.get('hold') or '',
                        'reason': r.get('reason') or '', 'cur': r.get('cur') or ''})
            if node:
                out[-1]['node_key'] = node          # a local holder (rt_split) round-trips by its node
    return out


# --------------------------------------------------------------------------- dry run

def solve_all(g, rt, seeds, S=None):
    S = S or Solver(g, rt)
    per = []
    for s in seeds:
        n = node_for(g, s)
        s['node'] = n
        s['cur_now'] = g.declared(n)
        s['tau'] = tau = seed_target(g, rt, s, n)
        if not g.fn_def(n[2:].rpartition('#')[0] if n.startswith('P:') else n[2:].split(':')[0]):
            s['state'] = 'no_definition'
            per.append((s, None, [], collections.Counter()))
            continue
        if S.scope and not S.in_scope(n):
            s['state'] = 'out_of_scope'                 # another lane's seed
            per.append((s, None, [], collections.Counter()))
            continue
        if s['cur_now'] and tau and g.same(s['cur_now'], tau):
            s['state'] = 'already_typed'
        if not tau:
            s['state'] = 'no_target'
            per.append((s, None, [], collections.Counter()))
            continue
        comp, boundary, reasons = S.expand(n, tau)
        per.append((s, comp, boundary, reasons))
    parent = list(range(len(per)))

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x
    owner = {}
    for idx, (s, comp, b, r) in enumerate(per):
        if r.get('too_large'):
            continue
        for n, v in (comp or {}).items():
            if v['st'] != 'retype' and n != s['node']:
                continue
            if n in owner:
                parent[find(idx)] = find(owner[n])
            else:
                owner[n] = idx
    groups = collections.defaultdict(list)
    for idx in range(len(per)):
        groups[find(idx)].append(idx)
    out = []
    for cid, (root_idx, members) in enumerate(sorted(groups.items())):
        comp, boundary, reasons = {}, [], collections.Counter()
        seeds_here = [per[i][0] for i in members]
        for i in members:
            s, c, b, r = per[i]
            for n, v in (c or {}).items():
                if n in comp and comp[n]['st'] == 'retype' and v['st'] == 'retype' and not g.same(comp[n]['t'], v['t']):
                    comp[n].setdefault('conflict', set()).add(v['t'])
                elif n not in comp or (v['st'] == 'retype' and comp[n]['st'] != 'retype'):
                    comp[n] = dict(v)
            boundary += b
            reasons += r
        pruned = {}
        if comp and not reasons.get('too_large'):
            for _ in range(4):
                res = S.evaluate(comp, boundary)
                prune = PRUNE - ({'member_missing'} if BRIDGE_MEMBERS else set())
                bad = {n: r for n, r in res['node_reasons'].items() if r & prune}
                if not bad:
                    break
                for n, r in bad.items():
                    comp[n]['st'] = 'pruned'
                    pruned[n] = sorted(r)
        res = S.evaluate(comp, boundary) if comp else {
            'changed': 0, 'removed': 0, 'added': 0, 'remaining': 0, 'net': 0, 'casts': [], 'files': set(),
            'reasons': {seeds_here[0].get('state', 'no_component')}, 'evidence': collections.Counter(), 'int_casts': 0}
        res['reasons'] |= set(reasons)
        res['pruned'] = pruned
        out.append(('C%04d' % cid, seeds_here, comp, boundary, res))
    return S, out


def split_pieces(S, comps):
    """After pruning, a merged component falls apart into connected pieces of retyped nodes; each piece is one
    transaction.  Seeds whose own node was pruned stay together in a '<cid>.held' row; pieces no seed touches
    (reached only through a node that was later pruned) are dropped and counted."""
    out = []
    dropped_side = [0]
    for cid, seeds_here, comp, boundary, res in comps:
        changed = [n for n, v in comp.items() if v['st'] == 'retype']
        # a seed already of its target type (a floor tie) joins the pieces it touches into one transaction
        connectors = {x.get('node') for x in seeds_here if (comp.get(x.get('node')) or {}).get('st') == 'ok'}
        cs, seen, pieces = set(changed) | connectors, set(), []
        for n in changed + sorted(connectors):
            if n in seen:
                continue
            stack, piece = [n], set()
            while stack:
                x = stack.pop()
                if x in seen:
                    continue
                seen.add(x)
                piece.add(x)
                stack.extend(m for kind, i, m in S.adj.get(x, ()) if m in cs and m not in seen)
            if piece - connectors:
                pieces.append(piece)
        if len(pieces) <= 1 and all(s.get('node') in cs or not cs for s in seeds_here):
            out.append((cid, seeds_here, comp, boundary, res))
            continue
        assigned = set()
        for k, piece in enumerate(sorted(pieces, key=lambda p: (-len(p), sorted(p)[0]))):
            sh = [x for x in seeds_here if x.get('node') in piece]
            if not sh:
                dropped_side[0] += 1          # retyped only on the way to a node later pruned: not this row's job
                continue
            sub = {n: (dict(v) if n in piece or v['st'] != 'retype' else dict(v, st='outside')) for n, v in comp.items()}
            assigned.update(id(x) for x in sh)
            r = S.evaluate(sub, boundary)
            r['reasons'] |= res['reasons'] - PRUNE
            r['pruned'] = res.get('pruned', {})
            out.append(('%s.%d' % (cid, k), sh, sub, boundary, r))
        rest = [x for x in seeds_here if id(x) not in assigned]
        if rest:
            sub = {n: (dict(v) if v['st'] != 'retype' else dict(v, st='outside')) for n, v in comp.items()}
            r = {'changed': 0, 'removed': 0, 'added': 0, 'remaining': 0, 'net': 0, 'casts': [], 'files': set(),
                 'reasons': set(res['reasons']), 'evidence': collections.Counter(), 'int_casts': 0,
                 'pruned': res.get('pruned', {}), 'node_reasons': {}}
            out.append(('%s.held' % cid, rest, sub, [], r))
    split_pieces.dropped = dropped_side[0]
    return out


def verdict_of(g, rt, seeds_here, comp, res):
    changed = sorted(n for n, v in comp.items() if v['st'] == 'retype')
    hard = {'conflict', 'arity', 'too_large', 'no_definition', 'ambiguous_definition', 'no_target', 'no_component'}
    ev_bad = sum(res['evidence'].get(k, 0) for k in ('wrong', 'unproven', 'view_member_missing'))
    new_casts = [c for c in res['casts'] if c['new']]
    new_bad = [c for c in new_casts if c['evidence'] in ('wrong',)]
    unbacked = [n for n in changed if n.startswith('P:') and not rt.pointer_cells(n) and not comp[n].get('seed') == n]
    if not changed:
        if all(s.get('state') == 'already_typed' for s in seeds_here):
            return 'already_typed', changed
        return 'hold', changed
    if res['reasons'] & hard:
        return 'hold', changed
    if res['net'] < 0 and ev_bad == 0 and 'member_missing' not in res['reasons']:
        return 'whole', changed
    if not new_bad:
        return 'bridge', changed
    res['reasons'].add('new_cast_contradicted')
    return 'hold', changed


def dryrun_main(a):
    import time
    t0 = time.time()
    g = Graph(a.graph)
    rt = Runtime(a.rt, g)
    out = Path(a.out)
    out.mkdir(parents=True, exist_ok=True)
    seeds = load_seeds(a.holds or [], a.actor_holds or [], tuple(a.grades))
    seeds += load_seed_tsv(getattr(a, 'seed_tsv', None) or [])
    S0 = Solver(g, rt)
    S0.scope = tuple(getattr(a, 'scope', None) or ())
    import functools
    for obj, names in ((rt, ('winner', 'pointer_cells', 'scalar_share', 'node_type')), (S0, ('polymorphic', 'void_pays'))):
        for name in names:      # graph and runtime are immutable during a solve
            setattr(obj, name, functools.lru_cache(maxsize=None)(getattr(obj, name)))
    if getattr(a, 'rt_seeds', False):
        extra, notes = rt_seeds(g, rt, S0)
        have = {node_for(g, s) for s in seeds}
        extra = [s for s in extra if s['node_key'] not in have]
        seeds += extra
        write_tsv(out / 'rt_seeds.tsv', extra, ['src', 'file', 'function', 'arg', 'node_key', 'cur', 'target', 'reason'])
        write_tsv(out / 'rt_seed_notes.tsv', [dict(src=a_, node=b_, voted=c_, reason=d_) for a_, b_, c_, d_ in notes],
                  ['src', 'node', 'voted', 'reason'])
    write_slots(g, rt, S0, out)
    print('graph: %d functions, %d edges, %d uses; %d seeds (%.0fs)' % (
        len(g.functions), len(g.edges), len(g.uses), len(seeds), time.time() - t0), flush=True)
    S, comps = solve_all(g, rt, seeds, S0)
    merged = {cid: (len(sh), sum(1 for v in c.values() if v['st'] == 'retype')) for cid, sh, c, b, r in comps}
    comps = split_pieces(S, comps)
    rows, bridge_rows = [], []
    (out / 'components').mkdir(exist_ok=True)
    for cid, seeds_here, comp, boundary, res in comps:
        verdict, changed = verdict_of(g, rt, seeds_here, comp, res)
        for sd in seeds_here:
            st = (comp.get(sd.get('node')) or {}).get('st')
            if sd.get('state') in ('no_definition', 'no_target', 'out_of_scope'):
                sd['outcome'] = 'hold:' + sd['state']
            elif st == 'pruned':
                sd['outcome'] = 'hold:' + '+'.join(res['pruned'].get(sd['node'], ['pruned']))
            elif st == 'ok' and verdict in ('whole', 'bridge', 'hold'):
                sd['outcome'] = 'already_typed' if not changed else verdict + '(seed_ok)'
            else:
                sd['outcome'] = verdict if verdict != 'hold' else 'hold:' + (res['reasons'] & {'too_large', 'new_cast_contradicted'} and
                                                                              '+'.join(sorted(res['reasons'] & {'too_large', 'new_cast_contradicted'})) or 'other')
            sd['component'] = cid
        files = {f for f in res['files'] if f}
        folders = {folder(f) for f in files}
        subsystems = {'/'.join(f.split('/')[:2]) for f in files}
        seed_folders = {folder(s['file']) for s in seeds_here}
        rows.append({
            'component': cid, 'seeds': len(seeds_here),
            'seed_sources': ','.join(sorted({s['src'] for s in seeds_here})),
            'seed_rows': ';'.join('%s#%s' % (s['function'], s['arg']) for s in seeds_here),
            'targets': ';'.join(sorted({s['tau'] for s in seeds_here if s.get('tau')})),
            'holds': ';'.join(sorted({s['hold'] for s in seeds_here})),
            'nodes': len(comp), 'changed': len(changed),
            'runtime_backed': sum(1 for n in changed if rt.pointer_cells(n)),
            'evidence': evidence_of(rt, S, changed),
            'boundary': len(boundary), 'files': len(files), 'folders': len(folders),
            'seed_folders': len(seed_folders), 'subsystems': len(subsystems),
            'folder_list': ' '.join(sorted(folders)), 'removed': res['removed'], 'added': res['added'],
            'net': res['net'], 'remaining': res['remaining'],
            'ev_correct': res['evidence'].get('correct', 0), 'ev_neutral': res['evidence'].get('neutral', 0),
            'ev_wrong': res['evidence'].get('wrong', 0), 'ev_unproven': res['evidence'].get('unproven', 0),
            'int_casts': res['int_casts'], 'pruned': len(res.get('pruned', {})) if '.' not in cid else 0,
            'merged_from': cid.split('.')[0], 'merged_seeds': merged.get(cid.split('.')[0], (0, 0))[0],
            'unbacked_params': sum(1 for n in changed if n.startswith('P:') and not rt.pointer_cells(n)),
            'whole_blockers': ','.join(whole_blockers(res)),
            'seeds_landable': sum(1 for sd in seeds_here if sd['outcome'].startswith(('whole', 'bridge'))),
            'verdict': verdict, 'reasons': ','.join(sorted(res['reasons'])),
            'changed_nodes': ' '.join(changed[:40]) + (' ...' if len(changed) > 40 else ''),
        })
        for c in res['casts']:
            if c['new']:
                bridge_rows.append(dict(component=cid, verdict=verdict, retired_by=retired_by(g, rt, c),
                                        **{k: c[k] for k in ('file', 'fn', 'line', 'cast', 'from_type', 'evidence',
                                                             'edge', 'src', 'dst', 'off')}))
        with open(out / 'components' / (cid + '.json'), 'w') as fh:
            json.dump({'seeds': seeds_here, 'verdict': verdict,
                       'comp': {n: {k: (sorted(v) if isinstance(v, set) else v) for k, v in d.items()} for n, d in comp.items()},
                       'boundary': boundary, 'casts': res['casts'],
                       'result': {k: (sorted(v) if isinstance(v, set) else v) for k, v in res.items() if k != 'casts'}},
                      fh, indent=1, default=str)
    write_tsv(out / 'components.tsv', rows)
    write_tsv(out / 'seeds.tsv', seeds, ['src', 'file', 'function', 'arg', 'node', 'cur', 'cur_now', 'target',
                                         'tau', 'rt_type', 'rt_share', 'hold', 'state',
                                         'component', 'outcome'])
    write_tsv(out / 'predicted_bridge_casts.tsv', bridge_rows)
    needs = collections.defaultdict(lambda: dict(nodes=set(), sites=set(), names=collections.Counter()))
    for tau, off, mtype, member, view, node, site in S.member_needs:
        k = needs[(tau, off, mtype)]
        k['nodes'].add(node); k['sites'].add(site); k['names'][member] += 1
    def existing(tau, off):
        rec = g.record_of(tau)
        size = g.size(rec) if rec else None
        if size is not None and off >= size:
            return 'beyond the record (0x%X bytes): a containing/next object, not a member' % size
        leaves = list(g.leaves(rec, off)) if rec else []
        real = [(path, typ) for path, typ in leaves if not re.match(r'^(pad|unused)', path.split('[')[0].split('.')[-1])]
        if not real:
            return 'add' + (' (inside %s)' % leaves[0][0].split('[')[0] if leaves else '')
        return 'reconcile with ' + ', '.join('%s:%s' % pt for pt in real[:3])
    write_tsv(out / 'member_needs.tsv', [
        dict(target=tau.rstrip(' *'), offset='0x%X' % off, member_type=mtype, action=existing(tau, off),
             nodes_blocked=len(v['nodes']), sites=len(v['sites']),
             view_names=' '.join(n for n, _ in v['names'].most_common(3)), example=sorted(v['sites'])[0])
        for (tau, off, mtype), v in sorted(needs.items(), key=lambda kv: -len(kv[1]['nodes']))],
        ['target', 'offset', 'member_type', 'action', 'nodes_blocked', 'sites', 'view_names', 'example'])
    summary = summarize(rows, seeds)
    summary['holder_check'] = holder_check(g, seeds)
    summary['merged_components'] = len(merged)
    summary['dropped_side_pieces'] = getattr(split_pieces, 'dropped', 0)
    summary['whole_blockers_of_bridge'] = dict(collections.Counter(b for r in rows if r['verdict'] == 'bridge'
                                                                   for b in r['whole_blockers'].split(',') if b))
    summary['bridge_netfalls'] = sum(1 for r in rows if r['verdict'] == 'bridge' and r['net'] < 0)
    summary['bridge_with_unbacked_params'] = sum(1 for r in rows if r['verdict'] == 'bridge' and r['unbacked_params'])
    summary['folder_crossing_by_size'] = {b: [sum(1 for r in rows if bucket(r['changed']) == b),
                                              sum(1 for r in rows if bucket(r['changed']) == b and r['folders'] > 1)]
                                          for b in ('1', '2-3', '4-10', '11-50', '>50')}
    summary['seed_outcomes'] = dict(collections.Counter(sd.get('outcome', '?').split('(')[0] for sd in seeds))
    summary['seed_outcomes_by_source'] = {src: dict(collections.Counter(sd.get('outcome', '?').split(':')[0].split('(')[0]
                                                                         for sd in seeds if sd['src'] == src))
                                          for src in sorted({sd['src'] for sd in seeds})}
    (out / 'summary.json').write_text(json.dumps(summary, indent=1))
    print(json.dumps(summary, indent=1))


def evidence_of(rt, S, changed):
    """Which runtime tables back the changed nodes: fn_args (entry cells), site (H9 call-site cells), value (H8
    pointer values at an access site), slot (H8 installed callbacks)."""
    c = collections.Counter()
    for n in changed:
        if n in rt.cells:
            c['fn_args'] += 1
        elif n in getattr(rt, 'derived', {}):
            c['site' if n.startswith(('L:', 'P:')) else 'value'] += 1
        holder = re.sub(r'#(\d+|ret)$', '', n)
        if holder in getattr(S, 'slots', {}) or (n.startswith(('P:', 'R:')) and re.sub(
                r'#\d+$', '', n[2:]) in getattr(S, 'slot_fns', ())):
            c['slot'] += 1
    return ','.join('%s:%d' % kv for kv in sorted(c.items()))


def write_slots(g, rt, S, out):
    """slots.tsv: every slot holder the runtime saw a function in, its installed callbacks and prototypes."""
    S.slot_fns = {f for fns in S.slots.values() for f in fns}
    rows = []
    for h, fns in sorted(S.slots.items(), key=lambda kv: -sum(kv[1].values())):
        protos = collections.Counter()
        for f in fns:
            d = g.fn_def(f)
            if d:
                protos['%s(%s)' % (d['ret'], ', '.join(p['type'] for p in d['params']))] += 1
        rows.append({'holder': h, 'declared': g.declared(h), 'callbacks': len(fns), 'calls': sum(fns.values()),
                     'prototypes': len(protos), 'agree': 'yes' if len(protos) == 1 else 'no',
                     'prototype_votes': '; '.join('%s=%d' % kv for kv in protos.most_common(4)),
                     'functions': ' '.join(sorted(f.split('@')[0] for f in fns)[:12]),
                     'sites': ' '.join(sorted(S.slot_sites[h])[:4])})
    for h, fns in sorted(S.untyped_slots.items(), key=lambda kv: -sum(kv[1].values())):
        rows.append({'holder': h, 'declared': g.declared(h), 'callbacks': len(fns), 'calls': sum(fns.values()),
                     'prototypes': 0, 'agree': 'untyped_holder', 'prototype_votes': '',
                     'functions': ' '.join(sorted(f.split('@')[0] for f in fns)[:12]), 'sites': ''})
    write_tsv(out / 'slots.tsv', rows, ['holder', 'declared', 'callbacks', 'calls', 'prototypes', 'agree',
                                        'prototype_votes', 'functions', 'sites'])
    write_tsv(out / 'slot_plan.tsv', slot_plan(g, rt, S),
              ['holder', 'declared', 'callbacks', 'proposed', 'basis', 'retype_callbacks', 'contradicting_callbacks',
               'retype', 'contradicting'])


def slot_plan(g, rt, S):
    """One prototype per slot family: per parameter position the runtime-voted type of the cells every installed
    callback received (share >= 0.75), else the type two thirds of the callbacks already declare, else void * (a
    generic slot).  Lists the callbacks whose placeholder parameters would take it and those that contradict it."""
    rows = []
    for h, fns in sorted(S.slots.items(), key=lambda kv: -sum(kv[1].values())):
        defs = {f: g.fn_def(f) for f in fns if g.fn_def(f)}
        if len(defs) < 2:
            continue
        arity = collections.Counter(len(d['params']) for d in defs.values()).most_common(1)[0][0]
        proposed, basis, retype, contra = [], [], set(), set()
        for j in range(arity):
            cells = collections.Counter()
            declared = collections.Counter()
            for f, d in defs.items():
                if j < len(d['params']):
                    cells.update(rt.pointer_cells('P:%s#%d' % (f, j)))
                    if g.cls(d['params'][j]['type']) == 'real':
                        declared[canon_display(g, d['params'][j]['type'])] += 1
            tau, sh = cells_type(rt, cells)
            if tau and sh >= 0.75 and g.cls(canon_display(g, tau)) == 'real':
                pick, why = canon_display(g, tau), 'runtime'
            elif declared and declared.most_common(1)[0][1] * 3 >= 2 * len(defs):
                pick, why = declared.most_common(1)[0][0], 'declared'
            else:
                ints = sum(1 for d in defs.values() if j < len(d['params']) and g.cls(d['params'][j]['type']) in ('int', 'small'))
                pick, why = ('s32', 'declared_int') if ints * 3 >= 2 * len(defs) and not cells else ('void *', 'generic')
            proposed.append(pick)
            basis.append(why)
            for f, d in defs.items():
                if j >= len(d['params']):
                    continue
                have = d['params'][j]['type']
                if g.same(have, pick) or pick == 'void *':
                    continue
                if g.cls(have) in OPEN:
                    retype.add('%s#%d' % (f.split('@')[0], j))
                elif g.cls(have) == 'real' and why == 'runtime':
                    contra.add('%s#%d' % (f.split('@')[0], j))
        rets = collections.Counter(d['ret'] for d in defs.values())
        rows.append({'holder': h, 'declared': g.declared(h), 'callbacks': len(defs),
                     'proposed': '%s (*)(%s)' % (rets.most_common(1)[0][0], ', '.join(proposed)),
                     'basis': ','.join(basis), 'retype_callbacks': len({x.split('#')[0] for x in retype}),
                     'contradicting_callbacks': len({x.split('#')[0] for x in contra}),
                     'retype': ' '.join(sorted(retype)[:20]), 'contradicting': ' '.join(sorted(contra)[:20])})
    return rows


def whole_blockers(res):
    out = []
    if res['net'] >= 0:
        out.append('net>=0')
    for c in res['casts']:
        tag = c['evidence'] + ('_new' if c['new'] else '_kept')
        if c['evidence'] in ('wrong', 'unproven', 'view_member_missing') and tag not in out:
            out.append(tag)
    return sorted(out)


def retired_by(g, rt, c):
    """Which missing type (or typing step) would remove this cast."""
    ev = c['evidence']
    if ev == 'placeholder_view':
        rtype, share, _ = rt.node_type(c['dst'])
        return 'type %s (still %s)%s' % (c['dst'], c['cast'], (' -> runtime says ' + canon_display(g, rtype)) if rtype else '')
    if ev in ('neutral', 'int') and g.cls(c.get('from_type')) in ('int', 'small'):
        return 'retype integer holder %s to a pointer' % c['src']
    if ev == 'neutral':
        return 'byte view: needs a member at +0x%X of %s' % (c['off'], c.get('from_type')) if c['off'] else \
            'retype %s from %s' % (c['dst'], c['cast'])
    if ev == 'correct':
        return 'co-view: fold %s into %s' % (c['cast'], c.get('from_type'))
    if ev == 'view_member_missing':
        return 'add member +0x%X to %s' % (c['off'], c.get('from_type'))
    if ev == 'unproven':
        return 'no runtime label on %s' % c['src']
    return 'contradicted: %s' % ev


def holder_check(g, seeds):
    """Every `caller_holder:<fn>:<kind>:<type>:<expr>` named by a proto1 hold must be an edge into the seed
    parameter from <fn> in the graph (the graph sees what the hold saw)."""
    by_dst = collections.defaultdict(set)
    for e in g.edges:
        if e['k'] == 'arg':
            by_dst[e['dst']].add(e['fn'].split('@')[0])
    found = missing = indirect = 0
    miss = []
    for s in seeds:
        for m in re.finditer(r'caller_holder:([A-Za-z_]\w*):', s.get('reason', '')):
            if m.group(1) in by_dst.get(s.get('node', ''), ()):
                found += 1
            elif not any(c['caller'].split('@')[0] == m.group(1) and c['callee'].split('@')[0] == s['function']
                         for c in g.calls_to.get(s.get('node', 'P:x#0')[2:].rpartition('#')[0], ())):
                indirect += 1
            else:
                missing += 1
                miss.append('%s#%s<-%s' % (s['function'], s['arg'], m.group(1)))
    return {'found': found, 'runtime_only_indirect': indirect, 'missing': missing, 'missing_rows': miss[:20]}


def write_tsv(path, rows, cols=None):
    if not rows and not cols:
        Path(path).write_text('')
        return
    cols = cols or list(rows[0].keys())
    with open(path, 'w') as fh:
        w = csv.DictWriter(fh, cols, delimiter='\t', extrasaction='ignore')
        w.writeheader()
        w.writerows(rows)


def bucket(c):
    return '0' if c == 0 else '1' if c == 1 else '2-3' if c <= 3 else '4-10' if c <= 10 else '11-50' if c <= 50 else '>50'


def summarize(rows, seeds):
    vc = collections.Counter(r['verdict'] for r in rows)
    seeds_by_verdict = collections.Counter()
    for r in rows:
        seeds_by_verdict[r['verdict']] += r['seeds']

    sizes = collections.Counter(bucket(r['changed']) for r in rows)
    return {
        'seeds': len(seeds), 'seed_sources': dict(collections.Counter(s['src'] for s in seeds)),
        'components': len(rows), 'verdicts': dict(vc), 'seeds_by_verdict': dict(seeds_by_verdict),
        'size_changed_nodes': dict(sizes),
        'multi_seed_components': sum(1 for r in rows if r['seeds'] > 1),
        'crossing_folders': sum(1 for r in rows if r['folders'] > 1),
        'crossing_subsystems': sum(1 for r in rows if r['subsystems'] > 1),
        'predicted_net_casts': {v: sum(r['net'] for r in rows if r['verdict'] == v) for v in vc},
        'predicted_removed': {v: sum(r['removed'] for r in rows if r['verdict'] == v) for v in vc},
        'predicted_added': {v: sum(r['added'] for r in rows if r['verdict'] == v) for v in vc},
        'hold_reasons': dict(collections.Counter(x for r in rows if r['verdict'] == 'hold'
                                                 for x in r['reasons'].split(',') if x)),
    }


def add_parsers(sub):
    d = sub.add_parser('dryrun')
    d.add_argument('--graph', required=True)
    d.add_argument('--rt', required=True)
    d.add_argument('--holds', nargs='*')
    d.add_argument('--actor-holds', nargs='*')
    d.add_argument('--grades', nargs='*', default=['A'])
    d.add_argument('--seed-tsv', nargs='*', help='seed rows (file, function, arg, target), e.g. a previous seeds.tsv')
    d.add_argument('--rt-seeds', action='store_true', help='add H8/H9 seeds (rt_intptr, rt_slot, rt_split)')
    d.add_argument('--scope', nargs='*', help='path prefixes a lane may edit: nodes declared elsewhere are boundaries')
    d.add_argument('--out', required=True)


def dispatch(a):
    if a.cmd == 'dryrun':
        return dryrun_main(a)
