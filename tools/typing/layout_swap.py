#!/usr/bin/env python3
"""Family view swap: replace generated layout views (S_<addr>...) with shared game types, proven by the build graph.

    layout_swap.py plan   --family F.json --out DIR [--workers 8]
    layout_swap.py apply  --family F.json --out DIR [--workers 8] [--no-fold] [--raw-fold] [--keep-on-warning]
    layout_swap.py prove  --out DIR [--workers 8]          (after apply; reverts failing files, re-proves)
    layout_swap.py revert --out DIR --files F...           (restore files from DIR/originals)

A *family* lists the generated views that census evidence identifies as views of one real object
(tools/typing/layout_census.py `assign` writes candidate files).  family.json:

    {"groups": [{"type": "TownPositionState", "header": "shared/town_pointees.h",
                 "views": ["src/town/scene/toggle.c:S_8077DC0C_1", "include/town/bar.h:S_800B0000_2"]}],
     "retype_fields": [{"header": "shared/town_root.h", "struct": "Rec_D_80016000", "field": "position",
                        "type": "TownPositionState *"}],
     "require_anchor": true,                     (accept only views with typed-flow identity evidence)
     "hold": ["src/dungeon", "include/dungeon"]} (never edit these prefixes; their users refuse the view)
A single-type file ({"type", "header", "views"}) is one group.

Every listed view V must describe the same object at the same base as its type T (delta 0).  A view is
**accepted** only when every use the compiler sees can be respelled through T without changing any access:

  - each member access through V (`p->unk_1E`, `p->unk_04.s`, `s.unk_08`, `&p->unk_10`) reaches a member of T
    at the same byte offset whose type gives the same access (cast_fold.same_access: the same canonical type;
    a plain store whose value is unused may take a same-width integer of the other signedness; a pointer store
    may move between void * and a data pointer when the value needs no cast; a pointer read whose value only
    feeds an explicit cast, a void * conversion or a truth test may take any data-pointer member).  Union
    views reached through a named member (`unk_04.s`) map leaf by leaf.  Padding members are never named;
  - when V is used with a stride or a size (`p[i]`, `p + 1`, `((V *)x)[-1]`, `sizeof(V)`, a V object or
    array), sizeof(V) == sizeof(T);
  - no use lies inside a macro expansion, and every user file is compiled by a registered recipe.
Identity evidence per view: `anchored` (a T-typed value reaches the view: a cast of a T * expression, a load
of a T * global through a byte view, a T * member, or a one-level void * local assigned from one of those),
`conflict` / `mixed` (another record reaches it, including `(V *)((W *)x)->f` where W's member f points at
another record), `shape` (layout fit only).  A refused view keeps its typedef and every use.

`apply` (one batch, many files; every touched file is snapshotted to DIR/originals first):
  1. listed struct members are retyped in their headers (views are planned afterwards, so the new member
     type is identity evidence);
  2. member names through each accepted V become T member paths (exact Clang source ranges); every other
     token V (casts, declarators, prototypes, `struct V`) becomes T; V's typedef is deleted; a file that does
     not see T includes T's header after its last #include;
  3. folding (default): a cast converting a record expression to its own type is removed (`((T *)p)->f` ->
     `p->f`); view_swap.retype then retypes `void *` / `u8 *` locals whose record casts all name T, except
     variables that hold two objects (merged views, or values that would need a cast); then folds again.
     `--raw-fold` also runs cast_fold's `*(T *)p` folds (these can change gcc 2.x alias decisions, so
     cast_wave proves them site by site instead);
  4. guards: Clang pointer-conversion warnings are counted per physical TU before and after (any rise
     restores the whole batch unless --keep-on-warning); a C file whose per-function lexical debt
     (tools/lint/debt_check) rises is restored.
`prove` refreshes ledger/layout_inline.jsonl (merged TUs), runs tools/build/affected.py prove over every
edited file (rows, modules, placement copies, image relinks), reverts the files whose recipes are not PASS
(with the edited headers whose deleted views they use) and repeats until PASS.  Commit, then `make -j8`.

Outputs under --out: decisions.jsonl (one row per view: verdict, reason, evidence, every use), summary.json,
swap.patch, swap.log, originals/, prove-N.json, prove_summary.json.
"""
from __future__ import annotations

import argparse
import collections
from concurrent.futures import ProcessPoolExecutor
import difflib
import json
from pathlib import Path
import re
import sys

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent), str(HERE.parent / 'lint')]
import cast_ast as A  # noqa: E402
import cast_fold as F  # noqa: E402
import field_census as C  # noqa: E402

GENERATED = re.compile(r'^S_(?:func_)?[0-9A-Fa-f]{8}(?:_\w+)?$')
WORK = 'build/.layout_swap'
SIZEOF_KINDS = ('UnaryExprOrTypeTraitExpr',)


# ---------------------------------------------------------------------------------------------- shared type

def shared_type(root, type_name, header):
    """{'size', 'leaves': {off: [(path, canon, size, volatile)]}} of T from a two-line synthetic TU."""
    work = Path(root) / WORK
    work.mkdir(parents=True, exist_ok=True)
    probe = work / ('probe_%s.c' % re.sub(r'\W', '_', type_name))
    probe.write_text('#include "common.h"\n#include "%s"\n%s *layout_swap_probe;\n' % (header, type_name))
    rel = probe.relative_to(root).as_posix()
    unit, error = A.clang_unit(root, rel)
    if unit is None:
        raise SystemExit('cannot parse %s: %s' % (header, error))
    key = unit.T.record(type_name)
    if not key or key not in unit.layouts:
        raise SystemExit('%s is not a complete record in %s' % (type_name, header))
    size = unit.layouts[key].get('size') or 0
    leaves = collections.defaultdict(list)
    for off in range(size):
        for path, t, _ in unit.leaves_at(key, off):
            if F.PAD.search(path):
                continue
            leaves[off].append((path, unit.canon(t), unit.size(t), unit.volatile(t)))
    return {'type': type_name, 'header': header, 'key': key, 'size': size, 'leaves': dict(leaves)}


