"""Typing facts for codemap.db: what the pointer-cast and type-flow tools derive from one clang parse per TU.

Every typing tool (cast_census, cast_fold, type_flow graph, object_kinds, param_alias ...) starts from
tools/typing/cast_ast.clang_unit (mipsel clang: JSON AST + -fdump-record-layouts-complete, two clang runs per
physical TU) and re-derives the same per-TU facts on every run.  This phase parses each registered physical TU
once, extracts

  cast_site      every pointer cast with its blocker class (tools/typing/cast_census.scan_unit, the census
                 classifier itself: cls/sub, base kind/record/declaration, view, offset, width ...)
  record_layout  every complete record the TU sees, with size/align, defining file, generated-view family
  record_member  its members at absolute offsets (nested members flattened with their C path)
  flow_tu        the type-flow graph of the TU (tools/typing/type_flow.Extract dump, gzip JSON), the input of
                 `type_flow.py graph`

and stores them keyed per TU by a stamp over the TU's include-closure sha (codemap `tu` table), its registered
recipe and the extractor sources.  `refresh` re-extracts only TUs whose stamp changed, commits every 50 TUs (a
stopped refresh resumes), and drops facts of TUs that left the build graph.

Queries and loaders live in typing_query.py (not part of the stamp).  Runtime evidence (the private native port's
rtti campaign) is loaded on demand with `codemap.py load-runtime DIR`
into rt_fn_arg / rt_kind / rt_pointee / rt_callsite (rt_meta records the files' sha and the decomp revision the
runtime was taken at); type-flow dry-run holds with `codemap.py load-flow DIR` into flow_item.  Both are keyed by
file::function::param so `codemap.py query param FILE::FN::I` joins declaration, runtime cells, casts and hold.
"""
from __future__ import annotations

import collections
import csv
import gzip
import hashlib
import json
import os
from pathlib import Path
import re
import sys
import time

HERE = Path(__file__).resolve()
TOOLS = HERE.parents[1]

TYPING_SOURCES = (HERE, TOOLS / 'typing/cast_census.py', TOOLS / 'typing/cast_ast.py', TOOLS / 'typing/cast_fold.py',
                  TOOLS / 'typing/field_census.py', TOOLS / 'typing/type_flow.py')

