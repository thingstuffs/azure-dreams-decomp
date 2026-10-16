#!/usr/bin/env python3
"""Advisory C lever detector; source evidence is not a retail-byte proof.

  lever_check.py ROW candidate.c [--root REPO] [--base baseline.c] [--json]
  lever_check.py --check OUT_DIR [OUT_DIR ...] [--root REPO] [--json]

Single-candidate mode always permits staging. Batch --check exits 1 for a
REFUSE-LIKELY finding, 2 for incomplete input, and 0 otherwise. The checker
does not compile, rewrite C, change gates, or grant review. It uses a bounded
C lexer and conservative statement analysis, not a complete C parser. Every
finding carries a candidate line, source excerpt, and reason. Existing smells
are INFO except unused leftovers; unused declarations count even if they predate
the edit. Decision 39/44/45 exceptions are review leads, not certifications.
"""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
from dataclasses import dataclass, field
import hashlib
import json
from pathlib import Path
import re
import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[2]))
from source_layout import row_path as layout_row_path

LIMIT = 4 * 1024 * 1024
SEVERITIES = ('REFUSE-LIKELY', 'REVIEW', 'INFO')
TYPE_WORDS = set('void char short int long signed unsigned float double s8 u8 s16 u16 s32 u32 s64 u64 f32 f64 size_t intptr_t uintptr_t bool'.split())
QUALIFIERS = set('const volatile restrict register static extern inline __inline__ auto typedef'.split())
CONTROL = set('if else for while do switch case default return goto sizeof break continue'.split())
ASSIGN = {'=', '+=', '-=', '*=', '/=', '%=', '|=', '&=', '^=', '<<=', '>>='}
TOKEN = re.compile(r'/\*[\s\S]*?\*/|//[^\n]*|^[ \t]*\#(?:\\\n|[^\n])*|'
                   r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|'
                   r'[A-Za-z_]\w*|0[xX][0-9a-fA-F]+[uUlL]*|\d+(?:\.\d*)?[uUlLfF]*|'
                   r'>>=|<<=|->|\+\+|--|\+=|-=|\*=|/=|%=|&=|\|=|\^=|==|!=|<=|>=|<<|>>|&&|\|\||\.\.\.|[^\s]', re.M)


@dataclass(frozen=True)
class Tok:
    value: str
    offset: int
    line: int


def lex(text):
    # Newline positions are counted once, avoiding quadratic prefix scans.
    import bisect
    newlines = [m.start() for m in re.finditer('\n', text)]
    result = []
    for m in TOKEN.finditer(text):
        value = m.group()
        if value.startswith(('/*', '//')) or value.lstrip().startswith('#'):
            continue
        result.append(Tok(value, m.start(), bisect.bisect_left(newlines, m.start()) + 1))
    return result


def values(tokens):
    return tuple(t.value for t in tokens)


def spelling(tokens):
    return ' '.join(values(tokens))


def pairs(tokens):
    stack = []; result = {}; wanted = {')': '(', ']': '[', '}': '{'}
    for i, t in enumerate(tokens):
        if t.value in ('(', '[', '{'):
            stack.append(i)
        elif t.value in wanted:
            if not stack or tokens[stack[-1]].value != wanted[t.value]:
                raise ValueError('unbalanced C delimiters at line %s' % t.line)
            start = stack.pop(); result[start] = i; result[i] = start
    if stack:
        raise ValueError('unclosed C delimiter at line %s' % tokens[stack[-1]].line)
    return result


def split_top(tokens, delimiter=','):
    depth = 0; start = 0; out = []
    for i, t in enumerate(tokens):
        if t.value in ('(', '[', '{'): depth += 1
        elif t.value in (')', ']', '}'): depth -= 1
        elif depth == 0 and t.value == delimiter:
            out.append(tokens[start:i]); start = i + 1
    out.append(tokens[start:]); return out


def strip_parens(tokens):
    tokens = list(tokens)
    while tokens and tokens[0].value == '(':
        p = pairs(tokens)
        if p[0] != len(tokens) - 1: break
        tokens = tokens[1:-1]
    return tokens


def simple_value(tokens, types):
    """Remove enclosing parentheses and scalar/pointer casts, never operations."""
    tokens = strip_parens(tokens)
    while tokens and tokens[0].value == '(':
        p = pairs(tokens); end = p[0]
        middle = values(tokens[1:end])
        if not middle or not all(x in types | QUALIFIERS | {'*', 'struct', 'union'} for x in middle): break
        tokens = strip_parens(tokens[end+1:])
    return tokens


@dataclass
class Var:
    name: str
    type: tuple
    token: Tok
    scope: int
    end: int
    index: int
    initializer: list = field(default_factory=list)
    union: object = None
    reads: list = field(default_factory=list)
    writes: list = field(default_factory=list)
    addressed: bool = False


@dataclass
class Union:
    label: str
    token: Tok
    members: dict
    variables: list = field(default_factory=list)
    register: bool = False


@dataclass
class Function:
    name: str
    ret: tuple
    args: tuple
    token: Tok
    start: int
    end: int
    defined: bool


