#!/usr/bin/env python3
"""Debt-matcher census, enriched with codemap and fresh MIPS Clang expression facts.

Run from the private repository root. Outputs describe the current source snapshot.
The cache is disposable; no source mutation is performed by this script.
"""
from __future__ import annotations

import argparse
from bisect import bisect_right
from collections import Counter, defaultdict
from concurrent.futures import ProcessPoolExecutor
import csv
import gzip
import hashlib
import json
import subprocess
from pathlib import Path
import re
import sqlite3
import sys

HERE = Path(__file__).resolve().parent
CATEGORIES = ('byte_cursor', 'generated_view', 'node_body', 'callback_param',
              'call_arg', 'int_pointer', 'sdk', 'redundant', 'union_pun', 'other')
GENERATED = re.compile(r'(?:\b|_)(?:S_(?:func_)?[0-9A-Fa-f]{6,8}\w*|\w*View|Rec_\w+|Row_\w+|R\d+_\w+|'
                       r'Func[0-9A-Fa-f]{8}\w*|\w*[0-9A-Fa-f]{8}(?:State|Args?|Data|Ctx|Work))\b')
SDK_TYPE = re.compile(r'\b(?:SVECTOR|VECTOR|MATRIX|CVECTOR|DVECTOR|RECT|SPRT(?:_8|_16)?|'
                      r'TILE(?:_1|_8|_16)?|POLY_[FG]T?[34]|LINE_[FG][234]|DR_[A-Z]+|'
                      r'P_TAG|TIM_IMAGE|Cdl\w+|DRAWENV|DISPENV|Gs\w+)\b')
SDK_CALL = re.compile(r'^(?:gte_|GTE_|RotTrans|RotAverage|NormalColor|LocalLight|LightColor|'
                      r'SetRotMatrix|SetTransMatrix|SetLightMatrix|SetColorMatrix|ApplyMatrix|MulMatrix|'
                      r'CompMatrix|PushMatrix|PopMatrix|LoadImage|StoreImage|MoveImage|DrawOTag|'
                      r'DrawPrim|ClearOTag|AddPrim|addPrim|setPoly|setSprt|setTile|setRGB|setXY|setUV|'
                      r'setClut|setTPage|SetDraw|SetDisp|PutDraw|PutDisp|Cd[A-Z]|Spu[A-Z]|VSync|DrawSync)')
NODE_TYPE = re.compile(r'\b(?:\w*Node|ObjectNodeHeader|Entity|SpriteOwner|ObjectHeader)\b')
BYTE_TYPE = re.compile(r'^(?:(?:const|volatile)\s+)*(?:u8|s8|char|unsigned char|signed char)\s*\*$')


def setup(root):
    for p in ('tools', 'tools/typing', 'tools/lint', 'tools/readability', 'tools/codemap'):
        sys.path.insert(0, str(Path(root) / p))


def canonical(t, typedefs, depth=0):
    """Expand aliases while preserving qualifiers and function signatures."""
    if depth > 20:
        return t
    def replace(m):
        value = m[0]
        return canonical(typedefs[value], typedefs, depth + 1) if value in typedefs else value
    # Do not expand a tag named identically to its typedef (typedef struct X X).
    parts = re.split(r'(\b(?:struct|union|enum)\s+\w+)', t or '')
    value = ''.join(p if re.match(r'^(?:struct|union|enum)\s+', p) else
                    re.sub(r'\b\w+\b', replace, p) for p in parts)
    value = re.sub(r'\bsigned int\b', 'int', value)
    value = re.sub(r'\bshort int\b', 'short', value)
    value = re.sub(r'\s+', ' ', value).strip()
    return re.sub(r'\s*([*(),\[\]])\s*', r'\1', value)