SCHEMA = '''
CREATE TABLE IF NOT EXISTS typing_tu(tu TEXT PRIMARY KEY, stamp TEXT, casts INTEGER, records INTEGER,
    flow_bytes INTEGER, error TEXT, seconds REAL, records_seen TEXT);
CREATE TABLE IF NOT EXISTS cast_site(tu TEXT, file TEXT, func TEXT, line INTEGER, cast_line INTEGER, col TEXT,
    start INTEGER, macro INTEGER, cls TEXT, sub TEXT, access TEXT, target TEXT, operand_type TEXT, base_kind TEXT,
    base_record TEXT, base_decl TEXT, base_expr TEXT, view TEXT, offset INTEGER, width INTEGER, row TEXT);
CREATE INDEX IF NOT EXISTS cast_site_tu ON cast_site(tu);
CREATE INDEX IF NOT EXISTS cast_site_file ON cast_site(file, func);
CREATE INDEX IF NOT EXISTS cast_site_view ON cast_site(view);
CREATE TABLE IF NOT EXISTS record_layout(record TEXT, def_file TEXT, kind TEXT, size INTEGER, align INTEGER,
    family TEXT, members TEXT, seen INTEGER, tu TEXT, UNIQUE(record, def_file));
CREATE INDEX IF NOT EXISTS record_layout_record ON record_layout(record);
CREATE INDEX IF NOT EXISTS record_layout_file ON record_layout(def_file);
CREATE TABLE IF NOT EXISTS record_member(record TEXT, def_file TEXT, off INTEGER, size INTEGER, type TEXT,
    name TEXT, path TEXT, depth INTEGER);
CREATE INDEX IF NOT EXISTS record_member_key ON record_member(record, def_file);
CREATE TABLE IF NOT EXISTS flow_tu(tu TEXT PRIMARY KEY, blob BLOB);
CREATE TABLE IF NOT EXISTS rt_meta(key TEXT PRIMARY KEY, value TEXT);
CREATE TABLE IF NOT EXISTS rt_fn_arg(file TEXT, function TEXT, arg INTEGER, calls INTEGER, nparams INTEGER,
    param_type TEXT, observations INTEGER, heap_kinds INTEGER, cells TEXT);
CREATE INDEX IF NOT EXISTS rt_fn_arg_fn ON rt_fn_arg(function, file);
CREATE TABLE IF NOT EXISTS rt_kind(id TEXT PRIMARY KEY, role TEXT, creator_file TEXT, creator_function TEXT,
    size INTEGER, allocs INTEGER, body_receivers TEXT, doc TEXT);
CREATE TABLE IF NOT EXISTS rt_pointee(file TEXT, line INTEGER, function TEXT, access TEXT, target TEXT,
    offset TEXT, value_class TEXT, value_target TEXT, value_offset TEXT, count INTEGER);
CREATE INDEX IF NOT EXISTS rt_pointee_site ON rt_pointee(file, line);
CREATE INDEX IF NOT EXISTS rt_pointee_target ON rt_pointee(target, offset);
CREATE TABLE IF NOT EXISTS rt_callsite(callee_file TEXT, callee TEXT, arg INTEGER, caller_file TEXT, caller TEXT,
    line INTEGER, cells TEXT, calls INTEGER);
CREATE INDEX IF NOT EXISTS rt_callsite_callee ON rt_callsite(callee, arg);
CREATE TABLE IF NOT EXISTS flow_item(item TEXT, function TEXT, file TEXT, param INTEGER, verdict TEXT, status TEXT,
    reason TEXT, predicted_delta TEXT, source TEXT);
CREATE INDEX IF NOT EXISTS flow_item_fn ON flow_item(function, param);
'''

VIEW_FAMILIES = (('S_', re.compile(r'^S_(?:func_)?[0-9A-Fa-f]{8}(?:_\w+)?$')), ('R12_', re.compile(r'^R12_')),
                 ('Row_', re.compile(r'^Row_')), ('Rec_', re.compile(r'^Rec_')), ('View', re.compile(r'View$')),
                 ('Func_state', re.compile(r'^Func[0-9A-Fa-f]{8}State$')))
CAST_COLS = ('file', 'func', 'line', 'cast_line', 'col', 'start', 'macro', 'cls', 'sub', 'access', 'target',
             'operand_type', 'base_kind', 'base_record', 'base_decl', 'base_expr', 'view', 'offset', 'width')


def tool_stamp():
    return hashlib.sha256(b''.join(p.read_bytes() for p in TYPING_SOURCES if p.is_file())).hexdigest()


def family_of(record, def_file):
    for name, rx in VIEW_FAMILIES:
        if rx.search(record):
            return name
    if def_file.startswith('src/'):
        return 'local'           # a record defined in a .c file: a file-local view
    return 'shared' if def_file.startswith('include/') else 'other'


def _setup(root):
    # the extractors of the tree being mapped first, then the ones next to this file (fixture roots have no tools/)
    for p in (str(TOOLS), str(TOOLS / 'typing'), str(Path(root) / 'tools'), str(Path(root) / 'tools/typing')):
        if p not in sys.path:
            sys.path.insert(0, p)


def flatten(unit, key, lay):
    """[(off, size, type, name, path, depth)] of a record's members, nested aggregates included."""
    out = []

    def walk(node, prefix, depth):
        name = node['name']
        path = (prefix + '.' + name if prefix else name) if name else prefix
        size = unit.size(node['type']) if not node['bits'] else None
        out.append((node['off'], size, node['type'], name, path, depth))
        if depth < 6:
            for kid in node['kids']:
                walk(kid, path, depth + 1)
    for node in lay.get('kids', ()):
        walk(node, '', 0)
    return out


