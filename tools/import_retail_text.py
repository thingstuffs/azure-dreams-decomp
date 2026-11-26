#!/usr/bin/env python3
"""Move a family of standalone text allocations to disc-backed link entries."""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path
import re
import sys

from build.name_inputs import table
from byte_map import RETAIL
from gate import linklist
from retail_text_imports import CATEGORY, TYPE_SIZES

FAMILIES = {
    'dreamin': 'src/dungeon/monster/dreamin/',
    'killer': 'src/dungeon/monster/killer/',
    'zu': 'src/dungeon/monster/zu/',
    'garuda': 'src/dungeon/monster/garuda/',
    'mandara': 'src/dungeon/monster/mandara/',
    'tyrant': 'src/dungeon/monster/tyrant/',
    'picket': 'src/dungeon/monster/picket/',
    'devkit': 'src/town/scene/resource/',
}
TEXT_KINDS = {'text', 'message', 'message_text', 'message_with_tail', 'asset_path'}
MIXED_TEXT_ROWS = {
    'src/dungeon/monster/killer/is_psyched_up_message_slot_g.c',
    'src/dungeon/monster/mandara/texture_rect_table_slot_g.c',
}
DEFINITION = re.compile(
    r'const\s+(u8|u32)\s+(\w+)\s*\[\s*(\d+)\s*\]\s*'
    r'(?:__attribute__\(\(aligned\(4\)\)\)\s*)?=\s*([\s\S]+);\s*\Z'
)


def read_records(path):
    return [json.loads(line) for line in path.read_text().splitlines()
            if line.strip() and not line.startswith('#')]


def without_rows(path, key, retired, family=None):
    lines = path.read_text().splitlines(keepends=True)
    keep = []
    removed = Counter()
    for line in lines:
        if line.strip() and not line.startswith('#'):
            row = json.loads(line)
            value = row.get(key)
            rid = f'{family}/{value}' if family is not None else value
            if rid in retired:
                removed[rid] += 1
                continue
        keep.append(line)
    if removed != Counter(retired):
        raise ValueError(f'{path.name}: expected exactly one record per retired row')
    return ''.join(keep)


def link_document(row, link):
    kind = row['container']
    counts = dict.fromkeys(linklist.CENSUS_LABELS, 0)
    counts['proven_data'] = row['size']
    entry = dict(kind='data', foff=hex(row['foff']), size=row['size'],
                 type=linklist.RETAIL_TEXT, evidence='ledger/coverage_regions.jsonl',
                 sha256=row['retail_sha256'], extractor='container-slice-v1',
                 symbols={row['canonical']: hex(row['vma'])})
    doc = dict(schema=linklist.MAP_SCHEMA, image=link, container=kind,
               foff=entry['foff'], size=entry['size'], vma=hex(row['vma']),
               evidence='Disc-backed text allocation', entries=[entry], census=counts)
    linklist.validate_image(doc)
    return json.dumps(doc, indent=2) + '\n'


def convert(root, family):
    paths = {row['id']: row['path'] for row in read_records(root / 'ledger/layout.jsonl')}
    rows_file = root / 'ledger/rows.jsonl'
    selected = []
    for row in read_records(rows_file):
        rel = paths.get(row['id'], '')
        if rel.startswith(FAMILIES[family]) and (row.get('data_kind') in TEXT_KINDS
                or rel in MIXED_TEXT_ROWS):
            selected.append((row, root / rel))
    if not selected:
        raise ValueError(f'no compiled text rows for {family}')

    container, = {row['container'] for row, _ in selected}
    retired = {row['id'] for row, _ in selected}
    header = root / 'include' / container / 'data.h'
    header_text, marker = header.read_text().rsplit('#endif', 1)
    names_path = root / 'config/names.tsv'
    names = table(names_path)
    ledger_path = root / 'ledger/coverage_regions.jsonl'
    additions, aliases, declarations, pending = [], [], [], {}
    registered = linklist.load(root)[2]
    blob_path = root / RETAIL[container]

    with blob_path.open('rb') as blob:
        for current, source in selected:
            match = DEFINITION.search(source.read_text())
            if match is None or current['id'] in registered:
                raise ValueError(f'{current["id"]}: expected a standalone data definition')
            ctype, definition, elements, _ = match.groups()
            canonical = names.get(definition, definition)
            if not re.fullmatch(r'D_[0-9A-F]{8}', canonical):
                raise ValueError(f'{current["id"]}: definition lacks a canonical data address')
            vma = int(canonical[2:], 16)
            size, offset = current['size'], current['foff']
            name = source.stem if definition == canonical or family == 'devkit' else definition
            if (canonical != current['true_name'] or int(elements) * TYPE_SIZES[ctype] != size
                    or names.get(name, canonical) != canonical
                    or re.search(r'\b' + re.escape(name) + r'\b', header_text)):
                raise ValueError(f'{current["id"]}: old extent or new symbol conflicts')
            if name not in names:
                aliases.append(f'0x{vma:08X}\t{canonical}\t{name}\tDisc-backed data at {container.upper()} +0x{offset:X}')
                names[name] = canonical
            blob.seek(offset)
            payload = blob.read(size)
            if len(payload) != size:
                raise ValueError(f'{current["id"]}: disc extent is truncated')
            image = f'{container}/text_{offset:x}'
            link = f'config/link/{image}.json'
            if (root / link).exists():
                raise ValueError(f'{current["id"]}: link view already exists')
            record = dict(container=container, foff=offset, size=size, category=CATEGORY,
                          vma=vma, symbol=name, canonical=canonical,
                          header=header.relative_to(root).as_posix(), c_type=ctype,
                          elements=int(elements), link_list=link,
                          retail_sha256=hashlib.sha256(payload).hexdigest())
            pending[root / link] = link_document(record, image)
            declarations.append(f'extern const {ctype} {name}[{elements}];')
            additions.append(record)

    pending[rows_file] = without_rows(rows_file, 'id', retired)
    for file in ('layout', 'levels', 'modules'):
        path = root / f'ledger/{file}.jsonl'
        pending[path] = without_rows(path, 'id', retired)
    splits = root / f'ledger/splits/{container}.jsonl'
    pending[splits] = without_rows(splits, 'func_vram', retired, container)
    owners = root / f'config/overlays/{container}.rodata_owners.jsonl'
    if owners.is_file():
        registered_owners = {row['id'] for row in read_records(owners)} & retired
        pending[owners] = without_rows(owners, 'id', registered_owners)
    label = '/* Disc-backed text allocations. */'
    if label in header_text:
        header_text, previous = header_text.rsplit(label, 1)
        declarations.extend(previous.strip().splitlines())
    pending[header] = (header_text.rstrip() + '\n\n' + label + '\n'
                       + '\n'.join(sorted(declarations)) + '\n\n#endif' + marker)
    if aliases:
        pending[names_path] = names_path.read_text().rstrip('\n') + '\n' + '\n'.join(aliases) + '\n'
    pending[ledger_path] = ledger_path.read_text() + ''.join(
        json.dumps(row, separators=(',', ':')) + '\n' for row in additions
    )

    for path, text in pending.items():
        path.write_text(text)
    for _, source in selected:
        source.unlink()
    print(f'{family}: {len(selected)} allocations, {sum(row["size"] for row in additions)} bytes')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('family', choices=FAMILIES)
    parser.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[1])
    args = parser.parse_args()
    try:
        convert(args.root.resolve(), args.family)
    except (OSError, ValueError, KeyError) as error:
        parser.exit(1, f'{error}\n')


if __name__ == '__main__':
    main()
