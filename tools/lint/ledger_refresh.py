#!/usr/bin/env python3
"""Re-derive every stored path, line, caller, function name and spelling in the public ledgers.

    ledger_refresh.py [--root R] [--base BASE] (--check | --write) [--list] [--only NAME,...] [--no-history]

Renames (config/names.tsv function rows, `git mv` of the files named after them) leave rows behind in
every ledger and evidence file that cites a function or a file: prototype-floor callers and blocking
spellings, union ledger citations, names.tsv evidence, bridge-cast site ids, accepted warning rows,
baseline keys, layout_inline extents and tool tables.  This one step re-derives them from the tree.

What is re-derived (each value is rewritten only when exactly one current value follows from it):

  function names  a name is *stale* when config/names.tsv once named a function so (any revision of the
                  table: `git log -p`) and neither HEAD's table nor a definition under src/ uses it now.
                  It resolves through the recorded renames: a HEAD row's `(renamed from X)` text and, per
                  revision, an address whose row lost the name and gained another; chains are followed
                  to names that are live.  Several live candidates (an old name that now means two
                  functions, one per image) are narrowed to the ones defined in a file the same record
                  cites; otherwise the name is reported, never guessed.  config/names.tsv has no image column,
                  so an address shared by several images (rows with one address) is never followed alone: a
                  rename reaches a name through a `(renamed from X)` clause of the row that renamed it, or
                  through an address where one old name became several; where several old names became
                  several at one address, the citation is left as written and reported (image unknown).
  (file, function) pairs  a record that pairs a file with a function (`path`/`file` with `caller`/
                  `function`, a site id `file::function@hash`, a warning row) whose function is live but
                  not defined in that file takes the one name config/names.tsv records at the same address
                  that the file defines (a per-image rename that kept the old name for the other image).
  paths           a src/ or include/ path that does not exist, in this order: a stable row id spelled as a
                  path (`src/<container>/<name>.c`, the physical row files before the layout moves) goes
                  to its row's file (tools/source_layout.py); a module file ledger/layout_inline.jsonl
                  records as merged (tu_old) to its one TU; otherwise git's rename history (all of it,
                  rename detection over src/ and include/); a file that was deleted, or renamed and later
                  deleted, follows its functions (address names through config/names.tsv) or the members
                  it #included: the one file they are defined in now, else the file defining the record's
                  own function.  A line number after a moved path (`path:12`, `path:55-87`) is carried
                  through a line diff from the file's last text to its current text when the line is
                  unchanged, or onto the function's current definition when it cited a definition (its
                  first line, or its span give or take the header/brace line); otherwise the line is
                  dropped and the path kept (reported as `line dropped`).
  in-place lines  with --base, a config/names.tsv line citation (`path:12`, `path:55-87`) of a file that still
                  exists but whose text changed since BASE, and that the row has cited unchanged since BASE (the
                  row's BASE evidence holds the same citation at the same position, or there cites a path that
                  was already gone at BASE and this citation is what a refresh at BASE derives from it onto the
                  BASE text), is carried through the file's BASE-to-current line diff the same way (an
                  unchanged line, else a definition's first line or span), else its line is dropped and the
                  path kept.  Any other citation the row changed since BASE was written against the current
                  text and is left alone, so a --write is a fixpoint.
  call lines      prototype-floor arity_evidence entries {path, caller, line}: a line that no longer calls
                  the row's function is re-derived from the caller's calls of it in order, when the caller
                  holds exactly as many calls as the ledger lists for it.
  cast sites      with --base, a ledger/unions.jsonl retired_to_cast entry `path:N CAST ...` that the row has
                  held unchanged since BASE, in a file edited since BASE, follows its cast within the function
                  that held line N at BASE: the casts with the same text in that function are paired in order
                  between BASE and now when their numbers agree, else the entry takes the free one nearest the
                  line diff's projection; it becomes `path CAST ... (cast gone)` only when no cast with that
                  text is left in the function.  Other entries whose line no longer holds the cast:
                  tools/lint/ledger_integrity.py's re-derivation (history anchor, git hunk offsets, the
                  field rule without record layouts).
  layout_inline   tools/typing/refresh_layout_inline.py against --base (default HEAD); `tu_new` must exist.

Frozen (never rewritten): `(renamed from X)` text, also `(renamed from X, earlier Y)`, and `previously X`
text (it records the old name on purpose),
func_<addr> symbols, the union's own id/owner/path/members and census numbers, layout_inline `tu_old`/
`member`/`member_id`, bridge-cast `legacy_line`, the accepted-warning stamp line, and every ledger not
listed in LEDGERS.  A bare file name in a tool table (a file-wide rule) is reported, never rewritten:
a file merged into a larger TU would widen the rule.

Coupled keys move together: a union id (`header::Owner.field`) renamed with its header is renamed in
ledger/unions.jsonl, tools/lint/union_baseline.json and debt_baseline.json bad_label_sites at once.
debt_baseline.json by_file rows of files that no longer exist move to the git-renamed file when it has no
row, otherwise they are dropped and by_class is lowered by their counts (debt_check requires by_class to equal
the sum of by_file; a dropped row is an allowance no file can use).

--check prints the changes it would make and exits 1 if there is any; --write applies them (only the
changed rows of a file are re-serialized, in the file's own format).  Values that cannot be re-derived
are listed as UNRESOLVED and do not fail --check (--fail-unresolved makes them fail).  --base BASE (the
revision the batch started from) sets the revision refresh_layout_inline maps from and the tree in-place
names.tsv line citations are carried from (without --base, in-place lines are not carried); history is
always the whole repository's (--no-history: HEAD's table and tree only, for a root without history).
"""
from __future__ import annotations

import argparse
import collections
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import time

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import lint_closure as C  # noqa: E402
import ledger_integrity as I  # noqa: E402

NAMES = 'config/names.tsv'
ACCEPTED = C.ACCEPTED
DEBT = 'tools/lint/debt_baseline.json'
UNION_BASELINE = 'tools/lint/union_baseline.json'
PROTO_BASELINE = 'tools/lint/proto_baseline.json'
SOUNDNESS = 'tools/lint/soundness_gcc_baseline.json'
UNIONS = 'ledger/unions.jsonl'
FLOORS = 'ledger/prototype_floors.jsonl'
IDENTITIES = 'ledger/prototype_identities.jsonl'
BRIDGES = 'ledger/bridge_casts.jsonl'
LAYOUT_INLINE = 'ledger/layout_inline.jsonl'
# Tool tables that hold literal src/include paths (or basenames) of files they treat specially.
TOOL_TABLES = ('tools/typing/union_census.py',)
LEDGERS = ('names', 'floors', 'identities', 'bridges', 'unions', 'accepted', 'debt', 'proto', 'soundness',
           'layout_inline', 'tools')

PATH = re.compile(r'(?<![\w/.-])((?:src|include)/[\w/.+-]*?[\w+-]+\.(?:c|h|inc))(?![\w/])'
                  r'(?::(\d+)(?:-(\d+))?)?')
IDENT = re.compile(r'(?<![\w/.])[A-Za-z_]\w*\b(?!\.(?:c|h|inc)\b)')
# Text that records an old name on purpose: config/names.tsv `(renamed from X)` and `previously X`.
# The whole parenthesis is frozen, including the several-name form `(renamed from a, earlier b)`.
FROZEN = re.compile(r'\(renamed from [^)]*\)|\bpreviously [A-Za-z_]\w*')
SITE_ID = re.compile(r'^(?P<file>[^:]+)::(?P<function>[A-Za-z_]\w*)(?P<rest>@.*)$')
FUNCTION_KEYS = ('caller', 'function')
# unions.jsonl fields that name the union itself or hold census numbers, not citations.
UNION_FROZEN = {'id', 'owner', 'path', 'members', 'loads', 'uses', 'kind', 'status', 'count_basis', 'line'}


def git(root, *args, check=False):
    result = subprocess.run(['git', *args], cwd=root, capture_output=True, text=True, errors='replace')
    if check and result.returncode:
        raise SystemExit(f'git {" ".join(args)}: {result.stderr.strip()}')
    return result.stdout if result.returncode == 0 else None


