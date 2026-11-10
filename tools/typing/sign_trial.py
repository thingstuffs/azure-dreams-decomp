#!/usr/bin/env python3
"""Opposite-sign compile trial for one record field, and per-cast removal trials.

    sign_trial.py include/x.h::Record.field [--root DIR] [--build-root DIR] [--tu src/a.c ...] [--json F]
    sign_trial.py include/x.h::Record.field --check-removal [...]

Raw lbu/lhu counts are a biased vote for a field's sign: under gcc 2.7.2 a signed field also compiles
to lbu/lhu in increments, masks, same-width copies and shifts, so only a compile can say which declaration
needs fewer value casts.  The trial answers that for one field:

  1. every TU whose include closure reaches the header and that uses the field on a value of the named record
     is compiled as it stands (a lexical type resolver reads local, parameter, global, member-chain and cast
     base types; another record with a member of that name is left alone, and a base whose type cannot be
     resolved is reported as `unresolved` and never stripped);
  2. the declared type is flipped (u16 <-> s16, u8 <-> s8), every value cast to the new type that is applied
     to that field is stripped from the TUs and headers that use it, and the TUs are compiled again;
  3. per function the two code streams are compared: identical (the flip needs no cast there) or differs
     (a cast, or another change, is still needed), together with the casts now and the functions that differ.

Recommendation: FLIP_CLEAN (all code identical with the opposite sign: every cast drops), FLIP_BETTER (fewer
functions differ than casts are stripped: try the flip and re-add casts only where code differs), TIE,
or KEEP (the flip needs at least as many casts as there are now).  Each differing function needs at least one
cast under the flip, so the differing count is a lower bound on the flip's casts.  A tie is decided by R17:
the declaration whose remaining casts sit at pure reads (use --place for the flip's casts).

--check-removal removes each existing value cast on the field (a cast to the type opposite the declaration;
with --identity also each cast to the declared type itself, with --stores each cast on the whole stored
value of a plain store `r->field = (type) value;`) one at a time, recompiles the TUs that see it and
reports NEEDED (the code changes) or NO-OP (identical: the cast can go).  Casts are found on any base the
resolver can type, including cast chains `(s16)((Rec *)p)->field` and stacked casts `(u16) (s16)r->field`.  Coordinate-like fields: check that negative values cannot occur before flipping to unsigned.

Compiles run the recipe's compiler cell and flags (the build graph of --build-root, default --root, when it
exists: tools/layout_compile_identity.production_recipes), then ccproc.  --root is edited in place and every
file is restored afterwards (also on error); use a private clone, never a tree others build in.
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
import tempfile
from concurrent.futures import ThreadPoolExecutor

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent))

FLIP = {'u16': 's16', 's16': 'u16', 'unsigned short': 'short', 'short': 'unsigned short',
        'u8': 's8', 's8': 'u8', 'unsigned char': 'signed char', 'signed char': 'unsigned char'}
SPELLINGS = {  # every spelling of a type's value cast
    's16': ('s16', 'short', 'signed short', 'int16_t'), 'u16': ('u16', 'unsigned short', 'uint16_t'),
    's8': ('s8', 'signed char', 'int8_t'), 'u8': ('u8', 'unsigned char', 'uint8_t'),
}
CANON = {'short': 's16', 'signed short': 's16', 'int16_t': 's16', 'unsigned short': 'u16', 'uint16_t': 'u16',
         'signed char': 's8', 'int8_t': 's8', 'unsigned char': 'u8', 'uint8_t': 'u8',
         's16': 's16', 'u16': 'u16', 's8': 's8', 'u8': 'u8'}
LOCAL_LABEL = re.compile(r'\$L[0-9]+\b')
FUNCTION_LABEL = re.compile(r'^([A-Za-z_]\w*):\s*$')
NOISE = ('\t.file', '\t.stabn', '\t.stabs', '\t.loc', '\t.ident')


def parse_spec(spec):
    """'include/x.h::Record.field' -> (header, owner, field).  The owner may be a member path into nested
    anonymous structs and unions of the record: 'include/x.h::Record.word.parts.high' -> owner
    'Record.word.parts', field 'high'."""
    header, _, rest = spec.partition('::')
    owner, _, field = rest.rpartition('.')
    if not (header and owner and field):
        raise ValueError(f'field spec must look like include/x.h::Record.field, got {spec!r}')
    return header, owner, field


def split_owner(owner):
    """'Record.word.parts' -> ('Record', ['word', 'parts'])."""
    record, *path = owner.split('.')
    return record, path


def owner_span(text, owner):
    """(start, end) of the braces of struct/union `owner` (typedef tail or tag), or None."""
    tail = re.search(r'\}\s*' + re.escape(owner) + r'\s*;', text)
    if tail:
        depth, i = 0, tail.start()
        while i >= 0:
            if text[i] == '}':
                depth += 1
            elif text[i] == '{':
                depth -= 1
                if depth == 0:
                    return i, tail.start()
            i -= 1
    head = re.search(r'\b(?:struct|union)\s+' + re.escape(owner) + r'\s*\{', text)
    if head:
        depth, i = 0, head.end() - 1
        while i < len(text):
            depth += (text[i] == '{') - (text[i] == '}')
            if depth == 0:
                return head.end() - 1, i
            i += 1
    return None


def member_span(text, span, member):
    """(start, end) of the braces of the nested struct/union member `member` declared at the top level of
    `span` (`union { ... } member;`), or None."""
    depth, i, end = 0, span[0] + 1, span[1]
    while i < end:
        if text[i] == '{':
            if depth == 0:
                d, j = 0, i
                while j < end:
                    d += (text[j] == '{') - (text[j] == '}')
                    if d == 0:
                        break
                    j += 1
                if re.match(r'\s*' + re.escape(member) + r'\s*;', text[j + 1:end]):
                    return i, j
                i = j
        i += 1
    return None


def top_level(text, span):
    """`span`'s body text with nested braces blanked (offsets kept)."""
    out, depth = [], 0
    for ch in text[span[0] + 1:span[1]]:
        if ch == '{':
            depth += 1
        out.append(ch if depth == 0 else ' ')
        if ch == '}':
            depth -= 1
    return ' ' * (span[0] + 1) + ''.join(out)


