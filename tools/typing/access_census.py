#!/usr/bin/env python3
"""Conservative source-access to retail-opcode join.

The pinned compiler is run once with -g for each requested physical TU.  A
section is admitted only when its bytes equal the cached, gate-checked object.
Only a unique (debug line, byte offset, width, read/write) pair is joined.
Ambiguous, optimized-away, and unmatched accesses remain explicit rows.
"""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
import csv
import json
from pathlib import Path
import re
import shlex
import sqlite3
import subprocess
import sys
import tempfile
from functools import lru_cache

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import field_census as F

OPS = {'lb': (1, 's', 'r'), 'lbu': (1, 'u', 'r'), 'lh': (2, 's', 'r'),
       'lhu': (2, 'u', 'r'), 'lw': (4, '?', 'r'), 'lwl': (4, '?', 'r'),
       'lwr': (4, '?', 'r'), 'sb': (1, '', 'w'), 'sh': (2, '', 'w'),
       'sw': (4, '', 'w'), 'swl': (4, '', 'w'), 'swr': (4, '', 'w')}
UNION_ALIASES = {'s', 'u', 's8', 'u8', 's16', 'u16', 's32', 'u32',
                 'word', 'signed_word', 'whole', 'signed_whole', 'halves', 'bytes'}
SECTION = re.compile(r'^Disassembly of section (\.text\.[^:]+):$')
INST = re.compile(r'^\s*([0-9a-f]+):\s+[0-9a-f]{8}\s+([a-z][a-z0-9]*)\s+([^#]*)')
LINE = re.compile(r'^(?:.+/)?[^/:]+\.c:(\d+)$')
MEM = re.compile(r'^\s*([a-z0-9]+),(-?(?:0x[0-9a-f]+|\d+))\(([a-z0-9]+)\)')
RAW_ENT = re.compile(r'^\s*\.ent\s+([A-Za-z_][A-Za-z_0-9]*)\s*$')
RAW_END = re.compile(r'^\s*\.end\s+')
RAW_REGISTER = re.compile(r'^\s*\.def\s+([A-Za-z_][A-Za-z_0-9]*);\s*\.val\s+(\d+);\s*\.scl\s+4;')
RAW_STACK = re.compile(r'^\s*\.def\s+([A-Za-z_][A-Za-z_0-9]*);\s*\.val\s+(-?\d+);\s*\.scl\s+1;')
REGISTER_NUMBERS = {2: 'v0', 3: 'v1', **{i + 4: f'a{i}' for i in range(4)},
                    **{i + 8: f't{i}' for i in range(8)},
                    **{i + 16: f's{i}' for i in range(8)}, 24: 't8', 25: 't9'}
CONSUMER_SIGN = {'slt': 's', 'sltu': 'u', 'sra': 's', 'srl': 'u',
                 'div': 's', 'divu': 'u'}


def run(args, cwd):
    return subprocess.run(args, cwd=cwd, text=True, capture_output=True, check=True).stdout


def instructions(disassembly):
    """Decode only memory instructions with an unambiguous debug line."""
    section = None
    line = None
    result = defaultdict(list)
    all_instructions = defaultdict(list)
    for raw in disassembly.splitlines():
        m = SECTION.match(raw)
        if m:
            section, line = m.group(1), None
            continue
        m = LINE.match(raw.strip())
        if m:
            line = int(m.group(1))
            continue
        m = INST.match(raw)
        if not m or section is None:
            continue
        op, operand = m.group(2), m.group(3).strip()
        pc = int(m.group(1), 16)
        all_instructions[section].append((pc, op, [p.strip() for p in operand.split(',')]))
        if line is None or op not in OPS:
            continue
        mm = MEM.match(operand)
        if mm is None:
            continue
        width, sign, rw = OPS[op]
        result[section].append(dict(pc=pc, line=line, opcode=op,
                                    offset=int(mm.group(2), 0), reg=mm.group(3),
                                    width=width, sign=sign, rw=rw,
                                    consumer='', consumer_sign=''))
    for section, ops in result.items():
        sequence = all_instructions[section]
        by_pc = {pc: i for i, (pc, _, _) in enumerate(sequence)}
        for load in ops:
            if load['rw'] != 'r' or load['opcode'] in ('lwl', 'lwr'):
                continue
            i = by_pc[load['pc']]
            target = sequence[i][2][0]
            votes = []
            for _, op, args in sequence[i + 1:i + 9]:
                if op.startswith(('b', 'j')):
                    break
                if op in CONSUMER_SIGN:
                    uses = args if op in ('div', 'divu') else args[1:]
                    if target in uses:
                        votes.append(op)
                if args and args[0] == target and op not in ('sw', 'sh', 'sb', 'swl', 'swr',
                                                              'mult', 'multu', 'div', 'divu'):
                    break
            if len(votes) == 1:
                load['consumer'] = votes[0]
                load['consumer_sign'] = CONSUMER_SIGN[votes[0]]
    return result


def stable_parameter_registers(disassembly):
    """Prove a saved register contains a parameter throughout one section.

    A single initial move from aN to sN qualifies until the next write to sN.
    This deliberately leaves local pointers and rebased pointers unmapped.
    """
    section = None
    seen = set()
    writes = defaultdict(lambda: defaultdict(list))
    calls = defaultdict(list)
    for raw in disassembly.splitlines():
        m = SECTION.match(raw)
        if m:
            section = m.group(1)
            seen.add(section)
            continue
        m = INST.match(raw)
        if not m or section is None:
            continue
        op, operand = m.group(2), m.group(3).strip()
        if op in ('jal', 'jalr'):
            calls[section].append(int(m.group(1), 16))
        if op.startswith(('b', 'j')) or op in ('sw', 'sh', 'sb', 'swl', 'swr', 'mult', 'multu', 'div', 'divu', 'mtlo', 'mthi'):
            continue
        first = operand.split(',', 1)[0]
        if re.fullmatch(r'[sa][0-7]', first):
            writes[section][first].append((int(m.group(1), 16), op, operand))
    result = defaultdict(dict)
    for section in seen:
        regs = writes[section]
        call_end = min(calls[section], default=float('inf'))
        for arg in range(4):
            reg = f'a{arg}'
            end = min(regs.get(reg, [(float('inf'), '', '')])[0][0], call_end)
            result[section][reg] = (arg, end)
        for reg, entries in regs.items():
            if not reg.startswith('s'):
                continue
            _, op, operand = entries[0]
            m = re.fullmatch(reg + r',a([0-3])', operand.replace(' ', ''))
            if op == 'move' and m:
                result[section][reg] = (int(m.group(1)), entries[1][0] if len(entries) > 1 else float('inf'))
    return result


