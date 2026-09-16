"""T69: the joint parameter-copy merge fires on both entry-copy forms, refuses everything that would
change the program, and always returns a text with fewer pins and the same unscored arms.

Every test is textual (no compiler): the generator's contract is that it deletes a declaration and a
copy statement, renames a parameter (and, for a pointer, retypes it), and erases the single-variable
keeps of the locals it removed - `vf` decides the rest.
"""
import collections
import os
import re
import sys
import unittest
from unittest import mock
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from pin_census import sites_of, unscored_text
from xform import t69_prologue as G

HEAD = '#include "common.h"\n\n'
PIN = "   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */"


def fn(params, body):
    return HEAD + "void f(%s)\n{\n%s}\n" % (params, body)


def gen(text):
    skips = collections.Counter()
    return G.prologue_candidates(text, skips), skips


def labels(text):
    return [l for l, _ in gen(text)[0]]


TWO = fn("void *a_in, void *b_in",
         "    void *a;\n    void *b;\n    a = a_in;\n    b = b_in;\n"
         "    ASM_KEEP(a);%s\n    ASM_KEEP(b);%s\n    g(a, b);\n" % (PIN, PIN))

DECLINIT = fn("void *a_in, void *b_in",
              "    void *a = a_in;\n    void *b = b_in;\n"
              "    ASM_KEEP(a);%s\n    ASM_KEEP(b);%s\n    g(a, b);\n" % (PIN, PIN))


class Moves(unittest.TestCase):
    def test_split_declaration_and_copy(self):
        cands, skips = gen(TWO)
        self.assertEqual(labels(TWO)[0], "prologue:f:a+b")
        best = cands[0][1]
        self.assertIn("void f(void *a, void *b)", best)
        self.assertNotIn("a_in", best)
        self.assertNotIn("b_in", best)
        self.assertNotIn("void *a;", best)
        self.assertNotIn("a = a_in;", best)
        self.assertEqual(len(sites_of(best)), 0)
        self.assertEqual(len(sites_of(TWO)), 2)

    def test_declaration_with_initialiser(self):
        cands, _ = gen(DECLINIT)
        best = cands[0][1]
        self.assertIn("void f(void *a, void *b)", best)
        self.assertNotIn("void *a = a_in;", best)
        self.assertEqual(len(sites_of(best)), 0)

    def test_every_subset_is_offered_whole_set_first(self):
        ls = labels(TWO)
        self.assertEqual(ls[0], "prologue:f:a+b")
        self.assertEqual(sorted(ls), sorted(["prologue:f:a+b", "prologue:f:a", "prologue:f:b"]))

    def test_pointer_retype_takes_the_local_type(self):
        t = fn("void *a_in", "    S *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n" % PIN)
        best = gen(t)[0][0][1]
        self.assertIn("void f(S *a)", best)

    def test_remaining_uses_of_the_parameter_are_renamed(self):
        t = fn("void *a_in, void *b_in",
               "    void *a = a_in;\n    void *b = b_in;\n    ASM_KEEP(a);%s\n    ASM_KEEP(b);%s\n"
               "    g(a_in, b_in);\n" % (PIN, PIN))
        best = gen(t)[0][0][1]
        self.assertIn("g(a, b);", best)
        self.assertNotIn("_in", best)

    def test_same_file_prototype_is_retyped_with_the_definition(self):
        t = (HEAD + "extern void f(void *);\n" +
             "void f(void *a_in)\n{\n    S *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n}\n" % PIN)
        best = gen(t)[0][0][1]
        self.assertIn("extern void f(S *);", best)
        self.assertIn("void f(S *a)", best)

    def test_a_nested_declaration_is_offered_and_journalled(self):
        t = fn("void *a_in",
               "    if (x) {\n        S *a = a_in;\n        ASM_KEEP(a);%s\n        g(a);\n    }\n" % PIN)
        cands, skips = gen(t)
        self.assertEqual(len(cands), 1)
        self.assertEqual(skips["nested-scope"], 1)

    def test_candidate_keeps_the_unscored_arms(self):
        for t in (TWO, DECLINIT):
            for _, c in gen(t)[0]:
                self.assertEqual(unscored_text(c), unscored_text(t))

    def test_every_candidate_removes_at_least_one_pin(self):
        for t in (TWO, DECLINIT):
            n = len(sites_of(t))
            for _, c in gen(t)[0]:
                self.assertLess(len(sites_of(c)), n)

    def test_menu_is_capped(self):
        many = ", ".join("void *p%d_in" % i for i in range(8))
        body = "".join("    void *p%d = p%d_in;\n" % (i, i) for i in range(8))
        body += "".join("    ASM_KEEP(p%d);%s\n" % (i, PIN) for i in range(8))
        t = fn(many, body + "    g(p0);\n")
        cands, skips = gen(t)
        self.assertLessEqual(len(cands), G.MAX_CANDS)
        self.assertTrue(skips["menu-capped"])


