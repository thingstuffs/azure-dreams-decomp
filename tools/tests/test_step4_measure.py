"""Fidelity step 4 measurement helpers: tools/fidelity/step4_measure.py (recipes, smallext, inline-asm count) and
the isolated SLUS link of tools/fidelity/slus_iso.py (gate + restore, genuine-$gp model).

    python3 -m unittest tools/tests/test_step4_measure.py
"""
import shutil, sys, tempfile, unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools")); sys.path.insert(0, str(ROOT / "tools/fidelity"))
import step4_measure as M  # noqa: E402


class RecipeTests(unittest.TestCase):
    def test_with_cell_keeps_row_flags_in_each_dialect(self):
        self.assertEqual(M.with_cell("2.7.2-G0 -fno-schedule-insns", "2.7.2-cdk", "overlay"), "2.7.2-cdk-G0 -fno-schedule-insns")
        self.assertEqual(M.with_cell("2.6.3 -G0", "2.7.2-cdk", "slus"), "2.7.2-cdk -G0")
        self.assertEqual(M.with_cell("2.7.2-cdk -mmips-as -G0", "2.7.2-cdk", "slus"), "2.7.2-cdk -G0")

    def test_evidenced_recipes(self):
        row = {"kind": "overlay", "cfg": "2.7.2-G0 -fno-strength-reduce"}
        self.assertEqual([c for _l, c in M.evidenced_recipes(row, "2.7.2-cdk-G0")],
                         ["2.7.2-cdk-G0", "2.7.2-cdk-G0 -fno-strength-reduce"])
        self.assertEqual([c for _l, c in M.evidenced_recipes(row, "2.8.0-G0")],
                         ["2.8.0-G0", "2.8.0-G0 -fno-strength-reduce", "2.7.2-cdk-G0 -fno-strength-reduce"])
        slus = {"kind": "slus", "cfg": "2.7.2"}
        self.assertEqual([c for _l, c in M.evidenced_recipes(slus, None)], ["2.7.2-cdk", "2.8.1"])
        # a non-splitting census recipe is no evidence: fall back to the two splitting cells
        self.assertEqual([c for _l, c in M.evidenced_recipes(dict(row, cfg="2.7.2"), "2.7.2")], ["2.7.2-cdk", "2.8.1"])


class TextTests(unittest.TestCase):
    def test_smallext_padded_struct(self):
        t = "extern struct {\n    s32 v;\n    s32 pad[2];\n} D_80012090;\nint f(void) { return D_80012090.v; }\n"
        self.assertEqual(M.smallext(t), "extern s32 D_80012090;\nint f(void) { return D_80012090; }\n")

    def test_smallext_padded_typedef_and_comment_mentions(self):
        t = ("typedef struct {\n    s32 field0;\n    s32 pad4;\n    s32 pad8;\n} S_80081480;\nextern S_80081480 D_80081480;\n"
             "/* copies into D_80081480 */\nvoid f(int x) { D_80081480.field0 = x; }\n")
        n = M.smallext(t)
        self.assertIn("extern s32 D_80081480;", n); self.assertNotIn("typedef", n); self.assertIn("D_80081480 = x;", n)

    def test_smallext_sized_array_read_at_zero_only(self):
        t = "extern u8 D_80080A84[16];\nint f(void) { return D_80080A84[0]; }\n"
        self.assertEqual(M.smallext(t), "extern u8 D_80080A84;\nint f(void) { return D_80080A84; }\n")
        self.assertIsNone(M.smallext("extern u8 D_80080A84[16];\nint f(int i) { return D_80080A84[i]; }\n"))

    def test_inline_asm_counts_statements_not_symbol_definitions(self):
        t = '__asm__(".set D_1, 0x1");\nvoid f(void) { __asm__("lui $2, %%hi(D_1)" : "=r"(x)); /* __asm__("x") */ }\n'
        self.assertEqual(M.inline_asm(t), 1)


class SlusIsoTests(unittest.TestCase):
    STEM = "w_8005A1D0"

    @classmethod
    def setUpClass(cls):
        if not (ROOT / "build_slus/build/slus_006.14").exists():
            raise unittest.SkipTest("no built build_slus tree")
        from slus_iso import SlusView
        cls.d = Path(tempfile.mkdtemp(prefix="slus_iso_test_"))
        cls.v = SlusView(cls.d / "view")

    @classmethod
    def tearDownClass(cls):
        shutil.rmtree(cls.d, ignore_errors=True)

    def test_calibrates_and_restores(self):
        self.assertEqual(self.v.calibrate()["result"], "MATCH")
        bad = self.v.gate({self.STEM: (None, "2.7.2", "")})              # a non-splitting cell cannot make its split
        self.assertEqual(bad["result"], "NO MATCH"); self.assertGreater(bad["residue"], 0)
        self.assertEqual(self.v.calibrate()["result"], "MATCH")           # the view is pristine again
        self.assertTrue((self.v.dest / "src" / (self.STEM + ".c")).is_symlink())

    def test_recipe_switch_links_exact(self):
        # the landed C of w_8005A1D0 is exact at 2.8.1 too (a byte-neutral switch the step-4 measurement found)
        self.assertEqual(self.v.gate({self.STEM: (None, "2.8.1", "")})["result"], "MATCH")

    def test_gp_symbols_from_the_pinned_object(self):
        from slus_iso import gp_symbols
        self.assertEqual(gp_symbols("w_8003D92C"), {"D_80080ABC", "D_80080ABE"})


if __name__ == "__main__":
    unittest.main()