def raw_local_registers(assembly):
    """Read GCC COFF register-local records inside each raw `.ent` function."""
    current = None
    result = defaultdict(lambda: defaultdict(list))
    for line in assembly.splitlines():
        m = RAW_ENT.match(line)
        if m:
            current = m.group(1)
            continue
        if RAW_END.match(line):
            current = None
            continue
        m = RAW_REGISTER.match(line)
        if current and m:
            reg = REGISTER_NUMBERS.get(int(m.group(2)))
            if reg:
                result[current][m.group(1)].append(reg)
    return result


def raw_stack_locals(assembly):
    """Read frame-relative GCC local-object locations for `$sp` frames."""
    current = None
    stack_frame = False
    result = defaultdict(lambda: defaultdict(list))
    for line in assembly.splitlines():
        match = RAW_ENT.match(line)
        if match:
            current, stack_frame = match.group(1), False
            continue
        if RAW_END.match(line):
            current, stack_frame = None, False
            continue
        if current and re.match(r'^\s*\.frame\s+\$sp,', line):
            stack_frame = True
        match = RAW_STACK.match(line)
        if current and stack_frame and match:
            result[current][match.group(1)].append(int(match.group(2)))
    return result


def stack_offsets_for_function(func, raw):
    """Bind one source local object to one compiler stack slot by name."""
    objects = defaultdict(set)
    for site in func['sites']:
        node = site.get('node')
        while isinstance(node, tuple) and len(node) == 3 and node[0] == 'F':
            node = node[1]
        if isinstance(node, str) and node.startswith('o:'):
            objects[node.rsplit(':', 2)[-2]].add(node)
    return {next(iter(nodes)): locations[0] for name, nodes in objects.items()
            if len(nodes) == len(locations := raw.get(name, [])) == 1}


def local_registers_for_function(func, raw):
    """Require one source local and one compiler location for a local name."""
    nodes = defaultdict(set)
    for site in func['sites']:
        node = site.get('node')
        if isinstance(node, str) and node.startswith('v:'):
            nodes[node.rsplit(':', 2)[-2]].add(node)
        elif (isinstance(node, str) and node.startswith('o:') and
              site.get('delta') == 0 and site.get('width') == 4 and
              site.get('sign') == 'p'):
            # A four-byte aggregate's pointer member at offset zero shares
            # the raw GCC register location of the aggregate itself.
            nodes[node.rsplit(':', 2)[-2]].add(('F', node, 0))
    result = {}
    for name, candidates in nodes.items():
        registers = raw.get(name, [])
        if len(candidates) == len(registers) == 1:
            result[next(iter(candidates))] = registers[0]
    return result


def sections(path, root):
    out = run(['mipsel-linux-gnu-objdump', '-h', str(path)], root)
    return set(re.findall(r'\s(\.text\.[^\s]+)\s+[0-9a-fA-F]+\s', out))


def section_bytes(path, section, root, tmp):
    dest = tmp / (path.stem + '_' + section[6:] + '.bin')
    run(['mipsel-linux-gnu-objcopy', '-O', 'binary', '-j', section, str(path), str(dest)], root)
    return dest.read_bytes()


def compile_debug_with_raw(tool_root, cwd, input_path, debug, raw_path, version, flags, maspsx_flags):
    """Run the pinned wrapper stages once, retaining GCC's register records.

    The resulting executable sections still have to match the cached object
    byte for byte before either instruction or register evidence is used.
    """
    import os
    cc_dir = tool_root / 'toolchain/compilers' / ('gcc-' + version)
    run([str(cc_dir / 'gcc'), '-B' + str(cc_dir) + '/', '-S', '-O2',
         *flags.split(), '-g', '-I' + str(tool_root / 'include'), '-w',
         str(input_path), '-o', str(raw_path)], cwd)
    processed = raw_path.with_name('processed.s')
    with raw_path.open() as source, processed.open('w') as dest:
        subprocess.run(['python3', str(tool_root / 'tools/ccproc.py')], cwd=cwd,
                       stdin=source, stdout=dest, stderr=subprocess.PIPE,
                       text=True, check=True)
    maspsx = (os.environ.get('AZURE_MASPSX_COMPANION') or os.environ.get('AZURE_MASPSX')
              or str(tool_root / 'toolchain/maspsx/maspsx.py'))
    with processed.open() as source:
        subprocess.run([str(tool_root / '.venv/bin/python'), maspsx,
                        '--aspsx-version=2.79', '--dont-force-G0', '--run-assembler',
                        '--gnu-as-path=mipsel-linux-gnu-as', '-I' + str(tool_root),
                        '-I' + str(tool_root / 'include'), '-EL', '-march=r3000', '-G8',
                        *maspsx_flags.split(), '-o', str(debug)],
                       cwd=cwd, stdin=source, stdout=subprocess.PIPE,
                       stderr=subprocess.PIPE, text=True, check=True)


def exact_debug_sections(built, debug, root, tmp):
    """Admit debug sections with unique byte-identical cached counterparts.

    `-g` occasionally changes a section's symbol name without changing its
    executable bytes. Equal names are checked first; differing names require
    a unique byte sequence on *both* sides, so identical tiny functions cannot
    be accidentally interchanged.
    """
    cached_sections, debug_sections = sections(built, root), sections(debug, root)
    common = cached_sections & debug_sections
    exact = {s for s in common if section_bytes(built, s, root, tmp) ==
             section_bytes(debug, s, root, tmp)}
    cached_by_bytes, debug_by_bytes = defaultdict(list), defaultdict(list)
    for section in cached_sections - exact:
        cached_by_bytes[section_bytes(built, section, root, tmp)].append(section)
    for section in debug_sections - exact:
        debug_by_bytes[section_bytes(debug, section, root, tmp)].append(section)
    for content, debug_names in debug_by_bytes.items():
        if len(debug_names) == len(cached_by_bytes.get(content, [])) == 1:
            exact.add(debug_names[0])
    return exact


