"""alloc_need.py (the allocation inverse) and alloc_sim's initialiser-aware declaration order.  Pure functions
only: no compile, no scorer, `kitlib.bootstrap` is never called.  The threshold cases are the four
inequalities round-80 lanes derived by hand (r81_opus_allocneed validated the tool on the real rows)."""
import sys
import unittest
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
KIT = ROOT / "tools/lanes/lanekit"
for sub in (ROOT / "tools/lanes", ROOT / "tools/xform", ROOT / "tools", KIT):   # KIT ends up first
    sys.path.insert(0, str(sub))

import alloc_need as A                                                    # noqa: E402
import alloc_sim                                                          # noqa: E402


def key(refs, live, pseudo, size=1):
    return (refs, live, size, pseudo)


class Priority(unittest.TestCase):
    def test_allocno_compare_verbatim(self):
        self.assertEqual(A.prio(21, 82), 10243)          # 8180A990 entity
        self.assertEqual(A.prio(26, 101), 10297)         # object_or_kind
        self.assertEqual(A.prio(2, 20), 1000)            # 80DE9000 saved_a
        self.assertEqual(A.prio(4, 77), 1038)            # position
        self.assertEqual(A.prio(1, 5), 0)                # floor_log2(1) = 0
        self.assertEqual(A.prio(16, 148), 4324)          # the floor_log2 cliff: 15 refs = 3040
        self.assertEqual(A.prio(15, 148), 3040)

    def test_tie_breaks_on_pseudo(self):
        self.assertTrue(A.outranks(key(2, 20, 82), key(4, 80, 90)))     # 1000 == 1000, lower pseudo first
        self.assertFalse(A.outranks(key(4, 80, 90), key(2, 20, 82)))


class Thresholds(unittest.TestCase):
    def test_8180A990_entity_over_object_or_kind(self):
        th = A.thresholds(key(21, 82, 120), key(26, 101, 84))
        self.assertEqual(th, {"hi_refs": 22, "hi_live": 81, "lo_refs": 25, "lo_live": 102})

    def test_80DE9000_tie_break(self):
        th = A.thresholds(key(2, 20, 82), key(4, 77, 90))
        self.assertEqual(th["hi_live"], 19)
        self.assertEqual(th["lo_live"], 80)               # 4/80 = 1000 ties, saved_a wins on its index
        self.assertEqual(th["hi_refs"], 3)

    def test_80921B2C_direction_state_below_z_offset(self):
        th = A.thresholds(key(2, 86, 83), key(3, 98, 88))
        self.assertEqual(th["lo_refs"], 2)
        self.assertEqual(th["lo_live"], 129)              # 3/129 = 232 ties z_offset's 232, 83 < 88

    def test_80D3BFD0_action_param_over_sprite(self):
        th = A.thresholds(key(2, 46, 81), key(5, 228, 82))
        self.assertEqual(th["hi_live"], 45)
        self.assertEqual(th["lo_refs"], 4)

    def test_cost_prefers_one_ref_over_many_insns(self):
        hi, lo = key(21, 82, 120), key(26, 101, 84)
        c = A.cost(A.thresholds(hi, lo), hi, lo)
        self.assertEqual(c[1:], ("live", "hi"))
        self.assertAlmostEqual(c[0], 1 / 8.0)


class Listing(unittest.TestCase):
    def test_callee_save_slots_are_one_word_under_another_colour(self):
        self.assertEqual(A.vkey("sw s4,64(sp)"), A.vkey("sw s3,60(sp)"))
        self.assertEqual(A.vkey("move s4,a1"), A.vkey("move s3,a1"))
        self.assertNotEqual(A.vkey("sw v0,16(sp)"), A.vkey("sw s3,60(sp)"))

    def test_insn_regs_skip_notes(self):
        lreg = ("(insn 6 4 8 (set (reg/v:SI 81)\n        (reg:SI 5 a1)) -1 (nil)\n"
                "    (expr_list:REG_DEAD (reg:SI 90)\n        (nil)))\n"
                "(insn 8 6 10 (set (reg:SI 82) (reg/v:SI 81)) -1 (nil))\n")
        got = A.parse_insn_regs(lreg, 76)
        self.assertEqual(got[6], ({81}, {5}))
        self.assertEqual(got[8], ({81, 82}, set()))

    def test_rotation_votes(self):
        # 80921B2C's shape: x (81) got s4, retail s3; the identical `addu v0,v0,s4` of y (82) must NOT vote for x
        rows = [(0, "move s4,a1", "move s3,a1"), (1, "move s5,a2", "move s4,a2"),
                (2, "addu v0,v0,s4", "addu v0,v0,s3"), (3, "addu v0,v0,s5", "addu v0,v0,s4")]
        asm = ("\t.ent f\n\tmove\t$20,$5\t\t# 6 movsi\n\tmove\t$21,$6\t\t# 7 movsi\n"
               "\taddu\t$2,$2,$20\t\t# 9 addsi3\n\taddu\t$2,$2,$21\t\t# 10 addsi3\n\t.end f\n")
        uid_regs = {6: ({81}, {5}), 7: ({82}, {6}), 9: ({81, 90}, set()), 10: ({82, 91}, set())}
        disp = {81: 20, 82: 21, 90: 2, 91: 2}
        votes, _cov = A.listing_votes(rows, asm, uid_regs, disp)
        self.assertEqual(dict(votes[81]), {19: 2})
        self.assertEqual(dict(votes[82]), {20: 2})


class Declarations(unittest.TestCase):
    TEXT = ("void f(void *position, s32 x_offset) {\n"
            "    s32 saved = x_offset;\n"
            "    u8 *p = (u8 *)position + 4, *q;\n"
            "    u8 *state;\n"
            "    state = p;\n"
            "    p->x = 1;\n"
            "}\n")

    def test_initialised_declarations_take_their_pseudo(self):
        m = alloc_sim.decl_pseudos(self.TEXT, 76)["map"]
        self.assertEqual(m, {"position": 80, "x_offset": 81, "saved": 82, "p": 83, "q": 84, "state": 85})

    def test_strip_inits(self):
        self.assertEqual(alloc_sim._strip_inits("    s32 i = f(a, b), j;"), "    s32 i, j;")
        self.assertIsNone(alloc_sim._strip_inits("    p->x = 1;"))
        self.assertEqual(alloc_sim._strip_inits("    s16 k;"), "    s16 k;")


if __name__ == "__main__":
    unittest.main()
