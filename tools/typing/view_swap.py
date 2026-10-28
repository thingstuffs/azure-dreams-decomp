#!/usr/bin/env python3
"""View census, local view retype and view-to-shared swap for the pointer-cast wave.

    view_swap.py retype  --folder src/town/minigame --out DIR [--apply]
    view_swap.py census  --folder src --out DIR

**retype** (the cast-removing pass).  A function-local `void *x` / `u8 *x` (one declarator, no storage
class but `register`) whose record casts all name one struct type V, e.g. `((S_80023A00_0 *)x)->unk_2A`,
is redeclared `V *x` and every `(V *)x` becomes `x`.  The variable is refused when any other use would
change meaning or need a new cast after the retype:

  - arithmetic, subscript, `*x`, `++`/`--`, compound assignment, address taken (`&x`);
  - an implicit conversion to anything but `void *` (a call argument or assignment into a typed pointer);
  - a bare use as a `u8 *` (passed or assigned where a `u8 *` is expected without a cast);
  - an assignment or initializer whose value is not already `void *`, `V *` or a null constant;
  - casts to two different record types (two views of one object are a census row, not a retype).
Explicit casts of x to other pointer types stay valid and stay as written; a following cast_fold pass folds
the raw `*(T *)((u8 *)x + K)` sites that the new type makes foldable.  Parameters are never retyped here
(their contract belongs to the prototype lanes): they are counted per folder as the parameter pool.

**census** (tool B decision table).  Every generated view (`S_<addr>...`, `Rec_*`, `Row_*`, `R<n>_*`) that
a file defines is listed with the fields the file uses (offset, type, read/write), its casts by operand
type, and its decision against the canonical shared types (include/shared, common.h, game.h, globals.h,
PsyQ) laid out anywhere in the scanned TUs:

  evidenced:<S>     the file casts a shared-typed S expression to the view, or the same base is also cast to
                    S in the same function, and every used field matches S exactly (reads by exact type,
                    plain stores by width) inside S's size;
  unique:<S>        no evidence, but exactly one shared type is compatible (a lane must confirm identity);
  ambiguous:<n>     n shared types are compatible and nothing says which;
  incompatible      evidence names S but a used field does not match (first failing field recorded);
  unused / no_candidate.
Swapping a view for S (`--swap`) rewrites only `evidenced` views whose every use is a member access through
a cast from an S-typed expression (`((V *)s)->f` -> `s->canon`); the view typedef is removed when unused.
"""
from __future__ import annotations

import argparse
import collections
from concurrent.futures import ProcessPoolExecutor
import json
from pathlib import Path
import re
import sys

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent)]
import cast_ast as A  # noqa: E402
import cast_fold as F  # noqa: E402
import field_census as C  # noqa: E402

GENERATED = re.compile(r'^(?:S_(?:func_)?[0-9A-Fa-f]{8}\w*|Rec_\w+|Row_\w+|R\d+_\w+)$')


def cast_record(unit, cast):
    """(record key, written type name) for an explicit cast to a complete record pointer."""
    t = C.qtype(cast)
    key = unit.record_of_pointer(t)
    if not key:
        return None
    name = re.sub(r'\s*\*\s*$', '', t.strip())
    return key, name


def up(parents, node):
    p = parents.get(id(node))
    while p is not None and p.get('kind') == 'ParenExpr':
        node, p = p, parents.get(id(p))
    return node, p


