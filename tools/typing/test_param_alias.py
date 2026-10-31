"""param_alias: typed parameter alias, redundant casts and view field synthesis on small clang-parsed TUs.

Run from a repository root (tools/typing on the path), or from the lane with ALIAS_TEST_ROOT=<root>.
Needs clang (the field_census front end)."""
import os
from pathlib import Path
import re
import subprocess
import sys
import tempfile
import unittest

HERE = Path(__file__).resolve().parent
ROOT = Path(os.environ.get('ALIAS_TEST_ROOT', HERE.parents[1]))
for p in (HERE, ROOT / 'tools' / 'typing', ROOT / 'tools'):
    sys.path.insert(0, str(p))

import cast_ast as A  # noqa: E402
import cast_fold as F  # noqa: E402
import field_census as C  # noqa: E402
import param_alias as P  # noqa: E402
import view_swap as V  # noqa: E402

COMMON = ('typedef unsigned char u8; typedef signed char s8; typedef unsigned short u16; typedef short s16;\n'
          'typedef unsigned int u32; typedef int s32;\n#define NULL ((void *)0)\n')


def unit_for(td, source):
    root = Path(td)
    (root / 'include').mkdir(exist_ok=True)
    (root / 'include/common.h').write_text(COMMON)
    (root / 'src').mkdir(exist_ok=True)
    (root / 'src/t.c').write_text(source)
    unit, err = A.clang_unit(root, 'src/t.c')
    assert unit is not None, err
    return root, unit


def plans_for(td, source, kinds=('alias',), min_casts=2):
    root, unit = unit_for(td, source)
    text = unit.text('src/t.c')
    out = []
    for file, fn in unit.functions({'src/t.c'}):
        parents, nodes = {}, []
        for n, p in A.walk(fn):
            parents[id(n)] = p
            nodes.append(n)
        if 'alias' in kinds:
            out += P.plan_alias(V, A, C, unit, file, fn, text, parents, nodes, min_casts)[0]
        if 'redundant' in kinds:
            out += P.plan_redundant(A, C, unit, file, fn, text, parents, nodes)[0]
    return root, out


def applied(td, source, kinds=('alias',), min_casts=2):
    root, plans = plans_for(td, source, kinds, min_casts)
    P.apply_plans(root, plans)
    return (root / 'src/t.c').read_text(), plans


def compiles(root):
    res = subprocess.run(['clang', '--target=mipsel-unknown-none', '-fsyntax-only', '-Werror=incompatible-pointer-types',
                          '-I', 'include', 'src/t.c'], cwd=root, capture_output=True, text=True)
    return res.returncode == 0, res.stderr


VIEW = ('#include "common.h"\ntypedef struct S_80001000_0 {\n    s32 unk_00;\n    u8 pad_04[0x4];\n    s16 unk_08;\n'
        '    u8 pad_0A[0x6];\n} S_80001000_0;\n')


