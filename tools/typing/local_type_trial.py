#!/usr/bin/env python3
"""Local-from-typed-source trial: an untyped local takes the record type its typed sources agree on.

    local_type_trial.py census --file F ... | --folder D  --out DIR [--workers 2]
    local_type_trial.py apply  --file F ...               --out DIR [--only FUNC:VAR ...] [--port PORT]
                               [--allow-scalar-reuse] [--cast-other-pointer] [--skip-list F] [--dry-run]

A *candidate* is a function-local `void *x` / `u8 *x` or generated-view `S_<addr>_N *x` (one declarator; no
static or extern; never a parameter, whose contract belongs to the prototype lanes).  A view local's member
accesses are renamed onto the record's member at the same offset with the same type (never through a union);
one that has none (`view_member_unmapped`), arithmetic on it (`view_arithmetic`) or passing it on as the view
(`passed_as_view`) refuses it.  Its *sources* are its initializer and every
`x = rhs`; each rhs is classified after stripping parentheses, implicit conversions and explicit casts to
`void *` / byte pointers / generated views:

  typed        a pointer to a named record that is not a generated view (a parameter, a typed local, a
               typed member load, a typed call return, `NODE_HEADER(...)`); it votes for that record;
  null         a null constant (no vote);
  untyped      a `void *` value: no vote.  A node-body walk (`NODE_BODY(h)`, `h + 0x20`) or another
               candidate local is accepted; a void * parameter, call return, member load or other value of
               unproven identity refuses the local (`untyped_source`, R3) unless --allow-untyped;
  byte         a byte-pointer value: no vote; the store takes one `(T *)` cast (counted);
  node_link    `x = view->link.i + 0x20`: a node link read as an integer through a view (no vote; the
               NODE_BODY pass below respells it);
  scalar       an integer converted to a pointer (a register reused for a flag): refused as
               `scalar_reuse` unless --allow-scalar-reuse (then the existing cast is respelled `(T *)`);
  constant_address  `(void *)0x800E0000`: always refused (`constant_address_source`).

The local is refused when typed sources name two records (`sources_disagree`), none (`no_typed_source`),
or when a use would change meaning or need a new conversion after the retype: `++`/`--`/compound
assignment (`cursor_arithmetic`), `&x`, `sizeof`, pointer difference, an implicit conversion to another
pointer type (`implicit_to_other_pointer`, `implicit_to_byte_pointer`), a compare with a pointer of another
type, a conditional operand, a use inside a macro argument.  A bare pointer arithmetic `x + K` / `x - K`
(which would scale by the record size after the retype) is rewritten before compiling:

  `x - 0x20`  ->  `NODE_HEADER(x)`              when the result feeds a void * or ObjectNodeHeader * slot;
  `x + K`     ->  `(u8 *)x + K`                 when the result feeds a void * / byte slot, a cast or more
                                                arithmetic (the same bytes and the same result type);
              ->  `(void *)((u8 *)x + K)`       otherwise (keeps the void * result type);
  `x[i]`, `*x` on a byte local -> `((u8 *)x)[i]`, `*(u8 *)x`.
Explicit `(T *)x` casts to the chosen record become `x`; source casts to `void *` / byte become redundant
and are dropped.  An implicit conversion to another record pointer that the void * local hid is refused
(`implicit_to_other_pointer`) unless --cast-other-pointer spells it as an explicit cast (counted; `(void *)`
when the target record is incomplete, e.g. a prototype-scope `struct Node`).

**apply** proves each file in stages (cast_wave.py's model): every physical TU that compiles the file is
captured first (layout_compile_identity.capture_one: raw object, canonical assembly, canonical object); the
retypes are applied together and recaptured (identical, or each candidate is retried alone from the
original text); then tools/typing/cast_fold.py's scan folds the sites whose base is a retyped local (twice:
an inner fold can expose an outer one), except sites whose member path crosses a union (their union-ledger
rows would move) or names a signedness view; the folds are recaptured (a failing set is split per function,
then per site); then stores of a header + 0x20 walk into a kept body local (`x = (u8 *)h + 0x20`,
`x = h + 0x20` with h void *, `x = view->link.i + 0x20`) become `NODE_BODY(h)`, with a raw pointer load of h
from a typed base respelled as that base's pointer member (`NODE_BODY(actor->next_actor_header)`); finally
no debt class (tools/lint/debt_check.py) may rise in any function and, with --port,
no GCC warning group (tools/lint/lint_closure.py lint flags) may rise in the TU.  A function whose debt or
warnings rise loses its candidates and the file is proved again.  The file on disk at exit is the last
proven text; every file is restored on --dry-run, on an error and on SIGTERM.

Outputs under --out: candidates.jsonl (one row per local: function, variable, declared type, chosen record,
sources by class, casts on the variable, verdict or refusal reason), fold_refusals.tsv (cast_fold's refusal
reasons at the retyped bases), receipt.json (per file: casts before/after, kept locals, verdicts).
"""
from __future__ import annotations

import argparse
import collections
from concurrent.futures import ProcessPoolExecutor
import json
from pathlib import Path
import re
import signal
import sys
import time

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent), str(HERE.parent / 'lint')]
import cast_ast as A  # noqa: E402
import cast_fold as F  # noqa: E402
import field_census as C  # noqa: E402

GENERATED = re.compile(r'^(?:S_(?:func_)?[0-9A-Fa-f]{8}\w*|Rec_\w+|Row_\w+|R\d+_\w+)$')
SIGN_VIEW = re.compile(r'(?:^|\.)(?:(?:un)?signed_\w+|whole|halves|s|u|b|sb|h|sh|w|sw|bytes|Ints)(?:\[|\.|$)')
HEADER_SIZE = 0x20
VIEW_DECL = re.compile(r'(\s*(?:register\s+)?)((?:struct\s+)?(?:S_(?:func_)?[0-9A-Fa-f]{8}\w*|Rec_\w+|Row_\w+|R\d+_\w+)\s*\*\s*)')
DECL = re.compile(r'(\s*(?:register\s+)?)((?:unsigned\s+char|signed\s+char|char|u8|s8|void)\s*\*\s*)')


def canon(unit, e):
    return unit.canon(C.qtype(e))


def is_untyped_pointer(unit, t):
    r = unit.canon(t)
    return r == 'void*' or (r.endswith('*') and not r.endswith('**') and r[:-1] in A.BYTE_POINTEES)


# caller_types.py's generated-name pattern: per-function and per-overlay views (ovl_<bank>_<addr>_S_<addr>_N,
# R03_<addr>_S_<addr>_N, Rec_D_<addr>, ...) are never a source record.
GENERATED_ANY = re.compile(r'(?:^|_)S_(?:func_)?[0-9A-Fa-f]{6,8}(?:_|$)|^Row_|^Rec_|^R\d+_|^B\d+_|_pre$|'
                           r'^Func[0-9A-Fa-f]{8}|[0-9A-Fa-f]{8}')


