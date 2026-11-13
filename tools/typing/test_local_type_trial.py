#!/usr/bin/env python3
"""Regression tests for tools/typing/local_type_trial.py (python3 -m unittest tools.typing.test_local_type_trial -v).

The planner runs on real Clang units of small fixture trees; the proof stages (capture_one, cast_fold, debt,
lint) are the existing tools' and are not repeated here."""
from pathlib import Path
import shutil
import sys
import tempfile
import unittest

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent), str(HERE.parents[1])]
import cast_ast as A  # noqa: E402
import local_type_trial as T  # noqa: E402

HEADER = """#ifndef X_H
#define X_H
typedef unsigned char u8;
typedef short s16;
typedef int s32;
typedef struct ObjectNodeHeader {
    struct ObjectNodeHeader *next;
    u8 pad_04[0x1C];
} ObjectNodeHeader;
#define NODE_BODY(node) ((void *)((ObjectNodeHeader *)(node) + 1))
#define NODE_HEADER(body) ((ObjectNodeHeader *)(body) - 1)
typedef struct Actor {
    s32 flags;
    union { s32 value; struct { s16 low; s16 high; } parts; } scratch;
    u8 hp;
    u8 max_hp;
    s16 facing;
    s32 pad_0C;
    ObjectNodeHeader *next_header;
} Actor;
typedef struct Other {
    s32 word;
} Other;
extern s32 flag_of(s32);
extern void take_void(void *);
extern void take_header(ObjectNodeHeader *);
extern void take_other(Other *);
extern Actor *actor_ring;
#endif
"""

SOURCE = """#include "x.h"

typedef struct S_80012345_0 {
    u8 pad[0x10];
    union { s32 i; void *p; } unk_10;
} S_80012345_0;

typedef struct S_80012345_1 {
    u8 pad[0x8];
    u8 unk_08;
    u8 unk_09;
    s16 unk_0A;
    signed char unk_0B;
} S_80012345_1;

void walk(Actor *in_actor) {
    void *actor;
    void *slot;

    actor = in_actor;
    slot = actor + 4;
    take_void(slot);
    take_header(actor - 0x20);
    (*(u8 *)((u8 *)actor + 8)) = (*(u8 *)((u8 *)actor + 9));
    ((S_80012345_0 *)actor)->unk_10.i = 0;
    actor = ((S_80012345_0 *)actor)->unk_10.i + 0x20;
}

void disagree(Actor *a, Other *o, s32 k) {
    void *x;

    x = a;
    if (k) {
        x = o;
    }
    (*(s32 *)((u8 *)x + 0)) = 1;
}

void untyped_only(void *p) {
    void *x;

    x = p;
    (*(s32 *)((u8 *)x + 0)) = 1;
}

void mixed(Actor *a, void *p, s32 k) {
    void *x;

    x = a;
    if (k) {
        x = p;
    }
    (*(s32 *)((u8 *)x + 0)) = 1;
}

void header_plus_one(ObjectNodeHeader *h) {
    void *x;

    x = h + 1;
    (*(s32 *)((u8 *)x + 0)) = 1;
}

void reuse(Actor *a) {
    void *x;

    x = a;
    (*(s32 *)((u8 *)x + 0)) = 1;
    x = (void *)(s32)(s16)flag_of(0);
    if (x == 0) {
        take_void(x);
    }
}

void constant(Actor *a) {
    void *x;

    x = a;
    (*(s32 *)((u8 *)x + 0)) = 1;
    x = (void *)0x800E0000;
}

void hidden(Actor *a) {
    void *x;

    x = a;
    (*(s32 *)((u8 *)x + 0)) = 1;
    take_other(x);
}

void body(ObjectNodeHeader *h) {
    void *x;

    x = NODE_BODY(h);
    (*(s32 *)((u8 *)x + 0)) = 1;
}

void cursor(Actor *a) {
    u8 *x;

    x = (u8 *)a;
    x += 4;
    *x = 1;
}

void viewed(Actor *a) {
    S_80012345_1 *v = (S_80012345_1 *)a;

    v->unk_08 = 1;
    v->unk_0A = v->unk_08;
}

void viewed_bad(Actor *a) {
    S_80012345_1 *v = (S_80012345_1 *)a;

    v->unk_0B = 1;
}

void link(void) {
    void *x;

    x = actor_ring;
    (*(s32 *)((u8 *)x + 0)) = 1;
    x = (u8 *)(*(void **)((u8 *)x + 0x10)) + 0x20;
}
"""


