"""T19: idiom detection and the `%` rewrites are textual; `vf` is not exercised.

The second fixture is dungeon/func_800D5794's spelling (lane r59_sol_large7): the rounded quotient
lands in a NAMED local that a later statement subtracts, and the remainder itself is read once.
"""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t19_modpow2 as M  # noqa: E402

CLASSIC = '''#include "common.h"
void f(s32 a, s32 *out) {
    s32 x;
    s32 q;

    x = g();
    q = x;
    if (x < 0) {
        q = x + 63;
    }
    out[0] = x - ((q >> 6) << 6);
}
'''

NAMED = '''#include "common.h"
void f(void *object, S_2 *spawn_params) {
    s32 offset_roll_a;
    s32 roll_remainder;
    s32 biased_roll;
    register s32 offset_sum ASM_REG("$2");
    u8 *part;

    offset_roll_a = g();
    {
        const s32 offset_roll_b = g();
        part = ((S_0 *)object)->unk_08;
        roll_remainder = offset_roll_a;
        if (offset_roll_a < 0) {
            roll_remainder = offset_roll_a + 63;
        }
        biased_roll = offset_roll_b;
        offset_sum = (roll_remainder >> 6) << 6;
        roll_remainder = offset_roll_a - offset_sum;
        if (offset_roll_b < 0) {
            biased_roll = offset_roll_b + 63;
        }
        offset_sum = (biased_roll >> 6) << 6;
        offset_sum = roll_remainder + (offset_roll_b - offset_sum) - 64;
        ((S_1 *)part)->unk_02 = spawn_params->unk_02 + offset_sum / 2;
    }
}
'''


class Classic(unittest.TestCase):
    def test_still_matched(self):
        its = M.idioms(CLASSIC)
        self.assertEqual(len(its), 1)
        self.assertEqual(its[0]["n"], 6)
        self.assertEqual(its[0]["vars"], {"x", "q"})
        self.assertEqual(its[0]["full"], its[0]["plain"])                  # nothing to fold
        full = M.spell_all(CLASSIC, its)
        self.assertIn("out[0] = (x % 64);", full)
        self.assertNotIn("if (x < 0)", full)
        modonly = dict(M.spell_one(CLASSIC, its[0]))["modonly"]
        self.assertIn("if (x < 0)", modonly)                               # the bias stays
        self.assertIn("out[0] = (x % 64);", modonly)


class Named(unittest.TestCase):
    def test_two_idioms(self):
        its = M.idioms(NAMED)
        self.assertEqual(len(its), 2)
        a, b = its
        self.assertEqual(a["vars"], {"roll_remainder", "offset_roll_a"})   # the rounded local is NOT a var
        self.assertEqual(b["vars"], {"biased_roll", "offset_roll_b"})      # so the `$2` pin is kept
        self.assertNotIn("offset_sum", a["vars"] | b["vars"])
        self.assertEqual(a["n"], 6)

    def test_fold_and_joint_rewrite(self):
        its = M.idioms(NAMED)
        self.assertNotEqual(its[0]["full"], its[0]["plain"])               # `r = x - s;` reads once below
        self.assertEqual(its[1]["full"], its[1]["plain"])                  # in a larger expression: no fold
        out = M.spell_all(NAMED, its)
        self.assertIn("        offset_sum = (offset_roll_a % 64) + (offset_roll_b % 64) - 64;", out)
        for gone in ("if (offset_roll_a < 0)", "if (offset_roll_b < 0)", "(roll_remainder >> 6) << 6",
                     "(biased_roll >> 6) << 6", "offset_roll_a - offset_sum"):
            self.assertNotIn(gone, out)
        self.assertIn("roll_remainder = offset_roll_a;", out)              # the dead copies are left alone

    def test_nofold_spelling(self):
        its = M.idioms(NAMED)
        spellings = dict(M.spell_one(NAMED, its[0]))
        self.assertIn("roll_remainder = (offset_roll_a % 64);", spellings["nofold"])
        self.assertNotIn("roll_remainder = (offset_roll_a % 64);", spellings["mod"])

    def test_live_rounded_local_refused(self):
        # the rounded value is read again after the remainder: `s = (b >> n) << n;` cannot go, so
        # the first idiom is refused; the second rewrites its own `s` and still matches
        live = NAMED.replace("        roll_remainder = offset_roll_a - offset_sum;",
                             "        roll_remainder = offset_roll_a - offset_sum;\n"
                             "        part = (u8 *)(offset_sum + 1);")
        self.assertEqual([i["d"] for i in M.idioms(live)], ["biased_roll"])

    def test_fold_refused_when_read_twice(self):
        twice = NAMED.replace("offset_sum = roll_remainder + (offset_roll_b - offset_sum) - 64;",
                              "offset_sum = roll_remainder + (offset_roll_b - offset_sum) - roll_remainder;")
        a = M.idioms(twice)[0]
        self.assertEqual(a["full"], a["plain"])                            # two reads in the statement

    def test_eligible(self):
        self.assertIsNone(M.T.eligible(NAMED, {}, {}))
        self.assertEqual(M.T.eligible(CLASSIC, {}, {}), "no live pin site")


if __name__ == "__main__":
    unittest.main()
