"""Check physical text imports against their linkage, declarations and disc."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import re
import sys

sys.path[:0] = [str(Path(__file__).resolve().parent), str(Path(__file__).resolve().parents[1])]

from tools.build.name_inputs import table
from tools.byte_map import RETAIL
from tools.gate import linklist

CATEGORY = 'imported_retail_text'
TYPE_SIZES = {'u8': 1, 'u32': 4}


def check(root, disc_root=None):
    root = Path(root)
    disc_root = root if disc_root is None else Path(disc_root)
    ledger = root / 'ledger/coverage_regions.jsonl'
    ranges = {}
    if ledger.is_file():
        for line in ledger.read_text().splitlines():
            if line.strip() and not line.startswith('#'):
                row = json.loads(line)
                if row.get('category') == CATEGORY:
                    key = row['container'], row['foff'], row['size']
                    if key in ranges:
                        return len(ranges), 0, [f'duplicate text range {key}']
                    ranges[key] = row

    imports = {}
    for image in linklist.load(root)[0].values():
        for entry in image['entries']:
            if entry.get('type') != linklist.RETAIL_TEXT:
                continue
            key = image['container'], entry['foff'], entry['size']
            if key in imports:
                return len(ranges), 0, [f'duplicate text import {key}']
            imports[key] = (Path(image['path']).relative_to(root).as_posix(), entry)

    compiled_data = set()
    for container in {key[0] for key in imports}:
        path = root / f'config/overlays/{container}.rodata_owners.jsonl'
        if path.is_file():
            for line in path.read_text().splitlines():
                if line.strip() and not line.startswith('#'):
                    compiled_data.add((container, linklist.num(json.loads(line)['foff'])))
    names = table(root / 'config/names.tsv')
    headers, checked, problems = {}, 0, []
    for key in sorted(imports.keys() | ranges.keys()):
        container, offset, size = key
        where = f'{container} +0x{offset:X} ({size} bytes)'
        if (container, offset) in compiled_data:
            problems.append(f'{where}: import still has a compiled rodata owner')
        if key not in imports or key not in ranges:
            problems.append(f'{where}: missing link import or coverage record')
            continue
        row = ranges[key]
        path, entry = imports[key]
        symbol, canonical = row.get('symbol', ''), row.get('canonical', '')
        sha256 = row.get('retail_sha256')
        if (path != row.get('link_list') or entry['sha256'] != sha256
                or canonical not in entry['symbols']
                or linklist.num(entry['symbols'][canonical]) != row.get('vma')
                or names.get(symbol) != canonical):
            problems.append(f'{where}: link import or name binding differs from coverage record')
        header = f'include/{container}/data.h'
        ctype, elements = row.get('c_type'), row.get('elements')
        if (container not in RETAIL or header != row.get('header') or ctype not in TYPE_SIZES
                or type(elements) is not int or TYPE_SIZES[ctype] * elements != size
                or not re.fullmatch(r'[A-Za-z_]\w*', symbol)):
            problems.append(f'{where}: invalid typed extern record')
            continue
        if header not in headers:
            candidate = root / header
            headers[header] = candidate.read_text() if candidate.is_file() else ''
        declaration = rf'^\s*extern\s+const\s+{ctype}\s+{symbol}\s*\[\s*{elements}\s*\]\s*;'
        if len(re.findall(declaration, headers[header], re.M)) != 1:
            problems.append(f'{where}: missing or repeated extern declaration for {symbol}')
        disc = disc_root / RETAIL[container]
        if disc.is_file():
            checked += 1
            with disc.open('rb') as stream:
                stream.seek(offset)
                blob = stream.read(size)
            if len(blob) != size or hashlib.sha256(blob).hexdigest() != sha256:
                problems.append(f'{where}: retail bytes differ from recorded hash')
    return len(ranges), checked, problems
