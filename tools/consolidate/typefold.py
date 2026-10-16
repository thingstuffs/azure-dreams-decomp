"""Conservative PS1 C view unification, independent of the historical lane drivers.

Only equal-size/equal-alignment views are eligible. Padding is a hole in a view,
not evidence of a field type. All non-padding, non-union leaves must have an
identically typed destination at the same offset. Union alternatives are checked
at each use; an unused alternative need not survive in the resolved type.
No casts between integer signs, pointer types, or qualifiers are invented.
"""
from __future__ import annotations
import ast
import hashlib
import json
import re
from dataclasses import dataclass, field
from pathlib import Path

LOCAL = re.compile(r"S_[0-9A-Fa-f]+_[0-9A-Za-z_]+$")
LEX = re.compile(r"[A-Za-z_]\w*|0[xX][0-9A-Fa-f]+|\d+|->|<<|>>|\+\+|--|==|!=|<=|>=|&&|\|\||[^\s]")
TRIVIA = re.compile(r'/\*.*?\*/|//[^\n]*|"(?:[^"\\]|\\.)*"|\'(?:[^\'\\]|\\.)*\'|^[ \t]*\#[^\n]*(?:\\\n[^\n]*)*', re.S | re.M)
ALIASES = {
    's8':'signed char', 'u8':'unsigned char', 's16':'short', 'u16':'unsigned short',
    's32':'int', 'u32':'unsigned int', 's64':'long long', 'u64':'unsigned long long',
    'f32':'float', 'f64':'double', 'signed':'int', 'signed int':'int',
    'unsigned':'unsigned int', 'short int':'short', 'signed short':'short',
    'signed short int':'short', 'unsigned short int':'unsigned short',
    'long int':'long', 'signed long':'long', 'signed long int':'long',
    'unsigned long int':'unsigned long', 'M2C_UNK':'int', 'M2C_UNK8':'signed char',
    'M2C_UNK16':'short', 'M2C_UNK32':'int', 'M2C_UNK64':'long long',
}
SIZES = {'char':1, 'signed char':1, 'unsigned char':1, 'short':2, 'unsigned short':2,
         'int':4, 'unsigned int':4, 'long':4, 'unsigned long':4, 'float':4,
         'long long':8, 'unsigned long long':8, 'double':8}

class Refuse(ValueError):
    pass


def mask(text):
    return TRIVIA.sub(lambda m: ''.join('\n' if c == '\n' else ' ' for c in m[0]), text)


def constant(text):
    """Integer constant expressions only; never eval repository text."""
    tree = ast.parse(text, mode='eval')
    def run(n):
        if isinstance(n, ast.Constant) and type(n.value) is int: return n.value
        if isinstance(n, ast.UnaryOp) and isinstance(n.op, (ast.UAdd, ast.USub)):
            v = run(n.operand); return v if isinstance(n.op, ast.UAdd) else -v
        if isinstance(n, ast.BinOp):
            a, b = run(n.left), run(n.right)
            if isinstance(n.op, ast.Add): return a+b
            if isinstance(n.op, ast.Sub): return a-b
            if isinstance(n.op, ast.Mult): return a*b
            if isinstance(n.op, ast.LShift) and 0 <= b < 32: return a << b
        raise Refuse('unsupported array bound: ' + text)
    n = run(tree.body)
    if not 0 <= n <= 65536: raise Refuse('array bound out of range')
    return n


def canon(text):
    words = re.findall(r'[A-Za-z_]\w*|\S', text)
    # Preserve qualifiers and function-pointer prototypes, including pointee types.
    for i, w in enumerate(words):
        if w not in ('unsigned', 'signed'): words[i] = ALIASES.get(w, w)
    s = ' '.join(words)
    quals = [q for q in ('const', 'volatile') if re.search(r'\b'+q+r'\b', s)]
    if '*' not in s and '(' not in s:
        s = re.sub(r'\b(const|volatile)\b', '', s)
        s = ' '.join(s.split()); s = ALIASES.get(s, s)
        return ' '.join(quals + [s])
    return s


