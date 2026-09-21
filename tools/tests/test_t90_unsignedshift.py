"""T90c: the mask-range argument and the respelling are textual; the listing screen and `vf` are
not exercised."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t90_unsignedshift as M  # noqa: E402

MASKED = '''#include "common.h"
void f(void *actor) {
    register s32 heading_byte ASM_REG("$19");   /* UNRESOLVED C shape (pin) */
    s32 heading_raw;
    s32 direction_offset;

    heading_raw = ((S_0 *)actor)->unk_2A.s;
    heading_byte = heading_raw >> 8;
    direction_offset = heading_byte & 0xE;
    D_80020090 = direction_offset;
}
'''

WIDEMASK = MASKED.replace("heading_byte & 0xE", "heading_byte & 0x7FFFFFF")

PLAINREAD = MASKED.replace("direction_offset = heading_byte & 0xE;",
                           "direction_offset = heading_byte + 1;")

ALREADY = '''#include "common.h"
void g(void *actor) {
    register s32 heading_byte ASM_REG("$19");   /* UNRESOLVED C shape (pin) */
    u32 heading_raw;
    s32 direction_offset;

    heading_raw = ((S_0 *)actor)->unk_2A.s;
    heading_byte = heading_raw >> 8;
    direction_offset = heading_byte & 0xE;
    D_80020090 = direction_offset;
}
'''

VARSHIFT = MASKED.replace("heading_raw >> 8", "heading_raw >> direction_offset")


def labels(text):
    return [c[0] for c in M.candidates(text)]


class TestRespell(unittest.TestCase):
    def test_the_mask_only_definition_is_offered(self):
        self.assertIn("ushift:heading_byte>>8>u32@8", labels(MASKED))

    def test_both_spellings_are_offered_for_a_bare_name(self):
        self.assertEqual(sorted(labels(MASKED)),
                         ["ushift:heading_byte>>8>u32@8", "ushift:heading_byte>>8>unsigned@8"])

    def test_the_cast_lands_on_the_operand(self):
        cand = dict((c[0], c[1]) for c in M.candidates(MASKED))["ushift:heading_byte>>8>u32@8"]
        self.assertIn("    heading_byte = (u32)heading_raw >> 8;\n", cand)
        self.assertIn("    direction_offset = heading_byte & 0xE;\n", cand)

    def test_the_pin_is_left_for_the_erase_plan(self):
        for _, cand, _, _ in M.candidates(MASKED):
            self.assertIn('ASM_REG("$19")', cand)


class TestRefusals(unittest.TestCase):
    def test_a_mask_reaching_the_sign_extended_bits_is_refused(self):
        self.assertEqual(labels(WIDEMASK), [])

    def test_a_read_that_is_not_a_mask_is_refused(self):
        self.assertEqual(labels(PLAINREAD), [])

    def test_an_already_unsigned_operand_is_refused(self):
        self.assertEqual(labels(ALREADY), [])

    def test_a_shift_by_a_name_is_refused(self):
        self.assertEqual(labels(VARSHIFT), [])

    def test_eligible_needs_pins(self):
        self.assertEqual(M.T.eligible("void f(void) {}\n", {}, {}), "no pins")

    def test_eligible_accepts_the_exemplar_shape(self):
        self.assertIsNone(M.T.eligible(MASKED, {}, {}))


class TestMaskReader(unittest.TestCase):
    def test_a_single_masked_mention_is_read(self):
        self.assertEqual(M._mask_read("    y = v & 0xE;", "v"), 0xE)

    def test_two_mentions_on_one_line_are_refused(self):
        self.assertIsNone(M._mask_read("    y = (v & 0xE) + v;", "v"))

    def test_a_member_of_the_same_name_is_not_a_mention(self):
        self.assertIsNone(M._mask_read("    y = p->v & 0xE;", "v"))


if __name__ == "__main__":
    unittest.main()
