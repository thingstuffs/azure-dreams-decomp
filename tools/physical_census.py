#!/usr/bin/env python3
"""Count disjoint physical byte ownership from the ledgers and matching disc files."""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
import hashlib
import json
from pathlib import Path
import re
import struct
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path[:0] = [str(ROOT), str(ROOT / "tools")]
from tools import coverage as C
from tools.byte_map import RETAIL, load_maps
from tools.retail_text_imports import check as check_text_imports
from tools.monster_bank_loads import intervals as monster_bank_intervals

MAP_SECTION = re.compile(r'^(\.\S+)\s+0x([0-9a-fA-F]+)\s+0x([0-9a-fA-F]+)'
                         r'(?:\s+load address 0x([0-9a-fA-F]+))?\s*$')
MAP_INPUT = re.compile(r'^\s+(?:(\.\S+)\s+)?0x([0-9a-fA-F]+)\s+0x([0-9a-fA-F]+)'
                       r'\s+(build/\S+\.o)\s*$')
CLASSES = (*sorted(C.RETAIL_RESIDUE_CATEGORIES), 'c_text', 'c_data', 'proven_c_copy',
           'sdk_asm', 'hand_asm', 'linked_asset', 'verified_asset', 'verified_zero_padding',
           'monster_bank_transfer')


def slus_spans(map_text, retail):
    """Validate the emitted map coordinates against the PS-X EXE's load header."""
    if not retail.startswith(b'PS-X EXE') or len(retail) < 0x800:
        raise ValueError('invalid SLUS executable header')
    base, size = struct.unpack_from('<II', retail, 0x18)
    if not 0 < size <= len(retail) - 0x800:
        raise ValueError('SLUS header load size differs')
    marker = 'Linker script and memory map\n'
    if marker not in map_text:
        raise ValueError('SLUS input is missing the emitted link map')
    totals = defaultdict(list)
    output = section = None
    seen = set()
    for line in map_text.split(marker, 1)[1].splitlines():
        if line.startswith('.'):
            output = line.split()[0]
            if output == '._800':
                layout = MAP_SECTION.fullmatch(line)
                if not layout or tuple(int(item, 16) for item in layout.groups()[1:]) != (base, len(retail)-0x800, 0x800):
                    raise ValueError('SLUS map load bounds differ from the disc')
                if output in seen:
                    raise ValueError('more than one SLUS load section')
                seen.add(output)
        if output != '._800':
            continue
        match = MAP_INPUT.fullmatch(line)
        if not match:
            section = line.strip() if re.fullmatch(r'\s+\.\S+\s*', line) else None
            continue
        kind, address, length, path = match.groups()
        kind = kind or section
        section = None
        address, length = int(address, 16), int(length, 16)
        if not length:
            continue
        offset = address - base + 0x800
        if not kind or not 0x800 <= offset < offset+length <= len(retail):
            raise ValueError('SLUS map input has missing section or exceeds the executable')
        if offset+length > 0x800+size:
            continue  # Padding or reserved bytes beyond the PS-X EXE's load size.
        if path.startswith('build/src/'):
            label = 'c_text' if kind == '.text' or kind.startswith('.text.') else 'c_data'
        elif path.startswith('build/asm/psyq/'):
            label = 'sdk_asm'
        elif path.startswith('build/asm/'):
            label = 'hand_asm'
        elif path.startswith(('build/assets/', 'build/module_assets/')):
            label = 'linked_asset'
        else:
            raise ValueError(f'unknown SLUS map input {path}')
        totals[label].append([offset, offset+length])
    spans = [interval for ranges in totals.values() for interval in ranges]
    if not totals['c_text'] or C.size(spans) != sum(b-a for a,b in spans):
        raise ValueError('SLUS map input allocations overlap or C text is absent')
    return totals


def leaves(images, image):
    for entry in images[image]['entries']:
        if entry.get('kind') == 'image':
            yield from leaves(images, entry['ref'])
        else:
            yield entry


def partition(size, classes):
    """Classify in specificity order and require each byte to contribute once."""
    occupied, classes_out = [], {}
    for label in CLASSES:
        candidates = classes.get(label, [])
        if any(not 0 <= low < high <= size for low, high in candidates):
            raise ValueError(f'{label}: extent outside its physical container')
        own = C.subtract(candidates, occupied)
        classes_out[label] = own
        occupied = C.merge(occupied + own)
    return classes_out, C.subtract([[0, size]], occupied)


