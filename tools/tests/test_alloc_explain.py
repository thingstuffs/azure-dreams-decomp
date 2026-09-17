"""Pure causal checks for alloc_explain; no compiler or gdb is run here."""
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import alloc_explain as explain


def observation(patterns_by_function):
    return {"state": {fn: {"first_pseudo": 68} for fn in patterns_by_function},
            "patterns": {fn: {"rtl": patterns} for fn, patterns in patterns_by_function.items()}}


def local_record(attempts, quantities, *, desired=2, target_qty=0, function="f"):
    target = next(q for q in quantities if q["qty"] == target_qty)
    accepted = [a for a in attempts if a["qty"] == target_qty and a.get("result", -1) >= 0]
    block = {"function": function, "block": 0, "quantities": quantities, "attempts": attempts,
             "initial_occupied": {str(q["qty"]): [] for q in quantities}, "fixed": [],
             "call_used": []}
    reason = {"owner": "local", "function": function, "pseudo": target["pseudos"][0], "block": 0,
              "quantity": target, "attempt": accepted[-1], "reasons": ["earlier-quantity-conflict"]}
    return {"site": 0, "line": 10, "var": "declared_name", "hard": desired, "valid": True,
            "assembly_equal": True, "error": None, "trace_errors": [],
            "bound": [{"owner": "local", "function": function,
                       "pseudo": target["pseudos"][0]}],
            "reasons": [reason], "trace": {"blocks": [block], "global_states": [],
                                                    "global_attempts": [], "errors": [],
                                                    "error": None, "assembly_equal": True}}


def quantity(qty, pseudo, priority, birth=0, death=10, suggestions=None):
    return {"qty": qty, "pseudos": [pseudo], "priority": priority, "birth": birth,
            "death": death, "n_refs": 2, "size": 1, "n_calls_crossed": 0,
            "phys_sugg": suggestions or [], "phys_copy_sugg": []}


class TrustTests(unittest.TestCase):
    def test_an_invalid_trace_is_rejected_before_a_diagnosis_is_made(self):
        rec = {"site": 3, "valid": False, "assembly_equal": False,
               "error": "gdb failed", "trace_errors": []}
        got = explain.explain_site(rec, {})
        self.assertEqual(got["status"], "untrusted-trace")
        self.assertNotIn("entries", got)
        self.assertNotIn("cause", got)

    def test_baseline_recipe_override_keeps_the_recorded_row_cfg_in_provenance(self):
        row = {"cfg": "2.7.2-cdk"}
        got = explain.recipe_provenance(row, "2.7.2 -G0")
        self.assertEqual(got, {"cfg": "2.7.2 -G0", "cell": "2.7.2", "flags": ["-G0"],
                               "recorded_row_cfg": "2.7.2-cdk",
                               "cfg_source": "command-line-override"})
        self.assertEqual(explain.recipe_provenance(row)["cfg_source"], "row-record")


class RTLTests(unittest.TestCase):
    def test_pseudo_numbers_are_scoped_to_the_function(self):
        obs = observation({
            "f": ["(set (reg/v:SI 72) (reg:SI 4 a0))", "(set (reg:SI 5 a1) (reg/v:SI 72))"],
            "g": ["(set (reg/v:SI 72) (symbol_ref:SI (\"OTHER\")))"],
        })
        got = explain.rtl_value(obs, "f", 72)
        self.assertEqual(got["origin"], {"kind": "hard-register-copy", "register": "$a0", "hard": 4})
        self.assertEqual(len(got["definitions"]), 1)
        self.assertEqual(len(got["uses"]), 1)
        self.assertNotIn("OTHER", str(got))

    def test_cross_compile_shape_does_not_depend_on_pseudo_number(self):
        a = observation({"f": ["(set (reg/v:SI 72) (reg:SI 4 a0))"]})
        b = {"state": {"f": {"first_pseudo": 76}},
             "patterns": {"f": {"rtl": ["(set (reg/v:SI 80) (reg:SI 4 a0))"]}}}
        self.assertEqual(explain.rtl_value(a, "f", 72)["definitions"][0]["shape"],
                         explain.rtl_value(b, "f", 80)["definitions"][0]["shape"])

    def test_expression_using_a_hard_register_is_not_called_a_plain_copy(self):
        obs = observation({"f": [
            "(set (reg:SI 72) (plus:SI (reg:SI 4 a0) (const_int 1)))",
            "(set (reg:SI 73) (mem:SI (reg:SI 4 a0)))",
        ]})
        self.assertEqual(explain.rtl_value(obs, "f", 72)["origin"], {"kind": "addition"})
        self.assertEqual(explain.rtl_value(obs, "f", 73)["origin"], {"kind": "memory-load"})

    def test_nested_mem_in_a_call_does_not_turn_call_result_into_a_load(self):
        direct = observation({"f": [
            "(set (reg:SI 72) (call (mem:SI (symbol_ref:SI (\"callee\"))) (const_int 16)))",
        ]})
        parallel = observation({"f": [
            "(parallel[ (set (reg:SI 72) (call (mem:SI (symbol_ref:SI (\"callee\"))) "
            "(const_int 16))) (clobber (reg:SI 31 ra)) ] )",
        ]})
        self.assertEqual(explain.rtl_value(direct, "f", 72)["origin"],
                         {"kind": "call-result", "symbol": "callee"})
        self.assertEqual(explain.rtl_value(parallel, "f", 72)["origin"],
                         {"kind": "rtl-definition"})