def classify_use(unit, ref, parents, var_type):
    """One DeclRefExpr use of a byte/void pointer local -> (kind, detail)."""
    node, p = up(parents, ref)
    if p is None:
        return 'unknown', None
    k = p.get('kind')
    if k == 'BinaryOperator' and p.get('opcode') == '=' and A.kids(p)[0] is node:
        return 'assign', A.kids(p)[1]
    if k == 'UnaryOperator' and p.get('opcode') == '&':
        return 'refuse', 'address_taken'
    if k in ('CompoundAssignOperator',) or (k == 'UnaryOperator' and p.get('opcode') in ('++', '--')):
        return 'refuse', 'modified_arithmetic'
    if not (k == 'ImplicitCastExpr' and p.get('castKind') == 'LValueToRValue'):
        return 'refuse', 'use_' + k
    node, q = up(parents, p)
    if q is None:
        return 'refuse', 'use_unknown'
    qk = q.get('kind')
    if qk == 'CStyleCastExpr':
        rec = cast_record(unit, q)
        if rec:
            return 'record_cast', (q, rec)
        return 'other_cast', q
    if qk == 'ImplicitCastExpr':
        ck = q.get('castKind')
        if ck in ('BitCast', 'NoOp'):
            target = unit.canon(C.qtype(q))
            if target == 'void*':
                return 'neutral', None
            return 'refuse', 'implicit_to_' + ('record' if target.startswith('rec:') else 'pointer')
        if ck in ('PointerToBoolean',):
            return 'neutral', None
        if ck in ('PointerToIntegral',):
            return 'refuse', 'pointer_to_integer'
        return 'refuse', 'implicit_' + str(ck)
    if qk in ('BinaryOperator',) and q.get('opcode') in ('==', '!='):
        other = [x for x in A.kids(q) if x is not node][0]
        o = A.strip_implicit(other)
        if C.int_value(o) == 0 or unit.canon(C.qtype(o)) == 'void*':
            return 'neutral', None
        return 'refuse', 'pointer_compare'
    if qk in ('BinaryOperator',) and q.get('opcode') in ('&&', '||'):
        return 'neutral', None
    if qk == 'UnaryOperator' and q.get('opcode') == '!':
        return 'neutral', None
    if qk in ('IfStmt', 'WhileStmt', 'DoStmt', 'ForStmt', 'ConditionalOperator') and unit.canon(var_type) == 'void*':
        return 'neutral', None
    if qk in ('IfStmt', 'WhileStmt', 'DoStmt', 'ForStmt'):
        return 'neutral', None
    if unit.canon(var_type) == 'void*' and qk in ('CallExpr', 'ReturnStmt', 'VarDecl', 'BinaryOperator') \
            and not (qk == 'BinaryOperator' and q.get('opcode') not in ('=',)):
        # A void * flowing into a void * slot (no conversion node) stays a void * conversion of V *.
        return 'neutral', None
    if qk == 'BinaryOperator' and q.get('opcode') in ('+', '-'):
        return 'refuse', 'arithmetic'
    if qk == 'ArraySubscriptExpr':
        return 'refuse', 'subscript'
    if qk == 'UnaryOperator' and q.get('opcode') == '*':
        return 'refuse', 'dereference'
    return 'refuse', 'byte_pointer_use_' + qk


def assignable(unit, rhs, key):
    """Can rhs be stored into a `V *` (record `key`) with no cast?"""
    r = A.strip_implicit(rhs)
    if C.int_value(r) == 0:
        return True
    t = unit.canon(C.qtype(r))
    if t == 'void*':
        return True
    if r.get('kind') == 'CStyleCastExpr':
        rec = cast_record(unit, r)
        return bool(rec and rec[0] == key)
    return unit.record_of_pointer(C.qtype(r)) == key


