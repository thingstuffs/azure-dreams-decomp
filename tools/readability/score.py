#!/usr/bin/env python3
"""Deterministic, dependency-free lexical readability census of physical src C definitions.

This measures source debt, not correctness or permission to alter matching C. No compiler,
ledger, build output, network access, or recursive work/ scan is required.
"""
from __future__ import annotations

import argparse
from bisect import bisect_right
from collections import Counter, defaultdict
from concurrent.futures import ProcessPoolExecutor
import csv
from dataclasses import dataclass, field
from functools import lru_cache
import hashlib
from pathlib import Path
import re
import sys
from typing import NamedTuple

SCHEMA = 'readability-v1'
CATEGORIES = ('offsets', 'casts', 'names', 'magic', 'structure')
WEIGHTS = dict(offset=8, cast=3, m2c=12, goto=8, address_self=5,
               address_ref=2, temporary=1, magic=2, depth=4, length=2)
# Directives (including continued macro bodies), comments and literals are distinct tokens.
LEX = re.compile(
    r'(?P<directive>^[ \t]*\#(?:[^\n\\]|\\[^\n]|\\\n)*)'
    r'|(?P<comment>/\*.*?\*/|//[^\n]*)'
    r'|(?P<literal>(?:u8|[LuU])?(?:"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'))'
    r'|(?P<number>(?:0[xX][0-9a-fA-F]+(?:\.[0-9a-fA-F]*)?(?:[pP][+-]?\d+)?'
    r'|(?:\d+\.\d*|\.\d+|\d+)(?:[eE][+-]?\d+)?)[uUlLfF]*)'
    r'|(?P<id>[A-Za-z_]\w*)'
    r'|(?P<op>>>=|<<=|>>=|->|\+\+|--|==|!=|<=|>=|&&|\|\||[+*/%&|^!-]=|<<|>>|[^\s])',
    re.M | re.S)
IDENT = re.compile(r'^[A-Za-z_]\w*$')
ADDRESS = re.compile(r'^(func_|D_|unk_)[A-Za-z0-9_]+$')
TEMP = re.compile(r'^(?:arg\d+|(?:var_|temp_)[A-Za-z0-9_]+|sp[0-9A-Fa-f]+)$')
QUALIFIERS = {'const', 'volatile', 'restrict', '__restrict', '__restrict__'}
BYTE_TYPES = {'u8', 's8', 'char', 'uint8_t', 'int8_t'}
CONTROL = {'if', 'for', 'while', 'switch', 'sizeof', '_Alignof', '__alignof__',
           'typeof', '__typeof__', 'return', 'case', '_Generic', '_Static_assert'}
ATTRIBUTES = {'__attribute__', '__attribute', '__declspec', 'asm', '__asm', '__asm__'}
NONCALL = CONTROL | ATTRIBUTES
CAST_TAIL = QUALIFIERS | {'*', ')'}
FUNCTION_POINTER = re.compile(r'(?:[A-Za-z_]\w* )+\( \*(?: (?:const|volatile))* \) '
                              r'\( [A-Za-z_\w*, ()]*\)')
ASSIGN = {'=', '+=', '-=', '*=', '/=', '%=', '&=', '|=', '^=', '<<=', '>>='}
COMPARE = {'==', '!=', '<', '>', '<=', '>='}


class Token(NamedTuple):
    value: str
    pos: int
    kind: str


@dataclass
class Function:
    path: str
    symbol: str
    occurrence: int
    line: int
    end_line: int
    static: bool
    metrics: dict
    calls: set = field(default_factory=set)
    callers: set = field(default_factory=set)
    anchor: str = ''
    header_style: str = 'ansi'

    @property
    def key(self):
        return f'{self.path}::{self.symbol}#{self.occurrence}'


@dataclass
class Source:
    path: str
    sha256: str
    byte_count: int
    functions: list
    warnings: list


def lex(text):
    return [Token(m[0], m.start(), m.lastgroup) for m in LEX.finditer(text)
            if m.lastgroup not in ('comment', 'directive')]


