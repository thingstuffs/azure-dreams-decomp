#!/usr/bin/env python3
"""Unit tests for tools/xform/t67_tailform.py - every move in both directions, and every refusal.

No compiles: the moves are text rewrites, so the whole contract (which shapes are produced, which are
refused, and that nothing else in the file moves) is decidable on synthetic texts.

    python3 -B tools/tests/test_t67_tailform.py
"""
import re
import sys
import unittest
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools"))

from pin_census import sites_of, unscored_text
from xform import t67_tailform as T67

HEAD = """#include \"common.h\"

extern void func_80010000(s32);
extern s32 func_80010004(void);

"""


def wrap(body, ret="void", params="s32 a, s32 b"):
    return HEAD + "%s BODY_NAME(%s)\n{\n%s}\n" % (ret, params, body)


def menu(text):
    """{label: candidate} for every move of one text (no cap)."""
    return {label: cand for label, cand in T67.tailform_candidates(text, cap=10 ** 6)}


def kinds(text):
    return sorted({k for k, _l, _c in T67.tailform_moves(text, None, 10 ** 6)})


def skips_of(text):
    import collections
    s = collections.Counter()
    T67.tailform_moves(text, s, 10 ** 6)
    return s


def pick(text, prefix):
    return {l: c for l, c in menu(text).items() if l.startswith(prefix)}


class Invariants(unittest.TestCase):
    """Properties every candidate of every move must have, whatever the text."""

    TEXTS = []

    def test_every_candidate_keeps_the_pin_multiset_and_the_unscored_arms(self):
        for text in self.TEXTS:
            key = T67._pin_key(text)
            usig = unscored_text(text)
            ppsig = T67._pp_sig(text)
            for label, cand in menu(text).items():
                self.assertEqual(T67._pin_key(cand), key, label)
                self.assertEqual(unscored_text(cand), usig, label)
                self.assertEqual(T67._pp_sig(cand), ppsig, label)
                self.assertNotEqual(cand, text, label)

    def test_no_candidate_introduces_scaffolding(self):
        for text in self.TEXTS:
            for label, cand in menu(text).items():
                for pat in T67.FORBIDDEN:
                    self.assertLessEqual(len(re.findall(pat, cand)), len(re.findall(pat, text)), label)

    def test_every_emitted_line_comes_from_the_text_or_is_a_label_or_a_jump(self):
        """The structural argument that replaces a qualifier count: a move never writes new C.

        Every line of a candidate is a line of the input, a line of the input re-indented, a fresh
        `L:`, a fresh `goto L;`, a `return E;` whose `E` is a source right-hand side, or a `} else {`
        / `}` brace assembled from the if's own indent.
        """
        for text in self.TEXTS:
            src = {ln.strip() for ln in text.splitlines()}
            for label, cand in menu(text).items():
                for ln in cand.splitlines():
                    s = ln.strip()
                    if not s or s in src:
                        continue
                    self.assertTrue(
                        re.fullmatch(r"(?:%s:|goto %s;|return [^;]*;|\} else \{|\})" % (T67.ID, T67.ID), s),
                        "%s produced a line that is not in the source: %r" % (label, ln))


