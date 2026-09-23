"""Round-76 harvest openings: T69_UNPIN_REST, T111_HOIST, T115_CALLCOPY, T85_WIDE and alloc_sim.set_counts.
All textual or synthetic-dump checks; nothing compiles."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t69_prologue as T69  # noqa: E402
import t111_selfadd as T111  # noqa: E402
import t115_carrierfold as T115  # noqa: E402
import t85_allocorder as T85  # noqa: E402
import alloc_sim  # noqa: E402
import t94_castsplit as T94  # noqa: E402
from pin_census import sites_of  # noqa: E402

PROLOGUE = '''#include "common.h"
void f(void *entity_in, void *motion_in, void *sprite_in)
{
    register void *entity ASM_REG("$17") = entity_in;
    void *motion = motion_in;
    register void *sprite ASM_REG("$20") = sprite_in;
    register void *entity_state ASM_REG("$19") = entity;

    ASM_KEEP(entity_in);
    func_80001000(entity_in, motion_in, sprite_in);
    func_80001004(entity_state, motion, sprite);
}
'''

SELFADD = '''#include "common.h"
void g(void *obj, s32 arg0) {
    u8 *work;
    s32 final_arg0;

    if (obj != 0) {
        final_arg0 = arg0;
        work = (u8 *)obj + 0x20;
        ASM_KEEP(work);
        ((S_0 *)work)->unk_13 = 0x1C;
        func_80001000(obj, final_arg0);
    }
}
'''

CALLCOPY = '''#include "common.h"
void h(void *obj) {
    void *init_obj;
    s32 flag_bits;

    init_obj = obj;
    ASM_KEEP(init_obj);
    flag_bits = func_800A6D30(init_obj);
    init_obj = obj;
    func_80001000(init_obj, flag_bits);
}
'''


class TestT69UnpinRest(unittest.TestCase):
    def test_surviving_copy_takes_the_parameter_reads(self):
        cands = dict(T69.prologue_candidates(PROLOGUE))
        lab = next(l for l in cands if l.endswith(":entity+motion"))
        params = {"entity_in", "motion_in", "sprite_in"}
        vs = dict(T69.rest_variants(cands[lab], params))
        self.assertIn("usecopy:sprite_in", vs)
        self.assertIn("func_80001000(entity, motion, sprite);", vs["usecopy:sprite_in"])
        # the parameter the merge created (`entity`) is never renamed to its copy `entity_state`
        self.assertNotIn("usecopy:entity", vs)
        pinned = {k: len(sites_of(v)) for k, v in vs.items()}
        self.assertEqual(pinned["usecopy:sprite_in+unpin-all"], 0)
        self.assertTrue(any(k.startswith("usecopy:sprite_in+unpin-") and n == 1 for k, n in pinned.items()))


class TestT111Hoist(unittest.TestCase):
    def test_arm_opening_copy_moves_above_the_if(self):
        cands = dict(T111.candidates(SELFADD))
        h = [c for l, c in cands.items() if l.endswith(":hoist")]
        self.assertTrue(h)
        t = h[0]
        self.assertLess(t.index("final_arg0 = arg0;"), t.index("if (obj != 0)"))

    def test_no_hoist_when_the_condition_reads_the_copy(self):
        t = SELFADD.replace("if (obj != 0)", "if (final_arg0 != 0)")
        self.assertFalse([l for l, _c in T111.candidates(t) if l.endswith(":hoist")])


class TestT115CallCopy(unittest.TestCase):
    def test_call_result_is_routed_through_the_kept_copy(self):
        cc = T115.callcopy_candidates(CALLCOPY)
        self.assertEqual(len(cc), 1)
        t = cc[0][1]
        self.assertIn("init_obj = (void *)func_800A6D30(init_obj);", t)
        self.assertIn("flag_bits = (s32)init_obj;", t)
        self.assertNotIn("ASM_KEEP(init_obj)", t)

    def test_no_reset_no_candidate(self):
        t = CALLCOPY.replace("    init_obj = obj;\n    func_80001000", "    func_80001000")
        self.assertEqual(T115.callcopy_candidates(t), [])


CASTUSE = '''#include "common.h"
void k(s32 packet_or_angle, s16 *end_xy) {
    ASM_KEEP_NV(packet_or_angle);
    end_xy[0] = (func_80064584((s16)packet_or_angle) >> 7) + 0x362;
}
'''


class TestT94CastUse(unittest.TestCase):
    def test_cast_at_the_use_becomes_the_in_place_shift_pair(self):
        cc = T94.castuse_candidates(CASTUSE)
        self.assertEqual(len(cc), 1)
        t = cc[0][1]
        self.assertIn("packet_or_angle <<= 16;\n    packet_or_angle >>= 16;", t)
        self.assertIn("func_80064584(packet_or_angle)", t)
        self.assertNotIn("ASM_KEEP", t)

    def test_a_write_in_the_statement_blocks_it(self):
        t = CASTUSE.replace("end_xy[0] = (func", "packet_or_angle = end_xy[0] = (func")
        self.assertEqual(T94.castuse_candidates(t), [])


class TestT85Wide(unittest.TestCase):
    def _rd(self, order, disp):
        return {"order": order, "disp": disp, "stats": {p: {"calls_crossed": 1} for p in order}}

    def test_extra_allocnos_from_erased_keeps(self):
        pinned = self._rd([80, 81], {80: 16, 81: 17})
        erased = self._rd([80, 81, 82, 83], {80: 17, 81: 18, 82: 16, 83: 2})
        pins = [("x", 18, None)]
        os.environ["T85_WIDE"] = "0"
        self.assertFalse(T85.is_order_site(pinned, erased, pins, 3)[0])
        os.environ["T85_WIDE"] = "1"
        self.assertTrue(T85.is_order_site(pinned, erased, pins, 3)[0])
        os.environ.pop("T85_WIDE")


LREG = '''(insn 25 37 39 (set (reg/v:SI 92)
        (const_int 0)) 168 {movsi_internal2} (nil)
    (expr_list:REG_EQUIV (const_int 0)
        (nil)))

(insn 26 25 27 (set (reg/v:SI 93)
        (reg:SI 4 a0)) 168 {movsi_internal2} (nil)
    (nil))

(insn 27 26 28 (set (reg/v:SI 93)
        (asm_operands/v ("") ("=r") 0[ (reg/v:SI 93) ] [ (asm_input:SI ("0")) ] ("f.c") 9)) -1 (nil)
    (nil))
'''


class TestAllocSimSets(unittest.TestCase):
    def test_set_counts_and_doubling(self):
        sc = alloc_sim.set_counts(LREG, 76)
        self.assertEqual(sc[92], (1, True))
        self.assertEqual(sc[93], (2, False))
        rd = {"order": [92, 93], "first": 76, "sets": sc,
              "stats": {92: {"n_refs": 4, "live_length": 40}, 93: {"n_refs": 4, "live_length": 20}}}
        self.assertEqual(alloc_sim.doubled(rd), {92: True, 93: False})
        self.assertEqual(alloc_sim.priority_undoubled(rd, 92), alloc_sim.priority(4, 20))


class TestT120Unvolatile(unittest.TestCase):
    SRC = '''#include "common.h"
void m(u8 *initial_stats, u16 config) {
    register s32 old_base ASM_REG("$6");
    volatile u16 slot;

    *(u16 *)&slot = config;
    old_base = *(volatile u8 *)(initial_stats + 5);
    func_80001000(old_base, slot);
}
'''

    def test_sites_and_drop(self):
        import t120_unvolatile as T120
        st = T120.sites(self.SRC)
        self.assertEqual(sorted(s["kind"] for s in st), ["cast", "decl"])
        cast = next(s for s in st if s["kind"] == "cast")
        self.assertIn("old_base", cast["names"])
        t = T120.drop(self.SRC, st)
        self.assertNotIn("volatile", t)
        self.assertIn("    slot = config;", t)
        self.assertIn("old_base = *(u8 *)(initial_stats + 5);", t)


if __name__ == "__main__":
    unittest.main()
