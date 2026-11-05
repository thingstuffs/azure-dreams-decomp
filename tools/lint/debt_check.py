#!/usr/bin/env python3
"""Per-function lexical readability debt ratchet; no compiler or game build needed."""
from __future__ import annotations

import argparse
from collections import Counter
import csv
import json
from pathlib import Path
import re
import sys

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS / 'readability'))
import score as c

SCHEMA = 3
CLASSES = ('local_externs', 'generated_layouts', 'm2c_macros', 'goto',
           'volatile', 'pointer_casts', 'sign_views')
GENERATED = re.compile(r'^S_(?:func_)?[0-9A-Fa-f]{8}(?:_\w+)?$')
# A marker annotates one adjacent statement, declaration or braced control arm.
# It never exempts the enclosing function just because it contains a marker.
MARKER = re.compile(r'^/\* BYTES: [^\n]+ \*/$')
OTHER_VIEW = {'whole', 'halves', 'signed_bytes'}
GENERIC_INDEX = re.compile(r'(?:(?:->|\.)\s*(?:b|sb|h|sh|w|sw|bytes|Ints)|\bInts)\s*\[')
ADDRESS_NAME = re.compile(r'[0-9A-Fa-f]{8}')
INTEGER_TYPES = {
    's8': ('signed', 8), 'u8': ('unsigned', 8),
    's16': ('signed', 16), 'u16': ('unsigned', 16),
    's32': ('signed', 32), 'u32': ('unsigned', 32),
    's64': ('signed', 64), 'u64': ('unsigned', 64),
    'int8_t': ('signed', 8), 'uint8_t': ('unsigned', 8),
    'int16_t': ('signed', 16), 'uint16_t': ('unsigned', 16),
    'int32_t': ('signed', 32), 'uint32_t': ('unsigned', 32),
    'int64_t': ('signed', 64), 'uint64_t': ('unsigned', 64),
    'short': ('signed', 16), 'int': ('signed', 32),
    'unsigned short': ('unsigned', 16), 'unsigned int': ('unsigned', 32),
    'signed short': ('signed', 16), 'signed int': ('signed', 32),
}


def union_fields(tokens, pairs, opening):
    """Simple immediate members of one union; nested records are separate sites."""
    close = pairs[opening]
    fields, start, i = [], opening + 1, opening + 1
    while i < close:
        if tokens[i].value in {'{', '(', '['} and i in pairs:
            i = pairs[i] + 1
            continue
        if tokens[i].value == ';':
            part = tokens[start:i]
            declarator_end = next((j for j, t in enumerate(part) if t.value == '['), len(part))
            ids = [j for j, token in enumerate(part[:declarator_end]) if token.kind == 'id']
            function_pointer = next((j + 2 for j in range(len(part) - 3)
                                     if [t.value for t in part[j:j + 4]] == ['(', '*', part[j + 2].value, ')']
                                     and part[j + 2].kind == 'id'), None)
            simple = not any(t.value in {'{', '}', '(', ')', ','} for t in part)
            if len(ids) >= 2 and (simple or function_pointer is not None):
                name_index = function_pointer if function_pointer is not None else ids[-1]
                name = part[name_index].value
                type_words = [t.value for t in part[:name_index] if t.kind == 'id'
                              and t.value not in {'const', 'volatile', 'restrict'}]
                if type_words:
                    fields.append((name, ' '.join(type_words),
                                   tuple(t.value for t in part[:name_index] + part[name_index + 1:])))
            start = i + 1
        i += 1
    return fields


def union_definition_count(tokens, pairs):
    """Count braced union definitions, including pointer and nested unions."""
    count = 0
    for i, token in enumerate(tokens):
        if token.value != 'union':
            continue
        opening = i + 1
        if opening < len(tokens) and tokens[opening].kind == 'id':
            opening += 1
        if opening < len(tokens) and tokens[opening].value == '{' and opening in pairs:
            count += 1
    return count


def generic_index_views(text):
    """Count indexed anonymous scratch/record views in code, not comments or literals."""
    clean = c.LEX.sub(lambda m: re.sub(r'[^\n]', ' ', m.group())
                      if m.lastgroup in {'comment', 'directive', 'literal'} else m.group(), text)
    return len(GENERIC_INDEX.findall(clean))


def check_union_inventory(current, tracked, baseline):
    """Validate physical definitions, ledger history, and the no-growth baseline."""
    current_ids = [row['id'] for row in current]
    tracked_ids = [row['id'] for row in tracked]
    baseline_ids = baseline.get('ids')
    problems = []
    if len(set(current_ids)) != len(current_ids):
        problems.append('census contains duplicate ids')
    if len(set(tracked_ids)) != len(tracked_ids):
        problems.append('ledger contains duplicate ids')
    if (type(baseline.get('count')) is not int or baseline['count'] < 0
            or not isinstance(baseline_ids, list)
            or any(not isinstance(id_, str) for id_ in baseline_ids)):
        return problems + ['invalid union baseline count or ids']
    if len(baseline_ids) != baseline['count']:
        problems.append(f'union baseline ids length {len(baseline_ids)} != count {baseline["count"]}')
    if len(set(baseline_ids)) != len(baseline_ids):
        problems.append('union baseline contains duplicate ids')
    live = set(current_ids)
    baseline_set = set(baseline_ids)
    tracked_by_id = {row['id']: row for row in tracked}
    for missing in sorted(live - set(tracked_ids)):
        problems.append(f'untracked union: {missing}')
    for row in current:
        old = tracked_by_id.get(row['id'])
        if old and old.get('members') != row['members']:
            problems.append(f'stale union members: {row["id"]}')
        if old and old.get('status') == 'retired':
            problems.append(f'retired union definition still present: {row["id"]}' if row['id'] in baseline_set
                            else f'retired union reintroduced: {row["id"]}')
    if len(current) > baseline['count']:
        problems.append(f'union count {len(current)} > baseline {baseline["count"]}')
    for row in current:
        if row['id'] not in baseline_set:
            old = tracked_by_id.get(row['id'], {})
            if old.get('status') != 'proven' or 'UNION:' not in old.get('evidence', ''):
                problems.append(f'new union lacks same-object proof: {row["id"]}')
    for row in tracked:
        status = row.get('status')
        if status not in {'proven', 'unproven', 'retire_candidate', 'retired'}:
            problems.append(f'bad union status: {row["id"]}')
        if row['id'] not in live and status != 'retired':
            problems.append(f'orphan non-retired ledger row: {row["id"]}')
    return problems


