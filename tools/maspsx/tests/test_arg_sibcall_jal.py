import os
import tempfile
import unittest
from pathlib import Path
from unittest import mock

from maspsx import MaspsxProcessor

from .util import strip_comments


class TestArgSibcallJalToJ(unittest.TestCase):
    """LEAD 22: retail/ASPSX emits a bare ``j CALLEE`` (no $ra write) for a
    tail-position call into an ARG-carrying sibcall *dispatcher* -- a callee
    reached only by ``j`` and never ``jal`` across MAIN.BIN -- where gcc + GNU as
    emit ``jal CALLEE`` (plus, branchy, a dead ``j $Lepilogue`` jump).

    The pass gates its ``jal``->``j`` shape test on membership in the binary-
    derived set (config/sibcall_syms.txt via ``tools/gen_sibcall_syms.py``). That
    membership gate is what distinguishes a true dispatcher from an ordinary
    RETURNING tail call (``return foo(x)``): both compile to byte-identical local
    shapes, so the shape test alone over-fires (the shape-only attempt regressed 66
    matched functions, e.g. func_8003E0C4->PopMatrix, func_80041BE4->func_80040A88).
    These tests drive the pass via a temp ``$MASPSX_SIBCALL_FILE`` fixture so they
    do not depend on the tracked config. Corpus proof: lead22_investigation.md.
    """

    def _run(self, lines, sibcall_syms=(), sdata_limit=8):
        # Point maspsx at a temp sibcall side-channel holding exactly the given
        # set (and an EMPTY noreturn side-channel so LEAD 18 never interferes).
        with tempfile.TemporaryDirectory() as d:
            sib = Path(d) / "sibcall_syms.txt"
            sib.write_text("".join(f"{s}\n" for s in sibcall_syms))
            nor = Path(d) / "noreturn_syms.txt"
            nor.write_text("")
            with mock.patch.dict(os.environ, {
                "MASPSX_SIBCALL_FILE": str(sib),
                "MASPSX_NORETURN_FILE": str(nor),
            }):
                mp = MaspsxProcessor(lines, sdata_limit=sdata_limit)
                return strip_comments(mp.process_lines())

    # --- fixtures --------------------------------------------------------------

    def _shape_b_body(self, name, callee):
        # Mirrors the real func_80020F68 @2.7.2 post-maspsx stream: a branchy
        # `return callee(args)` tail-call. The jal keeps its own reordered delay
        # slot (`sw $2,-16($17)`); an explicit dead `j $Lepilogue` (with a nop
        # delay slot) follows, and the shared epilogue lives at $L1.
        return [
            f".ent\t{name}",
            "subu\t$sp,$sp,32",
            "sw\t$31,24($sp)",
            "sw\t$17,20($sp)",
            "lw\t$2,56($4)",
            ".set\tnoreorder",
            "beq\t$2,$0,$L2",
            "nop",
            ".set\treorder",
            ".set\tnoreorder",
            ".set\tnomacro",
            f"jal\t{callee}",       # candidate sibcall
            "sw\t$2,-16($17)",       # jal's own delay slot (kept)
            ".set\tmacro",
            ".set\treorder",
            "j\t$L1",                # dead jump to the shared epilogue
            "nop",                   # its delay slot (deleted with it)
            "$L2:",
            "addu\t$4,$17,-32",
            ".set\tnoreorder",
            ".set\tnomacro",
            "jal\tfunc_8040316C",   # ordinary call (not in set) -> keep jal
            "sw\t$16,64($17)",
            ".set\tmacro",
            ".set\treorder",
            "$L1:",
            "lw\t$31,24($sp)",
            "lw\t$17,20($sp)",
            "addu\t$sp,$sp,32",
            "j\t$31",
            f".end\t{name}",
        ]

    def _shape_a_body(self, name, callee):
        # Mirrors func_800108D4 @2.8.1-G0: an empty-delay tail-call sitting
        # directly before an INLINE epilogue (no `j $Llabel`).
        return [
            f".ent\t{name}",
            "subu\t$sp,$sp,24",
            "sw\t$31,16($sp)",
            "move\t$4,$16",
            ".set\tnoreorder",
            ".set\tnomacro",
            f"jal\t{callee}",
            "nop",                   # empty delay slot
            ".set\tmacro",
            ".set\treorder",
            "lw\t$31,16($sp)",       # inline epilogue directly after
            "addu\t$sp,$sp,24",
            "j\t$31",
            f".end\t{name}",
        ]

    # --- SHAPE B ---------------------------------------------------------------

    def test_shape_b_member_is_rewritten(self):
        out = self._run(
            self._shape_b_body("func_80020F68", "func_80407FBC"),
            sibcall_syms=("func_80407FBC",),
        )
        self.assertIn("j\tfunc_80407FBC", out)
        self.assertNotIn("jal\tfunc_80407FBC", out)
        # the jal's own delay-slot store is preserved as the converted j's slot
        self.assertIn("sw\t$2,-16($17)", out)
        # the dead `j $L1` to the epilogue is deleted (commented out)
        self.assertNotIn("j\t$L1", out)
        # the ordinary non-member call keeps its jal
        self.assertIn("jal\tfunc_8040316C", out)

    def test_shape_b_non_member_kept(self):
        # SAME SHAPE B, but the callee is NOT in the sibcall set (the 66-regression
        # class: an ordinary returning tail call such as func_8003E0C4->PopMatrix).
        # Membership gate blocks the rewrite -> keeps jal, keeps `j $L1`.
        out = self._run(
            self._shape_b_body("func_8003E0C4", "PopMatrix"),
            sibcall_syms=("func_80407FBC",),  # some OTHER member; PopMatrix absent
        )
        self.assertIn("jal\tPopMatrix", out)
        self.assertNotIn("j\tPopMatrix", out)
        self.assertIn("j\t$L1", out)  # dead jump NOT deleted

    # --- SHAPE A ---------------------------------------------------------------

    def test_shape_a_member_is_rewritten(self):
        out = self._run(
            self._shape_a_body("func_800108D4", "func_80023954"),
            sibcall_syms=("func_80023954",),
        )
        self.assertIn("j\tfunc_80023954", out)
        self.assertNotIn("jal\tfunc_80023954", out)

    def test_shape_a_non_member_kept(self):
        # SAME SHAPE A with a non-member callee (the ordinary last-call-before-
        # return that the shape-only attempt wrongly flipped, breaking LEAD 18).
        out = self._run(
            self._shape_a_body("func_80013410", "func_800263C0"),
            sibcall_syms=("func_80023954",),  # member set without func_800263C0
        )
        self.assertIn("jal\tfunc_800263C0", out)
        self.assertNotIn("j\tfunc_800263C0", out)

    # --- func_8007BEF0 control (arg in own delay, inline epilogue, no j$L) ------

    def test_func_8007BEF0_shape_kept(self):
        # The one tail `jal` retail KEEPS: the callee's argument parked in the
        # jal's OWN delay slot with an inline epilogue and no `j $Llabel`. Even if
        # (hypothetically) added to the set, SHAPE A needs a nop delay (the arg is
        # in the slot) and SHAPE B needs a following `j $Llabel` (absent).
        lines = [
            ".ent\tfunc_80019A10",
            "subu\t$sp,$sp,24",
            "sw\t$31,20($sp)",
            ".set\tnoreorder",
            ".set\tnomacro",
            "jal\tfunc_8007BEF0",
            "li\t$4,0x00000001",    # ARG in the jal's own delay slot
            ".set\tmacro",
            ".set\treorder",
            "lw\t$31,20($sp)",       # inline epilogue
            "addu\t$sp,$sp,24",
            "j\t$31",
            ".end\tfunc_80019A10",
        ]
        out = self._run(lines, sibcall_syms=("func_8007BEF0",))
        self.assertIn("jal\tfunc_8007BEF0", out)
        self.assertNotIn("j\tfunc_8007BEF0", out)
        self.assertIn("li\t$4,0x00000001", out)

    # --- mid-function live fall-through (member, but not tail) ------------------

    def test_mid_function_live_fallthrough_kept(self):
        # A member callee whose call is followed by a live continuation (neither
        # the epilogue nor a `j $Llabel`) is a normal mid-function call -> keep jal.
        lines = [
            ".ent\tfunc_800206C8",
            "subu\t$sp,$sp,24",
            "sw\t$31,20($sp)",
            ".set\tnoreorder",
            ".set\tnomacro",
            "jal\tfunc_80407FBC",
            "move\t$4,$16",
            ".set\tmacro",
            ".set\treorder",
            "lw\t$2,0($16)",         # continuation, not epilogue
            "addu\t$16,$16,4",
            "lw\t$31,20($sp)",
            "addu\t$sp,$sp,24",
            "j\t$31",
            ".end\tfunc_800206C8",
        ]
        out = self._run(lines, sibcall_syms=("func_80407FBC",))
        self.assertIn("jal\tfunc_80407FBC", out)
        self.assertNotIn("j\tfunc_80407FBC", out)

    # --- indirect call never matches -------------------------------------------

    def test_indirect_call_not_rewritten(self):
        # An indirect `jalr $reg` in the same tail shape is never a direct symbol
        # sibcall and must not be touched.
        lines = [
            ".ent\tfunc_TEST",
            "subu\t$sp,$sp,24",
            "sw\t$31,16($sp)",
            "lw\t$25,0($4)",
            ".set\tnoreorder",
            ".set\tnomacro",
            "jalr\t$25",
            "nop",
            ".set\tmacro",
            ".set\treorder",
            "lw\t$31,16($sp)",
            "addu\t$sp,$sp,24",
            "j\t$31",
            ".end\tfunc_TEST",
        ]
        out = self._run(lines, sibcall_syms=("func_80407FBC",))
        self.assertIn("jalr\t$25", out)

    # --- empty set is a no-op --------------------------------------------------

    def test_empty_set_no_ops(self):
        out = self._run(self._shape_b_body("func_80020F68", "func_80407FBC"),
                        sibcall_syms=())
        self.assertIn("jal\tfunc_80407FBC", out)
        self.assertNotIn("j\tfunc_80407FBC", out)
        self.assertIn("j\t$L1", out)

    # --- SHAPE C (value-returning / dead-store sibcall) ------------------------

    def _shape_c_body(self, name, callee, delay="li\t$2,-1", jal_delay="nop"):
        # Mirrors func_800931C0's r<0 path @2.8.1 post-maspsx stream:
        #   jal callee ; nop ; j $L1 ; li $2,-1 ; ... $L1: <epilogue>
        # gcc parked the `return -1` value setup (`li $2,-1`) in the dead
        # `j $L1` delay slot; retail relocates it into the sibcall j delay.
        return [
            f".ent\t{name}",
            "subu\t$sp,$sp,32",
            "sw\t$31,24($sp)",
            "lw\t$2,0($4)",
            ".set\tnoreorder",
            ".set\tnomacro",
            f"jal\t{callee}",
            jal_delay,               # the jal's OWN delay slot
            ".set\tmacro",
            ".set\treorder",
            ".set\tnoreorder",
            ".set\tnomacro",
            "j\t$L1",                # dead jump to the shared epilogue
            delay,                   # X: the value setup parked here by gcc
            ".set\tmacro",
            ".set\treorder",
            "$L1:",
            "lw\t$31,24($sp)",
            "addu\t$sp,$sp,32",
            "j\t$31",
            f".end\t{name}",
        ]

    def test_shape_c_member_relocates_return_value(self):
        out = self._run(
            self._shape_c_body("func_800931C0", "func_80098B10"),
            sibcall_syms=("func_80098B10",),
        )
        # jal -> j
        self.assertIn("j\tfunc_80098B10", out)
        self.assertNotIn("jal\tfunc_80098B10", out)
        # the dead `j $L1` is deleted (commented out)
        self.assertNotIn("j\t$L1", out)
        # exactly one live `li $2,-1` survives (relocated into the j delay); the
        # original copy at the dead-jump slot is commented out.
        self.assertEqual(sum(1 for ln in out if ln.strip() == "li\t$2,-1"), 1)
        # and it must sit immediately after the converted sibcall `j`
        idx_j = next(i for i, ln in enumerate(out)
                     if ln.strip() == "j\tfunc_80098B10")
        self.assertEqual(out[idx_j + 1].strip(), "li\t$2,-1")

    def test_shape_c_non_member_kept(self):
        # Same SHAPE C but the callee is NOT in the set -> keep jal, keep j $L1.
        out = self._run(
            self._shape_c_body("func_800931C0", "func_80040A88"),
            sibcall_syms=("func_80098B10",),  # some other member
        )
        self.assertIn("jal\tfunc_80040A88", out)
        self.assertNotIn("j\tfunc_80040A88", out)
        self.assertIn("j\t$L1", out)

    def test_shape_c_nonnop_jal_delay_kept(self):
        # If the jal's OWN delay slot is NOT a nop, there is nothing to displace
        # into and two instructions would compete for one slot -> keep jal.
        # (This is the func_800ABC4C investigation-only shape the run must NOT
        # widen for.)
        out = self._run(
            self._shape_c_body("func_800ABC4C", "func_80098B10",
                               jal_delay="addiu\t$4,$4,12"),
            sibcall_syms=("func_80098B10",),
        )
        self.assertIn("jal\tfunc_80098B10", out)
        self.assertNotIn("j\tfunc_80098B10", out)

    def test_shape_c_load_in_delay_kept(self):
        # A LOAD in the dead-jump delay slot is NOT a safe relocation target
        # (it would need a use-delay after the jump) -> keep jal, keep j $L1.
        out = self._run(
            self._shape_c_body("func_TEST", "func_80098B10",
                               delay="lw\t$2,0($4)"),
            sibcall_syms=("func_80098B10",),
        )
        self.assertIn("jal\tfunc_80098B10", out)
        self.assertNotIn("j\tfunc_80098B10", out)
        self.assertIn("j\t$L1", out)


if __name__ == "__main__":
    unittest.main()
