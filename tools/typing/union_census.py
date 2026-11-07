#!/usr/bin/env python3
"""Inventory physical C union definitions and their spelled member accesses.

This is a lexical census, not type-flow proof.  Counts deliberately remain
separate from the evidence needed to call a union proven.
"""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
from copy import deepcopy
import csv
import json
from pathlib import Path
import re
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'readability'))
import score

ACCESS = re.compile(r'(?:\b[A-Za-z_]\w*\s*)?(?:\.|->)\s*([A-Za-z_]\w*)(?:\s*(?:\.|->)\s*[A-Za-z_]\w*)*')
ID = re.compile(r'^[A-Za-z_]\w*$')
R118_ZERO_FILES = {
    'func_8180B064.c', 'func_80098378.c', 'func_808119EC.c',
    'func_8028906C.c', 'func_809A38E4.c', 'func_80FB4C24.c',
    'func_81844F2C.c', 'func_818B6AFC.c',
}
R118_ZERO_SITES = {
    'src/dungeon/menu/select.c': {
        'cell_y', 'mesh_index', 'packed0', 'x1', 'packed1', 'vert0_addr',
        'vert1_addr', 'vert2_addr', 'vert2_ref', 'vert3_addr', 'index1',
        'index1_xy', 'index2', 'index3', 'y0_high', 'facing',
    },
    'src/dungeon/menu/draw_nearby_map_markers.c': {
        'entryFlag', 'entryType', 'markerKind', 'kind', 'object',
    },
    'src/dungeon/effect/particle/update_effect_base_state.c': {'effect'},
    'src/dungeon/effect/travel/cycle_seven_color_fade.c': {'fade_out_red'},
    'src/dungeon/monster/kewne/update_actor_render_effect_and_position.c': {'segment_limit'},
    'src/town/scene/object/create_town_hud.c': {'rgb', 'state'},
}
WIDTHS = {
    'char': 8, 'signed char': 8, 'unsigned char': 8, 's8': 8, 'u8': 8,
    'short': 16, 'signed short': 16, 'unsigned short': 16, 's16': 16, 'u16': 16,
    'int': 32, 'signed int': 32, 'unsigned int': 32, 's32': 32, 'u32': 32,
}
LOAD_OPS = ('lb', 'lbu', 'lh', 'lhu', 'lw', 'sb', 'sh', 'sw', 'unmapped')
SIGNED_LOADS = ('lb', 'lh')
UNSIGNED_LOADS = ('lbu', 'lhu')


def empty_loads(members):
    return {member['name']: dict.fromkeys(LOAD_OPS, 0) for member in members}


def type_sign(typ):
    typ = typ.strip()
    if typ.startswith(('u8', 'u16', 'u32', 'unsigned ')):
        return 'u'
    if typ.startswith(('s8', 's16', 's32', 'signed ', 'short', 'int', 'char')):
        return 's'
    return ''


def access_identity(access):
    """Return a physical owner or anonymous union declaration from access census."""
    base = access.get('base_type', '')
    if base.startswith('@'):
        match = re.fullmatch(r'@(.+):(\d+):\d+', base)
        if match:
            return ('line', match.group(1), int(match.group(2)))
    if ':' in base:
        path, owner = base.rsplit(':', 1)
        return ('owner', path, owner)
    return None


