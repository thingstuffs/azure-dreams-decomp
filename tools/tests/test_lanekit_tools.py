"""The round-73 promotions to the lane kit: `lab.py --grid` (expand_grid), `lab.py cellscore` /
`kitlib.row_at_cfg` / `kitlib.score_at`, `diff.py` and `dump.py`.  No compiles, no scorer, no real
lane: compilers and `verify` are fakes, and `kitlib.bootstrap` is never called (it would install the
Popen shim for the whole test run - see test_lanekit.py)."""
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
for sub in (ROOT / "tools/lanes", ROOT / "tools/xform", ROOT / "tools", KIT):   # KIT ends up first
    sys.path.insert(0, str(sub))

import kitlib                                                             # noqa: E402
import lab as L                                                           # noqa: E402
import diff as D                                                          # noqa: E402
import dump as DP                                                         # noqa: E402

ROW = {"id": "dungeon/func_80000000", "func": "func_80000000", "container": "dungeon",
       "c_path": "src/dungeon/func_80000000.c", "cfg": "2.7.2-G0", "cell": "2.7.2",
       "flags": "-G0", "kind": "overlay"}
PINNED = "void f(void) {\n    int a;\n    ASM_KEEP(a);\n    g(a);\n}\n"
FREE = "void f(void) {\n    int a;\n    g(a);\n}\n"


class TestGrid(unittest.TestCase):
    G = {"kind": {"loc": [], "cast": [["x;", "(s16)x;"]]},
         "flags": {"early": [], "late": [["a;\n", "b;\n"], ["c", "d"]]},
         "ab": {"0": [], "1": [["q", "r"]]}}

    def test_product_count_and_order(self):
        out = L.expand_grid(self.G)
        self.assertEqual(len(out), 2 * 2 * 2)
        self.assertEqual([n for n, _ in out][:3], ["loc+early+0", "loc+early+1", "loc+late+0"])
        self.assertEqual(out[-1][0], "cast+late+1")

    def test_reps_concatenate_in_axis_order(self):
        d = dict(L.expand_grid(self.G))
        self.assertEqual(d["cast+late+1"], [["x;", "(s16)x;"], ["a;\n", "b;\n"], ["c", "d"], ["q", "r"]])
        self.assertEqual(d["loc+early+0"], [])

    def test_at_base_pinned_prefixes_names(self):
        out = L.expand_grid({"@base": "pinned", "a": {"x": [], "y": []}})
        self.assertEqual([n for n, _ in out], ["@x", "@y"])

    def test_bad_shapes_refused(self):
        with self.assertRaises(SystemExit):
            L.expand_grid({"a": {"x+y": []}})
        with self.assertRaises(SystemExit):
            L.expand_grid({"a": {"x": [["only-old"]]}})
        with self.assertRaises(SystemExit):
            L.expand_grid({"a": []})

    def test_miss_is_logged_with_the_nearest_line(self):
        grid = {"k": {"drop": [["    ASM_KEEP(aa);\n", ""]]}}
        (name, reps), = L.expand_grid(grid)
        lab = L.Lab.__new__(L.Lab)
        with tempfile.TemporaryDirectory() as td:
            lab.lane, lab.id, lab.base, lab.erased = Path(td), ROW["id"], PINNED, PINNED
            with redirect_stdout(io.StringIO()) as out:
                self.assertIsNone(lab.test_subs(name, reps))
            rec = kitlib.log_read(td)[0]
        self.assertEqual(rec["status"], "pattern-missing")
        self.assertEqual(rec["variant"], "drop")
        self.assertIn("ASM_KEEP(a);", rec["why"])        # the nearest line in the text
        self.assertIn("SKIP", out.getvalue())


def fake_verify(exact_for):
    calls = []

    def verify(row, f, include_root=None, diff=False):
        calls.append(dict(row))
        ok = Path(f).read_text() in exact_for
        return {"exact": ok, "total": 0 if ok else 7, "subs": 0, "indels": 0, "status": "ok"}
    return verify, calls


class TestCellscore(unittest.TestCase):
    CFG = "2.8.1-G0 -mno-split-addresses"

    def run_cs(self, exact_for, lane=None):
        verify, calls = fake_verify(exact_for)
        lines = []
        with tempfile.TemporaryDirectory() as td:
            rec = L.cellscore(ROW, FREE, self.CFG, lane or td, name="v7", base=PINNED,
                              verify=verify, out=lines.append)
        return rec, "\n".join(lines), calls

    def test_row_override_mirrors_land_coherence(self):
        r = kitlib.row_at_cfg(ROW, self.CFG)
        self.assertEqual((r["cfg"], r["cell"], r["flags"]), (self.CFG, "2.8.1", "-G0 -mno-split-addresses"))
        self.assertEqual(ROW["cfg"], "2.7.2-G0")          # the caller's row is not mutated
        self.assertIs(kitlib.row_at_cfg(ROW, None), ROW)

    def test_exact_prints_handover_and_writes_no_ledger(self):
        led = ROOT / "ledger/rows.jsonl"
        before = led.stat().st_mtime_ns if led.exists() else None
        with mock.patch("common.set_row_cfg", side_effect=AssertionError("ledger write")):
            rec, out, calls = self.run_cs({FREE, PINNED})
        self.assertEqual(before, led.stat().st_mtime_ns if led.exists() else None)
        self.assertTrue(all(c["cfg"] == self.CFG and c["cell"] == "2.8.1" for c in calls))
        self.assertEqual(len(calls), 2)                   # candidate, then the pinned text (rule 2)
        self.assertIn("registered cfg : 2.7.2-G0   (UNCHANGED", out)
        self.assertIn("rule 2 HOLDS", out)
        cells = json.loads(rec["cells_line"])
        self.assertEqual((cells["id"], cells["to"]), (ROW["id"], self.CFG))
        self.assertIn(rec["cells_line"], out)
        self.assertIn("bash tools/lanes/land_coherence.sh <tag>", out)
        self.assertEqual((rec["kind"], rec["cfg"], rec["status"], rec["rule2"]),
                         ("cellscore", self.CFG, "exact", True))

    def test_rule2_not_holding_is_a_coherence_trade(self):
        rec, out, _ = self.run_cs({FREE})
        self.assertIn("does NOT hold", out)
        self.assertFalse(rec["rule2"])

    def test_not_exact_hands_nothing_over(self):
        rec, out, calls = self.run_cs(set())
        self.assertIn("NOT exact", out)
        self.assertNotIn("cells_line", rec)
        self.assertEqual(len(calls), 1)                   # no rule-2 score when the candidate misses

    def test_lane_name_relative_to_native_lane(self):
        _, out, _ = self.run_cs({FREE, PINNED}, lane=ROOT / "work/native_lane/r99_x")
        self.assertIn("land_coherence.sh <tag> r99_x", out)


