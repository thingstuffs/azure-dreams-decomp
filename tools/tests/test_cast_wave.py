"""Pointer-cast wave tools: exact member folds, one-view local retypes, view census decisions."""
from pathlib import Path
import shutil
import sys
import tempfile
import unittest

TOOLS = Path(__file__).resolve().parents[1]
sys.path[:0] = [str(TOOLS / 'typing'), str(TOOLS), str(TOOLS / 'lint')]
import cast_fold as F  # noqa: E402
import cast_wave as W  # noqa: E402
import view_swap as V  # noqa: E402

HEADER = '''
typedef unsigned char u8; typedef signed char s8; typedef short s16; typedef unsigned short u16;
typedef int s32; typedef unsigned int u32;
typedef struct Pos { s16 x; s16 y; s16 z; u16 pad; } Pos;
typedef struct Thing {
    u16 flags;
    s16 speed;
    Pos pos;
    union { s16 s; u16 u; } angle;
    u8 pad_0E[2];
    void *table;
    u8 *frames;
    s32 hp:8;
    s16 list[3];
} Thing;
'''


def fold(text, name='a.c'):
    with tempfile.TemporaryDirectory(prefix='cast-fold-') as temp:
        root = Path(temp)
        (root / 'include/shared').mkdir(parents=True)
        (root / 'include/shared/thing.h').write_text(HEADER)
        (root / 'src').mkdir()
        (root / 'src' / name).write_text(text)
        res = F.scan_tu((str(root), 'src/' + name, None, ['src/' + name], True))
        edits = F.select_edits(res['sites'])
        F.apply_edits(root, edits)
        return (root / 'src' / name).read_text(), res


def retype(text):
    with tempfile.TemporaryDirectory(prefix='view-retype-') as temp:
        root = Path(temp)
        (root / 'include/shared').mkdir(parents=True)
        (root / 'include/shared/thing.h').write_text(HEADER)
        (root / 'src').mkdir()
        (root / 'src/a.c').write_text(text)
        res = V.retype_tu((str(root), 'src/a.c', None, ['src/a.c']))
        V.apply_plans(root, res['plans'])
        return (root / 'src/a.c').read_text(), res


@unittest.skipUnless(shutil.which('clang'), 'clang required')
class FoldTest(unittest.TestCase):
    def test_exact_members_fold(self):
        out, res = fold('''#include "shared/thing.h"
s32 use(Thing *t, Thing obj) {
    s32 a = *(s16 *)((u8 *)t + 2);
    a += (*(s16 *)((u8 *)t + 8));
    a += *(u16 *)((char *)t + 0xC);
    a += ((u8 *)t)[0x16];
    a += *((s16 *)t + 14);
    a += *(s16 *)((u8 *)&obj + 6);
    return a + *(u16 *)t;
}
''')
        self.assertIn('a = t->speed;', out)
        self.assertIn('a += t->pos.z;', out)
        self.assertIn('a += t->angle.u;', out)
        self.assertIn('a += t->list[1];', out)
        self.assertIn('obj.pos.y', out)
        self.assertIn('return a + t->flags;', out)
        # ((u8 *)t)[0x16] is inside the frames pointer: no u8 member there.
        self.assertIn('((u8 *)t)[0x16]', out)

    def test_refusals(self):
        out, res = fold('''#include "shared/thing.h"
#define GET(p, o) (*(s16 *)((u8 *)(p) + (o)))
s32 use(Thing *t, void *raw) {
    s32 a = *(u16 *)((u8 *)t + 2);    /* read of s16 speed as u16: refused */
    a += *(s16 *)((u8 *)raw + 2);     /* untyped base */
    a += GET(t, 2);                   /* macro */
    a += *(s16 *)((u8 *)t + 0xE);     /* padding */
    a += *(u8 **)((u8 *)t + 0x10);    /* void * member read as u8 * */
    a += *(s16 *)((u8 *)t - 2);       /* before the object */
    return a;
}
''')
        self.assertEqual(res['sites'], [])
        reasons = res['refused']['src/a.c']
        for why in ('signedness_differs', 'base_void_pointer', 'macro', 'no_member_at_offset',
                    'pointer_type_differs', 'negative_offset'):
            self.assertIn(why, reasons)

    def test_store_by_width_and_pointer_store(self):
        out, _ = fold('''#include "shared/thing.h"
extern u8 frames[];
void set(Thing *t, s32 v) {
    *(u16 *)((u8 *)t + 2) = v;
    *(void **)((u8 *)t + 0x14) = frames;
    v = *(u16 *)((u8 *)t + 2) = 3;
}
''')
        self.assertIn('t->speed = v;', out)
        self.assertIn('t->frames = frames;', out)
        # The assignment's value is used: the exact type is required.
        self.assertIn('v = *(u16 *)((u8 *)t + 2) = 3;', out)

    def test_view_cast_over_typed_base(self):
        out, res = fold('''#include "shared/thing.h"
typedef struct S_80010000_0 { u8 pad[2]; s16 unk_02; u8 pad2[8]; union { s16 s; u16 u; } unk_0C; } S_80010000_0;
s32 use(Thing *t, void *raw) {
    ((S_80010000_0 *)t)->unk_0C.u = 1;
    return ((S_80010000_0 *)t)->unk_02 + ((S_80010000_0 *)raw)->unk_02 + ((S_80010000_0 *)((u8 *)t + 4))->unk_02;
}
''')
        self.assertIn('t->angle.u = 1;', out)
        self.assertIn('return t->speed + ((S_80010000_0 *)raw)->unk_02 + t->pos.y;', out)
        self.assertIn('view:base_void_pointer', res['refused']['src/a.c'])

    def test_nested_sites_fold_in_passes(self):
        text = '''#include "shared/thing.h"
typedef struct Holder { Thing *thing; } Holder;
s32 use(Holder *h) { return *(s16 *)((u8 *)*(Thing **)h + 2); }
'''
        out, _ = fold(text)
        self.assertIn('*(s16 *)((u8 *)h->thing + 2)', out)
        out, _ = fold(out)
        self.assertIn('return h->thing->speed;', out)


