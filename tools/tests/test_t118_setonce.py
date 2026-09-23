"""T118: the set-once chain fold and the accumulator split are textual; no screen, no `vf`."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t118_setonce as M  # noqa: E402
from pin_census import sites_of  # noqa: E402

SHIFT = '''#include "common.h"
void f(void *effect_state, s32 grid_y, S_0 *coords) {
    s32 scaled_y;
    s32 centered_coord;

    ASM_KEEP(effect_state);
    scaled_y = grid_y << 16;
    centered_coord = coords->unk_06;
    scaled_y >>= 10;
    func_80001000(scaled_y - centered_coord);
}
'''

ACC = '''#include "common.h"
void g(S_0 *rect, s32 col, s32 row_offset) {
    register s32 dst_index ASM_REG("$4");
    s32 other;

    dst_index = rect->unk_00;
    dst_index += col;
    other = dst_index * 2;
    func_80001000(other);
    dst_index += row_offset;
    func_80001004(dst_index);
}
'''


class TestSites(unittest.TestCase):
    def test_interleaved_independent_statement_is_skipped(self):
        st = M.sites(SHIFT)
        self.assertEqual([(s["v"], len(s["steps"])) for s in st], [("scaled_y", 1)])

    def test_step_reading_a_skipped_target_breaks_the_chain(self):
        t = SHIFT.replace("scaled_y >>= 10;", "scaled_y >>= centered_coord;")
        self.assertEqual(M.sites(t), [])

    def test_impure_step_does_not_move_past_a_statement(self):
        t = SHIFT.replace("scaled_y >>= 10;", "scaled_y >>= coords->unk_08;")
        self.assertEqual(M.sites(t), [])

    def test_no_pin_nearby_no_site(self):
        self.assertEqual(M.sites(SHIFT.replace("    ASM_KEEP(effect_state);\n", "")), [])

    def test_accumulator_has_a_split_point(self):
        st = M.sites(ACC)
        self.assertEqual(len(st), 1)
        self.assertIsNotNone(st[0]["split_at"])


class TestRewrite(unittest.TestCase):
    def test_fold_substitutes_in_order(self):
        st = M.sites(SHIFT)[0]
        t = M.rewrite(SHIFT, st, "fold")
        self.assertIn("scaled_y = (grid_y << 16) >> 10;", t)
        self.assertNotIn("scaled_y >>= 10;", t)
        self.assertLess(t.index("scaled_y = (grid_y"), t.index("centered_coord = coords"))

    def test_split_moves_the_prefix_to_a_fresh_local(self):
        st = M.sites(ACC)[0]
        t = M.rewrite(ACC, st, "split")
        self.assertIn("s32 dst_index_part;", t)
        self.assertIn("dst_index_part = rect->unk_00;", t)
        self.assertIn("other = dst_index_part * 2;", t)
        self.assertIn("dst_index = dst_index_part + row_offset;", t)

    def test_menu_erases_the_pins_naming_the_variable(self):
        mn = M.menu(ACC)
        named = [c for lab, c, _n, _a in mn if lab.endswith(":named")]
        self.assertTrue(named)
        self.assertTrue(all(len(sites_of(c)) < len(sites_of(ACC)) for c in named))

    def test_paren(self):
        self.assertEqual(M._paren("rect->unk_00"), "rect->unk_00")
        self.assertEqual(M._paren("a + b"), "(a + b)")
        self.assertEqual(M._paren("(a) + (b)"), "((a) + (b))")
        self.assertEqual(M._paren("(a + b)"), "(a + b)")


if __name__ == "__main__":
    unittest.main()
