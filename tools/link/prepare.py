"""Prepare original ET_REL inputs with the existing overlay home recipes.

This is object preparation, not a window gate. No prelinked row bytes enter
combined.py. The final global link proves every selected image against retail;
a separate, bounded production gate witnesses representative windows.
"""
from contextlib import contextmanager
import dataclasses
import hashlib
import importlib
import json
from pathlib import Path
import shutil
import sys


def load_gate(root):
    view = root / 'build_ovl'
    sys.path.insert(0, str(view / 'tools'))
    gate = importlib.import_module('overlay_local_gate')
    if gate.ROOT != view:
        raise ValueError('overlay gate must be loaded from the private build view')
    return gate



@contextmanager
def linklist_snapshot(gate):
    """Freeze the already validated lists during one input-bound preparation.

    The production loader stats every list on every symbol binding. Preserve
    its tables exactly and validate the complete list stamp at both ends.
    """
    import linklist
    original = linklist.load
    before = linklist._stamp(linklist.files(gate.ROOT))
    tables = original(gate.ROOT)
    def frozen(root):
        return tables if Path(root).absolute() == gate.ROOT else original(root)
    linklist.load = frozen
    import overlay_module_gate as modules
    import overlay_module_placements as placements
    module_load, placement_load, row_load = modules.load_modules, placements.load, modules.rows
    try:
        # These are immutable recipe inputs for this invocation. The ordinary
        # validators run once, before any object preparation; complete input
        # hashes are checked again after it. No gate implementation is edited.
        module_values = module_load(gate.ROOT)
        placement_values = placement_load(gate.ROOT, module_values)
        row_values = row_load(gate.ROOT)
        modules.load_modules = lambda root=modules.ROOT: module_values if Path(root).absolute() == gate.ROOT else module_load(root)
        placements.load = lambda root, modules=None: placement_values if Path(root).absolute() == gate.ROOT else placement_load(root, modules)
        modules.rows = lambda root: row_values if Path(root).absolute() == gate.ROOT else row_load(root)
        yield
    finally:
        modules.load_modules, placements.load, modules.rows = module_load, placement_load, row_load
        linklist.load = original
        if before != linklist._stamp(linklist.files(gate.ROOT)):
            raise ValueError('link lists changed during object preparation')


def compile_cache(gate, directory):
    """Invocation-local reuse before placement rebinding, keyed by recipe/evidence.

    Never reuse a previous invocation's objects. Include search paths and source
    dependencies are invariant during this preparation; graph/source checks run
    before and after it. Placement-specific flags and frozen evidence are keys.
    """
    original = gate.run
    cache = {}
    stats = dict(compiles=0, reused=0)
    directory.mkdir(parents=True, exist_ok=True)

    def cached_run(argv, **kwargs):
        if Path(argv[0]).name != 'cc.sh':
            return original(argv, **kwargs)
        source, output = Path(argv[1]), Path(argv[2])
        env = dict(kwargs.get('env') or {})
        for name in ('MASPSX_NORETURN_FILE', 'MASPSX_SIBCALL_FILE'):
            if name in env:
                env[name] = hashlib.sha256(Path(env[name]).read_bytes()).hexdigest()
        key = hashlib.sha256(json.dumps([str(source.resolve()), str(source.parent.resolve()),
            hashlib.sha256(source.read_bytes()).hexdigest(), list(map(str, argv[3:])),
            sorted(env.items())], sort_keys=True).encode()).hexdigest()
        if key in cache:
            shutil.copyfile(cache[key], output)
            stats['reused'] += 1
            return None
        result = original(argv, **kwargs)
        target = directory / (key + '.o')
        shutil.copyfile(output, target)
        cache[key] = target
        stats['compiles'] += 1
        return result

    gate.run = cached_run
    return original, stats


