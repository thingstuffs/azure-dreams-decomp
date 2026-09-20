"""T80: site detection, purity and the statement move are textual; the screen and `vf` are not exercised."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t80_derivecall as M  # noqa: E402

T = '''#include "common.h"
void f(s32 n, u8 *base) {
    void *object;
    register S_3 *object_state ASM_REG("$19");
    u8 *page_ptr;
    u8 *other;
    s32 taken;
    s32 count;
    u8 *deref;
    u8 *fromcall;

    object = g(n, &taken);
    h(object, &D_80045340);
    other = ((S_1 *)object)->unk_0C;
    object_state = object + 0x20;
    page_ptr = (u8 *)&D_80083160;
    deref = ((S_1 *)object)->unk_10;
    count = taken + 1;
    fromcall = base + n;
}
'''

CALLEE = '''#include "common.h"
void f(u8 *base, s32 n) {
    u8 *p;
    s32 v;

    if (n)
        k(base);
    p = base + 4;
    for (v = 0; v < n; v++) {
        k(base);
        p = base + 8;
    }
    q(p);
}
'''

NAMED = '''#include "common.h"
void f(u8 *base, s32 n) {
    u8 *p;
    u8 *r;

    k(p, n);
    p = base + 4;
    m(n);
    r = base + 8;
    n = 0;
}
'''

MERGE = '''#include "common.h"
void f(s16 raw, void *ot) {
    s32 call_param;
    u16 wide;
    void *call_pos;

    call_pos = ot;
    call_param = (s32)((u32)raw << 16);
    ASM_KEEP_NV(call_pos);
    wide = raw;
    call_param >>= 16;
    j(call_pos, call_param);
}
'''


class Purity(unittest.TestCase):
    def test_pure(self):
        loc, taken = {"base", "n", "object"}, {"taken"}
        self.assertEqual(M.pure_expr("object + 0x20", loc, taken), {"object"})
        self.assertEqual(M.pure_expr("(u8 *)&D_80083160", loc, taken), set())
        self.assertEqual(M.pure_expr("(S_3 *)base", loc, taken), {"base"})
        self.assertIsNone(M.pure_expr("((S_1 *)object)->unk_0C", loc, taken))   # a dereference
        self.assertIsNone(M.pure_expr("g(object)", loc, taken))                 # a call
        self.assertIsNone(M.pure_expr("base[n]", loc, taken))                   # a subscript
        self.assertIsNone(M.pure_expr("taken + 1", loc, taken))                 # an address-taken local
        self.assertIsNone(M.pure_expr("D_80083160 + 1", loc, taken))            # a symbol READ, not its address
        self.assertIsNone(M.pure_expr("n & D_80083160", loc, taken))            # a BINARY &: still a read
        self.assertEqual(M.pure_expr("base + (s32)&D_1234", loc, taken), {"base"})

    def test_written_names(self):
        self.assertEqual(M.written_names("x = f(a, b);"), {"x"})
        self.assertEqual(M.written_names("p += 2;"), {"p"})
        self.assertEqual(M.written_names("q->n = 1;"), set())


class Sites(unittest.TestCase):
    def test_sites(self):
        sites = M.sites_in(T)
        self.assertEqual(len(sites), 2)                                # `g(...)` and `h(...)`
        assigns = {a[1]: a for s in sites for a in s["assigns"]}
        self.assertIn("object_state", assigns)                         # two statements after the call
        self.assertIn("page_ptr", assigns)                             # three statements after it
        self.assertNotIn("deref", assigns)                             # the expression dereferences
        self.assertNotIn("count", assigns)                             # `taken` is address-taken
        self.assertIn("fromcall", assigns)                             # two parameters, neither written
        self.assertEqual(assigns["object_state"][3], {"object"})

    def test_eligible(self):
        self.assertIsNone(M.T.eligible(T, {}, {}))                     # the ASM_REG names object_state
        self.assertEqual(M.T.eligible(CALLEE, {}, {}), "no pins")

    def test_sole_body_and_move(self):
        sites = {s["i"]: s for s in M.sites_in(T)}
        site = [s for s in sites.values() if "h(object" in T.split("\n")[s["i"]]][0]
        a = [x for x in site["assigns"] if x[1] == "object_state"][0]
        new, dest = M.moved_text(T, site, a[0], 0)
        lines = [l.strip() for l in new.split("\n")]
        self.assertEqual(lines[dest], "object_state = object + 0x20;")
        self.assertEqual(lines[dest + 1], "h(object, &D_80045340);")
        # one statement further up crosses `object = g(n, &taken);`, which writes the operand
        self.assertIsNone(M.moved_text(T, site, a[0], 1))

    def test_unbraced_body_refused(self):
        # the sole-body `k(base);` of the unbraced `if` is never a site; the loop's call is
        self.assertEqual([a[1] for s in M.sites_in(CALLEE) for a in s["assigns"]], ["p"])
        self.assertEqual([s["i"] + 1 for s in M.sites_in(CALLEE)], [10])
        ml = CALLEE.split("\n")
        self.assertTrue(M.sole_body_above(ml, 6, 1))                   # the `k(base);` under `if (n)`
        self.assertFalse(M.sole_body_above(ml, 10, 1))                 # the call inside the loop body

    def test_named_or_written_refused(self):
        assigns = [a[1] for s in M.sites_in(NAMED) for a in s["assigns"]]
        self.assertNotIn("p", assigns)                                 # the call statement names p
        self.assertIn("r", assigns)


class Merge(unittest.TestCase):
    def test_merge_pair(self):
        out = M.merge_pairs(MERGE)
        self.assertEqual(len(out), 1)
        self.assertIn("    call_param = (s32)((u32)raw << 16) >> 16;", out[0][1])
        self.assertNotIn("call_param >>= 16;", out[0][1])
        self.assertIn("ASM_KEEP_NV(call_pos);", out[0][1])              # the pin in between is untouched

    def test_merge_needs_the_declared_type(self):
        bad = MERGE.replace("(s32)((u32)raw << 16)", "(u32)((u32)raw << 16)")
        self.assertEqual(M.merge_pairs(bad), [])                        # the cast is not `call_param`'s type
        bad2 = MERGE.replace("    wide = raw;", "    call_param = 0;")
        self.assertEqual(M.merge_pairs(bad2), [])                       # the name is written in between


if __name__ == "__main__":
    unittest.main()
