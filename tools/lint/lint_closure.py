#!/usr/bin/env python3
"""Lint a change's TU closure (or the full tree) on BASE and HEAD; fail on any new warning site.

    lint_closure.py BASE [HEAD] --port PORT [--plan] [--cap N]
    lint_closure.py BASE [HEAD] --port PORT --full --base-census DIR [--save-census DIR]

Closure mode: the TUs whose diagnostics a change can move are
  1. changed registered TUs (and registered TUs that #include a changed .c fragment);
  2. TUs that include, transitively, a changed header;
  3. TUs that reference (call, install, take the address of) a function whose
     declaration or definition text changed in any changed file.
Rule 2 is capped: a header whose include closure exceeds --cap TUs contributes only
the includers that reference an identifier its changed lines declare (function,
field, typedef, macro).  Capping is printed; --full covers what a cap leaves out.

Both sides compile the same closure with lint_build's flags; BASE source comes from
`git archive BASE -- src include`.  HEAD is the checkout at --root (working tree
included) unless a HEAD revision that differs from it is given, which is archived too.
The TU list always comes from --root's registry.

Findings group by (file, function, warning) as in lint_build.  The gate compares the
number of distinct warning sites per group (a header warning seen through one more
including TU is not a new site).  Any group with more sites on HEAD fails (exit 1),
as do compiler failures on HEAD that BASE did not have.

Full mode runs the complete lint_build census on --root and compares it with a cached
BASE census directory (lint_findings.tsv + lint_summary.json from a previous run);
--save-census copies this run's census for the next landing.

Accepted sites (tools/lint/accepted_warning_sites.tsv): a change that adopts a stricter contract on purpose
(the typed Psy-Q SDK prototypes in include/sdk) records the warning groups it raises, one row per (class, file,
function) with the site count it accepts.  The file is a ratchet, not a mute:
  * Against BASE's copy a change may only lower or drop rows.  A row it adds, or a count it raises, fails the
    closure unless the file carries the stamp `--write-accepted` writes for this BASE (the sha256 of BASE's copy
    of the file, `none` when BASE has none).  Adding rows therefore takes a deliberate --write-accepted run whose
    diff a review sees; the stamp expires at the next landing, whose BASE copy is different.
  * A stamped added or raised row honours only rising sites whose every HEAD message is `passing argument N of
    'f' from incompatible pointer type` with f declared in include/sdk: the group is accepted only when its sites
    of any other message (assignment, initialization, return, a non-SDK callee) do not outnumber BASE's, so the
    honoured rise is at most its SDK sites.  Only the classes in ACCEPTABLE_CLASSES can be accepted.
  * Rows BASE already has, or that a change lowers, are the record of an earlier landing and honour nothing;
    later landings compare against a census that already has those sites.
--write-accepted writes (with the stamp) the rising groups that meet the SDK rule, drops rows this change wrote
earlier whose group no longer rises, and keeps BASE's rows.  Per-site messages come from lint_build's
`site_messages` column; a BASE census written before that column bounds BASE's other-message sites by its site
count less its SDK message kinds (a note says so).

After the warning gate, decl_agreement checks every declaration of each function whose
declaration or definition changed (block-scope externs and other headers included)
against the HEAD definition and fails on a newly disagreeing one; GCC's census cannot
see a stale local prototype whose call keeps the warning it already had.
--no-decl-check skips it.
"""
from __future__ import annotations

import argparse
import collections
from concurrent.futures import ThreadPoolExecutor
import csv
import hashlib
import io
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tarfile
import tempfile
import time

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(HERE.parent))
import lint_build  # noqa: E402

