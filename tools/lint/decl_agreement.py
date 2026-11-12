#!/usr/bin/env python3
"""Check that every declaration of a changed function agrees with its definition.

    decl_agreement.py BASE [HEAD] [--root DIR] [--fail-new] [--names f,g] [--no-data]
    decl_agreement.py --data-census [--root DIR]

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
declarations in their own file.  With no definition in the tree, the include/sdk prototype
is the reference for a library function (the Psy-Q prototype is the contract), and otherwise
every prototype under include/ is.  --fail-new exits 1 when any declaration disagrees.

Function-pointer parameters compare by shape: parameter names and the pointer's own name
are dropped, the return and inner parameter types are normalised recursively, and a
typedef of a function pointer resolves to its spelled-out form.

A data pointer agrees with `void *` (C converts silently), so a stale `void *` parameter
left behind by a void * -> record retype is reported separately as `void_pointer_stale`:
a declaration whose parameter is `void *` where the definition takes a specific record
pointer, listed only when the declaration is new on HEAD or the definition changed since
BASE.  The class is report-only unless --fail-void is given.

Data objects get the same treatment.  Every `extern` object declaration (file scope and block
scope) and every non-static file-scope definition is grouped by name and compared by element
type and dimensions: `T x[]` agrees with `T x[N]`, qualifiers, struct keywords and scalar
typedefs do not matter, and an extent that is an expression is not evaluated.  Classes:
incompatible type (different element, pointer against array, different rank), size mismatch
(same element, different known extent, or an extent that differs from the size: in
config/slus_006.14.symbols.txt, the only per-object size source) and element type only
(same width, opposite sign, e.g. u8 against s8).  With --fail-new (and in lint_closure) a name
fails when it disagrees on HEAD and it did not on BASE or gained a declared type BASE lacked.
The full list (name, address from config/names.tsv, every declaration site with its type, the
definition, the symbol size) goes to build/decl_data.tsv.
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
FNPTR_TYPEDEF = re.compile(r'typedef\s+([^;{}()]+?)\(\s*\*\s*([A-Za-z_]\w*)\s*\)\s*\(([^;{}]*)\)\s*;')
FNPTR_SHAPE = re.compile(r'^(.*?)\(\s*\*\s*(?:[A-Za-z_]\w*)?\s*\)\s*\((.*)\)\s*$', re.S)
FNPTR_PREFIX = 'fnptr:'


def scalar_aliases(root):
    """{typedef name: scalar spelling} from simple typedefs under include/ plus the fixed-width set."""
    aliases = dict(FIXED_ALIASES)
    for path in sorted((Path(root) / 'include').rglob('*.h')):
        text = C.strip_comments(path.read_text(errors='replace'))
        for match in SCALAR_TYPEDEF.finditer(text):
            aliases.setdefault(match[2], ' '.join(match[1].split()))
    for path in sorted((Path(root) / 'include').rglob('*.h')):
        text = C.strip_comments(path.read_text(errors='replace'))
        for match in FNPTR_TYPEDEF.finditer(text):
            aliases.setdefault(FNPTR_PREFIX + match[2], function_pointer_form(match[1], match[3], aliases))
    return aliases


def function_pointer_form(ret, params, aliases):
    """Canonical `ret(*)(params)`: names dropped, return and inner parameters normalised."""
    inner = normalize_params(params, aliases)
    shown = '' if inner is None else ('void' if not inner else ','.join(inner))
    return normalize_type(ret, aliases) + '(*)(' + shown + ')'


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
    if tokens.count('(') and '*' in tokens:      # function pointer: drop the names, keep the shape
        shape = FNPTR_SHAPE.match(' '.join(tokens))
        if shape:
            return function_pointer_form(shape[1], shape[2], aliases)
        return re.sub(r'\s+', '', ' '.join(tokens))
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
    if len(words) == 1 and FNPTR_PREFIX + words[0] in aliases and not stars:
        return aliases[FNPTR_PREFIX + words[0]]
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
    if '(*)(' in a and '(*)(' in b:              # `()` inside a function pointer is unprototyped
        (ret_a, args_a), (ret_b, args_b) = (x[:-1].split('(*)(', 1) for x in (a, b) if x.endswith(')'))
        return ret_a == ret_b and (not args_a or not args_b or args_a == args_b)
    return a.endswith('*') and b.endswith('*') and 'void*' in (a, b) and '(' not in a + b


def void_stale_params(declaration, reference):
    """Positions where the declaration says `void *` and the definition a specific data pointer."""
    params, ref_params = declaration[4], reference[4]
    if params is None or ref_params is None or len(params) != len(ref_params) or declaration[3] != reference[3]:
        return []
    return [i for i, (a, b) in enumerate(zip(params, ref_params))
            if a in ('void*', 'const void*') and b != a and b.endswith('*') and '(' not in b
            and b.replace('const ', '').replace('volatile ', '') != 'void*']


def show_signature(entry):
    name, _, _, ret, params, _ = entry
    inner = '()' if params is None else '(' + (', '.join(params) or 'void') + ')'
    return f'{ret} {name}{inner}'


def check_tree(root, names, files=None):
    """Disagreements: list of dicts(name, file, line, declared, expected, expected_at)."""
    return scan_tree(root, names, files)[0]


def scan_tree(root, names, files=None):
    """(disagreements, void candidates): the second list holds declarations that agree only because
    a data pointer converts to `void *`; each row also carries the definition's signature."""
    root = Path(root)
    names = set(names)
    if not names:
        return [], []
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
    problems, candidates = [], []
    for name, entries in sorted(per_name.items()):
        static_files = {f for f, e in entries if e[2] == 'def' and e[5]}
        global_defs = [(f, e) for f, e in entries if e[2] == 'def' and not e[5]]
        if global_defs:
            refs = global_defs
        else:
            # a library function: its include/sdk prototype is the contract (decision 54; owner 11-02);
            # other names without a C definition fall back to every prototype under include/
            refs = [(f, e) for f, e in entries if f.startswith('include/sdk/')] or \
                [(f, e) for f, e in entries if f.startswith('include/')]
        for file, entry in entries:
            if file in static_files:
                own = [e for f, e in entries if f == file and e[2] == 'def' and e[5]]
                reference = own
                where = [file] * len(own)
            else:
                reference = [e for _, e in refs]
                where = [f'{f}:{e[1]}' for f, e in refs]
            if reference and any(agrees(entry, r) for r in reference):
                stale = [r for r in reference if void_stale_params(entry, r)]
                if stale and entry[2] == 'decl':
                    index = reference.index(stale[0])
                    candidates.append(dict(name=name, file=file, line=entry[1], declared=show_signature(entry),
                                           expected=show_signature(stale[0]), expected_at=where[index],
                                           definition=show_signature(stale[0])))
                continue
            if not reference:
                continue
            problems.append(dict(name=name, file=file, line=entry[1], declared=show_signature(entry),
                                 expected=show_signature(reference[0]),
                                 expected_at=where[0] if ':' in where[0] else f'{where[0]}:{reference[0][1]}'))
    return problems, candidates


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


