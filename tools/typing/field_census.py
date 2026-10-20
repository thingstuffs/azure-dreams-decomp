#!/usr/bin/env python3
"""Field-access census: every struct-field access site in the compiled tree, typed to a base identity.

A *site* is one lvalue that reads or writes memory at a constant offset from a base pointer, in any
spelling the tree uses:

  raw_cast    *((T *) (((u8 *) p) + off))   (and *(T *)p, any byte-pointer cast, negative offsets)
  F_macro     F(p, T, off)                  (the 13 per-file F() macros, all expand to raw_cast)
  raw_index   ((T *) p)[k]                  (constant k)
  member_unk  p->unk_XX / s.unk_XX          on a shared (include/) type
  member_view p->m / s.m                    on an address-named S_<addr> or *View view type
  member_named p->name                      on a shared type with a recovered name

Clang (mipsel target, so pointers are 4 bytes and layouts are the PS1 ones) parses each registered physical
TU; its JSON AST gives exact expression types and its record-layout dump gives field offsets.  Nothing is
compiled for the PS1 and no object is produced: this tool is read-only over src/ and include/.

Base identity is a flow-insensitive points-to analysis with offsets (Steensgaard style, union-find):
  - a pointer local/parameter is unified with every value assigned to it (``owner = owner_work - 0x20``
    puts owner at -0x20 in owner_work's object);
  - loading a pointer from a field yields that field's pointee, so pointer chains
    ``*(void **)(p + 8)`` resolve to "the object p+8 points at";
  - declared types, prototype parameter types (the implicit cast at each argument) and global declarations
    attach a type to the object; shared (include/) record types are *strong*, S_<addr>/View/Rec_ types weak;
  - call arguments and return values are unified with the callee's parameter/return in a second phase,
    refused per parameter when the arguments carry conflicting strong types (generic void * helpers).
Merges that would put two different strong types at the same offset are refused and counted.

Outputs (all under --out):
  sites.jsonl.gz   one record per site (deduplicated by source file + function, not per TU)
  layouts.jsonl    per base identity: offset -> widths/signs, uses, readers, writers, constants written
  top_types.tsv    the 30 base identities with the most sites
  summary.json     counts, coverage, refusals
"""
from __future__ import annotations

import argparse
import collections
import gzip
import json
import os
from pathlib import Path
import re
import subprocess
import sys
from concurrent.futures import ProcessPoolExecutor

HERE = Path(__file__).resolve().parent
TOOLS = HERE.parent
ROOT = TOOLS.parent

CLANG = os.environ.get('FIELD_CENSUS_CLANG', 'clang')
CLANG_ARGS = ['--target=mipsel-unknown-none', '-fsyntax-only', '-w', '-ferror-limit=0', '-Wno-everything']

SCALAR_SIZE = {
    'char': 1, 'signed char': 1, 'unsigned char': 1, '_Bool': 1,
    'short': 2, 'unsigned short': 2, 'short int': 2, 'unsigned short int': 2,
    'int': 4, 'unsigned int': 4, 'long': 4, 'unsigned long': 4, 'float': 4, 'unsigned': 4,
    'long int': 4, 'unsigned long int': 4,
    'long long': 8, 'unsigned long long': 8, 'double': 8, 'long double': 8,
}
UNNAMED = re.compile(r'\(unnamed (?:struct |union |enum )?at ([^)]*)\)')
STRONG_HOMES = ('include/shared/', 'include/common.h', 'include/game.h', 'include/globals.h')
PSYQ_NAME = re.compile(r'^(?:SVECTOR|VECTOR|MATRIX|CVECTOR|DVECTOR|RECT|SPRT(?:_8|_16)?|TILE(?:_1|_8|_16)?|POLY_[FG][T]?[34]|LINE_[FG][234]|DR_[A-Z]+|P_TAG|TIM_IMAGE)$')
WEAK_NAME = re.compile(r'(?:^|_)S_[0-9A-Fa-f]{6,8}|(?<!^Game)View$|^Rec_|^@|_pre$')
MAX_STEP = 0x4000   # larger constants are address arithmetic, not a field offset
UNK_FIELD = re.compile(r'^unk_?[0-9A-Fa-f]+$')
CONST_ADDR = re.compile(r'^(?:D|g)_[0-9A-F]{8}$')


# --------------------------------------------------------------------------- clang front end

def clang_run(root, rel, extra):
    cmd = [CLANG, *CLANG_ARGS, '-I', 'include', *extra, rel]
    res = subprocess.run(cmd, cwd=root, capture_output=True)
    return res.returncode, res.stdout.decode('utf-8', 'replace'), res.stderr.decode('utf-8', 'replace')


def record_key(text):
    """'struct X' / 'union X' / unnamed spellings -> stable record key."""
    text = text.strip()
    for kw in ('const ', 'volatile '):
        text = text.replace(kw, '')
    m = UNNAMED.search(text)
    if m:
        return '@' + m.group(1)
    for kw in ('struct ', 'union ', 'enum '):
        if text.startswith(kw):
            return text[len(kw):].strip()
    return text


LAYOUT_LINE = re.compile(r'^\s*(\d+)(?::(\d+)-(\d+))? \| (\s*)(.*)$')
SIZE_LINE = re.compile(r'\[sizeof=(\d+), (?:dsize=\d+, )?align=(\d+)')


def parse_layouts(text):
    """clang -fdump-record-layouts-complete -> {key: {'size', 'align', 'kind', 'fields': {name: (off, type)}}}."""
    out = {}
    for block in text.split('*** Dumping AST Record Layout')[1:]:
        lines = [l for l in block.splitlines() if l.strip()]
        if not lines:
            continue
        m = LAYOUT_LINE.match(lines[0])
        if not m:
            continue
        base = len(m.group(4))
        head = m.group(5)
        kind = head.split(' ', 1)[0]
        key = record_key(head.split('::')[-1] if '::(' in head else head)
        rec = {'kind': kind, 'fields': {}, 'order': []}
        for line in lines[1:]:
            s = SIZE_LINE.search(line)
            if s:
                rec['size'], rec['align'] = int(s.group(1)), int(s.group(2))
                continue
            m = LAYOUT_LINE.match(line)
            if not m or len(m.group(4)) != base + 2:
                continue
            body = m.group(5).rstrip()
            name = body.rsplit(' ', 1)[-1] if ' ' in body else ''
            ftype = body[:len(body) - len(name)].strip()
            off = int(m.group(1))
            if name and name not in rec['fields']:
                rec['fields'][name] = (off, ftype)
                rec['order'].append(name)
        out.setdefault(key, rec)
    return out


