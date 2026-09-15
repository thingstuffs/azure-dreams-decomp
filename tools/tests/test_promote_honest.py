"""The honest-C promotion plan: what a row needs before its pack can land at the true base.

    python3 -m unittest tools/tests/test_promote_honest.py

Synthetic inputs only (no compiler, no writes): the mate verifier is injected.
"""
import importlib.util
import json
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
_spec = importlib.util.spec_from_file_location("promote_honest", ROOT / "tools/lanes/promote_honest.py")
ph = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(ph)

CAND = "/tmp/out/dungeon/func_81814EDC.c"


def info(**kw):
    base = dict(id="dungeon/func_81814EDC", lane="lac1", cand=CAND, family="dungeon",
                func="func_81814EDC", foff=0x1834EDC, region="row_1834edc_800246dc", conf="proven",
                expected="func_800246DC", true_name="func_800246DC", cfg="2.7.2-cdk-G0",
                filter="ok", as_flags_missing=False)
    base.update(kw)
    return base


def mate(rid="dungeon/func_818FEDEC", func="func_818FEDEC", true_name=None, expected="func_800245EC"):
    return info(id=rid, func=func, true_name=true_name, expected=expected, cand=None, lane=None,
                row={"id": rid, "container": "dungeon", "func": func})


EXACT = lambda m: {"exact": True}
INEXACT = lambda m: {"exact": False, "result": "aligned 6"}


class PlanRow(unittest.TestCase):
    def test_done_row_needs_nothing(self):
        st, steps, note = ph.plan_row(info())
        self.assertEqual((st, steps), ("OK", []))
        self.assertIn("nothing to do (proven", note)

    def test_done_row_reports_a_blocking_filter_but_stays_ok(self):
        st, _steps, note = ph.plan_row(info(filter="stale base"))
        self.assertEqual(st, "OK")
        self.assertIn("stale base", note)

    def test_no_region_is_out_of_scope(self):
        st, steps, note = ph.plan_row(info(region=None, conf=None, expected=None, true_name=None))
        self.assertEqual((st, steps, note), ("SKIP", [], "no rowbase region"))

    def test_solved_single_row_region_promotes_and_registers(self):
        st, steps, _n = ph.plan_row(info(conf="solved", true_name=None))
        self.assertEqual(st, "DO")
        self.assertEqual([s[0] for s in steps], ["promote", "register"])
        self.assertEqual(steps[0], ("promote", "dungeon", "func_81814EDC", CAND, "2.7.2-cdk-G0",
                                    "row_1834edc_800246dc"))
        self.assertEqual(steps[1], ("register", "dungeon", "func_81814EDC", "func_800246DC"))

    def test_proven_region_only_registers(self):
        st, steps, _n = ph.plan_row(info(true_name=None))
        self.assertEqual((st, [s[0] for s in steps]), ("DO", ["register"]))

    def test_true_name_equal_to_the_synthetic_name_is_a_placeholder(self):
        st, steps, _n = ph.plan_row(info(true_name="func_81814EDC"))
        self.assertEqual((st, [s[0] for s in steps]), ("DO", ["register"]))

    def test_unrelated_true_name_is_refused(self):
        st, steps, note = ph.plan_row(info(true_name="func_DEADBEEF"))
        self.assertEqual((st, steps), ("REFUSE", []))
        self.assertIn("func_DEADBEEF", note)

    def test_as_flags_record_without_true_name_is_dialled_across(self):
        st, steps, _n = ph.plan_row(info(as_flags_missing=True))
        self.assertEqual((st, steps), ("DO", [("as_flags", "dungeon", "func_81814EDC", "func_800246DC")]))

    def test_as_flags_record_with_true_name_needs_nothing(self):
        self.assertEqual(ph.plan_row(info(as_flags_missing=False))[0], "OK")

    def test_blocking_filter_blocks_work(self):
        st, steps, note = ph.plan_row(info(conf="solved", true_name=None, filter="pins not lower 9 -> 9"))
        self.assertEqual((st, steps, note), ("SKIP", [], "pins not lower 9 -> 9"))

    def test_landed_candidate_may_still_promote(self):
        self.assertEqual(ph.plan_row(info(conf="solved", true_name=None, filter="landed"))[0], "DO")

    def test_shared_solved_region_is_skipped_without_decision_b(self):
        st, steps, note = ph.plan_row(info(conf="solved", true_name=None), mates=[mate()])
        self.assertEqual((st, steps), ("SKIP", []))
        self.assertIn("shared region row_1834edc_800246dc holds dungeon/func_818FEDEC", note)

    def test_shared_proven_region_registers_without_touching_the_mates(self):
        # promotion is the rename event; registering one row's name in a proven region is local.
        st, steps, _n = ph.plan_row(info(true_name=None), mates=[mate()])
        self.assertEqual((st, [s[0] for s in steps]), ("DO", ["register"]))

    def test_decision_b_registers_every_exact_mate(self):
        st, steps, note = ph.plan_row(info(conf="solved", true_name=None), mates=[mate()],
                                      decision_b=True, verify_fn=EXACT)
        self.assertEqual((st, [s[0] for s in steps]), ("DO", ["promote", "register", "register"]))
        self.assertEqual(steps[2], ("register", "dungeon", "func_818FEDEC", "func_800245EC"))
        self.assertIn("1 mate(s) exact", note)

    def test_decision_b_skips_a_mate_that_is_not_exact_and_names_it(self):
        st, steps, note = ph.plan_row(info(conf="solved", true_name=None), mates=[mate()],
                                      decision_b=True, verify_fn=INEXACT)
        self.assertEqual((st, steps), ("SKIP", []))
        self.assertIn("dungeon/func_818FEDEC", note)
        self.assertIn("aligned 6", note)

    def test_decision_b_does_not_re_register_a_mate_already_registered(self):
        m = mate(true_name="func_800245EC")
        st, steps, _n = ph.plan_row(info(conf="solved", true_name=None), mates=[m],
                                    decision_b=True, verify_fn=EXACT)
        self.assertEqual((st, [s[0] for s in steps]), ("DO", ["promote", "register"]))

    def test_decision_b_refuses_a_mate_with_an_unrelated_true_name(self):
        m = mate(true_name="func_DEADBEEF")
        st, steps, note = ph.plan_row(info(conf="solved", true_name=None), mates=[m],
                                      decision_b=True, verify_fn=EXACT)
        self.assertEqual((st, steps), ("SKIP", []))
        self.assertIn("func_DEADBEEF", note)