def kind(site, object_type=''):
    if site['spell'] in ('macro', 'F_macro'):
        return 'macro'
    if site['spell'].startswith('raw'):
        return 'byte cursor'
    field = (site.get('field') or '').split('[', 1)[0]
    if field in UNION_ALIASES and (site.get('decl') or '').startswith('@'):
        return 'union pun'
    if site['spell'] == 'member_view':
        if object_type and (site.get('decl') or '').startswith('@'):
            return 'named record'
        return 'view'
    return 'named record'


def member_path(site):
    base = site.get('base') or ''
    field = site.get('field') or ''
    if '->' in base:
        return base.split('->', 1)[1].replace('->', '.') + ('.' + field if field else '')
    if '.' in base:
        return base.split('.', 1)[1] + ('.' + field if field else '')
    return field


def parameter_aliases(func):
    """Resolve immutable, nonescaping local pointer copies to an incoming arg.

    A write with an unknown value or a second write invalidates the local.
    The source facts include compound assignments and address escapes.
    """
    writes = func.get('local_writes', {})
    escaped = set(func.get('escaped_locals', []))
    memo = {}

    def resolve(node, trail):
        if isinstance(node, str):
            param = re.fullmatch(r'p:.+:(\d+)', node)
            if param:
                return (int(param.group(1)), 0)
        if not isinstance(node, str) or not node.startswith('v:') or node in escaped or node in trail:
            return None
        if node in memo:
            return memo[node]
        assignments = writes.get(node, [])
        if len(assignments) != 1 or assignments[0] is None:
            return None
        origin, delta = assignments[0]
        base = resolve(origin, trail | {node})
        memo[node] = (base[0], base[1] + delta) if base else None
        return memo[node]

    return {node: alias for node in writes if (alias := resolve(node, set())) is not None}


def canonical_base(node, aliases, stack_locals=None):
    """Express a source base in terms of an argument or a pointer field load."""
    if isinstance(node, str):
        match = re.fullmatch(r'p:.+:(\d+)', node)
        if match:
            return ('arg', int(match.group(1))), 0
        if node.startswith('g:'):
            return ('global', node[2:]), 0
        if stack_locals and node in stack_locals:
            return ('stack',), stack_locals[node]
        if node in aliases:
            arg, delta = aliases[node]
            return ('arg', arg), delta
    if isinstance(node, tuple) and len(node) == 3 and node[0] == 'F':
        parent = canonical_base(node[1], aliases, stack_locals)
        if parent:
            key, delta = parent
            return ('field', key, delta + node[2]), 0
    return None


def stack_object_base(node):
    if isinstance(node, str):
        return node.startswith('o:')
    return isinstance(node, tuple) and len(node) == 3 and node[0] == 'F' and stack_object_base(node[1])