def void_pointer_stale(base_tree, head_tree, names, renames=None):
    """HEAD declarations that say `void *` where the definition takes a record pointer, when the
    declaration is new or its definition's signature differs from BASE's."""
    candidates = scan_tree(head_tree, names)[1]
    if not candidates:
        return []
    back = dict(renames or {})
    base_decls = {(p['file'], p['name'], p['declared']) for p in scan_tree(base_tree, names)[1]}
    base_sigs = base_signatures(base_tree, names)
    out = []
    for p in candidates:
        declaration_unchanged = (back.get(p['file'], p['file']), p['name'], p['declared']) in base_decls
        definition_changed = p['definition'] not in base_sigs.get(p['name'], ())
        if not declaration_unchanged or definition_changed:
            out.append(p)
    return out


def base_signatures(tree, names):
    """{name: set of definition signatures} for the wanted names under tree."""
    tree = Path(tree)
    aliases = scalar_aliases(tree)
    found = collections.defaultdict(set)
    needle = re.compile(r'\b(?:' + '|'.join(re.escape(n) for n in sorted(names)) + r')\s*\(')
    for top in ('src', 'include'):
        for path in sorted((tree / top).rglob('*')) if (tree / top).is_dir() else ():
            if path.suffix in C.SOURCE_SUFFIXES and path.is_file():
                text = path.read_text(errors='replace')
                if needle.search(text):
                    for entry in declarations(text, set(names), aliases):
                        if entry[2] == 'def':
                            found[entry[0]].add(show_signature(entry))
    return found


def format_void(p):
    return (f"VOID POINTER STALE {p['file']}:{p['line']}: {p['name']} declared as `{p['declared']}`, "
            f"definition takes a record pointer `{p['expected']}` ({p['expected_at']})")


