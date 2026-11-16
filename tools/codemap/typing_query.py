"""Queries and loaders over codemap.db typing facts (tools/codemap/typing_facts.py) and runtime/flow evidence.

Kept apart from the extractor so that editing a query or a loader does not invalidate every TU's typing stamp.
"""
from __future__ import annotations

import collections
import csv
import gzip
import hashlib
import json
from pathlib import Path
import re
import time

from typing_facts import CAST_COLS, ensure_schema


# ------------------------------------------------------------------------------------------- consumers

def cast_rows(db, folder='src'):
    """(rows keyed like cast_census.main, errors) for the files under `folder` (the census input, no clang)."""
    rows, errors = {}, []
    prefix = folder.rstrip('/') + '/'
    for (row,) in db.execute('SELECT row FROM cast_site WHERE file LIKE ? ORDER BY tu', (prefix + '%',)):
        r = json.loads(row)
        rows.setdefault((r['file'], r['start'], r.get('macro', 0), r.get('line'), tuple(r.get('starts', ()))), r)
    for tu, error in db.execute('SELECT tu, error FROM typing_tu WHERE error IS NOT NULL AND error != ""'):
        errors.append((tu, error))
    return rows, errors


def flow_blob(db, tu):
    row = db.execute('SELECT blob FROM flow_tu WHERE tu=?', (tu,)).fetchone()
    return row[0] if row else None


# ------------------------------------------------------------------------------------------- loaders

def file_stamp(paths):
    h = hashlib.sha256()
    for p in paths:
        if p.is_file():
            st = p.stat()
            h.update(('%s:%d:%d\n' % (p.name, st.st_size, st.st_mtime_ns)).encode())
    return h.hexdigest()


# Runtime identity: the campaign names functions by the (file, name) of the revision it was taken at.  rt_fn_map binds
# each such pair to the function's retail ADDRESS and images and to its definition in the current tree.  Kept out of
# typing_facts.SCHEMA (that file is part of every TU's typing stamp).
RT_MAP_SCHEMA = '''
CREATE TABLE IF NOT EXISTS rt_fn_map(file TEXT, function TEXT, address TEXT, images TEXT, cur_file TEXT,
    cur_function TEXT, how TEXT, PRIMARY KEY(file, function));
'''
ADDR_NAME = re.compile(r'^(?:func|w)_([0-9A-Fa-f]{8})$')


def old_name_addresses(names_text):
    """config/names.tsv text of the runtime's revision -> {name: {0x-address}} (function rows only: old name func_)."""
    out = collections.defaultdict(set)
    for line in names_text.splitlines():
        if not line.strip() or line.startswith('#'):
            continue
        cols = line.split('\t')
        if len(cols) >= 3 and cols[1].startswith('func_'):
            out[cols[2]].add(cols[0].lower())
    return out


def git_runtime_inputs(git_dir, rev, to_rev):
    """(names.tsv text at rev, {old path: new path or None}) from `git -C git_dir` (read-only)."""
    import subprocess
    git = ['git', '-C', str(git_dir)]
    names = subprocess.run(git + ['show', '%s:config/names.tsv' % rev], capture_output=True, text=True,
                           check=True).stdout
    diff = subprocess.run(git + ['diff', '-M', '-l100000', '--name-status', rev, to_rev, '--', 'src', 'include'],
                          capture_output=True, text=True, check=True).stdout
    renames = {}
    for line in diff.splitlines():
        p = line.split('\t')
        if p[0].startswith('R') and len(p) == 3:
            renames[p[1]] = p[2]
        elif p[0] == 'D' and len(p) == 2:
            renames[p[1]] = None
    return names, renames


