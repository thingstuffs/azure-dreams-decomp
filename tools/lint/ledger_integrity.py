#!/usr/bin/env python3
"""Integrity checks on ledger/unions.jsonl against a BASE revision.

    ledger_integrity.py BASE [--fail-new | --fail-all] [--list] [--no-layouts] [--rederive [--write]]

(a) loads: the number of rows with any non-zero per-member `loads` must not drop, and
    no row whose loads were non-zero on BASE may become all-zero (a regeneration that
    lost the field).  Rows absent from BASE, or BASE rows without `loads`, count as zero.
    Always gating.
(b) retired_to_cast sites, on the whole ledger: every string entry `path:line[,n] CAST ...`
    must name an existing line that contains CAST (whitespace-insensitive).  CAST is the
    first cast spelling of the text after the location: `(s16)`, `(u16 *)`, `(T *)`,
    `*(u8 *)&`.  `,n` with n > line names a second line, which must hold CAST too; a
    smaller n is a span of n lines starting at the line (only the first must hold CAST).
    Dict entries {site, cast} are checked the same way.  Entries with no `path:line` (for
    example `path (former member sites)`) are notes; `path:line` with no cast spelling only
    needs the line to exist.
(c) field rule, on every entry that passes (b): the cited span must reference the row's
    field, `->field` or `.field` for the last component of the row's path.  The span is
    the cited line(s) or the `,n` lines, plus the next line when the cast is a pointer
    cast or ends its line.  Classes, accepted:
      field     the row's field is referenced
      alias     a named member of the row (GridPoint x/y), or a field declared in the
                same declarator list as the row's (`u16 angle_x, angle_y, angle_z;`)
      named     the entry's own text names the member that is referenced
                (`(u16) value cast of y`, `(s16)effect->ticks_left`, a dict entry's `to`)
      renamed   the row's path is an `unk_XX`/`field_XX` name and a cast on the line
                applies to a member that a record of the file places at offset XX
                (clang record layouts of the cited file)
      typedef   a typedef or variable row (path == owner): the span names the owner, or a
                member the file's records declare with that type
    report only:
      renamed?  a cast applies to a differently named member whose offset could not be
                checked (no layouts, or the member is not in any record of the file)
      typedef?  a typedef row whose span names neither the type nor a member of that type
      nofield   the casts on the line apply to no member (a local, an array, a call)
    failing:
      wrong     a cast of another member stands on the line, the row's field (and every
                alias) is nowhere in the span, and no rename is possible: every cast is
                on an `unk_XX` member, the owner's record in the row's file still
                declares the field, or the layouts place the member at another offset
    --fail-new fails on entries stale on HEAD, or `wrong` on HEAD, that were neither stale
    nor `wrong` on BASE (same entry, BASE text; BASE uses HEAD's record layouts);
    --fail-all fails on every stale or `wrong` entry.  Without either flag (b) and (c)
    report.  --no-layouts skips clang: renames are then `renamed?`.
(e) evidence load numbers (report only): prose such as "2 lh and 4 lhu" in a row's evidence is compared
    with the sums of the row's own `loads`; an op whose stated numbers never equal the field is listed (--list).
(d) weak evidence (report only): retired rows that carry load counts, by how many
    mapped loads (lb, lbu, lh, lhu, lw; stores never vote) the decision rests on.

(f) public ledgers (audit rule R12, tools/lint/ledger_public.py): the public files that differ from BASE
    (ledger/*.jsonl|json, tools/**/*baseline*.json, config/*.tsv) must not gain lane-local strings: work/ or
    out/ paths, home or session scratch paths, lane names.  --fail-new and --fail-all both fail on a NEW one
    (strings already on BASE are the historical journals' and are only counted by `ledger_public.py census`).
    They must not gain a 40-hex "tree" commit hash outside public history either (an ancestor of HEAD, a local
    master, LEDGER_PUBLIC_REF or --public-ref): a lane root's private commit cannot be resolved by anyone.

(g) prototype-floor blocking spellings, on ledger/prototype_floors.jsonl: each `blocking` entry
    {declaration, path, spelling} names a declaration that keeps the floor.  Its file (`declaration`, else
    `path`) must still declare the name with that signature (return and parameter types after
    tools/lint/decl_agreement.py normalisation: whitespace, parameter names, struct keywords and scalar
    typedef aliases do not matter; `()` matches only an unprototyped declaration).  --fail-new fails on an
    entry that is stale on HEAD and was not stale on BASE (a new row, a new entry, or a declaration that a
    change respelled or removed); --fail-all fails on every stale entry.  A floor whose blocker is gone is
    obsolete or must be re-solved, not left citing a declaration that no longer exists.

(h) prototype-floor cited paths, on ledger/prototype_floors.jsonl: every src/ or include/ file a row cites
    (blocking and partition sites, the definition, callers, declarations, reason and evidence text) must
    exist on HEAD.  The planned owner header (`owner` / evidence `header` equal to the interface header the
    header planner derives for the definition's directory, tools/headers/plan.py header_for) is a plan, not
    evidence, and may not exist yet.  --fail-new fails on a row that cites a missing path BASE's same row
    (by name) did not; --fail-all fails on every one.  A rename that leaves a floor row naming the old file
    makes the row unverifiable.

(i) placed copies (tools/lint/placed_copies.py): every config/names.tsv row recorded `copy_of=0x<addr>` must be
    the same function as its canonical row: one row at each family address defines the name, and the retail
    words are equal except a jump within the function's own body.  --fail-new and --fail-all fail on any
    family that differs or cannot be found (a copy record is a claim about bytes, not a ratchet).

--rederive proposes a current line for each stale or `wrong` entry: the nearest line holding
the same cast spelling that passes the field rule, following the file's history from the
newest committed version where the entry held (cast and field), unique per row; a line that
fails the field rule is never chosen.  Lines move by `git diff` hunk offsets from the newest version
whose cited lines hold the cast text (field rule first, cast text alone when the field never held), and
only then by text search nearest the projected line.  When no such cast is left the line number is dropped
and the entry is marked `(cast gone)`.  --write applies the proposals.
"""
from __future__ import annotations

