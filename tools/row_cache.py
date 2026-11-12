"""Content-keyed memoization for accounting facts, never for proof verdicts.

AZURE_ROW_CACHE=0 is the cold oracle. AZURE_ROW_CACHE_STATS optionally names a
JSON metrics file. Cache loss, old schemas and corrupt entries are cache misses.
The authoritative readers and certificate checks still run on every invocation.
"""
from contextlib import contextmanager
import copy
import hashlib
import json
import os
from pathlib import Path
import tempfile
import time


def encoded(value):
    # Preserve mapping order: Counter tie order and levels.jsonl field order are
    # observable. The checksum also detects accidental mapping-order corruption.
    return json.dumps(value, ensure_ascii=True, separators=(',', ':')).encode()


def content_key(value):
    return hashlib.sha256(encoded(value)).hexdigest()


class RowCache:
    def __init__(self, root, name):
        self.path = Path(root) / 'ledger/cache/row_facts' / (name + '.json')
        self.enabled = (os.environ.get('AZURE_ROW_CACHE', '1') != '0'
                        and not self.path.is_symlink()
                        and self.path.parent.resolve().is_relative_to(Path(root).resolve()))
        self.old, self.new = {}, {}
        self.stats = dict(cache=name, enabled=self.enabled, hits=0, misses=0, corrupt=0, phases={})
        if self.enabled:
            try:
                doc = json.loads(self.path.read_text())
                if doc['schema'] == 1 and isinstance(doc['rows'], dict):
                    self.old = doc['rows']
            except (OSError, ValueError, KeyError, TypeError):
                pass

    @contextmanager
    def phase(self, name):
        start = time.monotonic()
        cpu = time.process_time()
        try:
            yield
        finally:
            phases = self.stats['phases']
            phases[name] = phases.get(name, 0) + time.monotonic() - start
            phases[name + '_cpu'] = phases.get(name + '_cpu', 0) + time.process_time() - cpu

    def get(self, row_id, inputs, compute, names=None):
        """names: a NameSlice. The entry then records the name-table entries compute consulted, and a hit needs
        each of them unchanged (an entry without that record misses)."""
        with self.phase('keys'):
            key = content_key(inputs)
        old = self.old.get(row_id)
        if self.enabled and isinstance(old, dict) and old.get('key') == key:
            if names is not None:
                with self.phase('names'):
                    current = names.unchanged(old.get('names'))
                if not current:
                    old = None
        if self.enabled and isinstance(old, dict) and old.get('key') == key:
            try:
                if old['sha256'] == content_key(old['value']):
                    self.new[row_id] = old
                    self.stats['hits'] += 1
                    return copy.deepcopy(old['value'])
            except (KeyError, TypeError, ValueError):
                pass
            self.stats['corrupt'] += 1
        self.stats['misses'] += 1
        consulted = None
        with self.phase('compute'):
            if names is None:
                value = compute()
            else:
                with names.recording() as log:
                    value = compute()
                consulted = names.slice(log)
        if self.enabled:
            value = copy.deepcopy(value)
            self.new[row_id] = dict(key=key, value=value, sha256=content_key(value))
            if consulted is not None:
                self.new[row_id]['names'] = consulted
        return copy.deepcopy(value)

    def save(self):
        if self.enabled:
            try:
                self.path.parent.mkdir(parents=True, exist_ok=True)
                # Concurrent readers see one complete generation. Independent
                # writers can lose hits, never mix entries or change the output.
                with tempfile.NamedTemporaryFile(dir=self.path.parent, delete=False) as f:
                    temp = Path(f.name)
                    f.write(encoded(dict(schema=1, rows=self.new)) + b'\n')
                temp.replace(self.path)
            except OSError:
                if 'temp' in locals():
                    try:
                        temp.unlink(missing_ok=True)
                    except OSError:
                        pass
        if os.environ.get('AZURE_ROW_CACHE_STATS'):
            Path(os.environ['AZURE_ROW_CACHE_STATS']).write_bytes(encoded(self.stats) + b'\n')


