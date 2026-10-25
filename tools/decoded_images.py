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
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from tools.decoded.lz import decode, encode


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


def manifests(root=ROOT):
    root = Path(root).resolve()
    images, names = [], set()
    for path in sorted((root / 'config/decoded').glob('*.json')):
        image = json.loads(path.read_text())
        if image.get('schema') != 'azure.decoded-image.v1' or image.get('proof_mode') not in ('decoded-only', 'recompress'):
            raise ValueError('unsupported decoded image producer')
        name = image['image']
        if not re.fullmatch(r'[a-z][a-z0-9_]*/[a-z][a-z0-9_]*', name) or name in names:
            raise ValueError('invalid or duplicate decoded image identity')
        names.add(name)
        base, size = number(image['address']), number(image['size'])
        if size <= 0 or base & 3 or size & 3 or not 0x80010000 <= base < base + size <= 0x80200000:
            raise ValueError('invalid decoded image bounds')
        sha = image['sha256']
        if not re.fullmatch('[a-f0-9]{64}', sha):
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
            for key in ('source_sha256', 'decoded_sha256'):
                if not re.fullmatch('[a-f0-9]{64}', stream[key]):
                    raise ValueError('invalid stream digest')
        functions, seen, sources = [], set(), set()
        for unit in image['units']:
            source = unit['source']
            if source in sources:
                raise ValueError('duplicate decoded translation unit')
            sources.add(source)
            for key, prefix in (('source', 'src/'), ('header', 'include/')):
                if not local(root, unit[key], prefix).is_file():
                    raise ValueError('missing decoded unit input: ' + unit[key])
            if unit['compiler'] != '2.7.2-cdk' or unit['flags'] != '-G0':
                raise ValueError('unreviewed decoded compiler recipe')
            if not unit['functions']:
                raise ValueError('decoded translation unit has no functions')
            for function in unit['functions']:
                symbol = function['name']
                address, length = number(function['address']), number(function['size'])
                if not re.fullmatch('[a-z][a-z0-9_]*', symbol) or symbol in seen:
                    raise ValueError('invalid or duplicate decoded function')
                seen.add(symbol)
                if address & 3 or length <= 0 or length & 3 or not base <= address < address + length <= base + size:
                    raise ValueError('decoded function outside image')
                functions.append((address, address + length, symbol))
        if not functions:
            raise ValueError('decoded image has no C')
        last = base
        for begin, end, _ in sorted(functions):
            if begin < last:
                raise ValueError('overlapping decoded functions')
            last = end
        if set(image['symbols']) & seen:
            raise ValueError('function also supplied as an external binding')
        for symbol, address in image['symbols'].items():
            if not re.fullmatch('[a-zA-Z_][a-zA-Z_0-9]*', symbol) or not 0x80000000 <= number(address) < 0x80200000:
                raise ValueError('invalid decoded symbol binding')
        local(root, image['evidence'], 'docs/')
        images.append(image)
    return images


