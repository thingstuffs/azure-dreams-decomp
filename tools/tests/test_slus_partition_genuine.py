"""Private contract tests for per-physical-owner genuine-ASPSX aggregation.

The aggregation boundary must only combine complete, independently checked
physical measurements.  These records are synthetic; compiler integration is
exercised by the owner's separate probe.
"""

from __future__ import annotations

import copy
import importlib.util
import sys
import unittest
from pathlib import Path

HERE = Path(__file__).resolve().parent
REPO = HERE.parents[2] if (HERE / "aspsx_diff.py").exists() else HERE.parents[1]
TARGET = HERE / "aspsx_diff.py" if (HERE / "aspsx_diff.py").exists() else REPO / "tools/fidelity/aspsx_diff.py"
sys.path[:0] = [str(REPO / "tools"), str(REPO / "tools/build"), str(REPO / "tools/fidelity")]
SPEC = importlib.util.spec_from_file_location("private_partition_aspsx_diff", TARGET)
DIFF = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(DIFF)

FA = "func_80030000"
FB = "func_80030010"
FC = "func_80030020"
VERSIONS = ["2.79", "2.81"]
ROW = {"row": "slus/code", "kind": "slus", "container": "slus",
       "cfg": "2.7.2 -G0", "cell": "2.7.2", "pins": 2}
UNITS = [
    {"source": "src/code.c", "recipe": {"ccver": "2.7.2", "ccflags": "-G0", "asflags": ""},
     "functions": [FA], "expected_functions": [FA], "role": "remainder"},
    {"source": "src/alpha.c", "recipe": {"ccver": "2.8.1", "ccflags": "-O2", "asflags": ""},
     "functions": [FB], "expected_functions": [FB, FC], "role": "module", "module": "alpha"},
]
EXPECTED = [FA, FB]  # complete original logical-row scope, not complete physical TU scope


def result(source, functions, *, words, retail_diff, retail_masked, exact_281, fired, gp):
    return {
        "source": source, "status": "ok", "functions": list(functions),
        "funcs": len(functions), "words": words, "selfcheck": True,
        "maspsx_exact": retail_diff == 0,
        "maspsx_retail": {"diff": retail_diff, "masked": retail_masked,
                           "checked": len(functions)},
        "genuine": {
            "2.79": {"exact": True, "diff": 0, "len": words, "mode": "-q",
                     "retail": [retail_diff, retail_masked], "retail_checked": len(functions)},
            "2.81": {"exact": exact_281, "diff": 0 if exact_281 else 3,
                     "len": words + (0 if exact_281 else 1), "mode": "-q -G0",
                     "retail": [retail_diff + (0 if exact_281 else 3), retail_masked],
                     "retail_checked": len(functions)},
        },
        "best": "2.79", "fired": fired, "trace_scope": "whole-unit",
        "gp_externs": gp, "n_gp_externs": len(gp),
        "attrib": {"2.81": {"diagnostic": "owner-only"}},
    }


RESULTS = [
    result("src/code.c", [FA], words=10, retail_diff=0, retail_masked=1,
           exact_281=True, fired=["fold_selfinc_la", "move_lui"], gp=["D_80080000"]),
    result("src/alpha.c", [FB], words=20, retail_diff=2, retail_masked=0,
           exact_281=False, fired=["move_lui"], gp=["D_80080000", "D_80080004"]),
]


