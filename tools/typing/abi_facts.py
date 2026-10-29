#!/usr/bin/env python3
"""Binary-side ABI facts from the byte-exact objects: callee contracts and call-site argument/return use.

    abi_facts.py scan  [--root R] [--cache build/abi_facts.json.gz] [--workers 8]   every built object
    abi_facts.py name  [--root R] [--cache ...] NAME...                            facts for C names (JSON)
    abi_facts.py object PATH.o                                                      one object (JSON)

Per function (each FUNC symbol of a `.text*` section, decoded with capstone):
  * `args`: incoming argument registers a0-a3 read before any write on some path (must-written dataflow
    over the function's CFG; delay slots and call clobbers modelled), plus `stack_args` (loads from the
    caller's outgoing-argument area, 16(sp)+ above the frame) -> `arity` (highest argument read + 1);
  * `returns`: 'value' when v0 is written on every path to `jr ra`, 'void' when on none, else 'partial'
    (gcc also uses v0 as a temporary, so 'value' is evidence, not proof, of a non-void contract);
  * `ret_defs` / `ret_fits`: the reaching definitions of v0 at each `jr ra` classified (sra 16 -> s16,
    andi 0xffff -> u16, lbu -> u8, slt -> bool, constants, call results...) and the narrowest integer
    types every definition fits.
Per call site (`jal`/`j` with an R_MIPS_26 relocation against a symbol that is not the function's own
section):
  * `args`: for each of a0-a3 the classified reaching definitions at the call (after the delay slot):
    narrow loads/extensions, constants, pass-through of the caller's own incoming argument ('entry'),
    a register left over from an earlier call ('stale': not set up for this call);
  * `stack_args`: outgoing stores to 16(sp).. before the call in its block;
  * `v0_use`: how the call's v0 is consumed: none / returned / raw / test / store8|16|32 / ext_s8|s16 /
    ext_u8|u16 (the caller narrows the result itself) / copy.

Binding: object symbols are the canonical `func_<addr>` names (tools/ccproc.py spells readable names
back); config/names.tsv maps C names to them.  `link_bindings` reads the per-unit linker scripts of a
registered image (`build/.state/link/<tag>/<n>.ld`: `symbol = address;`) so a caller's placement can be
joined to the unit at that address.  Pure Python + capstone; no compiler, no writes outside --cache.
"""
from __future__ import annotations

import argparse
from collections import defaultdict
from concurrent.futures import ProcessPoolExecutor
import gzip
import hashlib
import json
import os
from pathlib import Path
import re
import struct
import sys

HERE = Path(__file__).resolve()
DEFAULT_ROOT = HERE.parents[2]

ARG_REGS = ('a0', 'a1', 'a2', 'a3')
CALLER_SAVED = ('at', 'v0', 'v1', 'a0', 'a1', 'a2', 'a3', 't0', 't1', 't2', 't3', 't4', 't5', 't6', 't7',
                't8', 't9', 'ra', 'hi', 'lo')
R_MIPS_26 = 4

# ------------------------------------------------------------------------------------------------ ELF


class Elf:
    """Minimal ELF32 little-endian relocatable reader: sections, symbols, REL relocations."""

    def __init__(self, data: bytes):
        if len(data) < 52 or data[:6] != b'\x7fELF\x01\x01':
            raise ValueError('not an ELF32 little-endian object')
        shoff = struct.unpack_from('<I', data, 32)[0]
        count, shstrndx = struct.unpack_from('<HH', data, 48)
        raw = [struct.unpack_from('<10I', data, shoff + 40 * n) for n in range(count)]
        names = data[raw[shstrndx][4]:raw[shstrndx][4] + raw[shstrndx][5]] if count else b''
        self.sections = []
        for n, (name, typ, flags, addr, off, size, link, info, align, entsize) in enumerate(raw):
            body = b'' if typ == 8 else data[off:off + size]
            self.sections.append(dict(index=n, name=_cstr(names, name), type=typ, flags=flags, size=size,
                                      link=link, info=info, data=body))
        self.symbols = []
        for s in self.sections:
            if s['type'] != 2:
                continue
            strtab = self.sections[s['link']]['data']
            for off in range(0, len(s['data']), 16):
                name, value, size, info, other, shndx = struct.unpack_from('<IIIBBH', s['data'], off)
                self.symbols.append(dict(name=_cstr(strtab, name), value=value, size=size, type=info & 15,
                                         bind=info >> 4, shndx=shndx))
            break
        for sym in self.symbols:
            if not sym['name'] and sym['type'] == 3 and sym['shndx'] < len(self.sections):
                sym['name'] = self.sections[sym['shndx']]['name']
        self.relocs = {}
        for s in self.sections:
            if s['type'] != 9:             # SHT_REL (MIPS o32 uses REL)
                continue
            target = self.sections[s['info']]['name'] if s['info'] < len(self.sections) else '?'
            rows = []
            for off in range(0, len(s['data']) - 7, 8):
                r_off, r_info = struct.unpack_from('<II', s['data'], off)
                k = r_info >> 8
                sym = self.symbols[k] if k < len(self.symbols) else None
                rows.append((r_off, r_info & 0xff, sym['name'] if sym else '?',
                             bool(sym and sym['type'] == 3)))
            self.relocs[target] = rows

    def section(self, name):
        return next((s for s in self.sections if s['name'] == name), None)

    def functions(self):
        """[(name, section, offset, size, global)] for FUNC symbols in code sections."""
        out = []
        for sym in self.symbols:
            if sym['type'] != 2 or sym['shndx'] >= len(self.sections) or sym['shndx'] == 0:
                continue
            sec = self.sections[sym['shndx']]
            if not sec['flags'] & 0x4:      # SHF_EXECINSTR
                continue
            size = sym['size'] or (sec['size'] - sym['value'])
            out.append((sym['name'], sec['name'], sym['value'], size, sym['bind'] != 0))
        return out


