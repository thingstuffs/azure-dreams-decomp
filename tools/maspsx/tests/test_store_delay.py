import unittest

from maspsx import MaspsxProcessor

from .util import strip_comments


# gcc emits `.extern SYM, size`; `as -G8` uses the size to pick $gp (size <= 8)
# vs %hi/%lo (size > 8). The delay-slot store expansion only applies to the
# %hi/%lo (non-small-data) symbols, so tests declare a size > 8.


class TestStoreToSymbolInDelaySlot(unittest.TestCase):
    """ASPSX schedules a store-to-global macro into a following unconditional
    jump's delay slot, materialising %hi() in a caller-saved temp register and
    reusing it for the %lo() store (rather than GNU as's $at expansion + nop).

    Verified byte-exact against retail: func_8004EB30, func_8005ACD0,
    func_800557BC, func_8005A39C.
    """

    def _run(self, lines, sdata_limit=8):
        mp = MaspsxProcessor(lines, sdata_limit=sdata_limit)
        return strip_comments(mp.process_lines())

    def test_store_zero_into_return_delay(self):
        # e.g. void func_8004EB30(void) { D_80084130[0] = 0; }
        lines = [
            ".extern	D_80084130, 12",
            "sw	$0,D_80084130",
            "j	$31",
        ]
        expected_lines = [
            ".extern	D_80084130, 12",
            "lui	$2,%hi(D_80084130)",
            "j	$31",
            "sw	$0,%lo(D_80084130)($2)",
        ]
        self.assertEqual(expected_lines, self._run(lines))

    def test_store_arg_reg_uses_v0(self):
        lines = [
            ".extern	D_80086D4C, 12",
            "sw	$4,D_80086D4C",
            "j	$31",
        ]
        expected_lines = [
            ".extern	D_80086D4C, 12",
            "lui	$2,%hi(D_80086D4C)",
            "j	$31",
            "sw	$4,%lo(D_80086D4C)($2)",
        ]
        self.assertEqual(expected_lines, self._run(lines))

    def test_store_half_word(self):
        lines = [
            ".extern	D_80073828, 10",
            "sh	$4,D_80073828",
            "j	$31",
        ]
        expected_lines = [
            ".extern	D_80073828, 10",
            "lui	$2,%hi(D_80073828)",
            "j	$31",
            "sh	$4,%lo(D_80073828)($2)",
        ]
        self.assertEqual(expected_lines, self._run(lines))

    def test_temp_steps_to_v1_when_data_is_v0(self):
        # when the stored value lives in $v0 (e.g. it is also the return value),
        # ASPSX uses $v1 for the address so $v0 is not clobbered.
        lines = [
            ".extern	D_80084130, 12",
            "sw	$2,D_80084130",
            "j	$31",
        ]
        expected_lines = [
            ".extern	D_80084130, 12",
            "lui	$3,%hi(D_80084130)",
            "j	$31",
            "sw	$2,%lo(D_80084130)($3)",
        ]
        self.assertEqual(expected_lines, self._run(lines))

    def test_jr_ra_also_matches(self):
        lines = [
            ".extern	D_80084130, 12",
            "sw	$0,D_80084130",
            "jr	$ra",
        ]
        expected_lines = [
            ".extern	D_80084130, 12",
            "lui	$2,%hi(D_80084130)",
            "jr	$ra",
            "sw	$0,%lo(D_80084130)($2)",
        ]
        self.assertEqual(expected_lines, self._run(lines))

    # --- guard cases: the transformation must NOT fire ---------------------

    def test_not_applied_to_small_data_extern(self):
        # size <= -G: `as -G8` handles this as a single %gp_rel store and fills
        # the delay slot itself; we must leave the macro untouched. This is the
        # func_8003F5E0 / D_800814C8 shape.
        lines = [
            ".extern	D_800814C8, 4",
            "sw	$4,D_800814C8",
            "j	$31",
        ]
        clean = self._run(lines)
        self.assertIn("sw	$4,D_800814C8", clean)
        self.assertNotIn("lui	$2,%hi(D_800814C8)", clean)

    def test_not_applied_without_extern_size(self):
        # no `.extern` seen -> treated as small-data (historic default), untouched.
        lines = [
            "sw	$0,D_80084130",
            "j	$31",
        ]
        clean = self._run(lines)
        self.assertIn("sw	$0,D_80084130", clean)
        self.assertNotIn("lui	$2,%hi(D_80084130)", clean)

    def test_not_applied_when_followed_by_noreorder_boundary(self):
        # gcc prefills the return delay slot itself (behind a .set noreorder /
        # .set nomacro block); the store stays a plain macro for `as`. This is
        # the func_800542AC shape, which needs deeper dedup logic we do not do.
        lines = [
            ".extern	D_800847F6, 12",
            "sw	$2,D_800847F6",
            ".set	noreorder",
            ".set	nomacro",
            "j	$31",
            "li	$2,-1",
            ".set	macro",
            ".set	reorder",
        ]
        clean = self._run(lines)
        self.assertIn("sw	$2,D_800847F6", clean)
        self.assertNotIn("lui	$3,%hi(D_800847F6)", clean)

    def test_not_applied_before_conditional_branch(self):
        # a conditional branch delay slot is only safe to fill when ASPSX did so;
        # we conservatively leave these for `as`.
        lines = [
            ".extern	D_80084130, 12",
            "sw	$0,D_80084130",
            "beq	$4,$0,$L2",
            "nop",
        ]
        clean = self._run(lines)
        self.assertIn("sw	$0,D_80084130", clean)
        self.assertNotIn("lui	$2,%hi(D_80084130)", clean)

    def test_not_applied_to_gp_relative_store(self):
        # small-data symbols declared via .comm still go through %gp_rel.
        lines = [
            ".comm	D_80084130,4",
            "sw	$0,D_80084130",
            "j	$31",
        ]
        clean = self._run(lines)
        self.assertIn("sw	$0,%gp_rel(D_80084130)($gp)", clean)
        self.assertNotIn("lui	$2,%hi(D_80084130)", clean)

    def test_load_address_into_delay(self):
        # `return &D_X;` -> gcc emits `la $2,D_X`; ASPSX puts `lui` before the jump
        # and schedules the `%lo` addiu tail into the delay slot (rather than GNU
        # as's lui+addiu pair before the jump + a nop). See func_8003F534.
        lines = [
            ".extern	D_8006CE34, 12",
            "la	$2,D_8006CE34",
            "j	$31",
        ]
        expected_lines = [
            ".extern	D_8006CE34, 12",
            "lui	$2,%hi(D_8006CE34)",
            "j	$31",
            "addiu	$2,$2,%lo(D_8006CE34)",
        ]
        self.assertEqual(expected_lines, self._run(lines))


if __name__ == "__main__":
    unittest.main()
