#!/usr/bin/env python3
"""Respell address-named callees as the C function that really lives at that address.

    address_respell.py --classes CLASSES.tsv [--scope src/town src/dungeon/effect ...] [--codemap build/codemap.db]
                       [--out DIR] [--dry-run]

CLASSES.tsv is tools/codemap/target_census.py --classes output.  Only class C_SAME is taken: a C function whose
canonical symbol is func_<the same address> is linked there in the caller's container (or the SLUS), so the
readable name lowers (config/names.tsv, tools/ccproc.py) to the very symbol the address spelling resolved to and
the relocation, hence the bytes, cannot change.  C_COPY (a placement of another home linked at that address)
is never respelled: its readable name lowers to the home's own address; it needs a link-list binding instead.

Per .c file under --scope that spells an old name:
  * every token of the old name becomes the readable name (comments included);
  * the file-scope declaration of the old name is deleted when a header the TU already includes declares the
    readable name (codemap `decl`: a declaration of it in another file of the same TU), or the TU defines it;
    otherwise it is kept, renamed (it stays a local declaration of a real C name for extern_bulk.py / the
    header planner to publish later);
  * a data-shaped declaration (`extern T D_x;` / `D_x[]`) of a function is rewritten as `extern void name();` when no
    visible declaration exists (the use sites only take its address).
Holds (file untouched for that name): a native-module TU whose reviewed import inventory
(config/overlays/modules.json) lists the old name; a deletion whose replacing header is included after the old
declaration.  A header that declares an old name is renamed too (unless a held user still needs the old spelling).

Writes DIR/respell.tsv (file, old, new, action) and DIR/respell.patch (unified diff).  Prove the batch with
tools/lanes/prove_batch.sh (byte-exact) before committing; this tool does not compile.
"""
from __future__ import annotations

import argparse
import csv
import difflib
import json
import re
import sqlite3
import sys
from pathlib import Path

HERE = Path(__file__).resolve()
ROOT = HERE.parents[2]
DETAIL = re.compile(r'(?:^|\s)(?:slus )?(func_[0-9A-Fa-f]{8}) -> (\w+)')


def mapping(classes_path):
    """{old name: readable name} for the C_SAME rows."""
    out = {}
    with open(classes_path) as fh:
        for row in csv.DictReader(fh, delimiter='\t'):
            if row['class'] != 'C_SAME':
                continue
            m = DETAIL.search(row['detail'])
            if not m:
                continue
            symbol, readable = m[1], m[2]
            if int(symbol[5:], 16) != int(row['name'][-8:], 16):
                continue          # defensive: never a placement copy
            if readable != row['name']:
                out[row['name']] = readable
    return out


def decl_pattern(old):
    """One file-scope declaration statement of `old` on a single line."""
    return re.compile(r'^(?P<lead>[ \t]*)(?P<stmt>(?:extern[ \t]+)?[A-Za-z_][^;{}=\n]*?\b' + re.escape(old)
                      + r'\b[^;{}=\n]*;)[ \t]*(?:/\*[^\n]*?\*/[ \t]*)?\n', re.M)


def visible(db, tu, name):
    """True when the TU sees a declaration of `name` in a header of its include closure, or defines it."""
    if db is None:
        return False
    row = db.execute('SELECT headers FROM tu WHERE path = ?', (tu,)).fetchone()
    headers = set(json.loads(row[0] or '[]')) if row else set()
    for (f,) in db.execute('SELECT DISTINCT file FROM decl WHERE name = ?', (name,)):
        if f in headers:
            return True
    return db.execute('SELECT 1 FROM defn WHERE name = ? AND tu = ? LIMIT 1', (name, tu)).fetchone() is not None


def module_imports(root):
    """{source path: import symbols} of the native modules (config/overlays/modules.json): their import
    inventory is a reviewed manifest, so a respelled import needs a manifest edit, not this tool."""
    path = root / 'config/overlays/modules.json'
    out = {}
    if path.is_file():
        for m in json.loads(path.read_text()).get('modules', []):
            names = {d['symbol'] for d in m.get('imports', [])}
            for src in [m.get('source')] + [x.get('source') for x in m.get('members', []) if isinstance(x, dict)]:
                if src:
                    out.setdefault(src, set()).update(names)
    return out


def returns_void(db, name):
    """True when the definition / a header prototype of `name` returns void (None when unknown)."""
    if db is None:
        return None
    row = db.execute("SELECT ret FROM defn d JOIN decl x ON x.name = d.name AND x.kind = 'def' WHERE d.name = ? LIMIT 1",
                     (name,)).fetchone() or \
        db.execute("SELECT ret FROM decl WHERE name = ? AND file LIKE 'include/%' LIMIT 1", (name,)).fetchone()
    return None if row is None or row[0] is None else row[0].strip() == 'void'


def value_ignored(db, path, old):
    """True when the code map records calls of `old` in `path` and every one ignores the returned value."""
    if db is None or path is None:
        return False
    uses = {u for (u,) in db.execute('SELECT ret_use FROM call_site WHERE file = ? AND callee = ?', (path, old))}
    return bool(uses) and uses == {'ignored'}


def return_conflict(db, text, old, new, path=None):
    """A local declaration of `old` returns a value while the readable name's own prototype returns void: a caller
    may use the value (gcc 2.7: `void value not ignored`), so the prototype disagreement must be solved first.
    No conflict when every call in `path` ignores the value (code map call_site.ret_use): the void prototype
    compiles those calls to the same code."""
    if not returns_void(db, new):
        return False
    if value_ignored(db, path, old):
        return False
    for m in decl_pattern(old).finditer(text):
        head = m['stmt'].split(old, 1)[0]
        if not re.search(r'\bvoid\b', head) or '*' in head:
            return True
    return False


