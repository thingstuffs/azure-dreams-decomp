"""The cover list of a linked image: which bytes of the image a compiled object emits, and which of those are code.

The image linker (tools/build/mkbuild.py) stores one `cover` list in each origin file. The ownership check
(tools/lint/closure.py) reads nothing else about what the build compiled. This module only reads what the link
already produced (the chunk list, the linker map and the object symbol tables); it changes no built byte.

The rule for compiled code, the one the check relies on:

    A byte is C code when it lies in an input section `.text.<name>` of an object built from C that holds a FUNC
    symbol at offset 0 whose size equals the section size. Every other byte a C or module object emits is C data
    (a rodata array, a compiler table, a section without such a symbol). Bytes of assembled units are assembly.
    A unit whose symbols cannot be read contributes C data only (fail closed).
"""
import re
from pathlib import Path

SCHEMA = 'closure.cover.v1'
ASSEMBLY_KINDS = ('platform_asm', 'game_asm')
STT_FUNC = 2

_ENTRY_ONE = re.compile(r'^ (\S+)\s+0x([0-9a-fA-F]+)\s+0x([0-9a-fA-F]+)\s+(\S+\.o)\s*$')
_ENTRY_TWO = re.compile(r'^\s+0x([0-9a-fA-F]+)\s+0x([0-9a-fA-F]+)\s+(\S+\.o)\s*$')
_NAME_ONLY = re.compile(r'^ (\S+)\s*$')
_OUTPUT = re.compile(r'^(\.\S+)\s+0x([0-9a-fA-F]+)\s+0x([0-9a-fA-F]+)(?:\s+load address 0x([0-9a-fA-F]+))?\s*$')
_OUTPUT_NAME = re.compile(r'^(\.\S+)\s*$')


def map_sections(map_text, accept=None):
    """Input sections of a linker map as (output name, output address, load address or None, section, address,
    size, object path). `accept(output name)` selects the output sections to read."""
    out = []
    active, output, pending = False, None, None
    for line in map_text.splitlines():
        if line == 'Linker script and memory map':
            active = True
            continue
        if not active:
            continue
        match = _OUTPUT.match(line)
        if match:
            output = (match[1], int(match[2], 16), int(match[4], 16) if match[4] is not None else None)
            pending = None
            if accept is not None and not accept(output[0]):
                output = None
            continue
        if line and line[0] == '.':
            # an output section name too long for its line: its numbers follow on the next line
            output, pending = None, None
            continue
        if output is None:
            continue
        match = _ENTRY_ONE.match(line)
        if match:
            out.append((output[0], output[1], output[2], match[1], int(match[2], 16), int(match[3], 16), match[4]))
            pending = None
            continue
        match = _ENTRY_TWO.match(line)
        if match and pending:
            out.append((output[0], output[1], output[2], pending, int(match[1], 16), int(match[2], 16), match[3]))
            pending = None
            continue
        match = _NAME_ONLY.match(line)
        pending = match[1] if match and not match[1].startswith('*') else None
    return out


def piece_sections(map_text):
    """Input sections of every `.piece_N` output section of an image map: {N: [(section, address, size, path)]}."""
    pieces = {}
    for output, _address, _load, section, address, size, path in map_sections(
            map_text, lambda name: name.startswith('.piece_')):
        pieces.setdefault(int(output.split('_')[1]), []).append((section, address, size, path))
    return pieces


def complete_function_sections(metadata, prefix=''):
    """{section name: size} of the sections of one object that hold a FUNC symbol of exactly the section's size
    at offset 0. `metadata` is an object_metadata() result; none gives no section. `prefix` is the text a copy of
    the object put before each section name (a placed copy renames `.text.<name>` to `<prefix>.text.<name>`)."""
    if not metadata:
        return {}
    sizes = dict(metadata['sections'])
    found = {}
    for _name, section, value, size, kind in metadata.get('symbol_records', ()):
        if section and section.startswith(prefix + '.text.') and kind == STT_FUNC and value == 0 and size == sizes.get(section):
            found[section] = size
    return found


