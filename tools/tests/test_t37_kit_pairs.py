"""T37, round-72 KIT additions: the same-width de-register and the paired unpinned retype (textual only)."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t37_localwidth as M  # noqa: E402
from pin_census import sites_of, unscored_text  # noqa: E402

PAIR = '''#include "common.h"
void f(void *entity, S *motion) {
    register s32 direction_copy ASM_REG("$21");
    s32 direction_index;
    u32 height_bits;
    s16 old_direction;

    direction_copy = (*(s16 *)((u8 *)entity + 0x2A)) >> 9;
    ASM_KEEP(direction_copy);
    direction_index = direction_copy;
    old_direction = (s16)direction_index;
    height_bits = motion->unk_14;
    motion->unk_14 = height_bits | 0x40;
    motion->unk_0A = old_direction + direction_index;
}
'''


class TestSameWidth(unittest.TestCase):
    def test_the_base_menu_still_never_offers_the_local_its_own_width(self):
        labels = [l for l, _t in M.candidates(PAIR)]
        self.assertTrue(labels)
        self.assertNotIn("localwidth:direction_copy:s32>s32", labels)
        self.assertIn("localwidth:direction_copy:s32>s16", labels)

    def test_the_kit_menu_offers_the_de_register_at_the_same_width(self):
        hit = dict(M.kit_candidates(PAIR)).get("localwidth:direction_copy:s32>keep")
        self.assertIsNotNone(hit)
        self.assertIn("s32 direction_copy;", hit)
        self.assertNotIn("ASM_REG", hit)
        self.assertNotIn("ASM_KEEP(direction_copy)", hit)
        self.assertLess(len(sites_of(hit)), len(sites_of(PAIR)))


class TestPartners(unittest.TestCase):
    def test_only_unpinned_integer_locals_are_partners(self):
        names = [u for u, _ty in M.partners(PAIR, "direction_copy")]
        self.assertIn("direction_index", names)
        self.assertNotIn("direction_copy", names)

    def test_a_statement_sharing_the_pinned_local_ranks_first(self):
        self.assertEqual(M.partners(PAIR, "direction_copy")[0][0], "direction_index")

    def test_a_pair_retypes_both_and_erases_only_the_pinned_one(self):
        # with one pinned local the per-host and all-hosts de-registers are the same text, so the
        # pair is labelled from the joint one
        hit = dict(M.kit_candidates(PAIR)).get("pair:all>keep+direction_index:s32>s16")
        self.assertIsNotNone(hit)
        self.assertIn("s32 direction_copy;", hit)
        self.assertIn("s16 direction_index;", hit)
        self.assertNotIn("ASM_KEEP", hit)

    def test_every_kit_candidate_is_scored_the_same_way(self):
        sig = unscored_text(PAIR)
        for label, t in M.kit_candidates(PAIR):
            self.assertEqual(unscored_text(t), sig, label)
        self.assertLessEqual(len(M.kit_candidates(PAIR)), M.MAX_PAIRS)


if __name__ == "__main__":
    unittest.main()
