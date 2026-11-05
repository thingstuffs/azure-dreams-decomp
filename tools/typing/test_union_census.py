import tempfile
from pathlib import Path
import json
import subprocess
import sys
import unittest

from tools.typing.union_census import census, main


class UnionCensusTests(unittest.TestCase):
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
            rows[0]['status'] = 'retire'
            rows[0]['evidence'] = 'Wording does not determine retirement.'
            (root / 'ledger' / 'unions.jsonl').write_text(json.dumps(rows[0]) + '\n')
            (root / 'tools' / 'lint' / 'union_baseline.json').write_text(
                json.dumps({'schema': 1, 'count': 1, 'ids': ['src/one.c::Other.other']}) + '\n')
            check_result = subprocess.run(cmd, capture_output=True, text=True)
            self.assertNotEqual(check_result.returncode, 0)
            self.assertIn('retired union reintroduced', check_result.stderr)


if __name__ == '__main__':
    unittest.main()