def annotate(tree):
    """Give every AST node its expansion file/line ('_f', '_l') and a macro flag ('_m').

    Clang's JSON omits file/line when unchanged from the previously *printed* location, so locations are
    replayed in document order over the whole dump."""
    state = {'file': None, 'line': None}

    def loc(d):
        if not isinstance(d, dict):
            return False
        if 'spellingLoc' in d:
            loc(d['spellingLoc'])
            loc(d['expansionLoc'])
            return True
        if 'offset' in d:
            if d.get('file'):
                state['file'] = d['file']
            if d.get('line'):
                state['line'] = d['line']
            d['_f'], d['_l'] = state['file'], state['line']
        return False

    stack = [tree]
    while stack:
        x = stack.pop()
        if isinstance(x, list):
            stack.extend(reversed(x))
            continue
        if not isinstance(x, dict):
            continue
        rest = []
        if 'kind' in x:
            loc(x.get('loc'))
            if 'loc' in x and x['loc']:
                x['_f'] = state['file']
                x['_l'] = state['line']
            rng = x.get('range')
            if rng:
                macro = loc(rng.get('begin'))
                if 'loc' not in x or not x['loc']:
                    x['_f'], x['_l'] = state['file'], state['line']
                if macro:
                    x['_m'] = rng['begin']['expansionLoc'].get('offset')
                loc(rng.get('end'))
            for k, v in x.items():
                if k in ('loc', 'range') or not isinstance(v, (dict, list)):
                    continue
                rest.append(v)
        else:
            for v in x.values():
                if isinstance(v, (dict, list)):
                    rest.append(v)
        stack.extend(reversed(rest))


# --------------------------------------------------------------------------- types

class Types:
    def __init__(self, typedefs, layouts, record_files):
        self.typedefs = typedefs
        self.layouts = layouts
        self.record_files = record_files

    def resolve(self, t, depth=0):
        """Canonical spelling: typedefs expanded at the top level and through pointer bases."""
        t = (t or '').strip()
        for q in ('const ', 'volatile '):
            t = t.replace(q, '')
        t = re.sub(r'\s+', ' ', t).replace(' *', '*').replace('* ', '*').strip()
        if depth > 20:
            return t
        if '(*)' in t or '(*' in t:
            return 'fnptr*'
        if t.endswith('*'):
            return self.resolve(t[:-1], depth + 1) + '*'
        m = re.match(r'^(.*)\[(\d*)\]$', t)
        if m:
            return self.resolve(m.group(1), depth + 1) + '[' + m.group(2) + ']'
        if t in self.typedefs:
            return self.resolve(self.typedefs[t], depth + 1)
        if t.startswith(('struct ', 'union ', 'enum ')) or '(unnamed' in t:
            k = record_key(t)
            if t.startswith('enum '):
                return 'enum'
            return 'rec:' + k
        return t

    def size(self, t):
        r = self.resolve(t)
        if r.endswith('*'):
            return 4
        m = re.match(r'^(.*)\[(\d*)\]$', r)
        if m:
            inner = self.size(m.group(1))
            return inner * int(m.group(2)) if inner and m.group(2) else None
        if r == 'enum':
            return 4
        if r.startswith('rec:'):
            lay = self.layouts.get(r[4:])
            return lay.get('size') if lay else None
        return SCALAR_SIZE.get(r)

    def sign(self, t):
        r = self.resolve(t)
        if r.endswith('*'):
            return 'p'
        if r.startswith('rec:') or '[' in r:
            return 'r'
        if r in ('float', 'double'):
            return 'f'
        if r.startswith('unsigned') or r == '_Bool':
            return 'u'
        return 's'

    def pointee(self, t):
        r = self.resolve(t)
        return r[:-1] if r.endswith('*') else None

    def record(self, t):
        """Record key of a struct type or pointer-to-struct type, else None."""
        r = self.resolve(t)
        r = r[:-1] if r.endswith('*') else r
        return r[4:] if r.startswith('rec:') else None

    def type_identity(self, key):
        """(identity, strong).  Strong = a shared game type (include/shared, common.h, game.h, globals.h) or a
        PsyQ SDK type; everything else (module headers, file-local S_/Row_/View typedefs) is a weak view keyed
        by file:name."""
        f = self.record_files.get(key, '')
        if key.startswith('@'):
            return key, False
        if PSYQ_NAME.match(key):
            return key, True
        if f.startswith(STRONG_HOMES) and not WEAK_NAME.search(key):
            return key, True
        return (f + ':' + key) if f else key, False

    def strong_meta(self):
        """size and record-typed members of every strong type laid out in this TU (for nesting checks)."""
        meta = {}
        for key, lay in self.layouts.items():
            ident, strong = self.type_identity(key)
            if not strong or 'size' not in lay:
                continue
            nest = []
            for name in lay['order']:
                off, ftype = lay['fields'][name]
                base = re.sub(r'\[\d*\]$', '', ftype.strip())
                rec = self.record(base) if not base.endswith('*') else None
                if rec:
                    inner, istrong = self.type_identity(rec)
                    if istrong:
                        n = 1
                        m = re.search(r'\[(\d+)\]$', ftype.strip())
                        size = self.size(base) or 0
                        if m and size:
                            n = int(m.group(1))
                        for i in range(min(n, 64)):
                            nest.append((off + i * size, inner))
            meta[ident] = {'size': lay['size'], 'nest': nest}
        return meta


def qtype(node):
    t = node.get('type') or {}
    return t.get('qualType', '')


def strip(e, casts=True):
    """Remove parens (and implicit casts) around an expression."""
    while e and e.get('kind') in ('ParenExpr', 'ImplicitCastExpr') + (('CStyleCastExpr',) if casts else ()):
        if not e.get('inner'):
            break
        e = e['inner'][0]
    return e


def int_value(e):
    e = strip(e)
    if not e:
        return None
    if e.get('kind') == 'IntegerLiteral':
        return int(e['value'])
    if e.get('kind') == 'UnaryOperator' and e.get('opcode') in ('-', '+'):
        v = int_value(e['inner'][0])
        return None if v is None else (-v if e['opcode'] == '-' else v)
    if e.get('kind') == 'CharacterLiteral':
        return int(e['value'])
    return None


