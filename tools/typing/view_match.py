#!/usr/bin/env python3
"""Rank address-named view shapes against named records; never assert identity."""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
import csv
import json
from pathlib import Path
import re
import sqlite3

ADDRESS = re.compile(r'^(?:S_(?:func_)?[0-9A-Fa-f]{6,8}|Rec_|Row_)')
PLACEHOLDER = re.compile(r'(?:[0-9A-Fa-f]{8}|^S_|^Rec_|^Row_|View$|Scratch)')
SHARED = ('ActorRecord', 'TownObjectRecord', 'ObjectNodeHeader')


def sign(type_name):
    if '*' in type_name:
        return 'p'
    if type_name.startswith('unsigned') or type_name.startswith('u8') or type_name.startswith('u16') or type_name.startswith('u32'):
        return 'u'
    if type_name.startswith(('signed', 'short', 'int', 'long', 's8', 's16', 's32', 'char')):
        return 's'
    return '?'


def signature(members):
    """Leaf scalar members only; union alternatives are retained as alternatives."""
    return {(off, size, sign(ctype)) for off, size, ctype in members
            if size in (1, 2, 4) and not ctype.startswith(('struct ', 'union ', 'enum '))}


def rank(view, record):
    """Shape score, with size compatibility. Provenance is a separate gate."""
    vs, rs = view['signature'], record['signature']
    if not vs or not rs or record['size'] < max(off + width for off, width, _ in vs):
        return 0, 0
    common = vs & rs
    if not common:
        return 0, 0
    # A sparse view is expected; prioritize how much of its actual use agrees.
    score = len(common) / len(vs)
    return score, len(common)


def census(db):
    layouts = {}
    for name, file, size in db.execute('SELECT record,def_file,size FROM record_layout WHERE size IS NOT NULL'):
        if size <= 0:
            continue
        layouts[(name, file)] = dict(name=name, file=file, size=size, members=[])
    for name, file, off, size, ctype in db.execute('SELECT record,def_file,off,size,type FROM record_member'):
        item = layouts.get((name, file))
        if item:
            item['members'].append((off, size, ctype))
    for item in layouts.values():
        item['signature'] = signature(item['members'])
    views = [item for item in layouts.values() if ADDRESS.match(item['name'])]
    records = [item for item in layouts.values() if not item['name'].startswith('@')
               and not PLACEHOLDER.search(item['name'])
               and item['file'].startswith('include/') and len(item['signature']) >= 2]
    casts = Counter()
    for target, count in db.execute('SELECT target,COUNT(DISTINCT file||":"||start) FROM cast_site '
                                    'WHERE target IS NOT NULL GROUP BY target'):
        target = target.strip().rstrip('*').strip()
        casts[target] += count
    return views, records, casts


def kind_edges(path):
    """Object-kind creator/callback evidence attached to a view, not to a record."""
    if path is None:
        return {}
    data = json.loads(Path(path).read_text())
    edges = {}
    for kind in data.get('kinds', []):
        for qualified in kind.get('views', []):
            if ':' not in qualified:
                continue
            file, name = qualified.rsplit(':', 1)
            edge = {'kind': kind['kind'], 'creators': len(kind.get('creators', [])),
                    'callbacks': len(kind.get('callbacks', [])),
                    'allocators': ','.join(sorted({str(c.get('alloc', '')) for c in kind.get('creators', [])})),
                    'extent': kind.get('extent', 0)}
            key = (name, file)
            if key not in edges or edge['creators'] > edges[key]['creators']:
                edges[key] = edge
    return edges


def apply_retail_signatures(views, path):
    """Replace declared sign at observed view offsets with mapped load sign."""
    if path is None:
        return
    votes = defaultdict(lambda: defaultdict(set))
    counts = Counter()
    with Path(path).open() as stream:
        for row in csv.DictReader(stream, delimiter='\t'):
            if row.get('status') != 'mapped' or row.get('base_kind') != 'view' or row.get('direction') != 'r':
                continue
            typ = row.get('base_type', '')
            if ':' not in typ:
                continue
            file, name = typ.rsplit(':', 1)
            if not ADDRESS.match(name) or row.get('retail_sign') not in ('s', 'u'):
                continue
            key = (name, file)
            offset, width = int(row['offset']), int(row['declared_width'])
            votes[key][(offset, width)].add(row['retail_sign'])
            counts[key] += 1
    for view in views:
        key = (view['name'], view['file'])
        observed = votes.get(key)
        view['retail_sites'] = counts[key]
        if not observed:
            continue
        view['signature'] = {triple for triple in view['signature']
                             if (triple[0], triple[1]) not in observed}
        view['signature'].update((off, width, sign) for (off, width), signs in observed.items() for sign in signs)


