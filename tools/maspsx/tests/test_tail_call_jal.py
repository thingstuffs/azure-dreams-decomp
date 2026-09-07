import os
import tempfile
import unittest
from pathlib import Path
from unittest import mock

from maspsx import MaspsxProcessor

from .util import strip_comments


class TestTailCallJalToJ(unittest.TestCase):
    """LEAD 18-GENERAL: retail/ASPSX emits a bare ``j TARGET`` (no $ra write) for
    a final non-returning tail-call into a ZERO-ARG (void) ``noreturn`` callee,
    where gcc + GNU as emit ``jal TARGET``.

    The firing condition is DERIVED from a source-declared side-channel: a
    ``jal SYM`` is rewritten to ``j`` when SYM is in the auto-generated zero-arg
    noreturn set (``config/noreturn_syms.txt``, produced by
    ``tools/gen_noreturn_syms.py``) and its $ra link is provably dead. These
    tests drive that path via a temp ``$MASPSX_NORETURN_FILE`` fixture so they do
    not depend on the tracked config. The legacy by-name set is deprecated and
    empty. Corpus proof: build/tmp_infra/tailcall_discriminator_report.md (66/66).
    """

    def _run(self, lines, noreturn_syms=(), sdata_limit=8,
             noreturn_epilogue_syms=()):
        # Point maspsx at a temp side-channel file holding exactly the given set,
        # then process. The set is loaded in MaspsxProcessor.__init__, so both the
        # construction and process_lines happen while the env var is in place.
        with tempfile.TemporaryDirectory() as d:
            f = Path(d) / "noreturn_syms.txt"
            f.write_text("".join(f"{s}\n" for s in noreturn_syms))
            with mock.patch.dict(os.environ, {"MASPSX_NORETURN_FILE": str(f)}):
                mp = MaspsxProcessor(
                    lines,
                    sdata_limit=sdata_limit,
                    noreturn_epilogue_syms=noreturn_epilogue_syms,
                )
                return strip_comments(mp.process_lines())

    def _two_call_body(self, name, callee="func_8002643C"):
        # Mirrors func_80013410: a dead-link tail-call `jal callee` (followed by
        # another call, not by the return epilogue, delay slot = a reordered
        # store) and an ordinary last-call-before-return `jal func_800263C0`.
        return [
            f".ent\t{name}",
            "subu\t$sp,$sp,24",
            "sw\t$31,16($sp)",
            "lw\t$2,56($4)",
            "beq\t$2,$0,$L2",
            "lui\t$2,%hi(D_800265B8)",
            "addiu\t$2,$2,%lo(D_800265B8)",
            f"jal\t{callee}",
            "sw\t$2,-16($4)",
            "$L2:",
            "jal\tfunc_800263C0",
            "lw\t$31,16($sp)",
            "j\t$31",
            "addu\t$sp,$sp,24",
            f".end\t{name}",
        ]

    def test_zero_arg_noreturn_callee_is_rewritten(self):
        # Callee in the (zero-arg) noreturn set + dead link -> rewritten to `j`.
        out = self._run(
            self._two_call_body("func_80013410"),
            noreturn_syms=("func_8002643C",),
        )
        self.assertIn("j\tfunc_8002643C", out)
        self.assertNotIn("jal\tfunc_8002643C", out)
        # the ordinary last-call-before-return (not in the set) keeps its `jal`
        self.assertIn("jal\tfunc_800263C0", out)
        # the tail-call's delay-slot store is left untouched
        self.assertIn("sw\t$2,-16($4)", out)

    def test_arg_reg_in_delay_slot_is_not_rewritten(self):
        # Belt-and-braces guard: even with the callee in the noreturn set and a
        # dead link, a delay slot that writes an argument register ($a0-$a3)
        # blocks the rewrite (a zero-arg callee never sets up args in its slot;
        # this shape means the side-channel file is stale/wrong for the site).
        # Mirrors the real gcc-2.7.2 emission of func_80019A10's calls to the
        # arg-taking noreturn func_8007BEF0(s32): the `.set noreorder/.set nomacro`
        # wrapping is what parks the argument `li $4,1` in the delay slot, so
        # maspsx preserves it there (build/tmp_infra/f80019A10_272.s lines 66-71).
        lines = [
            ".ent\tfunc_80019A10",
            "subu\t$sp,$sp,24",
            "sw\t$31,16($sp)",
            "lw\t$2,56($4)",
            ".set\tnoreorder",
            "beq\t$2,$0,$L2",
            "nop",
            ".set\treorder",
            ".set\tnoreorder",
            ".set\tnomacro",
            "jal\tfunc_8007BEF0",  # candidate: in set below, dead link
            "li\t$4,0x00000001",    # delay slot = ARG ($a0) -> guard blocks
            ".set\tmacro",
            ".set\treorder",
            "$L2:",
            ".set\tnoreorder",
            ".set\tnomacro",
            "jal\tfunc_800263C0",   # later $ra write -> link above is dead
            "nop",
            ".set\tmacro",
            ".set\treorder",
            "lw\t$31,16($sp)",
            "j\t$31",
            "addu\t$sp,$sp,24",
            ".end\tfunc_80019A10",
        ]
        out = self._run(lines, noreturn_syms=("func_8007BEF0",))
        self.assertIn("jal\tfunc_8007BEF0", out)
        self.assertNotIn("j\tfunc_8007BEF0", out)
        # sanity: the arg load in the delay slot is untouched
        self.assertIn("li\t$4,0x00000001", out)

    def test_wrapped_store_delay_slot_is_rewritten(self):
        # A/B control for the arg-reg guard: the SAME `.set noreorder/.set nomacro`
        # wrapping, but a non-arg (store) delay slot, still converts. Mirrors the
        # real gate-b func_80013410 @2.8.1-G0 shape (jal func_8002643C then a
        # reordered `sw $2,-16($4)`). Proves the wrapping itself does not block;
        # only the arg-register delay slot does.
        lines = [
            ".ent\tfunc_80013410",
            "subu\t$sp,$sp,24",
            "sw\t$31,16($sp)",
            "lw\t$2,56($4)",
            ".set\tnoreorder",
            "beq\t$2,$0,$L2",
            "nop",
            ".set\treorder",
            ".set\tnoreorder",
            ".set\tnomacro",
            "jal\tfunc_8002643C",
            "sw\t$2,-16($4)",
            ".set\tmacro",
            ".set\treorder",
            "$L2:",
            ".set\tnoreorder",
            ".set\tnomacro",
            "jal\tfunc_800263C0",
            "nop",
            ".set\tmacro",
            ".set\treorder",
            "lw\t$31,16($sp)",
            "j\t$31",
            "addu\t$sp,$sp,24",
            ".end\tfunc_80013410",
        ]
        out = self._run(lines, noreturn_syms=("func_8002643C",))
        self.assertIn("j\tfunc_8002643C", out)
        self.assertNotIn("jal\tfunc_8002643C", out)
        self.assertIn("sw\t$2,-16($4)", out)

    def test_live_ra_link_after_jal_is_not_rewritten(self):
        # A noreturn-set callee whose return link is READ after the call (here
        # `sw $31` spills $ra) is left as `jal`: a live link means a real return
        # depends on it, so it is not a non-returning tail-call. Delay slot is a
        # nop, so the arg-reg guard is not the reason it is skipped.
        lines = [
            ".ent\tfunc_80013410",
            "subu\t$sp,$sp,24",
            "sw\t$31,16($sp)",
            ".set\tnoreorder",
            "jal\tfunc_8002643C",
            "nop",
            "sw\t$31,0($4)",
            "lw\t$31,16($sp)",
            "j\t$31",
            "addu\t$sp,$sp,24",
            ".set\treorder",
            ".end\tfunc_80013410",
        ]
        out = self._run(lines, noreturn_syms=("func_8002643C",))
        self.assertIn("jal\tfunc_8002643C", out)
        self.assertNotIn("j\tfunc_8002643C", out)

    def test_last_call_before_return_epilogue(self):
        # A `jal` immediately before the return epilogue (`lw $31,N($sp)` ...
        # `j/jr $31`). 2026-09-06: the shape guard that used to keep the `jal`
        # here is scoped to callees the CENSUS does not carry -- for a census
        # noreturn callee that epilogue is unreachable code and retail emits
        # `j` (measured on a matched dungeon row; receipts:
        # work/bridge_wave_20260906/maspsx_general_return_delay/REPORT.md).
        # Note `ra_link_dead` carries no information at this position: the
        # `lw $31,N($sp)` restore trivially kills the link either way.
        lines = [
            ".ent\tfunc_80013410",
            "subu\t$sp,$sp,24",
            "sw\t$31,16($sp)",
            "jal\tfunc_8002643C",
            "lw\t$31,16($sp)",
            "j\t$31",
            "addu\t$sp,$sp,24",
            ".end\tfunc_80013410",
        ]
        # A) not a census member -> untouched.
        out = self._run(lines, noreturn_syms=())
        self.assertIn("jal\tfunc_8002643C", out)
        self.assertNotIn("j\tfunc_8002643C", out)
        # B) census member -> converted.
        out = self._run(lines, noreturn_syms=("func_8002643C",))
        self.assertIn("j\tfunc_8002643C", out)
        self.assertNotIn("jal\tfunc_8002643C", out)

    def test_evidence_named_noreturn_epilogue_is_rewritten(self):
        # TOWN func_8094D708 calls a source-declared noreturn target through an
        # asm-name alias. Retail keeps the ordinary epilogue in the other branch
        # but uses a bare j at this site. The per-TU evidence names that callee;
        # unlisted immediate-epilogue sites retain the conservative default.
        lines = [
            ".ent\tfunc_8094D708",
            "subu\t$sp,$sp,32",
            "sw\t$31,24($sp)",
            "jal\tfunc_8001672C",
            "addu\t$16,$16,1",
            "lw\t$31,24($sp)",
            "j\t$31",
            "addu\t$sp,$sp,32",
            ".end\tfunc_8094D708",
        ]
        out = self._run(
            lines,
            noreturn_syms=("func_8001672C",),
            noreturn_epilogue_syms=("func_8001672C",),
        )
        self.assertIn("j\tfunc_8001672C", out)
        self.assertNotIn("jal\tfunc_8001672C", out)
        self.assertIn("addu\t$16,$16,1", out)

    def test_multi_site_all_qualifying_are_rewritten(self):
        # Mirrors func_80011A50: two dead-link tail-calls into the same zero-arg
        # noreturn callee (each delay slot a reordered store) both convert; the
        # ordinary last-call-before-return keeps its `jal`.
        lines = [
            ".ent\tfunc_80011A50",
            "subu\t$sp,$sp,24",
            "sw\t$31,16($sp)",
            "lw\t$2,128($4)",
            "beq\t$2,$0,$L2",
            "nop",
            "jal\tfunc_80024ABC",  # site 1
            "sw\t$3,-16($4)",
            "$L2:",
            "lw\t$2,132($4)",
            "beq\t$2,$0,$L3",
            "nop",
            "jal\tfunc_80024ABC",  # site 2
            "sw\t$3,-20($4)",
            "$L3:",
            "jal\tfunc_800263C0",  # ordinary last call -> keep jal
            "lw\t$31,16($sp)",
            "j\t$31",
            "addu\t$sp,$sp,24",
            ".end\tfunc_80011A50",
        ]
        out = self._run(lines, noreturn_syms=("func_80024ABC",))
        self.assertEqual(out.count("j\tfunc_80024ABC"), 2)
        self.assertNotIn("jal\tfunc_80024ABC", out)
        self.assertIn("jal\tfunc_800263C0", out)

    def test_fallthrough_after_delay_slot_is_not_rewritten(self):
        # LEAD 18 PER-TU fix (work/queues/maspsx_lead_18_per_tu.md). The noreturn
        # census is a per-FAMILY, union-only set, but `noreturn` is a PER-TU
        # property: func_80171574 entered config/noreturn_syms.dungeon.txt from
        # func_809C9B9C.c alone and then converted func_80BEB814's ORDINARY
        # returning call to the same symbol, leaving it exactly one word off
        # (same mechanism broke func_818124A8/func_818127A8 via func_80025598).
        #
        # This is the exact func_80BEB814 @2.8.1-G0 shape: the census member is
        # called, its delay slot holds a reordered store, and then STRAIGHT-LINE
        # CODE FALLS THROOUGH into a second call in the SAME basic block. gcc only
        # lays down reachable fall-through after a call it believes RETURNS, so
        # this TU does not treat the callee as noreturn -> keep the `jal`. The
        # genuinely-noreturn second call (block-terminal, `$L14:` follows) still
        # converts.
        lines = [
            ".ent\tfunc_80BEB814",
            "subu\t$sp,$sp,24",
            "sw\t$31,16($sp)",
            "lw\t$2,56($4)",
            ".set\tnoreorder",
            "beq\t$2,$0,$L14",
            "nop",
            ".set\treorder",
            "li\t$2,14",
            ".set\tnoreorder",
            ".set\tnomacro",
            "jal\tfunc_80171574",   # census member, but FALL-THROUGH follows
            "sb\t$2,154($16)",
            ".set\tmacro",
            ".set\treorder",
            "jal\tfunc_80171554",   # block-terminal ($L14 follows) -> converts
            "$L14:",
            "lbu\t$2,37($18)",
            "lw\t$31,16($sp)",
            "j\t$31",
            "addu\t$sp,$sp,24",
            ".end\tfunc_80BEB814",
        ]
        out = self._run(
            lines, noreturn_syms=("func_80171574", "func_80171554"))
        self.assertIn("jal\tfunc_80171574", out)
        self.assertNotIn("j\tfunc_80171574", out)
        self.assertIn("j\tfunc_80171554", out)
        self.assertNotIn("jal\tfunc_80171554", out)

    def test_target_not_in_set_is_not_rewritten(self):
        # Callee NOT in the noreturn set: no rewrite (non-empty set, unlisted).
        out = self._run(
            self._two_call_body("func_80013410"),
            noreturn_syms=("func_80099999",),
        )
        self.assertIn("jal\tfunc_8002643C", out)
        self.assertIn("jal\tfunc_800263C0", out)
        self.assertNotIn("j\tfunc_8002643C", out)

    def test_empty_set_no_ops(self):
        # Empty side-channel -> nothing is rewritten anywhere.
        out = self._run(self._two_call_body("func_80013410"), noreturn_syms=())
        self.assertIn("jal\tfunc_8002643C", out)
        self.assertIn("jal\tfunc_800263C0", out)
        self.assertNotIn("j\tfunc_8002643C", out)


if __name__ == "__main__":
    unittest.main()