def field_declaration(text, owner, field):
    """(offset of the type token, declared type) of a plain scalar `type field;` in owner's body."""
    record, path = split_owner(owner)
    span = owner_span(text, record)
    if span is None:
        raise ValueError(f'no struct/union body for {record}')
    for member in path:
        span = member_span(text, span, member)
        if span is None:
            raise ValueError(f'no nested struct/union member {member} in {owner}')
    types = '|'.join(sorted(map(re.escape, FLIP), key=len, reverse=True))
    pattern = re.compile(r'(?<![\w])(' + types + r')(\s+' + re.escape(field) + r'\s*;)')
    match = pattern.search(top_level(text, span), span[0], span[1])
    if not match and not path:                  # a member of an unnamed nested struct/union
        match = pattern.search(text, span[0], span[1])
    if not match:
        raise ValueError(f'{owner}.{field} is not a plain u8/s8/u16/s16 member (arrays, unions and other types are out of scope)')
    return match.start(1), match[1]


def flip_declaration(text, owner, field):
    start, declared = field_declaration(text, owner, field)
    return text[:start] + FLIP[declared] + text[start + len(declared):], declared


SIGN_SPELLINGS = sorted({s for group in SPELLINGS.values() for s in group}, key=len, reverse=True)
CAST_BEFORE = re.compile(r'\(\s*(' + '|'.join(map(re.escape, SIGN_SPELLINGS)) + r')\s*\)$')


def field_casts(text, spellings, field, resolver=None):
    """[(offset, length of the `(type)` part, base expression, status)] of value casts to `spellings`
    applied directly to a member named `field`.  status is 'match' (the base expression has the named
    record's type, or no resolver is given), 'other' (another type has a member of that name) or
    'unresolved' (the base type cannot be determined; never stripped).

    The member access may sit on any primary base: `r->f`, `a->b[i].f` or a cast chain `((T *)p)->f`;
    the casts are the 8/16-bit value casts written directly before it, through one or more wrapping
    parentheses (`(s16)(r->f)`), and stacked casts (`(u16) (s16)r->f`) count once each."""
    wanted = {CANON[s] for s in spellings}
    rows = []
    for m in re.finditer(r'(?:->|\.)\s*' + re.escape(field) + r'\b(?!\s*(?:->|\.|\[|\())', text):
        start = base_before(text, m.start())
        base = text[start:m.start()].strip()
        if not base:
            continue
        status, pos, end = None, start, m.end()
        while True:
            j = pos
            while j > 0 and text[j - 1].isspace():
                j -= 1
            cast = CAST_BEFORE.search(text[max(0, j - 48):j])
            if cast:
                at = max(0, j - 48) + cast.start()
                if CANON[cast[1]] in wanted:
                    if status is None:
                        status = resolver(text, start, base) if resolver else 'match'
                    rows.append((at, j - at, base, status))
                pos = at
                continue
            k = end
            while k < len(text) and text[k].isspace():
                k += 1
            if j > 0 and text[j - 1] == '(' and k < len(text) and text[k] == ')':
                pos, end = j - 1, k + 1             # `( access )`: a cast may sit outside the parentheses
                continue
            break
    return sorted(rows)


STORE_CAST = re.compile(r'\(\s*(' + '|'.join(map(re.escape, SIGN_SPELLINGS)) + r')\s*\)\s*')


def store_casts(text, field, resolver=None):
    """[(offset, length of the `(type)` part, base expression, status)] of 8/16-bit value casts applied to the
    whole stored value of a plain store `base->field = (type) value;` (`value` a parenthesised group or a
    postfix expression).  A store writes the low bits whatever the value's sign, so such casts are
    candidates for removal."""
    rows = []
    for m in re.finditer(r'(?:->|\.)\s*' + re.escape(field) + r'\s*=(?!=)\s*', text):
        cast = STORE_CAST.match(text, m.end())
        if not cast:
            continue
        stop = text.find(';', cast.end())
        operand = text[cast.end():stop].strip() if stop >= 0 else ''
        if not operand:
            continue
        if operand.startswith('('):
            if TypeIndex._group_end(operand) != len(operand) - 1:
                continue
        elif not re.fullmatch(r'[A-Za-z_]\w*(?:\s*(?:->|\.)\s*[A-Za-z_]\w*|\s*\[[^\]]*\])*', operand):
            continue
        start = base_before(text, m.start())
        base = text[start:m.start()].strip()
        if not base:
            continue
        status = resolver(text, start, base) if resolver else 'match'
        rows.append((cast.start(), len(cast[0].rstrip()), base, status))
    return rows


def strip_casts(text, spellings, field, resolver=None, unresolved=None):
    """Text without the casts on matching-record accesses and their count; unresolved sites are
    appended to `unresolved` as (line, base expression) and left alone."""
    out, last, count = [], 0, 0
    for start, length, base, status in field_casts(text, spellings, field, resolver):
        if status == 'unresolved' and unresolved is not None:
            unresolved.append((line_of(text, start), base))
        if status != 'match':
            continue
        out.append(text[last:start])
        last = start + length
        count += 1
    out.append(text[last:])
    return ''.join(out), count