import argparse
import collections
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import ledger_public  # noqa: E402
import placed_copies  # noqa: E402

FLOORS = 'ledger/prototype_floors.jsonl'


def blocking_signature(spelling, name, aliases):
    """(return, params) of a floor `spelling` such as `s16 f(u16, u16)`, normalised like decl_agreement; or None."""
    import decl_agreement as D
    found = D.declarations(spelling.rstrip().rstrip(';') + ';', {name}, aliases)
    return _sig(found[0]) if found else None


def _sig(found):
    params = found[4]
    return found[3], None if params is None else tuple(params)


def floor_blocking(rows, texts, aliases):
    """[{name, index, entry, file, status}] for each blocking entry: status 'ok', 'stale' (the file no longer
    declares that signature), 'nofile' or 'unparsed' (the spelling is not a declaration of the row's name)."""
    import decl_agreement as D
    out, decls = [], {}
    for row in rows:
        name = row.get('name')
        for i, entry in enumerate(row.get('blocking') or []):
            if not isinstance(entry, dict) or not entry.get('spelling') or not name:
                continue
            path = entry.get('declaration') or entry.get('path')
            want = blocking_signature(entry['spelling'], name, aliases)
            lines = texts.lines(path) if path else None
            if want is None:
                status = 'unparsed'
            elif lines is None:
                status = 'nofile'
            else:
                key = (path, name)
                if key not in decls:
                    decls[key] = {_sig(d) for d in D.declarations('\n'.join(lines), {name}, aliases)}
                status = 'ok' if want in decls[key] else 'stale'
            out.append(dict(name=name, index=i, file=path, status=status,
                            entry=json.dumps(entry, sort_keys=True)))
    return out


def recorded_function_renames(root, base):
    """{BASE name: HEAD name} for functions config/names.tsv renamed in place since BASE: at one address the
    BASE rows name `old`, HEAD no longer names it anywhere, and HEAD has exactly one name there BASE lacked."""
    def rows(text):
        out = {}
        for line in (text or '').splitlines():
            cols = line.split('\t')
            if len(cols) >= 3 and cols[0].startswith('0x'):
                out.setdefault(cols[0].lower(), set()).add(cols[2])
        return out
    head_path = Path(root) / 'config/names.tsv'
    head = rows(head_path.read_text(errors='replace') if head_path.is_file() else '')
    shown = subprocess.run(['git', 'show', f'{base}:config/names.tsv'], cwd=root, capture_output=True, text=True)
    old = rows(shown.stdout if shown.returncode == 0 else '')
    head_names = {n for names in head.values() for n in names}
    renames = {}
    for addr, names in old.items():
        added = head.get(addr, set()) - names
        for name in names - head_names:
            if len(added) == 1:
                renames[name] = next(iter(added))
    return renames


def file_renames(root, base):
    """{BASE path: HEAD path} for src/include files git records as renamed between BASE and the checkout."""
    shown = subprocess.run(['git', 'diff', '-M', '--name-status', '--diff-filter=R', base, '--', 'src', 'include'],
                           cwd=root, capture_output=True, text=True)
    out = {}
    for line in shown.stdout.splitlines() if shown.returncode == 0 else ():
        cols = line.split('\t')
        if len(cols) == 3 and cols[0].startswith('R'):
            out[cols[1]] = cols[2]
    return out


def check_floors(root, base, head_text, base_text):
    """(HEAD results, newly stale) for the prototype-floor blocking spellings; BASE results judge newness.

    A row whose function names.tsv renamed since BASE is compared with its BASE row by blocking index: an entry
    that was already stale under the old name is not newly stale under the new one."""
    import decl_agreement as D
    aliases = D.scalar_aliases(root)
    head = floor_blocking(read_ledger(head_text), Texts(root), aliases)
    base_rows = floor_blocking(read_ledger(base_text), Texts(root, base), aliases) if base_text is not None else []
    old = {(r['name'], r['entry']): r['status'] for r in base_rows}
    moved = file_renames(root, base) if base_text is not None else {}
    for r in base_rows:                         # the same entry, its cited files renamed since BASE
        entry = json.loads(r['entry'])
        if any(entry.get(k) in moved for k in ('path', 'declaration')):
            for k in ('path', 'declaration'):
                if entry.get(k) in moved:
                    entry[k] = moved[entry[k]]
            old.setdefault((r['name'], json.dumps(entry, sort_keys=True)), r['status'])
    renames = recorded_function_renames(root, base) if base_text is not None else {}
    renamed_old = {(renames[r['name']], r['index']): r['status'] for r in base_rows if r['name'] in renames}
    bad = [r for r in head if r['status'] in ('stale', 'nofile')]
    new = [r for r in bad if old.get((r['name'], r['entry'])) not in ('stale', 'nofile')
           and renamed_old.get((r['name'], r['index'])) not in ('stale', 'nofile')]
    return head, bad, new