def same_access(unit, want, have, store_only, rhs):
    """cast_fold.same_access over T's precomputed leaf (canon, size, volatile)."""
    path, h, hsize, hvol = have
    if unit.volatile(want) != hvol:
        return False, 'volatile_differs'
    w = unit.canon(want)
    if '[' in w or '[' in h:
        return (w == h, 'array_member')
    if w.endswith('*') or h.endswith('*'):
        if not (w.endswith('*') and h.endswith('*')):
            return False, 'pointer_vs_integer'
        if 'fnptr*' in (w, h):
            return (w == h and w != 'fnptr*', 'function_pointer_differs')
        if w == h:
            return True, ''
        if store_only and 'void*' in (w, h) and rhs is not None:
            value = rhs
            while value.get('kind') in ('ParenExpr', 'ImplicitCastExpr') and A.kids(value) and \
                    value.get('castKind') in (None, 'BitCast', 'NoOp'):
                value = A.kids(value)[0]
            r = unit.canon(C.qtype(value))
            if C.int_value(rhs) == 0 or r in (h, 'void*') or (h == 'void*' and r.endswith('*')):
                return True, ''
        return False, 'pointer_type_differs'
    if w.startswith('rec:') or h.startswith('rec:'):
        return (w == h, 'aggregate_differs')
    if w == h:
        return True, ''
    if store_only and unit.size(want) == hsize and hsize in (1, 2, 4) and 'float' not in (w, h):
        return True, ''
    return False, 'signedness_differs' if unit.size(want) == hsize else 'width_differs'


# ---------------------------------------------------------------------------------------------- per-TU scan

def view_keys(unit, assign):
    """{record key: 'file:name'} for the assigned views this TU declares (matched by defining file)."""
    out = {}
    names = collections.defaultdict(set)
    for spec in assign:
        file, name = spec.rsplit(':', 1)
        names[name].add(file)
    for name, files in names.items():
        key = None
        if name in unit.typedefs:
            key = unit.T.record(name)
        elif name in unit.layouts:
            key = name
        if not key or key not in unit.layouts:
            continue
        where = unit.record_files.get(key) or unit.record_files.get(name) or ''
        if where.startswith('@'):
            where = where[1:]
        hit = [f for f in files if where == f or where.endswith('/' + f) or f == where.lstrip('./')]
        if hit:
            out[key] = hit[0] + ':' + name
        elif len(files) == 1 and not where:
            out[key] = next(iter(files)) + ':' + name
    return out


def store_context(parents, node):
    outer = node
    while parents.get(id(outer)) is not None and parents[id(outer)].get('kind') == 'ParenExpr':
        outer = parents[id(outer)]
    holder = parents.get(id(outer))
    if holder is not None and holder.get('kind') == 'BinaryOperator' and holder.get('opcode') == '=' \
            and A.kids(holder)[0] is outer:
        above = parents.get(id(holder))
        return above is None or above.get('kind') in F.STATEMENT_PARENTS, A.kids(holder)[1], 'w'
    if holder is not None and (holder.get('kind') == 'CompoundAssignOperator' or (
            holder.get('kind') == 'UnaryOperator' and holder.get('opcode') in ('++', '--'))):
        return False, None, 'rw'
    if holder is not None and holder.get('kind') == 'UnaryOperator' and holder.get('opcode') == '&':
        return False, None, 'addr'
    return False, None, 'r'


def opaque_pointer_read(unit, parents, leaf):
    """True when a pointer member read is consumed only by an explicit cast, a conversion to void *, a truth
    test or a comparison with null: its pointee type is then never observed."""
    node, p = leaf, parents.get(id(leaf))
    while p is not None and (p.get('kind') == 'ParenExpr' or (p.get('kind') == 'ImplicitCastExpr'
                                                              and p.get('castKind') == 'LValueToRValue')):
        node, p = p, parents.get(id(p))
    if p is None:
        return False
    k = p.get('kind')
    if k == 'CStyleCastExpr':
        return True
    if k == 'ImplicitCastExpr':
        if p.get('castKind') == 'PointerToBoolean':
            return True
        return p.get('castKind') in ('BitCast', 'NoOp') and unit.canon(C.qtype(p)) == 'void*'
    if k == 'UnaryOperator' and p.get('opcode') == '!':
        return True
    if k == 'BinaryOperator' and p.get('opcode') in ('==', '!=', '&&', '||'):
        if p.get('opcode') in ('&&', '||'):
            return True
        other = [x for x in A.kids(p) if x is not node]
        return bool(other) and C.int_value(other[0]) == 0
    return False


def anchor_record(unit, e, flow=None):
    """Record key of the typed value underneath casts: `(V *)p` with p a `T *`, `*(void **)&g` with g a
    `T *`, `(V *)s->f` with f a `T *` member.  None when the value is untyped all the way down."""
    for _ in range(12):
        if e is None:
            return None
        k = e.get('kind')
        if k in ('ParenExpr', 'ImplicitCastExpr', 'CStyleCastExpr'):
            key = pointee_key(unit, C.qtype(e)) if k != 'CStyleCastExpr' else None
            inner = A.kids(e)[0] if A.kids(e) else None
            if k == 'ImplicitCastExpr' and key and not GENERATED.match(key):
                return key
            e = inner
            continue
        if k == 'UnaryOperator' and e.get('opcode') == '*':
            inner = A.kids(e)[0]
            # *(void **)((s8 *)&g + 0): the load of a pointer global through a byte view.
            x = inner
            while x is not None and x.get('kind') in ('ParenExpr', 'ImplicitCastExpr', 'CStyleCastExpr') \
                    or (x is not None and x.get('kind') == 'BinaryOperator' and x.get('opcode') == '+'
                        and C.int_value(A.kids(x)[1]) == 0):
                x = A.kids(x)[0] if A.kids(x) else None
            if x is not None and x.get('kind') == 'UnaryOperator' and x.get('opcode') == '&':
                return pointee_key(unit, C.qtype(A.kids(x)[0]))
            return None
        if flow and k == 'DeclRefExpr':
            got = flow.get((e.get('referencedDecl') or {}).get('id'))
            if got and len(got) == 1:
                return next(iter(got))
        return pointee_key(unit, C.qtype(e))
    return None


