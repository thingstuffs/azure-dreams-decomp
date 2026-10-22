#!/usr/bin/env python3
"""Experimental make projection of the registered recipes and load-image graph.

No gate receipts or production authority are written. Generated files, objects,
imports and linked images live in build/; only this generator is source.
"""
import argparse
import bisect
from collections import Counter
import copy
from contextlib import contextmanager
import hashlib
import json
import mmap
import os
from pathlib import Path
import re
import shlex
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
from tools.link.graph import Graph, number
from tools.link.combined import selected_images, object_metadata, slus_origins
from tools.link.prepare import load_gate, linklist_snapshot
from tools.build import content_cache
from tools.build.recipe_cache import RecipeCache, load as load_recipe_cache

STATE = ROOT / 'build/.state'
GENERATION_WRITES = None
RECIPE_CACHE = None
CONTAINERS = {'main': 'MAIN_MAIN.BIN', 'town': 'TOWN_TOWN.BIN',
              'dungeon': 'DUNGEON_DUNGEON.BIN', 'ovmovie': 'OVMOVIE.BIN'}


def rel(path):
    # Paths passed here are already rooted; avoid constructing several pathlib
    # objects per recipe/input in the 18,000-row enumeration.
    value = os.path.abspath(path)
    prefix = os.fspath(ROOT) + os.sep
    if not value.startswith(prefix):
        raise ValueError('path outside build root: ' + value)
    return value[len(prefix):]


def sha(blob):
    return hashlib.sha256(blob).hexdigest()


def write(path, blob):
    path = Path(path)
    if GENERATION_WRITES is not None:
        GENERATION_WRITES.add(rel(path))
    if isinstance(blob, str):
        blob = blob.encode()
    path.parent.mkdir(parents=True, exist_ok=True)
    if not path.exists() or path.read_bytes() != blob:
        temporary = path.with_name(path.name + '.tmp')
        temporary.write_bytes(blob)
        temporary.replace(path)


def stamp(kind):
    """Content digest of a stamp's inputs: a stamp only changes when its inputs' bytes do."""
    names = read(STATE/(kind+'.list'))
    return json.dumps(dict(kind=kind, inputs=hash_inputs(names)), sort_keys=True, indent=1) + '\n'


def write_stamp(kind):
    write(STATE/(kind+'.ok'), stamp(kind))


def put(path, value):
    write(path, json.dumps(value, sort_keys=True, indent=2) + '\n')


def read(path):
    return json.loads(Path(path).read_text())


def run(argv, **kw):
    result = subprocess.run(list(map(str, argv)), cwd=kw.pop('cwd', ROOT),
                            capture_output=True, text=True, **kw)
    if result.returncode:
        raise ValueError(shlex.join(map(str, argv)) + '\n' + result.stderr[-5000:])
    return result.stdout


def configure_inputs(extra=(), inventory_receipt=None):
    # Landing/accounting code and ordinary documentation cannot alter a recipe.
    # Review inputs are added explicitly below, including reviews outside docs/.
    irrelevant = {'tools/build/land_make.py', 'tools/build/make_evidence.py'}
    names = content_cache.inventory(ROOT, ('src', 'include', 'config', 'tools/build',
                                          'tools/gate', 'tools/link', 'tools/fidelity'), irrelevant)
    if inventory_receipt is not None:
        inventory_receipt.update(names)
    names.update(['tools/common.py', 'tools/source_layout.py', 'tools/row_db.py',
                  'tools/overlay_module_evidence.py'])
    manifest = content_cache.load(ROOT/'config/overlays/modules.json')
    names.update(n for m in manifest.get('modules', ()) for n in m.get('review_inputs', ()))
    ledgers = content_cache.inventory(ROOT, ('ledger',))
    names.update(ledgers)
    if inventory_receipt is not None:
        inventory_receipt.update(ledgers)
    names.update('work/disc/containers/' + name for name in CONTAINERS.values())
    names.update(['work/disc/extract/SLUS_006.14', 'baserom/slus_006.14'])
    names.update(['toolchain/genuine/bin/wibo', 'toolchain/genuine/psyq/psyq4.4/ASPSX.EXE'])
    names.update(['ledger/rows.jsonl', 'ledger/layout.jsonl', 'ledger/layout_inline.jsonl',
                  'ledger/tu_layout.jsonl', 'ledger/modules.jsonl', 'ledger/containers.jsonl',
                  'ledger/instance_load_regions.jsonl'])
    names.update(n for n in extra if n not in irrelevant and not n.startswith(('build/.state/', 'build_slus/build/partition_sources/')))
    return names


def configure_links(views=True):
    result = content_cache.links(ROOT, ('src', 'include', 'config', 'tools', 'ledger'))
    if views:
        result.update(content_cache.links(ROOT, ('build_ovl', 'build_slus'), prune=('build', 'work')))
    return result


def configure_environment():
    return {k:v for k,v in os.environ.items() if k.startswith(('AZURE_', 'MASPSX_')) or k in ('RAW', 'EXP', 'SRCROOT')}


def bootstrap_source_inputs():
    """Conservative source read set for the registered bootstrap producers.

    View projection/export depends on names and layout, not ordinary TU bytes.
    Native validation may read reviewed storage sources; SLUS module/partition
    producers may inspect their declared sources. Keep those edits on the full
    bootstrap path. Unknown/missing manifests also keep the full path.
    """
    overlay = ROOT/'config/overlays/modules.json'
    slus = ROOT/'config/slus_modules.json'
    if not overlay.is_file() or not slus.is_file():
        return None
    from tools.gate.source_layout import slus_source
    def strings(value):
        if isinstance(value, str):
            yield value
        elif isinstance(value, dict):
            for v in value.values():
                yield from strings(v)
        elif isinstance(value, list):
            for v in value:
                yield from strings(v)
    names = set()
    for manifest in ('config/overlays/modules.json', 'config/overlays/module_placements.json',
                     'config/slus_modules.json', 'config/slus_partitions.json'):
        path = ROOT/manifest
        if not path.is_file():
            continue
        for name in strings(read(path)):
            if not name.startswith(('src/', 'include/')):
                continue
            names.add(name)
            resolved = (ROOT/name).resolve()
            if resolved.is_relative_to(ROOT):
                names.add(rel(resolved))
            if manifest.startswith('config/slus_') and name.startswith('src/'):
                names.add(rel(slus_source(name, ROOT)))
    return sorted(names)


def bootstrap():
    snapshot = content_cache.Snapshot(ROOT)
    marker = STATE/'bootstrap.json'
    before = snapshot.hashes(configure_inputs())
    input_links = configure_links(views=False)
    all_links = configure_links()
    previous = content_cache.load(marker)
    valid = (previous.get('root') == str(ROOT) and previous.get('environment') == configure_environment()
            and previous.get('links') == all_links and previous.get('outputs')
            and all(v is not None for v in previous['outputs'].values())
            and snapshot.hashes(previous['outputs']) == previous['outputs'])
    if valid and previous.get('inputs') == before:
        print('Build views unchanged (content verified)', flush=True)
        return
    old = previous.get('inputs', {})
    changed = {n for n in set(old) | set(before) if old.get(n) != before.get(n)}
    sensitive = previous.get('source_sensitive')
    if (valid and sensitive is not None and set(old) == set(before)
            and all(old[n] is not None and before[n] is not None
                    and n.startswith(('src/', 'include/')) and n not in sensitive for n in changed)):
        # Every view output is current. The name/authority/link guards prove
        # that these particular body edits cannot change bootstrap's outputs.
        # Generate independently checks production recipe/module read sets.
        if before != snapshot.hashes(before) or all_links != configure_links():
            raise ValueError('bootstrap inputs changed during generation')
        put(STATE/'setup.ok', dict(inputs_sha256=sha(json.dumps(before, sort_keys=True).encode())))
        outputs = dict(previous['outputs'])
        outputs['build/.state/setup.ok'] = sha((STATE/'setup.ok').read_bytes())
        content_cache.save(marker, dict(root=str(ROOT), environment=configure_environment(), links=all_links,
                                       inputs=before, outputs=outputs, source_sensitive=sensitive))
        print('Build views unchanged (source-only edit; content verified)', flush=True)
        return
    _bootstrap()
    outputs = content_cache.inventory(ROOT, ('build_ovl/tools', 'build_slus/config/generated', 'build_slus/asm', 'build_slus/assets'))
    outputs.update(['build_slus/build.ninja', 'build_slus/build/slus_006.14.ld', 'build/.state/setup.ok'])
    after = snapshot.hashes(configure_inputs())
    # The module graph is a bootstrap output, included in the next input snapshot.
    graph_output = 'ledger/splits/overlay_modules.build.json'
    if {k:v for k,v in before.items() if k != graph_output} != {k:v for k,v in after.items() if k != graph_output}:
        raise ValueError('bootstrap inputs changed during generation')
    if input_links != configure_links(views=False):
        raise ValueError('bootstrap input links changed during generation')
    put(STATE/'setup.ok', dict(inputs_sha256=sha(json.dumps(after, sort_keys=True).encode())))
    content_cache.save(marker, dict(root=str(ROOT), environment=configure_environment(), links=configure_links(),
                                    inputs=after, outputs=snapshot.hashes(outputs),
                                    source_sensitive=bootstrap_source_inputs()))


def _bootstrap():
    run(['bash', 'tools/build/mk_slus_root.sh'])
    view = ROOT / 'build_slus'
    split_script = view/'build/slus_006.14.ld'
    if not split_script.exists() or (ROOT/'config/slus_006.14.yaml').stat().st_mtime_ns > split_script.stat().st_mtime_ns:
        run(['.venv/bin/splat', 'split', 'config/slus_006.14.yaml'], cwd=view)
    run(['python3', 'tools/configure.py'], cwd=view)
    run(['bash', 'tools/build/mk_ovl_root.sh'])
    STATE.mkdir(parents=True, exist_ok=True)
    write(ROOT / 'build/.ignore', '*\n')
    write(ROOT / 'build/.gitignore', '*\n')


