#!/usr/bin/env python3
"""Declarations and call sites of one physical TU from `clang -Xclang -ast-dump=json`.

    ast_facts.py src/dungeon/func_80FE16A8.c [--root R]      print the facts as JSON

Uses the tree's clang front end (tools/typing/field_census.CLANG_ARGS: mipsel target, -I include) and
keeps the JSON in memory only.  Per TU:

  decls  every function declaration/definition and extern data declaration in src/ and include/
         files: name, kind (proto | def | data), file, line, col, signature (as written at the site:
         return text + ParmVarDecl types; `()` kept for unprototyped sites), composite (clang's type of
         the redeclaration, merged with earlier visible declarations), canonical (desugared composite),
         ret, params, nparams, variadic, has_proto, storage, local (declared inside a function body)
  calls  every direct call: caller, callee, file, line, col, nargs, arg_types (source expression
         types, implicit conversions stripped), param_types, callee_type
         (the declaration visible at the site; param_types are its parameters), ret_use (ignored | assigned:T | init:T | cast:T |
         compared | cond | returned | arg | arith | deref | value | conv:T+... )

clang's JSON elides `file`/`line` when unchanged since the previously printed location, so the walk
tracks them in document order (loc, then range, spelling before expansion).
"""
from __future__ import annotations

import argparse
import json
import os
import re
from pathlib import Path
import subprocess
import sys

TYPING = Path(__file__).resolve().parents[1] / 'typing'
CLANG = os.environ.get('FIELD_CENSUS_CLANG', 'clang')
CLANG_ARGS = ['--target=mipsel-unknown-none', '-fsyntax-only', '-w', '-ferror-limit=0', '-Wno-everything']
FN_RETURNING_FN = re.compile(r'^(.*?)\(\*\((.*)\)\)\((.*)\)$')
COMPARE = {'==', '!=', '<', '>', '<=', '>='}
LOGIC = {'&&', '||'}


def clang_json(root, rel, headers=None):
    """(AST, error); `headers` (a list) receives the include closure clang reports with -H."""
    cmd = [CLANG, *CLANG_ARGS, '-I', 'include', '-H', '-Xclang', '-ast-dump=json', rel]
    res = subprocess.run(cmd, cwd=root, capture_output=True)
    err = []
    for line in res.stderr.decode('utf-8', 'replace').splitlines():
        stripped = line.lstrip('.')
        if stripped != line and stripped.startswith(' ') and headers is not None:
            headers.append(os.path.normpath(stripped.strip()))
        elif line.strip():
            err.append(line)
    if not res.stdout.strip():
        return None, (err or ['no output'])[-1][:300]
    return json.loads(res.stdout), ((err or [''])[-1][:300] if res.returncode else None)


def split_function_type(qual):
    """'s32 (s32, void *)' -> ('s32', ['s32', 'void *'], variadic, has_proto)."""
    m = FN_RETURNING_FN.match(qual)
    if m:   # 'void (*(s32))(void)': a function returning a function pointer
        ret, params, variadic, has_proto = split_function_type(m.group(1) + 'F(' + m.group(2) + ')')
        return m.group(1) + '(*)(' + m.group(3) + ')', params, variadic, has_proto
    depth, cut = 0, None
    # The parameter list is the last top-level parenthesised group.
    for i in range(len(qual) - 1, -1, -1):
        c = qual[i]
        if c == ')':
            depth += 1
        elif c == '(':
            depth -= 1
            if depth == 0:
                cut = i
                break
    if cut is None:
        return qual, [], False, True
    ret, inner = qual[:cut].strip(), qual[cut + 1:-1].strip()
    params, depth, cur = [], 0, ''
    for c in inner:
        if c in '([':
            depth += 1
        elif c in ')]':
            depth -= 1
        if c == ',' and depth == 0:
            params.append(cur.strip())
            cur = ''
        else:
            cur += c
    if cur.strip():
        params.append(cur.strip())
    variadic = bool(params) and params[-1] == '...'
    if variadic:
        params = params[:-1]
    has_proto = not (inner == '')
    if params == ['void']:
        params = []
    return ret, params, variadic, has_proto


IDENT = re.compile(r'(?<!struct )(?<!union )(?<!enum )\b[A-Za-z_]\w*\b')   # not a tag name
STORAGE = re.compile(r'\b(?:extern|static|inline|__inline__|__inline|register)\b|__attribute__\s*\(\(.*?\)\)')