def named_record(unit, t):
    """Record key of a pointer to a named, complete, non-generated record, else None."""
    key = unit.record_of_pointer(t)
    if not key or key.startswith('@') or GENERATED.match(key) or GENERATED_ANY.search(key):
        return None
    return key


def spelled_type(t):
    return re.sub(r'\s*\*\s*$', '', (t or '').strip())


def up(parents, node):
    """(outermost paren-wrapped node, its first non-paren parent)."""
    p = parents.get(id(node))
    while p is not None and p.get('kind') == 'ParenExpr':
        node, p = p, parents.get(id(p))
    return node, p


def classify_source(unit, rhs, candidates):
    """(class, record key or None, written type, node whose cast/text may be edited)."""
    e = rhs
    explicit = None
    while True:
        e = A.strip_parens(e)
        if not e:
            return 'untyped', None, None, None
        k = e.get('kind')
        if k == 'ImplicitCastExpr' and A.kids(e):
            if e.get('castKind') in ('IntegralToPointer',):
                if C.int_value(e) is not None:
                    return ('null' if C.int_value(e) == 0 else 'constant_address'), None, None, explicit
                v = A.strip_parens(A.kids(e)[0])
                if explicit is None and v.get('kind') == 'BinaryOperator' and v.get('opcode') == '+' and \
                        C.int_value(A.kids(v)[1]) == HEADER_SIZE and \
                        A.strip_parens(A.strip_implicit(A.kids(v)[0])).get('kind') == 'MemberExpr':
                    # `x = view->link.i + 0x20`: a node link read as an integer (NODE_BODY after the folds).
                    return 'node_link', None, None, None
                return 'scalar', None, None, explicit
            e = A.kids(e)[0]
            continue
        if k == 'CStyleCastExpr' and A.kids(e):
            t = C.qtype(e)
            inner = A.kids(e)[0]
            if C.int_value(e) is not None:
                return ('null' if C.int_value(e) == 0 else 'constant_address'), None, None, e
            if e.get('castKind') == 'IntegralToPointer':
                return 'scalar', None, None, e
            if is_untyped_pointer(unit, t) or GENERATED.match(unit.record_of_pointer(t) or '-'):
                if A.strip_implicit(inner).get('kind') in ('BinaryOperator', 'UnaryOperator'):
                    # `(void *)(p + 1)` (NODE_BODY) is another object than p: an offset, not a source type.
                    return 'untyped', None, None, explicit
                explicit = explicit or e
                e = inner
                continue
            break
        break
    if C.int_value(e) == 0 and C.int_value(e) is not None:
        return 'null', None, None, explicit
    t = C.qtype(e)
    r = unit.canon(t)
    if '[' in r:
        return 'untyped', None, None, explicit
    if not r.endswith('*') and not r.startswith('fnptr'):
        return 'scalar', None, None, explicit
    key = named_record(unit, t)
    if key and e.get('kind') == 'BinaryOperator' and e.get('opcode') in ('+', '-'):
        # `p + 1` on a typed pointer is the next object, not p's: only NODE_HEADER(x), `(ObjectNodeHeader *)x - 1`,
        # names its own record (the header of body x).
        left = A.strip_parens(A.kids(e)[0])
        if not (e.get('opcode') == '-' and C.int_value(A.kids(e)[1]) == 1 and key == 'ObjectNodeHeader'
                and left.get('kind') == 'CStyleCastExpr'):
            return 'untyped', None, None, explicit
    if key:
        return 'typed', key, spelled_type(t), explicit
    if A.strip_implicit(e).get('kind') == 'DeclRefExpr' and \
            ((A.strip_implicit(e).get('referencedDecl') or {}).get('id') in candidates):
        return 'untyped', None, None, explicit
    if unit.is_byte_pointer(t):
        return 'byte', None, None, explicit
    return 'untyped', None, None, explicit


def untyped_kind(unit, rhs, candidates):
    """Provenance of an untyped source: node_body (NODE_BODY(h), h + 0x20, a link + 0x20), candidate (another
    candidate local), or call / name / member / other (a void * value of unproven identity)."""
    e = A.strip_parens(A.strip_implicit(rhs))
    while e.get('kind') == 'CStyleCastExpr' and A.kids(e):
        inner = A.strip_parens(A.strip_implicit(A.kids(e)[0]))
        if inner.get('kind') == 'BinaryOperator' and inner.get('opcode') == '+':
            b = C.int_value(A.kids(inner)[1])
            if b == HEADER_SIZE or (b == 1 and unit.record_of_pointer(C.qtype(inner)) == 'ObjectNodeHeader'):
                return 'node_body'
        e = inner
    if e.get('kind') == 'BinaryOperator' and e.get('opcode') == '+' and (
            C.int_value(A.kids(e)[1]) == HEADER_SIZE or
            (C.int_value(A.kids(e)[1]) == 1 and unit.record_of_pointer(C.qtype(e)) == 'ObjectNodeHeader')):
        return 'node_body'
    if e.get('kind') == 'BinaryOperator':
        return 'offset'
    k = e.get('kind')
    if k == 'DeclRefExpr':
        return 'candidate' if (e.get('referencedDecl') or {}).get('id') in candidates else 'name'
    if k == 'CallExpr':
        return 'call'
    if k in ('MemberExpr', 'UnaryOperator', 'ArraySubscriptExpr'):
        return 'member'
    return 'other'