def variable_flow(unit, nodes):
    """{variable decl id: {record keys}}: one-level flow of typed values into untyped pointer variables."""
    flow = collections.defaultdict(set)
    for node, parent in nodes:
        k = node.get('kind')
        if k == 'VarDecl' and node.get('init') and A.kids(node):
            var, value = node.get('id'), A.kids(node)[-1]
            t = C.qtype(node)
        elif k == 'BinaryOperator' and node.get('opcode') == '=':
            lhs = A.strip_parens(A.kids(node)[0])
            if lhs.get('kind') != 'DeclRefExpr':
                continue
            var, value = (lhs.get('referencedDecl') or {}).get('id'), A.kids(node)[1]
            t = C.qtype(lhs)
        else:
            continue
        r = unit.canon(t)
        if not (r == 'void*' or r.endswith('*') and r[:-1] in A.BYTE_POINTEES):
            continue
        got = anchor_record(unit, value)
        flow[var].add(got)
    return {v: {g for g in gs if g} for v, gs in flow.items() if None not in gs}


def pointee_key(unit, t):
    """Record key of a pointer-to-record type, complete or not."""
    r = unit.T.resolve(t)
    if not r.endswith('*') or r.endswith('**'):
        return None
    return unit.T.record(t)


def scan_tu(args):
    root, rel, recipe, assign, files, shareds = args
    try:
        unit, error = A.clang_unit(root, rel, recipe)
    except Exception as exc:
        return {'tu': rel, 'error': str(exc)[-300:], 'uses': [], 'sees': {}}
    if unit is None:
        return {'tu': rel, 'error': error, 'uses': [], 'sees': {}}
    keys = view_keys(unit, assign)
    uses = []
    leaves_of = {t: {int(k): v for k, v in info['leaves'].items()} for t, info in shareds.items()}
    present = {n.get('_f') for n, _ in A.walk(unit.tree) if n.get('_f')} | {rel}
    sees = {f: sorted(t for t in shareds if t in unit.typedefs) for f in files if f in present}
    nodes = []
    for node, parent in A.walk(unit.tree):
        nodes.append((node, parent))
    parents = {id(n): p for n, p in nodes}
    flow = variable_flow(unit, nodes)
    for node, parent in nodes:
        k = node.get('kind')
        f = node.get('_f') or rel
        if f not in files:
            continue
        if k == 'MemberExpr':
            base = A.kids(node)[0]
            bt = C.qtype(base)
            key = unit.record_of_pointer(bt) if node.get('isArrow') else unit.T.record(bt)
            if key not in keys:
                continue
            view = keys[key]
            off = A.member_offset(unit, key, node.get('name'))
            if off is None:
                uses.append({'view': view, 'file': f, 'line': node.get('_l'), 'kind': 'member', 'ok': False,
                             'why': 'member_offset_unknown'})
                continue
            leaf, p, chain = node, parents.get(id(node)), [node]
            while p is not None and p.get('kind') == 'MemberExpr' and not p.get('isArrow') and A.kids(p)[0] is leaf:
                inner = unit.T.record(C.qtype(leaf))
                sub = A.member_offset(unit, inner, p.get('name')) if inner else None
                if sub is None:
                    break
                off += sub
                leaf, p = p, parents.get(id(p))
                chain.append(leaf)
            text = unit.text(f)
            rec = {'view': view, 'file': f, 'line': leaf.get('_l'), 'kind': 'member', 'offset': off,
                   'leaf_type': C.qtype(leaf), 'old_path': '.'.join(n.get('name') for n in chain)}
            if A.in_macro(leaf) or A.in_macro(node):
                uses.append(dict(rec, ok=False, why='macro'))
                continue
            first = A.node_range(node, text)
            rng = A.node_range(leaf, text)
            if rng is None or first is None:
                uses.append(dict(rec, ok=False, why='source_range_unavailable'))
                continue
            # The first member name ends where its MemberExpr ends; the chain ends at the leaf.
            start, end = first[1] - len(node.get('name')), rng[1]
            old = text[start:end]
            if re.sub(r'\s+', '', old) != rec['old_path']:
                uses.append(dict(rec, ok=False, why='member_text_mismatch'))
                continue
            store_only, rhs, rw = store_context(parents, leaf)
            cands = leaves_of[assign[view]].get(off, [])
            chosen, why = None, 'no_member_at_offset' if not cands else None
            for exact in (True, False):
                for have in cands:
                    ok, reason = same_access(unit, C.qtype(leaf), have, store_only and not exact, rhs)
                    if ok:
                        chosen = have
                        break
                    why = why or reason
                if chosen:
                    break
            if chosen is None and rw == 'r' and unit.T.resolve(C.qtype(leaf)).endswith('*') \
                    and opaque_pointer_read(unit, parents, leaf):
                # The read value only feeds an explicit cast or a void * conversion: any data-pointer member
                # at the same offset gives the same load and the same converted value.
                for have in cands:
                    if have[1].endswith('*') and have[1] != 'fnptr*' and not have[3] \
                            and unit.T.resolve(C.qtype(leaf)) != 'fnptr*':
                        chosen = have
                        break
            if chosen is None:
                uses.append(dict(rec, rw=rw, ok=False, why=why or 'no_exact_member'))
                continue
            uses.append(dict(rec, rw=rw, ok=True, start=start, end=end, old=old, new=chosen[0]))
        elif k == 'CStyleCastExpr' and unit.record_of_pointer(C.qtype(node)) in keys:
            view = keys[unit.record_of_pointer(C.qtype(node))]
            got = anchor_record(unit, A.kids(node)[0], flow)
            if got and got not in keys:
                uses.append({'view': view, 'file': f, 'line': node.get('_l'), 'kind': 'anchor',
                             'anchor': _type_name(unit, got)})
            inner = A.kids(node)[0]
            while inner.get('kind') in ('ParenExpr', 'ImplicitCastExpr') and A.kids(inner):
                inner = A.kids(inner)[0]
            if inner.get('kind') == 'MemberExpr' and inner.get('isArrow'):
                bkey = unit.record_of_pointer(C.qtype(A.kids(inner)[0]))
                if bkey in keys:
                    # (V *)((W *)x)->f: the object f points at.  Under W's shared type, f's declared pointee
                    # is the evidence (a self link keeps one identity; another record is a second object).
                    off = A.member_offset(unit, bkey, inner.get('name'))
                    pointee = None
                    for have in leaves_of[assign[keys[bkey]]].get(off, []) if off is not None else []:
                        if have[1].startswith('rec:') and have[1].endswith('*') and not have[1].endswith('**'):
                            pointee = have[1][4:-1]
                    uses.append({'view': view, 'file': f, 'line': node.get('_l'), 'kind': 'anchor',
                                 'anchor': pointee or ('<pointee of %s+%s>' % (assign[keys[bkey]], off))})
        elif (k == 'VarDecl' and A.kids(node) and node.get('init')) or (
                k == 'BinaryOperator' and node.get('opcode') == '='):
            lhs_t = C.qtype(node) if k == 'VarDecl' else C.qtype(A.kids(node)[0])
            key = unit.record_of_pointer(lhs_t)
            if key in keys:
                got = anchor_record(unit, A.kids(node)[-1], flow)
                if got and got not in keys:
                    uses.append({'view': keys[key], 'file': f, 'line': node.get('_l'), 'kind': 'anchor',
                                 'anchor': _type_name(unit, got)})
            if k == 'VarDecl':
                t = C.qtype(node)
                r = unit.T.resolve(t)
                key = unit.T.record(t)
                if key in keys and not r.endswith('*'):
                    uses.append({'view': keys[key], 'file': f, 'line': node.get('_l'), 'kind': 'size',
                                 'size': unit.layouts[key].get('size')})
        elif k in SIZEOF_KINDS:
            t = (node.get('argType') or {}).get('qualType') or ''
            key = unit.T.record(t) if t else None
            if key in keys and not unit.T.resolve(t).endswith('*'):
                uses.append({'view': keys[key], 'file': f, 'line': node.get('_l'), 'kind': 'size',
                             'size': unit.layouts[key].get('size')})
        elif k in ('BinaryOperator', 'ArraySubscriptExpr', 'UnaryOperator', 'CompoundAssignOperator'):
            if k == 'BinaryOperator' and node.get('opcode') not in ('+', '-'):
                continue
            if k == 'UnaryOperator' and node.get('opcode') not in ('++', '--'):
                continue
            for x in A.kids(node)[:2]:
                key = unit.record_of_pointer(C.qtype(x))
                if key in keys:
                    uses.append({'view': keys[key], 'file': f, 'line': node.get('_l'), 'kind': 'size',
                                 'size': unit.layouts[key].get('size')})
        elif k in ('VarDecl', 'FieldDecl'):
            t = C.qtype(node)
            r = unit.T.resolve(t)
            key = unit.T.record(t)
            if key in keys and not r.endswith('*'):
                uses.append({'view': keys[key], 'file': f, 'line': node.get('_l'), 'kind': 'size',
                             'size': unit.layouts[key].get('size')})
    sizes = {spec: unit.layouts[key].get('size') for key, spec in keys.items()}
    return {'tu': rel, 'error': error, 'uses': uses, 'sees': sees, 'sizes': sizes}


