#!/usr/bin/env python3
"""Retail-ABI facts per function and per call site from a byte-exact MIPS (R3000) object.

    abi.py OBJECT.o            print the facts of one object as JSON

Per function (one `.text.*` FUNC symbol):
  args_read          a0-a3 read before any write on some path from entry (explicit operands)
  args_at_first_call a0-a3 still unwritten when the first call/sibcall executes (pass-through candidates;
                     a call's argument reads are implicit, so these are not counted in args_read)
  stack_args_read    incoming stack argument slots read (frame-relative offsets >= frame + 16), as indexes
  home_stores        a0-a3 stored to their caller home slots (variadic / address-taken parameters)
  v0_at_return       per return path: 'own' (written by this function), 'call' (left by a callee),
                     'none' (never written on that path); v0_all_paths = no 'none' path
  return_ext         patterns of the last v0 write reaching each `jr ra` (through predecessor blocks):
                     s8/s16/u8/u16 (sll/sra, andi), load_<op>, bool (slt*), const, move, call, word, none
  calls_out, sibcalls, indirect_jumps, indirect_calls
Per call site (`jal` with an R_MIPS_26 relocation, `jalr`, and sibcall `j`):
  callee, offset, args (a0-a3 -> setup pattern since the previous call in the block, or 'inherited'),
  v0_use  'unused' | 'raw' | 'ext_s16' | 'ext_s8' | 'ext_u16' | 'ext_u8' | 'store8' | 'store16' |
          'store32' | 'test' | 'returned' | 'tail'
Read-only; capstone 5 (no regs_access on MIPS: def/use comes from the operand shapes below).
"""
from __future__ import annotations

import json
from pathlib import Path
import sys

import capstone
from capstone import mips

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'build'))
import affected as A    # noqa: E402  (ELF section/symbol/relocation reader)

ARGS = ('a0', 'a1', 'a2', 'a3')
R_MIPS_26 = 4
LOADS = {'lb', 'lbu', 'lh', 'lhu', 'lw', 'lwl', 'lwr'}
STORES = {'sb', 'sh', 'sw', 'swl', 'swr'}
BRANCH2 = {'beq', 'bne', 'beql', 'bnel'}
BRANCH1 = {'beqz', 'bnez', 'blez', 'bgtz', 'bltz', 'bgez', 'bgezal', 'bltzal', 'blezl', 'bgtzl', 'bltzl', 'bgezl'}
CLOBBER = ('v0', 'v1', 'a0', 'a1', 'a2', 'a3', 't0', 't1', 't2', 't3', 't4', 't5', 't6', 't7', 't8', 't9', 'ra',
           'at', 'hi', 'lo')

_MD = None


def disassembler():
    global _MD
    if _MD is None:
        _MD = capstone.Cs(capstone.CS_ARCH_MIPS, capstone.CS_MODE_MIPS32 | capstone.CS_MODE_LITTLE_ENDIAN)
        _MD.detail = True
    return _MD


class Insn:
    __slots__ = ('off', 'mn', 'ops', 'reads', 'writes', 'target', 'imm', 'mem', 'text')

    def __init__(self, i):
        self.off, self.mn = i.address, i.mnemonic
        self.text = (i.mnemonic + ' ' + i.op_str).strip()
        regs, self.imm, self.mem, self.target = [], None, None, None
        for o in i.operands:
            if o.type == mips.MIPS_OP_REG:
                regs.append(i.reg_name(o.reg))
            elif o.type == mips.MIPS_OP_IMM:
                self.imm = o.imm
            elif o.type == mips.MIPS_OP_MEM:
                self.mem = (i.reg_name(o.mem.base), o.mem.disp)
        self.ops = regs
        mn = self.mn
        reads, writes = [], []
        if mn in LOADS:
            writes = regs[:1]
            reads = [self.mem[0]] + (regs[:1] if mn in ('lwl', 'lwr') else [])
        elif mn in STORES:
            reads = regs[:1] + [self.mem[0]]
        elif mn in ('lwc2',) or mn in ('swc2',):
            reads = [self.mem[0]] if self.mem else []
        elif mn in BRANCH2:
            reads, self.target = regs[:2], self.imm
            writes = []
        elif mn in BRANCH1:
            reads, self.target = regs[:1], self.imm
            writes = ['ra'] if mn.endswith('al') else []
        elif mn in ('b', 'bal'):
            self.target = self.imm
            writes = ['ra'] if mn == 'bal' else []
        elif mn in ('j', 'jal'):
            self.target = self.imm
            writes = ['ra'] if mn == 'jal' else []
        elif mn == 'jr':
            reads = regs[:1]
        elif mn == 'jalr':
            reads, writes = regs[-1:], (regs[:1] if len(regs) > 1 else ['ra'])
        elif mn in ('mult', 'multu', 'div', 'divu'):
            reads, writes = [r for r in regs if r != 'zero'], ['hi', 'lo']
        elif mn in ('mfhi', 'mflo'):
            writes, reads = regs[:1], [mn[2:]]
        elif mn in ('mthi', 'mtlo'):
            reads, writes = regs[:1], [mn[2:]]
        elif mn in ('mtc2', 'ctc2', 'mtc0'):
            reads = regs[:1]
        elif mn in ('mfc2', 'cfc2', 'mfc0'):
            writes = regs[:1]
        elif mn in ('nop', 'syscall', 'break', 'rfe') or mn.startswith('cop'):
            pass
        else:
            writes, reads = regs[:1], regs[1:]
        self.reads = [r for r in reads if r != 'zero']
        self.writes = [r for r in writes if r != 'zero']


