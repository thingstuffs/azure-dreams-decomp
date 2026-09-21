"""T91: the site detection and the rewrite are textual; the screen and `vf` are not exercised."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t91_absfresh as M  # noqa: E402
from pin_census import sites_of  # noqa: E402
from pin_sites import erase_many  # noqa: E402

T = '''#include "common.h"

void f(void *actor, s32 n) {
    s32 target_x;
    s32 target_y;
    s8 small;
    s32 spare;
    u8 *view;

    ((S *)actor)->unk_60 = g(actor);
    ASM_SCHED_BARRIER();
    target_x = ((S *)actor)->unk_72.s;
    target_y = ((S *)actor)->unk_73.s;
    if (target_x < 0) {
        target_x = -target_x;
    }
    if (target_y < 0)
        target_y = -target_y;
    ((S *)actor)->unk_72.u = target_x;
    ((S *)actor)->unk_73.u = target_y;
    small = ((S *)actor)->unk_74.s;
    small = (small < 0) ? -small : small;
    ((S *)actor)->unk_74.u = small;
    spare = n;
    if (spare < 0) {
        spare = -spare;
    }
    view = (u8 *)actor;
    view[0] = spare;
}
'''

GOTO = '''#include "common.h"

void h(void *actor) {
    s32 target_x;

    ASM_KEEP(actor);
    target_x = ((S *)actor)->unk_72.s;
    if (target_x >= 0) {
        goto done;
    }
    target_x = 0 - target_x;
done:
    ((S *)actor)->unk_72.u = target_x;
}
'''

SPLIT = '''#include "common.h"

void m(void *a, void *b) {
    s32 delta_x;
    s32 delta_y;

    ASM_KEEP(a);
    delta_x = ((S *)a)->x;
    delta_x -= ((S *)b)->x;
    if (delta_x < 0) delta_x = -delta_x;
    delta_y = ((S *)a)->y;
    delta_y = delta_y - ((S *)b)->y;
    delta_y += 1;
    if (delta_y < 0) delta_y = -delta_y;
    p(delta_x, delta_y);
}
'''

NO_PRODUCER = '''#include "common.h"

void k(s32 v) {
    ASM_KEEP(v);
    if (v < 0) {
        v = -v;
    }
    p(v);
}
'''

JOIN = '''#include "common.h"

void j(void *actor, s32 n) {
    s32 target_x;

    ASM_KEEP(actor);
    if (n) {
        goto again;
    }
    target_x = ((S *)actor)->unk_72.s;
again:
    if (target_x < 0) {
        target_x = -target_x;
    }
    ((S *)actor)->unk_72.u = target_x;
}
'''


class Detection(unittest.TestCase):
    def test_every_spelling_of_the_negate(self):
        got = [(s["v"], s["expr"]) for s in M.sites(T)]
        self.assertEqual(got, [("target_x", "((S *)actor)->unk_72.s"),
                               ("target_y", "((S *)actor)->unk_73.s"),
                               ("small", "((S *)actor)->unk_74.s"),
                               ("spare", "n")])                 # braced, braceless, ternary, plain

    def test_the_second_site_looks_past_the_first_idiom(self):
        y = M.sites(T)[1]
        self.assertEqual(y["line"], 13)                          # its producer is above the x idiom
        self.assertFalse(y["other_sets"])

    def test_m2c_goto_spelling_takes_its_label_with_it(self):
        s, = M.sites(GOTO)
        self.assertEqual((s["v"], s["expr"]), ("target_x", "((S *)actor)->unk_72.s"))
        self.assertIn("done:", GOTO[s["idiom"][0]:s["idiom"][1]])

    def test_a_split_producing_run_folds_back_into_one_expression(self):
        xs, ys = M.sites(SPLIT)
        self.assertEqual(xs["expr"], "(((S *)a)->x) - (((S *)b)->x)")
        self.assertEqual(ys["expr"], "((((S *)a)->y) - (((S *)b)->y)) + (1)")
        self.assertEqual(SPLIT[xs["prod"][0]:xs["prod"][1]].count(";"), 2)   # both lines go
        new = M.rewrite(SPLIT, [xs])
        self.assertIn("    abs_delta_x = abs((((S *)a)->x) - (((S *)b)->x));\n", new)
        self.assertNotIn("delta_x -=", new)
        self.assertIn("p(abs_delta_x, delta_y);", new)

    def test_declaration_and_type(self):
        by = {s["v"]: s for s in M.sites(T)}
        self.assertEqual(by["target_x"]["decl"][3], "s32")
        self.assertEqual(by["small"]["decl"][3], "s8")           # widened to s32 by the rewrite

    def test_refusals(self):
        self.assertEqual(M.sites(NO_PRODUCER), [])               # v is a parameter, nothing produces it
        self.assertEqual(M.sites(JOIN), [])                      # a path into the gap skips the producer
        pointer = [x["v"] for x in M.sites(T.replace("s32 spare;", "s32 *spare;"))]
        self.assertEqual(pointer, ["target_x", "target_y", "small"])   # a pointer v is refused
        self.assertIsNotNone(M.T.eligible(T.replace("    ASM_SCHED_BARRIER();\n", ""), None, {}))
        self.assertIsNone(M.T.eligible(T, None, {}))

    def test_gap_is_one_block(self):
        self.assertEqual(M.outer("a; { b; } c;"), "a;  c;")
        self.assertIsNone(M.outer("a; } b;"))
        self.assertIsNone(M.outer("a; { b;"))


class Rewrite(unittest.TestCase):
    def test_joint_rewrite(self):
        ss = M.sites(T)[:2]
        new = M.rewrite(T, ss, grouped=True, widen=True)
        self.assertIn("    abs_x = abs(((S *)actor)->unk_72.s);\n", new)
        self.assertIn("    abs_y = abs(((S *)actor)->unk_73.s);\n", new)
        self.assertIn("((S *)actor)->unk_72.u = abs_x;", new)
        self.assertIn("((S *)actor)->unk_73.u = abs_y;", new)
        self.assertNotIn("if (target_x < 0)", new)
        self.assertNotIn("if (target_y < 0)", new)
        self.assertIn("extern int abs(int);", new)
        self.assertIn("    s32 target_x;\n    s32 abs_x;\n    s32 abs_y;\n    s32 target_y;\n", new)
        self.assertIn("ASM_SCHED_BARRIER();", new)               # the pin is erased separately

    def test_narrow_type_is_widened_and_can_be_kept(self):
        s = [x for x in M.sites(T) if x["v"] == "small"]
        self.assertIn("    s32 abs_small;\n", M.rewrite(T, s, grouped=False, widen=True))
        self.assertIn("    s8 abs_small;\n", M.rewrite(T, s, grouped=False, widen=False))
        self.assertIn("((S *)actor)->unk_74.u = abs_small;", M.rewrite(T, s, grouped=False, widen=True))

    def test_the_goto_form_loses_its_label(self):
        new = M.rewrite(GOTO, M.sites(GOTO))
        self.assertIn("    abs_x = abs(((S *)actor)->unk_72.s);\n", new)
        self.assertNotIn("done", new)
        self.assertIn("((S *)actor)->unk_72.u = abs_x;", new)

    def test_declaration_dropped_only_when_the_name_is_gone(self):
        ss = M.sites(T)[:2]
        new = M.rewrite(T, ss)
        self.assertIn("    s32 target_x;\n", new)
        gone = M.drop_decls(new, ss)
        self.assertNotIn("    s32 target_x;\n", gone)
        self.assertNotIn("    s32 target_y;\n", gone)
        self.assertIn("    s32 spare;\n", gone)                  # still written and read

    def test_a_pinned_declaration_is_never_dropped(self):
        t = T.replace("    s32 target_x;", '    register s32 target_x ASM_REG("$2");')
        ss = [s for s in M.sites(t) if s["v"] == "target_x"]
        new = M.rewrite(t, ss)
        self.assertEqual(M.drop_decls(new, ss), new)             # the line carries a live pin
        pins = [p for p in sites_of(new) if p[1] == "ASM_REG"]
        self.assertIn("    s32 target_x;", erase_many(new, pins, clean_notes=True))

    def test_pin_plans_reach_a_pin_on_the_declaration(self):
        t = T.replace("    s32 target_x;", '    register s32 target_x ASM_REG("$2");')
        ss = M.sites(t)[:2]
        new = M.rewrite(t, ss)
        plans = M.pin_plans(new, ss)
        self.assertEqual([sorted(p[1] for p in g) for g in plans][0],
                         ["ASM_REG", "ASM_SCHED_BARRIER"])       # the window plus the named pin
        self.assertTrue(all(len(g) == 1 for g in plans[1:]))


if __name__ == "__main__":
    unittest.main()