def remove_one_cast(text, spellings, field, index, resolver=None):
    """Remove the index-th matching-record cast (indexes count matching casts only); spellings None
    means the whole-value store casts (store_casts)."""
    found = store_casts(text, field, resolver) if spellings is None else field_casts(text, spellings, field, resolver)
    casts = [c for c in found if c[3] == 'match']
    start, length = casts[index][:2]
    return text[:start] + text[start + length:]


def base_before(text, pos):
    """Start offset of the primary expression that ends at `pos` (just before a `->`/`.`), balancing
    parentheses and brackets: `a->b[i]`, `((T *)p)`, `x.y`, `f(x)`.  A parenthesised group is the start of
    the primary unless a call name precedes it: a `(type)` cast before it applies to the whole access."""
    i = start = pos
    while True:
        while i > 0 and text[i - 1].isspace():
            i -= 1
        if i > 0 and text[i - 1] in ')]':
            close = text[i - 1]
            opener, depth = '(' if close == ')' else '[', 0
            j = i - 1
            while j >= 0:
                depth += (text[j] == close) - (text[j] == opener)
                if depth == 0:
                    break
                j -= 1
            if j < 0:
                return start
            i = start = j
            if close == ')':
                k = i
                while k > 0 and text[k - 1].isspace():
                    k -= 1
                w = k
                while w > 0 and (text[w - 1].isalnum() or text[w - 1] == '_'):
                    w -= 1
                if not ((w < k and text[w:k] not in KEYWORDS and not text[w].isdigit())
                        or (k > 0 and text[k - 1] == ']')):
                    return start                    # a cast, an operator or a statement keyword precedes it
            continue
        k = i
        while k > 0 and (text[k - 1].isalnum() or text[k - 1] == '_'):
            k -= 1
        if k == i:
            return start
        i = start = k
        j = i
        while j > 0 and text[j - 1].isspace():
            j -= 1
        if j >= 2 and text[j - 2:j] == '->':
            i = j - 2
        elif j >= 1 and text[j - 1] == '.':
            i = j - 1
        else:
            return start


def field_accesses(text, field, resolver):
    """[(offset, base, status)] of every `->field` / `.field` access with its resolved status."""
    rows = []
    for m in re.finditer(r'(?:->|\.)\s*' + re.escape(field) + r'\b', text):
        start = base_before(text, m.start())
        base = text[start:m.start()].strip()
        rows.append((m.start(), base, resolver(text, start, base) if resolver else 'match'))
    return rows


KEYWORDS = frozenset('return else do case default goto sizeof typedef extern static const volatile register '
                     'unsigned signed struct union enum if while for switch'.split())
STRUCT_END = re.compile(r'\}\s*([A-Za-z_]\w*)\s*;')
STRUCT_TAG = re.compile(r'\b(?:struct|union)\s+([A-Za-z_]\w*)\s*\{')
MEMBER = re.compile(r'^\s*(?:/\*.*?\*/\s*)*(?:(?:struct|union|const|volatile)\s+)*([A-Za-z_]\w*)\s*(\**)\s*'
                    r'([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*(?:/\*.*)?;', re.M)
HEADER_GLOBAL = re.compile(r'(?m)^extern\s+(?:(?:struct|union|const|volatile)\s+)*([A-Za-z_]\w*)\s*\*+\s*([A-Za-z_]\w*)\s*;')
FUNCTION_HEAD = re.compile(r'^(?:static\s+)?[A-Za-z_][^\n;{}=]*\([^;{}]*\)\s*\{', re.M)


