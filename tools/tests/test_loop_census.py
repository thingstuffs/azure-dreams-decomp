"""loop_census: the `-dL` dump parser and the dump comparison are textual; no compiler is run.

The dump fragments below are the real 2.7.2 shapes (loop.c:1557 onward) taken from
work/native_lane/r64_astra_loop/dumps/: a two-function file, a phony loop, `move-insn ... not
desirable` -> ` moved to N`, a `cond forces N ... not safe` follower, `consec`, `halved since
already moved`, and a movable-count mismatch.
"""
import os, sys, unittest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "lanes"))
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import loop_census as L  # noqa: E402


PINNED = """;; Function func_801750E4


Loop from 128 to 394: 117 real insns.
Continue at insn 380.
Insn 227: regno 129 (life 2), move-insn savings 1 not desirable
Insn 247: regno 133 (life 4), move-insn savings 1 not desirable
Insn 266: regno 137 (life 3), consec 2, savings 1 not desirable
Insn 384: regno 172 (life 2), savings 2 not desirable
Insn 385: regno 173 (life 1), cond forces 384 not safe
Insn 247: possible biv, reg 133, const = 251
Reg 108: biv verified
Loop unrolling: Not basic or general induction var.
Cannot eliminate biv 108.
First use: insn 61, last use: insn 402.


Loop from 107 to 125 is phony.

(note 2 0 4 "" NOTE_INSN_DELETED)

(insn 247 244 249 (set (reg:QI 133)
        (const_int 251)) -1 (nil)
    (expr_list:REG_EQUAL (const_int 251)
        (nil)))

(insn 384 383 385 (set (reg:SI 172)
        (zero_extend:SI (reg/v:HI 97))) -1 (nil)
    (nil))

(insn 385 384 387 (set (reg:SI 173)
        (ashift:SI (reg:SI 172)
            (const_int 16))) -1 (nil)
    (nil))

;; Function other


Loop at 44 ignored due to multiple entry points.

(insn 4 2 8 (set (reg:SI 81)
        (reg:SI 4 a0)) 168 {movsi_internal2} (nil)
    (nil))
"""

ERASED = """;; Function func_801750E4


Loop from 122 to 341: 81 real insns.
Continue at insn 330.
Insn 176: regno 125 (life 2), move-insn savings 1 not desirable
Insn 196: regno 129 (life 4), move-insn savings 1  moved to 356
Insn 215: regno 133 (life 3), consec 2, savings 1 not desirable
Insn 331: regno 167 (life 2), savings 2 halved since already moved  moved to 357
Insn 332: regno 168 (life 1), cond forces 331 savings 1  moved to 358
Insn 196: possible biv, reg 129, const = 251
Reg 104: biv verified
Loop unrolling: Not basic or general induction var.
Cannot eliminate biv 104.
First use: insn 55, last use: insn 349.


Loop from 103 to 119 is phony.

(note 2 0 4 "" NOTE_INSN_DELETED)

(insn 356 3 357 (set (reg:QI 129)
        (const_int 251)) -1 (nil)
    (expr_list:REG_EQUAL (const_int 251)
        (nil)))

(insn 357 356 358 (set (reg:SI 167)
        (zero_extend:SI (reg/v:HI 93))) -1 (nil)
    (nil))

(insn 358 357 5 (set (reg:SI 168)
        (ashift:SI (reg:SI 167)
            (const_int 16))) -1 (nil)
    (nil))

;; Function other


Loop at 40 ignored due to multiple entry points.

(insn 4 2 8 (set (reg:SI 81)
        (reg:SI 4 a0)) 168 {movsi_internal2} (nil)
    (nil))
"""


