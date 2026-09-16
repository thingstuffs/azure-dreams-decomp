"""`tools/lanes/perturb_basic`: each m2c perturbation makes its move on synthetic text, refuses what
would change the program, and obeys the catalogue's contract.

Every test is textual (no compiler): the module's contract is that it produces a DETERMINISTIC list
of (params, text) instances ordered by site, that no instance touches a preprocessor directive line
or adds a pin, and that a text which already carries pin sites is refused outright - what the
perturbed text then compiles to is the catalogue's measurement, not this module's claim.

Each kind has at least two must-refuse cases beside its move.
"""
import collections
import re
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/lanes"))
sys.path.insert(0, str(ROOT / "tools/xform"))

from pin_census import sites_of                       # noqa: E402
import perturb_basic as P                             # noqa: E402
from xform import t51_sched_order as T51             # noqa: E402

HEAD = '#include "common.h"\n\n'


def fn(params, body, name="f", ret="void"):
    return HEAD + "%s %s(%s)\n{\n%s}\n" % (ret, name, params, body)


def run(kind, text):
    d = P.Detail()
    return dict(P.PERTURBATIONS)[kind](text, d), d


def labels(kind, text):
    return [p["label"] for p, _ in run(kind, text)[0]]


# --------------------------------------------------------------------------- param_copy

PC = fn("u8 *tile, s32 n",
        "    s32 i;\n"
        "    i = 0;\n"
        "    while (i < n) {\n"
        "        tile[i] = 0;\n"
        "        i = i + 1;\n"
        "    }\n")


class ParamCopy(unittest.TestCase):
    def test_move(self):
        ins, _ = run("param_copy", PC)
        got = {p["param"]: t for p, t in ins}
        self.assertEqual(sorted(got), ["n", "tile"])
        t = got["tile"]
        self.assertIn("void f(u8 *tile_in, s32 n)", t)
        self.assertIn("    u8 *tile;\n", t)
        self.assertIn("    tile = tile_in;\n", t)
        self.assertIn("tile[i] = 0;", t)              # the body's uses stay `tile`
        self.assertLess(t.index("u8 *tile;"), t.index("tile = tile_in;"))

    def test_site_is_the_copy_line_and_declaration_comes_first(self):
        ins, _ = run("param_copy", PC)
        p, t = [x for x in ins if x[0]["param"] == "n"][0]
        self.assertEqual(PC.splitlines()[p["site"] - 1].strip(), "i = 0;")
        self.assertEqual(t.splitlines()[p["decl_line"] - 1].strip(), "s32 n;")

    def test_refuse_array_and_function_pointer_parameters(self):
        d = P.Detail()
        P.param_copy(fn("u8 tiles[4]", "    tiles[0] = 1;\n"), d)
        self.assertEqual(d["array-parameter"], 1)
        d = P.Detail()
        P.param_copy(fn("void (*cb)(s32)", "    cb(1);\n"), d)
        self.assertEqual(d["function-pointer-parameter"], 1)

    def test_refuse_struct_by_value_and_name_collision(self):
        d = P.Detail()
        out = P.param_copy(fn("struct Vec v", "    v.x = 1;\n"), d)
        self.assertEqual(out, [])
        self.assertEqual(d["struct-by-value-parameter"], 1)
        d = P.Detail()
        out = P.param_copy(fn("s32 n, s32 n_in", "    n_in = n;\n"), d)
        self.assertEqual([p["param"] for p, _ in out], ["n_in"])
        self.assertEqual(d["name-collides"], 1)

    def test_refuse_declaration_initialiser_that_reads_the_parameter(self):
        d = P.Detail()
        out = P.param_copy(fn("u8 *p", "    u8 *q = p;\n    q[0] = 1;\n"), d)
        self.assertEqual(out, [])
        self.assertEqual(d["read-in-declaration-initialiser"], 1)

    def test_refuse_declaration_block_with_an_aggregate_initialiser(self):
        d = P.Detail()
        out = P.param_copy(fn("s32 n", "    static const s32 t[] = {1, 2};\n    n = t[n];\n"), d)
        self.assertEqual(out, [])
        self.assertEqual(d["declaration-block-not-simple"], 1)


# --------------------------------------------------------------------------- decl_reorder

DR = fn("void", "    s32 a;\n    u8 *b;\n    a = 1;\n    b = 0;\n")


