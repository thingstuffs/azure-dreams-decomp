"""tools/lanes/ab_report.py on a synthetic lane directory in a tempdir: the codex.log header and
`tokens used` tail, served/exact rows, pin counts, status and the per-model aggregate."""
import json
import os
import sys
import tempfile
import time
import unittest
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools/lanes"))
import ab_report  # noqa: E402

LOG = ("Reading prompt from stdin...\nOpenAI Codex v0.154.0\n--------\n\x1b[1mworkdir:\x1b[0m /x\n"
       "\x1b[1mmodel:\x1b[0m gpt-6-sol\n--------\nuser\nmodel: not-this\n...work...\n"
       "\x1b[2mtokens used\x1b[0m\n1,234\nlast message\n")
PINNED = "void f(void) {\n    ASM_SCHED_BARRIER();\n    ASM_SCHED_BARRIER();\n}\n"
ONE = "void f(void) {\n    ASM_SCHED_BARRIER();\n}\n"


def make_lane(root, name, log=LOG, message=True):
    d = Path(root) / "work/native_lane" / name
    for sub in ("base/dungeon", "out/dungeon"):
        (d / sub).mkdir(parents=True)
    (d / "base/dungeon/func_1.c").write_text(PINNED)
    (d / "base/dungeon/func_1.c.base_sha").write_text("x")
    (d / "base/dungeon/func_2.c").write_text(PINNED)
    (d / "out/dungeon/func_1.c").write_text(ONE)
    (d / "out/dungeon/func_1.c.base_sha").write_text("x")
    (d / "out/dungeon/func_2.c").write_text(ONE)      # no .base_sha: not byte-exact
    (d / "codex.log").write_text(log)
    (d / "lane.pid").write_text("999999\n")
    t = time.time()
    os.utime(d / "lane.pid", (t - 600, t - 600))
    if message:
        (d / "last_message.txt").write_text("done")
        os.utime(d / "last_message.txt", (t, t))
    return d


class TestParse(unittest.TestCase):
    def test_model_and_tokens(self):
        self.assertEqual(ab_report.parse_model(LOG), "gpt-6-sol")
        self.assertEqual(ab_report.parse_tokens(LOG), 1234)
        self.assertIsNone(ab_report.parse_tokens("no figure\n"))


class TestScan(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.mkdtemp()

    def test_lane(self):
        d = make_lane(self.tmp, "r73_sol6_1")
        r = ab_report.scan(d, {"codex": {"pack": "r73_sol6_1", "model": "gpt-6-sol", "candidates": 1},
                               "note": "n"})
        self.assertEqual((r["model"], r["rows"], r["exact"], r["tokens"], r["status"]),
                         ("gpt-6-sol", 2, 1, 1234, "ok"))
        self.assertEqual((r["pins_before"], r["pins_after"], r["pins_removed"]), (2, 1, 1))
        self.assertAlmostEqual(r["minutes"], 10.0, delta=0.2)
        self.assertEqual(r["journal_candidates"], 1)

    def test_limit_cut_lane(self):
        d = make_lane(self.tmp, "r73_luna6_1", message=False,
                      log=LOG.replace("gpt-6-sol", "gpt-6-luna").replace(
                          "tokens used", "ERROR: You've hit your usage limit.\ntokens used"))
        r = ab_report.scan(d)
        self.assertEqual((r["model"], r["status"]), ("gpt-6-luna", "limit"))

    def test_glob_and_aggregate(self):
        make_lane(self.tmp, "r73_sol6_1")
        make_lane(self.tmp, "r73_sol6_2")
        make_lane(self.tmp, "r72_other")
        dirs = ab_report.lane_dirs(self.tmp, [], ["r73_sol6_*"])
        self.assertEqual([d.name for d in dirs], ["r73_sol6_1", "r73_sol6_2"])
        agg = ab_report.aggregate([ab_report.scan(d) for d in dirs])
        self.assertEqual(len(agg), 1)
        a = agg[0]
        self.assertEqual((a["model"], a["lanes"], a["ok"], a["rows"], a["exact"], a["exact_rate"],
                          a["pins_removed"], a["mean_tokens"], a["tokens_per_exact"]),
                         ("gpt-6-sol", 2, 2, 4, 2, 0.5, 2, 1234, 1234))

    def test_cli_json(self):
        make_lane(self.tmp, "r73_sol6_1")
        import io, contextlib
        buf = io.StringIO()
        with contextlib.redirect_stdout(buf):
            ab_report.main(["--glob", "r73_*", "--root", self.tmp, "--json"])
        out = json.loads(buf.getvalue())
        self.assertEqual(out["models"][0]["model"], "gpt-6-sol")


if __name__ == "__main__":
    unittest.main()
