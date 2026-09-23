"""T103: t69's copy drop composed with a move of the statements that last read the dropped values.
Textual only (no compiler): the runs, the legal moves and the built text are checked; the screen and `vf` are not run."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t103_dropsink as M  # noqa: E402
import t69_prologue as P  # noqa: E402
import t72_stmtperm as S  # noqa: E402
from pin_census import sites_of, unscored_text  # noqa: E402

ROW = '''#include "common.h"
typedef struct { s32 a; s32 b; s16 c; s16 d; } St;
void f(St *st, s32 offset_x, s32 offset_y, s32 base_x, s32 base_y) {
    register s32 held_offset_x ASM_REG("$22") = offset_x;
    register s32 held_offset_y ASM_REG("$23") = offset_y;

    func_80000000(st);
    st->a = held_offset_x << 4;
    st->b = held_offset_y << 4;
    st->c = (s16) base_x;
    st->d = (s16) base_y;
    ASM_KEEP(held_offset_x);
    ASM_KEEP(held_offset_y);
}
'''

NO_COPY = '''#include "common.h"
void g(s32 *p, s32 x) {
    s32 y;
    y = x + 1;
    ASM_KEEP(y);
    *p = y;
}
'''


class TestDetection(unittest.TestCase):
    def test_a_pinned_parameter_copy_is_eligible(self):
        self.assertIsNone(M.T.eligible(ROW, None, {}))

    def test_a_function_without_a_parameter_copy_refuses(self):
        self.assertEqual(M.T.eligible(NO_COPY, None, {}), "no redundant parameter copy")

    def test_the_dropped_names_include_the_parameters(self):
        label, _c = P.prologue_candidates(ROW)[0]
        self.assertEqual(M.dropped_names(ROW, label),
                         {"held_offset_x", "held_offset_y", "offset_x", "offset_y"})


class TestMoves(unittest.TestCase):
    def setUp(self):
        self.label, self.c = P.prologue_candidates(ROW)[0]
        self.names = M.dropped_names(ROW, self.label)
        self.runs = M.runs_mentioning(self.c, self.names)

    def test_the_copy_set_goes_with_its_keeps(self):
        self.assertEqual(sites_of(self.c), [])

    def test_the_run_holds_the_call_and_the_stores(self):
        self.assertEqual(len(self.runs), 1)
        self.assertEqual(len(self.runs[0]), 5)

    def test_the_two_reads_move_past_the_base_stores_as_one_block(self):
        run = self.runs[0]
        mv = dict(M.moves(run, self.names))
        grp = [t for t in mv if t.startswith("grp")]
        self.assertTrue(grp)
        cand = S.build(self.c, run, mv[max(grp)], set())
        body = [l.strip() for l in cand.split("\n") if l.strip().startswith(("st->", "func_"))]
        self.assertEqual(body[0], "func_80000000(st);")                 # the call anchors the run
        self.assertEqual([b[:5] for b in body[1:]], ["st->c", "st->d", "st->a", "st->b"])
        self.assertEqual(unscored_text(cand), unscored_text(self.c))

    def test_no_move_crosses_the_call(self):
        run = self.runs[0]
        for tag, perm in M.moves(run, self.names):
            self.assertEqual(perm[0], 0, tag)


if __name__ == "__main__":
    unittest.main()
