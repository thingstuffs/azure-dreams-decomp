"""Unit tests for tools/xform/t65_regroute.py: each move, its refusals, and the probe gating.

No compiler runs: `t65.SCREEN` is replaced by a stub, so `apply_verified` is exercised end to end
with a fake `vf`.
"""
import json
import os
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from common import sha_text
from pin_census import sites_of
from xform import t65_regroute as t65


def txt(*lines):
    return "".join(l + "\n" for l in lines)


def labels(gen):
    return [l for l, _ in gen]


def by_label(gen, head):
    return {l: c for l, c in gen if l.startswith(head)}


def ctx_of(text, var, reg, line=1):
    return t65.Ctx(text, var, reg, line)


# --------------------------------------------------------------------------- $2 moves

RET = txt(
    "s32 func_1(s32 arg0) {",
    "    s32 total;",
    "    s32 other;",
    "",
    "    other = arg0 + 1;",
    "    total = other * 3;",
    "    return total + 7;",
    "}")


class ReturnMoves(unittest.TestCase):
    def test_ret_op_rewrites_through_the_variable(self):
        c = ctx_of(RET, "total", 2, 7)
        out = by_label(t65.return_moves(c, t65.collections.Counter()), "t65:ret-op")
        self.assertEqual(len(out), 1)
        got = list(out.values())[0]
        self.assertIn("total = total + 7;", got)
        self.assertIn("return total;", got)

    def test_ret_via_rewrites_a_foreign_expression(self):
        text = RET.replace("return total + 7;", "return other * 5;")
        c = ctx_of(text, "total", 2, 7)
        out = by_label(t65.return_moves(c, t65.collections.Counter()), "t65:ret-via")
        got = list(out.values())[0]
        self.assertIn("total = other * 5;", got)
        self.assertIn("return total;", got)

    def test_refuses_a_return_type_mismatch(self):
        text = RET.replace("s32 total;", "u8 total;")
        sk = t65.collections.Counter()
        self.assertEqual(labels(t65.return_moves(ctx_of(text, "total", 2, 7), sk)), [])
        self.assertTrue(sk["return-type-mismatch"])

    def test_refuses_a_volatile_target(self):
        text = RET.replace("s32 total;", "volatile s32 total;")
        sk = t65.collections.Counter()
        self.assertEqual(labels(t65.return_moves(ctx_of(text, "total", 2, 7), sk)), [])
        self.assertTrue(sk["target-not-writable"])

    def test_refuses_a_side_effecting_return_expression(self):
        text = RET.replace("return total + 7;", "return other++;")
        sk = t65.collections.Counter()
        self.assertEqual(labels(t65.return_moves(ctx_of(text, "total", 2, 7), sk)), [])
        self.assertTrue(sk["return-expression-has-a-side-effect"])

    def test_no_edit_inside_an_ifdef_arm(self):
        text = txt(
            "s32 func_1(s32 arg0) {",
            "    s32 total;",
            "",
            "    total = arg0;",
            "#ifdef NON_MATCHING",
            "    return arg0 + 1;",
            "#else",
            "    return total;",
            "#endif",
            "}")
        got = labels(t65.return_moves(ctx_of(text, "total", 2, 4), t65.collections.Counter()))
        self.assertEqual(got, [])


CALLRES = txt(
    "s32 func_1(s32 arg0) {",
    "    s32 raw;",
    "    s32 scaled;",
    "",
    "    raw = helper(arg0);",
    "    scaled = raw * 4;",
    "    store(scaled);",
    "    return 0;",
    "}")


