#!/usr/bin/env python3
"""One final GNU ld invocation, with explicit imports and bank-qualified symbols.

Run from any directory. All scratch artifacts remain private and ignored.
"""
import argparse
import collections
import csv
import fnmatch
import hashlib
import json
from pathlib import Path
import re
import subprocess
import struct
try:
    from .graph import Graph, number, digest, qualification, emit_global
except ImportError:
    from graph import Graph, number, digest, qualification, emit_global

HERE = ROOT = SCRATCH = GRAPH = None
SLICES = []
WINDOWS = []


def tsv(name, header, rows):
    target = HERE/name
    with target.open('w', newline='') as stream:
        writer = csv.writer(stream, delimiter='\t', lineterminator='\n')
        writer.writerow(header)
        writer.writerows(rows)
    if target.stat().st_size > 2_000_000:
        receipts = SCRATCH/'receipts'
        receipts.mkdir(exist_ok=True)
        blob = target.read_bytes()
        target.replace(receipts/name)
        (HERE/(name+'.summary.json')).write_text(json.dumps(dict(
            bytes=len(blob), sha256=digest(blob), records=len(rows),
            private_receipt=relative(receipts/name)), indent=2)+'\n')


def relative(path):
    return Path(path).relative_to(ROOT).as_posix()


def run(argv, **kwargs):
    result = subprocess.run(list(map(str, argv)), cwd=ROOT, capture_output=True, text=True, **kwargs)
    if result.returncode:
        raise RuntimeError(' '.join(map(str, argv)) + '\n' + result.stderr[-5000:])
    return result.stdout


def nm(path):
    values = []
    for line in run(['mipsel-linux-gnu-nm', '-P', path]).splitlines():
        fields = line.split()
        if len(fields) >= 2:
            values.append((fields[0], fields[1], int(fields[2], 16) if len(fields) > 2 else 0))
    return values



def object_metadata(path):
    """Read ordinary ELF32 MIPS section/symbol metadata without three subprocesses.

    Unexpected bindings/section types use the existing binutils path. Relocations
    and object bytes are untouched; GNU ld remains the relocation authority.
    """
    data = Path(path).read_bytes()
    if len(data) < 52 or data[:7] != b'\x7fELF\x01\x01\x01':
        return None
    etype, machine = struct.unpack_from('<HH', data, 16)
    shoff = struct.unpack_from('<I', data, 32)[0]
    entsize, count, strings = struct.unpack_from('<HHH', data, 46)
    if etype != 1 or machine != 8 or entsize != 40 or not 0 < strings < count or shoff + count*40 > len(data):
        return None
    sections = [struct.unpack_from('<10I', data, shoff + n*40) for n in range(count)]
    def payload(section):
        offset, size = section[4:6]
        if offset + size > len(data):
            raise ValueError('truncated ELF metadata')
        return data[offset:offset+size]
    def string(table, offset):
        return table[offset:table.index(b'\0', offset)].decode('ascii')
    try:
        names = [string(payload(sections[strings]), section[0]) for section in sections]
        symbols, values, symbol_sizes = [], [], {}
        for section in sections:
            if section[1] != 2:
                continue
            if section[9] != 16 or section[5] % 16:
                return None
            strings_table = payload(sections[section[6]])
            raw = payload(section)
            for off in range(0, len(raw), 16):
                name, value, size, info, other, index = struct.unpack_from('<IIIBBH', raw, off)
                if not name or info & 15 in (3, 4):
                    continue
                if info & 15 not in (0, 1, 2):
                    return None
                name = string(strings_table, name)
                bind = info >> 4
                if bind not in (0, 1):
                    return None
                if index == 0:
                    kind, section_name = 'U', None
                elif index == 0xfff1:
                    kind, section_name = 'A', None
                elif index == 0xfff2:
                    kind, section_name = 'C', None
                elif 0 < index < count:
                    section_name = names[index]
                    target = sections[index]
                    if not target[2] & 2:
                        return None
                    kind = ('S' if section_name == '.sbss' else 'G' if section_name == '.sdata'
                            else 'B' if target[1] == 8 else 'T' if target[2] & 4
                            else 'D' if target[2] & 1 else 'R' if target[2] & 2 else 'N')
                else:
                    return None
                if bind == 0 and kind not in ('U', 'C', 'N'):
                    kind = kind.lower()
                values.append((name, kind, value))
                symbols.append((name, section_name, value))
                symbol_sizes[name] = size
        return dict(values=sorted(values), symbols=symbols, symbol_sizes=symbol_sizes,
                    sections=[(name, section[5]) for name, section in zip(names, sections)])
    except (IndexError, ValueError, UnicodeError, struct.error):
        return None


def qualified_redefinitions(prefix, renames, symbols):
    """Keep convergent undefined aliases distinct; bind them to real owner symbols.

    objcopy refuses two source symbols with the same rename target, even when
    both are undefined. Symbolic ld assignments preserve their owning section
    and therefore the NOCROSSREFS contract; no numeric address is substituted.
    """
    targets = collections.Counter(target for name,kind,target in renames)
    lines = []
    for name, kind, target in renames:
        if kind == 'U' and targets[target] > 1:
            alias = prefix + name
            symbols.append(f'{alias} = {target};')
            target = alias
        lines.append(f'{name} {target}\n')
    return ''.join(lines)


def unique_owner(candidates):
    """Aliases in one emitting instance agree; distinct equal-address instances do not."""
    if not candidates or len({peer['prefix'] for name,peer in candidates}) != 1:
        return None
    return min(candidates, key=lambda pair:(not pair[0].startswith(('func_', 'D_')),pair[0]))

def assignments(text):
    return {name: int(value, 16) for name, value in re.findall(
        r'^\s*([A-Za-z_][A-Za-z0-9_]*)\s*=\s*0x([0-9A-Fa-f]+)\s*;', text, re.M)}


def differences(actual, expected):
    return sum(a != b for a, b in zip(actual, expected)) + abs(len(actual) - len(expected))


