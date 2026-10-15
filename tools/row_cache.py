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

    def get(self, row_id, inputs, compute):
        with self.phase('keys'):
            key = content_key(inputs)
        old = self.old.get(row_id)
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
        with self.phase('compute'):
            value = compute()
        if self.enabled:
            value = copy.deepcopy(value)
            self.new[row_id] = dict(key=key, value=value, sha256=content_key(value))
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
        canon, rev, hexnames, name2hex = call_arity._name_tables()
        self.names = content_key([sorted(canon.items()),
                                 [(k, sorted(v)) for k, v in sorted(rev.items())],
                                 [(k, sorted(v)) for k, v in sorted(hexnames.items())],
                                 sorted(name2hex.items())])
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


def text_key(text):
    return hashlib.sha256(text.encode()).hexdigest()
