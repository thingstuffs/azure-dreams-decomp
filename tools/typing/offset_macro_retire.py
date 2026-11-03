#!/usr/bin/env python3
"""File-local raw-offset accessor macros: inventory of every use site and a rewrite planner.

    offset_macro_retire.py inventory --out DIR [--root R] [--file F ...] [--workers 6]
    offset_macro_retire.py prove --inventory DIR/offset_macros.tsv --out DIR/proof.tsv [--file F ...]
    offset_macro_retire.py plan --inventory DIR/offset_macros.tsv --patch OUT.patch [--root R]
                                [--proven DIR/proof.tsv] [--drop-unused] [--classes ...] [--file F ...] [--apply]

Some C files define accessor macros left over from recovery, e.g.

    #define U8(p, o) (*(u8 *)((u8 *)(p) + (o)))           U8(body, 0x9B)
    #define F(p, t, o) (*(t *)((u8 *)(p) + (o)))          F(actor, s16, 0x2A)
    #define SCR16(off) (*(u16 *)((u8 *)scratch + (off)))  SCR16(0x40)

The debt census (tools/lint/debt_check.py over tools/readability/score.py) is lexical and skips preprocessor
directives, so the casts inside such a body are counted nowhere and every use hides them.

`inventory` (read-only) finds every file-local macro under src/ whose body performs a pointer cast or a
byte-offset access (function-like or object-like), every use site of it (the outermost file-local macro
name token; nested file-local macros fold into the outer use), and joins each use to the clang facts of the
physical TU that compiles the file (tools/typing/cast_census.scan_unit: the casts of the expansion grouped
by their expansion location, with the census classification of the access, its base record, offset,
width and the member path `cast_fold.same_access` accepts).  Classes:

  direct_field   a typed struct base with a named member giving exactly the same access (union views
                 and signed/unsigned alternates picked by same_access; plain stores may take the other
                 signedness of the same width): `U8(body, 0x9B)` -> `body->action_phase.u`
  node_header    a negative offset from an object body that is an exact ObjectNodeHeader member
                 (`U16_AT(effect, -2)` -> `NODE_HEADER(effect)->flags`, the shared/object_node.h accessor)
  needs_member   a typed struct base, offset known, but no member starts there (gap / pad / inside an
                 array) or the member there differs in width, signedness or pointer type; `proposal`
                 names the member or view to add
  base_untyped   the base is not (yet) a struct pointer (void *, u8 *, an integer, a global byte array)
  other          generated views (S_<addr> records), constant addresses, variable offsets, address-only
                 macros, macros without a cast (array views) and anything the AST does not resolve

Outputs: DIR/offset_macros.tsv (one row per use site), DIR/macros.tsv (one row per definition),
DIR/summary.json.

Columns of note: base_type (clang type of the base argument), leaf_expr (the base the census reached through
any pointer casts in the argument), retype (base_untyped only: records whose members give every macro access
of that base in the function exactly, else the best partial match), hidden_casts (pointer casts the
expansion adds outside the arguments; debt_check counts none of them, see its --macro-casts report).

`prove` compiles each file's rewrite at its registered recipes (layout_compile_identity.capture_one, the
tu_identity primitive): all rows together, then row by row when the object changed, then a greedy
recombination; verdict per row (identical / object_changed / compile_error / object_changed_in_combination;
a node_header compile_error usually means the file does not include shared/object_node.h).  The file is
always restored.  gcc 2.7 schedules struct-member accesses differently from raw casts, so some folds move
loads: only proven rows should land.

`plan` rewrites the direct_field and node_header rows (with --proven: only rows proved identical): the use text (macro name through its closing parenthesis) becomes
`base->path` (`obj.path` for an `&obj` base, `(expr)->path` when the base is not a postfix expression), and a
macro definition is removed when no use of it remains in the file.  The planner refuses a file whose text
changed since the inventory (sha256 recorded per row).  Dry-run by default: a unified diff is written to
--patch; --apply writes the files.  Byte identity is not decided here: prove each edited TU with
tools/typing/tu_identity.py (snapshot before, compare after) and roll back any TU that changed.
"""
from __future__ import annotations

import argparse
import collections
from concurrent.futures import ProcessPoolExecutor
import csv
import difflib
import hashlib
import json
import os
from pathlib import Path
import re
import sys

HERE = Path(__file__).resolve().parent
TOOLS = HERE.parent
for _p in (HERE, TOOLS, TOOLS / 'lint', TOOLS / 'readability'):
    if str(_p) not in sys.path:
        sys.path.append(str(_p))

import score as S  # noqa: E402

DEFINE = re.compile(r'^[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)(\(([^)]*)\))?(.*)$', re.S)
UNDEF = re.compile(r'^[ \t]*#[ \t]*undef[ \t]+([A-Za-z_]\w*)')
# libgpu-style ordering-table link macros (owner ruling: the getaddr-inside-setaddr spelling is kept)
OT_LINK = re.compile(r'^(?:setaddr|getaddr|addPrim|addPrims|setlen|getlen|termPrim|catPrim)$')
POSTFIX = re.compile(r'^[A-Za-z_]\w*(?:\s*(?:->|\.)\s*[A-Za-z_]\w*|\s*\[[^\[\]]*\])*$')
FIELDS = ['file', 'function', 'line', 'macro', 'macro_shape', 'use', 'base_expr', 'base_type', 'leaf_expr', 'base_kind',
          'base_record', 'offset', 'offset_arg', 'access_type', 'width', 'signed', 'member', 'member_type', 'class', 'reason',
          'proposal', 'base_decl', 'retype', 'hidden_casts', 'census_sub', 'span', 'sha256']


# ------------------------------------------------------------------------------------------- lexical

