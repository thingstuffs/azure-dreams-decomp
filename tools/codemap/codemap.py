#!/usr/bin/env python3
"""codemap.db: one SQLite code map over artefacts the build already emits (a build artefact, never committed).

    codemap.py build   [--root R] [--db PATH] [--workers 8]     cold build (replaces the db)
    codemap.py refresh [--root R] [--db PATH] [--workers 8]     incremental: re-parse TUs whose source or
                                                                include-closure sha changed, re-read objects
                                                                whose sha changed, reload the build graph
                                                                when build/.state/index.json changed
    codemap.py check   [--root R] [--db PATH]                   stored shas vs the tree (exit 1 when stale)
    codemap.py query decls NAME | callers NAME | affected PATH... | families [--limit N] [--kind K]
                     | census [OUT.tsv] [--type-level] | abi NAME | voidret | sql "..."

Default db: <root>/build/codemap.db (build/ is gitignored).  Sources:
  build graph   build/.state/recipes, slus-recipes, images, index.json (tools/build/affected.Graph)
  clang         `clang -Xclang -ast-dump=json` per src/*.c file (tools/codemap/ast_facts.py), in memory
  retail ABI    capstone over the byte-exact linked objects (tools/codemap/abi.py)
  names         config/names.tsv;  debt  tools/lint/debt_check.analyze per src/include file

Tables: meta, source_file, recipe, tu, tu_dep, image, image_unit, name, function, decl, defn, call_site,
retail_fn, retail_call, debt_site, fact_key (incremental state).  Header declaration sites are stored
once (file/line/col/name/signature unique) with the first TU that saw them; `seen` counts TUs.
"""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
from concurrent.futures import ProcessPoolExecutor
import hashlib
import json
import os
from pathlib import Path
import re
import sqlite3
import sys
import time

HERE = Path(__file__).resolve()
TOOLS = HERE.parents[1]
DEFAULT_ROOT = HERE.parents[2]
sys.path[:0] = [str(HERE.parent), str(TOOLS / 'build')]

SCHEMA = '''
CREATE TABLE meta(key TEXT PRIMARY KEY, value TEXT);
CREATE TABLE source_file(path TEXT PRIMARY KEY, sha256 TEXT NOT NULL, kind TEXT);
CREATE TABLE recipe(id TEXT PRIMARY KEY, family TEXT, kind TEXT, source TEXT, physical TEXT, owner TEXT, home TEXT,
    output TEXT, args TEXT, recipe_sha256 TEXT, declaration_context_sha256 TEXT, linked INTEGER);
CREATE INDEX recipe_physical ON recipe(physical);
CREATE TABLE tu(path TEXT PRIMARY KEY, sha256 TEXT, closure_sha256 TEXT, headers TEXT, recipes INTEGER,
    decls INTEGER, calls INTEGER, parse_error TEXT, seconds REAL);
CREATE TABLE tu_dep(recipe TEXT, path TEXT);
CREATE INDEX tu_dep_path ON tu_dep(path);
CREATE INDEX tu_dep_recipe ON tu_dep(recipe);
CREATE TABLE image(name TEXT PRIMARY KEY, tag TEXT, output TEXT, kind TEXT, start INTEGER, size INTEGER,
    vma INTEGER, units INTEGER);
CREATE TABLE image_unit(image TEXT, idx INTEGER, recipe TEXT, func TEXT, kind TEXT, off INTEGER, size INTEGER,
    vma INTEGER, rows TEXT, rebind INTEGER);
CREATE INDEX image_unit_recipe ON image_unit(recipe);
CREATE TABLE name(address TEXT, symbol TEXT, name TEXT, evidence TEXT);
CREATE INDEX name_symbol ON name(symbol);
CREATE INDEX name_name ON name(name);
CREATE TABLE function(name TEXT PRIMARY KEY, symbol TEXT, address TEXT, defs INTEGER, protos INTEGER,
    local_protos INTEGER, signatures INTEGER, sites INTEGER, calls INTEGER, kind TEXT);
CREATE TABLE decl(id INTEGER PRIMARY KEY, name TEXT, kind TEXT, file TEXT, line INTEGER, col INTEGER,
    signature TEXT, composite TEXT, canonical TEXT, norm TEXT, canon_norm TEXT, ret TEXT, params TEXT,
    nparams INTEGER, variadic INTEGER,
    has_proto INTEGER, storage TEXT, local INTEGER, tu TEXT, seen INTEGER,
    UNIQUE(file, line, col, name, signature));
CREATE INDEX decl_name ON decl(name);
CREATE INDEX decl_tu ON decl(tu);
CREATE TABLE defn(name TEXT, file TEXT, line INTEGER, signature TEXT, canonical TEXT, norm TEXT,
    canon_norm TEXT, tu TEXT);
CREATE INDEX defn_name ON defn(name);
CREATE TABLE call_site(tu TEXT, caller TEXT, callee TEXT, file TEXT, line INTEGER, col INTEGER, nargs INTEGER,
    arg_types TEXT, param_types TEXT, callee_type TEXT, ret_use TEXT);
CREATE INDEX call_callee ON call_site(callee);
CREATE INDEX call_tu ON call_site(tu);
CREATE TABLE retail_fn(recipe TEXT, symbol TEXT, name TEXT, section TEXT, size INTEGER, args_read TEXT,
    args_at_first_call TEXT, stack_args_read TEXT, home_stores TEXT, v0_at_return TEXT, v0_all_paths INTEGER,
    return_ext TEXT, calls_out INTEGER, sibcalls INTEGER, indirect_jumps INTEGER, indirect_calls INTEGER,
    returns INTEGER, is_global INTEGER, error TEXT);
CREATE INDEX retail_fn_name ON retail_fn(name);
CREATE INDEX retail_fn_recipe ON retail_fn(recipe);
CREATE TABLE retail_call(recipe TEXT, caller TEXT, offset INTEGER, callee TEXT, callee_name TEXT, kind TEXT,
    a0 TEXT, a1 TEXT, a2 TEXT, a3 TEXT, v0_use TEXT);
CREATE INDEX retail_call_callee ON retail_call(callee_name);
CREATE INDEX retail_call_recipe ON retail_call(recipe);
CREATE TABLE debt_site(file TEXT, function TEXT, line INTEGER, class TEXT, count INTEGER);
CREATE INDEX debt_file ON debt_site(file);
CREATE TABLE fact_key(kind TEXT, key TEXT, sha256 TEXT, PRIMARY KEY(kind, key));
'''