@dataclass(eq=False)
class Type:
    kind: str
    name: str = ''
    size: int = 0
    align: int = 1
    fields: dict = field(default_factory=dict)  # name -> (offset, Type)
    elem: Type | None = None
    count: int = 0
    span: tuple | None = None
    header: str = ''

    def key(self):
        if self.kind == 'array': return ('array', self.count, self.elem.key())
        if self.kind in ('struct', 'union'):
            return (self.kind, self.size, self.align,
                    tuple((off, t.key()) for off, t in self.fields.values()))
        return (self.kind, self.name, self.size, self.align)


def pointer(ty, spelling=''):
    return Type('pointer', canon(spelling) if spelling else ty.name+' *', 4, 4, elem=ty)


def split_decls(body):
    depth = 0; start = 0
    for i, c in enumerate(body):
        if c in '{([': depth += 1
        elif c in '})]': depth -= 1
        elif c == ';' and depth == 0:
            yield body[start:i].strip(); start = i+1
    if body[start:].strip(): raise Refuse('unterminated member')


def brace_end(text, start):
    depth = 0
    for i in range(start, len(text)):
        if text[i] == '{': depth += 1
        elif text[i] == '}':
            depth -= 1
            if depth == 0: return i
    raise Refuse('unbalanced aggregate')


class Parser:
    def __init__(self, known=None):
        self.types = dict(known or {})
        self.errors = []
        self.duplicates = set()

    def base(self, spelling):
        spelling = ' '.join(spelling.split())
        if spelling in self.types: return self.types[spelling]
        if re.match(r'^(struct|union) ', spelling):
            return self.types.get(spelling, Type('opaque', spelling))
        c = canon(spelling); unqual = re.sub(r'\b(const|volatile)\s*', '', c)
        if unqual in SIZES:
            size = SIZES[unqual]
            # o32 PS1 aggregate ABI: double/long long have 8-byte alignment.
            return Type('scalar', c, size, size)
        return Type('opaque', c)

    def declaration(self, d):
        if re.search(r'\b(__attribute__|__declspec|packed|aligned)\b|:', d):
            raise Refuse('attributes or bitfields')
        m = re.fullmatch(r'(struct|union)\s*(\w*)\s*\{(.*)\}\s*(\w+)\s*(\[[^]]+\])?', d, re.S)
        if m:
            ty = self.body(m[1], m[3]); name, arr = m[4], m[5]
        else:
            fp = re.fullmatch(r'(.+?)\(\s*\*\s*(\w+)\s*\)\s*\((.*)\)', d)
            if fp:
                return fp[2], Type('pointer', canon(fp[1]+' (*)('+fp[3]+')'), 4, 4)
            m = re.fullmatch(r'((?:(?:const|volatile|unsigned|signed|struct|union|long|short)\s+)*[A-Za-z_]\w*)(?=\s|\*)\s*(\*\s*(?:(?:const|volatile)\s*)?(?:\*\s*)*)?\s*([A-Za-z_]\w*)\s*((?:\[[^]]+\]\s*)*)', d)
            if not m: raise Refuse('unsupported declaration: '+d[:100])
            base, stars, name, arr = m.groups(); ty = self.base(base)
            if stars:
                # Pointee spelling is retained: void* and int* are not interchangeable.
                for _ in range(stars.count('*')): ty = pointer(ty)
                ty.name = canon(base+' '+stars)
            elif ty.kind == 'opaque': raise Refuse('unknown by-value type: '+base)
        for bound in reversed(re.findall(r'\[([^]]+)\]', arr or '')):
            n = constant(bound)
            ty = Type('array', size=ty.size*n, align=ty.align, elem=ty, count=n)
        return name, ty

    def body(self, kind, body):
        ty = Type(kind); end = 0
        for d in split_decls(body):
            if not d: continue
            name, ft = self.declaration(d)
            if name in ty.fields: raise Refuse('duplicate member')
            off = 0 if kind == 'union' else (end+ft.align-1)//ft.align*ft.align
            ty.fields[name] = (off, ft)
            ty.align = max(ty.align, ft.align)
            end = max(end, off+ft.size)
        if not ty.fields: raise Refuse('empty aggregate')
        ty.size = (end+ty.align-1)//ty.align*ty.align
        return ty

    def parse(self, text, header=''):
        t = mask(text); pos = 0
        rx = re.compile(r'(typedef\s+)?\b(struct|union)\s*(\w*)\s*\{')
        while (m := rx.search(t, pos)):
            end = brace_end(t, m.end()-1)
            tail = re.match(r'\s*(\w+)?\s*;', t[end+1:]); pos = end+1
            if not tail:
                self.errors.append({'type': m[3] or '<anonymous>', 'reason': 'unsupported aggregate declarator/attribute', 'header': header})
                continue
            pos += tail.end()
            name = tail[1] if m[1] else None; tag = m[3]
            try:
                ty = self.body(m[2], t[m.end():end])
                if re.search(r'^\s*#\s*(?:if|elif|else|pragma)\b', text[m.end():end], re.M):
                    raise Refuse('conditional or pragma inside aggregate')
                ty.name = name or m[2]+' '+tag; ty.span = (m.start(), pos); ty.header = header
                if name and not header and LOCAL.fullmatch(name) and (name in self.duplicates or name in self.types and not self.types[name].header):
                    self.duplicates.add(name)
                    self.types.pop(name, None)
                    raise Refuse('duplicate/conditional local typedef')
                if name: self.types[name] = ty
                if tag: self.types[m[2]+' '+tag] = ty
            except (Refuse, SyntaxError, ValueError) as e:
                self.errors.append({'type':name or tag, 'reason':str(e), 'header':header})
        return self.types