def union_sites(rel, text, tokens=None, pairs=None):
    """Signedness unions and bad-label sites in one physical C/header file."""
    tokens = c.lex(text) if tokens is None else tokens
    pairs = c.pairs_of(tokens)[0] if pairs is None else pairs
    signedness, bad = [], []
    identities = Counter()
    for i, token in enumerate(tokens):
        if token.value != 'union':
            continue
        opening = i + 1
        if opening < len(tokens) and tokens[opening].kind == 'id':
            opening += 1
        if opening >= len(tokens) or tokens[opening].value != '{' or opening not in pairs:
            continue
        fields = union_fields(tokens, pairs, opening)
        if not fields:
            continue
        typed = [(name, INTEGER_TYPES.get(type_name), type_tokens)
                 for name, type_name, type_tokens in fields]
        widths = {(kind, width) for _, pair, _ in typed if pair for kind, width in [pair]}
        if any(('signed', width) in widths and ('unsigned', width) in widths
               for _, width in widths):
            signedness.append(text.count('\n', 0, token.pos) + 1)
        reasons = []
        for name, pair, type_tokens in typed:
            if name == 's' and pair and pair[0] == 'unsigned':
                reasons.append('unsigned_s')
            if name == 'u' and pair and pair[0] == 'signed':
                reasons.append('signed_u')
            if name in {'s', 'u'} and '*' in type_tokens and pair is None:
                reasons.append('pointer_' + name)
        types = [type_tokens for _, _, type_tokens in typed]
        if len(types) != len(set(types)):
            reasons.append('duplicate_type')
        pointer_types = [type_tokens for _, _, type_tokens in typed if '*' in type_tokens]
        if len(pointer_types) > 1 and len(set(pointer_types)) > 1:
            reasons.append('pointer_pun')
        close = pairs[opening]
        field_name = tokens[close + 1].value if close + 1 < len(tokens) and tokens[close + 1].kind == 'id' else '<anonymous>'
        # The trailing field name survives member relabelling and line shifts.
        identities[field_name] += 1
        if reasons:
            site = f'{rel}::{field_name}#{identities[field_name]}'
            bad.append(dict(site=site, file=rel, line=text.count('\n', 0, token.pos) + 1,
                            reasons=sorted(set(reasons))))
    return signedness, bad


def typedef_view_sites(tokens, pairs):
    """Simple braced struct/union typedefs; return alias and declaration span."""
    out = []
    for i, token in enumerate(tokens):
        if token.value != 'typedef' or i + 1 >= len(tokens) or tokens[i + 1].value not in {'struct', 'union'}:
            continue
        opening = i + 2
        if opening < len(tokens) and tokens[opening].kind == 'id':
            opening += 1
        if opening >= len(tokens) or tokens[opening].value != '{' or opening not in pairs:
            continue
        after = c.suffix_end(tokens, pairs, pairs[opening] + 1)
        if after + 1 < len(tokens) and tokens[after].kind == 'id' and tokens[after + 1].value == ';':
            out.append((tokens[after].value, tokens[i + 1].value, i, after + 2))
    return out


def end_of_site(tokens, pairs, start):
    """Exclusive end of the following statement, declaration, or control arm."""
    i = start
    while i < len(tokens):
        v = tokens[i].value
        if v == '{' and i in pairs:
            i = pairs[i] + 1
            # Include the condition of a do/while(0) statement, or struct alias.
            if tokens[start].value != 'do' and tokens[start].value not in {'typedef', 'struct', 'union', 'enum'}:
                return i
        elif v in {'(', '['} and i in pairs:
            i = pairs[i] + 1
        elif v == ';':
            return i + 1
        elif v == '}':
            return i
        else:
            i += 1
    return i


def exemptions(text, tokens, pairs):
    """Map exact BYTES comments to token spans; trailing comments bind backwards."""
    spans, errors = [], []
    positions = [t.pos for t in tokens]
    from bisect import bisect_left
    for m in c.LEX.finditer(text):
        if m.lastgroup != 'comment' or not re.search(r'\bBYTES:', m[0]):
            continue
        if not MARKER.fullmatch(m[0]):
            errors.append('BYTES marker must be /* BYTES: <one-line reason> */')
            continue
        following = bisect_left(positions, m.end())
        line_start = text.rfind('\n', 0, m.start()) + 1
        previous = following - 1
        if previous >= 0 and tokens[previous].pos >= line_start and tokens[previous].value == ':':
            # A trailing case/default marker describes the label value itself.
            start = previous
            while start > 0 and tokens[start].value not in {'case', 'default', ';', '{', '}'}:
                start -= 1
            end = following
        elif previous >= 0 and tokens[previous].pos >= line_start and tokens[previous].value == ';':
            # Locate the start of this complete preceding statement. The marker
            # is on its line; declarations/expressions may begin on earlier lines.
            start = previous
            while start > 0:
                v = tokens[start - 1].value
                if v in {';', '{', '}'}:
                    break
                if v in {')', ']'} and start - 1 in pairs:
                    start = pairs[start - 1]
                else:
                    start -= 1
            end = following
        else:
            start = following
            end = end_of_site(tokens, pairs, start)
        if start == end:
            errors.append('BYTES marker has no adjacent code site')
        else:
            spans.append((start, end))
    return spans, errors


