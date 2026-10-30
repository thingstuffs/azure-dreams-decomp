#!/usr/bin/env python3
"""Proof universe = build graph: which production recipes and images an edit reaches, and their proof.

    affected.py set   [--root R] FILE...                  affected recipes and images (JSON, no compile)
    affected.py prove [--root R] [--base B] [--edited-from-git REV | FILE...]
                      [--workers 8] [--no-relink] [--json OUT] [--keep]

The universe is the generated build graph itself, not an include-closure list of standalone captures:

  * every `build/.state/recipes/*.json` and `build/.state/slus-recipes/*.json` whose `dependencies`
    (the production cpp closure written by `make configure`) or own `source` contains an edited file,
    compared after resolving symlinks on both sides (build_slus/src and build_slus/include are views);
    placement copies (`build/.state/enumerate/*.member/*.c`) are reached through their projection
    owner, which every projection recipe lists as a dependency;
  * every edited file's own recipe(s) (source or projection owner) are always in the set;
  * images = registered `build/.state/images/*.json` whose units link an affected recipe, plus
    `slus/slus_bin` when a SLUS recipe is affected.

`prove` compiles each affected recipe in the candidate root at its production args, environment,
evidence files and name input (the root's own `tools/build/mkbuild.py` compile functions; outputs and
name witnesses are redirected to `build/.affected/<run>/`, so `build/obj` and `build/.state` are never
written), compares raw object bytes against the baseline object (`--base` root's `build/obj`, default
the root's own pre-edit `build/obj`) and, on a difference, reports the first differing section,
symbol and relocation.  Only images with a changed object are relinked (the production `_image_one`
link with the changed objects substituted) and compared with the baseline image; the report names the
first differing image symbol.  An image whose objects are all identical is PASS without a relink
(an image is a function of its objects).  The SLUS image is not relinked here: a changed SLUS object
marks `slus/slus_bin` CHANGED (object level) and the full `make` remains its proof.

No `make configure` runs: the recipe set is the root's current generated graph.  An edit that adds a
new `#include` is still caught (the edited file's own recipes are always compiled), but a header newly
reached only through that include is not in the closure until the next configure; edits outside
src/ and include/ (tools, config, ledgers) change the graph itself and are reported as `authority`
(prove refuses them unless --allow-authority).

Baseline freshness: before an object is trusted as the baseline its `.proof.json` must name the same
object sha, and every src/include input it records must equal the base text (`--base` root files, or
`git show <rev>:path` for files edited in the candidate root itself).  A baseline that fails is
STALE_BASE, never PASS.
"""
from __future__ import annotations

import argparse
from concurrent.futures import ThreadPoolExecutor
import hashlib
import json
import os
from pathlib import Path
import queue
import shlex
import shutil
import struct
import subprocess
import sys
import threading
import time

HERE = Path(__file__).resolve()
DEFAULT_ROOT = HERE.parents[2]
SOURCE_PREFIXES = ('src/', 'include/')


# ---------------------------------------------------------------------------------------------- graph

def sha256(blob):
    return hashlib.sha256(blob).hexdigest()


def _read_json(path):
    with open(path, 'rb') as fh:
        return json.loads(fh.read())