class CallResultMoves(unittest.TestCase):
    def test_call_goes_straight_into_the_target(self):
        out = by_label(t65.call_result_moves(ctx_of(CALLRES, "scaled", 2, 6),
                                             t65.collections.Counter()), "t65:call-into")
        got = list(out.values())[0]
        self.assertIn("scaled = helper(arg0);", got)
        self.assertIn("scaled = scaled * 4;", got)
        self.assertNotIn("s32 raw;", got)           # the dead declaration goes with the copy
        self.assertNotIn("raw", got)

    def test_plain_copy_drops_the_second_line(self):
        text = CALLRES.replace("scaled = raw * 4;", "scaled = raw;")
        out = by_label(t65.call_result_moves(ctx_of(text, "scaled", 2, 6),
                                             t65.collections.Counter()), "t65:call-into")
        got = list(out.values())[0]
        self.assertIn("scaled = helper(arg0);", got)
        self.assertNotIn("raw", got)

    def test_refuses_when_the_intermediate_is_used_again(self):
        text = CALLRES.replace("store(scaled);", "store(raw);")
        sk = t65.collections.Counter()
        self.assertEqual(labels(t65.call_result_moves(ctx_of(text, "scaled", 2, 6), sk)), [])
        self.assertTrue(sk["call-result-not-single-use"])

    def test_refuses_when_the_target_is_read_in_between(self):
        text = CALLRES.replace("    scaled = raw * 4;",
                               "    store(scaled);\n    scaled = raw * 4;")
        sk = t65.collections.Counter()
        self.assertEqual(labels(t65.call_result_moves(ctx_of(text, "scaled", 2, 7), sk)), [])
        self.assertTrue(sk["target-read-between-call-and-use"])

    def test_refuses_a_width_change(self):
        text = CALLRES.replace("s32 raw;", "s16 raw;")
        self.assertEqual(labels(t65.call_result_moves(ctx_of(text, "scaled", 2, 6),
                                                      t65.collections.Counter())), [])


# --------------------------------------------------------------------------- $4-$7 moves

ARGS = txt(
    "void func_1(s32 arg0, s32 arg1) {",
    "    s32 index;",
    "",
    "    index = arg0 * 12;",
    "    helper(arg1, arg0 * 12);",
    "    use(index);",
    "}")


class ArgumentMoves(unittest.TestCase):
    def test_argument_that_already_is_the_value_becomes_the_variable(self):
        out = by_label(t65.argument_moves(ctx_of(ARGS, "index", 5, 4),
                                          t65.collections.Counter()), "t65:arg-sub")
        got = list(out.values())[0]
        self.assertIn("helper(arg1, index);", got)

    def test_refuses_an_argument_that_is_not_the_variables_value(self):
        text = ARGS.replace("helper(arg1, arg0 * 12);", "helper(arg1, arg0 * 13);")
        got = by_label(t65.argument_moves(ctx_of(text, "index", 5, 4),
                                          t65.collections.Counter()), "t65:arg-sub")
        self.assertEqual(got, {})

    def test_refuses_when_an_operand_changes_before_the_call(self):
        text = ARGS.replace("    helper(arg1, arg0 * 12);",
                            "    arg0 = arg0 + 1;\n    helper(arg1, arg0 * 12);")
        sk = t65.collections.Counter()
        got = by_label(t65.argument_moves(ctx_of(text, "index", 5, 4), sk), "t65:arg-sub")
        self.assertEqual(got, {})
        self.assertTrue(sk["argument-operand-changed-before-the-call"])

    def test_hoists_an_argument_expression_when_the_target_is_dead(self):
        text = txt(
            "void func_1(s32 arg0, s32 arg1) {",
            "    s32 index;",
            "",
            "    index = arg0;",
            "    helper(arg1, index * 12);",
            "}")
        out = by_label(t65.argument_moves(ctx_of(text, "index", 5, 4),
                                          t65.collections.Counter()), "t65:arg-hoist")
        got = list(out.values())[0]
        self.assertIn("index = index * 12;", got)
        self.assertIn("helper(arg1, index);", got)

    def test_refuses_the_hoist_when_the_target_is_live_after(self):
        text = txt(
            "void func_1(s32 arg0, s32 arg1) {",
            "    s32 index;",
            "",
            "    index = arg0;",
            "    helper(arg1, index * 12);",
            "    use(index);",
            "}")
        sk = t65.collections.Counter()
        got = by_label(t65.argument_moves(ctx_of(text, "index", 5, 4), sk), "t65:arg-hoist")
        self.assertEqual(got, {})
        self.assertTrue(sk["target-live-after-the-call"])

    def test_refuses_when_the_prototype_holds_a_64_bit_parameter(self):
        text = ARGS.replace("void func_1(s32 arg0, s32 arg1) {", "void func_1(f32 arg0, s32 arg1) {")
        sk = t65.collections.Counter()
        self.assertEqual(labels(t65.argument_moves(ctx_of(text, "index", 5, 4), sk)), [])
        self.assertTrue(sk["parameter-slots-unresolved"])


