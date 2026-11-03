#!/usr/bin/env python3
"""Bulk extern wave: the mechanical local_externs classes over many folders, settled on screen proofs and
accepted by one full build-graph proof.

    extern_bulk.py --scope src/dungeon/effect src/dungeon/item ... --write include/dungeon/effect ... \
        --out DIR [--append-shared] [--data] [--workers 4] [--max-rounds 8] [--dry-run] [--no-screen]

What it removes (the header plan's `planned_remove`, tools/headers/plan.py; classes in extern_classes.py):
  * a local declaration whose owning header the TU already sees with the same prototype (deleted);
  * one whose owning header exists and declares it identically but the TU does not include it
    (`#include "<owner>"` added, declaration deleted);
  * one whose owner header lacks it (the canonical prototype is appended to the owner header after its
    APPEND_MARK, then the include/delete above).  Only headers under --write prefixes are written
    (append-only for existing ones; --append-shared also allows appends to existing include/shared/*).
    A TU whose needed header is not writable keeps its declarations (hold `header_not_writable`); one that
    would publish a generated S_<addr> layout name in a feature header too (`generated_layout_in_prototype`).
Plan holds (consumer conflicts, typedef/tag clashes, arity sites, annotations, no C definition...) are the
planner's; this tool never decides a prototype (that is tools/typing/sig_solver.py).  Names recorded in
ledger/prototype_floors.jsonl are never removed or published here (`prototype_floor`), and with --port-adapt
a TU whose edit would remove a native-port adaptation anchor keeps its text (`port_adaptation_anchor`).

Proof (replaces extern_wave.py's per-include assembly filter + standalone TU capture + build-graph round):
  1. settling rounds on SCREEN proofs (affected.prove(select=...)): one representative recipe per (compiled
     source, family, placement copy or not) of the affected set: every edited or consumer TU's own compile
     and one of its placement copies per family, instead of every copy.  A failing recipe blames the edited .c files
     in its closure (their whole TU edit is restored: TU edits are independent, so there is no bisection);
     a failing recipe reached only through a written header holds that header in the TUs whose appended
     names the failing source mentions (else in every TU that needs an append to it).
  2. one FULL proof (every affected recipe, placement copies, image relinks) of the settled state; a
     failure there blames as above and settles again.  Recipes compiled byte-identical in an earlier round
     with the same edited inputs are reused; keys (recipe, git trees of src/ and include/, baseline object
     digest, digests of the edited files reaching it) persist in DIR/reuse.json, so a rerun of the same batch reuses them
     and a new baseline never does.
  3. per-function debt ratchet (tools/lint/debt_check): a .c file whose debt rises is restored.
The files on disk at exit are the last full-PASS state (or the baseline on --dry-run / failure).  Run
tools/lanes/prove_batch.sh afterwards as the lane's batch proof (decoded image, natcheck, debt guard).

Writes DIR/receipt.json (local externs before/after per folder, proofs, holds by reason, timings),
DIR/holds.tsv, DIR/files.tsv, DIR/bulk.patch, DIR/bulk.log.
"""
from __future__ import annotations

import argparse
import csv
from collections import Counter, defaultdict
import difflib
import hashlib
import json
import re
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
TOOLS = HERE.parent
sys.path[:0] = [str(HERE), str(TOOLS), str(TOOLS / 'lint'), str(TOOLS / 'typing')]

import plan as P            # noqa: E402
import rewrite as R         # noqa: E402
import extern_wave as EW    # noqa: E402

LAYOUT_INLINE = 'ledger/layout_inline.jsonl'
RAW_DATA = re.compile(r'^D_[0-9A-Fa-f]{8}\b')
GENERATED = re.compile(r'\bS_(?:func_)?[0-9A-Fa-f]{8}\w*')       # tools/typing/sig_txn.py GENERATED_TYPE
ARITY = re.compile(r"too (?:many|few) arguments to function `([A-Za-z_]\w*)'")
CONFLICT = re.compile(r"(?:previous declaration of|conflicting types for|redefinition of|redeclaration of)"
                      r" `([A-Za-z_]\w*)'")


def load_names(a):
    """The --names / --names-from / --names-file filter (None: every planned name)."""
    out = set(a.names or ())
    if a.names_from == 'sdk':
        import extra
        out |= set(extra.SDK)
    if a.names_file:
        lines = a.names_file.read_text().splitlines()
        if lines and '\t' in lines[0]:
            cols = lines[0].split('\t')
            out |= {l.split('\t')[cols.index('new')] for l in lines[1:] if l.strip()}
        else:
            out |= {l.strip() for l in lines if l.strip()}
    return out if (a.names or a.names_from or a.names_file) else None


