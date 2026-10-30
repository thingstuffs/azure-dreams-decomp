#!/usr/bin/env python3
"""Generated-layout family census: which S_<addr> views are views of one real object, and what consolidating
each family would remove.

    layout_census.py inventory --out DIR                          lexical inventory (no compiler, ~20 s)
    layout_census.py assign    --out DIR --field-census FC        candidate family file for layout_swap plan
    layout_census.py report    --out DIR --field-census FC --plan PLAN [--field-casts FCC]
                               [--hold PREFIX ...]                 layouts_census.tsv + census.json

Inputs are the existing read-only censuses:
  inventory     every GENERATED name (tools/lint/debt_check) with its typedef(s), parsed fields, provenance
                comment and per-scope uses (cast / declarator / other).  `gen` counts scopes exactly as
                debt_check's generated_layouts does, so family sums add up to the debt total.
  field census  tools/typing/field_census.py sites.jsonl.gz: flow-based base identity per access site
                (label = shared type, derived pointee, or a view-only identity) and the site offset, from which
                each view's delta to its identity is computed.  Labels are a hypothesis (the analysis is
                flow-insensitive: one variable reused for two objects merges them).
  plan          layout_swap.py plan decisions.jsonl over the `assign` file: per view, whether every use maps onto
                the shared type exactly (accepted) and its identity evidence (anchored = a typed value flows into
                the view; shape = layout fit only).
  field casts   tools/typing/field_cast_census.py field_casts.tsv: casts on untyped members of shared structs
                (`(T *)root->position`), removable by retyping the member.

Family kinds in the report (one row each, ranked by removed debt per unit of work):
  type:<T>          views labelled with shared type T at delta 0; ready = accepted by the swap planner
  field:<R>.<f>     retype member f of R to the dominant cast target; removes those casts
  derived:<label>   views of a pointee reached through a shared type's untyped member (needs the member typed)
  new:<label>       view-only identities with >= 2 views: a proposed new shared type in the users' folder header
  singletons:<dir>  one-view identities, grouped by folder: need callback/allocator identity before consolidation
`--hold` marks rows whose files lie under the given prefixes (other lanes' areas) as held.
"""
from __future__ import annotations

import argparse
import collections
import gzip
import json
from pathlib import Path
import re
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
GENERATED = re.compile(r'^S_(?:func_)?[0-9A-Fa-f]{8}(?:_\w+)?$')
TYPEDEF = re.compile(r'typedef\s+(struct|union)\s+(S_\w+)?\s*\{', re.M)
WIDTH = {'s8': 1, 'u8': 1, 'char': 1, 's16': 2, 'u16': 2, 'short': 2, 's32': 4, 'u32': 4,
         'int': 4, 'long': 4, 'unsigned': 4, 'float': 4}


# ---------------------------------------------------------------------------------------------- inventory

def _match_brace(text, i):
    depth, j = 0, i
    while j < len(text):
        c = text[j]
        if c == '/' and text.startswith('/*', j):
            j = text.find('*/', j) + 2
            continue
        if c == '{':
            depth += 1
        elif c == '}':
            depth -= 1
            if depth == 0:
                return j
        j += 1
    return -1


def _fields(body):
    body = re.sub(r'/\*.*?\*/|//[^\n]*', ' ', body, flags=re.S)
    members, depth, cur = [], 0, ''
    for c in body:
        depth += {'{': 1, '}': -1}.get(c, 0)
        if c == ';' and depth == 0:
            members.append(' '.join(cur.split()))
            cur = ''
        else:
            cur += c
    out, off = [], 0
    for m in filter(None, members):
        arr = re.search(r'\[\s*(0x[0-9A-Fa-f]+|\d+)\s*\]\s*$', m)
        count = int(arr[1], 0) if arr else 1
        core = m[:arr.start()] if arr else m
        name = (re.search(r'(\w+)\s*$', core) or [None, ''])[1]
        ty = core[:len(core) - len(name)].strip()
        width = 4 if '*' in ty or '(*' in core else WIDTH.get(ty.split()[-1] if ty else '', None)
        mo = re.match(r'(?:pad|unk|field|f)_?([0-9A-Fa-f]+)$', name)
        if mo:
            off = int(mo[1], 16)
        if name.startswith('pad'):
            off += count * (width or 1)
            continue
        out.append({'o': off, 't': ty or core.split('{')[0].strip(), 'n': name, 'w': width, 'c': count})
        if width:
            off += width * count
    return out