def merge_spans(spans):
    out = []
    for a, n in sorted(spans):
        if out and a <= out[-1][0] + out[-1][1]:
            out[-1][1] = max(out[-1][1], a + n - out[-1][0])
        else:
            out.append([a, n])
    return out


def code_spans(chunk_foff, chunk_vma, chunk_size, sections, functions):
    """File extents of the function sections among `sections` (section, address, size, path) of one piece."""
    spans = []
    for section, address, size, _path in sections:
        if functions.get(section) == size and size:
            foff = chunk_foff + address - chunk_vma
            if chunk_foff <= foff and foff + size <= chunk_foff + chunk_size:
                spans.append([foff, size])
    return merge_spans(spans)


def image_cover(spec, chunks, metadata_of, noload_tables, map_text):
    """Cover list of one linked image.

    `chunks` is the chunk list the link wrote its script from (compiled allocations and retail imports),
    `metadata_of(object path)` the object_metadata of a chunk's object, `noload_tables` the compiler tables the
    image keeps as retail bytes after comparing them with the compiled table (dicts with foff, size, vma, unit).
    """
    pieces = piece_sections(map_text)
    entries = []
    for index, chunk in enumerate(chunks):
        offset = chunk['foff'] - spec['start']
        vma = chunk.get('vma', (spec['vma'] + offset) if spec['vma'] is not None else 0x10000000 + offset)
        entry = dict(foff=chunk['foff'], size=chunk['size'], vma=vma, origin=chunk['origin'], code=[])
        if chunk['origin'] == 'original_object':
            unit_index = int(Path(chunk['object']).stem)
            unit = spec['units'][unit_index]
            kind = 'module' if unit.get('module') else unit.get('kind', 'c')
            entry.update(unit=unit_index, kind=kind, recipe=unit.get('recipe'), rebind=bool(unit.get('rebind')),
                         rows=len(unit.get('rows', [])))
            if kind in ASSEMBLY_KINDS:
                entry['class'] = 'assembly'
            else:
                entry['class'] = 'c_data'
                functions = complete_function_sections(metadata_of(chunk['object']))
                entry['code'] = code_spans(chunk['foff'], vma, chunk['size'], pieces.get(index, ()), functions)
        else:
            entry['class'] = 'import'
        entries.append(entry)
    for table in noload_tables:
        entries.append(dict(foff=table['foff'], size=table['size'], vma=table['vma'], origin='noload_table',
                            code=[], unit=table['unit'], kind='table', **{'class': 'c_data'}))
    return dict(schema=SCHEMA, start=spec['start'], size=spec['size'], vma=spec['vma'], chunks=entries)


def slus_cover(map_text, output_sections, metadata_of, size):
    """Cover list of the executable from its linker map. `metadata_of(object path as written in the map)`."""
    entries, skipped = [], 0
    for output, out_address, load, section, address, nbytes, path in map_sections(
            map_text, lambda name: name in output_sections):
        if not nbytes:
            continue
        if load is None:
            skipped += nbytes
            continue
        foff = load + address - out_address
        if '/src/' in path:
            kind, klass = 'c', 'c_data'
        elif '/asm/psyq/' in path:
            kind, klass = 'sdk_assembly', 'assembly'
        elif path.endswith('/asm/main.o'):
            kind, klass = 'game_assembly', 'assembly'
        else:
            kind, klass = 'imported', 'import'
        entry = dict(foff=foff, size=nbytes, vma=address, origin='original_object' if klass != 'import' else 'retail_import',
                     code=[], kind=kind, **{'class': klass})
        if kind == 'c' and section.startswith('.text.'):
            if complete_function_sections(metadata_of(path)).get(section) == nbytes:
                entry['code'] = [[foff, nbytes]]
        entries.append(entry)
    return dict(schema=SCHEMA, start=0, size=size, vma=None, chunks=entries, unplaced_bytes=skipped)
