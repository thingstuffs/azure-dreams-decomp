#!/usr/bin/env python3
"""Field-access folder: raw offset accesses through a typed struct pointer become member accesses.

    cast_fold.py --folder src/town/map [--file F ...] --out DIR [--apply] [--workers N]

A *site* is an lvalue spelled through explicit pointer casts from a struct-typed base:

    *(T *)((u8 *)p + K)      *(T *)((char *)p + K)      *(T *)p      *((T *)p + n)
    ((u8 *)p)[K]             ((T *)p)[n]                *(T *)((u8 *)&obj + K)

where the base `p` (a side-effect-free name, member chain or constant subscript, no casts of its own) has a
declared pointer-to-complete-struct type (or `&obj` of a struct object).  The site is folded to `p->path`
(`obj.path`) when the struct has a non-bit-field member at byte offset K whose type gives exactly the same
access as T:

  - integers: the same canonical type (typedefs expanded; int/long and short/short int merged; char kept
    distinct).  A plain store whose value is unused may also take a same-width member of the other
    signedness (`sh` is `sh`); every read needs the exact type.
  - pointers: the same canonical type; a plain store may also convert between `void *` and another data
    pointer when the stored value is assignable without a cast.  Function pointers need identical spellings.
  - aggregates (struct copies): the same record.
  - volatility must agree; padding members (`pad*`) are never named.
Union members are reached through their named views (`p->field.member`), first exact member wins.

Nothing is folded when the base is untyped (void *, u8 *, an integer), when no exact member exists, or
inside a macro.  Every refusal is counted by reason.  The output is a plan; `--apply` writes the edits.
The edits are *expected* to be byte-identical; cast_wave.py proves each physical TU with tu_identity and
rolls back any TU that changed.

Outputs under --out: plan.jsonl (one record per folded site), refusals.tsv (reason counts per file),
summary.json.
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
import field_census as C  # noqa: E402

PAD = re.compile(r'(?:^|\.)(?:pad|_pad|padding|unused_pad)\w*(?:\[|$|\.)', re.I)
STATEMENT_PARENTS = {'CompoundStmt', 'IfStmt', 'ForStmt', 'WhileStmt', 'DoStmt', 'CaseStmt', 'DefaultStmt',
                     'LabelStmt', 'SwitchStmt'}


def pointer_type(t):
    t = (t or '').strip()
    return t.endswith('*') or '(*)' in t


def base_offset(unit, e):
    """(leaf, offset, explicit cast seen, address-of) for a constant-offset pointer from a typed base."""
    e = A.strip_parens(e)
    if not e:
        return None
    k = e.get('kind')
    if k == 'CStyleCastExpr':
        if not pointer_type(C.qtype(e)) or e.get('castKind') not in ('BitCast', 'NoOp'):
            return None
        r = base_offset(unit, A.kids(e)[0])
        return r and (r[0], r[1], True, r[3])
    if k == 'ImplicitCastExpr' and e.get('castKind') in ('BitCast', 'NoOp'):
        return base_offset(unit, A.kids(e)[0])
    if k == 'BinaryOperator' and e.get('opcode') in ('+', '-'):
        a, b = A.kids(e)
        ia, ib = C.int_value(a), C.int_value(b)
        if ib is not None and ia is None:
            ptr, n = a, ib
        elif ia is not None and ib is None and e['opcode'] == '+':
            ptr, n = b, ia
        else:
            return None
        pointee = unit.T.pointee(C.qtype(ptr))
        if pointee is None:
            return None
        scale = 1 if pointee == 'void' else unit.size(pointee)
        if not scale:
            return None
        r = base_offset(unit, ptr)
        if r is None:
            return None
        return r[0], r[1] + (n if e['opcode'] == '+' else -n) * scale, r[2], r[3]
    if k == 'UnaryOperator' and e.get('opcode') == '&':
        obj = A.strip_parens(A.kids(e)[0])
        rec = unit.T.record(C.qtype(obj))
        if rec and not unit.T.resolve(C.qtype(obj)).endswith('*') and A.pure(obj) and rec in unit.layouts:
            return obj, 0, False, True
        return None
    leaf = A.strip_implicit(e)
    if unit.record_of_pointer(C.qtype(e)) and A.pure(e) and leaf.get('kind') != 'IntegerLiteral':
        return e, 0, False, False
    return None


def base_kind(unit, e):
    """Why a cast chain's base is not foldable (for the refusal census)."""
    e = A.strip_parens(e)
    while e and e.get('kind') in ('CStyleCastExpr', 'ImplicitCastExpr', 'ParenExpr', 'BinaryOperator'):
        if e.get('kind') == 'BinaryOperator':
            if e.get('opcode') not in ('+', '-'):
                break
            a, b = A.kids(e)
            e = a if C.int_value(b) is not None else b
        else:
            e = A.kids(e)[0]
        e = A.strip_parens(e)
    if not e:
        return 'base_unknown'
    t = unit.T.resolve(C.qtype(e))
    if t.endswith('**'):
        return 'base_pointer_pointer'
    if t == 'void*':
        return 'base_void_pointer'
    if t.endswith('*') and t[:-1] in A.BYTE_POINTEES:
        return 'base_byte_pointer'
    if t.endswith('*') and t[:-1].startswith('rec:'):
        return 'base_incomplete_struct' if unit.record_of_pointer(C.qtype(e)) is None else 'base_not_pure'
    if t.endswith('*'):
        return 'base_scalar_pointer'
    if e.get('kind') == 'IntegerLiteral' or C.int_value(e) is not None:
        return 'base_constant_address'
    if t.startswith('rec:') or '[' in t:
        return 'base_array_or_object'
    return 'base_integer'


