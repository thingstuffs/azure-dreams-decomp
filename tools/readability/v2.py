"""Registry-driven additions to the frozen readability-v1 lexical census.

No preprocessing, type inference, source rewriting or build dependency. All detector
names are an explicit allowlist; registry entries are data, never executable code.
"""
from __future__ import annotations

import argparse
from bisect import bisect_right
from collections import Counter, defaultdict
from concurrent.futures import ProcessPoolExecutor
from dataclasses import dataclass, field
import hashlib
import json
from pathlib import Path
import re
import sys

import score as v1

SCHEMA = 'readability-v2'
DETECTORS = {'offset_macro', 'member_byte_view', 'fixed_address_cast',
             'local_placeholder_type', 'sign_extension', 'do_while_zero',
             'double_scalar_cast', 'repeated_lines', 'hex_named_literal'}
NAME = re.compile(r'^[a-z][a-z0-9_]*$')
PLACEHOLDER = re.compile(r'^(?:Entity|Actor|Rec(?:_\w+)?|S_(?:func_)?[0-9A-Fa-f]{8}_\w+)$')
PADDING = re.compile(r'^(?:pad|unk)(?:_[A-Za-z0-9_]+|[0-9A-Fa-f]+)?$')


@dataclass(frozen=True)
class Pattern:
    id: str
    category: str
    metric: str
    weight: int
    example: str
    why: str
    owner_decision: str | None
    detector: str = ''
    regex: str = ''
    options: dict = field(default_factory=dict)


@dataclass(frozen=True)
class Registry:
    patterns: tuple
    sha256: str

    @property
    def categories(self):
        return v1.CATEGORIES + tuple(sorted({p.category for p in self.patterns}))

    @property
    def metrics(self):
        return v1.METRICS + tuple(sorted({p.metric for p in self.patterns})) + ('v1_score',)

    @property
    def scores(self):
        return tuple(c + '_score' for c in self.categories) + ('score',)


def load_registry(path):
    data = path.read_bytes()
    patterns, seen, metrics = [], set(), {}
    for line, raw in enumerate(data.decode('utf-8').splitlines(), 1):
        if not raw.strip():
            continue
        try:
            rec = json.loads(raw)
            required = {'id', 'category', 'metric', 'weight', 'example', 'why', 'owner_decision'}
            if not isinstance(rec, dict) or not required <= rec.keys():
                raise ValueError('missing required fields')
            if set(rec) - required - {'detector', 'regex', 'options'}:
                raise ValueError('unknown fields')
            for key in ('id', 'category', 'metric'):
                if not isinstance(rec[key], str) or not NAME.fullmatch(rec[key]):
                    raise ValueError('invalid ' + key)
            if rec['id'] in seen:
                raise ValueError('duplicate id ' + rec['id'])
            if rec['category'] in v1.CATEGORIES or rec['metric'] in v1.METRICS + v1.SCORES + ('v1_score',):
                raise ValueError('legacy category/metric is reserved')
            if type(rec['weight']) is not int or rec['weight'] <= 0:
                raise ValueError('weight must be a positive integer')
            if any(not isinstance(rec[k], str) or not rec[k].strip() for k in ('example', 'why')):
                raise ValueError('example and why must be nonempty strings')
            if rec['owner_decision'] is not None and not isinstance(rec['owner_decision'], str):
                raise ValueError('owner_decision must be a string or null')
            detector, regex = rec.get('detector', ''), rec.get('regex', '')
            if bool(detector) == bool(regex):
                raise ValueError('specify exactly one detector or regex')
            if detector and detector not in DETECTORS:
                raise ValueError('unknown detector ' + str(detector))
            if regex:
                if not isinstance(regex, str):
                    raise ValueError('regex must be a string')
                compiled = re.compile(regex)
                if compiled.search(''):
                    raise ValueError('regex must not match empty input')
            opts = rec.get('options', {})
            if not isinstance(opts, dict):
                raise ValueError('options must be an object')
            expected = {
                'offset_macro': {'names', 'offset_arg', 'arity'},
                'hex_named_literal': {'names'}, 'repeated_lines': {'min_lines'},
            }.get(detector, set())
            if set(opts) - expected:
                raise ValueError('unknown detector options')
            if detector in {'offset_macro', 'hex_named_literal'}:
                if not isinstance(opts.get('names'), list) or not opts['names'] or any(
                        not isinstance(n, str) or not v1.IDENT.fullmatch(n) for n in opts['names']):
                    raise ValueError('names must be a nonempty list of identifiers')
            if detector == 'offset_macro':
                if (type(opts.get('arity')) is not int or type(opts.get('offset_arg')) is not int
                        or not 0 <= opts['offset_arg'] < opts['arity']):
                    raise ValueError('invalid macro arity/offset_arg')
            if detector == 'repeated_lines' and (type(opts.get('min_lines', 8)) is not int
                                               or opts.get('min_lines', 8) < 8):
                raise ValueError('min_lines must be at least eight')
            signature = (rec['category'], rec['weight'])
            if rec['metric'] in metrics and metrics[rec['metric']] != signature:
                raise ValueError('one metric must have one category and weight')
            metrics[rec['metric']] = signature
            seen.add(rec['id'])
            patterns.append(Pattern(**rec))
        except (ValueError, TypeError, re.error) as exc:
            raise ValueError(f'registry line {line}: {exc}') from exc
    if not patterns:
        raise ValueError('empty oddities registry')
    # A metric cannot collide with a generated category score column.
    if set(metrics) & {p.category + '_score' for p in patterns}:
        raise ValueError('metric collides with category score')
    return Registry(tuple(patterns), hashlib.sha256(data).hexdigest())