class Graph:
    """The generated build graph of one root (recipes, SLUS recipes, registered images)."""

    def __init__(self, root):
        self.root = Path(root).resolve()
        state = self.root / 'build/.state'
        if not (state / 'index.json').is_file():
            raise FileNotFoundError('no generated build graph (run make configure once): ' + str(state))
        self.index = _read_json(state / 'index.json')
        self.registered = {s['image']: s for s in self.index['images']}
        self.generated, targets = self._scan_makefile()
        current_slus = {Path(p).stem for p in self.index.get('slus_recipes', ())}
        self.recipes = {}          # id -> spec (family 'overlay' | 'slus') of the CURRENT graph
        self.stale = {}            # recipe files left by older configures (no make rule / not indexed)
        for family, folder in (('overlay', 'recipes'), ('slus', 'slus-recipes')):
            for path in sorted((state / folder).glob('*.json')):
                spec = _read_json(path)
                spec['_family'] = family
                spec['_id'] = path.stem
                live = (spec.get('output') in targets) if family == 'overlay' and targets is not None else \
                    (path.stem in current_slus) if family == 'slus' and current_slus else True
                (self.recipes if live else self.stale)[path.stem] = spec
        self.images = {}           # image name -> {tag, output, recipes, path}
        self.recipe_rows = {}      # recipe id -> registry rows its linked units place (image unit `rows`)
        for path in sorted((state / 'images').glob('*.json')):
            spec = _read_json(path)
            if spec['image'] not in self.registered:
                continue           # stale check files from older builds
            self.images[spec['image']] = dict(tag=spec['tag'], output=spec['output'], path=str(path),
                                              recipes=[u['recipe'] for u in spec['units']])
            for unit in spec['units']:
                self.recipe_rows.setdefault(unit['recipe'], set()).update(unit.get('rows') or ())
        self.slus_image = 'slus/slus_bin' if 'slus/slus_bin' in self.registered else None
        self._real = {}
        self._by_dep = None
        self._own = None
        self._by_recipe_image = None

    def _scan_makefile(self):
        """(generated groups, overlay object targets) from build/build.mk.

        Groups are grouped rules (`a b &: inputs`) that render generated SLUS sources (partition bodies):
        a SLUS partition recipe compiles build_slus/build/partition_sources/<x>.c, whose real inputs
        (src/slus/code.c, ...) appear only on the render rule, not in the recipe's dependencies.
        Targets are the `build/obj/<id>.o` rules: build/.state/recipes also keeps files from older
        configures (deleted or merged sources) that the current graph no longer builds."""
        groups, targets = {}, set()
        mk = self.root / 'build/build.mk'
        if not mk.is_file():
            return groups, None
        with open(mk, encoding='utf-8', errors='replace') as fh:
            lines = iter(fh)
            for line in lines:
                if line.startswith('build/obj/'):
                    head = line.split(':', 1)[0]
                    if head.endswith('.o') and ' ' not in head:
                        targets.add(head)
                    continue
                if '&:' not in line:
                    continue
                outs, inputs = line.split('&:', 1)
                command = next(lines, '').strip().lstrip('@')
                group = dict(targets=outs.split(), inputs=inputs.split(), command=command)
                for target in group['targets']:
                    groups[target] = group
        return groups, targets

    # Paths are compared physically: build_slus/{src,include} are symlink views of src/ and include/.
    def real(self, name):
        hit = self._real.get(name)
        if hit is None and name.startswith(SOURCE_PREFIXES) and '..' not in name and '//' not in name:
            # src/ and include/ hold no symlinks (checked by the tests); skip the stat walk.
            self._real[name] = hit = name
        if hit is None:
            path = Path(name)
            path = path if path.is_absolute() else self.root / path
            resolved = Path(os.path.realpath(path))
            hit = resolved.relative_to(self.root).as_posix() if resolved.is_relative_to(self.root) \
                else resolved.as_posix()
            self._real[name] = hit
        return hit

    def logical(self, name):
        path = Path(name)
        path = path if path.is_absolute() else self.root / path
        path = Path(os.path.abspath(path))
        if not path.is_relative_to(self.root):
            raise ValueError('path outside root: ' + str(name))
        return path.relative_to(self.root).as_posix()

    def by_dep(self):
        """{physical path: {recipe ids}} over dependencies, sources and projection owners."""
        if self._by_dep is None:
            index = {}
            for rid, spec in self.recipes.items():
                names = set(spec.get('dependencies', ()))
                if spec.get('source'):
                    names.add(spec['source'])
                if spec.get('projection'):
                    names.add(spec['projection']['owner'])
                for name in list(names):
                    if name in self.generated:
                        names.update(self.generated[name]['inputs'])
                for name in names:
                    if name.startswith('build/.state/') or name.startswith('toolchain/'):
                        continue   # generated witnesses / compilers: graph authority, not source edits
                    index.setdefault(self.real(name), set()).add(rid)
            self._by_dep = index
        return self._by_dep

    def own_source(self, spec):
        """Physical path of the file a recipe compiles (placement copies: their owner TU)."""
        if spec.get('projection'):
            return self.real(spec['projection']['owner'])
        if spec.get('source'):
            return self.real(spec['source'])
        if spec['_family'] == 'slus':
            argv = shlex.split(spec.get('command', ''))
            if len(argv) > 1:
                return self.real('build_slus/' + argv[1])
        return None

    def own_recipes(self, path):
        """Recipes whose own source (or placement-copy owner) is this file."""
        if self._own is None:
            own = {}
            for rid, spec in self.recipes.items():
                own.setdefault(self.own_source(spec), set()).add(rid)
            self._own = own
        return set(self._own.get(self.real(path), ()))

    def images_of(self, recipes):
        if self._by_recipe_image is None:
            index = {}
            for image, spec in self.images.items():
                for rid in spec['recipes']:
                    index.setdefault(rid, set()).add(image)
            self._by_recipe_image = index
        out = set()
        for rid in recipes:
            out |= self._by_recipe_image.get(rid, set())
        if self.slus_image and any(self.recipes[r]['_family'] == 'slus' for r in recipes):
            out.add(self.slus_image)
        return out


def affected_set(root, edited, graph=None):
    """Every recipe whose production closure or own source contains an edited file, and its images.

    Returns {files, recipes, slus_recipes, images, own, unconsumed, authority, kinds}."""
    graph = graph or Graph(root)
    files = sorted({graph.logical(p) for p in edited})
    authority = [f for f in files if not f.startswith(SOURCE_PREFIXES)]
    by_dep = graph.by_dep()
    selected, own, unconsumed = set(), {}, []
    for name in files:
        if name in authority:
            continue
        hits = set(by_dep.get(graph.real(name), ()))
        mine = graph.own_recipes(name) if name.endswith('.c') else set()
        hits |= mine
        own[name] = sorted(mine)
        if not hits:
            unconsumed.append(name)
        selected |= hits
    kinds = {}
    for rid in selected:
        spec = graph.recipes[rid]
        kind = 'slus' if spec['_family'] == 'slus' else 'placement_copy' if spec.get('projection') else \
            'module' if 'module' in spec else 'asm' if not spec.get('wrapper', '').endswith('cc.sh') else 'row'
        kinds[kind] = kinds.get(kind, 0) + 1
    return dict(files=files,
                recipes=sorted(r for r in selected if graph.recipes[r]['_family'] == 'overlay'),
                slus_recipes=sorted(r for r in selected if graph.recipes[r]['_family'] == 'slus'),
                images=sorted(graph.images_of(selected)), own=own, unconsumed=unconsumed,
                authority=authority, kinds=kinds)