def same_access(unit, want, have, store_only, rhs=None):
    """(ok, reason): does member type `have` give the same access as cast type `want`?"""
    if unit.volatile(want) != unit.volatile(have):
        return False, 'volatile_differs'
    w, h = unit.canon(want), unit.canon(have)
    if '[' in h or '[' in w:
        return False, 'array_member'
    if w.endswith('*') or h.endswith('*'):
        if not (w.endswith('*') and h.endswith('*')):
            return False, 'pointer_vs_integer'
        if w == 'fnptr*' or h == 'fnptr*':
            spell = lambda t: re.sub(r'\s+', '', unit.T.resolve(t) if t.strip() in unit.typedefs else t)
            return (spell(want) == spell(have), 'function_pointer_differs')
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
    sw, sh = unit.size(want), unit.size(have)
    if store_only and sw == sh and sw in (1, 2, 4) and 'float' not in (w, h) and 'double' not in (w, h):
        return True, ''
    if sw == sh:
        return False, 'signedness_differs'
    return False, 'width_differs'


def member_text(unit, leaf, address_of, path, text):
    inner = A.strip_implicit(leaf)
    # Redundant grouping around a postfix base is dropped: (a->b)->c -> a->b->c.
    rng = A.node_range(inner if inner.get('kind') in A.POSTFIX_KINDS else leaf, text)
    if rng is None:
        return None
    base = text[rng[0]:rng[1]].strip()
    grouped = base.startswith('(') and base.endswith(')') and A.balanced(base[1:-1])
    if inner.get('kind') not in A.POSTFIX_KINDS and not grouped:
        base = '(' + base + ')'
    return base + ('.' if address_of else '->') + path