def integer(value):
    value = re.sub(r'[uUlL]+$', '', value)
    if re.fullmatch(r'0[xX][0-9a-fA-F]+', value):
        return int(value, 16)
    if re.fullmatch(r'0[0-7]+', value):
        return int(value, 8)
    if re.fullmatch(r'\d+', value):
        return int(value, 10)
    return None


def ungroup(tokens, pairs, start, end):
    while start < end and tokens[start].value == '(' and pairs.get(start) == end - 1:
        start, end = start + 1, end - 1
    return start, end


def numeric_operand(tokens, pairs, start, end):
    start, end = ungroup(tokens, pairs, start, end)
    if start < end and tokens[start].value in {'+', '-'}:
        start += 1
        start, end = ungroup(tokens, pairs, start, end)
    return start if end == start + 1 and tokens[start].kind == 'number' and integer(tokens[start].value) is not None else None


def arguments(tokens, pairs, opening):
    end = pairs.get(opening)
    if end is None:
        return []
    result, begin, i = [], opening + 1, opening + 1
    while i < end:
        value = tokens[i].value
        if value in {'(', '[', '{'} and i in pairs:
            i = pairs[i] + 1
            continue
        if value == ',':
            result.append((begin, i))
            begin = i + 1
        i += 1
    result.append((begin, end))
    return result


@dataclass
class Context:
    tokens: list
    pairs: dict
    text: str
    newlines: list

    def line(self, i):
        return bisect_right(self.newlines, self.tokens[i].pos)

    def detail(self, a, b):
        return ' '.join(t.value for t in self.tokens[a:b])[:240]


