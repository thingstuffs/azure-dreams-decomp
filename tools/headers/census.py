#!/usr/bin/env python3
"""Outcome census for the lexical local_externs debt (tools/lint/debt_check.py).

Every debt site is mapped to what the header plan does with it:

    planned_remove           the static plan removes it (an include replaces it; bytes still decide)
    proven_remove            ... and the byte decision accepted the include (with --verdicts)
    bytes_hold:<mechanism>   ... but the byte decision kept it (with --verdicts)
    keep:<reason>            the plan keeps it (function/data/TU hold reason; SDK class for no-C names)
    unmodelled:<shape>       the plan has no row for it (block-scope extern, unparsed declarator)

    python3 tools/headers/census.py --out DIR [--scope src/x ...] [--verdicts verdicts.jsonl] [--data]

Writes sites.tsv (one row per debt site), by_reason.tsv, by_folder.tsv and summary.json.
"""
from __future__ import annotations

import argparse
import bisect
import json
import sys
from collections import Counter, defaultdict
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent), str(HERE.parent / 'lint')]

import plan as P          # noqa: E402

ROOT = HERE.parent.parent


def debt_sites(root, files):
    """{path: [(line, char offset, in_function)]} for the debt checker's local_externs sites."""
    import debt_check as D
    c = D.c
    out = {}
    for rel in files:
        text = (Path(root) / rel).read_text()
        tokens = c.lex(text)
        pairs, _ = c.pairs_of(tokens)
        definitions = list(c.definitions(tokens, pairs))
        spans, _ = D.exemptions(text, tokens, pairs)
        excluded = set()
        for a, b in spans:
            excluded.update(range(a, b))
        bodies = sorted((tokens[body].pos, tokens[end].pos) for start, name, body, end, style in definitions)
        nl = [i for i, ch in enumerate(text) if ch == '\n']
        rows = []
        for i in D.declaration_sites(tokens, pairs, definitions):
            if i in excluded:
                continue
            pos = tokens[i].pos
            inside = any(a <= pos <= b for a, b in bodies)
            rows.append((bisect.bisect_right(nl, pos - 1) + 1, pos, inside))
        out[rel] = rows
    return out


def sdk_detail(plan):
    """(path, line, name) -> 'category/problem' for no-C function sites."""
    return {(r[0], r[1], r[2]): f'{r[3]}/{r[8] or r[7]}' for r in plan.sdk_census}


def site_outcome(r, tp, verdict, sdk):
    """Outcome label for one plan SiteRow inside TU plan tp."""
    if tp is not None and r in tp.remove:
        if verdict is None:
            return 'planned_remove'
        h = tp.plan.fn_for_def(r.definition).header
        if h in verdict.get('accept', []):
            return 'proven_remove'
        why = verdict.get('holds', {}).get(h) or ('baseline_error' if verdict.get('baseline_error') else
                                                   'not_decided')
        return 'bytes_hold:' + why.split(':')[0] + (':' + why.split(':')[1].strip()[:40]
                                                    if why.startswith(('bytes_changed', 'compile_error')) and ':' in why
                                                    else '')
    reason = r.reason or r.cls
    kind = getattr(r.site, 'kind', '') or 'function'
    if r.definition is None and r.cls == 'no_c_definition':
        reason = 'no_c_definition:' + sdk.get((r.site.path, r.site.line, r.site.name), 'unclassified')
    elif reason.startswith('tu_hold:'):
        parts = reason.split(':')
        reason = 'tu_hold:' + parts[1]
    elif reason.startswith('function_held:'):
        reason = 'function_held:' + reason.split(':')[1]
    elif r.cls == 'data_hold':
        reason = 'data_hold:' + (r.detail or '').split(':')[0]
    return f'keep:{kind}:{reason}'