# ------------------------------------------------------------------------------------- object compare

def _elf_sections(data):
    if len(data) < 52 or data[:6] != b'\x7fELF\x01\x01':
        raise ValueError('not an ELF32 little-endian object')
    shoff = struct.unpack_from('<I', data, 32)[0]
    count, shstrndx = struct.unpack_from('<HH', data, 48)
    raw = [struct.unpack_from('<10I', data, shoff + 40 * n) for n in range(count)]
    strtab = data[raw[shstrndx][4]:raw[shstrndx][4] + raw[shstrndx][5]]

    def cstr(table, off):
        end = table.find(b'\0', off)
        return table[off:end if end >= 0 else len(table)].decode('latin-1')
    out = []
    for n, s in enumerate(raw):
        name, typ, flags, addr, off, size, link, info, align, entsize = s
        body = b'' if typ == 8 else data[off:off + size]   # SHT_NOBITS
        out.append(dict(index=n, name=cstr(strtab, name), type=typ, flags=flags, size=size, link=link,
                        info=info, data=body))
    return out, cstr


def elf_facts(data):
    """Sections (name -> bytes), symbols, relocations (section -> [(offset, type, symbol)])."""
    sections, cstr = _elf_sections(data)
    symbols = []
    for s in sections:
        if s['type'] != 2:      # SHT_SYMTAB
            continue
        names = sections[s['link']]['data']
        for off in range(0, len(s['data']), 16):
            name, value, size, info, other, shndx = struct.unpack_from('<IIIBBH', s['data'], off)
            symbols.append(dict(name=cstr(names, name), value=value, size=size, type=info & 15,
                                bind=info >> 4, shndx=shndx))
        break
    for sym in symbols:
        if not sym['name'] and sym['type'] == 3 and sym['shndx'] < len(sections):
            sym['name'] = sections[sym['shndx']]['name']
    relocs = {}
    for s in sections:
        if s['type'] not in (9, 4):   # SHT_REL / SHT_RELA
            continue
        target = sections[s['info']]['name'] if s['info'] < len(sections) else '?'
        step = 8 if s['type'] == 9 else 12
        rows = []
        for off in range(0, len(s['data']) - step + 1, step):
            r_off, r_info = struct.unpack_from('<II', s['data'], off)
            sym = symbols[r_info >> 8]['name'] if (r_info >> 8) < len(symbols) else '?'
            rows.append((r_off, r_info & 0xff, sym))
        relocs[target] = rows
    return dict(sections={s['name']: s for s in sections if s['name']}, symbols=symbols, relocs=relocs)


def symbol_at(facts, section, offset):
    """Name of the symbol covering `offset` in `section` (else the nearest preceding one)."""
    index = facts['sections'][section]['index'] if section in facts['sections'] else -1
    best = None
    for sym in facts['symbols']:
        if sym['shndx'] != index or sym['type'] in (3, 4) or not sym['name']:
            continue
        if sym['value'] <= offset < sym['value'] + max(sym['size'], 1):
            return '%s+0x%X' % (sym['name'], offset - sym['value'])
        if sym['value'] <= offset and (best is None or sym['value'] > best['value']):
            best = sym
    if best is not None:
        return '%s+0x%X' % (best['name'], offset - best['value'])
    return '%s+0x%X' % (section, offset)


ALLOC = 0x2


def object_difference(before, after):
    """None when the objects are byte-identical, else the first differing loadable section/symbol."""
    if before == after:
        return None
    try:
        a, b = elf_facts(before), elf_facts(after)
    except (ValueError, struct.error, IndexError) as exc:
        return dict(kind='unparsed', detail=str(exc))
    names_a = [n for n, s in a['sections'].items() if s['flags'] & ALLOC]
    names_b = [n for n, s in b['sections'].items() if s['flags'] & ALLOC]
    if sorted(names_a) != sorted(names_b):
        return dict(kind='section_set', only_before=sorted(set(names_a) - set(names_b))[:8],
                    only_after=sorted(set(names_b) - set(names_a))[:8])
    for name in names_a:
        sa, sb = a['sections'][name], b['sections'][name]
        if sa['size'] != sb['size']:
            off = next((i for i, (x, y) in enumerate(zip(sa['data'], sb['data'])) if x != y),
                       min(sa['size'], sb['size']))
            return dict(kind='section_size', section=name, before=sa['size'], after=sb['size'], offset=off,
                        symbol=symbol_at(a, name, off))
        if sa['data'] != sb['data']:
            off = next(i for i, (x, y) in enumerate(zip(sa['data'], sb['data'])) if x != y)
            return dict(kind='bytes', section=name, offset=off, symbol=symbol_at(a, name, off))
        ra, rb = a['relocs'].get(name, []), b['relocs'].get(name, [])
        if ra != rb:
            n = next((i for i, (x, y) in enumerate(zip(ra, rb)) if x != y), min(len(ra), len(rb)))
            x = ra[n] if n < len(ra) else None
            y = rb[n] if n < len(rb) else None
            off = (x or y)[0]
            return dict(kind='relocation', section=name, offset=off, symbol=symbol_at(a, name, off),
                        before=list(x) if x else None, after=list(y) if y else None)
    glob_a = sorted((s['name'], s['bind'], s['type']) for s in a['symbols'] if s['bind'] == 1)
    glob_b = sorted((s['name'], s['bind'], s['type']) for s in b['symbols'] if s['bind'] == 1)
    if glob_a != glob_b:
        return dict(kind='global_symbols', only_before=sorted(set(glob_a) - set(glob_b))[:8],
                    only_after=sorted(set(glob_b) - set(glob_a))[:8])
    return dict(kind='metadata_only')