def use_of(unit, ref, parents):
    """Classify one non-assignment use of a candidate local: (kind, detail)."""
    node, p = up(parents, ref)
    if p is None:
        return 'refuse', 'use_unknown'
    k = p.get('kind')
    if k == 'UnaryOperator' and p.get('opcode') == '&':
        return 'refuse', 'address_taken'
    if k == 'CompoundAssignOperator' or (k == 'UnaryOperator' and p.get('opcode') in ('++', '--')):
        return 'refuse', 'cursor_arithmetic'
    if k == 'UnaryExprOrTypeTraitExpr':
        return 'refuse', 'sizeof'
    if not (k == 'ImplicitCastExpr' and p.get('castKind') == 'LValueToRValue'):
        return 'refuse', 'use_' + k
    value, q = up(parents, p)
    if q is None:
        return 'refuse', 'use_unknown'
    qk = q.get('kind')
    if qk == 'CStyleCastExpr':
        return 'cast', q
    if qk == 'ImplicitCastExpr':
        ck = q.get('castKind')
        if ck in ('BitCast', 'NoOp'):
            target = unit.canon(C.qtype(q))
            if target == 'void*':
                return 'neutral', None
            if target.endswith('*') and target[:-1] in A.BYTE_POINTEES:
                return 'refuse', 'implicit_to_byte_pointer'
            return 'implicit', q
        if ck == 'PointerToBoolean':
            return 'neutral', None
        if ck == 'PointerToIntegral':
            return 'refuse', 'pointer_to_integer'
        return 'refuse', 'implicit_' + str(ck)
    if qk == 'BinaryOperator':
        op = q.get('opcode')
        if op in ('&&', '||'):
            return 'neutral', None
        if op in ('==', '!=', '<', '>', '<=', '>='):
            other = [x for x in A.kids(q) if x is not value]
            o = A.strip_implicit(other[0]) if other else None
            if o is None:
                return 'refuse', 'pointer_compare'
            if C.int_value(o) == 0 and C.int_value(o) is not None:
                return 'neutral', None
            if unit.canon(C.qtype(o)) == 'void*' or o.get('kind') == 'DeclRefExpr':
                return 'compare', o
            return 'refuse', 'pointer_compare'
        if op in ('+', '-'):
            a, b = A.kids(q)
            if A.strip_implicit(a) is not A.strip_implicit(value) and A.strip_parens(a) is not value:
                if op == '-':
                    return 'refuse', 'pointer_difference'
                return 'arith', (q, 'right')
            other = b
            if unit.canon(C.qtype(other)).endswith('*'):
                return 'refuse', 'pointer_difference'
            return 'arith', (q, 'left')
        if op == '=':
            return 'neutral', 'flow'   # stored into a slot of the local's own type (no conversion node)
        return 'refuse', 'binary_' + str(op)
    if qk in ('IfStmt', 'WhileStmt', 'DoStmt', 'ForStmt'):
        return 'neutral', None
    if qk == 'UnaryOperator' and q.get('opcode') == '!':
        return 'neutral', None
    if qk == 'ArraySubscriptExpr':
        return 'subscript', q
    if qk == 'UnaryOperator' and q.get('opcode') == '*':
        return 'deref', q
    if qk in ('CallExpr', 'ReturnStmt', 'VarDecl', 'InitListExpr'):
        return 'neutral', 'flow'
    if qk == 'ConditionalOperator':
        return 'refuse', 'conditional_operand'
    return 'refuse', 'use_' + qk


def consumer_slot(unit, expr, parents):
    """What the value of `expr` (a rewritten arithmetic) flows into: 'void', 'byte', 'header', 'cast', 'arith',
    'typed' or 'other'."""
    node, p = up(parents, expr)
    if p is None:
        return 'other'
    k = p.get('kind')
    if k == 'CStyleCastExpr':
        return 'cast'
    if k == 'BinaryOperator' and p.get('opcode') in ('+', '-') and A.strip_parens(A.kids(p)[0]) is A.strip_parens(node):
        return 'arith'
    if k == 'ImplicitCastExpr' and p.get('castKind') in ('BitCast', 'NoOp'):
        t = C.qtype(p)
        r = unit.canon(t)
        if r == 'void*':
            return 'void'
        if r.endswith('*') and r[:-1] in A.BYTE_POINTEES:
            return 'byte'
        if unit.record_of_pointer(t) == 'ObjectNodeHeader':
            return 'header'
        return 'typed'
    if k == 'BinaryOperator' and p.get('opcode') == '=':
        return 'void' if unit.canon(C.qtype(p)) in ('void*',) else ('byte' if unit.is_byte_pointer(C.qtype(p))
                                                                      else 'other')
    if k in ('CallExpr', 'ReturnStmt', 'VarDecl'):
        return 'void'
    return 'other'


def view_key(unit, t):
    """Record key when t is a one-star pointer to a generated per-function view."""
    key = unit.record_of_pointer(t)
    return key if key and GENERATED.match(key) else None


def access_leaf(unit, member, parents):
    """(leaf node, byte offset, leaf type) of `p->m(.n)*` starting at an arrow MemberExpr."""
    base_key = unit.record_of_pointer(C.qtype(A.kids(member)[0]))
    off = A.member_offset(unit, base_key, member.get('name')) if base_key else None
    if off is None:
        return None
    leaf, p = member, parents.get(id(member))
    while p is not None and p.get('kind') == 'MemberExpr' and not p.get('isArrow') and A.kids(p)[0] is leaf:
        inner = unit.T.record(C.qtype(leaf))
        sub = A.member_offset(unit, inner, p.get('name')) if inner else None
        if sub is None:
            return None
        off += sub
        leaf, p = p, parents.get(id(p))
    return leaf, off, C.qtype(leaf)


def decl_edit(unit, decl, parents, text, type_name):
    """Replace the declared type of a one-declarator local, keeping `register`."""
    stmt = parents.get(id(decl))
    if stmt is None or stmt.get('kind') != 'DeclStmt' or len(A.kids(stmt)) != 1:
        return 'multi_declarator'
    rng = A.node_range(decl, text)
    loc = (decl.get('loc') or {}).get('offset')
    if rng is None or loc is None or 'spellingLoc' in (decl.get('loc') or {}):
        return 'decl_in_macro'
    if not text.isascii():
        loc = len(text.encode()[:loc].decode(errors='replace'))
    m = DECL.fullmatch(text[rng[0]:loc]) or VIEW_DECL.fullmatch(text[rng[0]:loc])
    if not m:
        return 'decl_spelling'
    return (rng[0] + m.end(1), loc, type_name + ' *')


def strip_cast_edit(cast, text, parents=None):
    """Edit that drops an explicit cast's `(T *)` prefix, keeping the operand text (grouped when needed).
    A bare operand also drops the parentheses that only grouped the cast: `((u8 *)p)->f` -> `p->f`."""
    rng = A.node_range(cast, text)
    bare = A.strip_implicit(A.kids(cast)[0]) if A.kids(cast) else {}
    if parents is not None and rng is not None and bare.get('kind') in ('DeclRefExpr', 'MemberExpr',
                                                                         'ArraySubscriptExpr', 'CallExpr'):
        outer = parents.get(id(cast))
        if outer is not None and outer.get('kind') == 'ParenExpr':
            orng = A.node_range(outer, text)
            brng = A.node_range(bare, text)
            if orng is not None and brng is not None and not (orng[0] and (text[orng[0] - 1].isalnum()
                                                                           or text[orng[0] - 1] == '_')):
                return (orng[0], orng[1], text[brng[0]:brng[1]])
    inner = A.kids(cast)[0]
    irng = A.node_range(inner, text)
    if rng is None or irng is None:
        return None
    operand = text[irng[0]:irng[1]]
    bare = A.strip_implicit(inner)
    if bare.get('kind') in ('DeclRefExpr', 'MemberExpr', 'ArraySubscriptExpr', 'CallExpr'):
        brng = A.node_range(bare, text)
        if brng is not None:
            operand = text[brng[0]:brng[1]]     # `(T *)(name)` -> `name`
            return (rng[0], rng[1], operand)
    ik = 'ParenExpr' if inner.get('kind') == 'ParenExpr' else bare.get('kind')
    if ik not in A.POSTFIX_KINDS and ik != 'ParenExpr':
        operand = '(' + operand + ')'
    return (rng[0], rng[1], operand)


