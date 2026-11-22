#!/usr/bin/env python3
"""Batch member rename: many `record.old_member -> new_member` renames in one parse of the tree.

    rename_members_batch.py --rows ROWS.tsv [--rows MORE.tsv ...] [--record R] [--default-header H]
                            [--dry-run] [--report REPORT.tsv] [--workers N] [--tu T ...]

Single mode (rename_field.py) renames one member per invocation and re-parses every consumer TU each time.
This tool takes the whole row set, parses the consumer TUs once per round and resolves every access the same
way the single mode does: the declarators are renamed in the headers, clang (-fsyntax-only, mipsel target)
is run over each consumer TU, and each "no member named '<old>' in '<record>'" diagnostic names an access
site of THAT record only (a same-named member of another record never produces one), so only that token is
rewritten.  Typedef aliases of the record resolve to the record in the diagnostic; an access inside a macro
body or a macro argument is rewritten at its spelling location (the "expanded from macro" note), and a
designated initializer `.old = x` is rewritten too.

Input rows (TSV with a header line; '#' lines and blank lines ignored).  Columns, by name:
    record | header | old_member (old) | new_member (new, new_name) | offset (optional, 0x.. byte offset to check)
Member-pack rows (action/type/confidence columns) are accepted as they are: only action=rename with type '-'
and confidence proven/likely is applied, every other row is reported as skipped.  `--record` and
`--default-header` fill a column a file does not have (the ActorRecord rename table has neither).

A row is refused (never applied, reason in the report) when: the header or record is not found; the old member
is absent from the record or sits at another offset than the row says; the new name is not an identifier, is
already a member of the record, or is the old name of another row; two rows name the same member or the same
new name; or applying it makes the compiler report an error the rename cannot explain (the row is dropped
and the batch is re-run without it).  An unexplained error that names no row aborts the whole run and
restores every file.  Files are written with temp-file + rename and restored the same way.

--dry-run does everything but leaves the tree as it found it and prints per-row site counts.
The report TSV has one line per row: record header old_member new_member offset status sites macro_sites
uses files detail.
    sites        distinct token locations rewritten (macro bodies counted once), the declarator excluded
    macro_sites  the part of `sites` that lies inside a macro definition
    uses         distinct access locations the compiler reported (macro expansions counted each)
"""
from __future__ import annotations

import argparse
import csv
import json
import os
import re
import subprocess
import sys
import tempfile
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

HERE = Path(__file__).resolve().parent
TOOLS = HERE.parent
sys.path[:0] = [str(TOOLS), str(HERE)]

from rename_field import header_field_span  # noqa: E402  (the same declarator resolution as single mode)

IDENT = re.compile(r'^[A-Za-z_][A-Za-z0-9_]*$')
REPORT_COLS = ['record', 'header', 'old_member', 'new_member', 'offset', 'status', 'sites', 'macro_sites',
               'uses', 'files', 'detail']
ERR_HEAD = re.compile(r'^(?P<file>[^:\n]+):(?P<line>\d+):(?P<col>\d+): error: ', re.M)
NOTE_MACRO = re.compile(r'^(?P<file>[^:\n]+):(?P<line>\d+):(?P<col>\d+): note: expanded from macro', re.M)
NO_MEMBER = re.compile(r"no member named '(?P<f>\w+)' in '(?:struct |union )?(?P<t>\w+)'")
DESIGNATOR = re.compile(r"field designator '(?P<f>\w+)' does not refer to any field in type '(?:struct |union )?(?P<t>\w+)'")


class Row:
    def __init__(self, record, header, old, new, offset=None, src=''):
        self.record, self.header, self.old, self.new = record, header, old, new
        self.offset = offset  # int or None
        self.status = 'pending'
        self.detail = ''
        self.sites = set()      # (file, line, col) spelling locations
        self.macro_sites = set()
        self.uses = set()       # primary locations
        self.types = {record}   # type names clang may print for the record
        self.src = src

    def refuse(self, why):
        self.status = 'refused'
        self.detail = why

    def skip(self, why):
        self.status = 'skipped'
        self.detail = why


# ---------------------------------------------------------------- IO helpers (latin-1: columns stay byte columns)

def read_text(path):
    return Path(path).read_bytes().decode('latin-1')