INCLUDE = re.compile(r'^[ \t]*#[ \t]*include[ \t]*([<"])([^>"\n]+)[>"]', re.M)
IDENT = re.compile(r'[A-Za-z_]\w*')
COMMENT_OR_STRING = re.compile(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', re.S)
SOURCE_SUFFIXES = ('.c', '.h', '.inc')
STOP = frozenset('''
auto break case char const continue default do double else enum extern float for goto if inline
int long register restrict return short signed sizeof static struct switch typedef union unsigned
void volatile while __inline __inline__ __attribute__ __asm__ asm define include ifdef ifndef endif
undef elif pragma defined NULL s8 u8 s16 u16 s32 u32 s64 u64 f32 f64 bool true false
'''.split())
DEFAULT_CAP = 300
ACCEPTED = 'tools/lint/accepted_warning_sites.tsv'
ACCEPTED_HEADER = 'warning\tfile\tfunction\tsites\tcallees'
ACCEPTABLE_CLASSES = frozenset({'-Wincompatible-pointer-types'})
CALLEE = re.compile(r"argument \d+ of .([A-Za-z_]\w*).")
SDK_PASSING = re.compile(r"^passing argument \d+ of '([A-Za-z_]\w*)' from incompatible pointer type$")
SDK_PROTOTYPE = re.compile(r'\b([A-Za-z_]\w*)\s*\([^;{}]*\)\s*;')
STAMP = '# BASE copy sha256: '
STAMP_LINE = re.compile(r'^# BASE copy sha256: ([0-9a-f]{64}|none)\b', re.M)


# ---------------------------------------------------------------- text helpers

def strip_comments(text):
    """Blank comments and string/char literals, keeping newlines (line numbers survive)."""
    def blank(match):
        s = match.group(0)
        if s.startswith(('"', "'")):
            return s[0] + s[-1] if len(s) > 1 else s
        return '\n' * s.count('\n') or ' '
    return COMMENT_OR_STRING.sub(blank, text)


def logical_lines(text):
    """Join backslash continuations."""
    return text.replace('\\\n', ' ').splitlines()


def top_level_statements(text):
    """Yield (statement text, terminator) for brace depth 0, ignoring preprocessor lines.

    A function definition yields its header with terminator '{'; struct bodies are
    skipped as a whole so `} Name;` yields the trailing declarator."""
    lines = [l for l in logical_lines(text) if not l.lstrip().startswith('#')]
    body = '\n'.join(lines)
    depth, start = 0, 0
    for i, ch in enumerate(body):
        if ch == '{':
            if depth == 0:
                yield body[start:i], '{'
            depth += 1
            start = i + 1
        elif ch == '}':
            depth = max(0, depth - 1)
            start = i + 1
        elif ch == ';' and depth == 0:
            yield body[start:i], ';'
            start = i + 1


FUNCTION_DECL = re.compile(r'^(?P<head>[\w\s\*]*?)\b(?P<name>[A-Za-z_]\w*)\s*\((?P<params>.*)\)\s*'
                           r'(?:__attribute__\s*\(\(.*\)\))?\s*$', re.S)


def function_signatures(text):
    """{name: {normalized declaration}} for top-level function prototypes and definitions."""
    result = collections.defaultdict(set)
    for chunk, _ in top_level_statements(strip_comments(text)):
        flat = ' '.join(chunk.split())
        if not flat or flat.startswith('typedef') or '=' in flat:
            continue
        match = FUNCTION_DECL.match(flat)
        if not match or match['name'] in STOP:
            continue
        head = match['head'].split()
        if not head:                    # a bare call or macro use, not a declaration
            continue
        head = [w for w in head if w not in ('extern', 'static', 'inline', '__inline', '__inline__')]
        params = re.sub(r'\s*([,*()])\s*', r'\1', match['params']).strip()
        result[match['name']].add(' '.join(head) + ' ' + match['name'] + '(' + params + ')')
    return dict(result)


def changed_signatures(old_text, new_text):
    """Function names whose declaration set differs between two versions of one file."""
    old = function_signatures(old_text or '')
    new = function_signatures(new_text or '')
    return {name for name in old.keys() | new.keys() if old.get(name) != new.get(name)}


DECLARATOR = re.compile(r'\b([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*(?=[;=,:])')
DEFINE = re.compile(r'^\s*#\s*define\s+([A-Za-z_]\w*)')


def declared_identifiers(line):
    """Identifiers a changed header line declares: macro, function, field, typedef or variable."""
    line = strip_comments(line)
    match = DEFINE.match(line)
    if match:
        return {match[1]}
    if line.lstrip().startswith('#'):
        return set()
    function = re.search(r'\b([A-Za-z_]\w*)\s*\(', line)
    if function and function[1] not in STOP and not re.search(r'\(\s*\*', line):
        return {function[1]}
    pointer = re.search(r'\(\s*\*\s*(?:const\s+)?([A-Za-z_]\w*)\s*\)', line)  # function pointer slot
    if pointer:
        return {pointer[1]}
    return {name for name in DECLARATOR.findall(line) if name not in STOP}


# ---------------------------------------------------------------- tree scanning

class Tree:
    """One pass over src/ and include/: include edges and the wanted identifiers each file uses."""

    def __init__(self, root, wanted=frozenset()):
        self.root = Path(root)
        self.files = {}
        for top in ('src', 'include'):
            base = self.root / top
            if base.is_dir():
                for path in base.rglob('*'):
                    if path.suffix in SOURCE_SUFFIXES and path.is_file():
                        self.files[path.relative_to(self.root).as_posix()] = path
        self.includes = {}
        self.uses = collections.defaultdict(set)         # identifier -> files using it
        self.macro_uses = collections.defaultdict(set)   # identifier -> headers using it in a body
        wanted = frozenset(wanted)
        for rel, path in self.files.items():
            text = path.read_text(errors='replace')
            self.includes[rel] = self._resolve(rel, INCLUDE.findall(text))
            if not wanted:
                continue
            clean = strip_comments(text)
            for name in set(IDENT.findall(clean)) & wanted:
                self.uses[name].add(rel)
            if rel.endswith('.h'):
                for name in self._header_bodies(clean) & wanted:
                    self.macro_uses[name].add(rel)

    def _resolve(self, rel, found):
        resolved = []
        here = os.path.dirname(rel)
        for kind, name in found:
            candidates = ([os.path.normpath(os.path.join(here, name))] if kind == '"' else [])
            candidates.append(os.path.normpath(os.path.join('include', name)))
            for candidate in candidates:
                if candidate in self.files:
                    resolved.append(candidate)
                    break
        return resolved

    @staticmethod
    def _header_bodies(clean):
        """Identifiers a header uses (not merely declares): #define bodies and inline function bodies."""
        names = set()
        for line in logical_lines(clean):
            match = DEFINE.match(line)
            if match:
                names |= set(IDENT.findall(line[match.end():]))
        depth, head_start, inside = 0, 0, False
        for i, ch in enumerate(clean):
            if ch == '{':
                if depth == 0:
                    head = clean[head_start:i]
                    inside = '(' in head and not re.search(r'\b(struct|union|enum)\b', head) and '=' not in head
                    body_start = i
                depth += 1
            elif ch == '}':
                depth = max(0, depth - 1)
                if depth == 0:
                    if inside:
                        names |= set(IDENT.findall(clean[body_start:i]))
                    head_start = i + 1
            elif ch in ';' and depth == 0:
                head_start = i + 1
        return names

    def includers(self, seeds):
        """Files that include any seed, transitively (seeds excluded unless re-reached)."""
        reverse = collections.defaultdict(set)
        for src, targets in self.includes.items():
            for target in targets:
                reverse[target].add(src)
        seen, todo = set(), list(seeds)
        while todo:
            for parent in reverse.get(todo.pop(), ()):
                if parent not in seen:
                    seen.add(parent)
                    todo.append(parent)
        return seen


# ---------------------------------------------------------------- git helpers

def git(root, *args, check=True):
    result = subprocess.run(['git', *args], cwd=root, capture_output=True, text=True)
    if check and result.returncode:
        raise ValueError(f"git {' '.join(args)}: {result.stderr.strip()}")
    return result.stdout


def show(root, rev, path):
    """File text at rev (None: working tree); None when absent."""
    if rev is None:
        p = Path(root) / path
        return p.read_text(errors='replace') if p.is_file() else None
    result = subprocess.run(['git', 'show', f'{rev}:{path}'], cwd=root, capture_output=True)
    return result.stdout.decode(errors='replace') if result.returncode == 0 else None


def changes(root, base, head):
    """[(status, old path, new path)] under src/ and include/ (renames detected)."""
    args = ['diff', '--name-status', '-M', base] + ([head] if head else []) + ['--', 'src', 'include']
    rows = []
    for line in git(root, *args).splitlines():
        parts = line.split('\t')
        status = parts[0][0]
        if status == 'R':
            rows.append(('R', parts[1], parts[2]))
        elif status == 'D':
            rows.append(('D', parts[1], None))
        elif status == 'A':
            rows.append(('A', None, parts[1]))
        else:
            rows.append((status, parts[1], parts[1]))
    if head is None:
        for path in git(root, 'ls-files', '--others', '--exclude-standard', '--', 'src', 'include').splitlines():
            rows.append(('A', None, path))
    return rows


def diff_lines(old_text, new_text):
    """Changed lines (both sides) between two texts."""
    import difflib
    old, new = (old_text or '').splitlines(), (new_text or '').splitlines()
    out = []
    for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, old, new, autojunk=False).get_opcodes():
        if tag != 'equal':
            out += old[i1:i2] + new[j1:j2]
    return out


