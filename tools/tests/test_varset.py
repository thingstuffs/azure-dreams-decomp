"""varset: every move on synthetic texts, and every refusal the moves are supposed to make.

The refusals are the point of the file.  A varset move rewrites declarations, so a missed refusal is
not a wasted compile but a candidate that verifies byte-exact for the wrong reason (a dropped
qualifier the screen cannot see) or that does not mean what the original meant (a use reached by a
second definition through a label, a back edge that still carries the value).
"""
import collections
import re
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from xform import varset as V

HEAD = '#include "common.h"\n\n'


def wrap(body, sig="void func_test(s32 arg, u8 *ptr)"):
    return HEAD + sig + "\n{\n" + body + "}\n"


def labels(items):
    return [l for l, _ in items]


def run(move, text, focus=None):
    sk = collections.Counter()
    return move(text, focus, sk), sk


class Inline(unittest.TestCase):
    def test_single_definition_inlined_at_its_use(self):
        t = wrap("    s32 a;\n    s32 b;\n    a = arg + 1;\n    b = a;\n")
        got, sk = run(V.inline_def_candidates, t)
        self.assertIn("inline_def:a@7", labels(got))
        cand = dict(got)["inline_def:a@7"]
        self.assertIn("b = ((s32)(arg + 1));", cand)
        self.assertNotIn("a = arg + 1;", cand)
        self.assertNotIn("    s32 a;", cand)          # no definition left: the declaration goes too

    def test_use_several_statements_later_across_a_label(self):
        t = wrap("    s32 a;\n    s32 b;\n    a = arg + 1;\n    goto L;\nL:\n    b = a;\n")
        got, _ = run(V.inline_def_candidates, t)
        self.assertIn("inline_def:a@7", labels(got))

    def test_identical_multi_definition_web_inlines_together(self):
        t = wrap("    s32 a;\n    s32 b;\n    if (arg) {\n        a = 7;\n        goto L;\n    }\n"
                 "    a = 7;\nL:\n    b = a;\n")
        got, _ = run(V.inline_def_candidates, t)
        self.assertTrue(any(l.startswith("inline_def:a@") for l in labels(got)))
        cand = [c for l, c in got if l.startswith("inline_def:a@")][0]
        self.assertIn("b = ((s32)(7));", cand)

    def test_pointer_cast_is_subsumed_not_doubled(self):
        t = wrap("    M2C_UNK *p;\n    p = (M2C_UNK *)(arg + 8);\n"
                 "    func_800A0000(((S_1 *)p)->unk_00);\n")
        got, _ = run(V.inline_def_candidates, t)
        cand = [c for l, c in got if l.startswith("inline_def:p@")][0]
        self.assertIn("((S_1 *)(arg + 8))->unk_00", cand)

    def test_all_variant_removes_every_definition(self):
        t = wrap("    s32 a;\n    s32 b;\n    s32 c;\n    a = arg + 1;\n    b = a;\n"
                 "    a = arg + 2;\n    c = a;\n")
        got, _ = run(V.inline_def_candidates, t)
        self.assertIn("inline_def:all:a", labels(got))
        cand = dict(got)["inline_def:all:a"]
        self.assertNotIn("    s32 a;", cand)
        self.assertIn("b = ((s32)(arg + 1));", cand)
        self.assertIn("c = ((s32)(arg + 2));", cand)

    def test_initialised_declaration_is_a_definition(self):
        t = wrap("    s32 b;\n    if (arg) {\n        s32 k = arg + 1;\n        b = k;\n    }\n")
        got, _ = run(V.inline_def_candidates, t)
        cand = [c for l, c in got if l.startswith("inline_def:") and ":k" in l][0]
        self.assertIn("b = ((s32)(arg + 1));", cand)
        self.assertNotIn("s32 k =", cand)

    def test_initialised_declaration_is_not_partially_inlined(self):
        t = wrap("    s32 b;\n    s32 c;\n    if (arg) {\n        s32 k = arg + 1;\n"
                 "        b = k;\n        k = arg + 2;\n        c = k;\n    }\n")
        got, sk = run(V.inline_def_candidates, t)
        for label, cand in got:
            if ":k" in label and not label.startswith("inline_def:all"):
                self.assertIn("s32 k", cand, label)

    def test_initialised_declaration_never_merged_or_retyped(self):
        t = wrap("    s32 b;\n    s32 r;\n    s32 k = arg;\n    b = k;\n    r = 1;\n")
        got, sk = run(V.merge_local_candidates, t)
        self.assertEqual([l for l in labels(got) if "k" in l], [])
        self.assertTrue(sk["initialised-decl"])

    def test_call_in_the_expression_refused(self):
        t = wrap("    s32 a;\n    s32 b;\n    a = func_800A0000(arg);\n    b = a;\n")
        got, sk = run(V.inline_def_candidates, t)
        self.assertEqual([l for l in labels(got) if l.startswith("inline_def:a")], [])
        self.assertTrue(sk["inline:unsafe-rhs"])

    def test_operand_reassigned_between_definition_and_use_refused(self):
        t = wrap("    s32 a;\n    s32 b;\n    s32 t;\n    t = 1;\n    a = t + 1;\n"
                 "    t = 2;\n    b = a;\n")
        got, sk = run(V.inline_def_candidates, t)
        self.assertEqual([l for l in labels(got) if l.startswith("inline_def:a")], [])
        self.assertTrue(sk["inline:operand-clobbered"])

    def test_use_inside_a_pin_macro_refused(self):
        t = wrap("    s32 a;\n    s32 b;\n    a = arg + 1;\n    ASM_KEEP(a);\n    b = a;\n")
        got, sk = run(V.inline_def_candidates, t)
        self.assertEqual([l for l in labels(got) if l.startswith("inline_def:a")], [])
        self.assertTrue(sk["inline:use-in-pin"])

    def test_call_between_a_memory_read_and_its_use_refused(self):
        t = wrap("    s32 a;\n    s32 b;\n    a = ((S_1 *)ptr)->unk_00;\n"
                 "    func_800A0000(arg);\n    b = a;\n")
        got, sk = run(V.inline_def_candidates, t)
        self.assertEqual([l for l in labels(got) if l.startswith("inline_def:a")], [])
        self.assertTrue(sk["inline:call-between"])


