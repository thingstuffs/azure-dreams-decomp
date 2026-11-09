import unittest
import tempfile
import sqlite3
import io
from contextlib import redirect_stdout
from pathlib import Path
from unittest.mock import patch

from access_census import instructions, join, stable_parameter_registers, summarize, symbol_aliases, kind, shared_sign_rows, merge_site_rows, measure, exact_debug_sections, parameter_aliases, object_types_for_function, raw_local_registers, local_registers_for_function, raw_stack_locals, stack_offsets_for_function, recipes, main, proven_register_bases, width_consistency
import field_census as F


class AccessCensusTests(unittest.TestCase):
    DIS = '''Disassembly of section .text.func_12345678:
00000000 <func_12345678>:
   0: 00808021 move s0,a0
/tmp/src/a.c:4
   4: 92020002 lbu v0,2(s0)
   8: a2020003 sb v0,3(s0)
/tmp/src/a.c:5
   c: 86030004 lh v1,4(s0)
  10: 8fb00010 lw s0,16(sp)
'''

    def site(self, line, off, width, sign, rw='r'):
        return dict(file='src/a.c', func='f', line=line, node='p:f:0', delta=off,
                    width=width, sign=sign, rw=rw, spell='member_named',
                    decl='ActorRecord', ctype='u8', field='field', base='actor')

    def test_exact_register_line_offset_and_sign(self):
        ops = instructions(self.DIS)['.text.func_12345678']
        regs = stable_parameter_registers(self.DIS)['.text.func_12345678']
        rows = join([self.site(4, 2, 1, 'u'), self.site(4, 3, 1, 's', 'w'),
                     self.site(5, 4, 2, 'u')], ops, regs)
        self.assertEqual([(r['opcode'], r['agreement']) for r in rows],
                         [('lbu', 1), ('sb', 1), ('lh', 0)])
        self.assertEqual(summarize(rows)['agreement_pct'], 200 / 3)
        self.assertEqual(summarize(rows)['source_by_kind']['named record'], 3)

    def test_reject_ambiguous_and_unproven_base(self):
        ops = instructions(self.DIS)['.text.func_12345678']
        regs = stable_parameter_registers(self.DIS)['.text.func_12345678']
        duplicate = [self.site(4, 2, 1, 'u')] * 2
        unknown = self.site(4, 3, 1, 'u', 'w')
        unknown['node'] = 'v:local'
        rows = join(duplicate + [unknown], ops, regs)
        self.assertEqual([r['status'] for r in rows], ['ambiguous', 'ambiguous', 'unmapped'])
        self.assertEqual([r['reason'] for r in rows[:2]], ['no_unique_source_access'] * 2)
        held = join([self.site(4, 2, 1, 'u')], [], exact_section=False)
        self.assertEqual(summarize(held)['unjoined_by_reason'], {'no_exact_section': 1})

    def test_direct_argument_compound_read_write(self):
        dis = '''Disassembly of section .text.func_12345678:
/tmp/src/a.c:6
   0: 94a2001e lhu v0,30(a1)
   4: a4a2001e sh v0,30(a1)
'''
        site = self.site(6, 30, 2, 'u', 'rw')
        site['node'] = 'p:f:1'
        ops = instructions(dis)['.text.func_12345678']
        regs = stable_parameter_registers(dis)['.text.func_12345678']
        rows = join([site], ops, regs)
        self.assertEqual([(r['direction'], r['opcode']) for r in rows], [('r', 'lhu'), ('w', 'sh')])
        self.assertEqual([r['compound'] for r in rows], [1, 1])   # a compound join is flagged for the sign vote
        plain = join([self.site(6, 30, 2, 'u', 'r')], ops[:1], regs)
        self.assertEqual(plain[0].get('compound', 0), 0)

    def test_unique_scheduler_move_across_debug_lines(self):
        dis = '''Disassembly of section .text.func_12345678:
   0: 00808021 move s0,a0
/tmp/src/a.c:10
   4: 8e02000c lw v0,12(s0)
'''
        ops = instructions(dis)['.text.func_12345678']
        regs = stable_parameter_registers(dis)['.text.func_12345678']
        self.assertEqual(join([self.site(9, 12, 4, '?')], ops, regs)[0]['opcode'], 'lw')
        # Two source occurrences cannot be assigned to one retail load.
        rows = join([self.site(9, 12, 4, '?'), self.site(11, 12, 4, '?')], ops, regs)
        self.assertEqual([r['status'] for r in rows], ['unmapped', 'unmapped'])
        # Two retail loads cannot be assigned to one source occurrence.
        rows = join([self.site(9, 12, 4, '?')], ops + [dict(ops[0], pc=8)], regs)
        self.assertEqual(rows[0]['status'], 'unmapped')

    def test_unique_build_symbol_alias(self):
        with tempfile.TemporaryDirectory() as td:
            config = Path(td) / 'config'
            config.mkdir()
            (config / 'names.tsv').write_text('0x80000000\tfunc_80000000\tadvance\tevidence\n'
                                              '0x80000004\tfunc_80000004\tduplicate\tevidence\n'
                                              '0x80000008\tfunc_80000008\tduplicate\tevidence\n')
            aliases = symbol_aliases(td)
        self.assertEqual(aliases['advance'], 'func_80000000')
        self.assertNotIn('duplicate', aliases)

    def test_renamed_section_requires_unique_exact_bytes(self):
        built, debug = Path('built.o'), Path('debug.o')
        names = {built: {'.text.old', '.text.duplicate1', '.text.duplicate2'},
                 debug: {'.text.new', '.text.duplicate_a', '.text.duplicate_b'}}
        content = {'.text.old': b'unique', '.text.new': b'unique',
                   '.text.duplicate1': b'same', '.text.duplicate2': b'same',
                   '.text.duplicate_a': b'same', '.text.duplicate_b': b'same'}
        with patch('access_census.sections', side_effect=lambda path, root: names[path]), \
                patch('access_census.section_bytes', side_effect=lambda path, sec, root, tmp: content[sec]):
            self.assertEqual(exact_debug_sections(built, debug, Path('.'), Path('.')),
                             {'.text.new'})

    def test_single_assignment_local_parameter_alias_and_rebase(self):
        f = {'local_writes': {'v:copy': [('p:f:0', 8)], 'v:rebased': [('v:copy', 4)]},
             'escaped_locals': []}
        self.assertEqual(parameter_aliases(f), {'v:copy': (0, 8), 'v:rebased': (0, 12)})
        dis = '''Disassembly of section .text.func_12345678:
   0: 00808021 move s0,a0
/tmp/src/a.c:9
   4: 8e020010 lw v0,16(s0)
'''
        site = self.site(9, 4, 4, '?')
        site['node'] = 'v:rebased'
        rows = join([site], instructions(dis)['.text.func_12345678'],
                    stable_parameter_registers(dis)['.text.func_12345678'], aliases=parameter_aliases(f))
        self.assertEqual(rows[0]['opcode'], 'lw')
        f['local_writes']['v:copy'].append(None)
        self.assertNotIn('v:rebased', parameter_aliases(f))
        f['local_writes']['v:copy'].pop()
        f['escaped_locals'] = ['v:copy']
        self.assertNotIn('v:rebased', parameter_aliases(f))

    def test_proven_move_rebase_stack_reload_and_header_macro(self):
        dis = '''Disassembly of section .text.f:
   0: 00804021 move t0,a0
   4: 25090008 addiu t1,t0,8
/tmp/src/a.c:9
   8: 91220004 lbu v0,4(t1)
   c: afa40010 sw a0,16(sp)
  10: 8fa80010 lw t0,16(sp)
/tmp/src/a.c:10
  14: 95020002 lhu v0,2(t0)
  18: 2488ffe0 addiu t0,a0,-32
/tmp/src/a.c:11
  1c: 9502001e lhu v0,30(t0)
'''
        ops = instructions(dis)['.text.f']
        f = {'sites': []}
        bases = proven_register_bases(dis, '.text.f', f, {}, ops)
        sites = [self.site(9, 12, 1, 'u'), self.site(10, 2, 2, 'u'),
                 self.site(11, -2, 2, 'u')]
        sites[2]['spell'] = 'macro'
        rows = join(sites, ops, stable_parameter_registers(dis)['.text.f'],
                    proven_bases=bases)
        self.assertEqual([r['opcode'] for r in rows], ['lbu', 'lhu', 'lhu'])

    def test_pointer_chain_requires_unique_source_load(self):
        dis = '''Disassembly of section .text.f:
/tmp/src/a.c:4
   0: 8c880004 lw t0,4(a0)
/tmp/src/a.c:5
   4: 91020002 lbu v0,2(t0)
'''
        pointer = self.site(4, 4, 4, 'p')
        child = self.site(5, 2, 1, 'u')
        child['node'] = ('F', 'p:f:0', 4)
        ops = instructions(dis)['.text.f']
        f = {'sites': [pointer, child]}
        bases = proven_register_bases(dis, '.text.f', f, {}, ops)
        rows = join(f['sites'], ops, proven_bases=bases)
        self.assertEqual([r['opcode'] for r in rows], ['lw', 'lbu'])
        f['sites'].append(dict(pointer))
        bases = proven_register_bases(dis, '.text.f', f, {}, ops)
        self.assertEqual(join([child], ops, proven_bases=bases)[0]['status'], 'unmapped')

    def test_global_pointer_load_requires_symbol_relocation(self):
        dis = '''Disassembly of section .text.f:
/tmp/src/a.c:5
   0: 8f880000 lw t0,0(gp)
      0: R_MIPS_GPREL16 g_actor
   4: 91020002 lbu v0,2(t0)
'''
        site = self.site(5, 2, 1, 'u')
        site['node'] = ('F', 'g:g_actor', 0)
        ops = instructions(dis)['.text.f']
        bases = proven_register_bases(dis, '.text.f', {'sites': [site]}, {}, ops)
        self.assertEqual(join([site], ops, proven_bases=bases)[0]['opcode'], 'lbu')
        self.assertEqual(join([site], ops, proven_bases=proven_register_bases(
            dis.replace('g_actor', 'other'), '.text.f', {'sites': [site]}, {}, ops))[0]['status'],
            'unmapped')

    def test_direct_global_requires_matching_hi_lo_relocations(self):
        dis = '''Disassembly of section .text.f:
   0: 3c020000 lui v0,0x0
      0: R_MIPS_HI16 D_80083460
/tmp/src/a.c:5
   4: 9443001e lhu v1,30(v0)
      4: R_MIPS_LO16 D_80083460
'''
        site = self.site(5, 30, 2, 'u')
        site['node'] = 'g:g_dungeon_status'
        ops = instructions(dis)['.text.f']
        aliases = {'D_80083460': 'g_dungeon_status'}
        bases = proven_register_bases(dis, '.text.f', {'sites': [site]}, {}, ops,
                                      global_symbols=aliases)
        self.assertEqual(join([site], ops, proven_bases=bases)[0]['opcode'], 'lhu')
        literal = dict(site, node='g:D_80083460')
        bases = proven_register_bases(dis, '.text.f', {'sites': [literal]}, {}, ops)
        self.assertEqual(join([literal], ops, proven_bases=bases)[0]['opcode'], 'lhu')
        for changed in (dis.replace('R_MIPS_HI16 D_80083460', 'R_MIPS_HI16 D_80083461'),
                        dis.replace('R_MIPS_LO16 D_80083460', 'R_MIPS_LO16 D_80083461'),
                        dis.replace('R_MIPS_LO16 D_80083460', 'R_MIPS_LO16 D_80083460+0x2')):
            bases = proven_register_bases(changed, '.text.f', {'sites': [site]}, {}, ops,
                                          global_symbols=aliases)
            self.assertEqual(join([site], ops, proven_bases=bases)[0]['status'], 'unmapped')

    def test_global_address_from_hi_lo_addiu(self):
        dis = '''Disassembly of section .text.f:
   0: 3c020000 lui v0,0x0
      0: R_MIPS_HI16 D_80083460
   4: 24480000 addiu t0,v0,0
      4: R_MIPS_LO16 D_80083460
/tmp/src/a.c:5
   8: 91020002 lbu v0,2(t0)
'''
        site = self.site(5, 2, 1, 'u')
        site['node'] = 'g:g_dungeon_status'
        ops = instructions(dis)['.text.f']
        bases = proven_register_bases(dis, '.text.f', {'sites': [site]}, {}, ops,
                                      global_symbols={'D_80083460': 'g_dungeon_status'})
        self.assertEqual(join([site], ops, proven_bases=bases)[0]['opcode'], 'lbu')

    ADDEND = '''Disassembly of section .text.f:
   0: 3c020000 lui v0,0x0
      0: R_MIPS_HI16 D_80083460
   4: 24480020 addiu t0,v0,32
      4: R_MIPS_LO16 D_80083460
/tmp/src/a.c:5
   8: 91020002 lbu v0,2(t0)
'''

    def addend_join(self, dis, offset):
        site = dict(self.site(5, offset, 1, 'u'), node='g:g_dungeon_status')
        ops = instructions(dis)['.text.f']
        bases = proven_register_bases(dis, '.text.f', {'sites': [site]}, {}, ops,
                                      global_symbols={'D_80083460': 'g_dungeon_status'})
        return bases, join([site], ops, proven_bases=bases)[0]

    def test_hi_lo_addiu_immediate_is_the_lo16_addend(self):
        # objdump prints no '+addend' for these REL objects: the LO16 addend
        # is the addiu immediate, so lbu 2(t0) reads global+34, not global+2.
        bases, row = self.addend_join(self.ADDEND, 34)
        self.assertEqual(bases[8], (('global', 'g_dungeon_status'), 32))
        self.assertEqual((row['status'], row['opcode']), ('mapped', 'lbu'))
        self.assertEqual(self.addend_join(self.ADDEND, 2)[1]['status'], 'unmapped')
        same = self.ADDEND.replace('addiu t0,v0,32', 'addiu v0,v0,32').replace('lbu v0,2(t0)', 'lbu v0,2(v0)')
        self.assertEqual(self.addend_join(same, 34)[0][8], (('global', 'g_dungeon_status'), 32))

    def test_hi_lo_addiu_held_on_high_half_or_ambiguous_pairing(self):
        high = self.ADDEND.replace('3c020000 lui v0,0x0', '3c020001 lui v0,0x1')
        bases, row = self.addend_join(high, 34)
        self.assertNotIn(8, bases)
        self.assertEqual(row['status'], 'unmapped')
        self.assertEqual(self.addend_join(high, 0x10022)[1]['status'], 'unmapped')
        twice = self.ADDEND.replace('      4: R_MIPS_LO16 D_80083460\n',
                                    '      4: R_MIPS_LO16 D_80083460\n      4: R_MIPS_LO16 D_80083460\n')
        bases, row = self.addend_join(twice, 34)
        self.assertNotIn(8, bases)
        self.assertEqual(row['status'], 'unmapped')
        direct = '''Disassembly of section .text.f:
   0: 3c020001 lui v0,0x1
      0: R_MIPS_HI16 D_80083460
/tmp/src/a.c:5
   4: 90430022 lbu v1,34(v0)
      4: R_MIPS_LO16 D_80083460
'''
        self.assertEqual(self.addend_join(direct, 34)[1]['status'], 'unmapped')
        self.assertEqual(self.addend_join(direct.replace('lui v0,0x1', 'lui v0,0x0'), 34)[1]['status'],
                         'mapped')

    def test_global_half_address_does_not_cross_branch_or_overwrite(self):
        site = self.site(5, 2, 2, 'u')
        site['node'] = 'g:g_dungeon_status'
        prefix = '''Disassembly of section .text.f:
   0: 3c020000 lui v0,0x0
      0: R_MIPS_HI16 D_80083460
'''
        suffix = '''/tmp/src/a.c:5
   c: 94420002 lhu v0,2(v0)
      c: R_MIPS_LO16 D_80083460
'''
        for middle in ('   4: 10000001 b c <f+0xc>\n   8: 00000000 nop\n',
                       '   4: 00801021 move v0,a0\n   8: 00000000 nop\n'):
            dis = prefix + middle + suffix
            ops = instructions(dis)['.text.f']
            bases = proven_register_bases(dis, '.text.f', {'sites': [site]}, {}, ops,
                                          global_symbols={'D_80083460': 'g_dungeon_status'})
            self.assertEqual(join([site], ops, proven_bases=bases)[0]['status'], 'unmapped')

    def test_same_line_claim_precedes_global_cross_line_fallback(self):
        local = self.site(5, 2, 2, 'u')
        global_site = dict(self.site(10, 2, 2, 'u'), node='g:g_dungeon_status',
                           base='g_dungeon_status')
        op = dict(pc=4, line=5, offset=2, width=2, rw='r', reg='s0',
                  opcode='lhu', sign='u')
        rows = join([local, global_site], [op], {'s0': (0, float('inf'))},
                    proven_bases={4: (('global', 'g_dungeon_status'), 0)})
        self.assertEqual([r['status'] for r in rows], ['mapped', 'unmapped'])

    def test_stack_overwrite_and_branch_target_revoke_proof(self):
        dis = '''Disassembly of section .text.f:
   0: afa40010 sw a0,16(sp)
   4: afa00010 sw zero,16(sp)
   8: 8fa80010 lw t0,16(sp)
/tmp/src/a.c:5
   c: 91020002 lbu v0,2(t0)
'''
        site = self.site(5, 2, 1, 'u')
        ops = instructions(dis)['.text.f']
        bases = proven_register_bases(dis, '.text.f', {'sites': [site]}, {}, ops)
        self.assertEqual(join([site], ops, proven_bases=bases)[0]['status'], 'unmapped')
        branch = '''Disassembly of section .text.f:
   0: 00804021 move t0,a0
   4: 10000001 b 10 <f+0x10>
   8: 00000000 nop
/tmp/src/a.c:5
  10: 91020002 lbu v0,2(t0)
'''
        ops = instructions(branch)['.text.f']
        bases = proven_register_bases(branch, '.text.f', {'sites': [site]}, {}, ops)
        self.assertEqual(join([site], ops, proven_bases=bases)[0]['status'], 'unmapped')

    def test_raw_stack_local_object_offset(self):
        raw = '''\t.ent\tf
\t.frame\t$sp,32,$31
\t.def\tpoint;\t.val\t-16;\t.scl\t1;\t.type\t0x8;\t.endef
\t.end\tf
'''
        site = self.site(5, 2, 2, 's')
        site['node'] = 'o:src/a.c:f:point:1'
        func = {'sites': [site]}
        stacks = stack_offsets_for_function(func, raw_stack_locals(raw)['f'])
        self.assertEqual(stacks, {site['node']: -16})
        dis = '''Disassembly of section .text.f:
   0: 27bdffe0 addiu sp,sp,-32
/tmp/src/a.c:5
   4: 87a20012 lh v0,18(sp)
'''
        ops = instructions(dis)['.text.f']
        bases = proven_register_bases(dis, '.text.f', func, {}, ops, stacks)
        self.assertEqual(join([site], ops, proven_bases=bases, stack_locals=stacks)[0]['opcode'], 'lh')
        restored = dis.replace('/tmp/src/a.c:5', '   2: 27bd0020 addiu sp,sp,32\n/tmp/src/a.c:5')
        ops = instructions(restored)['.text.f']
        bases = proven_register_bases(restored, '.text.f', func, {}, ops, stacks)
        self.assertEqual(join([site], ops, proven_bases=bases, stack_locals=stacks)[0]['status'],
                         'unmapped')

    def test_fifth_callback_argument_loaded_from_o32_stack_slot(self):
        site = self.site(5, 2, 1, 'u')
        site['node'] = 'p:f:4'
        dis = '''Disassembly of section .text.f:
   0: 27bdffe0 addiu sp,sp,-32
   4: 8fa80030 lw t0,48(sp)
/tmp/src/a.c:5
   8: 91020002 lbu v0,2(t0)
'''
        ops = instructions(dis)['.text.f']
        bases = proven_register_bases(dis, '.text.f', {'sites': [site]}, {}, ops)
        self.assertEqual(join([site], ops, proven_bases=bases)[0]['opcode'], 'lbu')

    def test_width_consistency_uses_record_layout(self):
        db = sqlite3.connect(':memory:')
        db.execute('CREATE TABLE record_member (record TEXT, name TEXT, off INTEGER, size INTEGER, depth INTEGER)')
        db.execute('INSERT INTO record_member VALUES (?,?,?,?,?)', ('ActorRecord', 'field', 4, 2, 0))
        row = join([self.site(5, 4, 2, 'u')], [dict(line=5, offset=4, width=2, rw='r',
                    reg='a0', pc=0, opcode='lhu', sign='u')], {'a0': (0, float('inf'))})[0]
        self.assertEqual(width_consistency([row], db), (1, []))
        db.execute('UPDATE record_member SET size=1')
        checked, bad = width_consistency([row], db)
        self.assertEqual((checked, len(bad)), (1, 1))
        db.execute('UPDATE record_member SET size=NULL')
        self.assertEqual(width_consistency([row], db), (0, []))

    def test_source_extraction_records_unknown_local_reassignment(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'include').mkdir()
            (root / 'src').mkdir()
            (root / 'src/a.c').write_text(
                'struct Box { char x; }; void f(struct Box *p) {'
                'struct Box *q=p; q->x=1; q=0; q->x=2; }')
            facts = F.extract_tu((td, 'src/a.c'))
        self.assertIsNone(facts['error'])
        local = next(node for node in facts['functions'][0]['local_writes'] if ':q:' in node)
        self.assertEqual(len(facts['functions'][0]['local_writes'][local]), 2)
        self.assertNotIn(local, parameter_aliases(facts['functions'][0]))

    def test_four_byte_local_aggregate_keeps_address_and_register_member(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'include').mkdir()
            (root / 'src').mkdir()
            (root / 'src/a.c').write_text(
                'void f(char *p) { union { char *v; } state = {p}; state.v[2] = 1; }')
            facts = F.extract_tu((td, 'src/a.c'))
        self.assertIsNone(facts['error'])
        func = facts['functions'][0]
        pointer = next(s for s in func['sites'] if s['field'] == 'v')
        self.assertTrue(pointer['node'].startswith('o:'))
        raw = {'state': ['v1']}
        locations = local_registers_for_function(func, raw)
        self.assertEqual(locations[('F', pointer['node'], 0)], 'v1')

    def test_compiler_register_local_requires_same_debug_line(self):
        raw = '''\t.ent\tf
\t.def\tscratch;\t.val\t17;\t.scl\t4;\t.type\t0x18;\t.endef
\t.end\tf
'''
        registers = raw_local_registers(raw)
        local = 'v:src/a.c:f:scratch:1'
        site = self.site(9, 12, 4, '?')
        site['node'] = local
        f = {'sites': [site]}
        locations = local_registers_for_function(f, registers['f'])
        self.assertEqual(locations, {local: 's1'})
        dis = '''Disassembly of section .text.func_12345678:
/tmp/src/a.c:9
   0: 8e22000c lw v0,12(s1)
'''
        opcodes = instructions(dis)['.text.func_12345678']
        self.assertEqual(join([site], opcodes, local_registers=locations)[0]['opcode'], 'lw')
        site['line'] = 8
        self.assertEqual(join([site], opcodes, local_registers=locations)[0]['status'], 'unmapped')
        other = dict(site, node='v:src/a.c:f:scratch:2')
        self.assertEqual(local_registers_for_function({'sites': [site, other]}, registers['f']), {})

    def test_direct_consumer_vote_stops_at_overwrite_or_branch(self):
        dis = '''Disassembly of section .text.func_12345678:
/tmp/src/a.c:3
   0: 8c820004 lw v0,4(a0)
   4: 00021043 sra v0,v0,0x1
   8: 8c830008 lw v1,8(a0)
   c: 0062182b sltu v1,v1,v0
  10: 8c84000c lw a0,12(a0)
  14: 24040001 addiu a0,zero,1
  18: 00042042 srl a0,a0,0x1
  1c: 8c850010 lw a1,16(a0)
  20: 10000000 b 24 <target>
  24: 00052843 sra a1,a1,0x1
'''
        rows = instructions(dis)['.text.func_12345678']
        self.assertEqual([(r['consumer'], r['consumer_sign']) for r in rows],
                         [('sra', 's'), ('sltu', 'u'), ('', ''), ('', '')])
        div = '''Disassembly of section .text.func_12345678:
/tmp/src/a.c:4
   0: 8c820004 lw v0,4(a0)
   4: 0043001b divu v0,v1
'''
        self.assertEqual(instructions(div)['.text.func_12345678'][0]['consumer'], 'divu')

    def test_conflicting_header_cast_does_not_identify_body(self):
        f = {'attach': [('p:f:0', 0, 'AddressNamedBody', False),
                        ('p:f:0', 0, 'ObjectNodeHeader', True),
                        ('p:f:1', 0, 'ActorRecord', True)]}
        self.assertEqual(object_types_for_function(f), {'p:f:1': 'ActorRecord'})

    def test_anonymous_member_in_named_record_and_union_alias(self):
        site = {'spell': 'member_view', 'decl': '@include/shared/color.h:4:5', 'field': 'r'}
        self.assertEqual(kind(site, 'SpriteFrameState'), 'named record')
        site['field'] = 'u16'
        self.assertEqual(kind(site, 'ActorRecord'), 'union pun')

    def test_shared_field_majority_suggests_minority_value_cast(self):
        rows = []
        for op, sign in [('lhu', 'u'), ('lhu', 'u'), ('lh', 's')]:
            rows.append(dict(object_type='ActorRecord', member_path='action_timer.' + sign,
                             offset=150, declared_width=2, status='mapped', direction='r',
                             opcode=op, retail_sign=sign, file='src/a.c', line=7))
        row = shared_sign_rows(rows)[0]
        self.assertEqual(row[9:13], ['unsigned', 'u16', '(s16)', 'sample_only'])

    def test_header_vote_requires_declared_header_field_and_normalizes_body_offset(self):
        db = sqlite3.connect(':memory:')
        db.execute('CREATE TABLE record_member (record TEXT, name TEXT, off INTEGER, size INTEGER, depth INTEGER)')
        db.execute('INSERT INTO record_member VALUES (?,?,?,?,?)',
                   ('ObjectNodeHeader', 'flags', 30, 2, 0))
        base = dict(object_type='ObjectNodeHeader', member_path='flags', offset=-2,
                    declared_width=2, status='mapped', direction='r', opcode='lhu',
                    retail_sign='u', file='src/a.c', line=7, base_kind='named record',
                    consumer='sltu', consumer_sign='u')
        body = dict(base, base_type='VariantEffectBody')
        header = dict(base, base_type='ObjectNodeHeader')
        rows = shared_sign_rows([body] * 8 + [header] * 5, db)
        self.assertEqual(len(rows), 1)
        row = rows[0]
        self.assertEqual((row[2], row[7], row[14:]),
                         (30, 5, [5, 1, 0, 5, 'unsigned']))
        self.assertEqual(shared_sign_rows([dict(header, offset=None)], db)[0][7], 0)
        conflict = dict(header, consumer='sra', consumer_sign='s')
        self.assertEqual(shared_sign_rows([conflict] * 5, db)[0][12],
                         'review_consumer_conflict')

    def test_merge_replaces_a_physical_file(self):
        old = [{'file': 'src/a.c', 'opcode': 'lh'}, {'file': 'src/b.c', 'opcode': 'lw'}]
        new = [{'file': 'src/a.c', 'opcode': 'lhu'}]
        self.assertEqual(merge_site_rows(old, new), [old[1], new[0]])
        self.assertEqual(merge_site_rows(old, [], {'src/a.c'}), [old[1]])
        generated = {'file': 'build_slus/src/w_80000000.c', 'physical_tu': 'src/slus/w_80000000_owned.c'}
        self.assertEqual(merge_site_rows([generated], [], {'src/slus/w_80000000_owned.c'}), [])

    def test_missing_recipe_keeps_source_access_unresolved(self):
        db = sqlite3.connect(':memory:')
        db.execute('CREATE TABLE recipe (source TEXT, physical TEXT, output TEXT, args TEXT)')
        func = {'func': 'f', 'sites': [self.site(4, 2, 1, 'u')], 'attach': []}
        with patch('access_census.F.extract_tu', return_value={'error': None, 'functions': [func]}):
            rows, hold = measure(Path('.'), 'src/a.c', db, Path('.'))
        self.assertEqual((len(rows), rows[0]['status']), (1, 'unmapped'))
        self.assertIn('no unique compile recipe', hold)

    def test_two_recipe_placements_have_distinct_site_keys(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'build').mkdir()
            db = sqlite3.connect(root / 'build/codemap.db')
            db.execute('CREATE TABLE recipe (source TEXT, physical TEXT, output TEXT, args TEXT)')
            db.execute('CREATE TABLE record_member (record TEXT, name TEXT, off INTEGER, size INTEGER, depth INTEGER)')
            for output in ('build/a.o', 'build/b.o'):
                db.execute('INSERT INTO recipe VALUES (?,?,?,?)',
                           ('src/a.c', 'src/a.c', output, '["2.7.2","-G0",""]'))
            db.commit()
            self.assertEqual(len(recipes(db, 'src/a.c')), 2)
            row = join([self.site(4, 2, 1, 'u')], [])[0]
            with patch('access_census.measure', return_value=([row], None)), redirect_stdout(io.StringIO()):
                self.assertEqual(main(['--root', td, '--out', str(root / 'out'),
                                       '--source', 'src/a.c']), 0)
            with (root / 'out/access_sites.tsv').open() as stream:
                rows = list(__import__('csv').DictReader(stream, delimiter='\t'))
            self.assertEqual([r['recipe_output'] for r in rows], ['build/a.o', 'build/b.o'])


if __name__ == '__main__':
    unittest.main()
