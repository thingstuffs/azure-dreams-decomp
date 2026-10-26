#!/usr/bin/env python3
"""Compile registered game C for callback warnings and GCC cross-unit LTO types.

Uses the existing lint census and port flag parser; does not execute the builder.
A partial or failed census cannot establish or pass a baseline.
"""
from __future__ import annotations
import argparse
import collections
from concurrent.futures import ThreadPoolExecutor
import hashlib
from functools import lru_cache
import json
import os
from pathlib import Path
import re
import subprocess
import sys

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import lint_build as lint
from headers import cscan

CLASSES = ('-Wcast-function-type', '-Wincompatible-function-pointer-types',
           '-Wcast-function-type-strict', '-Wlto-type-mismatch', '-Wodr', 'lto-symbol-kind')



@lru_cache(maxsize=None)
def source_items(root, relative):
    """Recover declaration/function ownership when Clang omits GCC's context line."""
    path = root / relative
    if not relative.startswith(('src/', 'include/')) or not path.is_file():
        return []
    return cscan.scan(path.read_text()).items


def locate_function(root, row):
    if row['function'] != '<global>':
        return
    for item in source_items(root, row['file']):
        if item.line <= row['line'] <= item.end_line:
            if item.kind == 'def' and item.decls:
                row['function'] = item.decls[0].name
            elif item.kind == 'decl' and item.decls:
                row['function'] = '<global:' + ','.join(d.name for d in item.decls) + '>'
            return


def identity(row):
    return (row['file'], row['function'], row['warning'], row['message'])


