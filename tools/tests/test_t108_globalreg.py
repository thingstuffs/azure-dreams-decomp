"""T108: file-scope register variables found, moved into their one user, NON_MATCHING arms untouched; textual only."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t108_globalreg as M  # noqa: E402
from pin_census import sites_of, unscored_text  # noqa: E402

GUARDED = '''#include "common.h"

#ifndef NON_MATCHING
register s32 state ASM_REG("$7");   /* UNRESOLVED C shape (pin) */
#else
static s32 state;
#endif

void f(s32 *p) {
    s32 base_y;
    base_y = p[1];
    ASM_KEEP(base_y);
    state = p[0];
    p[2] = state + base_y;
}
'''

PLAIN = '''#include "common.h"
register u8 *carrier ASM_REG("$2");
u8 *g(u8 *r) {
    carrier = r;
    return carrier;
}
'''

TWO_USERS = PLAIN + '''void h(void) {
    carrier = 0;
}
'''


class TestSites(unittest.TestCase):
    def test_a_guarded_declaration_is_a_site(self):
        (s,) = M.sites(GUARDED)
        self.assertEqual((s["v"], s["ty"], s["guard"]), ("state", "s32", "m"))

    def test_a_pointer_type_keeps_its_star(self):
        (s,) = M.sites(PLAIN)
        self.assertEqual((s["v"], s["ty"], s["guard"]), ("carrier", "u8 *", ""))

    def test_a_variable_two_functions_use_is_refused(self):
        self.assertEqual(M.sites(TWO_USERS), [])
        self.assertEqual(M.T.eligible(TWO_USERS, None, {}),
                         "no file-scope register variable used by exactly one function's scored arm")


class TestMove(unittest.TestCase):
    def test_the_guarded_move_keeps_the_guard_and_the_nm_arm(self):
        menu = dict(M.candidates(GUARDED))
        c = menu["state:reg:none"]
        self.assertIn("void f(s32 *p) {\n#ifndef NON_MATCHING\n    register s32 state;\n#endif\n", c)
        self.assertNotIn('ASM_REG("$7")', c)
        self.assertIn("static s32 state;", c)
        self.assertEqual(unscored_text(c), unscored_text(GUARDED))
        self.assertEqual(len(sites_of(c)), 1)                    # the keep is still there

    def test_the_other_pins_are_offered_for_erasure(self):
        labels = [l for l, _ in M.candidates(GUARDED)]
        self.assertTrue(any(l.startswith("state:reg:one") for l in labels))
        self.assertTrue(any(l.startswith("state:plain:") for l in labels))

    def test_the_plain_move(self):
        c = dict(M.candidates(PLAIN))["carrier:plain:none"]
        self.assertIn("u8 *g(u8 *r) {\n    u8 *carrier;\n", c)
        self.assertEqual(sites_of(c), [])


if __name__ == "__main__":
    unittest.main()
