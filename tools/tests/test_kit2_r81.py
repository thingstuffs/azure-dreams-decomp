"""Round-81 kit wishes (r81_opus_kit2, from the r81_fable_eqv / r81_fable_late retrospectives):
`kitlib.score_at(diff=True)` returns the score AND the listing; `why.py <row> <text> --cfg A --vs-cfg B`;
`lab.py stage-cell --equal-pins`; `erase_census.py --full-diff`; diff.py journals to lab_log.jsonl and
`lab.py report` shows it (`kitlib.record_score`).  No compiles, no scorer, no real lane: `verify` and the
dumps are fakes and `kitlib.bootstrap` is never called (it would install the Popen shim for the whole run)."""
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
import why as W                                                           # noqa: E402
import erase_census as EC                                                 # noqa: E402

ROW = {"id": "dungeon/func_80000000", "func": "func_80000000", "container": "dungeon",
       "c_path": "src/dungeon/func_80000000.c", "cfg": "2.8.0-G0", "cell": "2.8.0",
       "flags": "-G0", "kind": "overlay"}
PINNED = "void f(void) {\n    int a;\n    ASM_KEEP(a);\n    g(a);\n}\n"
FREE = "void f(void) {\n    int a;\n    g(a);\n}\n"
# the same pin count as PINNED, a different text (the fc4 819C04E8 shape: exact at cdk at equal pins)
SAME_PINS = "void f(void) {\n    int a;\n    ASM_KEEP(a);\n    g(a + 0);\n}\n"


def fake_verify(exact_for):
    calls = []

    def verify(row, f, include_root=None, diff=False):
        calls.append((dict(row), diff))
        t = Path(f).read_text()
        if diff:
            return {"status": "diff", "text": "[   0] lw $2,0($4) | lw $3,0($4)\nTEXT OF " + t[:10], "secs": 1}
        ok = t in exact_for
        return {"exact": ok, "total": 0 if ok else 7, "subs": 0 if ok else 5, "indels": 0 if ok else 2,
                "status": "ok", "class": None if ok else "x"}
    return verify, calls


# ---------------------------------------------------------------------------------------- (1)

class ScoreAtDiff(unittest.TestCase):
    def test_diff_true_returns_score_fields_and_the_listing(self):
        verify, calls = fake_verify(set())
        v = kitlib.score_at(ROW, FREE, verify=verify, diff=True)
        self.assertEqual(kitlib.score_fields(v), {"exact": False, "total": 7, "subs": 5, "indels": 2, "status": "ok"})
        self.assertTrue(v["text"].startswith("[   0] lw $2"))
        self.assertEqual(v["diff_status"], "diff")
        self.assertEqual(sorted(d for _, d in calls), [False, True])       # one summary + one diff run

    def test_diff_true_at_another_cfg_scores_both_runs_there(self):
        verify, calls = fake_verify({FREE})
        v = kitlib.score_at(ROW, FREE, cfg="2.7.2-cdk-G0", verify=verify, diff=True)
        self.assertTrue(v["exact"])
        self.assertTrue(all(r["cfg"] == "2.7.2-cdk-G0" and r["cell"] == "2.7.2-cdk" for r, _ in calls))

    def test_plain_score_is_one_call_without_text(self):
        verify, calls = fake_verify({FREE})
        v = kitlib.score_at(ROW, FREE, verify=verify)
        self.assertEqual((len(calls), v["exact"], "text" in v), (1, True, False))


# ---------------------------------------------------------------------------------------- (2)

GREG_280 = """;; 206 conflicts: 80 86
;; Need 1 reg of class GR_REGS (for insn 24).
;; Need 1 reg of class HI_REG (for insn 141).
;; Need 2 regs of class MD_REGS (for insn 144).
Spilling reg 9.
Spilling reg 64.
 Register 133 now in 3.

Spilling reg 66.
;; Need 1 reg of class GR_REGS (for insn 24).
;; Need 2 regs of class MD_REGS (for insn 141).
Spilling reg 9.
;; Register dispositions:
"""
GREG_CDK = """;; Need 1 reg of class GR_REGS (for insn 24).
;; Need 1 reg of class MD_REGS (for insn 168).
Spilling reg 9.
Spilling reg 65.
"""
GREG_EGCS = """Spilling for insn 37.
Spilling reg 2.
Spilling for insn 40.
Spilling reg 3.
"""