def declaration_sites(tokens, pairs, definitions):
    """TU-local extern declarations, including unqualified file-scope prototypes.

    Explicit externs at block scope also count. Static/typedef declarations and
    actual definitions are excluded. This is a lexical ownership candidate,
    not proof of which folder owns the declaration.
    """
    sites = set()
    headers = {i for start, name, body, end, style in definitions for i in range(start, body)}
    for i, t in enumerate(tokens):
        if t.value != 'extern' or i in headers:
            continue
        # An initialized extern object is a definition, as is an extern
        # function body. Mixed declarations count once if any declarator
        # still needs a header declaration: extern int declared, defined = 1;
        j, initialized, candidate = i + 1, False, False
        while j < len(tokens):
            value = tokens[j].value
            if value in {',', ';'}:
                candidate |= not initialized
                initialized = False
                if value == ';':
                    break
            elif value == '=':
                initialized = True
            elif value in {'(', '[', '{'} and j in pairs:
                j = pairs[j]
            j += 1
        if candidate:
            sites.add(i)
    function_ranges = {start: end for start, name, body, end, style in definitions}
    i, start = 0, 0
    while i < len(tokens):
        if i in function_ranges:
            i = function_ranges[i] + 1
            start = i
            continue
        value = tokens[i].value
        if value == '{' and i in pairs:
            i = pairs[i] + 1
            continue
        if value == ';':
            statement = tokens[start:i]
            values = {t.value for t in statement}
            if not values & {'static', 'typedef', 'extern', '='}:
                for j in range(start + 2, i):
                    if (tokens[j].value == '(' and tokens[j - 1].kind == 'id'
                            and tokens[j - 1].value not in c.NONCALL
                            and tokens[j + 1].value != '*'
                            and j in pairs and pairs[j] < i):
                        sites.add(start)
                        break
            start = i + 1
        i += 1
    return sorted(sites)


# ------------------------------------------------------------------ opt-in: casts hidden in file-local macros
# Report only (--macro-casts): never part of CLASSES, the ratchet or the baseline.  score.lex drops
# preprocessor directives, so a cast written in a #define body is counted nowhere; this mode expands every
# use of a file-local macro (parameters substituted by the argument text, nested file-local macros followed
# to MACRO_DEPTH) and counts the pointer casts the body contributes at that use site.  Casts spelled in the
# arguments are not counted again (the argument text is already counted at the use site).
DEFINE = re.compile(r'^[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)(\(([^)]*)\))?(.*)$', re.S)
UNDEF = re.compile(r'^[ \t]*#[ \t]*undef[ \t]+([A-Za-z_]\w*)')
INCLUDE = re.compile(r'^[ \t]*#[ \t]*include[ \t]+[<"]([^>"]+)[>"]')
MACRO_DEPTH = 8


def macro_events(text):
    """[(position, name, params or None, body)] in file order; body None for #undef."""
    events = []
    for m in c.LEX.finditer(text):
        if m.lastgroup != 'directive':
            continue
        d = DEFINE.match(m[0])
        if d:
            params = None if d.group(2) is None else [p.strip() for p in d.group(3).split(',') if p.strip()]
            events.append((m.start(), d.group(1), params, d.group(4).replace('\\\n', ' ').strip()))
        else:
            u = UNDEF.match(m[0])
            if u:
                events.append((m.start(), u.group(1), None, None))
    return events


def directive_events(text):
    """Macro and include directives in lexical order (without evaluating #if)."""
    for m in c.LEX.finditer(text):
        if m.lastgroup != 'directive':
            continue
        directive = m[0]
        match = DEFINE.match(directive)
        if match:
            params = None if match.group(2) is None else [p.strip() for p in match.group(3).split(',') if p.strip()]
            yield m.start(), 'define', match.group(1), params, match.group(4).replace('\\\n', ' ').strip()
            continue
        match = UNDEF.match(directive)
        if match:
            yield m.start(), 'undef', match.group(1), None, None
            continue
        match = INCLUDE.match(directive)
        if match:
            yield m.start(), 'include', match.group(1), None, None


def include_macro_events(root, source, text, cache):
    """Header and local macro events at source positions, following reachable include/ headers.

    Conditional compilation is not evaluated: this is a lexical exposure report. Include
    guards and repeated includes are handled by visiting each header once per translation unit.
    Headers outside include/ and headers over 4 MiB are never read.
    """
    include_root = (root / 'include').resolve()
    seen, events = set(), []

    def resolve_header(current, name):
        for candidate in (current.parent / name, include_root / name):
            path = candidate.resolve()
            if path.is_relative_to(include_root) and path.is_file():
                return path
        return None

    def visit(path, source_pos):
        if path in seen:
            return
        seen.add(path)
        if path.stat().st_size > 4 * 1024 * 1024:
            raise ValueError('header over 4 MiB: ' + str(path))
        if path not in cache:
            cache[path] = list(directive_events(path.read_text()))
        for _, kind, name, params, body in cache[path]:
            if kind == 'include':
                nested = resolve_header(path, name)
                if nested is not None:
                    visit(nested, source_pos)
            else:
                events.append((source_pos, name, params, body, True))

    for pos, kind, name, params, body in directive_events(text):
        if kind == 'include':
            header = resolve_header(source, name)
            if header is not None:
                visit(header, pos)
        else:
            events.append((pos, name, params, body, False))
    return events


def lexical_casts(text):
    tokens = c.lex(text)
    pairs, _ = c.pairs_of(tokens)
    return len(c.cast_sites(tokens, pairs))


def call_args(tokens, pairs, open_i, text):
    """Argument texts of the call whose '(' is tokens[open_i] (top-level commas)."""
    close = pairs[open_i]
    args, start, depth = [], open_i + 1, 0
    for i in range(open_i + 1, close + 1):
        v = tokens[i].value
        if i == close or (v == ',' and depth == 0):
            args.append(text[tokens[start].pos:tokens[i - 1].pos + len(tokens[i - 1].value)] if i > start else '')
            start = i + 1
        elif v in '([{':
            depth += 1
        elif v in ')]}':
            depth -= 1
    return args


def macro_use_casts(name, args, table, depth=0, active=()):
    """Pointer casts the body of `name` contributes at one use with argument texts `args`."""
    params, body = table[name]
    tokens = c.lex(body)
    pairs, _ = c.pairs_of(tokens)
    params = params or []

    def subst(lo, hi):
        out, arg_casts = [], 0
        for t in tokens[lo:hi]:
            if t.kind == 'id' and t.value in params:
                k = params.index(t.value)
                a = args[k] if k < len(args) else ''
                out.append(a)
                arg_casts += lexical_casts(a)
            else:
                out.append(t.value)
        return ' '.join(out), arg_casts

    expanded, from_args = subst(0, len(tokens))
    count = lexical_casts(expanded) - from_args
    if depth >= MACRO_DEPTH:
        return count
    # nested file-local macros used by the body (C does not re-expand a macro inside itself)
    for i, t in enumerate(tokens):
        if t.kind != 'id' or t.value not in table or t.value == name or t.value in active:
            continue
        if i and tokens[i - 1].value in ('.', '->'):
            continue
        inner_params = table[t.value][0]
        if inner_params is None:
            count += macro_use_casts(t.value, [], table, depth + 1, active + (name,))
        elif i + 1 < len(tokens) and tokens[i + 1].value == '(' and i + 1 in pairs:
            inner = []
            for a in call_args(tokens, pairs, i + 1, body):
                sub = c.lex(a)
                inner.append(' '.join(args[params.index(x.value)] if x.kind == 'id' and x.value in params
                                      and params.index(x.value) < len(args) else x.value for x in sub))
            count += macro_use_casts(t.value, inner, table, depth + 1, active + (name,))
    return count


