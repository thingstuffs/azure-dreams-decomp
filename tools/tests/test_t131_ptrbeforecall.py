"""t131_ptrbeforecall: hoisting a work pointer above the preceding call (no compiler)."""
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import xform.t131_ptrbeforecall as t
from pin_census import sites_of

FIX = ROOT / "tools" / "fixtures" / "t131"

PRE = '''void f(Obj *object, int a) {
    u8 *w;
    int k;

    if (object != 0) {
        g1(object, a);
        k = a + 1;
        w = (u8 *)object + 0x20;
        *(s16 *)(w + 0xE) = 4;
        ASM_USE(w);
        g2(k);
    }
}
'''


def cands(text):
    return dict(t.candidates(text))


class T131(unittest.TestCase):
    def test_finds_assignment(self):
        a = t.assignments(PRE)
        self.assertEqual([(x["v"], x["x"]) for x in a], [("w", "object")])

    def test_hoist_above_call_and_pin_erased(self):
        c = cands(PRE)
        best = [v for k, v in c.items() if k.endswith(":named")][0]
        self.assertEqual(len(sites_of(best)), 0)
        # assignment now above g1(...), the old place is gone
        self.assertLess(best.index("w = (u8 *)object + 0x20;"), best.index("g1(object, a);"))
        self.assertEqual(best.count("w = (u8 *)object + 0x20;"), 1)

    def test_eligible_needs_pin(self):
        self.assertEqual(t.T.eligible(PRE.replace("        ASM_USE(w);\n", ""), None, None), "no pin sites")
        self.assertIsNone(t.T.eligible(PRE, None, None))

    def test_refuse_x_assigned_by_call(self):
        txt = PRE.replace("g1(object, a);", "object = g1(a);")
        self.assertEqual(cands(txt), {})

    def test_refuse_v_used_before(self):
        txt = PRE.replace("k = a + 1;", "k = w == 0;")
        c = cands(txt)
        # in-place hoist refused; only a fresh renamed pointer may appear, and never a plain hoist of `w`
        self.assertTrue(all("object_work" in v for v in c.values()))

    def test_refuse_across_label(self):
        txt = PRE.replace("        k = a + 1;\n", "      L1:\n        k = a + 1;\n")
        # the label sits between g1 and the assignment: no position above g1
        for v in cands(txt).values():
            self.assertGreater(v.index("w = (u8 *)object + 0x20;"), v.index("L1:"))

    def test_load_is_not_an_address(self):
        txt = PRE.replace("w = (u8 *)object + 0x20;", "w = object->sub;")
        self.assertEqual(t.assignments(txt), [])

    def test_addr_of_member(self):
        txt = PRE.replace("w = (u8 *)object + 0x20;", "w = &object->sub;")
        self.assertEqual([x["x"] for x in t.assignments(txt)], ["object"])

    def test_global_base_refused(self):
        txt = PRE.replace("Obj *object, int a", "int a").replace("f(", "f(") .replace("if (object != 0) {", "if (a) {")
        txt = "extern Obj *object;\n" + txt
        self.assertEqual(t.assignments(txt), [])

    def test_decl_form_hoists_to_function_scope(self):
        txt = '''void f(Obj *object) {
    if (object != 0) {
        g1(object);
        {
            u8 *w = (u8 *)object + 0x20;
            *(s16 *)(w + 2) = 4;
            ASM_USE(w);
        }
    }
}
'''
        best = [v for k, v in cands(txt).items() if k.endswith(":named")][0]
        self.assertIn("    u8 *w;\n", best)
        self.assertLess(best.index("w = (u8 *)object + 0x20;"), best.index("g1(object);"))
        self.assertEqual(len(sites_of(best)), 0)

    def test_loop_leave_needs_x_stable(self):
        txt = '''void f(Obj *o) {
    while (o != 0) {
        g1(o);
        w = (u8 *)o + 0x20;
        *(s16 *)(w + 2) = 4;
        ASM_USE(w);
        o = o->next;
    }
}
'''
        # o changes in the loop: the assignment may hoist within the body (above g1) - the position is inside
        # the loop and legal; nothing may be placed before the `while`
        for v in cands("u8 *w;\n" + txt).values():
            self.assertGreater(v.index("w = (u8 *)o + 0x20;"), v.index("while"))

    def test_fresh_pointer_when_v_reused(self):
        txt = '''void f(Obj *p) {
    int cw;
    if (p != 0) {
        g1(p);
        cw = 3;
        h(cw);
        cw = (s32)p + 0x20;
        ASM_KEEP(cw);
        ((T *)((u8 *)cw))->f = 10;
        cw = k | 0xC;
    }
}
'''
        c = cands(txt)
        self.assertTrue(c)
        best = [v for k, v in c.items() if k.endswith(":named")][0]
        self.assertIn("p_work = (u8 *)p + 0x20;", best)
        self.assertIn("u8 *p_work;", best)
        self.assertIn("((u8 *)p_work)", best)
        self.assertIn("cw = k | 0xC;", best)
        self.assertEqual(len(sites_of(best)), 0)


class Fixtures(unittest.TestCase):
    """The two rows r80_opus_earlyconst2 solved by hand, from their PRE-fix texts."""

    def test_800B4204_zero_pin_candidate(self):
        txt = (FIX / "func_800B4204.pre.c").read_text()
        self.assertEqual(len(sites_of(txt)), 3)
        c = cands(txt)
        joint = [v for k, v in c.items() if k.endswith(":joint")]
        self.assertTrue(joint)
        best = joint[0]
        self.assertEqual(len(sites_of(best)), 0)
        self.assertLess(best.index("owner_data = (u8 *)object + 0x20;"), best.index("func_8003DB94(sprite, D_80079444"))
        self.assertNotIn("__asm__", best)

    def test_80EB751C_hoisted_particle_work(self):
        txt = (FIX / "func_80EB751C.pre.c").read_text()
        named = [v for k, v in cands(txt).items() if k.endswith(":named")]
        self.assertTrue(named)
        hoist = "particle_work = (u8 *)particle + 0x20;"
        for best in named:
            self.assertIn("u8 *particle_work;", best)
            self.assertEqual(best.count(hoist), 1)
            self.assertEqual(len(sites_of(best)), len(sites_of(txt)) - 1)
            self.assertLess(best.index(hoist), best.index("((u8 *)particle_work)"))
        # one position sits above func_8004491C(particle, ...): the spelling the hand fix used
        self.assertTrue(any(v.index(hoist) < v.index("func_8004491C(particle") for v in named))


if __name__ == "__main__":
    unittest.main()
