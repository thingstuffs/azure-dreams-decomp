"""Derive classified decoded import ranges without recording their bytes."""
import csv
import struct

from tools.decoded.extents import extent_digest, valid_digest


CLASSES = ('code', 'text', 'alignment', 'data')
FIELDS = ('offset', 'size', 'class', 'sha256')


def owned_ranges(image, number):
    base = number(image['address'])
    return sorted((number(section['address']) - base,
                   number(section['address']) - base + number(section['size']))
                  for unit in image['units'] for section in unit['functions'] + unit.get('data', []))


def gaps(spans, size):
    cursor = 0
    for start, end in sorted(spans) + [(size, size)]:
        if start < cursor or end < start or end > size:
            raise ValueError('overlapping or out-of-bounds decoded import layout')
        if cursor < start:
            yield cursor, start
        cursor = end


def coalesce(spans):
    result = []
    for start, end in sorted(spans):
        if result and result[-1][1] == start:
            result[-1] = result[-1][0], end
        else:
            result.append((start, end))
    return result


def text_targets(image, number):
    layout = image['import_layout']
    targets = {(None, name): number(image['symbols'][name]) for name in layout['text_symbols']}
    placements = {u['placement']: u for u in image['units'] if 'placement' in u}
    for item in layout.get('text_placements', []):
        placement, name = item['placement'], item['symbol']
        targets[placement, name] = number(placements[placement]['bindings'][name])
    return targets


def derive(image, data, number):
    base, size = number(image['address']), number(image['size'])
    if len(data) != size:
        raise ValueError('decoded import input size differs')
    layout = image['import_layout']
    code_start, code_end = map(number, layout['code'])
    if not 0 <= code_start < code_end <= size or code_start % 4 or code_end % 4:
        raise ValueError('invalid decoded executable extent')

    owned = owned_ranges(image, number)
    for unit in image['units']:
        for function in unit['functions']:
            start = number(function['address']) - base
            if not code_start <= start < start + number(function['size']) <= code_end:
                raise ValueError('owned function outside decoded executable extent')
        for section in unit.get('data', []):
            start = number(section['address']) - base
            if start < code_end and start + number(section['size']) > code_start:
                raise ValueError('owned data inside decoded executable extent')

    starts = {address - base for address in text_targets(image, number).values()}
    sections = {(u['source'], d['section']): d
                for u in image['units'] for d in u.get('data', [])}
    for table in layout['text_tables']:
        section = sections[table['source'], table['section']]
        start = number(section['address']) - base + number(table['offset'])
        count, stride = number(table['count']), number(table['stride'])
        fields = tuple(map(number, table['pointers']))
        if (number(table['offset']) < 0 or count <= 0 or stride <= 0 or stride % 4
                or start % 4 or start + count * stride > number(section['address']) - base + number(section['size'])
                or not fields or any(field % 4 or not 0 <= field <= stride - 4 for field in fields)):
            raise ValueError('invalid decoded string pointer table')
        for row in range(start, start + count * stride, stride):
            starts.update(struct.unpack_from('<I', data, row + field)[0] - base for field in fields)

    typed = []
    for a, b in gaps(owned, size):
        start, end = max(code_start, a), min(code_end, b)
        if start < end:
            typed.append((start, end, 'code'))
    for start in starts:
        if not 0 <= start < size:
            raise ValueError('decoded string pointer outside image')
        end = data.find(b'\0', start)
        if end < 0:
            raise ValueError('unterminated decoded text')
        if start < code_end and end + 1 > code_start:
            raise ValueError('decoded string overlaps executable extent')
        typed.append((start, end + 1, 'text'))

    for start, end in gaps(owned + [(a, b) for a, b, _ in typed], size):
        pad_limit = (start + 3) & ~3
        kind = 'alignment' if end == pad_limit and not any(data[start:end]) else 'data'
        typed.append((start, end, kind))

    return [(a, b - a, kind, extent_digest(data[a:b])) for a, b, kind in sorted(typed)]


def read_table(path):
    result = []
    with path.open(newline='') as source:
        rows = csv.DictReader(source, delimiter='\t')
        if tuple(rows.fieldnames or ()) != FIELDS:
            raise ValueError('invalid decoded import range header')
        for row in rows:
            start, size, kind, sha = int(row['offset'], 16), int(row['size']), row['class'], row['sha256']
            if size <= 0 or kind not in CLASSES or not valid_digest(size, sha):
                raise ValueError('invalid decoded import range')
            if result and start < result[-1][0] + result[-1][1]:
                raise ValueError('unsorted or overlapping decoded import ranges')
            result.append((start, size, kind, sha))
    return result


def audit(image, rows, number, *, data=None):
    total = {kind: 0 for kind in CLASSES}
    for _, size, kind, _ in rows:
        total[kind] += size
    imported = coalesce((start, start + size) for start, size, _, _ in rows)
    if imported != list(gaps(owned_ranges(image, number), number(image['size']))):
        raise ValueError('decoded import table does not cover exactly the imported ranges')
    if total != image['import_classes']:
        raise ValueError(f'decoded import totals differ: {total}')
    if data is not None and rows != derive(image, data, number):
        raise ValueError('decoded import table differs from the derived ranges')
    return total


