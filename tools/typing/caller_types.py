#!/usr/bin/env python3
"""Caller-type worklist: pointer parameters typed as a view while their callers pass one shared record.

    caller_types.py run --out DIR [--codemap DB] [--root R] [--workers 4] [--no-reextract]
    caller_types.py fixture --root FIXTURE --out DIR      (clang over every src/*.c of a small tree)
    caller_types.py show --out DIR FUNCTION               (the rows of one function, from a finished run)

The defect class: a parameter typed as a generated per-function view (S_<ADDR>_<n>, Row_, Rec_, B<n>_,
R12_, *_pre, Func<ADDR>State), a file-local struct, `void *` or a byte pointer, when every caller passes
one shared record (ActorRecord, ObjectNodeHeader, ObjectPosition, SpriteFrameState, ...).  Record identity
comes from the callers first (AUDIT_RULES R3: creator, callback slot or caller provenance), and only then
is the view's shape tested against that record; a shape match alone never proposes a type.

Input is the type-flow graph that codemap.db already stores per TU (flow_tu: tools/typing/type_flow.Extract
over one clang parse).  The map is checked against the tree by file sha; TUs whose include closure changed
are re-extracted with clang (the same extractor) unless --no-reextract.  Nothing is written to the tree.

Evidence per (definition, parameter index):
  call      a direct call's argument: the static type of the value through explicit casts (type_flow's
            `st`), through locals whose every assignment agrees, and through the caller's own weakly typed
            parameter (resolved transitively from that parameter's callers)
  dispatch  the function's address stored in a node header update slot (ObjectNodeHeader.update_callback,
            or a +0x10 `unk_10`/`callback` slot of a generated view), passed to register_node, or passed to a
            parameter that some function stores into such a slot: active-node and draw dispatch pass
            (body, ObjectPosition *, SpriteFrameState *).  The body is reported as unknown (its record comes
            from the creator, which the graph does not tie to the slot's object).
  slot      the address stored in a typed function-pointer slot, table or parameter: the slot's own
            parameter types (and a slot_mismatch note when they differ from the definition)
Callers are bound to a definition by key (static functions are file-scoped), the caller's own TU, a
unique name, the retail call binding (codemap call_bind: caller file -> callee files), then the longest
shared directory; anything else is counted as ambiguous and not attributed.  A unique name whose file
the caller's retail binding never reaches is kept with bind `unique_other_copy` (a bank twin).

Accessed fields of a parameter: its member accesses, cast member accesses (`((T *)p)->m`) and raw
dereferences (`*(s16 *)((u8 *)p + K)`) through the parameter and locals that only ever hold it (plus a
constant offset).  Negative offsets are node header accesses and are reported apart.  A view with no
observed access falls back to its declared non-pad members.

Classes:
  A  every piece of evidence names the same record R (no unknown), and every accessed field lands on a
     field of R with the same offset and width (signedness differences are listed separately)
  B  the known evidence agrees on R, but some evidence is unknown, or no field was observed, or some
     accesses land in R's undeclared bytes (pad or byte arrays)
  C  conflicting records, no evidence at all, or an access that conflicts with R (wrong width, straddles a
     field, beyond R's size); R is then not proposed.  The other shared records the shape fits are listed
     as `shape_only` and are never proposed.

Outputs (DIR): caller_types.tsv (ranked worklist), summary.md, evidence.jsonl (every evidence item).
"""
from __future__ import annotations

import argparse
import bisect
from collections import Counter, defaultdict
from concurrent.futures import ProcessPoolExecutor
import csv
import gzip
import hashlib
import json
import os
from pathlib import Path
import re
import sqlite3
import sys

HERE = Path(__file__).resolve().parent
TOOLS = HERE.parent
DEFAULT_ROOT = TOOLS.parent

GENERATED = re.compile(r'(?:^|_)S_(?:func_)?[0-9A-Fa-f]{6,8}(?:_|$)|^Row_|^Rec_|^R\d+_|^B\d+_|_pre$|'
                       r'^Func[0-9A-Fa-f]{8}|[0-9A-Fa-f]{8}')
VIEW_NAME = re.compile(r'Views?$')
# Named records that are documented overlays rather than allocated objects: never a fold target.
# ScratchPad is the generic b[]/h[]/w[] index view of the scratchpad (R13): it fits any shape.
NOT_TARGETS = {'EntityRec', 'ScratchPad'}
SHARED_PREFERENCE = ('ActorRecord', 'ObjectNodeHeader', 'ObjectPosition', 'SpriteFrameState', 'ParticleState',
                     'TownObjectRecord', 'PlayerRecord')
NODE_HEADER = 'ObjectNodeHeader'
NODE_HEADER_SIZE = 0x20
DISPATCH_PARAMS = {1: 'ObjectPosition', 2: 'SpriteFrameState'}   # index 0 is the body
DRAW_REGISTRARS = {('register_node', 1)}
UPDATE_SLOT_NAMES = re.compile(r'^(?:unk_10|callback|update|update_fn|func_10|field_10)$')
SCALAR_SIZE = {
    'char': 1, 'signed char': 1, 'unsigned char': 1, '_Bool': 1,
    'short': 2, 'short int': 2, 'signed short': 2, 'unsigned short': 2, 'unsigned short int': 2,
    'int': 4, 'signed int': 4, 'signed': 4, 'unsigned int': 4, 'unsigned': 4, 'long': 4, 'long int': 4,
    'unsigned long': 4, 'unsigned long int': 4, 'float': 4, 'enum': 4,
    'long long': 8, 'unsigned long long': 8, 'double': 8,
    's8': 1, 'u8': 1, 's16': 2, 'u16': 2, 's32': 4, 'u32': 4, 's64': 8, 'u64': 8, 'f32': 4,
    'u_char': 1, 'u_short': 2, 'u_int': 4, 'u_long': 4,
}
UNNAMED = re.compile(r'\(unnamed (?:struct |union |enum )?at ([^)]*)\)')
FNPTR = re.compile(r'\(\s*\*\s*\w*\s*(?:const\s*)?\)\s*\(')


# --------------------------------------------------------------------------- small type helpers

def split_params(spelled):
    """'void (*)(a *, b)' / 'void (a *, b)' -> (['a *', 'b'], has_proto); last top-level paren group."""
    t = (spelled or '').strip()
    depth, cut = 0, None
    for i in range(len(t) - 1, -1, -1):
        c = t[i]
        if c == ')':
            depth += 1
        elif c == '(':
            depth -= 1
            if depth == 0:
                cut = i
                break
    if cut is None:
        return [], False
    inner = t[cut + 1:t.rfind(')')].strip()
    if inner == '':
        return [], False
    if inner == 'void':
        return [], True
    out, depth, cur = [], 0, ''
    for c in inner:
        if c == ',' and depth == 0:
            out.append(cur.strip())
            cur = ''
            continue
        depth += c in '(['
        depth -= c in ')]'
        cur += c
    out.append(cur.strip())
    return [x for x in out if x != '...'], True


PARAM_NODE = re.compile(r'^P:(.+)#(\d+)$')


def param_node(node):
    """'P:fn#2' -> ('fn', 2); None for anything else (derefs 'P:fn#2*', slots, fields)."""
    m = PARAM_NODE.match(node or '')
    return (m.group(1), int(m.group(2))) if m else None