def macro_use_casts_by_origin(name, args, table, header_origin, depth=0, active=()):
    """(file-local, header) casts contributed by one expansion and nested macros."""
    params, body = table[name]
    tokens = c.lex(body)
    pairs, _ = c.pairs_of(tokens)
    params = params or []
    expanded, from_args = [], 0
    for token in tokens:
        if token.kind == 'id' and token.value in params:
            index = params.index(token.value)
            argument = args[index] if index < len(args) else ''
            expanded.append(argument)
            from_args += lexical_casts(argument)
        else:
            expanded.append(token.value)
    direct = max(0, lexical_casts(' '.join(expanded)) - from_args)
    counts = [0, 0]
    counts[int(header_origin[name])] += direct
    if depth >= MACRO_DEPTH:
        return counts
    for i, token in enumerate(tokens):
        if (token.kind != 'id' or token.value not in table or token.value == name
                or token.value in active or (i and tokens[i - 1].value in ('.', '->'))):
            continue
        inner_params = table[token.value][0]
        if inner_params is None:
            inner_args = []
        elif i + 1 < len(tokens) and tokens[i + 1].value == '(' and i + 1 in pairs:
            inner_args = []
            for argument in call_args(tokens, pairs, i + 1, body):
                substituted = c.lex(argument)
                inner_args.append(' '.join(
                    args[params.index(t.value)] if t.kind == 'id' and t.value in params
                    and params.index(t.value) < len(args) else t.value for t in substituted))
        else:
            continue
        nested = macro_use_casts_by_origin(token.value, inner_args, table, header_origin,
                                           depth + 1, active + (name,))
        counts[0] += nested[0]
        counts[1] += nested[1]
    return counts


def macro_cast_sites(text, tokens, pairs):
    """[(token index, macro name, casts)] for every use of a file-local macro whose body adds pointer casts."""
    events = macro_events(text)
    if not events:
        return []
    table, out, ev = {}, [], 0
    for i, t in enumerate(tokens):
        while ev < len(events) and events[ev][0] <= t.pos:
            pos, name, params, body = events[ev]
            if body is None:
                table.pop(name, None)
            else:
                table[name] = (params, body)
            ev += 1
        if t.kind != 'id' or t.value not in table:
            continue
        if i and tokens[i - 1].value in ('.', '->'):
            continue
        params = table[t.value][0]
        if params is None:
            args = []
        elif i + 1 < len(tokens) and tokens[i + 1].value == '(' and i + 1 in pairs:
            args = call_args(tokens, pairs, i + 1, text)
        else:
            continue
        n = macro_use_casts(t.value, args, table)
        if n > 0:
            out.append((i, t.value, n))
    return out


def header_macro_cast_sites(text, tokens, pairs, events):
    """[(token index, macro name, casts)] for header-origin casts at expanded use sites."""
    table, origin, out, ev = {}, {}, [], 0
    for i, token in enumerate(tokens):
        while ev < len(events) and events[ev][0] <= token.pos:
            _, name, params, body, is_header = events[ev]
            if body is None:
                table.pop(name, None)
                origin.pop(name, None)
            else:
                table[name] = (params, body)
                origin[name] = is_header
            ev += 1
        if (token.kind != 'id' or token.value not in table
                or (i and tokens[i - 1].value in ('.', '->'))):
            continue
        params = table[token.value][0]
        if params is None:
            args = []
        elif i + 1 < len(tokens) and tokens[i + 1].value == '(' and i + 1 in pairs:
            args = call_args(tokens, pairs, i + 1, text)
        else:
            continue
        n = macro_use_casts_by_origin(token.value, args, table, origin)[1]
        if n:
            out.append((i, token.value, n))
    return out