QUAL = re.compile(r'\b(?:const|volatile|register|extern|static|inline)\b')


def sha256(blob):
    return hashlib.sha256(blob).hexdigest()


def norm_sig(signature):
    """Spelled signature with qualifiers and whitespace normalised (the census key)."""
    text = QUAL.sub('', signature or '')
    text = re.sub(r'\s+', ' ', text).strip()
    return re.sub(r'\s*([(),*\[\]])\s*', r'\1', text)


def canonical_site(d):
    """Type-level key of one site: the desugared composite type, except that an unprototyped site keeps
    its `()` (the composite would hide it) — so typedef/struct-tag spelling is not a conflict here."""
    canon = norm_sig(d.get('canonical') or d['signature'])
    if d['kind'] != 'data' and not d['has_proto']:
        cut = canon.find('(')
        canon = (canon[:cut] if cut >= 0 else canon) + '()'
    return canon


# ------------------------------------------------------------------------------------------ workers

def _parse_tu(args):
    root, rel = args
    import ast_facts
    started = time.monotonic()
    headers = []
    try:
        decls, calls, error = ast_facts.unit_facts(root, rel, headers)
    except Exception as exc:
        decls, calls, error = [], [], 'walker: ' + str(exc)[:300]
    return dict(path=rel, decls=decls, calls=calls, error=error,
                headers=sorted({h for h in headers if h.startswith(('src/', 'include/'))}),
                seconds=round(time.monotonic() - started, 3))


def _abi(args):
    root, rid, output = args
    import abi
    path = Path(root) / output
    try:
        blob = path.read_bytes()
    except OSError as exc:
        return dict(recipe=rid, error=str(exc), sha=None)
    try:
        facts = abi.analyze_object(blob)
    except Exception as exc:
        return dict(recipe=rid, error=str(exc)[:300], sha=sha256(blob))
    return dict(recipe=rid, facts=facts, sha=sha256(blob))


def _debt(args):
    root, rel = args
    sys.path.insert(0, str(TOOLS / 'lint'))
    import debt_check as D
    text = (Path(root) / rel).read_bytes().decode('utf-8', 'surrogateescape')
    try:
        res = D.analyze(rel, text)
    except Exception as exc:
        return rel, [], str(exc)[:200]
    rows = []
    for key, scope in res['scopes'].items():
        for cls, n in scope['counts'].items():
            if n:
                rows.append((rel, scope['symbol'], scope['line'], cls, n))
    return rel, rows, None


def _init_worker(nice):
    if nice:
        try:
            os.nice(nice)
        except OSError:
            pass


# ---------------------------------------------------------------------------------------- the map

