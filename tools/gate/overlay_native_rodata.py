"""Native entry/switch heads and replayable GNU-as tail-padding evidence.

This supports typed native objects and compiler-emitted tables in the TU.
It grants neither membership nor ownership of external objects.
"""
import hashlib
import importlib.util
import re
import struct


def digest(data):
    return hashlib.sha256(data).hexdigest()


def validate_layout(m):
    ds = m['owned_data']
    first = m['members'][0]
    cursor = first['foff']
    vma = first['vma']
    owners = {a['function'] for a in m['members']}
    for i, d in enumerate(ds):
        if (d['section'] != '.rodata' or d['foff'] != cursor or d['vma'] != vma
                or d['size'] <= 0 or d['size'] % 4):
            raise ValueError('invalid owned rodata layout')
        kind = d['kind']
        if i == 0:
            if (kind != 'typed_function_pointer' or d['size'] != 4
                    or d.get('target') not in owners or not d.get('symbol')):
                raise ValueError('native entry must target a complete native member')
        elif kind in ('typed_string', 'message_bytes', 'rectangle_records'):
            literal_bytes(d)
            if not d.get('symbol'):
                raise ValueError('typed native object lacks its symbol')
        elif kind == 'direction_offsets':
            direction_bytes(d)
            if not d.get('symbol'):
                raise ValueError('direction table lacks its native symbol')
        elif kind == 'alignment':
            alignment = d.get('alignment')
            if (alignment not in (8, 16) or d['size'] != (-vma % alignment)
                    or i + 1 == len(ds) or ds[i + 1]['kind'] != 'switch_table'
                    or d.get('symbol')):
                raise ValueError('not minimal switch-table alignment')
        elif kind == 'switch_table':
            if d.get('owner') not in owners or d.get('symbol'):
                raise ValueError('switch-table owner outside module')
        else:
            raise ValueError('unsupported native rodata record')
        cursor += d['size']
        vma += d['size']
    prefix = cursor - first['foff']
    if (first.get('body_offset') != prefix or prefix >= first['size']
            or any(a.get('body_offset', 0) for a in m['members'][1:])):
        raise ValueError('owned prefix/code coverage differs')
    if not m.get('membership_evidence'):
        raise ValueError('data module requires strong membership evidence')


def direction_bytes(d):
    """Eight native grid-direction pairs: signed x, unsigned y at 16 bits each."""
    pairs = d.get('pairs')
    if (d.get('size') != 32 or not isinstance(pairs, list) or len(pairs) != 8
            or any(not isinstance(p, list) or len(p) != 2
                   or any(type(v) is not int for v in p)
                   or not -32768 <= p[0] <= 32767 or not 0 <= p[1] <= 65535
                   for p in pairs)):
        raise ValueError('invalid typed eight-direction offset table')
    return b''.join(struct.pack('<hH', *p) for p in pairs)



def message_payload(d):
    """NUL-terminated Shift-JIS text, minimally padded to a word boundary.

    Text records preserve Unicode text; byte records preserve the game's encoded
    message spelling. Neither is a literal blob: both must be valid, nonempty,
    round-trippable Shift-JIS with no embedded terminator or control characters.
    """
    if d.get('encoding') != 'shift_jis':
        raise ValueError('unsupported native message encoding')
    if d['kind'] == 'typed_string':
        text = d.get('text')
        if not isinstance(text, str):
            raise ValueError('invalid typed native string')
        try:
            payload = text.encode('shift_jis', errors='strict')
        except UnicodeError as exc:
            raise ValueError('invalid typed native string encoding') from exc
    else:
        codes = d.get('bytes')
        if (not isinstance(codes, list) or not codes
                or any(type(v) is not int or not 1 <= v <= 255 for v in codes)):
            raise ValueError('invalid encoded native message bytes')
        payload = bytes(codes)
        try:
            text = payload.decode('shift_jis', errors='strict')
        except UnicodeError as exc:
            raise ValueError('invalid native message encoding') from exc
    if (not text or any(ord(c) < 32 or 127 <= ord(c) < 160 for c in text)
            or payload.decode('shift_jis', errors='strict') != text
            or text.encode('shift_jis', errors='strict') != payload):
        raise ValueError('invalid native message text')
    packed = payload + b'\0'
    packed += b'\0' * (-len(packed) % 4)
    if type(d.get('size')) is not int or d['size'] != len(packed):
        raise ValueError('native message must use minimal terminator/padding')
    return packed