def lexical(root, rel):
    import score as S
    import debt_check as D
    text = (root / rel).read_text()
    tokens = S.lex(text)
    pairs, warnings = S.pairs_of(tokens)
    spans, errors = D.exemptions(text, tokens, pairs)
    if warnings or errors:
        raise ValueError((rel, warnings, errors))
    excluded = set()
    for a, b in spans:
        if tokens[a].value == 'do' and tokens[a + 1].value == '{' and a + 1 in pairs:
            close = pairs[a + 1]
            excluded.update(range(a, a + 2))
            excluded.update(range(close, b))
        else:
            excluded.update(range(a, b))
    definitions, occurrences = [], Counter()
    for a, n, body, b, style in S.definitions(tokens, pairs):
        name = tokens[n].value
        occurrences[name] += 1
        definitions.append((a, b, name, occurrences[name]))
    newlines = [m.start() for m in re.finditer('\n', text)]
    source_lines = text.splitlines()
    rows = []
    for a, b in S.cast_sites(tokens, pairs):
        if any(i in excluded for i in range(a, b + 1)):
            continue
        pos = tokens[a].pos
        name, occurrence = '<global>', 0
        for lo, hi, fn, occ in definitions:
            if lo <= a <= hi:
                name, occurrence = fn, occ
                break
        # A range from the AST replaces this conservative lexical fallback.
        end_tok = S.operand_end(tokens, pairs, b + 1)
        end = tokens[end_tok - 1].pos + len(tokens[end_tok - 1].value)
        line = bisect_right(newlines, pos) + 1
        rows.append(dict(file=rel, function=name, occurrence=occurrence, line=line,
                         column=pos - (newlines[line - 2] if line > 1 else -1), start=pos,
                         cast_end=tokens[b].pos + 1, lexical_end=end,
                         to_type=text[pos + 1:tokens[b].pos].strip(),
                         prefix=text[pos:tokens[b].pos + 1],
                         lexical_text=text[pos:end],
                         source_line=source_lines[line - 1].strip()))
    expected = sum(x['counts']['pointer_casts'] for x in D.analyze(rel, text)['scopes'].values())
    assert len(rows) == expected, (rel, len(rows), expected)
    return rows


def shape(node, depth=0):
    import cast_ast as A
    while node and node.get('kind') in ('ParenExpr', 'ImplicitCastExpr') and A.kids(node):
        node = A.kids(node)[0]
    if not node:
        return 'unknown'
    k = node.get('kind', '?')
    if depth >= 3:
        return k
    label = k + (':' + node['opcode'] if 'opcode' in node else '')
    children = A.kids(node)
    return label + ('(' + ','.join(shape(c, depth + 1) for c in children[:3]) + ')' if children else '')