class CodeMap:
    def __init__(self, root, db, workers=8, nice=10, log=print, only=None):
        self.root = Path(root).resolve()
        self.only = only          # path prefix restricting parse/abi/debt work (tests, spot refreshes)
        self.db_path = Path(db) if db else self.root / 'build/codemap.db'
        self.workers, self.nice, self.log = workers, nice, log
        self.db = None

    def open(self, fresh=False):
        if fresh and self.db_path.exists():
            self.db_path.unlink()
        self.db_path.parent.mkdir(parents=True, exist_ok=True)
        new = not self.db_path.exists()
        self.db = sqlite3.connect(self.db_path)
        self.db.execute('PRAGMA journal_mode=WAL')
        self.db.execute('PRAGMA synchronous=NORMAL')
        if new:
            self.db.executescript(SCHEMA)
        return self.db

    def pool(self):
        return ProcessPoolExecutor(max_workers=self.workers, initializer=_init_worker, initargs=(self.nice,))

    def key(self, kind, name):
        row = self.db.execute('SELECT sha256 FROM fact_key WHERE kind=? AND key=?', (kind, name)).fetchone()
        return row[0] if row else None

    def set_key(self, kind, name, value):
        self.db.execute('INSERT OR REPLACE INTO fact_key VALUES (?,?,?)', (kind, name, value))

    # ---- source files ----
    def scan_sources(self):
        files = {}
        for top, kind in (('src', 'c'), ('include', 'h')):
            for dirpath, _, names in os.walk(self.root / top):
                for n in names:
                    if n.endswith(('.c', '.h')):
                        p = Path(dirpath) / n
                        files[p.relative_to(self.root).as_posix()] = sha256(p.read_bytes())
        return files

    # ---- build graph ----
    def load_graph(self, force=False):
        import affected as A
        index = self.root / 'build/.state/index.json'
        if not index.is_file():
            self.log('no build graph (build/.state/index.json); recipe/image tables left empty')
            return None
        stamp = sha256(index.read_bytes())
        if not force and self.key('graph', 'index.json') == stamp:
            return None
        t = time.monotonic()
        g = A.Graph(self.root)
        db = self.db
        for table in ('recipe', 'tu_dep', 'image', 'image_unit'):
            db.execute('DELETE FROM ' + table)
        linked = Counter()
        units = []
        for name, spec in g.images.items():
            data = json.loads(Path(spec['path']).read_text())
            kind = 'check' if '/check_' in name else 'image'
            db.execute('INSERT INTO image VALUES (?,?,?,?,?,?,?,?)', (name, spec['tag'], spec['output'], kind,
                       data.get('start'), data.get('size'), data.get('vma'), len(data['units'])))
            for i, u in enumerate(data['units']):
                linked[u['recipe']] += 1
                units.append((name, i, u['recipe'], u.get('func'), u.get('kind'), u.get('off'), u.get('size'),
                              u.get('vma'), json.dumps(u.get('rows', [])), int(bool(u.get('rebind')))))
        if g.slus_image:
            reg = g.registered[g.slus_image]
            db.execute('INSERT INTO image VALUES (?,?,?,?,?,?,?,?)', (g.slus_image, 'slus_slus_bin', reg['output'],
                       'slus', reg.get('start'), reg.get('size'), None, None))
            for rid, spec in g.recipes.items():
                if spec['_family'] == 'slus':
                    linked[rid] += 1
                    units.append((g.slus_image, None, rid, None, 'slus', None, None, None, '[]', 0))
        db.executemany('INSERT INTO image_unit VALUES (?,?,?,?,?,?,?,?,?,?)', units)
        rows, deps = [], []
        for rid, spec in g.recipes.items():
            family = spec['_family']
            kind = 'slus' if family == 'slus' else 'placement_copy' if spec.get('projection') else \
                'module' if 'module' in spec else 'row' if spec.get('wrapper', '').endswith('cc.sh') else 'asm'
            proj = spec.get('projection') or {}
            path = self.root / 'build/.state' / ('recipes' if family == 'overlay' else 'slus-recipes') / (rid + '.json')
            rows.append((rid, family, kind, spec.get('source') or spec.get('command'), g.own_source(spec),
                         proj.get('owner'), proj.get('home'), spec.get('output'), json.dumps(spec.get('args')),
                         sha256(path.read_bytes()), spec.get('declaration_context_sha256'), linked[rid]))
            closure = set()
            for d in spec.get('dependencies', ()):
                if d in g.generated:
                    closure.update(g.real(x) for x in g.generated[d]['inputs'])
                closure.add(g.real(d))
            if spec.get('projection'):
                closure.add(g.real(proj['owner']))
            for p in sorted(closure):
                if p.startswith(('src/', 'include/')):
                    deps.append((rid, p))
        db.executemany('INSERT INTO recipe VALUES (?,?,?,?,?,?,?,?,?,?,?,?)', rows)
        db.executemany('INSERT INTO tu_dep VALUES (?,?)', deps)
        self.set_key('graph', 'index.json', stamp)
        db.commit()
        self.log('graph: %d recipes, %d deps, %d images, %d units (%.1fs)' % (
            len(rows), len(deps), len(g.images) + bool(g.slus_image), len(units), time.monotonic() - t))
        return g

    # ---- names ----
    def load_names(self):
        path = self.root / 'config/names.tsv'
        if not path.is_file():
            return False
        stamp = sha256(path.read_bytes())
        if self.key('names', 'config/names.tsv') == stamp:
            return False
        self.db.execute('DELETE FROM name')
        rows = []
        for line in path.read_text().splitlines():
            if not line or line.startswith('#'):
                continue
            f = line.split('\t')
            if len(f) >= 3:
                rows.append((f[0], f[1], f[2], f[3] if len(f) > 3 else ''))
        self.db.executemany('INSERT INTO name VALUES (?,?,?,?)', rows)
        self.set_key('names', 'config/names.tsv', stamp)
        self.db.commit()
        self.log('names: %d rows' % len(rows))
        return True

    # ---- clang facts ----
    def closure_sha(self, rel, headers, files):
        parts = [rel + ':' + files.get(rel, '-')] + [h + ':' + files.get(h, '-') for h in headers]
        return sha256('\n'.join(parts).encode())

    def refresh_tus(self, files, force=False):
        db = self.db
        stored = {r[0]: (r[1], json.loads(r[2] or '[]')) for r in
                  db.execute('SELECT path, closure_sha256, headers FROM tu')}
        units = sorted(p for p in files if p.endswith('.c') and (not self.only or p.startswith(self.only)))
        todo = []
        for rel in units:
            old = stored.get(rel)
            if force or old is None or old[0] != self.closure_sha(rel, old[1], files):
                todo.append(rel)
        gone = sorted(p for p in set(stored) - set(units) if p not in files)
        for rel in gone + todo:
            self._drop_tu(rel)
        self.log('clang: %d of %d TUs to parse (%d removed)' % (len(todo), len(units), len(gone)))
        t = time.monotonic()
        recipes = Counter(r[0] for r in db.execute('SELECT physical FROM recipe'))
        done = 0
        with self.pool() as ex:
            for res in ex.map(_parse_tu, [(str(self.root), rel) for rel in todo], chunksize=8):
                self._store_tu(res, files, recipes)
                done += 1
                if done % 1000 == 0:
                    db.commit()
                    self.log('  parsed %d/%d (%.0fs)' % (done, len(todo), time.monotonic() - t))
        db.execute('DELETE FROM decl WHERE seen <= 0')
        db.commit()
        self.log('clang: parsed %d TUs in %.1fs' % (len(todo), time.monotonic() - t))
        return len(todo)

    def _drop_tu(self, rel):
        """Forget one TU's facts.  Its own file's sites go; every header site it saw loses one `seen`
        (sites no TU sees any more are deleted after the refresh, so a declaration removed from a
        header disappears once every consumer has been re-parsed)."""
        db = self.db
        row = db.execute('SELECT headers FROM tu WHERE path=?', (rel,)).fetchone()
        headers = json.loads(row[0] or '[]') if row else []
        db.execute('DELETE FROM tu WHERE path=?', (rel,))
        db.execute('DELETE FROM call_site WHERE tu=?', (rel,))
        db.execute('DELETE FROM defn WHERE tu=?', (rel,))
        db.execute('DELETE FROM decl WHERE file=?', (rel,))
        for i in range(0, len(headers), 500):
            chunk = headers[i:i + 500]
            db.execute('UPDATE decl SET seen=seen-1 WHERE file IN (%s)' % ','.join('?' * len(chunk)), chunk)
        db.execute('UPDATE decl SET tu=NULL WHERE tu=?', (rel,))

    def _store_tu(self, res, files, recipes):
        db = self.db
        rel = res['path']
        for d in res['decls']:
            canon = canonical_site(d)
            row = (d['name'], d['kind'], d['file'], d['line'], d['col'], d['signature'], d.get('composite'),
                   d['canonical'], norm_sig(d['signature']), canon, d['ret'], json.dumps(d['params']),
                   d['nparams'], int(d['variadic']), int(d['has_proto']), d['storage'], int(d['local']), rel)
            cur = db.execute('UPDATE decl SET seen=seen+1, tu=COALESCE(tu, ?) WHERE file=? AND line=? AND col=? '
                             'AND name=? AND signature=?', (rel, d['file'], d['line'], d['col'], d['name'],
                                                            d['signature']))
            if cur.rowcount == 0:
                db.execute('INSERT INTO decl(name,kind,file,line,col,signature,composite,canonical,norm,canon_norm,'
                           'ret,params,nparams,variadic,has_proto,storage,local,tu,seen) '
                           'VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,1)', row)
            if d['kind'] == 'def' and d['file'] == rel:
                db.execute('INSERT INTO defn VALUES (?,?,?,?,?,?,?,?)', (d['name'], d['file'], d['line'],
                           d['signature'], d['canonical'], norm_sig(d['signature']), canon, rel))
        # Calls inside header inline functions would repeat once per including TU: keep the TU's own.
        db.executemany('INSERT INTO call_site VALUES (?,?,?,?,?,?,?,?,?,?,?)', [
            (rel, c['caller'], c['callee'], c['file'], c['line'], c['col'], c['nargs'], json.dumps(c['arg_types']),
             json.dumps(c['param_types']), c['callee_type'], c['ret_use']) for c in res['calls'] if c['file'] == rel])
        db.execute('INSERT OR REPLACE INTO tu VALUES (?,?,?,?,?,?,?,?,?)', (
            rel, files.get(rel), self.closure_sha(rel, res['headers'], files), json.dumps(res['headers']),
            recipes.get(rel, 0), len(res['decls']), len(res['calls']), res['error'], res['seconds']))

    # ---- retail ABI ----
    def refresh_abi(self, force=False):
        db = self.db
        names = dict(db.execute('SELECT symbol, name FROM name'))
        todo, keep = [], set()
        for rid, output, physical in db.execute("SELECT id, output, physical FROM recipe WHERE linked > 0 "
                                                "AND kind != 'asm' AND output IS NOT NULL").fetchall():
            if self.only and not (physical or '').startswith(self.only):
                continue
            path = self.root / output
            if not path.is_file():
                continue
            keep.add(rid)
            proof = path.with_suffix('.proof.json')
            stamp = None
            if proof.is_file():
                try:
                    stamp = json.loads(proof.read_text()).get('object_sha256')
                except ValueError:
                    stamp = None
            if force or stamp is None or self.key('obj', rid) != stamp:
                todo.append((rid, output))
        stale = {r[0] for r in db.execute("SELECT key FROM fact_key WHERE kind='obj'")} - keep
        for rid in [r for r, _ in todo] + sorted(stale):
            db.execute('DELETE FROM retail_fn WHERE recipe=?', (rid,))
            db.execute('DELETE FROM retail_call WHERE recipe=?', (rid,))
            db.execute("DELETE FROM fact_key WHERE kind='obj' AND key=?", (rid,))
        self.log('abi: %d of %d linked objects to analyse' % (len(todo), len(keep)))
        t = time.monotonic()
        with self.pool() as ex:
            for res in ex.map(_abi, [(str(self.root), rid, out) for rid, out in todo], chunksize=16):
                rid = res['recipe']
                if 'facts' in res:
                    for f in res['facts']['functions']:
                        db.execute('INSERT INTO retail_fn VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)', (
                            rid, f['name'], names.get(f['name'], f['name']), f.get('section'), f.get('size'),
                            ','.join(f.get('args_read', [])), ','.join(f.get('args_at_first_call', [])),
                            ','.join(map(str, f.get('stack_args_read', []))), ','.join(f.get('home_stores', [])),
                            ','.join(f.get('v0_at_return', [])), int(bool(f.get('v0_all_paths'))),
                            ','.join(f.get('return_ext', [])), f.get('calls_out'), f.get('sibcalls'),
                            f.get('indirect_jumps'), f.get('indirect_calls'), f.get('returns'),
                            int(bool(f.get('global'))), f.get('error')))
                    db.executemany('INSERT INTO retail_call VALUES (?,?,?,?,?,?,?,?,?,?,?)', [
                        (rid, c['caller'], c['offset'], c['callee'], names.get(c['callee'], c['callee']), c['kind'],
                         c['args']['a0'], c['args']['a1'], c['args']['a2'], c['args']['a3'], c['v0_use'])
                        for c in res['facts']['calls']])
                if res.get('sha'):
                    self.set_key('obj', rid, res['sha'])
        db.commit()
        self.log('abi: analysed %d objects in %.1fs' % (len(todo), time.monotonic() - t))
        return len(todo)

    # ---- debt ----
    def refresh_debt(self, files, force=False):
        db = self.db
        todo = [p for p, s in sorted(files.items()) if (force or self.key('debt', p) != s)
                and (not self.only or p.startswith(self.only))]
        gone = {r[0] for r in db.execute("SELECT key FROM fact_key WHERE kind='debt'")} - set(files)
        for p in todo + sorted(gone):
            db.execute('DELETE FROM debt_site WHERE file=?', (p,))
            db.execute("DELETE FROM fact_key WHERE kind='debt' AND key=?", (p,))
        t = time.monotonic()
        with self.pool() as ex:
            for rel, rows, error in ex.map(_debt, [(str(self.root), p) for p in todo], chunksize=32):
                db.executemany('INSERT INTO debt_site VALUES (?,?,?,?,?)', rows)
                if error is None:
                    self.set_key('debt', rel, files[rel])
        db.commit()
        self.log('debt: %d files in %.1fs' % (len(todo), time.monotonic() - t))

    # ---- derived ----
    def derive(self):
        db = self.db
        db.execute('DELETE FROM function')
        symbol_of = {}
        for address, symbol, name in db.execute("SELECT address, symbol, name FROM name WHERE symbol LIKE 'func_%'"):
            symbol_of.setdefault(name, (symbol, address))
        agg = defaultdict(lambda: dict(defs=set(), protos=0, local=0, sigs=set(), sites=0, kinds=set()))
        for name, kind, norm, local in db.execute('SELECT name, kind, norm, local FROM decl'):
            a = agg[name]
            a['sites'] += 1
            a['kinds'].add(kind)
            a['sigs'].add(norm)
            if kind == 'proto':
                a['protos'] += 1
                a['local'] += local
        for name, file in db.execute('SELECT name, file FROM defn'):
            agg[name]['defs'].add(file)
        calls = Counter(r[0] for r in db.execute('SELECT callee FROM call_site'))
        rows = []
        for name, a in agg.items():
            sym, addr = symbol_of.get(name, (None, None))
            kind = 'data' if a['kinds'] == {'data'} else 'function'
            rows.append((name, sym, addr, len(a['defs']), a['protos'], a['local'], len(a['sigs']), a['sites'],
                         calls.get(name, 0), kind))
        db.executemany('INSERT INTO function VALUES (?,?,?,?,?,?,?,?,?,?)', rows)
        db.commit()

    def record_sources(self, files):
        db = self.db
        db.execute('DELETE FROM source_file')
        db.executemany('INSERT INTO source_file VALUES (?,?,?)',
                       [(p, s, 'c' if p.endswith('.c') else 'h') for p, s in files.items()])
        db.execute("INSERT OR REPLACE INTO meta VALUES ('refreshed_at', ?)", (time.strftime('%Y-%m-%dT%H:%M:%S'),))
        head = self.root / 'SCRATCH_HEAD'
        if head.is_file():
            db.execute("INSERT OR REPLACE INTO meta VALUES ('scratch_head', ?)", (head.read_text().strip(),))
        db.commit()

    def refresh(self, force=False):
        t = time.monotonic()
        timings = {}
        files = self.scan_sources()
        timings['scan'] = time.monotonic() - t
        s = time.monotonic(); self.load_graph(force); timings['graph'] = time.monotonic() - s
        s = time.monotonic(); self.load_names(); timings['names'] = time.monotonic() - s
        # A changed extractor invalidates its facts: key each phase by its tool sources too.
        tools = {'clang': [HERE.parent / 'ast_facts.py'], 'abi': [HERE.parent / 'abi.py', TOOLS / 'build/affected.py'],
                 'debt': [TOOLS / 'lint/debt_check.py']}
        stale = {}
        for phase, paths in tools.items():
            stamp = sha256(b''.join(p.read_bytes() for p in paths if p.is_file()))
            stale[phase] = force or self.key('tool', phase) != stamp
            tools[phase] = stamp
        s = time.monotonic(); parsed = self.refresh_tus(files, stale['clang']); timings['clang'] = time.monotonic() - s
        s = time.monotonic(); objects = self.refresh_abi(stale['abi']); timings['abi'] = time.monotonic() - s
        s = time.monotonic(); self.refresh_debt(files, stale['debt']); timings['debt'] = time.monotonic() - s
        for phase, stamp in tools.items():
            self.set_key('tool', phase, stamp)
        s = time.monotonic(); self.derive(); self.record_sources(files); timings['derive'] = time.monotonic() - s
        timings = {k: round(v, 1) for k, v in timings.items()}
        timings['total'] = round(time.monotonic() - t, 1)
        self.db.execute("INSERT OR REPLACE INTO meta VALUES ('last_refresh', ?)",
                        (json.dumps(dict(timings, parsed=parsed, objects=objects)),))
        self.db.commit()
        self.log('refresh: ' + json.dumps(dict(timings, parsed=parsed, objects=objects)))
        return timings

    def check(self):
        files = self.scan_sources()
        stored = dict(self.db.execute('SELECT path, sha256 FROM source_file'))
        changed = sorted(p for p in files if stored.get(p) != files[p])
        removed = sorted(set(stored) - set(files))
        index = self.root / 'build/.state/index.json'
        graph_stale = index.is_file() and self.key('graph', 'index.json') != sha256(index.read_bytes())
        names = self.root / 'config/names.tsv'
        names_stale = names.is_file() and self.key('names', 'config/names.tsv') != sha256(names.read_bytes())
        return dict(fresh=not (changed or removed or graph_stale or names_stale), changed=changed[:50],
                    changed_count=len(changed), removed=removed[:50], graph_stale=graph_stale,
                    names_stale=names_stale)