def node_body_source(unit, rhs, text):
    """((start, end, 'NODE_BODY(h)'), casts removed) for a source `(u8 *)h + 0x20` or `h + 0x20` (h void *)."""
    e = A.strip_implicit(rhs)
    rng = A.node_range(e, text)
    removed = 0
    if e.get('kind') == 'CStyleCastExpr' and unit.record_of_pointer(C.qtype(e)):
        e = A.strip_implicit(A.kids(e)[0])      # the (T *) a byte source was given by the retype
        removed = 1
    if e.get('kind') != 'BinaryOperator' or e.get('opcode') != '+' or C.int_value(A.kids(e)[1]) != HEADER_SIZE:
        return None
    left = A.strip_parens(A.kids(e)[0])
    byte_cast = False
    if left.get('kind') == 'CStyleCastExpr' and unit.is_byte_pointer(C.qtype(left)):
        removed += 1
        byte_cast = True
        left = A.kids(left)[0]
    elif unit.canon(C.qtype(A.strip_implicit(left))) != 'void*' and \
            not pointer_member_load(unit, left, text):
        return None
    inner = left if byte_cast else A.strip_implicit(left)
    if not unit.canon(C.qtype(A.strip_implicit(inner))).endswith('*') and not pointer_member_load(unit, inner, text):
        return None
    lr = A.node_range(inner, text)
    if rng is None or lr is None:
        return None
    operand = text[lr[0]:lr[1]].strip()
    while operand.startswith('(') and operand.endswith(')') and A.balanced(operand[1:-1]):
        operand = operand[1:-1].strip()
    member = pointer_member_load(unit, inner, text)
    if member:
        removed += len(re.findall(r'\(\s*[A-Za-z_][\w\s]*\*+\s*\)', operand))
        operand = member
    return (rng[0], rng[1], 'NODE_BODY(%s)' % operand), removed


def pointer_member_load(unit, e, text):
    """`p->m` for a raw pointer load `*(T **)((u8 *)p + K)` from a typed base whose member at K is a data pointer
    (NODE_BODY converts its argument, so the member's own pointee type does not matter)."""
    e = A.strip_parens(A.strip_implicit(e))
    extra = 0
    if e.get('kind') == 'MemberExpr':
        # ((V *)p)->m(.n): a view's link member over a typed base p.
        names, x = [], e
        while x.get('kind') == 'MemberExpr' and not x.get('isArrow'):
            names.append(x.get('name'))
            x = A.strip_parens(A.kids(x)[0])
        if x.get('kind') != 'MemberExpr' or not x.get('isArrow'):
            return None
        names.append(x.get('name'))
        chain = A.strip_parens(A.kids(x)[0])
        if chain.get('kind') != 'CStyleCastExpr':
            return None
        vkey = unit.record_of_pointer(C.qtype(chain))
        for name in reversed(names):
            sub = A.member_offset(unit, vkey, name) if vkey else None
            if sub is None:
                return None
            extra += sub
            node = next((n for n in (unit.layouts.get(vkey) or {}).get('kids', []) if n['name'] == name), None)
            vkey = unit.T.record(node['type']) if node and not unit.T.resolve(node['type']).endswith('*') else None
        if unit.size(C.qtype(e)) != 4:
            return None
    elif e.get('kind') == 'UnaryOperator' and e.get('opcode') == '*':
        chain = A.strip_parens(A.kids(e)[0])
        if chain.get('kind') != 'CStyleCastExpr':
            return None
    else:
        return None
    r = F.base_offset(unit, chain)
    if r is None or r[3]:
        return None
    leaf, off = r[0], r[1] + extra
    key = unit.record_of_pointer(C.qtype(leaf))
    if not key or off < 0:
        return None
    for path, t, _ in unit.leaves_at(key, off):
        if F.PAD.search(path) or path_crosses_union(unit, key, path):
            continue
        c = unit.canon(t)
        if c.endswith('*') and not c.startswith('fnptr'):
            return F.member_text(unit, leaf, False, path, text)
    return None


