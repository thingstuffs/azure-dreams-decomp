"""T84: definition parsing, copy detection and the narrowed variants are textual; the screen and `vf` are not exercised."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t84_narrowparams as M  # noqa: E402

T = '''#include "common.h"
extern void f(Rec *parent, s32 state, s16 pair, s32 offset_x, s32 offset_y, s32 offset_z);

/* comment with f(x) */
void f(Rec *parent, s32 state, s16 pair, s32 offset_x, s32 offset_y,
       s32 offset_z)
{
    register s32 saved_y ASM_REG("$19") = offset_y;   /* pin note */
    register s32 saved_z ASM_REG("$20") = offset_z;
    void *e;

    e = g(0x211, parent);
    if (e != NULL) {
        h(e, offset_x + 1, saved_y, saved_z);
    }
}
'''


class Narrow(unittest.TestCase):
    def test_parse(self):
        defs = M.definitions(T)
        self.assertEqual([d[0] for d in defs], ["f"])
        self.assertEqual([p for _, p, _, _ in defs[0][2]], ["parent", "state", "pair", "offset_x", "offset_y", "offset_z"])
        sites = M.sites_in(T)
        self.assertEqual([(l, p) for l, p, _ in sites[0][2]], [("saved_y", "offset_y"), ("saved_z", "offset_z")])

    def test_candidates(self):
        cands = {label: t for label, t, _ in M.candidates(T)}
        self.assertIn("f:prev+pinned:s16", cands)
        t = cands["f:prev+pinned:s16"]
        self.assertIn("s16 offset_x, s16 offset_y,\n       s16 offset_z)", t)          # the multi-line definition
        self.assertIn("extern void f(Rec *parent, s32 state, s16 pair, s16 offset_x, s16 offset_y, s16 offset_z);", t)
        self.assertNotIn("saved_y", t); self.assertIn("h(e, offset_x + 1, offset_y, offset_z);", t)
        self.assertIn("s32 state", cands["f:pinned:u16"])                                # untouched outside the group
        self.assertIn("u16 offset_y, u16 offset_z", cands["f:pinned:u16"].replace("\n       ", " "))


if __name__ == "__main__":
    unittest.main()
