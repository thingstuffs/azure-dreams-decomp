#!/usr/bin/env python3
"""Run one generator over rows WITHOUT touching src/: exact candidates are staged into a lane's out/ directory
(land later with tools/lanes/land_lanes.sh <tag> <lane>).  The round-57 t71_drive.py made general.

    python3 tools/lanes/gen_drive.py <generator> <lane> [--only id,id] [--workers N] [--base-from <lane2>]
                                     [--limit N] [--containers town,dungeon,main]

--base-from <lane2>  take a row's input text from work/native_lane/<lane2>/base/<id>.c when that file exists
                     (the pre-landing text of a model lane's rows): the way to check a new generator against the
                     exemplar rows a lane solved, whose src/ copy is already pin-free.
--fresh              ignore the journal's done set and TRUNCATE the lane's journal.jsonl, out/ and cells.jsonl
                     first: a re-sweep of a CHANGED generator over rows it already refused or missed (round 68;
                     rounds 60-67 deleted the lane directory by hand, which also threw away its staged wins).
--journal-refusals   also journal the rows `T.eligible()` refused, as
                     {"outcome": "refused", "reason": ...}: the refusal table a generator's next version is
                     written from (round 32's t69 table).  Off by default, so a lane's journal is unchanged.
--catchup            (round 76) also count as done every (id, in_sha) this generator already scored - in any
                     work/native_lane/*<generator>* lane journal (not *_check / *probe*: those score --base-from
                     texts) and in ledger/sweeps/<generator>.jsonl (the landing cascade's sweep.py journal) - whose
                     record is newer than the generator's module file: a tree-wide catch-up then scores only the rows
                     whose text changed since the generator last saw them.  Refused/error records never count.
Journal: work/native_lane/<lane>/journal.jsonl (resumable on (id, in_sha); refused records never mark a row
done, so they do not change what a later run sweeps).  A scorer run during a gate can
misreport (verify.py scores inside build_ovl, which mk_ovl_root.sh replaces): rerun the misses after the gate.
"""
import sys, json, tempfile, threading, time, importlib
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools')); sys.path.insert(0, str(ROOT / 'tools/xform'))
from common import rows, clean_path, sha_text, read_jsonl, parse_cfg
from pin_census import sites_of, unscored_text
from verify import verify

def arg(name, default=None):
    return sys.argv[sys.argv.index(name) + 1] if name in sys.argv else default

def flag(name):
    return name in sys.argv

gen, lane = sys.argv[1], sys.argv[2]
try:
    M = importlib.import_module('xform.' + gen)          # the package form: generators with relative imports
except ImportError:
    M = importlib.import_module(gen)
only = set(arg('--only').split(',')) if arg('--only') else None
workers = int(arg('--workers', 12)); limit = int(arg('--limit', 0))
containers = set(arg('--containers', 'town,dungeon,main,slus').split(','))
base_from = arg('--base-from')
fresh = flag('--fresh'); journal_refusals = flag('--journal-refusals')
OUT = ROOT / 'work/native_lane' / lane; (OUT / 'out').mkdir(parents=True, exist_ok=True); (OUT / '.ignore').write_text('*\n')
J = OUT / 'journal.jsonl'
if fresh:                                                   # a changed generator over the same rows
    import shutil
    for _p in (J, OUT / 'cells.jsonl'): _p.unlink(missing_ok=True)
    shutil.rmtree(OUT / 'out', ignore_errors=True); (OUT / 'out').mkdir(parents=True, exist_ok=True)
    print('--fresh: journal, out/ and cells.jsonl truncated', flush=True)
# a refused record never marks a row done: the next run re-asks the (possibly rewritten) eligible()
done = {(r['id'], r['in_sha']) for r in read_jsonl(J) if r.get('outcome') != 'refused'} if J.exists() else set()
if flag('--catchup'):
    import glob, os, datetime
    _gm = os.path.getmtime(M.__file__); _n0 = len(done)
    _longer = [p.stem for p in (ROOT / 'tools/xform').glob(gen + '?*.py')]
    for _j in glob.glob(str(ROOT / 'work/native_lane' / ('*' + gen + '*') / 'journal.jsonl')):
        _ln = Path(_j).parent.name
        if _ln == lane or '_check' in _ln or 'probe' in _ln or os.path.getmtime(_j) < _gm: continue
        if any(k != gen and k.startswith(gen) and k in _ln for k in _longer): continue   # t90_lifetimemerge vs _far
        done |= {(r['id'], r['in_sha']) for r in read_jsonl(Path(_j)) if r.get('outcome') not in ('refused', 'error') and 'in_sha' in r}
    _sw = ROOT / 'ledger/sweeps' / (gen + '.jsonl')
    if _sw.exists():
        _gt = datetime.datetime.fromtimestamp(_gm, datetime.timezone.utc).strftime('%Y-%m-%dT%H:%M:%SZ')
        done |= {(r['id'], r['in_sha']) for r in read_jsonl(_sw)
                 if r.get('outcome') not in ('refused', 'error') and 'in_sha' in r and r.get('at', '') >= _gt}
    print('--catchup:', len(done) - _n0, '(id, text) pairs already scored by', gen, flush=True)
