"""Derive classified decoded import ranges without recording their bytes."""
import csv
import hashlib
import re
import struct


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

    starts = {number(image['symbols'][symbol]) - base for symbol in layout['text_symbols']}
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

    return [(a, b - a, kind, range_digest(data[a:b])) for a, b, kind in sorted(typed)]


SHORT_RANGE = 16


def range_digest(extent):
    """Digest of an imported range; ranges under 16 bytes carry '-' (a short digest would hold the bytes)."""
    return hashlib.sha256(extent).hexdigest() if len(extent) >= SHORT_RANGE else '-'


def valid_digest(size, sha):
    if size < SHORT_RANGE:
        return sha == '-'
    return re.fullmatch('[0-9a-f]{64}', sha) is not None


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