# ------------------------------------------------------------------------------- baseline freshness

class Baseline:
    """Baseline objects/images: `base` root build outputs, or the candidate's own pre-edit outputs."""

    def __init__(self, root, base, edited, rev='HEAD', known=None):
        self.root, self.base = Path(root).resolve(), Path(base).resolve()
        self.same = self.root == self.base
        self.edited = set(edited)
        self.rev = rev
        self.known = dict(known or {})     # logical path -> pre-edit sha256 (snapshot callers)
        self.unverified = set()
        self._logical = {}
        self._file_sha = {}
        self._git_sha = {}

    def _current(self, tree, name):
        key = (str(tree), name)
        if key not in self._file_sha:
            try:
                self._file_sha[key] = sha256((tree / name).read_bytes())
            except OSError:
                self._file_sha[key] = None
        return self._file_sha[key]

    def _committed(self, name):
        if name not in self._git_sha:
            res = subprocess.run(['git', '-C', str(self.root), 'show', self.rev + ':' + name],
                                 capture_output=True)
            self._git_sha[name] = sha256(res.stdout) if res.returncode == 0 else None
        return self._git_sha[name]

    def expected(self, name):
        """The src/include text sha the baseline must have been built from."""
        if not self.same:
            return self._current(self.base, name)
        logical = self._logical.get(name)
        if logical is None:
            real = Path(name if name.startswith(SOURCE_PREFIXES) else os.path.realpath(self.root / name))
            real = real if not real.is_absolute() else (
                real.relative_to(self.root) if real.is_relative_to(self.root) else Path(name))
            logical = self._logical[name] = real.as_posix()
        if logical in self.known:
            return self.known[logical]
        if logical in self.edited:
            committed = self._committed(logical)
            if committed is None:
                self.unverified.add(logical)   # no git text: object sha + unedited inputs still checked
            return committed
        return self._current(self.root, name)

    def object(self, spec):
        """(bytes, problem) of the baseline object for one recipe."""
        path = self.base / spec['output']
        proof = path.with_suffix('.proof.json')
        if not path.is_file():
            return None, 'baseline object missing: ' + spec['output']
        blob = path.read_bytes()
        if not proof.is_file():
            return blob, 'baseline object has no .proof.json'
        receipt = _read_json(proof)
        if receipt.get('object_sha256') != sha256(blob):
            return blob, 'baseline object differs from its .proof.json'
        for name, digest in receipt.get('inputs', {}).items():
            logical = name[len('build_slus/'):] if name.startswith('build_slus/') else name
            if not logical.startswith(SOURCE_PREFIXES):
                continue
            want = self.expected(name)
            if want is not None and want != digest:
                return blob, 'baseline object was built from another ' + logical
        return blob, None


# ------------------------------------------------------------------------------------------- workers

WORKER_BOOT = r'''
import json, os, sys
from pathlib import Path
root = Path(sys.argv[1]); sys.path.insert(0, str(root)); os.chdir(root)
import importlib.util
spec = importlib.util.spec_from_file_location('affected_worker', sys.argv[2])
module = importlib.util.module_from_spec(spec); spec.loader.exec_module(module)
module.worker_loop(root)
'''


def worker_loop(root):
    """Long-lived worker in the candidate root: one JSON task per stdin line, one result per stdout line."""
    import contextlib
    import io
    import tempfile
    from tools.build import mkbuild as mk
    if mk.ROOT != Path(root).resolve():
        raise SystemExit('worker imported mkbuild from another root: ' + str(mk.ROOT))
    tmp = mk.STATE / 'tmp'
    tmp.mkdir(parents=True, exist_ok=True)
    os.environ['TMPDIR'] = str(tmp)
    tempfile.tempdir = str(tmp)
    out = sys.stdout
    for line in sys.stdin:
        task = json.loads(line)
        started = time.monotonic()
        sink = io.StringIO()
        try:
            with contextlib.redirect_stdout(sink):
                if task['op'] == 'compile':
                    result = _w_compile(mk, task)
                elif task['op'] == 'link':
                    result = _w_link(mk, task)
                else:
                    raise ValueError('unknown op ' + task['op'])
        except Exception as exc:   # reported, never passed
            result = dict(error=(type(exc).__name__ + ': ' + str(exc))[-1500:])
        result.update(key=task['key'], seconds=round(time.monotonic() - started, 3))
        out.write(json.dumps(result) + '\n')
        out.flush()