def write_atomic(path, text):
    path = Path(path)
    fd, tmp = tempfile.mkstemp(prefix='.' + path.name + '.', dir=str(path.parent))
    try:
        with os.fdopen(fd, 'wb') as fh:
            fh.write(text.encode('latin-1'))
        os.chmod(tmp, path.stat().st_mode & 0o7777)
        os.replace(tmp, path)
    except BaseException:
        if os.path.exists(tmp):
            os.unlink(tmp)
        raise


# ---------------------------------------------------------------- input

def parse_int(s):
    s = (s or '').strip()
    if not s or s == '-':
        return None
    return int(s, 0)


def load_rows(paths, record=None, default_header=None):
    rows = []
    for path in paths:
        with open(path, newline='', encoding='utf-8') as fh:
            lines = [l for l in fh.read().splitlines() if l.strip() and not l.startswith('#')]
        if not lines:
            continue
        rd = csv.reader(lines, delimiter='\t', quoting=csv.QUOTE_NONE)
        head = next(rd)

        def col(*names):
            for n in names:
                if n in head:
                    return head.index(n)
            return None
        ir, ih = col('record', 'struct'), col('header')
        io, inw = col('old_member', 'old', 'field'), col('new_member', 'new_name', 'new', 'to')
        iof = col('offset')
        ia, it, ic, ik = col('action'), col('type'), col('confidence'), col('kind')
        if io is None or inw is None:
            raise SystemExit('%s: need old_member and new_member columns, got %s' % (path, head))
        for n, cells in enumerate(rd, 2):
            def cell(i):
                return cells[i].strip() if i is not None and i < len(cells) else ''
            rec = cell(ir) or record or ''
            hdr = cell(ih) or default_header or ''
            try:
                off = parse_int(cell(iof))
            except ValueError:
                off = None
            r = Row(rec, hdr, cell(io), cell(inw), off, '%s:%d' % (Path(path).name, n))
            if ia is not None and cell(ia) != 'rename':
                r.skip('action %s' % (cell(ia) or '?'))
            elif ik is not None and cell(ik) not in ('', 'rename'):
                r.skip('kind %s' % cell(ik))
            elif it is not None and cell(it) not in ('', '-'):
                r.skip('retype')
            elif ic is not None and cell(ic) not in ('proven', 'likely'):
                r.skip('confidence %s' % (cell(ic) or '?'))
            elif not rec or not hdr:
                r.refuse('record or header missing (use --record / --default-header)')
            elif not r.old or not r.new:
                r.refuse('empty member name')
            rows.append(r)
    return rows


# ---------------------------------------------------------------- header-level checks

def record_tags(text, record):
    """Struct tag(s) of the typedef that defines `record` (clang prints 'struct TAG' for a tagged typedef)."""
    tags = set()
    for m in re.finditer(r'\}\s*' + re.escape(record) + r'\s*;', text):
        k = text.rfind('typedef struct', 0, m.start())
        if k >= 0:
            t = re.match(r'typedef struct\s+(\w+)\s*\{', text[k:])
            if t:
                tags.add(t.group(1))
    return tags


def has_record(text, record):
    return bool(re.search(r'\}\s*' + re.escape(record) + r'\s*;', text)
                or re.search(r'\bstruct\s+' + re.escape(record) + r'\s*\{', text))


def check_rows(root, rows):
    """Static refusals: header, record, member presence, collisions.  Mutates row status."""
    texts = {}
    live = [r for r in rows if r.status == 'pending']
    for r in live:
        hp = root / r.header
        if r.header not in texts:
            texts[r.header] = read_text(hp) if hp.is_file() else None
        text = texts[r.header]
        if text is None:
            r.refuse('header not found')
            continue
        if not has_record(text, r.record):
            r.refuse('record %s not defined in %s' % (r.record, r.header))
            continue
        if not IDENT.match(r.new):
            r.refuse('new name is not an identifier')
            continue
        r.types |= record_tags(text, r.record)
        try:
            span = header_field_span(text, r.record, r.old)
            new_span = header_field_span(text, r.record, r.new)
        except SystemExit as exc:
            r.refuse(str(exc))
            continue
        if span is None:
            r.refuse('member %s absent from %s' % (r.old, r.record))
        elif new_span is not None:
            r.refuse('new name %s already a member of %s' % (r.new, r.record))
    # duplicates and chains inside one record
    groups = {}
    for r in rows:
        if r.status == 'pending':
            groups.setdefault((r.header, r.record), []).append(r)
    for grp in groups.values():
        olds, news = {}, {}
        for r in grp:
            olds.setdefault(r.old, []).append(r)
            news.setdefault(r.new, []).append(r)
        for r in grp:
            if len(olds[r.old]) > 1:
                r.refuse('two rows for member %s' % r.old)
            elif len(news[r.new]) > 1:
                r.refuse('two rows give the new name %s' % r.new)
            elif r.new in olds:
                r.refuse('new name %s is the old name of another row' % r.new)
    # one clang type name must identify one row key across headers
    seen = {}
    for r in rows:
        if r.status != 'pending':
            continue
        for t in r.types:
            seen.setdefault((r.old, t), []).append(r)
    for rs in seen.values():
        if len({(x.header, x.record) for x in rs}) > 1:
            for x in rs:
                if x.status == 'pending':
                    x.refuse('ambiguous: %s named %s is defined in several headers of the batch' % (x.record, x.old))
    return texts