def macro_definitions(text):
    """[{name, params (None for object-like), body, start, end, line}] of every #define, in order."""
    out = []
    for m in S.LEX.finditer(text):
        if m.lastgroup != 'directive':
            continue
        d = DEFINE.match(m[0])
        if not d:
            u = UNDEF.match(m[0])
            if u:
                out.append(dict(name=u.group(1), undef=True, start=m.start(), end=m.end(),
                                line=text.count('\n', 0, m.start()) + 1))
            continue
        params = None
        if d.group(2) is not None:
            params = [p.strip() for p in d.group(3).split(',') if p.strip()]
        body = d.group(4).replace('\\\n', ' ')
        out.append(dict(name=d.group(1), params=params, body=body.strip(), start=m.start(), end=m.end(),
                        line=text.count('\n', 0, m.start()) + 1, undef=False))
    return out


def body_casts(body):
    """Pointer casts lexically inside a macro body, and casts through a macro parameter type `(t)`/`(t *)`."""
    tokens = S.lex(body)
    pairs, _ = S.pairs_of(tokens)
    return len(S.cast_sites(tokens, pairs))


def expanded_casts(defn, defs, depth=0):
    """Lexical casts of a body plus those of the file-local macros it invokes (depth-capped)."""
    n = body_casts(defn['body'])
    if depth > 8:
        return n
    latest = {}
    for d in defs:
        if not d.get('undef') and d is not defn and (d['name'] not in latest or d['start'] < defn['start']):
            latest[d['name']] = d
    for d in latest.values():
        hits = len(re.findall(r'\b%s\b' % re.escape(d['name']), defn['body']))
        if hits:
            n += hits * expanded_casts(d, [x for x in defs if x is not defn], depth + 1)
    return n


def body_kind(defn, access_names=()):
    """'access' when the body casts to a pointer (or through a type parameter), 'offset' when it indexes or
    adds a parameter offset without a cast, 'nested' when it only invokes another access macro, else ''."""
    body = defn['body']
    params = defn.get('params') or []
    if body_casts(body):
        return 'access'
    for p in params:
        q = re.escape(p)
        # (*(t)(...)) / (*(t *)(...)): the pointer type is a parameter
        if re.search(r'\*\s*\(\s*%s\s*\*?\s*\)' % q, body) or re.search(r'\(\s*%s\s*\*\s*\)' % q, body):
            return 'access'
    if re.search(r'\(\s*[A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)*\s*\*+\s*\)', body):
        return 'access'
    for p in params:
        q = re.escape(p)
        if re.search(r'\[\s*\(?\s*%s\s*\)?\s*(?:/\s*\d+\s*)?\]' % q, body) or \
                re.search(r'\+\s*\(\s*%s\s*\)' % q, body):
            return 'offset'
    if access_names and any(re.search(r'\b%s\b' % re.escape(n), body) for n in access_names if n != defn['name']):
        return 'nested'
    return ''


def roles(defn):
    """Role of each parameter: p (base pointer), o (byte offset), t (access type), v (other value)."""
    params = defn.get('params')
    if params is None:
        return []
    body = defn['body']
    out = []
    for p in params:
        q = re.escape(p)
        if re.search(r'\(\s*\*?\s*\(\s*%s\s*\*?\s*\)(?=\s*[(\w])' % q, body) or \
                re.search(r'\(\s*volatile\s+%s\s*\*' % q, body):
            out.append('t')
        elif re.search(r'(?:\+|\[)\s*\(?\s*%s\b' % q, body):
            out.append('o')
        elif re.search(r'\)\s*\(\s*%s\s*\)|\(\s*%s\s*\)\s*->|\b%s\s*->|\(\s*%s\s*\)\s*\[' % (q, q, q, q), body):
            out.append('p')
        else:
            out.append('v')
    return out


def shape(defn):
    r = roles(defn)
    if defn.get('params') is None:
        return 'object'
    return '_'.join(r) or 'noargs'


def split_args(tokens, pairs, open_i, text):
    """[(arg text, start, end)] of the call whose '(' is tokens[open_i]."""
    close = pairs[open_i]
    args, start, depth = [], open_i + 1, 0
    for i in range(open_i + 1, close + 1):
        v = tokens[i].value
        if i == close or (v == ',' and depth == 0):
            if i > start:
                a, b = tokens[start].pos, tokens[i - 1].pos + len(tokens[i - 1].value)
                args.append((text[a:b], a, b))
            else:
                args.append(('', tokens[i].pos, tokens[i].pos))
            start = i + 1
            continue
        if v in '([{':
            depth += 1
        elif v in ')]}':
            depth -= 1
    return args


def file_uses(text, defs):
    """Use sites of the file-local access macros: [{macro, start (name token), end, args, function, line}].

    A use inside the argument list of another file-local macro use is folded into that outer use (clang
    reports its casts at the outer expansion)."""
    access = {}
    tokens = S.lex(text)
    pairs, _ = S.pairs_of(tokens)
    events = sorted(defs, key=lambda d: d['start'])
    fns = [(tokens[a].pos, tokens[e].pos, tokens[n].value) for a, n, b, e, s in S.definitions(tokens, pairs)]
    uses, ev, covered = [], 0, -1
    for i, t in enumerate(tokens):
        while ev < len(events) and events[ev]['start'] <= t.pos:
            d = events[ev]
            if d.get('undef'):
                access.pop(d['name'], None)
            else:
                access[d['name']] = d
            ev += 1
        if t.kind != 'id' or t.value not in access or t.pos < covered:
            continue
        if i and tokens[i - 1].value in ('.', '->'):
            continue
        d = access[t.value]
        if d['params'] is not None:
            if i + 1 >= len(tokens) or tokens[i + 1].value != '(' or (i + 1) not in pairs:
                continue
            close = pairs[i + 1]
            end = tokens[close].pos + 1
            args = split_args(tokens, pairs, i + 1, text)
        else:
            end, args = t.pos + len(t.value), []
        fn = next((name for a, b, name in fns if a <= t.pos <= b), '<global>')
        uses.append(dict(macro=t.value, defn=d, start=t.pos, end=end, args=args, function=fn,
                         line=text.count('\n', 0, t.pos) + 1))
        covered = end
    return uses


