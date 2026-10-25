#!/usr/bin/env python3
"""Lint registered game TUs in both pointer widths using private port headers."""
from __future__ import annotations

import argparse
import ast
import collections
from concurrent.futures import ThreadPoolExecutor
import csv
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import sys

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import source_layout

WARNINGS = (
    'int-conversion', 'pointer-to-int-cast', 'int-to-pointer-cast', 'return-type',
    'shadow', 'uninitialized', 'maybe-uninitialized', 'incompatible-pointer-types',
    'implicit-function-declaration', 'array-bounds', 'sizeof-pointer-memaccess',
)
MODES = ('m32', 'm64')
PHASES = ('syntax', 'flow')
LOCATION = re.compile(r'^(.*?):(\d+):(\d+): (warning|error|fatal error): (.*?)(?: \[(-W[^]]+)\])?$')
FUNCTION = re.compile(r"^.*?: In (?:function|member function) [‘'](.*?)[’']:")


def native_flags(port, root):
    """Read non-coverage CFLAGS without executing the asset-extracting builder."""
    def literal(node):
        if isinstance(node, ast.Constant) and isinstance(node.value, str):
            return node.value
        if isinstance(node, ast.List):
            return [literal(v) for v in node.elts]
        if isinstance(node, ast.Name) and node.id in ('PORT', 'GEN'):
            return port if node.id == 'PORT' else port / 'gen'
        if isinstance(node, ast.BinOp):
            if isinstance(node.op, ast.Add):
                return literal(node.left) + literal(node.right)
            if isinstance(node.op, ast.Div):
                return literal(node.left) / literal(node.right)
        if (isinstance(node, ast.Call) and isinstance(node.func, ast.Name)
                and node.func.id == 'str' and len(node.args) == 1 and not node.keywords):
            return str(literal(node.args[0]))
        raise ValueError('unsupported native CFLAGS expression; review port/tools/build.py')

    flags = None
    for node in ast.parse((port / 'tools/build.py').read_text()).body:
        if isinstance(node, ast.Assign) and any(
                isinstance(t, ast.Name) and t.id == 'CFLAGS' for t in node.targets):
            flags = literal(node.value)
        elif (isinstance(node, ast.AugAssign) and isinstance(node.target, ast.Name)
                and node.target.id == 'CFLAGS'):
            if flags is None or not isinstance(node.op, ast.Add):
                raise ValueError('unsupported native CFLAGS assignment')
            flags += literal(node.value)
    if not isinstance(flags, list) or not all(isinstance(f, str) for f in flags):
        raise ValueError('native builder must define a literal CFLAGS list')
    # Preserve include order, substituting original game headers for adapters.
    flags = [f.replace(str(port / 'gen/include'), str(root / 'include'))
             for f in flags if f not in ('-w', '-m32', '-m64')]
    flags += ['-O1', *('-W' + w for w in WARNINGS), '-fdiagnostics-color=never',
              '-fdiagnostics-show-option', '-fmessage-length=0', '-fmax-errors=0']
    return flags


def units(root):
    """Same physical home selection as the port builder's by_tu census."""
    result = collections.defaultdict(list)
    for row in source_layout.registry(root).values():
        if row.get('source_row'):
            continue
        source = source_layout.row_relative(row, root)
        if (root / source).is_file():
            result[source].append(row['id'])
    return dict(sorted(result.items()))


def sanitize(text, root, port):
    return text.replace(str(port), '$PORT').replace(str(root), '$ROOT')


def parse_diagnostics(log, root, port, source, mode, phase):
    function = '<global>'
    rows = []
    for line in log.splitlines():
        if line.endswith('At top level:'):
            function = '<global>'
        match = FUNCTION.match(line)
        if match:
            function = match[1]
            continue
        match = LOCATION.match(line)
        if not match:
            continue
        file, row, column, severity, message, warning = match.groups()
        file = sanitize(file, root, port).removeprefix('$ROOT/')
        rows.append(dict(file=file, function=function, line=int(row), column=int(column),
                         severity=severity, message=sanitize(message, root, port),
                         warning=(warning or 'compiler-error').split('=')[0],
                         tu=source, mode=mode, phase=phase))
    return rows


