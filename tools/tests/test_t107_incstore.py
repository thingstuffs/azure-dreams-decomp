"""T107: the increment sites and the three store forms are textual; the screen and `vf` are not run."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t107_incstore as M  # noqa: E402
from pin_census import sites_of, unscored_text  # noqa: E402

ROW = '''#include "common.h"
typedef struct { u16 unk_9E; s32 unk_A0; } St;
void f(St *state, s32 mode) {
    u16 count;
    s32 phase;

    count = state->unk_9E;
    ASM_KEEP(count);
    phase = count * 0xAA;
    count++;
    state->unk_9E = count;
    state->unk_A0 += phase;
}
'''

NO_LOAD = '''#include "common.h"
void g(u16 *field, u16 step, s32 x) {
    ASM_KEEP_DEP_NV(step, x);
    step++;
    *field = step;
}
'''


class TestSites(unittest.TestCase):
    def test_the_staged_increment_and_its_load_are_found(self):
        (s,) = M.sites(ROW)
        self.assertEqual((s["v"], s["lv"]), ("count", "state->unk_9E"))
        self.assertIsNotNone(s["load"])

    def test_without_a_load_only_plus_applies(self):
        (s,) = M.sites(NO_LOAD)
        self.assertIsNone(s["load"])
        self.assertEqual({l.split("@")[0] for l, _ in M.candidates(NO_LOAD)}, {"plus"})

    def test_a_call_between_load_and_increment_drops_the_load_forms(self):
        t = ROW.replace("phase = count * 0xAA;", "phase = func_80000000(count);")
        self.assertIsNone(M.sites(t)[0]["load"])


class TestForms(unittest.TestCase):
    def setUp(self):
        self.menu = dict(M.candidates(ROW))

    def test_plus(self):
        c = self.menu["plus@10:named"]
        self.assertIn("state->unk_9E = count + 1;", c)
        self.assertNotIn("count++;", c)
        self.assertEqual(sites_of(c), [])

    def test_postinc(self):
        c = self.menu["postinc@10:named"]
        self.assertIn("count = state->unk_9E++;", c)
        self.assertNotIn("state->unk_9E = count", c)

    def test_early(self):
        c = self.menu["early@10:named"]
        self.assertIn("count = state->unk_9E;\n    state->unk_9E = count + 1;", c)
        self.assertIn("count++;", c)

    def test_unscored_arms_unchanged(self):
        for c in self.menu.values():
            self.assertEqual(unscored_text(c), unscored_text(ROW))


if __name__ == "__main__":
    unittest.main()