def plan_function(unit, file, fn, text):
    """Retype plans and refusal counts for one function."""
    parents = {}
    nodes = []
    for n, p in A.walk(fn):
        parents[id(n)] = p
        nodes.append(n)
    decls = {}
    for n in nodes:
        if n.get('kind') in ('VarDecl', 'ParmVarDecl') and n.get('storageClass') not in ('static', 'extern'):
            t = C.qtype(n)
            r = unit.canon(t)
            if r == 'void*' or (r.endswith('*') and not r.endswith('**') and r[:-1] in A.BYTE_POINTEES):
                decls[n['id']] = n
    uses = collections.defaultdict(list)
    for n in nodes:
        if n.get('kind') == 'DeclRefExpr':
            did = (n.get('referencedDecl') or {}).get('id')
            if did in decls:
                uses[did].append(n)
    plans, pool = [], collections.Counter()
    for did, decl in decls.items():
        refs = uses.get(did, [])
        records, casts, why = {}, [], None
        assigns = []
        if decl.get('kind') == 'VarDecl' and decl.get('init') and A.kids(decl):
            assigns.append(A.kids(decl)[0])
        for ref in refs:
            kind, detail = classify_use(unit, ref, parents, C.qtype(decl))
            if kind == 'refuse':
                why = why or detail
            elif kind == 'assign':
                assigns.append(detail)
            elif kind == 'record_cast':
                cast, (key, name) = detail
                records.setdefault(key, name)
                casts.append((cast, ref))
        if not casts:
            continue
        param = decl.get('kind') == 'ParmVarDecl'
        mapped = {}
        if len(records) > 1:
            key, mapped = merge_views(unit, records, casts, parents)
            if key is None:
                why = why or 'several_record_types'
                key = next(iter(records))
        else:
            key = next(iter(records))
        value_edits, added = [], 0
        if not why:
            for rhs in assigns:
                if assignable(unit, rhs, key):
                    continue
                edit = value_edit(unit, rhs, text, records[key])
                if edit is None:
                    why = 'assigned_value_in_macro'
                    break
                value_edits.append(edit[0])
                added += edit[1]
            if not why and added >= len(casts):
                why = 'casts_would_not_decrease'
        if param:
            pool['parameter:' + ('ok' if not why else why)] += len(casts)
            continue
        if why:
            pool['local_refused:' + why] += len(casts)
            continue
        edit = decl_edit(unit, decl, parents, text, records[key])
        if isinstance(edit, str):
            pool['local_refused:' + edit] += len(casts)
            continue
        edits = [edit] + value_edits
        removed = 0
        for cast, ref in casts:
            rng = A.node_range(cast, text)
            vr = A.node_range(ref, text)
            if rng is None or vr is None:
                why = 'cast_in_macro'
                break
            if cast_record(unit, cast)[0] != key:
                # Another view of the same object: its member access is renamed onto the chosen type.
                if id(cast) not in mapped:
                    continue
                leaf, path = mapped[id(cast)]
                lr = A.node_range(leaf, text)
                if lr is None:
                    why = 'cast_in_macro'
                    break
                edits.append((lr[0], lr[1], text[vr[0]:vr[1]] + '->' + path))
                removed += 1
                continue
            removed += 1
            outer, holder = cast, parents.get(id(cast))
            # Drop the parentheses that only grouped the cast: ((V *)x)->f -> x->f.
            while holder is not None and holder.get('kind') == 'ParenExpr':
                outer, holder = holder, parents.get(id(holder))
            orng = A.node_range(outer, text) or rng
            if outer is not cast and not (orng[0] and (text[orng[0] - 1].isalnum() or text[orng[0] - 1] == '_')) \
                    and (holder or {}).get('kind') != 'UnaryExprOrTypeTraitExpr':
                rng = orng
            edits.append((rng[0], rng[1], text[vr[0]:vr[1]]))
        if why:
            pool['local_refused:' + why] += len(casts)
            continue
        if removed <= added:
            pool['local_refused:casts_would_not_decrease'] += len(casts)
            continue
        plans.append({'file': file, 'func': fn['name'], 'var': decl['name'], 'type': records[key],
                      'casts': removed - added, 'added_casts': added, 'edits': edits, 'line': decl.get('_l'),
                      'merged_views': sorted(records[k] for k in records if k != key)})
        pool['local_retyped'] += removed - added
    return plans, pool


def access_leaf(unit, member, parents):
    """(leaf node, byte offset, leaf type) of `cast->m(.n)*` starting at an arrow MemberExpr."""
    base_key = unit.record_of_pointer(C.qtype(A.kids(member)[0]))
    off = member_offset(unit, base_key, member.get('name')) if base_key else None
    if off is None:
        return None
    leaf, p = member, parents.get(id(member))
    while p is not None and p.get('kind') == 'MemberExpr' and not p.get('isArrow') and A.kids(p)[0] is leaf:
        inner = unit.T.record(C.qtype(leaf))
        sub = member_offset(unit, inner, p.get('name')) if inner else None
        if sub is None:
            return None
        off += sub
        leaf, p = p, parents.get(id(p))
    return leaf, off, C.qtype(leaf)


