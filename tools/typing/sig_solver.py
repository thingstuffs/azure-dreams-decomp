#!/usr/bin/env python3
"""Signature-consensus solver: one canonical prototype per function, decided by object bytes.

    sig_solver.py solve --header include/dungeon/item.h --out DIR [--names N...] [--all-names] [--workers 8]
    sig_solver.py apply --decisions DIR/decisions.json --out DIR [--prove] [--workers 8]   (tools/typing/sig_txn.py)

`solve` (read-only for tracked files):
  1. census (sig_census.py): the names the header owns with two or more signature spellings across src/
     and include/ (or every owned name with --all-names), their definitions, declaration sites and users;
  2. ABI facts (abi_facts.py) of each callee and its call sites from the built objects;
  3. probes (sig_probe.py): every TU that defines or uses a name is compiled at its production recipe with
     the hide construction - a control (today's spelling, which must equal the production object), the
     definition's prototype 'D', the width-rule prototype 'W' (ABI-wide return, narrowing moved into the
     definition body), and per-axis variants (return only / parameters only) to explain a refusal;
  4. consensus (sig_consensus.py) -> DIR/decisions.json (unified names with their prototype) and
     DIR/floors.jsonl (refusals in ledger/prototype_floors.jsonl form).
Names already in ledger/prototype_floors.jsonl are skipped (never re-tried) unless --retry-floors.

`apply` (sig_txn.py) writes one owning-header transaction from decisions.json and proves it with the
build-graph proof (tools/build/affected.py when present, else the recipe-closure fallback).
"""
from __future__ import annotations

import argparse
from collections import defaultdict
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import time

HERE = Path(__file__).resolve()
TOOLS = HERE.parents[1]
for p in (str(HERE.parent), str(TOOLS), str(TOOLS / 'headers')):
    if p not in sys.path:
        sys.path.insert(0, p)

import abi_facts as A  # noqa: E402
import sig_census as C  # noqa: E402
import sig_consensus as K  # noqa: E402
import sig_probe as S  # noqa: E402

FLOORS = 'ledger/prototype_floors.jsonl'
NATIVE = set()          # recipe ids built by the native (genuine ASPSX) module builder: probed in place


def recipe_index(root):
    """({source: [overlay recipe ids compiled from it]}, {file: [recipes listing it as a dependency]})."""
    by_source, by_dep = defaultdict(list), defaultdict(list)
    # Only recipes some registered image links carry bytes worth keeping; unlinked facades are left to
    # natcheck (their build/obj objects need not reproduce, and the build-graph proof does not select them).
    linked = set()
    for p in sorted((Path(root) / 'build/.state/images').glob('*.json')):
        linked.update(u['recipe'] for u in json.loads(p.read_bytes()).get('units', ()))
    for p in sorted((Path(root) / 'build/.state/recipes').glob('*.json')):
        spec = json.loads(p.read_bytes())
        if spec.get('projection') or not spec.get('wrapper', '').endswith('cc.sh') or p.stem not in linked:
            continue
        by_source[spec.get('source')].append(p.stem)
        if spec.get('assembler') == 'genuine_aspsx_verified':
            NATIVE.add(p.stem)
        for d in spec.get('dependencies', ()):
            if d.endswith('.c'):
                by_dep[d].append(p.stem)
    return by_source, by_dep


def normalise_decl(text, name):
    """(ret, params) of a single declaration/definition text."""
    prefix, params = S.split_proto(text, name)
    return S.ret_text(prefix), ' '.join(params.split())