class Source:
    def __init__(self, text):
        self.text = text; self.tokens = lex(text); self.pair = pairs(self.tokens)
        self.types = set(TYPE_WORDS); self.unions = []; self.union_types = {}
        self.functions = []; self.variables = []; self.declaration_indices = set(); self.typedef_declarations = set()
        self._types(); self._functions(); self._locals(); self._references()

    def _types(self):
        ts = self.tokens; p = self.pair
        # Typedef names, including aggregate trailing aliases and function ptrs.
        for i,t in enumerate(ts):
            if t.value != 'typedef': continue
            j = i+1
            while j < len(ts) and ts[j].value != ';':
                if ts[j].value in ('{', '(','['): j = p[j]+1
                else: j += 1
            if j >= len(ts): continue
            names = []; k = i + 1
            while k < j:
                if k+2<j and ts[k].value=='(' and ts[k+1].value=='*' and re.fullmatch(r'[A-Za-z_]\w*',ts[k+2].value):
                    names.append(ts[k+2].value);self.typedef_declarations.add(k+2)
                if ts[k].value in ('{', '(', '['): k = p[k] + 1; continue
                if re.fullmatch(r'[A-Za-z_]\w*', ts[k].value) and ts[k].value not in ('__attribute__',): names.append(ts[k].value)
                k += 1
            if names:
                self.types.add(names[-1])
                self.typedef_declarations.update(k for k in range(i+1,j) if ts[k].value==names[-1] and (ts[k-1].value in ('struct','union','enum') or k+1==j or ts[k+1].value=='__attribute__'))
        for i,t in enumerate(ts):
            if t.value != 'union': continue
            j=i+1; tag=''
            if j<len(ts) and re.fullmatch(r'[A-Za-z_]\w*',ts[j].value): tag=ts[j].value;j+=1
            if j>=len(ts) or ts[j].value!='{': continue
            end=p[j]; members={}
            for part in split_top(ts[j+1:end],';'):
                if not part: continue
                # Last outer identifier is the member (array dimensions skipped).
                candidates=[];k=0
                while k<len(part):
                    if part[k].value in ('{','(','['): k=p[ts.index(part[k])]+1-ts.index(part[0]);continue
                    if re.fullmatch(r'[A-Za-z_]\w*',part[k].value):candidates.append(k)
                    k+=1
                if len(candidates)<2:continue
                n=candidates[-1];members[part[n].value]=values(part[:n])
            following=[];k=end+1
            while k<len(ts) and ts[k].value not in (';','='):following.append(ts[k]);k+=1
            typedef=i>0 and ts[i-1].value=='typedef'
            label=tag or (following[-1].value if following else 'anonymous@%d'%t.line)
            u=Union(label,t,members,register=i>0 and ts[i-1].value=='register');self.unions.append(u)
            if tag:self.union_types[tag]=u
            if typedef and following:
                alias=following[-1].value;self.union_types[alias]=u;self.types.add(alias)
            self.union_types['@'+str(i)]=u

    def _functions(self):
        ts=self.tokens;p=self.pair;depth=0;start=0;i=0
        while i<len(ts):
            t=ts[i]
            if depth==0 and t.value=='(' and i>start and re.fullmatch(r'[A-Za-z_]\w*',ts[i-1].value):
                name=ts[i-1].value;end=p[i];after=end+1
                while after+1<len(ts) and ts[after].value=='__attribute__' and ts[after+1].value=='(':after=p[after+1]+1
                nextv=ts[after].value if after<len(ts) else ''
                if name not in CONTROL|{'__attribute__','ASM_REG','asm','__asm','__asm__'} and nextv in ('{',';'):
                    ret=tuple(x.value for x in ts[start:i-1] if x.value not in QUALIFIERS)
                    if ret and not any(x in ret for x in ('=','return')):
                        args=[]
                        for arg in split_top(ts[i+1:end]):
                            av=list(values(arg));ids=[n for n,x in enumerate(av) if re.fullmatch(r'[A-Za-z_]\w*',x)]
                            if len(ids)>1 and av[ids[-1]] not in self.types|QUALIFIERS and (ids[-1]==len(av)-1 or '[' in av[ids[-1]+1:]):av.pop(ids[-1])
                            args.append(tuple(av))
                        if args==[()] or args==[('void',)]:args=[]
                        fend=p[after] if nextv=='{' else after
                        self.functions.append(Function(name,ret,tuple(args),ts[i-1],after,fend,nextv=='{'))
                        i=fend+1;start=i;continue
            if t.value=='{':depth+=1
            elif t.value=='}':depth-=1
            if depth==0 and t.value==';':start=i+1
            i+=1

    def _locals(self):
        ts=self.tokens;p=self.pair
        for fun in self.functions:
            if not fun.defined:continue
            scopes=[fun.start];i=fun.start+1;at_start=True
            while i<fun.end:
                t=ts[i]
                if t.value=='{':scopes.append(i);at_start=True;i+=1;continue
                if t.value=='}':
                    if len(scopes)>1:scopes.pop()
                    at_start=False;i+=1;continue
                if t.value==';':at_start=True;i+=1;continue
                if not at_start:i+=1;continue
                # Labels / case arms may precede declarations.
                if t.value in ('case','default'):
                    while i<fun.end and ts[i].value!=':':i+=1
                    i+=1;at_start=True;continue
                if i+1<fun.end and ts[i+1].value==':':i+=2;continue
                start=i;j=i;ty=[];union=None
                while j<fun.end and ts[j].value in QUALIFIERS:ty.append(ts[j].value);j+=1
                if j>=fun.end:break
                if ts[j].value in ('struct','union','enum'):
                    isunion=ts[j].value=='union';ty.append(ts[j].value);ui=j;j+=1
                    if j<fun.end and re.fullmatch(r'[A-Za-z_]\w*',ts[j].value):
                        ty.append(ts[j].value);union=self.union_types.get(ts[j].value) if isunion else None;j+=1
                    if j<fun.end and ts[j].value=='{':
                        union=self.union_types.get('@'+str(ui)) if isunion else None
                        j=p[j]+1
                elif ts[j].value in self.types or (re.fullmatch(r'[A-Za-z_]\w*',ts[j].value) and j+1<fun.end and (ts[j+1].value=='*' or re.fullmatch(r'[A-Za-z_]\w*',ts[j+1].value))):
                    ty.append(ts[j].value);union=self.union_types.get(ts[j].value);j+=1
                    while j<fun.end and ts[j].value in TYPE_WORDS|QUALIFIERS:ty.append(ts[j].value);j+=1
                else:at_start=False;i+=1;continue
                if any(x in ty for x in CONTROL):at_start=False;i+=1;continue
                end=j
                while end<fun.end and ts[end].value!=';':
                    if ts[end].value in ('(','[','{'):end=p[end]+1
                    else:end+=1
                if end>=fun.end:break
                # Declarators in a comma-separated declaration share the type.
                for declarator in split_top(ts[j:end]):
                    if not declarator:continue
                    k=0;ptr=[]
                    while k<len(declarator) and declarator[k].value in {'*'}|QUALIFIERS:ptr.append(declarator[k].value);k+=1
                    if k+2<len(declarator) and declarator[k].value=='(' and declarator[k+1].value=='*':
                        ptr.append('*');k+=2
                    if k>=len(declarator) or not re.fullmatch(r'[A-Za-z_]\w*',declarator[k].value):continue
                    name=declarator[k];idx=ts.index(name)
                    if k+1<len(declarator) and declarator[k+1].value=='(' and name.value!='ASM_REG':continue
                    init=[]
                    for n,x in enumerate(declarator):
                        if x.value=='=':init=declarator[n+1:];break
                    v=Var(name.value,tuple(ty+ptr),name,scopes[-1],p[scopes[-1]],idx,init,union)
                    self.variables.append(v);self.declaration_indices.add(idx)
                    if union:union.variables.append(v)
                i=end+1;at_start=True

    def _references(self):
        ts=self.tokens
        for v in self.variables:
            if v.initializer:v.writes.append((v.index,v.initializer,'='))
            for i in range(v.index+1,v.end):
                if ts[i].value!=v.name or i in self.declaration_indices:continue
                if i and ts[i-1].value in ('.','->','struct','union'):continue
                # Respect a later declaration shadowing this one in its scope.
                if any(w.name==v.name and w.index>v.index and w.scope<=i<w.end and w.index<=i for w in self.variables):continue
                j=i+1
                prefix_start = max((k for k in range(v.index+1,i) if ts[k].value in (';','{','}')), default=v.index) + 1
                dereference = '*' in values(ts[prefix_start:i])
                if j<len(ts) and ts[j].value in ASSIGN and not dereference:
                    op=ts[j].value;k=j+1
                    while k<v.end and ts[k].value not in (';',','):
                        if ts[k].value in ('(','[','{'):k=self.pair[k]+1
                        else:k+=1
                    v.writes.append((i,ts[j+1:k],op))
                    if op!='=':v.reads.append(i)
                elif (j<len(ts) and ts[j].value in ('++','--')) or (i and ts[i-1].value in ('++','--')):
                    v.writes.append((i,[], '++'));v.reads.append(i)
                else:
                    v.reads.append(i)
                    if i and ts[i-1].value=='&':v.addressed=True

    def statements(self):
        ts=self.tokens;p=self.pair
        for f in self.functions:
            if not f.defined:continue
            start=f.start+1;i=start
            while i<f.end:
                if ts[i].value in ('(', '['):i=p[i]+1;continue
                if ts[i].value in ('{','}'):
                    start=i+1
                elif ts[i].value==';':
                    if start<i:yield ts[start:i]
                    start=i+1
                i+=1


