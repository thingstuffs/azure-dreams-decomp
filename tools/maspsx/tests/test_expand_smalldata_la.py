import unittest

from maspsx import MaspsxProcessor

from .util import strip_comments


class TestExpandSmalldataLa(unittest.TestCase):
    """_expand_smalldata_la: when `gp_allow_la` is False (aspsx<2.80, e.g. the
    pinned aspsx-2.56 / PSYQ 4.0), a bare `la $R,SYM` for a KNOWN small-data extern
    must be materialised as an explicit `%hi/%lo` pair so the downstream
    `as -G8` cannot independently gp-relativize the passed-through macro (which real
    ASPSX 2.56 never did). Plain `sw`/`lw` of the same small symbol still gp-rel.
    See func_80047D44 (`D_8008152C`).
    """

    def test_smalldata_la_is_expanded_when_gp_allow_la_false(self):
        # A plain `.extern` symbol is left bare by maspsx for both the `sw` and the
        # `la` (downstream `as -G8` gp-relativizes them via the size hint). The bug:
        # `as` also gp-relativizes the `la`. This pass forces the `la` to %hi/%lo so
        # only the store gets gp-relativized (by `as`), matching real ASPSX 2.56.
        lines = [
            "	.extern	D_8008152C,4",
            "	sw	$2,D_8008152C",
            "	la	$2,D_8008152C",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8, gp_allow_la=False)
        res = strip_comments(mp.process_lines())

        # store left bare (as gp-relativizes it); address-load forced to %hi/%lo.
        self.assertTrue(any(l.startswith("sw\t$2,D_8008152C") for l in res))
        self.assertIn("lui\t$2,%hi(D_8008152C)", res)
        self.assertIn("addiu\t$2,$2,%lo(D_8008152C)", res)
        self.assertFalse(any(l.startswith("la\t$2,D_8008152C") for l in res))

    def test_smalldata_la_left_bare_when_gp_allow_la_true(self):
        # gp_allow_la True (aspsx>=2.80): this pass must NOT fire (it bails on
        # gp_allow_la), leaving the bare `la` for the downstream assembler.
        lines = [
            "	.extern	D_8008152C,4",
            "	la	$2,D_8008152C",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8, gp_allow_la=True)
        res = strip_comments(mp.process_lines())

        self.assertTrue(any(l.startswith("la\t$2,D_8008152C") for l in res))
        self.assertFalse(any(l.startswith("lui\t$2,%hi") for l in res))

    def test_large_extern_la_untouched(self):
        # size > -G: not small-data, `as` already emits %hi/%lo for the bare la; the
        # pass leaves it alone (no double expansion).
        lines = [
            "	.extern	D_80016000,16",
            "	la	$2,D_80016000",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8, gp_allow_la=False)
        res = strip_comments(mp.process_lines())

        self.assertTrue(any(l.startswith("la\t$2,D_80016000") for l in res))
        self.assertFalse(any("%hi(D_80016000)" in l for l in res))

    def test_smalldata_la_with_offset_is_expanded(self):
        lines = [
            "	.extern	D_8008152C,8",
            "	la	$2,D_8008152C+4",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8, gp_allow_la=False)
        res = strip_comments(mp.process_lines())

        self.assertIn("lui\t$2,%hi(D_8008152C+4)", res)
        self.assertIn("addiu\t$2,$2,%lo(D_8008152C+4)", res)

    def test_smalldata_la_in_jalr_delay_slot_untouched(self):
        # A `la` in a jalr (indirect call) delay slot must stay ONE instruction;
        # expanding to lui+addiu would inject a second insn into the slot and
        # shift every following byte (the LEAD 8 first-attempt veto case).
        lines = [
            "	.extern	D_8008152C,4",
            "	jalr	$3",
            "	la	$4,D_8008152C",
            "	nop",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8, gp_allow_la=False)
        res = strip_comments(mp.process_lines())

        self.assertTrue(any(l.startswith("la\t$4,D_8008152C") for l in res))
        self.assertFalse(any("%hi(D_8008152C)" in l for l in res))

    def test_smalldata_la_in_jal_delay_slot_unfilled_then_expanded(self):
        # A `la` in a jal delay slot is un-filled by an EARLIER pass (nop in the
        # slot, la re-emitted after the jal) before this pass runs, so the
        # expansion must land AFTER the jal's delay slot — never inside it.
        lines = [
            "	.extern	D_8008152C,4",
            "	jal	func_80047AB0",
            "	la	$4,D_8008152C",
            "	nop",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8, gp_allow_la=False)
        res = [l for l in strip_comments(mp.process_lines()) if l and not l.startswith(".")]

        jal = next(i for i, l in enumerate(res) if l.startswith("jal"))
        self.assertEqual(res[jal + 1], "nop")  # slot un-filled, exactly one insn
        self.assertIn("lui\t$4,%hi(D_8008152C)", res[jal + 2 :])
        self.assertIn("addiu\t$4,$4,%lo(D_8008152C)", res[jal + 2 :])

    def test_smalldata_la_after_break_still_expanded(self):
        # `break` starts with `b` but is not a branch — no delay slot; the
        # following `la` must still be expanded.
        lines = [
            "	.extern	D_8008152C,4",
            "	break	7",
            "	la	$2,D_8008152C",
        ]
        mp = MaspsxProcessor(lines, sdata_limit=8, gp_allow_la=False)
        res = strip_comments(mp.process_lines())

        self.assertIn("lui\t$2,%hi(D_8008152C)", res)
        self.assertIn("addiu\t$2,$2,%lo(D_8008152C)", res)


if __name__ == "__main__":
    unittest.main()
