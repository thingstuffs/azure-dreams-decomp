"""Pure parts of the lane kit (tools/lanes/lanekit): the substitution helper, the admission gate,
the table formatter, the ledger accounting, the report shape, the scheduler-dump parser, the pseudo
anonymiser and the `--around` resolver, plus the shim's argv scan.  No compiles, no lane, and
nothing here imports `sitecustomize` (importing it would monkeypatch `subprocess.Popen` for every
other test in the run)."""
import json
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
KIT = ROOT / "tools/lanes/lanekit"
sys.path.insert(0, str(KIT))
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/xform"))
sys.path.insert(0, str(ROOT / "tools/lanes"))

import kitlib                                                             # noqa: E402
import lane_shim                                                          # noqa: E402
import erase as E                                                         # noqa: E402
import lab as L                                                           # noqa: E402
import why as W                                                           # noqa: E402
import install as I                                                       # noqa: E402


BASE = "\n".join([
    "void f(void) {",
    "    register s32 v ASM_REG(\"$19\") = x;",
    "    ASM_KEEP(node);",
    "    g(v);",
    "    g(v);",
    "}",
])


class TestRep(unittest.TestCase):
    def test_replaces_first_only(self):
        self.assertEqual(kitlib.rep("a b a", "a", "Z"), "Z b a")

    def test_miss_names_the_nearest_line(self):
        with self.assertRaises(KeyError) as cm:
            kitlib.rep(BASE, "ASM_KEEP(nodes);", "")
        msg = str(cm.exception)
        self.assertIn("pattern not in text", msg)
        self.assertIn("ASM_KEEP(node);", msg)

    def test_miss_with_nothing_close(self):
        with self.assertRaises(KeyError) as cm:
            kitlib.rep("aaaa", "zzzzzzzzzzzzzzzz", "")
        self.assertIn("nothing close", str(cm.exception))

    def test_apply_subs_in_order(self):
        out = kitlib.apply_subs("a b c", [["a", "x"], ["x b", "y"]])
        self.assertEqual(out, "y c")

    def test_apply_subs_label_in_message(self):
        with self.assertRaises(KeyError) as cm:
            kitlib.apply_subs("a", [["a", "b"], ["q", "r"]], label="shape3")
        self.assertIn("shape3[1]", str(cm.exception))


class TestAdmissible(unittest.TestCase):
    def test_clean_reduction_is_admissible(self):
        cand = BASE.replace("    ASM_KEEP(node);\n", "")
        self.assertEqual(kitlib.admissible(BASE, cand), [])

    def test_same_pin_count_refused(self):
        self.assertTrue(any("not reduced" in r for r in kitlib.admissible(BASE, BASE)))

    def test_new_volatile_refused(self):
        cand = BASE.replace("    ASM_KEEP(node);\n", "    volatile s32 w = 1;\n")
        self.assertIn("adds volatile", kitlib.admissible(BASE, cand))

    def test_one_trip_block_refused(self):
        cand = BASE.replace("    ASM_KEEP(node);\n", "    do { w = 1; } while (0);\n")
        bad = kitlib.admissible(BASE, cand)
        self.assertTrue(any("one-trip" in r for r in bad), bad)

    def test_for_zero_refused(self):
        cand = BASE.replace("    ASM_KEEP(node);\n", "    for (i = 0; 0; i++) { w = 1; }\n")
        self.assertTrue(any("one-trip" in r for r in kitlib.admissible(BASE, cand)))

    def test_substituted_pin_refused_even_when_count_falls(self):
        # two pins out, one different pin in: the remaining set is not a subset of the base's
        cand = BASE.replace("    register s32 v ASM_REG(\"$19\") = x;\n", "    s32 v = x;\n")
        cand = cand.replace("    ASM_KEEP(node);", "    ASM_SCHED_BARRIER();")
        bad = kitlib.admissible(BASE, cand)
        self.assertTrue(any("did not have" in r for r in bad), bad)


