#!/usr/bin/env python3
"""One true prototype per function, in a real header (tools/headers).

    python3 tools/headers/headers.py table  --out DIR                 prototypes/sites/conflicts/data TSVs
    python3 tools/headers/headers.py dryrun [--scope src/x ...]       per-folder counts, no writes
    python3 tools/headers/headers.py apply  --scope src/x ... --out DIR [--workers N] [--dry-run | --decide-only]
    python3 tools/headers/headers.py explain --tu src/x/y.c --header include/x.h      why one hold

Layout: src/<a>/<b>/*.c define the functions declared in include/<a>/<b>.h (see plan.py).  apply writes
the needed headers, removes each scope TU's local declarations of published functions and includes the
owning headers instead.  Every TU edit is decided by its assembly at the registered recipe (prove.py):
a header whose include changes bytes or fails to compile stays a (TU, header) hold and the TU keeps its
local declarations for it.  The formal proof is tools/typing/tu_identity.py snapshot/compare.

Deterministic and rerunnable: everything is keyed by function name and recomputed from the tree, so a
newer HEAD (merged/moved/renamed files) just regenerates headers and re-points includes.
"""
from __future__ import annotations

import argparse
import json
import sys
from collections import Counter, defaultdict
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent)]

import model as M        # noqa: E402
import plan as P         # noqa: E402
import rewrite as R      # noqa: E402

ROOT = HERE.parent.parent


def _tsv(path, header, rows):
    with open(path, 'w') as fh:
        fh.write('\t'.join(header) + '\n')
        for r in rows:
            fh.write('\t'.join(str(x).replace('\t', ' ').replace('\n', ' ') for x in r) + '\n')


def header_of_row(plan):
    def f(r):
        fr = plan.fn_for_def(r.definition)
        return fr.header
    return f


def mechanism(cls):
    return {
        'unprototyped_hazard': 'K&R site; definition has char/short/float params: a prototype converts '
                               'arguments at the call -> byte proof per caller (prove.py), else keep',
        'param_width': 'site declares a different integer width than the definition: prototype converts '
                       'arguments -> byte proof per caller',
        'return_width': 'site expects a different return width: caller extension changes -> byte proof',
        'return_kind': 'int vs pointer return: pointer arithmetic on the result scales -> byte proof',
        'arity': 'site and definition disagree on parameter count -> recover the true formals (unused '
                 'arguments the callers pass) in the definition first',
        'varargs': "site declares '...' -> recover the definition's real parameters",
        'def_varargs': 'definition is varargs; sites are fixed -> decide which is original',
        'struct_by_value': 'site passes words where the definition takes a struct by value -> keep',
        'complex': 'function-pointer-returning declarator -> hand review',
        'no_c_definition': 'no C definition (asm, retail SLUS library, Psy-Q) -> keep or route to a '
                           'library header (owner ruling)',
        'cross_container': 'definition only in another overlay image -> keep (cannot link)',
        'multi_definition_conflict': 'several definitions in one image with different prototypes -> '
                                     'unify the copies first',
        'static_only': 'only a static definition exists -> keep',
        'same_file_static': 'the site redeclares a static of its own file -> keep',
    }.get(cls, '')