class Refusals(unittest.TestCase):
    def refuse(self, text, key):
        cands, skips = gen(text)
        self.assertEqual(cands, [], "expected no candidate, got %s" % [l for l, _ in cands])
        self.assertTrue(skips[key], "expected the %r refusal, got %s" % (key, dict(skips)))

    def test_local_written_twice(self):
        self.refuse(fn("void *a_in", "    void *a = a_in;\n    ASM_KEEP(a);%s\n    a = 0;\n    g(a);\n" % PIN),
                    "local-written-twice")

    def test_parameter_written(self):
        self.refuse(fn("void *a_in", "    void *a = a_in;\n    ASM_KEEP(a);%s\n    a_in = 0;\n    g(a);\n" % PIN),
                    "param-written")

    def test_address_taken(self):
        self.refuse(fn("void *a_in", "    void *a = a_in;\n    ASM_KEEP(a);%s\n    g(&a);\n" % PIN),
                    "addr-taken")

    def test_register_pinned_local(self):
        t = fn("void *a_in", '    register void *a ASM_REG("$18") = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n' % PIN)
        with mock.patch.dict(os.environ, {"T69_DROP_REG": "0"}):
            self.refuse(t, "reg-pinned-local")

    def test_register_pin_drops_with_the_copy_by_default(self):
        # T69_DROP_REG (round 32, default on): the copy AND its ASM_REG go; the pin's `register` does not
        # move onto the parameter (it was the pin's syntax), and the REG site alone counts as a removed pin.
        t = fn("void *a_in", '    register void *a ASM_REG("$18") = a_in;\n    g(a);\n')
        with mock.patch.dict(os.environ, {"T69_DROP_REG": "1"}):
            cands, skips = gen(t)
        self.assertEqual(len(cands), 1)
        self.assertTrue(skips["opened-drop-reg"])
        self.assertIn("void f(void *a)\n", cands[0][1])
        self.assertNotIn("ASM_REG", cands[0][1])
        self.assertEqual(sites_of(cands[0][1]), [])
        # a plain `register` local still carries its storage class (round-31 rule, unchanged)
        t2 = fn("void *a_in", "    register void *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n" % PIN)
        with mock.patch.dict(os.environ, {"T69_DROP_REG": "1"}):
            cands2, _ = gen(t2)
        self.assertIn("void f(register void *a)", cands2[0][1])

    def test_copy_in_a_nested_block_is_closed_by_default_and_opens_on_request(self):
        # the local is a block snapshot of a never-written parameter: every occurrence inside the block
        body = ("    void *a;\n    if (x) {\n        a = a_in;\n        ASM_KEEP(a);%s\n        g(a);\n    }\n" % PIN)
        self.refuse(fn("void *a_in", body), "copy-not-in-the-declaration-block")
        with mock.patch.dict(os.environ, {"T69_BLOCK_COPY": "1"}):
            cands, skips = gen(fn("void *a_in", body))
        self.assertEqual(len(cands), 1)
        self.assertTrue(skips["opened-block-copy"])
        self.assertIn("void f(void *a)\n", cands[0][1])
        self.assertNotIn("a = a_in", cands[0][1])
        self.assertNotIn("ASM_KEEP", cands[0][1])
        # an occurrence outside the copy's block keeps the refusal even with the opening
        with mock.patch.dict(os.environ, {"T69_BLOCK_COPY": "1"}):
            self.refuse(fn("void *a_in", body + "    h(a);\n"), "copy-not-in-the-declaration-block")

    def test_detail_counter_names_the_local_of_each_refusal(self):
        t = fn("void *a_in", "    void *a = a_in;\n    ASM_KEEP(a);%s\n    a = 0;\n    g(a);\n" % PIN)
        skips = G.Detail()
        for f in G.functions(t):
            G.entry_copies(t, f, skips)
        self.assertIn(("local-written-twice", "a"), skips.detail)
        self.assertEqual(skips["local-written-twice"], 1)
        self.assertIn(("no-entry-copy", None), skips.detail)

    def test_scalar_retype_is_closed_by_default(self):
        self.refuse(fn("s32 a_in", "    s16 a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n" % PIN),
                    "retype-scalar")

    def test_scalar_retype_opens_on_request(self):
        t = fn("s32 a_in", "    s16 a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n" % PIN)
        with mock.patch.dict(os.environ, {"T69_RETYPE_SCALAR": "1"}):
            cands, skips = gen(t)
        self.assertEqual(len(cands), 1)
        self.assertTrue(skips["opened-retype-scalar"])
        self.assertIn("void f(s16 a)", cands[0][1])

    def test_qualifier_never_changes(self):
        t = fn("void *a_in", "    const void *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n" % PIN)
        self.refuse(t, "qualifier-differs")

    def test_pointer_depth_never_changes(self):
        t = fn("void *a_in", "    S **a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n" % PIN)
        self.refuse(t, "pointer-depth-differs")

    def test_whole_function_inside_a_mips_arm_refused(self):
        # unscored_text/arm_labels only label NON_MATCHING: this arm has no other backstop.
        t = (HEAD + "#ifdef __mips__\n" + fn("void *a_in", "    void *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n" % PIN)[len(HEAD):]
             + "#else\nvoid f(void *a) { g(a); }\n#endif\n")
        self.refuse(t, "preprocessor-region")

    def test_whole_function_inside_an_if_zero_refused(self):
        t = HEAD + "#if 0\n" + fn("void *a_in", "    void *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n" % PIN)[len(HEAD):] + "#endif\n"
        self.refuse(t, "preprocessor-region")

    def test_prototype_inside_an_arm_is_not_edited(self):
        t = (HEAD + "#ifdef __mips__\nextern void f(void *);\n#endif\nextern void f(void *);\n" +
             "void f(void *a_in)\n{\n    S *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n}\n" % PIN)
        cands, skips = gen(t)
        self.assertEqual(cands, [])
        self.assertTrue(skips["prototype-not-retypable"])

    def test_a_recursive_call_is_not_mistaken_for_a_prototype(self):
        t = (HEAD + "void f(void *a_in)\n{\n    S *a = a_in;\n    ASM_KEEP(a);%s\n    f(a);\n    g(a);\n}\n" % PIN)
        best = gen(t)[0][0][1]
        self.assertIn("    f(a);", best)
        self.assertIn("void f(S *a)", best)

    def test_nested_scope_name_that_escapes_its_block_refused(self):
        t = fn("void *a_in",
               "    if (x) {\n        S *a = a_in;\n        ASM_KEEP(a);%s\n        g(a);\n    }\n    h(a);\n" % PIN)
        self.refuse(t, "nested-scope-name-escapes")

    def test_preprocessor_region_refused(self):
        t = fn("void *a_in",
               "#ifdef NON_MATCHING\n    void *a = a_in;\n#else\n    void *a = a_in;\n#endif\n"
               "    ASM_KEEP(a);%s\n    g(a);\n" % PIN)
        self.refuse(t, "preprocessor-region")

    def test_use_before_the_copy_refused(self):
        t = fn("void *a_in", "    void *a;\n    g(a);\n    a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n" % PIN)
        self.refuse(t, "use-before-copy")

    def test_copy_outside_the_declaration_block_refused(self):
        t = fn("void *a_in", "    void *a;\n    if (x) {\n        a = a_in;\n    }\n    ASM_KEEP(a);%s\n    g(a);\n" % PIN)
        self.refuse(t, "copy-not-in-the-declaration-block")

    def test_declared_twice_refused(self):
        t = fn("void *a_in",
               "    void *a = a_in;\n    ASM_KEEP(a);%s\n    if (x) {\n        void *a;\n        g(a);\n    }\n    g(a);\n" % PIN)
        self.refuse(t, "declared-twice")

    def test_copy_with_no_pin_on_it_is_not_offered_alone(self):
        t = fn("void *a_in", "    void *a = a_in;\n    g(a);\n")
        self.refuse(t, "no-pin-removed")

    def test_multi_variable_pin_is_kept_not_erased(self):
        t = fn("void *a_in, void *b_in",
               "    void *a = a_in;\n    void *b = b_in;\n    ASM_KEEP(a);%s\n"
               "    ASM_KEEP_DEP_NV(b, a);%s\n    g(a, b);\n" % (PIN, PIN))
        cands, skips = gen(t)
        self.assertTrue(cands)
        self.assertTrue(skips["pin-shape-not-erasable"])
        for _, c in cands:
            self.assertIn("ASM_KEEP_DEP_NV(b, a)", c)

    def test_no_parameters(self):
        self.refuse(fn("void", "    void *a = 0;\n    ASM_KEEP(a);%s\n    g(a);\n" % PIN), "no-parameters")

    def test_eligible_reports_the_reason(self):
        t = fn("void *a_in", "    g(a_in);\n")
        self.assertIsNotNone(G.T.eligible(t, {}, {}))
        self.assertIsNone(G.T.eligible(TWO, {}, {}))