def clean(t):
    t = re.sub(r'\b(?:const|volatile|register)\b', ' ', t or '')
    return re.sub(r'\s+', ' ', t).replace(' *', '*').replace('* ', '*').strip()


class Types:
    """Typedef/record resolution over the records and typedefs one TU's flow dump carries."""

    def __init__(self, typedefs, records):
        self.typedefs = typedefs
        self.records = records

    def resolve(self, t, depth=0):
        """'S_X *' -> 'rec:KEY*', 'u16' -> 'unsigned short', fn pointers -> 'fnptr'."""
        t = clean(t)
        if depth > 20:
            return t
        if FNPTR.search(t) or t.startswith('fnptr'):
            return 'fnptr'
        if t.endswith('*'):
            return self.resolve(t[:-1], depth + 1) + '*'
        m = re.match(r'^(.*)\[(\d*)\]$', t)
        if m:
            return self.resolve(m.group(1), depth + 1) + '[' + m.group(2) + ']'
        if t in self.typedefs and clean(self.typedefs[t]) != t:
            return self.resolve(self.typedefs[t], depth + 1)
        m = UNNAMED.search(t)
        if m:
            return 'rec:@' + m.group(1)
        for kw in ('struct ', 'union '):
            if t.startswith(kw):
                return 'rec:' + t[len(kw):].strip()
        if t.startswith('enum '):
            return 'enum'
        if t in self.records:            # tag used bare (clang prints `ActorRecord` for a typedef'd tag)
            return 'rec:' + t
        return t

    def size(self, t):
        r = self.resolve(t)
        if r.endswith('*') or r == 'fnptr':
            return 4
        m = re.match(r'^(.*)\[(\d*)\]$', r)
        if m:
            inner = self.size(m.group(1))
            return inner * int(m.group(2)) if inner and m.group(2) else None
        if r.startswith('rec:'):
            rec = self.records.get(r[4:])
            return rec.get('size') if rec else None
        return SCALAR_SIZE.get(r)

    def sign(self, t):
        r = self.resolve(t)
        if r.endswith('*') or r == 'fnptr':
            return 'p'
        if r.startswith('rec:'):
            return 'r'
        if '[' in r:
            return 'a'
        if r in ('float', 'double'):
            return 'f'
        if r.startswith('unsigned') or r == '_Bool':
            return 'u'
        return 's'

    def pointee_record(self, t):
        """Record key when t is a pointer to a record (one level), else None."""
        r = self.resolve(t)
        if r.endswith('*') and not r.endswith('**') and r[:-1].startswith('rec:'):
            return r[4:-1]
        return None

    def pointee(self, t):
        r = self.resolve(t)
        return r[:-1] if r.endswith('*') else None


def record_kind(key, file, spelled=''):
    """generated | file_local | anonymous | view_named | not_target | named."""
    name = spelled or key
    if GENERATED.search(name) or GENERATED.search(key):
        return 'generated'
    if (file or '').startswith('src/'):
        return 'file_local'
    if key.startswith('@'):
        return 'anonymous'
    if key in NOT_TARGETS or name in NOT_TARGETS:
        return 'not_target'
    if VIEW_NAME.search(name) or VIEW_NAME.search(key):
        return 'view_named'
    return 'named'


def disp(t):
    """Readable spelling: 'u8*' -> 'u8 *', 'X**' -> 'X **'."""
    return re.sub(r'(?<=[^\s*])\*', ' *', clean(t))


def bare_name(spelled):
    t = clean(spelled).rstrip('*').strip()
    for kw in ('struct ', 'union '):
        if t.startswith(kw):
            t = t[len(kw):]
    return t


# --------------------------------------------------------------------------- record leaves (slice match)

def flatten(key, records, types, base=0, prefix='', depth=0, out=None):
    """Every addressable member of record `key`: (off, size, sign, path, pad) with union alternatives,
    nested records and array elements (capped) expanded."""
    out = [] if out is None else out
    rec = records.get(key)
    if not rec or depth > 8:
        return out
    for name, off, ftype, bits in rec.get('fields', ()):
        if bits:
            continue
        if not name:
            continue          # anonymous member: its named children are listed with absolute offsets
        _leaf(base + off, ftype, (prefix + '.' + name) if prefix else name, records, types, depth, out,
              pad=bool(re.match(r'^(?:pad|_pad|filler|unused)', name)))
    return out


def _leaf(off, ftype, path, records, types, depth, out, pad):
    r = types.resolve(ftype)
    size = types.size(ftype)
    m = re.match(r'^(.*)\[(\d*)\]$', r)
    if m:
        out.append((off, size, 'a', path, pad))
        n = int(m.group(2) or 0)
        elt = re.sub(r'\s*\[\d*\]\s*$', '', clean(ftype))
        esize = types.size(elt)
        if esize and n:
            sub = types.resolve(elt)
            cap = 1024 if not sub.startswith('rec:') else 64
            for i in range(min(n, cap)):
                _leaf(off + i * esize, elt, '%s[%d]' % (path, i), records, types, depth + 1, out,
                      pad or (bool(re.match(r'^(?:unk|pad)', path.split('.')[-1])) and not sub.startswith('rec:')))
        return
    if r.startswith('rec:') and not r.endswith('*'):
        out.append((off, size, 'r', path, pad))
        flatten(r[4:], records, types, off, path, depth + 1, out)
        return
    out.append((off, size, types.sign(ftype), path, pad))


_LEAVES = {}


def leaves_of(key, records, types):
    """Cached leaf index of record `key`: (size, by_off, starts, scalar leaves sorted by offset)."""
    ck = (id(records), key)
    if ck not in _LEAVES or _LEAVES[ck][0] is not records:
        rec = records.get(key) or {}
        leaves = flatten(key, records, types) if rec.get('size') else []
        by_off = defaultdict(list)
        for leaf in leaves:
            by_off[leaf[0]].append(leaf)
        scal = sorted((l for l in leaves if l[2] in ('s', 'u', 'p', 'f') and l[1]), key=lambda l: l[0])
        _LEAVES[ck] = (records, (rec.get('size'), by_off, [l[0] for l in scal], scal))
    return _LEAVES[ck][1]