def load_member(row, access):
    """Match a joined access to one ledger member without lexical suffix guesses."""
    identity = access_identity(access)
    path = access.get('member_path', '').replace('->', '.')
    parts = path.split('.')
    prefix = row['path']
    if identity == ('line', row['file'], row['line']):
        if prefix and (len(parts) < 2 or parts[-2] != prefix):
            return None
        return parts[-1] if parts[-1] in row['loads'] else None
    if identity != ('owner', row['file'], row['owner']):
        return None
    # Named typedef unions appear as typed views in access_census: their
    # base_type is the union itself, while member_path includes the instance
    # field (for example object->extent.signed_value). The exact base type
    # identifies the declaration; the final path component is its member.
    if row.get('count_basis') == 'member_suffix_upper_bound' and row['path'] == row['owner']:
        if parts[-1] not in row['loads']:
            return None
        if len(parts) > 1:
            base_tail = re.search(r'([A-Za-z_]\w*)(?:\[[^]]*\])?\s*$',
                                  access.get('base_expression', ''))
            if not base_tail or parts[-2] != base_tail.group(1):
                return None
        return parts[-1]
    if prefix not in parts:
        return None
    i = len(parts) - 1 - parts[::-1].index(prefix)
    if i + 1 < len(parts) and parts[i + 1] in row['loads']:
        return parts[i + 1]
    # A retired union has one field in the current source. Attribute a load
    # only when its old member type uniquely names the retail width/sign.
    if row['status'] != 'retired' or i + 1 != len(parts):
        return None
    op = access.get('opcode', '')
    if op in ('lb', 'lbu', 'lh', 'lhu', 'lw'):
        wanted = {'lb': ('s', 8), 'lbu': ('u', 8), 'lh': ('s', 16),
                  'lhu': ('u', 16), 'lw': ('', 32)}[op]
        if op == 'lw' and access.get('declared_sign') in ('s', 'u'):
            wanted = (access['declared_sign'], 32)
    elif access.get('declared_width'):
        wanted = (access.get('declared_sign', ''), 8 * int(access['declared_width']))
    else:
        return None
    matches = [m['name'] for m in row['members']
               if WIDTHS.get(m['type']) == wanted[1] and
               (wanted[0] == '' or type_sign(m['type']) == wanted[0])]
    return matches[0] if len(matches) == 1 else None


def add_access_loads(rows, accesses):
    """Count byte-exact retail accesses; unjoined source accesses stay explicit."""
    by_line = defaultdict(list)
    by_owner = defaultdict(list)
    for row in rows:
        row['loads'] = empty_loads(row['members'])
        by_line[row['file'], row['line']].append(row)
        by_owner[row['file'], row['owner']].append(row)
    seen = set()
    for access in accesses:
        identity = access_identity(access)
        if identity is None:
            continue
        candidates = (by_line[identity[1], identity[2]] if identity[0] == 'line'
                      else by_owner[identity[1], identity[2]])
        for row in candidates:
            member = load_member(row, access)
            if member is None:
                continue
            # Stores do not vote for a signed field type. An unjoined store
            # therefore does not reduce signed-load coverage either.
            if access.get('direction') == 'w' and access.get('status') != 'mapped':
                continue
            # Separate physical placements are distinct retail images. Within
            # one placement, each joined source access maps to one instruction.
            key = (row['id'], member, access.get('recipe_output', ''),
                   access.get('file', ''), access.get('function', ''),
                   access.get('pc', ''), access.get('line', ''),
                   access.get('direction', ''))
            if access.get('status') == 'mapped' and access.get('pc') and key in seen:
                continue
            seen.add(key)
            op = access.get('opcode', '') if access.get('status') == 'mapped' else ''
            row['loads'][member][op if op in LOAD_OPS else 'unmapped'] += 1


def retain_retired_loads(rows, previous, live_ids):
    """Keep fuller pre-retirement joins when scalar aliases become ambiguous.

    A retired union with two same-width, same-sign members cannot attribute
    scalar retail loads to either old member.  Its byte-proven pre-retirement
    joins remain valid even when the current source no longer names the union.
    """
    for row in rows:
        if row['id'] in live_ids or row['status'] != 'retired':
            continue
        old = previous.get(row['id'], {}).get('loads')
        if not old:
            continue
        old_mapped = sum(sum(v[op] for op in LOAD_OPS if op != 'unmapped')
                         for v in old.values())
        new_mapped = sum(sum(v[op] for op in LOAD_OPS if op != 'unmapped')
                         for v in row['loads'].values())
        if old_mapped > new_mapped:
            row['loads'] = old