cen = {c['id']: c for c in read_jsonl(ROOT / 'ledger/census.jsonl')}
todo = []; refusals = []
for r in rows():
    if only and r['id'] not in only: continue
    if r['container'] not in containers or not clean_path(r).exists(): continue
    p = ROOT / 'work/native_lane' / base_from / 'base' / (r['id'] + '.c') if base_from else None
    t = (p if p and p.exists() else clean_path(r)).read_text(errors='replace')
    if not sites_of(t) or (r['id'], sha_text(t)) in done: continue
    why = M.T.eligible(t, r, cen.get(r['id'], {}))
    if why:
        if journal_refusals:
            refusals.append({'id': r['id'], 'in_sha': sha_text(t), 'cfg': r['cfg'], 'outcome': 'refused',
                             'reason': (why if isinstance(why, str) else repr(why))[:200]})
        continue
    todo.append((r, t))
    if limit and len(todo) >= limit: break
if refusals:
    with J.open('a') as f:
        for rec in refusals: f.write(json.dumps(rec) + '\n')
    print(len(refusals), 'rows refused by eligible(), journalled', flush=True)
print(len(todo), 'eligible rows', flush=True)
lock = threading.Lock()

def one(job):
    r, t = job; t0 = time.time(); usig = unscored_text(t)
    def vf(cand, cfg=None):
        # `cfg` scores the text at ANOTHER stock recipe (a generator testing a cell switch): verify
        # reads cfg for overlay rows and cell/flags for slus rows, so all three move together.
        if unscored_text(cand) != usig: return {'exact': False}
        rr = r
        if cfg and cfg != r['cfg']:
            cell, flags = parse_cfg(cfg); rr = dict(r, cfg=cfg, cell=cell, flags=' '.join(flags))
        with tempfile.TemporaryDirectory() as td:
            p = Path(td) / Path(r['c_path']).name; p.write_text(cand); return verify(rr, p, include_root=ROOT / 'include')
    try: new, info = M.T.apply_verified(t, r, cen.get(r['id'], {}), vf)
    except Exception as e: return {'id': r['id'], 'in_sha': sha_text(t), 'outcome': 'error', 'err': repr(e)[:200]}
    rec = {'id': r['id'], 'in_sha': sha_text(t), 'cfg': r['cfg'], 'outcome': 'exact' if new else 'miss', 'secs': round(time.time() - t0, 1), **info}
    if new and info.get('cfg') and info['cfg'] != r['cfg']:
        # a candidate exact only at another stock recipe: land it with
        # `CELLS=work/native_lane/<lane>/cells.jsonl` (tools/apply_candidates.py --cells)
        rec['cfg_was'] = r['cfg']
        with lock, (OUT / 'cells.jsonl').open('a') as f:
            f.write(json.dumps({'id': r['id'], 'to': info['cfg']}) + '\n')
    if new:
        d = OUT / 'out' / r['container']; d.mkdir(exist_ok=True); n = Path(r['c_path']).name
        (d / n).write_text(new); (d / (n + '.base_sha')).write_text(sha_text(t) + '\n')
    return rec

n = hits = 0; t0 = time.time()
with ThreadPoolExecutor(workers) as ex:
    for rec in ex.map(one, todo):
        with lock, J.open('a') as f: f.write(json.dumps(rec) + '\n')
        n += 1; hits += rec['outcome'] == 'exact'
        if rec['outcome'] == 'error': print('error', rec['id'], rec['err'], flush=True)
        if n % 50 == 0: print(f'{n}/{len(todo)} exact {hits} {time.time() - t0:.0f}s', flush=True)
print(f'done {n} exact {hits} {time.time() - t0:.0f}s')
