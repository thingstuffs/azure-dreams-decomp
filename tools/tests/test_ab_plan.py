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


if __name__ == "__main__":
    unittest.main()