def prepare_image(gate, graph, image, directory):
    """Reuse production match selection, compilation, rebinding and symbol rules."""
    from overlay_module_gate import project_segments
    from overlay_evidence import evidence_env, _gen_noreturn
    import linklist_data
    import match

    doc = graph.documents_cache[image]
    family = image.split('/')[0]
    start, size, base = (int(str(doc[k]), 0) if isinstance(doc[k], str) else doc[k]
                         for k in ('foff', 'size', 'vma'))
    end = start + size
    name = image.replace('/', '_')
    work = directory / name
    build = work / 'build'
    obj_dir = build / 'obj'
    obj_dir.mkdir(parents=True, exist_ok=True)
    sb = dict(split_results=f'overlays/{family}/overlay_first_pass_results.json',
              matched_sources=[dict(name=f'overlays/{family}',
                  results=f'overlays/{family}/overlay_first_pass_results.json',
                  source_dir=f'overlays/{family}/first_pass_matched', skip_rerun=True)])
    rows = gate.load_split_rows(sb, start, end)
    matches, counts = gate.load_matches(sb, start, end, family=family)
    segments = gate.build_segments(rows, matches, start, end, base - start)
    container_name = {'town': 'TOWN_TOWN.BIN', 'dungeon': 'DUNGEON_DUNGEON.BIN'}[family]
    container = gate.ROOT / 'work/s3_splat/extract' / container_name
    data = linklist_data.project_segments(segments, container, build, gate.ROOT, family, start, end)
    project_segments(segments, build, name, gate.ROOT)
    with _gen_noreturn().scoped_census_snapshot():
        c_objects = gate.compile_c_segments(segments, obj_dir, env=evidence_env(name), overlay=name)
    gate.check_bare_text_empty(c_objects)
    gate.compile_asm_segments(segments, obj_dir)
    symbols = build / 'link_data.symbols.txt'
    linklist_data.write_symbols(data, symbols)
    symbol_files = [gate.cfg_path('config/slus_006.14.symbols.txt'), symbols,
                   gate.cfg_path('config/overlays/abs_syms.txt')]
    if family == 'dungeon':
        symbol_files.append(gate.cfg_path('config/overlays/dungeon_engine.symbols.txt'))
    duplicates = gate.duplicate_match_funcs(segments)
    for seg in segments:
        if seg.kind not in ('c', 'platform_asm', 'game_asm') or seg.match is None:
            continue
        obj = obj_dir / (gate.segment_obj_key(seg, duplicates) + '.o')
        vma = seg.match.link_vram if seg.match.link_vram is not None else seg.vram
        mini = dataclasses.replace(seg, index=0, vram=vma)
        stem = build / ('rowbase_' + obj.stem)
        owner = gate.rodata_owner(family, seg.start)
        if owner:
            # The production validator checks section truncation and rodata/text
            # extents. The final linker consumes the original object, not this bin.
            gate.rodata_first_link(obj, seg, owner, 0x80080994, symbol_files, stem)
            continue
        place_func = seg.match.func
        if seg.match.link_vram is not None and match.symbol_info(str(obj), place_func) is None:
            place_func = seg.match.source.stem
        with container.open('rb') as stream:
            stream.seek(seg.start)
            payload = stream.read(seg.size)
        placements = match._local_section_placements(str(obj), place_func, vma, payload)
        gate.write_linker_script([mini], [obj], 0x80080994, symbol_files,
                                stem.with_suffix('.ld'), placements=placements, obj_paths={0: obj})
    gate.write_manifest(work / (name + '_manifest.json'), name, container, segments, counts)
    (build / (name + '.ld')).write_text('_gp = 0x80080994;\n')
    return work


def prepare_images(root, graph, images, directory):
    try:
        from .combined import preparation_digest
    except ImportError:
        from combined import preparation_digest
    before = preparation_digest(root, graph)
    gate = load_gate(root)
    import overlay_scoped_fingerprint as scoped
    if scoped.enabled(gate.ROOT):
        scoped.reject_environment()
    graph.documents_cache = graph.documents(validate=True)
    original, stats = compile_cache(gate, directory / 'compile_cache')
    prepared, holds = {}, []
    try:
        with linklist_snapshot(gate):
            for n, image in enumerate(images, 1):
                try:
                    prepared[image] = prepare_image(gate, graph, image, directory)
                except (Exception, SystemExit) as exc:
                    reason = str(exc).replace(str(root), '<root>')
                    holds.append([image, reason[-2000:]])
                    print('PREPARE HOLD', image, reason[-300:], flush=True)
                if n % 10 == 0 or n == len(images):
                    print(f'Prepared {n}/{len(images)} images; {len(holds)} holds; {stats}', flush=True)
    finally:
        gate.run = original
        del graph.documents_cache
    graph.verify_inputs(root)
    graph.verify_sources(root)
    if before != preparation_digest(root, graph):
        raise ValueError('preparation inputs changed during object builds')
    return prepared, holds, stats
