#!/usr/bin/env python3
"""Classify every local_externs debt site (tools/lint/debt_check.py) from the code map's declaration facts.

    extern_classes.py [--root R] [--db build/codemap.db] --out DIR [--scope src/x ...]

One row per debt site (a declaration statement; a statement with several declarators takes the class of
its least removable declarator).  Facts come from build/codemap.db (`decl`, `defn`, `tu.headers`), so the
census is seconds, not a re-parse; run `codemap.py refresh` first (the tool refuses a stale map for the
files it reads).

Function classes (`fn.*`), in removal order:
  fn.dup_visible_same        a header in the TU's include closure declares the same prototype (typedefs
                             expanded): deleting the local declaration is a no-op for the compiler
  fn.dup_visible_unproto     the local declaration is an empty `f()` and a visible header prototype has the
                             same return type: the composite type is already the header prototype
  fn.dup_visible_differs     a visible header declares it differently (signature solver: floors/width)
  fn.header_elsewhere_same   a header outside the TU's closure declares the same prototype (include it)
  fn.header_elsewhere_differs
  fn.no_header_consistent    no header declares it; every .c declaration and the C definition agree
                             (publish in the owning header, include, delete)
  fn.no_header_disagree      no header declares it; spellings disagree (solver)
  fn.no_header_unproto       no header declares it and this site is an empty `f()` (solver: arity)
  fn.no_c_def_sdk            no C definition; an include/sdk stand-in declares it
  fn.no_c_def                no C definition (asm / retail-only / linker symbol)
Data classes (`data.*`): the same visibility split (dup_visible_same / dup_visible_differs /
header_elsewhere_* / no_header_consistent / no_header_disagree), each prefixed with `D_` or `named`
(the symbol is a raw D_<addr> name or a named global).
`unmodelled.*`: no code-map declarator at the site (block-scope declarations, unparsed TUs).

Writes sites.tsv, by_class.tsv, by_folder.tsv (class columns), summary.json.
"""
from __future__ import annotations

import argparse
import bisect
import json
import re
import sqlite3
import sys
from collections import Counter, defaultdict
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE.parent / 'lint'), str(HERE.parent / 'readability')]

DSYM = re.compile(r'^D_[0-9A-Fa-f]{8}\b')
# Ranking: lower = more removable.  A multi-declarator statement takes its highest-ranked class.
ORDER = ('dup_visible_same', 'dup_visible_unproto', 'header_elsewhere_same', 'no_header_consistent',
         'dup_visible_differs', 'header_elsewhere_differs', 'no_header_disagree', 'no_header_unproto',
         'no_c_def_sdk', 'no_c_def')
MECHANICAL = {'fn.dup_visible_same', 'fn.dup_visible_unproto', 'data.D_.dup_visible_same',
              'data.named.dup_visible_same'}


def debt_sites(root, rel):
    """[(start line, end line, in_function)] of the debt checker's local_externs sites in one file."""
    import debt_check as D
    c = D.c
    text = (Path(root) / rel).read_text()
    tokens = c.lex(text)
    pairs, _ = c.pairs_of(tokens)
    definitions = list(c.definitions(tokens, pairs))
    spans, _ = D.exemptions(text, tokens, pairs)
    excluded = set()
    for a, b in spans:
        excluded.update(range(a, b))
    bodies = sorted((tokens[body].pos, tokens[end].pos) for start, name, body, end, style in definitions)
    nl = [i for i, ch in enumerate(text) if ch == '\n']
    line = lambda pos: bisect.bisect_right(nl, pos - 1) + 1
    out = []
    for i in D.declaration_sites(tokens, pairs, definitions):
        if i in excluded:
            continue
        j = i
        while j < len(tokens) and tokens[j].value != ';':
            if tokens[j].value in ('(', '[', '{') and j in pairs:
                j = pairs[j]
            j += 1
        pos = tokens[i].pos
        out.append((line(pos), line(tokens[min(j, len(tokens) - 1)].pos),
                    any(a <= pos <= b for a, b in bodies)))
    return out


