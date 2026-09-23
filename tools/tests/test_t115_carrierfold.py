"""T115: the carrier rules (store, use-first, substitution) are textual; the screen and `vf` are not run."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t115_carrierfold as M  # noqa: E402
from pin_census import sites_of  # noqa: E402

STORE = '''#include "common.h"
void f(S *polyline) {
    register s32 prim_mode ASM_REG("$2");   /* UNRESOLVED C shape (pin) */

    prim_mode = 5;
    polyline->unk_03 = prim_mode;
    prim_mode = 0x48;
    polyline->unk_07 = prim_mode;
    ASM_KEEP_NV(prim_mode);   /* UNRESOLVED C shape (pin) */
    polyline->unk_14 = 0x55555555;
    prim_mode |= 2;
    polyline->unk_07 = prim_mode;
}
'''

USEFIRST = '''#include "common.h"
void g(s32 rv, u8 *cnt) {
    s32 cc;
    s32 st;
    s32 phase;

    cc = *(s16 *)(cnt + 6);
    ASM_KEEP_NV(cc);   /* UNRESOLVED C shape (pin) */
    st = cc;
    phase = rv % st;
    h(phase, st);
}
'''


class TestStmt(unittest.TestCase):
    def test_arrow_lvalues_parse(self):
        self.assertEqual(M.stmt("    p->unk_07 |= 2;")[1:], ("p->unk_07", "|", "2"))
        self.assertIsNone(M.stmt("    ASM_KEEP(x);"))
        self.assertIsNone(M.stmt("    if (x) y = 1;"))


class TestStore(unittest.TestCase):
    def test_the_run_folds_into_field_stores_and_the_rmw_becomes_a_compound(self):
        c = dict(M.candidates(STORE))["prim_mode:fix:stmt"]
        self.assertIn("    polyline->unk_03 = 5;\n    polyline->unk_07 = 0x48;\n", c)
        self.assertIn("    polyline->unk_07 |= 2;\n", c)
        self.assertNotIn("ASM_KEEP_NV", c)
        self.assertIn('ASM_REG("$2")', c)                    # the stmt-only plan keeps the declaration pin
        self.assertEqual(len(sites_of(c)), 1)


class TestUseFirst(unittest.TestCase):
    def test_the_use_reads_the_source_and_the_copy_follows(self):
        c = dict(M.candidates(USEFIRST))["cc:usefirst@9:named"]
        self.assertIn("    phase = rv % cc;\n    st = cc;\n", c)
        self.assertEqual(sites_of(c), [])


class TestSubst(unittest.TestCase):
    def test_substitution_drops_the_definition(self):
        c = dict(M.candidates(USEFIRST))["cc:subst@7:named"]
        self.assertIn("    st = *(s16 *)(cnt + 6);\n", c.replace("(*(s16 *)(cnt + 6))", "*(s16 *)(cnt + 6)"))
        self.assertNotIn("cc = ", c)

    def test_no_pinned_local_is_refused(self):
        t = USEFIRST.replace("    ASM_KEEP_NV(cc);   /* UNRESOLVED C shape (pin) */\n", "")
        self.assertEqual(M.T.eligible(t, None, {}), "no pin sites")


if __name__ == "__main__":
    unittest.main()
