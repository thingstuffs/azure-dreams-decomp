#!/usr/bin/env python3
"""Type-flow graph and component solver: types and prototypes decided together, by runtime identity.

    type_flow.py graph  --out DIR [--scope src/...] [--tus F...] [--workers 6]
    type_flow.py dryrun --graph DIR --rt RTDIR --holds H.tsv... [--actor-holds A.tsv...] --out DIR
    type_flow.py plan   --graph DIR --rt RTDIR --component ID --dryrun DIR --out plan.json

A held prototype fix is usually not wrong on its own: the other end of the value's flow (a caller's local,
a struct field, a function-pointer slot, a global) carries another type, so the fix would need a new cast.
This tool models every place a value is held and every way it moves, and solves the coupled places as one
transaction.

graph (read-only; one clang parse per registered physical TU, mipsel, as cast_ast/field_census)
  Nodes (string keys):
    P:<fn>#<i>           parameter i of fn (static functions: <fn>@<file>)
    R:<fn>               return value of fn
    L:<fn>:<var>@<line>  local variable
    G:<name>             global variable (its value)
    &<lvalue node>       address of an object (&G:x, &F:Rec.m); `[]` marks an array element
    F:<Rec>.<member>     struct/union member (per record type, not per object)
    <node>*              the object a pointer node points at (deref, `p[i]`)
    <node>#<i>, #ret     parameter / return of a function-pointer holder (a slot)
    FN:<fn>              function designator (installed callbacks)
  Edges (dst <- src): init, assign, arg, ret, cmp, cond; every edge keeps its explicit casts (outermost
  first), the implicit conversion clang inserted, the byte offset added on the way (`p + 0x20`), the
  declared types at both ends and its site.  `uses` are casts applied to a node and consumed in place
  (`((T *)p)->m`, `*(W *)((u8 *)p + K)`), `int_uses` integer arithmetic on integer holders.
  Output: DIR/tu/<n>.json per TU and DIR/index.json.

dryrun (read-only): see solve.py-style docstring of `dryrun_main`.
"""
from __future__ import annotations

import argparse
from concurrent.futures import ProcessPoolExecutor
import gzip
import json
import os
from pathlib import Path
import re
import sys

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent)]

ASSIGN_OPS = {'='}
CMP_OPS = {'==', '!=', '<', '>', '<=', '>='}
INT_OPS = {'+', '-', '&', '|', '^', '>>', '<<', '*', '/', '%'}


def qt(e):
    t = (e or {}).get('type') or {}
    return t.get('qualType', '')


def kids(e):
    return (e or {}).get('inner') or []


def int_value(e):
    while e and e.get('kind') in ('ParenExpr', 'ImplicitCastExpr', 'CStyleCastExpr') and kids(e):
        e = kids(e)[0]
    if not e:
        return None
    k = e.get('kind')
    if k == 'IntegerLiteral':
        return int(e['value'])
    if k == 'CharacterLiteral':
        return int(e['value'])
    if k == 'UnaryOperator' and e.get('opcode') in ('-', '+', '~'):
        v = int_value(kids(e)[0])
        if v is None:
            return None
        return -v if e['opcode'] == '-' else (~v if e['opcode'] == '~' else v)
    return None


def is_pointer_spelling(t):
    t = (t or '').strip()
    return t.endswith('*') or '(*)' in t


def fnptr_arity(t):
    """'void (*)(int, void *)' -> 2; None when t is not a function pointer type."""
    m = re.search(r'\(\*\s*\w*\s*\)\s*\((.*)\)\s*$', t or '')
    if not m:
        return None
    inner = m.group(1).strip()
    if inner in ('', 'void'):
        return 0
    depth, n = 0, 1
    for ch in inner:
        depth += ch == '('
        depth -= ch == ')'
        n += ch == ',' and depth == 0
    return n


