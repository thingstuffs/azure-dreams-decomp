"""T85: lever detection, the declaration->pseudo map and the APPEARS test are textual/dump-shaped;
cc1, the simulator's calibration and `vf` are not exercised here."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import alloc_sim as A  # noqa: E402
import t85_allocorder as M  # noqa: E402

# lever (a): dungeon/func_8009AB4C's shape - a local copy of a formal, assigned twice, never written.
A_TEXT = '''#include "common.h"
s32 f(void *entity, u16 x, u16 y) {
    u16 *offsets;
    register void *entity_data ASM_REG("$19");
    void *current_entity;
    u16 base_x;
    s32 result;
    register s32 attempt ASM_REG("$18");

    current_entity = entity;
    base_x = x;
    offsets = D_8006CCD8;
    entity_data = *(void **)((s8 *)current_entity - 0x14);
    for (attempt = 0; attempt < 8; attempt++) {
        result = g(current_entity, base_x + offsets[attempt]);
        if (result != 0) {
            current_entity = entity;
            return result;
        }
    }
    return 0;
}
'''

# lever (b): town/func_800AC3CC's shape - a formal overwritten with a second meaning.
B_TEXT = '''#include "common.h"
s32 f(s32 group_id, void *record) {
    register s32 table_index ASM_REG("$16");
    s32 row_index;
    s32 result;

    table_index = h(group_id);
    if (k(group_id, record) != 0) {
        if (FIELD_U8(record, 1) == 13) {
            record = (void *)3;
        } else {
            record = (void *)m(record);
        }
        row_index = n(table_index);
        ASM_KEEP(table_index);
        result = tables[row_index][(s32)record];
        return result;
    }
    return 0;
}
'''

NO_LEVER = '''#include "common.h"
s32 f(void *p) {
    register void *keep ASM_REG("$16");

    keep = q(p);
    return r(keep);
}
'''


class Declarations(unittest.TestCase):
    def test_pseudo_map_follows_declaration_order(self):
        m = A.decl_pseudos(A_TEXT, 76)["map"]
        # 76..79 are the virtual registers; the two u16 formals each add a promotion pseudo
        self.assertEqual(m["entity"], 80)
        self.assertEqual((m["x"], m["y"]), (81, 83))
        # every local takes a pseudo in source order, the ASM_REG ones included (their slot is reserved)
        self.assertEqual([m[n] for n in ("offsets", "entity_data", "current_entity", "base_x", "result", "attempt")],
                         [85, 86, 87, 88, 89, 90])

    def test_aggregates_take_no_pseudo(self):
        text = A_TEXT.replace("    u16 *offsets;", "    Copy12 scratch;\n    s32 arr[3];\n    u16 *offsets;")
        m = A.decl_pseudos(text, 76)["map"]
        self.assertNotIn("scratch", m)
        self.assertNotIn("arr", m)
        self.assertEqual(m["offsets"], 85)

    def test_declarators(self):
        self.assertEqual([(n, t, s, a) for n, t, s, a in A._declarators("register s32 **table_slot")],
                         [("table_slot", ["s32"], 2, False)])
        self.assertEqual([n for n, _, _, _ in A._declarators("u16 base_x, base_y")], ["base_x", "base_y"])


class Levers(unittest.TestCase):
    def test_lever_a_drops_the_copy_and_renames(self):
        got = dict(M.lever_a(A_TEXT))
        self.assertIn("a:current_entity<-entity", got)
        t = got["a:current_entity<-entity"]
        self.assertNotIn("current_entity", t)
        self.assertNotIn("void *current_entity;", t)
        self.assertIn("entity_data = *(void **)((s8 *)entity - 0x14);", t)
        self.assertIn("g(entity, base_x", t)
        self.assertIn("a:base_x<-x", got)                       # the same shape on the u16 formal

    def test_lever_a_refusals(self):
        # the formal is written: the copy is not redundant
        t = A_TEXT.replace("    base_x = x;", "    base_x = x;\n    entity = 0;")
        self.assertNotIn("a:current_entity<-entity", dict(M.lever_a(t)))
        # the local is written with something else
        t = A_TEXT.replace("            current_entity = entity;", "            current_entity = other;")
        self.assertNotIn("a:current_entity<-entity", dict(M.lever_a(t)))
        # a narrowing copy converts, so it is not a plain copy
        t = A_TEXT.replace("    void *current_entity;", "    s8 *current_entity;")
        self.assertNotIn("a:current_entity<-entity", dict(M.lever_a(t)))

    def test_lever_b_splits_the_second_meaning(self):
        got = dict(M.lever_b(B_TEXT, []))
        self.assertIn("b:record@0:keep:last", got)
        t = got["b:record@0:keep:last"]
        self.assertIn("record_b = (void *)3;", t)
        self.assertIn("record_b = (void *)m(record);", t)       # the RHS still reads the formal
        self.assertIn("[(s32)record_b]", t)
        self.assertIn("k(group_id, record)", t)                 # uses before the split are untouched
        self.assertIn("void *record_b;", t)
        cast = got["b:record@0:cast:last"]                       # the use's type, both casts dropped
        self.assertIn("s32 record_b;", cast)
        self.assertIn("record_b = 3;", cast)
        self.assertIn("record_b = m(record);", cast)
        self.assertIn("[record_b]", cast)

    def test_lever_b_refusals(self):
        # one assignment only
        self.assertEqual(M.lever_b(B_TEXT.replace("            record = (void *)3;", "            q = 3;"), []), [])
        # a use between the region's assignments cannot be attributed
        t = B_TEXT.replace("        } else {", "        } else if (p(record)) {")
        self.assertNotIn("b:record@0:keep:last", dict(M.lever_b(t, [])))

    def test_lever_d_retypes_around_the_pin(self):
        labels = [l for l, _ in M.lever_d(B_TEXT, [])]
        self.assertIn("d:table_index:s32->s16", labels)
        self.assertIn("d:param group_id:s32->u16", labels)
        self.assertNotIn("d:table_index:s32->s32", labels)
        t = dict(M.lever_d(B_TEXT, []))["d:table_index:s32->s16"]
        self.assertIn('register s16 table_index ASM_REG("$16");', t)


class Eligibility(unittest.TestCase):
    ROW = {"cfg": "2.7.2-cdk-G0", "c_path": "f.c", "id": "x/f"}

    def test_eligible(self):
        self.assertIsNone(M.T.eligible(A_TEXT, self.ROW, {}))
        self.assertIsNone(M.T.eligible(B_TEXT, self.ROW, {}))

    def test_refusals(self):
        self.assertEqual(M.T.eligible(A_TEXT.replace('ASM_REG("$19")', 'ASM_REG("$2")').replace('ASM_REG("$18")', 'ASM_REG("$3")'),
                                      self.ROW, {}), "no callee-saved ASM_REG pin")
        self.assertEqual(M.T.eligible("s32 f(void) { return 0; }\n", self.ROW, {}), "no pins")
        self.assertEqual(M.T.eligible(NO_LEVER, self.ROW, {}), "no (a)/(b)/(d) lever candidate near the pin")
        self.assertEqual(M.T.eligible(B_TEXT, dict(self.ROW, cfg="2.9.9-G0"), {}),
                         "cell has no FIRST_PSEUDO_REGISTER in the model")

    def test_candidates_erase_the_pins(self):
        for label, cand in M.candidates(B_TEXT):
            self.assertNotIn("ASM_REG", cand)
            self.assertNotIn("ASM_KEEP", cand)


class Population(unittest.TestCase):
    """The APPEARS test, on synthetic dump readings."""
    @staticmethod
    def rd(order, disp, calls=1):
        return {"order": order, "disp": disp,
                "stats": {p: {"n_refs": 4, "live_length": 20, "calls_crossed": calls} for p in order}}

    def test_order_site(self):
        p = self.rd([81, 80], {81: 17, 80: 18})
        e = self.rd([81, 82, 80], {81: 16, 82: 17, 80: 18})
        ok, why = M.is_order_site(p, e, [("table_index", 16, None)])
        self.assertTrue(ok, why)

    def test_same_allocno_count_is_a_different_family(self):
        p = self.rd([82, 83], {82: 6, 83: 2})
        e = self.rd([82, 83], {82: 2, 83: 2})
        ok, why = M.is_order_site(p, e, [("source", 16, None)])
        self.assertFalse(ok)
        self.assertIn("not a missing-allocno site", why)

    def test_argument_registers_are_a_preference_family(self):
        p = self.rd([87, 84], {87: 4, 84: 7}, calls=0)
        e = self.rd([87, 84, 92], {87: 4, 84: 5, 92: 6}, calls=0)
        ok, why = M.is_order_site(p, e, [("count", 6, None)])
        self.assertFalse(ok)
        self.assertTrue("permutation" in why or "cross no call" in why)


if __name__ == "__main__":
    unittest.main()