def sha(text):
    return hashlib.sha256((text or '').encode('utf-8', 'surrogateescape')).hexdigest()


class Bulk:
    def __init__(self, root, files, data, writable, log=print, new_headers=False, data_named_only=False,
                 names=None, requests=None):
        self.root = Path(root).resolve()
        self.new_headers = new_headers
        self._base = {}
        self.log = log
        self.files = files
        t0 = time.monotonic()
        import model as M
        corpus = M.Corpus(self.root)
        # probe variants (.sigprobe_<pid>_*.c of a concurrent solver) and other dot files are never the tree
        corpus.c_files = [f for f in corpus.c_files if not Path(f).name.startswith('.')]
        self.plan = P.build(self.root, corpus=corpus, scope_files=files, include_data=data, requests=requests)
        self.log('plan: %d TUs in %.0f s' % (len(self.plan.tus), time.monotonic() - t0))
        self.writable = writable
        hof = lambda r: self.plan.fn_for_def(r.definition).header      # noqa: E731
        self.hof = hof
        if names is not None:
            # --names: only these names' declarations move (an extern wave restricted to, e.g., the Psy-Q
            # library names or the names address_names.py just respelled); every other plan edit is dropped
            for tp in self.plan.tus.values():
                tp.remove = [r for r in tp.remove if r.site.name in names]
                tp.append = {h: [n for n in ns if n in names] for h, ns in tp.append.items()}
                tp.append = {h: ns for h, ns in tp.append.items() if ns}
                need = {hof(r) for r in tp.remove} | set(tp.append)
                need |= {h for h, ns in tp.requested.items() if set(ns) & names}
                tp.add = [h for h in tp.add if h in need]
                tp.stale = []
        self.jobs = {}
        self.holds = []                 # (tu, header, reason)
        self.static = Counter()
        for rel, tp in sorted(self.plan.tus.items()):
            for h, why in sorted(tp.holds.items()):
                self.static[why.split(':')[0]] += 1
            if not (tp.add or tp.stale):
                continue
            orig = self.plan.corpus.text(rel)
            edit = R.tu_edit(tp, hof)
            if R.edit_tu(orig, edit) == orig and not (tp.requested and tp.append):
                continue
            self.jobs[rel] = (orig, edit)
        # held (tu, header) pairs; a TU in `restored` keeps its baseline text
        self.held = set()
        self.restored = {}
        self.anchors = {}
        # names recorded as prototype floors (ledger/prototype_floors.jsonl) keep their local declarations and
        # are never published by this tool: the planner does not read the floors ledger
        floors = set()
        try:
            for line in (self.root / 'ledger/prototype_floors.jsonl').read_text().splitlines():
                if line.strip():
                    floors.add(json.loads(line)['name'])
        except (OSError, ValueError, KeyError):
            pass
        self.floors = floors
        for rel, (orig, edit) in self.jobs.items():
            tp = self.plan.tus[rel]
            for r in tp.remove:
                if r.site.name in floors:
                    self.hold(rel, hof(r), 'prototype_floor:' + r.site.name)
                elif data_named_only and getattr(r.site, 'kind', '') == 'data' and RAW_DATA.match(r.site.name):
                    self.hold(rel, hof(r), 'data_raw_address:' + r.site.name)
            for h, requested_names in tp.requested.items():
                for n in sorted(set(requested_names) & floors):
                    self.hold(rel, h, 'prototype_floor:' + n)
            for h, names in tp.append.items():
                for n in sorted(set(names) & floors):
                    self.hold(rel, h, 'prototype_floor:' + n)
            for h in edit['add']:
                if not self.header_ok(h, rel):
                    self.hold(rel, h, 'header_not_writable')
                    continue
                gen = self.generated_names(h, rel)
                if gen:
                    self.hold(rel, h, 'generated_layout_in_prototype:' + gen[0])

    def keep_anchors(self, anchors):
        """Hold every TU whose edit would remove a port adaptation anchor."""
        texts = self.texts()
        for rel, keys in anchors.items():
            if rel in texts and rel in self.jobs:
                orig = self.jobs[rel][0]
                lost = [k for k in keys if k in orig and k not in texts[rel]]
                if lost:
                    self.restore_tu(rel, 'port_adaptation_anchor:' + ' '.join(lost[0].split())[:60])

    def generated_names(self, h, rel):
        """Names this TU needs written into h whose prototype spells a generated S_<addr> layout: publishing
        one in a feature header is refused (the signature solver's rule; the type needs an owner first).  A
        header that does not exist yet is generated whole, so any such row in it counts."""
        rows = {r.name: r for r in self.plan.headers.get(h, [])}
        if not (self.root / h).is_file():
            names = sorted(self.needed(h, rel))
        else:
            names = sorted(self.plan.tus[rel].append.get(h, ()))
        return [n for n in names if n in rows and GENERATED.search(rows[n].proto or rows[n].definition.proto or '')]

    def header_ok(self, h, rel):
        tp = self.plan.tus[rel]
        exists = (self.root / h).is_file()
        if not exists and not self.new_headers:
            return False
        needs_write = not exists or bool(tp.append.get(h))
        return not needs_write or self.writable(h, exists)

    def hold(self, rel, h, why):
        if (rel, h) not in self.held:
            self.held.add((rel, h))
            self.holds.append((rel, h, why))

    def restore_tu(self, rel, why):
        if rel in self.jobs and rel not in self.restored:
            self.restored[rel] = why
            self.holds.append((rel, '*', why))

    def accepted(self):
        out = {}
        for rel, (orig, edit) in self.jobs.items():
            if rel in self.restored:
                continue
            out[rel] = [h for h in edit['add'] if (rel, h) not in self.held]
        return out

    def texts(self):
        """{path: new text} of the current state (TU edits + the header texts they need)."""
        texts = {}
        acc = self.accepted()
        for rel, hs in acc.items():
            orig, edit = self.jobs[rel]
            new = R.edit_tu(orig, edit, hs)
            if not hs and edit.get('drop'):
                new = R.edit_tu(orig, dict(edit, add=[]), [])
            if new != orig:
                texts[rel] = new
        # A caller may already include the owner header but still need a prototype appended there.
        kept = {rel: hs for rel, hs in acc.items()
                if rel in texts or getattr(self.plan.tus[rel], 'requested', {})}
        for h, t in self.header_texts(kept).items():
            if t != self.base_text(h):
                texts[h] = t
        return texts

    def base_text(self, h):
        """A header's committed text (git HEAD), never the disk: the disk holds the previous round's state."""
        if h not in self._base:
            import subprocess
            res = subprocess.run(['git', '-C', str(self.root), 'show', 'HEAD:' + h], capture_output=True)
            self._base[h] = res.stdout.decode('utf-8', 'surrogateescape') if res.returncode == 0 else None
        return self._base[h]

    def needed(self, h, rel):
        """Names TU rel needs from h: the declarations it removes in favour of h, plus h's appends."""
        tp = self.plan.tus[rel]
        return {r.site.name for r in tp.remove if self.hof(r) == h} | set(tp.append.get(h, ()))

    def header_texts(self, accepted):
        """{header: text} the TUs in `accepted` need, always built from the committed header text (a round
        appends to the baseline, never to the previous round's output)."""
        names = defaultdict(set)
        for rel, hs in accepted.items():
            tp = self.plan.tus.get(rel)
            for h in hs:
                names[h] |= (self.needed(h, rel) if self.base_text(h) is None else set(tp.append.get(h, ()))) \
                    if tp else set()
        out = {}
        for h in sorted(names):
            old = self.base_text(h)
            if old is None:
                # a new header carries exactly the declarations its includers need (not every row the planner
                # could publish there: an image data header would otherwise list the whole image)
                rows = self.plan.headers.get(h, [])
                self.plan.headers[h] = [r for r in rows if r.name in names[h]]
                try:
                    out[h] = R.header_text(self.plan, h)
                finally:
                    self.plan.headers[h] = rows
            elif h in self.plan.existing and names[h]:
                out[h] = R.append_text(self.plan, h, names[h], old)
        return out

    def appended(self, h):
        """{name: [TUs that need it appended to h]} in the current state."""
        out = defaultdict(list)
        for rel, hs in self.accepted().items():
            if h in hs:
                for n in self.plan.tus[rel].append.get(h, ()):
                    out[n].append(rel)
        return out


