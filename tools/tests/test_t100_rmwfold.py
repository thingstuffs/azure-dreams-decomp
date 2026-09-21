"""T100: the read-modify-write triples and the two fold forms are textual; the screen and `vf` are not run."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t100_rmwfold as M  # noqa: E402
from pin_census import sites_of, unscored_text  # noqa: E402

RUN = '''#include "common.h"
void f(void *actor, void *action) {
    register void *context ASM_REG("$21");
    s32 actor_flags_14;
    s32 actor_flags_1c;
    s32 action_mode;

    context = action;
    ASM_SCHED_BARRIER();
    actor_flags_14 = ((S *)actor)->unk_14;
    actor_flags_1c = ((S *)actor)->unk_1C;
    action_mode = 0;
    actor_flags_14 |= 0x2000;
    actor_flags_1c |= 0x2000;
    ((S *)actor)->unk_14 = actor_flags_14;
    ((S *)actor)->unk_1C = actor_flags_1c;
    ((S *)context)->unk_20 = action_mode;
}
'''

CALL_BETWEEN = RUN.replace("    action_mode = 0;", "    action_mode = g(actor);")

OTHER_USE = RUN.replace("    ((S *)context)->unk_20 = action_mode;",
                        "    ((S *)context)->unk_20 = actor_flags_14;")

NO_RUN = '''#include "common.h"
void h(void *actor) {
    s32 v;
    v = 1;
    ASM_KEEP(v);
    ((S *)actor)->unk_14 = v;
}
'''


class TestDetection(unittest.TestCase):
    def test_both_triples_of_the_run_are_found(self):
        self.assertIsNone(M.T.eligible(RUN, None, {}))
        got = [(t["v"], t["op"], t["k"]) for t in M.triples(RUN)]
        self.assertEqual(got, [("actor_flags_14", "|", "0x2000"), ("actor_flags_1c", "|", "0x2000")])

    def test_a_call_between_load_and_store_is_refused(self):
        self.assertEqual(M.triples(CALL_BETWEEN), [])

    def test_a_local_read_elsewhere_is_refused(self):
        self.assertEqual([t["v"] for t in M.triples(OTHER_USE)], ["actor_flags_1c"])

    def test_a_plain_store_is_not_a_triple(self):
        self.assertEqual(M.T.eligible(NO_RUN, None, {}), "no scalarised read-modify-write")


class TestFolds(unittest.TestCase):
    def test_the_full_fold_leaves_one_statement_per_field(self):
        new = M.rewrite(RUN, M.triples(RUN), "full")
        self.assertIn("((S *)actor)->unk_14 |= 0x2000;", new)
        self.assertIn("((S *)actor)->unk_1C |= 0x2000;", new)
        self.assertNotIn("actor_flags_14", new)            # the declaration goes too
        self.assertNotIn("actor_flags_1c", new)

    def test_the_birth_form_keeps_the_store(self):
        new = M.rewrite(RUN, M.triples(RUN), "birth")
        self.assertIn("actor_flags_14 = ((S *)actor)->unk_14 | 0x2000;", new)
        self.assertIn("((S *)actor)->unk_14 = actor_flags_14;", new)
        self.assertNotIn("actor_flags_14 |= 0x2000;", new)


class TestCandidates(unittest.TestCase):
    def test_the_barrier_above_the_run_is_in_the_window(self):
        cands = dict(M.candidates(RUN))
        self.assertIn("rmw2@10:full:win", cands)
        self.assertNotIn("ASM_SCHED_BARRIER", cands["rmw2@10:full:win"])
        self.assertIn("ASM_REG", cands["rmw2@10:full:win"])   # the window plan keeps the far pin

    def test_every_candidate_removes_a_pin_and_keeps_the_unscored_text(self):
        n0, sig = len(sites_of(RUN)), unscored_text(RUN)
        cands = M.candidates(RUN)
        self.assertTrue(cands)
        for label, t in cands:
            self.assertLess(len(sites_of(t)), n0, label)
            self.assertEqual(unscored_text(t), sig, label)

    def test_the_whole_function_plan_is_offered_on_a_small_row(self):
        self.assertIn("rmw2@10:full:fn", dict(M.candidates(RUN)))


if __name__ == "__main__":
    unittest.main()