def cmd_table(a):
    plan = P.build(a.root, include_data=a.data)
    out = Path(a.out)
    out.mkdir(parents=True, exist_ok=True)
    gen = plan.generated
    sites = [r for r in plan.sites if r.site.path not in gen]
    by_fn = defaultdict(list)
    for r in sites:
        if r.definition is not None:
            by_fn[(r.definition.path, r.definition.name)].append(r)
    rows = []
    for key, fr in sorted(plan.functions.items()):
        d = fr.definition
        if d is None:
            cands = [x for x in plan.defs[fr.name] if not x.static]
            rows.append((fr.name, '', ';'.join(f'{x.path}:{x.line}' for x in cands), '', 'hold', fr.reason,
                         '', 0, ''))
            continue
        ss = by_fn.get((d.path, d.name), [])
        cc = Counter(r.cls for r in ss)
        rows.append((fr.name, d.container, f'{d.path}:{d.line}', fr.header if fr.status == 'header' else '',
                     fr.status, fr.reason, fr.proto or d.proto, len(ss),
                     ','.join(f'{k}={v}' for k, v in sorted(cc.items()))))
    _tsv(out / 'prototypes.tsv', ('function', 'container', 'definition', 'header', 'status', 'reason',
                                  'prototype', 'decl_sites', 'site_classes'), rows)
    srows = []
    for r in sorted(sites, key=lambda r: (r.site.path, r.site.line, r.site.name)):
        srows.append((r.site.path, r.site.line, r.site.name, r.site.storage or 'plain',
                      'header' if r.site.in_header else 'c', r.cls, r.detail, r.risk,
                      f'{r.definition.path}:{r.definition.line}' if r.definition else '',
                      ' '.join(r.site.text.split())[:160]))
    _tsv(out / 'sites.tsv', ('path', 'line', 'function', 'storage', 'where', 'class', 'detail', 'risk',
                             'definition', 'declaration'), srows)
    # conflicts: one row per (function, class) that is not a plain identical/spelling site, plus holds
    crow = []
    grouped = defaultdict(list)
    for r in sites:
        if r.cls in ('identical', 'spelling'):
            continue
        grouped[(r.fn, r.cls)].append(r)
    for (fn, cls), rs in sorted(grouped.items()):
        d = rs[0].definition
        paths = sorted({f'{r.site.path}:{r.site.line}' for r in rs})
        crow.append((fn, cls, M.risk(cls) if d else 'never', len(rs), ';'.join(paths[:6]) + (';...' if len(paths) > 6 else ''),
                     (d.proto if d else ''), mechanism(cls) or ('compatible spelling; unified to the definition'
                                                                if M.risk(cls) == 'safe' else '')))
    for key, fr in sorted(plan.functions.items()):
        if fr.status == 'hold':
            crow.append((fr.name, 'function_hold:' + fr.reason.split(':')[0], 'never', 0, '',
                         fr.definition.proto if fr.definition else '',
                         {'local_type_anonymous': 'a parameter type is an anonymous struct only its .c declares -> '
                                                  'move the type to a shared header (type consolidation)',
                          'local_type': 'a parameter type only its .c declares -> move the type to a header',
                          'multi_definition_conflict': 'copies of one function disagree -> unify the copies',
                          'multi_container_conflict': 'overlay copy shadows a resident function with another '
                                                      'prototype -> unify',
                          'varargs_definition': 'varargs definition -> hand review',
                          'knr_definition': 'K&R definition -> prototype it first (byte proof)',
                          'unknown_type': 'type not declared anywhere -> fix the definition',
                          'name_is_macro': 'a header macro has the same name'}.get(fr.reason.split(':')[0], fr.reason)))
    _tsv(out / 'conflicts.tsv', ('function', 'class', 'risk', 'sites', 'where', 'definition', 'mechanism_next_step'),
         crow)
    # data externs (lower priority): type agreement per name
    dd = defaultdict(list)
    for x in plan.data:
        if x.path in gen:
            continue
        dd[x.name].append(x)
    drows = []
    for n, xs in sorted(dd.items()):
        defs_ = [x for x in xs if x.is_def and x.storage != 'static' and x.path.endswith('.c')]
        ext = [x for x in xs if not x.is_def]
        if not ext:
            continue
        views = Counter(' '.join(x.spec) + ' ' + '*' * x.ptr + x.suffix.replace(' ', '') for x in ext)
        cls = 'no_c_definition' if not defs_ else ('consistent' if len(views) == 1 else 'type_views_differ')
        drows.append((n, cls, len(ext), len(views), ';'.join(f'{x.path}:{x.line}' for x in defs_[:3]),
                      ' | '.join(f'{v} x{c}' for v, c in views.most_common(4))))
    _tsv(out / 'data_externs.tsv', ('symbol', 'class', 'extern_sites', 'distinct_views', 'c_definition', 'views'), drows)
    _tsv(out / 'sdk_classification.tsv', ('path', 'line', 'symbol', 'category', 'library', 'canonical',
         'header', 'status', 'reason', 'evidence'), plan.sdk_census)
    import extra
    legacy = extra.legacy_data_census(plan)
    legacy_counts = Counter(r[0] for r in legacy)
    _tsv(out / 'data_externs_plan.tsv', ('symbol', 'status', 'reason', 'extern_sites', 'distinct_views',
         'headers', 'c_definition', 'views', 'declaration', 'legacy_header_sites', 'global_status',
         'global_reason'),
         [(*r, legacy_counts[r[0]], 'hold' if r[1] == 'hold' or legacy_counts[r[0]] else 'candidate',
           r[2] or ('legacy_header_fold' if legacy_counts[r[0]] else '')) for r in plan.data_census])
    _tsv(out / 'data_legacy_headers.tsv', ('symbol', 'legacy_header', 'line', 'plan_status', 'plan_reason',
         'generated_owners', 'planned_owners', 'legacy_declaration', 'next_step'), legacy)
    c = Counter(r.cls for r in sites if not r.site.in_header)
    print(json.dumps({'functions': len(plan.functions), 'published': sum(1 for f in plan.functions.values()
                                                                         if f.status == 'header'),
                      'headers': len(plan.headers), 'c_sites_by_class': dict(c.most_common())}, indent=1))