def make_path(value):
    if any(c in value for c in '\n\r:#$%\\ '):
        raise ValueError('unsupported make path: ' + value)
    return value


def rule(targets, deps, command):
    targets = list(map(make_path, targets))
    deps = sorted(set(map(make_path, deps)))
    op = ' &:' if len(targets) > 1 else ':'
    return (' '.join(targets) + op + ' ' + ' '.join(deps) + '\n\t@' +
            command.replace('$', '$$') + '\n\n')


def ninja_edges(text):
    """Read the deliberately small Ninja dialect emitted by configure.py.

    Expand its commands verbatim; do not maintain a second SLUS compiler table.
    Reject new syntax rather than silently dropping dependencies.
    """
    rules, globals_, edges = {}, {}, []
    current = None
    for line in text.splitlines():
        if not line or line.startswith('#') or line.startswith('default '):
            continue
        if line.startswith('  '):
            key, value = line.strip().split(' =', 1)
            value = value.lstrip()
            current[key] = value
        elif line.startswith('rule '):
            current = rules.setdefault(line[5:], {})
        elif line.startswith('build '):
            outputs, rest = line[6:].split(': ', 1)
            tokens = rest.split()
            edge = dict(outputs=outputs.split(), rule=tokens.pop(0), explicit=[], deps=[], vars={})
            implicit = False
            for token in tokens:
                if token in ('|', '||'):
                    implicit = True
                else:
                    edge['deps'].append(token)
                    if not implicit:
                        edge['explicit'].append(token)
            edges.append(edge)
            current = edge['vars']
        elif ' = ' in line:
            key, value = line.split(' = ', 1)
            globals_[key] = value
            current = globals_
        else:
            raise ValueError('unsupported Ninja syntax: ' + line[:100])
    for edge in edges:
        variables = dict(globals_, **edge['vars'], **{'in': ' '.join(edge['explicit']),
                         'out': ' '.join(edge['outputs'])})
        def expand(value):
            return re.sub(r'\$(?:\{(\w+)\}|(\w+)|(.))',
                          lambda m: expand(variables.get(m[1] or m[2], '')) if m[1] or m[2] else m[3], value)
        edge['command'] = '' if edge['rule'] == 'phony' else expand(rules[edge['rule']]['command'])
    return edges


def one_script_command(command):
    argv = shlex.split(command)
    transformed, fragments = [], []
    cursor = 0
    while cursor < len(argv):
        if argv[cursor] == '-T':
            fragments.append('build_slus/' + argv[cursor+1])
            if len(fragments) == 1:
                transformed += ['-T', '../build/.state/link/slus_slus_bin/image.ld']
            cursor += 2
        else:
            transformed.append(argv[cursor])
            cursor += 1
    if not fragments:
        raise ValueError('SLUS recipe has no linker script')
    return transformed, fragments


def slus_script():
    graph = Graph(ROOT/'config/link_graph')
    fragments = read(STATE/'slus_scripts.json')
    if fragments[0] != graph.manifest['build']['slus']['recipe']:
        raise ValueError('SLUS recipe differs from graph registration')
    text = ['/* Generated from link graph SLUS recipe; original fragment order. */']
    for name in fragments:
        text += ['/* ' + name + ' */', (ROOT/name).read_text()]
    write(STATE/'link/slus_slus_bin/image.ld', '\n'.join(text)+'\n')


def slus_rules(headers):
    edges = ninja_edges((ROOT / 'build_slus/build.ninja').read_text())
    # A cold checkout has not rendered partition bodies yet. Use the registered
    # producer verbatim before scanning includes; it validates coverage and
    # preserves content-identical output mtimes. The emitted make edge remains.
    for edge in edges:
        if edge['rule'] == 'partition_render':
            run(['bash', '-c', edge['command']], cwd=ROOT/'build_slus')
            if GENERATION_WRITES is not None:
                GENERATION_WRITES.update('build_slus/' + n for n in edge['outputs'])
    output, cc = [], 0
    for edge in edges:
        if edge['rule'] == 'sha1':
            continue
        deps = ['build_slus/' + d for d in edge['deps']]
        if edge['rule'] in ('cc', 'as'):
            deps += ['build/.state/compiletools.ok']
            import overlay_module_gate as M
            starts = [d for d in edge['explicit'] if d.endswith(('.c', '.s'))]
            deps += ['build_slus/' + d for d in include_closure(M, ROOT/'build_slus', starts)]
        if edge['rule'] == 'cc':
            cc += 1
        targets = ['build_slus/' + t for t in edge['outputs']]
        directories = sorted({str(Path(t).parent) for t in targets})
        if edge['rule'] == 'phony':
            output.append(' '.join(targets) + ': ' + ' '.join(sorted(set(deps))) + '\n')
            continue
        if edge['rule'] == 'link':
            argv, fragments = one_script_command(edge['command'])
            put(STATE/'slus_scripts.json', fragments)
            script = 'build/.state/link/slus_slus_bin/image.ld'
            output.append(rule([script], fragments + ['config/link_graph/graph.json'], 'python3 tools/build/mkbuild.py slus_script'))
            deps.append(script)
            edge['command'] = shlex.join(argv + ['-Map', 'build/slus_006.14.map'])
        clean_env = 'env -u AZURE_MASPSX -u AZURE_MASPSX_COMPANION -u MASPSX_NORETURN_FILE -u MASPSX_SIBCALL_FILE '
        command = 'mkdir -p ' + shlex.join(directories) + '; cd build_slus && ' + clean_env + 'bash -c ' + shlex.quote(edge['command'])
        output.append(rule(targets, deps, command))
    output.append(rule(['build/slus_slus_bin.bin'], ['build_slus/build/slus_006.14'],
                       'python3 tools/build/mkbuild.py slus'))
    return output, cc


def module_allocations(m, G):
    if G.Z.enabled(m):
        return [{k: a[k] for k in ('section', 'foff', 'vma', 'size', 'link_alignment')}
                for a in m['allocations']]
    first = G.module_first(m)
    prefix = sum(a['size'] for a in m['owned_data'])
    result = []
    if prefix:
        result.append(dict(section='.rodata', foff=first['foff'], vma=first['vma'],
                           size=prefix, link_alignment=4))
    result.append(dict(section='.text.*', foff=first['foff'] + prefix,
                       vma=first['vma'] + prefix, size=G.module_size(m) - prefix, link_alignment=4))
    return result


@contextmanager
def immutable_selection(gate):
    """Memoize read-only recipe tables inside one content-guarded generation.

    The production rowbase selector is called once per distinct interval, at a
    representative offset with identical interval membership. Its return value
    and validation remain authoritative. Nothing is persisted as gate evidence.
    """
    import gate_read_cache as cache
    records_original, delta_original = cache.read_records, gate._rowbase_proven_delta
    decoded, hashes, boundaries, answers = {}, {}, {}, {}
    def records(path):
        key = Path(path).absolute()
        if key not in decoded:
            hashes[key] = sha(key.read_bytes())
            decoded[key] = records_original(path)
        return decoded[key]
    def delta(family, offset):
        if family not in boundaries:
            path = gate.cfg_path(f'config/overlays/{family}.rowbase.jsonl')
            edges = {0}
            if path.exists():
                for r in records(path):
                    edges.update((number(r['foff_start']), number(r['foff_end'])))
            boundaries[family] = sorted(edges)
        edge = boundaries[family][bisect.bisect_right(boundaries[family], offset)-1]
        key = (family, edge)
        if key not in answers:
            answers[key] = delta_original(family, edge)
        return answers[key]
    cache.read_records, gate._rowbase_proven_delta = records, delta
    try:
        yield
    finally:
        cache.read_records, gate._rowbase_proven_delta = records_original, delta_original
        if any(sha(path.read_bytes()) != expected for path,expected in hashes.items()):
            raise ValueError('recipe selection inputs changed during generation')


INPUT_DIGESTS = {}

def hash_inputs(paths):
    result = {}
    for name in sorted(set(paths)):
        path = ROOT/name
        st = path.stat()
        stamp = (st.st_dev, st.st_ino, st.st_size, st.st_mtime_ns, st.st_ctime_ns)
        previous = INPUT_DIGESTS.get(str(path))
        if previous is None or previous[0] != stamp:
            previous = (stamp, sha(path.read_bytes()))
            INPUT_DIGESTS[str(path)] = previous
        result[name] = previous[1]
    return result


def genuine_status():
    paths = ['toolchain/genuine/bin/wibo', 'toolchain/genuine/psyq/psyq4.4/ASPSX.EXE']
    missing = [p for p in paths if not (ROOT/p).is_file()]
    if missing:
        return dict(mode='maspsx_only', missing=missing,
                    description='maspsx only; genuine ASPSX unavailable: ' + ', '.join(missing) + '; provision with tools/setup.sh --psyq DIR')
    return dict(mode='genuine_aspsx_verified', tools=hash_inputs(paths),
                description='native TUs use the canonical whole-TU genuine ASPSX 2.79 comparison; final ELF objects use maspsx')