LEDGER = 'ledger/unions.jsonl'
LOAD_OPS = ('lb', 'lbu', 'lh', 'lhu', 'lw')
SITE = re.compile(r'^(?P<path>[^\s:]+\.(?:c|h|inc)):(?P<line>\d+)(?:,(?P<n>\d+))?:?(?P<rest>.*)$', re.S)
CAST = re.compile(r'\*\s*\([^()]*\*\s*\)\s*&'
                  r'|\(\s*(?:(?:const|struct|union|enum|unsigned|signed|volatile)\s+)*'
                  r'[A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)*\s*(?:\*\s*)*\)')
GONE = '(cast gone)'
IDENT = re.compile(r'[A-Za-z_]\w*')
UNK = re.compile(r'^(?:unk|field)_?([0-9A-Fa-f]+)$')
# Union member names that say how a field is read, not which field it is.
GENERIC = {'s', 'u', 'p', 'i', 'w', 'h', 'b', 'f', 's8', 'u8', 's16', 'u16', 's32', 'u32',
           'word', 'signed_word', 'whole', 'signed_whole', 'half', 'halves', 'bytes', 'parts',
           'fields', 'as_s16', 'as_u16', 'as_s32', 'as_u32', 'bits', 'signed_value', 'value',
           'raw', 'ptr', 'addr', 'integer', 'unsigned_parts', 'signed_parts'}
PROSE_STOP = {'value', 'cast', 'casts', 'of', 'and', 'or', 'the', 'a', 'an', 'width', 'sign',
              'signed', 'unsigned', 'read', 'reads', 'store', 'stores', 'load', 'loads', 'both',
              'half', 'word', 'byte', 'view', 'gone', 'line', 'lines', 'site', 'sites', 'member',
              'former', 'branch', 'already', 'stale', 'on', 'in', 'to', 'at', 'from', 'with'}
ACCEPTED = ('field', 'alias', 'named', 'renamed', 'typedef')
REPORTED = ('renamed?', 'typedef?', 'nofield')
FIELD_CLASSES = ACCEPTED + REPORTED + ('wrong',)


def squash(text):
    return re.sub(r'\s+', '', text)


def parse_entry(entry):
    """dict(kind=note|site|nocast|unparsed, path, line, second, extra, cast, rest, to)."""
    if isinstance(entry, dict):
        site = entry.get('site', '')
        match = SITE.match(site) if isinstance(site, str) else None
        if not match:
            return dict(kind='unparsed')
        cast = CAST.match(str(entry.get('cast', '')).strip())
        return dict(kind='site' if cast else 'nocast', path=match['path'], line=int(match['line']),
                    second=None, extra=None, cast=cast.group(0) if cast else None, rest='',
                    to=entry.get('to') if isinstance(entry.get('to'), str) else None)
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
                cast=cast.group(0) if cast else None, rest=rest, to=None)


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


# ---------------------------------------------------------------- record layouts

class Layouts:
    """clang record layouts of a cited C file: [(record, member, offset, type)], cached.

    Offsets are relative to the record each `Dumping AST Record Layout` block describes,
    nested members included; a failed or skipped run gives None."""

    LINE = re.compile(r'^\s*(\d+)(?::\d+-\d+)? \| (\s*)(.*)$')
    ARGS = ['--target=mipsel-unknown-none', '-fsyntax-only', '-w', '-ferror-limit=0', '-Wno-everything']

    def __init__(self, root, enabled=True):
        self.root = Path(root)
        self.clang = os.environ.get('LEDGER_INTEGRITY_CLANG', 'clang')
        self.enabled = enabled and shutil.which(self.clang) is not None
        self.cache = {}

    def get(self, path):
        if not self.enabled or not path.endswith('.c'):
            return None
        if path not in self.cache:
            result = subprocess.run([self.clang, *self.ARGS, '-I', 'include', '-Xclang',
                                     '-fdump-record-layouts-complete', path],
                                    cwd=self.root, capture_output=True)
            text = result.stdout.decode(errors='replace')
            self.cache[path] = self.parse(text) if 'Dumping AST Record Layout' in text else None
        return self.cache[path]

    @classmethod
    def parse(cls, text):
        members = []
        for block in text.split('*** Dumping AST Record Layout')[1:]:
            lines = [line for line in block.splitlines() if cls.LINE.match(line)]
            if not lines:
                continue
            head = cls.LINE.match(lines[0])
            record = head.group(3).split()[-1]
            for line in lines[1:]:
                m = cls.LINE.match(line)
                body = m.group(3).strip()
                if ' ' not in body:
                    continue
                kind, name = body.rsplit(' ', 1)
                members.append((record, name, int(m.group(1)), kind))
        return members


def type_name(kind):
    """`const TransformHalf[3]` -> `TransformHalf`."""
    kind = re.sub(r'\[[^\]]*\]', '', kind).replace('*', ' ')
    words = [w for w in kind.split() if w not in ('const', 'volatile', 'struct', 'union', 'enum')]
    return words[-1] if words else ''


# ---------------------------------------------------------------- the field rule

def accesses(text, name):
    return re.search(r'(?:->|\.)\s*' + re.escape(name) + r'\b', text or '') is not None


def token_pattern(token):
    return re.compile(r'\s*'.join(map(re.escape, token)))


def skip_balanced(text, i, open_, close):
    depth = 0
    while i < len(text):
        if text[i] == open_:
            depth += 1
        elif text[i] == close:
            depth -= 1
            if depth == 0:
                return i + 1
        i += 1
    return i


