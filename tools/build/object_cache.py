#!/usr/bin/env python3
"""Shared content-addressed make objects; proofs are refreshed in the consuming root."""
import argparse
import ast
from contextlib import contextmanager
import fcntl
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import shlex
import subprocess
import sys
import tempfile
import time

sys.path.insert(0, str(Path(__file__).resolve().parents[2]))
from tools.build import content_cache, compile_slots

SCHEMA = 1
# Audited stock macros only form symbol visibility directives and symbol names.
LABEL_MACROS_SHA256 = '9011fb521abe02bf51d16d3ae8ec1667ccd899a26affb6a5fe00b842ab421dc5'


def digest(blob):
    return hashlib.sha256(blob).hexdigest()


def encode(value):
    return json.dumps(value, sort_keys=True, separators=(',', ':')).encode()


def cache_directory(root):
    # External roots are <parent>/<lane>/root. All such lanes and the lander
    # can share this directory by exporting AZURE_OBJECT_CACHE_DIR explicitly.
    root = Path(root)
    parent = root.parent.parent if (root/'SCRATCH_HEAD').exists() else root.parent/'azure-lanes'
    default = parent / '.azure-object-cache'
    return Path(os.environ.get('AZURE_OBJECT_CACHE_DIR', str(default)))


def safe_path(root, name):
    if not name or Path(name).is_absolute() or '..' in Path(name).parts:
        raise ValueError('unsafe object cache path: ' + name)
    path = root/name
    # Managed input symlinks are allowed. Restored artifacts must be real files.
    return path


def key_for(inputs):
    return digest(encode(inputs))


def assembly_inputs(root, text, view, cwd=None):
    """Bind files read by emitted assembler directives, including C string joins."""
    strings, spans = [], []
    for group in re.finditer(r'(?:"(?:\\.|[^"\\])*"\s*)+', text):
        spans.append((group.start(), group.end()))
        try:
            strings.append(''.join(ast.literal_eval(literal) for literal in
                re.findall(r'"(?:\\.|[^"\\])*"', group[0])))
        except (ValueError, SyntaxError):
            return None
    pending = [(text, spans), *((value, []) for value in strings)]
    found = set()
    while pending:
        current, opaque = pending.pop()
        if re.search(r'\.altmacro\b', current):
            return None
        if re.search(r'\.\\[A-Za-z_]|\\\(\)', current) and digest(current.encode()) != LABEL_MACROS_SHA256:
            return None
        # Stock label macros accept a visibility argument. An include directive
        # cannot be smuggled through that argument, including keyword syntax.
        for call in re.finditer(r'\b(?:glabel|alabel|ehlabel|jlabel|dlabel)\s+([^\n;]+)', current):
            try:
                lexer = shlex.shlex(call[1], posix=True, punctuation_chars=',')
                lexer.whitespace_split = True
                arguments = [v for v in lexer if v != ',']
            except ValueError:
                return None
            for value in arguments:
                if value.startswith('visibility=') and value.split('=', 1)[1] not in {'global', 'local'}:
                    return None
            positional = [v for v in arguments if '=' not in v]
            if len(positional) > 1 and positional[1] not in {'global', 'local'}:
                return None
        for directive in re.finditer(r'(?m)\.(include|incbin)\b([^\n;]*)', current):
            if any(start <= directive.start() < end for start, end in opaque):
                continue
            match = re.match(r'\s*"([^"\n]+)"', directive[2])
            if match is None:
                return None
            name = match[1]
            candidates = [Path(os.path.abspath(base/name)) for base in (cwd or root, view, view/'include')]
            target = next((path for path in candidates if path.is_file()), None)
            if target is None or not target.is_relative_to(root):
                return None
            relative = target.relative_to(root).as_posix()
            if relative in found:
                continue
            found.add(relative)
            if directive[1] == 'include':
                pending.append((target.read_text(errors='replace'), []))
    return found


