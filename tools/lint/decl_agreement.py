#!/usr/bin/env python3
"""Check that every declaration of a changed function agrees with its definition.

    decl_agreement.py BASE [HEAD] [--root DIR] [--fail-new] [--names f,g]

GCC only compares a call with the declaration that is visible at the call, so a stale
file-scope or block-scope `extern`/prototype line that disagrees with a retyped
definition keeps compiling with the very warning it already had.  The warning census
cannot see it: the diagnostic text, site and class are unchanged.

For every function whose declaration or definition text differs between BASE and HEAD
(HEAD defaults to the --root working tree), this tool finds every declaration of that
name under src/ and include/ -- prototypes in headers, file-scope prototypes, and
block-scope declarations inside function bodies -- and compares return type and
parameter types with the definition(s) on HEAD after normalisation: whitespace,
parameter names, `struct`/`union`/`enum` keywords, scalar typedef aliases (s32/int,
u8/unsigned char, ...), `unsigned int`/`unsigned`, array parameters/pointers.  An
empty parameter list `()` is an unprototyped declaration and agrees with anything.

A declaration agrees if it matches any non-static definition of the name (overlays can
define one name in several units); static definitions are checked only against the
declarations in their own file.  With no definition in the tree, prototypes under
include/ are the reference.  --fail-new exits 1 when any declaration disagrees.
"""
from __future__ import annotations

import argparse
import collections
from pathlib import Path
import re
import subprocess
import sys

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import lint_closure as C  # noqa: E402

KEYWORD_HEADS = frozenset('return else do case default goto sizeof typedef'.split())
BASE_TYPES = frozenset('int char short long unsigned signed float double void'.split())
STORAGE = frozenset('extern static inline __inline __inline__ register auto'.split())
TOKEN = re.compile(r'[A-Za-z_]\w*|\.\.\.|\S')
SCALAR_TYPEDEF = re.compile(r'typedef\s+((?:(?:unsigned|signed|short|long|int|char|float|double)\s+)+)([A-Za-z_]\w*)\s*;')
FIXED_ALIASES = {'s8': 'signed char', 'u8': 'unsigned char', 's16': 'short', 'u16': 'unsigned short',
                 's32': 'int', 'u32': 'unsigned', 's64': 'long long', 'u64': 'unsigned long long',
                 'f32': 'float', 'f64': 'double'}


def scalar_aliases(root):
    """{typedef name: scalar spelling} from simple typedefs under include/ plus the fixed-width set."""
    aliases = dict(FIXED_ALIASES)
    for path in sorted((Path(root) / 'include').rglob('*.h')):
        text = C.strip_comments(path.read_text(errors='replace'))
        for match in SCALAR_TYPEDEF.finditer(text):
            aliases.setdefault(match[2], ' '.join(match[1].split()))
    return aliases


def scalar_form(words):
    """Canonical spelling of a run of scalar keywords: order and `int` redundancy removed."""
    words = list(words)
    count = collections.Counter(words)
    sign = 'unsigned ' if count['unsigned'] else ''
    if count['char']:
        return ('signed ' if count['signed'] else sign) + 'char'
    if count['float'] or count['double']:
        return 'float' if count['float'] else ('long double' if count['long'] else 'double')
    if count['short']:
        return sign + 'short'
    if count['long'] >= 2:
        return sign + 'long long'
    if count['long']:
        return sign + 'long'
    if count['void']:
        return 'void'
    return sign.strip() or 'int' if not sign else 'unsigned'


def normalize_type(text, aliases):
    """Canonical type string for a parameter or return type; the parameter name is dropped."""
    tokens = [t for t in TOKEN.findall(text) if t not in STORAGE and t not in ('struct', 'union', 'enum')]
    if tokens.count('(') and '*' in tokens:      # function pointer: drop the inner name, keep the shape
        text = re.sub(r'\(\s*\*\s*[A-Za-z_]\w*\s*\)', '(*)', ' '.join(tokens))
        return re.sub(r'\s+', '', text)
    if '[' in tokens:                            # arrays decay to pointers; the name precedes '['
        joined, skip = [], 0
        for t in tokens:
            if t == '[':
                skip = 1
                if len(joined) >= 2 and re.match(r'[A-Za-z_]', joined[-1]) and joined[-1] not in BASE_TYPES:
                    joined.pop()
                joined.append('*')
            elif t == ']':
                skip = 0
            elif not skip:
                joined.append(t)
        tokens = joined
    elif len(tokens) >= 2 and re.match(r'[A-Za-z_]', tokens[-1]) and tokens[-1] not in BASE_TYPES \
            and tokens[-1] not in ('const', 'volatile'):
        # drop a trailing parameter name: an identifier after another identifier or '*'
        if re.match(r'[A-Za-z_]', tokens[-2]) or tokens[-2] == '*':
            before = tokens[:-1]
            if not (len(before) == 1 and before[0] in ('const', 'volatile')):
                tokens = before
    quals = sorted(t for t in tokens if t in ('const', 'volatile'))
    stars = ''.join(t for t in tokens if t == '*')
    words = [t for t in tokens if t not in ('const', 'volatile', '*')]
    resolved = []
    for w in words:
        resolved += aliases[w].split() if w in aliases else [w]
    if resolved and all(w in BASE_TYPES for w in resolved):
        base = scalar_form(resolved)
    else:
        base = ' '.join(resolved)
    return ' '.join(quals + [base]) + stars


