"""LEAD 2/4 guard #6: the six confirmed %lo-fold MISCOMPILE shapes.

Audit: ``work/town_100_20260812/maspsx_lo_fold_audit/`` (2026-08-12), fix staged
at ``work/maspsx_fix_20260814/``.  Both folds delete the materialisation of the
full base (``addiu $R,$R,%lo(SYM)`` for ``_fold_lo_into_accesses``, the whole
``la $R,SYM`` -> ``lui`` for ``_fold_selfinc_la``) and move ``%lo`` into each
access displacement.  That is only arithmetically neutral when EVERY reachable
access through the base gets the ``%lo``.  The invariant every test below checks
is therefore the same one:

    the base materialisation is deleted  ==>  no access through that base (or
    through a copy of it) may keep a numeric displacement.

Each shape violated it in a different way; all six were reproduced against the
live toolchain before the fix.  Four are the audit's ``repro/{b,c,d,e}.s``; the
last two are straight-line probes (no control-flow join needed at all).
"""

import unittest

from maspsx import MaspsxProcessor

from .util import strip_comments


def run(lines):
    return strip_comments(MaspsxProcessor(list(lines), sdata_limit=8).process_lines())


class TestFoldLoMiscompileGuards(unittest.TestCase):

    def assert_declined(self, res, kept, numeric):
        """The materialisation `kept` survived and `numeric` accesses stayed numeric."""
        self.assertIn(kept, res, f"base materialisation was deleted: {res}")
        for line in numeric:
            self.assertIn(line, res, f"access lost its numeric displacement: {res}")
        folded = [l for l in res if "%lo(SYM" in l and not l.startswith(("lui", "addiu", "la"))]
        self.assertEqual([], folded, f"%lo folded into an access despite the guard: {res}")

    def test_read_of_the_base_does_not_untag_it(self):
        # repro/b.s -- WORST shape: `bgez $3,$L1` merely READS the base, but the
        # untag logic treated operand 1 of any instruction as a destination, so $3
        # lost its tag. The addiu was deleted and `lh $7,4($3)` / `lh $8,6($3)`
        # kept numeric offsets -> wrong address on EVERY path, no join required.
        lines = [
            "	.ent	test",
            "test:",
            "	lui	$3,%hi(SYM)",
            "	addiu	$3,$3,%lo(SYM)",
            "	sll	$2,$4,2",
            "	addu	$3,$2,$3",
            "	lh	$5,0($3)",
            "	lh	$6,2($3)",
            "	bgez	$3,$L1",
            "	nop",
            "	lh	$7,4($3)",
            "$L1:",
            "	lh	$8,6($3)",
            "	jr	$31",
            "	nop",
            "	.end	test",
        ]
        self.assert_declined(run(lines), "addiu\t$3,$3,%lo(SYM)",
                             ["lh\t$5,0($3)", "lh\t$6,2($3)",
                              "lh\t$7,4($3)", "lh\t$8,6($3)"])

    def test_redefinition_jumped_around_by_a_branch_does_not_end_the_live_range(self):
        # repro/c.s (the origin receipt shape, func_8095563C) -- JOIN BYPASS: the
        # base IS linearly redefined (`lw $3,0($10)`) so a plain "dead after the
        # last folded access" rule accepts the fold, but `bgez $5,$L1` jumps AROUND
        # that redefinition and `lh $8,6($3)` at $L1 still reads the old base.
        lines = [
            "	.ent	t2",
            "t2:",
            "	lui	$3,%hi(SYM)",
            "	addiu	$3,$3,%lo(SYM)",
            "	sll	$2,$4,2",
            "	addu	$3,$2,$3",
            "	lh	$5,0($3)",
            "	lh	$6,2($3)",
            "	bgez	$5,$L1",
            "	nop",
            "	lw	$3,0($10)",
            "	sw	$3,4($10)",
            "	j	$L2",
            "	nop",
            "$L1:",
            "	lh	$8,6($3)",
            "$L2:",
            "	jr	$31",
            "	nop",
            "	.end	t2",
        ]
        self.assert_declined(run(lines), "addiu\t$3,$3,%lo(SYM)",
                             ["lh\t$5,0($3)", "lh\t$6,2($3)", "lh\t$8,6($3)"])

    def test_copy_of_the_base_after_a_bypassed_redefinition_is_not_invisible(self):
        # repro/d.s -- COPY AFTER UNTAG: same bypassed redefinition, but the
        # surviving read goes through a COPY (`addu $9,$3,$0`) made on the branch
        # arm. A liveness rule that only follows the base register by name misses
        # it; the copy is a mention of a live carrier, so the fold must decline.
        lines = [
            "	.ent	t3",
            "t3:",
            "	lui	$3,%hi(SYM)",
            "	addiu	$3,$3,%lo(SYM)",
            "	sll	$2,$4,2",
            "	addu	$3,$2,$3",
            "	lh	$5,0($3)",
            "	lh	$6,2($3)",
            "	bgez	$5,$L1",
            "	nop",
            "	lw	$3,0($10)",
            "	j	$L2",
            "	nop",
            "$L1:",
            "	addu	$9,$3,$0",
            "	lh	$8,6($9)",
            "$L2:",
            "	jr	$31",
            "	nop",
            "	.end	t3",
        ]
        self.assert_declined(run(lines), "addiu\t$3,$3,%lo(SYM)",
                             ["lh\t$5,0($3)", "lh\t$6,2($3)", "lh\t$8,6($9)"])

    def test_selfinc_redefinition_jumped_around_by_a_branch_declines(self):
        # repro/e.s -- LEAD 4, same class and strictly worse: _fold_selfinc_la has
        # no join guard at all, and its case (c) ("a plain redefinition of $R ends
        # the live range") exited with safe=True. `bgez $5,$L1` skips the
        # redefinition and `lh $8,2($3)` at $L1 reads a base the fold has already
        # demoted to %hi-only. The `la` must survive.
        lines = [
            "	.ent	t4",
            "t4:",
            "	la	$3,SYM",
            "$L0:",
            "	lh	$5,0($3)",
            "	addu	$3,$3,4",
            "	bgez	$5,$L1",
            "	nop",
            "	lw	$3,0($10)",
            "	j	$L2",
            "	nop",
            "$L1:",
            "	lh	$8,2($3)",
            "$L2:",
            "	jr	$31",
            "	nop",
            "	.end	t4",
        ]
        res = run(lines)
        self.assert_declined(res, "la\t$3,SYM", ["lh\t$5,0($3)", "lh\t$8,2($3)"])
        self.assertFalse(any(l.startswith("lui\t$3,%hi(SYM)") for l in res),
                         f"seed la was demoted to a bare %hi base: {res}")

    def test_access_that_overwrites_its_own_base_is_not_folded_through(self):
        # STRAIGHT-LINE probe 4a (SELF-OVERWRITE): the access-rewrite branch ended
        # in `continue`, skipping the untag/value-use guards, so `lw $3,0($3)` left
        # $3 tagged even though it now holds a LOADED VALUE. The next access was
        # then folded onto that value: `lw $2,%lo(SYM+4)($3)` dereferences
        # loaded_value + %lo(SYM+4) instead of loaded_value + 4. No label, no join.
        lines = [
            "	.ent	t5",
            "t5:",
            "	lui	$3,%hi(SYM)",
            "	addiu	$3,$3,%lo(SYM)",
            "	sll	$2,$4,2",
            "	addu	$3,$2,$3",
            "	lw	$3,0($3)",
            "	lw	$2,4($3)",
            "	jr	$31",
            "	nop",
            "	.end	t5",
        ]
        self.assert_declined(run(lines), "addiu\t$3,$3,%lo(SYM)",
                             ["lw\t$3,0($3)", "lw\t$2,4($3)"])

    def test_base_stored_as_data_is_not_folded(self):
        # STRAIGHT-LINE probe 4b (STORE-AS-DATA): the same `continue` skipped the
        # value-use guard for the store's VALUE operand. `sw $3,0($3)` folded to
        # `sw $3,%lo(SYM)($3)`, which writes a %hi-ONLY pointer into memory -- the
        # full address IS needed, so the addiu is real. Also covers `sw $3,0($2)`
        # (two distinct tagged registers, value and base).
        lines = [
            "	.ent	t6",
            "t6:",
            "	lui	$3,%hi(SYM)",
            "	addiu	$3,$3,%lo(SYM)",
            "	sll	$2,$4,2",
            "	addu	$3,$2,$3",
            "	sw	$3,0($3)",
            "	sw	$3,4($3)",
            "	jr	$31",
            "	nop",
            "	.end	t6",
        ]
        self.assert_declined(run(lines), "addiu\t$3,$3,%lo(SYM)",
                             ["sw\t$3,0($3)", "sw\t$3,4($3)"])

    def test_self_overwrite_bails_rather_than_retiring_the_tag(self):
        # func_8004A658 (LANDED, byte-exact) is why the f4a fix is a BAIL and not
        # an untag. `lw $3,12($3)` overwrites its own base. Retiring $3's tag is
        # more precise, but it also retires the accidental value-use bail that
        # made the scan collect a SECOND derivation from the later
        # `addu $2,$2,$3` -- one_base then became true and a REAL addiu was
        # deleted (-4 bytes vs retail). The pristine pass declined this fold; so
        # must the fixed one, and for a principled reason rather than by luck.
        lines = [
            "	.ent	t8",
            "t8:",
            "	lui	$3,%hi(SYM)",
            "	addiu	$3,$3,%lo(SYM)",
            "	sll	$2,$4,2",
            "	addu	$3,$2,$3",
            "	lbu	$2,0($3)",
            "	lw	$3,12($3)",
            "	addu	$2,$2,$3",
            "	lh	$2,2($2)",
            "	jr	$31",
            "	nop",
            "	.end	t8",
        ]
        self.assert_declined(run(lines), "addiu\t$3,$3,%lo(SYM)",
                             ["lbu\t$2,0($3)", "lw\t$3,12($3)"])

    def test_store_as_data_through_a_second_tagged_register(self):
        # Same class, the audit's spelling (B): the stored VALUE and the access
        # BASE are different registers, both carrying the %hi base.
        lines = [
            "	.ent	t7",
            "t7:",
            "	lui	$3,%hi(SYM)",
            "	addiu	$3,$3,%lo(SYM)",
            "	sll	$2,$4,2",
            "	addu	$2,$2,$3",
            "	sw	$3,0($2)",
            "	sw	$3,4($2)",
            "	jr	$31",
            "	nop",
            "	.end	t7",
        ]
        self.assert_declined(run(lines), "addiu\t$3,$3,%lo(SYM)",
                             ["sw\t$3,0($2)", "sw\t$3,4($2)"])