def detect(ctx, pattern):
    """Yield (first token, exclusive last token, units, diagnostic)."""
    ts, pairs, kind, opts = ctx.tokens, ctx.pairs, pattern.detector, pattern.options
    if pattern.regex:
        # Quoted contents never participate; this is normalized C tokens, not raw C.
        chunks = [t.value if t.kind != 'literal' else '<literal>' for t in ts]
        offsets, cursor = [], 0
        for chunk in chunks:
            offsets.append(cursor)
            cursor += len(chunk) + 1
        for m in re.finditer(pattern.regex, ' '.join(chunks)):
            if m.start() == m.end():
                raise ValueError('registry regex produced an empty match: ' + pattern.id)
            a = max(0, bisect_right(offsets, m.start()) - 1)
            b = bisect_right(offsets, m.end() - 1)
            yield a, b, 1, ctx.detail(a, b)
    elif kind == 'offset_macro':
        for i, t in enumerate(ts[:-1]):
            if (t.kind != 'id' or t.value not in opts['names'] or ts[i + 1].value != '('
                    or (i and ts[i - 1].value in {'.', '->'})):
                continue
            args = arguments(ts, pairs, i + 1)
            if len(args) == opts['arity'] and numeric_operand(ts, pairs, *args[opts['offset_arg']]) is not None:
                end = pairs[i + 1] + 1
                yield i, end, 1, ctx.detail(i, end)
    elif kind == 'member_byte_view':
        for a, b in v1.cast_sites(ts, pairs):
            values = [t.value for t in ts[a + 1:b]]
            if not set(values) & v1.BYTE_TYPES or values.count('*') != 1:
                continue
            end = v1.operand_end(ts, pairs, b + 1)
            operand = ts[b + 1:end]
            # An address of a member viewed as bytes is debt even without + N.
            if any(t.value == '&' for t in operand) and any(t.value in {'.', '->'} for t in operand):
                yield a, end, 1, ctx.detail(a, end)
    elif kind == 'fixed_address_cast':
        for a, b in v1.cast_sites(ts, pairs):
            end = v1.operand_end(ts, pairs, b + 1)
            n = numeric_operand(ts, pairs, b + 1, end)
            if n is not None and integer(ts[n].value) not in {0, 1}:
                address = integer(ts[n].value)
                operand, _ = ungroup(ts, pairs, b + 1, end)
                if ts[operand].value == '-':
                    address = -address
                label = 'scratchpad' if 0x1F800000 <= address < 0x1F800400 else 'fixed address candidate'
                yield a, end, 1, label + ': ' + ctx.detail(a, end)
    elif kind == 'sign_extension':
        # Expression spelling, accepting decimal, hex and suffixes for the shifts.
        for i in range(1, len(ts) - 3):
            if ts[i].value != '<<' or integer(ts[i + 1].value) != 16:
                continue
            j = i + 2
            while j < len(ts) and ts[j].value == ')':
                j += 1
            if j + 1 < len(ts) and ts[j].value == '>>' and integer(ts[j + 1].value) == 16:
                yield i - 1, j + 2, 1, ctx.detail(i - 1, j + 2)
        # Adjacent split statements: x = expression << 16; x >>= 16; or x <<= 16; ...
        for i, t in enumerate(ts[:-4]):
            if t.value != ';' or i < 2 or integer(ts[i - 1].value) != 16 or ts[i - 2].value not in {'<<', '<<='}:
                continue
            begin = i - 2
            while begin > 0 and ts[begin - 1].value not in {';', '{', '}'}:
                begin -= 1
            if (ts[begin].kind == 'id' and begin + 1 < i and ts[begin + 1].value in {'=', '<<='}
                    and ts[i + 1].value == ts[begin].value and ts[i + 2].value == '>>='
                    and integer(ts[i + 3].value) == 16 and ts[i + 4].value == ';'):
                yield begin, i + 5, 1, ctx.detail(begin, i + 5)
    elif kind == 'do_while_zero':
        for i, t in enumerate(ts[:-1]):
            if t.value != 'do' or ts[i + 1].value != '{' or i + 1 not in pairs:
                continue
            j = pairs[i + 1] + 1
            if j + 1 >= len(ts) or ts[j].value != 'while' or ts[j + 1].value != '(' or j + 1 not in pairs:
                continue
            close = pairs[j + 1]
            n = numeric_operand(ts, pairs, j + 2, close)
            if n is not None and integer(ts[n].value) == 0:
                yield i, close + 1, 1, ctx.detail(i, close + 1)
    elif kind == 'double_scalar_cast':
        wide = {'s32', 'int', 'int32_t', 'signed int'}
        narrow = {'s16', 'short', 'signed short', 'short int', 'signed short int', 'int16_t'}
        for i, t in enumerate(ts):
            if t.value != '(' or i not in pairs:
                continue
            j = pairs[i]
            k = j + 1
            if k >= len(ts) or ts[k].value != '(' or k not in pairs:
                continue
            end = pairs[k]
            if (ctx.detail(i + 1, j) in wide and ctx.detail(k + 1, end) in narrow
                    and end + 1 < len(ts) and (ts[end + 1].kind in {'id', 'number'} or ts[end + 1].value in {'(', '*', '&', '-', '+'})):
                yield i, end + 1, 1, ctx.detail(i, end + 1)
    elif kind == 'hex_named_literal':
        wanted = {n.lower() for n in opts['names']}
        def named(start, end):
            start, end = ungroup(ts, pairs, start, end)
            while start < end and ts[start].value in {'*', '&'}:
                start += 1
                start, end = ungroup(ts, pairs, start, end)
            if start >= end or ts[start].kind != 'id':
                return False
            name, cursor = ts[start].value, start + 1
            # Local named initializers have a type/qualifier prefix before the name.
            if all(t.kind == 'id' or t.value == '*' for t in ts[start:end]) and ts[end - 1].kind == 'id':
                name, cursor = ts[end - 1].value, end
            while cursor < end:
                if ts[cursor].value == '[' and cursor in pairs and pairs[cursor] < end:
                    cursor = pairs[cursor] + 1
                elif ts[cursor].value in {'.', '->'} and cursor + 1 < end and ts[cursor + 1].kind == 'id':
                    name, cursor = ts[cursor + 1].value, cursor + 2
                else:
                    return False
            segments = re.sub(r'([a-z0-9])([A-Z])', r'\1_\2', name).lower().split('_')
            return bool(wanted.intersection(segments))

        stops = {';', '{', '}', '&&', '||', ',', '?', ':'} | v1.ASSIGN | v1.COMPARE

        def boundary(i, step):
            while 0 <= i < len(ts):
                value = ts[i].value
                if value in stops:
                    break
                if step == -1 and value in {')', ']'} and i in pairs:
                    i = pairs[i] - 1
                elif step == 1 and value in {'(', '['} and i in pairs:
                    i = pairs[i] + 1
                elif (step == -1 and value in {'(', '['}) or (step == 1 and value in {')', ']'}):
                    break
                else:
                    i += step
            return i

        found = set()
        # Direct named operand and integer literal, never a name buried in an expression.
        for i, t in enumerate(ts):
            if t.value not in {'=', '+=', '-='} | v1.COMPARE:
                continue
            left, right = boundary(i - 1, -1) + 1, boundary(i + 1, 1)
            for a, b, other_a, other_b in ((i + 1, right, left, i), (left, i, i + 1, right)):
                n = numeric_operand(ts, pairs, a, b)
                if n is not None and ts[n].value.lower().startswith('0x') and named(other_a, other_b):
                    found.add(n)
        for n in sorted(found):
            yield n, n + 1, 1, ctx.detail(n, n + 1)


def local_types(tokens, pairs, line):
    """Inventory placeholder struct definitions, including forward typedef + tag body.

    These are consolidation candidates; shared layout equivalence needs owner review.
    Only member declaration names, not comments or array expressions, qualify as pad/unk.
    """
    aliases = defaultdict(set)
    for i, t in enumerate(tokens[:-3]):
        if t.value == 'typedef' and tokens[i + 1].value == 'struct' and tokens[i + 2].kind == 'id':
            if tokens[i + 3].kind == 'id' and i + 4 < len(tokens) and tokens[i + 4].value == ';':
                aliases[tokens[i + 2].value].add(tokens[i + 3].value)
    result = []
    for i, t in enumerate(tokens[:-1]):
        if t.value != 'struct':
            continue
        j = i + 1
        tag = tokens[j].value if tokens[j].kind == 'id' else ''
        if tag:
            j += 1
        if j >= len(tokens) or tokens[j].value != '{' or j not in pairs:
            continue
        end = pairs[j]
        names = set(aliases.get(tag, ()))
        # typedef may have qualifiers before struct; inspect its statement prefix.
        begin = i
        while begin and tokens[begin - 1].value not in {';', '{', '}'}:
            begin -= 1
        if any(t.value == 'typedef' for t in tokens[begin:i]):
            k = end + 1
            if k < len(tokens) and tokens[k].kind == 'id':
                names.add(tokens[k].value)
        names = sorted(n for n in names if PLACEHOLDER.fullmatch(n))
        members = set()
        for k in range(j + 1, end - 1):
            if (tokens[k].kind == 'id' and PADDING.fullmatch(tokens[k].value)
                    and tokens[k + 1].value in {'[', ';', ',', ':'}):
                members.add(tokens[k].value)
        if names and members:
            result.append(dict(names=names, line=line(tokens[i].pos), end_line=line(tokens[end].pos),
                               start=tokens[i].pos, end=tokens[end].pos, members=sorted(members)))
    return result