def fn_param_types(t):
    """'int (void *, int)' -> ['void *', 'int']; [] for '(void)'; None for '()' (unprototyped)."""
    m = re.match(r'^[^(]*?\((.*)\)\s*$', t or '')
    if not m:
        return None
    inner = m.group(1).strip()
    if inner == '':
        return None
    if inner == 'void':
        return []
    out, depth, cur = [], 0, ''
    for ch in inner:
        if ch == ',' and depth == 0:
            out.append(cur.strip())
            cur = ''
            continue
        depth += ch == '('
        depth -= ch == ')'
        cur += ch
    out.append(cur.strip())
    return [x for x in out if x != '...']


def fn_return_type(t):
    m = re.match(r'^(.*?)\s*\((.*)\)\s*$', t or '')
    return m.group(1).strip() if m else ''


# --------------------------------------------------------------------------- per-TU extraction

class Extract:
    """Walk one parsed TU (cast_ast.Unit) and collect the flow facts of every function body in scope."""

    def __init__(self, unit, files=None):
        self.u = unit
        self.T = unit.T
        self.files = files
        self.fnkey = {}            # FunctionDecl id -> key
        self.static_names = {}     # name -> key, static functions defined/declared in this TU
        self.decl_types = {}       # node -> {type: count} declared types seen
        self.functions = []
        self.edges = []
        self.uses = []
        self.int_uses = []
        self.calls = []
        self.protos = {}
        self.globals = {}
        self.records = set()
        self._prepare()

    # ---------------------------------------------------------------- keys
    def _prepare(self):
        for d in self.u.tree.get('inner', []):
            k = d.get('kind')
            if k == 'FunctionDecl':
                name = d.get('name')
                if d.get('storageClass') == 'static':
                    f = d.get('_f') or self.u.rel
                    key = self.static_names.setdefault(name, '%s@%s' % (name, f))
                else:
                    key = name
                self.fnkey[d['id']] = key
            elif k == 'VarDecl':
                self.globals.setdefault(d['name'], qt(d))

    def key_of_fn(self, ref):
        if ref.get('id') in self.fnkey:
            return self.fnkey[ref['id']]
        name = ref.get('name')
        return self.static_names.get(name, name)

    def declare(self, node, t):
        if node and t:
            c = self.decl_types.setdefault(node, {})
            c[t] = c.get(t, 0) + 1
            self.note_record(t)

    def note_record(self, t):
        r = self.T.record(t) if t else None
        if r:
            self.records.add(r)

    # ---------------------------------------------------------------- lvalues / values
    def lvalue(self, e):
        """Node key of an lvalue expression, or None."""
        e = self.strip_parens(e)
        if not e:
            return None
        k = e.get('kind')
        if k == 'DeclRefExpr':
            ref = e.get('referencedDecl') or {}
            rk = ref.get('kind')
            if rk == 'ParmVarDecl':
                return self.params.get(ref.get('id'))
            if rk == 'VarDecl':
                if ref.get('id') in self.locals:
                    return self.locals[ref['id']]
                n = 'G:' + ref.get('name', '?')
                self.declare(n, qt(ref))
                return n
            if rk == 'FunctionDecl':
                return 'FN:' + self.key_of_fn(ref)
            return None
        if k == 'MemberExpr':
            base = kids(e)[0] if kids(e) else None
            bt = qt(base)
            rec = self.T.record(bt)
            if rec is None:
                return None
            n = 'F:%s.%s' % (rec, e.get('name') or '?')
            self.declare(n, qt(e))
            self.records.add(rec)
            return n
        if k == 'ArraySubscriptExpr':
            base = kids(e)[0]
            b = self.strip_implicit(base)
            if b is not None and b.get('kind') == 'ImplicitCastExpr':
                pass
            # array object (decayed) or pointer value
            inner = self.strip_parens(base)
            if inner and inner.get('kind') == 'ImplicitCastExpr' and inner.get('castKind') == 'ArrayToPointerDecay':
                lv = self.lvalue(kids(inner)[0])
                if lv:
                    n = lv + '[]'
                    self.declare(n, qt(e))
                    return n
                return None
            v = self.value(base)
            if v and v['node'] and not v['casts']:
                n = v['node'] + '*'
                self.declare(n, qt(e))
                return n
            return None
        if k == 'UnaryOperator' and e.get('opcode') == '*':
            v = self.value(kids(e)[0])
            if v and v['node'] and not v['casts'] and not v['off']:
                n = v['node'] + '*'
                self.declare(n, qt(e))
                return n
            return None
        return None

    @staticmethod
    def strip_parens(e):
        while e and e.get('kind') == 'ParenExpr' and kids(e):
            e = kids(e)[0]
        return e

    @staticmethod
    def strip_implicit(e):
        while e and e.get('kind') in ('ParenExpr', 'ImplicitCastExpr') and kids(e):
            e = kids(e)[0]
        return e

    def value(self, e):
        """Value flow of an rvalue: {'node', 'off', 'casts': [(type, castKind)], 'imp': [castKind],
        'src_t', 'arith'} or None when the value has no single holder."""
        casts, imp = [], []
        off = 0
        arith = False
        while e:
            k = e.get('kind')
            if k == 'ParenExpr':
                e = kids(e)[0]
                continue
            if k == 'ImplicitCastExpr':
                ck = e.get('castKind')
                sub = kids(e)[0]
                if ck == 'LValueToRValue':
                    n = self.lvalue(sub)
                    return self._v(n, off, casts, imp, qt(sub), arith)
                if ck == 'ArrayToPointerDecay':
                    n = self.lvalue(sub)
                    return self._v(('&' + n + '[]') if n else None, off, casts, imp, qt(e), arith)
                if ck == 'FunctionToPointerDecay':
                    n = self.lvalue(sub)
                    return self._v(n, off, casts, imp, qt(e), arith)
                if ck not in ('NoOp',):
                    imp.append(ck)
                e = sub
                continue
            if k == 'CStyleCastExpr':
                casts.append((qt(e), e.get('castKind')))
                e = kids(e)[0]
                continue
            if k == 'UnaryOperator' and e.get('opcode') == '&':
                n = self.lvalue(kids(e)[0])
                if n:
                    self.declare('&' + n, qt(e))
                v = self._v(('&' + n) if n else None, off, casts, imp, qt(e), arith)
                r = self.addr_root(kids(e)[0])
                if v and r and r[0] != '&' + (n or ''):
                    v['root'], v['roff'] = r[0], r[1] + off
                return v
            if k == 'BinaryOperator' and e.get('opcode') in ('+', '-'):
                a, b = kids(e)
                ia, ib = int_value(a), int_value(b)
                if ib is not None and ia is None:
                    ptr, n = a, ib
                elif ia is not None and ib is None and e['opcode'] == '+':
                    ptr, n = b, ia
                else:
                    return None
                pt = self.T.pointee(qt(ptr))
                scale = 1
                if pt is not None:
                    scale = self.T.size(pt + ('' if pt.endswith('*') else '')) or 1
                    if pt in ('void',):
                        scale = 1
                off += (n if e['opcode'] == '+' else -n) * scale
                arith = True
                e = ptr
                continue
            if k == 'BinaryOperator' and e.get('opcode') in ('=', ','):
                e = kids(e)[1]
                continue
            if k == 'CallExpr':
                callee = self.callee_node(e)
                if callee is None:
                    return None
                return self._v(callee[1], off, casts, imp, qt(e), arith)
            if k == 'DeclRefExpr':
                n = self.lvalue(e)
                return self._v(n, off, casts, imp, qt(e), arith)
            if k in ('MemberExpr', 'ArraySubscriptExpr'):
                n = self.lvalue(e)
                return self._v(n, off, casts, imp, qt(e), arith)
            if k == 'IntegerLiteral' and int(e.get('value', '1')) == 0:
                return {'node': None, 'null': True, 'off': off, 'casts': casts, 'imp': imp, 'src_t': 'int', 'arith': arith}
            return None
        return None

    def addr_root(self, e, depth=0):
        """(root node, byte offset) of an lvalue reached through member / constant-index chains:
        `g.a.b` -> ('&G:g', off), `p->a.b` / `((T *)((u8 *)p - 0x20))->m` -> (p's node, off)."""
        import cast_ast as A
        e = self.strip_parens(e)
        if not e or depth > 12:
            return None
        k = e.get('kind')
        if k == 'DeclRefExpr':
            n = self.lvalue(e)
            return ('&' + n, 0) if n else None
        if k == 'MemberExpr':
            base = kids(e)[0]
            rec = self.T.record(qt(base))
            off = A.member_offset(self.u, rec, e.get('name')) if rec else None
            if off is None:
                return None
            if e.get('isArrow'):
                v = self.value(base)
                if v and v.get('node'):
                    return (v.get('root') or v['node'], v.get('roff', 0) + v['off'] + off) if not v.get('root') \
                        else (v['root'], v['roff'] + off)
                return None
            r = self.addr_root(base, depth + 1)
            return (r[0], r[1] + off) if r else None
        if k == 'ArraySubscriptExpr':
            base, idx = kids(e)
            i = int_value(idx)
            size = self.T.size(qt(e))
            inner = self.strip_parens(base)
            if i is None or not size:
                return None
            if inner and inner.get('kind') == 'ImplicitCastExpr' and inner.get('castKind') == 'ArrayToPointerDecay':
                r = self.addr_root(kids(inner)[0], depth + 1)
                return (r[0], r[1] + i * size) if r else None
            v = self.value(base)
            if v and v.get('node'):
                return (v['node'], v['off'] + i * size)
            return None
        if k == 'UnaryOperator' and e.get('opcode') == '*':
            v = self.value(kids(e)[0])
            if v and v.get('node'):
                return (v['node'], v['off'])
        return None

    @staticmethod
    def _v(node, off, casts, imp, src_t, arith):
        if node is None:
            return None
        return {'node': node, 'off': off, 'casts': casts, 'imp': imp, 'src_t': src_t, 'arith': arith}

    def callee_node(self, call):
        """('direct', 'R:fn') / ('slot', '<holder>#ret') for a CallExpr; also returns the param prefix."""
        c = kids(call)[0] if kids(call) else None
        s = self.strip_implicit(c)
        if s and s.get('kind') == 'DeclRefExpr' and (s.get('referencedDecl') or {}).get('kind') == 'FunctionDecl':
            key = self.key_of_fn(s['referencedDecl'])
            return ('direct', 'R:' + key, 'P:' + key, s['referencedDecl'])
        if s and s.get('kind') == 'UnaryOperator' and s.get('opcode') == '*':
            s = self.strip_implicit(kids(s)[0])
        v = self.value(c) if c else None
        if v and v['node'] and not v['off']:
            return ('slot', v['node'] + '#ret', v['node'] + '#', None)
        return None

    # ---------------------------------------------------------------- edges
    def edge(self, kind, dst, dst_t, val, site, extra=None):
        if not dst or not val:
            return
        rec = {'k': kind, 'dst': dst, 'dt': dst_t, 'src': val['node'], 'st': val['src_t'], 'off': val['off'],
               'casts': [c[0] for c in val['casts']], 'ck': [c[1] for c in val['casts']], 'imp': val['imp'],
               'fn': self.cur, 'file': site[0], 'line': site[1]}
        if val.get('null'):
            rec['null'] = 1
        if val.get('root'):
            rec['root'], rec['roff'] = val['root'], val['roff']
        if extra:
            rec.update(extra)
        self.edges.append(rec)
        for c in val['casts']:
            self.note_record(c[0])
        self.note_record(dst_t)
        self.note_record(val['src_t'])

    def site(self, e):
        return (e.get('_f') or self.curfile, e.get('_l') or 0)

    @staticmethod
    def macro(e):
        rng = (e or {}).get('range') or {}
        return int(any('spellingLoc' in (rng.get(k) or {}) or 'expansionLoc' in (rng.get(k) or {}) for k in ('begin', 'end')))

    # ---------------------------------------------------------------- functions
    def run(self):
        for d in self.u.tree.get('inner', []):
            if d.get('kind') == 'VarDecl':
                self.global_init(d)
            if d.get('kind') != 'FunctionDecl':
                continue
            body = [x for x in kids(d) if x.get('kind') == 'CompoundStmt']
            f = d.get('_f') or self.u.rel
            if not body:
                continue
            if self.files is not None and f not in self.files:
                continue
            self.function(d, body[0], f)
        return self

    def global_init(self, d):
        init = [x for x in kids(d) if x.get('kind') not in ('FullComment',)]
        if not init or d.get('storageClass') == 'extern':
            return
        f = d.get('_f') or self.u.rel
        if self.files is not None and f not in self.files:
            return
        self.cur, self.curfile = '<global>', f
        self.params, self.locals = {}, {}
        node = 'G:' + d['name']
        self.declare(node, qt(d))
        self.init_list(node, qt(d), init[-1])

    def init_list(self, node, t, e):
        """Static initializer: map list elements to members (records) or elements (arrays)."""
        e = self.strip_parens(e)
        if not e:
            return
        if e.get('kind') != 'InitListExpr':
            val = self.value(e)
            if val is not None:
                self.edge('init', node, t, val, self.site(e))
            return
        elems = kids(e)
        if e.get('array_filler'):
            pass
        r = self.T.resolve(t)
        if re.search(r'\[\d*\]$', r):
            elt = re.sub(r'\s*\[\d*\]$', '', t.strip())
            for x in elems:
                self.init_list(node + '[]', elt, x)
            return
        rec = self.T.record(t)
        lay = self.u.layouts.get(rec) if rec else None
        if not lay:
            return
        names = [kid for kid in lay['kids'] if not kid['bits']]
        if rec and rec in self.u.layouts and self.u.layouts[rec].get('kind') == 'union':
            names = names[:1]
        for kid, x in zip(names, elems):
            if not kid['name']:
                continue
            self.records.add(rec)
            n = 'F:%s.%s' % (rec, kid['name'])
            self.declare(n, kid['type'])
            self.init_list(n, kid['type'], x)

    def function(self, d, body, f):
        key = self.fnkey.get(d['id']) or d['name']
        self.cur, self.curfile = key, f
        self.params, self.locals = {}, {}
        ps = [x for x in kids(d) if x.get('kind') == 'ParmVarDecl']
        pinfo = []
        for i, p in enumerate(ps):
            n = 'P:%s#%d' % (key, i)
            self.params[p['id']] = n
            self.declare(n, qt(p))
            pinfo.append({'name': p.get('name', ''), 'type': qt(p)})
        ftype = qt(d)
        self.declare('R:' + key, fn_return_type(ftype))
        self.functions.append({'key': key, 'name': d['name'], 'file': f, 'line': d.get('_l'),
                               'static': d.get('storageClass') == 'static', 'params': pinfo,
                               'ret': fn_return_type(ftype), 'variadic': bool(d.get('variadic'))})
        self.walk(body)

    def walk(self, root):
        stack = [(root, None)]
        while stack:
            e, parent = stack.pop()
            if not isinstance(e, dict):
                continue
            self.visit(e, parent)
            for k in reversed(kids(e)):
                stack.append((k, e))

    def visit(self, e, parent):
        k = e.get('kind')
        if k == 'VarDecl':
            n = 'L:%s:%s@%s' % (self.cur, e.get('name'), e.get('_l'))
            self.locals[e['id']] = n
            self.declare(n, qt(e))
            init = [x for x in kids(e) if x.get('kind') != 'FullComment']
            if init and e.get('init'):
                if init[-1].get('kind') == 'InitListExpr':
                    self.init_list(n, qt(e), init[-1])
                else:
                    self.edge('init', n, qt(e), self.value(init[-1]), self.site(e))
            return
        if k == 'BinaryOperator' and e.get('opcode') in ASSIGN_OPS:
            lhs, rhs = kids(e)
            dst = self.lvalue(lhs)
            if dst:
                self.edge('assign', dst, qt(lhs), self.value(rhs), self.site(e))
            return
        if k == 'BinaryOperator' and e.get('opcode') in CMP_OPS:
            a, b = kids(e)
            va, vb = self.value(a), self.value(b)
            if va and vb and va.get('node') and vb.get('node'):
                self.edge('cmp', va['node'], va['src_t'], vb, self.site(e),
                          {'acasts': [c[0] for c in va['casts']], 'aoff': va['off']})
            else:
                for v, other in ((va, b), (vb, a)):
                    if v and v.get('node') and int_value(other) not in (None, 0):
                        self.int_uses.append({'node': v['node'], 'op': e['opcode'], 'fn': self.cur,
                                              'file': self.site(e)[0], 'line': self.site(e)[1]})
            return
        if k == 'BinaryOperator' and e.get('opcode') in INT_OPS:
            for x in kids(e):
                s = self.strip_implicit(x)
                if s is not None and s.get('kind') in ('DeclRefExpr', 'MemberExpr'):
                    xt = qt(s)
                    if not is_pointer_spelling(xt):
                        n = self.lvalue(s)
                        if n:
                            other = [y for y in kids(e) if y is not x]
                            self.int_uses.append({'node': n, 'op': e['opcode'], 'fn': self.cur,
                                                  'k': int_value(other[0]) if other else None,
                                                  'file': self.site(e)[0], 'line': self.site(e)[1]})
            return
        if k == 'CallExpr':
            self.call(e)
            return
        if k == 'ReturnStmt':
            if kids(e):
                self.edge('ret', 'R:' + self.cur, None, self.value(kids(e)[0]), self.site(e))
            return
        if k == 'MemberExpr':
            self.member_access(e, parent)
        if k == 'MemberExpr' and e.get('isArrow'):
            base = self.strip_parens(kids(e)[0])
            if base and base.get('kind') == 'CStyleCastExpr':
                v = self.value(kids(base)[0])
                if v and v['node']:
                    rec = self.T.record(qt(base))
                    if rec:
                        self.records.add(rec)
                    self.uses.append({'ctx': 'member', 'node': v['node'], 'cast': qt(base), 'off': v['off'],
                                      'inner_casts': [c[0] for c in v['casts']], 'member': e.get('name'),
                                      'mtype': qt(e), 'fn': self.cur, 'file': self.site(e)[0],
                                      'line': self.site(e)[1], 'macro': self.macro(e)})
            return
        if k == 'UnaryOperator' and e.get('opcode') == '*':
            inner = self.strip_parens(kids(e)[0])
            if inner and inner.get('kind') == 'CStyleCastExpr':
                v = self.value(kids(inner)[0])
                if v and v['node']:
                    self.uses.append({'ctx': 'raw', 'node': v['node'], 'cast': qt(inner), 'off': v['off'],
                                      'inner_casts': [c[0] for c in v['casts']], 'wtype': qt(e),
                                      'fn': self.cur, 'file': self.site(e)[0], 'line': self.site(e)[1],
                                      'macro': self.macro(e)})
            return
        if k == 'ArraySubscriptExpr':
            base = self.strip_parens(kids(e)[0])
            if base and base.get('kind') == 'ImplicitCastExpr':
                base = self.strip_parens(kids(base)[0]) if base.get('castKind') == 'LValueToRValue' else base
            base = self.strip_parens(base)
            if base and base.get('kind') == 'CStyleCastExpr':
                v = self.value(kids(base)[0])
                idx = int_value(kids(e)[1])
                if v and v['node'] and idx is not None:
                    size = self.T.size(qt(e)) or 1
                    self.uses.append({'ctx': 'raw', 'node': v['node'], 'cast': qt(base),
                                      'off': v['off'] + idx * size, 'inner_casts': [c[0] for c in v['casts']],
                                      'wtype': qt(e), 'fn': self.cur, 'file': self.site(e)[0],
                                      'line': self.site(e)[1]})
            return

    def member_access(self, e, parent):
        """`p->m` / `g.m` through an uncast holder: the member a retype of the holder must keep."""
        import cast_ast as A
        if parent is not None and parent.get('kind') == 'MemberExpr' and not parent.get('isArrow'):
            return          # inner link of a `.` chain; the outermost access is recorded
        base = kids(e)[0] if kids(e) else None
        rec = self.T.record(qt(base)) if base else None
        moff = A.member_offset(self.u, rec, e.get('name')) if rec else None
        if moff is None:
            return
        if e.get('isArrow'):
            v = self.value(base)
            if not v or not v.get('node') or v['casts']:
                return
            node, off = v['node'], v['off'] + moff
        else:
            r = self.addr_root(e)
            if not r:
                return
            node, off = r
        self.uses.append({'ctx': 'macc', 'node': node, 'off': off, 'member': e.get('name'), 'rec': rec,
                          'mtype': qt(e), 'fn': self.cur, 'file': self.site(e)[0], 'line': self.site(e)[1]})

    def call(self, e):
        c = self.callee_node(e)
        args = kids(e)[1:]
        site = self.site(e)
        if c is None:
            return
        mode, ret, prefix, ref = c
        ptypes = None
        if mode == 'direct':
            ptypes = fn_param_types(qt(ref))
            key = ret[2:]
            self.protos.setdefault(key, qt(ref))
        self.calls.append({'caller': self.cur, 'callee': ret[2:] if mode == 'direct' else ret[:-4],
                           'mode': mode, 'nargs': len(args), 'nparams': None if ptypes is None else len(ptypes),
                           'file': site[0], 'line': site[1]})
        for i, a in enumerate(args):
            dt = ptypes[i] if ptypes is not None and i < len(ptypes) else qt(a)
            dst = (prefix + '#%d' % i) if mode == 'direct' else (prefix + '%d' % i)
            self.edge('arg', dst, dt, self.value(a), site, {'i': i})

    # ---------------------------------------------------------------- output
    def dump(self):
        recs = {}
        todo = list(self.records)
        seen = set()
        while todo:
            r = todo.pop()
            if r in seen:
                continue
            seen.add(r)
            lay = self.u.layouts.get(r)
            if not lay or not lay.get('size'):
                continue
            fields = []
            stack = [(k, 0) for k in lay['kids']]
            while stack:
                node, depth = stack.pop(0)
                if node['name'] or depth == 0:
                    fields.append([node['name'], node['off'], node['type'], node['bits']])
                if not node['name']:
                    stack.extend((k, depth + 1) for k in node['kids'])
            recs[r] = {'size': lay['size'], 'kind': lay.get('kind'), 'file': self.u.record_files.get(r, ''),
                       'fields': fields}
        return {'tu': self.u.rel, 'functions': self.functions, 'edges': self.edges, 'uses': self.uses,
                'int_uses': self.int_uses, 'calls': self.calls, 'protos': self.protos,
                'decl_types': self.decl_types, 'records': recs,
                'typedefs': self._typedefs(recs)}

    def _typedefs(self, recs):
        word = re.compile(r'[A-Za-z_]\w*')
        names = set()
        for c in self.decl_types.values():
            for t in c:
                names.update(word.findall(t))
        for e in self.edges:
            for t in e['casts']:
                names.update(word.findall(t))
            names.update(word.findall(e.get('dt') or ''))
            names.update(word.findall(e.get('st') or ''))
        for u in self.uses:
            names.update(word.findall(u.get('cast', '')))
            for t in u.get('inner_casts', ()):
                names.update(word.findall(t))
            names.update(word.findall(u.get('mtype', '') or u.get('wtype', '')))
        for r in recs.values():
            for f in r['fields']:
                names.update(word.findall(f[2]))
        scalar = re.compile(r'^(?:(?:un)?signed )?(?:char|short|int|long)(?: int)?$|^unsigned$|^void$')
        names.update(k for k, v in self.u.typedefs.items() if scalar.match(v.strip()))
        out, todo = {}, [n for n in names if n in self.u.typedefs]
        while todo:
            n = todo.pop()
            if n in out:
                continue
            out[n] = self.u.typedefs[n]
            todo.extend(m for m in word.findall(out[n]) if m in self.u.typedefs and m not in out)
        return out


