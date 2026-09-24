"""tools/fidelity/split_fingerprint.py: the raw-word walker on synthetic MIPS words - one sequence per
fingerprint kind, one negative per macro/integer exclusion - and the sceptic's relocation detector."""
import sys
import unittest
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools/fidelity"))
import split_fingerprint as S  # noqa: E402

V0, V1, A0, A1, S0, S1, AT, RA = 2, 3, 4, 5, 16, 17, 1, 31


def lui(rt, imm): return (15 << 26) | (rt << 16) | (imm & 0xFFFF)
def addiu(rt, rs, imm): return (9 << 26) | (rs << 21) | (rt << 16) | (imm & 0xFFFF)
def ori(rt, rs, imm): return (13 << 26) | (rs << 21) | (rt << 16) | (imm & 0xFFFF)
def lw(rt, off, base): return (35 << 26) | (base << 21) | (rt << 16) | (off & 0xFFFF)
def lh(rt, off, base): return (33 << 26) | (base << 21) | (rt << 16) | (off & 0xFFFF)
def sw(rt, off, base): return (43 << 26) | (base << 21) | (rt << 16) | (off & 0xFFFF)
def addu(rd, rs, rt): return (rs << 21) | (rt << 16) | (rd << 11) | 33
def beqz(rs, off): return (4 << 26) | (rs << 21) | (off & 0xFFFF)
def jr(rs): return (rs << 21) | 8
def jal(t): return (3 << 26) | ((t >> 2) & 0x3FFFFFF)
NOP = 0


def one(words, **kw):
    """The event of the first lui in `words`."""
    return S.scan(words, 0x80100000, **kw)[0]


class Walker(unittest.TestCase):
    # ---- exclusions (not fingerprints)
    def test_la_macro(self):
        e = one([lui(V0, 0x8008), addiu(V0, V0, 0x3498), jr(RA), NOP])
        self.assertEqual(e["cls"], "macro_la")

    def test_load_macro(self):
        self.assertEqual(one([lui(V0, 0x8008), lw(V0, 0x2E60, V0), jr(RA), NOP])["cls"], "macro_load")

    def test_indexed_load_macro(self):
        self.assertEqual(one([lui(V0, 0x8008), addu(V0, V0, A0), lw(V0, 0x2E60, V0), jr(RA), NOP])["cls"], "macro_idx")

    def test_at_store_macro(self):
        self.assertEqual(one([lui(AT, 0x8008), sw(A0, 0x2E60, AT), jr(RA), NOP])["cls"], "at_macro")

    def test_integer_ori(self):
        self.assertEqual(one([lui(V0, 0x8008), ori(V0, V0, 0x3498), jr(RA), NOP])["cls"], "int_ori")

    def test_integer_value(self):
        self.assertEqual(one([lui(V0, 0x0001), addu(A0, A0, V0), addu(A1, A1, V0), jr(RA), NOP])["cls"], "page_only")

    def test_nonram(self):
        self.assertEqual(one([lui(V0, 0x1F80), lw(V1, 0x10, V0), jr(RA), NOP])["cls"], "nonram")

    # ---- fingerprint kinds
    def test_lo_other_reg(self):
        e = one([lui(V0, 0x8008), addiu(S1, V0, 0x3968), jr(RA), NOP])
        self.assertEqual((e["cls"], e["kinds"]), ("fingerprint", ["lo_other_reg"]))

    def test_interleaved(self):
        e = one([lui(V0, 0x8017), lw(20, 8, S1), addiu(V0, V0, 0x5988), jr(RA), NOP])
        self.assertEqual(e["kinds"], ["interleaved"])

    def test_high_in_delay_slot_taken_path(self):
        # beqz s0,+2 ; lui v0 (slot) ; lbu-ish overwrite on the fall-through ; ... target: addiu v0,v0,lo
        w = [beqz(S0, 2), lui(V0, 0x8002), lw(V0, 2, S0), jr(RA), addiu(V0, V0, 0x428C), jr(RA), NOP]
        e = [x for x in S.scan(w, 0x80100000) if x["i"] == 1][0]
        self.assertEqual(e["cls"], "fingerprint")
        self.assertIn("high_in_slot", e["kinds"])

    def test_slot_lo_is_weak(self):
        e = one([lui(V0, 0x8008), jr(RA), addiu(V0, V0, 0x3498)])
        self.assertEqual(e["kinds"], ["slot_lo"])
        self.assertEqual(S.strict_kinds(e), [])

    def test_store_through_high(self):
        self.assertEqual(one([lui(V0, 0x8008), sw(A0, 0x480C, V0), jr(RA), NOP])["kinds"], ["store_high_base"])

    def test_load_other_reg(self):
        self.assertEqual(one([lui(V0, 0x8008), lh(V1, 0x2E6A, V0), jr(RA), NOP])["kinds"], ["load_other_reg"])

    def test_shared_high(self):
        e = one([lui(A1, 0x8008), lw(V0, 0x2E60, A1), addiu(V0, V0, 1), sw(V0, 0x2E60, A1), jr(RA), NOP])
        self.assertEqual(e["kinds"], ["load_other_reg", "shared_high", "store_high_base"])

    def test_call_clobbers_caller_saved_high(self):
        # lui a0 ; jal ; nop ; addiu a0,a0,lo  -> a0 is dead across the call: no LO user
        self.assertEqual(one([lui(A0, 0x8004), jal(0x80040A88), NOP, addiu(A0, A0, 0x1AE4), jr(RA), NOP])["cls"], "page_only")

    def test_callee_saved_high_survives_call(self):
        e = one([lui(S0, 0x8008), jal(0x80040A88), NOP, lw(V0, 0x10, S0), jr(RA), NOP])
        self.assertIn("after_call", e["flags"])
        self.assertIn("interleaved", e["kinds"])

    def test_page_shared_across_symbols(self):
        w = [lui(V1, 0x8008), lw(V0, 0x2E60, V1), lw(A0, 0x3160, V1), jr(RA), NOP]
        self.assertEqual(S.scan(w, 0x80100000, symstarts=[0x80082E60, 0x80083160])[0]["cls"], "page_shared")
        self.assertEqual(S.scan(w, 0x80100000, symstarts=[0x80082E60])[0]["cls"], "fingerprint")

    def test_splitting_cells(self):
        self.assertTrue(S.splitting("2.7.2-cdk", "-G0"))
        self.assertFalse(S.splitting("2.7.2-cdk", "-mmips-as -G0"))
        self.assertFalse(S.splitting("2.8.1", "-mno-split-addresses"))
        self.assertFalse(S.splitting("2.7.2", ""))


class ScepticReloc(unittest.TestCase):
    def test_reloc_kinds(self):
        words = [["lui", "v0,0x0", ("R_MIPS_HI16", "D_1"), 0], ["lw", "s4,8(s1)", None, 0],
                 ["addiu", "v0,v0,0", ("R_MIPS_LO16", "D_1"), 0],
                 ["lui", "at,0x0", ("R_MIPS_HI16", "D_2"), 0], ["sw", "v0,0(at)", ("R_MIPS_LO16", "D_2"), 0],
                 ["lui", "v1,0x0", ("R_MIPS_HI16", "D_3"), 0], ["lh", "v0,0(v1)", ("R_MIPS_LO16", "D_3"), 0]]
        self.assertEqual(S.sceptic_kinds(words), {"pair_interleaved", "load_base_ne_dest"})


if __name__ == "__main__":
    unittest.main()