def materialize(root, rev, dest):
    """Extract rev's src/ and include/ into dest (about 20 MB; no worktree, no ledger)."""
    if dest.exists():
        shutil.rmtree(dest)
    dest.mkdir(parents=True)
    data = subprocess.run(['git', 'archive', '--format=tar', rev, '--', 'src', 'include'],
                          cwd=root, capture_output=True, check=True).stdout
    with tarfile.open(fileobj=io.BytesIO(data)) as archive:
        archive.extractall(dest, filter='data') if hasattr(tarfile, 'data_filter') else archive.extractall(dest)
    (dest / '.ignore').write_text('*\n')
    return dest


# ---------------------------------------------------------------- closure

def compute_closure(root, base, head, registered, cap=DEFAULT_CAP, head_tree=None):
    """Plan dict: changed TUs, header includers (capped), callers, total, notes, renames."""
    head_tree = Path(head_tree or root)
    rows = changes(root, base, head)
    renames = {new: old for status, old, new in rows if status == 'R'}
    changed_new = [new for _, _, new in rows if new]
    texts = []
    for status, old, new in rows:
        texts.append(((old or new), show(root, base, old) if old else None,
                      show(root, head, new) if new else None))
    functions = set()
    header_ids = {}
    for path, old_text, new_text in texts:
        functions |= changed_signatures(old_text, new_text)
        if path.endswith('.h'):
            ids = set()
            for line in diff_lines(old_text, new_text):
                ids |= declared_identifiers(line)
            header_ids[path] = ids
    functions -= STOP
    wanted = functions | set().union(*header_ids.values()) if header_ids else set(functions)
    tree = Tree(head_tree, wanted)
    reg = set(registered)
    notes = []

    changed_tus = {p for p in changed_new if p in reg}
    fragments = [p for p in changed_new if p.endswith(('.c', '.inc')) and p not in reg]
    for fragment in fragments:
        owners = tree.includers([fragment]) & reg
        changed_tus |= owners
        if not owners:
            notes.append(f'{fragment}: changed source that no registered TU compiles')

    header_tus, capped, header_sizes = set(), [], {}
    headers = [p for p in changed_new if p.endswith('.h')]
    for _, old, new in rows:
        if old and old.endswith('.h') and not new:
            headers.append(old)       # deleted header: its old includers changed anyway
    for header in headers:
        reach = tree.includers([header]) & reg
        header_sizes[header] = len(reach)
        if len(reach) > cap:
            ids = header_ids.get(renames.get(header, header), set()) | header_ids.get(header, set())
            users = set().union(*(tree.uses.get(i, set()) for i in ids)) if ids else set()
            kept = reach & users
            capped.append(dict(header=header, includers=len(reach), kept=len(kept),
                               identifiers=sorted(ids)))
            reach = kept
        header_tus |= reach

    caller_tus = set()
    macro_skipped = []
    for name in sorted(functions):
        caller_tus |= tree.uses.get(name, set()) & reg
        for header in tree.macro_uses.get(name, ()):
            reach = tree.includers([header]) & reg
            if len(reach) > cap:
                macro_skipped.append(f'{name} via {header} ({len(reach)} TUs)')
            else:
                caller_tus |= reach
    if macro_skipped:
        notes.append('macro/inline header users over the cap, not linted: ' + '; '.join(macro_skipped))
    total = changed_tus | header_tus | caller_tus
    return dict(changed=sorted(changed_tus), header=sorted(header_tus - changed_tus),
                callers=sorted(caller_tus - changed_tus - header_tus), closure=sorted(total),
                functions=sorted(functions), capped=capped, header_sizes=header_sizes, notes=notes, renames=renames,
                changed_files=len(rows))


