"""cast_census: classification of pointer casts on a small clang-parsed TU (needs clang).

Run from a repository root (tools/typing on the path), or from the lane with ALIAS_TEST_ROOT=<root>."""
import os
from pathlib import Path
import sys
import tempfile
import unittest

HERE = Path(__file__).resolve().parent
ROOT = Path(os.environ.get('ALIAS_TEST_ROOT', HERE.parents[1]))
for p in (HERE, ROOT / 'tools' / 'typing', ROOT / 'tools'):
    sys.path.insert(0, str(p))

import cast_census as K  # noqa: E402

COMMON = ('typedef unsigned char u8; typedef signed char s8; typedef unsigned short u16; typedef short s16;\n'
          'typedef unsigned int u32; typedef int s32;\n')

SOURCE = '''#include "common.h"
typedef struct Rec { s32 a; s16 b; u8 pad_06[0x2]; s32 c; } Rec;
typedef struct S_80001000_0 { u8 pad_00[0x4]; s16 unk_04; } S_80001000_0;
#define AT(p, k) (*(s16 *)((u8 *)(p) + (k)))
void callee(void *p);
void f(Rec *r, void *v, Rec *same) {
    *(s32 *)((u8 *)r + 8) = 1;
    *(s16 *)((u8 *)r + 6) = 2;
    *(s16 *)((u8 *)v + 4) = 3;
    ((S_80001000_0 *)v)->unk_04 = 4;
    callee((u8 *)f + 0x10);
    ((Rec *)same)->a = 5;
    callee((void *)AT(v, 2));
    (void)*((s16 *)((u8 *)v + 2));
}
'''


class CensusTests(unittest.TestCase):
    def test_classes(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'include').mkdir()
            (root / 'include/common.h').write_text(COMMON)
            (root / 'src').mkdir()
            (root / 'src/t.c').write_text(SOURCE)
            res = K.scan_tu((str(root), 'src/t.c', None, ['src/t.c']))
        self.assertIsNone(res['error'])
        by_line = {}
        for r in res['rows']:
            by_line.setdefault(r['line'], []).append((r['cls'], r['sub']))
        self.assertEqual(by_line[7], [('n', 'fold_now')] * 2)            # exact member c at 8
        self.assertEqual(by_line[8], [('b', 'pad_member')] * 2)          # pad_06 at 6
        self.assertEqual(by_line[9], [('a', 'void')] * 2)                # raw offset on void *
        self.assertEqual(by_line[10], [('c', 'generated_view_untyped_base')])
        self.assertEqual(by_line[11], [('e', 'function_pointer')])       # mid-function address
        self.assertEqual(by_line[12], [('n', 'redundant')])              # view of its own record
        self.assertTrue(all(c == 'd' for c, s in by_line[13] if s.startswith('macro')))


if __name__ == '__main__':
    unittest.main()