MERGE = txt(
    "void func_1(s32 arg0, s32 arg1) {",
    "    s32 cursor;",
    "",
    "    cursor = arg1;",
    "    while (cursor != 0) {",
    "        cursor = step(cursor);",
    "    }",
    "    use(arg0);",
    "}")


class ParamMergeMoves(unittest.TestCase):
    def test_both_directions(self):
        out = dict(t65.param_merge_moves(ctx_of(MERGE, "cursor", 5, 4),
                                         t65.collections.Counter()))
        self.assertEqual(sorted(k.split(":")[1] for k in out), ["merge-to-local", "merge-to-param"])
        a = out["t65:merge-to-param:arg1:4"]
        self.assertNotIn("cursor", a)
        self.assertIn("while (arg1 != 0)", a)
        b = out["t65:merge-to-local:cursor:4"]
        self.assertIn("void func_1(s32 arg0, s32 cursor)", b)
        self.assertNotIn("arg1", b)
        for got in (a, b):
            self.assertEqual(got.count("\n"), MERGE.count("\n") - 2)  # copy + declaration gone

    def test_refuses_when_the_parameter_is_used_after_the_merge_point(self):
        text = MERGE.replace("use(arg0);", "use(arg1);")
        sk = t65.collections.Counter()
        self.assertEqual(labels(t65.param_merge_moves(ctx_of(text, "cursor", 5, 4), sk)), [])
        self.assertTrue(sk["parameter-used-after-the-merge-point"])

    def test_refuses_a_type_difference(self):
        text = MERGE.replace("s32 cursor;", "u8 *cursor;")
        sk = t65.collections.Counter()
        self.assertEqual(labels(t65.param_merge_moves(ctx_of(text, "cursor", 5, 4), sk)), [])
        self.assertTrue(sk["parameter-type-differs"])

    def test_refuses_the_wrong_slot(self):
        sk = t65.collections.Counter()
        self.assertEqual(labels(t65.param_merge_moves(ctx_of(MERGE, "cursor", 4, 4), sk)), [])
        self.assertTrue(sk["no-copy-of-the-parameter-into-the-target"])

    def test_refuses_a_slot_the_function_has_no_parameter_for(self):
        sk = t65.collections.Counter()
        self.assertEqual(labels(t65.param_merge_moves(ctx_of(MERGE, "cursor", 6, 4), sk)), [])
        self.assertTrue(sk["function-has-fewer-parameters-than-the-slot"])

    def test_refuses_when_the_target_is_used_before_the_copy(self):
        text = MERGE.replace("    cursor = arg1;", "    use(cursor);\n    cursor = arg1;")
        sk = t65.collections.Counter()
        self.assertEqual(labels(t65.param_merge_moves(ctx_of(text, "cursor", 5, 5), sk)), [])
        self.assertTrue(sk["target-used-before-the-copy"])


# --------------------------------------------------------------------------- order-swap moves

ORDER = txt(
    "void func_1(s32 arg0) {",
    "    s32 base;",
    "    s32 tail;",
    "",
    "    base = arg0 * 4;",
    "    tail = arg0 + 1;",
    "    sink(tail);",
    "    sink(base);",
    "}")