def split_params(params):
    depth, current, parts = 0, [], []
    for ch in params:
        if ch in '([':
            depth += 1
        elif ch in ')]':
            depth -= 1
        if ch == ',' and depth == 0:
            parts.append(''.join(current))
            current = []
        else:
            current.append(ch)
    parts.append(''.join(current))
    return [p.strip() for p in parts]


def normalize_params(params, aliases):
    """None for an unprototyped `()`; [] for `(void)`; else the list of normalized types."""
    params = params.strip()
    if not params:
        return None
    if params == 'void':
        return []
    return [normalize_type(p, aliases) for p in split_params(params)]


def find_matching(text, start):
    """Index of the ')' matching the '(' at start, or -1."""
    depth = 0
    for i in range(start, len(text)):
        if text[i] == '(':
            depth += 1
        elif text[i] == ')':
            depth -= 1
            if depth == 0:
                return i
    return -1


def declarations(text, names, aliases):
    """[(name, line, kind, return type, params, static)] for each declaration/definition of a wanted name.

    kind is 'def' when a body follows, 'decl' when ';' follows.  Calls, address-of uses
    and initializers are not declarations: a declaration's head is only type words."""
    clean = '\n'.join(' ' * len(l) if l.lstrip().startswith('#') else l
                      for l in C.strip_comments(text).replace('\\\n', ' \n').split('\n'))
    wanted = '|'.join(re.escape(n) for n in sorted(names))
    if not wanted:
        return []
    found = []
    for match in re.finditer(r'\b(' + wanted + r')\s*\(', clean):
        open_paren = match.end() - 1
        close = find_matching(clean, open_paren)
        if close < 0:
            continue
        tail = clean[close + 1:close + 200].lstrip()
        tail = re.sub(r'^(?:__attribute__\s*\(\(.*?\)\)\s*)+', '', tail)
        if not tail or tail[0] not in ';{':
            continue
        # head: text back to the previous statement boundary
        begin = max(clean.rfind(c, 0, match.start()) for c in ';{}')
        head = clean[begin + 1:match.start()].strip()
        words = TOKEN.findall(head)
        if not words or any(w in KEYWORD_HEADS for w in words) or any(c in head for c in '=(:,?!+-/&|'):
            continue
        if not any(re.match(r'[A-Za-z_]', w) and w not in STORAGE for w in words):
            continue
        line = clean.count('\n', 0, match.start()) + 1
        found.append((match[1], line, 'def' if tail[0] == '{' else 'decl',
                      normalize_type(head, aliases),
                      normalize_params(clean[open_paren + 1:close], aliases), 'static' in words))
    return found


def agrees(declaration, reference):
    _, _, _, ret, params, _ = declaration
    _, _, _, ref_ret, ref_params, _ = reference
    if ret != ref_ret:
        return False
    if params is None or ref_params is None:
        return True
    return len(params) == len(ref_params) and all(compatible(a, b) for a, b in zip(params, ref_params))


def compatible(a, b):
    """Same normalized type, or a data pointer against `void *` (C converts those silently)."""
    if a == b:
        return True
    return a.endswith('*') and b.endswith('*') and 'void*' in (a, b) and '(' not in a + b


def show_signature(entry):
    name, _, _, ret, params, _ = entry
    inner = '()' if params is None else '(' + (', '.join(params) or 'void') + ')'
    return f'{ret} {name}{inner}'