def _w_compile(mk, task):
    spec = dict(task['spec'])
    run, rid = task['run'], task['id']
    spec.pop('_family', None)
    spec.pop('_id', None)
    target = '%s/obj/%s.o' % (run, rid)
    if spec.get('name_input'):
        spec['name_input'] = '%s/names/%s.json' % (run, rid)
    if task['family'] == 'slus':
        # The output path recurs in post-processing steps (`&& slus_data_pieces.py --object OUT`):
        # every whole-token occurrence is redirected.
        import re
        old = spec['output'][len('build_slus/'):] if spec['output'].startswith('build_slus/') else None
        pattern = re.compile(r'(?<![\w/.-])' + re.escape(old or '\0') + r'(?![\w/.-])')
        if not old or not pattern.search(spec['command']):
            raise ValueError('unexpected SLUS command shape: ' + spec['command'])
        new = os.path.relpath(mk.ROOT / target, mk.ROOT / 'build_slus')
        spec['command'] = pattern.sub(lambda m: new, spec['command'])
        spec['output'] = target
        path = mk.ROOT / run / 'recipes' / (rid + '.json')
        mk.put(path, spec)
        mk.slus_compile_uncached(path)
    else:
        if spec.get('projection'):
            # Re-derive the placement copy from the candidate's (edited) owner TU, as make does.
            sys.path.insert(0, str(mk.ROOT / 'tools'))
            from gate.source_layout import member_projection
            unit = member_projection(spec['projection']['home'], mk.ROOT)
            if unit is None:
                raise ValueError('member projection vanished: ' + spec['projection']['home'])
            # The object records its source path (STT_FILE), so the copy is written where make writes
            # it; content is a pure function of the owner and identical for recipes sharing a path.
            source = mk.ROOT / spec['source']
            blob = unit.encode() if isinstance(unit, str) else unit
            if not source.is_file() or source.read_bytes() != blob:
                source.parent.mkdir(parents=True, exist_ok=True)
                temporary = source.with_name('%s.%d.affected.tmp' % (source.name, os.getpid()))
                temporary.write_bytes(blob)
                os.replace(temporary, source)
        spec['output'] = target
        path = mk.ROOT / run / 'recipes' / (rid + '.json')
        mk.put(path, spec)
        mk.compile_uncached(path)
    blob = (mk.ROOT / target).read_bytes()
    return dict(object=target, sha256=sha256(blob))


def _w_link(mk, task):
    """Production `_image_one` link into a private state folder, changed objects substituted."""
    run, tag = task['run'], task['tag']
    spec = mk.read(task['image_spec'])
    private = mk.ROOT / run / 'link' / tag
    if private.exists():
        shutil.rmtree(private)
    (private / 'recipes').mkdir(parents=True)
    (private / 'link').mkdir()
    (private / 'origins').mkdir()
    (private / 'linkinputs.ok').symlink_to(mk.STATE / 'linkinputs.ok')
    objects = task['objects']          # recipe id -> object path (absolute or root-relative)
    for unit in spec['units']:
        recipe = mk.read(mk.STATE / 'recipes' / (unit['recipe'] + '.json'))
        recipe['output'] = objects[unit['recipe']]
        mk.put(private / 'recipes' / (unit['recipe'] + '.json'), recipe)
    spec['output'] = '%s/images/%s.bin' % (run, tag)
    (mk.ROOT / spec['output']).parent.mkdir(parents=True, exist_ok=True)
    spec_path = private / 'image.json'
    mk.put(spec_path, spec)
    original = mk.STATE
    mk.STATE = private
    try:
        mk._image_one(spec_path)
    finally:
        mk.STATE = original
    produced = (mk.ROOT / spec['output']).read_bytes()
    baseline = Path(task['baseline_image']).read_bytes()
    if produced == baseline:
        return dict(image_equal=True)
    offset = mk.first_difference(produced, baseline)
    return dict(image_equal=False, offset=offset, symbol=mk.checked_symbol(spec, offset))


class Workers:
    """N long-lived worker processes in the candidate root (mkbuild imported once per worker)."""

    def __init__(self, root, n, nice=10):
        self.root = Path(root).resolve()
        boot = [sys.executable, '-c', WORKER_BOOT, str(self.root), str(HERE)]
        pre = (lambda: os.nice(nice)) if nice else None
        self.procs = [subprocess.Popen(boot, cwd=self.root, stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                                       text=True, preexec_fn=pre) for _ in range(n)]
        self.free = queue.Queue()
        for p in self.procs:
            self.free.put(p)

    def call(self, task):
        proc = self.free.get()
        try:
            proc.stdin.write(json.dumps(task) + '\n')
            proc.stdin.flush()
            line = proc.stdout.readline()
            if not line:
                raise RuntimeError('worker %d exited' % proc.pid)
            return json.loads(line)
        finally:
            self.free.put(proc)

    def map(self, tasks):
        with ThreadPoolExecutor(max_workers=len(self.procs)) as ex:
            return list(ex.map(self.call, tasks))

    def close(self):
        for p in self.procs:
            try:
                p.stdin.close()
                p.wait(timeout=30)
            except Exception:
                if p.poll() is None:
                    p.kill()       # our own child, by its exact handle