class OrderMoves(unittest.TestCase):
    def test_inline_folds_a_single_use_definition(self):
        out = by_label(t65.inline_moves(ctx_of(ORDER, "base", 18, 5),
                                        t65.collections.Counter()), "t65:inline")
        got = list(out.values())[0]
        self.assertIn("sink(((s32)(arg0 * 4)));", got)
        self.assertNotIn("s32 base;", got)

    def test_inline_refuses_a_second_use(self):
        text = ORDER.replace("sink(tail);", "sink(base);")
        sk = t65.collections.Counter()
        self.assertEqual(labels(t65.inline_moves(ctx_of(text, "base", 18, 5), sk)), [])
        self.assertTrue(sk["inline-not-single-definition-single-use"])

    def test_inline_refuses_when_an_operand_changes(self):
        text = ORDER.replace("    tail = arg0 + 1;", "    arg0 = arg0 + 1;\n    tail = 1;")
        sk = t65.collections.Counter()
        self.assertEqual(labels(t65.inline_moves(ctx_of(text, "base", 18, 5), sk)), [])
        self.assertTrue(sk["inline-operand-changed-between"])

    def test_inline_keeps_a_qualifier_by_refusing(self):
        text = ORDER.replace("s32 base;", "const s32 base;")
        got = by_label(t65.inline_moves(ctx_of(text, "base", 18, 5),
                                        t65.collections.Counter()), "t65:inline")
        self.assertIn("(const s32)", list(got.values())[0])    # the cast carries the qualifier

    def test_sink_moves_the_definition_to_its_first_use(self):
        out = by_label(t65.sink_moves(ctx_of(ORDER, "base", 18, 5),
                                      t65.collections.Counter()), "t65:sink")
        got = list(out.values())[0]
        lines = [l.strip() for l in got.splitlines() if l.strip()]
        self.assertEqual(lines.index("base = arg0 * 4;"), lines.index("sink(base);") - 1)

    def test_sink_refuses_a_dependence(self):
        text = ORDER.replace("    tail = arg0 + 1;", "    arg0 = 3;")
        sk = t65.collections.Counter()
        self.assertEqual(labels(t65.sink_moves(ctx_of(text, "base", 18, 5), sk)), [])
        self.assertTrue(sk["sink-crosses-a-dependence"])

    def test_hoist_gives_the_variable_one_more_reference(self):
        text = txt(
            "void func_1(s32 arg0) {",
            "    s32 base;",
            "    s32 other;",
            "",
            "    base = arg0 * 4;",
            "    sink(base);",
            "    other = arg0 * 4;",
            "}")
        out = by_label(t65.hoist_moves(ctx_of(text, "base", 18, 5),
                                       t65.collections.Counter()), "t65:hoist")
        got = list(out.values())[0]
        self.assertIn("other = base;", got)
        self.assertEqual(got.count("base = arg0 * 4;"), 1)


# --------------------------------------------------------------------------- round 28 review
#
# One test per demonstrated defect.  Each asserts the REFUSAL (or the corrected output), and the
# comment names the broken text the tool used to emit.

class ValuePreservation(unittest.TestCase):
    """Defect 3: a routed expression whose own type was never checked."""

    FLOAT = txt(
        "extern f32 helper(s32);",
        "extern void sink(s32);",
        "s32 func_1(s32 arg0) {",
        "    s32 value;",
        "",
        "    value = 0;",
        "    sink(helper(arg0));",
        "    return arg0;",
        "}")

    def test_call_via_refuses_a_callee_whose_return_type_is_not_the_targets(self):
        # was: `value = helper(arg0); sink(value);` - the f32 result truncated to s32.
        sk = t65.collections.Counter()
        self.assertEqual(labels(t65.call_via_moves(ctx_of(self.FLOAT, "value", 2, 7), sk)), [])
        self.assertTrue(sk["route-expression-type-differs-from-the-target"])

    def test_call_via_refuses_a_void_callee(self):
        text = self.FLOAT.replace("extern f32 helper(s32);", "extern void helper(s32);")
        sk = t65.collections.Counter()
        got = [l for l in labels(t65.call_via_moves(ctx_of(text, "value", 2, 7), sk))
               if "helper" in l]
        self.assertEqual(got, [])                  # was: `value = helper(arg0);`

    def test_call_via_accepts_a_matching_return_type(self):
        text = self.FLOAT.replace("extern f32 helper(s32);", "extern s32 helper(s32);")
        out = by_label(t65.call_via_moves(ctx_of(text, "value", 2, 7),
                                          t65.collections.Counter()), "t65:call-via:helper")
        got = list(out.values())[0]
        self.assertIn("value = helper(arg0);", got)
        self.assertIn("sink(value);", got)

    def test_call_via_refuses_an_undeclared_callee(self):
        text = self.FLOAT.replace("extern f32 helper(s32);", "")
        sk = t65.collections.Counter()
        self.assertEqual(labels(t65.call_via_moves(ctx_of(text, "value", 2, 7), sk)), [])
        self.assertTrue(sk["call-via-callee-return-type-unknown"])

    def test_arg_via_refuses_a_floating_expression(self):
        # m2c prototypes are empty, so the argument's own spelling is the only check there is.
        text = txt(
            "extern void sink(s32, s32);",
            "void func_1(s32 arg0) {",
            "    s32 value;",
            "    f32 scale;",
            "",
            "    scale = 2.5f;",
            "    value = 0;",
            "    sink(arg0, scale * 2.0f);",
            "}")
        sk = t65.collections.Counter()
        self.assertEqual(labels(t65.arg_via_moves(ctx_of(text, "value", 5, 8), sk)), [])
        self.assertTrue(sk["route-expression-may-be-floating-or-64-bit"])

    def test_arg_sub_refuses_a_narrow_target(self):
        text = txt(
            "void func_1(s32 arg0, s32 arg1) {",
            "    u8 index;",
            "",
            "    index = arg0 * 12;",
            "    helper(arg1, arg0 * 12);",
            "}")
        sk = t65.collections.Counter()
        got = by_label(t65.argument_moves(ctx_of(text, "index", 5, 4), sk), "t65:arg-sub")
        self.assertEqual(got, {})                  # (u8)(arg0 * 12) is not arg0 * 12
        self.assertTrue(sk["argument-substitution-may-change-the-value-width"])


