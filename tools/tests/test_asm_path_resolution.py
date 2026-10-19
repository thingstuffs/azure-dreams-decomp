"""Ledger asm_path resolution must not depend on the root/asm -> build_slus/asm symlink.

Lane and gate roots carry that symlink (mk_scratch_root.sh, mk_ovl_root.sh); a canonical checkout
may not.  Fixture roots here have NO asm symlink: asm/... names must resolve to build_slus/asm/...
while every hashed name stays the logical ``asm/...`` string.

    ./.venv/bin/python3 -m pytest tools/tests/test_asm_path_resolution.py -q
"""
import sys
import tempfile
import unittest
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(REPO/'tools'), str(REPO/'tools/gate')]
import asm_paths  # noqa: E402
import overlay_module_gate as M  # noqa: E402
from lanes import proof_receipts as P  # noqa: E402


class AsmPathResolution(unittest.TestCase):
    def setUp(self):
        self._tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self._tmp.cleanup)
        self.root = Path(self._tmp.name).resolve()
        a = self.root/'build_slus/asm/psyq/libcard'
        a.mkdir(parents=True)
        (a/'A74.s').write_text('.include "macro.inc"\nnop\n')
        (a/'A75.s').write_text('nop\n')
        (self.root/'include').mkdir()
        (self.root/'include/macro.inc').write_text('# macros\n')
        (self.root/'build_slus/asm/psyq/libcard/local.inc').write_text('# local\n')

    def link(self):
        (self.root/'asm').symlink_to('build_slus/asm')

    def test_helper_falls_back_to_build_slus(self):
        got = asm_paths.resolve(self.root, 'asm/psyq/libcard/A74.s')
        self.assertEqual(got, self.root/'build_slus/asm/psyq/libcard/A74.s')
        self.assertTrue(got.is_file())

    def test_helper_prefers_root_path_and_leaves_other_names(self):
        self.link()
        self.assertEqual(asm_paths.resolve(self.root, 'asm/psyq/libcard/A74.s'), self.root/'asm/psyq/libcard/A74.s')
        self.assertEqual(asm_paths.resolve(self.root, 'include/macro.inc'), self.root/'include/macro.inc')
        self.assertEqual(asm_paths.resolve(self.root, 'missing/x.s'), self.root/'missing/x.s')

    def test_closure_names_are_logical(self):
        for linked in (False, True):
            with self.subTest(linked=linked):
                if linked:
                    self.link()
                self.assertEqual(M.closure(self.root, ['asm/psyq/libcard/A74.s']),
                                 {'asm/psyq/libcard/A74.s', 'include/macro.inc'})

    def test_closure_same_dir_include_stays_logical(self):
        (self.root/'build_slus/asm/psyq/libcard/A76.s').write_text('.include "local.inc"\n')
        self.assertEqual(M.closure(self.root, ['asm/psyq/libcard/A76.s']),
                         {'asm/psyq/libcard/A76.s', 'asm/psyq/libcard/local.inc'})

    def test_assembly_inputs_identical_with_and_without_symlink(self):
        (self.root/'build_slus/asm/psyq/libcard/A76.s').write_text('.include "local.inc"\n')
        before = P.assembly_inputs(self.root, 'asm/psyq/libcard/A76.s')
        self.link()
        after = P.assembly_inputs(self.root, 'asm/psyq/libcard/A76.s')
        self.assertEqual(before, after)
        self.assertEqual(set(before), {'asm/psyq/libcard/A76.s', 'asm/psyq/libcard/local.inc'})

    def test_missing_asm_still_fails(self):
        with self.assertRaises(ValueError):
            P.assembly_inputs(self.root, 'asm/psyq/libcard/NOPE.s')


if __name__ == '__main__':
    unittest.main()
