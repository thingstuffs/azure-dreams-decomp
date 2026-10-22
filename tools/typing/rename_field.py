#!/usr/bin/env python3
"""Rename one field of one shared struct everywhere the compiler sees it (decision 73: ActorRecord.unk_58 ->
previous_actor_header once every reader is typed).

    rename_field.py --header include/shared/entity.h --struct ActorRecord --field unk_58 --to previous_actor_header
                    [--check] [--receipt R.jsonl] [--workers N]

The header's field declaration is renamed first; every registered physical TU whose include closure holds the
header is then parsed by clang (-fsyntax-only, mipsel target, the same include path as tu_identity's
dependency scan).  Each "no member named '<field>' in '<struct>'" diagnostic names one access site of THAT
struct (an untyped or differently typed access never produces it), and only that token is rewritten.  Parsing
repeats until no TU reports the old name.  A diagnostic inside a generated stream (SLUS partitions) or any
other error stops the run and restores every file.  Object identity is proven separately with
tools/typing/tu_identity.py (snapshot before, compare after): a pure rename leaves every object unchanged.

--check reports the header state and the sites without writing.
"""
from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

HERE = Path(__file__).resolve().parent
TOOLS = HERE.parent
sys.path[:0] = [str(TOOLS), str(HERE)]


def header_field_span(text, struct, field):
    """(start, end) of the field's declarator token inside the struct definition, or None."""
    ends = [m for m in re.finditer(r"\}\s*" + re.escape(struct) + r"\s*;", text)]
    starts = [m for m in re.finditer(r"\bstruct\s+" + re.escape(struct) + r"\s*\{", text)]
    spans = []
    for m in ends:  # typedef struct [tag] { ... } NAME;  -> the nearest preceding `typedef struct`
        k = text.rfind("typedef struct", 0, m.start())
        if k >= 0:
            spans.append((text.index("{", k) + 1, m.start()))
    for m in starts if not spans else ():
        e = text.find("};", m.end())
        if e >= 0:
            spans.append((m.end(), e))
    for lo, hi in spans:
        body = text[lo:hi]
        # the declarator token only (a field name inside a comment is not the field)
        hits = list(re.finditer(r"\b" + re.escape(field) + r"\b(?=\s*(\[[^\]]*\]\s*)*(:\s*\d+\s*)?;)", body))
        if len(hits) == 1:
            return lo + hits[0].start(), lo + hits[0].end()
        if len(hits) > 1:
            raise SystemExit("field %s appears %d times in %s" % (field, len(hits), struct))
    return None


def _diag(args):
    root, rel, field, struct = args
    res = subprocess.run(['clang', '--target=mipsel-unknown-none', '-w', '-fsyntax-only', '-ferror-limit=0',
                          '-I', 'include', rel], cwd=root, capture_output=True, text=True)
    sites, other = [], []
    pat = re.compile(r"^(?P<file>[^:\n]+):(?P<line>\d+):(?P<col>\d+): error: no member named '" + re.escape(field)
                     + r"' in '(?:struct )?(?P<type>[^']+)'", re.M)
    for m in pat.finditer(res.stderr):
        if m.group("type") in (struct, "struct " + struct):
            sites.append((m.group("file"), int(m.group("line")), int(m.group("col"))))
        else:
            other.append(m.group(0))
    errs = [l for l in res.stderr.splitlines() if ": error:" in l and not pat.match(l)]
    other.extend(errs)
    return rel, sites, other


def consumers(root, header):
    import layout_compile_identity as LCI
    from tu_identity import proof_set
    physical, _ = LCI.recipes(root)
    tus, _ = proof_set(root, [header], physical, workers=6)
    return tus, physical


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=TOOLS.parent)
    ap.add_argument('--header', required=True)
    ap.add_argument('--struct', required=True)
    ap.add_argument('--field', required=True)
    ap.add_argument('--to', required=True)
    ap.add_argument('--check', action='store_true')
    ap.add_argument('--receipt', type=Path)
    ap.add_argument('--workers', type=int, default=4)
    ap.add_argument('--tu', nargs='*', default=None, help='explicit consumer TUs (skip closure discovery)')
    args = ap.parse_args(argv)
    root = args.root.resolve()
    hp = root / args.header
    htext = hp.read_text()
    span = header_field_span(htext, args.struct, args.field)
    done = header_field_span(htext, args.struct, args.to)
    if span is None and done is not None:
        print(json.dumps({'state': 'already', 'struct': args.struct, 'field': args.to}))
        return 0
    if span is None:
        print(json.dumps({'state': 'refused', 'reason': 'struct %s has no field %s in %s' % (args.struct, args.field, args.header)}))
        return 2
    tus = args.tu if args.tu is not None else consumers(root, args.header)[0]
    tus = [t for t in tus if (root / t).is_file()]
    with ProcessPoolExecutor(max_workers=args.workers) as ex:
        base = {rel: set(oo) for rel, _, oo in ex.map(_diag, [(str(root), t, args.field, args.struct) for t in tus])}
    saved = {args.header: htext}
    hp.write_text(htext[:span[0]] + args.to + htext[span[1]:])
    edits = []
    try:
        for rnd in range(8):
            with ProcessPoolExecutor(max_workers=args.workers) as ex:
                results = list(ex.map(_diag, [(str(root), t, args.field, args.struct) for t in tus]))
            sites = sorted({s for _, ss, _ in results for s in ss})
            other = [(rel, o) for rel, _, oo in results for o in oo if o not in base.get(rel, set())]
            if other:
                raise RuntimeError('other diagnostics: %s' % other[:8])
            if not sites:
                break
            byfile = {}
            for f, line, col in sites:
                p = Path(f) if Path(f).is_absolute() else root / f
                p = p.resolve()
                if not p.is_relative_to(root) or not (p.relative_to(root).parts[0] in ('src', 'include')):
                    raise RuntimeError('site outside src/include: %s' % f)
                byfile.setdefault(p, []).append((line, col))
            for p, locs in byfile.items():
                rel = p.relative_to(root).as_posix()
                if rel not in saved:
                    saved[rel] = p.read_text()
                lines = p.read_text().split('\n')
                for line, col in sorted(set(locs), reverse=True):
                    s = lines[line - 1]
                    i = col - 1
                    if s[i:i + len(args.field)] != args.field:
                        raise RuntimeError('diagnostic column does not hold the field token: %s:%d:%d' % (rel, line, col))
                    lines[line - 1] = s[:i] + args.to + s[i + len(args.field):]
                    edits.append(dict(file=rel, line=line, col=col, round=rnd))
                p.write_text('\n'.join(lines))
        else:
            raise RuntimeError('sites still reported after 8 rounds')
    except Exception as exc:
        for rel, t in saved.items():
            (root / rel).write_text(t)
        print(json.dumps({'state': 'refused', 'reason': str(exc)[:2000], 'restored': sorted(saved)}))
        return 1
    if args.check:
        for rel, t in saved.items():
            (root / rel).write_text(t)
    out = {'state': 'checked' if args.check else 'renamed', 'struct': args.struct, 'field': args.field, 'to': args.to,
           'consumer_tus': len(tus), 'sites': len(edits), 'files': sorted({e['file'] for e in edits} | {args.header})}
    if args.receipt:
        args.receipt.write_text(json.dumps(dict(out, edits=edits), indent=1) + '\n')
    print(json.dumps(out))
    return 0


if __name__ == '__main__':
    sys.exit(main())
