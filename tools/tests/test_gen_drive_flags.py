"""gen_drive.py's round-68 flags: --journal-refusals writes one {"outcome": "refused"} record per
row eligible() turned down, --fresh truncates the lane's journal/out/cells first, and neither is on
by default.  The generator is tools/tests/stub_gen_refuse.py, which refuses everything, so nothing
is compiled or verified."""
import json
import os
import shutil
import subprocess
import sys
import unittest
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
LANE = "zz_test_gen_drive_flags"
LANE_DIR = ROOT / "work/native_lane" / LANE


def row_with_pins():
    sys.path.insert(0, str(ROOT / "tools"))
    from common import rows, clean_path
    from pin_census import sites_of
    for r in rows():
        p = clean_path(r)
        if p.exists() and sites_of(p.read_text(errors="replace")):
            return r["id"]
    return None


class TestFlags(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.row = row_with_pins()
        if cls.row is None:
            raise unittest.SkipTest("no pinned row in this tree")

    def setUp(self):
        shutil.rmtree(LANE_DIR, ignore_errors=True)

    def tearDown(self):
        shutil.rmtree(LANE_DIR, ignore_errors=True)

    def drive(self, *flags):
        env = dict(os.environ, PYTHONPATH=str(ROOT / "tools/tests"))
        return subprocess.run([sys.executable, "tools/lanes/gen_drive.py", "stub_gen_refuse", LANE,
                               "--only", self.row, "--workers", "1", *flags],
                              cwd=str(ROOT), capture_output=True, text=True, timeout=600, env=env)

    def journal(self):
        p = LANE_DIR / "journal.jsonl"
        return [json.loads(l) for l in p.read_text().splitlines() if l.strip()] if p.exists() else []

    def test_default_journals_nothing(self):
        p = self.drive()
        self.assertEqual(p.returncode, 0, p.stderr)
        self.assertIn("0 eligible rows", p.stdout)
        self.assertEqual(self.journal(), [])

    def test_journal_refusals_records_the_reason(self):
        p = self.drive("--journal-refusals")
        self.assertEqual(p.returncode, 0, p.stderr)
        recs = self.journal()
        self.assertEqual(len(recs), 1)
        self.assertEqual(recs[0]["outcome"], "refused")
        self.assertEqual(recs[0]["id"], self.row)
        self.assertIn("refuses every row", recs[0]["reason"])
        self.assertIn("in_sha", recs[0])

    def test_refusals_do_not_mark_a_row_done(self):
        self.drive("--journal-refusals")
        self.drive("--journal-refusals")                 # the row is asked again, not skipped
        self.assertEqual(len(self.journal()), 2)

    def test_fresh_truncates_the_journal_and_out(self):
        self.drive("--journal-refusals")
        stale = LANE_DIR / "out/dungeon"
        stale.mkdir(parents=True, exist_ok=True)
        (stale / "func_stale.c").write_text("void f(void) {}\n")
        (LANE_DIR / "cells.jsonl").write_text('{"id": "x", "to": "2.8.0"}\n')
        p = self.drive("--fresh", "--journal-refusals")
        self.assertIn("--fresh", p.stdout)
        self.assertEqual(len(self.journal()), 1)
        self.assertFalse((stale / "func_stale.c").exists())
        self.assertFalse((LANE_DIR / "cells.jsonl").exists())

    def test_catchup_skips_text_another_lane_already_scored(self):
        sys.path.insert(0, str(ROOT / "tools"))
        from common import rows, clean_path, sha_text
        r = next(r for r in rows() if r["id"] == self.row)
        prev = ROOT / "work/native_lane/zz_catchup_prev_stub_gen_refuse"
        try:
            prev.mkdir(parents=True, exist_ok=True)
            (prev / "journal.jsonl").write_text(json.dumps(
                {"id": self.row, "in_sha": sha_text(clean_path(r).read_text(errors="replace")), "outcome": "miss"}) + "\n")
            p = self.drive("--catchup", "--journal-refusals")
            self.assertEqual(p.returncode, 0, p.stderr)
            self.assertIn("--catchup: 1 ", p.stdout)
            self.assertEqual(self.journal(), [])          # skipped before eligible(): no refused record
            p = self.drive("--journal-refusals")          # without the flag the row is asked again
            self.assertEqual(len(self.journal()), 1)
        finally:
            shutil.rmtree(prev, ignore_errors=True)


if __name__ == "__main__":
    unittest.main()
