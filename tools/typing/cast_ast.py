#!/usr/bin/env python3
"""Shared Clang front end for the pointer-cast tools (cast_fold.py, view_swap.py).

One physical TU is parsed with the mipsel Clang used by field_census (pointers are 4 bytes, layouts are the
PS1 ones).  The JSON AST gives exact expression types and source ranges; `-fdump-record-layouts-complete`
gives every laid-out record *with its nested members* at absolute offsets.  Nothing is compiled for the PS1
here and nothing is written: callers plan text edits and must prove complete-TU identity before keeping them.
"""
from __future__ import annotations

from contextlib import contextmanager
import json
from pathlib import Path
import re
import sys
import tempfile

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent)]
import field_census as C  # noqa: E402

# Spellings gcc treats as the same type (same mode and signedness); char stays distinct from signed char.
SCALAR_ALIAS = {
    'signed short': 'short', 'short int': 'short', 'signed short int': 'short',
    'unsigned short int': 'unsigned short', 'signed int': 'int', 'signed': 'int', 'long': 'int',
    'long int': 'int', 'signed long': 'int', 'unsigned': 'unsigned int', 'unsigned long': 'unsigned int',
    'unsigned long int': 'unsigned int',
}
BYTE_POINTEES = {'unsigned char', 'signed char', 'char'}
LAYOUT_LINE = re.compile(r'^\s*(-?\d+)(?::(\d+)-(\d+))? \| (\s*)(.*)$')
SIZE_LINE = re.compile(r'\[sizeof=(\d+), (?:dsize=\d+, )?align=(\d+)')
ARRAY = re.compile(r'^(.*?)\s*\[(\d+)\]$')


def parse_nested_layouts(text):
    """`-fdump-record-layouts-complete` -> {record key: {'size', 'kind', 'kids': [node]}}.

    A node is {'off': absolute offset in the dumped record, 'type': spelling, 'name': member name or ''
    for an anonymous member, 'bits': bool, 'kids': [nested nodes]}."""
    out = {}
    for block in text.split('*** Dumping AST Record Layout')[1:]:
        lines = [line for line in block.splitlines() if line.strip()]
        if not lines:
            continue
        head = LAYOUT_LINE.match(lines[0])
        if not head:
            continue
        base = len(head.group(4))
        title = head.group(5).strip()
        kind = title.split(' ', 1)[0]
        key = C.record_key(title.split('::')[-1] if '::(' in title else title)
        rec = {'kind': kind, 'kids': []}
        stack = [(base, rec)]
        for line in lines[1:]:
            s = SIZE_LINE.search(line)
            if s:
                rec['size'], rec['align'] = int(s.group(1)), int(s.group(2))
                continue
            m = LAYOUT_LINE.match(line)
            if not m:
                continue
            indent = len(m.group(4))
            body = m.group(5).rstrip()
            name = body.rsplit(' ', 1)[-1] if ' ' in body else ''
            if name.endswith(')') or not re.match(r'^[A-Za-z_]\w*$', name):
                name, ftype = '', body       # anonymous struct/union member
            else:
                ftype = body[:len(body) - len(name)].strip()
            node = {'off': int(m.group(1)), 'type': ftype, 'name': name, 'bits': m.group(2) is not None, 'kids': []}
            while stack and stack[-1][0] >= indent:
                stack.pop()
            if not stack:
                break
            stack[-1][1]['kids'].append(node)
            stack.append((indent, node))
        out.setdefault(key, rec)
    return out