class DupLabel(unittest.TestCase):
    BODY = """    s32 x;

    x = a;
    if (x > 0) {
        goto done;
    }
    x = b;
    if (x > 1) {
        goto done;
    }
    func_80010000(x);
    return;
done:
    func_80010000(0);
    return;
"""

    def test_the_tail_is_copied_over_every_goto_and_the_label_goes(self):
        text = wrap(self.BODY)
        c = pick(text, "dup_label:done:all")
        self.assertEqual(len(c), 1, sorted(menu(text)))
        label, cand = next(iter(c.items()))
        self.assertIn(":moved", label)                   # nothing falls into `done:`, so it is dropped
        self.assertNotIn("goto done;", cand)
        self.assertNotIn("done:", cand)
        self.assertEqual(cand.count("func_80010000(0);"), 2)

    def test_one_site_at_a_time_is_offered_and_keeps_the_label(self):
        text = wrap(self.BODY)
        c = pick(text, "dup_label:done:one@")
        self.assertEqual(len(c), 2, sorted(c))
        for label, cand in c.items():
            self.assertNotIn(":moved", label)
            self.assertIn("done:", cand)
            self.assertEqual(cand.count("goto done;"), 1)

    def test_a_single_goto_moves_the_tail(self):
        text = wrap("""    s32 x;

    x = a;
    if (x > 0) {
        goto done;
    }
    return;
done:
    func_80010000(0);
    return;
""")
        c = pick(text, "dup_label:done:")
        self.assertTrue(c, sorted(menu(text)))
        self.assertTrue(any(":moved" in l for l in c))

    def test_a_fallthrough_entry_keeps_the_label_and_its_tail(self):
        text = wrap("""    s32 x;

    x = a;
    if (x > 0) {
        goto done;
    }
    func_80010000(x);
done:
    func_80010000(0);
    return;
""")
        c = pick(text, "dup_label:done:")
        self.assertTrue(c, sorted(menu(text)))
        for label, cand in c.items():
            self.assertNotIn(":moved", label)
            self.assertIn("done:", cand)
            self.assertEqual(cand.count("func_80010000(0);"), 2)

    def test_a_tail_with_a_declaration_is_refused(self):
        text = wrap("""    s32 x;

    x = a;
    if (x > 0) {
        goto done;
    }
    if (x > 1) {
        goto done;
    }
    return;
done:
    {
        s32 y = 1;
        func_80010000(y);
    }
    return;
""")
        self.assertFalse(pick(text, "dup_label:done"), sorted(menu(text)))

    def test_a_tail_with_a_pin_is_refused_and_reachable_once_the_pin_is_erased(self):
        text = wrap("""    s32 x;

    x = a;
    if (x > 0) {
        goto done;
    }
    if (x > 1) {
        goto done;
    }
    return;
done:
    ASM_SCHED_BARRIER();
    func_80010000(0);
    return;
""")
        self.assertFalse(pick(text, "dup_label:done"), sorted(menu(text)))
        self.assertIn("dup_label:run-stops-at-pin", skips_of(text))
        from pin_sites import erase_many
        base = erase_many(text, sites_of(text), clean_notes=True)
        self.assertTrue(pick(base, "dup_label:done"), sorted(menu(base)))

    def test_a_tail_with_a_label_in_it_is_refused(self):
        text = wrap("""    s32 x;

    x = a;
    if (x > 0) {
        goto done;
    }
    if (x > 1) {
        goto done;
    }
    return;
done:
    x = 1;
mid:
    func_80010000(x);
    return;
""")
        self.assertFalse(pick(text, "dup_label:done"), sorted(menu(text)))

    def test_a_preprocessor_line_in_the_tail_is_refused(self):
        text = wrap("""    s32 x;

    x = a;
    if (x > 0) {
        goto done;
    }
    if (x > 1) {
        goto done;
    }
    return;
done:
#ifdef __mips__
    func_80010000(0);
#else
    func_80010000(1);
#endif
    return;
""")
        self.assertFalse(pick(text, "dup_label:done"), sorted(menu(text)))

    def test_a_break_in_a_copied_tail_that_would_change_target_is_refused(self):
        """The tail's `break;` leaves the `switch`; copied into the `while` body it would leave the
        loop instead.  Equal depth, different target."""
        text = wrap("""    s32 x;

    x = 0;
    while (x < 10) {
        x = x + 1;
        goto out;
    }
    switch (a) {
    case 1:
        func_80010000(1);
out:
        func_80010000(2);
        break;
    }
    return;
""")
        self.assertFalse(pick(text, "dup_label:out"), sorted(menu(text)))
        self.assertIn("dup_label:jump-target", skips_of(text))

    def test_a_tail_copied_into_a_block_that_shadows_one_of_its_names_is_refused(self):
        """The goto sits inside a block with its own `x`; the tail's `x` is the outer one."""
        shadowed = wrap("""    s32 x;

    x = a;
    if (x > 0) {
        s32 x;

        x = 2;
        func_80010000(x);
        goto done;
    }
    return;
done:
    func_80010000(x);
    return;
""")
        self.assertFalse(pick(shadowed, "dup_label:done"), sorted(menu(shadowed)))
        self.assertIn("dup_label:scope", skips_of(shadowed))
        plain = shadowed.replace("        s32 x;\n\n        x = 2;\n", "        x = 2;\n")
        self.assertTrue(pick(plain, "dup_label:done"), sorted(menu(plain)))

    def test_hoisting_a_tail_that_names_an_arm_local_is_refused(self):
        text = wrap("""    s32 x;

    if (a > 0) {
        s32 y;

        y = 1;
        x = y;
    } else {
        s32 y;

        y = 2;
        x = y;
    }
    return;
""")
        self.assertFalse(pick(text, "hoist_tail:"), sorted(menu(text)))
        self.assertIn("hoist_tail:scope", skips_of(text))