def _cstr(table, off):
    end = table.find(b'\0', off)
    return table[off:end if end >= 0 else len(table)].decode('latin-1')


ALLOC = 0x2


def object_difference(before: bytes, after: bytes):
    """None when two objects are equivalent for code: every allocated section's bytes and relocations
    (offset, type, symbol) and the global symbol set agree.  Metadata (STT_FILE, string tables) is
    ignored, so an object compiled from a sibling path compares equal.  Else a short description."""
    if before == after:
        return None
    try:
        a, b = Elf(before), Elf(after)
    except (ValueError, struct.error, IndexError) as exc:
        return dict(kind='unparsed', detail=str(exc))
    sa = {s['name']: s for s in a.sections if s['flags'] & ALLOC and s['name']}
    sb = {s['name']: s for s in b.sections if s['flags'] & ALLOC and s['name']}
    if sorted(sa) != sorted(sb):
        return dict(kind='section_set', only_before=sorted(set(sa) - set(sb))[:8],
                    only_after=sorted(set(sb) - set(sa))[:8])
    for name in sorted(sa, key=lambda n: (not n.startswith('.text'), n)):
        x, y = sa[name], sb[name]
        if x['size'] != y['size']:
            return dict(kind='section_size', section=name, before=x['size'], after=y['size'])
        if x['data'] != y['data']:
            off = next(i for i, (p, q) in enumerate(zip(x['data'], y['data'])) if p != q)
            return dict(kind='bytes', section=name, offset=off)
        if [r[:3] for r in a.relocs.get(name, [])] != [r[:3] for r in b.relocs.get(name, [])]:
            return dict(kind='relocation', section=name)
    ga = sorted((s['name'], s['type']) for s in a.symbols if s['bind'] == 1)
    gb = sorted((s['name'], s['type']) for s in b.symbols if s['bind'] == 1)
    if ga != gb:
        return dict(kind='global_symbols', only_before=sorted(set(ga) - set(gb))[:8],
                    only_after=sorted(set(gb) - set(ga))[:8])
    return None


# ------------------------------------------------------------------------------------------ decoding

_MD = None


def _disassembler():
    global _MD
    if _MD is None:
        import capstone
        md = capstone.Cs(capstone.CS_ARCH_MIPS, capstone.CS_MODE_MIPS32 + capstone.CS_MODE_LITTLE_ENDIAN)
        md.detail = True
        md.skipdata = True
        _MD = md
    return _MD


class Insn:
    __slots__ = ('addr', 'op', 'regs', 'imm', 'mem', 'reads', 'writes', 'target', 'kind')

    def __init__(self, addr, op, regs, imm, mem):
        self.addr, self.op, self.regs, self.imm, self.mem = addr, op, regs, imm, mem
        self.target = None
        self.kind = 'plain'
        self.reads, self.writes = _effects(op, regs, mem)

    def __repr__(self):
        return '%x:%s %s %s %s' % (self.addr, self.op, ','.join(self.regs), self.imm, self.mem or '')


STORES = {'sb', 'sh', 'sw', 'swl', 'swr'}
LOADS = {'lb', 'lbu', 'lh', 'lhu', 'lw', 'lwl', 'lwr'}
COP_MEM = {'lwc1', 'lwc2', 'swc1', 'swc2', 'ldc1', 'sdc1', 'ldc2', 'sdc2'}
BRANCH_REG = {'beq', 'bne', 'beql', 'bnel'}
BRANCH_ONE = {'beqz', 'bnez', 'bgez', 'bgtz', 'blez', 'bltz', 'beqzl', 'bnezl', 'bgezl', 'bltzl', 'bgtzl',
              'blezl'}