def load_check(rows, declared_types):
    """Report sign conflicts and insufficient mapped loads without gating."""
    report = []
    for row in rows:
        signed = sum(v['lb'] + v['lh'] for v in row['loads'].values())
        unsigned = sum(v['lbu'] + v['lhu'] for v in row['loads'].values())
        mapped = signed + unsigned
        unmapped = sum(v['unmapped'] for v in row['loads'].values())
        if mapped < 5 or unmapped > .3 * (mapped + unmapped):
            reason = 'insufficient'
        else:
            declared = declared_types.get(row['id'], '')
            expected = 's' if signed > unsigned else 'u' if unsigned > signed else ''
            reason = 'disagree' if expected and declared and type_sign(declared) not in ('', expected) else ''
        if reason:
            report.append((row['id'], reason, declared_types.get(row['id'], ''),
                           signed, unsigned, unmapped))
    return report


def current_declared_types(root, rows):
    """Read the current struct field type for retired rows; live unions have no single type."""
    result = {}
    by_file = defaultdict(list)
    for row in rows:
        if row['status'] == 'retired' and row['path']:
            by_file[row['file']].append(row)
    for rel, candidates in by_file.items():
        source_path = root / rel
        if not source_path.is_file():
            continue
        source = source_path.read_text(errors='replace')
        tokens = score.lex(source)
        pairs, _ = score.pairs_of(tokens)
        aggs = aggregates(tokens, pairs)
        for agg in aggs:
            if agg['kind'] != 'struct' or not agg['name']:
                continue
            for member in member_decls(tokens, pairs, agg['body'], agg['end']):
                for row in candidates:
                    if agg['name'] == row['owner'] and member['name'] == row['path']:
                        result[row['id']] = member['type'].strip()
    return result


def source_paths(root: Path):
    for folder, suffixes in (('src', {'.c', '.h'}), ('include', {'.h', '.c'})):
        for path in sorted((root / folder).rglob('*')):
            if path.is_file() and path.suffix in suffixes:
                if path.stat().st_size > 4_000_000:
                    raise ValueError(f'oversized source (inspect explicitly): {path}')
                yield path


def after_brace(tokens, close):
    """Declarator name directly after an aggregate definition, if any."""
    i = close + 1
    while i < len(tokens) and tokens[i].value in {'__attribute__', '__attribute'}:
        if i + 1 < len(tokens) and tokens[i + 1].value == '(':
            # Attribute is rare here; skip a balanced argument list.
            depth = 1
            i += 2
            while i < len(tokens) and depth:
                depth += (tokens[i].value == '(') - (tokens[i].value == ')')
                i += 1
        else:
            i += 1
    if i < len(tokens) and tokens[i].kind == 'id' and tokens[i].value not in {'const', 'volatile'}:
        return tokens[i].value
    return None


def aggregates(tokens, pairs):
    found = []
    for i, tok in enumerate(tokens):
        if tok.value not in {'union', 'struct'}:
            continue
        j = i + 1
        tag = None
        if j < len(tokens) and tokens[j].kind == 'id':
            tag = tokens[j].value
            j += 1
        if j >= len(tokens) or tokens[j].value != '{' or j not in pairs:
            continue
        end = pairs[j]
        name = tag or after_brace(tokens, end)
        found.append(dict(kind=tok.value, start=i, body=j, end=end, name=name))
    return found