def rows(root=ROOT):
    return [dict(id='decoded/' + image['image'] + '/' + function['name'],
                 image=image['image'], coordinate_space='decoded', source=unit['source'],
                 header=unit['header'], **function)
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
        if consumed != used or len(data) != size or digest(compressed[:used]) != stream['source_sha256'] or digest(data) != stream['decoded_sha256']:
            raise ValueError('compressed or decoded stream identity differs')
        receipts.append(dict(container=stream['container'], offset=hex(offset), used=used,
                             source_sha256=digest(compressed[:used]), decoded_offset=len(decoded),
                             size=size, decoded_sha256=digest(data)))
        decoded.extend(data)
    data = bytes(decoded)
    if len(data) != number(image['size']) or digest(data) != image['sha256']:
        raise ValueError('complete decoded image differs')
    return data, receipts


def run(root, command, log=None):
    if log:
        with log.open('w') as output:
            subprocess.run(command, cwd=root, stdout=output, stderr=subprocess.STDOUT, check=True)
        return ''
    return subprocess.run(command, cwd=root, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                          text=True, check=True).stdout


def build(root, image, *, compile_units=True):
    root = Path(root).resolve()
    base, size = number(image['address']), number(image['size'])
    work = local(root, 'build/decoded/' + image['image'])
    work.mkdir(parents=True, exist_ok=True)
    expected, streams = reproduce(root, image)
    retail = work / 'retail.bin'
    retail.write_bytes(expected)
    objects, inputs = [], {}
    functions = sorted((number(f['address']), number(f['size']), f['name'], unit)
                       for unit in image['units'] for f in unit['functions'])
    for unit in image['units']:
        obj = work / (Path(unit['source']).stem + '.o')
        if compile_units:
            run(root, ['nice', '-n', '10', 'bash', 'build_ovl/tools/cc.sh', unit['source'],
                       str(obj.relative_to(root)), unit['compiler'], unit['flags']], obj.with_suffix('.compile.log'))
        section_table = run(root, ['mipsel-linux-gnu-objdump', '-h', str(obj)])
        sections = {}
        for name, length in re.findall(r'^\s*\d+\s+(\S+)\s+([0-9a-fA-F]+)\s+', section_table, re.M):
            if int(length, 16):
                sections[name] = int(length, 16)
        text = {'.text.' + f['name']: number(f['size']) for f in unit['functions']}
        if {n: s for n, s in sections.items() if n.startswith('.text')} != text:
            raise ValueError('complete decoded TU text extents differ: ' + unit['source'])
        if any(n.startswith(('.data', '.rodata', '.rdata', '.srodata', '.lit', '.bss', '.sdata', '.sbss', '.ctors', '.dtors')) for n in sections):
            raise ValueError('unregistered decoded TU data')
        objects.append(obj)
        for key in ('source', 'header'):
            inputs[unit[key]] = digest(local(root, unit[key]).read_bytes())
    imports, script, gaps = [], [], []
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
    for address, length, name, unit in functions + [(base + size, 0, '', None)]:
        if address > cursor:
            index = len(gaps)
            section = '.decoded_gap_' + str(index)
            # Relative path: generated assembler/linker files are portable too.
            imports.extend([f'.section {section},"a",@progbits',
                            f'.incbin "{retail.relative_to(root).as_posix()}", {cursor-base}, {address-cursor}'])
            script.append(f'.gap_{index} 0x{cursor:X} : SUBALIGN(4) {{ *({section}) }}')
            gaps.append(dict(offset=cursor-base, size=address-cursor, owner='imported decoded asset'))
        if name:
            script.append(f'.fn_{name} 0x{address:X} : SUBALIGN(4) {{ *(.text.{name}) }}')
            script.append(f'ASSERT(SIZEOF(.fn_{name}) == {length}, "decoded function size differs")')
        cursor = address + length
    script.append('/DISCARD/ : { *(*) }\n}')
    (work / 'imports.s').write_text('\n'.join(imports) + '\n')
    (work / 'image.ld').write_text('\n'.join(script) + '\n')
    run(root, ['mipsel-linux-gnu-as', '-EL', '-march=r3000', '-o', str(work/'imports.o'), str(work/'imports.s')])
    run(root, ['mipsel-linux-gnu-ld', '-T', str(work/'image.ld'), '-o', str(work/'image.elf'),
               *map(str, objects), str(work/'imports.o')])
    run(root, ['mipsel-linux-gnu-objcopy', '-O', 'binary', str(work/'image.elf'), str(work/'image.bin')])
    actual = (work / 'image.bin').read_bytes()
    if actual != expected:
        differing = [dict(function=n, address=hex(a), size=s)
                     for a, s, n, _ in functions if actual[a-base:a-base+s] != expected[a-base:a-base+s]]
        raise ValueError('decoded image C differs: ' + json.dumps(differing))
    compressed = []
    if image['proof_mode'] == 'recompress':
        for index, stream in enumerate(streams):
            begin, length = stream['decoded_offset'], stream['size']
            packed = encode(actual[begin:begin+length])
            if len(packed) != stream['used'] or digest(packed) != stream['source_sha256']:
                raise ValueError('recompressed stream differs from retail')
            target = work / f'stream_{index}.lz'
            target.write_bytes(packed)
            compressed.append(dict(container=stream['container'], offset=stream['offset'],
                                   size=len(packed), sha256=digest(packed), output=target.relative_to(root).as_posix()))
    result = dict(result='PASS', image=image['image'], proof_mode=image['proof_mode'],
                  compressed_streams_produced_from_linked_image=bool(compressed), raw_c_coverage_bytes=0,
                  compressed_stream_bytes=sum(s['size'] for s in compressed), compressed_streams=compressed,
                  decoded_c_text_bytes=sum(s for _, s, _, _ in functions),
                  decoded_imported_bytes=sum(g['size'] for g in gaps),
                  size=len(actual), sha256=digest(actual), source_sha256=inputs, streams=streams,
                  functions=[dict(id='decoded/'+image['image']+'/'+n, name=n, address=hex(a),
                                  offset=a-base, size=s, source=u['source'], sha256=digest(actual[a-base:a-base+s]))
                             for a, s, n, u in functions], gaps=gaps)
    (work / 'proof.json').write_text(json.dumps(result, indent=2) + '\n')
    return result


def container_overlays(root, proofs):
    """Regenerated compressed ranges for the ordinary disc-container producer."""
    result = {}
    for proof in proofs:
        for stream in proof['compressed_streams']:
            data = local(root, stream['output'], 'build/decoded/').read_bytes()
            if len(data) != stream['size'] or digest(data) != stream['sha256']:
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
    parser.add_argument('command', choices=('check', 'build', 'rows'))
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
    elif args.command == 'build':
        for proof in build_all(root, images):
            print(json.dumps(proof, sort_keys=True))
    else:
        print(f'decoded registry OK: {len(images)} images, {len(rows(root))} functions; physical rows unchanged')


if __name__ == '__main__':
    main()