class Unit:
    """One parsed physical TU: AST, typedefs, nested layouts and source texts."""

    def __init__(self, root, rel, tree, layout_text):
        self.root = Path(root)
        self.rel = rel
        self.tree = tree
        self.layouts = parse_nested_layouts(layout_text)
        C.annotate(tree)
        self.typedefs = {}
        self.record_files = {}
        anon = {}
        for d in tree.get('inner', []):
            k = d.get('kind')
            if k == 'TypedefDecl':
                self.typedefs[d['name']] = C.qtype(d)
                inner = (d.get('inner') or [{}])[0]
                owned = inner.get('ownedTagDecl')
                if owned and not owned.get('name') and owned.get('id') in anon:
                    akey = anon[owned['id']]
                    if akey in self.layouts:
                        self.layouts.setdefault(d['name'], self.layouts[akey])
                    self.record_files.setdefault(d['name'], akey[1:].split(':')[0])
            elif k == 'RecordDecl' and d.get('completeDefinition'):
                if d.get('name'):
                    self.record_files.setdefault(d['name'], d.get('_f') or '')
                else:
                    anon[d['id']] = '@%s:%s:%s' % (d.get('_f'), d.get('_l'), (d.get('loc') or {}).get('col'))
        for key in self.layouts:
            if key.startswith('@'):
                self.record_files.setdefault(key, key[1:].split(':')[0])
        flat = {key: {'size': lay.get('size'), 'fields': {}} for key, lay in self.layouts.items()}
        self.T = C.Types(self.typedefs, flat, self.record_files)
        self.texts = {}

    # ------------------------------------------------------------------ text
    def text(self, file):
        if file not in self.texts:
            try:
                self.texts[file] = (self.root / file).read_text()
            except OSError:
                self.texts[file] = ''
        return self.texts[file]

    def functions(self, files=None):
        """(file, FunctionDecl) for every function body located in `files` (all when None)."""
        for d in self.tree.get('inner', []):
            if d.get('kind') != 'FunctionDecl':
                continue
            if not any(x.get('kind') == 'CompoundStmt' for x in d.get('inner', [])):
                continue
            f = d.get('_f') or self.rel
            if files is None or f in files:
                yield f, d

    # ------------------------------------------------------------------ types
    def canon(self, t):
        """Canonical scalar/pointer spelling: typedefs expanded, gcc-equivalent integer spellings merged."""
        r = self.T.resolve(t)
        stars = len(r) - len(r.rstrip('*'))
        core = r.rstrip('*')
        return SCALAR_ALIAS.get(core, core) + '*' * stars

    def volatile(self, t, depth=0):
        """True when the object type itself (not a pointee) is volatile-qualified, through typedefs."""
        t = (t or '').strip()
        if depth > 20:
            return False
        if t.endswith('*'):
            return False
        if re.search(r'\bvolatile\b', t):
            return True
        bare = re.sub(r'\b(?:const|volatile)\b', '', t).strip()
        return bare in self.typedefs and self.volatile(self.typedefs[bare], depth + 1)

    def record_of_pointer(self, t):
        """Record key when t is (a typedef of) a pointer to a complete struct/union, else None."""
        r = self.T.resolve(t)
        if not r.endswith('*') or r.endswith('**'):
            return None
        core = r[:-1]
        if not core.startswith('rec:'):
            return None
        key = core[4:]
        return key if key in self.layouts and self.layouts[key].get('size') else None

    def size(self, t):
        return self.T.size(t)

    def is_byte_pointer(self, t):
        r = self.T.resolve(t)
        return r.endswith('*') and not r.endswith('**') and r[:-1] in BYTE_POINTEES

    # ------------------------------------------------------------------ fields
    def leaves_at(self, key, off, depth=0):
        """Every member access path reaching byte offset `off` of record `key`.

        Yields (path, type spelling, node) where path is the C member path (`a.b[2].c`), outermost first:
        aggregates are yielded before their own members, so a caller wanting an exact scalar match tests
        each candidate's type.  Bit-fields are never yielded."""
        lay = self.layouts.get(key)
        if not lay or depth > 8 or off < 0 or off >= (lay.get('size') or 0):
            return
        for node in lay['kids']:
            yield from self._collect(node, off, '', 0, depth)

    def _collect(self, node, off, prefix, shift, depth):
        name = node['name']
        path = (prefix + '.' + name if prefix else name) if name else prefix
        start = node['off'] - shift
        t = node['type']
        if node['bits']:
            return
        size = self.size(t)
        if size is None or not (start <= off < start + size):
            return
        m = ARRAY.match(t.strip())
        if m:
            elem = m.group(1)
            esize = self.size(elem)
            if not esize or not path:
                return
            index, rel = divmod(off - start, esize)
            epath = '%s[%d]' % (path, index)
            ekey = self.T.record(elem) if not self.T.resolve(elem).endswith('*') else None
            if ekey:
                if rel == 0:
                    yield epath, elem, node
                for p, lt, n in self.leaves_at(ekey, rel, depth + 1):
                    yield epath + '.' + p, lt, n
            elif rel == 0:
                yield epath, elem, node
            return
        rkey = self.T.record(t) if not self.T.resolve(t).endswith('*') else None
        if rkey:
            if off == start and path:
                yield path, t, node
            if node['kids']:
                for kid in node['kids']:
                    yield from self._collect(kid, off, path, shift, depth)
            else:
                for p, lt, n in self.leaves_at(rkey, off - start, depth + 1):
                    yield (path + '.' + p if path else p), lt, n
            return
        if off == start and path:
            yield path, t, node


