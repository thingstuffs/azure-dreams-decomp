"""Pure parts of the allocator counterfactual probe: diff -> site matching, diff -> variables,
trace record -> knob plan, and the assembly distance. No compiler, no gdb."""
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import alloc_probe as probe

DIFF = """diff --git a/src/dungeon/func_800A57A0.c b/src/dungeon/func_800A57A0.c
index 96da8edc..6d98e9d7 100644
--- a/src/dungeon/func_800A57A0.c
+++ b/src/dungeon/func_800A57A0.c
@@ -113,13 +113,11 @@ void func_800AAF00(void *actor, s32 effect_param)
                 if (!special_action) {
-                        register s32 object_flags ASM_REG("$2");   /* UNRESOLVED C shape (pin) */
-                        s32 sign_bit;
-
+                        s32 object_flags;   /* UNRESOLVED C shape (pin) */
                         object_flags = ((S0 *)object)->unk_14;
-                        if (object_flags >= 0) {
-                            sign_bit = 0x80000000;
-                            ((S0 *)object)->unk_14 = object_flags | sign_bit;
+                        if (!(object_flags & 0x80000000)) {
+                            object_flags |= 0x80000000;
+                            ((S0 *)object)->unk_14 = object_flags;
                         }
"""

KEPT = """--- a/src/x.c
+++ b/src/x.c
@@ -1,4 +1,4 @@
-    register s32 value ASM_REG("$2") = input_value;
-    register s32 other ASM_REG("$4");
+    register s32 value ASM_REG("$2") = input_value + 1;
+    s32 other;
"""

INDEX = """| commit | row | regs | generators | diff |
|---|---|---|---|---|
| 449fa768 | dungeon/func_8188E648 | 7→6 | t10_epilogue,t2_pins | dungeon_func_8188E648.449fa768.diff |
| b13b4cf2 | town/func_800AC3B0 | 9→7 | t1_boiler | town_func_800AC3B0.b13b4cf2.diff |
"""

LOCAL_REC = dict(
    hard=2, var="value",
    reasons=[dict(owner="local", function="f", pseudo=72, block=0,
                  reasons=["earlier-quantity-conflict"],
                  quantity=dict(qty=0, birth=2, death=12, n_refs=2, size=1, priority=2000,
                                pseudos=[72], phys_sugg=[], phys_copy_sugg=[4, 5]),
                  attempt=dict(qty=0, result=3, suggestions_only=0, occupied=[2]),
                  competitors=[dict(qty=1, pseudos=[76], priority=10000, target_priority=2000,
                                    same_priority=False, suggested=False)])],
    attempt_reasons=[], trace={})

GLOBAL_REC = dict(
    hard=21, var="counter",
    reasons=[dict(owner="global", function="g", pseudo=137, allocno=4, order=2, reasons=["other-global-preference"],
                  preferences=[22], copy_preferences=[], hard_conflicts=[16, 17])],
    attempt_reasons=[dict(function="g", pseudo=137, hard=21, reasons=["already-used-register-selection"],
                          attempt=dict(result=22), competitors=[dict(pseudo=140, priority=1, target_priority=1)])],
    trace=dict(global_states=[dict(function="g", allocno_reg=[100, 110, 120, 130, 137, 140])]))


class DiffTests(unittest.TestCase):
    def test_removed_site_is_matched_by_variable_and_register(self):
        self.assertEqual(probe.diff_removed_sites(DIFF), [("object_flags", "2")])

    def test_a_site_present_on_both_sides_is_not_a_removal(self):
        self.assertEqual(probe.diff_removed_sites(KEPT), [("other", "4")])

    def test_changed_variables_are_declarations_and_assignments_not_fields(self):
        got = probe.diff_variables(DIFF)
        self.assertIn("object_flags", got)
        self.assertIn("sign_bit", got)
        self.assertNotIn("unk_14", got)
        self.assertNotIn("if", got)

    def test_strict_variables_drop_the_pinned_declaration_itself(self):
        # object_flags is only ever touched by its own declaration pair plus real assignments
        self.assertIn("object_flags", probe.strict_fix_variables(DIFF, "object_flags"))
        # in KEPT, `other` changes only by its declaration losing the macro
        self.assertNotIn("other", probe.strict_fix_variables(KEPT, "other"))
        self.assertEqual(probe.diff_removed_sites(KEPT), [("other", "4")])

    def test_index_rows_parse(self):
        idx = probe.parse_index(INDEX)
        self.assertEqual([r["row"] for r in idx], ["dungeon/func_8188E648", "town/func_800AC3B0"])
        self.assertEqual(idx[0]["commit"], "449fa768")
        self.assertEqual((idx[1]["regs_before"], idx[1]["regs_after"]), (9, 7))
        self.assertTrue(idx[0]["diff"].endswith(".diff"))