def dependency_inputs(root, spec):
    """Ask the selected compiler about macro/flag-dependent C includes as well."""
    sources = []
    if 'command' in spec:
        argv = shlex.split(spec['command'])
        if len(argv) < 6 or not argv[0].endswith('/cc.sh'):
            return dict(files=[], preprocessed={})
        source, version, flags = 'build_slus/'+argv[1], argv[3], shlex.split(argv[4])
        include_root = root/'build_slus/include'
        sources = [source]
    elif spec.get('args') and spec.get('source', '').endswith('.c'):
        source, version, flags = spec['source'], spec['args'][0], shlex.split(spec['args'][1])
        include_root = root/'include'
        sources = [source]
        if 'module' in spec:
            sources += [a['source'] for a in spec['module']['members']]
            flags += ['-I'+str((root/n).parent) for n in sources]
    else:
        return dict(files=[], preprocessed={})
    if any(f.startswith(('-B', '-specs', '--specs', '--sysroot', '-wrapper', '-fplugin',
                         '-fprofile', '-fbranch-probabilities', '-save-temps', '-MD', '-MMD',
                         '-MF', '-d')) for f in flags):
        return None
    compiler = root/'toolchain/compilers'/('gcc-'+version)
    found = {p.relative_to(root).as_posix() for p in compiler.iterdir()
             if p.is_file() and p.name in {'gcc', 'cc1', 'cpp', 'specs'}}
    preprocessed = {}
    for source in sorted(set(sources)):
        result = subprocess.run([str(compiler/'gcc'), '-B'+str(compiler)+'/', '-M', '-O2',
                                 *flags, '-I'+str(include_root), '-w', str(root/source)],
                                cwd=root, capture_output=True, text=True, check=True)
        expanded = subprocess.run([str(compiler/'gcc'), '-B'+str(compiler)+'/', '-E', '-P', '-O2',
                                   *flags, '-I'+str(include_root), '-w', str(root/source)],
                                  cwd=root, capture_output=True, check=True).stdout
        preprocessed[source] = digest(expanded)
        assembly = assembly_inputs(root, expanded.decode(errors='replace'),
            root/'build_slus' if 'command' in spec else root/'build_ovl',
            root/'build_slus' if 'command' in spec else root)
        if assembly is None:
            return None
        found.update(assembly)
        for name in shlex.split(result.stdout.replace('\\\n', ' ').split(':', 1)[1]):
            path = Path(os.path.abspath(root/name))
            if not path.is_relative_to(root):
                return None
            found.add(path.relative_to(root).as_posix())
    return dict(files=sorted(found), preprocessed=preprocessed)