class Split(unittest.TestCase):
    def test_two_webs_split(self):
        t = wrap("    s32 a;\n    s32 b;\n    s32 c;\n    a = arg + 1;\n    b = a;\n"
                 "    a = arg + 2;\n    c = a;\n")
        got, _ = run(V.split_def_candidates, t)
        self.assertTrue(any(l.startswith("split_def:a>a_2@") for l in labels(got)))
        cand = [c for l, c in got if l.startswith("split_def:a>a_2@")][0]
        self.assertIn("    s32 a_2;", cand)
        self.assertIn("a_2 = arg + 2;", cand)
        self.assertIn("c = a_2;", cand)
        self.assertIn("a = arg + 1;", cand)

    def test_split_at_labels_and_across_arms(self):
        t = wrap("    s32 a;\n    s32 b;\n    s32 c;\n"
                 "    if (arg) {\n        a = 1;\n        b = a;\n        goto L;\n    }\n"
                 "    a = 2;\n    c = a;\nL:\n    c = c + 1;\n")
        got, _ = run(V.split_def_candidates, t)
        self.assertTrue(any(l.startswith("split_def:a>") for l in labels(got)))

    def test_all_variant_gives_every_web_its_own_name(self):
        t = wrap("    s32 a;\n    s32 b;\n    s32 c;\n    s32 d;\n    a = 1;\n    b = a;\n"
                 "    a = 2;\n    c = a;\n    a = 3;\n    d = a;\n")
        got, _ = run(V.split_def_candidates, t)
        self.assertIn("split_def:all:a", labels(got))
        cand = dict(got)["split_def:all:a"]
        self.assertIn("    s32 a_2;", cand)
        self.assertIn("    s32 a_3;", cand)

    def test_use_reached_from_another_definition_through_a_label_refused(self):
        # both `a = 1` and `a = 2` reach `b = a`: one web, so there is nothing to split
        t = wrap("    s32 a;\n    s32 b;\n    if (arg) {\n        a = 1;\n        goto L;\n    }\n"
                 "    a = 2;\nL:\n    b = a;\n")
        got, sk = run(V.split_def_candidates, t)
        self.assertEqual([l for l in labels(got) if l.startswith("split_def:a")], [])
        self.assertTrue(sk["split:single-web"])

    def test_loop_back_edge_carrying_the_variable_refused(self):
        t = wrap("    s32 a;\n    s32 b;\n    a = 0;\n    while (arg) {\n        b = a;\n"
                 "        a = b + 1;\n    }\n    b = a;\n")
        got, sk = run(V.split_def_candidates, t)
        self.assertEqual([l for l in labels(got) if l.startswith("split_def:a")], [])
        self.assertTrue(sk["split:back-edge"] or sk["split:single-web"])

    def test_address_taken_local_refused(self):
        t = wrap("    s32 a;\n    s32 b;\n    a = 1;\n    b = a;\n    a = 2;\n"
                 "    func_800A0000(&a);\n")
        for move in (V.split_def_candidates, V.inline_def_candidates, V.merge_local_candidates,
                     V.retype_ptr_candidates):
            got, sk = run(move, t)
            self.assertEqual([l for l in labels(got) if ":a" in l or "a>" in l or ">a" in l], [],
                             move.__name__)
            self.assertTrue(sk["address-taken"], move.__name__)

    def test_struct_member_with_the_locals_name_is_not_renamed(self):
        t = wrap("    s32 a;\n    s32 b;\n    a = 1;\n    b = a;\n"
                 "    ((S_1 *)ptr)->a = 5;\n    a = 2;\n    b = a;\n")
        got, _ = run(V.split_def_candidates, t)
        for label, cand in got:
            self.assertIn("->a = 5;", cand)

    def test_same_named_inner_scope_local_refused(self):
        t = wrap("    s32 a;\n    s32 b;\n    a = 1;\n    b = a;\n    if (arg) {\n"
                 "        s32 a;\n        a = 2;\n        b = a;\n    }\n")
        got, sk = run(V.split_def_candidates, t)
        self.assertEqual([l for l in labels(got) if l.startswith("split_def:a")], [])
        self.assertTrue(sk["shadowed"])

    def test_local_referenced_inside_an_ifdef_arm_refused(self):
        # kept below MAX_UNKNOWN so the refusal is the variable's, not the whole body's
        t = (HEAD + "void func_test(s32 arg)\n{\n    s32 a;\n    s32 b;\n    s32 c;\n"
             "    a = 1;\n    b = a;\n    c = b;\n    c = c + 1;\n    c = c + 2;\n"
             "    c = c + 3;\n    c = c + 4;\n    c = c + 5;\n"
             "#ifndef NON_MATCHING\n    a = 2;\n#endif\n    b = a;\n    c = b;\n}\n")
        got, sk = run(V.split_def_candidates, t)
        self.assertTrue(V.functions(t), "the body must not be refused wholesale")
        self.assertEqual([l for l in labels(got) if l.startswith("split_def:a")], [])
        self.assertTrue(sk["in-pp-arm"] or sk["use-on-unknown-node"])

    def test_register_asm_reg_declaration_is_never_touched(self):
        t = wrap('    register s32 a ASM_REG("$2");\n    s32 b;\n    a = 1;\n    b = a;\n'
                 "    a = 2;\n    b = a;\n")
        for move in (V.split_def_candidates, V.inline_def_candidates, V.merge_local_candidates,
                     V.retype_ptr_candidates, V.merge_param_candidates):
            got, sk = run(move, t)
            self.assertEqual([l for l in labels(got) if re.search(r"\ba\b", l)], [], move.__name__)
            self.assertTrue(sk["asm-reg-decl"], move.__name__)

    def test_qualifiers_are_preserved(self):
        t = wrap("    volatile s32 a;\n    const s32 c;\n    s32 b;\n    a = 1;\n    b = a;\n"
                 "    a = 2;\n    b = a;\n")
        got, sk = run(V.split_def_candidates, t)
        self.assertEqual([l for l in labels(got) if l.startswith(("split_def:a", "split_def:c"))], [])
        self.assertEqual(sk["qualified-decl"], 2)
        for move in V.MOVES:
            for _, cand in move(t, None, collections.Counter()):
                self.assertEqual(cand.count("volatile"), t.count("volatile"))
                self.assertEqual(cand.count("const"), t.count("const"))