def merge_views(unit, records, casts, parents):
    """Pick one record type for a variable seen through several: every member access through the other
    casts must name a member of the chosen type at the same offset with the same canonical type.

    Shared (strong) types are preferred, then the largest view.  Returns (key, {id(cast): (leaf, path)}) or
    (None, {})."""
    def rank(k):
        strong = unit.T.type_identity(k)[1] and not GENERATED.match(k)
        return (not strong, -(unit.layouts[k].get('size') or 0), k)

    for chosen in sorted(records, key=rank):
        mapped, ok = {}, True
        for cast, ref in casts:
            k = cast_record(unit, cast)[0]
            if k == chosen:
                continue
            node, p = up(parents, cast)
            if p is None or p.get('kind') != 'MemberExpr' or not p.get('isArrow'):
                continue        # stays an explicit cast to the other type
            got = access_leaf(unit, p, parents)
            if got is None:
                ok = False
                break
            leaf, off, t = got
            want = unit.canon(t)
            path = next((pth for pth, lt, _ in unit.leaves_at(chosen, off)
                         if not F.PAD.search(pth) and unit.canon(lt) == want
                         and unit.volatile(lt) == unit.volatile(t)), None)
            if path is None:
                ok = False
                break
            mapped[id(cast)] = (leaf, path)
        if ok and mapped:
            return chosen, mapped
    return None, {}


def value_edit(unit, rhs, text, type_name):
    """((start, end, replacement), casts added) storing rhs into the retyped local.

    An explicit cast to a byte/void pointer is respelled as the new type (no new cast); any other value
    is wrapped in one `(V *)` cast."""
    r = A.strip_implicit(rhs)
    rng = A.node_range(r, text)
    if rng is None:
        return None
    if r.get('kind') == 'CStyleCastExpr':
        m = re.match(r'\(\s*[^()]*?\*\s*\)', text[rng[0]:rng[1]])
        if m and not re.search(r'\(\s*\*', m.group(0)):
            return (rng[0], rng[0] + m.end(), '(%s *)' % type_name), 0
    value = text[rng[0]:rng[1]]
    if r.get('kind') not in A.POSTFIX_KINDS and not (r.get('kind') == 'UnaryOperator' and r.get('opcode') == '&'):
        value = '(' + value + ')'
    return (rng[0], rng[1], '(%s *)%s' % (type_name, value)), 1


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
    spelled = text[rng[0]:loc]
    m = re.fullmatch(r'(\s*(?:register\s+)?)((?:unsigned\s+char|signed\s+char|char|u8|s8|void)\s*\*\s*)', spelled)
    if not m:
        return 'decl_spelling'
    return (rng[0] + m.end(1), loc, type_name + ' *')


def retype_tu(args):
    root, rel, recipe, files = args
    try:
        unit, error = A.clang_unit(root, rel, recipe)
    except Exception as exc:
        return {'tu': rel, 'error': str(exc)[-300:], 'plans': [], 'pool': {}}
    if unit is None:
        return {'tu': rel, 'error': error, 'plans': [], 'pool': {}}
    plans, pool = [], collections.defaultdict(collections.Counter)
    for file, fn in unit.functions(set(files)):
        p, c = plan_function(unit, file, fn, unit.text(file))
        plans.extend(p)
        pool[file].update(c)
    return {'tu': rel, 'error': error, 'plans': plans, 'pool': {f: dict(c) for f, c in pool.items()}}


def apply_plans(root, plans):
    by_file = collections.defaultdict(list)
    for p in plans:
        by_file[p['file']].extend(p['edits'])
    for file, edits in by_file.items():
        path = Path(root) / file
        text = path.read_text()
        edits = sorted(set(map(tuple, edits)), reverse=True)
        for (a, b, _), (c, d, _) in zip(edits[1:], edits):
            if b > c:
                raise ValueError('overlapping retype edits in ' + file)
        for a, b, rep in edits:
            text = text[:a] + rep + text[b:]
        path.write_text(text)
    return {f: len(e) for f, e in by_file.items()}


def retype(root, files, workers=6):
    tus, _ = F.physical_for(root, files)
    jobs = [(str(root), tu, recipe, sorted(files)) for tu, recipe in sorted(tus.items())]
    plans, pool, errors, seen = [], collections.defaultdict(collections.Counter), [], set()
    with ProcessPoolExecutor(max_workers=max(1, workers)) as ex:
        for res in ex.map(retype_tu, jobs, chunksize=4):
            if res['error']:
                errors.append((res['tu'], res['error']))
            for p in res['plans']:
                k = (p['file'], p['func'], p['var'])
                if k not in seen:
                    seen.add(k)
                    plans.append(p)
            for f, c in res['pool'].items():
                pool[f].update(c)
    return plans, pool, errors


# ---------------------------------------------------------------------- census (tool B)