class Parser(unittest.TestCase):
    def test_split_functions(self):
        fs = L.split_functions(PINNED)
        self.assertEqual([n for n, _, _ in fs], ["func_801750E4", "other"])
        self.assertIn("117 real insns", fs[0][1])
        self.assertNotIn("(insn 247", fs[0][1])          # RTL is not in the diagnostics half
        self.assertIn("(insn 247", fs[0][2])

    def test_loop_records(self):
        loops = L.parse_loops(L.split_functions(PINNED)[0][1])
        self.assertEqual([l["kind"] for l in loops], ["real", "phony"])
        self.assertEqual(loops[0]["insns"], 117)
        self.assertEqual((loops[0]["start"], loops[0]["end"]), (128, 394))
        self.assertIsNone(loops[1]["insns"])
        self.assertEqual(L.parse_loops(L.split_functions(PINNED)[1][1])[0]["kind"], "ignored")

    def test_movable_lines(self):
        m = L.parse_loops(L.split_functions(PINNED)[0][1])[0]["movables"]
        self.assertEqual(len(m), 5)
        self.assertEqual([x["status"] for x in m],
                         ["not desirable"] * 4 + ["not safe"])
        self.assertEqual(m[1]["uid"], 247)
        self.assertEqual((m[1]["regno"], m[1]["life"], m[1]["savings"]), (133, 4, 1))
        self.assertIn("move_insn", m[1]["flags"])
        self.assertEqual(m[2]["consec"], 2)
        self.assertEqual(m[4]["forces"], 384)
        self.assertIn("cond", m[4]["flags"])
        self.assertIsNone(m[4]["savings"])               # `not safe`: savings is never printed

    def test_moved_and_halved(self):
        m = L.parse_loops(L.split_functions(ERASED)[0][1])[0]["movables"]
        self.assertEqual([x["status"] for x in m],
                         ["not desirable", "moved", "not desirable", "moved", "moved"])
        self.assertEqual(m[1]["moved_to"], 356)
        self.assertIn("halved", m[3]["flags"])
        self.assertEqual(m[4]["moved_to"], 358)          # two spaces before ` moved to`

    def test_other_diagnostics(self):
        l0 = L.parse_loops(L.split_functions(PINNED)[0][1])[0]
        self.assertEqual(l0["unroll"], ["Loop unrolling: Not basic or general induction var."])
        self.assertEqual(l0["biv_dec"], ["Cannot eliminate biv #."])          # a decision
        self.assertEqual(l0["biv_info"], ["Insn #: possible biv, reg #, const = 251",
                                          "Reg #: biv verified"])            # analysis notes
        self.assertEqual(l0["giv_dec"], [])
        self.assertEqual(l0["giv_info"], [])

    def test_rtl_expr(self):
        rtl = L.split_functions(PINNED)[0][2]
        self.assertEqual(L.rtl_expr(rtl, 247), ("(const_int 251)", "QI"))
        self.assertEqual(L.rtl_expr(rtl, 384), ("(zero_extend:SI (reg:HI ?))", "SI"))
        self.assertEqual(L.rtl_expr(rtl, 385), ("(ashift:SI (reg:SI ?) (const_int 16))", "SI"))
        self.assertEqual(L.rtl_expr(rtl, 999), (None, None))
        hard = L.split_functions(PINNED)[1][2]
        self.assertEqual(L.rtl_expr(hard, 4), ("(reg:SI 4 a0)", "SI"))   # hard regs keep their name

    def test_loop_counts(self):
        self.assertEqual(L.loop_counts(L.split_functions(PINNED)), [117])
        self.assertEqual(L.loop_counts(L.split_functions(ERASED)), [81])