def _type_name(unit, key):
    """Typedef name of a record key when one exists (anonymous records), else the key."""
    if key.startswith('@'):
        for name, t in unit.typedefs.items():
            if unit.T.record(name) == key:
                return name
    return key


# ---------------------------------------------------------------------------------------------- planning

TOKEN = re.compile(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|\b(?:struct\s+|union\s+)?([A-Za-z_]\w*)\b',
                   re.S)


def files_naming(root, names):
    """{name: [files]} over src/**/*.c and include/**/*.h by token (comments and literals skipped)."""
    want = set(names)
    out = collections.defaultdict(list)
    pattern = re.compile(r'\b(' + '|'.join(sorted(map(re.escape, want))) + r')\b') if want else None
    for top, glob in (('src', '*.c'), ('include', '*.h')):
        for p in sorted((Path(root) / top).rglob(glob)):
            if p.is_symlink() or p.stat().st_size > 4 * 1024 * 1024:
                continue
            text = p.read_text(errors='replace')
            hits = set(pattern.findall(text)) if pattern else set()
            for name in hits:
                out[name].append(p.relative_to(root).as_posix())
    return out


def load_family(root, family):
    """(assign {'file:name': type}, shareds {type: layout}) from a single- or multi-type family file."""
    shareds, assign = {}, {}
    groups = family['groups'] if 'groups' in family else [family]
    for g in groups:
        if g['type'] not in shareds:
            shareds[g['type']] = shared_type(root, g['type'], g['header'])
        for spec in g['views']:
            assign[spec] = g['type']
    return assign, shareds


def view_files(root, spec, naming):
    """Files where view `spec` is the visible definition: its own file, plus (for a header view) every file
    naming it that does not define a same-named view of its own."""
    file, name = spec.rsplit(':', 1)
    if file.endswith('.c'):
        return [file]
    out = [file]
    for g in naming.get(name, []):
        if g == file:
            continue
        if typedef_span((Path(root) / g).read_text(errors='replace'), name) is None:
            out.append(g)
    return out


