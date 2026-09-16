"""The round-33 catalogue's declaration- and control-level perturbations: each move on synthetic text,
and the cases each kind must REFUSE.

Every test is textual (no compiler).  The contract under test is the catalogue's:
`PERTURBATIONS = [(kind, fn)]`, `fn(text, detail=None) -> [(params, new_text)]`, `params` carrying
`site` and `label`, enumeration deterministic and ordered by site, and no instance that changes what
the text means - a braceless arm, a short-circuit operand, a nested-block name under `__typeof__`, a
pointer increment under a cast, a loop body with `break`, a body that declares a variable.
"""
import collections
import re
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
for p in (ROOT / "tools", ROOT / "tools/lanes"):
    if str(p) not in sys.path:
        sys.path.insert(0, str(p))

import perturb_struct as P                                       # noqa: E402

HEAD = '#include "common.h"\n\ntypedef struct S { s32 a; s16 b; S *next; } S;\n\n'


def fn(params, body, head=HEAD, name="f"):
    return head + "void %s(%s)\n{\n%s}\n" % (name, params, body)


def run(kind, text):
    """(instances, detail) for one kind."""
    f = dict(P.PERTURBATIONS)[kind]
    d = P.Detail()
    return f(text, d), d


def labels(kind, text):
    return [p["label"] for p, _ in run(kind, text)[0]]


def only(kind, text, needle):
    """The one instance whose label holds `needle`."""
    got = [c for p, c in run(kind, text)[0] if needle in p["label"]]
    assert len(got) == 1, "expected exactly one %r instance, got %d" % (needle, len(got))
    return got[0]


# --------------------------------------------------------------------------- the contract

class Contract(unittest.TestCase):
    def test_menu_shape(self):
        self.assertEqual(P.KINDS, ["hoist", "retype_void", "split", "merge", "goto_to_loop",
                                   "tail_merge", "dup_tail", "cond_temp"])
        for kind, f in P.PERTURBATIONS:
            self.assertTrue(re.fullmatch(r"[a-z][a-z_]*", kind), kind)
            self.assertTrue(callable(f))

    def test_every_instance_carries_site_and_label(self):
        t = fn("S *p, s32 n", "    s32 x;\n    s32 y;\n\n    x = p->a + n;\n    y = p->b;\n"
                              "    g(x, y);\n")
        for kind, f in P.PERTURBATIONS:
            for params, cand in f(t, P.Detail()):
                self.assertIn("site", params)
                self.assertIn("label", params)
                self.assertIsInstance(params["site"], int)
                self.assertGreaterEqual(params["site"], 1)
                self.assertIsInstance(params["label"], str)
                self.assertNotEqual(cand, t)
                import json
                json.dumps(params)                     # params must be JSON-serialisable

    def test_enumeration_is_deterministic_and_ordered_by_site(self):
        t = fn("S *p, s32 n", "    s32 x;\n    s32 y;\n\n    x = p->a + n;\n    y = p->b;\n"
                              "    g(p->a, y);\n")
        for kind, f in P.PERTURBATIONS:
            a, b = f(t, P.Detail()), f(t, P.Detail())
            self.assertEqual([p["label"] for p, _ in a], [p["label"] for p, _ in b])
            self.assertEqual([c for _, c in a], [c for _, c in b])
            self.assertEqual([p["site"] for p, _ in a], sorted(p["site"] for p, _ in a))

    def test_a_plain_counter_works_as_detail(self):
        t = fn("S *p", "    s32 x;\n\n    x = p->a;\n    g(x);\n")
        c = collections.Counter()
        P.hoist(t, c)
        self.assertTrue(isinstance(c, collections.Counter))
        P.hoist(t, None)                                # None is allowed too

    def test_detail_records_what_each_refusal_was_about(self):
        t = fn("S *p", "    s32 x;\n\n    if (p->a)\n        x = p->b;\n    g(x);\n")
        _, d = run("hoist", t)
        self.assertIn("hoist:braceless-arm", d)
        self.assertTrue(any(k == "hoist:braceless-arm" for k, _ in d.detail))

    def test_no_instance_adds_scaffolding(self):
        t = fn("S *p, s32 n", "    s32 x;\n    s32 y;\n\n    x = p->a + n;\n    y = p->b;\n"
                              "    g(p->a, y);\n")
        for kind, f in P.PERTURBATIONS:
            for _, cand in f(t, P.Detail()):
                for bad in ("ASM_", "__asm__", "volatile", "#pragma", "__attribute__"):
                    self.assertNotIn(bad, cand, "%s added %s" % (kind, bad))


# --------------------------------------------------------------------------- hoist

class Hoist(unittest.TestCase):
    BASE = fn("S *p, s32 n", "    s32 x;\n    s32 y;\n\n    x = p->a;\n    y = n + 1;\n    g(x, y);\n")

    def test_member_load_is_hoisted_into_a_typeof_temporary(self):
        cand = only("hoist", self.BASE, "hoist:member:p->a")
        self.assertIn("    __typeof__(p->a) hoisted_1;\n", cand)
        self.assertIn("    hoisted_1 = p->a;\n", cand)
        self.assertIn("    x = hoisted_1;\n", cand)
        self.assertNotIn("x = p->a;", cand)

    def test_the_temporary_is_the_last_declaration_of_the_block(self):
        cand = only("hoist", self.BASE, "hoist:member:p->a")
        lines = cand.split("\n")
        i = next(k for k, l in enumerate(lines) if "__typeof__" in l)
        self.assertEqual(lines[i - 1].strip(), "s32 y;")          # after the block's last declaration
        self.assertTrue(lines[i + 1].strip() in ("", "hoisted_1 = p->a;"))
        params = next(p for p, c in run("hoist", self.BASE)[0] if c == cand)
        self.assertEqual(params["decl_pos"], "after_last_decl")
        self.assertEqual(params["expr"], "p->a")
        self.assertEqual(params["expr_class"], "member")

    def test_array_and_arithmetic_and_argument_classes(self):
        t = fn("S *p, s32 *v, s32 n",
               "    s32 x;\n\n    x = v[n + 1];\n    x = p->a + n;\n    g(p->a + n, x);\n")
        cls = {p["expr_class"] for p, _ in run("hoist", t)[0]}
        self.assertTrue({"array", "arith"} <= cls, cls)
        self.assertIn("hoist:array:v[n + 1]@9", labels("hoist", t))

    def test_a_chain_through_a_cast_is_hoisted(self):
        t = fn("void *q", "    s32 x;\n\n    x = ((S *)q)->a;\n    g(x);\n")
        cand = only("hoist", t, "hoist:member:((S *)q)->a")
        self.assertIn("__typeof__(((S *)q)->a) hoisted_1;", cand)
        self.assertIn("hoisted_1 = ((S *)q)->a;", cand)

    def test_a_pointer_prefix_of_an_lvalue_chain_is_still_hoisted(self):
        t = fn("S *p", "    s32 x;\n\n    x = 0;\n    p->next->a = 1;\n    g(x);\n")
        cand = only("hoist", t, "hoist:member:p->next@")
        self.assertIn("hoisted_1 = p->next;", cand)
        self.assertIn("hoisted_1->a = 1;", cand)          # the store still goes through the pointer

    # ---- must refuse

    def test_refuses_the_prefix_of_a_value_lvalue_chain(self):
        """`sprite->unk_0C.at00.v = 0x80;` - the copy would take the store and it would vanish."""
        t = fn("S *p", "    s32 x;\n\n    x = 0;\n    p->next->u.at00.v = 0x80;\n    g(x);\n")
        got, d = run("hoist", t)
        self.assertNotIn("u.at00", " ".join(pp["label"] for pp, _ in got))
        self.assertGreaterEqual(d["hoist:aggregate-prefix"], 1)
        for pp, _ in got:
            self.assertNotIn("at00", pp["expr"])

    def test_refuses_a_braceless_arm(self):
        t = fn("S *p", "    s32 x;\n\n    if (p->b)\n        x = p->a;\n    g(x);\n")
        got, d = run("hoist", t)
        self.assertEqual([p["label"] for p, _ in got], [])
        self.assertEqual(d["hoist:braceless-arm"], 1)

    def test_refuses_an_expression_naming_a_block_local(self):
        t = fn("S *p", "    s32 x;\n\n    {\n        s32 inner;\n        inner = p->a;\n"
                       "        x = inner + 1;\n    }\n    g(x);\n")
        got, d = run("hoist", t)
        self.assertNotIn("inner", " ".join(p["label"] for p, _ in got))
        self.assertGreaterEqual(d["hoist:names-a-block-local"], 1)

    def test_refuses_an_assignment_target_and_a_short_circuit_statement(self):
        t = fn("S *p, s32 n", "    s32 x;\n\n    p->a = n + 1;\n    x = (p->b != 0) && (n > 1);\n"
                              "    g(x);\n")
        got, d = run("hoist", t)
        self.assertEqual(d["hoist:stmt-has-shortcircuit"], 1)
        self.assertGreaterEqual(d["hoist:assignment-target"], 1)
        self.assertNotIn("p->a", " ".join(p["label"] for p, _ in got))

    def test_refuses_a_call_a_sideeffect_and_a_continuation_line(self):
        t = fn("S *p, s32 n",
               "    s32 x;\n\n    x = h(p->a) + n;\n    x = p->a + n++;\n"
               "    g(p,\n      x);\n")
        got, d = run("hoist", t)
        self.assertGreaterEqual(d["hoist:call-inside"], 1)
        self.assertGreaterEqual(d["hoist:incdec-inside"], 1)
        self.assertGreaterEqual(d["hoist:continuation-line"], 1)
        self.assertNotIn("h(p->a)", " ".join(p["label"] for p, _ in got))

    def test_refuses_a_declaration_statement(self):
        t = fn("S *p", "    s32 x = p->a;\n\n    g(x);\n")
        got, d = run("hoist", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["hoist:stmt-is-a-declaration"], 1)

    def test_refuses_a_volatile_subexpression(self):
        """`__typeof__` keeps the qualifier, so the temporary would be a volatile local."""
        t = fn("S *p", "    s32 x;\n\n    x = *(volatile s32 *)&p->a;\n    g(x);\n")
        got, d = run("hoist", t)
        self.assertEqual([pp["label"] for pp, _ in got], [])
        self.assertGreaterEqual(d["hoist:volatile-in-expr"], 1)

    def test_the_declaration_block_ends_at_the_first_statement(self):
        """`D_800CF828[0] = 1;` reads as a declaration of `F828` to varset's DECL_RE; the insertion
        point must still be the top of the body, not that line."""
        t = fn("S *p", "    s32 x;\n\n    x = p->a;\n    D_800CF828[0] = 1;\n    g(x);\n")
        got, d = run("hoist", t)
        self.assertTrue(got)
        cand = only("hoist", t, "hoist:member:p->a")
        lines = cand.split("\n")
        i = next(k for k, l in enumerate(lines) if "__typeof__" in l)
        j = next(k for k, l in enumerate(lines) if "D_800CF828" in l)
        self.assertLess(i, j)
        self.assertEqual(d["hoist:inside-the-declaration-block"], 0)

    def test_a_multi_line_declaration_ends_the_block(self):
        """`static void *const labels[] = {` runs on: the temporary must go ABOVE it."""
        t = fn("S *p", "    s32 x;\n    static void *const labels[] = {\n        &&a, &&b\n    };\n"
                       "\n    x = p->a;\n    g(x);\n    g(x);\n    g(x);\n    g(x);\n"
                       "    g(x);\na:\nb:\n    g(x);\n")
        cand = only("hoist", t, "hoist:member:p->a")
        lines = cand.split("\n")
        i = next(k for k, l in enumerate(lines) if "__typeof__" in l)
        j = next(k for k, l in enumerate(lines) if "static void" in l)
        self.assertLess(i, j)

    def test_an_arithmetic_span_is_only_unwrapped_when_it_is_one_pair(self):
        """`(a << 8) | (b & 0xFF)` starts and ends with a parenthesis without being one pair."""
        t = fn("s32 a, s32 b", "    s32 x;\n\n    x = 0;\n    x = (a << 8) | (b & 0xFF);\n    g(x);\n")
        for pp, cand in run("hoist", t)[0]:
            self.assertEqual(pp["expr"].count("("), pp["expr"].count(")"), pp["expr"])
            self.assertIn(pp["expr"], cand)

    def test_refuses_a_macro_argument_that_is_a_type_or_a_list(self):
        """`F(object, void **, 8)` passes a TYPE, and `G((a, b))` a list: neither is one value."""
        t = fn("S *p", "    s32 x;\n\n    x = 0;\n    x = F(p, void **, 8);\n    g(x);\n")
        got, d = run("hoist", t)
        self.assertNotIn("void **", " ".join(pp["expr"] for pp, _ in got))
        self.assertGreaterEqual(d["hoist:argument-is-a-type"], 1)

    def test_refuses_a_function_pointer_declaration(self):
        """`void (*cb)(void) = p->next;` is a declaration no declarator regex of varset matches."""
        t = fn("S *p", "    s32 x;\n\n    x = 0;\n    {\n"
                       "        void (*cb)(void) = p->next;\n        cb();\n    }\n    g(x);\n")
        got, d = run("hoist", t)
        self.assertNotIn("cb", " ".join(pp["label"] for pp, _ in got))
        self.assertGreaterEqual(d["hoist:stmt-is-a-declaration"], 1)

    def test_a_call_argument_keeps_the_spacing_of_the_line(self):
        t = fn("S *p, s32 n", "    s32 x;\n\n    x = 0;\n    g(n, p->a + n, x);\n")
        cands = [c for pp, c in run("hoist", t)[0] if pp["site"] == 10]
        self.assertTrue(cands)
        for c in cands:
            self.assertNotIn(",hoisted_1", c)