def operand_members(text, i):
    """Member names of the access chain an operator ending at i applies to.

    `(s16)p->a.b` gives [a, b]; `((S *)p)->f` gives [f] (the closing parenthesis of the
    cast's own group is crossed); `(u16)d[i]` and `(s16)award` give []."""
    n, depth = len(text), 0
    while i < n:
        while i < n and text[i].isspace():
            i += 1
        if i >= n:
            return []
        cast = CAST.match(text, i) if text[i] == '(' else None
        # `(T)x` is a cast when an operand follows; `(x)->f` is a parenthesized operand.
        if cast and re.match(r'\s*(?:[A-Za-z_(*&~!]|-(?!>))', text[cast.end():]):
            i = cast.end()
        elif text[i] == '(':
            depth, i = depth + 1, i + 1
        elif text[i] in '*&-~!+':
            i += 1
        else:
            break
    m = IDENT.match(text, i)
    if not m:
        return []
    i, names = m.end(), []
    while i < n:
        while i < n and text[i].isspace():
            i += 1
        if text.startswith('->', i) or text.startswith('.', i):
            i += 2 if text.startswith('->', i) else 1
            while i < n and text[i].isspace():
                i += 1
            m = IDENT.match(text, i)
            if not m:
                break
            names.append(m.group())
            i = m.end()
        elif text.startswith('[', i):
            i = skip_balanced(text, i, '[', ']')
        elif text.startswith('(', i):
            i = skip_balanced(text, i, '(', ')')
        elif text.startswith(')', i):
            j = i + 1
            while j < n and text[j].isspace():
                j += 1
            if depth > 0:
                depth, i = depth - 1, i + 1
            elif text.startswith(('->', '.', '['), j):
                i = j
            else:
                break
        elif depth > 0:
            # `((T *)(base + k))->f`: the rest of the group is arithmetic; the member
            # access after its closing parenthesis applies to the whole group.
            level = 0
            while i < n and not (text[i] == ')' and level == 0):
                level += {'(': 1, ')': -1}.get(text[i], 0)
                i += 1
        else:
            break
    return names


def cast_targets(text, token, limit=None):
    """[member chain] for each occurrence of token (squashed) starting before limit."""
    out = []
    for match in token_pattern(token).finditer(text or ''):
        if limit is not None and match.start() >= limit:
            break
        out.append(operand_members(text, match.end()))
    return out


def cast_fields(text, token):
    """Members the casts on this text apply to: `(s16)p->f` and `((T *)p)->f` give f."""
    return {name for chain in cast_targets(text, token) for name in chain}


def with_next(lines, i):
    """0-based line i joined with the following line (casts split across a line break)."""
    return lines[i] + (' ' + lines[i + 1] if i + 1 < len(lines) else '')


def row_field(row):
    return (row.get('path') or '').split('.')[-1]


def is_typedef_row(row):
    return bool(row.get('path')) and row.get('path') == row.get('owner')


def field_names(row):
    names = {row_field(row)}
    names |= {m.get('name') for m in row.get('members') or [] if m.get('name')}
    return {n for n in names if n}


def member_aliases(row):
    return {m.get('name') for m in row.get('members') or []
            if m.get('name') and m.get('name') not in GENERIC and m.get('name') != row_field(row)}


def owner_declarations(row, texts):
    """Declarator lists of the owner's record in the row's file, one per declaration:
    `u16 angle_x, angle_y, angle_z;` gives [angle_x, angle_y, angle_z]."""
    owner = row.get('owner')
    lines = texts.lines(row.get('file') or '') if row.get('file') else None
    if not lines or not owner:
        return []
    text = '\n'.join(lines)
    blocks = []
    for m in re.finditer(r'\b(?:struct|union)\s*(\w*)\s*\{', text):
        end = skip_balanced(text, m.end() - 1, '{', '}')
        tail = re.match(r'\s*(\w+)', text[end:])
        if m.group(1) == owner or (tail and tail.group(1) == owner):
            blocks.append(text[m.end():end - 1])
    out = []
    for body in blocks:
        for statement in re.sub(r'\{[^{}]*\}', ' ', body).split(';'):
            parts = [re.sub(r'\[[^\]]*\]|:\s*\d+', '', p).replace('*', ' ').split()
                     for p in statement.split(',')]
            names = [words[-1] for words in parts if words and IDENT.fullmatch(words[-1])]
            if names:
                out.append(names)
    return out


def prose_names(parsed):
    """Member names the entry's own text spells: `(u16) value cast of y`, `(s16)effect->x`."""
    names = set()
    rest = parsed.get('rest') or ''
    if parsed.get('cast'):
        cast = CAST.match(rest.strip())
        rest = rest.strip()[cast.end():] if cast else rest
    rest = rest.replace(GONE, ' ')
    for m in re.finditer(r'(?:->|\.)\s*([A-Za-z_]\w*)', rest):
        names.add(m.group(1))
    names |= {w for w in IDENT.findall(re.sub(r'(?:->|\.)\s*[A-Za-z_]\w*', ' ', rest))
              if w.lower() not in PROSE_STOP and not w.isdigit()}
    if parsed.get('to'):
        names.add(parsed['to'])
    return names


def span_numbers(parsed, lines):
    numbers = [parsed['line']] + ([parsed['second']] if parsed.get('second') else [])
    if parsed.get('extra'):
        numbers = list(range(parsed['line'], parsed['line'] + parsed['extra']))
    return [n for n in numbers if 1 <= n <= len(lines)]