def plan(root, family, workers):
    import layout_compile_identity as L  # noqa: F401  (physical_for needs it importable)
    assign, shareds = load_family(root, family)
    naming = files_naming(root, {spec.rsplit(':', 1)[1] for spec in assign})
    vfiles = {spec: view_files(root, spec, naming) for spec in assign}
    files = sorted({f for fs in vfiles.values() for f in fs})
    src_files = [f for f in files if f.startswith('src/')]
    tus, _ = F.physical_for(root, src_files)
    module_text = {tu: (Path(root) / tu).read_text(errors='replace') for tu in tus if tu not in src_files}
    covered = {f for f in src_files if f in tus or any(Path(f).name in t for t in module_text.values())}
    jobs = [(str(root), tu, recipe, assign, files, shareds) for tu, recipe in sorted(tus.items())]
    with ProcessPoolExecutor(max_workers=max(1, workers)) as ex:
        results = list(ex.map(scan_tu, jobs, chunksize=2))
    errors = [(r['tu'], r['error']) for r in results if r['error']]
    by_view = collections.defaultdict(list)
    sees = collections.defaultdict(set)
    sizes = {}
    for r in results:
        for u in r['uses']:
            by_view[u['view']].append(u)
        for f, s in r['sees'].items():
            sees[f].update(s)
        sizes.update(r.get('sizes', {}))
    decisions = []
    for spec, t in sorted(assign.items()):
        file, name = spec.rsplit(':', 1)
        used = by_view.get(spec, [])
        size = shareds[t]['size']
        reason = None
        if file not in naming.get(name, []):
            reason = 'view_not_found'
        elif any(f.startswith('include/') and f != file for f in vfiles[spec]):
            reason = 'named_in_other_header'
        elif any(f.startswith('src/') and f not in covered for f in vfiles[spec]):
            reason = 'uncompiled_user'
        elif spec not in sizes:
            reason = 'not_seen_by_compiler'
        elif family.get('hold') and any(f.startswith(tuple(family['hold'])) for f in vfiles[spec]):
            reason = 'held_user'
        bad = [u for u in used if u['kind'] == 'member' and not u['ok']]
        if not reason and bad:
            reason = 'member:%s@%s' % (bad[0]['why'], hex(bad[0].get('offset', -1)))
        if not reason and any(u['kind'] == 'size' for u in used) and sizes.get(spec) != size:
            reason = 'size_%s_vs_%s' % (sizes.get(spec), size)
        anchors = collections.Counter(u['anchor'] for u in used if u['kind'] == 'anchor')
        evidence = 'anchored' if anchors.get(t) and len(anchors) == 1 else (
            'conflict' if anchors and t not in anchors else ('mixed' if len(anchors) > 1 else 'shape'))
        if not reason and family.get('require_anchor') and evidence != 'anchored':
            reason = 'identity_' + evidence
        decisions.append({'view': spec, 'name': name, 'file': file, 'type': t, 'accepted': reason is None,
                          'evidence': evidence, 'anchors': dict(anchors),
                          'reason': reason, 'files': vfiles[spec],
                          'members': sum(1 for u in used if u['kind'] == 'member'),
                          'size_uses': sum(1 for u in used if u['kind'] == 'size'), 'size': sizes.get(spec),
                          'uses': used})
    return shareds, decisions, {f: sorted(s) for f, s in sees.items()}, errors, files


# ---------------------------------------------------------------------------------------------- applying

def typedef_span(text, name):
    """(start, end) of `typedef struct|union [name] { ... } name;  /* comment */\\n` (or an alias typedef)."""
    for m in re.finditer(r'typedef\s+(?:struct|union)\s+(?:%s\s*)?\{' % re.escape(name), text):
        depth, i = 0, m.end() - 1
        while i < len(text):
            c = text[i]
            if c == '/' and text.startswith('/*', i):
                i = text.find('*/', i) + 2
                continue
            if c == '{':
                depth += 1
            elif c == '}':
                depth -= 1
                if depth == 0:
                    break
            i += 1
        tail = re.match(r'\s*%s\s*;[ \t]*(?:/\*.*?\*/)?[ \t]*\n?' % re.escape(name), text[i + 1:], re.S)
        if tail:
            start = text.rfind('\n', 0, m.start()) + 1
            return start, i + 1 + tail.end()
    m = re.search(r'^[ \t]*typedef\s+(?:struct\s+|union\s+)?\w+\s+%s\s*;[^\n]*\n' % re.escape(name), text, re.M)
    if m:
        return m.start(), m.end()
    return None


def rename_tokens(text, name, new):
    def sub(m):
        if m.group(1) == name:
            return new
        return m.group(0)
    return TOKEN.sub(sub, text)


def add_include(text, header):
    line = '#include "%s"\n' % header
    if line in text:
        return text
    last = None
    for m in re.finditer(r'^#include[^\n]*\n', text, re.M):
        last = m
    if last is None:
        return line + text
    return text[:last.end()] + line + text[last.end():]


def apply(root, shareds, decisions, sees, out):
    root = Path(root)
    accepted = [d for d in decisions if d['accepted']]
    member_edits = collections.defaultdict(dict)
    for d in accepted:
        for u in d['uses']:
            if u['kind'] == 'member':
                member_edits[u['file']][(u['start'], u['end'])] = (u['old'], u['new'])
    touched = sorted({f for d in accepted for f in d['files']})
    originals = {f: (root / f).read_text() for f in touched}
    for f in touched:
        text = originals[f]
        for (s, e), (old, new) in sorted(member_edits.get(f, {}).items(), reverse=True):
            if text[s:e] != old:
                raise SystemExit('stale member range %s:%d' % (f, s))
            text = text[:s] + new + text[e:]
        visible = [d for d in accepted if f in d['files']]
        for d in visible:
            if d['file'] == f:
                span = typedef_span(text, d['name'])
                if span:
                    text = text[:span[0]] + text[span[1]:]
                text = re.sub(r'^[ \t]*(?:struct|union)\s+%s\s*;[ \t]*\n' % re.escape(d['name']), '', text,
                              flags=re.M)
        for d in visible:
            text = rename_tokens(text, d['name'], d['type'])
        # A header must see T on its own; a C file when its TU did not already declare T.
        for t in sorted({d['type'] for d in visible}):
            header = shareds[t]['header']
            own = f == 'include/' + header
            if text != originals[f] and not own and (f.startswith('include/') or t not in sees.get(f, [])) \
                    and not _sees_through_include(root, text, header):
                text = add_include(text, header)
        (root / f).write_text(text)
    return originals


def _sees_through_include(root, text, header):
    return ('"%s"' % header) in text


# ---------------------------------------------------------------------------------------------- folding