def check_offsets(root, rows, workers=1):
    """Offset check by compiling `_Static_assert(offsetof(R, m) == off)`; a nested member that offsetof
    cannot name is reported as unverified in `detail`, not refused."""
    byheader = {}
    for r in rows:
        if r.status == 'pending' and r.offset is not None:
            byheader.setdefault(r.header, []).append(r)
    for header, rs in byheader.items():
        inc = header[len('include/'):] if header.startswith('include/') else None
        for r in rs:
            lines = ['#include "%s"' % inc] if inc else ['#include "%s"' % os.path.relpath(root / header, root)]
            lines.append('_Static_assert(__builtin_offsetof(%s, %s) == %d, "OFFSET_MISMATCH");' % (r.record, r.old, r.offset))
            res = subprocess.run(['clang', '--target=mipsel-unknown-none', '-w', '-fsyntax-only', '-x', 'c', '-',
                                  '-I', 'include', '-I', str(root / Path(header).parent)],
                                 input='\n'.join(lines), cwd=str(root), capture_output=True, text=True)
            if res.returncode == 0:
                continue
            if 'OFFSET_MISMATCH' in res.stderr or 'static assertion failed' in res.stderr \
                    or 'static_assert failed' in res.stderr:
                r.refuse('member %s is not at offset 0x%X' % (r.old, r.offset))
            else:
                r.detail = 'offset not verified (nested or not nameable by offsetof)'


# ---------------------------------------------------------------- compiler pass

def _norm(root, f):
    p = Path(f)
    p = p if p.is_absolute() else Path(root) / p
    return os.path.normpath(str(p))


def _holds(text_lines, line, col, field):
    """Column of the field token at line:col (or one right of a designator dot), else None."""
    if not (1 <= line <= len(text_lines)):
        return None
    s = text_lines[line - 1]
    i = col - 1
    if s[i:i + len(field)] == field and not (i + len(field) < len(s) and (s[i + len(field)].isalnum() or s[i + len(field)] == '_')):
        return col
    if s[i:i + 1] == '.' and s[i + 1:i + 1 + len(field)] == field:
        return col + 1
    return None


def diag_tu(args):
    """One TU: (rel, sites, other).  sites = [(file, line, col, field, type, primary)], other = error lines."""
    root, rel, keys = args
    res = subprocess.run(['clang', '--target=mipsel-unknown-none', '-w', '-fsyntax-only', '-ferror-limit=0',
                          '-I', 'include', rel], cwd=root, capture_output=True, text=True)
    heads = list(ERR_HEAD.finditer(res.stderr))
    cache = {}

    def lines_of(f):
        if f not in cache:
            try:
                cache[f] = read_text(f).split('\n')
            except OSError:
                cache[f] = []
        return cache[f]
    sites, other = [], []
    for i, h in enumerate(heads):
        end = heads[i + 1].start() if i + 1 < len(heads) else len(res.stderr)
        block = res.stderr[h.start():end]
        first = block.split('\n', 1)[0]
        msg = first[h.end() - h.start():]
        m = NO_MEMBER.search(msg) or DESIGNATOR.search(msg)
        if m and (m.group('f'), m.group('t')) in keys:
            f, t = m.group('f'), m.group('t')
            pf = _norm(root, h.group('file'))
            pl, pc = int(h.group('line')), int(h.group('col'))
            cands = [(pf, pl, pc)] + [(_norm(root, n.group('file')), int(n.group('line')), int(n.group('col')))
                                     for n in NOTE_MACRO.finditer(block)]
            hit = None
            for cf, cl, cc in reversed(cands):  # innermost spelling first
                c2 = _holds(lines_of(cf), cl, cc, f)
                if c2:
                    hit = (cf, cl, c2)
                    break
            if hit is None:
                other.append(first + ' [token not found at any reported location]')
            else:
                inmacro = hit[:2] != (pf, pl) or hit[2] not in (pc, pc + 1)
                sites.append((hit[0], hit[1], hit[2], f, t, (pf, pl, pc), inmacro))
        else:
            other.append(first)
    return rel, sites, other


