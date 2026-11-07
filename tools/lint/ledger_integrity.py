#!/usr/bin/env python3
"""Integrity checks on ledger/unions.jsonl against a BASE revision.

    ledger_integrity.py BASE [--fail-new | --fail-all] [--list] [--rederive [--write]]

(a) loads: the number of rows with any non-zero per-member `loads` must not drop, and
    no row whose loads were non-zero on BASE may become all-zero (a regeneration that
    lost the field).  Rows absent from BASE, or BASE rows without `loads`, count as zero.
    Always gating.
(b) retired_to_cast sites, on the whole ledger: every string entry `path:line[,n] CAST ...`
    must name an existing line that contains CAST (whitespace-insensitive).  CAST is the
    first cast spelling of the text after the location: `(s16)`, `(u16 *)`, `(T *)`,
    `*(u8 *)&`.  `,n` with n > line names a second line, which must hold CAST too; a
    smaller n is a count or column and is not checked.  Dict entries {site, cast} are
    checked the same way.  Entries with no `path:line` (for example `path (former member
    sites)`) are notes; `path:line` with no cast spelling only needs the line to exist.
    --fail-new fails on entries stale on HEAD that were not stale on BASE (same entry,
    BASE text); --fail-all fails on every stale entry.  Without either flag (b) reports.
(c) weak evidence (report only): retired rows that carry load counts, by how many
    mapped loads (lb, lbu, lh, lhu, lw; stores never vote) the decision rests on.

--rederive proposes a current line for each stale entry: the nearest line holding the
same cast spelling applied to the row's field, following the file's history from the
newest committed version where the entry held, unique per row; when no such cast is
left the line number is dropped and the entry is marked `(cast gone)`.  --write applies the proposals.
"""
from __future__ import annotations

import argparse
import collections
import json
from pathlib import Path
import re
import subprocess
import sys

LEDGER = 'ledger/unions.jsonl'
LOAD_OPS = ('lb', 'lbu', 'lh', 'lhu', 'lw')
SITE = re.compile(r'^(?P<path>[^\s:]+\.(?:c|h|inc)):(?P<line>\d+)(?:,(?P<n>\d+))?:?(?P<rest>.*)$', re.S)
CAST = re.compile(r'\*\s*\([^()]*\*\s*\)\s*&'
                  r'|\(\s*(?:(?:const|struct|union|enum|unsigned|signed|volatile)\s+)*'
                  r'[A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)*\s*(?:\*\s*)*\)')
GONE = '(cast gone)'


def squash(text):
    return re.sub(r'\s+', '', text)


def parse_entry(entry):
    """dict(kind=note|site|nocast|unparsed, path, line, second, extra, cast, rest)."""
    if isinstance(entry, dict):
        site = entry.get('site', '')
        match = SITE.match(site) if isinstance(site, str) else None
        if not match:
            return dict(kind='unparsed')
        cast = CAST.match(str(entry.get('cast', '')).strip())
        return dict(kind='site' if cast else 'nocast', path=match['path'], line=int(match['line']),
                    second=None, extra=None, cast=cast.group(0) if cast else None, rest='')
    if not isinstance(entry, str):
        return dict(kind='unparsed')
    match = SITE.match(entry.strip())
    if not match:
        return dict(kind='note')
    line, n = int(match['line']), int(match['n']) if match['n'] else None
    rest = match['rest']
    cast = CAST.match(rest.strip())
    return dict(kind='site' if cast else 'nocast', path=match['path'], line=line,
                second=n if n and n > line else None, extra=n if n and n <= line else None,
                cast=cast.group(0) if cast else None, rest=rest)


class Texts:
    """File lines on the working tree (rev None) or at a revision, cached."""

    def __init__(self, root, rev=None):
        self.root, self.rev, self.cache = Path(root), rev, {}

    def lines(self, path):
        if path not in self.cache:
            if self.rev is None:
                p = self.root / path
                text = p.read_text(errors='replace') if p.is_file() else None
            else:
                result = subprocess.run(['git', 'show', f'{self.rev}:{path}'], cwd=self.root,
                                        capture_output=True)
                text = result.stdout.decode(errors='replace') if result.returncode == 0 else None
            self.cache[path] = None if text is None else text.splitlines()
        return self.cache[path]