def redundant_casts_tu(args):
    root, rel, recipe, files, tnames = args
    unit, error = A.clang_unit(root, rel, recipe)
    if unit is None:
        return {'tu': rel, 'error': error, 'edits': []}
    edits = []
    for f, fn in unit.functions(set(files)):
        text = unit.text(f)
        for node, parent in A.walk(fn):
            if node.get('kind') != 'CStyleCastExpr':
                continue
            target = C.qtype(node)
            wanted = {unit.T.record(t) for t in tnames} - {None}
            if unit.T.record(target) is None or unit.T.record(target) not in wanted or \
                    not unit.T.resolve(target).endswith('*') or unit.T.resolve(target).endswith('**'):
                continue
            op = A.kids(node)[0]
            inner = A.strip_parens(op if op.get('kind') != 'ImplicitCastExpr' or op.get('castKind') != 'NoOp'
                                   else A.kids(op)[0])
            inner = A.strip_implicit(inner) if inner.get('kind') == 'ImplicitCastExpr' and \
                inner.get('castKind') == 'LValueToRValue' else inner
            if unit.canon(C.qtype(inner)) != unit.canon(target) or not A.pure(inner) or A.in_macro(node):
                continue
            # ((T *)p)->f  /  (T *)p : drop the cast; keep grouping only where needed.
            rng = A.node_range(node, text)
            irng = A.node_range(inner, text)
            if rng is None or irng is None:
                continue
            outer = node
            p = parent
            if p is not None and p.get('kind') == 'ParenExpr':
                prng = A.node_range(p, text)
                if prng and inner.get('kind') in A.POSTFIX_KINDS:
                    rng = prng
            new = text[irng[0]:irng[1]]
            if inner.get('kind') not in A.POSTFIX_KINDS:
                new = '(' + new + ')'
            edits.append({'file': f, 'start': rng[0], 'end': rng[1], 'old': text[rng[0]:rng[1]], 'new': new,
                          'line': node.get('_l')})
    return {'tu': rel, 'error': error, 'edits': edits}


def fold(root, files, tnames, workers):
    src = [f for f in files if f.startswith('src/')]
    tus, _ = F.physical_for(root, src)
    jobs = [(str(root), tu, recipe, src, tnames) for tu, recipe in sorted(tus.items())]
    edits = collections.defaultdict(dict)
    with ProcessPoolExecutor(max_workers=max(1, workers)) as ex:
        for r in ex.map(redundant_casts_tu, jobs, chunksize=2):
            for e in r['edits']:
                edits[e['file']][(e['start'], e['end'])] = e
    done = 0
    for f, es in edits.items():
        text = (Path(root) / f).read_text()
        last = None
        for (s, e), ed in sorted(es.items(), reverse=True):
            if last is not None and e > last:
                continue  # nested in an edit already applied
            if text[s:e] != ed['old']:
                continue
            text = text[:s] + ed['new'] + text[e:]
            last = s
            done += 1
        (Path(root) / f).write_text(text)
    return done


# ---------------------------------------------------------------------------------------------- field retype

def retype_field(root, spec):
    """Retype one pointer member of a shared struct in its header: {"header", "struct", "field", "type"}.
    Returns the header path edited, or raises when the member is not a single plain pointer declaration."""
    path = Path(root) / 'include' / spec['header']
    text = path.read_text()
    m = re.search(r'typedef\s+struct\s+(?:%s\s*)?\{' % re.escape(spec['struct']), text)
    if not m:
        raise SystemExit('struct %s not found in %s' % (spec['struct'], spec['header']))
    close = m.end()
    depth = 1
    while depth and close < len(text):
        depth += {'{': 1, '}': -1}.get(text[close], 0)
        close += 1
    body = text[m.end():close]
    member = re.compile(r'^(?P<lead>[ \t]*(?:/\*[^\n]*?\*/[ \t]*)?)(?P<type>(?:struct\s+)?[A-Za-z_]\w*\s*\*+)\s*'
                        r'(?P<name>%s)\s*;' % re.escape(spec['field']), re.M)
    hits = list(member.finditer(body))
    if len(hits) != 1:
        raise SystemExit('member %s.%s: %d plain pointer declarations' % (spec['struct'], spec['field'], len(hits)))
    h = hits[0]
    new_type = spec['type'].strip()
    new_type = new_type if new_type.endswith('*') else new_type + ' *'
    old_type = h.group('type')
    body = body[:h.start('type')] + new_type + body[h.end('type'):]
    path.write_text(text[:m.end()] + body + text[close:])
    spec['old_type'] = old_type
    return 'include/' + spec['header']


def dependents(root, header):
    """src/ files whose production recipe closure contains `header` (tools/build/affected.Graph)."""
    sys.path.insert(0, str(Path(root) / 'tools' / 'build'))
    import affected
    g = affected.Graph(root)
    out = set()
    for rid in g.by_dep().get(g.real(header), ()):
        src = g.own_source(g.recipes[rid])
        if src and src.startswith('src/'):
            out.add(src)
    return sorted(out)


# ---------------------------------------------------------------------------------------------- warning guard

WARNINGS = ['-Wincompatible-pointer-types', '-Wint-conversion', '-Wincompatible-pointer-types-discards-qualifiers',
            '-Wpointer-sign', '-Wincompatible-function-pointer-types']


def warning_count_tu(args):
    """Pointer-conversion warnings Clang reports for one physical TU (types the swap could disturb)."""
    root, rel, recipe = args
    import subprocess
    cmd = [C.CLANG, '--target=mipsel-unknown-none', '-fsyntax-only', '-ferror-limit=0', '-Wno-everything',
           *WARNINGS, '-I', 'include']

    def run(source):
        res = subprocess.run(cmd + [str(source)], cwd=root, capture_output=True, text=True, errors='replace')
        lines = [l for l in res.stderr.splitlines() if ' warning: ' in l or ' error: ' in l]
        return {'warnings': sum(' warning: ' in l for l in lines), 'errors': sum(' error: ' in l for l in lines)}
    if recipe and 'slus_unit' in recipe:
        import tempfile
        import layout_compile_identity as L
        with tempfile.TemporaryDirectory(prefix='layout-swap-', dir=Path(root) / 'build_ovl') as td:
            with L.compilation_input(root, rel, recipe, Path(td)) as source:
                return rel, run(source)
    return rel, run(rel)


def warning_counts(root, files, workers):
    tus, _ = F.physical_for(root, [f for f in files if f.startswith('src/')])
    with ProcessPoolExecutor(max_workers=max(1, workers)) as ex:
        return dict(ex.map(warning_count_tu, [(str(root), tu, r) for tu, r in sorted(tus.items())]))


def disjoint_plans(plans):
    """view_swap.retype plans whose edits do not overlap an earlier plan in the same file."""
    taken, out = collections.defaultdict(list), []
    for p in plans:
        spans = sorted({(a, b) for a, b, _ in p['edits']})
        if any(b > c for (a, b), (c, d) in zip(spans, spans[1:])):
            continue  # the plan's own edits nest (a value cast inside a removed cast): leave it
        if any(a < d and c < b for a, b in spans for c, d in taken[p['file']]):
            continue
        taken[p['file']].extend(spans)
        out.append(p)
    return out


