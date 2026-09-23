"""T117: the staging plans and rewrites are textual; the screen and `vf` are not run."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t117_stagehost as M  # noqa: E402
from pin_census import sites_of  # noqa: E402

FENCE = '''#include "common.h"
void f(u8 *obj, u8 *draw_state) {
    s32 value;

    func_8004491C(obj);
    ((S *)obj)->unk_10 = D_80023DE0;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin) */
    value = 0x1000;
    ((S *)draw_state)->unk_1C = value;
}
'''

KEEP = '''#include "common.h"
void g(u8 *state, u8 *table, s32 angle) {
    s32 initial_state;
    u8 *entry;

    initial_state = 0x1C;
    ASM_KEEP_NV(initial_state);   /* UNRESOLVED C shape (pin) */
    ((S *)state)->unk_9A = initial_state;
    entry = table + (((s32)(angle + 0x100) >> 9) & 7);
    func_80048A44(state, *entry);
}
'''


class TestFence(unittest.TestCase):
    def test_the_store_source_is_staged_on_the_dead_local(self):
        c = dict(M.candidates(FENCE))["ASM_SCHED_BARRIER@7:value<-rhs"]
        self.assertIn("    value = D_80023DE0;\n    ((S *)obj)->unk_10 = value;\n", c)
        self.assertEqual(sites_of(c), [])

    def test_a_live_local_is_not_a_host(self):
        t = FENCE.replace("    value = 0x1000;\n", "")
        self.assertNotIn("ASM_SCHED_BARRIER@7:value<-rhs", dict(M.candidates(t)))


class TestKeep(unittest.TestCase):
    def test_a_parenthesised_operand_is_staged_on_the_kept_local(self):
        c = dict(M.candidates(KEEP))["ASM_KEEP_NV@7:initial_state<-op"]
        self.assertIn("    initial_state = (s32)(angle + 0x100) >> 9) & 7;\n".replace("(s32)(", "((s32)(", 1), c)
        self.assertIn("    entry = table + initial_state;\n", c)
        self.assertEqual(sites_of(c), [])

    def test_operands_split_top_level_sums_only(self):
        self.assertEqual(M.operands("a + (b >> 2)"), ["a + (b >> 2)", "(b >> 2)"])
        self.assertEqual(M.operands("(a + b) * 2"), ["(a + b) * 2"])


if __name__ == "__main__":
    unittest.main()
