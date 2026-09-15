#!/usr/bin/env python3
"""Unit tests for tools/xform/t59_offsetsym.py - the round-30 openings and every refusal.

No compiles: the move is a text rewrite, so what is offered, what is refused and what the rewritten
text looks like are all decidable on synthetic texts.

    python3 -B tools/tests/test_t59_offsetsym.py
"""
import os
import re
import sys
import unittest
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools"))

from pin_census import sites_of, unscored_text            # noqa: E402
from xform import t59_offsetsym as T59                    # noqa: E402

HEAD = """#include "common.h"

extern u8 D_80084054[];
extern u8 D_80084000[];
extern u8 D_80083E98[];
extern s16 D_80083460[];
extern u8 D_8007DC40[];
extern u8 D_80084074[];

"""


def wrap(body, decls="    u8 *page;\n    u8 *q;\n"):
    return HEAD + "void func_80010000(void)\n{\n" + decls + body + "}\n"


def pages(text, skips=None):
    return T59.find(text, skips)


def only(text):
    """The single page t59 finds, or a failure."""
    ps = pages(text)
    assert len(ps) == 1, "expected one page, got %d" % len(ps)
    return ps[0]


def apply_all(text):
    page = only(text)
    return T59.rewrite(text, page, page[3])


ALL_OPEN = dict(T59_SIGNED_OFFSET="1", T59_SELF_BUMP="1", T59_KEEP_GAP="1", T59_ANY_LITERAL="1")
ALL_SHUT = dict(T59_SIGNED_OFFSET="0", T59_SELF_BUMP="0", T59_KEEP_GAP="0", T59_ANY_LITERAL="0")


class Env(unittest.TestCase):
    def setUp(self):
        self._saved = {k: os.environ.get(k) for k in T59.SWITCHES}
        os.environ.update(ALL_OPEN)

    def tearDown(self):
        for k, v in self._saved.items():
            if v is None:
                os.environ.pop(k, None)
            else:
                os.environ[k] = v


# ------------------------------------------------------------------ the shipped move still works
class Shipped(Env):
    def test_plain_offset_use(self):
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = page + 0x4054;\n"
                 "    q[0] = 1;\n")
        out = apply_all(t)
        self.assertIn("q = D_80084054;", out)
        self.assertNotIn("0x80080000", out)
        self.assertNotIn("ASM_KEEP(page)", out)
        self.assertEqual(len(sites_of(out)), len(sites_of(t)) - 1)

    def test_cast_is_preserved_never_invented(self):
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = (u8 *)(page + 0x4054);\n")
        self.assertIn("q = (u8 *)D_80084054;", apply_all(t))

    def test_switches_shut_is_the_shipped_spelling(self):
        os.environ.update(ALL_SHUT)
        shut = wrap("    page = (u8 *)0x80080000;\n"
                    "    ASM_KEEP(page);\n"
                    "    q = page - 0x23C0;\n")
        self.assertEqual(pages(shut), [])
        os.environ.update(ALL_OPEN)
        self.assertEqual(len(pages(shut)), 1)


