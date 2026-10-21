#!/usr/bin/env python3
"""Firm lower-bound translation-unit map and ranked merge spans.

Reads the per-unit evidence written by tu_evidence.py and the committed ledger,
and writes:
  boundary_map.tsv  one row per proven span (J1 group), proven edge and unknown
                    text region of every analysis unit;
  spans_ranked.tsv  merge candidates deduplicated by their ordered home-row set
                    (town views and dungeon banks re-link the same homes), clean
                    spans first, then by member count;
  per_image.tsv     per unit: functions, current source files, files after all
                    clean / all span merges, TU lower bound;
  totals.json       headline counts.

A span is a proven part of one original TU.  complete_tu=yes only when both
edges are exact: the image text start/end next to fully classified non-code
bytes, or a B1/B2 edge between two adjacent functions.

usage: boundary_map.py --evidence DIR --out DIR [--root ROOT]
"""
import argparse
import json
import re
import sys
from collections import defaultdict
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import tu_lib as T  # noqa: E402

FLAGS = ('mixed_registered_cells', 'member_has_in_image_placement_copy', 'goto_or_volatile_body',
         'unregistered_or_twin', 'main_data_import', 'named_const_caveat',
         'existing_module_overlap', 'cross_image_partial', 'needs_module_placements', 'slus_partition',
         'member_has_jump_table', 'no_current_source', 'recipe_not_module_supported')
# recipes the overlay module gate builds (tools/gate/overlay_module_gate.module_recipe)
MODULE_RECIPES = ('2.7.2-cdk-G0', '2.7.2-G0', '2.7.2-cdk-G0 -O1')


class Ctx:
    def __init__(self, root):
        self.repo = T.Repo(root)
        self.src_cache = {}

    def path_of(self, fn):
        """Current source path of a function record (home row or containing row)."""
        repo = self.repo
        if fn['row'] and fn['row'].startswith('slus/'):
            return repo.layout.get(fn['row']) or repo.rows[fn['row']]['c_path']
        home = fn['home']
        if home:
            return repo.home_path(home)
        return None

    def body_flags(self, path):
        if path not in self.src_cache:
            p = self.repo.root / path if path else None
            text = p.read_text(errors='replace') if p and p.is_file() else ''
            text = re.sub(r'/\*.*?\*/', '', text, flags=re.S)
            self.src_cache[path] = bool(re.search(r'\bgoto\b|\bvolatile\b', text))
        return self.src_cache[path]


def edge_state(idx, fns, edges, unit_edge, side):
    """'exact', 'image', 'within:<a>-<b>' or 'unknown' for the edge left/right of idx."""
    n = len(fns)
    if side == 'left':
        if idx == 0 and unit_edge:
            return 'image', None
        best = None
        for e in edges:
            if e['right'] == idx and e['left'] == idx - 1:
                return 'exact', e
            if e['right'] <= idx and (best is None or e['right'] > best['right']):
                best = e
        return ('within:%d-%d' % (best['left'], best['right']), best) if best else ('unknown', None)
    if idx == n - 1 and unit_edge:
        return 'image', None
    best = None
    for e in edges:
        if e['left'] == idx and e['right'] == idx + 1:
            return 'exact', e
        if e['left'] >= idx and (best is None or e['left'] < best['left']):
            best = e
    return ('within:%d-%d' % (best['left'], best['right']), best) if best else ('unknown', None)


def member_flags(ctx, s, fns, k, unit_entries):
    """(member-level refusals, recipe) of function k in its unit."""
    repo = ctx.repo
    f = fns[k]
    flags = set()
    recipe = None
    r = None
    if f['row'] and f['row'].startswith('slus/'):
        r = repo.rows[f['row']]
    elif f['origin'] in ('row', 'region_row'):
        r = repo.rows.get(f['row'] or '')
    if r:
        home = repo.rows.get(f['home'] or '') or r
        recipe = (home.get('cfg'), home.get('row_asflags') or '')
        if home.get('source_row') or not home.get('exists', True):
            flags.add('unregistered_or_twin')
    elif not f['origin'].startswith('inside:'):
        flags.add('unregistered_or_twin')
    if f['home'] and len(set(unit_entries[f['home']])) > 1:
        flags.add('member_has_in_image_placement_copy')
    if s['container'] == 'main' and (f['rdata'] or f['data']):
        flags.add('main_data_import')
    p = ctx.path_of(f)
    if f['home'] and not (p and (repo.root / p).is_file()):
        flags.add('no_current_source')
    if p and ctx.body_flags(p):
        flags.add('goto_or_volatile_body')
    if f['home'] and (f['home'] in repo.module_of or f['home'] in repo.inlined):
        flags.add('existing_module_overlap')
    if p and s['container'] != 'slus' and f['home'] and set(repo.path_ids.get(p, [])) - {f['home']}:
        flags.add('existing_module_overlap')
    return flags, recipe


