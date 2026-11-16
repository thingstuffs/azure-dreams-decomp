#!/usr/bin/env python3
"""One name per clone family: native module copies take their canonical function's name (placed copies).

    clone_names.py --canonical-module SRC [--copies SRC ...] [--dry-run] [--root .]

For every member function of the canonical native module SRC (config/overlays/modules.json), the member at the
same offset of each copy module is the same retail function placed at another load address when its words agree
(tools/lint/placed_copies.py decides).  A copy whose name differs from the canonical member's takes the canonical
name through a config/names.tsv placed-copy row (`copy_of=0x<canonical address>; ...`, tools/build/name_inputs.py),
which the native module gate binds to the copy's own address, so every image stays byte-identical:

  * the canonical member's name must be the name of its ordinary config/names.tsv row (never a new name here);
  * the old name may appear only in the copy's own source and in headers that only that source includes (a
    reference from anywhere else would bind to the canonical address), else the copy is refused;
  * every whole-identifier use of the old name in those files becomes the canonical name, and the copy's
    names.tsv row records `copy_of=0x<canonical>; <file>: ...` with `(renamed from <old>)`;
  * tools/lint/placed_copies.py then checks every family; a copy it refuses (words differ, or its unit is also
    placed through config/link where the name would bind to the canonical address) is restored.

Prints one line per copy: renamed or refused with the reason.  --dry-run restores every file.
"""
from __future__ import annotations

import argparse
import json
from pathlib import Path
import re
import subprocess
import sys

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent / 'lint'), str(HERE.parent / 'build')]


def modules(root):
    return {m['source']: m for m in json.loads((root / 'config/overlays/modules.json').read_text())['modules']}


def defined_names(text, address, table):
    import clone_transplant as C
    return [n for n in C.Unit(text).defs if table.get(n, n) == address]


def users(root, name):
    res = subprocess.run(['git', 'grep', '-l', '-w', '-e', name, '--', 'include', 'src', 'config'], cwd=root,
                         capture_output=True, text=True)
    return sorted(res.stdout.split())


def includers(root, header):
    import clone_transplant as C
    return C.includers(root, Path(header).relative_to('include').as_posix())


def rename_word(text, old, new):
    return re.sub(r'(?<![\w.])(?<!->)' + re.escape(old) + r'(?!\w)', new, text)


def names_row(text, address, old, new, canonical, words, canonical_file):
    """config/names.tsv with the copy row at `address` renamed to a placed-copy row."""
    addr = '0x' + address[5:]
    out, hit = [], 0
    for line in text.splitlines(keepends=True):
        cols = line.rstrip('\n').split('\t')
        if len(cols) >= 3 and cols[0] == addr and cols[2] == old:
            evidence = cols[3] if len(cols) > 3 else ''
            m = re.match(r'(?:\([a-z]+\)\s*)?(src/\S+?\.c)(?::[\d-]*)?[;:]\s*(.*)$', evidence)
            where, what = (m[1], m[2]) if m else ('', evidence)
            cols[2] = new
            cols[3:] = ['copy_of=0x%s; %s: %s; the same %d words as %s at 0x%s (%s) (tools/lint/placed_copies.py), '
                        'so one function placed in another image (renamed from %s)'
                        % (canonical[5:], where, what.rstrip('.; '), words, new, canonical[5:], canonical_file, old)]
            line = '\t'.join(cols) + '\n'
            hit += 1
        out.append(line)
    if hit != 1:
        raise ValueError('%d names.tsv rows for %s %s' % (hit, address, old))
    return ''.join(out)


def run(root, canonical_src, copy_srcs, dry_run=False, log=print):
    import name_inputs
    import placed_copies as P
    root = Path(root).resolve()
    mods = modules(root)
    canon_mod = mods[canonical_src]
    table = name_inputs.table(root / 'config/names.tsv')
    results = []
    saved = {}

    def save(path):
        saved.setdefault(path, path.read_text())

    try:
        for src in copy_srcs:
            mod = mods[src]
            if len(mod['members']) != len(canon_mod['members']):
                results.append((src, None, 'refused', 'member count differs'))
                continue
            ctext = (root / canonical_src).read_text()
            text = (root / src).read_text()
            for cm, mm in zip(canon_mod['members'], mod['members']):
                cnames = defined_names(ctext, cm['function'], table)
                onames = defined_names(text, mm['function'], table)
                if len(cnames) != 1 or len(onames) != 1:
                    results.append((src, mm['function'], 'refused', 'definition not found'))
                    continue
                new, old = cnames[0], onames[0]
                if new == old:
                    continue
                if table.get(new) != cm['function']:
                    results.append((src, mm['function'], 'refused', 'canonical %s has no ordinary row' % new))
                    continue
                files = users(root, old)
                own_headers = [f for f in files if f.startswith('include/') and includers(root, f) == [src]]
                # the link graph is recaptured from the build after a rename
                others = [f for f in files if f not in own_headers and f not in (src, 'config/names.tsv')
                          and not f.startswith('config/link_graph/')]
                if others:
                    results.append((src, mm['function'], 'refused', '%s used in %s' % (old, ', '.join(others[:3]))))
                    continue
                before = {p: (root / p).read_text() for p in [src, 'config/names.tsv', *own_headers]}
                for p in [src, *own_headers]:
                    save(root / p)
                    (root / p).write_text(rename_word((root / p).read_text(), old, new))
                save(root / 'config/names.tsv')
                (root / 'config/names.tsv').write_text(
                    names_row((root / 'config/names.tsv').read_text(), mm['function'], old, new, cm['function'],
                              cm['size'] // 4, canonical_src))
                _, problems = P.check(root)
                mine = [p for p in problems if p.startswith(new + ':') and mm['function'] in p]
                if mine or any(p.startswith(new + ':') for p in problems):
                    for p, t in before.items():
                        (root / p).write_text(t)
                    results.append((src, mm['function'], 'refused', (mine or problems)[0][:200]))
                    continue
                table = name_inputs.table(root / 'config/names.tsv')
                text = (root / src).read_text()
                results.append((src, mm['function'], 'renamed', '%s -> %s' % (old, new)))
        for r in results:
            log('%s %s %s: %s' % r)
    finally:
        if dry_run:
            for p, t in saved.items():
                p.write_text(t)
    return results


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', default='.')
    ap.add_argument('--canonical-module', required=True)
    ap.add_argument('--copies', nargs='+', required=True)
    ap.add_argument('--dry-run', action='store_true')
    args = ap.parse_args(argv)
    res = run(args.root, args.canonical_module, args.copies, args.dry_run)
    print('clone names: %d renamed, %d refused' % (sum(r[2] == 'renamed' for r in res),
                                                   sum(r[2] == 'refused' for r in res)))
    return 0


if __name__ == '__main__':
    sys.exit(main())
