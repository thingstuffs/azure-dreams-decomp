"""T99: the absolute-memory spelling and the pin plans are textual; the screen and `vf` are not run."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t99_absmem as M  # noqa: E402
from pin_census import sites_of, unscored_text  # noqa: E402

SCALAR = '''#include "common.h"
extern u16 D_80013714;
extern u8 D_8008346A;
void f(void *state) {
    if (D_80013714 & 1) {
        return;
    }

    ASM_MEM_BARRIER();

    if (D_80013714 & 8) {
        *(s32 *)state = 1;
    }
}
'''

ARRAY = '''#include "common.h"
extern u16 D_80013714[5];
void g(void *state) {
    ASM_SCHED_BARRIER();
    if (!(D_80013714[0] & 1)) {
        *(s32 *)state = 2;
    }
}
'''

NO_SYM = '''#include "common.h"
void h(void *state) {
    s32 v;
    v = 1;
    ASM_KEEP(v);
    *(s32 *)state = v;
}
'''

WRITE = '''#include "common.h"
extern u16 D_80013714;
void w(void) {
    ASM_SCHED_BARRIER();
    D_80013714 = 0;
}
'''


class TestDetection(unittest.TestCase):
    def test_a_barrier_in_front_of_a_read_is_a_site(self):
        self.assertIsNone(M.T.eligible(SCALAR, None, {}))
        ss = M.sites(SCALAR)
        self.assertEqual([(s["sym"], s["ty"]) for s in ss], [("D_80013714", "u16")])

    def test_a_file_without_a_fixed_address_global_refuses(self):
        self.assertEqual(M.T.eligible(NO_SYM, None, {}),
                         "no fixed-address global declared at an integer width")

    def test_a_write_through_the_symbol_is_not_a_site(self):
        self.assertEqual(M.sites(WRITE), [])

    def test_only_the_read_below_the_pin_is_seen(self):
        s = M.sites(SCALAR)[0]
        self.assertGreater(s["span"][0], SCALAR.index("ASM_MEM_BARRIER"))


class TestSpelling(unittest.TestCase):
    def test_the_scalar_read_becomes_an_absolute_operand_at_its_width(self):
        cand = dict(M.candidates(SCALAR))[[l for l, _t in M.candidates(SCALAR)][0]]
        self.assertIn("if ((*(u16 *)0x80013714) & 8) {", cand)
        self.assertIn("if (D_80013714 & 1) {", cand)        # the read above the pin is untouched
        self.assertNotIn("ASM_MEM_BARRIER", cand)

    def test_the_zero_index_of_an_array_symbol_loses_its_brackets(self):
        labels = [l for l, _t in M.candidates(ARRAY)]
        self.assertTrue(labels)
        cand = dict(M.candidates(ARRAY))[labels[0]]
        self.assertIn("if (!((*(u16 *)0x80013714) & 1)) {", cand)
        self.assertNotIn("ASM_SCHED_BARRIER", cand)

    def test_a_non_zero_index_keeps_the_subscript(self):
        self.assertEqual(M._spell("u16", 0x80013714, "[i]"), "((u16 *)0x80013714)[i]")
        self.assertEqual(M._spell("u16", 0x80013714, "[0]"), "(*(u16 *)0x80013714)")

    def test_every_candidate_removes_a_pin_and_keeps_the_unscored_text(self):
        for src in (SCALAR, ARRAY):
            n0, sig = len(sites_of(src)), unscored_text(src)
            for label, t in M.candidates(src):
                self.assertLess(len(sites_of(t)), n0, label)
                self.assertEqual(unscored_text(t), sig, label)


if __name__ == "__main__":
    unittest.main()