class DeclReorder(unittest.TestCase):
    def test_move(self):
        ins, _ = run("decl_reorder", DR)
        self.assertEqual([p["label"] for p, _ in ins], ["decl_reorder: a <-> b"])
        t = ins[0][1]
        self.assertLess(t.index("u8 *b;"), t.index("s32 a;"))
        self.assertIn("    a = 1;\n    b = 0;\n", t)      # the statements do not move

    def test_assignment_is_not_a_declaration(self):
        # the regression that made every `x = y;` a declaration of `y` of type `x` (identifier
        # backtracking in DECL_ONE): two assignments must never be offered as a declaration swap
        ins, _ = run("decl_reorder", fn("void", "    s32 source_obj;\n    s32 source;\n"
                                                "    source_obj = source;\n    source = 1;\n"))
        self.assertEqual([p["label"] for p, _ in ins], ["decl_reorder: source_obj <-> source"])

    def test_refuse_side_effect_initialiser(self):
        d = P.Detail()
        out = P.decl_reorder(fn("void", "    s32 a = g();\n    s32 b;\n    b = a;\n"), d)
        self.assertEqual(out, [])
        self.assertEqual(d["initialiser-has-side-effect"], 1)

    def test_refuse_second_reads_first(self):
        d = P.Detail()
        out = P.decl_reorder(fn("void", "    s32 a;\n    s32 b = a;\n    g(b);\n"), d)
        self.assertEqual(out, [])
        self.assertEqual(d["second-reads-first"], 1)

    def test_refuse_multi_declarator(self):
        d = P.Detail()
        out = P.decl_reorder(fn("void", "    s32 a, c;\n    s32 b;\n    b = a + c;\n"), d)
        self.assertEqual(out, [])
        self.assertEqual(d["multi-declarator"], 1)


# --------------------------------------------------------------------------- width_change

WC = fn("s16 k", "    u8 v;\n    v = (u8)k;\n    g(v);\n")


class WidthChange(unittest.TestCase):
    def test_move(self):
        ins, _ = run("width_change", WC)
        moves = {(p["var"], p["move"]): p for p, _ in ins}
        self.assertIn(("k", "up"), moves)              # s16 -> s32
        self.assertIn(("k", "down"), moves)            # s16 -> s8
        self.assertIn(("k", "sign"), moves)            # s16 -> u16
        self.assertEqual(moves[("k", "up")]["to"], "s32")
        self.assertEqual(moves[("k", "down")]["to"], "s8")
        self.assertEqual(moves[("k", "sign")]["to"], "u16")
        self.assertEqual(moves[("k", "up")]["from"], "s16")
        self.assertIn("void f(s32 k)", dict(((p["var"], p["move"]), t) for p, t in ins)[("k", "up")])
        self.assertIn("    u16 v;\n", dict(((p["var"], p["move"]), t) for p, t in ins)[("v", "up")])

    def test_c_spellings_normalise(self):
        ins, _ = run("width_change", fn("void", "    unsigned char c;\n    c = 1;\n    g(c);\n"))
        tos = sorted({p["to"] for p, _ in ins})
        self.assertEqual(tos, ["s8", "u16"])
        self.assertEqual({p["from"] for p, _ in ins}, {"unsigned char"})

    def test_a_self_contained_row_keeps_to_the_widths_it_declares(self):
        # `dungeon/func_800933D8` carries its own typedefs (u8/s16/s32/u32, no s8): writing `s8`
        # there is a syntax error, so an unknown width is spelled in plain C
        text = ("typedef unsigned char u8;\ntypedef short s16;\ntypedef int s32;\n\n"
                "void f(void)\n{\n    s16 v;\n    v = 1;\n    g(v);\n}\n")
        ins, _ = run("width_change", text)
        got = {p["move"]: p for p, _ in ins}
        self.assertEqual(got["down"]["to"], "signed char")     # s8 is not declared here
        self.assertEqual(got["down"]["canon"], "s8")
        self.assertEqual(got["up"]["to"], "s32")               # s32 is
        self.assertIn("    signed char v;\n", dict((p["move"], t) for p, t in ins)["down"])

    def test_refuse_pointer_and_address_taken(self):
        d = P.Detail()
        P.width_change(fn("void", "    u8 *p;\n    p = 0;\n    g(p);\n"), d)
        self.assertEqual(d["pointer"], 1)
        d = P.Detail()
        out = P.width_change(fn("void", "    s32 v;\n    v = 1;\n    g(&v);\n"), d)
        self.assertEqual(out, [])
        self.assertEqual(d["address-taken"], 1)

    def test_refuse_array_and_prototype_parameter(self):
        d = P.Detail()
        P.width_change(fn("void", "    u8 t[4];\n    t[0] = 1;\n"), d)
        self.assertEqual(d["array"], 1)
        d = P.Detail()
        text = HEAD + "void f(s16 k);\n\nvoid f(s16 k)\n{\n    g(k);\n}\n"
        out = P.width_change(text, d)
        self.assertEqual(out, [])
        self.assertEqual(d["prototype-in-file"], 1)