class Facts:
    def __init__(self, db):
        self.db = db
        self.headers_of = {}
        self.hdecl = defaultdict(list)        # name -> [(file, kind, canon_norm, has_proto, ret)]
        for name, kind, file, cn, hp, ret in db.execute(
                "SELECT name, kind, file, canon_norm, has_proto, ret FROM decl WHERE file LIKE 'include/%' "
                "AND kind IN ('proto', 'data') AND storage != 'static'"):
            self.hdecl[name].append((file, kind, cn, hp, ret))
        self.cdecl = defaultdict(list)        # name -> [(file, kind, canon_norm, has_proto)]
        for name, kind, file, cn, hp in db.execute(
                "SELECT name, kind, file, canon_norm, has_proto FROM decl WHERE file NOT LIKE 'include/%' "
                "AND kind IN ('proto', 'data') AND storage != 'static'"):
            self.cdecl[name].append((file, kind, cn, hp))
        self.defs = defaultdict(set)
        for name, cn in db.execute('SELECT name, canon_norm FROM defn'):
            self.defs[name].add(cn)
        for path, headers in db.execute('SELECT path, headers FROM tu'):
            self.headers_of[path] = set(json.loads(headers or '[]'))

    def site_decls(self, rel, a, b):
        return self.db.execute("SELECT name, kind, canon_norm, has_proto, ret, line FROM decl WHERE file=? AND "
                               "line BETWEEN ? AND ? AND kind IN ('proto', 'data') AND storage != 'static'",
                               (rel, a, b)).fetchall()


def ret_of(cn):
    i = cn.find('(')
    return cn[:i] if i > 0 else cn


def classify_decl(f, rel, name, kind, cn, hp):
    vis = f.headers_of.get(rel, set())
    hs = [h for h in f.hdecl.get(name, ()) if h[1] == kind]
    visible = [h for h in hs if h[0] in vis]
    if kind == 'proto':
        if not f.defs.get(name):
            return 'fn.no_c_def_sdk' if any(h[0].startswith('include/sdk/') for h in hs) else 'fn.no_c_def'
        if visible:
            if any(h[2] == cn and h[3] for h in visible) or (hp and any(h[2] == cn for h in visible)):
                return 'fn.dup_visible_same'
            if not hp and any(h[3] and ret_of(h[2]) == ret_of(cn) for h in visible):
                return 'fn.dup_visible_unproto'
            return 'fn.dup_visible_differs'
        if hs:
            return 'fn.header_elsewhere_same' if any(h[2] == cn for h in hs) else 'fn.header_elsewhere_differs'
        if not hp:
            return 'fn.no_header_unproto'
        spell = {d[2] for d in f.cdecl.get(name, ()) if d[1] == 'proto'} | f.defs[name] | {cn}
        return 'fn.no_header_consistent' if len(spell) == 1 else 'fn.no_header_disagree'
    pre = 'data.D_.' if DSYM.match(name) else 'data.named.'
    if visible:
        return pre + ('dup_visible_same' if any(h[2] == cn for h in visible) else 'dup_visible_differs')
    if hs:
        return pre + ('header_elsewhere_same' if any(h[2] == cn for h in hs) else 'header_elsewhere_differs')
    spell = {d[2] for d in f.cdecl.get(name, ()) if d[1] == 'data'} | {cn}
    return pre + ('no_header_consistent' if len(spell) == 1 else 'no_header_disagree')


def rank(cls):
    tail = cls.rsplit('.', 1)[-1]
    return ORDER.index(tail) if tail in ORDER else len(ORDER)


def census(root, db_path, scope):
    db = sqlite3.connect('file:%s?mode=ro' % db_path, uri=True)
    f = Facts(db)
    files = sorted(p.relative_to(root).as_posix() for s in scope for p in (root / s).rglob('*.c'))
    rows = []
    for rel in files:
        for a, b, inside in debt_sites(root, rel):
            ds = f.site_decls(rel, a, b)
            if not ds:
                rows.append((rel, a, '', 'unmodelled.' + ('block_scope' if inside else 'no_decl_row')))
                continue
            classes = [classify_decl(f, rel, n, k, cn, hp) for n, k, cn, hp, ret, line in ds]
            cls = max(classes, key=rank)
            if inside:
                cls = 'block.' + cls
            rows.append((rel, a, ','.join(sorted({d[0] for d in ds})), cls))
    return rows