class Blobs:
    """`git cat-file --batch`: file texts at revisions through one process."""

    def __init__(self, root):
        self.root, self.proc = root, None

    def show(self, spec):
        if self.proc is None:
            self.proc = subprocess.Popen(['git', 'cat-file', '--batch'], cwd=self.root, stdin=subprocess.PIPE,
                                         stdout=subprocess.PIPE)
        self.proc.stdin.write(spec.encode() + b'\n')
        self.proc.stdin.flush()
        header = self.proc.stdout.readline().split()
        if len(header) != 3 or header[1] != b'blob':
            return None
        data = self.proc.stdout.read(int(header[2]))
        self.proc.stdout.read(1)
        return data.decode(errors='replace')

    def __del__(self):
        try:
            self.close()
        except (OSError, ValueError):
            pass

    def close(self):
        if self.proc is not None:
            self.proc.stdin.close()
            self.proc.wait()
            self.proc.stdout.close()
            self.proc = None


def opcodes(old, new):
    """difflib opcodes of two line lists (in process: one ledger refresh maps thousands of files)."""
    import difflib
    return difflib.SequenceMatcher(None, old, new, autojunk=False).get_opcodes()


# ---------------------------------------------------------------- the tree

class Tree:
    """src/ and include/ files of the checkout, the functions each .c/.inc file defines, names.tsv rows."""

    def __init__(self, root):
        self.root = Path(root)
        self.files = set()
        for top in ('src', 'include'):
            for directory, _, names in os.walk(self.root / top):
                rel = os.path.relpath(directory, self.root)
                self.files.update(f'{rel}/{n}' for n in names)
        self.defined = collections.defaultdict(set)        # name -> {file}
        self.defines = {}                                    # file -> {name}
        for rel in self.files:
            if rel.endswith(('.c', '.inc')):
                names = C.defined_functions(self.text(rel))
                self.defines[rel] = names
                for name in names:
                    self.defined[name].add(rel)
        self.rows = read_names(self.text(NAMES) or '')
        self.by_addr = collections.defaultdict(set)
        self.addrs = collections.defaultdict(set)
        for addr, _, name, _ in self.rows:
            self.by_addr[addr].add(name)
            self.addrs[name].add(addr)
        self._texts = {}

    def text(self, rel):
        path = self.root / rel
        try:
            return path.read_text(errors='replace')
        except (FileNotFoundError, IsADirectoryError):
            return None

    def cached(self, rel):
        if rel not in self._texts:
            self._texts[rel] = self.text(rel)
        return self._texts[rel]

    def exists(self, rel):
        return rel in self.files or (self.root / rel).is_file()

    def live(self, name):
        return name in self.addrs or name in self.defined

    def mentions(self, rel, name):
        """The file defines name or spells it (a prototype, a call, a callback table entry)."""
        if name in self.defines.get(rel, ()):
            return True
        text = self.cached(rel)
        return text is not None and re.search(r'\b' + re.escape(name) + r'\b', text) is not None


def read_names(text):
    """[(addr, symbol, name, evidence)] of the function rows of a names.tsv text."""
    rows = []
    for line in text.splitlines():
        cols = line.split('\t')
        if len(cols) >= 3 and cols[0].startswith('0x') and cols[1].startswith('func_'):
            rows.append((cols[0].lower(), cols[1], cols[2], cols[3] if len(cols) > 3 else ''))
    return rows


# ---------------------------------------------------------------- function-name history

class Names:
    """Every name config/names.tsv ever gave a function and the renames recorded between them."""

    RENAMED = re.compile(r'\(renamed from ([A-Za-z_]\w*)(?:, earlier ([A-Za-z_]\w*))?\)')

    def __init__(self, root, tree, history=True):
        self.tree = tree
        self.ever = collections.defaultdict(set)            # name -> {addr}
        self.pairs = collections.defaultdict(set)           # old name -> {new name}
        self.at = collections.defaultdict(set)              # addr -> {every name the table gave it}
        self.shared = collections.defaultdict(set)          # old name -> {addr whose rename the table cannot attribute}
        for addr, _, name, evidence in tree.rows:
            self.ever[name].add(addr)
            self.at[addr].add(name)
            for clause in self.RENAMED.findall(evidence):      # `(renamed from a, earlier b)`: both old names
                for old in filter(None, clause):
                    if old != name:
                        self.pairs[old].add(name)
                        self.ever[old].add(addr)
        self.history = False
        log = git(root, 'log', '-p', '-U0', '--no-color', '--reverse', '--format=C %H', '--', NAMES) \
            if history else None
        if log:
            self.history = True
            self._read_log(log)

    def _read_log(self, log):
        removed, added = collections.defaultdict(set), collections.defaultdict(set)

        def flush():
            for addr, gone in removed.items():
                new = added.get(addr, set()) - gone
                lost = gone - added.get(addr, set())
                if len(lost) > 1 and len(new) > 1:
                    # several names left and several arrived at one address in one revision: the images that
                    # place different functions there cannot be told apart by address, so no old -> new pairing
                    for old in lost:
                        self.shared[old].add(addr)
                else:
                    for old in lost:
                        self.pairs[old] |= new
            removed.clear()
            added.clear()
        for line in log.splitlines():
            if line.startswith('C '):
                flush()
                continue
            if line[:3] in ('-0x', '+0x'):
                cols = line[1:].split('\t')
                if len(cols) >= 3 and cols[1].startswith('func_'):
                    addr = cols[0].lower()
                    self.ever[cols[2]].add(addr)
                    self.at[addr].add(cols[2])
                    (removed if line[0] == '-' else added)[addr].add(cols[2])
        flush()

    def stale(self, name):
        return name in self.ever and not self.tree.live(name)

    def stale_in_prose(self, name):
        """A stale name that prose cannot mean as a plain word: snake_case or camelCase, 6+ characters."""
        return len(name) >= 6 and ('_' in name.strip('_') or re.search(r'[a-z][A-Z]', name) is not None) \
            and self.stale(name)

    def candidates(self, name):
        """Live names the recorded renames lead to from a stale name (the address's names as a fallback)."""
        seen, frontier, found = {name}, [name], set()
        while frontier:
            for new in self.pairs.get(frontier.pop(), ()):
                if new in seen:
                    continue
                seen.add(new)
                (found.add if self.tree.live(new) else frontier.append)(new)
        if not found:
            for addr in self.ever.get(name, ()):
                live = {n for n in self.tree.by_addr.get(addr, ()) if self.tree.live(n)}
                others = {n for n in self.at.get(addr, ()) if n != name and self.stale(n)}
                if len(live) > 1 and others:
                    # config/names.tsv has no image column: several rows at one address are different
                    # functions of different images, and with several old names there as well the address
                    # does not say whose name was cited (one old name for several images does: files narrow)
                    self.shared[name].add(addr)
                else:
                    found |= live
        return found

    def resolve(self, name, files=()):
        """(new name, None) or (None, reason) for a stale name; files narrow several candidates."""
        found = self.candidates(name)
        if len(found) == 1:
            return next(iter(found)), None
        if not found:
            if self.shared.get(name):
                return None, ('the address(es) %s hold several functions (one row per image) and no recorded '
                              'rename names this one: image unknown, left as cited'
                              % ', '.join(sorted(self.shared[name])))
            return None, 'no live name follows from it'
        narrowed = {n for n in found if any(f in self.tree.defined.get(n, ()) for f in files)}
        if len(narrowed) == 1:
            return next(iter(narrowed)), None
        return None, 'several live names follow from it: ' + ', '.join(sorted(found))

    def sibling_in(self, name, rel):
        """The one name recorded at one of name's addresses that rel defines (per-image rename), else None."""
        found = {n for addr in self.tree.addrs.get(name, ()) for n in self.tree.by_addr.get(addr, ())
                 if n != name and n in self.tree.defines.get(rel, ())}
        return next(iter(found)) if len(found) == 1 else None


# ---------------------------------------------------------------- path history