def expr_text(e, depth=0):
    """Compact readable spelling of a base expression (for reports only)."""
    if not e or depth > 6:
        return '?'
    k = e.get('kind')
    if k in ('ParenExpr', 'ImplicitCastExpr'):
        return expr_text(e['inner'][0], depth)
    if k == 'CStyleCastExpr':
        return expr_text(e['inner'][0], depth)
    if k == 'DeclRefExpr':
        return e['referencedDecl'].get('name', '?')
    if k == 'MemberExpr':
        return expr_text(e['inner'][0], depth + 1) + ('->' if e.get('isArrow') else '.') + e.get('name', '')
    if k == 'IntegerLiteral':
        return hex(int(e['value'])) if int(e['value']) > 9 else e['value']
    if k == 'BinaryOperator':
        return expr_text(e['inner'][0], depth + 1) + ' ' + e['opcode'] + ' ' + expr_text(e['inner'][1], depth + 1)
    if k == 'UnaryOperator':
        inner = expr_text(e['inner'][0], depth + 1)
        return (inner + e['opcode']) if e.get('isPostfix') else (e['opcode'] + inner)
    if k == 'ArraySubscriptExpr':
        return expr_text(e['inner'][0], depth + 1) + '[' + expr_text(e['inner'][1], depth + 1) + ']'
    if k == 'CallExpr':
        return expr_text(e['inner'][0], depth + 1) + '()'
    return k


# --------------------------------------------------------------------------- per-function extraction