class StatementExpansion(unittest.TestCase):
    """Defect 4: a move that expands, deletes or inserts at a brace-less controlled statement."""

    def test_ret_via_refuses_a_brace_less_if_body(self):
        # was: `if (a > 1) v = g(a); return v;` - the return left the conditional and the rest of
        # the function became unreachable.
        text = txt(
            "s32 func_1(s32 arg0, s32 *out) {",
            "    s32 value;",
            "",
            "    value = 1;",
            "    if (arg0 > 1)",
            "        return helper(arg0);",
            "    *out = 3;",
            "    return value;",
            "}")
        sk = t65.collections.Counter()
        self.assertEqual(labels(t65.return_moves(ctx_of(text, "value", 2, 4), sk)), [])
        self.assertTrue(sk["return-is-a-brace-less-controlled-statement"])

    def test_arg_via_refuses_a_brace_less_else_body(self):
        text = txt(
            "void func_1(s32 arg0, s32 arg1) {",
            "    s32 value;",
            "",
            "    value = 0;",
            "    if (arg0)",
            "        sink(1, 2);",
            "    else",
            "        sink(arg0, arg1 + 1);",
            "}")
        sk = t65.collections.Counter()
        self.assertEqual(labels(t65.arg_via_moves(ctx_of(text, "value", 5, 8), sk)), [])
        self.assertTrue(sk["route-line-is-a-brace-less-controlled-statement"])

    def test_a_braced_arm_is_still_allowed(self):
        text = txt(
            "void func_1(s32 arg0, s32 arg1) {",
            "    s32 value;",
            "",
            "    value = 0;",
            "    if (arg0) {",
            "        sink(arg0, arg1 + 1);",
            "    }",
            "}")
        out = by_label(t65.arg_via_moves(ctx_of(text, "value", 5, 6),
                                         t65.collections.Counter()), "t65:arg-via")
        self.assertIn("value = arg1 + 1;", list(out.values())[0])

    def test_inline_refuses_to_delete_a_brace_less_definition(self):
        text = txt(
            "void func_1(s32 arg0) {",
            "    s32 base;",
            "",
            "    if (arg0)",
            "        base = arg0 * 4;",
            "    sink(base);",
            "}")
        sk = t65.collections.Counter()
        self.assertEqual(labels(t65.inline_moves(ctx_of(text, "base", 18, 5), sk)), [])
        self.assertTrue(sk["definition-is-a-brace-less-controlled-statement"])

    def test_standalone_sees_a_label(self):
        text = txt(
            "void func_1(s32 arg0) {",
            "    s32 base;",
            "",
            "    base = arg0;",
            "block_1:",
            "    sink(base);",
            "}")
        c = ctx_of(text, "base", 18, 4)
        self.assertTrue(c.standalone(3))
        self.assertFalse(c.standalone(5))


