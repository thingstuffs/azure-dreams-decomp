#!/usr/bin/env python3
"""Classify the census `byte_cursor` casts by what the original code most likely was, with a route each.

    byte_cursor_classify.py --root . --census CENSUS_DIR --out DIR

Input: the cast census (census.py: CENSUS_DIR/census.tsv.gz) and the code map's cast_site / record
tables (build/codemap.db, read-only).  No compiler, no source mutation.  Every census row of category
`byte_cursor` gets one class (column `bc_class`) and a route (column `bc_route`):

  stream_reader      1  the base pointer is advanced by a data-dependent amount, or the offset is read from
                        the same base (`cmd + cmd->next`): a genuine byte stream (script/bytecode, sequence,
                        parsers, card/save data, text).  Route: legitimate end state (counted floor), or
                        an original-style reader macro only where it stays byte-exact and reads better
  record_walk        1b the base is advanced by a constant step and every access lies inside one step: an
                        array of records walked through a byte cursor (packets, tables).  Route: one typed
                        element pointer per step (an SDK primitive type for GPU packets)
  typed_member       2a typed record base, the code map already resolves a member at the offset/width
                        (addr_member, fold_now, redundant).  Route: guarded_routes / offset_macro_retire
  layout_gap         2b typed record base whose layout lacks the accessed member or has another width or
                        signedness (beyond_struct, pad_member, width_differs, negative_offset ...).  Route:
                        extend or correct the record layout (negative offsets: container / NODE_HEADER)
  untyped_record     2c void/byte/scalar base read at constant offsets, never advanced: an untyped record
                        pointer.  Route: retype the variable/parameter to a record type; `candidates`
                        lists existing records whose members match every accessed (offset, width)
  global_record      2d a global addressed at a constant byte offset.  Route: declare the global with its
                        record (or array) type
  array_stride       3  variable offset that is not data-driven (index * size, pre-scaled index): an array
                        element.  Route: typed array / element pointer; byte-scaled indices that the
                        compiler needs stay (check per site)
  other              4  conversions without an addressed access, unresolved sites

`domain` tags the function's subject (script, audio_sequence, card_save, text, decompress, cd_file,
gpu_packet) from its path and name; it is evidence for stream_reader, never the decider.

Outputs (DIR, ignored): byte_cursor_sites.tsv.gz (every site), groups.tsv (one row per function and base
variable), summary.json (class x folder counts), top_functions.tsv, worklist_<class>.tsv.
"""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
import csv
import gzip
import json
from pathlib import Path
import re
import sqlite3
import sys

HERE = Path(__file__).resolve().parent
CLASSES = ('stream_reader', 'record_walk', 'typed_member', 'layout_gap', 'untyped_record', 'global_record',
           'array_stride', 'other')
ROUTES = {
    'stream_reader': 'legitimate floor / reader macro',
    'record_walk': 'typed element pointer per step',
    'typed_member': 'guarded_routes or offset_macro_retire (member exists)',
    'layout_gap': 'extend/correct record layout',
    'untyped_record': 'retype variable to record type',
    'global_record': 'declare global with record type',
    'array_stride': 'typed array element',
    'other': 'inspect',
}
MEMBER_SUBS = {'addr_member', 'fold_now', 'redundant', 'struct_member', 'member'}
GAP_SUBS = {'beyond_struct', 'addr_beyond_struct', 'pad_member', 'width_differs', 'signedness_differs',
            'inside_scalar', 'negative_offset', 'pointer_vs_integer', 'addr_array_member', 'view_variable_offset'}
DOMAINS = (
    ('script', re.compile(r'script|bytecode|opcode_|interp|(?<![a-z])vm_|command_stream|event_cmd|run_.*commands', re.I)),
    ('audio_sequence', re.compile(r'audio/sequence|(?<![a-z])seq_|_seq(?![a-z])|note_|midi|sound_data|(?<![a-z])spu', re.I)),
    ('card_save', re.compile(r'libcard|frontend/card|memcard|save|card_', re.I)),
    ('text', re.compile(r'(?<![a-z])text(?!ur)|message|string|glyph|font|kanji', re.I)),
    ('decompress', re.compile(r'decompress|decode|unpack|(?<![a-z])lz|(?<![a-z])rle(?![a-z])|inflate', re.I)),
    ('cd_file', re.compile(r'engine/cd|cd_image|archive|(?<![a-z])file|chunk|packed', re.I)),
    ('gpu_packet', re.compile(r'packet|prim|poly|sprt|ordering|_ot_|gpu|draw_|render_|quad', re.I)),
)
IDENT = r'[A-Za-z_]\w*'