def file_macros(text):
    """(definitions of access macros, all definitions)."""
    defs = macro_definitions(text)
    names = set()
    while True:
        more = {d['name'] for d in defs if not d.get('undef') and body_kind(d, names)}
        if more <= names:
            break
        names |= more
    access = [d for d in defs if d.get('undef') and d['name'] in names or
              not d.get('undef') and body_kind(d, names)]
    return access, defs


# ------------------------------------------------------------------------------------------- clang facts

def _char_offsets(text):
    """byte offset -> char offset converter (identity for ASCII text)."""
    if text.isascii():
        return lambda b: b
    data = text.encode()
    table = {}
    def conv(b):
        if b not in table:
            table[b] = len(data[:b].decode(errors='replace'))
        return table[b]
    return conv


def _expansion(node):
    """(file, expansion byte offset, spelling byte offset, spelling file) of a macro-expanded node's begin."""
    begin = (node.get('range') or {}).get('begin') or {}
    exp = begin.get('expansionLoc') or {}
    spl = begin.get('spellingLoc') or {}
    return exp.get('_f'), exp.get('offset'), spl.get('offset'), spl.get('_f')


def _arg_types(unit, A, C, files):
    """{(file, spelling byte start, byte end): qualType} for nodes spelled in macro arguments."""
    out = {}
    for f, d in unit.functions(files):
        for node, parent in A.walk(d):
            rng = node.get('range') or {}
            b, e = rng.get('begin') or {}, rng.get('end') or {}
            bs, es = b.get('spellingLoc'), e.get('spellingLoc')
            if not bs or not es or bs.get('offset') is None or es.get('offset') is None:
                continue
            if (bs.get('_f') or f) != f or (es.get('_f') or f) != f:
                continue
            key = (f, bs['offset'], es['offset'] + es.get('tokLen', 1))
            if node.get('kind') in ('ImplicitCastExpr',):
                continue
            # outermost node wins: walk is pre-order, so keep the first
            out.setdefault(key, C.qtype(node))
    return out


def scan_tu(job):
    root, tu, recipe, files = job
    root = Path(root)
    sys.path[:0] = [str(root / 'tools' / 'typing'), str(root / 'tools')]
    import cast_ast as A
    import cast_census as CC
    import field_census as C
    try:
        unit, error = A.clang_unit(root, tu, recipe)
    except Exception as exc:  # recorded, never fatal
        return dict(tu=tu, error=str(exc)[-300:], casts=[], args={})
    if unit is None:
        return dict(tu=tu, error=error, casts=[], args={})
    want = set(files)
    rows = CC.scan_unit(unit, tu, want.__contains__)
    casts = []
    # scan_unit keeps the expansion offset in `starts`; recover file + spelling offsets from the AST itself
    by_node = {}
    for f, d in unit.functions(want):
        for node, parent in A.walk(d):
            if node.get('kind') == 'CStyleCastExpr' and A.in_macro(node):
                by_node.setdefault((d.get('name'), node.get('_l'), (node.get('range') or {}).get('begin', {}).get('col')),
                                   []).append(node)
    for r in rows:
        if not r.get('macro'):
            continue
        starts = r.get('starts') or []
        r = dict(r, exp=starts[-1] if starts else None, spell=starts[0] if len(starts) > 1 else None)
        off = r.get('access_offset', r.get('offset'))
        if r.get('base_kind') == 'struct' and r.get('base_record') in unit.layouts and isinstance(off, int):
            have = [(p, t) for p, t, _ in unit.leaves_at(r['base_record'], off)]
            r['have'] = have[-1] if have else None
            r['have_all'] = have
            if not have:
                lay = unit.layouts[r['base_record']]
                for node in lay.get('kids', []):
                    sz = unit.size(node['type']) or 0
                    if node['off'] <= off < node['off'] + sz:
                        r['covering'] = (node['name'], node['type'], node['off'])
        hdr = 'ObjectNodeHeader'
        if isinstance(off, int) and -0x20 <= off < 0 and hdr in unit.layouts and r.get('access') in ('star', 'index'):
            import cast_fold as F
            access = _strip_ptr(r.get('target'))
            cands = [(p, t) for p, t, _ in unit.leaves_at(hdr, 0x20 + off) if not F.PAD.search(p)]
            exact = [(p, t) for p, t in cands if F.same_access(unit, access, t, bool(r.get('store')))[0]]
            if exact or cands:
                r['node_member'], r['node_type'] = (exact or cands)[0]
                r['node_exact'] = bool(exact)
        casts.append(r)
    retype_candidates(unit, casts)
    for f, d in unit.functions(want):
        for node, parent in A.walk(d):
            if node.get('kind') == 'CStyleCastExpr' and A.in_macro(node):
                ef, eo, so, sf = _expansion(node)
                casts.append(dict(_spell_file=sf, _exp_file=ef, exp=eo, spell=so, func=d.get('name'), probe=1))
    args = {}
    for (f, a, b), t in _arg_types(unit, A, C, want).items():
        args['%s:%d:%d' % (f, a, b)] = t
    return dict(tu=tu, error=error, casts=casts, args=args)