def check_entry(entry, texts):
    """'ok' | 'note' | 'stale' | 'noline' | 'nofile' | 'unparsed'."""
    parsed = parse_entry(entry)
    if parsed['kind'] in ('note', 'unparsed'):
        return parsed['kind']
    lines = texts.lines(parsed['path'])
    if lines is None:
        return 'nofile'
    wanted = [parsed['line']] + ([parsed['second']] if parsed['second'] else [])
    if any(n < 1 or n > len(lines) for n in wanted):
        return 'noline'
    if parsed['kind'] == 'nocast':
        return 'ok'
    token = squash(parsed['cast'])
    return 'ok' if all(token in squash(lines[n - 1]) for n in wanted) else 'stale'


STALE = ('stale', 'noline', 'nofile')


def read_ledger(text):
    return [json.loads(line) for line in text.splitlines() if line.strip()]


def mapped_loads(row):
    return sum(sum((member or {}).get(op, 0) for op in LOAD_OPS)
               for member in (row.get('loads') or {}).values())


def any_loads(row):
    return any(any(v for v in (member or {}).values()) for member in (row.get('loads') or {}).values())


def check_loads(base_rows, head_rows):
    base = {r['id']: r for r in base_rows}
    head = {r['id']: r for r in head_rows}
    base_n = sum(1 for r in base_rows if any_loads(r))
    head_n = sum(1 for r in head_rows if any_loads(r))
    zeroed = sorted(i for i, r in base.items() if any_loads(r) and i in head and not any_loads(head[i]))
    dropped = sorted(i for i, r in base.items() if any_loads(r) and i not in head)
    problems = []
    if head_n < base_n:
        problems.append(f'rows with non-zero loads fell {base_n} -> {head_n}')
    problems += [f'loads zeroed: {i}' for i in zeroed]
    return dict(base=base_n, head=head_n, zeroed=zeroed, dropped=dropped, problems=problems)


def check_sites(head_rows, head_texts, base_rows=None, base_texts=None):
    """Per-entry results on HEAD, and which stale ones are new against BASE."""
    base_entries = {}
    for row in base_rows or ():
        base_entries[row['id']] = [json.dumps(e, sort_keys=True) for e in row.get('retired_to_cast') or []]
    results, counts = [], collections.Counter()
    base_cache = {}
    for row in head_rows:
        for entry in row.get('retired_to_cast') or []:
            status = check_entry(entry, head_texts)
            counts[status] += 1
            if status not in STALE:
                continue
            key = json.dumps(entry, sort_keys=True)
            new = True
            if base_texts is not None and key in base_entries.get(row['id'], ()):
                if key not in base_cache:
                    base_cache[key] = check_entry(entry, base_texts)
                new = base_cache[key] not in STALE
            results.append(dict(id=row['id'], entry=entry, status=status, new=new))
    return results, counts


def weak_evidence(rows, base_rows=None):
    base_status = {r['id']: r.get('status') for r in base_rows or ()}
    retired = [r for r in rows if r.get('status') == 'retired']
    with_loads = [r for r in retired if mapped_loads(r) > 0]

    def tally(group):
        return dict(rows=len(group), under5=sum(1 for r in group if mapped_loads(r) < 5),
                    one=sum(1 for r in group if mapped_loads(r) == 1))
    newly = [r for r in with_loads if base_rows is not None and base_status.get(r['id']) != 'retired']
    return dict(retired=len(retired), no_load_data=len(retired) - len(with_loads),
                all=tally(with_loads), newly_retired=tally(newly) if base_rows is not None else None)


# ---------------------------------------------------------------- re-derivation

def field_names(row):
    names = {row.get('path', '').split('.')[-1]}
    names |= {m.get('name') for m in row.get('members') or [] if m.get('name')}
    return {n for n in names if n}


def cast_fields(text, token):
    """Members the casts on this text apply to: `(s16)p->f` and `((T *)p)->f` give f."""
    fields = set()
    for match in re.compile(r'\s*'.join(map(re.escape, token))).finditer(text or ''):
        field = re.search(r'(?:->|\.)\s*([A-Za-z_]\w*)', text[match.end():match.end() + 120])
        if field:
            fields.add(field[1])
    return fields


def with_next(lines, i):
    """0-based line i joined with the following line (casts split across a line break)."""
    return lines[i] + (' ' + lines[i + 1] if i + 1 < len(lines) else '')


