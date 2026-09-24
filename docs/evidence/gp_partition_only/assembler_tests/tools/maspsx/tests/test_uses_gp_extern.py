import unittest

from maspsx import MaspsxProcessor

from .util import strip_comments


class TestUsesGpExtern(unittest.TestCase):
    """
    A locally owned small-data store is one GP-relative instruction and needs
    the load-delay nop. A true external is absolute in genuine ASPSX even with
    -G8, so its store macro has no adjacent GP hazard.
    """

    def test_small_external_store_after_load_has_no_artificial_nop(self):
        lines = [
            "	.extern	D_800814B0,4",
            "	lw	$2,0($2)",
            "	#nop",
            "	sw	$2,D_800814B0",
        ]
        expected_lines = [
            "lw\t$2,0($2)",
            "sw\t$2,D_800814B0",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = mp.process_lines()

        clean_lines = strip_comments(res)
        self.assertEqual(expected_lines, clean_lines)

    def test_locally_owned_small_store_after_load_gets_nop(self):
        lines = [
            "\t.comm\tD_800814B0,4",
            "\tlw\t$2,0($2)",
            "\t#nop",
            "\tsw\t$2,D_800814B0",
        ]
        clean_lines = strip_comments(MaspsxProcessor(lines, sdata_limit=8).process_lines())
        self.assertEqual([
            "lw\t$2,0($2)",
            "nop",
            "sw\t$2,%gp_rel(D_800814B0)($gp)",
            ".section .sbss",
            ".align 2",
            "D_800814B0:",
            ".space 4",
        ], clean_lines)

    def test_large_extern_store_after_load_no_nop(self):
        lines = [
            "	.extern	D_800814B0,16",
            "	lw	$2,0($2)",
            "	#nop",
            "	sw	$2,D_800814B0",
        ]
        expected_lines = [
            "lw\t$2,0($2)",
            "sw\t$2,D_800814B0",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = mp.process_lines()

        clean_lines = strip_comments(res)
        self.assertEqual(expected_lines, clean_lines)

    def test_unknown_extern_store_after_load_no_nop(self):
        """A symbol with no known size (never declared) must stay unchanged."""
        lines = [
            "	lw	$2,0($2)",
            "	#nop",
            "	sw	$2,D_UNKNOWN",
        ]
        expected_lines = [
            "lw\t$2,0($2)",
            "sw\t$2,D_UNKNOWN",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = mp.process_lines()

        clean_lines = strip_comments(res)
        self.assertEqual(expected_lines, clean_lines[:2])

    def test_small_extern_no_gp_when_sdata_limit_zero(self):
        """With sdata_limit=0 (-G0) there is no $gp window: no nop from this path."""
        lines = [
            "	.extern	D_800814B0,4",
            "	lw	$2,0($2)",
            "	#nop",
            "	sw	$2,D_800814B0",
        ]
        expected_lines = [
            "lw\t$2,0($2)",
            "sw\t$2,D_800814B0",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=0)
        res = mp.process_lines()

        clean_lines = strip_comments(res)
        self.assertEqual(expected_lines, clean_lines)