def run_diag(root, tus, keys, workers):
    args = [(str(root), t, keys) for t in tus]
    with ProcessPoolExecutor(max_workers=workers) as ex:
        return list(ex.map(diag_tu, args, chunksize=4))


def consumers(root, headers):
    """Consumer TUs: the registered physical TUs whose include closure holds a header (as single mode does).
    A source-only tree (no disc assets for the recipe registry) falls back to the textual include closure
    over src/**/*.c, which is a superset; TUs that do not compile standalone are covered by the baseline."""
    try:
        import layout_compile_identity as LCI
        from tu_identity import proof_set
        physical, _ = LCI.recipes(root)
        tus, _ = proof_set(root, sorted(headers), physical, workers=6)
        return tus
    except Exception as exc:  # noqa: BLE001 - any registry failure selects the textual closure
        print('recipe registry unavailable (%s); using the textual include closure' % type(exc).__name__, file=sys.stderr)
        from layout_dependencies import consumer_paths
        users = consumer_paths(root, set(headers))
        return sorted(u for u in users if u.startswith('src/') and u.endswith('.c'))


def other_key(e):
    """Position-free form of an error line, so a baseline error matches after edits shift lines."""
    return re.sub(r'^[^:\n]+:\d+:\d+: ', '', e)


# ---------------------------------------------------------------- batch driver

def run_batch(root, rows, tus=None, dry_run=False, workers=4, max_rounds=8, max_restarts=6, log=lambda s: None):
    """Apply (or dry-run) every pending row.  Returns the rows (statuses filled).  Restores the tree on any abort."""
    root = Path(root).resolve()
    texts = check_rows(root, rows)
    check_offsets(root, rows)
    live = [r for r in rows if r.status == 'pending']
    if not live:
        return rows
    headers = {r.header for r in live}
    if tus is None:
        log('consumer discovery over %d header(s)' % len(headers))
        tus = consumers(root, headers)
    tus = [t for t in tus if (root / t).is_file()]
    log('%d consumer TUs' % len(tus))
    keys0 = {(r.old, t) for r in live for t in r.types}
    log('baseline pass')
    base = {rel: {other_key(o) for o in oo} for rel, _, oo in run_diag(root, tus, keys0, workers)}
    saved = {}

    def restore():
        for rel, t in saved.items():
            write_atomic(root / rel, t)
        saved.clear()

    def save(rel):
        if rel not in saved:
            saved[rel] = read_text(root / rel)

    try:
        for attempt in range(max_restarts):
            live = [r for r in rows if r.status in ('pending', 'ok')]
            for r in live:
                r.status, r.detail = 'pending', r.detail if r.detail.startswith('offset') else ''
                r.sites, r.macro_sites, r.uses = set(), set(), set()
            if not live:
                return rows
            keymap = {(r.old, t): r for r in live for t in r.types}
            # header declarators renamed in one write per header
            for h in sorted({r.header for r in live}):
                save(h)
                text = saved[h]
                spans = []
                for r in (x for x in live if x.header == h):
                    sp = header_field_span(text, r.record, r.old)
                    spans.append((sp[0], sp[1], r.new))
                for a, b, new in sorted(spans, reverse=True):
                    text = text[:a] + new + text[b:]
                write_atomic(root / h, text)
            dropped = False
            for rnd in range(max_rounds):
                log('round %d/%d, %d rows' % (attempt, rnd, len(live)))
                results = run_diag(root, tus, set(keymap), workers)
                sites = {}
                for rel, ss, oo in results:
                    for f, line, col, field, typ, primary, inmacro in ss:
                        r = keymap[(field, typ)]
                        sites.setdefault((f, line, col), (r, inmacro))
                        r.uses.add(primary)
                        r.sites.add((f, line, col))
                        if inmacro:
                            r.macro_sites.add((f, line, col))
                site_lines = {(f, line) for f, line, _ in sites}
                newnames = {r.new: r for r in live}
                bad = []
                for rel, ss, oo in results:
                    for o in oo:
                        if other_key(o) in base.get(rel, set()):
                            continue
                        m = re.match(r'^(?P<file>[^:\n]+):(?P<line>\d+):\d+: ', o)
                        if m and (_norm(root, m.group('file')), int(m.group('line'))) in site_lines:
                            continue  # typo-correction cascade on a rewritten line
                        bad.append((rel, o))
                if bad:
                    blamed = {}
                    for rel, o in bad:
                        hit = [r for r in live if re.search(r"'(%s|%s)'" % (re.escape(r.old), re.escape(r.new)), o)]
                        if not hit:
                            raise RuntimeError('unexplained diagnostic in %s: %s' % (rel, o[:300]))
                        for r in hit:
                            blamed.setdefault(id(r), (r, o))
                    for r, o in blamed.values():
                        r.refuse('compile error after rename: %s' % other_key(o)[:240])
                    dropped = True
                    break
                if not sites:
                    break
                if dry_run:
                    break
                byfile = {}
                for (f, line, col), (r, inmacro) in sites.items():
                    p = Path(f)
                    if not p.is_relative_to(root) or p.relative_to(root).parts[0] not in ('src', 'include'):
                        raise RuntimeError('site outside src/include: %s' % f)
                    byfile.setdefault(p, []).append((line, col, r))
                for p, locs in byfile.items():
                    rel = p.relative_to(root).as_posix()
                    save(rel)
                    lines = read_text(p).split('\n')
                    for line, col, r in sorted(locs, key=lambda x: (-x[0], -x[1])):
                        s = lines[line - 1]
                        i = col - 1
                        if s[i:i + len(r.old)] != r.old:
                            raise RuntimeError('diagnostic column does not hold the member token: %s:%d:%d' % (rel, line, col))
                        lines[line - 1] = s[:i] + r.new + s[i + len(r.old):]
                    write_atomic(p, '\n'.join(lines))
            else:
                raise RuntimeError('sites still reported after %d rounds' % max_rounds)
            if dropped:
                restore()
                continue
            break
        else:
            raise RuntimeError('rows kept being dropped after %d restarts' % max_restarts)
        return finish(rows, dry_run, restore)
    except Exception:
        restore()
        raise