def extract(job):
    root, tu, recipe, accepted, cache = job
    root = Path(root)
    setup(root)
    import cast_ast as A
    import field_census as C
    import cast_census as CC
    cache = Path(cache)
    if cache.is_file():
        return json.loads(gzip.decompress(cache.read_bytes()))
    try:
        unit, error = A.clang_unit(root, tu, recipe)
    except Exception as exc:
        unit, error = None, type(exc).__name__ + ':' + str(exc)[-250:]
    result = dict(tu=tu, error=error, rows=[], callbacks=[])
    if unit is not None:
        for d in unit.tree.get('inner', []):
            if d.get('kind') not in ('FunctionDecl', 'VarDecl'):
                continue
            file = d.get('_f') or tu
            if file not in accepted:
                continue
            text = unit.text(file)
            parents = {id(n): p for n, p in A.walk(d)}
            params = {n.get('id'): (i, n.get('name'), C.qtype(n)) for i, n in
                      enumerate(n for n in A.kids(d) if n.get('kind') == 'ParmVarDecl')}
            for n, parent in A.walk(d):
                kind = n.get('kind')
                if kind == 'DeclRefExpr' and n.get('referencedDecl', {}).get('kind') == 'FunctionDecl':
                    top = n
                    p = parent
                    while p and p.get('kind') in ('ParenExpr', 'ImplicitCastExpr'):
                        top, p = p, parents.get(id(p))
                    if not (p and p.get('kind') == 'CallExpr' and A.kids(p)[0] is top):
                        result['callbacks'].append(n['referencedDecl'].get('name'))
                if kind != 'CStyleCastExpr' or not CC.is_pointer(C.qtype(n)) or not A.kids(n):
                    continue
                operand = A.kids(n)[0]
                target, source = C.qtype(n), C.qtype(operand)
                top, holder = n, parent
                while holder and holder.get('kind') in ('ParenExpr', 'ImplicitCastExpr'):
                    top, holder = holder, parents.get(id(holder))
                context = holder.get('kind', '') if holder else ''
                callee, arg_index, param_type, dest = '', '', '', ''
                if context == 'CallExpr':
                    children = A.kids(holder)
                    if top in children[1:]:
                        arg_index = children.index(top) - 1
                        callee_node = A.strip_implicit(children[0])
                        callee = callee_node.get('referencedDecl', {}).get('name') or C.expr_text(callee_node) or ''
                        ctype = canonical(C.qtype(callee_node), unit.typedefs)
                        # The AST's post-conversion argument type is the actual context type.
                        param_type = C.qtype(top)
                        # For variadic/unprototyped calls an explicit void* cast may still carry ABI intent.
                        if '...' not in ctype and not re.search(r'\(\s*\)\s*$', ctype):
                            dest = param_type
                elif context == 'VarDecl':
                    dest = C.qtype(holder)
                elif context == 'BinaryOperator' and holder.get('opcode') == '=' and A.kids(holder)[1] is top:
                    dest = C.qtype(A.kids(holder)[0])
                elif context == 'ReturnStmt':
                    dest = C.qtype(d).split('(', 1)[0].strip()
                leaf, off, variable = CC.chain_leaf(unit, n, A, C)
                param = None
                if leaf and leaf.get('kind') == 'DeclRefExpr':
                    param = params.get(leaf.get('referencedDecl', {}).get('id'))
                # Address-chain context distinguishes byte arithmetic from an ordinary byte conversion.
                address_top, address_holder = CC.climb(parents, n, A, C)
                base, chain_off, variable = CC.chain_leaf(unit, address_top, A, C)
                arithmetic = any(x.get('kind') == 'BinaryOperator' and x.get('opcode') in ('+', '-')
                                 and CC.is_pointer(C.qtype(x)) for x, _ in A.walk(address_top))
                rng = A.node_range(n, text)
                starts = []
                if rng:
                    starts = [rng[0]]
                else:
                    loc = n.get('range', {}).get('begin', {})
                    for l in (loc, loc.get('spellingLoc', {}), loc.get('expansionLoc', {})):
                        if l.get('offset') is not None:
                            o = l['offset']
                            starts.append(o if text.isascii() else len(text.encode()[:o].decode(errors='replace')))
                if not starts:
                    continue
                cs = canonical(source, unit.typedefs)
                ct = canonical(target, unit.typedefs)
                cd = canonical(dest, unit.typedefs)
                same = cs == ct
                # Do not erase a conversion through an unrelated intermediate pointer type, qualifiers,
                # function-pointer ABI, or arithmetic scaling. C implicit rules apply only in value contexts.
                void_implicit = (bool(dest) and cd == ct and
                                 ((cs == 'void*' and ct.endswith('*') and '(*' not in ct) or
                                  (ct == 'void*' and cs.endswith('*') and '(*' not in cs)) and
                                 not any(q in cs or q in ct for q in ('const', 'volatile')))
                null_implicit = (n.get('castKind') == 'NullToPointer' and bool(dest) and cd.endswith('*')
                                 and cd == ct)
                immediate = A.strip_implicit(operand)
                immediate_rng = A.node_range(operand, text)
                r = dict(file=file, function=d.get('name', '<global>') if d.get('kind') == 'FunctionDecl' else '<global>',
                         starts=sorted(set(starts)), end=rng[1] if rng else None,
                         from_type=source, to_type=target, from_canonical=cs, to_canonical=ct,
                         cast_kind=n.get('castKind', ''), expression_shape=shape(operand),
                         context=context, callee=callee, arg_index=arg_index, param_type=param_type,
                         destination=dest, same_type=same, implicit=void_implicit or null_implicit,
                         arithmetic=arithmetic, chain_offset=chain_off, variable_offset=variable,
                         chain_base_type=C.qtype(base) if base else '',
                         param_index=param[0] if param else '', param_type_source=param[2] if param else '',
                         param_name=param[1] if param else '', macro=int(A.in_macro(n)),
                         operand_text=text[immediate_rng[0]:immediate_rng[1]] if immediate_rng else C.expr_text(immediate),
                         operand_kind=immediate.get('kind', '') if immediate else '',
                         tu=tu)
                result['rows'].append(r)
    cache.write_bytes(gzip.compress(json.dumps(result, separators=(',', ':')).encode(), 6))
    return result