class Fixture(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        if not shutil.which('clang'):
            raise unittest.SkipTest('clang not available')
        cls.tmp = Path(tempfile.mkdtemp(prefix='local-type-trial-'))
        (cls.tmp / 'include').mkdir()
        (cls.tmp / 'src').mkdir()
        (cls.tmp / 'include/x.h').write_text(HEADER)
        (cls.tmp / 'src/a.c').write_text(SOURCE)
        cls.unit, err = A.clang_unit(cls.tmp, 'src/a.c')
        assert cls.unit is not None, err
        cls.text = cls.unit.text('src/a.c')
        cls.fns = {fn['name']: fn for _, fn in cls.unit.functions({'src/a.c'})}

    @classmethod
    def tearDownClass(cls):
        shutil.rmtree(cls.tmp, ignore_errors=True)

    def plan(self, name, **kw):
        plans, rows = T.plan_function(self.unit, 'src/a.c', self.fns[name], self.text, **kw)
        return plans, {r['var']: r for r in rows}

    def test_param_source_retypes_and_rewrites_arithmetic(self):
        plans, rows = self.plan('walk', allow_scalar=True)
        self.assertEqual(rows['actor']['record'], 'Actor')
        self.assertEqual(rows['actor']['reason'], '')
        self.assertEqual(rows['actor']['sources'].get('node_link'), 1)
        (p,) = [p for p in plans if p['var'] == 'actor']
        out = T.apply_text(self.text, p['edits'])
        self.assertIn('Actor *actor;', out)
        self.assertIn('slot = (u8 *)actor + 4;', out)
        self.assertIn('take_header(NODE_HEADER(actor));', out)
        # the node link keeps its implicit conversion until the NODE_BODY pass
        self.assertIn('actor = ((S_80012345_0 *)actor)->unk_10.i + 0x20;', out)
        self.assertEqual(rows['slot']['reason'], 'no_typed_source')

    def test_sources_disagree(self):
        _, rows = self.plan('disagree')
        self.assertEqual(rows['x']['reason'], 'sources_disagree')
        self.assertEqual(rows['x']['records'], ['Actor', 'Other'])

    def test_untyped_parameter_source_needs_flag(self):
        _, rows = self.plan('mixed')
        self.assertEqual(rows['x']['reason'], 'untyped_source')
        self.assertEqual(rows['x']['untyped_kinds'], {'name': 1})
        _, rows = self.plan('mixed', allow_untyped=True)
        self.assertEqual(rows['x']['reason'], '')

    def test_untyped_only_is_no_typed_source(self):
        _, rows = self.plan('untyped_only')
        self.assertEqual(rows['x']['reason'], 'no_typed_source')

    def test_scalar_reuse_needs_flag(self):
        plans, rows = self.plan('reuse')
        self.assertEqual(rows['x']['reason'], 'scalar_reuse')
        plans, rows = self.plan('reuse', allow_scalar=True)
        self.assertEqual(rows['x']['reason'], '')
        out = T.apply_text(self.text, plans[0]['edits'])
        self.assertIn('x = (Actor *)(s32)(s16)flag_of(0);', out)

    def test_constant_address_is_refused(self):
        _, rows = self.plan('constant', allow_scalar=True)
        self.assertEqual(rows['x']['reason'], 'constant_address_source')

    def test_hidden_conversion(self):
        _, rows = self.plan('hidden')
        self.assertEqual(rows['x']['reason'], 'implicit_to_other_pointer')
        plans, rows = self.plan('hidden', cast_other=True)
        self.assertEqual(rows['x']['reason'], '')
        out = T.apply_text(self.text, plans[0]['edits'])
        self.assertIn('take_other((Other *)x);', out)
        self.assertEqual(plans[0]['added_casts'], 1)

    def test_node_body_is_not_a_header_source(self):
        _, rows = self.plan('body')
        self.assertEqual(rows['x']['reason'], 'no_typed_source')
        self.assertEqual(rows['x']['sources'], {'untyped': 1})

    def test_typed_pointer_plus_one_is_not_its_record(self):
        _, rows = self.plan('header_plus_one')
        self.assertEqual(rows['x']['reason'], 'no_typed_source')
        self.assertEqual(rows['x']['untyped_kinds'], {'node_body': 1})

    def test_cursor_arithmetic_refused(self):
        _, rows = self.plan('cursor')
        self.assertEqual(rows['x']['reason'], 'cursor_arithmetic')

    def test_view_local_takes_the_source_record(self):
        plans, rows = self.plan('viewed')
        self.assertEqual(rows['v']['reason'], '')
        out = T.apply_text(self.text, plans[0]['edits'])
        self.assertIn('Actor *v = a;', out)
        self.assertIn('v->hp = 1;', out)
        self.assertIn('v->facing = v->hp;', out)
        _, rows = self.plan('viewed_bad')
        self.assertEqual(rows['v']['reason'], 'view_member_unmapped')    # s8 at 0x0C is no Actor member

    def test_union_paths(self):
        self.assertTrue(T.path_crosses_union(self.unit, 'Actor', 'scratch.parts.high'))
        self.assertTrue(T.path_crosses_union(self.unit, 'Actor', 'scratch.value'))
        self.assertFalse(T.path_crosses_union(self.unit, 'Actor', 'max_hp'))
        self.assertFalse(T.path_crosses_union(self.unit, 'Actor', 'next_header'))

    def test_apply_text_rejects_overlap(self):
        with self.assertRaises(ValueError):
            T.apply_text('abcdef', [(0, 3, 'x'), (2, 4, 'y')])
        self.assertEqual(T.apply_text('abcdef', [(0, 1, 'X'), (4, 4, '-')]), 'Xbcd-ef')


class NodeBodyPass(unittest.TestCase):
    """The post-fold pass on a retyped local: header + 0x20 stores become NODE_BODY(header member)."""

    def test_rewrites(self):
        if not shutil.which('clang'):
            self.skipTest('clang not available')
        tmp = Path(tempfile.mkdtemp(prefix='local-type-trial-'))
        try:
            (tmp / 'include').mkdir()
            (tmp / 'src').mkdir()
            (tmp / 'include/x.h').write_text(HEADER)
            (tmp / 'src/a.c').write_text(SOURCE.replace('void *actor;\n    void *slot;',
                                                        'Actor *actor;\n    void *slot;')
                                         .replace('    void *x;\n\n    x = actor_ring;',
                                                  '    Actor *x;\n\n    x = actor_ring;'))
            unit, err = A.clang_unit(tmp, 'src/a.c')
            self.assertIsNotNone(unit, err)
            text = unit.text('src/a.c')
            fns = {fn['name']: fn for _, fn in unit.functions({'src/a.c'})}
            got = []
            for name in ('walk', 'link'):
                for n, _ in A.walk(fns[name]):
                    if n.get('kind') == 'BinaryOperator' and n.get('opcode') == '=' and \
                            A.strip_parens(A.kids(n)[0]).get('kind') == 'DeclRefExpr':
                        r = T.node_body_source(unit, A.kids(n)[1], text)
                        if r:
                            got.append(r)
            spelled = sorted(r[0][2] for r in got)
            self.assertEqual(spelled, ['NODE_BODY(actor->next_header)', 'NODE_BODY(x->next_header)'])
        finally:
            shutil.rmtree(tmp, ignore_errors=True)


if __name__ == '__main__':
    unittest.main()
