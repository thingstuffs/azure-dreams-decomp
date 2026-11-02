"""prove(select=): screen proofs compile a chosen subset of the affected set and never claim the rest."""
import importlib.util
import os
from pathlib import Path
import sys
import unittest

HERE = Path(__file__).resolve().parent
ROOT = Path(os.environ.get('AFFECTED_TEST_ROOT') or Path(__file__).resolve().parents[3])
sys.path[:0] = [str(HERE), str(ROOT / 'tools/build/tests'), str(ROOT)]
import test_affected as TA   # noqa: E402

_spec = importlib.util.spec_from_file_location('affected_under_test', HERE.parent / 'affected.py')
A = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(A)


class ScreenTests(TA.ProveVerdictTests):
    def prove_select(self, files, produced, select):
        return A.prove(self.cand.root, files, self.base.root, compile_tasks=self.compiler(produced), select=select)

    def test_screen_skips_unselected_copies(self):
        r = self.prove_select(['src/owner.c'], {'rcopy': b'C' * 63 + b'D'},
                              lambda ids, g: [i for i in ids if i != 'rcopy'])
        self.assertTrue(r['screen'])
        self.assertEqual(r['verdict'], 'PASS')
        self.assertNotIn('rcopy', r['recipes'])
        self.assertNotIn('dungeon/bank_1', r['images'])     # nothing selected links there: not judged

    def test_screen_reports_a_selected_failure(self):
        r = self.prove_select(['src/owner.c'], {'rcopy': b'C' * 63 + b'D'}, lambda ids, g: list(ids))
        self.assertEqual(r['verdict'], 'CHANGED')
        self.assertEqual(r['screen_recipes'], len(r['recipes']))


if __name__ == '__main__':
    unittest.main()