def evaluate(ctx, name, s, fns, edges, a, b, mflags, where, kind, gid, group):
    members = fns[a:b + 1]
    left, le = edge_state(a, fns, edges, s['start_edge'], 'left')
    right, re_ = edge_state(b, fns, edges, s['end_edge'], 'right')
    files = []
    for f in members:
        p = ctx.path_of(f) or '?'
        if p not in files:
            files.append(p)
    flags = set()
    for k in range(a, b + 1):
        flags |= mflags[k][0]
    recipes = {mflags[k][1] for k in range(a, b + 1) if mflags[k][1]}
    if len(recipes) > 1:
        flags.add('mixed_registered_cells')
    if s['container'] != 'slus' and any(r[0] not in MODULE_RECIPES or r[1] for r in recipes):
        flags.add('recipe_not_module_supported')
    if group['caveat']:
        flags.add('named_const_caveat')
    if s['container'] == 'slus':
        flags.add('slus_partition')
    homes = [f['home'] for f in members]
    ids = {h for h in homes if h}
    # files shared with functions outside this span (existing multi-function files)
    for p in files:
        if p != '?' and s['container'] != 'slus' and set(ctx.repo.path_ids.get(p, [])) - ids:
            flags.add('existing_module_overlap')
    # cross-image: every other image placing a member must place all, contiguous, in order
    partial, elsewhere = [], []
    if None not in homes:
        for other in sorted({u for h in ids for u, _ in where[h]} - {name}):
            pos = {}
            for h in homes:
                hits = [i for u, i in where[h] if u == other]
                if len(hits) == 1:
                    pos[h] = hits[0]
            seq = [pos.get(h) for h in homes]
            if None in seq or seq != list(range(seq[0], seq[0] + len(seq))):
                partial.append(other)
            else:
                elsewhere.append(other)
    if partial:
        flags.add('cross_image_partial')
    if elsewhere or any(f['row'] != f['home'] for f in members if f['row']):
        flags.add('needs_module_placements')
    ev = '%s J1[%s]' % (gid, ','.join(group['literals'][:6]) + ('+%d' % (len(group['literals']) - 6)
                                                              if len(group['literals']) > 6 else ''))
    for side, st, e in (('L', left, le), ('R', right, re_)):
        if e:
            ev += ' %s:%s@%s' % (side, e['kind'], e['at'])
    complete = kind == 'span' and left in ('exact', 'image') and right in ('exact', 'image')
    return dict(unit=name, image=s['image'], kind=kind, span_id='%s#%s' % (name, gid), first=a, last=b,
                first_row=fn_label(members[0]), last_row=fn_label(members[-1]),
                member_count=len(members), files=files, evidence=ev, left=left, right=right,
                complete_tu='yes' if complete else 'no', flags=sorted(flags),
                key=(kind,) + tuple(h or ('%s@%X' % (name, f['foff'])) for h, f in zip(homes, members)),
                partial_in=partial, placed_in=elsewhere, anchor=group['file_anchor'],
                vma_first='%08X' % members[0]['vma'], foff_first='%X' % members[0]['foff'],
                foff_end='%X' % members[-1]['end'], container=s['container'],
                recipe=sorted(recipes)[0][0] if len(recipes) == 1 else '')


def clean_field(x):
    return str(x).replace('\\', '\\\\').replace('\t', '\\t').replace('\n', '\\n').replace('\r', '\\r')


