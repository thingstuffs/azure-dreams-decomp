"""Typed records containing symbolic function/data pointers and scalar fields.

Record layout, C declarations, initializers and the complete relocation inventory
are checked independently. Pointer literals, casts and interior code addresses
cannot substitute for real declarations and registered executable entries.
"""
import re
import struct

SCALARS = {'s16': (2, 'h'), 'u16': (2, 'H'), 's32': (4, 'i'), 'u32': (4, 'I')}


def clean(path):
    return re.sub(r'/\*.*?\*/|//[^\n]*', '', path.read_text(), flags=re.S)


def layout(slot):
    fields = slot['fields']
    cursor = 0
    names = set()
    for field in fields:
        if set(field) != {'name', 'type', 'kind', 'offset'}:
            raise ValueError('descriptor field schema differs')
        if not re.fullmatch(r'[A-Za-z_]\w*', field['name']) or field['name'] in names:
            raise ValueError('invalid/duplicate descriptor field')
        names.add(field['name'])
        kind, typ = field['kind'], field['type']
        if kind == 'scalar':
            if typ not in SCALARS:
                raise ValueError('unsupported descriptor scalar type')
            size = SCALARS[typ][0]
        elif kind in ('function', 'data'):
            if not re.fullmatch(r'[A-Za-z_]\w*', typ):
                raise ValueError('descriptor pointer requires a named typedef')
            size = 4
        else:
            raise ValueError('unsupported descriptor field kind')
        cursor = (cursor + size - 1) & -size
        if field['offset'] != cursor:
            raise ValueError('descriptor field offset/alignment differs')
        cursor += size
    if not any(field['kind'] == 'function' for field in fields):
        raise ValueError('descriptor requires a symbolic callback field')
    if cursor != slot['stride'] or cursor % 4:
        raise ValueError('descriptor record has unowned padding')
    if not slot['records'] or slot['size'] != len(slot['records']) * cursor:
        raise ValueError('descriptor array extent differs')
    if any(len(row) != len(fields) for row in slot['records']):
        raise ValueError('descriptor record arity differs')


def inventory(slot):
    """Return unrelocated scalar bytes and exact (offset, symbol, kind) slots."""
    layout(slot)
    packed = bytearray(slot['size'])
    pointers = []
    for index, row in enumerate(slot['records']):
        for field, value in zip(slot['fields'], row):
            offset = index * slot['stride'] + field['offset']
            if field['kind'] == 'scalar':
                if type(value) is not int:
                    raise ValueError('descriptor scalar is not an integer')
                try:
                    struct.pack_into('<' + SCALARS[field['type']][1], packed, offset, value)
                except struct.error as exc:
                    raise ValueError('descriptor scalar outside declared type') from exc
            elif not isinstance(value, str) or not re.fullmatch(r'[A-Za-z_]\w*', value):
                raise ValueError('descriptor pointer is not a symbolic identifier')
            else:
                pointers.append((offset, value, field['kind']))
    return bytes(packed), pointers


def source_words(slot, root):
    from overlay_native_allocations import source_symbol_pattern
    layout(slot)
    header = clean(root / slot['declaration'])
    fields = slot['fields']
    declaration = r'\s*'.join(re.escape(f['type']) + r'\s+' + re.escape(f['name']) + r'\s*;' for f in fields)
    if not re.search(r'\btypedef\s+struct\s*\{\s*' + declaration + r'\s*\}\s*' + re.escape(slot['type']) + r'\s*;', header):
        raise ValueError('descriptor C record layout differs')
    for field in fields:
        if field['kind'] == 'function':
            if not re.search(r'\btypedef\s+(?:s32|void\s*\*)\s*\(\s*\*\s*' + re.escape(field['type']) + r'\s*\)\s*\(\s*[^()]+\)\s*;', header):
                raise ValueError('descriptor lacks a typed callback contract')
        elif field['kind'] == 'data':
            if not re.search(r'\btypedef\s+(?:const\s+)?(?:u8|char|void)\s*\*\s*' + re.escape(field['type']) + r'\s*;', header):
                raise ValueError('descriptor lacks a typed data pointer')
    text = clean(root / slot['source'])
    found = re.findall(r'\b(?:const\s+)?' + re.escape(slot['type']) + r'\s+' + source_symbol_pattern(slot['symbol'], root) + r'\s*\[\s*([0-9]+)\s*\]\s*=\s*\{((?:[^{}]|\{[^{}]*\})*)\}\s*;', text)
    if len(found) != 1 or int(found[0][0]) != len(slot['records']):
        raise ValueError('descriptor initializer/extent differs')
    body = found[0][1]
    rows = re.findall(r'\{([^{}]*)\}', body)
    if re.sub(r'\{[^{}]*\}|[\s,]', '', body) or len(rows) != len(slot['records']):
        raise ValueError('descriptor initializer records differ')
    for actual, expected in zip(rows, slot['records']):
        values = [v.strip() for v in actual.split(',') if v.strip()]
        if len(values) != len(fields):
            raise ValueError('descriptor source arity differs')
        for field, value, wanted in zip(fields, values, expected):
            if field['kind'] == 'scalar':
                if not re.fullmatch(r'-?(?:0x[0-9a-fA-F]+|[0-9]+)', value) or int(value, 0) != wanted:
                    raise ValueError('descriptor scalar initializer differs')
            elif value != wanted and not re.fullmatch(source_symbol_pattern(wanted, root), value):
                raise ValueError('descriptor symbolic initializer differs')
    return inventory(slot)[0]


def validate(slot, m, root=None):
    if set(slot) != {'kind', 'symbol', 'offset', 'size', 'source', 'type', 'declaration', 'owner', 'fields', 'stride', 'records', 'bounds'}:
        raise ValueError('unsupported descriptor slot fields')
    if not re.fullmatch(r'[A-Za-z_]\w*', slot['type']):
        raise ValueError('invalid descriptor record type')
    _, pointers = inventory(slot)
    functions = {d['symbol'] for d in m['imports'] if d['kind'] == 'function'} | {a['function'] for a in m['members']}
    data = {d['symbol'] for d in m['imports'] if d['kind'] == 'data'}
    for _, target, kind in pointers:
        if target not in (functions if kind == 'function' else data):
            raise ValueError('descriptor pointer lacks its typed import')
    if slot['bounds'] not in m['review_inputs']:
        raise ValueError('descriptor bounds evidence is not fingerprinted')
    if root:
        import json
        proof = json.loads((root / slot['bounds']).read_text())
        expected = dict(symbol=slot['symbol'],stride=slot['stride'],count=len(slot['records']),size=slot['size'])
        if any(proof.get(k) != v for k,v in expected.items()) or not proof.get('basis') or not proof.get('consumers') or not proof.get('references'):
            raise ValueError('complete descriptor bounds evidence differs')
        if any(p not in m['review_inputs'] for p in proof['consumers']):
            raise ValueError('descriptor consumer evidence is not fingerprinted')
        source_words(slot, root)
