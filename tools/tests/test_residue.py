"""`tools/lanes/residue.fingerprint` on synthetic listings: one class per test, both shape modes.

No compiler: a `compile_s` listing is just a list of normalised instruction strings, so every class
can be built by hand.  The point of the module is that the census side and the catalogue side read a
residue with the SAME function, so the classes have to be exact - in particular a `$L` label
renumber must not read as a recolour (`screen.py` renumbers labels, and the old `\\$\\w+` anonymiser
blanked a label exactly like a register).
"""
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/lanes"))

import residue as R


A = ["addiu $sp,$sp,-24", "sw $31,20($sp)", "move $16,$4", "lw $2,0($16)", "jr $31"]


class Classes(unittest.TestCase):
    def test_nobuild(self):
        fp = R.fingerprint(A, None)
        self.assertEqual(fp["cls"], "NOBUILD")
        self.assertIsNone(fp["d"])
        self.assertEqual(fp["band"], "none")
        self.assertEqual(fp["L0"], "NOBUILD|none")
        self.assertEqual(R.fingerprint(None, A)["cls"], "NOBUILD")

    def test_invisible(self):
        fp = R.fingerprint(A, list(A))
        self.assertEqual(fp["cls"], "INVISIBLE")
        self.assertEqual(fp["d"], 0)
        self.assertEqual(fp["band"], "0")
        self.assertEqual(fp["shape"], "")
        self.assertEqual(fp["L2"], "INVISIBLE|0||")

    def test_moved(self):
        b = [A[0], A[2], A[1], A[3], A[4]]       # the same lines, sw and move exchanged
        fp = R.fingerprint(A, b)
        self.assertEqual(fp["cls"], "MOVED")
        self.assertEqual(fp["d"], 2)
        self.assertEqual(fp["band"], "1-2")
        self.assertEqual(fp["shape"], "-move +move")   # difflib spells the exchange as one line moved
        self.assertEqual(fp["regs"], [])

    def test_recoloured(self):
        b = ["addiu $sp,$sp,-24", "sw $31,20($sp)", "move $17,$4", "lw $2,0($17)", "jr $31"]
        fp = R.fingerprint(A, b)
        self.assertEqual(fp["cls"], "RECOLOURED")
        self.assertEqual(fp["d"], 4)
        self.assertEqual(fp["band"], "3-4")
        self.assertEqual(fp["shape"], "-lw,move +lw,move")
        self.assertEqual(fp["regs"], [["$16", "$17"]])
        self.assertEqual(fp["regfam"], [["s", "s"]])
        self.assertTrue(fp["L2"].endswith("|s>s"))

    def test_both(self):
        b = ["addiu $sp,$sp,-24", "move $17,$4", "sw $31,20($sp)", "lw $2,0($17)", "jr $31"]
        fp = R.fingerprint(A, b)
        self.assertEqual(fp["cls"], "BOTH")
        self.assertEqual(fp["regs"], [["$16", "$17"]])

    def test_changed(self):
        b = ["addiu $sp,$sp,-24", "sw $31,20($sp)", "move $16,$4", "lbu $2,0($16)", "jr $31"]
        fp = R.fingerprint(A, b)
        self.assertEqual(fp["cls"], "CHANGED")
        self.assertEqual(fp["shape"], "-lw +lbu")
        self.assertEqual(fp["regs"], [])

    def test_changed_when_line_counts_differ(self):
        fp = R.fingerprint(A, A + ["nop"])
        self.assertEqual(fp["cls"], "CHANGED")

    def test_label_renumber_is_not_a_recolour(self):
        ref = ["beq $2,$0,L3", "b L4", "L3:", "L4:"]
        cand = ["beq $2,$0,L4", "b L3", "L4:", "L3:"]
        self.assertEqual(R.fingerprint(ref, cand)["cls"], "CHANGED")
        dollar = ["beq $2,$0,$L3", "b $L4"]
        dollar2 = ["beq $2,$0,$L4", "b $L3"]
        self.assertEqual(R.fingerprint(dollar, dollar2)["cls"], "CHANGED")


class Shape(unittest.TestCase):
    def test_exact_mode_counts_repeats(self):
        ref = ["sw $16,0($sp)", "sw $17,4($sp)", "move $2,$4"]
        cand = ["sw $18,0($sp)", "sw $19,4($sp)", "move $2,$4"]
        fp = R.fingerprint(ref, cand)
        self.assertEqual(fp["shape"], "-swx2 +swx2")
        self.assertEqual(fp["d"], 4)

    def test_far_mode_top_four_each_side(self):
        ref = ["op%d $%d,$%d" % (i % 6, i % 8, (i + 1) % 8) for i in range(40)]
        cand = ["xop%d $%d,$%d" % (i % 9, i % 8, (i + 1) % 8) for i in range(40)]
        fp = R.fingerprint(ref, cand)
        self.assertEqual(fp["d"], 80)
        self.assertEqual(fp["band"], "33+")
        self.assertTrue(fp["shape"].startswith("far:-"))
        minus = fp["shape"][len("far:-"):].split(" +")[0]
        plus = fp["shape"].split(" +")[1]
        self.assertEqual(len(minus.split(",")), 4)
        self.assertEqual(len(plus.split(",")), 4)

    def test_shape_mode_switches_at_eight_changed_lines(self):
        ref = ["op%d $2,$3" % i for i in range(20)]
        near = list(ref)
        for i in range(4):
            near[i] = "zz%d $2,$3" % i          # 4 changed a side = 8 changed lines
        self.assertFalse(R.fingerprint(ref, near)["shape"].startswith("far:"))
        far = list(ref)
        for i in range(5):
            far[i] = "zz%d $2,$3" % i           # 10 changed lines
        self.assertTrue(R.fingerprint(ref, far)["shape"].startswith("far:"))


class Families(unittest.TestCase):
    def test_numeric_and_named_map_the_same(self):
        for num, name, fam in (("$0", "$zero", "zero"), ("$1", "$at", "at"), ("$2", "$v0", "v"),
                               ("$4", "$a0", "a"), ("$8", "$t0", "t"), ("$16", "$s0", "s"),
                               ("$24", "$t8", "t"), ("$26", "$k0", "k"), ("$28", "$gp", "gp"),
                               ("$29", "$sp", "sp"), ("$30", "$fp", "fp"), ("$31", "$ra", "ra")):
            self.assertEqual(R.regfamily(num), fam, num)
            self.assertEqual(R.regfamily(name), fam, name)
        self.assertEqual(R.regfamily("$f4"), "other")

    def test_bands(self):
        self.assertEqual([R.band_of(x) for x in (0, 1, 2, 3, 4, 5, 8, 9, 16, 17, 32, 33, 900)],
                         ["0", "1-2", "1-2", "3-4", "3-4", "5-8", "5-8", "9-16", "9-16",
                          "17-32", "17-32", "33+", "33+"])
        self.assertEqual(R.band_of(None), "none")

    def test_keys_nest(self):
        fp = R.fingerprint(A, ["addiu $sp,$sp,-24", "sw $31,20($sp)", "move $17,$4",
                               "lw $2,0($17)", "jr $31"])
        self.assertTrue(fp["L1"].startswith(fp["L0"] + "|"))
        self.assertTrue(fp["L2"].startswith(fp["L1"] + "|"))


if __name__ == "__main__":
    unittest.main()
