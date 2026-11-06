import unittest
import tempfile
import sqlite3
import io
from contextlib import redirect_stdout
from pathlib import Path
from unittest.mock import patch

from access_census import instructions, join, stable_parameter_registers, summarize, symbol_aliases, kind, shared_sign_rows, merge_site_rows, measure, exact_debug_sections, parameter_aliases, object_types_for_function, raw_local_registers, local_registers_for_function, recipes, main
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
