#!/usr/bin/env python3
"""Parameter retype for refused prototypes: the parameter sibling of the cast wave.

    param_retype.py census --scope src/town src/dungeon/actor ... --out DIR [--symbols S...] [--exclude P...]
    param_retype.py apply  --scope ... --out DIR [--symbols S...] [--exclude P...] [--census DIR/census.tsv]
                           [--max-closure 400] [--workers 4] [--no-decls]

A callee whose real prototype tools/proto cannot publish because a caller passes a value of another
type ('u8 *' to 's32 *', 'int' to 'void *', 'u8 *' to 'Rec_D_80082E80 *', ...) usually carries a
placeholder parameter type from the original decompiler output.  On this MIPS target every pointer
and int is one 32-bit register, so retyping a parameter (or the caller's holder) is normally
byte-identical, and the body then reads fields through the typed parameter instead of casts.

census  (read-only)
  1. tools/proto/prototypes.candidates proposes every declaration in --scope; each source site is
     rewritten in a sibling temp file and compiled with the strict native check (clang mipsel,
     -Werror=incompatible-pointer-types -Werror=int-conversion, as tools/proto/probe_sources); header
     sites are probed in their calling consumers.  A site that adds an error is a refusal.
  2. For every refused (callee, parameter): the definition's current type, the types callers pass
     (clang AST of each caller, with counts and the holder of each failing argument), how the body uses
     the parameter (member offsets through its record, record casts, raw/byte arithmetic, integer use,
     onward conversions), the candidate types that would satisfy every caller, and a proposal:
        callee          retype the definition's parameter (every caller already passes a compatible value)
        callee+callers  retype the parameter and the failing callers' holders (locals / own parameters)
        callers         keep the parameter, retype or un-cast the failing callers' holders
        none            no type satisfies the callers without a new cast (reason recorded)
  Output: census.tsv (one row per refused parameter), sites.tsv (one row per failing argument),
  refusals.tsv (probe result per refused declaration site), probes.jsonl (every probe, with its edit),
  holds.tsv (sites tools/proto cannot even propose: binding, private types, SDK/no definition), summary.json.

apply  (opt-in; writes sources in --root, which must be a private lane root)
  Families are processed one at a time on the current text (one callee and its failing holders):
    - the definition's parameter is respelled, member accesses through its old record are renamed to the
      new record's member at the same offset and type (exact type; constant-store width-only like
      cast_fold), explicit casts to the new type are dropped (`((X *)p)->f` -> `p->f`); every typed
      declaration of the callee (owner/folder header or source) is respelled the same way;
    - each failing caller holder is retyped the same way (or its redundant argument cast dropped);
    - a type header is added where the new type is not yet visible (shared include/ headers only);
    - cast_fold then folds raw `*(T *)((u8 *)p + K)` sites inside the touched functions.
  No call-site cast is ever added.  A family is rolled back (and the reason recorded) when:
    any touched function's lexical debt rises (tools/lint/debt_check classes, so casts never increase),
    the strict native check gains an error in any TU of the consumer closure,
    any registered physical TU whose dependency closure contains a changed file is not raw-, canonical-
    assembly- and canonical-object-identical to its original (tu_identity / layout_compile_identity),
    or the closure is larger than --max-closure.
  Then the prototypes for the accepted callees are proposed again (prototypes.candidates) and each
  declaration site is applied with the same closure identity + native check, one site at a time.
  Output: families.jsonl (verdict per family, with the edits kept), decls.tsv, receipt.jsonl
  (per proven TU), summary.json, changed_files.txt.  Nothing is staged or committed.
"""
from __future__ import annotations

import argparse
import collections
from concurrent.futures import ProcessPoolExecutor, ThreadPoolExecutor
from dataclasses import asdict
import difflib
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import time

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path[:0] = [str(HERE), str(HERE.parent), str(ROOT), str(HERE.parent / 'lint')]
import cast_ast as A  # noqa: E402
import field_census as C  # noqa: E402

NATIVE = ['clang', '--target=mipsel-unknown-none', '-fsyntax-only', '-std=gnu89', '-Wno-everything',
          '-Werror=incompatible-pointer-types', '-Werror=int-conversion', '-ferror-limit=0', '-Iinclude']
DIAG = re.compile(r'(?m)^(.*?):(\d+):(\d+): (?:fatal )?error: (.*)$')
PASSING = re.compile(r"passing '([^']*)'(?: \(aka '[^']*'\))? to parameter of type '([^']*)'")
INT_SIZES = {'char': 1, 'signed char': 1, 'unsigned char': 1, '_Bool': 1, 'short': 2, 'unsigned short': 2,
             'int': 4, 'unsigned int': 4, 'long long': 8, 'unsigned long long': 8}
GENERATED = re.compile(r'^(?:S_(?:func_)?[0-9A-Fa-f]{8}\w*|Rec_\w+|Row_\w+|R\d+_\w+)$')
PAD = re.compile(r'(?:^|\.)(?:pad|_pad|padding|unused_pad)\w*(?:\[|$|\.)', re.I)
STATEMENT_PARENTS = {'CompoundStmt', 'IfStmt', 'ForStmt', 'WhileStmt', 'DoStmt', 'CaseStmt', 'DefaultStmt',
                     'LabelStmt', 'SwitchStmt'}
SDK = 'SDK stand-in'


# ----------------------------------------------------------------------------------- type helpers

def decay(c):
    """Canonical spelling with arrays decayed to pointers ('u8[4]' -> 'unsigned char*')."""
    c = (c or '').replace(' ', ' ').strip()
    m = re.match(r'^(.*?)\s*\[\d*\]$', c)
    return (m.group(1).strip() + '*') if m else c


def is_ptr(c):
    return c.endswith('*')


def assignable(dst, src, null=False):
    """Can a value of canonical type `src` initialise a `dst` under the strict native check?

    Mirrors clang's -Werror=incompatible-pointer-types / -Werror=int-conversion: pointer <-> integer
    needs a null constant, distinct object pointers are incompatible unless one is void * or they differ
    only in the signedness of a same-width integer pointee (-Wpointer-sign, not an error)."""
    dst, src = decay(dst), decay(src)
    if dst == src:
        return True
    if is_ptr(dst):
        if not is_ptr(src):
            return null
        if dst == 'void*' or src == 'void*':
            return True
        pd, ps = dst[:-1].replace('const ', '').strip(), src[:-1].replace('const ', '').strip()
        if pd == ps:
            return True
        return pd in INT_SIZES and ps in INT_SIZES and INT_SIZES[pd] == INT_SIZES[ps]
    if is_ptr(src):
        return False
    if dst.startswith('rec:') or src.startswith('rec:'):
        return False
    return True


def type_name(spelling):
    """'struct Foo *' / 'Foo *' / 'const Foo *' -> 'Foo' (the record or typedef name), else ''."""
    s = re.sub(r'\b(?:const|volatile)\b', '', spelling or '').replace('*', ' ').split()
    if s[:1] and s[0] in ('struct', 'union'):
        s = s[1:]
    return s[0] if len(s) == 1 and re.match(r'^[A-Za-z_]\w*$', s[0]) else ''


def spelled(spelling):
    """Normalised C spelling of a pointer type: 'TileObject *', 's32', 'struct Foo *'."""
    t = re.sub(r'\s+', ' ', (spelling or '').strip())
    core = t.rstrip('* ').strip()
    n = t.count('*')
    return core + (' ' + '*' * n if n else '')


def strength(name):
    """Rank a record/typedef name: shared readable types first, generated census views last."""
    return 0 if name and not GENERATED.match(name) else 1


# ------------------------------------------------------------------------------------ AST helpers

def parents_of(fn):
    parents, nodes = {}, []
    for n, p in A.walk(fn):
        parents[id(n)] = p
        nodes.append(n)
    return parents, nodes


def up(parents, node):
    p = parents.get(id(node))
    while p is not None and p.get('kind') == 'ParenExpr':
        node, p = p, parents.get(id(p))
    return node, p


def callee_name(call):
    c = A.strip_implicit(A.kids(call)[0]) if A.kids(call) else None
    if not c or c.get('kind') != 'DeclRefExpr':
        return None
    return (c.get('referencedDecl') or {}).get('name')


def prototyped(call):
    t = C.qtype(A.kids(call)[0]) if A.kids(call) else ''
    return not re.search(r'\(\*\)\(\)$|\(\)$', t.strip())


def typedef_files(unit):
    out = getattr(unit, '_typedef_files', None)
    if out is None:
        out = {}
        for d in unit.tree.get('inner', []):
            if d.get('kind') == 'TypedefDecl' and d.get('_f'):
                out.setdefault(d['name'], d['_f'])
            elif d.get('kind') == 'RecordDecl' and d.get('name') and d.get('completeDefinition') and d.get('_f'):
                out.setdefault(d['tagUsed'] + ' ' + d['name'], d['_f'])
        unit._typedef_files = out
    return out


def type_home(unit, spelling):
    """Header that defines the named type of `spelling` in this unit ('' for builtins, None if unknown)."""
    name = type_name(spelling)
    if not name or name in ('void', 'char', 'int', 'short', 'long', 'unsigned', 'signed'):
        return ''
    files = typedef_files(unit)
    tagged = re.search(r'\b(struct|union)\s+(\w+)', spelling or '')
    f = files.get(tagged.group(1) + ' ' + tagged.group(2)) if tagged else files.get(name)
    return f


def find_function(unit, file, name):
    for f, fn in unit.functions({file}):
        if fn.get('name') == name:
            return fn
    return None


def params_of(fn):
    return [x for x in A.kids(fn) if x.get('kind') == 'ParmVarDecl']


class Target:
    """The type a variable is retyped to: spelling, canonical form, record key and the unit that lays it out."""

    def __init__(self, unit, spelling):
        self.unit = unit
        self.spelling = spelled(spelling)
        self.canon = decay(unit.canon(self.spelling))
        self.key = unit.record_of_pointer(self.spelling)
        self.home = type_home(unit, self.spelling)

    def describe(self):
        return self.spelling


# ------------------------------------------------------------------------------ variable retype planner

def access_leaf(unit, member, parents, key):
    """(leaf node, byte offset, leaf type, store_only) of `base->m(.n)*` starting at an arrow MemberExpr."""
    off = A.member_offset(unit, key, member.get('name'))
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
    outer, holder = up(parents, leaf)
    store = (holder is not None and holder.get('kind') == 'BinaryOperator' and holder.get('opcode') == '='
             and A.kids(holder)[0] is outer and (parents.get(id(holder)) or {}).get('kind') in STATEMENT_PARENTS)
    return leaf, off, C.qtype(leaf), store


