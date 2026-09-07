import os
import tempfile
import unittest
from pathlib import Path
from unittest import mock

from maspsx import MaspsxProcessor

from .util import strip_comments


class TestElideRaOnlyFrameForNoreturnTail(unittest.TestCase):
    """LEAD 19 (CLASS-A): whole-frame elision for a single-call noreturn-tail
    function whose stack frame exists ONLY to save $ra for that call.

    Retail/ASPSX emits NO prologue and NO epilogue for such a function: once the
    tail call never returns, the saved $ra is dead and the frame is pure
    overhead. gcc always builds it. This pass deletes the prologue
    (``subu/addiu $sp`` + ``sw $ra``) and the epilogue teardown
    (``lw $ra`` + ``addu/addiu $sp``), leaving the terminal ``jr $ra``/nop, and
    completes the tail ``jal``->``j`` if _rewrite_tail_call_jal_to_j had left it.

    Firing keys entirely on the gcc-emitted ``.mask``/``.fmask``/``.frame``
    directives plus the source-derived noreturn side-channel
    (``config/noreturn_syms.txt`` / ``$MASPSX_NORETURN_FILE``); these tests drive
    it via a temp side-channel fixture. Census proof (zero counterexamples across
    521 MAIN.BIN functions): build/tmp_infra/lead19_investigation.md.
    """

    def _run(self, lines, noreturn_syms=(), sibcall_syms=(), sdata_limit=8,
             retain_tail_frame=0, preserve_return_delay=False):
        with tempfile.TemporaryDirectory() as d:
            f = Path(d) / "noreturn_syms.txt"
            f.write_text("".join(f"{s}\n" for s in noreturn_syms))
            sf = Path(d) / "sibcall_syms.txt"
            sf.write_text("".join(f"{s}\n" for s in sibcall_syms))
            env = {
                "MASPSX_NORETURN_FILE": str(f),
                # Isolate from the real config/sibcall_syms.txt so the LEAD 23
                # (noreturn|sibcall) gate sees only the syms a test declares.
                "MASPSX_SIBCALL_FILE": str(sf),
            }
            with mock.patch.dict(os.environ, env):
                mp = MaspsxProcessor(
                    lines,
                    sdata_limit=sdata_limit,
                    retain_tail_frame=retain_tail_frame,
                    preserve_return_delay=preserve_return_delay,
                )
                return strip_comments(mp.process_lines())

    def _classA(
        self,
        name="func_8001D6C8",
        callee="func_80404700",
        mask="0x80000000,-8",
        fmask="0x00000000,0",
        frame="$sp,24,$31\t\t# vars= 0, regs= 1/0, args= 16, extra= 0",
        prologue=("subu\t$sp,$sp,24", "sw\t$31,16($sp)"),
        epilogue=("lw\t$31,16($sp)", "addu\t$sp,$sp,24"),
        body_extra=(),
        second_call=None,
    ):
        """A class-A shape: ra-only frame whose sole call is a noreturn tail call
        reached via a branch (so _rewrite_tail_call_jal_to_j rewrites it to `j`
        first). Knobs let each negative flip exactly one firing condition."""
        lines = [
            f".ent\t{name}",
            ".set\tnoreorder",
            f"{name}:",
            f".frame\t{frame}",
            f".mask\t{mask}",
            f".fmask\t{fmask}",
        ]
        lines += list(prologue)
        lines += [
            "lw\t$2,4($4)",
            "beq\t$2,$0,$L2",
            "sw\t$0,628($4)",
        ]
        lines += list(body_extra)
        lines += [
            f"jal\t{callee}",
            "sw\t$2,644($4)",
        ]
        if second_call is not None:
            lines += [f"jal\t{second_call}", "nop"]
        lines += ["$L2:"]
        lines += list(epilogue)
        lines += ["j\t$31", f".end\t{name}"]
        return lines

    # ---- positives -------------------------------------------------------

    def test_classA_frame_is_elided(self):
        out = self._run(self._classA(), noreturn_syms=("func_80404700",))
        # prologue + epilogue frame instructions are gone
        self.assertNotIn("subu\t$sp,$sp,24", out)
        self.assertNotIn("sw\t$31,16($sp)", out)
        self.assertNotIn("lw\t$31,16($sp)", out)
        self.assertNotIn("addu\t$sp,$sp,24", out)
        # tail call is a `j`, the terminal return survives, no `jal` remains
        self.assertIn("j\tfunc_80404700", out)
        self.assertNotIn("jal\tfunc_80404700", out)
        self.assertIn("j\t$31", out)
        # no residual $sp reference in any real instruction (the `.frame`
        # directive still names $sp but is assembled to no bytes)
        self.assertFalse([l for l in out if "$sp" in l and not l.startswith(".")])

    def test_classA_completes_jal_when_tail_precedes_epilogue(self):
        # When the tail jal sits directly before the epilogue,
        # _rewrite_tail_call_jal_to_j leaves it a `jal` (its is_return_epilogue
        # guard). Frame elision makes it a genuine tail call, so LEAD 19 both
        # elides the frame AND completes the jal->j.
        lines = [
            ".ent\tfunc_800111D4",
            ".set\tnoreorder",
            "func_800111D4:",
            ".frame\t$sp,24,$31\t\t# vars= 0, regs= 1/0, args= 16, extra= 0",
            ".mask\t0x80000000,-8",
            ".fmask\t0x00000000,0",
            "subu\t$sp,$sp,24",
            "sw\t$31,16($sp)",
            "lw\t$2,4($4)",
            "sw\t$0,0($4)",
            "jal\tfunc_80024204",
            "sw\t$2,644($4)",
            "lw\t$31,16($sp)",
            "addu\t$sp,$sp,24",
            "j\t$31",
            ".end\tfunc_800111D4",
        ]
        out = self._run(lines, noreturn_syms=("func_80024204",))
        self.assertNotIn("subu\t$sp,$sp,24", out)
        self.assertNotIn("sw\t$31,16($sp)", out)
        self.assertNotIn("lw\t$31,16($sp)", out)
        self.assertNotIn("addu\t$sp,$sp,24", out)
        self.assertIn("j\tfunc_80024204", out)
        self.assertNotIn("jal\tfunc_80024204", out)
        self.assertIn("j\t$31", out)

    def test_classA_can_retain_evidence_selected_partial_frame(self):
        out = self._run(
            self._classA(),
            noreturn_syms=("func_80404700",),
            retain_tail_frame=8,
        )
        self.assertIn("addiu\t$sp,$sp,-8", out)
        self.assertIn("addiu\t$sp,$sp,8", out)
        self.assertNotIn("sw\t$31,16($sp)", out)
        self.assertNotIn("lw\t$31,16($sp)", out)
        self.assertIn("j\tfunc_80404700", out)

    def test_classA_can_preserve_evidence_selected_return_delay(self):
        lines = self._classA(
            body_extra=("sw\t$2,4($4)",),
            epilogue=("lw\t$31,16($sp)", "sw\t$2,8($4)", "addu\t$sp,$sp,24"),
        )
        lines.insert(-1, "nop")
        out = self._run(
            lines,
            noreturn_syms=("func_80404700",),
            preserve_return_delay=True,
        )
        self.assertIn("sw\t$2,8($4)", out)
        ret = out.index("j\t$31")
        self.assertEqual(out[ret + 1], "nop")

    # ---- negatives (frame must be KEPT) ----------------------------------

    def _assert_frame_kept(self, out):
        self.assertIn("subu\t$sp,$sp,24", out)
        self.assertIn("sw\t$31,16($sp)", out)
        self.assertIn("lw\t$31,16($sp)", out)
        self.assertIn("addu\t$sp,$sp,24", out)

    def test_second_call_keeps_frame(self):
        # Two calls -> the frame genuinely carries $ra across a returning call.
        # (The noreturn tail may still be jal->j'd by LEAD 18; the frame stays.)
        out = self._run(
            self._classA(second_call="func_800263C0"),
            noreturn_syms=("func_80404700",),
        )
        self._assert_frame_kept(out)

    def test_callee_saved_mask_bit_keeps_frame(self):
        # `.mask` carries a callee-saved GPR ($s0 = bit 16) besides $ra -> the
        # frame is real. There is a matching `sw $16` spill in the prologue.
        out = self._run(
            self._classA(
                mask="0x80010000,-8",
                prologue=("subu\t$sp,$sp,24", "sw\t$31,16($sp)", "sw\t$16,8($sp)"),
                epilogue=("lw\t$31,16($sp)", "lw\t$16,8($sp)", "addu\t$sp,$sp,24"),
            ),
            noreturn_syms=("func_80404700",),
        )
        self._assert_frame_kept(out)
        self.assertIn("sw\t$16,8($sp)", out)

    def test_local_vars_in_frame_keeps_frame(self):
        # `.frame` with vars>0 -> the frame holds locals, not just $ra.
        out = self._run(
            self._classA(
                frame="$sp,24,$31\t\t# vars= 8, regs= 1/0, args= 16, extra= 0",
            ),
            noreturn_syms=("func_80404700",),
        )
        self._assert_frame_kept(out)

    def test_extra_sp_store_keeps_frame(self):
        # An sp-relative store other than the ra-save (a local/arg spill) means
        # the frame is not a pure ra-save frame -> structural guard aborts.
        out = self._run(
            self._classA(body_extra=("sw\t$2,8($sp)",)),
            noreturn_syms=("func_80404700",),
        )
        self._assert_frame_kept(out)
        self.assertIn("sw\t$2,8($sp)", out)

    def test_callee_not_in_noreturn_set_keeps_frame(self):
        # The tail callee is not declared noreturn -> its link may be live; do
        # not elide (and the jal->j pass is inert too).
        out = self._run(self._classA(), noreturn_syms=("func_80099999",))
        self._assert_frame_kept(out)
        self.assertIn("jal\tfunc_80404700", out)

    def test_empty_noreturn_set_keeps_frame(self):
        out = self._run(self._classA(), noreturn_syms=())
        self._assert_frame_kept(out)
        self.assertIn("jal\tfunc_80404700", out)

    def test_indirect_tail_call_keeps_frame(self):
        # A `jalr $reg` tail call is never elided (indirect target).
        lines = [
            ".ent\tfunc_X",
            ".set\tnoreorder",
            "func_X:",
            ".frame\t$sp,24,$31\t\t# vars= 0, regs= 1/0, args= 16, extra= 0",
            ".mask\t0x80000000,-8",
            ".fmask\t0x00000000,0",
            "subu\t$sp,$sp,24",
            "sw\t$31,16($sp)",
            "lw\t$2,4($4)",
            "jalr\t$2",
            "nop",
            "lw\t$31,16($sp)",
            "addu\t$sp,$sp,24",
            "j\t$31",
            ".end\tfunc_X",
        ]
        out = self._run(lines, noreturn_syms=("func_80404700",))
        self._assert_frame_kept(out)


