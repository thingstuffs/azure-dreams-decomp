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


# ---------------------------------------------------------------- r80_fable_n1 harvest: trace / deps /
# classify / checks.  Fixture dump texts in the exact format gcc 2.7.2 sched.c prints (commentary first,
# then the RTL); the numbers are small and hand-made, the line shapes are copied from real dumps.

SCHED2 = """;; Function f

;;\t -- basic block number 0 from 10 to 16 --
;; ready list initially:
;; 16

;; insn[  10]: priority =    3, ref_count =    1
;; insn[  11]: priority =    2, ref_count =    1
;; insn[  12]: priority =    2, ref_count =    1
;; insn[  13]: priority =    1, ref_count =    1
;; insn[  14]: priority =    1, ref_count =    1
;; insn[  16]: priority = 2147483390, ref_count =    0
;; ready list at T-1: 16 (7ffffefe), now 16
;; ready list at T-2: 13 (1) 14 (1), now 14 13
;; ready list at T-3: 13 (1) 12 (2) 11 (2), now 12 11 13
;; insn 11 has a greater potential hazard, now 11 12 13
;; ready list at T-4: 13 (1) 12 (2), now 12 13
;; ready list at T-5: 13 (1)
;; blocking insn 13 for 1 cycles
;; launching 13 before 12 with no stalls at T-6
;; ready list at T-6: 13 (1), now 13
;; ready list at T-7: 10 (3), now 10
;; total time = 7
;; new basic block head = 10
;; new basic block end = 16

(insn 10 9 11 (set (reg:SI 2 v0) (mem:SI (reg:SI 4 a0))) -1 (nil)
    (nil))
(insn 11 10 12 (set (reg:SI 3 v1) (plus:SI (reg:SI 2 v0) (const_int 1))) -1 (insn_list 10 (nil))
    (nil))
(insn:HI 12 11 13 (set (reg:SI 8 t0) (high:SI (symbol_ref:SI ("g")))) -1 (nil)
    (nil))
(insn 13 12 14 (set (reg:SI 8 t0) (lo_sum:SI (reg:SI 8 t0) (symbol_ref:SI ("g")))) -1 (insn_list 12 (nil))
    (nil))
(insn 14 13 16 (set (reg:SI 9 t1) (asm_operands/v ("") ("=r") 0[ (reg:SI 3 v1) ] [ (asm_input:SI ("0")) ] ("f.c") 5)) -1 (insn_list 11 (insn_list:REG_DEP_ANTI 13 (nil)))
    (nil))
(jump_insn 16 14 17 (set (pc) (label_ref 20)) -1 (insn_list 14 (nil))
    (nil))
"""
GREG_PRE = SCHED2[SCHED2.index("(insn 10"):]        # chain order 10 11 12 13 14 16 = the LUIDs

SCHED1 = """;; Function f

;;\t -- basic block number 0 from 20 to 23 --
;; insn[  20]: priority =    1, ref_count =    2
;; insn[  21]: priority =    1, ref_count =    1
;; insn[  22]: priority =    1, ref_count =    1
;; insn[  23]: priority =    1, ref_count =    0
;; ready list at T-1: 23 (1), now 23
;; ready list at T-2: 21 (7f000001) 22 (1), now 21 22
;; ready list at T-3: 22 (1) 20 (7f000001), now 20 22
;; ready list at T-4: 22 (1), now 22
;; total time = 4

(insn 22 0 20 (set (reg/v:SI 17 s1) (const_int 5)) -1 (nil) (nil))
(insn 20 22 21 (set (reg:SI 80) (high:SI (symbol_ref:SI ("g")))) -1 (nil) (nil))
(insn 21 20 23 (set (reg:SI 81) (lo_sum:SI (reg:SI 80) (symbol_ref:SI ("g")))) -1 (insn_list 20 (nil)) (nil))
(insn 23 21 24 (set (reg/v:SI 17 s1) (asm_operands/v ("") ("=r") 0[ (reg:SI 81) ] [ ] ("f.c") 3)) -1 (insn_list 21 (insn_list 20 (insn_list 22 (nil)))) (nil))
"""
COMBINE_PRE = """(insn 20 0 22 (set (reg:SI 80) (high:SI (symbol_ref:SI ("g")))) -1 (nil) (nil))
(insn 22 20 21 (set (reg/v:SI 17 s1) (const_int 5)) -1 (nil) (nil))
(insn 21 22 23 (set (reg:SI 81) (lo_sum:SI (reg:SI 80) (symbol_ref:SI ("g")))) -1 (insn_list 20 (nil)) (nil))
(insn 23 21 24 (set (reg/v:SI 17 s1) (asm_operands/v ("") ("=r") 0[ (reg:SI 81) ] [ ] ("f.c") 3)) -1 (nil) (nil))
"""