def retype_candidates(unit, rows, limit=4):
    """For untyped bases (census class a): records whose members give every macro access of that base in the
    function exactly (same_access), as `retype` on each row: 'R1,R2 (+n more)' or 'best R k/n'."""
    import cast_census as CC
    import cast_fold as F
    groups = collections.defaultdict(list)
    for r in rows:
        if not r.get('sub', '').startswith('macro:a:') or r.get('access') not in ('star', 'index'):
            continue
        off = r.get('access_offset')
        if not isinstance(off, int) or off < 0:
            continue
        groups[(r.get('file'), r.get('func'), r.get('base_expr'), r.get('base_decl'))].append(r)
    records = [k for k, lay in unit.layouts.items()
               if lay.get('size') and not k.startswith('@') and not CC.GENERATED.search(k) and lay.get('kind') == 'struct']
    for key, grp in groups.items():
        acc = {(r['access_offset'], _strip_ptr(r.get('target')), bool(r.get('store'))) for r in grp}
        top = max(o for o, t, s_ in acc)
        full, best = [], (0, None)
        for rec in records:
            if unit.layouts[rec]['size'] <= top:
                continue
            ok = 0
            for off, want, store in acc:
                cands = [(p, t) for p, t, _ in unit.leaves_at(rec, off) if not F.PAD.search(p)]
                if any(F.same_access(unit, want, t, store)[0] for p, t in cands):
                    ok += 1
            if ok == len(acc):
                full.append(rec)
            elif ok > best[0]:
                best = (ok, rec)
        if full:
            text = ','.join(sorted(full)[:limit]) + (' (+%d more)' % (len(full) - limit) if len(full) > limit else '')
        elif best[1]:
            text = 'best %s %d/%d' % (best[1], best[0], len(acc))
        else:
            text = 'none'
        for r in grp:
            r['retype'] = text
            r['retype_accesses'] = len(acc)


def _strip_ptr(t):
    t = (t or '').strip()
    return t[:-1].strip() if t.endswith('*') else t


SIGNED = {'s8': 1, 's16': 1, 's32': 1, 'char': 1, 'signed char': 1, 'short': 1, 'int': 1, 'long': 1,
          'u8': 0, 'u16': 0, 'u32': 0, 'unsigned char': 0, 'unsigned short': 0, 'unsigned int': 0}


def classify_use(use, group, text):
    """Fill class / reason / proposal for one use from its grouped census rows."""
    rows = [r for r in group if not r.get('probe')]
    hidden = 0
    probes = [r for r in group if r.get('probe')]
    arg_spans = [(a, b) for _, a, b in use['args']]
    for r in probes:
        sp = r.get('spell_char')
        in_arg = sp is not None and r.get('_spell_file') == use['file'] and any(a <= sp < b for a, b in arg_spans)
        if not in_arg:
            hidden += 1
    out = dict(hidden_casts=hidden)
    deref = next((r for r in rows if r.get('access') in ('star', 'index', 'arrow')), rows[0] if rows else None)
    if deref is None:
        out.update({'class': 'other', 'reason': 'no_cast_in_expansion'})
        return out
    sub = deref.get('sub', '')
    inner = sub.split(':')
    icls, isub = (inner[1], ':'.join(inner[2:])) if len(inner) >= 3 else ('f', sub)
    access_type = _strip_ptr(deref.get('target')) if deref.get('access') in ('star', 'index') else ''
    out.update(census_sub='%s:%s' % (icls, isub), base_kind=deref.get('base_kind', ''),
               leaf_expr=deref.get('base_expr', ''), base_decl=deref.get('base_decl', ''),
               retype=deref.get('retype', ''),
               base_record=deref.get('base_record', ''), offset=deref.get('access_offset', deref.get('offset', '')),
               access_type=access_type, width=deref.get('width', ''),
               signed=SIGNED.get(access_type, ''), member=deref.get('path', ''),
               _have=deref.get('have'), _covering=deref.get('covering'))
    if deref.get('node_member'):
        out.update(_node=(deref['node_member'], deref['node_type'], deref['node_exact']))
    if out['member']:
        out['member_type'] = next((t for p, t in deref.get('have_all') or () if p == out['member']), '')
    elif out['_have']:
        out['member_type'] = '%s %s' % (out['_have'][1], out['_have'][0])
    if deref.get('access') == 'arrow':
        out['access_type'] = 'view ' + (deref.get('view') or '')
    if icls == 'n' and isub in ('fold_now', 'fold_view') and deref.get('path'):
        out.update({'class': 'direct_field', 'reason': isub})
    elif icls == 'n':
        out.update({'class': 'other', 'reason': isub})
    elif icls == 'b' and deref.get('base_kind') in ('struct',):
        out.update({'class': 'needs_member', 'reason': isub})
    elif icls == 'b':
        out.update({'class': 'other', 'reason': isub})
    elif icls == 'a':
        out.update({'class': 'base_untyped', 'reason': isub})
    else:
        out.update({'class': 'other', 'reason': '%s:%s' % (icls, isub)})
    return out


def propose(row, unit_members):
    """Member proposal for a needs_member row (a name/type to add, or a union view)."""
    off = row.get('offset')
    t = row.get('access_type') or ''
    if not isinstance(off, int):
        return ''
    reason = row.get('reason', '')
    have = row.get('_have')
    cover = row.get('_covering')
    if reason in ('signedness_differs',) and have:
        return 'union view at 0x%X over %s %s: add %s alternate' % (off, have[1], have[0], t)
    if reason in ('width_differs', 'pointer_type_differs', 'pointer_vs_integer', 'aggregate_differs') and have:
        return 'member %s (%s) at 0x%X; access is %s: add a %s view or retype' % (have[0], have[1], off, t, t)
    if reason in ('no_member', 'pad_member', 'inside_scalar', 'array_member', 'inside_substruct',
                  'array_of_struct', 'no_exact_member'):
        where = ' inside %s %s at 0x%X' % (cover[1], cover[0], cover[2]) if cover else ''
        return '%s unk_%X; /* 0x%03X */ in %s (%s%s)' % (t or '?', off, off, row.get('base_record'), reason, where)
    return ''