def rectangle_bytes(d):
    """Eight PSX texture rectangles: unsigned 16-bit x,y,width,height.

    Validate the VRAM coordinate domain, positive dimensions and bounds;
    an arbitrary eight-by-four halfword array is not a rectangle table.
    """
    records = d.get('rectangles')
    if (d.get('size') != 64 or not isinstance(records, list) or len(records) != 8
            or any(not isinstance(r, list) or len(r) != 4
                   or any(type(v) is not int for v in r)
                   or not (0 <= r[0] < 1024 and 0 <= r[1] < 512
                           and 0 < r[2] <= 1024 - r[0]
                           and 0 < r[3] <= 512 - r[1]) for r in records)):
        raise ValueError('invalid typed eight-rectangle VRAM table')
    return b''.join(struct.pack('<4H', *r) for r in records)


def literal_bytes(d):
    if d['kind'] in ('typed_string', 'message_bytes'):
        return message_payload(d)
    if d['kind'] == 'rectangle_records':
        return rectangle_bytes(d)
    raise ValueError('unsupported typed native literal')


def validate_switch_assembly(m, assembly):
    """Account for rodata directives in the one, canonical gcc assembly stream.

    A table must be inside its owner's .ent/.end, refer to that function's
    local text labels and be addressed by its dispatch. Numeric tables and
    arbitrary initialized objects cannot masquerade as a switch table.
    """
    if not m['owned_data']:
        return
    owner = None
    section = None
    offset = 0
    words = {}
    halves = {}
    byte_values = {}
    labels = {}
    text_labels = {}
    bodies = {}
    for raw in assembly.splitlines():
        line = raw.split('#', 1)[0].strip()
        if not line:
            continue
        hit = re.fullmatch(r'\.ent\s+(\w+)', line)
        if hit:
            owner = hit[1]
            bodies.setdefault(owner, [])
        if owner:
            bodies[owner].append(line)
        if re.match(r'\.end\s', line):
            owner = None
        if line in ('.rdata', '.rodata', '.text', '.data', '.bss'):
            section = line
            continue
        if line.endswith(':'):
            label = line[:-1]
            if section in ('.rdata', '.rodata'):
                labels[label] = (offset, owner)
            elif section == '.text':
                text_labels[label] = owner
            continue
        if section not in ('.rdata', '.rodata'):
            continue
        hit = re.fullmatch(r'\.align\s+(\d+)', line)
        if hit:
            if int(hit[1]) > 4:
                raise ValueError('unsupported native alignment')
            align = 1 << int(hit[1])
            offset = (offset + align - 1) // align * align
            continue
        hit = re.fullmatch(r'\.word\s+([\w$]+)', line)
        if hit:
            words[offset] = (hit[1], owner)
            offset += 4
            continue
        hit = re.fullmatch(r'\.byte\s+(\d+)', line)
        if hit:
            value = int(hit[1])
            if not 0 <= value <= 255:
                raise ValueError('native message byte outside range')
            byte_values[offset] = (value, owner)
            offset += 1
            continue
        hit = re.fullmatch(r'\.half\s+(-?\d+)', line)
        if hit:
            if not -32768 <= int(hit[1]) <= 65535:
                raise ValueError('native direction halfword outside range')
            halves[offset] = (int(hit[1]) & 65535, owner)
            offset += 2
            continue
        if re.match(r'\.(?:globl|type|size|file)\s', line):
            continue
        raise ValueError('unaccounted native rodata directive: ' + line)
    base = m['members'][0]['foff']
    expected = {}
    expected_halves = {}
    expected_bytes = {}
    for d in m['owned_data']:
        start = d['foff'] - base
        if d['kind'] == 'typed_function_pointer':
            expected[start] = (d['target'], None)
            if labels.get(d['symbol']) != (start, None):
                raise ValueError('native entry assembly symbol differs')
        elif d['kind'] in ('typed_string', 'message_bytes', 'rectangle_records'):
            packed = literal_bytes(d)
            if (labels.get(d['symbol']) != (start, None)
                    or any(start < loc[0] < start + d['size'] for loc in labels.values())):
                raise ValueError('typed native assembly symbol/bounds differ')
            if d['kind'] == 'rectangle_records':
                expected_halves.update({start + i: (struct.unpack_from('<H', packed, i)[0], None)
                                       for i in range(0, len(packed), 2)})
            else:
                expected_bytes.update({start + i: (v, None) for i, v in enumerate(packed)})
        elif d['kind'] == 'direction_offsets':
            packed = direction_bytes(d)
            if labels.get(d['symbol']) != (start, None):
                raise ValueError('native direction symbol differs')
            expected_halves.update({start + i: (struct.unpack_from('<H', packed, i)[0], None)
                                   for i in range(0, len(packed), 2)})
        elif d['kind'] == 'switch_table':
            table_labels = [n for n, loc in labels.items()
                            if loc == (start, d['owner']) and re.fullmatch(r'\$L\d+', n)]
            body = '\n'.join(bodies.get(d['owner'], []))
            if (len(table_labels) != 1
                    or '%hi(' + table_labels[0] + ')' not in body
                    or '%lo(' + table_labels[0] + ')' not in body
                    or not re.search(r'\bj(?:r)?\s+\$\d+\b', body)):
                raise ValueError('table lacks its own switch dispatch')
            for pos in range(start, start + d['size'], 4):
                target, emitting_owner = words.get(pos, (None, None))
                if (emitting_owner != d['owner'] or not target
                        or not re.fullmatch(r'\$L\d+', target)
                        or text_labels.get(target) != d['owner']):
                    raise ValueError('table target not emitted by its owner')
                expected[pos] = (target, emitting_owner)
    if words != expected or halves != expected_halves or byte_values != expected_bytes or offset != sum(d['size'] for d in m['owned_data']):
        raise ValueError('native assembly head coverage differs')


