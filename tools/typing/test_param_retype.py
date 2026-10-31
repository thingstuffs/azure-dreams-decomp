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


V2_HEADER = """#ifndef V2_H
#define V2_H
typedef unsigned char u8;
typedef short s16;
typedef int s32;
typedef struct ObjectNodeHeader { u8 pad_00[0x1E]; unsigned short flags; } ObjectNodeHeader;
typedef struct Body { s32 x; u8 pad_04[0x9]; u8 species; s16 y; } Body;
typedef struct Big { Body body; u8 pad_10[0x10]; void *pending; } Big;
extern Body *dungeon_actor_ring_anchor;
#define U8_AT(p, o) (*(u8 *)((u8 *)(p) + (o)))
extern void take_void(void *);
#endif
"""

V2_SRC = """#include "v2.h"

typedef struct View { u8 pad[0x20]; void *unk_20; } View;

s32 tail(View *p, void *item) {
    if (p == dungeon_actor_ring_anchor) {
        p->unk_20 = item;
        return 0;
    }
    return 1;
}

s32 untail(View *p, void *item) {
    p->unk_20 = item;
    return 0;
}

s32 bytes(u8 *p) {
    u8 *alias = p;
    take_void(p - 0x20);
    return p[0xD] + U8_AT(p, 0xD) + *alias;
}

s32 cmp(void *p) {
    if (p == (s32)dungeon_actor_ring_anchor) {
        return 1;
    }
    return ((Body *)p)->y;
}

s32 integer(s32 p) {
    return ((Body *)p)->x;
}
"""


@unittest.skipUnless(shutil.which('clang'), 'clang not installed')
class KitV2(unittest.TestCase):
    """kit_v2 spec keys: tail_type, byte_arith, byte_macros, alias stores, compare_uncast, int_placeholder."""

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        root = Path(self.tmp.name)
        (root / 'include').mkdir()
        (root / 'src').mkdir()
        (root / 'include/v2.h').write_text(V2_HEADER)
        (root / 'src/v2.c').write_text(V2_SRC)
        self.units = R.Units(root)
        self.saved = {k: getattr(R, k) for k in ('TAIL_TYPE', 'TAIL_ANY', 'BYTE_ARITH', 'BYTE_MACROS',
                                                 'ALIAS_CAST', 'COMPARE_UNCAST', 'INT_PLACEHOLDER', 'SIGN_REMAP')}

    def tearDown(self):
        for k, v in self.saved.items():
            setattr(R, k, v)
        self.tmp.cleanup()

    def plan(self, name, i=0):
        unit = self.units.get('src/v2.c')
        fn = R.find_function(unit, 'src/v2.c', name)
        plan = R.plan_retype(unit, 'src/v2.c', fn, R.params_of(fn)[i], R.Target(unit, 'Body *'))
        text = None if 'refused' in plan else R.apply_text_edits(unit.text('src/v2.c'), plan['edits'])
        return plan, text

    def test_tail_type_only_when_guarded(self):
        plan, _ = self.plan('tail')
        self.assertEqual(plan.get('refused'), 'member_unmapped@0x20:void*')
        R.TAIL_TYPE = 'Big *'
        plan, text = self.plan('tail')
        self.assertNotIn('refused', plan, plan)
        self.assertIn('((Big *)p)->pending = item;', text)
        plan, _ = self.plan('untail')
        self.assertIn('refused', plan)                      # unguarded: not the player
        R.TAIL_ANY = True                                    # player-only symbol (spec "tail_symbols")
        plan, text = self.plan('untail')
        self.assertIn('((Big *)p)->pending = item;', text)

    def test_byte_arith_macros_alias(self):
        plan, _ = self.plan('bytes')
        self.assertIn('refused', plan)
        R.BYTE_ARITH = R.BYTE_MACROS = R.ALIAS_CAST = True
        plan, text = self.plan('bytes')
        self.assertNotIn('refused', plan, plan)
        self.assertIn('s32 bytes(Body *p)', text)
        self.assertIn('u8 *alias = (u8 *)p;', text)
        self.assertIn('take_void(((ObjectNodeHeader *)p - 1));', text)
        self.assertIn('return p->species + U8_AT(p, 0xD) + *alias;', text)

    def test_compare_uncast(self):
        plan, _ = self.plan('cmp')
        self.assertEqual(plan.get('refused'), 'compare_needs_cast')
        R.COMPARE_UNCAST = True
        plan, text = self.plan('cmp')
        self.assertIn('if (p == dungeon_actor_ring_anchor)', text)
        self.assertIn('return p->y;', text)

    def test_function_pointer_member_by_signature(self):
        root = Path(self.tmp.name)
        (root / 'src/fn.c').write_text(
            'typedef struct A A;\ntypedef void (*H)(A *, void *);\ntypedef void (*Callback)(void *, void *);\n'
            'typedef int (*IC)(void *, void *);\n'
            'struct A { union { void *address; void (*run)(void *, void *); H handler; } u; };\n'
            'int f(A *a) { return 0; }\n')
        unit = R.Units(root).get('src/fn.c')
        tgt = R.Target(unit, 'A *')
        self.assertEqual(R.map_member(unit, tgt, 0, 'Callback', False), 'u.run')
        self.assertEqual(R.map_member(unit, tgt, 0, 'H', False), 'u.handler')
        self.assertIsNone(R.map_member(unit, tgt, 0, 'IC', False))   # int-returning view: no member, no rollback

    def test_address_only_member_and_eager_uncast(self):
        root = Path(self.tmp.name)
        (root / 'src/addr.c').write_text(
            '#include "v2.h"\ntypedef struct Wide { s16 lo; } Wide;\n'
            's32 addr(Wide *p) {\n    if (p == (Wide *)dungeon_actor_ring_anchor) { return 0; }\n'
            '    return *(u8 *)((u8 *)&p->lo + 1);\n}\n')
        unit = R.Units(root).get('src/addr.c')
        fn = R.find_function(unit, 'src/addr.c', 'addr')
        plan = R.plan_retype(unit, 'src/addr.c', fn, R.params_of(fn)[0], R.Target(unit, 'Body *'))
        self.assertIn('refused', plan)                      # s16 at +0: Body has an s32 there
        R.BYTE_ARITH = R.COMPARE_UNCAST = True
        plan = R.plan_retype(unit, 'src/addr.c', fn, R.params_of(fn)[0], R.Target(unit, 'Body *'))
        self.assertNotIn('refused', plan, plan)
        text = R.apply_text_edits(unit.text('src/addr.c'), plan['edits'])
        self.assertIn('if (p == dungeon_actor_ring_anchor)', text)
        self.assertIn('return *(u8 *)((u8 *)&p->x + 1);', text)   # only the address is used

    def test_int_placeholder_plan(self):
        R.INT_PLACEHOLDER = True
        plan, text = self.plan('integer')
        self.assertNotIn('refused', plan, plan)
        self.assertIn('s32 integer(Body *p)', text)
        self.assertIn('return p->x;', text)


if __name__ == '__main__':
    unittest.main()
