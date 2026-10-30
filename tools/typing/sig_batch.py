#!/usr/bin/env python3
"""Batch transactions of the signature-consensus solver: many owning headers, one proof, bisection.

    sig_batch.py (--batch DIR | --decisions D.json...) --out DIR [--scope PREFIX...] [--natcheck PATH]
                 [--names N...] [--no-partial] [--no-repair] [--dry-run] [--no-proof] [--workers 8]
                 [--max-proofs 40] [--record-floors] [--affected tools/build/affected.py]

`--batch DIR` takes every DIR/<slug>/decisions.json of one `sig_solver.py solve --header H1 H2 ...` run.
Every header's transaction (tools/typing/sig_txn.py Transaction.plan_edits: owner prototypes, removed
declarations, owner includes, width-rule narrowing, floor markers, visibility repairs) is planned over the
same committed baseline and the plans are rendered together (render(): spans of every header applied in
one pass, so a consumer TU or a header edited by several transactions gets all of them).  Batch-level
checks before any compile: overlapping spans hold the later header's names; a TU that keeps a floor
declaration of one header's name never gains a header that reaches that owner; with --scope, an edit to a
header outside the prefixes (other than the batch's owners) holds the names that make it.

Proof: ONE tools/build/affected.py `prove` over the union of edited files (every production recipe whose
closure or own source holds an edited file, placement copies, image relinks), then ONE natcheck.  On a
failure the culprits are found by bisection (settle): names the failing recipes attribute (sig_txn
culprits rules: a conflicting declaration names its name; otherwise the names whose edits reach the
recipe) are separated from the rest; the unattributed names are proved first, then the attributed ones by
halves (by header first, then by name) until each failing name is isolated.  A single attributed name, or
a single name that fails on top of a proven set, is backed off.  Every accepted state is one whole-set
PASS proof of exactly the written files (half-proofs are attribution only); recipes whose edited inputs
are unchanged since an earlier byte-identical compile in the run are reused (affected.prove reuse).
A visibility repair whose path a failing recipe compiles is withdrawn first (the name then holds as
before); a TU whose new owner include brings a conflicting declaration stops including that owner.

Writes DIR/batch.json (proof log, back-offs, timings, yields), DIR/batch.patch, and per header
DIR/<slug>/txn/txn.json + txn.patch in sig_txn.py receipt form (so `sig_solver.py floors --txn` and the
reviewer checks are unchanged).  --record-floors upserts ledger/prototype_floors.jsonl for every header
after a PASS.  Requires src/ and include/ committed and build/obj current for HEAD.  Tracked files are
restored on --dry-run, an error or an interrupt.
"""
from __future__ import annotations

import argparse
from collections import defaultdict
import difflib
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import time

HERE = Path(__file__).resolve()
TOOLS = HERE.parents[1]
for p in (str(HERE.parent), str(TOOLS), str(TOOLS / 'headers'), str(TOOLS / 'lint')):
    if p not in sys.path:
        sys.path.insert(0, p)

import cscan  # noqa: E402
import sig_census as C  # noqa: E402
import sig_txn as T  # noqa: E402

LAYOUT_INLINE = T.LAYOUT_INLINE


def slug(header):
    return header[len('include/'):-2].replace('/', '__') if header.startswith('include/') else header


# ------------------------------------------------------------------------------------------ planning