def check_tree(root, names, files=None):
    """Disagreements: list of dicts(name, file, line, declared, expected, expected_at)."""
    root = Path(root)
    names = set(names)
    if not names:
        return []
    aliases = scalar_aliases(root)
    needle = re.compile(r'\b(?:' + '|'.join(re.escape(n) for n in sorted(names)) + r')\s*\(')
    per_name = collections.defaultdict(list)       # name -> [(file, entry)]
    paths = files if files is not None else sorted(
        p.relative_to(root).as_posix() for top in ('src', 'include') if (root / top).is_dir()
        for p in (root / top).rglob('*') if p.suffix in C.SOURCE_SUFFIXES and p.is_file())
    for rel in paths:
        text = (root / rel).read_text(errors='replace')
        if not needle.search(text):
            continue
        for entry in declarations(text, names, aliases):
            per_name[entry[0]].append((rel, entry))
    problems = []
    for name, entries in sorted(per_name.items()):
        static_files = {f for f, e in entries if e[2] == 'def' and e[5]}
        global_defs = [(f, e) for f, e in entries if e[2] == 'def' and not e[5]]
        if global_defs:
            refs = global_defs
        else:
            refs = [(f, e) for f, e in entries if f.startswith('include/')]
        for file, entry in entries:
            if file in static_files:
                own = [e for f, e in entries if f == file and e[2] == 'def' and e[5]]
                reference = own
                where = [file] * len(own)
            else:
                reference = [e for _, e in refs]
                where = [f'{f}:{e[1]}' for f, e in refs]
            if not reference or any(agrees(entry, r) for r in reference):
                continue
            problems.append(dict(name=name, file=file, line=entry[1], declared=show_signature(entry),
                                 expected=show_signature(reference[0]),
                                 expected_at=where[0] if ':' in where[0] else f'{where[0]}:{reference[0][1]}'))
    return problems


def changed_function_names(root, base, head):
    rows = C.changes(root, base, head)
    names = set()
    for _, old, new in rows:
        names |= C.changed_signatures(C.show(root, base, old) if old else None,
                                      C.show(root, head, new) if new else None)
    return names - C.STOP


def new_problems(base_tree, head_tree, names, renames=None):
    """(new, existing): HEAD disagreements split by whether the same declaration disagreed on BASE."""
    head = check_tree(head_tree, names)
    back = {new: old for new, old in (renames or {}).items()}
    base_keys = {(p['file'], p['name'], p['declared']) for p in check_tree(base_tree, names)}
    new, existing = [], []
    for p in head:
        key = (back.get(p['file'], p['file']), p['name'], p['declared'])
        (existing if key in base_keys else new).append(p)
    return new, existing


def format_problem(p):
    return (f"STALE DECLARATION {p['file']}:{p['line']}: {p['name']} declared as `{p['declared']}`, "
            f"definition is `{p['expected']}` ({p['expected_at']})")


def report(problems, existing=(), out=None):
    out = out or sys.stdout
    for p in problems:
        print(format_problem(p), file=out)
    print(f'declaration agreement {"FAIL" if problems else "PASS"}: {len(problems)} new disagreeing '
          f'declarations ({len(existing)} already disagreed on BASE, not failing)', file=out)
    return 1 if problems else 0


def check_change(root, base, head_tree, names, renames=None, out=None):
    """Entry point for lint_closure: exit code 1 when a changed function has a new stale declaration."""
    import tempfile
    if not names:
        return report([], [], out)
    with tempfile.TemporaryDirectory(prefix='decl_agreement.') as temporary:
        base_tree = C.materialize(root, base, Path(temporary) / 'base')
        new, existing = new_problems(base_tree, head_tree, names, renames)
    return report(new, existing, out)


def main(argv=None):
    import tempfile
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('base')
    parser.add_argument('head', nargs='?')
    parser.add_argument('--root', type=Path, default=HERE.parents[1])
    parser.add_argument('--fail-new', action='store_true', help='exit 1 when a disagreement is new since BASE')
    parser.add_argument('--names', help='comma-separated function names instead of the BASE..HEAD diff')
    args = parser.parse_args(argv)
    root = args.root.resolve()
    with tempfile.TemporaryDirectory(prefix='decl_agreement.') as temporary:
        head_tree = C.materialize(root, args.head, Path(temporary) / 'head') if args.head else root
        names = set(args.names.split(',')) if args.names else changed_function_names(root, args.base, args.head)
        renames = {new: old for status, old, new in C.changes(root, args.base, args.head) if status == 'R'}
        print(f'{len(names)} changed function declarations checked')
        code = check_change(root, args.base, head_tree, names, renames)
    return code if args.fail_new else 0


if __name__ == '__main__':
    sys.exit(main())