class Paths:
    """Where a src/include path that no longer exists went: git renames, else where its functions are."""

    def __init__(self, root, tree, names, history=True):
        self.root, self.tree, self.names, self.enabled = Path(root), tree, names, history
        self._log = None
        self._resolved, self._texts, self._opcodes, self._rev_texts = {}, {}, {}, {}
        self.blobs = Blobs(root)
        self._registry = self._layout = self._merged = None

    def _load(self):
        if self._log is not None:
            return self._log
        renamed, gone = {}, {}
        out = git(self.root, 'log', '-M', '-l20000', '--name-status', '--diff-filter=RD', '--format=C %H',
                  '--', 'src', 'include') if self.enabled else None
        commit = None
        for line in (out or '').splitlines():
            if line.startswith('C '):
                commit = line[2:].strip()
                continue
            cols = line.split('\t')
            if cols[0].startswith('R') and len(cols) == 3:
                renamed.setdefault(cols[1], (cols[2], commit))       # newest first: keep the latest
            elif cols[0] == 'D' and len(cols) == 2:
                gone.setdefault(cols[1], commit)
        self._log = renamed, gone
        return self._log

    def last_text(self, path):
        """The path's text just before git renamed or deleted it (None without history)."""
        if path not in self._texts:
            renamed, gone = self._load()
            commit = renamed[path][1] if path in renamed else gone.get(path)
            self._texts[path] = self.blobs.show(f'{commit}^:{path}') if commit else None
        return self._texts[path]

    def rev_text(self, rev, path):
        """The path's text at a revision (None when it is not there)."""
        if (rev, path) not in self._rev_texts:
            self._rev_texts[(rev, path)] = self.blobs.show(f'{rev}:{path}')
        return self._rev_texts[(rev, path)]

    def resolve(self, path, function=None):
        """(new path, how, old path whose text maps lines) or (None, reason, None)."""
        key = (path, function)
        if key in self._resolved:
            return self._resolved[key]
        result = self._resolve(path, function)
        self._resolved[key] = result
        return result

    def _resolve(self, path, function):
        if not self.enabled:
            return None, 'no history', None
        row = self.row_home(path)
        if row:
            return row, 'row id', path
        merged = self.merged_into(path)
        if merged:
            return merged, 'merged TU (layout_inline)', path
        renamed, gone = self._load()
        hops, current, last = 0, path, path
        while not self.tree.exists(current) and current in renamed and hops < 64:
            last, current, hops = current, renamed[current][0], hops + 1
        if self.tree.exists(current):
            return current, 'git rename', path
        if not current.endswith(('.c', '.inc')):
            return None, 'deleted header' if current in gone else 'not in history', None
        text = self.last_text(current) if (current in gone or current in renamed) else None
        if text is None:
            return None, 'not in history', None
        files = set()
        for name in C.defined_functions(text):
            files |= self.function_files(name, current)
        for member in AGGREGATED.findall(text):             # an aggregator TU: where its members are now
            member = os.path.normpath(os.path.join(os.path.dirname(current), member))
            found = member if self.tree.exists(member) else self.resolve(member)[0]
            if found:
                files.add(found)
        if len(files) == 1:
            return next(iter(files)), 'its functions moved', current
        if not files:
            moved = self.data_moved(current, text)
            if moved:
                return moved, 'its data moved', current
        if function:
            now = function if self.tree.live(function) else self.names.resolve(function)[0]
            mine = files & self.tree.defined.get(now, set()) if now else set()
            if len(mine) == 1:
                return next(iter(mine)), 'its function moved', current
        return None, f'deleted; its functions are in {len(files)} files', None

    def data_moved(self, path, text):
        """A deleted file without functions (tables, data definitions): the one file the deleting commit touched
        that now defines all of its file-scope data names."""
        names = set(DATA_DEFINITION.findall(C.strip_comments(text)))
        renamed, gone = self._load()
        commit = renamed[path][1] if path in renamed else gone.get(path)
        if not names or not commit:
            return None
        touched = git(self.root, 'show', '--format=', '--name-only', commit) or ''
        found = []
        for rel in touched.split():
            if rel != path and rel.endswith(('.c', '.inc', '.h')) and self.tree.exists(rel):
                here = set(DATA_DEFINITION.findall(C.strip_comments(self.tree.cached(rel) or '')))
                if names <= here:
                    found.append(rel)
        return found[0] if len(found) == 1 else None

    def merged_into(self, path):
        """The one TU ledger/layout_inline.jsonl records a module file (tu_old) merged into."""
        if self._merged is None:
            self._merged = collections.defaultdict(set)
            text = self.tree.text(LAYOUT_INLINE) or ''
            for line in text.splitlines():
                if line.strip():
                    rec = json.loads(line)
                    if isinstance(rec.get('tu_old'), str) and isinstance(rec.get('tu_new'), str):
                        self._merged[rec['tu_old']].add(rec['tu_new'])
        found = self._merged.get(path, set())
        return next(iter(found)) if len(found) == 1 and self.tree.exists(next(iter(found))) else None

    def row_home(self, path):
        """The current file of a path that spells a stable row id (`src/<container>/<name>.c`: the physical
        file names before the layout moves), through tools/gate/source_layout.py."""
        m = re.fullmatch(r'src/([a-z0-9_]+)/([\w.+-]+)\.c', path)
        if not m:
            return None
        if self._registry is None:
            try:
                sys.path.insert(0, str(HERE.parent))
                from gate import source_layout as S
                self._layout = S
                self._registry = S.registry(self.root)
            except Exception:                       # noqa: BLE001 - a root without the row ledger
                self._registry = {}
        rid = f'{m[1]}/{m[2]}'
        if rid not in self._registry:
            return None
        try:
            new = self._layout.row_relative(rid, self.root)
        except (ValueError, KeyError):
            return None
        new = str(new)
        return new if new != path and self.tree.exists(new) else None

    def function_files(self, name, old_path):
        """Files that define a function an old file defined: its current name, or for an address name
        (func_<addr>) the names config/names.tsv gives the address (one image's when the old file's
        subsystem directory tells them apart)."""
        if re.fullmatch(r'func_[0-9A-Fa-f]{8}', name):
            names = {n for n in self.tree.by_addr.get('0x' + name[5:].lower(), ()) if self.tree.live(n)}
            found = {n: self.tree.defined.get(n, set()) for n in names}
            if len(found) > 1:
                top = '/'.join(old_path.split('/')[:2]) + '/'
                same = {n: f for n, f in found.items() if any(x.startswith(top) for x in f)}
                found = same if len(same) == 1 else found
            return set().union(*found.values()) if found else set()
        now = name if self.tree.live(name) else self.names.resolve(name)[0]
        return set(self.tree.defined.get(now, set())) if now else set()

    def map_definition(self, old_path, new_path, first, second=None, rev=None, new_rev=None):
        """[first(, second)] of a citation that named a function's definition in old_path's last text (its text
        at rev when given: a file that still exists) (its first line, or its whole span give or take the
        header/brace line) moved onto that function's definition in new_path (its text at new_rev when
        given), else None."""
        old = self.rev_text(rev, old_path) if rev else self.last_text(old_path)
        new = self.rev_text(new_rev, new_path) if new_rev else self.tree.cached(new_path)
        if old is None or new is None:
            return None
        for name in C.defined_functions(old):
            span = function_lines(old, name)
            if span is None:
                continue
            if second is None:
                if first != span[0]:
                    continue
            elif not (span[0] <= first <= span[0] + 1 and span[1] - 1 <= second <= span[1]):
                continue
            here = [n for n in self.tree.defines.get(new_path, ())
                    if new_path in self.function_files(name, old_path) and (
                        n == name or n in self.tree.by_addr.get('0x' + name[5:].lower(), ())
                        or n in self.names.candidates(name))]
            current = function_lines(new, here[0]) if len(here) == 1 else None
            if current is None:
                return None
            if second is None:
                return [current[0]]
            return [current[0] + (first - span[0]), current[1] - (span[1] - second)]
        return None

    def map_line(self, old_path, new_path, line, rev=None, new_rev=None):
        """The current line (the line at new_rev when given) of an unchanged line of old_path's last text (its
        text at rev when given), else None."""
        if rev:
            old = self.rev_text(rev, old_path)
        else:
            old = self.last_text(old_path) if old_path != new_path else None
        new = self.rev_text(new_rev, new_path) if new_rev else self.tree.cached(new_path)
        if old is None or new is None:
            return None
        key = (rev, old_path, new_rev, new_path)
        if key not in self._opcodes:
            self._opcodes[key] = opcodes(old.splitlines(), new.splitlines())
        for tag, i1, i2, j1, _ in self._opcodes[key]:
            if i1 <= line - 1 < i2:
                return j1 + (line - 1 - i1) + 1 if tag == 'equal' else None
        return None


# ---------------------------------------------------------------- the refresher

