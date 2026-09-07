import unittest

from maspsx import MaspsxProcessor

from .util import strip_comments


def code(lines):
    """Stripped-comment code text for every real (non-directive/-label) line."""
    out = []
    for c in strip_comments(lines):
        if (not c or c.startswith(".") or c.endswith(":")
                or c.startswith("$L") or c.startswith("glabel")):
            continue
        out.append(c)
    return out


class TestRotateV0IntoBranchDelay(unittest.TestCase):
    """LEAD 26: rotate a converted sibcall/noreturn ``j``'s ``$v0``-setup delay
    slot up into the preceding BACKWARD conditional branch's empty ``nop`` slot.

    The pass runs LAST, on the OUTPUT of the LEAD 18/22 jal->j conversions, so
    these drive ``_rotate_sibcall_v0_into_branch_delay`` directly on hand-built
    post-conversion streams (with the ``jal->j`` marker the conversion stamps).
    Fixtures mirror the byte-verified confirmation sites: func_8009B70C site 3
    (positive) + sites 1/2 (filled-slot controls), func_800C7F80 idx 121
    (positive) + idx 37/43 (controls), and main func_8001A444 (forward-branch).
    """

    def _rot(self, lines):
        mp = MaspsxProcessor([])
        return mp._rotate_sibcall_v0_into_branch_delay(lines)

    # A converted sibcall `j` line as the LEAD 22 pass emits it (marker present).
    _J = "j\tfunc_800A14F8\t# maspsx: arg sibcall jal->j (LEAD 22)"
    # A converted noreturn `j` line as the LEAD 18 pass emits it.
    _J18 = "j\tfunc_80176F10\t# maspsx: tail-call jal->j (LEAD 18)"

    def _fires(self, out):
        rot = [ln for ln in out if "LEAD 26 rotate" in ln]
        nop = [ln for ln in out if "LEAD 26 nop" in ln]
        return len(rot) == 1 and len(nop) == 1, rot, nop

    # --- POSITIVE fixtures -----------------------------------------------------

    def test_positive_move_v0_zero_backedge_reload(self):
        # func_8009B70C site 3: backward bne, empty slot, converted `j`, the
        # `move v0,zero` (== `addu $2,$0,$zero`) in the j slot; the loop head at
        # the target reloads `lhu $2,0($fp)` -> $v0 dead on the taken edge.
        lines = [
            ".ent\tfunc_8009B70C",
            "$L48:",
            "lhu\t$2,0($fp)",          # target: WRITES $v0 first -> dead
            "andi\t$2,$2,0x0002",
            "bne\t$2,$0,$L48",          # BACKWARD conditional branch
            "nop",                      # empty branch delay slot
            self._J,                    # converted sibcall j
            "addu\t$2,$0,$zero",        # j delay slot: move v0,zero
            ".end\tfunc_8009B70C",
        ]
        out = self._rot(lines)
        fired, rot, _ = self._fires(out)
        self.assertTrue(fired, out)
        # branch slot now holds the move; j slot now holds nop.
        self.assertIn("addu\t$2,$0,$zero", rot[0])
        c = code(out)
        # order: ...; bne; move v0,zero; j; nop
        bi = c.index("bne\t$2,$0,$L48")
        self.assertEqual(c[bi + 1], "addu\t$2,$0,$zero")
        self.assertTrue(c[bi + 2].startswith("j\tfunc_800A14F8"))
        self.assertEqual(c[bi + 3], "nop")

    def test_positive_li_v0_1_target_jal_clobbers(self):
        # func_800C7F80 idx 121: backward bne, empty slot, `li v0,1` in the j
        # slot; the target block starts with a `jal` whose return clobbers $v0.
        lines = [
            ".ent\tfunc_800C7F80",
            "$L11:",
            "jal\tfunc_8003FC64",       # target: call clobbers $v0 -> dead
            "li\t$4,2",                 # (jal delay slot: no $v0 read)
            "addu\t$16,$2,$zero",       # reads $2 -- but it's the call return
            "slt\t$2,$17,4",
            "bne\t$2,$0,$L11",          # BACKWARD conditional branch
            "nop",
            "j\tfunc_800CD8E4\t# maspsx: arg sibcall jal->j (LEAD 22)",
            "li\t$2,1",                 # j delay slot: li v0,1
            ".end\tfunc_800C7F80",
        ]
        out = self._rot(lines)
        fired, rot, _ = self._fires(out)
        self.assertTrue(fired, out)
        self.assertIn("li\t$2,1", rot[0])

    def test_positive_lead18_marker_also_converts(self):
        # A `j` produced by the LEAD 18 (noreturn) path is equally eligible.
        lines = [
            ".ent\tfunc_x",
            "$L4:",
            "move\t$2,$4",              # target writes $v0 -> dead
            "bne\t$16,$0,$L4",
            "nop",
            self._J18,
            "addu\t$2,$0,$zero",
            ".end\tfunc_x",
        ]
        out = self._rot(lines)
        fired, _, _ = self._fires(out)
        self.assertTrue(fired, out)

    # --- MUST-NOT-FIRE controls ------------------------------------------------

    def test_nofire_forward_branch(self):
        # cond 4: forward branch (target emitted AFTER the branch) -- main
        # func_8001A444 direction. Even with a $v0 setup, do NOT rotate.
        lines = [
            ".ent\tfunc_fwd",
            "bne\t$16,$0,$L4",          # FORWARD conditional branch
            "nop",
            self._J,
            "addu\t$2,$0,$zero",
            "$L4:",
            "move\t$2,$4",
            ".end\tfunc_fwd",
        ]
        out = self._rot(lines)
        fired, _, _ = self._fires(out)
        self.assertFalse(fired, out)

    def test_nofire_j_slot_not_v0(self):
        # cond 2: the j delay slot writes $s0, not $v0 (main func_8001A444's real
        # shape: `addiu $s0,$zero,1`). Do NOT rotate.
        lines = [
            ".ent\tfunc_s0",
            "$L4:",
            "move\t$2,$4",
            "bne\t$16,$0,$L4",
            "nop",
            self._J,
            "addiu\t$16,$0,1",          # writes $s0, not $v0
            ".end\tfunc_s0",
        ]
        out = self._rot(lines)
        fired, _, _ = self._fires(out)
        self.assertFalse(fired, out)

    def test_nofire_j_slot_memory_store(self):
        # cond 2: never rotate a store (touches memory) even to $v0's address.
        lines = [
            ".ent\tfunc_mem",
            "$L4:",
            "lhu\t$2,0($fp)",
            "bne\t$16,$0,$L4",
            "nop",
            self._J,
            "sw\t$2,0($4)",             # store, not a move/li
            ".end\tfunc_mem",
        ]
        out = self._rot(lines)
        fired, _, _ = self._fires(out)
        self.assertFalse(fired, out)

    def test_nofire_filled_branch_slot(self):
        # cond 3: the branch delay slot is filled by the loop induction
        # (func_8009B70C sites 1/2) -- there is no empty slot to rotate into.
        lines = [
            ".ent\tfunc_filled",
            "$L19:",
            "lhu\t$2,0($fp)",
            "slt\t$2,$2,$5",
            "bne\t$2,$0,$L19",
            "addu\t$16,$16,1",          # induction FILLS the branch slot
            self._J,
            "addu\t$2,$0,$zero",
            ".end\tfunc_filled",
        ]
        out = self._rot(lines)
        fired, _, _ = self._fires(out)
        self.assertFalse(fired, out)

    def test_nofire_label_between_branch_slot_and_j(self):
        # A label between the empty branch delay slot and the converted `j` may
        # be an independent entry path. Rotating the $v0 setup above the label
        # would skip it when control enters at that label.
        lines = [
            ".ent\tfunc_label_entry",
            "$L4:",
            "lhu\t$2,0($fp)",
            "bne\t$16,$0,$L4",
            "nop",
            "$Lentry:",
            self._J,
            "addu\t$2,$0,$zero",
            ".end\tfunc_label_entry",
        ]
        out = self._rot(lines)
        fired, _, _ = self._fires(out)
        self.assertFalse(fired, out)

    def test_nofire_jal_preceded_j(self):
        # cond 3: the instruction before the `j` is a jal (func_800C7F80 idx 37),
        # not a conditional branch. Do NOT rotate.
        lines = [
            ".ent\tfunc_jalpre",
            "$L14:",
            "lhu\t$2,0($fp)",
            "jal\tfunc_800CD6AC",
            "li\t$5,16",                # jal delay slot (not a branch slot)
            "j\tfunc_800CD8E4\t# maspsx: arg sibcall jal->j (LEAD 22)",
            "li\t$2,1",
            ".end\tfunc_jalpre",
        ]
        out = self._rot(lines)
        fired, _, _ = self._fires(out)
        self.assertFalse(fired, out)

    def test_nofire_v0_read_at_target(self):
        # cond 5: the branch target READS $v0 before any write -> $v0 is LIVE on
        # the taken edge -> unsafe, do NOT rotate.
        lines = [
            ".ent\tfunc_live",
            "$L4:",
            "addu\t$17,$2,$zero",       # READS $v0 first -> live
            "move\t$2,$4",
            "bne\t$16,$0,$L4",
            "nop",
            self._J,
            "addu\t$2,$0,$zero",
            ".end\tfunc_live",
        ]
        out = self._rot(lines)
        fired, _, _ = self._fires(out)
        self.assertFalse(fired, out)

    def test_nofire_control_leaves_before_write(self):
        # cond 5: the target reaches a non-call branch before any $v0 write ->
        # unclear liveness -> bail.
        lines = [
            ".ent\tfunc_ctrl",
            "$L4:",
            "addu\t$17,$18,$zero",      # neither reads nor writes $v0
            "bne\t$19,$0,$L9",          # control leaves before a $v0 write
            "nop",
            "bne\t$16,$0,$L4",
            "nop",
            self._J,
            "addu\t$2,$0,$zero",
            "$L9:",
            "move\t$2,$0",
            ".end\tfunc_ctrl",
        ]
        out = self._rot(lines)
        fired, _, _ = self._fires(out)
        self.assertFalse(fired, out)

    def test_nofire_j_not_converted(self):
        # cond 1: the `j` carries no jal->j conversion marker (this run did not
        # produce it) -- a hand-written / non-sibcall tail j. Do NOT rotate.
        lines = [
            ".ent\tfunc_raw",
            "$L4:",
            "lhu\t$2,0($fp)",
            "bne\t$16,$0,$L4",
            "nop",
            "j\tfunc_800A14F8",         # NO marker
            "addu\t$2,$0,$zero",
            ".end\tfunc_raw",
        ]
        out = self._rot(lines)
        fired, _, _ = self._fires(out)
        self.assertFalse(fired, out)

    def test_nofire_backward_jr_target_boundary(self):
        # cond 5: end-of-function reached before any $v0 write -> bail.
        lines = [
            ".ent\tfunc_end",
            "$L4:",
            "addu\t$17,$18,$zero",      # no $v0 write before .end
            "bne\t$16,$0,$L4",
            "nop",
            self._J,
            "addu\t$2,$0,$zero",
            ".end\tfunc_end",
        ]
        out = self._rot(lines)
        fired, _, _ = self._fires(out)
        self.assertFalse(fired, out)


if __name__ == "__main__":
    unittest.main()