def proven_register_bases(disassembly, section, func, aliases, opcodes=None, stack_locals=None,
                          global_symbols=None):
    """Track straight-line pointer values and exact, unique pointer field loads.

    The state is discarded at control-flow edges and calls. Stack slots are
    tracked only at constant offsets from the entry stack pointer. A pointer
    load becomes a new base only when one source pointer access on that debug
    line identifies its parent and offset; an opcode's position is never used
    to choose between source accesses.

    Direct globals come from a `lui rt,%hi(sym)` / `%lo(sym)` pair. These are
    REL objects, so objdump prints no addend: the LO16 addend is the
    instruction's own immediate. `addiu rt,rs,%lo(sym)` therefore yields
    global+immediate, while a memory access `lbu rt,%lo(sym)(rs)` yields
    global+0 because join() adds the access's own offset (that same
    immediate). The pair is held (no base) when the `lui` immediate is
    non-zero, since the addend then has a high half the LO16 does not show,
    or when either instruction carries more than one relocation.
    """
    pointer_sources = defaultdict(list)
    line_loads = Counter((op['line'], op['offset']) for op in (opcodes or [])
                         if op['opcode'] == 'lw')
    branch_targets = set()
    global_loads = {}
    high_relocations = {}
    low_relocations = {}
    relocation_counts = Counter()
    global_symbols = global_symbols or {}
    scan_section = None
    previous_pc = None
    sp_writes = []
    for raw in disassembly.splitlines():
        match = SECTION.match(raw)
        if match:
            scan_section = match.group(1)
            continue
        match = INST.match(raw)
        if scan_section != section:
            continue
        if match:
            previous_pc = int(match.group(1), 16)
            pieces = [part.strip() for part in match.group(3).split(',')]
            if pieces and pieces[0] == 'sp' and match.group(2) not in OPS:
                sp_writes.append((previous_pc, match.group(2), pieces))
        relocation = re.match(r'^\s*[0-9a-f]+:\s+R_MIPS_GPREL16\s+([A-Za-z_]\w*)', raw)
        if relocation and previous_pc is not None:
            global_loads[previous_pc] = relocation.group(1)
        if previous_pc is not None and re.match(r'^\s*[0-9a-f]+:\s+R_MIPS_', raw):
            relocation_counts[previous_pc] += 1
        relocation = re.match(r'^\s*[0-9a-f]+:\s+R_MIPS_(HI16|LO16)\s+([A-Za-z_]\w*)\s*$', raw)
        if relocation and previous_pc is not None:
            (high_relocations if relocation.group(1) == 'HI16' else low_relocations)[previous_pc] = relocation.group(2)
        if match and match.group(2).startswith(('b', 'j')):
            target = re.search(r'(?:^|,)\s*([0-9a-f]+)\s*<', match.group(3))
            if target:
                branch_targets.add(int(target.group(1), 16))
    # More than one relocation on an instruction leaves its HI16/LO16 pairing
    # ambiguous; such an instruction never proves a global base.
    for pc in [pc for pc in high_relocations if relocation_counts[pc] != 1]:
        del high_relocations[pc]
    for pc in [pc for pc in low_relocations if relocation_counts[pc] != 1]:
        low_relocations[pc] = None
    negative_sp = []
    unsafe_sp = False
    for pc, op, pieces in sp_writes:
        if op != 'addiu' or len(pieces) != 3 or pieces[1] != 'sp':
            unsafe_sp = True
            break
        try:
            amount = int(pieces[2], 0)
        except ValueError:
            unsafe_sp = True
            break
        if amount < 0:
            negative_sp.append(pc)
    if len(negative_sp) > 1 or (negative_sp and negative_sp[0] != 0):
        unsafe_sp = True
    for site in func['sites']:
        if (site.get('rw') != 'r' or site.get('width') != 4 or
                site.get('sign') != 'p' or site.get('line') is None or
                site.get('delta') is None):
            continue
        base = canonical_base(site.get('node'), aliases, stack_locals)
        if base:
            pointer_sources[(site['line'], base[0], base[1] + site['delta'])].append(site)
    current_section = None
    line = None
    registers = {f'a{i}': (('arg', i), 0) for i in range(4)}
    if not unsafe_sp:
        registers['sp'] = (('stack',), 0)
    stack = {16 + 4 * i: (('arg', 4 + i), 0) for i in range(8)} if not unsafe_sp else {}
    high_halves = {}
    sp_delta = 0
    result = {}
    for raw in disassembly.splitlines():
        match = SECTION.match(raw)
        if match:
            current_section, line = match.group(1), None
            registers = {f'a{i}': (('arg', i), 0) for i in range(4)}
            if not unsafe_sp:
                registers['sp'] = (('stack',), 0)
            stack = ({16 + 4 * i: (('arg', 4 + i), 0) for i in range(8)}
                     if not unsafe_sp else {})
            high_halves = {}
            sp_delta = None if unsafe_sp else 0
            continue
        if current_section != section:
            continue
        match = LINE.match(raw.strip())
        if match:
            line = int(match.group(1))
            continue
        match = INST.match(raw)
        if not match:
            continue
        pc, op, operand = int(match.group(1), 16), match.group(2), match.group(3).strip()
        if pc in branch_targets:
            registers = {'sp': (('stack',), sp_delta)} if sp_delta is not None else {}
            stack.clear()
            high_halves.clear()
        args = [p.strip() for p in operand.split(',')]
        mem = MEM.match(operand) if op in OPS else None
        if mem:
            reg, offset, base_reg = mem.group(1), int(mem.group(2), 0), mem.group(3)
            provenance = registers.get(base_reg)
            if provenance:
                result[pc] = provenance
            # A matching HI16/LO16 relocation identifies a direct global
            # object access even when the assembler prints a zero high half.
            # The access's own immediate is the LO16 addend; join() adds it.
            symbol = low_relocations.get(pc)
            if symbol and high_halves.get(base_reg) == (symbol, 0):
                result[pc] = (('global', global_symbols.get(symbol, symbol)), 0)
            elif pc in low_relocations:
                result.pop(pc, None)
            if op in ('sw', 'sh', 'sb', 'swl', 'swr'):
                if base_reg == 'sp' and sp_delta is not None:
                    slot = sp_delta + offset
                    if op == 'sw' and reg in registers:
                        stack[slot] = registers[reg]
                    else:
                        stack.pop(slot, None)
                else:
                    # A store through an unknown alias could modify a pointer
                    # field. Do not reuse a field-load provenance past it.
                    registers = {r: v for r, v in registers.items() if v[0][0] != 'field'}
                continue
        if op.startswith(('b', 'j')):
            registers = {'sp': (('stack',), sp_delta)} if sp_delta is not None else {}
            stack.clear()
            high_halves.clear()
            continue
        if not args:
            continue
        dest = args[0]
        if not re.fullmatch(r'(?:[astv][0-9]|t[89]|sp|fp)', dest):
            continue
        previous_high = high_halves.get(dest)
        high_halves.pop(dest, None)
        if op == 'lui' and pc in high_relocations and len(args) == 2:
            try:
                high = int(args[1], 0)
            except ValueError:
                high = None
            if high is not None:
                high_halves[dest] = (high_relocations[pc], high)
        value = None
        if op == 'move' and len(args) == 2:
            value = registers.get(args[1])
        elif op in ('addu', 'or') and len(args) == 3:
            if args[2] == 'zero':
                value = registers.get(args[1])
            elif args[1] == 'zero':
                value = registers.get(args[2])
        elif op == 'addiu' and len(args) == 3:
            try:
                amount = int(args[2], 0)
            except ValueError:
                amount = None
            symbol = low_relocations.get(pc)
            pair = previous_high if dest == args[1] else high_halves.get(args[1])
            if pc in low_relocations:
                # %lo(sym): the immediate is the addend. Hold the pair when the
                # lui carried a high half or the pairing is not unique.
                if symbol and amount is not None and pair == (symbol, 0):
                    value = (('global', global_symbols.get(symbol, symbol)), amount)
            elif amount is not None:
                if dest == args[1] == 'sp':
                    if amount > 0:
                        sp_delta = None
                        stack.clear()
                    elif sp_delta is not None:
                        sp_delta += amount
                        value = (('stack',), sp_delta)
                elif args[1] in registers:
                    key, delta = registers[args[1]]
                    value = (key, delta + amount)
        elif op == 'lw' and mem:
            if base_reg == 'sp' and sp_delta is not None:
                value = stack.get(sp_delta + offset)
            if value is None and base_reg == 'gp' and pc in global_loads:
                value = (('field', ('global', global_loads[pc]), 0), 0)
            if value is None and line is not None and provenance and line_loads[line, offset] == 1:
                key, delta = provenance
                candidates = pointer_sources.get((line, key, delta + offset), [])
                if len(candidates) == 1:
                    value = (('field', key, delta + offset), 0)
        if dest == 'sp' and value is None:
            sp_delta = None
            stack.clear()
        if value is None:
            registers.pop(dest, None)
        else:
            registers[dest] = value
    return result


