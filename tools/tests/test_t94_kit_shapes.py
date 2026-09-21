"""T94, round-71 KIT additions: the cast EXPANSION (e) and the constant-free split (f), textual only."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t94_castsplit as M  # noqa: E402

EXPAND = '''#include "common.h"
void f(s32 *out) {
    register s32 angle ASM_REG("$16");
    register s32 next_angle ASM_REG("$17");
    s16 narrow;

    angle = out[0];
    ASM_KEEP(angle);
    angle = (s16)angle;
    next_angle = angle + 0x80;
    angle = (s16)next_angle;
    narrow = (s16)next_angle;
    out[1] = angle + narrow;
}
'''

OPSPLIT = '''#include "common.h"
void g(void *p, u32 prim, u32 tag_mask, u32 addr_mask, s32 *out) {
    u32 bucket_tag;
    s32 step_distance;
    s32 y_step;

    bucket_tag = (*(u32 *)p & tag_mask) | (prim & addr_mask);
    ASM_SCHED_BARRIER();
    y_step = out[0];
    step_distance = y_step * step_distance;
    out[1] = bucket_tag + step_distance;
}
'''


class Expand(unittest.TestCase):
    def test_a_narrowing_cast_of_a_name_expands_into_the_shift_pair(self):
        got = {(s[1], "|".join(x.strip() for x in s[3])) for s in M.sites(EXPAND)}
        self.assertIn(("expand", "angle = (u32)angle << 16;|angle >>= 16;"), got)
        self.assertIn(("expand", "angle = (u32)next_angle << 16;|angle >>= 16;"), got)

    def test_a_narrow_destination_is_not_expanded(self):
        # `narrow` is s16: the shift pair would not be the same value
        self.assertFalse([s for s in M.sites(EXPAND, near_only=False)
                          if s[1] == "expand" and s[3][0].strip().startswith("narrow")])

    def test_every_expansion_of_one_function_is_offered_as_one_group(self):
        labels = [l for l, _c in M.candidates(EXPAND)]
        self.assertTrue(any(l.startswith("expandx") for l in labels), labels)

    def test_the_function_wide_plan_reaches_the_register_declarations(self):
        by = dict(M.candidates(EXPAND))
        wide = [c for l, c in by.items() if l.endswith(":regvar") or l.endswith(":allvar")]
        self.assertTrue(wide)
        self.assertTrue(any('ASM_REG("$16")' not in c for c in wide))


class OpSplit(unittest.TestCase):
    def test_a_two_operand_rhs_with_no_constant_splits(self):
        got = {(s[1], "|".join(x.strip() for x in s[3])) for s in M.sites(OPSPLIT)}
        self.assertIn(("opsplit", "bucket_tag = (*(u32 *)p & tag_mask);|bucket_tag |= (prim & addr_mask);"), got)

    def test_insource_accepts_a_local_in_the_constants_place(self):
        got = {(s[1], "|".join(x.strip() for x in s[3])) for s in M.sites(OPSPLIT)}
        self.assertIn(("insource", "y_step *= step_distance;|step_distance = y_step;"), got)

    def test_an_operand_naming_the_destination_is_not_an_opsplit(self):
        for s in M.sites(OPSPLIT, near_only=False):
            if s[1] == "opsplit":
                self.assertNotIn("step_distance =", s[3][0])


if __name__ == "__main__":
    unittest.main()