def group_findings(diagnostics):
    grouped = {}
    for d in diagnostics:
        if (d['severity'] != 'warning' or d['warning'].removeprefix('-W') not in WARNINGS
                or not d['file'].startswith(('src/', 'include/'))):
            continue
        key = d['file'], d['function'], d['warning']
        group = grouped.setdefault(key, dict(observations=set(), sites=set(), modes=set(),
                                            tus=set(), phases=set(), messages=set()))
        # The same observation in syntax and flow is counted only once.
        group['observations'].add((d['tu'], d['mode'], d['line'], d['column'], d['message']))
        group['sites'].add(f"{d['file']}:{d['line']}:{d['column']}")
        for field, value in (('modes', d['mode']), ('tus', d['tu']),
                             ('phases', d['phase']), ('messages', d['message'])):
            group[field].add(value)
    findings = []
    for key, group in sorted(grouped.items()):
        file, function, warning = key
        findings.append(dict(
            finding='L' + hashlib.sha256('\0'.join(key).encode()).hexdigest()[:12],
            file=file, function=function, warning=warning, subsystem=file.split('/')[1],
            count=len(group['observations']), tu_count=len(group['tus']),
            modes=','.join(sorted(group['modes'])), phases=','.join(sorted(group['phases'])),
            sites=';'.join(sorted(group['sites'])), messages=' | '.join(sorted(group['messages']))))
    return findings


def counts(findings):
    def classes(rows):
        counter = collections.Counter(r['warning'] for r in rows)
        return {'-W' + w: counter['-W' + w] for w in WARNINGS}
    return dict(
        normalized_findings=len(findings), by_class=classes(findings),
        by_subsystem={s: classes(r for r in findings if r['subsystem'] == s)
                      for s in sorted({r['subsystem'] for r in findings})},
        by_mode={m: classes(r for r in findings if m in r['modes'].split(',')) for m in MODES})


def baseline_record(summary):
    return {key: summary[key] for key in (
        'schema_version', 'compiler', 'units', 'compiler_jobs', 'modes', 'phases', 'flags',
        'by_class', 'by_subsystem', 'by_mode', 'normalized_findings')}


def check_baseline(summary, baseline):
    """Refuse incomparable coverage as well as any increased warning class."""
    problems = []
    if summary['limited'] or summary['failed_jobs']:
        problems.append('baseline requires a complete census with zero failed compiler jobs')
    for key in ('schema_version', 'compiler', 'units', 'compiler_jobs', 'modes', 'phases', 'flags'):
        if baseline.get(key) != summary[key]:
            problems.append(f'baseline {key} differs; review before recording a new baseline')
    recorded = baseline.get('by_class')
    if (not isinstance(recorded, dict) or set(recorded) != set(summary['by_class'])
            or any(type(n) is not int or n < 0 for n in recorded.values())):
        problems.append('baseline must record a nonnegative integer for every warning class')
    else:
        for warning, current in summary['by_class'].items():
            if current > recorded[warning]:
                problems.append(f'{warning}: {current} > baseline {recorded[warning]}')
    return problems


def format_summary(summary):
    subsystems = sorted(summary['by_subsystem'])
    rows = [f"{summary['units']} TUs, {summary['compiler_jobs']} compiler jobs, "
            f"{summary['failed_jobs']} failed; {summary['normalized_findings']} finding groups",
            '\t'.join(['class', 'all', *subsystems])]
    for warning, total in summary['by_class'].items():
        rows.append('\t'.join([warning, str(total),
                    *(str(summary['by_subsystem'][s][warning]) for s in subsystems)]))
    rows.append('\t'.join(['TOTAL', str(summary['normalized_findings']),
                *(str(sum(summary['by_subsystem'][s].values())) for s in subsystems)]))
    return '\n'.join(rows)


