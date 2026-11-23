"""name_scope_migrate: anchors on (address, symbol), writes column 5 only, survives renames, refuses with reasons."""
import hashlib
import json
import sys
import unittest
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parents[1] / 'tools'))
sys.path.insert(0, str(HERE))
import name_scope as S  # noqa: E402
import name_scope_migrate as M  # noqa: E402
import test_name_scope_oracle as TO  # noqa: E402

L = S.Location


def batch_row(addr, old, new, *scope):
    return dict(addr=addr, old=old, new=new, scope=tuple(scope))


class Migrate(TO.Fixture):
    def run_migrate(self, names, rows, batch='F1'):
        return M.migrate(names, [(batch, rows)], self.oracle())

    def test_writes_column_five_only(self):
        self.add_object('alpha.o', 'func_80016000', 'src/a.c')
        names = '# h\n0x80016000\tfunc_80016000\talpha\tev text\n0x80016100\tfunc_80016100\tother\tev\n'
        new, kept, refusals, counts = self.run_migrate(names, [batch_row(0x80016000, 'func_80016000', 'alpha', L('town', 0x100000))])
        self.assertEqual(new, '# h\n0x80016000\tfunc_80016000\talpha\tev text\ttown:0x100000\n0x80016100\tfunc_80016100\tother\tev\n')
        self.assertEqual(refusals, [])
        self.assertEqual(counts[('F1', 'scoped')], 1)

    def test_a_renamed_row_is_keyed_by_the_oracle_and_reported(self):
        (self.root / 'src/a.c').write_text('void alpha_renamed(void)\n{\n}\n')
        self.add_object('alpha.o', 'func_80016000', 'src/a.c')
        names = '0x80016000\tfunc_80016000\talpha_renamed\tev\n'
        new, kept, refusals, counts = self.run_migrate(names, [batch_row(0x80016000, 'func_80016000', 'alpha', L('town', 0x100000))])
        self.assertEqual(new, '0x80016000\tfunc_80016000\talpha_renamed\tev\ttown:0x100000\n')
        self.assertEqual(refusals, [])
        self.assertEqual((counts[('F1', 'renamed')], kept[0][3]), (1, 'alpha'))

    def test_a_renamed_row_whose_oracle_differs_is_refused_with_the_reason(self):
        (self.root / 'src/a.c').write_text('void alpha_renamed(void)\n{\n}\n')
        self.add_object('alpha.o', 'func_80016000', 'src/a.c')
        names = '0x80016000\tfunc_80016000\talpha_renamed\tev\n'
        new, kept, refusals, counts = self.run_migrate(names, [batch_row(0x80016000, 'func_80016000', 'alpha', L('town', 0x200000))])
        self.assertEqual(new, names)
        self.assertEqual(refusals[0][2], 'renamed_oracle_differs')

    def test_refusals_are_not_forced(self):
        self.add_object('alpha.o', 'func_80016000', 'src/a.c')
        names = ('0x80016000\tfunc_80016000\talpha\tev\n'
                 '0x80016000\tfunc_80016000\talpha\tev\n'                 # the same anchor twice
                 '0x80016200\tfunc_80016200\tghost\tev\n')
        rows = [batch_row(0x80016000, 'func_80016000', 'alpha', L('town', 0x100000)),
                batch_row(0x80016300, 'func_80016300', 'gone', L('town', 0x100000)),
                batch_row(0x80016200, 'func_80016200', 'ghost', L('town', 0x100000))]
        new, kept, refusals, counts = self.run_migrate(names, rows)
        self.assertEqual(new, names)
        self.assertEqual([x[2] for x in refusals], ['ambiguous_anchor', 'anchor_gone', 'oracle_refused:no_current_object'])

    def test_an_existing_scope_is_kept_or_conflicts_and_collisions_refuse_every_claimant(self):
        self.add_object('alpha.o', 'func_80016000', 'src/a.c')
        row = [batch_row(0x80016000, 'func_80016000', 'alpha', L('town', 0x100000))]
        same = '0x80016000\tfunc_80016000\talpha\tev\ttown:0x100000\n'
        self.assertEqual(self.run_migrate(same, row)[3][('F1', 'already_scoped')], 1)
        other = '0x80016000\tfunc_80016000\talpha\tev\ttown:0x200000\n'
        self.assertEqual(self.run_migrate(other, row)[2][0][2], 'scope_conflict')
        clash = '0x80016000\tfunc_80016000\talpha\tev\n0x80016100\tfunc_80016100\tsquatter\tev\ttown:0x100000\n'
        new, kept, refusals, _ = self.run_migrate(clash, row)
        self.assertEqual((new, refusals[0][2]), (clash, 'location_collision'))

    def test_command_writes_only_with_write_and_lists_refusals(self):
        self.add_object('alpha.o', 'func_80016000', 'src/a.c')
        (self.root / 'config/names.tsv').write_text('0x80016000\tfunc_80016000\talpha\tev\n')
        batch = Path(self.td.name) / 'F1_x.tsv'
        batch.write_text('address\tsymbol\tnew_name\tscope\n0x80016000\tfunc_80016000\talpha\ttown:0x100000\n'
                         '0x80016400\tfunc_80016400\tmissing\ttown:0x100000\n')
        refusals = Path(self.td.name) / 'refusals.tsv'
        argv = ['--root', str(self.root), '--obj', str(self.obj), '--containers', str(self.disc),
                '--refusals', str(refusals), str(batch)]
        self.assertEqual(M.main(argv), 0)
        self.assertEqual((self.root / 'config/names.tsv').read_text(), '0x80016000\tfunc_80016000\talpha\tev\n')
        self.assertIn('anchor_gone', refusals.read_text())
        M.main(argv + ['--write'])
        self.assertEqual((self.root / 'config/names.tsv').read_text(), '0x80016000\tfunc_80016000\talpha\tev\ttown:0x100000\n')


if __name__ == '__main__':
    unittest.main()
