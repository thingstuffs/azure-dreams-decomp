#!/usr/bin/env python3
"""Per-name extern trial: replace every local declaration of a name with its owner header, keep what proves.

    extern_trial.py --names NAME ... | --names-file F | --top N  --out DIR
        [--exclude-names-file F] [--recent-repo REPO --recent N] [--address-functions] [--append]
        [--lint-port PORT] [--no-lint] [--port-adapt ADAPT] [--workers 2] [--plan-only] [--dry-run]

For each selected name (a function or a named data object; never a D_<addr> name, never a name recorded in
ledger/prototype_floors.jsonl):
  1. the owner is the header beside the name's definition (decision 74: the definition's folder header, or
     the include/sdk stand-in for a library name; tools/headers/plan.py resolves it);
  2. every local declaration of the name in a .c file is deleted and the TU includes the owner header
     (tools/headers/rewrite.py: after the existing includes).  Each TU is planned once per name (plan_tu over
     that name's sites only), so a hold of one name never blocks another name in the same TU.  An owner
     header that lacks the declaration is a hold (`missing_owner`) unless --append publishes the definition's
     prototype in it (append-only, as tools/headers/extern_bulk.py does);
  3. every consumer recipe is compiled and compared with the baseline objects (extern_bulk's screen and full
     build-graph proofs, tools/build/affected.py); a failing recipe restores the TU it blames, file by file;
  4. on a full PASS, tools/lint/lint_closure.py compares the trial tree with HEAD (GCC warning sites and
     declaration agreement); a TU with a new warning site or compile failure is restored and the state is
     proved again;
  5. names whose TU was restored together with another selected name are retried alone in that TU.
The files on disk at exit are the last proven state (every file restored with --dry-run or on failure).

Receipt (DIR/receipt.json, DIR/names.tsv, DIR/sites.tsv): per name the local declaration files, the files
changed, kept, and held with a reason class and the raw reason:
  type_disagreement  the owner (or a header the TU sees) declares another type, a consumer disagrees, or the
                     compiler refused the TU with the owner header
  new_warning        lint_closure: a new GCC warning site, a new compile failure or a declaration disagreement
  byte_change        a consumer recipe or image is not byte-identical
  missing_owner      no C definition / no published owner prototype / the owner header lacks the declaration
  foreign_import     the declaration binds a definition in another program (one import header per program)
  prototype_floor    recorded in ledger/prototype_floors.jsonl
  site_form          a conditional, multi-declarator or annotated local declaration, or a TU without common.h
  port_anchor        the edit would remove a native-port adaptation anchor (--port-adapt)
  debt_rise          a function's lexical debt would rise
  other              anything else (the raw reason says what)

--plan-only stops after planning (static yield, no writes, no compile); --dry-run proves and lints, then
restores every file.  Ranking (--top N): names by the number of .c files that declare them locally, among
names with a resolvable owner, after the exclusions (D_ names always; func_ names unless --address-functions;
prototype floors; --exclude-names-file; identifiers in the subjects of REPO's last --recent commits).
"""
from __future__ import annotations

import argparse
import contextlib
import copy
import json
import re
import subprocess
import sys
import time
from collections import Counter, defaultdict
from pathlib import Path

HERE = Path(__file__).resolve().parent
TOOLS = HERE.parent
sys.path[:0] = [str(TOOLS / 'headers'), str(TOOLS), str(TOOLS / 'lint'), str(HERE)]

RAW_DATA = re.compile(r'^D_[0-9A-Fa-f]{8}\b')
ADDRESS_FUNCTION = re.compile(r'^func_[0-9A-Fa-f]{8}\b')
IDENT = re.compile(r'[A-Za-z_]\w*')

CATEGORIES = ('type_disagreement', 'new_warning', 'byte_change', 'missing_owner', 'foreign_import',
              'prototype_floor', 'site_form', 'port_anchor', 'debt_rise', 'other')


