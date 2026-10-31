#!/usr/bin/env python3
"""Pointer-cast blocker census: every counted pointer cast in src/ classified by what keeps it.

    cast_census.py --root ROOT --out DIR [--folder src] [--workers 6] [--runtime DIR] [--runtime-src REV]

The unit is one lexical pointer cast as tools/lint/debt_check.py counts it (`pointer_casts`).  Clang (the
field_census front end, mipsel layouts) parses every registered physical TU that compiles a file under
--folder; each CStyleCastExpr to a pointer type is joined to its lexical cast by source offset, and the
expression around it decides the class.  A deref chain `*(s16 *)((u8 *)p + 0x10)` is one *site* holding two
casts; both casts get the site's class.

Classes (column `cls`; `sub` gives the reason):

  n  mechanical now:   fold_now     a typed base with an exact member (cast_fold folds it today)
                       redundant    a conversion C performs implicitly (void * either side, same type)
                       addr_member  `(u8 *)p + K` used as an address where p's struct has a member at K
  a  untyped base:     void / byte / scalar / integer / global / pointer_pointer base of an access, or an
                       untyped variable viewed through a real struct (`((ActorRecord *)arg0)->x`)
  b  typed base, no member: no_member (gap / pad), array_member (unk_XX[N] covers the offset),
                       width / signedness / pointer_type mismatch, beyond_struct, negative_offset
  c  generated or per-function view (S_<addr>, Rec_, Row_, *View, Func<addr>State ...) on either side
  d  inside a macro expansion
  e  legitimate C (the floor): function pointers, constant addresses, byte walks (variable offsets),
                       pointer differences, byte-pointer arguments of copy/fill helpers
  f  other: conversions between unrelated typed pointers (a prototype or variable type decides), casts the
                       AST could not see (unmatched lexical casts)

Runtime evidence (--runtime, the rtti site_facts.tsv.gz of the private native port; never written to src)
is joined per access site on file + line (mapped from --runtime-src to the scanned text by a line diff) +
width: `rt` is single_kind / multi_kind / global / overlay / not_reached.

Outputs: sites.tsv.gz (one row per cast), census.tsv (folder x cls x sub), summary.json.  Read-only.
"""
from __future__ import annotations

import argparse
import collections
from concurrent.futures import ProcessPoolExecutor
import difflib
import gzip
import json
import os
from pathlib import Path
import re
import subprocess
import sys

HERE = Path(__file__).resolve().parent


def _setup_path(root):
    for p in (HERE, HERE.parent, root / 'tools' / 'typing', root / 'tools', root / 'tools' / 'lint',
              root / 'tools' / 'readability'):
        if str(p) not in sys.path:
            sys.path.append(str(p))


GENERATED = re.compile(r'(?:^|_)S_(?:func_)?[0-9A-Fa-f]{6,8}|^Rec_|^Row_|^R\d+_|(?<!^Game)View$|^@|_pre$|'
                       r'^Func[0-9A-Fa-f]{8}|[0-9A-Fa-f]{8}(?:State|Args?|Data|Ctx|Work)$')
COPY_FN = re.compile(r'(?:mem|b)(?:cpy|set|move|copy|zero|cmp)|copy|fill|clear|zero|swap|checksum|crc|hash|'
                     r'read|write|load|store|transfer|dma|decode|decompress|unpack|load_image|store_image', re.I)
STATEMENT_PARENTS = {'CompoundStmt', 'IfStmt', 'ForStmt', 'WhileStmt', 'DoStmt', 'CaseStmt', 'DefaultStmt',
                     'LabelStmt', 'SwitchStmt'}


def is_pointer(t):
    t = (t or '').strip()
    return t.endswith('*') or '(*)' in t or bool(re.search(r'\(\*\s*\w*\)\s*\(', t))


def is_fnptr(unit, t):
    t = (t or '').strip()
    if '(*' in t:
        return True
    return unit.T.resolve(t) == 'fnptr*'