def clang_unit(root, rel, recipe=None):
    """Parse one physical TU (generated SLUS partitions through their registered compilation input)."""
    root = Path(root).resolve()

    def run(source):
        rc, out, err = C.clang_run(root, str(source), ['-Xclang', '-ast-dump=json'])
        if not out.strip():
            return None, (err.strip().splitlines() or ['no output'])[-1][:300]
        _, lay, _ = C.clang_run(root, str(source), ['-Xclang', '-fdump-record-layouts-complete'])
        return Unit(root, rel, json.loads(out), lay), (None if rc == 0 else (err.strip().splitlines() or [''])[-1][:300])

    if recipe and 'slus_unit' in recipe:
        import layout_compile_identity as L
        (root / 'build_ovl').mkdir(exist_ok=True)
        with tempfile.TemporaryDirectory(prefix='cast-ast-', dir=root / 'build_ovl') as td:
            with L.compilation_input(root, rel, recipe, Path(td)) as source:
                return run(source)
    return run(rel)


def member_offset(unit, key, name):
    """Byte offset of member `name` (searching through anonymous members) of record `key`."""
    lay = unit.layouts.get(key)
    if not lay or not name:
        return None
    stack = list(lay['kids'])
    while stack:
        node = stack.pop(0)
        if node['name'] == name and not node['bits']:
            return node['off']
        if not node['name']:
            stack.extend(node['kids'])
    return None


# ---------------------------------------------------------------------- expression helpers

def kids(e):
    return e.get('inner') or []


def strip_parens(e):
    while e and e.get('kind') == 'ParenExpr' and kids(e):
        e = kids(e)[0]
    return e


def strip_implicit(e):
    while e and e.get('kind') in ('ParenExpr', 'ImplicitCastExpr') and kids(e):
        e = kids(e)[0]
    return e


def in_macro(e):
    """True when any part of the node's range comes from a macro expansion."""
    rng = e.get('range') or {}
    return any('spellingLoc' in (rng.get(k) or {}) or 'expansionLoc' in (rng.get(k) or {}) for k in ('begin', 'end'))


def node_range(e, text):
    """(start, end) character offsets of a node outside macros, else None."""
    if in_macro(e):
        return None
    rng = e.get('range') or {}
    a, b = rng.get('begin') or {}, rng.get('end') or {}
    if 'offset' not in a or 'offset' not in b:
        return None
    start, end = a['offset'], b['offset'] + b.get('tokLen', 1)
    if not text.isascii():
        encoded = text.encode()
        start = len(encoded[:start].decode(errors='replace'))
        end = len(encoded[:end].decode(errors='replace'))
    return start, end


PURE_KINDS = {'DeclRefExpr', 'MemberExpr', 'ParenExpr', 'ImplicitCastExpr', 'IntegerLiteral', 'ArraySubscriptExpr'}


def pure(e):
    """Side-effect free and cast free (a pointer-valued name, member chain or constant subscript)."""
    stack = [e]
    while stack:
        x = stack.pop()
        k = x.get('kind')
        if k not in PURE_KINDS and not (k == 'UnaryOperator' and x.get('opcode') in ('&', '*')):
            return False
        stack.extend(kids(x))
    return True


def balanced(text):
    """True when every parenthesis in text closes inside it (so `(text)` is one group)."""
    depth = 0
    for ch in text:
        depth += ch == '('
        depth -= ch == ')'
        if depth < 0:
            return False
    return depth == 0


POSTFIX_KINDS = {'DeclRefExpr', 'MemberExpr', 'ArraySubscriptExpr', 'ParenExpr', 'CallExpr'}


def walk(node, parent=None):
    """(node, parent) pairs in document order."""
    stack = [(node, parent)]
    while stack:
        x, p = stack.pop()
        if not isinstance(x, dict):
            continue
        yield x, p
        for k in reversed(kids(x)):
            stack.append((k, x))