class FactInputs:
    """Semantic dependency slices of the preprocessor-free ladder/census scans.

    Source/raw text hashes are local to each row. Config/ledger slices and
    cross-row definitions are hashed as the values the scans actually consume.
    In particular a callee's parameter change invalidates its callers even if
    their own source is unchanged. Body-only changes need not invalidate them.
    Placement is deliberately absent here: callers pass FRESH placement results.
    """
    def __init__(self, root, ladder):
        import census
        import call_arity
        self.ladder, self.arity, self.census = ladder, call_arity, census
        files = ('tools/row_cache.py', 'tools/accounting_modules.py', 'tools/levels.py', 'tools/status.py',
                 'tools/common.py', 'tools/pin_census.py', 'tools/census.py',
                 'tools/call_arity.py', 'tools/gate/gen_noreturn_syms.py')
        self.code = content_key([(name, hashlib.sha256((Path(root)/name).read_bytes()).hexdigest())
                                 for name in files])
        # These helpers consult all definition sources, baseline and the symbol
        # tables. Read them anew in each CLI invocation, not from persistent IO
        # stat memos. Values below include additions/deletions and absent inputs.
        # The name tables (row true names, the SLUS symbol table and config/names.tsv) are keyed per row by the
        # entries each row's evaluation consults (NameSlice, passed to RowCache.get): most batches edit names.tsv
        # (per-overlay behaviour names), and a digest of the whole table missed every row. The values below that
        # use the tables are computed here, outside any row, and enter the keys as values.
        self.names = 'names:per-row-slice'
        self.slice = NameSlice(call_arity)
        self.void = content_key(sorted(census.void_exact_targets()))
        self.sites = census.audit_sites()

    def for_row(self, row):
        keys = [row['container'] + '/' + f for f in (row.get('defs') or [row.get('func')])
                if isinstance(f,str) and f]
        sites = [(key, self.sites.get(key, [])) for key in keys]
        targets = sorted({s.split('|')[1] for _, ss in sites for s in ss
                          if s.startswith('PASSTHRU|')})
        params = []
        if targets:
            idx = self.arity.default_def_index()
            params = [(t, idx.callee_params(t, row['container'], row['id'])) for t in targets]
        return [self.code, self.names, self.void, sites, params]


class _Recording(dict):
    """A read-only copy of one name table that logs the keys looked up (whole-table use logs '*')."""
    def __init__(self, table, index):
        super().__init__(table)
        self.index, self.log = index, None
        self.factory = getattr(table, 'default_factory', None)

    def note(self, key):
        if self.log is not None:
            self.log.add((self.index, key if isinstance(key, str) else '*'))

    def __getitem__(self, key):
        self.note(key)
        try:
            return dict.__getitem__(self, key)
        except KeyError:
            if self.factory is None:
                raise
            return self.factory()  # defaultdict semantics, without inserting

    def get(self, key, default=None):
        self.note(key)
        return dict.get(self, key, default)

    def __contains__(self, key):
        self.note(key)
        return dict.__contains__(self, key)

    def whole(name):
        method = getattr(dict, name)
        def use(self, *args, **kwargs):
            self.note(None)
            return method(self, *args, **kwargs)
        return use
    for _name in ('keys', 'items', 'values', '__iter__', '__len__', 'copy', '__eq__', '__ne__', '__repr__',
                  '__or__', '__ror__'):
        locals()[_name] = whole(_name)
    del whole, _name
    __hash__ = None


class NameSlice:
    """The entries of call_arity's name tables (canon, rev, hexnames, name2hex) a row computation consults.

    recording() swaps call_arity's table memo for recording copies while compute runs; slice() turns the log into
    [table, key, value] triples (value None: absent; key '*': the whole table, by content); a cached entry holds
    while every recorded triple still has its value (unchanged)."""
    def __init__(self, arity):
        self.arity = arity
        self.tables = arity._name_tables()
        self.proxies = tuple(_Recording(t, i) for i, t in enumerate(self.tables))
        self.values = {}

    def value(self, index, key):
        cached = self.values.get((index, key))
        if cached is None:
            table = self.tables[index]
            if key == '*':
                cached = ['*', content_key(sorted([k, sorted(v) if isinstance(v, (set, frozenset)) else v]
                                                  for k, v in table.items()))]
            elif dict.__contains__(table, key):
                v = dict.__getitem__(table, key)
                cached = ['=', sorted(v) if isinstance(v, (set, frozenset)) else v]
            else:
                cached = ['absent']
            self.values[(index, key)] = cached
        return cached

    @contextmanager
    def recording(self):
        log = set()
        saved = self.arity._NAMES
        for proxy in self.proxies:
            proxy.log = log
        self.arity._NAMES = self.proxies
        try:
            yield log
        finally:
            self.arity._NAMES = saved
            for proxy in self.proxies:
                proxy.log = None

    def slice(self, log):
        return [[index, key, self.value(index, key)] for index, key in sorted(log)]

    def unchanged(self, recorded):
        if not isinstance(recorded, list):
            return False
        try:
            return all(self.value(index, key) == value for index, key, value in recorded)
        except (TypeError, ValueError, IndexError):
            return False


def text_key(text):
    return hashlib.sha256(text.encode()).hexdigest()