class AliasTests(unittest.TestCase):
    def test_binds_typed_local_and_drops_view_casts(self):
        src = VIEW + ('void g(void *p);\nvoid f(void *object) {\n    s32 x;\n\n    x = ((S_80001000_0 *)object)->unk_00;\n'
                      '    ((S_80001000_0 *)object)->unk_08 = x;\n    g(object);\n}\n')
        with tempfile.TemporaryDirectory() as td:
            text, plans = applied(td, src)
            ok, err = compiles(Path(td))
        self.assertTrue(ok, err)
        self.assertEqual(len(plans), 1)
        self.assertIn('void f(void *object_arg) {\n    S_80001000_0 *object = object_arg;\n    s32 x;\n', text)
        self.assertIn('x = object->unk_00;', text)
        self.assertIn('object->unk_08 = x;', text)
        self.assertIn('g(object);', text)          # a void * slot takes the typed local unchanged
        self.assertNotIn('(S_80001000_0 *)', text)

    def test_unsafe_uses_keep_the_raw_parameter(self):
        src = VIEW + ('typedef struct Other { s32 a; } Other;\nvoid h(Other *o);\n'
                      'void f(void *object) {\n    ((S_80001000_0 *)object)->unk_00 = 1;\n'
                      '    ((S_80001000_0 *)object)->unk_08 = 2;\n    h(object);\n    *(s16 *)((u8 *)object + 8) = 3;\n'
                      '    g2(object + 4);\n}\n')
        src = src.replace('void f(', 'void g2(void *p);\nvoid f(')
        with tempfile.TemporaryDirectory() as td:
            text, plans = applied(td, src)
            ok, err = compiles(Path(td))
        self.assertTrue(ok, err)
        self.assertIn('h(object_arg);', text)               # implicit conversion to another record
        self.assertIn('g2(object_arg + 4);', text)          # void * arithmetic
        self.assertIn('*(s16 *)((u8 *)object + 8) = 3;', text)   # explicit casts work on the typed local

    def test_arg_suffixed_parameter_keeps_its_name(self):
        src = VIEW + ('void g(void *p);\nvoid f(void *bounds_arg) {\n    ((S_80001000_0 *)bounds_arg)->unk_00 = 1;\n'
                      '    ((S_80001000_0 *)bounds_arg)->unk_08 = 2;\n    g(bounds_arg);\n    g(bounds_arg + 1);\n}\n')
        with tempfile.TemporaryDirectory() as td:
            text, _ = applied(td, src)
            ok, err = compiles(Path(td))
        self.assertTrue(ok, err)
        self.assertIn('void f(void *bounds_arg) {\n    S_80001000_0 *bounds = bounds_arg;\n', text)
        self.assertIn('bounds->unk_08 = 2;', text)
        self.assertIn('g(bounds);', text)
        self.assertIn('g(bounds_arg + 1);', text)

    def test_declaration_after_leading_declarations(self):
        src = VIEW + ('void f(void *o) {\n    s32 a;\n    s32 b = 2;\n\n    a = ((S_80001000_0 *)o)->unk_00;\n'
                      '    ((S_80001000_0 *)o)->unk_08 = a + b;\n}\n')
        with tempfile.TemporaryDirectory() as td:
            root, unit = unit_for(td, src)
            text = unit.text('src/t.c')
            fn = next(fn for _, fn in unit.functions({'src/t.c'}))
            parents, nodes = {}, []
            for n, p in A.walk(fn):
                parents[id(n)] = p
                nodes.append(n)
            plans = P.plan_alias(V, A, C, unit, 'src/t.c', fn, text, parents, nodes, 2, 'last')[0]
            P.apply_plans(root, plans)
            out = (root / 'src/t.c').read_text()
            ok, err = compiles(root)
        self.assertTrue(ok, err)
        self.assertIn('    s32 b = 2;\n    S_80001000_0 *o = o_arg;\n\n    a = o->unk_00;', out)

    def test_declaration_after_refused_when_an_initializer_reads_the_parameter(self):
        src = VIEW + ('void f(void *o) {\n    s32 a = ((S_80001000_0 *)o)->unk_00;\n\n'
                      '    ((S_80001000_0 *)o)->unk_08 = a;\n}\n')
        with tempfile.TemporaryDirectory() as td:
            root, unit = unit_for(td, src)
            fn = next(fn for _, fn in unit.functions({'src/t.c'}))
            parents, nodes = {}, []
            for n, p in A.walk(fn):
                parents[id(n)] = p
                nodes.append(n)
            plans, pool = P.plan_alias(V, A, C, unit, 'src/t.c', fn, unit.text('src/t.c'), parents, nodes, 2, 'last')
        self.assertEqual(plans, [])
        self.assertEqual(pool.get('refused:param_read_in_declarations'), 2)

    def test_first_statement_gets_a_blank_line(self):
        src = VIEW + 'void f(void *o) {\n    ((S_80001000_0 *)o)->unk_00 = 1;\n    ((S_80001000_0 *)o)->unk_08 = 2;\n}\n'
        with tempfile.TemporaryDirectory() as td:
            text, _ = applied(td, src)
        self.assertIn('void f(void *o_arg) {\n    S_80001000_0 *o = o_arg;\n\n    o->unk_00 = 1;\n', text)

    def test_refuses_assigned_or_address_taken_parameter(self):
        for body in ('    object = 0;\n', '    k(&object);\n'):
            src = VIEW + ('void k(void **p);\nvoid f(void *object) {\n    ((S_80001000_0 *)object)->unk_00 = 1;\n'
                          '    ((S_80001000_0 *)object)->unk_08 = 2;\n' + body + '}\n')
            with tempfile.TemporaryDirectory() as td:
                _, plans = plans_for(td, src)
            self.assertEqual(plans, [], body)

    def test_refuses_macro_spelled_name_and_taken_arg_name(self):
        src = VIEW + ('#define object other\nvoid f(void *object) {\n    ((S_80001000_0 *)object)->unk_00 = 1;\n'
                      '    ((S_80001000_0 *)object)->unk_08 = 2;\n}\n')
        with tempfile.TemporaryDirectory() as td:
            _, plans = plans_for(td, src)
        self.assertEqual(plans, [])
        src = VIEW + ('int object_arg;\nvoid f(void *object) {\n    ((S_80001000_0 *)object)->unk_00 = 1;\n'
                      '    ((S_80001000_0 *)object)->unk_08 = 2;\n}\n')
        with tempfile.TemporaryDirectory() as td:
            _, plans = plans_for(td, src)
        self.assertEqual(plans, [])

    def test_min_casts(self):
        src = VIEW + 'void f(void *o) {\n    ((S_80001000_0 *)o)->unk_00 = 1;\n}\n'
        with tempfile.TemporaryDirectory() as td:
            _, plans = plans_for(td, src)
            self.assertEqual(plans, [])
        with tempfile.TemporaryDirectory() as td:
            _, plans = plans_for(td, src, min_casts=1)
            self.assertEqual(len(plans), 1)

    def test_second_view_keeps_its_cast_on_the_typed_local(self):
        src = VIEW + ('typedef struct S_80001000_1 { u8 pad_00[0x10]; s32 unk_10; } S_80001000_1;\n'
                      'void f(void *o) {\n    ((S_80001000_0 *)o)->unk_00 = 1;\n    ((S_80001000_0 *)o)->unk_08 = 2;\n'
                      '    ((S_80001000_1 *)o)->unk_10 = 3;\n}\n')
        with tempfile.TemporaryDirectory() as td:
            text, _ = applied(td, src)
            ok, err = compiles(Path(td))
        self.assertTrue(ok, err)
        self.assertIn('((S_80001000_1 *)o)->unk_10 = 3;', text)


