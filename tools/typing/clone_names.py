#!/usr/bin/env python3
"""One name per clone family: native module copies take their canonical function's name (placed copies).

    clone_names.py --canonical-module SRC [--copies SRC ...] [--dry-run] [--root .]
    clone_names.py --family CANONICAL=SRC COPY=SRC [COPY=SRC ...] [--dry-run] [--root .]

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

--family names one family directly: the function at address CANONICAL (0x<addr>) defined in SRC is the canonical
(its name must be its ordinary config/names.tsv row) and each COPY=SRC is a copy, renamed the same way; a header
that only the family's sources include follows the copy too.  Copies
whose words differ only in relocated fields that move with their image's base (placed_copies.relocated) record
that in their evidence.

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
    """Files that spell name as an identifier (a file path spelling it, `dir/<name>.c`, is not a use)."""
    res = subprocess.run(['git', 'grep', '-l', '-w', '-e', name, '--', 'include', 'src', 'config'], cwd=root,
                         capture_output=True, text=True)
    use = re.compile(r'(?<![\w/])' + re.escape(name) + r'(?![\w]|\.[ch]\b)')
    return sorted(f for f in res.stdout.split() if use.search((Path(root) / f).read_text(errors='replace')))


def includers(root, header):
    import clone_transplant as C
    return C.includers(root, Path(header).relative_to('include').as_posix())


def rename_word(text, old, new):
    """Every identifier use of old becomes new; members (`.old`, `->old`) and file paths (`dir/old.h`) stay."""
    return re.sub(r'(?<![\w./])(?<!->)' + re.escape(old) + r'(?!\w|\.[ch]\b)', new, text)


def names_row(text, address, old, new, canonical, words, canonical_file, proof=None):
    """config/names.tsv with the copy row at `address` renamed to a placed-copy row.

    proof: how the bodies agree, when not word for word (placed_copies.relocated)."""
    addr = '0x' + address[5:]
    out, hit = [], 0
    for line in text.splitlines(keepends=True):
        cols = line.rstrip('\n').split('\t')
        if len(cols) >= 3 and cols[0] == addr and cols[2] == old:
            evidence = cols[3] if len(cols) > 3 else ''
            m = re.match(r'(?:\([a-z]+\)\s*)?(src/\S+?\.c)(?::[\d-]*)?[;:]\s*(.*)$', evidence)
            where, what = (m[1], m[2]) if m else ('', evidence)
            cols[2] = new
            same = ('the same %d words as %s at 0x%s (%s)' % (words, new, canonical[5:], canonical_file)
                    if proof is None else proof)
            cols[3:] = ['copy_of=0x%s; %s: %s; %s (tools/lint/placed_copies.py), '
                        'so one function placed in another image (renamed from %s)'
                        % (canonical[5:], where, what.rstrip('.; '), same, old)]
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


def proof_text(rows, canonical_row, copy_row, new, canonical, canonical_file):
    """None when the two bodies are the same words (a jump within the body aside), else the relocation proof."""
    import placed_copies as P
    a, b = rows.words(canonical_row), rows.words(copy_row)
    start_a, start_b = rows.start(canonical_row), rows.start(copy_row)
    if not P.compare(a, b, start_a, start_b):
        return None
    if rows.relocated(canonical_row, copy_row):
        raise ValueError('differs')
    moved = sum(x != y for x, y in zip(a, b))
    shift = rows.module_shift(canonical_row, copy_row)
    return ('the same %d instructions as %s at 0x%s (%s) apart from %d relocated words%s'
            % (len(a), new, canonical[5:], canonical_file, moved,
               '' if shift is None else ', whose targets move with the image base (%+#x)' % shift))


def run_family(root, canonical, copies, dry_run=False, log=print):
    """Rename each (address, source) in copies to the name of the canonical (address, source)."""
    import name_inputs
    import placed_copies as P
    root = Path(root).resolve()
    table = name_inputs.table(root / 'config/names.tsv')
    rows = P.Rows(root)
    results, saved = [], {}

    def row_at(address, src):
        cands = list(rows.rows.get(address, []))
        cands += [rows.by_id[i] for i, m in rows.members.items()
                  if m.get('function') == address and i in rows.by_id and rows.by_id[i] not in cands]
        hits = [r for r in cands if (rows.members.get(r['id']) or {}).get('source', rows.paths.get(r['id'])) == src]
        return hits[0] if len(hits) == 1 else None


    caddr, csrc = canonical
    family_sources = {csrc, *(src for _, src in copies)}
    cnames = defined_names((root / csrc).read_text(), caddr, table)
    crow = row_at(caddr, csrc)
    try:
        if len(cnames) != 1 or crow is None or table.get(cnames[0]) != caddr:
            raise ValueError('canonical %s in %s has no ordinary row' % (caddr, csrc))
        new = cnames[0]
        for address, src in copies:
            onames = defined_names((root / src).read_text(), address, table)
            row = row_at(address, src)
            if not onames and new in name_inputs.copies(root / 'config/names.tsv') \
                    and address in name_inputs.copies(root / 'config/names.tsv')[new]['copies']:
                continue            # already recorded as a copy of this family
            if len(onames) != 1 or row is None:
                results.append((src, address, 'refused', 'definition or retail row not found'))
                continue
            old = onames[0]
            if old == new:
                continue
            try:
                proof = proof_text(rows, crow, row, new, caddr, csrc)
            except ValueError:
                results.append((src, address, 'refused', 'placed_copies: ' + rows.relocated(crow, row)[0][:160]))
                continue
            files = users(root, old)
            # a header only this family's sources include: each of them binds the name to its own address
            own_headers = [f for f in files if f.startswith('include/')
                           and src in includers(root, f) and set(includers(root, f)) <= family_sources]
            others = [f for f in files if f not in own_headers and f not in (src, 'config/names.tsv')
                      and not f.startswith('config/link_graph/')]
            if others:
                results.append((src, address, 'refused', '%s used in %s' % (old, ', '.join(others[:3]))))
                continue
            before = {p: (root / p).read_text() for p in [src, 'config/names.tsv', *own_headers]}
            for p in [src, *own_headers]:
                saved.setdefault(root / p, before[p])
                (root / p).write_text(rename_word(before[p], old, new))
            saved.setdefault(root / 'config/names.tsv', before['config/names.tsv'])
            (root / 'config/names.tsv').write_text(
                names_row(before['config/names.tsv'], address, old, new, caddr, rows.size(crow) // 4, csrc, proof))
            _, problems = P.check(root)
            mine = [p for p in problems if p.startswith(new + ':')]
            if mine:
                for p, t in before.items():
                    (root / p).write_text(t)
                results.append((src, address, 'refused', mine[0][:200]))
                continue
            table = name_inputs.table(root / 'config/names.tsv')
            results.append((src, address, 'renamed', '%s -> %s' % (old, new)))
    except ValueError as exc:
        results.append((csrc, caddr, 'refused', str(exc)))
    finally:
        if dry_run:
            for p, t in saved.items():
                p.write_text(t)
    for r in results:
        log('%s %s %s: %s' % r)
    return results


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', default='.')
    ap.add_argument('--canonical-module')
    ap.add_argument('--copies', nargs='+')
    ap.add_argument('--family', nargs='+', metavar='ADDRESS=SRC',
                    help='the canonical, then each copy, as 0x<address>=<source>')
    ap.add_argument('--dry-run', action='store_true')
    args = ap.parse_args(argv)
    if args.family:
        if len(args.family) < 2:
            ap.error('--family needs the canonical and at least one copy')
        pairs = []
        for item in args.family:
            address, _, src = item.partition('=')
            if not re.fullmatch(r'0x[0-9A-Fa-f]{8}', address) or not src:
                ap.error('want 0x<address>=<source>: ' + item)
            pairs.append(('func_' + address[2:].upper(), src))
        res = run_family(args.root, pairs[0], pairs[1:], args.dry_run)
    elif args.canonical_module and args.copies:
        res = run(args.root, args.canonical_module, args.copies, args.dry_run)
    else:
        ap.error('give --canonical-module and --copies, or --family')
    print('clone names: %d renamed, %d refused' % (sum(r[2] == 'renamed' for r in res),
                                                   sum(r[2] == 'refused' for r in res)))
    return 0


if __name__ == '__main__':
    sys.exit(main())