def map_member(unit, target, off, leaf_type, store, old_path=None):
    """Member path of `target` at byte offset `off` giving the same access as `leaf_type`, or None."""
    tu = target.unit
    want = decay(unit.canon(leaf_type))
    vol = unit.volatile(leaf_type)
    cands = [(p, t) for p, t, _ in tu.leaves_at(target.key, off) if not PAD.search(p)]
    if old_path and any(p == old_path and decay(tu.canon(t)) == want for p, t in cands):
        return old_path
    for p, t in cands:
        if decay(tu.canon(t)) == want and tu.volatile(t) == vol:
            return p
    if store and want in INT_SIZES:
        for p, t in cands:
            c = decay(tu.canon(t))
            if c in INT_SIZES and INT_SIZES[c] == INT_SIZES[want] and tu.volatile(t) == vol:
                return p
    return None


def member_path_text(unit, leaf, ref_node, text):
    """Spelled member path of a leaf (`a.b`) below the arrow on ref_node, for unchanged-path detection."""
    rng, rr = A.node_range(leaf, text), A.node_range(ref_node, text)
    if rng is None or rr is None:
        return None
    s = text[rng[0]:rng[1]]
    i = s.find('->')
    return re.sub(r'\s+', '', s[i + 2:]) if i >= 0 else None


def cast_removal_edit(parents, cast, ref, text):
    """Replace `(X *)v` (with grouping parens when they only grouped the cast) by `v`."""
    rng, vr = A.node_range(cast, text), A.node_range(ref, text)
    if rng is None or vr is None:
        return None
    outer, holder = cast, parents.get(id(cast))
    while holder is not None and holder.get('kind') == 'ParenExpr':
        outer, holder = holder, parents.get(id(holder))
    orng = A.node_range(outer, text) or rng
    if outer is not cast and not (orng[0] and (text[orng[0] - 1].isalnum() or text[orng[0] - 1] == '_')) \
            and (holder or {}).get('kind') != 'UnaryExprOrTypeTraitExpr':
        rng = orng
    return (rng[0], rng[1], text[vr[0]:vr[1]])


def plan_retype(unit, file, fn, decl, target, edit_decl=True):
    """Edits that retype one variable (parameter or local) of `fn` to `target`, or a refusal reason.

    Returns dict(edits=[(start, end, text)], removed=casts removed, renamed=member renames,
    uses=Counter of use kinds) or dict(refused=reason, uses=...)."""
    text = unit.text(file)
    parents, nodes = parents_of(fn)
    old = C.qtype(decl)
    old_c = decay(unit.canon(old))
    old_key = unit.record_of_pointer(old)
    new_c = target.canon
    uses = collections.Counter()
    edits, removed, renamed = [], 0, 0
    did = decl.get('id')
    refs = [n for n in nodes if n.get('kind') == 'DeclRefExpr' and (n.get('referencedDecl') or {}).get('id') == did]

    def refuse(why):
        return {'refused': why, 'uses': uses}

    if decl.get('kind') == 'VarDecl' and decl.get('init') and A.kids(decl):
        rhs = A.kids(decl)[0]
        ok = value_into(unit, rhs, target, text, edits)
        if ok is None:
            return refuse('initializer_needs_cast')
        removed += ok
    for ref in refs:
        if A.in_macro(ref):
            return refuse('use_in_macro')
        node, p = up(parents, ref)
        k = (p or {}).get('kind')
        if k == 'MemberExpr' and p.get('isArrow'):
            # p->m (array decays never reach here: an arrow base is a pointer rvalue)
            pass
        if k == 'BinaryOperator' and p.get('opcode') == '=' and A.kids(p)[0] is node:
            uses['assigned'] += 1
            ok = value_into(unit, A.kids(p)[1], target, text, edits)
            if ok is None:
                return refuse('assigned_value_needs_cast')
            removed += ok
            continue
        if k == 'UnaryOperator' and p.get('opcode') == '&':
            return refuse('address_taken')
        if k == 'CompoundAssignOperator' or (k == 'UnaryOperator' and p.get('opcode') in ('++', '--')):
            if old_c == new_c:
                continue
            return refuse('modified_arithmetic')
        if not (k == 'ImplicitCastExpr' and p.get('castKind') == 'LValueToRValue'):
            if k == 'UnaryExprOrTypeTraitExpr':
                uses['sizeof'] += 1
                continue
            return refuse('use_' + str(k))
        node, q = up(parents, p)
        qk = (q or {}).get('kind')
        if qk == 'MemberExpr' and q.get('isArrow'):
            uses['member'] += 1
            if not old_key:
                return refuse('member_on_non_record')
            got = access_leaf(unit, q, parents, old_key)
            if got is None:
                return refuse('member_offset_unknown')
            leaf, off, lt, store = got
            if target.key == old_key:
                continue
            if not target.key:
                return refuse('member_access_needs_record')
            path = map_member(unit, target, off, lt, store, member_path_text(unit, leaf, ref, text))
            if path is None:
                return refuse('member_unmapped@0x%X:%s' % (off, unit.canon(lt)))
            if path == member_path_text(unit, leaf, ref, text):
                continue
            lr, vr = A.node_range(leaf, text), A.node_range(ref, text)
            if lr is None or vr is None:
                return refuse('member_in_macro')
            edits.append((lr[0], lr[1], text[vr[0]:vr[1]] + '->' + path))
            renamed += 1
            continue
        if qk == 'CStyleCastExpr':
            cast_t = C.qtype(q)
            cc = decay(unit.canon(cast_t))
            if cc == new_c and is_ptr(new_c) or (cc == new_c and new_c in INT_SIZES):
                e = cast_removal_edit(parents, q, ref, text)
                if e is None:
                    return refuse('cast_in_macro')
                edits.append(e)
                removed += 1
                uses['cast_to_new'] += 1
                continue
            vkey = unit.record_of_pointer(cast_t)
            node2, holder = up(parents, q)
            if vkey and target.key and holder is not None and holder.get('kind') == 'MemberExpr' and holder.get('isArrow'):
                # ((V *)p)->m: rename onto the new record when an exact member exists (one cast fewer)
                got = access_leaf(unit, holder, parents, vkey)
                if got is not None:
                    leaf, off, lt, store = got
                    path = map_member(unit, target, off, lt, store)
                    lr, vr = A.node_range(leaf, text), A.node_range(ref, text)
                    if path is not None and lr is not None and vr is not None:
                        edits.append((lr[0], lr[1], text[vr[0]:vr[1]] + '->' + path))
                        removed += 1
                        uses['view_cast_merged'] += 1
                        continue
            uses['explicit_cast'] += 1
            continue
        if qk == 'ImplicitCastExpr':
            ck = q.get('castKind')
            if ck in ('PointerToBoolean', 'IntegralToBoolean'):
                uses['truth'] += 1
                continue
            dst = decay(unit.canon(C.qtype(q)))
            node3, r = up(parents, q)
            # a void * flowing into a comparison or condition stays fine
            if (r or {}).get('kind') == 'BinaryOperator' and r.get('opcode') in ('==', '!=', '<', '>', '<=', '>='):
                if comparison_ok(unit, r, node3, new_c):
                    uses['compare'] += 1
                    continue
                return refuse('compare_needs_cast')
            if (r or {}).get('kind') == 'BinaryOperator' and r.get('opcode') in ('+', '-', '*', '/', '&', '|', '^', '<<', '>>', '%'):
                if is_ptr(new_c) != is_ptr(old_c):
                    return refuse('arithmetic')
                uses['arithmetic'] += 1
                if old_c == new_c:
                    continue
                return refuse('arithmetic')
            if not assignable(dst, new_c):
                return refuse('converted_to_' + dst)
            uses['converted'] += 1
            continue
        # no conversion node: the context expected the old type itself
        if qk in ('IfStmt', 'WhileStmt', 'DoStmt', 'ForStmt', 'ConditionalOperator') or \
                (qk == 'UnaryOperator' and q.get('opcode') == '!') or \
                (qk == 'BinaryOperator' and q.get('opcode') in ('&&', '||')):
            uses['truth'] += 1
            continue
        if qk == 'BinaryOperator' and q.get('opcode') in ('==', '!=', '<', '>', '<=', '>='):
            if comparison_ok(unit, q, node, new_c):
                uses['compare'] += 1
                continue
            return refuse('compare_needs_cast')
        if qk == 'CallExpr' and A.kids(q)[0] is not node:
            if not prototyped(q):
                uses['passed_unprototyped'] += 1
                continue
            if assignable(old_c, new_c):
                uses['passed'] += 1
                continue
            return refuse('passed_as_' + old_c)
        if qk in ('ReturnStmt', 'VarDecl', 'InitListExpr') or (qk == 'BinaryOperator' and q.get('opcode') == '='):
            if assignable(old_c, new_c):
                uses['stored'] += 1
                continue
            return refuse('stored_as_' + old_c)
        if qk == 'ArraySubscriptExpr' or (qk == 'UnaryOperator' and q.get('opcode') == '*'):
            if old_c == new_c:
                continue
            return refuse('dereference' if qk == 'UnaryOperator' else 'subscript')
        if qk == 'BinaryOperator' and q.get('opcode') in ('+', '-'):
            if old_c == new_c:
                continue
            return refuse('pointer_arithmetic')
        if qk == 'BinaryOperator' and q.get('opcode') == ',':
            uses['comma'] += 1
            continue
        return refuse('use_' + str(qk))
    if edit_decl and old_c != new_c:
        e = decl_spelling_edit(unit, file, decl, parents, target.spelling)
        if isinstance(e, str):
            return refuse(e)
        edits.append(e)
    return {'edits': edits, 'removed': removed, 'renamed': renamed, 'uses': uses}


def comparison_ok(unit, cmp, node, new_c):
    other = [x for x in A.kids(cmp) if x is not node]
    if not other:
        return False
    o = A.strip_implicit(other[0])
    if C.int_value(o) == 0:
        return True
    oc = decay(unit.canon(C.qtype(o)))
    if is_ptr(new_c):
        return is_ptr(oc)
    return not is_ptr(oc)