class TestReportOtherCfg(unittest.TestCase):
    def test_cross_cfg_exact_is_marked_and_not_counted(self):
        with tempfile.TemporaryDirectory() as td:
            for rec in ({"variant": "v1", "distance": 0, "score": {"exact": True, "total": 0}, "status": "exact"},
                        {"variant": "v2", "kind": "cellscore", "cfg": "2.8.1-G0", "distance": None,
                         "score": {"exact": True, "total": 0}, "status": "exact"}):
                kitlib.log_append(td, dict(rec, row=ROW["id"]))
            text = L.report(td, ROW["id"])
        self.assertIn("exact @2.8.1-G0", text)
        self.assertIn("2 scored, 1 exact (+1 exact only at another cfg", text)


class TestDiff(unittest.TestCase):
    def test_identical_listings_give_an_empty_diff(self):
        lines, dist = D.run(ROW, "a", "a", listing=lambda r, t: ["lw $2,0($4)", "jr $31"])
        self.assertEqual((lines, dist), ([], 0))

    def test_changed_line_counts_two(self):
        lst = {"p": ["addu $2,$4,$5", "jr $31"], "c": ["addu $2,$5,$4", "jr $31"]}
        lines, dist = D.run(ROW, "p", "c", ctx=1, listing=lambda r, t: lst[t])
        self.assertEqual(dist, 2)
        self.assertEqual(lines[:2], ["--- pinned", "+++ candidate"])
        self.assertIn("-addu $2,$4,$5", lines)

    def test_no_build_is_none(self):
        self.assertEqual(D.run(ROW, "p", "c", listing=lambda r, t: None if t == "c" else ["x"]), (None, None))


class TestDump(unittest.TestCase):
    def setUp(self):
        self.td = tempfile.TemporaryDirectory()
        self.lane = Path(self.td.name)
        (self.lane / "c.c").write_text(FREE)
        self.seen = []

        def dumps(row, text, want=None, timeout=None):
            self.seen.append((row, text, want))
            return {"error": None, "asm": "jr $31\n", "greg": "greg\n", "sched2": "s2\n"}
        self.patches = [mock.patch.object(kitlib, "bootstrap", return_value=self.lane),
                        mock.patch.object(kitlib, "row_of", return_value=dict(ROW)),
                        mock.patch.object(kitlib, "dumps", side_effect=dumps)]
        for p in self.patches:
            p.start()

    def tearDown(self):
        for p in self.patches:
            p.stop()
        self.td.cleanup()

    def test_cfg_passthrough_and_files(self):
        with redirect_stdout(io.StringIO()) as out:
            w = DP.main([ROW["id"], str(self.lane / "c.c"), str(self.lane / "dumps"),
                         "--cfg", "2.8.1-G0", "--pass", "sched"])
        row, text, want = self.seen[0]
        self.assertEqual((row["cfg"], row["cell"]), ("2.8.1-G0", "2.8.1"))
        self.assertEqual(text, FREE)
        self.assertEqual(want, {"sched", "sched2"})
        self.assertEqual(sorted(p.name for p in w), ["c.greg", "c.s", "c.sched2"])
        self.assertIn("registered cfg 2.7.2-G0 unchanged", out.getvalue())

    def test_default_is_every_pass_at_the_registered_cfg(self):
        with redirect_stdout(io.StringIO()):
            DP.main([ROW["id"], str(self.lane / "c.c"), str(self.lane / "d")])
        row, _, want = self.seen[0]
        self.assertEqual((row["cfg"], want), ("2.7.2-G0", None))

    def test_outdir_outside_the_lane_refused(self):
        with self.assertRaises(SystemExit):
            DP.main([ROW["id"], str(self.lane / "c.c"), "/tmp/elsewhere_lanekit_test"])
        self.assertEqual(self.seen, [])

    def test_bad_pass_refused(self):
        with self.assertRaises(SystemExit), redirect_stdout(io.StringIO()), \
                mock.patch("sys.stderr", io.StringIO()):
            DP.main([ROW["id"], str(self.lane / "c.c"), str(self.lane / "d"), "--pass", "nope"])


if __name__ == "__main__":
    unittest.main()