class TestElideRaOnlyFrameCallerArgs(unittest.TestCase):
    """LEAD 23 extension: elide the $ra-only frame of an ARG-carrying tail
    sibcall, tolerating incoming caller-argument stack loads at N+16, N+20, ...
    and rebasing each by the removed frame size N. Confirmed on town
    func_800CF814, which tail-dispatches the same sibcall member twice with the
    fifth/sixth args loaded from 40($sp)/44($sp) (retail: frameless, 16/20).
    """

    def _run(self, lines, noreturn_syms=(), sibcall_syms=()):
        with tempfile.TemporaryDirectory() as d:
            nf = Path(d) / "noreturn_syms.txt"
            nf.write_text("".join(f"{s}\n" for s in noreturn_syms))
            sf = Path(d) / "sibcall_syms.txt"
            sf.write_text("".join(f"{s}\n" for s in sibcall_syms))
            env = {
                "MASPSX_NORETURN_FILE": str(nf),
                "MASPSX_SIBCALL_FILE": str(sf),
            }
            with mock.patch.dict(os.environ, env):
                mp = MaspsxProcessor(lines, sdata_limit=8)
                return strip_comments(mp.process_lines())

    # ---- positives -------------------------------------------------------

    def test_single_sibcall_one_caller_arg_rebased(self):
        # One caller-arg load (40 = 24 + 16) and a single tail sibcall.
        lines = [
            ".ent\tfunc_T",
            ".set\tnoreorder",
            "func_T:",
            ".frame\t$sp,24,$31\t\t# vars= 0, regs= 1/0, args= 16, extra= 0",
            ".mask\t0x80000000,-8",
            ".fmask\t0x00000000,0",
            "subu\t$sp,$sp,24",
            "sw\t$31,16($sp)",
            "lw\t$5,40($sp)",
            "lw\t$2,4($4)",
            "beq\t$2,$0,$L2",
            "sw\t$0,628($4)",
            "jal\tfunc_SIB",
            "sw\t$2,644($4)",
            "$L2:",
            "lw\t$31,16($sp)",
            "addu\t$sp,$sp,24",
            "j\t$31",
            ".end\tfunc_T",
        ]
        out = self._run(lines, sibcall_syms=("func_SIB",))
        # frame gone
        self.assertNotIn("subu\t$sp,$sp,24", out)
        self.assertNotIn("sw\t$31,16($sp)", out)
        self.assertNotIn("lw\t$31,16($sp)", out)
        self.assertNotIn("addu\t$sp,$sp,24", out)
        # caller-arg rebased 40 -> 16
        self.assertIn("lw\t$5,16($sp)", out)
        self.assertNotIn("lw\t$5,40($sp)", out)
        # tail is a `j`, no surviving jal, terminal return intact
        self.assertIn("j\tfunc_SIB", out)
        self.assertNotIn("jal\tfunc_SIB", out)
        self.assertIn("j\t$31", out)
        # the ONLY residual $sp reference is the rebased caller-arg load
        residual = [l for l in out if "$sp" in l and not l.startswith(".")]
        self.assertEqual(residual, ["lw\t$5,16($sp)"])

    def test_two_sibcalls_two_caller_args_rebased(self):
        # Mirrors town func_800CF814: two tail dispatches to the same sibcall
        # member, two caller-arg loads at 40/44 (N=24) -> 16/20.
        lines = [
            ".ent\tfunc_T2",
            ".set\tnoreorder",
            "func_T2:",
            ".frame\t$sp,24,$31\t\t# vars= 0, regs= 1/0, args= 16, extra= 0",
            ".mask\t0x80000000,-8",
            ".fmask\t0x00000000,0",
            "subu\t$sp,$sp,24",
            "sw\t$31,16($sp)",
            "lw\t$5,40($sp)",
            "lw\t$2,44($sp)",
            "lw\t$3,4($4)",
            "beq\t$3,$0,$L2",
            "nop",
            "j\tfunc_SIB",
            "nop",
            "$L2:",
            "lw\t$6,8($4)",
            "j\tfunc_SIB",
            "sh\t$6,6($4)",
            "lw\t$31,16($sp)",
            "addu\t$sp,$sp,24",
            "j\t$31",
            ".end\tfunc_T2",
        ]
        out = self._run(lines, sibcall_syms=("func_SIB",))
        self.assertNotIn("subu\t$sp,$sp,24", out)
        self.assertNotIn("sw\t$31,16($sp)", out)
        self.assertNotIn("lw\t$31,16($sp)", out)
        self.assertNotIn("addu\t$sp,$sp,24", out)
        self.assertIn("lw\t$5,16($sp)", out)
        self.assertIn("lw\t$2,20($sp)", out)
        self.assertNotIn("lw\t$5,40($sp)", out)
        self.assertNotIn("lw\t$2,44($sp)", out)
        self.assertEqual(out.count("j\tfunc_SIB"), 2)
        self.assertNotIn("jal\tfunc_SIB", out)
        self.assertIn("j\t$31", out)
        residual = sorted(
            l for l in out if "$sp" in l and not l.startswith(".")
        )
        self.assertEqual(residual, ["lw\t$2,20($sp)", "lw\t$5,16($sp)"])

    def test_noreturn_member_with_caller_arg_rebased(self):
        # The caller-arg rebase also applies when the tail target is a
        # (zero-arg-derived) noreturn member reached via a stack-arg load.
        lines = [
            ".ent\tfunc_T3",
            ".set\tnoreorder",
            "func_T3:",
            ".frame\t$sp,24,$31\t\t# vars= 0, regs= 1/0, args= 16, extra= 0",
            ".mask\t0x80000000,-8",
            ".fmask\t0x00000000,0",
            "subu\t$sp,$sp,24",
            "sw\t$31,16($sp)",
            "lw\t$5,40($sp)",
            "lw\t$2,4($4)",
            "beq\t$2,$0,$L2",
            "sw\t$0,628($4)",
            "jal\tfunc_NR",
            "sw\t$2,644($4)",
            "$L2:",
            "lw\t$31,16($sp)",
            "addu\t$sp,$sp,24",
            "j\t$31",
            ".end\tfunc_T3",
        ]
        out = self._run(lines, noreturn_syms=("func_NR",))
        self.assertNotIn("subu\t$sp,$sp,24", out)
        self.assertIn("lw\t$5,16($sp)", out)
        self.assertIn("j\tfunc_NR", out)
        self.assertNotIn("jal\tfunc_NR", out)

    # ---- negatives (frame must be KEPT) ----------------------------------

    def _base_ca(self, extra_body=(), tail="jal\tfunc_SIB", mask="0x80000000,-8",
                 prologue=("subu\t$sp,$sp,24", "sw\t$31,16($sp)"),
                 epilogue=("lw\t$31,16($sp)", "addu\t$sp,$sp,24")):
        lines = [
            ".ent\tfunc_N",
            ".set\tnoreorder",
            "func_N:",
            ".frame\t$sp,24,$31\t\t# vars= 0, regs= 1/0, args= 16, extra= 0",
            f".mask\t{mask}",
            ".fmask\t0x00000000,0",
        ]
        lines += list(prologue)
        lines += ["lw\t$5,40($sp)", "lw\t$2,4($4)", "beq\t$2,$0,$L2", "nop"]
        lines += list(extra_body)
        lines += [tail, "sw\t$2,644($4)", "$L2:"]
        lines += list(epilogue)
        lines += ["j\t$31", ".end\tfunc_N"]
        return lines

    def _assert_frame_kept(self, out):
        self.assertIn("subu\t$sp,$sp,24", out)
        self.assertIn("sw\t$31,16($sp)", out)
        self.assertIn("lw\t$31,16($sp)", out)
        self.assertIn("addu\t$sp,$sp,24", out)
        # the caller-arg load is NOT rebased when the frame is kept
        self.assertIn("lw\t$5,40($sp)", out)
        self.assertNotIn("lw\t$5,16($sp)", out)

    def test_unclassifiable_sp_use_keeps_frame(self):
        # A STORE into the caller-arg region is not a recognised caller-arg load
        # -> unclear -> keep the whole frame.
        out = self._run(
            self._base_ca(extra_body=("sw\t$6,44($sp)",)),
            sibcall_syms=("func_SIB",),
        )
        self._assert_frame_kept(out)

    def test_access_into_removed_frame_keeps_frame(self):
        # A non-$ra load at an offset INSIDE the removed frame [0,N) (a spill,
        # not an incoming arg) must abort the elision.
        out = self._run(
            self._base_ca(extra_body=("lw\t$6,8($sp)",)),
            sibcall_syms=("func_SIB",),
        )
        self._assert_frame_kept(out)
        self.assertIn("lw\t$6,8($sp)", out)

    def test_misaligned_caller_arg_below_window_keeps_frame(self):
        # An $sp load at N+0..N+12 (the caller's a0-a3 home area, below the
        # N+16 stack-arg window) is not an incoming stack argument -> keep.
        out = self._run(
            self._base_ca(extra_body=("lw\t$6,28($sp)",)),  # 28 = 24 + 4
            sibcall_syms=("func_SIB",),
        )
        self._assert_frame_kept(out)
        self.assertIn("lw\t$6,28($sp)", out)

    def test_non_ra_only_frame_keeps_frame(self):
        # A callee-saved GPR ($s0 = bit 16) besides $ra -> the frame is real,
        # even with a caller-arg load present.
        out = self._run(
            self._base_ca(
                mask="0x80010000,-8",
                prologue=("subu\t$sp,$sp,24", "sw\t$31,16($sp)",
                          "sw\t$16,8($sp)"),
                epilogue=("lw\t$31,16($sp)", "lw\t$16,8($sp)",
                          "addu\t$sp,$sp,24"),
            ),
            sibcall_syms=("func_SIB",),
        )
        self._assert_frame_kept(out)
        self.assertIn("sw\t$16,8($sp)", out)

    def test_target_not_in_evidence_keeps_frame(self):
        # The tail callee is in neither the noreturn nor the sibcall set -> its
        # link may be live; do not elide, and the caller-arg stays at 40.
        out = self._run(self._base_ca(), sibcall_syms=("func_OTHER",))
        self._assert_frame_kept(out)
        self.assertIn("jal\tfunc_SIB", out)


