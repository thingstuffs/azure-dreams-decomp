"""tools/fidelity/cell_retail_check.py: the trial-cfg rewrite, the genuine retail-exactness rule (never
aspsx_diff's `exact_versions` alone - that is genuine == maspsx) and the positional word differences."""
import re
import struct
import sys
import types
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/fidelity"))
sys.path.insert(0, str(ROOT / "tools"))
import cell_retail_check as C  # noqa: E402


class TrialCfg(unittest.TestCase):
    def test_cell_replaced_flags_kept(self):
        self.assertEqual(C.trial_cfg("2.8.0-G0", "2.7.2-cdk"), "2.7.2-cdk-G0")
        self.assertEqual(C.trial_cfg("2.6.3-G0", "2.7.2-cdk"), "2.7.2-cdk-G0")
        self.assertEqual(C.trial_cfg("2.7.2-G0 -fno-schedule-insns", "2.7.2-cdk"), "2.7.2-cdk-G0 -fno-schedule-insns")
        self.assertEqual(C.trial_cfg("2.95.2-G0 -fno-expensive-optimizations", "2.7.2-cdk"),
                         "2.7.2-cdk-G0 -fno-expensive-optimizations")
        self.assertEqual(C.trial_cfg("2.8.1", "2.7.2-cdk"), "2.7.2-cdk")
        self.assertEqual(C.trial_cfg("2.7.2-cdk -G0 -fno-schedule-insns -fforce-addr", "2.8.0"),
                         "2.8.0-G0 -fno-schedule-insns -fforce-addr")

    def test_plus_dialect(self):
        self.assertEqual(C.trial_cfg("2.8.1+-G0 -fno-cse-follow-jumps", "2.7.2-cdk"), "2.7.2-cdk-G0 -fno-cse-follow-jumps")


class GenuineExact(unittest.TestCase):
    def test_equal_to_a_non_exact_maspsx_leg_is_not_exact(self):
        # the cdk35 case: every genuine version == maspsx, both 2 words off retail
        gr = {v: [2, 0] for v in ("2.67", "2.77", "2.79")}
        self.assertFalse(C.genuine_retail_exact(False, ["2.67", "2.77", "2.79"], gr))

    def test_clean_zero(self):
        self.assertTrue(C.genuine_retail_exact(False, [], {"2.79": [0, 0]}))

    def test_masked_needs_an_exact_maspsx_leg_it_equals(self):
        self.assertTrue(C.genuine_retail_exact(True, ["2.79"], {"2.79": [0, 3]}))
        self.assertFalse(C.genuine_retail_exact(True, [], {"2.79": [0, 3]}))
        self.assertFalse(C.genuine_retail_exact(False, ["2.79"], {"2.79": [0, 3]}))


class Positions(unittest.TestCase):
    def test_masked_skipped_and_length_mismatch(self):
        A = types.SimpleNamespace(NAME_ADDR=re.compile(r"^func_([0-9A-F]{8})$"))
        A.resolve_tokens = lambda view, f, base, addr_of, gp, slice_base=None, layout=None: ([1, 2, 3, 4], {1})
        view = types.SimpleNamespace(funcs={"f": None}, unit_layout=lambda f: {})
        retail = struct.pack("<3I", 1, 9, 7)
        ctx = {"retail": retail, "link_vram": 0x80100000, "gp": 0}
        # word 1 masked (9 != 2 ignored), word 2 differs, word 3 has no retail counterpart
        self.assertEqual(C._positions(view, "f", ctx, A), [[2, 3, 7], [3, 4, None]])
        self.assertIsNone(C._positions(view, "g", ctx, A))


if __name__ == "__main__":
    unittest.main()