class TokenBoundaries(unittest.TestCase):
    """Defects 1 and 2: a substring or `\\b`-only match that rewrote a different object."""

    def test_hoist_refuses_an_occurrence_inside_a_longer_identifier(self):
        # was: `w = xa + b;` -> `w = xv;` (an undeclared symbol that sometimes compiles).
        text = txt(
            "void func_1(s32 arg0, s32 arg1, s32 xarg0) {",
            "    s32 value;",
            "    s32 other;",
            "",
            "    value = arg0 + arg1;",
            "    other = xarg0 + arg1;",
            "    sink(value);",
            "}")
        self.assertEqual(labels(t65.hoist_moves(ctx_of(text, "value", 18, 5),
                                                t65.collections.Counter())), [])

    def test_hoist_refuses_a_partial_expression(self):
        # was: `other = arg0 + arg1 * 2;` -> `other = value * 2;` (a precedence change).
        text = txt(
            "void func_1(s32 arg0, s32 arg1) {",
            "    s32 value;",
            "    s32 other;",
            "",
            "    value = arg0 + arg1;",
            "    other = arg0 + arg1 * 2;",
            "    sink(value);",
            "}")
        self.assertEqual(labels(t65.hoist_moves(ctx_of(text, "value", 18, 5),
                                                t65.collections.Counter())), [])

    def test_hoist_refuses_the_left_hand_side_of_a_store(self):
        # was: `unk->unk_14 = value | 0xC;` -> `value = value | 0xC;` - the store was DELETED.
        text = txt(
            "typedef struct S_1 {",
            "    s32 unk_14;",
            "} S_1;",
            "void func_1(void *arg0) {",
            "    s32 value;",
            "",
            "    value = ((S_1 *)arg0)->unk_14;",
            "    ((S_1 *)arg0)->unk_14 = value | 0xC;",
            "    sink(value);",
            "}")
        got = labels(t65.hoist_moves(ctx_of(text, "value", 18, 7), t65.collections.Counter()))
        self.assertEqual(got, [])

    def test_hoist_refuses_an_address_of(self):
        # was: `sink(&s->field);` -> `sink(&value);` - the address of a local for a field's.
        text = txt(
            "typedef struct S_1 {",
            "    s32 field;",
            "} S_1;",
            "void func_1(S_1 *arg0) {",
            "    s32 value;",
            "",
            "    value = arg0->field;",
            "    sink(&arg0->field);",
            "}")
        self.assertEqual(labels(t65.hoist_moves(ctx_of(text, "value", 18, 7),
                                                t65.collections.Counter())), [])

    def test_hoist_refuses_a_destination_of_another_type(self):
        text = txt(
            "void func_1(s32 arg0, s32 arg1) {",
            "    s32 value;",
            "    u8 other;",
            "",
            "    value = arg0 + arg1;",
            "    other = arg0 + arg1;",
            "    sink(value);",
            "}")
        sk = t65.collections.Counter()
        self.assertEqual(labels(t65.hoist_moves(ctx_of(text, "value", 18, 5), sk)), [])
        self.assertTrue(sk["hoist-destination-type-differs"])

    def test_hoist_through_a_typed_struct_member_is_allowed(self):
        text = txt(
            "typedef struct S_1 {",
            "    s32 unk_14;",
            "} S_1;",
            "void func_1(S_1 *arg0, s32 arg1) {",
            "    s32 value;",
            "",
            "    value = arg1 * 4;",
            "    arg0->unk_14 = arg1 * 4;",
            "    sink(value);",
            "}")
        out = by_label(t65.hoist_moves(ctx_of(text, "value", 18, 7),
                                       t65.collections.Counter()), "t65:hoist")
        self.assertIn("arg0->unk_14 = value;", list(out.values())[0])

    def test_hoist_refuses_a_floating_source_across_two_word_types(self):
        # s32 and u32 both hold 32 bits, but `(u32)e` and `(u32)(s32)e` differ for a float `e`.
        text = txt(
            "void func_1(f32 arg0) {",
            "    s32 value;",
            "    u32 other;",
            "",
            "    value = arg0 * 2.0f;",
            "    other = arg0 * 2.0f;",
            "    sink(value);",
            "}")
        sk = t65.collections.Counter()
        self.assertEqual(labels(t65.hoist_moves(ctx_of(text, "value", 18, 5), sk)), [])
        self.assertTrue(sk["hoist-source-may-be-floating-or-64-bit"])

    def test_hoist_through_a_return_of_the_same_type_is_allowed(self):
        text = txt(
            "s32 func_1(s32 arg0, s32 arg1) {",
            "    s32 value;",
            "",
            "    value = arg0 + arg1;",
            "    sink(value);",
            "    return arg0 + arg1;",
            "}")
        out = by_label(t65.hoist_moves(ctx_of(text, "value", 18, 4),
                                       t65.collections.Counter()), "t65:hoist")
        self.assertIn("return value;", list(out.values())[0])

    def test_hoist_refuses_a_return_of_another_type(self):
        text = txt(
            "u8 func_1(s32 arg0, s32 arg1) {",
            "    s32 value;",
            "",
            "    value = arg0 + arg1;",
            "    sink(value);",
            "    return arg0 + arg1;",
            "}")
        sk = t65.collections.Counter()
        self.assertEqual(labels(t65.hoist_moves(ctx_of(text, "value", 18, 4), sk)), [])
        self.assertTrue(sk["hoist-return-type-differs"])

    def test_merge_does_not_rename_a_struct_member_of_the_same_name(self):
        # was: `s->value = 1;` -> `s->arg0 = 1;` - a different member, a different offset.
        text = txt(
            "typedef struct S_1 {",
            "    s32 value;",
            "    s32 arg0;",
            "} S_1;",
            "void func_1(s32 arg0, S_1 *arg1) {",
            "    s32 value;",
            "",
            "    value = arg0;",
            "    arg1->value = 1;",
            "    sink(value);",
            "}")
        out = dict(t65.param_merge_moves(ctx_of(text, "value", 4, 8),
                                         t65.collections.Counter()))
        for got in out.values():
            self.assertIn("arg1->value = 1;", got)

    def test_merge_does_not_rewrite_a_comment(self):
        text = txt(
            "void func_1(s32 arg0, s32 arg1) {",
            "    s32 value;",
            "",
            "    value = arg0;",
            "    /* arg0 is the page index */",
            "    sink(arg1);",
            "    sink(value);",
            "}")
        out = dict(t65.param_merge_moves(ctx_of(text, "value", 4, 4),
                                         t65.collections.Counter()))
        self.assertTrue(out)
        for got in out.values():
            self.assertIn("/* arg0 is the page index */", got)

    def test_unshare_does_not_rewrite_a_member_of_the_same_name(self):
        # was: `sink(s->value);` -> `sink(s->((s32)(arg0 + arg1)));`
        text = txt(
            "typedef struct S_1 {",
            "    s32 value;",
            "} S_1;",
            "void func_1(S_1 *arg0, s32 arg1, s32 arg2) {",
            "    s32 value;",
            "",
            "    value = arg1 + arg2;",
            "    sink(value);",
            "    sink(arg0->value);",
            "    sink(value);",
            "}")
        out = dict(t65.unshare_moves(ctx_of(text, "value", 18, 7), t65.collections.Counter()))
        self.assertTrue(out)
        for got in out.values():
            self.assertIn("sink(arg0->value);", got)