class FunctionFacts:
    """Walk one function body; emit unify edges, type attachments and sites with symbolic node names.

    Node names: v:<file>:<func>:<var>:<id> pointer local, p:<func>:<i> parameter, r:<func> return value,
    g:<name> global object, o:... local aggregate object, t:<type> type object.  A field pointee is the tuple
    ('F', node, offset): the object the pointer stored at node+offset points to."""

    def __init__(self, types, fn, file, src_text, globals_):
        self.T = types
        self.fn = fn
        self.name = fn['name']
        self.file = file
        self.src = src_text
        self.globals = globals_
        self.locals = {}
        self.edges = []      # (a, b, delta, phase, key)
        self.results = set()
        self.attach = []     # (node, delta, identity, strong)
        self.sites = []
        params = [x for x in fn.get('inner', []) if x.get('kind') == 'ParmVarDecl']
        for i, p in enumerate(params):
            node = 'p:%s:%d' % (self.name, i)
            self.locals[p['id']] = ('ptr', node)
            self.type_var(node, qtype(p))

    # -- names
    def var_node(self, decl):
        did = decl.get('id')
        if did in self.locals:
            return self.locals[did]
        if did in self.globals:
            return ('glob', self.globals[did])
        return None

    def type_var(self, node, t):
        rec = self.T.record(t)
        if rec and self.T.pointee(t):
            ident, strong = self.T.type_identity(rec)
            self.attach.append((node, 0, ident, strong))

    def type_obj(self, node, t):
        rec = self.T.record(t)
        if rec and not self.T.pointee(t):
            ident, strong = self.T.type_identity(rec)
            self.attach.append((node, 0, ident, strong))

    # -- address of an lvalue: (node, delta) or None
    def addr(self, e):
        e = strip(e, casts=False)
        if not e:
            return None
        k = e.get('kind')
        if k == 'DeclRefExpr':
            ref = e['referencedDecl']
            vn = self.var_node(ref)
            if vn is None:
                return None
            if vn[0] == 'glob':
                return (vn[1], 0)
            if vn[0] == 'obj':
                return (vn[1], 0)
            return None  # address of a pointer local: not modelled
        if k == 'MemberExpr':
            base = e['inner'][0]
            off = self.member_offset(e)
            if off is None:
                return None
            b = self.value(base) if e.get('isArrow') else self.addr(base)
            if b is None:
                return None
            return (b[0], b[1] + off)
        if k == 'UnaryOperator' and e.get('opcode') == '*':
            return self.value(e['inner'][0])
        if k == 'ArraySubscriptExpr':
            base, idx = e['inner']
            i = int_value(idx)
            size = self.T.size(qtype(e))
            if i is None or size is None:
                return None
            b = self.value(base)
            if b is None:
                return None
            return (b[0], b[1] + i * size)
        return None

    def member_offset(self, e):
        base = e['inner'][0]
        rec = self.T.record(qtype(base))
        if rec is None:
            return None
        lay = self.T.layouts.get(rec)
        if not lay:
            return None
        f = lay['fields'].get(e.get('name'))
        return f[0] if f else None

    # -- value of a pointer-ish rvalue: (node, delta) or None
    def value(self, e):
        if not e:
            return None
        k = e.get('kind')
        if k == 'ParenExpr':
            return self.value(e['inner'][0])
        if k in ('CStyleCastExpr', 'ImplicitCastExpr'):
            ck = e.get('castKind')
            sub = e['inner'][0]
            if ck in ('ArrayToPointerDecay', 'FunctionToPointerDecay'):
                return self.addr(sub)
            if ck == 'LValueToRValue':
                return self.load(sub)
            v = self.value(sub)
            if v is not None and k == 'CStyleCastExpr':
                # an explicit cast to a record pointer is the code's own view of the object
                rec = self.T.record(qtype(e))
                if rec and self.T.pointee(qtype(e)):
                    ident, strong = self.T.type_identity(rec)
                    self.attach.append((v[0], v[1], ident, strong))
            return v
        if k == 'UnaryOperator':
            op = e.get('opcode')
            if op == '&':
                return self.addr(e['inner'][0])
            if op in ('++', '--'):
                return self.load(e['inner'][0])
            return None
        if k == 'BinaryOperator':
            op = e.get('opcode')
            a, b = e['inner']
            if op == '=':
                return self.value(b)
            if op == ',':
                return self.value(b)
            if op in ('+', '-'):
                ia, ib = int_value(a), int_value(b)
                if ib is not None and ia is None:
                    ptr, n = a, ib
                elif ia is not None and ib is None and op == '+':
                    ptr, n = b, ia
                else:
                    return None
                v = self.value(ptr)
                if v is None:
                    return None
                pt = self.T.pointee(qtype(ptr))
                scale = 1
                if pt is not None:
                    scale = self.T.size(pt) or 1
                step = (n if op == '+' else -n) * scale
                if abs(step) > MAX_STEP:
                    return None
                return (v[0], v[1] + step)
            return None
        if k == 'ConditionalOperator':
            x, y = self.value(e['inner'][1]), self.value(e['inner'][2])
            if x and y:
                self.edges.append((x[0], y[0], x[1] - y[1], 1, None))
            return x or y
        if k == 'CallExpr':
            callee = strip(e['inner'][0])
            if callee and callee.get('kind') == 'DeclRefExpr' and callee['referencedDecl'].get('kind') == 'FunctionDecl':
                node = 'c:%s:%s:%s' % (self.file, self.name, e.get('id'))
                if node not in self.results:
                    self.results.add(node)
                    self.edges.append((node, 'r:' + callee['referencedDecl']['name'], 0, 3, None))
                    self.type_var(node, qtype(e))
                return (node, 0)
            return None
        if k == 'DeclRefExpr':
            ref = e['referencedDecl']
            if ref.get('kind') == 'FunctionDecl':
                return None
            return self.load(e)
        if k in ('MemberExpr', 'ArraySubscriptExpr'):
            return self.load(e)
        return None

    def load(self, lv):
        """Value loaded from lvalue lv when it can hold a pointer (pointer or 4-byte integer)."""
        t = qtype(lv)
        size = self.T.size(t)
        ptrish = self.T.pointee(t) is not None or self.T.resolve(t).endswith('[]')
        if not ptrish and size != 4:
            return None
        s = strip(lv, casts=False)
        if s and s.get('kind') == 'DeclRefExpr':
            vn = self.var_node(s['referencedDecl'])
            if vn is None:
                return None
            if vn[0] == 'ptr':
                return (vn[1], 0)
            if vn[0] == 'glob':
                return (('F', vn[1], 0), 0)
            return None
        a = self.addr(lv)
        if a is None:
            return None
        return (('F', a[0], a[1]), 0)

    # -- statements and sites
    def assign_to(self, lhs, val):
        if val is None:
            return
        s = strip(lhs, casts=False)
        if s and s.get('kind') == 'DeclRefExpr':
            vn = self.var_node(s['referencedDecl'])
            if vn and vn[0] == 'ptr':
                self.edges.append((vn[1], val[0], val[1], 1, None))
            elif vn and vn[0] == 'glob':
                self.edges.append((('F', vn[1], 0), val[0], val[1], 1, None))
            return
        a = self.addr(lhs)
        if a is not None:
            self.edges.append((('F', a[0], a[1]), val[0], val[1], 1, None))

    def site(self, e, rw, const=None):
        """Record e as an access site when it is a constant-offset access through a base."""
        k = e.get('kind')
        spell = None
        field = None
        decl_type = None
        base_expr = None
        off_local = None
        if k == 'MemberExpr':
            base_expr = e['inner'][0]
            off_local = self.member_offset(e)
            field = e.get('name')
            rec = self.T.record(qtype(base_expr))
            ident, strong = self.T.type_identity(rec) if rec else (None, False)
            decl_type = ident
            if rec is None:
                spell = 'member_named'
            elif not strong:
                spell = 'member_view'
            elif UNK_FIELD.match(field or ''):
                spell = 'member_unk'
            else:
                spell = 'member_named'
        elif k == 'UnaryOperator':
            sub = strip(e['inner'][0], casts=False)
            if sub is None or sub.get('kind') != 'CStyleCastExpr':
                return
            spell = 'raw_cast'
            base_expr = sub
        elif k == 'ArraySubscriptExpr':
            base = strip(e['inner'][0], casts=False)
            idx = int_value(e['inner'][1])
            if base is None or idx is None:
                return
            if base.get('kind') == 'MemberExpr':
                # constant element of an array field: p->arr[2]
                base_expr = base['inner'][0]
                field = '%s[%d]' % (base.get('name'), idx)
                rec = self.T.record(qtype(base_expr))
                ident, strong = self.T.type_identity(rec) if rec else (None, False)
                decl_type = ident
                spell = 'member_named' if rec is None else ('member_view' if not strong else (
                    'member_unk' if UNK_FIELD.match(base.get('name') or '') else 'member_named'))
                e = dict(e, isArrow=base.get('isArrow'))
            elif base.get('kind') != 'CStyleCastExpr':
                return
            else:
                spell = 'raw_index'
                base_expr = base
        else:
            return
        a = self.addr(e)
        if e.get('_m') is not None and spell.startswith('raw'):
            text = self.src[e['_m']:e['_m'] + 3] if self.src else ''
            spell = 'F_macro' if re.match(r'F\s*\(', text) else 'macro'
        if spell.startswith('raw') or spell in ('F_macro', 'macro'):
            # base: the innermost uncast pointer expression
            inner = strip(base_expr)
            if inner and inner.get('kind') == 'BinaryOperator' and inner.get('opcode') in ('+', '-'):
                x, y = inner['inner']
                inner = strip(x) if int_value(y) is not None else strip(y)
            base_text = expr_text(inner)
            decl_type = self.T.resolve(qtype(inner)) if inner else None
            chain = self._is_load(inner)
        else:
            base_text = expr_text(base_expr)
            chain = self._is_load(strip(base_expr)) if e.get('isArrow') else False
        t = qtype(e)
        rec = {
            'file': self.file, 'func': self.name, 'line': e.get('_l'), 'spell': spell,
            'base': base_text, 'node': a[0] if a else None, 'delta': a[1] if a else None,
            'width': self.T.size(t), 'sign': self.T.sign(t), 'ctype': t, 'rw': rw,
            'field': field, 'decl': decl_type, 'chain': bool(chain),
        }
        if const is not None:
            rec['const'] = const
        self.sites.append(rec)

    def _is_load(self, e):
        """True when the base pointer was itself loaded from memory (a pointer chain)."""
        e = strip(e)
        if e is None:
            return False
        k = e.get('kind')
        return k in ('MemberExpr', 'ArraySubscriptExpr') or (k == 'UnaryOperator' and e.get('opcode') == '*')

    def is_leaf(self, e, parent):
        """A member/deref lvalue is a site unless it is only the base of a further dot/array access."""
        if parent is None:
            return True
        pk = parent.get('kind')
        if pk == 'MemberExpr' and not parent.get('isArrow'):
            return False
        if pk == 'ArraySubscriptExpr' and parent['inner'][0] is e:
            return False
        return True

    def walk(self):
        body = [x for x in self.fn.get('inner', []) if x.get('kind') == 'CompoundStmt']
        stack = [(b, None, 'r') for b in body]
        while stack:
            e, parent, ctx = stack.pop()
            if not isinstance(e, dict):
                continue
            k = e.get('kind')
            kids = e.get('inner') or []
            child_ctx = ['r'] * len(kids)
            if k == 'VarDecl':
                st = e.get('storageClass')
                if st in ('extern', 'static'):
                    gname = e['name'] if st == 'extern' else '%s:%s:%s' % (self.file, self.name, e['name'])
                    self.globals[e['id']] = 'g:' + gname
                    self.type_obj('g:' + gname, qtype(e))
                    if self.T.pointee(qtype(e)):
                        self.type_var(('F', 'g:' + gname, 0), qtype(e))
                else:
                    t = qtype(e)
                    r = self.T.resolve(t)
                    if r.endswith('*') or self.T.size(t) == 4:
                        node = 'v:%s:%s:%s:%s' % (self.file, self.name, e['name'], e['id'])
                        self.locals[e['id']] = ('ptr', node)
                        self.type_var(node, t)
                    else:
                        node = 'o:%s:%s:%s:%s' % (self.file, self.name, e['name'], e['id'])
                        self.locals[e['id']] = ('obj', node)
                        self.type_obj(node, t)
                    if e.get('init') and kids:
                        val = self.value(kids[0])
                        if val is not None and self.locals[e['id']][0] == 'ptr':
                            self.edges.append((node, val[0], val[1], 1, None))
            elif k == 'BinaryOperator' and e.get('opcode') == '=':
                self.assign_to(kids[0], self.value(kids[1]))
                child_ctx = ['w', 'r']
                c = int_value(kids[1])
                if c is not None:
                    e['_const'] = c
            elif k == 'CompoundAssignOperator':
                child_ctx = ['rw', 'r']
                lhs = strip(kids[0], casts=False)
                if lhs and lhs.get('kind') == 'DeclRefExpr' and self.T.pointee(qtype(lhs)):
                    v = self.var_node(lhs['referencedDecl'])
                    n = int_value(kids[1])
                    if v and v[0] == 'ptr' and n is not None and e.get('opcode') in ('+=', '-='):
                        scale = self.T.size(self.T.pointee(qtype(lhs))) or 1
                        self.edges.append((v[1], v[1], (n if e['opcode'] == '+=' else -n) * scale, 1, 'walk'))
            elif k == 'UnaryOperator' and e.get('opcode') in ('++', '--'):
                child_ctx = ['rw']
            elif k == 'UnaryOperator' and e.get('opcode') == '&':
                child_ctx = ['addr']
            elif k == 'CallExpr':
                callee = strip(kids[0]) if kids else None
                if callee and callee.get('kind') == 'DeclRefExpr' and callee['referencedDecl'].get('kind') == 'FunctionDecl':
                    fname = callee['referencedDecl']['name']
                    for i, arg in enumerate(kids[1:]):
                        val = self.value(arg)
                        if val is None:
                            continue
                        # the implicit conversion at the argument is the prototype's parameter type
                        if arg.get('kind') == 'ImplicitCastExpr':
                            rec = self.T.record(qtype(arg))
                            if rec and self.T.pointee(qtype(arg)):
                                ident, strong = self.T.type_identity(rec)
                                self.attach.append((val[0], val[1], ident, strong))
                        self.edges.append(('p:%s:%d' % (fname, i), val[0], val[1], 2, 'p:%s:%d' % (fname, i)))
            elif k == 'ReturnStmt' and kids:
                val = self.value(kids[0])
                if val is not None:
                    self.edges.append(('r:' + self.name, val[0], val[1], 2, 'r:' + self.name))
            elif k == 'ImplicitCastExpr' and e.get('castKind') == 'LValueToRValue':
                child_ctx = ['r']
            elif k == 'MemberExpr' and not e.get('isArrow'):
                child_ctx = ['base']
            elif k == 'ArraySubscriptExpr':
                child_ctx = ['base', 'r']
            elif k in ('ParenExpr',):
                child_ctx = [ctx]
            # sites
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
            for kid, c in reversed(list(zip(kids, child_ctx))):
                stack.append((kid, e, c))