def slice_match(accesses, key, records, types):
    """Test accessed (off, width, sign) fields against record `key`.

    -> {'verdict': full|partial|conflict|unknown, 'fields': [(access, path)], 'sign': [...], 'pad': [...],
        'conflicts': [...]}"""
    res = {'verdict': 'unknown', 'fields': [], 'sign': [], 'pad': [], 'conflicts': []}
    size, by_off, starts, scal = leaves_of(key, records, types)
    if not size:
        return res
    for acc in accesses:
        off, width, sign = acc[0], acc[1], acc[2]
        soft = sign in ('r', 'a')
        if width is None or off < 0 or off + width > size:
            (res['pad'] if soft else res['conflicts']).append((acc, 'beyond size 0x%X' % size))
            continue
        exact = [l for l in by_off.get(off, ()) if l[1] == width]
        named = [l for l in exact if not l[4]]
        if soft:
            if exact:
                res['fields'].append((acc, exact[0][3]))
            else:
                res['pad'].append((acc, 'aggregate width'))
            continue
        scalar = [l for l in named if l[2] in ('s', 'u', 'p', 'f')]
        if scalar:
            same = [l for l in scalar if l[2] == sign]
            pick = same[0] if same else scalar[0]
            res['fields'].append((acc, pick[3]))
            if not same:
                # signedness (s/u) or a pointer read as an integer (p/s, p/u): same width, noted apart
                res['sign'].append((acc, pick[3], pick[2]))
            continue
        # no exact named scalar: undeclared bytes (pad, byte arrays) or a conflict with a named field
        lo = bisect.bisect_left(starts, off - 8)
        hi = bisect.bisect_left(starts, off + width)
        near = scal[lo:hi]
        overlap = [l for l in near if l[0] < off + width and off < l[0] + l[1]]
        real = [l for l in overlap if not l[4] and not _byte_array_elem(l)]
        if exact and not named:
            res['pad'].append((acc, exact[0][3]))
        elif real:
            covering = [l for l in real if l[0] <= off and off + width <= l[0] + l[1]]
            res['conflicts'].append((acc, ('covers ' if covering else 'straddles ') +
                                     ','.join(sorted({l[3] for l in real}))[:80]))
        else:
            res['pad'].append((acc, 'undeclared bytes'))
    if res['conflicts']:
        res['verdict'] = 'conflict'
    elif res['pad']:
        res['verdict'] = 'partial'
    elif res['fields']:
        res['verdict'] = 'full'
    return res


def _byte_array_elem(leaf):
    return bool(re.search(r'\[\d+\]$', leaf[3])) and leaf[1] == 1 and re.match(r'^(?:unk|pad|bytes|b)', leaf[3].split('.')[-1])


# --------------------------------------------------------------------------- loading flows

def flows_from_codemap(db_path, root, reextract=True, workers=4, log=print, scope=None):
    """[(tu, flow dict)] from codemap.db, re-extracting TUs whose include closure no longer matches."""
    db = sqlite3.connect('file:%s?mode=ro' % db_path, uri=True)
    stored = dict(db.execute('SELECT path, sha256 FROM source_file'))
    current = {}

    def sha(rel):
        if rel not in current:
            try:
                current[rel] = hashlib.sha256((root / rel).read_bytes()).hexdigest()
            except OSError:
                current[rel] = None
        return current[rel]

    stale = []
    closures = {}
    for path, headers in db.execute('SELECT path, headers FROM tu'):
        files = [path] + [h for h in json.loads(headers or '[]') if h.startswith(('src/', 'include/'))]
        closures[path] = files
        if any(stored.get(f) != sha(f) for f in files):
            stale.append(path)
    live = {str(p.relative_to(root)) for p in (root / 'src').rglob('*.c')}
    new = sorted(live - set(closures))
    flows = []
    stale_set = set(stale)
    for tu, blob in db.execute('SELECT tu, blob FROM flow_tu'):
        if tu in stale_set or tu not in live or (scope and not tu.startswith(tuple(scope))):
            continue
        flows.append((tu, json.loads(gzip.decompress(blob))))
    redo = [t for t in sorted(stale_set & live) + new if not scope or t.startswith(tuple(scope))]
    info = {'codemap_tus': len(closures), 'flow_tus': len(flows), 'stale_tus': len(stale), 'new_tus': len(new),
            'reextracted': 0, 'extract_errors': []}
    if redo and reextract:
        log('re-extracting %d stale/new TUs with clang' % len(redo))
        got, errors = extract_flows(root, redo, workers)
        flows.extend(got)
        info['reextracted'] = len(got)
        info['extract_errors'] = errors
    elif redo:
        info['extract_errors'] = ['not re-extracted: %s' % t for t in redo[:20]]
    bind = call_bind_files(db)
    return flows, bind, info


def call_bind_files(db):
    """caller source file -> set of callee source files, from the retail call binding (link maps)."""
    out = defaultdict(set)
    try:
        src = dict(db.execute('SELECT id, source FROM recipe'))
        for caller, callee in db.execute('SELECT DISTINCT caller_recipe, callee_recipe FROM call_bind '
                                         'WHERE callee_recipe IS NOT NULL'):
            a, b = src.get(caller), src.get(callee)
            if a and b:
                out[a].add(b)
    except sqlite3.Error:
        pass
    return out


def _extract_one(args):
    root, rel = args
    for p in (str(TOOLS), str(HERE)):
        if p not in sys.path:
            sys.path.insert(0, p)
    import cast_ast as A
    import type_flow as TF
    try:
        unit, err = A.clang_unit(Path(root), rel)
    except Exception as exc:          # one failing TU is reported, never fatal
        return rel, None, 'clang: %s' % str(exc)[-200:]
    if unit is None:
        return rel, None, 'parse: %s' % err
    try:
        return rel, TF.Extract(unit).run().dump(), err
    except Exception as exc:
        return rel, None, 'type_flow: %s: %s' % (type(exc).__name__, str(exc)[-200:])


def extract_flows(root, tus, workers=1):
    root = Path(root).resolve()
    out, errors = [], []
    jobs = [(str(root), t) for t in tus]
    if workers <= 1:
        results = map(_extract_one, jobs)
    else:
        pool = ProcessPoolExecutor(max_workers=workers)
        results = pool.map(_extract_one, jobs, chunksize=4)
    for rel, flow, err in results:
        if flow is None:
            errors.append('%s: %s' % (rel, err))
        else:
            out.append((rel, flow))
    return out, errors


# --------------------------------------------------------------------------- the model

def norm_file(rel, path):
    """Tree-relative spelling of a location file.  SLUS partition TUs are parsed through a generated
    compilation input (a temporary file): those locations map to the TU itself, flagged with a `p` line."""
    if not path or path.startswith(('src/', 'include/')):
        return path, False
    m = re.search(r'(?:^|/)((?:src|include)/.*)$', path)
    if m and 'partition_sources' not in path:
        return m.group(1), False
    return rel, True


def normalize_flow(rel, flow, root=None):
    """Rewrite generated-input locations of one flow dump in place (see norm_file)."""
    text = None
    for fn in flow.get('functions', ()):
        f, generated = norm_file(rel, fn['file'])
        if generated:
            if text is None:
                try:
                    text = (Path(root) / rel).read_text(errors='replace').splitlines() if root else []
                except OSError:
                    text = []
            pat = re.compile(r'^[^;#/]*\b%s\s*\(' % re.escape(fn['name']))
            fn['line'] = next((i + 1 for i, x in enumerate(text) if pat.match(x) and not x.rstrip().endswith(';')),
                              'p%s' % fn['line'])
        fn['file'] = f
    for coll in ('edges', 'uses', 'calls'):
        for e in flow.get(coll, ()):
            f, generated = norm_file(rel, e.get('file'))
            if generated:
                e['line'] = 'p%s' % e.get('line')
            e['file'] = f
    return flow


