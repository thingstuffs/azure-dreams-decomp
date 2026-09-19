"""T74: operator scanning and chain splitting are textual; the screen and `vf` are not exercised."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t74_multiset as M  # noqa: E402

T = '''#include "common.h"
void f(s32 a, s32 b, s32 c, u8 *p, S *q) {
    s32 v;
    s32 w;
    s32 x;
    v = a + b + c;
    ASM_KEEP(v);
    w = (a - b) << 2;
    x = q->n - r;
    p[0] = v + w;
    p[1] = g(a) + b;
    v = v + a + b;
}
'''


class Chains(unittest.TestCase):
    def test_ops(self):
        self.assertEqual([o for _, o in M.top_ops("a + b + c")], ["+", "+"])
        self.assertEqual([o for _, o in M.top_ops("p->q - r")], ["-"])
        self.assertEqual([o for _, o in M.top_ops("a + -b")], ["+"])
        self.assertEqual([o for _, o in M.top_ops("(x - y) | (z << 2)")], ["|"])
        self.assertEqual([o for _, o in M.top_ops("a << 2")], ["<<"])
        self.assertEqual(M.top_ops("a * b"), [])

    def test_chains_and_splits(self):
        cs = {c[1]: c for c in M.chains(T)}
        self.assertEqual(cs["v"][2], "a"); self.assertEqual(cs["v"][3], [("+", "b"), ("+", "c")])
        self.assertEqual(cs["w"][2], "(a - b)"); self.assertEqual(cs["w"][3], [("<<", "2")])
        self.assertEqual(cs["x"][3], [("-", "r")])                       # the arrow is not an operator
        self.assertNotIn("p", cs)                                        # a store, not a local
        self.assertEqual([l for _, l in M.splits(cs["v"])], [["    v = a + b;", "    v += c;"], ["    v = a;", "    v += b;", "    v += c;"]])
        self.assertEqual([l for _, l in M.splits(cs["w"])], [["    w = (a - b);", "    w <<= 2;"]])

    def test_refusals(self):
        vs = [c[1] for c in M.chains(T)]
        self.assertEqual(vs.count("v"), 1)                               # `v = v + a + b` names v inside the chain: refused
        self.assertNotIn("p", vs)                                        # a call inside the chain: refused


if __name__ == "__main__":
    unittest.main()
