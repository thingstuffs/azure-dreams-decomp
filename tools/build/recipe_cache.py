"""Private configure checkpoints, bound to content rather than file timestamps.

Only edits to existing source/include files can reuse general checkpoints. An
edit to the configure driver may reuse include closures when its closure entry
point and every other authority are unchanged. Each closure still binds its
own input files. This cache contains recipes, never compile/image proofs or
gate verdicts.
"""
import copy
import gzip
import hashlib
import json
import os
from pathlib import Path
import types


def portable(value, root_text):
    """A walker's behaviour as JSON, independent of where its checkout lives and of interpreter state. Marshalled
    code is neither: its bytes embed the absolute co_filename and depend on object reference counts (FLAG_REF), so
    the same include walker hashed differently in a scratch root, and in any run after placement validation ran."""
    if isinstance(value, types.CodeType):
        return ['code', value.co_name, value.co_code.hex(), value.co_argcount, value.co_posonlyargcount,
                value.co_kwonlyargcount, value.co_flags, value.co_names, value.co_varnames, value.co_freevars,
                value.co_cellvars, [portable(c, root_text) for c in value.co_consts]]
    if isinstance(value, (frozenset, set)):
        return [type(value).__name__, sorted(json.dumps(portable(v, root_text)) for v in value)]
    if isinstance(value, tuple):
        return ['tuple', [portable(v, root_text) for v in value]]
    if isinstance(value, dict):
        return ['dict', sorted([repr(k), portable(v, root_text)] for k, v in value.items())]
    return repr(value).replace(root_text, '<root>')


# Configure inputs whose checkpoint guard binds their structure only. Every landing rewrites fields of these that are
# derived from source bytes: the link graph's TU source_sha256 witnesses (and the shard and layout_inline digests in
# its manifest), and layout_inline's member extents, hashes and original include spellings (an #include edit inside
# an inlined fragment rewrites them). Their readers are bound per checkpoint instead:
# - mkbuild binds the raw link-graph files on the 'graph' checkpoint (bind=), the only checkpoint that reads them, and
#   its consumers use only the structure (attestation refreshes every source witness from the live snapshot);
# - each checkpoint that reads a TU named by layout_inline binds that TU's records with its bytes (see bound()): the
#   extents, hashes and include spellings only select, restore or check bytes of their own TU, so any reader must
#   read that TU.
LAYOUT_INLINE = 'ledger/layout_inline.jsonl'
INLINE_DERIVED = frozenset(('offset', 'source_sha256', 'bytes', 'inlined_bytes', 'original_includes'))
GRAPH_MANIFEST = 'config/link_graph/graph.json'
_STRUCTURE = {}
# Configure inputs bound per checkpoint, by observed reads, instead of by the guard: the name table changes in most
# batches (per-overlay behaviour names) and no checkpoint reads it today (an audit-hook trace of a cold `generate full`
# saw only top-level readers, which run every configure); a checkpoint that does read it binds its bytes on its own
# record. It stays a configure input, so the unchanged-projection fast path still binds it.
PER_RECORD = frozenset({'config/names.tsv'})


def is_structural(name):
    return name in (LAYOUT_INLINE, GRAPH_MANIFEST) or (name.startswith('config/link_graph/tus.')
                                                        and name.endswith('.jsonl'))


def _records(blob):
    return [json.loads(line) for line in blob.decode().splitlines() if line.strip()]


def structure_of(name, blob):
    """The part of a structural input that its source-derived fields leave out."""
    if name == LAYOUT_INLINE:
        return [{k: v for k, v in r.items() if k not in INLINE_DERIVED} for r in _records(blob)]
    if name == GRAPH_MANIFEST:
        manifest = json.loads(blob)
        for part in manifest.get('tables', {}).get('tus', ()):
            part.pop('sha256', None)
        if LAYOUT_INLINE in manifest.get('inputs', {}):
            manifest['inputs'][LAYOUT_INLINE] = None
        return manifest
    return [{k: v for k, v in r.items() if k != 'source_sha256'} for r in _records(blob)]


def structural_digest(root, name, digest):
    """Guard value of one input: its content digest, or the digest of its structure for is_structural names.

    Falls back to the content digest when the file no longer has that digest or does not parse."""
    if digest is None or root is None or not is_structural(name):
        return digest
    key = (os.path.join(os.fspath(root), name), digest)
    if key not in _STRUCTURE:
        try:
            blob = (Path(root)/name).read_bytes()
            if hashlib.sha256(blob).hexdigest() != digest:
                return digest
            value = 'structure:' + hashlib.sha256(json.dumps(structure_of(name, blob), sort_keys=True).encode()).hexdigest()
        except (OSError, ValueError, KeyError, TypeError, AttributeError):
            return digest
        _STRUCTURE[key] = value
    return _STRUCTURE[key]


