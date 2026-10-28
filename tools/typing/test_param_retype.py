#!/usr/bin/env python3
"""Regression tests for tools/typing/param_retype.py (python3 -m unittest tools.typing.test_param_retype -v)."""
from pathlib import Path
import shutil
import sys
import tempfile
import unittest

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent), str(HERE.parents[1])]
import param_retype as R  # noqa: E402
import cast_ast as A  # noqa: E402

HEADER = """#ifndef X_H
#define X_H
typedef unsigned char u8;
typedef short s16;
typedef int s32;
typedef struct Obj {
    s32 x;
    u8 pad_04[0x20];
    u8 tile_x;
    u8 tile_y;
    s16 y;
} Obj;
#endif
"""

CALLEE = """#include "x.h"

typedef struct S_80012345_0 {
    u8 pad[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80012345_0;

s32 callee(S_80012345_0 *p, void *q) {
    ((Obj *)q)->x = 3;
    return p->unk_24 + p->unk_25 + ((Obj *)q)->y;
}

s32 user(S_80012345_0 *p) {
    return *(u8 *)p;
}

s32 named(Obj *o) {
    return o->x;
}
"""

CALLER = """#include "x.h"

extern void *get();
extern s32 callee();

s32 caller(void) {
    u8 *h;
    s32 word;

    h = (u8 *)get();
    word = (s32)get();
    return callee(h, (void *)word) + callee(h, h + 1);
}

extern s32 named();

s32 caller3(void) {
    u8 *b = get();

    return named(b);
}

s32 caller2(Obj *o) {
    return callee(((u8 *)o), o);
}
"""


class Pure(unittest.TestCase):
    def test_assignable_rules(self):
        a = R.assignable
        self.assertTrue(a('unsigned char*', 'char*'))           # -Wpointer-sign only
        self.assertTrue(a('int*', 'unsigned int*'))
        self.assertFalse(a('int*', 'unsigned char*'))           # u8 * to s32 *: incompatible
        self.assertTrue(a('void*', 'rec:Obj*'))
        self.assertTrue(a('rec:Obj*', 'void*'))
        self.assertFalse(a('rec:Obj*', 'unsigned char*'))
        self.assertFalse(a('void*', 'int'))                     # int-conversion
        self.assertTrue(a('void*', 'int', null=True))
        self.assertFalse(a('int', 'void*'))
        self.assertTrue(a('short', 'int'))
        self.assertTrue(a('unsigned char*', 'unsigned char[4]'))  # array decay
        self.assertFalse(a('rec:A', 'rec:B'))

    def test_spellings(self):
        self.assertEqual(R.decay('short[3]'), 'short*')
        self.assertEqual(R.spelled('TileObject*'), 'TileObject *')
        self.assertEqual(R.spelled('struct  Foo  *'), 'struct Foo *')
        self.assertEqual(R.spelled('s32'), 's32')
        self.assertEqual(R.type_name('const struct Foo *'), 'Foo')
        self.assertEqual(R.type_name('unsigned char *'), '')
        self.assertEqual(R.strength('ActorRecord'), 0)
        self.assertEqual(R.strength('Rec_D_80082E80'), 1)
        self.assertEqual(R.strength('S_800A2CB8_1'), 1)

    def test_text_edits(self):
        self.assertEqual(R.apply_text_edits('abcdef', [(0, 1, 'X'), (3, 5, 'YY')]), 'XbcYYf')
        with self.assertRaises(ValueError):
            R.apply_text_edits('abcdef', [(0, 3, 'X'), (2, 4, 'Y')])

    def test_ensure_include(self):
        text = '#include "common.h"\n\ns32 f(void);\n'
        out = R.ensure_include(text, 'include/shared/tile_object.h')
        self.assertEqual(out, '#include "common.h"\n#include "shared/tile_object.h"\n\ns32 f(void);\n')
        self.assertEqual(R.ensure_include(out, 'include/shared/tile_object.h'), out)

    def test_respell_declaration(self):
        text = 'extern s32 f();\ns32 g(Rec_X *start, Rec_X *end);\nvoid h(u8 *);\n'
        self.assertIsNone(R.respell_in_text(text, 'f', 0, 'TileObject *'))
        out = R.respell_in_text(text, 'g', 1, 'TileObject *')
        self.assertIn('s32 g(Rec_X *start, TileObject *end);', out)
        out = R.respell_in_text(text, 'h', 0, 'void *')
        self.assertIn('void h(void *);', out)
        self.assertIsNone(R.respell_in_text(out, 'h', 0, 'void *'))

    def test_line_map(self):
        old = 'a\nextern int f();\nb\nc\n'
        new = '#include "x.h"\na\nb\nc\n'
        m = R.line_map(old, new)
        self.assertEqual(m[2], 1)
        self.assertEqual(m[4], 4)