# --------------------------------------------------------------------------------------------- prove

def edited_from_git(root, rev):
    """Files changed in the candidate root since `rev` (tracked diff plus untracked src/include files)."""
    diff = subprocess.check_output(['git', '-C', str(root), 'diff', '--name-only', rev], text=True).split()
    new = subprocess.check_output(['git', '-C', str(root), 'ls-files', '--others', '--exclude-standard',
                                   '--', 'src', 'include'], text=True).split()
    return sorted(set(diff) | set(new))


def prove(root, edited, base=None, *, workers=8, relink=True, rev='HEAD', keep=False, nice=10,
          allow_authority=False, log=None, graph=None, compile_tasks=None, known=None, reuse=None,
          reuse_key=None):
    """Compile the affected set at production recipes and compare objects/images with the baseline.

    Returns a report: {verdict, scope, recipes: {id: {...}}, images: {image: {...}}, timing}.
    verdict: PASS (every affected object and image identical), CHANGED, STALE_BASE or ERROR.

    reuse / reuse_key (repeated proofs over one baseline, e.g. tools/typing/sig_batch.py bisection):
    `reuse_key(recipe id)` names the recipe's inputs (None: always compile); a recipe whose key is in
    the `reuse` dict was compiled byte-identical to its baseline object by an earlier proof and is PASS
    without a compile (its baseline object stands in for any relink).  PASS keys are added to `reuse`."""
    log = log or (lambda msg: None)
    root = Path(root).resolve()
    base = Path(base).resolve() if base else root
    started = time.monotonic()
    graph = graph or Graph(root)
    scope = affected_set(root, edited, graph)
    log('scope: %d recipes, %d SLUS recipes, %d images (%s)' % (
        len(scope['recipes']), len(scope['slus_recipes']), len(scope['images']), scope['kinds']))
    report = dict(root=str(root), base=str(base), scope=scope, recipes={}, images={})
    if scope['authority'] and not allow_authority:
        report.update(verdict='ERROR', error='graph-authority edits need make configure + a full build: '
                      + ', '.join(scope['authority']))
        return report
    baseline = Baseline(root, base, scope['files'], rev, known)
    ids = scope['recipes'] + scope['slus_recipes']
    # Generated SLUS sources (partition bodies) are re-rendered from the edited parents, as make does.
    renders = {}
    for rid in scope['slus_recipes']:
        for dep in graph.recipes[rid].get('dependencies', ()):
            if dep in graph.generated:
                renders[graph.generated[dep]['command']] = graph.generated[dep]
    for command in sorted(renders):
        if compile_tasks is None:
            res = subprocess.run(['bash', '-c', command], cwd=root, capture_output=True, text=True)
            if res.returncode:
                report.update(verdict='ERROR', error='render failed: ' + command + '\n' + res.stderr[-800:])
                return report
    report['renders'] = sorted(renders)
    run = 'build/.affected/%s-%d' % (time.strftime('%Y%m%d-%H%M%S'), os.getpid())
    (root / run).mkdir(parents=True)
    keys = {rid: reuse_key(rid) for rid in ids} if reuse is not None and reuse_key else {}
    reused = [rid for rid in ids if keys.get(rid) is not None and keys[rid] in reuse]
    for rid in reused:
        spec = graph.recipes[rid]
        rec = dict(source=spec.get('source') or spec.get('command'), family=spec['_family'], verdict='PASS',
                   reused=True)
        if spec.get('projection'):
            rec['owner'] = spec['projection']['owner']
        report['recipes'][rid] = rec
    report['reused'] = len(reused)
    reused = set(reused)
    tasks = [dict(op='compile', key=rid, id=rid, run=run, family=graph.recipes[rid]['_family'],
                  spec=graph.recipes[rid]) for rid in ids if rid not in reused]
    pool = None
    try:
        t0 = time.monotonic()
        if compile_tasks is not None:          # tests inject a compiler
            results = [compile_tasks(t) for t in tasks]
        elif tasks:
            pool = Workers(root, max(1, min(workers, len(tasks))), nice)
            results = pool.map(tasks)
        else:
            results = []
        report['compile_seconds'] = round(time.monotonic() - t0, 1)
        changed_objects = {}
        for task, res in zip(tasks, results):
            rid = task['id']
            spec = graph.recipes[rid]
            rec = dict(source=spec.get('source') or spec.get('command'), family=task['family'],
                       seconds=res.get('seconds'))
            if spec.get('projection'):
                rec['owner'] = spec['projection']['owner']
            if 'error' in res:
                lines = [l.strip() for l in res['error'].splitlines() if l.strip()]
                cause = next((l for l in reversed(lines) if 'error' in l.lower() and 'ValueError' not in l),
                             lines[-1] if lines else '')
                root_prefix = str(root) + '/'
                rec.update(verdict='ERROR', error=res['error'], cause=cause.replace(root_prefix, '')[:300])
            else:
                before, problem = baseline.object(spec)
                after = (root / res['object']).read_bytes()
                if problem:
                    rec.update(verdict='STALE_BASE', error=problem)
                    if before is not None and before == after:
                        rec['equal_to_stale_baseline'] = True
                else:
                    diff = object_difference(before, after)
                    rec['verdict'] = 'PASS' if diff is None else 'CHANGED'
                    if diff is None and before == after and keys.get(rid) is not None:
                        reuse[keys[rid]] = True
                    if diff:
                        rec['difference'] = diff
                        changed_objects[rid] = res['object']
            report['recipes'][rid] = rec
        # Images: identical objects -> identical image; relink only those with a changed object.
        t1 = time.monotonic()
        link_tasks = []
        for image in scope['images']:
            mine = [r for r in (graph.images[image]['recipes'] if image in graph.images else ids)
                    if r in report['recipes']]
            if image == graph.slus_image:
                mine = scope['slus_recipes']
            states = {report['recipes'][r]['verdict'] for r in mine}
            entry = dict(recipes=len(mine))
            report['images'][image] = entry
            if states <= {'PASS'}:
                entry['verdict'] = 'PASS'
                continue
            if 'ERROR' in states or 'STALE_BASE' in states:
                entry['verdict'] = 'ERROR' if 'ERROR' in states else 'STALE_BASE'
                continue
            entry['changed_recipes'] = sorted(r for r in mine if report['recipes'][r]['verdict'] == 'CHANGED')
            entry['verdict'] = 'CHANGED'
            if image == graph.slus_image or not relink:
                entry['relink'] = 'not run (%s)' % ('SLUS image: object level' if image == graph.slus_image
                                                    else '--no-relink')
                continue
            spec = graph.images[image]
            baseline_image = base / spec['output']
            objects = {}
            for rid in spec['recipes']:
                objects[rid] = changed_objects.get(rid) or str(base / graph.recipes[rid]['output'])
            link_tasks.append(dict(op='link', key=image, run=run, tag=spec['tag'], image_spec=spec['path'],
                                   objects=objects, baseline_image=str(baseline_image)))
        if link_tasks and compile_tasks is None:
            if pool is None:
                pool = Workers(root, max(1, min(workers, len(link_tasks))), nice)
            for task, res in zip(link_tasks, pool.map(link_tasks)):
                entry = report['images'][task['key']]
                if 'error' in res:
                    entry.update(relink='link failed', **link_failure(res['error'], graph.images[task['key']]))
                elif res['image_equal']:
                    entry.update(verdict='PASS', relink='image identical (object change not placed)')
                else:
                    entry.update(relink='image differs', first_offset=res['offset'], first_symbol=res['symbol'])
        report['relink_seconds'] = round(time.monotonic() - t1, 1)
    finally:
        if pool:
            pool.close()
        if not keep:
            shutil.rmtree(root / run, ignore_errors=True)
        else:
            report['run_dir'] = run
    report['baseline_unverified_edits'] = sorted(baseline.unverified)
    verdicts = [r['verdict'] for r in report['recipes'].values()] + \
               [i['verdict'] for i in report['images'].values()]
    report['verdict'] = ('ERROR' if 'ERROR' in verdicts else 'STALE_BASE' if 'STALE_BASE' in verdicts
                         else 'CHANGED' if any(i['verdict'] == 'CHANGED' for i in report['images'].values())
                         else 'PASS')
    report['counts'] = {k: verdicts.count(k) for k in sorted(set(verdicts))}
    # An object can differ only outside its placed bytes (symbol table, unplaced sections); every image
    # containing it was relinked and compared, so the build output is unchanged.
    report['objects_changed_not_placed'] = sorted(
        r for r, rec in report['recipes'].items() if rec['verdict'] == 'CHANGED' and report['verdict'] == 'PASS')
    report['seconds'] = round(time.monotonic() - started, 1)
    return report