class TypeIndex:
    """Record names and member types read from the headers under root/include (lexical, not a compiler):
    enough to resolve a base expression written as a declared local, parameter, global, member chain,
    array element or `(Type *)` cast.  A pointer global declared `extern` in a header (one type across the
    headers) resolves when the TU does not declare the name itself.  Several names of one record (tag and typedef) share an id."""

    def __init__(self, root):
        self.root = Path(root)
        self.ids, self.members, self.globals = {}, {}, {}
        for path in sorted((self.root / 'include').rglob('*.h')):
            self.add(path.read_text(errors='replace'), path.as_posix())

    def add(self, text, origin):
        text = re.sub(r'/\*.*?\*/', lambda m: ' ' * len(m[0]) if '\n' not in m[0] else '\n' * m[0].count('\n'), text, flags=re.S)
        spans = []
        for end in STRUCT_END.finditer(text):                      # typedef struct [Tag] { ... } Name;
            depth, i = 0, end.start()
            while i >= 0:
                depth += (text[i] == '}') - (text[i] == '{')
                if depth == 0:
                    break
                i -= 1
            if i < 0:
                continue
            head = text[max(0, i - 80):i]
            tag = re.search(r'\b(?:struct|union)\s+([A-Za-z_]\w*)\s*$', head)
            spans.append((i, end.start(), [end[1]] + ([tag[1]] if tag else [])))
        for tag in STRUCT_TAG.finditer(text):                       # struct Tag { ... };  (no typedef tail)
            if any(tag.end() - 1 == s[0] for s in spans):
                continue
            depth, i = 0, tag.end() - 1
            while i < len(text):
                depth += (text[i] == '{') - (text[i] == '}')
                if depth == 0:
                    break
                i += 1
            spans.append((tag.end() - 1, i, [tag[1]]))
        for start, end, names in spans:
            ident = (origin, start)
            body, depth, flat = text[start + 1:end], 0, []
            for ch in body:                                         # keep top-level text only
                if ch == '{':
                    depth += 1
                elif ch == '}':
                    depth -= 1
                    flat.append(' ')
                elif depth == 0:
                    flat.append(ch)
                else:
                    flat.append(' ')
            members = {m[3]: m[1] for m in MEMBER.finditer(''.join(flat)) if m[1] not in KEYWORDS | {'unsigned'}}
            self.members[ident] = members
            for name in names:
                self.ids.setdefault(name, ident)
        for m in HEADER_GLOBAL.finditer(text):                    # extern [struct] Type *name; at file scope
            if m[1] not in KEYWORDS:
                self.globals.setdefault(m[2], set()).add(m[1])

    def same(self, a, b):
        return a == b or (a in self.ids and self.ids.get(a) == self.ids.get(b))

    def declared_type(self, text, offset, name):
        """Type name of local/parameter/global `name` as declared before `offset` in its function (or file scope)."""
        heads = [m.start() for m in FUNCTION_HEAD.finditer(text, 0, offset)]
        window = text[heads[-1]:offset] if heads else text[:offset]
        pattern = re.compile(r'(?<![\w>.])(?:(?:struct|union|const|volatile|register|static|extern)\s+)*'
                             r'([A-Za-z_]\w*)\s*\**\s*\b' + re.escape(name) + r'\b\s*(?:\[[^\]]*\]\s*)*[;,=)\[]')
        found = [m[1] for m in pattern.finditer(window) if m[1] not in KEYWORDS]
        if not found and heads:
            found = [m[1] for m in re.finditer(r'(?m)^(?:(?:extern|static|const)\s+)*([A-Za-z_]\w*)\s*\**\s*\b'
                                               + re.escape(name) + r'\b\s*(?:\[[^\]]*\]\s*)*[;=]', text[:heads[-1]])
                     if m[1] not in KEYWORDS]
        if not found and len(self.globals.get(name, ())) == 1:      # a global declared in a header, one type
            found = list(self.globals[name])
        return found[-1] if found else None

    def type_of(self, text, offset, expr):
        expr = expr.strip()
        while expr.startswith('(') and expr.endswith(')') and self._balanced(expr[1:-1]):
            inner = expr[1:-1].strip()
            cast = re.match(r'^\(\s*(?:struct\s+|union\s+)?([A-Za-z_]\w*)\s*\*+\s*\)', inner)
            expr = inner
            if cast and cast.end() < len(inner):
                return cast[1]
        cast = re.match(r'^\(\s*(?:struct\s+|union\s+)?([A-Za-z_]\w*)\s*\*+\s*\)\s*\S', expr)
        if cast:
            return cast[1]
        if expr.startswith('('):                    # `((T *)p)->link`, `((T *)p)[i].x`: resolve the group, then walk
            close = self._group_end(expr)
            if close is None:
                return None
            current = self.type_of(text, offset, expr[:close + 1])
            rest = re.sub(r'^(?:\s*\[[^\]]*\])*', '', expr[close + 1:]).strip()
            if current is None or (rest and not rest.startswith(('->', '.'))):
                return None
            parts = re.split(r'\s*(?:->|\.)\s*', rest)[1:] if rest else []
        else:
            parts = re.split(r'\s*(?:->|\.)\s*', expr)
            first = re.sub(r'\[[^\]]*\]', '', parts[0]).strip()
            if not re.fullmatch(r'[A-Za-z_]\w*', first):
                return None
            current = self.declared_type(text, offset, first)
            parts = parts[1:]
            if current is None and len(self.globals.get(first, ())) > 1:
                return self._one_global(text, offset, expr, first, parts)
        return self._walk(current, parts)

    def _walk(self, current, parts):
        for member in parts:
            member = re.sub(r'\[[^\]]*\]', '', member).strip()
            ident = self.ids.get(current)
            current = self.members.get(ident, {}).get(member) if ident else None
            if current is None:
                return None
        return current

    def _one_global(self, text, offset, expr, name, parts):
        """A header global declared with several types (in headers no TU includes together): the one type
        whose record has the member chain and the member accessed next, or None when not exactly one has."""
        at = text.find(expr, offset)
        following = re.match(r'\s*(?:->|\.)\s*([A-Za-z_]\w*)', text[at + len(expr):]) if at >= 0 else None
        found = {}
        for candidate in sorted(self.globals[name]):
            current = self._walk(candidate, parts)
            if current is not None and (following is None
                                        or following[1] in self.members.get(self.ids.get(current), {})):
                found.setdefault(self.ids.get(current, current), current)
        return next(iter(found.values())) if len(found) == 1 else None

    @staticmethod
    def _group_end(expr):
        depth = 0
        for i, ch in enumerate(expr):
            depth += (ch == '(') - (ch == ')')
            if depth == 0:
                return i
        return None

    @staticmethod
    def _balanced(text):
        depth = 0
        for ch in text:
            depth += (ch == '(') - (ch == ')')
            if depth < 0:
                return False
        return depth == 0

    def resolver(self, owner):
        record, path = split_owner(owner)
        suffix = re.compile(r'\s*(?:->|\.)\s*' + r'\s*\.\s*'.join(map(re.escape, path)) + r'\s*$') if path else None

        def resolve(text, offset, base):
            if suffix is not None:              # `x->word.parts` for owner Record.word.parts: resolve x as Record
                match = suffix.search(base)
                if not match:
                    return 'other'
                base = base[:match.start()]
            if not base:
                return 'unresolved'
            found = self.type_of(text, offset, base)
            if found is None:
                return 'unresolved'
            return 'match' if self.same(found, record) else 'other'
        return resolve