def add_hit(f, pattern, first, last, units, detail):
    f.metrics[pattern.metric] += units
    f.metrics[pattern.category + '_score'] += units * pattern.weight
    f.oddities.append(dict(pattern_id=pattern.id, metric=pattern.metric, category=pattern.category,
                           line=first, end_line=last, units=units, detail=detail))


def analyze_source(path, data, registry):
    source = v1.analyze_source(path, data)
    text = data.decode('utf-8', 'surrogateescape')
    tokens = v1.lex(text)
    pairs, _ = v1.pairs_of(tokens)
    newlines = [-1] + [m.start() for m in re.finditer('\n', text)]
    line = lambda pos: bisect_right(newlines, pos)
    source.type_debts = local_types(tokens, pairs, line)
    type_patterns = [p for p in registry.patterns if p.detector == 'local_placeholder_type']
    for debt in source.type_debts:
        debt['users'] = set()
    for f, (start, name, brace, end, _) in zip(source.functions, v1.definitions(tokens, pairs)):
        f.metrics['v1_score'] = f.metrics['score']
        for metric in set(registry.metrics) - set(v1.METRICS) - {'v1_score'}:
            f.metrics[metric] = 0
        for category in registry.categories[len(v1.CATEGORIES):]:
            f.metrics[category + '_score'] = 0
        f.oddities = []
        body = tokens[brace + 1:end]
        bpairs = {i - brace - 1: pairs[i] - brace - 1 for i in range(brace + 1, end) if i in pairs}
        ctx = Context(body, bpairs, text, newlines)
        for pattern in registry.patterns:
            for a, b, units, detail in detect(ctx, pattern):
                add_hit(f, pattern, ctx.line(a), ctx.line(b - 1), units, detail)
        identifiers = {t.value for t in tokens[start:end + 1] if t.kind == 'id'}
        for debt in source.type_debts:
            # File-scope definitions may be used before their body (forward typedef).
            # Block-local definitions only belong to the containing function.
            inside = tokens[brace].pos < debt['start'] < tokens[end].pos
            in_other = any(g.line <= debt['line'] <= g.end_line for g in source.functions if g is not f)
            if not in_other and identifiers.intersection(debt['names']):
                debt['users'].add(f.key)
                for pattern in type_patterns:
                    add_hit(f, pattern, debt['line'], debt['end_line'], 1,
                            ','.join(debt['names']) + ': ' + ','.join(debt['members']) +
                            (' (block local)' if inside else ' (file local)'))
        by_line = defaultdict(list)
        for t in body:
            by_line[line(t.pos)].append(t.value)
        # Brace-only lines do not make an eight-line statement sequence.
        f.clone_lines = [(n, ' '.join(values)) for n, values in sorted(by_line.items())
                         if any(v not in {'{', '}', ';'} for v in values)]
        f.metrics['score'] = sum(f.metrics[c + '_score'] for c in registry.categories)
    return source


def count_duplicates(functions, registry):
    """Index eight-line seeds; score the union of later-copy lines, never window count.

    Canonical occurrence is the earliest (function key, body-line index). Same-function
    windows must not overlap. Exact tokens/literals are retained; no identifier renaming.
    """
    evidence = []
    fs = sorted(functions, key=lambda f: f.key)
    for pattern in (p for p in registry.patterns if p.detector == 'repeated_lines'):
        width = pattern.options.get('min_lines', 8)
        index = defaultdict(list)
        for fi, f in enumerate(fs):
            values = [text for _, text in f.clone_lines]
            for start in range(len(values) - width + 1):
                index[tuple(values[start:start + width])].append((fi, start))
        coverage = defaultdict(set)
        matches = defaultdict(list)
        for occurrences in index.values():
            if len(occurrences) < 2:
                continue
            canonical_fi, canonical_start = occurrences[0]
            for fi, start in occurrences[1:]:
                if fi == canonical_fi and start < canonical_start + width:
                    continue
                coverage[fi].update(range(start, start + width))
                matches[(fi, canonical_fi, canonical_start - start)].append(start)
        for (fi, ref_fi, delta), starts in sorted(matches.items()):
            starts.sort()
            first, last = starts[0], starts[0] + width
            for start in starts[1:] + [len(fs[fi].clone_lines) + width]:
                if start <= last:
                    last = max(last, start + width)
                    continue
                f, ref = fs[fi], fs[ref_fi]
                evidence.append(dict(pattern_id=pattern.id, function_id=f.key,
                    line=f.clone_lines[first][0], end_line=f.clone_lines[last - 1][0],
                    matched_lines=last - first, reference_id=ref.key,
                    reference_line=ref.clone_lines[first + delta][0],
                    reference_end_line=ref.clone_lines[last - 1 + delta][0]))
                first, last = start, start + width
        for fi, covered in sorted(coverage.items()):
            f = fs[fi]
            indices = sorted(covered)
            first, last = indices[0], indices[0]
            for idx in indices[1:] + [indices[-1] + 2]:
                if idx == last + 1:
                    last = idx
                    continue
                add_hit(f, pattern, f.clone_lines[first][0], f.clone_lines[last][0], last - first + 1,
                        'union of redundant code lines; exact >= ' + str(width) + '-line seeds; see duplicates.tsv')
                first = last = idx
            f.metrics['score'] = sum(f.metrics[c + '_score'] for c in registry.categories)
    return evidence


