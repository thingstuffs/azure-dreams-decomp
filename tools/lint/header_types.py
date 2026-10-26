#!/usr/bin/env python3
"""Compile reviewed aggregate header groups together; every group must be clean.

Separate TUs can hide a function/data contradiction when unused externs disappear
from LTO. Joining their existing owner headers exposes that contradiction to the
ordinary C compiler without changing game sources or synthesizing prototypes.
"""
from __future__ import annotations
import argparse
import json
import re
from pathlib import Path
import subprocess
import sys

HERE = Path(__file__).resolve().parent


def check(root, compiler, headers, aliases=()):
    source = ''.join('#include "' + name.removeprefix('include/') + '"\n' for name in headers)
    for pair in aliases:
        alias, target = pair['alias'], pair['target']
        source += ('_Static_assert(__builtin_types_compatible_p('
                   '__typeof__(' + target + '), __typeof__(*' + target + ')), '
                   '"' + target + ' must be a function");\n')
        source += ('_Static_assert(__builtin_types_compatible_p('
                   '__typeof__(' + alias + '), __typeof__(' + target + ')), '
                   '"' + alias + ' must match ' + target + '");\n')
    command = [compiler, '-m32', '-fwrapv', '-DM2CTX', '-DNON_MATCHING', '-w',
               '-I', str(root / 'include'), '-x', 'c', '-fsyntax-only', '-']
    result = subprocess.run(['nice', '-n', '10', *command], cwd=root,
                            input=source, capture_output=True, text=True)
    return dict(returncode=result.returncode,
                diagnostic=result.stderr.replace(str(root), '$ROOT'))


def main(argv=None):
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--root', type=Path, default=HERE.parents[1])
    p.add_argument('--groups', type=Path, default=HERE / 'header_type_groups.json')
    p.add_argument('--cc', nargs='+', default=['gcc', 'clang'])
    p.add_argument('--out', type=Path)
    a = p.parse_args(argv)
    root = a.root.resolve()
    groups = json.loads(a.groups.read_text())
    if groups.get('schema') != 1 or not groups.get('groups'):
        p.error('expected a nonempty schema-1 header group document')
    results = []
    for group in groups['groups']:
        headers = group['headers']
        if not headers:
            p.error('empty header group: ' + group['id'])
        for header in headers:
            path = root / header
            if not header.startswith('include/') or not path.resolve().is_relative_to(root / 'include') or not path.is_file():
                p.error('invalid header: ' + header)
        aliases = group.get('aliases', [])
        for pair in aliases:
            if (not isinstance(pair, dict) or set(pair) != {'alias', 'target'}
                    or any(not isinstance(name, str) or not re.fullmatch(r'[A-Za-z_]\w*', name)
                           for name in pair.values())):
                p.error('invalid code alias in group: ' + group['id'])
        for compiler in a.cc:
            result = check(root, compiler, headers, aliases)
            results.append(dict(group=group['id'], compiler=compiler, **result))
    report = dict(groups=len(groups['groups']), checks=len(results),
                  failures=sum(bool(r['returncode']) for r in results), results=results)
    if a.out:
        a.out.parent.mkdir(parents=True, exist_ok=True)
        a.out.write_text(json.dumps(report, indent=2) + '\n')
    for row in results:
        if row['returncode']:
            print(row['compiler'] + ': ' + row['group'] + ':\n' + row['diagnostic'], file=sys.stderr)
    print(json.dumps({k: report[k] for k in ('groups', 'checks', 'failures')}))
    return int(bool(report['failures']))


if __name__ == '__main__':
    sys.exit(main())
