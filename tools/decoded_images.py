#!/usr/bin/env python3
"""Build C into a separately registered, retail-derived decoded code image.

Physical container rows and their coverage are deliberately independent.
The recompress producer regenerates each stream from the complete linked
decoded image. Imported decoded gaps and resource padding remain explicit.
"""
import argparse
import hashlib
import json
import re
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from tools.decoded import bindings, call_targets, import_ranges
from tools.build.name_inputs import table as name_table
from tools.fidelity.objread import read_elf
from tools.decoded.extents import extent_digest, valid_digest
from tools.decoded.lz import decode, encode
from tools.build.slus_rodata_trim import trim


IDENTIFIER = re.compile(r'[A-Za-z_][A-Za-z_0-9]*')
ROW_NAME = re.compile(r'[a-z][a-z0-9_]*')
DATA_SECTIONS = {'.rodata', '.data'}
DATA_PREFIXES = ('.data', '.rodata', '.rdata', '.srodata', '.lit', '.bss',
                 '.sdata', '.sbss', '.ctors', '.dtors')


def number(value):
    if isinstance(value, bool) or not isinstance(value, (int, str)):
        raise ValueError('image coordinate must be an integer')
    return int(value, 0) if isinstance(value, str) else int(value)


def digest(data):
    return hashlib.sha256(data).hexdigest()


def local(root, name, prefix=None):
    path = Path(name)
    if path.is_absolute() or '..' in path.parts or not path.parts or (prefix and not name.startswith(prefix)):
        raise ValueError('unsafe decoded image path: ' + str(name))
    target = root / path
    # Disc extraction may be a provisioned read-only asset view. Never write it.
    asset = str(path).startswith('work/disc/containers/')
    if not asset and (target.is_symlink() or not target.resolve().is_relative_to(root.resolve())):
        raise ValueError('decoded image path escapes root: ' + str(name))
    return target


def validate_bindings(bindings):
    for symbol, address in bindings.items():
        if not IDENTIFIER.fullmatch(symbol) or not 0x80000000 <= number(address) < 0x80200000:
            raise ValueError('invalid decoded symbol binding')


def source_symbol(function):
    return function.get('symbol', function['name'])


def require_evidence(image):
    if image['proof_mode'] == 'recompress':
        for key in ('import_layout', 'binding_evidence', 'call_context'):
            if not image.get(key):
                raise ValueError('recompression requires ' + key)