def is_control(ins):
    return ins.target is not None or ins.mn in ('jr', 'jalr')


def ext_pattern(insns, idx, reg='v0'):
    """Pattern of the write to `reg` at insns[idx] (looking one step back for sll/sra pairs)."""
    ins = insns[idx]
    mn = ins.mn
    if mn in ('sra', 'srl') and ins.imm in (16, 24):
        src = ins.ops[1] if len(ins.ops) > 1 else None
        for j in range(idx - 1, max(-1, idx - 4), -1):
            prev = insns[j]
            if src in prev.writes:
                if prev.mn == 'sll' and prev.imm == ins.imm:
                    return ('s' if mn == 'sra' else 'u') + ('16' if ins.imm == 16 else '8')
                break
        return 'shift'
    if mn == 'andi' and ins.imm in (0xff, 0xffff):
        return 'u8' if ins.imm == 0xff else 'u16'
    if mn in LOADS:
        return 'load_' + mn
    if mn in ('slt', 'sltu', 'slti', 'sltiu', 'xori') and (mn != 'xori' or ins.imm == 1):
        return 'bool'
    if mn in ('lui', 'ori') or (mn == 'addiu' and len(ins.ops) > 1 and ins.ops[1] == 'zero'):
        return 'const'
    if mn == 'move' or (mn in ('addu', 'or') and 'zero' in ins.ops[1:]):
        return 'move'
    if mn in ('jal', 'jalr', 'j'):
        return 'call'
    if mn == 'addiu' and len(ins.ops) > 1 and ins.ops[1] == 'sp':
        return 'stack_address'
    return 'word'


