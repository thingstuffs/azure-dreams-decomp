import sys, tempfile, unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import relink_lint as R


class RelinkLint(unittest.TestCase):
    def tree(self, files, allow=""):
        d = Path(tempfile.mkdtemp())
        for rel, text in files.items():
            p = d / rel; p.parent.mkdir(parents=True, exist_ok=True); p.write_text(text)
        (d / "config/lint").mkdir(parents=True, exist_ok=True)
        (d / R.ALLOW).write_text(allow)
        return d

    def test_clean_tree(self):
        self.assertEqual(R.problems(self.tree({"src/dungeon/a.c": "int f(void) { return 0; }\n"})), [])

    def test_new_define_refused(self):
        d = self.tree({"src/dungeon/a.c": "#define dungeonX func_8016B138\n"})
        self.assertIn("new relocation text (define)", R.problems(d)[0])

    def test_new_relink_file_refused(self):
        d = self.tree({"src/town/b.c": "/* Relink of matched town/func_1; x */\n"})
        self.assertIn("(relink)", R.problems(d)[0])

    def test_allowed_and_ratchet(self):
        files = {"src/dungeon/a.c": "/* Relink of matched dungeon/func_1; */\n#define x D_80012345\n"}
        d = self.tree(files, "src/dungeon/a.c\tdefine,relink\n")
        self.assertEqual(R.problems(d), [])
        (d / "src/dungeon/a.c").unlink()
        self.assertIn("stale", R.problems(d)[0])
        self.assertEqual(R.shrink(d), 1)
        self.assertEqual(R.problems(d), [])

    def test_shrink_never_adds(self):
        d = self.tree({"src/dungeon/a.c": "#define y func_80012345\n"})
        R.shrink(d)
        self.assertEqual(R.read_allow(d), {})
        self.assertTrue(R.problems(d))

    def test_ordinary_defines_ignored(self):
        d = self.tree({"include/x.h": "#define COUNT 4\n#define F(x) func_80012345(x)\n"})
        self.assertEqual(R.problems(d), [])


if __name__ == "__main__":
    unittest.main()
