#!/usr/bin/env python3
"""Object-kind identity census: which callbacks receive the same object body as arg0, and what one body type per
kind would absorb (generated S_<addr> views, casts).

    object_kinds.py extract --out DIR [--scope PREFIX ...] [--workers 6]     clang facts per function (read-only)
    object_kinds.py report  --out DIR [--hold PREFIX ...]          kinds.json, kinds.tsv, draw_groups.tsv, installs.json
    object_kinds.py family  --out DIR --kind K --type T --header H [--view-scope PREFIX ...]
                                                                             layout_swap family file for one kind

Object system (engine/node, shared/object_node.h): every object is a 0x20-byte ObjectNodeHeader followed by its
body.  run_active_node_callbacks calls header->update_callback(header + 0x20, header->position, header->sprite)
and dispatch_registered_draw_callbacks calls a registered draw callback the same way for the head of each draw
chain.  So arg0 of an update callback is the body of every object that callback is ever installed on.

`extract` parses each registered physical TU with clang (tools/typing/field_census.py front end: mipsel layouts,
JSON AST, file/line replay) and walks each function in source order.  Unlike field_census's flow-insensitive
union-find, pointer locals are *rebound* at each assignment (the binding in force at a statement is the last one
in source order), so `object = allocate_list_node(...)` used three times in one function stays three objects.
A value is (root, delta): root is a parameter (p:F:i), a call result (c:<id>:<callee>), a global (g:name), a
function symbol (fn:name) or the pointee loaded from root+off (*(root+off)).  Per function it records member/raw
access sites, stores (lhs address and rhs value), calls (resolved arguments), casts to record pointers (target,
operand value and operand type) and returned values.

`report` links functions into object kinds:
  header roots   allocator results (allocate_list_node, allocate_flagged_object_node, initialize_scene_object_in_buffer,
                 and wrappers that return one of these at a fixed delta, found to a fixpoint), values typed
                 ObjectNodeHeader * (or a record whose first member is one), and arg0 of a known callback (-0x20);
  installs       a store of a function symbol to header+0x10 (any spelling: ->update_callback, ->header.update_callback,
                 ((S *)((u8 *)body - 0x10))->unk_00, [-1].unk_10), register_node(header, cb) (draw), and callback
                 parameters: a function whose parameter k reaches a header+0x10 store (or register_node) is a creator
                 wrapper and each call passing a function symbol at k installs it on the wrapper's node;
  identity       chain: a callback that installs G on its own body (arg0 - 0x10) makes G the same kind; one creation
                 site installing several update callbacks makes them one kind.  Kinds are a union-find over update
                 callbacks with a refusal: a union whose merged body layouts disagree (same offset, different width,
                 or pointer vs integer) is refused and the callback that bridged them is tagged `shared` (generic
                 finalizers and retire handlers).  Draw callbacks are recorded per kind but never merge kinds (a draw
                 callback walks every object registered under its slot).
  per kind       creators (function, line, allocator, flags), update and draw callbacks, the S_ views that reach the
                 body (member views through arg0, casts of arg0 / creator node + 0x20), a merged body layout
                 (offset -> widths/signs/functions, conflicts), and the casts that fold when arg0 is typed: casts to a
                 generated view (or to any record) whose operand is the body at delta 0, split by operand type.
  readiness      ready = every callback and every creator file is outside --hold prefixes, no layout conflict, and at
                 least one generated view to absorb; evidence = chain/co-install edges and creator count.

Same-named functions: a name defined in several files (dungeon/town copies, per-overlay copies) is keyed
`name@file` when every reference to it can be attributed to one definition (the referring file's own, then the one
in its physical TU, its folder, its area); such copies are separate callbacks and separate kinds.  A name some
reference cannot attribute keeps the bare merged key (summary: duplicate_names_split / _kept_merged).
tools/typing/param_retype.py callbacks accepts `name@file` symbols.

`family` writes a tools/typing/layout_swap.py family file listing the kind's arg0 views, for a new folder-header type.
"""
from __future__ import annotations

import argparse
import collections
from concurrent.futures import ProcessPoolExecutor
import gzip
import json
import os
from pathlib import Path
import re
import sqlite3
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path[:0] = [str(HERE), str(HERE.parent)]
import field_census as C  # noqa: E402

GENERATED = re.compile(r'^S_(?:func_)?[0-9A-Fa-f]{8}(?:_\w+)?$')
HEX_NAME = re.compile(r'^(?:D|func|g)_([0-9A-Fa-f]{8})$')
HEADER = 'ObjectNodeHeader'
HEADER_SIZE = 0x20
CALLBACK_SLOT = 0x10
SEED_ALLOCATORS = {'allocate_list_node': 0, 'allocate_flagged_object_node': 0, 'func_8003FD64': 0,
                   'initialize_scene_object_in_buffer': 0}
DRAW_REGISTRARS = {'register_node': (0, 1), 'register_node_if_unregistered': (0, 1), 'func_8004491C': (0, 1)}


# ------------------------------------------------------------------------------------------------- extraction

def rstr(root):
    return root if isinstance(root, str) else '*(%s%+d)' % (rstr(root[1]), root[2])