BRANCH_LINK = {'bgezal', 'bltzal'}
MULDIV = {'mult', 'multu', 'div', 'divu'}
TO_GPR = {'mfc0', 'mfc1', 'mfc2', 'cfc0', 'cfc1', 'cfc2'}
FROM_GPR = {'mtc0', 'mtc1', 'mtc2', 'ctc0', 'ctc1', 'ctc2'}
GPR = {'zero', 'at', 'v0', 'v1', 'a0', 'a1', 'a2', 'a3', 't0', 't1', 't2', 't3', 't4', 't5', 't6', 't7',
       's0', 's1', 's2', 's3', 's4', 's5', 's6', 's7', 't8', 't9', 'k0', 'k1', 'gp', 'sp', 'fp', 's8', 'ra'}


def _effects(op, regs, mem):
    """(reads, writes) register name tuples of one instruction; $zero never counts."""
    base = (mem[0],) if mem else ()
    if op in STORES:
        r, w = tuple(regs[:1]) + base, ()
    elif op in LOADS:
        r, w = base + (tuple(regs[:1]) if op in ('lwl', 'lwr') else ()), tuple(regs[:1])
    elif op in COP_MEM:
        r, w = base, ()
    elif op in BRANCH_REG:
        r, w = tuple(regs[:2]), ()
    elif op in BRANCH_ONE:
        r, w = tuple(regs[:1]), ()
    elif op in BRANCH_LINK:
        r, w = tuple(regs[:1]), ('ra',)
    elif op in ('b', 'j', 'nop', 'ssnop', 'syscall', 'break', '.byte'):
        r, w = (), ()
    elif op in ('jal', 'bal'):
        r, w = (), ('ra',)
    elif op == 'jr':
        r, w = tuple(regs[:1]), ()
    elif op == 'jalr':
        r, w = (regs[-1],) if regs else (), (regs[0],) if len(regs) > 1 else ('ra',)
    elif op in MULDIV:
        rr = [x for x in regs if x != 'zero'] if len(regs) == 3 else regs
        r, w = tuple(rr[:2]), ('hi', 'lo')
    elif op in ('mfhi', 'mflo'):
        r, w = ('hi',) if op == 'mfhi' else ('lo',), tuple(regs[:1])
    elif op in ('mthi', 'mtlo'):
        r, w = tuple(regs[:1]), ('hi',) if op == 'mthi' else ('lo',)
    elif op in TO_GPR:
        r, w = (), tuple(regs[:1])
    elif op in FROM_GPR:
        r, w = tuple(regs[:1]), ()
    elif regs:
        r, w = tuple(regs[1:]) + base, tuple(regs[:1])
    else:
        r, w = (), ()
    return (tuple(x for x in r if x in GPR or x in ('hi', 'lo')) if r else (),
            tuple(x for x in w if x != 'zero' and (x in GPR or x in ('hi', 'lo'))))


def decode(code: bytes, base: int = 0):
    from capstone import mips
    out = []
    for i in _disassembler().disasm(code, base):
        regs, imm, mem = [], None, None
        if i.mnemonic != '.byte':
            for o in i.operands:
                if o.type == mips.MIPS_OP_REG:
                    regs.append(i.reg_name(o.reg))
                elif o.type == mips.MIPS_OP_IMM:
                    imm = o.imm
                elif o.type == mips.MIPS_OP_MEM:
                    mem = (i.reg_name(o.mem.base), o.mem.disp)
        regs = ['s8' if r == 'fp' else r for r in regs]
        if mem and mem[0] == 'fp':
            mem = ('s8', mem[1])
        op = i.mnemonic
        if op == '.byte' and len(i.bytes) == 4:
            op, regs = _coprocessor(int.from_bytes(i.bytes, 'little'))
        out.append(Insn(i.address, op, regs, imm, mem))
    return out


GPR_NAMES = ('zero', 'at', 'v0', 'v1', 'a0', 'a1', 'a2', 'a3', 't0', 't1', 't2', 't3', 't4', 't5', 't6', 't7',
             's0', 's1', 's2', 's3', 's4', 's5', 's6', 's7', 't8', 't9', 'k0', 'k1', 'gp', 'sp', 's8', 'ra')


def _coprocessor(word):
    """Decode what capstone leaves as data: coprocessor moves (GTE ctc2/cfc2 and friends) touch a GPR,
    GTE commands (cop2 with the CO bit) touch none."""
    opcode, rs, rt = word >> 26, (word >> 21) & 31, (word >> 16) & 31
    if opcode in (0x10, 0x11, 0x12) and not rs & 0x10:
        z = opcode - 0x10
        name = {0: 'mfc%d', 2: 'cfc%d', 4: 'mtc%d', 6: 'ctc%d'}.get(rs)
        if name:
            return name % z, [GPR_NAMES[rt]]
    if opcode in (0x10, 0x11, 0x12):
        return 'cop%d' % (opcode - 0x10), []
    return '.byte', []