class Solver:
    def __init__(self, root, workers=8, log=print, census=None, facts=None, abi_cache=None):
        self.root = Path(root).resolve()
        self.log = log
        self.workers = workers
        self.census = census or C.Census(self.root, log=log)
        if facts is None:
            scan = A.scan(self.root, abi_cache or self.root / 'build/abi_facts.json.gz', workers, log=log)
            facts = A.Facts(self.root, scan)
        self.facts = facts
        self.by_source, self.by_dep = recipe_index(self.root)
        self.sdk = {}
        # headers the SLUS partition recipes read (through build_slus/include): the prober does not compile
        # SLUS recipes, so an overlay name declared in one of them is held instead of failing the proof
        self.slus_headers = set()
        for p in (self.root / 'build/.state/slus-recipes').glob('*.json'):
            for d in json.loads(p.read_bytes()).get('dependencies', ()):
                if d.startswith('build_slus/include/'):
                    self.slus_headers.add(d[len('build_slus/'):])

    def recipe_source(self, rid):
        return json.loads((self.root / 'build/.state/recipes' / (rid + '.json')).read_bytes())['source']

    def text(self, rel):
        return (self.root / rel).read_bytes().decode('utf-8', 'surrogateescape')

    # ---- planning
    def plan_name(self, info):
        """(definition dict, [site plans with tasks]) for one name; a site plan lists its probe tasks."""
        name = info.name
        row = info.row
        dproto = row.proto
        d_ret, d_params = normalise_decl(dproto, name)
        d_arity = len([p for p in d_params.split(',') if p.strip() and p.strip() != 'void'])
        definition = dict(path=row.definition.path, proto=dproto, ret=d_ret, params=d_params, arity=d_arity)
        w_ret = K.wide_return(d_ret)
        cands = {'D': S.proto(d_ret, name, d_params)}
        if w_ret:
            cands['W'] = S.proto(w_ret, name, d_params)
        def_paths = {d.path for d in info.definitions if not d.static}
        import plan as P
        types = dict(type_headers=[P.include_token(t) for t in row.type_headers], tags=list(row.tags))
        header_sites = [s for s in info.sites if s.in_header]
        plans = []
        for path in sorted(set(info.users) | def_paths):
            is_def = path in def_paths
            site = dict(path=path, is_def=is_def, tasks=[], results={}, detail={})
            plans.append(site)
            rids = self.by_source.get(path, [])
            if not rids:
                base = Path(path).name
                includers = [r for r in self.by_dep.get(path, ())
                             if base in self.text(self.recipe_source(r))]
                if includers:
                    site['blocked'] = 'unprobeable:included_fragment'
                else:
                    site['unbuilt'] = True     # no recipe compiles it: no bytes to keep (natcheck still does)
                continue
            text = self.text(path)
            local = S.local_decls(text, name)
            if any(n > 1 for _, _, n, _ in local):
                site['blocked'] = 'unprobeable:multi_declarator'
                continue
            spans = [(a, b) for a, b, _, _ in local]
            spelling, ctrl_decl = None, None
            if local:
                spelling = normalise_decl(local[0][3], name)
            elif not is_def:
                closure = self.census.corpus.closure(path)
                hs = sorted((closure.index(s.path), s) for s in header_sites if s.path in closure)
                if hs:
                    s0 = hs[0][1]
                    if s0.ndecl > 1:
                        site['blocked'] = 'unprobeable:multi_declarator_header'
                        continue
                    spelling = normalise_decl(s0.text, name)
                    ctrl_decl = S.proto(spelling[0], name, spelling[1]) if spelling[1] else \
                        S.proto(spelling[0], name, '')
            site['spelling'] = None if spelling is None else S.proto(spelling[0], name, spelling[1])
            if spelling is not None:
                params = spelling[1]
                site['arity'] = None if params == '' else \
                    len([p for p in params.split(',') if p.strip() and p.strip() not in ('void', '...')])
            variants = {'control': S.hide_variant(text, name, decl=ctrl_decl)}
            try:
                variants['D'] = S.hide_variant(text, name, spans, cands['D'], **types)
                if 'W' in cands:
                    variants['W'] = S.hide_variant(text, name, spans, cands['W'],
                                                   def_rewrite=(w_ret, d_ret) if is_def else None, **types)
                if spelling is not None and not is_def and spelling[1]:
                    s_ret, s_params = spelling
                    if s_params != d_params:
                        variants['par_D'] = S.hide_variant(text, name, spans, S.proto(s_ret, name, d_params),
                                                           **types)
                    if s_ret != d_ret:
                        variants['ret_D'] = S.hide_variant(text, name, spans, S.proto(d_ret, name, s_params))
                    if w_ret and s_ret != w_ret:
                        variants['ret_W'] = S.hide_variant(text, name, spans, S.proto(w_ret, name, s_params))
            except ValueError as exc:
                site['blocked'] = 'unprobeable:' + str(exc)[:80]
                continue
            for rid in rids:
                for key, vtext in variants.items():
                    site['tasks'].append(dict(key='%s|%s|%s|%s' % (name, path, rid, key), recipe=rid,
                                              text=vtext))
                if rid in NATIVE:      # proxy calibration: the unmodified text through the same pipeline
                    site['tasks'].append(dict(key='%s|%s|%s|%s' % (name, path, rid, 'production'), recipe=rid,
                                              text=None))
            site['recipes'] = rids
        return definition, plans

    # ---- solving
    def solve(self, names, out=None):
        infos = [self.census.info(n) for n in names]
        work = []
        decisions = []
        for info in infos:
            hold = None
            if info.owner is None:
                hold = info.row.reason if info.row is not None else 'no_definition'
            elif len({d.path for d in info.definitions if not d.static}) > 1:
                hold = 'multiple_definitions'
            elif info.header_users:
                hold = 'header_reference:' + info.header_users[0]
            elif info.owner not in self.slus_headers and any(
                    s.in_header and s.path in self.slus_headers for s in info.sites):
                hold = 'slus_consumer_unprobed:' + next(s.path for s in info.sites
                                                         if s.in_header and s.path in self.slus_headers)
            if hold:
                decisions.append(K.decide(info.name, info.owner, dict(path=None, proto=None, ret='', arity=None),
                                          [], self.facts.summary(info.name), hold=hold))
                continue
            definition, plans = self.plan_name(info)
            work.append((info, definition, plans))
        tasks = [t for _, _, plans in work for s in plans for t in s['tasks']]
        self.log('probing %d names: %d compiles over %d TU sites' % (
            len(work), len(tasks), sum(len(p) for _, _, p in work)))
        results = {}
        if tasks:
            t0 = time.monotonic()
            pool = S.Workers(self.root, min(self.workers, max(1, len(tasks))))
            try:
                for t, r in zip(tasks, pool.map(tasks)):
                    results[t['key']] = r
            finally:
                pool.close()
            self.log('probes: %d compiles, %.0f s wall, %.0f s compile' % (
                len(tasks), time.monotonic() - t0, pool.seconds))
        for info, definition, plans in work:
            sites = []
            for s in plans:
                if s.get('blocked') or s.get('unbuilt'):
                    sites.append(s)
                    continue
                calibrated, res, detail = True, {}, {}
                for rid in s['recipes']:
                    get = lambda k: results['%s|%s|%s|%s' % (info.name, s['path'], rid, k)]
                    ctrl = get('control')
                    if rid in NATIVE:
                        prod = get('production')
                        if 'error' in prod:
                            calibrated = False
                            detail['control'] = prod['error'][-300:]
                            continue
                    else:
                        prod = dict(blob=(self.root / 'build/obj' / (rid + '.o')).read_bytes())
                    if 'error' in ctrl or A.object_difference(prod['blob'], ctrl['blob']) is not None:
                        calibrated = False
                        detail['control'] = ctrl.get('error', '')[-300:] or \
                            A.object_difference(prod['blob'], ctrl['blob'])
                        continue
                    for t in s['tasks']:
                        k = t['key'].rsplit('|', 1)[1]
                        if k in ('control', 'production') or not t['key'].startswith('%s|%s|%s|' % (info.name, s['path'], rid)):
                            continue
                        diff = S.compare(ctrl, get(k))
                        verdict = 'neutral' if diff is None else 'error' if diff.get('kind') == 'error' else 'changed'
                        if res.get(k) in (None, 'neutral'):
                            res[k] = verdict
                        if diff is not None:
                            detail[k] = diff
                site = {k: v for k, v in s.items() if k != 'tasks'}
                site.update(calibrated=calibrated, results=res, detail=detail)
                sites.append(site)
            dec = K.decide(info.name, info.owner, definition, sites, self.facts.summary(info.name))
            if self.sdk and info.name in self.sdk and (info.owner or '').startswith('include/sdk/'):
                dec['sdk_prototype'] = self.sdk[info.name]       # ranking evidence only; bytes decide
            dec['site_results'] = [dict(path=s['path'], is_def=s.get('is_def'), spelling=s.get('spelling'),
                                        blocked=s.get('blocked'), calibrated=s.get('calibrated'),
                                        results=s.get('results'),
                                        detail={k: (v if not isinstance(v, dict) or v.get('kind') != 'error'
                                                    else dict(v, detail=v['detail'][-240:]))
                                                for k, v in (s.get('detail') or {}).items()})
                                   for s in sites]
            decisions.append(dec)
        return decisions


