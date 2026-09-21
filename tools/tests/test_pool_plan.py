"""Planning half of tools/lanes/pool.py: lane state (including a lane already running, which must be
adopted rather than launched), the build commands a rows JSON produces, and the --dry-run text.
No codex, no compiles, no launches - every case runs against a fake work/native_lane tree."""
import json
import os
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools/lanes"))
import pool  # noqa: E402


def lane(root, name, prompt=False, ran=False, pid=None, outs=0):
    d = Path(root) / "work/native_lane" / name
    d.mkdir(parents=True, exist_ok=True)
    if prompt:
        (d / "PROMPT.txt").write_text("p")
        (d / "BRIEF.md").write_text("b")
    if ran:
        (d / "last_message.txt").write_text("m")
    if pid is not None:
        (d / "lane.pid").write_text("%d\n" % pid)
    for i in range(outs):
        o = d / "out" / "dungeon"
        o.mkdir(parents=True, exist_ok=True)
        (o / ("func_%d.c" % i)).write_text("void f(void) {}\n")
    return d


class TestPlan(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.mkdtemp()
        self.rows = Path(self.tmp) / "rows.json"
        self.rows.write_text(json.dumps({
            "r68_a": ["dungeon/func_1", "dungeon/func_2"],
            "r68_b": ["town/func_3"],
            "r68_c": [],
        }))

    def test_actions(self):
        lane(self.tmp, "r68_a")                       # nothing built yet, rows known -> build+run
        lane(self.tmp, "r68_b", prompt=True)          # pack built, never launched -> run
        lane(self.tmp, "r68_c")                       # no pack, no rows -> no-rows
        steps = pool.plan(self.tmp, None, str(self.rows))
        self.assertEqual([s["action"] for s in steps], ["build+run", "run", "no-rows"])
        self.assertEqual([s["lane"] for s in steps], ["r68_a", "r68_b", "r68_c"])

    def test_already_ran_is_skipped(self):
        lane(self.tmp, "r68_a", prompt=True, ran=True)
        self.assertEqual(pool.plan(self.tmp, ["r68_a"], str(self.rows))[0]["action"], "skip")

    def test_live_lane_is_adopted_not_relaunched(self):
        lane(self.tmp, "r68_a", prompt=True, pid=os.getpid())     # this test process is alive
        self.assertEqual(pool.lane_state(self.tmp, "r68_a"), "running")
        self.assertEqual(pool.plan(self.tmp, ["r68_a"], str(self.rows))[0]["action"], "adopt")

    def test_dead_pid_is_not_running(self):
        lane(self.tmp, "r68_a", prompt=True, pid=999999)
        self.assertEqual(pool.lane_state(self.tmp, "r68_a"), "built")

    def test_build_command_carries_rows_duck_exemplars_paragraphs(self):
        lane(self.tmp, "r68_a")
        cmd = pool.plan(self.tmp, ["r68_a"], str(self.rows), exemplars=6,
                        paragraphs=["big_rows", "new_findings"])[0]["build"]
        self.assertEqual(cmd[:3], ["python3", "tools/lanes/build_class_pack.py", "r68_a"])
        self.assertIn("--duck", cmd)
        self.assertEqual(cmd[cmd.index("--rows") + 1], "dungeon/func_1,dungeon/func_2")
        self.assertEqual(cmd[cmd.index("--exemplars") + 1], "6")
        self.assertEqual(cmd[cmd.index("--paragraphs") + 1], "big_rows,new_findings")

    def test_no_exemplars_no_paragraphs(self):
        lane(self.tmp, "r68_a")
        cmd = pool.plan(self.tmp, ["r68_a"], str(self.rows), exemplars=0)[0]["build"]
        self.assertNotIn("--exemplars", cmd)
        self.assertNotIn("--paragraphs", cmd)

    def test_candidate_count(self):
        lane(self.tmp, "r68_b", prompt=True, ran=True, outs=3)
        self.assertEqual(pool.candidates(self.tmp, "r68_b"), 3)
        self.assertEqual(pool.candidates(self.tmp, "r68_never"), 0)

    def test_plan_text_names_the_lander_and_the_sentinel(self):
        lane(self.tmp, "r68_a")
        steps = pool.plan(self.tmp, ["r68_a"], str(self.rows))
        txt = pool.plan_text("big", "astra", 2, steps, "big")
        self.assertIn("gpt-6-astra", txt)
        self.assertIn("tools/lanes/land_gap.sh poolbig", txt)
        self.assertTrue(txt.endswith("POOL_big_END"))
        self.assertIn("--no-land", pool.plan_text("big", "sol", 1, steps, "big", land=False))


class TestCli(unittest.TestCase):
    def test_dry_run_launches_nothing(self):
        tmp = tempfile.mkdtemp()
        lane(tmp, "r68_a", prompt=True)
        rows = Path(tmp) / "rows.json"
        rows.write_text(json.dumps({"r68_a": ["dungeon/func_1"]}))
        p = subprocess.run([sys.executable, str(ROOT / "tools/lanes/pool.py"), "t", "--model", "sol",
                            "--rows-json", str(rows), "--root", tmp, "--dry-run"],
                           capture_output=True, text=True, cwd=str(ROOT))
        self.assertEqual(p.returncode, 0, p.stderr)
        self.assertIn("would launch: r68_a", p.stdout)
        self.assertIn("POOL_t_END", p.stdout)
        self.assertFalse((Path(tmp) / "work/native_lane/r68_a/last_message.txt").exists())


class TestParagraphs(unittest.TestCase):
    def test_named_paragraphs_exist(self):
        d = ROOT / "tools/lanes/brief_paragraphs"
        for name in ("big_rows", "class_question", "new_findings"):
            self.assertTrue((d / (name + ".md")).is_file(), name)
        # the template is the only one that may still carry unfilled slots
        self.assertNotIn("<<", (d / "big_rows.md").read_text())
        self.assertNotIn("<<", (d / "new_findings.md").read_text())
        self.assertIn("<<", (d / "class_question.md").read_text())


if __name__ == "__main__":
    unittest.main()