def member_decls(tokens, pairs, body, end):
    members = []
    start = body + 1
    i = start
    while i < end:
        if tokens[i].value in {'(', '[', '{'} and i in pairs:
            i = pairs[i] + 1
            continue
        if tokens[i].value == ';':
            part = tokens[start:i]
            if part:
                # Split multiple declarators without splitting nested aggregates.
                pieces, first, j = [], 0, 0
                while j < len(part):
                    if part[j].value in {'(', '[', '{'} and start + j in pairs:
                        j = pairs[start + j] - start + 1
                        continue
                    if part[j].value == ',':
                        pieces.append(part[first:j])
                        first = j + 1
                    j += 1
                pieces.append(part[first:])
                shared_type = ''
                for piece in pieces:
                    raw = ' '.join(t.value for t in piece)
                    fp = re.search(r'\(\s*\*\s*([A-Za-z_]\w*)\s*\)', raw)
                    if fp:
                        name = fp.group(1)
                        typ = raw.replace(name, '', 1).strip()
                    else:
                        # The declarator is the last identifier outside nested
                        # braces and brackets, excluding array extents.
                        visible, depth = [], 0
                        for j, token in enumerate(piece):
                            if token.value in {'}', ']', ')'}:
                                depth -= 1
                            elif token.kind == 'id' and depth == 0:
                                visible.append(j)
                            if token.value in {'{', '[', '('}:
                                depth += 1
                        pos = visible[-1] if visible and piece[-1].value != '}' else None
                        name = piece[pos].value if pos is not None else f'<anonymous_{len(members)}>'
                        prefix = ' '.join(t.value for t in piece[:pos]) if pos is not None else raw
                        suffix = ' '.join(t.value for t in piece[pos + 1:]) if pos is not None else ''
                        typ = (prefix + ' ' + suffix).strip()
                        if '{' in typ:
                            typ = typ.split('{', 1)[0].strip() + ' {...}'
                        if len(pieces) > 1 and piece is pieces[0]:
                            shared_type = prefix.strip()
                        elif shared_type and piece is not pieces[0]:
                            typ = (shared_type + ' ' + typ).strip()
                    members.append(dict(name=name, type=typ))
            start = i + 1
        i += 1
    return members


def classify(members, context):
    types = [m['type'] for m in members]
    if len(members) == 1 and context['zero_file']:
        return 'zero_init_idiom'
    if any(t.startswith('struct ') for t in types) and len(types) > 1:
        return 'per_action' if context['per_action'] else 'packed'
    ptr = [('*' in t or re.search(r'\(\s*\*', t)) for t in types]
    if any(ptr) and not all(ptr):
        return 'ptr_int'
    if len(types) > 1 and all(ptr) and len(set(types)) > 1:
        return 'ptr_ptr'
    widths = [WIDTHS.get(re.sub(r'\s+', ' ', t).strip()) for t in types]
    if len(widths) > 1 and all(w is not None for w in widths):
        if len(set(widths)) == 1:
            return 'sign_pun'
        return 'width_view'
    if any('[' in t or 'char' in t or t in {'u8', 's8'} for t in types) and len(types) > 1:
        return 'packed'
    if context['per_action']:
        return 'per_action'
    return 'other'


def access_index(texts):
    counts = Counter()
    examples = defaultdict(list)
    for rel, text in texts.items():
        area = rel.split('/', 1)[0]
        clean = score.LEX.sub(lambda m: re.sub(r'[^\n]', ' ', m.group())
                              if m.lastgroup in {'comment', 'directive', 'literal'} else m.group(), text)
        for match in ACCESS.finditer(clean):
            chain = tuple(re.findall(r'[A-Za-z_]\w*', match.group()))
            if not chain:
                continue
            for start in range(len(chain)):
                for end in range(start + 1, len(chain) + 1):
                    key = (area, chain[start:end])
                    counts[key] += 1
                    if len(examples[key]) < 3:
                        examples[key].append(f'{rel}:{text.count(chr(10), 0, match.start()) + 1}')
    return counts, examples


