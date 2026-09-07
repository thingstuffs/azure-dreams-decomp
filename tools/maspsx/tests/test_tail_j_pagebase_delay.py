import os
import tempfile
import unittest
from pathlib import Path
from unittest import mock

from maspsx import MaspsxProcessor

from .util import strip_comments


class TestSinkDeadPagebaseIntoTailJDelay(unittest.TestCase):
    """LEAD 27 (marker-gated): sink a DELIBERATELY-PINNED, consumer-free bare
    PAGE immediate sitting immediately before a converted noreturn/sibcall tail
    ``j SYM`` (empty ``nop`` delay slot) DOWN into that delay slot.

    Retail/ASPSX rematerialises a DEAD page base into the tail ``j``'s delay slot
    (``j SYM ; lui $v0,0xPPPP`` where SYM is void/noreturn, so $v0 is dead). gcc
    shares one page base across the branch and DCEs the rest, so the fill never
    exists in gcc's stock stream; it is MATERIALISED C-side by the
    ``ASM_PAGEBASE_PIN`` page-base pin, which gcc places as a consumer-free
    immediate BEFORE the ``j`` together with a reserved marker comment
    ``#maspsx_pagebase_pin $R``.

    THE DISCRIMINATOR: the bare-page-immediate SHAPE is NOT unique to a pin -- gcc
    materialises a natural ``0xNNNN0000`` mask constant (e.g. ``|= 0x10000000`` ->
    ``lui $v1,0x1000``) as the same shape, and retail leaves such a natural load
    STANDALONE with a ``nop`` tail slot (landed ``func_81880F28``). The round-1
    revision fired on both and regressed ``func_81880F28``. This pass fires ONLY
    when the unforgeable pin marker naming the immediate's register sits between
    the immediate and the ``j``; a natural mask constant carries no marker.
    """

    def _run(self, lines, sibcall_syms=(), noreturn_syms=(), sdata_limit=8):
        with tempfile.TemporaryDirectory() as d:
            sib = Path(d) / "sibcall_syms.txt"
            sib.write_text("".join(f"{s}\n" for s in sibcall_syms))
            nor = Path(d) / "noreturn_syms.txt"
            nor.write_text("".join(f"{s}\n" for s in noreturn_syms))
            with mock.patch.dict(os.environ, {
                "MASPSX_SIBCALL_FILE": str(sib),
                "MASPSX_NORETURN_FILE": str(nor),
            }):
                mp = MaspsxProcessor(lines, sdata_limit=sdata_limit)
                return strip_comments(mp.process_lines())

    def _body(self, callee, pre_lines):
        # A SHAPE-A tail call (jal CALLEE ; nop ; inline epilogue) preceded by
        # `pre_lines` (the page immediate and, for a pin, its marker comment). A
        # second callee-save ($16) keeps the frame off the LEAD 19 elision path so
        # this test isolates LEAD 27.
        return [
            ".ent\tfunc_TEST",
            "subu\t$sp,$sp,24",
            "sw\t$31,16($sp)",
            "sw\t$16,12($sp)",
            "move\t$4,$16",
            *pre_lines,
            ".set\tnoreorder",
            ".set\tnomacro",
            f"jal\t{callee}",
            "nop",
            ".set\tmacro",
            ".set\treorder",
            "lw\t$31,16($sp)",
            "lw\t$16,12($sp)",
            "addu\t$sp,$sp,24",
            "j\t$31",
            ".end\tfunc_TEST",
        ]

    def _seq(self, out):
        """Position map: stripped lines for adjacency asserts."""
        return [ln.strip() for ln in out]

    # --- positives (pin marker present) ---------------------------------------

    def test_pinned_bare_lui_sunk_into_delay(self):
        out = self._run(
            self._body("func_800AA6DC",
                       ["lui\t$2,0x800d", "#maspsx_pagebase_pin $2"]),
            sibcall_syms=("func_800AA6DC",))
        seq = self._seq(out)
        self.assertIn("j\tfunc_800AA6DC", seq)
        # the standalone lui is removed (relocated)
        self.assertEqual(seq.count("lui\t$2,0x800d"), 1)
        # ...and now sits in the j's delay slot (immediately after the j)
        i = seq.index("j\tfunc_800AA6DC")
        self.assertEqual(seq[i + 1], "lui\t$2,0x800d")

    def test_pinned_wide_li_normalised_to_lui_in_delay(self):
        # gcc emits `li $2,0x800d0000` (low16==0) for the pinned page constant;
        # the pass normalises it to an explicit single `lui` in the delay slot.
        out = self._run(
            self._body("func_800AA6DC",
                       ["li\t$2,0x800d0000", "#maspsx_pagebase_pin $2"]),
            sibcall_syms=("func_800AA6DC",))
        seq = self._seq(out)
        i = seq.index("j\tfunc_800AA6DC")
        self.assertEqual(seq[i + 1], "lui\t$2,0x800d")
        self.assertNotIn("li\t$2,0x800d0000", seq)

    def test_pinned_different_register_sunk(self):
        # Not $v0-specific: any pinned bare page immediate whose marker names the
        # same register.
        out = self._run(
            self._body("func_800AA6DC",
                       ["lui\t$3,0x8010", "#maspsx_pagebase_pin $3"]),
            sibcall_syms=("func_800AA6DC",))
        seq = self._seq(out)
        i = seq.index("j\tfunc_800AA6DC")
        self.assertEqual(seq[i + 1], "lui\t$3,0x8010")

    # --- negatives (safety guards) --------------------------------------------

    def test_natural_bare_lui_no_marker_not_sunk(self):
        # THE regression guard (models landed func_81880F28): gcc's natural
        # `lui $v1,0x1000` for `FIELD(x,0x1C) |= 0x10000000` lands before a
        # converted noreturn tail j with a nop slot -- the SAME shape as a pin but
        # with NO marker. Retail keeps it standalone; the pass MUST NOT fire.
        out = self._run(
            self._body("func_800AA6DC", ["lui\t$3,0x1000"]),
            sibcall_syms=("func_800AA6DC",))
        seq = self._seq(out)
        i = seq.index("j\tfunc_800AA6DC")
        self.assertEqual(seq[i + 1], "nop")           # delay slot untouched
        self.assertIn("lui\t$3,0x1000", seq)          # lui still standalone
        self.assertEqual(seq.count("lui\t$3,0x1000"), 1)

    def test_marker_register_mismatch_not_sunk(self):
        # Marker present but names a DIFFERENT register than the immediate -> not a
        # pin of THIS lui -> must not fire (the marker must name the sunk register).
        out = self._run(
            self._body("func_800AA6DC",
                       ["lui\t$2,0x800d", "#maspsx_pagebase_pin $3"]),
            sibcall_syms=("func_800AA6DC",))
        seq = self._seq(out)
        i = seq.index("j\tfunc_800AA6DC")
        self.assertEqual(seq[i + 1], "nop")
        self.assertIn("lui\t$2,0x800d", seq)

    def test_relocated_hi_lui_not_sunk(self):
        # A `%hi(SYM)` lui carries a reloc (a real page base with a %lo consumer),
        # NOT a bare immediate -> must be left in place even if a marker is present.
        out = self._run(
            self._body("func_800AA6DC",
                       ["lui\t$2,%hi(D_80083D08)", "#maspsx_pagebase_pin $2"]),
            sibcall_syms=("func_800AA6DC",))
        seq = self._seq(out)
        i = seq.index("j\tfunc_800AA6DC")
        self.assertEqual(seq[i + 1], "nop")             # delay slot untouched
        self.assertIn("lui\t$2,%hi(D_80083D08)", seq)   # still standalone

    def test_small_li_not_sunk(self):
        # `li $2,-1` (low16 != 0) is a small immediate, indistinguishable from a
        # live sibcall arg/return value -> the page-only guard must decline it even
        # with a marker present.
        out = self._run(
            self._body("func_800AA6DC",
                       ["li\t$2,-1", "#maspsx_pagebase_pin $2"]),
            sibcall_syms=("func_800AA6DC",))
        seq = self._seq(out)
        i = seq.index("j\tfunc_800AA6DC")
        self.assertEqual(seq[i + 1], "nop")
        self.assertIn("li\t$2,-1", seq)

    def test_non_member_not_converted_lui_kept(self):
        # Callee absent from both evidence sets -> jal kept, no tail j, lui stays,
        # pass never fires (cond 1: no jal->j marker).
        out = self._run(
            self._body("func_800AA6DC",
                       ["lui\t$2,0x800d", "#maspsx_pagebase_pin $2"]),
            sibcall_syms=("func_80407FBC",))
        seq = self._seq(out)
        self.assertIn("jal\tfunc_800AA6DC", seq)
        self.assertNotIn("j\tfunc_800AA6DC", seq)
        self.assertIn("lui\t$2,0x800d", seq)

    def test_marker_alone_without_pagebase_is_inert(self):
        # A stray marker with no preceding bare page immediate must not synthesise
        # a fire; the delay slot stays nop.
        out = self._run(
            self._body("func_800AA6DC",
                       ["move\t$2,$16", "#maspsx_pagebase_pin $2"]),
            sibcall_syms=("func_800AA6DC",))
        seq = self._seq(out)
        i = seq.index("j\tfunc_800AA6DC")
        self.assertEqual(seq[i + 1], "nop")


if __name__ == "__main__":
    unittest.main()