def map_runtime_identity(db, pairs, old_names=None, renames=None):
    """Bind runtime (file, function) pairs to address, images and current definition.

    A pair's address comes from the runtime revision's names.tsv (new name -> address; func_/w_<ADDR> names carry
    it), so later renames follow the address, never the spelling.  The current function is the retail function at
    that address (codemap retail_fn + recipe): the one compiled from the pair's file (followed through git renames),
    else the only name at that address.  A pair with no address (library or developer names) binds by name.
    Candidates at the address with different names and no file match are `ambiguous` and bind nothing.

    Returns {(file, function): dict(address, images, cur_file, cur_function, how)}."""
    old_names = old_names if old_names is not None else {}
    renames = renames or {}
    by_addr = collections.defaultdict(set)      # address -> {(name, source)}
    recipes = collections.defaultdict(set)      # (address, name, source) -> {recipe}
    by_name = collections.defaultdict(set)
    for sym, name, src, recipe in db.execute('SELECT f.symbol, f.name, r.source, f.recipe FROM retail_fn f '
                                             'JOIN recipe r ON r.id = f.recipe'):
        m = ADDR_NAME.match(sym or '')
        if m:
            addr = '0x' + m.group(1).lower()
            by_addr[addr].add((name, src))
            recipes[(addr, name, src)].add(recipe)
        by_name[name].add((name, src))
    defs = collections.defaultdict(set)
    for name, file in db.execute('SELECT name, file FROM defn'):
        defs[name].add(file)
    images = collections.defaultdict(set)
    for image, recipe in db.execute('SELECT image, recipe FROM image_unit'):
        images[recipe].add(image)
    out = {}
    for file, fn in sorted(set(pairs)):
        now = renames.get(file, file)
        addrs = set(old_names.get(fn, ()))
        m = ADDR_NAME.match(fn)
        if m:
            addrs.add('0x' + m.group(1).lower())
        cands = set()
        for a in addrs:
            cands |= {(a,) + c for c in by_addr.get(a, ())}
        if not addrs:
            cands = {(None,) + c for c in by_name.get(fn, ())}
        same = sorted(c for c in cands if c[2] == now)
        pick, how = None, None
        if same and len({c[1] for c in same}) == 1:
            pick, how = same[0], ('address+file' if addrs else 'name+file')
        elif cands and len({c[1] for c in cands}) == 1:
            name = next(iter(cands))[1]
            files = sorted({c[2] for c in cands} & defs.get(name, set())) or sorted({c[2] for c in cands})
            pick = next(c for c in sorted(cands, key=lambda c: (c[0] or '', c[2])) if c[2] == files[0])
            how = 'address' if addrs else 'name'
        elif not cands and fn in defs and (now in defs[fn] or len(defs[fn]) == 1):
            pick, how = (None, fn, now if now in defs[fn] else next(iter(defs[fn]))), 'definition_name'
        else:
            how = 'ambiguous' if cands else 'unmapped'
        if pick is None:
            out[(file, fn)] = dict(address=','.join(sorted(addrs)), images='', cur_file=None, cur_function=None,
                                   how=how)
            continue
        addr, name, src = pick
        imgs = set()
        if addr:
            for r in recipes.get((addr, name, src), ()):
                imgs |= images.get(r, set())
        out[(file, fn)] = dict(address=addr or '', images=','.join(sorted(imgs)), cur_file=src, cur_function=name,
                               how=how)
    return out


def runtime_pairs(db):
    """Every (file, function) the loaded runtime names: fn_args rows, kind creators and body receivers."""
    pairs = set(db.execute('SELECT DISTINCT file, function FROM rt_fn_arg'))
    for cf, cfn, recv in db.execute('SELECT creator_file, creator_function, body_receivers FROM rt_kind'):
        if cf and cfn:
            pairs.add((cf, cfn))
        for f, fn in json.loads(recv or '[]'):
            pairs.add((f, fn))
    return pairs