def plan_function(unit, file, fn, text, allow_scalar=False, cast_other=False, allow_untyped=False):
    """(plans, rows): retype plans and one census row per candidate local of one function."""
    parents, nodes = {}, []
    for n, p in A.walk(fn):
        parents[id(n)] = p
        nodes.append(n)
    decls = {}
    for n in nodes:
        if n.get('kind') == 'VarDecl' and n.get('storageClass') not in ('static', 'extern') \
                and (is_untyped_pointer(unit, C.qtype(n)) or view_key(unit, C.qtype(n))):
            decls[n['id']] = n
    refs = collections.defaultdict(list)
    for n in nodes:
        if n.get('kind') == 'DeclRefExpr':
            did = (n.get('referencedDecl') or {}).get('id')
            if did in decls:
                refs[did].append(n)
    plans, rows = [], []
    for did, decl in decls.items():
        var = decl['name']
        byte_local = unit.is_byte_pointer(C.qtype(decl))
        view = view_key(unit, C.qtype(decl))
        sources, uses = [], []
        if decl.get('init') and A.kids(decl):
            sources.append(A.kids(decl)[0])
        for ref in refs[did]:
            node, p = up(parents, ref)
            if p is not None and p.get('kind') == 'BinaryOperator' and p.get('opcode') == '=' and A.kids(p)[0] is node:
                sources.append(A.kids(p)[1])
            else:
                uses.append(ref)
        casts = 0
        for ref in refs[did]:
            node, p = up(parents, ref)
            if p is not None and p.get('kind') == 'ImplicitCastExpr':
                node, p = up(parents, p)
            while p is not None and p.get('kind') in ('BinaryOperator',) and p.get('opcode') in ('+', '-'):
                node, p = up(parents, p)
            if p is not None and p.get('kind') == 'CStyleCastExpr' and A.node_range(p, text) is not None:
                casts += 1
        row = {'file': file, 'func': fn['name'], 'var': var, 'line': decl.get('_l'), 'declared': C.qtype(decl),
               'sources': collections.Counter(), 'source_text': [], 'casts_on_var': casts, 'record': None}
        why = None
        typed = {}
        src_edits = []
        for rhs in sources:
            cls, key, spelled, cast = classify_source(unit, rhs, decls)
            row['sources'][cls] += 1
            rr = A.node_range(rhs, text)
            if rr and cls != 'typed':
                row['source_text'].append(cls + ': ' + ' '.join(text[rr[0]:rr[1]].split())[:120])
            if cls in ('untyped', 'byte'):
                uk = untyped_kind(unit, rhs, decls)
                row.setdefault('untyped_kinds', collections.Counter())[uk] += 1
            if cls == 'typed':
                bare = spelled[7:] if spelled.startswith('struct ') else spelled
                if bare != spelled and unit.T.record(bare) == key:
                    spelled = bare
                typed.setdefault(key, spelled)
            src_edits.append((cls, rhs, cast))
        if len(typed) > 1:
            why = 'sources_disagree'
            row['records'] = sorted(typed)
        elif not typed:
            why = 'no_typed_source'
        elif row['sources']['constant_address']:
            why = 'constant_address_source'
        elif row['sources']['scalar'] and not allow_scalar:
            why = 'scalar_reuse'
        elif key == 'ObjectNodeHeader' and row.get('untyped_kinds', {}).get('node_body'):
            why = 'sources_disagree'        # a node header and a node body are different objects
            row['records'] = ['ObjectNodeHeader', 'node body']
        elif not allow_untyped and any(k not in ('node_body', 'candidate')
                                       for k in row.get('untyped_kinds', {})):
            # a void * parameter, call return or member load of unproven identity also reaches the local (R3)
            why = 'untyped_source'
        key = next(iter(typed)) if len(typed) == 1 else None
        name = typed.get(key)
        row['record'] = name
        edits, added = [], 0
        if not why:
            for cls, rhs, cast in src_edits:
                if cls == 'typed' and cast is not None:
                    e = strip_cast_edit(cast, text, parents)
                    if e is None:
                        why = 'source_in_macro'
                        break
                    edits.append(e)
                elif cls in ('scalar', 'node_link') and cast is None:
                    continue    # an implicit integer store keeps its conversion (and its warning group)
                elif cls in ('byte', 'scalar'):
                    if cast is not None:
                        m = re.match(r'\(\s*[^()]*?\*\s*\)', text[A.node_range(cast, text)[0]:]) \
                            if A.node_range(cast, text) else None
                        if not m:
                            why = 'source_in_macro'
                            break
                        s = A.node_range(cast, text)[0]
                        edits.append((s, s + m.end(), '(%s *)' % name))
                    else:
                        r = A.node_range(A.strip_implicit(rhs), text)
                        if r is None:
                            why = 'source_in_macro'
                            break
                        value = text[r[0]:r[1]]
                        if A.strip_implicit(rhs).get('kind') not in A.POSTFIX_KINDS:
                            value = '(' + value + ')'
                        edits.append((r[0], r[1], '(%s *)%s' % (name, value)))
                        added += 1
        if not why:
            for ref in uses:
                kind, detail = use_of(unit, ref, parents)
                vr = A.node_range(ref, text)
                if kind == 'refuse' and not (view and detail == 'use_MemberExpr'):
                    why = detail
                    break
                if vr is None and kind in ('arith', 'subscript', 'deref'):
                    why = 'use_in_macro'
                    break
                v = text[vr[0]:vr[1]] if vr else ''
                if kind == 'cast' and A.node_range(detail, text) is None:
                    continue        # a cast inside a macro expansion (NODE_HEADER(x)) stays valid for any pointer
                if view and kind == 'refuse' and detail == 'use_MemberExpr':
                    kind = 'member'
                if view and kind == 'neutral' and detail == 'flow':
                    why = 'passed_as_view'
                    break
                if view and kind in ('arith', 'subscript', 'deref'):
                    why = 'view_arithmetic'
                    break
                if kind == 'member':
                    q = up(parents, up(parents, ref)[1])[1]
                    got = access_leaf(unit, q, parents) if q is not None and q.get('isArrow') else None
                    if got is None:
                        why = 'view_member_unmapped'
                        break
                    leaf, off, lt = got
                    path = next((pth for pth, t2, _ in unit.leaves_at(key, off)
                                 if not F.PAD.search(pth) and unit.canon(t2) == unit.canon(lt)
                                 and unit.volatile(t2) == unit.volatile(lt)
                                 and not path_crosses_union(unit, key, pth)), None)
                    lr = A.node_range(leaf, text)
                    if path is None or lr is None or vr is None:
                        why = 'view_member_unmapped'
                        row['detail'] = '%s at 0x%X (%s)' % (q.get('name'), off, lt)
                        break
                    edits.append((lr[0], lr[1], v + '->' + path))
                    continue
                if kind == 'cast':
                    if unit.record_of_pointer(C.qtype(detail)) == key and unit.canon(C.qtype(detail)).count('*') == 1:
                        e = strip_cast_edit(detail, text, parents)
                        if e is None:
                            why = 'use_in_macro'
                            break
                        edits.append(e)
                elif kind == 'implicit':
                    if unit.record_of_pointer(C.qtype(detail)) != key:
                        row.setdefault('conversions', []).append('%s at line %s' % (C.qtype(detail), ref.get('_l')))
                        if not cast_other or vr is None or '(*' in C.qtype(detail):
                            why = 'implicit_to_other_pointer'
                            row['detail'] = '%s at line %s' % (C.qtype(detail), ref.get('_l'))
                            break
                        # The void * local hid this conversion; with --cast-other-pointer it is spelled, as
                        # `(void *)` when the target record is incomplete (a prototype-scope `struct X` cannot
                        # be named compatibly).
                        target = C.qtype(detail).strip()
                        if unit.record_of_pointer(target) is None:
                            target = 'void *'
                        edits.append((vr[0], vr[0], '(%s)' % target))
                        added += 1
                elif kind == 'compare':
                    if unit.canon(C.qtype(detail)) != 'void*' and detail.get('kind') == 'DeclRefExpr' and \
                            (detail.get('referencedDecl') or {}).get('id') not in decls and \
                            named_record(unit, C.qtype(detail)) != key:
                        why = 'pointer_compare'
                        break
                elif kind == 'arith':
                    q, side = detail
                    other = A.kids(q)[1 if side == 'left' else 0]
                    k = C.int_value(other)
                    qr = A.node_range(q, text)
                    orng = A.node_range(other, text)
                    if qr is None or orng is None:
                        why = 'use_in_macro'
                        break
                    slot = consumer_slot(unit, q, parents)
                    outer, holder = up(parents, q)
                    paren = outer is not q
                    hdr_cast = None
                    if slot == 'cast':
                        hc = up(parents, q)[1]
                        if hc is not None and unit.record_of_pointer(C.qtype(hc)) == 'ObjectNodeHeader' \
                                and unit.canon(C.qtype(hc)).count('*') == 1:
                            hdr_cast = A.node_range(hc, text)
                    if q.get('opcode') == '-' and k == HEADER_SIZE and key != 'ObjectNodeHeader' and hdr_cast:
                        # `(ObjectNodeHeader *)(x - 0x20)` is NODE_HEADER(x): the cast goes with the arithmetic
                        edits.append((hdr_cast[0], hdr_cast[1], 'NODE_HEADER(%s)' % v))
                        added -= 1
                    elif q.get('opcode') == '-' and k == HEADER_SIZE and key != 'ObjectNodeHeader' \
                            and slot in ('void', 'header', 'cast'):
                        edits.append((qr[0], qr[1], 'NODE_HEADER(%s)' % v))
                    elif q.get('opcode') == '+' and k == HEADER_SIZE and key == 'ObjectNodeHeader' \
                            and slot in ('void', 'cast'):
                        edits.append((qr[0], qr[1], 'NODE_BODY(%s)' % v))
                    else:
                        expr = text[qr[0]:qr[1]]
                        rel_a, rel_b = vr[0] - qr[0], vr[1] - qr[0]
                        new = expr[:rel_a] + '(u8 *)' + v + expr[rel_b:]
                        if not byte_local and slot not in ('void', 'byte', 'cast', 'arith'):
                            new = '(void *)(' + new + ')'
                        elif not paren and slot != 'void':
                            new = '(' + new + ')'
                        edits.append((qr[0], qr[1], new))
                        added += 1 if (byte_local or slot in ('void', 'byte', 'cast', 'arith')) else 2
                elif kind == 'subscript':
                    if not byte_local:
                        why = 'subscript'
                        break
                    edits.append((vr[0], vr[1], '((u8 *)%s)' % v))
                    added += 1
                elif kind == 'deref':
                    if not byte_local:
                        why = 'dereference'
                        break
                    edits.append((vr[0], vr[1], '(u8 *)' + v))
                    added += 1
        if not why:
            d = decl_edit(unit, decl, parents, text, name)
            if isinstance(d, str):
                why = d
            else:
                edits.insert(0, d)
        if view:
            casts += sum(1 for _, rhs, c in src_edits if c is not None)
        if not why and not casts:
            why = 'no_casts_on_var'
        row['sources'] = dict(row['sources'])
        if 'untyped_kinds' in row:
            row['untyped_kinds'] = dict(row['untyped_kinds'])
        row['added_casts'] = added
        row['verdict'] = 'planned' if not why else 'refused'
        row['reason'] = why or ''
        rows.append(row)
        if not why:
            plans.append({'file': file, 'func': fn['name'], 'var': var, 'type': name, 'record': key,
                          'edits': sorted(set(edits)), 'added_casts': added, 'casts_on_var': casts,
                          'scalar_reuse': row['sources'].get('scalar', 0)})
    return plans, rows