def finish(rows, dry_run, restore):
    for r in rows:
        if r.status == 'pending':
            r.status = 'would_rename' if dry_run else 'renamed'
    if dry_run:
        restore()
    return rows


# ---------------------------------------------------------------- report

def write_report(path, rows):
    with open(path, 'w', newline='', encoding='utf-8') as fh:
        w = csv.writer(fh, delimiter='\t', lineterminator='\n')
        w.writerow(REPORT_COLS)
        for r in rows:
            files = sorted({f for f, _, _ in r.sites})
            w.writerow([r.record, r.header, r.old, r.new, '' if r.offset is None else '0x%X' % r.offset, r.status,
                        len(r.sites), len(r.macro_sites), len(r.uses), len(files), r.detail.replace('\t', ' ').replace('\n', ' ')])


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=TOOLS.parent)
    ap.add_argument('--rows', type=Path, action='append', required=True)
    ap.add_argument('--record')
    ap.add_argument('--default-header')
    ap.add_argument('--dry-run', action='store_true')
    ap.add_argument('--report', type=Path)
    ap.add_argument('--workers', type=int, default=4)
    ap.add_argument('--tu', nargs='*', default=None, help='explicit consumer TUs (skip closure discovery)')
    args = ap.parse_args(argv)
    rows = load_rows(args.rows, args.record, args.default_header)
    try:
        run_batch(args.root, rows, args.tu, args.dry_run, args.workers, log=lambda s: print(s, file=sys.stderr))
    except RuntimeError as exc:
        print(json.dumps({'state': 'aborted', 'reason': str(exc)[:2000], 'restored': True}))
        if args.report:
            for r in rows:
                if r.status in ('pending', 'ok'):
                    r.status, r.detail = 'aborted', str(exc)[:200]
            write_report(args.report, rows)
        return 1
    if args.report:
        write_report(args.report, rows)
    tally = {}
    for r in rows:
        tally[r.status] = tally.get(r.status, 0) + 1
    print(json.dumps({'state': 'dry-run' if args.dry_run else 'applied', 'rows': len(rows), 'status': tally,
                      'sites': sum(len(r.sites) for r in rows)}))
    return 0


if __name__ == '__main__':
    sys.exit(main())
