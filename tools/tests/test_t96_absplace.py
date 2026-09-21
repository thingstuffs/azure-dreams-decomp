"""T96: the goto / if-else abs spellings are textual; the screen and `vf` are not run."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t96_absplace as M  # noqa: E402
from pin_census import sites_of  # noqa: E402

GOTO = '''#include "common.h"
void f(void *motion, s32 *out) {
    s32 axis_delta;
    s32 origin_coord;
    struct { s32 dist[3]; } scratch;

    origin_coord = *(s32 *)motion;
    ASM_SCHED_BARRIER();
    axis_delta = out[0];
    ASM_SCHED_BARRIER();
    axis_delta -= origin_coord;
    if (axis_delta >= 0) {
        goto target_ready;
    }
    axis_delta = 0 - axis_delta;
target_ready:
    scratch.dist[0] = axis_delta;
    out[1] = scratch.dist[0];
}
'''

IFELSE = '''#include "common.h"
void g(s32 delta_x, s32 *out) {
    s32 distance;

    ASM_SCHED_BARRIER();
    if (delta_x < 0) {
        distance = delta_x;
        ASM_KEEP_NV(distance);
        distance = -distance;
    } else {
        distance = delta_x;
    }
    out[0] = distance;
}
'''

FOLD = '''#include "common.h"
void h(s32 source_coord, s32 *out) {
    s32 target_x;
    struct { s32 distance[3]; } work;

    target_x = out[2];
    ASM_SCHED_BARRIER();
    target_x -= source_coord;
    if (target_x < 0) {
        target_x = -target_x;
    }
    work.distance[0] = target_x;
    target_x = 0;
    out[0] = work.distance[0] + target_x;
}
'''

TWOGOTO = '''#include "common.h"
void k(s32 *out) {
    s32 a;
    s32 b;

    a = out[0];
    ASM_SCHED_BARRIER();
    if (a >= 0) { goto a_ready; }
    a = 0 - a;
a_ready:
    b = out[1];
    ASM_SCHED_BARRIER();
    if (b >= 0) { goto b_ready; }
    b = 0 - b;
b_ready:
    out[2] = a + b;
}
'''

NOTANIDIOM = '''#include "common.h"
void n(s32 *out) {
    s32 a;
    s32 b;

    a = out[0];
    ASM_KEEP(a);
    if (a >= 0) { goto a_ready; }
    b = 0 - a;
a_ready:
    out[1] = a + b;
}
'''


class TestSites(unittest.TestCase):
    def test_goto_spelling_is_a_site(self):
        s = M.sites(GOTO)
        self.assertEqual([(x["kind"], x["d"]) for x in s], [("goto", "axis_delta")])
        self.assertIsNotNone(s[0]["prod"])

    def test_ifelse_spelling_is_a_site_with_the_tested_value_as_source(self):
        s = M.sites(IFELSE)
        self.assertEqual([(x["kind"], x["d"], x["src"]) for x in s], [("ifelse", "distance", "delta_x")])

    def test_plainif_site_carries_its_producer_and_consumer(self):
        s = M.sites(FOLD)
        self.assertEqual([x["kind"] for x in s], ["plainif"])
        self.assertIsNotNone(s[0]["prod"])
        self.assertIsNotNone(s[0]["cons"])
        self.assertEqual(s[0]["cons"][1], "work.distance[0]")

    def test_a_negate_of_another_variable_is_not_an_idiom(self):
        self.assertEqual(M.sites(NOTANIDIOM), [])
        self.assertTrue(M.T.eligible(NOTANIDIOM, {}, {}))


class TestRewrite(unittest.TestCase):
    def test_goto_idiom_and_its_label_become_one_call(self):
        new = M.rewrite(GOTO, M.sites(GOTO), "inplace", "abs")
        self.assertIn("axis_delta = abs(axis_delta);", new)
        self.assertNotIn("target_ready", new)
        self.assertNotIn("goto", new)
        self.assertIn("extern int abs(int);", new)

    def test_ifelse_idiom_collapses_and_takes_the_pin_inside_it(self):
        new = M.rewrite(IFELSE, M.sites(IFELSE), "inplace", "abs")
        self.assertIn("distance = abs(delta_x);", new)
        self.assertNotIn("ASM_KEEP_NV(distance)", new)
        self.assertEqual(len(sites_of(new)), len(sites_of(IFELSE)) - 1)

    def test_fold_takes_the_producer_into_the_call(self):
        new = M.rewrite(FOLD, M.sites(FOLD), "fold", "abs")
        self.assertIn("target_x = abs(target_x - source_coord);", new)

    def test_foldcons_takes_the_consumer_too(self):
        new = M.rewrite(FOLD, M.sites(FOLD), "foldcons", "abs")
        self.assertIn("work.distance[0] = abs(target_x - source_coord);", new)
        self.assertNotIn("target_x -= source_coord;", new)

    def test_builtin_spelling_adds_no_declaration(self):
        new = M.rewrite(GOTO, M.sites(GOTO), "inplace", "__builtin_abs")
        self.assertIn("__builtin_abs(axis_delta)", new)
        self.assertNotIn("extern int abs(int);", new)


class TestMenu(unittest.TestCase):
    def test_every_candidate_carries_fewer_pins_and_the_same_unscored_text(self):
        from pin_census import unscored_text
        for text in (GOTO, IFELSE, FOLD, TWOGOTO):
            menu = M.candidates(text)
            self.assertTrue(menu, text[:40])
            for label, cand in menu:
                self.assertLess(len(sites_of(cand)), len(sites_of(text)), label)
                self.assertEqual(unscored_text(cand), unscored_text(text), label)

    def test_two_idioms_are_offered_jointly_and_singly(self):
        labels = [l for l, _ in M.candidates(TWOGOTO)]
        self.assertTrue(any(l.startswith("all2:") for l in labels), labels[:6])
        self.assertTrue(any(l.startswith("goto@") for l in labels), labels[:6])

    def test_a_plan_reaches_the_barriers_above_the_idiom(self):
        menu = M.candidates(GOTO)
        clear = [l for l, c in menu if "ASM_SCHED_BARRIER" not in c]
        self.assertTrue(clear, [l for l, _ in menu])


if __name__ == "__main__":
    unittest.main()
