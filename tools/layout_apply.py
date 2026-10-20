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
import tempfile

from guarded_package import apply as apply_package, export, safe
from source_layout import ROOT, registry, row_relative, tu_moves, validate, inline_records, mapping as row_layout, flat_relative
from layout_dependencies import consumer_paths, include_parents
from gate.source_layout import _safe_path as safe_row_destination

MAX_SCAN = 4 * 1024 * 1024
INCLUDE = re.compile(r'(?m)^([ \t]*#[ \t]*include[ \t]*[<"])([^">\n]+)([>"])')
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


def resolve(root, origin, token, moves=None, *, angled=False):
    """Resolve a quoted include against the current or simultaneous final tree."""
    moves = moves or {}
    destinations = set(moves.values())
    search = (Path('include') / token, Path(token)) if angled else (Path(origin).parent / token, Path('include') / token, Path(token))
    for candidate in search:
        normalized = os.path.normpath(candidate)
        if normalized == '..' or normalized.startswith('../') or Path(normalized).is_absolute():
            continue
        if normalized in destinations or (normalized not in moves and (root / normalized).is_file()):
            return Path(normalized).as_posix()
    return None


def rebase_includes(root, text, origin, destination, moves):
    directives = re.findall(r'(?m)^[ \t]*#[ \t]*include\b[^\n]*', text)
    if any(INCLUDE.fullmatch(line.rstrip()) is None for line in directives):
        # Trailing comments are harmless, but macro and continued directives
        # require a preprocessor-aware plan instead of an unchecked move.
        for line in directives:
            if INCLUDE.match(line) is None:
                raise ValueError('unsupported include directive: ' + origin)
    def replace(hit):
        token = hit[2]
        resolved = resolve(root, origin, token, angled=hit[1].endswith('<'))
        final = moves.get(resolved, resolved)
        if resolved is None:
            spelling = token
        elif final == resolved and origin == destination:
            spelling = token
        elif final.startswith('include/'):
            spelling = final[len('include/'):]
        else:
            spelling = os.path.relpath(final, Path(destination).parent)
        actual = resolve(root, destination, spelling, moves, angled=hit[1].endswith('<'))
        expected_target = (root / final).resolve() if final else None
        actual_target = (root / actual).resolve() if actual else None
        if actual_target != expected_target:
            raise ValueError('include target changed: ' + destination + ': ' + spelling)
        return hit[1] + spelling + hit[3]
    return INCLUDE.sub(replace, text)