def format_problem(p):
    return (f"STALE DECLARATION {p['file']}:{p['line']}: {p['name']} declared as `{p['declared']}`, "
            f"definition is `{p['expected']}` ({p['expected_at']})")


def report(problems, existing=(), out=None, void=(), fail_void=False):
    out = out or sys.stdout
    for p in problems:
        print(format_problem(p), file=out)
    for p in void:
        print(format_void(p), file=out)
    failing = bool(problems) or (fail_void and bool(void))
    print(f'declaration agreement {"FAIL" if failing else "PASS"}: {len(problems)} new disagreeing '
          f'declarations ({len(existing)} already disagreed on BASE, not failing); '
          f'void_pointer_stale {len(void)} ({"failing" if fail_void else "report-only"})', file=out)
    return 1 if failing else 0


def check_change(root, base, head_tree, names, renames=None, out=None, base_tree=None, fail_void=False, data=True):
    """Entry point for lint_closure: exit code 1 when a changed function has a new stale declaration.

    base_tree is an already materialised BASE (lint_closure's); without it BASE is extracted here."""
    import tempfile
    with tempfile.TemporaryDirectory(prefix='decl_agreement.') as temporary:
        if base_tree is None:
            try:
                base_tree = C.materialize(root, base, Path(temporary) / 'base')
            except subprocess.CalledProcessError:     # BASE has no src/ or include/: nothing to compare
                base_tree = Path(temporary) / 'base'
                base_tree.mkdir(exist_ok=True)
        if names:
            new, existing = new_problems(base_tree, head_tree, names, renames)
            void = void_pointer_stale(base_tree, head_tree, names, renames)
        else:
            new, existing, void = [], [], ()
        code = report(new, existing, out, void, fail_void)
        if data:
            code |= check_data(root, head_tree, base_tree, out)
    return code


def main(argv=None):
    import tempfile
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('base', nargs='?')
    parser.add_argument('head', nargs='?')
    parser.add_argument('--root', type=Path, default=HERE.parents[1])
    parser.add_argument('--fail-new', action='store_true', help='exit 1 when a disagreement is new since BASE')
    parser.add_argument('--fail-void', action='store_true',
                        help='also exit 1 for void_pointer_stale declarations (report-only by default)')
    parser.add_argument('--no-data', action='store_true', help='skip the data-object declaration pass')
    parser.add_argument('--data-census', action='store_true',
                        help='no BASE: list every data name with disagreeing declarations in --root, write '
                             'build/decl_data.tsv and print the top names')
    parser.add_argument('--names', help='comma-separated function names instead of the BASE..HEAD diff')
    args = parser.parse_args(argv)
    root = args.root.resolve()
    if args.data_census:
        return print_data_census(root)
    if not args.base:
        parser.error('BASE is required unless --data-census')
    with tempfile.TemporaryDirectory(prefix='decl_agreement.') as temporary:
        head_tree = C.materialize(root, args.head, Path(temporary) / 'head') if args.head else root
        names = set(args.names.split(',')) if args.names else changed_function_names(root, args.base, args.head)
        renames = {new: old for status, old, new in C.changes(root, args.base, args.head) if status == 'R'}
        print(f'{len(names)} changed function declarations checked')
        code = check_change(root, args.base, head_tree, names, renames, fail_void=args.fail_void,
                            data=not args.no_data)
    return code if args.fail_new or args.fail_void else 0


# ---------------------------------------------------------------------------------------------
# Data objects: every `extern` object declaration and every non-static file-scope definition
# of a name, compared by element type and total size.

EXTERN_STATEMENT = re.compile(r'(?<![\w.>])extern\s+([^;{}]*);')
DEFINITION_LINE = re.compile(
    r'^(?!extern\b|static\b|typedef\b|return\b|#)([A-Za-z_][^;(){}=\n]*?)\b([A-Za-z_]\w*)\s*((?:\[[^\]\n]*\]\s*)*)(?:=|;)',
    re.M)