def classify(row):
    f, t, ck = row.get('from_type', ''), row.get('to_type', ''), row.get('cast_kind', '')
    cs, ct = row.get('from_canonical', ''), row.get('to_canonical', '')
    generated = bool(GENERATED.search(f + ' ' + t + ' ' + row.get('chain_base_type', '')) or
                     'generated' in row.get('ast_sub', ''))
    sdk = bool(SDK_TYPE.search(f + ' ' + t) or SDK_CALL.search(row.get('callee', '')))
    node = (row.get('chain_offset') in (-32, 32) and row.get('arithmetic') and
            bool(NODE_TYPE.search(row.get('chain_base_type', ''))))
    byte = row.get('arithmetic') and (bool(BYTE_TYPE.match(f) or BYTE_TYPE.match(t)) or
                                      'u8 *' in row.get('cast_text', ''))
    callback = (row.get('is_callback') and row.get('param_index', '') != '' and
                canonical(row.get('param_type_source', ''), {}) in
                ('void*', 'int', 's32', 'u32', 'unsigned int'))
    call_arg = row.get('arg_index', '') != ''
    integral = ck in ('IntegralToPointer', 'NullToPointer')
    union = (not row.get('arithmetic') and cs.endswith('*') and ct.endswith('*') and cs != ct and
             cs != 'void*' and ct != 'void*' and not generated and
             not BYTE_TYPE.match(f) and
             row.get('context') in ('UnaryOperator', 'ArraySubscriptExpr', 'MemberExpr'))
    flags = dict(generated_view=generated, sdk=sdk, node_body=node, byte_cursor=byte,
                 callback_param=bool(callback), call_arg=call_arg, int_pointer=integral,
                 redundant=bool(row.get('same_type') or row.get('implicit')), union_pun=union)
    row['overlap_tags'] = ';'.join(k for k, yes in flags.items() if yes)
    if flags['redundant']:
        return 'redundant', 'same_type' if row.get('same_type') else 'implicit_value_conversion'
    if node:
        return 'node_body', 'typed_node_or_entity_plus_minus_0x20'
    if generated:
        return 'generated_view', 'per_function_or_view_type'
    if sdk:
        return 'sdk', 'sdk_type' if SDK_TYPE.search(f + ' ' + t) else 'sdk_call'
    if integral:
        return 'int_pointer', 'null_constant' if ck == 'NullToPointer' else (
            'constant_address' if row.get('operand_kind') == 'IntegerLiteral' else 'integer_value')
    if re.search(r'\(\*[^)]*\)\(', cs + ' ' + ct):
        return 'other', 'function_pointer'
    if callback:
        return 'callback_param', 'address_taken_function_untyped_param'
    if byte:
        return 'byte_cursor', 'variable_offset' if row.get('variable_offset') else 'constant_offset'
    if call_arg:
        return 'call_arg', 'prototype_argument_conversion'
    if union:
        return 'union_pun', 'storage_reinterpretation_candidate'
    if row.get('ast_status') == 'missing':
        return 'other', 'unresolved_lexical_site'
    if '(*' in ct or row.get('ast_sub') == 'function_pointer':
        return 'other', 'function_pointer'
    if row.get('context') in ('UnaryOperator', 'MemberExpr', 'ArraySubscriptExpr'):
        return 'other', 'direct_untyped_or_typed_memory_view'
    return 'other', 'value_or_nonbyte_conversion'