def extract_tu(args):
    """Worker: one physical TU -> {'functions': {(file, func): facts}, 'error': ...}."""
    root, rel = args
    rc, out, err = clang_run(root, rel, ['-Xclang', '-ast-dump=json'])
    if not out.strip():
        return {'tu': rel, 'error': (err.strip().splitlines() or ['no output'])[-1][:300], 'functions': []}
    try:
        tree = json.loads(out)
    except ValueError as exc:
        return {'tu': rel, 'error': 'json: %s' % exc, 'functions': []}
    _, lay_text, _ = clang_run(root, rel, ['-Xclang', '-fdump-record-layouts-complete'])
    layouts = parse_layouts(lay_text)
    annotate(tree)
    typedefs, record_files, globals_ = {}, {}, {}
    anon = {}
    for d in tree.get('inner', []):
        k = d.get('kind')
        if k == 'TypedefDecl':
            typedefs[d['name']] = qtype(d)
            inner = (d.get('inner') or [{}])[0]
            owned = inner.get('ownedTagDecl')
            if owned and not owned.get('name') and owned.get('id') in anon:
                key = anon[owned['id']]
                if key in layouts:
                    layouts.setdefault(d['name'], layouts[key])
                    record_files.setdefault(d['name'], key[1:].split(':')[0])
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
    # anonymous records keyed by their location already carry the file
    for key in layouts:
        if key.startswith('@'):
            record_files.setdefault(key, key[1:].split(':')[0])
    types = Types(typedefs, layouts, record_files)
    gfacts = []
    for d in tree.get('inner', []):
        if d.get('kind') == 'VarDecl':
            node = globals_[d['id']]
            t = qtype(d)
            rec = types.record(t)
            if rec:
                ident, strong = types.type_identity(rec)
                if types.pointee(t):
                    gfacts.append((('F', node, 0), 0, ident, strong))
                else:
                    gfacts.append((node, 0, ident, strong))
    texts = {}
    funcs = []
    for d in tree.get('inner', []):
        if d.get('kind') != 'FunctionDecl' or not any(x.get('kind') == 'CompoundStmt' for x in d.get('inner', [])):
            continue
        f = d.get('_f') or rel
        if f not in texts:
            try:
                texts[f] = (Path(root) / f).read_text(errors='replace')
            except OSError:
                texts[f] = ''
        ff = FunctionFacts(types, d, f, texts[f], globals_)
        ff.walk()
        funcs.append({'file': f, 'func': d['name'], 'edges': ff.edges, 'attach': ff.attach, 'sites': ff.sites})
    return {'tu': rel, 'error': None if rc == 0 else (err.strip().splitlines() or [''])[-1][:300],
            'functions': funcs, 'globals': gfacts, 'meta': types.strong_meta()}


