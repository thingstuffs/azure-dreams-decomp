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


def only(kind, text, opening, var=None):
    """The instances of one opening (of one variable), in site order."""
    ins, d = run(kind, text)
    return [(p, t) for p, t in ins
            if p.get("opening") == opening and (var is None or p.get("var") == var)], d


# a run whose source is NOT written above it, so the initialised-declaration spellings are legal
LA_INIT = fn("s32 y", "    s32 p;\n    s32 q;\n    p = y + 1;\n    q = y + 2;\n")


class LocalAlias(unittest.TestCase):
    def test_move(self):
        ins, _ = only("local_alias", LA, "base")
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
        ins, _ = only("local_alias", text, "base")
        t = [x[1] for x in ins if x[0]["var"] == "y"][0]
        lines = t.splitlines()
        decl = next(i for i, l in enumerate(lines) if l.strip() == "s32 y_alias;")
        els = next(i for i, l in enumerate(lines) if l.strip().startswith("} else"))
        self.assertGreater(decl, els)                  # not in the then-arm

    # --- opening: ALIAS_READ_ONCE (the run is one statement, the copy is read once)

    def test_read_once_opening(self):
        text = fn("void", "    s32 y;\n    s32 p;\n    s32 q;\n    p = y + 1;\n    q = 2;\n")
        ins, _ = only("local_alias", text, "read_once")
        self.assertTrue(ins)
        p, t = ins[0]
        self.assertEqual((p["var"], p["run"]), ("y", 1))
        self.assertIn("    y_alias = y;\n", t)
        self.assertIn("    p = y_alias + 1;\n", t)
        self.assertIn("    q = 2;\n", t)

    def test_read_once_refuses_a_variable_never_read(self):
        text = fn("void", "    s32 y;\n    s32 p;\n    y = 1;\n    p = 2;\n")
        out, d = run("local_alias", text)
        self.assertEqual([p["var"] for p, _ in out], [])
        self.assertGreaterEqual(d["no-run-with-a-read"], 1)

    # --- opening: ALIAS_WRITTEN_IN_RUN (the alias is a snapshot before the write)

    def test_written_in_run_renames_only_up_to_the_write(self):
        text = fn("void", "    s32 y;\n    s32 p;\n    s32 r;\n"
                          "    p = y + 1;\n    r = y + 9;\n    y = p;\n    p = y + 2;\n")
        ins, _ = only("local_alias", text, "written_in_run")
        self.assertTrue(ins)
        p, t = ins[0]
        self.assertIn("    p = y_alias + 1;\n", t)
        self.assertIn("    r = y_alias + 9;\n", t)
        self.assertIn("    y = p;\n", t)               # the write itself is untouched
        self.assertIn("    p = y + 2;\n", t)           # and everything after it reads `y`
        self.assertLess(t.index("y_alias = y;"), t.index("p = y_alias + 1;"))

    def test_written_in_run_never_renames_the_writing_statement(self):
        text = fn("void", "    s32 y;\n    s32 p;\n    s32 r;\n"
                          "    p = y + 1;\n    r = y + 2;\n    y = y + 3;\n    p = y;\n")
        for p, t in run("local_alias", text)[0]:
            if p["var"] == "y":
                self.assertIn("    y = y + 3;\n", t)

    # --- opening: ALIAS_BLOCK_REFUSED (what the declaration-block parser refused)

    def test_block_reopened_over_a_brace_carrying_declaration(self):
        # `struct { s32 a; } q;` IS a declaration, but the one-line parser refuses any line with a
        # brace on it - the whole leading block then read as "not simple"
        text = fn("s32 y", "    struct { s32 a; } q;\n    s32 p;\n"
                           "    p = y + 1;\n    p = y + 2;\n")
        ins, _ = only("local_alias", text, "block_reopened", var="y")
        self.assertTrue(ins)
        t = ins[0][1]
        self.assertIn("    struct { s32 a; } q;\n", t)
        self.assertLess(t.index("} q;"), t.index("s32 y_alias;"))
        self.assertLess(t.index("s32 y_alias;"), t.index("y_alias = y;"))

    def test_block_reopened_over_a_multi_line_aggregate_declaration(self):
        text = fn("s32 y", "    static void *const tbl[] = {\n        0, 0\n    };\n"
                           "    s32 p;\n    p = y + 1;\n    p = y + 2;\n")
        ins, _ = only("local_alias", text, "block_reopened", var="y")
        self.assertTrue(ins)
        t = ins[0][1]
        self.assertLess(t.index("};"), t.index("s32 y_alias;"))

    def test_the_widened_slot_still_refuses_an_unbalanced_declaration(self):
        # `_decl_slot` walks the block's declarations; an aggregate whose brace never closes above
        # the run is not a declaration it may step over
        text = fn("s32 y", "    static void *const tbl[] = {\n        0, 0\n    };\n"
                           "    s32 p;\n    p = y + 1;\n    p = y + 2;\n")
        ctx = P.Ctx(text)
        f0 = ctx.fns[0]
        run_line = next(i for i in range(len(ctx.lines)) if ctx.code(i).strip() == "p = y + 1;")
        at, why = P._decl_slot(ctx, f0, run_line)
        self.assertEqual(why, "multi_line_declaration")
        self.assertEqual(ctx.code(at).strip(), "p = y + 1;")
        at2, why2 = P._decl_slot(ctx, f0, run_line, wide=False)
        self.assertEqual(at2, None)
        self.assertEqual(why2, "declaration-block-not-simple:multi-line")

    def test_the_slot_refuses_a_directive_in_the_declaration_block(self):
        text = (HEAD + "void f(s32 y)\n{\n    s32 a;\n#define K 1\n    s32 p;\n"
                "    p = y + 1;\n    p = y + 2;\n}\n")
        ctx = P.Ctx(text)
        line = next(i for i in range(len(ctx.lines)) if ctx.code(i).strip() == "p = y + 1;")
        at, why = P._decl_slot(ctx, ctx.fns[0], line)
        self.assertEqual(at, None)
        self.assertEqual(why, "directive-in-declaration-block")

    def test_refuse_address_taken_inside_the_span_or_across_a_call(self):
        d = P.Detail()
        out = P.local_alias(fn("void", "    s32 y;\n    s32 p;\n    p = y + 1;\n    g(&y);\n"
                                       "    p = y + 2;\n"), d)
        self.assertEqual([p["var"] for p, _ in out if p["var"] == "y"], [])
        self.assertGreaterEqual(d["address-taken-inside-the-span"]
                                + d["address-taken:call-or-store-in-the-span"], 1)
        # a call inside the span could write `y` through the pointer it was handed earlier
        d = P.Detail()
        out = P.local_alias(fn("void", "    s32 y;\n    s32 p;\n    h(&y);\n"
                                       "    p = y + 1;\n    g(p);\n    p = y + 2;\n"), d)
        self.assertEqual([p["var"] for p, _ in out if p["var"] == "y"], [])
        self.assertGreaterEqual(d["address-taken:call-or-store-in-the-span"], 1)

    def test_address_taken_outside_the_span_is_opened(self):
        text = fn("void", "    s32 y;\n    s32 p;\n    s32 q;\n"
                          "    h(&y);\n    p = y + 1;\n    q = y + 2;\n")
        ins, _ = only("local_alias", text, "address_taken", var="y")
        self.assertTrue(ins)
        t = ins[0][1]
        self.assertIn("    h(&y);\n", t)               # the address-of line is NOT renamed
        self.assertIn("    p = y_alias + 1;\n", t)

    # --- opening: TYPED_ALIAS_INIT_DECL (the initialised declaration, typed and untyped)

    def test_typed_init_declaration(self):
        ins, _ = only("local_alias", LA_INIT, "typed_init", var="y")
        self.assertTrue(ins)
        p, t = ins[0]
        self.assertIn("    s32 y_alias = y;\n", t)
        self.assertNotIn("    y_alias = y;\n", t)      # no separate copy statement
        self.assertIn("p = y_alias + 1;", t)
        self.assertEqual(p["site"], t.splitlines().index("    s32 y_alias = y;") + 1)

    def test_typed_init_refuses_when_the_source_is_written_above_the_run(self):
        # `y = 3;` sits between the declaration slot and the run: an initialiser at block entry
        # would snapshot the WRONG value
        ins, d = only("local_alias", LA, "typed_init", var="y")
        self.assertEqual(ins, [])
        self.assertGreaterEqual(d["typed-init:source-written-above-the-run"], 1)

    def test_typed_init_refuses_when_a_label_sits_between(self):
        text = fn("s32 y", "    s32 p;\n    g(p);\nagain:\n"
                           "    p = y + 1;\n    p = y + 2;\n    goto again;\n")
        ins, d = only("local_alias", text, "typed_init", var="y")
        self.assertEqual(ins, [])
        self.assertGreaterEqual(d["typed-init:label-between-the-declaration-and-the-run"], 1)

    def test_typed_init_void_casts_a_member_access_back(self):
        text = fn("S *obj", "    s32 p;\n    p = obj->f;\n    p = obj->g;\n")
        ins, _ = only("local_alias", text, "typed_init_void", var="obj")
        self.assertTrue(ins)
        p, t = ins[0]
        self.assertEqual(p["type"], "void *")
        self.assertIn("    void *obj_alias = obj;\n", t)
        self.assertIn("((S *)obj_alias)->f", t)
        self.assertIn("((S *)obj_alias)->g", t)

    def test_typed_init_void_refuses_a_use_it_cannot_spell(self):
        for body in ("    s32 p;\n    p = obj[0];\n    p = obj[1];\n",
                     "    s32 p;\n    p = *obj;\n    p = *obj + 1;\n"):
            ins, d = only("local_alias", fn("S *obj", body), "typed_init_void", var="obj")
            self.assertEqual(ins, [], body)
            self.assertGreaterEqual(d["typed-init-void:use-needs-more-than-a-member-cast"], 1, body)

    def test_typed_init_refuses_an_address_taken_source_with_a_call_above_the_run(self):
        # `&y` is taken, and a call sits between the declaration slot and the run: it could write
        # `y` through that pointer, so an initialiser at BLOCK ENTRY would snapshot the wrong
        # value.  The statement form, which copies at the run's head, is still offered.
        text = fn("void", "    s32 y;\n    s32 p;\n    s32 q;\n"
                          "    h(&y);\n    g(1);\n    p = y + 1;\n    q = y + 2;\n")
        ins, d = only("local_alias", text, "typed_init", var="y")
        self.assertEqual(ins, [])
        self.assertGreaterEqual(d["typed-init:address-taken-with-a-call-or-store-above-the-run"], 1)
        self.assertTrue(only("local_alias", text, "address_taken", var="y")[0])

    def test_an_array_symbol_is_known_from_its_declaration_alone(self):
        text = (HEAD + "extern u8 D_800D1234[];\n\nvoid f(void)\n{\n    s32 a;\n"
                "    a = (s32)&D_800D1234;\n    a += (s32)D_800D1234;\n}\n")
        kinds = P._sym_kinds(P.Ctx(text))
        self.assertEqual(kinds["D_800D1234"], "array")
        for _, t in P.addr_literal(text):
            self.assertNotIn("__typeof__(&D_800D1234)", t)   # never a pointer to an array

    def test_typed_init_void_refuses_a_non_pointer_source(self):
        ins, d = only("local_alias", LA_INIT, "typed_init_void", var="y")
        self.assertEqual(ins, [])
        self.assertGreaterEqual(d["typed-init-void:source-is-not-a-pointer"], 1)

    def test_at_most_four_runs_an_opening_a_function(self):
        body = "".join("    s32 v%d;\n" % i for i in range(8))
        body += "".join("    v%d = v%d + 1;\n" % (i, i) for i in range(8))
        body += "".join("    v%d = v%d + 2;\n" % (i, i) for i in range(8))
        out, d = run("local_alias", fn("void", body))
        per = collections.Counter(p["opening"] for p, _ in out)
        for opening, n in per.items():
            self.assertLessEqual(n, P.MAX_ALIAS_PER_FN, opening)
        self.assertEqual([p["site"] for p, _ in out], sorted(p["site"] for p, _ in out))