@unittest.skipUnless(shutil.which('clang'), 'clang not installed')
class Fixture(unittest.TestCase):
    """End-to-end planning on a three-file tree parsed by the same clang front end."""

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        root = Path(self.tmp.name)
        (root / 'include').mkdir()
        (root / 'src').mkdir()
        (root / 'include/x.h').write_text(HEADER)
        (root / 'src/callee.c').write_text(CALLEE)
        (root / 'src/caller.c').write_text(CALLER)
        self.root = root
        self.units = R.Units(root)

    def tearDown(self):
        self.tmp.cleanup()

    def callee(self):
        unit = self.units.get('src/callee.c')
        fn = R.find_function(unit, 'src/callee.c', 'callee')
        return unit, fn, R.params_of(fn)

    def test_param_retype_renames_members_and_drops_casts(self):
        unit, fn, params = self.callee()
        target = R.Target(unit, 'Obj *')
        self.assertEqual(target.key, 'Obj')
        self.assertEqual(target.home, 'include/x.h')
        plan = R.plan_retype(unit, 'src/callee.c', fn, params[0], target)
        self.assertNotIn('refused', plan, plan)
        text = R.apply_text_edits(unit.text('src/callee.c'), plan['edits'])
        self.assertIn('s32 callee(Obj *p, void *q)', text)
        self.assertIn('p->tile_x + p->tile_y', text)
        plan = R.plan_retype(unit, 'src/callee.c', fn, params[1], target)
        self.assertNotIn('refused', plan, plan)
        self.assertEqual(plan['removed'], 2)
        text = R.apply_text_edits(unit.text('src/callee.c'), plan['edits'])
        self.assertIn('q->x = 3;', text)
        self.assertIn('+ q->y;', text)
        self.assertIn('Obj *q)', text)

    def test_byte_use_refuses(self):
        unit = self.units.get('src/callee.c')
        fn = R.find_function(unit, 'src/callee.c', 'user')
        plan = R.plan_retype(unit, 'src/callee.c', fn, R.params_of(fn)[0], R.Target(unit, 'Obj *'))
        self.assertNotIn('refused', plan)        # *(u8 *)p stays an explicit cast: valid on any pointer
        unit2 = self.units.get('src/caller.c')
        fn2 = R.find_function(unit2, 'src/caller.c', 'caller')
        calls = R.calls_in(unit2, 'src/caller.c', 'callee')
        self.assertEqual(len(calls), 3)

    def test_caller_holders(self):
        unit = self.units.get('src/caller.c')
        per, arity = R.gather_calls(self.units, ['src/caller.c'], 'callee', 2)
        self.assertFalse(arity)
        target = R.Target(self.units.get('src/callee.c'), 'Obj *')
        first = per[0][0]
        fix = R.holder_fix(first, target)
        # h is also used as `h + 1`: byte arithmetic refuses the retype
        self.assertEqual(fix['fix'], 'none')
        self.assertEqual(fix['why'], 'pointer_arithmetic')
        cast_arg = per[1][0]
        self.assertEqual(R.holder_fix(cast_arg, target)['fix'], 'compatible')   # (void *)word: void * converts
        expr_arg = per[1][1]
        fix = R.holder_fix(expr_arg, target)
        self.assertEqual((fix['holder'], fix['fix']), ('expression', 'none'))

    def test_drop_cast_keeps_no_extra_parens(self):
        unit = self.units.get('src/caller.c')
        fn = R.find_function(unit, 'src/caller.c', 'caller2')
        (_, call), = [c for c in R.calls_in(unit, 'src/caller.c', 'callee') if c[0] is fn]
        arg = A.kids(call)[1]
        kind, cast = R.holder_of(unit, fn, arg)
        self.assertEqual(kind, 'cast')
        target = R.Target(unit, 'Obj *')
        x = ('src/caller.c', unit, fn, call, arg, 'u8 *', False)
        self.assertEqual(R.holder_fix(x, target)['fix'], 'drop_cast')
        text = R.apply_text_edits(unit.text('src/caller.c'), [R.drop_cast_edit(unit.text('src/caller.c'), arg, cast)])
        self.assertIn('return callee(o, o);', text)

    def test_named_record_is_kept(self):
        unit = self.units.get('src/callee.c')
        fn = R.find_function(unit, 'src/callee.c', 'named')
        per, _ = R.gather_calls(self.units, ['src/caller.c'], 'named', 1)
        self.assertEqual(R.spelled(per[0][0][5]), 'u8 *')
        ev = R.evaluate_param(unit, 'src/callee.c', fn, R.params_of(fn)[0], per[0])
        self.assertEqual(ev['evaluated'][1]['plan']['refused'], 'member_access_needs_record')  # u8 * loses o->x
        self.assertEqual(ev['choice']['type'], 'Obj *')                       # caller's `b` takes Obj *
        self.assertEqual(ev['choice']['fixes'][0]['fix'], 'retype_local')

    def test_evaluate_param_prefers_shared_record(self):
        unit, fn, params = self.callee()
        per, _ = R.gather_calls(self.units, ['src/caller.c'], 'callee', 2)
        ev = R.evaluate_param(unit, 'src/callee.c', fn, params[0], per[0])
        types = [e['type'] for e in ev['evaluated']]
        self.assertEqual(types, ['S_80012345_0 *', 'u8 *', 'Obj *'])   # Obj: what caller2 casts away
        self.assertEqual(ev['klass'], 'view_param')
        self.assertIsNone(ev['choice'])           # u8 * loses the members; the view is private to callee.c
        self.assertIn('member_access_needs_record', ev['why'])
        self.assertIn('private_target_type', ev['why'])


if __name__ == '__main__':
    unittest.main()