def slus_origins(map_text, output_sections, size):
    """Summarize emitted input spans only; exclude discarded sections and symbols."""
    active, output = False, None
    counts = collections.Counter()
    for line in map_text.splitlines():
        if line == 'Linker script and memory map':
            active = True
        if not active:
            continue
        if line.startswith('.'):
            output = line.split()[0]
        if output not in output_sections:
            continue
        match = re.fullmatch(r'\s+(?:\.\S+\s+)?0x[0-9a-fA-F]+\s+0x([0-9a-fA-F]+)\s+(\S+\.o)\s*', line)
        if match:
            nbytes, path = int(match[1], 16), match[2]
            origin = ('C' if '/src/' in path else 'SDK_assembly' if '/asm/psyq/' in path
                      else 'game_assembly' if path.endswith('/asm/main.o') else 'imported_objects')
            counts[origin] += nbytes
    counts['linker_fill'] = size - sum(counts.values())
    if counts['linker_fill'] < 0 or not counts['C']:
        raise ValueError('SLUS map origin accounting failed')
    return dict(counts)



def selected_images(documents):
    """Complete town load views and dungeon banks; exclude diagnostic row views."""
    return sorted(image for image, doc in documents.items()
                  if image in ('town/engine', 'dungeon/engine') or image.startswith('dungeon/bank_') or
                  (image.startswith('town/') and number(doc.get('vma') or 0) == 0x80016000))


def select_windows(root, documents, images, initial, limit):
    """Bounded, deterministic coverage of actual placement rows in production windows."""
    if not 1 <= limit <= 60:
        raise ValueError('gate limit must be between 1 and 60')
    selected = list(dict.fromkeys(initial))
    if len(selected) > limit:
        raise ValueError('gate limit cannot omit the baseline windows')
    registry = {r['id']: r for r in map(json.loads, (root/'ledger/rows.jsonl').read_text().splitlines())}
    candidates = collections.defaultdict(set)
    for image in images:
        for entry in documents[image]['entries']:
            row = registry.get(entry.get('row'), {})
            config = row.get('gate_config')
            if config and (root/config).is_file():
                window = Path(config).name.removesuffix('.overlay.yaml')
                candidates[window].add(image)
    covered = set().union(*(candidates.get(w, set()) for w in selected))
    while len(selected) < limit and candidates:
        window = min(candidates, key=lambda w: (-len(candidates[w] - covered), w))
        hits = candidates.pop(window)
        if window not in selected:
            selected.append(window)
            covered.update(hits)
    return selected


def owned_resident(elf, spec):
    """Only emitted global definitions with an actual original SLUS input owner.

    Linker-script aliases, absolute catalogue witnesses and local/static names
    cannot become owners. Equal-address aliases must resolve to a real defining
    input object, including emitted data beyond the old prototype text cutoff.
    """
    ninja = (ROOT/spec['ninja']).read_text()
    inputs = [ROOT/'build_slus'/p for line in ninja.splitlines() if ': link ' in line
              for p in line.split(': link ', 1)[1].split() if p.endswith('.o')]
    definitions = collections.defaultdict(set)
    for line in run(['mipsel-linux-gnu-nm', '-A', '-g', '--defined-only', '-P', *inputs]).splitlines():
        match = re.match(r'^(.*?\.o):\s+(\S+)\s+([A-Za-z])\s+', line)
        if match and match[3] in 'TDBRSGVWC':
            definitions[match[2]].add(relative(match[1]))
    owners = {name: next(iter(paths)) for name, paths in definitions.items() if len(paths) == 1}
    resident = {name: value for name, kind, value in nm(elf)
                if kind in 'TDBRSGVW' and name in owners and not name.startswith('_binary_')
                and not owners[name].startswith(('build_slus/build/assets/', 'build_slus/build/module_assets/'))}
    return resident, {name: owners[name] for name in resident}



def resident_spans(elf, resident, owners):
    """Only explicit ELF symbol sizes on real original-input definitions grant extents."""
    spans, metadata_cache = [], {}
    for line in run(['mipsel-linux-gnu-nm','-g','-S','-P',elf]).splitlines():
        fields = line.split()
        if len(fields) >= 4 and fields[0] in resident and fields[1] in 'TDBRSGVW':
            size = int(fields[3], 16)
            name = fields[0]
            owner = owners[name]
            if owner not in metadata_cache:
                metadata_cache[owner] = object_metadata(ROOT/owner)
            metadata = metadata_cache[owner]
            if not metadata or metadata['symbol_sizes'].get(name) != size:
                continue
            section_sizes = dict(metadata['sections'])
            definitions = [(section, value) for symbol,section,value in metadata['symbols'] if symbol == name]
            if size > 0 and len(definitions) == 1:
                section, value = definitions[0]
                if section not in section_sizes or value + size > section_sizes[section]:
                    continue
                start = resident[name]
                spans.append((start, start+size, name))
    return spans


def containing_owner(address, spans):
    """An interior address needs an explicit nonzero extent; never infer the next boundary."""
    candidates = [span for span in spans if address is not None and span[0] < address < span[1]]
    return min(candidates, key=lambda span:(span[1]-span[0], span[2])) if candidates else None

def preparation_digest(root, graph):
    """Bind reusable private preparation to source, recipes, headers and evidence."""
    paths = set()
    for directory in ('src', 'include', 'tools/gate', 'tools/build', 'tools/fidelity',
                      'config/overlays', 'config/link', 'config/link_graph', 'ledger/splits'):
        paths.update(p for p in (root/directory).rglob('*') if p.is_file() and
                     p.suffix in ('.c', '.h', '.py', '.sh', '.txt', '.json', '.jsonl', '.yaml', '.ninja'))
    for directory in ('config', 'ledger'):
        paths.update(p for p in (root/directory).iterdir() if p.is_file() and
                     p.suffix in ('.json', '.jsonl', '.txt', '.tsv'))
    paths.update(root/p for p in ('tools/source_layout.py', 'tools/overlay_module_evidence.py', 'tools/link/prepare.py'))
    hashes = [(p.relative_to(root).as_posix(), digest(p.read_bytes())) for p in sorted(paths)]
    return digest(json.dumps(hashes, separators=(',', ':')).encode())


def prepared_digest(prepared):
    hashes = [(str(p), digest(p.read_bytes())) for work in prepared.values()
              for p in sorted(work.rglob('*')) if p.is_file() and p.suffix in ('.o', '.ld', '.json')]
    return digest(json.dumps(hashes, separators=(',', ':')).encode())


