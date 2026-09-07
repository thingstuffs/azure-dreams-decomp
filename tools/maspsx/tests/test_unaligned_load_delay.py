import unittest

from maspsx import MaspsxProcessor

from .util import strip_comments


class TestUnalignedLoadDelay(unittest.TestCase):
    """LEAD 29: `ulw`/`ulh`/`ulhu` end in a real load, so their destination
    register carries a load-delay slot exactly like a plain `lw`.

    maspsx used to drop these macros through its dispatch's final `else` (they
    are in neither load_mnemonics nor store_mnemonics), so a dependent next
    instruction followed with no nop. Genuine ASPSX 2.67 / 2.77 / 2.79 / 2.86 all
    emit `lwl; lwr; nop; swl; swr` for a `ulw`/`usw` pair on one register, and
    retail agrees — func_80E65598 (true name func_80174D98, dungeon, 2.8.1-G0),
    whose whole residue was that single missing nop at retail word 31.
    """

    def test_ulw_then_dependent_usw_gets_a_load_delay_nop(self):
        lines = [
            "	sw	$20,52($17)",
            "	ulw	$2,72($18)",
            "	usw	$2,76($16)",
            "	j	$31",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        i = res.index("ulw\t$2,72($18)")
        self.assertEqual(res[i + 1], "nop")
        self.assertEqual(res[i + 2], "usw\t$2,76($16)")

    def test_ulw_then_independent_instruction_gets_no_nop(self):
        lines = [
            "	ulw	$2,72($18)",
            "	usw	$3,76($16)",
            "	j	$31",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        i = res.index("ulw\t$2,72($18)")
        self.assertEqual(res[i + 1], "usw\t$3,76($16)")

    def test_ulw_base_reg_reuse_gets_a_nop(self):
        # The unaligned STORE reads its base register too, not just its value.
        lines = [
            "	ulw	$2,72($18)",
            "	usw	$4,76($2)",
            "	j	$31",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        i = res.index("ulw\t$2,72($18)")
        self.assertEqual(res[i + 1], "nop")

    def test_ulh_dependent_use_gets_a_nop(self):
        lines = [
            "	ulh	$2,6($18)",
            "	addu	$3,$2,$4",
            "	j	$31",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        i = res.index("ulh\t$2,6($18)")
        self.assertEqual(res[i + 1], "nop")

    def test_symbol_operand_form_is_left_untouched(self):
        # Deliberately narrow: only the numeric-offset register-base form is
        # handled. A symbol/addend operand would need the $at//%gp_rel expansion
        # machinery and has no retail witness, so it still passes straight
        # through with no added nop.
        lines = [
            "	ulw	$2,D_800E52E0",
            "	usw	$2,76($16)",
            "	j	$31",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8)
        res = strip_comments(mp.process_lines())

        i = res.index("ulw\t$2,D_800E52E0")
        self.assertEqual(res[i + 1], "usw\t$2,76($16)")


if __name__ == "__main__":
    unittest.main()