def base_name(row, cm):
    """The base variable of the addressed chain: code map base_expr, else the first lvalue in the cast text."""
    expr = (cm or {}).get('base_expr') or ''
    if re.fullmatch(IDENT + r'(?:(?:->|\.)' + IDENT + r')*', expr):
        return expr
    text = row.get('cast_text', '')
    m = re.match(r'\(\s*[^()]*\)\s*', text)
    rest = text[m.end():] if m else text
    for _ in range(6):
        rest = rest.lstrip('( ')
        mm = re.match(r'(?:(?:const|volatile|struct|unsigned|signed)\s+)*\w+\s*\**\s*\)\s*', rest)
        if mm and '*' in mm[0]:
            rest = rest[mm.end():]
            continue
        break
    m = re.match(r'&?\s*(' + IDENT + r'(?:(?:->|\.)' + IDENT + r')*)', rest.lstrip('&( '))
    return m[1] if m else ''


def domain_of(path, function):
    text = path + ' ' + function
    return next((name for name, rx in DOMAINS if rx.search(text)), '')


def advancement(body, name):
    """('', None) not advanced; ('const', step) constant step; ('data', None) data-dependent step."""
    if not name or not body:
        return '', None
    n = re.escape(name)
    steps = []
    for m in re.finditer(r'(?<![\w.>])' + n + r'\s*(\+\+|--|\+=|-=)\s*([^;,)]*)', body):
        op, rhs = m[1], m[2].strip()
        steps.append(1 if op in ('++', '--') else rhs)
    for m in re.finditer(r'(\+\+|--)\s*' + n + r'\b', body):
        steps.append(1)
    for m in re.finditer(r'(?<![\w.>=!<])' + n + r'\s*=(?!=)\s*([^;]*)', body):
        # p = p + k / p = (T *)((u8 *)p + k) / p = &p[k]: the cursor advances by k.  A value loaded
        # through the base (p = p->next, p = *(T **)((u8 *)p + 4)) is a list walk, not an advance.
        rhs = m[1].strip()
        bare = rhs
        for _ in range(6):
            bare = re.sub(r'^\(\s*(?:(?:const|volatile|struct|unsigned|signed)\s+)*\w+(?:\s+\w+)*\s*\*+\s*\)\s*', '', bare)
            if bare.startswith('(') and bare.endswith(')'):
                bare = bare[1:-1].strip()
        if bare.startswith('*') or re.search(n + r'\s*(?:->|\[|\.)', bare.replace('&' + name + '[', '')):
            if not re.match(r'&\s*' + n + r'\s*\[', bare):
                continue
        k = re.match(r'(?:\(\s*\w+\s*\*+\s*\)\s*)?\(?\s*' + n + r'\s*\)?\s*[+\-]\s*(.+)$', bare)
        k = k or re.match(r'&\s*' + n + r'\s*\[\s*(.+)\]$', bare)
        if not k:
            continue
        step = k[1].strip().strip('()').strip()
        steps.append(step)
    if not steps:
        return '', None
    consts = []
    for s in steps:
        if isinstance(s, int):
            consts.append(s)
        elif re.fullmatch(r'0x[0-9A-Fa-f]+|\d+', s):
            consts.append(int(s, 0))
        elif s.startswith('sizeof'):
            consts.append(-1)
        else:
            return 'data', None
    return 'const', max(consts) if consts else None