def write_tsv(path, fields, rows):
    with (gzip.open(path, 'wt', newline='') if str(path).endswith('.gz') else path.open('w', newline='')) as fh:
        writer = csv.DictWriter(fh, fields, delimiter='\t', lineterminator='\n', extrasaction='ignore')
        writer.writeheader()
        for row in rows:
            writer.writerow({k: (str(v).replace('\t', ' ').replace('\n', ' ') if v is not None else '')
                             for k, v in row.items()})


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--root', type=Path, default=Path('.'))
    ap.add_argument('--workers', type=int, default=4)
    ap.add_argument('--expected', type=int, help='optional independently measured debt count')
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--cache', type=Path, help='disposable AST cache, default: OUT/ast_cache')
    args = ap.parse_args()
    root = args.root.resolve()
    assert 1 <= args.workers <= 6
    setup(root)
    out = args.out.resolve()
    cache = args.cache.resolve() if args.cache else out / 'ast_cache'
    assert out.is_relative_to(root) and cache.is_relative_to(root), 'outputs must stay inside root'
    out.mkdir(parents=True, exist_ok=True)
    cache.mkdir(parents=True, exist_ok=True)
    (out / '.ignore').write_text('*\n')
    (cache / '.ignore').write_text('*\n')
    db = sqlite3.connect('file:%s?mode=ro' % (root / 'build/codemap.db'), uri=True)
    files = sorted(p.relative_to(root).as_posix() for p in (root / 'src').rglob('*.c'))
    rows = []
    for file in files:
        rows.extend(lexical(root, file))
    print('lexical rows:', len(rows), flush=True)
    if args.expected is not None:
        assert len(rows) == args.expected, (len(rows), args.expected)
    accepted = {r['file'] for r in rows}
    import layout_compile_identity as L
    physical, _ = L.recipes(root)
    tus = {tu for tu, file in db.execute('SELECT DISTINCT tu,file FROM cast_site') if file in accepted}
    covered = {f for (f,) in db.execute('SELECT DISTINCT file FROM cast_site')}
    # Also parse unregistered tables / physical streams missing from the map.
    tus.update(accepted - covered)
    # All inputs to MIPS AST extraction participate in the cache key.
    fingerprint = hashlib.sha256(Path(__file__).read_bytes())
    fingerprint.update(json.dumps(physical, sort_keys=True).encode())
    for dependency in ('tools/typing/cast_ast.py', 'tools/typing/field_census.py', 'tools/typing/cast_census.py', 'tools/layout_compile_identity.py'):
        fingerprint.update((root / dependency).read_bytes())
    # Source, header and recipe changes invalidate every cached AST fact.
    for path in sorted([*(root / 'src').rglob('*.c'), *(root / 'include').rglob('*.h'), *(root / 'config').rglob('*.json')]):
        fingerprint.update(path.relative_to(root).as_posix().encode())
        fingerprint.update(path.read_bytes())
    stamp = fingerprint.hexdigest()
    jobs = [(str(root), tu, physical.get(tu), accepted,
             str(cache / (hashlib.sha256((stamp + tu).encode()).hexdigest() + '.json.gz')))
            for tu in sorted(tus)]
    # Registered SLUS partition streams omit sibling functions from their canonical parent file.
    # The lexical ratchet counts those functions too, so also parse the complete parents.
    for tu in ('src/slus/code.c', 'src/slus/code2.c'):
        jobs.append((str(root), tu, None, accepted,
                     str(cache / (hashlib.sha256((stamp + 'raw:' + tu).encode()).hexdigest() + '.json.gz'))))
    ast, old_ast, callbacks, errors = defaultdict(list), defaultdict(list), set(), []
    for (raw,) in db.execute('SELECT row FROM cast_site ORDER BY tu'):
        r = json.loads(raw)
        starts = r.get('starts', []) if r.get('macro') else [r['start']]
        for start in starts:
            old_ast[(r['file'], start)].append(r)
    print('enrichment TUs:', len(jobs), flush=True)
    with ProcessPoolExecutor(max_workers=min(args.workers, 6)) as pool:
        for i, res in enumerate(pool.map(extract, jobs, chunksize=2), 1):
            callbacks.update(res['callbacks'])
            if res['error']:
                errors.append(dict(tu=res['tu'], error=res['error']))
            for r in res['rows']:
                for start in r['starts']:
                    ast[(r['file'], start)].append(r)
            if i % 250 == 0:
                print('enriched:', i, '/', len(jobs), flush=True)
    source_cache, source_hashes = {}, {}
    parameters = {}
    for (blob,) in db.execute('SELECT blob FROM flow_tu'):
        flow = json.loads(gzip.decompress(blob))
        for fn in flow['functions']:
            file = fn['file']
            if file.startswith(str(root) + '/'):
                file = file[len(str(root)) + 1:]
            parameters[(file, fn['name'])] = fn['params']
        for edge in flow['edges']:
            source = edge.get('src') or ''
            if source.startswith('FN:'):
                callbacks.add(source[3:].split('@', 1)[0])
    for row in rows:
        key = row['file'], row['start']
        candidates = ast.get(key, [])
        # Macro spellings can share their expansion offset: prefer a matching cast type and function.
        chosen = sorted(candidates, key=lambda r: (r['to_type'].replace(' ', '') != row['to_type'].replace(' ', ''),
                                                   r['function'] != row['function'], r['macro'], r['tu']))
        existing = old_ast.get(key, [])
        if existing:
            row['ast_cls'] = existing[0].get('cls', '')
            row['ast_sub'] = existing[0].get('sub', '')
            row['base_decl'] = existing[0].get('base_decl', '')
        if chosen:
            facts = chosen[0]
            keep = {'file', 'function', 'start', 'to_type'}
            row.update({k: v for k, v in facts.items() if k not in keep})
            row['ast_status'] = 'macro' if facts['macro'] else 'matched'
            row['ast_variants'] = len({(r['from_type'], r['to_type']) for r in candidates})
            end = facts.get('end') or row['lexical_end']
            # The existing codemap classifier resolves param bases through implicit lvalue conversions.
            base_decl = row.get('base_decl', '')
            params = parameters.get((row['file'], row['function']), [])
            if base_decl.startswith('param:'):
                index = int(base_decl.split(':')[1])
                if index < len(params):
                    row.update(param_index=index, param_name=params[index].get('name', ''),
                               param_type_source=params[index]['type'])
            # Pointer-only value chains already accepted by a void* destination are removable too.
            cs, ct = row['from_canonical'], row['to_canonical']
            cd = canonical(row.get('destination', ''), {'s32': 'int', 'u32': 'unsigned int',
                                                       'u8': 'unsigned char', 's8': 'signed char'})
            if cd and cs.endswith('*') and ct.endswith('*') and not any(q in cs or q in ct for q in ('const', 'volatile')) and '(*' not in cs + ct:
                if cd == cs or (cd == 'void*' and cs.endswith('*') and ct.endswith('*')):
                    row['implicit'] = True
        else:
            row['ast_status'] = 'missing'
            row['from_type'] = '<unresolved>'
            row['expression_shape'] = 'lexical_only'
            end = row['lexical_end']
            # GNU typeof omits this unevaluated expression from Clang's JSON. Its adjacent declaration
            # proves the source type, independently of the absent AST expression.
            if (row['file'].endswith('/update_motion_and_brightness.c') and
                    row['lexical_text'] == '(ObjectPosition *)motion' and
                    'ObjectPosition *motion = motion_arg;' in (root / row['file']).read_text()):
                row.update(from_type='ObjectPosition *', from_canonical='ObjectPosition*',
                           to_canonical='ObjectPosition*', same_type=True,
                           ast_status='lexical_typeof_declaration', expression_shape='DeclRefExpr',
                           context='typeof_unevaluated')
        if row['file'] not in source_cache:
            source_cache[row['file']] = (root / row['file']).read_text()
            source_hashes[row['file']] = hashlib.sha256(source_cache[row['file']].encode()).hexdigest()
        text = source_cache[row['file']]
        row['cast_text'] = text[row['start']:end]
        row['is_callback'] = row['function'] in callbacks
        row['category'], row['reason'] = classify(row)
        parts = Path(row['file']).parts
        row['subsystem'] = parts[1]
        row['folder'] = '/'.join(parts[:3]) if len(parts) > 3 else '/'.join(parts[:2])
        row['source_sha256'] = source_hashes[row['file']]
        row['site_id'] = row['file'] + ':' + str(row['start'])
    fields = ['site_id', 'file', 'function', 'occurrence', 'line', 'column', 'start', 'cast_end', 'cast_text',
              'from_type', 'to_type', 'from_canonical', 'to_canonical', 'expression_shape', 'category', 'reason',
              'subsystem', 'folder', 'context', 'callee', 'arg_index', 'param_type', 'param_index', 'destination',
              'cast_kind', 'operand_kind', 'operand_text', 'end',
              'param_type_source', 'chain_base_type', 'chain_offset', 'variable_offset', 'overlap_tags',
              'ast_status', 'ast_variants', 'ast_cls', 'ast_sub', 'base_decl', 'source_line', 'source_sha256']
    write_tsv(out / 'census.tsv.gz', fields, rows)
    aggregate = Counter((r['category'], r['subsystem'], r['folder']) for r in rows)
    write_tsv(out / 'summary.tsv', ['category', 'subsystem', 'folder', 'casts'],
              [dict(category=k[0], subsystem=k[1], folder=k[2], casts=n) for k, n in sorted(aggregate.items())])
    by_category = Counter(r['category'] for r in rows)
    top_fn, top_pair = [], []
    samples = []
    for category in CATEGORIES:
        subset = [r for r in rows if r['category'] == category]
        counts = Counter((r['file'], r['function']) for r in subset)
        for rank, ((file, function), n) in enumerate(counts.most_common(30), 1):
            top_fn.append(dict(category=category, rank=rank, file=file, function=function, casts=n))
        counts = Counter((r['from_type'], r['to_type']) for r in subset)
        for rank, ((from_type, to_type), n) in enumerate(counts.most_common(30), 1):
            top_pair.append(dict(category=category, rank=rank, from_type=from_type, to_type=to_type, casts=n))
        # Reproducible hash sample: avoids hand-picking the easiest functions.
        selected = sorted(subset, key=lambda r: hashlib.sha256(r['site_id'].encode()).hexdigest())[:20]
        for rank, r in enumerate(selected, 1):
            samples.append(dict(sample=rank, **r))
    write_tsv(out / 'top_functions.tsv', ['category', 'rank', 'file', 'function', 'casts'], top_fn)
    write_tsv(out / 'top_type_pairs.tsv', ['category', 'rank', 'from_type', 'to_type', 'casts'], top_pair)
    write_tsv(out / 'sample20.tsv', ['sample', *fields], samples)
    write_tsv(out / 'ast_errors.tsv', ['tu', 'error'], errors)
    unresolved = [r for r in rows if r['ast_status'] == 'missing']
    write_tsv(out / 'unresolved.tsv', fields, unresolved)
    totals = dict(base_revision=subprocess.check_output(['git', 'rev-parse', 'HEAD'], cwd=root, text=True).strip(), source_files=len(files),
                  debt_pointer_casts=len(rows), classified=len(rows), by_category=dict(by_category),
                  ast_status=dict(Counter(r['ast_status'] for r in rows)), ast_errors=len(errors),
                  ast_type_variants=sum(r.get('ast_variants', 0) > 1 for r in rows),
                  callback_functions=len(callbacks), runtime_join='not available in private root',
                  precedence=['redundant', 'node_body', 'generated_view', 'sdk', 'int_pointer', 'other:function_pointer_floor',
                              'callback_param', 'byte_cursor', 'call_arg', 'union_pun', 'other'])
    (out / 'totals.json').write_text(json.dumps(totals, indent=2) + '\n')
    print(json.dumps(totals, indent=2), flush=True)


if __name__ == '__main__':
    main()