class TestLedger(unittest.TestCase):
    def test_variant_count_dedups_and_skips_baselines(self):
        recs = [{"row": "a/b", "variant": "v1"}, {"row": "a/b", "variant": "v1"},
                {"row": "a/b", "variant": "v2"}, {"row": "a/b", "variant": "pinned_control", "kind": "baseline"},
                {"row": "c/d", "variant": "v9"}]
        self.assertEqual(kitlib.variant_count(recs, "a/b"), 2)
        self.assertEqual(kitlib.variant_count(recs, "c/d"), 1)

    def test_append_and_read_round_trip(self):
        with tempfile.TemporaryDirectory() as td:
            kitlib.log_append(td, {"row": "a/b", "variant": "v1", "distance": 3})
            kitlib.log_append(td, {"row": "a/b", "variant": "v2", "distance": None})
            got = kitlib.log_read(td)
            self.assertEqual([r["variant"] for r in got], ["v1", "v2"])

    def test_read_skips_a_truncated_line(self):
        with tempfile.TemporaryDirectory() as td:
            p = Path(td) / kitlib.LOG_NAME
            p.write_text(json.dumps({"row": "a/b", "variant": "v1"}) + "\n{\"row\": \n")
            self.assertEqual(len(kitlib.log_read(td)), 1)

    def test_lane_rows_reads_base_glob(self):
        with tempfile.TemporaryDirectory() as td:
            d = Path(td) / "base" / "dungeon"
            d.mkdir(parents=True)
            (d / "func_80001234.c").write_text("")
            self.assertEqual(kitlib.lane_rows(td), ["dungeon/func_80001234"])


class TestLaneDir(unittest.TestCase):
    def test_refuses_repo_root(self):
        import os
        old = os.environ.get("LANEKIT_LANE")
        os.environ["LANEKIT_LANE"] = str(ROOT)
        try:
            with self.assertRaises(SystemExit):
                kitlib.lane_dir(create=False)
        finally:
            if old is None:
                os.environ.pop("LANEKIT_LANE", None)
            else:
                os.environ["LANEKIT_LANE"] = old

    def test_refuses_outside_the_repo(self):
        import os
        old = os.environ.get("LANEKIT_LANE")
        os.environ["LANEKIT_LANE"] = "/"
        try:
            with self.assertRaises(SystemExit):
                kitlib.lane_dir(create=False)
        finally:
            if old is None:
                os.environ.pop("LANEKIT_LANE", None)
            else:
                os.environ["LANEKIT_LANE"] = old


class TestTable(unittest.TestCase):
    def test_columns_align_and_none_prints_empty(self):
        t = kitlib.fmt_table(["a", "bb"], [[1, None], ["xxx", "y"]])
        lines = t.splitlines()
        self.assertEqual(lines[0], "a    bb")
        self.assertEqual(lines[2], "1")
        self.assertEqual(lines[3], "xxx  y")


class TestReport(unittest.TestCase):
    def _lane(self, td, recs, served=()):
        for r in recs:
            kitlib.log_append(td, r)
        for rid in served:
            d = Path(td) / "base" / rid.split("/")[0]
            d.mkdir(parents=True, exist_ok=True)
            (d / (rid.split("/")[1] + ".c")).write_text("")
        return td

    def test_zero_measurement_row_is_named(self):
        with tempfile.TemporaryDirectory() as td:
            self._lane(td, [{"row": "a/f1", "variant": "v1", "distance": 2, "status": "measured"}],
                       served=["a/f1", "a/f2"])
            out = L.report(td)
            self.assertIn("ZERO MEASUREMENTS", out)
            self.assertIn("a/f2", out)

    def test_baselines_do_not_count_as_variants(self):
        with tempfile.TemporaryDirectory() as td:
            self._lane(td, [{"row": "a/f1", "variant": "pinned_control", "kind": "baseline",
                             "distance": 0, "status": "measured"}], served=["a/f1"])
            self.assertIn("ZERO MEASUREMENTS", L.report(td))

    def test_table_sorted_by_distance_and_counts_exact(self):
        with tempfile.TemporaryDirectory() as td:
            self._lane(td, [
                {"row": "a/f1", "variant": "far", "distance": 9, "status": "measured"},
                {"row": "a/f1", "variant": "near", "distance": 0, "status": "exact",
                 "score": {"exact": True, "total": 0}},
                {"row": "a/f1", "variant": "broken", "distance": None, "status": "no-build"}])
            out = L.report(td)
            self.assertIn("best listing distance 0", out)
            self.assertIn("3 variants measured", out)
            self.assertIn("1 exact", out)
            self.assertLess(out.index("near"), out.index("far"))
            self.assertLess(out.index("far"), out.index("broken"))


