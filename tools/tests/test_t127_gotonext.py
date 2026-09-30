import sys, unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "xform"))
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from t127_gotonext import rewrite, sites


def rw(t):
    return rewrite(t, range(len(sites(t))))


class GotoNext(unittest.TestCase):
    def test_label_removed_when_unused(self):
        self.assertEqual(rw("    y();\n    goto L;\nL:\n    z();\n"), "    y();\n    z();\n")

    def test_label_kept_when_other_goto(self):
        t = "    if (x) {\n        goto L;\n    }\n    goto L;\n\nL:\n    z();\n"
        self.assertEqual(rw(t), "    if (x) {\n        goto L;\n    }\nL:\n    z();\n")

    def test_other_label_untouched(self):
        t = "    goto L;\nM:\n    z();\nL:\n    w();\n"
        self.assertEqual(rw(t), t)

    def test_label_array_keeps_label(self):
        t = "    static void *tab[] = { &&L };\n    goto L;\nL:\n    z();\n"
        self.assertEqual(rw(t), "    static void *tab[] = { &&L };\nL:\n    z();\n")


if __name__ == "__main__":
    unittest.main()