def plan_tu(args):
    root, rel, recipe, files, allow_scalar, cast_other, allow_untyped = args
    try:
        unit, error = A.clang_unit(root, rel, recipe)
    except Exception as exc:  # noqa: BLE001 - recorded per TU
        return {'tu': rel, 'error': str(exc)[-300:], 'plans': [], 'rows': []}
    if unit is None:
        return {'tu': rel, 'error': error, 'plans': [], 'rows': []}
    plans, rows = [], []
    for file, fn in unit.functions(set(files)):
        p, r = plan_function(unit, file, fn, unit.text(file), allow_scalar, cast_other, allow_untyped)
        plans.extend(p)
        rows.extend(r)
    return {'tu': rel, 'error': error, 'plans': plans, 'rows': rows}


def plan(root, files, workers=2, allow_scalar=False, tus=None, cast_other=False, allow_untyped=False):
    """Plans and census rows for `files` (each local once even when several TUs compile its file)."""
    if tus is None:
        tus, _ = F.physical_for(root, files)
    jobs = [(str(root), tu, recipe, sorted(files), allow_scalar, cast_other, allow_untyped)
            for tu, recipe in sorted(tus.items())]
    plans, rows, errors, seen = [], [], [], set()
    pool = ProcessPoolExecutor(max_workers=workers) if workers > 1 else F._Inline()
    with pool as ex:
        for res in ex.map(plan_tu, jobs, chunksize=2):
            if res['error']:
                errors.append((res['tu'], res['error']))
            for r in res['rows']:
                k = (r['file'], r['func'], r['var'])
                if k in seen:
                    continue
                seen.add(k)
                rows.append(r)
                plans.extend(p for p in res['plans'] if (p['file'], p['func'], p['var']) == k)
    return plans, rows, errors


def apply_text(text, edits):
    """Apply (start, end, replacement) edits; overlapping edits raise ValueError."""
    edits = sorted(set(map(tuple, edits)))
    for (a1, b1, _), (a2, _, _) in zip(edits, edits[1:]):
        if a2 < b1:
            raise ValueError('overlapping edits at %d' % a2)
    for a, b, rep in reversed(edits):
        text = text[:a] + rep + text[b:]
    return text


# ---------------------------------------------------------------------- fold

def path_crosses_union(unit, key, path):
    """True when a member path from record `key` passes through a union (or names a signedness view)."""
    if SIGN_VIEW.search(path):
        return True
    lay = unit.layouts.get(key)
    if not lay:
        return True
    if lay.get('kind') == 'union':
        return True
    kids = lay['kids']
    for comp in path.split('.'):
        name = re.sub(r'\[\d+\]$', '', comp)
        node, crossed = _member(kids, name)
        if node is None:
            return True
        if crossed:
            return True
        t = re.sub(r'\s*\[\d*\]$', '', node['type'].strip())
        if t.startswith('union'):
            return True
        rec = unit.T.record(t) if not unit.T.resolve(t).endswith('*') else None
        if rec and unit.layouts.get(rec, {}).get('kind') == 'union':
            return True
        kids = node['kids'] or (unit.layouts.get(rec, {}).get('kids') if rec else []) or []
    return False


def _member(kids, name):
    """(node, crossed an anonymous union) for member `name` among `kids` (searching anonymous members)."""
    for node in kids:
        if node['name'] == name:
            return node, False
    for node in kids:
        if not node['name']:
            found, crossed = _member(node['kids'], name)
            if found is not None:
                return found, crossed or node['type'].strip().startswith('union')
    return None, False


