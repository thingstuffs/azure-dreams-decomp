"""Unpreprocessed top-level C scanner for the header tool (stdlib only, deterministic).

The scanner never rewrites text.  It reports, with byte-exact spans:
  * function definitions (name, storage, prototype text, return/parameter tokens),
  * file-scope declarations (extern/plain/static/typedef) split into declarators,
  * preprocessor directives (#include targets, conditional nesting),
so that higher layers can classify and, separately, edit whole lines.

Comments, string and character literals are masked to spaces (newlines kept) before
structural scanning; offsets in the masked text equal offsets in the original.
"""
from __future__ import annotations

import re
from dataclasses import dataclass, field

IDENT = re.compile(r'[A-Za-z_][A-Za-z0-9_]*')
TOKEN = re.compile(r'''
    (?P<id>[A-Za-z_][A-Za-z0-9_]*)
  | (?P<num>(?:0[xX][0-9A-Fa-f]+|\d+(?:\.\d*)?(?:[eE][+-]?\d+)?)[uUlLfF]*)
  | (?P<ell>\.\.\.)
  | (?P<op>->|\+\+|--|<<=|>>=|<<|>>|<=|>=|==|!=|&&|\|\||[-+*/%&|^!~<>=?:;,.()\[\]{}#])
''', re.X)

STORAGE = {'extern', 'static', 'typedef', 'register', 'auto', 'inline', '__inline__', '__inline'}
QUALIFIERS = {'const', 'volatile', '__volatile__', '__const__', 'signed', 'unsigned', '__signed__'}
BASE_TYPES = {'void', 'char', 'short', 'int', 'long', 'float', 'double', 'signed', 'unsigned'}
TAGS = {'struct', 'union', 'enum'}


def mask(text: str) -> str:
    """Comments and literals -> spaces (newlines preserved)."""
    out = list(text)
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == '/' and i + 1 < n and text[i + 1] == '*':
            j = text.find('*/', i + 2)
            j = n if j < 0 else j + 2
            for k in range(i, j):
                if out[k] != '\n':
                    out[k] = ' '
            i = j
        elif c == '/' and i + 1 < n and text[i + 1] == '/':
            j = text.find('\n', i)
            j = n if j < 0 else j
            for k in range(i, j):
                out[k] = ' '
            i = j
        elif c in '"\'':
            j = i + 1
            while j < n and text[j] != c:
                if text[j] == '\\':
                    j += 1
                elif text[j] == '\n':
                    break
                j += 1
            j = min(j + 1, n)
            for k in range(i, j):
                if out[k] != '\n':
                    out[k] = ' '
            i = j
        else:
            i += 1
    return ''.join(out)


@dataclass
class Directive:
    start: int
    end: int            # exclusive, includes trailing newline if present
    line: int           # 1-based
    kind: str           # include / define / if / ifdef / ifndef / elif / else / endif / other
    arg: str
    depth: int          # conditional depth BEFORE this directive applies


@dataclass
class Declarator:
    name: str
    is_function: bool
    complex: bool       # function-returning-pointer-to-function etc.: never touched
    text: str           # declarator text (original, masked comments removed)
    params: list | None  # list of token lists, None for non-functions
    ptr: int            # leading '*' count in the declarator (return/obj pointer level)
    suffix: str          # array/other suffix tokens for data (e.g. '[]', '[4]')


@dataclass
class Item:
    kind: str           # 'decl' | 'def' | 'other'
    start: int
    end: int            # exclusive
    line: int
    end_line: int
    storage: list       # storage-class keywords seen
    spec: list          # specifier tokens (type), storage removed
    decls: list         # Declarator list
    cond_depth: int     # conditional nesting depth (>0: inside #if)
    body: tuple | None = None   # (start, end) of a function body
    has_body_braces: bool = False  # struct/enum/initializer braces inside a decl
    text: str = ''


@dataclass
class Scan:
    text: str
    masked: str
    directives: list = field(default_factory=list)
    items: list = field(default_factory=list)

    def line_of(self, off: int) -> int:
        return self.text.count('\n', 0, off) + 1


def tokens(s: str):
    return [m.group(0) for m in TOKEN.finditer(s)]


