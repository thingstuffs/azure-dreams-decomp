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
        self.assertEqual(P.KINDS, ["hoist", "retype_void", "split", "merge", "goto_to_loop"])
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
        self.assertEqual(len(got), 1)
        self.assertIn("static void *p;", got[0][1])

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


if __name__ == "__main__":
    unittest.main()