def context_numbers(parsed, lines, token):
    """The span plus the next line where a pointer cast or a line-ending cast continues."""
    numbers = span_numbers(parsed, lines)
    out = list(numbers)
    pointer = token.endswith('*)') or token.endswith('&')
    for n in numbers:
        line = lines[n - 1]
        last = None
        for last in token_pattern(token).finditer(line):
            pass
        ends = last is not None and not line[last.end():].strip(' \t()')
        if (pointer or ends) and n + 1 <= len(lines) and n + 1 not in out:
            out.append(n + 1)
    return out


def classify_lines(row, parsed, lines, layouts=None, texts=None, cache=None):
    """Field-rule class of one parsed `site` entry against these file lines."""
    token = squash(parsed['cast'])
    field = row_field(row)
    span = span_numbers(parsed, lines)
    if not span:
        return 'wrong'
    context = ' \n '.join(lines[n - 1] for n in context_numbers(parsed, lines, token))
    if is_typedef_row(row):
        owner = row['owner']
        if re.search(r'\b' + re.escape(owner) + r'\b', context):
            return 'typedef'
        members = layouts.get(parsed['path']) if layouts else None
        typed = {name for _, name, _, kind in members or () if type_name(kind) == owner}
        return 'typedef' if any(accesses(context, name) for name in typed) else 'typedef?'
    if accesses(context, field):
        return 'field'
    key = row.get('id')
    if cache is not None and key in cache:
        aliases, declared = cache[key]
    else:
        declarations = owner_declarations(row, texts) if texts else []
        declared = {name for names in declarations for name in names}
        aliases = member_aliases(row) | {name for names in declarations if field in names
                                         for name in names if name != field}
        if cache is not None:
            cache[key] = aliases, declared
    if any(accesses(context, name) for name in aliases):
        return 'alias'
    if any(accesses(context, name) for name in prose_names(parsed) - GENERIC):
        return 'named'
    targets = set()
    for n in span:
        text = with_next(lines, n - 1)
        for chain in cast_targets(text, token, limit=len(lines[n - 1])):
            targets |= {name for name in chain if name not in GENERIC}
    if not targets:
        return 'nofield'
    named = {t for t in targets if not UNK.match(t)}
    if not named or field in declared:
        # Every cast is on an unk_XX member (whose name is its offset), or the owner's
        # record still declares the row's field under its own name: no rename happened.
        return 'wrong'
    members = layouts.get(parsed['path']) if layouts else None
    if members is None:
        return 'renamed?'
    unk = UNK.match(field)
    present = {name for _, name, _, _ in members}
    if unk:
        offset = int(unk.group(1), 16)
        if any(name in named and off == offset for _, name, off, _ in members):
            return 'renamed'
        return 'wrong' if named & present else 'renamed?'
    # A named row field that the file's records still declare was not renamed away.
    return 'wrong' if field in present and named & present else 'renamed?'


def field_class(row, entry, texts, layouts=None, cache=None):
    """Field-rule class of an entry that passes check_entry, or None (not a cast site)."""
    parsed = parse_entry(entry)
    if parsed['kind'] != 'site':
        return None
    lines = texts.lines(parsed['path'])
    if not lines:
        return None
    return classify_lines(row, parsed, lines, layouts, texts, cache)


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


def check_sites(head_rows, head_texts, base_rows=None, base_texts=None, layouts=None):
    """Per-entry results on HEAD (stale, or flagged by the field rule), which are new
    against BASE, and counts: (results, status counts, field-class counts)."""
    base_entries = {}
    for row in base_rows or ():
        base_entries[row['id']] = [json.dumps(e, sort_keys=True) for e in row.get('retired_to_cast') or []]
    results, counts, fields = [], collections.Counter(), collections.Counter()
    base_cache, alias_cache, base_alias_cache = {}, {}, {}
    for row in head_rows:
        for entry in row.get('retired_to_cast') or []:
            status = check_entry(entry, head_texts)
            counts[status] += 1
            fclass = field_class(row, entry, head_texts, layouts, alias_cache) if status == 'ok' else None
            if fclass:
                fields[fclass] += 1
            if status not in STALE and fclass not in REPORTED + ('wrong',):
                continue
            key = json.dumps(entry, sort_keys=True)
            new = True
            if base_texts is not None and key in base_entries.get(row['id'], ()):
                if (row['id'], key) not in base_cache:
                    base_status = check_entry(entry, base_texts)
                    base_class = (field_class(row, entry, base_texts, layouts, base_alias_cache)
                                  if base_status == 'ok' else None)
                    base_cache[(row['id'], key)] = base_status in STALE or base_class == 'wrong'
                new = not base_cache[(row['id'], key)]
            results.append(dict(id=row['id'], entry=entry, status=status, field=fclass, new=new))
    return results, counts, fields


EVIDENCE_LOAD = re.compile(r'\b(\d+)\s+(lbu|lb|lhu|lh|lw|unmapped)\b')


