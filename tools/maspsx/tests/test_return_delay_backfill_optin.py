"""LEAD 34 -- the FILL/KEEP discriminator of the return-delay backfill.

`_backfill_return_delay_store` (LEAD 19/23) declines whenever the store's VALUE
register is written by the instruction immediately before the store (guard (a)),
because retail KEEPS the nop on the read-modify-write and load-copy tails that
guard was derived from.  Two matched rows FILL with a tail that guard (a) also
declines; the separator is one instruction further back and is decided by
`_producer_in_load_shadow`: the producer of the stored value is itself stalled
in the load-delay shadow of the load feeding it

    <load> Rx,off(Rb) ; nop ; <alu> val,Rx,.. ; <store> val,off2(Rb2)

so the whole tail is ONE dependent chain with an idle hazard slot.  Where that
hazard slot carries independent work (or there is no ALU producer at all,
because the value comes straight out of the load), guard (a) still declines.

These tests pin all four cases and, critically, that the decision is taken on
LOCAL SHAPE ONLY -- the pass consults no function name (the per-function waiver
set this module used to test was deleted on 2026-09-06; receipts in
work/bridge_wave_20260906/maspsx_general_return_delay/REPORT.md).
"""

import os
import tempfile
import unittest
from pathlib import Path
from unittest import mock

from maspsx import MaspsxProcessor

from .util import strip_comments