# ---------------------------------------------------------------- linting

def lint_tree(tree_root, tus, port, cc='gcc', jobs=2):
    """Compile tus under tree_root with lint_build's flags; (findings, failures)."""
    tree_root, port = Path(tree_root).resolve(), Path(port).resolve()
    version = subprocess.check_output([cc, '--version'], text=True).splitlines()[0]
    flags = lint_build.native_flags(port, tree_root, version)
    environment = dict(os.environ, LC_ALL='C')
    tasks = [(s, m, p) for s in tus for m in lint_build.MODES for p in lint_build.PHASES]

    def compile_one(task):
        source, mode, phase = task
        command = ['nice', '-n', '10', cc, '-' + mode, *flags]
        command += ['-fsyntax-only'] if phase == 'syntax' else ['-S', '-o', os.devnull]
        result = subprocess.run([*command, source], cwd=tree_root, env=environment,
                                capture_output=True, text=True)
        return task, result.returncode, result.stderr

    diagnostics, failures = [], []
    with ThreadPoolExecutor(max_workers=max(1, min(jobs, 4))) as pool:
        for (source, mode, phase), code, log in pool.map(compile_one, tasks):
            rows = lint_build.parse_diagnostics(log, tree_root, port, source, mode, phase)
            diagnostics.extend(rows)
            if code:
                first = next((r['file'] + ':' + str(r['line']) + ': ' + r['message']
                              for r in rows if r['severity'] != 'warning'), '(no diagnostic)')
                failures.append(dict(tu=source, mode=mode, phase=phase, first_error=first))
    return lint_build.group_findings(diagnostics), failures


def read_census(directory):
    """Findings from a lint_build output directory (lint_findings.tsv)."""
    with (Path(directory) / 'lint_findings.tsv').open(newline='') as stream:
        rows = list(csv.DictReader(stream, delimiter='\t'))
    for row in rows:
        row['count'] = int(row['count'])
    return rows


def group_sites(findings, renames=None):
    """{(file, function, warning): (sites, count, row)} with BASE paths mapped to HEAD names."""
    back = {old: new for new, old in (renames or {}).items()}
    result = {}
    for row in findings:
        file = back.get(row['file'], row['file'])
        sites = len([s for s in row['sites'].split(';') if s]) if row.get('sites') else 0
        result[(file, row['function'], row['warning'])] = (sites, int(row['count']), row)
    return result


def increases(base_findings, head_findings, renames=None):
    """Groups whose distinct-site count rose (new groups included), sorted."""
    base = group_sites(base_findings, renames)
    head = group_sites(head_findings)
    out = []
    for key, (sites, count, row) in sorted(head.items()):
        was_sites, was_count = base.get(key, (0, 0, None))[:2]
        if sites > was_sites:
            base_row = base.get(key, (0, 0, None))[2]
            out.append(dict(file=key[0], function=key[1], warning=key[2], base_sites=was_sites,
                            head_sites=sites, base_count=was_count, head_count=count,
                            sites=row['sites'], messages=row['messages'],
                            site_messages=row.get('site_messages'),
                            base_messages=base_row.get('messages') if base_row else None,
                            base_site_messages=base_row.get('site_messages') if base_row else None))
    return out


def format_increase(row):
    return (f"{row['warning']} {row['file']} {row['function']}: sites {row['base_sites']} -> "
            f"{row['head_sites']} (observations {row['base_count']} -> {row['head_count']})\n"
            f"    at {row['sites']}\n    {row['messages'][:400]}")


# ---------------------------------------------------------------- main