class KindFacts(C.FunctionFacts):
    """FunctionFacts with source-order rebinding of pointer locals and extra event records."""

    def __init__(self, types, fn, file, src_text, globals_):
        super().__init__(types, fn, file, src_text, globals_)
        self.env = {}
        self.ev = {'stores': [], 'calls': [], 'sites': [], 'casts': [], 'returns': [], 'params': [], 'typed': []}
        self.local_types = {}
        self.seen_casts = set()
        for p in (x for x in fn.get('inner', []) if x.get('kind') == 'ParmVarDecl'):
            t = C.qtype(p)
            self.ev['params'].append({'name': p.get('name'), 'type': t, 'canon': self.T.resolve(t)})

    # values are resolved through the current bindings of pointer locals
    def resolve(self, v):
        if v is None:
            return None
        node, delta = v
        node, d0 = self.rnode(node)
        return (node, d0 + delta)

    def rnode(self, node, depth=0):
        if isinstance(node, tuple):
            inner, d0 = self.rnode(node[1], depth + 1)
            return ('F', inner, node[2] + d0), 0
        if depth < 20 and node in self.env:
            return self.env[node]
        return node, 0

    def jref(self, v):
        v = self.resolve(v)
        return None if v is None else [rstr(v[0]), v[1]]

    def value(self, e):
        if not e:
            return None
        k = e.get('kind')
        if k == 'DeclRefExpr' and (e.get('referencedDecl') or {}).get('kind') == 'FunctionDecl':
            return ('fn:' + e['referencedDecl']['name'], 0)
        if k == 'ImplicitCastExpr' and e.get('castKind') == 'FunctionToPointerDecay':
            return self.value(e['inner'][0])
        if k == 'UnaryOperator' and e.get('opcode') == '&':
            sub = C.strip(e['inner'][0], casts=False)
            if sub and sub.get('kind') == 'DeclRefExpr' and (sub.get('referencedDecl') or {}).get('kind') == 'FunctionDecl':
                return ('fn:' + sub['referencedDecl']['name'], 0)
        if k == 'CStyleCastExpr' and e.get('id') not in self.seen_casts:
            self.seen_casts.add(e.get('id'))
            t = C.qtype(e)
            rec = self.T.record(t)
            if rec and self.T.pointee(t):
                sub = e['inner'][0]
                ident, strong = self.T.type_identity(rec)
                self.ev['casts'].append({
                    'line': e.get('_l'), 'target': ident, 'name': rec, 'strong': strong,
                    'gen': bool(GENERATED.match(rec)), 'ref': self.jref(super().value(sub)),
                    'opnd': self.T.resolve(C.qtype(C.strip(sub, casts=False)) or C.qtype(sub)),
                    'macro': e.get('_m') is not None})
        if k == 'CallExpr':
            callee = C.strip(e['inner'][0])
            if callee and callee.get('kind') == 'DeclRefExpr' and callee['referencedDecl'].get('kind') == 'FunctionDecl':
                return ('c:%s:%s' % (e.get('id'), callee['referencedDecl']['name']), 0)
            return None
        return super().value(e)

    def site(self, e, rw, const=None):
        n = len(self.sites)
        super().site(e, rw, const)
        for s in self.sites[n:]:
            ref = None
            if s['node'] is not None:
                ref = self.jref((s['node'], s['delta']))
            decl = s['decl'] or ''
            self.ev['sites'].append({'line': s['line'], 'ref': ref, 'w': s['width'], 's': s['sign'], 'rw': rw,
                                     'view': decl, 'field': s['field'], 'spell': s['spell'],
                                     'const': s.get('const')})

    def bind(self, node, val):
        self.env[node] = self.resolve(val) if val is not None else (node, 0)
        ident = self.local_types.get(node)
        if ident:
            r, d = self.env[node]
            self.ev['typed'].append([rstr(r), d, ident])

    def walk(self):
        body = [x for x in self.fn.get('inner', []) if x.get('kind') == 'CompoundStmt']
        stack = [(b, None, 'r') for b in reversed(body)]
        while stack:
            item = stack.pop()
            if item[0] == '__bind__':
                self.bind(item[1], item[2])
                continue
            e, parent, ctx = item
            if not isinstance(e, dict):
                continue
            k = e.get('kind')
            kids = e.get('inner') or []
            child_ctx = ['r'] * len(kids)
            post = []
            if k == 'VarDecl':
                st = e.get('storageClass')
                if st in ('extern', 'static'):
                    gname = e['name'] if st == 'extern' else '%s:%s:%s' % (self.file, self.name, e['name'])
                    self.globals[e['id']] = 'g:' + gname
                else:
                    t = C.qtype(e)
                    r = self.T.resolve(t)
                    if r.endswith('*') or self.T.size(t) == 4:
                        node = 'v:%s:%s' % (e['name'], e['id'])
                        self.locals[e['id']] = ('ptr', node)
                        if self.T.record(t) and self.T.pointee(t):
                            self.local_types[node] = self.T.type_identity(self.T.record(t))[0]
                        val = self.value(kids[0]) if (e.get('init') and kids) else None
                        if val is None and self.T.record(t) and self.T.pointee(t):
                            ident, _ = self.T.type_identity(self.T.record(t))
                            val = ('t:%s:%s' % (ident, node), 0)
                        post.append(('__bind__', node, val))
                    else:
                        node = 'o:%s:%s' % (e['name'], e['id'])
                        self.locals[e['id']] = ('obj', node)
            elif k == 'BinaryOperator' and e.get('opcode') == '=':
                child_ctx = ['w', 'r']
                c = C.int_value(kids[1])
                if c is not None:
                    e['_const'] = c
                rhs = self.value(kids[1])
                lhs = C.strip(kids[0], casts=False)
                if lhs and lhs.get('kind') == 'DeclRefExpr' and (self.var_node(lhs['referencedDecl']) or ('',))[0] == 'ptr':
                    post.append(('__bind__', self.var_node(lhs['referencedDecl'])[1], rhs))
                else:
                    a = self.addr(kids[0])
                    if a is not None:
                        ref = self.jref(a)
                        rv = self.jref(rhs) if rhs is not None else None
                        self.ev['stores'].append({'line': e.get('_l'), 'lhs': ref, 'rhs': rv,
                                                  'text': C.expr_text(kids[0]), 'const': c})
            elif k == 'CompoundAssignOperator':
                child_ctx = ['rw', 'r']
                lhs = C.strip(kids[0], casts=False)
                if lhs and lhs.get('kind') == 'DeclRefExpr' and self.T.pointee(C.qtype(lhs)):
                    v = self.var_node(lhs['referencedDecl'])
                    n = C.int_value(kids[1])
                    if v and v[0] == 'ptr':
                        if n is not None and e.get('opcode') in ('+=', '-='):
                            scale = self.T.size(self.T.pointee(C.qtype(lhs))) or 1
                            cur = self.resolve((v[1], 0))
                            post.append(('__bind__', v[1], (cur[0], cur[1] + (n if e['opcode'] == '+=' else -n) * scale)))
                        else:
                            post.append(('__bind__', v[1], ('w:%s' % v[1], 0)))
            elif k == 'UnaryOperator' and e.get('opcode') in ('++', '--'):
                child_ctx = ['rw']
                lhs = C.strip(kids[0], casts=False)
                if lhs and lhs.get('kind') == 'DeclRefExpr':
                    v = self.var_node(lhs['referencedDecl'])
                    if v and v[0] == 'ptr':
                        post.append(('__bind__', v[1], ('w:%s' % v[1], 0)))
            elif k == 'UnaryOperator' and e.get('opcode') == '&':
                child_ctx = ['addr']
            elif k == 'CallExpr':
                callee = C.strip(kids[0]) if kids else None
                if callee and callee.get('kind') == 'DeclRefExpr' and callee['referencedDecl'].get('kind') == 'FunctionDecl':
                    fname = callee['referencedDecl']['name']
                    args = [self.jref(self.value(a)) for a in kids[1:]]
                    self.ev['calls'].append({'line': e.get('_l'), 'callee': fname, 'res': 'c:%s:%s' % (e.get('id'), fname),
                                             'args': args, 'consts': [C.int_value(a) for a in kids[1:]]})
            elif k == 'ReturnStmt' and kids:
                self.ev['returns'].append(self.jref(self.value(kids[0])))
            elif k == 'ImplicitCastExpr' and e.get('castKind') == 'LValueToRValue':
                child_ctx = ['r']
            elif k == 'MemberExpr' and not e.get('isArrow'):
                child_ctx = ['base']
            elif k == 'ArraySubscriptExpr':
                child_ctx = ['base', 'r']
            elif k in ('ParenExpr',):
                child_ctx = [ctx]
            elif k == 'CStyleCastExpr':
                self.value(e)
            if k in ('MemberExpr', 'UnaryOperator', 'ArraySubscriptExpr') and ctx != 'base':
                is_deref = k != 'UnaryOperator' or e.get('opcode') == '*'
                if is_deref and self.is_leaf(e, parent):
                    rw = ctx if ctx in ('r', 'w', 'rw', 'addr') else 'r'
                    const = parent.get('_const') if (parent and rw == 'w') else None
                    self.site(e, rw, const)
            if k == 'MemberExpr' and e.get('isArrow'):
                child_ctx = ['r']
            if k == 'UnaryOperator' and e.get('opcode') == '*':
                child_ctx = ['r']
            for p_ in reversed(post):
                stack.append(p_)
            for kid, c in reversed(list(zip(kids, child_ctx))):
                stack.append((kid, e, c))