def pairs_of(tokens):
    """Pair delimiters, reporting rather than silently dropping malformed source."""
    stack, pairs, warnings = [], {}, []
    opening = {'(': ')', '[': ']', '{': '}'}
    closing = {')', ']', '}'}
    for i, token in enumerate(tokens):
        v = token.value
        if v in opening:
            stack.append(i)
        elif v in closing:
            if stack and opening[tokens[stack[-1]].value] == v:
                j = stack.pop()
                pairs[i] = j
                pairs[j] = i
            else:
                warnings.append((token.pos, f'unmatched {v}'))
    warnings.extend((tokens[i].pos, f'unclosed {tokens[i].value}') for i in stack)
    return pairs, warnings


def suffix_end(tokens, pairs, i):
    while i + 1 < len(tokens) and tokens[i].value in ATTRIBUTES and tokens[i + 1].value == '(':
        close = pairs.get(i + 1)
        if close is None:
            break
        i = close + 1
    return i


def knr_body(tokens, pairs, start, close):
    """Recognize C89 identifier-list parameters followed by their declarations."""
    args = [t.value for t in tokens[start + 1:close]]
    if not args or any(v != ',' and not IDENT.fullmatch(v) for v in args):
        return None
    names = set(args) - {','}
    i, declaration, declared = close + 1, [], set()
    while i < len(tokens):
        v = tokens[i].value
        if v == '{':
            return i if declared and not declaration else None
        if v in {'=', '}'}:
            return None
        if v == ';':
            matches = names.intersection(declaration)
            if not matches:
                return None
            declared.update(matches)
            declaration = []
        else:
            declaration.append(v)
        i += 1
    return None


def definitions(tokens, pairs):
    """Find ANSI and K&R definitions, including attributes and merged TUs.

    File-scope data/struct/enum initializer braces are skipped as a whole.
    Macro-generated definitions are not expanded.
    """
    i, start = 0, 0
    while i < len(tokens):
        v = tokens[i].value
        if v == '(' and i in pairs:
            close = pairs[i]
            after = suffix_end(tokens, pairs, close + 1)
            prefix = [t.value for t in tokens[start:i - 1]]
            candidate = i > 0 and tokens[i - 1].kind == 'id' and i - 1 >= start
            style = 'ansi'
            if candidate and (after >= len(tokens) or tokens[after].value != '{'):
                old_body = knr_body(tokens, pairs, i, close)
                if old_body is not None:
                    after, style = old_body, 'knr'
            if (candidate and tokens[i - 1].value not in NONCALL
                    and not set(prefix) & {'=', 'typedef'}
                    and after < len(tokens) and tokens[after].value == '{'
                    and after in pairs):
                end = pairs[after]
                yield start, i - 1, after, end, style
                i, start = end + 1, end + 1
                continue
            i = close + 1
            continue
        if v == '{' and i in pairs:
            i = pairs[i] + 1
            start = i
            continue
        if v in {';', '}'}:
            start = i + 1
        i += 1


def pointer_type(values):
    """Spelled pointer type, not `(a * b)` or a function-pointer declaration."""
    if '*' not in values:
        return False
    star = values.index('*')
    if star and all(IDENT.fullmatch(v) for v in values[:star]):
        if all(v == '*' or v in QUALIFIERS for v in values[star:]):
            return True
    # Abstract function pointer, e.g. (void (*)(int, char *)). Named declarators fail.
    return bool(FUNCTION_POINTER.fullmatch(' '.join(values)))


def operand_end(tokens, pairs, i):
    """One unary/postfix operand; enough to locate a byte-pointer + literal idiom."""
    n = len(tokens)
    while i < n and tokens[i].value in {'*', '&', '+', '-', '!', '~', '++', '--'}:
        i += 1
    if i >= n:
        return i
    if tokens[i].value == '(' and i in pairs:
        i = pairs[i] + 1
    elif tokens[i].kind in {'id', 'number', 'literal'}:
        i += 1
    else:
        return i
    while i < n:
        if tokens[i].value in {'[', '('} and i in pairs:
            i = pairs[i] + 1
        elif tokens[i].value in {'.', '->'} and i + 1 < n:
            i += 2
        else:
            break
    return i