class Refresher:
    def __init__(self, root, history=True, base=None):
        self.root = Path(root)
        self.base = base                        # revision whose tree in-place line citations were written against
        self._base_rows = None
        self.tree = Tree(root)
        self.names = Names(root, self.tree, history)
        self.paths = Paths(root, self.tree, self.names, history)
        self.declarations = None
        self.changes = []                       # (ledger, where, old, new, how)
        self.unresolved = []                    # (ledger, where, value, reason)
        self._seen_unresolved = set()

    INCLUDE = re.compile(r'(?m)^[ \t]*#[ \t]*include[ \t]*"([^"]+)"')

    def includes(self, rel):
        """The file and every file it #includes, transitively (quoted includes: beside the file, then include/)."""
        if not hasattr(self, '_includes'):
            self._includes = {}
        if rel in self._includes:
            return self._includes[rel]
        seen, todo = {rel}, [rel]
        while todo:
            current = todo.pop()
            for target in self.INCLUDE.findall(self.tree.cached(current) or ''):
                for candidate in (os.path.normpath(os.path.join(os.path.dirname(current), target)),
                                  'include/' + target):
                    if self.tree.exists(candidate):
                        if candidate not in seen:
                            seen.add(candidate)
                            todo.append(candidate)
                        break
        self._includes[rel] = seen
        return seen

    def note(self, ledger, where, old, new, how):
        self.changes.append((ledger, where, old, new, how))

    def fail(self, ledger, where, value, reason):
        key = (ledger, where, value)
        if key not in self._seen_unresolved:
            self._seen_unresolved.add(key)
            self.unresolved.append((ledger, where, value, reason))

    # -- values

    def path(self, ledger, where, path, function=None):
        """The current spelling of one path (unchanged when it exists or cannot be re-derived)."""
        if self.tree.exists(path) or not path.startswith(('src/', 'include/')):
            return path
        new, how, _ = self.paths.resolve(path, function)
        if new is None:
            self.fail(ledger, where, path, how)
            return path
        return new

    def name(self, ledger, where, name, files=()):
        if not self.names.stale(name):
            return name
        new, reason = self.names.resolve(name, [self.path(ledger, where, f) for f in files])
        if new is None:
            self.fail(ledger, where, name, reason)
            return name
        return new

    def base_evidence(self, cols):
        """The --base revision's evidence of a config/names.tsv row (address, symbol, name; the one row at the
        address and symbol when the name differs), else None."""
        if not self.base:
            return None
        if self._base_rows is None:
            text = self.paths.blobs.show(f'{self.base}:{NAMES}')
            if text is None:
                self.fail('names', self.base, NAMES, '--base has no config/names.tsv: in-place lines not carried')
            self._base_rows, by_symbol = {}, collections.defaultdict(list)
            for line in (text or '').split('\n'):
                old = line.split('\t')
                if len(old) == 4 and old[0].startswith('0x'):
                    self._base_rows[tuple(old[:3])] = old[3]
                    by_symbol[tuple(old[:2])].append(old[3])
            self._base_by_symbol = by_symbol
        found = self._base_rows.get(tuple(cols[:3]))
        if found is None and len(self._base_by_symbol.get(tuple(cols[:2]), ())) == 1:
            found = self._base_by_symbol[tuple(cols[:2])][0]
        return found

    def text(self, ledger, where, text, files=(), function=None, base_text=None):
        """Prose or a site string: paths (with their line numbers) and stale function names re-derived.

        base_text is the same record's text at --base: a line citation of a file that still exists and that
        the record has cited unchanged since then (same position, same path and lines) follows the file's
        base-to-current line diff."""
        if not isinstance(text, str) or not text:
            return text
        cited = [m.group(1) for m in PATH.finditer(text)] + list(files)
        frozen = [m.span() for m in FROZEN.finditer(text)]
        tokens = [m.group(0) for m in PATH.finditer(text)]
        carried = [False] * len(tokens)
        if base_text is not None and self.base:
            before = [m.group(0) for m in PATH.finditer(base_text)]
            if len(before) == len(tokens):
                carried = [a == b or b == self._refreshed_at_base(m, function)
                           for a, b, m in zip(before, tokens, PATH.finditer(base_text))]
            elif any(self._in_place_shift(m) for m in PATH.finditer(text)):
                self.fail(ledger, where, '(line citations)', f'{len(before)} cited paths at --base, {len(tokens)} '
                          'now: in-place lines not carried')
        out, last = [], 0
        for i, m in enumerate(PATH.finditer(text)):
            out.append(self._names_in(ledger, where, text[last:m.start()], cited, frozen, last))
            out.append(self._path_token(ledger, where, m, function, carried[i]))
            last = m.end()
        out.append(self._names_in(ledger, where, text[last:], cited, frozen, last))
        return ''.join(out)

    def _names_in(self, ledger, where, piece, cited, frozen, offset):
        def sub(m):
            start = offset + m.start()
            if any(a <= start < b for a, b in frozen) or not self.names.stale_in_prose(m.group(0)):
                return m.group(0)
            return self.name(ledger, where, m.group(0), cited)
        return IDENT.sub(sub, piece)

    def _refreshed_at_base(self, m, function):
        """A --base citation of a path that was already gone at --base, re-derived onto the --base tree (what a
        refresh run at the batch start writes), else None: a row holding exactly this was written against the
        --base text."""
        path, first, second = m.group(1), m.group(2), m.group(3)
        if not path.startswith(('src/', 'include/')) or self.paths.rev_text(self.base, path) is not None:
            return None
        new, _, old_path = self.paths.resolve(path, function)
        if new is None or self.paths.rev_text(self.base, new) is None:
            return None
        if first is None:
            return new
        lines = [self.paths.map_line(old_path, new, int(first), new_rev=self.base)]
        if second is not None:
            lines.append(self.paths.map_line(old_path, new, int(second), new_rev=self.base))
        if any(n is None for n in lines):
            lines = self.paths.map_definition(old_path, new, int(first), None if second is None else int(second),
                                              new_rev=self.base)
        if lines is None:
            return new
        return f'{new}:{lines[0]}' + (f'-{lines[1]}' if second is not None else '')

    def _in_place_shift(self, m):
        """A line citation of an existing file whose text changed since --base."""
        path = m.group(1)
        return m.group(2) is not None and self.tree.exists(path) and path.startswith(('src/', 'include/')) \
            and self.paths.rev_text(self.base, path) not in (None, self.tree.cached(path))

    def _path_token(self, ledger, where, m, function, carried=False):
        path, first, second = m.group(1), m.group(2), m.group(3)
        if self.tree.exists(path) and carried and self._in_place_shift(m):
            return self._carry_in_place(ledger, where, m)
        if self.tree.exists(path) or not path.startswith(('src/', 'include/')):
            return m.group(0)
        new, how, old_path = self.paths.resolve(path, function)
        if new is None:
            self.fail(ledger, where, path, how)
            return m.group(0)
        if first is None:
            return new
        lines = [self.paths.map_line(old_path, new, int(first))]
        if second is not None:
            lines.append(self.paths.map_line(old_path, new, int(second)))
        if any(n is None for n in lines):
            lines = self.paths.map_definition(old_path, new, int(first), None if second is None else int(second))
        if lines is None:
            self.note(ledger, where, m.group(0), new, 'line dropped')
            return new
        return f'{new}:{lines[0]}' + (f'-{lines[1]}' if second is not None else '')

    def _carry_in_place(self, ledger, where, m):
        """A citation of a file edited since --base: its lines through the base-to-current line diff (an
        unchanged line, else a definition's first line or span), else the path without the line."""
        path, first, second = m.group(1), int(m.group(2)), m.group(3)
        second = None if second is None else int(second)
        lines = [self.paths.map_line(path, path, first, self.base)]
        if second is not None:
            lines.append(self.paths.map_line(path, path, second, self.base))
        if any(n is None for n in lines):
            lines = self.paths.map_definition(path, path, first, second, self.base)
        if lines is None:
            self.note(ledger, where, m.group(0), path, 'line dropped (edited since --base)')
            return path
        new = f'{path}:{lines[0]}' + (f'-{lines[1]}' if second is not None else '')
        if new != m.group(0):
            self.note(ledger, where, m.group(0), new, 'line carried (edited since --base)')
        return new

    def value(self, ledger, where, value, files=(), function=None):
        """A JSON value with every string (and dict key) refreshed; dicts pairing a file with a function
        also get the per-image check."""
        if isinstance(value, str):
            return self.text(ledger, where, value, files, function)
        if isinstance(value, list):
            return [self.value(ledger, where, v, files, function) for v in value]
        if isinstance(value, dict):
            out = {self.text(ledger, where, k, files, function) if isinstance(k, str) else k:
                   self.value(ledger, where, v, files, function) for k, v in value.items()}
            self.pair(ledger, where, out)
            return out
        return value

    def pair(self, ledger, where, record):
        """{path|file, caller|function}: a live function the file does not define becomes the one name
        recorded at its address that the file defines."""
        file = next((record[k] for k in ('path', 'file') if isinstance(record.get(k), str)), None)
        key = next((k for k in FUNCTION_KEYS if isinstance(record.get(k), str)), None)
        if not file or not key or not file.endswith(('.c', '.inc')) or not self.tree.exists(file):
            return
        function = record[key]
        if self.names.stale(function) or not self.tree.live(function) or self.tree.mentions(file, function):
            return
        sibling = self.names.sibling_in(function, file)
        if sibling:
            record[key] = sibling
        elif function in self.tree.addrs:
            self.fail(ledger, where, f'{file}::{function}', 'the file does not define this function')