class Ctx:
    def __init__(self, unit, A, C, F):
        self.unit, self.A, self.C, self.F = unit, A, C, F

    def rec_name(self, key):
        return key or ''

    def generated(self, key):
        return bool(key) and bool(GENERATED.search(key))


def climb(parents, node, A, C):
    """Outermost node of the address expression containing `node` (parens, pointer casts, +/- integer)."""
    top = node
    while True:
        p = parents.get(id(top))
        if p is None:
            return top, None
        k = p.get('kind')
        if k == 'ParenExpr':
            top = p
            continue
        if k in ('CStyleCastExpr', 'ImplicitCastExpr') and p.get('castKind') in ('BitCast', 'NoOp') and \
                is_pointer(C.qtype(p)):
            top = p
            continue
        if k == 'BinaryOperator' and p.get('opcode') in ('+', '-') and is_pointer(C.qtype(p)):
            top = p
            continue
        return top, p


def chain_leaf(unit, e, A, C):
    """Walk an address chain down to its base: (leaf, const offset or None, has_variable_index)."""
    e = A.strip_parens(e)
    off, var = 0, False
    while e:
        k = e.get('kind')
        if k in ('CStyleCastExpr', 'ImplicitCastExpr') and e.get('castKind') in ('BitCast', 'NoOp') and A.kids(e):
            e = A.strip_parens(A.kids(e)[0])
            continue
        if k == 'ParenExpr':
            e = A.strip_parens(e)
            continue
        if k == 'BinaryOperator' and e.get('opcode') in ('+', '-') and is_pointer(C.qtype(e)):
            a, b = A.kids(e)
            if is_pointer(C.qtype(a)):
                ptr, idx = a, b
            else:
                ptr, idx = b, a
            n = C.int_value(idx)
            pointee = unit.T.pointee(C.qtype(ptr))
            scale = 1 if pointee in (None, 'void') else (unit.size(pointee) or 0)
            if n is None or not scale:
                var = True
                off = None
            elif off is not None:
                off += (n if e['opcode'] == '+' else -n) * scale
            e = A.strip_parens(ptr)
            continue
        break
    return e, off, var


def base_class(unit, leaf, A, C):
    """(kind, record key) of an access base expression."""
    t = C.qtype(leaf)
    r = unit.T.resolve(t)
    if leaf.get('kind') == 'UnaryOperator' and leaf.get('opcode') == '&':
        obj = A.strip_parens(A.kids(leaf)[0])
        rec = unit.T.record(C.qtype(obj))
        rt = unit.T.resolve(C.qtype(obj))
        if rec and not rt.endswith('*') and rec in unit.layouts and '[' not in rt:
            return 'struct', rec
        if '[' in rt or not rec:
            return 'global', None
    if leaf.get('kind') == 'ImplicitCastExpr' and leaf.get('castKind') == 'ArrayToPointerDecay':
        inner = A.strip_parens(A.kids(leaf)[0])
        it = unit.T.resolve(C.qtype(inner))
        el = it.split('[', 1)[0]
        if el.startswith('rec:') and el[4:] in unit.layouts:
            return 'struct_array', el[4:]
        return 'global', None
    key = unit.record_of_pointer(t)
    if key:
        return 'struct', key
    if r.endswith('**'):
        return 'pointer_pointer', None
    if r == 'void*':
        return 'void', None
    if r.endswith('*') and r[:-1] in A.BYTE_POINTEES:
        return 'byte', None
    if r.endswith('*') and r[:-1].startswith('rec:'):
        return 'incomplete', r[5:-1]
    if r.endswith('*'):
        return 'scalar', None
    if C.int_value(leaf) is not None:
        return 'constant', None
    return 'integer', None