# --------------------------------------------------------------------------- union-find with offsets

class Solver:
    def __init__(self):
        self.ids = {}
        self.parent = []
        self.off = []         # node location = parent location + off
        self.fields = []      # root -> {offset: node}
        self.types = []       # root -> {delta: (identity, strong)}
        self.views = []       # root -> {delta: set(identity)}
        self.origin = []      # node -> (kind, info) provenance for labels
        self.refused = collections.Counter()
        self.unstable = set()
        self.meta = {}

    def node(self, name):
        if isinstance(name, tuple):
            _, base, off = name
            b = self.node(base)
            r, o = self.find(b)
            return self.field(r, o + off)
        n = self.ids.get(name)
        if n is None:
            n = self._new(('name', name))
            self.ids[name] = n
        return n

    def _new(self, origin):
        n = len(self.parent)
        self.parent.append(n)
        self.off.append(0)
        self.fields.append(None)
        self.types.append(None)
        self.views.append(None)
        self.origin.append(origin)
        return n

    def field(self, root, off):
        fm = self.fields[root]
        if fm is None:
            fm = self.fields[root] = {}
        n = fm.get(off)
        if n is None:
            n = self._new(('field', root, off))
            fm[off] = n
        return n

    def find(self, n):
        path = []
        while self.parent[n] != n:
            path.append(n)
            n = self.parent[n]
        root = n
        total = 0
        for x in reversed(path):
            total += self.off[x]
            self.off[x] = total
            self.parent[x] = root
        # recompute: off[x] must be relative to root; walk again from leaf side
        return (root, 0) if not path else (root, self.off[path[0]])

    def find_off(self, n):
        r, o = self.find(n)
        return r, (o if n != r else 0)

    def nested(self, outer, inner, rel, depth=0):
        """Is strong type `inner` a (transitively) nested member of `outer` at offset rel?"""
        if outer == inner and rel == 0:
            return True
        if depth > 4:
            return False
        for off, t in self.meta.get(outer, {}).get('nest', ()):
            size = self.meta.get(t, {}).get('size', 0)
            if off <= rel < off + max(size, 1) and self.nested(t, inner, rel - off, depth + 1):
                return True
        return False

    def compatible(self, t, dt, u, du):
        """Strong types t at dt and u at du may share one object: disjoint, or one nested in the other."""
        st = self.meta.get(t, {}).get('size', 4)
        su = self.meta.get(u, {}).get('size', 4)
        if t == u and dt != du:
            return False        # one object holding the same shared type twice = two objects conflated
        if dt + st <= du or du + su <= dt:
            return True
        if t == u:
            return dt == du
        return self.nested(t, u, du - dt) or self.nested(u, t, dt - du)

    def type_conflict(self, ra, rb, delta):
        """Would putting rb's strong types at +delta inside ra clash with ra's?"""
        ta = [(d, t[0]) for d, t in (self.types[ra] or {}).items() if t[1]]
        if not ta:
            return False
        for d, t in (self.types[rb] or {}).items():
            if not t[1]:
                continue
            for da, u in ta:
                if not self.compatible(t[0], d + delta, u, da):
                    return True
        return False

    def union(self, a, b, delta, guard=True):
        """Constrain loc(a) = loc(b) + delta.  Returns False when refused."""
        work = [(a, b, delta, guard)]
        ok = True
        first = True
        while work:
            a, b, delta, g = work.pop()
            ra, oa = self.find_off(a)
            rb, ob = self.find_off(b)
            # loc(a) = loc(ra)+oa ; loc(b) = loc(rb)+ob ; want loc(ra) = loc(rb) + ob + delta - oa
            d = ob + delta - oa
            if ra == rb:
                if d != 0:
                    self.unstable.add(ra)
                    self.refused['offset_inconsistent'] += 1
                    if first:
                        ok = False
                first = False
                continue
            # attach ra under rb at offset d  (loc(ra) = loc(rb) + d)
            if self.type_conflict(rb, ra, d):
                self.refused['strong_type_conflict' if first else 'strong_type_conflict_cascade'] += 1
                if first:
                    ok = False
                first = False
                continue
            first = False
            if len(self.fields[ra] or {}) > len(self.fields[rb] or {}):
                # keep the bigger field map as the root: attach rb under ra at -d
                ra, rb, d = rb, ra, -d
            self.parent[ra] = rb
            self.off[ra] = d
            for dd, t in (self.types[ra] or {}).items():
                tb = self.types[rb] = self.types[rb] or {}
                if dd + d not in tb or (t[1] and not tb[dd + d][1]):
                    tb[dd + d] = t
            for dd, vs in (self.views[ra] or {}).items():
                vb = self.views[rb] = self.views[rb] or {}
                vb.setdefault(dd + d, set()).update(vs)
            if ra in self.unstable:
                self.unstable.add(rb)
            fa = self.fields[ra] or {}
            self.fields[ra] = None
            fb = self.fields[rb] = self.fields[rb] or {}
            for off, fn in fa.items():
                if off + d in fb:
                    work.append((fn, fb[off + d], 0, True))
                else:
                    fb[off + d] = fn
            self.types[ra] = None
            self.views[ra] = None
        return ok

    def attach_type(self, n, delta, ident, strong):
        r, o = self.find_off(n)
        at = o + delta
        if strong:
            tm = self.types[r] = self.types[r] or {}
            for d, t in tm.items():
                if t[1] and not self.compatible(ident, at, t[0], d):
                    self.refused['strong_type_attach_conflict'] += 1
                    return False
            tm[at] = (ident, True)
        else:
            vm = self.views[r] = self.views[r] or {}
            vm.setdefault(at, set()).add(ident)
        return True

    def strong_at(self, r):
        return {d: t[0] for d, t in (self.types[r] or {}).items() if t[1]}


# --------------------------------------------------------------------------- driver

def physical_tus(root):
    sys.path.insert(0, str(Path(root) / 'tools'))
    import layout_compile_identity as L
    physical, members = L.recipes(root)
    return sorted(physical), sorted(members)