# --------------------------------------------------------------------------- adjacent_swap

AS = fn("void", "    s32 a;\n    s32 b;\n    a = 1;\n    b = 2;\n    g(a, b);\n")


class AdjacentSwap(unittest.TestCase):
    def test_move(self):
        ins, _ = run("adjacent_swap", AS)
        self.assertEqual(len(ins), 1)
        self.assertIn("    b = 2;\n    a = 1;\n", ins[0][1])

    def test_refuse_a_call(self):
        d = P.Detail()
        out = P.adjacent_swap(fn("void", "    s32 a;\n    a = 1;\n    g(a);\n"), d)
        self.assertEqual(out, [])
        self.assertEqual(d["call"], 1)

    def test_refuse_dependent_statements(self):
        d = P.Detail()
        out = P.adjacent_swap(fn("void", "    s32 a;\n    s32 b;\n    a = 1;\n    b = a;\n"), d)
        self.assertEqual(out, [])
        self.assertEqual(d["dep-data"], 1)

    def test_refuse_a_brace_less_control_body(self):
        d = P.Detail()
        out = P.adjacent_swap(fn("void", "    s32 a;\n    s32 b;\n    if (a)\n        a = 1;\n    b = 2;\n"), d)
        self.assertEqual(out, [])
        self.assertEqual(d["brace-less-control-body"], 1)

    def test_refuse_a_declaration_pair(self):
        d = P.Detail()
        P.adjacent_swap(fn("void", "    s32 a;\n    s32 b;\n    a = b;\n"), d)
        self.assertGreaterEqual(d["declaration"], 1)


# --------------------------------------------------------------------------- local_alias

LA = fn("void", "    s32 y;\n    s32 p;\n    s32 q;\n    y = 3;\n    p = y + 1;\n    q = y + 2;\n")


class LocalAlias(unittest.TestCase):
    def test_move(self):
        ins, _ = run("local_alias", LA)
        self.assertTrue(ins)
        p, t = ins[0]
        self.assertEqual(p["var"], "y")
        self.assertEqual(p["alias"], "y_alias")
        self.assertEqual(p["typed"], "explicit")
        self.assertIn("    s32 y_alias;\n", t)
        self.assertIn("    y_alias = y;\n", t)
        self.assertIn("p = y_alias + 1;", t)
        self.assertIn("q = y_alias + 2;", t)
        self.assertIn("    y = 3;\n", t)               # the write before the run is untouched
        self.assertLess(t.index("s32 y_alias;"), t.index("y_alias = y;"))

    def test_declaration_goes_into_the_run_s_own_arm(self):
        text = fn("s32 c", "    s32 y;\n    s32 p;\n    y = c;\n"
                           "    if (c) {\n        p = 1;\n    } else {\n"
                           "        p = y + 1;\n        p = y + 2;\n    }\n")
        ins, _ = run("local_alias", text)
        t = [x[1] for x in ins if x[0]["var"] == "y"][0]
        lines = t.splitlines()
        decl = next(i for i, l in enumerate(lines) if l.strip() == "s32 y_alias;")
        els = next(i for i, l in enumerate(lines) if l.strip().startswith("} else"))
        self.assertGreater(decl, els)                  # not in the then-arm

    def test_refuse_address_taken_and_written_in_the_run(self):
        d = P.Detail()
        P.local_alias(fn("void", "    s32 y;\n    s32 p;\n    p = y + 1;\n    p = y + 2;\n    g(&y);\n"), d)
        self.assertEqual(d["address-taken"], 1)
        d = P.Detail()
        out = P.local_alias(fn("void", "    s32 y;\n    s32 p;\n    p = y + 1;\n    y = p;\n    p = y + 2;\n"), d)
        self.assertEqual([p["var"] for p, _ in out], [])
        self.assertTrue(d["written-in-run"] >= 1)

    def test_refuse_a_single_read(self):
        d = P.Detail()
        out = P.local_alias(fn("void", "    s32 y;\n    s32 p;\n    s32 q;\n    p = y + 1;\n    q = 2;\n"), d)
        self.assertEqual(out, [])
        self.assertEqual(d["no-run-with-two-reads"], 1)

    def test_at_most_four_runs_a_function(self):
        body = "".join("    s32 v%d;\n" % i for i in range(8))
        body += "".join("    v%d = v%d + 1;\n" % (i, i) for i in range(8))
        body += "".join("    v%d = v%d + 2;\n" % (i, i) for i in range(8))
        out, d = run("local_alias", fn("void", body))
        self.assertLessEqual(len(out), P.MAX_ALIAS_PER_FN)
        self.assertEqual([p["site"] for p, _ in out], sorted(p["site"] for p, _ in out))


