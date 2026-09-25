import unittest

from maspsx import MaspsxProcessor

from .util import strip_comments


class TestFoldSelfincLa(unittest.TestCase):
    """_fold_selfinc_la (LEAD 4): a loop-invariant `%hi(SYM)` base that is
    self-incremented by a constant stride each lap keeps `%hi` only and folds
    `%lo(SYM+off)` into every access. gcc emits `la $R,SYM` (full pointer) with
    0-offset loads and a raw self-increment; retail keeps the `%hi`-only base and
    folds. See func_8004A6C0.
    """

    def test_selfinc_loop_is_folded(self):
        # func_8004A6C0 shape: base $3 = la SYM, two field loads (0/2) through $3,
        # self-incremented by 4 each lap across a label + branch.
        lines = [
            "	la	$3,SYM",
            "	move	$6,$0",
            "$L5:",
            "	lh	$2,0($3)",
            "	bne	$2,$4,$L4",
            "	lh	$2,2($3)",
            "	beq	$2,$5,$L3",
            "$L4:",
            "	addu	$6,$6,1",
            "	slt	$2,$6,20",
            "	bne	$2,$0,$L5",
            "	addu	$3,$3,4",
            "$L3:",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        # la rewritten to a bare %hi; %lo folded into both accesses; self-inc kept.
        self.assertIn("lui\t$3,%hi(SYM)", res)
        self.assertFalse(any(l.startswith("la\t$3") for l in res))
        self.assertIn("lh\t$2,%lo(SYM)($3)", res)
        self.assertIn("lh\t$2,%lo(SYM+2)($3)", res)
        self.assertTrue(any("addu\t$3,$3,4" in l for l in res))

    def test_no_selfinc_is_not_folded(self):
        # A fixed base (no self-increment) is the case _fold_lo_into_accesses guards
        # against: retail keeps the full pointer + numeric offsets. Leave the la.
        lines = [
            "	la	$3,SYM",
            "	lh	$2,0($3)",
            "	lh	$4,2($3)",
            "	jr	$31",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        self.assertTrue(any(l.startswith("la\t$3,SYM") for l in res))
        self.assertFalse(any("%lo(SYM" in l for l in res))

    def test_call_separated_selfinc_loop_keeps_its_seed(self):
        # Historical func_8004AB7C shape: the retired pass used to move the
        # address seed across this call. The current source no longer emits that
        # shape. Keep this synthetic input as an exact pass-through regression.
        lines = [
            "	la	$17,itemCategoryTable",
            "	lw	$4,D_80013628",
            "	jal	func_800A6D98",
            "$L5:",
            "	lbu	$2,1($17)",
            "	lw	$3,D_80012090",
            "	sra	$2,$2,$3",
            "	andi	$2,$2,1",
            "	bne	$2,$0,$L4",
            "	nop",
            "$L4:",
            "	addu	$17,$17,20",
            "	bne	$2,$0,$L5",
            "	nop",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        self.assertEqual(res, [
            "la\t$17,itemCategoryTable",
            "lw\t$4,D_80013628",
            "jal\tfunc_800A6D98",
            "nop",
            "$L5:",
            "lbu\t$2,1($17)",
            "lw\t$3,D_80012090",
            "nop",
            "sra\t$2,$2,$3",
            "andi\t$2,$2,1",
            "bne\t$2,$0,$L4",
            "nop",
            "nop",
            "$L4:",
            "addu\t$17,$17,20",
            "bne\t$2,$0,$L5",
            "nop",
            "nop",
        ])

    def test_value_use_aborts_fold(self):
        # If the base escapes as a value (here `move $5,$3`), folding is unsafe
        # (the full address is needed) -> keep the la, no fold.
        lines = [
            "	la	$3,SYM",
            "$L5:",
            "	lh	$2,0($3)",
            "	move	$5,$3",
            "	addu	$3,$3,4",
            "	bne	$2,$0,$L5",
            "	nop",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        self.assertTrue(any(l.startswith("la\t$3,SYM") for l in res))
        self.assertFalse(any("%lo(SYM" in l for l in res))

    def test_known_small_data_is_not_folded(self):
        # A KNOWN small-data symbol (size <= -G) must NOT have %lo folded into its
        # accesses by _fold_selfinc_la (the accesses stay numeric-offset). Its `la`
        # is instead materialised to a plain %hi/%lo pair by _expand_smalldata_la
        # (with gp_allow_la=False, aspsx never gp-relativizes a `la`), so the field
        # loads keep their numeric offsets rather than being folded to %lo(SMALL+off).
        lines = [
            "	.extern	SMALL, 4",
            "	la	$3,SMALL",
            "$L5:",
            "	lh	$2,0($3)",
            "	addu	$3,$3,4",
            "	bne	$2,$0,$L5",
            "	nop",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        # not FOLDED: the field load keeps its numeric offset, no %lo(SMALL+off)
        # folded into the access displacement (the only %lo is in the expanded la).
        self.assertFalse(any(l.startswith("lh\t$2,%lo(SMALL") for l in res))
        self.assertTrue(any("lh\t$2,0($3)" in l for l in res))

    def test_indexed_advance_aborts_fold(self):
        # A register-register advance (`addu $3,$3,$7`) is not a constant stride;
        # the folded %hi-only base would be wrong -> abort.
        lines = [
            "	la	$3,SYM",
            "$L5:",
            "	lh	$2,0($3)",
            "	addu	$3,$3,$7",
            "	bne	$2,$0,$L5",
            "	nop",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        self.assertTrue(any(l.startswith("la\t$3,SYM") for l in res))
        self.assertFalse(any("%lo(SYM" in l for l in res))


if __name__ == "__main__":
    unittest.main()