# ------------------------------------------------------------------------------------------ queries

def q_decls(db, name):
    rows = db.execute('SELECT norm, kind, file, line, local, seen, signature FROM decl WHERE name=? '
                      'ORDER BY norm, file, line', (name,)).fetchall()
    by = defaultdict(list)
    for norm, kind, file, line, local, seen, sig in rows:
        by[norm].append(dict(kind=kind, file=file, line=line, local=bool(local), seen=seen, spelled=sig))
    defs = {r[0] for r in db.execute('SELECT norm FROM defn WHERE name=?', (name,))}
    sym = db.execute("SELECT symbol FROM name WHERE name=? AND symbol LIKE 'func_%'", (name,)).fetchone()
    abi = db.execute('SELECT recipe, args_read, args_at_first_call, stack_args_read, v0_at_return, v0_all_paths, '
                     'return_ext FROM retail_fn WHERE name=?', (name,)).fetchall()
    return dict(name=name, symbol=sym[0] if sym else None, distinct=len(by), conflict=len(by) > 1,
                signatures=[dict(signature=k, sites=len(v), matches_definition=k in defs, where=v[:40])
                            for k, v in sorted(by.items(), key=lambda kv: -len(kv[1]))],
                retail=[dict(zip(('recipe', 'args_read', 'args_at_first_call', 'stack_args', 'v0_at_return',
                                  'v0_all_paths', 'return_ext'), r)) for r in abi[:20]],
                retail_placements=len(abi))