STATIC_LINE = re.compile(r'^static\b[^;(){}=\n]*?\b([A-Za-z_]\w*)\s*(?:\[[^\]\n]*\]\s*)*(?:=|;)', re.M)
FNPTR_OBJECT = re.compile(r'^(.*?)\(\s*\*\s*([A-Za-z_]\w*)\s*\)\s*\((.*)\)\s*$', re.S)
QUALIFIERS = frozenset('const volatile register auto'.split())
SCALAR_SIZE = {'char': 1, 'signed char': 1, 'unsigned char': 1, 'short': 2, 'unsigned short': 2, 'int': 4,
               'unsigned': 4, 'long': 4, 'unsigned long': 4, 'long long': 8, 'unsigned long long': 8,
               'float': 4, 'double': 8, 'long double': 8}
SIGN_FAMILY = {'char': 'b', 'signed char': 'b', 'unsigned char': 'b', 'short': 'h', 'unsigned short': 'h',
               'int': 'w', 'unsigned': 'w', 'long': 'w', 'unsigned long': 'w'}
INTEGER = re.compile(r'^(?:0[xX][0-9a-fA-F]+|\d+)[uUlL]*$')
SYMBOL_SIZE = re.compile(r'^(\w+)\s*=\s*(0[xX][0-9a-fA-F]+)\s*;\s*//.*?\bsize:(0[xX][0-9a-fA-F]+|\d+)', re.M)
CLASS_ORDER = ('incompatible type', 'size mismatch', 'element type only')


def clean_text(text):
    return '\n'.join(' ' * len(l) if l.lstrip().startswith('#') else l
                     for l in C.strip_comments(text).replace('\\\n', ' \n').split('\n'))


def parse_dims(text):
    """Tuple of dimensions: int, None for `[]`, or the expression text when it is not a literal."""
    dims = []
    for part in re.findall(r'\[([^\]]*)\]', text):
        part = part.strip()
        dims.append(None if not part else int(part.rstrip('uUlL'), 0) if INTEGER.match(part) else part)
    return tuple(dims)


def object_declarators(statement, aliases):
    """[(name, element type, dims)] of an extern statement, or [] for function declarations."""
    statement = statement.strip()
    shape = FNPTR_OBJECT.match(statement)
    if shape:
        return [(shape[2], function_pointer_form(re.sub(r'\bstruct\b', '', shape[1]), shape[3], aliases), ())]
    if '(' in statement:
        return []
    chunks = split_params(statement)
    base, stars_base, out = None, 0, []
    for index, chunk in enumerate(chunks):
        tokens = [t for t in TOKEN.findall(chunk) if t not in QUALIFIERS]
        end = tokens.index('[') if '[' in tokens else len(tokens)
        head = tokens[:end]
        ids = [i for i, t in enumerate(head) if re.match(r'[A-Za-z_]', t)]
        if not ids:
            return []
        name_at = ids[-1]
        name = head[name_at]
        before = head[:name_at]
        if index == 0:
            words = [t for t in before if t != '*']
            if not words or any(w in STORAGE and w != 'extern' for w in words):
                words = [w for w in words if w not in STORAGE]
            base = [w for w in words if w != 'extern']
            if not base:
                return []
            stars = before.count('*')
        else:
            stars = before.count('*')
        element = normalize_type(' '.join(base) + ' ' + '*' * stars, aliases)
        out.append((name, element, parse_dims(''.join(tokens[end:]))))
    return out


def element_size(element):
    if element.endswith('*') and '(' not in element:
        return 4
    return SCALAR_SIZE.get(element)


def total_size(element, dims):
    size = element_size(element)
    if size is None or any(not isinstance(d, int) for d in dims):
        return None
    for d in dims:
        size *= d
    return size


def dims_compatible(a, b):
    if a == b:
        return True
    if len(a) == 1 and a[0] is None or len(b) == 1 and b[0] is None:
        return True                              # `T x[]` agrees with any T extent
    if len(a) != len(b):
        return False
    return all(x == y or x is None or y is None or isinstance(x, str) or isinstance(y, str)
               for x, y in zip(a, b))


def data_class(a, b):
    """Disagreement class between two (element, dims) types, or None when they agree."""
    (elem_a, dims_a), (elem_b, dims_b) = a, b
    if elem_a != elem_b:
        family = SIGN_FAMILY.get(elem_a)
        if family is None or family != SIGN_FAMILY.get(elem_b):
            return 'incompatible type'
        return 'element type only' if dims_compatible(dims_a, dims_b) else 'size mismatch'
    if dims_compatible(dims_a, dims_b):
        return None
    sizes = total_size(elem_a, dims_a), total_size(elem_a, dims_b)
    if len(dims_a) != len(dims_b) and sizes[0] is not None and sizes[0] == sizes[1]:
        return 'incompatible type'
    return 'size mismatch'


