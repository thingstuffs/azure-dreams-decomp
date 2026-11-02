#!/usr/bin/env python3
"""Promote rows linked at a placeholder address to the true base their callers jal, and respell the callers.

    rebase_placeholder_rows.py --classes CLASSES.tsv [--only NAME ...] [--codemap DB] [--out DIR] [--dry-run]

CLASSES.tsv is tools/codemap/target_census.py --classes output; class C_PLACEHOLDER rows read
`<symbol> linked at <addr> (row <row>, canonical <name>); true address <true> in region <foff>@<base>`: the callers
of the address name `func_<true>` reach a C row whose unit is linked at its placeholder row address (the devkit card
server, MAIN +0x269000 at 0x80400000, keeps 0x8001xxxx row ids).  Per C row (assembler / library rows are skipped):

  * config/overlays/<container>.rowbase.jsonl gains a proven record for exactly the row's extent with
    delta = true - foff (unless a proven record already covers it), so the build links the unit at the true address;
  * ledger/splits/<container>.jsonl: the row's true_name becomes func_<true>;
  * config/names.tsv: the canonical readable name's line moves to <true> / func_<true>; alias lines for func_<true>
    (a second readable name for the same function, e.g. wait_selected) are removed and their users respelled; a
    stale alias of the row's old true_name is removed when nothing spells it;
  * rows whose symbol a native module binds by name (config/overlays/modules.json members: a home shared with
    another container) are skipped;
  * every .c spelling `func_<true>` or such an alias is respelled to the canonical name with
    tools/headers/address_respell.py's rules (delete the local declaration when an included header declares the
    name and no #include follows it, else rename it; native-module imports are held).
Run tools/registry.py and the link-graph capture afterwards (ledger/rows.jsonl, config/link_graph), then
make configure && make && make check: the rowbase records change link addresses, so only a full build proves it.
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
sys.path.insert(0, str(HERE.parent))
import address_respell as AR  # noqa: E402

DETAIL = re.compile(r'^(?P<sym>\S+) linked at (?P<linked>0x[0-9a-f]+) \(row (?P<row>[^,)]+), canonical (?P<canon>\S+)\); '
                    r'true address (?P<true>0x[0-9a-f]+) in region (?P<foff>0x[0-9a-f]+)@(?P<base>0x[0-9a-f]+)')


def placeholders(classes, only=None):
    out = []
    with open(classes) as fh:
        for row in csv.DictReader(fh, delimiter='\t'):
            if row['class'] != 'C_PLACEHOLDER' or (only and row['name'] not in only):
                continue
            m = DETAIL.match(row['detail'])
            if m:
                out.append(dict(name=row['name'], symbol=m['sym'], row=m['row'], canonical=m['canon'],
                                true=int(m['true'], 16)))
    return out


def read_jsonl(path):
    return [json.loads(line) for line in path.read_text().splitlines() if line.strip()]


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--classes', type=Path, required=True)
    ap.add_argument('--only', nargs='*')
    ap.add_argument('--root', type=Path, default=ROOT)
    ap.add_argument('--codemap', type=Path)
    ap.add_argument('--out', type=Path)
    ap.add_argument('--dry-run', action='store_true')
    a = ap.parse_args(argv)
    root = a.root.resolve()
    dbp = a.codemap or root / 'build/codemap.db'
    db = sqlite3.connect('file:%s?mode=ro' % dbp, uri=True) if dbp.is_file() else None
    names_path = root / 'config/names.tsv'
    names_lines = names_path.read_text(errors='surrogateescape').split('\n')
    log, diffs = [], []
    changed = {}                                   # path -> new text

    def text_of(rel):
        return changed.get(rel) if rel in changed else (root / rel).read_text(errors='surrogateescape')

    by_container = {}
    respell = {}                                   # old spelling -> canonical name
    module_functions = set()                       # symbols other native modules bind by name (shared homes)
    modules_path = root / 'config/overlays/modules.json'
    if modules_path.is_file():
        for m in json.loads(modules_path.read_text()).get('modules', []):
            module_functions |= {x.get('function') for x in m.get('members', []) if isinstance(x, dict)}
    for p in placeholders(a.classes, set(a.only) if a.only else None):
        container, func = p['row'].split('/')
        splits_rel = 'ledger/splits/%s.jsonl' % container
        rows = by_container.setdefault(container, read_jsonl(root / splits_rel))
        split = next((r for r in rows if r.get('func_vram') == func), None)
        if split is None or split.get('result') != 'MATCH' or not split.get('c_path') or \
                'asm' in str(split.get('config', '')):
            log.append((p['name'], 'skip_not_c_row', func))
            continue
        canonical = p['canonical']
        if func in module_functions:
            log.append((p['name'], 'skip_native_module_member', func))
            continue
        if canonical.startswith('func_'):
            log.append((p['name'], 'skip_no_readable_name', func))
            continue
        true_sym = 'func_%08X' % p['true']
        foff, size = int(split['foff']), int(split['size'])
        # rowbase record (skipped when a proven record already covers the extent)
        rb_rel = 'config/overlays/%s.rowbase.jsonl' % container
        rb = text_of(rb_rel)
        covered = False
        for line in rb.splitlines():
            if line.strip().startswith('{'):
                r = json.loads(line)
                if r.get('base_confidence') == 'proven' and int(str(r['foff_start']), 0) <= foff and \
                        foff + size <= int(str(r['foff_end']), 0):
                    covered = int(str(r['delta']), 0) == p['true'] - foff or 'conflict'
        if covered == 'conflict':
            log.append((p['name'], 'skip_rowbase_conflict', func))
            continue
        if not covered:
            rec = {'schema': 'azure-clean.rowbase.v1', 'region': '%s_%X_callers' % (container, foff),
                   'foff_start': '0x%X' % foff, 'foff_end': '0x%X' % (foff + size),
                   'delta': '0x%X' % (p['true'] - foff), 'base_confidence': 'proven',
                   'proof': 'Retail jal %s call sites (tools/codemap call_bind placeholder_base) reach this row only at '
                            'true base 0x%08X; the region delta is recorded in ledger/instance_load_regions.jsonl. '
                            'PROMOTED: byte-exact recompile at the true base (make check).' % (true_sym, p['true'])}
            changed[rb_rel] = rb.rstrip('\n') + '\n' + json.dumps(rec) + '\n'
        old_true = split.get('true_name')
        split['true_name'] = true_sym
        # names.tsv
        aliases = []
        new_lines = []
        for line in names_lines:
            cols = line.split('\t')
            if len(cols) >= 3 and cols[1] == func and cols[2] == canonical:
                cols[0], cols[1] = '0x%08X' % p['true'], true_sym
                line = '\t'.join(cols)
            elif len(cols) >= 3 and cols[1] == true_sym and cols[2] != canonical:
                aliases.append(cols[2])
                continue
            elif len(cols) >= 3 and old_true and cols[1] == old_true and old_true not in (true_sym, func):
                if db is None or not db.execute('SELECT 1 FROM call_site WHERE callee = ? LIMIT 1', (cols[2],)).fetchone() \
                        and not db.execute('SELECT 1 FROM decl WHERE name = ? LIMIT 1', (cols[2],)).fetchone():
                    log.append((p['name'], 'retire_stale_alias', cols[2]))
                    continue
            new_lines.append(line)
        names_lines = new_lines
        respell[p['name']] = canonical
        for alias in aliases:
            respell[alias] = canonical
        log.append((p['name'], 'rebase', '%s -> %s (%s)%s' % (func, true_sym, canonical,
                                                              ' aliases ' + ','.join(aliases) if aliases else '')))
    for container, rows in by_container.items():
        changed['ledger/splits/%s.jsonl' % container] = ''.join(json.dumps(r, separators=(',', ':')) + '\n' for r in rows)
    changed['config/names.tsv'] = '\n'.join(names_lines)
    # respell the callers
    imports = AR.module_imports(root)
    token = re.compile(r'\b(' + '|'.join(sorted(map(re.escape, respell), key=len, reverse=True)) + r')\b') if respell else None
    for path in sorted((root / 'src').rglob('*.c')) if token else ():
        rel = str(path.relative_to(root))
        text = text_of(rel)
        if not token.search(text):
            continue
        new = text
        for old in sorted(set(token.findall(text))):
            name = respell[old]
            if old in imports.get(rel, ()):
                log.append((old, 'hold_native_module_import', rel))
                continue
            if AR.return_conflict(db, new, old, name):
                log.append((old, 'hold_return_type', rel))
                continue
            out, action = AR.respell_text(new, old, name, AR.visible(db, rel, name))
            if action is None:
                log.append((old, 'hold_decl_order', rel))
                continue
            new = out
            log.append((old, action, rel))
        if new != text:
            changed[rel] = new
    for rel, new in sorted(changed.items()):
        old = (root / rel).read_text(errors='surrogateescape')
        if old == new:
            continue
        diffs.extend(difflib.unified_diff(old.splitlines(True), new.splitlines(True), 'a/' + rel, 'b/' + rel))
        if not a.dry_run:
            (root / rel).write_text(new, errors='surrogateescape')
    if a.out:
        a.out.mkdir(parents=True, exist_ok=True)
        (a.out / 'rebase.tsv').write_text('name\taction\tdetail\n' + ''.join('\t'.join(map(str, r)) + '\n' for r in log))
        (a.out / 'rebase.patch').write_text(''.join(diffs), errors='surrogateescape')
    counts = {}
    for r in log:
        counts[r[1]] = counts.get(r[1], 0) + 1
    print('rebase_placeholder_rows: %s%s' % (counts, ' (dry run)' if a.dry_run else ''))
    return 0


if __name__ == '__main__':
    sys.exit(main())