class Batch:
    """The transactions of several owning headers over one baseline and one census."""

    def __init__(self, root, datas, census, log=print, partial=True, repair=True, scope=None, names=None):
        self.root = Path(root).resolve()
        self.log = log
        self.census = census
        self.originals = {}
        self.txns = {}
        self.cands = {}          # name -> owning header
        self.decision = {}       # name -> candidate decision (Transaction.candidates form)
        self.scope = tuple(scope or ())
        for data in datas:
            H = data['header']
            if H in self.txns:
                log('duplicate decisions for %s: ignored' % H)
                continue
            txn = T.Transaction(self.root, H, data['decisions'], census=census, log=log, partial=partial,
                                originals=self.originals, repair=repair)
            self.txns[H] = txn
            for n, d in txn.candidates(set(names) if names else None).items():
                if n in self.cands:
                    log('%s: decided under %s and %s; kept the first' % (n, self.cands[n], H))
                    continue
                self.cands[n] = H
                self.decision[n] = d

    def text(self, rel):
        return next(iter(self.txns.values())).text(rel)

    def state(self):
        """Version of the proof-learned state (no_include / no_repair / no_type_include): plans are a
        function of it."""
        return tuple((H, len(t.no_include), len(t.no_repair), len(t.no_type_include))
                     for H, t in sorted(self.txns.items()))

    def _parts(self, names):
        floor_map = {}
        parts = []
        for _ in range(4):
            parts = []
            for H, txn in self.txns.items():
                chosen = {n: self.decision[n] for n in sorted(names) if self.cands[n] == H}
                if not chosen:
                    continue
                txn.batch_names = set(names)
                txn.batch_floor_tus = floor_map
                parts.append((txn, txn.plan_edits(chosen)))
            new_map = defaultdict(set)
            for txn, ep in parts:
                for f in ep['report']['floors']:
                    new_map[f['path']].add(txn.header)
            new_map = dict(new_map)
            if new_map == floor_map:
                break
            floor_map = new_map
        return parts

    def plan(self, names):
        """(texts, {header: report}, file_names, held {name: why}) for a set of candidate names."""
        names = set(names)
        held = {}
        while True:
            parts = self._parts(names)
            new = {n: why for txn, ep in parts for n, why in ep['report']['held'].items()}
            if new:
                # re-plan without them: the other headers' include checks treat batch names as unified
                held.update(new)
                names -= set(new)
                continue
            parts = [(t, ep) for t, ep in parts if ep['report']['names']]
            if not parts:
                return {}, {}, {}, held
            new = self._overlaps(parts)
            if not new:
                texts, file_names = T.render(parts, self.text)
                new = self._out_of_scope(texts, file_names)
            if not new:
                for t, ep in parts:
                    ep['report']['file_names'] = {p: ns for p, ns in file_names.items()
                                                  if set(ns) & set(ep['report']['names'])}
                return texts, {t.header: ep['report'] for t, ep in parts}, file_names, held
            held.update(new)
            names -= set(new)

    def _overlaps(self, parts):
        """Names to hold because their spans overlap another header's spans in one file."""
        by_path = defaultdict(list)
        for txn, ep in parts:
            for path, es in ep['edits'].items():
                by_path[path].append((txn, ep, [e for e in es if e[0] != 'floor']))
        out = {}
        for path, rows in by_path.items():
            if len(rows) < 2:
                continue
            seen = []
            for txn, ep, spans in rows:
                trial = sorted(set(seen + spans))
                try:
                    T.apply_spans(self.text(path), trial)
                    seen += spans
                except ValueError:
                    for n in ep.get('file_names', {}).get(path, ()):
                        out[n] = 'batch_overlap:' + path
        return out

    def _out_of_scope(self, texts, file_names):
        if not self.scope:
            return {}
        out = {}
        for path in texts:
            if path.endswith('.h') and path not in self.txns and not path.startswith(self.scope):
                for n in file_names.get(path, ()):
                    out[n] = 'out_of_scope_header:' + path
        return out


CONFLICT = T.CONFLICT


LOCATION = re.compile(r"(?:^|\s)(?:build_ovl/|build_slus/)?(include/[\w/.-]+\.h):\d+: (?:previous declaration|"
                      r"conflicting types)", re.M)