def save_prepared(root, graph, path, prepared, holds, stats):
    path.write_text(json.dumps(dict(prepared={k: v.relative_to(root).as_posix() for k,v in prepared.items()},
        holds=holds, stats=stats, inputs_sha256=preparation_digest(root, graph),
        artifacts_sha256=prepared_digest(prepared)), indent=2)+'\n')


def load_prepared(root, graph, path):
    data = json.loads(path.read_text())
    prepared = {k: root/v for k,v in data['prepared'].items()}
    if any(not p.resolve().is_relative_to(root) for p in prepared.values()):
        raise ValueError('prepared object path escapes private root')
    if data['inputs_sha256'] != preparation_digest(root, graph) or data['artifacts_sha256'] != prepared_digest(prepared):
        raise ValueError('prepared objects or their inputs changed; rerun --prepare')
    return prepared, data['holds'], data['stats']

def plan():
    # Every raw object or linked image is private; none is a delivery.
    SCRATCH.mkdir(exist_ok=True)
    (SCRATCH / '.ignore').write_text('*\n')
    (SCRATCH / '.gitignore').write_text('*\n')
    command = ['python3', 'tools/build/gate_all.py', '--workers', '4', '--all']
    for window in WINDOWS:
        command += ['--only-window', f'config/overlays/{window}.overlay.yaml']
    (HERE / 'gate_plan.json').write_text(json.dumps(dict(
        windows=WINDOWS, slices=SLICES, cwd='private root',
        env={'GATE_JOURNAL': relative(SCRATCH/'gate.jsonl')}, argv=command), indent=2)+'\n')
    print(' '.join(command))