def manifests(root=ROOT):
    root = Path(root).resolve()
    images, names = [], set()
    for path in sorted((root / 'config/decoded').glob('*.json')):
        image = json.loads(path.read_text())
        if image.get('schema') != 'azure.decoded-image.v1' or image.get('proof_mode') not in ('decoded-only', 'recompress'):
            raise ValueError('unsupported decoded image producer')
        require_evidence(image)
        name = image['image']
        if not re.fullmatch(r'[a-z][a-z0-9_]*/[a-z][a-z0-9_]*', name) or name in names:
            raise ValueError('invalid or duplicate decoded image identity')
        names.add(name)
        base, size = number(image['address']), number(image['size'])
        if size <= 0 or base & 3 or size & 3 or not 0x80010000 <= base < base + size <= 0x80200000:
            raise ValueError('invalid decoded image bounds')
        sha = image['sha256']
        if not valid_digest(size, sha):
            raise ValueError('invalid decoded image digest')
        if not image['streams'] or sum(number(s['size']) for s in image['streams']) != size:
            raise ValueError('decoded stream extents do not cover image')
        for stream in image['streams']:
            local(root, stream['container'], 'work/disc/containers/')
            used, limit = number(stream['used']), number(stream['input_limit'])
            if not 0 < used <= limit <= 0x100000 or number(stream['offset']) < 20 or number(stream['size']) <= 0:
                raise ValueError('invalid compressed stream bounds')
            # This producer's source contract is one terminating raw upload.
            # Multi-command resources need their own resource-base validation;
            # accepting a different offset here would misattribute the stream.
            if (len(stream['command']) != 8 or stream['command'][:3] != [5, 16, 20]
                    or stream['command'][7] != 0):
                raise ValueError('unsupported source command contract')
            if not (valid_digest(used, stream['source_sha256']) and
                    valid_digest(number(stream['size']), stream['decoded_sha256'])):
                raise ValueError('invalid stream digest')
        functions, data, seen, sources, placements = [], [], set(), set(), set()
        for unit in image['units']:
            source = unit['source']
            placed = 'placement' in unit
            if placed:
                placement = unit['placement']
                if not ROW_NAME.fullmatch(placement) or placement in placements:
                    raise ValueError('invalid or duplicate decoded placement')
                placements.add(placement)
                validate_bindings(unit['bindings'])
            else:
                if source in sources:
                    raise ValueError('duplicate decoded translation unit')
                if 'bindings' in unit:
                    raise ValueError('decoded bindings require a placement')
                sources.add(source)
            for key, prefix in (('source', 'src/'), ('header', 'include/')):
                if placed and key == 'header' and key not in unit:
                    continue
                if not local(root, unit[key], prefix).is_file():
                    raise ValueError('missing decoded unit input: ' + unit[key])
            if unit['compiler'] != '2.7.2-cdk' or unit['flags'] != '-G0':
                raise ValueError('unreviewed decoded compiler recipe')
            if unit.get('genuine_asflags', []) not in ([], ['-0']):
                raise ValueError('unreviewed decoded genuine assembler recipe')
            if not unit['functions']:
                raise ValueError('decoded translation unit has no functions')
            data_sections = set()
            for datum in unit.get('data', []):
                section = datum['section']
                if not isinstance(datum.get('trim_end_padding', False), bool):
                    raise ValueError('invalid decoded data padding policy')
                address, length = number(datum['address']), number(datum['size'])
                if placed or section not in DATA_SECTIONS or section in data_sections:
                    raise ValueError('invalid or duplicate decoded data section')
                if length <= 0 or not base <= address < address + length <= base + size:
                    raise ValueError('decoded data outside image')
                data_sections.add(section)
                data.append((address, address + length, section))
            exports = set()
            for function in unit['functions']:
                symbol = function['name']
                address, length = number(function['address']), number(function['size'])
                if not ROW_NAME.fullmatch(symbol) or symbol in seen:
                    raise ValueError('invalid or duplicate decoded function')
                if 'symbol' in function and (not placed or not IDENTIFIER.fullmatch(source_symbol(function))):
                    raise ValueError('invalid decoded placement export')
                export = source_symbol(function)
                if export in exports:
                    raise ValueError('duplicate decoded placement export')
                exports.add(export)
                seen.add(symbol)
                if address & 3 or length <= 0 or length & 3 or not base <= address < address + length <= base + size:
                    raise ValueError('decoded function outside image')
                functions.append((address, address + length, symbol))
            if placed and exports & unit['bindings'].keys():
                raise ValueError('placement export also supplied as a binding')
        if not functions:
            raise ValueError('decoded image has no C')
        last = base
        for begin, end, _ in sorted(functions + data):
            if begin < last:
                raise ValueError('overlapping decoded extents')
            last = end
        text_bytes = sum(end - begin for begin, end, _ in functions)
        data_bytes = sum(end - begin for begin, end, _ in data)
        coverage = dict(functions=len(functions), text_bytes=text_bytes, data_bytes=data_bytes,
                        imported_bytes=size - text_bytes - data_bytes,
                        stream_bytes=sum(number(s['used']) for s in image['streams'])
                        if image['proof_mode'] == 'recompress' else 0)
        expected = image.get('coverage')
        if (not isinstance(expected, dict) or any(type(value) is not int for value in expected.values())
                or expected != coverage):
            raise ValueError(f'{name}: decoded coverage differs: expected {expected}, found {coverage}')
        if set(image['symbols']) & seen:
            raise ValueError('function also supplied as an external binding')
        validate_bindings(image['symbols'])
        local(root, image['evidence'], 'docs/')
        images.append(image)
    return images