def inventory(root):
    sys.path.insert(0, str(root / 'tools' / 'readability'))
    import score as c
    defs, uses = {}, collections.defaultdict(lambda: collections.defaultdict(collections.Counter))
    files = sorted((root / 'src').rglob('*.c')) + sorted((root / 'include').rglob('*.h'))
    for path in files:
        if path.is_symlink() or path.stat().st_size > 4 * 1024 * 1024:
            continue
        rel = path.relative_to(root).as_posix()
        text = path.read_text(errors='replace')
        if 'S_' not in text:
            continue
        for m in TYPEDEF.finditer(text):
            close = _match_brace(text, text.find('{', m.start()))
            if close < 0:
                continue
            tail = re.match(r'\s*(\w+)\s*;([ \t]*/\*(.*?)\*/)?', text[close + 1:close + 400], re.S)
            name = tail[1] if tail else m[2]
            if not name or not GENERATED.fullmatch(name):
                continue
            fields = _fields(text[text.find('{', m.start()) + 1:close])
            defs.setdefault(name, []).append({
                'file': rel, 'line': text.count('\n', 0, m.start()) + 1,
                'comment': (tail[3].strip() if tail and tail[3] else ''), 'fields': fields,
                'extent': max([f['o'] + (f['w'] or 1) * f['c'] for f in fields] + [0])})
        if not rel.startswith('src/'):
            continue
        tokens = c.lex(text)
        pairs, _ = c.pairs_of(tokens)
        owners = ['<global>'] * len(tokens)
        for start, name_i, body_i, end, style in c.definitions(tokens, pairs):
            owners[start:end + 1] = [tokens[name_i].value] * (end + 1 - start)
        for i, t in enumerate(tokens):
            if t.kind != 'id' or not GENERATED.fullmatch(t.value):
                continue
            prev = tokens[i - 1].value if i else ''
            nxt = tokens[i + 1].value if i + 1 < len(tokens) else ''
            nxt2 = tokens[i + 2].value if i + 2 < len(tokens) else ''
            if prev == '(' and nxt == '*' and nxt2 == ')' or prev in ('(', 'const') and nxt == '*' and nxt2 in (')', '*'):
                kind = 'cast'
            elif nxt == '*' or (i + 1 < len(tokens) and tokens[i + 1].kind == 'id'):
                kind = 'decl'
            else:
                kind = 'other'
            uses[t.value][(rel, owners[i])][kind] += 1
    # Attribute each use to the definition it sees: the file's own typedef, else the single header typedef.
    views = {}
    for name in sorted(set(defs) | set(uses)):
        dlist = defs.get(name, [])
        here = {d['file']: d for d in dlist}
        headers = [d['file'] for d in dlist if d['file'].startswith('include/')]
        for d in dlist:
            views[d['file'] + ':' + name] = dict(d, name=name, uses=[])
        for (f, fn), cnt in uses.get(name, {}).items():
            key = f + ':' + name if f in here else (headers[0] + ':' + name if len(headers) == 1 else
                                                    '<unresolved>:' + name)
            views.setdefault(key, {'name': name, 'file': key.rsplit(':', 1)[0], 'fields': [], 'uses': [],
                                   'comment': '', 'extent': 0})
            views[key]['uses'].append(dict(file=f, fn=fn, **cnt))
    for v in views.values():
        v['gen'] = len(v['uses'])
        v['casts'] = sum(u.get('cast', 0) for u in v['uses'])
    return views


# ---------------------------------------------------------------------------------------------- field census join

def labels(field_census, views):
    """{view key: {'family', 'typed', 'sites', 'delta'}} from field_census sites (majority label per view)."""
    lab = collections.defaultdict(collections.Counter)
    delta = collections.defaultdict(collections.Counter)
    with gzip.open(field_census / 'sites.jsonl.gz', 'rt') as fh:
        for line in fh:
            s = json.loads(line)
            decl = s.get('decl') or ''
            if not GENERATED.match(decl.split(':')[-1]):
                continue
            label = s.get('label') or '<none>'
            lab[decl][(label, s.get('typed'))] += 1
            m = re.match(r'(?:unk|field|f)_?([0-9A-Fa-f]+)', (s.get('field') or '').split('.')[0].split('[')[0])
            if s.get('off') is not None and m:
                delta[(decl, label)][s['off'] - int(m[1], 16)] += 1
    out = {}
    for decl, c in lab.items():
        (label, typed), n = c.most_common(1)[0]
        d = delta.get((decl, label))
        out[decl] = {'family': label, 'typed': typed, 'sites': n,
                     'delta': d.most_common(1)[0][0] if d else None, 'share': round(n / sum(c.values()), 2)}
    return out


