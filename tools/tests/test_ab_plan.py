"""tools/lanes/ab_plan.py: the r76 A/B draws the SAME rows for every arm, per band, seeded."""
import sys
import unittest
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools/lanes"))
import ab_plan  # noqa: E402

ROWS = ([{"row": "c/a%02d" % i, "band": "1-2"} for i in range(30)]
        + [{"row": "c/b%02d" % i, "band": "3-7"} for i in range(12)]
        + [{"row": "c/c%02d" % i, "band": "8+"} for i in range(7)])


class Draw(unittest.TestCase):
    def test_paired_packs_and_sizes(self):
        lanes, chosen = ab_plan.draw(ROWS, 20, 5, 76)
        self.assertEqual({b: len(r) for b, r in chosen.items()}, {"1-2": 20, "3-7": 10, "8+": 5})
        for k in range(1, 5):
            packs = {tuple(lanes["r76_%s_b12_%d" % (arm, k)]) for arm in ab_plan.ARMS}
            self.assertEqual(len(packs), 1)                      # every arm gets the same rows
        self.assertEqual(len(lanes), (4 + 2 + 1) * len(ab_plan.ARMS))

    def test_seeded_and_prefix_stable(self):
        a, _ = ab_plan.draw(ROWS, 20, 5, 76)
        b, _ = ab_plan.draw(ROWS, 20, 5, 76)
        self.assertEqual(a, b)
        c, _ = ab_plan.draw(ROWS, 10, 5, 76)                     # phase A = the first packs of the full plan
        self.assertEqual(c["r76_opus_b12_1"], a["r76_opus_b12_1"])
        self.assertEqual(c["r76_opus_b12_2"], a["r76_opus_b12_2"])


class Stratified(unittest.TestCase):
    def rows(self):
        return [{"row": "%s/f%03d" % ("dungeon" if i % 3 else "town", i), "band": "1-2"} for i in range(90)]

    def test_quota_overlap_single_serve(self):
        rows = self.rows()
        dist = {r["row"]: i for i, r in enumerate(rows)}
        st = ab_plan.strata(rows, dist)
        arms, ov, sample = ab_plan.assign(rows, st, 76)
        self.assertEqual({a: len(v) for a, v in arms.items()}, ab_plan.QUOTA)
        self.assertEqual(len(ov), ab_plan.OVERLAP)
        served = [i for v in arms.values() for i in v] + ov
        self.assertEqual(len(served), len(set(served)))              # no row served twice (overlap aside)
        self.assertEqual(len(sample), sum(ab_plan.QUOTA.values()) + ab_plan.OVERLAP)
        for a in ("luna6", "sol6", "opus"):                           # every 2-slot arm gets every tercile
            self.assertEqual({st[i][2] for i in arms[a]}, {"easy", "mid", "hard"})

    def test_unbuildable_rows_are_hardest(self):
        rows = self.rows()[:6]
        dist = {r["row"]: i for i, r in enumerate(rows)}
        dist[rows[1]["row"]] = None                              # a dungeon row (4 in the group)
        st = ab_plan.strata(rows, dist)
        self.assertEqual(st[rows[1]["row"]][2], "hard")

    def test_probe_ok(self):
        import pool
        self.assertTrue(pool.probe_ok("banner\nOK\n"))
        self.assertFalse(pool.probe_ok("You've hit your usage limit. OK\nOK"))
        self.assertFalse(pool.probe_ok("not ok"))
        self.assertEqual(pool.TIER_OF["agy"], "agy")


if __name__ == "__main__":
    unittest.main()
