#!/usr/bin/env python3
"""Read-only instruction checks for missing members of a shared TU cohort.

Extract relocation masks from supplied placement objects, after checking their
text against the registered home's retail bytes. Audit missing slots against
those fingerprints. Equality outside relocation fields is a necessary shape
screen, never a binding, ownership, admission or whole-object identity proof.
Nothing in this tool installs rows, cuts inferred groups or changes placements.
"""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
import csv
import hashlib
import json
from pathlib import Path
import sys

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent), str(HERE.parent / 'gate')]
import copy_place as CP
import linklist as L
import tu_cohort as C
import tu_lib as T

MASK_TYPES = {'R_MIPS_HI16', 'R_MIPS_LO16', 'R_MIPS_GPREL16', 'R_MIPS_26', 'R_MIPS_32'}


def sha(data):
    return hashlib.sha256(data).hexdigest()


def masked(data, relocs):
    """Refuse unknown, overlapping or malformed masks instead of erasing evidence."""
    offsets = set()
    for offset, kind in relocs:
        if (type(offset) is not int or offset < 0 or offset % 4 or offset + 4 > len(data)
                or offset in offsets or kind not in MASK_TYPES):
            raise ValueError('unsupported or malformed text relocation mask')
        offsets.add(offset)
    return CP._mask(data, [(off, kind, '') for off, kind in relocs])


def extract(home, row, obj, blob):
    """Record metadata only: no source authority or object payload is exported."""
    sections = CP._sections(obj)
    text = [v for k, v in sections.items() if k == '.text' or k.startswith('.text.')]
    if len(text) != 1 or len(text[0][0]) != row['size'] or text[0][2] != 'PROGBITS':
        raise ValueError('placement object must have exactly the complete home text extent')
    data, relocs, _ = text[0]
    masks = [(off, kind) for off, kind, _ in relocs]
    start = row['foff']
    retail = blob[start:start + row['size']]
    if len(retail) != row['size'] or masked(retail, masks) != masked(data, masks):
        raise ValueError('supplied object disagrees with home retail outside relocation fields')
    return dict(home=home, container=row['container'], foff=start, size=row['size'],
                recipe=row.get('cfg'), object_sha256=sha(obj.read_bytes()),
                home_sha256=sha(retail), masked_sha256=sha(masked(retail, masks)),
                relocations=masks, other_sections={k: len(v[0]) for k, v in sections.items()
                                                  if not (k == '.text' or k.startswith('.text.'))},
                authority='instruction shape only; original objects and all allocations still require proof')


def check_slot(shape, row, blob, foff, view=None):
    """Pure necessary-condition test with immutable-home and view-boundary guards."""
    if any(shape.get(k) != row.get(k) for k in ('container', 'foff', 'size')):
        raise ValueError('shape registry geometry changed')
    size = row['size']
    home = blob[row['foff']:row['foff'] + size]
    if len(home) != size or sha(home) != shape['home_sha256']:
        raise ValueError('shape home bytes changed')
    expected = masked(home, shape['relocations'])
    if sha(expected) != shape['masked_sha256']:
        raise ValueError('shape relocation fingerprint changed')
    if type(foff) is not int or foff < 0 or foff + size > len(blob):
        return dict(state='outside_container')
    if view is not None and not (view['foff'] <= foff and foff + size <= view['foff'] + view['size']):
        return dict(state='outside_view')
    actual = masked(blob[foff:foff + size], shape['relocations'])
    return dict(state='masked_text_equal' if expected == actual else 'text_conflict',
                expected_sha256=shape['masked_sha256'], actual_sha256=sha(actual),
                first_difference=next((i for i, (a, b) in enumerate(zip(expected, actual)) if a != b), None))