def view_census_tu(args):
    """Per generated view defined in the scanned files: used fields, cast operands, evidence."""
    root, rel, recipe, files = args
    try:
        unit, error = A.clang_unit(root, rel, recipe)
    except Exception as exc:
        return {'tu': rel, 'error': str(exc)[-300:], 'views': {}, 'shared': {}}
    if unit is None:
        return {'tu': rel, 'error': error, 'views': {}, 'shared': {}}
    return dict(view_census_unit(unit, files), tu=rel, error=error)


def view_census_unit(unit, files, with_shared=True):
    """Census rows of the views `files` define, plus the shared layouts this TU sees."""
    views = {}
    fileset = set(files)

    def view_of(key):
        f = unit.record_files.get(key, '')
        name = key
        if f not in fileset or not GENERATED.match(name.split(':')[-1]):
            return None
        if (f, name) not in views:
            lay = unit.layouts.get(key, {})
            views[(f, name)] = {'file': f, 'view': name, 'size': lay.get('size'), 'fields': {},
                                'operands': collections.Counter(), 'evidence': collections.Counter(),
                                'casts': 0, 'arith': False}
        return views[(f, name)]

    for file, fn in unit.functions(fileset):
        parents, nodes = {}, []
        for n, p in A.walk(fn):
            parents[id(n)] = p
            nodes.append(n)
        # shared casts of each base variable in this function (evidence for its views)
        shared_of = collections.defaultdict(set)
        view_bases = []
        for n in nodes:
            if n.get('kind') != 'CStyleCastExpr':
                continue
            rec = cast_record(unit, n)
            if not rec:
                continue
            op = A.strip_implicit(A.kids(n)[0])
            base = op['referencedDecl'].get('id') if op.get('kind') == 'DeclRefExpr' else None
            ident, strong = unit.T.type_identity(rec[0])
            v = view_of(rec[0])
            if v is not None:
                v['casts'] += 1
                ot = unit.T.resolve(C.qtype(op))
                okey = unit.record_of_pointer(C.qtype(op))
                if okey:
                    oid, ostrong = unit.T.type_identity(okey)
                    cls = 'shared' if ostrong and not GENERATED.match(okey) else 'view'
                    if cls == 'shared':
                        v['evidence'][okey] += 1
                elif ot == 'void*':
                    cls = 'void'
                elif ot.endswith('*') and ot[:-1] in A.BYTE_POINTEES:
                    cls = 'byte'
                elif op.get('kind') == 'BinaryOperator':
                    cls = 'arith'
                else:
                    cls = 'other'
                v['operands'][cls] += 1
                if base is not None:
                    view_bases.append((base, v))
            elif strong and base is not None and not GENERATED.match(rec[0]):
                shared_of[base].add(rec[0])
        for base, v in view_bases:
            for s in shared_of.get(base, ()):
                v['evidence'][s] += 1
        # member uses through any expression of view type
        for n in nodes:
            if n.get('kind') != 'MemberExpr':
                continue
            b = A.kids(n)[0]
            bt = C.qtype(b)
            key = unit.record_of_pointer(bt) if n.get('isArrow') else unit.T.record(bt)
            if not key:
                continue
            v = view_of(key)
            if v is None:
                continue
            off = member_offset(unit, key, n.get('name'))
            if off is None:
                continue
            # descend through union/struct member selections to the accessed leaf
            leaf, path = n, [n.get('name')]
            p = parents.get(id(leaf))
            while p is not None and p.get('kind') == 'MemberExpr' and not p.get('isArrow') and A.kids(p)[0] is leaf:
                inner = unit.T.record(C.qtype(leaf))
                sub = member_offset(unit, inner, p.get('name')) if inner else None
                if sub is None:
                    break
                off += sub
                path.append(p.get('name'))
                leaf, p = p, parents.get(id(p))
            rw = 'r'
            hold = p
            if hold is not None and hold.get('kind') == 'BinaryOperator' and hold.get('opcode') == '=' and A.kids(hold)[0] is leaf:
                rw = 'w'
            elif hold is not None and (hold.get('kind') == 'CompoundAssignOperator' or
                                       (hold.get('kind') == 'UnaryOperator' and hold.get('opcode') in ('++', '--'))):
                rw = 'rw'
            elif hold is not None and hold.get('kind') == 'UnaryOperator' and hold.get('opcode') == '&':
                rw = 'addr'
            t = C.qtype(leaf)
            fk = '%#x' % off
            slot = v['fields'].setdefault(fk, {'types': {}, 'rw': set(), 'names': set()})
            slot['types'][unit.canon(t)] = t
            slot['rw'].add(rw)
            slot['names'].add('.'.join(path))
        for n in nodes:
            # a view used with pointer arithmetic or subscripts needs an exact size
            if n.get('kind') in ('BinaryOperator', 'ArraySubscriptExpr', 'UnaryOperator'):
                if n.get('kind') == 'UnaryOperator' and n.get('opcode') not in ('++', '--'):
                    continue
                if n.get('kind') == 'BinaryOperator' and n.get('opcode') not in ('+', '-'):
                    continue
                for x in A.kids(n)[:1]:
                    key = unit.record_of_pointer(C.qtype(x))
                    v = view_of(key) if key else None
                    if v is not None:
                        v['arith'] = True
    shared = {}
    for key, lay in unit.layouts.items() if with_shared else ():
        ident, strong = unit.T.type_identity(key)
        if strong and not GENERATED.match(key) and not key.startswith('@') and lay.get('size'):
            shared[key] = shared_leaves(unit, key)
    out = {}
    for (f, name), v in views.items():
        v['operands'] = dict(v['operands'])
        v['evidence'] = dict(v['evidence'])
        for slot in v['fields'].values():
            slot['rw'] = sorted(slot['rw'])
            slot['names'] = sorted(slot['names'])
        out[f + '::' + name] = v
    return {'views': out, 'shared': shared}