# ------------------------------------------------------------------ refusals
class Refusals(Env):
    def test_never_matches_inside_a_non_matching_arm(self):
        t = wrap("#ifdef NON_MATCHING\n"
                 "    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = page + 0x4054;\n"
                 "#endif\n")
        self.assertEqual(pages(t), [])

    def test_never_matches_inside_if_zero(self):
        t = wrap("#if 0\n"
                 "    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = page + 0x4054;\n"
                 "#endif\n")
        self.assertEqual(pages(t), [])

    def test_never_matches_inside_an_unknown_conditional(self):
        # arm_labels calls these lines "both" - the t66 defect of round 28
        t = wrap("#ifdef __mips__\n"
                 "    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = page + 0x4054;\n"
                 "#endif\n")
        self.assertEqual(pages(t), [])

    def test_symbol_spelled_only_in_a_port_arm_is_not_a_symbol(self):
        t = (HEAD.replace("extern u8 D_80084054[];\n", "") +
             "void func_80010000(void)\n{\n    u8 *page;\n    u8 *q;\n"
             "#ifdef NON_MATCHING\n    q = D_80084054;\n#endif\n"
             "    page = (u8 *)0x80080000;\n"
             "    ASM_KEEP(page);\n"
             "    q = page + 0x4054;\n}\n")
        sk = {}
        self.assertEqual(pages(t, sk), [])
        self.assertIn("no-symbol-named-at-the-address", sk)

    def test_symbol_without_an_extern_declaration_is_refused(self):
        # the name is in the code, but not behind an `extern`: t59 will not spell it
        t = (HEAD.replace("extern u8 D_80084054[];", "static u8 D_80084054[32];") +
             "void func_80010000(void)\n{\n    u8 *page;\n    u8 *q;\n"
             "    page = (u8 *)0x80080000;\n"
             "    ASM_KEEP(page);\n"
             "    q = page + 0x4054;\n}\n")
        sk = {}
        self.assertEqual(pages(t, sk), [])
        self.assertEqual(sk.get("symbol-has-no-extern-declaration"), 1)

    def test_no_symbol_at_the_address_is_refused(self):
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = page + 0x1234;\n")
        sk = {}
        self.assertEqual(pages(t, sk), [])
        self.assertEqual(sk.get("no-symbol-named-at-the-address"), 1)

    def test_unbalanced_parentheses_are_refused(self):
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = (u8 *)(page + 0x4054;\n")
        self.assertEqual(pages(t), [])

    def test_no_pin_no_page(self):
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    q = page + 0x4054;\n")
        self.assertEqual(pages(t), [])


# ------------------------------------------------------------------ scaling (the round-30 defect)
class Scaling(Env):
    def test_pointer_arithmetic_scales_by_the_declaration(self):
        t = wrap("    page = (s16 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = (u8 *)(page + 0x1A30);\n",
                 decls="    s16 *page;\n    u8 *q;\n")
        # 0x1A30 shorts = 0x3460 bytes -> D_80083460
        self.assertIn("q = (u8 *)D_80083460;", apply_all(t))

    def test_void_star_star_scales_by_four(self):
        t = wrap("    page = (void **)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = (u8 *)(page + 0x1000);\n",
                 decls="    void **page;\n    u8 *q;\n")
        self.assertIn("q = (u8 *)D_80084000;", apply_all(t))

    def test_the_inner_cast_beats_the_declaration(self):
        t = wrap("    page = (void **)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = (u8 *)((u8 *)page + 0x4074);\n",
                 decls="    void **page;\n    u8 *q;\n")
        self.assertIn("q = (u8 *)D_80084074;", apply_all(t))

    def test_a_cast_that_is_not_parenthesising_applies_to_the_page(self):
        t = wrap("    page = (void **)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = (u8 *)page + 0x4074;\n",
                 decls="    void **page;\n    u8 *q;\n")
        self.assertIn("q = (u8 *)D_80084074;", apply_all(t))

    def test_an_integer_page_scales_by_one(self):
        t = wrap("    page = 0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = (u8 *)(page + 0x4054);\n",
                 decls="    u32 page;\n    u8 *q;\n")
        self.assertIn("q = (u8 *)D_80084054;", apply_all(t))


# ------------------------------------------------------------------ T59_SIGNED_OFFSET
class SignedOffset(Env):
    def test_minus_offset(self):
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = (u8 *)(page - 0x23C0);\n")
        self.assertIn("q = (u8 *)D_8007DC40;", apply_all(t))

    def test_shut_off_the_minus_use_is_gone(self):
        os.environ["T59_SIGNED_OFFSET"] = "0"
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = (u8 *)(page - 0x23C0);\n")
        self.assertEqual(pages(t), [])


# ------------------------------------------------------------------ T59_SELF_BUMP
class SelfAdvance(Env):
    BODY = ("    page = (u8 *)0x80080000;\n"
            "    ASM_KEEP(page);\n"
            "    page += 0x3E98;\n"
            "    q = page;\n")

    def test_bump_becomes_the_symbol(self):
        t = wrap(self.BODY)
        out = apply_all(t)
        self.assertIn("page = D_80083E98;", out)
        self.assertNotIn("+= 0x3E98", out)
        self.assertNotIn("0x80080000", out)
        self.assertEqual(len(sites_of(out)), len(sites_of(t)) - 1)

    def test_minus_bump(self):
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    page -= 0x23C0;\n"
                 "    q = page;\n")
        self.assertIn("page = D_8007DC40;", apply_all(t))

    def test_self_assignment_with_a_cast(self):
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    page = (u8 *)page + 0x4054;\n"
                 "    q = page;\n")
        out = apply_all(t)
        self.assertIn("page = D_80084054;", out)
        self.assertNotIn("0x4054", out)

    def test_another_reader_before_the_advance_refuses(self):
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = page;\n"
                 "    page += 0x3E98;\n")
        sk = {}
        self.assertEqual(pages(t, sk), [])
        self.assertEqual(sk.get("advance-is-not-the-page-value's-only-reader"), 1)

    def test_advance_inside_a_loop_refuses(self):
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    while (1) {\n"
                 "        page += 0x3E98;\n"
                 "    }\n")
        sk = {}
        self.assertEqual(pages(t, sk), [])
        self.assertEqual(sk.get("advance-is-conditional-or-in-another-block"), 1)

    def test_a_label_between_refuses(self):
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = 0;\n"
                 "again:\n"
                 "    page += 0x3E98;\n")
        sk = {}
        self.assertEqual(pages(t, sk), [])
        self.assertEqual(sk.get("advance-is-conditional-or-in-another-block"), 1)

    def test_a_case_label_between_refuses(self):
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    switch (1) {\n"
                 "    case 0:\n"
                 "        page += 0x3E98;\n"
                 "    }\n")
        sk = {}
        self.assertEqual(pages(t, sk), [])
        self.assertEqual(sk.get("advance-is-conditional-or-in-another-block"), 1)

    def test_a_balanced_if_between_is_allowed(self):
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    if (q == 0) {\n"
                 "        q = (u8 *)1;\n"
                 "    }\n"
                 "    page += 0x3E98;\n")
        self.assertIn("page = D_80083E98;", apply_all(t))

    def test_shut_off_no_advance(self):
        os.environ["T59_SELF_BUMP"] = "0"
        self.assertEqual(pages(wrap(self.BODY)), [])