def leaves(ty, off=0, path='', optional=False):
    """Padding holes are excluded; arrays retain their shape (no scalar/array alias)."""
    if ty.kind in ('struct', 'union'):
        for name, (o, ft) in ty.fields.items():
            if name.startswith('pad_'): continue
            yield from leaves(ft, off+o, path+('.' if path else '')+name,
                              optional or ty.kind == 'union')
    elif ty.kind == 'array' and ty.elem.kind in ('struct', 'union', 'array'):
        # Kept conservative: don't map a dynamic aggregate index into a scalar field.
        yield off, path, ty, optional
    else:
        yield off, path, ty, optional


def layout_map(source, target):
    if source.size != target.size or source.align != target.align:
        raise Refuse('size/alignment differ')
    if source.kind != target.kind:
        raise Refuse('aggregate kind differs')
    dest = list(leaves(target)); mapping = {}; unresolved = []
    for off, path, ty, optional in leaves(source):
        matches = [(p, t) for o, p, t, _ in dest if off == o and ty.key() == t.key()]
        if not matches:
            if optional: unresolved.append(path); continue
            raise Refuse('no identical leaf at 0x%X (%s)' % (off, path))
        matches.sort(key=lambda x: (x[0].count('.'), len(x[0]), x[0]))
        mapping[path] = matches[0][0]
    src_leaves = list(leaves(source))
    for off, path, ty, optional in dest:
        if optional:
            # Alternative union spellings may differ, but cannot create a named
            # region over bytes that are only padding in the source view.
            covered = any(o < off+ty.size and off < o+st.size for o,_,st,_ in src_leaves)
        else:
            covered = any(o == off and st.key() == ty.key() for o,_,st,_ in src_leaves)
        if not covered:
            raise Refuse('destination has an extra named leaf at 0x%X (%s)' % (off,path))
    if not mapping: raise Refuse('no mapped non-padding leaves')
    return mapping, unresolved


@dataclass
class Trace:
    ty: Type
    start: int
    source: Type | None = None
    path: str = ''
    first: int = -1