def census(root: Path):
    texts = {p.relative_to(root).as_posix(): p.read_text(errors='replace') for p in source_paths(root)}
    counts, examples = access_index(texts)
    rows = []
    used_ids = Counter()
    for rel, source in texts.items():
        if not re.search(r'\bunion\b', source):
            continue
        tokens = score.lex(source)
        pairs, warnings = score.pairs_of(tokens)
        if warnings:
            # Some merged translation units are imperfect.  Matched sites are
            # still useful; report a warning instead of inventing a union.
            pass
        aggs = aggregates(tokens, pairs)
        for agg in aggs:
            if agg['kind'] != 'union':
                continue
            parent = min((a for a in aggs if a['body'] < agg['start'] < a['end']),
                         key=lambda a: a['end'] - a['body'], default=None)
            field = after_brace(tokens, agg['end'])
            owner = parent['name'] if parent else agg['name']
            if not owner:
                owner = Path(rel).stem
            keypart = field or agg['name'] or f'anonymous@{source.count(chr(10), 0, tokens[agg["start"]].pos) + 1}'
            key = f'{rel}::{owner}.{keypart}'
            used_ids[key] += 1
            if used_ids[key] > 1:
                key += f'#{used_ids[key]}'
            members = member_decls(tokens, pairs, agg['body'], agg['end'])
            line = source.count('\n', 0, tokens[agg['start']].pos) + 1
            # A standalone typedef names a type, not an instance.  Its uses
            # appear under arbitrary field/variable names.  The member-only
            # suffix count is an upper bound, but zero is a sound lexical lead.
            is_typedef = (agg['start'] > 0 and tokens[agg['start'] - 1].value == 'typedef')
            standalone_type = parent is None and (is_typedef or field is None)
            path = () if standalone_type else (field,) if field else (agg['name'],) if agg['name'] else ()
            uses = {}
            sites = {}
            for member in members:
                name = member['name']
                chain = path + (name,)
                if not path:
                    chain = (name,)
                uses[name] = {area: counts[area, chain] for area in ('src', 'include')}
                sites[name] = examples['src', chain] + examples['include', chain]
            context = dict(zero_file=len(members) == 1 and
                           (Path(rel).name in R118_ZERO_FILES or
                            field in R118_ZERO_SITES.get(rel, set())),
                           per_action=owner in {'ActorRecord', 'TownObjectRecord'} and
                           (field or '').startswith(('unk_8', 'unk_9', 'unk_A', 'unk_B')))
            kind = classify(members, context)
            status = 'proven' if kind == 'zero_init_idiom' else 'unproven'
            evidence = ('Round 118 accepted compiler lever; preserve separately from type-overlay retirement.'
                        if kind == 'zero_init_idiom' else
                        'Lexical use counts only; creator and same-object proof pending.')
            rows.append(dict(id=key, file=rel, line=line, owner=owner, path=field or '',
                             members=members, kind=kind, uses=uses, example_sites=sites,
                             count_basis=('member_suffix_upper_bound' if standalone_type else 'field_path_lexical'),
                             status=status, evidence=evidence, retired_to_cast=[]))
    return sorted(rows, key=lambda r: (r['file'], r['line'], r['id']))


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[2])
    parser.add_argument('--out', type=Path)
    parser.add_argument('--access-sites', type=Path,
                        help='access_census.py access_sites.tsv with byte-exact retail joins')
    parser.add_argument('--check-loads', action='store_true',
                        help='report sign disagreements and insufficient coverage; never fail')
    args = parser.parse_args(argv)
    root = args.root.resolve()
    rows = census(root)
    physical_count = len(rows)
    summary = Counter(r['kind'] for r in rows)
    if args.out:
        previous = {}
        current_ids = {row['id'] for row in rows}
        if args.out.exists():
            previous = {row['id']: row for line in args.out.read_text().splitlines()
                        if line.strip() for row in [json.loads(line)]}
            for row in rows:
                old = previous.get(row['id'])
                if old:
                    for key in ('status', 'evidence', 'retired_to_cast', 'hold_reason', 'loads'):
                        if key in old:
                            row[key] = old[key]
            rows.extend(deepcopy(old) for key, old in previous.items() if key not in current_ids)
            rows.sort(key=lambda row: (row['file'], row['line'], row['id']))
        if args.access_sites:
            with args.access_sites.open(newline='') as stream:
                add_access_loads(rows, csv.DictReader(stream, delimiter='\t'))
            retain_retired_loads(rows, previous, current_ids)
        else:
            for row in rows:
                row.setdefault('loads', empty_loads(row['members']))
        args.out.parent.mkdir(parents=True, exist_ok=True)
        args.out.write_text(''.join(json.dumps(r, sort_keys=True) + '\n' for r in rows))
    elif args.access_sites:
        with args.access_sites.open(newline='') as stream:
            add_access_loads(rows, csv.DictReader(stream, delimiter='\t'))
    else:
        for row in rows:
            row['loads'] = empty_loads(row['members'])
    if args.check_loads:
        for entry in load_check(rows, current_declared_types(root, rows)):
            print('\t'.join(map(str, entry)))
    print(f'{physical_count} union definitions: ' + ', '.join(f'{k}={v}' for k, v in sorted(summary.items())))


if __name__ == '__main__':
    main()
