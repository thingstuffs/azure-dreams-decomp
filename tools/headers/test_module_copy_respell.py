import importlib.util
from pathlib import Path
import unittest

spec = importlib.util.spec_from_file_location('module_copy_respell', Path(__file__).with_name('module_copy_respell.py'))
tool = importlib.util.module_from_spec(spec)
spec.loader.exec_module(tool)


class ImportInventoryTests(unittest.TestCase):
    def test_calls_are_not_mistaken_for_local_prototypes(self):
        self.assertFalse(tool.local_prototype('void caller(void) { old_call(); }\n', 'old_call'))
        self.assertFalse(tool.local_prototype('void caller(void) { extern void old_call(void); old_call(); }\n', 'old_call'))
        self.assertTrue(tool.local_prototype('extern void old_call(void);\nvoid caller(void) { old_call(); }\n', 'old_call'))

    def setUp(self):
        self.module = dict(members=[dict(function='func_80001100')], imports=[
            dict(symbol='func_80002200', kind='function', vma=0x80002200, basis='original'),
            dict(symbol='D_80003300', kind='data', vma=0x80003300)])
        self.pair = dict(link='func_80004400>func_80002200', new='callee')

    def test_replaces_symbol_and_preserves_address(self):
        entries = tool.revised_imports(self.module, [self.pair], {'func_80004400', 'D_80003300'})
        self.assertEqual(entries[0]['symbol'], 'func_80004400')
        self.assertEqual(entries[0]['vma'], 0x80002200)
        self.assertEqual(entries[1], self.module['imports'][1])

    def test_retains_old_import_for_other_calls(self):
        symbols = {'func_80002200', 'func_80004400', 'D_80003300'}
        entries = tool.revised_imports(self.module, [self.pair], symbols)
        self.assertEqual({entry['symbol'] for entry in entries}, symbols)

    def test_existing_home_bound_elsewhere_is_refused(self):
        self.module['imports'].append(dict(symbol='func_80004400', kind='function', vma=0x80005500))
        with self.assertRaisesRegex(ValueError, 'already bound elsewhere'):
            tool.revised_imports(self.module, [self.pair], {'func_80004400', 'D_80003300'})

    def test_new_unreviewed_import_is_refused(self):
        with self.assertRaisesRegex(ValueError, 'unexpected import'):
            tool.revised_imports(self.module, [self.pair], {'func_80004400', 'func_80009900', 'D_80003300'})

    def test_missing_unrelated_import_is_refused(self):
        with self.assertRaisesRegex(ValueError, 'unexpected import'):
            tool.revised_imports(self.module, [self.pair], {'func_80004400'})

    def test_local_home_symbol_is_refused(self):
        self.module['members'].append(dict(function='func_80004400'))
        with self.assertRaisesRegex(ValueError, 'defined in the module'):
            tool.revised_imports(self.module, [self.pair], {'func_80004400', 'D_80003300'})

    def test_two_targets_cannot_share_one_home_symbol(self):
        self.module['imports'].append(dict(symbol='func_80005500', kind='function', vma=0x80005500))
        pair = dict(link='func_80004400>func_80005500', new='other')
        with self.assertRaisesRegex(ValueError, 'already bound elsewhere'):
            tool.revised_imports(self.module, [self.pair, pair], {'func_80004400', 'D_80003300'})


if __name__ == '__main__':
    unittest.main()