def join(sites, opcodes, parameter_registers=None, object_types=None, aliases=None,
         local_registers=None, proven_bases=None, exact_section=True, stack_locals=None):
    """Bijective exact joins, including unique cross-line scheduler moves.

    The fallback omits the debug line only when the complete function has one
    source access and one opcode for the proven register/offset/width/direction.
    It cannot assign one of several same-field accesses by source order.
    """
    parameter_registers = parameter_registers or {}
    object_types = object_types or {}
    aliases = aliases or {}
    local_registers = local_registers or {}
    proven_bases = proven_bases or {}
    stack_locals = stack_locals or {}
    expanded = [dict(s, rw=direction, compound=int(s['rw'] == 'rw')) for s in sites
                for direction in (('r', 'w') if s['rw'] == 'rw' else (s['rw'],))]
    by_static, by_proven = defaultdict(list), defaultdict(list)
    for index, op in enumerate(opcodes):
        by_static[(op['offset'], op['width'], op['rw'], op['reg'])].append(index)
        base = proven_bases.get(op['pc'])
        if base:
            by_proven[(base[0], base[1] + op['offset'], op['width'], op['rw'])].append(index)

    facts = []
    source_shapes = Counter()
    for s in expanded:
        node = s.get('node')
        base = canonical_base(node, aliases, stack_locals)
        local = local_registers.get(node)
        static = None
        shape = None
        if s.get('delta') is not None and s.get('width'):
            if local:
                static = (s['delta'], s['width'], s['rw'], local, float('inf'))
            elif base and base[0][0] == 'arg':
                regs = [reg for reg, (arg, _) in parameter_registers.items() if arg == base[0][1]]
                saved = [reg for reg in regs if reg.startswith('s')]
                if saved:
                    regs = saved
                if len(regs) == 1:
                    reg = regs[0]
                    static = (s['delta'] + base[1], s['width'], s['rw'], reg,
                              parameter_registers[reg][1])
            if base:
                shape = (base[0], base[1] + s['delta'], s['width'], s['rw'])
                source_shapes[shape] += 1
        facts.append((static, shape, bool(local)))

    def candidate_ops(index, same_line):
        s = expanded[index]
        static, shape, _ = facts[index]
        found = set()
        if static:
            offset, width, rw, reg, end = static
            found.update(i for i in by_static.get((offset, width, rw, reg), [])
                         if opcodes[i]['pc'] < end and
                         (not same_line or opcodes[i]['line'] == s.get('line')))
        if shape:
            found.update(i for i in by_proven.get(shape, [])
                         if not same_line or opcodes[i]['line'] == s.get('line'))
        return found

    candidates = [candidate_ops(i, True) if s.get('line') is not None else set()
                  for i, s in enumerate(expanded)]
    same_line_claimed = set().union(*candidates) if candidates else set()
    for i, s in enumerate(expanded):
        _, shape, local = facts[i]
        if candidates[i] or shape is None or local or source_shapes[shape] != 1:
            continue
        whole = candidate_ops(i, False)
        if len(whole) == 1 and next(iter(whole)) not in same_line_claimed:
            candidates[i] = whole
    claimants = defaultdict(list)
    for i, choices in enumerate(candidates):
        for op_index in choices:
            claimants[op_index].append(i)
    line_shapes = {(op['line'], op['offset'], op['width'], op['rw']) for op in opcodes}
    retail_shapes = {(op['offset'], op['width'], op['rw']) for op in opcodes}
    emitted = []
    for i, s in enumerate(expanded):
        choices = candidates[i]
        mapped = len(choices) == 1 and len(claimants[next(iter(choices))]) == 1
        op = opcodes[next(iter(choices))] if mapped else None
        status = 'mapped' if mapped else 'ambiguous' if choices else 'unmapped'
        if mapped:
            reason = ''
        elif not exact_section:
            reason = 'no_exact_section'
        elif len(choices) > 1:
            reason = 'no_unique_retail_opcode'
        elif choices:
            reason = 'no_unique_source_access'
        elif s.get('line') is None:
            reason = 'no_debug_line'
        elif s.get('delta') is None or not s.get('width'):
            reason = 'unknown_source_offset_or_width'
        elif stack_object_base(s.get('node')):
            reason = 'stack_local'
        elif s['spell'] in ('macro', 'F_macro'):
            reason = 'macro_expansion'
        elif facts[i][0] is None and facts[i][1] is None:
            reason = 'base_not_proven'
        elif (s['line'], s['delta'], s['width'], s['rw']) in line_shapes:
            reason = 'base_register_not_proven'
        elif (s['delta'], s['width'], s['rw']) in retail_shapes:
            reason = 'debug_line_or_rebase'
        else:
            reason = 'no_matching_retail_access'
        object_type = object_types.get(s.get('node'), '') if isinstance(s.get('node'), str) else ''
        base_kind = kind(s, object_type)
        declared = s['sign']
        agreement = bool(op and base_kind == 'named record' and s['width'] == op['width'] and
                         (op['rw'] == 'w' or op['sign'] == '?' or declared == op['sign']))
        emitted.append(dict(function=s['func'], file=s['file'], line=s['line'],
                            base_type=s.get('decl') or s.get('ctype') or '', base_kind=base_kind,
                            object_type=object_type,
                            base_expression=s.get('base') or '', member_path=member_path(s),
                            offset=s['delta'], declared_width=s['width'], declared_sign=declared,
                            direction=s['rw'], opcode=op['opcode'] if op else '',
                            retail_sign=op['sign'] if op else '', pc=op['pc'] if op else '',
                            compound=s.get('compound', 0),
                            consumer=op.get('consumer', '') if op else '',
                            consumer_sign=op.get('consumer_sign', '') if op else '',
                            status=status, reason=reason, agreement=int(agreement)))
    return emitted


def recipes(db, source):
    """Return every pinned placement, preferring the physical source key."""
    rows = list(db.execute('SELECT output,args,source FROM recipe WHERE source=?', (source,)))
    if not rows:
        rows = list(db.execute('SELECT output,args,source FROM recipe WHERE physical=?', (source,)))
    return rows


def recipe(db, source):
    rows = recipes(db, source)
    return rows[0] if len(rows) == 1 else None


def object_types_for_function(func):
    attachments = defaultdict(set)
    strong_types = defaultdict(set)
    for node, delta, ident, strong in func['attach']:
        if isinstance(node, str) and delta == 0:
            attachments[node].add(ident)
            if strong:
                strong_types[node].add(ident)
    # An explicit cast through NODE_HEADER(body) can attach ObjectNodeHeader
    # at zero even though the pointer still denotes a body. Any conflicting
    # declared view/record identity keeps that node unproven.
    return {node: next(iter(types)) for node, types in attachments.items()
            if len(types) == 1 and strong_types[node] == types}