SCORER = """NO MATCH func_80000000 2.7.2-G0
  disasm (got | tgt):
    [ 0] addiu sp,sp,-24              | addiu sp,sp,-24
!   [ 1] lui t0,0x8008                | lw v0,0(a0)
!   [ 2] lw v0,0(a0)                  | lui t0,0x8008
!   [ 3] addu v1,v0,a1                | addu a2,v0,a1
!   [ 4] ori a0,s1,0x30               | addiu a0,s1,48  raw 0x30002436 vs 0x30002426
!   [ 5] sll v0,v0,0x2                | jr ra
!   [ 6] jr ra                        | nop
!   [ 7] nop                          |
"""

DAP_ASM = """\t.ent\tf
f:
\tsubu\t$sp,$sp,24  # 5 subsi3_internal
\tlw\t$2,0($4)  # 7 movsi_internal2/5
\t#nop
\tli\t$8,528482304\t\t\t# 0x1f800000  # 9 movsi_internal2/3
\tli\t$9,0x12345678  # 10 movsi_internal2/3
\tlw\t$3,gameWork  # 11 movsi_internal2/5
\tj\t$31  # 12 return_internal
\t.end\tf
"""
DAP_GEN = [(0, "addiu sp,sp,-24"), (1, "lw v0,0(a0)"), (2, "nop"), (3, "lui t0,0x1f80"), (4, "lui t1,0x1234"),
           (5, "ori t1,t1,0x5678"), (6, "lui v1,0x8008"), (7, "lw v1,1234(v1)"), (8, "jr ra"), (9, "nop")]

FLOW = """(insn 30 0 31 (set (reg/v:SI 95) (const_int 528482304)) -1 (nil) (nil))
(insn 31 30 32 (set (reg:SI 5 a1) (plus:SI (reg/v:SI 95) (const_int 48))) -1 (insn_list 30 (nil)) (nil))
(insn 40 31 41 (set (reg/v:SI 96) (const_int 16)) -1 (nil) (nil))
(insn 41 40 42 (set (reg/v:SI 96) (reg:SI 2 v0)) -1 (nil) (nil))
(insn 42 41 43 (set (reg:SI 6 a2) (plus:SI (reg/v:SI 96) (const_int 1))) -1 (nil) (nil))
"""
COMBINE = """(insn 31 30 42 (set (reg:SI 5 a1) (ior:SI (reg/v:SI 95) (const_int 48))) -1 (insn_list 30 (nil)) (nil))
(insn 42 31 43 (set (reg:SI 6 a2) (ior:SI (reg/v:SI 96) (const_int 1))) -1 (nil) (nil))
"""

import sched_trace as ST                                                  # noqa: E402
import retailmap as RM                                                    # noqa: E402
import why as WY                                                          # noqa: E402
import checks as CK                                                       # noqa: E402