def header_records(layouts):
    """Records that start with an ObjectNodeHeader member (e.g. ItemMenuObjectNode)."""
    out = {HEADER}
    for key, lay in layouts.items():
        for name in lay.get('order', []):
            off, ftype = lay['fields'][name]
            if off == 0 and C.record_key(ftype) == HEADER:
                out.add(key)
            break
    return out


def extract_tu(args):
    root, rel = args
    rc, out, err = C.clang_run(root, rel, ['-Xclang', '-ast-dump=json'])
    if not out.strip():
        return {'tu': rel, 'error': (err.strip().splitlines() or ['no output'])[-1][:300], 'functions': []}
    try:
        tree = json.loads(out)
    except ValueError as exc:
        return {'tu': rel, 'error': 'json: %s' % exc, 'functions': []}
    _, lay_text, _ = C.clang_run(root, rel, ['-Xclang', '-fdump-record-layouts-complete'])
    layouts = C.parse_layouts(lay_text)
    C.annotate(tree)
    typedefs, record_files, globals_, anon = {}, {}, {}, {}
    for d in tree.get('inner', []):
        k = d.get('kind')
        if k == 'TypedefDecl':
            typedefs[d['name']] = C.qtype(d)
            inner = (d.get('inner') or [{}])[0]
            owned = inner.get('ownedTagDecl')
            if owned and not owned.get('name') and owned.get('id') in anon:
                key = anon[owned['id']]
                if key in layouts:
                    layouts.setdefault(d['name'], layouts[key])
                    record_files.setdefault(d['name'], key[1:].split(':')[0])
            elif owned is None:
                # typedef of a named record keeps the record's file; a plain typedef name is its own key
                pass
            record_files.setdefault(d['name'], d.get('_f') or '')
        elif k == 'RecordDecl' and d.get('completeDefinition'):
            key = d.get('name') or None
            if key:
                record_files.setdefault(key, d.get('_f') or '')
            else:
                anon[d['id']] = '@%s:%s:%s' % (d.get('_f'), d.get('_l'), (d.get('loc') or {}).get('col'))
        elif k == 'VarDecl':
            name = d['name']
            if d.get('storageClass') == 'static':
                name = '%s:%s' % (d.get('_f'), name)
            globals_[d['id']] = 'g:' + name
    for key in layouts:
        if key.startswith('@'):
            record_files.setdefault(key, key[1:].split(':')[0])
    types = C.Types(typedefs, layouts, record_files)
    hdr = header_records(layouts)
    texts, funcs = {}, []
    for d in tree.get('inner', []):
        if d.get('kind') != 'FunctionDecl' or not any(x.get('kind') == 'CompoundStmt' for x in d.get('inner', [])):
            continue
        f = d.get('_f') or rel
        if f not in texts:
            try:
                texts[f] = (Path(root) / f).read_text(errors='replace')
            except OSError:
                texts[f] = ''
        ff = KindFacts(types, d, f, texts[f], globals_)
        ff.walk()
        funcs.append(dict(file=f, func=d['name'], tu=rel, line=d.get('_l'), **ff.ev))
    sizes = {}
    for key, lay in layouts.items():
        if 'size' in lay:
            ident, strong = types.type_identity(key)
            sizes[ident] = lay['size']
    hdr_ids = sorted({types.type_identity(k)[0] for k in hdr})
    return {'tu': rel, 'error': None if rc == 0 else (err.strip().splitlines() or [''])[-1][:300],
            'functions': funcs, 'header_types': hdr_ids, 'sizes': sizes}


def cmd_extract(args):
    root = Path(args.root).resolve()
    out = Path(args.out)
    out.mkdir(parents=True, exist_ok=True)
    tus, _ = C.physical_tus(root)
    if args.scope:
        tus = [t for t in tus if t.startswith(tuple(args.scope))]
    seen, errors, nfun = set(), [], 0
    header_types, sizes = set(), {}
    with gzip.open(out / 'facts.jsonl.gz', 'wt') as fh, ProcessPoolExecutor(max_workers=args.workers) as ex:
        for res in ex.map(extract_tu, [(str(root), t) for t in tus], chunksize=4):
            if res.get('error'):
                errors.append((res['tu'], res['error']))
            header_types.update(res.get('header_types', []))
            for k, v in (res.get('sizes') or {}).items():
                sizes.setdefault(k, v)
            for f in res['functions']:
                key = (f['file'], f['func'])
                if key in seen:
                    continue
                seen.add(key)
                nfun += 1
                fh.write(json.dumps(f) + '\n')
    meta = {'tus': len(tus), 'functions': nfun, 'errors': errors, 'header_types': sorted(header_types),
            'scope': args.scope or []}
    (out / 'extract.json').write_text(json.dumps(meta, indent=1) + '\n')
    (out / 'sizes.json').write_text(json.dumps(sizes) + '\n')
    print(json.dumps({'tus': len(tus), 'functions': nfun, 'tu_errors': len(errors)}))
    return 0


