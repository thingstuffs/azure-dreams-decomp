"""tools/lanes/lane_cap.py: per-lane token/wall caps (kill + cap.txt) and the per-band stop rule."""
import json
import os
import subprocess
import sys
import tempfile
import time
import unittest
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools/lanes"))
import lane_cap  # noqa: E402
import pool  # noqa: E402


def token_event(inp, cached, out):
    return json.dumps({"type": "event_msg", "payload": {"type": "token_count", "info": {"total_token_usage": {
        "input_tokens": inp, "cached_input_tokens": cached, "output_tokens": out}}}})


class Caps(unittest.TestCase):
    def setUp(self):
        self.root = Path(tempfile.mkdtemp())
        self.d = self.root / "work/native_lane/r76_x"
        self.d.mkdir(parents=True)
        (self.d / "PROMPT.txt").write_text("p")
        (self.d / "BRIEF.md").write_text("b")

    def spawn(self):
        p = subprocess.Popen(["setsid", "sleep", "60"])
        (self.d / "lane.pid").write_text("%d\n" % p.pid)
        self.addCleanup(lambda: (p.kill(), p.wait()))
        return p

    def test_wall_cap_kills_and_marks(self):
        p = self.spawn()
        t = time.time() - 3600
        os.utime(self.d / "lane.pid", (t, t))
        self.assertIsNone(lane_cap.check(self.root, "r76_x", p.pid, wall_cap=120))
        rec = lane_cap.check(self.root, "r76_x", p.pid, wall_cap=30)
        self.assertEqual(rec["cap"], "wall")
        p.wait(timeout=5)
        self.assertTrue((self.d / "cap.txt").exists())
        self.assertEqual(pool.lane_state(self.root, "r76_x"), "ran")      # never relaunched

    def test_token_cap(self):
        p = self.spawn()
        self.assertIsNone(lane_cap.check(self.root, "r76_x", p.pid, token_cap=1000, tokens_fn=lambda r, l: 900))
        rec = lane_cap.check(self.root, "r76_x", p.pid, token_cap=1000, tokens_fn=lambda r, l: 1500)
        self.assertEqual((rec["cap"], rec["figure"]), ("tokens", 1500))

    def test_live_tokens_from_rollout(self):
        (self.d / "lane.pid").write_text("1\n")
        start = (self.d / "lane.pid").stat().st_mtime
        stamp = time.strftime("%Y-%m-%dT%H-%M-%S", time.gmtime(start))
        day = self.root / "sessions" / time.strftime("%Y/%m/%d", time.gmtime(start))
        day.mkdir(parents=True)
        (day / ("rollout-%s-other.jsonl" % stamp)).write_text(json.dumps({"x": "another lane"}) + "\n"
                                                              + token_event(10, 0, 0) + "\n")
        (day / ("rollout-%s-mine.jsonl" % stamp)).write_text(
            json.dumps({"prompt": "cd %s && ..." % self.d.resolve()}) + "\n"
            + token_event(1000, 600, 50) + "\n" + token_event(14813611, 14100864, 116104) + "\n")
        self.assertEqual(lane_cap.live_tokens(self.root, "r76_x", self.root / "sessions"), 828851)
        self.assertIn("mine", (self.d / "rollout.txt").read_text())


class BandStop(unittest.TestCase):
    H = [{"pins_removed": 2, "tokens": 1_000_000}, {"pins_removed": 0, "tokens": 1_000_000},
         {"pins_removed": 0, "tokens": 2_000_000, "estimated": False}]

    def test_off_and_not_enough_lanes(self):
        self.assertEqual(lane_cap.band_stop(self.H, 3, 0, 10)[0], False)
        self.assertEqual(lane_cap.band_stop(self.H[:2], 3, 0.5, 10)[2], "2 of 3 lanes finished")

    def test_threshold(self):
        # 2 pins over 4M tokens x weight 10 = 40 units -> 0.05 pins per unit
        stop, rate, _ = lane_cap.band_stop(self.H, 3, 0.1, 10)
        self.assertEqual((stop, rate), (True, 0.05))
        self.assertFalse(lane_cap.band_stop(self.H, 3, 0.01, 10)[0])

    def test_no_weight_never_stops(self):
        stop, rate, why = lane_cap.band_stop(self.H, 3, 100, None)
        self.assertEqual((stop, rate), (False, None))
        self.assertIn("TODO", why)

    def test_estimates_are_not_measurements(self):
        h = [{"pins_removed": 0, "tokens": 5, "estimated": True}] * 3
        self.assertEqual(lane_cap.band_stop(h, 3, 1, 1)[2], "no measured tokens")

    def test_pool_flags_default_off(self):
        a = pool.parse(["t"])
        self.assertEqual((a.token_cap, a.wall_cap, a.band_stop), (0, 0, 0))


if __name__ == "__main__":
    unittest.main()