def unresolved_source_rows(root, source):
    """Keep source accesses visible when retail instructions cannot be inspected."""
    facts = F.extract_tu((str(root), source))
    if facts['error']:
        return [], f'{source}: clang: {facts["error"]}'
    return [row for func in facts['functions']
            for row in join(func['sites'], [], object_types=object_types_for_function(func),
                            exact_section=False)], None


@lru_cache(maxsize=4)
def symbol_aliases(root):
    aliases = defaultdict(set)
    for line in (Path(root) / 'config/names.tsv').read_text().splitlines():
        if not line or line.startswith('#'):
            continue
        parts = line.split('\t', 3)
        if len(parts) >= 3:
            aliases[parts[2]].add(parts[1])
    return {name: next(iter(old)) for name, old in aliases.items() if len(old) == 1}


@lru_cache(maxsize=4)
def relocation_aliases(root):
    """Return only old symbols with one declared source spelling."""
    names = defaultdict(set)
    for source, old in symbol_aliases(root).items():
        names[old].add(source)
    return {old: next(iter(source)) for old, source in names.items() if len(source) == 1}


def measure(root, source, db, out, selected=None):
    selected = selected if selected is not None else recipe(db, source)
    if selected is None:
        rows, error = unresolved_source_rows(root, source)
        return rows, error or f'{source}: no unique compile recipe'
    cached, args, command = selected
    if args in (None, 'null'):
        # SLUS recipes can append a rodata trim command. The compiler flags
        # belong only to the first command; an empty quoted maspsx argument
        # immediately before && otherwise becomes the literal token '&&'.
        argv = shlex.split(command.split('&&', 1)[0])
        if len(argv) < 4 or argv[0] != 'tools/cc.sh':
            rows, error = unresolved_source_rows(root, source)
            return rows, error or f'{source}: unsupported SLUS recipe command'
        version = argv[3]
        flags = argv[4] if len(argv) > 4 else ''
        maspsx = argv[5] if len(argv) > 5 else ''
        input_path = root / 'build_slus' / argv[1]
        tool_root = root / 'build_slus'
        cwd = root / 'build_slus'
    else:
        version, flags, maspsx = json.loads(args)
        input_path = root / source
        tool_root = root / 'build_ovl'
        cwd = root
    built = root / cached
    if not built.is_file():
        rows, error = unresolved_source_rows(root, source)
        return rows, error or f'{source}: cached object missing'
    with tempfile.TemporaryDirectory(prefix='access_', dir=out) as tmp_name:
        tmp = Path(tmp_name)
        debug = tmp / 'debug.o'
        raw_path = tmp / 'registers.s'
        compile_debug_with_raw(tool_root, cwd, input_path, debug, raw_path, version, flags, maspsx)
        dis = run(['mipsel-linux-gnu-objdump', '-d', '-r', '-l', str(debug)], root)
        debug_ops = instructions(dis)
        registers = stable_parameter_registers(dis)
        exact = exact_debug_sections(built, debug, root, tmp)
        facts = F.extract_tu((str(root), source))
        if facts['error'] and args in (None, 'null'):
            # Some src/slus wrappers include a generated partition at a path
            # that exists only in build_slus. Parse the exact compiled source
            # there, retaining its true generated file and line in each row.
            generated = F.extract_tu((str(root / 'build_slus'), argv[1]))
            if not generated['error']:
                for func in generated['functions']:
                    for site in func['sites']:
                        site['file'] = str((root / 'build_slus' / site['file']).resolve().relative_to(root))
                facts = generated
        if facts['error']:
            return [], f'{source}: clang: {facts["error"]}'
        funcs = facts['functions']
        # Most physical TUs hold one function, often renamed by slus.h. For
        # multi-function TUs, only literal symbol-name matches are admissible.
        assign = {}
        if len(funcs) == len(exact) == 1:
            assign[funcs[0]['func']] = next(iter(exact))
        else:
            aliases = symbol_aliases(str(root))
            for f in funcs:
                name = '.text.' + aliases.get(f['func'], f['func'])
                if name in exact:
                    assign[f['func']] = name
        rows = []
        raw_registers = (raw_local_registers(raw_path.read_text())
                         if any(isinstance(site.get('node'), str) and site['node'].startswith(('v:', 'o:'))
                                for f in funcs for site in f['sites']) else {})
        raw_stacks = raw_stack_locals(raw_path.read_text())
        for f in funcs:
            s = assign.get(f['func'])
            object_types = object_types_for_function(f)
            if s:
                aliases = parameter_aliases(f)
                stacks = stack_offsets_for_function(f, raw_stacks.get(f['func'], {}))
                rows.extend(join(f['sites'], debug_ops.get(s, []), registers.get(s), object_types,
                                 aliases,
                                 local_registers_for_function(f, raw_registers.get(f['func'], {})),
                                 proven_register_bases(dis, s, f, aliases, debug_ops.get(s, []), stacks,
                                                       relocation_aliases(str(root))),
                                 stack_locals=stacks))
            else:
                rows.extend(join(f['sites'], [], object_types=object_types, exact_section=False))
        missing = len(funcs) - len(assign)
        return rows, f'{source}: {missing} functions have no exact section mapping' if missing else None


def summarize(rows):
    mapped = [r for r in rows if r['status'] == 'mapped']
    source_by_kind = Counter(r['base_kind'] for r in rows)
    by_kind = Counter(r['base_kind'] for r in mapped)
    agrees = sum(r['agreement'] for r in mapped)
    return dict(source_sites=len(rows), mapped=len(mapped), agreement=agrees,
                agreement_pct=100 * agrees / len(mapped) if mapped else None,
                by_kind=dict(sorted(by_kind.items())),
                source_by_kind=dict(sorted(source_by_kind.items())),
                unjoined_by_reason=dict(sorted(Counter(r.get('reason') or 'unclassified_previous'
                                                        for r in rows if r['status'] != 'mapped').items())),
                coverage_by_kind={kind: 100 * by_kind[kind] / count
                                  for kind, count in sorted(source_by_kind.items())})