# ------------------------------------------------------------------------------------------------- linking

def parse_root(s):
    """'*(p:f:0+16)' -> ('F', 'p:f:0', 16); plain roots unchanged."""
    if s.startswith('*(') and s.endswith(')'):
        body = s[2:-1]
        m = re.match(r'^(.*)([+-]\d+)$', body)
        if m:
            return ('F', parse_root(m.group(1)), int(m.group(2)))
    return s


class Symbols:
    """Name -> function: a defined function, or a data-named address (names.tsv, D_/func_<addr>) that is a function
    in the same area (town / dungeon / ...) as the referring file."""

    def __init__(self, root, defined, resolve=None):
        self.defined = defined
        self.resolve = resolve or (lambda name, file: name)
        self.addr = {}
        names = Path(root) / 'config/names.tsv'
        if names.exists():
            for line in names.read_text(errors='replace').splitlines():
                if line.startswith('#') or not line.strip():
                    continue
                cols = line.split('\t')
                if len(cols) >= 3 and cols[0].startswith('0x'):
                    self.addr.setdefault(cols[2], int(cols[0], 16))
                    self.addr.setdefault(cols[1], int(cols[0], 16))
        self.by_addr = collections.defaultdict(set)
        db = Path(root) / 'build/codemap.db'
        if db.exists():
            con = sqlite3.connect(str(db))
            for name, address in con.execute("select name, address from function where kind='function' and address is not null"):
                try:
                    self.by_addr[int(address, 16)].add(name)
                except (TypeError, ValueError):
                    pass
            con.close()

    def function(self, name, file):
        if name in self.defined:
            return self.resolve(name, file)
        a = self.addr.get(name)
        if a is None:
            m = HEX_NAME.match(name)
            a = int(m.group(1), 16) if m else None
        if a is None:
            return None
        cands = [n for n in self.by_addr.get(a, ()) if n in self.defined]
        if len(cands) > 1:
            area = file.split('/')[1] if file.count('/') > 1 else ''
            same = [n for n in cands if any(f.split('/')[1:2] == [area] for f in self.defined[n])]
            cands = same or cands
        return self.resolve(cands[0], file) if len(cands) == 1 else None


def load_facts(out):
    funcs = []
    with gzip.open(Path(out) / 'facts.jsonl.gz', 'rt') as fh:
        for line in fh:
            funcs.append(json.loads(line))
    return funcs


def root_of(ref):
    return None if ref is None else ref[0]


