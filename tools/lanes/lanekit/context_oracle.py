#!/usr/bin/env python3
"""Read-only PSX context oracle. Retail evidence is distinct from C and inference.

Uses only the standard library. All reports go to stdout unless --out is given.
No compiler, registry writer, lander, or gate is called. See TOOLS.md for limits.
"""
from __future__ import annotations

import argparse
from bisect import bisect_right
from collections import Counter, defaultdict, deque
import csv
from dataclasses import dataclass, replace
import hashlib
import io
import json
from pathlib import Path
import re
import struct

REGS = ('zero at v0 v1 a0 a1 a2 a3 t0 t1 t2 t3 t4 t5 t6 t7 '
        's0 s1 s2 s3 s4 s5 s6 s7 t8 t9 k0 k1 gp sp fp ra').split()
ARGS = (4, 5, 6, 7)
WATCH = (2, 3, 4, 5, 6, 7)
VOLATILE = (1, 2, 3, *range(4, 16), 24, 25, 31)
KW = {'if', 'while', 'for', 'switch', 'return', 'sizeof', '__attribute__',
      'asm', '__asm__', 'ASM_REG', 'ASM_KEEP', 'ASM_USE'}
MAX_INPUT = 4 * 1024 * 1024

def integer(x):
    return int(x, 0) if isinstance(x, str) else int(x)

def hx(x):
    return None if x is None else f'0x{x & 0xffffffff:08X}'

def jsonl(path):
    if not path.exists():
        return []
    with path.open() as f:
        return [json.loads(s) for s in f if s.strip() and not s.lstrip().startswith('#')]

def text_of(path):
    if path.stat().st_size > MAX_INPUT:
        raise ValueError(f'text exceeds 4 MiB limit: {path.name}')
    return path.read_text(errors='replace')

def strip_c(text):
    # Keep offsets/newlines; string literals cannot create fake functions/calls.
    return re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',
                  lambda m: re.sub(r'[^\n]', ' ', m.group()), text, flags=re.S)

def balanced(s, start, left='(', right=')'):
    depth = 0
    for i in range(start, len(s)):
        if s[i] == left:
            depth += 1
        elif s[i] == right:
            depth -= 1
            if depth == 0:
                return s[start+1:i], i
    return None

def split_args(s):
    if not s.strip():
        return []
    out, start, depth = [], 0, 0
    for i, c in enumerate(s):
        if c in '([{':
            depth += 1
        elif c in ')]}':
            depth -= 1
        elif c == ',' and depth == 0:
            out.append(s[start:i].strip()); start = i+1
    out.append(s[start:].strip())
    return out

def signatures(text):
    """Lexical declarations/definitions; () is unspecified, never zero arity.

    This is deliberately not a preprocessor. Multiple conditional declarations
    remain alternatives. Function-pointer declarators and K&R definitions are
    reported as unsupported rather than assigned an invented prototype.
    """
    s = strip_c(text); out = []
    rx = r'(?m)^[ \t]*((?:[A-Za-z_]\w*[ \t\n]+|\*[ \t]*)+)([A-Za-z_]\w*)\s*\('
    for m in re.finditer(rx, s):
        name = m.group(2)
        if name in KW or m.group(1).strip() in KW:
            continue
        b = balanced(s, m.end()-1)
        if not b:
            continue
        end = b[1]+1
        # Attributes can occur after the parameter list.
        while re.match(r'\s*__attribute__\s*\(', s[end:]):
            a = re.match(r'\s*__attribute__\s*\(', s[end:])
            ab = balanced(s, end+a.end()-1)
            if not ab:
                break
            end = ab[1]+1
        tail = s[end:].lstrip()
        if not tail.startswith((';', '{')):
            continue
        params = split_args(b[0]); params = [] if params == ['void'] else params
        body_start = end + len(s[end:]) - len(tail) if tail.startswith('{') else None
        body_end = balanced(s, body_start, '{', '}')[1] if body_start is not None and balanced(s, body_start, '{', '}') else None
        out.append({'name': name, 'params': params, 'arity': None if not b[0].strip() else len([p for p in params if p != '...']),
                    'variadic': '...' in params, 'return': ' '.join(m.group(1).split()),
                    'noreturn': bool(re.search(r'\bnoreturn\b', text[m.start():end])),
                    'definition': body_start is not None, 'start': m.start(), 'end': end,
                    'body_start': body_start, 'body_end': body_end,
                    'line': text.count('\n', 0, m.start())+1})
    return out

def statement_head(pre):
    """Drop statement-level prefixes (labels, closing braces, control heads) from
    the text between the previous statement boundary and a call, so that only
    text that can actually consume the call's value remains.

    A `case X:`/`default:`/`label:` colon is a label only at the start of the
    statement: a ternary colon (`a ? b : f()`) has its `?` earlier in the same
    text and is never stripped.  `if (..)`, `while (..)`, `for (..)`, `else` and
    `do` heads and the tail of a `for (a; b; c)` header are not value uses.
    """
    pre = pre.strip()
    while True:
        old = pre
        pre = pre.lstrip('} \t\r\n')
        m = re.match(r'(?:else|do)\b\s*', pre)
        if m:
            pre = pre[m.end():]
        m = re.match(r'(?:if|while|for|switch)\s*\(', pre)
        if m:
            b = balanced(pre, m.end()-1)
            if b:
                pre = pre[b[1]+1:].lstrip()
        m = re.match(r'case\b', pre)
        if m:
            depth = q = 0; cut = None
            for i in range(m.end(), len(pre)):
                c = pre[i]
                if c in '([{':
                    depth += 1
                elif c in ')]}':
                    depth -= 1
                elif depth == 0 and c == '?':
                    q += 1
                elif depth == 0 and c == ':':
                    if q:
                        q -= 1
                    else:
                        cut = i; break
            if cut is not None:
                pre = pre[cut+1:].lstrip()
        m = re.match(r'(?:default|[A-Za-z_]\w*)\s*:(?!:)\s*', pre)
        if m and not re.match(r'(?:return|sizeof)\b', pre):
            pre = pre[m.end():]
        if pre.count(')') > pre.count('(') and pre.endswith(')'):
            pre = ''          # tail of a for(;;) header split at its last ';'
        if pre == old:
            return pre

def c_calls(text, sigs):
    s = strip_c(text); out = []
    for sig in sigs:
        if sig['body_end'] is None:
            continue
        a, z = sig['body_start'], sig['body_end']
        for m in re.finditer(r'\b([A-Za-z_]\w*)\s*\(', s[a+1:z]):
            name = m.group(1); start = a+1+m.start(); op = a+1+m.end()-1
            if name in KW or name.startswith('ASM_'):
                continue
            b = balanced(s, op)
            if not b or b[1] > z:
                continue
            pre = s[max(a+1, s.rfind(';', a+1, start)+1, s.rfind('{', a+1, start)+1):start].strip()
            tail = s[b[1]+1:z].lstrip()
            head = statement_head(pre)
            use = 'ignored' if not head and tail.startswith(';') else 'value'
            if re.search(r'\(\s*void\s*\)\s*$', pre):
                use = 'ignored'
            out.append({'caller': sig['name'], 'callee': name, 'arity': len(split_args(b[0])),
                        'args': split_args(b[0]), 'use': use,
                        'line': text.count('\n', 0, start)+1})
    return out

def void_return(sig):
    return bool(re.search(r'\bvoid\b',sig['return'])) and '*' not in sig['return']