DERIVED = {'ObjectNodeHeader->[0x8]': 'ObjectPosition', 'ObjectNodeHeader->[0xc]': 'SpriteFrameState'}


def type_headers(root):
    out = {}
    for p in sorted((root / 'include').rglob('*.h')):
        for m in re.finditer(r'\}\s*([A-Z]\w*)\s*;', p.read_text(errors='replace')):
            out.setdefault(m[1], p.relative_to(root / 'include').as_posix())
    return out


def assign(root, lab):
    """layout_swap family file: every view labelled with a shared type (or a known pointee) at delta 0."""
    headers = type_headers(root)
    groups = collections.defaultdict(list)
    for spec, v in lab.items():
        t = v['family'] if v['typed'] == 'strong' else DERIVED.get(v['family'])
        if t and v['delta'] == 0 and t in headers and not spec.startswith('@'):
            groups[t].append(spec)
    return {'groups': [{'type': t, 'header': headers[t], 'views': sorted(vs)} for t, vs in sorted(groups.items())]}


# ---------------------------------------------------------------------------------------------- report

def folder_of(files):
    """Common folder header for a set of users: include/<top>/<sub>.h by majority."""
    c = collections.Counter('/'.join(f.split('/')[1:3]) for f in files if f.startswith('src/'))
    if not c:
        return ''
    top = c.most_common(1)[0][0]
    return 'include/%s.h' % top if '.' not in top else 'include/%s.h' % top.split('/')[0]


def report(root, views, lab, plan, field_casts, hold):
    decisions = {}
    if plan:
        for line in open(plan):
            d = json.loads(line)
            decisions[d['view']] = d
    held = lambda files: any(f.startswith(tuple(hold)) for f in files) if hold else False
    rows = collections.defaultdict(lambda: dict(views=0, ready=0, gen=0, gen_ready=0, casts=0, casts_anchor=0,
                                                files=set(), held_views=0, reasons=collections.Counter(),
                                                evidence=collections.Counter(), header='', type=''))
    headers = type_headers(root)
    for key, v in views.items():
        files = {u['file'] for u in v['uses']} | {v['file']}
        info = lab.get(key)
        d = decisions.get(key)
        if d:
            kind, t = 'type', d['type']
            row = rows['type:' + t]
            row['type'], row['header'] = t, 'include/' + headers.get(t, '?')
        elif info and info['typed'] == 'strong':
            t = info['family']
            row = rows['type:%s@delta%s' % (t, info['delta'])]
            row['type'], row['header'] = t, 'include/' + headers.get(t, '?')
        elif info and info['typed'] == 'derived':
            row = rows['derived:' + info['family']]
        elif info and info['typed'] == 'view_only':
            row = rows['viewonly:' + info['family']]
        else:
            row = rows['singletons:' + '/'.join(v['file'].split('/')[:3])]
        row['views'] += 1
        row['gen'] += v['gen']
        row['casts'] += v['casts']
        row['files'] |= files
        if held(files):
            row['held_views'] += 1
        if d:
            row['reasons'][(d['reason'] or 'accepted').split('@')[0]] += 1
            if d['accepted']:
                row['ready'] += 1
                row['gen_ready'] += v['gen']
                row['evidence'][d.get('evidence', '?')] += 1
                row['casts_anchor'] += sum(1 for u in d['uses'] if u.get('kind') == 'anchor')
    # View-only identities with one view are singletons of their folder; >= 2 views propose a new type.
    final = {}
    for name, row in rows.items():
        if name.startswith('viewonly:'):
            if row['views'] >= 2:
                row['header'] = folder_of(row['files'])
                final['new:' + name[len('viewonly:'):]] = row
                continue
            folder = '/'.join(sorted(row['files'])[0].split('/')[:3])
            target = final.setdefault('singletons:' + folder, rows.get('singletons:' + folder) or dict(
                views=0, ready=0, gen=0, gen_ready=0, casts=0, casts_anchor=0, files=set(), held_views=0,
                reasons=collections.Counter(), evidence=collections.Counter(), header='', type=''))
            for k in ('views', 'gen', 'casts', 'held_views'):
                target[k] += row[k]
            target['files'] |= row['files']
            continue
        final.setdefault(name, row)
    out = []
    for name, row in final.items():
        work = len(row['files']) + (5 if row['header'] else 0)
        removable = row['gen_ready'] + row['casts_anchor']
        out.append(dict(family=name, kind=name.split(':')[0], type=row['type'], header=row['header'],
                        views=row['views'], ready=row['ready'], held_views=row['held_views'],
                        generated_sites=row['gen'], generated_ready=row['gen_ready'], casts_to_views=row['casts'],
                        casts_removable_now=row['casts_anchor'], files=len(row['files']),
                        score=round(removable / max(1, work), 3),
                        status=('held' if row['held_views'] == row['views'] and row['views'] else
                                'mixed' if row['held_views'] else 'open'),
                        evidence=dict(row['evidence']), reasons=dict(row['reasons'].most_common(6))))
    if field_casts:
        users = collections.defaultdict(set)
        sites = Path(field_casts).with_name('sites.jsonl')
        if sites.is_file():
            for line in open(sites):
                x = json.loads(line)
                users[(x['record'], x['member'])].add(x['file'])
        for line in list(open(field_casts))[1:]:
            rec, mem, mtype, header, target, casts, nfiles, allc, others = (line.rstrip('\n').split('\t') + [''])[:9]
            casts = int(casts)
            out.append(dict(family='field:%s.%s' % (rec, mem), kind='field', type=target, header=header,
                            views=0, ready=0, held_views=0, generated_sites=0, generated_ready=0,
                            casts_to_views=int(allc), casts_removable_now=casts if not others else casts,
                            files=int(nfiles), score=round(casts / (int(nfiles) + 5), 3),
                            status=('held' if held([header]) or (users[(rec, mem)] and all(
                                held([f]) for f in users[(rec, mem)])) else
                                    'mixed' if held(users[(rec, mem)]) else 'open'), evidence={},
                            reasons={'other_targets': others} if others else {}))
    out.sort(key=lambda r: (-r['score'], -r['generated_sites']))
    return out