class Merge(unittest.TestCase):
    def test_disjoint_live_ranges_across_control_flow(self):
        t = wrap("    s32 a;\n    s32 b;\n    s32 r;\n    if (arg) {\n        a = 1;\n"
                 "        r = a;\n    } else {\n        b = 2;\n        r = b;\n    }\n")
        got, _ = run(V.merge_local_candidates, t)
        self.assertIn("merge_local:b>a", labels(got))
        self.assertIn("merge_local:a>b", labels(got))
        cand = dict(got)["merge_local:b>a"]
        self.assertNotIn("    s32 b;", cand)
        self.assertIn("a = 2;", cand)

    def test_overlapping_live_ranges_refused(self):
        t = wrap("    s32 a;\n    s32 b;\n    s32 r;\n    a = 1;\n    b = 2;\n    r = a + b;\n")
        got, sk = run(V.merge_local_candidates, t)
        self.assertNotIn("merge_local:a>b", labels(got))
        self.assertNotIn("merge_local:b>a", labels(got))
        self.assertTrue(sk["merge:live-ranges-overlap"])

    def test_different_types_never_merged(self):
        t = wrap("    s32 a;\n    u8 b;\n    s32 r;\n    a = 1;\n    r = a;\n    b = 2;\n    r = b;\n")
        got, _ = run(V.merge_local_candidates, t)
        self.assertNotIn("merge_local:a>b", labels(got))
        self.assertNotIn("merge_local:b>a", labels(got))

    def test_dead_parameter_absorbs_the_local(self):
        t = wrap("    s32 a;\n    s32 r;\n    r = 0;\n    a = 3;\n    r = a;\n")
        got, _ = run(V.merge_param_candidates, t)
        self.assertIn("merge_param:a>arg", labels(got))
        cand = dict(got)["merge_param:a>arg"]
        self.assertNotIn("    s32 a;", cand)
        self.assertIn("arg = 3;", cand)

    def test_usecopy_sends_later_parameter_uses_through_the_copy(self):
        t = wrap("    s32 a;\n    s32 r;\n    a = arg;\n    r = arg + 1;\n    r = r + arg;\n")
        got, _ = run(V.merge_param_candidates, t)
        self.assertIn("merge_param:usecopy:arg>a", labels(got))
        cand = dict(got)["merge_param:usecopy:arg>a"]
        self.assertIn("a = arg;", cand)
        self.assertIn("r = a + 1;", cand)
        self.assertIn("r = r + a;", cand)

    def test_reassigned_parameter_refused(self):
        t = wrap("    s32 a;\n    s32 r;\n    a = arg;\n    arg = 2;\n    r = arg;\n")
        got, sk = run(V.merge_param_candidates, t)
        self.assertEqual([l for l in labels(got) if "usecopy" in l], [])
        self.assertTrue(sk["usecopy:parameter-reassigned"] or sk["param:parameter-reassigned"])


