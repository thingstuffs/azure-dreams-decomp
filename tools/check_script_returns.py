#!/usr/bin/env python3
"""Check decoded script return consumers against current registered C bodies.

Usage: python3 tools/check_script_returns.py --sites TABLE --services TABLE --holds TABLE
An explicit, reasoned hold is keyed by the full site AND issue identity. Newly void
callees, new sites and changed candidate sets fail. Polls consume a return even
without a subsequent v15 read. This checks a decoded census, not decoder coverage.
"""
from __future__ import annotations
import argparse
import csv
import hashlib
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from headers import cscan


def read_table(path):
    with path.open(newline='') as handle:
        return list(csv.DictReader(handle, delimiter='\t'))


def site_key(site):
    return ':'.join(site[k] for k in ('container', 'block', 'file_offset', 'op', 'callee'))


def consumes(site):
    if site['op'] in {'poll_service', 'poll_group_handler'}:
        return True
    return site['op'] in {'call_native', 'call_service', 'call_service_from_table'} and bool(site['reads'])


def return_kind(text, symbol):
    matches = [(item, decl) for item in cscan.scan(text).items if item.kind == 'def'
               for decl in item.decls if decl.name == symbol]
    if len(matches) != 1:
        return 'missing_definition'
    item, decl = matches[0]
    # cscan retains GNU attributes in specifiers. Their argument tokens must
    # not hide the return type or be mistaken for part of it.
    types = []
    tokens = iter(item.spec)
    for token in tokens:
        if token == '__attribute__':
            depth = 0
            for argument in tokens:
                depth += (argument == '(') - (argument == ')')
                if depth == 0:
                    break
        else:
            types.append(token)
    return 'void' if 'void' in types and decl.ptr == 0 else 'value'


def issue_key(site, reason, source='', symbol=''):
    identity = [site_key(site), reason, source, symbol, site['how'], site['resolved'], site['candidates']]
    return hashlib.sha256(json.dumps(identity, separators=(',', ':')).encode()).hexdigest()


def audit(root, sites, services, source_for):
    services = {row['callee']: row for row in services}
    cache = {}
    issues = []
    checked = 0
    for site in sites:
        if not consumes(site):
            continue
        source = symbol = ''
        reason = ''
        targets = []
        if site['op'] in {'call_service', 'poll_service', 'poll_group_handler'}:
            service = services.get(site['callee'])
            if service:
                targets.append((service['source'], service['function']))
            else:
                reason = 'unresolved_service'
        elif not site['resolved']:
            reason = 'ambiguous_callee' if site['how'] == 'ambiguous' else 'no_native_body'
        else:
            for candidate in site['resolved'].split('|'):
                parts = candidate.split(':')
                if len(parts) != 3:
                    raise ValueError('bad resolved identity: ' + site_key(site))
                name, _, row = parts
                owners = source_for(row)
                if isinstance(owners, str):
                    owners = [owners] if owners else []
                if not owners:
                    reason = 'missing_row'
                targets.extend((owner, name) for owner in owners)
        for target_source, target_symbol in sorted(set(targets)):
            path = root / target_source
            key = target_source, target_symbol
            if key not in cache:
                cache[key] = return_kind(path.read_text(), target_symbol) if path.is_file() else 'missing_definition'
            kind = cache[key]
            checked += 1
            # An unresolved placement cannot hide a confirmed void sibling.
            if kind == 'void':
                reason, source, symbol = kind, target_source, target_symbol
                break
            if kind != 'value' and not reason:
                reason, source, symbol = kind, target_source, target_symbol
        if reason:
            issues.append(dict(issue=issue_key(site, reason, source, symbol), site=site_key(site),
                               reason=reason, source=source, function=symbol))
    return issues, checked


def check_holds(issues, holds):
    held = {row['issue']: row for row in holds}
    if len(held) != len(holds) or any(not row.get('evidence', '').strip() for row in holds):
        raise ValueError('duplicate holds or missing hold evidence')
    active = {row['issue'] for row in issues}
    return [row for row in issues if row['reason'] == 'void' or row['issue'] not in held], sorted(set(held) - active)


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--root', type=Path, default=ROOT)
    ap.add_argument('--sites', type=Path, required=True)
    ap.add_argument('--services', type=Path, required=True)
    ap.add_argument('--holds', type=Path, required=True)
    ap.add_argument('--issues-out', type=Path)
    args = ap.parse_args()
    from source_layout import registry, row_relative
    reg = registry(args.root)
    sources = {rid: {row_relative(row, args.root)} for rid, row in reg.items()}
    # Complete module ownership supersedes retained member-fragment paths.
    from gate import overlay_module_gate as G
    for module in G.load_modules(args.root):
        for member in G.all_members(module):
            sources.setdefault(member['id'], set()).add(module['source'])
    source_for = lambda rid: sorted(sources.get(rid, ()))
    sites = read_table(args.sites)
    issues, checked = audit(args.root, sites, read_table(args.services), source_for)
    unknown, stale = check_holds(issues, read_table(args.holds))
    if args.issues_out:
        with args.issues_out.open('w') as handle:
            fields = ['issue', 'site', 'reason', 'source', 'function']
            writer = csv.DictWriter(handle, fields, delimiter='\t', lineterminator='\n')
            writer.writeheader(); writer.writerows(issues)
    print(json.dumps(dict(sites=len(sites), consumers=sum(map(consumes, sites)),
                          checked=checked, held=len(issues)-len(unknown),
                          untriaged=unknown, stale_holds=stale), sort_keys=True))
    return bool(unknown or stale)


if __name__ == '__main__':
    sys.exit(main())