def key_inputs(root, recipe_path, spec):
    """Bind live includes, compiler bytes, recipe flags, and fastland3 tool closure.

    A fresh include walk catches newly introduced and shadowing headers even if
    configure's previous dependency list is stale. Unsupported volatile inputs
    bypass the cache; compilation and the ordinary image proof still run.
    """
    from tools.link.prepare import load_gate
    load_gate(root)
    import overlay_module_gate as modules
    names = set(spec['dependencies']) - {str(recipe_path.relative_to(root)), spec.get('name_input')}
    optional = {'config/names.tsv'}
    names.add('config/names.tsv')  # cold name vocabularies have not been discovered yet
    names.update(spec.get('config_tables', {}).values())
    if spec.get('assembler') == 'genuine_aspsx_verified':
        family = spec['module']['container']
        optional.update('config/'+kind+'_syms'+suffix+'.txt'
                        for kind in ('noreturn', 'sibcall') for suffix in ('', '.'+family))
        names.update(optional)
    starts = [n for n in names if n.endswith(('.c', '.s', '.h'))]
    names.update(modules.closure(root, starts))
    discovered = dependency_inputs(root, spec)
    if discovered is None:
        return None
    names.update(discovered['files'])
    closure_file = root/'build/.state/compiletools.list'
    tools = json.loads(closure_file.read_text())
    names.update(tools)
    flags = ' '.join(spec.get('args', [])) + ' ' + spec.get('command', '')
    # Root-sensitive debug strings and volatile macros cannot use portable keys.
    if re.search(r'(?<!\S)-g|\b__(?:FILE|BASE_FILE|DATE|TIME|TIMESTAMP)__\b', flags):
        return None
    for name in names:
        if name.endswith(('.c', '.h', '.s')):
            text = safe_path(root, name).read_text(errors='replace')
            if re.search(r'\b__(?:FILE|BASE_FILE|DATE|TIME|TIMESTAMP)__\b', text):
                return None
            if name.endswith('.s'):
                view = root/'build_slus' if 'command' in spec else root/'build_ovl'
                assembly = assembly_inputs(root, text, view, view if 'command' in spec else root)
                if assembly is None:
                    return None
                discovered['files'] = sorted(set(discovered['files']) | assembly)
    names.update(discovered['files'])
    inputs = content_cache.hashes(root, names)
    if any(value is None and name not in optional for name, value in inputs.items()):
        raise ValueError('missing object cache input')
    # The executable, rather than its pathname/version label, is its identity.
    executables = {}
    for tool in ('mipsel-linux-gnu-as', 'python3'):
        executable = shutil.which(tool)
        if not executable:
            raise ValueError('missing compile executable: ' + tool)
        executables[tool] = digest(Path(executable).read_bytes())
    python = root/'.venv/bin/python'
    if python.exists():
        executables['venv-python'] = digest(python.read_bytes())
    env = {name: os.environ.get(name) for name in
           ('LANG', 'LC_ALL', 'LC_CTYPE', 'SOURCE_DATE_EPOCH', 'TZ', 'PYTHONHASHSEED',
            'MASPSX_GP_LIMIT_FROM_CC1', 'MASPSX_NO_CDK_LO_FOLD', 'MASPSX_NO_SELFINC_LA_FOLD')}
    canonical = {'MASPSX_NORETURN_FILE', 'MASPSX_SIBCALL_FILE'}
    if any(k.startswith('MASPSX_') and k not in canonical and k not in env for k in os.environ):
        return None
    # These can introduce untracked headers, executables or compiler plugins.
    if any(os.environ.get(name) for name in ('CPATH', 'C_INCLUDE_PATH', 'CPLUS_INCLUDE_PATH',
                                           'GCC_EXEC_PREFIX', 'COMPILER_PATH', 'LIBRARY_PATH',
                                           'DEPENDENCIES_OUTPUT', 'SUNPRO_DEPENDENCIES')):
        return None
    return dict(schema=SCHEMA, recipe=spec, inputs=inputs, preprocessed=discovered['preprocessed'], executables=executables,
                environment=env, python=sys.version)


@contextmanager
def locked(directory):
    directory.mkdir(parents=True, exist_ok=True)
    with (directory/'cache.lock').open('a+b') as stream:
        fcntl.flock(stream, fcntl.LOCK_EX)
        yield


def artifacts(spec):
    target = Path(spec['output'])
    result = [spec['output'], str(target.with_suffix('.proof.json'))]
    if spec.get('name_input'):
        result.append(spec['name_input'])
    if 'slus_data_pieces.py' in spec.get('command', ''):
        result += [str(target.with_suffix('.unsplit.o')), str(target.with_suffix('.data-pieces.json'))]
    return result


def atomic_copy(source, target):
    target.parent.mkdir(parents=True, exist_ok=True)
    if target.is_symlink():
        raise ValueError('refusing symlink cache output: ' + target.name)
    fd, temporary = tempfile.mkstemp(prefix='.object-', dir=target.parent)
    try:
        with os.fdopen(fd, 'wb') as stream, source.open('rb') as original:
            shutil.copyfileobj(original, stream)
        os.replace(temporary, target)
    finally:
        Path(temporary).unlink(missing_ok=True)


def restore(directory, key, inputs, root, outputs):
    with locked(directory):
        entry = directory/key
        if not entry.exists():
            return False
        manifest = json.loads((entry/'manifest.json').read_text())
        if manifest['key_inputs'] != inputs or set(manifest['outputs']) != set(outputs):
            raise ValueError('object cache manifest does not match key: ' + key)
        for index, name in enumerate(outputs):
            blob = entry/str(index)
            if digest(blob.read_bytes()) != manifest['outputs'][name]:
                raise ValueError('corrupt object cache artifact: ' + key)
        for index, name in enumerate(outputs):
            atomic_copy(entry/str(index), safe_path(root, name))
        (entry/'manifest.json').touch()  # LRU access, never inputs' mtimes
        return True


