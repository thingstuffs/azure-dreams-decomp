import unittest

from maspsx import MaspsxProcessor

from .util import strip_comments

JALJ = "\t# maspsx: tail-call jal->j (LEAD 18)"


class TestRotateDeadValueIntoTailJDelay(unittest.TestCase):
    """LEAD 28 (marker-gated): rotate a DELIBERATELY-PINNED dead value into a
    converted noreturn/sibcall tail ``j SYM`` delay slot when the branch delay is
    already occupied by the call's last arg-move.

    Retail/ASPSX parks a DEAD dispatch value (e.g. ``addu $v0,$v0,$a1`` =
    base+index, dead because the sibcall callee ignores $v0) in the tail ``j``
    delay slot and pulls the last arg-move UP into an earlier load-delay ``nop``.
    gcc-2.8.x parks the dead value STANDALONE before the jal and schedules the
    arg-move into the branch delay, wasting the load-delay as a ``nop`` -- one word
    longer. The dead value is materialised C-side by ``ASM_TAILSLOT_PIN``, which
    emits the reserved marker ``#maspsx_tailslot_pin $R``. This pass rotates:
    arg-move -> load-delay nop; dead value -> branch delay; standalone dead value
    deleted (net -1 word -> retail).

    THE DISCRIMINATOR (same discipline as LEAD 27, whose round-1 revision was
    VETOED for shape-only firing): fires ONLY when the unforgeable marker naming
    the dead value's register sits between it and the ``j``. A natural dead ALU op
    before a converted tail j carries no marker and is left untouched.

    The pass runs on ALREADY-converted lines (the ``jal->j`` stamp is present), so
    these cases exercise ``_rotate_dead_value_into_tail_j_delay`` directly on the
    post-conversion stream LEAD 18/22 hands it. End-to-end (gcc -> maspsx ->
    byte-exact) is proven by the landed func_800D38EC MATCH.
    """

    def _rotate(self, res):
        mp = MaspsxProcessor([], sdata_limit=8)
        return strip_comments(mp._rotate_dead_value_into_tail_j_delay(res))

    def _body(self, tail, callee="func_800D910C", load_delay="nop"):
        """A block: a load + its load-delay slot, a dispatch chain, then `tail`
        (the D / marker / j / M sequence under test)."""
        return [
            ".ent\tfunc_TEST",
            "lh\t$3,42($17)",
            load_delay,               # load-delay slot (a nop = fillable)
            "addu\t$2,$2,$3",         # consumes the load (why the nop is there)
            "addiu\t$2,$2,256",
            "sra\t$2,$2,7",
            "andi\t$2,$2,0x001c",
            *tail,
            "lhu\t$2,20($19)",        # next block (a fresh use of $2)
            ".end\tfunc_TEST",
        ]

    # --- positive: the marker fires the rotation ------------------------------

    def test_pinned_dead_addu_rotated(self):
        out = self._rotate(self._body([
            "addu\t$2,$2,$5",                    # D (dead dispatch, writes $v0)
            "#maspsx_tailslot_pin $2",           # the pin marker naming $v0
            "j\tfunc_800D910C" + JALJ,           # converted tail j
            "addu\t$4,$19,$zero",                # M (arg-move a0=arg2, branch delay)
        ]))
        # D sits in the j's delay slot now
        i = out.index("j\tfunc_800D910C")
        self.assertEqual(out[i + 1], "addu\t$2,$2,$5")
        # the standalone D is gone (commented out -> stripped to "")
        self.assertEqual(out.count("addu\t$2,$2,$5"), 1)
        # M was pulled up into the load-delay nop (immediately after the load)
        j = out.index("lh\t$3,42($17)")
        self.assertEqual(out[j + 1], "addu\t$4,$19,$zero")
        # the load-delay nop is consumed (no nop remains between load and its use)
        self.assertEqual(out[j + 2], "addu\t$2,$2,$3")

    def test_move_form_arg_delay_rotated(self):
        # The arg-move may be spelled `move $4,$17` (not addu ...,$zero).
        out = self._rotate(self._body([
            "addu\t$2,$2,$5",
            "#maspsx_tailslot_pin $2",
            "j\tfunc_800D910C" + JALJ,
            "move\t$4,$17",
        ]))
        i = out.index("j\tfunc_800D910C")
        self.assertEqual(out[i + 1], "addu\t$2,$2,$5")
        j = out.index("lh\t$3,42($17)")
        self.assertEqual(out[j + 1], "move\t$4,$17")

    # --- negatives (safety guards) --------------------------------------------

    def test_natural_dead_addu_no_marker_not_rotated(self):
        # THE over-fire guard: the SAME shape (dead addu before a converted tail j
        # with an arg-move delay) but NO marker -> a natural dead value gcc emitted;
        # retail leaves the schedule as-is. The pass MUST NOT fire.
        out = self._rotate(self._body([
            "addu\t$2,$2,$5",
            "j\tfunc_800D910C" + JALJ,
            "addu\t$4,$19,$zero",
        ]))
        i = out.index("j\tfunc_800D910C")
        self.assertEqual(out[i + 1], "addu\t$4,$19,$zero")   # delay untouched
        j = out.index("lh\t$3,42($17)")
        self.assertEqual(out[j + 1], "nop")                  # load-delay still nop
        self.assertEqual(out.count("addu\t$2,$2,$5"), 1)     # D still standalone

    def test_marker_register_mismatch_not_rotated(self):
        # Marker names a DIFFERENT register than the dead value -> not a pin of THIS
        # value -> must not fire.
        out = self._rotate(self._body([
            "addu\t$2,$2,$5",
            "#maspsx_tailslot_pin $3",
            "j\tfunc_800D910C" + JALJ,
            "addu\t$4,$19,$zero",
        ]))
        i = out.index("j\tfunc_800D910C")
        self.assertEqual(out[i + 1], "addu\t$4,$19,$zero")

    def test_nop_delay_pinned_dead_value_sunk_arm_b(self):
        # ARM B (empty-slot sink, LEAD 28b): a bare `nop` branch delay with a
        # marker-pinned dead value immediately before the j -> there is no arg-move
        # to rotate, so the pinned value is SUNK into the nop slot (net -1 word).
        # (This used to be declined and deferred to LEAD 27; ARM B now owns the
        # tailslot-marker + nop-delay case for a general ALU dead value.)
        out = self._rotate(self._body([
            "addu\t$2,$2,$5",                    # D (dead value, adjacent)
            "#maspsx_tailslot_pin $2",           # the pin marker naming $v0
            "j\tfunc_800D910C" + JALJ,
            "nop",                               # bare nop branch delay
        ]))
        i = out.index("j\tfunc_800D910C")
        self.assertEqual(out[i + 1], "addu\t$2,$2,$5")       # sunk into the delay
        self.assertEqual(out.count("addu\t$2,$2,$5"), 1)     # standalone D gone
        # the load-delay nop is UNTOUCHED (ARM B does no arg-move rotation)
        j = out.index("lh\t$3,42($17)")
        self.assertEqual(out[j + 1], "nop")

    def test_non_arg_register_mover_not_rotated(self):
        # The branch-delay mover must write an ARGUMENT register ($a0-$a3). A move
        # into a saved reg is not the call's arg setup -> decline.
        out = self._rotate(self._body([
            "addu\t$2,$2,$5",
            "#maspsx_tailslot_pin $2",
            "j\tfunc_800D910C" + JALJ,
            "move\t$16,$17",
        ]))
        i = out.index("j\tfunc_800D910C")
        self.assertEqual(out[i + 1], "move\t$16,$17")        # untouched

    def test_no_load_delay_slot_not_rotated(self):
        # No load-delay nop before D (the load's delay is already filled) -> there
        # is nowhere legal to relocate the arg-move -> decline (never regress).
        out = self._rotate(self._body([
            "addu\t$2,$2,$5",
            "#maspsx_tailslot_pin $2",
            "j\tfunc_800D910C" + JALJ,
            "addu\t$4,$19,$zero",
        ], load_delay="addu\t$6,$6,$7"))  # load-delay filled, not a nop
        i = out.index("j\tfunc_800D910C")
        self.assertEqual(out[i + 1], "addu\t$4,$19,$zero")   # delay untouched

    def test_argmove_reads_dead_reg_not_rotated(self):
        # cond 6: if the arg-move READS the dead register, the value is NOT dead
        # (it feeds the call) -> decline.
        out = self._rotate(self._body([
            "addu\t$2,$2,$5",
            "#maspsx_tailslot_pin $2",
            "j\tfunc_800D910C" + JALJ,
            "move\t$4,$2",                # a0 = the "dead" value -> it's live
        ]))
        i = out.index("j\tfunc_800D910C")
        self.assertEqual(out[i + 1], "move\t$4,$2")

    def test_unconverted_jal_not_rotated(self):
        # Cond 1: without the jal->j stamp (callee not an evidence member) the tail
        # is still a jal -> pass never fires.
        out = self._rotate(self._body([
            "addu\t$2,$2,$5",
            "#maspsx_tailslot_pin $2",
            "j\tfunc_800D910C",           # NO jal->j marker
            "addu\t$4,$19,$zero",
        ]))
        i = out.index("j\tfunc_800D910C")
        self.assertEqual(out[i + 1], "addu\t$4,$19,$zero")

    def test_argmove_depends_on_load_not_rotated(self):
        # cond 7a: the arg-move reading the LOADED register ($3) cannot fill that
        # load's own delay slot (a load-use hazard) -> decline this slot.
        out = self._rotate(self._body([
            "addu\t$2,$2,$5",
            "#maspsx_tailslot_pin $2",
            "j\tfunc_800D910C" + JALJ,
            "move\t$4,$3",                # a0 depends on $3, the loaded value
        ]))
        i = out.index("j\tfunc_800D910C")
        self.assertEqual(out[i + 1], "move\t$4,$3")          # not rotated