# --------------------------------------------------------------------------- stmt_shift

SH = fn("void", "    s32 a;\n    s32 b;\n    s32 c;\n    s32 d;\n"
                "    a = 1;\n    b = 2;\n    c = 3;\n    d = 4;\n")


class StmtShift(unittest.TestCase):
    def test_move(self):
        ins, _ = run("stmt_shift", SH)
        self.assertTrue(ins)
        got = {(p["stmt"], p["dir"], p["k"]): t for p, t in ins}
        self.assertIn(("a = 1;", "down", 2), got)
        t = got[("a = 1;", "down", 2)]
        body = [l.strip() for l in t.splitlines() if l.strip().endswith(";") and "=" in l
                and not l.strip().startswith("s32")]
        self.assertEqual(body, ["b = 2;", "c = 3;", "a = 1;", "d = 4;"])

    def test_up_and_down_and_k_are_recorded(self):
        ins, _ = run("stmt_shift", SH)
        ks = {(p["dir"], p["k"]) for p, _ in ins}
        self.assertIn(("up", 2), ks)
        self.assertIn(("down", 2), ks)
        self.assertTrue(all(P.MIN_SHIFT <= p["k"] <= P.MAX_SHIFT for p, _ in ins))
        for p, _ in ins:
            self.assertEqual(len(p["across"]), p["k"])

    def test_never_k_equals_one(self):
        # k == 1 is adjacent_swap's own move and must not be duplicated here
        self.assertEqual([p["k"] for p, _ in run("stmt_shift", SH)[0] if p["k"] < 2], [])

    def test_refuse_crossing_a_control_line_or_a_declaration(self):
        text = fn("s32 n", "    s32 a;\n    s32 b;\n    a = 1;\n    if (n) {\n        b = 2;\n    }\n"
                           "    b = 3;\n    n = 4;\n")
        out, d = run("stmt_shift", text)
        self.assertEqual([p["label"] for p, _ in out], [])
        self.assertGreaterEqual(d["crosses-control-or-not-simple"] + d["control-or-not-simple"], 1)
        text = fn("void", "    s32 a;\n    a = 1;\n    {\n        s32 b;\n        b = 2;\n"
                          "        b = 3;\n        b = 4;\n    }\n")
        out, d = run("stmt_shift", text)
        self.assertTrue(all(p["fn"] == "f" for p, _ in out))
        self.assertGreaterEqual(d["crosses-control-or-not-simple"] + d["control-or-not-simple"], 1)

    def test_refuse_crossing_a_call_or_a_dependent_statement(self):
        # a moved statement that touches MEMORY may not cross a call
        text = fn("S *p", "    s32 a;\n    s32 b;\n    s32 c;\n"
                          "    a = p->f;\n    g(b);\n    c = 3;\n    c = 4;\n")
        out, d = run("stmt_shift", text)
        self.assertEqual([q["stmt"] for q, _ in out if q["stmt"].startswith("a =")], [])
        self.assertGreaterEqual(d["call"] + d["crosses-call"], 1)
        text = fn("void", "    s32 a;\n    s32 b;\n    s32 c;\n"
                          "    a = 1;\n    b = a;\n    c = b;\n    c = 9;\n")
        out, d = run("stmt_shift", text)
        self.assertEqual([p["stmt"] for p, _ in out if p["stmt"] == "a = 1;"], [])
        self.assertGreaterEqual(d["crosses-dep-data"], 1)

    # --- opening: the pure-local statement that may cross a call

    def test_pure_local_crosses_a_call(self):
        text = fn("void *records", "    void *r;\n    s32 a;\n"
                                   "    r = records;\n    a = g(1);\n    a = h(2);\n")
        ins, _ = only("stmt_shift", text, "pure_local_2_down")
        self.assertTrue(ins)
        p, t = ins[0]
        self.assertEqual((p["stmt"], p["pure_local"]), ("r = records;", True))
        body = [l.strip() for l in t.splitlines() if l.strip().endswith(";")
                and not l.strip().startswith(("void", "s32"))]
        self.assertEqual(body, ["a = g(1);", "a = h(2);", "r = records;"])

    def test_pure_local_is_the_only_k_equals_one(self):
        text = fn("void", "    s32 a;\n    s32 b;\n    b = 1;\n    g(a);\n")
        ins, _ = only("stmt_shift", text, "pure_local_1_down")
        self.assertTrue(ins)
        self.assertEqual(ins[0][0]["k"], 1)
        for p, _ in run("stmt_shift", SH)[0]:            # no call anywhere: k == 1 stays out
            self.assertGreaterEqual(p["k"], P.MIN_SHIFT)

    def test_pure_local_refuses_a_global_or_an_address_taken_local(self):
        locs, taken = {"a", "b"}, {"b"}
        self.assertTrue(P._pure_local_stmt("    a = b + 1;", locs, set()))
        self.assertTrue(P._pure_local_stmt("    a = (s32)b;", locs, set()))
        self.assertFalse(P._pure_local_stmt("    a = D_800F93AA;", locs, set()))   # a global read
        self.assertFalse(P._pure_local_stmt("    a = b;", locs, taken))            # b is addressed
        self.assertFalse(P._pure_local_stmt("    b = a;", locs, taken))            # b is addressed
        self.assertFalse(P._pure_local_stmt("    a = p->f;", locs, set()))
        self.assertFalse(P._pure_local_stmt("    a = g(b);", locs, set()))
        self.assertFalse(P._pure_local_stmt("    a = &b;", locs, set()))
        self.assertFalse(P._pure_local_stmt("    *a = b;", locs, set()))

    def test_an_address_taken_local_may_not_cross_a_call(self):
        text = fn("void", "    s32 a;\n    s32 b;\n    h(&b);\n    b = 1;\n    g(a);\n    g(a);\n")
        out, d = run("stmt_shift", text)
        self.assertEqual([p["stmt"] for p, _ in out if p["stmt"] == "b = 1;"], [])
        self.assertGreaterEqual(d["crosses-call"], 1)

    def test_refuse_crossing_a_store_that_may_alias(self):
        # the alias test adjacent_swap added, applied to every crossed statement in turn
        text = fn("s32 *p", "    s32 a;\n    s32 b;\n"
                            "    a = p[0];\n    p[1] = 1;\n    b = 2;\n    b = 3;\n")
        out, d = run("stmt_shift", text)
        self.assertEqual([q["stmt"] for q, _ in out if q["stmt"].startswith("a =")], [])
        self.assertGreaterEqual(d["crosses-dep-mem-alias"] + d["crosses-dep-data"], 1)


