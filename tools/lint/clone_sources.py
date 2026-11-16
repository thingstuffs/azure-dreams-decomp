#!/usr/bin/env python3
"""Clone sources: copies of one retail function body that are kept as one source text.

ledger/clone_sources.jsonl records, per family, the donor copy (`donor`, its func_<addr>, and `row`, its retail
row id) and every copy rewritten from the donor's text by tools/typing/clone_transplant.py (`copies`: address, row
id and the symbol map, donor object symbol -> copy object symbol, for every symbol that differs between the two
placements).  This check finds each copy's source through its row the way tools/lint/placed_copies.py does
(ledger/layout.jsonl, or the native module member in config/overlays/modules.json), takes the function in it
whose config/names.tsv symbol is the address, and compares the two definitions token by token, comments and layout aside.  Two tokens agree when
they are equal, when they are the two definitions' own names, or when both spell object symbols (through the name
table, as ccproc spells them) and the map takes the donor's symbol to the copy's.  Any other difference is drift:
a later edit to one copy that was not made to the others (run clone_transplant.py again from the edited copy, or
make the same edit in every copy).

    python3 tools/lint/clone_sources.py [--root .]      # prints the families; rc 1 on drift
"""
from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
LEDGER = 'ledger/clone_sources.jsonl'
sys.path.insert(0, str(Path(__file__).resolve().parent))
sys.path.insert(0, str(ROOT / 'tools/readability'))


def load(root):
    path = Path(root) / LEDGER
    if not path.is_file():
        return []
    return [json.loads(x) for x in path.read_text().splitlines() if x.strip()]


def _table(root):
    sys.path.insert(0, str(Path(root) / 'tools/build'))
    try:
        import name_inputs
    finally:
        sys.path.pop(0)
    return name_inputs.table(Path(root) / 'config/names.tsv')


def definition_tokens(text, name):
    """Code tokens of `name`'s definition (comments and directives dropped), or None."""
    import score
    tokens = score.lex(text)
    pairs, _ = score.pairs_of(tokens)
    for start, at, body, end, style in score.definitions(tokens, pairs):
        if tokens[at].value == name:
            return [(t.value, t.kind, k and tokens[k - 1].value in ('.', '->'))
                    for k, t in enumerate(tokens[start:end + 1], start)]
    return None


def locate(rows, root, address, row_id, table):
    """(file, function name, text) of the definition of `address` in the source of row `row_id`, or (None, reason).

    The row id (container and retail position) tells copies at one address in different images apart."""
    import score
    member = rows.members.get(row_id)
    path = member['source'] if member else rows.paths.get(row_id)
    if not path or not (Path(root) / path).is_file():
        return None, 'row %s has no source' % row_id
    text = (Path(root) / path).read_text(errors='replace')
    tokens = score.lex(text)
    pairs, _ = score.pairs_of(tokens)
    hits = [tokens[at].value for start, at, body, end, style in score.definitions(tokens, pairs)
            if table.get(tokens[at].value, tokens[at].value) == address]
    if len(hits) != 1:
        return None, '%d definitions of %s in %s' % (len(hits), address, path)
    return (path, hits[0], text), None


MODULE_FILE = re.compile(r'(?:^|/)ovl_([0-9a-f]{6})\.c$')


def module_tag(path):
    """`CB9000` for src/dungeon/modules/ovl_cb9000.c (its generated views are spelled CL_CB9000_...)."""
    m = MODULE_FILE.search(path or '')
    return m[1].upper() if m else None


def compare(donor, copy, donor_name, copy_name, symmap, table, tags=(None, None)):
    """Problems between two definitions' token lists (empty when they are one source under the map).

    `tags` (donor module tag, copy module tag): a module view type or member spelled CL_<donor tag>_... in the
    donor is the copy's CL_<copy tag>_... (one layout per module copy)."""
    if len(donor) != len(copy):
        return ['%d tokens != %d' % (len(donor), len(copy))]
    for k, ((a, ka, ma), (b, kb, mb)) in enumerate(zip(donor, copy)):
        if a == b:
            continue
        if ka == kb == 'id' and all(tags) and a.startswith('CL_%s_' % tags[0]) and \
                b == 'CL_%s_' % tags[1] + a[len('CL_%s_' % tags[0]):]:
            continue
        if ka == kb == 'id' and not ma and not mb:
            if a == donor_name and b == copy_name:
                continue
            sa, sb = table.get(a, a), table.get(b, b)
            if symmap.get(sa, sa) == sb:
                continue
        return ['token %d: %s != %s' % (k, a, b)]
    return []


def check(root=ROOT):
    root = Path(root)
    families = load(root)
    if not families:
        return {}, []
    import placed_copies as P
    rows = P.Rows(root)
    table = _table(root)
    report, problems = {}, []
    for fam in families:
        hit, why = locate(rows, root, fam['donor'], fam['row'], table)
        if not hit:
            problems.append('%s: donor %s' % (fam['donor'], why))
            continue
        dpath, dname, dtext = hit
        dtokens = definition_tokens(dtext, dname)
        report[fam['donor']] = [(fam['donor'], dpath, dname)]
        for c in fam['copies']:
            hit, why = locate(rows, root, c['address'], c['row'], table)
            if not hit:
                problems.append('%s: copy %s' % (fam['donor'], why))
                continue
            cpath, cname, ctext = hit
            report[fam['donor']].append((c['address'], cpath, cname))
            bad = compare(dtokens, definition_tokens(ctext, cname), dname, cname, c.get('map', {}), table,
                          (module_tag(dpath), module_tag(cpath)))
            problems += ['%s %s (%s) drifted from %s (%s): %s' % (cname, c['address'], cpath, dname, dpath, p)
                         for p in bad[:1]]
    return report, problems


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--root', type=Path, default=ROOT)
    args = parser.parse_args(argv)
    report, problems = check(args.root.resolve())
    for donor, members in report.items():
        print(donor + ': ' + ', '.join('%s %s' % (a, p) for a, p, _ in members))
    for p in problems:
        print('CLONE DRIFT ' + p)
    print('clone sources: %d families, %d copies, %d problems' % (
        len(report), sum(len(v) - 1 for v in report.values()), len(problems)))
    return 1 if problems else 0


if __name__ == '__main__':
    sys.exit(main())