@unittest.skipUnless(shutil.which('clang'), 'clang required')
class RetypeTest(unittest.TestCase):
    def test_one_view_local(self):
        out, res = retype('''#include "shared/thing.h"
typedef struct S_80010000_0 { u8 pad[2]; s16 unk_02; } S_80010000_0;
extern void take(void *);
extern u8 *source(void);
s32 use(void *object, u8 *base) {
    u8 *view = object;
    u8 *next;
    void *other;
    next = (u8 *)base + 0x20;
    ((S_80010000_0 *)view)->unk_02 = 1;
    take(view);
    ((S_80010000_0 *)next)->unk_02 = 2;
    ((S_80010000_0 *)next)->unk_02 += 3;
    other = source();
    ((S_80010000_0 *)other)->unk_02 = 4;
    other = (u8 *)other + 4;
    return ((S_80010000_0 *)object)->unk_02;
}
''')
        self.assertIn('S_80010000_0 *view = object;', out)
        self.assertIn('view->unk_02 = 1;', out)
        self.assertIn('take(view);', out)
        self.assertIn('S_80010000_0 *next;', out)
        self.assertIn('next = (S_80010000_0 *)((u8 *)base + 0x20);', out)
        self.assertIn('next->unk_02 += 3;', out)
        # `other` would need two new casts to drop one: refused.
        self.assertIn('void *other;', out)
        # Parameters are counted, never retyped.
        self.assertIn('((S_80010000_0 *)object)->unk_02', out)
        pool = res['pool']['src/a.c']
        self.assertTrue(any(k.startswith('parameter:') for k in pool))

    def test_two_views_merge_or_refuse(self):
        out, res = retype('''#include "shared/thing.h"
typedef struct S_80010000_0 { u8 pad[2]; s16 unk_02; } S_80010000_0;
typedef struct S_80010000_1 { u8 pad[2]; s16 field_02; s16 unk_04; } S_80010000_1;
typedef struct S_80010000_2 { u8 pad[2]; u16 unk_02; } S_80010000_2;
s32 use(void *object) {
    void *p = object;
    void *q = object;
    s32 a = ((S_80010000_0 *)p)->unk_02 + ((S_80010000_1 *)p)->unk_04;
    return a + ((S_80010000_2 *)q)->unk_02 + ((S_80010000_1 *)q)->unk_04;
}
''')
        # p: S_80010000_0's unk_02 is S_80010000_1's field_02 (same offset and type).
        self.assertIn('S_80010000_1 *p = object;', out)
        self.assertIn('p->field_02 + p->unk_04', out)
        # q: the u16 view does not match the s16 member: refused.
        self.assertIn('void *q = object;', out)
        self.assertIn('local_refused:several_record_types', res['pool']['src/a.c'])


class CensusDecisionTest(unittest.TestCase):
    SHARED = {
        'Thing': {'size': 0x20, 'leaves': {'2': [['speed', 'short', 2]], '10': [['angle.s', 'short', 2],
                                                                                ['angle.u', 'unsigned short', 2]]}},
        'Other': {'size': 0x10, 'leaves': {'2': [['b', 'short', 2]]}},
        'Raw': {'size': 0x40, 'raw': True, 'leaves': {'2': [['h[1]', 'short', 2], ['uh[1]', 'unsigned short', 2]]}},
    }

    def view(self, fields, evidence=None):
        return {'fields': fields, 'evidence': evidence or {}, 'arith': False, 'size': 4}

    def test_evidenced_ambiguous_incompatible(self):
        f = {'0x2': {'types': {'short': 's16'}, 'rw': ['r'], 'names': ['unk_02']}}
        self.assertEqual(V.decide(self.view(f), self.SHARED)['decision'], 'ambiguous')
        d = V.decide(self.view(f, {'Thing': 2}), self.SHARED)
        self.assertEqual((d['decision'], d['shared'], d['mapping']), ('evidenced', 'Thing', {'0x2': 'speed'}))
        g = {'0xa': {'types': {'unsigned short': 'u16'}, 'rw': ['r'], 'names': ['unk_0A']}}
        self.assertEqual(V.decide(self.view(g), self.SHARED)['shared'], 'Thing')
        bad = {'0x2': {'types': {'unsigned short': 'u16'}, 'rw': ['r'], 'names': ['unk_02']}}
        self.assertEqual(V.decide(self.view(bad, {'Other': 1}), self.SHARED)['decision'], 'incompatible')
        store = {'0x2': {'types': {'unsigned short': 'u16'}, 'rw': ['w'], 'names': ['unk_02']}}
        self.assertEqual(V.decide(self.view(store, {'Other': 1}), self.SHARED)['decision'], 'evidenced')


class DebtTest(unittest.TestCase):
    def test_debt_rise_detected(self):
        before = 'void f(void *p) { ((int *)p)[0] = 1; }\n'
        after = 'void f(void *p) { ((int *)p)[0] = 1; *(short *)(char *)p = 2; }\n'
        self.assertEqual(W.debt_rises('src/a.c', before, after), ['f#1'])
        self.assertEqual(W.debt_rises('src/a.c', after, before), [])


if __name__ == '__main__':
    unittest.main()