# --------------------------------------------------------------------------- probe gating

PROBE_ROW = txt(
    "s32 func_1(s32 arg0) {",
    "    register s32 total ASM_REG(\"$2\");",
    "    s32 other;",
    "",
    "    other = arg0 + 1;",
    "    total = other * 3;",
    "    return total + 7;",
    "}")


def report_for(text, register="2", knob="sugg", var="total", line=6, owner="local"):
    return {"id": "x/func_1", "cfg": "2.7.2-G0", "sha": sha_text(text), "pins": 1, "reg_sites": 1,
            "sites": [{"row": "x/func_1", "site": 0, "line": line, "var": var, "register": register,
                       "owner": owner, "minimal_knob": knob, "sufficient": ["force", knob],
                       "status": "ok", "competitor": {"found": False}, "competitor_names": {}}]}


class ProbeGating(unittest.TestCase):
    def setUp(self):
        self.dir = tempfile.TemporaryDirectory(prefix="t65_")
        os.environ["T65_PROBE_DIR"] = self.dir.name
        self.row = {"id": "x/func_1", "cfg": "2.7.2-G0", "c_path": "src/x/func_1.c",
                    "container": "x"}
        self.addCleanup(self.dir.cleanup)
        self.addCleanup(lambda: os.environ.pop("T65_PROBE_DIR", None))

    def write(self, rep):
        Path(self.dir.name, "x_func_1.json").write_text(json.dumps(rep))

    def test_missing_report_is_ineligible(self):
        self.assertEqual(T_eligible(PROBE_ROW, self.row), "no probe report")

    def test_stale_sha_is_ineligible(self):
        self.write(report_for(PROBE_ROW + "/* moved on */\n"))
        self.assertEqual(T_eligible(PROBE_ROW, self.row), "probe report stale")

    def test_fresh_report_with_a_targeted_knob_is_eligible(self):
        self.write(report_for(PROBE_ROW))
        self.assertIsNone(T_eligible(PROBE_ROW, self.row))

    def test_untargeted_knob_is_ineligible(self):
        self.write(report_for(PROBE_ROW, knob="pref"))
        self.assertEqual(T_eligible(PROBE_ROW, self.row),
                         "no sugg or order-swap site with a C lever")

    def test_unnameable_sugg_register_is_skipped_with_its_reason(self):
        rep = report_for(PROBE_ROW, register="3")
        rep["sites"][0]["sufficient"] = ["force", "sugg"]
        skips = t65.collections.Counter()
        self.assertEqual(t65.plan_sites(rep, skips), [])
        self.assertEqual(skips["sugg-register-never-named-pre-reload"], 1)

    def test_unnameable_sugg_register_with_a_fallback_routes_to_order(self):
        rep = report_for(PROBE_ROW, register="3")
        rep["sites"][0]["sufficient"] = ["force", "sugg", "order-swap"]
        plans = t65.plan_sites(rep, t65.collections.Counter())
        self.assertEqual([(p[1], p[2]) for p in plans], [("order", "fallback:order-swap")])