def show_type(element, dims):
    return element + ''.join('[' + ('' if d is None else str(d)) + ']' for d in dims)


def scan_data_text(text, aliases):
    """(declarations, definitions, statics): declarations [(name, line, element, dims)],
    definitions the same for non-static file-scope definitions, statics the set of static names."""
    clean = clean_text(text)
    decls, defs = [], []
    if 'extern' in clean:
        for match in EXTERN_STATEMENT.finditer(clean):
            line = clean.count('\n', 0, match.start(1)) + 1
            for name, element, dims in object_declarators(match[1], aliases):
                decls.append((name, line, element, dims))
    for match in DEFINITION_LINE.finditer(clean):
        words = [t for t in TOKEN.findall(match[1]) if t not in QUALIFIERS]
        if not words or any(w in KEYWORD_HEADS for w in words):
            continue
        stars = match[1].count('*')
        base = [w for w in words if w != '*']
        if not base:
            continue
        element = normalize_type(' '.join(base) + ' ' + '*' * stars, aliases)
        line = clean.count('\n', 0, match.start(2)) + 1
        defs.append((match[2], line, element, parse_dims(match[3])))
    statics = {m[1] for m in STATIC_LINE.finditer(clean)}
    return decls, defs, statics


def symbol_sizes(root):
    """{name: (address text, size)} from the SLUS symbol list; the only per-object size source."""
    path = Path(root) / 'config/slus_006.14.symbols.txt'
    if not path.is_file():
        return {}
    return {m[1]: (m[2].lower(), int(m[3], 0)) for m in SYMBOL_SIZE.finditer(path.read_text(errors='replace'))}


def name_addresses(root):
    """{name: address} from config/names.tsv (new and old spelling) and the SLUS symbol list."""
    out = {}
    path = Path(root) / 'config/names.tsv'
    if path.is_file():
        for line in path.read_text(errors='replace').splitlines():
            parts = line.split('\t')
            if len(parts) >= 3 and parts[0].startswith('0x'):
                out.setdefault(parts[2], parts[0])
                out.setdefault(parts[1], parts[0])
    for name, (address, _) in symbol_sizes(root).items():
        out.setdefault(name, address)
    return out


def data_files(root):
    import os
    root = str(root)
    out = []
    for top in ('src', 'include'):
        for directory, _, names in os.walk(os.path.join(root, top)):
            rel = os.path.relpath(directory, root).replace(os.sep, '/')
            out += [f'{rel}/{n}' for n in names if n.endswith(C.SOURCE_SUFFIXES)]
    return sorted(out)


def parse_data_files(root, files=None, reuse=None):
    """{file: (text hash, declarations, definitions, statics)}; a file whose text hash matches an
    entry of `reuse` (a previous parse made with the same aliases) is not parsed again."""
    root = Path(root)
    aliases = scalar_aliases(root)
    reuse = reuse if reuse and reuse['aliases'] == aliases else dict(files={})
    parsed = {}
    for rel in files if files is not None else data_files(root):
        try:
            text = (root / rel).read_text(errors='replace')
        except OSError:
            continue
        digest = hash(text)
        old = reuse['files'].get(rel)
        parsed[rel] = old if old and old[0] == digest else (digest, *scan_data_text(text, aliases))
    return dict(aliases=aliases, files=parsed)


def group_data(parse):
    """{name: {'decls': [(file, line, element, dims)], 'defs': [...]}} from a parse."""
    found = collections.defaultdict(lambda: dict(decls=[], defs=[]))

    def key(name, rel):
        # raw address names (D_80123456) are reused by every overlay that loads there: one object per image
        return f'{name}@{rel.split("/")[1]}' if name.startswith('D_') and rel.count('/') > 1 else name

    for rel, (_, decls, defs, statics) in parse['files'].items():
        for name, line, element, dims in decls:
            if name not in statics:
                found[key(name, rel)]['decls'].append((rel, line, element, dims))
        for name, line, element, dims in defs:
            if name not in statics:
                found[key(name, rel)]['defs'].append((rel, line, element, dims))
    return found


def scan_data_tree(root, files=None):
    return group_data(parse_data_files(root, files))