def value_into(unit, rhs, target, text, edits):
    """Casts removed (>= 0) when `rhs` can be stored into the retyped variable without a new cast, else None.

    An explicit cast to the old pointer type is respelled as the new type (`(u8 *)x` -> `(X *)x`), or dropped
    when its operand already has a compatible type."""
    r = A.strip_implicit(rhs)
    if C.int_value(r) == 0 and is_ptr(target.canon):
        return 0
    rc = decay(unit.canon(C.qtype(r)))
    if r.get('kind') != 'CStyleCastExpr' and assignable(target.canon, rc):
        return 0
    if r.get('kind') == 'CStyleCastExpr':
        inner = A.strip_implicit(A.kids(r)[0])
        ic = decay(unit.canon(C.qtype(inner)))
        rng = A.node_range(r, text)
        if rng is None:
            return None
        if assignable(target.canon, ic, C.int_value(inner) == 0) and (is_ptr(ic) == is_ptr(target.canon)):
            ir = A.node_range(A.kids(r)[0], text)
            if ir is None:
                return None
            inner_text = text[ir[0]:ir[1]]
            edits.append((rng[0], rng[1], inner_text))
            return 1
        m = re.match(r'\(\s*[^()]*?\)', text[rng[0]:rng[1]])
        if m and is_ptr(target.canon) and is_ptr(rc):
            edits.append((rng[0], rng[0] + m.end(), '(%s)' % target.spelling))
            return 0
    return None


def decl_spelling_edit(unit, file, decl, parents, spelling):
    """Respell a parameter's or one-declarator local's type (keeps `register`)."""
    text = unit.text(file)
    rng = A.node_range(decl, text)
    loc = (decl.get('loc') or {}).get('offset')
    if rng is None or loc is None or 'spellingLoc' in (decl.get('loc') or {}):
        return 'decl_in_macro'
    if decl.get('kind') == 'VarDecl':
        stmt = parents.get(id(decl))
        if stmt is None or stmt.get('kind') != 'DeclStmt' or len(A.kids(stmt)) != 1:
            return 'multi_declarator'
    if not text.isascii():
        loc = len(text.encode()[:loc].decode(errors='replace'))
    old = text[rng[0]:loc]
    m = re.fullmatch(r'(\s*(?:register\s+)?)((?:(?:const|volatile|struct|union|unsigned|signed)\s+)*\w+(?:\s+\w+)?\s*\**\s*)', old)
    if not m:
        return 'decl_spelling'
    new = spelling if spelling.endswith('*') else spelling + ' '
    return (rng[0] + m.end(1), loc, new)


# ---------------------------------------------------------------------------- body census (read-only)

def body_census(unit, file, fn, decl):
    """How the body uses one parameter: counts by kind, member offsets, record casts."""
    text = unit.text(file)
    parents, nodes = parents_of(fn)
    did = decl.get('id')
    old_key = unit.record_of_pointer(C.qtype(decl))
    out = {'uses': collections.Counter(), 'offsets': collections.Counter(), 'views': collections.Counter(),
           'conversions': collections.Counter()}
    for ref in nodes:
        if ref.get('kind') != 'DeclRefExpr' or (ref.get('referencedDecl') or {}).get('id') != did:
            continue
        node, p = up(parents, ref)
        k = (p or {}).get('kind')
        if k == 'ImplicitCastExpr' and p.get('castKind') == 'LValueToRValue':
            node, q = up(parents, p)
            qk = (q or {}).get('kind')
            if qk == 'MemberExpr' and q.get('isArrow') and old_key:
                got = access_leaf(unit, q, parents, old_key)
                if got:
                    out['offsets']['0x%X:%s' % (got[1], unit.canon(got[2]))] += 1
                out['uses']['member'] += 1
            elif qk == 'CStyleCastExpr':
                v = unit.record_of_pointer(C.qtype(q))
                if v:
                    out['views'][v] += 1
                    out['uses']['record_cast'] += 1
                else:
                    t = decay(unit.canon(C.qtype(q)))
                    out['uses']['byte_cast' if t[:-1] in A.BYTE_POINTEES else 'scalar_cast' if is_ptr(t) else 'int_cast'] += 1
            elif qk == 'ImplicitCastExpr':
                out['conversions'][decay(unit.canon(C.qtype(q)))] += 1
                out['uses']['converted'] += 1
            elif qk in ('ArraySubscriptExpr',) or (qk == 'UnaryOperator' and q.get('opcode') == '*'):
                out['uses']['deref'] += 1
            elif qk == 'BinaryOperator' and q.get('opcode') in ('+', '-', '&', '|', '^', '<<', '>>', '*', '/', '%'):
                out['uses']['arithmetic'] += 1
            elif qk == 'BinaryOperator' and q.get('opcode') in ('==', '!=', '<', '>', '<=', '>='):
                out['uses']['compare'] += 1
            elif qk == 'CallExpr':
                out['uses']['passed'] += 1
            else:
                out['uses'][str(qk)] += 1
        elif k == 'BinaryOperator' and p.get('opcode') == '=':
            out['uses']['assigned'] += 1
        else:
            out['uses'][str(k)] += 1
    return out


def body_summary(b):
    parts = ['%s=%d' % kv for kv in sorted(b['uses'].items())]
    if b['offsets']:
        parts.append('offsets=' + ','.join(sorted(b['offsets'])[:12]))
    if b['views']:
        parts.append('views=' + ','.join('%s:%d' % kv for kv in b['views'].most_common(4)))
    if b['conversions']:
        parts.append('to=' + ','.join('%s:%d' % kv for kv in b['conversions'].most_common(4)))
    return ' '.join(parts)


# ----------------------------------------------------------------------------- native probe (census)

def native_keys(root, path, stdin_text=None, cwd_rel=None):
    """Strict native errors of one source: list of (line, col, message)."""
    cmd = ['nice', '-n', '10'] + NATIVE
    if stdin_text is not None:
        cmd += ['-iquote', str(Path(cwd_rel).parent), '-x', 'c', '-']
    else:
        cmd += [path]
    r = subprocess.run(cmd, cwd=root, text=True, capture_output=True, input=stdin_text)
    out = []
    for m in DIAG.finditer(r.stderr):
        out.append((m.group(1), int(m.group(2)), int(m.group(3)), m.group(4)))
    return r.returncode, out


def line_map(old, new):
    """{new line number: old line number} for unchanged lines (1-based)."""
    sm = difflib.SequenceMatcher(a=old.splitlines(), b=new.splitlines(), autojunk=False)
    out = {}
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == 'equal':
            for k in range(i2 - i1):
                out[j1 + k + 1] = i1 + k + 1
    return out


def probe_source(job):
    root, path, edits = job
    import tools.proto.prototypes as P
    text = (Path(root) / path).read_text()
    rc0, base = native_keys(root, path, text, path)
    base_keys = collections.Counter((f, m) for f, _, _, m in base)
    out = []
    for e in edits:
        try:
            new = P.rewrite(text, [e])
        except Exception as exc:  # noqa: BLE001
            out.append(dict(file=path, symbol=e.symbol, status='rewrite_error', errors=[str(exc)[:200]]))
            continue
        rc, after = native_keys(root, path, new, path)
        lm = line_map(text, new)
        extra = collections.Counter((f, m) for f, _, _, m in after) - base_keys
        errs = [(path if f == '<stdin>' else f, lm.get(l, 0) if f == '<stdin>' else l, c, m)
                for f, l, c, m in after if (f, m) in extra]
        if errs:
            out.append(dict(file=path, symbol=e.symbol, status='native_type_error', errors=errs, edit=asdict(e)))
        elif rc and not rc0:
            out.append(dict(file=path, symbol=e.symbol, status='compile_error', errors=[], edit=asdict(e)))
        else:
            out.append(dict(file=path, symbol=e.symbol, status='ok', errors=[], edit=asdict(e)))
    return out


def probe_header(root, e, consumers, cap=8):
    """Probe a header declaration edit by rewriting it in place (private root) and compiling consumers."""
    import tools.proto.prototypes as P
    hp = Path(root) / e.file
    text = hp.read_text()
    try:
        new = P.rewrite(text, [e])
    except Exception as exc:  # noqa: BLE001
        return dict(file=e.file, symbol=e.symbol, status='rewrite_error', errors=[str(exc)[:200]])
    calling = [c for c in consumers if re.search(r'\b' + re.escape(e.symbol) + r'\s*\(', (Path(root) / c).read_text())][:cap]
    if not calling:
        return dict(file=e.file, symbol=e.symbol, status='header_no_calling_consumer', errors=[], edit=asdict(e))
    before = {c: native_keys(root, c) for c in calling}
    try:
        hp.write_text(new)
        after = {c: native_keys(root, c) for c in calling}
    finally:
        hp.write_text(text)
    errs = []
    for c in calling:
        extra = collections.Counter((f, m) for f, _, _, m in after[c][1]) - \
            collections.Counter((f, m) for f, _, _, m in before[c][1])
        errs += [(f, l, col, m) for f, l, col, m in after[c][1] if (f, m) in extra and f.endswith('.c')]
    return dict(file=e.file, symbol=e.symbol, status='native_type_error' if errs else 'ok', errors=errs, edit=asdict(e))


# ----------------------------------------------------------------------------------------- census

class Units:
    """Lazily parsed clang units of single source files (current text)."""

    def __init__(self, root):
        self.root, self.cache = Path(root), {}

    def get(self, rel):
        if rel not in self.cache:
            try:
                unit, err = A.clang_unit(self.root, rel)
            except Exception as exc:  # noqa: BLE001
                unit, err = None, str(exc)[-200:]
            self.cache[rel] = unit
        return self.cache[rel]

    def drop(self, rels):
        for r in rels:
            self.cache.pop(r, None)


def in_scope(path, scope, exclude=()):
    ok = not scope or any(path == p or path.startswith(p.rstrip('/') + '/') for p in scope)
    return ok and not any(path == p or path.startswith(p.rstrip('/') + '/') for p in exclude)


def calls_in(unit, file, symbol):
    """[(function decl, CallExpr)] calling `symbol` in `file`."""
    out = []
    for f, fn in unit.functions({file}):
        for n, _ in A.walk(fn):
            if n.get('kind') == 'CallExpr' and callee_name(n) == symbol:
                out.append((fn, n))
    return out


