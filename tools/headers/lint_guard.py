#!/usr/bin/env python3
"""Native-lint guard for declaration waves: which edited TUs gain a lint finding group?

    lint_guard.py --port <port>/port --base <rev> [--files F...] [--out DIR]

A wave that replaces a TU's own declaration with the owner's prototype can stay byte-identical and still
make the native port compile warn (an int passed where the prototype takes a pointer, a struct pointer
where it takes char *).  tools/lint/lint_build.py --check is census-wide; this compares only the edited
TUs: lint_build --only <files> on a detached worktree of <rev> and on the root, keyed (file, function,
warning class).  Exit 1 lists the TUs with a new group (restore their edit or type the site first).
Default files: the .c files `git diff --name-only <rev>` reports under src/.
--restore puts those TUs back to <rev> and drops, from the append block (APPEND_MARK) of every header edited
since <rev>, the prototypes of names a restored TU still declares itself (it would conflict with them).
Re-run the batch proof afterwards.
"""
from __future__ import annotations

import argparse
import csv
import os
import subprocess
import sys
import tempfile
from pathlib import Path


def findings(root, port, files, out):
    env = dict(os.environ, JOBS=os.environ.get('JOBS', '4'))
    res = subprocess.run(['nice', '-n', '10', sys.executable, str(Path(__file__).resolve().parents[1] / 'lint/lint_build.py'),
                          '--root', str(root), '--port', str(port), '--out', str(out), '--only', *files],
                         env=env, capture_output=True, text=True)
    path = Path(out) / 'lint_findings.tsv'
    if not path.is_file():
        raise SystemExit('lint_build produced no findings table under %s:\n%s' % (out, (res.stdout + res.stderr)[-1500:]))
    rows = list(csv.reader(path.open(), delimiter='\t'))
    return {tuple(r[1:4]) for r in rows[1:] if len(r) > 3}


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', default='.')
    ap.add_argument('--port', required=True)
    ap.add_argument('--base', required=True)
    ap.add_argument('--files', nargs='*')
    ap.add_argument('--out')
    ap.add_argument('--restore', action='store_true')
    a = ap.parse_args()
    root = Path(a.root).resolve()
    files = a.files or [f for f in subprocess.run(['git', '-C', str(root), 'diff', '--name-only', a.base, '--', 'src'],
                                                    capture_output=True, text=True).stdout.split() if f.endswith('.c')]
    files = [f for f in files if (root / f).is_file()]
    # lint_build checks registered physical TUs only (merged members compile through their owner)
    sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'lint'))
    sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
    import lint_build
    registered = lint_build.units(root)
    skipped = [f for f in files if f not in registered]
    files = [f for f in files if f in registered]
    if skipped:
        print('not registered TUs (not linted): %d' % len(skipped))
    if not files:
        print('no edited .c files')
        return 0
    out = Path(a.out or tempfile.mkdtemp(prefix='lint_guard_')).resolve()
    out.mkdir(parents=True, exist_ok=True)
    wt = out / 'base_tree'
    subprocess.run(['git', '-C', str(root), 'worktree', 'add', '--detach', '-f', str(wt), a.base],
                   check=True, capture_output=True)
    try:
        before = findings(wt, a.port, [f for f in files if (wt / f).is_file()], out / 'before')
    finally:
        subprocess.run(['git', '-C', str(root), 'worktree', 'remove', '--force', str(wt)], capture_output=True)
    after = findings(root, a.port, files, out / 'after')
    new = sorted(after - before)
    for f, fn, cls in new:
        print('NEW\t%s\t%s\t%s' % (f, fn, cls))
    print('%d edited TUs; lint groups %d -> %d; new %d' % (len(files), len(before), len(after), len(new)))
    if new and a.restore:
        restore(root, a.base, sorted({f for f, _, _ in new}))
    return 1 if new else 0


def restore(root, base, tus):
    """Put `tus` back to `base`; drop from the append blocks of the headers edited since `base` the names a
    restored TU declares itself (it would conflict); restore, in turn, every other edited TU that had dropped
    its own declaration of a trimmed name (it relied on the appended prototype).  Repeats to a fixpoint."""
    import re
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    from rewrite import APPEND_MARK
    decl = re.compile(r'^[^#\n{}=]*?\b([A-Za-z_]\w*)\s*\([^;{}]*\)\s*;', re.M)

    def git(*a):
        return subprocess.run(['git', '-C', str(root), *a], capture_output=True, text=True).stdout

    def names(text):
        return set(decl.findall(text))

    restored, trimmed = set(), set()
    todo = set(tus)
    while todo:
        subprocess.run(['git', '-C', str(root), 'checkout', base, '--', *sorted(todo)], check=True)
        restored |= todo
        local = set()
        for f in restored:
            local |= names((root / f).read_text(errors='replace'))
        for h in git('diff', '--name-only', base, '--', 'include').split():
            text = (root / h).read_text()
            at = text.find(APPEND_MARK)
            if at < 0:
                continue
            head, lines = text[:at], text[at:].split('\n')
            drop = [l for l in lines[1:] if decl.match(l) and decl.match(l).group(1) in local]
            if not drop:
                continue
            trimmed |= {decl.match(l).group(1) for l in drop}
            kept = [l for l in lines if l not in drop]
            if any(decl.match(l) or l.startswith('#include') for l in kept[1:]):
                new = head + '\n'.join(kept)
            else:
                new = re.sub(r'\n{3,}', '\n\n', head.rstrip('\n') + '\n\n#endif\n')
            (root / h).write_text(new)
            print('trimmed', h, ' '.join(sorted({decl.match(l).group(1) for l in drop})))
        todo = set()
        for f in git('diff', '--name-only', base, '--', 'src').split():
            if f in restored or not f.endswith('.c'):
                continue
            before = names(git('show', '%s:%s' % (base, f)))
            now = names((root / f).read_text(errors='replace'))
            if (before - now) & trimmed:
                todo.add(f)
    for f in sorted(restored):
        print('restored', f)