def fold_sites(root, file, tus, kept, workers=1):
    """cast_fold sites of `file` whose base is a kept local, minus union/sign-view paths.

    Returns (sites, refusal counter)."""
    wanted = {(p['func'], p['var']) for p in kept}
    sites, refused = [], collections.Counter()
    for tu, recipe in sorted(tus.items()):
        unit, error = A.clang_unit(root, tu, recipe)
        if unit is None:
            refused['parse_error'] += 1
            continue
        for f, fn in unit.functions({file}):
            if not any(fn['name'] == func for func, _ in wanted):
                continue
            vars_ = {v for func, v in wanted if func == fn['name']}
            s, r = F.scan_function(unit, f, fn)
            refused.update(r)
            for site in s:
                base = re.match(r'\(?\s*([A-Za-z_]\w*)', site['new'])
                if not base or base.group(1) not in vars_:
                    continue
                if path_crosses_union(unit, site['record'], site['path']):
                    refused['union_or_sign_view_path'] += 1
                    refused['union_path:%s.%s' % (site['record'], site['path'])] += 1
                    continue
                sites.append(site)
        break       # one TU parse is enough for one file's text
    return F.select_edits(sites).get(file, []), refused


def node_body_sites(root, file, tus, kept):
    """NODE_BODY rewrites of `x = (u8 *)h + 0x20` / `x = h + 0x20` stores into kept body locals (run after the
    folds, so the header expression is already folded; a macro argument is never folded)."""
    wanted = {(p['func'], p['var']) for p in kept if p['record'] != 'ObjectNodeHeader'}
    edits = []
    for tu, recipe in sorted(tus.items()):
        unit, error = A.clang_unit(root, tu, recipe)
        if unit is None:
            continue
        text = unit.text(file)
        for f, fn in unit.functions({file}):
            parents = {}
            for n, p in A.walk(fn):
                parents[id(n)] = p
            for n, p in A.walk(fn):
                if n.get('kind') != 'BinaryOperator' or n.get('opcode') != '=':
                    continue
                lhs = A.strip_parens(A.kids(n)[0])
                if lhs.get('kind') != 'DeclRefExpr' or (fn['name'], lhs.get('name') or
                                                        (lhs.get('referencedDecl') or {}).get('name')) not in wanted:
                    continue
                body = node_body_source(unit, A.kids(n)[1], text)
                if body:
                    edits.append(body[0])
        break
    return edits


# ---------------------------------------------------------------------- proof

class Prover:
    def __init__(self, root, file, port=None):
        sys.path.insert(0, str(Path(root) / 'tools'))
        import layout_compile_identity as L
        self.L = L
        self.root = Path(root)
        self.file = file
        self.port = port
        self.tus, _ = F.physical_for(root, [file])
        self.before = {tu: L.capture_one(root, tu, r) for tu, r in self.tus.items()}
        self.lint_before = self.lint() if port else None

    def identical(self):
        import cast_wave as W
        for tu, r in self.tus.items():
            try:
                now = self.L.capture_one(self.root, tu, r)
            except Exception as exc:  # noqa: BLE001 - a compile failure is a difference
                return False, '%s: %s' % (tu, str(exc)[-200:])
            if not W.identical(self.before[tu], now):
                return False, tu
        return True, ''

    def lint(self):
        import lint_closure as LC
        findings, failures = LC.lint_tree(self.root, sorted(self.tus), self.port, jobs=2)
        return LC.group_sites(findings), failures

    def warning_rises(self):
        """Function names (of this file) whose warning groups rise, plus 'compile' on a new failure."""
        if not self.port:
            return set()
        (b, bf), (a, af) = self.lint_before, self.lint()
        bad = set()
        for key, row in a.items():
            if row[0] > b.get(key, (0,))[0]:
                bad.add(key[1] or '')
        if len(af) > len(bf):
            bad.add('compile')
        return bad


def debt_by_function(rel, text):
    import debt_check as D
    res = D.analyze(rel, text)
    return {k: dict(v['counts']) for k, v in res['scopes'].items()}


def rising_functions(rel, before, after):
    """{function key: {class: (before, after)}} for every class that rises."""
    b, a = debt_by_function(rel, before), debt_by_function(rel, after)
    bad = {}
    for key, counts in a.items():
        old = b.get(key, {})
        up_ = {k: (old.get(k, 0), n) for k, n in counts.items() if n > old.get(k, 0)}
        if up_:
            bad[key] = up_
    return bad


def casts(rel, text):
    return sum(v.get('pointer_casts', 0) for v in debt_by_function(rel, text).values())


def func_of_key(key):
    return str(key).split('#')[0]


def prove_file(root, file, plans, port, log, keep_failed=None):
    """Apply and prove one file's plans; returns a receipt row.  The file holds the last proven text."""
    path = Path(root) / file
    original = path.read_text()
    prover = Prover(root, file, port)
    result = {'file': file, 'casts_before': casts(file, original), 'kept': [], 'dropped': {}, 'folds': 0}
    active = list(plans)

    def retype_text(chosen):
        return apply_text(original, [e for p in chosen for e in p['edits']])

    def prove(text):
        path.write_text(text)
        return prover.identical()

    for attempt in range(6):
        if not active:
            break
        # 1. retypes
        try:
            text = retype_text(active)
            ok, why = prove(text)
        except ValueError as exc:
            ok, why = False, str(exc)
        if not ok:
            log('%s: retypes together not identical (%s); one at a time' % (file, why))
            single = []
            for p in active:
                try:
                    ok1, why1 = prove(retype_text([p]))
                except ValueError as exc:
                    ok1, why1 = False, str(exc)
                if ok1:
                    single.append(p)
                else:
                    result['dropped']['%s:%s' % (p['func'], p['var'])] = 'retype_not_identical'
            active = single
            if not active:
                break
            try:
                text = retype_text(active)
                ok, why = prove(text)
            except ValueError as exc:
                ok, why = False, str(exc)
            if not ok:
                for p in active[1:]:
                    result['dropped']['%s:%s' % (p['func'], p['var'])] = 'retype_combination_not_identical'
                active = active[:1]
                text = retype_text(active)
                ok, why = prove(text)
                if not ok:
                    break
        proven = text
        # 2. folds (two passes)
        nfold = 0
        for _ in range(2):
            sites, refused = fold_sites(root, file, prover.tus, active)
            if not nfold:
                result['fold_refusals'] = collections.Counter(refused)
            if not sites:
                break
            ok, _ = prove(apply_text(proven, [(s['start'], s['end'], s['new']) for s in sites]))
            if ok:
                proven = path.read_text()
                nfold += len(sites)
                continue
            # split per function, then per site
            by_func = collections.defaultdict(list)
            for s in sites:
                by_func[s['func']].append(s)
            good = []
            for func, group in by_func.items():
                ok, _ = prove(apply_text(proven, [(s['start'], s['end'], s['new']) for s in good + group]))
                if ok:
                    good += group
                    continue
                for s in group:
                    ok, _ = prove(apply_text(proven, [(x['start'], x['end'], x['new']) for x in good + [s]]))
                    if ok:
                        good.append(s)
                    else:
                        result.setdefault('fold_not_identical', []).append('%s:%s' % (s['func'], s['old'][:60]))
            path.write_text(proven := apply_text(proven, [(s['start'], s['end'], s['new']) for s in good]))
            nfold += len(good)
            break
        path.write_text(proven)
        bodies = node_body_sites(root, file, prover.tus, active)
        if bodies:
            ok, _ = prove(apply_text(proven, bodies))
            if ok:
                proven = path.read_text()
                result['node_body'] = len(bodies)
            path.write_text(proven)
        # 3. debt and warnings
        rises = rising_functions(file, original, proven)
        bad = {func_of_key(k) for k in rises}
        warn = prover.warning_rises()
        if rises or warn:
            log('%s: debt rises %s; warning rises %s' % (file, sorted(rises.items()), sorted(warn)))
            result.setdefault('rises', []).append({'debt': {k: v for k, v in rises.items()}, 'warnings': sorted(warn)})
            if keep_failed:
                (Path(keep_failed) / (Path(file).name + '.attempt%d.c' % attempt)).write_text(proven)
        result['folds_tried'] = nfold
        if 'compile' in warn:
            bad |= {p['func'] for p in active}
        bad |= {w for w in warn if w}
        drop = [p for p in active if p['func'] in bad]
        if not drop:
            ok, why = prover.identical()
            if not ok:
                log('%s: final state not identical (%s); restoring' % (file, why))
                path.write_text(original)
                active = []
                break
            result['kept'] = [{'func': p['func'], 'var': p['var'], 'type': p['type'],
                               'scalar_reuse': p['scalar_reuse']} for p in active]
            result['folds'] = nfold
            break
        for p in drop:
            result['dropped']['%s:%s' % (p['func'], p['var'])] = 'debt_or_warning_rise'
        active = [p for p in active if p not in drop]
        path.write_text(original)
    if not result['kept']:
        path.write_text(original)
    final = path.read_text()
    result['casts_after'] = casts(file, final)
    if 'fold_refusals' in result:
        result['fold_refusals'] = dict(result['fold_refusals'])
    return result