# --------------------------------------------------------------------------- retype_void

class RetypeVoid(unittest.TestCase):
    def test_a_local_pointer_is_declared_void_with_casts_at_its_uses(self):
        t = fn("void *q", "    S *p;\n    s32 x;\n\n    p = q;\n    x = p->a;\n"
                          "    p->b = 1;\n    g(p, x);\n")
        cand = only("retype_void", t, "retype_void:local:p")
        self.assertIn("    void *p;\n", cand)
        self.assertIn("x = ((S *)p)->a;", cand)
        self.assertIn("((S *)p)->b = 1;", cand)
        self.assertIn("p = q;", cand)                    # a bare assignment stays bare
        self.assertIn("g(p, x);", cand)                  # a bare argument stays bare

    def test_a_parameter_is_retyped_in_the_signature(self):
        t = fn("S *p", "    s32 x;\n\n    x = p->a;\n    g(x);\n")
        cand = only("retype_void", t, "retype_void:param:p")
        self.assertIn("void f(void *p)", cand)
        self.assertIn("x = ((S *)p)->a;", cand)

    def test_index_deref_and_arithmetic_uses_take_the_cast(self):
        t = fn("void *q, s32 n", "    S *p;\n    s32 x;\n\n    p = q;\n    x = p[n].a;\n"
                                 "    x = (*p).b;\n    p = p + 1;\n    g(x);\n")
        cand = only("retype_void", t, "retype_void:local:p")
        self.assertIn("x = ((S *)p)[n].a;", cand)
        self.assertIn("x = (*((S *)p)).b;", cand)
        self.assertIn("p = ((S *)p) + 1;", cand)

    def test_params_record_the_type_change(self):
        t = fn("S *p", "    s32 x;\n\n    x = p->a;\n    g(x);\n")
        params = next(p for p, _ in run("retype_void", t)[0])
        self.assertEqual((params["which"], params["var"], params["from"], params["to"]),
                         ("param", "p", "S *", "void *"))
        self.assertGreaterEqual(params["casts"], 1)

    # ---- must refuse

    def test_refuses_a_double_pointer(self):
        t = fn("S **pp", "    s32 x;\n\n    x = (*pp)->a;\n    g(x);\n")
        got, d = run("retype_void", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["retype_void:not-a-single-pointer"], 1)

    def test_refuses_an_address_taken_pointer(self):
        t = fn("void *q", "    S *p;\n    s32 x;\n\n    p = q;\n    h(&p);\n    x = p->a;\n    g(x);\n")
        got, d = run("retype_void", t)
        self.assertEqual([p["label"] for p, _ in got], [])
        self.assertGreaterEqual(d["address-taken"] + d["retype_void:address-taken"], 1)

    def test_refuses_a_pointer_increment_and_a_pointer_difference(self):
        t = fn("S *p, S *q", "    s32 x;\n\n    x = p->a;\n    p++;\n    x = p - q;\n    g(x);\n")
        got, d = run("retype_void", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["retype_void:pointer-incdec"], 1)

    def test_refuses_a_pointer_with_no_use_that_needs_the_type(self):
        t = fn("S *p", "    s32 x;\n\n    x = 1;\n    g(p, x);\n")
        got, d = run("retype_void", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["retype_void:no-use-needing-the-type"], 1)

    def test_refuses_an_untyped_or_byte_pointer(self):
        t = fn("u8 *p", "    s32 x;\n\n    x = p[2];\n    g(x);\n")
        got, d = run("retype_void", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["retype_void:already-untyped"], 1)


# --------------------------------------------------------------------------- split / merge

SPLIT_BASE = fn("s32 n", "    s32 t;\n    s32 x;\n    s32 y;\n\n    t = n + 1;\n    x = t;\n"
                         "    t = n + 2;\n    y = t;\n    g(x, y);\n")


class Split(unittest.TestCase):
    def test_a_second_lifetime_takes_a_fresh_name(self):
        got, _ = run("split", SPLIT_BASE)
        self.assertTrue(got)
        cand = got[0][1]
        self.assertIn("s32 t_2;", cand)
        self.assertIn("t_2 = n + 2;", cand)
        self.assertIn("y = t_2;", cand)
        self.assertIn("t = n + 1;", cand)

    def test_the_label_and_site_come_from_varset(self):
        params = run("split", SPLIT_BASE)[0][0][0]
        self.assertTrue(params["label"].startswith("split:split_def:"))
        self.assertEqual(params["move"], "split_def")
        self.assertGreaterEqual(params["site"], 1)

    def test_refuses_a_single_lifetime(self):
        t = fn("s32 n", "    s32 t;\n\n    t = n + 1;\n    g(t);\n")
        got, d = run("split", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["split:single-web"], 1)

    def test_refuses_an_address_taken_local(self):
        t = fn("s32 n", "    s32 t;\n    s32 x;\n\n    t = n + 1;\n    x = t;\n    h(&t);\n"
                        "    t = n + 2;\n    g(x, t);\n")
        got, d = run("split", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["address-taken"], 1)