def q_callers(db, name):
    rows = db.execute('SELECT tu, caller, file, line, nargs, arg_types, param_types, callee_type, ret_use '
                      'FROM call_site WHERE callee=? ORDER BY file, line', (name,)).fetchall()
    retail = db.execute('SELECT r.recipe, r.caller, n.name, r.offset, r.a0, r.a1, r.a2, r.a3, r.v0_use '
                        'FROM retail_call r LEFT JOIN name n ON n.symbol=r.caller WHERE r.callee_name=?',
                        (name,)).fetchall()
    use = Counter(r[-1] for r in retail)
    return dict(name=name, c_sites=[dict(zip(('tu', 'caller', 'file', 'line', 'nargs', 'arg_types', 'param_types',
                                               'callee_type', 'ret_use'), r)) for r in rows],
                ret_use=dict(Counter(r[-1] for r in rows)), retail_sites=len(retail), retail_v0_use=dict(use),
                retail=[dict(zip(('recipe', 'caller_symbol', 'caller', 'offset', 'a0', 'a1', 'a2', 'a3', 'v0_use'), r))
                        for r in retail[:40]])


def q_affected(db, paths):
    recipes = set()
    for p in paths:
        recipes |= {r[0] for r in db.execute('SELECT recipe FROM tu_dep WHERE path=?', (p,))}
        recipes |= {r[0] for r in db.execute('SELECT id FROM recipe WHERE physical=? OR owner=?', (p, p))}
    kinds = Counter()
    for rid in recipes:
        row = db.execute('SELECT kind FROM recipe WHERE id=?', (rid,)).fetchone()
        kinds[row[0] if row else '?'] += 1
    images = set()
    for rid in recipes:
        images |= {r[0] for r in db.execute('SELECT image FROM image_unit WHERE recipe=?', (rid,))}
    return dict(paths=paths, recipes=len(recipes), kinds=dict(kinds), images=len(images),
                image_names=sorted(images)[:60], recipe_ids=sorted(recipes)[:60])