def validate_relocations(m, view):
    ds = m['owned_data']
    prefix = sum(d['size'] for d in ds)
    heads = [(sec, data) for sec, data in view.obj.sections.items()
             if sec in ('.rodata', '.rdata') and data]
    if not prefix:
        if heads:
            raise ValueError('unowned native data')
        return []
    if len(heads) != 1 or len(heads[0][1]) != prefix:
        raise ValueError('native data extent differs')
    sec, data = heads[0]
    # View.rel is a dictionary: count the original records too, so duplicates
    # cannot disappear during canonicalization.
    relocs = [(off, (kind, target)) for (section, off), (kind, target) in view.rel.items()
              if section == sec]
    if len(relocs) != sum(r[0] == sec for r in view.obj.relocs):
        raise ValueError('duplicate native data relocation')
    actual = dict(relocs)
    expected = {}
    inventory = []
    base = m['members'][0]['foff']
    members = {a['function']: a['size'] - a.get('body_offset', 0) for a in m['members']}
    for d in ds:
        start = d['foff'] - base
        if d['kind'] == 'typed_function_pointer':
            sym = view.obj.symbols.get(d['symbol'])
            if sym is None or sym[0] != sec or sym[1] != start:
                raise ValueError('native entry symbol differs')
            expected[start] = ('32', ('fn', d['target'], 0))
        elif d['kind'] in ('typed_string', 'message_bytes', 'rectangle_records'):
            sym = view.obj.symbols.get(d['symbol'])
            if (sym is None or sym[0] != sec or sym[1] != start
                    or any(s[0] == sec and start < s[1] < start + d['size']
                           for s in view.obj.symbols.values())):
                raise ValueError('typed native object symbol/bounds differ')
            if data[start:start + d['size']] != literal_bytes(d):
                raise ValueError('typed native object bytes differ')
        elif d['kind'] == 'direction_offsets':
            sym = view.obj.symbols.get(d['symbol'])
            if sym is None or sym[0] != sec or sym[1] != start:
                raise ValueError('native direction symbol differs')
            if data[start:start + d['size']] != direction_bytes(d):
                raise ValueError('native direction bytes differ')
        elif d['kind'] == 'alignment':
            if any(data[start:start + d['size']]):
                raise ValueError('native alignment is not zero')
        elif d['kind'] == 'switch_table':
            for pos in range(start, start + d['size'], 4):
                kind, target = actual.get(pos, (None, (None, None, None)))
                if (kind != '32' or target[0] != 'fn' or target[1] != d['owner']
                        or not isinstance(target[2], int) or target[2] % 4
                        or not 0 <= target[2] < members[d['owner']]):
                    raise ValueError('switch table relocation points outside its owning function')
                expected[pos] = (kind, target)
            # Both objects must contain address relocations from this function
            # to the start of its own table; imports cannot supply that table.
            fsec, begin, end = view.funcs[d['owner']]
            refs = {kind for (s, off), (kind, target) in view.rel.items()
                    if s == fsec and begin <= off < end and target == ('sec', '.rodata', start)}
            if not {'HI16', 'LO16'} <= refs:
                raise ValueError('switch owner does not address its table')
        inventory.append({'offset': start, 'size': d['size'], 'kind': d['kind']})
    if actual != expected:
        raise ValueError('native head relocation inventory differs')
    return {'records': inventory,
            'relocations': [[pos, kind, list(target)] for pos, (kind, target) in sorted(actual.items())]}


