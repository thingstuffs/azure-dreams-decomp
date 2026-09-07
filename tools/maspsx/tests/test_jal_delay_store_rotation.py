import unittest

from maspsx import MaspsxProcessor

from .util import strip_comments


class TestRotateMarkedStoreIntoJalDelay(unittest.TestCase):
    """LEAD 30 (marker-gated): rotate a DELIBERATELY-PINNED store down into a REAL
    ``jal`` call's delay slot, lifting the filler gcc parked there up in front of
    the call.

    Blocking instance func_800463EC (MAIN, 2.7.2-cdk -O2, 294 words): retail holds
    ``sh $v1,0x8c($s2)`` pending until the ``RotAverage4`` delay slot -- after all
    six outgoing stack arguments -- and keeps the last stack-argument store
    ``sw $v0,0x24($sp)`` in front of the ``jal``. gcc's dbr does the opposite at
    every pinned compiler. Same multiset, same registers, same length: one
    length-preserving rotation apart.

    THE DISCRIMINATOR (same discipline as LEAD 27/28): the assembler differential
    was MEASURED -- genuine ASPSX 2.67/2.77/2.79/2.86 all assemble this gcc ``.s``
    to bytes identical to maspsx -- so NO shipped assembler performs this rotation
    and the pass must never fire on shape. It fires ONLY on the unforgeable
    ``#maspsx_jaldelay_pin $R`` marker emitted by the ``ASM_JALDELAY_PIN`` C macro.

    Unlike LEAD 27/28 this leaves a real call intact, moves a LIVE store (the
    callee reads the memory it writes) and changes no word count. End-to-end
    (gcc -> maspsx -> byte-exact) is proven by the func_800463EC MATCH banked at
    work/debt_20260803/maspsx_jaldelay/func_800463EC/oracle_summary_patched.json.
    """

    def _rotate(self, res):
        mp = MaspsxProcessor([], sdata_limit=8)
        return strip_comments(mp._rotate_marked_store_into_jal_delay(res))

    def _body(self, lines):
        return [".ent\tfunc_TEST", *lines, ".end\tfunc_TEST"]

    def _site(self, marker="#maspsx_jaldelay_pin $3", store="sh\t$3,140($18)",
              call="jal\tRotAverage4", delay="sw\t$2,36($sp)", window=None,
              lead=("lhu\t$3,4($2)",)):
        """The func_800463EC shape: a load feeding the pinned store, the marker,
        the store, a run of outgoing stack-argument setup, the call, its filler."""
        if window is None:
            window = [
                "sw\t$2,16($sp)",
                "addu\t$2,$19,16",
                "sw\t$2,20($sp)",
                "addu\t$2,$18,148",
            ]
        out = list(lead)
        if marker:
            out.append(marker)
        out += ["addu\t$2,$19,8", store, *window, call, delay,
                "sw\t$2,192($18)"]
        return self._body(out)

    # --- positive ------------------------------------------------------------

    def test_pinned_store_rotated_into_jal_delay(self):
        out = self._rotate(self._site())
        self.assertEqual(out, [
            ".ent\tfunc_TEST",
            "lhu\t$3,4($2)",
            "addu\t$2,$19,8",
            "sw\t$2,16($sp)",        # every window real shifts up one slot
            "addu\t$2,$19,16",
            "sw\t$2,20($sp)",
            "addu\t$2,$18,148",
            "sw\t$2,36($sp)",        # M lifted in front of the call
            "jal\tRotAverage4",
            "sh\t$3,140($18)",       # D now fills the call's delay slot
            "sw\t$2,192($18)",
            ".end\tfunc_TEST",
        ])

    def test_length_is_preserved(self):
        src = self._site()
        out = self._rotate(src)
        self.assertEqual(len(out), len(strip_comments(src)))

    def test_marker_below_the_store_also_fires(self):
        # gcc schedules the pin's liveness tail freely: on the blocking instance the
        # marker lands ABOVE the store, but BELOW must work identically -- the pass
        # finds D by last-writer search, not by marker adjacency.
        out = self._rotate(self._body([
            "lhu\t$3,4($2)",
            "addu\t$2,$19,8",
            "sh\t$3,140($18)",
            "#maspsx_jaldelay_pin $3",
            "sw\t$2,16($sp)",
            "addu\t$2,$18,148",
            "jal\tRotAverage4",
            "sw\t$2,36($sp)",
        ]))
        i = out.index("jal\tRotAverage4")
        self.assertEqual(out[i + 1], "sh\t$3,140($18)")
        self.assertEqual(out[i - 1], "sw\t$2,36($sp)")

    def test_store_immediately_before_the_call_is_a_plain_swap(self):
        # Degenerate window (D is the last real before the jal): the rotation
        # collapses to a two-line swap, which is still exactly retail's order.
        out = self._rotate(self._body([
            "lhu\t$3,4($2)",
            "#maspsx_jaldelay_pin $3",
            "sh\t$3,140($18)",
            "jal\tRotAverage4",
            "sw\t$2,36($sp)",
        ]))
        self.assertEqual(out, [
            ".ent\tfunc_TEST",
            "lhu\t$3,4($2)",
            "sw\t$2,36($sp)",
            "jal\tRotAverage4",
            "sh\t$3,140($18)",
            ".end\tfunc_TEST",
        ])

    def test_last_store_of_the_pinned_reg_is_the_one_rotated(self):
        # Two stores of $3 before the call: the pin names the value LIVE at the
        # call, so the LAST one is D (same rule as LEAD 28 ARM B's last-writer).
        out = self._rotate(self._body([
            "lhu\t$3,4($2)",
            "#maspsx_jaldelay_pin $3",
            "sh\t$3,132($18)",
            "sh\t$3,140($18)",
            "addu\t$2,$18,148",
            "jal\tRotAverage4",
            "sw\t$2,36($sp)",
        ]))
        i = out.index("jal\tRotAverage4")
        self.assertEqual(out[i + 1], "sh\t$3,140($18)")
        self.assertEqual(out.count("sh\t$3,132($18)"), 1)   # untouched
        self.assertEqual(out.count("sh\t$3,140($18)"), 1)   # moved, not copied

    # --- negatives (safety guards) -------------------------------------------

    def test_no_marker_not_rotated(self):
        # THE over-fire guard: the identical shape with NO marker is what every
        # unmarked candidate in the census looks like. Must not fire.
        out = self._rotate(self._site(marker=None))
        i = out.index("jal\tRotAverage4")
        self.assertEqual(out[i + 1], "sw\t$2,36($sp)")
        self.assertEqual(out[i - 1], "addu\t$2,$18,148")

    def test_marker_register_mismatch_not_rotated(self):
        out = self._rotate(self._site(marker="#maspsx_jaldelay_pin $4"))
        i = out.index("jal\tRotAverage4")
        self.assertEqual(out[i + 1], "sw\t$2,36($sp)")

    def test_nop_delay_slot_not_rotated(self):
        # A bare nop delay would make this a length-CHANGING sink -- LEAD 28 ARM B's
        # shape, governed by a different marker. Decline.
        out = self._rotate(self._site(delay="nop"))
        i = out.index("jal\tRotAverage4")
        self.assertEqual(out[i + 1], "nop")

    def test_converted_tail_j_not_rotated(self):
        # A `j SYM` is LEAD 18/22's converted tail; this pass owns real calls only.
        out = self._rotate(self._site(call="j\tRotAverage4"))
        i = out.index("j\tRotAverage4")
        self.assertEqual(out[i + 1], "sw\t$2,36($sp)")

    def test_indirect_jalr_not_rotated(self):
        out = self._rotate(self._site(call="jalr\t$25"))
        i = out.index("jalr\t$25")
        self.assertEqual(out[i + 1], "sw\t$2,36($sp)")

    def test_load_inside_the_window_not_rotated(self):
        # Never reorder a store past a load -- the one direction that can change
        # what the program means.
        out = self._rotate(self._site(window=[
            "sw\t$2,16($sp)", "lw\t$2,8($19)", "addu\t$2,$18,148"]))
        i = out.index("jal\tRotAverage4")
        self.assertEqual(out[i + 1], "sw\t$2,36($sp)")

    def test_same_base_store_inside_the_window_not_rotated(self):
        # A window store through D's own base register could alias D. Decline.
        out = self._rotate(self._site(window=[
            "sw\t$2,16($sp)", "sw\t$2,144($18)", "addu\t$2,$18,148"]))
        i = out.index("jal\tRotAverage4")
        self.assertEqual(out[i + 1], "sw\t$2,36($sp)")

    def test_window_writing_the_store_base_not_rotated(self):
        out = self._rotate(self._site(window=[
            "sw\t$2,16($sp)", "addu\t$18,$18,$4", "addu\t$2,$18,148"]))
        i = out.index("jal\tRotAverage4")
        self.assertEqual(out[i + 1], "sw\t$2,36($sp)")

    def test_window_writing_the_pinned_reg_not_rotated(self):
        out = self._rotate(self._site(window=[
            "sw\t$2,16($sp)", "addu\t$3,$3,$4", "addu\t$2,$18,148"]))
        i = out.index("jal\tRotAverage4")
        self.assertEqual(out[i + 1], "sw\t$2,36($sp)")

    def test_real_nop_inside_the_window_not_rotated(self):
        # A nop in the window is a hazard filler whose shadow would shift with it.
        out = self._rotate(self._site(window=[
            "sw\t$2,16($sp)", "nop", "addu\t$2,$18,148"]))
        i = out.index("jal\tRotAverage4")
        self.assertEqual(out[i + 1], "sw\t$2,36($sp)")

    def test_label_inside_the_window_not_rotated(self):
        # A second entry into the window means D would be skipped on that path.
        out = self._rotate(self._site(window=[
            "sw\t$2,16($sp)", "$L7:", "addu\t$2,$18,148"]))
        i = out.index("jal\tRotAverage4")
        self.assertEqual(out[i + 1], "sw\t$2,36($sp)")

    def test_branch_inside_the_window_not_rotated(self):
        out = self._rotate(self._site(window=[
            "sw\t$2,16($sp)", "beq\t$4,$0,$L7", "addu\t$2,$18,148"]))
        i = out.index("jal\tRotAverage4")
        self.assertEqual(out[i + 1], "sw\t$2,36($sp)")

    def test_second_call_between_marker_and_target_not_rotated(self):
        # The marker must govern exactly ONE call; an intervening call would both
        # make "the next jal" ambiguous and let D cross a callee that observes it.
        out = self._rotate(self._body([
            "lhu\t$3,4($2)",
            "#maspsx_jaldelay_pin $3",
            "sh\t$3,140($18)",
            "jal\tSetRotMatrix",
            "nop",
            "addu\t$2,$18,148",
            "jal\tRotAverage4",
            "sw\t$2,36($sp)",
        ]))
        i = out.index("jal\tRotAverage4")
        self.assertEqual(out[i + 1], "sw\t$2,36($sp)")

    def test_delay_filler_writing_the_pinned_reg_not_rotated(self):
        # M and D invert their relative order, so M must not feed D.
        out = self._rotate(self._site(delay="addu\t$3,$4,$5"))
        i = out.index("jal\tRotAverage4")
        self.assertEqual(out[i + 1], "addu\t$3,$4,$5")

    def test_delay_filler_through_the_store_base_not_rotated(self):
        out = self._rotate(self._site(delay="sw\t$2,36($18)"))
        i = out.index("jal\tRotAverage4")
        self.assertEqual(out[i + 1], "sw\t$2,36($18)")

    def test_delay_filler_touching_ra_not_rotated(self):
        # M crosses the ``jal``, the one instruction that redefines $ra.
        out = self._rotate(self._site(delay="sw\t$31,36($sp)"))
        i = out.index("jal\tRotAverage4")
        self.assertEqual(out[i + 1], "sw\t$31,36($sp)")

    def test_macro_delay_filler_not_rotated(self):
        # `la` can assemble to two words; lifting it out of a delay slot is not a
        # word-for-word rotation.
        out = self._rotate(self._site(delay="la\t$2,D_80083160"))
        i = out.index("jal\tRotAverage4")
        self.assertEqual(out[i + 1], "la\t$2,D_80083160")

    def test_symbolic_store_operand_not_rotated(self):
        # Only the numeric off($base) form has a retail witness (and only it is
        # guaranteed single-word without an $at expansion).
        out = self._rotate(self._site(store="sh\t$3,D_1F80008C"))
        i = out.index("jal\tRotAverage4")
        self.assertEqual(out[i + 1], "sw\t$2,36($sp)")

    def test_out_of_range_store_offset_not_rotated(self):
        out = self._rotate(self._site(store="sh\t$3,70000($18)"))
        i = out.index("jal\tRotAverage4")
        self.assertEqual(out[i + 1], "sw\t$2,36($sp)")

    def test_pinned_reg_redefined_after_its_store_not_rotated(self):
        # $3 is rewritten between the store and the call, so the value the marker
        # pins is no longer the one that store wrote. Decline.
        out = self._rotate(self._body([
            "lhu\t$3,4($2)",
            "#maspsx_jaldelay_pin $3",
            "sh\t$3,140($18)",
            "addu\t$3,$4,$5",
            "addu\t$2,$18,148",
            "jal\tRotAverage4",
            "sw\t$2,36($sp)",
        ]))
        i = out.index("jal\tRotAverage4")
        self.assertEqual(out[i + 1], "sw\t$2,36($sp)")

    def test_load_shadow_above_the_store_is_preserved(self):
        # D was filling the load-delay of the load above it; the real that would
        # slide into D's slot reads that load's destination, so rotating would
        # expose the hazard. Decline.
        out = self._rotate(self._body([
            "#maspsx_jaldelay_pin $3",
            "lw\t$4,8($19)",
            "sh\t$3,140($18)",
            "addu\t$5,$4,$6",
            "addu\t$2,$18,148",
            "jal\tRotAverage4",
            "sw\t$2,36($sp)",
        ]))
        i = out.index("jal\tRotAverage4")
        self.assertEqual(out[i + 1], "sw\t$2,36($sp)")

    def test_marker_in_a_different_block_not_rotated(self):
        # The raw marker scan stops at any label: a marker from an earlier block
        # cannot authorise a rotation here.
        out = self._rotate(self._body([
            "#maspsx_jaldelay_pin $3",
            "sh\t$3,140($18)",
            "$L7:",
            "addu\t$2,$18,148",
            "jal\tRotAverage4",
            "sw\t$2,36($sp)",
        ]))
        i = out.index("jal\tRotAverage4")
        self.assertEqual(out[i + 1], "sw\t$2,36($sp)")


