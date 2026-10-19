#!/usr/bin/env python3
"""Plan or apply a reviewed LL7 tree TSV as one guarded file transaction.

Accepted columns: current_path/proposed_path (tree or header plan) and
source_tu/proposed_tu (v5 move plan).  --check is read-only and emits the
complete reverse map.  --apply uses guarded_package's SHA-bound rollback.
Historical raw paths and row c_path lineage are intentionally never rewritten.
"""
from __future__ import annotations

import argparse
import csv
import hashlib
import json
import os
from pathlib import Path, PurePosixPath
import re
import shutil
import tempfile

from guarded_package import apply as apply_package, export, safe
from source_layout import ROOT, registry, row_relative, tu_moves, validate

MAX_SCAN = 4 * 1024 * 1024
INCLUDE = re.compile(r'(?m)^([ \t]*#[ \t]*include[ \t]+")([^"\n]+)(")')
PATH_MACROS = re.compile(r'\b__(?:FILE|BASE_FILE|LINE|INCLUDE_LEVEL)__\b')


def rows(path):
    with Path(path).open(newline='') as f:
        return list(csv.DictReader(f, delimiter='\t'))


def path(name, kind):
    p = PurePosixPath(name)
    if (not name or str(p) != name or p.is_absolute() or '..' in p.parts
            or len(p.parts) < (3 if kind == "src" else 2) or p.parts[0] != kind or '\\' in name
            or p.suffix not in ({'.c'} if kind == 'src' else {'.h'})):
        raise ValueError('unsafe ' + kind + ' path: ' + repr(name))
    return name


def table_moves(table, source, target, kind, *, disposition=None):
    result = {}
    for row in rows(table):
        if disposition and row.get('disposition') != disposition:
            continue
        old, new = row.get(source, ''), row.get(target, '')
        if not new or old == new:
            continue
        path(old, kind)
        path(new, kind)
        if old in result and result[old] != new:
            raise ValueError('conflicting destination for ' + old)
        result[old] = new
    return result


def scan_files(root, families, suffixes):
    """Only the named source/metadata families; never walk work or the root."""
    for family in families:
        base = root / family
        if not base.exists():
            continue
        if base.is_file():
            candidates = [base]
        else:
            candidates = (Path(folder) / name for folder, _, names in os.walk(base)
                          for name in names)
        for p in candidates:
            if p.suffix in suffixes and p.is_file() and not p.is_symlink() and p.stat().st_size <= MAX_SCAN:
                yield p


def resolve(root, origin, token):
    for candidate in (Path(origin).parent / token, Path('include') / token, Path(token)):
        normalized = os.path.normpath(candidate)
        if (normalized != '..' and not normalized.startswith('../')
                and (root / normalized).is_file()):
            return Path(normalized).as_posix()
    return None


def rebase_includes(root, text, origin, destination, moves):
    def replace(hit):
        token = hit[2]
        resolved = resolve(root, origin, token)
        if resolved is None:
            return hit[0]
        final = moves.get(resolved, resolved)
        if final == resolved and origin == destination:
            return hit[0]
        if final.startswith('include/'):
            spelling = final[len('include/'):]
        else:
            spelling = os.path.relpath(final, Path(destination).parent)
        return hit[1] + spelling + hit[3]
    return INCLUDE.sub(replace, text)


def inline_body(root, old, new, body, sites, moves):
    lines = body.splitlines(keepends=True)
    provenance = []
    by_line = {}
    for site in sites:
        if site.get('hold') or site.get('condition_depth') != '0':
            raise ValueError('inline site requires review: ' + old + ':' + site.get('include_line', '?'))
        line = int(site['include_line'])
        if line in by_line or not 1 <= line <= len(lines):
            raise ValueError('duplicate/out-of-range inline line: ' + old + ':' + str(line))
        token = site['include_token']
        expected = re.fullmatch(r'[ \t]*#[ \t]*include[ \t]+"([^"\n]+)"[ \t]*\n?', lines[line - 1])
        if expected is None or expected[1] != token:
            raise ValueError('inline include changed: ' + old + ':' + str(line))
        member = path(site['member_source'], 'src')
        if resolve(root, old, token) != member:
            raise ValueError('inline member identity differs: ' + member)
        data = safe(root, member).read_bytes()
        if PATH_MACROS.search(data.decode('utf-8', 'surrogateescape')):
            raise ValueError('path/line macro in inline member: ' + member)
        by_line[line] = (site, data)
    out = []
    for number, line in enumerate(lines, 1):
        if number not in by_line:
            out.append(rebase_includes(root, line, old, new, moves))
            continue
        site, data = by_line[number]
        member = site['member_source']
        piece = rebase_includes(root, data.decode('utf-8', 'surrogateescape'), member, new, moves)
        if piece and not piece.endswith('\n'):
            piece += '\n'
        start = sum(len(x.encode('utf-8', 'surrogateescape')) for x in out)
        out.append(piece)
        provenance.append({'tu_old': old, 'tu_new': new, 'member': member,
                           'member_id': site['member_id'], 'manifest_key': site['manifest_key'],
                           'order': int(site['member_order']), 'offset': start,
                           'source_sha256': hashlib.sha256(data).hexdigest(),
                           'bytes': len(data)})
    return ''.join(out), provenance