SCHED_DUMP = """
;; Function func_1

;;	 -- basic block number 0 from 4 to 22 --
;; ready list initially:
;; 22

;; insn[  12]: priority =    1, ref_count =    1
;; insn[  19]: priority =    1, ref_count =    1
;; insn[  22]: priority = 2147483261, ref_count =    0
;; ready list at T-1: 22 (7ffffe7d), now 22
;; ready list at T-2: 12 (7f000001) 19 (7f000001), now 19 12
;; total time = 3

;;	 -- basic block number 1 from 26 to 31 --
;; insn[  26]: priority =    4, ref_count =    1
;; total time = 5

(insn 19 12 22 (set (reg:SI 81)
        (reg:SI 4 a0)) 172 {m} (insn_list:REG_DEP_ANTI 12 (nil))
    (nil))

(insn 12 4 19 (set (reg:SI 80)
        (const_int 3)) 172 {m} (nil)
    (nil))
"""


class TestSchedParser(unittest.TestCase):
    def test_blocks_priorities_and_ready_lists(self):
        b = W.sched_blocks(SCHED_DUMP)
        self.assertEqual([x["n"] for x in b], [0, 1])
        self.assertEqual(b[0]["prio"][12], (1, 1))
        self.assertEqual(b[0]["prio"][22], (2147483261, 0))
        self.assertEqual(b[0]["total"], 3)
        self.assertEqual(len(b[0]["ready"]), 2)
        self.assertEqual(b[0]["ready"][1][0], 2)
        self.assertEqual(b[1]["prio"][26], (4, 1))

    def test_block_commentary_stops_at_the_rtl(self):
        # the RTL below must not be scanned for `;; insn[` lines of the last block
        self.assertNotIn(19, W.sched_blocks(SCHED_DUMP)[1]["prio"])

    def test_insns_of_gives_order_links_and_anon(self):
        got = W.insns_of(SCHED_DUMP)
        self.assertEqual([x["uid"] for x in got], [19, 12])
        self.assertEqual(got[0]["links"], [(12, "REG_DEP_ANTI")])
        self.assertIn("(reg:SI p0)", got[0]["anon"])          # pseudo 81 renamed, first seen
        self.assertIn("(reg:SI 4 a0)", got[0]["anon"])        # hard register untouched
        self.assertIn("(reg:SI p1)", got[1]["anon"])          # pseudo 80 renamed second


class TestPreOrder(unittest.TestCase):
    """`src` must be the chain order of the pass before the scheduler, not UID order: combine
    creates high-UID insns and splices them where the combined insn was."""

    def test_uses_the_combine_dump_for_sched(self):
        d = {"sched": SCHED_DUMP, "combine": SCHED_DUMP}
        self.assertEqual(W.pre_order(d, "sched"), {19: 0, 12: 1})   # chain order, not 12 then 19

    def test_uses_the_greg_dump_for_sched2(self):
        d = {"sched2": SCHED_DUMP, "greg": SCHED_DUMP}
        self.assertEqual(W.pre_order(d, "sched2"), {19: 0, 12: 1})

    def test_none_when_the_previous_dump_is_absent(self):
        self.assertIsNone(W.pre_order({"sched": SCHED_DUMP}, "sched"))


class TestAnon(unittest.TestCase):
    def test_first_appearance_numbering_is_per_table(self):
        t = {}
        self.assertEqual(W.anon("(set (reg:SI 90) (reg/v:HI 91))", t),
                         "(set (reg:SI p0) (reg:HI p1))")
        self.assertEqual(W.anon("(reg:SI 91)", t), "(reg:SI p1)")

    def test_hard_registers_are_not_renamed(self):
        self.assertEqual(W.anon("(reg:SI 4 a0)", {}), "(reg:SI 4 a0)")