def classify(sigs):
    """Conflict kind over normalised signatures 'ret(params)' (the retro census vocabulary)."""
    parsed = []
    for s in sigs:
        i = s.rfind('(', 0, len(s) - 1) if s.endswith(')') else -1
        depth, cut = 0, None
        for j in range(len(s) - 1, -1, -1):
            if s[j] == ')':
                depth += 1
            elif s[j] == '(':
                depth -= 1
                if depth == 0:
                    cut = j
                    break
        ret, params = (s[:cut], s[cut + 1:-1]) if cut is not None else (s, '')
        parsed.append((ret, params))
    rets = {r for r, _ in parsed}
    pars = {p for _, p in parsed}
    kinds = set()
    scalars = {'s8', 's16', 's32', 'u8', 'u16', 'u32', 'int', 'short', 'char', 'long', 'unsigned', 'signed',
               'unsignedint', 'unsignedchar', 'unsignedshort', 'signedchar'}
    if len(rets) > 1:
        kinds.add('ret_width' if all(r.replace(' ', '') in scalars for r in rets) else 'ret_other')
    if len(pars) > 1:
        empties = '' in pars
        arities = {len(p.split(',')) if p not in ('', 'void') else 0 for p in pars if p != ''}
        if len(arities) > 1:
            kinds.add('arity')
        elif not empties:
            kinds.add('param_type')
        else:
            kinds.add('empty_vs_typed')
    if len(kinds) > 1:
        return 'mixed:' + '+'.join(sorted(kinds))
    return kinds.pop() if kinds else 'none'


