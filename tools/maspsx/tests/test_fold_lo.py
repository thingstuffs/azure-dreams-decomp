import unittest

from maspsx import MaspsxProcessor

from .util import strip_comments


class TestFoldLoIntoAccesses(unittest.TestCase):
    """_fold_lo_into_accesses: drop gcc>=2.8's `addiu $R,$R,%lo(SYM)` and fold
    %lo(SYM+off) into each access — but ONLY when the 2+ accesses derive from the
    SAME base register (one indexed base reused for several offsets). Two
    INDEPENDENT single-use derivations off one shared %hi base must NOT be folded
    (retail keeps the addiu + 0-offset loads). See func_8004A8D8 / func_8004AE68.
    """

    def test_shared_base_is_folded(self):
        # func_8004A8D8 shape: one indexed base ($3) reused for two field offsets.
        lines = [
            "	lui	$3,%hi(SYM)",
            "	addiu	$3,$3,%lo(SYM)",
            "	sll	$2,$4,2",
            "	addu	$2,$2,$3",
            "	sh	$0,0($2)",
            "	sh	$0,2($2)",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        # addiu dropped (folded), %lo folded into both stores.
        self.assertNotIn("addiu\t$3,$3,%lo(SYM)", res)
        self.assertIn("sh\t$0,%lo(SYM)($2)", res)
        self.assertIn("sh\t$0,%lo(SYM+2)($2)", res)

    def test_distinct_bases_are_not_folded(self):
        # func_8004AE68 shape: two INDEPENDENT single-use derivations ($2, $3) off
        # one shared %hi base ($6). Retail keeps the addiu and uses 0-offset loads.
        lines = [
            "	lui	$6,%hi(SYM)",
            "	addiu	$6,$6,%lo(SYM)",
            "	lw	$2,0($4)",
            "	lw	$3,0($5)",
            "	lbu	$2,1($2)",
            "	lbu	$3,1($3)",
            "	addu	$2,$2,$6",
            "	addu	$3,$3,$6",
            "	lbu	$4,0($2)",
            "	lbu	$2,0($3)",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        # addiu KEPT, no %lo folded into the loads.
        self.assertIn("addiu\t$6,$6,%lo(SYM)", res)
        self.assertIn("lbu\t$4,0($2)", res)
        self.assertIn("lbu\t$2,0($3)", res)
        self.assertFalse(any("%lo(SYM)" in l and l.startswith("lbu") for l in res))

    def test_reused_base_register_is_not_folded(self):
        # func_8005AF74 / func_8005AFF4 shape: gcc materialises the full base into $3
        # (lui+addiu), forms the indexed base in $2 (addu $2,$2,$3), then REUSES $3 as a
        # store value (`li $3,127`). Because $3 is spent-then-reused, retail keeps the
        # addiu and uses numeric offsets (materialise), NOT the folded form. maspsx must
        # therefore NOT drop the addiu here even though 3 accesses share the one base $2.
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

        # addiu KEPT, offsets stay numeric (no %lo folded into the stores).
        self.assertIn("addiu\t$3,$3,%lo(SYM)", res)
        self.assertIn("sh\t$3,10($2)", res)
        self.assertIn("sh\t$3,8($2)", res)
        self.assertIn("sh\t$3,2($2)", res)
        self.assertFalse(any("%lo(SYM" in l and l.startswith("sh") for l in res))


class TestFoldLoControlFlowJoin(unittest.TestCase):
    """LEAD 2 guard #4: never fold accesses that a second predecessor edge can
    reach without passing the seed `lui` (func_800C738C miscompile)."""

    C738C = [
        "	srl	$2,$4,23",
        "	andi	$2,$2,0x1",
        "	srl	$3,$4,24",
        "	bne	$2,$0,$L5",
        "	andi	$3,$3,0x3f",
        "	sll	$3,$3,5",
        "	lui	$2,%hi(SYM_A)",
        "	j	$L9",
        "	addiu	$2,$2,%lo(SYM_A)",
        "$L5:",
        "	sll	$3,$3,5",
        "	lui	$2,%hi(SYM_B)",
        "	addiu	$2,$2,%lo(SYM_B)",
        "$L9:",
        "	addu	$2,$3,$2",
        "	lhu	$5,0($2)",
        "	lhu	$3,4($2)",
        "	lhu	$4,2($2)",
        "	lhu	$2,6($2)",
    ]

    def test_two_arm_select_merging_into_shared_loads_is_not_folded(self):
        # func_800C738C: `$L9` is a JOIN — the fall-through arm reaches it with $2
        # already holding the FULL base of a DIFFERENT symbol (SYM_A). Folding
        # %lo(SYM_B+k) into the four shared loads (and deleting SYM_B's addiu)
        # miscompiles that edge, so the addiu must survive with numeric offsets.
        mp = MaspsxProcessor(list(self.C738C), sdata_limit=8)
        res = strip_comments(mp.process_lines())

        self.assertIn("addiu\t$2,$2,%lo(SYM_B)", res)
        for off in ("0", "4", "2", "6"):
            self.assertTrue(
                any(l.startswith("lhu\t") and l.endswith(f",{off}($2)") for l in res),
                f"lhu at numeric offset {off} missing: {res}",
            )
        self.assertFalse(any("%lo(SYM_B" in l and l.startswith("lhu") for l in res))

    def test_branch_inside_the_window_still_folds(self):
        # func_8003E188 (LEAD 2's own cross-branch win): the label is created by a
        # branch that is ITSELF inside [seed lui .. last access], so nothing can
        # reach the accesses without passing the seed. Must still fold.
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
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        self.assertNotIn("addiu\t$3,$3,%lo(SYM)", res)
        self.assertIn("lbu\t$5,%lo(SYM)($2)", res)
        self.assertIn("sb\t$0,%lo(SYM+1)($2)", res)

    def test_back_edge_into_the_fold_region_is_not_folded(self):
        # The outside edge may also arrive from BELOW: a loop back-edge re-enters
        # $L3 between the seed and the accesses, so $2's definition on that edge is
        # whatever the loop body left behind. Decline.
        lines = [
            "	lui	$3,%hi(SYM)",
            "	addiu	$3,$3,%lo(SYM)",
            "	sll	$2,$4,2",
            "$L3:",
            "	addu	$2,$2,$3",
            "	sh	$0,0($2)",
            "	sh	$0,2($2)",
            "	addiu	$4,$4,1",
            "	bne	$4,$5,$L3",
            "	nop",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        self.assertIn("addiu\t$3,$3,%lo(SYM)", res)
        self.assertIn("sh\t$0,0($2)", res)
        self.assertIn("sh\t$0,2($2)", res)
        self.assertFalse(any("%lo(SYM" in l and l.startswith("sh") for l in res))

    def test_local_labels_of_another_function_do_not_block_the_fold(self):
        # `$L2` is reused by every function of a TU. The outside-edge search is
        # bounded by .ent/.end, so a NEIGHBOUR function's `beq ...,$L2` must not
        # suppress this function's in-window fold.
        lines = [
            "	.ent	func_A",
            "func_A:",
            "	lui	$3,%hi(SYM)",
            "	addiu	$3,$3,%lo(SYM)",
            "	sll	$2,$4,2",
            "	addu	$2,$2,$3",
            "	lbu	$5,0($2)",
            "	beq	$5,$0,$L2",
            "	nop",
            "$L2:",
            "	sb	$0,1($2)",
            "	.end	func_A",
            "	.ent	func_B",
            "func_B:",
            "	beq	$4,$0,$L2",
            "	nop",
            "$L2:",
            "	j	$31",
            "	nop",
            "	.end	func_B",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        self.assertNotIn("addiu\t$3,$3,%lo(SYM)", res)
        self.assertIn("lbu\t$5,%lo(SYM)($2)", res)
        self.assertIn("sb\t$0,%lo(SYM+1)($2)", res)

    def test_two_derivations_through_one_scratch_reg_are_not_folded(self):
        # LEAD 2 guard #5, func_80953300 (town, 2.7.2-cdk-G0): the func_8004AE68
        # shape spelled with ONE scratch register instead of two. Both indexed
        # bases live in $3, so the base-REGISTER-NAME test cannot tell them apart,
        # but they are two INDEPENDENT single-use derivations off the shared %hi
        # base and retail keeps the addiu with 0-offset stores (retail word 34 is
        # `addiu a1,a1,%lo(D_80024308)`; genuine ASPSX 2.67-2.86 agree).
        lines = [
            "	lui	$5,%hi(SYM)",
            "	addiu	$5,$5,%lo(SYM)",
            "	sll	$3,$16,1",
            "	addu	$3,$3,$5",
            "	li	$4,1",
            "	sh	$4,0($3)",
            "	sll	$3,$6,1",
            "	addu	$3,$3,$5",
            "	li	$4,2",
            "	sh	$4,0($3)",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        # addiu KEPT, stores stay 0-offset.
        self.assertIn("addiu\t$5,$5,%lo(SYM)", res)
        self.assertIn("sh\t$4,0($3)", res)
        self.assertFalse(any("%lo(SYM" in l and l.startswith("sh") for l in res))

    def test_single_derivation_with_a_reused_index_reg_still_folds(self):
        # Guard #5 must key on the DERIVATION instance, not on "did the register
        # ever get rewritten": one `addu` into $2 feeding two offsets is still the
        # func_8004A8D8 fold and must keep firing after the guard lands.
        lines = [
            "	lui	$3,%hi(SYM)",
            "	addiu	$3,$3,%lo(SYM)",
            "	sll	$2,$4,2",
            "	addu	$2,$2,$3",
            "	sh	$0,0($2)",
            "	sh	$0,2($2)",
            "	sh	$0,4($2)",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        self.assertNotIn("addiu\t$3,$3,%lo(SYM)", res)
        self.assertIn("sh\t$0,%lo(SYM)($2)", res)
        self.assertIn("sh\t$0,%lo(SYM+2)($2)", res)
        self.assertIn("sh\t$0,%lo(SYM+4)($2)", res)


if __name__ == "__main__":
    unittest.main()
