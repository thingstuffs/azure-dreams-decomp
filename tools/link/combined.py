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
try:
    from .graph import Graph, number, digest, qualification, emit_global
except ImportError:
    from graph import Graph, number, digest, qualification, emit_global

HERE = ROOT = SCRATCH = GRAPH = None
SLICES = []
WINDOWS = []


def tsv(name, header, rows):
    with (HERE/name).open('w', newline='') as stream:
        writer = csv.writer(stream, delimiter='\t', lineterminator='\n')
        writer.writerow(header)
        writer.writerows(rows)


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
    WINDOWS = [window for _, window in SLICES]
    plan()
    if args.plan:
        return
    slus_spec = GRAPH.manifest['build']['slus']
    slus_elf = ROOT / slus_spec['elf']
    # Absolute catalog assignments in the baseline ELF are still imports, not
    # SLUS-owned definitions. Static/local names cannot satisfy a new global ref.
    resident = {n: v for n, kind, v in nm(slus_elf) if kind in ['T','D','B','R','S','G','V','W']}
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
    symbols, objects, noloads, bank_fragments, standalone = [], list(slus_inputs), [], {}, []
    needed_resident, fallback_bindings, local_links = [], [], []
    comparison_rows, image_sections, spec_counts = [], {}, {}
    next_lma = 0x1000000
    for image, window, start, size, base in image_specs:
        tag = image.replace('/', '_')
        work = ROOT/'build_ovl/work/s3_splat'/window
        manifest = json.loads((work/f'{window}_manifest.json').read_text())
        window_script = (work/'build'/f'{window}.ld').read_text()
        window_assignments = assignments(window_script)
        segments = []
        seen_modules = set()
        for seg in manifest['c_segments'] + manifest.get('platform_asm_segments', []) + manifest.get('game_asm_segments', []):
            off = number(seg['file_start'])
            if not (start <= off and off+seg['size'] <= start+size):
                continue
            module_dir = None
            allocations = []
            if seg.get('module'):
                if seg['module'] in seen_modules:
                    continue
                seen_modules.add(seg['module'])
                module_dir = work/'build/modules'/seg['module']
                receipt = json.loads((module_dir/'receipt.json').read_text())
                if receipt['gate']['result'] != 'MATCH':
                    raise RuntimeError('module baseline failed')
                allocations = GRAPH.tus['module/' + seg['module']].get('allocations', [])
                if allocations:
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
                matches = [module_dir/'module.o']
            else:
                matches = list((work/'build/obj').glob(seg['func']+'*.o'))
                if not matches:
                    matches = list((work/'build/obj').glob('*_'+seg['func']+'_*.o'))
            if len(matches) != 1:
                holds.append([image, seg['func'], f'0x{off:X}', seg['size'], f'original object lookup returned {len(matches)} candidates'])
                continue
            original = matches[0]
            mini = module_dir/'module.ld' if module_dir else work/'build'/f'rowbase_{original.stem}.ld'
            rules = mini.read_text() if mini.exists() else window_script
            defs = assignments(rules)
            defs.update({k:v for k,v in window_assignments.items() if k not in defs})
            vma = number(seg.get('rowbase_link_vram', seg['vram']))
            if base is not None and vma != base+off-start:
                holds.append([image, seg['func'], f'0x{off:X}', seg['size'], 'compile VMA differs from selected load image; retain import'])
                continue
            values = nm(original)
            # rodata-first modules have a dedicated mini-link description: retain their
            # baseline bytes until the complete module can be placed faithfully.
            if not allocations and any(k.upper() in ['R','D'] and k != 'U' for _, k, _ in values) and mini.exists() and '.out_' not in rules:
                holds.append([image, seg['func'], f'0x{off:X}', seg['size'], 'rodata-first original object needs dedicated placement'])
                continue
            sections = run(['mipsel-linux-gnu-objdump', '-h', original])
            text_sections = re.findall(r'^\s*\d+\s+(\.text(?:\.[^\s]+)?)\s+([0-9a-fA-F]+)', sections, re.M)
            mode = '.text.*' if any(n.startswith('.text.') and int(nbytes,16) for n,nbytes in text_sections) else '.text'
            text_size = sum(int(nbytes,16) for n,nbytes in text_sections if (n.startswith('.text.') if mode=='.text.*' else n=='.text'))
            if text_size > seg['size']:
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
                all_sections = re.findall(r'^\s*\d+\s+(\.[^\s]+)\s+([0-9a-fA-F]+)', sections, re.M)
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
            for line in run(['mipsel-linux-gnu-objdump','-t',original]).splitlines():
                fields=line.split()
                if len(fields)>=5 and fields[-3] in offsets:
                    symbol_offsets[fields[-1]]=offsets[fields[-3]]+int(fields[0],16)
            if seg.get('source') and Path(seg['source']).is_absolute():
                seg = dict(seg, source=relative(seg['source']))
            segment = dict(seg=seg, off=off, vma=vma, original=original, placed=placed,
                           rules=rules, defs=defs, values=values, prefix=prefix, mode=mode, text_size=text_size,
                           symbol_offsets=symbol_offsets, tu_id=tu_id, allocations=allocations)
            segments.append(segment)
        # Preserve exactly the per-object proven address for every relocation. Resolve
        # to a real definition only if its linked address agrees with that witness.
        local_defs = collections.defaultdict(list)
        for s in segments:
            for name, kind, value in s['values']:
                if kind.isupper() and kind not in ['U', 'A', 'N']:
                    local_defs[name].append((s, s['vma']+s['symbol_offsets'].get(name,value)))
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
                    if name in resident and resident[name] == expected:
                        renamed = name
                        needed_resident.append([image, f"0x{s['off']:X}", name, f'0x{expected:08X}', 'actual SLUS definition'])
                    elif candidates:
                        renamed = candidates[0][0]['prefix']+name
                        local_links.append([image, f"0x{s['off']:X}", name, f'0x{expected:08X}', candidates[0][0]['seg']['func']])
                    elif expected in resident_by_address and 0x8002d000 <= expected < 0x80081800:
                        renamed = sorted(resident_by_address[expected], key=lambda n:(not n.startswith(('func_', 'D_')),n))[0]
                        needed_resident.append([image, f"0x{s['off']:X}", name, f'0x{expected:08X}', 'SLUS definition selected by equal address: '+renamed])
                    elif expected is not None:
                        symbols.append(f'{renamed} = 0x{expected:08X};')
                        fallback_bindings.append([image, f"0x{s['off']:X}", name, f'0x{expected:08X}', 'per-window address witness; owner object outside prototype'])
                    else:
                        raise RuntimeError(f'unresolved {image} {s["seg"]["func"]} {name}')
                renames.append(f'{name} {renamed}\n')
            rename_file = SCRATCH/(s['placed'].stem+'.rename.txt')
            rename_file.write_text(''.join(renames))
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
    slus_defined = set(resident)
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
    (HERE/'global.ld').write_text(script)
    response = SCRATCH/'objects.rsp'
    response.write_text('\n'.join(relative(obj) for obj in objects)+'\n')
    elf = SCRATCH/'onelink.elf'
    argv = ['mipsel-linux-gnu-ld','-EL','--no-check-sections','-T',relative(HERE/'global.ld'),
            '-Map',relative(SCRATCH/'onelink.map'),'-o',relative(elf),'@'+relative(response)]
    (HERE/'link_command.json').write_text(json.dumps(dict(argv=argv, original_slus_objects=len(slus_inputs),
                                                       input_objects=len(objects)),indent=2)+'\n')
    result = subprocess.run(argv,cwd=ROOT,capture_output=True,text=True)
    (SCRATCH/'link.log').write_text(result.stdout+result.stderr)
    if result.returncode:
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
    summary = dict(images=spec_counts, slus_bytes=len(got), slus_differing_bytes=diffs,
                   original_slus_objects=len(slus_inputs), original_overlay_objects=len(object_rows), graph_schema=GRAPH.manifest['schema'], graph_base=GRAPH.manifest['base'], symbol_qualification='stable image, graph TU home and placement row (assembly uses stable container/row identity)',
                   resident_bindings=len(needed_resident), local_bindings=len(local_links),
                   fallback_bindings=len(fallback_bindings), held_rows=len(holds),
                   final_link_invocations=1, note='baseline links are prerequisites, not counted as final combined invocation')
    (HERE/'prototype_summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print(json.dumps(summary,indent=2))
    if holds or any(r[2] != 'MATCH' or r[7] != 'MATCH' for r in comparison_rows):
        raise RuntimeError('combined proof has held source objects or byte differences')


if __name__ == '__main__':
    main()
