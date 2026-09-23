"""T110: parameter groups, carrier fold/retype and the declaration retype are textual; no screen, no `vf`."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t110_paramfold as M  # noqa: E402
from pin_census import sites_of  # noqa: E402

FOLD = '''#include "common.h"
void func_80172CC8(void *origin, s32 x_offset, s32 y_offset, s32 variant);
void func_80172CC8(void *origin, s32 x_offset, s32 y_offset, s32 variant) {
    void *node;
    register s32 variant_flag ASM_REG("$21");

    variant_flag = variant;
    node = func_8003FC64(0x212);
    if (node != 0) {
        *(s16 *)node = x_offset + y_offset;
        if ((variant_flag << 0x10) == 0) {
            func_8003DB94(node, 0);
        }
        ASM_KEEP(variant_flag);
    }
}
'''

WIDEN = '''#include "common.h"
#define BODY_NAME func_8016A8A8
void *BODY_NAME(s16 flags, s8 grid_x, s8 grid_y, s16 part);
void *BODY_NAME(s16 flags, s8 grid_x, s8 grid_y, s16 part) {
    s8 saved_x;
    s8 saved_y;
    register void *obj ASM_REG("$4");

    saved_x = grid_x;
    ASM_KEEP_NV(saved_x);
    saved_y = grid_y;
    ASM_KEEP_NV(saved_y);
    obj = func_8003FD64(0x112, 0);
    ((u8 *)obj)[0x24] = saved_x;
    ((u8 *)obj)[0x25] = saved_y;
    return obj;
}
'''


class TestGroups(unittest.TestCase):
    def test_the_pinned_carrier_reaches_its_formal(self):
        fname, params, b0, b1 = M.functions(FOLD)[0]
        self.assertEqual(M.carriers(FOLD, "variant", b0, b1), ["variant_flag"])
        mine = [s for s in sites_of(FOLD) if b0 < s[3] < b1]
        self.assertEqual(dict(M.groups(FOLD, params, b0, b1, mine))["reach"], [3])


class TestRewrite(unittest.TestCase):
    def test_fold_drops_the_carrier_and_retypes_every_declaration(self):
        c = dict(M.candidates(FOLD))["func_80172CC8:all=s16:fold:all"]
        self.assertEqual(sites_of(c), [])
        self.assertNotIn("variant_flag", c)
        self.assertIn("if ((variant << 0x10) == 0)", c)
        self.assertEqual(c.count("(void *origin, s16 x_offset, s16 y_offset, s16 variant)"), 2)

    def test_retype16_keeps_the_carriers_and_the_unnamed_register_pin(self):
        c = dict(M.candidates(WIDEN))["BODY_NAME:reach=s32:retype16:named"]
        self.assertIn("    s16 saved_x;", c)
        self.assertIn('register void *obj ASM_REG("$4");', c)
        self.assertEqual(c.count("(s16 flags, s32 grid_x, s32 grid_y, s16 part)"), 2)
        self.assertEqual(len(sites_of(c)), 1)


if __name__ == "__main__":
    unittest.main()