def attest_graph(graph, registry):
    """Refresh source/layout witnesses; retain independent graph extent/cell guards."""
    sys.path.insert(0, str(ROOT/'tools'))
    from gate.source_layout import row_relative
    inputs = hash_inputs(graph.manifest.get('inputs', {}))
    for path in ('ledger/containers.jsonl', 'ledger/splits/slus.jsonl', 'ledger/instance_load_regions.jsonl'):
        if inputs[path] != graph.manifest['inputs'][path]:
            raise ValueError('graph layout authority changed: ' + path)
    tus, placements = {}, {}
    modules = {m['key']: m for m in read(ROOT/'config/overlays/modules.json')['modules']}
    for key, tu in graph.tus.items():
        if key.startswith('module/'):
            m = modules[key[7:]]
            if tu['recipe_witness'] != m['recipe']:
                raise ValueError('graph TU/cell disagrees: ' + key)
            source, recipe = m['source'], m['recipe']
            home = key
        else:
            row = registry[key]
            home = row.get('source_row') or key
            if tu['recipe_witness'].get('cfg') != row['cfg']:
                raise ValueError('graph TU/cell disagrees: ' + key)
            source = row_relative(registry[home], ROOT)
            recipe = {k: registry[home].get(k) for k in ('cfg', 'row_asflags', 'gate_config')}
        if not (ROOT/source).resolve().is_relative_to(ROOT):
            raise ValueError('graph TU escapes checkout: ' + key)
        tus[key] = dict(home=home, source=source, source_sha256=sha((ROOT/source).read_bytes()), recipe=recipe)
    for key, entry in graph.entries.items():
        if entry['kind'] != 'tu':
            continue
        a, witness = entry['attributes'], graph.tus[entry['tu']]['recipe_witness']
        row = registry[a['row']]
        if (row['foff'], row['size'], row['cfg']) != (number(a['foff']), number(a['size']), witness['cfg']):
            raise ValueError('live registry differs from graph placement: ' + a['row'])
        placements[key] = dict(row=row['id'], home=row.get('source_row') or row['id'],
                               cfg=row['cfg'], row_asflags=row.get('row_asflags'))
    return dict(schema='azure-clean.live-graph.v1', inputs=inputs, tus=tus, placements=placements)


def build_native(spec, target):
    """Use the existing native builder, including its real ASPSX leg, once per TU."""
    import tempfile
    import types
    load_gate(ROOT)
    import overlay_module_gate as M
    # Keep the SDK's short DOS paths and every temporary file in this checkout.
    proxy = types.SimpleNamespace(TemporaryDirectory=lambda **kw: tempfile.TemporaryDirectory(prefix='g', dir=STATE/'tmp'))
    old_m, old_z = M.tempfile, M.Z.tempfile
    M.tempfile = M.Z.tempfile = proxy
    try:
        receipt, _ = M.build(spec['module'], STATE/'native'/spec['module']['key'], ROOT, artifact_only=True)
    finally:
        M.tempfile, M.Z.tempfile = old_m, old_z
    if receipt['genuine']['result'] != 'MATCH':
        raise ValueError('canonical genuine ASPSX comparison failed')
    shutil.copyfile(STATE/'native'/spec['module']['key']/'module.o', target)


def extend_checks(images, recipes, row_plans, registry, modules, module_jobs, docs, gate):
    """Every compiled recipe gets a byte-checked placement, including diagnostic layouts."""
    by_extent = {}
    for row in registry.values():
        if row.get('foff') is not None:
            by_extent.setdefault((row['container'], row['foff'], row['size']), []).append(row)
    for family in CONTAINERS:
        for line in (ROOT/'ledger/splits'/(family+'.jsonl')).read_text().splitlines():
            r = json.loads(line)
            if r.get('result') == 'MATCH' and r.get('source_kind') in {'platform_asm', 'game_asm'}:
                row = dict(r, id=family+'/'+r['func_vram'], container=family)
                by_extent.setdefault((family, r['foff'], r['size']), []).append(row)
    row_lookup = dict(registry)
    row_lookup.update((r['id'],r) for values in by_extent.values() for r in values)
    def unit_rows(family, unit):
        if not unit.get('module'):
            return [r['id'] for r in by_extent.get((family, unit['off'], unit['size']), [])]
        import overlay_module_gate as M
        m = modules[unit['module']]
        delta = unit['allocations'][0]['foff']-module_allocations(m, M)[0]['foff']
        return [r['id'] for a in M.all_members(m)
                for r in by_extent.get((family, a['foff']+delta, a['size']), [])]
    for spec in images.values():
        for u in spec['units']:
            u['rows'] = unit_rows(spec['image'].split('/')[0], u)
    used = {u['recipe'] for spec in images.values() for u in spec['units']}
    outside = []
    for key in sorted(set(recipes)-used):
        recipe = recipes[key]
        if 'module' in recipe:
            m = recipe['module']
            import overlay_module_gate as M
            family = m['container']
            allocations = module_allocations(m, M)
            start = min(a['foff'] for a in allocations)
            end = max(a['foff']+a['size'] for a in allocations)
            unit = dict(recipe=key, allocations=allocations, imports={a['symbol']:a['vma'] for a in m['imports']}, module=m['key'])
        else:
            family, start, size = next(k for k,v in row_plans.items() if v['recipe'] == key)
            plan = row_plans[(family,start,size)]
            vma = plan['recipe_vma']
            if vma is None:
                rows = by_extent.get((family,start,size), [])
                if not rows:
                    raise ValueError('extra recipe has no registered placement: ' + key)
                window = gate.load_yaml(ROOT/rows[0]['gate_config'])['standalone_build']['window']
                vma = number(window['vram_start']) + start-number(window['file_start'])
            end = start+size
            unit = dict(plan, off=start, size=size, vma=vma)
        unit['rows'] = unit_rows(family, unit)
        rows = [row_lookup[r] for r in unit['rows']]
        containing = sorted(image for image,doc in docs.items() if doc['container'] == family
                            and number(doc['foff']) <= start and end <= number(doc['foff'])+number(doc['size']))
        if any(r.get('source_row') for r in rows):
            category = 'placement-only view'
        elif containing:
            category = 'alternate bank layout'
        else:
            category = 'diagnostic/relink copy window'
        image = family+'/check_'+key
        tag = image.replace('/', '_')
        images[tag] = dict(image=image, tag=tag, container='work/disc/containers/'+CONTAINERS[family],
                           start=start, size=end-start, vma=None, units=[unit], output='build/'+tag+'.bin',
                           document={}, check_recipe=key)
        outside.append(dict(recipe=key, rows=unit['rows'], windows=sorted({r['gate_config'] for r in rows}),
                            classification=category, source=recipe['source'], graph_views=containing,
                            why='registered MATCH recipe has no allocation in the 402 selected load extents',
                            image=image, start=start, size=end-start, resolution='compile, link and compare this extra layout with the disc extent'))
    return outside


def extend_placement_checks(images, recipes, row_plans, registry, modules, module_jobs, placements, gate):
    """Cover remaining registered placements even when their recipe was checked elsewhere."""
    import overlay_module_gate as M
    covered = {r for image in images.values() for u in image['units'] for r in u.get('rows', [])}
    candidates = []
    for m in modules.values():
        candidates.append((m, M.all_members(m), module_allocations(m,M), m['imports']))
    for p in placements:
        m = modules[p['module']]
        delta = p['projected'][0]['foff']-M.module_first(m)['foff']
        vdelta = p['projected'][0]['vma']-M.module_first(m)['vma']
        allocations = p.get('allocations') or [dict(a,foff=a['foff']+delta,vma=a['vma']+vdelta) for a in module_allocations(m,M)]
        candidates.append((m,p['projected'],allocations,p['imports']))
    checks, holds = [], []
    for rid,row in sorted(registry.items()):
        if row['kind'] != 'overlay' or rid in covered:
            continue
        family, start, size = row['container'],row['foff'],row['size']
        plan = row_plans.get((family,start,size))
        if plan:
            vma = plan['recipe_vma']
            if vma is None:
                window = gate.load_yaml(ROOT/row['gate_config'])['standalone_build']['window']
                vma = number(window['vram_start'])+start-number(window['file_start'])
            unit = dict(plan,off=start,size=size,vma=vma,rows=[rid])
            end = start+size
        else:
            candidate = next((c for c in candidates if any(a['id']==rid for a in c[1])),None)
            if candidate is None:
                holds.append(dict(row=rid,reason='no production ordinary recipe or complete native placement',window=row['gate_config']))
                continue
            m,members,allocations,imports = candidate
            start = min(a['foff'] for a in allocations);end = max(a['foff']+a['size'] for a in allocations)
            unit = dict(recipe=module_jobs[m['key']],module=m['key'],allocations=allocations,
                        imports={a['symbol']:a['vma'] for a in imports},rows=[a['id'] for a in members])
        covered.update(unit['rows'])
        image = family+'/check_place_'+sha(rid.encode())[:24];tag=image.replace('/','_')
        images[tag] = dict(image=image,tag=tag,container='work/disc/containers/'+CONTAINERS[family],start=start,size=end-start,
                           vma=None,units=[unit],output='build/'+tag+'.bin',document={})
        checks.append(dict(image=image,start=start,size=end-start,recipe=unit['recipe'],rows=unit['rows'],
                           windows=sorted({registry[r]['gate_config'] for r in unit['rows']}),reason='recipe proven elsewhere; this registered placement was outside the selected extents'))
    if holds:
        put(STATE/'placement_holds.json',holds)
        raise ValueError('unproven registered placements: '+', '.join(r['row'] for r in holds[:10]))
    return checks


def include_closure(module, root, starts):
    return RECIPE_CACHE.closure(module, root, starts) if RECIPE_CACHE is not None else module.closure(root, starts)


def checkpoint(key, produce, dependencies=None, copy_value=True):
    return RECIPE_CACHE.memo(key, produce, dependencies, copy_value) if RECIPE_CACHE is not None else produce()


@contextmanager
def cached_selection(gate):
    """Retain authoritative module validation until one of its reads changes."""
    import overlay_module_gate as M
    import overlay_module_placements as P
    module_load, placement_load = M.load_modules, P.load
    M.load_modules = lambda root=M.ROOT: checkpoint('modules', lambda: module_load(root)) if Path(root) == gate.ROOT else module_load(root)
    P.load = lambda root, modules=None: checkpoint('placements', lambda: placement_load(root, modules)) if Path(root) == gate.ROOT else placement_load(root, modules)
    try:
        with linklist_snapshot(gate):
            yield
    finally:
        M.load_modules, P.load = module_load, placement_load