def analyze(path, text, macro_casts=False, header_events=()):
    tokens = c.lex(text)
    pairs, warnings = c.pairs_of(tokens)
    definitions = list(c.definitions(tokens, pairs))
    spans, errors = exemptions(text, tokens, pairs)
    for a, b in spans:
        if any(a <= name and end < b for start, name, body, end, style in definitions):
            errors.append('BYTES marker cannot exempt a whole function; annotate a specific site')
    errors += [message for pos, message in warnings]
    excluded = set()
    for a, b in spans:
        if tokens[a].value == 'do' and a + 1 in pairs and tokens[a + 1].value == '{':
            # The recorded scheduling constraint is the wrapper shell. Its
            # ordinary body still owns any casts, externs or other debt.
            close = pairs[a + 1]
            excluded.update(range(a, a + 2))
            excluded.update(range(close, b))
        else:
            excluded.update(range(a, b))
    scopes, owners, occurrences = {}, ['<global>'] * len(tokens), Counter()
    for start, name, body, end, style in definitions:
        symbol = tokens[name].value
        occurrences[symbol] += 1
        key = symbol + '#' + str(occurrences[symbol])
        scopes[key] = dict(symbol=symbol, line=text.count('\n', 0, tokens[name].pos) + 1)
        owners[start:end + 1] = [key] * (end + 1 - start)
    scopes['<global>'] = dict(symbol='<global>', line=1)
    typedefs = [dict(name=name, kind=kind, file=path,
                     line=text.count('\n', 0, tokens[start].pos) + 1,
                     users=set(), start=start, end=end)
                for name, kind, start, end in typedef_view_sites(tokens, pairs)]
    typedef_by_name = {}
    declaration_tokens = set()
    for row in typedefs:
        typedef_by_name.setdefault(row['name'], []).append(row)
        declaration_tokens.update(range(row['start'], row['end']))
    for i, token in enumerate(tokens):
        if (i not in declaration_tokens and token.kind == 'id' and owners[i] != '<global>'
                and token.value in typedef_by_name):
            for row in typedef_by_name[token.value]:
                row['users'].add(owners[i])
    for row in typedefs:
        row['users'] = sorted(row['users'])
        del row['start'], row['end']
    counts = {key: Counter() for key in scopes}
    sizes = Counter()
    layouts = {key: set() for key in scopes}
    views = Counter()
    for i, token in enumerate(tokens):
        owner = owners[i]
        if i in excluded:
            continue
        # Literal contents are not identifiers, casts, keywords, or macro calls.
        sizes[owner] += 1
        if token.kind != 'id':
            continue
        value = token.value
        if i and tokens[i - 1].value in {'.', '->'}:
            if value in {'s', 'u'}:
                views['s_u'] += 1
                counts[owner]['sign_views'] += 1
            elif value.startswith('as_') and re.fullmatch(r'as_[su](?:8|16|32)', value):
                views['as_signedness'] += 1
                counts[owner]['sign_views'] += 1
            elif value in {'signed_whole', 'signed_byte'} | OTHER_VIEW:
                views['other_width_views'] += 1
                counts[owner]['sign_views'] += 1
        if value == 'goto':
            counts[owner]['goto'] += 1
        if value == 'volatile':
            counts[owner]['volatile'] += 1
        if value.startswith('M2C_'):
            counts[owner]['m2c_macros'] += 1
        if GENERATED.fullmatch(value):
            layouts[owner].add(value)
    for i in declaration_sites(tokens, pairs, definitions):
        if i not in excluded:
            counts[owners[i]]['local_externs'] += 1
    for a, b in c.cast_sites(tokens, pairs):
        if not any(i in excluded for i in range(a, b + 1)):
            counts[owners[a]]['pointer_casts'] += 1
    hidden = {key: Counter() for key in scopes} if macro_casts else None
    header_hidden = {key: Counter() for key in scopes} if macro_casts else None
    if macro_casts:
        for i, name, n in macro_cast_sites(text, tokens, pairs):
            if i not in excluded:
                hidden[owners[i]]['macro_casts'] += n
                hidden[owners[i]]['macro_uses'] += 1
                hidden[owners[i]]['macro:' + name] += n
        for i, name, n in header_macro_cast_sites(text, tokens, pairs, header_events):
            if i not in excluded:
                header_hidden[owners[i]]['casts'] += n
                header_hidden[owners[i]]['uses'] += 1
                header_hidden[owners[i]]['macro:' + name] += n
    # Directives are excluded by the C lexer; count only actual M2C definitions.
    for m in c.LEX.finditer(text):
        if m.lastgroup == 'directive' and re.match(r'\s*#\s*define\s+M2C_\w+\b', m[0]):
            counts['<global>']['m2c_macros'] += 1
    rows = {}
    for key, scope in scopes.items():
        counts[key]['generated_layouts'] = len(layouts[key])
        rows[key] = dict(counts={k: counts[key][k] for k in CLASSES}, tokens=sizes[key], **scope)
        if hidden is not None:
            rows[key]['macro_casts'] = dict(hidden[key])
            rows[key]['header_macro_casts'] = dict(header_hidden[key])
    signedness_unions, bad_label_unions = union_sites(path, text, tokens, pairs)
    return dict(file=path, scopes=rows, markers=len(spans), errors=errors,
                view_counts=dict(views), signedness_unions=signedness_unions,
                bad_label_unions=bad_label_unions, typedef_views=typedefs,
                union_definitions=union_definition_count(tokens, pairs),
                generic_index_views=generic_index_views(text))


def totals(rows):
    return {key: sum(row['counts'][key] for row in rows) for key in CLASSES}


def census(root, only=None, macro_casts=False):
    available = sorted(p.relative_to(root).as_posix() for p in (root / 'src').rglob('*.c'))
    if not available:
        raise ValueError('no src/**/*.c files')
    selected = sorted(set(only)) if only else available
    if set(selected) - set(available):
        raise ValueError('--only must name existing src/**/*.c files')
    files, functions, errors, markers = {}, {}, [], 0
    view_counts, signedness_unions, bad_label_unions = Counter(), [], []
    union_definitions = generic_views = 0
    typedef_views, address_names = [], set()
    header_cache = {}
    for rel in selected:
        path = root / rel
        # Refuse silently skipped inputs and keep reads bounded in size.
        if path.is_symlink() or path.stat().st_size > 4 * 1024 * 1024:
            raise ValueError('unsupported symlink or source over 4 MiB: ' + rel)
        text = path.read_text()
        header_events = include_macro_events(root, path, text, header_cache) if macro_casts else ()
        source = analyze(rel, text, macro_casts, header_events)
        scopes = source['scopes']
        functions[rel] = scopes
        files[rel] = dict(counts=totals(scopes.values()),
                          tokens=sum(r['tokens'] for r in scopes.values()))
        errors += [rel + ': ' + message for message in source['errors']]
        markers += source['markers']
        view_counts.update(source['view_counts'])
        signedness_unions.extend((rel, line) for line in source['signedness_unions'])
        bad_label_unions.extend(source['bad_label_unions'])
        union_definitions += source['union_definitions']
        generic_views += source['generic_index_views']
        typedef_views.extend(source['typedef_views'])
        address_names.update(row['name'] for row in source['typedef_views']
                             if ADDRESS_NAME.search(row['name']) and not row['name'].startswith('S_'))
    if not only:
        for base in ('include', 'src'):
            for path in sorted((root / base).rglob('*.h')):
                rel = path.relative_to(root).as_posix()
                if path.is_symlink() or path.stat().st_size > 4 * 1024 * 1024:
                    raise ValueError('unsupported symlink or header over 4 MiB: ' + rel)
                header_text = path.read_text()
                header_tokens = c.lex(header_text)
                header_pairs = c.pairs_of(header_tokens)[0]
                sign, bad = union_sites(rel, header_text, header_tokens, header_pairs)
                union_definitions += union_definition_count(header_tokens, header_pairs)
                generic_views += generic_index_views(header_text)
                address_names.update(name for name, _, _, _ in typedef_view_sites(header_tokens, header_pairs)
                                     if ADDRESS_NAME.search(name) and not name.startswith('S_'))
                signedness_unions.extend((rel, line) for line in sign)
                bad_label_unions.extend(bad)
    extra = {}
    if macro_casts:
        hidden, header_hidden = Counter(), Counter()
        for scopes in functions.values():
            for row in scopes.values():
                hidden.update({k: v for k, v in row.get('macro_casts', {}).items() if not k.startswith('macro:')})
                header_hidden.update({k: v for k, v in row.get('header_macro_casts', {}).items()
                                      if not k.startswith('macro:')})
        extra['macro_casts_report'] = dict(casts=hidden['macro_casts'], uses=hidden['macro_uses'],
                                           note='report only; baseline records total, no ratchet')
        extra['header_macro_casts_report'] = dict(casts=header_hidden['casts'], uses=header_hidden['uses'],
                                                  note='report only; reachable include/ macros, lexical #if scope')
    return dict(**extra, schema_version=SCHEMA, classes=list(CLASSES), limited=bool(only),
                source_files=len(selected), function_count=sum(len(s) - 1 for s in functions.values()),
                by_class=totals(files.values()), by_file=files, by_function=functions,
                exempt_sites=markers, errors=errors,
                sign_views_report=dict(view_counts, total=sum(view_counts.values()),
                                       note='lexical source member accesses; includes width-view candidates'),
                signedness_unions_report=dict(count=len(signedness_unions),
                                              note='same-width signed and unsigned immediate union members in src/ and include/'),
                union_definitions_report=dict(count=union_definitions,
                                              note='all braced union definitions in src/ and include/'),
                generic_index_views_report=dict(count=generic_views,
                                                note='indexed ScratchPad members and record bytes candidates in src/ and include/'),
                signedness_union_sites=signedness_unions,
                bad_label_unions=bad_label_unions,
                view_inventory_report=dict(address_named_types=len(address_names),
                                           source_local_single_function_types=sum(
                                               len(row['users']) == 1 and not row['name'].startswith('S_')
                                               and not ADDRESS_NAME.search(row['name']) for row in typedef_views),
                                           note='unique address-named aliases in src/include; named .c typedef declarations with one function user'),
                typedef_view_sites=typedef_views)


