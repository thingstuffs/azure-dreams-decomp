"""tools/fidelity/epilogue_model.py: the cc1 epilogue text model (gcc 2.7.2's function_epilogue decision applied
to a 2.8-era listing), the census, and the retail return-shape classifier."""
import struct
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/fidelity"))
sys.path.insert(0, str(ROOT / "tools"))
import epilogue_model as E  # noqa: E402

BLOCK = "\t.set\tnoreorder\n\t.set\tnomacro\n\tj\t$31\n\taddu\t$sp,$sp,{n}\n\t.set\tmacro\n\t.set\treorder\n"


def fn(name, mask, body, n=32):
    return (f"\t.ent\t{name}\n{name}:\n\t.frame\t$sp,{n},$31\n\t.mask\t0x{mask:08x},-8\n\t.fmask\t0x00000000,0\n"
            f"{body}{BLOCK.format(n=n)}\n\t.end\t{name}\n")


MULTI = fn("f", 0x80030000, "\tlw\t$31,24($sp)\n\tlw\t$17,20($sp)\n\tlw\t$16,16($sp)\n\t#nop\n")
RA_LD = fn("g", 0x80000000, "\tlw\t$31,16($sp)\n\t#nop\n", 24)                         # lw $31 / #nop / j
RA_X = fn("h", 0x80000000, "\tlw\t$31,16($sp)\n\tmove\t$2,$0\n", 24)                   # lw $31 / X / j
LEAF = "\t.ent\tk\nk:\n\t.mask\t0x00000000,0\n\t.fmask\t0x00000000,0\n\t.set\tnoreorder\n\t.set\tnomacro\n" \
       "\tj\t$31\n\tmove\t$2,$4\n\t.set\tmacro\n\t.set\treorder\n\n\t.end\tk\n"


class TextModel(unittest.TestCase):
    def test_multi_restore_rewritten_by_both_rules(self):
        for rule in ("all", "t272"):
            out = E.rewrite(MULTI, rule)
            self.assertIn("\tlw\t$16,16($sp)\n\t#nop\n\taddu\t$sp,$sp,32\n\tj\t$31\n", out)
            self.assertNotIn("noreorder", out)

    def test_ra_only_after_ra_load_rewritten(self):
        # 2.7.2: no epilogue delay insn -> noreorder is false -> `addu / j $31` in reorder mode
        self.assertIn("\taddu\t$sp,$sp,24\n\tj\t$31\n", E.rewrite(RA_LD, "t272"))

    def test_ra_only_with_delay_insn_kept(self):
        # 2.7.2's epilogue-delay form `lw $31 / X / j $31 / addu` is printed under noreorder: t272 keeps it
        self.assertEqual(E.rewrite(RA_X, "t272"), RA_X)
        self.assertNotEqual(E.rewrite(RA_X, "all"), RA_X)

    def test_leaf_and_non_sp_slot_untouched(self):
        for rule in ("all", "t272"):
            self.assertEqual(E.rewrite(LEAF, rule), LEAF)

    def test_rule_is_per_function(self):
        src = RA_X + "\n" + MULTI
        out = E.rewrite(src, "t272")
        self.assertIn(RA_X, out)
        self.assertEqual(out.count("noreorder"), 1)

    def test_census(self):
        c = {x["f"]: x for x in E.census(MULTI + RA_X + LEAF)}
        self.assertEqual((c["f"]["ra_only"], c["f"]["restores"], c["f"]["nr_sp"]), (False, 3, 1))
        self.assertEqual((c["h"]["ra_only"], c["h"]["nr_sp"], c["h"]["blocks"][0]["after_ra_load"]), (True, 1, False))
        self.assertEqual((c["k"]["nr_sp"], c["k"]["other_ret"]), (0, 1))     # a return whose slot is not the teardown


class Tok:
    def __init__(self, ws):
        self.ws = ws

    def tokens(self, f):
        return [(w, None, None) for w in self.ws]


class RetailShapes(unittest.TestCase):
    JR, NOP, SP, LWRA, LWS0 = 0x03E00008, 0, 0x27BD0020, 0x8FBF0018, 0x8FB00010

    def test_classes(self):
        E_ = E.retail_shapes
        self.assertEqual(E_(Tok([self.LWS0, self.SP, self.JR, self.NOP]), ["f"]), {"sp_before_nop": 1})
        self.assertEqual(E_(Tok([self.LWRA, self.SP, self.JR, self.NOP]), ["f"]), {"sp_before_nop_ld_shadow": 1})
        self.assertEqual(E_(Tok([self.LWRA, self.NOP, self.JR, self.SP]), ["f"]), {"filled_sp": 1})
        self.assertEqual(E_(Tok([self.LWRA, self.JR, self.SP]), ["f"]), {"filled_sp_after_lw_ra": 1})
        self.assertEqual(E_(Tok([0x00801021, self.JR, 0x24020001]), ["f"]), {"filled_other": 1})


if __name__ == "__main__":
    unittest.main()