def rows(root=ROOT):
    return [dict(id='decoded/' + image['image'] + '/' + function['name'],
                 image=image['image'], coordinate_space='decoded', source=unit['source'],
                 header=unit.get('header'), **function,
                 **({'placement': unit['placement']} if 'placement' in unit else {}))
            for image in manifests(root) for unit in image['units'] for function in unit['functions']]


def reproduce(root, image):
    decoded, receipts = bytearray(), []
    for stream in image['streams']:
        offset, used, size = (number(stream[k]) for k in ('offset', 'used', 'size'))
        with local(root, stream['container']).open('rb') as source:
            source.seek(offset - 20)
            header = source.read(20)
            if len(header) != 20 or list(struct.unpack('<HHIhhhhI', header)) != stream['command']:
                raise ValueError('compressed image source command differs')
            compressed = source.read(number(stream['input_limit']))
        if len(compressed) != number(stream['input_limit']):
            raise ValueError('truncated source resource')
        data, consumed = decode(compressed, size)
        if consumed != used or len(data) != size or extent_digest(compressed[:used]) != stream['source_sha256'] or extent_digest(data) != stream['decoded_sha256']:
            raise ValueError('compressed or decoded stream identity differs')
        receipts.append(dict(container=stream['container'], offset=hex(offset), used=used,
                             source_sha256=extent_digest(compressed[:used]), decoded_offset=len(decoded),
                             size=size, decoded_sha256=extent_digest(data)))
        decoded.extend(data)
    data = bytes(decoded)
    if len(data) != number(image['size']) or extent_digest(data) != image['sha256']:
        raise ValueError('complete decoded image differs')
    return data, receipts


def audit_bindings(root, image, expected=None):
    path = image.get('binding_evidence')
    evidence = bindings.read_evidence(local(root, path, 'config/decoded/evidence/')) if path else {}
    return bindings.audit(image, bindings.external_symbols(root), evidence, data=expected, number=number)


def audit_import_ranges(root, image, expected=None):
    path = local(root, image['import_layout']['table'], 'config/decoded/evidence/')
    rows = import_ranges.read_table(path)
    holds = local(root, image['import_layout']['holds'], 'config/decoded/evidence/')
    import_ranges.audit_holds(holds, image, rows, number)
    return import_ranges.audit(image, rows, number, data=expected)


def audit_object_references(root, image, expected, objects=None):
    layout = image['import_layout']
    sources = layout['reference_sources']
    units = {u['source']: u for u in image['units']}
    if not set(sources) <= units.keys() or len(sources) != len(set(sources)):
        raise ValueError('invalid text reference sources')
    aliases = name_table(root / 'config/names.tsv')
    # A clean check compiles the reference owners. The link can reuse the objects it just compiled.
    build_dir = root / 'build'
    build_dir.mkdir(exist_ok=True)
    with tempfile.TemporaryDirectory(dir=build_dir) as tmp:
        parsed = {}
        for i, source in enumerate(units):
            unit = units[source]
            if objects is None:
                path = Path(tmp) / f'{i}.o'
                run(root, ['nice', '-n', '10', 'bash', 'build_ovl/tools/cc.sh', source,
                           str(path), unit['compiler'], unit['flags']], path.with_suffix('.log'))
            else:
                path = objects[source]
            parsed[source] = read_elf(path.read_bytes())
        import_ranges.audit_references(image, {src: parsed[src] for src in sources}, aliases, expected, number)
        if 'call_context' in image:
            return call_targets.audit(root, image, parsed, aliases, expected, number)