class TU:
    def __init__(self, rel, flow):
        self.rel = rel
        self.flow = flow
        self.T = Types(flow.get('typedefs', {}), flow.get('records', {}))
        self.assigns = defaultdict(list)     # (fn, dst) -> [edge]
        self.fn_assigns = defaultdict(dict)  # fn -> {dst: [edge]}
        self.by_src = defaultdict(list)      # (fn, src) -> [edge]
        self.uses = defaultdict(list)        # (fn, node) -> [use]
        for e in flow.get('edges', ()):
            if e['k'] in ('init', 'assign'):
                self.assigns[(e['fn'], e['dst'])].append(e)
                self.fn_assigns[e['fn']].setdefault(e['dst'], []).append(e)
            if e.get('src'):
                self.by_src[(e['fn'], e['src'])].append(e)
        for u in flow.get('uses', ()):
            self.uses[(u['fn'], u['node'])].append(u)
        self.fn_keys = {f['key'] for f in flow.get('functions', ())}


class Model:
    def __init__(self, flows, bind=None, root=None):
        self.tus = {}
        self.defs = {}                       # did -> def
        self.by_name = defaultdict(list)     # name -> [did]
        self.records = {}                    # include/ records by key (fold targets and shape tests)
        self.record_dupes = set()
        self.typedefs = {}
        self.bind = bind or {}
        self.bindable = set().union(*self.bind.values()) if self.bind else set()   # files retail calls reach
        self.ambiguous = Counter()           # name -> unattributed call sites
        for rel, flow in sorted(flows, key=lambda x: x[0]):
            normalize_flow(rel, flow, root)
            tu = TU(rel, flow)
            self.tus[rel] = tu
            for key, rec in flow.get('records', {}).items():
                f = rec.get('file', '')
                if not f.startswith('include/'):
                    continue
                old = self.records.get(key)
                if old is None:
                    self.records[key] = rec
                elif old.get('file') != f or old.get('size') != rec.get('size'):
                    self.record_dupes.add(key)
                elif len(rec.get('fields', ())) > len(old.get('fields', ())):
                    self.records[key] = rec
            for name, t in flow.get('typedefs', {}).items():
                self.typedefs.setdefault(name, t)
            for fn in flow.get('functions', ()):
                did = '%s::%s' % (fn['file'], fn['name'])
                if did in self.defs:
                    continue                 # a body in a header seen by several TUs: first TU wins
                d = dict(fn, did=did, tu=rel)
                self.defs[did] = d
                self.by_name[fn['name']].append(did)
        self.T = Types(self.typedefs, self.records)

    # ---------------------------------------------------------------- binding
    def bind_call(self, tu, key, caller_file):
        """did of the definition a call (or address use) of `key` in TU `tu` reaches, or (None, how)."""
        if '@' in key:
            name, f = key.split('@', 1)
            did = '%s::%s' % (norm_file(tu.rel, f)[0], name)
            return (did, 'static') if did in self.defs else (None, 'missing')
        cands = self.by_name.get(key, [])
        if not cands:
            return None, 'no_definition'
        same = [d for d in cands if self.defs[d]['tu'] == tu.rel or self.defs[d]['file'] == caller_file]
        if len(same) == 1:
            return same[0], 'same_tu'
        glob = [d for d in cands if not self.defs[d].get('static')]
        bound = self.bind.get(caller_file, set()) | self.bind.get(tu.rel, set())
        if len(glob) == 1:
            # The only C definition of the name; when the retail binding of the caller never reaches its file
            # the call lands on another copy (a bank twin compiled from another source): same name, same text.
            f = self.defs[glob[0]]['file']
            return glob[0], ('unique_other_copy' if bound and f in self.bindable and f not in bound else 'unique')
        hit = [d for d in glob if self.defs[d]['file'] in bound]
        if len(hit) == 1:
            return hit[0], 'call_bind'

        def common(d):
            a, b = self.defs[d]['file'].split('/'), caller_file.split('/')
            n = 0
            while n < min(len(a), len(b)) and a[n] == b[n]:
                n += 1
            return n
        pool = hit or glob
        if pool:
            best = max(common(d) for d in pool)
            top = [d for d in pool if common(d) == best]
            if len(top) == 1 and best >= 3:
                return top[0], 'path_prefix'
        return None, 'ambiguous'

    # ---------------------------------------------------------------- evidence
    def type_class(self, tu, spelled):
        """('rec', key, display) | ('view', key, display) | ('weak', None, display)."""
        T = tu.T
        r = T.resolve(spelled)
        disp = clean(spelled)
        if r == 'fnptr':
            return 'weak', None, disp
        key = T.pointee_record(spelled)
        if key is None:
            return 'weak', None, disp
        rec = tu.flow.get('records', {}).get(key) or self.records.get(key) or {}
        kind = record_kind(key, rec.get('file', ''), bare_name(spelled))
        name = bare_name(spelled) if not key.startswith('@') else (bare_name(spelled) or key)
        if kind == 'named' and rec.get('file', '').startswith('include/'):
            return 'rec', key, name
        return 'view', key, name

    def resolve_value(self, tu, fn, src, st, off, depth=0, seen=None):
        """Evidence for a value: dict(cat=rec|view|weak|unknown|param|null, key, label, how)."""
        cat, key, label = self.type_class(tu, st) if st else ('weak', None, '?')
        if off:
            if cat == 'rec':
                nested = self.member_record_at(key, off)
                if nested:
                    return dict(cat='rec', key=nested, label=nested, how='interior')
                if key == NODE_HEADER and off == NODE_HEADER_SIZE:
                    return dict(cat='unknown', key=None, label='NODE_BODY(%s)' % label, how='node_body')
            return dict(cat='unknown', key=None, label='%s%+#x' % (label, off), how='interior')
        if cat == 'rec':
            return dict(cat='rec', key=key, label=label, how='static')
        if src and src.startswith('L:') and depth < 6:
            seen = set() if seen is None else seen
            if src in seen:
                return dict(cat='unknown', key=None, label=label, how='local_cycle')
            seen.add(src)
            got = []
            for e in tu.assigns.get((fn, src), ()):
                if e.get('null'):
                    continue
                if not e.get('src'):
                    got.append(dict(cat='unknown', key=None, label=e.get('st') or '?', how='local_source'))
                    continue
                got.append(self.resolve_value(tu, fn, e['src'], e.get('st'), e.get('off', 0), depth + 1, seen))
            recs = {g['key'] for g in got if g['cat'] == 'rec'}
            if got and len(recs) == 1 and all(g['cat'] == 'rec' for g in got):
                g = dict(got[0])
                g['how'] = 'local'
                return g
            params = {(g['cat'], g.get('param')) for g in got}
            if got and len(params) == 1 and got[0]['cat'] == 'param':
                return dict(got[0])
            if got and len(recs) > 1:
                return dict(cat='unknown', key=None, label='local:' + '|'.join(sorted(recs)), how='local_multi')
        if param_node(src) and param_node(src)[0] == fn:
            return dict(cat='param', key=None, label=label, how='param', param=(tu.rel, src))
        return dict(cat=cat, key=key, label=label, how='static')

    def member_record_at(self, key, off):
        rec = self.records.get(key)
        if not rec:
            return None
        for name, foff, ftype, bits in rec.get('fields', ()):
            if foff == off and name and not bits:
                r = self.T.resolve(ftype)
                if r.startswith('rec:') and not r.endswith('*') and '[' not in r:
                    k = r[4:]
                    if record_kind(k, self.records.get(k, {}).get('file', '')) == 'named':
                        return k
        return None

    def collect(self):
        """{(did, i): [evidence]} plus per-def accesses and slot notes."""
        ev = defaultdict(list)
        slot_notes = defaultdict(list)
        installer_params = self.installer_params()
        for rel, tu in self.tus.items():
            for e in tu.flow.get('edges', ()):
                if e['k'] == 'arg' and param_node(e['dst']):
                    callee_key, idx = param_node(e['dst'])
                    src = e.get('src') or ''
                    if src.startswith('FN:'):
                        continue                 # address passed as an argument: an install, below
                    did, how = self.bind_call(tu, callee_key, e['file'])
                    if did is None:
                        if how == 'ambiguous':
                            self.ambiguous[callee_key] += 1
                        continue
                    nparams = len(self.defs[did]['params'])
                    site = '%s:%s' % (e['file'], e['line'])
                    if int(idx) >= nparams:
                        continue
                    if e.get('null'):
                        item = dict(cat='null', key=None, label='0', how='null')
                    else:
                        item = self.resolve_value(tu, e['fn'], src, e.get('st'), e.get('off', 0))
                    item.update(kind='call', site=site, caller=e['fn'], bind=how)
                    ev[(did, int(idx))].append(item)
            for e in tu.flow.get('edges', ()):
                src = e.get('src') or ''
                if not src.startswith('FN:'):
                    continue
                did, how = self.bind_call(tu, src[3:], e['file'])
                if did is None:
                    continue
                for slot in self.slots_of(tu, e, installer_params):
                    self.add_install(ev, slot_notes, did, slot, '%s:%s' % (e['file'], e['line']), e['fn'])
        return ev, slot_notes

    def installer_params(self):
        """(callee_key, i) pairs whose parameter some function stores into an update slot."""
        out = set()
        for rel, tu in self.tus.items():
            for e in tu.flow.get('edges', ()):
                if e['k'] not in ('assign', 'init') or not param_node(e.get('src')):
                    continue
                if self.update_slot(tu, e['dst'], e.get('dt')):
                    out.add(param_node(e['src']))
        return out

    def update_slot(self, tu, dst, dt):
        """'node_update' / 'slot_0x10' when dst is a node header update slot, else None."""
        if not dst.startswith('F:'):
            return None
        rec, _, member = dst[2:].rpartition('.')
        if member == 'update_callback':
            return 'node_update'
        fields = (tu.flow.get('records', {}).get(rec) or self.records.get(rec) or {}).get('fields', ())
        off = next((f[1] for f in fields if f[0] == member), None)
        if off != 0x10:
            return None
        if rec == NODE_HEADER:
            return 'node_update'
        if UPDATE_SLOT_NAMES.match(member) and record_kind(rec, (tu.flow.get('records', {}).get(rec) or {}).get('file', '')) != 'named':
            params, proto = split_params(dt or '')
            if not (proto and params):
                return 'slot_0x10'
        return None

    def slots_of(self, tu, e, installer_params, depth=0):
        """Where an FN: value lands: [(kind, detail, slot params or None)]."""
        out = []
        dst, dt = e['dst'], e.get('dt') or ''
        fnptr_params, proto = split_params(dt) if FNPTR.search(clean(dt)) or tu.T.resolve(dt) == 'fnptr' else ([], False)
        if FNPTR.search(clean(dt)) is None and dt in tu.T.typedefs:
            fnptr_params, proto = split_params(tu.T.typedefs[dt])
        if e['k'] == 'arg' and param_node(dst):
            key, i = param_node(dst)
            name = key.split('@')[0]
            if (name, int(i)) in DRAW_REGISTRARS:
                out.append(('dispatch', 'register_node', None))
            elif (key, int(i)) in installer_params:
                out.append(('dispatch', 'via %s#%s' % (name, i), None))
            elif proto and fnptr_params:
                out.append(('slot', 'arg %s#%s' % (name, i), fnptr_params))
            return out
        kind = self.update_slot(tu, dst, dt)
        if kind:
            out.append(('dispatch', kind + ' ' + dst[2:], None))
            if proto and fnptr_params:
                out.append(('slotnote', dst[2:], fnptr_params))
            return out
        if proto and fnptr_params:
            out.append(('slot', dst, fnptr_params))
            return out
        if dst.startswith('L:') and depth < 2:
            for e2 in tu.by_src.get((e['fn'], dst), ()):
                out.extend(self.slots_of(tu, e2, installer_params, depth + 1))
        return out

    def add_install(self, ev, notes, did, slot, site, creator):
        kind, detail, params = slot
        d = self.defs[did]
        n = len(d['params'])
        if kind == 'dispatch':
            for i in range(n):
                if i == 0:
                    item = dict(cat='unknown', key=None, label='body', how='dispatch_body')
                elif i in DISPATCH_PARAMS:
                    k = DISPATCH_PARAMS[i]
                    item = dict(cat='rec', key=k, label=k, how='dispatch')
                else:
                    item = dict(cat='unknown', key=None, label='not passed', how='dispatch_no_arg')
                item.update(kind='dispatch', site=site, caller=creator, bind=detail)
                ev[(did, i)].append(item)
            return
        if kind in ('slot', 'slotnote'):
            for i, pt in enumerate(params[:n]):
                if kind == 'slot':
                    # A slot declaration names a record only when it is typed with one; `u8 *` / view slots
                    # say nothing about identity and are kept as mismatch notes only.
                    tu = self.tus[d['tu']]
                    cat, key, label = self.type_class(tu, pt)
                    if cat == 'rec':
                        ev[(did, i)].append(dict(cat=cat, key=key, label=label, how='slot', kind='slot',
                                                 site=site, caller=creator, bind=detail))
                if clean(pt) != clean(d['params'][i]['type']) and \
                        self.T.resolve(pt) != self.T.resolve(d['params'][i]['type']):
                    notes[(did, i)].append('%s %s: slot %s' % (site, detail, disp(pt)))

    # ---------------------------------------------------------------- accesses
    def accesses(self, did, i):
        """[(off, width, sign, member, line)], header accesses, escapes for parameter i of did."""
        d = self.defs[did]
        tu = self.tus[d['tu']]
        fn = d['key']
        start = 'P:%s#%d' % (fn, i)
        alias = {start: 0}
        changed = True
        while changed:
            changed = False
            for dst, edges in tu.fn_assigns.get(fn, {}).items():
                if not dst.startswith('L:') or dst in alias:
                    continue
                offs = set()
                ok = True
                for e in edges:
                    if e.get('src') in alias and not e.get('root'):
                        offs.add(alias[e['src']] + e.get('off', 0))
                    else:
                        ok = False
                        break
                if ok and len(offs) == 1:
                    alias[dst] = offs.pop()
                    changed = True
        acc, header, escapes = [], [], []
        T = tu.T
        recs = tu.flow.get('records', {})
        for node, delta in alias.items():
            for u in tu.uses.get((fn, node), ()):
                ctx = u['ctx']
                if ctx == 'macc':
                    off, t = u['off'] + delta, u.get('mtype', '')
                    member = u.get('member', '')
                elif ctx == 'member':
                    rk = T.pointee_record(u.get('cast', ''))
                    fields = (recs.get(rk) or {}).get('fields', ())
                    moff = next((f[1] for f in fields if f[0] == u.get('member')), None)
                    if moff is None:
                        continue
                    off, t = u['off'] + delta + moff, u.get('mtype', '')
                    member = '(%s)%s' % (bare_name(u.get('cast', '')), u.get('member'))
                elif ctx == 'raw':
                    off, t = u['off'] + delta, u.get('wtype', '')
                    member = '*(%s)' % clean(u.get('cast', ''))
                else:
                    continue
                item = (off, T.size(t), T.sign(t), member, u.get('line'))
                (header if off < 0 else acc).append(item)
            for e in tu.by_src.get((fn, node), ()):
                if e['k'] == 'arg':
                    pn = param_node(e['dst'])
                    escapes.append('%s#%s' % (pn[0].split('@')[0], pn[1]) if pn else e['dst'])
        return acc, header, escapes

    def declared_members(self, tu, key):
        rec = tu.flow.get('records', {}).get(key) or {}
        out = []
        for name, off, ftype, bits in rec.get('fields', ()):
            if not name or bits or re.match(r'^(?:pad|_pad|filler)', name):
                continue
            out.append((off, tu.T.size(ftype), tu.T.sign(ftype), name + ' (declared)', None))
        return out