def record_floors(root, decisions_path, txn_path=None):
    """Upsert ledger/prototype_floors.jsonl: refused names not applied, and the per-site floors of names
    applied partially (one record per name; a later solve replaces it)."""
    data = json.loads(decisions_path.read_text())
    txn = json.loads(txn_path.read_text()) if txn_path else dict(names={})
    applied = txn.get('names', {}) if txn.get('verdict') == 'PASS' else {}
    ledger = root / FLOORS
    old = K.load_floors(ledger)
    evidence = dict(tree=data.get('tree'), tool='tools/typing/sig_solver.py', header=data.get('header'))
    n_new = 0
    for d in data['decisions']:
        name = d['name']
        if name in applied:
            if applied[name]['status'] != 'partial':
                old.pop(name, None)
                continue
            sites = [f for f in txn.get('floor_sites', []) if f['name'] == name]
            reasons = {f['reason'] for f in sites}
            floor = next((c for c in K.FLOOR_ORDER + ('pointer_kind',) if c in reasons), 'return_width')
            rec = K.floor_record(dict(d, status='partial', floor_class=floor,
                                      blocking=[dict(path=f['path'], is_def=False, spelling=f.get('spelling'),
                                                     reason=f['reason'], declaration=f.get('declaration'))
                                                for f in sites]), evidence)
        elif d['status'] == 'refused' and d.get('floor_class') != 'name_hold':
            # name holds (no owner, header references, unprobed SLUS consumers...) are tool limits, not
            # floors: they stay re-triable
            rec = K.floor_record(d, evidence)
        else:
            continue
        old[name] = rec
        n_new += 1
    ledger.parent.mkdir(parents=True, exist_ok=True)
    ledger.write_text(''.join(json.dumps(old[k], sort_keys=True, default=str) + '\n' for k in sorted(old)))
    print('%s: %d records (%d written from %s)' % (FLOORS, len(old), n_new, decisions_path))
    return 0