def q_families(db, limit=40, kind=None, key='canon_norm'):
    rows = db.execute("SELECT name, %s, file, kind FROM decl WHERE kind IN ('proto','def')" % key).fetchall()
    by = defaultdict(lambda: defaultdict(set))
    for name, norm, file, k in rows:
        by[name][norm].add(file)
    out = []
    for name, sigs in by.items():
        typed = {s: f for s, f in sigs.items() if not s.endswith('()')}
        if len(sigs) < 2:
            continue
        sites = sum(len(f) for f in sigs.values())
        k = classify(typed) if len(typed) >= 2 else 'empty_vs_typed_only'
        if kind and not k.startswith(kind):
            continue
        out.append(dict(name=name, signatures=len(sigs), sites=sites, kind=k,
                        defs=db.execute('SELECT COUNT(*) FROM defn WHERE name=?', (name,)).fetchone()[0]))
    out.sort(key=lambda r: (-r['sites'], -r['signatures'], r['name']))
    return dict(families=len(out), kinds=dict(Counter(r['kind'] for r in out).most_common()), top=out[:limit])


def q_census(db, out=None, key='norm'):
    """Tree-wide declaration-conflict census (the retro's decl_conflicts.tsv, from clang facts).

    Signatures per name over unique (file, signature) sites of prototypes and definitions in src/ and
    include/; empty-parens prototypes count as a signature but not for the conflict kind."""
    if key not in ('norm', 'canon_norm'):
        raise ValueError('census key is norm (as written) or canon_norm (type level)')
    rows = db.execute("SELECT name, %s, file, kind, local FROM decl WHERE kind IN ('proto','def')" % key).fetchall()
    by = defaultdict(lambda: defaultdict(set))
    protos, defs_by = set(), defaultdict(set)
    for name, norm, file, kind, local in rows:
        by[name][norm].add(file + (' (def)' if kind == 'def' else ''))
        if kind == 'proto':
            protos.add(name)
        else:
            defs_by[name].add(norm)
    dist, kinds, table = Counter(), Counter(), []
    def_disagree = multi_def = 0
    for name, sigs in by.items():
        dist[len(sigs)] += 1
        if len(sigs) < 2:
            continue
        typed = [s for s in sigs if not s.endswith('()')]
        kind = classify(typed) if len(typed) >= 2 else 'empty_vs_typed_only'
        kinds[kind] += 1
        d = defs_by.get(name, set())
        multi_def += len(d) > 1
        def_disagree += bool(d) and any(s not in d for s in typed)
        table.append((name, len(sigs), kind, sum(len(f) for f in sigs.values()), len(d), sigs))
    table.sort(key=lambda r: (-r[1], -r[3], r[0]))
    if out:
        with open(out, 'w') as fh:
            fh.write('name\tdistinct_sigs\tkind\tsites\tdefinitions\tsignatures\n')
            for name, n, kind, sites, nd, sigs in table:
                text = ' || '.join('%s @%d: %s' % (s, len(f), '; '.join(sorted(f)[:4])) for s, f in sigs.items())
                fh.write('%s\t%d\t%s\t%d\t%d\t%s\n' % (name, n, kind, sites, nd, text))
    return dict(key=key, names_with_prototypes=len(protos), names_with_definitions=len(defs_by),
                distinct_signature_distribution=dict(sorted(dist.items())),
                names_with_two_or_more=sum(v for k, v in dist.items() if k >= 2), kinds=dict(kinds.most_common()),
                definitions_disagree_across_copies=multi_def, prototype_disagrees_with_definition=def_disagree,
                top=[dict(name=r[0], signatures=r[1], kind=r[2], sites=r[3], defs=r[4]) for r in table[:15]])