class TestJalDelayPinMarkerIsTransparent(unittest.TestCase):
    """The marker must not shadow the real next instruction.

    ``get_next_instruction`` drives every load-delay decision and treats any
    ``#`` comment other than a small allow-list as an instruction. A pin comment
    sitting between a load and its user would therefore be asked
    ``line_loads_from_reg`` (always False for a bare comment) and the required
    hazard ``nop`` would be silently dropped. ``is_instruction`` skips the LEAD 30
    marker so the scan looks through it.
    """

    def test_nop_still_emitted_across_the_marker(self):
        mp = MaspsxProcessor([
            ".ent\tfunc_TEST",
            "lw\t$3,4($2)",
            "#maspsx_jaldelay_pin $3",
            "addu\t$4,$3,$5",
            ".end\tfunc_TEST",
        ], sdata_limit=8)
        out = mp.process_lines()
        stripped = strip_comments(out)
        i = stripped.index("lw\t$3,4($2)")
        self.assertEqual(stripped[i + 1], "nop")
        self.assertEqual(stripped[i + 2], "addu\t$4,$3,$5")

    def test_marker_survives_process_line(self):
        mp = MaspsxProcessor([
            ".ent\tfunc_TEST",
            "sh\t$3,140($18)",
            "#maspsx_jaldelay_pin $3",
            ".end\tfunc_TEST",
        ], sdata_limit=8)
        out = mp.process_lines()
        self.assertTrue(any("maspsx_jaldelay_pin $3" in line for line in out))


if __name__ == "__main__":
    unittest.main()