def entry_sizes(directory):
    result = []
    for entry in directory.iterdir():
        if not re.fullmatch('[0-9a-f]{64}', entry.name) or not entry.is_dir() or entry.is_symlink():
            continue
        try:  # unlocked callers race with prune and restore
            mtime = (entry/'manifest.json').stat().st_mtime_ns
            size = sum(p.stat().st_size for p in entry.iterdir() if p.is_file())
        except FileNotFoundError:
            continue
        result.append((mtime, entry, size))
    return result


def publish(directory, key, inputs, root, outputs):
    directory.mkdir(parents=True, exist_ok=True)
    temporary = Path(tempfile.mkdtemp(prefix='.publish-', dir=directory))
    try:
        values = {}
        for index, name in enumerate(outputs):
            source = safe_path(root, name)
            if source.is_symlink():
                raise ValueError('refusing symlink cache input: ' + name)
            shutil.copyfile(source, temporary/str(index))
            values[name] = digest((temporary/str(index)).read_bytes())
        (temporary/'manifest.json').write_bytes(encode(dict(key_inputs=inputs, outputs=values)))
        with locked(directory):
            target = directory/key
            if not target.exists():
                counter = directory/'bytes'
                added = sum(p.stat().st_size for p in temporary.iterdir())
                temporary.rename(target)
                # Never walk the cache under the lock: a missing counter stays
                # missing and the background prune rebuilds it.
                if counter.exists():
                    content_cache.save(counter, int(counter.read_text())+added)
            else:
                current = json.loads((target/'manifest.json').read_text())
                if any(current['outputs'].get(n) != d for n, d in values.items() if not n.endswith('.proof.json')):
                    raise ValueError('different artifacts published for the same cache key: ' + key)
    finally:
        if temporary.exists():
            shutil.rmtree(temporary)