# ---------------------------------------------------------------------- driver

def files_of(root, args):
    if args.file:
        return sorted(args.file)
    return sorted(p.relative_to(root).as_posix() for p in (root / args.folder).rglob('*.c'))


def write_rows(out, rows):
    with open(out / 'candidates.jsonl', 'w') as fh:
        for r in rows:
            fh.write(json.dumps(r, sort_keys=True) + '\n')
    reasons = collections.Counter()
    held = collections.Counter()
    for r in rows:
        reasons[r['reason'] or 'planned'] += 1
        held[r['reason'] or 'planned'] += r['casts_on_var']
    return {'locals': len(rows), 'by_reason': dict(reasons.most_common()),
            'casts_on_var_by_reason': dict(held.most_common())}


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('mode', choices=('census', 'apply'))
    ap.add_argument('--root', type=Path, default=HERE.parents[1])
    ap.add_argument('--folder', default='src')
    ap.add_argument('--file', nargs='*', default=[])
    ap.add_argument('--only', nargs='*', default=[], help='FUNC:VAR locals to apply (default: every planned one)')
    ap.add_argument('--skip-list', type=Path, help='files other lanes own (one per line)')
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--port', help='native port tree for the GCC warning gate (lint_closure flags)')
    ap.add_argument('--allow-scalar-reuse', action='store_true')
    ap.add_argument('--allow-untyped', action='store_true',
                    help='accept void * sources of unproven identity (parameters, call returns, member loads)')
    ap.add_argument('--cast-other-pointer', action='store_true',
                    help='spell a conversion the void * local hid (to another record pointer) as an explicit cast')
    ap.add_argument('--workers', type=int, default=2)
    ap.add_argument('--dry-run', action='store_true', help='prove, report, then restore every file')
    args = ap.parse_args(argv)
    root = args.root.resolve()
    args.out.mkdir(parents=True, exist_ok=True)
    logf = open(args.out / 'trial.log', 'a')

    def log(msg):
        line = time.strftime('%H:%M:%S ') + msg
        print(line, flush=True)
        logf.write(line + '\n')
        logf.flush()

    skip = set()
    if args.skip_list:
        skip = {l.strip() for l in args.skip_list.read_text().splitlines() if l.strip()}
    files = [f for f in files_of(root, args) if f not in skip]
    plans, rows, errors = plan(root, files, args.workers, args.allow_scalar_reuse,
                               cast_other=args.cast_other_pointer, allow_untyped=args.allow_untyped)
    for tu, err in errors:
        log('parse error %s: %s' % (tu, err))
    summary = write_rows(args.out, rows)
    summary['errors'] = errors[:20]
    if args.mode == 'census':
        (args.out / 'summary.json').write_text(json.dumps(summary, indent=2) + '\n')
        print(json.dumps({k: summary[k] for k in ('locals', 'by_reason')}))
        return 0
    if args.only:
        want = set(args.only)
        plans = [p for p in plans if '%s:%s' % (p['func'], p['var']) in want]
    originals = {f: (root / f).read_text() for f in {p['file'] for p in plans}}
    signal.signal(signal.SIGTERM, lambda signum, frame: sys.exit(128 + signum))
    receipt = []
    try:
        for file in sorted(originals):
            mine = [p for p in plans if p['file'] == file]
            log('%s: %d planned locals' % (file, len(mine)))
            res = prove_file(root, file, mine, args.port, log, args.out)
            log('%s: kept %d, folds %d, casts %d -> %d' % (file, len(res['kept']), res['folds'],
                                                             res['casts_before'], res['casts_after']))
            receipt.append(res)
    except BaseException:
        for f, t in originals.items():
            (root / f).write_text(t)
        raise
    finally:
        if args.dry_run:
            for f, t in originals.items():
                (root / f).write_text(t)
    reasons = collections.Counter()
    for res in receipt:
        for r in res.get('fold_refusals', {}).items():
            reasons[r[0]] += r[1]
    with open(args.out / 'fold_refusals.tsv', 'w') as fh:
        fh.write('reason\tsites\n')
        for k, n in reasons.most_common():
            fh.write('%s\t%d\n' % (k, n))
    summary['receipt'] = receipt
    (args.out / 'receipt.json').write_text(json.dumps(summary, indent=2, default=str) + '\n')
    print(json.dumps({'files': len(receipt), 'kept': sum(len(r['kept']) for r in receipt),
                      'casts_before': sum(r['casts_before'] for r in receipt),
                      'casts_after': sum(r['casts_after'] for r in receipt)}))
    return 0


if __name__ == '__main__':
    sys.exit(main())