# --------------------------------------------------------------------------- classification

def dedupe(accesses):
    seen = {}
    for a in accesses:
        k = (a[0], a[1], a[2])
        if k not in seen:
            seen[k] = a
    return sorted(seen.values(), key=lambda a: (a[0], a[1] or 0, a[2]))


def resolve_params(model, ev):
    """Replace 'param' evidence (the caller's own weakly typed parameter) by that parameter's consensus."""
    memo = {}

    def consensus(did, i, stack):
        if (did, i) in memo:
            return memo[(did, i)]
        if (did, i) in stack or len(stack) > 6:
            return None
        stack = stack | {(did, i)}
        items = ev.get((did, i), [])
        keys = set()
        for it in items:
            if it['cat'] == 'null':
                continue
            if it['cat'] == 'param':
                got = consensus_of_param(it, stack)
                if got is None:
                    memo[(did, i)] = None
                    return None
                keys.add(got)
            elif it['cat'] == 'rec':
                keys.add(it['key'])
            else:
                memo[(did, i)] = None
                return None
        result = keys.pop() if len(keys) == 1 else None
        memo[(did, i)] = result
        return result

    def consensus_of_param(it, stack):
        rel, node = it['param']
        key, idx = param_node(node)
        name, _, f = key.partition('@')
        tu = model.tus[rel]
        fn = next((x for x in tu.flow.get('functions', ()) if x['key'] == key), None)
        if fn is None:
            return None
        did = '%s::%s' % (fn['file'], fn['name'])
        return consensus(did, int(idx), stack)

    for k, items in ev.items():
        for it in items:
            if it['cat'] == 'param':
                got = consensus_of_param(it, frozenset())
                rel, node = it['param']
                via = node[2:].split('@')[0]
                if got:
                    it.update(cat='rec', key=got, label=got, how='via ' + via)
                else:
                    it.update(cat='unknown', key=None, how='via %s (unresolved)' % via)
                it.pop('param', None)