def evidence_load_mismatches(rows):
    """Report-only: [(id, op, stated numbers, actual)] where the evidence prose quotes retail load counts
    ("2 lh and 4 lhu") and none of the numbers stated for an op equals the row's own `loads` sum.

    Prose is written from a census run; a row whose loads were re-censused later disagrees with it.
    Only rows with a `loads` field and the word "load" in the evidence text are read."""
    out = []
    for row in rows:
        text, loads = row.get('evidence'), row.get('loads')
        if not isinstance(text, str) or not isinstance(loads, dict) or not re.search(r'\bloads?\b', text):
            continue
        stated = collections.defaultdict(list)
        for number, op in EVIDENCE_LOAD.findall(text):
            stated[op].append(int(number))
        for op, numbers in sorted(stated.items()):
            actual = sum(v.get(op, 0) for v in loads.values() if isinstance(v, dict))
            if actual not in numbers:
                out.append((row['id'], op, numbers, actual))
    return out


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

    def anchor(self, path, numbers, token, holds=None):
        """(rev, lines) of the newest version whose numbered lines all hold token (and,
        given holds(lines), pass it: the entry's field is referenced there)."""
        for rev in self.revisions(path):
            lines = self.lines(rev, path)
            if lines and all(0 < n <= len(lines) and token in squash(lines[n - 1]) for n in numbers) \
                    and (holds is None or holds(lines)):
                return rev, lines
        return None, None

    def diff(self, rev, path, old, new):
        if (rev, path) not in self.opcodes:
            self.opcodes[(rev, path)] = git_opcodes(old, new)
        return self.opcodes[(rev, path)]


HUNK = re.compile(r'^@@ -(\d+)(?:,(\d+))? \+(\d+)(?:,(\d+))? @@')


def git_opcodes(old, new):
    """difflib-style opcodes from `git diff -U0` (histogram), so old lines move by git's own hunk
    offsets; difflib's matcher when git is unavailable."""
    import tempfile
    try:
        with tempfile.TemporaryDirectory(prefix='ledger_diff.') as temporary:
            a, b = Path(temporary) / 'a', Path(temporary) / 'b'
            a.write_text(''.join(line + '\n' for line in old))
            b.write_text(''.join(line + '\n' for line in new))
            result = subprocess.run(['git', 'diff', '--no-index', '--no-color', '-U0', '--diff-algorithm=histogram',
                                     '--', str(a), str(b)], capture_output=True, text=True, check=False)
        if result.returncode not in (0, 1):
            raise OSError(result.stderr)
    except OSError:
        import difflib
        return difflib.SequenceMatcher(None, old, new, autojunk=False).get_opcodes()
    ops, i, j = [], 0, 0
    for line in result.stdout.splitlines():
        hunk = HUNK.match(line)
        if not hunk:
            continue
        count_a = 1 if hunk[2] is None else int(hunk[2])
        count_b = 1 if hunk[4] is None else int(hunk[4])
        i1 = int(hunk[1]) - 1 if count_a else int(hunk[1])
        j1 = int(hunk[3]) - 1 if count_b else int(hunk[3])
        if i1 > i:
            ops.append(('equal', i, i1, j, j1))
        ops.append(('replace' if count_a and count_b else 'delete' if count_a else 'insert',
                    i1, i1 + count_a, j1, j1 + count_b))
        i, j = i1 + count_a, j1 + count_b
    if i < len(old):
        ops.append(('equal', i, len(old), j, len(new)))
    return ops


def map_line(opcodes, new, n, token, accept):
    """(current line or None, projected line, class) for old line n through the diff.

    accept(line) gives the field-rule class of the entry moved to that current line; a
    line whose class is not accepted is never returned."""
    i = n - 1
    for tag, i1, i2, j1, j2 in opcodes:
        if not i1 <= i < i2:
            continue
        projected = j1 + (i - i1) * max(1, j2 - j1) // max(1, i2 - i1) + 1
        if tag == 'equal':
            line = j1 + (i - i1) + 1
            how = accept(line)
            return (line, line, how) if how in ACCEPTED else (None, line, None)
        block = [j + 1 for j in range(max(0, j1 - 2), min(len(new), j2 + 2)) if token in squash(new[j])]
        ok = [(j, accept(j)) for j in block]
        ok = [(j, how) for j, how in ok if how in ACCEPTED]
        if not ok:
            return None, projected, None
        best, how = min(ok, key=lambda item: abs(item[0] - projected))
        return best, projected, how
    return None, n, None


def relocate(row, entries, texts, history=None, layouts=None):
    """{entry: (replacement, how)} for a row's stale or wrong string entries; duplicates share one result.

    how: 'history' (followed from the newest committed text where the entry held, through the
    diff to the current text, onto a line that passes the field rule), 'history-renamed' (as
    history, but the line passes only through a proven rename: review), 'history+field' or
    'field' (nearest line holding the cast that passes the field rule) or 'gone' (no such
    line left)."""
    cache = {}
    cited = set()
    for entry in row.get('retired_to_cast') or []:
        parsed = parse_entry(entry)
        if parsed['kind'] == 'site' and check_entry(entry, texts) == 'ok' \
                and field_class(row, entry, texts, layouts, cache) in ACCEPTED:
            for n in span_numbers(parsed, texts.lines(parsed['path']) or []):
                cited.add((parsed['path'], squash(parsed['cast']), n))
    out = {}
    for entry in sorted(set(entries), key=lambda e: (parse_entry(e)['path'], parse_entry(e)['line'])):
        parsed = parse_entry(entry)
        path, token = parsed['path'], squash(parsed['cast'])
        lines = texts.lines(path) or []
        numbers = [parsed['line']] + ([parsed['second']] if parsed['second'] else [])

        def at(line, the_lines=lines, the_layouts=layouts):
            moved = dict(parsed, line=line, second=None)
            return classify_lines(row, moved, the_lines, the_layouts, texts, cache)

        def held(old_lines):
            return all(at(n, old_lines, None) in ('field', 'alias', 'named', 'typedef') for n in numbers)
        rev, old = history.anchor(path, numbers, token, held) if history else (None, None)
        if old is None and history:
            # The field rule never held on a commit; the newest version whose cited lines hold the
            # cast text still gives the git line offsets, which beat a text search from the old number.
            rev, old = history.anchor(path, numbers, token)
        near = [i + 1 for i, t in enumerate(lines) if token in squash(t) and at(i + 1) in ACCEPTED]

        def free(n):
            return n is not None and (path, token, n) not in cited

        def nearest(pool, target):
            pool = [n for n in pool if free(n)]
            return min(pool, key=lambda n: (abs(n - target), n)) if pool else None
        found, how = [], 'history' if old else 'field'
        for n in numbers:
            choice, target, cls = (map_line(history.diff(rev, path, old, lines), lines, n, token, at)
                                   if old else (None, n, None))
            if free(choice) and cls == 'renamed':
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


