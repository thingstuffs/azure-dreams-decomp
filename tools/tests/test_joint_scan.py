"""tools/lanes/joint_scan.py: the subset enumeration and the pinned-variable grouping."""
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/lanes"))
sys.path.insert(0, str(ROOT / "tools"))
import joint_scan  # noqa: E402

REG = ("reg", "ASM_REG", "17", 0, 0, 1, "void *target")
KEEP_T = ("stmt", "ASM_KEEP", "target", 0, 0, 2, "")
KEEP_C = ("stmt", "ASM_KEEP", "context", 0, 0, 3, "")
KEEPNV = ("stmt", "ASM_KEEP_NV", "context", 0, 0, 4, "")


class T(unittest.TestCase):
    def test_var_of_reads_the_register_declaration(self):
        self.assertEqual(joint_scan.var_of(REG), "target")
        self.assertEqual(joint_scan.var_of(("reg", "ASM_REG", "2", 0, 0, 1, "S_1 **row")), "row")
        self.assertEqual(joint_scan.var_of(KEEP_C), "context")

    def test_exhaustive_includes_singles_and_every_subset(self):
        subs = joint_scan.subsets_of([REG, KEEP_T, KEEP_C], pair_pins=20, exhaustive_pins=10)
        self.assertEqual(len(subs), 7)                       # 2^3 - 1
        self.assertIn((0,), subs); self.assertIn((0, 1, 2), subs)

    def test_structured_groups_whole_set_macro_variable_and_pairs(self):
        sites = [REG, KEEP_T, KEEP_C, KEEPNV]
        subs = joint_scan.subsets_of(sites, pair_pins=20, exhaustive_pins=0)
        self.assertIn((0, 1, 2, 3), subs)                    # the whole set
        self.assertIn((1, 2), subs)                          # same macro ASM_KEEP
        self.assertIn((0, 1), subs)                          # same variable: target (REG + KEEP)
        self.assertIn((2, 3), subs)                          # same variable: context
        self.assertNotIn((0,), subs)                         # no singles outside exhaustive mode
        self.assertEqual(len(subs), len(set(subs)))          # no duplicates
        no_pairs = joint_scan.subsets_of(sites, pair_pins=3, exhaustive_pins=0)
        self.assertNotIn((0, 3), no_pairs)                   # pairs only under --pair-pins

    def test_custom_pool_skips_flags_the_recipe_already_has(self):
        row = {"cfg": "2.7.2-cdk-G0 -g"}
        pool = joint_scan.pool_for(row, "custom")
        self.assertTrue(all(p.startswith("2.7.2-cdk-G0 -g ") for p in pool))
        self.assertNotIn("2.7.2-cdk-G0 -g -g", pool)
        self.assertEqual(len(pool), len(joint_scan.CUSTOM_FLAGS) - 1)



class TCoherence(unittest.TestCase):
    def test_coherence_subsets_include_whole_groups_pairs_and_singles(self):
        import coherence_scan
        sites = [REG, KEEP_T, KEEP_C, KEEPNV]
        subs = coherence_scan.subsets(sites, pair_pins=8)
        self.assertIn((0, 1, 2, 3), subs); self.assertIn((0, 1), subs); self.assertIn((2, 3), subs)
        self.assertIn((0,), subs); self.assertEqual(len(subs), len(set(subs)))
        big = coherence_scan.subsets(sites, pair_pins=2)
        self.assertNotIn((0, 3), big); self.assertIn((0, 1, 2, 3), big)   # no pairs above --pair-pins; groups stay


if __name__ == "__main__":
    unittest.main()
