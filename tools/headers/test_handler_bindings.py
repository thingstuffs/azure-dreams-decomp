"""A known callback entry does not imply a safe canonical C spelling."""
from pathlib import Path
import tempfile
import unittest
from check_handler_bindings import BindingIndex


class BindingTests(unittest.TestCase):
    def index(self, *, names=None, root=Path('.')):
        home = dict(image='town/home', vma=0x80001000, size=0x100, symbols={})
        copy = dict(image='town/copy', vma=0x80002000, size=0x100, symbols={})
        caller = dict(row='caller', home='caller', tu='src/town/home.c', image='town/home', vma=0x80001000)
        copied = dict(row='copy', home='caller', tu='src/town/copy.c', image='town/copy', vma=0x80002000)
        target = dict(row='target', home='target', tu='src/town/target.c', image='town/home', vma=0x80001020)
        placed = dict(row='placed', home='target', tu='src/town/target.c', image='town/copy', vma=0x80002020)
        rows = {entry['row']: entry for entry in (caller, copied, target, placed)}
        for entry in rows.values():
            entry['bindings'] = {}
        local = {'town/copy': {0x80001020: [('town/home', 0x80002020)]}}
        tables = ({'town/home': home, 'town/copy': copy}, {}, rows, local)
        return BindingIndex(root, tables=tables, names=names, resident={})

    def test_data_and_function_names_with_equal_literals(self):
        index = self.index(names={'address': 'D_80001020', 'handler': 'func_80001020'})
        self.assertEqual(index.check('src/town/home.c', 'address', 'handler')['status'], 'SAME_BINDING')

    def test_home_caller_cannot_substitute_the_targets_home_address(self):
        index = self.index(names={'placed_address': 'D_80002020', 'handler': 'func_80001020'})
        row = index.check('src/town/home.c', 'placed_address', 'handler')
        self.assertEqual(row['status'], 'PLACEMENT_ADDRESS_ALIAS')
        self.assertIn('0x80002020 -> 0x80001020', row['evidence'])

    def test_copy_rebinding_can_make_different_literals_equivalent(self):
        index = self.index(names={'placed_address': 'D_80002020', 'handler': 'func_80001020'})
        self.assertEqual(index.check('src/town/copy.c', 'placed_address', 'handler')['status'], 'SAME_BINDING')

    def test_unknown_identifier_does_not_guess_an_address(self):
        row = self.index(names={}).check('src/town/home.c', 'D_80001020', 'unknown')
        self.assertEqual(row['status'], 'UNKNOWN_CANONICAL_ADDRESS')

    def test_duplicate_readable_name_uses_ccprocs_last_table_row(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            (root / 'config').mkdir()
            (root / 'config/names.tsv').write_text(
                '0x80001020\tfunc_80001020\thandler\n'
                '0x80001040\tfunc_80001040\thandler\n')
            row = self.index(root=root).check('src/town/home.c', 'D_80001040', 'handler')
            self.assertEqual(row['canonical_after'], '0x80001040')
            self.assertEqual(row['status'], 'SAME_BINDING')


if __name__ == '__main__':
    unittest.main()