def line_of(text, offset):
    return text.count('\n', 0, offset) + 1


def split_functions(asm):
    """{function label: normalised lines} from a code stream; local labels renamed, debug noise dropped."""
    current, out = None, {}
    for line in asm.splitlines():
        if line.startswith(NOISE):
            continue
        match = FUNCTION_LABEL.match(line)
        if match:
            current = match[1]
            out[current] = []
            continue
        if current is not None:
            out[current].append(LOCAL_LABEL.sub('$L', line.rstrip()))
    return out


def diff_functions(before, after):
    """[(function, first differing lines)] for functions whose code differs (missing counts as differing)."""
    rows = []
    for name in sorted(set(before) | set(after)):
        a, b = before.get(name), after.get(name)
        if a == b:
            continue
        import difflib
        delta = [l for l in difflib.unified_diff(a or [], b or [], lineterm='', n=0)
                 if l[:1] in '+-' and not l.startswith(('+++', '---'))]
        rows.append((name, delta[:4]))
    return rows


class RecipeCompiler:
    """Compile a TU of `root` at the compiler cell and flags the build graph of `build_root` links it with."""

    def __init__(self, root, build_root=None, jobs=2):
        self.root, self.build_root = Path(root).resolve(), Path(build_root or root).resolve()
        self.jobs = max(1, min(int(jobs), 2))
        self.notes = []

    def recipes(self, tu):
        import layout_compile_identity as L
        stub = dict(kind='overlay', cell='2.7.2-cdk', flags=['-G0'], asflags=[], row_id=None)
        try:
            return L.production_compiles(self.build_root, tu, stub)
        except (OSError, KeyError, ValueError, ImportError):
            self.notes.append(f'{tu}: no build graph; default 2.7.2-cdk -G0')
            return [stub]

    def compile(self, tu):
        """{function: lines} merged over the TU's distinct production compiles (prefixed when several)."""
        merged = {}
        compiles = self.recipes(tu)
        for n, recipe in enumerate(compiles):
            cc = self.build_root / 'toolchain/compilers' / ('gcc-' + recipe['cell'])
            flags = list(recipe['flags'])
            if '-O2' not in flags:
                flags = ['-O2', *flags]
            with tempfile.TemporaryDirectory(prefix='sign_trial.') as td:
                asm = Path(td) / 'out.s'
                run = subprocess.run(['nice', '-n', '15', str(cc / 'gcc'), '-B' + str(cc) + '/', '-S', *flags,
                                      '-I' + str(self.root / 'include'), '-w', str(self.root / tu), '-o', str(asm)],
                                     cwd=self.root, capture_output=True, text=True)
                if run.returncode:
                    raise ValueError(f'{tu}: compile failed: {run.stderr[-300:]}')
                text = asm.read_text(errors='replace')
            ccproc = self.root / 'tools/build/ccproc.py'
            names = self.root / 'config/names.tsv'
            if ccproc.is_file():
                args = [sys.executable, str(ccproc)] + (['--names-tsv', str(names)] if names.is_file() else [])
                proc = subprocess.run(args, cwd=self.root, input=text, capture_output=True, text=True)
                if proc.returncode == 0:
                    text = proc.stdout
            for name, lines in split_functions(text).items():
                merged[name if n == 0 else f'{name}@recipe{n}'] = lines
        return merged

    def __call__(self, tus):
        with ThreadPoolExecutor(self.jobs) as pool:
            return dict(zip(tus, pool.map(self.compile, tus)))


class Edits:
    """In-place text edits with guaranteed restoration."""

    def __init__(self, root):
        self.root, self.saved = Path(root), {}

    def write(self, rel, text):
        path = self.root / rel
        if rel not in self.saved:
            self.saved[rel] = path.read_bytes()
        path.write_text(text)

    def restore(self):
        for rel, data in self.saved.items():
            (self.root / rel).write_bytes(data)
        self.saved.clear()

    def __enter__(self):
        return self

    def __exit__(self, *exc):
        self.restore()


def field_users(root, header, field, tus=None):
    """(TUs that use the field, headers that use it) among the include closure of `header`."""
    root = Path(root)
    uses = re.compile(r'(?:->|\.)\s*' + re.escape(field) + r'\b')
    if tus is None:
        from layout_dependencies import consumer_paths, include_parents
        closure = consumer_paths(root, {header}, parents=include_parents(root))
    else:
        closure = set(tus) | {header}
    sources, headers = [], []
    for rel in sorted(closure):
        path = root / rel
        if path.suffix in ('.c', '.h') and path.is_file() and uses.search(path.read_text(errors='replace')):
            (sources if path.suffix == '.c' else headers).append(rel)
    return sources, headers


def relevant(root, sources, field, resolver):
    """TUs with at least one access of the named record's field (or one whose base type cannot be resolved)."""
    keep = []
    for rel in sources:
        statuses = {status for _, _, status in field_accesses((Path(root) / rel).read_text(), field, resolver)}
        if statuses & {'match', 'unresolved'}:
            keep.append(rel)
    return keep


