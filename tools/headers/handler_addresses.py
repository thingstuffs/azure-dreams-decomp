"""Resolve imported data spellings to exact C entry points without crossing banks.

The small nominal addresses in independently compiled overlays are not global
identities. A data spelling binds only within the same row address space, to a
resident function, or to the shared engine of its own container. This module is
also used by the import-header generator: function addresses must never become
new data declarations on a rerun.
"""
from __future__ import annotations

from collections import defaultdict
import json
import re

try:
    from . import model as M
except ImportError:
    import model as M


def number(value):
    return int(value, 0) if isinstance(value, str) else int(value)


def read_rows(path):
    if not path.exists():
        return []
    return [json.loads(line) for line in path.read_text().splitlines() if line.strip()]


class AddressIndex:
    def __init__(self, corpus, definitions):
        self.corpus = corpus
        self.definitions = definitions
        self.addresses = defaultdict(set)
        self.spellings = defaultdict(set)
        self.by_address = defaultdict(list)
        self.namespaces = defaultdict(set)
        self.def_namespaces = defaultdict(set)
        self.engine = set()
        self.rows = {r['id']: r for r in read_rows(corpus.root / 'ledger/rows.jsonl')}
        layouts = {r['id']: r['path'] for r in read_rows(corpus.root / 'ledger/layout.jsonl')}
        layouts.update({r['member_id']: r['tu_new'] for r in read_rows(corpus.root / 'ledger/layout_inline.jsonl')})
        table = corpus.root / 'config/names.tsv'
        if table.exists():
            for line in table.read_text().splitlines():
                cols = line.split('\t')
                if len(cols) < 3 or line.startswith('#'):
                    continue
                old, new = cols[1:3]
                m = re.fullmatch(r'(?:func_|D_)([0-9a-fA-F]{8})', old)
                if m:
                    self.addresses[old].add(int(m[1], 16))
                    self.addresses[new].add(int(m[1], 16))
                # D_ aliases name data views, not functions of a coincident bank.
                if old.startswith('func_'):
                    self.spellings[old].update((old, new))
                    self.spellings[new].update((old, new))
        symbols = corpus.root / 'config/slus_006.14.symbols.txt'
        if symbols.exists():
            for line in symbols.read_text().splitlines():
                m = re.match(r'(\w+)\s*=\s*(0x[0-9a-fA-F]+);', line)
                if m:
                    self.addresses[m[1]].add(int(m[2], 16))
        for name in definitions:
            m = re.fullmatch(r'(?:func_|D_)([0-9a-fA-F]{8})', name)
            if m:
                self.addresses[name].add(int(m[1], 16))
        by_path = defaultdict(list)
        for name, ds in definitions.items():
            for d in ds:
                if not d.static:
                    by_path[d.path].append(d)
        for row in self.rows.values():
            if row.get('source_row'):
                continue
            path = layouts.get(row['id'], 'src/' + row['container'] + '/' + row.get('c_path', row['id']).split('/')[-1])
            labels = {row.get('func'), row.get('true_name')}
            labels.update(s for n in tuple(labels) if n for s in self.spellings[n])
            found = [d for d in by_path[path] if d.name in labels]
            # File ownership alone does not identify one entry of a merged TU.
            if len(found) != 1:
                continue
            d = found[0]
            nominal = re.fullmatch(r'func_([0-9a-fA-F]{8})', (row.get('true_name') or ''))
            if nominal is None:
                nominal = re.fullmatch(r'func_([0-9a-fA-F]{8})', (row.get('func') or ''))
            addresses = {int(nominal[1], 16)} if nominal else set(self.addresses[d.name])
            if row.get('foff') is not None:
                for address in addresses:
                    ns = (row['container'], address - number(row['foff']))
                    self.namespaces[path].add(ns)
                    self.def_namespaces[(d.path, d.name)].add(ns)
                    if row.get('gate_config') == 'config/overlays/' + row['container'] + '_engine.overlay.yaml':
                        self.engine.add((d.path, d.name))
            for address in addresses:
                if d not in self.by_address[(d.container, address)]:
                    self.by_address[(d.container, address)].append(d)
        # Names reused by multiple overlays are not aliases across those
        # overlays. Unregistered resident helpers may still have an unambiguous
        # symbol-map address; do not index orphan overlay definitions by number.
        for name, ds in definitions.items():
            for d in ds:
                if d.static or (d.path, d.name) in self.def_namespaces:
                    continue
                if d.container == M.RESIDENT and len(self.addresses[name]) == 1:
                    address = next(iter(self.addresses[name]))
                    self.by_address[(d.container, address)].append(d)
        # Exact linked entry addresses are scoped by image. A start in an
        # unrelated bank is never a candidate for this TU's import.
        self.placements = defaultdict(list)
        self.link_starts = defaultdict(list)
        images, by_row = {}, {}
        for link in sorted((corpus.root / 'config/link').glob('*/*.json')):
            if link.stat().st_size > 4 * 1024 * 1024:
                raise ValueError('oversized link authority: ' + link.name)
            image = json.loads(link.read_text())
            images[image['image']] = image
            for entry in image.get('entries', []):
                if 'row' not in entry or 'tu' not in entry:
                    continue
                by_row[entry['row']] = (image, entry)
                self.placements[entry['tu']].append((image, entry))
        for image, entry in by_row.values():
            home = self.rows.get(entry.get('home'), {})
            labels = {home.get('func'), home.get('true_name'), entry.get('home', '').split('/')[-1]}
            labels.update(t for n in tuple(labels) if n for t in self.spellings[n])
            ds = [d for d in by_path[entry['tu']] if d.name in labels]
            if len(ds) == 1:
                self.link_starts[(image['image'], number(entry['vma']) + number(entry.get('body_offset', 0)))].append(ds[0])
        self.link_rows = by_row
        # A header's declarations have the context of its actual consumers.
        for rel in corpus.c_files:
            spaces = self.namespaces[rel]
            if spaces:
                for header in corpus.closure(rel)[1:]:
                    self.namespaces[header].update(spaces)
        for rel in corpus.c_files:
            if self.placements[rel]:
                for header in corpus.closure(rel)[1:]:
                    self.placements[header].extend(self.placements[rel])

    def targets(self, path, name):
        spaces = self.namespaces[path]
        containers = {c for c, delta in spaces}
        cont = M.container_of(path)
        if cont == 'include':
            top = path.split('/')[1]
            cont = M.CONTAINER_OF_TOP.get(top, top)
        containers.add(cont)
        direct = {name} | self.spellings[name]
        found = {}
        for symbol in direct:
            for d in self.definitions.get(symbol, ()):
                key = (d.path, d.name)
                if (not d.static and (d.container in containers or d.container == M.RESIDENT)
                        and (d.container == M.RESIDENT or not self.rows or d.path == path
                             or spaces & self.def_namespaces[key] or key in self.engine)):
                    found[key] = (d, 'exact function identifier in the importing address space / names.tsv function alias')
        addresses = set(self.addresses[name])
        m = re.fullmatch(r'(?:func_|D_)([0-9a-fA-F]{8})', name)
        if m:
            addresses.add(int(m[1], 16))
        for image, entry in self.placements[path]:
            for address in addresses:
                destination = address
                home = self.link_rows.get(entry.get('home'))
                if home and entry['row'] != entry.get('home'):
                    himage, hentry = home
                    bindings = {number(k): number(v) for k, v in entry.get('bindings', {}).items()}
                    if address == number(hentry['vma']) + number(hentry.get('body_offset', 0)):
                        destination = number(entry['vma'])
                    elif address in bindings:
                        destination = bindings[address]
                    else:
                        hits = []
                        for candidate in image.get('entries', []):
                            chome = self.link_rows.get(candidate.get('home'))
                            if chome and number(chome[1]['vma']) + number(chome[1].get('body_offset', 0)) == address:
                                hits.append((chome[0]['image'], number(candidate['vma'])))
                        if number(himage['vma']) <= address < number(himage['vma']) + number(himage['size']):
                            hits = [h for h in hits if h[0] == himage['image']]
                        if len(hits) == 1:
                            destination = hits[0][1]
                        elif len(hits) > 1:
                            continue
                        elif (image.get('layout') and image.get('layout') == himage.get('layout')
                              and number(himage['vma']) <= address < number(himage['vma']) + number(himage['size'])):
                            destination += number(image['vma']) - number(himage['vma'])
                        else:
                            destination = {number(k): number(v) for k, v in image.get('symbols', {}).items()}.get(address, address)
                for d in self.link_starts.get((image['image'], destination), ()):
                    found[(d.path, d.name)] = (d, 'config/link exact entry start in ' + image['image'])
        for address in addresses:
            for c in containers | {M.RESIDENT}:
                for d in self.by_address.get((c, address), ()):
                    key = (d.path, d.name)
                    if d.container == M.RESIDENT:
                        evidence = 'resident C entry / config/names.tsv / SLUS symbol map'
                    elif spaces & self.def_namespaces[key]:
                        evidence = 'exact C entry in the same row address space (container, address minus file offset)'
                    elif key in self.engine and d.container in containers:
                        evidence = 'shared engine C entry in the importing container'
                    else:
                        continue
                    found[key] = (d, evidence)
        return [found[k] for k in sorted(found)]