class Compare(unittest.TestCase):
    def test_transitions(self):
        trans, refusal = L.compare(L.split_functions(PINNED), L.split_functions(ERASED))
        self.assertIsNone(refusal)
        kinds = [t["kind"] for t in trans]
        self.assertEqual(kinds.count("hoist_gained"), 2)
        self.assertEqual(kinds.count("forced_follow"), 1)      # the `forces 384` follower
        self.assertNotIn("hoist_lost", kinds)
        h = [t for t in trans if t["kind"] == "hoist_gained"]
        self.assertEqual(h[0]["expr"], "(const_int 251)")
        self.assertEqual(h[0]["mode"], "QI")
        self.assertEqual((h[0]["life"], h[0]["savings"]), (4, 1))
        self.assertEqual(h[0]["insns"], [117, 81])
        self.assertEqual(h[1]["expr"], "(zero_extend:SI (reg:HI ?))")
        # the biv regnos and insn UIDs are normalised away and the unroll message is identical,
        # so neither is a decision change
        self.assertNotIn("biv_changed", kinds)
        self.assertNotIn("unroll_changed", kinds)

    def test_decisions_flag_but_analysis_notes_do_not(self):
        """`possible biv ... const = N` is an analysis note; the unrolling verdict is a decision."""
        e = ERASED.replace("const = 251", "const = 4").replace(
            "Loop unrolling: Not basic or general induction var.", "Loop unrolling: 8 iterations.")
        trans, refusal = L.compare(L.split_functions(PINNED), L.split_functions(e))
        self.assertIsNone(refusal)
        kinds = [t["kind"] for t in trans]
        self.assertIn("biv_info_changed", kinds)               # `const = N` survives normalisation
        self.assertNotIn("biv_info_changed", L.FLAGGING)       # but it never flags a row
        self.assertIn("unroll_changed", kinds)
        self.assertIn("unroll_changed", L.FLAGGING)

    def test_giv_decision_is_flagging(self):
        e = ERASED.replace("Reg 104: biv verified",
                           "giv of insn 300 not worth while, 3 vs 5.")
        trans, _ = L.compare(L.split_functions(PINNED), L.split_functions(e))
        self.assertIn("giv_decision_changed", [t["kind"] for t in trans])
        self.assertIn("giv_decision_changed", L.FLAGGING)

    def test_no_transition_when_only_the_count_moves(self):
        """A count change with no decision change is NOT evidence (r64 NOTE, section 3)."""
        e = ERASED.replace(" moved to 356", "not desirable").replace("81 real insns", "111 real insns")
        e = e.replace("halved since already moved  moved to 357", "not desirable")
        e = e.replace(", cond forces 331 savings 1  moved to 358", ", cond forces 331 not safe")
        trans, refusal = L.compare(L.split_functions(PINNED), L.split_functions(e))
        self.assertIsNone(refusal)
        self.assertEqual([t["kind"] for t in trans if t["kind"] in L.PRIMARY], [])

    def test_loop_count_mismatch_refused(self):
        e = ERASED.replace("Loop from 103 to 119 is phony.",
                           "Loop from 103 to 119: 9 real insns.")
        trans, refusal = L.compare(L.split_functions(PINNED), L.split_functions(e))
        self.assertEqual(trans, [])
        self.assertTrue(refusal.startswith("loop_count_differs:func_801750E4:1_vs_2"), refusal)

    def test_function_set_change_refused(self):
        e = ERASED.replace(";; Function other", ";; Function gone")
        _, refusal = L.compare(L.split_functions(PINNED), L.split_functions(e))
        self.assertEqual(refusal, "function_set_changed")

    def test_same_length_but_different_movables_is_realigned(self):
        """Erasure can drop one movable and add another: a blind positional pair would invent a
        decision change, so the loop is re-paired by defining expression instead."""
        e = ERASED.replace("(zero_extend:SI (reg/v:HI 93))", "(neg:SI (reg:SI 93))")
        trans, refusal = L.compare(L.split_functions(PINNED), L.split_functions(e))
        self.assertIsNone(refusal)
        kinds = [t["kind"] for t in trans]
        self.assertIn("positional_realigned", kinds)
        self.assertNotIn("positional_realigned", L.FLAGGING)
        exprs = [t["expr"] for t in trans if t["kind"] in L.PRIMARY]
        self.assertIn("(const_int 251)", exprs)                       # still paired by expression
        self.assertNotIn("(zero_extend:SI (reg:HI ?))", exprs)        # its partner is gone, not flipped
        self.assertIn("movable_set_changed", kinds)

    def test_movable_set_change_matched_by_expression(self):
        """Fewer movables: the survivors still pair by expression, the rest are reported as such."""
        e = "\n".join(l for l in ERASED.splitlines() if not l.startswith("Insn 215:"))
        trans, refusal = L.compare(L.split_functions(PINNED), L.split_functions(e))
        self.assertIsNone(refusal)
        self.assertIn("movable_set_changed", [t["kind"] for t in trans])
        self.assertEqual([t["kind"] for t in trans].count("hoist_gained"), 2)


class PinGroups(unittest.TestCase):
    TEXT = '''#include "common.h"
void f(s32 n) {
    register s32 angle ASM_REG("$21");
    s32 i;
    for (i = 0; i < n; i++) {
        ASM_USE_NV(angle);
        ASM_USE_NV(angle);
        ASM_USE_NV(angle);
        ASM_USE_NV(angle);
        ASM_USE_NV(other);
        ASM_KEEP(i);
    }
}
'''

    def test_use_runs(self):
        from pin_census import sites_of
        sites = sites_of(self.TEXT)
        self.assertEqual(L.use_runs(sites), [("ASM_USE_NV", "angle", 4)])

    def test_pin_groups_largest_first(self):
        from pin_census import sites_of
        g = L.pin_groups(sites_of(self.TEXT))
        self.assertEqual(g[0][0], "ASM_USE_NV(angle)")
        self.assertEqual(len(g[0][1]), 4)
        self.assertEqual({k for k, _ in g},
                         {"ASM_USE_NV(angle)", "ASM_USE_NV(other)", "ASM_KEEP(i)",
                          "ASM_REG($21 angle)"})   # a register pin is keyed by its variable too

    def test_loop_keyword_skip(self):
        self.assertTrue(L.LOOP_KW.search("    for (i = 0; i < n; i++) {"))
        self.assertTrue(L.LOOP_KW.search("    } while (p);"))
        self.assertIsNone(L.LOOP_KW.search("    s32 forward = doorway;"))


if __name__ == "__main__":
    unittest.main()
