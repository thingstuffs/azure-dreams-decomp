import unittest

from maspsx import MaspsxProcessor

from .util import strip_comments


class TestFoldLoReuseGuard(unittest.TestCase):
    """LEAD F3: narrowing _fold_lo_into_accesses' raw-base reuse guard.

    The guard exists for cases where gcc reuses or restores the %hi seed
    register after the indexed base has been formed. A later epilogue move into
    the return register is not that case and must not block the fold.
    """

    def test_epilogue_return_move_does_not_block_fold(self):
        lines = [
            "	lui	$2,%hi(SYM)",
            "	addiu	$2,$2,%lo(SYM)",
            "	sll	$3,$4,2",
            "	addu	$3,$3,$2",
            "	sh	$17,0($3)",
            "	sh	$18,2($3)",
            "	move	$2,$16",
            "	lw	$31,28($sp)",
            "	jr	$31",
            "	nop",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        self.assertNotIn("addiu\t$2,$2,%lo(SYM)", res)
        self.assertIn("sh\t$17,%lo(SYM)($3)", res)
        self.assertIn("sh\t$18,%lo(SYM+2)($3)", res)
        self.assertIn("addu\t$2,$16,$zero", res)

    def test_epilogue_return_addu_zero_does_not_block_fold(self):
        lines = [
            "	lui	$2,%hi(SYM)",
            "	addiu	$2,$2,%lo(SYM)",
            "	sll	$3,$4,2",
            "	addu	$3,$3,$2",
            "	sh	$17,0($3)",
            "	sh	$18,2($3)",
            "	addu	$2,$16,$0",
            "	lw	$31,28($sp)",
            "	lw	$18,24($sp)",
            "	lw	$17,20($sp)",
            "	lw	$16,16($sp)",
            "	addiu	$sp,$sp,32",
            "	jr	$31",
            "	nop",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        self.assertNotIn("addiu\t$2,$2,%lo(SYM)", res)
        self.assertIn("sh\t$17,%lo(SYM)($3)", res)
        self.assertIn("sh\t$18,%lo(SYM+2)($3)", res)
        self.assertIn("addu\t$2,$16,$0", res)

    def test_store_data_reuse_still_blocks_fold(self):
        lines = [
            "	lui	$3,%hi(SYM)",
            "	addiu	$3,$3,%lo(SYM)",
            "	sll	$2,$4,1",
            "	addu	$2,$2,$4",
            "	sll	$2,$2,2",
            "	addu	$2,$2,$3",
            "	li	$3,127",
            "	sh	$3,10($2)",
            "	sh	$3,8($2)",
            "	li	$3,2",
            "	sh	$3,2($2)",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        self.assertIn("addiu\t$3,$3,%lo(SYM)", res)
        self.assertIn("sh\t$3,10($2)", res)
        self.assertIn("sh\t$3,8($2)", res)
        self.assertFalse(any("%lo(SYM" in line and line.startswith("sh") for line in res))

    def test_raw_base_restore_still_blocks_fold(self):
        lines = [
            "	lui	$17,%hi(SYM)",
            "	addiu	$17,$17,%lo(SYM)",
            "	sll	$2,$4,2",
            "	addu	$2,$2,$17",
            "	sh	$0,0($2)",
            "	sh	$0,2($2)",
            "	lw	$17,20($sp)",
            "	jr	$31",
            "	nop",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        self.assertIn("addiu\t$17,$17,%lo(SYM)", res)
        self.assertIn("sh\t$0,0($2)", res)
        self.assertIn("sh\t$0,2($2)", res)

    def test_raw_base_ordinary_reuse_still_blocks_fold(self):
        lines = [
            "	lui	$5,%hi(SYM)",
            "	addiu	$5,$5,%lo(SYM)",
            "	sll	$2,$4,3",
            "	addu	$2,$2,$5",
            "	sw	$6,0($2)",
            "	sh	$7,6($2)",
            "	addiu	$5,$4,5",
            "	jr	$31",
            "	nop",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        self.assertIn("addiu\t$5,$5,%lo(SYM)", res)
        self.assertIn("sw\t$6,0($2)", res)
        self.assertIn("sh\t$7,6($2)", res)

    def test_indexed_base_crossing_call_still_blocks_fold(self):
        lines = [
            "	lui	$2,%hi(SYM)",
            "	addiu	$2,$2,%lo(SYM)",
            "	sll	$16,$3,2",
            "	addu	$16,$16,$2",
            "	lh	$3,0($16)",
            "	jal	func_80000000",
            "	nop",
            "	sh	$4,2($16)",
            "	lw	$16,16($sp)",
            "	jr	$31",
            "	nop",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        self.assertIn("addiu\t$2,$2,%lo(SYM)", res)
        self.assertIn("lh\t$3,0($16)", res)
        self.assertIn("sh\t$4,2($16)", res)

    def test_callee_saved_restore_of_indexed_base_does_not_block_fold(self):
        lines = [
            "	lui	$2,%hi(SYM)",
            "	addiu	$2,$2,%lo(SYM)",
            "	sll	$16,$3,2",
            "	addu	$16,$16,$2",
            "	sh	$0,0($16)",
            "	sh	$0,2($16)",
            "	lw	$16,16($sp)",
            "	lw	$31,20($sp)",
            "	jr	$31",
            "	nop",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        self.assertNotIn("addiu\t$2,$2,%lo(SYM)", res)
        self.assertIn("sh\t$0,%lo(SYM)($16)", res)
        self.assertIn("sh\t$0,%lo(SYM+2)($16)", res)
        self.assertIn("lw\t$16,16($sp)", res)


if __name__ == "__main__":
    unittest.main()