def candidate_kind(model, d, i):
    """Parameter kind when the parameter is in scope, else None."""
    p = d['params'][i]
    tu = model.tus[d['tu']]
    t = p['type']
    r = tu.T.resolve(t)
    if not r.endswith('*') or r.endswith('**'):
        return None, None
    pointee = r[:-1]
    if pointee == 'void':
        return 'void', None
    if pointee in ('char', 'signed char', 'unsigned char'):
        return 'byte', None
    if pointee.startswith('rec:'):
        key = pointee[4:]
        rec = tu.flow.get('records', {}).get(key) or model.records.get(key) or {}
        return record_kind(key, rec.get('file', ''), bare_name(t)), key
    return None, None


def classify(model, ev, slot_notes):
    rows = []
    for did, d in model.defs.items():
        tu = model.tus[d['tu']]
        for i, p in enumerate(d['params']):
            kind, key = candidate_kind(model, d, i)
            if kind is None:
                continue
            items = ev.get((did, i), [])
            real = [it for it in items if it['cat'] != 'null']
            recs = Counter(it['key'] for it in real if it['cat'] == 'rec')
            if kind == 'named' or kind == 'not_target' and not recs:
                # a named record parameter is listed only when its evidence names another record
                if not any(k != key for k in recs):
                    continue
            if kind == 'named' and set(recs) == {key}:
                continue
            unknown = [it for it in real if it['cat'] != 'rec']
            acc, header, escapes = model.accesses(did, i)
            declared_only = False
            if not acc and key is not None and kind in ('generated', 'file_local', 'anonymous', 'view_named'):
                acc = model.declared_members(tu, key)
                declared_only = bool(acc)
            acc = dedupe(acc)
            proposed = None
            reason = []
            verdict = '-'
            sm = None
            if len(recs) == 1:
                proposed = next(iter(recs))
                sm = slice_match(acc, proposed, model.records, model.T)
                verdict = sm['verdict']
            if not real:
                cls = 'C'
                reason.append('no_evidence')
            elif len(recs) > 1:
                cls = 'C'
                reason.append('conflicting_records')
            elif not recs:
                cls = 'C'
                reason.append('no_record_evidence')
            elif proposed == key:
                cls = 'C'
                reason.append('already_typed')
            elif kind in ('named', 'not_target') and \
                    not model.records.get(proposed, {}).get('file', '').startswith('include/shared/'):
                # the declaration already names a record; a caller holding a module-local named record is
                # more likely the narrower view of it than its identity
                cls = 'C'
                reason.append('callers_hold_non_shared_record')
            elif kind == 'named' and key in SHARED_PREFERENCE and proposed not in SHARED_PREFERENCE:
                # a canonical record is declared and callers hold a narrower shared view of it
                cls = 'C'
                reason.append('callers_hold_narrower_record')
            elif verdict == 'conflict':
                cls = 'C'
                reason.append('slice_conflict')
            elif not unknown and verdict == 'full' and not declared_only and \
                    not (kind == 'named' and key in SHARED_PREFERENCE):
                cls = 'A'
            else:
                cls = 'B'
                if unknown:
                    reason.append('unknown_evidence')
                if verdict == 'partial':
                    reason.append('partial_slice')
                if verdict == 'unknown':
                    reason.append('no_fields_observed')
                if declared_only:
                    reason.append('declared_fields_only')
                if kind == 'named' and key in SHARED_PREFERENCE:
                    reason.append('canonical_record_swap')
            shape, near = [], None
            if len(acc) >= 2:
                lo = min(a[0] for a in acc)
                end = max(a[0] + (a[1] or 0) for a in acc)
                for rk in shared_targets(model):
                    if rk == proposed or lo < 0 or (model.records[rk].get('size') or 0) < end:
                        continue
                    s = slice_match(acc, rk, model.records, model.T)
                    if s['verdict'] == 'full':
                        shape.append(rk)
                    elif s['verdict'] == 'conflict' and rk in SHARED_PREFERENCE:
                        # near fit: one or two accesses disagree with a declared width (R16: settle the field)
                        hit, bad = len(s['fields']), len(s['conflicts'])
                        if hit >= 3 and bad <= 2 and hit >= 3 * bad and (near is None or hit > near[1]):
                            near = (rk, hit, len(acc), s['conflicts'])
                shape = sorted(shape, key=lambda k: (k not in SHARED_PREFERENCE,
                                                     SHARED_PREFERENCE.index(k) if k in SHARED_PREFERENCE else 0,
                                                     model.records[k].get('size', 0), k))
            if cls in ('A', 'B') and kind == 'named' and \
                    (model.records.get(key) or {}).get('file', '').startswith('include/shared/'):
                reason.append('shared_record_swap')
            if cls == 'C' and shape and 'slice_conflict' in reason:
                reason.append('shape_only_conflict')
            if cls == 'C':
                proposed_out = ''
            else:
                proposed_out = proposed + ' *'
            rows.append(dict(
                cls=cls, function=d['name'], file=d['file'], line=d['line'], param=i, name=p.get('name', ''),
                declared=disp(p['type']), kind=kind, items=items,
                n_evidence=len(real), unknown=len(unknown), proposed=proposed_out, record=proposed or '',
                verdict=verdict, sm=sm, accesses=acc, header=header, escapes=escapes, shape=shape,
                reason=reason, slot_notes=slot_notes.get((did, i), []), declared_only=declared_only,
                near=near,
                kinds=Counter(it['kind'] for it in real)))
    order = {'A': 0, 'B': 1, 'C': 2}
    rows.sort(key=lambda r: (order[r['cls']], -r['n_evidence'], -len(r['accesses']), r['unknown'],
                             r['file'], r['function'], r['param']))
    return rows