def batch_culprits(proof, file_names, root, names, reports, txns):
    """(names named by the compiler, names to bisect, [(header, TU) that must stop including the header],
    [(header, type header) the owner header must not gain]) for a failed proof: sig_txn culprits rules, with
    the conflicting declaration's owner header found among the TU's new includes, and a conflict located in
    a type header an owner header newly includes refused at the owner header."""
    certain, drop, stop, refuse = set(), set(), [], []
    for rid, rec in proof.get('recipes', {}).items():
        if rec.get('verdict') == 'PASS':
            continue
        own = T.failing_source(rec, root)
        error = rec.get('error', '')
        named = set(CONFLICT.findall(error))
        direct = (named | set(T.ARITY.findall(error))) & names
        if direct:
            certain |= direct
            continue
        if named:
            located = set(LOCATION.findall(error))
            hs = [(H, x) for H, rep in reports.items() for x in rep.get('header_includes', ()) if x in located]
            if hs:
                refuse += hs
                continue
        if named:
            hs = [H for H, rep in reports.items() if own in rep.get('includes_added', ())]
            declaring = [H for H in hs if any(n in txns[H].census.corpus.text(H) for n in named)]
            if declaring or hs:
                stop += [(H, own) for H in (declaring or hs)]
                continue
        # the names spelled on the lines the compiler reports (the call whose declaration changed)
        on_lines = set()
        for path, line in ERROR_AT.findall(error):
            if rec.get('family') == 'slus':
                path = T.slus_path(root, path)
            on_lines |= set(cscan.IDENT.findall(_line(root, path, int(line)))) & names
        if on_lines:
            drop |= on_lines
            continue
        hit = set(file_names.get(own, ()))
        if not hit:
            for d in _deps(root, rid):
                hit |= set(file_names.get(d, ()))
            # a TU reached only through an edited header changes only through the names it mentions
            census = next(iter(txns.values())).census if txns else None
            if census is not None and own in census.corpus.c_files:
                hit = (hit & census.mentions(own)) or hit
        drop |= hit & names
    return certain, drop, stop, refuse


ERROR_AT = re.compile(r'(?:^|\s)(?:build_ovl/|build_slus/)?((?:src|include)/[\w/.-]+\.[ch]):(\d+): (?!warning)', re.M)


def _line(root, path, number):
    try:
        lines = (Path(root) / path).read_text(errors='replace').splitlines()
    except OSError:
        return ''
    return lines[number - 1] if 0 < number <= len(lines) else ''


def _deps(root, rid):
    for folder in ('recipes', 'slus-recipes'):
        spec = Path(root) / 'build/.state' / folder / (rid + '.json')
        if spec.is_file():
            return [T.slus_path(root, d[len('build_slus/'):]) if d.startswith('build_slus/') else d
                    for d in json.loads(spec.read_text()).get('dependencies', [])]
    return []


