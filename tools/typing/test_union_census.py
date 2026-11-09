import tempfile
from pathlib import Path
import json
import subprocess
import sys
import unittest

from tools.typing.union_census import (census, main, add_access_loads,
                                       load_check, load_votes, retain_retired_loads)


class UnionCensusTests(unittest.TestCase):
    def test_loads_count_retail_opcodes_and_report_majority(self):
        row = dict(id='include/e.h::Effect.ticks', file='include/e.h', line=7,
                   owner='Effect', path='ticks', status='retired',
                   members=[{'name': 's', 'type': 's16'}, {'name': 'u', 'type': 'u16'}])
        accesses = [dict(base_type='include/e.h:Effect', member_path='ticks',
                         file='src/e.c', function='f', line=str(i), pc=str(4 * i),
                         opcode=op, status='mapped', direction='r')
                    for i, op in enumerate(('lh', 'lh', 'lh', 'lh', 'lhu'), 1)]
        accesses.append(dict(accesses[0], line='8', pc='', opcode='', status='unmapped',
                             declared_width='2', declared_sign='s'))
        accesses.append(dict(accesses[0], line='9', pc='', opcode='', status='unmapped',
                             direction='w', declared_width='2', declared_sign='s'))
        add_access_loads([row], accesses)
        self.assertEqual(row['loads']['s']['lh'], 4)
        self.assertEqual(row['loads']['u']['lhu'], 1)
        self.assertEqual(row['loads']['s']['unmapped'], 1)
        self.assertEqual(load_check([row], {row['id']: 'u16'}),
                         [(row['id'], 'disagree', 'u16', 4, 1, 1)])
        self.assertEqual(load_check([row], {row['id']: 's16'}), [])

    def test_byte_view_loads_do_not_vote_on_a_halfword(self):
        row = dict(id='include/e.h::R.unk_A8', file='include/e.h', line=3, owner='R', path='unk_A8',
                   status='retired', members=[{'name': 'byte', 'type': 'u8'}, {'name': 'half', 'type': 'u16'}])
        base = dict(base_type='include/e.h:R', file='src/e.c', function='f', status='mapped', direction='r')
        accesses = [dict(base, member_path='unk_A8.byte', line=str(i), pc=str(i), opcode='lbu') for i in range(11)]
        accesses += [dict(base, member_path='unk_A8.half', line=str(20 + i), pc=str(20 + i), opcode='lh') for i in range(5)]
        accesses += [dict(base, member_path='unk_A8.half', line='40', pc='40', opcode='lhu')]
        add_access_loads([row], accesses)
        self.assertEqual(load_votes(row, 'u16')[:2], (5, 1))
        self.assertEqual(load_votes(row, 'u8')[:2], (0, 11))
        self.assertEqual(load_votes(row, '')[:2], (5, 12))
        self.assertEqual(load_check([row], {row['id']: 'u16'}), [(row['id'], 'disagree', 'u16', 5, 1, 0)])

    def test_sign_neutral_unsigned_loads_mark_the_count_biased(self):
        row = dict(id='include/e.h::R.timer', file='include/e.h', line=3, owner='R', path='timer',
                   status='retired', members=[{'name': 'half', 'type': 'u16'}])
        base = dict(base_type='include/e.h:R', member_path='timer.half', file='src/e.c', function='f',
                    status='mapped', direction='r')
        accesses = [dict(base, line=str(i), pc=str(i), opcode='lhu', consumer_sign='') for i in range(5)]
        accesses.append(dict(base, line='9', pc='9', opcode='lh', consumer_sign=''))
        accesses.append(dict(base, line='10', pc='10', opcode='lhu', consumer_sign='u'))
        accesses.append(dict(base, line='11', pc='11', opcode='lhu', consumer_sign='', compound='0'))
        add_access_loads([row], accesses)
        self.assertEqual(load_votes(row, 'u16'), (1, 7, 6))
        # 7 lhu against 1 lh is a raw unsigned majority, but only one unsigned load has an unsigned consumer
        self.assertEqual(load_check([row], {row['id']: 'u16'}), [(row['id'], 'biased', 'u16', 1, 7, 0)])
        # an unsigned-only consumer on most of the loads is real evidence
        for access in accesses[:5]:
            access['consumer_sign'] = 'u'
        row2 = dict(row, loads=None)
        row2.pop('neutral_loads')
        add_access_loads([row2], accesses)
        self.assertEqual(load_check([row2], {row2['id']: 'u16'}), [])
        # rmw joins stay neutral even next to an unsigned consumer
        rmw = [dict(a, compound='1', consumer_sign='u') for a in accesses]
        row3 = dict(row, loads=None)
        row3.pop('neutral_loads', None)
        add_access_loads([row3], rmw)
        self.assertEqual(load_votes(row3, 'u16')[2], 7)

    def test_live_union_uses_declaration_identity(self):
        row = dict(id='include/e.h::Effect.ticks', file='include/e.h', line=7,
                   owner='Effect', path='ticks', status='unproven',
                   members=[{'name': 's', 'type': 's16'}, {'name': 'u', 'type': 'u16'}])
        access = dict(base_type='@include/e.h:7:12', member_path='ticks.s',
                      file='src/e.c', function='f', line='9', pc='4',
                      opcode='lh', status='mapped', direction='r')
        add_access_loads([row], [access])
        self.assertEqual(row['loads']['s']['lh'], 1)
        self.assertEqual(row['loads']['u']['lh'], 0)
        self.assertEqual(load_check([row], {}), [(row['id'], 'insufficient', '', 1, 0, 0)])

    def test_named_typedef_union_joins_typed_view_to_exact_owner(self):
        row = dict(id='src/e.c::Half.Half', file='src/e.c', line=4,
                   owner='Half', path='Half', status='unproven',
                   count_basis='member_suffix_upper_bound',
                   members=[{'name': 'bits', 'type': 'u16'},
                            {'name': 'signed_value', 'type': 's16'}])
        access = dict(base_type='src/e.c:Half', base_kind='view',
                      base_expression='object->extent',
                      member_path='object->extent.signed_value',
                      file='src/e.c', function='f', line='14', pc='8',
                      opcode='lh', status='mapped', direction='r')
        wrong_type = dict(access, base_type='src/e.c:OtherHalf', pc='12')
        nested = dict(access, member_path='object->extent.parts.signed_value', pc='16')
        add_access_loads([row], [access, wrong_type, nested])
        self.assertEqual(row['loads']['signed_value']['lh'], 1)
        self.assertEqual(row['loads']['bits']['lh'], 0)

    def test_retired_word_load_uses_declared_member_for_bucket_only(self):
        row = dict(id='include/e.h::Effect.word', file='include/e.h', line=4,
                   owner='Effect', path='word', status='retired',
                   members=[{'name': 'signed', 'type': 's32'},
                            {'name': 'unsigned', 'type': 'u32'}])
        access = dict(base_type='include/e.h:Effect', member_path='word',
                      file='src/e.c', function='f', line='8', pc='4', opcode='lw',
                      status='mapped', direction='r', declared_sign='s')
        add_access_loads([row], [access])
        self.assertEqual(row['loads']['signed']['lw'], 1)
        self.assertEqual(row['loads']['unsigned']['lw'], 0)
        self.assertEqual(load_check([row], {row['id']: 's32'}),
                         [(row['id'], 'insufficient', 's32', 0, 0, 0)])

    def test_retired_alias_keeps_fuller_byte_proven_loads(self):
        row = dict(id='include/e.h::Effect.stage', file='include/e.h', line=7,
                   owner='Effect', path='stage', status='retired',
                   members=[{'name': 's', 'type': 's16'},
                            {'name': 'u', 'type': 'u16'},
                            {'name': 'p', 'type': 'u16'}])
        old = dict(row)
        old['loads'] = {name: dict.fromkeys(
            ('lb', 'lbu', 'lh', 'lhu', 'lw', 'sb', 'sh', 'sw', 'unmapped'), 0)
            for name in ('s', 'u', 'p')}
        old['loads']['s']['lh'] = 3
        old['loads']['u']['lhu'] = 5
        old['loads']['p']['lhu'] = 6
        access = dict(base_type='include/e.h:Effect', member_path='stage',
                      file='src/e.c', function='f', line='9', pc='4',
                      opcode='lhu', status='mapped', direction='r')
        add_access_loads([row], [access])
        self.assertEqual(sum(v['lhu'] for v in row['loads'].values()), 0)
        retain_retired_loads([row], {row['id']: old}, set())
        self.assertEqual(row['loads'], old['loads'])
        add_access_loads([row], [access])
        retain_retired_loads([row], {row['id']: old}, {row['id']})
        self.assertEqual(sum(v['lhu'] for v in row['loads'].values()), 0)

    def test_regeneration_keeps_retired_alias_loads(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'include').mkdir()
            (root / 'src').mkdir()
            header = root / 'include' / 'e.h'
            header.write_text('typedef unsigned short u16;\ntypedef struct Effect { u16 stage; } Effect;\n')
            row = dict(id='include/e.h::Effect.stage', file='include/e.h', line=2,
                       owner='Effect', path='stage', status='retired',
                       members=[{'name': 's', 'type': 's16'},
                                {'name': 'u', 'type': 'u16'},
                                {'name': 'p', 'type': 'u16'}])
            row['loads'] = {name: dict.fromkeys(
                ('lb', 'lbu', 'lh', 'lhu', 'lw', 'sb', 'sh', 'sw', 'unmapped'), 0)
                for name in ('s', 'u', 'p')}
            row['loads']['s']['lh'] = 3
            row['loads']['u']['lhu'] = 5
            row['loads']['p']['lhu'] = 6
            ledger = root / 'unions.jsonl'
            ledger.write_text(json.dumps(row) + '\n')
            sites = root / 'access_sites.tsv'
            sites.write_text('base_type\tmember_path\tfile\tfunction\tline\tpc\topcode\tstatus\tdirection\n'
                             'include/e.h:Effect\tstage\tsrc/e.c\tf\t9\t4\tlhu\tmapped\tr\n')
            main(['--root', str(root), '--out', str(ledger), '--access-sites', str(sites)])
            self.assertEqual(json.loads(ledger.read_text())['loads'], row['loads'])

    def test_regeneration_without_access_sites_keeps_loads(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'src').mkdir()
            (root / 'include').mkdir()
            (root / 'src/use.c').write_text('union { short s; unsigned short u; } field;\n')
            row, = census(root)
            row['loads'] = {name: dict.fromkeys(
                ('lb', 'lbu', 'lh', 'lhu', 'lw', 'sb', 'sh', 'sw', 'unmapped'), 0)
                for name in ('s', 'u')}
            row['loads']['s']['lh'] = 4
            row['loads']['u']['lhu'] = 1
            ledger = root / 'unions.jsonl'
            ledger.write_text(json.dumps(row) + '\n')
            main(['--root', str(root), '--out', str(ledger)])
            self.assertEqual(json.loads(ledger.read_text())['loads'], row['loads'])

    def test_regeneration_preserves_byte_hold(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'src').mkdir()
            (root / 'include').mkdir()
            (root / 'src/use.c').write_text('union { short s; unsigned short u; } field;\n')
            row, = census(root)
            row.update(status='unproven', hold_reason='bytes',
                       evidence='src/use.c: first byte difference at +0x12')
            ledger = root / 'unions.jsonl'
            ledger.write_text(json.dumps(row) + '\n')
            main(['--root', str(root), '--out', str(ledger)])
            updated = json.loads(ledger.read_text())
            self.assertEqual(updated['hold_reason'], 'bytes')
            self.assertEqual(updated['evidence'], row['evidence'])

    def test_local_union_variable_counts_its_root_name(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'src').mkdir()
            (root / 'include').mkdir()
            (root / 'src' / 'use.c').write_text('''
void use(void) {
  union { long long both; struct { int hi; int lo; } word; } wide_product;
  wide_product.both = 1;
  (void)wide_product.word.hi;
}
''')
            row, = census(root)
            self.assertEqual(row['uses']['both']['src'], 1)
            self.assertEqual(row['uses']['word']['src'], 1)

    def test_typedef_union_counts_members_through_instance_fields(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'src').mkdir()
            (root / 'include').mkdir()
            (root / 'src' / 'use.c').write_text('''
typedef union Half { unsigned short bits; short value; } Half;
typedef struct Box { Half whole; } Box;
void use(Box *box) { box->whole.bits = 1; box->whole.value = 2; }
''')
            row, = census(root)
            self.assertEqual(row['count_basis'], 'member_suffix_upper_bound')
            self.assertEqual(row['uses']['bits']['src'], 1)
            self.assertEqual(row['uses']['value']['src'], 1)

    def test_nested_typedef_and_anonymous_members(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'src').mkdir()
            (root / 'include').mkdir()
            (root / 'include' / 'sample.h').write_text('''
typedef union Word { int value; unsigned char bytes[4]; } Word;
typedef struct Record {
  union { short s; unsigned short u; } field;
  struct { union { int a; void *p; } slot; } inner;
} Record;
''')
            (root / 'src' / 'use.c').write_text('''
void use(Record *r) { r->field.s = 1; r->inner.slot.p = 0; }
''')
            rows = census(root)
            self.assertEqual(len(rows), 3)
            field = next(r for r in rows if r['path'] == 'field')
            self.assertEqual(field['owner'], 'Record')
            self.assertEqual(field['kind'], 'sign_pun')
            self.assertEqual(field['uses']['s']['src'], 1)
            self.assertEqual(field['uses']['u']['src'], 0)
            word = next(r for r in rows if r['id'].endswith('Word.Word'))
            self.assertEqual([m['name'] for m in word['members']], ['value', 'bytes'])

    def test_check_rejects_missing_row_and_growth(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'src').mkdir()
            (root / 'include').mkdir()
            (root / 'ledger').mkdir()
            (root / 'tools' / 'lint').mkdir(parents=True)
            source = root / 'src' / 'one.c'
            source.write_text('typedef union One { int a; short b; } One;\n')
            rows = census(root)
            (root / 'ledger' / 'unions.jsonl').write_text(json.dumps(rows[0]) + '\n')
            (root / 'tools' / 'lint' / 'union_baseline.json').write_text(
                json.dumps({'schema': 1, 'count': 1, 'ids': [rows[0]['id']]}) + '\n')
            check = Path(__file__).resolve().parents[1] / 'lint' / 'debt_check.py'
            cmd = [sys.executable, str(check), '--unions', '--root', str(root)]
            self.assertEqual(subprocess.run(cmd, capture_output=True).returncode, 0)
            (root / 'ledger' / 'unions.jsonl').write_text('')
            self.assertNotEqual(subprocess.run(cmd, capture_output=True).returncode, 0)
            (root / 'ledger' / 'unions.jsonl').write_text(json.dumps(rows[0]) + '\n')
            source.write_text(source.read_text() + 'union { int x; short y; } two;\n')
            self.assertNotEqual(subprocess.run(cmd, capture_output=True).returncode, 0)
            source.write_text('typedef union One { int a; short b; } One;\n')
            rows[0]['status'] = 'retired'
            rows[0]['evidence'] = 'Wording does not determine retirement.'
            (root / 'ledger' / 'unions.jsonl').write_text(json.dumps(rows[0]) + '\n')
            (root / 'tools' / 'lint' / 'union_baseline.json').write_text(
                json.dumps({'schema': 1, 'count': 1, 'ids': ['src/one.c::Other.other']}) + '\n')
            check_result = subprocess.run(cmd, capture_output=True, text=True)
            self.assertNotEqual(check_result.returncode, 0)
            self.assertIn('retired union reintroduced', check_result.stderr)


if __name__ == '__main__':
    unittest.main()