class Linker:
    def __init__(self, root, out):
        self.funcs = load_facts(out)
        meta = json.loads((Path(out) / 'extract.json').read_text())
        self.header_types = set(meta.get('header_types', []))
        bare = collections.defaultdict(set)
        self.tu_of = {}
        for f in self.funcs:
            bare[f['func']].add(f['file'])
            self.tu_of.setdefault(f['file'], f.get('tu') or f['file'])
        self.dup = {n for n, fs in bare.items() if len(fs) > 1}
        self.dup_all = set(self.dup)
        self.bare = bare
        self.unresolved = collections.Counter()
        self.merged_ambiguous = []
        self.sym = Symbols(root, bare, self.resolve)
        self.qualify_duplicates()
        self.defined = collections.defaultdict(set)
        for f in self.funcs:
            self.defined[f['func']].add(f['file'])
        self.by_name = collections.defaultdict(list)
        for f in self.funcs:
            self.by_name[f['func']].append(f)

    def resolve(self, name, file):
        """Function key for `name` as referenced from `file`.  A name defined in one file is its own key; a name
        defined in several files (same-named copies in different binaries or areas) is keyed `name@file` by the
        definition the referring file sees: its own, the one in its physical TU, the one in its folder, then the
        one in its area.  Anything else is `name@?` (never merged with either copy)."""
        fs = self.bare.get(name)
        if not fs or len(fs) == 1 or '@' in name or name not in self.dup:
            return name
        if file in fs:
            return '%s@%s' % (name, file)
        tu = self.tu_of.get(file, file)
        for pick in ([g for g in fs if self.tu_of.get(g, g) == tu],
                     [g for g in fs if os.path.dirname(g) == os.path.dirname(file)],
                     [g for g in fs if g.split('/')[1:2] == file.split('/')[1:2]]):
            if len(pick) == 1:
                return '%s@%s' % (name, pick[0])
        self.unresolved[name] += 1
        return name + '@?'

    def qualify_duplicates(self):
        """Rewrite every fact so that same-named functions in different files are different functions: own
        parameter roots (p:F:i), call results (c:<id>:F) and callees are keyed through resolve()."""
        if not self.dup:
            return
        # A name some referring file cannot attribute to one copy keeps the old merged key (bare name): splitting
        # it would drop that file's installs.  Only fully attributable copies are separated.
        alt = '|'.join(sorted((re.escape(n) for n in self.dup), key=len, reverse=True))
        any_re = re.compile(r'(?<![\w@])(%s)(?![\w@])' % alt)
        ambiguous = set()
        sym_re = re.compile(r'"(?:fn:|g:(?:[^"]*:)?)([A-Za-z_]\w*)"')
        for f in self.funcs:
            text = json.dumps(f)
            for m in set(any_re.findall(text)):
                if self.resolve(m, f['file']).endswith('@?'):
                    ambiguous.add(m)
            for m in set(sym_re.findall(text)):   # data-named function addresses (D_/func_<addr>, names.tsv)
                r = self.sym.function(m, f['file'])
                if r and r.endswith('@?'):
                    ambiguous.add(r[:-2])
        self.merged_ambiguous = sorted(ambiguous)
        self.dup -= ambiguous
        self.unresolved.clear()
        if not self.dup:
            return
        alt = '|'.join(sorted((re.escape(n) for n in self.dup), key=len, reverse=True))
        own_re = re.compile(r'(?<![\w@])p:(%s):(?=\d)' % alt)
        call_re = re.compile(r'(c:\d+:)(%s)(?![\w@])' % alt)
        for i, f in enumerate(self.funcs):
            file = f['file']
            text = json.dumps(f)
            if not (own_re.search(text) or call_re.search(text) or f['func'] in self.dup):
                continue
            new = dict(f)
            if f['func'] in self.dup:
                new['func'] = self.resolve(f['func'], file)
            for c in new.get('calls', ()):
                if c.get('callee') in self.dup:
                    c['callee'] = self.resolve(c['callee'], file)
            text = json.dumps(new)
            text = own_re.sub(lambda m: 'p:%s:' % (new['func'] if m.group(1) == f['func'] else m.group(1)), text)
            text = call_re.sub(lambda m: m.group(1) + self.resolve(m.group(2), file), text)
            self.funcs[i] = json.loads(text)

    def fsym(self, ref, file):
        """Function a value names (function designator, or a data symbol / &symbol at a function address)."""
        if ref is None or ref[1] != 0:
            return None
        r = ref[0]
        if r.startswith('fn:'):
            return self.sym.function(r[3:], file)
        if r.startswith('g:'):
            return self.sym.function(r[2:].split(':')[-1], file)
        return None

    # --- header roots per function, to a fixpoint over allocator wrappers and known callbacks
    def header_delta(self, f, root, callbacks, allocators):
        """Offset of the ObjectNodeHeader within root's object (root + h = header), or None."""
        if root.startswith('c:'):
            callee = root.split(':', 2)[2]
            if callee in allocators:
                return allocators[callee]
            return None
        if root.startswith('t:'):
            ident = root[2:].rsplit(':v:', 1)[0]
            return 0 if self.is_header_type(ident) else None
        for r, d, ident in f.get('typed', ()):
            if r == root and self.is_header_type(ident):
                return d
        m = re.match(r'^p:(.*):(\d+)$', root)
        if m and m.group(1) == f['func']:
            i = int(m.group(2))
            if i == 0 and f['func'] in callbacks:
                return -HEADER_SIZE
            p = f['params'][i] if i < len(f['params']) else None
            if p and p['canon'].endswith('*'):
                rec = p['canon'][:-1]
                rec = rec[4:] if rec.startswith('rec:') else rec
                if rec == HEADER or any(h.split(':')[-1] == rec for h in self.header_types):
                    return 0
        return None

    def is_header_type(self, ident):
        return ident in self.header_types or ident.split(':')[-1] == HEADER

    def body_seeds(self):
        """Functions whose arg0 is evidently an object body: they store a function symbol at arg0 - 0x10 (their own
        update slot) or access the header flags at arg0 - 2."""
        seeds = set()
        for f in self.funcs:
            own = 'p:%s:0' % f['func']
            for st in f['stores']:
                if st['lhs'] and st['lhs'][0] == own and st['lhs'][1] == CALLBACK_SLOT - HEADER_SIZE \
                        and self.fsym(st['rhs'], f['file']):
                    seeds.add(f['func'])
            for site in f['sites']:
                if site['ref'] and site['ref'][0] == own and site['ref'][1] == -2 and site['w'] == 2:
                    seeds.add(f['func'])
        return seeds

    def run(self):
        allocators = dict(SEED_ALLOCATORS)
        callbacks = self.body_seeds()
        self.seeds = set(callbacks)
        for rnd in range(8):
            installs, carriers = self.scan(callbacks, allocators)
            new_cb = {g for i in installs for g in [i['cb']] if g}
            grew = False
            # wrappers: a function that returns an allocator node at a fixed delta is an allocator
            for f in self.funcs:
                if f['func'] in allocators:
                    continue
                ds = set()
                for r in f['returns']:
                    if r is None:
                        ds.add(None)
                        continue
                    h = self.header_delta(f, r[0], callbacks, allocators)
                    ds.add(None if h is None else h - r[1])
                if len(ds) == 1 and None not in ds:
                    allocators[f['func']] = ds.pop()
                    grew = True
            if new_cb - callbacks:
                callbacks |= new_cb
                grew = True
            if not grew:
                break
        self.allocators, self.callbacks = allocators, callbacks
        self.installs, self.carriers = installs, carriers
        return installs

    def scan(self, callbacks, allocators):
        """Installs: dicts(func, file, line, node (root, header delta) or None, role update/draw, cb, via)."""
        installs = []
        carriers = {}   # (func, param index) -> (role, exported node slot or None)
        for rnd in range(6):
            changed = False
            for f in self.funcs:
                for node, role, val, line, via in self.slots(f, callbacks, allocators):
                    key = self.own_param(f, val)
                    if key is not None and key not in carriers:
                        carriers[key] = (role, self.export(f, node), (f['file'], f['func'], node[0], node[1]))
                        changed = True
                for c in f['calls']:
                    for i, a in enumerate(c['args']):
                        car = carriers.get((c['callee'], i))
                        key = self.own_param(f, a) if car else None
                        if key is None or key in carriers:
                            continue
                        node = self.carried_node(c, car[1])
                        carriers[key] = (car[0], self.export(f, node) if node else None,
                                         car[2] if node is None or self.export(f, node) is None else None)
                        changed = True
            if not changed:
                break
        for f in self.funcs:
            for node, role, val, line, via in self.slots(f, callbacks, allocators):
                g = self.fsym(val, f['file'])
                if g:
                    installs.append({'func': f['func'], 'file': f['file'], 'line': line, 'node': node,
                                     'role': role, 'cb': g, 'via': via})
            for c in f['calls']:
                for i, a in enumerate(c['args']):
                    car = carriers.get((c['callee'], i))
                    g = self.fsym(a, f['file']) if car else None
                    if not g:
                        continue
                    installs.append({'func': f['func'], 'file': f['file'], 'line': c['line'],
                                     'node': self.carried_node(c, car[1]), 'inner': car[2], 'role': car[0], 'cb': g,
                                     'via': 'arg:%s:%d' % (c['callee'], i)})
        return installs, carriers

    @staticmethod
    def own_param(f, val):
        if val is None or val[1] != 0:
            return None
        m = re.match(r'^p:(.*):(\d+)$', val[0])
        if m and m.group(1) == f['func']:
            return (f['func'], int(m.group(2)))
        return None

    @staticmethod
    def export(f, node):
        """A node (root, h) of f as callers see it: ('ret', h') for a returned node, (p:f:j, h) for a node parameter."""
        if node is None:
            return None
        root, h = node
        for r in f['returns']:
            if r is not None and r[0] == root:
                return ('ret', h - r[1])
        m = re.match(r'^p:(.*):(\d+)$', root)
        if m and m.group(1) == f['func']:
            return node
        return None

    @staticmethod
    def carried_node(call, slot):
        """In the caller: the header root a carrier's node corresponds to (the call result for a returned node, the
        argument for a node parameter)."""
        if slot is None:
            return None
        node_root, h = slot
        if node_root == 'ret':
            return (call['res'], h)
        m = re.match(r'^p:(.*):(\d+)$', node_root)
        if m and m.group(1) == call['callee']:
            j = int(m.group(2))
            a = call['args'][j] if j < len(call['args']) else None
            if a is not None and not a[0].startswith('*('):
                return (a[0], a[1] + h)
        return None

    def slots(self, f, callbacks, allocators):
        """(node, role, stored value, line, via) for each callback-slot store / draw registration in f.
        node = (root, header delta): root + delta is the header."""
        out = []
        for s in f['stores']:
            lhs = s['lhs']
            if lhs is None:
                continue
            r = lhs[0]
            if (s.get('text') or '').endswith('update_callback') and not r.startswith('*('):
                out.append(((r, lhs[1] - CALLBACK_SLOT), 'update', s['rhs'], s['line'], 'store'))
                continue
            if r.startswith('*('):
                continue
            h = self.header_delta(f, r, callbacks, allocators)
            if h is None or lhs[1] - h != CALLBACK_SLOT:
                continue
            out.append(((r, h), 'update', s['rhs'], s['line'], 'store'))
        for c in f['calls']:
            reg = DRAW_REGISTRARS.get(c['callee'])
            if not reg or len(c['args']) <= max(reg):
                continue
            node, cb = c['args'][reg[0]], c['args'][reg[1]]
            if node is None or node[0].startswith('*('):
                continue
            # register_node's first parameter is the header itself
            out.append(((node[0], node[1]), 'draw', cb, c['line'], c['callee']))
        return out