# ---------------------------------------------------------------- serialisation

def json_line_format(line, row):
    """A json.dumps keyword set that reproduces this ledger line exactly, else None."""
    for kwargs in (dict(sort_keys=True), dict(sort_keys=True, separators=(',', ':')), {},
                   dict(separators=(',', ':')), dict(sort_keys=True, ensure_ascii=False),
                   dict(ensure_ascii=False), dict(separators=(',', ':'), ensure_ascii=False),
                   dict(sort_keys=True, separators=(',', ':'), ensure_ascii=False)):
        if json.dumps(row, **kwargs) == line:
            return kwargs
    return None


def json_file_format(text, data):
    for kwargs in (dict(indent=2, sort_keys=True), dict(indent=2), dict(indent=1, sort_keys=True),
                   dict(indent=1), dict(sort_keys=True), {}, dict(indent=2, sort_keys=True, ensure_ascii=False)):
        dumped = json.dumps(data, **kwargs)
        if dumped + '\n' == text:
            return kwargs, '\n'
        if dumped == text:
            return kwargs, ''
    return None, None


class Files:
    """Pending file texts; --write saves the changed ones."""

    def __init__(self, root):
        self.root, self.texts, self.original = Path(root), {}, {}

    def read(self, rel):
        if rel not in self.texts:
            path = self.root / rel
            self.original[rel] = self.texts[rel] = path.read_text() if path.is_file() else None
        return self.texts[rel]

    def set(self, rel, text):
        self.read(rel)
        self.texts[rel] = text

    def changed(self):
        return sorted(rel for rel, text in self.texts.items() if text != self.original[rel])

    def write(self):
        for rel in self.changed():
            (self.root / rel).write_text(self.texts[rel])


# ---------------------------------------------------------------- ledgers

def refresh_jsonl(r, files, rel, ledger, row_fn):
    text = files.read(rel)
    if text is None:
        return
    out, dirty = [], False
    for number, line in enumerate(text.splitlines(), 1):
        if not line.strip():
            out.append(line)
            continue
        row = json.loads(line)
        new = row_fn(json.loads(line), f'{rel}:{number}')
        if new == row:
            out.append(line)
            continue
        kwargs = json_line_format(line, row)
        if kwargs is None:
            r.fail(ledger, f'{rel}:{number}', '(row)', 'row format not reproducible; not rewritten')
            out.append(line)
            continue
        out.append(json.dumps(new, **kwargs))
        dirty = True
        r.note(ledger, f'{rel}:{number}', diff_summary(row, new), '', 'row')
    if dirty:
        files.set(rel, '\n'.join(out) + ('\n' if text.endswith('\n') else ''))


def diff_summary(old, new):
    """[(old, new)] for the leaf values (and dict keys) that differ."""
    pairs = []

    def walk(a, b):
        if isinstance(a, dict) and isinstance(b, dict) and len(a) == len(b):
            for (ka, va), (kb, vb) in zip(a.items(), b.items()):
                if ka != kb:
                    pairs.append((ka, kb))
                walk(va, vb)
        elif isinstance(a, list) and isinstance(b, list) and len(a) == len(b):
            for x, y in zip(a, b):
                walk(x, y)
        elif a != b:
            pairs.append((a, b))
    walk(old, new)
    return pairs


def names_ledger(r, files):
    """config/names.tsv evidence: cited paths, line ranges and function names."""
    text = files.read(NAMES)
    if text is None:
        return
    out, dirty = [], False
    for number, line in enumerate(text.split('\n'), 1):
        cols = line.split('\t')
        if len(cols) == 4 and cols[0].startswith('0x'):
            where = f'{NAMES}:{number} {cols[2]}'
            own = sorted(r.tree.defined.get(cols[2], ()))
            evidence = r.text('names', where, cols[3], own, cols[2], r.base_evidence(cols))
            if evidence != cols[3]:
                r.note('names', where, cols[3], evidence, 'evidence')
                cols[3] = evidence
                line = '\t'.join(cols)
                dirty = True
        out.append(line)
    if dirty:
        files.set(NAMES, '\n'.join(out))


def floor_row(r, row, where):
    files = [row['definition']['path']] if isinstance(row.get('definition'), dict) and \
        isinstance(row['definition'].get('path'), str) else []
    if isinstance(row.get('name'), str):
        row['name'] = r.name('floors', where, row['name'], files)
    new = r.value('floors', where, row, files, row.get('name'))
    name = new.get('name')
    definition = new.get('definition')
    if isinstance(definition, dict) and isinstance(definition.get('path'), str) and name and \
            r.tree.exists(definition['path']) and not r.tree.mentions(definition['path'], name):
        found = r.tree.defined.get(name, set())
        if len(found) == 1:
            definition['path'] = next(iter(found))
        else:
            r.fail('floors', where, f"definition {definition['path']}", f'{name} is not there '
                   f'({len(found)} defining files)')
    if name and isinstance(new.get('arity_evidence'), list):
        call_lines(r, where, name, new['arity_evidence'])
    if name and isinstance(new.get('blocking'), list):
        blockers(r, where, new)
    return new


class Declarations:
    """Files that spell a function's declaration with a given signature (decl_agreement normalisation)."""

    def __init__(self, r):
        import decl_agreement as D
        self.r, self.D, self.aliases = r, D, D.scalar_aliases(r.root)
        self.spellers, self.sigs = None, {}

    def files(self, name):
        if self.spellers is None:
            wanted = set()
            for line in (self.r.tree.text(FLOORS) or '').splitlines():
                if line.strip():
                    row = json.loads(line)
                    if isinstance(row.get('name'), str):
                        wanted.add(self.r.names.resolve(row['name'])[0] or row['name']
                                   if self.r.names.stale(row['name']) else row['name'])
            self.spellers = collections.defaultdict(set)
            if wanted:
                pattern = re.compile(r'\b(' + '|'.join(map(re.escape, sorted(wanted))) + r')\s*\(')
                for rel in sorted(self.r.tree.files):
                    if rel.endswith(('.c', '.h', '.inc')):
                        for m in pattern.finditer(self.r.tree.cached(rel) or ''):
                            self.spellers[m.group(1)].add(rel)
        return self.spellers.get(name, set())

    def signatures(self, rel, name, kind):
        key = (rel, name, kind)
        if key not in self.sigs:
            found = self.D.declarations(self.r.tree.cached(rel) or '', {name}, self.aliases)
            self.sigs[key] = {I._sig(d) for d in found if d[2] == kind}
        return self.sigs[key]


def blockers(r, where, row):
    """Blocking entries whose file no longer declares their spelling: the one file that does now (a declaration
    moved to an owner header), else reported (the floor may be obsolete or need re-solving)."""
    name = row['name']
    if r.declarations is None:
        r.declarations = Declarations(r)
    decls = r.declarations
    for i, entry in enumerate(row['blocking']):
        if not isinstance(entry, dict) or not isinstance(entry.get('spelling'), str):
            continue
        old = entry.get('declaration') or entry.get('path')
        want = I.blocking_signature(entry['spelling'], name, decls.aliases)
        kind = 'def' if entry.get('is_def') else 'decl'
        if want is None or not isinstance(old, str) or (r.tree.exists(old) and want in decls.signatures(old, name, kind)):
            continue
        found = sorted(f for f in decls.files(name) if want in decls.signatures(f, name, kind))
        unit = entry.get('path')
        if len(found) > 1 and isinstance(unit, str) and r.tree.exists(unit):
            seen = r.includes(unit)                     # the one the blocked unit sees
            found = [f for f in found if f in seen] if any(f in seen for f in found) else found
        if len(found) != 1:
            r.fail('floors', f'{where} blocking[{i}]', f'{old}: {entry["spelling"]}',
                   'no file declares this spelling now (the floor may be obsolete)' if not found else
                   f'{len(found)} files declare it')
            continue
        # `declaration` is where the spelling is declared; `path` (the unit it blocks in) is kept when both exist
        entry['declaration' if 'declaration' in entry else 'path'] = found[0]


CALL_SPAN_LIMIT = 4000