def data_disagreements(found, symbols=None):
    """{name: dict(klass, types, rows)} for each name whose declarations or definition disagree.

    types is the set of distinct (element, dims); rows [(role, site, type)] lists every declaration,
    each definition and the symbol-list size."""
    symbols = symbols or {}
    out = {}
    for name, entry in found.items():
        refs = [(f, l, e, d) for f, l, e, d in entry['defs']]
        decls = entry['decls']
        types = {(e, d) for _, _, e, d in decls + refs}
        klass = None
        ordered = sorted(types, key=lambda t: show_type(*t))
        rank = lambda c: CLASS_ORDER.index(c)
        for i, a in enumerate(ordered):
            for b in ordered[i + 1:]:
                c = data_class(a, b)
                if c and (klass is None or rank(c) < rank(klass)):
                    klass = c
        symbol = symbols.get(name.split('@')[0])
        if symbol and klass is None:
            for e, d in ordered:
                size = total_size(e, d)
                if size is not None and size != symbol[1] and not (d and d[-1] is None):
                    klass = 'size mismatch'
        if klass is None:
            continue
        rows = [('def', f'{f}:{l}', show_type(e, d)) for f, l, e, d in refs]
        rows += [('decl', f'{f}:{l}', show_type(e, d)) for f, l, e, d in decls]
        if symbol:
            rows.append(('symbol', 'config/slus_006.14.symbols.txt', f'{symbol[1]} bytes'))
        out[name] = dict(klass=klass, types=types, rows=rows)
    return out


def address_of(name, addresses):
    name = name.split('@')[0]
    if name in addresses:
        return addresses[name]
    match = re.match(r'D_([0-9A-Fa-f]{8})$', name)
    return '0x' + match[1].upper() if match else ''


def write_data_list(path, disagreements, addresses):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open('w') as stream:
        stream.write('name\taddress\tclass\trole\tsite\ttype\n')
        for name in sorted(disagreements):
            row = disagreements[name]
            for role, site, shown in row['rows']:
                stream.write(f'{name}\t{address_of(name, addresses)}\t{row["klass"]}\t{role}\t{site}\t{shown}\n')


def new_data_disagreements(head, base):
    """Names that disagree on HEAD and either did not on BASE or gained a type BASE lacked."""
    return sorted(n for n, row in head.items() if n not in base or row['types'] - base[n]['types'])


def data_census(root, tsv=None, files=None, parse=None):
    """(disagreements by name, scanned names) for the tree; writes the list when tsv is given."""
    found = group_data(parse or parse_data_files(root, files))
    result = data_disagreements(found, symbol_sizes(root))
    if tsv is not None:
        write_data_list(tsv, result, name_addresses(root))
    return result, found


def check_data(root, head_tree, base_tree, out=None):
    """Return code for the data pass: 1 when a name's data declarations disagree newly since BASE."""
    out = out or sys.stdout
    head_parse = parse_data_files(head_tree)
    head, _ = data_census(head_tree, tsv=Path(root) / 'build/decl_data.tsv', parse=head_parse)
    base, _ = data_census(base_tree, parse=parse_data_files(base_tree, reuse=head_parse))
    new = new_data_disagreements(head, base)
    for name in new:
        row = head[name]
        print(f'DATA DISAGREEMENT {name}: {row["klass"]}', file=out)
        for role, site, shown in row['rows']:
            print(f'    {role} {site}: {shown}', file=out)
    by_class = collections.Counter(row['klass'] for row in head.values())
    print(f'data declaration agreement {"FAIL" if new else "PASS"}: {len(new)} new disagreeing data names '
          f'({len(head) - len(new)} already disagreed on BASE, not failing; '
          f'{len(head)} disagreeing names on HEAD: ' + ', '.join(f'{by_class[c]} {c}' for c in CLASS_ORDER) + ')', file=out)
    return 1 if new else 0


def print_data_census(root, limit=20):
    result, found = data_census(root, tsv=root / 'build/decl_data.tsv')
    by_class = collections.Counter(row['klass'] for row in result.values())
    print(f'{len(result)} of {len(found)} data names disagree: ' +
          ', '.join(f'{by_class[c]} {c}' for c in CLASS_ORDER) + '; list in build/decl_data.tsv')
    ranked = sorted(result.items(), key=lambda kv: (-len(kv[1]['types']), -len(kv[1]['rows']), kv[0]))
    for name, row in ranked[:limit]:
        print(f'{name}\t{row["klass"]}\t{len(row["types"])} types: ' +
              ' | '.join(sorted(show_type(*t) for t in row['types'])))
    return 0


if __name__ == '__main__':
    sys.exit(main())
