"""T93, round-71 KIT additions: a plain declaration pinned by a keep statement, and a cross-width donor."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t93_scopemerge as M  # noqa: E402

PLAIN = '''#include "common.h"
void f(void *actor, void **sprite) {
    u32 fall_anim;
    s32 world_coord;
    void *animation_table;

    world_coord = 0;
    {
        s32 fall_duration;
        fall_duration = 0x10;
        ASM_KEEP_NV(fall_duration);
        animation_table = (void *)actor;
        *(s32 *)((u8 *)actor + 0x96) = fall_duration;
    }
    fall_anim = (u32)animation_table + world_coord;
    *sprite = (void *)fall_anim;
}
'''

PTR = '''#include "common.h"
void g(void *actor, void **out) {
    s32 direction;
    u8 *host;

    direction = 0;
    {
        u8 *copy_dest;
        copy_dest = (u8 *)actor + 0x94;
        ASM_KEEP(copy_dest);
        *out = copy_dest;
    }
    host = (u8 *)direction;
    *out = host;
}
'''


class PlainDonee(unittest.TestCase):
    def test_a_plain_declaration_with_a_keep_in_its_block_is_a_donee(self):
        ds = M.donees(PLAIN)
        self.assertEqual([(d["v"], d["ty"], d["reg"]) for d in ds], [("fall_duration", "s32", False)])

    def test_an_integer_donor_of_another_width_is_offered(self):
        d = M.donees(PLAIN)[0]
        names = M.donors(PLAIN, d)
        self.assertIn("world_coord", names)                     # same type, offered first
        self.assertIn("fall_anim", names)                       # u32 against the donee's s32
        self.assertLess(names.index("world_coord"), names.index("fall_anim"))

    def test_the_merge_hands_the_keep_to_the_donor_and_the_erase_plan_takes_it(self):
        by = dict(M.candidates(PLAIN))
        cand = by["fall_duration->fall_anim@9:erase"]
        self.assertIn("fall_anim = 0x10;", cand)
        self.assertNotIn("fall_duration", cand)
        self.assertNotIn("ASM_KEEP_NV", cand)


class PointerDonee(unittest.TestCase):
    def test_a_pointer_donee_still_needs_its_donors_exact_type(self):
        d = next(x for x in M.donees(PTR) if x["v"] == "copy_dest")
        self.assertNotIn("direction", M.donors(PTR, d))          # s32 against u8 *: not offered


if __name__ == "__main__":
    unittest.main()