class SinkAndHoist(unittest.TestCase):
    IFELSE = """    s32 x;

    if (a > 0) {
        x = 1;
    } else {
        x = 2;
    }
    func_80010000(x);
    func_80010000(b);
    return;
"""

    def test_sink_pushes_the_tail_into_both_arms(self):
        text = wrap(self.IFELSE)
        c = pick(text, "sink_tail:if-else")
        self.assertEqual(len(c), 1, sorted(menu(text)))
        cand = next(iter(c.values()))
        self.assertEqual(cand.count("func_80010000(x);"), 2)
        self.assertEqual(cand.count("func_80010000(b);"), 2)
        # the tail is gone from after the if/else: it now stands only inside the two arms
        body = cand.split("{\n", 1)[1]
        self.assertNotIn("    }\n    func_80010000(x);", body)

    def test_hoist_is_the_exact_inverse(self):
        text = wrap(self.IFELSE)
        sunk = next(iter(pick(text, "sink_tail:if-else").values()))
        back = pick(sunk, "hoist_tail:")
        self.assertTrue(back, sorted(menu(sunk)))
        self.assertIn(re.sub(r"\s+", " ", text), [re.sub(r"\s+", " ", c) for c in back.values()])

    def test_hoist_offers_every_suffix_length(self):
        text = wrap("""    s32 x;

    if (a > 0) {
        x = 1;
        func_80010000(x);
        func_80010000(b);
    } else {
        x = 2;
        func_80010000(x);
        func_80010000(b);
    }
    return;
""")
        c = pick(text, "hoist_tail:")
        self.assertEqual(sorted(l.split(":")[1].split("@")[0] for l in c), ["1", "2"])

    def test_hoist_refuses_to_empty_an_arm(self):
        text = wrap("""    s32 x;

    if (a > 0) {
        x = 1;
        func_80010000(x);
    } else {
        func_80010000(x);
    }
    return;
""")
        self.assertFalse(pick(text, "hoist_tail:"), sorted(menu(text)))
        self.assertIn("hoist_tail:empties-an-arm", skips_of(text))

    def test_hoist_refuses_a_run_that_is_not_token_identical(self):
        text = wrap("""    s32 x;

    if (a > 0) {
        x = 1;
        func_80010000(1);
    } else {
        x = 2;
        func_80010000(2);
    }
    return;
""")
        self.assertFalse(pick(text, "hoist_tail:"), sorted(menu(text)))

    def test_token_equality_sees_through_whitespace_but_not_through_a_string(self):
        def k(line):
            return T67._key(T67.Ctx(wrap("    %s\n" % line)), [len(HEAD.splitlines()) + 2])

        # whitespace and comments do not decide it
        self.assertEqual(k("x = a  +  1;"), k("x=a+1;"))
        self.assertEqual(k("x = 1; /* a note */"), k("x = 1;"))
        self.assertEqual(k("x = 1; // a note"), k("x = 1;"))
        # ... but no two token-different lines may share a key
        self.assertNotEqual(k('f("a");'), k('f("b");'))
        self.assertNotEqual(k('f("http://a");'), k('f("http://b");'))   # `//` inside a string
        self.assertNotEqual(k("y = - -y;"), k("y = --y;"))              # adjacent operators
        self.assertNotEqual(k("y = + +y;"), k("y = ++y;"))
        self.assertNotEqual(k("y = a - -1;"), k("y = a--1;"))
        self.assertNotEqual(k("y = p - > q;"), k("y = p->q;"))
        self.assertNotEqual(k("y = a < < 1;"), k("y = a<<1;"))
        self.assertNotEqual(k("y = 1e-3;"), k("y = 1e - 3;"))
        self.assertNotEqual(k("f('a');"), k("f('b');"))

    def test_sink_without_an_else_needs_a_terminating_arm(self):
        term = wrap("""    s32 x;

    x = 0;
    if (a > 0) {
        func_80010000(1);
        return;
    }
    func_80010000(x);
    return;
""")
        c = pick(term, "sink_tail:else@")
        self.assertEqual(len(c), 1, sorted(menu(term)))
        cand = next(iter(c.values()))
        self.assertIn("} else {", cand)
        self.assertEqual(cand.count("func_80010000(x);"), 1)

        nonterm = term.replace("        func_80010000(1);\n        return;\n", "        func_80010000(1);\n")
        self.assertFalse(pick(nonterm, "sink_tail:else@"), sorted(menu(nonterm)))
        self.assertIn("sink_tail:arm-does-not-terminate", skips_of(nonterm))

    def test_sink_without_an_else_refuses_a_close_line_carrying_a_comment(self):
        text = wrap("""    s32 x;

    x = 0;
    if (a > 0) {
        func_80010000(1);
        return;
    }   /* MATCH pin: the arm above is the retail block */
    func_80010000(x);
    return;
""")
        self.assertFalse(pick(text, "sink_tail:else@"), sorted(menu(text)))
        self.assertIn("sink_tail:close-line-carries-a-comment", skips_of(text))

    def test_hoist_refuses_a_suffix_that_would_step_over_a_guarded_statement(self):
        """`_arm_lines` does not see preprocessor-guarded lines; a two-line suffix that spans one
        would reorder the arm's guarded statement past the hoisted pair."""
        text = wrap("""    s32 x;

    if (a > 0) {
        func_80010000(7);
        x = 1;
#ifdef __mips__
        func_80010000(9);
#endif
        func_80010000(x);
    } else {
        func_80010000(8);
        x = 1;
        func_80010000(x);
    }
    return;
""")
        labels = sorted(pick(text, "hoist_tail:"))
        self.assertTrue(any(l.startswith("hoist_tail:1@") for l in labels), labels)
        self.assertFalse(any(l.startswith("hoist_tail:2@") for l in labels), labels)
        self.assertIn("hoist_tail:pp-line-inside-the-suffix", skips_of(text))

    def test_sink_refuses_a_tail_with_a_declaration_or_a_pin(self):
        decl = wrap("""    s32 x;

    if (a > 0) {
        x = 1;
    } else {
        x = 2;
    }
    {
        s32 y = x;

        func_80010000(y);
    }
    return;
""")
        self.assertFalse(pick(decl, "sink_tail:if-else"), sorted(menu(decl)))
        pin = wrap("""    s32 x;

    if (a > 0) {
        x = 1;
    } else {
        x = 2;
    }
    ASM_KEEP(x);
    func_80010000(x);
    return;
""")
        self.assertFalse(pick(pin, "sink_tail:if-else"), sorted(menu(pin)))


