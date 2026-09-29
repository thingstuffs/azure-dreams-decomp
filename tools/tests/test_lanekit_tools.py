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
import erase as ER                                                        # noqa: E402
import prio as PR                                                         # noqa: E402

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


class TestApiCap(unittest.TestCase):
    def test_api_refuses_the_61st_attempt_and_explicit_more_allows_it(self):
        with tempfile.TemporaryDirectory() as td:
            lab = L.Lab.__new__(L.Lab)
            lab.lane, lab.id, lab.base, lab.erased = Path(td), ROW["id"], PINNED, PINNED
            for n in range(kitlib.VARIANT_CAP):
                kitlib.log_append(td, {"row": lab.id, "variant": f"v{n}", "status": "measured"})
            with self.assertRaisesRegex(SystemExit, "--more"):
                lab.test("last", FREE)
            with self.assertRaisesRegex(SystemExit, "--more"):
                lab.test_subs("missing", [["absent", "x"]])
            self.assertEqual(lab.count(), kitlib.VARIANT_CAP)
            lab.more = True
            with redirect_stdout(io.StringIO()):
                self.assertIsNone(lab.test_subs("missing", [["absent", "x"]]))
            self.assertEqual(lab.count(), kitlib.VARIANT_CAP + 1)


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


class TestBaseFile(unittest.TestCase):
    def test_start_text_precedence(self):
        self.assertEqual(L.start_text("v", "PIN", "ERA"), "ERA")
        self.assertEqual(L.start_text("v", "PIN", "ERA", "FILE"), "FILE")
        self.assertEqual(L.start_text("@v", "PIN", "ERA", "FILE"), "PIN")     # @name still means pinned

    def test_read_base_file(self):
        self.assertIsNone(L.read_base_file(None))
        with tempfile.TemporaryDirectory() as td:
            (Path(td) / "b.c").write_text(FREE)
            self.assertEqual(L.read_base_file(Path(td) / "b.c"), FREE)
        with self.assertRaisesRegex(SystemExit, "no such file"):
            L.read_base_file("/nonexistent/lanekit_base.c")

    def test_test_subs_starts_from_the_base_file(self):
        with tempfile.TemporaryDirectory() as td:
            lab = L.Lab.__new__(L.Lab)
            lab.lane, lab.id, lab.base, lab.erased, lab.more = Path(td), ROW["id"], PINNED, FREE, False
            lab.start = "void f(void) {\n    int b;\n}\n"
            seen = []
            lab.test = lambda name, text, note="", score=False, stage=None: seen.append((name, text, note))
            lab.test_subs("v", [["int b;", "int c;"]])
            lab.test_subs("@p", [["int a;", "int d;"]])
            with redirect_stdout(io.StringIO()):
                self.assertIsNone(lab.test_subs("miss", [["int a;", "x"]]))    # not in the --base text
        self.assertEqual(seen[0][:2], ("v", "void f(void) {\n    int c;\n}\n"))
        self.assertIn("--base", seen[0][2])
        self.assertIn("int d;", seen[1][1])