def category(reason):
    """Reason class of a raw hold reason (planner, extern_bulk blame, or this tool's lint gate)."""
    r = reason
    while r.startswith(('tu_hold:', 'retry:')):
        r = r.split(':', 1)[1]
    if r.startswith('no_definition:'):
        r = r.split(':', 1)[1]
    head = r.split(':', 1)[0]
    if head == 'cross_container':
        return 'foreign_import'
    if head == 'data_views_differ':
        return 'type_disagreement'
    if head == 'prototype_floor':
        return 'prototype_floor'
    if head.startswith('lint_'):
        return 'new_warning'
    if head == 'proof_error':
        return 'type_disagreement'
    if head.startswith(('proof_', 'header_consumer_', 'header_include_', 'header_closure_')):
        # a header-side compile error is a declaration conflict; everything else is a byte change
        return 'type_disagreement' if head.split('_')[-1] == 'error' or '_error' in head else 'byte_change'
    if head in ('hand_written_header_differs', 'consumer_conflict', 'multi_container_conflict', 'typedef_clash',
                'tag_clash', 'name_clash') or head.startswith(('existing_header_', 'site_')):
        return 'type_disagreement'
    if head in ('missing_owner', 'header_not_writable', 'function_held', 'data_owner_unresolved', 'no_definition',
                'unbound', 'generated_layout_in_prototype', 'no_owner') or head.startswith('data_'):
        return 'missing_owner'
    if head in ('conditional_site', 'multi_declarator', 'annotated_declaration', 'tu_without_common_h'):
        return 'site_form'
    if head == 'port_adaptation_anchor':
        return 'port_anchor'
    if head == 'debt_rise':
        return 'debt_rise'
    return 'other'


# ------------------------------------------------------------------ plan and selection

def load_plan(root, log=print):
    import model as M
    import plan as P
    t0 = time.monotonic()
    corpus = M.Corpus(root)
    corpus.c_files = [f for f in corpus.c_files if not Path(f).name.startswith('.')]
    plan = P.build(root, corpus=corpus, include_data=True)
    log('plan: %d declaration sites in %.0f s' % (len(plan.sites), time.monotonic() - t0))
    return plan


def floors_of(root):
    out = set()
    try:
        for line in (Path(root) / 'ledger/prototype_floors.jsonl').read_text().splitlines():
            if line.strip():
                out.add(json.loads(line)['name'])
    except (OSError, ValueError, KeyError):
        pass
    return out


def decoded_sources(root):
    try:
        return {u['source'] for u in json.loads((Path(root) / 'config/decoded/menu_cache.json').read_text())['units']}
    except (OSError, ValueError, KeyError):
        return set()


def local_sites(plan):
    """{name: [SiteRow]} of non-static declarations in .c files (tree-wide)."""
    out = defaultdict(list)
    for r in plan.sites:
        s = r.site
        if s.path.endswith('.c') and s.path.startswith('src/') and getattr(s, 'storage', '') != 'static':
            out[s.name].append(r)
    return out


def owner_of(plan, row):
    """(owner header, '') or ('', reason) for one site row."""
    if row.definition is None:
        return '', 'no_definition:' + (row.detail if row.cls == 'data_hold' and row.detail else row.cls)
    fr = plan.fn_for_def(row.definition)
    if fr is None:
        return '', 'function_held:unbound'
    if fr.status != 'header':
        return '', 'function_held:' + (fr.reason or 'unpublished')
    return fr.header, ''


def owner_reason_class(reason):
    """'function_held:private_header_type:T@f' -> 'private_header_type'; 'no_definition:cross_container' ->
    'cross_container'."""
    parts = reason.split(':')
    return parts[1] if len(parts) > 1 and parts[0] in ('function_held', 'no_definition') else parts[0]


def recent_subject_names(repo, n):
    """Identifiers in the subjects of repo's last n commits (read-only git)."""
    if not repo or not n:
        return set()
    res = subprocess.run(['git', '-C', str(repo), 'log', '-%d' % n, '--format=%s'], capture_output=True, text=True)
    return set(IDENT.findall(res.stdout))