def trial(root, spec, compile_tus, tus=None):
    """Run the opposite-sign trial; returns a result dict (see module doc)."""
    root = Path(root).resolve()
    header, owner, field = parse_spec(spec)
    text = (root / header).read_text()
    flipped_text, declared = flip_declaration(text, owner, field)
    target = CANON[FLIP[declared]]                    # the sign the flip declares
    spellings = SPELLINGS[target]
    sources, headers = field_users(root, header, field, tus)
    resolver = TypeIndex(root).resolver(owner)
    sources = relevant(root, sources, field, resolver)
    if not sources:
        return dict(spec=spec, declared=declared, flipped=FLIP[declared], status='no_tus', tus=[], functions=[],
                    casts_now=0, differing=0, recommendation='NO_TUS', unresolved=[])
    before = compile_tus(sources)
    stripped, texts, unresolved = {}, {}, []
    for rel in sorted(set(sources) | set(headers) | {header}):
        skipped = []
        new, count = strip_casts(flipped_text if rel == header else (root / rel).read_text(), spellings, field,
                                 resolver, skipped)
        unresolved += [dict(file=rel, line=line, base=base) for line, base in skipped]
        texts[rel] = new
        if count:
            stripped[rel] = count
    with Edits(root) as edits:
        for rel, new in texts.items():
            edits.write(rel, new)
        after = compile_tus(sources)
    functions, differing = [], 0
    for tu in sources:
        changed = {name: delta for name, delta in diff_functions(before[tu], after[tu])}
        for name in sorted(before[tu]):
            functions.append(dict(tu=tu, function=name, status='differs' if name in changed else 'identical',
                                  delta=changed.get(name, [])))
        differing += len(changed)
    casts_now = sum(stripped.values())
    if differing == 0 and casts_now:
        recommendation = 'FLIP_CLEAN'
    elif differing == 0:
        recommendation = 'TIE'          # nothing to strip and nothing changes: neutral
    elif differing < casts_now:
        recommendation = 'FLIP_BETTER'
    elif differing == casts_now:
        recommendation = 'TIE'
    else:
        recommendation = 'KEEP'
    return dict(spec=spec, declared=declared, flipped=FLIP[declared], status='ok', tus=sources,
                stripped=stripped, unresolved=unresolved, casts_now=casts_now, differing=differing,
                functions=functions,
                recommendation=recommendation,
                recommended_type=FLIP[declared] if recommendation in ('FLIP_CLEAN', 'FLIP_BETTER') else declared)


WRITE_AFTER = re.compile(r'\s*(?:=(?!=)|\+\+|--|[-+*/%&|^]=|<<=|>>=)')


def function_spans(text):
    """{function name: (start, end)} of the function definitions in a C text (end = its closing brace)."""
    spans = {}
    for m in FUNCTION_HEAD.finditer(text):
        name = re.search(r'([A-Za-z_]\w*)\s*\(', m[0])
        depth, i = 0, m.end() - 1
        while i < len(text):
            depth += (text[i] == '{') - (text[i] == '}')
            if depth == 0:
                break
            i += 1
        if name:
            spans[name[1]] = (m.start(), i)
    return spans


_NAMES = {}


def source_name(root, label, spans):
    """The C name in `spans` of an asm function label: ccproc writes renamed functions back under their
    func_<addr> label (config/names.tsv), so a label may name a function the source calls otherwise."""
    if label in spans:
        return label
    key = str(root)
    if key not in _NAMES:
        table = collections.defaultdict(set)
        path = Path(root) / 'config/names.tsv'
        if path.is_file():
            for line in path.read_text(errors='replace').splitlines():
                cols = line.split('\t')
                if len(cols) >= 3 and not line.startswith('#'):
                    table[cols[1]].add(cols[2])
        _NAMES[key] = table
    found = [name for name in _NAMES[key].get(label, ()) if name in spans]
    return found[0] if len(found) == 1 else None


def read_sites(text, field, resolver, span=None):
    """Offsets where a value cast can go in front of a read of the named record's field: matching accesses
    that are not a store target, an increment or an address, and carry no 8/16-bit cast yet."""
    access = re.compile(r'(?:->|\.)\s*' + re.escape(field) + r'\b')
    sites = []
    for offset, base, status in field_accesses(text, field, resolver):
        if status != 'match' or (span and not span[0] <= offset < span[1]):
            continue
        end = access.match(text, offset).end()
        if WRITE_AFTER.match(text, end) or re.match(r'\s*(?:->|\.|\[|\()', text[end:end + 8]):
            continue
        start = base_before(text, offset)
        before = text[:start].rstrip()
        if before.endswith(('++', '--')) or (before.endswith('&') and not before.endswith('&&')):
            continue
        if CAST_BEFORE.search(before[-48:]):
            continue
        sites.append(start)
    return sites