# --------------------------------------------------------------------------- page_local

PL = fn("void", "    s32 a;\n    a = D_800D1234;\n    D_800D5678 = a;\n    g(D_800D1234);\n")


class PageLocal(unittest.TestCase):
    def test_move(self):
        ins, _ = only("page_local", PL, "unsigned")
        self.assertEqual(len(ins), 1)
        p, t = ins[0]
        self.assertEqual(p["page"], "0x800D0000")
        self.assertEqual(p["uses"], 3)
        self.assertIn("    u8 *page;\n", t)
        self.assertIn("    page = (u8 *)0x800D0000;\n", t)
        self.assertIn("(*(__typeof__(D_800D1234) *)(page + 0x1234))", t)
        self.assertIn("(*(__typeof__(D_800D5678) *)(page + 0x5678))", t)
        self.assertLess(t.index("u8 *page;"), t.index("page = (u8 *)"))

    def test_the_signed_base_is_the_next_boundary_with_negative_offsets(self):
        # both symbols sit in the page's UPPER half, so `addiu`'s signed immediate reaches them
        # from the boundary above - the form the landed t54 rows' m2c text carries
        text = fn("void", "    s32 a;\n    a = D_800DF234;\n    D_800DE678 = a;\n    g(D_800DF234);\n")
        ins, _ = only("page_local", text, "signed")
        self.assertEqual(len(ins), 1)
        p, t = ins[0]
        self.assertEqual(p["page"], "0x800E0000")
        self.assertIn("    u32 page;\n", t)
        self.assertIn("    page = 0x800E0000;\n", t)
        self.assertIn("(*(__typeof__(D_800DF234) *)(page - 0xDCC))", t)    # 0x800E0000 - 0x800DF234
        self.assertIn("(*(__typeof__(D_800DE678) *)(page - 0x1988))", t)

    def test_the_signed_base_is_not_offered_below_the_immediate_range(self):
        # PL's symbols are at 0x800D1234 / 0x800D5678 - 0xEDCC and 0xA988 below the boundary above,
        # which no `addiu` reaches: the second instance is not offered at all
        ins, _ = only("page_local", PL, "signed")
        self.assertEqual(ins, [])
        self.assertEqual(len(only("page_local", PL, "unsigned")[0]), 1)

    def test_an_array_symbol_is_opened_and_a_function_symbol_refused(self):
        text = fn("void", "    s32 a;\n    a = D_800D1234[0];\n    a = D_800D5678;\n")
        ins, d = only("page_local", text, "unsigned")
        self.assertEqual(len(ins), 1)
        t = ins[0][1]
        self.assertIn("(*(__typeof__(D_800D1234) *)(page + 0x1234))[0]", t)
        self.assertEqual(d["symbol-used-as-array-or-function"], 0)
        self.assertEqual(ins[0][0]["n_array"], 1)
        d = P.Detail()
        out = P.page_local(fn("void", "    s32 a;\n    a = D_800D1234(1);\n    a = D_800D1234(2);\n"), d)
        self.assertEqual(out, [])
        self.assertEqual(d["symbol-used-as-a-function"], 2)

    def test_an_address_of_use_is_opened_with_the_symbol_s_own_pointer_type(self):
        text = fn("void", "    s32 a;\n    a = (s32)&D_800D1234;\n    a = (s32)&D_800D5678;\n")
        ins, d = only("page_local", text, "unsigned")
        self.assertEqual(len(ins), 1)
        t = ins[0][1]
        self.assertIn("a = (s32)((__typeof__(&D_800D1234))(page + 0x1234));", t)
        self.assertIn("a = (s32)((__typeof__(&D_800D5678))(page + 0x5678));", t)
        self.assertEqual(d["address-of-symbol"], 0)
        self.assertEqual(ins[0][0]["n_addr_of"], 2)

    def test_the_page_name_check_is_per_function(self):
        # another function's local `page` must not refuse this one (the file-wide scan did)
        text = (HEAD + "void other(void)\n{\n    u8 *page;\n    page = 0;\n    g(page);\n}\n\n"
                "void f(void)\n{\n    s32 a;\n    a = D_800D1234;\n    a = D_800D5678;\n}\n")
        ins, _ = only("page_local", text, "unsigned")
        self.assertEqual([p["fn"] for p, _ in ins], ["f"])
        self.assertEqual(ins[0][0]["name"], "page")
        # in the function that DOES spell it, a fresh name is used instead
        text2 = fn("void", "    u8 *page;\n    page = 0;\n    g(D_800D1234, D_800D5678);\n")
        ins2, _ = only("page_local", text2, "unsigned")
        self.assertEqual([p["name"] for p, _ in ins2], ["page2"])

    def test_refuse_single_use_page_and_an_exhausted_page_name(self):
        d = P.Detail()
        out = P.page_local(fn("void", "    s32 a;\n    a = D_800D1234;\n    a = D_800E5678;\n"), d)
        self.assertEqual(out, [])
        self.assertEqual(d["single-use-page"], 2)
        d = P.Detail()
        decls = "".join("    u8 *%s;\n" % n for n in ("page", "page2", "page3", "page4", "page5"))
        uses = "".join("    %s = 0;\n" % n for n in ("page", "page2", "page3", "page4", "page5"))
        out = P.page_local(fn("void", decls + uses + "    g(D_800D1234, D_800D5678);\n"), d)
        self.assertEqual(out, [])
        self.assertEqual(d["page-name-in-use"], 1)