class ReviewFixes(unittest.TestCase):
    """The round-31 reviewer's eight synthetic cases (work/native_lane/r31_prologue/scratch/rev_synth.py)
    and the two rows that demonstrated them, one test each."""

    def refuse(self, text, key, env=None):
        with mock.patch.dict(os.environ, env or {}):
            cands, skips = gen(text)
        self.assertEqual(cands, [], "expected no candidate, got %s" % [l for l, _ in cands])
        self.assertTrue(skips[key], "expected the %r refusal, got %s" % (key, dict(skips)))

    # --- defect 2: a retype may not re-interpret a surviving use of the parameter ---------------
    def test_pointer_retype_that_changes_pointer_arithmetic_refused(self):
        # rev_synth case 1: void* byte arithmetic would become a sizeof(S) stride.
        self.refuse(fn("void *a_in", "    S *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n    h(a_in + 4);\n" % PIN),
                    "retype-pointer-use-not-value")

    def test_pointer_retype_that_changes_an_indexed_load_refused(self):
        # rev_synth case 2: a 1-byte load at +3 would become a struct load at +3*sizeof(S).
        self.refuse(fn("u8 *a_in", "    S *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n    k(a_in[3]);\n" % PIN),
                    "retype-pointer-use-not-value")

    def test_pointer_retype_with_only_value_uses_is_accepted(self):
        # the shape of the eight rows prologue1 landed: the retyped parameter survives as an argument.
        t = fn("void *a_in", "    S *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n    h(a_in, 2);\n" % PIN)
        cands, _ = gen(t)
        self.assertEqual(len(cands), 1)
        self.assertIn("void f(S *a)", cands[0][1])
        self.assertIn("h(a, 2);", cands[0][1])

    def test_pointer_retype_with_a_comparison_use_is_accepted(self):
        t = fn("void *a_in", "    S *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n    if (a_in == 0) { g(0); }\n" % PIN)
        cands, _ = gen(t)
        self.assertEqual(len(cands), 1)
        self.assertIn("if (a == 0)", cands[0][1])

    def test_pointer_retype_with_a_dereference_use_refused(self):
        self.refuse(fn("S *a_in", "    T *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n    h(a_in->x);\n" % PIN),
                    "retype-pointer-use-not-value")

    def test_pointer_retype_with_a_macro_call_use_refused(self):
        # MAC(p) may be `(p)[3]`: an argument slot of an upper-case callee is not a value use.
        self.refuse(fn("void *a_in", "    S *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n    h(MAC(a_in));\n" % PIN),
                    "retype-use-in-macro-call")

    def test_scalar_retype_with_a_surviving_use_refused(self):
        # rev_synth case 6: the high half the surviving use reads would be gone.
        self.refuse(fn("s32 a_in", "    s16 a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n    h(a_in >> 16);\n" % PIN),
                    "retype-scalar-surviving-use", env={"T69_RETYPE_SCALAR": "1"})

    def test_scalar_retype_that_changes_signedness_refused(self):
        # rev_synth case 7: a signed division would become unsigned.
        self.refuse(fn("s32 a_in", "    u32 a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n    h(a_in / 2);\n" % PIN),
                    "retype-scalar-surviving-use", env={"T69_RETYPE_SCALAR": "1"})

    def test_scalar_retype_with_no_surviving_use_still_opens(self):
        t = fn("s32 a_in", "    s16 a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n" % PIN)
        with mock.patch.dict(os.environ, {"T69_RETYPE_SCALAR": "1"}):
            cands, _ = gen(t)
        self.assertEqual(len(cands), 1)
        self.assertIn("void f(s16 a)", cands[0][1])

    # --- defect 1: no preprocessor directive line is ever rewritten ----------------------------
    def test_define_alias_of_the_parameter_refused(self):
        # src/dungeon/func_810332A4.c: `#define effect held_effect` with no #undef.  The merge used
        # to emit `#define held_effect held_effect` and silently change what `effect` means below.
        t = (HEAD + "void f(S *effect, S *motion)\n{\n    S1 *held_effect;\n    S1 *held_motion;\n"
             "    held_effect = effect;\n    held_motion = motion;\n"
             "#define effect held_effect\n#define motion held_motion\n"
             "    ASM_KEEP(held_effect);%s\n    g(effect, motion);\n}\n" % PIN)
        self.refuse(t, "macro-name-collision")

    def test_define_of_the_local_name_refused(self):
        t = (HEAD + "#define a 7\n" +
             fn("void *a_in", "    void *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n" % PIN)[len(HEAD):])
        self.refuse(t, "macro-name-collision")

    def test_no_candidate_ever_rewrites_a_directive_line(self):
        srcs = [TWO, DECLINIT,
                fn("void *a_in", "    S *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n    h(a_in, 1);\n" % PIN),
                HEAD + "#include \"a_in.h\"\n#pragma once\n" +
                fn("void *a_in", "    void *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n" % PIN)[len(HEAD):]]
        def directives(s):
            return sorted(l for l in s.splitlines() if l.lstrip().startswith("#"))

        for t in srcs:
            for lab, c in gen(t)[0]:
                self.assertEqual(directives(t), directives(c),
                                 "%s rewrote a directive line" % lab)

    def test_pp_depth_survives_a_bare_hash_line(self):
        G._pp_depth("#\n# \nint x;\n")          # used to raise IndexError on `# `

    # --- the rename must not reach a member, a string literal or a comment --------------------
    def test_member_of_the_same_name_is_not_renamed(self):
        # rev_synth case 3: `s->a_in` is a struct member, not the parameter.
        t = fn("void *a_in, S *s", "    void *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n    s->a_in = 1;\n" % PIN)
        cands, _ = gen(t)
        self.assertEqual(len(cands), 1)
        self.assertIn("s->a_in = 1;", cands[0][1])
        self.assertIn("void f(void *a, S *s)", cands[0][1])

    def test_string_literal_is_not_renamed(self):
        # rev_synth case 4
        t = fn("void *a_in", '    void *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n    p("a_in");\n' % PIN)
        cands, _ = gen(t)
        self.assertEqual(len(cands), 1)
        self.assertIn('p("a_in");', cands[0][1])

    def test_line_comment_is_not_renamed(self):
        # rev_synth case 8
        # (the reviewer's own line put the comment on the declaration, which the merge deletes whole;
        # the observable case is a comment on a line that survives)
        t = fn("void *a_in", "    void *a = a_in;\n    ASM_KEEP(a);%s\n"
                             "    g(a);  // a_in is the caller's node\n" % PIN)
        cands, _ = gen(t)
        self.assertEqual(len(cands), 1)
        self.assertIn("// a_in is the caller's node", cands[0][1])

    def test_a_stringizing_macro_call_on_the_parameter_refused(self):
        t = (HEAD + "#define NAME_OF(x) #x\n" +
             fn("void *a_in", "    void *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n    p(NAME_OF(a_in));\n" % PIN)[len(HEAD):])
        self.refuse(t, "macro-stringizes-the-name")

    # --- the `register` storage class is carried, never dropped -------------------------------
    def test_register_local_carries_its_storage_class(self):
        # rev_synth case 5
        t = fn("void *a_in", "    register void *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n" % PIN)
        cands, skips = gen(t)
        self.assertEqual(len(cands), 1)
        self.assertIn("void f(register void *a)", cands[0][1])
        self.assertTrue(skips["register-local-carried"])

    def test_register_local_carries_its_storage_class_with_a_retype(self):
        t = fn("void *a_in", "    register S *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n" % PIN)
        cands, _ = gen(t)
        self.assertEqual(len(cands), 1)
        self.assertIn("void f(register S *a)", cands[0][1])

    def test_register_is_not_doubled_on_a_register_parameter(self):
        t = fn("register void *a_in", "    register void *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n" % PIN)
        cands, _ = gen(t)
        self.assertEqual(len(cands), 1)
        self.assertNotIn("register register", cands[0][1])
        self.assertIn("void f(register void *a)", cands[0][1])

    def test_a_register_parameter_keeps_its_own_storage_class(self):
        # `functions()` reads `register void *` as the parameter's type, so the retype path used to
        # overwrite it with the local's plain type and drop the keyword.
        t = fn("register void *a_in", "    S *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n" % PIN)
        cands, _ = gen(t)
        self.assertEqual(len(cands), 1)
        self.assertIn("void f(register S *a)", cands[0][1])

    def test_a_register_parameter_is_not_a_retype(self):
        # `register void *` vs `void *` is the same type: no retype, and no prototype edit.
        t = (HEAD + "extern void f(void *);\n" +
             "void f(register void *a_in)\n{\n    void *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n}\n" % PIN)
        cands, _ = gen(t)
        self.assertEqual(len(cands), 1)
        self.assertIn("extern void f(void *);", cands[0][1])
        self.assertIn("void f(register void *a)", cands[0][1])

    def test_a_scalar_parameter_never_becomes_a_pointer(self):
        t = fn("s32 a_in", "    S *a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n" % PIN)
        self.refuse(t, "pointer-vs-scalar")
        self.refuse(t, "pointer-vs-scalar", env={"T69_RETYPE_SCALAR": "1"})

    def test_a_pointer_parameter_never_becomes_a_scalar(self):
        t = fn("void *a_in", "    s32 a = a_in;\n    ASM_KEEP(a);%s\n    g(a);\n" % PIN)
        self.refuse(t, "pointer-vs-scalar", env={"T69_RETYPE_SCALAR": "1"})