def _directives(text: str, masked: str):
    """Find directive lines; return (directives, masked text with directives blanked)."""
    out = list(masked)
    res = []
    depth = 0
    pos = 0
    n = len(masked)
    line = 1
    while pos < n:
        eol = masked.find('\n', pos)
        eol = n if eol < 0 else eol
        stripped = masked[pos:eol].lstrip()
        if stripped.startswith('#'):
            end = eol
            while end < n and masked[end - 1:end] == '\\' and end > pos:
                nxt = masked.find('\n', end + 1)
                end = n if nxt < 0 else nxt
            full_end = min(end + 1, n)
            body = masked[pos:end]
            m = re.match(r'\s*#\s*([A-Za-z_]*)\s*(.*)', body, re.S)
            kw = m.group(1) if m else ''
            arg = text[pos:end]
            arg = re.sub(r'^\s*#\s*[A-Za-z_]*\s*', '', arg, count=1).strip()
            kind = kw if kw in ('include', 'define', 'undef', 'if', 'ifdef', 'ifndef', 'elif', 'else', 'endif') else 'other'
            if kind in ('endif',):
                depth -= 1
            res.append(Directive(pos, full_end, line, kind, arg, depth))
            if kind in ('if', 'ifdef', 'ifndef'):
                depth += 1
            for k in range(pos, end):
                if out[k] != '\n':
                    out[k] = ' '
            line += masked.count('\n', pos, full_end)
            pos = full_end
            continue
        line += 1
        pos = eol + 1
    return res, ''.join(out)


def _match(masked: str, i: int, open_c: str, close_c: str) -> int:
    """Index just past the bracket matching masked[i] (which is open_c)."""
    depth = 0
    n = len(masked)
    while i < n:
        c = masked[i]
        if c == open_c:
            depth += 1
        elif c == close_c:
            depth -= 1
            if depth == 0:
                return i + 1
        i += 1
    return n


def _split_top(toks, sep=','):
    parts, cur, depth = [], [], 0
    for t in toks:
        if t in '([{':
            depth += 1
        elif t in ')]}':
            depth -= 1
        if t == sep and depth == 0:
            parts.append(cur)
            cur = []
        else:
            cur.append(t)
    parts.append(cur)
    return parts


def _close(toks, i):
    """Index of the token closing toks[i] (an opening bracket)."""
    pairs = {'(': ')', '[': ']', '{': '}'}
    o, c = toks[i], pairs[toks[i]]
    depth = 0
    for j in range(i, len(toks)):
        if toks[j] == o:
            depth += 1
        elif toks[j] == c:
            depth -= 1
            if depth == 0:
                return j
    return len(toks) - 1


def parse_declarator(toks):
    """toks = one declarator (no specifiers).  Returns Declarator or None."""
    # strip initializer
    depth = 0
    for k, t in enumerate(toks):
        if t in '([{':
            depth += 1
        elif t in ')]}':
            depth -= 1
        elif t == '=' and depth == 0:
            toks = toks[:k]
            break
    # strip trailing __attribute__((...))
    while len(toks) >= 2 and '__attribute__' in toks:
        k = toks.index('__attribute__')
        if k + 1 < len(toks) and toks[k + 1] == '(':
            toks = toks[:k] + toks[_close(toks, k + 1) + 1:]
        else:
            break
    ptr = 0
    i = 0
    while i < len(toks) and toks[i] in ('*', 'const', 'volatile'):
        if toks[i] == '*':
            ptr += 1
        i += 1
    rest = toks[i:]
    if not rest:
        return None
    if IDENT.fullmatch(rest[0]):
        name = rest[0]
        tail = rest[1:]
        if tail and tail[0] == '(':
            j = _close(tail, 0)
            params = _split_top(tail[1:j])
            if params == [[]]:
                params = None          # '()' -- unprototyped (K&R) declarator
            after = tail[j + 1:]
            complex_ = bool(after) and after[0] in ('(', '[')
            return Declarator(name, True, complex_, ' '.join(toks), params, ptr, '')
        return Declarator(name, False, False, ' '.join(toks), None, ptr, ' '.join(tail))
    if rest[0] == '(':
        # (*name)(...) or (name)(...) or function returning function pointer
        j = _close(rest, 0)
        inner = rest[1:j]
        names = [t for t in inner if IDENT.fullmatch(t) and t not in QUALIFIERS]
        name = names[0] if names else ''
        stars = inner.count('*')
        if '(' in inner:
            return Declarator(name, True, True, ' '.join(toks), None, ptr, '')
        if stars == 0 and name:
            # parenthesised plain name: (name)(params)
            tail = rest[j + 1:]
            if tail and tail[0] == '(':
                k = _close(tail, 0)
                params = _split_top(tail[1:k])
                return Declarator(name, True, True, ' '.join(toks), params if params != [[]] else [], ptr, '')
        return Declarator(name, False, False, ' '.join(toks), None, ptr, ' '.join(rest[j + 1:]))
    return None