def member_match(unit, F, key, off, want, store_only, rhs):
    """('fold_now', path) or (b-reason, None) for an access of type want at offset off of record key."""
    size = unit.layouts.get(key, {}).get('size') or 0
    if off < 0:
        return 'negative_offset', None
    if off >= size:
        return 'beyond_struct', None
    cands = [(p, t) for p, t, _ in unit.leaves_at(key, off) if not F.PAD.search(p)]
    allc = [(p, t) for p, t, _ in unit.leaves_at(key, off)]
    if not cands:
        # Inside a member that does not start at off (an array or a wider scalar) or in a gap.
        return ('pad_member' if allc else _inside(unit, key, off)), None
    why = None
    for exact in (True, False):
        for p, t in cands:
            ok, reason = F.same_access(unit, want, t, store_only and not exact, rhs)
            if ok:
                return 'fold_now', p
            why = why or reason
    return (why or 'no_exact_member'), None


def _inside(unit, key, off):
    """Classify an offset with no member starting there: inside an array member, inside a scalar, or a gap."""
    lay = unit.layouts.get(key) or {}
    for node in lay.get('kids', []):
        t = node['type']
        sz = unit.size(t) or 0
        if node['off'] <= off < node['off'] + sz:
            if '[' in t:
                name = node['name'] or ''
                return 'array_member' if not unit.T.record(t.split('[')[0]) else 'array_of_struct'
            if unit.T.record(t) and not unit.T.resolve(t).endswith('*'):
                return 'inside_substruct'
            return 'inside_scalar'
    return 'no_member'


def dest_type(unit, top, holder, A, C):
    """Type the context converts the cast's value to, or None when the context does not convert implicitly."""
    if holder is None:
        return None
    k = holder.get('kind')
    if k == 'ImplicitCastExpr' and holder.get('castKind') in ('BitCast', 'NoOp'):
        return C.qtype(holder)
    if k == 'BinaryOperator' and holder.get('opcode') == '=' and A.kids(holder)[1] is top:
        return C.qtype(A.kids(holder)[0])
    if k == 'VarDecl':
        return C.qtype(holder)
    if k == 'CallExpr':
        return 'call_arg'
    if k == 'ReturnStmt':
        return 'return'
    return None


def base_decl(ctx, leaf, A):
    """Where the base value comes from: param:N, local, global, member, load, call, other."""
    e = A.strip_implicit(leaf) if leaf else None
    while e and e.get('kind') in ('CStyleCastExpr', 'ParenExpr', 'ImplicitCastExpr') and A.kids(e):
        e = A.kids(e)[0]
    if not e:
        return ''
    k = e.get('kind')
    if k == 'DeclRefExpr':
        d = e.get('referencedDecl') or {}
        if d.get('kind') == 'ParmVarDecl':
            return 'param:%s' % ctx.params.get(d.get('id'), '?')
        if d.get('kind') == 'VarDecl':
            return 'local' if d.get('id') in ctx.locals else 'global'
        return d.get('kind', 'decl')
    if k == 'MemberExpr':
        return 'member'
    if k in ('UnaryOperator', 'ArraySubscriptExpr'):
        return 'load' if (k == 'ArraySubscriptExpr' or e.get('opcode') == '*') else ('addr' if e.get('opcode') == '&' else 'other')
    if k == 'CallExpr':
        return 'call'
    if k == 'IntegerLiteral':
        return 'constant'
    return k