class TestBlockTraces(unittest.TestCase):
    def setUp(self):
        self.b = ST.block_traces(SCHED2)[0]
        self.t = {t["t"]: t for t in self.b["ticks"]}

    def test_block_priorities_and_total(self):
        self.assertEqual((self.b["function"], self.b["n"], self.b["total"]), ("f", 0, 7))
        self.assertEqual(self.b["prio"][16], (2147483390, 0))

    def test_hazard_line_carries_the_final_order(self):
        t = self.t[3]
        self.assertEqual((t["sorted"], t["now"], t["pick"], t["hazard"]), ([12, 11, 13], [11, 12, 13], 11, 11))

    def test_all_blocked_tick_has_no_pick_and_launch_joins_next_tick(self):
        self.assertEqual((self.t[5]["pick"], self.t[5]["blocked"]), (None, [(13, 1)]))
        self.assertEqual(self.t[6]["launched"], [(13, 0)])
        self.assertEqual(self.b["launches"][0], {"uid": 13, "before": 12, "stalls": 0, "t": 6})

    def test_mode_insns_only_with_modes(self):
        self.assertNotIn(12, [x["uid"] for x in ST.instructions(SCHED2)])          # historical reading kept
        self.assertIn(12, [x["uid"] for x in ST.instructions(SCHED2, modes=True)])


class TestPickReason(unittest.TestCase):
    def setUp(self):
        self.b = ST.block_traces(SCHED2)[0]
        self.t = {t["t"]: t for t in self.b["ticks"]}
        self.recs = {x["uid"]: x for x in WY.insns_of(SCHED2, True)}
        self.luid = {x["uid"]: i for i, x in enumerate(WY.insns_of(GREG_PRE, True))}

    def reason(self, t, last=None, phase="sched2", luid=None):
        return WY.pick_reason(t, self.luid if luid is None else luid, self.recs, {}, last, phase)

    def test_labels(self):
        self.assertEqual(self.reason(self.t[1])[0], "sole")
        self.assertEqual(self.reason(self.t[2])[0], "LUID tie")          # 14 over 13, equal priority 1
        self.assertEqual(self.reason(self.t[3])[0], "hazard")
        self.assertIn("the sort had 12 first", self.reason(self.t[3])[1])
        self.assertEqual(self.reason(self.t[4])[0], "priority")
        self.assertEqual(self.reason(self.t[5])[0], "stall")
        self.assertEqual(self.reason(self.t[6])[0], "sole")

    def test_lower_luid_winner_is_class_or_stale_sort_and_names_the_link_fact(self):
        t = dict(self.t[2], now=[13, 14], pick=13)
        lab, why = WY.pick_reason(t, self.luid, self.recs, {16: [(14, "true")]}, 16, "sched2")
        self.assertEqual(lab, "class/stale-sort")
        self.assertIn("14 is a LOG_LINK of the last-scheduled 16", why)

    def test_unknown_luid_is_said(self):
        self.assertEqual(self.reason(self.t[2], luid={13: 0})[0], "tie")

    def test_launched_boost_only_in_sched1(self):
        recs = {x["uid"]: x for x in WY.insns_of(SCHED1, True)}
        t = ST.block_traces(SCHED1)[0]["ticks"][1]
        lab, why = WY.pick_reason(t, {}, recs, {}, 23, "sched")
        self.assertEqual(lab, "priority")
        self.assertIn("launched: birthing boost", why)
        self.assertTrue(WY.is_launched(21, 0x7f000001, recs, "sched"))
        self.assertFalse(WY.is_launched(21, 0x7f000001, recs, "sched2"))
        self.assertFalse(WY.is_launched(16, 0x7ffffefe, self.recs, "sched"))      # a jump is tail, not launched

    def test_loss_reasons(self):
        self.assertEqual(WY.loss_reason(self.t[3], 13, self.luid), "priority 2 > 1")
        self.assertTrue(WY.loss_reason(self.t[3], 12, self.luid).startswith("potential hazard"))
        self.assertTrue(WY.loss_reason(self.t[2], 13, self.luid).startswith("LUID tie"))
        self.assertTrue(WY.loss_reason(self.t[5], 13, self.luid).startswith("blocked for 1"))


