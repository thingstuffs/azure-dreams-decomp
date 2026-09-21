"""T88: the cast-scaled flip, its parenthesisation and its erase plans are textual; the listing screen and
`vf` are not exercised (the exemplar row is checked with tools/lanes/gen_drive.py --base-from r62_astra_big)."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t88_castshift as M  # noqa: E402
from pin_census import sites_of  # noqa: E402

HEAD = '#include "common.h"\n\n'


def fn(body, decls="    void *offset_value;\n    void *table_value;\n"):
    return HEAD + "void f(void)\n{\n" + decls + "\n" + body + "}\n"


EXEMPLAR = fn('''    table_value = (void **)&D_8006CCD8;
    ASM_KEEP(offset_value);
    owner_sprite = PTR(owner, -0x14);
    offset_value = (void *)((s32)offset_value * 2);
    offset_value = (u8 *)offset_value + (u32)table_value;
''')


class Flips(unittest.TestCase):
    def test_the_operand_is_taken_with_its_cast(self):
        f = M.flips(EXEMPLAR)
        self.assertEqual(len(f), 1)
        s0, s1, rep, _, x, y = f[0]
        self.assertEqual(EXEMPLAR[s0:s1], "(s32)offset_value * 2")
        self.assertEqual(rep, "(s32)offset_value << 1")      # enclosed by `(void *)(` ... `)`: no parens
        self.assertEqual((x, y), ("offset_value", "offset_value"))

    def test_an_unenclosed_site_is_parenthesised(self):
        t = fn("    ASM_KEEP(offset_value);\n    offset_value = (u8 *)base + (s32)offset_value * 4;\n")
        self.assertEqual(M.flips(t)[0][2], "((s32)offset_value << 2)")

    def test_a_shift_flips_back_to_a_multiply(self):
        t = fn("    ASM_KEEP(offset_value);\n    offset_value = (void *)((u32)offset_value << 4);\n")
        self.assertEqual(M.flips(t)[0][2], "(u32)offset_value * 16")

    def test_a_bare_operand_is_left_to_t35(self):
        self.assertEqual(M.flips(fn("    ASM_KEEP(offset_value);\n    count = count * 2;\n")), [])

    def test_a_non_power_of_two_is_left_alone(self):
        self.assertEqual(M.flips(fn("    ASM_KEEP(offset_value);\n"
                                    "    offset_value = (void *)((s32)offset_value * 12);\n")), [])

    def test_a_scale_inside_a_pin_is_never_touched(self):
        self.assertEqual(M.flips(fn('    ASM_CLOBBER("$3");\n    ASM_KEEP((s32)offset_value * 2);\n')), [])


class Candidates(unittest.TestCase):
    def test_the_flip_is_offered_with_the_window_pin_erased(self):
        cands = M.candidates(EXEMPLAR)
        self.assertTrue(cands)
        for label, c in cands:
            self.assertIn("(s32)offset_value << 1", c)
            self.assertNotIn("* 2", c)
            self.assertLess(len(sites_of(c)), len(sites_of(EXEMPLAR)))
        self.assertTrue(any(l.endswith("|one0") for l, _ in cands), [l for l, _ in cands])

    def test_every_candidate_is_a_distinct_text(self):
        texts = [c for _, c in M.candidates(EXEMPLAR)]
        self.assertEqual(len(texts), len(set(texts)))

    def test_a_row_without_a_pin_in_the_window_offers_nothing(self):
        far = fn("    ASM_KEEP(other);\n" + "    a = 1;\n" * 9 +
                 "    offset_value = (void *)((s32)offset_value * 2);\n")
        self.assertEqual([l for l, _ in M.candidates(far)], [])


class Eligible(unittest.TestCase):
    def test_a_cast_scaled_pinned_row_is_eligible(self):
        self.assertIsNone(M.T.eligible(EXEMPLAR, {}, {}))

    def test_no_pin_is_refused(self):
        self.assertEqual(M.T.eligible(EXEMPLAR.replace("    ASM_KEEP(offset_value);\n", ""), {}, {}),
                         "no pin sites")

    def test_no_cast_scale_is_refused(self):
        self.assertEqual(M.T.eligible(fn("    ASM_KEEP(offset_value);\n    a = b + 1;\n"), {}, {}),
                         "no cast-scaled power of two")


if __name__ == "__main__":
    unittest.main()
