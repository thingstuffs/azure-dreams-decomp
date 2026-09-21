"""T98: the formal retype and the pin plans are textual; the cc1 screen and `vf` are not run."""
import os, re, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t98_paramcell as M  # noqa: E402
from pin_census import sites_of, unscored_text  # noqa: E402

TWIN = '''#include "common.h"
extern u8 D_80083498[];
extern void *func_8003FD64(s32 kind, void *data);
extern void *spawn(s32, s8, s8, s16);

void *spawn(s32 flags, s8 pos_x, s8 pos_y, s16 value)
{
    void *obj;
    register s32 object_type ASM_REG("$4");
    register void *object_pool ASM_REG("$5");
    s8 saved_x;
    s16 saved_value;

    object_type = 0x112;
    ASM_USE_NV(object_type);
    saved_x = pos_x;
    saved_value = value;
    object_pool = D_80083498;
    ASM_USE2_NV(saved_value, object_pool);
    obj = func_8003FD64(object_type, object_pool);
    *(s8 *)obj = saved_x;
    ASM_KEEP(saved_x);
    *(s16 *)((u8 *)obj + 4) = pos_y;
    return obj;
}
'''

NO_FORMAL = '''#include "common.h"
void h(void)
{
    s32 v;
    v = 1;
    ASM_KEEP(v);
    *(s32 *)0x80010000 = v;
}
'''

POINTERS = '''#include "common.h"
void p(void *a, void *b)
{
    register void *c ASM_REG("$4");
    c = a;
    ASM_KEEP(c);
    *(void **)b = c;
}
'''


class TestDetection(unittest.TestCase):
    def test_twin_is_eligible_and_reaches_both_formals(self):
        self.assertIsNone(M.T.eligible(TWIN, None, {}))
        found = M.pinned_params(TWIN)
        self.assertEqual(len(found), 1)
        fname, params, _body, reach = found[0]
        self.assertEqual(fname, "spawn")
        self.assertEqual([p[0] for p in params], ["flags", "pos_x", "pos_y", "value"])
        # `pos_x` is copied into the pinned ASM_USE2 group's neighbour, `value` into saved_value
        self.assertIn(3, reach)

    def test_function_without_a_formal_refuses(self):
        self.assertEqual(M.T.eligible(NO_FORMAL, None, {}),
                         "no pinned function with a scalar integer formal")

    def test_pointer_formals_are_not_scalar(self):
        self.assertEqual(M.T.eligible(POINTERS, None, {}),
                         "no pinned function with a scalar integer formal")

    def test_copies_of_finds_the_entry_copy(self):
        _n, _p, (b0, b1), _r = M.pinned_params(TWIN)[0]
        self.assertEqual(M.copies_of(TWIN, "pos_x", b0, b1), {"saved_x"})
        self.assertEqual(M.copies_of(TWIN, "value", b0, b1), {"saved_value"})


class TestRetype(unittest.TestCase):
    def test_every_declaration_of_the_function_changes(self):
        _n, params, _b, _r = M.pinned_params(TWIN)[0]
        out = M.retype(TWIN, "spawn", params, {2: "s16"})
        self.assertIn("extern void *spawn(s32, s8, s16, s16);", out)
        self.assertIn("void *spawn(s32 flags, s8 pos_x, s16 pos_y, s16 value)", out)
        self.assertNotIn("s8 pos_y", out)

    def test_other_formals_are_untouched(self):
        _n, params, _b, _r = M.pinned_params(TWIN)[0]
        out = M.retype(TWIN, "spawn", params, {2: "s16"})
        self.assertEqual(out.count("s8 pos_x"), 1)
        self.assertEqual(out.count("s8,"), 1)          # only pos_x is left in the bare type list


class TestCandidates(unittest.TestCase):
    def setUp(self):
        self.cands = M.candidates(TWIN)
        self.labels = [c[0] for c in self.cands]

    def test_the_entry_plan_takes_the_allocation_group(self):
        hit = [t for lab, t in self.cands
               if lab in ("spawn:pos_y=s16:precall", "spawn:pos_y=s16:callargs")]
        self.assertTrue(hit)
        t = hit[0]
        self.assertIn("s16 pos_y", t)
        self.assertIn("s32 object_type;", t)           # de-registered
        self.assertIn("void *object_pool;", t)
        self.assertNotIn("ASM_USE_NV", t)
        self.assertNotIn("ASM_USE2_NV", t)
        self.assertIn("ASM_KEEP(saved_x);", t)         # the pin after the call stays

    def test_every_candidate_removes_pins_and_keeps_the_unscored_text(self):
        n0, sig = len(sites_of(TWIN)), unscored_text(TWIN)
        for lab, t in self.cands:
            self.assertLess(len(sites_of(t)), n0, lab)
            self.assertEqual(unscored_text(t), sig, lab)

    def test_the_menu_offers_both_directions_and_a_group(self):
        self.assertIn("spawn:pos_y=s16:all", self.labels)
        self.assertIn("spawn:value=s8:all", self.labels)
        self.assertTrue(any(l.startswith("spawn:all=s16") for l in self.labels))
        self.assertTrue(all(":flags=s32" not in l for l in self.labels))   # never its own width

    def test_candidates_are_bounded(self):
        self.assertLessEqual(len(self.cands), M.MAX_CANDS)


if __name__ == "__main__":
    unittest.main()