def candidates(views, records, casts, edges=None, per_view=3):
    edges = edges or {}
    rows = []
    for view in views:
        if not view['signature']:
            continue
        matches = []
        for record in records:
            score, shared = rank(view, record)
            if shared >= 2 and score >= 0.5:
                matches.append((score, shared, record))
        edge = edges.get((view['name'], view['file']), {})
        tag = 'creator_site' if edge.get('creators') else 'callback_slot' if edge.get('callbacks') else 'shape_only'
        for score, shared, record in sorted(matches, key=lambda x: (-x[0], -x[1], x[2]['size'], x[2]['name']))[:per_view]:
            rows.append((view['name'], view['file'], view['size'], record['name'], record['file'], record['size'],
                         len(view['signature']), shared, f'{score:.3f}', casts[view['name']],
                         tag, edge.get('kind', ''), edge.get('creators', 0), edge.get('callbacks', 0),
                         edge.get('allocators', ''), edge.get('extent', 0), view.get('retail_sites', 0)))
    return sorted(rows, key=lambda r: (-r[9], -float(r[8]), r[0], r[3]))


def shared_shadow_rows(candidate_rows, access_rows, shared_fields):
    """Observed view loads at shared-record field offsets; identity stays unproven."""
    fields = defaultdict(list)
    for record, field, offset, width in shared_fields:
        fields[(record, int(offset), int(width))].append(field)
    candidate_index = defaultdict(list)
    for row in candidate_rows:
        if row[3] in SHARED:
            candidate_index[(row[0], row[1])].append(row)
    votes = defaultdict(Counter)
    members = defaultdict(set)
    for access in access_rows:
        if (access.get('status') != 'mapped' or access.get('base_kind') != 'view' or
                access.get('direction') != 'r' or access.get('opcode') not in ('lb', 'lbu', 'lh', 'lhu', 'lw')):
            continue
        qualified = access.get('base_type', '')
        if ':' not in qualified:
            continue
        file, view = qualified.rsplit(':', 1)
        for candidate in candidate_index.get((view, file), []):
            offset, width = int(access['offset']), int(access['declared_width'])
            for field in fields.get((candidate[3], offset, width), []):
                key = (view, file, candidate[3], field, offset, width, candidate[8],
                       candidate[9], candidate[10])
                votes[key][access['opcode']] += 1
                members[key].add(access.get('member_path', ''))
    result = []
    for key, opcodes in sorted(votes.items()):
        signed = opcodes['lb'] + opcodes['lh']
        unsigned = opcodes['lbu'] + opcodes['lhu']
        majority = 'signed' if signed > unsigned else 'unsigned' if unsigned > signed else 'tie_or_unknown'
        result.append((*key, ','.join(sorted(members[key])),
                       *(opcodes[op] for op in ('lb', 'lbu', 'lh', 'lhu', 'lw')),
                       majority, 'unproven'))
    return result


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[2])
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--kinds-json', type=Path, help='object_kinds.py report kinds.json; may be scoped')
    ap.add_argument('--access-sites', type=Path, help='access_census.py access_sites.tsv; sampled retail signs')
    args = ap.parse_args(argv)
    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=True)
    db = sqlite3.connect(args.root.resolve() / 'build/codemap.db')
    views, records, casts = census(db)
    apply_retail_signatures(views, args.access_sites)
    edges = kind_edges(args.kinds_json)
    rows = candidates(views, records, casts, edges)
    with (out / 'view_candidates.tsv').open('w', newline='') as stream:
        writer = csv.writer(stream, delimiter='\t', lineterminator='\n')
        writer.writerow(['view', 'view_file', 'view_size', 'candidate_record', 'record_file', 'record_size',
                         'view_signature', 'matching_members', 'shape_score', 'casts', 'evidence',
                         'object_kind', 'creator_sites', 'callbacks', 'allocators', 'observed_extent', 'retail_sites'])
        writer.writerows(rows)
    if args.access_sites:
        with args.access_sites.open() as stream:
            accesses = csv.DictReader(stream, delimiter='\t')
            shared_fields = db.execute('SELECT record,name,off,size FROM record_member WHERE depth=0 '
                                       'AND record IN (?,?,?)', SHARED)
            shadow_rows = shared_shadow_rows(rows, accesses, shared_fields)
        with (out / 'shared_view_shadow_candidates.tsv').open('w', newline='') as stream:
            writer = csv.writer(stream, delimiter='\t', lineterminator='\n')
            writer.writerow(['view', 'view_file', 'candidate_record', 'shared_field', 'offset', 'width',
                             'shape_score', 'casts', 'view_evidence', 'view_members',
                             'lb', 'lbu', 'lh', 'lhu', 'lw', 'majority', 'record_identity'])
            writer.writerows(shadow_rows)
    print(f'views={len(views)} records={len(records)} shape_candidates={len(rows)} '
          f'candidates_with_kind_evidence={sum(r[10] != "shape_only" for r in rows)}')


if __name__ == '__main__':
    main()