def inventory(root, out, only=None, workers=6, log=print):
    sys.path[:0] = [str(root / 'tools' / 'typing'), str(root / 'tools')]
    import cast_fold as F
    files = sorted(p.relative_to(root).as_posix() for p in (root / 'src').rglob('*.c'))
    if only:
        files = [f for f in files if f in set(only)]
    per_file, macro_rows = {}, []
    for f in files:
        path = root / f
        if path.stat().st_size > 4 * 1024 * 1024:
            continue
        text = path.read_text()
        if '#' not in text or 'define' not in text:
            continue
        access, defs = file_macros(text)
        live = [d for d in access if not d.get('undef')]
        if not live:
            continue
        uses = file_uses(text, access)
        per_file[f] = dict(text=text, defs=access, uses=uses)
        counts = collections.Counter(u['defn']['start'] for u in uses)
        names = {d['name'] for d in live}
        seen = collections.Counter()
        for d in live:
            seen[d['name']] += 1
            macro_rows.append(dict(file=f, macro=d['name'], line=d['line'], shape=shape(d),
                                   kind=body_kind(d, names), lexical_body_casts=expanded_casts(d, live),
                                   redefined=int(seen[d['name']] > 1), uses=counts[d['start']],
                                   nested_mentions=sum(len(re.findall(r'\b%s\b' % re.escape(d['name']), x['body']))
                                                       for x in live if x['name'] != d['name']),
                                   body=d['body'][:160]))
    log('%d files define %d access macros; %d use sites' % (len(per_file), len(macro_rows),
                                                           sum(len(v['uses']) for v in per_file.values())))
    tus, _ = F.physical_for(root, sorted(per_file))
    jobs = [(str(root), tu, recipe, sorted(per_file)) for tu, recipe in sorted(tus.items())]
    casts_by_file = collections.defaultdict(list)
    arg_types, errors = {}, []
    with ProcessPoolExecutor(max_workers=workers) as ex:
        for res in ex.map(scan_tu, jobs, chunksize=1):
            if res['error']:
                errors.append((res['tu'], res['error']))
            for r in res['casts']:
                f = r.get('file') or r.get('_exp_file')
                casts_by_file[f].append(r)
            arg_types.update(res['args'])
            log('  %s: %d macro casts' % (res['tu'], len(res['casts'])))
    rows = []
    for f, info in sorted(per_file.items()):
        text = info['text']
        conv = _char_offsets(text)
        sha = hashlib.sha256(text.encode()).hexdigest()
        groups = collections.defaultdict(list)
        seen_keys = set()
        for r in casts_by_file.get(f, []):
            if r.get('exp') is None:
                continue
            if r.get('probe') and r.get('_exp_file') != f:
                continue
            key = (r.get('probe', 0), r.get('exp'), r.get('spell'), r.get('cls'), r.get('sub'), r.get('line'),
                   r.get('target'))
            if key in seen_keys:      # one file compiled by several physical TUs
                continue
            seen_keys.add(key)
            r = dict(r, exp_char=conv(r['exp']), spell_char=None if r.get('spell') is None else conv(r['spell']))
            groups[r['exp_char']].append(r)
        for u in info['uses']:
            u['file'] = f
            row = dict(file=f, function=u['function'], line=u['line'], macro=u['macro'],
                       macro_shape=shape(u['defn']), use=' '.join(text[u['start']:u['end']].split())[:120],
                       span='%d:%d' % (u['start'], u['end']), sha256=sha)
            rl = roles(u['defn'])
            base = u['args'][rl.index('p')] if 'p' in rl and len(u['args']) == len(rl) else None
            if base is not None:
                row['base_expr'] = ' '.join(base[0].split())
                bs = base[1]
                # clang spans are bytes; find the node exactly covering the argument text
                enc = text[:bs].encode()
                b0 = len(enc)
                b1 = b0 + len(base[0].encode())
                row['base_type'] = arg_types.get('%s:%d:%d' % (f, b0, b1), '')
            cls = classify_use(u, groups.get(u['start'], []), text)
            row.update(cls)
            if 'o' in rl and len(u['args']) == len(rl):
                row['offset_arg'] = ' '.join(u['args'][rl.index('o')][0].split())
                if row.get('offset') in (None, ''):
                    row['offset'] = row['offset_arg']
            node = row.pop('_node', None)
            if node and row['class'] != 'direct_field' and 'p' in rl and 'o' in rl:
                try:
                    literal = int(row.get('offset_arg', '').replace(' ', ''), 0)
                except ValueError:
                    literal = None
                if literal is not None and literal == row.get('offset'):
                    row['member'], row['member_type'] = node[0], node[1]
                    if node[2]:
                        row.update({'class': 'node_header', 'reason': 'NODE_HEADER(base)->%s' % node[0]})
                    else:
                        row['proposal'] = 'NODE_HEADER(base)->%s (%s; access is %s: type the consumer first)' % (
                            node[0], node[1], row.get('access_type'))
            if OT_LINK.match(u['macro']):
                row.update({'class': 'other', 'reason': 'ot_link_macro'})
            if row['class'] == 'other' and row.get('reason') == 'no_cast_in_expansion' and body_kind(u['defn']) == 'offset':
                row['reason'] = 'array_view_macro'
            if row['class'] == 'needs_member':
                row['proposal'] = propose(row, None)
            rows.append(row)
    # member lookups for proposals need the layouts: second pass from the census rows (have = member at off)
    out.mkdir(parents=True, exist_ok=True)
    (out / '.ignore').write_text('*\n')
    with (out / 'offset_macros.tsv').open('w', newline='') as fh:
        w = csv.DictWriter(fh, FIELDS, delimiter='\t', lineterminator='\n', extrasaction='ignore')
        w.writeheader()
        for r in rows:
            w.writerow({k: r.get(k, '') for k in FIELDS})
    with (out / 'macros.tsv').open('w', newline='') as fh:
        keys = ['file', 'macro', 'line', 'shape', 'kind', 'lexical_body_casts', 'redefined', 'uses', 'nested_mentions',
                'body']
        w = csv.DictWriter(fh, keys, delimiter='\t', lineterminator='\n')
        w.writeheader()
        for r in macro_rows:
            w.writerow(r)
    summary = dict(
        files=len(per_file), macros=len(macro_rows), use_sites=len(rows),
        by_class=dict(collections.Counter(r['class'] for r in rows)),
        hidden_casts_rewritable=sum(int(r.get('hidden_casts') or 0) for r in rows
                                    if r['class'] in ('direct_field', 'node_header')),
        by_reason=dict(collections.Counter('%s:%s' % (r['class'], r.get('reason', '')) for r in rows).most_common()),
        by_shape=dict(collections.Counter(r['macro_shape'] for r in rows)),
        hidden_casts_clang=sum(int(r.get('hidden_casts') or 0) for r in rows),
        hidden_casts_by_class={k: sum(int(r.get('hidden_casts') or 0) for r in rows if r['class'] == k)
                               for k in sorted({r['class'] for r in rows})},
        lexical_hidden_casts=sum(m['lexical_body_casts'] * m['uses'] for m in macro_rows),
        unused_macros=sum(1 for m in macro_rows if not m['uses'] and not m['nested_mentions']),
        nested_only_macros=sum(1 for m in macro_rows if not m['uses'] and m['nested_mentions']),
        files_fully_direct=sorted({f for f in per_file if
                                   all(r['class'] == 'direct_field' for r in rows if r['file'] == f)
                                   and any(r['file'] == f for r in rows)}),
        errors=errors)
    (out / 'summary.json').write_text(json.dumps(summary, indent=1) + '\n')
    return rows, summary