def inline_body(root, old, new, body, sites, moves):
    lines = body.splitlines(keepends=True)
    provenance = []
    by_line = {}
    # Never trust advisory TSV condition_depth: derive the nesting at each site.
    from layout_dependencies import conditional_depths
    depths = conditional_depths(body)
    for site in sites:
        if site.get('hold') or site.get('condition_depth') != '0':
            raise ValueError('inline site requires review: ' + old + ':' + site.get('include_line', '?'))
        line = int(site['include_line'])
        if line in by_line or not 1 <= line <= len(lines):
            raise ValueError('duplicate/out-of-range inline line: ' + old + ':' + str(line))
        if depths[line - 1] != 0:
            raise ValueError('conditional inline site: ' + old + ':' + str(line))
        token = site['include_token']
        expected = re.fullmatch(r'[ \t]*#[ \t]*include[ \t]+"([^"\n]+)"[ \t]*\n?', lines[line - 1])
        if expected is None or expected[1] != token:
            raise ValueError('inline include changed: ' + old + ':' + str(line))
        member = path(site['member_source'], 'src')
        # Decision 70: a module copy may supersede the row's own file (`row_source`); the row then
        # points at the inlined copy and its superseded file is retired in the same transaction.
        own = path(site['row_source'], 'src') if site.get('row_source') else member
        row = registry(root).get(site['member_id'])
        if row is None or row.get('source_row') or row_relative(row, root) != own:
            raise ValueError('inline row identity differs: ' + own)
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
                           'bytes': len(data),
                           'inlined_bytes': len(piece.encode('utf-8', 'surrogateescape')),
                           'original_includes': [m[2] for m in INCLUDE.finditer(data.decode('utf-8', 'surrogateescape'))]})
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
    if inline:
        # In-place inline: a TU already at its final path stays there (identity move). No TU-layout
        # history record is written for it below; every other check is the moved-TU path. Once all
        # of a TU's members are retired the inline has been applied and nothing is planned again.
        pending = {}
        for site in rows(inline):
            pending.setdefault(path(site['tu_current'], 'src'), []).append(site['member_source'])
        for old, members in pending.items():
            if any(safe(root, m).exists() for m in members):
                moves.setdefault(old, old)
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
        if src.is_file():
            active[old] = new
        elif not src.exists() and dst.is_file():
            already[old] = new
        else:
            raise ValueError('source missing: ' + old)
    # Classify the entire move set before checking destinations. A skipped
    # source cannot authorize an overwrite merely by appearing in the TSV.
    for old, new in active.items():
        if safe(root, new).exists() and new not in active:
            raise ValueError('destination exists: ' + new)
    changes = PlanChanges()
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
    inline_members = [site['member_source'] for group in sites.values() for site in group]
    superseded = {site['row_source']: old for old, group in sites.items() for site in group
                  if site.get('row_source') and site['row_source'] != site['member_source']}
    retired = inline_members + sorted(superseded)
    if len(retired) != len(set(retired)) or set(retired) & (set(active) | set(active.values())):
        raise ValueError('inline member has multiple physical owners')
    parents = include_parents(root) if inline_members else {}
    for member in retired:
        users = consumer_paths(root, {member}, transitive=False, parents=parents) - {member}
        if users - set(sites):
            raise ValueError('inline member has other consumers: ' + member)
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
    changes.update({member: None for member in retired})
    rewritten = []
    # External consumers of moved headers or source includes must follow the
    # same resolved identity. Paths under work/raw are intentionally excluded.
    for p in scan_files(root, ('src', 'include'), {'.c', '.h'}):
        rel = p.relative_to(root).as_posix()
        if rel in active or rel in retired or rel in nonhome:
            continue
        raw = p.read_bytes()
        body = raw.decode('utf-8', 'surrogateescape')
        if not INCLUDE.search(body):
            continue
        result = rebase_includes(root, body, rel, rel, active)
        if result != body:
            changes[rel] = result.encode('utf-8', 'surrogateescape')
            rewritten.append(rel)
    # Row layout is the current location; c_path in splits/rows is immutable
    # provenance and cannot be repurposed as a layout path.
    row_map = {}
    for rid, r in registry(root).items():
        if not r.get('source_row'):
            row_map.setdefault(row_relative(r, root), []).append(rid)
    relocated = {rid: new for old, new in active.items() for rid in row_map.get(old, [])}
    relocated.update({r['member_id']: r['tu_new'] for r in provenance})
    if relocated:
        p = root / 'ledger/layout.jsonl'
        entries = [json.loads(line) for line in p.read_text().splitlines() if line.strip()] if p.exists() else []
        old_ids = {record['id'] for record in entries}
        for record in entries:
            if record['id'] in relocated:
                record['path'] = relocated[record['id']]
        entries.extend({'id': rid, 'path': new} for rid, new in relocated.items() if rid not in old_ids)
        changes['ledger/layout.jsonl'] = ''.join(json.dumps(x, separators=(',', ':')) + '\n' for x in entries).encode()
    tu_history = {old: active.get(new, new) for old, new in tu_moves(root).items()}
    for old, new in active.items():
        if old.startswith('src/') and old not in row_map and old != new:
            tu_history[old] = new
    if tu_history:
        changes['ledger/tu_layout.jsonl'] = ''.join(json.dumps({'old': a, 'new': b}, separators=(',', ':')) + '\n'
                                                   for a, b in sorted(tu_history.items())).encode()
    prior_inline = inline_records(root)
    if any(r['tu_new'] in sites for r in prior_inline):
        raise ValueError('additional inlining into an inlined TU requires review')
    for r in prior_inline:
        origin = r['tu_new']
        destination = active.get(origin, origin)
        if destination not in changes or changes[destination] is None:
            continue
        raw = safe(root, origin).read_bytes()
        prefix = raw[:r['offset']].decode('utf-8', 'surrogateescape')
        piece = raw[r['offset']:r['offset'] + r['inlined_bytes']].decode('utf-8', 'surrogateescape')
        r['offset'] = len(rebase_includes(root, prefix, origin, destination, active).encode('utf-8', 'surrogateescape'))
        r['inlined_bytes'] = len(rebase_includes(root, piece, origin, destination, active).encode('utf-8', 'surrogateescape'))
        r['tu_new'] = destination
    if provenance or prior_inline:
        changes['ledger/layout_inline.jsonl'] = ''.join(json.dumps(x, separators=(',', ':')) + '\n'
                                                       for x in prior_inline + provenance).encode()
    # Rewrite only live path fields/tokens. Historical evidence is immutable.
    references = ('config/link', 'config/overlays', 'config/slus_modules.json',
                  'ledger/splits/overlay_modules.build.json', 'ledger/splits/slus.build.ninja',
                  *structured_evidence_paths(root))
    reference_moves = {**already, **active}
    reference_moves.update({r['member']: r['tu_new'] for r in provenance})
    reference_moves.update({row_file: active[old] for row_file, old in superseded.items()})
    for p in scan_files(root, references, {'.json', '.jsonl', '.tsv', '.yaml', '.ninja'}):
        rel = p.relative_to(root).as_posix()
        if rel in changes:
            continue
        data = p.read_bytes()
        updated = rewrite_references(data, p.suffix, reference_moves)
        if updated != data:
            changes[rel] = updated
    rewrite_byte_maps(root, changes, reference_moves)
    validate_planned_layout(root, row_map, relocated, tu_history, prior_inline + provenance, changes)
    for rel in list(changes):
        if (safe(root, rel).read_bytes() if safe(root, rel).is_file() else None) == changes[rel]:
            del changes[rel]
    certs, fingerprints = renewal_fingerprints(root, changes)
    report = {'moves': active, 'already_applied': already, 'skipped_nonhome': skipped,
              'reverse_map': {new: old for old, new in sorted(moves.items())},
              'inline_members': len(provenance), 'rows_relocated': len(relocated),
              'include_rewritten_consumers': sorted(rewritten),
              'certificates_requiring_renewal': certs,
              'renewal_input_fingerprints': fingerprints,
              'changed_paths': sorted(changes)}
    # Bind both payload and all lookup/metadata inputs, including unchanged
    # headers. A changed dependency invalidates the reviewed plan too.
    inputs = {}
    families = ('src', 'include', *references, 'link', 'ledger/modules',
                'ledger/rows.jsonl', 'ledger/layout.jsonl', 'ledger/tu_layout.jsonl',
                'ledger/layout_inline.jsonl', 'config/lint/relink_text.allow')
    for p in scan_files(root, families, {'.c', '.h', '.json', '.jsonl', '.tsv', '.yaml', '.ninja', '.allow'}):
        inputs[p.relative_to(root).as_posix()] = hashlib.sha256(p.read_bytes()).hexdigest()
    for rel in ('ledger/rows.jsonl', 'ledger/layout.jsonl', 'ledger/tu_layout.jsonl', 'ledger/layout_inline.jsonl'):
        p = root / rel
        inputs[rel] = hashlib.sha256(p.read_bytes()).hexdigest() if p.is_file() else None
    for rel in changes:
        inputs[rel] = hashlib.sha256(safe(root, rel).read_bytes()).hexdigest() if safe(root, rel).is_file() else None
    for rel in ('ledger/layout.jsonl', 'ledger/tu_layout.jsonl', 'ledger/layout_inline.jsonl'):
        inputs.setdefault(rel, None)
    for name in ('layout_apply.py', 'layout_dependencies.py', 'guarded_package.py', 'gate/source_layout.py',
                 'layout_compile_identity.py', 'slus_module_context.py', 'byte_map_format.py'):
        p = root / 'tools' / name
        if p.is_file():
            inputs['tools/' + name] = hashlib.sha256(p.read_bytes()).hexdigest()
    changes.inputs = inputs
    payload = {rel: hashlib.sha256(data).hexdigest() if data is not None else None
               for rel, data in sorted(changes.items())}
    bound = {'report': report, 'inputs': inputs, 'payload': payload,
             'tables': [hashlib.sha256(Path(p).read_bytes()).hexdigest() if p else None
                        for p in (tree, headers, inline)]}
    report['plan_sha256'] = hashlib.sha256(json.dumps(bound, sort_keys=True, separators=(',', ':')).encode()).hexdigest()
    return changes, report