def split(names, cands):
    """Two halves of a name set: by owning header when it spans several, else by name."""
    by_h = defaultdict(list)
    for n in sorted(names):
        by_h[cands[n]].append(n)
    if len(by_h) > 1:
        a, b = [], []
        for H, ns in sorted(by_h.items(), key=lambda kv: (-len(kv[1]), kv[0])):
            (a if len(a) <= len(b) else b).extend(ns)
        return set(a), set(b)
    ns = sorted(names)
    return set(ns[:len(ns) // 2]), set(ns[len(ns) // 2:])


# ------------------------------------------------------------------------------------------- runner

class Runner:
    """Write / prove / bisect over one Batch.  `prover(files, texts) -> report` and `natcheck() -> report`
    are injectable (tests); by default the root's affected.prove (in process) and the port natcheck."""

    def __init__(self, root, batch, out, *, prover=None, natcheck=None, log=print, no_proof=False,
                 max_proofs=40, refresh=True):
        self.root = Path(root).resolve()
        self.batch = batch
        self.out = out
        self.log = log
        self.prover = prover
        self.natcheck = natcheck
        self.no_proof = no_proof
        self.max_proofs = max_proofs
        self.refresh = refresh
        self.written = {}
        self.dropped = {}        # name -> why
        self.backoffs = []
        self.fail_memo = {}      # (names, state) -> (proof, attributed)
        self.pass_memo = {}      # (names, state) -> (texts, reports, file_names, proof)
        self.proofs = []         # one row per proof run
        self.last = None         # (names, state) of the files on disk
        self.best = None         # (names, pass_memo entry) of the largest proven set
        self._debt = {}

    # ---- files
    def restore(self):
        for rel in list(self.written):
            T.write(self.root, rel, self.batch.originals[rel])
        self.written = {}
        self.last = None

    def write_set(self, texts):
        self.restore()
        for rel, t in texts.items():
            self.batch.text(rel)
            T.write(self.root, rel, t)
            self.written[rel] = t
        if self.refresh and (self.root / LAYOUT_INLINE).is_file():
            self.batch.text(LAYOUT_INLINE)
            T.refresh_layout(self.root, self.log)
            now = (self.root / LAYOUT_INLINE).read_text()
            if now != self.batch.originals[LAYOUT_INLINE]:
                self.written[LAYOUT_INLINE] = now

    def debt(self, rel, text):
        key = (rel, hashlib.sha1((text or '').encode('utf-8', 'surrogateescape')).hexdigest())
        if key not in self._debt:
            self._debt[key] = T.debt_counts(rel, text)
        return self._debt[key]

    def drop(self, n, why, **extra):
        if n not in self.dropped:
            self.dropped[n] = why
            self.backoffs.append(dict(round=len(self.proofs), name=n, header=self.batch.cands.get(n), why=why,
                                      **extra))

    # ---- one attempt
    def attempt(self, names):
        """('PASS' | 'FAIL' | 'EMPTY', proof, attributed names, effective names) for one name set."""
        names = set(names) - set(self.dropped)
        while True:
            if not names:
                return 'EMPTY', None, set(), names
            key = (frozenset(names), self.batch.state())
            if key in self.fail_memo:
                proof, attributed = self.fail_memo[key]
                return 'FAIL', proof, attributed, names
            if key in self.pass_memo:
                texts = self.pass_memo[key][0]
                if self.last != key:
                    self.write_set(texts)
                    self.last = key
                return 'PASS', self.pass_memo[key][3], set(), names
            texts, reports, file_names, held = self.batch.plan(names)
            for n, why in sorted(held.items()):
                self.drop(n, why)
            names -= set(held)
            if not texts:
                for n in sorted(names):
                    self.drop(n, 'no_edit')
                return 'EMPTY', None, set(), set()
            self.write_set(texts)
            rises = {rel for rel, t in texts.items() if rel.endswith(('.c', '.h'))
                     and any(v > self.debt(rel, self.batch.originals[rel]).get(k, 0)
                             for k, v in self.debt(rel, t).items()
                             if not (rel.endswith('.h') and k == 'local_externs'))}
            if rises:
                bad = {n for rel in rises for n in file_names.get(rel, ())} & names
                for n in sorted(bad):
                    self.drop(n, 'debt_rise', files=sorted(rises)[:10])
                self.log('debt rise in %s: back off %s' % (sorted(rises)[:5], sorted(bad)))
                names -= bad
                if bad:
                    continue
            key = (frozenset(names), self.batch.state())
            if self.no_proof:
                self.pass_memo[key] = (texts, reports, file_names, None)
                self.last = key
                return 'PASS', None, set(), names
            if len(self.proofs) >= self.max_proofs:
                raise BudgetExhausted()
            proof = self.prove(texts, names)
            self.last = key
            if proof.get('verdict') == 'PASS':
                self.pass_memo[key] = (texts, reports, file_names, proof)
                if self.best is None or len(names) > len(self.best[0]):
                    self.best = (set(names), self.pass_memo[key])
                return 'PASS', proof, set(), names
            certain, drop, stop, refuse = batch_culprits(proof, file_names, self.root, names, reports,
                                                         self.batch.txns)
            if not certain and self.withdraw_repairs(proof, reports):
                continue
            grew = False
            for H, tu in stop:
                if tu not in self.batch.txns[H].no_include:
                    self.batch.txns[H].no_include.add(tu)
                    grew = True
            for H, x in refuse:
                if x not in self.batch.txns[H].no_type_include:
                    self.batch.txns[H].no_type_include.add(x)
                    grew = True
            if certain:
                # the compiler names them (conflicting types / argument count): no bisection needed
                for n in sorted(certain):
                    self.drop(n, 'proof', named_by_compiler=True, recipes=self.proofs[-1]['failing'])
                self.log('back off (named by the compiler) %s' % ', '.join(sorted(certain)))
                names -= certain
                continue
            if grew and not drop:
                self.log('stop including the owner header in: %s; owner type includes refused: %s' % (
                    ', '.join('%s<-%s' % s for s in stop)[:300], ', '.join('%s:%s' % r for r in refuse)[:300]))
                continue
            self.fail_memo[(frozenset(names), self.batch.state())] = (proof, drop)
            return 'FAIL', proof, drop, names

    def withdraw_repairs(self, proof, reports):
        """Refuse the visibility repairs a failing recipe compiles (its own source or a repaired header in
        its dependencies); True when any was withdrawn (the plan changes, names stay)."""
        repaired = {}
        for H, rep in reports.items():
            for r in rep.get('repairs', ()):
                repaired.setdefault(r['path'], set()).add(H)
        if not repaired:
            return False
        hit = set()
        for rid, rec in proof.get('recipes', {}).items():
            if rec.get('verdict') == 'PASS':
                continue
            own = T.failing_source(rec, self.root)
            paths = {own} | {d for d in _deps(self.root, rid) if d.endswith('.h')}
            hit |= paths & set(repaired)
        new = False
        for path in sorted(hit):
            for H in repaired[path]:
                if path not in self.batch.txns[H].no_repair:
                    self.batch.txns[H].no_repair.add(path)
                    new = True
        if new:
            self.log('visibility repair refused by the proof: %s' % ', '.join(sorted(hit))[:300])
        return new

    def prove(self, texts, names):
        files = sorted(r for r in texts if r.endswith(('.c', '.h')))
        t0 = time.monotonic()
        # the written set: the plan texts plus the refreshed layout ledger (placement-copy reuse keys)
        proof = self.prover(files, dict(self.written))
        bad = [dict(recipe=r, source=v.get('source'), verdict=v['verdict'],
                    why=v.get('difference') or (v.get('cause') or v.get('error', ''))[-300:])
               for r, v in proof.get('recipes', {}).items() if v['verdict'] != 'PASS'][:20]
        row = dict(n=len(self.proofs) + 1, names=len(names), files=len(files), verdict=proof.get('verdict'),
                   counts=proof.get('counts'), recipes=len(proof.get('recipes', {})), reused=proof.get('reused', 0),
                   seconds=round(time.monotonic() - t0, 1), failing=bad[:8])
        self.proofs.append(row)
        self.log('proof %d: %d names, %d files -> %s %s (%d recipes, %d reused, %.0f s)' % (
            row['n'], len(names), len(files), row['verdict'], row['counts'], row['recipes'], row['reused'],
            row['seconds']))
        for f in bad[:4]:
            self.log('  failing %s %s: %s' % (f['verdict'], T.failing_source(f, self.root), str(f['why'])[-200:]))
        return proof

    # ---- bisection
    def settle(self, good, extra):
        """Largest set found that passes: `good` (proven, or empty) plus what survives of `extra`."""
        extra = set(extra) - set(self.dropped) - set(good)
        if not extra:
            return set(good)
        status, proof, attributed, eff = self.attempt(set(good) | extra)
        if status in ('PASS', 'EMPTY'):
            return eff
        extra, good = eff - set(good), set(good) & eff
        if not extra:
            return good
        attributed &= extra
        if len(extra) == 1 or len(attributed) == 1:
            culprit = attributed or extra
            for n in sorted(culprit):
                self.drop(n, 'proof', recipes=self.proofs[-1]['failing'] if self.proofs else [])
            self.log('back off %s' % ', '.join(sorted(culprit)))
            return self.settle(good, extra - culprit)
        if attributed and attributed != extra:
            return self.settle(self.settle(good, extra - attributed), attributed)
        a, b = split(attributed or extra, self.batch.cands)
        self.log('bisect %d names: %d + %d' % (len(attributed or extra), len(a), len(b)))
        return self.settle(self.settle(good, a), b)

    def run(self):
        """(final proven name set, its (texts, reports, file_names, proof), natcheck report); the files on
        disk are that set's proven texts."""
        names = set(self.batch.cands)
        nat = None
        for _ in range(4):
            try:
                names = self.settle(set(), names)
                entry = None
                if names:
                    status, proof, _, names = self.attempt(names)    # disk = this set's proven texts
                    if status != 'PASS':
                        continue
                    entry = self.pass_memo[(frozenset(names), self.batch.state())]
            except BudgetExhausted:
                self.log('proof budget (%d) exhausted' % self.max_proofs)
                if self.best is None:
                    self.restore()
                    names, entry = set(), None
                else:
                    names, entry = self.best
                    self.write_set(entry[0])
                for n in sorted(set(self.batch.cands) - set(self.dropped) - names):
                    self.drop(n, 'proof_budget')
                return names, entry, None
            if not names or self.no_proof or not self.natcheck:
                return names, entry, nat
            nat = self.natcheck()
            fails = nat.get('unit_failures', []) + nat.get('adaptation_errors', [])
            if not fails:
                return names, entry, nat
            bad = T.native_culprits(nat, entry[2], names)
            if not bad:
                self.log('natcheck: no culprit for %d failures: restoring' % len(fails))
                break
            for n in sorted(bad):
                self.drop(n, 'natcheck', units=[u.get('unit') for u in nat.get('unit_failures', [])][:10])
            names -= bad
        self.restore()
        return set(), None, nat


class BudgetExhausted(Exception):
    pass


# ---------------------------------------------------------------------------------- default prover

def load_affected(path):
    spec = importlib.util.spec_from_file_location('affected_batch', str(path))
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


def include_targets(corpus, rel, text):
    out = set()
    for d in cscan.scan(text or '').directives:
        if d.kind == 'include' and d.arg.startswith('"'):
            r = corpus.resolve_include(rel, d.arg.split('"')[1])
            if r:
                out.add(r)
    return out


class Prover:
    """affected.prove in process over one graph, with per-recipe reuse keyed by edited input texts."""

    def __init__(self, root, affected, census, originals, workers=8, log=print):
        self.root = Path(root).resolve()
        self.mod = load_affected(affected)
        self.graph = self.mod.Graph(self.root)
        self.corpus = census.corpus
        self.originals = originals
        self.workers = workers
        self.log = log
        self.reuse = {}

    def __call__(self, files, texts):
        g = self.graph
        by_dep = g.by_dep()
        digest = {f: hashlib.sha256(t.encode('utf-8', 'surrogateescape')).hexdigest() for f, t in texts.items()}
        new_inc = {f: include_targets(self.corpus, f, t) - include_targets(self.corpus, f, self.originals.get(f))
                   for f, t in texts.items() if f.endswith(('.c', '.h'))}
        reach = defaultdict(set)
        for f in files:
            hits = set(by_dep.get(g.real(f), ())) | (g.own_recipes(f) if f.endswith('.c') else set())
            for rid in hits:
                reach[rid].add(f)
        layout = digest.get(LAYOUT_INLINE) or 'base'

        def key(rid):
            ks = set(reach.get(rid, ()))
            todo = list(ks)
            while todo:
                f = todo.pop()
                for x in new_inc.get(f, ()):
                    for y in [x] + list(self.corpus.closure(x)):
                        if y in digest and y not in ks:
                            ks.add(y)
                            todo.append(y)
            spec = g.recipes[rid]
            parts = [rid] + ['%s=%s' % (f, digest[f]) for f in sorted(ks)]
            if spec.get('projection'):
                parts.append('layout=' + layout)
            return hashlib.sha256('\n'.join(parts).encode()).hexdigest()
        return self.mod.prove(self.root, files, workers=self.workers, graph=g, reuse=self.reuse, reuse_key=key,
                              log=lambda m: self.log('  ' + m))


# ------------------------------------------------------------------------------------------- main

def load_decisions(args):
    paths = list(args.decisions or [])
    if args.batch:
        paths += sorted(args.batch.glob('*/decisions.json')) or [args.batch / 'decisions.json']
    datas = []
    for p in paths:
        data = json.loads(Path(p).read_text())
        data['_path'] = str(p)
        datas.append(data)
    return datas


def write_receipts(out, batch, runner, final, entry, verdict, natcheck, timings, tree):
    texts, reports, file_names, proof = entry if entry else ({}, {}, {}, None)
    written = runner.written if final else {}
    if proof is not None and natcheck is not None:
        proof = dict(proof, natcheck=dict(unit_failures=len(natcheck.get('unit_failures', [])),
                                          adaptation_errors=len(natcheck.get('adaptation_errors', [])),
                                          contract_errors=len(natcheck.get('contract_errors', []))))
    per_header = {}
    for H, txn in batch.txns.items():
        rep = reports.get(H, dict(header=H, names={}, floors=[], respelled=[], includes_added=[], repairs=[]))
        files = sorted(p for p, ns in file_names.items() if set(ns) & set(rep.get('names', {})))
        if H in written and rep.get('names'):
            files = sorted(set(files) | {H})
        bo = [b for b in runner.backoffs if b.get('header') == H]
        receipt, patch, yields, floors, rl, re_, rh = T.build_receipt(
            txn, rep, written if rep.get('names') else {}, proof if rep.get('names') else None, bo,
            len(runner.proofs), tree, files=files)
        d = out / slug(H) / 'txn'
        d.mkdir(parents=True, exist_ok=True)
        (d / 'txn.json').write_text(json.dumps(receipt, indent=1, default=str) + '\n')
        (d / 'txn.patch').write_text(patch)
        per_header[H] = dict(candidates=sum(1 for n in batch.cands.values() if n == H),
                             unified=receipt['unified'], partial=receipt['partial'],
                             local_declarations_removed=rl, empty_declarations_removed=re_,
                             header_declarations_removed=rh, floor_sites=len(floors),
                             backoffs=len(bo), files=len(receipt['files']))
    patch, yields = [], defaultdict(int)
    for rel in sorted(written):
        old, new = batch.originals[rel], written[rel]
        patch.extend(difflib.unified_diff((old or '').splitlines(True), new.splitlines(True), 'a/' + rel, 'b/' + rel))
        if rel.endswith(('.c', '.h')):
            b, a = T.debt_counts(rel, old), T.debt_counts(rel, new)
            for k in set(b) | set(a):
                yields[k + '_delta'] += a.get(k, 0) - b.get(k, 0)
    (out / 'batch.patch').write_text(''.join(patch))
    why = defaultdict(int)
    for b in runner.backoffs:
        why[b['why'].split(':')[0]] += 1
    rec = dict(tree=tree, verdict=verdict, headers=per_header, candidates=len(batch.cands), applied=len(final),
               backoffs_by_reason=dict(sorted(why.items(), key=lambda kv: -kv[1])), backoffs=runner.backoffs,
               proofs=runner.proofs, natcheck=None if natcheck is None else dict(
                   unit_failures=len(natcheck.get('unit_failures', [])),
                   adaptation_errors=len(natcheck.get('adaptation_errors', []))),
               files=sorted(written), debt=dict(yields), timings=timings,
               repairs=[dict(r, header=H) for H, rep in reports.items() for r in rep.get('repairs', ())])
    (out / 'batch.json').write_text(json.dumps(rec, indent=1, default=str) + '\n')
    return rec


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=HERE.parents[2])
    src = ap.add_mutually_exclusive_group(required=True)
    src.add_argument('--batch', type=Path, help='a `sig_solver.py solve --header H1 H2 ...` output folder')
    src.add_argument('--decisions', type=Path, nargs='+')
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--names', nargs='*')
    ap.add_argument('--scope', nargs='*', default=[], help='header prefixes a batch may edit besides its owners')
    ap.add_argument('--affected', type=Path, help="tools/build/affected.py (default: the root's own)")
    ap.add_argument('--natcheck', type=Path, help='port natcheck.py: once after the PASS byte proof')
    ap.add_argument('--no-partial', action='store_true')
    ap.add_argument('--no-repair', action='store_true')
    ap.add_argument('--dry-run', action='store_true', help='write, prove, then restore every file')
    ap.add_argument('--no-proof', action='store_true', help='write only (the caller proves)')
    ap.add_argument('--workers', type=int, default=8)
    ap.add_argument('--max-proofs', type=int, default=40)
    ap.add_argument('--record-floors', action='store_true', help='upsert ledger/prototype_floors.jsonl after PASS')
    args = ap.parse_args(argv)
    if not 1 <= args.workers <= 8:
        ap.error('between 1 and 8 workers on this host')
    root = args.root.resolve()
    affected = args.affected or root / 'tools/build/affected.py'
    if not args.no_proof and not affected.is_file():
        ap.error("no tools/build/affected.py in the root; pass --affected PATH")
    dirty = subprocess.run(['git', '-C', str(root), 'status', '--porcelain', '-uno', '--', 'src', 'include'],
                           capture_output=True, text=True).stdout.strip()
    if dirty:
        raise SystemExit('src/ or include/ has uncommitted changes; commit first:\n' + dirty[:600])
    datas = load_decisions(args)
    out = args.out
    out.mkdir(parents=True, exist_ok=True)
    logf = open(out / 'batch.log', 'a')

    def log(msg):
        line = time.strftime('%H:%M:%S ') + msg
        print(line, flush=True)
        logf.write(line + '\n')
        logf.flush()

    started = time.monotonic()
    timings = {}
    census = C.Census(root, log=log)
    timings['census'] = round(time.monotonic() - started, 1)
    batch = Batch(root, datas, census, log=log, partial=not args.no_partial, repair=not args.no_repair,
                  scope=args.scope, names=args.names)
    log('%d headers, %d candidate names' % (len(batch.txns), len(batch.cands)))
    prover = None if args.no_proof else Prover(root, affected, census, batch.originals, args.workers, log)
    natcheck = None
    if args.natcheck and not args.no_proof:
        natcheck = lambda: T.run_natcheck(root, args.natcheck, out, log)  # noqa: E731
    runner = Runner(root, batch, out, prover=prover, natcheck=natcheck, log=log, no_proof=args.no_proof,
                    max_proofs=args.max_proofs)
    tree = subprocess.run(['git', '-C', str(root), 'rev-parse', 'HEAD'], capture_output=True, text=True).stdout.strip()
    try:
        t0 = time.monotonic()
        final, entry, nat = runner.run()
        timings['settle'] = round(time.monotonic() - t0, 1)
        timings['proof_seconds'] = round(sum(p['seconds'] for p in runner.proofs), 1)
        verdict = 'NONE' if not final else 'PASS' if entry and entry[3] is not None else 'UNPROVEN'
        timings['total'] = round(time.monotonic() - started, 1)
        rec = write_receipts(out, batch, runner, final, entry, verdict, nat, timings, tree)
        log('result: %s; %d of %d names applied over %d headers, %d proofs (%.0f s), %d files, debt %s, '
            'back-offs %s; %.0f s' % (verdict, len(final), len(batch.cands), len(batch.txns), len(runner.proofs),
                                     timings['proof_seconds'], len(rec['files']), rec['debt'],
                                     rec['backoffs_by_reason'], timings['total']))
        if args.record_floors and verdict == 'PASS' and not args.dry_run:
            import sig_solver
            for data in datas:
                txn_json = out / slug(data['header']) / 'txn' / 'txn.json'
                sig_solver.record_floors(root, Path(data['_path']), txn_json)
        if args.dry_run:
            raise KeyboardInterrupt
        return 0 if verdict == 'PASS' else 1
    except KeyboardInterrupt:
        runner.restore()
        log('dry run / interrupted: every file restored')
        return 0 if args.dry_run else 130
    except BaseException:
        runner.restore()
        log('failed: every file restored')
        raise


if __name__ == '__main__':
    sys.exit(main())