class TestStageCell(unittest.TestCase):
    CFG = "2.7.2-cdk-G0"

    def setUp(self):
        self.td = tempfile.TemporaryDirectory()
        self.lane = Path(self.td.name)
        self.bp = self.lane / "base/dungeon/func_80000000.c"
        self.bp.parent.mkdir(parents=True)
        self.bp.write_text(PINNED)
        self.bp.with_name(self.bp.name + ".base_sha").write_text("abc123\n")

    def tearDown(self):
        self.td.cleanup()

    def run_sc(self, cand, exact_for, note="mechanism X"):
        verify, _ = fake_verify(exact_for)
        lines = []
        rec = L.stage_cell(ROW, cand, self.CFG, note, self.lane, self.bp, PINNED, name="v7",
                           verify=verify, out=lines.append)
        return rec, "\n".join(lines)

    def test_cells_record_shape(self):
        self.assertEqual(L.cells_record("a/b", "2.7.2-cdk-G0", "why", 3, 0),
                         {"id": "a/b", "to": "2.7.2-cdk-G0", "coherence": "why", "pins_before": 3, "pins_after": 0})

    def test_cells_write_appends_and_replaces_same_id_and_cfg(self):
        p = self.lane / "cells.jsonl"
        L.cells_write(p, L.cells_record("a/b", "X", "one", 2, 1))
        L.cells_write(p, L.cells_record("c/d", "X", "two", 2, 1))
        L.cells_write(p, L.cells_record("a/b", "X", "three", 2, 0))
        L.cells_write(p, L.cells_record("a/b", "Y", "other cfg", 2, 0))
        got = [json.loads(l) for l in p.read_text().splitlines()]
        self.assertEqual([(g["id"], g["to"], g["coherence"]) for g in got],
                         [("c/d", "X", "two"), ("a/b", "X", "three"), ("a/b", "Y", "other cfg")])

    def test_exact_and_admissible_is_staged_with_sha_and_cells_line(self):
        rec, out = self.run_sc(FREE, {FREE})
        dst = self.lane / "out/dungeon/func_80000000.c"
        self.assertEqual(dst.read_text(), FREE)
        self.assertEqual(dst.with_name(dst.name + ".base_sha").read_text(), "abc123\n")
        line = json.loads((self.lane / "cells.jsonl").read_text())
        self.assertEqual(line, {"id": ROW["id"], "to": self.CFG, "coherence": "mechanism X",
                                "pins_before": 1, "pins_after": 0})
        self.assertNotIn("refused", rec)
        self.assertEqual(rec["kind"], "stage-cell")
        self.assertEqual(rec["staged"], "out/dungeon/func_80000000.c")

    def test_not_exact_is_refused_and_writes_nothing(self):
        rec, out = self.run_sc(FREE, set())
        self.assertIn("not exact at " + self.CFG, rec["refused"])
        self.assertFalse((self.lane / "out").exists())
        self.assertFalse((self.lane / "cells.jsonl").exists())

    def test_not_admissible_is_refused(self):
        rec, out = self.run_sc(PINNED, {PINNED})           # exact, but no pin removed
        self.assertIn("not admissible", rec["refused"])
        self.assertFalse((self.lane / "cells.jsonl").exists())

    def test_note_is_required_and_registered_cfg_refused(self):
        with self.assertRaisesRegex(SystemExit, "--note"):
            self.run_sc(FREE, {FREE}, note=" ")
        with self.assertRaises(SystemExit):
            L.stage_cell(ROW, FREE, ROW["cfg"], "n", self.lane, self.bp, PINNED, verify=fake_verify({FREE})[0])


SCORER_TEXT = """resolved: overlay x
  ! [   0] addiu $s1, $s1, 1 | addiu $s2, $s2, 1 raw 24310001 24520001
    [   1] lw $s2, 0($sp) | lw $s1, 0($sp)
  ~ [   2] j 0x80100000 | j 0x80200000
    [   3] jr $ra | jr $ra
"""


class TestScorerDiff(unittest.TestCase):
    def test_parse_scorer(self):
        rows = D.parse_scorer(SCORER_TEXT)
        self.assertEqual(len(rows), 4)
        self.assertEqual(rows[0], (0, "addiu $s1, $s1, 1", "addiu $s2, $s2, 1"))      # generated, retail
        self.assertEqual(D.parse_scorer("*** MATCH ***"), [])

    def test_plain_diff_shows_every_changed_line(self):
        lines = D.scorer_diff(SCORER_TEXT, ctx=0)
        self.assertIn("-addiu $s2, $s2, 1", lines)
        self.assertIn("+addiu $s1, $s1, 1", lines)
        self.assertIn("-lw $s1, 0($sp)", lines)

    def test_norm_regs_removes_a_pure_renaming_and_branch_targets(self):
        self.assertEqual(D.scorer_diff(SCORER_TEXT, ctx=0, norm_regs=True), [])

    def test_norm_regs_keeps_a_real_difference(self):
        text = "    [   0] addu $t0, $t1, $t1 | addu $t0, $t1, $t2\n"
        lines = D.scorer_diff(text, ctx=0, norm_regs=True)
        self.assertIn("-addu $r0, $r1, $r2", lines)
        self.assertIn("+addu $r0, $r1, $r1", lines)

    def test_canon_regs_keeps_fixed_registers(self):
        self.assertEqual(D.canon_regs(["lw $s3, 4($sp)", "jr $ra", "move $s3, $zero"]),
                         ["lw $r0, 4($sp)", "jr $ra", "move $r0, $zero"])

    def test_no_scorer_lines_is_none(self):
        self.assertIsNone(D.scorer_diff("*** MATCH ***"))

    def test_norm_regs_needs_scorer(self):
        with self.assertRaises(SystemExit):
            D.main(["dungeon/func_80000000", "pinned", "--norm-regs"])