def classify(row, cm, adv, step):
    """(class, subclass) for one byte_cursor census row."""
    kind = (cm or {}).get('base_kind') or ''
    decl = ((cm or {}).get('base_decl') or '').split(':')[0]
    sub = (cm or {}).get('sub') or row.get('ast_sub', '')
    access = (cm or {}).get('access') or ''
    text = row.get('cast_text', '')
    variable = row.get('variable_offset') in ('True', True, '1')
    name = row.get('_base', '')
    try:
        off = int(row.get('chain_offset') or (cm or {}).get('offset') or 0)
    except ValueError:
        off = 0
    data_driven = bool(variable and name and len(re.findall(r'(?<![\w.>])' + re.escape(name) + r'(?![\w])', text)) >= 2)
    if adv == 'data' or data_driven:
        return 'stream_reader', 'data_driven_offset' if data_driven else 'data_step_cursor'
    if adv == 'const':
        if step in (None, -1) or step <= 0 or variable or 0 <= off < max(step, 1):
            return 'record_walk', 'constant_step_%s' % (step if step not in (None, -1) else 'sizeof')
        # an access beyond one step: the variable is a record pointer that is also reused as a short
        # cursor elsewhere in the function (register reuse); classify the access as a record access
    if kind == 'struct' or kind == 'struct_array' or (row.get('chain_base_type', '').rstrip(' *') not in
                                                       ('void', 'u8', 's8', 'char', 'unsigned char', 'signed char', '')
                                                       and kind not in ('void', 'byte', 'scalar', 'global', 'pointer_pointer')
                                                       and not row.get('chain_base_type', '').startswith(('short', 's16', 'u16', 's32', 'u32', 'int', 'unsigned'))):
        if variable:
            return 'array_stride', 'struct_member_array'
        if sub in MEMBER_SUBS or sub.endswith('fold_now') or sub.endswith('addr_member'):
            return 'typed_member', sub or 'member'
        if sub in GAP_SUBS or sub.endswith(tuple(GAP_SUBS)) or off < 0:
            return 'layout_gap', sub or ('negative_offset' if off < 0 else 'gap')
        return 'layout_gap', sub or 'unresolved_member'
    if variable:
        if kind == 'global' or decl == 'global':
            return 'array_stride', 'global_table'
        if re.search(r'\*\s*(?:0x[0-9A-Fa-f]+|\d+)|<<\s*\d+|sizeof', text):
            return 'array_stride', 'scaled_index'
        return 'array_stride', 'byte_index'
    if kind == 'global' or decl in ('global', 'addr'):
        return 'global_record', sub or 'global'
    if access == 'value' and not re.search(r'[+\-]', text):
        return 'other', 'conversion'
    if kind in ('void', 'byte', 'scalar', 'pointer_pointer', 'incomplete', ''):
        return 'untyped_record', '%s_%s' % (kind or 'unknown', decl or 'expr')
    return 'other', sub or 'unclassified'


def function_bodies(root, rel, cache):
    if rel in cache:
        return cache[rel]
    sys.path.insert(0, str(root / 'tools/readability'))
    import score as S
    text = (root / rel).read_text(errors='replace')
    tokens = S.lex(text)
    pairs, _ = S.pairs_of(tokens)
    bodies, seen = {}, Counter()
    for a, n, b, e, style in S.definitions(tokens, pairs):
        fn = tokens[n].value
        seen[fn] += 1
        bodies[(fn, seen[fn])] = text[tokens[a].pos:tokens[e].pos + 1]
    cache[rel] = bodies
    return bodies


SCALAR_TYPES = {'void', 'u8', 's8', 'char', 'unsigned char', 'signed char', 'u16', 's16', 'short', 'u32', 's32',
                'int', 'unsigned int', 'unsigned short', 'long', 'unsigned long'}


def alias_source(body, name):
    """(source expression, shape) of the first value an untyped local takes (declaration initialiser or
    assignment), casts stripped.  shape: param / global / member / load / node_body / arith / call / other.
    A local that only aliases a typed source should take that type (the casts at its uses then fold)."""
    if not name or not re.fullmatch(IDENT, name):
        return '', ''
    n = re.escape(name)
    m = re.search(r'(?<![\w.>])' + n + r'\s*=(?!=)\s*([^;]*);', body)
    if not m:
        return '', ''
    src = m[1].strip()
    for _ in range(4):
        src = re.sub(r'^\(\s*(?:(?:const|volatile|struct|unsigned|signed)\s+)*\w+(?:\s+\w+)*\s*\*+\s*\)\s*', '', src).strip()
        if src.startswith('(') and src.endswith(')') and src.count('(') == 1:
            src = src[1:-1].strip()
    sig = body.split('{', 1)[0]
    if re.match(r'NODE_BODY\s*\(', src):
        shape = 'node_body'
    elif src.startswith('*'):
        shape = 'load'
    elif re.fullmatch(IDENT, src):
        declared = re.search(r'[\w*\s]\b' + re.escape(src) + r'\s*[,)]', sig)
        local = re.search(r'\b\w[\w\s]*\**\s*\b' + re.escape(src) + r'\s*[;=,\[]', body.split('{', 1)[-1])
        shape = 'param' if declared else ('local' if local else 'global')
    elif re.fullmatch(IDENT + r'(?:(?:->|\.)' + IDENT + r'|\[[^\]]*\])+', src) or src.startswith('&'):
        shape = 'member'
    elif re.match(IDENT + r'\s*\(', src):
        shape = 'call'
    elif re.search(r'[+\-]', src):
        shape = 'arith'
    else:
        shape = 'other'
    return src[:60], shape