def holder_of(unit, fn, arg):
    """Classify the expression a caller passes: (kind, decl or cast node)."""
    a = A.strip_parens(arg)
    while a.get('kind') == 'ImplicitCastExpr' and a.get('castKind') in ('LValueToRValue', 'BitCast', 'NoOp',
                                                                          'ArrayToPointerDecay', 'IntegralCast'):
        a = A.strip_parens(A.kids(a)[0])
    if a.get('kind') == 'DeclRefExpr':
        ref = a.get('referencedDecl') or {}
        if ref.get('kind') in ('VarDecl', 'ParmVarDecl'):
            for n, _ in A.walk(fn):
                if n.get('id') == ref.get('id') and n.get('kind') == ref.get('kind'):
                    if n.get('kind') == 'VarDecl' and n.get('storageClass') in ('static', 'extern'):
                        return 'static_or_global', n
                    return ('local' if n.get('kind') == 'VarDecl' else 'own_parameter'), n
            return 'global', None
        return 'other_ref', None
    if a.get('kind') == 'CStyleCastExpr':
        return 'cast', a
    if a.get('kind') == 'MemberExpr':
        return 'field', None
    if a.get('kind') == 'CallExpr':
        return 'call_result', None
    if a.get('kind') == 'UnaryOperator' and a.get('opcode') == '&':
        return 'address_of', None
    if C.int_value(a) is not None:
        return 'constant', None
    return 'expression', None


def census(root, scope, symbols=(), exclude=(), workers=4, log=print, def_scope=None):
    """Probe declarations and analyse every refused parameter. Returns (rows, sites, probes)."""
    import tools.proto.prototypes as P
    import layout_compile_identity as L  # noqa: F401  (import check: tools path)
    root = Path(root).resolve()
    t0 = time.time()
    corpus, types, remaining, edits, holds = P.candidates(root, scope, symbols=symbols)
    edits = [e for e in edits if in_scope(e.file, scope, exclude)]
    log('candidates: %d proposed declarations, %d holds (%.0fs)' % (len(edits), len(holds), time.time() - t0))
    src = collections.defaultdict(list)
    hdr = []
    for e in edits:
        (hdr.append(e) if e.file.endswith('.h') else src[e.file].append(e))
    probes = []
    with ThreadPoolExecutor(workers) as pool:
        for res in pool.map(probe_source, [(str(root), p, es) for p, es in sorted(src.items())]):
            probes.extend(res)
    rev = collections.defaultdict(list)
    for c in corpus.c_files:
        if c.startswith('src/'):
            for h in corpus.closure(c):
                rev[h].append(c)
    for e in hdr:
        probes.append(probe_header(str(root), e, sorted(rev.get(e.file, []))))
    log('probe: %s (%.0fs)' % (dict(collections.Counter(p['status'] for p in probes)), time.time() - t0))
    refused = [p for p in probes if p['status'] == 'native_type_error']
    rows, sites = analyse(root, refused, edits, log, def_scope)
    log('analysis: %d parameters, %d failing arguments (%.0fs)' % (len(rows), len(sites), time.time() - t0))
    held = [h for h in holds if in_scope(h['file'], scope, exclude)]
    return rows, sites, probes, dict(remaining=len(remaining), proposed=len(edits), held=held,
                                     holds=dict(collections.Counter(h['reason'].split(':')[0] for h in held)))


def gather_calls(units, files, symbol, nparams=None):
    """Every call of `symbol` in `files`: per parameter index, [(file, unit, fn, call, arg, type, null)]."""
    per_param, arity = collections.defaultdict(list), []
    for cf in sorted(files):
        cu = units.get(cf)
        if cu is None:
            continue
        for cfn, call in calls_in(cu, cf, symbol):
            args = A.kids(call)[1:]
            if nparams is not None and len(args) != nparams:
                arity.append('arity:%s:%d/%d' % (cf, len(args), nparams))
            for i, arg in enumerate(args if nparams is None else args[:nparams]):
                inner = A.strip_implicit(arg)
                per_param[i].append((cf, cu, cfn, call, arg, C.qtype(inner), C.int_value(inner) == 0))
    return per_param, arity


def evaluate_param(dunit, dpath, fn, pdecl, calls, editable=None):
    """Candidate types for one parameter and the proposal. `editable(file)` limits holder fixes."""
    cur = C.qtype(pdecl)
    cur_c = decay(dunit.canon(cur))
    b = body_census(dunit, dpath, fn, pdecl)
    cands = [(spelled(cur), dunit)]
    for t in [x[5] for x in calls]:
        ts = spelled(t)
        if ts not in [c[0] for c in cands]:
            cands.append((ts, next(x[1] for x in calls if spelled(x[5]) == ts)))
    # what callers cast away at the call (`f((u8 *)position)`): the operand is the real object
    for x in calls:
        a = A.strip_parens(x[4])
        while a.get('kind') == 'ImplicitCastExpr' and A.kids(a):
            a = A.strip_parens(A.kids(a)[0])
        if a.get('kind') == 'CStyleCastExpr':
            ts = spelled(C.qtype(A.strip_implicit(A.kids(a)[0])))
            if is_ptr(ts) and ts not in [c[0] for c in cands]:
                cands.append((ts, x[1]))
    # record types the body itself casts the parameter to (D1/D3: s32 / void * holders of a record)
    for key, _ in b['views'].most_common():
        name = key if re.match(r'^[A-Za-z_]\w*$', key) else ''
        if name:
            ts = spelled(name + ' *')
            if ts not in [c[0] for c in cands]:
                cands.append((ts, dunit))
    evaluated = []
    for ts, tu in cands:
        if '[' in ts or '(' in ts:
            continue
        tgt = Target(tu, ts)
        if not tgt.canon or tgt.home is None:
            continue        # a name this unit cannot see
        if tgt.canon != cur_c and not is_ptr(tgt.canon):
            continue        # never trade a parameter for an integer: pointers are the readable contract
        bad = [x for x in calls if not assignable(tgt.canon, decay(x[1].canon(x[5])), x[6])]
        if tgt.canon == cur_c:
            plan = {'edits': [], 'removed': 0, 'uses': collections.Counter()}
        elif tgt.home and tgt.home.startswith('src/') and tgt.home != dpath:
            plan = {'refused': 'private_type_in_' + tgt.home}
        else:
            plan = plan_retype(dunit, dpath, fn, pdecl, target_in(dunit, tgt))
            cur_key = dunit.record_of_pointer(cur)
            if plan.get('renamed') and cur_key and not GENERATED.match(cur_key):
                # a named record keeps its member names: its callers' holders change instead
                plan = {'refused': 'named_record_members_would_be_renamed'}
        fixes = []
        for x in bad:
            f = holder_fix(x, tgt)
            if f['fix'] != 'none' and editable is not None and not editable(x[0]):
                f = dict(f, fix='none', why='caller_not_editable:' + x[0])
            fixes.append(f)
        evaluated.append(dict(type=ts, target=tgt, bad=bad, plan=plan, fixes=fixes,
                              fixable=all(f['fix'] != 'none' for f in fixes)))
    choice, klass, why = choose(evaluated, cur, cur_c, b)
    return dict(cur=spelled(cur), cur_c=cur_c, body=b, evaluated=evaluated, choice=choice, klass=klass, why=why)


def candidates_text(evaluated):
    return ';'.join('%s[%s%s]' % (e['type'], 'ok' if 'edits' in e['plan'] else e['plan']['refused'],
                                  '' if not e['bad'] else ',%d bad,%s' % (len(e['bad']), 'fixable' if e['fixable'] else
                                                                         'unfixable:' + next(f.get('why', '') for f in e['fixes'] if f['fix'] == 'none')))
                    for e in evaluated)


def arg_at(unit, file, symbol, line, col):
    """(fn, call, index, arg) of the argument of a `symbol` call starting at line:col."""
    for cfn, call in calls_in(unit, file, symbol):
        for i, arg in enumerate(A.kids(call)[1:]):
            b = (arg.get('range') or {}).get('begin') or {}
            if b.get('_l') == line and b.get('col') == col:
                return cfn, call, i, arg
    return None


def sdk_failures(units, probes):
    """Failing arguments of SDK stand-in calls: [(param, expected spelling, x tuple)] from native diagnostics."""
    out = []
    for p in probes:
        for f, l, c, m in p['errors']:
            mm = PASSING.search(m)
            cu = units.get(f)
            hit = arg_at(cu, f, p['symbol'], l, c) if cu is not None and mm else None
            if not hit:
                out.append((None, mm.group(2) if mm else '', (f, cu, None, None, None, mm.group(1) if mm else m[:80], False)))
                continue
            cfn, call, i, arg = hit
            inner = A.strip_implicit(arg)
            out.append((i, mm.group(2), (f, cu, cfn, call, arg, C.qtype(inner), C.int_value(inner) == 0)))
    return out