class Describe(unittest.TestCase):
    def test_plan_column(self):
        st, steps, note = ph.plan_row(info(conf="solved", true_name=None, as_flags_missing=True),
                                      mates=[mate()], decision_b=True, verify_fn=EXACT)
        self.assertEqual(st, "DO")
        self.assertEqual(ph.describe(steps, note),
                         "promote row_1834edc_800246dc, register func_800246DC, as_flags func_800246DC, "
                         "register func_800245EC [decision B: 1 mate(s) exact]")

    def test_unresolved_rows_land_lanes_would_still_land(self):
        shared = info(id="dungeon/a", conf="solved", true_name=None)
        stale = info(id="dungeon/b", conf="solved", true_name=None, filter="stale base")
        noreg = info(id="dungeon/c", region=None, conf=None, expected=None, true_name=None)
        done = info(id="dungeon/d")
        plans = [(i, ph.plan_row(i, mates=[mate()] if i is shared else []))
                 for i in (shared, stale, noreg, done)]
        self.assertEqual([p[1][0] for p in plans], ["SKIP", "SKIP", "SKIP", "OK"])
        self.assertEqual(ph.unresolved(plans), ["dungeon/a"])

    def test_plan_column_of_a_row_with_nothing_to_do(self):
        self.assertEqual(ph.describe([], "nothing to do (proven, true name x)"),
                         "nothing to do (proven, true name x)")