def generate(full=False):
    global GENERATION_WRITES, RECIPE_CACHE
    # Lazy producer imports must not create bytecode directories inside the
    # observed read set. Source/configuration bytes remain the authority.
    sys.dont_write_bytecode = True
    snapshot = content_cache.Snapshot(ROOT)
    marker = STATE/'configure.json'
    previous = content_cache.load(marker)
    before_inventory = set()
    names = configure_inputs(previous.get('inputs', ()), before_inventory)
    names.add('build_slus/build.ninja')
    before = snapshot.hashes(names)
    input_links = configure_links()
    observed_now = {n: RecipeCache.hash_at(ROOT, n) for n in previous.get('observed', {})}
    context = dict(schema=1, root=str(ROOT), environment=configure_environment(), links=input_links)
    compatible = (previous.get('root') == str(ROOT) and previous.get('environment') == context['environment']
                  and previous.get('links') == input_links)
    outputs_valid = (compatible and previous.get('outputs')
                     and all(v is not None for v in previous['outputs'].values())
                     and snapshot.hashes(previous['outputs']) == previous['outputs'])
    if (not full and outputs_valid and previous.get('inputs') == before
            and observed_now == previous.get('observed', {})):
        print('Make projection unchanged (inputs and generated bytes verified)', flush=True)
        return
    load_gate(ROOT)
    import overlay_module_gate as M
    cache_path = STATE/'configure-cache.json.gz'
    saved = load_recipe_cache(cache_path) if not full and outputs_valid and rel(cache_path) in previous['outputs'] else {}
    RECIPE_CACHE = RecipeCache(ROOT, before, context, saved)
    RECIPE_CACHE.digests.update(observed_now)
    cache = RECIPE_CACHE
    GENERATION_WRITES = set()
    try:
        with M.closure_snapshot():
            _generate()
        outputs = GENERATION_WRITES
        outputs.add(rel(cache_path))
        print(f'Configure checkpoints: {RECIPE_CACHE.hits} reused, {RECIPE_CACHE.misses} regenerated', flush=True)
    finally:
        GENERATION_WRITES = None
        RECIPE_CACHE = None
    after_links = configure_links()
    if before != snapshot.hashes(names) or input_links != after_links or not cache.extra_unchanged():
        raise ValueError('configure inputs changed during generation')
    index = read(STATE/'index.json')
    # Projected sources and frozen evidence are replayed with write(), even on
    # checkpoint hits. They are already in outputs; do not parse 8,859 recipes.
    after_inventory = set()
    names = configure_inputs(index['inputs'], after_inventory) | {'build_slus/build.ninja'}
    if before_inventory != after_inventory:
        raise ValueError('configure input inventory changed during generation')
    final_inputs = {n: before[n] for n in names if n in before}
    final_inputs.update(snapshot.hashes(names - set(before)))
    # A cold tree discovers compiler/recipe inputs while enumerating. Bind the
    # completed inventory now so its first later source edit can reuse it.
    cache.guard = cache.guard_for(final_inputs, context)
    write(cache_path, cache.blob())
    content_cache.save(marker, dict(root=str(ROOT), environment=configure_environment(), links=after_links,
                                   inputs=final_inputs, outputs=snapshot.hashes(outputs),
                                   observed={n:cache.digests[n] for n in cache.used if n not in final_inputs and n not in outputs}))