def folder_of(rel, depth):
    return '/'.join(rel.split('/')[:-1][:depth])


def write(out, rows, depth=3):
    out.mkdir(parents=True, exist_ok=True)
    with open(out / 'sites.tsv', 'w') as fh:
        fh.write('path\tline\tnames\tclass\n')
        for r in rows:
            fh.write('\t'.join(map(str, r)) + '\n')
    by = Counter(r[3] for r in rows)
    with open(out / 'by_class.tsv', 'w') as fh:
        fh.write('class\tsites\tmechanical\n')
        for k, n in sorted(by.items(), key=lambda kv: -kv[1]):
            fh.write('%s\t%d\t%s\n' % (k, n, 'yes' if k in MECHANICAL else ''))
    cols = sorted(by, key=lambda k: -by[k])
    per = defaultdict(Counter)
    for r in rows:
        per[folder_of(r[0], depth)][r[3]] += 1
    with open(out / 'by_folder.tsv', 'w') as fh:
        fh.write('folder\tsites\tmechanical\t' + '\t'.join(cols) + '\n')
        for fo in sorted(per, key=lambda x: -sum(per[x].values())):
            c = per[fo]
            fh.write('%s\t%d\t%d\t%s\n' % (fo, sum(c.values()), sum(c[k] for k in MECHANICAL),
                                         '\t'.join(str(c[k]) for k in cols)))
    summary = dict(sites=len(rows), mechanical=sum(by[k] for k in MECHANICAL),
                   functions=sum(n for k, n in by.items() if '.fn.' in '.' + k),
                   data=sum(n for k, n in by.items() if 'data.' in k),
                   classes=dict(by.most_common()))
    (out / 'summary.json').write_text(json.dumps(summary, indent=1) + '\n')
    return summary


def fuse(out, rows, plan_sites):
    """Join with tools/headers/census.py sites.tsv (the header planner's outcome per site): the planner's
    planned_remove is the mechanical set; the code-map class says what the held sites are."""
    import csv
    plan = {}
    for r in csv.DictReader(open(plan_sites), delimiter='\t'):
        o = r['outcome']
        plan[(r['path'], r['line'])] = ':'.join(o.split(':')[:4]) if o.startswith('keep:') else o.split(':')[0]
    cross = Counter()
    for path, line, names, cls in rows:
        cross[(cls, plan.get((path, str(line)), 'unjoined'))] += 1
    with open(out / 'fused.tsv', 'w') as fh:
        fh.write('class\tplanner_outcome\tsites\n')
        for (cls, o), n in sorted(cross.items(), key=lambda kv: (kv[0][0], -kv[1])):
            fh.write('%s\t%s\t%d\n' % (cls, o, n))
    planned = Counter(cls for (cls, o), n in cross.items() for _ in range(n) if o == 'planned_remove')
    return dict(planned_remove=sum(planned.values()), planned_by_class=dict(planned.most_common()))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=HERE.parents[1])
    ap.add_argument('--db', type=Path)
    ap.add_argument('--scope', nargs='*', default=['src'])
    ap.add_argument('--depth', type=int, default=3)
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--plan-sites', type=Path, help='tools/headers/census.py sites.tsv to fuse with')
    a = ap.parse_args(argv)
    root = a.root.resolve()
    rows = census(root, a.db or root / 'build/codemap.db', a.scope)
    summary = write(a.out, rows, a.depth)
    if a.plan_sites:
        summary['fused'] = fuse(a.out, rows, a.plan_sites)
        (a.out / 'summary.json').write_text(json.dumps(summary, indent=1) + '\n')
    print(json.dumps(summary, indent=1))
    return 0


if __name__ == '__main__':
    sys.exit(main())