class Interference(unittest.TestCase):
    """The def-vs-live-out edge: a live range can be dead on the path INTO a definition and still
    be needed after it.  A lin/lout overlap test alone merged two interfering locals."""

    #   a = 1; if (arg) goto mid; b = 2; r = b; mid: r = a; f(r);
    # `r` is defined at `r = b` where `a` is live OUT (the `mid:` use).  Neither is live-in there,
    # so the live-in/live-out test alone accepted `a > r` and the arg == 0 path then read 2 for 1.
    JUMP_IN = ("    s32 a;\n    s32 b;\n    s32 r;\n    a = 1;\n    if (arg) {\n"
               "        goto mid;\n    }\n    b = 2;\n    r = b;\nmid:\n    r = a;\n"
               "    func_800A0000(r);\n")

    def test_definition_over_a_live_out_range_refused(self):
        got, sk = run(V.merge_local_candidates, wrap(self.JUMP_IN))
        self.assertNotIn("merge_local:a>r", labels(got))
        self.assertNotIn("merge_local:r>a", labels(got))
        self.assertTrue(sk["merge:live-ranges-overlap"])

    def test_the_genuinely_disjoint_pair_of_the_same_body_still_merges(self):
        # `b` dies at `r = b`, so b/r do NOT interfere - the fix must not refuse everything.
        got, _ = run(V.merge_local_candidates, wrap(self.JUMP_IN))
        self.assertIn("merge_local:b>r", labels(got))

    def test_parameter_written_where_the_local_is_live_refused(self):
        t = wrap("    s32 a;\n    s32 r;\n    a = 1;\n    if (a) {\n        goto mid;\n    }\n"
                 "    arg = 2;\n    r = arg;\nmid:\n    r = a;\n    func_800A0000(r);\n")
        got, sk = run(V.merge_param_candidates, t)
        self.assertEqual([l for l in labels(got) if l.startswith("merge_param:a>")], [])

    def test_local_live_at_entry_never_absorbs_the_parameter(self):
        # the parameter's implicit entry definition is an interference edge of its own
        t = wrap("    s32 a;\n    s32 r;\n    r = arg + a;\n    a = 3;\n    r = a;\n")
        got, _ = run(V.merge_param_candidates, t)
        self.assertEqual([l for l in labels(got) if l.startswith("merge_param:a>")], [])

    def test_no_candidate_is_a_degenerate_self_copy(self):
        for t in (wrap(self.JUMP_IN),
                  wrap("    s32 a;\n    s32 r;\n    s32 i;\n    i = 0;\nloop:\n    r = arg;\n"
                       "    a = arg;\n    i = i + 1;\n    if (i < 3) {\n        goto loop;\n    }\n"
                       "    func_800A0000(r);\n")):
            for move in V.MOVES:
                for label, cand in move(t, None, collections.Counter()):
                    self.assertFalse(re.search(r"^\s*(\w+) = \1;\s*$", cand, re.M),
                                     "%s produced a self-copy" % label)