def scan_function(unit, file, fn, store_width_only=True):
    """Fold candidates and refusals in one function body."""
    text = unit.text(file)
    parents = {}
    sites, refused = [], collections.Counter()
    for node, parent in A.walk(fn):
        parents[id(node)] = parent
    for node, parent in A.walk(fn):
        k = node.get('kind')
        if k == 'UnaryOperator' and node.get('opcode') == '*':
            operand = A.kids(node)[0]
            stripped = A.strip_parens(A.strip_implicit(operand) if operand.get('kind') == 'ImplicitCastExpr'
                                      and operand.get('castKind') != 'LValueToRValue' else operand)
            chain = stripped
            index = 0
        elif k == 'ArraySubscriptExpr':
            idx = C.int_value(A.kids(node)[1])
            base = A.strip_parens(A.kids(node)[0])
            if idx is None:
                continue
            chain = base
            while chain and chain.get('kind') == 'ImplicitCastExpr' and chain.get('castKind') in ('BitCast', 'NoOp', 'ArrayToPointerDecay'):
                chain = A.strip_parens(A.kids(chain)[0])
            if not chain or chain.get('kind') != 'CStyleCastExpr':
                continue
            index = idx
        elif k == 'MemberExpr' and node.get('isArrow'):
            # ((V *)e)->m.n : a view cast over a typed base is a site at offset(m.n) in V.
            chain = A.strip_parens(A.kids(node)[0])
            if not chain or chain.get('kind') != 'CStyleCastExpr':
                continue
            vkey = unit.record_of_pointer(C.qtype(chain))
            extra = A.member_offset(unit, vkey, node.get('name')) if vkey else None
            if extra is None:
                continue
            leaf, p = node, parents.get(id(node))
            while p is not None and p.get('kind') == 'MemberExpr' and not p.get('isArrow') and A.kids(p)[0] is leaf:
                inner = unit.T.record(C.qtype(leaf))
                sub = A.member_offset(unit, inner, p.get('name')) if inner else None
                if sub is None:
                    break
                extra += sub
                leaf, p = p, parents.get(id(p))
            node, index = leaf, extra
        else:
            continue
        # Only spellings with an explicit cast in the address are sites.
        if not chain or chain.get('kind') not in ('CStyleCastExpr', 'BinaryOperator'):
            continue
        if chain.get('kind') == 'BinaryOperator' and not _has_cast(chain):
            continue
        tag = 'view:' if k == 'MemberExpr' else ''
        if A.in_macro(node):
            refused[tag + 'macro'] += 1
            continue
        want = C.qtype(node)
        r = base_offset(unit, chain)
        if r is None or not r[2]:
            if _has_cast(chain):
                refused[tag + base_kind(unit, chain)] += 1
            continue
        leaf, off, _, address_of = r
        if k == 'MemberExpr':
            off += index
        elif k == 'ArraySubscriptExpr':
            esize = unit.size(want)
            if not esize:
                refused['element_size_unknown'] += 1
                continue
            off += index * esize
        key = unit.T.record(C.qtype(leaf)) if address_of else unit.record_of_pointer(C.qtype(leaf))
        if off < 0:
            refused[tag + 'negative_offset'] += 1
            continue
        if off >= (unit.layouts[key].get('size') or 0):
            refused[tag + 'beyond_struct'] += 1
            continue
        # Context: a plain store whose value is unused may match by width.
        outer = node
        while parents.get(id(outer)) is not None and parents[id(outer)].get('kind') == 'ParenExpr':
            outer = parents[id(outer)]
        holder = parents.get(id(outer))
        store_only = False
        rhs = None
        if holder is not None and holder.get('kind') == 'BinaryOperator' and holder.get('opcode') == '=' \
                and A.kids(holder)[0] is outer:
            above = parents.get(id(holder))
            store_only = store_width_only and (above is None or above.get('kind') in STATEMENT_PARENTS)
            rhs = A.kids(holder)[1]
        candidates = [(p, t) for p, t, _ in unit.leaves_at(key, off) if not PAD.search(p)]
        if not candidates:
            refused[tag + 'no_member_at_offset'] += 1
            continue
        chosen, why = None, None
        # Exact type first; width-only store matches only when nothing exact exists.
        for exact in (True, False):
            for p, t in candidates:
                ok, reason = same_access(unit, want, t, store_only and not exact, rhs)
                if ok:
                    chosen = (p, t)
                    break
                why = why or reason
            if chosen:
                break
        if not chosen:
            refused[tag + (why or 'no_exact_member')] += 1
            continue
        rng = A.node_range(outer, text)
        site_rng = A.node_range(node, text)
        new = member_text(unit, leaf, address_of, chosen[0], text)
        if rng is None or new is None or site_rng is None:
            refused[tag + 'source_range_unavailable'] += 1
            continue
        # Keep a wrapping parenthesis that is syntax of sizeof or follows an identifier character.
        if outer is not node and ((holder or {}).get('kind') == 'UnaryExprOrTypeTraitExpr'
                                  or (rng[0] and (text[rng[0] - 1].isalnum() or text[rng[0] - 1] == '_'))):
            rng = site_rng
        sites.append({
            'file': file, 'func': fn['name'], 'line': node.get('_l'), 'start': rng[0], 'end': rng[1],
            'old': text[rng[0]:rng[1]], 'new': new, 'record': key, 'offset': off, 'cast_type': want,
            'member_type': chosen[1], 'path': chosen[0], 'store_width_only': unit.canon(want) != unit.canon(chosen[1]),
        })
    return sites, refused


def _has_cast(e):
    for x, _ in A.walk(e):
        if x.get('kind') == 'CStyleCastExpr':
            return True
    return False


def scan_tu(args):
    root, rel, recipe, files, store_width_only = args
    try:
        unit, error = A.clang_unit(root, rel, recipe)
    except Exception as exc:  # recorded as a refusal of the whole TU
        return {'tu': rel, 'error': str(exc)[-300:], 'sites': [], 'refused': {}}
    if unit is None:
        return {'tu': rel, 'error': error, 'sites': [], 'refused': {}}
    sites, refused = [], collections.defaultdict(collections.Counter)
    for file, fn in unit.functions(set(files)):
        s, r = scan_function(unit, file, fn, store_width_only)
        sites.extend(s)
        refused[file].update(r)
    return {'tu': rel, 'error': error, 'sites': sites, 'refused': {f: dict(c) for f, c in refused.items()}}