def _generate():
    print('Reading link graph and live registry', flush=True)
    def graph_model():
        g = Graph(ROOT / 'config/link_graph')
        return dict(manifest=g.manifest, files=g.files, tus=g.tus, entries=g.entries,
                    docs=g.documents(validate=True))
    from types import SimpleNamespace
    model = checkpoint('graph', graph_model, copy_value=False)
    graph = SimpleNamespace(**{k:v for k,v in model.items() if k != 'docs'})
    registry = {r['id']: r for r in map(json.loads, (ROOT/'ledger/rows.jsonl').read_text().splitlines())}
    # Source bytes do not choose a graph recipe/placement. Reuse the validated
    # structure, then refresh EVERY live source/input digest from this snapshot.
    attestation = checkpoint('attestation-model', lambda: attest_graph(graph, registry), lambda value: [])
    if RECIPE_CACHE is not None:
        attestation['inputs'] = {n: RECIPE_CACHE.digest(n) for n in graph.manifest.get('inputs', {})}
        for tu in attestation['tus'].values():
            tu['source_sha256'] = RECIPE_CACHE.digest(tu['source'])
    put(STATE/'graph_attestation.json', attestation)
    docs = model['docs']
    gate = load_gate(ROOT)
    import linklist
    import overlay_module_gate as M
    import overlay_module_placements as P
    import overlay_evidence as E
    recipes, row_plans, images = {}, {}, {}
    capture = {}
    replayed = {}
    def replay(name, text):
        if name in replayed:
            if replayed[name] != text:
                raise ValueError('conflicting configure artifact: '+name)
            return
        write(ROOT/name, text)
        replayed[name] = text
    registered_extents = {(r['container'], r.get('foff'), r['size']): r for r in registry.values()}
    phase_cache = {}
    sdk = genuine_status()
    print('Assembler: ' + sdk['description'], flush=True)
    STATE.mkdir(parents=True, exist_ok=True)

    def record(argv, **kwargs):
        source = Path(argv[1]).resolve()
        if not source.is_relative_to(ROOT):
            raise ValueError('source escapes root')
        env = {}
        for key, value in (kwargs.get('env') or {}).items():
            if key.startswith('MASPSX_') and key.endswith('_FILE'):
                blob = Path(value).read_bytes() if Path(value).exists() else b''
                # Comments/ordering are immaterial to maspsx's symbol sets.
                blob = ('\n'.join(sorted(E.load_noreturn_file(value))) + '\n').encode()
                target = STATE / 'evidence' / (sha(blob) + '.txt')
                write(target, blob)
                env[key] = rel(target)
            else:
                raise ValueError('unhandled compiler environment: ' + key)
        live = capture.get('live')
        spec = dict(source=rel(source), wrapper=rel(argv[0]), args=list(map(str, argv[3:])), env=env, live=live)
        if source.parent.name.endswith('.member') and source.is_relative_to(STATE):
            # T1 member projection: the gate wrote this unit from its home's span in the owner TU.
            # Bind the owner TU and inline ledger, and re-project at compile time (compile_one).
            from gate.source_layout import row_relative
            home = capture.get('home') or family + '/' + source.stem
            spec['projection'] = dict(home=home, owner=str(row_relative(registry[home], ROOT)))
        key = sha(json.dumps(spec, sort_keys=True).encode())[:24]
        spec['output'] = 'build/obj/' + key + '.o'
        spec['declaration_context_sha256'] = sha(source.read_bytes())
        recipes.setdefault(key, spec)
        capture['key'] = key
        return subprocess.CompletedProcess(argv, 0)

    def rebound(root, entry, obj, log=None):
        capture['rebind'] = entry
        return {}

    print('Validating immutable home/module recipe tables', flush=True)
    with immutable_selection(gate), cached_selection(gate), E._gen_noreturn().scoped_census_snapshot():
        print('Selecting registered source rows', flush=True)
        modules = {m['key']: m for m in M.load_modules(gate.ROOT)}
        placements = P.load(gate.ROOT, list(modules.values()))
        module_rows = {(m['container'], a['foff'], a['size']) for m in modules.values() for a in M.all_members(m)}
        module_rows.update((p['container'], a['foff'], a['size']) for p in placements for a in p['projected'])
        matches = {}
        for family, filename in CONTAINERS.items():
            sb = dict(matched_sources=[dict(name=family, results=f'overlays/{family}/overlay_first_pass_results.json',
                       source_dir=f'overlays/{family}/first_pass_matched', skip_rerun=True)])
            def select():
                import dataclasses
                table, _ = gate.load_matches(sb, 0, graph.files[family]['size'], family=family)
                return [dict(dataclasses.asdict(m), source=str(m.source)) for m in table.values()]
            values = checkpoint('matches:'+family, select, copy_value=False)
            matches[family] = {(v['start'], v['size']): gate.MatchEntry(**dict(v, source=Path(v['source']))) for v in values}
        old_run, old_rebind = gate.run, linklist.rebind_object
        gate.run, linklist.rebind_object = record, rebound
        try:
            # One enumeration per physical row, independent of the number of views.
            for family, table in matches.items():
                print('Enumerating', family, len(table), 'rows', flush=True)
                for (off, size), match in table.items():
                    if (family, off, size) in module_rows:
                        continue
                    # A placement compiles with its HOME's evidence: family and frozen scope (decision 75 (A):
                    # the home may live in another container).  The scope is part of the checkpoint key.
                    place = linklist.placement(gate.ROOT, family, off, row=family+'/'+match.source.stem) if match.source_kind == 'c' else None
                    evidence_family, evidence_offset = (linklist.evidence_scope(gate.ROOT, place)
                                                        if place and place['row'] != place['home'] else (family, off))
                    scope_key = '' if (evidence_family, evidence_offset) == (family, off) else f':home={evidence_family}:{evidence_offset}'
                    def enumerate_row():
                        nonlocal capture
                        base_names = E._gen_noreturn().scoped_census(evidence_family, evidence_offset)['names'] if evidence_family in {'town','dungeon'} else E.load_noreturn_file(E.evidence_env(evidence_family).get('MASPSX_NORETURN_FILE', E.DEFAULT_NORETURN_FILE))
                        capture = dict(live=dict(base_names=sorted(base_names))) if match.source_kind == 'c' else {}
                        if place and place['row'] != place['home']:
                            capture['home'] = place['home']
                        segment = gate.Segment(0, match.source_kind, off, off+size,
                            match.link_vram or off, '.text.*', name=match.func, match=match)
                        if match.source_kind == 'c':
                            gate.compile_c_segments([segment], STATE / 'enumerate', env=E.evidence_env(family), overlay=family)
                        else:
                            gate.compile_asm_segments([segment], STATE / 'enumerate')
                        key = capture['key']
                        spec = recipes[key]
                        artifacts = {n: (ROOT/n).read_text() for n in spec['env'].values()}
                        if spec.get('projection'):
                            artifacts[spec['source']] = (ROOT/spec['source']).read_text()
                        plan = dict(recipe=key, rebind=capture.get('rebind'), func=match.func,
                                    source_stem=match.source.stem, recipe_vma=match.link_vram, kind=match.source_kind)
                        return dict(key=key, spec=spec, plan=plan, artifacts=artifacts)
                    cached = checkpoint(f'row:{family}:{off}:{size}{scope_key}', enumerate_row, copy_value=False)
                    recipes.setdefault(cached['key'], dict(cached['spec']))
                    for name, text in cached['artifacts'].items():
                        replay(name, text)
                    row_plans[(family, off, size)] = cached['plan']
        finally:
            gate.run, linklist.rebind_object = old_run, old_rebind
        module_jobs = {}
        def enumerate_module(key, m):
            nonlocal capture
            capture = {}
            source = gate.ROOT / m['source']
            text = source.read_text() + '\n' + '\n'.join((gate.ROOT / a['source']).read_text() for a in m['members'])
            evidence_dir = STATE / 'module_evidence' / key
            evidence_dir.mkdir(parents=True, exist_ok=True)
            env = E.evidence_env_with_candidate(m['container'], text, evidence_dir, foff=M.module_first(m)['foff'])
            if M.Z.enabled(m):
                env = {f'MASPSX_{kind}_FILE': str(gate.ROOT/'config'/f'{kind.lower()}_syms.{m["container"]}.txt') for kind in ('NORETURN','SIBCALL')}
            flags = M.module_cflags(m)
            if M.Z.enabled(m):
                flags += ['-I' + str((gate.ROOT/a['source']).parent.resolve()) for a in m['members']]
            base = E.load_noreturn_file(env['MASPSX_NORETURN_FILE']) if M.Z.enabled(m) else (E._gen_noreturn().scoped_census(m['container'], M.module_first(m)['foff'])['names'] if m['container'] in {'town','dungeon'} else E.load_noreturn_file(E.evidence_env(m['container']).get('MASPSX_NORETURN_FILE', E.DEFAULT_NORETURN_FILE)))
            capture['live'] = dict(base_names=sorted(base), include_own=not M.Z.enabled(m))
            record([gate.ROOT/'tools/cc.sh', source, 'unused', M.module_compiler(m), ' '.join(flags), ''], env=env)
            job = capture['key']
            recipes[job]['module'] = m
            recipes[job]['assembler'] = sdk['mode']
            recipes[job]['declaration_context_sha256'] = sha(text.encode())
            return dict(key=job, spec=recipes[job], artifacts={n:(ROOT/n).read_text() for n in recipes[job]['env'].values()})
        for key, m in modules.items():
            cached = checkpoint('module:'+key, lambda: enumerate_module(key, m), copy_value=False)
            recipes[cached['key']] = dict(cached['spec'])
            for name, text in cached['artifacts'].items():
                replay(name, text)
            module_jobs[key] = cached['key']
        def compose_images():
            images = {}
            for image in selected_images(docs) + ['main/main_bin', 'ovmovie/ovmovie_bin']:
                family = image.split('/')[0]
                doc = docs.get(image, dict(foff=0, size=graph.files[family]['size'], vma=None, entries=[]))
                start, size = number(doc['foff']), number(doc['size'])
                end = start + size
                units, consumed = [], set()
                # Native complete TUs supersede their row members, including separated allocations.
                candidates = [(m, M.all_members(m), module_allocations(m, M), m['imports'])
                              for m in modules.values() if m['container'] == family]
                candidates += [(modules[p['module']], p['projected'],
                    p.get('allocations') or [dict(a, foff=a['foff'] + p['projected'][0]['foff'] - M.module_first(modules[p['module']])['foff'],
                        vma=a['vma'] + p['projected'][0]['vma'] - M.module_first(modules[p['module']])['vma'])
                        for a in module_allocations(modules[p['module']], M)], p['imports'])
                    for p in placements if p['container'] == family]
                for m, members, allocations, imports in candidates:
                    if not all(start <= a['foff'] and a['foff'] + a['size'] <= end for a in allocations):
                        continue
                    consumed.update((a['foff'], a['size']) for a in members)
                    units.append(dict(recipe=module_jobs[m['key']], allocations=allocations,
                                      imports={a['symbol']: a['vma'] for a in imports}, module=m['key']))
                # Follow the production MATCH selector inside each graph load extent.
                for (off, nbytes), match in matches[family].items():
                    if not (start <= off and off+nbytes <= end) or (off, nbytes) in consumed:
                        continue
                    plan = row_plans.get((family, off, nbytes))
                    if plan is None:
                        raise ValueError('partial native TU in image: ' + image)
                    vma = plan['recipe_vma']
                    if vma is None:
                        # MAIN has several file-to-RAM phases: use its registered window.
                        registered = registered_extents.get((family, off, nbytes), {})
                        phase = registered.get('gate_config')
                        if not phase and family in {'main', 'ovmovie'}:
                            phase = 'config/overlays/' + ('main_boot' if family == 'main' else 'ovmovie') + '.overlay.yaml'
                        if doc['vma'] is not None:
                            vma = number(doc['vma']) + off - start
                        elif phase:
                            if phase not in phase_cache:
                                phase_cache[phase] = gate.load_yaml(ROOT/phase)['standalone_build']['window']
                            w = phase_cache[phase]
                            vma = number(w['vram_start']) + off - number(w['file_start'])
                        elif doc['vma'] is not None:
                            vma = number(doc['vma']) + off - start
                        else:
                            raise ValueError('source row has no registered load phase')
                    units.append(dict(plan, off=off, size=nbytes, vma=vma))
                tag = image.replace('/', '_')
                spec = dict(image=image, tag=tag, container='work/disc/containers/' + CONTAINERS[family],
                            start=start, size=size, vma=None if doc['vma'] is None else number(doc['vma']),
                            units=units, output='build/' + tag + '.bin', document=doc)
                images[tag] = spec
            outside = extend_checks(images, recipes, row_plans, registry, modules, module_jobs, docs, gate)
            placement_checks = extend_placement_checks(images, recipes, row_plans, registry, modules, module_jobs, placements, gate)
            return dict(images=list(images.items()), outside=outside, placement_checks=placement_checks)
        layout_key = sha(json.dumps([[list(k),v] for k,v in row_plans.items()] + [module_jobs], sort_keys=True).encode())
        layout = checkpoint('images:'+layout_key, compose_images, lambda value: [], copy_value=False)
        images, outside, placement_checks = dict(layout['images']), layout['outside'], layout['placement_checks']
    put(STATE/'outside_recipes.json', outside)
    put(STATE/'placement_checks.json', placement_checks)
    put(STATE/'row_plans.json', [dict(container=f, off=o, size=n, **v) for (f,o,n),v in row_plans.items()])
    # Keep the full header/pipeline stamps as independently checked witnesses;
    # schedule objects from their actual include closure and compiler tools.
    headers = sorted(rel(p) for p in (ROOT/'include').rglob('*') if p.is_file())
    headers += sorted(rel(p) for directory in (ROOT/'src').iterdir() if directory.is_dir() for p in directory.rglob('*.h') if p.is_file())
    pipeline = sorted(rel(p) for d in ('tools/build', 'tools/gate', 'tools/link')
                      for p in (ROOT/d).rglob('*') if p.is_file() and p.suffix in ('.py', '.sh'))
    pipeline += ['config/names.tsv']
    pipeline += sorted(rel(p) for p in (ROOT/'tools/fidelity').glob('*.py'))
    pipeline += ['tools/overlay_module_evidence.py']
    pipeline += sorted(rel(p) for p in (ROOT/'toolchain/maspsx').rglob('*.py') if p.is_file())
    compile_build = {'mkbuild.py', 'cc.sh', 'ccproc.py', 'as.sh', 'asproc.py', 'slus_rodata_trim.py'}
    compiletools = [n for n in pipeline if not n.startswith(('tools/build/', 'tools/link/'))
                    or n.rsplit('/', 1)[-1] in compile_build]
    linktools = [n for n in pipeline if not n.startswith('tools/build/') or n == 'tools/build/mkbuild.py']
    out = ['# Generated by tools/build/mkbuild.py; private, no authority switch.\n']
    # Link inputs read by image_one (symbol catalogs, rowbase/rodata-owner/link-list/graph tables).
    linkinputs = sorted(rel(p) for d in ('config/overlays', 'config/link', 'config/link_graph')
                        for p in (ROOT/d).rglob('*') if p.is_file())
    linkinputs += sorted(rel(p) for p in (ROOT/'config').glob('*.txt'))
    stamp_inputs = [('headers', headers), ('pipeline', pipeline), ('linkinputs', linkinputs),
                    ('compiletools', compiletools), ('linktools', linktools)]
    for kind, names in stamp_inputs:
        put(STATE/(kind+'.list'), names)
        out.append(rule(['build/.state/'+kind+'.ok'], names + ['build/.state/'+kind+'.list'],
                        'python3 tools/build/mkbuild.py stamp '+kind))
    sr, slus_cc = slus_rules(headers)
    out += sr
    def emit_recipe(key, spec, path):
        # A projected unit is rewritten by every configure; its real inputs are the owner TU and the
        # inline ledger (added below), and compile_one re-derives it, so it is not a make prerequisite.
        unit = [] if spec.get('projection') else [spec['source']]
        unit_exclude = {spec['source']} if spec.get('projection') else set()
        deps = [rel(path), *unit, 'build/.state/compiletools.ok'] + list(spec['env'].values())
        if 'module' in spec:
            deps += [a['source'] for a in spec['module']['members']] + spec['module']['headers'] + spec['module']['review_inputs']
            deps += [a['declaration'] for a in spec['module']['imports'] if 'declaration' in a]
            if spec['assembler'] == 'genuine_aspsx_verified':
                deps += ['toolchain/genuine/bin/wibo', 'toolchain/genuine/psyq/psyq4.4/ASPSX.EXE']
        if spec.get('projection'):
            deps += [spec['projection']['owner'], 'ledger/layout_inline.jsonl']
        starts = [spec['source']] + ([a['source'] for a in spec['module']['members']] if 'module' in spec else [])
        deps += [n for n in include_closure(M, ROOT, starts) if (ROOT/n).is_file() and n not in unit_exclude]
        if spec['args']:
            deps += ['toolchain/compilers/gcc-' + spec['args'][0] + '/' + tool for tool in ('gcc','cc1','cpp')]
        spec['dependencies'] = sorted(set(deps))
        put(path, spec)
        return dict(dependencies=spec['dependencies'], rule=rule([spec['output']], deps, f'python3 tools/build/mkbuild.py compile {rel(path)}'))
    for key, spec in recipes.items():
        path = STATE/'recipes'/(key+'.json')
        emitted = checkpoint('emit-recipe:'+key+':'+spec['declaration_context_sha256'],
                             lambda: emit_recipe(key, spec, path),
                             lambda value: [ROOT/n for n in value['dependencies'] if n != rel(path) and not n.startswith('build/.state/')],
                             copy_value=False)
        spec['dependencies'] = emitted['dependencies']
        GENERATION_WRITES.add(rel(path))
        out.append(emitted['rule'])
    def emit_image(tag, spec, path):
        put(path, spec)
        deps = [rel(path), spec['container'], 'build/.state/linktools.ok', 'build/.state/linkinputs.ok'] + [recipes[u['recipe']]['output'] for u in spec['units']]
        return rule([spec['output']], deps, f'python3 tools/build/mkbuild.py image {rel(path)}')
    for tag, spec in images.items():
        path = STATE/'images'/(tag+'.json')
        fragment = checkpoint('emit-image:'+layout_key+':'+tag, lambda: emit_image(tag, spec, path), lambda value: [], copy_value=False)
        GENERATION_WRITES.add(rel(path))
        out.append(fragment)
    outputs = ['build/slus_slus_bin.bin'] + [s['output'] for s in images.values()]
    out += ['.PHONY: images\nimages: ' + ' '.join(outputs + [r['output'] for r in recipes.values()] +
            ['build/.state/'+kind+'.ok' for kind, _ in stamp_inputs]) + '\n']
    index = dict(schema='azure-clean.make-build.v1', files=graph.files,
                 images=[dict(image='slus/slus_bin', output=outputs[0], file='slus', start=0, size=graph.files['slus']['size'])] +
                        [dict(image=s['image'], output=s['output'], file=s['image'].split('/')[0], start=s['start'], size=s['size']) for s in images.values()],
                 overlay_recipes=len(recipes), slus_c_recipes=slus_cc, ordinary_rows=len(row_plans),
                 native_modules=len(module_jobs), graph_attestation_sha256=sha(json.dumps(attestation, sort_keys=True).encode()), assembler=sdk, check_images=len(outside), placement_check_images=len(placement_checks), physical_overlay_sources=len({r['source'] for r in recipes.values()}))
    index['stamp_kinds'] = [kind for kind, _ in stamp_inputs]
    put(STATE/'index.json', index)
    source_deps = []
    metadata = sorted(rel(p) for d in ('config/link_graph', 'config/link', 'config/overlays')
                      for p in (ROOT/d).rglob('*') if p.is_file() and p.suffix in ('.json', '.jsonl', '.yaml', '.txt'))
    metadata += sorted(rel(p) for p in (ROOT/'config').glob('*.txt'))
    metadata += sorted({p for m in modules.values() for p in m['review_inputs']})
    metadata += ['ledger/modules.jsonl']
    metadata += ['config/frozen_raw.jsonl', 'ledger/rows.jsonl', 'ledger/layout.jsonl', 'ledger/layout_inline.jsonl', 'config/names.tsv']
    metadata += sorted(rel(p) for p in (ROOT/'ledger/splits').glob('*.jsonl'))
    out += ['build/build.mk: ' + ' '.join(sorted(set(source_deps + metadata + pipeline))) + '\n']
    from tools.gate.source_layout import slus_source
    slus_sources = [rel(slus_source(source, ROOT)) for m in read(ROOT/'config/slus_modules.json')['modules']
                    for source in [m['source']]+[a['source'] for a in m['members']]]
    index['inputs'] = sorted(set(slus_sources + metadata + pipeline + headers + ['config/slus_modules.json', 'config/slus_partitions.json', 'ledger/tu_layout.jsonl', 'ledger/layout_inline.jsonl', 'ledger/splits/slus.build.ninja'] + [r['source'] for r in recipes.values()] + [d for r in recipes.values() for d in r['dependencies'] if d.startswith('src/')] + [t['source'] for t in attestation['tus'].values()] + [a['source'] for m in modules.values() for a in M.all_members(m)]))
    index['inputs'] = sorted(set(index['inputs']) | set(graph.manifest.get('inputs', {})) |
                             {d for r in recipes.values() for d in r['dependencies'] if d.startswith('toolchain/')})
    put(STATE/'index.json', index)
    # Always refresh the makefile timestamp after regeneration, even if its text is stable.
    write(ROOT/'build/build.mk', ''.join(out))
    (ROOT/'build/build.mk').touch()
    print(f'Generated {len(outputs)} images, {len(recipes)} overlay recipes, {slus_cc} SLUS C recipes', flush=True)