class Expressions:
    """Small postfix/type reader, not a C compiler. Unknown syntax fails closed.

    Edits are limited to source positions; comments, strings, and unrelated members
    are never globally substituted. Declarations with shadowed names are refused.
    """
    def __init__(self, text, types, locals_, spans):
        self.text = text
        self.toks = [m for m in LEX.finditer(mask(text)) if not any(a <= m.start() < b for a,b in spans)]
        self.words = [m[0] for m in self.toks]; self.types = types; self.locals = locals_
        spellings = {n:n for n in locals_}
        for spelling, ty in types.items():
            if spelling.startswith(('struct ', 'union ')) and ty in locals_.values():
                spellings[spelling.split()[1]] = ty.name
        self.pairs = {}; stack = []; self.vars = {}; self.type_edits = []; self.cache = {}
        for i, w in enumerate(self.words):
            if w in ('(', '[', '{'): stack.append(i)
            elif w in (')', ']', '}'):
                if not stack or self.words[stack[-1]] != {')':'(', ']':'[', '}':'{'}[w]:
                    raise Refuse('unbalanced C tokens')
                j = stack.pop(); self.pairs[i] = j; self.pairs[j] = i
        for i, w in enumerate(self.words):
            if w not in spellings: continue
            local_name = spellings[w]
            if w != local_name and (not i or self.words[i-1] not in ('struct', 'union')): continue
            start = i-1 if i and self.words[i-1] in ('struct', 'union') else i
            j = i+1
            while j < len(self.words) and self.words[j] in ('*', 'const', 'volatile'): j += 1
            if '*' not in self.words[i+1:j]: raise Refuse('by-value/unsupported local type use: '+w)
            ptr = types[local_name]
            for _ in range(self.words[i+1:j].count('*')): ptr = pointer(ptr)
            # Only a complete cast type or a simple pointer declaration is accepted.
            if j < len(self.words) and self.words[j] == ')' and start and self.words[start-1] == '(':
                pass
            elif j < len(self.words) and re.fullmatch(r'[A-Za-z_]\w*', self.words[j]):
                var = self.words[j]
                if j+1 < len(self.words) and self.words[j+1] == '(':
                    raise Refuse('function returning local pointer')
                if var in self.vars: raise Refuse('shadowed/redeclared local pointer: '+var)
                self.vars[var] = ptr
                if j+1 < len(self.words) and self.words[j+1] == ',':
                    # Function parameters are fine; comma-separated declarations aren't.
                    if not any(self.words[k] == '(' and self.pairs.get(k, -1) > j for k in range(j)):
                        raise Refuse('multiple pointer declarators')
            else: raise Refuse('unsupported local type use: '+w)
            self.type_edits.append((self.toks[start].start(), self.toks[i].end(), local_name))
        # A second declaration of a typed variable in a nested scope can have any type.
        # Refuse it rather than guessing C scope from text.
        for var in self.vars:
            decl_matches = re.findall(r'\b(?:[A-Za-z_]\w*\s+)+(?:\*\s*)*'+re.escape(var)+r'\s*(?=[;=,)\[])', mask(text))
            count = sum(not re.match(r'(?:return|goto|case|else)\b', d) for d in decl_matches)
            if count > 1: raise Refuse('possible shadowed pointer: '+var)

    def cast_type(self, a, b):
        words = self.words[a:b]
        if not words: return None
        # Cast type has no expression operators or variable name.
        stars = words.count('*'); raw = ' '.join(w for w in words if w not in ('*', 'const', 'volatile'))
        ty = self.types.get(raw) or self.types.get(raw.replace('struct ', '').replace('union ', ''))
        if ty is None: return None
        if any(w not in ('*', 'const', 'volatile', 'struct', 'union') and w not in raw.split() for w in words): return None
        for _ in range(stars): ty = pointer(ty)
        return ty

    def infer(self, end):
        if end in self.cache: return self.cache[end]
        self.cache[end] = None
        out = self._infer(end)
        self.cache[end] = out; return out

    def _infer(self, end):
        if end <= 0: return None
        i = end-1; w = self.words[i]
        if re.fullmatch(r'[A-Za-z_]\w*', w):
            if i and self.words[i-1] in ('.', '->'):
                base = self.infer(i-1)
                if base is None: return None
                ty = base.ty
                if self.words[i-1] == '->':
                    if ty.kind != 'pointer' or ty.elem is None: return None
                    ty = ty.elem
                if ty.kind not in ('struct', 'union') or w not in ty.fields: return None
                _, ft = ty.fields[w]
                src = base.source or (ty if ty in self.locals.values() else None)
                path = (base.path+'.' if base.path else '')+w if src else ''
                return Trace(ft, base.start, src, path, base.first if base.first >= 0 else i)
            ty = self.vars.get(w)
            if ty is not None: return Trace(ty, i)
        if w == ']':
            j = self.pairs[i]; base = self.infer(j)
            if base and base.ty.kind in ('pointer', 'array'):
                return Trace(base.ty.elem, base.start, base.source,
                             base.path+'[]' if base.source else '', base.first)
        if w == ')':
            j = self.pairs[i]
            # A parenthesised cast expression: ((T *) arbitrary_expression).
            if j+1 < i and self.words[j+1] == '(':
                k = self.pairs[j+1]
                if k < i and (ty := self.cast_type(j+2, k)):
                    return Trace(ty, j)
            # Parenthesised variable, dereference or simple pointer arithmetic.
            inner = self.infer(i)
            if inner and inner.start == j+1:
                return Trace(inner.ty, j, inner.source, inner.path, inner.first)
            if j+1 < i and self.words[j+1] == '*' and inner and inner.start == j+2 and inner.ty.kind == 'pointer':
                return Trace(inner.ty.elem, j, inner.source, inner.path, inner.first)
            if j+1 < i and self.words[j+1] in self.vars:
                ty = self.vars[self.words[j+1]]
                if ty.kind == 'pointer' and j+2 < i and self.words[j+2] in ('+', '-'):
                    return Trace(ty, j)
        return None

    def rewrite(self, target, mapping):
        edits = []; traces = []
        changed_members = {p.split('.')[0] for n, mp in mapping.items() for p,d in mp.items() if p != d}
        changed_members |= {p.split('.')[0] for n in mapping for _,p,_,_ in leaves(self.locals[n]) if p not in mapping[n]}
        for i, w in enumerate(self.words[:-1]):
            if w not in ('.', '->'): continue
            tr = self.infer(i+2)
            if tr is None and self.words[i+1] in changed_members:
                raise Refuse('unresolved member base: '+self.words[i+1])
            if tr and tr.source:
                traces.append((i+2, tr))
        for end, tr in traces:
            if tr.ty.kind in ('struct', 'union'):
                if not any(other.first == tr.first and other.path.startswith(tr.path+'.')
                           for _, other in traces):
                    raise Refuse('whole aggregate member use: '+tr.path)
                continue
            if tr.source.name not in target: continue
            mp = mapping[tr.source.name]
            if tr.path not in mp: raise Refuse('unmapped member/union alternative used: '+tr.path)
            dest = mp[tr.path]
            edits.append((self.toks[tr.first].start(), self.toks[end-1].end(), dest))
        for a,b,name in self.type_edits: edits.append((a,b,target[name]))
        return apply_edits(self.text, edits)


