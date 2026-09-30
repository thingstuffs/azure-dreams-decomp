import sys, unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "xform"))
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import t129_defarity as T


class Trim(unittest.TestCase):
    def setUp(self):
        T._DEFS = {"func_80001000": "void *p, s16 a", "func_80002000": ""}

    def test_trims_call_and_prototype(self):
        t = "extern void func_80001000(void *, u8, s32);\nvoid f(void) {\n    func_80001000(p, x, 0);\n}\n"
        n, names = T.trim(t)
        self.assertEqual(names, {"func_80001000"})
        self.assertIn("extern void func_80001000(void *, u8);", n)
        self.assertIn("func_80001000(p, x);", n)

    def test_zero_arity(self):
        n, _ = T.trim("extern s32 func_80002000(s32);\ns32 g(void) {\n    return func_80002000(k);\n}\n")
        self.assertIn("func_80002000(void);", n)
        self.assertIn("return func_80002000();", n)

    def test_side_effect_argument_kept(self):
        t = "void f(void) {\n    func_80001000(p, x, i++);\n}\n"
        self.assertEqual(T.trim(t)[0], t)

    def test_definition_untouched(self):
        t = "void func_80001000(void *p, s16 a, s32 extra) {\n}\n"
        self.assertEqual(T.trim(t)[0], t)


if __name__ == "__main__":
    unittest.main()
