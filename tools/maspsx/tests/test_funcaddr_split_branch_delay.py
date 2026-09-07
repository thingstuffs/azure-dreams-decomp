import unittest

from maspsx import MaspsxProcessor

from .util import strip_comments


# LEAD 36 -- `_split_funcaddr_la` hoists the generated `lui $R,%hi(FUNC)` BACKWARDS
# to the highest safe home for it.  The backward walk stops on a preceding
# branch/jump, and because the walk has by then already accepted every real
# instruction below that branch, the surviving destination is the first real
# instruction after it -- i.e. the branch's own DELAY SLOT.  Inserting there
# displaces whatever the scheduler had put in the slot.  Retail does not do that
# (witness: dungeon func_818D4E68, foff 0x18F4E68, 2.7.2-G0):
#
#     bne   $2,$0,$L13
#     addu  $4,$20,-32              <- delay slot, KEPT by retail
#     lui   $5,%hi(func_80045340)
#     jal   func_8004491C
#     addiu $5,$5,%lo(func_80045340)
#
# The sibling pass `_hoist_la_expansion_lui` (F2) already carries the same rule.
# F2 can simply CANCEL, because its hoist is an optional refinement of a whole
# `la`; here the split is not optional (cancelling leaves the `la` intact and the
# jal delay slot a bare `nop`, one word MORE than retail), so the guard steps the
# destination one real instruction PAST the slot instead -- possibly right back
# onto the `la`, which splits the pair in place.


