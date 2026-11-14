#!/usr/bin/env python3
"""Placed-copy families: one name for the same function placed at several addresses.

A config/names.tsv row whose evidence starts with `copy_of=0x<addr>` records that the function at its address is
the same function as the name's ordinary (canonical) row at <addr>, compiled from a separate source in another
image (tools/build/name_inputs.py). This check refuses a family whose bodies differ.

For every family address the check finds the one row at that address whose source defines the family name, takes
its retail words (a native module member's extent from config/overlays/modules.json, else the ledger row's) and
compares them with the canonical row's words. The sizes must be equal and every word identical, except a J/JAL
whose target lies inside its own function at the same offset on both sides (a branch within the body, the only
field that moves with the placement). Any other difference, including a call to a different target, refuses.

The copy's name binds to its own address only where the native module gate compiles its TU, so every copy must be
a native module member (config/overlays/modules.json). A TU that config/link
also places in other images (an entry whose row is not its home) is compiled there through ccproc's global table,
which spells the name as the canonical address. So a copy is refused when such a placement places the copy itself
or a function of its TU that references the name.

    python3 tools/lint/placed_copies.py [--root .]      # prints the families; rc 1 on a problem
"""
from __future__ import annotations

import argparse
import json
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
CONTAINERS = {'dungeon': 'DUNGEON_DUNGEON.BIN', 'town': 'TOWN_TOWN.BIN', 'main': 'MAIN_MAIN.BIN',
              'ovmovie': 'OVMOVIE.BIN'}


def _name_inputs():
    sys.path.insert(0, str(ROOT / 'tools/build'))
    try:
        import name_inputs
    finally:
        sys.path.pop(0)
    return name_inputs


def strip_comments(text):
    text = re.sub(r'/\*.*?\*/', lambda m: re.sub(r'[^\n]', ' ', m[0]), text, flags=re.S)
    return re.sub(r'//[^\n]*', '', text)


def defines(text, name):
    """True when the C text has a function definition (not a declaration) of name."""
    for m in re.finditer(r'\b' + re.escape(name) + r'\s*\(', text):
        depth, i = 1, m.end()
        while i < len(text) and depth:
            depth += {'(': 1, ')': -1}.get(text[i], 0)
            i += 1
        rest = text[i:i + 400].lstrip()
        # K&R parameter declarations may sit between ')' and '{'
        if rest.startswith('{') or re.match(r'(?:[^;{}()]*;\s*)+\{', rest):
            line = text[text.rfind('\n', 0, m.start()) + 1:m.start()]
            if not re.search(r'[=,(]\s*$', line) and 'return' not in line:
                return True
    return False


def definition(text, name):
    """Body text of name's definition in comment-stripped C text, or None."""
    for m in re.finditer(r'\b' + re.escape(name) + r'\s*\(', text):
        line = text[text.rfind('\n', 0, m.start()) + 1:m.start()]
        if re.search(r'[=,(]\s*$', line) or 'return' in line:
            continue
        depth, i = 1, m.end()
        while i < len(text) and depth:
            depth += {'(': 1, ')': -1}.get(text[i], 0)
            i += 1
        rest = re.match(r'\s*(?:[^;{}()]*;\s*)*\{', text[i:])
        if not rest:
            continue
        brace = i + rest.end() - 1
        depth, j = 0, brace
        while j < len(text):
            depth += {'{': 1, '}': -1}.get(text[j], 0)
            j += 1
            if depth == 0:
                return text[brace:j]
    return None


def compare(canonical, copy, start_a, start_b):
    """Problems between two word lists (empty when they are the same function)."""
    if len(canonical) != len(copy):
        return [f'size {4 * len(canonical)} != {4 * len(copy)}']
    problems = []
    for k, (a, b) in enumerate(zip(canonical, copy)):
        if a == b:
            continue
        op = a >> 26
        if op in (2, 3) and b >> 26 == op:
            ta = ((start_a + 4 * k + 4) & 0xF0000000) | ((a & 0x03FFFFFF) << 2)
            tb = ((start_b + 4 * k + 4) & 0xF0000000) | ((b & 0x03FFFFFF) << 2)
            ra, rb = ta - start_a, tb - start_b
            if ra == rb and 0 <= ra < 4 * len(canonical):
                continue
        problems.append(f'word {k}: {a:08x} != {b:08x}')
    return problems