def solve(results):
    """Phase 1 unifies within functions (and through globals, which are single objects); phase 2 propagates
    types and anchor labels across calls in rounds *without* unifying callers (an allocator or a node-taking
    helper would otherwise fuse every object kind into one class)."""
    S = Solver()
    seen = set()
    funcs = []
    for res in results:
        for ident, m in (res.get('meta') or {}).items():
            S.meta.setdefault(ident, m)
    for res in results:
        for g in res.get('globals', []):
            S.attach_type(S.node(g[0]), g[1], g[2], g[3])
        for f in res['functions']:
            key = (f['file'], f['func'])
            if key in seen:
                continue
            seen.add(key)
            funcs.append(f)
    # a function name defined in several files (statics, bank copies) gets private parameter/return
    # nodes; calls to it carry no edges (the callee is ambiguous)
    defs = collections.Counter(f['func'] for f in funcs)
    dup = {n for n, c in defs.items() if c > 1}
    S.refused['ambiguous_function_names'] = len(dup)

    def rename(x, f):
        if isinstance(x, tuple):
            return (x[0], rename(x[1], f), x[2])
        if isinstance(x, str) and f['func'] in dup:
            for pre in ('p:%s:' % f['func'], 'r:%s' % f['func']):
                if x.startswith(pre) and (pre[0] == 'p' or x == pre):
                    return x[:2] + f['file'] + '@' + x[2:]
        return x
    for f in funcs:
        if f['func'] in dup:
            f['attach'] = [(rename(n, f), d, i, st) for n, d, i, st in f['attach']]
            f['sites'] = [dict(s_, node=rename(s_['node'], f)) for s_ in f['sites']]
        edges = []
        for a, b, d, phase, tag in f['edges']:
            if phase == 2 and tag:
                callee = tag.split(':')[1]
                if callee in dup:
                    if tag.startswith('r:') and callee == f['func']:
                        tag = a = rename(a, f)          # this definition's own return statements
                    else:
                        continue
            if phase == 3 and b.startswith('r:') and b[2:] in dup:
                continue
            edges.append((rename(a, f) if phase == 1 else a, rename(b, f), d, phase, tag))
        f['edges'] = edges
    for f in funcs:
        for node, delta, ident, strong in f['attach']:
            S.attach_type(S.node(node), delta, ident, strong)
    for f in funcs:
        for a, b, d, phase, tag in f['edges']:
            if phase == 1:
                ok = S.union(S.node(a), S.node(b), d)
                if not ok and tag == 'walk':
                    S.refused['walking_pointer'] += 1
    # materialize every site base now, so anchors see the field pointees sites use
    for f in funcs:
        for site in f['sites']:
            if site['node'] is not None:
                S.node(site['node'])
    calls = collections.defaultdict(list)
    for f in funcs:
        for a, b, d, phase, tag in f['edges']:
            if phase == 2:
                calls[tag].append((a, b, d))
    A = Anchors(S)
    for rnd in range(4):
        A.rebuild()
        changed = 0
        for slot, edges in calls.items():
            # parameter slot p:<f>:<i> (callers' arguments vote) or return slot r:<f> (return statements vote)
            votes = collections.Counter()
            for a, b, d in edges:
                lab = A.at_node(S.node(b), d)
                votes[lab if lab and lab[1] == 0 and not lab[0].startswith('anon') else None] += 1
            typed = {k: v for k, v in votes.items() if k}
            if len(typed) == 1:
                (lab, _), = typed
                changed += A.inherit(S.node(slot), lab)
            elif len(typed) > 1 and rnd == 0:
                S.refused['param_votes_disagree' if slot.startswith('p:') else 'return_votes_disagree'] += 1
        for f in funcs:
            for a, b, d, phase, tag in f['edges']:
                if phase == 3:      # (call-site result node, r:callee)
                    lab = A.at_node(S.node(b), 0)
                    if lab and lab[1] == 0 and not lab[0].startswith('anon'):
                        changed += A.inherit(S.node(a), lab[0])
        if not changed:
            break
    A.rebuild()
    return S, funcs, A


class Anchors:
    """Per class: the named points a site offset is measured from.

    strong   a shared type attached at an offset (EntityRec at 0, ObjectNodeHeader at -0x20)
    path     a field pointee of an anchored class: 'ObjectNodeHeader->[0xc]'
    inherit  a parameter/call result whose callers all agree on one anchor
    view     a weak (S_/View) type, only when nothing better exists"""

    def __init__(self, S):
        self.S = S
        self.inherited = {}     # node -> label
        self.cache = {}

    def inherit(self, node, label):
        if self.inherited.get(node) == label:
            return 0
        if node in self.inherited:
            self.S.refused['inherit_conflict'] += 1
            return 0
        self.inherited[node] = label
        if '->' not in label and not label.startswith('view:') and label in self.S.meta:
            self.S.attach_type(node, 0, label, True)
        return 1

    def rebuild(self):
        S = self.S
        self.members = collections.defaultdict(list)
        for n in range(len(S.parent)):
            self.members[S.find(n)[0]].append(n)
        self.cache = {}

    def anchors(self, r, depth=0):
        """[(class offset, label, size or None, rank)] for root r; rank 0 strong, 1 path/inherited, 2 view."""
        if r in self.cache:
            return self.cache[r]
        self.cache[r] = []
        S = self.S
        out = []
        for d, (t, strong) in (S.types[r] or {}).items():
            if strong:
                out.append((d, t, S.meta.get(t, {}).get('size'), 0))
        for n in self.members.get(r, ()):
            o = S.origin[n]
            _, off = S.find_off(n)
            if n in self.inherited:
                out.append((off, self.inherited[n], None, 1))
            if o[0] == 'field' and depth < 5:
                pr, po = S.find_off(o[1])
                lab = self.label_at(pr, po + o[2], depth + 1)
                if lab and not lab[0].startswith('anon'):
                    out.append((off, '%s->[%#x]' % (lab[0], lab[1]), None, 1))
        for d, vs in (S.views[r] or {}).items():
            out.append((d, 'view:' + sorted(vs)[0], None, 2))
        self.cache[r] = out
        return out

    def label_at(self, r, off, depth=0):
        """(label, offset relative to that label's origin) for class offset off in root r."""
        best = None
        for d, lab, size, rank in self.anchors(r, depth):
            rel = off - d
            inside = size is not None and 0 <= rel < size
            if rank == 0 and not inside and size is not None:
                key = (3, abs(rel), len(lab))
            elif rank == 0:
                key = (0, 0, len(lab))
            elif rank == 1:
                key = (1 if rel >= 0 else 2, abs(rel), len(lab))
            else:
                key = (4 if 0 <= rel < 0x400 else 5, abs(rel), len(lab))
            if best is None or key < best[0]:
                best = (key, lab, rel)
        if best is None:
            names = sorted(str(S_name) for S_name in self._names(r))
            return ('anon:' + (names[0] if names else str(r)), off)
        return (best[1], best[2])

    def _names(self, r):
        S = self.S
        out = []
        for n in self.members.get(r, ()):
            o = S.origin[n]
            if o[0] == 'name' and isinstance(o[1], str) and o[1].startswith(('p:', 'r:', 'g:')):
                out.append(o[1])
        return out

    def at_node(self, n, delta):
        r, o = self.S.find_off(n)
        return self.label_at(r, o + delta)