class TestTraceCli(unittest.TestCase):
    def setUp(self):
        self.blocks = ST.block_traces(SCHED2)

    def test_resolve_block_forms(self):
        self.assertEqual(WY.resolve_block(self.blocks, "13")[1], "insn uid 13")
        self.assertIn("read as basic block number 0", WY.resolve_block(self.blocks, "0")[1])
        self.assertEqual(WY.resolve_block(self.blocks, "b0")[0]["n"], 0)
        self.assertIn("retail word [4] = insn uid 12", WY.resolve_block(self.blocks, "r4", {4: 12})[1])
        with self.assertRaises(SystemExit):
            WY.resolve_block(self.blocks, "r4")                   # exact text: no retail listing
        with self.assertRaises(SystemExit):
            WY.resolve_block(self.blocks, "b7")

    def test_insn_history(self):
        recs = {x["uid"]: x for x in WY.insns_of(SCHED2, True)}
        luid = {x["uid"]: i for i, x in enumerate(WY.insns_of(GREG_PRE, True))}
        out = "\n".join(WY.explain_trace({}, "sched2", self.blocks[0], recs, luid, "insn uid 13", insn=13))
        self.assertIn("its dependents (it becomes ready when the last of these is scheduled): 14 anti @T-2", out)
        self.assertIn("ready from T-2", out)
        self.assertIn("T-2   lost to 14: LUID tie", out)
        self.assertIn("T-5   lost to nothing (stall): blocked for 1 cycles", out)
        self.assertIn("T-6   PICKED  sole", out)

    def test_block_table_and_ticks_with_retail_columns(self):
        recs = {x["uid"]: x for x in WY.insns_of(SCHED2, True)}
        retail = {"by_uid": {12: [3]}, "gen_ret": {3: 1}, "note": "fixture"}
        out = WY.explain_trace({}, "sched2", self.blocks[0], recs, {}, "b0", retail=retail)
        head = next(l for l in out if l.startswith("pos"))
        self.assertIn("gen  retail", head)
        self.assertTrue(any(l.startswith("T-3   11     hazard") for l in out))

    def test_deps(self):
        out = "\n".join(WY.explain_deps({"sched2": SCHED2}, "sched2", 13, (1, 1)))
        self.assertIn("12   true", out)
        self.assertIn("14   anti", out)
        with self.assertRaises(SystemExit):
            WY.explain_deps({"sched2": SCHED2}, "sched2", 99)


class TestRetailMap(unittest.TestCase):
    def test_classify_labels_each_kind(self):
        rows = RM.scorer_rows(SCORER)
        self.assertEqual(len(rows), 8)
        self.assertEqual(rows[-1], (7, "nop", ""))
        regions, tot = RM.classify(rows)
        self.assertEqual(tot, {"ORDER": 1, "COLOUR": 1, "OPCODE": 1, "COUNT": 1})
        kinds = {x["kind"]: x for r in regions for x in r["items"]}
        self.assertEqual((kinds["COLOUR"]["got"], kinds["COLOUR"]["tgt"]), ("addu v1,v0,a1", "addu a2,v0,a1"))
        self.assertEqual((kinds["OPCODE"]["got"], kinds["OPCODE"]["tgt"]), ("ori a0,s1,0x30", "addiu a0,s1,48"))
        self.assertEqual((kinds["COUNT"]["got"], kinds["COUNT"]["ret"]), ("sll v0,v0,0x2", None))

    def test_moved_instruction_keeps_its_text_and_drift(self):
        m, _regions, moved = RM.align(RM.scorer_rows(SCORER))
        self.assertEqual(len(moved), 1)
        g, r = next(iter(moved.items()))
        self.assertEqual({g, r}, {1, 2})
        self.assertEqual((RM.drift_at(m, moved, 0), RM.drift_at(m, moved, 6)), (0, -1))   # sll inserted before jr

    def test_branch_targets_and_colour_key(self):
        self.assertEqual(RM.mask("bnez v0,0x8001f0"), "bnez v0,TGT")
        self.assertEqual(RM.colour_key("lw s1,4(sp)"), RM.colour_key("lw s3,4(sp)"))
        self.assertNotEqual(RM.colour_key("lw s1,4(sp)"), RM.colour_key("lw s1,4(gp)"))

    def test_uid_map_expands_macros(self):
        by_uid, by_gen, cov = RM.uid_map(DAP_ASM, DAP_GEN)
        self.assertEqual(by_uid, {5: [0], 7: [1], 9: [3], 10: [4, 5], 11: [6, 7], 12: [8]})
        self.assertEqual(by_gen[7], 11)
        self.assertEqual(cov, (9, 9, 10))

    def test_classify_lines_on_match(self):
        out = D.classify_lines("MATCH func_80000000 2.7.2-G0\n", "2.7.2-G0", "v1")
        self.assertIn("nothing to classify", out[0])
        out = D.classify_lines(SCORER, "2.7.2-G0", "v1")
        self.assertIn("ORDER 1, COLOUR 1, OPCODE 1, COUNT 1", out[0])

    def test_diff_classify_needs_scorer(self):
        with self.assertRaises(SystemExit):
            D.main(["dungeon/func_80000000", "pinned", "--classify"])