def print_plan(plan, out=None):
    out = out or sys.stdout
    print(f"changed files {plan['changed_files']}; closure {len(plan['closure'])} TUs = "
          f"changed {len(plan['changed'])} + header includers {len(plan['header'])} + "
          f"callers/installers {len(plan['callers'])}", file=out)
    if plan['functions']:
        shown = ', '.join(plan['functions'][:12]) + (' ...' if len(plan['functions']) > 12 else '')
        print(f"changed function declarations {len(plan['functions'])}: {shown}", file=out)
    if plan['header_sizes']:
        largest = sorted(plan['header_sizes'].items(), key=lambda kv: -kv[1])[:5]
        print(f"changed headers {len(plan['header_sizes'])}; largest include closures: "
              + ', '.join(f'{h} {n}' for h, n in largest), file=out)
    for cap in plan['capped']:
        print(f"capped {cap['header']}: {cap['includers']} including TUs -> {cap['kept']} that reference "
              f"its changed identifiers ({', '.join(cap['identifiers'][:8]) or 'none'}); "
              f"run --full for the rest", file=out)
    for note in plan['notes']:
        print('note: ' + note, file=out)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('base', help='base revision (the tree being landed onto)')
    parser.add_argument('head', nargs='?', help='head revision (default: the --root working tree)')
    parser.add_argument('--root', type=Path, default=HERE.parents[1])
    parser.add_argument('--port', type=Path, required=True, help='private port directory containing tools/build.py and include/')
    parser.add_argument('--out', type=Path, help='keep outputs here (default: a temporary directory, removed afterwards)')
    parser.add_argument('--cc', default='gcc')
    parser.add_argument('--jobs', type=int, default=int(os.environ.get('JOBS', '2')))
    parser.add_argument('--cap', type=int, default=DEFAULT_CAP, help='header closure size above which only identifier-referencing includers are kept')
    parser.add_argument('--plan', action='store_true', help='print the closure and exit')
    parser.add_argument('--list', action='store_true', help='with --plan, list the closure TUs')
    parser.add_argument('--full', action='store_true', help='full census on HEAD against --base-census')
    parser.add_argument('--base-census', type=Path, help='lint_build output directory of the BASE full census')
    parser.add_argument('--no-decl-check', action='store_true', help='skip the declaration agreement check')
    parser.add_argument('--fail-void', action='store_true',
                        help='fail on void_pointer_stale declarations (reported only by default)')
    parser.add_argument('--write-accepted', action='store_true',
                        help=f'record the rising groups of {sorted(ACCEPTABLE_CLASSES)} in {ACCEPTED} and accept them')
    parser.add_argument('--save-census', type=Path, help='with --full, copy this census here for the next landing')
    args = parser.parse_args(argv)
    if args.out is not None:
        return run(args, parser)
    with tempfile.TemporaryDirectory(prefix='lint_closure.') as temporary:
        args.out = Path(temporary)
        return run(args, parser)


def run(args, parser):
    root, out = args.root.resolve(), args.out.resolve()
    started = time.time()
    try:
        git(root, 'rev-parse', '--verify', args.base + '^{commit}')
        head = args.head
        if head:
            git(root, 'rev-parse', '--verify', head + '^{commit}')
            same = git(root, 'rev-parse', head).strip() == git(root, 'rev-parse', 'HEAD').strip()
            dirty = git(root, 'status', '--porcelain', '--', 'src', 'include').strip()
            if same and not dirty:
                head = None          # the checkout already is HEAD
        if args.full and not args.base_census:
            raise ValueError('--full needs --base-census DIR (a previous lint_build census of BASE)')
        if args.full and head:
            raise ValueError('--full lints the --root checkout; check out HEAD there instead of naming it')
        registered = lint_build.units(root)
    except (OSError, ValueError, subprocess.CalledProcessError) as error:
        parser.error(str(error))
    out.mkdir(parents=True, exist_ok=True)
    (out / '.ignore').write_text('*\n')
    if args.full:
        return run_full(args, root, out, started)
    head_tree = materialize(root, head, out / 'head_tree') if head else root

    plan = compute_closure(root, args.base, head, registered, args.cap, head_tree)
    print_plan(plan)
    print(f'closure computed in {time.time() - started:.1f}s')
    if args.plan:
        if args.list:
            for tu in plan['closure']:
                print(tu)
        return 0
    if not plan['closure']:
        print('closure empty: nothing to lint')
        refused = accepted_rows(root, args.base)[1]
        for line in refused:
            print('ACCEPTED ROW REFUSED ' + line)
        code = 1 if refused else 0
        return code if args.no_decl_check else code | decl_check(args, root, head_tree, plan['functions'],
                                                                   plan['renames'])
    base_tree = materialize(root, args.base, out / 'base_tree')
    head_tus = [tu for tu in plan['closure'] if (head_tree / tu).is_file()]
    base_tus = sorted({plan['renames'].get(tu, tu) for tu in plan['closure']})
    base_tus = [tu for tu in base_tus if (base_tree / tu).is_file()]
    t = time.time()
    base_findings, base_failures = lint_tree(base_tree, base_tus, args.port, args.cc, args.jobs)
    print(f'BASE: {len(base_tus)} TUs linted in {time.time() - t:.1f}s, {len(base_findings)} finding groups, '
          f'{len(base_failures)} failed jobs')
    t = time.time()
    head_findings, head_failures = lint_tree(head_tree, head_tus, args.port, args.cc, args.jobs)
    print(f'HEAD: {len(head_tus)} TUs linted in {time.time() - t:.1f}s, {len(head_findings)} finding groups, '
          f'{len(head_failures)} failed jobs')
    write_json(out / 'closure_result.json', dict(plan=plan, base_findings=base_findings,
               head_findings=head_findings, base_failures=base_failures, head_failures=head_failures))
    code = report(base_findings, head_findings, base_failures, head_failures, plan['renames'], started,
                  recorded_renames(root, args.base), diff_line_map(root, args.base, plan['renames']) if not head else None,
                  accepted=accepted_rows(root, args.base),
                  write_root=root if args.write_accepted else None, base=args.base,
                  sdk=sdk_functions(head_tree))
    if not args.no_decl_check:
        code |= decl_check(args, root, head_tree, plan['functions'], plan['renames'], base_tree)
    return code