def select_edits(sites):
    """Per file, drop sites nested inside another site (a later pass folds the outer one)."""
    by_file = collections.defaultdict(dict)
    for s in sites:
        by_file[s['file']][(s['start'], s['end'])] = s
    out = {}
    for file, spans in by_file.items():
        keep = []
        ordered = sorted(spans.values(), key=lambda s: (s['start'], -s['end']))
        for s in ordered:
            inner = [o for o in ordered if o is not s and s['start'] <= o['start'] and o['end'] <= s['end']]
            if inner:
                continue
            if keep and keep[-1]['end'] > s['start']:
                continue
            keep.append(s)
        out[file] = keep
    return out


def apply_edits(root, edits):
    """Write the planned replacements; returns {file: sites applied}."""
    done = {}
    for file, sites in edits.items():
        path = Path(root) / file
        text = path.read_text()
        for s in sorted(sites, key=lambda s: -s['start']):
            if text[s['start']:s['end']] != s['old']:
                raise ValueError('stale plan for %s:%s' % (file, s['line']))
            text = text[:s['start']] + s['new'] + text[s['end']:]
        path.write_text(text)
        done[file] = len(sites)
    return done


def physical_for(root, files):
    """Registered physical TUs (with recipes) whose stream contains each of `files` (the file itself, or the
    module/partition that includes it)."""
    import layout_compile_identity as L
    physical, members = L.recipes(root)
    want = set(files)
    out = {f: physical[f] for f in want if f in physical}
    rest = want - set(out)
    if rest:
        for tu, recipe in physical.items():
            if recipe['kind'] in ('overlay_module', 'slus_module'):
                text = (Path(root) / tu).read_text(errors='replace')
                for f in list(rest):
                    if Path(f).name in text:
                        out[tu] = recipe
    return out, physical


def plan(root, files, workers=6, store_width_only=True):
    """Scan the TUs that compile `files`; returns (edits by file, refusals by file, errors)."""
    tus, _ = physical_for(root, files)
    jobs = [(str(root), tu, recipe, sorted(files), store_width_only) for tu, recipe in sorted(tus.items())]
    sites, refused, errors = [], collections.defaultdict(collections.Counter), []
    with ProcessPoolExecutor(max_workers=workers) if workers > 1 else _Inline() as ex:
        for res in ex.map(scan_tu, jobs, chunksize=4):
            if res['error']:
                errors.append((res['tu'], res['error']))
            sites.extend(res['sites'])
            for f, c in res['refused'].items():
                refused[f].update(c)
    return select_edits(sites), refused, errors


class _Inline:
    """In-process stand-in for an executor (pool workers cannot always start their own pools)."""

    def __enter__(self):
        return self

    def __exit__(self, *exc):
        return False

    def map(self, fn, items, chunksize=1):
        return map(fn, items)


def folder_files(root, folder, files=None):
    root = Path(root)
    if files:
        return sorted(files)
    return sorted(p.relative_to(root).as_posix() for p in (root / folder).rglob('*.c'))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=HERE.parents[1])
    ap.add_argument('--folder', default='src')
    ap.add_argument('--file', nargs='*', default=[])
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--apply', action='store_true')
    ap.add_argument('--exact-stores', action='store_true', help='refuse width-only store matches')
    ap.add_argument('--workers', type=int, default=6)
    args = ap.parse_args(argv)
    root = args.root.resolve()
    files = folder_files(root, args.folder, args.file)
    edits, refused, errors = plan(root, files, args.workers, not args.exact_stores)
    args.out.mkdir(parents=True, exist_ok=True)
    with open(args.out / 'plan.jsonl', 'w') as fh:
        for file in sorted(edits):
            for s in edits[file]:
                fh.write(json.dumps(s, sort_keys=True) + '\n')
    reasons = collections.Counter()
    with open(args.out / 'refusals.tsv', 'w') as fh:
        fh.write('file\treason\tsites\n')
        for f in sorted(refused):
            for reason, n in sorted(refused[f].items()):
                fh.write('%s\t%s\t%d\n' % (f, reason, n))
                reasons[reason] += n
    summary = {'files': len(files), 'files_with_folds': len(edits), 'sites': sum(map(len, edits.values())),
               'refused': dict(reasons.most_common()), 'errors': errors[:20]}
    if args.apply:
        apply_edits(root, edits)
        summary['applied'] = True
    (args.out / 'summary.json').write_text(json.dumps(summary, indent=2) + '\n')
    print(json.dumps({k: summary[k] for k in ('files', 'files_with_folds', 'sites')}))
    return 0


if __name__ == '__main__':
    sys.exit(main())
