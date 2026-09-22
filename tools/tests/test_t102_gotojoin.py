"""T102: the join finder, the scope test and the duplication are textual; the screen and `vf` are not."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t102_gotojoin as M  # noqa: E402

# the shape of dungeon/func_800C9858: the tail ends the block, so the copy needs a label past it
OPEN_TAIL = '''#include "common.h"
void f(void *part, void *scratch) {
    {
        s16 edge_coord;
        s32 axis_extent;
        if (((S *)part)->unk_00 & 2) {
            edge_coord = (s8)((S *)part)->unk_02;
            axis_extent = ((S *)scratch)->unk_10C;
            ASM_SCHED_BARRIER();
            edge_coord -= axis_extent;
            goto axis_y_join;
        }
        edge_coord = (s8)((S *)part)->unk_02;
        axis_extent = ((S *)scratch)->unk_10C;
        ASM_SCHED_BARRIER();
        edge_coord += axis_extent;
axis_y_join:
        SP16(0x8A) = edge_coord;
        SP16(0x82) = edge_coord;
    }
}
'''

# the shape of dungeon/func_80977E0C: the tail ends in a goto, so no new label is needed
CLOSED_TAIL = '''#include "common.h"
void g(void *entity, void *action) {
    s32 effect_entry;
    u8 *effect_table;

    if (((S *)action)->unk_92 != 0) {
        effect_table = (u8 *)0x80170000;
        ASM_KEEP(effect_table);
        effect_table += 0x4150;
        goto effect_common;
    }
    effect_table = (u8 *)0x80170000;
    ASM_KEEP(effect_table);
    effect_table += 0x4158;
effect_common:
    effect_entry = (s32)effect_table;
    func_80047784(entity, *(u8 *)effect_entry, 0);
    goto done;
done:
    return;
}
'''

# the tail names a local of a block the goto site is not inside
OUT_OF_SCOPE = '''#include "common.h"
void h(void *part) {
    s32 outer;
    if (((S *)part)->unk_00 & 2) {
        ASM_SCHED_BARRIER();
        goto join;
    }
    {
        s32 inner;
        inner = ((S *)part)->unk_04;
join:
        outer = inner;
    }
}
'''


class TestJoins(unittest.TestCase):
    def test_label_with_a_goto_predecessor(self):
        js = M.joins(OPEN_TAIL)
        self.assertEqual([j["label"] for j in js], ["axis_y_join"])
        self.assertEqual(len(js[0]["gotos"]), 1)

    def test_tail_stops_at_the_transfer(self):
        j = M.joins(CLOSED_TAIL)[0]
        self.assertEqual(j["label"], "effect_common")
        ends = M.tails(CLOSED_TAIL, j)
        self.assertTrue(ends[-1][1])                      # the last statement is a `goto`
        self.assertEqual(len(ends), 3)

    def test_out_of_scope_tail_refused(self):
        j = next(x for x in M.joins(OUT_OF_SCOPE) if x["label"] == "join")
        end = M.tails(OUT_OF_SCOPE, j)[0][0]
        self.assertFalse(M._in_scope(OUT_OF_SCOPE, j, end))
        self.assertFalse([l for l, _c in M.candidates(OUT_OF_SCOPE)])


class TestDuplicate(unittest.TestCase):
    def test_open_tail_gets_a_label_of_its_own(self):
        cand = dict(M.candidates(OPEN_TAIL))["dup:axis_y_join@17+2/1"]
        self.assertNotIn("goto axis_y_join;", cand)
        self.assertIn("goto axis_y_join_done;", cand)
        self.assertIn("axis_y_join_done:", cand)
        self.assertNotIn("\naxis_y_join:", cand)          # nothing jumps to the old label
        self.assertEqual(cand.count("SP16(0x8A) = edge_coord;"), 2)

    def test_closed_tail_needs_no_label(self):
        cand = next(c for l, c in M.candidates(CLOSED_TAIL) if l.startswith("dup:effect_common@15+3"))
        self.assertNotIn("goto effect_common;", cand)
        self.assertNotIn("effect_common_done", cand)
        self.assertEqual(cand.count("func_80047784(entity, *(u8 *)effect_entry, 0);"), 2)

    def test_eligible_and_capped(self):
        self.assertIsNone(M.T.eligible(OPEN_TAIL, {}, {}))
        self.assertLessEqual(len(M.candidates(CLOSED_TAIL)), M.MAX_CANDS)


if __name__ == "__main__":
    unittest.main()