def validate_planned_layout(root, row_map, relocated, wrappers, inlined, changes):
    """Reject invalid future row/wrapper bindings during --check, before writes."""
    reg = registry(root)
    owners, inline_owners = {}, {}
    for r in inlined:
        inline_owners.setdefault(r['tu_new'], set()).add(r['member_id'])
    for old, ids in row_map.items():
        for rid in ids:
            new = relocated.get(rid, old)
            safe_row_destination(new, reg[rid]['container'])
            owners.setdefault(new, set()).add(rid)
    for target, ids in owners.items():
        if len(ids) > 1 and ids != inline_owners.get(target):
            raise ValueError('planned rows collide: ' + target)
    aliases = {flat_relative(row) for row in reg.values()}
    for old, new in wrappers.items():
        if (old in aliases or new in aliases or old in owners or
                (new in owners and owners[new] != inline_owners.get(new))):
            raise ValueError('planned TU layout collides with row path: ' + new)
        if changes.get(new) is None and (new in changes or not (root / new).is_file()):
            raise ValueError('planned TU layout destination missing: ' + new)
    source_root = (root / 'src').resolve()
    for target in set(relocated.values()) | set(wrappers.values()):
        if not (root / target).resolve().is_relative_to(source_root):
            raise ValueError('planned source symlink escapes src: ' + target)