COLUMNS = ['rank', 'family', 'kind', 'type', 'header', 'status', 'views', 'ready', 'held_views', 'generated_sites',
           'generated_ready', 'casts_to_views', 'casts_removable_now', 'files', 'score', 'evidence', 'reasons']


def write_tsv(path, rows):
    with open(path, 'w') as fh:
        fh.write('\t'.join(COLUMNS) + '\n')
        for i, r in enumerate(rows, 1):
            r = dict(r, rank=i)
            fh.write('\t'.join(json.dumps(r[c], sort_keys=True) if isinstance(r[c], dict) else str(r[c])
                               for c in COLUMNS) + '\n')


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('mode', choices=('inventory', 'assign', 'report'))
    ap.add_argument('--root', type=Path, default=ROOT)
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--field-census', type=Path)
    ap.add_argument('--plan', type=Path, help='layout_swap plan decisions.jsonl')
    ap.add_argument('--field-casts', type=Path, help='field_cast_census field_casts.tsv')
    ap.add_argument('--hold', nargs='*', default=[])
    args = ap.parse_args(argv)
    root = args.root.resolve()
    args.out.mkdir(parents=True, exist_ok=True)
    inv = args.out / 'inventory.json'
    if args.mode == 'inventory' or not inv.exists():
        views = inventory(root)
        inv.write_text(json.dumps(views, sort_keys=True))
        print(json.dumps({'views': len(views), 'generated_layouts': sum(v['gen'] for v in views.values()),
                          'casts_to_views': sum(v['casts'] for v in views.values())}))
        if args.mode == 'inventory':
            return 0
    views = json.loads(inv.read_text())
    lab = labels(args.field_census, views)
    if args.mode == 'assign':
        fam = assign(root, lab)
        (args.out / 'assign.json').write_text(json.dumps(fam, indent=1) + '\n')
        print(json.dumps({'types': len(fam['groups']), 'views': sum(len(g['views']) for g in fam['groups'])}))
        return 0
    rows = report(root, views, lab, args.plan, args.field_casts, args.hold)
    write_tsv(args.out / 'layouts_census.tsv', rows)
    totals = collections.Counter()
    for r in rows:
        totals[r['kind'] + ':generated'] += r['generated_sites']
        totals[r['kind'] + ':ready'] += r['generated_ready']
    (args.out / 'census.json').write_text(json.dumps({'rows': len(rows), 'totals': dict(totals)}, indent=2) + '\n')
    print(json.dumps(dict(totals)))
    return 0


if __name__ == '__main__':
    sys.exit(main())