def select(plan, floors, top=None, names=None, exclude=(), address_functions=False):
    """(selected names in order, {name: skip reason}).  Explicit names keep their order; --top ranks by the
    number of .c files declaring the name locally (ties by name) among names with a resolvable owner."""
    sites = local_sites(plan)
    skipped = {}
    exclude = set(exclude)

    def skip(n):
        if RAW_DATA.match(n):
            return 'd_address_name'
        if n in floors:
            return 'prototype_floor'
        if n in exclude:
            return 'excluded'
        if not sites.get(n):
            return 'no_local_declaration'
        return ''
    if names is not None:
        out = []
        for n in names:
            why = skip(n)
            if why:
                skipped[n] = why
            elif n not in out:
                out.append(n)
        return out, skipped
    ranked = []
    for n, rows in sites.items():
        why = skip(n)
        if not why and ADDRESS_FUNCTION.match(n) and not address_functions:
            why = 'address_function_name'
        if not why and not any(owner_of(plan, r)[0] for r in rows):
            why = 'no_owner:' + Counter(owner_reason_class(owner_of(plan, r)[1]) for r in rows).most_common(1)[0][0]
        if why:
            skipped[n] = why
            continue
        ranked.append((-len({r.site.path for r in rows}), n))
    ranked.sort()
    return [n for _, n in ranked[:top]], skipped


def companion_conflict(plan, rel, name, own, headers, declared):
    """Hold reason when including `headers` would put another name's declaration next to a different local
    declaration of it in rel (the other name's local declaration stays: only `name` moves), else ''."""
    import plan as P
    for h in sorted(headers):
        if h not in declared:
            names = set()
            for f in {h} | set(plan.corpus.closure(h)):
                if f.endswith('.h'):
                    names |= P._declared_names(plan, f)
            declared[h] = names
        others = [r for r in own if r.site.name != name and r.site.name in declared[h]]
        for r in others:
            if r.definition is None:
                return 'existing_header_other:%s@%s' % (r.site.name, h)
            if getattr(r.site, 'kind', '') != 'data' and not (
                    r.cls in ('identical', 'spelling') or (r.cls == 'unprototyped' and not r.detail)):
                # the local declaration itself disagrees with the definition the header declares
                return 'existing_header_other_%s:%s@%s' % (r.cls, r.site.name, h)
        reason, _ = P._existing_gap(plan, rel, h, others)
        if reason:
            return 'existing_header_other:%s' % reason
        reason = closure_conflict(plan, rel, h, name)
        if reason:
            return reason
    return ''


def _compatible(x, y):
    """Two function declaration sites the compiler accepts together: both bind one definition with an
    identical or spelling-only prototype, or their texts agree."""
    ok = lambda r: r.cls in ('identical', 'spelling') or (r.cls == 'unprototyped' and not r.detail)  # noqa: E731
    if x.definition is not None and y.definition is not None and ok(x) and ok(y) and \
            (x.definition.path, x.definition.name) == (y.definition.path, y.definition.name):
        return True
    norm = lambda t: re.sub(r'\bextern\s+|\s+', ' ', t).strip().rstrip(';').strip()   # noqa: E731
    return norm(x.site.text) == norm(y.site.text)


def closure_conflict(plan, rel, h, moved=None):
    """Hold reason when a header that including h newly brings into rel declares a name that rel (its
    local declarations or the headers it already includes) declares differently, else ''.  The local
    declarations of `moved` (the name being moved) do not count."""
    import extra
    corpus = plan.corpus
    have = [f for f in corpus.closure(rel) if f != rel and f.endswith('.h')]
    new = [f for f in corpus.closure(h) if f.endswith('.h') and f not in set(have)]
    if not new:
        return ''
    seen_fn, seen_data = defaultdict(list), defaultdict(list)
    for f in have + [rel]:
        for r in plan.sites_by_path.get(f, []):
            if getattr(r.site, 'kind', '') != 'data' and not (f == rel and r.site.name == moved):
                seen_fn[r.site.name].append(r)
        for x in plan.data_by_path.get(f, []):
            if not x.is_def and not (f == rel and x.name == moved):
                seen_data[x.name].append(x)
    for f in new:
        for r in plan.sites_by_path.get(f, []):
            if getattr(r.site, 'kind', '') == 'data':
                continue
            for y in seen_fn.get(r.site.name, ()):
                if not _compatible(r, y):
                    return 'existing_header_closure:%s@%s~%s' % (r.site.name, f, y.site.path)
        for x in plan.data_by_path.get(f, []):
            if x.is_def:
                continue
            for y in seen_data.get(x.name, ()):
                if extra.data_key(x, plan.tindex) != extra.data_key(y, plan.tindex):
                    return 'existing_header_closure:%s@%s~%s' % (x.name, f, y.path)
    return ''


