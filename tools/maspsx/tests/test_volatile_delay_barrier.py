import unittest

from maspsx import MaspsxProcessor

from .util import strip_comments


class TestVolatileDelayBarrier(unittest.TestCase):
    """A `.set volatile` region blocks the delay-slot rotation of the access.

    gcc brackets a volatile memory reference with `.set volatile` /
    `.set novolatile` (config/mips/mips.c `%{` / `%}`) -- bare for the SN
    assembler, `#`-commented for GNU `as`.  ASPSX honours the live directive and
    refuses to reschedule the marked access, so `_expand_store_to_symbol_in_delay`
    must leave it where the compiler put it and let the following jump keep its
    `nop`.  Receipts (16 rotation sites over the whole landed corpus, none of them
    volatile-marked, plus the genuine-ASPSX verdict on the row this closes):
    work/bridge_wave_20260906/maspsx_store_delay_jal/REPORT.md.
    """

    SYM = "D_80013714"
    EXTERN = ".extern\tD_80013714, 12"

    def _run(self, body, sdata_limit=8):
        lines = [
            self.EXTERN,
            ".ent\tfunc_TEST",
            *body,
            ".end\tfunc_TEST",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=sdata_limit)
        return strip_comments(mp.process_lines())

    # ---- the rotation still happens without the markers ---------------------

    def test_plain_store_before_a_call_is_still_rotated(self):
        out = self._run([
            f"sh\t$0,{self.SYM}",
            "jal\tfunc_CALLEE",
        ])
        self.assertIn(f"lui\t$2,%hi({self.SYM})", out)
        self.assertIn(f"sh\t$0,%lo({self.SYM})($2)", out)

    def test_plain_store_before_a_return_is_still_rotated(self):
        out = self._run([
            f"sh\t$0,{self.SYM}",
            "j\t$31",
        ])
        self.assertIn(f"lui\t$2,%hi({self.SYM})", out)
        self.assertIn(f"sh\t$0,%lo({self.SYM})($2)", out)

    # ---- the markers block it ----------------------------------------------

    def test_commented_volatile_store_before_a_call_is_not_rotated(self):
        out = self._run([
            "#.set\tvolatile",
            f"sh\t$0,{self.SYM}",
            "#.set\tnovolatile",
            "jal\tfunc_CALLEE",
        ])
        self.assertIn(f"sh\t$0,{self.SYM}", out)
        self.assertNotIn(f"lui\t$2,%hi({self.SYM})", out)

    def test_bare_volatile_store_before_a_call_is_not_rotated(self):
        out = self._run([
            ".set\tvolatile",
            f"sh\t$0,{self.SYM}",
            ".set\tnovolatile",
            "jal\tfunc_CALLEE",
        ])
        self.assertIn(f"sh\t$0,{self.SYM}", out)
        self.assertNotIn(f"lui\t$2,%hi({self.SYM})", out)

    def test_volatile_store_before_a_return_is_not_rotated(self):
        out = self._run([
            "#.set\tvolatile",
            f"sh\t$0,{self.SYM}",
            "#.set\tnovolatile",
            "j\t$31",
        ])
        self.assertIn(f"sh\t$0,{self.SYM}", out)
        self.assertNotIn(f"lui\t$2,%hi({self.SYM})", out)

    # ---- the region CLOSES, and never spans a function ----------------------

    def test_store_after_the_region_closed_is_rotated(self):
        out = self._run([
            "#.set\tvolatile",
            "sh\t$0,0($4)",
            "#.set\tnovolatile",
            f"sh\t$0,{self.SYM}",
            "jal\tfunc_CALLEE",
        ])
        self.assertIn(f"lui\t$2,%hi({self.SYM})", out)
        self.assertIn(f"sh\t$0,%lo({self.SYM})($2)", out)

    def test_an_unclosed_region_in_a_previous_function_does_not_leak(self):
        lines = [
            self.EXTERN,
            ".ent\tfunc_EARLIER",
            "#.set\tvolatile",
            "sh\t$0,0($4)",
            ".end\tfunc_EARLIER",
            ".ent\tfunc_TEST",
            f"sh\t$0,{self.SYM}",
            "jal\tfunc_CALLEE",
            ".end\tfunc_TEST",
        ]
        out = strip_comments(MaspsxProcessor(lines, sdata_limit=8).process_lines())
        self.assertIn(f"lui\t$2,%hi({self.SYM})", out)

    # ---- the `la` variant is covered by the same barrier --------------------

    def test_volatile_marked_la_is_not_rotated(self):
        out = self._run([
            "#.set\tvolatile",
            f"la\t$4,{self.SYM}",
            "#.set\tnovolatile",
            "jal\tfunc_CALLEE",
        ], sdata_limit=8)
        self.assertNotIn(f"addiu\t$4,$4,%lo({self.SYM})", out)


if __name__ == "__main__":
    unittest.main()