def _issue(code,severity,token,message,subject='',related=None):
    return dict(code=code,severity=severity,line=token.line,column=0,offset=token.offset,
                message=message,subject=subject,related_lines=related or [])


def local_findings(src):
    out=[];ts=src.tokens;types=src.types
    def emit(code,level,t,msg,subject='',related=None):out.append(_issue(code,level,t,msg,subject,related))
    for v in src.variables:
        if not v.reads:
            emit('UNUSED-LOCAL','REFUSE-LIKELY',v.token,'Local %s is never read%s.'%(v.name,' (set but unused)' if v.writes else ''),v.name)
        if len(v.writes)==1 and len(v.reads)==1 and not v.addressed and not v.union:
            wi,rhs,op=v.writes[0];ri=v.reads[0]
            # Feeding an existing multi-role scalar with a one-use local is the
            # review4 steering-copy family; a field-address local is a real view.
            owner=next((w for w in src.variables if w is not v and any(a<=ri<max(a+1, next((j for j in range(a+1,w.end) if ts[j].value==';'),w.end)) for a,_,_ in w.writes)),None)
            simple=simple_value(rhs,types)
            widths={'s8':8,'u8':8,'char':8,'s16':16,'u16':16,'short':16,'s32':32,'u32':32,'int':32,'s64':64,'u64':64}
            v_width=next((widths[x] for x in v.type if x in widths),None)
            owner_width=next((widths[x] for x in owner.type if x in widths),None) if owner else None
            typed_snapshot=owner and '*' not in v.type and '*' not in owner.type and v_width and owner_width and v_width!=owner_width
            if owner and not typed_snapshot and len(owner.writes)>1 and op=='=' and any(simple_value(r,types) == [ts[ri]] for a,r,o in owner.writes):
                emit('STEERING-COPY','REFUSE-LIKELY',ts[wi],'%s is assigned once and read once, only to feed reused %s; substitute its expression directly.'%(v.name,owner.name),v.name,[ts[ri].line])
            else:
                emit('SINGLE-USE','INFO',v.token,'%s has one assignment and one read; check whether its name explains a real value/view.'%v.name,v.name,[ts[ri].line])
        if len(v.writes) == 1 and v.reads and not v.union:
            _, rhs, _ = v.writes[0]
            body = spelling(rhs)
            scalar = any(x in TYPE_WORDS - {'void'} for x in v.type) and '*' not in v.type
            pointer = '*' in v.type
            stripped_rhs = simple_value(rhs, types)
            scalar_names = {w.name for w in src.variables if '*' not in w.type and not w.union}
            scalar_input = bool(pointer and '*' in values(rhs) and len(stripped_rhs) == 1 and (stripped_rhs[0].value in scalar_names or re.fullmatch(r'0[xX][0-9a-fA-F]+|[0-9]+', stripped_rhs[0].value)))
            pointer_input = bool(re.search(r'\(\s*(?:s32|u32|int|intptr_t|uintptr_t)\s*\)', body))
            readbacks = []
            for ri in v.reads:
                before = spelling(ts[max(v.index + 1, ri - 8):ri])
                pointer_back = bool(re.search(r'\([^()]+\*\s*\)\s*\(*$', before))
                int_back = bool(re.search(r'\(\s*(?:s32|u32|int|intptr_t|uintptr_t)\s*\)\s*\(*$', before))
                readbacks.append(pointer_back if scalar else int_back)
            if all(readbacks) and ((scalar and pointer_input) or (pointer and scalar_input)):
                emit('POINTER-INT-LAUNDER', 'REFUSE-LIKELY', v.token,
                     '%s only carries a pointer/integer conversion to be cast back; replace the round-trip with the original expression.' % v.name,
                     v.name, [ts[i].line for i in v.reads])
        # Two straight-line overwrites without a read or control/call barrier.
        for (a,rhs,op),(b,next_rhs,next_op) in zip(v.writes,v.writes[1:]):
            if op!='=' or next_op!='=' or any(a<i<=b for i in v.reads) or v.name in values(next_rhs):continue
            region=values(ts[a+1:b])
            if any(x in region for x in ('{','}','if','for','while','case','default','break','continue','goto','return')):continue
            if any(re.fullmatch(r'[A-Za-z_]\w*',x) and n+1<len(region) and region[n+1]=='(' and x not in types for n,x in enumerate(region)):continue
            emit('DEAD-VALUE','REFUSE-LIKELY',ts[a],'%s is overwritten at line %d before any read (source evidence; inspect retail before allowing a vestigial store).'%(v.name,ts[b].line),v.name,[ts[b].line])
    # File-scope unused typedefs, including aggregate aliases.
    for name in sorted(types-TYPE_WORDS):
        positions=[i for i,t in enumerate(ts) if t.value==name and (i==0 or ts[i-1].value not in ('.','->'))]
        uses=[i for i in positions if i not in src.typedef_declarations]
        preprocessor = '\n'.join(line for line in src.text.splitlines() if line.lstrip().startswith('#define'))
        if positions and not uses and not re.search(r'\b'+re.escape(name)+r'\b',preprocessor):
            emit('UNUSED-TYPEDEF','REFUSE-LIKELY',ts[positions[0]],'Typedef %s has no use in this translation unit.'%name,name)
    for u in src.unions:
        for v in u.variables:
            init=values(v.initializer)
            if len(u.members)==1 and init==('{','0','}'):
                emit('ZERO-UNION','INFO',v.token,'Zero-initialized single-member union %s is the accepted idiom; retain its trade record.'%v.name,v.name)
            else:
                emit('UNION-SHAPE','REVIEW',v.token,'Union %s is outside the accepted zero-init single-member idiom; inspect its representation uses.'%v.name,v.name)
                if len(u.members)==1:
                    emit('UNION-CARRIER','REFUSE-LIKELY',v.token,'Single-member union %s lacks the accepted = {0} initializer.'%v.name,v.name)
            accesses=[]
            for i in range(v.index+1,v.end-2):
                if ts[i].value!=v.name or ts[i+1].value not in ('.','->'):continue
                name=ts[i+2].value
                if name not in u.members:continue
                j=i+3;path=name
                while j+1<v.end and ts[j].value=='.':path+='.'+ts[j+1].value;j+=2
                write=j<v.end and ts[j].value in ASSIGN
                accesses.append((i,name,path,write))
            reads=Counter(name for _,name,_,write in accesses if not write)
            writes=Counter(name for _,name,_,write in accesses if write)
            if v.initializer and u.members:
                first=init[2] if len(init)>2 and init[1]=='.' else next(iter(u.members));reads[first]+=0;writes[first]+=1
            escaped=any(ts[ri+1].value!='.' for ri in v.reads) or '*' in v.type
            for name,ty in u.members.items():
                if not reads[name] and (len(u.members)>1):
                    emit('UNREAD-MEMBER','INFO' if escaped else 'REFUSE-LIKELY',u.token,'Union %s member %s (%s) is %s; inspect a width/mode-only carrier.'%(v.name,name,' '.join(ty),'write-only' if writes[name] else 'never accessed'),v.name+'.'+name)
            events=[];constructors=[]
            for wi,rhs,op in v.writes:
                if op!='=':continue
                # A whole-union assignment takes effect after RHS evaluation.
                position=ts.index(rhs[-1])+1 if rhs else wi
                member=None;rv=values(rhs)
                brace=next((n for n,x in enumerate(rv) if x=='{'),None)
                if brace is not None and rv[-1:] == ('}',):
                    prefix=rv[:brace]
                    literal=not prefix or (prefix[0]=='(' and prefix[-1]==')' and (u.label in prefix or 'union' in prefix))
                    if literal:
                        body=rv[brace+1:-1]
                        member=body[1] if len(body)>1 and body[0]=='.' else next(iter(u.members),None)
                        if prefix:constructors.append((wi,member))
                events.append((position,member,member or '',True,wi))
            for i,name,path,write in accesses:
                position=i
                if write:
                    j=i+3
                    while j+1<v.end and ts[j].value=='.':j+=2
                    j+=1
                    while j<v.end and ts[j].value!=';':
                        if ts[j].value in ('(','[','{'):j=src.pair[j]+1
                        else:j+=1
                    position=j
                events.append((position,name,path,write,i))
            # These repeated constructors/read-backs are a distinct source
            # lever. They are not mislabeled as reads of inactive members.
            readbacks=[]
            for w in src.variables:
                if w is v or len(w.writes)!=1 or len(w.reads)!=1:continue
                rhs=simple_value(w.writes[0][1],types)
                if len(rhs)==3 and values(rhs)[:2]==(v.name,'.') and rhs[2].value in u.members:readbacks.append(w)
            if len(u.members)>1 and len(constructors)>=2 and len(readbacks)>=2:
                emit('UNION-CONSTRUCTOR-COPY','REFUSE-LIKELY',ts[constructors[0][0]],
                     '%s uses repeated whole-union constructors followed by single-use scalar read-backs; inspect clobber-only steering and substitute direct expressions.'%v.name,v.name,[ts[w.writes[0][0]].line for w in readbacks])
            last=None
            for _,name,path,write,i in sorted(events,key=lambda item:(item[0],not item[3])):
                if write:
                    last=(i,name) if name else None
                    continue
                if last and last[1]!=name:
                    before=u.members.get(last[1],());after=u.members[name]
                    if before!=after:
                        emit('UNION-LAUNDER','REFUSE-LIKELY',ts[i],'%s is read through %s after a write through different-type member %s (%s -> %s).'%(v.name,path,last[1],' '.join(before),' '.join(after)),v.name,[ts[last[0]].line])
                if '.' in path and last and last[1]==name:
                    # A nested partial write/read-back into a register union is
                    # precisely the dead-full-value preservation family.
                    nested_writes=[a for a in accesses if a[0]<i and a[2]==path and a[3]]
                    full_writes=[a for a in accesses if a[0]<i and '.' not in a[2] and a[3] and a[1]!=name]
                    if nested_writes and full_writes:
                        emit('UNION-PARTIAL','REFUSE-LIKELY',ts[nested_writes[-1][0]],'%s partial write/read-back of %s can preserve a dead whole value; the direct scalar expression would do.'%(v.name,path),v.name,[ts[i].line])
    stmts=list(src.statements())
    stores=[]
    for st in stmts:
        depth=0;eq=None
        for n,t in enumerate(st):
            if t.value in ('(','[','{'):depth+=1
            elif t.value in (')',']','}'):depth-=1
            elif depth==0 and t.value in ASSIGN:eq=n;break
        if eq is None:
            sv=values(st)
            # A discarded arithmetic result is a value-only statement. Calls,
            # declarations, control flow, and explicit (void) markers are kept.
            declaration=bool(sv and sv[0] in types|QUALIFIERS|{'struct','union','enum'})
            calls=any(t.value=='(' and n and re.fullmatch(r'[A-Za-z_]\w*',st[n-1].value) and st[n-1].value not in types for n,t in enumerate(st))
            if not declaration and not calls and not any(x in sv for x in CONTROL|{'++','--','volatile','void'}) and any(x in sv for x in ('+','-','^','|','&','/','%','<<','>>')):
                emit('DISCARDED-VALUE','REFUSE-LIKELY',st[0],'Arithmetic result is computed and never consumed; inspect whether this is an artificial dependency.','expression')
            continue
        lhs=strip_parens(st[:eq]);rhs=strip_parens(st[eq+1:]);op=st[eq].value
        if not lhs or not rhs:continue
        if values(lhs)==values(rhs) and op=='=':
            emit('SELF-ASSIGN','REFUSE-LIKELY',lhs[0],'Self assignment has no value effect; decision 39 requires a retail-evidenced read and site comment.',spelling(lhs))
        if op=='=' and (any(x.value in ('.','->','[','*') or x.value.startswith('D_') for x in lhs)):
            stores.append((lhs,rhs,st))
            simple=simple_value(rhs,types)
            if len(simple)==1:
                v=next((v for v in src.variables if v.name==simple[0].value and v.index<src.tokens.index(simple[0])<v.end),None)
                if v:
                    preceding=[(i,r,op) for i,r,op in v.writes if ts[i].offset<st[0].offset and op=='=']
                    if preceding and values(strip_parens(preceding[-1][1]))==values(lhs):
                        emit('READ-WRITEBACK','REFUSE-LIKELY',lhs[0],'Read followed by unchanged write-back through %s; decision 39 needs site-specific retail evidence.'%v.name,spelling(lhs),[ts[preceding[-1][0]].line])
        rv=values(simple_value(rhs,types))
        # Cancellation requires the same syntactic operand; no algebra across
        # function calls or volatile accesses is treated as a certainty.
        if len(rv)==3 and rv[0]==rv[2] and rv[1] in ('^','-') and re.fullmatch(r'[A-Za-z_]\w*',rv[0]):
            emit('FAKE-DEPENDENCY','REFUSE-LIKELY',rhs[0],'Expression %s cancels its operand.'%' '.join(rv),spelling(lhs))
        if len(rv)>=5 and rv[-4]=='+' and rv[-2]=='-' and rv[-3]==rv[-1] and re.fullmatch(r'[A-Za-z_]\w*',rv[-1]):
            emit('FAKE-DEPENDENCY','REFUSE-LIKELY',rhs[0],'Expression adds and subtracts the same value.',spelling(lhs))
    previous_stores = {}
    for lhs2,rhs2,st2 in stores:
        key=values(lhs2);previous=previous_stores.get(key);previous_stores[key]=(lhs2,rhs2,st2)
        if previous is None:continue
        lhs,rhs,st=previous
        identical=values(rhs)==values(rhs2)
        a=ts.index(st[-1]);b=ts.index(st2[0]);middle=values(ts[a+1:b])
        if any(x in middle for x in ('{','}','if','else','case','for','while','goto','return')):continue
        if any(x == '(' and n and re.fullmatch(r'[A-Za-z_]\w*',middle[n-1]) and middle[n-1] not in types|{'sizeof'} for n,x in enumerate(middle)):continue
        volatile_destination='volatile' in values(lhs) or any('volatile' in v.type and v.name in values(lhs) for v in src.variables)
        if volatile_destination:continue  # The compiler must retain qualified accesses.
        if identical:
            emit('REPEATED-STORE','REFUSE-LIKELY',lhs2[0],'Repeated identical store, with no intervening control/call; inspect whether retail emits it.',spelling(lhs),[lhs[0].line])
        elif 'volatile' not in values(lhs) and not any('volatile' in v.type and v.name in values(lhs) for v in src.variables):
            # A syntactic intervening read invalidates this inference. Different
            # memory aliases remain a documented limitation of the advisory.
            sequence=values(ts[a+1:b])+values(rhs2)
            target=values(lhs)
            consumed=any(sequence[n:n+len(target)]==target for n in range(len(sequence)))
            if not consumed:
                emit('DEAD-STORE','REFUSE-LIKELY',lhs[0],'Store is overwritten at line %d with no intervening syntactic read/control/call; inspect aliases, qualifiers, and retail emission.'%lhs2[0].line,spelling(lhs),[lhs2[0].line])
    for first, second in zip(stmts, stmts[1:]):
        av, bv = values(first), values(second)
        if len(av) == len(bv) == 3 and av[0] == bv[0] and av[2] == bv[2] and (av[1], bv[1]) in (('+=', '-='), ('-=', '+='), ('^=', '^=')):
            ia = ts.index(first[-1]); ib = ts.index(second[0])
            if values(ts[ia+1:ib]) == (';',):
                emit('CANCELLED-UPDATE', 'REFUSE-LIKELY', first[0],
                     'Adjacent inverse updates cancel the value; inspect retail evidence before admitting this dependency.', av[0], [second[0].line])
    # Balanced branch-arm comparisons avoid matching text across nested arms.
    def arm(i):
        if i>=len(ts):return None,None
        if ts[i].value=='{':return ts[i+1:src.pair[i]],src.pair[i]+1
        j=i
        while j<len(ts) and ts[j].value!=';':
            if ts[j].value in ('(','['):j=src.pair[j]+1
            else:j+=1
        return ts[i:j],j+1
    for i,t in enumerate(ts):
        if t.value=='if' and i+1<len(ts) and ts[i+1].value=='(':
            end=src.pair[i+1];left,nxt=arm(end+1)
            if nxt is not None and nxt<len(ts) and ts[nxt].value=='else':
                right,_=arm(nxt+1)
                if left and right and values(left)==values(right):emit('IDENTICAL-ARMS','REFUSE-LIKELY',t,'Both branch arms have identical tokenized actions; the condition is a steering dependency.','branch')
        if t.value=='volatile':emit('VOLATILE','REVIEW',t,'Volatile qualifier/access changed; inspect the retail/effect justification.','volatile')
        if t.value in ('asm','__asm','__asm__'):emit('ASM','REFUSE-LIKELY',t,'Inline asm is an explicit compiler-steering lever.','asm')
        if t.value=='do':
            body,nxt=arm(i+1)
            if nxt and nxt+1<len(ts) and ts[nxt].value=='while' and ts[nxt+1].value=='(':
                end=src.pair[nxt+1];cond=values(strip_parens(ts[nxt+2:end]))
                if cond in (('0',),('false',)):emit('ONE-TRIP','REVIEW',t,'One-trip do/while block; inspect scaffold debt and whether this block was added.','do/while(0)')
    return out