# --------------------------------------------------------------------------- addr_literal

AL = fn("void", "    s32 a;\n    a = D_800D1234;\n    a = D_800D1234 + 1;\n"
                "    a = (s32)&D_80105678;\n")


class AddrLiteral(unittest.TestCase):
    def test_move(self):
        ins, _ = only("addr_literal", AL, "symbol")
        got = {p["symbol"]: t for p, t in ins}
        self.assertEqual(sorted(got), ["D_800D1234", "D_80105678"])
        t = got["D_800D1234"]
        self.assertIn("a = (*(__typeof__(D_800D1234) *)0x800D1234);", t)
        self.assertIn("a = (*(__typeof__(D_800D1234) *)0x800D1234) + 1;", t)
        self.assertIn("a = (s32)&D_80105678;", t)       # the other symbol is untouched
        self.assertEqual([p for p, _ in ins if p["symbol"] == "D_800D1234"][0]["uses"], 2)

    def test_an_address_use_takes_the_pointer_spelling(self):
        t = [t for p, t in only("addr_literal", AL, "symbol")[0]
             if p["symbol"] == "D_80105678"][0]
        self.assertIn("a = (s32)((__typeof__(&D_80105678))0x80105678);", t)

    def test_a_whole_page_instance_rewrites_every_symbol_of_the_page(self):
        text = fn("void", "    s32 a;\n    a = D_800D1234;\n    a = D_800D5678;\n    a = D_80105678;\n")
        ins, d = only("addr_literal", text, "page")
        self.assertEqual(len(ins), 1)
        p, t = ins[0]
        self.assertEqual(p["page"], "0x800D0000")
        self.assertIn("(*(__typeof__(D_800D1234) *)0x800D1234)", t)
        self.assertIn("(*(__typeof__(D_800D5678) *)0x800D5678)", t)
        self.assertIn("a = D_80105678;", t)             # the other page is untouched
        self.assertEqual(d["single-symbol-page"], 1)

    def test_refuse_a_function_symbol(self):
        d = P.Detail()
        out = P.addr_literal(fn("void", "    s32 a;\n    a = D_800D1234(1);\n"), d)
        self.assertEqual(out, [])
        self.assertEqual(d["symbol-is-a-function"], 1)

    def test_refuse_a_body_with_no_symbol(self):
        d = P.Detail()
        out = P.addr_literal(fn("void", "    s32 a;\n    a = 1;\n    g(a);\n"), d)
        self.assertEqual(out, [])
        self.assertEqual(d["no-page-symbols"], 1)