def q_voidret(db, limit=40):
    """C definitions returning void whose retail callers use v0 after the call (the voidret class),
    and non-void definitions whose retail body never writes v0 on some path."""
    used = ('raw', 'ext_s16', 'ext_s8', 'ext_u16', 'ext_u8', 'store8', 'store16', 'store32', 'test')
    rows = db.execute(
        "SELECT d.name, d.file, COUNT(*) AS sites, SUM(c.v0_use IN (%s)) AS v0_used "
        "FROM defn d JOIN retail_call c ON c.callee_name = d.name "
        "WHERE d.norm LIKE 'void(%%' GROUP BY d.name, d.file HAVING v0_used > 0 ORDER BY v0_used DESC"
        % ','.join('?' * len(used)), used).fetchall()
    void_read = [dict(name=r[0], file=r[1], retail_sites=r[2], v0_used=r[3]) for r in rows]
    rows = db.execute(
        "SELECT DISTINCT d.name, d.file, f.v0_at_return FROM defn d JOIN retail_fn f ON f.name = d.name "
        "WHERE d.norm NOT LIKE 'void(%' AND f.v0_all_paths = 0 AND f.v0_at_return LIKE '%none%'").fetchall()
    value_missing = [dict(name=r[0], file=r[1], v0_at_return=r[2]) for r in rows]
    return dict(void_but_v0_read=len(void_read), void_examples=void_read[:limit],
                nonvoid_without_v0_on_some_path=len(value_missing), nonvoid_examples=value_missing[:limit])


def q_abi(db, name):
    rows = db.execute('SELECT f.recipe, r.kind, r.physical, f.args_read, f.args_at_first_call, f.stack_args_read, '
                      'f.home_stores, f.v0_at_return, f.v0_all_paths, f.return_ext, f.calls_out '
                      'FROM retail_fn f LEFT JOIN recipe r ON r.id=f.recipe WHERE f.name=? OR f.symbol=?',
                      (name, name)).fetchall()
    keys = ('recipe', 'kind', 'source', 'args_read', 'args_at_first_call', 'stack_args', 'home_stores',
            'v0_at_return', 'v0_all_paths', 'return_ext', 'calls_out')
    return dict(name=name, placements=len(rows), facts=[dict(zip(keys, r)) for r in rows[:40]])


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('mode', choices=('build', 'refresh', 'check', 'query'))
    ap.add_argument('args', nargs='*')
    ap.add_argument('--root', type=Path, default=DEFAULT_ROOT)
    ap.add_argument('--db', type=Path)
    ap.add_argument('--workers', type=int, default=8)
    ap.add_argument('--nice', type=int, default=10)
    ap.add_argument('--limit', type=int, default=40)
    ap.add_argument('--kind', help='families: only this conflict kind prefix')
    ap.add_argument('--only', help='build/refresh: restrict parse/abi/debt work to this path prefix')
    ap.add_argument('--type-level', action='store_true',
                    help='census/families: compare desugared types (typedef/tag spellings are not conflicts)')
    a = ap.parse_intermixed_args(argv)
    if not 1 <= a.workers <= 8:
        ap.error('between 1 and 8 workers on this host')
    cm = CodeMap(a.root, a.db, a.workers, a.nice, log=lambda m: print(m, file=sys.stderr, flush=True),
                 only=a.only)
    if a.mode in ('build', 'refresh'):
        cm.open(fresh=a.mode == 'build')
        cm.refresh(force=a.mode == 'build')
        return 0
    if not cm.db_path.exists():
        print('no codemap at %s (run codemap.py build)' % cm.db_path, file=sys.stderr)
        return 2
    db = cm.open()
    if a.mode == 'check':
        res = cm.check()
        print(json.dumps(res, indent=1))
        return 0 if res['fresh'] else 1
    if not a.args:
        ap.error('query needs: decls NAME | callers NAME | affected PATH... | families | abi NAME | sql TEXT')
    what, rest = a.args[0], a.args[1:]
    if what == 'decls':
        res = q_decls(db, rest[0])
    elif what == 'callers':
        res = q_callers(db, rest[0])
    elif what == 'affected':
        res = q_affected(db, rest)
    elif what == 'families':
        res = q_families(db, a.limit, a.kind, 'canon_norm' if a.type_level else 'norm')
    elif what == 'abi':
        res = q_abi(db, rest[0])
    elif what == 'voidret':
        res = q_voidret(db, a.limit)
    elif what == 'census':
        res = q_census(db, rest[0] if rest else None, 'canon_norm' if a.type_level else 'norm')
    elif what == 'sql':
        cur = db.execute(rest[0])
        cols = [c[0] for c in cur.description or ()]
        res = [dict(zip(cols, r)) for r in cur.fetchmany(a.limit)]
    else:
        ap.error('unknown query ' + what)
    print(json.dumps(res, indent=1, default=str))
    return 0


if __name__ == '__main__':
    sys.exit(main())