class History:
    """Committed versions of a file, newest first, to find where a stale entry was last true."""

    def __init__(self, root, depth=80):
        self.root, self.depth = Path(root), depth
        self.revs, self.texts, self.opcodes = {}, {}, {}

    def revisions(self, path):
        if path not in self.revs:
            out = subprocess.run(['git', 'log', '--format=%H', f'-n{self.depth}', '--', path],
                                 cwd=self.root, capture_output=True, text=True).stdout
            self.revs[path] = out.split()
        return self.revs[path]

    def lines(self, rev, path):
        if (rev, path) not in self.texts:
            self.texts[(rev, path)] = Texts(self.root, rev).lines(path)
        return self.texts[(rev, path)]

    def anchor(self, path, numbers, token):
        """(rev, lines) of the newest version whose numbered lines all hold token."""
        for rev in self.revisions(path):
            lines = self.lines(rev, path)
            if lines and all(0 < n <= len(lines) and token in squash(lines[n - 1]) for n in numbers):
                return rev, lines
        return None, None

    def diff(self, rev, path, old, new):
        if (rev, path) not in self.opcodes:
            import difflib
            self.opcodes[(rev, path)] = difflib.SequenceMatcher(None, old, new, autojunk=False).get_opcodes()
        return self.opcodes[(rev, path)]


def map_line(opcodes, new, n, token, fields):
    """(current line or None, projected line, field matched) for old line n through the diff."""
    i = n - 1
    for tag, i1, i2, j1, j2 in opcodes:
        if not i1 <= i < i2:
            continue
        projected = j1 + (i - i1) * max(1, j2 - j1) // max(1, i2 - i1) + 1
        if tag == 'equal':
            return j1 + (i - i1) + 1, j1 + (i - i1) + 1, True
        block = [j for j in range(max(0, j1 - 2), min(len(new), j2 + 2)) if token in squash(new[j])]
        if not block:
            return None, projected, False
        same = [j for j in block if cast_fields(with_next(new, j), token) & fields]
        best = min(same or block, key=lambda j: abs(j + 1 - projected))
        return best + 1, projected, bool(same)
    return None, n, False


def relocate(row, entries, texts, history=None):
    """{entry: (replacement, how)} for a row's stale string entries; duplicates share one result.

    how: 'history' (followed from the newest committed text where the entry held, through the
    diff to the current text, onto the same field), 'history-renamed' (the matching diff block
    holds the cast but on a differently named member: review), 'history+field' or 'field'
    (nearest line where the cast applies to the row's field) or 'gone' (no such cast left)."""
    cited = set()
    for entry in row.get('retired_to_cast') or []:
        parsed = parse_entry(entry)
        if parsed['kind'] == 'site' and check_entry(entry, texts) == 'ok':
            for n in (parsed['line'], parsed['second']):
                if n:
                    cited.add((parsed['path'], squash(parsed['cast']), n))
    out = {}
    for entry in sorted(set(entries), key=lambda e: (parse_entry(e)['path'], parse_entry(e)['line'])):
        parsed = parse_entry(entry)
        path, token = parsed['path'], squash(parsed['cast'])
        lines = texts.lines(path) or []
        numbers = [parsed['line']] + ([parsed['second']] if parsed['second'] else [])
        fields = field_names(row)
        rev, old = history.anchor(path, numbers, token) if history else (None, None)
        if old:
            for n in numbers:
                fields |= cast_fields(with_next(old, n - 1), token)
        near = [i + 1 for i, t in enumerate(lines) if token in squash(t)
                and cast_fields(with_next(lines, i), token) & fields]

        def free(n):
            return n is not None and (path, token, n) not in cited

        def nearest(pool, target, window=None):
            pool = [n for n in pool if free(n) and (window is None or abs(n - target) <= window)]
            return min(pool, key=lambda n: (abs(n - target), n)) if pool else None
        found, how = [], 'history' if old else 'field'
        for n in numbers:
            choice, target, matched = (map_line(history.diff(rev, path, old, lines), lines, n, token, fields)
                                       if old else (None, n, False))
            if free(choice) and not matched:
                how = 'history-renamed'
            if not free(choice):
                choice = nearest(near, target)
                if choice is not None and old:
                    how = 'history+field'
            if choice is None:
                break
            cited.add((path, token, choice))
            found.append(choice)
        if not found:
            out[entry] = (' '.join(f'{path} {parsed["rest"].strip()} {GONE}'.split()), 'gone')
            continue
        location = f'{path}:{min(found)}' + (f',{max(found)}' if len(found) > 1 else '')
        if parsed['extra'] and len(found) == 1:
            location += f",{parsed['extra']}"
        out[entry] = (location + parsed['rest'], how)
    return out