def dryrun_plan(root, scope, data=False):
    plan = P.build(root, scope=scope or ['src'], include_data=data)
    return plan


def summarize(plan, verdicts=None):
    """Per-folder counts for a plan (optionally after prove verdicts)."""
    per = defaultdict(Counter)
    holds = Counter()
    used_headers = set()
    for rel, tp in sorted(plan.tus.items()):
        folder = rel.rsplit('/', 1)[0]
        c = per[folder]
        c['tus'] += 1
        accepted = tp.add if verdicts is None else verdicts.get(rel, {}).get('accept', [])
        hv = {} if verdicts is None else verdicts.get(rel, {}).get('holds', {})
        if accepted or tp.stale:
            orig = plan.corpus.text(rel)
            edit = R.tu_edit(tp, lambda r: plan.fn_for_def(r.definition).header)
            if R.edit_tu(orig, edit, accepted) == orig:      # already applied
                accepted = []
            else:
                c['tus_changed'] += 1
        c['includes_added'] += len(accepted)
        c['decls_removed'] += sum(1 for r in tp.remove if plan.fn_for_def(r.definition).header in accepted)
        c['decls_kept'] += sum(1 for r in plan.sites_by_path.get(rel, []) if r.site.storage != 'static') - \
            sum(1 for r in tp.remove if plan.fn_for_def(r.definition).header in accepted)
        for h, why in list(tp.holds.items()) + list(hv.items()):
            holds[why.split(':')[0]] += 1
            c['tu_header_holds'] += 1
        used_headers.update(accepted)
    return per, holds, used_headers


def folder_table(plan, verdicts, jobs):
    """Per-folder counts after byte decisions (TUs without a job are unchanged)."""
    per = defaultdict(Counter)
    for rel, tp in sorted(plan.tus.items()):
        c = per[rel.rsplit('/', 1)[0]]
        c['tus'] += 1
        v = verdicts.get(rel, {})
        acc = set(v.get('accept', [])) if rel in jobs else set()
        removed = sum(1 for r in tp.remove if plan.fn_for_def(r.definition).header in acc)
        if rel in jobs and (acc or tp.stale):
            c['changed'] += 1
        c['removed'] += removed
        c['kept'] += sum(1 for r in plan.sites_by_path.get(rel, []) if r.site.storage != 'static') - removed
        c['incl'] += len(acc)
        c['holds'] += len(tp.holds) + len(v.get('holds', {}))
    lines = [f'{"folder":48} {"tus":>5} {"changed":>7} {"removed":>7} {"kept":>6} {"incl+":>6} {"holds":>6}']
    tot = Counter()
    for f in sorted(per):
        c = per[f]
        tot.update(c)
        lines.append(f'{f:48} {c["tus"]:5} {c["changed"]:7} {c["removed"]:7} {c["kept"]:6} {c["incl"]:6} {c["holds"]:6}')
    lines.append(f'{"TOTAL":48} {tot["tus"]:5} {tot["changed"]:7} {tot["removed"]:7} {tot["kept"]:6} {tot["incl"]:6} '
                 f'{tot["holds"]:6}')
    return '\n'.join(lines) + '\n'


