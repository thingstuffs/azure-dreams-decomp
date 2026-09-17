"""Focused regression coverage for compiler-lineage fingerprinting."""
from pathlib import Path
import struct
import sys
import unittest
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import lineage_fingerprint as fingerprint


def words(*values):
    return b"".join(struct.pack("<I", value) for value in values)


JAL_ZERO = 0x0C000000
SW_V0_0_S0 = 0xAE020000
LUI_V1_8001 = 0x3C038001
SW_A0_20_V1 = 0xAC640020


class LineageFingerprintTests(unittest.TestCase):
    def test_object_local_store_in_call_slot_is_family_neutral(self):
        _ins, evidence, _held, _gp = fingerprint.scan(
            words(JAL_ZERO, SW_V0_0_S0))

        self.assertEqual(len(evidence["slot_store"]), 1)
        self.assertEqual(evidence["split_store"], [])
        decision = fingerprint.classify(evidence)
        self.assertIsNone(decision.family)
        self.assertIn("insufficient", decision.verdict)
        self.assertIn("family-neutral", " ".join(decision.notes))

    def test_compiler_split_global_store_retains_family_evidence(self):
        _ins, evidence, _held, _gp = fingerprint.scan(
            words(LUI_V1_8001, SW_A0_20_V1))

        self.assertEqual(len(evidence["split_store"]), 1)
        decision = fingerprint.classify(evidence)
        self.assertEqual(decision.family, fingerprint.FAMILY_B)

    def test_body_slice_excludes_data_prefix_from_classification(self):
        raw = words(LUI_V1_8001, SW_A0_20_V1, JAL_ZERO, SW_V0_0_S0)
        _ins, whole_evidence, _held, _gp = fingerprint.scan(raw)
        self.assertEqual(fingerprint.classify(whole_evidence).family,
                         fingerprint.FAMILY_B)

        body = fingerprint.body_slice(raw, offset=8)
        self.assertEqual(body, raw[8:])
        _ins, body_evidence, _held, _gp = fingerprint.scan(body)
        self.assertEqual(len(body_evidence["slot_store"]), 1)
        self.assertIsNone(fingerprint.classify(body_evidence).family)

        prefix_only = fingerprint.body_slice(raw, size=8)
        self.assertEqual(prefix_only, raw[:8])
        _ins, prefix_evidence, _held, _gp = fingerprint.scan(prefix_only)
        self.assertEqual(fingerprint.classify(prefix_evidence).family,
                         fingerprint.FAMILY_B)

    def test_body_slice_rejects_invalid_ranges(self):
        raw = words(0, 0)
        invalid = ((2, None), (0, 2), (-4, None), (0, -4), (12, None), (4, 8))
        for offset, size in invalid:
            with self.subTest(offset=offset, size=size):
                with self.assertRaises(ValueError):
                    fingerprint.body_slice(raw, offset=offset, size=size)

    def test_overlay_is_required_before_ledger_lookup(self):
        with mock.patch.object(fingerprint, "rows") as ledger_rows:
            with self.assertRaisesRegex(ValueError, "--overlay is required"):
                fingerprint.resolve_target("func_80000000")
            ledger_rows.assert_not_called()


if __name__ == "__main__":
    unittest.main()