def write_tsv(path, fields, rows):
    with path.open('w', newline='') as stream:
        writer = csv.DictWriter(stream, fields, delimiter='\t', lineterminator='\n')
        writer.writeheader()
        writer.writerows(rows)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=TOOLS.parent)
    parser.add_argument('--port', type=Path, required=True, help='private clone directory containing tools/build.py and include/')
    parser.add_argument('--out', type=Path, default=Path('work/lint'))
    parser.add_argument('--cc', default='gcc', help='GCC executable with multilib support')
    parser.add_argument('--jobs', type=int, default=int(os.environ.get('JOBS', '4')))
    parser.add_argument('--only', nargs='+', help='registered source paths; partial runs cannot check or write a baseline')
    parser.add_argument('--summary', action='store_true', help='print per-class/per-subsystem counts')
    parser.add_argument('--baseline', type=Path, default=Path(__file__).with_name('baseline.json'))
    actions = parser.add_mutually_exclusive_group()
    actions.add_argument('--check', action='store_true', help='fail on any class increase above --baseline')
    actions.add_argument('--write-baseline', action='store_true', help='record a reviewed full census at --baseline')
    args = parser.parse_args(argv)
    if args.only and (args.check or args.write_baseline):
        parser.error('--only cannot check or write a baseline')
    root, port, out = args.root.resolve(), args.port.resolve(), args.out.resolve()
    try:
        if not (root / 'ledger/rows.jsonl').is_file():
            raise ValueError('--root must contain ledger/rows.jsonl')
        if not (port / 'include').is_dir():
            raise ValueError('--port must contain include/')
        available = units(root)
        selected = sorted(set(args.only)) if args.only else sorted(available)
        if not selected or set(selected) - available.keys():
            raise ValueError('no registered TUs selected, or an unregistered --only path')
        flags = native_flags(port, root)
        version = subprocess.check_output([args.cc, '--version'], text=True).splitlines()[0]
        baseline = json.loads(args.baseline.read_text()) if args.check else None
        if args.check and not isinstance(baseline, dict):
            raise ValueError('baseline must be a JSON object')
    except (OSError, ValueError, SyntaxError, subprocess.CalledProcessError) as error:
        parser.error(str(error))

    out.mkdir(parents=True, exist_ok=True)
    (out / '.ignore').write_text('*\n')
    write_tsv(out / 'lint_units.tsv', ['tu', 'rows'],
              [dict(tu=s, rows=';'.join(sorted(available[s]))) for s in selected])
    tasks = [(s, m, p) for s in selected for m in MODES for p in PHASES]
    environment = dict(os.environ, LC_ALL='C')

    def compile_one(task):
        source, mode, phase = task
        command = ['nice', '-n', '10', args.cc, '-' + mode, *flags]
        command += ['-fsyntax-only'] if phase == 'syntax' else ['-S', '-o', os.devnull]
        result = subprocess.run([*command, source], cwd=root, env=environment, capture_output=True, text=True)
        return task, result.returncode, result.stderr

    diagnostics, failures = [], []
    with ThreadPoolExecutor(max_workers=max(1, min(args.jobs, 4))) as pool:
        for index, (task, returncode, log) in enumerate(pool.map(compile_one, tasks), 1):
            source, mode, phase = task
            rows = parse_diagnostics(log, root, port, source, mode, phase)
            diagnostics.extend(rows)
            if returncode:
                logs = out / 'failed_logs'
                logs.mkdir(exist_ok=True)
                name = hashlib.sha256('\0'.join(task).encode()).hexdigest()[:20] + '.log'
                (logs / name).write_text(sanitize(log, root, port))
                first = next((r['file'] + ':' + str(r['line']) + ': ' + r['message']
                              for r in rows if r['severity'] != 'warning'),
                             sanitize(log, root, port).splitlines()[0] if log else '(no diagnostic)')
                failures.append(dict(tu=source, mode=mode, phase=phase, returncode=returncode,
                                     first_error=first, log='failed_logs/' + name))
            if index % 1000 == 0:
                print(f'{index}/{len(tasks)} compiler jobs complete', file=sys.stderr, flush=True)

    findings = group_findings(diagnostics)
    write_tsv(out / 'lint_findings.tsv', ['finding', 'file', 'function', 'warning', 'subsystem',
              'count', 'tu_count', 'modes', 'phases', 'sites', 'messages'], findings)
    totals = counts(findings)
    write_tsv(out / 'lint_counts.tsv', ['warning', 'subsystem', 'findings'],
              [dict(warning=w, subsystem=s, findings=n)
               for s, classes in totals['by_subsystem'].items() for w, n in classes.items()])
    write_tsv(out / 'lint_compile_failures.tsv', ['tu', 'mode', 'phase', 'returncode', 'first_error', 'log'], failures)
    summary = dict(schema_version=1, compiler=version, units=len(selected), compiler_jobs=len(tasks),
                   failed_jobs=len(failures), modes=list(MODES), phases=list(PHASES),
                   jobs=max(1, min(args.jobs, 4)), limited=bool(args.only),
                   flags=[sanitize(f, root, port) for f in flags],
                   native_builder_sha256=hashlib.sha256((port / 'tools/build.py').read_bytes()).hexdigest(),
                   source_repairs_applied=False, **totals)
    (out / 'lint_summary.json').write_text(json.dumps(summary, indent=2) + '\n')
    print(format_summary(summary) if args.summary else format_summary(summary).splitlines()[0])
    problems = check_baseline(summary, baseline) if args.check else []
    if failures:
        problems.append('compiler jobs failed; see lint_compile_failures.tsv and failed_logs/')
    if args.write_baseline and not failures:
        args.baseline.write_text(json.dumps(baseline_record(summary), indent=2) + '\n')
        print('Baseline written: ' + str(args.baseline))
    for problem in problems:
        print(problem, file=sys.stderr)
    if args.check and not problems:
        print('Baseline check passed')
    return int(bool(problems))


if __name__ == '__main__':
    sys.exit(main())