def apply_edits(text, edits):
    unique = sorted(set(edits))
    for first, second in zip(unique, unique[1:]):
        if first[1] > second[0]: raise Refuse('overlapping edits')
    for a,b,repl in reversed(unique): text = text[:a]+repl+text[b:]
    return text


def add_include(text, header):
    if re.search(r'^\s*#\s*include\s*"'+re.escape(header)+r'"', text, re.M): return text
    incs = list(re.finditer(r'^\s*#\s*include[^\n]*\n', text, re.M))
    pos = incs[-1].end() if incs else 0
    return text[:pos]+'#include "'+header+'"\n'+text[pos:]


class Catalog:
    def __init__(self, root):
        self.root = Path(root); self.types = {}; self.targets = {}; self.errors = []
        headers = sorted((self.root/'include/shared').glob('*.h'))+sorted((self.root/'include/records').glob('*.h'))
        # Multiple passes resolve named by-value dependencies regardless of header order.
        for _ in range(4):
            p = Parser(self.types)
            for h in headers: p.parse(h.read_text(), h.relative_to(self.root/'include').as_posix())
            self.types = p.types; self.errors = p.errors
        for name, ty in self.types.items():
            if ' ' not in name and ty.header and ty.name == name: self.targets[name] = ty
        self.provenance = self._load('ledger/struct_census_structs.json', {})
        self.groups = {g['key']:g for g in self._load('ledger/struct_census.json', {}).get('groups', [])}
        self.records = self._load('ledger/records.json', {})
        for record in list(self.records.values()):
            if record.get('canonical_type'):
                self.records[record['canonical_type']] = record
        self.modules = {r['id']:r['module'] for r in self._jsonl('ledger/modules.jsonl')}
        self.rows = {r['id']:r for r in self._jsonl('ledger/rows.jsonl')}

    def _load(self, path, default):
        p = self.root/path; return json.loads(p.read_text()) if p.exists() else default

    def _jsonl(self, path):
        p = self.root/path
        return [json.loads(l) for l in p.read_text().splitlines() if l.strip()] if p.exists() else []

    def analyze(self, text, row_id, only=None):
        p = Parser(self.types); p.parse(text)
        local = {n:t for n,t in p.types.items() if LOCAL.fullmatch(n) and t.header == '' and t.name == n}
        out = []
        for name, source in local.items():
            provenance = self.provenance.get(row_id+'|'+name, {})
            cls = provenance.get('class', 'unclassified:'+row_id+'|'+name)
            item = {'row':row_id, 'local':name, 'class':cls, 'module':self.modules.get(row_id, ''),
                    'size':source.size, 'align':source.align, 'candidates':[], 'holds':[]}
            for dest, ty in sorted(self.targets.items(), key=lambda x:(x[1].header.startswith('records/'), x[0])):
                if only and dest != only: continue
                # Record-class provenance is evidence; a conflicting known class is a hard refusal.
                rec_cls = self.records.get(dest, {}).get('class')
                if rec_cls and not cls.startswith('unclassified:') and rec_cls != cls: continue
                try: mp, unresolved = layout_map(source, ty)
                except Refuse: continue
                try:
                    folded = fold_one(text, p.types, source, ty, mp)
                    item['candidates'].append({'type':dest, 'header':ty.header, 'mapping':mp,
                                               'unused_union_alternatives':unresolved,
                                               'selection': 'provenance' if rec_cls == cls else 'review-required',
                                               'after_sha256':sha(folded.encode())})
                except Refuse as e: item['holds'].append({'type':dest, 'reason':str(e)})
            if not item['candidates'] and not item['holds']:
                item['holds'].append({'reason':'no equal-size/alignment typed layout in catalog'})
            out.append(item)
        for error in p.errors:
            if LOCAL.fullmatch(error['type'] or ''):
                out.append({'row':row_id, 'local':error['type'], 'class':self.provenance.get(row_id+'|'+error['type'], {}).get('class', 'unclassified'),
                            'module':self.modules.get(row_id, ''), 'candidates':[], 'holds':[error]})
        return out

    def fold(self, text, row_id, choices=None):
        notes = []; holds = []; choices = choices or {}
        # Reparse after each fold, so positions and declarations cannot go stale.
        for item in self.analyze(text, row_id):
            cands = item['candidates']; name = item['local']
            if name in choices: cands = [c for c in cands if c['type'] == choices[name]]
            if not cands:
                holds.append({'local':name, 'reason':item['holds'] or 'no equal-size compatible shared layout'}); continue
            # An ambiguous layout is not semantic evidence: explicit selection is required.
            if name not in choices and not any(c['selection'] == 'provenance' for c in cands):
                holds.append({'local':name, 'reason':'layout match requires explicit semantic selection', 'types':[c['type'] for c in cands]}); continue
            if name not in choices: cands = [c for c in cands if c['selection'] == 'provenance']
            if len(cands) > 1:
                holds.append({'local':name, 'reason':'ambiguous targets', 'types':[c['type'] for c in cands]}); continue
            c = cands[0]; p = Parser(self.types); p.parse(text)
            try:
                text = fold_one(text, p.types, p.types[name], self.targets[c['type']], c['mapping'])
                notes.append({'local':name, **c})
            except Refuse as e: holds.append({'local':name, 'reason':str(e)})
        return text, notes, holds