def shared_targets(model):
    """Named records of include/shared that a view may be folded into (shape tests only)."""
    if getattr(model, '_targets', None) is None:
        model._targets = sorted(k for k, r in model.records.items()
                                if r.get('file', '').startswith('include/shared/') and r.get('size')
                                and record_kind(k, r.get('file', '')) == 'named')
    return model._targets


# --------------------------------------------------------------------------- output

def fmt_acc(a):
    sign = a[2]
    return '+0x%X:%s%s' % (a[0], a[1] if a[1] is not None else '?', sign)


def near_text(near):
    if not near:
        return ''
    rk, hit, n, conflicts = near
    return '%s (%d/%d; %s)' % (rk, hit, n, '; '.join('%s %s' % (fmt_acc(a), why) for a, why in conflicts))


def evidence_kinds(items):
    """'call', 'node_update', 'slot_0x10', 'register_node', 'via_installer', 'slot' joined with '+'."""
    kinds = set()
    for it in items:
        if it['cat'] == 'null':
            continue
        if it['kind'] != 'dispatch':
            kinds.add(it['kind'])
            continue
        b = it.get('bind', '')
        kinds.add('slot_0x10' if b.startswith('slot_0x10') else 'node_update' if b.startswith('node_update')
                  else 'register_node' if b == 'register_node' else 'via_installer')
    return '+'.join(sorted(kinds))


def evidence_text(items):
    c = Counter()
    for it in items:
        if it['cat'] == 'null':
            continue
        label = it['label'] if it['cat'] == 'rec' else '%s(%s)' % (it['label'], it['cat'] if it['cat'] != 'unknown' else it['how'])
        c[(label, it['kind'])] += 1
    return '; '.join('%s x%d %s' % (lab, n, kind) for (lab, kind), n in c.most_common())


COLUMNS = ['rank', 'class', 'function', 'site', 'param', 'param_name', 'declared_type', 'param_kind',
           'caller_types', 'evidence', 'unknown', 'unknown_detail', 'proposed_type', 'slice_vs_proposed',
           'sign_mismatch', 'slice_conflicts', 'accessed_fields', 'header_accesses', 'shape_only_shared',
           'shape_near_shared', 'reason', 'example_sites', 'slot_mismatch', 'forwarded_to']


def tsv_rows(rows):
    for n, r in enumerate(rows, 1):
        sm = r['sm'] or {}
        unk = Counter(it['how'] for it in r['items'] if it['cat'] not in ('rec', 'null'))
        sites = []
        for it in r['items']:
            s = '%s(%s)' % (it['site'], it['kind'])
            if s not in sites:
                sites.append(s)
        yield [n, r['cls'], r['function'], '%s:%s' % (r['file'], r['line']), r['param'], r['name'],
               r['declared'], r['kind'], evidence_text(r['items']), r['n_evidence'], r['unknown'],
               ', '.join('%s x%d' % kv for kv in unk.most_common()), r['proposed'],
               r['verdict'] + (' (%d/%d fields)' % (len(sm.get('fields', ())), len(r['accesses'])) if sm else ''),
               '; '.join('%s=%s(%s)' % (fmt_acc(a), path, s) for a, path, s in sm.get('sign', ())),
               '; '.join('%s %s' % (fmt_acc(a), why) for a, why in sm.get('conflicts', ())[:4]),
               ' '.join(fmt_acc(a) for a in r['accesses'][:40]) + (' (declared)' if r['declared_only'] else ''),
               len(r['header']), ','.join(r['shape'][:5]), near_text(r['near']), ','.join(r['reason']),
               ' '.join(sites[:4]), '; '.join(r['slot_notes'][:3]), ','.join(sorted(set(r['escapes']))[:5])]


def write_outputs(rows, out, info, model):
    out.mkdir(parents=True, exist_ok=True)
    with (out / 'caller_types.tsv').open('w', newline='') as fh:
        w = csv.writer(fh, delimiter='\t', lineterminator='\n')
        w.writerow(COLUMNS)
        w.writerows(tsv_rows(rows))
    with (out / 'evidence.jsonl').open('w') as fh:
        for r in rows:
            fh.write(json.dumps({'function': r['function'], 'file': r['file'], 'param': r['param'],
                                 'class': r['cls'], 'items': r['items'],
                                 'accesses': r['accesses'], 'slice': r['sm']}, default=list) + '\n')
    (out / 'summary.md').write_text(summary(rows, info, model))