def link_failure(error, image):
    """Readable cause of a failed relink: the first ld error and the unit it names."""
    lines = [l for l in error.splitlines() if l.strip()]
    first = next((l for l in lines[1:] if 'warning:' not in l), lines[0] if lines else error)
    first = first.replace('mipsel-linux-gnu-ld: ', '')
    out = dict(link_error=first[:300])
    if 'source/import extent' in first:
        out['link_error'] = 'linked size differs from the retail extent (%s)' % first.strip()
    import re
    m = re.search(r'/(\d+)\.o\b', error)
    if m:
        try:
            spec = _read_json(image['path'])
            unit = spec['units'][int(m.group(1))]
            out['link_unit'] = '%s (recipe %s)' % (unit.get('func'), unit['recipe'])
        except (OSError, ValueError, IndexError, KeyError):
            pass
    return out


def summary(report, limit=20):
    """Short human-readable lines for a prove report."""
    s = report['scope']
    lines = ['%s: %d recipes (%s), %d SLUS recipes, %d images; %.1fs' % (
        report['verdict'], len(s['recipes']), ', '.join('%s %d' % kv for kv in sorted(s['kinds'].items())),
        len(s['slus_recipes']), len(s['images']), report.get('seconds', 0))]
    if report.get('objects_changed_not_placed'):
        lines.append('  note: %d objects differ only outside their placed bytes; every image is identical'
                     % len(report['objects_changed_not_placed']))
    if report.get('error'):
        lines.append('  error: ' + report['error'])
    bad = [(rid, r) for rid, r in sorted(report['recipes'].items()) if r['verdict'] != 'PASS']
    for rid, r in bad[:limit]:
        d = r.get('difference', {})
        where = d.get('symbol') or d.get('kind') or r.get('cause') or r.get('error', '')[:160]
        lines.append('  recipe %s %s %s%s: %s' % (rid, r['verdict'], r['source'],
                                                  ' (copy of %s)' % r['owner'] if r.get('owner') else '', where))
    for image, e in sorted(report['images'].items()):
        if e['verdict'] != 'PASS' or e.get('relink'):
            lines.append('  image %s %s%s' % (image, e['verdict'], (
                ' at %s (+0x%X)' % (e['first_symbol'], e['first_offset']) if e.get('first_symbol') else
                ' [%s: %s%s]' % (e['relink'], e['link_error'], ' at ' + e['link_unit'] if e.get('link_unit') else '')
                if e.get('link_error') else ' [%s]' % e['relink'] if e.get('relink') else '')))
    if len(bad) > limit:
        lines.append('  ... %d more non-PASS recipes' % (len(bad) - limit))
    return lines