class Merge(unittest.TestCase):
    MERGE_BASE = fn("s32 n", "    s32 a;\n    s32 b;\n\n    a = n + 1;\n    g(a);\n"
                             "    b = n + 2;\n    g(b);\n")

    def test_two_disjoint_locals_merge(self):
        got, _ = run("merge", self.MERGE_BASE)
        self.assertTrue(got)
        cands = [c for p, c in got if "merge_local" in p["label"]]
        self.assertTrue(cands)
        self.assertTrue(any("s32 b;" not in c or "s32 a;" not in c for c in cands))

    def test_params_say_which_varset_move_it_was(self):
        for params, _ in run("merge", self.MERGE_BASE)[0]:
            self.assertIn(params["which"], ("local", "param"))
            self.assertTrue(params["label"].startswith("merge:merge_"))

    def test_refuses_overlapping_live_ranges(self):
        t = fn("s32 n", "    s32 a;\n    s32 b;\n\n    a = n + 1;\n    b = n + 2;\n    g(a, b);\n")
        got, d = run("merge", t)
        self.assertEqual([p for p, _ in got if p["which"] == "local"], [])
        self.assertGreaterEqual(d["merge:live-ranges-overlap"], 1)

    def test_refuses_locals_of_different_types(self):
        t = fn("s32 n", "    s32 a;\n    s16 b;\n\n    a = n + 1;\n    g(a);\n    b = n + 2;\n"
                        "    g(b);\n")
        got, _ = run("merge", t)
        self.assertEqual([p for p, _ in got if "merge_local" in p["label"]], [])


# --------------------------------------------------------------------------- goto_to_loop

DO_LOOP = fn("s32 n", "    s32 i;\n\n    i = 0;\nloop:\n    g(i);\n    i = i + 1;\n"
                      "    if (i < n) {\n        goto loop;\n    }\n    h(i);\n")
DO_LOOP_1LINE = fn("s32 n", "    s32 i;\n\n    i = 0;\nloop:\n    g(i);\n    i = i + 1;\n"
                            "    if (i < n) goto loop;\n    h(i);\n")
WHILE_LOOP = fn("s32 n", "    s32 i;\n\n    i = 0;\ntop:\n    if (i < n) {\n        g(i);\n"
                         "        i = i + 1;\n        goto top;\n    }\n    h(i);\n")


class GotoToLoop(unittest.TestCase):
    def test_a_bottom_test_becomes_a_do_while(self):
        got, _ = run("goto_to_loop", DO_LOOP)
        self.assertEqual([p["label"] for p, _ in got], ["goto_to_loop:do_while:loop@10"])
        cand = got[0][1]
        self.assertIn("    do {\n", cand)
        self.assertIn("    } while (i < n);\n", cand)
        self.assertNotIn("goto loop", cand)
        self.assertNotIn("loop:", cand)
        self.assertIn("        g(i);\n".strip(), cand)
        self.assertEqual(got[0][0]["form"], "do_while")
        self.assertEqual(got[0][0]["cond"], "i < n")

    def test_the_one_line_terminator_is_the_same_move(self):
        got, _ = run("goto_to_loop", DO_LOOP_1LINE)
        self.assertEqual(len(got), 1)
        self.assertIn("} while (i < n);", got[0][1])

    def test_a_top_test_becomes_a_while(self):
        got, _ = run("goto_to_loop", WHILE_LOOP)
        self.assertEqual([p["form"] for p, _ in got], ["while"])
        cand = got[0][1]
        self.assertIn("    while (i < n) {\n", cand)
        self.assertNotIn("goto top", cand)
        self.assertNotIn("top:", cand)

    def test_a_labelled_block_body_is_recognised(self):
        t = fn("s32 n", "    s32 i;\n\n    i = 0;\nloop: {\n    g(i);\n    i = i + 1;\n    }\n"
                        "    if (i < n) goto loop;\n    h(i);\n")
        got, _ = run("goto_to_loop", t)
        self.assertEqual([p["form"] for p, _ in got], ["do_while"])
        self.assertIn("} while (i < n);", got[0][1])

    # ---- must refuse

    def test_refuses_a_label_with_two_gotos(self):
        t = fn("s32 n", "    s32 i;\n\n    i = 0;\n    if (n) {\n        goto loop;\n    }\nloop:\n"
                        "    g(i);\n    i = i + 1;\n    if (i < n) {\n        goto loop;\n    }\n"
                        "    h(i);\n")
        got, d = run("goto_to_loop", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["goto_to_loop:label-multi-goto"], 1)

    def test_refuses_a_body_that_declares_a_variable(self):
        t = fn("s32 n", "    s32 i;\n\n    i = 0;\nloop:\n    {\n        s32 tmp;\n"
                        "        tmp = i;\n        g(tmp);\n    }\n    i = i + 1;\n"
                        "    if (i < n) {\n        goto loop;\n    }\n    h(i);\n")
        got, d = run("goto_to_loop", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["goto_to_loop:body-declares"], 1)

    def test_refuses_a_body_with_break_or_continue(self):
        t = fn("s32 n", "    s32 i;\n\n    i = 0;\nloop:\n    while (n) {\n        break;\n    }\n"
                        "    i = i + 1;\n    if (i < n) {\n        goto loop;\n    }\n    h(i);\n")
        got, d = run("goto_to_loop", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["goto_to_loop:body-has-break-or-continue"], 1)

    def test_refuses_a_forward_goto_and_a_region_holding_a_label(self):
        t = fn("s32 n", "    s32 i;\n\n    i = 0;\n    goto done;\ndone:\n    h(i);\n")
        got, d = run("goto_to_loop", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["goto_to_loop:goto-from-outside"], 1)

    def test_refuses_a_top_test_with_an_else_arm(self):
        """`L: if (C) { A } else { B goto L; }` is not `while (C) { A }`."""
        t = fn("s32 n", "    s32 i;\n\n    i = 0;\ntop:\n    if (i < n) {\n        g(i);\n"
                        "    } else {\n        i = i + 1;\n        goto top;\n    }\n    h(i);\n")
        got, d = run("goto_to_loop", t)
        self.assertEqual([pp["form"] for pp, _ in got], [])
        self.assertGreaterEqual(d["goto_to_loop:top-test-has-an-else"], 1)

    def test_refuses_a_region_with_a_directive_line(self):
        t = fn("s32 n", "    s32 i;\n\n    i = 0;\nloop:\n#ifdef X\n    g(i);\n#endif\n"
                        "    i = i + 1;\n    if (i < n) {\n        goto loop;\n    }\n    h(i);\n")
        got, d = run("goto_to_loop", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["goto_to_loop:directive-in-region"], 1)


# --------------------------------------------------------------------------- real texts

class RealRows(unittest.TestCase):
    """Two registered pin-free rows: the module must enumerate without touching a directive line."""

    IDS = ("dungeon/func_7FFED7CC", "main/func_7FDD26A8")

    def test_no_instance_edits_a_preprocessor_line(self):
        for rid in self.IDS:
            p = ROOT / "src" / (rid + ".c")
            if not p.exists():
                self.skipTest("row %s is not in this tree" % rid)
            text = p.read_text(errors="replace")
            base = [l for l in text.split("\n") if l.lstrip().startswith("#")]
            for kind, f in P.PERTURBATIONS:
                for _, cand in f(text, P.Detail()):
                    self.assertEqual([l for l in cand.split("\n") if l.lstrip().startswith("#")],
                                     base, "%s changed a directive line in %s" % (kind, rid))

    def test_the_goto_loop_of_a_real_row(self):
        p = ROOT / "src/dungeon/func_7FFED7CC.c"
        if not p.exists():
            self.skipTest("row is not in this tree")
        got, _ = run("goto_to_loop", p.read_text(errors="replace"))
        self.assertEqual(len(got), 1)
        self.assertEqual(got[0][0]["form"], "do_while")
        self.assertIn("} while (*value_ptr != 0);", got[0][1])


# --------------------------------------------------------------------------- the review's defects