class Walker:
    def __init__(self, keep, root=None):
        self.file = None
        self.line = None
        self.keep = keep          # predicate on file path
        self.root = Path(root) if root else None
        self.texts = {}
        self.begin = None
        self.typedefs = {}
        self.decls, self.calls = [], []

    def desugar(self, text, depth=0):
        """Replace typedef names by their underlying types (to a fixpoint) — the type-level spelling."""
        if not text or depth > 8:
            return text
        out = IDENT.sub(lambda m: self.typedefs.get(m.group(0), m.group(0)), text)
        return out if out == text else self.desugar(out, depth + 1)

    def text(self, name):
        if name not in self.texts:
            try:
                self.texts[name] = (self.root / name).read_bytes() if self.root else None
            except OSError:
                self.texts[name] = None
        return self.texts[name]

    def spelled(self, node, pos, merged):
        """(signature as written at this site, has_proto, ret, params).

        clang prints a redeclaration's type as the composite with earlier declarations (`f()` after
        `f(s32)` prints `(s32)`; `X *` after `struct X *` prints `struct X *`), so the site's own spelling
        comes from its ParmVarDecl types and the source text between the declaration start and its name."""
        m_ret, m_params, variadic, _ = split_function_type(merged)
        # An unprototyped redeclaration gets implicit ParmVarDecls copied from the composite type.
        parms = [c for c in node.get('inner', ()) if c.get('kind') == 'ParmVarDecl' and not c.get('isImplicit')]
        params = [c.get('type', {}).get('qualType', '?') for c in parms]
        ret, has_proto = m_ret, True
        blob = self.text(pos[0]) if pos and pos[3] is not None else None
        if blob is not None and self.begin and self.begin[0] == pos[0] and self.begin[3] is not None:
            head = blob[self.begin[3]:pos[3]].decode('utf-8', 'replace')
            head = re.sub(r'\s+', ' ', STORAGE.sub(' ', head)).strip()
            if head and '(' not in head and ';' not in head and '{' not in head:
                ret = head
            tail = blob[pos[3] + (pos[4] or 0):pos[3] + (pos[4] or 0) + 64].decode('utf-8', 'replace')
            if not parms and re.match(r'\s*\(\s*\)', tail):
                has_proto = False
        if not parms and has_proto and m_params and blob is None:
            params = m_params          # no source text: fall back to the composite parameters
        inner = ', '.join(params + (['...'] if variadic else [])) or ('void' if has_proto else '')
        return '%s (%s)' % (ret, inner), has_proto, ret, params, variadic

    def see(self, loc):
        if not loc:
            return None
        if 'spellingLoc' in loc or 'expansionLoc' in loc:
            self.see(loc.get('spellingLoc'))
            return self.see(loc.get('expansionLoc'))
        if 'file' in loc:
            self.file = os.path.normpath(loc['file'])   # 'include/x/../../src/y.h' -> 'src/y.h'
        if 'line' in loc:
            self.line = loc['line']
        return (self.file, self.line, loc.get('col'), loc.get('offset'), loc.get('tokLen'))

    def position(self, node):
        here = self.see(node.get('loc'))
        rng = node.get('range') or {}
        begin = self.see(rng.get('begin'))
        self.see(rng.get('end'))
        self.begin = begin
        return here if here and here[2] is not None else begin

    def walk(self, node, parents, function):
        pos = self.position(node)
        kind = node.get('kind')
        if kind == 'FunctionDecl' and not node.get('isImplicit'):
            self.function_decl(node, pos, function is not None)
            body = next((c for c in node.get('inner', ()) if c.get('kind') == 'CompoundStmt'), None)
            inner_fn = node.get('name') if body is not None else function
            for child in node.get('inner', ()):
                self.walk(child, parents + [node], inner_fn)
            return
        if kind == 'TypedefDecl' and node.get('name') and not node.get('isImplicit'):
            under = node.get('type', {}).get('qualType')
            if under and under != node['name'] and node['name'] not in IDENT.findall(under) \
                    and node['name'] not in ('struct', 'union', 'enum'):
                self.typedefs[node['name']] = under
        if kind == 'VarDecl' and node.get('storageClass') == 'extern':
            self.data_decl(node, pos, function is not None)
        if kind == 'CallExpr' and function is not None:
            self.call(node, pos, parents, function)
        for child in node.get('inner', ()):
            self.walk(child, parents + [node], function)

    def function_decl(self, node, pos, local):
        if not pos or not self.keep(pos[0]):
            return
        qual = node['type']['qualType']
        signature, has_proto, ret, params, variadic = self.spelled(node, pos, qual)
        body = any(c.get('kind') == 'CompoundStmt' for c in node.get('inner', ()))
        self.decls.append(dict(name=node['name'], kind='def' if body else 'proto', file=pos[0], line=pos[1],
                               col=pos[2], signature=signature, composite=qual,
                               canonical=self.desugar(signature),
                               ret=ret, params=params, nparams=len(params), variadic=variadic,
                               has_proto=has_proto, storage=node.get('storageClass', ''), local=local))

    def data_decl(self, node, pos, local):
        if not pos or not self.keep(pos[0]):
            return
        qual = node['type']['qualType']
        self.decls.append(dict(name=node['name'], kind='data', file=pos[0], line=pos[1], col=pos[2],
                               signature=qual, composite=qual, canonical=self.desugar(qual), ret=None,
                               params=[], nparams=0, variadic=False, has_proto=True, storage='extern',
                               local=local))

    def call(self, node, pos, parents, function):
        inner = node.get('inner') or []
        if not inner:
            return
        callee = strip(inner[0])
        ref = callee.get('referencedDecl') if callee.get('kind') == 'DeclRefExpr' else None
        if not ref or ref.get('kind') != 'FunctionDecl':
            return
        args = inner[1:]
        self.calls.append(dict(
            caller=function, callee=ref['name'], file=pos[0] if pos else None, line=pos[1] if pos else None,
            col=pos[2] if pos else None, nargs=len(args),
            arg_types=[strip(a).get('type', {}).get('qualType') for a in args],
            param_types=split_function_type(ref.get('type', {}).get('qualType', ''))[1],
            callee_type=ref.get('type', {}).get('qualType'), ret_use=return_use(node, parents)))


