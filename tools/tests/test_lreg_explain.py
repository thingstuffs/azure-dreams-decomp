"""lreg_explain.py (local-alloc replay from the `.lreg` dump).  Pure functions on a synthetic dump: no compile, no
scorer, `kitlib.bootstrap` is never called.  The tree-wide check (every local pseudo of every row reproduced
against `;; Register N in R.`) is r81_opus_lregexplain/tmp/fidelity_batch.py."""
import sys
import unittest
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
KIT = ROOT / "tools/lanes/lanekit"
for sub in (ROOT / "tools/lanes", ROOT / "tools/xform", ROOT / "tools", KIT):   # KIT ends up first
    sys.path.insert(0, str(sub))
# a lane patch copy (patch_src/tools/tests next to patch_src/tools/lanes/lanekit): test that copy; inert in the repo
if (Path(__file__).resolve().parents[1] / "lanes/lanekit/lreg_explain.py").is_file():
    sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "lanes/lanekit"))

import lreg_explain as LX                                                 # noqa: E402

# One block, eight objects (a code label counts as an insn number; notes do not):
#   #1 uid 10  80 <- $a0            copy suggestion $a0 for 80's qty; $a0 dies here (REG_DEAD)
#   #2 uid 11  81 <- 80 + 1         81 TIED into 80's qty (80 dies here, 81 not yet born)
#   #3 lbl 12
#   #4 uid 13  clobber 82           birth at 2*4-1 = 7
#   #5 uid 14  82 <- 5              (82 already has its qty); global 90 dies here
#   #6 uid 15  mem[81] <- 82        81 and 82 die: death 12
#   #7 uid 16  83 <- $v1            copy suggestion $v1 (it dies here); 83 unused: REG_UNUSED death 2*7+1 = 15
#   note 17 (not counted)
DUMP = """;; Function f

Register 80 used 2 times across 2 insns in block 0; GR_REGS or none.

Register 81 used 2 times across 9 insns in block 0; GR_REGS or none.

Register 82 used 3 times across 5 insns in block 0; GR_REGS or none.

Register 83 used 1 times across 1 insns in block 0; GR_REGS or none.

Register 90 used 3 times across 9 insns; GR_REGS or none.

1 basic blocks.

Basic block 0: first insn 10, last 16.

Registers live at start: 3 4 29 30 90

;; Register 80 in 4.
;; Register 81 in 4.
;; Register 82 in 2.
;; Register 83 in 3.
(note/i 9 0 10 "" NOTE_INSN_DELETED)

(insn 10 9 11 (set (reg:SI 80)
        (reg:SI 4 a0)) 168 {movsi_internal2} (nil)
    (expr_list:REG_DEAD (reg:SI 4 a0)
        (nil)))

(insn 11 10 12 (set (reg:SI 81)
        (plus:SI (reg:SI 80)
            (const_int 1))) 3 {addsi3_internal} (nil)
    (expr_list:REG_DEAD (reg:SI 80)
        (nil)))

(code_label 12 11 13 5 "")

(insn 13 12 14 (clobber (reg:SI 82)) -1 (nil)
    (nil))

(insn 14 13 15 (set (reg:SI 82)
        (const_int 5)) 168 {movsi_internal2} (nil)
    (expr_list:REG_DEAD (reg:SI 90)
        (nil)))

(insn 15 14 16 (set (mem:SI (reg:SI 81))
        (reg:SI 82)) 168 {movsi_internal2} (nil)
    (expr_list:REG_DEAD (reg:SI 81)
        (expr_list:REG_DEAD (reg:SI 82)
            (nil))))

(insn 16 15 17 (set (reg:SI 83)
        (reg:SI 3 v1)) 168 {movsi_internal2} (nil)
    (expr_list:REG_DEAD (reg:SI 3 v1)
        (expr_list:REG_UNUSED (reg:SI 83)
            (nil))))

(note 17 16 0 "" NOTE_INSN_DELETED)
"""


def function():
    return LX.Function(DUMP, 76, "2.7.2-cdk")