class PlanTests(unittest.TestCase):
    def test_local_plan_targets_the_quantity_and_its_competitor(self):
        plan = probe.plan_knobs(LOCAL_REC)
        names = [k["name"] for k in plan]
        self.assertEqual(names[:2], ["force", "force-return"])
        for want in ("sugg", "unconflict", "refs+1", "shorten-death", "competitor-refs-1", "order-swap"):
            self.assertIn(want, names)
        sugg = next(k for k in plan if k["name"] == "sugg")
        self.assertEqual(sugg["target"], dict(scope="local", function="f", block=0, qty=0,
                                              pseudo=72, birth=2, death=12))
        self.assertEqual(sugg["ops"][0], dict(op="setbit", sym="qty_phys_sugg", idx=0, bit=2))
        self.assertEqual(sugg["ops"][1]["sym"], "qty_phys_num_sugg")
        comp = next(k for k in plan if k["name"] == "competitor-refs-1")
        self.assertEqual(comp["ops"], [dict(op="add_i32", sym="qty_n_refs", idx=1, delta=-1)])
        swap = next(k for k in plan if k["name"] == "order-swap")
        self.assertEqual(swap["hook"], "postsort2")
        self.assertEqual(swap["ops"], [dict(op="swap_qty_order", a=0, b=1)])

    def test_local_unconflict_clears_retail_over_the_whole_lifetime(self):
        k = next(k for k in probe.plan_knobs(LOCAL_REC) if k["name"] == "unconflict")
        self.assertEqual(k["hook"], "own")
        self.assertEqual(k["ops"], [dict(op="clrbit_range", sym="regs_live_at", lo=2, hi=12, bit=2)])

    def test_a_one_ref_one_insn_quantity_gets_no_impossible_knobs(self):
        rec = dict(LOCAL_REC)
        rec["reasons"] = [dict(LOCAL_REC["reasons"][0])]
        rec["reasons"][0]["quantity"] = dict(LOCAL_REC["reasons"][0]["quantity"], n_refs=1, birth=4, death=5)
        names = [k["name"] for k in probe.plan_knobs(rec)]
        self.assertNotIn("refs-1", names)          # would make n_refs 0
        self.assertNotIn("shorten-death", names)   # would make death == birth (find_free_reg aborts)

    def test_global_plan_uses_the_allocno_and_names_the_competitor_allocno(self):
        plan = probe.plan_knobs(GLOBAL_REC)
        names = [k["name"] for k in plan]
        for want in ("pref", "copypref", "unconflict", "order-swap", "used-so-far-set",
                     "used-so-far-clear", "competitor-unpref"):
            self.assertIn(want, names)
        self.assertTrue(all(k["hook"] == "global" for k in plan))
        pref = next(k for k in plan if k["name"] == "pref")
        self.assertEqual(pref["ops"], [dict(op="setbit", sym="hard_reg_preferences", idx=4, bit=21)])
        swap = next(k for k in plan if k["name"] == "order-swap")
        self.assertEqual(swap["ops"], [dict(op="swap_order", sym="allocno_order", count="max_allocno",
                                            a=4, b=5)])
        self.assertEqual(swap["competitor"], dict(allocno=5, pseudo=140, source="attempt_reasons",
                                                  earlier=True))

    def test_global_competitor_falls_back_to_an_earlier_attempt_that_took_retail(self):
        rec = dict(GLOBAL_REC)
        rec["attempt_reasons"] = [dict(rec["attempt_reasons"][0], competitors=[])]
        rec["trace"] = dict(rec["trace"], global_attempts=[
            dict(function="g", pseudo=110, result=21), dict(function="g", pseudo=137, result=22)])
        swap = next(k for k in probe.plan_knobs(rec) if k["name"] == "order-swap")
        self.assertEqual(swap["competitor"], dict(allocno=1, pseudo=110, source="earlier-attempt",
                                                  earlier=True))
        self.assertEqual(probe.competitor_record(rec, rec["reasons"][0], 21),
                         dict(found=True, source="earlier-attempt", earlier=True, pseudo=110, allocno=1))

    def test_a_later_global_attempt_is_not_a_competitor(self):
        # the only attempt that took retail's register runs AFTER the target's own find_reg attempt:
        # it did not take the register from the target, so no competitor knob may be planned
        rec = dict(GLOBAL_REC)
        rec["attempt_reasons"] = [dict(rec["attempt_reasons"][0], competitors=[])]
        rec["trace"] = dict(rec["trace"], global_attempts=[
            dict(function="g", pseudo=137, result=22), dict(function="g", pseudo=110, result=21)])
        names = [k["name"] for k in probe.plan_knobs(rec)]
        self.assertNotIn("order-swap", names)
        self.assertNotIn("competitor-unpref", names)
        self.assertEqual(probe.global_competitor(rec, 137, "g"), (None, None, None))
        crec = probe.competitor_record(rec, rec["reasons"][0], 21)
        self.assertEqual((crec["found"], crec["source"], crec["earlier"]), (False, "none", False))
        self.assertIn("competitor knobs not planned", crec["note"])

    def test_a_failed_earlier_attempt_by_the_target_bounds_the_scan(self):
        # the target's own FIRST attempt is the boundary (mirrors local_competitor), so an attempt
        # between a failed early try and the successful retry is not offered as a competitor
        rec = dict(GLOBAL_REC)
        rec["attempt_reasons"] = [dict(rec["attempt_reasons"][0], competitors=[])]
        rec["trace"] = dict(rec["trace"], global_attempts=[
            dict(function="g", pseudo=137, result=-1), dict(function="g", pseudo=110, result=21),
            dict(function="g", pseudo=137, result=22)])
        self.assertEqual(probe.global_competitor(rec, 137, "g"), (None, None, None))

    def test_a_global_competitor_in_another_function_is_not_used(self):
        rec = dict(GLOBAL_REC)
        rec["attempt_reasons"] = [dict(rec["attempt_reasons"][0], competitors=[])]
        rec["trace"] = dict(rec["trace"], global_attempts=[dict(function="other", pseudo=110, result=21)])
        self.assertNotIn("order-swap", [k["name"] for k in probe.plan_knobs(rec)])

    def test_a_foreign_function_attempt_does_not_end_the_scan(self):
        # the function filter is applied first, so a same-numbered pseudo elsewhere cannot cut the scan
        rec = dict(GLOBAL_REC)
        rec["attempt_reasons"] = [dict(rec["attempt_reasons"][0], competitors=[])]
        rec["trace"] = dict(rec["trace"], global_attempts=[
            dict(function="other", pseudo=137, result=3), dict(function="g", pseudo=110, result=21),
            dict(function="g", pseudo=137, result=22)])
        self.assertEqual(probe.global_competitor(rec, 137, "g"), (110, 1, "earlier-attempt"))

    def test_local_competitor_falls_back_to_an_earlier_attempt_with_retail(self):
        rec = dict(LOCAL_REC)
        rec["reasons"] = [dict(LOCAL_REC["reasons"][0], competitors=[])]
        rec["trace"] = dict(blocks=[dict(function="f", block=0,
                                         quantities=[dict(qty=1, pseudos=[76], priority=10000)],
                                         attempts=[dict(qty=1, result=2), dict(qty=0, result=3)])])
        k = next(k for k in probe.plan_knobs(rec) if k["name"] == "competitor-refs-1")
        self.assertEqual(k["ops"], [dict(op="add_i32", sym="qty_n_refs", idx=1, delta=-1)])
        self.assertEqual(k["competitor"], dict(qty=1, pseudos=[76], source="attempts", earlier=True))

    def test_a_later_local_attempt_is_not_a_competitor(self):
        rec = dict(LOCAL_REC)
        rec["reasons"] = [dict(LOCAL_REC["reasons"][0], competitors=[])]
        rec["trace"] = dict(blocks=[dict(function="f", block=0, quantities=[dict(qty=1, pseudos=[76])],
                                         attempts=[dict(qty=0, result=3), dict(qty=1, result=2)])])
        self.assertNotIn("competitor-refs-1", [k["name"] for k in probe.plan_knobs(rec)])
        crec = probe.competitor_record(rec, rec["reasons"][0], 2)
        self.assertEqual((crec["found"], crec["source"], crec["earlier"]), (False, "none", False))

    def test_the_local_competitor_record_names_its_source(self):
        self.assertEqual(probe.competitor_record(LOCAL_REC, LOCAL_REC["reasons"][0], 2),
                         dict(found=True, source="competitors", earlier=True, qty=1, pseudos=[76]))

    def test_no_owner_means_no_plan(self):
        self.assertEqual(probe.plan_knobs(dict(hard=2, reasons=[dict(owner="unassigned-or-eliminated",
                                                                    pseudo=9, reasons=["x"])])), [])

    def test_every_planned_knob_name_is_rankable(self):
        for rec in (LOCAL_REC, GLOBAL_REC):
            for k in probe.plan_knobs(rec):
                self.assertIn(k["name"], probe.KNOB_ORDER)