def T_eligible(text, row):
    return t65.T.eligible(text, row, {})


# --------------------------------------------------------------------------- end to end

class ApplyVerified(unittest.TestCase):
    def setUp(self):
        self.dir = tempfile.TemporaryDirectory(prefix="t65e_")
        os.environ["T65_PROBE_DIR"] = self.dir.name
        Path(self.dir.name, "x_func_1.json").write_text(json.dumps(report_for(PROBE_ROW)))
        self.row = {"id": "x/func_1", "cfg": "2.7.2-G0", "c_path": "src/x/func_1.c",
                    "container": "x"}
        self.addCleanup(self.dir.cleanup)
        self.addCleanup(lambda: os.environ.pop("T65_PROBE_DIR", None))
        self.saved, t65.SCREEN = t65.SCREEN, self.screen
        self.addCleanup(lambda: setattr(t65, "SCREEN", self.saved))
        self.seen = []

    def screen(self, row, text):
        """Every text compiles to the same listing: the screen never rejects."""
        self.seen.append(text)
        return ["one", "two"]

    def test_accepts_the_first_exact_candidate_and_journals_it(self):
        want = {}

        def vf(cand):
            ok = "total = total + 7;" in cand
            if ok:
                want["cand"] = cand
            return {"exact": ok}

        out, log = t65.T.apply_verified(PROBE_ROW, self.row, {}, vf)
        self.assertIsNotNone(out)
        self.assertEqual(out, want["cand"])
        self.assertEqual(log["pins_in"], 1)
        self.assertEqual(log["pins_out"], 0)
        self.assertEqual(log["exact"][0]["register"], "2")
        self.assertTrue(log["steps"][0].startswith("t65:ret-op"))
        self.assertEqual(log["sites"][0]["d0"], 0)

    def test_no_exact_returns_none_with_the_journal(self):
        out, log = t65.T.apply_verified(PROBE_ROW, self.row, {}, lambda c: {"exact": False})
        self.assertIsNone(out)
        self.assertEqual(log["pins_out"], 1)
        self.assertGreater(log["candidates_n"], 0)
        self.assertTrue(log["moves"])
        self.assertIn("screened", log)

    def test_verify_budget_is_respected(self):
        os.environ["T65_VERIFY"] = "1"
        self.addCleanup(lambda: os.environ.pop("T65_VERIFY", None))
        calls = []

        def vf(cand):
            calls.append(cand)
            return {"exact": False}

        out, log = t65.T.apply_verified(PROBE_ROW, self.row, {}, vf)
        self.assertIsNone(out)
        self.assertEqual(len(calls), 1)
        self.assertEqual(log["tried"], 1)

    def test_a_candidate_never_carries_scaffolding(self):
        out, log = t65.T.apply_verified(PROBE_ROW, self.row, {}, lambda c: {"exact": False})
        for cand in self.seen:
            for bad in ("__asm__", "volatile", "while (0)", "do {", "for (;0;)"):
                self.assertNotIn(bad, cand)
            self.assertLessEqual(len(sites_of(cand)), 1)


if __name__ == "__main__":
    unittest.main(verbosity=2)