def function_lines(text, name):
    """(first, last) 1-based lines of name's definition in text, else None."""
    clean = C.strip_comments(text)
    for m in C.DEFINED.finditer(clean):
        if m.group(1) != name:
            continue
        start = clean.index('{', m.start())
        end = I.skip_balanced(clean, start, '{', '}')
        return clean.count('\n', 0, m.start()) + 1, clean.count('\n', 0, end) + 1
    return None


def call_lines(r, where, name, entries):
    """arity_evidence entries whose line no longer calls name: re-derived by order within the caller."""
    groups = collections.defaultdict(list)
    for entry in entries:
        if isinstance(entry, dict) and isinstance(entry.get('path'), str) and isinstance(entry.get('line'), int) \
                and isinstance(entry.get('caller'), str):
            groups[(entry['path'], entry['caller'])].append(entry)
    call = re.compile(r'\b' + re.escape(name) + r'\s*\(')
    for (path, caller), group in groups.items():
        text = r.tree.cached(path)
        if text is None:
            continue
        lines = C.strip_comments(text).split('\n')
        if all(0 < e['line'] <= len(lines) and call.search(lines[e['line'] - 1]) for e in group):
            continue
        span = function_lines(text, caller)
        if span is None:
            r.fail('floors', where, f'{path}:{caller}', f'caller does not define itself there (calls of {name})')
            continue
        found = [n for n in range(span[0], min(span[1], len(lines)) + 1) if call.search(lines[n - 1])]
        if len(found) != len(group):
            r.fail('floors', where, f'{path}:{caller}', f'{len(found)} calls of {name} in the caller, the ledger '
                   f'lists {len(group)}')
            continue
        for entry, line in zip(sorted(group, key=lambda e: e['line']), found):
            entry['line'] = line


def bridge_row(r, row, where):
    file = row.get('file')
    new = r.value('bridges', where, {k: v for k, v in row.items() if k != 'legacy_line'},
                  [file] if isinstance(file, str) else [], row.get('function'))
    if 'legacy_line' in row:
        new['legacy_line'] = row['legacy_line']
    site = SITE_ID.match(row.get('site_id') or '')
    if site and isinstance(new.get('file'), str) and isinstance(new.get('function'), str) \
            and site['file'] == row.get('file') and site['function'] == row.get('function'):
        new['site_id'] = f"{new['file']}::{new['function']}{site['rest']}"
    elif site:
        new['site_id'] = row['site_id']
    return {k: new[k] for k in row}


def identity_row(r, row, where):
    files = [row[k] for k in ('file', 'contract_file') if isinstance(row.get(k), str)]
    return r.value('identities', where, row, files, None)


def union_rows(r, files):
    """ledger/unions.jsonl: ids/files of renamed headers (coupled), cited sites and prose, then cast lines."""
    renamed_ids = {}

    def row_fn(row, where):
        file = row.get('file')
        context = [file] if isinstance(file, str) else []
        new = dict(row)
        for key, value in row.items():
            if key in UNION_FROZEN:
                continue
            if key == 'example_sites' and isinstance(value, dict):
                new[key] = {k: r.value('unions', where, v, context) for k, v in value.items()}
            else:
                new[key] = r.value('unions', where, value, context)
        old_id, new_file = row.get('id'), new.get('file')
        if isinstance(old_id, str) and isinstance(new_file, str) and new_file != file \
                and old_id.startswith(f'{file}::'):
            new['id'] = new_file + old_id[len(file):]
            renamed_ids[old_id] = new['id']
        elif 'id' in row:
            new['id'] = row['id']
        return new
    refresh_jsonl(r, files, UNIONS, 'unions', row_fn)
    carry_casts(r, files)
    rederive_casts(r, files)
    return renamed_ids


def function_spans(text):
    """[(name, first, last)] 1-based line spans of the definitions in a C text."""
    clean = C.strip_comments(text)
    spans = []
    for m in C.DEFINED.finditer(clean):
        start = clean.index('{', m.start())
        end = I.skip_balanced(clean, start, '{', '}')
        spans.append((m.group(1), clean.count('\n', 0, m.start()) + 1, clean.count('\n', 0, end) + 1))
    return spans


def cast_lines(lines, first, last, token):
    """Line numbers in [first, last] whose text holds the squashed cast token."""
    return [n for n in range(first, min(last, len(lines)) + 1) if token in I.squash(lines[n - 1])]


def match_carried(entries, pairs):
    """Decide, per BASE entry, whether the row already holds it where it points now or still as BASE wrote it.

    pairs: [(BASE entry, target, gone)]. Each entry of the row stands for at most one BASE entry, either as its
    target (carried already) or as the BASE text (to carry). The largest such matching is taken, trying the target
    first, so a row whose every BASE entry already sits at its target is left alone (a second --write is a
    fixpoint), while an entry that equals another entry's target is still carried when the row's other entries show
    the group was never carried (a lane's new citation in a shifted file does not stop the carry).
    Returns {pair index: (row index, carried)}."""
    slots = collections.defaultdict(list)
    for index, entry in enumerate(entries):
        if isinstance(entry, str):
            slots[entry].append(index)
    options = [[(i, True) for i in slots.get(target, [])] + [(i, False) for i in slots.get(entry, [])]
               for entry, target, _ in pairs]
    owner, chosen = {}, {}

    def place(pair, seen):
        for index, carried in options[pair]:
            if index in seen:
                continue
            seen.add(index)
            if index not in owner or place(owner[index], seen):
                owner[index], chosen[pair] = pair, (index, carried)
                return True
        return False

    for pair in range(len(pairs)):
        place(pair, set())
    return {pair: chosen[pair] for pair in chosen if owner.get(chosen[pair][0]) == pair}


def carry_casts(r, files):
    """--base: retired_to_cast entries the row holds unchanged since BASE follow their cast inside the function
    that held the cited line at BASE (same cast text, paired in order); `(cast gone)` only when the function no
    longer holds that cast text. Where each BASE entry points now is computed from the BASE row alone, and an entry
    already at its target is not moved again (match_carried)."""
    if not r.base:
        return
    text = files.read(UNIONS)
    base_text = r.paths.rev_text(r.base, UNIONS)
    if text is None or base_text is None:
        return
    base_rows = {}
    for line in base_text.splitlines():
        if line.strip():
            row = json.loads(line)
            base_rows[row.get('id')] = row
    lines = text.splitlines()
    out, dirty = [], False
    for line in lines:
        if not line.strip():
            out.append(line)
            continue
        row = json.loads(line)
        entries = row.get('retired_to_cast')
        base_row = base_rows.get(row.get('id'))
        if not isinstance(entries, list) or not base_row:
            out.append(line)
            continue
        # where each BASE entry should point now: the BASE row's site entries, grouped by the function that held
        # the cited line at BASE and the cast text, paired in order with the lines of that function now holding it
        groups = collections.defaultdict(list)          # (path, function, token) -> [(entry, parsed, occurrences, first)]
        spans_at = {}
        for entry in base_row.get('retired_to_cast') or []:
            if not isinstance(entry, str):
                continue
            parsed = I.parse_entry(entry)
            if parsed['kind'] != 'site' or parsed['second']:
                continue
            path = parsed['path']
            old_text, new_text = r.paths.rev_text(r.base, path), r.tree.cached(path)
            if old_text is None or new_text is None or old_text == new_text:
                continue
            if path not in spans_at:
                spans_at[path] = function_spans(old_text)
            old_lines, token = old_text.splitlines(), I.squash(parsed['cast'])
            home = next(((name, a, b) for name, a, b in spans_at[path] if a <= parsed['line'] <= b), None)
            if home is None:
                continue
            occurrences = cast_lines(old_lines, home[1], home[2], token)
            if parsed['line'] not in occurrences:
                continue                                # already stale at BASE: ledger_integrity's re-derivation
            groups[(path, home[0], token)].append((entry, parsed, occurrences, home[1]))
        pairs = []                                      # (BASE entry, where it points now, gone)
        for (path, function, token), members in groups.items():
            new_text = r.tree.cached(path)
            span = function_lines(new_text, function)
            if span is None and r.names.stale(function):
                renamed, _ = r.names.resolve(function, [path])
                span = function_lines(new_text, renamed) if renamed else None
            if span is None:
                continue                                # the function left the file: path re-derivation's job
            new_lines = new_text.splitlines()
            now = cast_lines(new_lines, span[0], span[1], token)
            room = {n: max(1, I.squash(new_lines[n - 1]).count(token)) for n in now}
            taken = collections.Counter()
            for entry, parsed, occurrences, old_first in members:
                if not now:
                    pairs.append((entry, ' '.join(f"{path} {parsed['rest'].strip()} {I.GONE}".split()), True))
                    continue
                if len(now) == len(occurrences):
                    choice = now[occurrences.index(parsed['line'])]
                else:
                    projected = r.paths.map_line(path, path, parsed['line'], r.base)
                    if projected is None:
                        projected = parsed['line'] - old_first + span[0]
                    pool = [n for n in now if taken[n] < room[n]] or now
                    choice = min(pool, key=lambda n: (abs(n - projected), n))
                taken[choice] += 1
                pairs.append((entry, f'{path}:{choice}' + (f",{parsed['extra']}" if parsed['extra'] else '')
                              + parsed['rest'], False))
        new_entries = list(entries)
        for pair, (index, carried) in sorted(match_carried(entries, pairs).items()):
            entry, target, gone = pairs[pair]
            if carried or entry == target:
                continue
            r.note('unions', row['id'], entry, target,
                   'cast gone from its function' if gone else 'cast line (carried in its function)')
            new_entries[index] = target
        if new_entries == entries:
            out.append(line)
            continue
        kwargs = json_line_format(line, row) or dict(sort_keys=True)
        out.append(json.dumps(dict(row, retired_to_cast=new_entries), **kwargs))
        dirty = True
    if dirty:
        files.set(UNIONS, '\n'.join(out) + ('\n' if text.endswith('\n') else ''))