class MergeRuns(unittest.TestCase):
    BODY = """    s32 x;

    x = a;
    if (x > 0) {
        func_80010000(1);
        func_80010000(2);
        return;
    }
    func_80010000(1);
    func_80010000(2);
    return;
"""

    def test_both_assignments_are_offered_for_every_shared_suffix(self):
        """Every run of 2..8 statements ending in the terminator is a merge of its own, and each is
        offered in both assignments (`:first` keeps the earlier body, `:second` the later)."""
        text = wrap(self.BODY)
        c = pick(text, "merge_runs:")
        self.assertEqual(sorted(l.split(":")[1] for l in c),
                         ["first", "first", "second", "second"], sorted(menu(text)))

    def test_the_merged_side_becomes_a_goto_to_a_fresh_label(self):
        text = wrap(self.BODY)
        for label, cand in pick(text, "merge_runs:").items():
            self.assertEqual(cand.count("shared_tail:"), 1, label)
            self.assertEqual(cand.count("goto shared_tail;"), 1, label)
            self.assertEqual(cand.count("func_80010000(2);"), 1, label)
        whole = [c for l, c in pick(text, "merge_runs:").items() if l.endswith("12+16")]
        self.assertEqual(len(whole), 1)
        self.assertEqual(whole[0].count("func_80010000(1);"), 1)

    def test_a_run_of_one_plain_statement_is_not_merged(self):
        text = wrap("""    s32 x;

    x = a;
    if (x > 0) {
        return;
    }
    return;
""")
        self.assertFalse(pick(text, "merge_runs:"), sorted(menu(text)))

    def test_a_run_that_is_not_the_last_statement_of_its_block_is_refused(self):
        """A statement after the inner run's terminator: only `:second` (the label on the outer,
        block-final run) survives."""
        text = wrap(self.BODY).replace(
            "        func_80010000(2);\n        return;\n    }",
            "        func_80010000(2);\n        return;\n        x = 3;\n    }")
        c = pick(text, "merge_runs:")
        self.assertEqual(sorted({l.split(":")[1] for l in c}), ["second"], sorted(menu(text)))
        self.assertIn("merge_runs:not-last-in-block", skips_of(text))

    def test_a_goto_into_a_loop_body_is_refused(self):
        text = wrap("""    s32 x;

    x = 0;
    while (x < 10) {
        func_80010000(1);
        func_80010000(2);
        return;
    }
    func_80010000(1);
    func_80010000(2);
    return;
""")
        c = pick(text, "merge_runs:")
        self.assertEqual(sorted({l.split(":")[1] for l in c}), ["second"], sorted(menu(text)))
        self.assertIn("merge_runs:jump-into", skips_of(text))

    def test_a_goto_into_a_block_with_an_initialised_declaration_is_refused(self):
        text = wrap("""    s32 x;

    x = a;
    if (x > 0) {
        s32 y = 3;

        func_80010000(y);
        func_80010000(2);
        return;
    }
    func_80010000(y);
    func_80010000(2);
    return;
""")
        self.assertNotIn("merge_runs:first", "".join(menu(text)))

    def test_a_break_terminator_in_two_different_loops_is_refused(self):
        text = wrap("""    s32 x;

    x = 0;
    while (x < 10) {
        func_80010000(1);
        func_80010000(2);
        break;
    }
    while (x < 20) {
        func_80010000(1);
        func_80010000(2);
        break;
    }
    return;
""")
        self.assertFalse(pick(text, "merge_runs:"), sorted(menu(text)))