class ReviewFixes(unittest.TestCase):
    """The round-33 adversarial review's six findings, each at the reviewer's own definition.

    Every text below is the reviewer's, or the row's line they named, reduced to the smallest
    synthetic that carries it; each finding has a must-REFUSE and, where refusing could over-fire, a
    must-ACCEPT beside it.
    """

    # ---- (1) a memory read moved across a call

    def test_refuses_a_memory_read_hoisted_across_a_call(self):
        """`x = h(n) + p->a;` - the load would leave its place after the `jal`."""
        t = fn("S *p, s32 n", "    s32 x;\n\n    x = h(n) + p->a;\n    g(x);\n")
        got, d = run("hoist", t)
        self.assertEqual([pp["label"] for pp, _ in got], [])
        self.assertGreaterEqual(d["hoist:call-in-statement"], 1)

    def test_refuses_a_memory_read_beside_a_sibling_call_argument(self):
        """`g(h(), p->a)`: the calls' argument order is unspecified, so the read still crosses one."""
        t = fn("S *p, s32 n", "    s32 x;\n\n    x = 0;\n    g(h(n), p->a);\n    g(x);\n")
        got, d = run("hoist", t)
        self.assertNotIn("p->a", " ".join(pp["expr"] for pp, _ in got))
        self.assertGreaterEqual(d["hoist:call-in-statement"], 1)

    def test_accepts_a_read_inside_the_only_calls_own_argument(self):
        """The must-ACCEPT beside it: `g(p->a + n)` moves the read out but still BEFORE the call."""
        t = fn("S *p, s32 n", "    s32 x;\n\n    x = 0;\n    g(p->a + n);\n    g(x);\n")
        got, d = run("hoist", t)
        self.assertIn("p->a", " ".join(pp["expr"] for pp, _ in got))
        self.assertEqual(d["hoist:call-in-statement"], 0)

    def test_refuses_a_memory_read_beside_an_INDIRECT_call(self):
        """`varset.CALL_RE` is a NAME then `(`; a call through a table or a pointer is a call too."""
        t = fn("S *p, s32 i", "    s32 x;\n\n    x = 0;\n    x = D_800294B8[i](i) + p->a;\n"
                              "    g(x);\n")
        got, d = run("hoist", t)
        self.assertNotIn("p->a", " ".join(pp["expr"] for pp, _ in got))
        self.assertGreaterEqual(d["hoist:call-in-statement"], 1)

    def test_an_indirect_calls_own_argument_is_still_hoisted(self):
        t = fn("S *p, s32 i", "    s32 x;\n\n    x = 0;\n    D_800294B8[i](p->a + i);\n    g(x);\n")
        got, _ = run("hoist", t)
        self.assertIn("p->a", " ".join(pp["expr"] for pp, _ in got))

    def test_a_cast_is_not_read_as_an_indirect_call(self):
        t = fn("S *p, s32 y", "    s32 x;\n\n    x = 0;\n    x = (s32)(y + 1) + p->a;\n    g(x);\n")
        got, d = run("hoist", t)
        self.assertIn("p->a", " ".join(pp["expr"] for pp, _ in got))
        self.assertEqual(d["hoist:call-in-statement"], 0)

    def test_a_local_only_computation_may_cross_a_call(self):
        """`flags & ~0x20000` reads no memory: a call cannot disturb it (the reviewer's own 69)."""
        t = fn("s32 n", "    s32 x;\n    s32 flags;\n\n    flags = 1;\n"
                        "    x = h(n) + (flags & 0x20);\n    g(x);\n")
        got, _ = run("hoist", t)
        self.assertIn("flags & 0x20", " ".join(pp["expr"] for pp, _ in got))

    # ---- (2) a pinned text

    PINNED = ('#include "common.h"\n\nvoid f(s32 n)\n{\n    s32 a;\n    s32 b;\n\n'
              '    a = n + 1;\n    ASM_KEEP(a);\n    g(a);\n    b = n + 2;\n    ASM_KEEP(b);\n'
              '    g(b);\n}\n')
    REGPIN = ('#include "common.h"\n\nvoid f(s32 n)\n{\n    register s32 x ASM_REG("a2");\n'
              '    s32 y;\n\n    y = n + 1;\n    g(y);\n    x = y + 2;\n    g(x);\n}\n')

    def test_no_kind_perturbs_a_text_holding_a_pin(self):
        for text in (self.PINNED, self.REGPIN):
            for kind, f in P.PERTURBATIONS:
                d = P.Detail()
                self.assertEqual(f(text, d), [], "%s perturbed a pinned text" % kind)
                self.assertEqual(d["%s:text-is-pinned" % kind], 1)

    def test_an_asm_reg_without_the_register_keyword_still_refuses(self):
        """`sites_of` wants the `register` keyword; the masked-text test is wider on purpose."""
        t = self.REGPIN.replace("register s32 x", "s32 x")
        for kind, f in P.PERTURBATIONS:
            self.assertEqual(f(t, P.Detail()), [], kind)

    def test_the_unresolved_pin_comment_of_a_population_row_is_not_a_pin(self):
        """39 population rows carry `/* UNRESOLVED C shape (pin): ... */` and are not pinned.

        The gate is `sites_of` plus `PIN_TEXT` on the MASKED text, so a comment SAYING pin does not
        refuse the row.  (A comment quoting a whole `ASM_KEEP(x);` would: `sites_of` reads it as a
        site on the raw text, and the driver's population rule reads the same function, so the two
        agree - which is the property that matters.)
        """
        t = fn("S *p", "    s32 x;\n\n    /* UNRESOLVED C shape (pin): a register lived here */\n"
                       "    x = p->a;\n    g(x);\n")
        self.assertTrue(run("hoist", t)[0])

    # ---- (3) an aggregate-valued temporary

    AGG = ('#include "common.h"\n\ntypedef struct { s16 v; } V;\n'
           'typedef struct { V at02; u8 pad[4]; V list[2]; V *ptr; s32 n; } U;\n'
           'typedef struct { U unk_00; } M;\n\n'
           'void f(M *motion)\n{\n    s16 axis_pos;\n\n    axis_pos = motion->unk_00.at02.v;\n'
           '    g(axis_pos);\n}\n')

    def test_refuses_an_aggregate_prefix_on_the_read_side(self):
        got, d = run("hoist", self.AGG)
        for pp, _ in got:
            self.assertNotIn("at02;", pp["expr"] + ";")     # never the struct-valued prefix
            self.assertFalse(pp["expr"].endswith("at02"))
        self.assertGreaterEqual(d["hoist:aggregate-prefix"], 1)

    def test_refuses_a_full_chain_whose_last_member_is_an_aggregate(self):
        """`dst->words = src->words;` - `__typeof__` is right and the copy is a block copy."""
        t = ('#include "common.h"\n\ntypedef struct { u32 words[4]; s32 n; } W;\n\n'
             'void f(W *dst, W *src)\n{\n    dst->words = src->words;\n    g(dst->n);\n}\n')
        got, d = run("hoist", t)
        self.assertNotIn("words", " ".join(pp["expr"] for pp, _ in got))
        self.assertGreaterEqual(d["hoist:aggregate-member"], 1)

    def test_refuses_an_index_whose_element_is_an_aggregate(self):
        """`tmp = u->ptr[i];` is a struct copy; `u->list[i]` as a PREFIX is the same class."""
        t = ('#include "common.h"\n\ntypedef struct { s16 v; } V;\n'
             'typedef struct { V list[2]; V *ptr; s32 n; } U;\n\n'
             'void f(U *u, s32 i)\n{\n    V tmp;\n    s32 x;\n\n    tmp = u->ptr[i];\n'
             '    x = u->list[i].v;\n    g(x);\n}\n')
        got, d = run("hoist", t)
        for pp, _ in got:
            self.assertFalse(pp["expr"].endswith("]"), pp["expr"])
        self.assertGreaterEqual(d["hoist:aggregate-element"], 1)
        self.assertGreaterEqual(d["hoist:aggregate-prefix"], 1)

    def test_a_scalar_member_is_still_hoisted(self):
        """The must-ACCEPT: the aggregate rule may not swallow the ordinary member load."""
        got, _ = run("hoist", self.AGG)
        self.assertIn("motion->unk_00.at02.v", " ".join(pp["expr"] for pp, _ in got))

    # ---- (4) sizeof

    def test_refuses_sizeof(self):
        """`hoisted_1 = sizeof(entries);` made gcc's inline block copy a real `jal memcpy`."""
        t = fn("void", "    u8 entries[6];\n\n    memcpy(entries, D_80089260, sizeof(entries));\n")
        got, d = run("hoist", t)
        self.assertNotIn("sizeof", " ".join(pp["label"] for pp, _ in got))
        self.assertGreaterEqual(d["hoist:sizeof-in-expr"], 1)

    # ---- (5) the dropped storage class

    def test_retype_void_keeps_a_static_storage_class(self):
        t = fn("void", "    static S *p;\n\n    p = D_80089260;\n    g(p->a);\n")
        got = run("retype_void", t)[0]
        # this HEAD never writes `u8`, so round 33's offset-load spelling refuses it and only the
        # cast spelling is enumerated; both must keep the storage class
        self.assertEqual(sorted(p.get("spelling", "cast") for p, _ in got), ["cast"])
        for _, cand in got:
            self.assertIn("static void *p;", cand)
        t2 = t.replace("typedef struct S {", "typedef u8 byte;\ntypedef struct S {")
        self.assertEqual(sorted(p.get("spelling", "cast") for p, _ in run("retype_void", t2)[0]),
                         ["cast", "offset_load"])
        for _, cand in run("retype_void", t2)[0]:
            self.assertIn("static void *p;", cand)

    # ---- (6) a loop body that declares a POINTER

    def test_goto_to_loop_refuses_a_body_declaring_a_pointer(self):
        t = fn("S *base, s32 n", "    s32 i;\n\n    i = 0;\nloop:\n    {\n        S *q;\n"
                                 "        s32 *dst;\n\n        q = base + i;\n        dst = &n;\n"
                                 "        q->a = *dst;\n    }\n    i = i + 1;\n"
                                 "    if (i < n) {\n        goto loop;\n    }\n    h(i);\n")
        got, d = run("goto_to_loop", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["goto_to_loop:body-declares"], 1)

    def test_goto_to_loop_still_accepts_a_body_with_a_multiplication(self):
        """A BARE `count * scale;` has a declaration's exact shape; `_is_typename` tells them apart.

        (The statement must start at the line's left edge for `DECL_LINE` to reach it at all, so the
        test uses the bare expression statement, not `g(count * scale);` - a call could never match
        the anchored pattern and would prove nothing.)
        """
        t = fn("s32 n", "    s32 i;\n    s32 count;\n    s32 scale;\n\n    i = 0;\n    count = 2;\n"
                        "    scale = 3;\nloop:\n    count * scale;\n    i = i + 1;\n"
                        "    if (i < n) {\n        goto loop;\n    }\n    h(i);\n")
        got, d = run("goto_to_loop", t)
        self.assertEqual([pp["form"] for pp, _ in got], ["do_while"])
        self.assertEqual(d["goto_to_loop:body-declares"], 0)
        # and the gate does fire on the same shape when the base IS a type name
        t2 = t.replace("    count * scale;", "    S *scale2;")
        self.assertEqual(run("goto_to_loop", t2)[0], [])


# --------------------------------------------------------------------------- round 33 widening D
#
# Implementer D's two openings of `goto_to_loop`, the two new kinds `tail_merge` / `dup_tail` /
# `cond_temp`, `merge` with `allow_init=True`, and `retype_void`'s offset-load spelling.  Each
# carries the move and at least TWO cases it must refuse.

# t41's OWN landed spelling: the closing brace of the label's block and the backward test on ONE
# line.  Before the opening, `goto_to_loop:no-terminator` on 14 of 14 t41 / t41c / t44 oracle rows.
T41_LANDED = fn("s32 n", "    s32 i;\n\n    i = 0;\n    loop_0: {\n        g(i);\n"
                         "        i = i + 1;\n    } if (i < n) goto loop_0;\n    h(i);\n")