class DistanceTests(unittest.TestCase):
    def test_identical_listings_have_distance_zero(self):
        self.assertEqual(probe.distance(["a", "b"], ["a", "b"]), 0)

    def test_one_changed_line_counts_once(self):
        self.assertEqual(probe.distance(["a", "b", "c"], ["a", "x", "c"]), 1)

    def test_an_extra_line_counts(self):
        self.assertEqual(probe.distance(["a", "b"], ["a", "b", "c"]), 1)

    def test_a_missing_listing_is_not_a_number(self):
        self.assertIsNone(probe.distance(None, ["a"]))


class FallbackHookTests(unittest.TestCase):
    """The next_qty <= 3 hook for priority knobs can land after the second (inline) sort."""

    def test_a_fallback_whose_first_call_is_not_the_suggestions_pass_is_marked_late(self):
        res = dict(hook_used="blockfirst-fallback", first_free_just_try_suggested=0, block_next_qty=2)
        self.assertEqual(probe.fallback_status("presort", res), ("blockfirst-fallback-late", True))

    def test_a_fallback_inside_the_suggestions_pass_still_precedes_the_sort(self):
        res = dict(hook_used="blockfirst-fallback", first_free_just_try_suggested=1, block_next_qty=3)
        self.assertEqual(probe.fallback_status("presort", res), ("blockfirst-fallback", False))

    def test_an_unrecorded_flag_is_unknown_not_late(self):
        self.assertEqual(probe.fallback_status("presort", dict(hook_used="blockfirst-fallback")),
                         ("blockfirst-fallback", False))

    def test_a_knob_written_at_the_qsort_is_untouched(self):
        res = dict(hook_used="presort", first_free_just_try_suggested=0)
        self.assertEqual(probe.fallback_status("presort", res), ("presort", False))
        self.assertEqual(probe.fallback_status("own", dict(hook_used=None)), (None, False))

    def test_the_embedded_gdb_script_is_syntactically_valid(self):
        compile(probe.PROBE_SCRIPT, "probe.py", "exec")


