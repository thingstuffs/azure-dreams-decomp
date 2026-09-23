"""tools/lanes/record_usage.py: an Agent-tool lane's usage.json from the Agent result, never a model's guess."""
import json
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools/lanes"))
import record_usage  # noqa: E402

NOTE = ("<task-notification>\n<task-id>a1b2</task-id>\n<status>completed</status>\n"
        "<usage><subagent_tokens>%d</subagent_tokens><tool_uses>%d</tool_uses><duration_ms>%d</duration_ms></usage>\n"
        "</task-notification>")


def assistant(mid, **u):
    return json.dumps({"type": "assistant", "timestamp": "2026-09-23T03:0%dZ" % len(mid),
                       "message": {"id": mid, "model": "claude-opus-5-5", "usage": u}})


class Backfill(unittest.TestCase):
    def setUp(self):
        self.tmp = Path(tempfile.mkdtemp())
        self.lane = self.tmp / "work/native_lane/r73_opus_s5"
        self.lane.mkdir(parents=True)
        (self.lane / "codex.log").write_text("model: claude-opus-5-5[1m]\ntokens used\n320000\n")
        self.sess = self.tmp / "sess.jsonl"
        lines = [json.dumps({"type": "queue-operation", "timestamp": "2026-09-23T03:43:00Z",
                             "content": NOTE % (300000, 100, 2000000)}),
                 json.dumps({"type": "queue-operation", "timestamp": "2026-09-23T03:44:00Z",   # resumed: last wins
                             "content": NOTE % (328384, 129, 2233693)})]
        self.sess.write_text("\n".join(lines) + "\n")
        sub = self.tmp / "sess/subagents"
        sub.mkdir(parents=True)
        (sub / "agent-a1b2.meta.json").write_text(json.dumps({"description": "Opus lane r73_opus_s5 (1-2 pins)",
                                                              "model": "opus"}))
        (sub / "agent-a1b2.jsonl").write_text("\n".join([
            assistant("m1", input_tokens=2, output_tokens=5, cache_creation_input_tokens=100, cache_read_input_tokens=10),
            assistant("m1", input_tokens=2, output_tokens=9, cache_creation_input_tokens=100, cache_read_input_tokens=10),
            assistant("m22", input_tokens=1, output_tokens=4, cache_creation_input_tokens=50, cache_read_input_tokens=200),
        ]) + "\n")

    def test_backfill_writes_measured_usage(self):
        res = record_usage.backfill(self.sess, root=self.tmp)
        self.assertEqual([(l, a) for l, a, _ in res], [("r73_opus_s5", "written")])
        u = json.loads((self.lane / "usage.json").read_text())
        self.assertEqual((u["tokens"], u["tool_uses"], u["duration_ms"], u["estimated"], u["model"]),
                         (328384, 129, 2233693, False, "claude-opus-5-5[1m]"))
        t = u["transcript"]                       # m1 deduplicated: its last usage counted once
        self.assertEqual((t["api_calls"], t["input"], t["output"], t["cache_creation"], t["cache_read"], t["blended"]),
                         (2, 3, 13, 150, 210, 166))

    def test_backfill_keeps_a_recorded_result_and_replaces_an_estimate(self):
        record_usage.main([ "r73_opus_s5", "--tokens", "1", "--root", str(self.tmp)])
        self.assertEqual(record_usage.backfill(self.sess, root=self.tmp)[0][1], "kept")
        record_usage.main(["r73_opus_s5", "--estimate", "5", "--root", str(self.tmp)])
        self.assertTrue(json.loads((self.lane / "usage.json").read_text())["estimated"])
        self.assertEqual(record_usage.backfill(self.sess, root=self.tmp)[0][1], "written")

    def test_prompt_template_has_no_self_estimate(self):
        p = (ROOT / "tools/lanes/agent_lane_prompt.md").read_text()
        self.assertIn("<LANE_DIR>", p)
        self.assertNotIn("best estimate", p)


if __name__ == "__main__":
    unittest.main()
