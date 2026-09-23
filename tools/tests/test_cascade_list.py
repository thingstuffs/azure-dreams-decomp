"""tools/lanes/cascade_list.py: the cascade_extra.txt parser (round 76 repair of the `sed 's/$/ tNN/'` corruption)."""
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools/lanes"))
import cascade_list  # noqa: E402


class CascadeList(unittest.TestCase):
    def parse(self, text, known=("t88_castshift", "t96_absplace", "t97_pagesym", "t36_paramwidth")):
        with tempfile.TemporaryDirectory() as td:
            p = Path(td) / "c.txt"; p.write_text(text); msgs = []
            return cascade_list.extras(p, warn=msgs.append, known=set(known)), msgs

    def test_the_repo_file_is_clean(self):
        msgs = []
        toks = cascade_list.extras(warn=msgs.append)
        self.assertEqual(msgs, [], "cascade_extra.txt carries duplicates or stray tokens")
        self.assertEqual(len(toks), len(set(toks)))
        for t in ("t100_rmwfold", "t116_ptaglink", "t103_dropsink", "t110_paramfold", "t113_sibarity", "t117_stagehost"):
            self.assertIn(t, toks)
        body = [l for l in cascade_list.EXTRA.read_text().splitlines() if l.strip() and not l.lstrip().startswith("#")]
        self.assertTrue(all(len(l.split()) == 1 for l in body), "one generator per line")

    def test_sed_corruption_is_harmless(self):
        toks, msgs = self.parse("# comment t96_absplace t97_pagesym\nt88_castshift t96_absplace t97_pagesym\n"
                                "t96_absplace t97_pagesym\n")
        self.assertEqual(toks, ["t88_castshift", "t96_absplace", "t97_pagesym"])
        self.assertTrue(any("duplicates dropped" in m for m in msgs))

    def test_stray_and_builtin_tokens_are_dropped(self):
        toks, msgs = self.parse("t88_castshift\nbogus\nt36_paramwidth\n")
        self.assertEqual(toks, ["t88_castshift"])
        self.assertTrue(any("bogus is not a tools/xform module" in m for m in msgs))
        self.assertTrue(any("t36_paramwidth is already in land_lanes.sh" in m for m in msgs))

    def test_builtin_parses_land_lanes(self):
        b = cascade_list.builtin()
        self.assertEqual(b[0], "t36_paramwidth")
        self.assertIn("t87_lifetimemerge", b)
        self.assertNotIn("t2_pins", b)
        self.assertFalse(any(t.startswith("$") for t in b))
        self.assertEqual(cascade_list.full()[-1], "t2_pins")


if __name__ == "__main__":
    unittest.main()