def tree_sha(root):
    res = subprocess.run(['git', '-C', str(root), 'rev-parse', 'HEAD'], capture_output=True, text=True)
    return res.stdout.strip() or None


def slug(header):
    return header[len('include/'):-2].replace('/', '__') if header.startswith('include/') else header


def owning_headers(census, prefix='include/'):
    """[(header, conflicting names, declaration sites)] for owning headers under a prefix, most names first."""
    rows = defaultdict(lambda: [0, 0])
    for n, r in census.plan.functions.items():
        if '@' in n or r.status != 'header' or not r.header.startswith(prefix):
            continue
        info = census.info(n)
        if info.conflict:
            rows[r.header][0] += 1
            rows[r.header][1] += len(info.sites)
    return sorted(((h, a, b) for h, (a, b) in rows.items()), key=lambda x: (-x[1], x[0]))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest='mode', required=True)
    sp = sub.add_parser('solve')
    sp.add_argument('--root', type=Path, default=HERE.parents[2])
    sp.add_argument('--header', nargs='+', required=True,
                    help='one or more owning headers (one census for all; DIR/<slug>/ per header when several)')
    sp.add_argument('--names', nargs='*')
    sp.add_argument('--all-names', action='store_true', help='every owned name, not only conflicting ones')
    sp.add_argument('--retry-floors', action='store_true')
    sp.add_argument('--out', type=Path, required=True)
    sp.add_argument('--workers', type=int, default=8)
    sp.add_argument('--abi-cache', type=Path)
    sp.add_argument('--sdk-evidence', type=Path,
                    help='Ghidra PsyQ-signature JSON lines: evidence rows for include/sdk names only')
    hp = sub.add_parser('headers', help='owning headers with conflicting names under a prefix (batch planning)')
    hp.add_argument('--root', type=Path, default=HERE.parents[2])
    hp.add_argument('--prefix', default='include/')
    fp = sub.add_parser('floors', help='record refusals / applied per-site floors in the floors ledger')
    fp.add_argument('--root', type=Path, default=HERE.parents[2])
    fp.add_argument('--decisions', type=Path, required=True)
    fp.add_argument('--txn', type=Path, help='txn.json of the applied transaction (partial names, applied set)')
    ap_apply = sub.add_parser('apply', help='see tools/typing/sig_txn.py')
    ap_apply.add_argument('rest', nargs=argparse.REMAINDER)
    args = ap.parse_args(argv)
    if args.mode == 'apply':
        import sig_txn
        return sig_txn.main(args.rest)
    if args.mode == 'floors':
        return record_floors(args.root.resolve(), args.decisions, args.txn)
    if args.mode == 'headers':
        census = C.Census(args.root.resolve(), log=lambda m: print(m, file=sys.stderr))
        for h, n, sites in owning_headers(census, args.prefix):
            print('%s\t%d\t%d\t%s' % (h, n, sites, slug(h)))
        return 0
    if not 1 <= args.workers <= 8:
        ap.error('between 1 and 8 workers on this host')
    root = args.root.resolve()
    args.out.mkdir(parents=True, exist_ok=True)
    logf = open(args.out / 'solve.log', 'a')

    def log(msg):
        line = time.strftime('%H:%M:%S ') + msg
        print(line, flush=True)
        logf.write(line + '\n')
        logf.flush()

    started = time.monotonic()
    solver = Solver(root, args.workers, log, abi_cache=args.abi_cache)
    solver.sdk = C.sdk_evidence(args.sdk_evidence)
    floors = K.load_floors(root / FLOORS)
    sha = tree_sha(root)
    for header in args.header:
        out = args.out if len(args.header) == 1 else args.out / slug(header)
        out.mkdir(parents=True, exist_ok=True)
        names = args.names or solver.census.names_owned_by(header)
        chosen, skipped = [], []
        for n in names:
            info = solver.census.info(n)
            if not args.names and not args.all_names and not info.conflict:
                continue
            if n in floors and not args.retry_floors:
                skipped.append(n)
                continue
            chosen.append(n)
        log('%s: %d names to solve (%d recorded floors skipped)' % (header, len(chosen), len(skipped)))
        decisions = solver.solve(chosen)
        (out / 'decisions.json').write_text(json.dumps(dict(header=header, tree=sha, decisions=decisions),
                                                       indent=1, default=str) + '\n')
        with open(out / 'floors.jsonl', 'w') as fh:
            for d in decisions:
                if d['status'] == 'refused' and d.get('floor_class') != 'name_hold':
                    fh.write(json.dumps(K.floor_record(d, dict(tree=sha, tool='tools/typing/sig_solver.py')),
                                        sort_keys=True, default=str) + '\n')
        uni = [d for d in decisions if d['status'] == 'unified']
        log('%s: decided %d: unified %d (D %d, W %d), refused %d %s; %.0f s' % (
            header, len(decisions), len(uni), sum(d['choice'] == 'D' for d in uni),
            sum(d['choice'] == 'W' for d in uni), len(decisions) - len(uni),
            _count(d.get('floor_class') for d in decisions if d['status'] == 'refused'),
            time.monotonic() - started))
    return 0


def _count(xs):
    out = defaultdict(int)
    for x in xs:
        out[x] += 1
    return dict(out)


if __name__ == '__main__':
    sys.exit(main())