def baseline_record(summary):
    """Keep only debt-bearing files/scopes; preserve full file denominators."""
    record = {key: summary[key] for key in ('schema_version', 'classes', 'by_class')}
    if 'macro_casts_report' in summary:
        record['report_counts'] = dict(file_local_macro_casts=summary['macro_casts_report']['casts'],
                                       header_macro_casts=summary['header_macro_casts_report']['casts'],
                                       signedness_unions=summary['signedness_unions_report']['count'],
                                       unions_total=summary['union_definitions_report']['count'],
                                       generic_index_views=summary['generic_index_views_report']['count'],
                                       address_named_types=summary['view_inventory_report']['address_named_types'],
                                       source_local_single_function_types=summary['view_inventory_report']['source_local_single_function_types'])
    record['bad_label_sites'] = sorted(row['site'] for row in summary['bad_label_unions'])
    record['by_file'] = {}
    for rel, row in sorted(summary['by_file'].items()):
        if not any(row['counts'].values()):
            continue
        scopes = {}
        for key, scope in sorted(summary['by_function'][rel].items()):
            counts = [scope['counts'][k] for k in CLASSES]
            while counts and counts[-1] == 0:
                counts.pop()
            if counts:
                scopes[key] = [scope['tokens'], *counts]
        directory, name = rel.rsplit('/', 1)
        record['by_file'].setdefault(directory, {})[name] = [row['tokens'], scopes]
    return record


def baseline_text(record):
    """Sorted keys, one physical file per line, and no source line numbers."""
    dump = lambda value: json.dumps(value, separators=(',', ':'), sort_keys=True)
    files = ',\n'.join(dump(directory) + ':{\n' + ',\n'.join(
        dump(name) + ':' + dump(row) for name, row in sorted(rows.items())) + '\n}'
        for directory, rows in sorted(record['by_file'].items()))
    reports = ',"report_counts":' + dump(record['report_counts']) if 'report_counts' in record else ''
    bad_labels = ',"bad_label_sites":' + dump(record['bad_label_sites'])
    return ('{"by_class":' + dump(record['by_class']) + ',"by_file":{\n' + files
            + '\n},"classes":' + dump(record['classes']) + reports + bad_labels
            + ',"schema_version":' + dump(record['schema_version']) + '}\n')



def validate_counts(counts):
    return (isinstance(counts, dict) and set(counts) == set(CLASSES)
            and all(type(n) is int and n >= 0 for n in counts.values()))


def validate_baseline(baseline):
    """Validate sparse storage and expand it for absolute-count comparisons."""
    if not isinstance(baseline, dict) or baseline.get('schema_version') != SCHEMA or baseline.get('classes') != list(CLASSES):
        raise ValueError('baseline schema/classes differ; review before writing a new baseline')
    if not validate_counts(baseline.get('by_class')):
        raise ValueError('baseline must record nonnegative integer counts for every class')
    directories = baseline.get('by_file')
    fields = {'schema_version', 'classes', 'by_class', 'by_file', 'bad_label_sites'}
    if ('report_counts' in baseline and (not isinstance(baseline['report_counts'], dict)
            or set(baseline['report_counts']) != {'file_local_macro_casts', 'header_macro_casts',
                                                  'signedness_unions', 'unions_total', 'generic_index_views', 'address_named_types',
                                                  'source_local_single_function_types'}
            or any(type(n) is not int or n < 0 for n in baseline['report_counts'].values()))):
        raise ValueError('invalid report-only baseline counts')
    sites = baseline.get('bad_label_sites')
    if (not isinstance(sites, list) or any(not isinstance(s, str) or not s.startswith(('src/', 'include/')) for s in sites)
            or len(sites) != len(set(sites))):
        raise ValueError('invalid bad-label union baseline sites')
    if (set(baseline) not in (fields, fields | {'report_counts'})
            or not isinstance(directories, dict)):
        raise ValueError('baseline requires sparse by_file records')
    files, functions = {}, {}
    for directory, entries in directories.items():
        if (not isinstance(directory, str) or (not directory.startswith('src/')
                and directory != 'src') or Path(directory).is_absolute()
                or any(part in {'', '.', '..'} for part in directory.split('/'))
                or not isinstance(entries, dict) or not entries):
            raise ValueError('invalid baseline directory')
        for name, packed in entries.items():
            if not isinstance(name, str) or '/' in name or not name.endswith('.c'):
                raise ValueError('invalid baseline filename')
            rel = directory + '/' + name
            if (not isinstance(packed, list) or len(packed) != 2
                    or type(packed[0]) is not int or packed[0] < 0
                    or not isinstance(packed[1], dict) or not packed[1]):
                raise ValueError('invalid baseline file tokens/scopes in ' + rel)
            scopes = {}
            for key, row in packed[1].items():
                # [tokens, counts in CLASSES order]; trailing zero counts omitted.
                if (not isinstance(key, str) or not key or not isinstance(row, list)
                        or not 2 <= len(row) <= len(CLASSES) + 1
                        or any(type(n) is not int or n < 0 for n in row)
                        or row[-1] == 0):
                    raise ValueError('invalid sparse baseline scope in ' + rel)
                counts = dict.fromkeys(CLASSES, 0)
                counts.update(zip(CLASSES, row[1:]))
                scopes[key] = dict(counts=counts, tokens=row[0])
            if sum(r['tokens'] for r in scopes.values()) > packed[0]:
                raise ValueError('baseline file tokens below retained scope tokens in ' + rel)
            files[rel] = dict(counts=totals(scopes.values()), tokens=packed[0])
            functions[rel] = scopes
    if totals(files.values()) != baseline['by_class']:
        raise ValueError('baseline class totals differ')
    return dict(baseline, by_file=files, by_function=functions)