class WhyTwoCfgs(unittest.TestCase):
    def test_reload_rounds(self):
        rs = W.reload_rounds(GREG_280)
        self.assertEqual(len(rs), 2)
        self.assertEqual(rs[0]["need"], [(1, "GR_REGS", 24), (1, "HI_REG", 141), (2, "MD_REGS", 144)])
        self.assertEqual(rs[0]["spill"], [9, 64, 66])            # `Register N now in R` lines between do not split
        self.assertEqual(rs[1], {"need": [(1, "GR_REGS", 24), (2, "MD_REGS", 141)], "spill": [9]})

    def test_explain_reload_identical_ignores_insn_uids_and_names_a_difference(self):
        same = W.explain_reload({"greg": GREG_CDK}, {"greg": GREG_CDK.replace("168", "141")}, ("A", "B"))
        self.assertIn("IDENTICAL", same[1])
        diff = W.explain_reload({"greg": GREG_280}, {"greg": GREG_CDK}, ("A", "B"))
        self.assertIn("DIFFERENT", diff[1])
        self.assertIn("round 1: need 1 GR_REGS (insn 24), 1 MD_REGS (insn 168) -> spill 9, 65", "\n".join(diff))
        egcs = W.explain_reload({"greg": GREG_EGCS}, {"greg": GREG_CDK}, ("A", "B"))
        self.assertIn("no `;; Need` lines (egcs-style per-insn reload): 2 `Spilling reg` lines, registers 2, 3",
                      "\n".join(egcs))
        self.assertEqual(W.explain_reload({"greg": ""}, {}, ("A", "B")), [])

    def test_alloc_pair_reads_each_side_at_its_own_cell(self):
        seen = []

        def fake_read(d, row, text):
            seen.append(row["cfg"])
            return "no-first-pseudo:2.95.2" if row["cfg"].startswith("2.95.2") else {"ok": 1}
        ra, rb = kitlib.row_at_cfg(ROW, "2.95.2-G0"), kitlib.row_at_cfg(ROW, "2.7.2-cdk-G0")
        with mock.patch.object(W, "alloc_read", fake_read):
            _, _, bad = W.alloc_pair({}, {}, ROW, ("t", "t"), rows=(ra, rb))
            self.assertEqual(seen, ["2.95.2-G0", "2.7.2-cdk-G0"])
            self.assertEqual(len(bad), 1)
            self.assertTrue(bad[0].startswith("[2.95.2-G0] why:"))
            seen.clear()
            W.alloc_pair({}, {}, ROW, ("t", "t"))                 # two texts, one cfg: the one row twice
            self.assertEqual(seen, ["2.8.0-G0", "2.8.0-G0"])

    def test_pass_summary_masks_pseudos_and_names_the_first_differing_pass(self):
        rtl_a = "(insn 5 4 6 (set (reg:SI 80) (reg:SI 4 a0)) -1 (nil)\n    (nil))\n"
        # one extra pseudo up front shifts every first-appearance name; masked, only the real change counts
        rtl_b = ("(insn 3 2 5 (set (reg:SI 90) (const_int 0)) -1 (nil)\n    (nil))\n"
                 "(insn 5 3 6 (set (reg:SI 91) (reg:SI 4 a0)) -1 (nil)\n    (nil))\n")
        out = "\n".join(W.pass_summary({"rtl": rtl_a, "jump": rtl_a}, {"rtl": rtl_b, "jump": rtl_a}, ("A", "B")))
        self.assertIn("first pass whose insn stream differs: rtl", out)
        self.assertRegex(out, r"jump\s+1\s+1\s+0\s+same")
        same = "\n".join(W.pass_summary({"rtl": rtl_a}, {"rtl": rtl_a}, ("A", "B")))
        self.assertIn("differs: none", same)

    def _main(self, *argv):
        err = io.StringIO()
        with mock.patch.object(sys, "argv", ["why.py", *argv]), mock.patch("sys.stderr", err), \
                mock.patch.object(kitlib, "bootstrap", side_effect=AssertionError("bootstrap reached")):
            with self.assertRaises(SystemExit):
                W.main()
        return err.getvalue()

    def test_cli_refusals(self):
        self.assertIn("--vs-cfg compares whole compiles",
                      self._main("a/b", "--vs-cfg", "2.7.2-cdk-G0", "--pass", "sched2", "--trace", "--block", "1"))
        self.assertIn("not --vs", self._main("a/b", "cand.c", "--vs-cfg", "2.7.2-cdk-G0", "--vs", "erased"))
        self.assertIn("--pass is required", self._main("a/b"))
        self.assertIn("give the text once", self._main("a/b", "x.c", "--variant", "y.c", "--pass", "greg"))

    def test_cli_vs_cfg_without_pass_reaches_the_lane(self):
        # `--pass` is optional with --vs-cfg: argument checks pass and the tool goes on to bootstrap
        with mock.patch.object(sys, "argv", ["why.py", "a/b", "erased", "--vs-cfg", "2.7.2-cdk-G0"]), \
                mock.patch.object(kitlib, "bootstrap", side_effect=RuntimeError("bootstrap reached")):
            with self.assertRaisesRegex(RuntimeError, "bootstrap reached"):
                W.main()