def main():
    global ROOT, HERE, SCRATCH, GRAPH, SLICES, WINDOWS
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[2])
    parser.add_argument('--graph', type=Path)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--scratch', type=Path, required=True)
    parser.add_argument('--extend-ovmovie', action='store_true')
    parser.add_argument('--plan', action='store_true')
    parser.add_argument('--all-images', action='store_true', help='all 60 town load views and every dungeon bank')
    parser.add_argument('--image', action='append', default=[], help='restrict expansion to named load images for incremental proofs')
    parser.add_argument('--prepare', action='store_true', help='prepare the additional images through production home recipes')
    parser.add_argument('--gate-limit', type=int, default=60, help='maximum distinct production proof windows (1..60)')
    args = parser.parse_args()
    ROOT, HERE, SCRATCH = args.root.resolve(), args.output.resolve(), args.scratch.resolve()
    for path in (HERE, SCRATCH):
        if not path.is_relative_to(ROOT) or path == ROOT:
            raise ValueError('outputs must be private subdirectories of root')
        path.mkdir(parents=True, exist_ok=True)
    GRAPH = Graph(args.graph or ROOT/'config/link_graph')
    GRAPH.verify_inputs(ROOT)
    GRAPH.verify_sources(ROOT)
    SLICES = [(r['view'], r['window']) for r in GRAPH.manifest['build']['slice']]
    if args.extend_ovmovie:
        SLICES += [(r['view'], r['window']) for r in GRAPH.manifest['build']['extensions']]
    documents = GRAPH.documents(validate=True)
    additional = selected_images(documents) if args.all_images else []
    if args.image:
        if not args.all_images or set(args.image) - set(additional):
            raise ValueError('--image requires --all-images and known load images')
        additional = [image for image in additional if image in args.image]
    additional = [image for image in additional if image not in dict(SLICES)]
    baseline_images = {image for image, _ in SLICES}
    scope_images = sorted(set(additional) | (set(selected_images(documents)) & baseline_images)) if args.all_images else []
    WINDOWS = select_windows(ROOT, documents, scope_images, [w for _, w in SLICES], args.gate_limit)
    plan()
    if args.plan:
        return
    prepared, preparation_holds, preparation_stats = {}, [], {}
    if additional:
        try:
            from .prepare import prepare_images, load_gate
        except ImportError:
            from prepare import prepare_images, load_gate
        if args.prepare:
            prepared, preparation_holds, preparation_stats = prepare_images(ROOT, GRAPH, additional, SCRATCH/'prepared')
            save_prepared(ROOT, GRAPH, SCRATCH/'prepared_index.json', prepared, preparation_holds, preparation_stats)
        else:
            prepared, preparation_holds, preparation_stats = load_prepared(ROOT, GRAPH, SCRATCH/'prepared_index.json')
        accounted = set(prepared) | {image for image, _ in preparation_holds}
        missing = set(additional) - accounted
        if missing:
            raise ValueError('preparation index omits requested images: ' + ', '.join(sorted(missing)))
        load_gate(ROOT)
        SLICES += [(image, image.replace('/', '_')) for image in additional if image in prepared]
    slus_spec = GRAPH.manifest['build']['slus']
    slus_elf = ROOT / slus_spec['elf']
    # Absolute catalog assignments in the baseline ELF are still imports, not
    # SLUS-owned definitions. Static/local names cannot satisfy a new global ref.
    resident = {n: v for n, kind, v in nm(slus_elf) if kind in ['T','D','B','R','S','G','V','W']}
    legacy_resident = dict(resident)
    resident, resident_owners = owned_resident(slus_elf, slus_spec)
    resident_intervals = resident_spans(slus_elf, resident, resident_owners)
    resident_by_address = collections.defaultdict(list)
    for name, value in resident.items():
        if not name.startswith(('$', '__')):
            resident_by_address[value].append(name)
    slus_script = (ROOT/slus_spec['recipe']).read_text()
    # Original wildcard clauses are all SLUS build/src scoped. The discard is deferred
    # until all image input sections have been assigned in the combined description.
    discard = slus_script.find('    /DISCARD/')
    if discard < 0:
        discard = slus_script.find('  /DISCARD/')
    if discard >= 0:
        slus_script = slus_script[:discard] + '}\n'
    slus_script = slus_script.replace('build/', 'build_slus/build/')
    (HERE/'slus_sections.ld').write_text(slus_script)
    slus_inputs = []
    ninja = (ROOT/slus_spec['ninja']).read_text()
    for line in ninja.splitlines():
        if ': link ' in line:
            slus_inputs = [ROOT/'build_slus'/p for p in line.split(': link ', 1)[1].split() if p.endswith('.o')]
    if not slus_inputs:
        raise RuntimeError('SLUS object list missing')
    documents = GRAPH.documents(validate=True)
    image_specs = []
    for image, window in SLICES:
        d = documents.get(image)
        if d is None:
            extension = next(r for r in GRAPH.manifest['build']['extensions'] if r['view'] == image)
            d = dict(foff=0, size=GRAPH.files[extension['file']]['size'], vma=None)
        image_specs.append((image, window, number(d['foff']), number(d['size']),
                            None if d['vma'] is None else number(d['vma'])))
    container_paths = {'main': 'MAIN_MAIN.BIN', 'town': 'TOWN_TOWN.BIN',
                       'dungeon': 'DUNGEON_DUNGEON.BIN', 'ovmovie': 'OVMOVIE.BIN'}
    containers = {c: (ROOT/'work/disc/containers'/p).read_bytes()
                  for c,p in container_paths.items()}
    for c, blob in containers.items():
        if len(blob) != GRAPH.files[c]['size'] or hashlib.sha1(blob).hexdigest() != GRAPH.files[c]['sha1']:
            raise ValueError('physical input identity mismatch: ' + c)
    placements = {(e['view'], number(e['attributes']['foff'])): e['tu']
                  for e in GRAPH.entries.values() if e['kind'] == 'tu'}
    registry = {r['id']: r for r in map(json.loads, (ROOT/'ledger/rows.jsonl').read_text().splitlines())}
    rows_by_extent = collections.defaultdict(list)
    for row in registry.values():
        rows_by_extent[(row['container'], row.get('foff'), row['size'])].append(row)

    object_rows, provenance, holds = [], [], []
    placement_bridges = []
    symbols, objects, noloads, bank_fragments, standalone = [], list(slus_inputs), [], {}, []
    needed_resident, fallback_bindings, local_links = [], [], []
    binding_changes = []
    comparison_rows, image_sections, spec_counts = [], {}, {}
    next_lma = 0x1000000
    image_work = {}
    for image, window, start, size, base in image_specs:
        tag = image.replace('/', '_')
        work = prepared.get(image, ROOT/'build_ovl/work/s3_splat'/window)
        prepared_window = image.replace('/', '_') if image in prepared else window
        manifest = json.loads((work/f'{prepared_window}_manifest.json').read_text())
        window_script = (work/'build'/f'{prepared_window}.ld').read_text()
        window_assignments = assignments(window_script)
        segments = []
        seen_modules = set()
        prepared_allocations = {}
        for seg in manifest['c_segments'] + manifest.get('platform_asm_segments', []) + manifest.get('game_asm_segments', []):
            off = number(seg['file_start'])
            if not (start <= off and off+seg['size'] <= start+size):
                continue
            module_dir = None
            allocations = []
            original_override = None
            rules_override = None
            if seg.get('module'):
                module_id = seg.get('module_placement') or seg['module']
                if module_id in seen_modules:
                    continue
                seen_modules.add(module_id)
                module_dir = work/'build/modules'/module_id
                receipt = json.loads((module_dir/'receipt.json').read_text())
                if receipt['gate']['result'] != 'MATCH':
                    raise RuntimeError('module baseline failed')
                if seg.get('module_placement'):
                    import overlay_module_placements as module_placements
                    placement = next(p for p in module_placements.load(ROOT/'build_ovl') if p['key'] == seg['module_placement'])
                    first = placement['projected'][0]
                    receipt = dict(receipt, gate=dict(receipt['gate'], foff=first['foff'], vma=first['vma']))
                    allocations = placement.get('allocations', [])
                    original_override = module_dir/'artifact/module.o'
                    rules_override = module_dir/'placement.ld'
                else:
                    allocations = GRAPH.tus['module/' + seg['module']].get('allocations', [])
                if allocations and not seg.get('module_placement'):
                    witnessed = [{k:a[k] for k in ('section','foff','vma','size','link_alignment')}
                                 for a in receipt['physical'].get('allocations', [])]
                    if allocations != witnessed:
                        raise ValueError('graph/module allocation witnesses disagree')
                    if any(not (start <= a['foff'] and a['foff'] + a['size'] <= start + size)
                           for a in allocations):
                        raise ValueError('complete module allocations exceed selected image')
                seg = dict(seg, file_start=hex(receipt['gate']['foff']), size=receipt['gate']['bytes'],
                           rowbase_link_vram=hex(receipt['gate']['vma']), source='module:'+seg['module'])
                off = number(seg['file_start'])
                if not (start <= off and off+seg['size'] <= start+size):
                    holds.append([image,seg['func'],hex(off),seg['size'],'complete module exceeds selected image'])
                    continue
                matches = [original_override or module_dir/'module.o']
                if not allocations and receipt.get('physical', {}).get('owned_data'):
                    prefix_size = sum(d['size'] for d in receipt['physical']['owned_data'])
                    aoff, avma = receipt['gate']['foff'], receipt['gate']['vma']
                    allocations = [dict(section='.rodata', foff=aoff, vma=avma, size=prefix_size, link_alignment=4),
                        dict(section='.text.*', foff=aoff+prefix_size, vma=avma+prefix_size,
                             size=receipt['gate']['bytes']-prefix_size, link_alignment=4)]
            else:
                exact = work/'build/obj'/f"{seg['func']}__{off:06X}.o"
                plain = work/'build/obj'/(seg['func']+'.o')
                matches = [exact] if exact.is_file() else [plain] if plain.is_file() else list((work/'build/obj').glob(seg['func']+'*.o'))
                if not matches:
                    matches = list((work/'build/obj').glob('*_'+seg['func']+'_*.o'))
            if allocations and any(not (start <= a['foff'] and a['foff'] + a['size'] <= start + size) for a in allocations):
                holds.append([image,seg['func'],hex(off),seg['size'],'complete module allocation exceeds selected image'])
                continue
            if len(matches) != 1:
                holds.append([image, seg['func'], f'0x{off:X}', seg['size'], f'original object lookup returned {len(matches)} candidates'])
                continue
            original = matches[0]
            mini = rules_override or (module_dir/'module.ld' if module_dir else work/'build'/f'rowbase_{original.stem}.ld')
            rules = mini.read_text() if mini.exists() else window_script
            defs = assignments(rules)
            defs.update({k:v for k,v in window_assignments.items() if k not in defs})
            vma = number(seg.get('rowbase_link_vram', seg['vram']))
            if base is not None and vma != base+off-start:
                try:
                    from .placement import prove_invariant_placement
                except ImportError:
                    from placement import prove_invariant_placement
                wanted = containers[image.split('/')[0]][off:off+seg['size']]
                bridge = None if allocations or module_dir else prove_invariant_placement(
                    ROOT, documents[image], original, rules, vma, base+off-start, wanted,
                    SCRATCH/f'placement_{tag}_{off:x}')
                if bridge is None:
                    holds.append([image, seg['func'], f'0x{off:X}', seg['size'], 'compile VMA differs from selected load image; no invariant placement proof; retain import'])
                    continue
                placement_bridges.append(dict(bridge,image=image,foff=hex(off)))
                vma = base+off-start
                seg = dict(seg,rowbase_link_vram=hex(vma))
            metadata = object_metadata(original)
            values = metadata['values'] if metadata else nm(original)
            # rodata-first modules have a dedicated mini-link description: retain their
            # baseline bytes until the complete module can be placed faithfully.
            if not allocations and mini.exists() and '.out_' in rules and any(k.upper() in ['R','D'] and k != 'U' for _, k, _ in values):
                # Production rodata-owner recipe: load the validated prefix and
                # text from one original ET_REL object at their declared VMAs.
                rodata = re.search(r'^\s*(\.(?:rodata|rdata)) 0x([0-9a-fA-F]+) :', rules, re.M)
                text = re.search(r'^\s*\.out_\w+ 0x([0-9a-fA-F]+)', rules, re.M)
                if rodata and text:
                    rbase, tbase = int(rodata[2], 16), int(text[1], 16)
                    allocations = [dict(section=rodata[1], foff=off, vma=rbase, size=tbase-rbase, link_alignment=1),
                        dict(section='.text.*', foff=off+tbase-rbase, vma=tbase, size=seg['size']-(tbase-rbase), link_alignment=4)]
            if not allocations and any(k.upper() in ['R','D'] and k != 'U' for _, k, _ in values) and mini.exists() and '.out_' not in rules:
                holds.append([image, seg['func'], f'0x{off:X}', seg['size'], 'rodata-first original object needs dedicated placement'])
                continue
            sections = '' if metadata else run(['mipsel-linux-gnu-objdump', '-h', original])
            all_sections = [(name, f'{size:x}') for name,size in metadata['sections']] if metadata else re.findall(
                r'^\s*\d+\s+(\.[^\s]+)\s+([0-9a-fA-F]+)', sections, re.M)
            text_sections = [(name, size) for name,size in all_sections if name == '.text' or name.startswith('.text.')]

            mode = '.text.*' if any(n.startswith('.text.') and int(nbytes,16) for n,nbytes in text_sections) else '.text'
            text_size = sum(int(nbytes,16) for n,nbytes in text_sections if (n.startswith('.text.') if mode=='.text.*' else n=='.text'))
            if text_size > seg['size'] and not allocations:
                holds.append([image, seg['func'], f'0x{off:X}', seg['size'], f'object text {text_size} exceeds registered extent; dedicated composite layout needed'])
                continue
            family = image.split('/')[0]
            candidates = rows_by_extent[(family, off, seg['size'])]
            if len(candidates) > 1:
                raise ValueError('ambiguous registry extent for ' + image + ':' + hex(off))
            # Manifest func is often the linked true-name, not the immutable
            # registry row name. Bind through the exact physical extent.
            rid = candidates[0]['id'] if candidates else family + '/' + seg['func']
            tu_id = 'module/' + seg['module'] if seg.get('module') else placements.get((image, off), registry.get(rid, {}).get('source_row') or rid)
            if tu_id not in GRAPH.tus:
                # Existing assembly has a stable container/row identity.
                if seg in manifest.get('platform_asm_segments', []) + manifest.get('game_asm_segments', []):
                    tu_id = 'assembly/' + rid
                else:
                    raise ValueError('source object has no graph TU home: ' + tu_id)
            prefix = qualification(image, tu_id, rid)
            placed = SCRATCH/f'{tag}_{off:x}.o'
            # A complete TU has several function sections. nm's values are
            # section-relative, so recover their emission offsets before linking peers.
            offsets, at = {}, 0
            for sect,nbytes in text_sections:
                if (sect.startswith('.text.') if mode=='.text.*' else sect=='.text'):
                    offsets[sect] = at
                    at += int(nbytes,16)
            if allocations:
                offsets = {}
                for allocation in allocations:
                    at = 0
                    for sect, nbytes in all_sections:
                        if fnmatch.fnmatchcase(sect, allocation['section']):
                            alignment = allocation['link_alignment']
                            at = (at + alignment - 1) // alignment * alignment
                            offsets[sect] = allocation['vma'] - vma + at
                            at += int(nbytes, 16)
                    if at != allocation['size']:
                        raise ValueError('object allocation size disagrees with graph')
            symbol_offsets = {}
            section_sizes = {name:int(size,16) for name,size in all_sections}
            if metadata:
                symbol_offsets = {name: offsets[section]+value for name,section,value in metadata['symbols'] if section in offsets and 0 <= value < section_sizes[section]}
            else:
                for line in run(['mipsel-linux-gnu-objdump','-t',original]).splitlines():
                    fields=line.split()
                    if len(fields)>=5 and fields[-3] in offsets and int(fields[0],16) < section_sizes[fields[-3]]:
                        symbol_offsets[fields[-1]]=offsets[fields[-3]]+int(fields[0],16)
            if seg.get('source') and Path(seg['source']).is_absolute():
                seg = dict(seg, source=relative(seg['source']))
            segment = dict(seg=seg, off=off, vma=vma, original=original, placed=placed,
                           rules=rules, defs=defs, values=values, prefix=prefix, mode=mode, text_size=text_size,
                           symbol_offsets=symbol_offsets, tu_id=tu_id, allocations=allocations)
            segments.append(segment)
        image_work[image] = (work, manifest, window_script, segments)
    engine_defs = collections.defaultdict(list)
    for image in ('town/engine', 'dungeon/engine'):
        if image not in image_work:
            continue
        for segment in image_work[image][3]:
            for name, kind, value in segment['values']:
                if kind in 'TDBRSGVW' and name in segment['symbol_offsets']:
                    engine_defs[image.split('/')[0]].append((name, segment['vma']+segment['symbol_offsets'][name], segment))
    for image, window, start, size, base in image_specs:
        tag = image.replace('/', '_')
        work, manifest, window_script, segments = image_work[image]
        # Preserve exactly the per-object proven address for every relocation. Resolve
        # to a real definition only if its linked address agrees with that witness.
        local_defs = collections.defaultdict(list)
        local_by_address = collections.defaultdict(list)
        for s in segments:
            for name, kind, value in s['values']:
                if kind in 'TDBRSGVW' and name in s['symbol_offsets']:
                    address = s['vma']+s['symbol_offsets'][name]
                    local_defs[name].append((s, address))
                    local_by_address[address].append((name, s))
        for s in segments:
            renames = []
            for name, kind, value in s['values']:
                renamed = s['prefix'] + name
                if kind == 'U':
                    expected = s['defs'].get(name)
                    if expected is None:
                        match = re.fullmatch(r'(?:func|D)_([0-9a-fA-F]{8})', name)
                        expected = int(match[1],16) if match else None
                    candidates = [(peer, addr) for peer,addr in local_defs[name] if addr == expected]
                    if len({peer['prefix'] for peer,addr in candidates}) > 1:
                        candidates = []
                    interior = containing_owner(expected, resident_intervals)
                    local_owner = unique_owner(local_by_address.get(expected, []))
                    engine_candidates = [(owner_name, peer) for owner_name, addr, peer in engine_defs[image.split('/')[0]]
                                         if addr == expected and peer is not s]
                    engine_owner = unique_owner(engine_candidates)
                    if name in resident and resident[name] == expected:
                        renamed = name
                        needed_resident.append([image, f"0x{s['off']:X}", name, f'0x{expected:08X}', 'actual SLUS definition in '+resident_owners[name]])
                    elif candidates:
                        renamed = candidates[0][0]['prefix']+name
                        local_links.append([image, f"0x{s['off']:X}", name, f'0x{expected:08X}', candidates[0][0]['seg']['func']])
                    elif expected in resident_by_address:
                        renamed = sorted(resident_by_address[expected], key=lambda n:(not n.startswith(('func_', 'D_')),n))[0]
                        needed_resident.append([image, f"0x{s['off']:X}", name, f'0x{expected:08X}', 'SLUS defining TU selected by equal witnessed address: '+renamed+' in '+resident_owners[renamed]])
                    elif local_owner:
                        owner_name, peer = local_owner
                        renamed = peer['prefix'] + owner_name
                        local_links.append([image, f"0x{s['off']:X}", name, f'0x{expected:08X}',
                                            'actual same-image definition selected by equal address: '+owner_name])
                        binding_changes.append([image, f"0x{s['off']:X}", name, f'0x{expected:08X}', renamed, relative(peer['original'])])
                    elif engine_owner:
                        owner_name, peer = engine_owner
                        renamed = peer['prefix'] + owner_name
                        needed_resident.append([image, f"0x{s['off']:X}", name, f'0x{expected:08X}',
                                                'actual resident engine definition in '+relative(peer['original'])])
                        binding_changes.append([image, f"0x{s['off']:X}", name, f'0x{expected:08X}', renamed, relative(peer['original'])])
                    elif interior:
                        begin, end, owner_name = interior
                        renamed = s['prefix'] + name
                        expression = owner_name + f' + 0x{expected-begin:X}'
                        symbols.append(f'{renamed} = {expression};')
                        needed_resident.append([image, f"0x{s['off']:X}", name, f'0x{expected:08X}',
                            'SLUS emitted symbol extent: '+expression+' in '+resident_owners[owner_name]])
                        binding_changes.append([image, f"0x{s['off']:X}", name, f'0x{expected:08X}', expression, resident_owners[owner_name]])
                    elif expected is not None:
                        symbols.append(f'{renamed} = 0x{expected:08X};')
                        fallback_bindings.append([image, f"0x{s['off']:X}", name, f'0x{expected:08X}', 'address witness; no unique agreeing emitted global resident or same-image definition'])
                    if expected is not None and renamed in resident and not (
                            name in legacy_resident and legacy_resident[name] == expected or
                            candidates or expected in legacy_resident.values() and 0x8002d000 <= expected < 0x80081800):
                        binding_changes.append([image, f"0x{s['off']:X}", name, f'0x{expected:08X}', renamed, resident_owners[renamed]])
                    if expected is None:
                        raise RuntimeError(f'unresolved {image} {s["seg"]["func"]} {name}')
                renames.append((name, kind, renamed))
            rename_file = SCRATCH/(s['placed'].stem+'.rename.txt')
            rename_file.write_text(qualified_redefinitions(s['prefix'], renames, symbols))
            run(['mipsel-linux-gnu-objcopy', '--redefine-syms='+relative(rename_file), s['original'], s['placed']])
            objects.append(s['placed'])
            # Table placement mirrors the original NOLOAD address witness. Table
            # contents remain imported, exactly as in the production mini-link.
            for sect, addr in re.findall(r'^\s*(\.[\w.]+)\s+0x([0-9a-fA-F]+)\s+\(NOLOAD\)',s['rules'],re.M):
                name = f'.table_{tag}_{s["off"]:x}_{len(noloads)}'
                noloads.append(f'  {name} 0x{int(addr,16):08X} (NOLOAD) : SUBALIGN(4) {{ KEEP("{relative(s["placed"])}"({sect}*)) }}')
            object_rows.append([image, f"0x{s['off']:X}", s['seg']['size'], f"0x{s['vma']:08X}",
                                relative(s['original']), digest(s['original'].read_bytes()),
                                GRAPH.tus[s['tu_id']]['source'] if s['tu_id'] in GRAPH.tus else s['seg'].get('source'),
                                s['seg'].get('config'), s['text_size'], s['mode'], s['tu_id'], s['prefix']])
        payloads = []
        for s in segments:
            if s['allocations']:
                for a in s['allocations']:
                    payloads.append(dict(s, off=a['foff'], vma=a['vma'], mode=a['section'],
                                         seg=dict(s['seg'], size=a['size'])))
            else:
                payloads.append(s)
        payloads.sort(key=lambda s:s['off'])
        cursor, fragments, section_list = start, [], []
        imported, compiled_bytes = 0, 0
        chunks = []
        for s in payloads:
            if s['off'] < cursor:
                raise RuntimeError('overlapping compiled rows')
            if cursor < s['off']:
                chunks.append(('import', cursor, s['off']-cursor, None))
            chunks.append(('compiled',s['off'],s['seg']['size'],s))
            cursor = s['off']+s['seg']['size']
        if cursor < start+size:
            chunks.append(('import',cursor,start+size-cursor,None))
        lma = next_lma
        next_lma += (size + 0xFFFF) & ~0xFFFF
        for idx,(kind,off,nbytes,s) in enumerate(chunks):
            section_name = f'.piece_{tag}_{idx}'
            if kind == 'import':
                payload = containers[image.split('/')[0]][off:off+nbytes]
                binary = SCRATCH/f'{tag}_{idx}.bin'
                binary.write_bytes(payload)
                obj = SCRATCH/f'{tag}_{idx}.raw.o'
                run(['mipsel-linux-gnu-objcopy','-I','binary','-O','elf32-tradlittlemips','-B','mips',
                     '--rename-section',f'.data={section_name},alloc,load,readonly,data,contents',binary,obj])
                objects.append(obj)
                keep = f'KEEP("{relative(obj)}"({section_name}))'
                imported += nbytes
                provenance.append([image,f'0x{off:X}',nbytes,'retail import',digest(payload)])
            else:
                keep = f'KEEP("{relative(s["placed"])}"({s["mode"]}))'
                compiled_bytes += nbytes
                provenance.append([image,f'0x{off:X}',nbytes,'compiled original object',digest(s['original'].read_bytes())])
            if base is not None:
                fragments.append(f'      . = 0x{off-start:X}; {keep}')
                fragments.append(f'      . = 0x{off-start+nbytes:X};')
            else:
                # MAIN is a file container, not a single RAM image. Raw file-only
                # spans use a diagnostic address domain; code uses proven row VMAs.
                vma = s['vma'] if s else 0x10000000+off
                standalone.append(f'  {section_name} 0x{vma:08X} : AT(0x{lma+off-start:X}) SUBALIGN(1) {{ {keep} . = 0x{nbytes:X}; }}')
                section_list.append((section_name,off,nbytes))
        if base is not None:
            bank_fragments[tag] = (base,lma,fragments)
            section_list.append(('.'+tag,start,size))
        image_sections[image] = section_list
        spec_counts[image] = dict(size=size, original_objects=len(segments), compiled_bytes=compiled_bytes,
                                  imported_bytes=imported, start=start, window=window)
    # Whole-image ld script. All SLUS objects and selected original ET_REL C
    # objects are consumed here; no prelinked overlay payload supplies C bytes.
    head = ['/* One combined link; run the command in link_command.json from the private root. */',
            '/* AT addresses pack outputs for comparison; they are not retail CD sectors. */',
            '/* MAIN file-only spans use diagnostic VMAs; overlap checks retain baseline policy. */',
            *slus_script.splitlines()]
    slus_undef = {}
    for path in [ROOT/'build_slus/config/generated/slus_006.14.undefined_funcs.txt',
                 ROOT/'build_slus/build/slus_006.14.undefined_syms.modules.txt', ROOT/'config/slus_006.14.c_syms.txt']:
        slus_undef.update(assignments(path.read_text()))
    # Preserve all original fallback aliases, but avoid overriding genuine owners.
    original_slus_defined = {fields[0] for line in run(
        ['mipsel-linux-gnu-nm','-g','--defined-only','-P',*slus_inputs]).splitlines()
        if len(fields:=line.split())>=2 and fields[1].isalpha()}
    for name, addr in sorted(slus_undef.items()):
        if name not in original_slus_defined:
            head.append(f'{name} = 0x{addr:08X};')
    banks = [(tag.replace('_', '/', 1), base, spec_counts[tag.replace('_', '/', 1)]['size'], fragments)
             for tag, (base, lma, fragments) in bank_fragments.items()]
    script = emit_global('\n'.join(head), standalone, banks, symbols, noloads)
    script_path = SCRATCH/'global.ld'
    script_path.write_text(script)
    (HERE/'global_script_summary.json').write_text(json.dumps(dict(
        bytes=len(script.encode()), sha256=digest(script.encode()),
        lines=script.count('\n'), private_script=relative(script_path)), indent=2)+'\n')
    response = SCRATCH/'objects.rsp'
    response.write_text('\n'.join(relative(obj) for obj in objects)+'\n')
    elf = SCRATCH/'onelink.elf'
    argv = ['mipsel-linux-gnu-ld','-EL','--no-check-sections','-T',relative(script_path),
            '-Map',relative(SCRATCH/'onelink.map'),'-o',relative(elf),'@'+relative(response)]
    (HERE/'link_command.json').write_text(json.dumps(dict(argv=argv, original_slus_objects=len(slus_inputs),
                                                       input_objects=len(objects)),indent=2)+'\n')
    result = subprocess.run(argv,cwd=ROOT,capture_output=True,text=True)
    (SCRATCH/'link.log').write_text(result.stdout+result.stderr)
    if result.returncode:
        tsv('prototype_holds.tsv',['image','row','foff','size','reason'],holds)
        tsv('preparation_holds.tsv',['image','reason'],preparation_holds)
        raise RuntimeError(result.stderr[-7000:])
    map_blob = (SCRATCH/'onelink.map').read_bytes()
    slus_counts = slus_origins(map_blob.decode(), slus_spec['sections'], GRAPH.files['slus']['size'])
    slus_compiled = sum(slus_counts.get(k, 0) for k in ('C', 'SDK_assembly', 'game_assembly'))
    (HERE/'map_summary.json').write_text(json.dumps(dict(
        map_bytes=len(map_blob), map_sha256=digest(map_blob), map_lines=map_blob.count(b'\n'),
        original_slus_objects=len(slus_inputs), original_overlay_objects=len(object_rows),
        overlay_source_object_bytes=sum(c['compiled_bytes'] for c in spec_counts.values()),
        overlay_import_bytes=sum(c['imported_bytes'] for c in spec_counts.values()),
        slus_origin_bytes=slus_counts,
        noload_table_witnesses=len(noloads), selected_outputs=1+len(spec_counts),
        note='Map exceeds 2 MB and remains private. NOLOAD table contents remain imported.'
    ), indent=2)+'\n')
    for image, section_list in image_sections.items():
        c = spec_counts[image]
        got = bytearray(c['size'])
        for section,off,nbytes in section_list:
            out = SCRATCH/'extract.bin'
            run(['mipsel-linux-gnu-objcopy','-O','binary','--only-section='+section,elf,out])
            payload = out.read_bytes()
            if len(payload) != nbytes:
                raise RuntimeError(f'{section} length {len(payload)} != {nbytes}')
            got[off-c['start']:off-c['start']+nbytes] = payload
        want = containers[image.split('/')[0]][c['start']:c['start']+c['size']]
        diffs = differences(got, want)
        window = c['window']
        import yaml
        if image in prepared and image not in baseline_images:
            comparison_rows.append([image,c['size'],'MATCH' if diffs==0 else 'DIFF',diffs,c['compiled_bytes'],c['imported_bytes'],
                                    0,'NOT_GATED',0,digest(got),digest(want),'full retail comparison; object preparation is not a production window gate'])
            c.update(differing_bytes=diffs,sha256=digest(got),window_compared_bytes=0,window_differing_bytes=0)
            continue
        w = yaml.safe_load((ROOT/'config/overlays'/f'{window}.overlay.yaml').read_text())['standalone_build']['window']
        baseline = (ROOT/'build_ovl/work/s3_splat'/window/'build'/f'{window}.window.bin').read_bytes()
        if len(baseline) != number(w['file_end']) - number(w['file_start']):
            raise ValueError('baseline window length disagrees with its declared extent')
        a,b=max(number(w['file_start']),c['start']),min(number(w['file_end']),c['start']+c['size'])
        baseline_diffs = differences(got[a-c['start']:b-c['start']],baseline[a-number(w['file_start']):b-number(w['file_start'])])
        comparison_rows.append([image,c['size'],'MATCH' if diffs==0 else 'DIFF',diffs,c['compiled_bytes'],c['imported_bytes'],
                                b-a,'MATCH' if baseline_diffs==0 else 'DIFF',baseline_diffs,
                                digest(got),digest(want),'compiled originals + explicit retail gaps; historical one-link invocation unproved'])
        c.update(differing_bytes=diffs,sha256=digest(got),window_compared_bytes=b-a,window_differing_bytes=baseline_diffs)
    out = SCRATCH/'slus.bin'
    run(['mipsel-linux-gnu-objcopy','-O','binary',
         *['--only-section='+s for s in slus_spec['sections']],elf,out])
    got = out.read_bytes()
    want = (ROOT/'baserom/slus_006.14').read_bytes()
    baseline = (ROOT/slus_spec['binary']).read_bytes()
    diffs = differences(got, want)
    bd = differences(got, baseline)
    comparison_rows.insert(0,['slus/slus_bin',len(got),'MATCH' if not diffs else 'DIFF',diffs,
                              slus_compiled,len(got)-slus_compiled,len(baseline),'MATCH' if not bd else 'DIFF',bd,
                              digest(got),digest(want),'original complete SLUS link sections and ET_REL inputs, including retail assets/SDK assembly'])
    tsv('ldscript_results.tsv',['image','bytes_compared','retail_result','different_bytes','compiled_bytes','imported_bytes',
                             'baseline_compared_bytes','baseline_result','baseline_different_bytes','output_sha256','retail_sha256','reason'],comparison_rows)
    tsv('prototype_objects.tsv',['image','foff','size','link_vma','original_object','object_sha256','source','config','object_text_bytes','text_sections','tu_identity','symbol_namespace'],object_rows)
    tsv('provenance.tsv',['image','foff','size','origin','input_sha256'],provenance)
    tsv('prototype_holds.tsv',['image','row','foff','size','reason'],holds)
    for name,rows in [('resident_bindings',needed_resident),('remaining_bindings',fallback_bindings),('local_bindings',local_links)]:
        tsv(name+'.tsv',['image','caller_foff','original_symbol','vma','authority'],rows)
    tsv('binding_changes.tsv', ['image','caller_foff','original_symbol','vma','owner_symbol','owner_object'], binding_changes)
    tsv('preparation_holds.tsv', ['image','reason'], preparation_holds)
    row_holds = collections.Counter(row[0] for row in holds)
    tsv('images.tsv', ['image','status','retail_result','different_bytes','compiled_bytes','imported_bytes','source_row_holds','reason'],
        [[r[0], 'DIFF' if r[2] != 'MATCH' else 'LINKED_WITH_HOLDS' if row_holds[r[0]] else 'LINKED' if r[4] else 'IMPORT_ONLY',
          r[2], r[3], r[4], r[5], row_holds[r[0]], r[11]] for r in comparison_rows] +
        [[image,'HELD','NOT_LINKED','','','','',reason] for image,reason in preparation_holds])
    (HERE/'placement_bridges.json').write_text(json.dumps(placement_bridges,indent=2)+'\n')
    summary = dict(images=spec_counts, slus_bytes=len(got), slus_differing_bytes=diffs,
                   original_slus_objects=len(slus_inputs), original_overlay_objects=len(object_rows), graph_schema=GRAPH.manifest['schema'], graph_base=GRAPH.manifest['base'], symbol_qualification='stable image, graph TU home and placement row (assembly uses stable container/row identity)',
                   resident_bindings=len(needed_resident), local_bindings=len(local_links),
                   fallback_bindings=len(fallback_bindings), held_rows=len(holds),
                   placement_bridges=len(placement_bridges),
                   linked_images=len(comparison_rows), byte_exact_images=sum(r[2] == 'MATCH' for r in comparison_rows),
                   import_only_images=sum(not r[4] for r in comparison_rows),
                   preparation_stats=preparation_stats, preparation_held_images=len(preparation_holds),
                   symbolic_owner_aliases=len(symbols)-len(fallback_bindings),
                   reduced_bindings=len(binding_changes), fallback_bindings_before_owner_resolution=len(fallback_bindings)+len(binding_changes),
                   slus_sha1=hashlib.sha1(got).hexdigest(), scoped_windows=len(WINDOWS),
                   final_link_invocations=1, note='baseline links are prerequisites, not counted as final combined invocation')
    (HERE/'prototype_summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print(json.dumps(summary,indent=2))
    if holds or preparation_holds or any(r[2] != 'MATCH' or r[7] not in ('MATCH', 'NOT_GATED') for r in comparison_rows):
        raise RuntimeError('combined proof has held source objects or byte differences')


if __name__ == '__main__':
    main()
