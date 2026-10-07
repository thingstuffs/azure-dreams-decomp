import unittest

from maspsx import MaspsxProcessor

from .util import strip_comments


class TestPreserveCompilerBranchDelay(unittest.TestCase):
    def _run(self, lines):
        mp = MaspsxProcessor(lines, sdata_limit=8)
        return strip_comments(mp.process_lines())

    def test_preserves_shift_in_branch_delay_as_genuine_aspsx(self):
        lines = [
            ".extern	D_80083D08, 48",
            ".set	noreorder",
            "bne	$4,$2,$L2",
            "sll	$4,$4,3",
            "j	$L3",
            "addu	$2,$0,$zero",
            "$L2:",
            "la	$2,D_80083D08",
            "addu	$4,$4,$2",
            "lhu	$3,4($4)",
            "$L3:",
        ]
        # Genuine ASPSX preserves the compiler's explicit branch slot.
        expected = lines[2:]
        self.assertEqual(expected, self._run(lines))

    def test_not_applied_when_fallthrough_uses_lui_register(self):
        lines = [
            ".extern	D_80083D08, 48",
            ".set	noreorder",
            "bne	$4,$2,$L2",
            "sll	$4,$4,3",
            "j	$L3",
            "addu	$3,$2,$zero",
            "$L2:",
            "la	$2,D_80083D08",
            "addu	$4,$4,$2",
        ]
        clean = self._run(lines)
        self.assertIn("sll	$4,$4,3", clean)
        self.assertIn("la	$2,D_80083D08", clean)
        self.assertNotIn("lui	$2,%hi(D_80083D08)", clean)

    def test_not_applied_without_fallthrough_jump(self):
        lines = [
            ".extern	D_80083D08, 48",
            ".set	noreorder",
            "bne	$4,$2,$L2",
            "sll	$4,$4,3",
            "addu	$2,$0,$zero",
            "$L2:",
            "la	$2,D_80083D08",
            "addu	$4,$4,$2",
        ]
        clean = self._run(lines)
        self.assertIn("sll	$4,$4,3", clean)
        self.assertIn("la	$2,D_80083D08", clean)
        self.assertNotIn("lui	$2,%hi(D_80083D08)", clean)

    def test_not_applied_when_addu_does_not_consume_shifted_index(self):
        lines = [
            ".extern	D_80083D08, 48",
            ".set	noreorder",
            "bne	$4,$2,$L2",
            "sll	$4,$4,3",
            "j	$L3",
            "addu	$2,$0,$zero",
            "$L2:",
            "la	$2,D_80083D08",
            "addu	$5,$5,$2",
        ]
        clean = self._run(lines)
        self.assertIn("sll	$4,$4,3", clean)
        self.assertIn("la	$2,D_80083D08", clean)
        self.assertNotIn("lui	$2,%hi(D_80083D08)", clean)


if __name__ == "__main__":
    unittest.main()
