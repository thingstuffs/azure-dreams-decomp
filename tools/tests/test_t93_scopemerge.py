"""T93: donee/donor scanning and the rename are textual; the screen and `vf` are not exercised."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t93_scopemerge as M  # noqa: E402
from pin_census import sites_of  # noqa: E402

T = '''#include "common.h"
void f(void *sequence, s32 state) {
    s32 result;
    switch (state) {
        register void *object_m ASM_REG("$16");
        register s32 object_index_m ASM_REG("$17");
    case 2:
        {
            register s32 object_index ASM_REG("$17") = 0;
            u32 mask = 0x20000000;
            void *object_slot = sequence;
            do {
                object_m = ((S *)object_slot)->unk_AC;
                object_index++;
                object_slot = (u8 *)object_slot + 4;
            } while (object_index < 2);
        }
        break;
    case 3:
        {
            register s32 object_index ASM_REG("$17") = 0;
            do {
                object_index++;
            } while (object_index < 2);
        }
        break;
    }
    result = object_index_m;
}
'''

NOINIT = '''#include "common.h"
void g(void *packet, u32 uv_right) {
    register u32 coord_value;
    u32 other;
    coord_value = 1;
    other = coord_value;
    if (other != 0) {
        register u32 uv_adjusted ASM_REG("$2");
        uv_adjusted = uv_right - 1;
        ((S *)packet)->unk_14 = uv_adjusted;
    }
}
'''

CLASH = '''#include "common.h"
void h(void *packet, u32 uv_right) {
    register u32 coord_value;
    if (uv_right != 0) {
        register u32 uv_adjusted ASM_REG("$2");
        uv_adjusted = uv_right - 1;
        coord_value = uv_adjusted;
        ((S *)packet)->unk_14 = coord_value;
    }
}
'''


class Scan(unittest.TestCase):
    def test_nested_declarations_only(self):
        ds = M.donees(T)
        names = [(d["v"], bool(d["init"])) for d in ds]
        self.assertIn(("object_index", True), names)
        self.assertEqual(names.count(("object_index", True)), 2)     # one per sibling block
        # the switch block's own declarations are nested blocks too, so they are scanned as well
        self.assertEqual([d["v"] for d in ds if M.donors(T, d)].count("object_index"), 2)
        self.assertNotIn("object_m", [d["v"] for d in ds if M.donors(T, d)])   # no free void * outside

    def test_a_donor_alive_in_the_block_is_refused(self):
        d = M.donees(CLASH)[0]
        self.assertNotIn("coord_value", M.donors(CLASH, d))
        self.assertEqual(M.T.eligible(CLASH, None, {}), "no enclosing local free over the block")

    def test_donor_of_the_same_type_outside_the_block(self):
        d = M.donees(NOINIT)[0]
        self.assertIn("coord_value", M.donors(NOINIT, d))


class Merge(unittest.TestCase):
    def test_initialiser_block_keeps_program_order(self):
        new = dict(M.candidates(T))["object_index->object_index_m@9:rename"]
        body = new.split("case 2:")[1].split("break;")[0]
        self.assertIn("u32 mask;", body)
        self.assertIn("void *object_slot;", body)
        self.assertLess(body.index("object_index_m = 0;"), body.index("mask = 0x20000000;"))
        self.assertLess(body.index("mask = 0x20000000;"), body.index("object_slot = sequence;"))
        self.assertNotIn("register s32 object_index ASM_REG", body)
        # the SIBLING block keeps its own declaration: the donee is keyed by its span, not its name
        other = new.split("case 3:")[1]
        self.assertIn('register s32 object_index ASM_REG("$17") = 0;', other)

    def test_joint_form_takes_both_blocks(self):
        new = dict(M.candidates(T))["object_index->object_index_m@x2:rename"]
        self.assertNotIn('register s32 object_index ASM_REG("$17")', new)
        self.assertEqual(len(sites_of(new)), len(sites_of(T)) - 2)

    def test_plain_rename_without_initialiser(self):
        new = dict(M.candidates(NOINIT))["uv_adjusted->coord_value@8:rename"]
        self.assertNotIn("uv_adjusted", new)
        self.assertIn("coord_value = uv_right - 1;", new)
        self.assertEqual(len(sites_of(new)), len(sites_of(NOINIT)) - 1)


if __name__ == "__main__":
    unittest.main()
