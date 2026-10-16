"""Conservative dependencies of sources present before a package transaction.

No fingerprint implementation is imported. C dependencies come from the actual
compiler's preprocessor at the production recipe; uncertainty forces a full gate.
"""
import ast
from concurrent.futures import ThreadPoolExecutor
import json
import os
from pathlib import Path
import re
import runpy
import shlex
import struct
import subprocess
import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

import yaml


def local(root, name):
    p = Path(name)
    if p.is_absolute() or '..' in p.parts:
        raise ValueError('dependency path escapes root: ' + str(name))
    return root / p


def rows(root, name):
    parts = Path(name).parts
    if len(parts) == 3 and parts[0] == 'overlays' and parts[2] == 'overlay_first_pass_results.json':
        name = 'ledger/splits/' + parts[1] + '.jsonl'
    return [json.loads(s) for s in local(root, name).read_text().splitlines()
            if s.strip() and not s.lstrip().startswith('#')]


def window_recipes(root):
    """Capture recipes before mutation, without needing exported source facades."""
    parser_path = root / 'tools/gate/match.py'
    tree = ast.parse(parser_path.read_text())
    node = next(n for n in tree.body if isinstance(n, ast.FunctionDef)
                and n.name == 'parse_config_label')
    namespace = {}
    exec(compile(ast.Module(body=[node], type_ignores=[]), str(parser_path), 'exec'), namespace)
    parse = namespace['parse_config_label']
    recipes = set()
    manifest = root / 'config/overlays/modules.json'
    modules = json.loads(manifest.read_text())['modules'] if manifest.exists() else []
    native_members = {m['source'] for module in modules
                      for m in [*module['members'], *module.get('data_members', [])]}
    tables = {}
    windows = 0
    unhashed_inputs = set()
    for path in sorted((root / 'config/overlays').glob('*.overlay.yaml')):
        cfg = yaml.safe_load(path.read_text())
        sb = cfg.get('standalone_build', {})
        w = sb.get('window', {})
        if not w:
            continue
        fs, fe = w['file_start'], w['file_end']
        if not isinstance(fs, int) or not isinstance(fe, int) or fs >= fe:
            raise ValueError('invalid production window: ' + path.name)
        windows += 1
        symbols = cfg.get('options', {}).get('symbol_addrs_path')
        if symbols:
            local(root, symbols)
            unhashed_inputs.add(symbols)
        for group in sb.get('matched_sources', []):
            name = group['results']
            if name not in tables:
                tables[name] = rows(root, name)
            for row in tables[name]:
                if (row.get('result') != 'MATCH' or
                        (group.get('skip_rerun', True) and row.get('rerun')) or
                        not (fs <= row['foff'] and row['foff'] + row['size'] <= fe)):
                    continue
                kind = row.get('source_kind', 'c')
                if kind == 'c':
                    folder = Path(group['source_dir'])
                    if len(folder.parts) == 3 and folder.parts[0] == 'overlays' and folder.parts[2] == 'first_pass_matched':
                        unit = {'dungeon_engine': 'dungeon', 'dungeon_engine_pilot_only': 'dungeon_engine'}.get(folder.parts[1], folder.parts[1])
                        from source_layout import row_relative
                        source = row_relative({'container': unit, 'c_path': row['func_vram'] + '.c'}, root)
                    else:
                        source = str(folder / (row['func_vram'] + '.c'))
                    if source in native_members:
                        continue  # The native TU replaces this per-row compile.
                    version, flags = parse(row.get('config') or '2.7.2')
                elif kind in ('platform_asm', 'game_asm'):
                    source, version, flags = row['asm_path'], '', ''
                else:
                    raise ValueError('unknown production source kind: ' + kind)
                recipes.add((source, version, flags, kind))
    # Native modules replace per-row compiles in their existing bank windows.
    for module in modules:
        if module['recipe']['cfg'] != '2.7.2-cdk-G0':
            raise ValueError('unknown native module recipe')
        recipes.add((module['source'], '2.7.2-cdk', '-G0', 'c'))
    return {'windows': windows, 'recipes': sorted(recipes), 'unhashed_inputs': sorted(unhashed_inputs)}


def generated_sdk_sources(root):
    """Known split outputs, with their include-bearing generated preamble.

    These are generated inputs, not missing maintained assembly sources. Splat
    disassembly of the declared SDK asm segments includes macro.inc; MAIN's
    extra twin gets its text from the real generator without writing outputs.
    Existing outputs are still scanned in full, including any extra includes.
    """
    generated = {}
    config = root / 'config/slus_006.14.yaml'
    if config.is_file():
        cfg = yaml.safe_load(config.read_text())
        preamble = cfg.get('options', {}).get('asm_inc_header', '.include "macro.inc"')
        if preamble != '.include "macro.inc"':
            raise ValueError('unmodelled generated SDK assembly preamble')
        def segments(entries):
            for entry in entries:
                if isinstance(entry, dict):
                    yield from segments(entry.get('subsegments', []))
                elif (isinstance(entry, list) and len(entry) >= 3 and
                      entry[1] == 'asm' and isinstance(entry[2], str) and
                      entry[2].startswith('psyq/')):
                    name = 'asm/' + entry[2] + '.s'
                    local(root, name)  # Never classify paths which escape root.
                    yield name
        generated.update((name, preamble + '\n') for name in segments(cfg.get('segments', [])))
    generator = root / 'tools/build/main_sdk_asm.py'
    if generator.is_file():
        module = runpy.run_path(str(generator))
        output = module['OUTPUT']
        if output != 'build_slus/asm/psyq/libcard/main_patch_delay.s':
            raise ValueError('unmodelled MAIN SDK assembly output')
        generated[output.removeprefix('build_slus/')] = module['assembly'](
            struct.pack('<6I', *module['WORDS']))
    return generated


