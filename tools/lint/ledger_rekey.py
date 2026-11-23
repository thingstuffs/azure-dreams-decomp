#!/usr/bin/env python3
"""Rewrite the ledger and baseline keys that embed a renamed record member or symbol.

    ledger_rekey.py [--root R] (--members TABLE ... | --symbols TABLE ... | --between OLD NEW) [--base REV]
                    (--check | --write) [--list] [--only NAME,...] [--skip-collisions]

A member rename (`record.old -> new`) or a symbol rename (a function or data name) leaves keys behind in the ledgers
and baselines: union ids are `header::Owner.member`, debt baseline keys are `function#n` per file, prototype floors
name functions and callers, bridge casts spell members and functions.  tools/lint/ledger_refresh.py re-derives paths
and the names config/names.tsv has seen; it does not know a member rename and cannot place a name that stays alive
in another image.  This tool takes the rename tables themselves and rewrites each key with that ledger's own
grammar - never a blind text replace.

Input
  --members TABLE   member renames in the member-pack / rename_members_batch row format (columns record, header,
                    old_member|old, new_member|new_name|new, optional offset; a `status` column from a
                    rename_members_batch report keeps only `renamed`/`would_rename` rows; action/type/confidence
                    columns follow rename_members_batch.load_rows)
  --symbols TABLE   symbol renames: a header line naming old_name and new_name (renames.tsv of a rename package;
                    scope_files and id are carried), or header-less config/names.tsv style rows `addr old new ...`
  --between A B     derive both tables from the token-level diff of every src/ and include/ file between two
                    revisions: an identifier that differs at the same token position is a rename (a member when it
                    follows `->` or `.`).  Files whose token streams differ in length are reported and skipped.
  --base REV        the revision before the renames: debt baseline keys are re-numbered by definition position
                    between REV and the tree (without it a key keeps its occurrence number)

Every rename is applied only where the CURRENT tree shows it: a function key moves in a file that now defines the
new name and no longer the old one (an old name that stays alive in another image keeps its keys there), a union id
moves only to an id the union census of that file now produces.  A key whose new form already exists with different
content is a COLLISION: the run refuses and writes nothing (--skip-collisions migrates the rest).

Ledgers (own grammar each):
  debt        tools/lint/debt_baseline.json by_file scope keys `symbol#n`; bad_label_sites `file::Owner.path#n`
  union_ids   ledger/unions.jsonl id/owner/path (live rows by the union census, retired rows by the header's declared
              members), tools/lint/union_baseline.json ids (`file::Owner.member`)
  floors      ledger/prototype_floors.jsonl name, definition.proto, arity_evidence[].caller, blocking[].spelling
  proto       tools/lint/proto_baseline.json candidate_sites `function::declaration::definition::class`
  accepted    tools/lint/accepted_warning_sites.tsv function and callees
  soundness   tools/lint/soundness_gcc_baseline.json identities [file, function, ...]
  bridges     ledger/bridge_casts.jsonl function, site_id and the member/function spellings of cast_text
  fields      ledger/fields.jsonl census rows (type, name, off: name and previous_name), site rows `file:function:var`
History tables (ledger/names.jsonl, ledger/prototype_identities.jsonl, layout_inline) and frozen text
(`(renamed from X)`, func_<addr> identities) are never rewritten.

Report per ledger: migrated, already-new, collisions, untouched (old keys that name a renamed symbol/member but
could not be placed, with the reason).  --check writes nothing and exits 1 when anything would change; --write
saves every changed file with tools/atomic_io (temp file in the same directory, fsync, rename, under the ledger lock).
"""
from __future__ import annotations

import argparse
import collections
import csv
import json
import re
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(HERE.parent))
sys.path.insert(0, str(HERE.parent / 'readability'))
sys.path.insert(0, str(HERE.parent / 'typing'))
import atomic_io  # noqa: E402
import score  # noqa: E402

DEBT = 'tools/lint/debt_baseline.json'
UNION_BASELINE = 'tools/lint/union_baseline.json'
UNIONS = 'ledger/unions.jsonl'
FLOORS = 'ledger/prototype_floors.jsonl'
PROTO = 'tools/lint/proto_baseline.json'
ACCEPTED = 'tools/lint/accepted_warning_sites.tsv'
SOUNDNESS = 'tools/lint/soundness_gcc_baseline.json'
BRIDGES = 'ledger/bridge_casts.jsonl'
FIELDS = 'ledger/fields.jsonl'
LEDGERS = ('debt', 'union_ids', 'floors', 'proto', 'accepted', 'soundness', 'bridges', 'fields')