def fn_label(fn):
    return fn['row'] or ('unregistered@%X' % fn['foff'])


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=HERE.parents[1])
    ap.add_argument('--evidence', type=Path, required=True)
    ap.add_argument('--out', type=Path, required=True)
    args = ap.parse_args(argv)
    ctx = Ctx(args.root)
    repo = ctx.repo
    units = {}
    for p in sorted((args.evidence / 'units').glob('*.json')):
        d = json.loads(p.read_text())
        units[d['summary']['unit']] = d
    # home -> [(unit, index)] for the cross-image contiguity check
    where = defaultdict(list)
    for name, d in units.items():
        for f in d['functions']:
            if f['home'] and f['origin'] in ('row', 'region_row'):
                where[f['home']].append((name, f['i']))
    args.out.mkdir(parents=True, exist_ok=True)
    rows_out, spans, per_image = [], [], []
    all_paths = set()
    for name, d in sorted(units.items()):
        s = d['summary']
        fns = d['functions']
        edges = d['edges']
        unit_entries = defaultdict(list)
        for f in fns:
            if f['home']:
                unit_entries[f['home']].append(f['foff'])
        covered = [False] * len(fns)
        unit_spans = []
        jt_owners = {v['fn'] for v in d['jump_tables'].values()}
        mflags = [member_flags(ctx, s, fns, k, unit_entries) for k in range(len(fns))]
        for k in jt_owners:
            mflags[k][0].add('member_has_jump_table')
        for gi, g in enumerate(d['groups']):
            a, b = g['first'], g['last']
            for k in range(a, b + 1):
                covered[k] = True
            sp = evaluate(ctx, name, s, fns, edges, a, b, mflags, where, kind='span', gid=g['gid'], group=g)
            unit_spans.append(sp)
            spans.append(sp)
            # installable sub-runs: consecutive members without member-level refusals and
            # with one registered recipe, >= 2 members (each a proven part of one TU)
            runs, run = [], []
            for k in range(a, b + 1):
                if mflags[k][0]:
                    runs.append(run)
                    run = []
                elif run and mflags[k][1] != mflags[run[0]][1]:
                    runs.append(run)
                    run = [k]
                else:
                    run.append(k)
            runs.append(run)
            for run in runs:
                if len(run) >= 2 and (run[0], run[-1]) != (a, b):
                    sub = evaluate(ctx, name, s, fns, edges, run[0], run[-1], mflags, where, kind='subspan',
                                   gid='%s.%X' % (g['gid'], fns[run[0]]['foff']), group=g)
                    unit_spans.append(sub)
                    spans.append(sub)
        # proven edges
        for e in edges:
            exact = e['right'] == e['left'] + 1
            rows_out.append([name, 'edge:%s@%s' % (e['kind'], e['at']), 'edge', fn_label(fns[e['left']]),
                             fn_label(fns[e['right']]), str(e['right'] - e['left'] + 1), '',
                             '%s %s' % (e['kind'], e.get('text') or e.get('fill', '')),
                             'exact' if exact else 'interval', ''])
        # unknown regions: maximal runs of functions in no span
        k = 0
        while k < len(fns):
            if covered[k]:
                k += 1
                continue
            j = k
            while j + 1 < len(fns) and not covered[j + 1]:
                j += 1
            rows_out.append([name, 'unknown:%X' % fns[k]['foff'], 'unknown', fn_label(fns[k]), fn_label(fns[j]),
                             str(j - k + 1), '', '', 'n/a', ''])
            k = j + 1
        for sp in unit_spans:
            rows_out.append([name, sp['span_id'], sp['kind'], sp['first_row'], sp['last_row'], str(sp['member_count']),
                             ';'.join(sp['files']), sp['evidence'] + ' left=%s right=%s' % (sp['left'], sp['right']),
                             sp['complete_tu'], ','.join(sp['flags'])])
        # file counts
        paths = []
        for f in fns:
            p = ctx.path_of(f)
            if p:
                all_paths.add(p)
        for f in fns:
            p = ctx.path_of(f)
            if p:
                paths.append(p)
        current = len(set(paths))

        def after(selected):
            parent = {p: p for p in set(paths)}

            def find(x):
                while parent[x] != x:
                    parent[x] = parent[parent[x]]
                    x = parent[x]
                return x
            for sp in selected:
                fs = [p for p in sp['files'] if p in parent]
                for p in fs[1:]:
                    parent[find(p)] = find(fs[0])
            return len({find(p) for p in parent})
        whole = [sp for sp in unit_spans if sp['kind'] == 'span']
        clean = [sp for sp in unit_spans if not sp['flags']]
        stabs, last = 0, -1
        for e in sorted(edges, key=lambda e: e['right']):
            if e['left'] >= last:
                stabs += 1
                last = e['right']
        per_image.append(dict(unit=name, image=s['image'], functions=len(fns), current_files=current,
                              spans=len(whole), clean_spans_or_subspans=len(clean),
                              flagged_spans_or_subspans=len(unit_spans) - len(clean),
                              span_members=sum(sp['member_count'] for sp in whole),
                              files_after_clean=after(clean), files_after_all=after(whole),
                              tu_lower_bound=stabs + 1, complete_tus=sum(1 for sp in unit_spans if sp['complete_tu'] == 'yes'),
                              alphabetical=s['alphabetical'], file_anchors=s['file_anchors']))
    cols = ['image', 'span_id', 'kind', 'first_row', 'last_row', 'member_count', 'member_files', 'evidence',
            'complete_tu', 'refusal_flags']
    with open(args.out / 'boundary_map.tsv', 'w') as f:
        f.write('\t'.join(cols) + '\n')
        for r in sorted(rows_out, key=lambda r: (r[0], r[2] not in ('span', 'subspan'), r[1])):
            f.write('\t'.join(clean_field(x) for x in r) + '\n')
    # dedupe by ordered home set
    fam = defaultdict(list)
    for sp in spans:
        fam[sp['key']].append(sp)
    ranked = []
    for key, sps in fam.items():
        rep = sps[0]
        flags = sorted(set().union(*[set(s['flags']) for s in sps]))
        ranked.append(dict(rep=rep, occurrences=len(sps), units=[s['unit'] for s in sps], flags=flags,
                           complete=any(s['complete_tu'] == 'yes' for s in sps)))
    ranked.sort(key=lambda r: (bool(r['flags']), -r['rep']['member_count'], r['rep']['unit'], r['rep']['first']))
    rcols = ['rank', 'span_id', 'clean', 'member_count', 'member_files', 'file_reduction', 'complete_tu',
             'refusal_flags', 'occurrences', 'container', 'first_row', 'last_row', 'foff_first', 'foff_end',
             'vma_first', 'file_anchor', 'files', 'evidence', 'units']
    with open(args.out / 'spans_ranked.tsv', 'w') as f:
        f.write('\t'.join(rcols) + '\n')
        for i, r in enumerate(ranked, 1):
            sp = r['rep']
            files = [p for p in sp['files']]
            f.write('\t'.join(map(clean_field, [i, sp['span_id'], 'yes' if not r['flags'] else 'no', sp['member_count'],
                                        len(files), max(0, len(files) - 1), 'yes' if r['complete'] else 'no',
                                        ','.join(r['flags']), r['occurrences'], sp['container'], sp['first_row'],
                                        sp['last_row'], sp['foff_first'], sp['foff_end'], sp['vma_first'],
                                        sp['anchor'], ';'.join(files), sp['evidence'],
                                        ','.join(r['units'][:8]) + (' (+%d)' % (len(r['units']) - 8)
                                                                    if len(r['units']) > 8 else '')])) + '\n')
    pcols = list(per_image[0])
    with open(args.out / 'per_image.tsv', 'w') as f:
        f.write('\t'.join(pcols) + '\n')
        for r in per_image:
            f.write('\t'.join(str(r[c]) for c in pcols) + '\n')
    holds = defaultdict(int)
    for r in ranked:
        for fl in r['flags']:
            holds[fl] += 1
    clean = [r for r in ranked if not r['flags']]
    def unique_after(selected):
        parent = {p: p for p in all_paths}

        def find(x):
            while parent[x] != x:
                parent[x] = parent[parent[x]]
                x = parent[x]
            return x
        for r in selected:
            fs = [p for p in r['rep']['files'] if p in parent]
            for p in fs[1:]:
                parent[find(p)] = find(fs[0])
        return len({find(p) for p in parent})
    whole_ranked = [r for r in ranked if r['rep']['kind'] == 'span']
    totals = dict(
        source_files_in_one_link_images=len(all_paths),
        source_files_after_clean_merges=unique_after(clean),
        source_files_after_all_whole_span_merges=unique_after(whole_ranked),
        unique_whole_spans=len(whole_ranked), unique_subspans=len(ranked) - len(whole_ranked),
        units=len(units), span_occurrences=len(spans), unique_spans=len(ranked), clean_unique_spans=len(clean),
        flagged_unique_spans=len(ranked) - len(clean),
        clean_member_files=sum(len(r['rep']['files']) for r in clean),
        flagged_member_files=sum(len(r['rep']['files']) for r in ranked if r['flags']),
        clean_file_reduction=sum(max(0, len(r['rep']['files']) - 1) for r in clean),
        flagged_file_reduction=sum(max(0, len(r['rep']['files']) - 1) for r in ranked if r['flags']),
        complete_unique_spans=sum(1 for r in ranked if r['complete']),
        holds_by_reason=dict(sorted(holds.items())),
        images_with_spans=len({sp['unit'] for sp in spans}),
        alphabetical={k: sum(1 for p in per_image if p['alphabetical'] == k) for k in ('yes', 'no', 'n/a')},
    )
    (args.out / 'totals.json').write_text(json.dumps(totals, indent=1, sort_keys=True) + '\n')
    print(json.dumps(totals, indent=1, sort_keys=True))


if __name__ == '__main__':
    main()