# --------------------------------------------------------------------------- page_local

PL = fn("void", "    s32 a;\n    a = D_800D1234;\n    D_800D5678 = a;\n    g(D_800D1234);\n")


class PageLocal(unittest.TestCase):
    def test_move(self):
        ins, _ = run("page_local", PL)
        self.assertEqual(len(ins), 1)
        p, t = ins[0]
        self.assertEqual(p["page"], "0x800D0000")
        self.assertEqual(p["uses"], 3)
        self.assertIn("    u8 *page;\n", t)
        self.assertIn("    page = (u8 *)0x800D0000;\n", t)
        self.assertIn("(*(__typeof__(D_800D1234) *)(page + 0x1234))", t)
        self.assertIn("(*(__typeof__(D_800D5678) *)(page + 0x5678))", t)
        self.assertLess(t.index("u8 *page;"), t.index("page = (u8 *)"))

    def test_refuse_array_function_and_address_of_uses(self):
        d = P.Detail()
        out = P.page_local(fn("void", "    s32 a;\n    a = D_800D1234[0];\n    a = D_800D5678;\n"), d)
        self.assertEqual(out, [])
        self.assertTrue(d["symbol-used-as-array-or-function"] >= 1)
        d = P.Detail()
        out = P.page_local(fn("void", "    s32 a;\n    a = (s32)&D_800D1234;\n    a = (s32)&D_800D5678;\n"), d)
        self.assertEqual(out, [])
        self.assertEqual(d["address-of-symbol"], 2)

    def test_refuse_single_use_page_and_an_existing_page_local(self):
        d = P.Detail()
        out = P.page_local(fn("void", "    s32 a;\n    a = D_800D1234;\n    a = D_800E5678;\n"), d)
        self.assertEqual(out, [])
        self.assertEqual(d["single-use-page"], 2)
        d = P.Detail()
        out = P.page_local(fn("void", "    u8 *page;\n    page = 0;\n    g(D_800D1234, D_800D5678);\n"), d)
        self.assertEqual(out, [])
        self.assertEqual(d["page-name-in-use"], 1)


# --------------------------------------------------------------------------- the shared contract

TEXTS = [PC, DR, WC, AS, LA, PL]