def cast_sites(tokens, pairs):
    sites = []
    for i, token in enumerate(tokens):
        if token.value != '(' or i not in pairs:
            continue
        end = pairs[i]
        # Avoid joining long parenthesized expressions merely to reject them.
        if end - i > 48 or end + 1 >= len(tokens):
            continue
        if tokens[end - 1].value not in CAST_TAIL:
            continue
        values = [t.value for t in tokens[i + 1:end]]
        if not pointer_type(values):
            continue
        nxt = tokens[end + 1]
        if nxt.kind not in {'id', 'number', 'literal'} and nxt.value not in {'(', '*', '&', '+', '-', '~', '!'}:
            continue
        if i and tokens[i - 1].value in {'sizeof', '_Alignof', '__alignof__', 'typeof', '__typeof__'}:
            continue
        sites.append((i, end))
    return sites


def raw_offsets(tokens, pairs, casts):
    count = 0
    for start, end in casts:
        values = {t.value for t in tokens[start + 1:end]}
        if not values & BYTE_TYPES or sum(t.value == '*' for t in tokens[start + 1:end]) != 1:
            continue
        stop = operand_end(tokens, pairs, end + 1)
        # Permit redundant grouping around the cast's operand before the arithmetic.
        while stop < len(tokens) and tokens[stop].value == ')' and pairs.get(stop, start + 1) < start:
            stop += 1
        if stop >= len(tokens) or tokens[stop].value not in {'+', '-'}:
            continue
        stop += 1
        while stop < len(tokens) and tokens[stop].value in {'(', '+', '-'}:
            stop += 1
        if stop < len(tokens) and tokens[stop].kind == 'number':
            count += 1
    return count


@lru_cache(maxsize=8192)
def trivial_number(value):
    # Treat signed +/-1 and zero alike; unary signs are separate lexical tokens.
    try:
        v = re.sub(r'[uUlL]+$', '', value)
        if re.fullmatch(r'0[xX][0-9a-fA-F]+', v):
            return int(v, 16) in {0, 1}
        if re.fullmatch(r'0[0-7]+', v):
            return int(v, 8) in {0, 1}
        return float(re.sub(r'[fF]$', '', v)) in {0, 1}
    except ValueError:
        return False


def magic_sites(tokens, pairs):
    """Union of assignment RHS/comparison operand spans; count each literal once."""
    marked = [0] * (len(tokens) + 1)
    assign_stop = {';', ',', '{', '}'}
    compare_stop = assign_stop | {'&&', '||', '?', ':', 'return', 'case'} | ASSIGN

    def boundary(i, step, stops):
        while 0 <= i < len(tokens):
            v = tokens[i].value
            if v in stops:
                break
            if step == 1 and v in {'(', '['} and i in pairs:
                i = pairs[i] + 1
            elif step == -1 and v in {')', ']'} and i in pairs:
                i = pairs[i] - 1
            elif (step == 1 and v in {')', ']'}) or (step == -1 and v in {'(', '['}):
                break
            else:
                i += step
        return i

    for i, token in enumerate(tokens):
        if token.value in ASSIGN:
            # An initializer list belongs to the assignment as well.
            if i + 1 < len(tokens) and tokens[i + 1].value == '{' and i + 1 in pairs:
                end = pairs[i + 1] + 1
            else:
                end = boundary(i + 1, 1, assign_stop)
            marked[i + 1] += 1
            marked[end] -= 1
        elif token.value in COMPARE:
            start = boundary(i - 1, -1, compare_stop) + 1
            end = boundary(i + 1, 1, compare_stop)
            marked[start] += 1
            marked[end] -= 1
    active, count = 0, 0
    for i, token in enumerate(tokens):
        active += marked[i]
        if active and token.kind == 'number' and not trivial_number(token.value):
            count += 1
    return count


def direct_calls(tokens, pairs):
    calls = set()
    statement = 0
    for i, token in enumerate(tokens[:-1]):
        if token.value in {';', '{', '}'}:
            statement = i + 1
        if token.kind != 'id' or tokens[i + 1].value != '(' or token.value in NONCALL:
            continue
        if i and tokens[i - 1].value in {'.', '->'}:
            continue
        if i + 1 not in pairs:
            continue
        end = pairs[i + 1]
        prefix = [t.value for t in tokens[statement:i]]
        # Block-scope prototypes are declarations, not caller edges.
        if (end + 1 < len(tokens) and tokens[end + 1].value == ';' and prefix
                and all(IDENT.fullmatch(v) or v == '*' for v in prefix)
                and not set(prefix) & {'return', 'goto'}):
            continue
        if not token.value.startswith(('M2C_', 'ASM_')):
            calls.add(token.value)
    return calls