def compile_one(path):
    spec = read(path)
    target = ROOT/spec['output']
    target.parent.mkdir(parents=True, exist_ok=True)
    env = dict(os.environ, TMPDIR=str(STATE/'tmp'))
    (STATE/'tmp').mkdir(exist_ok=True)
    for key in ('AZURE_MASPSX', 'AZURE_MASPSX_COMPANION', 'MASPSX_NORETURN_FILE', 'MASPSX_SIBCALL_FILE'):
        env.pop(key, None)
    env.update({k: str(ROOT/v) for k, v in spec['env'].items()})
    temporary = target.with_suffix('.tmp.o')
    if spec.get('projection'):
        # Re-derive the projected unit from the current owner TU (fails closed on a stale inline ledger).
        sys.path.insert(0, str(ROOT/'tools'))
        from gate.source_layout import member_projection
        unit = member_projection(spec['projection']['home'], ROOT)
        if unit is None:
            raise ValueError('member projection vanished; run make configure: ' + spec['projection']['home'])
        write(ROOT/spec['source'], unit)
    if spec.get('live') is not None:
        text = (ROOT/spec['source']).read_text()
        if 'module' in spec:
            text += '\n' + '\n'.join((ROOT/a['source']).read_text() for a in spec['module']['members'])
        if sha(text.encode()) != spec.get('declaration_context_sha256'):
            load_gate(ROOT)
            import overlay_evidence as E
            names = set(spec['live']['base_names'])
            include_own = spec['live'].get('include_own', not bool(spec.get('module', {}).get('allocation_model')))
            if include_own:
                names |= E.candidate_noreturn_syms(text)
            live_path = target.with_suffix('.noreturn.txt')
            write(live_path, '\n'.join(sorted(names)) + '\n')
            env['MASPSX_NORETURN_FILE'] = str(live_path)
    if spec.get('assembler') == 'genuine_aspsx_verified':
        build_native(spec, temporary)
    else:
        run([ROOT/spec['wrapper'], ROOT/spec['source'], temporary, *spec['args']], env=env)
    if 'module' in spec and spec.get('assembler') != 'genuine_aspsx_verified':
        gate = load_gate(ROOT)
        import overlay_module_gate as M
        m = spec['module']
        if M.Z.enabled(m):
            cooked, _ = M.Z.prepare(m, temporary.read_bytes(), ROOT)
        else:
            cooked, _ = M.N.prepare_object(m, temporary.read_bytes(), ROOT/'tools/build/slus_rodata_trim.py')
        temporary.write_bytes(cooked)
        expected = M.Z.expected_payload(m) if M.Z.enabled(m) else M.payload_spec(m)
        actual = [(s['name'], s['size']) for s in M.sections(temporary) if s['flags'] & 2 and s['size'] and s['name'] not in M.META]
        if actual != expected:
            raise ValueError('native payload differs: ' + m['key'])
    temporary.replace(target)
    deps = [p for p in spec.get('dependencies', []) if p != rel(path)]
    put(target.with_suffix('.proof.json'), dict(object_sha256=sha(target.read_bytes()),
        recipe_sha256=sha(Path(path).read_bytes()), inputs=hash_inputs(deps),
        assembler=spec.get('assembler', 'maspsx' if spec['wrapper'].endswith('cc.sh') else 'gnu_as')))
    print('CC' if spec['wrapper'].endswith('cc.sh') else 'AS', spec['output'], spec['source'], flush=True)


def cover_image(start, size, compiled):
    """Partition an image into source allocations and explicit retail gaps."""
    cursor, chunks = start, []
    for allocation in sorted(compiled, key=lambda a: a['foff']):
        a = dict(allocation)
        if a['size'] <= 0 or a['foff'] < cursor or a['foff']+a['size'] > start+size:
            raise ValueError('overlapping/out-of-image source allocation')
        if cursor < a['foff']:
            chunks.append(dict(foff=cursor, size=a['foff']-cursor, origin='retail_import'))
        chunks.append(a)
        cursor = a['foff'] + a['size']
    if cursor < start+size:
        chunks.append(dict(foff=cursor, size=start+size-cursor, origin='retail_import'))
    return chunks


@contextmanager
def frozen_lists(gate):
    import linklist
    original = linklist.load
    tables = original(gate.ROOT)
    linklist.load = lambda root: tables if Path(root).absolute() == gate.ROOT else original(root)
    try:
        yield
    finally:
        linklist.load = original