def plan(root, tree, *, headers=None, inline=None):
    root = Path(root).resolve()
    # Fail before modifying anything if B17's row graph is already invalid.
    validate(root)
    first = rows(tree)
    if not first:
        raise ValueError('empty tree')
    if {'current_path', 'proposed_path'} <= first[0].keys():
        moves = table_moves(tree, 'current_path', 'proposed_path', 'src')
    elif {'source_tu', 'proposed_tu'} <= first[0].keys():
        moves = table_moves(tree, 'source_tu', 'proposed_tu', 'src')
    else:
        raise ValueError('tree needs current_path/proposed_path or source_tu/proposed_tu')
    if headers:
        moves.update(table_moves(headers, 'current_path', 'proposed_path', 'include',
                                 disposition='move proposed'))
    if len(set(moves.values())) != len(moves):
        raise ValueError('two files target the same path')
    active, already, skipped = {}, {}, {}
    nonhome = set()
    allow = root / 'config/lint/relink_text.allow'
    if allow.is_file():
        for line in allow.read_text().splitlines():
            if line and not line.startswith('#'):
                name, kinds = line.split('\t', 1)
                if 'relink' in kinds.split(','):
                    nonhome.add(name)
    for row in registry(root).values():
        if row.get('source_row'):
            nonhome.add('src/' + row['container'] + '/' + Path(row['c_path']).name)
    for old, new in moves.items():
        src, dst = safe(root, old), safe(root, new)
        if old in nonhome or (src.is_file() and re.search(rb'(?m)^/\* Relink of matched', src.read_bytes())):
            skipped[old] = 'non-home relink or placement copy'
            continue
        if src.is_file() and (not dst.exists() or new in moves):
            active[old] = new
        elif not src.exists() and dst.is_file():
            already[old] = new
        elif src.is_file() and dst.exists():
            raise ValueError('destination exists: ' + new)
        else:
            raise ValueError('source missing: ' + old)
    changes = {}
    staged_destinations = {}
    provenance = []
    sites = {}
    if inline:
        for site in rows(inline):
            old = site['tu_current']
            if old in active:
                sites.setdefault(old, []).append(site)
        for old in sites:
            sites[old].sort(key=lambda r: int(r['member_order']))
    for old, new in active.items():
        raw = safe(root, old).read_bytes()
        body = raw.decode('utf-8', 'surrogateescape')
        if PATH_MACROS.search(body):
            raise ValueError('path/line macro in moved file: ' + old)
        if old in sites:
            result, evidence = inline_body(root, old, new, body, sites[old], active)
            provenance.extend(evidence)
        else:
            result = rebase_includes(root, body, old, new, active) if old.startswith(('src/', 'include/')) else body
        staged_destinations[new] = result.encode('utf-8', 'surrogateescape')
    changes.update({old: None for old in active if old not in staged_destinations})
    changes.update(staged_destinations)
    # External consumers of moved headers or source includes must follow the
    # same resolved identity. Paths under work/raw are intentionally excluded.
    for p in scan_files(root, ('src', 'include'), {'.c', '.h'}):
        rel = p.relative_to(root).as_posix()
        if rel in active:
            continue
        raw = p.read_bytes()
        body = raw.decode('utf-8', 'surrogateescape')
        if not INCLUDE.search(body):
            continue
        result = rebase_includes(root, body, rel, rel, active)
        if result != body:
            changes[rel] = result.encode('utf-8', 'surrogateescape')
    # Row layout is the current location; c_path in splits/rows is immutable
    # provenance and cannot be repurposed as a layout path.
    row_map = {row_relative(r, root): rid for rid, r in registry(root).items()
               if not r.get('source_row')}
    relocated = {row_map[old]: new for old, new in active.items() if old in row_map}
    if relocated:
        p = root / 'ledger/layout.jsonl'
        entries = [json.loads(line) for line in p.read_text().splitlines() if line.strip()] if p.exists() else []
        old_ids = {record['id'] for record in entries}
        for record in entries:
            if record['id'] in relocated:
                record['path'] = relocated[record['id']]
        entries.extend({'id': rid, 'path': new} for rid, new in relocated.items() if rid not in old_ids)
        changes['ledger/layout.jsonl'] = ''.join(json.dumps(x, separators=(',', ':')) + '\n' for x in entries).encode()
    tu_history = tu_moves(root)
    for old, new in active.items():
        if old.startswith('src/') and old not in row_map:
            tu_history[old] = new
    if tu_history:
        changes['ledger/tu_layout.jsonl'] = ''.join(json.dumps({'old': a, 'new': b}, separators=(',', ':')) + '\n'
                                                   for a, b in sorted(tu_history.items())).encode()
    if provenance:
        evidence = root / 'ledger/layout_inline.jsonl'
        prior = evidence.read_text() if evidence.exists() else ''
        changes['ledger/layout_inline.jsonl'] = (prior + ''.join(json.dumps(x, separators=(',', ':')) + '\n'
                                                             for x in provenance)).encode()
    # Physical manifests, link lists, and certificate evidence use literal
    # canonical paths. Do not replace c_path/raw lineage or source snippets.
    references = ('config/link', 'config/overlays', 'config/slus_modules.json', 'ledger/modules', 'docs/evidence',
                  'ledger/splits/overlay_modules.build.json', 'ledger/splits/slus.build.ninja')
    reference_pattern = re.compile(b'|'.join(re.escape(old.encode()) for old in sorted(active, key=len, reverse=True))) if active else None
    for p in scan_files(root, references, {'.json', '.jsonl', '.tsv', '.yaml', '.md', '.ninja'}):
        rel = p.relative_to(root).as_posix()
        if rel in changes:
            continue
        data = p.read_bytes()
        updated = reference_pattern.sub(lambda match: active[match[0].decode()].encode(), data) if reference_pattern else data
        if updated != data:
            changes[rel] = updated
    changes = {rel: data for rel, data in changes.items()
               if (safe(root, rel).read_bytes() if safe(root, rel).is_file() else None) != data}
    certs = {x for x in changes if x.startswith('ledger/modules/') and x.endswith('.json')}
    manifest = root / 'config/overlays/modules.json'
    if manifest.is_file():
        for module in json.loads(manifest.read_text()).get('modules', []):
            if module.get('source') in active or any(h in active for h in module.get('headers', [])):
                rel = 'ledger/modules/overlay_' + module['key'] + '.json'
                if (root / rel).is_file():
                    certs.add(rel)
    certs = sorted(certs)
    return changes, {'moves': active, 'already_applied': already, 'skipped_nonhome': skipped,
                     'reverse_map': {new: old for old, new in sorted(moves.items())},
                     'inline_members': len(provenance), 'rows_relocated': len(relocated),
                     'certificates_requiring_renewal': certs,
                     'changed_paths': sorted(changes)}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('tree', type=Path)
    ap.add_argument('--root', type=Path, default=ROOT)
    ap.add_argument('--headers', type=Path)
    ap.add_argument('--inline', type=Path)
    mode = ap.add_mutually_exclusive_group(required=True)
    mode.add_argument('--check', action='store_true')
    mode.add_argument('--apply', action='store_true')
    args = ap.parse_args()
    changes, report = plan(args.root, args.tree, headers=args.headers, inline=args.inline)
    if args.apply and changes:
        with tempfile.TemporaryDirectory(prefix='layout-package-', dir=args.root) as directory:
            package = Path(directory) / 'package'
            export(package, args.root, changes, {'kind': 'layout-apply', 'reverse_map': report['reverse_map']})
            report['transaction'] = apply_package(package, args.root, live=True)
    else:
        report['transaction'] = {'status': 'check' if args.check else 'already-applied', 'files': len(changes)}
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
