#!/usr/bin/env python3
"""Frozen, resumable pin damage and interaction experiments; never edits source.

prepare/start/status/report use work/pin_search/<tag>. Every probe is atomic and
recipe-bound. Uniform pair samples are independent of the overlap-selected arm.
Full target scoring is used even for negative results; no cc1 screen filtering.
"""
import argparse
import collections
import concurrent.futures
import itertools
import json
import os
from pathlib import Path
import random
import re
import resource
import signal
import subprocess
import sys
import tempfile
import time

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, rows, clean_path, sha_text, sha_file, PARKED_CONTAINERS
from pin_search import (atomic_json, atomic_text, digest, fingerprints, ownership,
                        configure, POLICY_ENV, safe_tag, utc, initialize_worker)
from pin_census import sites_of, unscored_text, asm_blocker
from pin_sites import erase_many, site_facts, scored_mask, linked, score
from pin_search_engine import erasure_groups
from pin_patterns import family, signature


def identity(pid):
    try:
        p = Path('/proc') / str(pid)
        if b'pin_atlas.py' not in (p / 'cmdline').read_bytes(): return None
        return (p / 'stat').read_text().rsplit(') ', 1)[1].split()[19]
    except (OSError, IndexError): return None


def experiment_fingerprint(selected):
    f = fingerprints(selected)
    # Score executes the generated gate copy and its row tables, not just source tools.
    actual = {p for p in (ROOT / 'build_ovl/tools').rglob('*') if p.is_file() and p.suffix in ('.py', '.sh', '.json')}
    actual.update(p for p in (ROOT / 'config/overlays').iterdir() if p.is_file())
    actual.update((ROOT / 'config').glob('*.yaml'))
    actual.update((ROOT / 'config').glob('*.jsonl'))
    for container in ('main', 'town', 'dungeon', 'dungeon_engine', 'ovmovie'):
        actual.add(ROOT / 'build_ovl/overlays' / container / 'overlay_first_pass_results.json')
    actual.add(ROOT / 'build_ovl/work/g3/overlay_func_compare.py')
    actual.add((ROOT / '.venv/bin/python').resolve())
    actual.add(ROOT / '.venv/pyvenv.cfg')
    for p in sorted(actual):
        if p.exists():
            name = str(p.relative_to(ROOT)) if p.is_relative_to(ROOT) else str(p)
            f['recipe_inputs'][name] = sha_file(p)
    f['recipe'] = digest(f['recipe_inputs'])
    # Historical ledgers are not inputs to this experiment. Bind only actual code.
    code = {p: h for p, h in f['search_inputs'].items() if p.startswith('tools/')}
    for p in ('tools/pin_atlas.py', 'tools/pin_patterns.py'):
        code[p] = sha_file(ROOT / p)
    return dict(recipe=f['recipe'], recipe_inputs=f['recipe_inputs'],
                code=digest(code), code_inputs=code)


def manifest_key(m):
    return digest({k: m[k] for k in ('schema', 'rows', 'fingerprints', 'options', 'environment')})


def load(d, check=False):
    m = json.loads((d / 'manifest.json').read_text())
    if manifest_key(m) != m['key']: raise RuntimeError('manifest identity changed')
    if check:
        f = experiment_fingerprint([x['row'] for x in m['rows']])
        if f != m['fingerprints']: raise RuntimeError('recipe/code changed; preserve this run and prepare a new tag')
        for x in m['rows']:
            if sha_file(d / x['input']) != x['sha']: raise RuntimeError('frozen input changed: ' + x['row']['id'])
    return m