def _extract(args):
    root, rel, recipe, out = args
    import cast_ast as A
    try:
        unit, err = A.clang_unit(root, rel, recipe)
    except Exception as exc:  # noqa: BLE001 - one failing TU is reported, the rest go on
        return rel, 'error: %s' % exc
    if unit is None:
        return rel, 'parse: %s' % err
    x = Extract(unit).run()
    data = x.dump()
    name = re.sub(r'[^A-Za-z0-9_.-]', '_', rel) + '.json.gz'
    with gzip.open(Path(out) / 'tu' / name, 'wt') as fh:
        fh.write(json.dumps(data, separators=(',', ':')))
    return rel, 'ok' if not err else 'ok-with-errors'


def graph_main(a):
    root = Path(a.root).resolve()
    out = Path(a.out)
    (out / 'tu').mkdir(parents=True, exist_ok=True)
    sys.path.insert(0, str(root / 'tools'))
    import layout_compile_identity as L
    physical, _members = L.recipes(root)
    tus = sorted(physical)
    if a.tus:
        tus = [t for t in tus if t in set(a.tus)]
    if a.scope:
        tus = [t for t in tus if t.startswith(tuple(a.scope))]
    done = {}
    jobs = []
    for rel in tus:
        name = re.sub(r'[^A-Za-z0-9_.-]', '_', rel) + '.json.gz'
        if a.resume and (out / 'tu' / name).exists():
            done[rel] = 'cached'
            continue
        recipe = physical[rel].get('slus_unit') and 'slus_unit:' + physical[rel]['slus_unit']
        jobs.append((str(root), rel, physical[rel] if physical[rel].get('slus_unit') else None, str(out)))
    status = dict(done)
    if a.workers > 1:
        with ProcessPoolExecutor(a.workers) as ex:
            for rel, st in ex.map(_extract, jobs, chunksize=4):
                status[rel] = st
    else:
        for j in jobs:
            rel, st = _extract(j)
            status[rel] = st
    (out / 'index.json').write_text(json.dumps({'root': str(root), 'tus': status}, indent=1))
    bad = {k: v for k, v in status.items() if not v.startswith(('ok', 'cached'))}
    print('%d TUs, %d failed' % (len(status), len(bad)))
    for k, v in list(bad.items())[:20]:
        print('  ', k, v)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest='cmd', required=True)
    g = sub.add_parser('graph')
    g.add_argument('--root', default=str(HERE.parents[1]))
    g.add_argument('--out', required=True)
    g.add_argument('--scope', nargs='*')
    g.add_argument('--tus', nargs='*')
    g.add_argument('--workers', type=int, default=4)
    g.add_argument('--resume', action='store_true')
    import type_flow_solve as S
    S.add_parsers(sub)
    a = ap.parse_args(argv)
    if a.cmd == 'graph':
        return graph_main(a)
    return S.dispatch(a)


if __name__ == '__main__':
    sys.exit(main())