class TestFuncAddrSplitBranchDelayGuard(unittest.TestCase):
    def _run(self, lines, sdata_limit=8):
        mp = MaspsxProcessor(lines, sdata_limit=sdata_limit)
        return strip_comments(mp.process_lines())

    @staticmethod
    def _idx(out, needle):
        for i, line in enumerate(out):
            if line == needle:
                return i
        raise AssertionError(f"{needle!r} not in {out}")

    def test_split_in_place_when_only_a_branch_delay_precedes(self):
        # The witness shape: the only instruction the lui could be hoisted across
        # IS the preceding bne's delay slot, so the pair must split IN PLACE --
        # `lui` where the `la` stood, `%lo` still in the jal delay slot.
        lines = [
            "subu	$sp,$sp,24",
            "sw	$31,16($sp)",
            "lbu	$2,122($20)",
            "andi	$2,$2,0x0004",
            ".set	noreorder",
            ".set	nomacro",
            "bne	$2,$0,$L13",
            "addu	$4,$20,-32",
            ".set	macro",
            ".set	reorder",
            "la	$5,func_80045340",
            "jal	func_8004491C",
            "nop",
            "$L13:",
            "lw	$31,16($sp)",
            "addu	$sp,$sp,24",
            "j	$31",
        ]
        out = self._run(lines)
        b = self._idx(out, "bne	$2,$0,$L13")
        self.assertEqual("addu	$4,$20,-32", out[b + 1])          # delay slot untouched
        self.assertEqual("lui	$5,%hi(func_80045340)", out[b + 2])  # split in place
        self.assertEqual("jal	func_8004491C", out[b + 3])
        self.assertEqual("addiu	$5,$5,%lo(func_80045340)", out[b + 4])

    def test_hoist_stops_one_short_of_the_delay_slot(self):
        # With ordinary setup between the delay slot and the `la`, the lui still
        # hoists -- but only as far as the first instruction AFTER the slot.
        lines = [
            "subu	$sp,$sp,24",
            "sw	$31,16($sp)",
            ".set	noreorder",
            ".set	nomacro",
            "bne	$2,$0,$L13",
            "addu	$4,$20,-32",
            ".set	macro",
            ".set	reorder",
            "sh	$3,16($6)",
            "sh	$3,18($6)",
            "la	$5,func_80045340",
            "jal	func_8004491C",
            "nop",
            "$L13:",
            "lw	$31,16($sp)",
            "addu	$sp,$sp,24",
            "j	$31",
        ]
        out = self._run(lines)
        b = self._idx(out, "bne	$2,$0,$L13")
        self.assertEqual("addu	$4,$20,-32", out[b + 1])
        self.assertEqual("lui	$5,%hi(func_80045340)", out[b + 2])
        self.assertEqual("sh	$3,16($6)", out[b + 3])
        self.assertEqual("sh	$3,18($6)", out[b + 4])
        self.assertEqual("jal	func_8004491C", out[b + 5])
        self.assertEqual("addiu	$5,$5,%lo(func_80045340)", out[b + 6])

    def test_prologue_hoist_is_unchanged(self):
        # NEGATIVE CONTROL: with no branch between the prologue and the `la`, the
        # pass keeps hoisting all the way to just after the prologue (the original
        # func_80041AB0 / func_80043CD0 behaviour).
        lines = [
            ".extern	D_8008148C, 12",
            ".extern	D_80081480, 12",
            "subu	$sp,$sp,24",
            "lw	$2,D_8008148C",
            "la	$4,func_80041AE4",
            "sw	$31,16($sp)",
            "sw	$2,D_80081480",
            "jal	func_80040A88",
            "lw	$31,16($sp)",
            "addu	$sp,$sp,24",
            "j	$31",
        ]
        expected = [
            ".extern	D_8008148C, 12",
            ".extern	D_80081480, 12",
            "subu	$sp,$sp,24",
            "lui	$4,%hi(func_80041AE4)",
            "lw	$2,D_8008148C",
            "sw	$31,16($sp)",
            "sw	$2,D_80081480",
            "jal	func_80040A88",
            "addiu	$4,$4,%lo(func_80041AE4)",
            "lw	$31,16($sp)",
            "addu	$sp,$sp,24",
            "j	$31",
            "nop",
        ]
        self.assertEqual(expected, self._run(lines))

    def test_jal_delay_slot_is_never_stolen_by_the_guard(self):
        # A preceding *jal* (not a conditional branch) owns a delay slot too, and
        # the guard must respect it identically.
        lines = [
            "subu	$sp,$sp,24",
            "sw	$31,16($sp)",
            ".set	noreorder",
            ".set	nomacro",
            "jal	func_80040000",
            "addu	$4,$20,-32",
            ".set	macro",
            ".set	reorder",
            "la	$5,func_80045340",
            "jal	func_8004491C",
            "nop",
            "lw	$31,16($sp)",
            "addu	$sp,$sp,24",
            "j	$31",
        ]
        out = self._run(lines)
        j = self._idx(out, "jal	func_80040000")
        self.assertEqual("addu	$4,$20,-32", out[j + 1])
        self.assertEqual("lui	$5,%hi(func_80045340)", out[j + 2])

    def test_branch_stop_still_declines_when_the_la_is_itself_the_delay_slot(self):
        # `la` DIRECTLY in the branch delay slot: `dest == i` before the guard even
        # runs, so nothing changes -- the pass declines exactly as it did before
        # (whole `la`, jal delay left to the ordinary machinery).
        lines = [
            "subu	$sp,$sp,24",
            "sw	$31,16($sp)",
            ".set	noreorder",
            ".set	nomacro",
            "bne	$2,$0,$L13",
            "la	$5,func_80045340",
            ".set	macro",
            ".set	reorder",
            "jal	func_8004491C",
            "nop",
            "$L13:",
            "lw	$31,16($sp)",
            "addu	$sp,$sp,24",
            "j	$31",
        ]
        out = self._run(lines)
        b = self._idx(out, "bne	$2,$0,$L13")
        # the whole `la` stays in the slot (left to `as` to expand), and the jal
        # delay slot is NOT given a %lo tail -- byte-identical to pre-LEAD-36.
        self.assertEqual("la	$5,func_80045340", out[b + 1])
        self.assertNotIn("%lo(func_80045340)", "".join(out))

    def test_label_stop_is_not_treated_as_a_delay_slot(self):
        # A LABEL stop leaves `dest` at the first instruction of the block, which
        # is not a delay slot; the hoist must still reach it.
        lines = [
            "subu	$sp,$sp,24",
            "sw	$31,16($sp)",
            "$L7:",
            "sh	$3,16($6)",
            "sh	$3,18($6)",
            "la	$5,func_80045340",
            "jal	func_8004491C",
            "nop",
            "lw	$31,16($sp)",
            "addu	$sp,$sp,24",
            "j	$31",
        ]
        out = self._run(lines)
        lab = self._idx(out, "$L7:")
        self.assertEqual("lui	$5,%hi(func_80045340)", out[lab + 1])
        self.assertEqual("sh	$3,16($6)", out[lab + 2])

    def test_break_does_not_arm_the_guard(self):
        # `break` matches the walk's `b\w*` barrier but owns NO delay slot, so it
        # must not arm the guard: the instruction after it is an ordinary one and
        # the lui still hoists onto it (pre-LEAD-36 behaviour).
        mp = MaspsxProcessor([], sdata_limit=8)
        self.assertFalse(mp._owns_a_delay_slot("break\t0x1c00"))
        for good in ("bne\t$2,$0,$L1", "beq\t$2,$3,$L1", "bgez\t$2,$L1",
                     "j\t$L1", "jr\t$31", "jal\tfunc_1", "jalr\t$25"):
            self.assertTrue(mp._owns_a_delay_slot(good), good)
        for bad in ("$L1:", ".set\tnoreorder", "", "addu\t$4,$5,$6", "sw\t$2,0($3)"):
            self.assertFalse(mp._owns_a_delay_slot(bad), bad)

    def test_guard_helper_is_identity_without_a_branch_stop(self):
        # Unit-level pin on the helper itself: it must be a no-op unless the walk
        # actually stopped on a branch, and it must never move the destination
        # backwards.
        mp = MaspsxProcessor([], sdata_limit=8)
        res = ["bne\t$2,$0,$L1", "addu\t$4,$20,-32", "", "la\t$5,func_1"]
        self.assertEqual((1, False), mp._branch_delay_safe_hoist_dest(res, 3, 1, False))
        self.assertEqual((3, True), mp._branch_delay_safe_hoist_dest(res, 3, 1, True))
        res2 = ["bne\t$2,$0,$L1", "addu\t$4,$20,-32", "sh\t$3,0($6)", "la\t$5,func_1"]
        self.assertEqual((2, False), mp._branch_delay_safe_hoist_dest(res2, 3, 1, True))
        # dest already == la index (nothing to hoist): unchanged, and NOT reported
        # as a split-in-place, so the caller keeps declining.
        self.assertEqual((3, False), mp._branch_delay_safe_hoist_dest(res2, 3, 3, True))


if __name__ == "__main__":
    unittest.main()
