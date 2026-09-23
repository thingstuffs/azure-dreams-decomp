"""tools/lanes/cluster.py: one cluster of 3-5 pins per big row (round 76 cluster packs)."""
import sys
import unittest
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools/lanes"))
import cluster  # noqa: E402
import served  # noqa: E402


def site(line, macro, arg, kind="stmt", decl=""):
    return (kind, macro, arg, line * 10, line * 10 + 5, line, decl)


SITES = [site(10, "ASM_REG", "4", "reg", "int count"), site(12, "ASM_KEEP", "count"), site(14, "ASM_USE", "count"),
         site(40, "ASM_SCHED_BARRIER", ""), site(41, "ASM_SCHED_BARRIER", ""), site(43, "ASM_KEEP", "p"),
         site(44, "ASM_KEEP", "q"), site(200, "ASM_KEEP", "far"), site(300, "ASM_KEEP", "x"), site(301, "ASM_KEEP", "x")]


class Pick(unittest.TestCase):
    def test_same_variable_group_ranks_first(self):
        ranked = cluster.pick_clusters(SITES, 3, 5, 25)
        self.assertEqual(ranked[0][0], (0, 1, 2))                  # REG decl `count` + KEEP/USE(count)
        self.assertIn("count", ranked[0][1])

    def test_barriers_do_not_form_a_variable_group(self):
        for idx, why in cluster.pick_clusters(SITES, 3, 5, 25):
            self.assertNotIn("same variable ``", why)

    def test_disjoint_and_sizes(self):
        dj = cluster.disjoint(cluster.pick_clusters(SITES, 3, 5, 25))
        used = [i for idx, _ in dj for i in idx]
        self.assertEqual(len(used), len(set(used)))
        self.assertTrue(all(3 <= len(idx) <= 5 for idx, _ in dj))
        self.assertIn((3, 4, 5, 6), [idx for idx, _ in dj])        # the barrier run at lines 40-44

    def test_small_row_and_far_sites(self):
        self.assertEqual(cluster.pick_clusters(SITES[:2], 3, 5, 25), [])
        far = [site(1, "ASM_KEEP", "a"), site(100, "ASM_KEEP", "b"), site(300, "ASM_KEEP", "c")]
        (idx, why), = cluster.pick_clusters(far, 3, 5, 25)
        self.assertIn("none within --near", why)

    def test_scope_convention_matches_served(self):
        idx = cluster.pick_clusters(SITES, 3, 5, 25)[0][0]
        as_json = [[SITES[i][5], SITES[i][1], SITES[i][2]] for i in idx]      # build_class_pack's cluster.json
        self.assertEqual(served.cluster_scope(as_json), served.cluster_scope(list(reversed(as_json))))
        self.assertTrue(served.cluster_scope(as_json).startswith("cluster:10:ASM_REG(4)"))


if __name__ == "__main__":
    unittest.main()