def place(root, spec, compile_tus, tus=None, apply=False, log=None):
    """Flip the declaration, strip every 8/16-bit value cast of either sign on the field, then for each
    function whose code differs restore its old meaning (each read without a cast takes a cast to the old
    declared type, casts to the new type go, casts to the old type stay) and prune the old-type casts one
    at a time while the function's code stays identical.  Returns the casts the flipped
    declaration needs; with `apply` the flipped tree stays written (only when every function is identical)."""
    root = Path(root).resolve()
    header, owner, field = parse_spec(spec)
    text = (root / header).read_text()
    flipped_text, declared = flip_declaration(text, owner, field)
    old, new = CANON[declared], CANON[FLIP[declared]]
    sources, headers = field_users(root, header, field, tus)
    resolver = TypeIndex(root).resolver(owner)
    sources = relevant(root, sources, field, resolver)
    say = log or (lambda *a: None)
    if not sources:
        return dict(spec=spec, declared=declared, flipped=FLIP[declared], status='no_tus', placed=[], unresolved=[])
    baseline = compile_tus(sources)
    texts, counts, originals = {}, collections.Counter(), {}
    for rel in sorted(set(sources) | set(headers) | {header}):
        originals[rel] = (root / rel).read_text()
        current = flipped_text if rel == header else originals[rel]
        for kind in (new, old):
            current, n = strip_casts(current, SPELLINGS[kind], field, resolver)
            counts[kind] += n
        texts[rel] = current
    edits = Edits(root)
    placed, unresolved = [], []
    try:
        for rel, body in texts.items():
            edits.write(rel, body)
        after = compile_tus(sources)
        for tu in sources:
            differing = [name for name, _ in diff_functions(baseline[tu], after[tu])]
            if not differing:
                continue
            say(f'{tu}: {len(differing)} differing: {", ".join(differing)}')

            def same(name, body):
                edits.write(tu, body)
                code = compile_tus([tu])[tu]
                return code.get(name) == baseline[tu].get(name), code
            for name in differing:
                # the function as it was, its uncast reads cast to the old type and its casts to the new
                # type stripped: the old code, spelled for the flipped declaration
                cast = '(' + old + ')'
                orig = originals[tu]
                cname = source_name(root, name, function_spans(orig))
                ospan = function_spans(orig).get(cname)
                span = function_spans(texts[tu]).get(cname)
                if ospan is None or span is None:
                    unresolved.append(dict(tu=tu, function=name, reads=0))
                    continue
                sites = read_sites(orig, field, resolver, ospan)
                for at in sorted(sites, reverse=True):
                    orig = orig[:at] + cast + orig[at:]
                orig, _ = strip_casts(orig, SPELLINGS[new], field, resolver)
                fspan = function_spans(orig)[cname]
                body = texts[tu][:span[0]] + orig[fspan[0]:fspan[1] + 1] + texts[tu][span[1] + 1:]
                ok, _ = same(name, body)
                if not ok:
                    unresolved.append(dict(tu=tu, function=name, reads=len(sites)))
                    edits.write(tu, texts[tu])
                    continue
                # prune: drop each added cast while the function stays identical
                index = 0
                while True:
                    added = cast_sites(body, cast, field, resolver, function_spans(body).get(cname))
                    if index >= len(added):
                        break
                    at = added[index]
                    trial_body = body[:at] + body[at + len(cast):]
                    ok, _ = same(name, trial_body)
                    if ok:
                        body = trial_body
                    else:
                        index += 1
                texts[tu] = body
                edits.write(tu, body)
                kept = cast_sites(body, cast, field, resolver, function_spans(body).get(cname))
                for at in kept:
                    placed.append(dict(tu=tu, function=name, line=line_of(body, at),
                                       text=body[at:body.find('\n', at)].strip()[:100]))
                say(f'  {name}: {len(kept)} cast(s) needed of {len(sites)} read(s)')
        final = compile_tus(sources)
        still = [(tu, name) for tu in sources for name, _ in diff_functions(baseline[tu], final[tu])]
    finally:
        if not apply:
            edits.restore()
    if apply and (still or unresolved):
        edits.restore()
    return dict(spec=spec, declared=declared, flipped=FLIP[declared], status='ok', tus=sources,
                stripped=dict(counts), placed=placed, unresolved=unresolved,
                still_differing=[f'{tu}:{name}' for tu, name in still],
                applied=bool(apply and not still and not unresolved))


def cast_sites(body, cast, field, resolver, span):
    """Offsets of the `cast` texts that sit directly on a read of the named record's field inside `span`."""
    starts = {base_before(body, offset) for offset, _, status in field_accesses(body, field, resolver)
              if status == 'match'}
    return [m.start() for m in re.finditer(re.escape(cast), body)
            if (not span or span[0] <= m.start() < span[1]) and m.end() in starts]


def format_place(result):
    lines = [f"{result['spec']}: declared {result['declared']}, placed under {result['flipped']}"]
    if result['status'] != 'ok':
        return lines[0] + '\n  no TU uses the field'
    lines.append(f"  TUs {len(result['tus'])}; casts stripped {result['stripped']}; casts the flip needs "
                 f"{len(result['placed'])}; unresolved functions {len(result['unresolved'])}; "
                 f"still differing {len(result['still_differing'])}")
    for row in result['placed']:
        lines.append(f"  needs   {row['tu']}:{row['line']} ({row['function']}) {row['text']}")
    for row in result['unresolved']:
        lines.append(f"  UNRESOLVED {row['tu']} {row['function']} (the old meaning with {row['reads']} added casts is not identical)")
    for row in result['still_differing']:
        lines.append(f"  STILL   {row}")
    if 'applied' in result:
        lines.append(f"  applied: {result['applied']}")
    return '\n'.join(lines)


