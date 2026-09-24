"""tools/fidelity/aspsx_diff.py: the word comparator (per-function tokens, canonical relocations) and
tools/fidelity/objread.py's LNK expression decoding it depends on."""
import struct
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/fidelity"))
sys.path.insert(0, str(ROOT / "tools"))
import aspsx_diff as A  # noqa: E402
from objread import Obj, read_lnk  # noqa: E402


def words(*ws):
    return b"".join(struct.pack("<I", w) for w in ws)


def elf(text, relocs, syms=None, sec=".text", extra=None):
    o = Obj("elf")
    o.sections[sec] = text
    o.sections.update(extra or {})
    o.symbols.update(syms or {"f": (sec, 0, "func", len(text))})
    o.relocs = relocs
    return o


def lnk(text, relocs, syms=None, sec=".text", extra=None):
    o = Obj("lnk")
    o.sections[sec] = text
    o.sections.update(extra or {})
    o.symbols.update(syms or {"f": (sec, 0, "global", None)})
    o.relocs = relocs
    return o


LUI_V0, LW_V0, JR_RA, NOP = 0x3C020000, 0x8C420000, 0x03E00008, 0
ADDIU_SP = 0x27BD0018


class Comparator(unittest.TestCase):
    def test_identical_is_exact(self):
        t = words(LUI_V0, LW_V0, JR_RA, NOP)
        m = A.View(elf(t, []))
        g = A.View(lnk(t, []), m)
        c = A.compare_units(m, g)
        self.assertTrue(c["exact"]); self.assertEqual(c["diff"], 0)

    def test_relocation_fields_are_masked_and_compared_symbolically(self):
        # GNU as (REL) keeps the addend in the instruction; ASPSX keeps it in the patch expression
        m = A.View(elf(words(LUI_V0 | 0x0001, LW_V0 | 0x2345, JR_RA, NOP),
                       [(".text", 0, "HI16", ("sym", "D_X"), 0x12345), (".text", 4, "LO16", ("sym", "D_X"), 0x2345)]))
        g = A.View(lnk(words(LUI_V0, LW_V0, JR_RA, NOP),
                       [(".text", 0, "HI16", ("sym", "D_X"), 0x12345), (".text", 4, "LO16", ("sym", "D_X"), 0x12345)]), m)
        self.assertTrue(A.compare_units(m, g)["exact"])

    def test_a_different_relocation_target_is_a_difference(self):
        m = A.View(elf(words(0x0C000000, NOP), [(".text", 0, "26", ("sym", "SD_Call"), 0)]))
        g = A.View(lnk(words(0x0C000000, NOP), [(".text", 0, "26", ("sym", "func_80053DA8"), 0)]), m)
        c = A.compare_units(m, g)
        self.assertFalse(c["exact"]); self.assertEqual(c["diff"], 1)
        self.assertEqual(A.classify(c["regions"], m), {"reloc": 1})

    def test_local_jump_targets_compare_function_relative(self):
        # ELF: `j` against the section symbol with the offset in the field; LNK: sectbase + const
        m = A.View(elf(words(NOP, 0x08000000 | (8 >> 2), NOP, JR_RA, NOP), [(".text", 4, "26", ("sec", ".text"), 8)]))
        g = A.View(lnk(words(NOP, 0x08000000, NOP, JR_RA, NOP), [(".text", 4, "26", ("sec", ".text"), 8)]), m)
        self.assertTrue(A.compare_units(m, g)["exact"])

    def test_gp_relative_extern_versus_absolute_is_classified(self):
        # maspsx/GNU as: `lw $2,%gp_rel(D_X)($28)`; genuine ASPSX: `lui/lw` pair (an .extern is absolute)
        m = A.View(elf(words(0x8F820000, JR_RA, NOP), [(".text", 0, "GPREL16", ("sym", "D_X"), 0)],
                       syms={"f": (".text", 0, "func", 12)}))
        g = A.View(lnk(words(LUI_V0, LW_V0, JR_RA, NOP),
                       [(".text", 0, "HI16", ("sym", "D_X"), 0), (".text", 4, "LO16", ("sym", "D_X"), 0)]), m)
        c = A.compare_units(m, g)
        self.assertFalse(c["exact"])
        self.assertEqual(A.classify(c["regions"], m, c["delay_only"]), {"gp-extern": 1})

    def test_return_delay_unfill_is_classified_as_delay_slot(self):
        m = A.View(elf(words(ADDIU_SP, JR_RA, NOP), []))                   # maspsx: un-filled
        g = A.View(lnk(words(JR_RA, ADDIU_SP), []), m)                     # genuine: gcc's filled slot
        c = A.compare_units(m, g)
        self.assertFalse(c["exact"]); self.assertEqual(c["delay_only"], ["f"])

    def test_length_mismatch_is_never_exact(self):
        m = A.View(elf(words(JR_RA, NOP), []))
        g = A.View(lnk(words(JR_RA, NOP, NOP), []), m)
        self.assertFalse(A.compare_units(m, g)["exact"])

    def test_missing_function_counts_all_its_words(self):
        m = A.View(elf(words(JR_RA, NOP), []))
        g = A.View(lnk(words(JR_RA, NOP), [], syms={"other": (".text", 0, "global", None)}), m)
        c = A.compare_units(m, g)
        self.assertEqual(c["missing"], ["f"]); self.assertEqual(c["diff"], 2)

    def test_nested_symbol_is_not_a_boundary_in_lnk(self):
        # a composite `func_X` (4-byte bank) + `func_X_body`: ELF sizes nest the body inside func_X
        t = words(0x12345678, JR_RA, NOP)
        m = A.View(elf(t, [], syms={"func_X": (".text", 0, "func", 12), "func_X_body": (".text", 4, "func", 8)}))
        g = A.View(lnk(t, [], syms={"func_X": (".text", 0, "global", None), "func_X_body": (".text", 4, "global", None)}), m)
        self.assertEqual(g.funcs["func_X"], (".text", 0, 12))
        self.assertTrue(A.compare_units(m, g, ["func_X"])["exact"])

    def test_composite_prefix_section_is_part_of_the_unit(self):
        pre = {".text.f": words(0x11111111)}
        m = A.View(elf(words(JR_RA, NOP), [], extra=pre))
        g = A.View(lnk(words(JR_RA, NOP), [], extra={".text.f": words(0x22222222)}), m)
        self.assertEqual(len(m.tokens("f")), 3)
        self.assertFalse(A.compare_units(m, g)["exact"])


