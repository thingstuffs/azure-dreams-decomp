"""T90b: statement splitting, the nested-call finder, the host rule and the two placements are
textual; the listing screen and `vf` are not exercised."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t90_callunnest as M  # noqa: E402

NEST = '''#include "common.h"
void f(void *effect_state, void *saved_effect_id, void *animation) {
    s32 effect_result;
    s32 target;
    register s32 effect_id ASM_REG("$5");   /* UNRESOLVED C shape (pin) */

    effect_result = func_800990FC();
    target = ((S_0 *)effect_state)->unk_11C;
    effect_id = effect_result;
    saved_effect_id = effect_id;
    func_80099290(func_80099194(D_800E0683,
        func_80099734(target, effect_id)));
    func_800A5720(saved_effect_id);
}
'''

LIVE = '''#include "common.h"
void g(void *state) {
    s32 kept;
    s32 other;

    kept = func_800990FC();
    ASM_KEEP(kept);   /* UNRESOLVED C shape (pin) */
    other = 1;
    func_80099290(func_80099194(D_800E0683, func_80099734(state, other)));
    D_80020090 = kept;
}
'''

FLAT = '''#include "common.h"
void h(void *state) {
    s32 kept;

    kept = func_800990FC();
    ASM_KEEP(kept);   /* UNRESOLVED C shape (pin) */
    func_80099290(state);
}
'''


def labels(text):
    return [c[0] for c in M.candidates(text)]


def by_label(text):
    return dict((c[0], c[1]) for c in M.candidates(text))


class TestDetection(unittest.TestCase):
    def test_the_inner_call_is_the_one_named(self):
        self.assertTrue([x for x in labels(NEST) if x.startswith("unnest:func_80099734>effect_result@")],
                        labels(NEST))

    def test_the_outer_call_is_never_named(self):
        self.assertEqual([x for x in labels(NEST) if "func_80099290" in x], [])

    def test_afterhost_places_the_assignment_at_the_hosts_death(self):
        cand = by_label(NEST)["unnest:func_80099734>effect_result@11:afterhost"]
        lines = [x.strip() for x in cand.splitlines()]
        i = lines.index("effect_result = func_80099734(target, effect_id);")
        self.assertEqual(lines[i - 1], "effect_id = effect_result;")
        self.assertEqual(lines[i + 1], "saved_effect_id = effect_id;")

    def test_the_statement_is_folded_onto_one_line(self):
        cand = by_label(NEST)["unnest:func_80099734>effect_result@11:afterhost"]
        self.assertIn("    func_80099290(func_80099194(D_800E0683, effect_result));\n", cand)

    def test_before_places_the_assignment_at_the_statement(self):
        cand = by_label(NEST)["unnest:func_80099734>effect_result@11:before"]
        lines = [x.strip() for x in cand.splitlines()]
        i = lines.index("effect_result = func_80099734(target, effect_id);")
        self.assertEqual(lines[i - 1], "saved_effect_id = effect_id;")

    def test_the_pin_is_left_for_the_erase_plan(self):
        for _, cand, _, _ in M.candidates(NEST):
            self.assertIn('ASM_REG("$5")', cand)


class TestRefusals(unittest.TestCase):
    def test_a_host_still_read_below_is_refused(self):
        self.assertEqual([x for x in labels(LIVE) if ">kept@" in x], [])

    def test_a_statement_without_a_nested_call_offers_nothing(self):
        self.assertEqual(labels(FLAT), [])

    def test_eligible_needs_pins(self):
        self.assertEqual(M.T.eligible("void f(void) {}\n", {}, {}), "no pins")

    def test_eligible_accepts_the_exemplar_shape(self):
        self.assertIsNone(M.T.eligible(NEST, {}, {}))


class TestScanner(unittest.TestCase):
    def test_statements_split_at_semicolons_not_inside_parentheses(self):
        body = "void f(void) {\n    a = g(1, 2);\n    for (i = 0; i < 3; i++) { b = 1; }\n}\n"
        st = M.statements(body, body.index("{"), len(body) - 2)
        got = [" ".join(body[s:e].split()) for s, e in st]
        self.assertIn("a = g(1, 2);", got)
        self.assertIn("b = 1;", got)

    def test_nested_calls_skips_the_outermost_and_the_non_innermost(self):
        s = "    f(g(h(x)), 1);"
        got = [s[a:b] for a, b in M.nested_calls(s, 0, len(s))]
        self.assertEqual(got, ["h(x)"])


if __name__ == "__main__":
    unittest.main()