def compare_row(label, current, previous):
    problems = []
    old = previous['counts'] if previous else dict.fromkeys(CLASSES, 0)
    for key in CLASSES:
        if current['counts'][key] > old[key]:
            problems.append(f'{label}: {key} {current["counts"][key]} > baseline {old[key]}')
    # Density is reported in the census only. Removing declarations or other
    # tokens must not fail the ratchet when no absolute debt count increases.
    return problems


def check_baseline(summary, baseline):
    baseline = validate_baseline(baseline)
    if summary['limited'] or summary['errors']:
        return ['baseline requires a complete census without parse/marker errors']
    problems = []
    for key in CLASSES:
        if summary['by_class'][key] > baseline['by_class'][key]:
            problems.append(f'all: {key} {summary["by_class"][key]} > baseline {baseline["by_class"][key]}')
    if 'report_counts' in baseline:
        current = summary['signedness_unions_report']['count']
        previous = baseline['report_counts']['signedness_unions']
        if current > previous:
            problems.append(f'all: signedness_unions {current} > baseline {previous}')
        current = summary['union_definitions_report']['count']
        previous = baseline['report_counts']['unions_total']
        if current > previous:
            problems.append(f'all: unions_total {current} > baseline {previous}')
        current = summary['generic_index_views_report']['count']
        previous = baseline['report_counts']['generic_index_views']
        if current > previous:
            problems.append(f'all: generic_index_views {current} > baseline {previous}')
    for rel, row in summary['by_file'].items():
        problems += compare_row(rel, row, baseline['by_file'].get(rel))
        old_scopes = baseline['by_function'].get(rel, {})
        for key, scope in summary['by_function'][rel].items():
            problems += compare_row(rel + '::' + key, scope, old_scopes.get(key))
    known = set(baseline['bad_label_sites'])
    for row in summary['bad_label_unions']:
        if row['site'] not in known:
            problems.append(f'{row["site"]}: new bad-label union ({",".join(row["reasons"])})')
    return problems