def rederive(rows, results, texts, history=None, layouts=None):
    by_row = collections.defaultdict(list)
    for result in results:
        if isinstance(result['entry'], str) and parse_entry(result['entry'])['kind'] == 'site' \
                and (result['status'] in ('stale', 'noline') or result.get('field') == 'wrong'):
            by_row[result['id']].append(result['entry'])
    changes = []
    for row in rows:
        stale = by_row.get(row['id'])
        if not stale:
            continue
        mapping = relocate(row, stale, texts, history, layouts)
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

FLOOR_LEDGER = 'ledger/prototype_floors.jsonl'
CITED_PATH = re.compile(r'(?<![\w/.-])(?:src|include)/[\w/.-]+\.(?:c|h|inc)\b')


def planned_header(definition_path):
    """The interface header tools/headers/plan.py plans for a definition's directory."""
    parts = definition_path.split('/')[1:-1]
    return 'include/' + '/'.join(parts) + '.h'


def floor_cited_paths(row):
    """{path} that a prototype-floor row cites as evidence (the planned owner header excluded)."""
    definition = (row.get('definition') or {}).get('path') if isinstance(row.get('definition'), dict) else None
    plan = planned_header(definition) if definition else None
    found = set()

    def walk(value, key=None, parent=None):
        if isinstance(value, dict):
            for k, v in value.items():
                walk(v, k, key)
        elif isinstance(value, list):
            for v in value:
                walk(v, key, parent)
        elif isinstance(value, str):
            if value == plan and (key == 'owner' or (key == 'header' and parent == 'evidence')):
                return
            found.update(CITED_PATH.findall(value))
    walk(row)
    return found


