#!/usr/bin/env python3
"""Delete file-scope `extern` declarations a .c file never uses.

    dead_externs.py [--scope src/dungeon ...] [--names NAMES.txt] [--out DIR] [--dry-run]

A declaration is dead when its name occurs exactly once in the file (the declaration itself; comments count
as occurrences, so a name a comment still mentions is kept) and the statement is a single-line declaration of
that one name at column 0: a function prototype (`[extern] T name(...);`) or an `extern` object
(`extern T name[...];`, `extern T name;`).  Tentative definitions (an object without `extern`), static
prototypes, multi-name statements, indented (block-scope) declarations and macro lines are never touched.
An unused extern declaration emits nothing in gcc 2.7 objects, so the edit is byte-neutral by construction;
prove the batch anyway (tools/lanes/prove_batch.sh) - the per-TU proof is the acceptance.

--names limits the edit to the listed names (one per line).  Writes DIR/dead_externs.tsv and DIR/dead_externs.patch.
SLUS sources are skipped (the executable build splices partition owners into merged compiler inputs, so a name
one file declares can be used by a sibling of the same physical TU); the list comes from build/codemap.db
(recipes of family slus) and falls back to every file under src/slus/ when no code map is present.
"""
from __future__ import annotations

import argparse
import difflib
import re
import sqlite3
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TYPE = (r'(?:(?:const|volatile|unsigned|signed|struct|union|enum)[ \t]+)*[A-Za-z_]\w*'
        r'(?:[ \t]*\*+[ \t]*|[ \t]+)(?:\*[ \t]*)*')
TAIL = r'[ \t]*;[ \t]*(?:/\*[^\n]*?\*/[ \t]*)?\n'
# data: only `extern` (a file-scope object without it is a tentative definition)
DATA = re.compile(r'^extern[ \t]+' + TYPE + r'(?P<name>[A-Za-z_]\w*)[ \t]*(?:\[[^;\]\n]*\][ \t]*)*' + TAIL, re.M)
# functions: a prototype, with or without `extern` (never a definition: it ends in `;`)
FUNC = re.compile(r'^(?:extern[ \t]+|static[ \t]+)?' + TYPE + r'(?P<name>[A-Za-z_]\w*)[ \t]*\([^;{}()\n]*\)' + TAIL, re.M)


def dead_in(text, only=None):
    """[(start, end, name)] of dead single-line extern declarations in one file."""
    out = []
    for m in sorted(list(DATA.finditer(text)) + list(FUNC.finditer(text)), key=lambda m: m.start()):
        name = m['name']
        if only is not None and name not in only:
            continue
        if m.group(0).startswith('static') and '(' in m.group(0):
            continue            # a static prototype may announce a definition elsewhere in the file
        if len(re.findall(r'\b' + re.escape(name) + r'\b', text)) == 1 and \
                not (out and out[-1][0] == m.start()):
            out.append((m.start(), m.end(), name))
    return out


def slus_sources(root):
    """Physical sources of the executable's recipes (merged/partitioned compiler inputs)."""
    db = root / 'build/codemap.db'
    if not db.is_file():
        return set()
    con = sqlite3.connect('file:%s?mode=ro' % db, uri=True)
    return {p for (p,) in con.execute("SELECT physical FROM recipe WHERE family = 'slus'") if p}


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--scope', nargs='*', default=['src'])
    ap.add_argument('--root', type=Path, default=ROOT)
    ap.add_argument('--names', type=Path)
    ap.add_argument('--out', type=Path)
    ap.add_argument('--dry-run', action='store_true')
    a = ap.parse_args(argv)
    root = a.root.resolve()
    only = set(a.names.read_text().split()) if a.names else None
    skip = slus_sources(root)
    rows, diffs = [], []
    for scope in a.scope:
        base = root / scope
        files = [base] if base.is_file() else sorted(base.rglob('*.c'))
        for path in files:
            rel = str(path.relative_to(root))
            if rel in skip or rel.startswith('src/slus/'):
                continue
            text = path.read_text(errors='surrogateescape')
            hits = dead_in(text, only)
            if not hits:
                continue
            new = text
            for start, end, name in reversed(hits):
                new = new[:start] + new[end:]
                rows.append((str(path.relative_to(root)), name))
            rel = str(path.relative_to(root))
            diffs.extend(difflib.unified_diff(text.splitlines(True), new.splitlines(True), 'a/' + rel, 'b/' + rel))
            if not a.dry_run:
                path.write_text(new, errors='surrogateescape')
    if a.out:
        a.out.mkdir(parents=True, exist_ok=True)
        (a.out / 'dead_externs.tsv').write_text('file\tname\n' + ''.join('%s\t%s\n' % r for r in rows))
        (a.out / 'dead_externs.patch').write_text(''.join(diffs), errors='surrogateescape')
    print('dead_externs: %d declarations in %d files%s' % (len(rows), len({r[0] for r in rows}),
                                                          ' (dry run)' if a.dry_run else ''))
    return 0


if __name__ == '__main__':
    sys.exit(main())