def census(root, slus_map, slus_image, disc_root=None):
    root = Path(root)
    disc_root = root if disc_root is None else Path(disc_root)
    _, _, problems = check_text_imports(root, disc_root=disc_root)
    if problems:
        raise ValueError(problems[0])
    rows = C.records(root / 'ledger/rows.jsonl')
    regions = C.records(root / 'ledger/coverage_regions.jsonl')
    latest_regions = C.latest_regions(regions)
    residue = C.retail_residue_regions(regions)
    instances = {(r['container'], r['foff'], r['size']): r
                 for r in C.records(root / 'ledger/instances.jsonl')}
    containers = {r['container']: (r['bytes'], r['retail_sha1'])
                  for r in C.records(root / 'ledger/containers.jsonl')}
    containers['slus'] = (524288, (root/'config/slus_006.14.sha1').read_text().split()[0])
    images = load_maps(root, 'link')[0]
    views = json.loads((root/'link/physical_roots.json').read_text())
    native = C.module_data_ranges(root)
    placement_paths = load_maps(root)[0].values()
    slus_retail = (disc_root / RETAIL['slus']).read_bytes()
    result = {}
    for container, (expected_size, expected_sha1) in sorted(containers.items()):
        retail = slus_retail if container == 'slus' else (disc_root / RETAIL[container]).read_bytes()
        if len(retail) != expected_size or hashlib.sha1(retail).hexdigest() != expected_sha1:
            raise ValueError(f'{container}: disc input differs from the registered container')
        classes, imports, placements = defaultdict(list), [], []
        maps = sorted((images[id_] for id_ in views if images[id_]['container'] == container),
                      key=lambda view: view['foff'])
        cursor = 0
        map_entries = []
        for doc in maps:
            if doc['foff'] != cursor:
                raise ValueError(f'{container}: physical roots overlap or leave a gap')
            map_entries.extend(leaves(images, doc['image']))
            cursor += doc['size']
        if cursor != len(retail):
            raise ValueError(f'{container}: physical roots omit part of the container')
        for entry in map_entries:
            start, end = C.extent(entry)
            if entry.get('sha256'):
                if hashlib.sha256(retail[start:end]).hexdigest() != entry['sha256']:
                    raise ValueError(f'{container} +0x{start:X}: map range SHA-256 differs')
                if entry.get('extractor'):
                    classes['verified_asset'].append([start, end])
                    imports.append([start, end])
            if entry.get('kind') == 'padding' and not any(retail[start:end]):
                classes['verified_zero_padding'].append([start, end])

        if container == 'dungeon':
            pending = [C.extent(entry) for entry in map_entries
                       if entry.get('kind') == 'data' and entry.get('type') == 'typing pending']
            transfers = monster_bank_intervals(root, retail, slus_retail)
            classes['monster_bank_transfer'] = C.intersection(transfers, pending)

        for record in residue:
            if record['container'] == container:
                span = C.extent(record)
                if 'retail_sha256' in record:
                    start, end = span
                    if hashlib.sha256(retail[start:end]).hexdigest() != record['retail_sha256']:
                        raise ValueError(f'{container} +0x{start:X}: classified range SHA-256 differs')
                classes[record['category']].append(span)
                if record['category'] == 'imported_retail_text':
                    imports.append(span)
        if container == 'slus':
            if Path(slus_image).read_bytes() != retail:
                raise ValueError('linked SLUS does not equal the disc executable')
            classes.update(slus_spans(Path(slus_map).read_text(), retail))
        else:
            text, data, alignment = C.overlay_c_ranges(rows, container, native)
            classes['c_text'], classes['c_data'] = text, data
            for start, end in alignment:
                if any(retail[start:end]):
                    raise ValueError(f'{container} +0x{start:X}: native alignment was not zero-filled')
            classes['verified_zero_padding'].extend(alignment)
            for entry in rows:
                if entry['container'] == container and entry.get('foff') is not None and entry.get('source_row'):
                    placements.append(C.extent(entry))
            for doc in placement_paths:
                if doc['container'] == container:
                    placements.extend(C.extent(r) for r in doc['entries']
                                      if r.get('row') and r['row'] != r['home'])
            for (c, off, size), record in instances.items():
                if c == container and record.get('result') == 'proven' and (
                        c, off, size, 'instance_excluded') not in latest_regions:
                    classes['proven_c_copy'].append([off, off+size])
            for record in latest_regions.values():
                if record['container'] == container and record['category'] == 'sdk_asm':
                    classes['sdk_asm'].append(C.extent(record))

        owned, unknown = partition(len(retail), classes)
        unknown_reasons = Counter()
        by_kind = defaultdict(list)
        names = {'data': 'typing_pending', 'unresolved': 'no_evidence_label',
                 'code_region': 'code_candidate', 'padding': 'unverified_padding'}
        for entry in map_entries:
            by_kind[names.get(entry.get('kind'), 'other')].append(C.extent(entry))
        for reason, spans in by_kind.items():
            count = C.size(C.intersection(spans, unknown))
            if count:
                unknown_reasons[reason] = count
        if sum(unknown_reasons.values()) != C.size(unknown):
            raise ValueError(f'{container}: incomplete unknown byte accounting')
        counts = {label: C.size(spans) for label, spans in owned.items()}
        counts['unclassed'] = C.size(unknown)
        c_bytes = owned['c_text'] + owned['c_data']
        result[container] = dict(
            file_bytes=len(retail), classes=counts,
            c_placement_bytes=C.size(C.intersection(placements, c_bytes)),
            imported_by_class={label: n for label, spans in owned.items()
                               if (n := C.size(C.intersection(spans, imports)))},
            unclassed_by_reason=dict(sorted(unknown_reasons.items())),
        )
    return result


def table(report):
    names = sorted(report)
    labels = ['file_bytes', *CLASSES, 'unclassed', 'c_placement_bytes']
    lines = ['class\t' + '\t'.join(names) + '\ttotal']
    for label in labels:
        values = [report[c].get(label, report[c]['classes'].get(label, 0)) for c in names]
        lines.append(label + '\t' + '\t'.join(map(str, (*values, sum(values)))))
    return '\n'.join(lines) + '\n'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=ROOT)
    parser.add_argument('--disc-root', type=Path, help='root of the extracted disc paths (defaults to --root)')
    parser.add_argument('--slus-map', type=Path, required=True)
    parser.add_argument('--slus-image', type=Path, required=True)
    parser.add_argument('--json', action='store_true', help='include import and unclassified totals by reason')
    args = parser.parse_args()
    try:
        report = census(args.root.resolve(), args.slus_map, args.slus_image, args.disc_root)
    except (OSError, ValueError, KeyError, TypeError) as error:
        parser.exit(1, f'physical census: {error}\n')
    print(json.dumps(report, indent=2) if args.json else table(report), end='\n' if args.json else '')


if __name__ == '__main__':
    main()
