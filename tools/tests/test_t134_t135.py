"""T134 / T135 unit tests on synthetic texts: pure text transforms, no compile, no scorer."""
import sys
import unittest
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
for sub in (ROOT / "tools/xform", ROOT / "tools"):
    sys.path.insert(0, str(sub))

import xform.t134_givrecover as A                                        # noqa: E402
import xform.t135_narrowparam as B                                       # noqa: E402
from pin_census import sites_of, unscored_text                           # noqa: E402

GIV = '''void *f(s16 x) {
    s32 angle;
    s32 i;
    register s16 pos_x ASM_REG("$22");
    void *obj;

    pos_x = x;
    i = 0;
    angle = i;
    do {
        obj = g(0x212);
        h(obj, angle);
        k(angle | 3, pos_x);
        i += 1;
        angle += 0x80;
    } while (i < 0x20);
    return obj;
}
'''

GIV_ZERO_FOR = '''void f(void) {
    s32 i;
    s32 off = 0;
    register s32 keep ASM_REG("$17");

    for (i = 0; i < 8; i++) {
        keep = g(off);
        off += 8;
    }
}
'''

NOT_GIV_READ_AFTER = '''void f(void) {
    s32 i;
    s32 off;
    i = 0;
    off = 0;
    do {
        i += 1;
        off += 4;
        g(off);
    } while (i < 8);
}
'''

NOT_GIV_TWO_WRITES = '''void f(void) {
    s32 i;
    s32 off;
    i = 0;
    off = 0;
    do {
        g(off);
        off = h();
        i += 1;
        off += 4;
    } while (i < 8);
}
'''

NONZERO_START = '''void f(void) {
    s32 i;
    s32 off;
    i = 5;
    off = 0;
    do {
        g(off);
        i += 1;
        off += 4;
    } while (i < 8);
}
'''

NARROW = '''extern s32 g(s32, s32);
extern s32 f(s32 a, s32 b);
s32 f(s32 a, s32 b) {
    register s32 raw_a ASM_REG("$6") = a;
    s32 held;
    s32 r;

    held = b;
    r = g(raw_a & 0xFFFF, held & 0xFFFF);
    return r + (s16)a;
}
'''


class GivRecover(unittest.TestCase):
    def test_detects_counter_variable(self):
        self.assertEqual([g[:5] for g in A.givs(GIV)], [("f", "angle", "i", "0x80", 0)])

    def test_rewrite_uses_and_drops_variable(self):
        (label, t, fname), = A.giv_bases(GIV)
        self.assertIn("h(obj, i * 0x80);", t)
        self.assertIn("k((i * 0x80) | 3, pos_x);", t)
        self.assertNotIn("angle", t)
        self.assertEqual(unscored_text(t), unscored_text(GIV))

    def test_for_header_and_zero_init(self):
        (label, t, _), = A.giv_bases(GIV_ZERO_FOR)
        self.assertIn("keep = g(i * 8);", t)
        self.assertNotIn("off", t)

    def test_pin_named_variable_is_erased(self):
        src = GIV.replace("s32 angle;", 'register s32 angle ASM_REG("$18");')
        n0 = len(sites_of(src))
        (label, t, _), = A.giv_bases(src)
        self.assertEqual(len(sites_of(t)), n0 - 1)
        self.assertNotIn("angle", t)

    def test_refusals(self):
        for src in (NOT_GIV_READ_AFTER, NOT_GIV_TWO_WRITES):
            self.assertEqual(A.givs(src), [], src)

    def test_nonzero_counter_start_folds_the_offset(self):
        (label, t, _), = A.giv_bases(NONZERO_START)
        self.assertIn("g(i * 4 - 20);", t)

    def test_stack_offers_pin_erasures(self):
        c = A.stack(GIV, len(sites_of(GIV)))
        self.assertTrue(c)
        self.assertTrue(all(len(sites_of(t)) < len(sites_of(GIV)) for _, t in c))

    def test_cfg_menu(self):
        row = {"cfg": "2.7.2-cdk-G0 -fno-schedule-insns"}
        self.assertEqual(A.cfg_menu(row), [None, "2.7.2-cdk-G0", ])


class NarrowParam(unittest.TestCase):
    def test_analysis(self):
        (fname, params, per, cp), = B.analyses(NARROW)
        self.assertEqual(fname, "f")
        self.assertEqual(per["a"], {"s16", "u16"})
        self.assertEqual(per["b"], {"u16"})
        self.assertEqual({k: v[0] for k, v in cp.items()}, {"raw_a": "a", "held": "b"})

    def test_bases_retype_and_drop(self):
        outs = {label.split(":", 2)[2]: t for label, t, _ in B.bases(NARROW)}
        t = next(v for k, v in outs.items() if k.endswith("drop") and k.startswith("ev:own"))
        self.assertIn("s32 f(s16 a, u16 b) {", t)
        self.assertIn("extern s32 f(s16 a, u16 b);", t)
        self.assertNotIn("raw_a", t)
        self.assertNotIn("held", t)
        self.assertIn("g(a & 0xFFFF, b & 0xFFFF)", t)

    def test_callee_prototype_variant(self):
        t = next(t for label, t, _ in B.bases(NARROW) if label.endswith("drop+u16proto"))
        self.assertIn("extern s32 g(u16, u16);", t)
        self.assertIn("g(a, b)", t)

    def test_nocast_variant(self):
        t = next(t for label, t, _ in B.bases(NARROW) if label.endswith("drop+nocast"))
        self.assertIn("return r + a;", t)

    def test_stack_pins_fall(self):
        n0 = len(sites_of(NARROW))
        c = B.stack(NARROW, n0)
        self.assertTrue(c)
        self.assertTrue(all(len(sites_of(t)) < n0 for _, t, _ in c))

    def test_pinned_copy_without_narrow_use(self):
        src = 'void f(void *p, s32 x) {\n    s32 saved_x = x;\n    g(p);\n    ASM_KEEP(saved_x);\n    h(saved_x);\n}\n'
        (fname, params, per, cp), = B.analyses(src)
        self.assertEqual(set(per), {"x"})

    def test_no_evidence_no_analysis(self):
        self.assertEqual(B.analyses("void f(s32 x) {\n    g(x);\n}\n"), [])


if __name__ == "__main__":
    unittest.main()