def signatures(base,candidate):
    old={f.name:f for f in base.functions};out=[]
    normalize=lambda xs:tuple('s32' if x=='M2C_UNK' else x for x in xs)
    for f in candidate.functions:
        before=old.get(f.name)
        if before and (before.ret!=f.ret or before.args!=f.args):
            out.append(_issue('NEEDS-CONTEXT', 'REVIEW' if len(before.args)!=len(f.args) and (before.defined or before.args) else 'INFO',f.token,
                'Signature/prototype changed for %s (%s %s -> %s %s). Decision 45(e) needs reach/ABI context; callback entry arguments may be real.'%(f.name,' '.join(before.ret),before.args,' '.join(f.ret),f.args),f.name))
    return out



def call_arities(src):
    declarations={f.token.offset for f in src.functions};counts=defaultdict(Counter);sites={}
    ts=src.tokens
    for i,t in enumerate(ts[:-1]):
        if not re.fullmatch(r'[A-Za-z_]\w*',t.value) or ts[i+1].value!='(':continue
        if t.offset in declarations or t.value in CONTROL|src.types|{'__attribute__','asm','__asm','__asm__','ASM_REG','ASM_KEEP'}:continue
        if t.value.isupper():continue  # macro invocations are not ABI calls
        end=src.pair[i+1];arguments=split_top(ts[i+2:end]);arity=0 if arguments==[[]] else len(arguments)
        counts[t.value][arity]+=1;sites[(t.value,arity)]=t
    return counts,sites