def decl_check(args, root, head_tree, names, renames, base_tree=None):
    import decl_agreement
    return decl_agreement.check_change(root, args.base, head_tree, set(names), renames, base_tree=base_tree,
                                       fail_void=getattr(args, 'fail_void', False))


def write_json(path, data):
    path.write_text(json.dumps(data, indent=1) + '\n')


def rename_hints(base_findings, head_findings, rising, renames=None):
    """{(file, function, warning): old function(s)} for new groups that look like a renamed function:
    a BASE group in the same file and class, with the same site count, whose function has no
    group of that class on HEAD (a string for one candidate, a sorted list when several functions of
    one file vanished with that class and count).  Hints only; the gate still fails."""
    base = group_sites(base_findings, renames)
    head = group_sites(head_findings)
    vanished = collections.defaultdict(list)
    for (file, function, warning), (sites, _, _) in base.items():
        if (file, function, warning) not in head:
            vanished[(file, warning, sites)].append(function)
    hints = {}
    for row in rising:
        if row['base_sites'] == 0:
            old = vanished.get((row['file'], row['warning'], row['head_sites']))
            if old:
                hints[(row['file'], row['function'], row['warning'])] = old[0] if len(old) == 1 else sorted(old)
    return hints


def recorded_renames(root, base=None):
    """{name: {address}} from config/names.tsv: a function renamed at its address keeps one row per name.

    With base, BASE's rows are read too, so a name whose row a rename replaced (both functions at an address
    renamed) still records its address."""
    out = collections.defaultdict(set)
    texts = []
    path = Path(root) / 'config/names.tsv'
    if path.is_file():
        texts.append(path.read_text(errors='replace'))
    if base:
        texts.append(git(root, 'show', f'{base}:config/names.tsv', check=False))
    for text in texts:
        for line in text.splitlines():
            cols = line.split('\t')
            if len(cols) >= 3 and cols[0].startswith('0x'):
                out[cols[2]].add(cols[0].lower())
    return out


def diff_line_map(root, base, renames=None):
    """line_map(path, base_line) -> HEAD line of an unchanged BASE line, or None when the line was edited, from
    `git diff -U0 BASE` of the working tree (edits above a function shift its lines without changing them).
    `path` is the HEAD path; a file renamed since BASE (renames: {HEAD path: BASE path}) is diffed against its
    BASE path with rename detection."""
    cache = {}
    renames = renames or {}

    def hunks(path):
        if path not in cache:
            paths = [renames[path], path] if renames.get(path, path) != path else [path]
            out = git(root, 'diff', '-U0', '-M', '--no-ext-diff', base, '--', *paths, check=False)
            cache[path] = [tuple(int(n) if n else 1 for n in m.groups())
                           for m in re.finditer(r'^@@ -(\d+)(?:,(\d+))? \+(\d+)(?:,(\d+))? @@', out, re.M)]
        return cache[path]

    def line_map(path, line):
        shift = 0
        for old_start, old_len, new_start, new_len in hunks(path):
            # git names the line before the change for an empty side (pure insertion or deletion)
            old_first = old_start if old_len else old_start + 1
            new_first = new_start if new_len else new_start + 1
            if line < old_first:
                break
            if line < old_first + old_len:
                return None
            shift = (new_first + new_len) - (old_first + old_len)
        return line + shift
    return line_map


def mapped_sites(sites, line_map):
    out = []
    for site in (sites or '').split(';'):
        if site:
            path, line, col = site.rsplit(':', 2)
            head = line_map(path, int(line))
            if head is None:
                return None
            out.append(f'{path}:{head}:{col}')
    return ';'.join(out)


def proven_rename(base_findings, row, old, names, line_map=None, renames=None):
    """A hinted rename is the same warning site, not a new one, when the BASE group under the old name lists
    the same sites and config/names.tsv records both names at one address (an R6 rename). With line_map the BASE
    sites are first carried to their HEAD lines through unchanged lines, so an edit above the function that only
    shifts it does not make its sites new.  A file renamed since BASE (renames: {HEAD path: BASE path}) is
    compared under its HEAD path, as the closure compares renamed files."""
    if not names or not (names.get(old, set()) & names.get(row['function'], set())):
        return False
    base_file = (renames or {}).get(row['file'], row['file'])
    for b in base_findings:
        if b['file'] == base_file and b['function'] == old and b['warning'] == row['warning']:
            sites = ';'.join(row['file'] + site[len(base_file):] if site.startswith(base_file + ':') else site
                             for site in (b.get('sites') or '').split(';') if site)
            if sites == row['sites']:
                return True
            return bool(line_map) and mapped_sites(sites, line_map) == row['sites']
    return False


def read_accepted(text):
    """{(file, function, warning): accepted sites} from an accepted_warning_sites.tsv text (None: no file)."""
    rows = {}
    for line in (text or '').splitlines():
        cols = line.split('\t')
        if not line.strip() or line.startswith('#') or cols[0] == 'warning' or len(cols) < 4:
            continue
        rows[(cols[1], cols[2], cols[0])] = int(cols[3])
    return rows


def sdk_functions(tree):
    """Names of the functions include/sdk/*.h declares in the given tree."""
    names = set()
    for header in sorted((Path(tree) / 'include/sdk').glob('*.h')):
        text = '\n'.join(l for l in strip_comments(header.read_text(errors='replace')).splitlines()
                         if not l.lstrip().startswith('#'))
        names.update(m.group(1) for m in SDK_PROTOTYPE.finditer(text))
    return names - STOP