# ------------------------------------------------------------------------------------------- planner

def member_spelling(base, path):
    """`base->path`, `obj.path` for `&obj`, `(expr)->path` for a non-postfix base."""
    b = base.strip()
    while b.startswith('(') and b.endswith(')') and _balanced(b[1:-1]):
        b = b[1:-1].strip()
    if b.startswith('&') and not b.startswith('&&'):
        obj = b[1:].strip()
        if POSTFIX.match(obj):
            return obj + '.' + path
        return '(' + obj + ').' + path
    if POSTFIX.match(b):
        return b + '->' + path
    return '(' + b + ')->' + path


def _balanced(s):
    depth = 0
    for ch in s:
        depth += ch == '('
        depth -= ch == ')'
        if depth < 0:
            return False
    return depth == 0


REWRITE = ('direct_field', 'node_header')
CAST_PREFIX = re.compile(r'^\(\s*(?:const\s+|volatile\s+)*[A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)*\s*\*+\s*\)\s*')


def _squash(t):
    return re.sub(r'\s+', '', t or '')


def _unparen(b):
    b = b.strip()
    while b.startswith('(') and b.endswith(')') and _balanced(b[1:-1]):
        b = b[1:-1].strip()
    return b


def base_spelling(arg, leaf):
    """The base text to write before `->path`: the macro argument itself, or the argument with its leading
    pointer casts peeled when clang's census walked through them to a typed leaf (`((u8 *)p)` with p a
    struct pointer).  None when the argument does not spell the census leaf (refuse the row)."""
    b = _unparen(arg)
    want = _squash(leaf)
    while True:
        if _squash(b) == want:
            return b
        m = CAST_PREFIX.match(b)
        if not m:
            return None
        b = _unparen(b[m.end():])


def plan_file(text, rows, classes=('direct_field', 'node_header')):
    """(new text, uses rewritten, definitions removed, skipped rows) for one file.

    rows: inventory rows for this file (dicts with span, macro_shape, class, member, base_expr, leaf_expr)."""
    edits, skipped = [], []
    rewritten = collections.Counter()
    for r in rows:
        if r['class'] not in classes or not r.get('member'):
            continue
        rl = r['macro_shape'].split('_')
        if 'p' not in rl or 'o' not in rl or not set(rl) <= {'p', 'o', 't'}:
            skipped.append((r, 'shape ' + r['macro_shape']))
            continue
        a, b = (int(x) for x in r['span'].split(':'))
        use = text[a:b]
        tokens = S.lex(use)
        pairs, _ = S.pairs_of(tokens)
        if len(tokens) < 2 or tokens[0].value != r['macro'] or tokens[1].value != '(' or pairs.get(1) != len(tokens) - 1:
            raise ValueError('%s: span %s is not a use of %s' % (r['file'], r['span'], r['macro']))
        args = split_args(tokens, pairs, 1, use)
        if len(args) != len(rl):
            skipped.append((r, 'argument count'))
            continue
        base = args[rl.index('p')][0]
        if ' '.join(base.split()) != r.get('base_expr'):
            raise ValueError('%s: base text changed at %s' % (r['file'], r['span']))
        if r['class'] == 'node_header':
            # the header macro casts any body pointer; redundant pointer casts on the argument go
            body = _unparen(base)
            while CAST_PREFIX.match(body):
                body = _unparen(body[CAST_PREFIX.match(body).end():])
            edits.append((a, b, 'NODE_HEADER(%s)->%s' % (body, r['member'])))
            rewritten[r['macro']] += 1
            continue
        spelled = base_spelling(base, r.get('leaf_expr') or base)
        if spelled is None:
            skipped.append((r, 'base %s does not spell census leaf %s' % (base, r.get('leaf_expr'))))
            continue
        edits.append((a, b, member_spelling(spelled, r['member'])))
        rewritten[r['macro']] += 1
    new = text
    for a, b, rep in sorted(edits, reverse=True):
        new = new[:a] + rep + new[b:]
    # definitions (and #undefs) of a rewritten macro go once nothing outside them mentions the name
    defs = macro_definitions(new)
    tokens = S.lex(new)
    removals = []
    for name in sorted(rewritten):
        own = [d for d in defs if d['name'] == name]
        code = sum(1 for t in tokens if t.kind == 'id' and t.value == name)
        directives = sum(len(re.findall(r'\b%s\b' % re.escape(name), d['body'] if not d.get('undef') else ''))
                         for d in defs if d['name'] != name)
        others = [m for m in S.LEX.finditer(new) if m.lastgroup == 'directive' and re.search(r'\b%s\b' % re.escape(name), m[0])
                  and not any(d['start'] == m.start() for d in own)]
        if code or directives or others:
            continue
        for d in own:
            a, b = d['start'], d['end']
            if b < len(new) and new[b] == '\n':
                b += 1
            removals.append((a, b))
    for a, b in sorted(removals, reverse=True):
        new = new[:a] + new[b:]
        # a removed definition block leaves at most one blank line behind
        while a >= 2 and new[a - 2:a] == '\n\n' and new[a:a + 1] == '\n':
            new = new[:a] + new[a + 1:]
    return new, sum(rewritten.values()), len(removals), skipped