def run(root, command, log=None):
    if log:
        with log.open('w') as output:
            subprocess.run(command, cwd=root, stdout=output, stderr=subprocess.STDOUT, check=True)
        return ''
    result = subprocess.run(command, cwd=root, capture_output=True, text=True)
    if result.returncode:
        raise ValueError(f'{command[0]} failed: {result.stderr.strip()}')
    return result.stdout


def object_sections(root, obj):
    table = run(root, ['mipsel-linux-gnu-objdump', '-h', str(obj)])
    return {name: int(length, 16) for name, length in
            re.findall(r'^\s*\d+\s+(\S+)\s+([0-9a-fA-F]+)\s+', table, re.M)
            if int(length, 16)}


def place_object(root, work, obj, unit, text):
    placement = unit['placement']
    prefix = f'_decoded_{placement}.'
    section_prefix = f'.decoded.{placement}'
    placed = work / f'placed_{placement}.o'
    rename_sections = [arg for section in text for arg in
                       ('--rename-section', f'{section}={section_prefix}{section}')]
    run(root, ['mipsel-linux-gnu-objcopy', '--prefix-symbols', prefix,
               *rename_sections, str(obj), str(placed)])
    return placed, prefix, section_prefix


def function_symbols(obj, unit, section_prefix=''):
    """{function row name: True} for each manifest function of `unit` whose text section in `obj` (the object the
    image links: the compiled unit, or its placed copy whose sections carry `section_prefix`) holds one FUNC symbol
    of the section's size at offset 0. The ownership check counts only such bytes as compiled code, so a function
    whose section is missing or holds anything else records False."""
    from tools.build.cover import complete_function_sections
    from tools.link.combined import object_metadata
    found = complete_function_sections(object_metadata(obj), section_prefix)
    return {f['name']: found.get(section_prefix + '.text.' + source_symbol(f)) == number(f['size'])
            for f in unit['functions']}


def data_sections(obj, unit):
    """{section name: True} for each C data extent registered by `unit` whose section in `obj` (the compiled unit,
    after any trailing-padding trim) exists with exactly the registered size."""
    from tools.link.combined import object_metadata
    metadata = object_metadata(obj)
    sizes = dict(metadata['sections']) if metadata else {}
    return {d['section']: sizes.get(d['section']) == number(d['size']) for d in unit.get('data', [])}