def write_table(rows, stream):
    writer = csv.writer(stream, delimiter='\t', lineterminator='\n')
    writer.writerow(FIELDS)
    writer.writerows((f'{start:#06x}', size, kind, sha) for start, size, kind, sha in rows)

def audit_holds(path, image, rows, number):
    """Each imported function lies wholly within an unowned executable interval."""
    start, end = map(number, image['import_layout']['code'])
    unowned = [(max(a, start), min(b, end))
               for a, b in gaps(owned_ranges(image, number), number(image['size']))
               if max(a, start) < min(b, end)]
    code = [(a, a + size) for a, size, kind, _ in rows if kind == 'code']
    held = []
    with path.open(newline='') as source:
        table = csv.DictReader(source, delimiter='\t')
        if table.fieldnames != ['offset', 'size', 'reason', 'first_difference']:
            raise ValueError('invalid decoded function hold header')
        for row in table:
            offset, size = int(row['offset'], 16), int(row['size'])
            difference = row['first_difference']
            if (offset % 4 or size <= 0 or size % 4 or not row['reason'].strip()
                    or (held and offset < held[-1][1])):
                raise ValueError('invalid decoded function hold')
            if difference != '-':
                first = int(difference, 16)
                if first % 4 or not offset <= first < offset + size:
                    raise ValueError('first difference outside decoded function hold')
            held.append((offset, offset + size))
    if coalesce(held) != unowned or coalesce(code) != unowned:
        raise ValueError('function holds differ from imported executable ranges')
    return len(held)


def audit_references(image, objects, aliases, data, number):
    """Prove the listed text uses against emitted relocations and their linked disc operands."""
    layout = image['import_layout']
    base = number(image['address'])
    units = {u['source']: u for u in image['units'] if 'placement' not in u}
    text = {(place, aliases.get(name, name)): address
            for (place, name), address in text_targets(image, number).items()}
    tables = {table['symbol']: table for table in layout['text_tables']}
    table_addresses = {}
    for name, table in tables.items():
        section = next(s for s in units[table['source']]['data'] if s['section'] == table['section'])
        table_addresses[aliases.get(name, name)] = (name, number(section['address']) + number(table['offset']))
    seen_text, seen_tables = set(), set()
    for unit in image['units']:
        source = unit['source']
        if source not in objects:
            continue
        obj = objects[source]
        functions = {'.text.' + f.get('symbol', f['name']): number(f['address']) - base
                     for f in unit['functions']}
        sections = dict(functions)
        sections.update({s['section']: number(s['address']) - base for s in unit.get('data', [])})
        for section, offset, kind, (target_type, name), addend in obj.relocs:
            if section not in sections or target_type != 'sym':
                continue
            if kind not in ('HI16', 'LO16', '32'):
                continue
            key = unit.get('placement'), name
            table = table_addresses.get(name) if section in functions else None
            if table is None and key not in text:
                continue
            address = table[1] if table else text[key]
            target = (address + addend) & 0xffffffff
            word, = struct.unpack_from('<I', data, sections[section] + offset)
            if kind == 'HI16':
                target = (target + 0x8000) >> 16
            mask = 0xffffffff if kind == '32' else 0xffff
            if (word ^ target) & mask:
                raise ValueError('text relocation differs for ' + name)
            if kind != 'HI16':
                if table:
                    seen_tables.add(table[0])
                elif addend == 0:
                    seen_text.add(key)
    if seen_text != text.keys() or seen_tables != tables.keys():
        raise ValueError('decoded text symbol or pointer table lacks a compiled reference: ' +
                         ', '.join(sorted({k[1] for k in text.keys() - seen_text} | (tables.keys() - seen_tables))))
    for name, table in tables.items():
        source, section = table['source'], table['section']
        obj = objects[source]
        start = number(table['offset'])
        if name not in obj.symbols or obj.symbols[name][:2] != (section, start):
            raise ValueError('decoded text table does not start at its defined symbol')
        section_offset = next(number(s['address']) - base for s in units[source]['data'] if s['section'] == section)
        bank = table['bank']
        bank_address = number(image['symbols'][bank])
        relocs = {(sec, off): (kind, target, addend) for sec, off, kind, target, addend in obj.relocs}
        for i in range(number(table['count'])):
            for field in table['pointers']:
                offset = start + i * number(table['stride']) + number(field)
                kind, target, addend = relocs.get((section, offset), (None, None, 0))
                value, = struct.unpack_from('<I', data, section_offset + offset)
                if (kind != '32' or target != ('sym', aliases.get(bank, bank)) or
                        value != bank_address + addend):
                    raise ValueError('decoded text table lacks its linked text relocation')
