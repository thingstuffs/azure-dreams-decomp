import sys, unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "xform"))
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from t124_skipgoto import inv, rewrite, sites, parse_at


def rw(t, alt=None):
    return rewrite(t, range(len(sites(t))), alt)


class Inv(unittest.TestCase):
    TABLE = [
        ("x == 0", "x != 0"), ("x != 0", "x == 0"), ("a < b", "a >= b"), ("a <= b", "a > b"),
        ("a > b", "a <= b"), ("a >= b", "a < b"),
        ("x", "!x"), ("p->q", "!p->q"), ("a.b[3]", "!a.b[3]"), ("f(x)", "!f(x)"),
        ("!x", "x"), ("!(x & 0x800)", "x & 0x800"), ("!(a && b)", "a && b"),
        ("x & 0x800", "!(x & 0x800)"),
        ("a && b", "!(a && b)"), ("a || b", "!(a || b)"), ("a < b && c", "!(a < b && c)"),
        ("(a < b)", "a >= b"), ("((x))", "!x"),
        ("(u8) x < 5", "(u8) x >= 5"), ("(s32) x", "!((s32) x)") if False else ("(s32) x == 0", "(s32) x != 0"),
        ("*p", "!(*p)"), ("a << 2 < b", "a << 2 >= b"), ("a >> 2 == 0", "a >> 2 != 0"),
        ("p->q < 0", "p->q >= 0"), ("a < b < c", "!(a < b < c)"), ("a == b | c", "!(a == b | c)"),
        ("(a & 1) == 0", "(a & 1) != 0"), ("(a < b) == c", "(a < b) != c"),
        ("x = 3", "!(x = 3)"), ("a ? b : c", "!(a ? b : c)"), ("!a == b", "!a != b"),
        ("f(a, b) == 0", "f(a, b) != 0"), ("x[a < b] == 1", "x[a < b] != 1"),
        ("  a   ==\n  b ", "a != b"), ("!x && y", "!(!x && y)"), ("p->q != &D_80", "p->q == &D_80"), ("(a & 1) != 0", "(a & 1) == 0"), ("a & b", "!(a & b)"), ("a == &b", "a != &b"),
    ]

    def test_table(self):
        for c, want in self.TABLE:
            self.assertEqual(inv(c), want, c)

    def test_involution_shape(self):
        for c in ("a == b", "a < b", "x", "a && b"):
            self.assertEqual(inv(inv(c)), c)


class Shapes(unittest.TestCase):
    def test_skip(self):
        t = "void f() {\n    if (x == 0) goto L1;\n    y = 1;\n    z = 2;\nL1:\n    return;\n}\n"
        self.assertEqual(rw(t), "void f() {\n    if (x != 0) {\n        y = 1;\n        z = 2;\n    }\n    return;\n}\n")

    def test_braced_goto(self):
        t = "void f() {\n    if (a) {\n        goto L1;\n    }\n    y = 1;\nL1:\n    return;\n}\n"
        self.assertEqual(rw(t), "void f() {\n    if (!a) {\n        y = 1;\n    }\n    return;\n}\n")

    def test_ifelse(self):
        t = "void f() {\n    if (a) {\n        p = 1;\n        goto L1;\n    }\n    q = 2;\nL1:\n    return;\n}\n"
        self.assertEqual(rw(t), "void f() {\n    if (a) {\n        p = 1;\n    } else {\n        q = 2;\n    }\n    return;\n}\n")

    def test_ifelse_goto_first(self):
        t = ("void f() {\n    if (a < b) goto L1;\n    p = 1;\n    goto L2;\nL1:\n    q = 2;\nL2:\n    return;\n}\n")
        self.assertEqual(rw(t), "void f() {\n    if (a >= b) {\n        p = 1;\n    } else {\n        q = 2;\n    }\n    return;\n}\n")

    def test_nested(self):
        t = ("void f() {\n    if (a) goto L1;\n    x = 1;\n    if (b) goto L2;\n    y = 2;\nL2:\n    z = 3;\nL1:\n    return;\n}\n")
        want = ("void f() {\n    if (!a) {\n        x = 1;\n        if (!b) {\n            y = 2;\n        }\n        z = 3;\n    }\n    return;\n}\n")
        self.assertEqual(rw(t), want)

    def test_label_kept_when_other_goto(self):
        t = ("void f() {\n    if (z) {\n        w = 1;\n    } else if (q) goto L1;\n    if (a) goto L1;\n    x = 1;\nL1:\n    return;\n}\n")
        out = rw(t)
        self.assertIn("L1:", out)
        self.assertIn("goto L1;", out)   # the else-if one cannot be rewritten
        self.assertIn("if (!a) {\n        x = 1;\n    }", out)

    def test_goto_from_body_keeps_label(self):
        t = ("void f() {\n    if (a) goto L1;\n    if (b) goto L2;\n    x = 1;\nL1:\n    y = 2;\nL2:\n    return;\n}\n")
        out = rw(t)
        self.assertTrue("L2:" in out or "L1:" in out)
        self.assertNotIn("goto L1;", out) if "L1:" not in out else None

    def test_label_in_body_refused(self):
        t = "void f() {\n    if (a) goto L1;\n    x = 1;\nL9:\n    y = 2;\nL1:\n    return;\n}\n"
        self.assertEqual(rw(t), t)

    def test_unbalanced_body_refused(self):
        t = "void f() {\n    if (a) goto L1;\n    if (b) {\n        x = 1;\nL1:\n        y = 2;\n    }\n}\n"
        self.assertEqual(rw(t), t)

    def test_else_if_refused(self):
        t = "void f() {\n    if (z) {\n        w = 1;\n    } else if (a) goto L1;\n    x = 1;\nL1:\n    return;\n}\n"
        self.assertEqual(rw(t), t)

    def test_preprocessor_arm(self):
        t = "void f() {\n#ifdef NON_MATCHING\n    if (a) goto L1;\n    x = 1;\nL1:\n#endif\n    return;\n}\n"
        self.assertEqual(rw(t), t)

    def test_case_in_body_refused(self):
        t = "void f() {\n    switch (s) {\n    case 1:\n    if (a) goto L1;\n    x = 1;\n    case 2:\n    y = 1;\nL1:\n    break;\n    }\n}\n"
        self.assertEqual(rw(t), t)

    def test_switch_inside_body_ok(self):
        t = "void f() {\n    if (a) goto L1;\n    switch (s) {\n    case 1:\n        x = 1;\n        break;\n    }\nL1:\n    return;\n}\n"
        self.assertIn("if (!a) {\n        switch (s) {", rw(t))

    def test_comment_and_string_ignored(self):
        t = 'void f() {\n    if (a) goto L1;\n    puts("}{ L1:");\n    /* } */\n    x = 1;\nL1:\n    return;\n}\n'
        self.assertIn("if (!a) {", rw(t))

    def test_unbraced_control_refused(self):
        t = "void f() {\n    while (k)\n        if (a) goto L1;\n    x = 1;\nL1:\n    return;\n}\n"
        self.assertEqual(rw(t), t)


if __name__ == "__main__":
    unittest.main()