def dependency_closure(root, baseline):
    if 'error' in baseline:
        raise ValueError('baseline window recipes unavailable: ' + baseline['error'])
    recipes = {tuple(r) for r in baseline['recipes']}
    current = {tuple(r) for r in window_recipes(root)['recipes']}
    current_sources = {r[0] for r in current}
    # Rows folded into a newly added native TU are no longer standalone
    # compiles. Its whole-TU/window inputs are covered by incremental hashes.
    recipes = {r for r in recipes if r[0] in current_sources}
    generated = None
    virtual = {}
    def source_path(name, kind):
        nonlocal generated
        p = local(root, name)
        # Production asm is regenerated by the SLUS split and linked into
        # the gate view; a canonical checkout has no top-level asm facade.
        if kind != 'c' and not p.is_file() and name.startswith('asm/'):
            p = local(root, 'build_slus/' + name)
        if not p.is_file() and kind == 'platform_asm':
            if generated is None:
                generated = generated_sdk_sources(root)
            if name in generated:
                virtual[str(p.relative_to(root))] = generated[name]
                return p
        if not p.is_file():
            raise ValueError('existing window source missing: ' + name)
        if not p.resolve().is_relative_to(root):
            raise ValueError('existing window source escapes root: ' + name)
        return p
    for name, _, _, kind in recipes:
        source_path(name, kind)
    sources = {r[0] for r in recipes}
    # Observe new recipes/conditional flags for existing sources too, while
    # excluding sources and TUs introduced by this transaction.
    recipes.update(r for r in current if r[0] in sources)

    def scan(recipe):
        name, version, flags, kind = recipe
        source = source_path(name, kind)
        if kind != 'c':
            found, pending = set(), [str(source.relative_to(root))]
            while pending:
                item = pending.pop()
                if item in found:
                    continue
                p = local(root, item)
                found.add(item)
                text = virtual[item] if item in virtual else p.read_text()
                for line in text.splitlines():
                    if not re.match(r'\s*(?:\.(?:include|incbin)|#\s*include)\b', line):
                        continue
                    hit = re.fullmatch(r'\s*(?:\.(?:include|incbin)|#\s*include)\s+"([^"]+)"\s*(?:,.*)?', line)
                    if not hit:
                        raise ValueError('unmodelled assembly include: ' + line)
                    # GNU as searches its cwd and -I include directory. Also
                    # overbind source-relative candidates; never choose one
                    # shadow and silently miss another possible dependency.
                    targets = {candidate.resolve() for candidate in
                               (p.parent / hit[1], root / 'include' / hit[1], root / hit[1], root / 'build_ovl_gate' / hit[1])
                               if candidate.is_file()}
                    if not targets:
                        raise ValueError('missing assembly include: ' + line)
                    pending.extend(str(target.relative_to(root)) for target in targets)
            return found
        argv_flags = shlex.split(flags)
        if not re.fullmatch(r'[A-Za-z0-9_.-]+', version) or any(
                f.startswith(('-B', '-specs', '--specs', '--sysroot', '-wrapper')) for f in argv_flags):
            raise ValueError('unmodelled compiler recipe')
        gcc = root / 'toolchain/compilers' / ('gcc-' + version)
        result = subprocess.run([str(gcc / 'gcc'), '-B' + str(gcc) + '/', '-M', '-x', 'c', '-O2',
                                 *argv_flags, '-I' + str(root / 'include'), '-w', str(source)],
                                cwd=root, capture_output=True, text=True, check=True, timeout=300)
        output = result.stdout.replace('\\\n', ' ').split(':', 1)
        if len(output) != 2:
            raise ValueError('malformed preprocessor dependency output')
        found = set()
        for dep in shlex.split(output[1]):
            path = Path(os.path.abspath(root / dep))
            name = str(path.relative_to(root))
            if not path.is_file():
                raise ValueError('preprocessor dependency missing: ' + name)
            found.add(name)
        if str(source.relative_to(root)) not in found:
            raise ValueError('preprocessor omitted source dependency')
        return found

    workers = min(16, len(os.sched_getaffinity(0)) if hasattr(os, 'sched_getaffinity') else (os.cpu_count() or 1))
    with ThreadPoolExecutor(max_workers=max(1, workers)) as pool:
        return set().union(*pool.map(scan, sorted(recipes)))
