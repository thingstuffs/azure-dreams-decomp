"""tools/lanes/compose2.py: the pure helpers (no compiler runs) - nearest-distance parsing, the default B set, and
the compile_s wrapper's capture / target substitution."""
import importlib.util
import sys
import unittest
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
_spec = importlib.util.spec_from_file_location("compose2", ROOT / "tools/lanes/compose2.py")
C = importlib.util.module_from_spec(_spec); _spec.loader.exec_module(C)


class Compose2(unittest.TestCase):
    def test_nearest_of_accepts_every_journal_shape(self):
        self.assertEqual(C.nearest_of({"nearest": 14}), [14])
        self.assertEqual(C.nearest_of({"nearest": [{"distance": 3, "label": "x"}, {"distance": None}]}), [3])
        self.assertEqual(C.nearest_of({"nearest": [(5, "x"), (7, "y")]}), [5, 7])
        self.assertEqual(C.nearest_of({}), [])

    def test_default_B_is_the_cascade_plus_the_late_generators(self):
        b = C.default_B()
        self.assertNotIn("t2_pins", b)
        self.assertNotIn("t53_reg_state", b)
        for t in ("t36_paramwidth", "t77_symplace", "t110_paramfold", "t117_stagehost"):
            self.assertIn(t, b)
        self.assertEqual(len(b), len(set(b)))

    def test_wrapper_captures_and_substitutes(self):
        calls = []
        orig = C._ORIG
        try:
            C._ORIG = lambda row, text: calls.append(text) or ["L:" + text]
            row = {"id": "x/f", "cfg": "2.7.2"}
            C.CAPTURE["x/f"] = {}
            C.compile_s(row, "candA")
            self.assertIn("candA", C.CAPTURE.pop("x/f").values())
            C.SUBST[C.sha_text("candB")] = "orig"
            self.assertEqual(C.compile_s(row, "candB"), ["L:orig"])     # B's target = the original listing
            C.SUBST.clear()
        finally:
            C._ORIG = orig; C._CACHE.clear()

    def test_pinfree_menu_keeps_only_pin_free_candidates_within_max_dA(self):
        t0 = "void f(void)\n{\n    ASM_KEEP(x);\n    x = 1;\n}\n"
        near_free = t0.replace("    ASM_KEEP(x);\n", "")
        far_free = near_free.replace("x = 1", "x = 2")
        pinned = t0.replace("x = 1", "x = 3")
        listing = {t0: ["a", "b", "c"], near_free: ["a", "b", "d"], pinned: ["a", "b", "c", "e"],
                   far_free: ["q"] * 40}

        class T:
            @staticmethod
            def eligible(text, row, cen):
                return None

            @staticmethod
            def apply_verified(text, row, cen, vf):
                for c in (near_free, far_free, pinned):
                    C.compile_s(row, c)
                return None, {}
        A = type("A", (), {"T": T, "__name__": "fakeA"})
        orig = C._ORIG
        try:
            C._ORIG = lambda row, text: listing.get(text)
            row = {"id": "x/g", "cfg": "2.7.2"}
            C.MODE.update(pinfree=True, max_dA=20)
            menu = C.menu_of(A, row, t0, {}, 3)
            self.assertEqual([(d, pc) for d, pc, _h, _c in menu], [(2, 0)])     # the far one is beyond max_dA
            C.MODE.update(pinfree=False)
            self.assertEqual([pc for _d, pc, _h, _c in C.menu_of(A, row, t0, {}, 3)], [1])
        finally:
            C._ORIG = orig; C._CACHE.clear(); C.MODE.update(pinfree=False); C.STATS.clear()


if __name__ == "__main__":
    unittest.main()