def analyze_function(code, base, size, relocs, own_section, name):
    md = disassembler()
    insns = [Insn(i) for i in md.disasm(code[base:base + size], base)]
    if not insns:
        return None, []
    at = {ins.off: k for k, ins in enumerate(insns)}
    calls = {}      # insn index -> callee name (jal/j relocations against another symbol)
    for off, typ, sym in relocs:
        if typ == R_MIPS_26 and off in at and sym not in (own_section, name):
            calls[at[off]] = sym
    n = len(insns)
    # Basic blocks: leaders are entry, branch targets, and the instruction after each delay slot.
    leaders = {0}
    for k, ins in enumerate(insns):
        if is_control(ins):
            if k + 2 < n:
                leaders.add(k + 2)
            local = ins.mn not in ('jal', 'jalr', 'jr') and k not in calls
            if local and ins.target is not None and ins.target in at:
                leaders.add(at[ins.target])
    order = sorted(leaders)
    blocks = []
    for b, start in enumerate(order):
        end = order[b + 1] if b + 1 < len(order) else n
        blocks.append((start, end))
    block_of = {start: b for b, (start, _) in enumerate(blocks)}
    succ = [[] for _ in blocks]
    exits = {}      # block -> 'return' | 'sibcall' | 'indirect'
    indirect_jumps = 0
    for b, (start, end) in enumerate(blocks):
        term = next((k for k in range(start, end) if is_control(insns[k]) and insns[k].mn not in ('jal', 'jalr')
                     and not (insns[k].mn == 'bal')), None)
        if term is None:
            if end < n:
                succ[b].append(block_of[end])
            continue
        ins = insns[term]
        if ins.mn == 'jr':
            if ins.ops[:1] == ['ra']:
                exits[b] = 'return'
            else:
                exits[b] = 'indirect'
                indirect_jumps += 1
            continue
        if ins.mn == 'j' and term in calls:
            exits[b] = 'sibcall'
            continue
        if ins.target is not None and ins.target in at:
            succ[b].append(block_of[at[ins.target]])
        if ins.mn not in ('b', 'j') and end < n:
            succ[b].append(block_of[end])

    def steps(start, end):
        """Instructions of a block in execution order: a delay slot runs before its branch's effects."""
        k = start
        while k < end:
            ins = insns[k]
            if is_control(ins) and k + 1 < end:
                yield k, 'reads'
                yield k + 1, 'all'
                yield k, 'writes'
                k += 2
            else:
                yield k, 'all'
                k += 1

    # --- must-defined argument registers (read-before-write) and v0 provenance (may-set) ---
    defined_in = [None] * len(blocks)
    v0_in = [None] * len(blocks)
    defined_in[0] = frozenset()
    v0_in[0] = frozenset({'none'})
    work = [0]
    args_read, at_call = set(), None
    returns, call_sites = [], []
    stack_args, home = set(), set()
    frame = 0
    for ins in insns[:6]:
        if ins.mn == 'addiu' and ins.ops[:2] == ['sp', 'sp'] and ins.imm and ins.imm < 0:
            frame = -ins.imm
            break
    visits = 0
    final = {}
    while work:
        b = work.pop()
        visits += 1
        if visits > 20000:
            break
        defined, v0 = set(defined_in[b]), set(v0_in[b])
        start, end = blocks[b]
        for k, part in steps(start, end):
            ins = insns[k]
            if part in ('all', 'reads'):
                for r in ins.reads:
                    if r in ARGS and r not in defined:
                        args_read.add(r)
                if ins.mn in ('lw', 'lh', 'lhu', 'lb', 'lbu') and ins.mem and ins.mem[0] == 'sp' \
                        and frame and ins.mem[1] >= frame + 16:
                    stack_args.add((ins.mem[1] - frame) // 4)
                if ins.mn == 'sw' and ins.mem and ins.mem[0] == 'sp' and frame and ins.ops[:1] and \
                        ins.ops[0] in ARGS and ins.mem[1] == frame + 4 * ARGS.index(ins.ops[0]):
                    home.add(ins.ops[0])
            if part in ('all', 'writes'):
                callish = ins.mn in ('jal', 'jalr') or (ins.mn == 'j' and k in calls)
                if callish:
                    if at_call is None:
                        at_call = sorted(set(ARGS) - defined)
                    defined.update(CLOBBER)
                    v0 = {'call'}
                defined.update(ins.writes)
                if 'v0' in ins.writes and not callish:
                    v0 = {'own'}
        final[b] = (frozenset(defined), frozenset(v0))
        for s in succ[b]:
            nd = frozenset(defined) if defined_in[s] is None else defined_in[s] & frozenset(defined)
            nv = frozenset(v0) if v0_in[s] is None else v0_in[s] | frozenset(v0)
            if nd != defined_in[s] or nv != v0_in[s]:
                defined_in[s], v0_in[s] = nd, nv
                work.append(s)
    preds = [[] for _ in blocks]
    for b, ss in enumerate(succ):
        for x in ss:
            preds[x].append(b)

    def last_v0(b, depth, seen):
        """Patterns of the last v0 write reaching the end of block b (through predecessors)."""
        start, end = blocks[b]
        order_k = [k for k, part in steps(start, end) if part in ('all', 'writes')]
        last = next((k for k in reversed(order_k) if 'v0' in insns[k].writes or
                     insns[k].mn in ('jal', 'jalr')), None)
        if last is not None:
            return {ext_pattern(insns, last)}
        if not preds[b]:
            return {'none'}
        if depth > 6:
            return {'unknown'}
        out = set()
        for p in preds[b]:
            if p not in seen:
                out |= last_v0(p, depth + 1, seen | {p})
        return out or {'unknown'}

    v0_paths, return_ext = set(), set()
    for b, kind in exits.items():
        if kind != 'return' or b not in final:
            continue
        v0_paths |= final[b][1]
        return_ext |= last_v0(b, 0, {b})
    # --- call sites ---
    for k, ins in enumerate(insns):
        callish = ins.mn in ('jal', 'jalr') or (ins.mn == 'j' and k in calls)
        if not callish:
            continue
        b = max(i for i, (s, e) in enumerate(blocks) if s <= k)
        start = blocks[b][0]
        args = {}
        span = list(range(start, k)) + ([k + 1] if k + 1 < n else [])
        prev_call = max((j for j in span if j < k and insns[j].mn in ('jal', 'jalr')), default=None)
        if prev_call is not None:
            span = [j for j in span if j > prev_call + 1]
        for a in ARGS:
            w = next((j for j in reversed(span) if a in insns[j].writes), None)
            args[a] = ext_pattern(insns, w, a) if w is not None else 'inherited'
        use = 'tail' if ins.mn == 'j' else 'unused'
        if ins.mn != 'j':
            j = k + 2
            while j < n:
                nxt = insns[j]
                if 'v0' in nxt.reads:
                    mn = nxt.mn
                    if mn == 'sll' and nxt.imm in (16, 24):
                        follow = insns[j + 1] if j + 1 < n else None
                        kind = 's' if follow is not None and follow.mn == 'sra' else 'u'
                        use = 'ext_%s%s' % (kind, '16' if nxt.imm == 16 else '8')
                    elif mn == 'andi' and nxt.imm in (0xff, 0xffff):
                        use = 'ext_u8' if nxt.imm == 0xff else 'ext_u16'
                    elif mn in ('sb', 'sh', 'sw') and nxt.ops[:1] == ['v0']:
                        use = {'sb': 'store8', 'sh': 'store16', 'sw': 'store32'}[mn]
                    elif mn in BRANCH1 or mn in BRANCH2 or mn in ('slt', 'sltu', 'slti', 'sltiu'):
                        use = 'test'
                    elif mn == 'jr':
                        use = 'returned'
                    else:
                        use = 'raw'
                    break
                if 'v0' in nxt.writes or nxt.mn in ('jal', 'jalr'):
                    break
                if nxt.mn == 'jr' and nxt.ops[:1] == ['ra']:
                    # v0 untouched through the delay slot: the call's value is this function's return.
                    slot = insns[j + 1] if j + 1 < n else None
                    use = 'raw' if slot is not None and 'v0' in slot.reads else \
                        'unused' if slot is not None and 'v0' in slot.writes else 'returned'
                    break
                if is_control(nxt) or (j in at and j != k + 2 and j in leaders):
                    break
                j += 1
        call_sites.append(dict(offset=ins.off, callee=calls.get(k, '<indirect>' if ins.mn == 'jalr' else '?'),
                               kind='sibcall' if ins.mn == 'j' else 'call', args=args, v0_use=use))
    fn = dict(name=name, size=size, args_read=sorted(args_read), args_at_first_call=at_call or [],
              stack_args_read=sorted(stack_args), home_stores=sorted(home),
              v0_at_return=sorted(v0_paths), v0_all_paths=bool(v0_paths) and 'none' not in v0_paths,
              return_ext=sorted(return_ext), calls_out=sum(1 for c in call_sites if c['kind'] == 'call'),
              sibcalls=sum(1 for c in call_sites if c['kind'] == 'sibcall'), indirect_jumps=indirect_jumps,
              indirect_calls=sum(1 for c in call_sites if c['callee'] == '<indirect>'),
              returns=sum(1 for v in exits.values() if v == 'return'))
    return fn, call_sites


def analyze_object(blob):
    """{'functions': [...], 'calls': [...]} for every FUNC symbol in the object's .text sections."""
    facts = A.elf_facts(blob)
    sections = {s['index']: (n, s) for n, s in facts['sections'].items()}
    functions, calls = [], []
    for sym in facts['symbols']:
        if sym['type'] != 2 or sym['shndx'] not in sections:
            continue
        sec_name, sec = sections[sym['shndx']]
        if not sec_name.startswith('.text'):
            continue
        size = sym['size'] or (sec['size'] - sym['value'])
        try:
            fn, sites = analyze_function(sec['data'], sym['value'], size, facts['relocs'].get(sec_name, []),
                                         sec_name, sym['name'])
        except Exception as exc:     # recorded per function, never fatal for the census
            fn, sites = dict(name=sym['name'], size=size, error=str(exc)[:200]), []
        if fn is None:
            continue
        fn['section'] = sec_name
        fn['global'] = sym['bind'] == 1
        functions.append(fn)
        for site in sites:
            calls.append(dict(site, caller=sym['name']))
    return dict(functions=functions, calls=calls)


if __name__ == '__main__':
    print(json.dumps(analyze_object(Path(sys.argv[1]).read_bytes()), indent=1))
