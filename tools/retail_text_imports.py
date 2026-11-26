"""Check physical text imports against their linkage, declarations and disc.

For standalone imports shorter than sixteen bytes, the digest authenticates
the full sixteen-byte window. The allocation size comes from the records.
Coordinated changes to the length in the coverage row, link list and extern
can pass if they use that same authenticated window.
"""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import re
import sys

sys.path[:0] = [str(Path(__file__).resolve().parent), str(Path(__file__).resolve().parents[1])]

from tools.build.name_inputs import table
from tools.byte_map import RETAIL
from tools.gate import linklist, overlay_native_rodata

CATEGORY = 'imported_retail_text'
TYPE_SIZES = {'u8': 1, 'u32': 4}


def check_native(root, disc_root, ranges):
    manifest = root / 'config/overlays/modules.json'
    modules = json.loads(manifest.read_text())['modules'] if manifest.is_file() else []
    expected, checked, problems = {}, 0, []
    for module in modules:
        try:
            imports = overlay_native_rodata.text_imports(module)
            if not imports:
                continue
            overlay_native_rodata.validate_layout(module)
            container = module['container']
            source = module['source']
            for d, _ in imports:
                key = container, d['foff'], d['size']
                if key in expected:
                    raise ValueError(f'duplicate native text range {key}')
                expected[key] = dict(container=container, foff=d['foff'], size=d['size'],
                                     category=CATEGORY, module=module['key'], source=source,
                                     symbol=d['source_symbol'], canonical=d['symbol'], vma=d['vma'])
            overlay_native_rodata.validate_text_declarations(module, (root / source).read_text(), root)
            disc = disc_root / RETAIL[container]
            if disc.is_file():
                overlay_native_rodata.read_text_imports(module, disc)
                checked += len(imports)
        except (OSError, ValueError, KeyError, TypeError) as error:
            problems.append(f"{module['key']}: {error}")
    for key in sorted(ranges.keys() | expected.keys()):
        if ranges.get(key) != expected.get(key):
            problems.append(f'{key}: native text record differs from module allocation')
    return checked, problems


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

    native_ranges = {key: ranges.pop(key) for key, row in list(ranges.items()) if 'module' in row}
    native_checked, native_problems = check_native(root, disc_root, native_ranges)
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
        hash_size = entry.get('hash_size', size)
        if (path != row.get('link_list') or entry['sha256'] != sha256
                or row.get('hash_size', size) != hash_size
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
                blob = stream.read(hash_size)
            if len(blob) != hash_size or hashlib.sha256(blob).hexdigest() != sha256:
                problems.append(f'{where}: retail bytes differ from recorded hash')
    return len(ranges) + len(native_ranges), checked + native_checked, problems + native_problems