def rederive_casts(r, files):
    """ledger_integrity's re-derivation for retired_to_cast entries whose line no longer holds the cast."""
    text = files.read(UNIONS)
    if text is None:
        return
    lines = text.splitlines()
    rows = [json.loads(line) for line in lines if line.strip()]
    texts = I.Texts(r.root)
    results = []
    for row in rows:
        for entry in row.get('retired_to_cast') or []:
            status = I.check_entry(entry, texts)
            if status in ('stale', 'noline'):
                results.append(dict(id=row['id'], entry=entry, status=status, field=None))
    if not results:
        return
    history = I.History(r.root) if r.names.history else None
    before = {row['id']: list(row.get('retired_to_cast') or []) for row in rows}
    changes = I.rederive(rows, results, texts, history, None)
    by_id = {row['id']: row for row in rows}
    out = []
    for line in lines:
        if not line.strip():
            out.append(line)
            continue
        old = json.loads(line)
        row = by_id[old['id']]
        if row.get('retired_to_cast') == before[old['id']]:
            out.append(line)
            continue
        kwargs = json_line_format(line, old) or dict(sort_keys=True)
        out.append(json.dumps(dict(old, retired_to_cast=row['retired_to_cast']), **kwargs))
    for change in changes:
        r.note('unions', change['id'], change['old'], change['new'], 'cast line (' + change['how'] + ')')
    files.set(UNIONS, '\n'.join(out) + ('\n' if text.endswith('\n') else ''))


def union_baseline(r, files, renamed_ids):
    text = files.read(UNION_BASELINE)
    if text is None or not renamed_ids:
        return
    data = json.loads(text)
    kwargs, tail = json_file_format(text, data)
    ids = [renamed_ids.get(i, i) for i in data.get('ids', [])]
    if ids != data.get('ids'):
        data['ids'] = sorted(ids) if data['ids'] == sorted(data['ids']) else ids
        for old, new in renamed_ids.items():
            r.note('union_baseline', UNION_BASELINE, old, new, 'union id')
        files.set(UNION_BASELINE, json.dumps(data, **(kwargs or dict(indent=1))) + (tail or '\n'))


def accepted_ledger(r, files):
    text = files.read(ACCEPTED)
    if text is None:
        return
    out, dirty = [], False
    for number, line in enumerate(text.split('\n'), 1):
        cols = line.split('\t')
        if line.startswith('#') or not line.strip() or cols[0] == 'warning' or len(cols) < 4:
            out.append(line)
            continue
        where = f'{ACCEPTED}:{number}'
        record = dict(file=r.path('accepted', where, cols[1]), function=cols[2])
        record['function'] = r.name('accepted', where, cols[2], [record['file']])
        r.pair('accepted', where, record)
        callees = cols[4] if len(cols) > 4 else None
        if callees:
            callees = ','.join(r.name('accepted', where, c, [record['file']]) for c in callees.split(','))
        new = [cols[0], record['file'], record['function'], cols[3]] + ([callees] if len(cols) > 4 else []) \
            + cols[5:]
        if new != cols:
            r.note('accepted', where, '\t'.join(cols[1:3] + cols[4:5]), '\t'.join(new[1:3] + new[4:5]), 'row')
            dirty = True
        out.append('\t'.join(new))
    if dirty:
        files.set(ACCEPTED, '\n'.join(out))


def debt_ledger(r, files, renamed_ids):
    text = files.read(DEBT)
    if text is None:
        return
    import debt_check as D
    data = json.loads(text)
    by_file, dropped = data['by_file'], collections.Counter()
    moves = []
    for directory in sorted(by_file):
        for name in sorted(by_file[directory]):
            rel = f'{directory}/{name}'
            packed = by_file[directory][name]
            scopes = {}
            for key, row in packed[1].items():
                new_key = key if key.startswith('<') else r.name('debt', rel, key, [rel])
                scopes[new_key] = row
            if scopes != packed[1]:
                r.note('debt', rel, sorted(packed[1]), sorted(scopes), 'scope names')
                packed[1] = scopes
            if r.tree.exists(rel):
                continue
            new, how, _ = r.paths.resolve(rel)
            moves.append((directory, name, rel, new, how))
    for directory, name, rel, new, how in moves:
        packed = by_file[directory].pop(name)
        target_dir, _, target_name = (new or '').rpartition('/')
        if how == 'git rename' and new.endswith('.c') and target_name not in by_file.get(target_dir, {}):
            by_file.setdefault(target_dir, {})[target_name] = packed
            r.note('debt', rel, rel, new, f'by_file row moved ({how})')
        else:
            for key, row in packed[1].items():
                for cls, n in zip(D.CLASSES, row[1:]):
                    dropped[cls] += n
            r.note('debt', rel, rel, '', 'by_file row dropped (file gone' + (f'; {new} has its own row)' if new
                                                                            else ')'))
        if not by_file[directory]:
            del by_file[directory]
    for cls, n in dropped.items():
        data['by_class'][cls] -= n
    sites = []
    for site in data.get('bad_label_sites', []):
        base, _, ordinal = site.partition('#')
        new = renamed_ids.get(base)
        if new is None and not r.tree.exists(base.split('::')[0]):
            path = r.path('debt', 'bad_label_sites', base.split('::')[0])
            new = path + base[len(base.split('::')[0]):]
        sites.append(f'{new}#{ordinal}' if new and new != base else site)
    if sites != data.get('bad_label_sites'):
        r.note('debt', 'bad_label_sites', '', '', f'{sum(a != b for a, b in zip(sites, data["bad_label_sites"]))} '
               'sites re-keyed')
        data['bad_label_sites'] = sorted(sites)
    new_text = D.baseline_text(data)
    if new_text != text:
        files.set(DEBT, new_text)


def proto_ledger(r, files):
    text = files.read(PROTO_BASELINE)
    if text is None:
        return
    data = json.loads(text)
    kwargs, tail = json_file_format(text, data)
    sites = []
    for site in data.get('candidate_sites', []):
        parts = site.split('::')
        paths = [p for p in parts if p.startswith(('src/', 'include/'))]
        new = [r.path('proto', site, p) if p.startswith(('src/', 'include/')) else
               r.name('proto', site, p, paths) for p in parts]
        sites.append('::'.join(new))
    if sites != data.get('candidate_sites'):
        for a, b in zip(data['candidate_sites'], sites):
            if a != b:
                r.note('proto', PROTO_BASELINE, a, b, 'candidate site')
        data['candidate_sites'] = sorted(sites) if data['candidate_sites'] == sorted(data['candidate_sites']) \
            else sites
        files.set(PROTO_BASELINE, json.dumps(data, **(kwargs or dict(indent=2))) + (tail or '\n'))


def soundness_ledger(r, files):
    text = files.read(SOUNDNESS)
    if text is None:
        return
    data = json.loads(text)
    kwargs, tail = json_file_format(text, data)
    changed = False
    for key in ('identities', 'identity_counts'):
        rows = data.get(key)
        if not isinstance(rows, list):
            continue
        for i, row in enumerate(rows):
            if not isinstance(row, list) or len(row) < 2 or not isinstance(row[0], str):
                continue
            where = f'{SOUNDNESS} {key}[{i}]'
            path = r.path('soundness', where, row[0])
            record = dict(file=path, function=r.name('soundness', where, row[1], [path]))
            r.pair('soundness', where, record)
            new = [record['file'], record['function']] + [r.text('soundness', where, v, [path])
                                                          if isinstance(v, str) else v for v in row[2:]]
            if new != row:
                r.note('soundness', where, row[:2], new[:2], 'identity')
                rows[i] = new
                changed = True
    if changed:
        files.set(SOUNDNESS, json.dumps(data, **(kwargs or dict(indent=2))) + (tail or '\n'))