class Prover:
    """affected.prove in process over one graph; reuse keyed by edited input texts, persisted."""

    def __init__(self, root, plan, originals, workers, reuse_path, log=print, affected=None):
        import sig_batch as SB
        self.SB = SB
        self.root = Path(root).resolve()
        self.mod = SB.load_affected(affected or self.root / 'tools/build/affected.py')
        if 'select' not in self.mod.prove.__code__.co_varnames:
            raise RuntimeError('affected.py without prove(select=): screen proofs need the patched prover')
        self.graph = self.mod.Graph(self.root)
        self.corpus = plan.corpus
        self.originals = originals
        self.workers = workers
        self.log = log
        self.reuse_path = reuse_path
        import subprocess
        # the source trees at HEAD (not the commit: a tools-only commit keeps the cache)
        self.head = subprocess.run(['git', '-C', str(self.root), 'rev-parse', 'HEAD:src', 'HEAD:include'],
                                   capture_output=True, text=True).stdout.strip().replace('\n', '+') or 'nohead'
        self.reuse = {}
        self._objects = {}
        if reuse_path and reuse_path.is_file():
            try:
                self.reuse = dict.fromkeys(json.loads(reuse_path.read_text()), True)
            except ValueError:
                self.reuse = {}

    def object_digest(self, rel):
        if rel not in self._objects:
            try:
                self._objects[rel] = hashlib.sha256((self.root / rel).read_bytes()).hexdigest()
            except (OSError, TypeError):
                self._objects[rel] = 'none'
        return self._objects[rel]

    def save(self):
        if self.reuse_path:
            self.reuse_path.write_text(json.dumps(sorted(self.reuse)))

    def screen(self, ids, graph, edited):
        """One recipe per (compiled source, family, projection or not): an edited TU keeps its own compile
        and one placement copy per family; a consumer reached through a header keeps one per family."""
        out, seen = [], set()
        for rid in ids:
            spec = graph.recipes[rid]
            key = (graph.own_source(spec), spec.get('_family'), bool(spec.get('projection')))
            if key in seen:
                continue
            seen.add(key)
            out.append(rid)
        return out

    def __call__(self, texts, screen):
        g = self.graph
        # the layout ledger is in the digests (placement-copy keys), not in the edited set (as sig_batch)
        files = sorted(f for f in texts if f.endswith(('.c', '.h')))
        by_dep = g.by_dep()
        digest = {f: sha(t) for f, t in texts.items()}
        new_inc = {f: self.SB.include_targets(self.corpus, f, t) -
                   self.SB.include_targets(self.corpus, f, self.originals.get(f))
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
            # the baseline object's bytes are part of the key: a later batch (or an --adopt) changes them
            # (content, not mtime: a compile's object-cache hit touches the baseline object)
            base = self.object_digest(spec.get('output'))
            parts = [rid, 'head=' + self.head, 'base=' + base] + ['%s=%s' % (f, digest[f]) for f in sorted(ks)]
            if spec.get('projection'):
                parts.append('layout=' + layout)
            return hashlib.sha256('\n'.join(parts).encode()).hexdigest()
        sel = (lambda ids, graph: self.screen(ids, graph, files)) if screen else None
        seen = {}

        def keyed(rid):
            seen[rid] = key(rid)
            return seen[rid]
        rep = self.mod.prove(self.root, files, workers=self.workers, graph=g, reuse=self.reuse, reuse_key=keyed,
                             log=lambda m: self.log('  ' + m), select=sel)
        self.last_keys = seen
        self.save()
        return rep


def port_anchors(path):
    """{tu: [anchor text]} from the native port's adaptation table (tools/adapt.py FIXES: (old, new, why)
    triples applied to game sources).  An edit that removes an anchor breaks the port's adaptation (natcheck
    ADAPTATION), so such a TU keeps its text.  Parsed with ast (literals only); never imported."""
    import ast
    out = defaultdict(list)
    if not path or not Path(path).is_file():
        return out
    tree = ast.parse(Path(path).read_text())

    def take(key, value):
        try:
            rows = ast.literal_eval(value)
        except ValueError:
            return
        for row in rows if isinstance(rows, list) else ():
            if isinstance(row, tuple) and row and isinstance(row[0], str):
                out[key].append(row[0])
    for node in ast.walk(tree):
        if isinstance(node, ast.Assign) and len(node.targets) == 1:
            tg = node.targets[0]
            if isinstance(tg, ast.Subscript) and getattr(tg.value, 'id', '') == 'FIXES':
                key = tg.slice.value if isinstance(tg.slice, ast.Constant) else None
                if isinstance(key, str):
                    take(key, node.value)
            elif getattr(tg, 'id', '') == 'FIXES' and isinstance(node.value, ast.Dict):
                for k, v in zip(node.value.keys, node.value.values):
                    if isinstance(k, ast.Constant):
                        take(k.value, v)
        elif isinstance(node, ast.Call) and getattr(node.func, 'attr', '') == 'update' and \
                getattr(getattr(node.func, 'value', None), 'id', '') == 'FIXES' and node.args and \
                isinstance(node.args[0], ast.Dict):
            for k, v in zip(node.args[0].keys, node.args[0].values):
                if isinstance(k, ast.Constant):
                    take(k.value, v)
    return out


def closure_of(graph, rid):
    """Tree files a recipe compiles: dependencies, own source, placement owner and the inputs of generated
    sources (SLUS partition bodies are rendered from src/slus/*.c)."""
    spec = graph.recipes[rid]
    return {graph.real(d) for d in graph.dependency_names(spec)} | {graph.own_source(spec)}


NATIVE_LOG = re.compile(r'command failed: (build/\.state/native/[\w./-]+\.log)')
HEADER_AT = re.compile(r'(?:build_ovl/|build_slus/)?(include/[\w/.-]+\.h):(\d+):')


def failing_source(rec):
    import sig_txn as T
    return T.failing_source(rec)


def _text(root, rel):
    try:
        return (Path(root) / rel).read_text(errors='replace')
    except OSError:
        return ''


def blame(bulk, prover, report, texts):
    """Update holds for every non-PASS recipe/image of a report; returns the number of new holds."""
    before = len(bulk.holds)
    g = prover.graph
    real = {g.real(f): f for f in texts}
    # appended names per header as proved (a hold made for one failing recipe must not shrink what the next
    # failing recipe of the same round is matched against)
    snapshot = {h: bulk.appended(h) for h in texts if h.endswith('.h')}
    bad = [rid for rid, rec in report['recipes'].items() if rec['verdict'] not in ('PASS',)]
    for image, entry in report.get('images', {}).items():
        if entry.get('verdict') not in ('PASS', None):
            bad += entry.get('changed_recipes', [])
    facts = {}
    for rid in set(bad):
        spec = g.recipes.get(rid)
        seen = {real[x] for x in closure_of(g, rid) if x in real} if spec else set()
        own = real.get(g.own_source(spec)) if spec else None
        error = report['recipes'].get(rid, {}).get('error', '')
        for log_path in NATIVE_LOG.findall(error):
            # native (genuine ASPSX) module builds report only the failing log: read the compiler's words
            error += '\n' + _text(bulk.root, log_path)[-6000:].replace(str(bulk.root) + '/', '')
        facts[rid] = (seen, own, error)
    # most attributable first: the own TU is edited, then the compiler names something, then the rest; a later
    # recipe whose edited inputs this round already changed is explained (the next proof re-judges it)
    order = sorted(facts, key=lambda r: (facts[r][1] not in facts[r][0],
                                         not (CONFLICT.search(facts[r][2]) or ARITY.search(facts[r][2])
                                              or NATIVE_LOG.search(facts[r][2])), r))
    restored0 = set(bulk.restored)
    held_names = set()           # (header, name) held this round

    def hold(rel, h, n, why):
        held_names.add((h, n))
        bulk.hold(rel, h, why)
    for rid in order:
        rec = report['recipes'].get(rid, {})
        verdict = rec.get('verdict', 'image').lower()
        seen, own, _ = facts[rid]
        cs = [f for f in seen if f.endswith('.c')]
        hs = [f for f in seen if f.endswith('.h')]
        if not seen:
            bulk.log('  unattributed failure %s: %s' % (rid, (rec.get('cause') or '')[:200]))
            raise RuntimeError('failure without an edited input: ' + rid)
        if {f for f in bulk.restored if f not in restored0} & set(cs):
            continue
        src_text = _text(bulk.root, failing_source(rec))
        if any(h in hs and (n in facts[rid][2] or re.search(r'\b%s\b' % re.escape(n), src_text))
               for h, n in held_names):
            continue
        src = failing_source(rec)
        error = facts[rid][2]
        named = set(CONFLICT.findall(error)) | set(ARITY.findall(error))
        n0 = len(bulk.holds)
        # 1. the compiler's words: an appended prototype it names, or the appended line it reports
        for h in hs:
            app = snapshot.get(h) or {}
            lines = (texts.get(h) or '').splitlines()
            precise = {n for n in app if n in named}
            for path, line in HEADER_AT.findall(error):
                if path == h and 0 < int(line) <= len(lines):
                    precise |= set(re.findall(r'[A-Za-z_]\w*', lines[int(line) - 1])) & set(app)
            for n in precise:
                for rel in app[n]:
                    hold(rel, h, n, 'header_consumer_%s:%s:%s' % (verdict, n, src))
        if len(bulk.holds) > n0:
            continue
        # 2. the recipe's own TU edit, then other edited TUs it compiles (merged-TU members), not yet restored
        if own in cs and own not in bulk.restored:
            bulk.restore_tu(own, 'proof_%s:%s' % (verdict, rid))
            continue
        fresh = [f for f in cs if f not in bulk.restored]
        if fresh:
            for f in fresh:
                bulk.restore_tu(f, 'proof_%s:%s' % (verdict, rid))
            continue
        # 3. appended names the failing source mentions; else every appended name of the edited headers
        for h in hs:
            app = snapshot.get(h) or {}
            hit = {n for n in app if re.search(r'\b%s\b' % re.escape(n), src_text)}
            for n in (hit or set(app)):
                for rel in app[n]:
                    hold(rel, h, n, 'header_consumer_%s%s:%s:%s' % (verdict, '' if hit else '_unattributed', n, src))
            if not app and h not in getattr(bulk.plan, 'existing', ()):
                # a generated (new) header changed a consumer: TUs that add h
                for rel, hs_ in bulk.accepted().items():
                    if h in hs_:
                        bulk.hold(rel, h, 'header_closure_%s:%s' % (verdict, src))
        if len(bulk.holds) > n0:
            continue
        # 4. nothing attributable left: every TU that adds an edited header this recipe sees
        for rel, hs_ in bulk.accepted().items():
            for h in hs_:
                if h in hs:
                    bulk.hold(rel, h, 'header_include_%s:%s' % (verdict, src))
    return len(bulk.holds) - before


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=HERE.parents[1])
    ap.add_argument('--scope', nargs='+', required=True, help='src/ folders (recursive) or .c files to edit')
    ap.add_argument('--exclude', nargs='*', default=[], help='path prefixes inside the scope not to edit')
    ap.add_argument('--write', nargs='*', default=[], help='header path prefixes this run may write')
    ap.add_argument('--append-shared', action='store_true', help='allow appends to existing include/shared/*')
    ap.add_argument('--data', action='store_true', help='data externs too (planner --data)')
    ap.add_argument('--data-named-only', action='store_true',
                    help='data externs of named globals only: a TU whose move would publish a raw D_<addr> symbol '
                         'keeps that header\'s declarations (implies --data)')
    ap.add_argument('--names', nargs='*', help='only these names move (others keep their declarations)')
    ap.add_argument('--names-from', choices=['sdk'], help="'sdk': the Psy-Q library names of tools/headers/extra.py")
    ap.add_argument('--names-file', type=Path, help='file with one name per line (or a TSV whose column `new` lists them)')
    ap.add_argument('--publish-callers', action='store_true',
                    help='request owner prototypes/includes for file,new pairs in --names-file; keep old call spellings')
    ap.add_argument('--port-adapt', type=Path,
                    help="the native port's tools/adapt.py: TUs whose edit would remove an adaptation anchor keep "
                         "their text (natcheck ADAPTATION otherwise)")
    ap.add_argument('--new-headers', action='store_true',
                    help='allow generating folder headers that do not exist yet (native module recipes refuse a '
                         'literal include the configured views lack until make configure; off by default)')
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--workers', type=int, default=4)
    ap.add_argument('--max-rounds', type=int, default=10)
    ap.add_argument('--no-screen', action='store_true', help='settle on full proofs only')
    ap.add_argument('--affected', type=Path, help='affected.py to prove with (default: the root\'s)')
    ap.add_argument('--dry-run', action='store_true')
    ap.add_argument('--debug-keys', action='store_true', help='write DIR/keysN.json (reuse key per recipe) per proof')
    ap.add_argument('--plan-only', action='store_true',
                    help='static yield of the plan (no writes, no proof): DIR/plan.json and plan_holds.tsv')
    a = ap.parse_args(argv)
    if not 1 <= a.workers <= 8:
        ap.error('between 1 and 8 workers on this host')
    root = a.root.resolve()
    a.out.mkdir(parents=True, exist_ok=True)
    logf = open(a.out / 'bulk.log', 'a')

    def log(msg):
        line = time.strftime('%H:%M:%S ') + msg
        print(line, flush=True)
        logf.write(line + '\n')
        logf.flush()

    started = time.monotonic()
    files = []
    for s in a.scope:
        p = root / s
        files += [s] if p.is_file() else sorted(x.relative_to(root).as_posix() for x in p.rglob('*.c'))
    files = sorted({f for f in files if not f.startswith(tuple(a.exclude)) and not Path(f).name.startswith('.')})
    # decoded-image sources are outside the recipe graph (tools/decoded_images.py proves them; affected.prove
    # refuses an edit to one): never edited here
    try:
        decoded = {u['source'] for u in json.loads((root / 'config/decoded/menu_cache.json').read_text())['units']}
    except (OSError, ValueError, KeyError):
        decoded = set()
    files = [f for f in files if f not in decoded]

    def writable(h, exists):
        if h.startswith(tuple(a.write)):
            return True
        return a.append_shared and exists and h.startswith('include/shared/')

    log('scope: %d files, write %s, data=%s' % (len(files), a.write, a.data))
    requests = defaultdict(set)
    if a.publish_callers:
        if not a.names_file:
            ap.error('--publish-callers requires --names-file with file and new columns')
        with a.names_file.open() as fh:
            reader = csv.DictReader(fh, delimiter='\t')
            if not {'file', 'new'} <= set(reader.fieldnames or ()):
                ap.error('--publish-callers requires file and new columns')
            for row in reader:
                if row['file'] in files and re.fullmatch(r'[A-Za-z_]\w*', row['new']):
                    requests[row['file']].add(row['new'])
    bulk = Bulk(root, files, a.data or a.data_named_only, writable, log, new_headers=a.new_headers,
                data_named_only=a.data_named_only, names=load_names(a), requests=requests)
    if a.port_adapt:
        bulk.keep_anchors(port_anchors(a.port_adapt))
    log('jobs: %d TUs with edits; static holds %s' % (len(bulk.jobs), dict(bulk.static.most_common(8))))
    texts0 = bulk.texts()
    if a.plan_only:
        per = defaultdict(lambda: [0, 0])
        for f in files:
            cur = EW.read(root, f)
            fo = '/'.join(f.split('/')[:-1][:3])
            per[fo][0] += EW.local_externs(f, cur)
            per[fo][1] += EW.local_externs(f, texts0.get(f, cur))
        res = dict(files=len(files), tus_with_edits=len(bulk.jobs),
                   tus_changed=len([f for f in texts0 if f.endswith('.c')]),
                   headers=sorted(f for f in texts0 if f.endswith('.h')),
                   new_headers=sorted(f for f in texts0 if f.endswith('.h') and not (root / f).is_file()),
                   local_externs_before=sum(v[0] for v in per.values()),
                   local_externs_after=sum(v[1] for v in per.values()),
                   by_folder={k: dict(before=v[0], after=v[1]) for k, v in sorted(per.items())},
                   holds=dict(Counter(w.split(':')[0] for _, _, w in bulk.holds)), static_holds=dict(bulk.static))
        (a.out / 'plan.json').write_text(json.dumps(res, indent=1) + '\n')
        EW._tsv(a.out / 'plan_holds.tsv', ('tu', 'header', 'reason'), bulk.holds)
        log('plan-only: local externs %d -> %d over %d files (%d TUs, %d headers written); holds %s' % (
            res['local_externs_before'], res['local_externs_after'], len(files), res['tus_changed'],
            len(res['headers']), res['holds']))
        return 0
    originals = {f: EW.read(root, f) for f in set(texts0) | set(bulk.jobs)}
    originals[LAYOUT_INLINE] = EW.read(root, LAYOUT_INLINE)
    prover = Prover(root, bulk.plan, originals, a.workers, a.out / 'reuse.json', log, a.affected)
    import sig_txn as T
    written = set()

    def write_state(texts):
        for f in list(written):
            if f not in texts and f != LAYOUT_INLINE:
                EW.write(root, f, originals[f])
                written.discard(f)
        for f, t in texts.items():
            if EW.read(root, f) != t:
                EW.write(root, f, t)
            written.add(f)
        EW.write(root, LAYOUT_INLINE, originals[LAYOUT_INLINE])
        T.refresh_layout(root, lambda m: log('  ' + m))
        now = EW.read(root, LAYOUT_INLINE)
        out = dict(texts)
        if now != originals[LAYOUT_INLINE]:
            out[LAYOUT_INLINE] = now
            written.add(LAYOUT_INLINE)
        return out

    def restore_all():
        for f in set(originals):
            if EW.read(root, f) != originals[f]:
                EW.write(root, f, originals[f])

    proofs = []
    accepted_state = None
    try:
        rounds = 0
        screen = not a.no_screen
        while rounds < a.max_rounds:
            rounds += 1
            texts = bulk.texts()
            if not texts:
                log('nothing left to prove')
                write_state({})
                accepted_state = {}
                break
            state = write_state(texts)
            t0 = time.monotonic()
            rep = prover(state, screen)
            row = dict(round=rounds, screen=screen, verdict=rep['verdict'], counts=rep.get('counts'),
                       recipes=len(rep.get('recipes', {})), reused=rep.get('reused', 0),
                       scope=len(rep['scope']['recipes']) + len(rep['scope']['slus_recipes']),
                       files=len(texts), seconds=round(time.monotonic() - t0, 1))
            proofs.append(row)
            if a.debug_keys:
                (a.out / ('keys%d.json' % rounds)).write_text(json.dumps(prover.last_keys, sort_keys=True))
            log('proof %d (%s): %d files -> %s %s (%d of %d recipes, %d reused, %.0f s)' % (
                rounds, 'screen' if screen else 'full', len(texts), rep['verdict'], rep.get('counts'),
                row['recipes'], row['scope'], row['reused'], row['seconds']))
            stale = [r for r, rec in rep.get('recipes', {}).items() if rec['verdict'] == 'STALE_BASE']
            if stale or rep['verdict'] == 'STALE_BASE' or (rep['verdict'] == 'ERROR' and not rep.get('recipes')):
                raise RuntimeError('proof %s: %s %s' % (rep['verdict'], rep.get('error', '')[:400], stale[:5]))
            if rep['verdict'] != 'PASS':
                bad = [(rid, rec.get('cause', '')) for rid, rec in rep['recipes'].items() if rec['verdict'] != 'PASS']
                for rid, cause in bad[:6]:
                    log('  failing %s: %s' % (rid, cause[:160]))
                (a.out / ('round%d.json' % rounds)).write_text(json.dumps(dict(
                    row, failing={rid: dict(verdict=rec['verdict'], source=rec.get('source'),
                                            cause=rec.get('cause'), difference=rec.get('difference'))
                                  for rid, rec in rep['recipes'].items() if rec['verdict'] != 'PASS'}),
                    indent=1, default=str))
                n = blame(bulk, prover, rep, texts)
                EW._tsv(a.out / 'holds.tsv', ('tu', 'header', 'reason'), bulk.holds)
                why = Counter(w.split(':')[0] for _, _, w in bulk.holds[len(bulk.holds) - n:])
                log('  blame: %d new holds %s, %d TUs restored' % (n, dict(why), len(bulk.restored)))
                if not n:
                    raise RuntimeError('a failing proof produced no new hold')
                continue
            if screen:
                screen = False
                continue
            # full PASS: debt ratchet
            rises = [f for f in texts if f.endswith('.c') and EW.debt_rises(f, originals[f], texts[f])]
            if rises:
                for f in rises:
                    bulk.restore_tu(f, 'debt_rise')
                log('  debt rise: restored %d TUs' % len(rises))
                screen = not a.no_screen
                continue
            accepted_state = state
            break
        if accepted_state is None:
            raise RuntimeError('no full PASS within %d rounds' % a.max_rounds)
        final = {f: EW.read(root, f) for f in originals}
        changed = sorted(f for f in originals if final[f] != originals[f])
        per_folder = defaultdict(lambda: [0, 0])
        rows = []
        for f in files:
            b = EW.local_externs(f, originals.get(f) or EW.read(root, f))
            n = EW.local_externs(f, final.get(f) or EW.read(root, f))
            fo = '/'.join(f.split('/')[:-1][:3])
            per_folder[fo][0] += b
            per_folder[fo][1] += n
            if f in changed:
                rows.append((f, b, n))
        patch = []
        for f in changed:
            patch.extend(difflib.unified_diff((originals[f] or '').splitlines(True), (final[f] or '').splitlines(True),
                                              'a/' + f if originals[f] is not None else '/dev/null', 'b/' + f))
        (a.out / 'bulk.patch').write_text(''.join(patch))
        EW._tsv(a.out / 'holds.tsv', ('tu', 'header', 'reason'), bulk.holds)
        EW._tsv(a.out / 'files.tsv', ('file', 'local_externs_before', 'local_externs_after'), rows)
        receipt = dict(scope=a.scope, exclude=a.exclude, write=a.write, data=a.data, files=len(files),
                       tus_with_edits=len(bulk.jobs), files_changed=len([f for f in changed if f.endswith('.c')]),
                       headers_changed=[f for f in changed if f.endswith('.h')],
                       local_externs_before=sum(v[0] for v in per_folder.values()),
                       local_externs_after=sum(v[1] for v in per_folder.values()),
                       by_folder={k: dict(before=v[0], after=v[1]) for k, v in sorted(per_folder.items())},
                       proofs=proofs, holds_by_reason=dict(Counter(w.split(':')[0] for _, _, w in bulk.holds)),
                       static_holds=dict(bulk.static), seconds=round(time.monotonic() - started, 1))
        (a.out / 'receipt.json').write_text(json.dumps(receipt, indent=1) + '\n')
        log('local externs %d -> %d; %d .c files, %d headers changed; holds %s; %.0f s' % (
            receipt['local_externs_before'], receipt['local_externs_after'], receipt['files_changed'],
            len(receipt['headers_changed']), receipt['holds_by_reason'], receipt['seconds']))
        if a.dry_run:
            restore_all()
            log('dry run: every file restored')
        return 0
    except BaseException:
        restore_all()
        log('failed/interrupted: every file restored')
        raise


if __name__ == '__main__':
    sys.exit(main())
