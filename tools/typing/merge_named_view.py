#!/usr/bin/env python3
"""Merge a NAMED per-file view (e.g. PersonObject) into its canonical shared type, respelling member paths.

    merge_named_view.py --view PersonObject --into TownObjectRecord --header include/shared/town_object.h \
        --map timer=timer.as_s16 heading=heading.as_s16 ... [--files F...] [--check]

layout_swap.py refuses views that other headers name (`named_in_other_header`) and only plans generated
`S_<addr>` views.  A named view that a census has shown to be the same object at delta 0 (same offsets, same
leaf types) is merged here instead:

  1. every token `View` in the files that use it becomes `Type` (`struct View` too); the view's typedef is
     removed from its defining header (pass --keep-typedef to leave it);
  2. each file is parsed with clang (-fsyntax-only, mipsel, -I include); every
     "no member named 'm' in 'Type'" diagnostic is one access through the old view: its token `m` is rewritten
     to the mapped path (--map m=path, path may descend into a union leaf);  unmapped members, or any other new
     diagnostic, restore every file and exit 2;
  3. byte identity is NOT proven here: run tools/lanes/prove_batch.sh (affected.py prove) on the result.
The mapping is the judgement (one line per member, from the view's typedef and the canonical layout); the tool
only applies it where the compiler says the old name is used.
"""
import argparse, os, re, subprocess, sys, json
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor


def diag(root, rel):
    res = subprocess.run(['clang', '--target=mipsel-unknown-none', '-w', '-fsyntax-only', '-ferror-limit=0',
                          '-I', 'include', rel], cwd=root, capture_output=True, text=True)
    return [l for l in res.stderr.splitlines() if ': error:' in l]


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=Path('.'))
    ap.add_argument('--view', required=True)
    ap.add_argument('--into', required=True)
    ap.add_argument('--map', nargs='*', default=[])
    ap.add_argument('--files', nargs='*', default=None)
    ap.add_argument('--keep-typedef', action='store_true')
    ap.add_argument('--check', action='store_true')
    # Members whose names also exist in the canonical type with another type must be renamed in the view first
    # (rename_field.py --struct VIEW --field m --to m__view) so the compiler reports them as missing.
    a = ap.parse_args(argv)
    root = a.root.resolve()
    mapping = dict(m.split('=', 1) for m in a.map)
    tok = re.compile(r'\b' + re.escape(a.view) + r'\b')
    if a.files is None:
        files = []
        for top in ('src', 'include'):
            for d, _, names in os.walk(root / top):
                for n in names:
                    p = Path(d) / n
                    if p.suffix in ('.c', '.h') and p.stat().st_size < 4 << 20 and tok.search(p.read_text(errors='replace')):
                        files.append(p.relative_to(root).as_posix())
        files.sort()
    else:
        files = a.files
    saved = {f: (root / f).read_text() for f in files}
    cfiles = [f for f in files if f.endswith('.c')]
    # a pre-existing diagnostic that only changes the type's spelling is not new
    base = {f: {e.replace(a.view, a.into) for e in diag(root, f)} for f in cfiles}
    typedef = re.compile(r'typedef struct ' + re.escape(a.view) + r'\s*\{[^{}]*?\}\s*' + re.escape(a.view) + r'\s*;\n?',
                         re.S)
    edits = []
    try:
        for f in files:
            t = saved[f]
            if not a.keep_typedef:
                t = typedef.sub('', t)
            t = tok.sub(a.into, t)
            (root / f).write_text(t)
        miss = re.compile(r"^(?P<f>[^:]+):(?P<l>\d+):(?P<c>\d+): error: no member named '(?P<m>\w+)' in '(?:struct )?"
                          + re.escape(a.into) + r"'")
        for rnd in range(6):
            with ThreadPoolExecutor(max_workers=6) as ex:
                results = dict(zip(cfiles, ex.map(lambda f: diag(root, f), cfiles)))
            sites, other = [], []
            for f, errs in results.items():
                lines_hit = set()
                for e in errs:
                    m = miss.match(e)
                    if m:
                        sites.append((m.group('f'), int(m.group('l')), int(m.group('c')), m.group('m')))
                        lines_hit.add((m.group('f'), int(m.group('l'))))
                for e in errs:
                    if miss.match(e) or e in base[f]:
                        continue
                    m2 = re.match(r'^([^:]+):(\d+):', e)
                    if m2 and (m2.group(1), int(m2.group(2))) in lines_hit:
                        continue  # typo-correction cascade on a rename line
                    other.append(e)
            if other:
                raise RuntimeError('new diagnostics: ' + json.dumps(sorted(set(other))[:10]))
            if not sites:
                break
            unmapped = sorted({s[3] for s in sites if s[3] not in mapping})
            if unmapped:
                raise RuntimeError('unmapped members: ' + ', '.join(unmapped))
            byfile = {}
            for f, l, c, m in sites:
                byfile.setdefault(f, set()).add((l, c, m))
            for f, locs in byfile.items():
                p = (root / f).resolve()
                rel = p.relative_to(root).as_posix()
                if rel not in saved:
                    saved[rel] = p.read_text()
                lines = p.read_text().split('\n')
                for l, c, m in sorted(locs, reverse=True):
                    s = lines[l - 1]
                    if s[c - 1:c - 1 + len(m)] != m:
                        raise RuntimeError('column does not hold %s: %s:%d:%d' % (m, rel, l, c))
                    lines[l - 1] = s[:c - 1] + mapping[m] + s[c - 1 + len(m):]
                    edits.append(dict(file=rel, line=l, col=c, member=m, to=mapping[m]))
                p.write_text('\n'.join(lines))
        else:
            raise RuntimeError('did not converge')
    except Exception as exc:
        for f, t in saved.items():
            (root / f).write_text(t)
        print(json.dumps({'state': 'refused', 'reason': str(exc)}))
        return 2
    if a.check:
        for f, t in saved.items():
            (root / f).write_text(t)
    print(json.dumps({'state': 'checked' if a.check else 'applied', 'files': len(files), 'edits': len(edits)}))
    return 0


if __name__ == '__main__':
    sys.exit(main())
