"""T116: the OT-link detection and the P_TAG spelling are textual; the screen and `vf` are not run."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t116_ptaglink as M  # noqa: E402
from pin_census import sites_of  # noqa: E402

ROW = '''#include "common.h"
void f(u8 *prim, Scratch *scratch) {
    register u32 addr_mask ASM_REG("$18") = 0x00FFFFFF;   /* UNRESOLVED C shape (pin) */
    u32 tag_mask = 0xFF000000;

    *(u32 *)prim = (*(u32 *)prim & tag_mask) |
        (scratch->ot[scratch->index] & addr_mask);
    {
        u32 ot_word;

        ot_word = scratch->ot[scratch->index];
        scratch->ot[scratch->index] = (ot_word & tag_mask) |
            ((s32)prim & addr_mask);
    }
}
'''


class TestLinks(unittest.TestCase):
    def test_both_links_are_found_the_copy_form_too(self):
        fn = M.functions(ROW)[0]
        ls = M.links(ROW, fn[2], fn[3], ["addr_mask"], ["tag_mask"])
        self.assertEqual([(l[3], l[4]) for l in ls],
                         [("*(u32 *)prim", "scratch->ot[scratch->index]"), ("scratch->ot[scratch->index]", "(s32)prim")])

    def test_joint_spelling_uses_the_bitfield_and_drops_the_pin(self):
        c = dict(M.candidates(ROW))["f:all2:plain"]
        self.assertIn("((P_TAG *)&*(u32 *)prim)->addr = ((P_TAG *)&scratch->ot[scratch->index])->addr;", c)
        self.assertIn("((P_TAG *)&scratch->ot[scratch->index])->addr = (u32)((s32)prim);", c)
        self.assertNotIn("ot_word = scratch", c)
        self.assertIn("} P_TAG;", c)
        self.assertEqual(sites_of(c), [])

    def test_no_pinned_mask_is_refused(self):
        t = ROW.replace('register u32 addr_mask ASM_REG("$18")', "u32 addr_mask").replace(
            "   /* UNRESOLVED C shape (pin) */", "") + "void g(void) { ASM_SCHED_BARRIER(); }\n"
        self.assertEqual(M.T.eligible(t, None, {}), "no pinned 0x00FFFFFF/0xFF000000 mask local")


if __name__ == "__main__":
    unittest.main()
