"""T71: the update-after-call move finds the probe shape, refuses every unsafe move, and its rewrite keeps
the statements' order and erases only pins.  Textual tests (no compiler): `vf` is a stub that accepts a
named candidate.
"""
import os
import sys
import unittest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform"))
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t71_updateaftercall as M  # noqa: E402
from pin_census import sites_of  # noqa: E402

PROBE = """#include "common.h"
extern s32 func_80024610(void *, void *, void *, s32, s32, s32 *, u8, s32);
extern s32 func_80064584();

s32 func_818B1334(void *source, u16 *target, void *context) {
    s32 circle_values[34];
    s16 radius;
    s32 entry_angle;
    s32 entry_index;
    u16 angle_offset;
    void *offset_cursor;
    void *source_arg;

    entry_index = 0;
    offset_cursor = source;
    do {
        radius = 0x20;
        func_80064584(entry_index << 0xA);
        source_arg = source;
        ASM_KEEP(source_arg);   /* UNRESOLVED C shape (pin) */
        angle_offset = *(u16 *)((u8 *)offset_cursor + 0x1A);
        offset_cursor += 2;
        entry_angle = entry_index << 0x11;
        entry_index += 1;
        func_80024610(source_arg, target, context, radius, (s32) (s16) (target[5] - angle_offset), circle_values, 0xFF, entry_angle >> 0x10);
    } while (entry_index < 8);
    return 0;
}
"""


class Sites(unittest.TestCase):
    def test_probe_shape(self):
        sites = M.sites_in(PROBE)
        self.assertEqual(len(sites), 1)
        i, j, updates, ind = sites[0]
        self.assertEqual(i, j)
        self.assertEqual([v for _, v in updates], ["offset_cursor", "entry_index"])
        self.assertTrue(PROBE.split("\n")[i].lstrip().startswith("func_80024610("))

    def test_named_in_call_refused(self):
        t = PROBE.replace("entry_angle >> 0x10);", "entry_angle >> 0x10, entry_index);")
        self.assertEqual([v for _, v in M.sites_in(t)[0][2]], ["offset_cursor"])

    def test_named_between_refused(self):
        t = PROBE.replace("        entry_angle = entry_index << 0x11;\n        entry_index += 1;",
                          "        entry_index += 1;\n        entry_angle = entry_index << 0x11;")
        self.assertEqual([v for _, v in M.sites_in(t)[0][2]], ["offset_cursor"])

    def test_global_and_address_taken_refused(self):
        t = PROBE.replace("    void *offset_cursor;\n", "")                           # a global now
        self.assertEqual([v for _, v in M.sites_in(t)[0][2]], ["entry_index"])
        t = PROBE.replace("radius = 0x20;", "radius = (s32) &entry_index;")
        self.assertEqual([v for _, v in M.sites_in(t)[0][2]], ["offset_cursor"])

    def test_unbraced_control_body_refused(self):
        t = PROBE.replace("        entry_index += 1;", "        if (radius)\n            entry_index += 1;")
        self.assertEqual(M.sites_in(t), [])                       # the scan stops at the unbraced body

    def test_variable_operand(self):
        t = PROBE.replace("offset_cursor += 2;", "offset_cursor += radius;")
        self.assertEqual([v for _, v in M.sites_in(t)[0][2]], ["offset_cursor", "entry_index"])
        t2 = t.replace("        entry_angle = entry_index << 0x11;", "        entry_angle = entry_index << 0x11;\n        radius = 3;")
        self.assertEqual([v for _, v in M.sites_in(t2)[0][2]], ["entry_index"])


class Rewrite(unittest.TestCase):
    def test_rewrite_and_erase(self):
        site = M.sites_in(PROBE)[0]
        moved = M.rewrite(PROBE, site, site[2])
        lines = moved.split("\n")
        k = next(n for n, l in enumerate(lines) if l.lstrip().startswith("func_80024610("))
        self.assertEqual(lines[k + 1].strip(), "offset_cursor += 2;")
        self.assertEqual(lines[k + 2].strip(), "entry_index += 1;")
        self.assertEqual(lines[k - 1].strip(), "entry_angle = entry_index << 0x11;")
        self.assertEqual(sorted(moved.split("\n")), sorted(PROBE.split("\n")))      # a permutation of lines

    def test_apply_verified_accepts_named_candidate(self):
        def vf(cand, cfg=None):
            ls = cand.split("\n")
            k = [n for n, l in enumerate(ls) if l.lstrip().startswith("func_80024610(")]
            return {"exact": "ASM_KEEP" not in cand and bool(k) and ls[k[0] + 2].strip() == "entry_index += 1;"}
        new, info = M.T.apply_verified(PROBE, {"id": "x"}, {}, vf)
        self.assertIsNotNone(new)
        self.assertEqual(len(sites_of(new)), 0)
        self.assertEqual(info["pins_out"], 0)
        self.assertTrue(info["step"].startswith("all:"))
        self.assertIsNone(M.T.eligible(PROBE, {"id": "x"}, {}))
        self.assertEqual(M.T.eligible(new, {"id": "x"}, {}), "no pins")


if __name__ == "__main__":
    unittest.main()