# ------------------------------------------------------------------------------------------------- kinds

class UF:
    def __init__(self):
        self.p = {}

    def find(self, x):
        self.p.setdefault(x, x)
        while self.p[x] != x:
            self.p[x] = self.p[self.p[x]]
            x = self.p[x]
        return x

    def union(self, a, b):
        a, b = self.find(a), self.find(b)
        if a != b:
            self.p[b] = a
        return a


def access_key(site):
    return '%s%d' % (site['s'], site['w'] or 0)


def merge_layout(acc):
    """acc: offset -> Counter(access) -> layout rows and conflict list."""
    rows, conflicts = [], []
    spans = []
    for off in sorted(acc):
        kinds = acc[off]
        widths = {int(k[1:]) for k in kinds if k[1:].isdigit()}
        signs = {k[0] for k in kinds}
        ptr = 'p' in signs
        intish = bool(signs & {'s', 'u'})
        conflict = []
        if len({w for w in widths if w <= 4}) > 1:
            conflict.append('width')
        if ptr and intish:
            conflict.append('pointer_vs_integer')
        rows.append({'off': off, 'access': dict(kinds), 'conflict': conflict})
        if conflict:
            conflicts.append((off, conflict))
        spans.append((off, max(widths or {1})))
    for (a, wa), (b, wb) in zip(spans, spans[1:]):
        if a + wa > b and wa <= 4:
            conflicts.append((a, ['overlap:%#x' % b]))
    return rows, conflicts