def prune(directory, max_bytes):
    if max_bytes < 0:
        raise ValueError('cache size cap must be nonnegative')
    directory.mkdir(parents=True, exist_ok=True)
    # One prune at a time: a second walk would only repeat the first one's work.
    with (directory/'prune.lock').open('a+b') as stream:
        try:
            fcntl.flock(stream, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except BlockingIOError:
            return dict(skipped='busy', max_bytes=max_bytes)
        return prune_locked(directory, max_bytes)


def prune_locked(directory, max_bytes):
    counter = directory/'bytes'
    # The inventory of a full cache takes minutes, so it runs without the lock.
    # Entries are only deleted under the lock, one at a time, and only if still
    # unused since the inventory: restore touches manifest.json under that lock.
    before = int(counter.read_text()) if counter.exists() else None
    entries = entry_sizes(directory)
    total = sum(size for _, _, size in entries)
    removed = 0
    for mtime, entry, size in sorted(entries):
        if total <= max_bytes:
            break
        with locked(directory):
            try:
                if (entry/'manifest.json').stat().st_mtime_ns != mtime:
                    continue  # restored meanwhile
            except FileNotFoundError:
                total -= size  # already removed by someone else
                continue
            shutil.rmtree(entry)
        total -= size
        removed += 1
    with locked(directory):
        # Entries published during the inventory are not in it; keep their bytes.
        grown = max(0, int(counter.read_text()) - before) if before is not None and counter.exists() else 0
        content_cache.save(counter, total + grown)
    return dict(bytes=total + grown, removed=removed, max_bytes=max_bytes)


def enforce_cap(directory, cap):
    # Publication accounts bytes under the same lock. Only an over-cap cache
    # needs an LRU inventory, which takes minutes to hours on a full lane
    # cache, so it never runs inside a compile: a detached prune does it
    # (one at a time, see prune) down to a low watermark so later misses do
    # not start it again at once. A missing counter counts as over the cap.
    with locked(directory):
        counter = directory/'bytes'
        total = int(counter.read_text()) if counter.exists() else cap+1
    if total > cap:
        subprocess.Popen([sys.executable, str(Path(__file__).resolve()), 'prune',
                          '--directory', str(directory), '--max-bytes', str(cap*3//4)],
                         stdin=subprocess.DEVNULL, stdout=subprocess.DEVNULL,
                         stderr=subprocess.DEVNULL, start_new_session=True)


def refresh_proof(root, recipe_path, spec):
    target = safe_path(root, spec['output'])
    proof_path = target.with_suffix('.proof.json')
    proof = json.loads(proof_path.read_text())
    deps = [n for n in spec['dependencies'] if n != str(recipe_path.relative_to(root))]
    proof.update(object_sha256=digest(target.read_bytes()), recipe_sha256=digest(recipe_path.read_bytes()),
                 inputs=content_cache.hashes(root, deps))
    content_cache.save(proof_path, proof)
    target.touch()  # name witness may just have been restored


def log_event(root, status, spec, key=None, seconds=0):
    log = Path(os.environ.get('AZURE_OBJECT_CACHE_LOG', str(root/'build/.state/object-cache.jsonl')))
    log.parent.mkdir(parents=True, exist_ok=True)
    fd = os.open(log, os.O_CREAT | os.O_APPEND | os.O_WRONLY, 0o600)
    try:
        os.write(fd, encode(dict(status=status, output=spec['output'], key=key, seconds=seconds)) + b'\n')
    finally:
        os.close(fd)


def compile_recipe(root, recipe_path, build):
    root, recipe_path = Path(root), Path(recipe_path)
    if not recipe_path.is_absolute():
        recipe_path = root/recipe_path
    spec = json.loads(recipe_path.read_text())
    enabled = os.environ.get('AZURE_OBJECT_CACHE', '0') != '0'
    # Library tests/legacy hand-written recipes do not have fastland3 witnesses.
    enabled = enabled and (root/'build/.state/compiletools.list').is_file()
    with compile_slots.acquire():
        inputs = key_inputs(root, recipe_path, spec) if enabled else None
    key = key_for(inputs) if inputs else None
    directory, outputs = cache_directory(root), artifacts(spec)
    started = time.monotonic()
    hit = bool(key and restore(directory, key, inputs, root, outputs))
    sample = int(os.environ.get('AZURE_OBJECT_VERIFY', '0'))
    if not 0 <= sample <= 100:
        raise ValueError('AZURE_OBJECT_VERIFY must be a percentage (0..100)')
    verify = hit and int(key[:8], 16) % 100 < sample
    expected = {name: digest((root/name).read_bytes()) for name in outputs
                if not name.endswith('.proof.json')} if verify else {}
    if not hit or verify:
        # A make recipe owns exactly one job already; never read or return
        # jobserver pipe tokens, and never run recursive make while holding a slot.
        with compile_slots.acquire():
            build()
            if inputs is not None and key_inputs(root, recipe_path, spec) != inputs:
                raise ValueError('object cache inputs changed during compile')
        if verify and any(digest((root/name).read_bytes()) != value for name, value in expected.items()):
            with locked(directory):
                shutil.rmtree(directory/key)
            raise ValueError('object cache verification differs: ' + key)
        if key and not hit:
            publish(directory, key, inputs, root, outputs)
            enforce_cap(directory, int(os.environ.get('AZURE_OBJECT_CACHE_BYTES', str(48 * 1024**3))))
    if hit:
        refresh_proof(root, recipe_path, spec)
        print('CACHE_VERIFY' if verify else 'CACHE_HIT', spec['output'], flush=True)
    log_event(root, 'verify' if verify else 'hit' if hit else 'miss' if key else 'bypass',
              spec, key, time.monotonic()-started)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=['prune'])
    parser.add_argument('--directory', type=Path, required=True)
    parser.add_argument('--max-bytes', type=int, default=48 * 1024**3)
    args = parser.parse_args()
    print(json.dumps(prune(args.directory, args.max_bytes), sort_keys=True))


if __name__ == '__main__':
    main()