class SplitRet(unittest.TestCase):
    BODY = """    s32 v;

    if (a > 0) {
        v = 1;
        goto ret;
    }
    v = 2;
    goto ret;
ret:
    return v;
"""

    def test_every_goto_becomes_its_own_return_and_the_tail_goes(self):
        text = wrap(self.BODY, ret="s32")
        c = pick(text, "split_ret:ret:all")
        self.assertEqual(len(c), 1, sorted(menu(text)))
        label, cand = next(iter(c.items()))
        self.assertIn(":dropped", label)
        self.assertNotIn("goto ret;", cand)
        self.assertNotIn("ret:", cand)
        self.assertNotIn("return v;", cand)
        self.assertIn("return 1;", cand)
        self.assertIn("return 2;", cand)
        self.assertNotIn("s32 v;", cand)

    def test_one_at_a_time_keeps_the_tail(self):
        text = wrap(self.BODY, ret="s32")
        c = pick(text, "split_ret:ret:one@")
        self.assertEqual(len(c), 2, sorted(c))
        for label, cand in c.items():
            self.assertIn("return v;", cand)
            self.assertEqual(cand.count("goto ret;"), 1)

    def test_a_narrower_variable_than_the_return_type_is_refused(self):
        text = wrap(self.BODY.replace("s32 v;", "s16 v;"), ret="s32")
        self.assertFalse(pick(text, "split_ret:ret:"), sorted(menu(text)))
        self.assertIn("split_ret:type-differs-from-return-type", skips_of(text))

    def test_a_qualified_variable_is_refused(self):
        for q in ("volatile s32 v;", "const s32 v;", "static s32 v;"):
            text = wrap(self.BODY.replace("s32 v;", q), ret="s32")
            self.assertFalse(pick(text, "split_ret:ret:"), q)
            self.assertIn("split_ret:qualified-or-pinned", skips_of(text), q)

    def test_a_variable_used_elsewhere_is_refused(self):
        text = wrap(self.BODY.replace("    return v;\n", "    func_80010000(v);\n    return v;\n"),
                    ret="s32")
        self.assertFalse(pick(text, "split_ret:ret:"), sorted(menu(text)))

    def test_a_fallthrough_into_the_return_label_is_refused(self):
        text = wrap("""    s32 v;

    if (a > 0) {
        v = 1;
        goto ret;
    }
    v = 2;
ret:
    return v;
""", ret="s32")
        self.assertFalse(pick(text, "split_ret:ret:"), sorted(menu(text)))
        self.assertIn("split_ret:fallthrough-into-label", skips_of(text))

    def test_the_reverse_merges_two_identical_returns_under_one_label(self):
        text = wrap("""    s32 x;

    x = a;
    if (x > 0) {
        return x + 1;
    }
    return x + 1;
""", ret="s32")
        c = pick(text, "split_ret:merge:")
        self.assertEqual(sorted(l.split(":")[2] for l in c), ["first", "second"], sorted(menu(text)))
        for label, cand in c.items():
            self.assertEqual(cand.count("return x + 1;"), 1, label)
            self.assertEqual(cand.count("goto return_tail;"), 1, label)
            self.assertEqual(cand.count("return_tail:"), 1, label)

    def test_a_bare_return_is_not_merged(self):
        text = wrap("""    s32 x;

    x = a;
    if (x > 0) {
        return;
    }
    return;
""")
        self.assertFalse(pick(text, "split_ret:merge:"), sorted(menu(text)))