def plan_tus(plan, files, names, log=print):
    """{rel: merged TuPlan}, {(rel, name): static hold reason}: each name planned alone (plan_tu over that
    name's sites only), then the passing names of a TU merged into one TuPlan."""
    import plan as P
    tus, static = {}, {}
    declared = {}
    t0 = time.monotonic()
    for rel in files:
        own = plan.sites_by_path.get(rel, [])
        mine = sorted({r.site.name for r in own if r.site.name in names})
        merged = P.TuPlan(rel)
        for n in mine:
            rows = [r for r in own if r.site.name == n]
            plan.sites_by_path[rel] = rows
            try:
                tp = P.plan_tu(plan, rel)
            finally:
                plan.sites_by_path[rel] = own
            removes = [r for r in tp.remove if r.site.name == n]
            if not removes:
                why = next((r.reason for r in rows if r.reason), '') or 'not_planned'
                hs = {owner_of(plan, r)[0] for r in rows} - {''}
                why = next((tp.holds[h] for h in sorted(hs) if h in tp.holds), why)
                static[(rel, n)] = why
                continue
            hs = {plan.fn_for_def(r.definition).header for r in removes}
            conflict = companion_conflict(plan, rel, n, own, hs, declared)
            if conflict:
                static[(rel, n)] = conflict
                continue
            merged.remove += removes
            for h in sorted(hs):
                if h not in merged.add:
                    merged.add.append(h)
                if tp.append.get(h):
                    merged.append[h] = sorted(set(merged.append.get(h, [])) | set(tp.append[h]))
            merged.drop_typedefs += [d for d in tp.drop_typedefs if d[0] in hs and d not in merged.drop_typedefs]
        if merged.remove:
            tus[rel] = merged
    log('per-name TU plans: %d TUs with edits, %d static holds in %.0f s' % (
        len(tus), len(static), time.monotonic() - t0))
    return tus, static


# ------------------------------------------------------------------ lint gate

def lint_increases(result):
    """(rising groups, new compile failures) from lint_closure's closure_result.json."""
    import lint_closure as LC
    plan = result.get('plan', {})
    renames = plan.get('renames') or {}
    rising = LC.increases(result.get('base_findings', []), result.get('head_findings', []), renames)
    back = {old: new for new, old in renames.items()}
    base_failed = {(back.get(f['tu'], f['tu']), f['mode'], f['phase']) for f in result.get('base_failures', [])}
    failures = [f for f in result.get('head_failures', []) if (f['tu'], f['mode'], f['phase']) not in base_failed]
    return rising, failures


def lint_blame(bulk, rising, failures, closure_of):
    """Restore the edited TUs a lint finding names: the TU itself (a .c warning file or failing TU), else every
    edited TU whose added headers' include closure contains the warning's header.  Returns the restored TUs
    (empty: nothing attributable)."""
    acc = bulk.accepted()
    hit = {}
    for f in failures:
        if f['tu'] in acc:
            hit.setdefault(f['tu'], 'lint_compile_failure:%s' % f.get('first_error', '')[:120])
    for row in rising:
        why = 'lint_new_warning:%s:%s' % (row['warning'], row['function'])
        if row['file'] in acc:
            hit.setdefault(row['file'], why)
            continue
        for rel, hs in acc.items():
            if any(row['file'] == h or row['file'] in closure_of(h) for h in hs):
                hit.setdefault(rel, why)
    for rel, why in hit.items():
        bulk.restore_tu(rel, why)
    return sorted(hit)