def strip(node):
    while node.get('kind') in ('ImplicitCastExpr', 'ParenExpr') and node.get('inner'):
        node = node['inner'][0]
    return node


def return_use(node, parents):
    child, notes = node, []
    for parent in reversed(parents):
        kind = parent.get('kind')
        if kind == 'ParenExpr':
            child = parent
            continue
        if kind == 'ImplicitCastExpr':
            if parent.get('castKind') in ('IntegralCast', 'IntegralToBoolean', 'IntegralToPointer'):
                notes.append('conv:' + parent['type']['qualType'])
            child = parent
            continue
        inner = parent.get('inner') or []
        index = next((i for i, c in enumerate(inner) if c is child), -1)
        prefix = ''.join(n + '+' for n in notes)
        if kind == 'CStyleCastExpr':
            return 'ignored' if parent.get('castKind') == 'ToVoid' else prefix + 'cast:' + parent['type']['qualType']
        if kind == 'BinaryOperator':
            op = parent.get('opcode')
            if op == '=':
                return prefix + ('assigned:' + inner[0]['type']['qualType'] if index == 1 else 'lvalue')
            if op in COMPARE:
                return prefix + 'compared'
            if op in LOGIC:
                return prefix + 'cond'
            if op == ',':
                return 'ignored' if index == 0 else prefix + 'value'
            return prefix + 'arith'
        if kind == 'CompoundAssignOperator':
            return prefix + 'arith'
        if kind == 'VarDecl':
            return prefix + 'init:' + parent['type']['qualType']
        if kind == 'ReturnStmt':
            return prefix + 'returned'
        if kind == 'CallExpr':
            return prefix + 'arg'
        if kind == 'UnaryOperator':
            return prefix + ('cond' if parent.get('opcode') == '!' else 'arith')
        if kind in ('IfStmt', 'WhileStmt', 'SwitchStmt'):
            return prefix + 'cond' if index == 0 else 'ignored'
        if kind == 'DoStmt':
            return prefix + 'cond' if index == 1 else 'ignored'
        if kind == 'ForStmt':
            return prefix + 'cond' if index == 2 else 'ignored'
        if kind == 'ConditionalOperator':
            return prefix + ('cond' if index == 0 else 'value')
        if kind in ('MemberExpr', 'ArraySubscriptExpr'):
            return prefix + 'deref'
        if kind in ('CompoundStmt', 'CaseStmt', 'DefaultStmt', 'LabelStmt'):
            return 'ignored'
        if kind == 'InitListExpr':
            return prefix + 'init'
        return prefix + 'other:' + kind
    return 'ignored'


def unit_facts(root, rel, headers=None):
    """(decls, calls, error) of one TU; files outside src/ and include/ are skipped."""
    tree, error = clang_json(root, rel, headers)
    if tree is None:
        return [], [], error
    sys.setrecursionlimit(max(sys.getrecursionlimit(), 20000))
    walker = Walker(lambda f: f is not None and f.startswith(('src/', 'include/')), root)
    for child in tree.get('inner', ()):
        walker.walk(child, [tree], None)
    return walker.decls, walker.calls, error


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('tu')
    ap.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[2])
    args = ap.parse_args(argv)
    decls, calls, error = unit_facts(args.root, args.tu)
    print(json.dumps(dict(decls=decls, calls=calls, error=error), indent=1))
    return 0


if __name__ == '__main__':
    sys.exit(main())