def audit(groups, shapes, rows, images, entries, regions, blob):
    """Return summaries and bounded-detail inputs; retain all unknowns as unknowns."""
    physical = defaultdict(list)
    for rid, row in rows.items():
        if isinstance(row.get('foff'), int) and row.get('row_kind') != 'data':
            physical[(L.family(row['container']), row['foff'])].append(rid)
    summaries, details = [], []
    for group in groups:
        geometry = C.plan(group['member_rows'].split(';'), images, entries, rows, regions)
        counts = Counter()
        records = []
        partials_with_conflicts = 0
        for cohort in geometry['cohorts']:
            if cohort['state'] != 'partial':
                continue
            checks = []
            for missing in cohort['missing']:
                home = missing['home']
                row = rows[home]
                view = images.get(cohort['image'])
                container = view['container'] if view else rows[geometry['sites'][0]]['container']
                item = dict(home=home, foff=missing['foff'], size=row['size'],
                            registered_rows=physical[(L.family(container), missing['foff'])])
                if home not in shapes:
                    item.update(state='no_object_shape')
                elif L.family(container) != L.family(row['container']):
                    item.update(state='cross_container_requires_separate_shape')
                else:
                    item.update(check_slot(shapes[home], row, blob(container), missing['foff'], view))
                if item['state'] == 'masked_text_equal':
                    item['same_home_rows'] = []
                    item['other_home_rows'] = []
                    for rid in item['registered_rows']:
                        candidate = rows[rid]
                        actual_home = C.ultimate_home(rid, rows)
                        entry = entries.get(rid)
                        record = dict(row=rid, home=actual_home, size=candidate['size'],
                                      recipe=candidate.get('cfg'), image=entry['image'] if entry else None,
                                      delta=entry['vma'] - entry['foff'] if entry else None)
                        item['same_home_rows' if actual_home == home else 'other_home_rows'].append(record)
                if item['state'] == 'outside_view':
                    item['enclosing_views'] = sorted(key for key, v in images.items()
                        if v['container'] == container and v.get('vma') is not None
                        and v['vma'] - v['foff'] == cohort['delta']
                        and v['foff'] <= item['foff'] and item['foff'] + item['size'] <= v['foff'] + v['size'])
                counts[item['state']] += 1
                checks.append(item)
            conflict = any(x['state'] == 'text_conflict' for x in checks)
            partials_with_conflicts += conflict
            records.append(dict(image=cohort['image'], foff=cohort['foff'], delta=cohort['delta'], checks=checks))
        summary = dict(group=group['group_id'], partial_cohorts=len(records),
                       partial_cohorts_with_text_conflict=partials_with_conflicts,
                       slots=sum(counts.values()), **{k: counts[k] for k in
                           ('text_conflict', 'masked_text_equal', 'outside_view', 'outside_container',
                            'no_object_shape', 'cross_container_requires_separate_shape')})
        summaries.append(summary)
        details.append(dict(**summary, member_rows=geometry['sites'], home_rows=geometry['homes'],
                            geometry_holds=Counter(h['reason'] for h in geometry['holds']),
                            cohorts=records, holds=[], authority='read-only necessary instruction checks; no installation proof'))
    return summaries, details


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--root', type=Path, default=HERE.parents[1])
    sub = ap.add_subparsers(dest='command', required=True)
    ex = sub.add_parser('extract', help='objects TSV has home and root-relative object columns')
    ex.add_argument('--objects', type=Path, required=True)
    ex.add_argument('--out', type=Path, required=True)
    ck = sub.add_parser('check')
    ck.add_argument('--groups', type=Path, required=True)
    ck.add_argument('--shapes', type=Path, required=True)
    ck.add_argument('--out', type=Path, required=True)
    ck.add_argument('--details', type=Path, required=True)
    args = ap.parse_args()
    root = args.root.resolve()
    repo = T.Repo(root)
    if args.command == 'extract':
        shapes = {}
        with args.objects.open() as fh:
            for record in csv.DictReader(fh, delimiter='\t'):
                path = Path(record['object'])
                if path.is_absolute() or '..' in path.parts:
                    raise ValueError('object path must be local to the root')
                home = record['home']
                if home in shapes or repo.rows[home].get('source_row'):
                    raise ValueError('one own-home object per shape')
                row = repo.rows[home]
                shapes[home] = extract(home, row, root / path, repo.blob(row['container']))
        args.out.write_text(json.dumps(shapes, indent=2) + '\n')
        print(json.dumps(dict(shapes=len(shapes))))
        return
    with args.groups.open() as fh:
        groups = list(csv.DictReader(fh, delimiter='\t'))
    shapes = json.loads(args.shapes.read_text())
    images, _, entries, _ = L.load(root)
    regions = {c: C.S.rowbase(root, c) for c in ('main', 'town', 'dungeon', 'ovmovie')}
    summaries, details = audit(groups, shapes, repo.rows, images, entries, regions, repo.blob)
    args.details.mkdir(parents=True, exist_ok=True)
    for detail in details:
        C.write_details(detail, args.details / (detail['group'] + '.json'))
    with args.out.open('w') as fh:
        fields = list(summaries[0]) if summaries else ['group']
        writer = csv.DictWriter(fh, fieldnames=fields, delimiter='\t')
        writer.writeheader()
        writer.writerows(summaries)
    print(json.dumps(dict(groups=len(summaries), slots=sum(r['slots'] for r in summaries))))


if __name__ == '__main__':
    main()