def cmd_dryrun(a):
    plan = dryrun_plan(a.root, a.scope, a.data)
    per, holds, used = summarize(plan)
    tot = Counter()
    lines = []
    lines.append(f'{"folder":48} {"tus":>5} {"changed":>7} {"removed":>7} {"kept":>6} {"incl+":>6} {"holds":>6}')
    for folder in sorted(per):
        c = per[folder]
        tot.update(c)
        lines.append(f'{folder:48} {c["tus"]:5} {c["tus_changed"]:7} {c["decls_removed"]:7} {c["decls_kept"]:6} '
                     f'{c["includes_added"]:6} {c["tu_header_holds"]:6}')
    lines.append(f'{"TOTAL":48} {tot["tus"]:5} {tot["tus_changed"]:7} {tot["decls_removed"]:7} {tot["decls_kept"]:6} '
                 f'{tot["includes_added"]:6} {tot["tu_header_holds"]:6}')
    fh = Counter(f.status + ':' + f.reason.split(':')[0] for f in plan.functions.values())
    lines.append('')
    lines.append(f'headers to create: {len(used)} (of {len(plan.headers)} owning headers)')
    lines.append('functions: ' + ', '.join(f'{k}={v}' for k, v in sorted(fh.items())))
    lines.append('TU-level holds by reason: ' + ', '.join(f'{k}={v}' for k, v in holds.most_common()))
    kept = Counter()
    for rel, tp in plan.tus.items():
        for r in plan.sites_by_path.get(rel, []):
            if r.site.storage == 'static' or r in tp.remove:
                continue
            kept[(r.reason or r.cls).split(':')[0] + (':' + r.reason.split(':')[1] if r.reason.startswith(
                'function_held') else '')] += 1
    lines.append('declarations kept by reason: ' + ', '.join(f'{k}={v}' for k, v in kept.most_common()))
    lines.append('SDK/no-C site classification: ' + ', '.join(f'{k}={v}' for k, v in
                 Counter(r[3] for r in plan.sdk_census).most_common()))
    lines.append('data plan (enabled=%s): ' % a.data + ', '.join(f'{k}={v}' for k, v in
                 Counter(r[2] or r[1] for r in plan.data_census).most_common()))
    text = '\n'.join(lines) + '\n'
    if a.list_edits:
        Path(a.list_edits).write_text(''.join(rel + '\n' for rel, tp in sorted(plan.tus.items())
                                              if tp.add or tp.stale))
    if a.out:
        Path(a.out).write_text(text)
    print(text)


def write_headers(root, plan, headers, saved=None):
    written = []
    for h in sorted(headers):
        p = Path(root) / h
        txt = R.header_text(plan, h)
        if p.exists():
            old = p.read_text()
            if P.GENERATED_MARK not in old[:400]:
                raise SystemExit(f'refusing to overwrite hand-written header {h}')
            if old == txt:
                continue
            if saved is not None:
                saved[h] = old
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(txt)
        written.append(h)
    return written


def cmd_apply(a):
    if a.dry_run:            # static per-folder counts for the scope, no writes, no compiler
        a.list_edits = None
        cmd_dryrun(argparse.Namespace(root=a.root, scope=a.scope, out=None, list_edits=None, data=a.data))
        return
    root = Path(a.root).resolve()
    plan = P.build(root, scope=a.scope, include_data=a.data)
    hof = header_of_row(plan)
    jobs = {}
    for rel, tp in sorted(plan.tus.items()):
        if tp.add or tp.stale:
            orig = plan.corpus.text(rel)
            edit = R.tu_edit(tp, hof)
            if R.edit_tu(orig, edit) == orig:      # already applied (rerun): nothing to decide
                continue
            jobs[rel] = (orig, edit)
    needed = sorted({h for _, e in jobs.values() for h in e['add']})
    # regenerate every generated header that exists (owners may have moved) plus the needed ones
    regen = sorted(set(needed) | {h for h in plan.generated if h in plan.headers})
    created_before = {h for h in regen if not (root / h).exists()}
    saved = {}
    headers_written = write_headers(root, plan, regen, saved)
    print(f'plan: {len(jobs)} TUs with edits, {len(needed)} headers needed', flush=True)
    if a.no_prove:
        verdicts = {rel: {'tu': rel, 'accept': e['add'], 'holds': {}} for rel, (o, e) in jobs.items()}
    else:
        sys.path.insert(0, str(root / 'tools'))
        import layout_compile_identity as L
        import prove
        recipes, _ = L.recipes(root)
        verdicts = prove.run(root, jobs, recipes, workers=a.workers)
    if a.decide_only:
        for h in sorted(created_before):
            (root / h).unlink()
        for h, old in saved.items():
            (root / h).write_text(old)
        created_before = set()
    edited, holds = [], []
    used = set()
    for rel, (orig, edit) in sorted(jobs.items()):
        v = verdicts.get(rel, {'accept': [], 'holds': {}})
        acc = v['accept']
        for h, why in sorted(v.get('holds', {}).items()):
            holds.append((rel, h, why))
        if v.get('baseline_error'):
            holds.append((rel, '*', 'baseline_error: ' + v['baseline_error']))
        new = R.edit_tu(orig, dict(edit, drop=edit.get('drop', [])), acc)
        if not acc and edit.get('drop'):
            new = R.edit_tu(orig, dict(edit, add=[]), [])
        if new != orig:
            if not a.decide_only:
                (root / rel).write_bytes(new.encode('utf-8', 'surrogateescape'))
            edited.append(rel)
        used.update(acc)
    for rel, tp in sorted(plan.tus.items()):
        for h, why in sorted(tp.holds.items()):
            holds.append((rel, h, why))
    # generated headers whose folder no longer defines anything: delete when the scope is the whole tree
    orphans = sorted(h for h in plan.generated if h not in plan.headers)
    if orphans and a.scope == ['src'] and not a.decide_only:
        for h in orphans:
            (root / h).unlink()
    # remove headers created by this run that no accepted edit uses
    removed = []
    for h in sorted(created_before - used):
        (root / h).unlink()
        removed.append(h)
    out = Path(a.out)
    out.mkdir(parents=True, exist_ok=True)
    (out / 'edited.txt').write_text(''.join(e + '\n' for e in edited))
    _tsv(out / 'apply_holds.tsv', ('tu', 'header', 'reason'), holds)
    summary = {'scope': a.scope, 'decide_only': bool(a.decide_only), 'tus_planned': len(plan.tus), 'tus_with_edits': len(jobs), 'tus_edited': len(edited),
               'headers_written': headers_written,
               'headers_used': sorted(used), 'headers_unused_removed': removed, 'orphan_generated_headers': orphans,
               'decls_removed': sum(1 for rel, (o, e) in jobs.items() for h, s, t in e['remove']
                                    if h in verdicts.get(rel, {}).get('accept', [])),
               'data_decls_removed': sum(1 for rel, tp in plan.tus.items() for r in tp.remove
                                    if getattr(r.site, 'kind', '') == 'data' and
                                    plan.fn_for_def(r.definition).header in verdicts.get(rel, {}).get('accept', [])),
               'holds_by_reason': dict(Counter(w.split(':')[0] for _, _, w in holds).most_common())}
    (out / 'apply_summary.json').write_text(json.dumps(summary, indent=1) + '\n')
    (out / 'verdicts.jsonl').write_text(''.join(json.dumps({k: v for k, v in verdicts[r].items() if k != 'base'},
                                                           sort_keys=True) + '\n' for r in sorted(verdicts)))
    (out / 'folders.txt').write_text(folder_table(plan, {r: v for r, v in verdicts.items()}, jobs))
    print(json.dumps({k: v for k, v in summary.items() if k != 'headers_used'}, indent=1))