def arity_findings(base,candidate):
    old,_=call_arities(base);new,sites=call_arities(candidate);out=[]
    for callee,arities in new.items():
        if callee not in old:continue
        for arity in arities:
            if arity not in old[callee]:
                out.append(_issue('NEEDS-CONTEXT','REVIEW',sites[(callee,arity)],
                    'Call to %s changes arity (%s -> %d); check caller/callee and callback reach before treating added arguments as fake.'%(callee,sorted(old[callee]),arity),callee))
    return out


def read_small(path):
    path=Path(path)
    if path.stat().st_size>LIMIT:raise ValueError('input exceeds 4 MiB: '+str(path))
    return path.read_text(encoding='utf-8')


class Repository:
    """Exact registry, selected include closure, and selected callee files only."""
    def __init__(self,root):
        self.root=Path(root).resolve();self._rows=None;self._headers={};self._symbol_tables={}

    def rows(self):
        if self._rows is None:
            path=self.root/'ledger/rows.jsonl'
            # The canonical derived registry can exceed 4 MiB; stream this one
            # explicitly named file, never recursive-search it.
            with path.open() as stream:self._rows=[json.loads(l) for l in stream if l.strip()]
        return self._rows

    def row(self,name):
        matches=[r for r in self.rows() if name in (r['id'],r.get('func'),r.get('true_name'),r['id'].split('/')[-1])]
        if len(matches)!=1:raise ValueError('row must resolve uniquely: '+name)
        return matches[0]

    def source_path(self,row):
        container=row.get('container',row['id'].split('/')[0]);name=Path(row.get('c_path') or (row['id']+'.c')).name
        return layout_row_path(row['id'], self.root)

    def header(self,name):
        if name not in self._headers:
            path=Path(name)
            if path.is_absolute() or '..' in path.parts:raise ValueError('unsafe include: '+name)
            p=self.root/'include'/path
            self._headers[name]=read_small(p) if p.is_file() else ''
        return self._headers[name]

    def symbols(self,row=None):
        paths=['config/slus_006.14.symbols.txt']
        if row and row.get('gate_config'):
            config=Path(row['gate_config'])
            if config.is_absolute() or '..' in config.parts:raise ValueError('unsafe gate config')
            p=self.root/config
            if p.is_file():
                match=re.search(r'^\s*symbol_addrs_path:\s*[\"\']?([^\s\"\']+)',read_small(p),re.M)
                if match:paths.append(match[1])
        result={}
        for name in paths:
            p=Path(name)
            if p.is_absolute() or '..' in p.parts:raise ValueError('unsafe symbol table')
            if name not in self._symbol_tables:
                table={};path=self.root/p
                if path.is_file():
                    for symbol,value in re.findall(r'^\s*([A-Za-z_]\w*)\s*=\s*(0[xX][0-9a-fA-F]+)',read_small(path),re.M):table[int(value,16)]=symbol
                self._symbol_tables[name]=table
            result.update(self._symbol_tables[name])
        return result

    def include_findings(self,src):
        available=set(TYPE_WORDS)-set('s8 u8 s16 u16 s32 u32 s64 u64 f32 f64'.split());out=[];seen=set()
        def visit(text,origin=None):
            # Keep order: collecting all typedef names first hides the exact
            # preinclude bug that caused six rejects in review1.
            clean=re.sub(r'/\*[\s\S]*?\*/|//[^\n]*',lambda m:'\n'*m.group().count('\n'),text)
            ts=lex(text);parsed=Source(text)
            typedefs=defaultdict(list)
            for name in parsed.types-TYPE_WORDS:
                for t in ts:
                    if t.value==name:typedefs[t.line].append(name);break
            for lineno,line in enumerate(clean.splitlines(),1):
                m=re.match(r'\s*#\s*include\s*"([^"\n]+)"',line)
                if m:
                    name=m[1]
                    if name not in seen:
                        seen.add(name);visit(self.header(name),origin or Tok(name,0,lineno))
                match=re.search(r'\btypedef\s+(s8|u8|s16|u16|s32|u32)\s+([A-Za-z_]\w*)\s*;',line)
                if match and match[1] not in available and origin:
                    out.append(_issue('HEADER-ORDER','REFUSE-LIKELY',origin,'Header typedef %s requires %s before this include; preincluded carrier headers can hide this error.'%(match[2],match[1]),origin.value))
                # Builtin scalar typedefs (also on lines defining several).
                for m in re.finditer(r'\btypedef\s+(?:(?:unsigned|signed|long|short|char|int|float|double)\s+)+([A-Za-z_]\w*)\s*;',line):available.add(m[1])
                available.update(typedefs.get(lineno,[]))
        visit(src.text)
        for f in src.functions:
            for ty in [f.ret,*f.args]:
                for position,name in enumerate(ty):
                    if position and ty[position-1] in ('struct','union','enum'):continue  # C tags do not require typedef aliases.
                    if re.fullmatch(r'[A-Z][A-Za-z_]\w*',name) and name not in available|src.types|{'NULL'} and not name.startswith(('ASM_','M2C_')):
                        out.append(_issue('MISSING-TYPE','REFUSE-LIKELY',f.token,'Type %s in declaration of %s has no local or included typedef.'%(name,f.name),name))
        return out

    def context_findings(self,row,base,src):
        out=[];old={f.name:f for f in base.functions}
        for f in src.functions:
            if f.defined:continue
            before=old.get(f.name)
            if before and before.ret==f.ret and before.args==f.args:continue
            matches=[r for r in self.rows() if r.get('true_name')==f.name or r.get('func')==f.name or r['id'].split('/')[-1]==f.name]
            same=[r for r in matches if r.get('container')==row.get('container') and r.get('gate_config')==row.get('gate_config')]
            # Global engine helpers with an explicitly registered unique name
            # may be consumed from another bank. Duplicate overlay names need
            # the reach oracle; never pick the first matching function.
            if len(same)==1:target=same[0]
            elif len(matches)==1:target=matches[0]
            else:continue
            path=self.source_path(target)
            if not path.is_file():continue
            definitions=[d for d in Source(read_small(path)).functions if d.defined and d.name in (f.name,target.get('func'),target['id'].split('/')[-1])]
            if len(definitions)!=1:continue
            real=definitions[0]
            norm=lambda ty:tuple('s32' if x=='M2C_UNK' else x for x in ty)
            if norm(f.ret)!=norm(real.ret) and all(x in TYPE_WORDS or x in {'*'} for x in (*f.ret,*real.ret)):
                out.append(_issue('DECLARATION-CONFLICT','REFUSE-LIKELY',f.token,'Declared return %s for %s conflicts with %s in registered %s:%d. Confirm reach before correcting ABI.'%(' '.join(f.ret),f.name,' '.join(real.ret),str(path.relative_to(self.root)),real.token.line),f.name))
        return out