def classify_cast(ctx, node, parents, fn_name):
    unit, A, C, F = ctx.unit, ctx.A, ctx.C, ctx.F
    target = C.qtype(node)
    kids = A.kids(node)
    if not kids:
        return None
    op = kids[0]
    optype = C.qtype(op)
    ck = node.get('castKind')
    rec = {'target': target, 'operand_type': optype}
    # e: function pointers and integer constants.
    if is_fnptr(unit, target) or is_fnptr(unit, optype) or ck == 'FunctionToPointerDecay':
        return dict(rec, cls='e', sub='function_pointer')
    if ck == 'IntegralToPointer' or ck == 'NullToPointer':
        v = C.int_value(op)
        if v is not None:
            return dict(rec, cls='e', sub='constant_address' if v else 'null_constant')
    top, holder = climb(parents, node, A, C)
    hk = holder.get('kind') if holder else None
    deref = None
    if hk == 'UnaryOperator' and holder.get('opcode') == '*':
        deref = ('star', holder)
    elif hk == 'ArraySubscriptExpr' and A.kids(holder)[0] is top:
        deref = ('index', holder)
    elif hk == 'ImplicitCastExpr' and holder.get('castKind') == 'ArrayToPointerDecay':
        pass
    elif hk == 'MemberExpr' and holder.get('isArrow'):
        deref = ('arrow', holder)
    # An ImplicitCastExpr(LValueToRValue) never sits between; but a BitCast to the subscript base type may.
    if deref is None and hk == 'ImplicitCastExpr' and holder.get('castKind') in ('LValueToRValue',):
        pass
    leaf, off, var = chain_leaf(unit, top, A, C)
    bkind, bkey = base_class(unit, leaf, A, C) if leaf else ('unknown', None)
    rec.update(base_kind=bkind, base_record=bkey or '', offset='' if off is None else off,
               base_expr=C.expr_text(leaf) if leaf else '', base_decl=base_decl(ctx, leaf, A))
    cast_rec = unit.record_of_pointer(target)
    view_generated = ctx.generated(cast_rec) or ctx.generated(unit.T.record(target) or '')
    if deref:
        how, site = deref
        rec['access'] = how
        if how == 'arrow':
            vkey = unit.record_of_pointer(C.qtype(top))
            moff = A.member_offset(unit, vkey, site.get('name')) if vkey else None
            want_node = site
            if ctx.generated(vkey):
                return dict(rec, cls='c', sub='generated_view' + ('' if bkind == 'struct' else '_untyped_base'),
                            view=vkey, line=site.get('_l'))
            if bkind == 'struct' and off is not None and moff is not None:
                if ctx.generated(bkey):
                    return dict(rec, cls='c', sub='generated_base', view=vkey, line=site.get('_l'))
                if vkey == bkey:
                    return dict(rec, cls='n', sub='redundant', view=vkey, line=site.get('_l'))
                r, path = member_match(unit, F, bkey, off + moff, C.qtype(site), False, None)
                if r == 'fold_now':
                    return dict(rec, cls='n', sub='fold_view', view=vkey, path=path, line=site.get('_l'))
                return dict(rec, cls='b', sub='view_' + r, view=vkey, width=unit.size(C.qtype(site)) or '',
                            line=site.get('_l'), access_offset=off + moff)
            if bkind == 'struct' and ctx.generated(bkey):
                return dict(rec, cls='c', sub='generated_base', view=vkey, line=site.get('_l'))
            if bkind == 'struct':
                return dict(rec, cls='b', sub='view_variable_offset', view=vkey, line=site.get('_l'))
            return dict(rec, cls='a', sub='view_' + bkind, view=vkey, line=site.get('_l'),
                        width=unit.size(C.qtype(site)) or '', access_offset=moff if off == 0 else '')
        # star / index
        want = C.qtype(site)
        width = unit.size(want) or ''
        rec.update(width=width, line=site.get('_l'))
        if how == 'index':
            idx = C.int_value(A.kids(site)[1])
            if idx is None:
                var = True
            elif off is not None and width:
                off += idx * width
        rec['access_offset'] = '' if off is None or var else off
        if view_generated:
            return dict(rec, cls='c', sub='generated_cast')
        if bkind in ('struct', 'struct_array'):
            if ctx.generated(bkey):
                return dict(rec, cls='c', sub='generated_base')
            if var or off is None:
                return dict(rec, cls='b', sub='variable_offset')
            if bkind == 'struct_array':
                return dict(rec, cls='b', sub='struct_array_base')
            # store context
            outer = site
            while parents.get(id(outer)) is not None and parents[id(outer)].get('kind') == 'ParenExpr':
                outer = parents[id(outer)]
            h2 = parents.get(id(outer))
            store_only, rhs = False, None
            if h2 is not None and h2.get('kind') == 'BinaryOperator' and h2.get('opcode') == '=' and \
                    A.kids(h2)[0] is outer:
                above = parents.get(id(h2))
                store_only = above is None or above.get('kind') in STATEMENT_PARENTS
                rhs = A.kids(h2)[1]
            rec['store'] = int(bool(h2 is not None and h2.get('kind') in ('BinaryOperator', 'CompoundAssignOperator')
                                    and h2.get('opcode', '').endswith('=') and h2.get('opcode') not in ('==', '!=', '<=', '>=')
                                    and A.kids(h2)[0] is outer))
            r, path = member_match(unit, F, bkey, off, want, store_only, rhs)
            if r == 'fold_now':
                return dict(rec, cls='n', sub='fold_now', path=path)
            return dict(rec, cls='b', sub=r)
        if var and bkind in ('byte', 'void', 'scalar', 'global'):
            return dict(rec, cls='e', sub='byte_walk_' + bkind)
        return dict(rec, cls='a', sub=bkind)
    # Not a dereference: a conversion or an address computation.
    rec['access'] = 'value'
    if hk == 'BinaryOperator' and holder.get('opcode') == '-' and all(is_pointer(C.qtype(x)) for x in A.kids(holder)):
        return dict(rec, cls='e', sub='pointer_difference')
    if top is not node and off not in (None, 0) and not var and bkind == 'struct':
        if ctx.generated(bkey) or view_generated:
            return dict(rec, cls='c', sub='generated_address')
        r, path = member_match(unit, F, bkey, off, 'u8', True, None)
        # any member starting at off makes `&p->member` spellable (the address only)
        cands = [p for p, t, _ in unit.leaves_at(bkey, off) if not F.PAD.search(p)]
        if cands:
            return dict(rec, cls='n', sub='addr_member', path=cands[0])
        return dict(rec, cls='b', sub='addr_' + _inside(unit, bkey, off) if 0 <= off < (unit.layouts[bkey].get('size') or 0)
                    else 'addr_beyond_struct')
    if var:
        return dict(rec, cls='e', sub='byte_walk_value')
    if view_generated or ctx.generated(unit.T.record(optype) or ''):
        return dict(rec, cls='c', sub='generated_conversion')
    dest = dest_type(unit, top, holder, A, C)
    src_t = C.qtype(op)
    cs, ct = unit.canon(src_t), unit.canon(target)
    if dest == 'call_arg':
        # parameter type: the implicit conversion clang inserted above, if any, else the cast type itself
        dest = target
    if dest == 'return':
        dest = target
    if cs == ct and top is node:
        return dict(rec, cls='n', sub='redundant_same_type')
    if dest and top is node:
        cd = unit.canon(dest)
        if cd == cs or (cd == 'void*' and is_pointer(src_t) and not is_fnptr(unit, src_t)) or \
                (cs == 'void*' and cd.endswith('*') and not is_fnptr(unit, dest)):
            return dict(rec, cls='n', sub='redundant_to_' + ('void' if cd == 'void*' else 'typed'))
    if ck == 'IntegralToPointer':
        return dict(rec, cls='a', sub='integer_value')
    # byte pointer argument of a copy/fill helper
    if hk in ('CallExpr', 'ImplicitCastExpr') and (ct.endswith('*') and ct[:-1] in A.BYTE_POINTEES or ct == 'void*'):
        call = holder if hk == 'CallExpr' else parents.get(id(holder))
        if call is not None and call.get('kind') == 'CallExpr':
            callee = C.expr_text(A.kids(call)[0])
            if COPY_FN.search(callee or ''):
                return dict(rec, cls='e', sub='copy_helper_arg', callee=callee)
    if bkind in ('void', 'byte', 'integer', 'scalar', 'pointer_pointer'):
        return dict(rec, cls='a', sub='conversion_from_' + bkind)
    return dict(rec, cls='f', sub='typed_conversion')