# the same, with a declaration in the braced body (dungeon/func_8008F15C `u32 slot_base;`)
T41_LANDED_DECL = fn("s32 n", "    s32 i;\n\n    i = 0;\n    loop_0: {\n        s32 tmp;\n"
                              "        tmp = i;\n        g(tmp);\n        i = i + 1;\n"
                              "    } if (i < n) goto loop_0;\n    h(i);\n")


class GotoToLoopLandedSpelling(unittest.TestCase):
    def test_the_terminator_may_share_the_closing_brace_line(self):
        got, d = run("goto_to_loop", T41_LANDED)
        self.assertEqual([p["label"] for p, _ in got], ["goto_to_loop:do_while:loop_0@10"])
        cand = got[0][1]
        self.assertIn("    do {\n", cand)
        self.assertIn("    } while (i < n);\n", cand)
        self.assertNotIn("loop_0", cand)
        self.assertNotIn("goto", cand)
        self.assertEqual(d["goto_to_loop:no-terminator"], 0)
        # the body survives whole and in order
        self.assertIn("        g(i);\n        i = i + 1;\n", cand)

    def test_a_braced_label_may_declare_in_its_body(self):
        got, d = run("goto_to_loop", T41_LANDED_DECL)
        self.assertEqual([p["form"] for p, _ in got], ["do_while"])
        self.assertEqual(d["goto_to_loop:body-declares"], 0)
        cand = got[0][1]
        self.assertIn("    do {\n        s32 tmp;\n", cand)      # still inside the same block
        self.assertIn("    } while (i < n);\n", cand)

    # ---- must refuse

    def test_an_UNBRACED_body_that_declares_is_still_refused(self):
        """The relaxation is the label's own brace, not "a loop body may declare"."""
        t = fn("s32 n", "    s32 i;\n\n    i = 0;\nloop_0:\n    s32 tmp;\n    tmp = i;\n"
                        "    g(tmp);\n    i = i + 1;\n    if (i < n) goto loop_0;\n    h(i);\n")
        got, d = run("goto_to_loop", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["goto_to_loop:body-declares"], 1)

    def test_a_braced_body_with_break_is_still_refused(self):
        t = fn("s32 n", "    s32 i;\n\n    i = 0;\n    loop_0: {\n        while (n) {\n"
                        "            break;\n        }\n        i = i + 1;\n"
                        "    } if (i < n) goto loop_0;\n    h(i);\n")
        got, d = run("goto_to_loop", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["goto_to_loop:body-has-break-or-continue"], 1)

    def test_a_one_line_terminator_for_ANOTHER_label_is_not_a_terminator(self):
        """`} if (c) goto skip;` with the REAL backward goto on the next line.

        The old scan read the first non-blank line BELOW the closing brace as the terminator and
        `_loop_text` then deleted every line from the label to it - the `goto skip;` statement
        sharing the brace line included.  The close must be a bare `}` for that path.
        """
        t = fn("s32 n", "    s32 i;\n\n    i = 0;\n    loop_0: {\n        g(i);\n"
                        "        i = i + 1;\n    } if (i > n) goto skip;\n"
                        "    if (i < n) goto loop_0;\nskip:\n    h(i);\n")
        got, d = run("goto_to_loop", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["goto_to_loop:label-block-close-has-a-statement"], 1)

    def test_a_trailing_statement_after_the_goto_is_not_a_terminator(self):
        """`} if (c) goto L; x = 1;` - the regex must END at the `;`, or the `x = 1;` is swallowed."""
        t = fn("s32 n", "    s32 i;\n\n    i = 0;\n    loop_0: {\n        g(i);\n"
                        "        i = i + 1;\n    } if (i < n) goto loop_0; i = 0;\n    h(i);\n")
        got, d = run("goto_to_loop", t)
        self.assertEqual(got, [])
        # the same-line pattern does not match (it is anchored at the `;`), and the close is then
        # not a bare `}` either, so the second guard catches it and nothing is deleted
        self.assertGreaterEqual(d["goto_to_loop:label-block-close-has-a-statement"], 1)


# --------------------------------------------------------------------------- tail_merge

BOTH_ARMS = fn("s32 n", "    s32 x;\n\n    if (n) {\n        x = 1;\n        g(x);\n"
                        "    } else {\n        x = 2;\n        g(x);\n    }\n    h(x);\n")


class TailMerge(unittest.TestCase):
    def test_the_common_tail_is_hoisted_out_of_both_arms(self):
        got, _ = run("tail_merge", BOTH_ARMS)
        self.assertEqual([p["n_tail"] for p, _ in got], [1])
        cand = got[0][1]
        self.assertEqual(cand.count("g(x);"), 1)
        self.assertIn("    if (n) {\n        x = 1;\n    } else {\n        x = 2;\n    }\n"
                      "    g(x);\n", cand)
        self.assertFalse(got[0][0]["dropped_else"])

    def test_an_emptied_else_arm_is_dropped(self):
        """dup_after_if's own inverse: `if (c) { A; s } else { s }` -> `if (c) { A } s;`."""
        t = fn("s32 n", "    s32 x;\n\n    if (n) {\n        g(n);\n        x = 1;\n"
                        "    } else {\n        x = 1;\n    }\n    h(x);\n")
        got, _ = run("tail_merge", t)
        self.assertEqual(len(got), 1)
        cand = got[0][1]
        self.assertTrue(got[0][0]["dropped_else"])
        self.assertNotIn("else", cand)
        self.assertIn("    if (n) {\n        g(n);\n    }\n    x = 1;\n", cand)

    def test_a_longer_tail_and_its_shorter_prefix_are_both_enumerated(self):
        t = fn("s32 n", "    s32 x;\n\n    if (n) {\n        x = 1;\n        g(x);\n"
                        "        h(x);\n    } else {\n        x = 2;\n        g(x);\n"
                        "        h(x);\n    }\n    h(0);\n")
        got, _ = run("tail_merge", t)
        self.assertEqual(sorted(p["n_tail"] for p, _ in got), [1, 2])

    # ---- must refuse

    def test_refuses_an_if_with_no_else(self):
        t = fn("s32 n", "    s32 x;\n\n    if (n) {\n        x = 1;\n        g(x);\n    }\n"
                        "    h(x);\n")
        got, d = run("tail_merge", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["tail_merge:no-else"], 1)

    def test_refuses_a_jump_before_the_tail(self):
        """`if (c) { return; s } else { s }` - the tail is DEAD in the if arm."""
        t = fn("s32 n", "    s32 x;\n\n    if (n) {\n        x = 1;\n        return;\n"
                        "        g(x);\n    } else {\n        x = 2;\n        g(x);\n    }\n"
                        "    h(x);\n")
        got, d = run("tail_merge", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["tail_merge:jump-before-the-tail"], 1)

    def test_refuses_an_else_if_chain_and_an_emptied_IF_arm(self):
        t = fn("s32 n", "    s32 x;\n\n    if (n) {\n        x = 1;\n        g(x);\n"
                        "    } else if (n == 2) {\n        x = 2;\n        g(x);\n    }\n"
                        "    h(x);\n")
        got, d = run("tail_merge", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["tail_merge:else-if"], 1)
        t2 = fn("s32 n", "    s32 x;\n\n    if (n) {\n        g(x);\n    } else {\n"
                         "        x = 2;\n        g(x);\n    }\n    h(x);\n")
        got2, d2 = run("tail_merge", t2)
        self.assertEqual(got2, [])
        self.assertGreaterEqual(d2["tail_merge:if-arm-empties"], 1)

    def test_refuses_a_tail_that_is_not_a_simple_statement(self):
        """A nested block's closing brace is not "the arm's tail": pulling it out changes scope."""
        t = fn("s32 n", "    s32 x;\n\n    if (n) {\n        x = 1;\n        if (x) {\n"
                        "            g(x);\n        }\n    } else {\n        x = 2;\n"
                        "        if (x) {\n            g(x);\n        }\n    }\n    h(x);\n")
        got, d = run("tail_merge", t)
        self.assertEqual([p["label"].split(":")[1] for p, _ in got], [])
        self.assertGreaterEqual(d["tail_merge:tail-not-a-simple-statement"]
                                + d["tail_merge:no-common-tail"], 1)


# --------------------------------------------------------------------------- dup_tail

class DupTail(unittest.TestCase):
    def test_the_statement_after_an_if_is_written_into_both_arms(self):
        t = fn("s32 n", "    s32 x;\n\n    if (n) {\n        x = 1;\n    }\n    g(x);\n"
                        "    h(x);\n")
        got, _ = run("dup_tail", t)
        self.assertEqual(len(got), 1)
        cand = got[0][1]
        self.assertEqual(cand.count("g(x);"), 2)
        self.assertIn("    if (n) {\n        x = 1;\n        g(x);\n    } else {\n"
                      "        g(x);\n    }\n", cand)

    # ---- must refuse

    def test_refuses_a_brace_that_does_not_close_an_if(self):
        """`} else {` after a LOOP's brace does not compile; the generator's own scan cannot see it."""
        t = fn("s32 n", "    s32 x;\n\n    x = 0;\n    while (n) {\n        x = 1;\n    }\n"
                        "    g(x);\n")
        got, d = run("dup_tail", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["dup_tail:brace-does-not-close-an-if"], 1)

    def test_refuses_an_else_and_a_declaration_after_the_brace(self):
        # the generator's `IF_RE` is a BARE `}` line, so `next-line-is-else` needs the brace and
        # the `else` on separate lines - the style m2c never writes, which is why it is silent
        t = fn("s32 n", "    s32 x;\n\n    if (n) {\n        x = 1;\n    }\n    else {\n"
                        "        x = 2;\n    }\n    h(x);\n")
        _, d = run("dup_tail", t)
        self.assertGreaterEqual(d["dup_tail:next-line-is-else"], 1)
        t2 = fn("s32 n", "    s32 x;\n\n    if (n) {\n        x = 1;\n    }\n    {\n"
                         "        s32 y;\n        y = x;\n        g(y);\n    }\n")
        got2, d2 = run("dup_tail", t2)
        self.assertEqual(got2, [])
        self.assertGreaterEqual(d2["dup_tail:next-line-not-a-simple-statement"], 1)