# ------------------------------------------------------------------ T59_KEEP_GAP
class KeepGap(Env):
    def test_another_pin_between(self):
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(q);\n"
                 "    ASM_KEEP(page);\n"
                 "    q = page + 0x4054;\n")
        out = apply_all(t)
        self.assertIn("q = D_80084054;", out)
        self.assertIn("ASM_KEEP(q);", out)            # the other pin is untouched
        self.assertNotIn("ASM_KEEP(page)", out)

    def test_an_unrelated_statement_between(self):
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    q = (u8 *)0;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = page + 0x4054;\n")
        self.assertIn("q = D_80084054;", apply_all(t))

    def test_a_reader_of_the_page_between_stops_the_scan(self):
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    q = page + 4;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = page + 0x4054;\n")
        self.assertEqual(pages(t), [])

    def test_shut_off_only_the_adjacent_keep(self):
        os.environ["T59_KEEP_GAP"] = "0"
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(q);\n"
                 "    ASM_KEEP(page);\n"
                 "    q = page + 0x4054;\n")
        sk = {}
        self.assertEqual(pages(t, sk), [])
        self.assertEqual(sk.get("keep-not-on-the-line-after-the-page-definition"), 1)


# ------------------------------------------------------------------ definitions inside an arm
class ArmSplitPage(Env):
    SPLIT = ("#ifdef NON_MATCHING\n"
             "    page = D_80084054 - 0x4054;\n"
             "#else\n"
             "    page = (u8 *)0x80080000;\n"
             "#endif\n"
             "    ASM_KEEP(page);\n"
             "    q = page + 0x4054;\n")

    def test_the_keep_goes_and_the_arm_does_not(self):
        t = wrap(self.SPLIT)
        out = apply_all(t)
        self.assertIn("q = D_80084054;", out)
        self.assertNotIn("ASM_KEEP(page)", out)
        self.assertIn("    page = (u8 *)0x80080000;", out)        # the definition stays
        self.assertIn("#ifdef NON_MATCHING", out)
        self.assertEqual(unscored_text(out), unscored_text(t))     # the port arm is byte-identical
        self.assertEqual(len(sites_of(out)), len(sites_of(t)) - 1)

    def test_a_match_only_arm_is_edited_and_the_port_side_is_untouched(self):
        """`#ifndef NON_MATCHING` is the code the byte gate compiles: editing it is the whole job."""
        t = (HEAD + "void func_80010000(void)\n{\n    u8 *page;\n    u8 *q;\n"
             "#ifndef NON_MATCHING\n"
             "    page = (u8 *)0x80080000;\n"
             "    ASM_KEEP(page);\n"
             "    page += 0x3E98;\n"
             "    q = page;\n"
             "#else\n"
             "    q = D_80083E98;\n"
             "#endif\n}\n")
        out = apply_all(t)
        self.assertIn("page = D_80083E98;", out)
        self.assertNotIn("ASM_KEEP(page)", out)
        self.assertIn("#ifndef NON_MATCHING", out)
        self.assertEqual(unscored_text(out), unscored_text(t))
        self.assertIn("    q = D_80083E98;\n#endif", out)      # the port arm, verbatim
        self.assertEqual(len(sites_of(out)), len(sites_of(t)) - 1)

    def test_a_locked_definition_is_reported(self):
        self.assertTrue(only(wrap(self.SPLIT))[5])

    def test_a_plain_definition_is_not_locked(self):
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = page + 0x4054;\n")
        self.assertFalse(only(t)[5])