@dataclass(frozen=True)
class Val:
    term: str = '?'
    const: int | None = None
    offset: int = 0
    width: str = 'unknown'
    origins: frozenset[str] = frozenset()
    roots: frozenset[int] = frozenset()
    written: bool = True
    prepared: bool = True

    def show(self):
        return {'value': hx(self.const) if self.const is not None else self.term + (f'{self.offset:+d}' if self.offset else ''),
                'width': self.width, 'origins': sorted(self.origins),
                'memory_roots': [hx(x) for x in sorted(self.roots)], 'written': self.written,
                'locally_prepared':self.prepared}

def const(n, width='word32'):
    n &= 0xffffffff
    return Val(hx(n), n, width=width)

def join(a, b):
    if a == b:
        return a
    return Val(a.term if (a.term, a.offset) == (b.term, b.offset) else '?',
               a.const if a.const == b.const else None,
               a.offset if (a.term, a.offset) == (b.term, b.offset) else 0,
               a.width if a.width == b.width else 'mixed', a.origins | b.origins,
               a.roots | b.roots, a.written and b.written, a.prepared and b.prepared)

def binary(op, a, b):
    roots = a.roots | b.roots
    for v in (a, b):
        if v.const is not None and 0x80000000 <= v.const < 0x80800000:
            roots |= {v.const}
    origins = a.origins | b.origins
    if a.const is not None and b.const is not None:
        x, y = a.const, b.const
        sx = x if x < 0x80000000 else x-0x100000000
        sy = y if y < 0x80000000 else y-0x100000000
        value = {'add': lambda: x+y, 'sub': lambda: x-y, 'or': lambda: x|y,
                 'and': lambda: x&y, 'xor': lambda: x^y, 'nor': lambda: ~(x|y),
                 'sll': lambda: x << (y & 31), 'srl': lambda: x >> (y & 31),
                 'sra': lambda: sx >> (y & 31), 'slt': lambda: int(sx < sy),
                 'sltu': lambda: int(x < y)}[op]()
        return const(value)
    if op in ('add', 'or') and b.const == 0:
        return replace(a, written=True, prepared=True)
    if op in ('add', 'or') and a.const == 0:
        return replace(b, written=True, prepared=True)
    if op == 'add' and (a.const is not None or b.const is not None):
        v, k = (b, a.const) if a.const is not None else (a, b.const)
        k = k if k < 0x80000000 else k-0x100000000
        return replace(v, offset=v.offset+k, roots=frozenset(roots), written=True, prepared=True)
    term = f'{op}({a.term},{b.term})'
    if len(term) > 100 or a.term == '?' or b.term == '?':
        term = '?'
    width = 'word32'
    if op == 'sra' and b.const in (16, 24):
        width = 'signed16-promoted' if b.const == 16 else 'signed8-promoted'
    elif op == 'and' and b.const in (255, 65535):
        width = 'unsigned8-promoted' if b.const == 255 else 'unsigned16-promoted'
    return Val(term, width=width, origins=origins, roots=frozenset(roots))

@dataclass(frozen=True)
class Insn:
    pc: int
    word: int
    mn: str
    reads: tuple[int, ...] = ()
    writes: tuple[int, ...] = ()
    rs: int = 0
    rt: int = 0
    rd: int = 0
    imm: int = 0
    target: int | None = None
    control: str = ''

def decode(word, pc):
    op, rs, rt, rd, sh, fn = word>>26, word>>21&31, word>>16&31, word>>11&31, word>>6&31, word&63
    imm = word & 65535; signed = imm if imm < 32768 else imm-65536
    mn, reads, writes, target, ctrl = 'unknown', (), (), None, ''
    if op == 0:
        if word == 0:
            mn = 'nop'
        elif fn in (0, 2, 3, 4, 6, 7):
            mn = {0:'sll',2:'srl',3:'sra',4:'sllv',6:'srlv',7:'srav'}[fn]
            reads, writes = ((rt, rs) if fn >= 4 else (rt,)), (rd,)
        elif fn in (8, 9):
            mn = 'jr' if fn == 8 else 'jalr'; reads = (rs,)
            writes = (rd,) if fn == 9 else (); ctrl = 'return' if fn == 8 and rs == 31 else ('call' if fn == 9 and rd else 'indirect-jump')
        elif fn in (12, 13):
            mn, ctrl = ('syscall' if fn == 12 else 'break'), 'trap'
        elif fn in (16, 18):
            mn, writes = ('mfhi' if fn == 16 else 'mflo'), (rd,)
        elif fn in (17, 19, 24, 25, 26, 27):
            mn = {17:'mthi',19:'mtlo',24:'mult',25:'multu',26:'div',27:'divu'}[fn]
            reads = (rs,) if fn in (17,19) else (rs, rt)
        elif fn in (32,33,34,35,36,37,38,39,42,43):
            mn = {32:'add',33:'addu',34:'sub',35:'subu',36:'and',37:'or',38:'xor',39:'nor',42:'slt',43:'sltu'}[fn]
            reads, writes = (rs, rt), (rd,)
    elif op in (2, 3):
        mn = 'j' if op == 2 else 'jal'; ctrl = 'jump' if op == 2 else 'call'
        target = (pc+4)&0xf0000000 | (word & 0x03ffffff)<<2
        writes = (31,) if op == 3 else ()
    elif op in (1,4,5,6,7):
        mn = {1:'regimm',4:'beq',5:'bne',6:'blez',7:'bgtz'}[op]
        reads = (rs,rt) if op in (4,5) else (rs,); target = pc+4+signed*4; ctrl = 'branch'
        if op == 1:
            mn = {0:'bltz',1:'bgez',16:'bltzal',17:'bgezal'}.get(rt, 'unknown')
            if rt in (16,17):
                writes = (31,); ctrl = 'conditional-call'
    elif op in (8,9,10,11,12,13,14,15):
        mn = {8:'addi',9:'addiu',10:'slti',11:'sltiu',12:'andi',13:'ori',14:'xori',15:'lui'}[op]
        reads, writes = (() if op == 15 else (rs,)), (rt,)
    elif op in (32,33,34,35,36,37,38,40,41,42,43,46,50,58):
        mn = {32:'lb',33:'lh',34:'lwl',35:'lw',36:'lbu',37:'lhu',38:'lwr',40:'sb',41:'sh',42:'swl',43:'sw',46:'swr',50:'lwc2',58:'swc2'}[op]
        reads = (rs,rt) if op in (34,38,40,41,42,43,46) else (rs,)
        writes = (rt,) if op in (32,33,34,35,36,37,38) else ()
    elif op in (16,18):
        mn = 'cop'
        if rs in (0,2):
            mn, writes = 'mfc', (rt,)
        elif rs in (4,6):
            mn, reads = 'mtc', (rt,)
        elif rs == 8:
            mn, target, ctrl = 'bcop', pc+4+signed*4, 'branch'
    return Insn(pc, word, mn, tuple(r for r in reads if r), tuple(r for r in writes if r), rs,rt,rd,sh if op == 0 else signed,target,ctrl)

@dataclass(frozen=True)
class State:
    regs: tuple[Val, ...]
    stack: tuple[tuple[int, Val], ...] = ()
    pending: tuple[int, Val] | None = None
    recent_stack_stores: tuple[int, ...] = ()