def scan_tu(args):
    root, rel, recipe, files = args
    root = Path(root)
    _setup_path(root)
    import cast_ast as A
    import cast_fold as F
    import field_census as C
    try:
        unit, error = A.clang_unit(root, rel, recipe)
    except Exception as exc:
        return {'tu': rel, 'error': str(exc)[-300:], 'rows': []}
    if unit is None:
        return {'tu': rel, 'error': error, 'rows': []}
    ctx = Ctx(unit, A, C, F)
    files = set(files)
    rows = []
    for d in unit.tree.get('inner', []):
        f = d.get('_f') or rel
        if f not in files:
            continue
        if d.get('kind') not in ('FunctionDecl', 'VarDecl'):
            continue
        if d.get('kind') == 'FunctionDecl' and not any(x.get('kind') == 'CompoundStmt' for x in d.get('inner', [])):
            continue
        text = unit.text(f)
        parents = {}
        ctx.params, ctx.locals = {}, set()
        for x in d.get('inner', []):
            if x.get('kind') == 'ParmVarDecl':
                ctx.params[x.get('id')] = len(ctx.params)
        for node, parent in A.walk(d):
            parents[id(node)] = parent
            if node.get('kind') == 'VarDecl' and node is not d:
                ctx.locals.add(node.get('id'))
        for node, parent in A.walk(d):
            if node.get('kind') != 'CStyleCastExpr' or not is_pointer(C.qtype(node)):
                continue
            macro = A.in_macro(node)
            rng = None if macro else A.node_range(node, text)
            try:
                r = classify_cast(ctx, node, parents, d.get('name'))
            except Exception as exc:  # recorded, never fatal
                r = {'cls': 'f', 'sub': 'classifier_error:' + type(exc).__name__, 'target': C.qtype(node)}
            if r is None:
                continue
            if macro:
                # A cast written in this file inside a macro argument (or around a macro name) is still a
                # lexical cast here; one inside a header macro body is not counted by debt_check.
                begin = (node.get('range') or {}).get('begin') or {}
                offs = [x.get('offset') for x in (begin.get('spellingLoc') or {}, begin.get('expansionLoc') or {}, begin)
                        if x.get('offset') is not None]
                r = dict(r, cls='d', sub='macro:%s:%s' % (r['cls'], r['sub']), macro=1, starts=offs)
            r.update(file=f, func=d.get('name'), start=rng[0] if rng else -1)
            r.setdefault('line', node.get('_l'))
            r['cast_line'] = node.get('_l')
            r['col'] = ((node.get('range') or {}).get('begin') or {}).get('col', '')
            rows.append(r)
    return {'tu': rel, 'error': error, 'rows': rows}