def build(root, image, *, compile_units=True):
    root = Path(root).resolve()
    base, size = number(image['address']), number(image['size'])
    work = local(root, 'build/decoded/' + image['image'])
    work.mkdir(parents=True, exist_ok=True)
    require_evidence(image)
    expected, streams = reproduce(root, image)
    if 'binding_evidence' in image:
        audit_bindings(root, image, expected)
    if 'import_layout' in image:
        audit_import_ranges(root, image, expected)
    retail = work / 'retail.bin'
    retail.write_bytes(expected)
    objects, inputs, compiled, functions, data = [], {}, {}, [], []
    function_flags, data_flags = {}, {}
    imports, script, gaps = [], [], []
    for unit in image['units']:
        key = (unit['source'], unit['compiler'], unit['flags'])
        if key not in compiled:
            obj = work / f'unit_{len(compiled)}.o'
            if compile_units:
                run(root, ['nice', '-n', '10', 'bash', 'build_ovl/tools/cc.sh', unit['source'],
                           str(obj.relative_to(root)), unit['compiler'], unit['flags']], obj.with_suffix('.compile.log'))
            compiled[key] = obj, object_sections(root, obj)
        obj, sections = compiled[key]
        text = {'.text.' + source_symbol(f): number(f['size']) for f in unit['functions']}
        prefix = section_prefix = ''
        if 'placement' in unit:
            if any(sections.get(n) != s for n, s in text.items()):
                raise ValueError('complete decoded placement extents differ: ' + unit['placement'])
            obj, prefix, section_prefix = place_object(root, work, obj, unit, text)
            for name, address in sorted(unit['bindings'].items()):
                script.append(f'{prefix}{name} = 0x{number(address):X};')
        else:
            if {n: s for n, s in sections.items() if n.startswith('.text')} != text:
                raise ValueError('complete decoded TU text extents differ: ' + unit['source'])
            owned_data = unit.get('data', [])
            data_extents = {d['section']: number(d['size']) for d in owned_data}
            emitted_data = {n: s for n, s in sections.items() if n.startswith(DATA_PREFIXES)}
            trims = [d for d in owned_data if d.get('trim_end_padding')
                     and emitted_data.get(d['section'], 0) > number(d['size'])]
            if trims:
                contents = bytearray(obj.read_bytes())
                for datum in trims:
                    section, length = datum['section'], number(datum['size'])
                    trim(contents, length, section)
                    emitted_data[section] = length
                obj = work / (obj.stem + '_owned.o')
                obj.write_bytes(contents)
            if emitted_data != data_extents:
                raise ValueError('unregistered or mismatched decoded TU data: ' + unit['source'])
            data_flags.update({(unit['source'], k): v for k, v in data_sections(obj, unit).items()})
        function_flags.update(function_symbols(obj, unit, section_prefix))
        obj_path = obj.relative_to(root).as_posix()
        objects.append(obj_path)
        for f in unit['functions']:
            functions.append((number(f['address']), number(f['size']), f['name'], unit,
                              obj_path, section_prefix + '.text.' + source_symbol(f), source_symbol(f), prefix))
        for d in unit.get('data', []):
            data.append((number(d['address']), number(d['size']), d['section'], unit, obj_path))
        for key in ('source', 'header'):
            if key in unit and unit[key] not in inputs:
                inputs[unit[key]] = digest(local(root, unit[key]).read_bytes())
    if 'import_layout' in image:
        audit_object_references(root, image, expected, {key[0]: value[0] for key, value in compiled.items()})
    symbols = dict(image['symbols'])
    # ccproc may canonicalize resident names. Accept only aliases of the same
    # explicit binding; no unresolved relocation is masked or guessed.
    name_path = root / 'config/names.tsv'
    if name_path.is_file():
        for line in name_path.read_text().splitlines():
            cols = line.split('\t')
            if len(cols) >= 3:
                for alias in cols[1:3]:
                    if alias in symbols:
                        for other in cols[1:3]:
                            if other in symbols and number(symbols[other]) != number(symbols[alias]):
                                raise ValueError('inconsistent resident alias binding')
                            symbols[other] = symbols[alias]
    for name, address in sorted(symbols.items()):
        script.append(f'{name} = 0x{number(address):X};')
    script.append('SECTIONS {')
    cursor = base
    functions.sort()
    allocations = functions + [
        (address, length, f'data_{index}', unit, obj, section, None, '')
        for index, (address, length, section, unit, obj) in enumerate(data)
    ]
    for address, length, name, unit, obj, section_name, export, prefix in (
            sorted(allocations) + [(base + size, 0, '', None, '', '', '', '')]):
        if address > cursor:
            index = len(gaps)
            section = '.decoded_gap_' + str(index)
            # Relative path: generated assembler/linker files are portable too.
            imports.extend([f'.section {section},"a",@progbits',
                            f'.incbin "{retail.relative_to(root).as_posix()}", {cursor-base}, {address-cursor}'])
            script.append(f'.gap_{index} 0x{cursor:X} : SUBALIGN(1) {{ *({section}) }}')
            gaps.append(dict(offset=cursor-base, size=address-cursor, owner='imported decoded asset'))
        if name:
            if export is not None:
                if 'placement' in unit:
                    script.append(f'{name} = {prefix}{export};')
                    script.append(f'ASSERT({prefix}{export} == 0x{address:X}, "decoded placement entry differs")')
                output, alignment = '.fn_' + name, 4
            else:
                output, alignment = '.' + name, 1
            script.append(f'{output} 0x{address:X} : SUBALIGN({alignment}) {{ {obj}({section_name}) }}')
            script.append(f'ASSERT(SIZEOF({output}) == {length}, "decoded section size differs")')
        cursor = address + length
    script.append('/DISCARD/ : { *(*) }\n}')
    (work / 'imports.s').write_text('\n'.join(imports) + '\n')
    (work / 'image.ld').write_text('\n'.join(script) + '\n')
    run(root, ['mipsel-linux-gnu-as', '-EL', '-march=r3000', '-o', str(work/'imports.o'), str(work/'imports.s')])
    run(root, ['mipsel-linux-gnu-ld', '-T', str(work/'image.ld'), '-o', str(work/'image.elf'),
               *objects, str(work/'imports.o')])
    run(root, ['mipsel-linux-gnu-objcopy', '-O', 'binary', str(work/'image.elf'), str(work/'image.bin')])
    actual = (work / 'image.bin').read_bytes()
    if actual != expected:
        differing = [dict(function=n, address=hex(a), size=s)
                     for a, s, n, *_ in functions if actual[a-base:a-base+s] != expected[a-base:a-base+s]]
        differing.extend(dict(section=section, source=u['source'], address=hex(a), size=s)
                         for a, s, section, u, _ in data
                         if actual[a-base:a-base+s] != expected[a-base:a-base+s])
        raise ValueError('decoded image C differs: ' + json.dumps(differing))
    compressed = []
    if image['proof_mode'] == 'recompress':
        for index, stream in enumerate(streams):
            begin, length = stream['decoded_offset'], stream['size']
            packed = encode(actual[begin:begin+length])
            with local(root, stream['container']).open('rb') as source:
                source.seek(number(stream['offset']))
                original = source.read(stream['used'])
            if len(packed) != stream['used'] or packed != original:
                raise ValueError('recompressed stream differs from retail')
            target = work / f'stream_{index}.lz'
            target.write_bytes(packed)
            compressed.append(dict(container=stream['container'], offset=stream['offset'],
                                   size=len(packed), sha256=extent_digest(packed), output=target.relative_to(root).as_posix()))
    result = dict(result='PASS', image=image['image'], proof_mode=image['proof_mode'],
                  compressed_streams_produced_from_linked_image=bool(compressed), raw_c_coverage_bytes=0,
                  compressed_stream_bytes=sum(s['size'] for s in compressed), compressed_streams=compressed,
                  decoded_c_text_bytes=sum(s for _, s, *_ in functions),
                  decoded_c_data_bytes=sum(s for _, s, *_ in data),
                  data=[dict(section=section, source=u['source'], address=hex(a),
                             offset=a-base, size=s, sha256=extent_digest(actual[a-base:a-base+s]),
                             compiled_section=data_flags.get((u['source'], section), False))
                        for a, s, section, u, _ in sorted(data)],
                  decoded_imported_bytes=sum(g['size'] for g in gaps),
                  size=len(actual), sha256=extent_digest(actual), source_sha256=inputs, streams=streams,
                  functions=[dict(id='decoded/'+image['image']+'/'+n, name=n, address=hex(a),
                                  offset=a-base, size=s, source=u['source'], sha256=extent_digest(actual[a-base:a-base+s]),
                                  func_symbol=function_flags.get(n, False),
                                  **({'placement': u['placement'], 'symbol': export} if 'placement' in u else {}))
                             for a, s, n, u, _, _, export, _ in functions], gaps=gaps)
    (work / 'proof.json').write_text(json.dumps(result, indent=2) + '\n')
    return result