class PlanChanges(dict):
    """File payloads plus the read set used to guard the reviewed transaction."""


def structured_evidence_paths(root):
    """Only manifest-referenced structured evidence, never a prose/history sweep."""
    result = set()
    def walk(value):
        if isinstance(value, dict):
            for child in value.values():
                walk(child)
        elif isinstance(value, list):
            for child in value:
                walk(child)
        elif isinstance(value, str) and value.startswith('docs/evidence/') and Path(value).suffix in {'.json', '.jsonl'}:
            safe(root, value)
            result.add(value)
    for rel in ('config/overlays/modules.json', 'config/slus_modules.json'):
        p = root / rel
        if p.is_file():
            walk(json.loads(p.read_text()))
    return sorted(result)


def rewrite_references(data, suffix, moves):
    # Cheap token prefilter avoids parsing thousands of unrelated window YAMLs.
    tokens = re.findall(rb'(?:src|include)/[A-Za-z0-9_./-]+', data)
    if not any(token.decode() in moves for token in tokens):
        return data
    live = {'source', 'tu', 'path', 'headers', 'review_inputs', 'inputs', 'declaration'}
    history = {'history', 'evidence', 'provenance', 'c_path', 'fingerprint', 'previous'}
    def visit(value, field=None):
        if field in history:
            return value
        if isinstance(value, dict):
            return {k: visit(v, k) for k, v in value.items()}
        if isinstance(value, list):
            return [visit(v, field) for v in value]
        if isinstance(value, str) and field in live:
            return moves.get(value, value)
        return value
    text = data.decode('utf-8', 'surrogateescape')
    if suffix in {'.json', '.jsonl'}:
        if suffix == '.json':
            value = json.loads(text)
            updated = visit(value)
            return (json.dumps(updated, indent=2) + '\n').encode() if updated != value else data
        lines = []
        for line in text.splitlines(keepends=True):
            if not line.strip() or line.lstrip().startswith('#'):
                lines.append(line)
                continue
            value = json.loads(line)
            updated = visit(value)
            lines.append(json.dumps(updated, separators=(',', ':')) + '\n' if updated != value else line)
        return ''.join(lines).encode()
    if suffix == '.yaml':
        # Narrow scalar/list path fields, with no changes to comments/prose.
        import yaml
        value = yaml.safe_load(text)
        updated = visit(value)
        # Scalar marks preserve comments and all historical YAML formatting.
        edits = []
        def marked(node, field=None):
            if field in history:
                return
            if isinstance(node, yaml.MappingNode):
                for key, child in node.value:
                    marked(child, key.value)
            elif isinstance(node, yaml.SequenceNode):
                for child in node.value:
                    marked(child, field)
            elif field in live and node.value in moves:
                replacement = moves[node.value]
                if node.style == '"':
                    replacement = json.dumps(replacement)
                elif node.style == "'":
                    replacement = "'" + replacement.replace("'", "''") + "'"
                edits.append((node.start_mark.index, node.end_mark.index, replacement))
        marked(yaml.compose(text))
        for start, end, replacement in sorted(edits, reverse=True):
            text = text[:start] + replacement + text[end:]
        return text.encode()
    if suffix == '.tsv':
        lines = text.splitlines(keepends=True)
        fields = lines[0].rstrip('\r\n').split('\t') if lines else []
        out = lines[:1]
        for line in lines[1:]:
            body = line.rstrip('\r\n')
            cells = body.split('\t')
            cells = [moves.get(cell, cell) if index < len(fields) and fields[index] in live else cell
                     for index, cell in enumerate(cells)]
            out.append('\t'.join(cells) + line[len(body):])
        return ''.join(out).encode()
    if suffix == '.ninja':
        pattern = re.compile(r'(?<![^\s|:])(' + '|'.join(re.escape(p) for p in sorted(moves, key=len, reverse=True)) + r')(?=$|[\s|:])') if moves else None
        out = []
        for line in text.splitlines(keepends=True):
            body, marker, comment = line.partition('#')
            out.append((pattern.sub(lambda m: moves[m[0]], body) if pattern else body) + marker + comment)
        return ''.join(out).encode()
    return data