# ---------------------------------------------------------------------------------------------- proof

def refresh_layout_inline(root, log):
    """Merged (LL7) TUs: re-map ledger/layout_inline.jsonl member extents to the edited text (placement copies
    are projected from them), exactly as sig_txn does before its proof."""
    import subprocess
    res = subprocess.run(['nice', '-n', '10', sys.executable, 'tools/typing/refresh_layout_inline.py', '--root', '.',
                          '--base', 'HEAD'], cwd=root, capture_output=True, text=True)
    if res.returncode:
        raise RuntimeError('refresh_layout_inline failed: ' + (res.stderr or res.stdout)[-800:])
    log('layout_inline: ' + (res.stdout.strip().splitlines() or [''])[-1][:160])


def prove_batch(root, out, workers, log, rounds=4):
    """affected.py prove over every file this batch edited; files whose own recipes (or placement copies) are
    not PASS go back to their original text and the rest is proved again.  Returns the final report."""
    import subprocess
    orig_dir = out / 'originals'
    originals = {p.relative_to(orig_dir).as_posix(): p.read_text() for p in orig_dir.rglob('*') if p.is_file()}
    reverted = []
    report = {}
    for r in range(rounds):
        edited = sorted(f for f, t in originals.items() if (root / f).read_text() != t)
        if not edited:
            log('nothing left to prove')
            return {'verdict': 'EMPTY', 'reverted': reverted}
        refresh_layout_inline(root, log)
        path = out / ('prove-%d.json' % r)
        cmd = ['nice', '-n', '10', sys.executable, 'tools/build/affected.py', 'prove', '--root', '.',
               '--workers', str(workers), '--json', str(path), *edited]
        res = subprocess.run(cmd, cwd=root, capture_output=True, text=True)
        (out / 'prove.log').open('a').write(res.stdout[-6000:] + res.stderr[-3000:])
        report = json.loads(path.read_text()) if path.is_file() else {'verdict': 'ERROR', 'recipes': {}}
        log('proof round %d: %s %s' % (r, report.get('verdict'), report.get('counts')))
        if report.get('verdict') == 'PASS':
            report['reverted'] = reverted
            return report
        bad = {v.get('owner') or v.get('source') for v in report.get('recipes', {}).values()
               if v.get('verdict') != 'PASS'}
        culprits = sorted(f for f in bad if f in edited)
        if not culprits:
            log('failures outside edited sources (header effect): %s' % sorted(bad)[:5])
            break
        # A reverted C file needs the views its edited headers deleted: revert those headers with it.
        for f in list(culprits):
            for inc in re.findall(r'^[ \t]*#[ \t]*include[ \t]*"([^"]+)"', originals[f], re.M):
                h = 'include/' + inc
                if h in edited and h not in culprits and any(
                        d.strip() for d in [originals[h]] if typedef_span(originals[h], 'S_') is None):
                    if any(re.search(r'\b%s\b' % re.escape(n), originals[f])
                           for n in re.findall(r'\}\s*(S_\w+)\s*;', originals[h])):
                        culprits.append(h)
        for f in culprits:
            (root / f).write_text(originals[f])
        reverted.extend(culprits)
        log('reverted %d files: %s' % (len(culprits), culprits[:8]))
    report['reverted'] = reverted
    return report


# ---------------------------------------------------------------------------------------------- debt guard

def debt(rel, text):
    import debt_check as D
    return {k: dict(v['counts']) for k, v in D.analyze(rel, text)['scopes'].items()}


def guard(root, originals, out, log):
    """Restore any edited src file where some function's debt rises; returns per-file deltas."""
    import debt_check as D  # noqa: F401
    deltas = {}
    for f, before in originals.items():
        after = (Path(root) / f).read_text()
        if after == before or not f.endswith('.c'):
            continue
        b, a = debt(f, before), debt(f, after)
        rises = [k for k, c in a.items() if any(n > b.get(k, {}).get(cls, 0) for cls, n in c.items())]
        if rises:
            log('debt rise in %s %s: restored' % (f, rises[:3]))
            (Path(root) / f).write_text(before)
            continue
        tot = lambda d, cls: sum(v.get(cls, 0) for v in d.values())
        deltas[f] = {cls: tot(a, cls) - tot(b, cls) for cls in ('generated_layouts', 'pointer_casts')}
    return deltas


# ---------------------------------------------------------------------------------------------- main

