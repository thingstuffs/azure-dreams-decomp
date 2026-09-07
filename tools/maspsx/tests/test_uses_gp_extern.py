import unittest

from maspsx import MaspsxProcessor

from .util import strip_comments


class TestUsesGpExtern(unittest.TestCase):
    """
    LEAD 16: `_uses_gp` must consult `extern_sizes` so the load-delay-nop gate
    fires for a store into a small (`<= sdata_limit`) `.extern` global.

    Real `as -G8` emits a single gp-relative `sw` for such an extern, so the
    load->store hazard is genuine and needs a load-delay nop. Previously
    `_uses_gp` only looked at locally-defined `.sbss`/`.sdata` symbols and
    silently dropped the mandatory nop for referenced-only externs.
    """

    def test_small_extern_store_after_load_gets_nop(self):
        lines = [
            "	.extern	D_800814B0,4",
            "	lw	$2,0($2)",
            "	#nop",
            "	sw	$2,D_800814B0",
        ]
        expected_lines = [
            "lw\t$2,0($2)",
            "nop",
            "sw\t$2,D_800814B0",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = mp.process_lines()

        clean_lines = strip_comments(res)
        # drop the passed-through `.extern` directive line
        clean_lines = [l for l in clean_lines if not l.startswith(".extern")]
        self.assertEqual(expected_lines, clean_lines[:3])

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
        clean_lines = [l for l in clean_lines if not l.startswith(".extern")]
        self.assertEqual(expected_lines, clean_lines[:2])

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
        clean_lines = [l for l in clean_lines if not l.startswith(".extern")]
        self.assertEqual(expected_lines, clean_lines[:2])
