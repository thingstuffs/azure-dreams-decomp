"""r82_sonnet_nojtbl: jtbl-mismatch status + --no-jtbl scoring in the lane kit (kitlib / nojtbl / lab / diff)."""
import io
import json
import sys
import tempfile
import unittest
from contextlib import redirect_stdout
from pathlib import Path
from unittest import mock

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
KIT = ROOT / "tools/lanes/lanekit"
for p in (str(KIT), str(ROOT / "tools")):
    if p not in sys.path:
        sys.path.insert(0, p)
import kitlib                                                             # noqa: E402
import nojtbl                                                             # noqa: E402
import lab as L                                                           # noqa: E402
import diff as D                                                          # noqa: E402

ERR = ("jtbl: local .rodata at 0x80024098 word 1: got 0x80025E84, retail 0x80025DCC "
       "(the switch's case->label table differs from retail); local .rodata at 0x80024098 word 3: got 0x1, retail 0x2 (x)")
ROW = {"id": "dungeon/func_X", "kind": "overlay", "func": "func_X", "cfg": "2.7.2-cdk-G0", "c_path": "a/func_X.c"}


class Parse(unittest.TestCase):
    def test_parse(self):
        j = nojtbl.parse_jtbl_err(ERR)
        self.assertEqual(j[0], {"addr": "0x80024098", "word": 1, "got": "0x80025E84", "retail": "0x80025DCC"})
        self.assertEqual([x["word"] for x in j], [1, 3])
        self.assertEqual(nojtbl.parse_jtbl_err("ld: nope"), [])
        self.assertEqual(nojtbl.parse_jtbl_err(None), [])

    def test_status_idempotent_and_narrow(self):
        v = nojtbl.jtbl_status({"status": "failed", "class": "build-fail", "err": ERR, "exact": False})
        self.assertEqual(v["status"], "jtbl-mismatch")
        self.assertEqual(v["jtbl"][0]["word"], 1)
        self.assertEqual(nojtbl.jtbl_status(dict(v))["jtbl"], v["jtbl"])
        other = nojtbl.jtbl_status({"status": "failed", "err": "gcc: error"})
        self.assertEqual(other["status"], "failed")
        self.assertNotIn("jtbl", other)


class ScoreAt(unittest.TestCase):
    def setUp(self):
        self.calls = []

        def fake(row, f, include_root=None, diff=False):
            self.calls.append(diff)
            if diff:
                return {"status": "diff", "text": "build-fail/no-hex"}
            return {"status": "failed", "exact": False, "err": ERR}
        self.fake = fake

    def test_summary_and_diff_report_jtbl_mismatch(self):
        with mock.patch.object(kitlib, "row_at_cfg", lambda r, c: r):
            v = kitlib.score_at(ROW, "int x;", verify=self.fake)
            self.assertEqual(v["status"], "jtbl-mismatch")
            v = kitlib.score_at(ROW, "int x;", verify=self.fake, diff=True)
        self.assertEqual(v["status"], "jtbl-mismatch")
        self.assertEqual(kitlib.score_fields(v)["jtbl"][0]["retail"], "0x80025DCC")
        self.assertIn("jtbl-mismatch", D.jtbl_lines(v)[0].lower())
        self.assertIn("word 1", D.jtbl_lines(v)[0])

    def test_no_jtbl_never_claims_exact(self):
        def ok(row, f, include_root=None, diff=False):
            return {"status": "diff", "text": "MATCH"} if diff else {"status": "ok", "exact": True, "total": 0}
        with mock.patch.object(kitlib, "row_at_cfg", lambda r, c: r):
            v = kitlib.score_at(ROW, "x", verify=ok, no_jtbl=True)
        self.assertIs(v["exact"], False)
        self.assertIs(v["text_exact"], True)
        self.assertIs(v["jtbl_checked"], False)
        self.assertEqual(D.jtbl_lines(v, True)[0], "# text exact, jump table NOT checked")
        self.assertIn("text exact, jump table NOT checked", L.jtbl_note(kitlib.score_fields(v)))
        self.assertEqual(L.score_cell(kitlib.score_fields(v)), "text exact, jtbl NOT checked")
        with tempfile.TemporaryDirectory() as td:
            rec = kitlib.record_score(td, ROW, "v", v, "t")
        self.assertEqual(rec["status"], "text-exact-nojtbl")

    def test_no_jtbl_diff_text_is_marked(self):
        def ok(row, f, include_root=None, diff=False):
            return {"status": "diff", "text": "  [   0] a | b"} if diff else {"status": "ok", "exact": False, "total": 3}
        with mock.patch.object(kitlib, "row_at_cfg", lambda r, c: r):
            v = kitlib.score_at(ROW, "x", verify=ok, no_jtbl=True, diff=True)
        self.assertTrue(v["text"].startswith("NOTE jump-table content check OFF"))
        self.assertFalse(v["text_exact"])

    def test_slus_refused(self):
        with self.assertRaises(SystemExit):
            nojtbl.verify_nojtbl(dict(ROW, kind="slus"), "f.c", verify_fn=lambda *a, **k: {})


class Routing(unittest.TestCase):
    def test_shim_routes_only_when_flagged(self):
        seen = []
        with mock.patch.object(nojtbl._subprocess, "run", lambda cmd, *a, **k: seen.append(cmd)):
            s = nojtbl._Shim()
            cmd = ["nice", "python3", "tools/aligned_score.py", "--func", "f"]
            s.run(cmd)
            nojtbl._tls.off = True
            try:
                s.run(cmd)
                s.run(["python3", "other.py"])
            finally:
                nojtbl._tls.off = False
        self.assertEqual(seen[0], cmd)
        self.assertEqual(seen[1], ["nice", "python3", str(nojtbl.RUNNER), "--func", "f"])
        self.assertEqual(seen[2], ["python3", "other.py"])

    def test_trampoline_anchor_exists_in_scorer(self):
        """nojtbl_run.py patches overlay_func_compare.py after this anchor; if the scorer changes, fail here."""
        import nojtbl_run
        src = (ROOT / "tools/gate/overlay_func_compare.py").read_text()
        self.assertIn(nojtbl_run.ANCHOR, src)
        self.assertIn("local_table_diffs", (ROOT / "tools/gate/match.py").read_text())

    def test_runner_wraps_only_overlay_func_compare(self):
        import nojtbl_run
        seen = []
        with mock.patch.object(nojtbl_run, "_run", lambda cmd, *a, **k: seen.append(cmd)):
            nojtbl_run.run(["python3", "/x/work/g3/overlay_func_compare.py", "--func", "f"])
            nojtbl_run.run(["python3", "/x/other.py"])
        self.assertEqual(seen[0][:2], ["python3", "-c"])
        self.assertEqual(seen[0][3:], ["/x/work/g3/overlay_func_compare.py", "--func", "f"])
        self.assertEqual(seen[1], ["python3", "/x/other.py"])


if __name__ == "__main__":
    unittest.main()