def image_one(path):
    spec = read(path)
    gate = load_gate(ROOT)
    import linklist
    import match
    import linklist_data
    from tools.link.placement import prove_invariant_placement
    directory = STATE/'link'/spec['tag']
    directory.mkdir(parents=True, exist_ok=True)
    # Fault only the exact relocation/table slices; do not reread a whole
    # multi-megabyte container for each diagnostic layout.
    with (ROOT/spec['container']).open('rb') as disc_file:
        raw = mmap.mmap(disc_file.fileno(), 0, access=mmap.ACCESS_READ)
    compiled, symbols, noloads, objects = [], ['_gp = 0x80080994;'], [], []
    tables_checked = 0
    catalogs = [gate.cfg_path('config/slus_006.14.symbols.txt'), gate.cfg_path('config/overlays/abs_syms.txt')]
    if spec['image'].startswith('dungeon/'):
        catalogs.append(gate.cfg_path('config/overlays/dungeon_engine.symbols.txt'))
    with frozen_lists(gate):
        for i, unit in enumerate(spec['units']):
            recipe = read(STATE/'recipes'/(unit['recipe']+'.json'))
            original = directory/(str(i)+'.original.o')
            shutil.copyfile(ROOT/recipe['output'], original)
            if unit.get('rebind'):
                entry = dict(unit['rebind'], bindings={number(k): number(v) for k,v in unit['rebind']['bindings'].items()})
                linklist.rebind_object(gate.ROOT, entry, original)
            metadata = object_metadata(original)
            if metadata is None:
                raise ValueError('unsupported object metadata')
            prefix = f'u{i}_'
            placed = directory/(str(i)+'.o')
            if unit.get('module'):
                defs = unit['imports']
                allocations = unit['allocations']
            else:
                off, size, vma = unit['off'], unit['size'], unit['vma']
                match_entry = gate.MatchEntry(off, size, unit['func'], '2.7.2', ROOT/recipe['source'], spec['image'], link_vram=unit.get('recipe_vma'), source_kind=unit['kind'])
                segment = gate.Segment(0, unit['kind'], off, off+size, vma, '.text.*', name=unit['func'], match=match_entry)
                place_func = unit['func']
                if place_func not in {s[0] for s in metadata['symbols']}:
                    place_func = unit['source_stem']
                owner = gate.rodata_owner(spec['image'].split('/')[0], off)
                mini = directory/(str(i)+'.ld')
                if owner:
                    gate.rodata_first_link(original, segment, owner, 0x80080994, catalogs, mini.with_suffix(''))
                    rules = mini.read_text()
                    ro = re.search(r'^\s*(\.(?:rodata|rdata)) 0x([0-9a-fA-F]+) :', rules, re.M)
                    tx = re.search(r'^\s*\.out_\w+ 0x([0-9a-fA-F]+)', rules, re.M)
                    rbase, tbase = int(ro[2],16), int(tx[1],16)
                    allocations = [dict(section=ro[1], foff=off, vma=rbase, size=tbase-rbase, link_alignment=1),
                                   dict(section='.text.*', foff=off+tbase-rbase, vma=tbase, size=size-(tbase-rbase), link_alignment=4)]
                else:
                    has_local_data = any(name in {'.rodata','.rdata','.sdata','.data'} and nbytes for name,nbytes in metadata['sections'])
                    placements = match._local_section_placements(str(original), place_func, vma, raw[off:off+size]) if unit['kind'] == 'c' and has_local_data else {}
                    gate.write_linker_script([segment], [original], 0x80080994, catalogs, mini,
                                              placements=placements, obj_paths={0: original})
                    rules = mini.read_text()
                    if placements:
                        # NOLOAD resolves addresses only; the image keeps retail bytes there.
                        # Compare the placed table CONTENTS with retail (gate local_table_mismatches).
                        errors = gate.local_table_mismatches(original, placements, segment, vma, ROOT/spec['container'],
                                                             0x80080994, catalogs, directory/('tbl_'+str(i)), unit['func'])
                        if errors:
                            raise ValueError('compiler-local table differs from retail in ' + spec['image'] + ': ' + errors[0])
                        tables_checked += len(placements)
                    for section, address in placements.items():
                        noloads.append(f'.table_{i}_{len(noloads)} 0x{address:X} (NOLOAD) : SUBALIGN(4) {{ KEEP("{rel(placed)}"({section}*)) }}')
                    section = '.text.*' if unit['kind'] == 'c' else '.text'
                    allocations = [dict(section=section, foff=off, vma=vma, size=size, link_alignment=1)]
                defs = {name: int(value,16) for name,value in re.findall(r'^\s*(\w+)\s*=\s*0x([0-9a-fA-F]+)\s*;', rules, re.M)}
                if spec['vma'] is not None and vma != spec['vma'] + off - spec['start']:
                    target_vma = spec['vma'] + off - spec['start']
                    proof = prove_invariant_placement(ROOT, spec['document'], original, rules, vma, target_vma,
                                                      raw[off:off+size], directory/('bridge_'+str(i)))
                    if proof is None:
                        raise ValueError('no invariant placement bridge: ' + spec['image'] + ':' + hex(off))
                    for a in allocations:
                        a['vma'] += target_vma-vma
            for name, kind, value in metadata['values']:
                if kind == 'U':
                    if name == '_gp':
                        address = 0x80080994
                    elif name in defs:
                        address = defs[name]
                    else:
                        raise ValueError('unwitnessed import: ' + name)
                    symbols.append(f'{prefix}{name} = 0x{address:X};')
            run(['mipsel-linux-gnu-objcopy', '--prefix-symbols='+prefix, original, placed])
            objects.append(placed)
            for allocation in allocations:
                if not allocation['size']:
                    continue
                compiled.append(dict(allocation, object=rel(placed), origin='original_object'))
    chunks = cover_image(spec['start'], spec['size'], compiled)
    imports = []
    import_object = directory/'imports.o'
    for i, chunk in enumerate(chunks):
        if chunk['origin'] == 'retail_import':
            imports += [f'.section .import_{i},"a",@progbits',
                        f'.incbin "{spec["container"]}", {chunk["foff"]}, {chunk["size"]}']
            chunk.update(object=rel(import_object), section=f'.import_{i}', link_alignment=1)
    write(directory/'imports.s', '\n'.join(imports)+'\n')
    run(['mipsel-linux-gnu-as', '-EL', '-march=r3000', '-o', import_object, directory/'imports.s'])
    objects.append(import_object)
    script = ['OUTPUT_FORMAT("elf32-tradlittlemips")', 'OUTPUT_ARCH(mips)', *symbols, 'SECTIONS {']
    for i, chunk in enumerate(chunks):
        offset = chunk['foff']-spec['start']
        vma = chunk.get('vma', (spec['vma'] + offset) if spec['vma'] is not None else 0x10000000+offset)
        script += [f'.piece_{i} 0x{vma:X} : AT(0x{offset:X}) SUBALIGN({chunk["link_alignment"]}) {{ KEEP("{chunk["object"]}"({chunk["section"]})) }}',
                   f'ASSERT(SIZEOF(.piece_{i}) == 0x{chunk["size"]:X}, "source/import extent {i}")']
    script += noloads + ['/DISCARD/ : { *(*) }', '}']
    write(directory/'image.ld', '\n'.join(script)+'\n')
    write(directory/'objects.rsp', '\n'.join(rel(o) for o in objects)+'\n')
    run(['mipsel-linux-gnu-ld', '-EL', '--no-check-sections', '-T', directory/'image.ld',
         '-Map', directory/'image.map', '-o', directory/'image.elf', '@'+rel(directory/'objects.rsp')])
    target = ROOT/spec['output']
    temporary = target.with_suffix('.tmp.bin')
    run(['mipsel-linux-gnu-objcopy', '-O', 'binary', directory/'image.elf', temporary])
    if temporary.stat().st_size != spec['size']:
        raise ValueError('linked image length differs')
    temporary.replace(target)
    put(STATE/'origins'/(spec['tag']+'.json'), dict(image=spec['image'],
        original_object_bytes=sum(c['size'] for c in chunks if c['origin']=='original_object'),
        retail_import_bytes=sum(c['size'] for c in chunks if c['origin']=='retail_import'),
        objects=len(spec['units']), tables_checked=tables_checked,
        link_inputs_sha256=sha((STATE/'linkinputs.ok').read_bytes()), assembly_bytes=sum(u.get('size',0) for u in spec['units'] if u.get('kind') in {'platform_asm','game_asm'}), noload_tables=len(noloads),
        linker_script_sha256=sha((directory/'image.ld').read_bytes()),
        recipes={u['recipe']: sha((ROOT/read(STATE/'recipes'/(u['recipe']+'.json'))['output']).read_bytes()) for u in spec['units']},
        rows=sorted({row for u in spec['units'] for row in u.get('rows', [])})))
    print('LINK', spec['image'], flush=True)


def slus_copy():
    source = ROOT/'build_slus/build/slus_006.14'
    target = ROOT/'build/slus_slus_bin.bin'
    shutil.copyfile(source, target)
    graph = Graph(ROOT/'config/link_graph')
    map_blob = (ROOT/'build_slus/build/slus_006.14.map').read_bytes()
    counts = slus_origins(map_blob.decode(), graph.manifest['build']['slus']['sections'], graph.files['slus']['size'])
    put(STATE/'origins/slus_slus_bin.json', dict(image='slus/slus_bin',
        original_object_bytes=sum(counts.get(k,0) for k in ('C','SDK_assembly','game_assembly')),
        retail_import_bytes=counts.get('imported_objects',0),
        assembly_bytes=counts.get('SDK_assembly',0)+counts.get('game_assembly',0),
        linker_fill_bytes=counts.get('linker_fill',0), slus_origins=counts,
        map_sha256=sha(map_blob)))


def first_difference(actual, expected):
    return next((i for i,(a,b) in enumerate(zip(actual,expected)) if a != b),
                None if len(actual) == len(expected) else min(len(actual),len(expected)))