class Contract(unittest.TestCase):
    def test_class_shape(self):
        self.assertEqual(G.T.name, "t69_prologue")
        self.assertEqual(G.T.level, 1)
        self.assertTrue(G.T.needs_verify)

    def test_apply_verified_journals_its_skips_and_takes_the_first_exact(self):
        seen = []

        def vf(cand):
            seen.append(cand)
            return {"exact": len(seen) == 2}

        with mock.patch.object(G, "compile_s", lambda row, t: ["x"] * len(t)), \
             mock.patch.object(G, "sdiff", lambda a, b: abs(len(a) - len(b))):
            new, info = G.T.apply_verified(TWO, {"id": "x"}, {}, vf)
        self.assertIsNotNone(new)
        self.assertEqual(info["tried"], 2)
        self.assertIn("skips", info)
        self.assertLess(len(sites_of(new)), len(sites_of(TWO)))

    def test_apply_verified_misses_cleanly(self):
        with mock.patch.object(G, "compile_s", lambda row, t: ["x"]), \
             mock.patch.object(G, "sdiff", lambda a, b: 0):
            new, info = G.T.apply_verified(TWO, {"id": "x"}, {}, lambda c: {"exact": False})
        self.assertIsNone(new)
        self.assertEqual(info["refused"], ["no candidate exact at the recorded cell"])

    def test_apply_verified_drops_a_candidate_that_does_not_compile(self):
        with mock.patch.object(G, "compile_s", lambda row, t: None):
            new, info = G.T.apply_verified(TWO, {"id": "x"}, {}, lambda c: {"exact": True})
        self.assertIsNone(new)
        self.assertEqual(info["tried"], 0)


if __name__ == "__main__":
    unittest.main()