class AggregatePartitionTests(unittest.TestCase):
    def aggregate(self, units=None, results=None, expected=None, versions=None):
        return DIFF._aggregate_partition(copy.deepcopy(ROW),
                                         copy.deepcopy(UNITS if units is None else units),
                                         copy.deepcopy(RESULTS if results is None else results),
                                         copy.deepcopy(EXPECTED if expected is None else expected),
                                         copy.deepcopy(VERSIONS if versions is None else versions))

    def assert_rejected(self, *, units=None, results=None, expected=None, fragment=None):
        try:
            rec = self.aggregate(units, results, expected)
        except (ValueError, RuntimeError) as exc:
            if fragment:
                self.assertIn(fragment, str(exc))
            return
        self.assertEqual(rec.get("status"), "error", rec)
        self.assertFalse(rec.get("exact_versions"), rec)
        if fragment:
            self.assertIn(fragment, rec.get("err", ""))

    def test_mixed_owner_recipes_and_counts_keep_original_row_provenance(self):
        rec = self.aggregate()
        self.assertEqual(rec["status"], "ok")
        self.assertEqual(rec["row"], "slus/code")
        self.assertEqual(rec["cfg"], "2.7.2 -G0")
        self.assertEqual(rec["cell"], "mixed")
        self.assertEqual(rec["pins"], 2)
        self.assertEqual(rec["funcs"], 2)
        self.assertEqual(rec["words"], 30)
        self.assertEqual(rec["maspsx_retail"], {"diff": 2, "masked": 1, "checked": 2})
        self.assertFalse(rec["maspsx_exact"])
        self.assertTrue(rec["selfcheck"])
        physical = {unit["source"]: unit for unit in rec["physical_units"]}
        self.assertEqual(set(physical), {unit["source"] for unit in UNITS})
        self.assertEqual(physical["src/code.c"]["recipe"], UNITS[0]["recipe"])
        self.assertEqual(physical["src/alpha.c"]["recipe"], UNITS[1]["recipe"])
        self.assertEqual(set(physical["src/alpha.c"]["expected_functions"]), {FB, FC})

    def test_exact_versions_intersect_token_results_but_retail_masks_remain_visible(self):
        rec = self.aggregate()
        self.assertEqual(rec["exact_versions"], ["2.79"])
        self.assertTrue(rec["genuine"]["2.79"]["exact"])
        self.assertEqual(rec["genuine"]["2.79"]["diff"], 0)
        self.assertEqual(rec["genuine"]["2.79"]["len"], 30)
        self.assertEqual(rec["genuine"]["2.79"]["retail"], [2, 1])
        self.assertEqual(rec["genuine"]["2.79"]["retail_checked"], 2)
        self.assertEqual(rec["genuine"]["2.79"]["modes"],
                         {"src/code.c": "-q", "src/alpha.c": "-q"})
        self.assertFalse(rec["genuine"]["2.81"]["exact"])
        self.assertEqual(rec["genuine"]["2.81"]["diff"], 3)

    def test_trace_and_gp_are_unions_with_whole_unit_scope_and_no_row_fix_claim(self):
        rec = self.aggregate()
        self.assertEqual(set(rec["fired"]), {"fold_selfinc_la", "move_lui"})
        self.assertEqual(rec["trace_scope"], "union-of-whole-physical-units")
        self.assertEqual(set(rec["gp_externs"]), {"D_80080000", "D_80080004"})
        self.assertEqual(rec["n_gp_externs"], 2)
        self.assertNotIn("fix", rec)
        self.assertNotIn("disable_pass", rec)
        self.assertNotIn("attrib", rec)
        self.assertEqual(rec["partition_attribution"],
                         {result["source"]: result["attrib"] for result in RESULTS})

    def test_unit_source_and_function_coverage_must_be_complete_and_unique(self):
        self.assert_rejected(results=RESULTS[:1])
        self.assert_rejected(results=RESULTS + [result("src/extra.c", [FC], words=1,
                                                       retail_diff=0, retail_masked=0,
                                                       exact_281=True, fired=[], gp=[])])
        self.assert_rejected(results=RESULTS + [RESULTS[0]])
        wrong = copy.deepcopy(RESULTS)
        wrong[1]["functions"] = [FA]
        self.assert_rejected(results=wrong)
        wrong[1]["functions"] = [FB, FB]
        self.assert_rejected(results=wrong)
        self.assert_rejected(expected=[FA])
        self.assert_rejected(expected=[FA, FB, FC])
        self.assert_rejected(expected=[FA, FA])
        self.assert_rejected(units=UNITS + [UNITS[0]])
        wrong_units = copy.deepcopy(UNITS)
        wrong_units[1]["functions"] = [FA]
        self.assert_rejected(units=wrong_units)

    def test_selfcheck_or_measurement_error_invalidates_the_whole_row(self):
        bad = copy.deepcopy(RESULTS)
        bad[1]["selfcheck"] = False
        self.assert_rejected(results=bad)
        bad = copy.deepcopy(RESULTS)
        bad[1]["status"] = "error"
        bad[1]["err"] = "synthetic compiler failure"
        self.assert_rejected(results=bad)
        bad = copy.deepcopy(RESULTS)
        del bad[1]["maspsx_retail"]
        self.assert_rejected(results=bad)
        bad = copy.deepcopy(RESULTS)
        bad[1]["funcs"] = 0
        self.assert_rejected(results=bad)
        bad = copy.deepcopy(RESULTS)
        bad[1]["maspsx_retail"]["checked"] = 0
        self.assert_rejected(results=bad)

    def test_one_owner_version_error_never_becomes_partial_exact(self):
        bad = copy.deepcopy(RESULTS)
        bad[1]["genuine"]["2.79"] = {"err": "ASPSX syntax error", "mode": "-q"}
        rec = self.aggregate(results=bad)
        self.assertNotIn("2.79", rec.get("exact_versions", []))
        self.assertFalse(rec["genuine"]["2.79"].get("exact"))
        self.assertIn("err", rec["genuine"]["2.79"])
        self.assertEqual(rec["genuine"]["2.79"]["unit_errors"],
                         {"src/alpha.c": "ASPSX syntax error"})

    def test_missing_or_inconsistent_retail_check_never_grants_version_exactness(self):
        for value in (None, 0):
            with self.subTest(retail_checked=value):
                bad = copy.deepcopy(RESULTS)
                if value is None:
                    del bad[1]["genuine"]["2.79"]["retail_checked"]
                else:
                    bad[1]["genuine"]["2.79"]["retail_checked"] = value
                rec = self.aggregate(results=bad)
                self.assertNotIn("2.79", rec["exact_versions"])
                self.assertIn("err", rec["genuine"]["2.79"])
                self.assertIn("src/alpha.c", rec["genuine"]["2.79"]["unit_errors"])
                physical = {unit["source"]: unit for unit in rec["physical_units"]}
                self.assertNotIn("2.79", physical["src/alpha.c"]["exact_versions"])
                self.assertFalse(rec["ownerwise_exact_versions"])

    def test_disjoint_owner_exact_versions_do_not_create_common_row_version(self):
        different = copy.deepcopy(RESULTS)
        different[0]["genuine"]["2.79"].update(exact=True, diff=0)
        different[0]["genuine"]["2.81"].update(exact=False, diff=2)
        different[1]["genuine"]["2.79"].update(exact=False, diff=3)
        different[1]["genuine"]["2.81"].update(exact=True, diff=0)
        rec = self.aggregate(results=different)
        self.assertEqual(rec["exact_versions"], [])
        self.assertTrue(rec["ownerwise_exact_versions"])
        physical = {unit["source"]: unit for unit in rec["physical_units"]}
        self.assertEqual(physical["src/code.c"]["exact_versions"], ["2.79"])
        self.assertEqual(physical["src/alpha.c"]["exact_versions"], ["2.81"])
        self.assertFalse(rec["genuine"]["2.79"]["exact"])
        self.assertFalse(rec["genuine"]["2.81"]["exact"])

    def test_full_tu_scope_stays_attached_to_owner_without_expanding_row_proof(self):
        rec = self.aggregate()
        physical = {unit["source"]: unit for unit in rec["physical_units"]}
        owner = physical["src/alpha.c"]
        self.assertEqual(owner["role"], "module")
        self.assertEqual(owner["module"], "alpha")
        self.assertEqual(owner["expected_functions"], [FB, FC])
        self.assertEqual(owner["functions"], [FB])
        self.assertEqual(rec["functions"], [FA, FB])
        self.assertEqual(rec["funcs"], 2)
        # FC is proven present in the physical TU by the compile/trace checks,
        # but it belongs to a sibling logical row and is not scored here.
        self.assertNotIn(FC, rec["functions"])
        self.assert_rejected(expected=[FA, FB, FC])


if __name__ == "__main__":
    unittest.main()
