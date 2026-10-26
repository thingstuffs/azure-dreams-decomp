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

SCHEMA = 2
CLASSES = ('local_externs', 'generated_layouts', 'm2c_macros', 'goto',
           'volatile', 'pointer_casts')
GENERATED = re.compile(r'^S_(?:func_)?[0-9A-Fa-f]{8}(?:_\w+)?$')
# A marker annotates one adjacent statement, declaration or braced control arm.
# It never exempts the enclosing function just because it contains a marker.
MARKER = re.compile(r'^/\* BYTES: [^\n]+ \*/$')


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


def analyze(path, text):
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
    counts = {key: Counter() for key in scopes}
    sizes = Counter()
    layouts = {key: set() for key in scopes}
    for i, token in enumerate(tokens):
        owner = owners[i]
        if i in excluded:
            continue
        # Literal contents are not identifiers, casts, keywords, or macro calls.
        sizes[owner] += 1
        if token.kind != 'id':
            continue
        value = token.value
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
    # Directives are excluded by the C lexer; count only actual M2C definitions.
    for m in c.LEX.finditer(text):
        if m.lastgroup == 'directive' and re.match(r'\s*#\s*define\s+M2C_\w+\b', m[0]):
            counts['<global>']['m2c_macros'] += 1
    rows = {}
    for key, scope in scopes.items():
        counts[key]['generated_layouts'] = len(layouts[key])
        rows[key] = dict(counts={k: counts[key][k] for k in CLASSES}, tokens=sizes[key], **scope)
    return dict(file=path, scopes=rows, markers=len(spans), errors=errors)


def totals(rows):
    return {key: sum(row['counts'][key] for row in rows) for key in CLASSES}


def census(root, only=None):
    available = sorted(p.relative_to(root).as_posix() for p in (root / 'src').rglob('*.c'))
    if not available:
        raise ValueError('no src/**/*.c files')
    selected = sorted(set(only)) if only else available
    if set(selected) - set(available):
        raise ValueError('--only must name existing src/**/*.c files')
    files, functions, errors, markers = {}, {}, [], 0
    for rel in selected:
        path = root / rel
        # Refuse silently skipped inputs and keep reads bounded in size.
        if path.is_symlink() or path.stat().st_size > 4 * 1024 * 1024:
            raise ValueError('unsupported symlink or source over 4 MiB: ' + rel)
        source = analyze(rel, path.read_text())
        scopes = source['scopes']
        functions[rel] = scopes
        files[rel] = dict(counts=totals(scopes.values()),
                          tokens=sum(r['tokens'] for r in scopes.values()))
        errors += [rel + ': ' + message for message in source['errors']]
        markers += source['markers']
    return dict(schema_version=SCHEMA, classes=list(CLASSES), limited=bool(only),
                source_files=len(selected), function_count=sum(len(s) - 1 for s in functions.values()),
                by_class=totals(files.values()), by_file=files, by_function=functions,
                exempt_sites=markers, errors=errors)


def baseline_record(summary):
    """Keep only debt-bearing files/scopes; preserve full file denominators."""
    record = {key: summary[key] for key in ('schema_version', 'classes', 'by_class')}
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
    return ('{"by_class":' + dump(record['by_class']) + ',"by_file":{\n' + files
            + '\n},"classes":' + dump(record['classes'])
            + ',"schema_version":' + dump(record['schema_version']) + '}\n')



def validate_counts(counts):
    return (isinstance(counts, dict) and set(counts) == set(CLASSES)
            and all(type(n) is int and n >= 0 for n in counts.values()))


def validate_baseline(baseline):
    """Validate sparse storage and expand it for the unchanged comparisons."""
    if not isinstance(baseline, dict) or baseline.get('schema_version') != SCHEMA or baseline.get('classes') != list(CLASSES):
        raise ValueError('baseline schema/classes differ; review before writing a new baseline')
    if not validate_counts(baseline.get('by_class')):
        raise ValueError('baseline must record nonnegative integer counts for every class')
    directories = baseline.get('by_file')
    if (set(baseline) != {'schema_version', 'classes', 'by_class', 'by_file'}
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
    # Exact cross multiplication: no rounding and no float-dependent thresholds.
    if previous and (current['counts']['pointer_casts'] * previous['tokens'] >
                     old['pointer_casts'] * current['tokens']):
        problems.append(label + ': pointer_cast_density increased (casts per nonexempt C token)')
    return problems


def check_baseline(summary, baseline):
    baseline = validate_baseline(baseline)
    if summary['limited'] or summary['errors']:
        return ['baseline requires a complete census without parse/marker errors']
    problems = []
    for key in CLASSES:
        if summary['by_class'][key] > baseline['by_class'][key]:
            problems.append(f'all: {key} {summary["by_class"][key]} > baseline {baseline["by_class"][key]}')
    for rel, row in summary['by_file'].items():
        problems += compare_row(rel, row, baseline['by_file'].get(rel))
        old_scopes = baseline['by_function'].get(rel, {})
        for key, scope in summary['by_function'][rel].items():
            problems += compare_row(rel + '::' + key, scope, old_scopes.get(key))
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
    compact = {k: v for k, v in summary.items() if k not in ('by_function', 'by_file')}
    (out / 'debt_summary.json').write_text(json.dumps(compact, indent=2) + '\n')
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
    actions = parser.add_mutually_exclusive_group()
    actions.add_argument('--check', action='store_true')
    actions.add_argument('--write-baseline', action='store_true')
    args = parser.parse_args(argv)
    if args.only and (args.check or args.write_baseline):
        parser.error('--only cannot check or write a baseline')
    try:
        baseline = json.loads(args.baseline.read_text()) if args.check else None
        if baseline is not None:
            validate_baseline(baseline)
        summary = census(args.root.resolve(), args.only)
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
    for problem in problems:
        print(problem, file=sys.stderr)
    if args.check and not problems:
        print('Baseline check passed')
    return int(bool(problems))


if __name__ == '__main__':
    sys.exit(main())