# ------------------------------------------------------------------------------------------- analysis

BRANCHES = BRANCH_REG | BRANCH_ONE | BRANCH_LINK | {'b', 'j', 'jal', 'bal', 'jr', 'jalr'}
CALLS = {'jal', 'jalr', 'bal', 'bgezal', 'bltzal'}


class Function:
    """CFG + reaching definitions of one function (instructions at offsets 0..size)."""

    def __init__(self, insns, relocs=None, own_section=None):
        self.insns = insns
        self.by_addr = {x.addr: n for n, x in enumerate(insns)}
        relocs = relocs or {}
        # call/jump targets bound by relocations: offset -> symbol
        self.calls = {}
        for x in insns:
            if x.op in ('jal', 'j') and x.addr in relocs:
                sym, is_section = relocs[x.addr]
                if x.op == 'jal' and not (is_section and sym == own_section):
                    x.kind, x.target = 'call', sym
                elif x.op == 'j' and not is_section:
                    x.kind, x.target = 'tailcall', sym
                elif x.op == 'j' and is_section and sym != own_section:
                    x.kind, x.target = 'tailcall', sym
            if x.op == 'jalr':
                x.kind = 'call'
        self._blocks()
        self._reaching()

    def _succ_of_branch(self, n):
        x = self.insns[n]
        nxt = n + 2
        tgt = self.by_addr.get(x.imm) if x.imm is not None else None
        if x.op == 'jr':
            if x.regs and x.regs[0] == 'ra':
                return [], 'return'
            return 'all', 'switch'
        if x.kind == 'tailcall':
            return [], 'tailcall'
        if x.kind == 'call' or x.op in CALLS:
            return [nxt], 'call'
        if x.op in ('b', 'j'):
            return ([tgt] if tgt is not None else []), 'jump'
        return [t for t in (tgt, nxt) if t is not None], 'cond'

    def _blocks(self):
        n = len(self.insns)
        leaders = {0}
        for i, x in enumerate(self.insns):
            if x.op in BRANCHES and x.op not in ('jal', 'jalr', 'bal', 'bgezal', 'bltzal'):
                succ, _ = self._succ_of_branch(i)
                if succ != 'all':
                    leaders.update(s for s in succ if s < n)
                if i + 2 < n:
                    leaders.add(i + 2)
        self.leaders = sorted(l for l in leaders if l < n)
        self.block_of = {}
        self.blocks = []        # (start, end_exclusive, succ list, exit kind)
        for k, s in enumerate(self.leaders):
            e = self.leaders[k + 1] if k + 1 < len(self.leaders) else n
            succ, kind = [e] if e < n else [], 'fall'
            for i in range(s, e):
                x = self.insns[i]
                if x.op in BRANCHES and x.op not in ('jal', 'jalr', 'bal', 'bgezal', 'bltzal'):
                    succ, kind = self._succ_of_branch(i)
                    break
            self.blocks.append([s, e, succ, kind])
        for b, (s, e, succ, kind) in enumerate(self.blocks):
            for i in range(s, e):
                self.block_of[i] = b
        index = {blk[0]: b for b, blk in enumerate(self.blocks)}
        for blk in self.blocks:
            if blk[2] == 'all':
                blk[2] = list(range(len(self.blocks)))
            else:
                blk[2] = [index[s] for s in blk[2] if s in index]
        self.preds = defaultdict(list)
        for b, blk in enumerate(self.blocks):
            for s in blk[2]:
                self.preds[s].append(b)

    def _step(self, i, state, pending):
        """Apply instruction i to a {reg: frozenset(def ids)} state; returns the new pending clobber."""
        x = self.insns[i]
        for w in x.writes:
            state[w] = frozenset([i])
        if pending is not None:
            for r in CALLER_SAVED:
                state[r] = frozenset([('call', pending)])
            pending = None
        if x.kind == 'call' or x.op in CALLS:
            pending = i            # clobbers apply after the delay slot
        return pending

    def _reaching(self):
        nb = len(self.blocks)
        entry = {r: frozenset([('entry', r)]) for r in GPR | {'hi', 'lo'}}
        self.block_in = [None] * nb
        self.block_in[0] = dict(entry)
        out = [None] * nb
        work = list(range(nb))
        seen = 0
        while work:
            seen += 1
            if seen > 20000:
                break
            b = work.pop(0)
            s, e, succ, kind = self.blocks[b]
            ins = self.block_in[b]
            if ins is None:
                continue
            state = dict(ins)
            pending = None
            for i in range(s, e):
                pending = self._step(i, state, pending)
            if pending is not None:
                for r in CALLER_SAVED:
                    state[r] = frozenset([('call', pending)])
            out[b] = state
            for t in succ:
                old = self.block_in[t]
                if old is None:
                    new = dict(state)
                else:
                    new = {r: old.get(r, frozenset()) | state.get(r, frozenset()) for r in set(old) | set(state)}
                if new != old:
                    self.block_in[t] = new
                    if t not in work:
                        work.append(t)
        self.block_out = out

    def walk(self):
        """Yield (index, state_before) for every reachable instruction."""
        for b, (s, e, succ, kind) in enumerate(self.blocks):
            if self.block_in[b] is None:
                continue
            state = dict(self.block_in[b])
            pending = None
            for i in range(s, e):
                yield i, state
                state = dict(state)
                pending = self._step(i, state, pending)

    # -- classification of one definition of a register
    def classify_def(self, d, reg, depth=0):
        if isinstance(d, tuple):
            return 'entry' if d[0] == 'entry' else 'call'
        x = self.insns[d]
        op, regs, imm = x.op, x.regs, x.imm
        if op in ('lb', 'lbu', 'lh', 'lhu'):
            return {'lb': 's8', 'lbu': 'u8', 'lh': 's16', 'lhu': 'u16'}[op]
        if op == 'sra' and imm in (16, 24):
            return 's16' if imm == 16 else 's8'
        if op == 'srl' and imm in (16, 24):
            return 'u16' if imm == 16 else 'u8'
        if op == 'andi' and imm is not None:
            return 'u8' if imm <= 0xff else 'u16'
        if op in ('slt', 'sltu', 'slti', 'sltiu'):
            return 'bool'
        if op in ('li', 'addiu', 'ori', 'addi') and len(regs) >= 2 and regs[1] == 'zero' and imm is not None:
            return 'const:%d' % imm
        if op == 'li' and imm is not None:
            return 'const:%d' % imm
        if op == 'lui':
            return 'wide'
        if op in ('move', 'or', 'addu', 'daddu') and depth < 4:
            srcs = [r for r in regs[1:] if r != 'zero']
            if op == 'move' or len(srcs) == 1:
                if not srcs:
                    return 'const:0'
                # follow the copy through its own reaching definitions
                for i, st in self._state_at(d):
                    kinds = {self.classify_def(dd, srcs[0], depth + 1) for dd in st.get(srcs[0], ())}
                    return join_kinds(kinds)
        if op == 'move' and len(regs) == 2 and regs[1] == 'zero':
            return 'const:0'
        return 'wide'

    def _state_at(self, idx):
        b = self.block_of[idx]
        s = self.blocks[b][0]
        if self.block_in[b] is None:
            return
        state = dict(self.block_in[b])
        pending = None
        for i in range(s, idx):
            pending = self._step(i, state, pending)
        yield idx, state