class Contract(unittest.TestCase):
    def test_every_kind_is_deterministic(self):
        for kind, f in P.PERTURBATIONS:
            for text in TEXTS:
                a = [(p, t) for p, t in f(text)]
                b = [(p, t) for p, t in f(text)]
                self.assertEqual(a, b, kind)

    def test_instances_are_ordered_by_site_and_carry_the_contract_keys(self):
        for kind, f in P.PERTURBATIONS:
            for text in TEXTS:
                out = f(text)
                self.assertEqual([p["site"] for p, _ in out], sorted(p["site"] for p, _ in out), kind)
                for p, t in out:
                    self.assertEqual(p["kind"], kind)
                    self.assertIsInstance(p["label"], str)
                    self.assertTrue(1 <= p["site"] <= len(text.splitlines()) + 1)
                    self.assertNotEqual(t, text)

    def test_a_text_with_a_pin_site_is_refused_outright(self):
        pinned = fn("u8 *tile, s32 n", "    s32 i;\n    i = 0;\n    ASM_KEEP(i);\n    tile[n] = i;\n")
        self.assertTrue(sites_of(pinned))
        for kind, f in P.PERTURBATIONS:
            d = P.Detail()
            self.assertEqual(f(pinned, d), [], kind)
            self.assertEqual(d["text-has-pins"], 1, kind)

    def test_no_directive_line_is_ever_touched(self):
        text = (HEAD + "#define LIMIT 4\n\nvoid f(s32 n)\n{\n    s32 a;\n    s32 b;\n"
                "    a = LIMIT;\n    b = 2;\n    g(a, b, n);\n}\n")
        before = P._directive_lines(text)
        for kind, f in P.PERTURBATIONS:
            for _, t in f(text):
                self.assertEqual(P._directive_lines(t), before, kind)

    def test_nothing_adds_a_pin_or_scaffolding(self):
        banned = re.compile(r"\bASM_[A-Z0-9_]+|__asm__|\basm\b|\bvolatile\b|#pragma|__attribute__")
        for kind, f in P.PERTURBATIONS:
            for text in TEXTS:
                for _, t in f(text):
                    self.assertEqual(sites_of(t), [], kind)
                    self.assertFalse(banned.search(t[len(HEAD):]), kind)

    def test_detail_counter_records_refusal_and_subject(self):
        d = P.Detail()
        P.param_copy(fn("struct Vec v", "    v.x = 1;\n"), d)
        self.assertTrue(any(k == "struct-by-value-parameter" and w for k, w in d.detail))

    def test_a_plain_counter_works_as_detail(self):
        c = collections.Counter()
        P.param_copy(fn("struct Vec v", "    v.x = 1;\n"), c)
        self.assertEqual(c["struct-by-value-parameter"], 1)


# ------------------------------------------------------- the round-33 review's four defects
#
# One root cause behind three of them: `DECL_ONE` matched `<ident> <ident>;`, which is also the shape
# of `goto done;` and `return obj;`, so a JUMP parsed as a declaration.  The consequences were
# decl_reorder swapping two `goto`s (a control-flow change that compiles), param_copy inserting its
# entry copy AFTER a leading `goto` (unreachable copy, uninitialised local), and local_alias emitting
# `return v_alias;` as its declaration (invalid C, lost as NOBUILD).  The fourth was independent:
# `t51.access()` reports `x = <memory>;` as a non-memory statement, so `t51.independent()` called a
# store/load pair on the SAME lvalue independent.

