"""T114: the `$0` binding's rewrite is textual; the screen and `vf` are not run."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t114_zeroreg as M  # noqa: E402
from pin_census import sites_of, unscored_text  # noqa: E402

ROW = '''#include "common.h"
s32 f(s32 is_available, s32 mult) {
    s32 mode;
    register s32 zero ASM_REG("$0");   /* UNRESOLVED C shape (pin) */

#ifdef NON_MATCHING
    zero = 0;
#else
#endif
    mode = (u32)zero < (u32)is_available;
    zero = 0;
    return mode + (mult + zero);
}
'''


class TestZero(unittest.TestCase):
    def test_the_binding_is_found(self):
        self.assertEqual(M.zeros(ROW), ["zero"])
        self.assertIsNone(M.T.eligible(ROW, None, {}))

    def test_fold_writes_the_literal_compare_and_drops_the_addend(self):
        c = dict(M.candidates(ROW))["zero:fold"]
        self.assertIn("    mode = is_available != 0;\n", c)
        self.assertIn("    return mode + (mult);\n", c)
        self.assertNotIn("    zero = 0;\n    return", c)
        self.assertEqual(sites_of(c), [])

    def test_the_non_matching_arm_is_untouched(self):
        for _l, c in M.candidates(ROW):
            self.assertEqual(unscored_text(c), unscored_text(ROW))
            self.assertIn("#ifdef NON_MATCHING\n    zero = 0;\n#else", c)
            self.assertIn("    s32 zero;\n", c)

    def test_literal_keeps_the_casts(self):
        c = dict(M.candidates(ROW))["zero:literal"]
        self.assertIn("mode = (u32)0 < (u32)is_available;", c)

    def test_no_zero_register_is_refused(self):
        self.assertIn("ASM_REG", M.T.eligible(ROW.replace('"$0"', '"$2"'), None, {}))


if __name__ == "__main__":
    unittest.main()