# ------------------------------------------------------------------ liveness of the definition
class Liveness(Env):
    def test_a_surviving_reader_keeps_the_definition(self):
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = page + 0x4054;\n"
                 "    q = page + 8;\n")
        out = apply_all(t)
        self.assertIn("q = D_80084054;", out)
        self.assertIn("page = (u8 *)0x80080000;", out)   # still read by `page + 8`
        self.assertNotIn("ASM_KEEP(page)", out)

    def test_a_surviving_bump_keeps_the_definition(self):
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = page + 0x4054;\n"
                 "    page += 8;\n")
        out = apply_all(t)
        self.assertIn("page = (u8 *)0x80080000;", out)

    def test_a_use_after_a_bump_is_not_offered(self):
        # `page + 0x4054` after `page += 8` is NOT at 0x80084054 any more
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    page += 0x4000;\n"
                 "    q = page + 0x54;\n")
        page = only(t)
        self.assertEqual([k for k, _s, _e, _r in page[3]], ["bump"])

    def test_everything_dead_drops_definition_and_keep(self):
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = page + 0x4054;\n")
        out = apply_all(t)
        self.assertNotIn("page = (u8 *)0x80080000;", out)


# ------------------------------------------------------------------ T59_ANY_LITERAL
class AnyLiteral(Env):
    def test_a_page_with_a_non_zero_low_half(self):
        t = wrap("    page = (u8 *)0x80084000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = page + 0x54;\n")
        self.assertIn("q = D_80084054;", apply_all(t))

    def test_shut_off(self):
        os.environ["T59_ANY_LITERAL"] = "0"
        t = wrap("    page = (u8 *)0x80084000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = page + 0x54;\n")
        self.assertEqual(pages(t), [])


# ------------------------------------------------------------------ invariants over every candidate
class Invariants(Env):
    TEXTS = [
        wrap("    page = (u8 *)0x80080000;\n    ASM_KEEP(page);\n    q = page + 0x4054;\n"),
        wrap("    page = (u8 *)0x80080000;\n    ASM_KEEP(page);\n    page += 0x3E98;\n    q = page;\n"),
        wrap("    page = (u8 *)0x80080000;\n    ASM_KEEP(q);\n    ASM_KEEP(page);\n    q = page - 0x23C0;\n"),
        wrap(ArmSplitPage.SPLIT),
    ]
    SCAFFOLD = re.compile(r"__asm__|\bvolatile\b|do\s*\{|while\s*\(\s*0\s*\)|for\s*\(\s*;\s*0\s*;|#pragma"
                          r"|__attribute__|ASM_[A-Z0-9_]*\s*\(")

    def test_every_candidate_removes_a_pin_and_adds_no_scaffolding(self):
        for t in self.TEXTS:
            for page in pages(t):
                for chosen in [[u] for u in page[3]] + [page[3]]:
                    out = T59.rewrite(t, page, chosen)
                    self.assertLess(len(sites_of(out)), len(sites_of(t)), t)
                    self.assertEqual(unscored_text(out), unscored_text(t), t)
                    before = len(self.SCAFFOLD.findall(t))
                    self.assertLessEqual(len(self.SCAFFOLD.findall(out)), before, t)
                    self.assertNotIn("extern", out[out.index("void func_80010000"):])

    def test_no_integer_replaces_a_symbol(self):
        for t in self.TEXTS:
            out = apply_all(t)
            for m in re.finditer(r"\bD_([0-9A-F]{8})\b", t):
                self.assertIn(m.group(0), out, t)

    def test_eligible_reports_the_shape(self):
        self.assertIsNone(T59.T.eligible(self.TEXTS[0], None, None))
        self.assertEqual(T59.T.eligible(wrap("    q = (u8 *)0;\n"), None, None),
                         "no kept page with a symbol-backed offset use")