class AgreementTests(unittest.TestCase):
    def test_target_knob_naming_the_pinned_variable_agrees(self):
        rec = dict(status="ok", var="value", sufficient=["sugg"], minimal_knob="sugg", competitor_names={})
        self.assertEqual(probe.agreement(rec, ["value", "other"]), "same-variable")
        self.assertEqual(probe.agreement(rec, ["other"]), "no-overlap")

    def test_competitor_knob_needs_the_competitor_name(self):
        rec = dict(status="ok", var="value", sufficient=["competitor-refs-1"],
                   minimal_knob="competitor-refs-1", competitor_names={})
        self.assertEqual(probe.agreement(rec, ["value"]), "competitor-unnamed")
        rec["competitor_names"] = {"competitor-refs-1": "target"}
        self.assertEqual(probe.agreement(rec, ["target"]), "competitor-variable-in-fix")

    def test_force_only_and_no_knob_are_distinguished(self):
        self.assertEqual(probe.agreement(dict(status="ok", var="v", sufficient=[], minimal_knob=None), []),
                         "no-sufficient-knob")
        self.assertEqual(probe.agreement(dict(status="ok", var="v", sufficient=["force"],
                                              minimal_knob=None, competitor_names={}), []), "force-only")
        self.assertEqual(probe.agreement(dict(status="untrusted"), []), "not-measured")


if __name__ == "__main__":
    unittest.main()
