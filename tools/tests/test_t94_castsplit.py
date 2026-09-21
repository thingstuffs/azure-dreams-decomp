"""T94: statement splitting and the sign-extension merge are textual; the screen and `vf` are not run."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t94_castsplit as M  # noqa: E402
from pin_census import sites_of  # noqa: E402

T = '''#include "common.h"
void f(void *effect, s32 *out) {
    s32 impact_position;
    s32 table_index;
    s32 coord_base;
    s32 collision_coord;
    s32 map_index;
    s32 tile;
    s32 untouched;

    impact_position = func_80069EF8() & 0xF;
    ASM_KEEP(impact_position);
    impact_position = (s16)(impact_position - 8);

    ASM_KEEP_NV(table_index);
    table_index = (table_index + 0x100) >> 8;

    ASM_KEEP_NV(collision_coord);
    coord_base = collision_coord + 0x20;

    ASM_KEEP(tile);
    map_index = tile / 2;


    untouched = (s16)(untouched - 8);
    out[0] = impact_position + table_index + coord_base + map_index + untouched;
}
'''

SIGNEXT = '''#include "common.h"
void g(void *actor, s32 *out) {
    u32 global_flags;
    s32 state_index;
    void *actor_arg;

    global_flags = (*(u8 *)((u8 *)actor + 0x6D));
    global_flags <<= 24;
    ASM_KEEP(actor_arg);
    state_index = (s32)global_flags >> 24;
    out[0] = state_index;
}
'''


class Sites(unittest.TestCase):
    def test_every_shape_is_found(self):
        got = {(s[1], "|".join(x.strip() for x in s[3])) for s in M.sites(T)}
        self.assertIn(("cast", "impact_position -= 8;|impact_position = (s16)impact_position;"), got)
        self.assertIn(("two-op", "table_index += 0x100;|table_index >>= 8;"), got)
        self.assertIn(("insource", "collision_coord += 0x20;|coord_base = collision_coord;"), got)
        self.assertIn(("half", "map_index = tile + ((u32)tile >> 31);|map_index >>= 1;"), got)

    def test_a_statement_far_from_every_pin_is_not_a_site(self):
        far = T.replace("    untouched = (s16)(untouched - 8);\n", "")
        far = far.replace("    out[0] =", "\n\n\n    untouched = (s16)(untouched - 8);\n    out[0] =")
        self.assertFalse([s for s in M.sites(far) if "untouched" in "".join(s[3])])

    def test_signext_merge(self):
        ss = M.sites(SIGNEXT)
        self.assertEqual([s[1] for s in ss], ["signext"])
        i, label, span, new = ss[0]
        self.assertEqual(span, (i, i + 2))                       # the shift pair and the line between
        self.assertEqual([x.strip() for x in new],
                         ["ASM_KEEP(actor_arg);", "state_index = (s8)(global_flags + 0);"])

    def test_refusals(self):
        self.assertEqual(M.T.eligible('#include "common.h"\nvoid h(void) { s32 a; a = 1; }\n', None, {}),
                         "no pins")
        self.assertIsNone(M.T.eligible(T, None, {}))


class Candidates(unittest.TestCase):
    def test_each_candidate_drops_a_pin_and_keeps_the_rest(self):
        cands = M.candidates(T)
        self.assertTrue(cands)
        for label, new in cands:
            self.assertLess(len(sites_of(new)), len(sites_of(T)))
        by = dict(cands)
        one = next(v for k, v in by.items() if k.startswith("cast@") and k.endswith(":n1"))
        self.assertIn("impact_position -= 8;", one)
        self.assertIn("impact_position = (s16)impact_position;", one)
        self.assertNotIn("ASM_KEEP(impact_position);", one)

    def test_half_expansion(self):
        new = next(v for k, v in M.candidates(T) if k.startswith("half@") and k.endswith(":n1"))
        self.assertIn("map_index = tile + ((u32)tile >> 31);", new)
        self.assertIn("map_index >>= 1;", new)


if __name__ == "__main__":
    unittest.main()