class Spelling(Env):
    """The declaration decides `D_X` vs `&D_X` - a scalar cast as a pointer does not compile."""

    def test_a_scalar_only_symbol_takes_its_address(self):
        head = HEAD.replace("extern u8 D_80084054[];", "extern PackedOffsets D_80084054;")
        t = (head + "void func_80010000(void)\n{\n    u8 *page;\n    PackedOffsets *q;\n"
             "    page = (u8 *)0x80080000;\n"
             "    ASM_KEEP(page);\n"
             "    q = (PackedOffsets *)(page + 0x4054);\n}\n")
        self.assertIn("q = (PackedOffsets *)&D_80084054;", apply_all(t))

    def test_an_array_symbol_decays(self):
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = page + 0x4054;\n")
        self.assertIn("q = D_80084054;", apply_all(t))


# ================================================================== round-30 review fixes
# Three defects an adversarial reviewer demonstrated on the first version of the openings.  Each shape
# below is one of their repros; the assertion is the REFUSAL (and its journal key), or - for the shapes
# that stay legal - that the candidate is unchanged.
class Dominance(Env):
    """Defect 1: `straight_line` counted braces, so BRACELESS control flow passed it."""

    DEF = "    page = (u8 *)0x80080000;\n    ASM_KEEP(page);\n"
    KEY = "advance-is-conditional-or-in-another-block"

    def refused(self, body):
        sk = {}
        self.assertEqual(pages(wrap(self.DEF + body), sk), [], body)
        self.assertEqual(sk.get(self.KEY), 1, sk)

    def test_a_braceless_if_between_refuses(self):
        # accepted before the fix: the candidate erased the definition and left `if (c) page = D_X;`,
        # so on !c the page was undefined
        self.refused("    if (c)\n        page += 0x3E98;\n    q = page;\n")

    def test_a_braceless_while_between_refuses(self):
        # the advance is per-iteration; `page = D_X;` in a loop is not the same value
        self.refused("    while (c)\n        page += 0x3E98;\n    q = page;\n")

    def test_a_braceless_else_between_refuses(self):
        self.refused("    if (c) {\n        c = 1;\n    } else\n        page += 0x3E98;\n    q = page;\n")

    def test_a_braceless_for_between_refuses(self):
        self.refused("    for (c = 0; c < 4; c++)\n        page += 0x3E98;\n    q = page;\n")

    def test_a_break_between_refuses(self):
        # the advance can be LEFT OUT where the definition ran
        self.refused("    if (c) {\n        break;\n    }\n    page += 0x3E98;\n    q = page;\n")

    def test_a_continue_between_refuses(self):
        self.refused("    if (c) {\n        continue;\n    }\n    page += 0x3E98;\n    q = page;\n")

    def test_a_return_between_refuses(self):
        self.refused("    if (c) {\n        return;\n    }\n    page += 0x3E98;\n    q = page;\n")

    def test_a_macro_control_header_between_refuses(self):
        # `FOR_EACH(c)` is a call to t59's eyes; the segment not ending on `;` or `}` is what catches it
        self.refused("    FOR_EACH(c)\n        page += 0x3E98;\n    q = page;\n")

    def test_a_guarded_self_assignment_refuses(self):
        # `if (c) page = (u8 *)page + K;` - the guard is on the advance's own line
        self.refused("    if (c) page = (u8 *)page + 0x3E98;\n    q = page;\n")

    def test_a_complete_braced_if_between_is_still_allowed(self):
        t = wrap(self.DEF + "    if (c) {\n        q = (u8 *)1;\n    }\n    page += 0x3E98;\n    q = page;\n")
        self.assertIn("page = D_80083E98;", apply_all(t))

    def test_a_complete_do_while_between_is_still_allowed(self):
        t = wrap(self.DEF + "    do {\n        q = (u8 *)1;\n    } while (c);\n"
                            "    page += 0x3E98;\n    q = page;\n")
        self.assertIn("page = D_80083E98;", apply_all(t))

    def test_a_complete_else_if_chain_between_is_still_allowed(self):
        t = wrap(self.DEF + "    if (c) {\n        q = (u8 *)1;\n    } else if (c == 2) {\n"
                            "        q = (u8 *)2;\n    }\n    page += 0x3E98;\n    q = page;\n")
        self.assertIn("page = D_80083E98;", apply_all(t))