class UsecopyBackEdge(unittest.TestCase):
    """`usecopy` renames parameter uses that run AFTER the copy; a loop makes "after" a lie."""

    LOOP = ("    s32 a;\n    s32 r;\n    s32 i;\n    i = 0;\nloop:\n    r = arg;\n    a = arg;\n"
            "    i = i + 1;\n    if (i < 3) {\n        goto loop;\n    }\n    func_800A0000(r);\n")

    def test_parameter_use_above_the_copy_on_a_back_edge_refused(self):
        got, sk = run(V.merge_param_candidates, wrap(self.LOOP))
        # `r = arg` sits above `a = arg` in the loop body: on iteration 1 it runs first
        self.assertNotIn("merge_param:usecopy:arg>a", labels(got))
        self.assertTrue(sk["usecopy:parameter-used-before-copy"])

    def test_the_copy_that_does_dominate_its_uses_is_still_offered(self):
        # `r = arg` IS the copy here, and `a = arg` below it is dominated by it
        got, _ = run(V.merge_param_candidates, wrap(self.LOOP))
        self.assertIn("merge_param:usecopy:arg>r", labels(got))
        cand = dict(got)["merge_param:usecopy:arg>r"]
        self.assertIn("a = r;", cand)
        self.assertIn("r = arg;", cand)


class Labels(unittest.TestCase):
    """A label, a goto target and a spaced struct member are tokens that merely LOOK like the
    local.  Renaming or substituting into one produced text that is not C (`goto ((s32)(1));`)."""

    SHADOW = ("    s32 done;\n    s32 b;\n    if (arg) {\n        done = 1;\n        goto done;\n"
              "    }\n    done = 1;\ndone:\n    b = done;\n")

    def test_inline_never_substitutes_into_a_label_or_its_goto(self):
        got, _ = run(V.inline_def_candidates, wrap(self.SHADOW))
        for label, cand in got:
            self.assertIn("    goto done;", cand, label)
            self.assertIn("\ndone:\n", cand, label)
            self.assertNotIn("goto ((", cand, label)

    def test_split_never_renames_a_label_or_its_goto(self):
        got, _ = run(V.split_def_candidates, wrap(self.SHADOW))
        for label, cand in got:
            self.assertIn("    goto done;", cand, label)
            self.assertIn("\ndone:\n", cand, label)

    def test_spaced_struct_member_is_not_the_local(self):
        t = wrap("    s32 count;\n    s32 b;\n    count = 1;\n    b = count;\n    count = 2;\n"
                 "    ((S_1 *)ptr)-> count = 5;\n    b = count;\n")
        got, _ = run(V.split_def_candidates, t)
        self.assertTrue(any(l.startswith("split_def:count>") for l in labels(got)))
        for label, cand in got:
            self.assertIn("((S_1 *)ptr)-> count = 5;", cand, label)

    def test_a_label_is_not_a_use_that_welds_two_webs_together(self):
        t = wrap("    s32 done;\n    s32 b;\n    done = 1;\n    b = done;\n    if (arg) {\n"
                 "        goto done;\n    }\n    done = 2;\n    b = done;\ndone:\n"
                 "    func_800A0000(b);\n")
        got, _ = run(V.split_def_candidates, t)
        self.assertTrue(any(l.startswith("split_def:done>") for l in labels(got)))