class LintGate:
    def __init__(self, root, port, out, jobs, log):
        self.root, self.port, self.out, self.jobs, self.log = root, port, out, jobs, log
        self.runs = []
        self.bulk = None

    def __call__(self, state, texts):
        n = len(self.runs) + 1
        out = self.out / ('lint%d' % n)
        cmd = [sys.executable, str(self.root / 'tools/lint/lint_closure.py'), 'HEAD', '--root', str(self.root),
               '--port', str(self.port), '--jobs', str(self.jobs), '--out', str(out)]
        t0 = time.monotonic()
        res = subprocess.run(cmd, cwd=self.root, capture_output=True, text=True)
        (self.out / ('lint%d.log' % n)).write_text(res.stdout + res.stderr)
        tail = [l for l in res.stdout.splitlines() if l.startswith(('lint closure', 'NEW', 'decl'))]
        row = dict(run=n, rc=res.returncode, seconds=round(time.monotonic() - t0, 1), lines=tail[-12:])
        self.runs.append(row)
        verdict = [l for l in tail if l.startswith('lint closure')] or tail or [res.stdout.strip()[-200:]]
        self.log('lint %d: rc %d in %.0f s: %s' % (n, res.returncode, row['seconds'], verdict[-1]))
        if res.returncode == 0:
            return 0
        try:
            result = json.loads((out / 'closure_result.json').read_text())
        except (OSError, ValueError):
            raise RuntimeError('lint_closure failed without a result: ' + (res.stdout + res.stderr)[-600:])
        rising, failures = lint_increases(result)
        corpus = self.bulk.plan.corpus
        restored = lint_blame(self.bulk, rising, failures, lambda h: set(corpus.closure(h)))
        row['restored'] = restored
        if not restored:
            # the declaration agreement step (or a finding outside the edited TUs' closures) failed
            raise RuntimeError('lint_closure failed with nothing attributable to an edited TU: ' +
                               ' | '.join(tail[-6:]))
        self.log('  lint blame: restored %d TUs' % len(restored))
        return len(restored)


# ------------------------------------------------------------------ outcome

def outcomes(plan, sites, selected, static, bulks):
    """{(rel, name): ('kept', '') | ('held', reason)} for every local site file of the selected names.
    bulks: [(Bulk, names it moved)] in order; a later Bulk's verdict for a (rel, name) overrides."""
    out = {}
    for n in selected:
        for r in sites.get(n, []):
            rel = r.site.path
            if (rel, n) in static:
                out[(rel, n)] = ('held', static[(rel, n)])
            else:
                out.setdefault((rel, n), ('held', 'not_planned'))
    for bulk, names in bulks:
        acc = bulk.accepted()
        held = {}
        for rel, h, why in bulk.holds:
            held.setdefault((rel, h), why)
        for rel, tp in bulk.plan.tus.items():
            for r in tp.remove:
                n = r.site.name
                if n not in names or (rel, n) not in out:
                    continue
                h = plan.fn_for_def(r.definition).header
                if rel in bulk.restored:
                    out[(rel, n)] = ('held', bulk.restored[rel])
                elif (rel, h) in held:
                    out[(rel, n)] = ('held', held[(rel, h)])
                elif rel in acc and h in acc[rel]:
                    out[(rel, n)] = ('kept', '')
    return out


def receipt_rows(selected, kinds, outs):
    rows = []
    for n in selected:
        mine = {rel: v for (rel, m), v in outs.items() if m == n}
        kept = sorted(rel for rel, (st, _) in mine.items() if st == 'kept')
        held = {rel: why for rel, (st, why) in mine.items() if st == 'held'}
        by_cat = Counter(category(w) for w in held.values())
        status = 'kept' if kept and not held else 'partial' if kept else 'held'
        rows.append(dict(name=n, kind=kinds.get(n, ''), files=len(mine), kept=len(kept), held=len(held),
                         status=status, held_by_reason=dict(by_cat), kept_files=kept,
                         held_files={rel: dict(reason=category(w), raw=w) for rel, w in sorted(held.items())}))
    return rows