def check_floor_paths(root, base):
    """(HEAD rows citing a missing path, the subset new vs BASE): [(name, sorted missing paths)]."""
    path = Path(root) / FLOOR_LEDGER
    if not path.is_file():
        return [], []
    head = read_ledger(path.read_text())
    shown = subprocess.run(['git', 'show', f'{base}:{FLOOR_LEDGER}'], cwd=root, capture_output=True, text=True)
    base_rows = read_ledger(shown.stdout) if shown.returncode == 0 else []
    base_texts = Texts(root, base)
    old = collections.defaultdict(set)
    for row in base_rows:
        old[row.get('name')].update(p for p in floor_cited_paths(row) if base_texts.lines(p) is None)
    exists = {}
    bad, new = [], []
    for row in head:
        missing = sorted(p for p in floor_cited_paths(row)
                         if not exists.setdefault(p, (Path(root) / p).is_file()))
        if missing:
            bad.append((row.get('name'), missing))
            fresh = [p for p in missing if p not in old.get(row.get('name'), set())]
            if fresh:
                new.append((row.get('name'), fresh))
    return bad, new


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('base', help='base revision to compare loads and staleness against')
    parser.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[2])
    parser.add_argument('--ledger', default=LEDGER)
    mode = parser.add_mutually_exclusive_group()
    mode.add_argument('--fail-new', action='store_true',
                      help='fail on retired_to_cast entries newly stale or newly wrong-field on HEAD')
    mode.add_argument('--fail-all', action='store_true', help='fail on every stale or wrong-field entry')
    parser.add_argument('--list', action='store_true', help='list every flagged entry and weak row')
    parser.add_argument('--no-layouts', action='store_true',
                        help='do not run clang for record layouts (renames become renamed?)')
    parser.add_argument('--rederive', action='store_true', help='propose current lines for stale entries')
    parser.add_argument('--write', action='store_true', help='with --rederive, rewrite the ledger')
    parser.add_argument('--public-ref', action='append', default=[],
                        help='a ref whose ancestors are public history, for "tree" hashes (repeatable)')
    args = parser.parse_args(argv)
    root = args.root.resolve()
    head_rows = read_ledger((root / args.ledger).read_text())
    shown = subprocess.run(['git', 'show', f'{args.base}:{args.ledger}'], cwd=root, capture_output=True, text=True)
    if shown.returncode:
        parser.error(f'cannot read {args.ledger} at {args.base}: {shown.stderr.strip()}')
    base_rows = read_ledger(shown.stdout)
    head_texts, base_texts = Texts(root), Texts(root, args.base)
    layouts = Layouts(root, not args.no_layouts)

    if args.rederive:
        results, _, _ = check_sites(head_rows, head_texts, layouts=layouts)
        changes = rederive(head_rows, results, head_texts, History(root), layouts)
        for change in changes:
            print(f"{change['how']:8} {change['id']}\n    {change['old']}\n -> {change['new']}")
        tally = collections.Counter(c['how'] for c in changes)
        print(f"re-derived {len(changes)} entries: " + ', '.join(f'{k} {v}' for k, v in sorted(tally.items())))
        if args.write:
            (root / args.ledger).write_text(''.join(json.dumps(r, sort_keys=True) + '\n' for r in head_rows))
            print(f'wrote {args.ledger}')
        return 0

    loads = check_loads(base_rows, head_rows)
    results, counts, fields = check_sites(head_rows, head_texts, base_rows, base_texts, layouts)
    weak = weak_evidence(head_rows, base_rows)
    stale = [r for r in results if r['status'] in STALE]
    wrong = [r for r in results if r['field'] == 'wrong']
    reported = [r for r in results if r['field'] in REPORTED]
    new_bad = [r for r in stale + wrong if r['new']]
    print(f"loads: rows with non-zero loads {loads['base']} -> {loads['head']}; zeroed {len(loads['zeroed'])}; "
          f"dropped rows {len(loads['dropped'])}")
    print('retired_to_cast: ' + ', '.join(f'{k} {counts[k]}' for k in
          ('ok', 'stale', 'noline', 'nofile', 'note', 'unparsed')) +
          f'; stale on HEAD {len(stale)} (new vs BASE {sum(1 for r in stale if r["new"])})')
    print('field rule: ' + ', '.join(f'{k} {fields[k]}' for k in FIELD_CLASSES) +
          f'; wrong on HEAD {len(wrong)} (new vs BASE {sum(1 for r in wrong if r["new"])})' +
          ('' if layouts.enabled else ' [no record layouts]'))
    w = weak['all']
    line = (f"weak evidence (report only): retired {weak['retired']}, with load data {w['rows']}, "
            f"<5 mapped loads {w['under5']}, exactly 1 {w['one']}; no load data {weak['no_load_data']}")
    if weak['newly_retired'] is not None:
        n = weak['newly_retired']
        line += f"; newly retired vs BASE {n['rows']} (<5 {n['under5']}, 1 {n['one']})"
    print(line)
    mismatched = evidence_load_mismatches(head_rows)
    print(f'evidence load numbers (report only): {len({m[0] for m in mismatched})} rows quote counts that '
          f'differ from their own loads ({len(mismatched)} ops)')
    flagged = stale + wrong
    if args.list:
        listed = flagged + reported
    elif args.fail_all:
        listed = flagged
    elif args.fail_new:
        listed = new_bad
    else:
        listed = flagged[:10]
    for r in listed:
        label = r['status'].upper() if r['status'] in STALE else r['field'].upper()
        print(f"  {'NEW ' if r['new'] and r in flagged else ''}{label} {r['id']}: {r['entry']}")
    if not (args.list or args.fail_all or args.fail_new) and len(flagged) > 10:
        print(f'  ... {len(flagged) - 10} more (--list)')
    if args.list:
        for row in head_rows:
            if row.get('status') == 'retired' and 0 < mapped_loads(row) < 5:
                print(f'  WEAK {mapped_loads(row)} {row["id"]}')
        for rid, op, numbers, actual in mismatched:
            print(f'  EVIDENCE-LOADS {rid}: {op} stated {numbers}, loads field has {actual}')
    for problem in loads['problems']:
        print('LOADS ' + problem)
    floors_head = root / FLOORS
    if floors_head.is_file():
        shown_floors = subprocess.run(['git', 'show', f'{args.base}:{FLOORS}'], cwd=root, capture_output=True, text=True)
        floor_rows, floor_bad, floor_new = check_floors(
            root, args.base, floors_head.read_text(), shown_floors.stdout if shown_floors.returncode == 0 else None)
    else:
        floor_rows, floor_bad, floor_new = [], [], []
    print(f'floor blocking spellings: {len(floor_rows)} entries, stale on HEAD {len(floor_bad)} '
          f'(new vs BASE {len(floor_new)}), unparsed {sum(1 for r in floor_rows if r["status"] == "unparsed")}')
    for r in (floor_bad if (args.list or args.fail_all) else floor_new):
        print(f"  {'NEW ' if r in floor_new else ''}FLOOR {r['status'].upper()} {r['name']} "
              f"blocking[{r['index']}] {r['file']}: {r['entry']}")
    floor_missing, floor_missing_new = check_floor_paths(root, args.base)
    print(f'floor cited paths: {len(floor_missing)} rows cite a missing src/include file '
          f'(new vs BASE {len(floor_missing_new)})')
    for name, missing in (floor_missing if (args.list or args.fail_all) else floor_missing_new):
        print(f"  {'NEW ' if any(n == name for n, _ in floor_missing_new) else ''}FLOOR PATH {name}: "
              + ', '.join(missing))
    copy_families, copy_problems = placed_copies.check(root)
    print(f'placed copies: {len(copy_families)} families, '
          f'{sum(len(v) - 1 for v in copy_families.values())} copies, {len(copy_problems)} differ or cannot be found')
    for problem in copy_problems:
        print('  PLACED COPY ' + problem)
    lane_local = ledger_public.check(root, args.base, public_ref=args.public_ref)
    failed = (bool(loads['problems']) or (args.fail_all and flagged) or (args.fail_new and new_bad)
              or (args.fail_all and floor_bad) or (args.fail_new and floor_new)
              or (args.fail_new and floor_missing_new) or (args.fail_all and floor_missing)
              or ((args.fail_new or args.fail_all) and lane_local > 0)
              or ((args.fail_new or args.fail_all) and copy_problems))
    print('ledger integrity ' + ('FAIL' if failed else 'PASS'))
    return 1 if failed else 0


if __name__ == '__main__':
    sys.exit(main())