IDENT = re.compile(r'[A-Za-z_]\w*')
IDENT_ONLY = re.compile(r'^[A-Za-z_]\w*$')
STRIP = re.compile(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', re.S)


class Collision(Exception):
    pass


# ---------------------------------------------------------------- rename tables

class Member:
    def __init__(self, record, header, old, new, offset=None, src=''):
        self.record, self.header, self.old, self.new, self.offset, self.src = record, header, old, new, offset, src


def _columns(path):
    with open(path, newline='', encoding='utf-8') as handle:
        lines = [line for line in handle.read().splitlines() if line.strip() and not line.startswith('#')]
    if not lines:
        return [], []
    reader = list(csv.reader(lines, delimiter='\t', quoting=csv.QUOTE_NONE))
    return reader[0], reader[1:]


def read_members(path):
    """Rows of a member-pack or rename_members_batch report table (the loader's skip rules, plus `status`)."""
    head, rows = _columns(path)

    def col(*names):
        for name in names:
            if name in head:
                return head.index(name)
        return None
    ir, ih, io = col('record', 'struct'), col('header'), col('old_member', 'old', 'field')
    inw, iof = col('new_member', 'new_name', 'new', 'to'), col('offset')
    ia, it, ic, ik, ist = col('action'), col('type'), col('confidence'), col('kind'), col('status')
    if io is None or inw is None:
        raise SystemExit(f'{path}: need old_member and new_member columns, got {head}')
    out = []
    for n, cells in enumerate(rows, 2):
        def cell(i):
            return cells[i].strip() if i is not None and i < len(cells) else ''
        if ist is not None and cell(ist) not in ('renamed', 'would_rename'):
            continue
        if ia is not None and cell(ia) != 'rename':
            continue
        if ik is not None and cell(ik) not in ('', 'rename'):
            continue
        if it is not None and cell(it) not in ('', '-'):
            continue
        if ic is not None and cell(ic) not in ('proven', 'likely'):
            continue
        old, new = cell(io), cell(inw)
        if not IDENT_ONLY.match(old) or not IDENT_ONLY.match(new) or old == new:
            continue
        try:
            offset = int(cell(iof), 0) if cell(iof) not in ('', '-') else None
        except ValueError:
            offset = None
        out.append(Member(cell(ir), cell(ih), old, new, offset, f'{Path(path).name}:{n}'))
    return out


def read_symbols(path):
    """[(old, new, scope_files tuple)]: a header with old_name/new_name, or config/names.tsv style `addr old new`."""
    head, rows = _columns(path)
    out = []
    if 'old_name' in head and 'new_name' in head:
        io, inw = head.index('old_name'), head.index('new_name')
        isc = head.index('scope_files') if 'scope_files' in head else None
        for cells in rows:
            if max(io, inw) >= len(cells):
                continue
            old, new = cells[io].strip(), cells[inw].strip()
            scope = tuple(x for x in cells[isc].split(';') if x) if isc is not None and isc < len(cells) else ()
            if IDENT_ONLY.match(old) and IDENT_ONLY.match(new) and old != new:
                out.append((old, new, scope))
        return out
    for cells in ([head] if head and head[0].startswith('0x') else []) + rows:
        if len(cells) >= 3 and cells[0].startswith('0x') and IDENT_ONLY.match(cells[1]) \
                and IDENT_ONLY.match(cells[2]) and cells[1] != cells[2]:
            out.append((cells[1].strip(), cells[2].strip(), ()))
    return out


class Tables:
    def __init__(self, members=(), symbols=()):
        self.members = list(members)
        self.symbols = list(symbols)
        self.member_new = collections.defaultdict(set)      # old member -> {new}
        self.member_rows = collections.defaultdict(list)    # old member -> [Member]
        for m in self.members:
            self.member_new[m.old].add(m.new)
            self.member_rows[m.old].append(m)
        self.symbol_new = collections.defaultdict(set)      # old symbol -> {new}
        for old, new, _ in self.symbols:
            self.symbol_new[old].add(new)

    def any(self):
        return bool(self.members or self.symbols)


# ---------------------------------------------------------------- tree

def strip_code(text):
    return STRIP.sub(' ', text)


def function_keys(text):
    """[`symbol#n`] in definition order: the per-file function keys tools/lint/debt_check.py baselines."""
    tokens = score.lex(text)
    pairs = score.pairs_of(tokens)[0]
    seen = collections.Counter()
    keys = []
    for _start, name, _body, _end, _style in score.definitions(tokens, pairs):
        symbol = tokens[name].value
        seen[symbol] += 1
        keys.append(f'{symbol}#{seen[symbol]}')
    return keys


def live_union_ids(rel, text):
    """The ids tools/typing/union_census.census gives the unions of one file."""
    from union_census import aggregates, after_brace
    if not re.search(r'\bunion\b', text):
        return []
    tokens = score.lex(text)
    pairs, _ = score.pairs_of(tokens)
    aggs = aggregates(tokens, pairs)
    used = collections.Counter()
    ids = []
    for agg in aggs:
        if agg['kind'] != 'union':
            continue
        parent = min((a for a in aggs if a['body'] < agg['start'] < a['end']),
                     key=lambda a: a['end'] - a['body'], default=None)
        field = after_brace(tokens, agg['end'])
        owner = parent['name'] if parent else agg['name']
        if not owner:
            owner = Path(rel).stem
        keypart = field or agg['name'] or f'anonymous@{text.count(chr(10), 0, tokens[agg["start"]].pos) + 1}'
        key = f'{rel}::{owner}.{keypart}'
        used[key] += 1
        ids.append(key + (f'#{used[key]}' if used[key] > 1 else ''))
    return ids


def live_bad_label_sites(rel, text):
    import debt_check as D
    return [row['site'] for row in D.union_sites(rel, text)[1]]


class Tree:
    def __init__(self, root, base=None):
        self.root, self.base = Path(root), base
        self._text, self._ids, self._keys, self._union, self._bad, self._base = {}, {}, {}, {}, {}, {}
        self._declared = {}
        self._global = None
        self._tags = {}

    def exists(self, rel):
        return (self.root / rel).is_file()

    def text(self, rel):
        if rel not in self._text:
            path = self.root / rel
            self._text[rel] = path.read_text(errors='replace') if path.is_file() else None
        return self._text[rel]

    def ids(self, rel):
        if rel not in self._ids:
            text = self.text(rel)
            self._ids[rel] = set(IDENT.findall(strip_code(text))) if text is not None else set()
        return self._ids[rel]

    def keys(self, rel):
        if rel not in self._keys:
            text = self.text(rel)
            self._keys[rel] = function_keys(text) if text is not None else []
        return self._keys[rel]

    def union_ids(self, rel):
        if rel not in self._union:
            text = self.text(rel)
            self._union[rel] = set(live_union_ids(rel, text)) if text is not None else set()
        return self._union[rel]

    def declared_ids(self, rel):
        """`file::Owner.member` for every member of every struct and union the file declares (owner spelled with
        its tag and with its typedef name): the ids a RETIRED union row can still name for a renamed member."""
        if rel not in self._declared:
            text = self.text(rel)
            found = set()
            if text is not None:
                from union_census import aggregates, after_brace, member_decls
                tokens = score.lex(text)
                pairs, _ = score.pairs_of(tokens)
                for agg in aggregates(tokens, pairs):
                    owners = {agg['name'], after_brace(tokens, agg['end'])} - {None}
                    for member in member_decls(tokens, pairs, agg['body'], agg['end']):
                        found |= {f'{rel}::{o}.{member["name"]}' for o in owners}
            self._declared[rel] = found
        return self._declared[rel]

    def bad_sites(self, rel):
        if rel not in self._bad:
            text = self.text(rel)
            self._bad[rel] = set(live_bad_label_sites(rel, text)) if text is not None else set()
        return self._bad[rel]

    def base_text(self, rel):
        if not self.base:
            return None
        if rel not in self._base:
            run = subprocess.run(['git', 'show', f'{self.base}:{rel}'], cwd=self.root, capture_output=True,
                                 text=True, errors='replace')
            self._base[rel] = run.stdout if run.returncode == 0 else None
        return self._base[rel]

    def tags(self, header, record):
        """The record's own name plus the struct tag(s) of its typedef (a union id is spelled with the tag)."""
        key = (header, record)
        if key not in self._tags:
            names = {record}
            text = self.text(header) if header else None
            if text:
                for m in re.finditer(r'\}\s*' + re.escape(record) + r'\s*;', text):
                    k = text.rfind('typedef struct', 0, m.start())
                    t = re.match(r'typedef struct\s+(\w+)\s*\{', text[k:]) if k >= 0 else None
                    if t:
                        names.add(t.group(1))
            self._tags[key] = names
        return self._tags[key]

    def global_ids(self):
        """Identifiers of the whole src/ and include/ code (one pass, lazily)."""
        if self._global is None:
            found = set()
            for top in ('src', 'include'):
                for path in sorted((self.root / top).rglob('*')):
                    if path.suffix in ('.c', '.h') and path.is_file() and path.stat().st_size < 4_000_000:
                        found.update(IDENT.findall(strip_code(path.read_text(errors='replace'))))
            self._global = found
        return self._global


# ---------------------------------------------------------------- report

class Report:
    def __init__(self):
        self.stats = {name: collections.Counter() for name in LEDGERS}
        self.detail = {name: [] for name in LEDGERS}
        self.collisions = []

    def migrated(self, ledger, what):
        self.stats[ledger]['migrated'] += 1
        self.detail[ledger].append(('migrated', what))

    def already(self, ledger, what):
        self.stats[ledger]['already-new'] += 1
        self.detail[ledger].append(('already-new', what))

    def collision(self, ledger, what):
        self.stats[ledger]['collisions'] += 1
        self.detail[ledger].append(('COLLISION', what))
        self.collisions.append((ledger, what))

    def untouched(self, ledger, what):
        self.stats[ledger]['untouched'] += 1
        self.detail[ledger].append(('untouched', what))

    def total_changes(self):
        return sum(c['migrated'] for c in self.stats.values())

    def lines(self, listing=False, only=None):
        out = [f'{"ledger":<10} {"migrated":>8} {"already-new":>11} {"collisions":>10} {"untouched":>9}']
        for name in LEDGERS:
            if only and name not in only:
                continue
            s = self.stats[name]
            out.append(f'{name:<10} {s["migrated"]:>8} {s["already-new"]:>11} {s["collisions"]:>10} {s["untouched"]:>9}')
        for name in LEDGERS:
            if only and name not in only:
                continue
            for kind, what in self.detail[name]:
                if listing or kind in ('COLLISION', 'untouched'):
                    out.append(f'  {name}: {kind}: {what}')
        return out


# ---------------------------------------------------------------- the rekeyer

class Rekey:
    def __init__(self, root, tables, base=None, only=None, retired=True):
        self.root = Path(root)
        self.retired = retired
        self.tables, self.base = tables, base
        self.tree = Tree(root, base)
        self.report = Report()
        self.out = {}                                   # rel -> new text
        self.only = set(only) if only else None
        self.original = {}

    # -- plumbing

    def read(self, rel):
        if rel in self.out:
            return self.out[rel]
        if rel not in self.original:
            path = self.root / rel
            self.original[rel] = path.read_text() if path.is_file() else None
        return self.original[rel]

    def set(self, rel, text):
        self.read(rel)
        if text != self.original.get(rel):
            self.out[rel] = text
        else:
            self.out.pop(rel, None)

    def changed(self):
        return sorted(self.out)

    def write(self):
        for rel in self.changed():
            atomic_io.write_text(self.root / rel, self.out[rel])

    def wanted(self, ledger):
        return not self.only or ledger in self.only

    # -- symbol resolution (the tree decides)

    def resolve(self, rel, name):
        """The new spelling of `name` in file rel: exactly one table candidate that rel spells while it no longer
        spells `name`; None when the tree does not show a rename there; the string 'ambiguous' on several."""
        news = self.tables.symbol_new.get(name)
        if not news or not rel or not self.tree.exists(rel):
            return None
        ids = self.tree.ids(rel)
        if name in ids:
            return None
        live = sorted(n for n in news if n in ids)
        if len(live) == 1:
            return live[0]
        return 'ambiguous' if live else None

    def resolve_global(self, name):
        """Rename of a name that no file spells any more (a floor row whose definition file is a header)."""
        news = self.tables.symbol_new.get(name)
        if not news:
            return None
        ids = self.tree.global_ids()
        if name in ids:
            return None
        live = sorted(n for n in news if n in ids)
        return live[0] if len(live) == 1 else ('ambiguous' if live else None)

    def resolve_any(self, files, name):
        found = {self.resolve(f, name) for f in files if isinstance(f, str)}
        found.discard(None)
        if len(found) == 1:
            return found.pop()
        return 'ambiguous' if found else None

    def retoken(self, text, files):
        """Identifier tokens of a declaration or cast text that name a renamed symbol in the cited files."""
        def sub(m):
            new = self.resolve_any(files, m.group(0)) if m.group(0) in self.tables.symbol_new else None
            return new if new and new != 'ambiguous' else m.group(0)
        return IDENT.sub(sub, text)

    # -- debt baseline

    def debt(self):
        text = self.read(DEBT)
        if text is None:
            return
        import debt_check as D
        data = json.loads(text)
        r = self.report
        for directory in sorted(data['by_file']):
            for name in sorted(data['by_file'][directory]):
                rel = f'{directory}/{name}'
                scopes = data['by_file'][directory][name][1]
                stale = [k for k in scopes if '#' in k and k.rpartition('#')[0] in self.tables.symbol_new]
                if not stale:
                    continue
                keymap = self._key_map(rel)
                for key in sorted(stale):
                    symbol = key.rpartition('#')[0]
                    new_symbol = self.resolve(rel, symbol)
                    if new_symbol is None:
                        if symbol in self.tree.ids(rel) or not self.tree.exists(rel):
                            continue            # the old name is still defined here (another image), or no file
                        r.untouched('debt', f'{rel}::{key}: the file spells none of the new names')
                        continue
                    if new_symbol == 'ambiguous':
                        r.untouched('debt', f'{rel}::{key}: several new names are spelled in the file')
                        continue
                    new_key = keymap.get(key) or f'{new_symbol}#{key.rpartition("#")[2]}'
                    if not new_key.startswith(new_symbol + '#') or new_key not in self.tree.keys(rel):
                        r.untouched('debt', f'{rel}::{key}: no `{new_key}` definition in the tree')
                        continue
                    if new_key in scopes:
                        if scopes[new_key] == scopes[key]:
                            del scopes[key]
                            r.migrated('debt', f'{rel}::{key} -> {new_key} (equal row already present)')
                        else:
                            r.collision('debt', f'{rel}::{key} -> {new_key}: the new key holds a different row')
                        continue
                    scopes[new_key] = scopes.pop(key)
                    r.migrated('debt', f'{rel}::{key} -> {new_key}')
        self.bad_label_sites(data)
        new_text = D.baseline_text(data)
        self.set(DEBT, new_text)

    def _key_map(self, rel):
        """old key -> new key by definition position between --base and the tree (empty without --base)."""
        base_text = self.tree.base_text(rel)
        if base_text is None:
            return {}
        old, new = function_keys(base_text), self.tree.keys(rel)
        if len(old) != len(new):
            return {}
        return {a: b for a, b in zip(old, new) if a != b}

    def bad_label_sites(self, data):
        sites = data.get('bad_label_sites', [])
        present = set(sites)
        out = []
        for site in sites:
            base, _, ordinal = site.partition('#')
            rel = base.split('::')[0]
            if not self.tree.exists(rel) or site in self.tree.bad_sites(rel):
                out.append(site)
                continue
            found = self._candidates(site, rel, self.tree.bad_sites(rel))
            if not found:
                if self._mentions_renamed(site):
                    self.report.untouched('debt', f'bad_label_sites {site}: no live site under the new names')
                out.append(site)
                continue
            if len(found) > 1:
                self.report.untouched('debt', f'bad_label_sites {site}: several live sites: {found}')
                out.append(site)
                continue
            new = found[0]
            if new in present:
                self.report.already('debt', f'bad_label_sites {site} -> {new}')
                continue
            present.add(new)
            out.append(new)
            self.report.migrated('debt', f'bad_label_sites {site} -> {new}')
        if out != sites:
            data['bad_label_sites'] = sorted(out)

    # -- union ids

    def _mentions_renamed(self, ident):
        names = set(IDENT.findall(ident.partition('::')[2]))
        return bool(names & (set(self.tables.member_new) | set(self.tables.symbol_new)))

    def _member_options(self, owner, part):
        """New spellings of member `part` of record `owner`: the table rows of that record (its typedef name or struct
        tag), or every row when the table carries no record (a --between table)."""
        out = set()
        for m in self.tables.member_rows.get(part, ()):
            if not m.record or owner == m.record or owner in self.tree.tags(m.header, m.record):
                out.add(m.new)
        return out

    def _candidates(self, ident, rel, live):
        """Live ids reachable from `ident` by renaming member and symbol components (owner.path#n)."""
        base, hashmark, ordinal = ident.partition('#')
        _file, _, rest = base.partition('::')
        parts = rest.split('.')
        choices = []
        for i, part in enumerate(parts):
            options = {part}
            if i == 0:
                options |= self.tables.symbol_new.get(part, set())
            else:
                owner = parts[0]
                options |= self._member_options(owner, part) if i == 1 else self.tables.member_new.get(part, set())
                options |= self.tables.symbol_new.get(part, set())
            choices.append(sorted(options, key=lambda o: o != part))
        out = []
        for combo in _product(choices):
            cand = f'{rel}::{".".join(combo)}{hashmark}{ordinal}'
            if cand != ident and cand in live:
                out.append(cand)
        return out

    def _cited_sites_spell(self, row, old_id, new_id):
        """True when the retired row's cited cast lines spell the renamed member by its new name and none by the old
        one (a row citing `debris->unk_0A` stays `unk_0A` when it is another record's member that was renamed)."""
        old = old_id.partition('::')[2].partition('#')[0].split('.')
        new = new_id.partition('::')[2].partition('#')[0].split('.')
        changed = [(a, b) for a, b in zip(old, new) if a != b and old.index(a) > 0]
        if not changed:
            return False
        a, b = changed[-1]
        has_new = has_old = False
        for entry in row.get('retired_to_cast') or []:
            if not isinstance(entry, str):
                continue
            m = re.match(r'^(\S+?):(\d+)(?:-(\d+))?\b', entry)
            text = self.tree.text(m.group(1)) if m else None
            if not text:
                continue
            lines = text.splitlines()
            first, last = int(m.group(2)), int(m.group(3) or m.group(2))
            span = ' '.join(lines[max(first - 1, 0):min(last + 1, len(lines))])
            has_new = has_new or bool(re.search(r'(?:->|\.)\s*' + re.escape(b) + r'\b', span))
            has_old = has_old or bool(re.search(r'(?:->|\.)\s*' + re.escape(a) + r'\b', span))
        return has_new and not has_old

    def union_ids(self):
        import ledger_refresh as R
        r = self.report
        tracked = {}                        # id -> line index in the ledger
        text = self.read(UNIONS)
        lines = text.splitlines() if text is not None else []
        rows = [json.loads(line) if line.strip() else None for line in lines]
        for i, row in enumerate(rows):
            if row:
                tracked[row['id']] = i
        renamed = {}                        # old id -> new id (shared by the three stores)
        for i, row in enumerate(rows):
            if not row or not isinstance(row.get('id'), str):
                continue
            rel = row.get('file') or row['id'].split('::')[0]
            retired = row.get('status') == 'retired'
            if retired and not self.retired:
                continue
            if not self.tree.exists(rel) or row['id'] in self.tree.union_ids(rel):
                continue
            if retired and row['id'] in self.tree.declared_ids(rel):
                continue
            if not self._mentions_renamed(row['id']):
                continue
            # a live row must reach an id the union census now produces; a retired row (the union is gone) the
            # member of a record the file now declares under the new name
            found = self._candidates(row['id'], rel, self.tree.declared_ids(rel) if retired
                                     else self.tree.union_ids(rel))
            if retired:
                # history: it follows the rename only where its own cast sites now spell the new member
                found = [c for c in found if self._cited_sites_spell(row, row['id'], c)]
            if not found:
                if retired:
                    continue                    # a retired row of a member that was not renamed: history, not stale
                r.untouched('union_ids', f'{UNIONS}: {row["id"]}: no live id under the new names')
                continue
            if len(found) > 1:
                r.untouched('union_ids', f'{UNIONS}: {row["id"]}: several live ids under the new names: {found}')
                continue
            new = found[0]
            if new in tracked and tracked[new] != i:
                r.collision('union_ids', f'{row["id"]} -> {new}: the ledger already tracks the new id')
                continue
            renamed[row['id']] = new
        out = list(lines)
        for i, row in enumerate(rows):
            if not row or row.get('id') not in renamed:
                continue
            new_row = dict(row)
            new_id = renamed[row['id']]
            new_row['id'] = new_id
            owner, _, rest = new_id.partition('::')[2].partition('#')[0].partition('.')
            if 'owner' in new_row:
                new_row['owner'] = owner
            if 'path' in new_row and rest:
                new_row['path'] = rest
            kwargs = R.json_line_format(lines[i], row)
            if kwargs is None:
                r.untouched('union_ids', f'{UNIONS}: {row["id"]}: row format not reproducible, not rewritten')
                renamed.pop(row['id'])
                continue
            out[i] = json.dumps(new_row, **kwargs)
            r.migrated('union_ids', f'{UNIONS}: {row["id"]} -> {new_id}')
        if text is not None:
            self.set(UNIONS, '\n'.join(out) + ('\n' if text.endswith('\n') else ''))
        base_text = self.read(UNION_BASELINE)
        if base_text is not None:
            data = json.loads(base_text)
            ids = list(data.get('ids', []))
            present = set(ids)
            new_ids = []
            for old in ids:
                if old in renamed:
                    new = renamed[old]
                    if new in present:
                        r.collision('union_ids', f'{UNION_BASELINE}: {old} -> {new} already listed')
                        new_ids.append(old)
                    else:
                        present.add(new)
                        new_ids.append(new)
                        r.migrated('union_ids', f'{UNION_BASELINE}: {old} -> {new}')
                else:
                    new_ids.append(old)
            if new_ids != ids:
                data['ids'] = sorted(new_ids) if ids == sorted(ids) else new_ids
                kwargs, tail = R.json_file_format(base_text, json.loads(base_text))
                self.set(UNION_BASELINE, json.dumps(data, **(kwargs or dict(indent=1))) + (tail if kwargs else '\n'))

    # -- prototype floors

    def floors(self):
        import ledger_refresh as R
        text = self.read(FLOORS)
        if text is None:
            return
        r = self.report
        lines = text.splitlines()
        rows = [json.loads(line) if line.strip() else None for line in lines]
        names = collections.Counter(row.get('name') for row in rows if row)
        out = list(lines)
        for i, row in enumerate(rows):
            if not row:
                continue
            new = json.loads(lines[i])
            files = self._floor_files(row)
            before = json.dumps(new, sort_keys=True)
            name = row.get('name')
            if isinstance(name, str) and name in self.tables.symbol_new:
                renamed = self.resolve_any(files[:1] or files, name)
                if renamed is None:
                    renamed = self.resolve_global(name) if not files or not any(
                        self.tree.exists(f) and name in self.tree.ids(f) for f in files) else None
                if renamed == 'ambiguous':
                    r.untouched('floors', f'{FLOORS}:{i + 1} {name}: several new names')
                elif renamed:
                    if names.get(renamed):
                        r.collision('floors', f'{FLOORS}:{i + 1} {name} -> {renamed}: a floor row of that name exists')
                        continue
                    new['name'] = renamed
                    names[renamed] += 1
                elif any(self.tree.exists(f) and name not in self.tree.ids(f) for f in files[:1]):
                    r.untouched('floors', f'{FLOORS}:{i + 1} {name}: definition file {files[0]} no longer spells it and '
                                f'no new name is spelled there')
            self._floor_text(new, row, files)
            if json.dumps(new, sort_keys=True) == before:
                continue
            kwargs = R.json_line_format(lines[i], row)
            if kwargs is None:
                r.untouched('floors', f'{FLOORS}:{i + 1}: row format not reproducible, not rewritten')
                continue
            out[i] = json.dumps(new, **kwargs)
            r.migrated('floors', f'{FLOORS}:{i + 1} {row.get("name")}' + (
                f' -> {new["name"]}' if new.get('name') != row.get('name') else ' (citations)'))
        self.set(FLOORS, '\n'.join(out) + ('\n' if text.endswith('\n') else ''))

    @staticmethod
    def _floor_files(row):
        files = []
        definition = row.get('definition')
        if isinstance(definition, dict) and isinstance(definition.get('path'), str):
            files.append(definition['path'])
        for key in ('blocking', 'arity_evidence'):
            for entry in row.get(key) or []:
                if isinstance(entry, dict):
                    for field in ('declaration', 'path'):
                        if isinstance(entry.get(field), str) and entry[field] not in files:
                            files.append(entry[field])
        return files

    def _floor_text(self, new, row, files):
        for entry in new.get('arity_evidence') or []:
            if isinstance(entry, dict) and isinstance(entry.get('caller'), str) and isinstance(entry.get('path'), str):
                renamed = self.resolve(entry['path'], entry['caller'])
                if renamed and renamed != 'ambiguous':
                    entry['caller'] = renamed
        for entry in new.get('blocking') or []:
            if isinstance(entry, dict) and isinstance(entry.get('spelling'), str):
                where = [entry[k] for k in ('declaration', 'path') if isinstance(entry.get(k), str)]
                entry['spelling'] = self.retoken(entry['spelling'], where)
        definition = new.get('definition')
        if isinstance(definition, dict) and isinstance(definition.get('proto'), str) and isinstance(
                definition.get('path'), str):
            definition['proto'] = self.retoken(definition['proto'], [definition['path']])

    # -- proto baseline

    def proto(self):
        import ledger_refresh as R
        text = self.read(PROTO)
        if text is None:
            return
        data = json.loads(text)
        sites = data.get('candidate_sites', [])
        present = set(sites)
        out = []
        r = self.report
        for site in sites:
            parts = site.split('::')
            paths = [p for p in parts[1:] if p.startswith(('src/', 'include/'))]
            new_name = self.resolve_any(paths, parts[0]) if parts[0] in self.tables.symbol_new else None
            if new_name == 'ambiguous':
                r.untouched('proto', f'{site}: several new names')
                out.append(site)
            elif new_name:
                new_site = '::'.join([new_name] + parts[1:])
                if new_site in present:
                    r.already('proto', f'{site} -> {new_site}')
                    continue
                present.add(new_site)
                out.append(new_site)
                r.migrated('proto', f'{site} -> {new_site}')
            else:
                if parts[0] in self.tables.symbol_new and not any(
                        self.tree.exists(p) and parts[0] in self.tree.ids(p) for p in paths):
                    r.untouched('proto', f'{site}: no cited file spells a new name')
                out.append(site)
        if out != sites:
            kwargs, tail = R.json_file_format(text, data)
            data['candidate_sites'] = sorted(out) if sites == sorted(sites) else out
            self.set(PROTO, json.dumps(data, **(kwargs or dict(indent=2))) + (tail if kwargs else '\n'))

    # -- accepted warning sites

    def accepted(self):
        text = self.read(ACCEPTED)
        if text is None:
            return
        r = self.report
        lines = text.split('\n')
        keys = {}
        for i, line in enumerate(lines):
            cols = line.split('\t')
            if not line.startswith('#') and len(cols) >= 4 and cols[0] != 'warning':
                keys[(cols[0], cols[1], cols[2])] = i
        out = list(lines)
        for i, line in enumerate(lines):
            cols = line.split('\t')
            if line.startswith('#') or len(cols) < 4 or cols[0] == 'warning':
                continue
            new = list(cols)
            renamed = self.resolve(cols[1], cols[2]) if cols[2] in self.tables.symbol_new else None
            if renamed == 'ambiguous':
                r.untouched('accepted', f'{ACCEPTED}:{i + 1} {cols[2]}: several new names')
            elif renamed:
                new[2] = renamed
            if len(cols) > 4 and cols[4]:
                callees = [self.resolve(cols[1], c) if c in self.tables.symbol_new else None for c in cols[4].split(',')]
                new[4] = ','.join(c if c and c != 'ambiguous' else old for c, old in zip(callees, cols[4].split(',')))
            if new == cols:
                continue
            key = (new[0], new[1], new[2])
            if new[2] != cols[2] and key in keys and keys[key] != i:
                r.collision('accepted', f'{ACCEPTED}:{i + 1} {cols[2]} -> {new[2]}: that warning row exists')
                continue
            out[i] = '\t'.join(new)
            r.migrated('accepted', f'{ACCEPTED}:{i + 1} {cols[2]} -> {new[2]}' + (
                f' callees {cols[4]} -> {new[4]}' if len(cols) > 4 and new[4] != cols[4] else ''))
        self.set(ACCEPTED, '\n'.join(out))

    # -- soundness baseline

    def soundness(self):
        import ledger_refresh as R
        text = self.read(SOUNDNESS)
        if text is None:
            return
        data = json.loads(text)
        r = self.report
        changed = False
        for key in ('identities', 'identity_counts'):
            rows = data.get(key)
            if not isinstance(rows, list):
                continue
            present = {(row[0], row[1]) for row in rows if isinstance(row, list) and len(row) > 1}
            for i, row in enumerate(rows):
                if not isinstance(row, list) or len(row) < 2 or not isinstance(row[0], str) \
                        or row[1] not in self.tables.symbol_new:
                    continue
                renamed = self.resolve(row[0], row[1])
                if renamed == 'ambiguous':
                    r.untouched('soundness', f'{key}[{i}] {row[0]} {row[1]}: several new names')
                elif renamed:
                    if (row[0], renamed) in present:
                        r.collision('soundness', f'{key}[{i}] {row[0]} {row[1]} -> {renamed} exists')
                        continue
                    rows[i] = [row[0], renamed] + row[2:]
                    present.add((row[0], renamed))
                    changed = True
                    r.migrated('soundness', f'{key}[{i}] {row[0]}: {row[1]} -> {renamed}')
        if changed:
            kwargs, tail = R.json_file_format(text, json.loads(text))
            self.set(SOUNDNESS, json.dumps(data, **(kwargs or dict(indent=2))) + (tail if kwargs else '\n'))

    # -- bridge casts

    def bridges(self):
        import bridge_check as B
        import ledger_refresh as R
        text = self.read(BRIDGES)
        if text is None:
            return
        r = self.report
        lines = text.splitlines()
        rows = [json.loads(line) if line.strip() else None for line in lines]
        sites = {row['site_id'] for row in rows if row}
        out = list(lines)
        members = {}                                   # old member -> new, every table row
        for old, news in self.tables.member_new.items():
            members[old] = sorted(news)
        for i, row in enumerate(rows):
            if not row or row.get('status') == 'retired':
                continue
            rel, function = row.get('file'), row.get('function')
            if not isinstance(rel, str) or not self.tree.exists(rel):
                continue
            new = dict(row)
            new_function = function
            if function in self.tables.symbol_new:
                renamed = self.resolve(rel, function)
                if renamed and renamed != 'ambiguous':
                    new_function = renamed
            new['function'] = new_function
            texts = B.function_texts(self.tree.text(rel))
            bodies = texts.get(new_function, [])
            cast = row['cast_text']
            ordinal = row.get('ordinal', 1)
            if sum(b.count(cast) for b in bodies) < ordinal:
                alt = self._respell(cast, rel, bodies, ordinal)
                if alt is not None:
                    new['cast_text'] = alt
                elif new_function == function:
                    continue
            m = re.match(r'^(?P<file>[^:]+)::(?P<function>[A-Za-z_]\w*)(?P<rest>@.*)$', row.get('site_id') or '')
            if m and m['file'] == rel and m['function'] == function and new_function != function:
                new['site_id'] = f'{rel}::{new_function}{m["rest"]}'
            if new == row:
                continue
            if new['site_id'] != row['site_id'] and new['site_id'] in sites:
                r.collision('bridges', f'{BRIDGES}:{i + 1} {row["site_id"]} -> {new["site_id"]} exists')
                continue
            kwargs = R.json_line_format(lines[i], row)
            if kwargs is None:
                r.untouched('bridges', f'{BRIDGES}:{i + 1}: row format not reproducible, not rewritten')
                continue
            sites.discard(row['site_id'])
            sites.add(new['site_id'])
            out[i] = json.dumps(new, **kwargs)
            r.migrated('bridges', f'{BRIDGES}:{i + 1} {function} cast `{row["cast_text"][:60]}`')
        self.set(BRIDGES, '\n'.join(out) + ('\n' if text.endswith('\n') else ''))

    def _respell(self, cast, rel, bodies, ordinal):
        """The cast text under the new member and symbol names, when the function now holds it literally."""
        if not bodies:
            return None
        pieces = []
        last = 0
        for m in IDENT.finditer(cast):
            pieces.append(cast[last:m.start()])
            word = m.group(0)
            before = cast[max(0, m.start() - 2):m.start()]
            if before.endswith('->') or before.endswith('.'):
                options = sorted(self.tables.member_new.get(word, ()))
            else:
                options = [self.resolve(rel, word)] if word in self.tables.symbol_new else []
            options = [o for o in options if o and o != 'ambiguous']
            pieces.append(options if options else word)
            last = m.end()
        pieces.append(cast[last:])
        slots = [i for i, p in enumerate(pieces) if isinstance(p, list)]
        if not slots:
            return None
        for combo in _product([pieces[i] for i in slots]):
            trial = list(pieces)
            for i, word in zip(slots, combo):
                trial[i] = word
            text = ''.join(trial)
            if sum(b.count(text) for b in bodies) >= ordinal:
                return text
        return None

    # -- fields

    def fields(self):
        import ledger_refresh as R
        text = self.read(FIELDS)
        if text is None:
            return
        r = self.report
        lines = text.splitlines()
        rows = [json.loads(line) if line.strip() else None for line in lines]
        taken = collections.defaultdict(set)
        for row in rows:
            if row and 'name' in row and 'off' in row and isinstance(row.get('type'), str):
                taken[(row['type'], row['name'])].add(row['off'])
        by_record = collections.defaultdict(list)
        for m in self.tables.members:
            by_record[(m.record, m.old)].append(m)
        out = list(lines)
        for i, row in enumerate(rows):
            if not row:
                continue
            new = dict(row)
            if 'name' in row and 'off' in row and isinstance(row.get('type'), str) and isinstance(row.get('name'), str):
                hits = [m for m in by_record.get((row['type'], row['name']), [])
                        if m.offset is None or m.offset == _hex(row['off'])]
                if len(hits) == 1:
                    m = hits[0]
                    if taken.get((row['type'], m.new)):
                        r.collision('fields', f'{FIELDS}:{i + 1} {row["type"]}.{row["name"]} -> {m.new}: a row of '
                                    'that type already carries the new name')
                        continue
                    new['name'] = m.new
                    if row.get('name') != m.new:
                        new['previous_name'] = row['name']
                elif len(hits) > 1:
                    r.untouched('fields', f'{FIELDS}:{i + 1} {row["type"]}.{row["name"]}: several table rows')
            site = row.get('site')
            if isinstance(site, str) and site.count(':') >= 2:
                file, function, rest = site.split(':', 2)
                if function in self.tables.symbol_new:
                    renamed = self.resolve(file, function)
                    if renamed and renamed != 'ambiguous':
                        new['site'] = f'{file}:{renamed}:{rest}'
            if new == row:
                continue
            kwargs = R.json_line_format(lines[i], row)
            if kwargs is None:
                r.untouched('fields', f'{FIELDS}:{i + 1}: row format not reproducible, not rewritten')
                continue
            out[i] = json.dumps(new, **kwargs)
            r.migrated('fields', f'{FIELDS}:{i + 1} {row.get("type")}.{row.get("name", row.get("site"))}')
        self.set(FIELDS, '\n'.join(out) + ('\n' if text.endswith('\n') else ''))

    # -- driver

    def run(self):
        steps = (('debt', self.debt), ('union_ids', self.union_ids), ('floors', self.floors), ('proto', self.proto),
                 ('accepted', self.accepted), ('soundness', self.soundness), ('bridges', self.bridges),
                 ('fields', self.fields))
        for name, step in steps:
            if self.wanted(name):
                step()
        return self.report


def _product(choices):
    out = [[]]
    for options in choices:
        out = [prefix + [o] for prefix in out for o in options]
    return out


def _hex(text):
    try:
        return int(text, 0)
    except (TypeError, ValueError):
        return None


# ---------------------------------------------------------------- tables from two revisions

TOKEN = re.compile(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'|[A-Za-z_]\w*|\d\w*|->|\S', re.S)


def code_tokens(text):
    out = []
    for m in TOKEN.finditer(text):
        t = m.group(0)
        if t[0] in '/"\'' and (t.startswith(('/*', '//')) or t[0] in '"\''):
            continue
        out.append(t)
    return out


def derive_between(root, old, new):
    """(Tables, report lines): identifier differences at equal token positions of every changed src/include file."""
    root = Path(root)
    run = subprocess.run(['git', 'diff', '--name-only', old, new, '--', 'src', 'include'], cwd=root,
                         capture_output=True, text=True, check=True)
    members, symbols = collections.Counter(), collections.Counter()
    skipped = []
    for rel in run.stdout.split():
        if not rel.endswith(('.c', '.h')):
            continue
        a = subprocess.run(['git', 'show', f'{old}:{rel}'], cwd=root, capture_output=True, text=True, errors='replace')
        b = subprocess.run(['git', 'show', f'{new}:{rel}'], cwd=root, capture_output=True, text=True, errors='replace')
        if a.returncode or b.returncode:
            continue
        ta, tb = code_tokens(a.stdout), code_tokens(b.stdout)
        if len(ta) != len(tb):
            skipped.append(rel)
            continue
        for i, (x, y) in enumerate(zip(ta, tb)):
            if x != y and IDENT_ONLY.match(x) and IDENT_ONLY.match(y):
                kind = members if i and ta[i - 1] in ('.', '->') and tb[i - 1] in ('.', '->') else symbols
                if kind is symbols and i and ta[i - 1] in ('struct', 'union', 'enum', 'typedef'):
                    continue
                kind[(x, y)] += 1
    tables = Tables([Member('', '', x, y) for (x, y) in sorted(members)],
                    [(x, y, ()) for (x, y) in sorted(symbols)])
    lines = [f'between {old}..{new}: {len(members)} member pairs, {len(symbols)} symbol pairs, '
             f'{len(skipped)} files with different token streams skipped']
    return tables, lines


# ---------------------------------------------------------------- command line

def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--root', type=Path, default=HERE.parents[1])
    parser.add_argument('--members', action='append', default=[], metavar='TABLE')
    parser.add_argument('--symbols', action='append', default=[], metavar='TABLE')
    parser.add_argument('--between', nargs=2, metavar=('OLD', 'NEW'))
    parser.add_argument('--base', help='revision before the renames (exact debt key renumbering)')
    parser.add_argument('--only', help='comma-separated ledgers: ' + ','.join(LEDGERS))
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument('--check', action='store_true')
    mode.add_argument('--write', action='store_true')
    parser.add_argument('--list', action='store_true', help='also list every migrated key')
    parser.add_argument('--no-retired', action='store_true', help='leave the ids of retired union rows alone (by default a '
                        'retired row follows its member rename when its cited cast lines now spell the new name and '
                        'none the old one: ledger_integrity\'s field rule needs that when another record of the '
                        'header still declares the old name)')
    parser.add_argument('--skip-collisions', action='store_true', help='migrate the rest when a collision is found')
    args = parser.parse_args(argv)
    members, symbols, notes = [], [], []
    for path in args.members:
        members += read_members(path)
    for path in args.symbols:
        symbols += read_symbols(path)
    if args.between:
        derived, notes = derive_between(args.root, *args.between)
        members += derived.members
        symbols += derived.symbols
        args.base = args.base or args.between[0]
    tables = Tables(members, symbols)
    if not tables.any():
        parser.error('no rename rows: give --members, --symbols or --between')
    only = args.only.split(',') if args.only else None
    if only and set(only) - set(LEDGERS):
        parser.error('unknown ledger in --only')
    rekey = Rekey(args.root, tables, args.base, only, not args.no_retired)
    report = rekey.run()
    for line in notes + [f'{len(tables.members)} member rows, {len(tables.symbols)} symbol rows'] + \
            report.lines(args.list, only):
        print(line)
    if report.collisions and not args.skip_collisions:
        print(f'REFUSED: {len(report.collisions)} collision(s); nothing written', file=sys.stderr)
        return 2
    files = rekey.changed()
    if args.write:
        rekey.write()
        print('ledger rekey WROTE', ', '.join(files) if files else '(nothing to change)')
        return 0
    print('ledger rekey would change ' + (', '.join(files) if files else 'nothing'))
    return 1 if files else 0


if __name__ == '__main__':
    sys.exit(main())