def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('mode', choices=('plan', 'apply', 'prove', 'revert'))
    ap.add_argument('--root', type=Path, default=HERE.parents[1])
    ap.add_argument('--family', type=Path)
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--workers', type=int, default=6)
    ap.add_argument('--no-fold', action='store_true')
    ap.add_argument('--raw-fold', action='store_true', help='also fold raw *(T *)p sites (cast_fold)')
    ap.add_argument('--files', nargs='*', default=[])
    ap.add_argument('--keep-on-warning', action='store_true', help='keep edits even if pointer warnings rise')
    args = ap.parse_args(argv)
    root = args.root.resolve()
    out = args.out
    out.mkdir(parents=True, exist_ok=True)
    sys.path.insert(0, str(root / 'tools'))

    def log(msg):
        print(msg, flush=True)
        with open(out / 'swap.log', 'a') as fh:
            fh.write(msg + '\n')

    if args.mode == 'revert':
        for f in args.files:
            src = out / 'originals' / f
            if src.exists():
                (root / f).write_text(src.read_text())
                log('reverted %s' % f)
        return 0
    if args.mode == 'prove':
        report = prove_batch(root, out, args.workers, log)
        (out / 'prove_summary.json').write_text(json.dumps({k: report.get(k) for k in (
            'verdict', 'counts', 'reverted')}, indent=2) + '\n')
        return 0 if report.get('verdict') == 'PASS' else 1
    family = json.loads(args.family.read_text())
    fields = family.get('retype_fields', [])
    has_views = bool(family.get('groups') or family.get('views'))
    originals, before_warn = {}, {}
    if args.mode == 'apply':
        # Snapshot (and measure warnings of) every file the batch may touch, before any edit.
        names = {spec.rsplit(':', 1)[1] for g in (family.get('groups') or [family]) for spec in g.get('views', [])}
        touched = {f for fs in files_naming(root, names).values() for f in fs} if names else set()
        for spec in fields:
            touched.add('include/' + spec['header'])
            touched.update(dependents(root, 'include/' + spec['header']))
        hold = tuple(family.get('hold', ()))
        if hold:
            # Held areas (other lanes' files) are never edited; their proofs still run through the graph.
            touched = {f for f in touched if not f.startswith(hold) or f in
                       {'include/' + spec['header'] for spec in fields}}
        touched = sorted(touched)
        before_warn = warning_counts(root, touched, args.workers)
        originals = {f: (root / f).read_text() for f in touched}
        (out / 'originals').mkdir(parents=True, exist_ok=True)
        for f, text in originals.items():
            dest = out / 'originals' / f
            dest.parent.mkdir(parents=True, exist_ok=True)
            dest.write_text(text)

    def restore(why):
        for f, text in originals.items():
            if (root / f).read_text() != text:
                (root / f).write_text(text)
        log('restored every file (%s)' % why)

    summary = {'retype_fields': fields}
    try:
        types = []
        if args.mode == 'apply':
            for spec in fields:
                retype_field(root, spec)
                log('retyped %s.%s: %s -> %s' % (spec['struct'], spec['field'], spec['old_type'], spec['type']))
                types.append(spec['type'].rstrip(' *'))
        # Views are planned on the retyped text: a retyped field is identity evidence (an anchor).
        if has_views:
            shareds, decisions, sees, errors, files = plan(root, family, args.workers)
        else:
            shareds, decisions, sees, errors, files = {}, [], {}, [], []
        with open(out / 'decisions.jsonl', 'w') as fh:
            for d in decisions:
                fh.write(json.dumps(d, sort_keys=True) + '\n')
        reasons = collections.Counter((d['reason'] or 'accepted').split('@')[0] for d in decisions)
        summary.update({'types': {t: [i['header'], i['size']] for t, i in shareds.items()},
                        'views': len(decisions), 'accepted': sum(d['accepted'] for d in decisions),
                        'evidence': dict(collections.Counter(d['evidence'] for d in decisions if d['accepted'])),
                        'reasons': dict(reasons.most_common()), 'parse_errors': errors[:20]})
        log(json.dumps({k: summary[k] for k in ('views', 'accepted', 'evidence', 'reasons')}))
        if args.mode != 'apply':
            (out / 'summary.json').write_text(json.dumps(summary, indent=2, default=str) + '\n')
            return 0
        if summary['accepted']:
            missing = [f for d in decisions if d['accepted'] for f in d['files'] if f not in originals]
            if missing:
                raise RuntimeError('unsnapshotted files: %s' % missing[:5])
            apply(root, shareds, decisions, sees, out)
        types = sorted(set(types) | {d['type'] for d in decisions if d['accepted']})
        src = [f for f in originals if f.startswith('src/')]
        if not args.no_fold and types:
            n = fold(root, src, types, args.workers)
            log('folded %d redundant casts' % n)
            if args.raw_fold:
                # Raw `*(T *)p` folds can change gcc 2.x alias decisions (MEM_IN_STRUCT_P); cast_wave proves
                # them site by site, so the batch leaves them out unless asked.
                edits, refused, ferrors = F.plan(root, src, args.workers)
                edits = {f: [e for e in es if e['record'] in set(types)] for f, es in edits.items()}
                edits = {f: es for f, es in edits.items() if es}
                F.apply_edits(root, edits)
                log('folded %d raw offset sites' % sum(map(len, edits.values())))
            import view_swap as V
            plans, pool, rerrors = V.retype(root, src, args.workers)
            # One record type per variable: view_swap's merge of a second view onto the chosen type renames
            # members at equal offsets, which is wrong when the variable is reused for another object.
            # A plan that must cast an assigned value is a variable reused for another object: leave it.
            plans = disjoint_plans([p for p in plans if p['type'] in types and not p.get('merged_views')
                                    and not p.get('added_casts')])
            V.apply_plans(root, plans)
            log('retyped %d locals (%d casts)' % (len(plans), sum(p['casts'] for p in plans)))
            if plans:
                n = fold(root, sorted({p['file'] for p in plans}), types, args.workers)
                log('folded %d casts made redundant by the retyped locals' % n)
        after_warn = warning_counts(root, list(originals), args.workers)
        rises = {tu: (before_warn.get(tu), w) for tu, w in after_warn.items()
                 if before_warn.get(tu) is None or w['warnings'] > before_warn[tu]['warnings']
                 or w['errors'] > before_warn[tu]['errors']}
        summary['warning_rises'] = rises
        if rises:
            log('pointer-conversion warnings rose in %d TUs: %s' % (len(rises), sorted(rises)[:8]))
            if not args.keep_on_warning:
                raise RuntimeError('warning rise')
    except BaseException as exc:
        if args.mode == 'apply':
            restore(exc)
        (out / 'summary.json').write_text(json.dumps(summary, indent=2, default=str) + '\n')
        if isinstance(exc, (RuntimeError, KeyboardInterrupt)):
            return 1
        raise
    if args.mode == 'apply':
        deltas = guard(root, originals, out, log)
        summary['files'] = len(deltas)
        summary['generated_layouts_delta'] = sum(d['generated_layouts'] for d in deltas.values())
        summary['pointer_casts_delta'] = sum(d['pointer_casts'] for d in deltas.values())
        patch = []
        for f in sorted(originals):
            now = (root / f).read_text()
            if now != originals[f]:
                patch.extend(difflib.unified_diff(originals[f].splitlines(True), now.splitlines(True),
                                                  'a/' + f, 'b/' + f))
        (out / 'swap.patch').write_text(''.join(patch))
        log('edited %d files: generated_layouts %+d, pointer_casts %+d' % (
            sum(1 for f in originals if (root / f).read_text() != originals[f]),
            summary['generated_layouts_delta'], summary['pointer_casts_delta']))
    (out / 'summary.json').write_text(json.dumps(summary, indent=2, default=str) + '\n')
    return 0


if __name__ == '__main__':
    sys.exit(main())
