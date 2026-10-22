#!/usr/bin/env python3
"""Match legacy hold anchors to fresh, ordered byte-inference candidates.

Numeric group IDs are run-local. An unavailable-member diagnostic supplies
anchors, not the complete historical member list. Keep every compatible fresh
tuple and never turn a unique candidate into historical membership authority.
"""
from __future__ import annotations

import argparse
import csv
import hashlib
import json
from pathlib import Path
import re


PREFIX = 'Whole group is not own-home registered C: '
SITE = re.compile(r'(?:[a-z_]+/[A-Za-z0-9_.$-]+|unregistered@[0-9A-Fa-f]+)\Z')


def anchors(reason):
    """Read only the explicit unavailable-member clause, never later diagnostics."""
    if not reason.startswith(PREFIX):
        return []
    values = reason[len(PREFIX):].split(';', 1)[0].split(',')
    if not values or any(not SITE.fullmatch(v) for v in values):
        raise ValueError('malformed unavailable-member anchors')
    return values


def ordered_within(need, sites):
    """Keep order and multiplicity; a set containment test loses both."""
    index = 0
    for site in sites:
        if index < len(need) and site == need[index]:
            index += 1
    return index == len(need)


def tuple_key(container, sites):
    """Full digest of ordered registered identities, scoped to their container."""
    payload = json.dumps([container, list(sites)], separators=(',', ':'))
    return hashlib.sha256(payload.encode()).hexdigest()


def match(references, groups):
    out = []
    for ref in references:
        if ref.get('category') not in ('placed_or_unavailable_members', 'missing_reference_membership'):
            continue
        need = anchors(ref['reason'])
        found = [g for g in groups if need and ordered_within(need, g['member_rows'].split(';'))]
        state = ('no_reference_anchors' if not need else
                 'no_fresh_candidate' if not found else
                 'unique_fresh_candidate' if len(found) == 1 else 'ambiguous_fresh_candidates')
        for group in found or [None]:
            sites = group['member_rows'].split(';') if group else []
            out.append(dict(gid=ref['gid'], status=state, anchors=';'.join(need),
                            fresh_group=group['group_id'] if group else '',
                            tuple_sha256=tuple_key(group['container'], sites) if group else '',
                            level=group['level'] if group else '',
                            container=group['container'] if group else '',
                            member_rows=';'.join(sites), historical_membership='unavailable'))
    return out


def freeze(group, unit, blob):
    """Bind the full fresh tuple to exact bytes and the recorded load geometry."""
    start, end = (int(group[k], 16) for k in ('foff_first', 'foff_end'))
    summary = unit['summary']
    if summary['container'] != group['container'] or summary['image'] != group['image']:
        raise ValueError('inference unit does not match the group image')
    functions = [f for f in unit['functions'] if start <= f['foff'] < end]
    labels = [f['row'] or 'unregistered@%X' % f['foff'] for f in functions]
    if labels != group['member_rows'].split(';') or not functions or functions[-1]['end'] != end:
        raise ValueError('ordered group membership does not match the byte evidence')
    cursor, members = start, []
    for site, fn in zip(labels, functions):
        if fn['foff'] != cursor or fn['end'] <= cursor or fn['end'] > len(blob):
            raise ValueError('noncontiguous or out-of-range evidence span')
        members.append(dict(site=site, home=fn['home'], foff=cursor, end=fn['end'],
                            sha256=hashlib.sha256(blob[cursor:fn['end']]).hexdigest()))
        cursor = fn['end']
    payload = dict(container=group['container'], image=group['image'], unit=summary['unit'],
                   delta=summary['delta'], level=group['level'], evidence=group['evidence'], members=members)
    content_key = hashlib.sha256(json.dumps(payload, sort_keys=True, separators=(',', ':')).encode()).hexdigest()
    return dict(fresh_group=group['group_id'], tuple_sha256=tuple_key(group['container'], labels),
                content_sha256=content_key, historical_membership='unavailable', **payload)


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--references', type=Path, required=True)
    ap.add_argument('--groups', type=Path, required=True)
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[2])
    ap.add_argument('--evidence', type=Path, help='tu_evidence output, required with --snapshots')
    ap.add_argument('--snapshots', type=Path, help='freeze every matched fresh tuple; never infer the old tuple')
    args = ap.parse_args()
    def read(path):
        with path.open() as fh:
            return list(csv.DictReader(fh, delimiter='\t'))
    groups = read(args.groups)
    records = match(read(args.references), groups)
    if args.snapshots:
        if not args.evidence:
            ap.error('--snapshots requires --evidence')
        import tu_lib as T
        repo = T.Repo(args.root)
        selected = {r['fresh_group'] for r in records if r['fresh_group']}
        units = {}
        for group in groups:
            if group['group_id'] not in selected:
                continue
            image = group['image']
            names = T.MAIN_CHILDREN if image == 'main/main_bin' else [image]
            candidates = []
            for name in names:
                if name not in units:
                    path = args.evidence / 'units' / (name.replace('/', '__') + '.json')
                    units[name] = json.loads(path.read_text())
                try:
                    candidates.append(freeze(group, units[name], repo.blob(group['container'])))
                except ValueError:
                    continue
            if len(candidates) != 1:
                raise ValueError('no unique byte-bound inference unit: ' + group['group_id'])
            args.snapshots.mkdir(parents=True, exist_ok=True)
            (args.snapshots / (group['group_id'] + '.json')).write_text(json.dumps(candidates[0], indent=2) + '\n')
    fields = ['gid', 'status', 'anchors', 'fresh_group', 'tuple_sha256', 'level',
              'container', 'member_rows', 'historical_membership']
    with args.out.open('w') as fh:
        writer = csv.DictWriter(fh, fieldnames=fields, delimiter='\t')
        writer.writeheader()
        writer.writerows(records)
    print(json.dumps(dict(references=len({r['gid'] for r in records}), candidates=sum(bool(r['fresh_group']) for r in records))))


if __name__ == '__main__':
    main()
