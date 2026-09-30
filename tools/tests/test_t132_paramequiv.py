"""T132 unit tests on synthetic texts: pure text transforms, no compile, no scorer."""
import sys
import unittest
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
for sub in (ROOT / "tools/xform", ROOT / "tools"):
    sys.path.insert(0, str(sub))

import xform.t132_paramequiv as M                                        # noqa: E402
from pin_census import sites_of, unscored_text                           # noqa: E402

PROTO = 'void f(void *a_arg, void *b_arg)\n__attribute__((section(".text.f")));\n'

DIRECT = PROTO + '''void f(void *a_arg, void *b_arg)
{
    u8 *a = (u8 *)a_arg;
    u8 *b = (u8 *)b_arg;
    register u8 *c ASM_REG("$20");
    c = g(a);
    h(b, c);
}
'''

SPLIT = '''void f(void *effect, void *output)
{
    void *self = effect;
    void *t;
    ASM_KEEP(self);
    g(self);
    effect = h(self);
    k(effect, t);
}
'''

COPY = '''void f(u8 *node, s32 n)
{
    u8 *w;
    ASM_KEEP(node);
    w = node + n;
    g(node, w);
}
'''

PP = '''void f(void *a_arg)
{
    u8 *a = (u8 *)a_arg;
    ASM_KEEP(a);
#ifdef NON_MATCHING
    x = 1;
#else
    x = 2;
#endif
    g(a);
}
'''


class Direct(unittest.TestCase):
    def test_cast_copies_dropped_without_pins_on_them(self):
        bs = M.direct_bases(DIRECT)
        self.assertTrue(bs)
        label, t, fn = bs[0]
        self.assertIn("void f(u8 *a, u8 *b)", t)                     # definition retyped and renamed
        self.assertNotIn("u8 *a = (u8 *)a_arg;", t)
        self.assertEqual(t.count("void f(u8 *a, u8 *b)"), 2)         # the attribute prototype follows
        self.assertIn("ASM_REG", t)                                  # base keeps the pin on c

    def test_menu_erases_the_other_pin(self):
        cands, n0 = M.candidates(DIRECT)
        self.assertEqual(n0, 1)
        self.assertTrue(any("ASM_REG" not in t and "u8 *a, u8 *b" in t for _l, t in cands))
        self.assertTrue(all(len(sites_of(t)) < n0 for _l, t in cands))

    def test_prototype_sync_arity_mismatch_untouched(self):
        t = 'void f(int x)\n__attribute__((section("s")));\nvoid f(u8 *a, u8 *b)\n{\n}\n'
        self.assertEqual(M.sync_attr_protos(t, "f"), t)


class Split(unittest.TestCase):
    def test_reassigned_parameter_role_is_split(self):
        s = M.split_roles(SPLIT)
        self.assertTrue(s)
        _lab, t, p, q = s[0]
        self.assertIn("void *effect__role;", t)
        self.assertIn("effect__role = h(self);", t)
        self.assertIn("k(effect__role, t);", t)

    def test_role_split_then_direct_folds_the_copy_into_the_parameter(self):
        bs = M.direct_bases(SPLIT)
        self.assertTrue(bs)
        label, t, _fn = bs[0]
        self.assertTrue(label.startswith("split:"))
        self.assertIn("void f(void *self, void *output)", t)
        self.assertIn("effect = h(self);", t)
        self.assertNotIn("__role", t)
        self.assertNotIn("void *self = effect;", t)
        self.assertEqual(len(sites_of(t)), 0)

    def test_goto_above_the_reassignment_refuses(self):
        t = SPLIT.replace("    g(self);", "    if (n) goto out;\n    g(self);")
        self.assertEqual(M.split_roles(t), [])

    def test_read_of_parameter_before_copy_refuses(self):
        t = SPLIT.replace("    void *self = effect;\n", "    g(effect);\n    void *self = effect;\n")
        self.assertEqual(M.split_roles(t), [])


class Copy(unittest.TestCase):
    def test_pinned_parameter_becomes_a_local_copy(self):
        bs = M.copy_bases(COPY)
        self.assertTrue(bs)
        tops = [t for l, t, _f in bs if l.endswith("@top")]
        t = tops[0]
        self.assertIn("void f(u8 *node_arg, s32 n)", t)
        self.assertIn("u8 *node = node_arg;", t)
        self.assertNotIn("ASM_KEEP(node)", t)
        self.assertIn("w = node + n;", t)                            # body still reads the local

    def test_written_parameter_is_not_copied(self):
        t = COPY.replace("    g(node, w);", "    node = w;\n    g(node, w);")
        self.assertEqual(M.copy_bases(t), [])

    def test_unpinned_parameter_needs_T132_ALL(self):
        t = COPY.replace("    ASM_KEEP(node);\n", "    ASM_KEEP(w);\n")
        self.assertEqual(M.copy_bases(t), [])


class Shield(unittest.TestCase):
    def test_arm_inside_body_does_not_hide_the_row(self):
        bs = M.direct_bases(PP)
        self.assertTrue(bs)
        t = bs[0][1]
        self.assertIn("#ifdef NON_MATCHING", t)
        self.assertIn("#endif", t)
        self.assertEqual(unscored_text(t), unscored_text(t))
        self.assertIn("void f(u8 *a)", t)

    def test_arm_mentioning_the_name_is_refused(self):
        t = PP.replace("x = 1;", "x = a_arg;")
        self.assertEqual(M.direct_bases(t), [])


if __name__ == "__main__":
    unittest.main()