# --------------------------------------------------------------------------- cond_temp

class CondTemp(unittest.TestCase):
    def test_the_whole_condition_is_computed_into_a_temporary(self):
        t = fn("S *p", "    s32 x;\n\n    x = 0;\n    if (p->a + 1) {\n        x = 1;\n    }\n"
                       "    g(x);\n")
        got, _ = run("cond_temp", t)
        cand = [c for p, c in got if p["expr_class"] == "whole"]
        self.assertEqual(len(cand), 1)
        self.assertIn("    __typeof__(p->a + 1) cond_1;\n", cand[0])
        self.assertIn("    cond_1 = p->a + 1;\n    if (cond_1) {\n", cand[0])

    def test_one_operand_may_be_taken_instead(self):
        t = fn("S *p, s32 n", "    s32 x;\n\n    x = 0;\n    if (p->a < n) {\n        x = 1;\n"
                              "    }\n    g(x);\n")
        got, _ = run("cond_temp", t)
        self.assertIn("p->a", [p["expr"] for p, _ in got])
        cand = [c for p, c in got if p["expr"] == "p->a"][0]
        self.assertIn("    cond_1 = p->a;\n    if (cond_1 < n) {\n", cand)

    def test_a_full_cast_spells_the_temporarys_type(self):
        """m2c declares `s32 temp;`; a `__typeof__` temporary can never equal that declaration.

        `_temp_type` is unit-tested directly because the span scanner does not offer a bare cast as
        an operand today (`((s32)(D_800FE508[1]))` holds no top-level operator, so `_paren_spans`
        passes it over) - the spelling rule is what this test is about, not the span menu.
        """
        self.assertEqual(P._temp_type("((s32)(D_800FE508[1]))", None, ())[1], "cast")
        self.assertEqual(P._temp_type("((s32)(D_800FE508[1]))", None, ())[0], "s32")
        self.assertEqual(P._temp_type("(S *)q", None, ("S",))[0], "S *")
        self.assertEqual(P._temp_type("p->a + 1", None, ())[1], "typeof")
        self.assertEqual(P._temp_type("(void *)q", None, ())[1], "typeof")   # `void` is not a temp
        # the cast must COVER the expression: `(s16)a + b` is an `int`, and `s16 t = ...` truncates
        self.assertEqual(P._temp_type("(s16)a + b", None, ())[1], "typeof")
        self.assertEqual(P._temp_type("(s8 *)entry - 2", None, ())[1], "typeof")
        self.assertEqual(P._temp_type("(s16) counter == 6", None, ())[1], "typeof")
        self.assertEqual(P._temp_type("(u16)first_value", None, ())[0], "u16")   # covered
        self.assertEqual(P._temp_type("(S *)p->next", None, ("S",))[0], "S *")   # `->` is not an op
        t = fn("s32 n", "    s32 x;\n\n    x = 0;\n    if (((s32)(D_800FE508[1])) < n) {\n"
                        "        x = 1;\n    }\n    g(x);\n")
        got, _ = run("cond_temp", t)
        self.assertEqual(len([1 for p, _ in got if p["expr_class"] == "whole"]), 1)

    # ---- must refuse

    def test_refuses_a_while_and_a_for_condition(self):
        t = fn("S *p", "    s32 x;\n\n    x = 0;\n    while (p->a) {\n        x = 1;\n    }\n"
                       "    g(x);\n")
        got, d = run("cond_temp", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["cond_temp:loop-condition-re-evaluated"], 1)
        t2 = fn("S *p", "    s32 x;\n\n    x = 0;\n    for (x = 0; p->a; x = x + 1) {\n"
                        "        g(x);\n    }\n")
        got2, d2 = run("cond_temp", t2)
        self.assertEqual(got2, [])
        self.assertGreaterEqual(d2["cond_temp:loop-condition-re-evaluated"], 1)

    def test_refuses_a_short_circuit_condition_and_an_else_if(self):
        t = fn("S *p, s32 n", "    s32 x;\n\n    x = 0;\n    if (p != 0 && p->a < n) {\n"
                              "        x = 1;\n    }\n    g(x);\n")
        got, d = run("cond_temp", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["cond_temp:shortcircuit-in-condition"], 1)
        t2 = fn("S *p, s32 n", "    s32 x;\n\n    x = 0;\n    if (n) {\n        x = 1;\n"
                               "    } else if (p->a < n) {\n        x = 2;\n    }\n    g(x);\n")
        _, d2 = run("cond_temp", t2)
        self.assertGreaterEqual(d2["cond_temp:else-if"], 1)

    def test_refuses_a_call_in_the_condition_beside_a_memory_read(self):
        t = fn("S *p", "    s32 x;\n\n    x = 0;\n    if (g(0) != p->a) {\n        x = 1;\n"
                       "    }\n    h(x);\n")
        got, d = run("cond_temp", t)
        self.assertEqual([p["expr"] for p, _ in got], [])
        self.assertGreaterEqual(d["cond_temp:call-in-condition"] + d["hoist:call-inside"], 1)


# --------------------------------------------------------------------------- merge --allow-init

class MergeAllowInit(unittest.TestCase):
    def test_an_initialised_typed_alias_is_now_a_merge_candidate(self):
        """`S *alias = obj;` used and then dead; merging `alias` into `obj` drops the alias line."""
        # m2c's own shape: the alias is initialised from a PARAMETER (a local host cannot be
        # assigned above a C89 declaration), so the move is `merge_param`
        t = fn("S *obj", "    S *alias = obj;\n\n    alias->a = 1;\n    g(alias->b);\n")
        got, d = run("merge", t)
        self.assertIn("merge:merge_param:alias>obj", [p["label"] for p, _ in got])
        cand = [c for p, c in got if p["label"] == "merge:merge_param:alias>obj"][0]
        self.assertNotIn("alias", cand)
        self.assertIn("    obj->a = 1;\n", cand)
        self.assertEqual(d["initialised-decl"], 0)

    # ---- must refuse

    def test_refuses_a_guest_whose_initialiser_is_lost(self):
        """`T g = X;` merged into h DROPS the line, so the definition `g = X` disappears."""
        t = fn("s32 n", "    s32 a = n + 1;\n    s32 b;\n\n    g(a);\n    b = 2;\n    g(b);\n")
        got, d = run("merge", t)
        self.assertNotIn("merge:merge_local:a>b", [p["label"] for p, _ in got])
        self.assertGreaterEqual(d["merge:init-lost"], 1)

    def test_refuses_a_candidate_that_initialises_a_declaration_from_itself(self):
        """The direction that renames the READ inside the host's own initialiser: `s32 b = b;`."""
        t = fn("s32 n", "    s32 a;\n    s32 b = a;\n\n    g(b);\n    h(n);\n")
        got, d = run("merge", t)
        for _, cand in got:
            self.assertNotIn("b = b;", cand)
            self.assertNotIn("a = a;", cand)
        self.assertGreaterEqual(d["merge:self-initialised-declaration"], 1)

    def test_the_default_of_the_varset_entry_points_is_unchanged(self):
        import varset as VS
        import inspect
        for f in (VS.merge_local_candidates, VS.merge_param_candidates):
            self.assertEqual(inspect.signature(f).parameters["allow_init"].default, False)
        t = fn("S *obj", "    S *alias = obj;\n\n    alias->a = 1;\n    g(alias->b);\n")
        self.assertEqual(VS.merge_param_candidates(t), [])
        self.assertNotEqual(VS.merge_param_candidates(t, allow_init=True), [])


# --------------------------------------------------------------------------- retype_void offsets

OFF_HEAD = ('#include "common.h"\n\n'
            'typedef struct S_1 {\n    u8 pad_00[0xC];\n    s32 unk_0C;\n    u8 pad_10[0x2];\n'
            '    u16 unk_12;\n} S_1;\n\n')