def is_sdk_message(message, sdk):
    match = SDK_PASSING.match(message.strip())
    return bool(match) and match.group(1) in sdk


def other_sites(sites, messages, site_messages, sdk):
    """(number of a group's sites with a message other than an SDK passing-argument one, exact).  Without
    per-site messages (a census written before lint_build's site_messages column) the count is bounded by the
    site count less the group's SDK message kinds: exact when every kind is SDK (0) or none is."""
    if not sites:
        return 0, True
    if site_messages:
        per_site = json.loads(site_messages)
        return sum(1 for msgs in per_site.values() if not msgs or not all(is_sdk_message(m, sdk) for m in msgs)), True
    kinds = [m for m in (messages or '').split(' | ') if m.strip()]
    sdk_kinds = sum(1 for m in kinds if is_sdk_message(m, sdk))
    if sdk_kinds == len(kinds):
        return 0, True
    return max(sites - sdk_kinds, 1), sdk_kinds == 0


def stamp_of(text):
    """sha256 of an accepted-file text (`none` for an absent file), the --write-accepted stamp value."""
    return 'none' if text is None else hashlib.sha256(text.encode()).hexdigest()


def accepted_rows(root, base):
    """(honoured, refused) for the --root accepted file against BASE's copy.  Rows added or raised against BASE
    are honoured only when the file carries the --write-accepted stamp of BASE's copy and their class is
    acceptable; otherwise each is refused (the closure fails).  Lowered, dropped and unchanged rows honour
    nothing."""
    head_text = show(root, None, ACCEPTED)
    base_text = show(root, base, ACCEPTED)
    head, before = read_accepted(head_text), read_accepted(base_text)
    grown = {k: v for k, v in head.items() if before.get(k) is None or v > before[k]}
    stamp = STAMP_LINE.search(head_text or '')
    stamped = bool(stamp) and stamp.group(1) == stamp_of(base_text)
    honoured, refused = {}, []
    for key, limit in sorted(grown.items()):
        was = before.get(key)
        what = f"{key[2]} {key[0]} {key[1]}: {'added' if was is None else f'raised {was} ->'} {limit}"
        if key[2] not in ACCEPTABLE_CLASSES:
            refused.append(what + ' (class cannot be accepted)')
        elif not stamped:
            refused.append(what + ' (no --write-accepted stamp for this BASE: a change may only lower or drop rows)')
        else:
            honoured[key] = limit
    return honoured, refused


def honour_sdk_only(row, sdk):
    """None when a rising group's growth is SDK passing-argument sites only, else the reason it is not."""
    head_other, _ = other_sites(row['head_sites'], row.get('messages'), row.get('site_messages'), sdk)
    base_other, exact = other_sites(row['base_sites'], row.get('base_messages'), row.get('base_site_messages'), sdk)
    if head_other > base_other:
        return (f"{head_other} site(s) with assignment/initialization/return or non-SDK callee messages "
                f"(BASE {base_other}{'' if exact else ', bounded'})")
    return None


def write_accepted(root, rising, base=None, sdk=frozenset()):
    """Record the rising groups of acceptable classes whose growth is SDK passing-argument sites only in the
    --root accepted file, stamped for BASE's copy; rows this change wrote earlier whose group no longer rises are
    dropped and BASE's rows are kept.  Returns the recorded groups (honoured in this run)."""
    path = Path(root) / ACCEPTED
    base_text = show(root, base, ACCEPTED) if base else None
    before = read_accepted(base_text)
    current = read_accepted(path.read_text() if path.is_file() else None)
    rows, added = {}, {}
    for key, sites in current.items():
        if key in before:
            rows[key] = sites
    for row in rising:
        key = (row['file'], row['function'], row['warning'])
        if row['warning'] not in ACCEPTABLE_CLASSES or honour_sdk_only(row, sdk):
            continue
        callees = ','.join(sorted(set(CALLEE.findall(row.get('messages') or ''))))
        rows[key] = (row['head_sites'], callees)
        added[key] = row['head_sites']
    callee_cols = {}
    for line in (path.read_text().splitlines() if path.is_file() else []):
        cols = line.split('\t')
        if len(cols) >= 4 and not line.startswith('#') and cols[0] != 'warning':
            callee_cols[(cols[1], cols[2], cols[0])] = cols[4] if len(cols) > 4 else ''
    body = []
    for key, value in rows.items():
        sites, callees = value if isinstance(value, tuple) else (value, callee_cols.get(key, ''))
        body.append('\t'.join([key[2], key[0], key[1], str(sites), callees]))
    header = ['# Warning groups accepted once by the landing that wrote them (tools/lint/lint_closure.py).',
              STAMP + stamp_of(base_text) + ' (written by --write-accepted; rows added or raised against any other '
              'BASE fail the closure)',
              ACCEPTED_HEADER]
    path.write_text('\n'.join(header + sorted(body, key=lambda l: l.split('\t')[1:3] + [l.split('\t')[0]])) + '\n')
    print(f'wrote {len(added)} accepted group(s) to {ACCEPTED}')
    return added