def _load_rows(inventory_tsv, only=None, proven=None):
    rows = list(csv.DictReader(open(inventory_tsv), delimiter='\t'))
    ok = None
    if proven:
        ok = {(r['file'], r['span']) for r in csv.DictReader(open(proven), delimiter='\t')
              if r['verdict'] == 'identical'}
    by_file = collections.defaultdict(list)
    for r in rows:
        if only and r['file'] not in only:
            continue
        if ok is not None and r['class'] in REWRITE and (r['file'], r['span']) not in ok:
            r = dict(r, **{'class': r['class'] + '_held'})
        by_file[r['file']].append(r)
    return by_file


def drop_unused(text):
    """Remove access-macro definitions with no use and no other mention (dead after earlier rewrites);
    repeated until nothing changes (a removed macro may have been the last user of another)."""
    total = 0
    while True:
        text, n = _drop_unused_once(text)
        total += n
        if not n:
            return text, total


def _drop_unused_once(text):
    access, _ = file_macros(text)
    uses = collections.Counter(u['macro'] for u in file_uses(text, access))
    tokens = S.lex(text)
    code = collections.Counter(t.value for t in tokens if t.kind == 'id')
    directives = [m for m in S.LEX.finditer(text) if m.lastgroup == 'directive']
    removals = []
    for d in access:
        if d.get('undef') or uses[d['name']] or code[d['name']]:
            continue
        same = [x for x in access if x['name'] == d['name']]
        if any(re.search(r'\b%s\b' % re.escape(d['name']), m[0]) for m in directives
               if not any(x['start'] == m.start() for x in same)):
            continue
        a, b = d['start'], d['end']
        if b < len(text) and text[b] == '\n':
            b += 1
        removals.append((a, b))
    for a, b in sorted(removals, reverse=True):
        text = text[:a] + text[b:]
        while a >= 2 and text[a - 2:a] == '\n\n' and text[a:a + 1] == '\n':
            text = text[:a] + text[a + 1:]
    return text, len(removals)


def plan(root, inventory_tsv, patch, only=None, apply=False, log=print, proven=None, unused=False,
         classes=REWRITE):
    by_file = _load_rows(inventory_tsv, only, proven)
    macros_tsv = Path(inventory_tsv).with_name('macros.tsv')
    if unused and macros_tsv.is_file():
        # files whose access macros have no use at all have no use rows
        for m in csv.DictReader(open(macros_tsv), delimiter='\t'):
            if not only or m['file'] in only:
                by_file.setdefault(m['file'], [])
    diff, totals, refused = [], collections.Counter(), []
    for f, frows in sorted(by_file.items()):
        totals['held_rows'] += sum(1 for r in frows if r['class'].endswith('_held'))
        if not any(r['class'] in classes for r in frows) and not unused:
            continue
        path = root / f
        text = path.read_text()
        if frows and hashlib.sha256(text.encode()).hexdigest() != frows[0]['sha256']:
            refused.append((f, 'text changed since inventory'))
            continue
        try:
            new, n, removed, skip = plan_file(text, frows, classes)
        except ValueError as exc:
            refused.append((f, str(exc)))
            continue
        if unused:
            new, dead = drop_unused(new)
            totals['unused_definitions_removed'] += dead
        totals['skipped_rows'] += len(skip)
        for r, why in skip:
            log('  kept %s:%s %s (%s)' % (f, r['line'], r['use'], why))
        if new == text:
            continue
        totals['files'] += 1
        totals['uses'] += n
        totals['definitions_removed'] += removed
        diff.extend(difflib.unified_diff(text.splitlines(True), new.splitlines(True), 'a/' + f, 'b/' + f))
        if apply:
            path.write_text(new)
    Path(patch).parent.mkdir(parents=True, exist_ok=True)
    Path(patch).write_text(''.join(diff))
    log('%d files, %d uses rewritten, %d definitions removed (+%d unused), %d direct rows held by proof, '
        '%d kept by the planner; %d files refused' %
        (totals['files'], totals['uses'], totals['definitions_removed'], totals['unused_definitions_removed'],
         totals['held_rows'], totals['skipped_rows'], len(refused)))
    for f, why in refused:
        log('  refused %s: %s' % (f, why))
    return totals, refused


# ------------------------------------------------------------------------------------------- proof