def analyse(root, refused, edits, log=print, def_scope=None):
    units = Units(root)
    by_symbol = collections.defaultdict(list)
    for p in refused:
        by_symbol[(p['symbol'], p['edit']['definition'])].append(p)
    rows, sites = [], []
    for (symbol, definition), probes in sorted(by_symbol.items()):
        base = dict(symbol=symbol, definition=definition)
        if ':' not in definition:
            # SDK stand-in: the contract is fixed; only the callers' holders can change
            per = collections.defaultdict(list)
            for i, expected, x in sdk_failures(units, probes):
                per[(i, expected)].append(x)
            for (i, expected), xs in sorted(per.items(), key=lambda kv: (str(kv[0][0]), kv[0][1])):
                fixes = []
                for x in xs:
                    if x[2] is None:
                        fixes.append(dict(holder='unlocated', fix='none', why='argument_not_located'))
                        continue
                    tgt = Target(x[1], expected)
                    fixes.append(holder_fix(x, tgt) if tgt.canon else dict(holder='?', fix='none', why='type_not_visible'))
                ok = all(f['fix'] != 'none' for f in fixes)
                counts = collections.Counter(spelled(x[5]) for x in xs)
                rows.append(dict(base, param='' if i is None else i, name='', current=spelled(expected),
                                 callers=';'.join('%s:%d' % kv for kv in counts.most_common()), failing=len(xs),
                                 caller_files=len({x[0] for x in xs}), body='', candidates='',
                                 proposed=spelled(expected) if ok else '', klass='sdk_contract',
                                 fix_side='callers' if ok else 'none',
                                 reason='' if ok else ';'.join(sorted({f.get('why', '') for f in fixes if f['fix'] == 'none'}))[:300]))
                for x, f in zip(xs, fixes):
                    sites.append(dict(base, caller=x[0], line=(x[4] or {}).get('range', {}).get('begin', {}).get('_l', '') if x[4] else '',
                                      param='' if i is None else i, passed=spelled(x[5]), expected=spelled(expected),
                                      holder=f['holder'], fix=f['fix'], message=f.get('why', '')))
            continue
        dpath, dname = definition.rsplit(':', 1)
        dunit = units.get(dpath)
        fn = find_function(dunit, dpath, dname) if dunit else None
        if fn is None:
            rows.append(dict(base, param='*', klass='definition_unparsed', fix_side='none',
                             reason='definition not found in its own file AST', failing=len(probes)))
            continue
        params = params_of(fn)
        callers = {f for p in probes for f, *_ in p['errors'] if f.endswith('.c')} | \
            {p['file'] for p in probes if p['file'].endswith('.c')}
        per_param, arity = gather_calls(units, callers, symbol, len(params))
        found = False
        for i, pdecl in enumerate(params):
            calls = per_param.get(i, [])
            cur_c = decay(dunit.canon(C.qtype(pdecl)))
            failing = [x for x in calls if not assignable(cur_c, decay(x[1].canon(x[5])), x[6])]
            if not failing:
                continue
            found = True
            ev = evaluate_param(dunit, dpath, fn, pdecl, calls)
            choice = ev['choice']
            counts = collections.Counter(spelled(x[5]) for x in calls)
            klass = ev['klass']
            why = ev['why']
            if def_scope is not None and not def_scope(dpath):
                why = ('definition_out_of_scope; ' + why).strip('; ')
            rows.append(dict(base, param=i, name=pdecl.get('name', ''), current=ev['cur'],
                             callers=';'.join('%s:%d' % kv for kv in counts.most_common()), failing=len(failing),
                             body=body_summary(ev['body']), candidates=candidates_text(ev['evaluated']),
                             proposed=choice['type'] if choice else '', klass=klass,
                             fix_side=('callee' if choice and not choice['bad'] else
                                       'callers' if choice and choice['type'] == ev['cur'] else
                                       'callee+callers' if choice else 'none'),
                             reason=why, caller_files=len({x[0] for x in calls}), other=';'.join(arity[:3])))
            for x in failing:
                fix = holder_fix(x, choice['target'] if choice else Target(dunit, ev['cur']))
                sites.append(dict(base, caller=x[0], line=(x[3].get('range') or {}).get('begin', {}).get('_l', ''),
                                  param=i, passed=spelled(x[5]), expected=spelled(ev['cur']), holder=fix['holder'],
                                  fix=fix['fix'], message=fix.get('why', '')))
        if not found:
            msgs = sorted({m[:120] for p in probes for *_, m in p['errors']})
            rows.append(dict(base, param='*', klass='return_or_other' if not arity else 'arity', fix_side='none',
                             failing=sum(len(p['errors']) for p in probes),
                             reason=(';'.join(arity[:2]) + ' ' + ' | '.join(msgs[:2])).strip()[:300]))
    return rows, sites


def holder_fix(x, target):
    """Can the failing argument be made compatible with `target` by retyping its holder (no new cast)?"""
    cf, cu, cfn, call, arg, atype, null = x
    kind, node = holder_of(cu, cfn, arg)
    if assignable(target.canon, decay(cu.canon(atype)), null):
        return dict(holder=kind, fix='compatible')
    if kind in ('local', 'own_parameter'):
        if is_ptr(decay(cu.canon(C.qtype(node)))) and not is_ptr(target.canon):
            return dict(holder=kind, fix='none', why='holder_pointer_to_integer')
        if target.home and target.home.startswith('src/') and target.home != cf:
            return dict(holder=kind, fix='none', why='private_target_type')
        tg = target_in(cu, target)
        plan = plan_retype(cu, cf, cfn, node, tg)
        if 'refused' in plan:
            return dict(holder=kind, fix='none', why=plan['refused'])
        return dict(holder=kind, fix='retype_' + kind, plan=plan, decl=node, target=tg)
    if kind == 'cast':
        inner = A.strip_implicit(A.kids(node)[0])
        ic = decay(cu.canon(C.qtype(inner)))
        if assignable(target.canon, ic, C.int_value(inner) == 0) and is_ptr(ic) == is_ptr(target.canon):
            return dict(holder=kind, fix='drop_cast', cast=node)
        return dict(holder=kind, fix='none', why='cast_operand_' + ic)
    return dict(holder=kind, fix='none', why=kind)


def target_in(unit, target):
    """The same target type expressed in another unit (layouts from the unit that sees the type)."""
    if unit is target.unit:
        return target
    t = Target(unit, target.spelling)
    if t.canon == target.canon and (t.key or not target.key):
        return t
    # not visible in this unit: keep the defining unit's layout and canonical form
    t.canon, t.key, t.unit, t.home = target.canon, target.key, target.unit, target.home
    t.needs_header = True
    return t


def choose(evaluated, cur, cur_c, body):
    """Pick the proposal: (evaluated entry or None, class, reason)."""
    cur_s = spelled(cur)
    klass = classify(cur_c, [e for e in evaluated])
    ok = [e for e in evaluated if 'edits' in e['plan'] and e['fixable']]
    if not ok:
        reasons = sorted({e['plan'].get('refused', '') for e in evaluated if 'refused' in e['plan']} |
                         {f.get('why', '') for e in evaluated for f in e['fixes'] if f['fix'] == 'none'})
        return None, klass, ';'.join(r for r in reasons if r)[:300] or 'no_candidate'

    def rank(e):
        # a shared record beats a census view, which beats a byte/void/scalar pointer; then fewest holder
        # changes, then most casts removed
        name = type_name(e['type'])
        fixes = sum(f['fix'] != 'compatible' for f in e['fixes'])
        kind = strength(name) if e['target'].key else 2
        return (kind, fixes, -e['plan'].get('removed', 0), e['type'] != cur_s, e['type'])
    best = sorted(ok, key=rank)[0]
    return best, klass, ''


def classify(cur_c, evaluated):
    passed = {decay(e['target'].canon) for e in evaluated[1:]}
    if not is_ptr(cur_c):
        return 'int_param_pointer_args' if any(is_ptr(p) for p in passed) else 'scalar_mismatch'
    if any(not is_ptr(p) for p in passed):
        return 'pointer_param_int_args'
    cur_key = evaluated[0]['target'].key if evaluated else None
    if cur_key and GENERATED.match(cur_key):
        return 'view_param'
    if cur_key:
        return 'record_param_mismatch'
    if cur_c[:-1] in A.BYTE_POINTEES or cur_c == 'void*':
        return 'byte_param'
    return 'scalar_pointer_param'


# ------------------------------------------------------------------------------------------ outputs

CENSUS_FIELDS = ['symbol', 'definition', 'param', 'name', 'current', 'callers', 'failing', 'caller_files', 'body',
                 'candidates', 'proposed', 'klass', 'fix_side', 'reason', 'other']
SITE_FIELDS = ['symbol', 'definition', 'caller', 'line', 'param', 'passed', 'expected', 'holder', 'fix', 'message']


def write_tsv(path, rows, fields):
    with open(path, 'w') as fh:
        fh.write('\t'.join(fields) + '\n')
        for r in rows:
            fh.write('\t'.join(str(r.get(k, '')).replace('\t', ' ').replace('\n', ' ') for k in fields) + '\n')


def read_tsv(path):
    lines = Path(path).read_text().splitlines()
    head = lines[0].split('\t')
    return [dict(zip(head, l.split('\t'))) for l in lines[1:] if l]


# ------------------------------------------------------------------------------------------ prover

class Prover:
    """Complete-TU identity against the ORIGINAL objects plus the strict native check, per transaction.

    Every accepted change is byte-identical, so a TU's original object (captured once, lazily, before the
    first change that reaches it) stays the expected object for the whole run."""

    def __init__(self, root, out, workers=4, max_closure=400, log=print):
        import layout_compile_identity as L
        self.root, self.out, self.workers, self.max_closure, self.log = Path(root), Path(out), workers, max_closure, log
        self.physical, _ = L.recipes(self.root)
        self.deps = self.load_deps()
        self.rdeps = collections.defaultdict(set)
        for tu, ds in self.deps.items():
            self.rdeps[tu].add(tu)
            for d in ds:
                self.rdeps[d].add(tu)
        self.baseline = {}
        self.receipts = []

    def load_deps(self):
        cache = self.out / 'deps.json'
        if cache.exists():
            return json.loads(cache.read_text())
        from tu_identity import _mm
        out = {}
        self.log('dependency map: %d physical TUs (clang -MM, once)' % len(self.physical))
        with ProcessPoolExecutor(max_workers=self.workers) as ex:
            for rel, deps in ex.map(_mm, [(str(self.root), p, self.physical[p]) for p in sorted(self.physical)],
                                    chunksize=32):
                out[rel] = sorted({os.path.normpath(d) for d in deps})
        cache.write_text(json.dumps(out))
        return out

    def note_include(self, file, headers):
        """A file gains #include of `headers`: every TU that sees the file now also sees them (and theirs)."""
        seen = self.rdeps.get(file, set()) | ({file} if file in self.physical else set())
        for h in headers:
            for d in {h} | header_closure(self.root, h):
                self.rdeps[d] |= seen

    def closure(self, files):
        tus = set()
        for f in files:
            tus |= self.rdeps.get(f, set())
        return sorted(tus)

    def capture(self, tus):
        from tu_identity import capture
        return {r['source']: r for r in capture(self.root, tus, self.physical, self.workers)}

    def native(self, tus):
        def one(tu):
            rc, errs = native_keys(self.root, tu)
            return tu, collections.Counter((f, m) for f, l, c, m in errs)
        with ThreadPoolExecutor(self.workers) as pool:
            return dict(pool.map(one, tus))

    def begin(self, files):
        """Before a transaction: closure, missing baselines and native errors on the current text."""
        orphans = [f for f in files if not self.rdeps.get(f)]
        if orphans:
            return None, None, 'no_physical_tu:' + orphans[0]
        tus = self.closure(files)
        if len(tus) > self.max_closure:
            return None, None, 'closure_too_large:%d' % len(tus)
        missing = [t for t in tus if t not in self.baseline]
        if missing:
            self.baseline.update(self.capture(missing))
        bad = [t for t in tus if 'error' in self.baseline[t]]
        if bad:
            return None, None, 'baseline_compile_error:' + bad[0]
        return tus, self.native(tus), ''

    def check(self, tus, native_before, label):
        after = self.capture(tus)
        changed = []
        for t in tus:
            a, b = after[t], self.baseline[t]
            same = 'error' not in a and all(a[k] == b[k] for k in
                                            ('raw_sha256', 'canonical_assembly_sha256', 'canonical_object_sha256'))
            if not same:
                changed.append(t)
        if changed:
            return 'identity:' + ','.join(changed[:3]) + ('' if len(changed) <= 3 else ',+%d' % (len(changed) - 3))
        nat = self.native(tus)
        gained = []
        for t in tus:
            extra = nat[t] - native_before[t]
            gained += ['%s: %s' % (f, m) for (f, m) in extra]
        if gained:
            return 'native:' + ' | '.join(sorted(set(gained))[:3])
        for t in tus:
            self.receipts.append(dict(source=t, label=label, raw_equal=True, canonical_assembly_equal=True,
                                      canonical_object_equal=True, raw_sha256=self.baseline[t]['raw_sha256']))
        return ''