def split_specifiers(toks):
    """Split leading declaration-specifier tokens from the first declarator.

    Returns (storage, spec, declarator_tokens_list)."""
    storage, spec = [], []
    i = 0
    saw_type = False
    n = len(toks)
    while i < n:
        t = toks[i]
        if t in STORAGE:
            storage.append(t)
            i += 1
            continue
        if t == '__attribute__' and i + 1 < n and toks[i + 1] == '(':
            j = _close(toks, i + 1)
            spec.extend(toks[i:j + 1])
            i = j + 1
            continue
        if t in QUALIFIERS:
            spec.append(t)
            i += 1
            continue
        if t in BASE_TYPES:
            spec.append(t)
            saw_type = True
            i += 1
            continue
        if t in TAGS:
            spec.append(t)
            i += 1
            if i < n and IDENT.fullmatch(toks[i]):
                spec.append(toks[i])
                i += 1
            if i < n and toks[i] == '{':
                j = _close(toks, i)
                spec.extend(toks[i:j + 1])
                i = j + 1
            saw_type = True
            continue
        if IDENT.fullmatch(t) and not saw_type:
            # a typedef name used as the type -- unless it is the declarator itself
            nxt = toks[i + 1] if i + 1 < n else ''
            nxt2 = toks[i + 2] if i + 2 < n else ''
            if nxt == '(' and nxt2 in ('*', '('):
                pass                      # 'T (*name)(...)': T is the type
            elif nxt in ('(', ';', ',', '=', '[', '') and not spec:
                # implicit int declaration like  f();  -- treat as declarator
                break
            spec.append(t)
            saw_type = True
            i += 1
            continue
        break
    decl_toks = toks[i:]
    return storage, spec, _split_top(decl_toks)


def scan(text: str) -> Scan:
    masked0 = mask(text)
    directives, masked = _directives(text, masked0)
    sc = Scan(text, masked, directives)
    # conditional depth per offset
    cond_marks = [(d.start, d.depth + (1 if d.kind in ('if', 'ifdef', 'ifndef') else 0)) for d in directives
                  if d.kind in ('if', 'ifdef', 'ifndef', 'endif')]

    def cond_depth_at(off):
        depth = 0
        for start, dp in cond_marks:
            if start > off:
                break
            depth = dp
        return depth

    # line index
    nl = [i for i, c in enumerate(text) if c == '\n']
    import bisect

    def line_of(off):
        return bisect.bisect_right(nl, off - 1) + 1

    n = len(masked)
    i = 0
    start = None
    while i < n:
        c = masked[i]
        if c.isspace():
            i += 1
            continue
        if start is None:
            start = i
        if c in '([':
            i = _match(masked, i, c, ')' if c == '(' else ']')
            continue
        if c == ';':
            _emit(sc, text, masked, start, i + 1, None, line_of, cond_depth_at)
            start = None
            i += 1
            continue
        if c == '{':
            head = masked[start:i]
            htoks = tokens(head)
            is_def = (htoks and htoks[-1] == ')' and '=' not in htoks
                      and not any(t in TAGS for t in htoks[:1]) and 'typedef' not in htoks)
            # struct/union/enum anywhere directly before '{' -> not a function
            if htoks and (htoks[-1] in TAGS or (len(htoks) >= 2 and htoks[-2] in TAGS)):
                is_def = False
            j = _match(masked, i, '{', '}')
            if is_def:
                _emit(sc, text, masked, start, j, (i, j), line_of, cond_depth_at)
                start = None
            i = j
            continue
        i += 1
    if start is not None and masked[start:].strip():
        _emit(sc, text, masked, start, n, None, line_of, cond_depth_at, kind='other')
    return sc


def _emit(sc, text, masked, start, end, body, line_of, cond_depth_at, kind=None):
    head = masked[start:body[0]] if body else masked[start:end]
    toks = tokens(head)
    if toks and toks[-1] == ';':
        toks = toks[:-1]
    storage, spec, dparts = split_specifiers(toks)
    decls = []
    has_braces = '{' in toks
    for part in dparts:
        if not part:
            continue
        d = parse_declarator(part)
        if d is not None:
            decls.append(d)
    if kind is None:
        kind = 'def' if body else 'decl'
    if kind == 'def' and (len(decls) != 1 or not decls[0].is_function):
        kind = 'other'
    if kind == 'decl' and not decls:
        kind = 'other'
    sc.items.append(Item(kind, start, end, line_of(start), line_of(max(start, end - 1)), storage, spec, decls,
                         cond_depth_at(start), body, has_braces, text[start:end]))