class Formula(unittest.TestCase):
    def test_qty_cmp_pri_verbatim(self):
        self.assertEqual(LX.qty_pri(2, 4, 1), 5000)          # 80097F94 lit0: qty 107, 2 refs over 8..12
        self.assertEqual(LX.qty_pri(6, 6, 1), 20000)         # its rival 112+110+111
        self.assertEqual(LX.qty_pri(4, 2, 1), 40000)
        self.assertEqual(LX.qty_pri(1, 7, 1), 0)             # floor_log2(1) = 0
        self.assertEqual(LX.qty_pri(3, 5, 1), 6000)
        self.assertEqual(LX.floor_log2(0), -1)               # floor_log2_wide(0)

    def test_small_sort_compares_qty_numbers_not_positions(self):
        pri = [1, 3, 2]                                      # higher is better; sorted would be [1, 2, 0]
        cmp = lambda a, b: pri[b] - pri[a]                   # qty_compare
        self.assertEqual(LX.small_sort(3, cmp), [0, 1, 2])   # the (0,1) (1,2) (0,1) replay swaps back
        pri = [3, 1, 2]
        self.assertEqual(LX.small_sort(3, cmp), [0, 2, 1])
        pri = [1, 2]
        self.assertEqual(LX.small_sort(2, cmp), [1, 0])
        pri = [2, 2]
        self.assertEqual(LX.small_sort(2, cmp), [0, 1])      # a tie never exchanges

    def test_requires_inout(self):
        self.assertEqual(LX.requires_inout("0"), 1)
        self.assertEqual(LX.requires_inout("d"), 0)
        self.assertEqual(LX.requires_inout("0,d"), 1)
        self.assertEqual(LX.requires_inout("0,0"), 2)
        self.assertEqual(LX.requires_inout("=d"), 0)


class Parse(unittest.TestCase):
    def test_sexprs_vectors_and_strings(self):
        n = LX.parse_sexprs('(parallel[ (set (reg:SI 2 v0) (const_int 1)) (use (const_int 0)) ] ) "a(b"')
        self.assertEqual(LX.code_of(n[0]), "parallel")
        self.assertIsInstance(n[0][1], LX.Vec)
        self.assertEqual(n[1], '"a(b"')

    def test_dump_sections(self):
        fn = function()
        self.assertEqual(fn.name, "f")
        self.assertEqual([o.kind for o in fn.d["chain"]][:3], ["note", "insn", "insn"])   # note/i normalised
        self.assertEqual(fn.stats[81]["refs"], 2)
        self.assertEqual(fn.d["blocks"][0]["live"], {3, 4, 29, 30})
        self.assertEqual(fn.d["blocks"][0]["live_pseudos"], {90})
        self.assertEqual(fn.reg_qty[90], -1)                  # multi-block: global