# ------------------------------------------------------------------------------------------- apply

def debt(rel, text):
    import debt_check as D
    return {k: dict(v['counts']) for k, v in D.analyze(rel, text)['scopes'].items()}


def casts_of(rel, text):
    return sum(v.get('pointer_casts', 0) for v in debt(rel, text).values())


def debt_rises(rel, before, after):
    b, a = debt(rel, before), debt(rel, after)
    return [k for k, counts in a.items() if any(n > b.get(k, {}).get(c, 0) for c, n in counts.items())]


def apply_text_edits(text, edits):
    edits = sorted(set(edits), key=lambda e: (e[0], e[1]))
    for (a, b, _), (c, d, _) in zip(edits, edits[1:]):
        if b > c:
            raise ValueError('overlapping edits')
    for a, b, rep in reversed(edits):
        text = text[:a] + rep + text[b:]
    return text


def ensure_include(text, header_rel):
    """Add `#include "<header>"` after the last leading include (no-op when present)."""
    inc = header_rel.removeprefix('include/')
    if re.search(r'#\s*include\s*"' + re.escape(inc) + '"', text):
        return text
    import tools.proto.prototypes as P
    scan = P.cscan.scan(text)
    first_use = min((it.start for it in scan.items), default=len(text))
    includes = [d for d in scan.directives if d.kind == 'include' and d.end <= first_use and d.depth <= int(header_rel.endswith('.h'))]
    at = includes[-1].end if includes else 0
    line = '#include "%s"\n' % inc
    if at and text[at - 1] != '\n':
        line = '\n' + line
    return text[:at] + line + text[at:]


def respell_in_text(text, symbol, index, spelling):
    """Respell parameter `index` of every typed (non-definition) declaration of `symbol` in `text`.

    Returns the new text, or None when nothing changed.  Empty `()` declarations are left alone
    (prototypes.py replaces them); the parameter name is kept."""
    import tools.proto.prototypes as P
    M = P.M
    scan = P.cscan.scan(text)
    reps = []
    for it in scan.items:
        if it.kind != 'decl' or not any(d.name == symbol and d.is_function for d in it.decls):
            continue
        m = re.search(r'\b' + re.escape(symbol) + r'\s*\(', scan.masked[it.start:it.end])
        if not m:
            continue
        start = it.start + m.end() - 1
        close = P.balanced(scan.masked, start)
        inner = scan.masked[start + 1:close]
        if not inner.strip() or inner.strip() == 'void':
            continue
        depth, cuts = 0, [start + 1]
        for j in range(start + 1, close):
            ch = scan.masked[j]
            depth += ch == '('
            depth -= ch == ')'
            if ch == ',' and depth == 0:
                cuts.append(j + 1)
        cuts.append(close + 1)
        if index >= len(cuts) - 1:
            continue
        a, b = cuts[index], cuts[index + 1] - 1
        ptext = text[a:b]
        lead = ptext[:len(ptext) - len(ptext.lstrip())]
        trail = ptext[len(ptext.rstrip()):]
        toks = P.cscan.tokens(ptext.strip())
        if toks and toks[0] == 'register':
            toks = toks[1:]
        name = M.param_parts(toks)[2] if toks else ''
        if not name:
            new = spelling.rstrip()
        else:
            new = (spelling if spelling.endswith('*') else spelling + ' ') + name
        if re.sub(r'\s+', '', new) != re.sub(r'\s+', '', ptext):
            reps.append((a, b, lead + new + trail))
    return apply_text_edits(text, reps) if reps else None


class Index:
    """Built once per apply run: typed declaration files and calling files of every function name."""

    CALL = re.compile(r'\b([A-Za-z_]\w*)\s*\(')

    def __init__(self, root):
        import tools.proto.prototypes as P
        self.root = Path(root)
        corpus, types, definitions, sites = P.census(self.root)
        self.corpus, self.types, self.definitions = corpus, types, definitions
        self.typed = collections.defaultdict(set)
        self.empty = collections.defaultdict(set)
        for s in sites:
            if s.params is not None and not P.identifier_list(s.params, types.visible(s.path)):
                self.typed[s.name].add(s.path)
            else:
                self.empty[s.name].add(s.path)
        self.callers = collections.defaultdict(set)
        for c in corpus.c_files:
            for m in self.CALL.finditer(corpus.scan(c).masked):
                self.callers[m.group(1)].add(c)

    def owner_header(self, dpath):
        folders = dpath.split('/')[1:-1]
        for n in range(len(folders), 0, -1):
            h = 'include/' + '/'.join(folders[:n]) + '.h'
            if (self.root / h).is_file():
                return h
        return None


def drop_cast_edit(text, arg, cast):
    """Replace a call argument `((T *)x)` by `x` (grouping parentheses of the argument go too)."""
    rng, ir = A.node_range(arg, text), A.node_range(A.kids(cast)[0], text)
    if rng is None or ir is None:
        return None
    inner = text[ir[0]:ir[1]].strip()
    while inner.startswith('(') and inner.endswith(')') and A.balanced(inner[1:-1]):
        inner = inner[1:-1].strip()
    return (rng[0], rng[1], inner)


def respell_all(root, index, texts, headers, respells, editable):
    """Respell typed declarations for every (function, param, spelling, home, definition file); '' or reason."""
    for name, i, spelling, home, deffile in respells:
        for f in sorted(index.typed.get(name, ())):
            if f == deffile and f not in texts:
                continue
            new = respell_in_text(texts.get(f, (Path(root) / f).read_text()), name, i, spelling)
            if new is None:
                continue
            if not editable(f):
                return 'declaration_not_editable:%s:%s' % (name, f)
            texts[f] = new
            if home and type_name(spelling) and home != f:
                headers[f].add(home)
    return ''


def plan_family(root, units, index, symbol, definition, editable, def_ok):
    """Plan every text change of one family on the current text.

    Returns (dict(texts={file: new text}, touched={file: {functions}}, headers={file: {type headers}},
    summary=...), '') or (None, reason)."""
    texts, touched, headers = {}, collections.defaultdict(set), collections.defaultdict(set)
    edits = collections.defaultdict(list)
    summary = dict(params=[], holders=0, casts_dropped=0, renamed=0)
    respells = []
    if ':' not in definition:
        return None, 'sdk_family_needs_probe'
    dpath, dname = definition.rsplit(':', 1)
    if not def_ok(dpath):
        return None, 'definition_out_of_scope:' + dpath
    dunit = units.get(dpath)
    fn = find_function(dunit, dpath, dname) if dunit else None
    if fn is None:
        return None, 'definition_unparsed'
    params = params_of(fn)
    callers = index.callers.get(symbol, set()) - {dpath} | ({dpath} if len(calls_in(dunit, dpath, symbol)) else set())
    per_param, arity = gather_calls(units, callers, symbol, len(params))
    if arity:
        return None, arity[0]
    for i, pdecl in enumerate(params):
        calls = per_param.get(i, [])
        cur_c = decay(dunit.canon(C.qtype(pdecl)))
        if all(assignable(cur_c, decay(x[1].canon(x[5])), x[6]) for x in calls):
            continue
        ev = evaluate_param(dunit, dpath, fn, pdecl, calls, editable)
        choice = ev['choice']
        if choice is None:
            return None, 'param%d:%s' % (i, ev['why'])
        tgt = choice['target']
        if choice['type'] != ev['cur']:
            plan = choice['plan']
            edits[dpath] += plan['edits']
            touched[dpath].add(dname)
            summary['renamed'] += plan.get('renamed', 0)
            summary['casts_dropped'] += plan.get('removed', 0)
            dt = target_in(dunit, tgt)
            if getattr(dt, 'needs_header', False):
                if not tgt.home or tgt.home.startswith('src/'):
                    return None, 'type_home_unusable:%s:%s' % (choice['type'], tgt.home)
                headers[dpath].add(tgt.home)
            respells.append((symbol, i, tgt.spelling, tgt.home, dpath))
            summary['params'].append('%d:%s->%s' % (i, ev['cur'], tgt.spelling))
        for x, fix in zip(choice['bad'], choice['fixes']):
            cf, cu = x[0], x[1]
            if fix['fix'] == 'drop_cast':
                e = drop_cast_edit(cu.text(cf), x[4], fix['cast'])
                if e is None:
                    return None, 'caller_cast_in_macro:' + cf
                edits[cf].append(e)
                summary['casts_dropped'] += 1
            else:
                if fix['holder'] == 'own_parameter':
                    # the caller's own contract changes too: respell its typed declarations (chain retype)
                    j = [q.get('id') for q in params_of(x[2])].index(fix['decl'].get('id'))
                    respells.append((x[2].get('name'), j, fix['target'].spelling, tgt.home, cf))
                edits[cf] += fix['plan']['edits']
                summary['casts_dropped'] += fix['plan'].get('removed', 0)
                if getattr(fix['target'], 'needs_header', False):
                    if not tgt.home or tgt.home.startswith('src/'):
                        return None, 'type_home_unusable:%s:%s' % (choice['type'], tgt.home)
                    headers[cf].add(tgt.home)
            touched[cf].add(x[2].get('name'))
            summary['holders'] += 1
    if not edits:
        return None, 'nothing_to_change'
    for f, es in edits.items():
        try:
            texts[f] = apply_text_edits(units.get(f).text(f), es)
        except ValueError:
            return None, 'overlapping_edits:' + f
    why = respell_all(root, index, texts, headers, respells, editable)
    if why:
        return None, why
    for f, hs in headers.items():
        base = texts.get(f, (Path(root) / f).read_text())
        for h in sorted(hs):
            if f.endswith('.h') and h in header_closure(root, f):
                continue
            base = ensure_include(base, h)
        texts[f] = base
    return dict(texts=texts, touched=touched, headers=headers, summary=summary), ''