class TestFoldLoStillFiresAfterGuardSix(unittest.TestCase):
    """The other direction: guard #6 is subtractive, not a kill switch.

    If any of these regress, the guard has been over-tightened and every
    legitimate LEAD 2 / LEAD 4 win has been thrown away with the bug.
    """

    def test_branch_inside_the_window_still_folds(self):
        # func_8003E188: the label is created by a branch that is ITSELF inside
        # [seed lui .. last access] and the base is dead afterwards. Must fold.
        lines = [
            "	lui	$3,%hi(SYM)",
            "	addiu	$3,$3,%lo(SYM)",
            "	sll	$2,$4,2",
            "	addu	$2,$2,$3",
            "	lbu	$5,0($2)",
            "	beq	$5,$0,$L2",
            "	nop",
            "$L2:",
            "	sb	$0,1($2)",
        ]
        res = run(lines)
        self.assertNotIn("addiu\t$3,$3,%lo(SYM)", res)
        self.assertIn("lbu\t$5,%lo(SYM)($2)", res)
        self.assertIn("sb\t$0,%lo(SYM+1)($2)", res)

    def test_shared_indexed_base_still_folds(self):
        # func_8004A8D8: the plain win. One indexed base, several field offsets,
        # base dead after the last store.
        lines = [
            "	lui	$3,%hi(SYM)",
            "	addiu	$3,$3,%lo(SYM)",
            "	sll	$2,$4,2",
            "	addu	$2,$2,$3",
            "	sh	$0,0($2)",
            "	sh	$0,2($2)",
        ]
        res = run(lines)
        self.assertNotIn("addiu\t$3,$3,%lo(SYM)", res)
        self.assertIn("sh\t$0,%lo(SYM)($2)", res)
        self.assertIn("sh\t$0,%lo(SYM+2)($2)", res)

    def test_epilogue_restores_after_the_fold_still_fold(self):
        # The carriers ARE mentioned again, but only as straight-line plain
        # redefinitions (a callee-saved restore, a return-value move) with no
        # label or branch in between, which really does end the live range.
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
        res = run(lines)
        self.assertNotIn("addiu\t$2,$2,%lo(SYM)", res)
        self.assertIn("sh\t$0,%lo(SYM)($16)", res)
        self.assertIn("sh\t$0,%lo(SYM+2)($16)", res)

    def test_landed_epilogue_label_after_last_access_still_folds(self):
        # func_8004A700 / func_8004A7D8 (LANDED, byte-exact; retail keeps the
        # %hi-only base and folds %lo per access, so the addiu MUST be dropped).
        # v1 of guard #6 declined this and cost +4 bytes on each row: the epilogue
        # label `$L2` fences the liveness scan, and `move $2,$16` -- a
        # redefinition of the seed, not a read -- was treated as a decline. A
        # fenced REDEFINITION must keep watching; only a READ declines. Note the
        # `beq ...,$L2` sits BEFORE the seed lui, so it is also the exact shape
        # that a widened joins_from_outside bound would wrongly reject.
        lines = [
            "	.ent	func_8004A700",
            "func_8004A700:",
            "	slt	$2,$5,20",
            "	beq	$2,$0,$L2",
            "	nop",
            "	sll	$3,$5,2",
            "	addu	$16,$2,$4",
            "	lui	$2,%hi(SYM)",
            "	addiu	$2,$2,%lo(SYM)",
            "	addu	$3,$3,$2",
            "	sh	$17,0($3)",
            "	sh	$18,2($3)",
            "$L2:",
            "	move	$2,$16",
            "	lw	$31,28($sp)",
            "	lw	$18,24($sp)",
            "	lw	$17,20($sp)",
            "	lw	$16,16($sp)",
            "	addu	$sp,$sp,32",
            "	j	$31",
            "	nop",
            "	.end	func_8004A700",
        ]
        res = run(lines)
        self.assertNotIn("addiu\t$2,$2,%lo(SYM)", res)
        self.assertIn("sh\t$17,%lo(SYM)($3)", res)
        self.assertIn("sh\t$18,%lo(SYM+2)($3)", res)

    def test_selfinc_loop_still_folds(self):
        # func_8004A6C0: LEAD 4's win. Labels and branches everywhere, but the
        # scan never reaches case (c), so guard #6 never fires.
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
        res = run(lines)
        self.assertIn("lui\t$3,%hi(SYM)", res)
        self.assertFalse(any(l.startswith("la\t$3") for l in res))
        self.assertIn("lh\t$2,%lo(SYM)($3)", res)
        self.assertIn("lh\t$2,%lo(SYM+2)($3)", res)

    def test_straight_line_selfinc_redefinition_still_ends_the_range(self):
        # Guard #6 only rejects case (c) when something could jump around the
        # redefinition. With no label and no branch between the seed and the
        # redefinition, the linear argument holds and the fold must still fire.
        lines = [
            "	la	$3,SYM",
            "	lh	$5,0($3)",
            "	addu	$3,$3,4",
            "	lh	$6,0($3)",
            "	lw	$3,0($10)",
            "	jr	$31",
            "	nop",
        ]
        res = run(lines)
        self.assertIn("lui\t$3,%hi(SYM)", res)
        self.assertFalse(any(l.startswith("la\t$3") for l in res))
        self.assertIn("lh\t$5,%lo(SYM)($3)", res)


if __name__ == "__main__":
    unittest.main()