def rewrite_byte_maps(root, changes, moves):
    import byte_map_format as B
    groups = {}
    for p in sorted((root / 'link').glob('*/*.tsv')):
        groups.setdefault((p.parent.name, p.stem.split('.')[0]), []).append(p)
    for (container, name), paths in groups.items():
        doc = B.read_parts(paths, root)
        changed = False
        for entry in doc['entries']:
            if entry.get('tu') in moves:
                entry['tu'] = moves[entry['tu']]
                changed = True
        if not changed:
            continue
        blobs = B.encode(doc)
        for p in paths:
            changes[p.relative_to(root).as_posix()] = None
        for index, blob in enumerate(blobs):
            suffix = '' if len(blobs) == 1 else '.%03d' % index
            changes['link/' + container + '/' + name + suffix + '.tsv'] = blob


def renewal_fingerprints(root, changes):
    """Diff each certificate's live dependency projection across the transaction.

    These hashes identify renewals; only the production gate can certify bytes.
    Source/include dependencies are transitive, including unlisted consumers.
    """
    manifest = root / 'config/overlays/modules.json'
    if not manifest.is_file():
        return [], {}
    before = json.loads(manifest.read_text()).get('modules', [])
    after = json.loads(changes.get('config/overlays/modules.json', manifest.read_bytes())).get('modules', [])
    def fingerprint(module, staged):
        pending = [module['source'], *module.get('headers', []), *module.get('review_inputs', []),
                   *(d['declaration'] for d in module.get('imports', []) if 'declaration' in d)]
        inputs = {}
        while pending:
            rel = pending.pop()
            if rel in inputs:
                continue
            data = changes[rel] if staged and rel in changes else ((root / rel).read_bytes() if (root / rel).is_file() else None)
            inputs[rel] = hashlib.sha256(data).hexdigest() if data is not None else None
            if data is not None and Path(rel).suffix in {'.c', '.h'}:
                for hit in INCLUDE.finditer(data.decode('utf-8', 'surrogateescape')):
                    target = resolve_staged(root, rel, hit[2], changes if staged else {}, angled=hit[1].endswith('<'))
                    if target:
                        pending.append(target)
        return hashlib.sha256(json.dumps([module, inputs], sort_keys=True).encode()).hexdigest()
    module_diffs = {old['key']: (fingerprint(old, False), fingerprint(new, True))
                    for old, new in zip(before, after)}
    # Production certificates also bind neighbouring physical inputs in each
    # required window. Diff their layout/source projection, so an include-only
    # edit renews both its own module and certificates sharing that window.
    extents = []
    current = row_layout(root)
    reg = registry(root)
    for rid, row in reg.items():
        home = reg.get(row.get('source_row'), row)
        rel = current.get(home['id'], flat_relative(home))
        if rel in changes and row.get('foff') is not None and row.get('size'):
            extents.append((row['container'], row['foff'], row['foff'] + row['size'],
                            rel, hashlib.sha256((root / rel).read_bytes()).hexdigest(),
                            hashlib.sha256(changes[rel]).hexdigest() if changes[rel] is not None else None))
    for module in before:
        a, b = module_diffs[module['key']]
        if a != b:
            for member in module.get('members', []) + module.get('data_members', []):
                extents.append((module['container'], member['foff'], member['foff'] + member['size'],
                                'module/' + module['key'], a, b))
    fingerprints, window_cache = {}, {}
    def window_projection(name):
        if name in window_cache:
            return window_cache[name]
        p = root / name
        if not p.is_file():
            return ([], [])
        import yaml
        doc = yaml.load(p.read_text(), Loader=getattr(yaml, 'CSafeLoader', yaml.SafeLoader))
        sb = doc.get('standalone_build', {})
        w = sb.get('window')
        if not w:
            return ([], [])
        container = Path(sb.get('split_results', '')).parts
        container = container[1] if len(container) > 1 else ''
        container = 'dungeon' if container == 'dungeon_engine' else container
        num = lambda x: int(x, 0) if isinstance(x, str) else x
        lo, hi = num(w['file_start']), num(w['file_end'])
        entries = [e for e in extents if e[0] == container and lo < e[2] and e[1] < hi]
        value = ([[e[3], e[4]] for e in entries], [[e[3], e[5]] for e in entries])
        window_cache[name] = value
        return value
    for module in before:
        rel = 'ledger/modules/overlay_' + module['key'] + '.json'
        if not (root / rel).is_file():
            continue
        cert = json.loads((root / rel).read_text())
        names = cert.get('fingerprint', {}).get('required_windows', [])
        names = set(names) | {w['config'] for w in cert.get('windows', []) if 'config' in w}
        a, b = module_diffs[module['key']]
        wa, wb = {}, {}
        for name in sorted(names):
            wa[name], wb[name] = window_projection(name)
        a = hashlib.sha256(json.dumps([a, wa], sort_keys=True).encode()).hexdigest()
        b = hashlib.sha256(json.dumps([b, wb], sort_keys=True).encode()).hexdigest()
        if a != b:
            fingerprints[rel] = {'before': a, 'after': b}
    return sorted(fingerprints), fingerprints