def run(root, out, tus=None, workers=4, limit=None):
    root = Path(root).resolve()
    out = Path(out)
    out.mkdir(parents=True, exist_ok=True)
    if tus is None:
        tus, _ = physical_tus(root)
    if limit:
        tus = tus[:limit]
    results = []
    errors = []
    with ProcessPoolExecutor(max_workers=workers) as ex:
        for res in ex.map(extract_tu, [(str(root), t) for t in tus], chunksize=8):
            results.append(res)
            if res.get('error'):
                errors.append((res['tu'], res['error']))
    S, funcs, A = solve(results)
    return report(S, funcs, A, errors, out, len(tus))


def classify(label):
    if label.startswith('anon:'):
        return 'untyped'
    if label.startswith('view:'):
        return 'view_only'
    if '->' in label:
        return 'derived'
    return 'strong'


def report(S, funcs, A, errors, out, n_tus):
    by_label = collections.defaultdict(list)
    spell = collections.Counter()
    cov = collections.Counter()
    with gzip.open(out / 'sites.jsonl.gz', 'wt') as fh:
        for f in funcs:
            for s in f['sites']:
                spell[s['spell']] += 1
                rec = {k: v for k, v in s.items() if k not in ('node', 'delta')}
                if s['node'] is None:
                    cov['no_base'] += 1
                    rec['typed'] = 'no_base'
                else:
                    r, o = S.find_off(S.node(s['node']))
                    lab, rel = A.label_at(r, o + s['delta'])
                    rec['label'], rec['off'] = lab, rel
                    rec['typed'] = classify(lab)
                    if r in S.unstable:
                        rec['unstable'] = True
                    cov[rec['typed']] += 1
                    by_label[lab].append(rec)
                fh.write(json.dumps(rec, separators=(',', ':')) + '\n')
    total = sum(spell.values())
    rows = []
    with open(out / 'layouts.jsonl', 'w') as fh:
        for lab, sites in sorted(by_label.items(), key=lambda kv: -len(kv[1])):
            fields = collections.defaultdict(lambda: {'uses': 0, 'widths': collections.Counter(), 'readers': set(),
                                                      'writers': set(), 'consts': collections.Counter(),
                                                      'names': collections.Counter(), 'funcs': set()})
            fns, files, sp, views = set(), set(), collections.Counter(), collections.Counter()
            for s in sites:
                fns.add((s['file'], s['func']))
                files.add(s['file'])
                sp[s['spell']] += 1
                if s['spell'] == 'member_view' and s.get('decl'):
                    views[s['decl']] += 1
                fd = fields[s['off']]
                fd['uses'] += 1
                fd['funcs'].add((s['file'], s['func']))
                fd['widths']['%s%s' % (s['sign'], s['width'])] += 1
                if s['rw'] in ('r', 'rw'):
                    fd['readers'].add((s['file'], s['func']))
                if s['rw'] in ('w', 'rw'):
                    fd['writers'].add((s['file'], s['func']))
                if 'const' in s:
                    fd['consts'][hex(s['const'])] += 1
                if s.get('field'):
                    fd['names'][s['field']] += 1
            row = {
                'label': lab, 'typed': classify(lab), 'sites': len(sites), 'functions': len(fns), 'files': len(files),
                'views': len(views), 'view_names': [v for v, _ in views.most_common(12)], 'spellings': dict(sp),
                'fields': {'%#x' % o: {
                    'uses': v['uses'], 'functions': len(v['funcs']), 'widths': dict(v['widths']),
                    'readers': len(v['readers']), 'writers': len(v['writers']),
                    'consts': dict(v['consts'].most_common(6)), 'names': dict(v['names'].most_common(4))}
                    for o, v in sorted(fields.items())},
            }
            rows.append(row)
            if len(sites) >= 3:
                fh.write(json.dumps(row, separators=(',', ':')) + '\n')
    with open(out / 'top_types.tsv', 'w') as fh:
        fh.write('rank\tbase_identity\ttyped\tsites\tfunctions\tfiles\toffsets\tS_views_merged\traw_cast\tF_macro\t'
                 'raw_index\tmember_unk\tmember_view\tmember_named\tother\ttop_view_types\n')
        for i, row in enumerate(rows[:30], 1):
            sp = row['spellings']
            named = ('raw_cast', 'F_macro', 'raw_index', 'member_unk', 'member_view', 'member_named')
            other = row['sites'] - sum(sp.get(k, 0) for k in named)
            fh.write('\t'.join(map(str, [i, row['label'], row['typed'], row['sites'], row['functions'], row['files'],
                                         len(row['fields']), row['views'], *[sp.get(k, 0) for k in named], other,
                                         ','.join(v.split(':')[-1] if not v.startswith('@') else 'anon' + v for v in row['view_names'][:4]) or '-'])) + '\n')
    summary = {
        'physical_tus': n_tus, 'tu_errors': len(errors), 'functions': len(funcs), 'sites': total,
        'spellings': dict(spell), 'coverage': dict(cov),
        'typed_pct': round(100.0 * (cov['strong'] + cov['derived']) / total, 1) if total else 0,
        'typed_or_view_pct': round(100.0 * (cov['strong'] + cov['derived'] + cov['view_only']) / total, 1) if total else 0,
        'base_identities': len(by_label), 'refused': dict(S.refused), 'unstable_classes': len(S.unstable),
        'errors_sample': errors[:20],
    }
    (out / 'summary.json').write_text(json.dumps(summary, indent=1, sort_keys=True) + '\n')
    return summary


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=ROOT)
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--workers', type=int, default=4)
    ap.add_argument('--limit', type=int)
    ap.add_argument('--tu', action='append', help='physical TU path(s) instead of the registered set')
    args = ap.parse_args(argv)
    summary = run(args.root, args.out, tus=args.tu, workers=args.workers, limit=args.limit)
    print(json.dumps({k: summary[k] for k in ('physical_tus', 'tu_errors', 'functions', 'sites', 'typed_pct',
                                              'typed_or_view_pct', 'coverage', 'spellings')}, sort_keys=True))


if __name__ == '__main__':
    main()