def respell_text(text, old, new, can_delete):
    """(new text, action) for one file; action None = hold."""
    pat = decl_pattern(old)
    decls = [m for m in pat.finditer(text)
             if not m['lead'] and m['stmt'].split(old, 1)[0].rstrip()[-1:] not in ('*', '(')]
    # a multi-line declaration would leave text behind: hold
    for line in text.splitlines():
        if re.search(r'\b' + re.escape(old) + r'\b', line) and line.rstrip().endswith(',') and \
                line.lstrip().startswith('extern'):
            return text, None
    if re.search(r'^[ \t]*(?:extern[ \t]+)?[^;{}=\n]*\b' + re.escape(new) + r'\b[ \t]*\(', text, re.M) and decls:
        can_delete = True        # the file already declares the readable name: the old declaration is a duplicate
    action = 'rename'
    out = text
    if can_delete and decls and re.search(r'^[ \t]*#[ \t]*include\b', text[decls[0].start():], re.M):
        return text, None        # the header that declares the readable name may come after the old declaration
    for m in reversed(decls):
        stmt = m['stmt']
        if can_delete:
            out = out[:m.start()] + out[m.end():]
            action = 'delete_decl'
        elif '(' not in stmt[stmt.index(old) + len(old):].lstrip()[:1]:
            # data-shaped declaration of a function: declare it as a function
            out = out[:m.start()] + 'extern void %s();\n' % new + out[m.end():]
            action = 'data_decl_as_function'
    out = re.sub(r'\b' + re.escape(old) + r'\b', new, out)
    return out, action


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--classes', type=Path, required=True)
    ap.add_argument('--scope', nargs='*', default=['src'])
    ap.add_argument('--root', type=Path, default=ROOT)
    ap.add_argument('--codemap', type=Path)
    ap.add_argument('--out', type=Path)
    ap.add_argument('--dry-run', action='store_true')
    a = ap.parse_args(argv)
    root = a.root.resolve()
    dbp = a.codemap or root / 'build/codemap.db'
    db = sqlite3.connect('file:%s?mode=ro' % dbp, uri=True) if dbp.is_file() else None
    names = mapping(a.classes)
    token = re.compile(r'\b(' + '|'.join(sorted(map(re.escape, names), key=len, reverse=True)) + r')\b') if names else None
    rows, diffs = [], []
    files = sorted({p for s in a.scope for p in (root / s).rglob('*.c')} | {p for s in a.scope if (root / s).is_file()
                                                                          for p in [root / s]})
    headers = sorted(p for p in (root / 'include').rglob('*.h'))
    imports = module_imports(root)
    # A name an included header declares is renamed there too (the header keeps declaring it, now readable).
    declared_in_header = {}
    for h in headers:
        text = h.read_text(errors='surrogateescape')
        for old in (set(token.findall(text)) if token else ()):
            declared_in_header.setdefault(old, []).append(h)
    for path in files:
        text = path.read_text(errors='surrogateescape')
        if token is None or not token.search(text):
            continue
        rel = str(path.relative_to(root))
        new_text = text
        for old in sorted(set(token.findall(text))):
            new = names[old]
            if old in imports.get(rel, ()):
                rows.append((rel, old, new, 'hold_native_module_import'))
                continue
            if return_conflict(db, new_text, old, new, rel):
                rows.append((rel, old, new, 'hold_return_type'))
                continue
            out, action = respell_text(new_text, old, new, visible(db, rel, new))
            if action is None:
                rows.append((rel, old, new, 'hold_decl_order_or_multiline'))
                continue
            new_text = out
            rows.append((rel, old, new, action))
        if new_text != text:
            diffs.extend(difflib.unified_diff(text.splitlines(True), new_text.splitlines(True), 'a/' + rel, 'b/' + rel))
            if not a.dry_run:
                path.write_text(new_text, errors='surrogateescape')
    done = {r[1] for r in rows if not r[3].startswith('hold')}
    held = {r[1] for r in rows if r[3].startswith('hold')}
    for old in sorted(done):
        for h in declared_in_header.get(old, ()):
            if old in held:
                continue        # a held user still spells the old name through this header
            text = h.read_text(errors='surrogateescape')
            new_text = re.sub(r'\b' + re.escape(old) + r'\b', names[old], text)
            rel = str(h.relative_to(root))
            rows.append((rel, old, names[old], 'rename_in_header'))
            diffs.extend(difflib.unified_diff(text.splitlines(True), new_text.splitlines(True), 'a/' + rel, 'b/' + rel))
            if not a.dry_run:
                h.write_text(new_text, errors='surrogateescape')
    if a.out:
        a.out.mkdir(parents=True, exist_ok=True)
        with (a.out / 'respell.tsv').open('w') as fh:
            fh.write('file\told\tnew\taction\n')
            fh.writelines('\t'.join(r) + '\n' for r in rows)
        (a.out / 'respell.patch').write_text(''.join(diffs), errors='surrogateescape')
    counts = {}
    for r in rows:
        counts[r[3]] = counts.get(r[3], 0) + 1
    print('address_respell: %d names mapped; %d file edits %s' % (len(names), len(rows), counts))
    return 0


if __name__ == '__main__':
    sys.exit(main())