class CommentsAreNeverDropped(unittest.TestCase):
    """Every whole-line edit matches on the MASKED line and writes a fresh one; a trailing comment on
    the original - an m2c note, or a `/* MATCH pin: ... */` describing a pin still in the file - would
    vanish.  A line whose text is copied over verbatim keeps its comment and is NOT refused."""

    def test_dup_label_refuses_a_commented_goto_and_a_commented_label(self):
        base = """    s32 x;

    x = a;
    if (x > 0) {
        goto done;%s
    }
    if (x > 1) {
        goto done;
    }
    return;
done:%s
    func_80010000(0);
    return;
"""
        plain = wrap(base % ("", ""))
        self.assertTrue(pick(plain, "dup_label:done"))
        on_goto = wrap(base % ("   /* MATCH pin: the branch retail takes */", ""))
        self.assertFalse([l for l in pick(on_goto, "dup_label:done") if "one@5" in l or ":all" in l],
                         sorted(menu(on_goto)))
        self.assertIn("dup_label:comment-on-a-replaced-line", skips_of(on_goto))
        on_label = wrap(base % ("", "   /* the shared exit */"))
        self.assertFalse([l for l in pick(on_label, "dup_label:done") if ":moved" in l],
                         sorted(menu(on_label)))

    def test_a_copied_tail_keeps_its_own_comments(self):
        text = wrap("""    s32 x;

    x = a;
    if (x > 0) {
        goto done;
    }
    if (x > 1) {
        goto done;
    }
    return;
done:
    func_80010000(0);   /* m2c: the shared epilogue */
    return;
""")
        c = pick(text, "dup_label:done:all")
        self.assertEqual(len(c), 1, sorted(menu(text)))
        self.assertEqual(next(iter(c.values())).count("/* m2c: the shared epilogue */"), 2)

    def test_hoist_refuses_a_comment_on_the_deleted_else_copy(self):
        text = wrap("""    s32 x;

    if (a > 0) {
        x = 1;
        func_80010000(x);
    } else {
        x = 2;
        func_80010000(x);   /* the copy that would be deleted */
    }
    return;
""")
        self.assertFalse(pick(text, "hoist_tail:"), sorted(menu(text)))
        self.assertIn("hoist_tail:comment-on-a-deleted-line", skips_of(text))

    def test_merge_runs_refuses_a_comment_on_the_run_it_replaces(self):
        text = wrap(MergeRuns.BODY.replace(
            "    func_80010000(1);\n    func_80010000(2);\n    return;\n",
            "    func_80010000(1);   /* the outer copy */\n    func_80010000(2);\n    return;\n"))
        got = sorted(pick(text, "merge_runs:"))
        # the full run (whose first line now carries the comment) is refused in the `:first`
        # assignment that would replace it; the shorter suffix, which does not include that line, stays
        self.assertNotIn("merge_runs:first:12+16", got, got)
        self.assertIn("merge_runs:first:13+17", got, got)
        self.assertIn("merge_runs:comment-on-a-replaced-line", skips_of(text))

    def test_split_ret_refuses_a_comment_on_any_line_it_removes(self):
        for where, repl in (("assignment", ("        v = 1;\n", "        v = 1;   /* retail's value */\n")),
                            ("goto", ("        goto ret;\n", "        goto ret;   /* the shared exit */\n")),
                            ("declaration", ("    s32 v;\n", "    s32 v;   /* m2c: the result */\n"))):
            text = wrap(SplitRet.BODY.replace(*repl), ret="s32")
            self.assertNotEqual(wrap(SplitRet.BODY, ret="s32"), text, where)
            got = pick(text, "split_ret:ret:")
            self.assertFalse([l for l in got if ":dropped" in l], (where, sorted(got)))
            self.assertIn("split_ret:comment-on-a-replaced-line", skips_of(text), where)

    def test_split_ret_merge_refuses_a_comment_on_the_return_it_replaces(self):
        text = wrap("""    s32 x;

    x = a;
    if (x > 0) {
        return x + 1;   /* the arm's copy */
    }
    return x + 1;
""", ret="s32")
        self.assertFalse([l for l in pick(text, "split_ret:merge:") if l.endswith("+8")],
                         sorted(menu(text)))
        self.assertIn("split_ret:merge-comment-on-a-replaced-line", skips_of(text))


class MultiLineStatements(unittest.TestCase):
    """A physical line is not a statement.  `t51.units()` is line-based, so a continuation line can
    be balanced and `;`-terminated on its own; moving one cuts its statement in half."""

    def test_a_continuation_line_is_never_a_tail_statement(self):
        text = wrap("""    s32 x;

    if (a > 0) {
        x = 1;
        func_80010000(((a * 3) +
            ((b * 5) >> 2)));
    } else {
        x = 2;
        func_80010000(((a * 3) +
            ((b * 5) >> 2)));
    }
    return;
""")
        ctx = T67.Ctx(text)
        lines = [ln.strip() for ln in text.splitlines()]
        cont = lines.index("((b * 5) >> 2)));")
        self.assertEqual(T67.kind_of(ctx, cont), "continuation")
        self.assertEqual(T67.kind_of(ctx, cont - 1), "partial")
        self.assertFalse(pick(text, "hoist_tail:"), sorted(menu(text)))

    def test_a_braceless_if_body_on_the_next_line_is_not_a_terminator(self):
        text = wrap("""    s32 x;

    x = a;
    if (x > 0)
        return;
    if (x > 1) {
        goto done;
    }
    if (x > 2) {
        goto done;
    }
    return;
done:
    func_80010000(0);
    return;
""")
        ctx = T67.Ctx(text)
        cont = [ln.strip() for ln in text.splitlines()].index("return;")
        self.assertEqual(T67.kind_of(ctx, cont), "continuation")
        for label, cand in menu(text).items():           # nothing may carry that `return;` away
            self.assertIn("    if (x > 0)\n        return;\n", cand, label)

    def test_every_candidate_of_a_multi_line_row_still_compiles_as_C_text(self):
        """Structural stand-in for the compiler: no candidate may leave a line whose parentheses do
        not balance where the base's did."""
        text = wrap("""    s32 x;

    x = a;
    if (x > 0) {
        goto done;
    }
    if (x > 1) {
        goto done;
    }
    return;
done:
    func_80010000(((a * 3) +
        ((b * 5) >> 2)));
    return;
""")
        for label, cand in menu(text).items():
            self.assertEqual(cand.count("("), cand.count(")"), label)
            self.assertEqual(cand.count("{"), cand.count("}"), label)
        self.assertFalse(pick(text, "dup_label:done"), sorted(menu(text)))