def lexical_casts(root, rel):
    import score as S
    text = (root / rel).read_text()
    tokens = S.lex(text)
    pairs, _ = S.pairs_of(tokens)
    import debt_check as D
    res = D.analyze(rel, text)
    spans, _ = D.exemptions(text, tokens, pairs)
    excluded = set()
    for a, b in spans:
        if tokens[a].value == 'do' and a + 1 in pairs and tokens[a + 1].value == '{':
            close = pairs[a + 1]
            excluded.update(range(a, a + 2))
            excluded.update(range(close, b))
        else:
            excluded.update(range(a, b))
    return [(tokens[a].pos, text.count('\n', 0, tokens[a].pos) + 1, any(i in excluded for i in range(a, b + 1)))
            for a, b in S.cast_sites(tokens, pairs)], sum(v['counts']['pointer_casts'] for v in res['scopes'].values())


# ------------------------------------------------------------------------------------------- runtime join

def line_maps(root, old_rev, files, git_root):
    """{file: {new_line: old_line}} for files that differ between old_rev and the scanned text."""
    maps = {}
    for f in files:
        try:
            old = subprocess.run(['git', '-C', str(git_root), 'show', '%s:%s' % (old_rev, f)], capture_output=True,
                                 text=True, check=True).stdout.splitlines()
        except subprocess.CalledProcessError:
            maps[f] = None
            continue
        new = (root / f).read_text().splitlines()
        if old == new:
            continue
        m = {}
        sm = difflib.SequenceMatcher(None, old, new, autojunk=False)
        for tag, i1, i2, j1, j2 in sm.get_opcodes():
            if tag == 'equal':
                for k in range(i2 - i1):
                    m[j1 + k + 1] = i1 + k + 1
            elif tag == 'replace' and i2 - i1 == j2 - j1:
                for k in range(i2 - i1):
                    m[j1 + k + 1] = i1 + k + 1
        maps[f] = m
    return maps