# --------------------------------------------------------------------------- the shared contract

TEXTS = [PC, DR, WC, AS, LA, PL, SH, AL]


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


class ReviewFixesStepTwo(unittest.TestCase):
    """The round-33 adversarial review of implementer C: five defects, each with the move it must
    still make beside the two shapes it must now refuse.  Every test here fails on the module as it
    stood before the fix (scratch/perturb_basic_C1.py)."""

    # --- BLOCKING 1: an initialised alias declaration above a `case` never runs
    SW = fn("Menu *menu",
            "    s32 pad;\n"
            "    pad = 0;\n"
            "    switch (menu->state)\n"
            "    {\n"
            "        case 0:\n"
            "            menu->state = menu->state + 1;\n"
            "            break;\n"
            "        case 1:\n"
            "            g(menu);\n"
            "            break;\n"
            "    }\n")

    def test_typed_init_refuses_a_slot_inside_a_switch_body(self):
        ins, d = run("local_alias", self.SW)
        for p, t in ins:
            self.assertNotIn(p["opening"], ("typed_init", "typed_init_void"),
                             "an initialised declaration was emitted for %s" % p["label"])
        self.assertTrue(d["typed-init:case-label-between-the-declaration-and-the-run"])
        # and no emitted text ever puts a declaration with an initialiser above the first label
        for _p, t in ins:
            lines = t.splitlines()
            for k, ln in enumerate(lines):
                if ln.strip().startswith("case 0:"):
                    self.assertNotIn("_alias =", lines[k - 1])

    def test_typed_init_refuses_a_case_label_on_the_block_s_own_brace_line(self):
        text = fn("Menu *menu",
                  "    s32 pad;\n"
                  "    pad = 0;\n"
                  "    switch (menu->state) { case 0:\n"
                  "            menu->state = menu->state + 1;\n"
                  "            g(menu);\n"
                  "            break;\n"
                  "    }\n")
        _ins, d = run("local_alias", text)
        self.assertTrue(d["typed-init:case-label-between-the-declaration-and-the-run"])

    def test_the_statement_spelling_still_reaches_a_switch_arm(self):
        # the plain `T alias;` + `alias = menu;` form is unaffected: the declaration carries no
        # initialiser, so a slot control skips costs nothing
        ins, _d = run("local_alias", self.SW)
        self.assertTrue([p for p, _ in ins if p["opening"] in ("base", "read_once")])

    def test_typed_init_is_still_emitted_in_an_ordinary_block(self):
        text = fn("Menu *menu",
                  "    s32 pad;\n"
                  "    pad = 0;\n"
                  "    menu->state = menu->state + 1;\n"
                  "    g(menu);\n")
        ins, _d = only("local_alias", text, "typed_init")
        self.assertTrue(ins)
        self.assertIn("Menu *menu_alias = menu;", ins[0][1])

    # --- BLOCKING 2: a page use above the line `page = ...` lands on
    def test_page_local_never_rewrites_a_use_above_its_own_assignment(self):
        text = fn("void",
                  "    S_A *primary = &D_8002E5D8;\n"
                  "    s32 a;\n"
                  "    a = D_8002E5E8;\n"
                  "    a = a + D_8002E5F8;\n")
        ins, d = only("page_local", text, "unsigned")
        self.assertEqual(len(ins), 1)
        t = ins[0][1]
        self.assertIn("S_A *primary = &D_8002E5D8;", t)        # the declaration is left alone
        self.assertEqual(d["use-above-the-page-assignment"], 1)
        # every rewritten use is below the assignment
        lines = t.splitlines()
        at = [k for k, ln in enumerate(lines) if "page = (u8 *)" in ln][0]
        for k, ln in enumerate(lines):
            if "page + 0x" in ln or "page - 0x" in ln:
                self.assertGreater(k, at, ln)

    def test_page_local_refuses_the_page_when_only_the_declaration_run_uses_it(self):
        text = fn("void",
                  "    S_A *primary = &D_8002E5D8;\n"
                  "    S_B *secondary = &D_8002E5E8;\n"
                  "    s32 a;\n"
                  "    a = 1;\n"
                  "    g(primary, secondary, a);\n")
        d = P.Detail()
        self.assertEqual(P.page_local(text, d), [])
        self.assertEqual(d["use-above-the-page-assignment"], 2)
        self.assertEqual(d["no-page-symbols"], 1)

    # --- BLOCKING 3: the bare `(page + off)` is a u8 * and steps in bytes
    def test_an_address_use_never_becomes_a_bare_byte_pointer(self):
        text = fn("void",
                  "    s32 *p;\n"
                  "    p = &D_80027F18 + 4;\n"
                  "    p = &D_800287CC;\n")
        for mode in ("unsigned", "signed"):
            ins, _d = only("page_local", text, mode)
            for _p, t in ins:
                self.assertNotIn("= (page + 0x", t)
                self.assertNotIn("= (page - 0x", t)
                self.assertIn("((__typeof__(&D_80027F18))(page", t)

    # --- MAJOR 4: a symbol rewritten inside its own in-body declaration
    def test_a_symbol_is_never_rewritten_in_its_own_declaration(self):
        text = fn("void",
                  "    s32 a;\n"
                  "    extern s32 D_8008DAB4;\n"
                  "    a = D_8008DAB4;\n"
                  "    a = a + D_8008DAC4;\n")
        for kind in ("addr_literal", "page_local"):
            ins, d = run(kind, text)
            self.assertTrue(ins, kind)
            for _p, t in ins:
                self.assertIn("extern s32 D_8008DAB4;", t, kind)
            self.assertTrue(d["symbol-in-its-own-declaration"], kind)

    def test_a_use_in_an_initialiser_is_still_rewritten(self):
        text = fn("void",
                  "    s32 a = D_8008DAB4;\n"
                  "    s32 b;\n"
                  "    b = D_8008DAC4;\n"
                  "    g(a, b);\n")
        ins, _d = only("addr_literal", text, "page")
        self.assertEqual(len(ins), 1)
        self.assertIn("s32 a = (*(__typeof__(D_8008DAB4) *)0x8008DAB4);", ins[0][1])

    # --- MAJOR 5: a struct MEMBER write renamed into the alias
    def test_local_alias_never_renames_a_struct_member_write(self):
        text = fn("void",
                  "    Work w;\n"
                  "    s32 a;\n"
                  "    a = w.count;\n"
                  "    w.first = 1;\n"
                  "    w.second = 2;\n"
                  "    g(a);\n")
        ins, d = run("local_alias", text)
        self.assertTrue(d["aggregate-source:used-with-a-member"])
        for _p, t in ins:
            self.assertIn("w.first = 1;", t)
            self.assertIn("w.second = 2;", t)
            self.assertNotIn("w_alias.first", t)
            self.assertNotIn("w_alias.second", t)

    def test_local_alias_never_copies_an_aggregate_nothing_has_written(self):
        # before the fix `w_alias = w;` went in at the top - copying an aggregate nothing had
        # written - and the two member writes below it were renamed into the copy
        text = fn("void",
                  "    Work w;\n"
                  "    s32 a;\n"
                  "    w.first = D_80020034;\n"
                  "    w.second = D_80020048;\n"
                  "    a = w.first;\n"
                  "    g(a);\n")
        ins, d = run("local_alias", text)
        self.assertEqual([p["label"] for p, _ in ins if p["var"] == "w"], [])
        self.assertTrue(d["aggregate-source:used-with-a-member"])
        for _p, t in ins:
            self.assertNotIn("w_alias", t)

    def test_writes_object_still_cuts_a_run_for_a_source_whose_type_reads_as_a_pointer(self):
        # the aggregate refusal reads `_declared_type`, which is not scope-aware (the reviewer's
        # latent hazard): where a shadowed declaration makes a struct read as a pointer, the member
        # write must STILL cut the run rather than be renamed into the copy
        ctx = P.Ctx(fn("void", "    s32 a;\n    a = w.count;\n    w.first = 1;\n    g(a);\n"))
        blk = P._straight_blocks(ctx, ctx.fns[0], minlen=1)
        self.assertTrue(blk)
        cut = [i for i in blk[0] if P._writes_object(ctx.code(i), "w")]
        self.assertEqual([ctx.code(i).strip() for i in cut], ["w.first = 1;"])

    def test_a_pointer_member_write_is_still_the_kind_s_own_move(self):
        # `v->f = x` writes the POINTEE: an alias that copies the pointer addresses the same object
        text = fn("Menu *menu",
                  "    s32 a;\n"
                  "    a = menu->count;\n"
                  "    menu->first = 1;\n"
                  "    g(a, menu);\n")
        ins, _d = only("local_alias", text, "base", var="menu")
        self.assertTrue(ins)
        self.assertIn("menu_alias->first = 1;", ins[0][1])

    def test_local_alias_refuses_an_aggregate_source(self):
        # slus/w_8004AA78: `packed_cursor = shuffle.indices;` - an ARRAY member decays to the
        # address of the array INSIDE the copy, so the pointer addresses a different object
        text = fn("void",
                  "    Buf shuffle;\n"
                  "    u8 *cursor;\n"
                  "    s32 n;\n"
                  "    cursor = shuffle.indices;\n"
                  "    n = shuffle.count;\n"
                  "    g(cursor, n);\n")
        ins, d = run("local_alias", text)
        self.assertEqual([p["label"] for p, _ in ins if p["var"] == "shuffle"], [])
        self.assertTrue(d["aggregate-source:used-with-a-member"])

    def test_a_pointer_source_is_not_an_aggregate(self):
        text = fn("Buf *shuffle",
                  "    u8 *cursor;\n"
                  "    s32 n;\n"
                  "    cursor = shuffle->indices;\n"
                  "    n = shuffle->count;\n"
                  "    g(cursor, n);\n")
        ins, _d = run("local_alias", text)
        self.assertTrue([p for p, _ in ins if p["var"] == "shuffle"])

    def test_the_page_assignment_goes_below_a_declaration_that_follows_a_comment(self):
        # main/func_800121A4: the mask keeps a block comment's `/*`, so the walk stopped at the
        # comment and the assignment landed ABOVE the declaration below it - a declaration after a
        # statement, which cc1 refuses
        text = fn("void",
                  "    s16 mode;\n"
                  "    /* D_80013714 and D_80010208 sit on the same 64K page; retail keeps\n"
                  "     * ONE lui live in a callee-saved register across both accesses.\n"
                  "     */\n"
                  "    u8 *global_page = (u8 *)0x80010000;\n"
                  "    mode = D_800D1234;\n"
                  "    mode = mode + D_800D5678;\n")
        ins, _d = only("page_local", text, "unsigned")
        self.assertEqual(len(ins), 1)
        lines = ins[0][1].splitlines()
        asg = [k for k, ln in enumerate(lines) if "page = (u8 *)0x800D0000;" in ln][0]
        decl = [k for k, ln in enumerate(lines) if "u8 *global_page" in ln][0]
        self.assertGreater(asg, decl)

    def test_writes_object_sees_the_member_chain_and_not_the_arrow(self):
        self.assertTrue(P._writes_object("w.first = 1;", "w"))
        self.assertTrue(P._writes_object("w.a.b = 1;", "w"))
        self.assertTrue(P._writes_object("w.arr[2] = 1;", "w"))
        self.assertTrue(P._writes_object("w.count++;", "w"))
        self.assertFalse(P._writes_object("p->first = 1;", "p"))
        self.assertFalse(P._writes_object("a = w.first;", "w"))
        self.assertFalse(P._writes_object("if (w.first == 1) {", "w"))
        self.assertFalse(P._writes_object("q.w.first = 1;", "w"))