def member_offset(unit, key, name):
    lay = unit.layouts.get(key)
    if not lay or not name:
        return None
    stack = list(lay['kids'])
    while stack:
        node = stack.pop(0)
        if node['name'] == name and not node['bits']:
            return node['off']
        if not node['name']:
            stack.extend(node['kids'])
    return None


def shared_leaves(unit, key):
    """{offset: [(path, canonical type, size)]} for every scalar/pointer leaf of a shared record."""
    out = collections.defaultdict(list)
    size = unit.layouts[key].get('size') or 0
    for off in range(size):
        for path, t, _ in unit.leaves_at(key, off):
            if F.PAD.search(path):
                continue
            c = unit.canon(t)
            if c.startswith('rec:') or '[' in c:
                continue
            out[off].append((path, c, unit.size(t)))
    # A union of scalar arrays (ScratchPad) fits every view: it is never structural evidence.
    raw = bool(out) and all('[' in path for leaves in out.values() for path, _, _ in leaves)
    return {'size': size, 'leaves': {str(k): v for k, v in out.items()}, 'raw': raw}


def field_ok(slot, leaves):
    """First member path of a shared type giving the same access as every use of a view field."""
    want = set(slot['types'])
    reads = any(rw != 'w' for rw in slot['rw'])
    for path, canon, size in leaves:
        if want == {canon}:
            return path
    if not reads and len(want) == 1:
        w = next(iter(want))
        wsize = {'char': 1, 'signed char': 1, 'unsigned char': 1, 'short': 2, 'unsigned short': 2,
                 'int': 4, 'unsigned int': 4}.get(w)
        for path, canon, size in leaves:
            if wsize and size == wsize and canon in ('char', 'signed char', 'unsigned char', 'short',
                                                     'unsigned short', 'int', 'unsigned int'):
                return path
    return None


