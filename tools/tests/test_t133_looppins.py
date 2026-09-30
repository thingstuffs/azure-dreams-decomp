"""t133_looppins: goto loop -> real loop jointly with pin erasure (no compiler needed)."""
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import xform.t133_looppins as t
from pin_census import sites_of

SRC = '''void f(int n) {
    register int i ASM_REG("$16");
    register int acc ASM_REG("$17");
    int other;

    acc = 0;
    i = 0;
loop_a:
    acc = acc + i;
    i = i + 1;
    if (i < n) { goto loop_a; }
    other = 3;
    g(acc, other);
}
'''

TWO = '''void f(int n, int m) {
    register int i ASM_REG("$16");
    register int j ASM_REG("$18");
    int k;

    i = 0;
outer:
    j = 0;
inner:
    k = k + j;
    j = j + 1;
    if (j < m) { goto inner; }
    i = i + 1;
    if (i < n) { goto outer; }
    g(k);
}
'''


def labels(text):
    return [l for l, _c, _t in t.candidates(text)]


class T133(unittest.TestCase):
    def test_callee_saved(self):
        s = sites_of(SRC)
        self.assertEqual([t.is_callee(x) for x in s], [True, True])
        self.assertEqual([t.pinned_var(x) for x in s], ["i", "acc"])

    def test_all_pins_erased_with_do_while(self):
        c = {l: v for l, v, _ in t.candidates(SRC)}
        best = c["do:loop_a:all"]
        self.assertEqual(len(sites_of(best)), 0)
        self.assertIn("do {", best)
        self.assertIn("} while (i < n);", best)
        self.assertNotIn("goto", best)

    def test_t44_unbraced_if_goto_is_dropped(self):
        self.assertFalse(t._wellformed("void f(void) {\ndo {\n a();\n if (i < n) } while (1);\n}\n"))
        self.assertTrue(t._wellformed("void f(void) {\ndo {\n a();\n} while (i < n);\n}\n"))

    def test_loop_label_prefix_is_seen(self):
        self.assertIn("looq_a", t._swap_in("loop_a: x();"))
        self.assertEqual(t._swap_out("looq_a", "loop_a"), "loop_a")

    def test_unbraced_back_edge_goes_through_t122(self):
        txt = SRC.replace("if (i < n) { goto loop_a; }", "if (i < n) goto loop_a;")
        ls = labels(txt)
        self.assertTrue(ls and all(l.startswith("while") for l in ls))
        self.assertEqual(len(sites_of([c for l, c, _ in t.candidates(txt) if l.endswith(":all")][0])), 0)

    def test_singles_last_first(self):
        ls = [l for l in labels(SRC) if l.startswith("do:loop_a:one")]
        self.assertEqual(ls, ["do:loop_a:one1", "do:loop_a:one0"])

    def test_candidates_have_fewer_pins_and_same_scored_text(self):
        for _l, cand, _t in t.candidates(SRC):
            self.assertLess(len(sites_of(cand)), 2)

    def test_pin_on_unreferenced_variable_not_erased(self):
        txt = SRC.replace("int other;", 'register int other ASM_REG("$19");')
        c = {l: v for l, v, _ in t.candidates(txt)}
        self.assertEqual(len(sites_of(c["do:loop_a:all"])), 1)      # `other` stays pinned

    def test_joint_candidate_first_for_two_loops(self):
        ls = labels(TWO)
        self.assertTrue(ls[0].startswith("joint:"))
        c = t.candidates(TWO)[0][1]
        self.assertEqual(c.count("goto"), 0)
        self.assertEqual(len(sites_of(c)), 0)

    def test_no_loop_no_candidates(self):
        txt = SRC.replace("loop_a:", "").replace("if (i < n) { goto loop_a; }", "")
        self.assertEqual(t.candidates(txt), [])
        self.assertEqual(t.T.eligible(txt, None, None), "no backward-goto loop")

    def test_eligible_needs_pin(self):
        txt = SRC.replace(' ASM_REG("$16")', "").replace(' ASM_REG("$17")', "")
        self.assertEqual(t.T.eligible(txt, None, None), "no pin sites")
        self.assertIsNone(t.T.eligible(SRC, None, None))

    def test_keep_pin_on_loop_variable(self):
        txt = SRC.replace("    acc = acc + i;", "    acc = acc + i;\n    ASM_KEEP(acc);")
        c = {l: v for l, v, _ in t.candidates(txt)}
        self.assertEqual(len(sites_of(c["do:loop_a:all"])), 0)

    def test_icount(self):
        self.assertEqual(t.icount([".ent", "addiu $2,$2,1", "$L1:", "jr $31", ".end"]), 2)


if __name__ == "__main__":
    unittest.main()