def inline_slices(root, digest):
    """{TU: digest of its layout_inline records, in ledger order}, from the ledger bytes with that digest."""
    if digest is None:
        return {}
    blob = (Path(root)/LAYOUT_INLINE).read_bytes()
    if hashlib.sha256(blob).hexdigest() != digest:
        raise ValueError('configure inputs changed during generation: ' + LAYOUT_INLINE)
    groups = {}
    for record in _records(blob):
        groups.setdefault(record.get('tu_new'), []).append(record)
    return {tu: hashlib.sha256(json.dumps(records, sort_keys=True).encode()).hexdigest()
            for tu, records in groups.items() if isinstance(tu, str)}


class RecipeCache:
    @staticmethod
    def guard_for(inputs, context):
        # Names/presence bind negative include resolution probes as well.
        root = context.get('root')
        authority = {n: (v is not None if n.startswith(('src/', 'include/')) or n in PER_RECORD
                         else structural_digest(root, n, v))
                     for n, v in inputs.items()}
        return hashlib.sha256(json.dumps([authority, context], sort_keys=True).encode()).hexdigest()

    @staticmethod
    def closure_guard_for(inputs, context, closure_entry):
        closure_inputs = dict(inputs)
        if closure_entry is not None and 'tools/build/mkbuild.py' in closure_inputs:
            closure_inputs['tools/build/mkbuild.py'] = hashlib.sha256(closure_entry.encode()).hexdigest()
        return RecipeCache.guard_for(closure_inputs, context)

    def __init__(self, root, inputs, context, saved=None, closure_entry=None):
        self.root = Path(root)
        self.inputs = inputs
        self.digests = dict(inputs)
        self.used = set()
        self.names = {}
        self.closure_entry = closure_entry
        self.guard = self.guard_for(inputs, context)
        # The driver does not implement the include walk: it passes root and
        # starts to module.closure. Bind that entry point separately so edits
        # elsewhere in mkbuild.py need not repeat thousands of identical walks.
        self.closure_guard = self.closure_guard_for(inputs, context, closure_entry)
        records = saved.get('records', {}) if saved else {}
        if saved and saved.get('guard') == self.guard:
            self.old = records
        elif saved and saved.get('closure_guard') == self.closure_guard:
            self.old = {k: v for k, v in records.items() if k.startswith('closure:')}
        else:
            self.old = {}
        self.records = {}
        self.hits = self.misses = 0
        self.walkers = {}
        self.inline = inline_slices(self.root, inputs.get(LAYOUT_INLINE))

    def name(self, path):
        logical = os.path.abspath(path)
        if logical not in self.names:
            prefix = os.fspath(self.root) + os.sep
            physical = os.path.realpath(logical)
            # An external header still has a content-bound logical name.
            path = physical if physical.startswith(prefix) else logical
            self.names[logical] = path[len(prefix):] if path.startswith(prefix) else None
        return self.names[logical]

    @staticmethod
    def hash_at(root, name):
        if os.path.isabs(name) or '..' in name.split('/'):
            raise ValueError('unsafe checkpoint input: '+name)
        try:
            return hashlib.sha256((root/name).read_bytes()).hexdigest()
        except FileNotFoundError:
            return None
        except IsADirectoryError:
            names = sorted(n for n in os.listdir(root/name) if n != '__pycache__')
            return 'directory:' + hashlib.sha256(json.dumps(names).encode()).hexdigest()

    def current_digest(self, name):
        return self.hash_at(self.root, name)

    def digest(self, name):
        self.used.add(name)
        if name not in self.digests:
            self.digests[name] = self.current_digest(name)
        return self.digests[name]

    def bound(self, name):
        """A record's binding of one input: its digest, plus its layout_inline records when it is a TU named there."""
        digest = self.digest(name)
        inline = self.inline.get(name)
        return digest if digest is None or inline is None else digest + '+inline:' + inline

    def memo(self, key, produce, dependencies=None, copy_value=True, bind=()):
        """bind names inputs bound to this record by content even though the guard covers them."""
        old = self.old.get(key)
        if old and all(self.bound(n) == d for n, d in old['inputs'].items()):
            self.records[key] = old
            self.hits += 1
            return copy.deepcopy(old['value']) if copy_value else old['value']
        if dependencies is None:
            from gate_read_cache import observing, stamp_of
            with observing() as observed:
                value = produce()
            probes = {}
            for path, stamp in observed.items():
                if path == '\0volatile':
                    continue
                name = self.name(path)
                if (not name or name.startswith(('build/.state/', 'build_slus/build/'))
                        or '__pycache__' in name.split('/') or name.endswith(('.pyc', '.tmp'))):
                    continue
                if name.startswith(('src/', 'include/')) or name not in self.inputs or name in PER_RECORD:
                    probes[name] = (path, stamp)
            # Bind undeclared review files and absent optional inputs too. Their
            # parent directory name sets catch new siblings outside inventories.
            names = set(probes)
            for name, (path, stamp) in probes.items():
                self.digest(name)
                if stamp_of(path) != stamp:
                    raise ValueError('inputs changed during generation (checkpoint '+key+')')
            cacheable = '\0volatile' not in observed
        else:
            value = produce()
            names = {self.name(p) for p in dependencies(value)} - {None}
            cacheable = True
        names = set(names) | set(bind)
        if cacheable:
            self.records[key] = dict(inputs={n: self.bound(n) for n in sorted(names)},
                                     value=copy.deepcopy(value))
        self.misses += 1
        return value

    def extra_unchanged(self):
        return all(self.current_digest(n) == self.digests[n] for n in self.used if n not in self.inputs)

    def closure(self, module, root, starts):
        # Do not observe M.closure's invocation-wide read cache: its observer
        # deliberately merges *all* scans. The transitive result is the exact
        # file set; inventory and symlink guards bind all resolution probes.
        functions = {n: v for n, v in vars(module).items()
                     if isinstance(v, types.FunctionType)
                     and (n == 'closure' or v.__module__ == getattr(module, '__name__', None))}
        walker = getattr(module, 'closure')
        if not isinstance(walker, types.FunctionType):
            return sorted(walker(root, starts))
        functions['closure'] = walker
        signature = (getattr(module, '__name__', None), getattr(module, '__file__', None),
                     tuple(sorted((n, id(v), id(v.__code__)) for n, v in functions.items())))
        cached = self.walkers.get(id(module))
        if cached is None or cached[0] is not module or cached[1] != signature:
            source = getattr(module, '__file__', None)
            source_name = None
            if source is not None:
                source_path = Path(source).resolve()
                if not source_path.is_relative_to(self.root.resolve()):
                    return sorted(walker(root, starts))
                source_name = source_path.relative_to(self.root.resolve()).as_posix()
            root_text = os.fspath(self.root.resolve())
            function_code = [(n, hashlib.sha256(json.dumps(portable(v.__code__, root_text)).encode()).hexdigest(),
                              portable(v.__defaults__, root_text), portable(v.__kwdefaults__, root_text))
                             for n, v in sorted(functions.items())]
            identity = [getattr(module, '__name__', type(module).__qualname__), source_name,
                        self.digest(source_name) if source_name else None, function_code]
            fingerprint = hashlib.sha256(json.dumps(identity, sort_keys=True).encode()).hexdigest()
            self.walkers[id(module)] = module, signature, fingerprint
        else:
            fingerprint = cached[2]
        key = 'closure:' + fingerprint + ':' + os.fspath(root.relative_to(self.root)) + ':' + json.dumps(starts)
        return self.memo(key, lambda: sorted(module.closure(root, starts)),
                         lambda found: [root/n for n in found])

    def blob(self):
        # Bank name sets and frozen evidence repeat across thousands of rows.
        # Share them on disk and after decode, retaining ordinary recipe values.
        records, bases, base_ids, artifacts = {}, {}, {}, {}
        for key, record in self.records.items():
            if key.startswith(('row:', 'module:')):
                value = dict(record['value'])
                spec = dict(value['spec'])
                if spec.get('live') is not None:
                    live = dict(spec['live'])
                    names = live['base_names']
                    identity = base_ids.get(tuple(names))
                    if identity is None:
                        identity = str(len(bases))
                        base_ids[tuple(names)] = identity
                        bases[identity] = names
                    live['base_names'] = identity
                    spec['live'] = live
                for name, text in value['artifacts'].items():
                    if name in artifacts and artifacts[name] != text:
                        raise ValueError('conflicting configure artifact: '+name)
                    artifacts[name] = text
                value['spec'], value['artifacts'] = spec, list(value['artifacts'])
                record = dict(record, value=value)
            records[key] = record
        return gzip.compress(json.dumps(dict(codec=1, guard=self.guard, closure_guard=self.closure_guard,
                                             records=records,
                                             bases=bases, artifacts=artifacts),
                                        sort_keys=True, separators=(',', ':')).encode(), compresslevel=1, mtime=0)


def load(path):
    try:
        saved = json.loads(gzip.decompress(path.read_bytes()))
        if saved.get('codec') == 1:
            def restore_entry(entry):
                if entry is not None:
                    entry['bindings'] = {int(k):v for k,v in entry['bindings'].items()}
            for key, record in saved['records'].items():
                value = record['value']
                if key.startswith(('row:', 'module:')):
                    if value['spec'].get('live') is not None:
                        live = value['spec']['live']
                        live['base_names'] = saved['bases'][live['base_names']]
                    value['artifacts'] = {n:saved['artifacts'][n] for n in value['artifacts']}
                if key.startswith('row:'):
                    restore_entry(value['plan'].get('rebind'))
                elif key.startswith('images:'):
                    for _, image in value['images']:
                        for unit in image['units']:
                            restore_entry(unit.get('rebind'))
        return saved
    except (FileNotFoundError, ValueError, OSError, EOFError, KeyError, TypeError):
        return {}