def _digest(res):
    return (res['raw_sha256'], res['canonical_object_sha256'], json.dumps(res.get('variant_raw_sha256'), sort_keys=True))


def _capture_all(root, tus):
    import layout_compile_identity as L
    out = {}
    for tu, recipe in sorted(tus.items()):
        try:
            out[tu] = _digest(L.capture_one(root, tu, recipe))
        except Exception as exc:  # a compile error is a changed object
            out[tu] = ('error', str(exc)[-200:])
    return out


def prove_file(job):
    """Per-row object identity of one file's direct_field rewrites (all rows, then row by row on failure).

    Writes the candidate text into the root temporarily and always restores the original."""
    root, f, rows = job
    root = Path(root)
    sys.path[:0] = [str(root / 'tools' / 'typing'), str(root / 'tools')]
    import cast_fold as F
    tus, _ = F.physical_for(root, [f])
    path = root / f
    original = path.read_text()
    verdicts = {}
    try:
        base = _capture_all(root, tus)
        if any(v[0] == 'error' for v in base.values()):
            return f, {r['span']: 'baseline_error' for r in rows}

        def same(subset, detail=False):
            new, n, removed, skip = plan_file(original, subset)
            path.write_text(new)
            try:
                got = _capture_all(root, tus)
                ok = got == base
                if detail:
                    ok = 'identical' if ok else ('compile_error' if any(v[0] == 'error' for v in got.values())
                                                 else 'object_changed')
                return ok, {x['span'] for x, _ in skip}
            finally:
                path.write_text(original)

        ok, skipped = same(rows)
        if ok:
            return f, {r['span']: 'planner_kept' if r['span'] in skipped else 'identical' for r in rows}
        good = []
        for r in rows:
            single, skipped = same([r], detail=True)
            verdicts[r['span']] = 'planner_kept' if r['span'] in skipped else single
            if verdicts[r['span']] == 'identical':
                good.append(r)
        # interactions: grow the accepted set greedily
        if good and not same(good)[0]:
            accepted = []
            for r in good:
                if same(accepted + [r])[0]:
                    accepted.append(r)
                else:
                    verdicts[r['span']] = 'object_changed_in_combination'
        return f, verdicts
    finally:
        path.write_text(original)


def prove(root, inventory_tsv, out, only=None, workers=6, log=print):
    by_file = _load_rows(inventory_tsv, only)
    jobs = []
    for f, frows in sorted(by_file.items()):
        direct = [r for r in frows if r['class'] in REWRITE]
        if not direct:
            continue
        if hashlib.sha256((root / f).read_text().encode()).hexdigest() != frows[0]['sha256']:
            log('  refused %s: text changed since inventory' % f)
            continue
        # unchanged rows of other classes ride along untouched (plan_file ignores them)
        jobs.append((str(root), f, direct))
    results = []
    with ProcessPoolExecutor(max_workers=workers) as ex:
        for f, verdicts in ex.map(prove_file, jobs):
            for r in by_file[f]:
                if r['class'] in REWRITE:
                    results.append(dict(file=f, line=r['line'], span=r['span'], use=r['use'], member=r['member'],
                                        verdict=verdicts.get(r['span'], 'missing')))
            c = collections.Counter(verdicts.values())
            log('  %s: %s' % (f, dict(c)))
    out = Path(out)
    out.parent.mkdir(parents=True, exist_ok=True)
    with out.open('w', newline='') as fh:
        w = csv.DictWriter(fh, ['file', 'line', 'span', 'use', 'member', 'verdict'], delimiter='\t', lineterminator='\n')
        w.writeheader()
        w.writerows(results)
    total = collections.Counter(r['verdict'] for r in results)
    log('proof: %s' % dict(total))
    return results


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest='mode', required=True)
    i = sub.add_parser('inventory')
    i.add_argument('--root', type=Path, default=TOOLS.parent)
    i.add_argument('--out', type=Path, required=True)
    i.add_argument('--file', nargs='*')
    i.add_argument('--workers', type=int, default=6)
    p = sub.add_parser('plan')
    p.add_argument('--root', type=Path, default=TOOLS.parent)
    p.add_argument('--inventory', type=Path, required=True)
    p.add_argument('--patch', type=Path, required=True)
    p.add_argument('--file', nargs='*')
    p.add_argument('--apply', action='store_true')
    p.add_argument('--proven', type=Path, help='prove output: rewrite only rows whose verdict is identical')
    p.add_argument('--drop-unused', action='store_true', help='also remove access macros with no use left')
    p.add_argument('--classes', nargs='+', default=list(REWRITE), choices=REWRITE,
                   help='row classes to rewrite (default: direct_field node_header)')
    v = sub.add_parser('prove')
    v.add_argument('--root', type=Path, default=TOOLS.parent)
    v.add_argument('--inventory', type=Path, required=True)
    v.add_argument('--out', type=Path, required=True, help='per-row verdict TSV')
    v.add_argument('--file', nargs='*')
    v.add_argument('--workers', type=int, default=6)
    args = ap.parse_args(argv)
    root = args.root.resolve()
    os.chdir(root)
    if args.mode == 'inventory':
        _, summary = inventory(root, args.out.resolve(), args.file, args.workers)
        print(json.dumps({k: summary[k] for k in ('files', 'macros', 'use_sites', 'by_class',
                                                   'hidden_casts_clang', 'lexical_hidden_casts')}))
        return 0
    if args.mode == 'prove':
        prove(root, args.inventory, args.out, set(args.file or ()) or None, args.workers)
        return 0
    totals, refused = plan(root, args.inventory, args.patch, set(args.file or ()) or None, args.apply,
                           proven=args.proven, unused=args.drop_unused, classes=tuple(args.classes))
    return 1 if refused else 0


if __name__ == '__main__':
    sys.exit(main())
