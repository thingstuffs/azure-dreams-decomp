"""Tests for tools/headers/foreign_imports.py and foreign_twins.py (pure helpers; no build needed)."""
import collections
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import cscan  # noqa: E402
import foreign_imports as F  # noqa: E402


class Render(unittest.TestCase):
    def test_scalars_and_pointers(self):
        self.assertEqual(F.render('f', 'int(int,unsigned char*,short)', 1), 's32 f(s32, u8 *, s16)')
        self.assertEqual(F.render('f', 'struct Particle*(int)', 1), 'void *f(s32)')
        self.assertEqual(F.render('f', 'void(void)', 1), 'void f(void)')
        self.assertEqual(F.render('f', 'void*()', 0), 'void *f()')
        self.assertEqual(F.render('f', 'void(void*,...)', 1), 'void f(void *, ...)')

    def test_function_pointer_and_unrenderable(self):
        self.assertEqual(F.render('f', 'void(struct Object*,void(*)(void))', 1), 'void f(void *, void (*)(void))')
        self.assertIsNone(F.render('f', 'struct Big(int)', 1))


class Candidates(unittest.TestCase):
    def test_width_rule_and_loose_spellings(self):
        c = F.candidates('f', collections.Counter({'void f(s32)': 4, 's16 f(s32)': 3, 'void f()': 1}))
        self.assertEqual(c, ['void f(s32)', 's16 f(s32)', 's32 f(s32)'])

    def test_all_knr_is_a_pure_move(self):
        self.assertEqual(F.candidates('f', collections.Counter({'s32 f()': 3, 'void f()': 1})), ['s32 f()', 'void f()'])

    def test_noreturn_kept(self):
        t = 'void f(s32) __attribute__((noreturn))'
        self.assertEqual(F.candidates('f', collections.Counter({t: 2})), [t])


class HeaderText(unittest.TestCase):
    HEADER = '#ifndef H\n#define H\n/*\n * foreign-program: town 0x78B800-0x796000\n */\n#include "common.h"\n\n#endif\n'

    def test_append_block_is_append_only(self):
        once = F.append_block(self.HEADER, ['void func_80034A1C(void *, void *, s32);'])
        twice = F.append_block(once, ['s32 func_80071494(void);   /* current rand */'])
        self.assertIn(F.BEGIN, twice)
        self.assertLess(twice.index('func_80034A1C'), twice.index('func_80071494'))
        self.assertLess(twice.index(F.END), twice.rindex('#endif'))
        self.assertEqual(set(F.header_decls(twice)), {'func_80034A1C', 'func_80071494'})

    def test_marker_ranges(self):
        self.assertEqual(F.RANGE.findall('main 0x269000-0x275800; town 0x26E000-0x272000'),
                         [('main', '0x269000', '0x275800'), ('town', '0x26E000', '0x272000')])


class EditText(unittest.TestCase):
    def test_remove_and_include(self):
        text = '#include "common.h"\n#include "a.h"\n\nextern void func_8003CF18(u32 kind);\ns32 x;\n'
        sc = cscan.scan(text)
        found, _ = F.local_sites(text, {'func_8003CF18'})
        spans = [(s, e) for s, e, _n, _c in found['func_8003CF18']]
        out = F.edit_text(text, 'dungeon/effect/head_bank_imports.h', spans, sc)
        self.assertEqual(out, '#include "common.h"\n#include "a.h"\n#include "dungeon/effect/head_bank_imports.h"\n\ns32 x;\n')

    def test_common_typedefs_replaced(self):
        text = '#include "x.h"\ntypedef unsigned char u8;\ntypedef unsigned int u32;\n\nextern void func_8010C0F8(void);\n'
        sc = cscan.scan(text)
        found, _ = F.local_sites(text, {'func_8010C0F8'})
        out = F.edit_text(text, 'h.h', [(s, e) for s, e, _n, _c in found['func_8010C0F8']], sc)
        self.assertNotIn('typedef', out)
        self.assertIn('#include "h.h"', out)

    def test_sig_key(self):
        self.assertEqual(F.sig_key('extern void func_804059A8(s32 value);', 'func_804059A8'), 'void(s32)')
        self.assertEqual(F.sig_key('s32 wait_selected(s32 poll_id);', 'wait_selected'),
                         F.sig_key('s32 wait_selected(s32);', 'wait_selected'))
        self.assertNotEqual(F.sig_key('void f(s32);', 'f'), F.sig_key('void f(void *);', 'f'))
        self.assertEqual(F.sig_key('extern void g(s32 v) __attribute__((noreturn));', 'g'), 'void(s32)noreturn')

    def test_address_key(self):
        self.assertEqual(F.address_key('func_7003CF18'), '0x8003CF18')
        self.assertEqual(F.address_key('0x80098f70'), '0x80098F70')


if __name__ == '__main__':
    unittest.main()