class Replay(unittest.TestCase):
    def setUp(self):
        self.fn = function()
        self.B = self.fn.blocks[0]
        self.run = LX.allocate(self.B, 76)

    def test_qtys_births_deaths_ties(self):
        q = self.B.qtys
        self.assertEqual(len(q), 3)
        self.assertEqual(q[0].regs, [81, 80])                 # the tie: 81 joins 80's qty
        self.assertEqual((q[0].birth, q[0].death, q[0].refs), (2, 12, 4))
        self.assertEqual(q[0].copy, {4})                      # copy-suggested $a0 by insn 10
        self.assertEqual((q[1].regs, q[1].birth, q[1].death), ([82], 7, 12))   # CLOBBER birth 2n-1
        self.assertEqual((q[2].regs, q[2].birth, q[2].death), ([83], 14, 15))  # REG_UNUSED death 2n+1
        self.assertEqual(self.B.count, 7)                      # the label counts, the notes do not

    def test_passes_and_registers(self):
        r = self.run
        self.assertEqual(r["phys"], {0: 4, 1: 2, 2: 3})       # 83 takes its copy suggestion $v1, not the lower $v0
        self.assertEqual(r["how"][0][0], "sugg")
        self.assertEqual(r["how"][2][0], "sugg")
        self.assertEqual(r["how"][1][0], "prio")
        self.assertEqual(r["po"], [0, 1, 2])
        agree, total, miss, _ = LX.fidelity(self.fn, [r])
        self.assertEqual((agree, total, miss), (4, 4, []))

    def test_hard_register_liveness(self):
        # $v1 is live from block entry until insn #7 kills it, so qty 1 (82) cannot take $v1 over 7..12
        self.assertTrue(self.B.hard_at[8] >> 3 & 1)
        self.assertFalse(self.B.hard_at[4] >> 4 & 1)          # $a0 died at insn #1
        self.assertEqual(LX.why_not(self.B, self.run, self.B.qtys[1], 3, 76)[0][:6], "hard $")

    def test_global_span_and_holders(self):
        self.assertEqual(self.B.gspans[90], [(0, 10)])        # live at entry, REG_DEAD at insn #5
        h = LX.global_holders(self.fn, [self.run], 90, 2)
        self.assertEqual(len(h), 1)
        self.assertIn("qty 1 (82) in $v0 over 7..12", h[0][2])

    def test_inverse_priority_and_geometry(self):
        # retail wants 82 in $v1: $v1 is hard-live over 82's life (live from block entry to insn #7), and the
        # finding names the hard register
        res = LX.explain(DUMP, 76, "2.7.2-cdk", retail={80: 4, 81: 4, 82: 3, 83: 3})
        f = [x for x in res["findings"] if x["qty"] == 1][0]
        self.assertEqual((f["got"], f["retail"]), (2, 3))
        self.assertTrue(any(w.startswith("hard $v1") for w in f["why_not"]))
        # a retail $v1 for 83 that the model already gives: no finding for it
        self.assertFalse([x for x in res["findings"] if x["qty"] == 2])

    def test_suggestion_winner_is_not_a_priority_question(self):
        res = LX.explain(DUMP, 76, "2.7.2-cdk", retail={80: 2, 81: 2, 82: 2, 83: 3})
        f = [x for x in res["findings"] if x["qty"] == 0][0]
        self.assertTrue(any("SUGGESTION pass" in w for w in f["why_not"]))


def two_qty_block():
    """A (refs 4, 2..10, prio 10000) and B (refs 2, 4..10, prio 3333) overlap; A is placed first and takes $v0."""
    B = LX.Block(None, {"b": 0})
    B.qtys = [LX.Qty(n=0, regs=[100], size=1, mode="SI", birth=2, death=10, calls=0, min_class="GR_REGS",
                     alt_class="NO_REGS", refs=4, birth_uid=1),
              LX.Qty(n=1, regs=[101], size=1, mode="SI", birth=4, death=10, calls=0, min_class="GR_REGS",
                     alt_class="NO_REGS", refs=2, birth_uid=2)]
    B.count = 6
    B.numbers = {i: 100 + i for i in range(1, 7)}
    return B


class Inverse(unittest.TestCase):
    def test_priority_thresholds_through_the_two_qty_replay(self):
        B = two_qty_block()
        run = LX.allocate(B, 76)
        self.assertEqual(run["phys"], {0: 2, 1: 3})
        sols = LX.search_priority(B, 76, True, {0: 3, 1: 2}, [1], run, [0, 1])
        got = {(s["qty"], s["term"], s["value"]) for s in sols}
        # B refs >= 4 (13333 > 10000); B length <= 1 (at 2 the priorities TIE at 10000 and a tie never exchanges);
        # A refs <= 2 (2500 < 3333); A length >= 25 (at 24 they tie at 3333)
        self.assertEqual(got, {(1, "refs", 4), (1, "length", 1), (0, "refs", 2), (0, "length", 25)})
        self.assertTrue(all(s["crossed"] == [0] or s["crossed"] == [1] for s in sols))

    def test_geometry_earlier_death(self):
        B = two_qty_block()
        geo = LX.search_geometry(B, 76, True, {1: 2}, [1], [0], base_run=LX.allocate(B, 76))
        self.assertIn((0, "death", 4), {(g["qty"], g["term"], g["value"]) for g in geo})


if __name__ == "__main__":
    unittest.main()