class ChronologyTests(unittest.TestCase):
    def test_a_later_claim_is_not_reported_as_the_cause(self):
        qs = [quantity(0, 72, 2000), quantity(1, 76, 10000)]
        attempts = [
            {"qty": 0, "suggestions_only": 0, "result": 3, "occupied": [],
             "accept_call_clobbered": 0},
            {"qty": 1, "suggestions_only": 0, "result": 2, "occupied": [],
             "accept_call_clobbered": 0},
        ]
        rec = local_record(attempts, qs)
        obs = observation({"f": ["(set (reg/v:SI 72) (reg:SI 4 a0))",
                                 "(set (reg/v:SI 76) (symbol_ref:SI (\"TABLE\")))"]})
        entry = explain.explain_site(rec, obs)["entries"][0]
        self.assertEqual(entry["cause"]["kind"], "no-earlier-claim-proven")
        self.assertNotIn("competitor", entry)

    def test_suggestion_pass_can_beat_a_higher_priority_target(self):
        # Quantity 1 has lower priority but its suggestion-only attempt is chronologically first.
        # The explanation must not reverse that fact by sorting quantities by priority itself.
        qs = [quantity(0, 72, 10000), quantity(1, 76, 100, suggestions=[2])]
        attempts = [
            {"qty": 1, "suggestions_only": 1, "result": 2, "occupied": [],
             "accept_call_clobbered": 0},
            {"qty": 0, "suggestions_only": 0, "result": 3, "occupied": [2],
             "accept_call_clobbered": 0},
        ]
        rec = local_record(attempts, qs)
        obs = observation({"f": ["(set (reg/v:SI 72) (reg:SI 4 a0))",
                                 "(set (reg/v:SI 76) (symbol_ref:SI (\"TABLE\")))"]})
        entry = explain.explain_site(rec, obs)["entries"][0]
        self.assertEqual(entry["cause"]["kind"],
                         "desired-register-taken-by-earlier-local-quantity")
        self.assertEqual(entry["cause"]["ordering"], "suggestion-pass-precedes-priority-pass")
        self.assertEqual([a["pass"] for a in entry["chronology"]], ["suggestion", "priority"])


class ScopeTests(unittest.TestCase):
    def test_global_owner_is_explicitly_unsupported(self):
        rec = {"site": 0, "line": 1, "var": "x", "hard": 2, "valid": True,
               "assembly_equal": True, "error": None, "trace_errors": [],
               "bound": [{"owner": "global", "function": "f", "pseudo": 72}], "reasons": [],
               "trace": {"errors": [], "error": None, "assembly_equal": True}}
        obs = observation({"f": ["(set (reg/v:SI 72) (reg:SI 4 a0))"]})
        got = explain.explain_site(rec, obs)
        self.assertEqual(got["status"], "unsupported-global")
        self.assertEqual(got["entries"][0]["scope"], "global")
        self.assertNotIn("cause", got["entries"][0])


class ComparisonTests(unittest.TestCase):
    def test_multiple_bindings_are_not_silently_paired_by_list_position(self):
        entry = {"status": "ok", "quantity_graph": [], "cause": {"kind": "x"}}
        baseline = {"status": "ok", "entries": [entry, dict(entry)]}
        candidate = {"status": "ok", "entries": [entry]}
        got = explain.compare_entries(baseline, candidate)
        self.assertEqual(got["status"], "ambiguous-binding")
        self.assertEqual((got["baseline_local_entries"], got["candidate_local_entries"]), (2, 1))
        self.assertFalse(got["pseudo_ids_compared"])

    def test_equal_graphs_with_different_compile_local_ids_compare_equal(self):
        obs_a = observation({"f": ["(set (reg/v:SI 72) (reg:SI 4 a0))"]})
        obs_b = {"state": {"f": {"first_pseudo": 76}},
                 "patterns": {"f": {"rtl": ["(set (reg/v:SI 80) (reg:SI 4 a0))"]}}}
        qa, qb = quantity(0, 72, 2000), quantity(7, 80, 2000)
        ea = {"status": "ok", "cause": {"kind": "x"},
              "quantity_graph": [explain._quantity_node(obs_a, "f", qa)]}
        eb = {"status": "ok", "cause": {"kind": "x"},
              "quantity_graph": [explain._quantity_node(obs_b, "f", qb)]}
        got = explain.compare_entries({"status": "ok", "entries": [ea]},
                                      {"status": "ok", "entries": [eb]})
        self.assertEqual(got["status"], "unchanged")
        self.assertFalse(got["pseudo_ids_compared"])


if __name__ == "__main__":
    unittest.main()