class RetypeVoidOffset(unittest.TestCase):
    def test_a_member_use_becomes_an_offset_load(self):
        t = fn("void *arg", "    S_1 *p;\n\n    p = arg;\n    p->unk_0C = 1;\n    g(p->unk_12);\n",
               head=OFF_HEAD)
        got, _ = run("retype_void", t)
        off = [(p, c) for p, c in got if p.get("spelling") == "offset_load"]
        self.assertEqual(len(off), 1)
        cand = off[0][1]
        self.assertIn("    void *p;\n", cand)
        self.assertIn("    *(s32 *)((u8 *)p + 0xC) = 1;\n", cand)
        self.assertIn("    g(*(u16 *)((u8 *)p + 0x12));\n", cand)
        self.assertEqual(off[0][0]["casts"], 2)

    def test_the_offset_walk_cross_checks_the_unk_name(self):
        """A typedef whose padding does not put `unk_XX` at 0xXX is not read at all."""
        bad = OFF_HEAD.replace("u8 pad_00[0xC];", "u8 pad_00[0x8];")
        t = fn("void *arg", "    S_1 *p;\n\n    p = arg;\n    p->unk_0C = 1;\n", head=bad)
        got, d = run("retype_void", t)
        self.assertEqual([p for p, _ in got if p.get("spelling") == "offset_load"], [])
        self.assertGreaterEqual(d["retype_void:offset:typedef-not-readable"], 1)

    # ---- must refuse

    def test_refuses_a_chained_member_use(self):
        head = OFF_HEAD.replace("s32 unk_0C;", "S_1 *unk_0C;")
        t = fn("void *arg", "    S_1 *p;\n\n    p = arg;\n    p->unk_0C->unk_12 = 1;\n", head=head)
        got, d = run("retype_void", t)
        self.assertEqual([p for p, _ in got if p.get("spelling") == "offset_load"], [])
        self.assertGreaterEqual(d["retype_void:offset:member-use-is-a-chain"], 1)

    def test_refuses_an_indexed_use_and_a_member_the_typedef_lacks(self):
        t = fn("void *arg", "    S_1 *p;\n\n    p = arg;\n    p[1].unk_0C = 1;\n", head=OFF_HEAD)
        got, d = run("retype_void", t)
        self.assertEqual([p for p, _ in got if p.get("spelling") == "offset_load"], [])
        self.assertGreaterEqual(d["retype_void:offset:use-is-not-a-member"], 1)
        t2 = fn("void *arg", "    S_1 *p;\n\n    p = arg;\n    p->unk_40 = 1;\n", head=OFF_HEAD)
        got2, d2 = run("retype_void", t2)
        self.assertEqual([p for p, _ in got2 if p.get("spelling") == "offset_load"], [])
        self.assertGreaterEqual(d2["retype_void:offset:member-not-in-the-typedef"], 1)


# --------------------------------------------------------------------------- the compile's findings
#
# The whole-population run of implementer D's kinds compiled 16,398 instances and named three
# defects by their NOBUILD records.  Each test below FAILS on the code as it stood before its fix
# and carries the population row that found it.

class WholePopulationNobuilds(unittest.TestCase):
    def test_tail_merge_refuses_a_continuation_line_as_the_tail(self):
        """dungeon/func_800A4710: `                  sprite->unk_04);` ends in `;` and `movable`
        called it a statement, so a FRAGMENT of a multi-line call was hoisted out of both arms."""
        t = fn("S *p, s32 n", "    s32 x;\n\n    if (n) {\n        x = 1;\n        g(p->a,\n"
                              "          p->b);\n    } else {\n        x = 2;\n        g(p->a,\n"
                              "          p->b);\n    }\n    h(x);\n")
        got, d = run("tail_merge", t)
        for p, cand in got:
            self.assertNotIn("p->b);\n    h", cand)
        self.assertGreaterEqual(d["tail_merge:tail-is-a-continuation-line"], 1)

    def test_tail_merge_refuses_a_tail_that_reads_a_local_declared_in_the_arm(self):
        """town/func_800B361C: the tail leaves the block where `branch_flags` is declared."""
        t = fn("S *p, s32 n", "    if (n) {\n        s32 branch_flags;\n\n"
                              "        branch_flags = p->a;\n        p->b = branch_flags;\n"
                              "    } else {\n        s32 branch_flags;\n\n"
                              "        branch_flags = 0;\n        p->b = branch_flags;\n    }\n"
                              "    h(n);\n")
        got, d = run("tail_merge", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["tail_merge:tail-reads-an-arm-local"], 1)

    def test_dup_tail_refuses_the_brace_that_closes_an_ELSE_arm(self):
        """main/func_80012030: `} else { .. }` + stmt gave `} else { .. stmt } else { stmt }`.

        `} else {` nets ZERO braces, so a scan that only looks for a brace-opening head one level
        up walks straight past it and names the `if` as the closing brace's owner.
        """
        t = fn("s32 n", "    s32 x;\n\n    if (n) {\n        x = 1;\n    } else {\n"
                        "        x = 2;\n    }\n    g(x);\n")
        got, d = run("dup_tail", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["dup_tail:brace-does-not-close-an-if"], 1)

    def test_dup_tail_still_accepts_the_brace_of_an_if_with_no_else(self):
        """The same walk must not become blind: the honest shape still enumerates."""
        t = fn("s32 n", "    s32 x;\n\n    if (n) {\n        x = 1;\n    }\n    g(x);\n")
        self.assertEqual(len(run("dup_tail", t)[0]), 1)

    def test_a_temporary_is_never_declared_above_the_locals_it_names(self):
        """town/func_800C1FCC: a `static void *const jt[] = {` keep ends the declaration run at the
        body's FIRST line, so `_decl_block_end` returns `lo - 1` and `__typeof__(increased_y ...)`
        landed above `s32 increased_y;`.  45 of the run's 45 cond_temp nobuild instances."""
        body = ("    static const s32 tbl[] = {\n        1, 2\n    };\n    s32 y;\n\n"
                "    y = n + 1;\n    y = y + 2;\n    y = y + 3;\n    y = y + 4;\n"
                "    y = y + 5;\n    y = y + 6;\n    y = y + 7;\n    if (y > 5) {\n"
                "        g(y + 1, tbl[0]);\n    }\n    h(y);\n")
        t = fn("s32 n", body)
        got, d = run("cond_temp", t)
        self.assertEqual(got, [])                       # `y` is declared BELOW the insertion point
        self.assertGreaterEqual(d["cond_temp:names-a-block-local"], 1)
        # `hoist` builds its temporary exactly the same way and now carries the same guard
        got2, _ = run("hoist", t)
        for p, _ in got2:
            names = set(re.findall(r"[A-Za-z_]\w*", p["expr"]))
            self.assertFalse(names & {"y", "tbl"},
                             "hoist still names a later declaration: %s" % p["label"])
        # a parameter-only expression is still enumerated: the guard is about LOCALS, not placement
        self.assertIn("n + 1", [p["expr"] for p, _ in got2])

    def test_retype_void_offsets_refuse_a_member_increment(self):
        """`*(s32 *)((u8 *)p + 0x4)++` increments the POINTER: postfix binds tighter than `*`."""
        t = fn("void *arg", "    S_1 *p;\n\n    p = arg;\n    p->unk_0C++;\n    g(p->unk_12);\n",
               head=OFF_HEAD)
        got, d = run("retype_void", t)
        for p, cand in got:
            self.assertNotIn(")++", cand)
        self.assertGreaterEqual(d["retype_void:offset:member-incdec"], 1)

    def test_a_note_comment_above_a_statement_is_not_a_continuation(self):
        """dungeon/func_8008FF58: `_mask` keeps a comment's `/*` and `*/`, so a note line read as
        the previous statement and the line under it was refused as a continuation."""
        note = "       /* UNRESOLVED C shape (pin): removing it drops a computation */\n"
        t = fn("S *p, s32 n", "    s32 x;\n\n    if (n) {\n        x = 1;\n" + note +
                              "        g(x);\n    } else {\n        x = 2;\n" + note +
                              "        g(x);\n    }\n    h(x);\n")
        got, d = run("tail_merge", t)
        self.assertEqual([p["n_tail"] for p, _ in got], [1])
        self.assertEqual(d["tail_merge:tail-is-a-continuation-line"], 0)
        # and the same line no longer makes `hoist` call the statement under it a continuation
        t2 = fn("S *p", "    s32 x;\n\n    x = 0;\n" + note + "    x = p->a + 1;\n    g(x);\n")
        got2, d2 = run("hoist", t2)
        self.assertEqual(d2["hoist:continuation-line"], 0)
        self.assertTrue(got2)

    def test_merge_refuses_two_declarations_at_the_same_depth_in_DIFFERENT_blocks(self):
        """town/func_800A4A8C: varset's `merge:different-block` compares DEPTH, and two sibling
        `if` arms declare at the same depth - the rename then puts a name where it does not exist
        ("`enabled' undeclared").  All 12 merge nobuild instances of the run, 7 of which HEAD's own
        merge produces at its default, so the shape predates `allow_init`."""
        t = fn("s32 n", "    if (n) {\n        s32 heading;\n\n        heading = 1;\n"
                        "        g(heading);\n    } else {\n        s32 enabled;\n\n"
                        "        enabled = 2;\n        g(enabled);\n    }\n")
        got, d = run("merge", t)
        for p, cand in got:
            self.assertNotIn("heading>enabled", p["label"])
            self.assertNotIn("enabled>heading", p["label"])
        self.assertGreaterEqual(d["merge:different-block-same-depth"], 1)
        # the same two names in ONE block are still merged
        t2 = fn("s32 n", "    s32 heading;\n    s32 enabled;\n\n    heading = 1;\n"
                         "    g(heading);\n    enabled = 2;\n    g(enabled);\n    h(n);\n")
        self.assertTrue([p for p, _ in run("merge", t2)[0]
                         if "heading" in p["label"] and "enabled" in p["label"]])

    def test_the_offset_spelling_refuses_a_row_without_the_u8_type(self):
        """dungeon/func_81940F34 never writes `u8` and does not reach the tree's typedefs, so
        `(u8 *)state` is "`u8' undeclared".  4 of the run's 8 remaining nobuild instances."""
        head = OFF_HEAD.replace("u8 pad_00[0xC];", "char pad_00[0xC];") \
                       .replace("u8 pad_10[0x2];", "char pad_10[0x2];") \
                       .replace("u16 unk_12;", "short unk_12;")
        self.assertNotIn("u8", head)
        t = fn("void *arg", "    S_1 *p;\n\n    p = arg;\n    p->unk_0C = 1;\n", head=head)
        got, d = run("retype_void", t)
        self.assertEqual([p for p, _ in got if p.get("spelling") == "offset_load"], [])
        self.assertGreaterEqual(d["retype_void:offset:row-has-no-u8-type"], 1)

    def test_dup_tail_needs_no_continuation_guard(self):
        """The continuation class is tail_merge's ALONE, and this says why - measured, not assumed.

        `dup_after_if` duplicates the line AFTER a bare `}`, and a `}` always ends a statement, so
        `movable`'s trailing `;` plus that context already make the line complete.  `tail_merge`
        takes the LAST line of an arm, where the line above can be an open call, which is where the
        five nobuild instances came from.  main/func_800111D4, the row that looked like this class,
        is the ELSE-arm brace above.
        """
        t = fn("S *p, s32 n", "    s32 x;\n\n    if (n) {\n        x = 1;\n    }\n    g(p->a,\n"
                              "      p->b);\n")
        got, d = run("dup_tail", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["dup_tail:next-line-not-a-simple-statement"], 1)