def scan_path(item):
    root, path, registry = item
    if path.is_symlink():
        raise ValueError('source symlink refused: ' + path.relative_to(root).as_posix())
    return analyze_source(path.relative_to(root).as_posix(), path.read_bytes(), registry)


def scan(root, registry, workers=1):
    paths = sorted(p for suffix in ('*.c', '*.h') for p in (root / 'src').rglob(suffix))
    items = [(root, p, registry) for p in paths]
    if workers == 1:
        sources = [scan_path(item) for item in items]
    else:
        with ProcessPoolExecutor(max_workers=workers) as pool:
            sources = list(pool.map(scan_path, items, chunksize=16))
    functions = [f for source in sources for f in source.functions]
    duplicates = count_duplicates(functions, registry)
    edges, unresolved = v1.resolve_calls(functions)
    return sources, functions, edges, unresolved, duplicates


def summarize(sources, functions, key, registry):
    groups = defaultdict(list)
    counts = Counter(key(s.path) for s in sources)
    for f in functions:
        groups[key(f.path)].append(f)
    for group in sorted(counts):
        fs = groups[group]
        row = dict(group=group, files=counts[group], functions=len(fs))
        for metric in registry.metrics + registry.scores:
            row[metric] = (max((f.metrics[metric] for f in fs), default=0) if metric == 'max_nesting'
                           else sum(f.metrics[metric] for f in fs))
        yield row


def explain(f, registry):
    parts = [v1.explain(f)]
    for metric in sorted({p.metric for p in registry.patterns}):
        if f.metrics[metric]:
            parts.append(f'{f.metrics[metric]} {metric}')
    return '; '.join(p for p in parts if p != 'no weighted debt') or 'no weighted debt'


def tidy_misses(functions, max_score=100, min_lines=80):
    """An explicit absolute cutoff avoids source-length dilution of the v1 score."""
    return sorted((f for f in functions if f.metrics['v1_score'] <= max_score
                   and f.metrics['code_lines'] >= min_lines and f.metrics['score'] > f.metrics['v1_score']),
                  key=lambda f: (-f.metrics['score'], -f.metrics['score'] + f.metrics['v1_score'], f.key))[:30]


def write_outputs(out, revision, sources, functions, edges, unresolved, duplicates, registry,
                  tidy_max_score=100, tidy_min_lines=80):
    columns = ('function_id', 'path', 'symbol', 'occurrence', 'line', 'end_line', 'static',
               'known_callers', 'anchor_sha256', 'header_style') + registry.metrics + registry.scores
    v1.write_tsv(out / 'scores.tsv', columns, (dict(function_id=f.key, path=f.path, symbol=f.symbol,
        occurrence=f.occurrence, line=f.line, end_line=f.end_line, static=int(f.static),
        known_callers=len(f.callers), anchor_sha256=f.anchor, header_style=f.header_style, **f.metrics) for f in functions))
    for label, key in [('files', lambda p: p), ('folders', lambda p: str(Path(p).parent)),
                       ('subsystems', lambda p: p.split('/')[1] if '/' in p else p)]:
        v1.write_tsv(out / f'{label}.tsv', ('group', 'files', 'functions') + registry.metrics + registry.scores,
                     summarize(sources, functions, key, registry))
    v1.write_tsv(out / 'coverage.tsv', ('path', 'sha256', 'bytes', 'definitions', 'warnings'),
        (dict(path=s.path, sha256=s.sha256, bytes=s.byte_count, definitions=len(s.functions), warnings=len(s.warnings)) for s in sources))
    v1.write_tsv(out / 'parse_warnings.tsv', ('path', 'line', 'reason'),
        (dict(path=s.path, line=n, reason=reason) for s in sources for n, reason in s.warnings))
    v1.write_tsv(out / 'calls.tsv', ('caller', 'callee'), edges)
    v1.write_tsv(out / 'unresolved_calls.tsv', ('caller', 'symbol', 'reason', 'candidates'), unresolved)
    v1.write_tsv(out / 'oddities.tsv', ('function_id', 'pattern_id', 'category', 'metric', 'line', 'end_line', 'units', 'detail'),
        (dict(function_id=f.key, **h) for f in functions for h in f.oddities))
    v1.write_tsv(out / 'duplicates.tsv', ('pattern_id', 'function_id', 'line', 'end_line', 'matched_lines',
        'reference_id', 'reference_line', 'reference_end_line'), duplicates)
    v1.write_tsv(out / 'local_types.tsv', ('path', 'line', 'end_line', 'names', 'placeholder_members', 'users', 'function_ids'),
        (dict(path=s.path, line=d['line'], end_line=d['end_line'], names=','.join(d['names']),
            placeholder_members=','.join(d['members']), users=len(d['users']), function_ids=';'.join(sorted(d['users'])))
         for s in sources for d in s.type_debts))
    for category in registry.categories:
        ranked = sorted((f for f in functions if f.metrics[category + '_score']),
            key=lambda f: (-f.metrics[category + '_score'] * max(1, len(f.callers)), -f.metrics[category + '_score'], f.key))
        v1.write_tsv(out / 'queue' / f'{category}.tsv',
            ('rank', 'function_id', 'path', 'symbol', 'occurrence', 'line', 'anchor_sha256', 'category_score',
             'known_callers', 'caller_multiplier', 'payoff', 'total_score', 'evidence'),
            (dict(rank=i, function_id=f.key, path=f.path, symbol=f.symbol, occurrence=f.occurrence,
                line=f.line, anchor_sha256=f.anchor, category_score=f.metrics[category + '_score'],
                known_callers=len(f.callers), caller_multiplier=max(1, len(f.callers)),
                payoff=f.metrics[category + '_score'] * max(1, len(f.callers)), total_score=f.metrics['score'],
                evidence=explain(f, registry)) for i, f in enumerate(ranked, 1)))
    digest = hashlib.sha256(''.join(f'{s.path}\0{s.sha256}\n' for s in sources).encode()).hexdigest()
    metadata = dict(schema=SCHEMA, revision=revision, source_sha256=digest, registry_sha256=registry.sha256,
        source_files=len(sources), c_files=sum(s.path.endswith('.c') for s in sources),
        header_files=sum(s.path.endswith('.h') for s in sources), functions=len(functions),
        source_bytes=sum(s.byte_count for s in sources), parse_warnings=sum(len(s.warnings) for s in sources),
        knr_definitions=sum(f.header_style == 'knr' for f in functions), zero_definition_files=sum(not s.functions for s in sources),
        resolved_edges=len(edges), unresolved_calls=len(unresolved),
        tidy_max_v1_score=tidy_max_score, tidy_min_code_lines=tidy_min_lines,
        legacy_weights=','.join(f'{k}:{v}' for k, v in v1.WEIGHTS.items()),
        registry_weights=','.join(f'{p.id}:{p.weight}' for p in registry.patterns))
    v1.write_tsv(out / 'metadata.tsv', ('key', 'value'), (dict(key=k, value=v) for k, v in metadata.items()))
    v1.write_tsv(out / 'trend.tsv', ('schema', 'revision', 'category', 'weighted_debt'),
        (dict(schema=SCHEMA, revision=revision, category=c, weighted_debt=sum(f.metrics[c + '_score'] for f in functions)) for c in registry.categories))
    v1.write_tsv(out / 'pattern_totals.tsv', ('pattern_id', 'category', 'metric', 'units', 'weight', 'weighted_debt', 'functions'),
        (dict(pattern_id=p.id, category=p.category, metric=p.metric, units=sum(h['units'] for f in functions for h in f.oddities if h['pattern_id'] == p.id),
            weight=p.weight, weighted_debt=p.weight * sum(h['units'] for f in functions for h in f.oddities if h['pattern_id'] == p.id),
            functions=sum(any(h['pattern_id'] == p.id for h in f.oddities) for f in functions)) for p in registry.patterns))
    misses = tidy_misses(functions, tidy_max_score, tidy_min_lines)
    v1.write_tsv(out / 'tidy_misses.tsv', ('rank', 'function_id', 'path', 'symbol', 'line', 'anchor_sha256',
        'code_lines', 'v1_score', 'v2_score', 'added_debt', 'evidence'),
        (dict(rank=i, function_id=f.key, path=f.path, symbol=f.symbol, line=f.line, anchor_sha256=f.anchor,
            code_lines=f.metrics['code_lines'], v1_score=f.metrics['v1_score'], v2_score=f.metrics['score'],
            added_debt=f.metrics['score'] - f.metrics['v1_score'], evidence=explain(f, registry)) for i, f in enumerate(misses, 1)))