def literal_findings(base,src,repo=None,row=None):
    out=[];ts=src.tokens;symbols=set(re.findall(r'\bD_([0-9A-Fa-f]{8})\b',base.text+src.text))
    known=repo.symbols(row) if repo else {}
    symbols.update('%08X'%address for address in known)
    for i,t in enumerate(ts):
        if not re.fullmatch(r'(?:0[xX][0-9A-Fa-f]{8}|[0-9]{8,10})[uUlL]*',t.value):continue
        raw=t.value.rstrip('uUlL');address=int(raw,16 if raw.lower().startswith('0x') else 10);page=address>=0x80000000 and (address&0xffff)==0
        normalized='%08X'%address
        # Require a nearby pointer cast or a pointer declaration initializer,
        # so 0x80000000 masks and numeric tag constants are not "addresses".
        recent=ts[max(0,i-14):i];ptr=bool(re.search(r'\([^;{}]*\*[^;{}]*\)\s*$',spelling(recent)))
        var=next((v for v in src.variables if any(x.offset==t.offset for x in v.initializer) and '*' in v.type),None)
        if not ptr and not var:continue
        if not var:
            for v in src.variables:
                if any(any(x.offset==t.offset for x in rhs) for _,rhs,_ in v.writes):var=v;break
        genuine=0
        if var:
            for ri in var.reads:
                # Dereference, array, or typed field access. Mere copies to
                # another local never count as decision-44 genuine uses.
                start=max((n for n in range(var.index+1,ri) if ts[n].value in (';','{','}')),default=var.index)+1
                prefix=ts[start:ri]
                dereference=any(t.value=='*' and (n==0 or prefix[n-1].value in ('=','(','return',',','+','-','|','&','?',':')) for n,t in enumerate(prefix))
                if ts[ri+1].value in ('->','[') or dereference:genuine+=1
        if page and genuine>=2:
            out.append(_issue('INTEGER-PAGE','INFO',t,'Integer page pointer has %d genuine accesses: decision 44 allows it subject to site citation and required proofs.'%genuine,var.name if var else raw))
        elif page or normalized in {s.upper() for s in symbols}:
            out.append(_issue('LITERAL-ADDRESS','REFUSE-LIKELY',t,'Literal address %s %s; use a symbol or supply decision-44 save-dependence/context evidence.'%(raw,('has known symbol '+known.get(address,'D_'+normalized)) if not page else 'has fewer than two directly evidenced page accesses'),var.name if var else raw))
    for finding in out:
        token=next(t for t in ts if t.offset==finding['offset'])
        raw=token.value.rstrip('uUlL');finding['address']=int(raw,16 if raw.lower().startswith('0x') else 10)
    return out