class ReviewFixesD(unittest.TestCase):
    """The two defects the round-33 adversarial reviewer demonstrated (both MAJOR, both real).

    Each defect gets its must-refuse cases AND the must-accept case beside them, because both
    guards are shape guards: a guard that also refuses the honest shape has not fixed anything.

    PROVEN TO FAIL BEFORE THE FIX against `work/native_lane/r33_catalog/scratch/ps_prefix_D/
    perturb_struct.py` - this module with the THREE guard CALL SITES removed and nothing else -
    run by `scratch/prefix_run_D.py`.  HEAD cannot be the baseline: it has neither `dup_tail` nor
    `cond_temp`.  5 of the 8 fail there: the four refusal tests and the `hoist` one.  The two
    must-accept tests pass (which is the point of having them), and so does the helper unit test,
    whose functions the pre-fix copy still contains - it discriminates nothing and is not claimed
    to.
    """

    # ---- defect 1: dup_tail wrote the copy behind a jump, where it can never run

    def test_dup_tail_refuses_an_arm_that_has_already_returned(self):
        """main/func_7FDD1A0C: `if (next_entry == 0) { return 0; }` then the tail - the copy
        written into the IF arm sits behind the `return` and is unreachable.  1,117 of the kind's
        2,276 population instances, every one of them measured INVISIBLE."""
        t = fn("s32 n", "    s32 x;\n\n    x = 0;\n    if (n == 0) {\n        return;\n    }\n"
                        "    x = n + 0x20;\n    g(x);\n")
        got, d = run("dup_tail", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["dup_tail:jump-before-the-tail"], 1)

    def test_dup_tail_refuses_an_arm_that_has_already_jumped(self):
        """The same for `goto` (main/func_7FDD26A8) and for `break` (main/func_7FDD3834)."""
        t = fn("s32 n", "    s32 x;\n\n    x = 0;\n    if (n == 0) {\n        goto epilogue;\n"
                        "    }\n    x = n + 1;\n    g(x);\nepilogue:\n    return;\n")
        got, d = run("dup_tail", t)
        self.assertEqual(got, [])
        self.assertGreaterEqual(d["dup_tail:jump-before-the-tail"], 1)
        t2 = fn("s32 n", "    s32 x;\n\n    x = 0;\n    while (n) {\n        if (n == 0) {\n"
                         "            break;\n        }\n        x = n + 1;\n        g(x);\n"
                         "    }\n")
        got2, d2 = run("dup_tail", t2)
        self.assertEqual([p["label"] for p, _ in got2], [])
        self.assertGreaterEqual(d2["dup_tail:jump-before-the-tail"], 1)

    def test_dup_tail_still_takes_a_jump_in_a_NESTED_block(self):
        """Only a jump at the ARM'S OWN depth is dead.  `if (c) { if (d) { return; } }` falls
        through when `d` is false, so the copy runs and the instance is honest - the guard must
        read the depth, not the word."""
        t = fn("s32 n", "    s32 x;\n\n    x = 0;\n    if (n == 0) {\n        if (n > 1) {\n"
                        "            return;\n        }\n    }\n    x = n + 1;\n    g(x);\n")
        got, d = run("dup_tail", t)
        self.assertEqual(len(got), 1)
        self.assertEqual(d["dup_tail:jump-before-the-tail"], 0)
        self.assertIn("    } else {\n        x = n + 1;\n    }\n", got[0][1])

    # ---- defect 2: an operand lifted above a side effect in the SAME expression

    def test_cond_temp_refuses_an_operand_hoisted_over_a_store_in_the_condition(self):
        """`if ((p->a = n) > q->a)` - hoisting `q->a` puts its load BEFORE the store to `p->a`.
        Placement settles a store BETWEEN the insertion point and the `if` and settles nothing
        about one INSIDE the condition; report_impl_D §5 claimed otherwise and was wrong."""
        t = fn("S *p, S *q, s32 n", "    if ((p->a = n) > q->a) {\n        n = 1;\n    }\n"
                                    "    g(n);\n")
        got, d = run("cond_temp", t)
        self.assertEqual([p["label"] for p, _ in got], [])
        self.assertGreaterEqual(d["cond_temp:side-effect-elsewhere-in-the-expression"], 1)

    def test_cond_temp_refuses_an_operand_hoisted_over_an_increment_in_the_condition(self):
        t = fn("S *p, S *q, s32 n", "    if (p->a++ > q->b) {\n        n = 1;\n    }\n"
                                    "    g(n);\n")
        got, d = run("cond_temp", t)
        self.assertEqual([p["label"] for p, _ in got], [])
        self.assertGreaterEqual(d["cond_temp:side-effect-elsewhere-in-the-expression"], 1)

    def test_cond_temp_still_takes_a_condition_with_no_side_effect(self):
        """The guard reads the REST of the condition, not the presence of an operator: a plain
        comparison of two member loads still enumerates both the whole condition and the operand."""
        t = fn("S *p, S *q, s32 n", "    if (p->a > q->b) {\n        n = 1;\n    }\n    g(n);\n")
        got, d = run("cond_temp", t)
        self.assertTrue(len(got) >= 2)
        self.assertEqual(d["cond_temp:side-effect-elsewhere-in-the-expression"], 0)

    def test_hoist_carries_the_same_guard_and_keeps_its_own_assignment(self):
        """The reviewer measured HEAD's `hoist` doing the same on `x = p->a++ + q->b;`, so the
        helper is applied there too.  The statement's OWN top-level `=` is not a side effect the
        temporary crosses - the store to `x` happens after the right-hand side is evaluated and the
        temporary is assigned before the statement - so `x = p->a + q->b;` must still be taken."""
        t = fn("S *p, S *q, s32 n", "    s32 x;\n\n    x = p->a++ + q->b;\n    g(x);\n")
        got, d = run("hoist", t)
        self.assertEqual([p["label"] for p, _ in got if "q->b" in p["label"]], [])
        self.assertGreaterEqual(d["hoist:side-effect-elsewhere-in-the-expression"], 1)
        t2 = fn("S *p, S *q, s32 n", "    s32 x;\n\n    x = p->a + q->b;\n    g(x);\n")
        got2, d2 = run("hoist", t2)
        self.assertTrue(got2)
        self.assertEqual(d2["hoist:side-effect-elsewhere-in-the-expression"], 0)

    def test_the_rest_fragment_is_not_put_through_expr_ok(self):
        """A unit test of the helper, because the temptation is to re-use `_expr_ok`: the remainder
        of a condition is a FRAGMENT (`if (( = n) > `), and `_expr_ok`'s well-formedness rules -
        not-an-expression, a bare type, a top-level comma - would refuse almost every one."""
        d = P.Detail()
        self.assertTrue(P._rest_side_effect_free("p->a > ", d, "w", "cond_temp"))
        self.assertTrue(P._rest_side_effect_free("f(a, b) != ", d, "w", "cond_temp"))
        self.assertTrue(P._rest_side_effect_free(" >= ", d, "w", "cond_temp"))
        self.assertFalse(P._rest_side_effect_free("(p->a = n) > ", d, "w", "cond_temp"))
        self.assertFalse(P._rest_side_effect_free("p->a++ > ", d, "w", "cond_temp"))
        # `_stmt_rest` blanks ONE top-level `=` and no other
        self.assertEqual(" ".join(P._stmt_rest("x = A + B;", 4, 5).split()), "x + B;")
        self.assertIn("=", P._stmt_rest("x = (p->a = n) + B;", 17, 18))


if __name__ == "__main__":
    unittest.main()


# --------------------------------------------------------------------------- the __typeof__ declaration
# A first hoist's `__typeof__(EXPR) hoisted_1;` must be read as a declaration by the block scanner,
# or a second hoist / cond_temp declares its temporary below a statement (hoist>hoist 26% NOBUILD,
# cond_temp>cond_temp 35% in the round-33 two-move catalogue; report_run2.txt §4).

class TypeofDeclaration(unittest.TestCase):
    def test_a_typeof_temporary_is_a_declaration_line(self):
        self.assertTrue(P._declaration_line("    __typeof__(p->a) hoisted_1;"))
        self.assertTrue(P._declaration_line("    __typeof__(p->a) *hoisted_2;"))
        self.assertFalse(P._declaration_line("    hoisted_1 = p->a;"))

    def test_a_second_hoist_declares_below_the_first_temporary(self):
        first = only("hoist", Hoist.BASE, "hoist:member:p->a")
        self.assertIn("    __typeof__(p->a) hoisted_1;\n", first)
        # `y = n + 1;` is still a plain statement on the first hoist's text: hoist `n + 1` there.
        second = only("hoist", first, "hoist:arith:n + 1")
        lines = [l.strip() for l in second.split("\n")]
        d1 = lines.index("__typeof__(p->a) hoisted_1;")
        d2 = next(i for i, l in enumerate(lines) if l.startswith("__typeof__(n + 1)"))
        s1 = lines.index("hoisted_1 = p->a;")
        self.assertLess(d1, d2)
        self.assertLess(d2, s1)                        # a declaration, never below a statement
