"""retype_family: raw-spelling parser, per-variable refusals and the rewrite text (no compiler needed)."""
from pathlib import Path
import sys
import unittest

TOOLS = Path(__file__).resolve().parents[1]
sys.path[:0] = [str(TOOLS / 'typing'), str(TOOLS)]
import retype_family as R

FAM = {'type': 'SpriteFrameState', 'header': 'shared/sprite_frame_state.h', 'labels': ['X'],
       'fields': {'0xc:4': 'color.word:s', '0x12:2': 'clut:u', '0x14:2': 'flags:u', '0x1c:2': 'scale_x:u',
                  '0x2c:4': 'frameTable:p'},
       'constants': {'scale_x': {'0x1000': 'ONE'}}}

TEXT = '''#include "common.h"
void make(void *node, void *arg)
{
    void *part;
    u8 *walk;
    part = *((void **) (((u8 *) node) + 0xC));
    *((s16 *) (((u8 *) part) + 0x1C)) = 0x1000;
    (*(s32 *)((u8 *)part + 0xC)) = 0x80FF;
    *((u16 *) (((u8 *) part) + 0x12)) -= 0x80;
    x = *((s16 *) (((u8 *) part) + 0x12));
    walk = *((u8 **) (((u8 *) part) + 0x2C));
    *((u16 *) (((u8 *) walk) + 0x14)) |= 0xC;
    walk += 4;
    *((u16 *) (((u8 *) arg) + 0x14)) |= 0xC;
}
'''


def site(line, off, width, sign, rw, base):
    return {'line': line, 'off': off, 'width': width, 'sign': sign, 'rw': rw, 'base': base}


class ParserTest(unittest.TestCase):
    def test_spellings(self):
        self.assertEqual(R.find_raw('*((s32 *) (((u8 *) p) + 0x28)) = 1;', 'p'), [(0, 30, None, 0x28, 'raw_cast')])
        # outer parentheses are swallowed, `void * *` and a zero offset parse
        self.assertEqual(R.find_raw('  (*(void * *)((u8 *)p + 0)) = t;', 'p'), [(2, 28, None, 0, 'raw_cast')])
        self.assertEqual(R.find_raw('y = *((u16 *) (((u8 *) p) + (-2)));', 'p')[0][3], -2)
        self.assertEqual(R.find_raw('F(p, u16, 0x14) |= 1;', 'p'), [(0, 15, 'u16', 0x14, 'F_macro')])
        self.assertEqual(R.find_raw('a = b * (p);', 'p'), [])           # multiplication, not a deref
        self.assertEqual(R.find_raw('*((s32 *) (((u8 *) q) + 4)) = 0;', 'p'), [])

    def test_nested_void_cast_and_byte_address(self):
        line = '(*(u8 *)((u8 *)((void *)part_data) + 0x25)) = held;'
        self.assertEqual(R.find_raw(line, 'part_data')[0][3], 0x25)
        self.assertEqual(R.parse_byte_address('((s8 *) (p)) + (0x12)'), ('p', 0x12))
        self.assertEqual(R.parse_byte_address('((u8 *)((void *)p)) - 2'), ('p', -2))
        self.assertIsNone(R.parse_byte_address('((s16 *)p) + 2'))
        self.assertIsNone(R.parse_byte_address('(u8 *)p + i'))


class PlanTest(unittest.TestCase):
    def plan(self, sites):
        span = R.func_span(TEXT, 'make')
        return R.plan_function(TEXT, span, 'make', sites, FAM)

    def test_rewrite_with_sign_rule_and_constant(self):
        sites = [site(7, 0x1C, 2, 's', 'w', 'part'), site(8, 0xC, 4, 's', 'w', 'part'),
                 site(9, 0x12, 2, 'u', 'rw', 'part'), site(10, 0x12, 2, 's', 'r', 'part'),
                 site(11, 0x2C, 4, 'p', 'r', 'part')]
        plans, refusals = self.plan(sites)
        self.assertEqual([p[0] for p in plans], ['part'])
        out = R.apply_plans(TEXT, R.func_span(TEXT, 'make'), plans, FAM)
        self.assertIn('    SpriteFrameState *part;', out)
        self.assertIn('    part->scale_x = ONE;', out)                   # store: no cast, named constant
        self.assertIn('    part->color.word = 0x80FF;', out)
        self.assertIn('    part->clut -= 0x80;', out)                    # u16 RMW on a u16 field
        self.assertIn('    x = *(s16 *)&part->clut;', out)               # minority signed load keeps lh
        self.assertIn('    walk = part->frameTable;', out)

    def test_refusals(self):
        sites = [site(12, 0x14, 2, 'u', 'rw', 'walk'), site(14, 0x14, 2, 'u', 'rw', 'arg'),
                 site(7, 0x1C, 2, 's', 'w', 'part')]
        plans, refusals = self.plan(sites)
        why = dict(refusals)
        self.assertEqual(why['walk'], 'byte_pointer_use')               # walk += 4 scales differently once typed
        self.assertEqual(why['arg'], 'parameter')
        self.assertTrue(why['part'].startswith('non_family_site'))      # +0xC store not in the family sites given

    def test_unmapped_field(self):
        plans, refusals = self.plan([site(7, 0x1C, 4, 's', 'w', 'part')])
        self.assertEqual(refusals, [('part', 'unmapped_field:0x1c:4')])


if __name__ == '__main__':
    unittest.main()