def cmd_report(args):
    root = Path(args.root).resolve()
    out = Path(args.out)
    L = Linker(root, out)
    installs = L.run()
    by_func = collections.defaultdict(list)
    by_def = {}
    for f in L.funcs:
        by_func[f['func']].append(f)
        by_def[(f['file'], f['func'])] = f
    hold = tuple(args.hold or ())

    # object identity: creation node (function, root, header delta) -> update callbacks / draw callbacks
    nodes = collections.defaultdict(lambda: {'update': set(), 'draw': set(), 'lines': set(), 'file': None})
    chains = []
    via_wrapper = collections.defaultdict(list)   # callback -> [(caller file, caller, line, wrapper node key)]
    for i in installs:
        if i['node'] is None:
            if i.get('inner'):
                via_wrapper[i['cb']].append((i['file'], i['func'], i['line'], tuple(i['inner'])))
            continue
        key = (i['file'], i['func'], i['node'][0], i['node'][1])
        n = nodes[key]
        n[i['role']].add(i['cb'])
        n['lines'].add(i['line'])
        n['file'] = i['file']
        if i['role'] == 'update' and tuple(i['node']) == ('p:%s:0' % i['func'], -HEADER_SIZE):
            chains.append((i['func'], i['cb']))

    # body accesses per callback (arg0) and per creation node
    def body_sites(f, root, base):
        acc = collections.defaultdict(collections.Counter)
        views = collections.Counter()
        for s in f['sites']:
            ref = s['ref']
            if ref is None or ref[0] != root:
                continue
            off = ref[1] - base
            if off < 0:
                continue
            acc[off][access_key(s)] += 1
            name = (s['view'] or '').split(':')[-1]
            if GENERATED.match(name) and s['spell'] in ('member_view', 'member_unk'):
                views[s['view']] += 1
        casts = collections.Counter()
        cast_views = collections.Counter()
        for c in f['casts']:
            ref = c['ref']
            if ref is None or ref[0] != root:
                continue
            off = ref[1] - base
            opnd = c['opnd'] or ''
            okind = 'void*' if opnd == 'void*' else ('byte*' if opnd in ('unsigned char*', 'char*', 'signed char*') else 'other')
            where = 'body0' if off == 0 else ('header' if off < 0 else 'inner')
            casts[(where, okind, 'gen' if c['gen'] else ('strong' if c['strong'] else 'view'))] += 1
            if c['gen']:
                cast_views[(c['target'], where)] += 1
        return acc, views, casts, cast_views

    update_cbs = {i['cb'] for i in installs if i['role'] == 'update'}
    draw_only = sorted({i['cb'] for i in installs if i['role'] == 'draw'} - update_cbs)
    uf = UF()
    evidence = collections.Counter()
    for cb in update_cbs:
        uf.find(cb)
    for a, b in chains:
        if a in update_cbs and b in update_cbs:
            evidence[('chain', a, b)] += 1
    for key, n in nodes.items():
        ups = sorted(n['update'])
        for b in ups[1:]:
            evidence[('coinstall', ups[0], b)] += 1

    # per-callback body layout (arg0) for the refusal check
    cb_layout = {}
    for cb in update_cbs:
        cb_layout[cb] = collections.defaultdict(collections.Counter)
        for f in by_func.get(cb, ()):
            acc, _, _, _ = body_sites(f, 'p:%s:0' % cb, 0)
            for o, x in acc.items():
                cb_layout[cb][o].update(x)
    comp_layout = {cb: {o: collections.Counter(c) for o, c in acc.items()} for cb, acc in cb_layout.items()}

    def compatible(la, lb):
        for off in set(la) & set(lb):
            sa = {k[0] for k in la[off]}
            sb = {k[0] for k in lb[off]}
            wa = {k[1:] for k in la[off]}
            wb = {k[1:] for k in lb[off]}
            if ('p' in sa and sb & {'s', 'u'} and 'p' not in sb) or ('p' in sb and sa & {'s', 'u'} and 'p' not in sa):
                return False
            if not (wa & wb) and all(w.isdigit() and int(w) <= 4 for w in wa | wb):
                return False
        return True

    refused = collections.Counter()
    shared = set()
    # chains first (strongest), then co-installs
    for (why, a, b), _ in sorted(evidence.items(), key=lambda x: (x[0][0] != 'chain', x[0])):
        ra, rb = uf.find(a), uf.find(b)
        if ra == rb:
            continue
        if compatible(comp_layout[ra], comp_layout[rb]):
            r = uf.union(ra, rb)
            other = rb if r == ra else ra
            for off, c in comp_layout[other].items():
                comp_layout[r].setdefault(off, collections.Counter()).update(c)
        else:
            refused[why] += 1
            # the callback with the smaller own layout is the generic bridge
            shared.add(min((a, b), key=lambda x: (len(cb_layout.get(x) or {}), x)))

    members = collections.defaultdict(set)
    for cb in update_cbs:
        members[uf.find(cb)].add(cb)

    kinds = []
    for rep, cbs in members.items():
        kname = min(cbs, key=lambda x: (x.startswith('func_'), len(x), x))
        acc_all = collections.defaultdict(collections.Counter)
        views = collections.Counter()
        casts = collections.Counter()
        cast_views = collections.Counter()
        files = set()
        functions = []
        part_casts = collections.Counter()
        for cb in sorted(cbs):
            defs = by_func.get(cb, [])
            if not defs:
                functions.append({'func': cb, 'file': None, 'role': 'update', 'note': 'undefined'})
                continue
            for f in defs:
                acc, v, c, cv = body_sites(f, 'p:%s:0' % cb, 0)
                for o, x in acc.items():
                    acc_all[o].update(x)
                views.update(v)
                casts.update(c)
                cast_views.update(cv)
                files.add(f['file'])
            for f in defs:
                for j in (1, 2):
                    if j < len(f['params']) and f['params'][j]['canon'] in ('void*', 'unsigned char*', 'char*', 'int', 'long'):
                        for c in f['casts']:
                            if c['ref'] == ['p:%s:%d' % (cb, j), 0]:
                                part_casts[(j, c['name'])] += 1
            f = defs[0]
            p0 = f['params'][0] if f['params'] else None
            functions.append({'func': cb, 'file': f['file'], 'copies': len(defs),
                              'role': 'shared' if cb in shared else 'update',
                              'arg0': p0['type'] if p0 else None, 'fields': len(cb_layout.get(cb) or {})})
        creators, draws = [], collections.Counter()
        for key, n in nodes.items():
            if not (n['update'] & cbs):
                continue
            ffile, fname, root_, h = key
            if root_ == 'p:%s:0' % fname and h == -HEADER_SIZE:
                continue        # a chain install on the callback's own body, not a creation
            f = by_def.get((ffile, fname))
            draws.update(n['draw'])
            alloc = root_.split(':', 2)[2] if root_.startswith('c:') else root_
            cr = {'func': fname, 'file': n['file'], 'lines': sorted(x for x in n['lines'] if x), 'alloc': alloc,
                  'flags': None}
            if f is not None and root_.startswith('c:'):
                for c in f['calls']:
                    if c['res'] == root_:
                        cr['flags'] = c['consts'][0] if c['consts'] else None
                acc, v, c, cv = body_sites(f, root_, h + HEADER_SIZE)
                for o, x in acc.items():
                    acc_all[o].update(x)
                views.update(v)
                casts.update(c)
                cast_views.update(cv)
            if n['file']:
                files.add(n['file'])
            creators.append(cr)
        for cb in cbs:
            for cfile, cfunc, line, inner in via_wrapper.get(cb, ()):
                n = nodes.get(inner)
                if n is not None:
                    draws.update(n['draw'])
                files.add(cfile)
                creators.append({'func': cfunc, 'file': cfile, 'lines': [line], 'alloc': 'via:' + inner[1],
                                 'flags': None})
        layout, conflicts = merge_layout(acc_all)
        gen_views = sorted(set(views) | {t for (t, w) in cast_views if w == 'body0'})
        fold = sum(v for (w, o, g), v in casts.items() if w == 'body0')
        fold_gen = sum(v for (w, o, g), v in casts.items() if w == 'body0' and g == 'gen')
        fold_void = sum(v for (w, o, g), v in casts.items() if w == 'body0' and o == 'void*')
        held = sorted(x for x in files if x.startswith(hold)) if hold else []
        area = collections.Counter('/'.join(x.split('/')[:2]) for x in files)
        ev = collections.Counter(why for (why, a, b) in evidence if a in cbs and b in cbs)
        size = max((r['off'] + max([int(k[1:]) for k in r['access'] if k[1:].isdigit()] or [1]) for r in layout), default=0)
        kinds.append({
            'kind': kname, 'callbacks': functions, 'creators': creators, 'draw': sorted(draws),
            'files': sorted(files), 'area': area.most_common(1)[0][0] if area else '',
            'layout': layout, 'conflicts': conflicts, 'extent': size,
            'views': gen_views, 'view_uses': dict(views), 'casts': {'|'.join(k): v for k, v in casts.items()},
            'fold_body0': fold, 'fold_body0_generated': fold_gen, 'fold_body0_void': fold_void,
            'evidence': dict(ev), 'held_files': held,
            'fold_position_sprite': sum(part_casts.values()),
            'part_casts': {'%d:%s' % k: v for k, v in part_casts.items()},
            'ready': bool(not held and not conflicts and gen_views and len(cbs) >= 1 and (creators or ev)),
        })
    kinds.sort(key=lambda k: (-(len(k['views']) + k['fold_body0']), k['kind']))

    # draw interfaces: every object registered under one draw callback is read through that callback's arg0
    # (dispatch walks the whole chain), so the kinds drawn by D share D's view of the body prefix.
    groups = []
    for d in sorted({x for k in kinds for x in k['draw']}):
        mem = [k for k in kinds if d in k['draw']]
        acc = collections.defaultdict(collections.Counter)
        dviews, dfiles = collections.Counter(), set()
        dfold = 0
        for f in by_func.get(d, ()):
            a, v, c, cv = body_sites(f, 'p:%s:0' % d, 0)
            for o, x in a.items():
                acc[o].update(x)
            dviews.update(v)
            dviews.update({t: n for (t, w), n in cv.items() if w == 'body0'})
            dfold += sum(n for (w, o, g), n in c.items() if w == 'body0')
            dfiles.add(f['file'])
        own = {o: collections.Counter(x) for o, x in acc.items()}
        for k in mem:
            for r in k['layout']:
                acc[r['off']].update(r['access'])
        layout, conflicts = merge_layout(acc)
        # conflicts inside the draw callback's own extent are the ones that matter for a shared prefix type
        dext = max((o + 4 for o in own), default=0)
        views = sorted(set(dviews) | {v for k in mem for v in k['views']})
        files = sorted(dfiles | {x for k in mem for x in k['files']})
        groups.append({'draw': d, 'kinds': [k['kind'] for k in mem], 'draw_files': sorted(dfiles),
                       'draw_extent': dext, 'own_fields': sorted(own),
                       'conflicts_in_prefix': [c for c in conflicts if c[0] < dext], 'conflicts': len(conflicts),
                       'views': views, 'fold_body0': dfold + sum(k['fold_body0'] for k in mem), 'files': files,
                       'held_files': sorted(x for x in files if hold and x.startswith(hold))})
    groups.sort(key=lambda g: (-len(g['views']), g['draw']))
    with open(out / 'draw_groups.tsv', 'w') as fh:
        fh.write('draw\tkinds\tviews\tfold_body0\tdraw_extent\tprefix_conflicts\tfiles\theld_files\tdraw_files\tkind_names\n')
        for g in groups:
            fh.write('\t'.join(str(x) for x in [
                g['draw'], len(g['kinds']), len(g['views']), g['fold_body0'], '%#x' % g['draw_extent'],
                len(g['conflicts_in_prefix']), len(g['files']), len(g['held_files']), ','.join(g['draw_files']),
                ','.join(g['kinds'])]) + '\n')
    summary = {
        'functions': len(L.funcs), 'callbacks': len(L.callbacks), 'installs': len(installs),
        'install_via': dict(collections.Counter(i['via'].split(':')[0] for i in installs)),
        'install_roles': dict(collections.Counter(i['role'] for i in installs)),
        'allocators': len(L.allocators), 'carriers': len(L.carriers), 'chains': len(chains),
        'kinds': len(kinds), 'kinds_multi': sum(1 for k in kinds if len(k['callbacks']) > 1),
        'kinds_ready': sum(1 for k in kinds if k['ready']), 'shared_callbacks': sorted(shared),
        'refused_unions': dict(refused),
        'views_in_kinds': sum(len(k['views']) for k in kinds),
        'fold_body0': sum(k['fold_body0'] for k in kinds),
        'fold_body0_void': sum(k['fold_body0_void'] for k in kinds),
        'fold_position_sprite': sum(k['fold_position_sprite'] for k in kinds),
        'ambiguous_function_names': len(L.dup_all),
        'unresolved_duplicate_references': sum(L.unresolved.values()),
        'duplicate_names_split': len(L.dup),
        'duplicate_names_kept_merged': len(L.merged_ambiguous),
        'draw_only_callbacks': draw_only,
    }
    summary['draw_groups'] = len(groups)
    summary['draw_groups_multi'] = sum(1 for g in groups if len(g['kinds']) > 1)
    (out / 'kinds.json').write_text(json.dumps({'summary': summary, 'kinds': kinds, 'draw_groups': groups},
                                               indent=1, default=list) + '\n')
    (out / 'installs.json').write_text(json.dumps(installs, indent=0, default=list) + '\n')
    fields = ['rank', 'kind', 'area', 'status', 'callbacks', 'creators', 'draw', 'views', 'view_uses', 'fold_body0',
              'fold_body0_void', 'fold_body0_generated', 'fold_position_sprite', 'extent', 'conflicts', 'evidence', 'files', 'callback_names',
              'view_names']
    with open(out / 'kinds.tsv', 'w') as fh:
        fh.write('\t'.join(fields) + '\n')
        for i, k in enumerate(kinds, 1):
            status = 'held' if k['held_files'] else ('ready' if k['ready'] else ('conflict' if k['conflicts'] else 'open'))
            row = [i, k['kind'], k['area'], status, len(k['callbacks']), len(k['creators']), len(k['draw']),
                   len(k['views']), sum(k['view_uses'].values()), k['fold_body0'], k['fold_body0_void'],
                   k['fold_body0_generated'], k['fold_position_sprite'], '%#x' % k['extent'], len(k['conflicts']),
                   json.dumps(k['evidence'], sort_keys=True), len(k['files']),
                   ','.join(c['func'] for c in k['callbacks']),
                   ','.join(v.split(':')[-1] for v in k['views'])]
            fh.write('\t'.join(str(x) for x in row) + '\n')
    print(json.dumps(summary, indent=1))
    return 0