def plan_sdk_family(root, units, index, probes, editable):
    """SDK stand-in callee: re-probe its declarations on the current text, fix the failing holders."""
    import tools.proto.prototypes as P
    edits, touched = collections.defaultdict(list), collections.defaultdict(set)
    summary = dict(params=[], holders=0, casts_dropped=0, renamed=0)
    respells, headers = [], collections.defaultdict(set)
    fresh = []
    for p in probes:
        e = P.Edit(**{k: (int(v) if k == 'occurrences' else v) for k, v in p['edit'].items()})
        if e.file.endswith('.h'):
            fresh.append(dict(p, errors=[tuple(x) for x in p['errors']]))
            continue
        text = (Path(root) / e.file).read_text()
        try:
            new = P.rewrite(text, [e])
        except Exception as exc:  # noqa: BLE001
            return None, 'rewrite_error:' + str(exc)[:80]
        _, base = native_keys(root, e.file, text, e.file)
        _, after = native_keys(root, e.file, new, e.file)
        lm = line_map(text, new)
        extra = collections.Counter((f, m) for f, _, _, m in after) - collections.Counter((f, m) for f, _, _, m in base)
        errs = [(e.file if f == '<stdin>' else f, lm.get(l, 0) if f == '<stdin>' else l, c, m)
                for f, l, c, m in after if (f, m) in extra]
        fresh.append(dict(p, errors=errs))
    if not any(p['errors'] for p in fresh):
        return None, 'no_failing_argument'
    for i, expected, x in sdk_failures(units, fresh):
        if x[2] is None:
            return None, 'argument_not_located:%s:%s' % (x[0], x[5])
        if not editable(x[0]):
            return None, 'caller_not_editable:' + x[0]
        tgt = Target(x[1], expected)
        if not tgt.canon:
            return None, 'type_not_visible:' + expected
        fix = holder_fix(x, tgt)
        if fix['fix'] == 'none':
            return None, 'caller:%s:%s:%s' % (x[0], fix['holder'], fix.get('why', ''))
        if fix['fix'] == 'compatible':
            continue
        cf, cu = x[0], x[1]
        if fix['fix'] == 'drop_cast':
            e = drop_cast_edit(cu.text(cf), x[4], fix['cast'])
            if e is None:
                return None, 'caller_cast_in_macro:' + cf
            edits[cf].append(e)
            summary['casts_dropped'] += 1
        else:
            if fix['holder'] == 'own_parameter':
                j = [q.get('id') for q in params_of(x[2])].index(fix['decl'].get('id'))
                respells.append((x[2].get('name'), j, tgt.spelling, tgt.home, cf))
            edits[cf] += fix['plan']['edits']
            summary['casts_dropped'] += fix['plan'].get('removed', 0)
        touched[cf].add(x[2].get('name'))
        summary['holders'] += 1
    if not edits:
        return None, 'nothing_to_change'
    texts = {}
    for f, es in edits.items():
        try:
            texts[f] = apply_text_edits(units.get(f).text(f), es)
        except ValueError:
            return None, 'overlapping_edits:' + f
    why = respell_all(root, index, texts, headers, respells, editable)
    if why:
        return None, why
    for f, hs in headers.items():
        base = texts.get(f, (Path(root) / f).read_text())
        for h in sorted(hs):
            if not (f.endswith('.h') and h in header_closure(root, f)):
                base = ensure_include(base, h)
        texts[f] = base
    return dict(texts=texts, touched=touched, headers=headers, summary=summary), ''


_HCLOSURE = {}


def header_closure(root, rel):
    """Files a header (or source) includes, transitively (clang -MM)."""
    if rel not in _HCLOSURE:
        res = subprocess.run(['clang', '--target=mipsel-unknown-none', '-w', '-MM', '-Iinclude', '-x', 'c', rel],
                             cwd=root, capture_output=True, text=True)
        _HCLOSURE[rel] = {os.path.normpath(t) for t in res.stdout.replace('\\\n', ' ').split(':', 1)[-1].split()}
    return _HCLOSURE[rel]


def fold_touched(root, files, touched):
    """cast_fold sites inside the touched functions of the changed files: {file: new text}."""
    import cast_fold as F
    if not files:
        return {}
    edits, _, _ = F.plan(root, files, 1)
    out = {}
    for f, ss in edits.items():
        keep = [s for s in ss if s['func'] in touched.get(f, ())]
        if keep:
            text = (Path(root) / f).read_text()
            for s in sorted(keep, key=lambda s: -s['start']):
                if text[s['start']:s['end']] == s['old']:
                    text = text[:s['start']] + s['new'] + text[s['end']:]
            out[f] = text
    return out


def transact(root, prover, units, label, texts, touched=None, added_headers=None, fold=True):
    """Write `texts`, fold, check debt + identity + native; roll back on failure. Returns (verdict, info)."""
    root = Path(root)
    before = {f: (root / f).read_text() for f in texts}
    for f, hs in (added_headers or {}).items():
        prover.note_include(f, hs)
    tus, nat, why = prover.begin(list(texts))
    if tus is None:
        return why, {}
    folded = {}
    try:
        for f, t in texts.items():
            (root / f).write_text(t)
        units.drop(texts)
        if fold and touched:
            folded = fold_touched(root, sorted(f for f in texts if f.endswith('.c')), touched)
            for f, t in folded.items():
                before.setdefault(f, (root / f).read_text())
                (root / f).write_text(t)
            units.drop(folded)
        final = {f: (root / f).read_text() for f in before}
        rises = [(f, r) for f in final if f.endswith('.c') for r in debt_rises(f, before[f], final[f])]
        hdr = [f for f in final if f.endswith('.h') and casts_of(f, final[f]) > casts_of(f, before[f])]
        if rises or hdr:
            raise RuntimeError('debt_rise:%s' % ((rises or hdr)[0],))
        verdict = prover.check(tus, nat, label)
        if verdict:
            raise RuntimeError(verdict)
    except Exception as exc:  # noqa: BLE001  roll the whole transaction back
        for f, t in before.items():
            (root / f).write_text(t)
        units.drop(before)
        return str(exc)[:400] or type(exc).__name__, dict(tus=len(tus))
    casts = sum(casts_of(f, before[f]) - casts_of(f, final[f]) for f in final)
    return '', dict(tus=len(tus), files=sorted(final), casts_removed=casts, folds=len(folded), before=before)


def apply_families(root, out, census_rows, probes, scope, exclude, def_scope, workers, max_closure, log,
                   passes=3):
    root = Path(root).resolve()
    units = Units(root)
    prover = Prover(root, out, workers, max_closure, log)
    t0 = time.time()
    index = Index(root)
    log('index: %d names with typed declarations (%.0fs)' % (len(index.typed), time.time() - t0))
    editable = lambda f: in_scope(f, scope, exclude)
    def_ok = lambda f: in_scope(f, def_scope, exclude)
    # every refused callee is re-evaluated on the current text (proposals first): an earlier family can
    # retype the holders a later one needs, so refused families get further passes until nothing changes
    fams = collections.OrderedDict()
    for r in sorted(census_rows, key=lambda r: not r.get('proposed')):
        if r.get('param') != '*' or ':' not in r['definition']:
            fams.setdefault((r['symbol'], r['definition']), []).append(r)
    sdk_probes = collections.defaultdict(list)
    for p in probes:
        if p['status'] == 'native_type_error' and ':' not in p['edit']['definition']:
            sdk_probes[p['symbol']].append(p)
    results, originals = {}, {}
    pending = list(fams)
    for npass in range(1, passes + 1):
        progress = run_pass(root, prover, units, index, pending, sdk_probes, editable, def_ok, results, originals,
                            log, npass)
        pending = [k for k in pending if results[k]['verdict'] == 'refused']
        log('pass %d: %d accepted, %d still refused' % (npass, progress, len(pending)))
        if not progress or not pending:
            break
    return list(results.values()), prover, originals, units


def run_pass(root, prover, units, index, fams, sdk_probes, editable, def_ok, results, originals, log, npass):
    accepted = 0
    for n, (symbol, definition) in enumerate(fams):
        key = (symbol, definition)
        label = '%s@%s' % (symbol, definition.split(':')[0])
        t1 = time.time()
        if ':' in definition:
            plan, why = plan_family(root, units, index, symbol, definition, editable, def_ok)
        else:
            plan, why = plan_sdk_family(root, units, index, sdk_probes.get(symbol, []), editable)
        if plan is None:
            # every caller is already compatible (an earlier family fixed the holders): publish only
            results[key] = dict(symbol=symbol, definition=definition, npass=npass,
                                verdict='compatible' if why == 'nothing_to_change' else 'refused', reason=why)
            log('[%d/%d] %s refused: %s' % (n + 1, len(fams), label, why))
            continue
        for f in plan['texts']:
            originals.setdefault(f, (root / f).read_text())
        verdict, info = transact(root, prover, units, label, plan['texts'], plan['touched'], plan['headers'])
        for f in info.get('files', []):
            originals.setdefault(f, info['before'][f])
        rec = dict(symbol=symbol, definition=definition, plan=plan['summary'], tus=info.get('tus', 0), npass=npass)
        if verdict:
            rec.update(verdict='rolled_back', reason=verdict)
            log('[%d/%d] %s ROLLED BACK (%d TUs, %.0fs): %s' % (n + 1, len(fams), label, info.get('tus', 0),
                                                              time.time() - t1, verdict[:200]))
        else:
            rec.update(verdict='accepted', files=info['files'], casts_removed=info['casts_removed'], folds=info['folds'])
            accepted += 1
            log('[%d/%d] %s accepted: %s holders=%d, %d files, %d TUs, casts -%d (%.0fs)' % (
                n + 1, len(fams), label, ','.join(plan['summary']['params']) or '-', plan['summary']['holders'],
                len(info['files']), info['tus'], info['casts_removed'], time.time() - t1))
        results[key] = rec
    return accepted