def decide(view, shared):
    """Census decision for one view against the shared-type universe."""
    fields = view['fields']
    if not fields:
        return {'decision': 'unused', 'candidates': []}

    def compatible(s):
        info = shared.get(s)
        if not info:
            return None, 'not_laid_out'
        if view['arith'] and view['size'] != info['size']:
            return None, 'size_differs_with_arithmetic'
        mapping = {}
        for off, slot in sorted(fields.items(), key=lambda x: int(x[0], 16)):
            if int(off, 16) >= info['size']:
                return None, 'field_%s_beyond_%d' % (off, info['size'])
            path = field_ok(slot, info['leaves'].get(str(int(off, 16)), []))
            if not path:
                return None, 'field_%s_%s' % (off, '/'.join(sorted(slot['types'])))
            mapping[off] = path
        return mapping, None

    evidence = sorted(view['evidence'], key=lambda s: -view['evidence'][s])
    if evidence:
        results = {}
        for s in evidence:
            mapping, why = compatible(s)
            results[s] = (mapping, why)
        good = [s for s in evidence if results[s][0] is not None]
        if len(good) == 1 or (good and len(set(good)) == 1):
            return {'decision': 'evidenced', 'shared': good[0], 'mapping': results[good[0]][0],
                    'candidates': good}
        if len(good) > 1:
            return {'decision': 'evidence_conflict', 'candidates': good}
        s = evidence[0]
        return {'decision': 'incompatible', 'shared': s, 'reason': results[s][1], 'candidates': []}
    good = []
    for s in shared:
        if shared[s].get('raw'):
            continue
        mapping, why = compatible(s)
        if mapping is not None:
            good.append((s, mapping))
    if not good:
        return {'decision': 'no_candidate', 'candidates': []}
    if len(good) == 1:
        return {'decision': 'unique', 'shared': good[0][0], 'mapping': good[0][1], 'candidates': [good[0][0]]}
    return {'decision': 'ambiguous', 'candidates': sorted(s for s, _ in good)[:12], 'n': len(good)}


def census(root, files, workers=6):
    tus, _ = F.physical_for(root, files)
    jobs = [(str(root), tu, recipe, sorted(files)) for tu, recipe in sorted(tus.items())]
    views, shared, errors = {}, {}, []
    with ProcessPoolExecutor(max_workers=max(1, workers)) as ex:
        for res in ex.map(view_census_tu, jobs, chunksize=4):
            if res['error']:
                errors.append((res['tu'], res['error']))
            for k, v in res['views'].items():
                if k not in views:
                    views[k] = v
            for k, s in res['shared'].items():
                shared.setdefault(k, s)
    rows = []
    for k, v in sorted(views.items()):
        d = decide(v, shared)
        rows.append(dict(v, **d))
    return rows, shared, errors


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('mode', choices=('retype', 'census'))
    ap.add_argument('--root', type=Path, default=HERE.parents[1])
    ap.add_argument('--folder', default='src')
    ap.add_argument('--file', nargs='*', default=[])
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--apply', action='store_true')
    ap.add_argument('--workers', type=int, default=6)
    args = ap.parse_args(argv)
    root = args.root.resolve()
    files = F.folder_files(root, args.folder, args.file)
    args.out.mkdir(parents=True, exist_ok=True)
    if args.mode == 'retype':
        plans, pool, errors = retype(root, files, args.workers)
        with open(args.out / 'retype_plan.jsonl', 'w') as fh:
            for p in plans:
                fh.write(json.dumps(p, sort_keys=True) + '\n')
        with open(args.out / 'retype_pool.tsv', 'w') as fh:
            fh.write('file\tbucket\tcasts\n')
            for f in sorted(pool):
                for b, n in sorted(pool[f].items()):
                    fh.write('%s\t%s\t%d\n' % (f, b, n))
        totals = collections.Counter()
        for c in pool.values():
            totals.update(c)
        summary = {'files': len(files), 'variables': len(plans), 'casts': sum(p['casts'] for p in plans),
                   'pool': dict(totals.most_common()), 'errors': errors[:20]}
        if args.apply:
            apply_plans(root, plans)
            summary['applied'] = True
        (args.out / 'retype_summary.json').write_text(json.dumps(summary, indent=2) + '\n')
        print(json.dumps({k: summary[k] for k in ('files', 'variables', 'casts')}))
        return 0
    rows, shared, errors = census(root, files, args.workers)
    with open(args.out / 'views.jsonl', 'w') as fh:
        for r in rows:
            fh.write(json.dumps(r, sort_keys=True, default=list) + '\n')
    decisions = collections.Counter(r['decision'] for r in rows)
    summary = {'views': len(rows), 'decisions': dict(decisions.most_common()), 'shared_types': len(shared),
               'casts_by_decision': {d: sum(r['casts'] for r in rows if r['decision'] == d) for d in decisions},
               'errors': errors[:20]}
    (args.out / 'census_summary.json').write_text(json.dumps(summary, indent=2) + '\n')
    print(json.dumps(summary['decisions']))
    return 0


if __name__ == '__main__':
    sys.exit(main())