def summary(rows, info, model):
    cls = Counter(r['cls'] for r in rows)
    by_kind = defaultdict(Counter)
    for r in rows:
        by_kind[r['kind']][r['cls']] += 1
    targets = Counter(r['record'] for r in rows if r['cls'] == 'A')
    lines = ['# Caller-type worklist', '',
             'Rows: %d (A %d, B %d, C %d).  Definitions scanned: %d; TUs: %d.' % (
                 len(rows), cls['A'], cls['B'], cls['C'], len(model.defs), len(model.tus)), '',
             'Input: %s' % json.dumps(info, default=str)[:600], '',
             '## Classes by parameter kind', '', '| kind | A | B | C |', '|---|---|---|---|']
    for k in sorted(by_kind):
        lines.append('| %s | %d | %d | %d |' % (k, by_kind[k]['A'], by_kind[k]['B'], by_kind[k]['C']))
    ek = Counter(evidence_kinds(r['items']) for r in rows if r['cls'] == 'A')
    lines += ['', '## Class A by evidence kind', '',
              'call = direct calls; node_update = ObjectNodeHeader.update_callback (or a field named so);',
              'slot_0x10 = a +0x10 unk_10/callback slot of a generated view (weakest dispatch heuristic);',
              'register_node = draw registration; via_installer = passed to a parameter some function stores in',
              'an update slot; slot = a typed function-pointer slot or table naming a record.', '']
    lines += ['- %s: %d' % kv for kv in ek.most_common()]
    lines += ['', '## Class A targets', '']
    lines += ['- %s: %d' % kv for kv in targets.most_common()]
    reasons = Counter(x for r in rows for x in r['reason'])
    lines += ['', '## Reasons (B and C)', ''] + ['- %s: %d' % kv for kv in reasons.most_common()]
    swaps = Counter('%s -> %s' % (r['declared'], r['proposed']) for r in rows if 'shared_record_swap' in r['reason'])
    lines += ['', '## Swaps of one include/shared record for another (class A and B, %d rows)' % sum(swaps.values()), '',
              'The declaration already names a shared record and every caller passes another one: a claim that',
              'the declared record duplicates (part of) the passed one.  Review as a record consolidation.', '']
    lines += ['- %s: %d' % kv for kv in swaps.most_common(20)]
    lines += ['', '## Top class A rows', '']
    for r in [r for r in rows if r['cls'] == 'A'][:40]:
        lines.append('- `%s` %s:%s arg%d `%s` -> `%s` (%s; fields %s)' % (
            r['function'], r['file'], r['line'], r['param'], r['declared'], r['proposed'],
            evidence_text(r['items']), ' '.join(fmt_acc(a) for a in r['accesses'][:8])))
    noev = [r for r in rows if r['cls'] == 'C' and 'no_evidence' in r['reason'] and r['shape']]
    lines += ['', '## No visible caller, but the view is a full slice of a shared record (%d)' % len(noev), '',
              'These are reached only through data tables, retail-address slots or assembly (no C reference), so',
              'record identity is unproven (R3); the slice is a lead for creator or runtime evidence, not a fold.', '']
    for r in noev[:60]:
        lines.append('- `%s` %s:%s arg%d `%s` fits %s (%s)' % (
            r['function'], r['file'], r['line'], r['param'], r['declared'], ', '.join(r['shape'][:3]),
            ' '.join(fmt_acc(a) for a in r['accesses'][:8])))
    nearrows = [r for r in rows if r['cls'] == 'C' and 'no_evidence' in r['reason'] and not r['shape'] and r['near']]
    lines += ['', '## No visible caller, near fit (one or two accesses disagree with a declared field width) (%d)'
              % len(nearrows), '', 'The shared field may need settling first (R16, R17) before the view folds.', '']
    for r in nearrows[:40]:
        lines.append('- `%s` %s:%s arg%d `%s`: %s' % (r['function'], r['file'], r['line'], r['param'],
                                                      r['declared'], near_text(r['near'])))
    agreed = [r for r in rows if 'slice_conflict' in r['reason']]
    lines += ['', '## Callers agree on a record but an access conflicts with it (%d)' % len(agreed), '',
              'Either the view is not that object, or the record declares a field narrower or wider than retail',
              'reads it (settle the shared field first, R16).  Never folded by this tool.', '']
    for r in agreed[:40]:
        lines.append('- `%s` %s:%s arg%d `%s`: callers %s; %s' % (
            r['function'], r['file'], r['line'], r['param'], r['declared'], evidence_text(r['items']),
            '; '.join('%s %s' % (fmt_acc(a), why) for a, why in (r['sm'] or {}).get('conflicts', ())[:3])))
    conflict = [r for r in rows if 'shape_only_conflict' in r['reason']]
    lines += ['', '## Shape fits another record but callers pass a different one (%d; never proposed)' % len(conflict), '']
    for r in conflict[:30]:
        lines.append('- `%s` %s:%s arg%d: callers %s; shape fits %s' % (
            r['function'], r['file'], r['line'], r['param'], evidence_text(r['items']), ', '.join(r['shape'][:3])))
    slots = [r for r in rows if r['slot_notes']]
    lines += ['', '## Typed slots whose parameter type differs from the definition (%d)' % len(slots), '']
    for r in slots[:30]:
        lines.append('- `%s` arg%d `%s`: %s' % (r['function'], r['param'], r['declared'], r['slot_notes'][0]))
    lines += ['', '## Calls not attributed (several definitions share the name)', '',
              'Call sites: %d over %d names; top: %s' % (
                  sum(model.ambiguous.values()), len(model.ambiguous),
                  ', '.join('%s x%d' % kv for kv in model.ambiguous.most_common(10)))]
    return '\n'.join(lines) + '\n'


# --------------------------------------------------------------------------- entry points

def analyze(flows, bind=None, log=None, root=None):
    import time
    t0 = time.monotonic()
    model = Model(flows, bind, root)
    t1 = time.monotonic()
    ev, notes = model.collect()
    resolve_params(model, ev)
    t2 = time.monotonic()
    rows = classify(model, ev, notes)
    if log:
        log('model %.1fs, evidence %.1fs, classify %.1fs' % (t1 - t0, t2 - t1, time.monotonic() - t2))
    return model, rows


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest='cmd', required=True)
    run = sub.add_parser('run')
    run.add_argument('--root', type=Path, default=DEFAULT_ROOT)
    run.add_argument('--codemap', type=Path, help='codemap.db (default <root>/build/codemap.db)')
    run.add_argument('--out', type=Path, required=True)
    run.add_argument('--workers', type=int, default=4)
    run.add_argument('--no-reextract', action='store_true')
    run.add_argument('--scope', nargs='*', help='only TUs under these prefixes (callers outside are missed)')
    fx = sub.add_parser('fixture')
    fx.add_argument('--root', type=Path, required=True)
    fx.add_argument('--out', type=Path, required=True)
    show = sub.add_parser('show')
    show.add_argument('--out', type=Path, required=True)
    show.add_argument('function')
    a = ap.parse_args(argv)
    if a.cmd == 'show':
        with (a.out / 'caller_types.tsv').open() as fh:
            r = csv.reader(fh, delimiter='\t')
            head = next(r)
            for row in r:
                if row[2] == a.function:
                    print('\n'.join('%-18s %s' % kv for kv in zip(head, row)))
                    print()
        return 0
    root = a.root.resolve()
    if a.cmd == 'fixture':
        tus = sorted(str(p.relative_to(root)) for p in (root / 'src').rglob('*.c'))
        flows, errors = extract_flows(root, tus)
        bind, info = {}, {'fixture_tus': len(tus), 'extract_errors': errors}
    else:
        db = a.codemap or root / 'build/codemap.db'
        flows, bind, info = flows_from_codemap(db, root, not a.no_reextract, a.workers,
                                               log=lambda m: print(m, file=sys.stderr), scope=a.scope)
        if a.scope:
            info['scope'] = a.scope
    model, rows = analyze(flows, bind, log=lambda m: print(m, file=sys.stderr), root=root)
    info['shared_targets'] = len(shared_targets(model))
    write_outputs(rows, a.out, info, model)
    c = Counter(r['cls'] for r in rows)
    print('rows=%d A=%d B=%d C=%d -> %s' % (len(rows), c['A'], c['B'], c['C'], a.out))
    return 0


if __name__ == '__main__':
    sys.exit(main())