# ---------------------------------------------------------------------------------------- (3)

class StageCellEqualPins(unittest.TestCase):
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

    def run_sc(self, cand, exact_for, equal_pins):
        verify, _ = fake_verify(exact_for)
        lines = []
        rec = L.stage_cell(ROW, cand, self.CFG, "mechanism X", self.lane, self.bp, PINNED, name="v",
                           verify=verify, out=lines.append, equal_pins=equal_pins)
        return rec, "\n".join(lines)

    def cells(self):
        return [json.loads(l) for l in (self.lane / "cells.jsonl").read_text().splitlines()]

    def test_admissible_equal_pins_waives_only_the_fewer_pins_rule(self):
        self.assertTrue(kitlib.admissible(PINNED, SAME_PINS))
        self.assertEqual(kitlib.admissible(PINNED, SAME_PINS, equal_pins=True), [])
        self.assertEqual(kitlib.admissible(PINNED, PINNED, equal_pins=True), [])
        more = PINNED.replace("g(a);", "ASM_KEEP(a);\n    g(a);")
        self.assertTrue(kitlib.admissible(PINNED, more, equal_pins=True))
        other = PINNED.replace("ASM_KEEP(a)", "ASM_KEEP(b)")          # same count, a pin the base did not have
        self.assertTrue(any("did not have" in b for b in kitlib.admissible(PINNED, other, equal_pins=True)))
        vol = SAME_PINS.replace("int a;", "volatile int a;")
        self.assertTrue(any("volatile" in b for b in kitlib.admissible(PINNED, vol, equal_pins=True)))
        gt = SAME_PINS.replace("g(a + 0);", "goto x;\nx:\n    g(a + 0);")
        self.assertTrue(any("goto" in b for b in kitlib.admissible(PINNED, gt, equal_pins=True)))

    def test_equal_pins_without_the_flag_is_refused_with_a_hint(self):
        rec, _ = self.run_sc(SAME_PINS, {SAME_PINS}, False)
        self.assertIn("not admissible", rec["refused"])
        self.assertIn("--equal-pins", rec["refused"])
        self.assertFalse((self.lane / "cells.jsonl").exists())

    def test_pure_recipe_switch_stages_as_recipe_switch_for_land_recipe_move(self):
        rec, out = self.run_sc(PINNED, {PINNED}, True)
        self.assertNotIn("refused", rec)
        c = self.cells()[0]
        self.assertEqual((c["kind"], c["rule2"], c["pins_before"], c["pins_after"]), ("recipe-switch", True, 1, 1))
        self.assertIn("tools/fidelity/land_recipe_move.py", rec["lander"])
        self.assertIn("PURE recipe switch", out)
        self.assertEqual((self.lane / "out/dungeon/func_80000000.c").read_text(), PINNED)

    def test_equal_pins_new_text_rule2_false_is_a_coherence_move_for_land_coherence(self):
        rec, out = self.run_sc(SAME_PINS, {SAME_PINS}, True)
        c = self.cells()[0]
        self.assertEqual((c["kind"], c["rule2"]), ("coherence", False))
        self.assertIn("land_coherence.sh", rec["lander"])
        self.assertIn("[equal pins 1 -> 1]", out)
        self.assertTrue(rec["equal_pins"])

    def test_equal_pins_new_text_rule2_true_is_a_recipe_switch(self):
        rec, _ = self.run_sc(SAME_PINS, {SAME_PINS, PINNED}, True)
        self.assertEqual(self.cells()[0]["kind"], "recipe-switch")

    def test_flag_does_not_stage_an_inexact_or_more_pinned_candidate(self):
        rec, _ = self.run_sc(SAME_PINS, set(), True)
        self.assertIn("not exact", rec["refused"])
        more = PINNED.replace("g(a);", "ASM_KEEP(a);\n    g(a);")
        rec, _ = self.run_sc(more, {more}, True)
        self.assertIn("not admissible", rec["refused"])

    def test_fewer_pins_is_unchanged_by_the_flag(self):
        rec, _ = self.run_sc(FREE, {FREE}, True)
        self.assertEqual((self.cells()[0]["pins_after"], self.cells()[0]["kind"]), (0, "coherence"))
        self.assertIn("land_coherence.sh", rec["lander"])