class AdvanceSpan(Env):
    """Defect 2: the advance was replaced by rewriting its WHOLE LINE, deleting anything else on it."""

    DEF = "    page = (u8 *)0x80080000;\n    ASM_KEEP(page);\n"

    def test_a_statement_after_a_bump_on_the_same_line_survives(self):
        out = apply_all(wrap(self.DEF + "    page += 0x3E98; q = page;\n"))
        self.assertIn("page = D_80083E98; q = page;", out)

    def test_a_comment_after_a_bump_survives(self):
        out = apply_all(wrap(self.DEF + "    page += 0x3E98;   /* the note */\n    q = page;\n"))
        self.assertIn("page = D_80083E98;   /* the note */", out)

    def test_a_statement_after_a_self_assignment_survives(self):
        out = apply_all(wrap(self.DEF + "    page = (u8 *)page + 0x3E98; q = page;\n"))
        self.assertIn("page = D_80083E98; q = page;", out)

    def test_the_replacement_touches_no_character_outside_the_advance(self):
        t = wrap(self.DEF + "    page += 0x3E98;\n    q = page;\n")
        page = only(t)
        for kind, s, e, rep in page[3]:
            self.assertEqual(kind, "bump")
            self.assertRegex(t[s:e], r"^[ \t]*page \+= 0x3E98;$")     # the span ends at the `;`
            self.assertTrue(rep.endswith(";") and "\n" not in rep, rep)


class KeepGapStructure(Env):
    """Defect 3: the keep-gap loop applied no structural test, so a definition inside a conditional
    block was paired with a keep outside it - erased from the block, its use made unconditional."""

    KEY = "keep-is-not-in-the-page-definition's-block"

    def refused(self, body, key=None):
        sk = {}
        self.assertEqual(pages(wrap(body), sk), [], body)
        self.assertEqual(sk.get(key or self.KEY), 1, sk)

    def test_a_definition_inside_an_if_block_refuses(self):
        self.refused("    if (c) {\n        page = (u8 *)0x80080000;\n    }\n"
                     "    ASM_KEEP(page);\n    q = page + 0x4054;\n")

    def test_a_label_in_the_gap_refuses(self):
        self.refused("    page = (u8 *)0x80080000;\n    c = 1;\nagain:\n"
                     "    ASM_KEEP(page);\n    q = page + 0x4054;\n")

    def test_a_case_label_in_the_gap_refuses(self):
        self.refused("    switch (c) {\n    case 0:\n        page = (u8 *)0x80080000;\n"
                     "    case 1:\n        ASM_KEEP(page);\n        q = page + 0x4054;\n    }\n")

    def test_a_definition_that_is_a_braceless_body_refuses(self):
        self.refused("    if (c)\n        page = (u8 *)0x80080000;\n"
                     "    ASM_KEEP(page);\n    q = page + 0x4054;\n",
                     key="page-definition-is-a-braceless-body")

    def test_a_keep_that_is_a_braceless_body_refuses(self):
        # (the gap `if (c)` fails the structural test first - either refusal keeps the keep in place)
        sk = {}
        t = wrap("    page = (u8 *)0x80080000;\n    if (c)\n        ASM_KEEP(page);\n"
                 "    q = page + 0x4054;\n")
        self.assertEqual(pages(t, sk), [])
        self.assertTrue(set(sk) & {self.KEY, "keep-is-a-braceless-body"}, sk)

    def test_a_use_past_a_label_is_refused(self):
        # the definition dominates the keep, but a `goto` can enter at the label with the page unset
        sk = {}
        t = wrap("    page = (u8 *)0x80080000;\n    ASM_KEEP(page);\n"
                 "    if (c) goto again;\nagain:\n    q = page + 0x4054;\n")
        self.assertEqual(pages(t, sk), [])
        self.assertEqual(sk.get("use-is-past-a-label-or-jump-from-the-keep"), 1, sk)

    def test_directives_and_other_pins_in_the_gap_are_still_allowed(self):
        t = wrap("    page = (u8 *)0x80080000;\n#ifdef FOO\n#endif\n"
                 "    ASM_KEEP(q);\n    ASM_KEEP(page);\n    q = page + 0x4054;\n")
        out = apply_all(t)
        self.assertIn("q = D_80084054;", out)
        self.assertIn("ASM_KEEP(q);", out)
        self.assertIn("#ifdef FOO", out)