class TestReturnDelayBackfillShadow(unittest.TestCase):
    def _run(self, lines, noreturn_syms=("func_NR",), sibcall_syms=(),
             fill_shadowed=True):
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
                mp = MaspsxProcessor(
                    lines, sdata_limit=8,
                    fill_shadowed_return_delay=fill_shadowed)
                return strip_comments(mp.process_lines())

    def _shape(self, name, tail_body, label_before_store=False):
        """An elidable ra-only-frame noreturn-tail function named `name` whose
        return arm ends with `tail_body` then the epilogue + `jr $31`."""
        lines = [
            f".ent\t{name}",
            ".set\tnoreorder",
            f"{name}:",
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
        ]
        body = list(tail_body)
        if label_before_store:
            # A LIVE label defined ON the store: a branch can reach the store
            # directly, so guard (b) must abort the rotation.
            lines += ["beq\t$2,$0,$L9"]
            body = body[:-1] + ["$L9:", body[-1]]
        lines += body
        lines += [
            "lw\t$31,16($sp)",
            "jr\t$31",
            "addu\t$sp,$sp,24",
            f".end\t{name}",
        ]
        return lines

    # The retail FILL residue: producer stalled in the load's hazard shadow.
    SHADOWED_TAIL = ("lhu\t$2,20($8)", "nop", "andi\t$2,$2,0xbfff",
                     "sh\t$2,20($8)")
    # The retail KEEP residue: same read-modify-write of the SAME address, but
    # the load's hazard slot carries independent work.
    BUSY_TAIL = ("lhu\t$2,20($8)", "sh\t$0,22($8)", "addu\t$2,$2,1",
                 "sh\t$2,20($8)")
    # The retail KEEP residue: no ALU producer at all, the value is the load.
    COPY_TAIL = ("lhu\t$2,20($3)", "nop", "sh\t$2,20($8)")
    STORE = "sh\t$2,20($8)"
    NAME = "func_RB"

    def _positions(self, out, needle):
        return [i for i, l in enumerate(out) if l == needle]

    def _assert_filled(self, out):
        stores = self._positions(out, self.STORE)
        rets = self._positions(out, "jr\t$31")
        self.assertEqual(len(stores), 1)
        self.assertEqual(len(rets), 1)
        self.assertGreater(stores[0], rets[0], f"store not sunk: {out}")

    def _assert_kept(self, out):
        stores = self._positions(out, self.STORE)
        rets = self._positions(out, "jr\t$31")
        self.assertEqual(len(stores), 1)
        self.assertEqual(len(rets), 1)
        self.assertLess(stores[0], rets[0], f"store wrongly sunk: {out}")
        self.assertIn("nop", out[rets[0] + 1:])

    # ---- the discriminator ------------------------------------------------

    def test_shadowed_producer_fills_under_the_switch(self):
        out = self._run(self._shape(self.NAME, self.SHADOWED_TAIL))
        self._assert_filled(out)

    def test_shadowed_producer_keeps_by_default(self):
        # The switch is OFF unless a build asks for it: the same shape KEEPS in
        # another container, so guard (a) stays in charge by default.
        out = self._run(self._shape(self.NAME, self.SHADOWED_TAIL),
                        fill_shadowed=False)
        self._assert_kept(out)

    def test_busy_hazard_slot_keeps_nop(self):
        # Same RMW of the same address, same "value written by the previous
        # instruction" -- but the load's delay slot is not idle.
        out = self._run(self._shape(self.NAME, self.BUSY_TAIL))
        self._assert_kept(out)

    def test_load_copy_keeps_nop(self):
        # The producer IS the load, so there is no shadowed ALU; guard (a)
        # still declines.
        out = self._run(self._shape(self.NAME, self.COPY_TAIL))
        self._assert_kept(out)

    def test_value_not_fresh_still_fills(self):
        # The sites guard (a) always allowed are unchanged.
        out = self._run(self._shape(self.NAME, (
            "lw\t$2,8($4)",
            "sb\t$3,155($4)",
            self.STORE,
        )))
        self._assert_filled(out)

    def test_shadow_requires_the_load_to_feed_the_producer(self):
        # An idle nop before the producer is not enough: the instruction before
        # it must be the LOAD whose result the producer consumes.
        out = self._run(self._shape(self.NAME, (
            "sb\t$0,154($4)",
            "nop",
            "andi\t$2,$2,0xbfff",
            self.STORE,
        )))
        self._assert_kept(out)

    def test_shadow_requires_the_producer_to_read_the_loaded_register(self):
        # The load must be the reason for the nop: a load into an unrelated
        # register leaves guard (a) in charge.
        out = self._run(self._shape(self.NAME, (
            "lhu\t$5,20($8)",
            "nop",
            "andi\t$2,$7,0xbfff",
            self.STORE,
        )))
        self._assert_kept(out)

    # ---- the decision is name-blind --------------------------------------

    def test_decision_does_not_depend_on_the_ent_symbol(self):
        for name in ("func_RB", "func_8195AE0C", "func_deadbeef", "main"):
            with self.subTest(name=name):
                self._assert_filled(
                    self._run(self._shape(name, self.SHADOWED_TAIL)))
                self._assert_kept(
                    self._run(self._shape(name, self.BUSY_TAIL)))

    # ---- CORRECTNESS guards are NOT waived -------------------------------

    def test_declines_when_store_is_a_live_branch_target(self):
        out = self._run(
            self._shape(self.NAME, self.SHADOWED_TAIL, label_before_store=True))
        self._assert_kept(out)

    def test_declines_on_sp_based_store(self):
        out = self._run(self._shape(self.NAME, (
            "lhu\t$2,20($8)",
            "nop",
            "andi\t$2,$2,0xbfff",
            "sh\t$2,20($sp)",
        )))
        self.assertIn("sh\t$2,20($sp)", out)
        rets = self._positions(out, "jr\t$31")
        self.assertEqual(len(rets), 1)
        self.assertLess(out.index("sh\t$2,20($sp)"), rets[0])

    def test_declines_when_predecessor_is_not_a_store(self):
        out = self._run(self._shape(self.NAME, (
            "lhu\t$2,20($8)",
            "nop",
            "andi\t$2,$2,0xbfff",
        )))
        self.assertNotIn(self.STORE, out)
        rets = self._positions(out, "jr\t$31")
        self.assertEqual(len(rets), 1)
        self.assertIn("nop", out[rets[0] + 1:])


if __name__ == "__main__":
    unittest.main()