if __name__ == "__main__":
    unittest.main()


# --------------------------------------------------------------------------- the __typeof__ declaration
# The round-33 two-move catalogue lost every hoist>param_copy / hoist>page_local / hoist>local_alias
# composition (99% NOBUILD): a `__typeof__(EXPR) name;` temporary at the end of the declaration run
# was read as a STATEMENT, so the second kind inserted its statement above it (report_run2.txt §4).

class TypeofDeclaration(unittest.TestCase):
    # the temporary names `n`, not `tile`: a declaration that reads the copied parameter is refused
    # on purpose (`declaration-initialiser-reads-the-parameter`), as on the real rows where the
    # hoisted expression and the copied parameter differ.
    TEXT = fn("u8 *tile, s32 n",
              "    s32 i;\n"
              "    __typeof__(n) hoisted_1;\n"
              "    hoisted_1 = n;\n"
              "    i = hoisted_1;\n"
              "    g(i, tile[0]);\n")

    def test_a_typeof_temporary_is_a_declaration(self):
        ctx = P.Ctx(self.TEXT)
        k = next(i for i, l in enumerate(ctx.lines) if "__typeof__" in l)
        self.assertTrue(ctx.is_decl(k))
        self.assertTrue(P._declarative(ctx, k))
        self.assertTrue(P.TYPEOF_DECL.match("    __typeof__(p->a) *q;"))
        self.assertTrue(P.TYPEOF_DECL.match("    __typeof__(v[0]) t[4];"))
        self.assertFalse(P.TYPEOF_DECL.match("    x = (__typeof__(y))z;"))
        self.assertFalse(P.TYPEOF_DECL.match("    hoisted_1 = tile[0];"))

    def test_param_copy_inserts_its_copy_below_the_typeof_temporary(self):
        ins, _ = run("param_copy", self.TEXT)
        t = {p["param"]: c for p, c in ins}["tile"]
        lines = [l.strip() for l in t.split("\n")]
        self.assertLess(lines.index("__typeof__(n) hoisted_1;"), lines.index("tile = tile_in;"))
        self.assertLess(lines.index("tile = tile_in;"), lines.index("hoisted_1 = n;"))
