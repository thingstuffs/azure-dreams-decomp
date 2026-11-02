#!/usr/bin/env python3
"""Respell the address names that tools/headers/address_respell.py holds in native modules, with the module's
import inventory edited in the same change.

    module_import_respell.py --classes CLASSES.tsv [--scope src/...] [--out DIR] [--dry-run]

address_respell.py respells a C_SAME address name (a callback stored as data, `D_800A5828`, whose C function is
linked at that very address) to the function's readable name, but holds the native-module TUs: their import
inventory (config/overlays/modules.json, a reviewed manifest) lists the old symbol.  The readable name lowers
(config/names.tsv, tools/build/ccproc.py) to the function's canonical symbol func_<addr>, so after the respell the
module object references func_<addr> where it referenced D_<addr>; same address, same relocation value.

For every hold `hold_native_module_import` this tool:
  * respells the TU with address_respell's own rules (the native-module hold lifted for exactly that name);
  * drops the module's import entry for the old symbol when the module's own source defines the function (the
    reference becomes local to the object), else rewrites it: symbol -> func_<addr>, kind -> function, the vma kept,
    the data-view fields (foff, view_bytes, owner, asset, map) dropped, `basis` naming the readable function and
    the evidence (an address-only data view becomes the function import it always was).  An entry for func_<addr>
    that already exists absorbs it.
Prove with make configure + make + make check (the module manifest is a graph authority).
"""
from __future__ import annotations

import argparse
import difflib
import json
import re
import sqlite3
import sys
from pathlib import Path

HERE = Path(__file__).resolve()
sys.path.insert(0, str(HERE.parent))
import address_respell as AR  # noqa: E402

DATA_FIELDS = ('foff', 'view_bytes', 'owner', 'asset', 'map', 'evidence', 'declaration')


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--classes', type=Path, required=True)
    ap.add_argument('--scope', nargs='*', default=['src'])
    ap.add_argument('--root', type=Path, default=HERE.parents[2])
    ap.add_argument('--out', type=Path)
    ap.add_argument('--dry-run', action='store_true')
    a = ap.parse_args(argv)
    root = a.root.resolve()
    dbp = root / 'build/codemap.db'
    db = sqlite3.connect('file:%s?mode=ro' % dbp, uri=True) if dbp.is_file() else None
    names = AR.mapping(a.classes)
    mpath = root / 'config/overlays/modules.json'
    mtext = mpath.read_text()
    manifest = json.loads(mtext)
    imports = AR.module_imports(root)
    rows, diffs = [], []
    files = sorted({p for s in a.scope for p in (root / s).rglob('*.c')} |
                   {root / s for s in a.scope if (root / s).is_file()})
    changed_manifest = False
    for path in files:
        rel = str(path.relative_to(root))
        held = sorted(n for n in imports.get(rel, ()) if n in names)
        if not held:
            continue
        text = path.read_text(errors='surrogateescape')
        new_text = text
        for old in held:
            if not re.search(r'\b%s\b' % re.escape(old), new_text):
                continue
            new = names[old]
            local = [m for m in AR.decl_pattern(old).finditer(new_text) if not m['lead']]
            if not local and not AR.visible(db, rel, new):
                rows.append((rel, old, new, 'hold_old_name_from_header'))   # a header spells the old name
                continue
            first_use = re.search(r'\b%s\b' % re.escape(old), new_text)
            defined_at = re.search(r'^[A-Za-z_][^;{}=\n]*\b%s\s*\([^;]*\)\s*\{' % re.escape(new), new_text, re.M)
            later_definition = defined_at is not None and first_use is not None and defined_at.start() > first_use.start()
            # a TU that defines the function after its use keeps the declaration, renamed
            out, action = AR.respell_text(new_text, old, new, AR.visible(db, rel, new) and not later_definition)
            if action is None and AR.visible(db, rel, new) and not later_definition:
                # merged TU: an #include follows the old declaration, but a header the TU includes declares the
                # readable name (or the TU defines it); the declaration goes, the build proof checks the order
                decls = [m for m in AR.decl_pattern(old).finditer(new_text) if not m['lead']]
                if decls:
                    out = new_text
                    for m in reversed(decls):
                        out = out[:m.start()] + out[m.end():]
                    out, action = re.sub(r'\b%s\b' % re.escape(old), new, out), 'delete_decl'
            if action is None:
                rows.append((rel, old, new, 'hold_decl_order_or_multiline'))
                continue
            new_text = out
            canonical = 'func_' + old[-8:].upper()
            for m in manifest['modules']:
                srcs = [m.get('source')] + [x.get('source') for x in m.get('members', []) if isinstance(x, dict)]
                if rel not in srcs:
                    continue
                imps = m.get('imports', [])
                at = next((i for i, e in enumerate(imps) if e['symbol'] == old), None)
                if at is None:
                    continue
                hit = imps.pop(at)
                changed_manifest = True
                defined = re.search(r'^[A-Za-z_][^;{}=\n]*\b%s\s*\([^;]*\)\s*\{' % re.escape(new), new_text, re.M)
                if defined:
                    continue             # the module defines the function itself: no import at all
                if not any(e['symbol'] == canonical for e in imps):
                    entry = {k: v for k, v in hit.items() if k not in DATA_FIELDS}
                    entry.update(symbol=canonical, kind='function',
                                 basis='respelled callback address: %s, the C function linked at this address '
                                       '(config/names.tsv); formerly the address-only data view %s' % (new, old))
                    imps.insert(at, entry)
                changed_manifest = True
            rows.append((rel, old, new, action + '+module_import'))
        if new_text != text:
            diffs.extend(difflib.unified_diff(text.splitlines(True), new_text.splitlines(True), 'a/' + rel, 'b/' + rel))
            if not a.dry_run:
                path.write_text(new_text, errors='surrogateescape')
    if changed_manifest:
        indent = next(n for n in (1, 2, 4) if json.dumps(json.loads(mtext), indent=n) + '\n' == mtext) \
            if any(json.dumps(json.loads(mtext), indent=n) + '\n' == mtext for n in (1, 2, 4)) else 2
        new_m = json.dumps(manifest, indent=indent) + '\n'
        diffs.extend(difflib.unified_diff(mtext.splitlines(True), new_m.splitlines(True),
                                          'a/config/overlays/modules.json', 'b/config/overlays/modules.json'))
        if not a.dry_run:
            mpath.write_text(new_m)
    if a.out:
        a.out.mkdir(parents=True, exist_ok=True)
        with (a.out / 'module_respell.tsv').open('w') as fh:
            fh.write('file\told\tnew\taction\n')
            fh.writelines('\t'.join(r) + '\n' for r in rows)
        (a.out / 'module_respell.patch').write_text(''.join(diffs), errors='surrogateescape')
    print('module_import_respell: %d edits' % len(rows))
    return 0


if __name__ == '__main__':
    sys.exit(main())