def layout_inline_ledger(r, files, base, write):
    text = files.read(LAYOUT_INLINE)
    if text is None:
        return
    for number, line in enumerate(text.splitlines(), 1):
        if line.strip():
            tu = json.loads(line).get('tu_new')
            if isinstance(tu, str) and not r.tree.exists(tu):
                r.fail('layout_inline', f'{LAYOUT_INLINE}:{number}', tu, 'tu_new does not exist')
    script = HERE.parent / 'typing' / 'refresh_layout_inline.py'
    args = [sys.executable, str(script), '--root', str(r.root), '--base', base or 'HEAD']
    result = subprocess.run(args + ([] if write else ['--check']), capture_output=True, text=True)
    report = (result.stdout + result.stderr).strip()
    if result.returncode:
        if write:
            r.fail('layout_inline', LAYOUT_INLINE, '(refresh)', report.splitlines()[-1] if report else 'failed')
        else:
            r.note('layout_inline', LAYOUT_INLINE, '', '', 'refresh_layout_inline --check: ' +
                   (report.splitlines()[-1] if report else 'records would change'))
    elif write:
        files.original[LAYOUT_INLINE] = files.texts[LAYOUT_INLINE] = (r.root / LAYOUT_INLINE).read_text()


# A file-scope data definition: `static u32 table[33] = {`, `s32 *D_8017834C = ...`, `T name[] = {`.
DATA_DEFINITION = re.compile(r'(?m)^(?:static\s+|const\s+)*[A-Za-z_][\w \t]*?[\s*]([A-Za-z_]\w*)\s*(?:\[[^\]\n]*\]\s*)*=')
AGGREGATED = re.compile(r'(?m)^[ \t]*#[ \t]*include[ \t]*"([^"]+\.c)"')
TOOL_LITERAL = re.compile(r"""(['"])((?:src|include)/[\w/.+-]+\.(?:c|h|inc)|[\w.+-]+\.(?:c|inc))\1""")


def tool_tables(r, files):
    """Quoted src/include paths (and bare file names) in the listed tool tables."""
    for rel in TOOL_TABLES:
        text = files.read(rel)
        if text is None:
            continue

        def sub(m, rel=rel):
            value = m.group(2)
            where = f'{rel} {value}'
            if '/' in value:
                new = r.path('tools', where, value)
            else:
                new = basename_now(r, where, value)
            if new != value:
                r.note('tools', where, value, new, 'literal')
            return m.group(1) + new + m.group(1)
        new_text = TOOL_LITERAL.sub(sub, text)
        if new_text != text:
            files.set(rel, new_text)


def basename_now(r, where, base):
    """A bare file name whose file is gone: the current name of the one file it was, when that name is
    unique in the tree."""
    if any(f.rsplit('/', 1)[-1] == base for f in r.tree.files):
        return base
    renamed, gone = r.paths._load()
    olds = sorted({p for p in list(renamed) + list(gone) if p.rsplit('/', 1)[-1] == base})
    news = set()
    for old in olds:
        new, _, _ = r.paths.resolve(old)
        if new:
            news.add(new)
    if len(news) != 1:
        r.fail('tools', where, base, f'{len(olds)} historical paths, {len(news)} current files')
        return base
    new_file = next(iter(news))
    old_functions = set()
    for old in olds:
        text = r.paths.last_text(old) or ''
        for name in C.defined_functions(text):
            old_functions |= {n for n in r.tree.defines.get(new_file, ()) if new_file in r.paths.function_files(name, old)
                              and (n == name or n in r.tree.by_addr.get('0x' + name[5:].lower(), ())
                                   or n in r.names.candidates(name))}
    if r.tree.defines.get(new_file, set()) - old_functions:
        r.fail('tools', where, base, f'merged into {new_file} with other functions: a file-wide rule would widen')
        return base
    # A bare name keys a file-wide rule; a table that also lists the current file by path (or another rule
    # added after the rename) decides what the rule covers now, so the name is reported, not rewritten.
    r.fail('tools', where, base, f'its file is now {new_file}: a file-wide rule, review by hand')
    return base


# ---------------------------------------------------------------- main

def run(root, base=None, only=None, history=True, write=False):
    """(Refresher, Files) after refreshing the selected ledgers in memory (written when write)."""
    started = time.time()
    r = Refresher(root, history, base)
    files = Files(root)
    want = set(only or LEDGERS)
    if 'names' in want:
        names_ledger(r, files)
    if 'floors' in want:
        refresh_jsonl(r, files, FLOORS, 'floors', lambda row, where: floor_row(r, row, where))
    if 'identities' in want:
        refresh_jsonl(r, files, IDENTITIES, 'identities', lambda row, where: identity_row(r, row, where))
    if 'bridges' in want:
        refresh_jsonl(r, files, BRIDGES, 'bridges', lambda row, where: bridge_row(r, row, where))
    renamed_ids = union_rows(r, files) if 'unions' in want else {}
    if 'unions' in want:
        union_baseline(r, files, renamed_ids)
    if 'accepted' in want:
        accepted_ledger(r, files)
    if 'debt' in want:
        debt_ledger(r, files, renamed_ids)
    if 'proto' in want:
        proto_ledger(r, files)
    if 'soundness' in want:
        soundness_ledger(r, files)
    if 'tools' in want:
        tool_tables(r, files)
    r.paths.blobs.close()
    if write:
        files.write()
    if 'layout_inline' in want:
        layout_inline_ledger(r, files, base, write)
    r.elapsed = time.time() - started
    return r, files


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--root', type=Path, default=HERE.parents[1])
    parser.add_argument('--base', help='the batch start: refresh_layout_inline maps layout_inline records from it '
                        '(default HEAD), and names.tsv line citations of files edited since it follow the edits '
                        '(default: not carried)')
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument('--check', action='store_true', help='report what would change; exit 1 if anything')
    mode.add_argument('--write', action='store_true', help='apply the changes')
    parser.add_argument('--list', action='store_true', help='print every change and unresolved value')
    parser.add_argument('--only', help='comma-separated subset of: ' + ','.join(LEDGERS))
    parser.add_argument('--no-history', action='store_true', help="HEAD's table and tree only")
    parser.add_argument('--fail-unresolved', action='store_true', help='unresolved values fail too')
    args = parser.parse_args(argv)
    only = args.only.split(',') if args.only else None
    if only and set(only) - set(LEDGERS):
        parser.error('unknown ledger: ' + ', '.join(sorted(set(only) - set(LEDGERS))))
    r, files = run(args.root.resolve(), args.base, only, not args.no_history, args.write)
    tally = collections.Counter(c[0] for c in r.changes)
    open_ = collections.Counter(u[0] for u in r.unresolved)
    limit = None if args.list else 20
    for ledger, where, old, new, how in r.changes[:limit]:
        print(f'CHANGE {ledger} {where}: {how}: {old!s:.300} -> {new!s:.300}')
    if limit is not None and len(r.changes) > limit:
        print(f'  ... {len(r.changes) - limit} more changes (--list)')
    for ledger, where, value, reason in r.unresolved[:limit]:
        print(f'UNRESOLVED {ledger} {where}: {value}: {reason}')
    if limit is not None and len(r.unresolved) > limit:
        print(f'  ... {len(r.unresolved) - limit} more unresolved (--list)')
    changed = files.changed()
    pending = changed or any(c[4].startswith('refresh_layout_inline') for c in r.changes)
    print('changes: ' + (', '.join(f'{k} {v}' for k, v in sorted(tally.items())) or 'none') +
          f'; files {"written" if args.write else "to change"}: {", ".join(changed) or "none"}')
    print('unresolved: ' + (', '.join(f'{k} {v}' for k, v in sorted(open_.items())) or 'none') +
          ('' if r.names.history else ' [no history: HEAD table only]'))
    print(f'ledger refresh {"WROTE" if args.write else "CHANGES PENDING" if pending else "CLEAN"} '
          f'({r.elapsed:.0f} s)')
    if args.check and pending:
        return 1
    if args.fail_unresolved and r.unresolved:
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main())
