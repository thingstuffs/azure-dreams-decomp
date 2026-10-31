#!/usr/bin/env python3
"""Typed parameter alias, redundant-cast removal and view field synthesis for the pointer-cast wave.

    param_alias.py plan  --folder src/town/shop --out DIR [--min-casts 2] [--skip-list FILE] [--workers 4]
    param_alias.py apply --plan DIR/plan.jsonl [--only KEYS]

Three plan kinds, all edits inside one C file (headers are never touched):

**alias** (the lever).  A `void *` / byte-pointer parameter P that the body reads through record casts
`((V *)P)->f` keeps its prototype (callers, header declarations and dispatch tables are unchanged) and
gets the standard C callback binding at the top of the body:

    void update_x(void *object_arg) {
        S_800B34FC_0 *object = object_arg;
        ... object->unk_18 ...                 (was ((S_800B34FC_0 *)object)->unk_18)

The typed local takes the parameter's name and the parameter is renamed `<name>_arg`.  Every use of P is
classified with view_swap.classify_use:
  - a cast to V (the most-used view; merge_views picks one that every other view's member accesses fit)
    loses the cast;
  - a use whose meaning is the same through a V * (explicit casts to other types, void * slots, truth
    tests, == NULL) refers to the typed local unchanged;
  - any other use (void * arithmetic, subscript, an implicit conversion to another record or pointer,
    comparison with a typed pointer) is respelled `<name>_arg` and keeps its exact meaning.
Refused: P assigned, incremented or address-taken; P spelled in a macro (or the file #defines the name);
`<name>_arg` already spelled in the file; fewer than --min-casts view casts.  The alias never changes a
prototype, so it does not collide with prototype lanes.

**redundant**.  A cast to the type the operand already has (`(T *)p` with p a T *; `((T *)p)->m`), and a
cast of a `void *` value stored straight into a variable of the cast type (`T *x = (T *)vp;`) are dropped.

**synth** (runs after alias and cast_fold).  A raw access `*(T *)((u8 *)obj + K)` whose base is a pointer
to a generated view V defined in the same C file, where K falls inside a `u8 pad_XX[N]` / `u8 unk_XX[N]`
array of V, gets a member `T unk_K;` split out of that array (offset-neutral: K aligned to T, T's alignment
no larger than V's, every access at K in the file the same width and, for reads, the same type).  The
following cast_fold pass then folds the site.  Offsets, size and alignment of V are checked with a clang
record-layout comparison before the edit is kept.

The edits are *expected* to be byte-identical; alias_wave.py proves every touched physical TU with
tu_identity and rolls back per function.  Outputs: plan.jsonl (one record per plan with its text edits),
summary.json (counts and refusals).
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


def _setup_path(root):
    for p in (HERE, root / 'tools' / 'typing', root / 'tools', root / 'tools' / 'lint'):
        if str(p) not in sys.path:
            sys.path.append(str(p))


C_KEYWORDS = {'auto', 'break', 'case', 'char', 'const', 'continue', 'default', 'do', 'double', 'else', 'enum',
              'extern', 'float', 'for', 'goto', 'if', 'int', 'long', 'register', 'return', 'short', 'signed',
              'sizeof', 'static', 'struct', 'switch', 'typedef', 'union', 'unsigned', 'void', 'volatile', 'while'}
GENERATED = re.compile(r'^(?:S_(?:func_)?[0-9A-Fa-f]{8}\w*|Rec_\w+|Row_\w+|R\d+_\w+)$')
PAD_DECL = re.compile(r'^(\s*)(u8|unsigned char|char|s8)\s+((?:pad|unk)_?([0-9A-Fa-f]+))\s*\[\s*(0x[0-9A-Fa-f]+|\d+)\s*\]\s*;')
INT_TYPES = {'s8': 1, 'u8': 1, 's16': 2, 'u16': 2, 's32': 4, 'u32': 4, 'int': 4, 'char': 1, 'short': 2,
             'unsigned char': 1, 'signed char': 1, 'unsigned short': 2, 'unsigned int': 4, 'long': 4,
             'unsigned long': 4}


# ------------------------------------------------------------------------------------------- helpers

def up(A, parents, node):
    p = parents.get(id(node))
    while p is not None and p.get('kind') == 'ParenExpr':
        node, p = p, parents.get(id(p))
    return node, p


def drop_cast_edit(A, parents, cast, text, replacement):
    """(start, end, replacement) removing a cast (and the parentheses that only grouped it)."""
    rng = A.node_range(cast, text)
    if rng is None:
        return None
    outer, holder = cast, parents.get(id(cast))
    while holder is not None and holder.get('kind') == 'ParenExpr':
        outer, holder = holder, parents.get(id(holder))
    orng = A.node_range(outer, text) or rng
    if outer is not cast and not (orng[0] and (text[orng[0] - 1].isalnum() or text[orng[0] - 1] == '_')) \
            and (holder or {}).get('kind') != 'UnaryExprOrTypeTraitExpr':
        rng = orng
    return (rng[0], rng[1], replacement)


def ident_used(text, name):
    return re.search(r'(?<![\w])' + re.escape(name) + r'(?![\w])', text) is not None


def defines(text, name):
    for m in re.finditer(r'(?m)^\s*#\s*define\s+(\w+)(.*)$', text):
        if m.group(1) == name or ident_used(m.group(2), name):
            return True
    return False


# ------------------------------------------------------------------------------------------- alias

def plan_alias(V, A, C, unit, file, fn, text, parents, nodes, min_casts, decl_at='first'):
    plans, pool = [], collections.Counter()
    params = [x for x in fn.get('inner', []) if x.get('kind') == 'ParmVarDecl']
    body = next((x for x in fn.get('inner', []) if x.get('kind') == 'CompoundStmt'), None)
    if body is None:
        return plans, pool
    for prm in params:
        t = C.qtype(prm)
        r = unit.canon(t)
        if not (r == 'void*' or (r.endswith('*') and not r.endswith('**') and r[:-1] in A.BYTE_POINTEES)):
            continue
        name = prm.get('name')
        if not name:
            continue
        refs = [n for n in nodes if n.get('kind') == 'DeclRefExpr'
                and (n.get('referencedDecl') or {}).get('id') == prm.get('id')]
        views, raw, keep, why = collections.defaultdict(list), [], [], None
        for ref in refs:
            if A.in_macro(ref):
                why = 'macro_use'
                break
            kind, detail = V.classify_use(unit, ref, parents, t)
            if kind == 'assign':
                why = 'assigned'
            elif kind == 'refuse':
                if detail in ('address_taken', 'modified_arithmetic'):
                    why = detail
                else:
                    raw.append(ref)
            elif kind == 'record_cast':
                cast, (key, tname) = detail
                if A.in_macro(cast):
                    raw.append(ref)
                    continue
                views[(key, tname)].append((cast, ref))
            else:
                keep.append(ref)
        n_views = sum(map(len, views.values()))
        if not n_views:
            continue
        if why:
            pool['refused:' + why] += n_views
            continue
        if defines(text, name):
            pool['refused:name_in_define'] += n_views
            continue
        # Names: the typed local takes the parameter's name and the parameter becomes `<name>_arg`; a
        # parameter already spelled `<x>_arg` keeps its name and the local is `<x>`.
        lname, new_param = name, name + '_arg'
        if name.endswith('_arg') and len(name) > 4 and not ident_used(text, name[:-4]) \
                and name[:-4] not in C_KEYWORDS:
            lname, new_param = name[:-4], name
        elif ident_used(text, new_param):
            pool['refused:arg_name_taken'] += n_views
            continue
        # The chosen view: one every other view's member accesses fit (merge_views), else the most used.
        records = {k: tn for (k, tn) in views}
        casts = [(c, ref) for v in views.values() for c, ref in v]
        mapped = {}
        if len(records) > 1:
            key, mapped = V.merge_views(unit, records, casts, parents)
            if key is None:
                key = max(views, key=lambda kv: (len(views[kv]), unit.layouts[kv[0]].get('size') or 0))[0]
                mapped = {}
        else:
            key = next(iter(records))
        tname = records[key]
        edits, removed = [], 0
        for (k, tn), lst in views.items():
            for cast, ref in lst:
                if k == key:
                    e = drop_cast_edit(A, parents, cast, text, lname)
                    if e is None:
                        why = 'cast_range'
                        break
                    edits.append(e)
                    removed += 1
                elif id(cast) in mapped:
                    leaf, path = mapped[id(cast)]
                    lr = A.node_range(leaf, text)
                    if lr is None:
                        why = 'cast_range'
                        break
                    edits.append((lr[0], lr[1], lname + '->' + path))
                    removed += 1
                # other views keep their explicit cast, now applied to the typed local
        if why:
            pool['refused:' + why] += n_views
            continue
        if removed < min_casts:
            pool['below_min_casts'] += n_views
            continue
        for ref in raw + keep:
            rr = A.node_range(ref, text)
            if rr is None or text[rr[0]:rr[1]] != name:
                why = 'raw_use_range'
                break
            spelled_use = new_param if any(ref is r for r in raw) else lname
            if spelled_use != name:
                edits.append((rr[0], rr[1], spelled_use))
        if why:
            pool['refused:' + why] += n_views
            continue
        # Rename the parameter in the definition.
        loc = (prm.get('loc') or {})
        off = loc.get('offset')
        if off is None or 'spellingLoc' in loc:
            pool['refused:param_loc'] += n_views
            continue
        if not text.isascii():
            off = len(text.encode()[:off].decode(errors='replace'))
        if text[off:off + len(name)] != name:
            pool['refused:param_spelling'] += n_views
            continue
        if new_param != name:
            edits.append((off, off + len(name), new_param))
        # Bind the typed local as the first declaration of the body.
        brng = A.node_range(body, text)
        if brng is None or text[brng[0]] != '{':
            pool['refused:body_range'] += n_views
            continue
        nl = text.find('\n', brng[0])
        if nl < 0 or text[brng[0] + 1:nl].strip():
            pool['refused:body_layout'] += n_views
            continue
        rest = text[nl + 1:]
        m = re.match(r'([ \t]*)(\S.*)', rest)
        indent = m.group(1) if m and m.group(1) else '    '
        first = (m.group(2) if m else '').strip()
        first_kids = A.kids(body)
        declares_first = bool(first_kids) and first_kids[0].get('kind') == 'DeclStmt'
        spelled = '%s *%s = %s;\n' % (tname, lname, new_param)
        insert = indent + spelled + ('' if declares_first else '\n')
        at = nl + 1
        if decl_at == 'last' and declares_first:
            # After the leading declarations (another pseudo order for the register allocator); refused
            # when an earlier initializer reads the parameter.
            last = None
            for k in first_kids:
                if k.get('kind') != 'DeclStmt':
                    break
                last = k
            lr = A.node_range(last, text)
            if lr is None:
                pool['refused:decl_range'] += n_views
                continue
            at = text.find('\n', lr[1] - 1) + 1
            if any(a < at for a, b, _ in edits if a > brng[0]):
                pool['refused:param_read_in_declarations'] += n_views
                continue
            insert = indent + spelled
        edits.append((at, at, insert))
        plans.append({'kind': 'alias', 'file': file, 'func': fn['name'], 'param': name, 'local': lname, 'view': tname,
                      'record': key, 'casts': removed, 'raw_uses': len(raw), 'other_views': len(records) - 1,
                      'line': prm.get('_l'), 'edits': sorted(edits)})
        pool['alias_casts'] += removed
    return plans, pool


# ------------------------------------------------------------------------------------------- redundant

def plan_redundant(A, C, unit, file, fn, text, parents, nodes):
    plans, pool = [], collections.Counter()
    for node in nodes:
        if node.get('kind') != 'CStyleCastExpr' or A.in_macro(node):
            continue
        target = C.qtype(node)
        if not target.strip().endswith('*'):
            continue
        kids = A.kids(node)
        if not kids:
            continue
        op = kids[0]
        src = C.qtype(op)
        same = unit.T.resolve(target) == unit.T.resolve(src) and not re.search(r'\b(const|volatile)\b', target + src) \
            and unit.canon(target) not in ('fnptr*',) and node.get('castKind') in ('NoOp', 'BitCast')
        why = None
        if same:
            why = 'same_type'
        else:
            # (T *)vp stored straight into a T * variable or initializer.
            holder = parents.get(id(node))
            outer = node
            while holder is not None and holder.get('kind') == 'ParenExpr':
                outer, holder = holder, parents.get(id(holder))
            dest = None
            if holder is not None and holder.get('kind') == 'VarDecl':
                dest = C.qtype(holder)
            elif holder is not None and holder.get('kind') == 'BinaryOperator' and holder.get('opcode') == '=' \
                    and A.kids(holder)[1] is outer:
                above = parents.get(id(holder))
                if above is not None and above.get('kind') in ('CompoundStmt', 'IfStmt', 'ForStmt', 'WhileStmt',
                                                                'DoStmt', 'CaseStmt', 'DefaultStmt', 'LabelStmt'):
                    dest = C.qtype(A.kids(holder)[0])
            if dest and unit.canon(src) == 'void*' and unit.T.resolve(dest) == unit.T.resolve(target) \
                    and not re.search(r'\b(const|volatile)\b', target + dest) and unit.canon(target) != 'fnptr*':
                why = 'void_to_declared_type'
        if not why:
            continue
        orng = A.node_range(op, text)
        if orng is None:
            continue
        e = drop_cast_edit(A, parents, node, text, None)
        if e is None:
            continue
        operand = text[orng[0]:orng[1]]
        crng = A.node_range(node, text)
        inner = A.strip_implicit(op)
        if (e[0], e[1]) != tuple(crng) and inner.get('kind') not in A.POSTFIX_KINDS:
            operand = '(' + operand + ')'      # the dropped parentheses grouped a unary operand
        plans.append({'kind': 'redundant', 'file': file, 'func': fn['name'], 'why': why, 'casts': 1,
                      'line': node.get('_l'), 'edits': [(e[0], e[1], operand)]})
        pool['redundant_' + why] += 1
    return plans, pool


# ------------------------------------------------------------------------------------------- synth

def local_views(A, C, unit, file, text):
    """{record key: (typedef name, member list)} for generated struct typedefs defined in this C file."""
    out = {}
    for d in unit.tree.get('inner', []):
        if d.get('kind') != 'TypedefDecl' or d.get('_f') != file or not GENERATED.match(d.get('name', '')):
            continue
        key = unit.T.record(C.qtype(d))
        if key and key in unit.layouts:
            out[key] = d.get('name')
    return out


def plan_synth(A, C, F, unit, file, text, sites_by_key, views):
    """Member additions for raw accesses at pad offsets of file-local generated views.

    sites_by_key: {record key: [(offset, cast type, is_store)]} from raw sites on typed bases."""
    plans, pool = [], collections.Counter()
    for key, sites in sites_by_key.items():
        if key not in views:
            pool['not_local_view'] += len(sites)
            continue
        tname = views[key]
        lay = unit.layouts[key]
        m = re.search(r'typedef\s+struct\s+%s\s*\{' % re.escape(tname), text) or \
            re.search(r'typedef\s+struct\s*\{', text[:0])
        if not m:
            pool['definition_not_found'] += len(sites)
            continue
        start = m.end()
        end = text.find('}', start)
        block = text[start:end]
        by_off = collections.defaultdict(list)
        for off, ctype, store in sites:
            by_off[off].append((ctype, store))
        align = lay.get('align')
        new_block = block
        added = []
        for off in sorted(by_off):
            accs = by_off[off]
            loads = {unit.canon(c) for c, s in accs if not s}
            widths = {unit.size(c) for c, s in accs}
            if len(widths) != 1:
                pool['mixed_width'] += len(accs)
                continue
            w = widths.pop()
            if len(loads) > 1:
                pool['mixed_load_type'] += len(accs)
                continue
            ctype = next(iter([c for c, s in accs if not s] or [accs[0][0]]))
            spelled = _spell(unit, ctype)
            if spelled is None:
                pool['type_not_spellable'] += len(accs)
                continue
            if w not in (1, 2, 4) or off % w or (align and w > align):
                pool['alignment'] += len(accs)
                continue
            if re.search(r'\bunk_%02X\b' % off, new_block) or re.search(r'\bpad_%02X\b' % (off + w), new_block):
                pool['name_taken'] += len(accs)
                continue
            if '{' in block:
                pool['nested_record'] += len(accs)
                continue
            # Find the pad array line covering [off, off + w).
            done = False
            lines = new_block.split('\n')
            for i, line in enumerate(lines):
                pm = PAD_DECL.match(line)
                if not pm:
                    continue
                poff = _member_offset(unit, key, pm.group(3))
                if poff is None:
                    continue
                n = int(pm.group(5), 0)
                if not (poff <= off and off + w <= poff + n):
                    continue
                ind, base = pm.group(1), pm.group(2)
                parts = []
                if off > poff:
                    parts.append('%s%s %s[0x%X];' % (ind, base, pm.group(3), off - poff))
                parts.append('%s%s unk_%02X;' % (ind, spelled, off))
                if poff + n > off + w:
                    rest = poff + n - off - w
                    parts.append('%s%s pad_%02X[0x%X];' % (ind, base, off + w, rest))
                tail = line[pm.end():]
                lines[i:i + 1] = parts[:-1] + [parts[-1] + tail]
                done = True
                break
            if not done:
                pool['no_pad_array'] += len(accs)
                continue
            new_block = '\n'.join(lines)
            added.append((off, spelled, len(accs)))
        if added:
            plans.append({'kind': 'synth', 'file': file, 'func': '', 'view': tname, 'record': key,
                          'members': added, 'casts': 2 * sum(n for _, _, n in added),
                          'edits': [(start, end, new_block)]})
            pool['synth_sites'] += sum(n for _, _, n in added)
    return plans, pool


def _member_offset(unit, key, name):
    import cast_ast as A
    return A.member_offset(unit, key, name)


def _spell(unit, ctype):
    """A member spelling for a cast pointee type, or None when it cannot be spelled safely in the view."""
    t = re.sub(r'\s+', ' ', ctype.strip())
    if t in INT_TYPES:
        return t
    if t in ('void *',) or re.fullmatch(r'(?:s8|u8|s16|u16|s32|u32|void) \*', t):
        return t
    return None


# ------------------------------------------------------------------------------------------- driver

def raw_sites(A, C, F, unit, file, fn):
    """Raw accesses on record-typed bases that cast_fold refuses for a missing member."""
    out = collections.defaultdict(list)
    sites, refused = F.scan_function(unit, file, fn)
    folded = {(s['line'], s['offset']) for s in sites}
    parents = {}
    for node, parent in A.walk(fn):
        parents[id(node)] = parent
    for node, parent in A.walk(fn):
        if node.get('kind') != 'UnaryOperator' or node.get('opcode') != '*' or A.in_macro(node):
            continue
        operand = A.kids(node)[0]
        chain = A.strip_parens(A.strip_implicit(operand) if operand.get('kind') == 'ImplicitCastExpr'
                               and operand.get('castKind') != 'LValueToRValue' else operand)
        if not chain or chain.get('kind') != 'CStyleCastExpr':
            continue
        r = F.base_offset(unit, chain)
        if r is None or not r[2] or r[3]:
            continue
        leaf, off, _, _ = r
        key = unit.record_of_pointer(C.qtype(leaf))
        if not key or off < 0 or off >= (unit.layouts[key].get('size') or 0):
            continue
        if (node.get('_l'), off) in folded:
            continue
        holder = parents.get(id(node))
        while holder is not None and holder.get('kind') == 'ParenExpr':
            holder = parents.get(id(holder))
        store = holder is not None and holder.get('kind') == 'BinaryOperator' and holder.get('opcode') == '='
        out[key].append((off, C.qtype(node), store))
    return out


def scan_tu(args):
    root, rel, recipe, files, opts = args
    root = Path(root)
    _setup_path(root)
    import cast_ast as A
    import cast_fold as F
    import field_census as C
    import view_swap as V
    try:
        unit, error = A.clang_unit(root, rel, recipe)
    except Exception as exc:
        return {'tu': rel, 'error': str(exc)[-300:], 'plans': [], 'pool': {}}
    if unit is None:
        return {'tu': rel, 'error': error, 'plans': [], 'pool': {}}
    plans, pool = [], collections.Counter()
    synth_sites = collections.defaultdict(lambda: collections.defaultdict(list))
    for file, fn in unit.functions(set(files)):
        text = unit.text(file)
        parents, nodes = {}, []
        for n, p in A.walk(fn):
            parents[id(n)] = p
            nodes.append(n)
        if 'alias' in opts['kinds']:
            p, c = plan_alias(V, A, C, unit, file, fn, text, parents, nodes, opts['min_casts'],
                              opts.get('decl_at', 'first'))
            plans.extend(p)
            pool.update(c)
        if 'redundant' in opts['kinds']:
            p, c = plan_redundant(A, C, unit, file, fn, text, parents, nodes)
            plans.extend(p)
            pool.update(c)
        if 'synth' in opts['kinds']:
            for key, lst in raw_sites(A, C, F, unit, file, fn).items():
                synth_sites[file][key].extend(lst)
    if 'synth' in opts['kinds']:
        for file, by_key in synth_sites.items():
            text = unit.text(file)
            p, c = plan_synth(A, C, F, unit, file, text, by_key, local_views(A, C, unit, file, text))
            plans.extend(p)
            pool.update(c)
    return {'tu': rel, 'error': error, 'plans': plans, 'pool': dict(pool)}


def plan(root, files, kinds=('alias', 'redundant'), min_casts=2, workers=4, decl_at='first'):
    _setup_path(root)
    import cast_fold as F
    tus, _ = F.physical_for(root, files)
    opts = {'kinds': list(kinds), 'min_casts': min_casts, 'decl_at': decl_at}
    jobs = [(str(root), tu, recipe, sorted(files), opts) for tu, recipe in sorted(tus.items())]
    plans, pool, errors, seen = [], collections.Counter(), [], set()
    with (ProcessPoolExecutor(max_workers=workers) if workers > 1 and len(jobs) > 1 else F._Inline()) as ex:
        for res in ex.map(scan_tu, jobs, chunksize=2):
            if res['error']:
                errors.append((res['tu'], res['error']))
            for p in res['plans']:
                k = (p['kind'], p['file'], p['func'], p.get('param'), p.get('view'), p.get('line'),
                     tuple(map(tuple, p['edits'])))
                if k not in seen:
                    seen.add(k)
                    plans.append(p)
            pool.update(res['pool'])
    return plans, pool, errors


def apply_plans(root, plans):
    """Apply text edits; plans overlapping an earlier plan in the same file are skipped (returned)."""
    by_file = collections.defaultdict(list)
    for p in plans:
        by_file[p['file']].append(p)
    applied, skipped = [], []
    for file, ps in by_file.items():
        path = Path(root) / file
        text = path.read_text()
        taken, edits = [], []
        for p in ps:
            spans = [(a, b) for a, b, _ in p['edits']]
            clash = any((a < b2 and a2 < b) or (a == b and a2 < a < b2) or (a2 == b2 and a < a2 < b)
                        for a, b in spans for a2, b2 in taken)
            if clash:
                skipped.append(p)
                continue
            taken.extend(spans)
            edits.extend(p['edits'])
            applied.append(p)
        for a, b, rep in sorted(edits, key=lambda e: (e[0], e[1]), reverse=True):
            text = text[:a] + rep + text[b:]
        path.write_text(text)
    return applied, skipped


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest='cmd', required=True)
    p = sub.add_parser('plan')
    p.add_argument('--root', type=Path, default=HERE.parents[1])
    p.add_argument('--folder', default='src')
    p.add_argument('--file', nargs='*', default=[])
    p.add_argument('--skip-list', type=Path)
    p.add_argument('--kinds', default='alias,redundant')
    p.add_argument('--min-casts', type=int, default=2)
    p.add_argument('--out', type=Path, required=True)
    p.add_argument('--workers', type=int, default=4)
    a = sub.add_parser('apply')
    a.add_argument('--root', type=Path, default=HERE.parents[1])
    a.add_argument('--plan', type=Path, required=True)
    args = ap.parse_args(argv)
    root = args.root.resolve()
    _setup_path(root)
    if args.cmd == 'plan':
        import cast_fold as F
        files = F.folder_files(root, args.folder, args.file)
        if args.skip_list:
            skip = {l.strip() for l in args.skip_list.read_text().splitlines() if l.strip()}
            files = [f for f in files if f not in skip]
        plans, pool, errors = plan(root, files, args.kinds.split(','), args.min_casts, args.workers)
        args.out.mkdir(parents=True, exist_ok=True)
        with open(args.out / 'plan.jsonl', 'w') as fh:
            for p in plans:
                fh.write(json.dumps(p, sort_keys=True) + '\n')
        summary = {'files': len(files), 'plans': dict(collections.Counter(p['kind'] for p in plans)),
                   'casts': dict(collections.Counter({p['kind']: 0 for p in plans}) +
                                 collections.Counter(**{k: sum(p['casts'] for p in plans if p['kind'] == k)
                                                        for k in {p['kind'] for p in plans}})),
                   'pool': dict(pool.most_common()), 'errors': errors[:20]}
        (args.out / 'summary.json').write_text(json.dumps(summary, indent=1) + '\n')
        print(json.dumps({k: summary[k] for k in ('files', 'plans', 'casts')}))
    else:
        plans = [json.loads(l) for l in args.plan.read_text().splitlines() if l.strip()]
        applied, skipped = apply_plans(root, plans)
        print(json.dumps({'applied': len(applied), 'skipped': len(skipped)}))
    return 0


if __name__ == '__main__':
    sys.exit(main())