class OneTripBlock(Env):
    """The one gap that still crosses a block boundary: `do { ... } while (0);` runs exactly once, so
    the definition does dominate its keep.  The definition is then KEPT (no empty block left behind)."""

    BODY = ("    do {\n        page = (u8 *)0x80080000;\n    } while (0);\n"
            "    ASM_KEEP(page);\n    q = page + 0x4054;\n")

    def test_the_use_is_respelled_and_the_definition_stays(self):
        t = wrap(self.BODY)
        page = only(t)
        self.assertTrue(page[5], "a one-trip definition must be def_locked")
        out = T59.rewrite(t, page, page[3])
        self.assertIn("q = D_80084054;", out)
        self.assertNotIn("ASM_KEEP(page)", out)
        self.assertIn("        page = (u8 *)0x80080000;\n", out)     # still inside the block
        self.assertNotIn("do {\n    } while (0);", out)              # and no empty block left behind
        self.assertEqual(len(sites_of(out)), len(sites_of(t)) - 1)

    def test_a_real_loop_is_not_one_trip(self):
        sk = {}
        t = wrap("    do {\n        page = (u8 *)0x80080000;\n    } while (c);\n"
                 "    ASM_KEEP(page);\n    q = page + 0x4054;\n")
        self.assertEqual(pages(t, sk), [])
        self.assertEqual(sk.get(KeepGapStructure.KEY), 1)

    def test_a_while_zero_loop_is_not_a_do_while_zero(self):
        # `while (0) { page = ...; }` never runs at all; only a `do` block is one-trip
        sk = {}
        t = wrap("    while (0) {\n        page = (u8 *)0x80080000;\n    }\n"
                 "    ASM_KEEP(page);\n    q = page + 0x4054;\n")
        self.assertEqual(pages(t, sk), [])
        self.assertEqual(sk.get(KeepGapStructure.KEY), 1)


class NothingElseIsDeleted(Env):
    """Over every shape this file builds: a candidate erases only the keep, the page definition and the
    advance it rewrites.  Any other line of the row must survive verbatim."""

    BODIES = [
        "    page = (u8 *)0x80080000;\n    ASM_KEEP(page);\n    q = page + 0x4054;\n    c = 7;\n",
        "    page = (u8 *)0x80080000;\n    ASM_KEEP(page);\n    page += 0x3E98; c = 7;\n    q = page;\n",
        "    page = (u8 *)0x80080000;\n    ASM_KEEP(page);\n    page = (u8 *)page + 0x4054; c = 7;\n"
        "    q = page;\n",
        "    page = (u8 *)0x80080000;\n    ASM_KEEP(q);\n    c = 7;\n    ASM_KEEP(page);\n"
        "    q = page - 0x23C0;\n",
        OneTripBlock.BODY + "    c = 7;\n",
    ]

    def test_no_other_statement_is_deleted(self):
        for body in self.BODIES:
            t = wrap(body, decls="    u8 *page;\n    u8 *q;\n    int c;\n")
            for page in pages(t):
                for chosen in [[u] for u in page[3]] + [page[3]]:
                    out = T59.rewrite(t, page, chosen)
                    self.assertIn("c = 7;", out, body)
                    self.assertIn("int c;", out, body)
                    self.assertEqual(out.count("ASM_KEEP(q);"), t.count("ASM_KEEP(q);"), body)


class Apply(Env):
    def test_apply_verified_journals_its_refusals(self):
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = page + 0x4054;\n")
        new, info = T59.T.apply_verified(t, {"cfg": "2.7.2"}, {}, lambda c, cfg=None: {"exact": False})
        self.assertIsNone(new)
        self.assertEqual(info["skips"].get("not-exact"), 1)
        self.assertTrue(all(info["openings"].values()))

    def test_apply_verified_takes_the_first_exact_candidate(self):
        t = wrap("    page = (u8 *)0x80080000;\n"
                 "    ASM_KEEP(page);\n"
                 "    q = page + 0x4054;\n")
        new, info = T59.T.apply_verified(t, {"cfg": "2.7.2"}, {}, lambda c, cfg=None: {"exact": True})
        self.assertIsNotNone(new)
        self.assertEqual(info["pins_out"], info["pins_in"] - 1)
        self.assertIn("step", info)


if __name__ == "__main__":
    unittest.main(verbosity=2)