class Retype(unittest.TestCase):
    def test_single_struct_type_retyped_and_casts_dropped(self):
        t = wrap("    M2C_UNK *p;\n    p = (M2C_UNK *)ptr;\n"
                 "    ((S_1 *)p)->unk_00 = 1;\n    ((S_1 *)p)->unk_04 = 2;\n")
        got, _ = run(V.retype_ptr_candidates, t)
        self.assertIn("retype_ptr:p>S_1", labels(got))
        cand = dict(got)["retype_ptr:p>S_1"]
        self.assertIn("    S_1 *p;", cand)
        self.assertIn("p->unk_00 = 1;", cand)
        self.assertIn("p->unk_04 = 2;", cand)

    def test_two_struct_types_refused(self):
        t = wrap("    M2C_UNK *p;\n    p = (M2C_UNK *)ptr;\n"
                 "    ((S_1 *)p)->unk_00 = 1;\n    ((S_2 *)p)->unk_04 = 2;\n")
        got, sk = run(V.retype_ptr_candidates, t)
        self.assertEqual(labels(got), [])
        self.assertTrue(sk["retype:not-one-struct-type"])

    def test_pointer_arithmetic_refused(self):
        t = wrap("    M2C_UNK *p;\n    p = (M2C_UNK *)ptr;\n"
                 "    ((S_1 *)p)->unk_00 = 1;\n    p = p + arg;\n")
        got, sk = run(V.retype_ptr_candidates, t)
        self.assertEqual(labels(got), [])
        self.assertTrue(sk["retype:arithmetic-or-index"])

    def test_already_typed_pointer_refused(self):
        t = wrap("    S_1 *p;\n    p = (S_1 *)ptr;\n    p->unk_00 = 1;\n")
        got, sk = run(V.retype_ptr_candidates, t)
        self.assertEqual(labels(got), [])
        self.assertTrue(sk["retype:not-an-untyped-pointer"])


class Determinism(unittest.TestCase):
    TEXT = wrap("    s32 a;\n    s32 b;\n    s32 c;\n    a = arg + 1;\n    b = a;\n"
                "    a = arg + 2;\n    c = a;\n    b = c;\n")

    def test_stable_and_bounded(self):
        for move in V.MOVES:
            first = move(self.TEXT, None, collections.Counter())
            second = move(self.TEXT, None, collections.Counter())
            self.assertEqual(first, second, move.__name__)
            self.assertLessEqual(len(first), V.CAP, move.__name__)

    def test_focus_comes_first(self):
        got = V.split_def_candidates(self.TEXT, "a", collections.Counter())
        self.assertTrue(got and ":a" in got[0][0])

    def test_no_candidate_equals_its_input_and_none_adds_scaffolding(self):
        for label, cand in V.candidates(self.TEXT):
            self.assertNotEqual(cand, self.TEXT, label)
            for pat in (r"ASM_", r"__asm__", r"volatile", r"do\s*\{", r"while\s*\(\s*0\s*\)"):
                self.assertEqual(len(re.findall(pat, cand)), len(re.findall(pat, self.TEXT)), label)


class Cfg(unittest.TestCase):
    def test_unknown_construct_makes_everything_later_reachable(self):
        t = wrap("    s32 a;\n    s32 b;\n    a = 1;\n    SOME_MACRO(arg)\n    b = a;\n    a = 2;\n"
                 "    b = a;\n")
        fn = V.functions(t)[0]
        unknown = [n for n in fn.nodes if n.kind == "unknown"]
        self.assertTrue(unknown)
        self.assertTrue(set(range(unknown[0].i + 1, len(fn.nodes))) <= set(unknown[0].succ))

    def test_declaration_node_is_not_a_use(self):
        t = wrap("    s32 a;\n    s32 b;\n    a = 1;\n    b = a;\n")
        fn = V.functions(t)[0]
        decl_node = fn.decls["a"][0]["node"]
        self.assertNotIn(decl_node, fn.kinds("a"))


if __name__ == "__main__":
    unittest.main()