class TestChecks(unittest.TestCase):
    ROW = {"func": "f"}

    def test_const_base(self):
        self.assertEqual(CK.const_base(FLOW, COMBINE, 31), {"base": 95, "value": 528482304, "sets": 1, "c": 48})
        v, ev = CK.check_const_base({"flow": FLOW, "combine": COMBINE}, 31, "ori a1,s1,0x30", "addiu a1,s1,48")
        self.assertEqual(v, "OPAQUE-BASE")
        self.assertIn("pseudo 95 has ONE set, from const_int 0x1f800000", ev)
        v, ev = CK.check_const_base({"flow": FLOW, "combine": COMBINE}, 42, "ori a2,s2,0x1", "addiu a2,s2,1")
        self.assertEqual(v, "UNKNOWN")
        self.assertIn("2 set(s)", ev)
        self.assertIsNone(CK.check_const_base({}, 31, "addu a1,s1,v0", "addiu a1,s1,48"))

    def test_barrier(self):
        p = CK.Pass({"sched2": SCHED2, "greg": GREG_PRE}, "sched2", self.ROW)
        v, ev = CK.check_barrier(p, 13)
        self.assertEqual(v, "BARRIER-GOVERNED")
        self.assertIn("volatile asm 14; insn 13 is before 14 (direct LOG_LINK with 14)", ev)
        p1 = CK.Pass({"sched": SCHED1.replace("asm_operands/v", "asm_operands")}, "sched", self.ROW)
        self.assertIsNone(CK.check_barrier(p1, 20))

    def test_sole_ready(self):
        p = CK.Pass({"sched2": SCHED2, "greg": GREG_PRE}, "sched2", self.ROW)
        self.assertEqual(CK.check_sole_ready(p, 10, "earlier")[0], "NOT-REORDERABLE")     # sole at T-7
        self.assertEqual(CK.check_sole_ready(p, 14, "earlier")[0], "REORDERABLE")         # LUID tie at T-2
        v, ev = CK.check_sole_ready(p, 13, "later")
        self.assertEqual(v, "REORDERABLE")
        self.assertIn("lost a LUID tie to 14 at T-2", ev)
        self.assertIsNone(CK.check_sole_ready(p, 13, None))

    def test_launched_vs_early_group(self):
        p = CK.Pass({"sched": SCHED1, "combine": COMBINE_PRE}, "sched", self.ROW)
        gen = {22: 0, 20: 1, 21: 2}
        ret = {20: 0, 22: 1, 21: 2}
        v, ev = CK.check_launched(p, 20, gen.get, ret.get)
        self.assertEqual(v, "NOT-REORDERABLE")
        self.assertIn("no non-launched consumer of 20 has a LUID below 22 (consumers: 21*, 23", ev)
        early = COMBINE_PRE.replace("(insn 22 20 21", "(insn 99 0 0").replace("(insn 23 21 24", "(insn 23 0 0")
        early = early.replace("(insn 99 0 0", "(insn 22 20 21")
        lines = early.splitlines()
        p2 = CK.Pass({"sched": SCHED1, "combine": "\n".join([lines[0], lines[3], lines[1], lines[2]])}, "sched", self.ROW)
        self.assertEqual(CK.check_launched(p2, 20, gen.get, ret.get)[0], "REORDERABLE")   # 23 now below 22
        self.assertIsNone(CK.check_launched(p, 21, gen.get, ret.get))                   # no inversion


if __name__ == "__main__":
    unittest.main()