def analyze_source(path, data):
    text = data.decode('utf-8', 'surrogateescape')
    tokens = lex(text)
    pairs, problems = pairs_of(tokens)
    lines = [-1] + [m.start() for m in re.finditer('\n', text)]
    line = lambda pos: bisect_right(lines, pos)
    occurrences = Counter()
    functions = []
    for start, name, brace, end, style in definitions(tokens, pairs):
        symbol = tokens[name].value
        occurrences[symbol] += 1
        body = tokens[brace + 1:end]
        bpairs = {i - brace - 1: pairs[i] - brace - 1 for i in range(brace + 1, end) if i in pairs}
        casts = cast_sites(body, bpairs)
        ids = [t.value for t in tokens[name + 1:end] if t.kind == 'id']
        addr = Counter(v for v in ids if ADDRESS.fullmatch(v))
        temporary = Counter(v for v in ids if TEMP.fullmatch(v))
        depth = max_depth = 0
        for t in body:
            if t.value == '{':
                depth += 1
                max_depth = max(max_depth, depth)
            elif t.value == '}':
                depth -= 1
        code_lines = len({line(t.pos) for t in tokens[start:end + 1]})
        metrics = dict(
            raw_offsets=raw_offsets(body, bpairs, casts), pointer_casts=len(casts),
            m2c=sum(v.startswith('M2C_') for v in ids), gotos=ids.count('goto'),
            address_self=int(bool(ADDRESS.fullmatch(symbol))),
            address_func_refs=sum(n for v, n in addr.items() if v.startswith('func_')),
            address_data_refs=sum(n for v, n in addr.items() if v.startswith('D_')),
            address_unknown_refs=sum(n for v, n in addr.items() if v.startswith('unk_')),
            temporary_refs=sum(temporary.values()), temporary_unique=len(temporary),
            magic_numbers=magic_sites(body, bpairs), max_nesting=max_depth,
            lines=line(tokens[end].pos) - line(tokens[start].pos) + 1,
            code_lines=code_lines, tokens=end - start + 1)
        metrics['offsets_score'] = WEIGHTS['offset'] * metrics['raw_offsets']
        metrics['casts_score'] = WEIGHTS['cast'] * metrics['pointer_casts']
        metrics['names_score'] = (WEIGHTS['address_self'] * metrics['address_self']
                                  + WEIGHTS['address_ref'] * sum(addr.values())
                                  + WEIGHTS['temporary'] * metrics['temporary_refs'])
        metrics['magic_score'] = WEIGHTS['magic'] * metrics['magic_numbers']
        metrics['structure_score'] = (WEIGHTS['m2c'] * metrics['m2c'] + WEIGHTS['goto'] * metrics['gotos']
                                      + WEIGHTS['depth'] * max(0, max_depth - 2)
                                      + WEIGHTS['length'] * max(0, (code_lines - 1) // 40))
        metrics['score'] = sum(metrics[f'{c}_score'] for c in CATEGORIES)
        anchor = hashlib.sha256('\0'.join(t.value for t in tokens[start:end + 1]).encode(
            'utf-8', 'surrogateescape')).hexdigest()
        functions.append(Function(path, symbol, occurrences[symbol], line(tokens[name].pos),
                                  line(tokens[end].pos),
                                  any(t.value == 'static' for t in tokens[start:name]),
                                  metrics, direct_calls(body, bpairs), anchor=anchor, header_style=style))
    return Source(path, hashlib.sha256(data).hexdigest(), len(data), functions,
                  [(line(pos), warning) for pos, warning in problems])


def resolve_calls(functions):
    by_symbol = defaultdict(list)
    for f in functions:
        by_symbol[f.symbol].append(f)
    edges, unresolved = [], []
    for f in functions:
        for name in sorted(f.calls):
            targets = by_symbol.get(name, [])
            local = [g for g in targets if g.path == f.path]
            visible = local or [g for g in targets if not g.static]
            if len(visible) == 1:
                target = visible[0]
                if target.key != f.key:
                    target.callers.add(f.key)
                edges.append(dict(caller=f.key, callee=target.key))
            else:
                unresolved.append(dict(caller=f.key, symbol=name,
                                       reason='ambiguous' if visible else 'external_or_indirect',
                                       candidates=len(visible)))
    return edges, unresolved


def scan_path(item):
    root, path = item
    if path.is_symlink():
        raise ValueError('source symlink refused: ' + path.relative_to(root).as_posix())
    return analyze_source(path.relative_to(root).as_posix(), path.read_bytes())


def scan(root, workers=1):
    # Deliberately walk src only. Headers physically in src are included once, not expanded.
    paths = sorted(p for suffix in ('*.c', '*.h') for p in (root / 'src').rglob(suffix))
    items = [(root, p) for p in paths]
    if workers == 1:
        sources = [scan_path(item) for item in items]
    else:
        # map preserves path order; all caller resolution/output happens in the parent.
        with ProcessPoolExecutor(max_workers=workers) as pool:
            sources = list(pool.map(scan_path, items, chunksize=16))
    functions = [f for source in sources for f in source.functions]
    edges, unresolved = resolve_calls(functions)
    return sources, functions, edges, unresolved


METRICS = ('raw_offsets', 'pointer_casts', 'm2c', 'gotos', 'address_self', 'address_func_refs',
           'address_data_refs', 'address_unknown_refs', 'temporary_refs', 'temporary_unique',
           'magic_numbers', 'max_nesting', 'lines', 'code_lines', 'tokens')
SCORES = tuple(c + '_score' for c in CATEGORIES) + ('score',)


def write_tsv(path, columns, rows):
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open('w', encoding='utf-8', newline='') as stream:
        writer = csv.DictWriter(stream, fieldnames=columns, delimiter='\t', lineterminator='\n')
        writer.writeheader()
        writer.writerows(rows)


def summarize(sources, functions, key):
    groups = defaultdict(list)
    file_counts = Counter(key(s.path) for s in sources)
    for f in functions:
        groups[key(f.path)].append(f)
    for group in sorted(file_counts):
        fs = groups[group]
        row = dict(group=group, files=file_counts[group], functions=len(fs))
        for metric in METRICS + SCORES:
            row[metric] = (max((f.metrics[metric] for f in fs), default=0) if metric == 'max_nesting'
                           else sum(f.metrics[metric] for f in fs))
        yield row


def explain(f):
    m = f.metrics
    descriptions = [('raw_offsets', 'byte offsets'), ('pointer_casts', 'pointer casts'),
                    ('m2c', 'M2C macros'), ('gotos', 'gotos'),
                    ('address_self', 'address name'), ('address_func_refs', 'func_ uses'),
                    ('address_data_refs', 'D_ uses'), ('address_unknown_refs', 'unk_ uses'),
                    ('temporary_refs', 'temporary names'), ('magic_numbers', 'magic literals')]
    parts = [f'{m[k]} {label}' for k, label in descriptions if m[k]]
    if m['max_nesting'] > 2:
        parts.append(f"nesting {m['max_nesting']}")
    if m['code_lines'] > 40:
        parts.append(f"{m['code_lines']} code lines")
    return '; '.join(parts) or 'no weighted debt'


def write_outputs(out, revision, sources, functions, edges, unresolved):
    columns = ('function_id', 'path', 'symbol', 'occurrence', 'line', 'end_line', 'static',
               'known_callers', 'anchor_sha256', 'header_style') + METRICS + SCORES
    rows = []
    for f in functions:
        row = dict(function_id=f.key, path=f.path, symbol=f.symbol, occurrence=f.occurrence,
                   line=f.line, end_line=f.end_line, static=int(f.static), known_callers=len(f.callers),
                   anchor_sha256=f.anchor, header_style=f.header_style, **f.metrics)
        rows.append(row)
    write_tsv(out / 'scores.tsv', columns, rows)
    for label, key in [('files', lambda p: p), ('folders', lambda p: str(Path(p).parent)),
                       ('subsystems', lambda p: p.split('/')[1])]:
        write_tsv(out / f'{label}.tsv', ('group', 'files', 'functions') + METRICS + SCORES,
                  summarize(sources, functions, key))
    write_tsv(out / 'coverage.tsv', ('path', 'sha256', 'bytes', 'definitions', 'warnings'),
              (dict(path=s.path, sha256=s.sha256, bytes=s.byte_count, definitions=len(s.functions),
                    warnings=len(s.warnings)) for s in sources))
    write_tsv(out / 'parse_warnings.tsv', ('path', 'line', 'reason'),
              (dict(path=s.path, line=line, reason=reason) for s in sources for line, reason in s.warnings))
    write_tsv(out / 'calls.tsv', ('caller', 'callee'), edges)
    write_tsv(out / 'unresolved_calls.tsv', ('caller', 'symbol', 'reason', 'candidates'), unresolved)
    for category in CATEGORIES:
        ranked = sorted((f for f in functions if f.metrics[category + '_score']),
                        key=lambda f: (-f.metrics[category + '_score'] * max(1, len(f.callers)),
                                       -f.metrics[category + '_score'], f.key))
        write_tsv(out / 'queue' / f'{category}.tsv',
                  ('rank', 'function_id', 'path', 'symbol', 'occurrence', 'line', 'anchor_sha256',
                   'category_score', 'known_callers', 'caller_multiplier', 'payoff', 'total_score', 'evidence'),
                  (dict(rank=i, function_id=f.key, path=f.path, symbol=f.symbol, occurrence=f.occurrence,
                        line=f.line, anchor_sha256=f.anchor, category_score=f.metrics[category + '_score'],
                        known_callers=len(f.callers), caller_multiplier=max(1, len(f.callers)),
                        payoff=f.metrics[category + '_score'] * max(1, len(f.callers)),
                        total_score=f.metrics['score'], evidence=explain(f)) for i, f in enumerate(ranked, 1)))
    digest = hashlib.sha256(''.join(f'{s.path}\0{s.sha256}\n' for s in sources).encode()).hexdigest()
    write_tsv(out / 'metadata.tsv', ('key', 'value'),
              [dict(key=k, value=v) for k, v in dict(schema=SCHEMA, revision=revision,
               source_sha256=digest, source_files=len(sources), c_files=sum(s.path.endswith('.c') for s in sources),
               header_files=sum(s.path.endswith('.h') for s in sources), functions=len(functions),
               knr_definitions=sum(f.header_style == 'knr' for f in functions),
               source_bytes=sum(s.byte_count for s in sources),
               zero_definition_files=sum(not s.functions for s in sources),
               parse_warnings=sum(len(s.warnings) for s in sources),
               resolved_edges=len(edges), unresolved_calls=len(unresolved),
               weights=','.join(f'{k}:{v}' for k, v in WEIGHTS.items())).items()])
    write_tsv(out / 'trend.tsv', ('schema', 'revision', 'category', 'weighted_debt'),
              (dict(schema=SCHEMA, revision=revision, category=c,
                    weighted_debt=sum(f.metrics[c + '_score'] for f in functions)) for c in CATEGORIES))


def render_docs(revision, sources, functions, edges, unresolved):
    subsystem_rows = list(summarize(sources, functions, lambda p: p.split('/')[1]))
    totals = {c: sum(f.metrics[c + '_score'] for f in functions) for c in CATEGORIES}
    rows = [f'# Readability census\n\nBaseline: `{revision}`; metric schema: `{SCHEMA}`. '
            f'{len(sources):,} physical source files (.c/.h), {len(functions):,} function definitions, '
            f'{sum(s.byte_count for s in sources):,} source bytes.\n',
            'This is a lexical source census for choosing future work. Scores describe visible debt; '
            'they do not prove that a literal is unexplained, a cast removable, or a rewrite safe for matching. '
            'Every physical `.c`/`.h` file under `src/` is read once, including merged translation units, auxiliary C and local headers. '
            'A function is keyed by relative path, symbol and occurrence, so duplicate overlay names and '
            'conditional definitions remain separate. Declarations, function-pointer variables and data '
            'initializers are excluded. Comments, string/character contents and preprocessor directive '
            'bodies do not contribute.\n',
            '## Measurements and weights\n\n'
            '| Measure | Definition | Score |\n| --- | --- | ---: |\n'
            '| Byte offsets | Spelled byte-pointer cast (`u8 *`, `s8 *`, `char *`, `int8_t *`, `uint8_t *`) '
            'followed by one operand and addition/subtraction of a numeric literal; includes '
            '`(u8 *)p + 0x24` and `((u8 *)p) - 0x20` | 8 each |\n'
            '| Pointer casts | Explicit pointer casts in bodies, including initializers and abstract '
            'function-pointer casts; declarations and `sizeof(type *)` excluded | 3 each |\n'
            '| M2C macros | Identifier occurrences beginning `M2C_`, in signature/body | 12 each |\n'
            '| Gotos | `goto` keyword occurrences | 8 each |\n'
            '| Address names | Self named `func_`, `D_`, `unk_`; signature/body identifier uses with those '
            'prefixes, including unknown offset fields | 5 self; 2 per use |\n'
            '| Temporary names | Exact `arg` + digits, `var_...`, `temp_...`, or `sp` + hex digits; '
            'occurrences, including declarations/parameters; unique count also exported | 1 per use |\n'
            '| Magic literals | Numeric occurrences in assignment RHS or comparison operands, including '
            'nested expressions; overlaps counted once; 0 and +/-1 (including suffixes/floats) excluded | 2 each |\n'
            '| Nesting | Maximum brace depth inside the function, outer body excluded | 4 per level above 2 |\n'
            '| Length | Physical lines, token-bearing lines, token count; only token-bearing lines scored '
            '| 2 per started block of 40 lines after the first 40 |\n\n'
            'Total score is the sum of five category scores. `offsets` and `casts` use their own weights; '
            '`names` combines address and temporary names; `magic` counts magic literals; `structure` '
            'combines M2C, gotos, nesting and length. Overlap between categories is intentional: an offset '
            'cast with a literal can contribute to three categories. Brace nesting includes local structs '
            'and initializer lists, and does not measure unbraced control nesting. Magic detection is '
            'syntactic: constants in local named initializers are included, standalone return values, '
            'case labels, array bounds on the left of assignments and standalone call arguments are '
            'excluded. No semantic naming recommendation follows from these counts.\n',
            '## Subsystems\n\n| Subsystem | Files | Definitions | Offsets | Casts | Names | Magic | Structure | Total |\n'
            '| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |']
    for r in subsystem_rows:
        values = [r['files'], r['functions']] + [r[c + '_score'] for c in CATEGORIES] + [r['score']]
        rows.append('| ' + r['group'] + ' | ' + ' | '.join(f'{v:,}' for v in values) + ' |')
    rows.append('\nSubsystem values are weighted debt totals. `files.tsv` and `folders.tsv` give the '
                'same aggregation at file and immediate parent-folder level; all files, including those '
                'without definitions, appear in coverage/file summaries. Maximum nesting aggregates '
                'with max; other numeric measures sum (temporary unique counts are per-function sums).\n')
    rows.append('## Fifty hardest functions\n\nRanked by total weighted score, ties by function key. '
                'Locations are for navigation; replay/queue identity uses the symbol and occurrence.\n\n'
                '| Rank | Function | Source | Score | What makes it hard |\n| ---: | --- | --- | ---: | --- |')
    for i, f in enumerate(sorted(functions, key=lambda f: (-f.metrics['score'], f.key))[:50], 1):
        rows.append(f'| {i} | `{f.symbol}` (#{f.occurrence}) | '
                    f'[{f.path}:{f.line}](../{f.path}#L{f.line}) | {f.metrics["score"]:,} | {explain(f)} |')
    rows.append('\n## Work queues and caller limits\n\n'
                'Each `queue/{offsets,casts,names,magic,structure}.tsv` contains all definitions with '
                'debt in that category. Payoff is `category_score * max(1, known_callers)`, an optimistic '
                'score reduction times distinct source callers. It is a prioritization estimate, not a '
                'prediction of achievable reduction. Ties use category score then function key. '
                'Repeated calls from one definition count once; recursion does not boost its own count. '
                'A unique same-file target wins, otherwise only a unique non-static global definition '
                'resolves. Duplicate overlay symbols and conditional variants remain ambiguous. '
                'Function-pointer/address-taking edges, alias expansion, assembly calls and preprocessor '
                'macro expansion are not resolved. Local callbacks whose spelling coincides with a global '
                'function can be overcounted. `calls.tsv` exposes the edges and `unresolved_calls.tsv` '
                f'exposes {len(unresolved):,} unresolved spellings; {len(edges):,} edges resolve. '
                'A token-normalized definition hash anchors each queue entry. Before editing, inspect '
                'the current symbol, callers, owning header and proof requirements. Names need evidence; '
                'offset/cast fixes should retype declarations rather than add use-site casts.\n')
    rows.append('## Trend per landing\n\n'
                'Track the five **total weighted category debts** from `trend.tsv`, in this order: '
                '`offsets`, `casts`, `names`, `magic`, `structure`. Lower is better; also retain metadata '
                'coverage, source digest and schema so deleted/missed functions cannot masquerade as '
                'readability improvements. Do not divide by source length: adding code must not dilute debt. '
                'Use the same schema and weights on both sides of a landing, report five signed deltas, '
                'and inspect changed-function rows when coverage changes. This metric is not a build gate.\n\n'
                '| Category | Baseline weighted debt |\n| --- | ---: |')
    rows.extend(f'| {c} | {totals[c]:,} |' for c in CATEGORIES)
    rows.append('\n## Reproduce and limitations\n\n'
                'Run from the repository root (Python 3 standard library only):\n\n```sh\n'
                'nice -n 10 python3 -m unittest discover -s tools/readability -p "test_*.py"\n'
                f'nice -n 10 python3 tools/readability/score.py --schema v1 --root . --revision {revision} '
                '--out out/readability --docs docs/READABILITY.md\n```\n\n'
                'The CLI uses at most four workers (override with `--workers 1` for serial use). Outputs have stable ordering and contain no timestamps or absolute paths. The source '
                'digest hashes sorted relative paths and file hashes; metadata and coverage make the '
                'snapshot auditable without a build. The scanner handles ANSI/K&R definitions, implicit int returns and GNU '
                'attributes. It does not expand macro-generated function definitions. Source symlinks '
                'are refused. Includes are not expanded; definitions in headers outside `src/` are outside '
                'this source census. Both sides of conditional compilation are textually counted; '
                'there is no claim that all are linked together. Branch-dependent unmatched delimiters '
                'are reported in `parse_warnings.tsv` and require review. Pointer casts through typedefs '
                'without a spelled `*`, variable byte offsets, scalar casts, field names without the '
                'listed prefixes and numeric literals outside assignments/comparisons are outside the '
                'metric. This deliberately conservative lexer is not a C type checker.\n')
    return '\n'.join(rows)


def main_v1(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--schema', choices=('v1',), default='v1')
    parser.add_argument('--root', type=Path, default=Path('.'))
    parser.add_argument('--out', type=Path, default=Path('out/readability'))
    parser.add_argument('--workers', type=int, choices=range(1, 5), default=4)
    parser.add_argument('--revision', default='working-tree', help='Snapshot label, not a Git checkout operation')
    parser.add_argument('--docs', type=Path, help='Optionally write the generated methodology and census document')
    args = parser.parse_args(argv)
    root = args.root.resolve()
    if not (root / 'src').is_dir():
        parser.error('--root must contain src/')
    sources, functions, edges, unresolved = scan(root, args.workers)
    out = args.out if args.out.is_absolute() else root / args.out
    write_outputs(out, args.revision, sources, functions, edges, unresolved)
    if args.docs:
        docs = args.docs if args.docs.is_absolute() else root / args.docs
        docs.parent.mkdir(parents=True, exist_ok=True)
        docs.write_text(render_docs(args.revision, sources, functions, edges, unresolved), encoding='utf-8')
    print(f'{SCHEMA}: {len(sources)} source files; {len(functions)} definitions; '
          f'{sum(f.metrics["score"] for f in functions)} weighted debt; '
          f'{sum(len(s.warnings) for s in sources)} delimiter warnings')
    return 1 if any(s.warnings for s in sources) else 0


def main(argv=None):
    """Keep v1's implementation/output frozen; v2 owns the extended census."""
    selector = argparse.ArgumentParser(add_help=False)
    selector.add_argument('--schema', choices=('v1', 'v2'), default='v2')
    selected, _ = selector.parse_known_args(argv)
    if selected.schema == 'v1':
        return main_v1(argv)
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    import v2
    return v2.main(argv)


if __name__ == '__main__':
    sys.exit(main())
