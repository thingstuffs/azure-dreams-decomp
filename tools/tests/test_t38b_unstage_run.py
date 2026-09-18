"""T38b: the staging-run finder and the inliner are textual; the order search and `vf` are not exercised here."""
import os
import sys
import unittest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform"))
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t38b_unstage_run as M  # noqa: E402

TEXT = """#include "common.h"
void f(u8 *packet, s32 texture_u) {
    s32 texture_v;
    register s16 texture_id ASM_REG("$2");
    texture_id = 0x7DCF;
    texture_v = 0x40;
    ASM_KEEP_NV(texture_v);
    *(s16 *)(packet + 0xE) = texture_id;
    *(u8 *)(packet + 0x18) = texture_u | 7;
    *(u8 *)(packet + 0xD) = texture_v;
    *(u8 *)(packet + 0x19) = texture_v;
    g(packet);
}
"""


class Runs(unittest.TestCase):
    def test_run_found_with_interleaved_store_and_keep(self):
        rs = M.runs(TEXT)
        self.assertEqual(len(rs), 1)
        a, b, stages = rs[0]
        self.assertEqual(set(stages), {"texture_id", "texture_v"})
        self.assertEqual(stages["texture_id"][0], "0x7DCF")
        self.assertEqual(len(stages["texture_v"][2]), 2)           # stored twice

    def test_reassignment_ends_the_run(self):
        t = TEXT.replace("    *(u8 *)(packet + 0xD) = texture_v;", "    texture_v = 1;\n    *(u8 *)(packet + 0xD) = texture_v;")
        a, b, stages = M.runs(t)[0]
        self.assertNotIn("texture_v", stages)                      # the first staging of texture_v has no store before the reassignment

    def test_later_read_refuses(self):
        t = TEXT.replace("    g(packet);", "    g(packet, texture_id);")
        a, b, stages = M.runs(t)[0]
        self.assertNotIn("texture_id", stages)

    def test_inline(self):
        run = M.runs(TEXT)[0]
        out = M.inline_run(TEXT, run, ["texture_id", "texture_v"])
        self.assertIn("*(s16 *)(packet + 0xE) = 0x7DCF;", out)
        self.assertIn("*(u8 *)(packet + 0xD) = 0x40;", out)
        self.assertIn("*(u8 *)(packet + 0x19) = 0x40;", out)
        self.assertNotIn("texture_id = 0x7DCF;", out)
        self.assertNotIn("texture_v = 0x40;", out)
        self.assertIn("*(u8 *)(packet + 0x18) = texture_u | 7;", out)

    def test_candidates_drop_pins(self):
        cands = M.candidates(TEXT)
        self.assertTrue(cands)
        self.assertTrue(all("ASM_KEEP_NV(texture_v)" not in t or "ASM_REG" not in t for _, t in cands))


if __name__ == "__main__":
    unittest.main()
