#!/usr/bin/env python3
"""Report repeated pointer casts and unused or repeated C-local typedef names."""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
import csv
from pathlib import Path
import re
import sqlite3
import sys

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent / 'readability'))
import score


def local_typedefs(text):
    """Return alias and token span for top-level typedefs, including braced records."""
    tokens = score.lex(text)
    result = []
    i = 0
    while i < len(tokens):
        if tokens[i].value != 'typedef':
            i += 1
            continue
        start, depth = i, 0
        i += 1
        while i < len(tokens):
            v = tokens[i].value
            if v in ('{', '(', '['):
                depth += 1
            elif v in ('}', ')', ']'):
                depth -= 1
            elif v == ';' and depth == 0:
                break
            i += 1
        end = min(i + 1, len(tokens))
        # Last identifier before the closing semicolon is the ordinary alias;
        # function-pointer typedefs need a separate declarator parser.
        part = tokens[start:end - 1]
        fn_names = [part[j + 2].value for j in range(len(part) - 3)
                    if [t.value for t in part[j:j + 2]] == ['(', '*']
                    and part[j + 2].kind == 'id' and part[j + 3].value == ')']
        aliases = [t.value for t in part if t.kind == 'id']
        if aliases:
            name = fn_names[-1] if fn_names and not any(t.value == '{' for t in part) else aliases[-1]
            users = sum(t.value == name for t in tokens[:start] + tokens[end:])
            result.append(dict(name=name, line=text.count('\n', 0, tokens[start].pos) + 1,
                               users=users, form='function_pointer' if fn_names and not any(t.value == '{' for t in part) else 'ordinary'))
        i = end
    return result


def cast_pairs(db):
    rows = db.execute('SELECT DISTINCT file,func,start,target,base_expr FROM cast_site '
                      'WHERE COALESCE(macro,0)=0 AND file LIKE "src/%" AND target IS NOT NULL')
    pairs = Counter()
    for file, func, _, target, base in rows:
        pairs[(file, func or '', target or '', base or '')] += 1
    totals = Counter()
    for (file, func, _, _), count in pairs.items():
        totals[(file, func)] += count
    selected = {key for key, _ in totals.most_common(200)}
    return sorted((file, func, totals[(file, func)], target, base, count)
                  for (file, func, target, base), count in pairs.items() if (file, func) in selected)


def write_tsv(path, header, rows):
    with path.open('w', newline='') as stream:
        writer = csv.writer(stream, delimiter='\t', lineterminator='\n')
        writer.writerow(header)
        writer.writerows(rows)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--root', type=Path, default=HERE.parents[1])
    ap.add_argument('--out', type=Path, required=True)
    args = ap.parse_args(argv)
    root, out = args.root.resolve(), args.out.resolve()
    out.mkdir(parents=True, exist_ok=True)
    db = sqlite3.connect(root / 'build/codemap.db')
    pairs = cast_pairs(db)
    write_tsv(out / 'cast_pairs_top200.tsv', ['file', 'function', 'function_casts', 'target_type', 'base_expression', 'pair_casts'], pairs)
    names = defaultdict(set)
    unused = []
    files = 0
    for path in (root / 'src').rglob('*.c'):
        files += 1
        rel = path.relative_to(root).as_posix()
        text = path.read_text(errors='replace')
        for td in local_typedefs(text):
            names[td['name']].add(rel)
            if td['users'] == 0:
                unused.append((rel, td['line'], td['name'], td['form']))
    write_tsv(out / 'unused_local_typedefs.tsv', ['file', 'line', 'typedef', 'form'], unused)
    repeated = [(name, len(paths), ','.join(sorted(paths))) for name, paths in names.items() if len(paths) > 1]
    write_tsv(out / 'repeated_typedef_names.tsv', ['name', 'files', 'definitions'], sorted(repeated, key=lambda r: (-r[1], r[0])))
    generic = [row for row in repeated if not re.search(r'[0-9A-Fa-f]{8}', row[0])]
    write_tsv(out / 'generic_typedef_names.tsv', ['name', 'files', 'definitions'], sorted(generic, key=lambda r: (-r[1], r[0])))
    print(f'files={files} top200_cast_pairs={len(pairs)} unused_local_typedefs={len(unused)} '
          f'repeated_names={len(repeated)} generic_repeated_names={len(generic)}')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