class TestReturnDelayBackfill(unittest.TestCase):
    """LEAD 19/23 `maspsx-return-delay-backfill`: after the frame elision vacates
    the `jr $ra` return delay slot, sink a reg-base displacement store that sits
    immediately before the return into that slot -- iff the store's VALUE is not
    produced by the instruction immediately preceding it (the retail fill/keep
    discriminator that the 2026-07-10 naive LEAD-23b fill lacked).
    """

    def _run(self, lines, noreturn_syms=(), sibcall_syms=()):
        with tempfile.TemporaryDirectory() as d:
            nf = Path(d) / "noreturn_syms.txt"
            nf.write_text("".join(f"{s}\n" for s in noreturn_syms))
            sf = Path(d) / "sibcall_syms.txt"
            sf.write_text("".join(f"{s}\n" for s in sibcall_syms))
            env = {
                "MASPSX_NORETURN_FILE": str(nf),
                "MASPSX_SIBCALL_FILE": str(sf),
            }
            with mock.patch.dict(os.environ, env):
                mp = MaspsxProcessor(lines, sdata_limit=8)
                return strip_comments(mp.process_lines())

    def _shape(self, tail_body, ret="jr\t$31", dealloc_in_delay=True):
        """An elidable ra-only-frame noreturn-tail function whose $L2 return arm
        ends with `tail_body` + a return. Two epilogue arrangements, both of which
        leave a nop in the return delay slot after elision:
          * dealloc_in_delay=True:  `lw $31; jr $31; addu $sp` -- the dealloc IS
            the return delay slot, elision nops it (the marker case).
          * dealloc_in_delay=False: `lw $31; addu $sp; jr $31; nop` -- gcc put the
            dealloc before the return and left a GENUINE nop delay (the real
            func_8008C1D4 shape at 2.7.2).
        `tail_body` is the last few real instructions before the ra-restore."""
        lines = [
            ".ent\tfunc_RB",
            ".set\tnoreorder",
            "func_RB:",
            ".frame\t$sp,24,$31\t\t# vars= 0, regs= 1/0, args= 16, extra= 0",
            ".mask\t0x80000000,-8",
            ".fmask\t0x00000000,0",
            "subu\t$sp,$sp,24",
            "sw\t$31,16($sp)",
            "lw\t$2,4($4)",
            "beq\t$2,$0,$L2",
            "sw\t$0,628($4)",
            "jal\tfunc_NR",
            "sw\t$2,644($4)",
            "$L2:",
            "sb\t$0,155($4)",  # branch target is this filler, NOT the store
        ]
        lines += list(tail_body)
        lines += ["lw\t$31,16($sp)"]
        if dealloc_in_delay:
            lines += [ret, "addu\t$sp,$sp,24", ".end\tfunc_RB"]
        else:
            lines += ["addu\t$sp,$sp,24", ret, "nop", ".end\tfunc_RB"]
        return lines

    def _tail_index(self, out, needle):
        return [i for i, l in enumerate(out) if l == needle]

    # ---- positives (store sunk into the return delay slot) ---------------

    def test_zero_store_fills(self):
        # value $zero: nothing defines it -> always FILL (func_8008C1D4 shape).
        out = self._run(
            self._shape(("sw\t$0,140($4)",)), noreturn_syms=("func_NR",))
        # exactly one store, and it now sits AFTER the return
        stores = self._tail_index(out, "sw\t$0,140($4)")
        rets = self._tail_index(out, "jr\t$31")
        self.assertEqual(len(stores), 1)
        self.assertEqual(len(rets), 1)
        self.assertGreater(stores[0], rets[0])
        # the vacated slot no longer carries a trailing nop after the return
        self.assertNotEqual(out[-1] if out else "", "nop")

    def test_zero_store_fills_genuine_nop_delay(self):
        # The real func_8008C1D4 shape: gcc emits the dealloc before the return
        # and a GENUINE nop in the `j $31` delay slot. Elision still leaves a nop
        # there; the backfill sinks the $zero store into it.
        out = self._run(
            self._shape(("sw\t$0,140($4)",), dealloc_in_delay=False),
            noreturn_syms=("func_NR",),
        )
        stores = self._tail_index(out, "sw\t$0,140($4)")
        rets = self._tail_index(out, "jr\t$31")
        self.assertEqual(len(stores), 1)
        self.assertEqual(len(rets), 1)
        self.assertGreater(stores[0], rets[0])

    def test_reg_value_defined_earlier_fills(self):
        # value $6 defined two insns before the store (not back-to-back) -> FILL
        # (func_800403EC / func_800B79CC shape).
        out = self._run(
            self._shape((
                "lw\t$6,8($4)",
                "sb\t$2,155($4)",
                "sw\t$6,140($4)",
            )),
            noreturn_syms=("func_NR",),
        )
        stores = self._tail_index(out, "sw\t$6,140($4)")
        rets = self._tail_index(out, "jr\t$31")
        self.assertEqual(len(stores), 1)
        self.assertGreater(stores[0], rets[0])

    # ---- negatives (nop KEPT) --------------------------------------------

    def test_value_defined_immediately_before_keeps_nop(self):
        # value $6 defined by the IMMEDIATELY-preceding addiu -> retail keeps the
        # nop (func_800CF814: `addiu v0,v0,1; sh v0,104(a0); jr ra; nop`).
        out = self._run(
            self._shape((
                "lw\t$6,8($4)",
                "addiu\t$6,$6,1",
                "sw\t$6,140($4)",
            )),
            noreturn_syms=("func_NR",),
        )
        stores = self._tail_index(out, "sw\t$6,140($4)")
        rets = self._tail_index(out, "jr\t$31")
        self.assertEqual(len(stores), 1)
        # store STAYS before the return; a nop still fills the delay slot
        self.assertLess(stores[0], rets[0])
        self.assertIn("nop", out[rets[0] + 1:])

    def test_value_from_load_across_delay_nop_keeps_nop(self):
        # func_800A1600 / func_8195A2C4 shape: the store's value is freshly
        # loaded, separated from the store only by a MIPS load-delay nop
        # (`lw $6,8($4); nop; sw $6,140($4)`) -> retail KEEPS the nop. The
        # discriminator must look PAST the load-delay nop to the producing load.
        out = self._run(
            self._shape((
                "lw\t$6,8($4)",
                "nop",
                "sw\t$6,140($4)",
            )),
            noreturn_syms=("func_NR",),
        )
        stores = self._tail_index(out, "sw\t$6,140($4)")
        rets = self._tail_index(out, "jr\t$31")
        self.assertEqual(len(stores), 1)
        self.assertLess(stores[0], rets[0])  # store STAYS before the return

    def test_branch_target_store_keeps_nop(self):
        # func_800B4C60 shape: the store is itself a branch target (a live label
        # sits on it) -> retail KEEPS the nop even for a $zero store.
        lines = [
            ".ent\tfunc_BT",
            ".set\tnoreorder",
            "func_BT:",
            ".frame\t$sp,24,$31\t\t# vars= 0, regs= 1/0, args= 16, extra= 0",
            ".mask\t0x80000000,-8",
            ".fmask\t0x00000000,0",
            "subu\t$sp,$sp,24",
            "sw\t$31,16($sp)",
            "lw\t$2,4($4)",
            "beqz\t$2,$L7",     # LIVE branch to the store
            "sw\t$0,628($4)",
            "jal\tfunc_NR",
            "sw\t$2,644($4)",
            "$L7:",             # live label ON the store
            "sw\t$0,140($4)",   # branch-target store
            "lw\t$31,16($sp)",
            "jr\t$31",
            "addu\t$sp,$sp,24",
            ".end\tfunc_BT",
        ]
        out = self._run(lines, noreturn_syms=("func_NR",))
        stores = self._tail_index(out, "sw\t$0,140($4)")
        rets = self._tail_index(out, "jr\t$31")
        self.assertEqual(len(stores), 1)
        self.assertLess(stores[0], rets[0])  # store STAYS before the return

    def test_live_label_on_return_keeps_nop(self):
        # a LIVE label on the return (a real branch targets it) means a path can
        # reach `jr $31` while skipping the store -> must NOT sink it.
        lines = [
            ".ent\tfunc_LR",
            ".set\tnoreorder",
            "func_LR:",
            ".frame\t$sp,24,$31\t\t# vars= 0, regs= 1/0, args= 16, extra= 0",
            ".mask\t0x80000000,-8",
            ".fmask\t0x00000000,0",
            "subu\t$sp,$sp,24",
            "sw\t$31,16($sp)",
            "lw\t$2,4($4)",
            "beq\t$2,$0,$L2",
            "sw\t$0,628($4)",
            "jal\tfunc_NR",
            "sw\t$2,644($4)",
            "$L2:",
            "bne\t$2,$3,$L9",   # LIVE branch to the return label (skips store)
            "nop",
            "sw\t$0,140($4)",   # store
            "$L9:",             # live label on the return
            "lw\t$31,16($sp)",
            "jr\t$31",
            "addu\t$sp,$sp,24",
            ".end\tfunc_LR",
        ]
        out = self._run(lines, noreturn_syms=("func_NR",))
        stores = self._tail_index(out, "sw\t$0,140($4)")
        rets = self._tail_index(out, "jr\t$31")
        self.assertEqual(len(stores), 1)
        self.assertLess(stores[0], rets[0])  # store STAYS before the return

    def test_dead_label_between_store_and_return_still_fills(self):
        # A DEAD label between the store and the return (e.g. the epilogue label
        # LEAD 22 orphaned when it deleted `j $Llabel`) emits no bytes and must
        # NOT block the rotation -- this is the real func_8008C1D4 shape.
        lines = [
            ".ent\tfunc_DL",
            ".set\tnoreorder",
            "func_DL:",
            ".frame\t$sp,24,$31\t\t# vars= 0, regs= 1/0, args= 16, extra= 0",
            ".mask\t0x80000000,-8",
            ".fmask\t0x00000000,0",
            "subu\t$sp,$sp,24",
            "sw\t$31,16($sp)",
            "lw\t$2,4($4)",
            "beq\t$2,$0,$L2",
            "sw\t$0,628($4)",
            "jal\tfunc_NR",
            "sw\t$2,644($4)",
            "$L2:",
            "sb\t$0,155($4)",
            "sw\t$0,140($4)",   # store
            "$L7:",             # DEAD label (nothing branches to $L7)
            "lw\t$31,16($sp)",
            "jr\t$31",
            "addu\t$sp,$sp,24",
            ".end\tfunc_DL",
        ]
        out = self._run(lines, noreturn_syms=("func_NR",))
        stores = self._tail_index(out, "sw\t$0,140($4)")
        rets = self._tail_index(out, "jr\t$31")
        self.assertEqual(len(stores), 1)
        self.assertGreater(stores[0], rets[0])  # store sunk into the delay slot

    def test_frame_kept_means_no_backfill(self):
        # if the frame is NOT elided (callee not a member), there is no vacated
        # slot and the store is untouched.
        out = self._run(
            self._shape(("sw\t$0,140($4)",)), noreturn_syms=("func_OTHER",))
        self.assertIn("subu\t$sp,$sp,24", out)  # frame kept
        stores = self._tail_index(out, "sw\t$0,140($4)")
        rets = self._tail_index(out, "jr\t$31")
        self.assertEqual(len(stores), 1)
        self.assertLess(stores[0], rets[0])


if __name__ == "__main__":
    unittest.main()