# ---------------------------------------------------------------------------------------- (7)

class EraseCensusFullDiff(unittest.TestCase):
    REF = ["lw $2,0($4)", "addu $2,$2,$5", "jr $31"]

    def test_diff_keep(self):
        self.assertIsNone(EC.diff_keep(None, 4, True))              # does not build: never a diff
        self.assertEqual(EC.diff_keep(300, -1, True), 0)            # full: every site, every line
        self.assertEqual(EC.diff_keep(3, 4, False), EC.DIFF_CAP)    # --diff 4: near sites, capped
        self.assertIsNone(EC.diff_keep(5, 4, False))
        self.assertIsNone(EC.diff_keep(0, -1, False))               # flagless: no diff field (output unchanged)

    def test_changed_lines_cap_and_full(self):
        cand = ["x%d" % i for i in range(20)]
        full = EC.changed_lines(self.REF, cand, 0)
        self.assertEqual(len(full), 23)
        self.assertEqual(EC.changed_lines(self.REF, cand), full[:16])
        self.assertTrue(all(l[:1] in "+-" and not l.startswith(("---", "+++")) for l in full))

    def test_size_warning(self):
        with tempfile.NamedTemporaryFile() as f:
            f.write(b"x" * 100)
            f.flush()
            self.assertIsNone(EC.size_warning(f.name, limit=100))
            self.assertIn("MB", EC.size_warning(f.name, limit=99))
        self.assertIsNone(EC.size_warning("/nonexistent/x.jsonl"))

    def test_searched_work_path(self):
        self.assertFalse(EC.searched_work_path("/tmp/x.jsonl"))
        with tempfile.TemporaryDirectory() as td:
            work = Path(td) / "work"
            (work / "lane" / "a").mkdir(parents=True)
            self.assertTrue(EC.searched_work_path(work / "lane" / "a" / "x.jsonl", work=work))
            self.assertFalse(EC.searched_work_path(Path(td) / "elsewhere.jsonl", work=work))
            (work / "lane" / ".ignore").write_text("*\n")
            self.assertFalse(EC.searched_work_path(work / "lane" / "a" / "x.jsonl", work=work))
            (work / "lane" / ".ignore").unlink()
            (work / ".ignore").write_text("lane/\n")
            self.assertFalse(EC.searched_work_path(work / "lane" / "a" / "x.jsonl", work=work))
            self.assertTrue(EC.searched_work_path(work / "other" / "x.jsonl", work=work))

    def test_full_and_diff_n_are_exclusive(self):
        with tempfile.TemporaryDirectory() as td, \
                mock.patch.object(sys, "argv", ["erase_census.py", str(Path(td) / "x.jsonl"), "--full-diff", "--diff", "3"]), \
                mock.patch.object(EC, "Pool", side_effect=AssertionError("a census was started")):
            with self.assertRaisesRegex(SystemExit, "drop --diff N"):
                EC.main()


# ---------------------------------------------------------------------------------------- (8)