class Rows:
    def __init__(self, root):
        self.root = root
        self.rows = {}
        for line in (root / 'ledger/rows.jsonl').read_text().splitlines():
            if line.strip():
                row = json.loads(line)
                self.rows.setdefault(row.get('true_name'), []).append(row)
        self.paths = {}
        for line in (root / 'ledger/layout.jsonl').read_text().splitlines():
            if line.strip():
                row = json.loads(line)
                self.paths[row['id']] = row['path']
        self.members = {}
        modules = root / 'config/overlays/modules.json'
        if modules.is_file():
            for m in json.loads(modules.read_text())['modules']:
                for a in m['members']:
                    self.members[a['id']] = a
        self.texts = {}
        self.placed = {}
        for path in sorted((root / 'config/link').glob('*/*.json')):
            for entry in json.loads(path.read_text()).get('entries', []):
                if 'tu' in entry and entry.get('row') != entry.get('home'):
                    self.placed.setdefault(entry['tu'], set()).add(entry['home'])
        self.names = {}
        names = root / 'config/names.tsv'
        for raw in (names.read_text().splitlines() if names.is_file() else []):
            cols = raw.split('#', 1)[0].split('\t')
            if len(cols) >= 3 and cols[1].strip() and cols[2].strip():
                self.names.setdefault(cols[1].strip(), set()).add(cols[2].strip())
        self.by_id = {r['id']: r for rows in self.rows.values() for r in rows}

    def text(self, path):
        if path not in self.texts:
            p = self.root / path
            self.texts[path] = strip_comments(p.read_text(errors='replace')) if p.is_file() else ''
        return self.texts[path]

    def find(self, address, name):
        """(row, path) of the one row at address whose source defines name."""
        hits = [(r, self.paths.get(r['id'])) for r in self.rows.get(address, [])]
        hits = [(r, p) for r, p in hits if p and defines(self.text(p), name)]
        return hits

    def placed_users(self, path, name):
        """Placed functions of the TU at path (link-list entries other than their home) that are, or reference, name."""
        text = self.text(path)
        hits = []
        for home in sorted(self.placed.get(path, ())):
            row = self.by_id.get(home)
            if row is None:
                continue
            for fn in sorted((self.names.get(row.get("true_name"), set()) | {row.get("true_name")}) - {None}):
                body = definition(text, fn)
                if body is not None and (fn == name or re.search(r'\b' + re.escape(name) + r'\b', body)):
                    hits.append(f'{home} ({fn})')
                    break
        return hits

    def words(self, row):
        member = self.members.get(row['id'])
        offset = member.get('body_offset', 0) if member else 0
        foff = (member['foff'] if member else row['foff']) + offset
        size = (member['size'] if member else row['size']) - offset
        with (self.root / 'work/disc/containers' / CONTAINERS[row['container']]).open('rb') as f:
            f.seek(foff)
            data = f.read(size)
        return list(struct.unpack('<%dI' % (len(data) // 4), data))


def check(root=ROOT):
    root = Path(root)
    families = _name_inputs().copies(root / 'config/names.tsv')
    if not families:
        return {}, []
    missing = sorted({c for c in CONTAINERS.values() if not (root / 'work/disc/containers' / c).is_file()})
    if missing:
        # the retail containers are extracted locally (never published); without them nothing can be proven
        return {}, [f'{len(families)} families recorded but the retail containers are missing: ' + ', '.join(missing)]
    rows = Rows(root)
    problems, report = [], {}
    for name, family in sorted(families.items()):
        found = {}
        for address in [family['canonical'], *family['copies']]:
            hits = rows.find(address, name)
            if len(hits) != 1:
                problems.append(f'{name}: {len(hits)} rows at {address} define it '
                                f'({", ".join(p for _, p in hits) or "none"})')
                continue
            found[address] = hits[0]
        if family['canonical'] not in found:
            continue
        base_row, base_path = found[family['canonical']]
        base = rows.words(base_row)
        start = int(family['canonical'][5:], 16)
        report[name] = [(family['canonical'], base_path, 4 * len(base))]
        for address in family['copies']:
            if address not in found:
                continue
            row, path = found[address]
            if row['id'] not in rows.members:
                problems.append(f'{name}: {address} ({path}) is not a native module entry; only the native module '
                                'gate binds a family name to a copy\'s own address')
            users = rows.placed_users(path, name)
            if users:
                problems.append(f'{name}: {address} ({path}) is also placed through config/link, where the name binds '
                                f'to {family["canonical"]}: ' + ', '.join(users[:3]))
            bad = compare(base, rows.words(row), start, int(address[5:], 16))
            report[name].append((address, path, 4 * len(base)))
            problems += [f'{name}: {address} ({path}) differs from {family["canonical"]}: {p}' for p in bad[:3]]
    return report, problems


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--root', type=Path, default=ROOT)
    args = parser.parse_args(argv)
    report, problems = check(args.root.resolve())
    for name, members in report.items():
        print(name + ': ' + ', '.join(f'{a} {p}' for a, p, _ in members) + f' ({members[0][2]} bytes)')
    for p in problems:
        print('PLACED COPY ' + p)
    print(f'placed copies: {len(report)} families, {sum(len(v) - 1 for v in report.values())} copies, '
          f'{len(problems)} problems')
    return 1 if problems else 0


if __name__ == '__main__':
    sys.exit(main())