class PinsAndArms(unittest.TestCase):
    PINNED = wrap("""    register s32 x ASM_REG("$2");

    x = a;
    if (x > 0) {
        goto done;
    }
    if (x > 1) {
        goto done;
    }
    ASM_SCHED_BARRIER();
    func_80010000(x);
    return;
done:
    func_80010000(0);
    return;
""")

    def test_the_pin_count_is_exactly_preserved_by_every_move(self):
        n = len(sites_of(self.PINNED))
        self.assertEqual(n, 2)
        cands = menu(self.PINNED)
        self.assertTrue(cands)
        for label, cand in cands.items():
            self.assertEqual(len(sites_of(cand)), n, label)

    def test_unscored_text_is_unchanged_and_a_non_mips_arm_is_never_edited(self):
        text = self.PINNED.replace(
            "    register s32 x ASM_REG(\"$2\");\n",
            "#ifdef __mips__\n    register s32 x ASM_REG(\"$2\");\n#else\n    s32 x;\n#endif\n")
        usig = unscored_text(text)
        ppsig = T67._pp_sig(text)
        for label, cand in menu(text).items():
            self.assertEqual(unscored_text(cand), usig, label)
            self.assertEqual(T67._pp_sig(cand), ppsig, label)
            self.assertIn("    s32 x;", cand, label)

    def test_a_move_whose_tail_holds_the_pin_is_refused_here_and_offered_after_the_erasure(self):
        text = wrap("""    s32 x;

    x = a;
    if (x > 0) {
        goto done;
    }
    if (x > 1) {
        goto done;
    }
    return;
done:
    ASM_KEEP(x);
    func_80010000(x);
    return;
""")
        self.assertFalse(pick(text, "dup_label:done"))
        from pin_sites import erase_many
        base = erase_many(text, sites_of(text), clean_notes=True)
        self.assertTrue(pick(base, "dup_label:done"))

    def test_eligible_and_the_menu_cap(self):
        row = {"cfg": "2.7.2:-O2"}
        self.assertIsNone(T67.T.eligible(self.PINNED, row, {}))
        self.assertIsNotNone(T67.T.eligible(wrap("    return;\n"), row, {}))
        self.assertIsNotNone(T67.T.eligible(self.PINNED, {}, {}))
        self.assertLessEqual(len(T67.tailform_candidates(self.PINNED)), T67.MENU_CAP)

    def test_candidates_are_ordered_by_distance_from_a_live_pin(self):
        ctx = T67.Ctx(self.PINNED)
        self.assertTrue(ctx.pinlines)
        self.assertEqual(ctx.near_pin(ctx.pinlines[0]), 0)


class BracelessAnchors(unittest.TestCase):
    """The ANCHOR refusal: the line a move REWRITES or inserts after may not be a braceless body.

    Round-29 review: `_starts_statement`/`kind_of` were applied only to the lines INSIDE a tail or a
    run, never to the anchor.  Four of the five moves therefore accepted an anchor that is the
    braceless body of an `if`/`while`/`for` head on the line above and emitted C whose control flow
    differs from the base while compiling cleanly - so the screen could not reject it and it was a
    live `vf` candidate.  One real row was affected (`town/func_808110CC`).  Each text below is one
    of the reviewer's probes.
    """

    def test_dup_label_refuses_a_goto_that_is_a_braceless_if_body(self):
        text = wrap("""    s32 t;

    t = 0;
    if (a) {
        ASM_KEEP(t);
    }
    if (a)
        goto L;
    t = 5;
    return t;

L:
    t = 1;
    t = t + 2;
    return t;
""", ret="s32")
        self.assertFalse(pick(text, "dup_label"), sorted(menu(text)))
        self.assertTrue(skips_of(text)["dup_label:goto-is-a-braceless-body"])
        # the braced form of the same shape IS offered: the refusal is about the anchor, not the label
        ok = text.replace("    if (a)\n        goto L;\n", "    if (a) {\n        goto L;\n    }\n")
        self.assertTrue(pick(ok, "dup_label"), sorted(menu(ok)))

    def test_a_braceless_goto_still_counts_as_an_entry_so_the_label_is_kept(self):
        """The braced `goto L;` may still be rewritten - but L may NOT be dropped.

        A braceless `goto L;` is refused as an ANCHOR (it stays in `refs`, never in `whole`), so
        `set(chosen) == set(refs)` is false and no candidate may take the `:moved` form.
        """
        text = wrap("""    s32 t;

    t = 0;
    ASM_KEEP(t);
    if (a) {
        goto L;
    }
    if (b)
        goto L;
    t = 5;
    return t;

L:
    t = 1;
    t = t + 2;
    return t;
""", ret="s32")
        c = pick(text, "dup_label:L:")
        self.assertTrue(c, sorted(menu(text)))
        self.assertFalse([l for l in c if l.endswith(":moved")], sorted(c))
        self.assertFalse([l for l in c if ":all" in l], sorted(c))
        for lab, cand in c.items():
            self.assertIn("\nL:\n", cand, lab)                      # the label survives
            self.assertIn("    if (b)\n        goto L;\n", cand, lab)   # the braceless site is untouched
        self.assertTrue(skips_of(text)["dup_label:goto-is-a-braceless-body"])

    def test_sink_refuses_an_if_block_that_is_a_braceless_while_body(self):
        text = wrap("""    s32 t;

    t = 0;
    ASM_KEEP(t);
    while (a)
        if (b) {
            return 1;
        }
    t = 9;
    return t;
""", ret="s32")
        self.assertFalse(pick(text, "sink_tail"), sorted(menu(text)))
        self.assertTrue(skips_of(text)["sink_tail:if-head-is-a-braceless-body"])

    def test_sink_and_hoist_refuse_an_if_else_that_is_a_braceless_if_body(self):
        text = wrap("""    s32 t;

    t = 0;
    ASM_KEEP(t);
    if (a)
        if (b) {
            t = 1;
            c = c + 1;
        } else {
            t = 2;
            c = c + 1;
        }
    t = t + 3;
    return t;
""", ret="s32", params="s32 a, s32 b, s32 c")
        self.assertFalse(pick(text, "sink_tail"), sorted(menu(text)))
        self.assertFalse(pick(text, "hoist_tail"), sorted(menu(text)))
        s = skips_of(text)
        self.assertTrue(s["sink_tail:if-head-is-a-braceless-body"])
        self.assertTrue(s["hoist_tail:if-head-is-a-braceless-body"])

    def test_split_ret_refuses_an_assignment_that_is_a_braceless_if_body(self):
        text = wrap("""    s32 v;
    s32 z;

    z = 0;
    ASM_KEEP(z);
    if (b) {
        v = 7;
        goto R;
    }
    if (a)
        v = 1;
    goto R;

R:
    return v;
""", ret="s32")
        self.assertFalse(pick(text, "split_ret:R"), sorted(menu(text)))