class FilterAndFiles(unittest.TestCase):
    def test_filter_statuses(self):
        import hashlib
        import tempfile
        with tempfile.TemporaryDirectory() as d:
            f = Path(d) / "func_1.c"
            cur = "void f(void) { ASM_KEEP(a); ASM_KEEP(b); }\n"
            f.write_text(cur)
            Path(str(f) + ".base_sha").write_text(hashlib.sha256(cur.encode()).hexdigest() + "\n")
            self.assertEqual(ph.filter_status(f, cur, cur), "landed")
            self.assertEqual(ph.filter_status(f, "void f(void) { ASM_KEEP(a); }\n", cur), "ok")
            self.assertTrue(ph.filter_status(f, "void f(void) { ASM_KEEP(a); }\n", cur + "\n")
                            .startswith("stale base"))
            grew = "void f(void) { ASM_KEEP(a); ASM_KEEP(b); volatile int x; }\n"
            self.assertTrue(ph.filter_status(f, grew, cur).startswith("scaffolding grew"))
            same = cur.replace("ASM_KEEP(b)", "ASM_KEEP(c)")   # same pin count, different text
            self.assertEqual(ph.filter_status(f, same, cur), "pins not lower 2 -> 2")

    def test_set_true_name_preserves_the_record_and_its_neighbours(self):
        import tempfile
        other = json.dumps({"func_vram": "func_7FFE7800", "result": "data"}, separators=(",", ":"))
        rec = {"func_vram": "func_81814EDC", "vram": 1, "result": "MATCH", "config": "2.7.2-cdk-G0"}
        with tempfile.TemporaryDirectory() as d:
            (Path(d) / "ledger/splits").mkdir(parents=True)
            p = Path(d) / "ledger/splits/dungeon.jsonl"
            p.write_text(other + "\n" + json.dumps(rec, separators=(",", ":")) + "\n")
            old_root = ph.ROOT
            try:
                ph.ROOT = Path(d)
                self.assertEqual(ph.set_true_name("dungeon", "func_81814EDC", "func_800246DC"), "set")
                self.assertEqual(ph.set_true_name("dungeon", "func_81814EDC", "func_800246DC"), "already")
                with self.assertRaises(SystemExit):
                    ph.set_true_name("dungeon", "func_81814EDC", "func_DEADBEEF")
                with self.assertRaises(SystemExit):
                    ph.set_true_name("dungeon", "func_NOTHERE", "func_1")
            finally:
                ph.ROOT = old_root
            lines = p.read_text().splitlines()
            self.assertEqual(lines[0], other)                      # unrelated line byte-identical
            got = json.loads(lines[1])
            self.assertEqual(list(got)[:2], ["func_vram", "true_name"])
            self.assertEqual(got["true_name"], "func_800246DC")
            self.assertEqual({k: got[k] for k in rec}, rec)        # every other field preserved

    def test_set_as_flags_true_name_rewrites_one_line_only(self):
        rec = {"schema": "azure-clean.overlay-asflags.v1", "func": "func_80614B88",
               "as_flags": "--aspsx-version=2.60", "proof": "x"}
        other = json.dumps({"schema": "s", "func": "func_1", "true_name": "func_2"}, separators=(",", ":"))
        import tempfile
        with tempfile.TemporaryDirectory() as d:
            fam_dir = Path(d) / "config/overlays"
            fam_dir.mkdir(parents=True)
            p = fam_dir / "town.as_flags.jsonl"
            p.write_text(other + "\n" + json.dumps(rec, separators=(",", ":")) + "\n")
            old_root = ph.ROOT
            try:
                ph.ROOT = Path(d)
                self.assertTrue(ph.as_flags_missing("town", "func_80614B88"))
                self.assertFalse(ph.as_flags_missing("town", "func_1"))
                self.assertEqual(ph.set_as_flags_true_name("town", "func_80614B88", "func_80507788"), "set")
                self.assertEqual(ph.set_as_flags_true_name("town", "func_nope", "func_x"), "absent")
            finally:
                ph.ROOT = old_root
            lines = p.read_text().splitlines()
            self.assertEqual(lines[0], other)
            got = json.loads(lines[1])
            self.assertEqual(list(got), ["schema", "func", "true_name", "as_flags", "proof"])
            self.assertEqual(got["true_name"], "func_80507788")
            self.assertEqual(got["proof"], "x")


if __name__ == "__main__":
    unittest.main()