def main():
    """Export the live declaration census; do not rewrite source or headers."""
    import argparse
    import csv
    from pathlib import Path
    try:
        from . import cscan
    except ImportError:
        import cscan
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[2])
    ap.add_argument('--out', type=Path, required=True)
    args = ap.parse_args()
    corpus = M.Corpus(args.root, src_dirs=tuple('src/' + n for n in M.CONTAINER_OF_TOP))
    for rel in corpus.c_files + corpus.h_files:
        if (corpus.root / rel).stat().st_size > 4 * 1024 * 1024:
            raise ValueError('oversized C input: ' + rel)
    defs, sites, data = M.collect(corpus, M.TypeIndex(corpus))
    declarations = {(x.path, x.line, x.name): x for x in data
                    if x.storage == 'extern' or x.suffix and not x.is_def}
    # Legacy import inventories also occur at block scope in merged TUs.
    for rel in corpus.c_files:
        sc = corpus.scan(rel)
        for match in re.finditer(r'\bextern\s+[^;{}]+;', sc.masked):
            fragment = corpus.text(rel)[match.start():match.end()]
            for item in cscan.scan(fragment).items:
                for d in item.decls:
                    if not d.is_function:
                        line = sc.line_of(match.start())
                        declarations.setdefault((rel, line, d.name), M.DataDecl(
                            d.name, rel, line, match.start(), match.end(), tuple(item.spec), d.ptr,
                            d.suffix, 'extern', len(item.decls), False))
    index = AddressIndex(corpus, defs)
    args.out.mkdir(parents=True, exist_ok=True)
    count = 0
    with (args.out / 'handler_decls.tsv').open('w') as fh:
        writer = csv.writer(fh, delimiter='\t')
        writer.writerow(('symbol', 'declared_type', 'declaration_file', 'line', 'definition_file',
                         'prototype', 'resolution', 'evidence'))
        for x in sorted(declarations.values(), key=lambda d: (d.path, d.line, d.name)):
            targets = index.targets(x.path, x.name)
            if not targets:
                continue
            count += 1
            declaration = 'extern ' + ' '.join(x.spec) + ' ' + '*' * x.ptr + x.name + x.suffix + ';'
            for d, evidence in targets:
                writer.writerow((x.name, declaration, x.path, x.line, d.path, d.proto + ';',
                                 'UNIQUE' if len(targets) == 1 else 'AMBIGUOUS', evidence))
    print(str(count) + ' function-address declaration sites')


if __name__ == '__main__':
    main()