def extract(args):
    """Worker: one clang parse of a physical TU -> cast rows, records, flow graph blob."""
    root, tu, recipe = args
    _setup(root)
    started = time.monotonic()
    import cast_ast as A
    import cast_census as CC
    try:
        unit, error = A.clang_unit(Path(root), tu, recipe)
    except Exception as exc:          # one failing TU is recorded, never fatal
        return dict(tu=tu, error='clang: ' + str(exc)[-300:], rows=[], records=[], flow=None,
                    seconds=round(time.monotonic() - started, 3))
    if unit is None:
        return dict(tu=tu, error=error, rows=[], records=[], flow=None, seconds=round(time.monotonic() - started, 3))
    try:
        rows = CC.scan_unit(unit, tu, lambda f: f.startswith('src/') and f.endswith('.c'))
    except Exception as exc:
        rows, error = [], 'cast_census: %s: %s' % (type(exc).__name__, str(exc)[-200:])
    records = []
    for key, lay in unit.layouts.items():
        def_file = unit.record_files.get(key, '') or ''
        if not def_file.startswith(('src/', 'include/')) or not lay.get('size'):
            continue
        records.append((key, def_file, lay.get('kind'), lay.get('size'), lay.get('align'), flatten(unit, key, lay)))
    flow = None
    try:
        import type_flow as TF
        flow = gzip.compress(json.dumps(TF.Extract(unit).run().dump(), separators=(',', ':')).encode(), 6)
    except Exception as exc:
        error = (error + '; ' if error else '') + 'type_flow: %s: %s' % (type(exc).__name__, str(exc)[-200:])
    return dict(tu=tu, error=error, rows=rows, records=records, flow=flow, seconds=round(time.monotonic() - started, 3))


def ensure_schema(db):
    db.executescript(SCHEMA)


def drop(db, tu):
    row = db.execute('SELECT records_seen FROM typing_tu WHERE tu=?', (tu,)).fetchone()
    seen = json.loads(row[0] or '[]') if row else []
    db.execute('DELETE FROM typing_tu WHERE tu=?', (tu,))
    db.execute('DELETE FROM cast_site WHERE tu=?', (tu,))
    db.execute('DELETE FROM flow_tu WHERE tu=?', (tu,))
    for i in range(0, len(seen), 500):           # rowids of the record_layout rows this TU saw
        chunk = seen[i:i + 500]
        db.execute('UPDATE record_layout SET seen=seen-1 WHERE rowid IN (%s)' % ','.join('?' * len(chunk)), chunk)


def store(db, res, stamp):
    tu = res['tu']
    db.executemany('INSERT INTO cast_site VALUES (%s)' % ','.join('?' * 21), [
        (tu,) + tuple(r.get(c) if not isinstance(r.get(c), (list, dict)) else json.dumps(r.get(c)) for c in CAST_COLS)
        + (json.dumps(r, separators=(',', ':')),) for r in res['rows']])
    seen = []
    for key, def_file, kind, size, align, members in res['records']:
        shape = '%d:%s' % (len(members), hashlib.sha256(repr((size, align, kind, members)).encode()).hexdigest()[:16])
        row = db.execute('SELECT rowid, members FROM record_layout WHERE record=? AND def_file=?',
                         (key, def_file)).fetchone()
        if row is None:
            cur = db.execute('INSERT INTO record_layout VALUES (?,?,?,?,?,?,?,1,?)',
                             (key, def_file, kind, size, align, family_of(key, def_file), shape, tu))
            seen.append(cur.lastrowid)
        else:
            seen.append(row[0])
            db.execute('UPDATE record_layout SET seen=seen+1, size=?, align=?, kind=?, members=? WHERE rowid=?',
                       (size, align, kind, shape, row[0]))
            if row[1] == shape:
                continue                         # a shared header record most TUs see: members unchanged
            db.execute('DELETE FROM record_member WHERE record=? AND def_file=?', (key, def_file))
        db.executemany('INSERT INTO record_member VALUES (?,?,?,?,?,?,?,?)',
                       [(key, def_file) + m for m in members])
    if res['flow'] is not None:
        db.execute('INSERT OR REPLACE INTO flow_tu VALUES (?,?)', (tu, res['flow']))
    db.execute('INSERT OR REPLACE INTO typing_tu VALUES (?,?,?,?,?,?,?,?)', (
        tu, stamp, len(res['rows']), len(res['records']), len(res['flow'] or b''), res['error'], res['seconds'],
        json.dumps(seen, separators=(',', ':'))))


