"""Lander admission on the live fidelity-site count (tools/land_admit.py) and the owner-kept composite asm spelling
(pin_census.composite_asm_spans / levels.L5_EXCLUDE_COMPOSITE_ASM).  Synthetic rows/text; levels.live_audit_keyed_sites
is stubbed, so no ledger or config file is read.

    python3 -m unittest tools.tests.test_land_admit
"""
import os, sys, unittest
from unittest import mock

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import call_arity, land_admit, levels as L, pin_census as P  # noqa: E402

ROW = {"id": "dungeon/func_80091234", "size": 64, "container": "dungeon", "kind": "overlay",
       "true_name": None, "func": "func_80091234", "defs": None}
SITE = ("func_80091234", "PASSTHRU|func_80010000|x")
SHORT = "void func_80091234(void) { func_80010000(1); }\n"          # arity-short: 1 of 3 arguments
FIXED = "void func_80091234(void) { func_80010000(0, 1, 2); }\n"


class Admission(unittest.TestCase):
    def setUp(self):
        L._CONTAINER_SYMS["dungeon"] = set()
        di = call_arity.DefIndex.from_texts([("dungeon", "func_80010000", "void func_80010000(void *a, s32 b, s32 c) { }\n")])
        self.di = di
        # the audit site is "live" in both texts; the L5 predicate (arity) then decides
        p = mock.patch.object(L, "live_audit_keyed_sites", lambda r, t: [SITE]); p.start(); self.addCleanup(p.stop)

    def test_counts_follow_the_l5_predicate(self):
        self.assertEqual(land_admit.fidelity_counts(ROW, FIXED, SHORT, self.di), (0, 1))
        self.assertEqual(L.live_fidelity_sites(ROW, SHORT, self.di), [SITE[1]])

    def test_fall_is_a_win(self):
        fell, grew = land_admit.admit([], [], True, 0, 1)
        self.assertEqual((fell, grew), (["fidelity"], []))

    def test_rise_at_equal_pins_is_refused(self):
        self.assertEqual(land_admit.admit([], [], True, 1, 0), ([], ["fidelity"]))

    def test_rise_with_pins_falling_is_not_blocked(self):
        self.assertEqual(land_admit.admit(["pins"], [], False, 1, 0), (["pins"], []))

    def test_unchanged_count_adds_nothing(self):
        self.assertEqual(land_admit.admit([], [], True, 1, 1), ([], []))


COMPOSITE = '''static const u32 bank[] __asm__("func_80024000")
__attribute__((section(".text.func_80024000"), aligned(4))) = { 1, 2 };
__asm__(".globl func_80024000\\n"
        ".type func_80024000,@function\\n"
        ".size func_80024000, 8");
void func_80024008(void) { }
'''


class Composite(unittest.TestCase):
    def n(self, t):
        import re
        return len(re.findall(r"__asm__|\basm\s*\(", P.strip_composite_asm(t)))

    def test_alias_and_stamp_excluded(self):
        self.assertEqual(len(P.composite_asm_spans(COMPOSITE)), 2)
        self.assertEqual(self.n(COMPOSITE), 0)

    def test_function_pointer_alias_with_initialiser(self):
        t = 'void (*const module_entry)(void *) asm("func_80024000") = f;\nvoid f(void *a) { }\n'
        self.assertEqual(self.n(t), 0)

    def test_stamp_without_data_prefix_stays_counted(self):
        t = '__asm__(".globl func_80024000\\n.size func_80024000, 8");\n'
        self.assertEqual(self.n(t), 1)

    def test_not_covered_by_the_ruling_stays_counted(self):
        for extra in ('__asm__(".globl func_80024000\\nfunc_80024000 = 0x80024000");',
                      '__asm__(".set func_80024000_returning, func_80024000");',
                      'extern s16 D_X[5] __asm__("D_800133A0");',
                      'void g(int v) { __asm__("" : "+r"(v)); }'):
            self.assertEqual(self.n(COMPOSITE + extra + "\n"), 1, extra)

    def test_levels_flag_guards_the_exclusion(self):
        L._CONTAINER_SYMS["dungeon"] = set()
        rec = lambda: L.evaluate_row(ROW, COMPOSITE, "raw", set(), {}, {}, None)
        with mock.patch.object(L, "L5_EXCLUDE_COMPOSITE_ASM", False):
            self.assertIn("inline_asm", rec()["l5_residue"])
        with mock.patch.object(L, "L5_EXCLUDE_COMPOSITE_ASM", True):
            self.assertNotIn("inline_asm", rec()["l5_residue"])


if __name__ == "__main__":
    unittest.main()