def analyze(base_text,candidate_text,row='',repository=None,row_record=None):
    """Pure source comparison API; optional repository enables bounded context."""
    base=Source(base_text);cand=Source(candidate_text)
    old=local_findings(base)+literal_findings(base,base,repository,row_record)
    findings=local_findings(cand)+literal_findings(base,cand,repository,row_record)
    if repository:
        old+=repository.include_findings(base)
        findings+=repository.include_findings(cand)
        if row_record:findings+=repository.context_findings(row_record,base,cand)
    # Comparing lexical symptoms, not row IDs/review verdicts, keeps the
    # calibration honest. New unused declarations remain REFUSE-LIKELY.
    fingerprint=lambda f:(f['code'],f['subject'],re.sub(r'line \d+','line <n>',f['message']))
    baseline=Counter(fingerprint(f) for f in old)
    seen=Counter();seen_addresses=Counter();old_addresses=Counter(f['address'] for f in old if 'address' in f);lines=candidate_text.splitlines()
    # Added scaffold tokens need token-diff evidence (counts alone miss moves
    # and replacement qualifiers). Inherited occurrences are INFO by identity.
    for f in findings:
        key=fingerprint(f);seen[key]+=1
        inherited=seen[key]<=baseline[key]
        if 'address' in f:
            seen_addresses[f['address']]+=1
            inherited=inherited or seen_addresses[f['address']]<=old_addresses[f['address']]
        if inherited and f['severity']!='INFO' and f['code'] not in ('UNUSED-LOCAL','UNUSED-TYPEDEF'):
            f['severity']='INFO';f['inherited']=True
        else:f['inherited']=inherited
        f['evidence']=lines[f['line']-1].strip() if 0<f['line']<=len(lines) else ''
        f['column']=f.pop('offset')-sum(len(l)+1 for l in lines[:f['line']-1])+1
    for f in signatures(base,cand)+arity_findings(base,cand):
        f['evidence']=lines[f['line']-1].strip();f['column']=1;f.pop('offset');f['inherited']=False;findings.append(f)
    # Decision 39 explicitly admits an unchanged writeback keeping a retail
    # read. Decision 45 explicitly admits an existing set-but-unused local.
    # These comments lower severity to INFO pending the required byte proof;
    # they never make an ABI change cease to need context.
    for f in findings:
        neighborhood='\n'.join(lines[max(0,f['line']-5):min(len(lines),f['line']+4)])
        if f['code']=='VOLATILE' and repository and not f['inherited']:
            symbols=set(re.findall(r'\bD_[0-9A-Fa-f]{8}\b',f['evidence']))
            header_text='\n'.join(repository._headers.values())
            qualified=set(re.findall(r'struct\s*\{\s*volatile[^}]*\}\s*(\w+)',header_text))
            for statement in base.statements():
                st=spelling(statement)
                if any('. '+name+' .' in st for name in qualified) and symbols & set(re.findall(r'\bD_[0-9A-Fa-f]{8}\b',st)):
                    f['severity']='INFO';f['message']+=' Baseline reads the same symbol through an included volatile field; inspect the alias/width equivalence.';break
        if f['code'] in ('SELF-ASSIGN','READ-WRITEBACK') and re.search(r'decision\s*39|retail[^\n]*(?:read|write.back)',neighborhood,re.I):
            f['severity']='INFO';f['message']+=' Site claims decision-39 evidence; verify the receipt.'
        if f['code']=='UNUSED-LOCAL' and re.search(r'retail[^\n]*frame[^\n]*(?:unused|reserve)',neighborhood,re.I):
            f['severity']='INFO';f['message']+=' Site claims retail frame storage; verify the frame proof.'
        if f['code']=='UNUSED-LOCAL':
            existed=any(v.name==f['subject'] for v in base.variables)
            ts=cand.tokens
            for i,t in enumerate(ts):
                if not existed or t.value!='if' or i+1>=len(ts) or ts[i+1].value!='(':continue
                end=cand.pair[i+1];start=end+1
                if start>=len(ts):continue
                if ts[start].value=='{':arm_end=cand.pair[start];body=ts[start+1:arm_end];after=arm_end+1
                else:
                    arm_end=next((k for k in range(start,len(ts)) if ts[k].value==';'),len(ts));body=ts[start:arm_end];after=arm_end+1
                if after<len(ts) and ts[after].value=='else':continue
                bodyv=values(body)
                site='\n'.join(lines[max(0,t.line-5):min(len(lines),t.line+3)])
                if len(bodyv)>=3 and bodyv[:2]==(f['subject'],'=') and bodyv.count(';')<=1 and re.search(r'decision\s*45',site,re.I):
                    f['severity']='INFO';f['message']+=' Existing local set in a cited one-arm decision-45 site; verify retail evidence, pin count, and ABI context.';break
    unique={}
    for f in findings:unique.setdefault((f['code'],f['line'],f['subject'],f['severity']),f)
    findings=sorted(unique.values(),key=lambda f:(SEVERITIES.index(f['severity']),f['line'],f['code']))
    counts=dict(Counter(f['severity'] for f in findings));highest=next((s for s in SEVERITIES if counts.get(s)),None)
    context_available=repository is not None and (repository.root/'tools/lanes/lanekit/context_oracle.py').is_file()
    return {'version':1,'row':row,'advisory':True,'reviewer':'pending',
            'base_sha256':hashlib.sha256(base_text.encode()).hexdigest(),
            'candidate_sha256':hashlib.sha256(candidate_text.encode()).hexdigest(),
            'counts':{s:counts.get(s,0) for s in SEVERITIES},'severity':highest,'flags':findings,
            'context_hint':('context_oracle.py reach '+row if context_available else 'Check callback registration and callers; use context_oracle.py reach when installed') if any(f['code']=='NEEDS-CONTEXT' for f in findings) else None,
            'limitations':['Lexical/statement analysis does not prove retail stores, aliasing, complete C semantics, or ABI reach.']}