def cmd_explain(a):
    root = Path(a.root).resolve()
    plan = P.build(root, scope_files=[a.tu], include_data=a.data)
    tp = plan.tus[a.tu]
    if a.header in tp.holds:
        print('static hold: ' + tp.holds[a.header])
        return
    edit = R.tu_edit(tp, header_of_row(plan))
    sys.path.insert(0, str(root / 'tools'))
    import layout_compile_identity as L
    import prove
    recipes, _ = L.recipes(root)
    fresh = not (root / a.header).exists()
    write_headers(root, plan, [a.header])
    try:
        print(prove.explain(root, a.tu, recipes[a.tu], plan.corpus.text(a.tu), edit, a.header))
    finally:
        if fresh:
            (root / a.header).unlink()


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', default=str(ROOT))
    sub = ap.add_subparsers(dest='cmd', required=True)
    t = sub.add_parser('table')
    t.add_argument('--out', required=True)
    d = sub.add_parser('dryrun')
    d.add_argument('--scope', nargs='*', default=[])
    d.add_argument('--out')
    d.add_argument('--list-edits', help='write the TUs the plan would edit (tu_identity --edit input)')
    p = sub.add_parser('apply')
    p.add_argument('--scope', nargs='+', required=True)
    p.add_argument('--out', required=True)
    p.add_argument('--workers', type=int, default=6)
    p.add_argument('--no-prove', action='store_true', help='accept every planned edit (experiments only)')
    p.add_argument('--dry-run', action='store_true', help='print the static per-folder counts and exit')
    p.add_argument('--decide-only', action='store_true',
                   help='byte-decide every planned edit but write no TU (headers are created only for the '
                        'compiles and removed again): a proven dry run')
    e = sub.add_parser('explain', help='why one (TU, header) include is held: compiler error or asm diff')
    e.add_argument('--tu', required=True)
    e.add_argument('--header', required=True)
    for parser in (t, d, p, e):
        parser.add_argument('--data', action='store_true',
                            help='plan/consolidate data externs (apply only after data naming; pilot now)')
    a = ap.parse_args(argv)
    if not 1 <= getattr(a, 'workers', 1) <= 6:
        ap.error('between 1 and 6 workers on this host')
    {'table': cmd_table, 'dryrun': cmd_dryrun, 'apply': cmd_apply, 'explain': cmd_explain}[a.cmd](a)


if __name__ == '__main__':
    main()