def check_removal(root, spec, compile_tus, tus=None, identity=False, stores=False):
    """Remove each value cast to the type opposite the declaration alone; report NEEDED or NO-OP per cast.
    With `identity`, casts to the declared type itself (`(s16)` on a short field) are checked too; with
    `stores`, 8/16-bit casts on the whole stored value of a plain store to the field."""
    root = Path(root).resolve()
    header, owner, field = parse_spec(spec)
    declared = field_declaration((root / header).read_text(), owner, field)[1]
    kinds = [('opposite', SPELLINGS[CANON[FLIP[declared]]])]     # casts to the sign the declaration does not have
    if identity:
        kinds.append(('identity', SPELLINGS[CANON[declared]]))
    if stores:
        kinds.append(('store', None))
    sources, headers = field_users(root, header, field, tus)
    resolver = TypeIndex(root).resolver(owner)
    sources = relevant(root, sources, field, resolver)
    sites, unresolved = [], []
    for rel in sources + [h for h in headers if h not in sources]:
        text = (root / rel).read_text()
        for kind, spellings in kinds:
            matching = 0
            found = store_casts(text, field, resolver) if spellings is None else field_casts(text, spellings, field, resolver)
            for start, length, base, status in found:
                if status == 'unresolved' and kind == 'opposite':
                    unresolved.append(dict(file=rel, line=line_of(text, start), base=base))
                if status == 'match':
                    sites.append((rel, kind, spellings, matching, line_of(text, start), text[start:start + length].strip()))
                    matching += 1
    baseline = compile_tus(sources) if sources else {}
    rows = []
    for rel, kind, spellings, index, line, cast in sites:
        affected = [tu for tu in sources if tu == rel] if rel.endswith('.c') else sources
        with Edits(root) as edits:
            edits.write(rel, remove_one_cast((root / rel).read_text(), spellings, field, index, resolver))
            after = compile_tus(affected)
        changed = [(tu, name) for tu in affected for name, _ in diff_functions(baseline[tu], after[tu])]
        rows.append(dict(file=rel, line=line, cast=cast, kind=kind, verdict='NEEDED' if changed else 'NO-OP',
                         functions=sorted({name for _, name in changed})))
    rows.sort(key=lambda r: (r['file'], r['line']))
    return dict(spec=spec, declared=declared, casts=rows, unresolved=unresolved,
                noops=sum(1 for r in rows if r['verdict'] == 'NO-OP'))


def format_trial(result):
    lines = [f"{result['spec']}: declared {result['declared']}, trial {result['flipped']}"]
    if result['status'] != 'ok':
        lines.append('  no TU uses the field')
        return '\n'.join(lines)
    lines.append(f"  TUs {len(result['tus'])}; casts to {result['flipped']} now {result['casts_now']} "
                 f"({', '.join(f'{k} {v}' for k, v in sorted(result['stripped'].items())) or 'none'}); "
                 f"functions differing with {result['flipped']} and no casts {result['differing']}")
    for row in result['functions']:
        if row['status'] == 'differs':
            lines.append(f"  differs   {row['tu']} {row['function']}: {' | '.join(row['delta'])}")
    if result.get('unresolved'):
        lines.append(f"  unresolved base types (casts left alone): {len(result['unresolved'])}: "
                     + ', '.join(f"{u['file']}:{u['line']} {u['base']}" for u in result['unresolved'][:6]))
    identical = sum(1 for r in result['functions'] if r['status'] == 'identical')
    lines.append(f'  identical functions {identical}')
    lines.append(f"  recommendation: {result['recommendation']} -> declare {result['recommended_type']}")
    return '\n'.join(lines)


def format_removal(result):
    lines = [f"{result['spec']}: declared {result['declared']}, {len(result['casts'])} casts checked"]
    for row in result['casts']:
        lines.append(f"  {row['verdict']:7} {row['file']}:{row['line']} {row['cast']}"
                     + (f" {row['kind']}" if row.get('kind') in ('identity', 'store') else '')
                     + (f" ({', '.join(row['functions'])})" if row['functions'] else ''))
    if result.get('unresolved'):
        lines.append(f"  unresolved base types (skipped): {len(result['unresolved'])}: "
                     + ', '.join(f"{u['file']}:{u['line']} {u['base']}" for u in result['unresolved'][:6]))
    lines.append(f"  no-ops {result['noops']}")
    return '\n'.join(lines)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('field', help='include/x.h::Record.field')
    parser.add_argument('--root', type=Path, default=HERE.parents[1], help='private tree edited in place and restored')
    parser.add_argument('--build-root', type=Path, help='tree holding build/.state and toolchain/ (default --root)')
    parser.add_argument('--tu', action='append', help='explicit TUs instead of the include-closure users of the field')
    parser.add_argument('--check-removal', action='store_true')
    parser.add_argument('--place', action='store_true',
                        help='flip, strip both signs\' casts on the field and place the casts the flip needs '
                             '(pruned greedily one cast at a time, so the count is an upper bound)')
    parser.add_argument('--apply', action='store_true', help='with --place: leave the flipped tree written when clean')
    parser.add_argument('--identity', action='store_true',
                        help='with --check-removal: also check casts to the declared type itself')
    parser.add_argument('--stores', action='store_true',
                        help='with --check-removal: also check casts on the whole stored value of plain stores')
    parser.add_argument('--jobs', type=int, default=2, help='parallel compiles (at most 2)')
    parser.add_argument('--json', type=Path, help='write the result here')
    parser.add_argument('--fail-flip', action='store_true', help='exit 1 when the opposite sign is recommended')
    args = parser.parse_args(argv)
    compiler = RecipeCompiler(args.root, args.build_root, args.jobs)
    try:
        if args.place:
            result = place(args.root, args.field, compiler, args.tu, apply=args.apply,
                           log=lambda *a: print(*a, file=sys.stderr, flush=True))
            print(format_place(result))
        elif args.check_removal:
            result = check_removal(args.root, args.field, compiler, args.tu, identity=args.identity,
                                   stores=args.stores)
            print(format_removal(result))
        else:
            result = trial(args.root, args.field, compiler, args.tu)
            print(format_trial(result))
    except (OSError, ValueError) as error:
        parser.error(str(error))
    for note in sorted(set(compiler.notes)):
        print('note: ' + note, file=sys.stderr)
    if args.json:
        args.json.write_text(json.dumps(result, indent=1) + '\n')
    flip = not (args.check_removal or args.place) and result['recommendation'] in ('FLIP_CLEAN', 'FLIP_BETTER')
    return 1 if args.fail_flip and flip else 0


if __name__ == '__main__':
    sys.exit(main())