class TestAround(unittest.TestCase):
    def test_substring(self):
        a = W.Around("symbol_ref", None, BASE, None)
        self.assertTrue(a.hit('(high:SI (symbol_ref:SI ("D_1")))'))
        self.assertFalse(a.hit("(const_int 3)"))

    def test_pseudo_number(self):
        a = W.Around("81", None, BASE, None)
        self.assertTrue(a.hit("(set (reg/v:SI 81) (const_int 0))"))
        self.assertFalse(a.hit("(set (reg:SI 810) (const_int 0))"))

    def test_hard_register(self):
        a = W.Around("$19", None, BASE, None)
        self.assertTrue(a.hit("(reg:SI 19 $19)"))

    def test_line_form_needs_a_variable_of_the_function(self):
        with self.assertRaises(SystemExit):
            W.Around("L3", None, BASE, None)      # no decl_pseudos without a first_pseudo


class TestShimArgv(unittest.TestCase):
    def test_finds_a_plain_compiler(self):
        self.assertEqual(lane_shim._compiler_in(["/x/gcc-2.8.1/cc1", "f.i"]), 0)

    def test_finds_a_compiler_behind_nice(self):
        self.assertEqual(lane_shim._compiler_in(["nice", "-n10", "ionice", "-c2", "-n7", "/x/gcc"]), 5)

    def test_ignores_a_non_compiler(self):
        self.assertIsNone(lane_shim._compiler_in(["python3", "tools/verify.py", "row", "f.c"]))
        self.assertIsNone(lane_shim._compiler_in(["mipsel-linux-gnu-as", "-o", "a.o"]))


class TestInstall(unittest.TestCase):
    def test_writes_tools_md_with_absolute_paths_and_rows(self):
        with tempfile.TemporaryDirectory() as td:
            d = Path(td) / "base" / "dungeon"
            d.mkdir(parents=True)
            (d / "func_80001234.c").write_text("")
            p = I.install(td)
            text = p.read_text()
            self.assertIn(str(ROOT / "tools/verify.py"), text)
            self.assertIn(str(KIT / "lab.py"), text)
            self.assertIn("dungeon/func_80001234", text)
            self.assertIn("There is no `RUNBOOK.md`", text)
            self.assertIn(str(ROOT / "tools/xform/screen.py"), text)
            self.assertIn("none of which exist", text)

    def test_refuses_the_repo_root(self):
        with self.assertRaises(SystemExit):
            I.install(ROOT)


class TestSiteLabel(unittest.TestCase):
    def test_statement_and_register_forms(self):
        self.assertEqual(E.site_label(("stmt", "ASM_USE", "near_y", 0, 0, 1, "")), "ASM_USE(near_y)")
        self.assertEqual(E.site_label(("reg", "ASM_REG", "$19", 0, 0, 1, "s32 v")), "ASM_REG $19")


class TestBriefTemplate(unittest.TestCase):
    """The v2 brief must not reintroduce the dead references the mining found."""

    def setUp(self):
        self.text = (ROOT / "tools/lanes/duck_pack_brief_v2.md").read_text()

    def test_no_dead_references(self):
        self.assertNotIn("../r58_order", self.text)
        self.assertNotIn("tools/lanes/screen.py", self.text)
        self.assertNotIn("tools/lanes/pin_sites.py", self.text)
        self.assertNotIn("tools/xform/pin_census.py", self.text)

    def test_states_there_is_no_runbook(self):
        self.assertIn("no `RUNBOOK.md`", self.text)

    def test_fixes_the_restatement_heading(self):
        self.assertIn("# Working DUCK restatements", self.text)

    def test_quotes_the_duck_payoff(self):
        self.assertIn("12.6%", self.text)
        self.assertIn("30.4%", self.text)

    def test_every_repo_path_it_names_exists(self):
        import re
        missing = []
        for m in re.finditer(r"<REPO>/([A-Za-z0-9_./<>-]+)", self.text):
            rel = m.group(1).rstrip(".")
            if "<" in rel or rel.endswith("/"):
                continue
            if not (ROOT / rel).exists():
                missing.append(rel)
        self.assertEqual(missing, [])


if __name__ == "__main__":
    unittest.main()