def record_index(db):
    """{(off, size): {record}} over leaf members, and {record: (size, generated)}."""
    from census import GENERATED
    index, info = defaultdict(set), {}
    for rec, size in db.execute('SELECT record, size FROM record_layout'):
        if rec.startswith('@'):
            continue
        info[rec] = (size or 0, bool(GENERATED.search(rec)))
    for rec, off, size in db.execute('SELECT DISTINCT record, off, size FROM record_member'):
        if rec in info:
            index[(off, size)].add(rec)
    return index, info


def candidates(accesses, index, info, limit=3):
    """Existing records whose members start at every accessed (offset, width), named records first.

    Fewer than three distinct accesses match too many unrelated layouts to be evidence: no candidate."""
    sets = [index.get(a, set()) for a in accesses if a[0] is not None and a[0] >= 0 and a[1]]
    if len(sets) < 3:
        return []
    common = set.intersection(*sets) if len(sets) > 1 else set(sets[0])
    top = max(a[0] for a in accesses if a[0] is not None)
    common = [r for r in common if info[r][0] > top]
    named = [r for r in common if not info[r][1]]
    pool = named or common
    if len(pool) > 8:
        return ['ambiguous:%d' % len(pool)]
    return sorted(pool, key=lambda r: (info[r][1], info[r][0], r))[:limit]