def load_runtime(path, files):
    """{(file, line): [(width, class, target, access, offset, smin, smax, umin, umax, count)]}"""
    out = collections.defaultdict(list)
    with gzip.open(path, 'rt') as fh:
        header = fh.readline().rstrip('\n').split('\t')
        ix = {k: i for i, k in enumerate(header)}
        for line in fh:
            p = line.rstrip('\n').split('\t')
            f = p[0]
            if f not in files:
                continue
            out[(f, int(p[ix['line']]))].append({k: p[ix[k]] for k in ('col', 'function', 'access', 'width', 'class',
                                                                     'target', 'offset', 'count', 'smin', 'smax',
                                                                     'umin', 'umax')})
    return out


def runtime_verdict(rows, width, col=None):
    if not rows:
        return 'not_reached', ''
    sel = [r for r in rows if not width or str(r['width']) == str(width)] or rows
    if col:
        exact = [r for r in sel if r['col'] == str(col)]
        sel = exact or sel
    classes = {r['class'] for r in sel}
    targets = sorted({r['target'] for r in sel})
    if classes == {'heap'}:
        return ('single_kind' if len(targets) == 1 else 'multi_kind'), ','.join(targets[:4])
    if classes <= {'global', 'ram'}:
        return 'global', ','.join(t.split('+')[0] for t in targets[:3])
    if classes <= {'overlay'}:
        return 'overlay', ''
    if 'heap' in classes:
        return 'mixed_heap', ','.join(t for t in targets if t.startswith('rk'))[:60]
    return 'mixed', ''


# ------------------------------------------------------------------------------------------- main