def prepare_object(m, raw, trim_path):
    """Return a new object; the original artifact is always retained by caller."""
    spec = importlib.util.spec_from_file_location('overlay_rodata_trim', trim_path)
    trim = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(trim)
    prefix = sum(d['size'] for d in m['owned_data'])
    if not prefix:
        return raw, None
    data = bytearray(raw)
    result = trim.trim(data, prefix)
    if not result['trimmed']:
        return raw, None
    if result['trimmed'] != 4 or not any(d['kind'] == 'switch_table' for d in m['owned_data']):
        raise ValueError('only measured four-byte native table tail trim is supported')
    return bytes(data), dict(result, section='.rodata', zero_tail=True,
                            no_tail_relocations=True, no_tail_symbols=True)


def make_proof(m, raw, obj, ma, ge, assembly, trim_path, artifacts):
    validate_switch_assembly(m, assembly)
    before, trim = prepare_object(m, raw, trim_path)
    if before != obj:
        raise ValueError('trimmed object is not the guarded section-size-only edit')
    native = validate_relocations(m, ma)
    if native != validate_relocations(m, ge):
        raise ValueError('genuine native relocation inventory differs')
    return {'schema': 'overlay-native-rodata-v1', 'module': m['key'],
            'owned_data': m['owned_data'], 'native': native, 'trim': trim,
            'artifacts': {name: digest(data) for name, data in artifacts.items()}}


def verify_proof(m, proof, raw, obj, ma, ge, assembly, trim_path, artifacts):
    if proof is None:
        raise ValueError('native rodata/trim receipt missing')
    expected = make_proof(m, raw, obj, ma, ge, assembly, trim_path, artifacts)
    if proof != expected:
        raise ValueError('native rodata/trim receipt unbound or changed')
