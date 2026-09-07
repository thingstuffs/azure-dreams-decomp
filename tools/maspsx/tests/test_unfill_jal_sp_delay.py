import unittest

from maspsx import MaspsxProcessor

from .util import strip_comments


# Retail/ASPSX leaves a direct-call (`jal SYM`) delay slot UNFILLED (nop) when the
# instruction that would fill it is a stack-pointer swap (`move $sp,$reg`, i.e.
# `addu $sp,$reg,$zero`) -- the coroutine/stack-switch idiom where $sp is repointed
# just before the call. gcc's delayed-branch pass instead sinks that move into the
# slot. See func_8004CAA0. The pass hoists the move back above the jal and nops the
# delay slot; it is semantics-preserving because the delay slot always executes and
# the move neither reads nor depends on the jal's only output ($ra).


class TestUnfillJalSpDelay(unittest.TestCase):
    def _run(self, lines, sdata_limit=8):
        mp = MaspsxProcessor(lines, sdata_limit=sdata_limit)
        return strip_comments(mp.process_lines())

    def test_sp_swap_unfilled_from_jal_delay(self):
        lines = [
            ".ent\tx",
            ".set\tnoreorder",
            "subu\t$sp,$sp,24",
            "sw\t$31,16($sp)",
            "addu\t$8,$3,$zero",
            "addiu\t$8,$8,-4",
            "jal\tfunc_8004C36C",
            "addu\t$sp,$8,$zero",   # gcc-filled delay slot: move sp,t0
            "addu\t$sp,$sp,4",
            "j\t$31",
            ".end\tx",
        ]
        expected = [
            ".ent\tx",
            ".set\tnoreorder",
            "subu\t$sp,$sp,24",
            "sw\t$31,16($sp)",
            "addu\t$8,$3,$zero",
            "addiu\t$8,$8,-4",
            "addu\t$sp,$8,$zero",   # hoisted above the jal
            "jal\tfunc_8004C36C",
            "nop",                  # un-filled delay slot
            "addu\t$sp,$sp,4",
            "j\t$31",
            ".end\tx",
        ]
        self.assertEqual(expected, self._run(lines))

    def test_jalr_register_call_is_untouched(self):
        # A register/function-pointer call (`jalr`) is NOT a direct `jal SYM`; the
        # sp-swap must stay in its (correctly gcc-filled) delay slot.
        lines = [
            ".ent\tx",
            ".set\tnoreorder",
            "jalr\t$25",
            "addu\t$sp,$8,$zero",
            "j\t$31",
            ".end\tx",
        ]
        out = self._run(lines)
        self.assertIn("jalr\t$25", out)
        # order preserved: jalr immediately followed by the sp-swap, no injected nop
        i = out.index("jalr\t$25")
        self.assertEqual("addu\t$sp,$8,$zero", out[i + 1])

    def test_non_sp_delay_is_untouched(self):
        # A jal whose delay slot writes a non-$sp register must not be disturbed.
        lines = [
            ".ent\tx",
            ".set\tnoreorder",
            "jal\tfunc_8004C36C",
            "addu\t$4,$8,$zero",
            "j\t$31",
            ".end\tx",
        ]
        out = self._run(lines)
        i = out.index("jal\tfunc_8004C36C")
        self.assertEqual("addu\t$4,$8,$zero", out[i + 1])

    def test_sp_swap_reading_ra_is_untouched(self):
        # If the delay-slot move sources $ra, hoisting it above the jal would read
        # the OLD $ra -> not semantics-preserving; must not fire.
        lines = [
            ".ent\tx",
            ".set\tnoreorder",
            "jal\tfunc_8004C36C",
            "addu\t$sp,$ra,$zero",
            "j\t$31",
            ".end\tx",
        ]
        out = self._run(lines)
        i = out.index("jal\tfunc_8004C36C")
        self.assertEqual("addu\t$sp,$ra,$zero", out[i + 1])

    def test_already_unfilled_nop_delay_is_untouched(self):
        # Reorder-region / already-nop delay slot: nothing to un-fill.
        lines = [
            ".ent\tx",
            ".set\tnoreorder",
            "jal\tfunc_8004C36C",
            "nop",
            "addu\t$sp,$8,$zero",
            "j\t$31",
            ".end\tx",
        ]
        out = self._run(lines)
        i = out.index("jal\tfunc_8004C36C")
        self.assertEqual("nop", out[i + 1])
        self.assertEqual("addu\t$sp,$8,$zero", out[i + 2])


if __name__ == "__main__":
    unittest.main()