def advisory_line(result):
    counts=result['counts'];summary=', '.join('%d %s'%(counts[s],s) for s in SEVERITIES if counts[s]) or 'no source levers detected'
    top=next((f for f in result['flags'] if f['severity']!='INFO'),None)
    return 'lever-check advisory: '+summary+('; line %d %s: %s'%(top['line'],top['code'],top['evidence']) if top else '')+'; staging remains allowed'


def stage_advisory(row,base,text,out=print,root=None):
    """lab.py hook: analysis failure must never alter staging eligibility."""
    try:
        repo=Repository(root) if root else None
        result=analyze(base,text,row['id'],repo,row)
        out('  '+advisory_line(result));return result
    except Exception as exc:  # Advisory analysis must not become a staging gate.
        out('  lever-check advisory: NEEDS-CONTEXT (analysis incomplete: %s); staging remains allowed'%exc)
        return {'advisory':True,'reviewer':'pending','error':str(exc)}


def check_file(repo,row_name,candidate,base_path=None):
    row=repo.row(row_name);candidate=Path(candidate)
    base=Path(base_path) if base_path else repo.source_path(row)
    result=analyze(read_small(base),read_small(candidate),row['id'],repo,row)
    result.update(candidate=str(candidate),base=str(base))
    guard=candidate.with_name(candidate.name+'.base_sha')
    if guard.is_file():
        expected=read_small(guard).strip()
        if expected!=result['base_sha256']:
            result['freshness']={'status':'NEEDS-REBASE','expected_sha256':expected,'actual_sha256':result['base_sha256']}
        else:result['freshness']={'status':'fresh'}
    return result


def print_report(result):
    print(result['row']+': '+advisory_line(result))
    for f in result['flags']:
        print('  %s %s:%d:%d %s — %s\n    %s'%(f['severity'],result.get('candidate','candidate'),f['line'],f['column'],f['code'],f['message'],f['evidence']))
    if result.get('freshness'):print('  freshness: '+result['freshness']['status'])
    if result.get('context_hint'):print('  NEEDS-CONTEXT: '+result['context_hint'])


def main(argv=None):
    ap=argparse.ArgumentParser(description=__doc__,formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('row',nargs='?');ap.add_argument('candidate',nargs='?',type=Path)
    ap.add_argument('--root',type=Path,default=Path(__file__).resolve().parents[3])
    ap.add_argument('--base',type=Path);ap.add_argument('--json',action='store_true')
    ap.add_argument('--check',nargs='+',type=Path,metavar='OUT_DIR')
    args=ap.parse_args(argv);repo=Repository(args.root);reports=[];errors=[]
    try:
        if args.check:
            if args.row or args.candidate or args.base:ap.error('--check cannot be combined with row/candidate/--base')
            files=[]
            for directory in args.check:
                if not directory.is_dir():raise ValueError('missing out directory: '+str(directory))
                selected=sorted(directory.glob('*/*.c'))
                if not selected:raise ValueError('out directory contains no container/*.c: '+str(directory))
                files.extend(selected)
            for path in files:
                name=path.parent.name+'/'+path.stem
                try:reports.append(check_file(repo,name,path))
                except Exception as exc:errors.append({'row':name,'candidate':str(path),'error':str(exc)})
        else:
            if not args.row or not args.candidate:ap.error('provide ROW candidate.c or --check OUT_DIR')
            reports.append(check_file(repo,args.row,args.candidate,args.base))
    except Exception as exc:errors.append({'error':str(exc)})
    if args.json:print(json.dumps({'version':1,'advisory':True,'reviewer':'pending','reports':reports,'errors':errors},indent=2))
    else:
        for result in reports:print_report(result)
        for error in errors:print('lever-check: incomplete: '+error['error'],file=sys.stderr)
    if errors or any(r.get('freshness',{}).get('status')=='NEEDS-REBASE' for r in reports):return 2
    if args.check and any(r['counts']['REFUSE-LIKELY'] for r in reports):return 1
    return 0


if __name__=='__main__':raise SystemExit(main())