def merge_state(a, b):
    regs = [join(x, y) for x,y in zip(a.regs,b.regs)]
    am,bm = dict(a.stack),dict(b.stack)
    stack = tuple((k,join(am[k],bm[k])) for k in sorted(am.keys() & bm.keys()))
    pending = a.pending if a.pending == b.pending else None
    if a.pending and b.pending and a.pending[0] == b.pending[0]:
        pending = (a.pending[0], join(a.pending[1], b.pending[1]))
    elif a.pending != b.pending:
        for p in (a.pending,b.pending):
            if p:
                regs[p[0]] = join(regs[p[0]],p[1])
    return State(tuple(regs),stack,pending,tuple(sorted(set(a.recent_stack_stores)&set(b.recent_stack_stores))))

def analyse(words, address):
    """Bounded forward CFG interpretation, including jump and load delay slots.

    Entry reads are MAY-path witnesses. Calls kill caller-saved registers after
    their delay slot. Stack spills preserve entry provenance; loops widen to ?.
    """
    insns = [decode(w,address+i*4) for i,w in enumerate(words)]
    jump_targets = {x.target for x in insns if x.control}
    merge_pairs = {}
    for i in range(len(insns)-1):
        a,b = insns[i:i+2]
        if ({a.mn,b.mn}=={'lwl','lwr'} and a.rt==b.rt and a.rs==b.rs and a.rt!=a.rs
                and ((a.mn=='lwl' and a.imm==b.imm+3) or (b.mn=='lwl' and b.imm==a.imm+3))
                and b.pc not in jump_targets and not (i and insns[i-1].control)
                and not (i+2<len(insns) and a.rt in insns[i+2].reads)):
            merge_pairs[a.pc] = 'first';merge_pairs[b.pc] = 'complete'
    initial = State(tuple(const(0) if i == 0 else Val('entry:'+REGS[i], origins=frozenset({'entry:'+REGS[i]}), written=False, prepared=False) for i in range(32)))
    states = {0:initial}; queue = deque([0]); calls, stores, reads, unknown, return_reads = {}, {}, {}, set(), set()
    steps = 0

    def step(i, state):
        ins = insns[i]; regs = list(state.regs); mem = dict(state.stack)
        recent = set(state.recent_stack_stores)
        for r in ins.reads:
            if r in WATCH and not regs[r].written:
                reads.setdefault(r,set()).add(ins.pc)
            for origin in regs[r].origins:
                if origin.startswith('return:'):
                    return_reads.add((origin,ins.pc,REGS[r]))
        if ins.mn == 'unknown':
            unknown.add(ins.pc)
        mn = ins.mn; value = Val(); load = False
        if mn == 'lui':
            value = const((ins.word&65535)<<16)
        elif mn in ('addi','addiu','slti','sltiu','andi','ori','xori'):
            kind = {'addi':'add','addiu':'add','slti':'slt','sltiu':'sltu','andi':'and','ori':'or','xori':'xor'}[mn]
            value = binary(kind,regs[ins.rs],const(ins.word&65535 if mn in ('andi','ori','xori') else ins.imm))
        elif mn in ('add','addu','sub','subu','and','or','xor','nor','slt','sltu'):
            value = binary({'addu':'add','subu':'sub'}.get(mn,mn),regs[ins.rs],regs[ins.rt])
        elif mn in ('sll','srl','sra','sllv','srlv','srav'):
            value = binary(mn[:3],regs[ins.rt],regs[ins.rs] if mn.endswith('v') else const(ins.imm))
        elif mn in ('lb','lbu','lh','lhu','lw','lwl','lwr','sb','sh','sw','swl','swr','lwc2','swc2'):
            addr = binary('add',regs[ins.rs],const(ins.imm))
            isstack = addr.term == 'entry:sp' and addr.const is None
            if mn in ('sb','sh','sw','swl','swr','swc2'):
                key = ins.pc; rec = (addr, regs[ins.rt])
                if key in stores:
                    rec = tuple(join(x,y) for x,y in zip(stores[key],rec))
                stores[key] = rec
                if isstack and mn == 'sw':
                    mem[addr.offset] = regs[ins.rt]
                    recent.add(addr.offset)
            elif mn != 'lwc2':
                load = True
                roots = addr.roots
                if addr.const is not None:
                    roots |= {addr.const}
                width = {'lb':'signed8-promoted','lbu':'unsigned8-promoted','lh':'signed16-promoted','lhu':'unsigned16-promoted'}.get(mn,'word32')
                value = mem.get(addr.offset,Val(f'{mn}({addr.show()["value"]})', width=width,
                                               origins=addr.origins,roots=frozenset(roots))) if isstack else Val(f'{mn}({addr.show()["value"]})',width=width,origins=addr.origins,roots=frozenset(roots))
                value = replace(value,written=True,prepared=True)
                if mn in ('lwl','lwr') and merge_pairs.get(ins.pc)!='complete':
                    value = replace(value,origins=value.origins|regs[ins.rt].origins)
        elif mn in ('jal','jalr','bltzal','bgezal'):
            value = const(ins.pc+8)
        # A previous load becomes visible AFTER this instruction's reads; an
        # explicit write to the same GPR wins over that delayed load.
        if state.pending and state.pending[0] not in ins.writes:
            regs[state.pending[0]] = state.pending[1]
        for r in ins.writes:
            if not load:
                regs[r] = replace(value,written=True,prepared=True)
        pending = (ins.writes[0],value) if load and ins.writes else None
        regs[0] = const(0)
        return State(tuple(regs),tuple(sorted(mem.items())),pending,tuple(sorted(recent)))

    while queue and steps < max(100, len(words)*80):
        i = queue.popleft(); steps += 1; state = states[i]; ins = insns[i]
        # jalr's target is sampled before the delay slot.
        target_value = state.regs[ins.rs] if ins.mn in ('jalr','jr') else const(ins.target or 0)
        after = step(i,state)
        if ins.control and ins.control != 'trap' and i+1 < len(words):
            if insns[i+1].control:
                unknown.add(insns[i+1].pc)
            after = step(i+1,after)
        successors = []
        external_jump = ins.control == 'jump' and not address <= (ins.target or 0) < address+len(words)*4
        tail_dispatch = ins.control == 'indirect-jump' or external_jump
        if ins.control in ('call','conditional-call') or tail_dispatch:
            stack = dict(after.stack); sp = after.regs[29]
            stack_args = {}
            if sp.term == 'entry:sp':
                for offset in range(16,132,4):
                    key = sp.offset+offset
                    if key not in after.recent_stack_stores or key not in stack:
                        break
                    stack_args[offset] = stack[key]
            args = tuple(after.regs[r] for r in ARGS)
            old = calls.get(ins.pc)
            if old:
                args = tuple(join(x,y) for x,y in zip(old['values'],args))
                target_value = join(old['target_value'],target_value)
                stack_args = {k:join(old['stack_values'][k],v) for k,v in stack_args.items() if k in old['stack_values']}
            calls[ins.pc] = {'pc':ins.pc,'mn':ins.mn,'target':ins.target,
                             'target_value':target_value,'values':args,'stack_values':stack_args,
                             'tail_dispatch':tail_dispatch}
            regs = list(after.regs)
            for r in VOLATILE:
                regs[r] = Val('call-clobbered',written=True,prepared=False)
            for r in (2,3):
                regs[r] = Val('return:'+hx(ins.pc),origins=frozenset({'return:'+hx(ins.pc)}))
            after = State(tuple(regs),tuple((k,v) for k,v in after.stack if k not in {sp.offset+j for j in stack_args}))
            successors = [] if tail_dispatch else [i+2]
        elif ins.control in ('jump','branch'):
            if ins.target is not None and address <= ins.target < address+len(words)*4 and (ins.target-address)%4 == 0:
                successors.append((ins.target-address)//4)
            if ins.control == 'branch' and not (ins.mn == 'beq' and ins.rs == ins.rt):
                successors.append(i+2)
        elif not ins.control:
            successors = [i+1]
        for nxt in successors:
            if nxt >= len(words):
                continue
            merged = merge_state(states[nxt],after) if nxt in states else after
            if states.get(nxt) != merged:
                states[nxt] = merged; queue.append(nxt)
    for pc,c in calls.items():
        c['return_consumed'] = [{'pc':hx(p),'register':r} for origin,p,r in sorted(return_reads) if origin == 'return:'+hx(pc)]
    merge_reads = {REGS[r]:[hx(p) for p in sorted(ps)] for r,ps in reads.items()
                   if all(p in merge_pairs for p in ps)}
    return {'calls':list(calls.values()),'stores':stores,
            'entry_reads':{REGS[r]:[hx(p) for p in sorted(ps)] for r,ps in reads.items()},
            'merge_seed_entry_reads':merge_reads,
            'unknown_instructions':[hx(x) for x in sorted(unknown)],
            'converged':not queue,'reachable_words':len(states), 'insns':insns}

class Oracle:
    def __init__(self, root, manifest=None):
        self.root = Path(root).resolve(); self.inputs = {}; self.images = {}; self.functions = []
        self.by_addr = defaultdict(list); self.by_row = defaultdict(list); self.defs = defaultdict(list)
        self.maps = defaultdict(list); self.sources = {}; self.header_cache = {}
        self.calls = []; self.dispatchers = []; self.stores = []; self.word_refs = defaultdict(list); self.raw_jals = defaultdict(list)
        self.levels = {}; self.volatiles = {}; self.baseline = {}
        self.direct_by_target = defaultdict(list)
        self.pointer_args = defaultdict(list)
        self.pointer_stores = defaultdict(list)
        self.entry_stores = defaultdict(list)
        self.dispatch_by_root = defaultdict(list)
        if manifest:
            self._fixture(Path(manifest))
        else:
            self._repository()
        self._index()

    def read(self, p):
        b = p.read_bytes(); self.inputs[str(p.relative_to(self.root))] = hashlib.sha256(b).hexdigest()
        return b

    def readtext(self,p):
        if p.stat().st_size > MAX_INPUT:
            raise ValueError('text exceeds 4 MiB: '+p.name)
        return self.read(p).decode(errors='replace')

    def loadjsonl(self,p):
        if not p.exists():
            return []
        return [json.loads(s) for s in self.readtext(p).splitlines() if s.strip() and not s.lstrip().startswith('#')]

    def source(self, path):
        if path not in self.sources:
            p = self.root/path
            if not p.exists():
                self.sources[path] = ('',[],[],[]); return self.sources[path]
            t = self.readtext(p); sigs = signatures(t); headers = self.headers(p,t,set())
            self.sources[path] = (t,sigs,c_calls(t,sigs),headers)
        return self.sources[path]

    def headers(self,p,text,seen):
        result = []
        for inc in re.findall(r'^\s*#\s*include\s*["<]([^">]+)[">]',text,re.M):
            # Exact include paths only. No recursive tree search, no system headers.
            candidates = (p.parent/inc,self.root/'include'/inc)
            q = next((q for q in candidates if q.is_file() and q.resolve().is_relative_to(self.root)),None)
            if not q or q in seen:
                continue
            seen.add(q)
            if q not in self.header_cache:
                ht = self.readtext(q); self.header_cache[q] = (ht,signatures(ht))
            ht,hs = self.header_cache[q]
            result += [{**s,'path':str(q.relative_to(self.root))} for s in hs]
            result += self.headers(q,ht,seen)
        return result

    def add(self, row, container, name, address, foff, size, source, mapping='fixture'):
        address,foff,size = integer(address),integer(foff),integer(size)
        if container not in self.images or foff < 0 or size <= 0 or size % 4 or foff+size > len(self.images[container]):
            return
        if any(f['container']==container and f['foff']==foff and f['address']==address for f in self.by_row[row]):
            return
        text,sigs,cc,headers = self.source(source)
        sig = next((s for s in sigs if s['definition'] and s['name']==name),None)
        f = {'row':row,'container':container,'name':name,'address':address,'foff':foff,'size':size,
             'source':source,'signature':sig,'mapping':mapping,'c_calls':[c for c in cc if c['caller']==name],
             'prototypes':sigs+headers}
        self.functions.append(f); self.by_addr[address].append(f); self.by_row[row].append(f)
        if sig:
            self.defs[address].append(f)

    def _fixture(self, manifest):
        doc = json.loads(self.read(manifest))
        for image in doc['images']:
            self.images[image['container']] = self.read(self.root/image['file'])
        for m in doc.get('mappings',[]):
            self.maps[m['container']].append((integer(m['start']),integer(m['end']),integer(m['delta']),m.get('confidence','fixture')))
        for f in doc['functions']:
            self.add(f['row'],f['container'],f['name'],f['address'],f['foff'],f['size'],f['source'])
        self.script_tables = doc.get('script_tables',[])

    def _repository(self):
        import sys
        tools = next((p / "tools" for p in Path(__file__).resolve().parents
                      if (p / "tools/source_layout.py").is_file()), self.root / "tools")
        sys.path.insert(0, str(tools))
        from source_layout import row_relative
        names = {'main':'MAIN_MAIN.BIN','town':'TOWN_TOWN.BIN','dungeon':'DUNGEON_DUNGEON.BIN','ovmovie':'OVMOVIE_OVMOVIE.BIN'}
        missing = []
        for container,name in names.items():
            p = self.root/'work/disc/containers'/name
            if p.exists():
                self.images[container] = self.read(p)
            else:
                missing.append(container)
        p = self.root/'baserom/slus_006.14'
        if p.exists():
            self.images['slus'] = self.read(p)
            b = self.images['slus']
            if b[:8] != b'PS-X EXE':
                raise ValueError('SLUS lacks PS-X EXE header')
            load,size = struct.unpack_from('<II',b,0x18)
            self.maps['slus'].append((0x800,min(len(b),0x800+size),load-0x800,'PS-X EXE header'))
        else:
            missing.append('slus')
        self.missing_images = missing
        rows = self.loadjsonl(self.root/'ledger/rows.jsonl')
        if not rows:
            raise ValueError('no ledger rows (use --manifest for fixtures)')
        native_members = {}
        p = self.root/'config/overlays/modules.json'
        if p.exists():
            for module in json.loads(self.read(p)).get('modules',[]):
                for member in module.get('members',[]):
                    native_members[member['id']] = member
        symbol_map = {}
        p = self.root/'config/slus_006.14.symbols.txt'
        if p.exists():
            for m in re.finditer(r'^\s*(\w+)\s*=\s*(0x[0-9a-fA-F]+)\s*;[^\n]*', self.readtext(p),re.M):
                if 'type:func' in m.group():
                    symbol_map[m.group(1)] = integer(m.group(2))
        for container in names:
            for m in self.loadjsonl(self.root/f'config/overlays/{container}.rowbase.jsonl'):
                if 'delta' in m:
                    self.maps[container].append((integer(m['foff_start']),integer(m['foff_end']),integer(m['delta']),m.get('base_confidence','unknown')))
        for row in rows:
            container = row['container']; stem = row['id'].split('/')[-1]
            source = row_relative(row, self.root)
            native = native_members.get(row['id'])
            if native:
                source = native['source']
            t,sigs,_,_ = self.source(source)
            if container == 'slus':
                m = re.search(r'([0-9A-Fa-f]{8})$',stem)
                if not m or not self.maps['slus']:
                    continue
                address = int(m.group(1),16); delta = self.maps['slus'][0][2]
                # Row size bounds the physical member, not its TU's externs or
                # registry defs list (which includes declarations).
                candidates = [s for s in sigs if s['definition']]
                name = next((s['name'] for s in candidates if symbol_map.get(s['name'],self.name_address(s['name']))==address),'func_'+f'{address:08X}')
                self.add(row['id'],container,name,address,address-delta,row['size'],source,'row + PS-X EXE header')
            elif row.get('foff') is not None and row.get('row_kind') != 'data':
                name = row.get('true_name') or row.get('func') or stem
                address = self.name_address(name)
                mapping = 'row true_name' if row.get('true_name') else 'row name (may be synthetic)'
                bounds = [(z-a,d,c) for a,z,d,c in self.maps[container]
                          if a<=row['foff'] and row['foff']+row['size']<=z and c.startswith('proven')]
                if bounds:
                    _,delta,confidence = min(bounds)
                    address = row['foff']+delta
                    mapping = 'rowbase '+confidence
                    name = next((s['name'] for s in sigs if s['definition'] and self.name_address(s['name'])==address),name)
                    if len({d for _,d,_ in bounds})>1:
                        mapping += ' (conflicting containing records; narrowest chosen)'
                if address is not None:
                    if native:
                        offset = integer(native.get('body_offset',0))
                        size = integer(native['size'])
                        if offset<0 or offset>=size or offset%4:
                            raise ValueError('invalid native member body_offset: '+row['id'])
                        name = native['function'];address = integer(native['vma'])+offset
                        off = integer(native['foff'])
                        self.maps[container].append((off,off+size,integer(native['vma'])-off,'native member physical extent'))
                        self.add(row['id'],container,name,address,off+offset,size-offset,source,'native member body_offset='+str(offset))
                    else:
                        self.add(row['id'],container,name,address,row['foff'],row['size'],source,mapping)
        # Add exported resident functions not represented by C rows. Their
        # symbol boundaries are evidence, not fabricated accounting rows.
        if self.maps['slus']:
            delta = self.maps['slus'][0][2]; end = self.maps['slus'][0][1]+delta
            addresses = sorted(set(symbol_map.values()))
            for i,address in enumerate(addresses):
                if address in self.by_addr or not delta+0x800 <= address < end:
                    continue
                nxt = addresses[i+1] if i+1 < len(addresses) else end
                name = next(n for n,a in symbol_map.items() if a==address)
                self.add('slus/symbol:'+name,'slus',name,address,address-delta,nxt-address,'src/slus/__unrepresented__.c','exported symbol interval; C unavailable')
        self.levels = {r['id']:r for r in self.loadjsonl(self.root/'ledger/levels.jsonl')}
        self.volatiles = {r['id']:r for r in self.loadjsonl(self.root/'ledger/real_volatiles.jsonl')}
        p = self.root/'config/decomp_audit_baseline.json'
        if p.exists():
            self.baseline = json.loads(self.read(p))
        self.script_tables = []
        p = self.root/'ledger/evidence/fno_table.json'
        if p.exists():
            table = json.loads(self.read(p))
            self.script_tables.append({'container':'town','foff':table['file_offset'],
                                       'address':table['vram'],'entries':table['table']})

    @staticmethod
    def name_address(name):
        m = re.search(r'(?:^|_)([0-9A-Fa-f]{8})$',name or '')
        return int(m.group(1),16) if m else None

    def location(self,container,off):
        starts,funcs = self.intervals.get(container,([],[]))
        i = bisect_right(starts,off)-1
        f = funcs[i] if i>=0 and off<funcs[i]['foff']+funcs[i]['size'] else None
        if f:
            return hx(f['address']+off-f['foff']),f['row'],f['mapping']
        matches = [(z-a,d,c) for a,z,d,c in self.maps[container] if a<=off<z]
        if matches:
            _,delta,confidence = min(matches)
            return hx(off+delta),None,confidence
        # Only use a data-gap delta when BOTH neighbouring rows agree.
        if 0 <= i < len(funcs)-1:
            a,b = funcs[i],funcs[i+1]
            if a['address']-a['foff']==b['address']-b['foff'] and b['foff']-a['foff']-a['size']<=4096:
                return hx(off+a['address']-a['foff']),None,'bracketed data gap (inferred)'
        return None,None,'unmapped'

    def _index(self):
        self.intervals = {}
        for container in self.images:
            fs = sorted((f for f in self.functions if f['container']==container),key=lambda f:f['foff'])
            self.intervals[container] = ([f['foff'] for f in fs],fs)
        for f in self.functions:
            words = [x[0] for x in struct.iter_unpack('<I',self.images[f['container']][f['foff']:f['foff']+f['size']])]
            analysis = analyse(words,f['address']); f['analysis'] = analysis
            by_target = defaultdict(list)
            for c in analysis['calls']:
                c = {**c,'caller':f['row'],'caller_name':f['name'],'container':f['container'],
                     'foff':f['foff']+c['pc']-f['address'], 'function':f}
                self.calls.append(c)
                self.direct_by_target[c['target']].append(c)
                for i,v in enumerate(c['values']):
                    if v.const in self.by_addr:
                        self.pointer_args[v.const].append((c,i))
                if c['target'] is None:
                    self.dispatchers.append(c)
                    for root in c['target_value'].roots:
                        self.dispatch_by_root[root].append(c)
                else:
                    by_target[c['target']].append(c)
            for addr,cs in by_target.items():
                cc = [c for c in f['c_calls'] if self.name_address(c['callee'])==addr or any(x['name']==c['callee'] for x in self.by_addr[addr])]
                for i,c in enumerate(sorted(cs,key=lambda c:c['pc'])):
                    c['c_candidates'] = cc
                    c['c_call'] = cc[i] if len(cc)==len(cs) else None
            for pc,(addr,value) in analysis['stores'].items():
                store = {'function':f,'pc':pc,'address':addr,'value':value}
                self.stores.append(store)
                if value.const in self.by_addr:
                    self.pointer_stores[value.const].append(store)
                for origin in value.origins:
                    self.entry_stores[(id(f),origin)].append(store)
        # Exactly one sequential aligned-word read per image; never recurse
        # through work/, archives, or dump directories.
        addresses = set(self.by_addr)
        for container,b in self.images.items():
            for i,(word,) in enumerate(struct.iter_unpack('<I',b[:len(b)//4*4])):
                off = i*4
                if word in addresses:
                    self.word_refs[word].append({'container':container,'foff':hx(off),
                                                'address':self.location(container,off)[0],
                                                'owner':self.location(container,off)[1],
                                                'mapping':self.location(container,off)[2]})
                if word>>26 == 3:
                    target = 0x80000000 | (word&0x03ffffff)<<2
                    if target in addresses:
                        self.raw_jals[target].append({'container':container,'foff':hx(off),
                                                     'word':hx(word),'classification':'jal encoding; unanalysed text/data until mapped'})

    def resolve(self, query):
        if query in self.by_row:
            return self.by_row[query]
        matches = [f for f in self.functions if query in (f['name'],f['row'].split('/')[-1])]
        if not matches:
            address = self.name_address(query)
            if address is None:
                try:
                    address = integer(query)
                except ValueError:
                    pass
            matches = self.by_addr.get(address,[])
        if not matches:
            raise ValueError('no function: '+query)
        # A name used in many overlay banks remains an ambiguous query.
        return matches

    @staticmethod
    def signature(sig):
        if not sig:
            return None
        return {k:sig[k] for k in ('name','params','arity','variadic','return','noreturn','line')}

    def xrefs(self,f):
        t = self.sources[f['source']][0]; code = strip_c(t)
        reg_pins = []
        for m in re.finditer(r'ASM_REG\s*\(\s*[^,]+,\s*"?\$?(a[0-3]|[4-7])"?\s*\)',t):
            reg_pins.append(m.group(1))
        # Common macro form is ASM_REG(type, name, "reg").
        for m in re.finditer(r'ASM_REG\s*\([^;\n]*?"\$?(a[0-3]|[4-7])"',t):
            reg_pins.append(m.group(1))
        level = self.levels.get(f['row'],{})
        return {'pinned':bool(re.search(r'\bASM_\w+\s*\(',code)) or bool(level.get('pins_left')),
                'pins_left':level.get('pins_left'), 'argument_reg_pins':sorted(set(reg_pins)),
                'm2c_unk_params':bool(f['signature'] and any('M2C_UNK' in p for p in f['signature']['params'])),
                'call_arity_sites':level.get('l5_fidelity',[]),
                'volatile':bool(re.search(r'\bvolatile\b',code)),
                'volatile_ledger':self.volatiles.get(f['row'])}

    def entry(self,f):
        observed = f['analysis']['entry_reads']; sig = f['signature']; n = sig['arity'] if sig else None
        merge = f['analysis']['merge_seed_entry_reads']
        context_reads = {r:sites for r,sites in observed.items() if r not in merge}
        variadic = bool(sig and sig['variadic'])
        wide = bool(sig and any(re.search(r'\b(double|f64|s64|u64|M2C_UNK64|int64_t|uint64_t)\b|\blong\s+long\b',p) and '*' not in p for p in sig['params']))
        beyond = [r for r in ('a1','a2','a3') if r in context_reads and n is not None and int(r[1])+1>n and not variadic and not wide]
        nonstandard = [r for r in ('v0','v1') if r in context_reads]
        return {'row':f['row'],'function':f['name'],'container':f['container'],'address':hx(f['address']),
                'c_signature':self.signature(sig),'reads_before_write':observed,
                'merge_seed_entry_reads':merge,'entry_reads_requiring_context':context_reads,
                'parameter_layout':('variadic' if variadic else 'wide ABI layout unresolved' if wide else 'lexical scalar/pointer parameter count; aggregate layout may be unresolved'),
                'beyond_declared_params':beyond,'nonstandard_entry_regs':nonstandard,
                'required_register_arity_lower_bound':max([int(r[1])+1 for r in context_reads if r.startswith('a')]+[0]),
                'flags':(['hidden_parameter_or_uninitialised_local_or_pin'] if beyond else []) + (['nonstandard_entry_state'] if nonstandard else []) + (['wide_parameter_abi_layout_unresolved'] if wide else []),
                'coverage':self.coverage(f),'cross_references':self.xrefs(f)}

    @staticmethod
    def coverage(f):
        a = f['analysis']
        return {'mapping':f['mapping'],'converged':a['converged'],
                'unknown_instructions':a['unknown_instructions'],'c_definition_available':f['signature'] is not None}

    def call_record(self,c):
        values = c['values']; prepared = [REGS[r] for r,v in zip(ARGS,values) if v.prepared]
        forwarded = [REGS[r] for r,v in zip(ARGS,values) if v.term.startswith('entry:') and not v.offset and not v.roots]
        cc = c.get('c_call'); candidates = c.get('c_candidates',[])
        insns = c['function']['analysis']['insns'];index = (c['pc']-c['function']['address'])//4
        ins = insns[index]
        overlap = (c['target'] is None and ins.rs in ARGS
                   and not (index+1<len(insns) and ins.rs in insns[index+1].writes))
        flags = []; scoped = [p for p in c['function']['prototypes'] if cc and p['name']==cc['callee'] and not p['definition']]
        if cc and scoped and all(p['arity'] is None for p in scoped):
            flags.append('unspecified_prototype_default_promotions')
        elif cc and not scoped:
            if not any(p['name']==cc['callee'] for p in c['function']['prototypes']):
                flags.append('no_lexical_prototype_default_promotions_possible')
        if cc and scoped and any(p['arity'] is not None and not p['variadic'] and p['arity']!=cc['arity'] for p in scoped):
            flags.append('call_vs_local_prototype_arity')
        if cc and scoped and any(re.search(r'\bvoid\b',p['return']) and '*' not in p['return'] for p in scoped) and cc['use']=='value':
            flags.append('void_prototype_value_used')
        if scoped and any(p['noreturn'] for p in scoped):
            flags.append('noreturn_declaration_requires_control_flow_review')
        return {'caller':c['caller'],'caller_function':c['caller_name'],'container':c['container'],
                'pc':hx(c['pc']),'foff':hx(c['foff']),'instruction':c['mn'],'target':hx(c['target']),
                'tail_dispatch':c['tail_dispatch'],
                'indirect_target_register':REGS[ins.rs] if c['target'] is None else None,
                'argument_target_overlap':REGS[ins.rs] if overlap else None,
                'indirect_target':c['target_value'].show() if c['target'] is None else None,
                'argument_registers':{REGS[r]:v.show() for r,v in zip(ARGS,values)},
                'locally_prepared_registers':prepared,'entry_forwarded_registers':forwarded,
                'stack_arguments':{str(k):v.show() for k,v in sorted(c['stack_values'].items())},
                'arity':cc['arity'] if cc else None,'arity_basis':'matched C call (lexical)' if cc else 'unknown; register preparation is not exact arity',
                'c_call':cc,'c_candidates':candidates,'local_prototypes':[self.signature(s) for s in scoped],
                'return_consumed':c['return_consumed'],'flags':flags}

    def compatible(self, caller, target):
        if target['container']=='slus':
            return True
        return caller['container']==target['container']

    def callsites(self, targets):
        addresses = {f['address'] for f in targets}; reports = []
        for address in sorted(addresses):
            fs = [f for f in targets if f['address']==address]
            calls = [c for c in self.direct_by_target[address] if any(self.compatible(c['function'],f) for f in fs)]
            records = [self.call_record(c) for c in calls]
            defs = [{**self.signature(f['signature']),'row':f['row']} for f in self.defs[address] if f['signature']]
            typed = Counter(p['arity'] for rec in records for p in rec['local_prototypes'] if p['arity'] is not None)
            expected = sorted({d['arity'] for d in defs if d['arity'] is not None})
            if not expected and typed:
                expected = [typed.most_common(1)[0][0]]
            observed = sorted({r['arity'] for r in records if r['arity'] is not None})
            for r,c in zip(records,calls):
                localdefs = [d for d in self.defs[address] if self.compatible(c['function'],d)]
                ns = {d['signature']['arity'] for d in localdefs if d['signature']['arity'] is not None}
                if r['arity'] is not None and ns and r['arity'] not in ns and not any(d['signature']['variadic'] for d in localdefs):
                    r['flags'].append('call_vs_definition_arity')
                if r['arity'] is not None and not ns and expected and r['arity'] not in expected:
                    r['flags'].append('call_vs_modal_typed_prototype_arity')
                if r['c_call'] and r['c_call']['use']=='value' and any(void_return(d['signature']) for d in localdefs):
                    r['flags'].append('void_definition_value_used')
                localvoid = [void_return(p) for p in r['local_prototypes']]
                defvoid = [void_return(d['signature']) for d in localdefs]
                if localvoid and defvoid and set(localvoid).isdisjoint(defvoid):
                    r['flags'].append('void_value_return_type_disagreement')
                if not c['tail_dispatch'] and any(d['signature']['noreturn'] for d in localdefs) and c['pc']+8 < c['function']['address']+c['function']['size']:
                    r['flags'].append('noreturn_definition_has_retail_continuation')
            reports.append({'address':hx(address),'rows':[f['row'] for f in fs],
                            'definitions':defs,'expected_arities':expected,
                            'expected_basis':'definitions (bank alternatives)' if defs else 'modal lexical typed prototype; definition unavailable',
                            'observed_c_arities':observed,'arity_disagreement':len(observed)>1 or any(r['flags'] and any('arity' in x for x in r['flags']) for r in records),
                            'callsites':records,'raw_jal_encodings':self.raw_jals[address]})
        return reports

    def dispatch_match(self,c, roots):
        return bool(c['target_value'].roots & roots)

    def reach(self,f):
        address = f['address']; direct = [self.call_record(c) for c in self.direct_by_target[address] if self.compatible(c['function'],f)]
        refs = self.word_refs[address]; registrations = []; bindings = []; dispatch = []
        for c,i in self.pointer_args[address]:
                # A pointer argument is only a registration candidate until a
                # retail callee store links that argument to a callback slot.
                registrars = [g for g in self.by_addr[c['target']] if self.compatible(c['function'],g)] if c['target'] is not None else []
                stores = [s for g in registrars for s in self.entry_stores[(id(g),'entry:'+REGS[ARGS[i]])]]
                roots = frozenset(x for s in stores for x in s['address'].roots)
                roots |= frozenset(s['address'].const for s in stores if s['address'].const is not None)
                rec = {'caller':c['caller'],'pc':hx(c['pc']),'registrar':hx(c['target']),
                       'callback_register':REGS[ARGS[i]],'callback_value':hx(address),
                       'slot_stores':[{'row':s['function']['row'],'pc':hx(s['pc']), 'slot':s['address'].show()} for s in stores],
                       'classification':'retail argument-to-slot store' if stores else 'pointer argument; registration not established'}
                registrations.append(rec)
                dispatch_candidates = {id(d):d for root in roots for d in self.dispatch_by_root[root]}
                for d in dispatch_candidates.values():
                    dispatch.append({'route':'registration slot -> jalr (inferred alias)','registration':rec,
                                     'dispatcher':self.call_record(d)})
        for ref in refs:
            if not ref['address']:
                continue
            slot = integer(ref['address'])
            for d in self.dispatchers:
                # Array roots can precede the matched table entry; bounded
                # offset check is labelled inference, never identity proof.
                roots = d['target_value'].roots
                hits = [x for x in roots if 0<=slot-x<1024]
                if hits and (d['container']==ref['container'] or d['container']=='slus'):
                    dispatch.append({'route':'data table -> jalr (bounded table-root candidate)',
                                     'reference':ref,'table_roots':[hx(x) for x in hits],
                                     'dispatcher':self.call_record(d)})
        # Direct sw of a materialised pointer is another registration route.
        for s in self.pointer_stores[address]:
                binding = {'row':s['function']['row'],'pc':hx(s['pc']),'slot':s['address'].show()}
                bindings.append(binding)
                roots = s['address'].roots | ({s['address'].const} if s['address'].const is not None else set())
                dispatch_candidates = {id(d):d for root in roots for d in self.dispatch_by_root[root]}
                for d in dispatch_candidates.values():
                    dispatch.append({'route':'direct slot store -> jalr (inferred alias)','binding':binding,'dispatcher':self.call_record(d)})
        scripts = []
        for table in self.script_tables:
            for i,item in enumerate(table.get('entries',[])):
                if isinstance(item,dict):
                    target = integer(item['target']); number = item.get('number',i)
                else:
                    target = integer(item); number = i
                if target != address:
                    continue
                off = integer(table['foff'])+number*4; b = self.images.get(table['container'],b'')
                valid = off+4<=len(b) and struct.unpack_from('<I',b,off)[0]==address
                scripts.append({'container':table['container'],'number':number,'foff':hx(off),
                                'retail_word_verified':valid,'metadata':item})
        arities = []
        for d in dispatch:
            args = d['dispatcher']['argument_registers']; n = 0
            for r in ('a0','a1','a2','a3'):
                if args[r]['locally_prepared'] and r!=d['dispatcher']['argument_target_overlap']:
                    n += 1
                else:
                    break
            if n:
                arities.append(n)
        entry = self.entry(f)
        lower = max([entry['required_register_arity_lower_bound']]+arities)
        unique = {json.dumps(d,sort_keys=True):d for d in dispatch}
        return {'row':f['row'],'function':f['name'],'address':hx(address),'entry':entry,
                'direct_callers':direct,'address_words':refs,'registration_calls':registrations,
                'direct_pointer_stores':bindings,'script_call_table_entries':scripts,
                'dispatch_contexts':list(unique.values()),
                'inferred_true_signature':{'required_register_arity_lower_bound':lower,
                  'callback_convention_arities':sorted(set(arities)),
                  'statement':f'callback receives at least {lower} register arguments' if dispatch else 'entry/call evidence; exact source signature unresolved',
                  'types':'see retail argument origins/widths; exact C types unresolved',
                  'confidence':'inferred slot alias' if dispatch else 'entry reads only'},
                'ambiguity':{'same_address_candidates':[g['row'] for g in self.by_addr[address] if g is not f],
                             'warning':'address equality alone does not establish overlay bank identity'},
                'raw_jal_encodings':self.raw_jals[address]}

    def census(self):
        entries = [self.entry(f) for f in self.functions]; call_reports = self.callsites(self.functions)
        issues = defaultdict(list)
        for report in call_reports:
            for call in report['callsites']:
                for flag in call['flags']:
                    issues[call['caller']].append({'flag':flag,'callee':report['address'],'pc':call['pc']})
        ranked = []
        for f,e in zip(self.functions,entries):
            reach = self.reach(f)
            flags = e['flags'] + sorted({x['flag'] for x in issues[f['row']]})
            x = e['cross_references']
            convention = reach['inferred_true_signature']['callback_convention_arities']
            declared = e['c_signature']['arity'] if e['c_signature'] else None
            if (convention and declared is not None and max(convention)>declared
                    and not f['signature']['variadic'] and not e['parameter_layout'].startswith('wide')):
                flags.append('callback_convention_exceeds_declared_params')
            x['call_arity_sites'] = x['call_arity_sites'] + [i for i in issues[f['row']] if 'arity' in i['flag']]
            score = 10*len(e['beyond_declared_params']) + 8*len(e['nonstandard_entry_regs']) + 6*sum('arity' in flag for flag in flags) + 3*sum('prototype' in flag for flag in flags)
            if flags:
                score += 2*bool(x['pinned']) + 2*bool(x['argument_reg_pins']) + bool(x['m2c_unk_params']) + bool(x['volatile'])
                score += 10*('callback_convention_exceeds_declared_params' in flags)
            ranked.append({'row':f['row'],'function':f['name'],'container':f['container'],'address':hx(f['address']),
                           'score':score,'flags':flags,'entry_reads':e['reads_before_write'],
                           'declared_arity':e['c_signature']['arity'] if e['c_signature'] else None,
                           'cross_references':x,'call_issues':issues[f['row']], 'coverage':e['coverage'],
                           'reach_summary':{'address_words':len(reach['address_words']),
                             'registration_calls':len(reach['registration_calls']),
                             'dispatch_contexts':len(reach['dispatch_contexts']),
                             'callback_convention_arities':convention,
                             'script_call_table_entries':len(reach['script_call_table_entries'])}})
        ranked.sort(key=lambda r:(-r['score'],r['row']))
        counts = {'functions_analysed':len(entries),'registered_rows':len({f['row'] for f in self.functions if '/symbol:' not in f['row']}),
                  'images':len(self.images),'direct_retail_calls':sum(c['target'] is not None for c in self.calls),
                  'jalr_calls':sum(c['mn']=='jalr' for c in self.dispatchers),
                  'indirect_dispatch_sites':len(self.dispatchers),
                  'address_words':sum(len(x) for x in self.word_refs.values()),
                  'indirect_tail_dispatches':sum(c['tail_dispatch'] for c in self.dispatchers),
                  'direct_tail_dispatches':sum(c['target'] is not None and c['tail_dispatch'] for c in self.calls),
                  'entry_read_rows':sum(any(r in e['reads_before_write'] for r in ('a1','a2','a3','v0','v1')) for e in entries),
                  'beyond_declared_rows':sum(bool(e['beyond_declared_params']) for e in entries),
                  'v0_v1_entry_rows':sum(bool(e['nonstandard_entry_regs']) for e in entries),
                  'partial_load_merge_seed_rows':sum(bool(e['merge_seed_entry_reads']) for e in entries),
                  'arity_disagreement_callees':sum(r['arity_disagreement'] for r in call_reports),
                  'ranked_issue_rows':sum(bool(r['flags']) for r in ranked),
                  'callback_convention_mismatch_rows':sum('callback_convention_exceeds_declared_params' in r['flags'] for r in ranked),
                  'nonconverged':sum(not f['analysis']['converged'] for f in self.functions),
                  'unknown_instruction_functions':sum(bool(f['analysis']['unknown_instructions']) for f in self.functions),
                  'missing_c_definitions':sum(not bool(f['signature']) for f in self.functions),
                  'missing_images':getattr(self,'missing_images',[])}
        return {'counts':counts,'rows':ranked,'dispatchers':[self.call_record(d) for d in self.dispatchers],
                'inputs_sha256':self.inputs,'limitations':LIMITS}

LIMITS = [
    'MAY-path entry reads; unknown opcodes, nonconvergence, synthetic mapping and missing C are explicit coverage gaps.',
    'Register setup is an observed shape, not proof of exact arity: unused arguments and old values are indistinguishable in bytes.',
    'An unchanged indirect-target register inside a0-a3 is retained as an argument/target overlap and is not counted as extra-argument evidence; a delay-slot overwrite can prepare a real argument there.',
    'Variadic entry reads are permitted. Wide-argument ABI layouts are unresolved; aggregate-by-value layouts require manual review. Paired LWL/LWR merge seeds remain physical reads but do not establish hidden inputs.',
    'Slot matching is inferred aliasing. Overlay banks can share addresses; every address-equality candidate is retained.',
    'C parsing is lexical, with local include closure, not preprocessing. C-to-retail call pairing requires equal occurrence counts.',
    'Registration traces one direct callee store; multi-hop wrappers, heap aliasing, arbitrary script VMs and unregistered code are unresolved.',
    'All aligned words in available images are scanned; raw jal encodings outside analysed functions may be data.',
    'Representative row spans plus exported resident symbol intervals are analysed; repeated container instances are not reconstructed from an instances count. Symbol intervals are upper bounds, not ownership proofs.',
]

def render_census(report,fmt):
    columns = ['row','function','score','declared_arity','flags','entry_reads','pinned','argument_reg_pins','m2c_unk_params','volatile','call_arity_sites']
    rows = []
    for r in report['rows']:
        x = r['cross_references']; rows.append({**{k:r[k] for k in columns if k in r},**x,
            'flags':';'.join(r['flags']),'entry_reads':';'.join(r['entry_reads']),
            'argument_reg_pins':';'.join(x['argument_reg_pins']), 'call_arity_sites':json.dumps(x['call_arity_sites'],sort_keys=True)})
    if fmt=='csv':
        out = io.StringIO(); w = csv.DictWriter(out,columns,extrasaction='ignore');w.writeheader();w.writerows(rows)
        return out.getvalue()
    lines = ['# Context census','', 'Retail/C diagnostic findings; reviewer pending.','',
             *[f'- {k}: {v}' for k,v in report['counts'].items()], '',
             '| Row | Score | Declared args | Entry reads | Findings |',
             '|---|---:|---:|---|---|']
    lines += [f'| {r["row"]} | {r["score"]} | {r["declared_arity"]} | {r["entry_reads"]} | {r["flags"]} |' for r in rows if r['score']]
    lines += ['', '## Coverage limits', '', *['- '+s for s in report['limitations']]]
    return '\n'.join(lines)+'\n'

def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--root',type=Path,default=Path(__file__).resolve().parents[3])
    ap.add_argument('--manifest',type=Path,help='fixture manifest under --root (no live tree required)')
    sub = ap.add_subparsers(dest='command',required=True)
    for command in ('reach','entry-regs','callsites','census'):
        p = sub.add_parser(command)
        if command!='census':
            p.add_argument('query',nargs='?');p.add_argument('--all',action='store_true')
        p.add_argument('--format',choices=('json','csv','md'),default='json')
        p.add_argument('--out',type=Path,help='explicit report file or census directory')
    a = ap.parse_args(argv)
    if a.command!='census' and (bool(a.query)==bool(a.all)):
        ap.error('provide exactly one query or --all')
    if a.command=='reach' and a.all:
        ap.error('reach requires one query; census inventories dispatchers tree-wide')
    if a.command!='census' and a.format!='json':
        ap.error('CSV/MD formats are for census')
    try:
        root = a.root.resolve(); manifest = a.manifest.resolve() if a.manifest else None
        if manifest and not manifest.is_relative_to(root):
            raise ValueError('--manifest must be under --root')
        o = Oracle(root,manifest)
        fs = o.functions if a.command=='census' or a.all else o.resolve(a.query)
        if a.command=='reach':
            result = [o.reach(f) for f in fs]
        elif a.command=='entry-regs':
            result = [o.entry(f) for f in fs]
        elif a.command=='callsites':
            result = o.callsites(fs)
        else:
            result = o.census()
        if a.command!='census':
            result = {'command':a.command,'query':a.query,'ambiguous_query':len(fs)>1 if not a.all else False,
                      'results':result,'limitations':LIMITS,'inputs_sha256':o.inputs}
        output = render_census(result,a.format) if a.command=='census' and a.format!='json' else json.dumps(result,indent=2,sort_keys=True)+'\n'
        if a.out:
            a.out.parent.mkdir(parents=True,exist_ok=True);a.out.write_text(output)
        else:
            print(output,end='')
        return 0
    except (OSError,ValueError,KeyError,struct.error) as exc:
        ap.exit(2,'context_oracle: '+str(exc)+'\n')

if __name__=='__main__':
    raise SystemExit(main())