def physical_tus(root):
    _setup(root)
    import layout_compile_identity as L
    physical, _ = L.recipes(Path(root))
    return physical


def refresh(cm, force=False, physical=None):
    """Re-extract typing facts of every physical TU whose stamp changed.  Returns the number extracted."""
    db = cm.db
    ensure_schema(db)
    t = time.monotonic()
    physical = physical if physical is not None else physical_tus(cm.root)
    tool = cm.typing_tool = tool_stamp()     # the stamp this refresh extracts with (meta typing_complete)
    closure = dict(db.execute('SELECT path, closure_sha256 FROM tu'))
    stored = dict(db.execute('SELECT tu, stamp FROM typing_tu'))
    todo, stamps = [], {}
    for tu, recipe in sorted(physical.items()):
        if cm.only and not tu.startswith(cm.only):
            continue
        own = closure.get(tu)
        if own is None:
            try:
                own = hashlib.sha256((cm.root / tu).read_bytes()).hexdigest()
            except OSError:
                own = '-'
        stamps[tu] = hashlib.sha256('\n'.join((tool, own, json.dumps(recipe, sort_keys=True))).encode()).hexdigest()
        if force or stored.get(tu) != stamps[tu]:
            todo.append(tu)
    gone = sorted(set(stored) - set(physical)) if not cm.only else []
    for tu in gone + todo:
        drop(db, tu)
    db.execute('DELETE FROM record_layout WHERE seen <= 0')
    db.execute('DELETE FROM record_member WHERE NOT EXISTS (SELECT 1 FROM record_layout r WHERE '
               'r.record = record_member.record AND r.def_file = record_member.def_file)')
    db.commit()
    cm.log('typing: %d of %d physical TUs to extract (%d removed)' % (len(todo), len(stamps), len(gone)))
    done = 0
    jobs = [(str(cm.root), tu, physical[tu] if physical[tu].get('slus_unit') else None) for tu in todo]
    with cm.pool() as ex:
        for res in ex.map(extract, jobs, chunksize=2):
            store(db, res, stamps[res['tu']])
            done += 1
            if done % 50 == 0:
                db.commit()
            if done % 1000 == 0:
                cm.log('  typing %d/%d (%.0fs)' % (done, len(todo), time.monotonic() - t))
    db.execute('DELETE FROM record_layout WHERE seen <= 0')
    db.commit()
    cm.log('typing: extracted %d TUs in %.1fs' % (done, time.monotonic() - t))
    return done


def check(cm, physical=None):
    """TUs whose typing stamp is stale (read-only): [(tu, reason)]."""
    db = cm.db
    tables = {r[0] for r in db.execute("SELECT name FROM sqlite_master WHERE type='table'")}
    if 'typing_tu' not in tables:
        return [('*', 'no typing facts')]
    physical = physical if physical is not None else physical_tus(cm.root)
    tool = tool_stamp()
    closure = dict(db.execute('SELECT path, closure_sha256 FROM tu'))
    stored = dict(db.execute('SELECT tu, stamp FROM typing_tu'))
    out = []
    for tu, recipe in physical.items():
        own = closure.get(tu) or '-'
        stamp = hashlib.sha256('\n'.join((tool, own, json.dumps(recipe, sort_keys=True))).encode()).hexdigest()
        if stored.get(tu) != stamp:
            out.append((tu, 'missing' if tu not in stored else 'stale'))
    return out