def join_kinds(kinds):
    kinds = set(kinds)
    if len(kinds) == 1:
        return next(iter(kinds))
    return '|'.join(sorted(kinds))


INT_RANGES = {'u8': (0, 0xff), 's8': (-0x80, 0x7f), 'u16': (0, 0xffff), 's16': (-0x8000, 0x7fff)}
FITS = {'u8': {'u8', 'bool'}, 's8': {'s8', 'bool'}, 'u16': {'u16', 'u8', 'bool'},
        's16': {'s16', 's8', 'u8', 'bool'}}


def fits(kinds):
    """Integer types every classified definition fits (narrowest first)."""
    out = []
    for t in ('u8', 's8', 'u16', 's16'):
        lo, hi = INT_RANGES[t]
        ok = True
        for k in kinds:
            for part in k.split('|'):
                if part in FITS[t]:
                    continue
                if part.startswith('const:') and lo <= int(part[6:]) <= hi:
                    continue
                ok = False
        if ok and kinds:
            out.append(t)
    return out


def _use_kind(f, j, reg):
    """How instruction j consumes `reg` (a call's v0 or a copy of it)."""
    x = f.insns[j]
    op = x.op
    if op == 'sb' and x.regs[:1] == [reg]:
        return 'store8'
    if op == 'sh' and x.regs[:1] == [reg]:
        return 'store16'
    if op == 'sw' and x.regs[:1] == [reg]:
        return 'store32'
    if op == 'sll' and x.imm in (16, 24):
        return 'ext_s16' if x.imm == 16 else 'ext_s8'
    if op == 'andi' and x.imm in (0xff, 0xffff):
        return 'ext_u8' if x.imm == 0xff else 'ext_u16'
    if op in BRANCH_REG | BRANCH_ONE:
        return 'test'
    if op == 'jr' and x.regs[:1] == ['ra']:
        return 'returned'
    if op in ('move',) or (op in ('addu', 'or') and 'zero' in x.regs[1:]):
        return 'copy'
    return 'raw'