def relink_check(root, images, workers=4, nice=10, graph=None):
    """Relink images from the root's own objects through the private link path; each must equal the
    built image (a self-test of the relink machinery: identical objects must give identical images)."""
    root = Path(root).resolve()
    graph = graph or Graph(root)
    run = 'build/.affected/relink-%s-%d' % (time.strftime('%Y%m%d-%H%M%S'), os.getpid())
    tasks = []
    for image in images:
        spec = graph.images[image]
        tasks.append(dict(op='link', key=image, run=run, tag=spec['tag'], image_spec=spec['path'],
                          objects={r: str(root / graph.recipes[r]['output']) for r in spec['recipes']},
                          baseline_image=str(root / spec['output'])))
    pool = Workers(root, max(1, min(workers, len(tasks))), nice)
    try:
        return {t['key']: r for t, r in zip(tasks, pool.map(tasks))}
    finally:
        pool.close()
        shutil.rmtree(root / run, ignore_errors=True)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest='mode', required=True)
    rc = sub.add_parser('relink-check', help='self-test: relink images from unchanged objects')
    rc.add_argument('--root', type=Path, default=DEFAULT_ROOT)
    rc.add_argument('images', nargs='+')
    rc.add_argument('--workers', type=int, default=4)
    for name in ('set', 'prove'):
        p = sub.add_parser(name)
        p.add_argument('--root', type=Path, default=DEFAULT_ROOT)
        p.add_argument('files', nargs='*')
        p.add_argument('--edited-from-git', metavar='REV', help='edit set = git diff --name-only REV (+ untracked)')
        p.add_argument('--json', type=Path, help='write the full JSON report here')
    pp = sub.choices['prove']
    pp.add_argument('--base', type=Path, help='root holding baseline build/obj + images (default: --root)')
    pp.add_argument('--rev', default='HEAD', help='committed text of edited files when --base is --root')
    pp.add_argument('--workers', type=int, default=8)
    pp.add_argument('--nice', type=int, default=10)
    pp.add_argument('--no-relink', action='store_true')
    pp.add_argument('--keep', action='store_true', help='keep build/.affected/<run> objects and links')
    pp.add_argument('--allow-authority', action='store_true')
    args = ap.parse_args(argv)
    root = args.root.resolve()
    if args.mode == 'relink-check':
        res = relink_check(root, args.images, min(max(args.workers, 1), 8))
        print(json.dumps(res, indent=1, sort_keys=True))
        return 0 if all(r.get('image_equal') for r in res.values()) else 1
    files = list(args.files)
    if args.edited_from_git:
        files += edited_from_git(root, args.edited_from_git)
    if not files:
        ap.error('no edited files (name them or pass --edited-from-git REV)')
    if args.mode == 'set':
        scope = affected_set(root, files)
        if args.json:
            args.json.write_text(json.dumps(scope, indent=1, sort_keys=True) + '\n')
        print(json.dumps(dict(scope, recipes=len(scope['recipes']), slus_recipes=len(scope['slus_recipes']),
                              images=scope['images'][:40], images_total=len(scope['images'])), sort_keys=True))
        return 0
    if not 1 <= args.workers <= 8:
        ap.error('between 1 and 8 workers on this host')
    report = prove(root, files, args.base, workers=args.workers, relink=not args.no_relink, rev=args.rev,
                   keep=args.keep, nice=args.nice, allow_authority=args.allow_authority,
                   log=lambda m: print(m, file=sys.stderr, flush=True))
    if args.json:
        args.json.parent.mkdir(parents=True, exist_ok=True)
        args.json.write_text(json.dumps(report, indent=1, sort_keys=True) + '\n')
    print('\n'.join(summary(report)))
    return 0 if report['verdict'] == 'PASS' else 1


if __name__ == '__main__':
    sys.exit(main())
