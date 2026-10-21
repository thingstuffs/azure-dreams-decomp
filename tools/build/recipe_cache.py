"""Private configure checkpoints, bound to content rather than file timestamps.

Only edits to existing source/include files can reuse checkpoints. Any authority,
tool, inventory, environment or symlink change discards the whole cache. Within
that boundary a record binds the files its producer actually reads. This cache
contains recipes, never compile/image proofs or gate verdicts.
"""
import copy
import gzip
import hashlib
import json
import os
from pathlib import Path


class RecipeCache:
    @staticmethod
    def guard_for(inputs, context):
        # Names/presence bind negative include resolution probes as well.
        authority = {n: (v is not None if n.startswith(('src/', 'include/')) else v)
                     for n, v in inputs.items()}
        return hashlib.sha256(json.dumps([authority, context], sort_keys=True).encode()).hexdigest()

    def __init__(self, root, inputs, context, saved=None):
        self.root = Path(root)
        self.inputs = inputs
        self.digests = dict(inputs)
        self.used = set()
        self.names = {}
        self.guard = self.guard_for(inputs, context)
        self.old = saved.get('records', {}) if saved and saved.get('guard') == self.guard else {}
        self.records = {}
        self.hits = self.misses = 0

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

    def memo(self, key, produce, dependencies=None, copy_value=True):
        old = self.old.get(key)
        if old and all(self.digest(n) == d for n, d in old['inputs'].items()):
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
                if name.startswith(('src/', 'include/')) or name not in self.inputs:
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
        if cacheable:
            self.records[key] = dict(inputs={n: self.digest(n) for n in sorted(names)},
                                     value=copy.deepcopy(value))
        self.misses += 1
        return value

    def extra_unchanged(self):
        return all(self.current_digest(n) == self.digests[n] for n in self.used if n not in self.inputs)

    def closure(self, module, root, starts):
        # Do not observe M.closure's invocation-wide read cache: its observer
        # deliberately merges *all* scans. The transitive result is the exact
        # file set; inventory and symlink guards bind all resolution probes.
        key = 'closure:' + os.fspath(root.relative_to(self.root)) + ':' + json.dumps(starts)
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
        return gzip.compress(json.dumps(dict(codec=1, guard=self.guard, records=records,
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