def add_owner_prototypes(root, prover, units, symbols, editable, log):
    """Publish each accepted callee's prototype in its owning folder header when that header lacks one."""
    import tools.proto.prototypes as P
    root = Path(root)
    index = Index(root)
    rows = []
    for sym in sorted(symbols):
        ds = [d for d in index.definitions.get(sym, []) if d.path.startswith('src/')]
        if len(ds) != 1:
            rows.append(dict(symbol=sym, header='', verdict='skipped', reason='definitions:%d' % len(ds)))
            continue
        d = ds[0]
        if d.static or d.knr or d.varargs or d.complex:
            rows.append(dict(symbol=sym, header='', verdict='skipped', reason='static_or_old_style'))
            continue
        h = index.owner_header(d.path)
        if not h:
            rows.append(dict(symbol=sym, header='', verdict='skipped', reason='no_owner_header'))
            continue
        if h in index.typed.get(sym, ()) or h in index.empty.get(sym, ()):
            rows.append(dict(symbol=sym, header=h, verdict='skipped', reason='owner_declares_it'))
            continue
        if not editable(h):
            rows.append(dict(symbol=sym, header=h, verdict='skipped', reason='owner_not_editable'))
            continue
        th, tags, subst, why = P.P.type_needs(d, index.types)
        if why:
            rows.append(dict(symbol=sym, header=h, verdict='skipped', reason='type:' + why))
            continue
        proto = re.sub(r'\b(?:static|extern|inline|__inline__)\b\s*', '', P.P.substituted_proto(d, subst)).strip()
        proto = re.sub(r'\bregister\s+', '', proto)
        text = (root / h).read_text()
        closure = header_closure(root, h)
        new = text
        for t in sorted(th):
            if t != h and t not in closure:
                new = ensure_include(new, t)
        decl = ''.join(t + ';\n' for t in sorted(tags) if not re.search(r'\b' + re.escape(t) + r'\s*[;{]', text)) + proto + ';\n'
        m = list(re.finditer(r'(?m)^\s*#\s*endif\b[^\n]*\s*$', new))
        if not m:
            rows.append(dict(symbol=sym, header=h, verdict='skipped', reason='no_include_guard'))
            continue
        at = m[-1].start()
        new = new[:at].rstrip('\n') + '\n' + decl + '\n' + new[at:]
        verdict, info = transact(root, prover, units, 'owner:%s:%s' % (h, sym), {h: new}, fold=False)
        rows.append(dict(symbol=sym, header=h, verdict='rolled_back' if verdict else 'accepted', reason=verdict[:300],
                         tus=info.get('tus', 0)))
        log('owner %s %s: %s %s' % (h, sym, rows[-1]['verdict'], verdict[:160]))
    return rows


def apply_decls(root, prover, units, scope, exclude, symbols, log):
    """Publish the accepted callees' prototypes at their declaration sites, one site at a time, each proven."""
    import tools.proto.prototypes as P
    root = Path(root).resolve()
    corpus, types, remaining, edits, holds = P.candidates(root, scope, symbols=symbols)
    edits = [e for e in edits if in_scope(e.file, scope, exclude)]
    rows = []
    for e in edits:
        text = (root / e.file).read_text()
        try:
            new = P.rewrite(text, [e])
        except Exception as exc:  # noqa: BLE001
            rows.append(dict(file=e.file, symbol=e.symbol, verdict='rewrite_error', reason=str(exc)[:200], action=e.action))
            continue
        hs = {e.file: {e.header} | set(filter(None, e.type_headers.split(';')))} if e.header or e.type_headers else None
        verdict, info = transact(root, prover, units, 'decl:%s:%s' % (e.file, e.symbol), {e.file: new},
                                 added_headers=hs, fold=False)
        rows.append(dict(file=e.file, symbol=e.symbol, verdict='rolled_back' if verdict else 'accepted',
                         reason=verdict[:300], action=e.action))
        log('decl %s %s (%s): %s %s' % (e.file, e.symbol, e.action, rows[-1]['verdict'], verdict[:160]))
    for h in holds:
        rows.append(dict(file=h['file'], symbol=h['symbol'], verdict='held', reason=h['reason'], action=''))
    return rows


def count_remaining(root, scope, exclude):
    r = subprocess.run([sys.executable, 'tools/proto/prototypes.py', '--check', '--max-remaining', '100000'],
                       cwd=root, capture_output=True, text=True)
    total = json.loads(r.stdout.strip().splitlines()[-1])['remaining']
    import tools.proto.prototypes as P
    corpus, types, _, sites = P.census(Path(root))
    rem = [s for s in sites if P.unprototyped(s, types)]
    return total, sum(1 for s in rem if in_scope(s.path, scope, exclude))


# --------------------------------------------------------------------------------------------- main

def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('mode', choices=('census', 'apply'))
    ap.add_argument('--root', type=Path, default=ROOT)
    ap.add_argument('--scope', nargs='+', default=[], help='caller/declaration files (and editable files)')
    ap.add_argument('--def-scope', nargs='*', help='definitions that may be retyped (default: --scope)')
    ap.add_argument('--exclude', nargs='*', default=[], help='paths owned by other lanes: never edited')
    ap.add_argument('--symbols', nargs='*', default=[])
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--census', type=Path, help='apply: reuse a census directory instead of re-running it')
    ap.add_argument('--workers', type=int, default=4)
    ap.add_argument('--max-closure', type=int, default=400, help='refuse transactions reaching more TUs')
    ap.add_argument('--no-decls', action='store_true', help='retype only; do not publish prototypes')
    ap.add_argument('--no-owner', action='store_true', help='do not add prototypes to owning folder headers')
    ap.add_argument('--passes', type=int, default=3, help='re-run refused families while a pass accepts any')
    args = ap.parse_args(argv)
    root = args.root.resolve()
    if root != ROOT:
        raise SystemExit('run the copy of this tool inside --root (tools/proto resolves ROOT from its own path)')
    os.chdir(root)
    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=True)
    if not (out / '.ignore').exists():
        (out / '.ignore').write_text('deps.json\nprobes.jsonl\n')
    logf = open(out / 'run.log', 'a')

    def log(msg):
        line = time.strftime('%H:%M:%S ') + msg
        print(line, flush=True)
        logf.write(line + '\n')
        logf.flush()

    def_scope = args.def_scope if args.def_scope is not None else args.scope
    def_ok = lambda f: in_scope(f, def_scope, args.exclude)
    cdir = out if args.mode == 'census' else (args.census or out / 'census')
    if args.mode == 'census' or not args.census:
        rows, sites, probes, counts = census(root, args.scope, args.symbols, args.exclude, args.workers, log, def_ok)
        cdir.mkdir(parents=True, exist_ok=True)
        write_tsv(cdir / 'holds.tsv', counts.pop('held'), ['file', 'symbol', 'reason', 'definition', 'evidence'])
        write_tsv(cdir / 'census.tsv', rows, CENSUS_FIELDS)
        write_tsv(cdir / 'sites.tsv', sites, SITE_FIELDS)
        with open(cdir / 'probes.jsonl', 'w') as fh:
            for p in probes:
                fh.write(json.dumps(p, sort_keys=True) + '\n')
        write_tsv(cdir / 'refusals.tsv', [dict(p, errors=len(p['errors']), first=(p['errors'][0][3] if p['errors'] and
                                                isinstance(p['errors'][0], (list, tuple)) else ''))
                                          for p in probes if p['status'] != 'ok'], ['file', 'symbol', 'status', 'errors', 'first'])
        summ = dict(counts, probes=dict(collections.Counter(p['status'] for p in probes)),
                    parameters=len(rows), klass=dict(collections.Counter(r.get('klass') for r in rows)),
                    fix_side=dict(collections.Counter(r.get('fix_side') for r in rows)),
                    failing_arguments=len(sites), site_fix=dict(collections.Counter(s['fix'] for s in sites)),
                    site_holder=dict(collections.Counter(s['holder'] for s in sites)))
        (cdir / 'summary.json').write_text(json.dumps(summ, indent=2, sort_keys=True) + '\n')
        log('census: ' + json.dumps(summ, sort_keys=True))
        if args.mode == 'census':
            return 0
    rows = read_tsv(cdir / 'census.tsv')
    probes = [json.loads(l) for l in (cdir / 'probes.jsonl').read_text().splitlines() if l.strip()]
    if args.symbols:
        rows = [r for r in rows if r['symbol'] in args.symbols]
    total0, scoped0 = count_remaining(root, args.scope, args.exclude)
    log('empty declarations before: %d tree-wide, %d in scope' % (total0, scoped0))
    results, prover, originals, units = apply_families(root, out, rows, probes, args.scope, args.exclude, def_scope,
                                                       args.workers, args.max_closure, log, args.passes)
    with open(out / 'families.jsonl', 'w') as fh:
        for r in results:
            fh.write(json.dumps(r, sort_keys=True) + '\n')
    accepted = sorted({r['symbol'] for r in results if r['verdict'] in ('accepted', 'compatible')})
    owners, decls = [], []
    editable = lambda f: in_scope(f, args.scope, args.exclude)
    if accepted and not args.no_decls:
        if not args.no_owner:
            owners = add_owner_prototypes(root, prover, units, [r['symbol'] for r in results if r['verdict'] == 'accepted'
                                                                 and ':' in r['definition']], editable, log)
            write_tsv(out / 'owners.tsv', owners, ['symbol', 'header', 'verdict', 'reason', 'tus'])
            for o in owners:
                if o['verdict'] == 'accepted':
                    originals.setdefault(o['header'], None)
        decls = apply_decls(root, prover, units, args.scope, args.exclude, accepted, log)
        write_tsv(out / 'decls.tsv', decls, ['file', 'symbol', 'verdict', 'action', 'reason'])
    total1, scoped1 = count_remaining(root, args.scope, args.exclude)
    changed = {f for f, t in originals.items() if t is None or (root / f).read_text() != t}
    changed |= {d['file'] for d in decls if d['verdict'] == 'accepted'}
    (out / 'changed_files.txt').write_text(''.join(f + '\n' for f in sorted(changed)))
    with open(out / 'receipt.jsonl', 'w') as fh:
        for r in prover.receipts:
            fh.write(json.dumps(r, sort_keys=True) + '\n')
    summ = dict(empty_declarations_before=dict(tree=total0, scope=scoped0),
                empty_declarations_after=dict(tree=total1, scope=scoped1),
                families=dict(collections.Counter(r['verdict'] for r in results)),
                refusal_reasons=dict(collections.Counter(re.split(r'[:@]', r['reason'])[0]
                                                         for r in results if r['verdict'] == 'refused')),
                rollback_reasons=dict(collections.Counter(re.split(r'[:@]', r['reason'])[0]
                                                          for r in results if r['verdict'] == 'rolled_back')),
                casts_removed_by_families=sum(r.get('casts_removed', 0) for r in results),
                owner_prototypes=dict(collections.Counter(o['verdict'] for o in owners)),
                declarations=dict(collections.Counter(d['verdict'] for d in decls)),
                tus_proven=len({r['source'] for r in prover.receipts}), changed_files=len(changed))
    (out / 'summary.json').write_text(json.dumps(summ, indent=2, sort_keys=True) + '\n')
    log('apply: ' + json.dumps(summ, sort_keys=True))
    return 0


if __name__ == '__main__':
    sys.exit(main())