def fold_one(text, types, source, dest, mapping):
    # All local definitions are kept out of expression parsing. A dependency on the
    # folded type inside another typedef needs a separate aggregate-layout proof.
    locals_ = {n:t for n,t in types.items() if LOCAL.fullmatch(n) and t.header == '' and t.name == n}
    for n,t in locals_.items():
        if n != source.name and re.search(r'\b'+re.escape(source.name)+r'\b', mask(text[t.span[0]:t.span[1]])):
            raise Refuse('local typedef dependency: '+n)
    spans = [t.span for t in locals_.values()]
    # Operate on just this source type; other local casts remain ordinary opaque expressions.
    expr = Expressions(text, types, {source.name:source}, spans)
    new = expr.rewrite({source.name:dest.name}, {source.name:mapping})
    # Remove the original definition by its unchanged prefix position (member/type edits
    # take place outside local definitions, but can precede this definition).
    delta_before = sum(len(repl)-(b-a) for a,b,name in expr.type_edits
                       for repl in [dest.name] if b <= source.span[0])
    a,b = source.span; a += delta_before; b += delta_before
    new = new[:a]+new[b:]
    # A trailing provenance comment is useful evidence, keep it intact.
    return add_include(new, dest.header)


def sha(data):
    return hashlib.sha256(data).hexdigest()