def resolve_staged(root, origin, token, changes, *, angled=False):
    search = (Path('include') / token, Path(token)) if angled else (Path(origin).parent / token, Path('include') / token, Path(token))
    for p in search:
        rel = os.path.normpath(p)
        if Path(rel).is_absolute() or rel == '..' or rel.startswith('../'):
            continue
        if (rel in changes and changes[rel] is not None) or (rel not in changes and (root / rel).is_file()):
            return Path(rel).as_posix()
    return None


def apply_reviewed(root, changes, report, expected):
    if not expected or expected != report['plan_sha256']:
        raise ValueError('--apply requires matching reviewed --expect-plan-sha')
    root = Path(root).resolve()
    if not changes:
        return {'status': 'already-applied', 'files': 0}
    with tempfile.TemporaryDirectory(prefix='layout-package-', dir=root) as directory:
        package = Path(directory) / 'package'
        export(package, root, changes, {'kind': 'layout-apply', 'plan_sha256': expected,
                                      'reverse_map': report['reverse_map'],
                                      'protected_inputs': changes.inputs})
        return apply_package(package, root, live=True)


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('tree', type=Path)
    ap.add_argument('--root', type=Path, default=ROOT)
    ap.add_argument('--headers', type=Path)
    ap.add_argument('--inline', type=Path)
    mode = ap.add_mutually_exclusive_group(required=True)
    mode.add_argument('--check', action='store_true')
    mode.add_argument('--apply', action='store_true')
    ap.add_argument('--expect-plan-sha', help='plan_sha256 from the reviewed --check output')
    args = ap.parse_args()
    changes, report = plan(args.root, args.tree, headers=args.headers, inline=args.inline)
    if args.apply:
        report['transaction'] = apply_reviewed(args.root, changes, report, args.expect_plan_sha)
    else:
        report['transaction'] = {'status': 'check', 'files': len(changes)}
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