def render_docs(revision, sources, functions, edges, unresolved, registry, tidy_max_score=100, tidy_min_lines=80):
    rows = [f'# Readability census\n\nBaseline: `{revision}`; schema: `{SCHEMA}`. '
        f'{len(sources):,} physical `.c`/`.h` files under `src/`, {len(functions):,} definitions, '
        f'{sum(s.byte_count for s in sources):,} bytes; {sum(len(s.warnings) for s in sources)} delimiter warnings.\n',
        'Scores describe visible source debt and review candidates. They do not establish correctness, '
        'shared layout equivalence, removable casts, or safe matching-C rewrites. No source files are changed. '
        'Function identity remains relative path, symbol, occurrence, and a token-normalized SHA-256 anchor. '
        'Comments, directives (including macro definitions), and quoted contents never create detector hits. '
        'Both conditional branches are counted textually. Includes are not expanded.\n',
        '## Legacy measurements\n\nThe five v1 category scores, definitions and weights are unchanged in v2. '
        '`v1_score` is their original sum on the same function. `--schema v1` uses the frozen implementation '
        'and ignores the registry, emitting the original columns, queues, trend and methodology.\n']
    legacy = v1.render_docs(revision, sources, functions, edges, unresolved)
    rows.append(legacy.split('## Measurements and weights\n\n', 1)[1].split('## Subsystems', 1)[0].replace(
        'Total score is the sum of five category scores.', 'The v1 score is the sum of these five category scores.'))
    rows.extend(['## Added measurements\n',
        '| Category | Units and boundary | Weight |\n| --- | --- | ---: |',
        '| offset_macros | Literal offset argument in F(owner,type,offset), U8/S8/S16/U16/U32/S32(owner,offset), '
        'U8/S8/S16/U16/U32/S32_AT(owner,offset), PTR(owner,offset). Exact macro spellings/arity live in the registry. '
        'Nested owner expressions and signed/grouped integer offsets allowed; dynamic offsets excluded. | 8/access |',
        '| byte_views | Spelled byte-pointer cast of an address-of member expression, including '
        '`(u8 *)&x->unk_10 + 1`. Count once per cast even without arithmetic. | 8/view |',
        '| fixed_addresses | Spelled pointer cast whose operand is an integer other than 0 or +/-1. '
        '`0x1F800000..0x1F8003FF` is labeled scratchpad in evidence; other integers are fixed-address candidates '
        '(may include sentinels). Dereference is not required. | 8/cast |',
        '| local_types | Placeholder struct typedef candidates named Entity, Actor, Rec or Rec_*, '
        'S_[func_]8hex_suffix with a pad*/unk* member. Forward typedef + tag definitions included. '
        'One unit per definition per function spelling its type in signature/body, including block-local types. '
        'Declarations/fields only, never quoted text, trigger membership. | 12/type user |',
        '| sign_extension | `(... << 16) >> 16` or adjacent `x = expr << 16; x >>= 16;` '
        '(also <<=), decimal/hex/suffixed shifts accepted. Counts spelling, not inferred signedness. | 3/idiom |',
        '| wrappers | Body-spelled `do { ... } while (0)` with a constant integer zero condition. '
        'Macro definitions are excluded by the lexer. | 3/wrapper |',
        '| double_casts | Adjacent signed 32-bit then signed 16-bit scalar casts: `(s32)(s16)`, '
        'int32_t/int16_t and built-in signed int/short equivalents. Other scalar cast chains excluded. | 3/chain |',
        '| duplicates | Exact token-normalized sequences of >=8 substantive physical body lines, within '
        'or across functions/files. Brace-only/comment/blank lines excluded; declarations/control lines included; '
        'literal values and identifiers retained. Earliest (function key, line index) copy is canonical. '
        'Same-function seed windows must not overlap. Score the union of later-copy lines once, including '
        'overlapping seeds. Adjacent covered lines merge into evidence ranges; a range may have several references '
        'in duplicates.tsv. This detects copy candidates, including conditional/overlay copies, without asserting '
        'that extraction is safe or runtime code is duplicated. Formatting across physical lines or renamed locals '
        'can prevent detection. | 2/redundant code line |',
        '| hex_states | Direct hex integer assignment/comparison with an identifier segment state, '
        'timer or countdown (snake_case/camelCase, case insensitive). State and timer units exported separately; '
        '0/1 included here. Arithmetic expressions, bitmask operations, decimal values, case labels, '
        'unnamed fields, and semantic aliases excluded. A hex literal is not judged wrong. | 2/literal |\n',
        'Total v2 debt is the sum of all category scores. Cross-category overlap is intentional: '
        'a member byte view can already be a v1 byte offset, and a hex state can already be a magic literal. '
        'Added debt is `score - v1_score`, not a v1 trend delta. Each detector hit carries pattern id, '
        'source line span, units and a diagnostic in `oddities.tsv`. `local_types.tsv` inventories candidates '
        'including those without direct function users; unreferenced types contribute no function score. '
        'A lexical candidate does not prove it duplicates a shared type; an owner must check include/ layouts. '
        f'This snapshot has {sum(len(s.type_debts) for s in sources):,} type definitions, '
        f'{sum(not d["users"] for s in sources for d in s.type_debts):,} without direct function users.\n',
        '## Oddities registry\n\n`ledger/readability_oddities.jsonl` is loaded automatically in v2. '
        'One JSON object per pattern requires id, category, metric, positive integer weight, example, why, '
        'owner_decision (string or null), and exactly one detector or regex. Built-in detector names are an '
        'allowlist; invalid/duplicate ids, reserved v1 names, unknown options, inconsistent metric weights and '
        'empty-match regexes fail the run. A regex is applied to space-separated body tokens with quoted '
        'literals replaced by `<literal>`. Append a regex entry to add a category/metric and queue without '
        'editing Python; structural patterns use a tested allowlisted detector. There is no eval or dynamic import '
        'from registry data. Review regexes for runtime cost. Changing the registry changes the metric: retain '
        'its SHA-256 with every trend and compare only identical schema/registry/weights.\n',
        '| Pattern | Detector | Category / metric | Owner decision |\n| --- | --- | --- | --- |'])
    for p in registry.patterns:
        rows.append(f'| {p.id} | `{p.detector or p.regex}` | {p.category} / {p.metric} | {p.owner_decision or "pending"} |')
    rows.extend(['\n## Per-category totals\n', '| Category | Units | Weighted debt | Functions |', '| --- | ---: | ---: | ---: |'])
    for c in registry.categories:
        patterns = [p for p in registry.patterns if p.category == c]
        units = sum(h['units'] for f in functions for h in f.oddities if h['category'] == c) if patterns else None
        rows.append(f'| {c} | {units if units is not None else "mixed v1 measures"} | '
                    f'{sum(f.metrics[c + "_score"] for f in functions):,} | '
                    f'{sum(bool(f.metrics[c + "_score"]) for f in functions):,} |')
    rows.append(f'\nTotal: **{sum(f.metrics["score"] for f in functions):,}**; '
                f'original v1 debt: **{sum(f.metrics["v1_score"] for f in functions):,}**; '
                f'added categories: **{sum(f.metrics["score"] - f.metrics["v1_score"] for f in functions):,}**. '
                '`pattern_totals.tsv` separates individual registry patterns and units.\n')
    rows.extend(['## Per-subsystem totals\n', '| Subsystem | Files | Definitions | ' +
        ' | '.join(registry.categories) + ' | Total |', '| --- | ---: | ---: | ' + ' | '.join('---:' for _ in registry.categories) + ' | ---: |'])
    for r in summarize(sources, functions, lambda p: p.split('/')[1], registry):
        values = [r['files'], r['functions']] + [r[c + '_score'] for c in registry.categories] + [r['score']]
        rows.append('| ' + r['group'] + ' | ' + ' | '.join(f'{v:,}' for v in values) + ' |')
    rows.extend(['\nSubsystems/files/folders sum every metric except max_nesting (maximum). '
                 'Local type counts sum type users; duplicate lines sum redundant-copy coverage.\n',
        '## Thirty worst functions v1 rated tidy\n\n'
        f'Operational definition: v1 score <= {tidy_max_score}, >= {tidy_min_lines} code lines, '
        'positive added debt; rank by v2 score, then added debt, then function key. These absolute '
        'cutoffs and the eligible count are explicit; the score is not divided by length. '
        'Override with --tidy-max-score and --tidy-min-lines. `tidy_misses.tsv` exports the same list.\n',
        '| Rank | Function | Source | Lines | v1 | v2 | Added |', '| ---: | --- | --- | ---: | ---: | ---: | ---: |'])
    for i, f in enumerate(tidy_misses(functions, tidy_max_score, tidy_min_lines), 1):
        rows.append(f'| {i} | `{f.symbol}` (#{f.occurrence}) | [{f.path}:{f.line}](../{f.path}#L{f.line}) '
                    f'| {f.metrics["code_lines"]} | {f.metrics["v1_score"]} | {f.metrics["score"]} '
                    f'| {f.metrics["score"] - f.metrics["v1_score"]} |')
    eligible = sum(f.metrics['v1_score'] <= tidy_max_score and f.metrics['code_lines'] >= tidy_min_lines
                   and f.metrics['score'] > f.metrics['v1_score'] for f in functions)
    rows.append(f'\nEligible definitions: {eligible:,}; showing up to 30.\n')
    rows.extend(['## Queues, proof and reproduction\n\n'
        '`queue/<category>.tsv` retains the v1 columns, including symbol/occurrence, normalized anchor, '
        'evidence, category score and payoff = category score * max(1, distinct known callers). '
        'Each registry category gets a queue automatically, even if empty. Same-file/global unique '
        'resolution and ambiguity limits are unchanged from v1; callback, assembly and macro-expanded '
        f'edges are not inferred. {len(edges):,} resolved edges; {len(unresolved):,} unresolved spellings. '
        'Keep all trend categories, coverage and source digest; never compare v1 totals directly with v2 totals. '
        'Evidence spans describe the snapshot, not replay offsets. Inspect current symbols, anchors, '
        'shared headers and matching proof before source changes. This census is not a build gate.\n',
        'Run from the repository root (Python standard library, <=4 workers):\n\n```sh\n'
        'nice -n 10 python3 -m unittest discover -s tools/readability -p "test_*.py"\n'
        f'nice -n 10 python3 tools/readability/score.py --schema v2 --root . --revision {revision} '
        '--out out/readability-v2 --docs docs/READABILITY.md\n'
        f'nice -n 10 python3 tools/readability/score.py --schema v1 --root . --revision {revision} '
        '--out out/readability-v1\n```\n\n'
        'Outputs use sorted relative identities, no timestamps, and no absolute paths. --revision labels '
        'a snapshot; it does not check out that Git revision. Source symlinks are refused. '
        'Definitions in include/ are outside coverage. Unmatched conditional delimiters are reported '
        'and cause exit 1; invalid registry/input causes exit 2. Exit 0 requires no delimiter warnings. '
        'Worker count does not change output. Macro-generated functions, typedef-only pointer casts, '
        'type flow and semantic states/timers require further detectors and owner review.\n'])
    return '\n'.join(rows)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--schema', choices=('v2',), default='v2')
    parser.add_argument('--root', type=Path, default=Path('.'))
    parser.add_argument('--out', type=Path, default=Path('out/readability'))
    parser.add_argument('--workers', type=int, choices=range(1, 5), default=4)
    parser.add_argument('--revision', default='working-tree', help='Snapshot label; does not check out Git')
    parser.add_argument('--registry', type=Path, default=Path('ledger/readability_oddities.jsonl'))
    parser.add_argument('--docs', type=Path)
    parser.add_argument('--tidy-max-score', type=int, default=100)
    parser.add_argument('--tidy-min-lines', type=int, default=80)
    args = parser.parse_args(argv)
    root = args.root.resolve()
    if not (root / 'src').is_dir():
        parser.error('--root must contain src/')
    if args.tidy_max_score < 0 or args.tidy_min_lines < 1:
        parser.error('tidy score must be nonnegative and line threshold positive')
    try:
        registry = load_registry(args.registry if args.registry.is_absolute() else root / args.registry)
        sources, functions, edges, unresolved, duplicates = scan(root, registry, args.workers)
        out = args.out if args.out.is_absolute() else root / args.out
        write_outputs(out, args.revision, sources, functions, edges, unresolved, duplicates, registry,
                      args.tidy_max_score, args.tidy_min_lines)
        if args.docs:
            docs = args.docs if args.docs.is_absolute() else root / args.docs
            docs.parent.mkdir(parents=True, exist_ok=True)
            docs.write_text(render_docs(args.revision, sources, functions, edges, unresolved, registry,
                            args.tidy_max_score, args.tidy_min_lines), encoding='utf-8')
    except (OSError, ValueError) as exc:
        print('readability-v2: ' + str(exc), file=sys.stderr)
        return 2
    print(f'{SCHEMA}: {len(sources)} source files; {len(functions)} definitions; '
          f'{sum(f.metrics["score"] for f in functions)} weighted debt; '
          f'{sum(len(s.warnings) for s in sources)} delimiter warnings; registry {registry.sha256}')
    return 1 if any(s.warnings for s in sources) else 0


if __name__ == '__main__':
    sys.exit(main())
