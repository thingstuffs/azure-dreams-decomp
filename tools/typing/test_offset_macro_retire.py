"""Lexical parts of offset_macro_retire.py (no clang): macro discovery, use sites, rewrite planning.

    python3 -m unittest tools/typing/test_offset_macro_retire.py
"""
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parent))
import offset_macro_retire as M  # noqa: E402

TEXT = '''#include "common.h"

#define U8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define F(p, t, o) (*(t *)((u8 *)(p) + (o)))
#define SP16(base, off) ((base)->h[(off) / 2])
#define addPrim(ot, p) (setaddr((p), getaddr(ot)), setaddr((ot), (p)))
#define setaddr(p, a) (((P_TAG *)(p))->addr = (u32)(a))
#define getaddr(p) ((u32)(((P_TAG *)(p))->addr))
#define LIMIT 4

void f(ActorRecord *body, u8 *raw)
{
    U8(body, 0x9B) = 1;
    S16(raw, 2) = U8(((u8 *)body), 0x24);
    F(&work, u16, 6) = F(body, s16, 0x2A);
}
'''


def row(span, macro, shape, member, base, leaf=None, cls='direct_field'):
    return {'file': 'src/x.c', 'line': '1', 'use': '', 'span': '%d:%d' % span, 'macro': macro, 'macro_shape': shape,
            'class': cls, 'member': member, 'base_expr': base, 'leaf_expr': leaf if leaf is not None else base}


class Discovery(unittest.TestCase):
    def test_access_macros_and_roles(self):
        access, defs = M.file_macros(TEXT)
        names = [d['name'] for d in access]
        self.assertEqual(names, ['U8', 'S16', 'F', 'SP16', 'addPrim', 'setaddr', 'getaddr'])
        by = {d['name']: d for d in access}
        self.assertEqual(M.shape(by['U8']), 'p_o')
        self.assertEqual(M.shape(by['F']), 'p_t_o')
        self.assertEqual(M.shape(by['SP16']), 'p_o')
        self.assertEqual(M.body_kind(by['SP16']), 'offset')
        self.assertEqual(M.body_kind(by['addPrim'], {'setaddr', 'getaddr'}), 'nested')
        self.assertEqual(M.expanded_casts(by['U8'], access), 2)

    def test_uses_fold_nested_arguments(self):
        access, _ = M.file_macros(TEXT)
        uses = M.file_uses(TEXT, access)
        self.assertEqual([u['macro'] for u in uses], ['U8', 'S16', 'U8', 'F', 'F'])
        self.assertTrue(all(u['function'] == 'f' for u in uses))
        self.assertEqual(uses[2]['args'][0][0], '((u8 *)body)')


class Planner(unittest.TestCase):
    def spans(self):
        access, _ = M.file_macros(TEXT)
        return [(u['start'], u['end']) for u in M.file_uses(TEXT, access)]

    def test_spelling(self):
        self.assertEqual(M.member_spelling('body', 'action_phase'), 'body->action_phase')
        self.assertEqual(M.member_spelling('&work', 'depth'), 'work.depth')
        self.assertEqual(M.member_spelling('a + 1', 'x'), '(a + 1)->x')
        self.assertEqual(M.member_spelling('(o->target)', 'x'), 'o->target->x')
        self.assertEqual(M.base_spelling('((u8 *)body)', 'body'), 'body')
        self.assertIsNone(M.base_spelling('raw', 'body'))

    def test_rewrite_and_definition_removal(self):
        s = self.spans()
        rows = [row(s[0], 'U8', 'p_o', 'action_phase', 'body'),
                row(s[1], 'S16', 'p_o', 'x', 'raw', cls='base_untyped'),
                row(s[2], 'U8', 'p_o', 'tile_x', '((u8 *)body)', leaf='body'),
                row(s[3], 'F', 'p_t_o', 'depth', '&work'),
                row(s[4], 'F', 'p_t_o', 'facing', 'body')]
        new, n, removed, skipped = M.plan_file(TEXT, rows)
        self.assertEqual((n, removed, skipped), (4, 2, []))
        self.assertIn('    body->action_phase = 1;\n', new)
        self.assertIn('    S16(raw, 2) = body->tile_x;\n', new)
        self.assertIn('    work.depth = body->facing;\n', new)
        self.assertNotIn('#define U8', new)
        self.assertNotIn('#define F(', new)
        self.assertIn('#define S16', new)

    def test_refuses_changed_base_and_skips_foreign_leaf(self):
        s = self.spans()
        with self.assertRaises(ValueError):
            M.plan_file(TEXT, [row(s[0], 'U8', 'p_o', 'm', 'other')])
        new, n, removed, skipped = M.plan_file(TEXT, [row(s[1], 'S16', 'p_o', 'm', 'raw', leaf='body')])
        self.assertEqual((new, n, len(skipped)), (TEXT, 0, 1))

    def test_node_header_rows(self):
        text = '#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))\nvoid g(void *e)\n{\n    U16(((u8 *)(e)), -2) |= 1;\n}\n'
        access, _ = M.file_macros(text)
        u = M.file_uses(text, access)[0]
        r = row((u['start'], u['end']), 'U16', 'p_o', 'flags', '((u8 *)(e))', cls='node_header')
        new, n, removed, skipped = M.plan_file(text, [r])
        self.assertEqual(new, 'void g(void *e)\n{\n    NODE_HEADER(e)->flags |= 1;\n}\n')

    def test_drop_unused(self):
        new, n = M.drop_unused(TEXT.replace('    S16(raw, 2) = U8(((u8 *)body), 0x24);\n', ''))
        # S16, SP16, addPrim, then setaddr/getaddr once addPrim is gone; LIMIT is not an access macro
        self.assertEqual(n, 5)
        self.assertNotIn('#define addPrim', new)
        self.assertNotIn('#define getaddr', new)
        self.assertIn('#define LIMIT 4', new)


if __name__ == '__main__':
    unittest.main()