def rederive(rows, results, texts, history=None):
    by_row = collections.defaultdict(list)
    for result in results:
        if isinstance(result['entry'], str) and parse_entry(result['entry'])['kind'] == 'site' \
                and result['status'] in ('stale', 'noline'):
            by_row[result['id']].append(result['entry'])
    changes = []
    for row in rows:
        stale = by_row.get(row['id'])
        if not stale:
            continue
        mapping = relocate(row, stale, texts, history)
        new_list = []
        for entry in row['retired_to_cast']:
            if entry in mapping:
                replacement, how = mapping[entry]
                changes.append(dict(id=row['id'], old=entry, new=replacement, how=how))
                new_list.append(replacement)
            else:
                new_list.append(entry)
        row['retired_to_cast'] = new_list
    return changes


# ---------------------------------------------------------------- main

def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('base', help='base revision to compare loads and staleness against')
    parser.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[2])
    parser.add_argument('--ledger', default=LEDGER)
    mode = parser.add_mutually_exclusive_group()
    mode.add_argument('--fail-new', action='store_true', help='fail on retired_to_cast entries newly stale on HEAD')
    mode.add_argument('--fail-all', action='store_true', help='fail on every stale retired_to_cast entry')
    parser.add_argument('--list', action='store_true', help='list every stale entry and weak row')
    parser.add_argument('--rederive', action='store_true', help='propose current lines for stale entries')
    parser.add_argument('--write', action='store_true', help='with --rederive, rewrite the ledger')
    args = parser.parse_args(argv)
    root = args.root.resolve()
    head_rows = read_ledger((root / args.ledger).read_text())
    shown = subprocess.run(['git', 'show', f'{args.base}:{args.ledger}'], cwd=root, capture_output=True, text=True)
    if shown.returncode:
        parser.error(f'cannot read {args.ledger} at {args.base}: {shown.stderr.strip()}')
    base_rows = read_ledger(shown.stdout)
    head_texts, base_texts = Texts(root), Texts(root, args.base)

    if args.rederive:
        results, _ = check_sites(head_rows, head_texts)
        changes = rederive(head_rows, results, head_texts, History(root))
        for change in changes:
            print(f"{change['how']:8} {change['id']}\n    {change['old']}\n -> {change['new']}")
        tally = collections.Counter(c['how'] for c in changes)
        print(f"re-derived {len(changes)} entries: " + ', '.join(f'{k} {v}' for k, v in sorted(tally.items())))
        if args.write:
            (root / args.ledger).write_text(''.join(json.dumps(r, sort_keys=True) + '\n' for r in head_rows))
            print(f'wrote {args.ledger}')
        return 0

    loads = check_loads(base_rows, head_rows)
    results, counts = check_sites(head_rows, head_texts, base_rows, base_texts)
    weak = weak_evidence(head_rows, base_rows)
    stale = [r for r in results]
    new_stale = [r for r in results if r['new']]
    print(f"loads: rows with non-zero loads {loads['base']} -> {loads['head']}; zeroed {len(loads['zeroed'])}; "
          f"dropped rows {len(loads['dropped'])}")
    print('retired_to_cast: ' + ', '.join(f'{k} {counts[k]}' for k in
          ('ok', 'stale', 'noline', 'nofile', 'note', 'unparsed')) +
          f'; stale on HEAD {len(stale)} (new vs BASE {len(new_stale)})')
    w = weak['all']
    line = (f"weak evidence (report only): retired {weak['retired']}, with load data {w['rows']}, "
            f"<5 mapped loads {w['under5']}, exactly 1 {w['one']}; no load data {weak['no_load_data']}")
    if weak['newly_retired'] is not None:
        n = weak['newly_retired']
        line += f"; newly retired vs BASE {n['rows']} (<5 {n['under5']}, 1 {n['one']})"
    print(line)
    listed = stale if args.list or args.fail_all else new_stale if args.fail_new else stale[:10]
    for r in listed:
        print(f"  {'NEW ' if r['new'] else ''}{r['status'].upper()} {r['id']}: {r['entry']}")
    if not (args.list or args.fail_all or args.fail_new) and len(stale) > 10:
        print(f'  ... {len(stale) - 10} more (--list)')
    if args.list:
        for row in head_rows:
            if row.get('status') == 'retired' and 0 < mapped_loads(row) < 5:
                print(f'  WEAK {mapped_loads(row)} {row["id"]}')
    for problem in loads['problems']:
        print('LOADS ' + problem)
    failed = bool(loads['problems']) or (args.fail_all and stale) or (args.fail_new and new_stale)
    print('ledger integrity ' + ('FAIL' if failed else 'PASS'))
    return 1 if failed else 0


if __name__ == '__main__':
    sys.exit(main())