def width_consistency(rows, db):
    """Check direct named fields against independent record layout sizes."""
    declared = defaultdict(set)
    for record, name, offset, size in db.execute(
            'SELECT record,name,off,size FROM record_member WHERE depth=0'):
        if size is not None:
            declared[record, name, offset].add(size)
    checked, mismatches = 0, []
    for row in rows:
        if row['status'] != 'mapped' or row['base_kind'] != 'named record':
            continue
        path = row['member_path']
        if not path or '.' in path or '[' in path or not isinstance(row.get('offset'), int):
            continue
        record = row['base_type']
        offset = row['offset'] + 32 if record == 'ObjectNodeHeader' and row['offset'] < 0 else row['offset']
        sizes = declared.get((record, path, offset), set())
        if len(sizes) != 1:
            continue
        checked += 1
        opcode_width = OPS[row['opcode']][0]
        if opcode_width != next(iter(sizes)):
            mismatches.append((row['file'], row['line'], row['function'], record,
                               path, offset, next(iter(sizes)), opcode_width, row['opcode']))
    return checked, mismatches


SHARED = ('ActorRecord', 'TownObjectRecord', 'ObjectNodeHeader')


def shared_sign_rows(rows, db=None):
    fields = defaultdict(Counter)
    sites = defaultdict(list)
    consumer_votes = defaultdict(Counter)
    declared = {}
    if db is not None:
        for record, name, offset, width in db.execute(
                'SELECT record,name,off,size FROM record_member WHERE depth=0 '
                'AND record IN (?,?,?)', SHARED):
            fields[(record, name, offset, width)]
            declared[(record, name)] = (offset, width)
    for row in rows:
        record = (row.get('base_type') if row.get('base_type') in SHARED else
                  row.get('object_type'))
        if record not in SHARED:
            continue
        if db is not None and row.get('base_kind') not in ('named record', 'union pun'):
            continue
        path = row['member_path']
        if not path:
            continue
        if row.get('offset') in (None, '') or row.get('declared_width') in (None, ''):
            continue
        top = path.split('.', 1)[0].split('[', 1)[0]
        offset = int(row['offset'])
        width = int(row['declared_width'])
        if record == 'ObjectNodeHeader':
            # NODE_HEADER(body)->field is addressed relative to the body.
            # The body pointer may also carry a misleading strong cast at
            # offset zero, so require the *declared* header base type.
            if row.get('base_type') != 'ObjectNodeHeader':
                continue
            if offset < 0:
                offset += 32
        if declared:
            if declared.get((record, top)) != (offset, width):
                continue
            path = top
        elif path.endswith(('.u', '.s')):
            path = path[:-2]
        key = (record, path, offset, width)
        if row['status'] == 'mapped' and row['direction'] == 'r':
            fields[key][row['opcode']] += 1
            sites[key].append(row)
            if row.get('consumer_sign') in ('s', 'u'):
                consumer_votes[key][row['consumer_sign']] += 1
    result = []
    for (record, path, offset, width), opcodes in sorted(fields.items()):
        signed = sum(opcodes[op] for op in ('lb', 'lh'))
        unsigned = sum(opcodes[op] for op in ('lbu', 'lhu'))
        majority = 'signed' if signed > unsigned else 'unsigned' if unsigned > signed else 'tie_or_unknown'
        suggested_type = (('s' if majority == 'signed' else 'u') + str(width * 8)
                          if majority != 'tie_or_unknown' and width in (1, 2, 4) else '')
        recommendation = ('sample_only' if signed != unsigned else
                          'hold_consumer' if opcodes['lw'] else 'hold_no_loads' if not any(opcodes.values()) else
                          'hold_tie')
        minority = [f"{r['file']}:{r['line']}" for r in sites[(record, path, offset, width)]
                    if (majority == 'signed' and r['retail_sign'] == 'u') or
                       (majority == 'unsigned' and r['retail_sign'] == 's')]
        minority_cast = ('(' + ('u' if majority == 'signed' else 's') + str(width * 8) + ')'
                         if minority and suggested_type else '')
        consumer = consumer_votes[(record, path, offset, width)]
        consumer_majority = ('signed' if consumer['s'] > consumer['u'] else
                             'unsigned' if consumer['u'] > consumer['s'] else 'tie_or_unknown')
        load_count = sum(opcodes.values())
        if consumer_majority != 'tie_or_unknown':
            if majority != 'tie_or_unknown' and majority != consumer_majority:
                recommendation = 'review_consumer_conflict'
            elif majority == 'tie_or_unknown':
                recommendation = 'hold_consumer_only'
        result.append([record, path, offset, width, opcodes['lb'], opcodes['lbu'],
                       opcodes['lh'], opcodes['lhu'], opcodes['lw'], majority,
                       suggested_type, minority_cast, recommendation, ','.join(minority),
                       load_count, int(load_count >= 5), consumer['s'], consumer['u'], consumer_majority])
    return result


def folder_rows(rows):
    groups = defaultdict(list)
    for row in rows:
        parts = Path(row['file']).parts
        folder = '/'.join(parts[:3]) if len(parts) >= 3 and not parts[2].endswith('.c') else '/'.join(parts[:2])
        groups[folder].append(row)
    return [(folder, value['source_sites'], value['mapped'], value['agreement'],
             '' if value['agreement_pct'] is None else f"{value['agreement_pct']:.2f}")
            for folder, group in sorted(groups.items()) for value in [summarize(group)]]


def disagreement_rows(rows):
    groups = defaultdict(list)
    for row in rows:
        if row['status'] != 'mapped' or row['direction'] != 'r' or row['retail_sign'] not in ('s', 'u'):
            continue
        path = row['member_path']
        if not path:
            continue
        if path.endswith(('.s', '.u')):
            path = path[:-2]
        key = (row['object_type'] or row['base_type'], path, row['offset'], row['declared_width'])
        groups[key].append(row)
    result = []
    for (record, path, offset, width), group in sorted(groups.items()):
        signs = Counter(row['retail_sign'] for row in group)
        if signs['s'] == signs['u']:
            continue
        majority = 's' if signs['s'] > signs['u'] else 'u'
        for row in group:
            if row['declared_sign'] in ('s', 'u') and row['declared_sign'] != majority:
                result.append([record, path, offset, width, majority, row['file'], row['line'],
                               row['function'], row['opcode'], row['declared_sign']])
    return result