def lnk_bytes(records):
    return b"LNK\x02" + b"".join(records) + b"\x00"


def rec_section(idx, name):
    return bytes([16]) + struct.pack("<HHB", idx, 0, 4) + bytes([len(name)]) + name.encode()


def rec_switch(idx):
    return bytes([6]) + struct.pack("<H", idx)


def rec_bytes(b):
    return bytes([2]) + struct.pack("<H", len(b)) + b


def rec_xref(idx, name):
    return bytes([14]) + struct.pack("<H", idx) + bytes([len(name)]) + name.encode()


def rec_xdef(idx, sect, off, name):
    return bytes([12]) + struct.pack("<HHI", idx, sect, off) + bytes([len(name)]) + name.encode()


def rec_patch(typ, off, expr):
    return bytes([10, typ]) + struct.pack("<H", off) + expr


def e_const(v):
    return bytes([0]) + struct.pack("<I", v)


def e_sym(i):
    return bytes([2]) + struct.pack("<H", i)


def e_sstart(s):
    return bytes([12]) + struct.pack("<H", s)


def e_add(a, b):
    return bytes([44]) + a + b


def e_sub(a, b):
    return bytes([46]) + a + b


class LnkExpressions(unittest.TestCase):
    def test_sub_is_second_minus_first_and_patches_are_chunk_relative(self):
        data = lnk_bytes([
            rec_section(1, ".text"), rec_section(4, ".sdata"), rec_xref(9, "sym"), rec_xdef(10, 1, 0, "f"),
            rec_switch(1),
            rec_bytes(words(LUI_V0, LW_V0)),
            rec_patch(82, 0, e_sub(e_const(4), e_sym(9))),              # sym - 4 (measured spelling)
            rec_bytes(words(0x8F830000, JR_RA)),                         # second chunk starts at 8
            rec_patch(30, 0, e_sub(e_sstart(4), e_sym(9))),             # 2.56-2.81 gp-relative form
        ])
        o = read_lnk(data)
        self.assertEqual(o.unknown, [])
        self.assertEqual(o.relocs[0], (".text", 0, "HI16", ("sym", "sym"), (-4) & 0xFFFFFFFF))
        self.assertEqual(o.relocs[1], (".text", 8, "GPREL16", ("sym", "sym"), 0))
        self.assertEqual(o.symbols["f"][:2], (".text", 0))

    def test_add_of_section_and_constant(self):
        data = lnk_bytes([rec_section(1, ".text"), rec_section(2, ".rdata"), rec_switch(1),
                          rec_bytes(words(0x08000000, NOP)),
                          rec_patch(74, 0, e_add(bytes([4]) + struct.pack("<H", 2), e_const(48)))])
        o = read_lnk(data)
        self.assertEqual(o.relocs, [(".text", 0, "26", ("sec", ".rdata"), 48)])


if __name__ == "__main__":
    unittest.main()