def census(root, scope, data=True, verdicts=None, plan=None):
    plan = plan or P.build(root, scope=scope, include_data=data)
    for tp in plan.tus.values():
        tp.plan = plan
    sdk = sdk_detail(plan)
    files = sorted(plan.tus)
    sites = debt_sites(root, files)
    rows = []
    for rel in files:
        tp = plan.tus[rel]
        prs = plan.sites_by_path.get(rel, [])
        v = None if verdicts is None else verdicts.get(rel, {'accept': [], 'holds': {}})
        for line, pos, inside in sites.get(rel, []):
            hits = [r for r in prs if r.site.start <= pos < r.site.end]
            if not hits:
                dd = [x for x in plan.data_by_path.get(rel, []) if x.start <= pos < x.end]
                if dd and not inside:
                    rows.append((rel, line, ','.join(sorted({x.name for x in dd})), 'data',
                                 'keep:data:data_not_enabled' if not plan.include_data else
                                 'unmodelled:data_no_plan_row'))
                    continue
                rows.append((rel, line, '', 'block' if inside else 'file',
                             'unmodelled:' + ('block_scope_extern' if inside else 'no_plan_row')))
                continue
            outs = [site_outcome(r, tp, v, sdk) for r in hits]
            # one debt site per statement: a statement moves only when every declarator moves
            out = next((o for o in outs if not o.endswith('_remove')), outs[0])
            rows.append((rel, line, ','.join(sorted({r.site.name for r in hits})),
                         getattr(hits[0].site, 'kind', '') or 'function', out))
    return plan, rows


def folder_of(rel, depth):
    parts = rel.split('/')[:-1]
    return '/'.join(parts[:depth])


def write(out, rows, depth=3):
    out = Path(out)
    out.mkdir(parents=True, exist_ok=True)
    with open(out / 'sites.tsv', 'w') as fh:
        fh.write('path\tline\tnames\tkind\toutcome\n')
        for r in rows:
            fh.write('\t'.join(map(str, r)) + '\n')
    top = Counter(r[4].split(':')[0] for r in rows)
    reason = Counter(r[4] if not r[4].startswith('keep:') else ':'.join(r[4].split(':')[:4]) for r in rows)
    with open(out / 'by_reason.tsv', 'w') as fh:
        fh.write('outcome\tsites\n')
        for k, n in reason.most_common():
            fh.write(f'{k}\t{n}\n')
    per = defaultdict(Counter)
    for r in rows:
        per[folder_of(r[0], depth)][r[4].split(':')[0]] += 1
    cols = ['planned_remove', 'proven_remove', 'bytes_hold', 'keep', 'unmodelled']
    with open(out / 'by_folder.tsv', 'w') as fh:
        fh.write('folder\tsites\t' + '\t'.join(cols) + '\n')
        for f in sorted(per):
            c = per[f]
            fh.write(f'{f}\t{sum(c.values())}\t' + '\t'.join(str(c[k]) for k in cols) + '\n')
    summary = {'sites': len(rows), 'outcomes': dict(top.most_common()),
               'top_reasons': dict(reason.most_common(40))}
    (out / 'summary.json').write_text(json.dumps(summary, indent=1) + '\n')
    return summary


def load_verdicts(path):
    out = {}
    for line in Path(path).read_text().splitlines():
        if line.strip():
            v = json.loads(line)
            out[v['tu']] = v
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', default=str(ROOT))
    ap.add_argument('--scope', nargs='*', default=['src'])
    ap.add_argument('--out', required=True)
    ap.add_argument('--data', action='store_true', help='plan data externs too (headers.py --data)')
    ap.add_argument('--verdicts', help='verdicts.jsonl from headers.py apply --decide-only')
    ap.add_argument('--depth', type=int, default=3, help='folder depth for by_folder.tsv')
    a = ap.parse_args(argv)
    _, rows = census(Path(a.root).resolve(), a.scope, a.data,
                     load_verdicts(a.verdicts) if a.verdicts else None)
    print(json.dumps(write(a.out, rows, a.depth), indent=1))


if __name__ == '__main__':
    main()
