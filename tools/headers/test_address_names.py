"""Unit coverage for address_names.py (the TU rewrite) and extern_bulk.py's --names filter."""
import argparse
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import address_names as A   # noqa: E402
import extern_bulk as B     # noqa: E402

TU = '''#include "common.h"

extern s16 func_80069EF8(void); /* random */
extern void func_8003E188(s32 index, s32 flag);

/* calls func_80069EF8 in a comment and "func_80069EF8" in a string stay */
void f(void) {
    s16 value = func_80069EF8();
    extern_like(value);
    func_8003E188(value, 0);
}
'''


class ApplyTest(unittest.TestCase):
    def run_apply(self, text, pairs, header=None):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            (root / 'include').mkdir()
            (root / 'include/common.h').write_text(header or '/* empty */\n')
            (root / 'src').mkdir()
            (root / 'src/a.c').write_text(text)
            log = []
            A._CORPUS.clear()
            A.apply_one(root, 'src/a.c', pairs, log)
            return (root / 'src/a.c').read_text(), log

    def test_respell_declaration_and_calls(self):
        out, log = self.run_apply(TU, [('func_80069EF8', 'rand', ''), ('func_8003E188', 'set_packed_2bit_flag', '')])
        self.assertIn('extern s16 rand(void); /* random */', out)
        self.assertIn('s16 value = rand();', out)
        self.assertIn('set_packed_2bit_flag(value, 0);', out)
        self.assertIn('extern void set_packed_2bit_flag(s32 index, s32 flag);', out)
        # comments and strings untouched
        self.assertIn('calls func_80069EF8 in a comment and "func_80069EF8"', out)
        self.assertEqual([r[4] for r in log], ['respelled', 'respelled'])

    def test_block_statement_is_not_a_declaration(self):
        out, _ = self.run_apply(TU, [('func_80069EF8', 'rand', '')])
        self.assertIn('    s16 value = rand();\n', out)

    def test_visible_declaration_deletes_local_one(self):
        out, log = self.run_apply(TU, [('func_80069EF8', 'rand', '')], header='s32 rand(void);\n')
        self.assertNotIn('extern s16', out)
        self.assertIn('s16 value = rand();', out)
        self.assertTrue(log[0][4].startswith('deleted_declaration'))

    def test_tu_that_declares_the_new_name_keeps_one_declaration(self):
        text = TU.replace('#include "common.h"\n', '#include "common.h"\nextern s32 rand(void);\n')
        out, log = self.run_apply(text, [('func_80069EF8', 'rand', '')])
        self.assertEqual(out.count('rand(void);'), 1)

    def test_no_declaration_and_nothing_visible_holds(self):
        text = 'void g(void) { func_80042640(0, 1); }\n'
        out, log = self.run_apply(text, [('func_80042640', 'init_monster_from_stats', 'include/engine/entity.h')])
        self.assertEqual(out, text)
        self.assertEqual(log[0][4], 'hold:no_visible_prototype')

    def test_idempotent(self):
        once, _ = self.run_apply(TU, [('func_80069EF8', 'rand', '')])
        twice, log = self.run_apply(once, [('func_80069EF8', 'rand', '')])
        self.assertEqual(once, twice)
        self.assertEqual(log, [])


class NamesFilterTest(unittest.TestCase):
    def test_names_file_tsv_and_list(self):
        with tempfile.TemporaryDirectory() as d:
            tsv = Path(d) / 'plan.tsv'
            tsv.write_text('file\told\tnew\tkind\nsrc/a.c\tfunc_1\trand\tlibrary_alias\n')
            a = argparse.Namespace(names=['abs'], names_from=None, names_file=tsv)
            self.assertEqual(B.load_names(a), {'abs', 'rand'})
            lst = Path(d) / 'names.txt'
            lst.write_text('rsin\nrcos\n')
            a = argparse.Namespace(names=None, names_from=None, names_file=lst)
            self.assertEqual(B.load_names(a), {'rsin', 'rcos'})
            a = argparse.Namespace(names=None, names_from=None, names_file=None)
            self.assertIsNone(B.load_names(a))

    def test_names_from_sdk_includes_kernel_entry_points(self):
        a = argparse.Namespace(names=None, names_from='sdk', names_file=None)
        got = B.load_names(a)
        for n in ('OpenEvent', 'EnterCriticalSection', 'SetRCnt', 'rindex', 'rsin'):
            self.assertIn(n, got)


if __name__ == '__main__':
    unittest.main()
