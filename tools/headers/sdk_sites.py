#!/usr/bin/env python3
"""Per-site planner verdicts for Psy-Q/BIOS library names (tools/headers/extra.py SDK table).

    sdk_sites.py [--root R] [--scope src] [--out sites.tsv]

For every file-scope declaration of an SDK name inside a .c file of the scope: whether the header plan
removes it (and which include/sdk header replaces it) or keeps it, with the planner's reason.  Read-only.
"""
from __future__ import annotations
import argparse, collections, csv, re, sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent)]
import extra  # noqa: E402
import plan as P  # noqa: E402
import model as M  # noqa: E402


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--root', default='.')
    ap.add_argument('--scope', nargs='+', default=['src'])
    ap.add_argument('--out')
    a = ap.parse_args()
    root = Path(a.root).resolve()
    corpus = M.Corpus(root)
    corpus.c_files = [f for f in corpus.c_files if not Path(f).name.startswith('.')]
    names = set(extra.SDK)
    pat = re.compile(r'\b(' + '|'.join(sorted(names, key=len, reverse=True)) + r')\b')
    files = [f for f in corpus.c_files if any(f == s or f.startswith(s.rstrip('/') + '/') for s in a.scope)
             and pat.search(corpus.text(f))]
    plan = P.build(root, corpus=corpus, scope_files=files)
    hof = lambda r: plan.fn_for_def(r.definition).header  # noqa: E731
    rows = []
    for rel in sorted(plan.tus):
        tp = plan.tus[rel]
        removed = {(r.site.name, r.site.line): hof(r) for r in tp.remove}
        for s in plan.sites:
            if s.site.path != rel or s.site.name not in names or getattr(s.site, 'in_header', False):
                continue
            key = (s.site.name, s.site.line)
            if key in removed:
                h = removed[key]
                verdict = 'held:' + tp.holds[h] if h in tp.holds else 'remove'
                rows.append((rel, s.site.line, s.site.name, verdict, h, s.cls, s.reason))
            else:
                rows.append((rel, s.site.line, s.site.name, 'keep', '', s.cls, s.reason or s.detail))
    out = open(a.out, 'w') if a.out else sys.stdout
    w = csv.writer(out, delimiter='\t', lineterminator='\n')
    w.writerow(['file', 'line', 'name', 'verdict', 'header', 'class', 'reason'])
    w.writerows(rows)
    c = collections.Counter(r[3].split(':')[0] + ':' + (r[6] or '').split(':')[0] if r[3] != 'remove' else 'remove' for r in rows)
    print(dict(c), file=sys.stderr)


if __name__ == '__main__':
    main()
