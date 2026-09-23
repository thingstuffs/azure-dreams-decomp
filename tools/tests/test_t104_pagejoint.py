"""T104: the joint page rewrite, the field fold and the pin plans are textual; the screen and `vf` are not run."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t104_pagejoint as M  # noqa: E402
from pin_census import sites_of, unscored_text  # noqa: E402

ROW = '''#include "common.h"
typedef struct S_1 {
    u8 pad[0x438];
    union { M2C_UNK (*s)(); s32 u; } unk_438;
} S_1;
extern M2C_UNK D_80097D54;
extern s32 D_800D0438;
void f(u8 *state) {
    u8 *callback_page;
    M2C_UNK (*callback)();
    {
        u8 *handler_page;

        handler_page = (u8 *)0x80090000;
        ASM_KEEP(handler_page);
        callback_page = (u8 *)0x800D0000;
        callback = ((S_1 *)callback_page)->unk_438.s;
        ASM_SCHED_BARRIER();
        *(M2C_UNK **)(state + 0x14) = (M2C_UNK *)(handler_page + 0x7D54);
        if (callback != NULL) {
            callback();
            ((S_1 *)callback_page)->unk_438.u = 0;
        }
    }
}
'''

ONE_PAGE = ROW.replace("callback_page = (u8 *)0x800D0000;", "callback_page = state;")


class TestDetection(unittest.TestCase):
    def test_a_pinned_and_an_unpinned_page_are_eligible(self):
        self.assertEqual(M.page_vars(ROW), (["handler_page"], ["callback_page"]))
        self.assertIsNone(M.T.eligible(ROW, None, {}))

    def test_a_lone_pinned_page_is_t29s_and_refuses(self):
        self.assertEqual(M.T.eligible(ONE_PAGE, None, {}), "no unpinned page local beside the pinned one")


class TestRewrite(unittest.TestCase):
    def setUp(self):
        self.menu = dict(M.candidates(ROW))

    def test_both_pages_go_together(self):
        (label, jt), = M.joint_texts(ROW)
        self.assertEqual(label, "handler_page+callback_page")
        self.assertNotIn("handler_page", jt)
        self.assertNotIn("callback_page", jt)
        self.assertIn("&D_80097D54", jt)

    def test_the_field_is_folded_to_its_own_symbol(self):
        c = self.menu["handler_page+callback_page:typeof:win"]
        self.assertIn("callback = (*(__typeof__(((S_1 *)0)->unk_438.s) *)&D_800D0438);", c)
        self.assertIn("(*(__typeof__(((S_1 *)0)->unk_438.u) *)&D_800D0438) = 0;", c)
        self.assertNotIn("D_800D0000", c)                    # the page symbol t29 named is dropped
        self.assertEqual(sites_of(c), [])

    def test_the_bare_form_writes_the_declared_scalar(self):
        c = self.menu["handler_page+callback_page:bare:none"]
        self.assertIn("D_800D0438 = 0;", c)
        self.assertIn("callback = ((__typeof__(((S_1 *)0)->unk_438.s))D_800D0438);", c)
        self.assertIn("ASM_SCHED_BARRIER();", c)              # the `none` plan keeps the window's pins

    def test_every_candidate_keeps_the_unscored_arms_and_drops_a_pin(self):
        for c in self.menu.values():
            self.assertEqual(unscored_text(c), unscored_text(ROW))
            self.assertLess(len(sites_of(c)), len(sites_of(ROW)))


if __name__ == "__main__":
    unittest.main()