def checked_symbol(spec, offset):
    path = STATE/'images'/(spec['image'].replace('/', '_')+'.json')
    if not path.exists():
        elf = ROOT/'build_slus/build/slus_006.14.elf'
        if not elf.exists():
            return '<SLUS EXE header or unavailable ELF symbol map>'
        address = None
        for line in run(['mipsel-linux-gnu-objdump', '-h', elf]).splitlines():
            fields = line.split()
            if len(fields) >= 7 and fields[0].isdigit():
                size, vma, lma = (int(fields[i],16) for i in (2,3,4))
                if lma <= offset < lma+size:
                    address = vma+offset-lma
                    break
        if address is None:
            return '<SLUS file padding>'
        candidates = []
        for line in run(['mipsel-linux-gnu-nm', '-n', '-S', elf]).splitlines():
            fields = line.split()
            if len(fields) == 4 and fields[2] in 'TtDdRrWw':
                begin, size = int(fields[0],16), int(fields[1],16)
                if begin <= address < begin+size:
                    candidates.append((size, fields[3]))
        return min(candidates)[1] if candidates else '<SLUS section label at 0x%X>' % address
    off = spec['start']+offset
    for unit in read(path)['units']:
        if unit.get('module'):
            m = read(STATE/'recipes'/(unit['recipe']+'.json'))['module']
            for row in m.get('data_members', [])+m['members']:
                # At copied placements use the allocation's file displacement.
                delta = unit['allocations'][0]['foff']-module_allocations_for_check(m)[0]['foff']
                if row['foff']+delta <= off < row['foff']+delta+row['size']:
                    return row.get('function', row['id'])
        elif unit['off'] <= off < unit['off']+unit['size']:
            return unit['func']
    return '<explicit retail import>'


def module_allocations_for_check(m):
    return m.get('allocations') or [dict(foff=min(a['foff'] for a in m.get('data_members', [])+m['members']))]


def check():
    index = read(STATE/'index.json')
    graph = Graph(ROOT/'config/link_graph')
    if 'graph_attestation_sha256' in index:
        registry = {r['id']:r for r in map(json.loads, (ROOT/'ledger/rows.jsonl').read_text().splitlines())}
        current = attest_graph(graph, registry)
        configured = read(STATE/'graph_attestation.json')
        def structure(value):
            value = copy.deepcopy(value)
            for tu in value['tus'].values():
                tu.pop('source_sha256', None)
            return value
        if structure(current) != structure(configured):
            raise ValueError('live graph attestation changed; run make configure and rebuild')
        put(STATE/'checked_graph_attestation.json', current)
        if genuine_status() != index['assembler']:
            raise ValueError('genuine ASPSX availability/identity changed; run make configure')
    for kind in index.get('stamp_kinds', ('headers', 'pipeline', 'linkinputs')) if 'graph_attestation_sha256' in index else ():
        if (STATE/(kind+'.ok')).read_text() != stamp(kind):
            raise ValueError('stale ' + kind + ' stamp: inputs changed since the build; run make')
    inputs_before = hash_inputs(index.get('inputs', []))
    blobs = {}
    for family, spec in graph.files.items():
        blob = (ROOT/'work/disc/extract'/spec['disc_path']).read_bytes()
        if len(blob) != spec['size'] or hashlib.sha1(blob).hexdigest() != spec['sha1']:
            raise ValueError('disc input identity differs: ' + family)
        blobs[family] = blob
    documents = graph.documents()
    extras_path = STATE/'outside_recipes.json'
    extras = read(extras_path) if extras_path.exists() else []
    placements_path = STATE/'placement_checks.json'
    placement_checks = read(placements_path) if placements_path.exists() else []
    expected_images = set(selected_images(documents)) | {'main/main_bin', 'ovmovie/ovmovie_bin', 'slus/slus_bin'} | {r['image'] for r in extras+placement_checks}
    if len(index['images']) != len(expected_images) or {s['image'] for s in index['images']} != expected_images:
        raise ValueError('build index does not cover the complete image graph')
    extra_by_image = {r['image']:r for r in extras+placement_checks}
    for spec in index['images']:
        family = spec['image'].split('/')[0]
        doc = documents.get(spec['image'], extra_by_image.get(spec['image'], dict(foff=0, size=graph.files[family]['size'])))
        start = doc.get('foff', doc.get('start'))
        if spec['output'] != 'build/' + spec['image'].replace('/', '_') + '.bin':
            raise ValueError('build index output path differs from graph identity')
        if (spec['file'], spec['start'], spec['size']) != (family, number(start), number(doc['size'])):
            raise ValueError('build index image extent differs from graph')
    results, consumed, checked_rows = [], set(), {}
    proof_cache = {}
    for spec in index['images']:
        actual_path = ROOT/spec['output']
        actual = actual_path.read_bytes() if actual_path.exists() else b''
        expected = blobs[spec['file']][spec['start']:spec['start']+spec['size']]
        got, want = hashlib.sha1(actual).hexdigest(), hashlib.sha1(expected).hexdigest()
        result = dict(image=spec['image'], output=spec['output'], bytes=len(actual), sha1=got,
                      retail_sha1=want, result='MATCH' if got == want else 'DIFF')
        modes, rows = Counter(), set()
        image_path = STATE/'images'/(spec['image'].replace('/', '_')+'.json')
        if image_path.exists():
            for unit in read(image_path)['units']:
                key = unit['recipe']; consumed.add(key); rows.update(unit.get('rows', []))
                if key not in proof_cache:
                    recipe_path = STATE/'recipes'/(key+'.json')
                    recipe = read(recipe_path)
                    obj = ROOT/recipe['output']
                    proof = read(obj.with_suffix('.proof.json'))
                    if proof['object_sha256'] != sha(obj.read_bytes()) or proof['recipe_sha256'] != sha(recipe_path.read_bytes()) or proof['inputs'] != hash_inputs(proof['inputs']):
                        raise ValueError('stale compile proof: '+key)
                    proof_cache[key] = proof
                modes[proof_cache[key]['assembler']] += 1
            origin = read(STATE/'origins'/(spec['image'].replace('/', '_')+'.json'))
            if (origin['recipes'] != {u['recipe']: proof_cache[u['recipe']]['object_sha256'] for u in read(image_path)['units']}
                    or origin['link_inputs_sha256'] != sha((STATE/'linkinputs.ok').read_bytes())):
                raise ValueError('stale image: ' + spec['image'] + ' was not linked from the current objects/link inputs; run make')
        else:
            modes['maspsx'] = index.get('slus_c_recipes', 0)
            rows.update(r['id'] for r in map(json.loads, (ROOT/'ledger/rows.jsonl').read_text().splitlines()) if r['container']=='slus')
        result['assemblers'] = dict(modes)
        result['rows'] = sorted(rows)
        if got != want:
            offset = first_difference(actual, expected)
            result.update(first_difference=offset, disc_offset=spec['start']+offset,
                          symbol=checked_symbol(spec, offset))
            print(f"DIFF {spec['image']} offset=0x{offset:X} disc=0x{spec['start']+offset:X} symbol={result['symbol']}", flush=True)
        else:
            print('MATCH', spec['image'], 'assemblers='+','.join(f'{k}:{v}' for k,v in sorted(modes.items())), flush=True)
            for row in rows:
                checked_rows.setdefault(row, []).append(spec['image'])
        results.append(result)
    if 'overlay_recipes' in index and len(consumed) != index['overlay_recipes']:
        raise ValueError('compiled recipes outside checked image scope')
    if 'graph_attestation_sha256' in index:
        expected_rows = {r['id'] for r in registry.values() if r['kind']=='overlay'}
        represented = {rid for r in results for rid in r['rows']}
        if expected_rows - represented:
            raise ValueError('registered row placements outside checked scope: '+', '.join(sorted(expected_rows-represented)[:10]))
    if inputs_before != hash_inputs(inputs_before):
        raise ValueError('inputs changed during make check')
    matched = sum(r['result']=='MATCH' for r in results)
    put(ROOT/'build/check.json', dict(schema='azure-clean.make-check.v2', images=len(results), matched=matched,
        results=results, rows=checked_rows, overlay_recipes_checked=len(consumed),
        graph_attestation_sha256=index.get('graph_attestation_sha256'), assembler=index.get('assembler'),
        inputs=inputs_before, outputs={r['output']:sha((ROOT/r['output']).read_bytes()) for r in results if (ROOT/r['output']).exists()}))
    failures = [r['image'] for r in results if r['result'] != 'MATCH']
    if failures:
        raise ValueError('retail mismatch: ' + ', '.join(failures))
    print(f'CHECK {matched}/{len(results)} images SHA-1 MATCH (including SLUS EXE); {len(consumed)} overlay recipes checked')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('action', choices=['bootstrap', 'generate', 'compile', 'image', 'check', 'slus', 'slus_script', 'stamp'])
    parser.add_argument('spec', nargs='?')
    args = parser.parse_args()
    if os.environ.get('MKBUILD_TRACE'):
        import faulthandler
        faulthandler.dump_traceback_later(45, repeat=True)
    os.chdir(ROOT)
    import tempfile
    temporary_directory = STATE/'tmp'
    temporary_directory.mkdir(parents=True, exist_ok=True)
    os.environ['TMPDIR'] = str(temporary_directory)
    tempfile.tempdir = str(temporary_directory)
    if args.action in ('compile', 'image', 'stamp'):
        {'compile': compile_one, 'image': image_one, 'stamp': write_stamp}[args.action](args.spec)
    else:
        if args.action == 'generate':
            if args.spec not in (None, 'full'):
                parser.error('generate accepts only the optional full selector')
            generate(full=args.spec == 'full')
        else:
            {'bootstrap': bootstrap, 'check': check, 'slus': slus_copy, 'slus_script': slus_script}[args.action]()


if __name__ == '__main__':
    main()