def write_outputs(out, summary, baseline=None):
    if baseline is not None:
        baseline = validate_baseline(baseline)
    out.mkdir(parents=True, exist_ok=True)
    (out / '.ignore').write_text('*\n')
    with (out / 'debt_functions.tsv').open('w', newline='') as stream:
        fields = ['file', 'function', 'line', *CLASSES, 'tokens', 'pointer_casts_per_1000_tokens', 'status']
        writer = csv.DictWriter(stream, fields, delimiter='\t', lineterminator='\n')
        writer.writeheader()
        for rel, scopes in summary['by_function'].items():
            for key, row in scopes.items():
                old = baseline['by_function'].get(rel, {}).get(key) if baseline else None
                problems = compare_row(rel + '::' + key, row, old) if baseline else []
                writer.writerow(dict(file=rel, function=key, line=row['line'], **row['counts'], tokens=row['tokens'],
                    pointer_casts_per_1000_tokens=round(1000 * row['counts']['pointer_casts'] / max(1, row['tokens']), 3),
                    status='FAIL' if problems else 'PASS' if baseline else 'CENSUS'))
    if 'macro_casts_report' in summary:
        with (out / 'debt_macro_casts.tsv').open('w', newline='') as stream:
            writer = csv.writer(stream, delimiter='\t', lineterminator='\n')
            writer.writerow(['file', 'function', 'line', 'pointer_casts', 'macro_casts', 'macro_uses', 'macros'])
            for rel, scopes in summary['by_function'].items():
                for key, row in scopes.items():
                    hidden = row.get('macro_casts') or {}
                    if hidden.get('macro_casts'):
                        macros = ','.join('%s=%d' % (k[6:], v) for k, v in sorted(hidden.items()) if k.startswith('macro:'))
                        writer.writerow([rel, key, row['line'], row['counts']['pointer_casts'],
                                         hidden['macro_casts'], hidden['macro_uses'], macros])
        with (out / 'debt_header_macro_casts.tsv').open('w', newline='') as stream:
            writer = csv.writer(stream, delimiter='\t', lineterminator='\n')
            writer.writerow(['file', 'function', 'line', 'pointer_casts', 'header_macro_casts',
                             'header_macro_uses', 'macros'])
            for rel, scopes in summary['by_function'].items():
                for key, row in scopes.items():
                    hidden = row.get('header_macro_casts') or {}
                    if hidden.get('casts'):
                        macros = ','.join('%s=%d' % (k[6:], v) for k, v in sorted(hidden.items())
                                          if k.startswith('macro:'))
                        writer.writerow([rel, key, row['line'], row['counts']['pointer_casts'],
                                         hidden['casts'], hidden['uses'], macros])
    compact = {k: v for k, v in summary.items() if k not in ('by_function', 'by_file')}
    (out / 'debt_summary.json').write_text(json.dumps(compact, indent=2) + '\n')
    with (out / 'debt_bad_label_unions.tsv').open('w', newline='') as stream:
        writer = csv.writer(stream, delimiter='\t', lineterminator='\n')
        writer.writerow(['site', 'file', 'line', 'reasons', 'status'])
        known = set(baseline['bad_label_sites']) if baseline else set()
        for row in summary['bad_label_unions']:
            writer.writerow([row['site'], row['file'], row['line'], ','.join(row['reasons']),
                             'KNOWN' if row['site'] in known else 'FAIL' if baseline else 'CENSUS'])
    with (out / 'debt_signedness_unions.tsv').open('w', newline='') as stream:
        writer = csv.writer(stream, delimiter='\t', lineterminator='\n')
        writer.writerow(['file', 'line'])
        writer.writerows(summary['signedness_union_sites'])
    with (out / 'debt_view_inventory.tsv').open('w', newline='') as stream:
        writer = csv.writer(stream, delimiter='\t', lineterminator='\n')
        writer.writerow(['file', 'line', 'kind', 'typedef', 'function_users', 'users'])
        for row in summary['typedef_view_sites']:
            writer.writerow([row['file'], row['line'], row['kind'], row['name'],
                             len(row['users']), ','.join(row['users'])])
    with (out / 'debt_files.tsv').open('w', newline='') as stream:
        writer = csv.writer(stream, delimiter='\t', lineterminator='\n')
        writer.writerow(['file', *CLASSES, 'tokens'])
        for rel, row in summary['by_file'].items():
            writer.writerow([rel, *(row['counts'][key] for key in CLASSES), row['tokens']])


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=TOOLS.parent)
    parser.add_argument('--out', type=Path, default=Path('work/debt'))
    parser.add_argument('--baseline', type=Path, default=Path(__file__).with_name('debt_baseline.json'))
    parser.add_argument('--only', nargs='+')
    parser.add_argument('--summary', action='store_true')
    parser.add_argument('--macro-casts', action='store_true',
                        help='report pointer casts added by file-local and reachable include/ macro bodies '
                             'at each use site; these report counts do not affect the ratchet')
    parser.add_argument('--bridges', action='store_true',
                        help='check open ledger/bridge_casts.jsonl cast sites; no debt census')
    parser.add_argument('--prototypes', action='store_true',
                        help='definition-inclusive prototype consistency census and ratchet')
    parser.add_argument('--unions', action='store_true',
                        help='check the tracked union inventory and its no-growth baseline')
    actions = parser.add_mutually_exclusive_group()
    actions.add_argument('--check', action='store_true')
    actions.add_argument('--write-baseline', action='store_true')
    args = parser.parse_args(argv)
    if args.prototypes:
        if args.bridges or args.only:
            parser.error('--prototypes cannot be combined with --bridges or --only')
        from proto_check import main as proto_main
        command = ['--root', str(args.root), '--out', str(args.out / 'proto_consistency.json')]
        if args.check:
            command.append('--check')
        if args.write_baseline:
            command.append('--write-baseline')
        return proto_main(command)
    if args.bridges:
        if args.only or args.check or args.write_baseline:
            parser.error('--bridges cannot be combined with --only, --check or --write-baseline')
        from bridge_check import check_bridges
        try:
            counts, problems = check_bridges(args.root.resolve(),
                                             args.root.resolve() / 'ledger/bridge_casts.jsonl')
        except (OSError, ValueError, TypeError, KeyError) as exc:
            parser.error(str(exc))
        print(f'bridge rows: {sum(counts.values())}; open: {counts["open"]}; retired: {counts["retired"]}')
        for problem in problems:
            print(problem, file=sys.stderr)
        return 1 if problems else 0
    if args.unions:
        if args.only or args.write_baseline or args.macro_casts:
            parser.error('--unions does not combine with debt census options')
        sys.path.insert(0, str(TOOLS / 'typing'))
        from union_census import census as union_census
        root = args.root.resolve()
        current = union_census(root)
        ledger_path = root / 'ledger/unions.jsonl'
        union_baseline = root / 'tools/lint/union_baseline.json'
        try:
            tracked = [json.loads(line) for line in ledger_path.read_text().splitlines() if line.strip()]
            baseline = json.loads(union_baseline.read_text())
        except (OSError, ValueError) as exc:
            parser.error(str(exc))
        problems = check_union_inventory(current, tracked, baseline)
        for problem in problems:
            print(problem, file=sys.stderr)
        print(f'{len(current)} unions; baseline {baseline["count"]}; {len(tracked)} ledger rows')
        if not problems:
            print('Union ledger check passed')
        return int(bool(problems))
    if args.only and (args.check or args.write_baseline):
        parser.error('--only cannot check or write a baseline')
    try:
        baseline = json.loads(args.baseline.read_text()) if args.check else None
        if baseline is not None:
            validate_baseline(baseline)
        report_macros = args.macro_casts or args.summary or args.write_baseline
        summary = census(args.root.resolve(), args.only, report_macros)
        problems = check_baseline(summary, baseline) if args.check else []
        problems += summary['errors']
        write_outputs(args.out, summary, baseline)
        if args.write_baseline and not problems:
            # Omitted files, scopes and trailing class counts all mean zero debt.
            args.baseline.write_text(baseline_text(baseline_record(summary)))
    except (OSError, ValueError, TypeError, KeyError) as exc:
        parser.error(str(exc))
    print(f'{summary["source_files"]} C files; {summary["function_count"]} functions; '
          f'{summary["exempt_sites"]} BYTES sites exempt')
    if args.summary:
        for key, count in summary['by_class'].items():
            print(f'{key}\t{count}')
        print('sign_views by form\t' + json.dumps(summary['sign_views_report'], sort_keys=True))
        print(f'signedness_unions (ratchet)\t{summary["signedness_unions_report"]["count"]}')
        print(f'unions_total (ratchet)\t{summary["union_definitions_report"]["count"]}')
        print(f'generic_index_views (ratchet)\t{summary["generic_index_views_report"]["count"]}')
        print(f'bad_label_unions (known sites only)\t{len(summary["bad_label_unions"])}')
        for key, value in summary['view_inventory_report'].items():
            if key != 'note':
                print(f'{key} (report only)\t{value}')
    if report_macros:
        report = summary['macro_casts_report']
        print(f'macro_casts (report only)\t{report["casts"]}\t{report["uses"]} uses')
        report = summary['header_macro_casts_report']
        print(f'header_macro_casts (report only)\t{report["casts"]}\t{report["uses"]} uses')
    for problem in problems:
        print(problem, file=sys.stderr)
    if args.check and not problems:
        print('Baseline check passed')
    return int(bool(problems))


if __name__ == '__main__':
    sys.exit(main())