def report(base_findings, head_findings, base_failures, head_failures, renames, started, names=None,
           line_map=None, accepted=None, write_root=None, base=None, sdk=frozenset()):
    """Print the gate and return its exit code.  `accepted` is accepted_rows()'s (honoured, refused) pair (a
    bare dict is taken as honoured rows); refused rows fail."""
    honoured, refused = accepted if isinstance(accepted, tuple) else (accepted or {}, [])
    rising = increases(base_findings, head_findings, renames)
    hints = rename_hints(base_findings, head_findings, rising, renames)
    kept = []
    for row in rising:
        hint = hints.get((row['file'], row['function'], row['warning']))
        candidates = [hint] if isinstance(hint, str) else (hint or [])
        proven = [old for old in candidates if proven_rename(base_findings, row, old, names, line_map, renames)]
        if len(proven) == 1:
            print(f"renamed {row['warning']} {row['file']} {proven[0]} -> {row['function']}: the same "
                  f"{row['head_sites']} site(s), both names at one address in config/names.tsv (not new)")
        else:
            kept.append(row)
    rising = kept
    if any(r.get('base_sites') and not r.get('base_site_messages') for r in rising):
        print('note: the BASE census has no per-site messages; BASE sites of other messages are bounded by the '
              'site count less the SDK message kinds')
    if write_root is not None:
        honoured, refused = write_accepted(write_root, rising, base, sdk), []
    for line in refused:
        print('ACCEPTED ROW REFUSED ' + line)
    if honoured:
        kept = []
        for row in rising:
            limit = honoured.get((row['file'], row['function'], row['warning']))
            why = honour_sdk_only(row, sdk) if limit is not None else None
            if limit is not None and row['head_sites'] <= limit and why is None:
                print(f"accepted {row['warning']} {row['file']} {row['function']}: sites {row['base_sites']} -> "
                      f"{row['head_sites']} (recorded in {ACCEPTED} by this change)")
            else:
                if why:
                    print(f"not accepted {row['warning']} {row['file']} {row['function']}: {why}")
                kept.append(row)
        print(f'accepted groups: {len(rising) - len(kept)} of {len(rising)} rising')
        rising = kept
    back = {old: new for new, old in (renames or {}).items()}
    base_failed = {(back.get(f['tu'], f['tu']), f['mode'], f['phase']) for f in base_failures}
    new_failures = [f for f in head_failures if (f['tu'], f['mode'], f['phase']) not in base_failed]
    for row in rising:
        print('NEW ' + format_increase(row))
        old = hints.get((row['file'], row['function'], row['warning']))
        if old:
            print(f'    hint: possibly {" or ".join(old) if isinstance(old, list) else old} renamed '
                  '(same file, class and site count gone from BASE)')
    for failure in new_failures:
        print(f"NEW COMPILE FAILURE {failure['tu']} -{failure['mode']} {failure['phase']}: {failure['first_error']}")
    by_class = collections.Counter(r['warning'] for r in rising)
    summary = ', '.join(f'{w} +{n}' for w, n in sorted(by_class.items())) or 'none'
    status = 'FAIL' if rising or new_failures or refused else 'PASS'
    print(f'lint closure {status}: {len(rising)} groups with new sites ({summary}), '
          f'{len(new_failures)} new compile failures, {len(refused)} refused accepted rows; '
          f'{time.time() - started:.1f}s total')
    return 1 if status == 'FAIL' else 0


def run_full(args, root, out, started):
    base_dir = args.base_census.resolve()
    base_summary = json.loads((base_dir / 'lint_summary.json').read_text())
    if base_summary.get('limited'):
        print('--base-census is a partial (--only) census; it cannot gate a full run', file=sys.stderr)
        return 2
    census = out / 'full'
    code = lint_build.main(['--root', str(root), '--port', str(args.port), '--out', str(census),
                            '--cc', args.cc, '--jobs', str(args.jobs)])
    summary = json.loads((census / 'lint_summary.json').read_text())
    for key in ('schema_version', 'compiler', 'modes', 'phases', 'flags'):
        if base_summary.get(key) != summary.get(key):
            print(f'base census {key} differs from this run; re-census BASE before comparing', file=sys.stderr)
            return 2
    if base_summary.get('units') != summary.get('units'):
        print(f"note: TU count {base_summary.get('units')} -> {summary.get('units')}")
    base_failures = list(csv.DictReader((base_dir / 'lint_compile_failures.tsv').open(), delimiter='\t')) \
        if (base_dir / 'lint_compile_failures.tsv').is_file() else []
    head_failures = list(csv.DictReader((census / 'lint_compile_failures.tsv').open(), delimiter='\t'))
    renames = {new: old for status, old, new in changes(root, args.base, None) if status == 'R'}
    result = report(read_census(base_dir), read_census(census), base_failures, head_failures,
                    renames, started, recorded_renames(root, args.base), diff_line_map(root, args.base, renames),
                    accepted=accepted_rows(root, args.base), write_root=root if args.write_accepted else None,
                    base=args.base, sdk=sdk_functions(root))
    if not args.no_decl_check:
        import decl_agreement
        names = decl_agreement.changed_function_names(root, args.base, None)
        result |= decl_agreement.check_change(root, args.base, root, names, renames,
                                                 fail_void=args.fail_void)
    if args.save_census and result == 0 and code == 0:
        args.save_census.mkdir(parents=True, exist_ok=True)
        for name in ('lint_findings.tsv', 'lint_summary.json', 'lint_compile_failures.tsv', 'lint_units.tsv'):
            shutil.copy2(census / name, args.save_census / name)
        print(f'census saved to {args.save_census}')
    return result


if __name__ == '__main__':
    sys.exit(main())