class TokenEquality(unittest.TestCase):
    """`_key` is a C tokenizer, not squashed whitespace: no two token-different lines share a key."""

    def test_hoist_refuses_two_arms_whose_suffixes_only_look_alike(self):
        text = wrap("""    s32 x;

    x = 0;
    ASM_KEEP(x);
    if (a) {
        x = 3;
        b = - -b;
    } else {
        x = 4;
        b = --b;
    }
    return x + b;
""", ret="s32")
        self.assertFalse(pick(text, "hoist_tail"), sorted(menu(text)))

    def test_ret_merge_refuses_two_returns_that_only_look_alike(self):
        text = wrap("""    s32 x;

    x = 0;
    ASM_KEEP(x);
    if (a) {
        return - -b;
    }
    if (b) {
        return --b;
    }
    return x;
""", ret="s32")
        self.assertFalse(pick(text, "split_ret:merge"), sorted(menu(text)))

    def test_merge_runs_refuses_two_runs_with_different_string_arguments(self):
        text = wrap("""    s32 x;

    x = 0;
    ASM_KEEP(x);
    if (a) {
        func_80010000(1);
        func_80010008("http://a");
        return;
    }
    if (x) {
        func_80010000(1);
        func_80010008("http://b");
        return;
    }
""")
        self.assertFalse(pick(text, "merge_runs"), sorted(menu(text)))
        same = text.replace('"http://b"', '"http://a"')
        self.assertTrue(pick(same, "merge_runs"), sorted(menu(same)))


class HoistScope(unittest.TestCase):
    """Both copies are scope-checked, not only the one that survives."""

    def test_hoist_refuses_when_the_deleted_else_copy_reads_an_arm_local(self):
        text = wrap("""    s32 t;

    t = 0;
    ASM_KEEP(t);
    if (a) {
        func_80010000(1);
        t = b;
    } else {
        s32 b;

        b = func_80010004();
        func_80010000(b);
        t = b;
    }
    return t;
""", ret="s32")
        self.assertFalse(pick(text, "hoist_tail"), sorted(menu(text)))
        self.assertTrue(skips_of(text)["hoist_tail:scope"])
        # without the shadowing declaration the same hoist IS offered
        ok = text.replace("        s32 b;\n\n", "")
        self.assertTrue(pick(ok, "hoist_tail"), sorted(menu(ok)))


Invariants.TEXTS = [DupLabel.BODY and wrap(DupLabel.BODY), wrap(SinkAndHoist.IFELSE),
                    wrap(MergeRuns.BODY), wrap(SplitRet.BODY, ret="s32"), PinsAndArms.PINNED,
                    wrap("""    s32 t;

    t = 0;
    if (a) {
        ASM_KEEP(t);
    }
    if (a)
        goto L;
    t = 5;
    return t;

L:
    t = 1;
    t = t + 2;
    return t;
""", ret="s32"),
                    wrap("""    s32 v;
    s32 z;

    z = 0;
    ASM_KEEP(z);
    if (b) {
        v = 7;
        goto R;
    }
    if (a)
        v = 1;
    goto R;

R:
    return v;
""", ret="s32")]


if __name__ == "__main__":
    unittest.main(verbosity=2)