def cmd_family(args):
    data = json.loads((Path(args.out) / 'kinds.json').read_text())
    kind = next((k for k in data['kinds'] if k['kind'] == args.kind), None)
    if kind is None:
        print('no kind %s' % args.kind, file=sys.stderr)
        return 1
    scope = tuple(args.view_scope or ())
    views = []
    for v in kind['views']:
        path, _, name = v.rpartition(':')
        if scope and not path.startswith(scope):
            continue
        views.append('%s:%s' % (path, name))
    fam = {'type': args.type, 'header': args.header, 'views': views, 'kind': args.kind,
           'callbacks': [c['func'] for c in kind['callbacks']]}
    if args.hold:
        fam['hold'] = args.hold
    sys.stdout.write(json.dumps(fam, indent=1) + '\n')
    return 0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('cmd', choices=['extract', 'report', 'family'])
    ap.add_argument('--root', default=str(ROOT))
    ap.add_argument('--out', required=True)
    ap.add_argument('--scope', nargs='*')
    ap.add_argument('--hold', nargs='*')
    ap.add_argument('--workers', type=int, default=6)
    ap.add_argument('--kind')
    ap.add_argument('--type')
    ap.add_argument('--header')
    ap.add_argument('--view-scope', nargs='*')
    args = ap.parse_args(argv)
    return {'extract': cmd_extract, 'report': cmd_report, 'family': cmd_family}[args.cmd](args)


if __name__ == '__main__':
    sys.exit(main())
