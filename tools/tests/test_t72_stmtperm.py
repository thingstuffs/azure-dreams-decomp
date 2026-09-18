"""T72: statement parsing, the dependence order, the run around a pin and the rebuild are textual and
compiler-free; the listing screen and `vf` are stubbed."""
import os
import sys
import unittest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform"))
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t72_stmtperm as M  # noqa: E402
from pin_census import sites_of  # noqa: E402

PROBE = """#include "common.h"
extern s32 func_80024610(void *, void *, void *, s32, s32, s32 *, u8, s32);
extern s32 func_80064584();
extern s32 D_80012345;

s32 func_818B1334(void *source, u16 *target, void *context) {
    s32 circle_values[34];
    s16 radius;
    s32 entry_angle;
    s32 entry_index;
    u16 angle_offset;
    void *offset_cursor;
    void *source_arg;

    entry_index = 0;
    offset_cursor = source;
    do {
        radius = 0x20;
        func_80064584(entry_index << 0xA);
        source_arg = source;
        ASM_KEEP(source_arg);   /* UNRESOLVED C shape (pin) */
        angle_offset = *(u16 *)((u8 *)offset_cursor + 0x1A);
        offset_cursor += 2;
        entry_angle = entry_index << 0x11;
        entry_index += 1;
        func_80024610(source_arg, target, context, radius, (s32) (s16) (target[5] - angle_offset), circle_values, 0xFF, entry_angle >> 0x10);
    } while (entry_index < 8);
    return 0;
}
"""


def stmt(text, locals_=frozenset(), taken=frozenset()):
    return M.Stmt([text], 0, 0, set(locals_), set(taken))


class Parse(unittest.TestCase):
    def test_kinds(self):
        L = {"a", "b", "p", "i"}
        s = stmt("a = b + 1;", L)
        self.assertTrue(s.pure); self.assertEqual((s.w, s.r), ({"a"}, {"b"}))
        s = stmt("i++;", L)
        self.assertTrue(s.pure); self.assertEqual((s.w, s.r), ({"i"}, {"i"}))
        s = stmt("p = (u8 *)p + 2;", L)
        self.assertTrue(s.pure)
        s = stmt("a = p->x;", L)
        self.assertFalse(s.pure); self.assertTrue(s.memr); self.assertEqual(s.loads, {("p", "x")})
        s = stmt("((S *)p)->x = a;", L)
        self.assertTrue(s.memw); self.assertEqual(s.stores, {("p", "x")}); self.assertIn("a", s.r)
        s = stmt("a = f(b);", L)
        self.assertTrue(s.call); self.assertEqual(s.w, {"a"})
        s = stmt("a = D_80012345;", L)
        self.assertFalse(s.pure)                               # a global read may be written by a call
        s = stmt("a = &D_80012345;", L)
        self.assertTrue(s.pure)                                # an address constant
        s = stmt("a = b;", L, taken={"b"})
        self.assertFalse(s.pure)                               # address-taken locals live in memory

    def test_depends(self):
        L = {"a", "b", "c", "p", "q"}
        call = stmt("f(a);", L)
        self.assertFalse(M.depends(stmt("b = c + 1;", L), call))        # a pure statement crosses a call
        self.assertTrue(M.depends(stmt("a = c + 1;", L), call))          # unless the call reads its result
        self.assertTrue(M.depends(stmt("a = p->x;", L), call))           # a load never crosses a call
        self.assertFalse(M.depends(stmt("p->x = a;", L), stmt("p->y = b;", L)))   # different fields, one base
        self.assertTrue(M.depends(stmt("p->x = a;", L), stmt("p->x = b;", L)))
        self.assertTrue(M.depends(stmt("p->x = a;", L), stmt("q->y = b;", L)))    # different bases: conservative
        self.assertTrue(M.depends(stmt("p->x = a;", L), stmt("b = q->y;", L)))


class Runs(unittest.TestCase):
    def test_probe_run(self):
        rs = M.runs(PROBE)
        self.assertEqual(len(rs), 1)
        window, run = rs[0]
        self.assertEqual(len(window), 1)
        texts = [s.text for s in run]
        self.assertIn("func_80024610(source_arg, target, context, radius, (s32) (s16) (target[5] - angle_offset), circle_values, 0xFF, entry_angle >> 0x10)", texts)
        self.assertIn("radius = 0x20", texts)
        orders = list(M.orders(run))
        self.assertEqual(orders[0], tuple(range(len(run))))
        # the t71 order (both increments after the call) is among them
        i_call = texts.index([t for t in texts if t.startswith("func_80024610(")][0])
        i_inc = texts.index("entry_index += 1"); i_cur = texts.index("offset_cursor += 2")
        self.assertTrue(any(p.index(i_inc) > p.index(i_call) and p.index(i_cur) > p.index(i_call) for p in orders))
        # the load never crosses the call
        i_ld = texts.index("angle_offset = *(u16 *)((u8 *)offset_cursor + 0x1A)")
        self.assertTrue(all(p.index(i_ld) < p.index(i_call) for p in orders))

    def test_build_is_a_permutation_with_the_pin_gone(self):
        window, run = M.runs(PROBE)[0]
        perm = list(M.orders(run))[1]
        out = M.build(PROBE, run, perm, set(window))
        self.assertEqual(len(sites_of(out)), 0)
        keep = [l for l in PROBE.split("\n") if "ASM_KEEP" not in l]
        self.assertEqual(sorted(out.split("\n")), sorted(keep))
        self.assertNotEqual(out.split("\n"), keep)

    def test_apply_verified_with_stubs(self):
        want = None

        def fake_compile(row, text):
            # "retail" = the order with both increments after the call and no pin
            ls = [l.strip() for l in text.split("\n") if l.strip() and "ASM_KEEP" not in l]
            k = next(n for n, l in enumerate(ls) if l.startswith("func_80024610("))
            return ["ok"] if ls[k + 1] == "offset_cursor += 2;" and ls[k + 2] == "entry_index += 1;" else ["no", str(k)]
        old = M.screen.compile_s
        M.screen.compile_s = fake_compile
        try:
            new, info = M.T.apply_verified(PROBE, {"cfg": "2.7.2-cdk", "c_path": "x.c"}, {}, lambda c, cfg=None: {"exact": True})
        finally:
            M.screen.compile_s = old
        self.assertIsNotNone(new)
        self.assertEqual(info["pins_out"], 0)
        self.assertEqual(info["tried"], 1)


if __name__ == "__main__":
    unittest.main()