def prepare(a):
    d = safe_tag(a.tag)
    if (d / 'manifest.json').exists(): raise RuntimeError('tag already prepared')
    selected, inventory = [], []
    keep = set(Path(a.ids).read_text().split()) if a.ids else None
    for r in rows():
        if not r.get('exists') or r['container'] in PARKED_CONTAINERS: continue
        p = clean_path(r)
        if not p.exists(): continue
        t = p.read_text(); n = len(sites_of(t))
        if not n: continue
        inventory.append(dict(id=r['id'], pins=n, stock=bool(r.get('stock')), asm_blocker=bool(asm_blocker(t))))
        if r.get('stock') and (keep is None or r['id'] in keep): selected.append((r, t))
    # Deterministic interleaving gives early progress across compiler/size strata.
    buckets = collections.defaultdict(list)
    for r, t in selected:
        n = len(sites_of(t)); buckets[(r['cfg'], min(n // 4, 4))].append((r, t))
    for values in buckets.values(): values.sort(key=lambda x: digest(x[0]['id']))
    ordered = []
    while any(buckets.values()):
        for k in sorted(buckets):
            if buckets[k]: ordered.append(buckets[k].pop())
    if a.sample: ordered = ordered[:a.sample]
    if not ordered: raise RuntimeError('no eligible rows')
    records = []
    for r, t in ordered:
        p = Path('inputs') / (r['id'].replace('/', '_') + '.c'); atomic_text(d / p, t)
        records.append(dict(row=r, sha=sha_text(t), input=str(p), pins=len(sites_of(t))))
    atomic_text(d / '.ignore', '*\n')
    m = dict(schema=1, created=utc(), tag=a.tag, rows=records,
             fingerprints=experiment_fingerprint([r for r, _ in ordered]), environment=POLICY_ENV,
             options=dict(pairs_per_arm=a.pairs, max_groups=a.groups, timeout=a.timeout))
    m['key'] = manifest_key(m); atomic_json(d / 'manifest.json', m)
    atomic_json(d / 'inventory.json', inventory)
    print(json.dumps(dict(tag=a.tag, rows=len(records), pins=sum(x['pins'] for x in records), key=m['key'])))


def overlap(a, b):
    """Jaccard of affected retail word positions, including insertion boundaries."""
    def positions(rec):
        out = set()
        for r in rec.get('regions', []):
            lo, hi = r['t']; out.update(range(lo, max(lo + 1, hi)))
        return out
    aa, bb = positions(a), positions(b)
    return len(aa & bb) / len(aa | bb) if aa and bb else 0.0


def pair_plan(rowid, singles, count):
    valid = [i for i, s in enumerate(singles) if s.get('status') == 'ok' and s.get('total') is not None]
    pairs = list(itertools.combinations(valid, 2))
    rng = random.Random(digest([rowid, 'uniform-pairs-v1']))
    uniform = set(rng.sample(pairs, min(count, len(pairs))))
    weights = {p: overlap(singles[p[0]], singles[p[1]]) for p in pairs}
    ranked = sorted((p for p in pairs if weights[p] > 0), key=lambda p: (-weights[p], digest([rowid, p])))[:count]
    chosen = uniform | set(ranked)
    return [dict(s=list(p), arms=[arm for arm, yes in (('uniform', p in uniform), ('overlap', p in ranked)) if yes],
                 overlap=weights[p]) for p in sorted(chosen)]


def group_plan(live, singles, pairs, limit):
    n = len(live); seen = {tuple(p['s']) for p in pairs}; candidates = []
    if n > 1: candidates.append((tuple(range(n)), 'strip'))
    candidates.extend((tuple(g), 'variable-or-macro') for g in erasure_groups(live, families_only=True) if len(g) > 2)
    neighbors = [set([i]) for i in range(n)]
    for p in pairs:
        i, j = p['s']
        if p.get('status') == 'ok' and linked(singles[i].get('total'), singles[j].get('total'), p.get('total'),
                [r['t'] for r in singles[i].get('regions', [])], [r['t'] for r in singles[j].get('regions', [])]):
            neighbors[i].add(j); neighbors[j].add(i)
    # Neighborhoods avoid collapsing a long chain into the already-tested full strip.
    candidates[1:1] = [(tuple(sorted(g)), 'measured-neighborhood') for g in neighbors if len(g) > 2]
    out = []
    for g, reason in candidates:
        if g in seen: continue
        seen.add(g); out.append(dict(s=list(g), reason=reason))
        if len(out) >= limit: break
    return out


def probe_child(a):
    # A killed controller must not leave compilers consuming CPU or its lock inherited.
    signal.signal(signal.SIGTERM, lambda *_: os.killpg(os.getpgrp(), signal.SIGKILL))
    initialize_worker(a.parent_pid)
    req = json.loads(Path(a.probe).read_text()); configure(req['environment'])
    started = time.monotonic(); cpu = time.process_time()
    r = score(req['row'], Path(req['source']).read_text())
    r.update(wall_seconds=time.monotonic() - started,
             cpu_seconds=time.process_time() - cpu + resource.getrusage(resource.RUSAGE_CHILDREN).ru_utime + resource.getrusage(resource.RUSAGE_CHILDREN).ru_stime)
    atomic_json(Path(a.probe).with_suffix('.result.json'), r)


def measure(d, m, item, rowdir, selected, retry_errors=False):
    key = 'base' if not selected else '-'.join(map(str, selected))
    if len(key) > 120:    # a strip probe on a many-pin row overflowed NAME_MAX (2026-09-12, 56+ pins)
        key = 'h' + digest(selected)[:16]
    path = rowdir / 'probes' / (key + '.json')
    bound = digest([m['key'], item['row']['id'], selected])
    if path.exists():
        saved = json.loads(path.read_text())
        if saved.get('key') != bound: raise RuntimeError('probe identity changed')
        if saved.get('status') == 'ok' or not retry_errors:
            candidate_path = rowdir / 'candidates' / (key + '.c')
            if selected and saved.get('exact') and not candidate_path.exists():
                source = (d / item['input']).read_text(); live = sites_of(source)
                candidate = erase_many(source, [live[i] for i in selected], clean_notes=True)
                if sha_text(candidate) != saved['candidate_sha']: raise RuntimeError('cached candidate identity changed')
                atomic_text(candidate_path, candidate)
            return saved
    source = (d / item['input']).read_text(); live = sites_of(source)
    candidate = erase_many(source, [live[i] for i in selected], clean_notes=True)
    if unscored_text(source) != unscored_text(candidate): raise RuntimeError('unscored C changed')
    with tempfile.TemporaryDirectory(prefix='pin-atlas-') as td:
        td = Path(td); cfile = td / Path(item['row']['c_path']).name; cfile.write_text(candidate)
        req = td / 'request.json'; req.write_text(json.dumps(dict(row=item['row'], source=str(cfile), environment=m['environment'])))
        with (td / 'stderr.log').open('w+') as log:
            p = subprocess.Popen([sys.executable, str(Path(__file__).resolve()), '--probe', str(req), '--parent-pid', str(os.getpid())],
                                 cwd=ROOT, stdin=subprocess.DEVNULL, stdout=log, stderr=log, start_new_session=True,
                                 env=dict(os.environ, TMPDIR=str(td)))
            try:
                p.wait(timeout=m['options']['timeout'])
                if p.returncode: raise RuntimeError('probe exited ' + str(p.returncode))
                rec = json.loads(req.with_suffix('.result.json').read_text())
            except (subprocess.TimeoutExpired, RuntimeError, OSError, ValueError) as exc:
                try: os.killpg(p.pid, signal.SIGKILL)
                except ProcessLookupError: pass
                p.wait(); log.seek(0)
                rec = dict(status='failed', exact=False, total=None, error=str(exc), stderr=log.read()[-1200:])
    rec.update(key=bound, s=list(selected), source_sha=item['sha'], candidate_sha=sha_text(candidate), at=utc())
    atomic_json(path, rec)
    # Save every independently scored exact erasure. No union is assumed exact, no landing.
    if selected and rec.get('status') == 'ok' and rec.get('exact'):
        atomic_text(rowdir / 'candidates' / (key + '.c'), candidate)
    return rec


def row_job(d, m, item, retry_errors=False):
    rowid = item['row']['id']; rd = d / 'rows' / rowid.replace('/', '_')
    rd.mkdir(parents=True, exist_ok=True)
    result = rd / 'result.json'
    if result.exists():
        saved = json.loads(result.read_text())
        if saved.get('key') != m['key']: raise RuntimeError('row result identity changed')
        if not retry_errors or not saved.get('errors'): return saved
    start = time.monotonic(); source = (d / item['input']).read_text(); live = sites_of(source)
    def probe(s): return measure(d, m, item, rd, s, retry_errors)
    base = probe([])
    rec = dict(id=rowid, key=m['key'], source_sha=item['sha'], pins=len(live), baseline=base, singles=[], pairs=[], groups=[])
    if not base.get('exact'):
        rec.update(status='baseline-failed', errors=1); atomic_json(result, rec); return rec
    masked = scored_mask(source)
    for i in range(len(live)):
        s = probe([i])
        try: facts = site_facts(source, masked, live, i)
        except Exception as exc: facts = dict(site=i, macro=live[i][1], facts_error=repr(exc))
        rec['singles'].append(dict(s, facts=facts))
    plan = pair_plan(rowid, rec['singles'], m['options']['pairs_per_arm'])
    atomic_json(rd / 'pair_plan.json', plan)
    for p in plan: rec['pairs'].append(dict(probe(p['s']), arms=p['arms'], overlap=p['overlap']))
    groups = group_plan(live, rec['singles'], rec['pairs'], m['options']['max_groups'])
    atomic_json(rd / 'group_plan.json', groups)
    for g in groups: rec['groups'].append(dict(probe(g['s']), reason=g['reason']))
    probes = rec['singles'] + rec['pairs'] + rec['groups']
    errors = sum(x.get('status') != 'ok' for x in probes)
    rec.update(status='complete' if not errors else 'complete-with-errors', errors=errors,
               probes=1 + len(probes), wall_seconds=time.monotonic() - start,
               cpu_seconds=sum(x.get('cpu_seconds', 0) for x in [base] + probes),
               best_removal=max((len(x['s']) for x in probes if x.get('exact')), default=0))
    atomic_json(result, rec); return rec


def run(a):
    d = safe_tag(a.tag)
    with ownership():
        m = load(d, check=True); configure(m['environment'])
        state = dict(pid=os.getpid(), identity=identity(os.getpid()), phase='running', started=utc(), key=m['key'], rows=len(m['rows']), completed=0)
        atomic_json(d / 'state.json', state)
        try:
            with concurrent.futures.ThreadPoolExecutor(max_workers=a.workers) as ex:
                fs = [ex.submit(row_job, d, m, x, a.retry_errors) for x in m['rows']]
                for f in concurrent.futures.as_completed(fs):
                    r = f.result(); state.update(completed=state['completed'] + 1, last=r['id'], updated=utc())
                    atomic_json(d / 'state.json', state)
            # Changes to build inputs during a run invalidate it, rather than silently mixing recipes.
            load(d, check=True)
            state.update(phase='complete', finished=utc()); atomic_json(d / 'state.json', state)
            report(d, m)
        except BaseException as exc:
            state.update(phase='error', error=repr(exc), finished=utc()); atomic_json(d / 'state.json', state); raise


def report(d, m=None):
    m = m or load(d); records = []
    for item in m['rows']:
        p = d / 'rows' / item['row']['id'].replace('/', '_') / 'result.json'
        if p.exists(): records.append(json.loads(p.read_text()))
    clusters = collections.defaultdict(list); arms = collections.defaultdict(collections.Counter)
    singles = []; best = []; probes = 0
    for r in records:
        probes += r.get('probes', 1); singles.extend(r['singles'])
        if r.get('best_removal'): best.append(dict(id=r['id'], pins=r['best_removal']))
        for s in r['singles']:
            facts = s['facts']
            if s.get('status') != 'ok': continue
            # Descriptive bins, not assertions of a common causal fix.
            key = (family(facts.get('macro')), s.get('class'), facts.get('var_type'), tuple(sorted(set(facts.get('defs', [])))))
            clusters[json.dumps(key)].append(dict(id=r['id'], site=facts['site'], total=s.get('total'), signature=signature(s.get('regions', []))))
        for p in r['pairs']:
            for arm in p['arms']:
                arms[arm]['tested'] += 1
                if p.get('status') != 'ok': arms[arm]['failed'] += 1; continue
                arms[arm]['exact'] += bool(p.get('exact'))
                a, b = [r['singles'][i].get('total') for i in p['s']]
                if a is not None and b is not None and p.get('total') is not None:
                    arms[arm]['below_both_singles'] += p['total'] < min(a, b)
    ranked = [dict(key=json.loads(k), sites=len(v), examples=sorted(v, key=lambda x: (x['total'] is None, x['total'] or 0, x['id']))[:5]) for k, v in sorted(clusters.items(), key=lambda kv: (-len(kv[1]), kv[0]))]
    out = dict(tag=m['tag'], at=utc(), rows_expected=len(m['rows']), rows_done=len(records),
               pins_expected=sum(x['pins'] for x in m['rows']), sites_measured=len(singles),
               row_statuses=dict(collections.Counter(r['status'] for r in records)),
               probes=probes, cpu_seconds=sum(r.get('cpu_seconds', 0) for r in records),
               exact_single_sites=sum(bool(s.get('exact')) for s in singles),
               candidate_rows=best, staged_pins_upper_bound=sum(x['pins'] for x in best),
               pair_arms={k: dict(v) for k, v in arms.items()}, clusters=ranked,
               caveats=['Candidates require source review and publication gates; overlapping exact subsets cannot be unioned without rechecking.',
                        'Pair arms overlap and sample within rows; counts are descriptive, not independent trials or population causal estimates.',
                        'Source-fact heuristics and LCS range overlap suggest hypotheses, not compiler ownership.',
                        'SLUS distances use the existing pinned-object metric, overlay distances use aligned LCS; compare within a row only.'])
    atomic_json(d / 'report.json', out)
    print(json.dumps({k: v for k, v in out.items() if k not in ('clusters', 'candidate_rows', 'caveats')}, indent=2))
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('action', nargs='?', choices=['prepare', 'run', 'start', 'status', 'report'])
    ap.add_argument('--tag'); ap.add_argument('--ids'); ap.add_argument('--sample', type=int, default=0)
    ap.add_argument('--workers', type=int, default=4); ap.add_argument('--pairs', type=int, default=12)
    ap.add_argument('--groups', type=int, default=8); ap.add_argument('--timeout', type=int, default=90)
    ap.add_argument('--retry-errors', action='store_true'); ap.add_argument('--probe'); ap.add_argument('--parent-pid', type=int)
    a = ap.parse_args()
    if a.probe: return probe_child(a)
    if not a.tag or not a.action: ap.error('action and --tag required')
    if a.workers < 1 or a.pairs < 0 or a.groups < 1 or a.timeout < 1: ap.error('invalid budget')
    d = safe_tag(a.tag)
    if a.action == 'prepare':
        with ownership(): prepare(a)
    elif a.action == 'run': run(a)
    elif a.action == 'start':
        load(d, check=True)
        with ownership(): pass
        cmd = ['nice', '-n', '10', sys.executable, str(Path(__file__).resolve()), 'run', '--tag', a.tag, '--workers', str(a.workers)]
        if a.retry_errors: cmd.append('--retry-errors')
        with (d / 'controller.log').open('a') as log:
            p = subprocess.Popen(cmd, cwd=ROOT, stdin=subprocess.DEVNULL, stdout=log, stderr=log, start_new_session=True)
        print('started', p.pid)
    elif a.action == 'report': report(d)
    else:
        state = json.loads((d / 'state.json').read_text()) if (d / 'state.json').exists() else {'phase': 'prepared'}
        state['alive'] = bool(state.get('identity') and identity(state.get('pid')) == state['identity'])
        print(json.dumps(state, indent=2))

if __name__ == '__main__': main()