def compare(current, baseline):
    problems = []
    if current['limited'] or current['failures']:
        problems.append('a complete census and zero failed commands are required')
    for key in ('schema', 'compiler', 'mode', 'flags', 'unit_digest', 'units'):
        if current.get(key) != baseline.get(key):
            problems.append('incomparable baseline: ' + key)
    previous = {tuple(row) for row in baseline.get('identities', [])}
    for row in current['identities']:
        if tuple(row) not in previous:
            problems.append('new diagnostic: ' + ' | '.join(row))
    previous_counts = {tuple(row[:4]): row[4] for row in baseline.get('identity_counts', [])}
    for row in current.get('identity_counts', []):
        key, count = tuple(row[:4]), row[4]
        if key in previous and count > previous_counts.get(key, 0):
            problems.append('additional diagnostic occurrences: ' + ' | '.join(key))
    return problems


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--root', type=Path, default=HERE.parents[1])
    ap.add_argument('--port', type=Path, required=True)
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--cc', default='gcc')
    ap.add_argument('--mode', choices=('callbacks', 'lto'), default='lto')
    ap.add_argument('--jobs', type=int, default=4)
    ap.add_argument('--only', nargs='+')
    ap.add_argument('--baseline', type=Path)
    action = ap.add_mutually_exclusive_group()
    action.add_argument('--check', action='store_true')
    action.add_argument('--write-baseline', action='store_true')
    args = ap.parse_args(argv)
    if (args.check or args.write_baseline) and (args.only or not args.baseline):
        ap.error('baseline actions require --baseline and a complete census')
    root, port, out = args.root.resolve(), args.port.resolve(), args.out.resolve()
    try:
        available = lint.units(root)
        selected = sorted(set(args.only)) if args.only else sorted(available)
        if not selected or set(selected) - available.keys():
            raise ValueError('empty or unregistered TU selection')
        compiler = subprocess.check_output([args.cc, '--version'], text=True).splitlines()[0]
        clang = 'clang' in compiler.lower()
        if clang and args.mode == 'lto':
            raise ValueError('LTO mode requires GCC; use clang for callback mode')
        flags = [f for f in lint.native_flags(port, root)
                 if not f.startswith('-W') and not f.startswith('-O') and f != '-fmax-errors=0']
        flags += ['-m32', '-O1', '-fwrapv']
        flags += (['-Wcast-function-type-strict', '-Wincompatible-function-pointer-types',
                   '-Wno-error=incompatible-function-pointer-types',
                   '-Wno-error=int-conversion', '-Wno-error=incompatible-pointer-types',
                   '-Wno-error=implicit-function-declaration', '-Wno-error=return-type']
                  if clang else ['-Wcast-function-type'])
        if args.mode == 'lto':
            flags += ['-flto', '-Wlto-type-mismatch', '-Wodr']
        prior = json.loads(args.baseline.read_text()) if args.check else None
    except (OSError, ValueError, subprocess.CalledProcessError) as exc:
        ap.error(str(exc))
    out.mkdir(parents=True, exist_ok=True)
    (out / '.ignore').write_text('*\n')
    logs = out / 'logs'
    logs.mkdir(exist_ok=True)
    objects = out / 'objects'
    objects.mkdir(exist_ok=True)
    environment = dict(os.environ, LC_ALL='C')

    def run(command):
        p = subprocess.run(['nice', '-n', '10', *command], cwd=root,
                           env=environment, capture_output=True, text=True)
        return p.returncode, lint.sanitize(p.stderr, root, port)

    def compile_one(item):
        index, source = item
        obj = objects / (str(index) + '.o')
        command = [args.cc, *flags]
        command += ['-c', '-o', str(obj)] if args.mode == 'lto' else ['-fsyntax-only']
        code, log = run([*command, source])
        return source, obj, code, log

    findings, failures, good = [], [], []
    # Consume every result; retain failure diagnostics even when other units pass.
    with ThreadPoolExecutor(max_workers=max(1, min(4, args.jobs))) as pool:
        for index, result in enumerate(pool.map(compile_one, enumerate(selected))):
            source, obj, code, log = result
            if log:
                (logs / (str(index) + '.txt')).write_text(log)
            if code:
                failures.append(dict(stage='compile', source=source, returncode=code,
                                     log='logs/' + str(index) + '.txt'))
            else:
                good.append(obj)
            findings += lint.parse_diagnostics(log.replace('$ROOT', str(root)).replace('$PORT', str(port)),
                                               root, port, source, 'm32', args.mode)
            if (index + 1) % 250 == 0:
                print(f'{index + 1}/{len(selected)} units; {len(failures)} failures', flush=True)
    if args.mode == 'lto' and good:
        # A response file avoids ARG_MAX. Never allow duplicate definitions: they
        # are link failures, not evidence of a successful whole-program check.
        response = out / 'objects.rsp'
        response.write_text('\n'.join('"' + str(p).replace('\\', '\\\\').replace('"', '\\"') + '"' for p in good) + '\n')
        code, log = run([args.cc, '-m32', '-O1', '-flto=' + str(max(1, min(4, args.jobs))), '-fwrapv', '-Wlto-type-mismatch',
                         '-Wodr', '-nostdlib', '-r', '-flinker-output=nolto-rel',
                         '@' + str(response), '-o', str(out / 'linked.o')])
        (logs / 'link.txt').write_text(log)
        if code:
            failures.append(dict(stage='link', source='<all>', returncode=code, log='logs/link.txt'))
        findings += lint.parse_diagnostics(log.replace('$ROOT', str(root)).replace('$PORT', str(port)),
                                           root, port, '<link>', 'm32', 'link')
    unique = {}
    counts = collections.Counter()
    for row in findings:
        if clang:
            locate_function(root, row)
        if (row['phase'] == 'link' and row['severity'] == 'error'
                and re.search(r'(?:function|variable) .+ redeclared as (?:variable|function)', row['message'])):
            row['warning'] = 'lto-symbol-kind'
        if row['warning'] in CLASSES and row['severity'] in ('warning', 'error'):
            counts[identity(row)] += 1
            unique.setdefault(identity(row), row)
    rows = [unique[k] for k in sorted(unique)]
    normalized = [list(identity(row)) for row in rows]
    summary = dict(schema=2, compiler=compiler, mode=args.mode,
                   flags=[lint.sanitize(f, root, port) for f in flags],
                   unit_digest=hashlib.sha256('\n'.join(selected).encode()).hexdigest(),
                   units=len(selected), limited=bool(args.only), failures=len(failures),
                   by_class={c: sum(r['warning'] == c for r in rows) for c in CLASSES},
                   by_class_occurrences={c: sum(n for key, n in counts.items() if key[2] == c)
                                         for c in CLASSES},
                   identities=normalized,
                   identity_counts=[list(key) + [counts[key]] for key in sorted(counts)])
    lint.write_tsv(out / 'findings.tsv', ['file', 'function', 'line', 'column', 'severity',
                   'message', 'warning', 'tu', 'mode', 'phase'], rows)
    lint.write_tsv(out / 'failures.tsv', ['stage', 'source', 'returncode', 'log'], failures)
    (out / 'summary.json').write_text(json.dumps(summary, indent=2) + '\n')
    print(json.dumps({k: v for k, v in summary.items() if k != 'identities'}, indent=2))
    problems = compare(summary, prior) if args.check else []
    if args.write_baseline:
        if summary['limited'] or failures:
            problems.append('refusing baseline from partial or failed census')
        else:
            args.baseline.write_text(json.dumps(summary, indent=2) + '\n')
    for problem in problems:
        print(problem, file=sys.stderr)
    return int(bool(failures or problems))


if __name__ == '__main__':
    sys.exit(main())