class ReviewFixes(unittest.TestCase):
    def test_a_jump_is_not_a_declaration(self):
        for s in ("    goto done;", "    return obj;", "    return x + 1;", "    break;",
                  "    continue;", "    typedef unsigned char u8;"):
            self.assertIsNone(P.DECL_ONE.match(s), s)
        for s in ("    u8 x;", "    S_1 *p;", "    static s32 n;", "    const u8 *q = r;"):
            self.assertIsNotNone(P.DECL_ONE.match(s), s)

    def test_decl_reorder_never_swaps_two_jumps(self):
        # main/func_7FDD1F7C site 18: `goto state2;` / `goto done;` were offered as a decl pair and
        # swapped, which moved the body of a brace-less `if` out of its arm
        text = fn("s32 state", "    s32 r;\n    r = 0;\n    if (state == 2)\n"
                               "        goto state2;\n    goto done;\n"
                               "state2:\n    r = 2;\ndone:\n    g(r);\n")
        out, d = run("decl_reorder", text)
        self.assertEqual([p["label"] for p, _ in out], [])
        self.assertEqual(d["second-reads-first"] + d["multi-declarator"], 0)

    def test_decl_reorder_refuses_a_brace_less_control_body(self):
        # the guard that stops a swap landing inside an arm, exercised on its own path
        text = fn("s32 c", "    if (c)\n        s32 a;\n    s32 b;\n    g(c);\n")
        out, d = run("decl_reorder", text)
        self.assertEqual(out, [])
        self.assertEqual(d["brace-less-control-body"], 1)

    def test_param_copy_puts_the_copy_before_a_leading_jump(self):
        # slus/w_80048734: the declaration run swallowed `goto test;`, so the copy landed after the
        # jump - unreachable, and the new local was read uninitialised
        text = fn("u8 *source", "    u32 b;\n    goto test;\n"
                                "body:\n    b = *source;\n    source = source + 1;\n"
                                "test:\n    if (b == 0) goto body;\n")
        out, _ = run("param_copy", text)
        self.assertEqual(len(out), 1)
        t = out[0][1]
        self.assertLess(t.index("source = source_in;"), t.index("goto test;"))
        self.assertLess(t.index("u8 *source;"), t.index("source = source_in;"))

    def test_local_alias_never_declares_with_a_control_keyword(self):
        # town/func_800A48A0 / town/func_80092360: the variable has NO declaration in the function
        # (it is a global), so the only line `_declared_type` matched was `return D_800CFE60;` - it
        # returned the type `return` and the alias was emitted as `return D_800CFE60_alias;`.  The
        # variable must not be a candidate at all now.
        text = fn("void", "    s32 p;\n    s32 q;\n"
                          "    p = D_800CFE60 + 1;\n    q = D_800CFE60 + 2;\n"
                          "    return D_800CFE60;\n", ret="s32")
        out, _ = run("local_alias", text)
        self.assertEqual([p["var"] for p, _ in out], [])
        for p, t in out:
            self.assertNotIn(p["type"].strip().split()[0], ("return", "goto", "break", "continue"))

    def test_adjacent_swap_refuses_a_store_and_a_load_of_the_same_lvalue(self):
        # t51.independent('a[0] = 1;', 'x = a[0];') is True - the gate would have caught it, the
        # catalogue has no gate
        self.assertTrue(T51.independent("a[0] = 1;", "x = a[0];"))
        self.assertFalse(P._mem_independent("a[0] = 1;", "x = a[0];"))
        for a, b in (("saved = lv->value;", "lv->value = rv->value;"),
                     ("object = *slot;", "*slot = 0;"),
                     ("a[i] = 1;", "x = a[j];")):
            self.assertFalse(P._mem_independent(a, b), (a, b))
        # and it must NOT refuse a pointer store beside a plain arithmetic read of the same pointer
        self.assertTrue(P._mem_independent("parent = object + 0x20;", "((S *)object)->unk = 1;"))
        self.assertTrue(P._mem_independent("x = y * z;", "p->f = 1;"))
        self.assertTrue(P._mem_independent("x = (S *)y;", "p->f = 1;"))

    def test_adjacent_swap_refuses_a_global_store_beside_a_dereference(self):
        # the second half of the same modelling gap: `t51.access()` calls a plain-identifier LHS a
        # REGISTER write, but `D_800814AC = delta;` stores to a global, which an unrelated
        # dereference may alias
        loc = {"delta", "c", "x", "y", "z"}
        self.assertFalse(P._mem_independent("D_800814AC = delta;",
                                            "((Gfx *)0x80010000)->shade = c;", loc))
        self.assertTrue(P._mem_independent("x = 1;", "p->f = 2;", loc))       # x is a local
        self.assertTrue(P._mem_independent("x = y * z;", "p->f = 1;", loc))
        self.assertTrue(P._mem_independent("D_800814AC = delta;", "x = y + 1;", loc))

    def test_adjacent_swap_does_not_emit_the_same_lvalue_pair(self):
        text = fn("void", "    s32 x;\n    s32 t[4];\n    t[0] = 1;\n    x = t[0];\n    g(x);\n")
        out, d = run("adjacent_swap", text)
        self.assertEqual(out, [])
        self.assertEqual(d["dep-mem-alias"], 1)

    def test_a_conditionally_compiled_function_is_refused(self):
        # town/func_8051EDA4 defines the row twice, `#ifndef NON_MATCHING` / `#else`: the second arm
        # is never compiled, so every instance in it would read as a spurious INVISIBLE
        text = (HEAD + "#ifndef NON_MATCHING\nvoid f(s32 n)\n{\n    s32 a;\n    a = n;\n    g(a);\n}\n"
                "#else\nvoid f(s32 n)\n{\n    s32 a;\n    a = n;\n    g(a);\n}\n#endif\n")
        for kind, f in P.PERTURBATIONS:
            d = P.Detail()
            self.assertEqual(f(text, d), [], kind)
            self.assertEqual(d["conditionally-compiled-function"], 2, kind)


if __name__ == "__main__":
    unittest.main()