def _tsv(path, header, rows):
    with open(path, 'w') as fh:
        fh.write('\t'.join(header) + '\n')
        for r in rows:
            fh.write('\t'.join(str(x) for x in r) + '\n')


# ------------------------------------------------------------------ main

def install_sigterm_exit():
    """A terminated trial exits through SystemExit, so restoring() puts the baseline texts back as for ^C."""
    import signal
    signal.signal(signal.SIGTERM, lambda signum, frame: sys.exit(128 + signum))


@contextlib.contextmanager
def restoring(disk, log=print):
    """Restore every baseline text (disk.restore()) when the body fails, is interrupted or is terminated."""
    try:
        yield
    except BaseException:
        disk.restore()
        log('failed/interrupted: every file restored')
        raise


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=HERE.parents[1])
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument('--names', nargs='+', help='names to try, in this order')
    g.add_argument('--names-file', type=Path, help='one name per line (# comments allowed)')
    g.add_argument('--top', type=int, help='the N most-declared reachable names')
    ap.add_argument('--exclude-names-file', type=Path, help='names never tried (one per line)')
    ap.add_argument('--recent-repo', type=Path, help='repository whose recent commit subjects exclude names')
    ap.add_argument('--recent', type=int, default=0, help='number of recent commit subjects (with --recent-repo)')
    ap.add_argument('--address-functions', action='store_true', help='rank func_<addr> names too')
    ap.add_argument('--append', action='store_true',
                    help='publish a missing owner declaration (append-only, the definition\'s prototype)')
    ap.add_argument('--lint-port', type=Path, help='native port directory for lint_closure (required unless --no-lint)')
    ap.add_argument('--no-lint', action='store_true', help='skip the lint_closure gate')
    ap.add_argument('--lint-jobs', type=int, default=2)
    ap.add_argument('--port-adapt', type=Path, help="the native port's tools/adapt.py (adaptation anchors)")
    ap.add_argument('--workers', type=int, default=2)
    ap.add_argument('--max-rounds', type=int, default=10)
    ap.add_argument('--no-retry', action='store_true', help='do not retry restored multi-name TUs per name')
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--plan-only', action='store_true', help='static yield only: no writes, no compile')
    ap.add_argument('--dry-run', action='store_true', help='prove and lint, then restore every file')
    a = ap.parse_args(argv)
    if not (a.no_lint or a.plan_only or a.lint_port):
        ap.error('--lint-port is required (or --no-lint)')
    if a.port_adapt and not a.port_adapt.is_file():
        ap.error('--port-adapt %s is not a file (the anchors would silently be empty)' % a.port_adapt)
    if not 1 <= a.workers <= 8:
        ap.error('between 1 and 8 workers on this host')
    root = a.root.resolve()
    a.out.mkdir(parents=True, exist_ok=True)
    logf = open(a.out / 'trial.log', 'a')

    def log(msg):
        line = time.strftime('%H:%M:%S ') + msg
        print(line, flush=True)
        logf.write(line + '\n')
        logf.flush()

    started = time.monotonic()
    # a terminated trial restores the baseline texts like an interrupted one (restoring() below)
    install_sigterm_exit()
    import extern_bulk as B
    import extern_wave as EW
    plan = load_plan(root, log)
    floors = floors_of(root)
    exclude = set()
    if a.exclude_names_file:
        exclude |= {l.split('#')[0].strip() for l in a.exclude_names_file.read_text().splitlines()} - {''}
    exclude |= recent_subject_names(a.recent_repo, a.recent)
    names = a.names
    if a.names_file:
        names = [l.split('#')[0].strip() for l in a.names_file.read_text().splitlines()]
        names = [n for n in names if n]
    selected, skipped = select(plan, floors, a.top, names, exclude, a.address_functions)
    if names is not None:
        for n, why in skipped.items():
            log('skip %s: %s' % (n, why))
    log('selected %d names%s' % (len(selected), ' (top %d)' % a.top if a.top else ''))
    sites = local_sites(plan)
    kinds = {n: ('data' if any(getattr(r.site, 'kind', '') == 'data' for r in sites.get(n, [])) else 'function')
             for n in selected}
    decoded = decoded_sources(root)
    files = sorted({r.site.path for n in selected for r in sites.get(n, [])} - decoded)
    static = {}
    for n in selected:
        for r in sites.get(n, []):
            if r.site.path in decoded:
                static[(r.site.path, n)] = 'decoded_image_source'
    tus, static_tu = plan_tus(plan, files, set(selected), log)
    static.update(static_tu)
    owners = {}
    for n in selected:
        hs = Counter(owner_of(plan, r)[0] or owner_of(plan, r)[1] for r in sites.get(n, []))
        owners[n] = hs.most_common(1)[0][0] if hs else ''
    owner_headers = {h for h in owners.values() if h.startswith('include/')}

    def writable(h, exists):
        return a.append and exists and h in owner_headers

    def make_bulk(tu_plans, names_):
        p = copy.copy(plan)
        p.tus = {rel: copy.copy(tp) for rel, tp in tu_plans.items()}
        b = B.Bulk(root, sorted(p.tus), True, writable, log, data_named_only=True, names=set(names_), plan=p)
        if a.port_adapt:
            b.keep_anchors(B.port_anchors(a.port_adapt))
        return b
    bulk = make_bulk(tus, selected)
    # the planner's append rows: without --append a needed append holds the TU (header_not_writable)
    texts0 = bulk.texts()
    bulks = [(bulk, set(selected))]

    def write_receipt(state_note, proofs=(), lint_runs=(), changed=(), before=None, after=None):
        outs = outcomes(plan, sites, selected, static, bulks)
        rows = receipt_rows(selected, kinds, outs)
        for r in rows:
            r['owner'] = owners.get(r['name'], '')
        held_by = Counter()
        for r in rows:
            held_by.update(r['held_by_reason'])
        res = dict(state=state_note, names_tried=len(selected), names_skipped=skipped if names is not None else
                   dict(Counter(skipped.values())),
                   names_kept=sum(r['status'] == 'kept' for r in rows),
                   names_partial=sum(r['status'] == 'partial' for r in rows),
                   names_held=sum(r['status'] == 'held' for r in rows),
                   sites_kept=sum(r['kept'] for r in rows), sites_held=sum(r['held'] for r in rows),
                   sites_held_by_reason=dict(held_by),
                   names_held_by_reason=dict(Counter(max(r['held_by_reason'], key=r['held_by_reason'].get)
                                                     for r in rows if r['status'] == 'held')),
                   files_changed=sorted(changed), local_externs_before=before, local_externs_after=after,
                   proofs=list(proofs), lint=list(lint_runs), seconds=round(time.monotonic() - started, 1),
                   names=rows)
        (a.out / 'receipt.json').write_text(json.dumps(res, indent=1) + '\n')
        _tsv(a.out / 'names.tsv', ('name', 'kind', 'owner', 'files', 'kept', 'held', 'status', 'held_by_reason'),
             ((r['name'], r['kind'], r['owner'], r['files'], r['kept'], r['held'], r['status'],
               ','.join('%s=%d' % kv for kv in sorted(r['held_by_reason'].items()))) for r in rows))
        _tsv(a.out / 'sites.tsv', ('name', 'file', 'outcome', 'reason', 'raw'),
             ((n, rel, st, category(w) if st == 'held' else '', w) for (rel, n), (st, w) in sorted(outs.items(),
                                                                                                   key=lambda kv: (kv[0][1], kv[0][0]))))
        log('receipt: %d names tried, %d kept, %d partial, %d held; sites kept %d held %d %s' % (
            res['names_tried'], res['names_kept'], res['names_partial'], res['names_held'], res['sites_kept'],
            res['sites_held'], dict(held_by)))
        return res
    if a.plan_only:
        changed = sorted(f for f in texts0 if f.endswith('.c'))
        before = sum(EW.local_externs(f, EW.read(root, f)) for f in changed)
        after = sum(EW.local_externs(f, texts0[f]) for f in changed)
        write_receipt('plan_only', changed=changed, before=before, after=after)
        return 0
    originals = {f: EW.read(root, f) for f in set(texts0) | set(bulk.jobs)}
    prover = B.Prover(root, bulk.plan, originals, a.workers, a.out / 'reuse.json', log)
    disk = B.DiskState(root, originals, log)
    gate = None
    if not a.no_lint:
        gate = LintGate(root, a.lint_port.resolve(), a.out, a.lint_jobs, log)
        gate.bulk = bulk
    proofs = []
    with restoring(disk, log):
        state, rows = B.settle(bulk, prover, disk, max_rounds=a.max_rounds, log=log, out=a.out, after_pass=gate)
        proofs += rows
        # retry, one name at a time, the names of TUs restored with another selected name
        if not a.no_retry:
            multi = defaultdict(set)
            for rel, tp in bulk.plan.tus.items():
                if rel in bulk.restored and len({r.site.name for r in tp.remove}) > 1 and \
                        not bulk.restored[rel].startswith('port_adaptation_anchor'):
                    for r in tp.remove:
                        multi[r.site.name].add(rel)
            kept_in = defaultdict(set)          # rel -> names a retry kept there (the next retry builds on them)
            for n in sorted(multi, key=selected.index):
                sub = {}
                for rel in sorted(multi[n]):
                    tp = copy.copy(tus[rel])
                    tp.remove = [r for r in tp.remove if r.site.name == n or r.site.name in kept_in[rel]]
                    hs = {plan.fn_for_def(r.definition).header for r in tp.remove}
                    tp.add = [h for h in tp.add if h in hs]
                    tp.append = {h: v for h, v in tp.append.items() if h in hs}
                    tp.drop_typedefs = [d for d in tp.drop_typedefs if d[0] in hs]
                    sub[rel] = tp
                b2 = make_bulk(sub, {n} | {m for rel in sub for m in kept_in[rel]})
                if not b2.jobs:
                    continue
                log('retry %s alone in %d TUs' % (n, len(b2.jobs)))
                if gate:
                    gate.bulk = b2
                st2, rows = B.settle(b2, prover, disk, max_rounds=a.max_rounds, log=log, out=a.out,
                                     extra=state, after_pass=gate, tag='r%s_' % n)
                proofs += rows
                state = st2 or state
                for rel, hs in b2.accepted().items():
                    if any(plan.fn_for_def(r.definition).header in hs
                           for r in b2.plan.tus[rel].remove if r.site.name == n):
                        kept_in[rel].add(n)
                b2.restored = {rel: 'retry:' + why for rel, why in b2.restored.items()}
                b2.holds = [(rel, h, 'retry:' + why) for rel, h, why in b2.holds]
                bulks.append((b2, {n}))
        final = {f: EW.read(root, f) for f in originals}
        changed = sorted(f for f in originals if final[f] != originals[f] and f != B.LAYOUT_INLINE)
        before = sum(EW.local_externs(f, originals[f]) for f in changed if f.endswith('.c'))
        after = sum(EW.local_externs(f, final[f]) for f in changed if f.endswith('.c'))
        import difflib
        patch = []
        for f in changed:
            patch.extend(difflib.unified_diff((originals[f] or '').splitlines(True), (final[f] or '').splitlines(True),
                                              'a/' + f, 'b/' + f))
        (a.out / 'trial.patch').write_text(''.join(patch))
        write_receipt('dry_run' if a.dry_run else 'applied', proofs, gate.runs if gate else (), changed, before, after)
        if a.dry_run:
            disk.restore()
            log('dry run: every file restored')
        return 0


if __name__ == '__main__':
    sys.exit(main())
