"""screen.normalise: assembler-local labels (`1f`/`1:`) share the `$L` label space.

The compiler is not run here - `normalise` takes the raw cc1 lines, so these are textual.  The
listings below are the two spellings of one block: the `abssi2` expansion `abs()` produces and the
`bgez $L.. / subu / $L..:` a hand-written conditional negate produces.  They assemble to the same
bytes, so the screen must call them equal (the t91_absfresh family, 2026-09-21).
"""
import os, re, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import screen as S  # noqa: E402


def old_norm(src):
    """The normalisation as it stood before the numeric-local-label fix (the regression oracle)."""
    out, lab, inside = [], {}, False
    for ln in src:
        s = ln.split("#")[0].strip()
        if s.startswith(".ent"):
            inside = True; out.append(".ent"); continue
        if s.startswith(".end"):
            inside = False; continue
        if not inside or not s or s.startswith((".loc", ".frame", ".mask", ".fmask", ".set")):
            continue
        s = re.sub(r"\s+", " ", s)
        s = re.sub(r"\$L\d+", lambda m: lab.setdefault(m.group(0), "L%d" % len(lab)), s)
        out.append(S._addr(s))
    return out


def listing(body):
    return ["\t.ent\tf", "\t.frame\t$sp,0,$31", "\t.mask\t0x00000000,0"] + \
           ["\t" + l if not l.endswith(":") else l for l in body] + ["\t.end\tf"]


PINNED = listing([
    "lb\t$2,114($17)",
    "lb\t$3,115($17)",
    "bgez\t$2,$L18",
    "subu\t$2,$0,$2",
    "$L18:",
    "bgez\t$3,$L19",
    "subu\t$3,$0,$3",
    "$L19:",
    "sb\t$2,114($17)",
    "beq\t$4,$0,$L20",
    "sb\t$3,115($17)",
    "$L20:",
])
ABS = listing([
    "lb\t$2,114($17)",
    "lb\t$3,115($17)",
    "bgez\t$2,1f",
    "subu\t$2,$0,$2",
    "1:",
    "bgez\t$3,1f",
    "subu\t$3,$0,$3",
    "1:",
    "sb\t$2,114($17)",
    "beq\t$4,$0,$L18",
    "sb\t$3,115($17)",
    "$L18:",
])


class LocalLabels(unittest.TestCase):
    def test_abs_expansion_equals_the_hand_written_negate(self):
        self.assertEqual(S.sdiff(S.normalise(PINNED), S.normalise(ABS)), 0)
        self.assertNotEqual(S.sdiff(old_norm(PINNED), old_norm(ABS)), 0)   # what the fix repaired

    def test_each_definition_is_its_own_label(self):
        out = S.normalise(ABS)
        self.assertEqual([l for l in out if l.endswith(":")], ["L0:", "L1:", "L2:"])
        self.assertIn("bgez $2,L0", out)
        self.assertIn("bgez $3,L1", out)                  # the SECOND `1:`, not the first
        self.assertIn("beq $4,$0,L2", out)

    def test_backward_reference_takes_the_previous_definition(self):
        out = S.normalise(listing(["1:", "addiu $2,$2,-1", "bne $2,$0,1b", "b 1f", "nop", "1:"]))
        self.assertEqual([l for l in out if l.endswith(":")], ["L0:", "L1:"])
        self.assertIn("bne $2,$0,L0", out)
        self.assertIn("b L1", out)

    def test_a_reference_with_no_definition_is_left_alone(self):
        out = S.normalise(listing(["bgez $2,1f", "subu $2,$0,$2"]))
        self.assertIn("bgez $2,1f", out)

    def test_hex_and_offsets_are_not_labels(self):
        out = S.normalise(listing(["andi $2,$2,0x1f", "lb $3,1($4)", "li $5,1"]))
        self.assertEqual(out, [".ent", "andi $2,$2,0x1f", "lb $3,1($4)", "li $5,1"])

    def test_division_check_labels_are_numbered_too(self):
        out = S.normalise(listing(["div $0,$2,$3", "bne $3,$0,1f", "break 7", "1:", "mflo $2"]))
        self.assertIn("bne $3,$0,L0", out)
        self.assertIn("L0:", out)


class NoRegression(unittest.TestCase):
    def test_a_listing_without_numeric_labels_normalises_as_before(self):
        self.assertEqual(S.normalise(PINNED), old_norm(PINNED))
        big = listing(["lui $2,%hi(D_80174078+16)", "addiu $2,$2,%lo(D_80174078+16)",
                       "li $3,0x00010000", "addu $4,$5,8", "beq $2,$0,$L7", "b $L3", "$L7:", "$L3:"])
        self.assertEqual(S.normalise(big), old_norm(big))

    def test_only_an_exact_no_op_move_is_dropped(self):
        out = S.normalise(listing(["move $2,$2", "move $2,$3"]))
        self.assertEqual(out, [".ent", "move $2,$3"])


if __name__ == "__main__":
    unittest.main()