def load_runtime_map(db, old_names=None, renames=None, log=print):
    """Fill rt_fn_map from the loaded rt_* tables.  Returns {how: count, 'renamed': n}."""
    db.executescript(RT_MAP_SCHEMA)
    db.execute('DELETE FROM rt_fn_map')
    got = map_runtime_identity(db, runtime_pairs(db), old_names, renames)
    db.executemany('INSERT INTO rt_fn_map VALUES (?,?,?,?,?,?,?)',
                   [(f, fn, v['address'], v['images'], v['cur_file'], v['cur_function'], v['how'])
                    for (f, fn), v in sorted(got.items())])
    db.commit()
    counts = dict(collections.Counter(v['how'] for v in got.values()))
    counts['renamed'] = sum(1 for (f, fn), v in got.items() if v['cur_function'] and v['cur_function'] != fn)
    log('runtime identity: %s' % json.dumps(counts, sort_keys=True))
    return counts


def load_runtime(db, rt_dir, source_rev=None, log=print, git_dir=None, to_rev='HEAD'):
    """rtti_merge.py output DIR -> rt_* tables (replaced whole).  Returns row counts.

    With source_rev and git_dir (a repository holding that revision; only read), rt_fn_map binds every runtime
    (file, function) through that revision's names.tsv and the git file renames up to to_rev; without them pairs
    bind by name (a runtime taken at the current tree)."""
    rt_dir = Path(rt_dir)
    ensure_schema(db)
    db.executescript(RT_MAP_SCHEMA)
    for table in ('rt_fn_arg', 'rt_kind', 'rt_pointee', 'rt_callsite', 'rt_meta', 'rt_fn_map'):
        db.execute('DELETE FROM ' + table)
    counts = {}
    fa = rt_dir / 'fn_args.tsv'
    if fa.is_file():
        rows = []
        with fa.open() as fh:
            for r in csv.DictReader(fh, delimiter='\t'):
                rows.append((r['file'], r['function'], int(r['arg']), int(r['calls'] or 0),
                             int(r['nparams']) if r['nparams'] else None, r['param_type'], int(r['observations'] or 0),
                             int(r['heap_kinds'] or 0), r['values']))
        db.executemany('INSERT INTO rt_fn_arg VALUES (?,?,?,?,?,?,?,?,?)', rows)
        counts['rt_fn_arg'] = len(rows)
    kj = rt_dir / 'kinds_rt.json'
    if kj.is_file():
        rows = []
        for k in json.loads(kj.read_text()).get('kinds', ()):
            c = k.get('creator') or {}
            doc = {x: k.get(x) for x in ('flags', 'allocator', 'through_wrappers', 'generations')}
            text = json.dumps(doc)
            while len(text) > 20000 and doc['generations']:
                # keep the document valid JSON (flags and allocator are read back): drop generations from the end
                doc['generations'] = doc['generations'][:len(doc['generations']) // 2]
                text = json.dumps(doc)
            rows.append((k['id'], k.get('role'), c.get('file'), c.get('function'), k.get('size'), k.get('allocs'),
                         json.dumps([(b['file'], b['function']) for b in k.get('body_receivers', ())]), text))
        db.executemany('INSERT INTO rt_kind VALUES (?,?,?,?,?,?,?,?)', rows)
        counts['rt_kind'] = len(rows)
    pt = rt_dir / 'pointees.tsv.gz'
    if pt.is_file():
        rows = []
        with gzip.open(pt, 'rt') as fh:
            for r in csv.DictReader(fh, delimiter='\t'):
                rows.append((r['file'], int(r['line'] or 0), r['function'], r['access'], r['target'], r['offset'],
                             r['value_class'], r['value_target'], r['value_offset'], int(r['count'])))
        db.executemany('INSERT INTO rt_pointee VALUES (?,?,?,?,?,?,?,?,?,?)', rows)
        counts['rt_pointee'] = len(rows)
    cs = rt_dir / 'callsite_args.tsv.gz'
    if cs.is_file():
        rows = []
        with gzip.open(cs, 'rt') as fh:
            for r in csv.DictReader(fh, delimiter='\t'):
                rows.append((r['callee_file'], r['callee'], int(r['arg']), r['caller_file'], r['caller'],
                             int(r['line'] or 0), r['cells'], int(r['calls'])))
        db.executemany('INSERT INTO rt_callsite VALUES (?,?,?,?,?,?,?,?)', rows)
        counts['rt_callsite'] = len(rows)
    old_names, renames = None, None
    if source_rev and git_dir:
        text, renames = git_runtime_inputs(git_dir, source_rev, to_rev)
        old_names = old_name_addresses(text)
    counts['rt_fn_map'] = load_runtime_map(db, old_names, renames, log)
    files = sorted(p for p in rt_dir.iterdir() if p.is_file())
    meta = dict(dir=str(rt_dir), stamp=file_stamp(files), source_rev=source_rev or '', counts=json.dumps(counts),
                loaded_at=time.strftime('%Y-%m-%dT%H:%M:%S'), git_to_rev=to_rev if git_dir else '')
    db.executemany('INSERT OR REPLACE INTO rt_meta VALUES (?,?)', list(meta.items()))
    db.commit()
    log('runtime: %s' % json.dumps(counts))
    return counts


SEED = re.compile(r'^(?P<fn>[^#@]+)(?:@(?P<file>[^#]+))?#(?P<param>\d+)$')


def load_flow(db, path, log=print):
    """type-flow lane item_status.tsv (or a DIR holding it) -> flow_item (replaced whole)."""
    path = Path(path)
    if path.is_dir():
        path = path / 'item_status.tsv'
    ensure_schema(db)
    db.execute('DELETE FROM flow_item')
    rows = []
    with path.open() as fh:
        for r in csv.DictReader(fh, delimiter='\t'):
            for seed in filter(None, (s.strip() for s in (r.get('seed_rows') or '').split(';'))):
                m = SEED.match(seed)
                if not m:
                    continue
                rows.append((r.get('transaction'), m['fn'], m['file'], int(m['param']), r.get('verdict'),
                             r.get('status'), r.get('reason'), r.get('predicted_delta'), path.name))
    db.executemany('INSERT INTO flow_item VALUES (?,?,?,?,?,?,?,?,?)', rows)
    db.commit()
    log('flow: %d seed rows from %s' % (len(rows), path))
    return len(rows)


# ------------------------------------------------------------------------------------------- queries

def q_casts(db, folder=None, cls=None, sub=None, func=None, by='cls,sub', limit=40):
    """AST cast rows (deduplicated across TUs) grouped by `by`; filters on folder/cls/sub/function."""
    where, args = [], []
    if folder:
        where.append('file LIKE ?'); args.append(folder.rstrip('/') + '/%')
    if cls:
        where.append('cls = ?'); args.append(cls)
    if sub:
        where.append('sub LIKE ?'); args.append(sub + '%')
    if func:
        where.append('func = ?'); args.append(func)
    cols = [c.strip() for c in by.split(',') if c.strip()]
    for c in cols:
        if c not in CAST_COLS:
            raise ValueError('group by one of ' + ', '.join(CAST_COLS))
    sql = ('SELECT %s, COUNT(*) FROM (SELECT DISTINCT file, start, macro, line, cls, sub, func, view, base_decl, '
           'base_kind, base_record, target, access, operand_type, base_expr, offset, width, cast_line, col FROM cast_site%s) '
           'GROUP BY %s ORDER BY COUNT(*) DESC LIMIT %d') % (
        ', '.join(cols), (' WHERE ' + ' AND '.join(where)) if where else '', ', '.join(cols), limit)
    out = [dict(zip(cols + ['casts'], r)) for r in db.execute(sql, args)]
    total = db.execute('SELECT COUNT(*) FROM (SELECT DISTINCT file, start, macro, line FROM cast_site%s)' % (
        (' WHERE ' + ' AND '.join(where)) if where else ''), args).fetchone()[0]
    return dict(filters=dict(folder=folder, cls=cls, sub=sub, func=func), ast_casts=total, groups=out)


def q_views(db, name=None, folder=None, family=None, limit=40):
    """Records with members, users (cast rows naming the view) and same-shape siblings."""
    where, args = [], []
    if name:
        where.append('record = ?'); args.append(name)
    if folder:
        where.append('def_file LIKE ?'); args.append(folder.rstrip('/') + '/%')
    if family:
        where.append('family = ?'); args.append(family)
    rows = db.execute('SELECT record, def_file, kind, size, align, family, members, seen FROM record_layout%s '
                      'ORDER BY record LIMIT %d' % ((' WHERE ' + ' AND '.join(where)) if where else '', limit),
                      args).fetchall()
    out = []
    for record, def_file, kind, size, align, fam, nm, seen in rows:
        members = db.execute('SELECT off, size, type, name, path FROM record_member WHERE record=? AND def_file=? '
                             'AND depth=0 ORDER BY off', (record, def_file)).fetchall()
        users = db.execute('SELECT COUNT(DISTINCT file || ":" || start), COUNT(DISTINCT file || ":" || func) '
                           'FROM cast_site WHERE view=? OR target LIKE ?', (record, record + ' *%')).fetchone()
        out.append(dict(record=record, def_file=def_file, kind=kind, size=size, align=align, family=fam, seen_in_tus=seen,
                        cast_sites=users[0], functions=users[1],
                        members=[dict(off=m[0], size=m[1], type=m[2], name=m[3]) for m in members[:64]]))
    fam = dict(db.execute('SELECT family, COUNT(*) FROM record_layout GROUP BY family'))
    return dict(families=fam, records=out)


def q_rt(db, function, file=None):
    """Runtime cells per parameter of `function`, with the declared parameters and the casts on each."""
    args = [function] + ([file] if file else [])
    fw = ' AND file = ?' if file else ''
    params = {}
    for f, p in db.execute("SELECT file, params FROM decl WHERE kind='def' AND name=?" + fw, args):
        params[f] = json.loads(p or '[]')
    rt = db.execute('SELECT file, arg, calls, param_type, observations, heap_kinds, cells FROM rt_fn_arg '
                    'WHERE function=?' + fw + ' ORDER BY file, arg', args).fetchall()
    casts = db.execute('SELECT file, base_decl, cls, COUNT(DISTINCT start) FROM cast_site WHERE func=?' + fw +
                       " AND base_decl LIKE 'param:%' GROUP BY file, base_decl, cls", args).fetchall()
    per = collections.defaultdict(lambda: collections.defaultdict(dict))
    for f, decl, cls, n in casts:
        per[f][int(decl.split(':')[1])][cls] = n
    callsites = db.execute('SELECT arg, caller_file, caller, line, cells, calls FROM rt_callsite WHERE callee=?'
                           + (' AND callee_file = ?' if file else '') + ' ORDER BY arg, calls DESC', args).fetchall()
    holds = db.execute('SELECT item, param, verdict, status, reason FROM flow_item WHERE function=?'
                       + (' AND (file IS NULL OR file=?)' if file else ''), args).fetchall()
    meta = dict(db.execute('SELECT key, value FROM rt_meta'))
    return dict(function=function, runtime_source=meta.get('source_rev'), definitions={
        f: dict(params=p, casts_by_param={i: dict(c) for i, c in per.get(f, {}).items()}) for f, p in params.items()},
        runtime=[dict(zip(('file', 'arg', 'calls', 'param_type', 'observations', 'heap_kinds', 'cells'), r)) for r in rt],
        callsites=[dict(zip(('arg', 'caller_file', 'caller', 'line', 'cells', 'calls'), r)) for r in callsites[:60]],
        flow=[dict(zip(('item', 'param', 'verdict', 'status', 'reason'), r)) for r in holds])


def q_param(db, key):
    """FILE::FUNCTION::INDEX (or FUNCTION::INDEX) -> every fact keyed to that parameter."""
    parts = key.split('::')
    if len(parts) == 3:
        file, function, index = parts
    elif len(parts) == 2:
        file, (function, index) = None, parts
    else:
        raise ValueError('param key is FILE::FUNCTION::INDEX')
    index = int(index)
    res = q_rt(db, function, file)
    out = dict(param=key, function=function, file=file)
    out['declared'] = {f: (d['params'][index] if index < len(d['params']) else None) for f, d in res['definitions'].items()}
    out['casts'] = {f: d['casts_by_param'].get(index, {}) for f, d in res['definitions'].items()}
    out['runtime'] = [r for r in res['runtime'] if r['arg'] == index]
    out['callsites'] = [r for r in res['callsites'] if r['arg'] == index]
    out['flow'] = [r for r in res['flow'] if r['param'] == index]
    out['pointee_stores'] = [dict(zip(('file', 'line', 'function', 'access', 'target', 'offset', 'value_class',
                                       'value_target', 'value_offset', 'count'), r)) for r in db.execute(
        "SELECT * FROM rt_pointee WHERE value_class='func' AND value_target "
        + ('= ?' if file else 'LIKE ?'), ((file or '%') + ':' + function,)).fetchall()[:20]]
    return out


def q_holds(db, limit=40):
    rows = db.execute('SELECT reason, status, COUNT(*), COUNT(DISTINCT item) FROM flow_item GROUP BY reason, status '
                      'ORDER BY COUNT(*) DESC').fetchall()
    return [dict(reason=r[0], status=r[1], seeds=r[2], items=r[3]) for r in rows[:limit]]


def q_slots(db, function=None, limit=40):
    """Callback slots observed at runtime: which functions are stored into which object slot (rt_pointee)."""
    args, w = [], ''
    if function:
        w, args = ' AND value_target LIKE ?', ['%:' + function]
    rows = db.execute("SELECT target, offset, value_target, access, SUM(count), COUNT(DISTINCT file || line), "
                      "GROUP_CONCAT(DISTINCT function) FROM rt_pointee WHERE value_class='func'" + w +
                      " GROUP BY target, offset, value_target, access ORDER BY SUM(count) DESC LIMIT %d" % limit,
                      args).fetchall()
    return [dict(zip(('slot_object', 'slot_offset', 'function', 'access', 'count', 'sites', 'by_functions'), r))
            for r in rows]


# ------------------------------------------------------------------------------------------- planner prefilter

STAGE_ROWS = {
    'alias': "base_decl LIKE 'param:%' AND cls IN ('a', 'c')",
    'retype': "base_decl LIKE 'local:%' AND cls IN ('a', 'c')",
    'fold': "(cls = 'n' AND sub LIKE 'fold%') OR (cls = 'c' AND sub LIKE 'generated_view%')",
    'synth': "cls = 'b' AND (sub LIKE '%pad_member%' OR sub LIKE '%array_member%' OR sub = 'no_member')",
    'redundant': "cls = 'n' AND sub LIKE 'redundant%'",
}


def candidate_files(db, files, stages):
    """The subset of `files` whose cast rows give any of `stages` something to plan (wave prefilter).

    A file the map has no typing facts for is kept (new or unparsed).  Returns (subset, reasons by file)."""
    files = list(files)
    known = {r[0] for r in db.execute('SELECT DISTINCT file FROM cast_site')}
    seen_tus = {r[0] for r in db.execute('SELECT tu FROM typing_tu')}
    clauses = [STAGE_ROWS[s] for s in dict.fromkeys(stages) if s in STAGE_ROWS]
    if len(clauses) != len(set(stages)):
        return files, {f: 'stage without a prefilter' for f in files}
    hit = collections.defaultdict(set)
    if clauses:
        sql = 'SELECT DISTINCT file, cls, sub FROM cast_site WHERE (%s)' % ') OR ('.join(clauses)
        for file, cls, sub in db.execute(sql):
            hit[file].add('%s:%s' % (cls, sub))
    out, why = [], {}
    for f in files:
        if f in hit:
            out.append(f)
            why[f] = ','.join(sorted(hit[f])[:4])
        elif f not in known and f not in seen_tus:
            out.append(f)
            why[f] = 'no typing facts'
    return out, why