def write_tsv(path, fields, rows):
    opener = gzip.open if str(path).endswith('.gz') else open
    with opener(path, 'wt', newline='') as fh:
        w = csv.DictWriter(fh, fields, delimiter='\t', lineterminator='\n', extrasaction='ignore')
        w.writeheader()
        for r in rows:
            w.writerow({k: str(v).replace('\t', ' ').replace('\n', ' ') for k, v in r.items()})


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=Path('.'))
    ap.add_argument('--census', type=Path, required=True, help='census.py output directory')
    ap.add_argument('--out', type=Path, required=True)
    args = ap.parse_args(argv)
    root = args.root.resolve()
    sys.path.insert(0, str(HERE))
    rows = [r for r in csv.DictReader(gzip.open(args.census / 'census.tsv.gz', 'rt'), delimiter='\t')
            if r['category'] == 'byte_cursor']
    db = sqlite3.connect('file:%s?mode=ro' % (root / 'build/codemap.db'), uri=True)
    cm = {}
    for file, start, raw in db.execute('SELECT file, start, row FROM cast_site'):
        cm.setdefault((file, start), json.loads(raw))
    index, info = record_index(db)
    cache, groups = {}, defaultdict(list)
    for r in rows:
        c = cm.get((r['file'], int(r['start'])))
        r['_base'] = base_name(r, c)
        bodies = function_bodies(root, r['file'], cache)
        body = bodies.get((r['function'], int(r['occurrence'] or 1)), '') if r['function'] != '<global>' else ''
        root_var = r['_base'].split('->')[0].split('.')[0]
        adv, step = advancement(body, root_var) if root_var and '->' not in r['_base'] and '.' not in r['_base'] \
            else advancement(body, r['_base'])
        r['bc_class'], r['bc_sub'] = classify(r, c, adv, step)
        r['alias_of'] = ''
        if r['bc_class'] == 'untyped_record' and 'local' in r['bc_sub']:
            src, shape = alias_source(body, root_var)
            if src:
                # where an untyped local gets its value: the type of that source is the local's type
                r['bc_sub'] = 'local_from_' + shape
                r['alias_of'] = src
        r['bc_route'] = ROUTES[r['bc_class']]
        r['domain'] = domain_of(r['file'], r['function'])
        r['base'] = r['_base']
        r['base_kind'] = (c or {}).get('base_kind', '')
        r['base_decl'] = (c or {}).get('base_decl', '')
        r['width'] = (c or {}).get('width', '')
        r['advance'] = adv + ('' if step in (None,) else ':%s' % step)
        groups[(r['file'], r['function'], r['_base'])].append(r)
    group_rows = []
    for (file, function, base), members in groups.items():
        cls = Counter(m['bc_class'] for m in members).most_common(1)[0][0]
        acc = sorted({(int(m['chain_offset']) if m['chain_offset'] not in ('', None) and m['variable_offset'] != 'True' else None,
                       int(m['width']) if str(m['width']).isdigit() else 0) for m in members}, key=repr)
        cand = candidates(acc, index, info) if cls == 'untyped_record' else []
        widths = {w for o, w in acc if w}
        offs = [o for o, w in acc if o is not None]
        shape = ''
        if cls == 'untyped_record' and len(widths) == 1 and len(offs) >= 2 and \
                all(o % next(iter(widths)) == 0 for o in offs):
            shape = 'uniform_%d' % next(iter(widths))       # one element type: an array view, not a record
        elif cls == 'untyped_record':
            shape = 'record'

        group_rows.append(dict(file=file, function=function, base=base, casts=len(members), bc_class=cls, shape=shape,
                               subs=','.join(sorted({m['bc_sub'] for m in members}))[:120],
                               domain=members[0]['domain'], base_types=','.join(sorted({m['chain_base_type'] for m in members}))[:80],
                               accesses=' '.join('%s/%s' % a for a in acc)[:200], candidates=','.join(cand),
                               alias_of=members[0].get('alias_of', ''),
                               folder=members[0]['folder']))
    out = args.out
    out.mkdir(parents=True, exist_ok=True)
    (out / '.ignore').write_text('*\n')
    fields = ['site_id', 'file', 'function', 'line', 'cast_text', 'from_type', 'to_type', 'chain_base_type',
              'chain_offset', 'variable_offset', 'base', 'base_kind', 'base_decl', 'width', 'advance', 'ast_sub',
              'bc_class', 'bc_sub', 'bc_route', 'alias_of', 'domain', 'folder', 'subsystem']
    write_tsv(out / 'byte_cursor_sites.tsv.gz', fields, rows)
    group_rows.sort(key=lambda g: (-g['casts'], g['file'], g['function']))
    write_tsv(out / 'groups.tsv', ['file', 'function', 'base', 'casts', 'bc_class', 'shape', 'subs', 'domain', 'base_types',
                                   'accesses', 'candidates', 'alias_of', 'folder'], group_rows)
    for cls in CLASSES:
        write_tsv(out / ('worklist_%s.tsv' % cls), ['file', 'function', 'base', 'casts', 'shape', 'subs', 'domain',
                                                    'base_types', 'accesses', 'candidates', 'alias_of', 'folder'],
                  [g for g in group_rows if g['bc_class'] == cls])
    by_class = Counter(r['bc_class'] for r in rows)
    by_sub = Counter((r['bc_class'], r['bc_sub']) for r in rows)
    by_folder = defaultdict(Counter)
    for r in rows:
        by_folder[r['bc_class']][r['folder']] += 1
    by_domain = defaultdict(Counter)
    for r in rows:
        by_domain[r['bc_class']][r['domain'] or '-'] += 1
    fn_counts = defaultdict(Counter)
    for r in rows:
        fn_counts[r['bc_class']][(r['file'], r['function'])] += 1
    top = []
    for cls in CLASSES:
        for rank, ((file, fn), n) in enumerate(fn_counts[cls].most_common(25), 1):
            top.append(dict(bc_class=cls, rank=rank, file=file, function=fn, casts=n))
    write_tsv(out / 'top_functions.tsv', ['bc_class', 'rank', 'file', 'function', 'casts'], top)
    untyped = [g for g in group_rows if g['bc_class'] == 'untyped_record']
    summary = dict(byte_cursor=len(rows), by_class={c: by_class.get(c, 0) for c in CLASSES},
                   by_sub={'%s:%s' % k: n for k, n in by_sub.most_common(60)},
                   by_folder={c: dict(by_folder[c].most_common(15)) for c in CLASSES},
                   by_domain={c: dict(by_domain[c].most_common()) for c in CLASSES},
                   groups=len(group_rows),
                   untyped_groups_with_candidate=sum(1 for g in untyped if g['candidates'] and not g['candidates'].startswith('ambiguous')),
                   untyped_casts_with_candidate=sum(g['casts'] for g in untyped if g['candidates'] and not g['candidates'].startswith('ambiguous')),
                   untyped_casts_by_shape=dict(Counter(g['shape'] for g in untyped for _ in range(g['casts']))),
                   untyped_casts_by_base_decl=dict(Counter(
                       (r['base_decl'] or '').split(':')[0] for r in rows if r['bc_class'] == 'untyped_record')),
                   census_revision=json.loads((args.census / 'totals.json').read_text()).get('base_revision'))
    (out / 'summary.json').write_text(json.dumps(summary, indent=1) + '\n')
    print(json.dumps({k: summary[k] for k in ('byte_cursor', 'by_class', 'groups', 'untyped_groups_with_candidate',
                                              'untyped_casts_with_candidate', 'untyped_casts_by_shape',
                                              'untyped_casts_by_base_decl')}, indent=1))
    return 0


if __name__ == '__main__':
    sys.exit(main())