def merge_site_rows(existing, incoming, files=None):
    """A later complete physical-file measurement replaces an earlier one."""
    files = set(files) if files is not None else {row['file'] for row in incoming}
    return [row for row in existing if (row.get('physical_tu') or row['file']) not in files] + incoming


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--root', type=Path, default=HERE.parents[1])
    ap.add_argument('--codemap', type=Path, default=Path('build/codemap.db'))
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--source', action='append', default=[], help='physical TU relative to root; repeatable')
    ap.add_argument('--source-file', type=Path, help='newline-delimited physical TUs')
    ap.add_argument('--from-sites', type=Path, help='rebuild summaries from a previous access_sites.tsv')
    ap.add_argument('--merge-sites', action='append', type=Path, default=[],
                    help='replace rows for files in this additional access_sites.tsv; repeatable')
    args = ap.parse_args(argv)
    if args.merge_sites and not args.from_sites:
        ap.error('--merge-sites requires --from-sites')
    if not args.source and not args.source_file and not args.from_sites:
        ap.error('supply --source, --source-file, or --from-sites')
    root, out = args.root.resolve(), args.out.resolve()
    out.mkdir(parents=True, exist_ok=True)
    db = sqlite3.connect(root / args.codemap)
    rows, holds = [], []
    if args.from_sites:
        with args.from_sites.open() as stream:
            rows = list(csv.DictReader(stream, delimiter='\t'))
        replaced_files = set()
        for path in args.merge_sites:
            with path.open() as stream:
                incoming = list(csv.DictReader(stream, delimiter='\t'))
            source_manifest = path.parent / 'source_files.txt'
            files = (set(source_manifest.read_text().splitlines()) if source_manifest.is_file()
                     else {row['file'] for row in incoming})
            replaced_files.update(files)
            rows = merge_site_rows(rows, incoming, files)
            summary_path = path.parent / 'access_summary.json'
            if summary_path.is_file():
                holds.extend(json.loads(summary_path.read_text()).get('holds', []))
        for row in rows:
            row['physical_tu'] = row.get('physical_tu') or row['file']
            for key in ('line', 'offset', 'declared_width', 'pc', 'agreement'):
                row[key] = int(row[key]) if row.get(key) else 0
            if row['base_kind'] == 'view':
                row['base_kind'] = kind({'spell': 'member_view', 'decl': row['base_type'],
                                         'field': row['member_path'].rsplit('.', 1)[-1]}, row.get('object_type', ''))
                row['agreement'] = int(row['status'] == 'mapped' and row['base_kind'] == 'named record'
                                       and (row['direction'] == 'w' or row['retail_sign'] == '?'
                                            or row['declared_sign'] == row['retail_sign']))
        previous = out / 'access_summary.json'
        if previous.is_file():
            prior = json.loads(previous.read_text()).get('holds', [])
            holds = [hold for hold in prior if hold.split(':', 1)[0] not in replaced_files] + holds
    else:
        sources = list(args.source)
        if args.source_file:
            sources.extend(line.strip() for line in args.source_file.read_text().splitlines() if line.strip())
        sources = list(dict.fromkeys(sources))
        (out / 'source_files.txt').write_text(''.join(source + '\n' for source in sources))
        for source in sources:
            placements = recipes(db, source)
            for selected in placements or [None]:
                output = selected[0] if selected else ''
                try:
                    got, hold = measure(root, source, db, out, selected)
                    rows.extend(dict(row, physical_tu=source, recipe_output=output) for row in got)
                    if hold:
                        holds.append(hold + (f' [recipe {output}]' if len(placements) > 1 else ''))
                except (OSError, subprocess.CalledProcessError, ValueError) as exc:
                    try:
                        unresolved, error = unresolved_source_rows(root, source)
                        rows.extend(dict(row, physical_tu=source, recipe_output=output) for row in unresolved)
                        holds.append((error or f'{source}: {exc}') +
                                     (f' [recipe {output}]' if len(placements) > 1 else ''))
                    except (OSError, subprocess.CalledProcessError, ValueError):
                        holds.append(f'{source}: {exc}' +
                                     (f' [recipe {output}]' if len(placements) > 1 else ''))
    cols = ['function', 'physical_tu', 'recipe_output', 'file', 'line', 'base_type', 'base_kind', 'object_type', 'base_expression',
            'member_path', 'offset', 'declared_width', 'declared_sign', 'direction',
            'opcode', 'retail_sign', 'pc', 'compound', 'consumer', 'consumer_sign', 'status', 'reason', 'agreement']
    with (out / 'access_sites.tsv').open('w', newline='') as stream:
        writer = csv.DictWriter(stream, cols, delimiter='\t', lineterminator='\n')
        writer.writeheader()
        writer.writerows(rows)
    with (out / 'shared_field_signs.tsv').open('w', newline='') as stream:
        writer = csv.writer(stream, delimiter='\t', lineterminator='\n')
        writer.writerow(['record', 'field', 'offset', 'width', 'lb', 'lbu', 'lh', 'lhu', 'lw',
                         'majority', 'suggested_type', 'minority_value_cast', 'recommendation', 'minority_sites',
                         'mapped_loads', 'at_least_five', 'consumer_signed', 'consumer_unsigned',
                         'consumer_majority'])
        writer.writerows(shared_sign_rows(rows, db))
    with (out / 'access_folders.tsv').open('w', newline='') as stream:
        writer = csv.writer(stream, delimiter='\t', lineterminator='\n')
        writer.writerow(['folder', 'source_sites', 'mapped', 'agreement', 'agreement_pct'])
        writer.writerows(folder_rows(rows))
    with (out / 'access_disagreements.tsv').open('w', newline='') as stream:
        writer = csv.writer(stream, delimiter='\t', lineterminator='\n')
        writer.writerow(['record', 'field', 'offset', 'width', 'majority_sign', 'file', 'line',
                         'function', 'opcode', 'declared_sign'])
        writer.writerows(disagreement_rows(rows))
    result = dict(summarize(rows), holds=holds)
    checked, mismatches = width_consistency(rows, db)
    result['width_consistency'] = {'checked': checked, 'mismatches': len(mismatches)}
    with (out / 'width_mismatches.tsv').open('w', newline='') as stream:
        writer = csv.writer(stream, delimiter='\t', lineterminator='\n')
        writer.writerow(['file', 'line', 'function', 'record', 'field', 'offset',
                         'declared_size', 'opcode_width', 'opcode'])
        writer.writerows(mismatches)
    (out / 'access_summary.json').write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(result))
    return int(bool(holds))


if __name__ == '__main__':
    raise SystemExit(main())