class JournalAndReport(unittest.TestCase):
    def test_record_score_and_report_via_column(self):
        with tempfile.TemporaryDirectory() as td:
            v = {"exact": False, "total": 12, "subs": 9, "indels": 3, "status": "ok", "text": "..."}
            r = kitlib.record_score(td, ROW, "sym4", v, "my_probe.py", cfg="2.7.2-cdk-G0", text=FREE)
            self.assertEqual((r["kind"], r["source"], r["status"], r["pins"], r["cfg"]),
                             ("score", "my_probe.py", "scored", 0, "2.7.2-cdk-G0"))
            self.assertEqual(r["score"]["total"], 12)
            f = kitlib.record_score(td, ROW, "nobuild", {"status": "failed", "exact": False, "err": "x"}, "p.py")
            self.assertEqual(f["status"], "failed")
            kitlib.log_append(td, {"row": ROW["id"], "variant": "v1", "distance": 3, "status": "measured"})
            out = L.report(td, ROW["id"])
        self.assertNotIn("ZERO MEASUREMENTS", out)
        self.assertIn("my_probe.py", out)
        self.assertIn("total 12 @2.7.2-cdk-G0", out)
        self.assertIn("lab.py", out)                                # a record without a source is lab.py's

    def test_repeated_identical_measurement_is_one_line(self):
        with tempfile.TemporaryDirectory() as td:
            for _ in range(3):
                kitlib.log_append(td, {"row": ROW["id"], "variant": "c", "kind": "diff-listing", "source": "diff.py",
                                       "distance": 4, "status": "measured", "score": None})
            out = L.report(td, ROW["id"])
        self.assertEqual(out.count("diff.py"), 1)
        self.assertIn("(x3)", out)

    def test_diff_records_do_not_count_toward_the_cap(self):
        recs = [{"row": "r", "variant": "a", "kind": k} for k in ("diff-listing", "diff-scorer", "diff-score", "baseline")]
        recs.append({"row": "r", "variant": "b"})
        self.assertEqual(kitlib.variant_count(recs, "r"), 1)

    def _diff_main(self, td, argv, verify_exact=False):
        v = {"exact": verify_exact, "total": 0 if verify_exact else 5, "subs": 3, "indels": 2, "status": "ok",
             "text": "  ! [   0] lw $2,0($4) | lw $3,0($4)\n    [   1] jr $31 | jr $31\n"}
        cand = Path(td) / "cand.c"
        cand.write_text(FREE)
        with mock.patch.object(kitlib, "bootstrap", return_value=Path(td)), \
                mock.patch.object(kitlib, "row_of", return_value=ROW), \
                mock.patch.object(kitlib, "base_text", return_value=PINNED), \
                mock.patch.object(kitlib, "score_at", return_value=v) as sa, \
                mock.patch.object(D, "run", return_value=(["--- pinned", "+++ cand", "-a", "+b"], 2)), \
                redirect_stdout(io.StringIO()) as so:
            D.main(["dungeon/func_80000000", str(cand)] + argv)
        return kitlib.log_read(td), so.getvalue(), sa

    def test_diff_scorer_is_journalled_with_its_score(self):
        with tempfile.TemporaryDirectory() as td:
            recs, out, sa = self._diff_main(td, ["--scorer"])
            self.assertEqual(sa.call_count, 1)
            self.assertIn('# score {"exact": false, "total": 5', out)
            self.assertEqual(len(recs), 1)
            r = recs[0]
            self.assertEqual((r["kind"], r["source"], r["variant"], r["score"]["total"]),
                             ("diff-scorer", "diff.py --scorer", "cand", 5))
            self.assertIn("diff.py --scorer", L.report(td, ROW["id"]))

    def test_diff_scorer_with_score_scores_once_and_logs_once(self):
        with tempfile.TemporaryDirectory() as td:
            recs, _, sa = self._diff_main(td, ["--scorer", "--score"])
            self.assertEqual((sa.call_count, len(recs)), (1, 1))

    def test_diff_listing_is_journalled_and_no_log_writes_nothing(self):
        with tempfile.TemporaryDirectory() as td:
            recs, _, _ = self._diff_main(td, [])
            self.assertEqual((recs[0]["kind"], recs[0]["distance"], recs[0]["source"]), ("diff-listing", 2, "diff.py"))
        with tempfile.TemporaryDirectory() as td:
            recs, _, sa = self._diff_main(td, ["--no-log", "--scorer"])
            self.assertEqual((recs, sa.call_count), ([], 1))

    def test_diff_score_is_journalled_once(self):
        with tempfile.TemporaryDirectory() as td:
            recs, _, _ = self._diff_main(td, ["--score"], verify_exact=True)
            self.assertEqual([(r["kind"], r["status"]) for r in recs], [("diff-score", "exact")])


if __name__ == "__main__":
    unittest.main()
