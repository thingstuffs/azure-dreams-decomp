import sys, unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "xform"))
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from t126_ppcollapse import collapse_all, mips_blocks, take_portable, nblocks


class Collapse(unittest.TestCase):
    def test_same_arms(self):
        t = "a;\n#ifdef __mips__\n    int x;\n#else\n    int  x; /* c */\n#endif\nb;"
        self.assertEqual(collapse_all(t), "a;\n    int x;\nb;")

    def test_empty(self):
        self.assertEqual(collapse_all("a;\n#ifdef __mips__\n\n#endif\nb;"), "a;\nb;")

    def test_nested_then_outer(self):
        t = "#ifdef NON_MATCHING\n#ifdef __mips__\n#endif\nx;\n#else\nx;\n#endif"
        self.assertEqual(collapse_all(t), "x;")

    def test_different_arms_stay(self):
        t = "#ifdef __mips__\nx;\n#else\ny;\n#endif"
        self.assertEqual(collapse_all(t), t)

    def test_if_zero_and_elif_untouched(self):
        t = "#if 0\n#else\n#endif\n#ifdef A\nx;\n#elif B\nx;\n#else\nx;\n#endif"
        self.assertEqual(collapse_all(t), t)


class Portable(unittest.TestCase):
    def test_ifdef_takes_else(self):
        t = "a;\n#ifdef __mips__\nasm();\n#else\nplain;\n#endif\nb;"
        self.assertEqual(take_portable(t, range(len(mips_blocks(t.split("\n"))))), "a;\nplain;\nb;")

    def test_ifndef_takes_first(self):
        t = "#ifndef __mips__\nplain;\n#else\nasm();\n#endif"
        self.assertEqual(take_portable(t, [0]), "plain;")

    def test_nested_not_offered(self):
        t = "#ifdef NON_MATCHING\n#ifdef __mips__\nx;\n#else\ny;\n#endif\n#endif"
        self.assertEqual(mips_blocks(t.split("\n")), [])
        self.assertEqual(nblocks(t), 2)


if __name__ == "__main__":
    unittest.main()