def folder_of(f):
    parts = f.split('/')
    return '/'.join(parts[:3]) if len(parts) > 3 else '/'.join(parts[:2])


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=HERE.parents[1])
    ap.add_argument('--folder', default='src')
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--workers', type=int, default=6)
    ap.add_argument('--runtime', type=Path, help='site_facts.tsv.gz of the rtti native run')
    ap.add_argument('--runtime-src', help='decomp revision the runtime evidence was taken at')
    ap.add_argument('--git-root', type=Path, help='repository holding --runtime-src')
    args = ap.parse_args(argv)
    root = args.root.resolve()
    args.out = args.out.resolve()
    _setup_path(root)
    os.chdir(root)
    import cast_fold as F
    files = sorted(p.relative_to(root).as_posix() for p in (root / args.folder).rglob('*.c'))
    tus, _ = F.physical_for(root, files)
    jobs = [(str(root), tu, recipe, files) for tu, recipe in sorted(tus.items())]
    rows, errors = {}, []
    with ProcessPoolExecutor(max_workers=args.workers) as ex:
        for res in ex.map(scan_tu, jobs, chunksize=2):
            if res['error']:
                errors.append((res['tu'], res['error']))
            for r in res['rows']:
                rows.setdefault((r['file'], r['start'], r.get('macro', 0), r.get('line'), tuple(r.get('starts', ()))), r)
    # Join to lexical casts.
    out_rows = []
    lex_total = 0
    by_file = collections.defaultdict(list)
    for r in rows.values():
        by_file[r['file']].append(r)
    for f in files:
        lex, counted = lexical_casts(root, f)
        lex_total += counted
        starts = {r['start']: r for r in by_file.get(f, []) if not r.get('macro')}
        mstarts = {}
        for r in by_file.get(f, []):
            if r.get('macro'):
                text = (root / f).read_text()
                for o in r.get('starts', ()):
                    # clang offsets are bytes; lexical positions are characters
                    c = len(text.encode()[:o].decode(errors='replace')) if not text.isascii() else o
                    mstarts.setdefault(c, r)
        seen, mseen = set(), set()
        for pos, line, exempt in lex:
            r = starts.get(pos)
            if r is None and pos in mstarts:
                r = mstarts[pos]
                mseen.add(id(r))
            if r is None:
                base = Path(f).name
                sub = ('jump_table_data' if re.match(r'D_[0-9A-F]{8}', base) else
                       'slus_partition_unparsed' if f.startswith('src/slus/') else 'unmatched_lexical')
                out_rows.append({'file': f, 'func': '', 'line': line, 'cast_line': line, 'start': pos,
                                 'cls': 'e' if sub == 'jump_table_data' else 'f', 'sub': sub,
                                 'counted': 0 if exempt else 1})
                continue
            seen.add(pos)
            r = dict(r, counted=0 if exempt else 1)
            if exempt:
                r['sub'] += ':bytes_exempt'
            out_rows.append(r)
        for r in by_file.get(f, []):
            if r.get('macro'):
                if id(r) not in mseen:
                    out_rows.append(dict(r, counted=0, sub=r['sub'] + ':header_macro'))
            elif r['start'] not in seen:
                out_rows.append(dict(r, counted=0, sub=r['sub'] + ':uncounted'))
    # Runtime join.
    if args.runtime:
        rt = load_runtime(args.runtime, set(files))
        rt_funcs = {(f, x['function']) for (f, _), xs in rt.items() for x in xs}
        maps = line_maps(root, args.runtime_src, files, args.git_root or root) if args.runtime_src else {}
        for r in out_rows:
            if r['cls'] not in ('a', 'b', 'c', 'n') or r.get('access') in (None, 'value'):
                continue
            line = r.get('line')
            m = maps.get(r['file'], {})
            if m is None:
                r['rt'] = 'file_new'
                continue
            old = m.get(line, line) if m else line
            if m and line not in m:
                r['rt'] = 'line_changed'
                continue
            r['rt'], r['rt_targets'] = runtime_verdict(rt.get((r['file'], old)), r.get('width'))
            if r['rt'] == 'not_reached' and (r['file'], r.get('func')) not in rt_funcs:
                r['rt'] = 'fn_not_run'
    args.out.mkdir(parents=True, exist_ok=True)
    cols = ['file', 'folder', 'func', 'line', 'cast_line', 'counted', 'cls', 'sub', 'access', 'target', 'operand_type',
            'base_kind', 'base_record', 'base_decl', 'base_expr', 'view', 'offset', 'access_offset', 'width', 'store', 'path', 'rt', 'rt_targets']
    with gzip.open(args.out / 'sites.tsv.gz', 'wt') as fh:
        fh.write('\t'.join(cols) + '\n')
        for r in sorted(out_rows, key=lambda r: (r['file'], r.get('start', 0))):
            r['folder'] = folder_of(r['file'])
            fh.write('\t'.join(str(r.get(c, '')).replace('\t', ' ') for c in cols) + '\n')
    agg = collections.Counter()
    for r in out_rows:
        if r.get('counted'):
            agg[(r['folder'], r['cls'], r['sub'], r.get('rt', ''))] += 1
    with open(args.out / 'census.tsv', 'w') as fh:
        fh.write('folder\tcls\tsub\trt\tcasts\n')
        for (fo, c, s, rtv), n in sorted(agg.items()):
            fh.write('%s\t%s\t%s\t%s\t%d\n' % (fo, c, s, rtv, n))
    counted = [r for r in out_rows if r.get('counted')]
    summary = {'files': len(files), 'tus': len(jobs), 'lexical_pointer_casts': lex_total,
               'classified': len(counted),
               'by_class': dict(collections.Counter(r['cls'] for r in counted).most_common()),
               'by_sub': dict(collections.Counter(r['cls'] + ':' + r['sub'] for r in counted).most_common()),
               'macro_casts_uncounted': sum(1 for r in out_rows if r.get('macro')),
               'errors': errors[:30], 'error_count': len(errors)}
    (args.out / 'summary.json').write_text(json.dumps(summary, indent=1) + '\n')
    print(json.dumps({k: summary[k] for k in ('files', 'tus', 'lexical_pointer_casts', 'classified', 'by_class',
                                              'error_count')}))
    return 0


if __name__ == '__main__':
    sys.exit(main())
