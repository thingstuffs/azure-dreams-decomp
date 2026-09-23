"""tools/lanes/land_gap.sh: the argument handling, the EXTRA_T cascade list, the arm twins, the
queue lock and the max wait - all against a FAKE repo root whose land_lanes.sh and arm_restore.py
only record what they were called with.  Nothing is landed, gated or compiled, and the busy check is
injected (GAP_BUSY_CMD), so the test never consults the real machine: on this box a real `sweep.py`
is usually running and the real check would wait for hours."""
import os
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
SCRIPT = ROOT / "tools/lanes/land_gap.sh"

FAKE_LAND = """#!/bin/bash
# records its arguments and the EXTRA_T it was given, then "succeeds"
echo "$*" >> "$PWD/land_calls.txt"
echo "EXTRA_T=$EXTRA_T" >> "$PWD/land_calls.txt"
exit ${FAKE_LAND_RC:-0}
"""

FAKE_ARM = """import sys, pathlib
lane = sys.argv[1]
out = pathlib.Path("work/native_lane/%s_arms/out/dungeon" % lane)
if __import__("os").environ.get("FAKE_ARM_WINS", "1") == "1":
    out.mkdir(parents=True, exist_ok=True)
    (out / "func_1.c").write_text("void f(void) {}\\n")
print("arm_restore %s" % lane)
"""


class Base(unittest.TestCase):
    def setUp(self):
        self.tmp = Path(tempfile.mkdtemp())
        (self.tmp / "tools/lanes").mkdir(parents=True)
        (self.tmp / "build_ovl/work").mkdir(parents=True)
        (self.tmp / "work/native_lane").mkdir(parents=True)
        (self.tmp / "STATUS.md").write_text("Pin sites now: 5,152 in 1,123 rows\n")
        land = self.tmp / "tools/lanes/land_lanes.sh"
        land.write_text(FAKE_LAND)
        land.chmod(0o755)
        (self.tmp / "tools/lanes/arm_restore.py").write_text(FAKE_ARM)
        shutil.copy(ROOT / "tools/lanes/cascade_extra.txt", self.tmp / "tools/lanes/cascade_extra.txt")

    def tearDown(self):
        shutil.rmtree(self.tmp, ignore_errors=True)

    def gap(self, *args, env=None, timeout=60):
        e = dict(os.environ, LAND_GAP_ROOT=str(self.tmp), GAP_POLL="1", GAP_MAX_WAIT="20",
                 GAP_BUSY_CMD="false")            # "false" exits 1 = not busy
        e.update(env or {})
        return subprocess.run(["bash", str(SCRIPT), *args], capture_output=True, text=True,
                              env=e, timeout=timeout)

    def calls(self):
        p = self.tmp / "land_calls.txt"
        return p.read_text().splitlines() if p.exists() else []


class TestArgs(Base):
    def test_usage_without_lanes(self):
        p = self.gap("tag")
        self.assertEqual(p.returncode, 1)
        self.assertIn("usage", p.stdout + p.stderr)

    def test_lands_tag_and_lanes_then_prints_the_pin_line(self):
        p = self.gap("r68pool", "r68_a", "r68_b", env={"FAKE_ARM_WINS": "0"})
        self.assertEqual(p.returncode, 0, p.stdout + p.stderr)
        self.assertEqual(self.calls()[0], "r68pool r68_a r68_b")
        self.assertIn("Pin sites now: 5,152 in 1,123 rows", p.stdout)
        self.assertIn("LAND_GAP_END r68pool", p.stdout)

    def test_extra_t_comes_from_cascade_extra_txt(self):
        self.gap("r68pool", "r68_a", env={"FAKE_ARM_WINS": "0"})
        extra = [l for l in self.calls() if l.startswith("EXTRA_T=")][0]
        for gen in ("t88_castshift", "t90_callunnest", "t95_runjoint", "t117_stagehost"):
            self.assertIn(gen, extra)
        self.assertNotIn("#", extra)                       # comment lines are not passed as generators
        toks = extra[len("EXTRA_T="):].split()
        self.assertEqual(len(toks), len(set(toks)))         # each generator once (round-76 repair)

    def test_a_corrupted_list_is_deduplicated(self):
        # round 76: `sed 's/$/ t96 .../'` appended the same generators to every line, comments included
        (self.tmp / "tools/lanes/cascade_extra.txt").write_text(
            "# header t96_absplace\nt88_castshift t96_absplace\nt89_lifetimesplit t96_absplace\nnot_a_gen\n")
        p = self.gap("r68pool", "r68_a", env={"FAKE_ARM_WINS": "0"})
        extra = [l for l in self.calls() if l.startswith("EXTRA_T=")][0]
        self.assertEqual(extra.split("=", 1)[1].split(), ["t88_castshift", "t96_absplace", "t89_lifetimesplit"])
        self.assertIn("duplicates dropped", p.stderr)
        self.assertIn("not_a_gen is not a tools/xform module", p.stderr)

    def test_extra_t_can_be_overridden(self):
        self.gap("r68pool", "r68_a", env={"EXTRA_T": "t99_only", "FAKE_ARM_WINS": "0"})
        self.assertIn("EXTRA_T=t99_only ", self.calls()[1] + " ")

    def test_a_refused_landing_is_retried_until_the_deadline(self):
        # land_lanes.sh refuses ("a codex lane is running") when one starts between our check and
        # its own: the lander must try again, not give up with the lanes staged.
        p = self.gap("r68pool", "r68_a", env={"FAKE_LAND_RC": "1", "GAP_MAX_WAIT": "4"})
        self.assertEqual(p.returncode, 1)
        calls = [c for c in self.calls() if not c.startswith("EXTRA_T")]
        self.assertGreater(len(calls), 1, calls)
        self.assertEqual(set(calls), {"r68pool r68_a"})       # never the twins after a refusal
        self.assertIn("retrying", p.stdout)


class TestArms(Base):
    def test_arm_twins_land_as_a_second_transaction(self):
        p = self.gap("r68pool", "r68_a")
        self.assertIn("arm_restore r68_a", p.stdout)
        calls = [c for c in self.calls() if not c.startswith("EXTRA_T")]
        self.assertEqual(calls, ["r68pool r68_a", "r68poola r68_a_arms"])

    def test_gap_arms_0_skips_them(self):
        self.gap("r68pool", "r68_a", env={"GAP_ARMS": "0"})
        self.assertEqual([c for c in self.calls() if not c.startswith("EXTRA_T")], ["r68pool r68_a"])


class TestWaiting(Base):
    def test_no_gap_within_max_wait_lands_nothing(self):
        p = self.gap("r68pool", "r68_a", env={"GAP_BUSY_CMD": "true", "GAP_MAX_WAIT": "2"})
        self.assertEqual(p.returncode, 2)
        self.assertIn("no landing within", p.stdout)
        self.assertIn("still staged", p.stdout)
        self.assertEqual(self.calls(), [])

    def test_second_lander_queues_on_the_lock(self):
        lock = self.tmp / "build_ovl/work/land_gap.lock"
        holder = subprocess.Popen(["flock", str(lock), "sleep", "30"])
        try:
            p = self.gap("r68pool", "r68_a", env={"GAP_MAX_WAIT": "2"})
            self.assertEqual(p.returncode, 3)
            self.assertIn("another gap lander", p.stdout)
            self.assertEqual(self.calls(), [])
        finally:
            holder.kill()
            holder.wait()


if __name__ == "__main__":
    unittest.main()