def container_overlays(root, proofs):
    """Regenerated compressed ranges for the ordinary disc-container producer."""
    result = {}
    for proof in proofs:
        for stream in proof['compressed_streams']:
            data = local(root, stream['output'], 'build/decoded/').read_bytes()
            if len(data) != stream['size'] or extent_digest(data) != stream['sha256']:
                raise ValueError('generated compressed artifact changed')
            result.setdefault(stream['container'], []).append((number(stream['offset']), data))
    for name, spans in result.items():
        last = 0
        retail = local(root, name).read_bytes()
        for offset, data in sorted(spans):
            if offset < last or data != retail[offset:offset+len(data)]:
                raise ValueError('compressed output overlaps or differs from container')
            last = offset + len(data)
    return result


def build_all(root, images=None):
    root = Path(root).resolve()
    proofs = [build(root, image) for image in (images if images is not None else manifests(root))]
    layout = {'MAIN_MAIN.BIN': 'MAIN/MAIN.BIN', 'TOWN_TOWN.BIN': 'TOWN/TOWN.BIN',
              'DUNGEON_DUNGEON.BIN': 'DUNGEON/DUNGEON.BIN', 'OVMOVIE.BIN': 'OVMOVIE.BIN'}
    containers = []
    for source, spans in container_overlays(root, proofs).items():
        retail = local(root, source).read_bytes()
        output = bytearray(retail)
        for offset, data in spans:
            output[offset:offset+len(data)] = data
        if output != retail:
            raise ValueError('complete compressed container differs')
        destination = local(root, 'build/decoded/disc/' + layout[Path(source).name])
        destination.parent.mkdir(parents=True, exist_ok=True)
        destination.write_bytes(output)
        containers.append(dict(source=source, output=destination.relative_to(root).as_posix(),
                               size=len(output), sha256=digest(output), retail_sha256=digest(retail),
                               sha1=hashlib.sha1(output).hexdigest(), identical=bytes(output)==retail,
                               regenerated_compressed_bytes=sum(len(data) for _,data in spans)))
    target = local(root, 'build/decoded/containers.json')
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_text(json.dumps(dict(result='PASS', containers=containers), indent=2)+'\n')
    return proofs


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=ROOT)
    parser.add_argument('command', choices=('check', 'build', 'rows', 'imports'))
    parser.add_argument('--image', help='one decoded image identity')
    args = parser.parse_args()
    root = args.root.resolve()
    images = manifests(root)
    if args.image:
        images = [i for i in images if i['image'] == args.image]
        if not images:
            raise ValueError('unknown decoded image')
    if args.command == 'rows':
        for row in rows(root):
            if not args.image or row['image'] == args.image:
                print(json.dumps(row, sort_keys=True))
    elif args.command == 'imports':
        if len(images) != 1:
            parser.error('select one decoded image with --image')
        image, = images
        import_ranges.write_table(import_ranges.derive(image, reproduce(root, image)[0], number),
                                  sys.stdout)
    elif args.command == 'build':
        for proof in build_all(root, images):
            print(json.dumps(proof, sort_keys=True))
    else:
        missing = []
        for image in images:
            available = all(local(root, stream['container']).is_file() for stream in image['streams'])
            expected = reproduce(root, image)[0] if available else None
            counts = audit_bindings(root, image, expected)
            print(f"{image['image']}: {counts['placement']} placement bindings and "
                  f"{counts['global']} global symbols checked, including "
                  f"{counts['address_names']} address-spelled bindings")
            if 'import_layout' in image:
                if available:
                    calls = audit_object_references(root, image, expected)
                if available and calls is not None:
                    outside, placements, exceptions = calls
                    print(f"{image['image']}: {outside} distinct external callees, {placements} ordinary "
                          f"placement call sites, {exceptions} recorded ordinary exceptions")
                totals = audit_import_ranges(root, image, expected)
                detail = ', '.join(f'{kind} {size:,}' for kind, size in totals.items())
                print(f"{image['image']}: imported bytes ({detail})")
            if not available:
                missing.append(image['image'])
        detail = ('; no disc for ' + ', '.join(missing) +
                  ': import totals and registered ranges only; disc bytes and text references unchecked') if missing else ''
        print(f'decoded registry OK: {len(images)} images, {len(rows(root))} functions{detail}')


if __name__ == '__main__':
    main()