class TestEmptySlotSinkArmB(unittest.TestCase):
    """LEAD 28 ARM B (empty-slot sink, "LEAD 28b"): sink a marker-pinned dead value
    into a converted tail ``j``'s EMPTY (``nop``) delay slot.

    Distinct from ARM A (rotation), which requires the branch delay to already hold
    the call's last arg-move. When the delay is a bare ``nop`` and gcc parks the
    pinned dead value standalone before the ``j`` (or schedules a rematerialised
    page-base to the top of the block), there is nothing to rotate -- ARM B sinks
    the pinned producer straight into the ``nop`` (net -1 word). It generalises
    LEAD 27's page-``lui`` sink onto the ``#maspsx_tailslot_pin`` marker and tolerates
    a NON-adjacent producer. End-to-end proof: the two-site func_818FEF80 dungeon
    MATCH (SiteB floated `lui $v1,0xfffe`, SiteC adjacent `subu $v0,$v0,$a0`).
    """

    def _sink(self, lines):
        mp = MaspsxProcessor([], sdata_limit=8)
        return strip_comments(mp._rotate_dead_value_into_tail_j_delay(lines))

    def _body(self, block, callee="func_80024800"):
        """`block` is the raw instruction stream of a single function body between
        `.ent`/`.end`; a fresh use of $2 follows (the next block)."""
        return [".ent\tfunc_TEST", *block, "lhu\t$2,20($19)", ".end\tfunc_TEST"]

    # --- positives -----------------------------------------------------------

    def test_adjacent_dead_alu_sunk(self):
        # SiteC shape: `subu $v0,$v0,$a0` immediately before the tail j, nop delay.
        out = self._sink(self._body([
            "subu\t$2,$2,$4",
            "#maspsx_tailslot_pin $2",
            "j\tfunc_80024954" + JALJ,
            "nop",
        ]))
        i = out.index("j\tfunc_80024954")
        self.assertEqual(out[i + 1], "subu\t$2,$2,$4")       # sunk into delay
        self.assertEqual(out.count("subu\t$2,$2,$4"), 1)     # standalone gone

    def test_floated_pagebase_sunk(self):
        # SiteB shape: gcc schedules the pinned `lui $v1,0xfffe` to the TOP of the
        # block (before two independent volatile ops); the marker sits by the j.
        # ARM B keys on the marker, back-finds the lui, and sinks it -- proving the
        # NON-adjacent tolerance LEAD 27 (cond 3 adjacency) lacked.
        out = self._sink(self._body([
            "lui\t$3,0xfffe",         # floated producer (writes $v1)
            "sh\t$4,10($7)",          # volatile store (reads $a0/$a3, not $v1)
            "lw\t$2,8($5)",           # volatile load (writes $v0, not $v1)
            "#maspsx_tailslot_pin $3",
            "j\tfunc_80024800" + JALJ,
            "nop",
        ]))
        i = out.index("j\tfunc_80024800")
        self.assertEqual(out[i + 1], "lui\t$3,0xfffe")       # sunk into delay
        self.assertEqual(out.count("lui\t$3,0xfffe"), 1)     # standalone gone
        # the intervening volatile ops keep their order and position
        self.assertEqual(out[i - 2], "sh\t$4,10($7)")
        self.assertEqual(out[i - 1], "lw\t$2,8($5)")

    # --- negatives (safety guards) -------------------------------------------

    def test_natural_dead_value_no_marker_not_sunk(self):
        # THE over-fire guard: identical shape (a dead ALU op before a converted
        # tail j with a nop delay) but NO marker -> a natural gcc schedule retail
        # leaves alone. ARM B MUST NOT fire.
        out = self._sink(self._body([
            "subu\t$2,$2,$4",
            "j\tfunc_80024954" + JALJ,
            "nop",
        ]))
        i = out.index("j\tfunc_80024954")
        self.assertEqual(out[i + 1], "nop")                  # delay untouched
        self.assertEqual(out.count("subu\t$2,$2,$4"), 1)     # D still standalone

    def test_marker_register_without_producer_not_sunk(self):
        # Marker names $v1 but the only sinkable dead value is in $v0 (no $v1
        # writer) -> no producer for the named reg -> decline.
        out = self._sink(self._body([
            "subu\t$2,$2,$4",
            "#maspsx_tailslot_pin $3",
            "j\tfunc_80024954" + JALJ,
            "nop",
        ]))
        i = out.index("j\tfunc_80024954")
        self.assertEqual(out[i + 1], "nop")
        self.assertEqual(out.count("subu\t$2,$2,$4"), 1)

    def test_live_reg_read_before_j_not_sunk(self):
        # $R is READ between the producer and the j (a store consumes it) -> not a
        # dead rematerialisation -> decline (never move a live value).
        out = self._sink(self._body([
            "subu\t$2,$2,$4",
            "sw\t$2,0($7)",           # reads $v0 -> $v0 is live
            "#maspsx_tailslot_pin $2",
            "j\tfunc_80024954" + JALJ,
            "nop",
        ]))
        i = out.index("j\tfunc_80024954")
        self.assertEqual(out[i + 1], "nop")
        self.assertIn("subu\t$2,$2,$4", out)

    def test_non_alu_producer_not_sunk(self):
        # The last writer of $R before the j is a LOAD (not a clean single-dest ALU
        # op) -> illegal to sink into a delay slot -> decline.
        out = self._sink(self._body([
            "lw\t$2,0($7)",
            "#maspsx_tailslot_pin $2",
            "j\tfunc_80024954" + JALJ,
            "nop",
        ]))
        i = out.index("j\tfunc_80024954")
        self.assertEqual(out[i + 1], "nop")
        self.assertIn("lw\t$2,0($7)", out)

    def test_label_between_producer_and_j_not_sunk(self):
        # A label between the producer and the j (a second entry) -> decline.
        out = self._sink(self._body([
            "subu\t$2,$2,$4",
            "$L99:",
            "#maspsx_tailslot_pin $2",
            "j\tfunc_80024954" + JALJ,
            "nop",
        ]))
        i = out.index("j\tfunc_80024954")
        self.assertEqual(out[i + 1], "nop")

    def test_single_word_li_sunk(self):
        # A `li` whose value has low16==0 (SiteB's `li $3,-131072` = 0xfffe0000)
        # expands to a single `lui` -> legal one-word delay fill -> sunk.
        out = self._sink(self._body([
            "li\t$3,-131072",
            "#maspsx_tailslot_pin $3",
            "j\tfunc_80024800" + JALJ,
            "nop",
        ]))
        i = out.index("j\tfunc_80024800")
        self.assertEqual(out[i + 1], "li\t$3,-131072")

    def test_multiword_li_not_sunk(self):
        # A `li` needing BOTH halves (`lui`+`ori`, two words) cannot fit one delay
        # slot -> decline (defensive: never emit a split constant into a delay).
        out = self._sink(self._body([
            "li\t$3,0x8002abcd",       # low16 != 0 and not addiu/ori-able -> 2 words
            "#maspsx_tailslot_pin $3",
            "j\tfunc_80024800" + JALJ,
            "nop",
        ]))
        i = out.index("j\tfunc_80024800")
        self.assertEqual(out[i + 1], "nop")            # delay untouched
        self.assertIn("li\t$3,0x8002abcd", out)        # producer left standalone

    def test_unconverted_jal_not_sunk(self):
        # Without the jal->j stamp (callee not evidence) the tail is still a jal ->
        # not a converted tail j -> ARM B never fires.
        out = self._sink(self._body([
            "subu\t$2,$2,$4",
            "#maspsx_tailslot_pin $2",
            "j\tfunc_80024954",       # NO jal->j marker
            "nop",
        ]))
        i = out.index("j\tfunc_80024954")
        self.assertEqual(out[i + 1], "nop")


if __name__ == "__main__":
    unittest.main()