def analyze(code: bytes, relocs=None, own_section=None):
    """Facts of one function's code ({offset: (symbol, is_section)} relocations at R_MIPS_26 sites)."""
    insns = decode(code)
    f = Function(insns, relocs, own_section)
    frame = 0
    for x in insns[:4]:
        if x.op in ('addiu', 'addi') and x.regs[:2] == ['sp', 'sp'] and x.imm is not None and x.imm < 0:
            frame = -x.imm
            break
    arg_reads = set()
    stack_args = set()
    calls = []
    returns_written, returns_unwritten = 0, 0
    ret_defs = set()
    uses = defaultdict(set)      # call index -> v0 use kinds
    # copies of a call's v0 (move/addu/or x, v0, zero): definition index -> call index, followed so a
    # saved result's later extension or store is attributed to the call
    copies = {}
    for _ in range(3):
        grew = False
        for i, state in f.walk():
            x = insns[i]
            if _use_kind(f, i, x.reads[0] if x.reads else '') == 'copy' and x.reads and i not in copies:
                for d in state.get(x.reads[0], ()):
                    origin = d[1] if isinstance(d, tuple) and d[0] == 'call' and x.reads[0] == 'v0' else \
                        copies.get(d) if not isinstance(d, tuple) else None
                    if origin is not None:
                        copies[i] = origin
                        grew = True
                        break
        if not grew:
            break
    for i, state in f.walk():
        x = insns[i]
        for r in x.reads:
            if r in ARG_REGS and any(isinstance(d, tuple) and d[0] == 'entry' for d in state.get(r, ())):
                arg_reads.add(r)
            for d in state.get(r, ()):
                if isinstance(d, tuple) and d[0] == 'call' and r == 'v0':
                    kind = _use_kind(f, i, r)
                    if kind != 'copy':
                        uses[d[1]].add(kind)
                elif not isinstance(d, tuple) and d in copies:
                    kind = _use_kind(f, i, r)
                    if kind != 'copy':
                        uses[copies[d]].add(kind)
        if x.op in LOADS and x.mem and x.mem[0] == 'sp' and x.mem[1] >= frame + 16:
            stack_args.add((x.mem[1] - frame - 16) // 4)
        if x.op == 'jr' and x.regs[:1] == ['ra']:
            # the delay slot executes first
            st = dict(state)
            if i + 1 < len(insns):
                f._step(i + 1, st, None)
            defs = st.get('v0', frozenset())
            if any(isinstance(d, tuple) and d[0] == 'entry' for d in defs):
                returns_unwritten += 1
            if any(not (isinstance(d, tuple) and d[0] == 'entry') for d in defs):
                returns_written += 1
            for d in defs:
                if isinstance(d, tuple) and d[0] == 'call':
                    uses[d[1]].add('returned')
                elif not isinstance(d, tuple) and d in copies:
                    uses[copies[d]].add('returned')
                ret_defs.add(f.classify_def(d, 'v0'))
        if x.kind in ('call', 'tailcall') and x.target:
            st = dict(state)
            if i + 1 < len(insns):
                f._step(i + 1, st, None)
            args = {}
            for r in ARG_REGS:
                kinds = {f.classify_def(d, r) for d in st.get(r, ())}
                if kinds and all(k == 'call' for k in kinds):
                    args[r] = 'stale'
                else:
                    args[r] = join_kinds(kinds) if kinds else 'none'
            b = f.block_of[i]
            lo = f.blocks[b][0]
            in_block = [r for r in ARG_REGS if st.get(r) and all(
                not isinstance(d, tuple) and lo <= d <= i + 1 for d in st[r])]
            outgoing = set()
            for j in range(lo, min(i + 2, len(insns))):
                y = insns[j]
                if y.op in STORES and y.mem and y.mem[0] == 'sp' and 16 <= y.mem[1] < 16 + 4 * 12 and frame:
                    outgoing.add((y.mem[1] - 16) // 4)
            # 16(sp).. is also local storage in frames without outgoing stack arguments: count stores
            # there only for a call that sets all four argument registers, as a contiguous run from slot 0
            run = 0
            while run in outgoing:
                run += 1
            outgoing = set(range(run)) if len(in_block) == 4 else set()
            calls.append(dict(offset=x.addr, target=x.target, tail=x.kind == 'tailcall', args=args,
                              set_in_block=in_block, stack_args=sorted(outgoing), _i=i))
    for c in calls:
        i = c.pop('_i')
        c['v0_use'] = sorted(uses.get(i, ())) or (['returned'] if c['tail'] else ['none'])
    regs_read = [r for r in ARG_REGS if r in arg_reads]
    arity = max([ARG_REGS.index(r) + 1 for r in regs_read] + [4 + k + 1 for k in stack_args if k >= 0] + [0])
    total = returns_written + returns_unwritten
    returns = 'void' if returns_written == 0 else 'value' if returns_unwritten == 0 else 'partial'
    if total == 0:
        returns = 'noreturn'
    kinds = sorted(k for k in ret_defs if k != 'entry')
    return dict(size=len(code), arity=arity, args=regs_read, stack_args=sorted(k for k in stack_args if k >= 0),
                returns=returns, ret_defs=kinds, ret_fits=fits(kinds) if returns == 'value' else [],
                calls=calls)


def object_facts(blob: bytes):
    """{function symbol: facts} for every FUNC symbol of an object."""
    elf = Elf(blob)
    out = {}
    for name, secname, off, size, is_global in elf.functions():
        sec = elf.section(secname)
        code = sec['data'][off:off + size]
        relocs = {}
        for r_off, r_type, sym, is_section in elf.relocs.get(secname, ()):
            if r_type == R_MIPS_26 and off <= r_off < off + size:
                relocs[r_off - off] = (sym, is_section)
        facts = analyze(code, relocs, secname)
        facts['global'] = is_global
        facts['section'] = secname
        out[name] = facts
    return out


# --------------------------------------------------------------------------------------------- names

def names_table(root):
    """C name -> canonical object symbol (func_<addr>) from config/names.tsv, and the reverse."""
    fwd, rev = {}, defaultdict(set)
    path = Path(root) / 'config/names.tsv'
    if path.is_file():
        for raw in path.read_text().splitlines():
            cols = raw.split('#', 1)[0].split('\t')
            if len(cols) >= 3:
                old, new = cols[1].strip(), cols[2].strip()
                if old and new and old != new and old.startswith('func_'):
                    fwd[new] = old
                    rev[old].add(new)
    return fwd, rev


# ------------------------------------------------------------------------------------- tree-wide scan

def _recipes(root):
    root = Path(root)
    out = {}
    for family, folder in (('overlay', 'recipes'), ('slus', 'slus-recipes')):
        for p in sorted((root / 'build/.state' / folder).glob('*.json')):
            spec = json.loads(p.read_bytes())
            out[p.stem] = dict(family=family, source=spec.get('source'), output=spec.get('output'),
                               projection=(spec.get('projection') or {}).get('owner'),
                               command=spec.get('command'))
    return out


def _scan_one(job):
    root, rid, output = job
    path = Path(root) / output
    if not path.is_file():
        return rid, None, 'missing'
    blob = path.read_bytes()
    try:
        return rid, hashlib.sha256(blob).hexdigest(), object_facts(blob)
    except Exception as exc:                      # recorded, never fatal for the scan
        return rid, hashlib.sha256(blob).hexdigest(), 'error: %s' % exc


def scan(root, cache=None, workers=8, log=print):
    """{recipe id: {sha, source, family, projection, functions}} for every built object, cached by sha."""
    root = Path(root).resolve()
    recipes = _recipes(root)
    old = {}
    if cache and Path(cache).is_file():
        try:
            old = json.loads(gzip.decompress(Path(cache).read_bytes()))
        except (OSError, ValueError):
            old = {}
    todo, out = [], {}
    for rid, r in recipes.items():
        out_path = r['output']
        if r['family'] == 'slus' and out_path and not out_path.startswith('build_slus/'):
            out_path = 'build_slus/' + out_path
        if not out_path or not (root / out_path).is_file():
            continue
        prev = old.get(rid)
        if prev and prev.get('output') == out_path:
            st = (root / out_path).stat()
            if prev.get('mtime_ns') == st.st_mtime_ns and prev.get('bytes') == st.st_size:
                out[rid] = prev
                continue
        todo.append((str(root), rid, out_path))
    if todo:
        paths = {t[1]: t[2] for t in todo}
        with ProcessPoolExecutor(max_workers=max(1, min(workers, 8))) as ex:
            for rid, digest, facts in ex.map(_scan_one, todo, chunksize=32):
                r = recipes[rid]
                out_path = paths[rid]
                st = (root / out_path).stat()
                out[rid] = dict(sha256=digest, output=out_path, source=r['source'], family=r['family'],
                                projection=r['projection'], mtime_ns=st.st_mtime_ns, bytes=st.st_size,
                                functions=facts if isinstance(facts, dict) else {}, error=None
                                if isinstance(facts, dict) else facts)
    log('abi facts: %d objects (%d rescanned)' % (len(out), len(todo)))
    if cache and todo:
        Path(cache).parent.mkdir(parents=True, exist_ok=True)
        Path(cache).write_bytes(gzip.compress(json.dumps(out, sort_keys=True).encode()))
    return out


class Facts:
    """Name-level view over a scan: definitions and call sites of a C name, per recipe."""

    def __init__(self, root, scan_result):
        self.root = Path(root)
        self.scan = scan_result
        self.fwd, self.rev = names_table(root)
        self.defs = defaultdict(list)      # object symbol -> [(rid, facts)]
        self.calls = defaultdict(list)     # object symbol -> [(rid, caller symbol, call facts)]
        for rid, rec in scan_result.items():
            for fname, facts in rec.get('functions', {}).items():
                self.defs[fname].append((rid, facts))
                for c in facts.get('calls', ()):
                    self.calls[c['target']].append((rid, fname, c))

    def symbol(self, name):
        return self.fwd.get(name, name)

    def callee(self, name):
        """Definitions of a C name: [{recipe, source, projection, facts}] (global symbols only)."""
        sym = self.symbol(name)
        out = []
        for rid, facts in self.defs.get(sym, ()):
            if not facts.get('global'):
                continue
            rec = self.scan[rid]
            out.append(dict(recipe=rid, source=rec['source'], projection=rec['projection'], facts=facts))
        return out

    def sites(self, name):
        sym = self.symbol(name)
        out = []
        for rid, caller, c in self.calls.get(sym, ()):
            rec = self.scan[rid]
            out.append(dict(recipe=rid, source=rec['source'], projection=rec['projection'], caller=caller,
                            **{k: v for k, v in c.items() if k != 'target'}))
        return out

    def summary(self, name):
        defs = self.callee(name)
        sites = self.sites(name)
        arities = sorted({d['facts']['arity'] for d in defs})
        returns = sorted({d['facts']['returns'] for d in defs})
        fits_ = [set(d['facts']['ret_fits']) for d in defs if d['facts']['returns'] == 'value']
        common = sorted(set.intersection(*fits_)) if fits_ else []
        use = defaultdict(int)
        for s in sites:
            for u in s['v0_use']:
                use[u] += 1
        set_up = defaultdict(int)
        for s in sites:
            # argument registers written in the call's own block (leftovers from earlier blocks are not
            # counted) plus outgoing stack-argument stores: the caller's evident argument count
            n = max([ARG_REGS.index(r) + 1 for r in s.get('set_in_block', ())] + [0])
            if s['stack_args']:
                n = max(n, 4 + max(s['stack_args']) + 1)
            set_up[n] += 1
        return dict(name=name, symbol=self.symbol(name), definitions=len(defs), arity=arities, returns=returns,
                    ret_defs=sorted({k for d in defs for k in d['facts']['ret_defs']}), ret_fits=common,
                    call_sites=len(sites), v0_use=dict(sorted(use.items())),
                    args_set_up=dict(sorted(set_up.items())))


# ------------------------------------------------------------------------------------- link bindings

ASSIGN = re.compile(r'^\s*([A-Za-z_.$][\w.$]*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;', re.M)


def link_bindings(root, tag):
    """{unit index: {symbol: address}} from a registered image's per-unit linker scripts."""
    out = {}
    folder = Path(root) / 'build/.state/link' / tag
    for ld in sorted(folder.glob('*.ld')):
        if not ld.stem.isdigit():
            continue
        out[int(ld.stem)] = {m.group(1): int(m.group(2), 16) for m in ASSIGN.finditer(ld.read_text())}
    return out


def image_units(root):
    """{image tag: [unit dicts (recipe, func, vma, size)]} from build/.state/images."""
    out = {}
    for p in sorted((Path(root) / 'build/.state/images').glob('*.json')):
        spec = json.loads(p.read_bytes())
        out[spec['tag']] = spec.get('units', [])
    return out


# ------------------------------------------------------------------------------------------------ CLI

def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest='mode', required=True)
    for name in ('scan', 'name'):
        p = sub.add_parser(name)
        p.add_argument('--root', type=Path, default=DEFAULT_ROOT)
        p.add_argument('--cache', type=Path)
        p.add_argument('--workers', type=int, default=8)
    sub.choices['name'].add_argument('names', nargs='+')
    sub.choices['name'].add_argument('--sites', action='store_true', help='list every call site')
    po = sub.add_parser('object')
    po.add_argument('path', type=Path)
    args = ap.parse_args(argv)
    if args.mode == 'object':
        print(json.dumps(object_facts(args.path.read_bytes()), indent=1, sort_keys=True))
        return 0
    root = args.root.resolve()
    cache = args.cache or root / 'build/abi_facts.json.gz'
    if not 1 <= args.workers <= 8:
        ap.error('between 1 and 8 workers on this host')
    result = scan(root, cache, args.workers, log=lambda m: print(m, file=sys.stderr))
    if args.mode == 'scan':
        return 0
    facts = Facts(root, result)
    for name in args.names:
        rec = facts.summary(name)
        if args.sites:
            rec['definitions_detail'] = [dict(d, facts={k: v for k, v in d['facts'].items() if k != 'calls'})
                                         for d in facts.callee(name)]
            rec['sites'] = facts.sites(name)
        print(json.dumps(rec, sort_keys=True))
    return 0


if __name__ == '__main__':
    sys.exit(main())