LREG = """Register 89 used 6 times across 3 insns.
Register 99 used 20 times across 23 insns; crosses 2 calls.
Register 100 used 2 times across 4 insns in block 1.
"""
GREG = """;; 2 regs to allocate: 89 99

Register dispositions:
89 in 2  99 in -1

"""


class TestPrio(unittest.TestCase):
    def test_floor_log2(self):
        self.assertEqual([PR.floor_log2(n) for n in (0, 1, 2, 3, 8, 20, 42)], [0, 0, 1, 1, 3, 4, 5])

    def test_priority_formula_and_columns(self):
        rows = PR.priority_rows(LREG, GREG, {89: "linked_body"})
        self.assertEqual(len(rows), 2)                      # the `in block` pseudo is local: hidden
        r89, r99 = rows
        self.assertEqual(r89, [0, 89, "linked_body", 6, 3, 0, 2, 40000, "0", "$v0"])
        self.assertEqual(r99[:9], [1, 99, "", 20, 23, 2, 4, 34782, "1"])
        self.assertEqual(r99[9], "spilled")

    def test_all_lists_locals_and_flags_order_disagreement(self):
        rows = PR.priority_rows(LREG, GREG.replace("89 99", "99 89"), include_local=True)
        self.assertEqual([r[1] for r in rows], [99, 89, 100])
        self.assertEqual(rows[0][8], "1!")                  # dump ranks 99 first, the formula says 89
        self.assertEqual((rows[2][0], rows[2][8]), ("-", "-"))


class TestEraseCfg(unittest.TestCase):
    def test_cfg_scores_each_erasure_with_the_byte_scorer(self):
        text = "void f(void) {\n    int a;\n    ASM_KEEP(a);\n    g(a);\n}\n"
        calls = []

        def score_at(row, t, cfg=None, verify=None, diff=False):
            calls.append((row["cfg"], t))
            return {"total": 5 if "ASM_KEEP" in t else 0, "exact": "ASM_KEEP" not in t}
        with tempfile.TemporaryDirectory() as td:
            (Path(td) / "v.c").write_text(text)
            fake_screen = mock.Mock(target=["x"], distance=mock.Mock(side_effect=AssertionError("listing used")))
            with mock.patch.object(kitlib, "bootstrap", return_value=Path(td)), \
                    mock.patch.object(kitlib, "row_of", return_value=dict(ROW)), \
                    mock.patch.object(kitlib, "base_text", return_value=text), \
                    mock.patch.object(kitlib, "screen_for", return_value=fake_screen):
                res = ER.scan(ROW["id"], mode="all", variant=str(Path(td) / "v.c"), cfg="2.8.1-G0",
                              workers=1, score_at=score_at)
        self.assertTrue(all(c == "2.8.1-G0" for c, _ in calls))
        self.assertEqual((res["here"], res["lone"], res["all"], res["cfg"]), (5, {0: 0}, 0, "2.8.1-G0"))
        self.assertIn("byte scores at 2.8.1-G0", ER.render(res))


if __name__ == "__main__":
    unittest.main()