class RedundantTests(unittest.TestCase):
    def test_same_type_and_void_into_declared_type(self):
        src = ('#include "common.h"\ntypedef struct T { s32 a; } T;\nvoid *get(void);\n'
               'void f(T *t, u8 *b) {\n    T *x = (T *)get();\n    T *y;\n\n    y = (T *)get();\n'
               '    ((T *)t)->a = 1;\n    *(u8 *)b = 2;\n    x->a = y->a;\n}\n')
        with tempfile.TemporaryDirectory() as td:
            text, plans = applied(td, src, kinds=('redundant',))
            ok, err = compiles(Path(td))
        self.assertTrue(ok, err)
        self.assertIn('T *x = get();', text)
        self.assertIn('y = get();', text)
        self.assertIn('t->a = 1;', text)
        self.assertIn('*b = 2;', text)
        self.assertEqual(len(plans), 4)

    def test_keeps_qualified_and_function_pointer_casts(self):
        src = ('#include "common.h"\ntypedef void (*Fn)(void);\nvoid f(volatile u8 *b, Fn g) {\n'
               '    *(volatile u8 *)b = 1;\n    ((Fn)g)();\n}\n')
        with tempfile.TemporaryDirectory() as td:
            _, plans = plans_for(td, src, kinds=('redundant',))
        self.assertEqual(plans, [])

    def test_grouping_kept_for_unary_operand(self):
        src = '#include "common.h"\ntypedef struct T { s32 a; } T;\nvoid f(T **pp) {\n    ((T *)*pp)->a = 1;\n}\n'
        with tempfile.TemporaryDirectory() as td:
            text, _ = applied(td, src, kinds=('redundant',))
            ok, err = compiles(Path(td))
        self.assertTrue(ok, err)
        self.assertIn('(*pp)->a = 1;', text)


class SynthTests(unittest.TestCase):
    def synth(self, src):
        with tempfile.TemporaryDirectory() as td:
            root, unit = unit_for(td, src)
            text = unit.text('src/t.c')
            sites = {}
            for file, fn in unit.functions({'src/t.c'}):
                for k, v in P.raw_sites(A, C, F, unit, file, fn).items():
                    sites.setdefault(k, []).extend(v)
            plans, pool = P.plan_synth(A, C, F, unit, 'src/t.c', text, sites, P.local_views(A, C, unit, 'src/t.c', text))
            before = unit.layouts
            P.apply_plans(root, plans)
            after, _ = A.clang_unit(root, 'src/t.c')
            return (root / 'src/t.c').read_text(), plans, pool, before, after.layouts

    def test_splits_pad_without_moving_anything(self):
        src = VIEW + 'void f(S_80001000_0 *p) {\n    *(s16 *)((u8 *)p + 0xC) = 1;\n    p->unk_08 = *(u16 *)((u8 *)p + 4);\n}\n'
        text, plans, pool, before, after = self.synth(src)
        self.assertIn('    u8 pad_0A[0x2];\n    s16 unk_0C;\n    u8 pad_0E[0x2];\n', text)
        self.assertIn('    u16 unk_04;\n    u8 pad_06[0x2];\n', text)
        key = 'S_80001000_0'
        self.assertEqual(before[key]['size'], after[key]['size'])
        self.assertEqual(before[key]['align'], after[key]['align'])
        old = {n['name']: n['off'] for n in before[key]['kids']}
        new = {n['name']: n['off'] for n in after[key]['kids']}
        for name in ('unk_00', 'unk_08'):
            self.assertEqual(old[name], new[name])
        self.assertEqual(new['unk_0C'], 0xC)

    def test_refuses_mixed_widths_and_misalignment(self):
        src = VIEW + ('void f(S_80001000_0 *p) {\n    *(s16 *)((u8 *)p + 0xC) = 1;\n    *(u8 *)((u8 *)p + 0xC) = 1;\n'
                      '    *(s16 *)((u8 *)p + 0xB) = 1;\n}\n')
        text, plans, pool, _, _ = self.synth(src)
        self.assertEqual(plans, [])
        self.assertEqual(pool.get('mixed_width'), 2)
        self.assertEqual(pool.get('alignment'), 1)

    def test_refuses_alignment_above_the_view(self):
        src = ('#include "common.h"\ntypedef struct S_80002000_0 {\n    u8 unk_00;\n    u8 pad_01[0x7];\n} S_80002000_0;\n'
               'void f(S_80002000_0 *p) {\n    *(s32 *)((u8 *)p + 4) = 1;\n}\n')
        text, plans, pool, _, _ = self.synth(src)
        self.assertEqual(plans, [])
        self.assertEqual(pool.get('alignment'), 1)


if __name__ == '__main__':
    unittest.main()
