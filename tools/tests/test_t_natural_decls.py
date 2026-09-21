"""natural's declaration reader (round 68).

Two families of defect, both measured over the 1,123 pinned rows before the fix:

  * `VDECL_RE` let the run between the base type and the name be EMPTY, so an ordinary statement
    read as a declaration - `dx = -dx;` as an `x` of type `d`, `divisor = 10;` as an `r` of type
    `diviso`.  28,488 body lines over the pinned rows matched that way (t83's `_locals` and t66's
    rescan apply it line by line, outside any declaration prologue).
  * `_block_decls` stopped a block's prologue at the first line `_DECL_START_RE` could not spell,
    and that regex knew neither `static void *const item_targets[7] = {` (the computed-goto label
    table, 1,778 hidden declarations), nor `void (*handler)(s32);` (432), nor
    `union { ... } slot;` (334), nor `s16 v[10][6][3];` (80).  Each of them hid EVERY declaration
    below it in its block - 18 functions came back with no declarations at all.

The file name matches the suite's `test_t*.py` discovery pattern on purpose.
"""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import natural as N  # noqa: E402


def fn(text):
    return list(N._functions(N._T(text)))[0]


def decls(text):
    return {d["name"]: d for ds in fn(text).decls.values() for d in ds}


LABEL_TABLE = '''#include "common.h"

void func_test(u8 *arg0) {
    static void *const item_targets[7] = {
        &&L0, &&after_first, &&after_first,
        &&L4, &&after_first, &&after_first,
        &&L4
    };
    s32 texture_base;
    register void *upload_data ASM_REG("$5");   /* UNRESOLVED C shape (pin) */
    s32 next_tick;

    texture_base = arg0[0];
    next_tick = texture_base + 1;
    upload_data = arg0 + next_tick;
    goto *item_targets[next_tick];
L0:
L4:
after_first:
    return;
}
'''

FNPTR = '''#include "common.h"

void func_test(void *object) {
    M2C_UNK (*update_actor)(void *, void *);
    s32 frame;

    frame = 0;
    update_actor = D_80083E98;
    update_actor(object, &frame);
}
'''

AGGREGATE = '''#include "common.h"

void func_test(void *object) {
    s32 sort_depth;
    struct { u16 a, b, c; } camera_angles;
    union { S_1 *pointer; s32 value; } effect_data;
    Vec4 shadow_scale;
    u8 *vertex0, *vertex1, *depth_out;

    sort_depth = 0;
    camera_angles.a = 1;
    effect_data.value = 2;
    shadow_scale.x = 3;
    vertex0 = vertex1 = depth_out = object;
}
'''


class VdeclSeparator(unittest.TestCase):
    """The base type and the name need a real separator: white space or a star run."""

    def test_a_negated_self_assignment_is_not_a_declaration(self):
        self.assertIsNone(N.VDECL_RE.match("    dx = -dx;"))

    def test_an_assignment_of_a_literal_is_not_a_declaration(self):
        self.assertIsNone(N.VDECL_RE.match("    divisor = 10;"))

    def test_the_whole_alphabet_of_plain_assignments_stays_out(self):
        for line in ("    table_base = (s32)D_80030000;", "    entry = (EntryT *)(index * 0x18);",
                     "    next_tick = texture_base + 1;", "    countdown = 0;"):
            self.assertIsNone(N.VDECL_RE.match(line), line)

    def test_a_keyword_can_never_be_the_base_type(self):
        for line in ("    return x;", "    goto top;", "    sizeof x;"):
            self.assertIsNone(N.VDECL_RE.match(line), line)
            self.assertIsNone(N._DECL_START_RE.match(line), line)

    def test_the_declarations_it_did_spell_are_unchanged(self):
        for line, name, ty in (("    s32 x;", "x", "s32"), ("    u8 *p;", "p", "u8*"),
                               ("    unsigned count;", "count", "unsigned"),
                               ("    register u8 *page ASM_REG(\"$7\");", "page", "u8*"),
                               ("    struct Actor *actor;", "actor", "struct Actor*"),
                               ("    s32 total = 3;", "total", "s32")):
            m = N.VDECL_RE.match(line)
            self.assertIsNotNone(m, line)
            self.assertEqual(m.group("n"), name)
            self.assertEqual(N._ptype(m.group("q").split(), m.group("base"), m.group("ptr")), ty)

    def test_a_starred_declarator_with_no_space_still_matches(self):
        m = N.VDECL_RE.match("    u8*p;")
        self.assertEqual((m.group("n"), m.group("ptr").strip()), ("p", "*"))


class LabelTable(unittest.TestCase):
    """`static void *const item_targets[7] = { ... };` no longer hides the run below it."""

    def test_every_declaration_below_the_table_is_read(self):
        d = decls(LABEL_TABLE)
        self.assertEqual(sorted(d), ["item_targets", "next_tick", "texture_base", "upload_data"])

    def test_the_table_itself_is_a_multi_line_declaration_natural_does_not_spell(self):
        d = decls(LABEL_TABLE)["item_targets"]
        self.assertFalse(d["single"])
        self.assertIsNone(d["ty"])
        self.assertEqual(d["line"], 3)
        self.assertEqual(d["end"], 7)                      # the `};` line, not the first `,`
        self.assertFalse(fn(LABEL_TABLE).usable(d))

    def test_the_pin_below_it_is_still_the_pinned_variable(self):
        F = fn(LABEL_TABLE)
        d = decls(LABEL_TABLE)["upload_data"]
        self.assertTrue(d["pinned"])
        self.assertIn(("upload_data", d["line"]), F.pinned)

    def test_a_body_that_is_only_a_label_table_parses(self):
        text = LABEL_TABLE[:LABEL_TABLE.index("    s32 texture_base;")] + "    return;\n}\n"
        self.assertEqual(sorted(decls(text)), ["item_targets"])

    def test_a_one_line_table_is_read_the_same_way(self):
        text = LABEL_TABLE.replace('''    static void *const item_targets[7] = {
        &&L0, &&after_first, &&after_first,
        &&L4, &&after_first, &&after_first,
        &&L4
    };''', "    static void *const item_targets[7] = { &&L0, &&L4 };")
        d = decls(text)
        self.assertIn("item_targets", d)
        self.assertEqual(d["item_targets"]["line"], d["item_targets"]["end"])
        self.assertIn("next_tick", d)


class OtherShapes(unittest.TestCase):

    def test_a_function_pointer_is_named_inside_its_parentheses(self):
        d = decls(FNPTR)
        self.assertEqual(sorted(d), ["frame", "update_actor"])
        self.assertFalse(d["update_actor"]["single"])

    def test_an_inline_aggregate_declares_its_variable_and_not_its_members(self):
        d = decls(AGGREGATE)
        self.assertEqual(sorted(d), ["camera_angles", "depth_out", "effect_data", "shadow_scale",
                                     "sort_depth", "vertex0", "vertex1"])

    def test_a_comma_list_below_an_aggregate_still_names_every_declarator(self):
        d = decls(AGGREGATE)
        self.assertEqual({d[n]["line"] for n in ("vertex0", "vertex1", "depth_out")}, {7})

    def test_a_multi_dimensional_array_does_not_stop_the_run(self):
        text = AGGREGATE.replace("    Vec4 shadow_scale;", "    s16 grid[10][6][3];\n    Vec4 shadow_scale;")
        d = decls(text)
        self.assertIn("grid", d)
        self.assertIn("shadow_scale", d)

    def test_an_extern_declaration_inside_a_body_does_not_stop_the_run(self):
        text = FNPTR.replace("    s32 frame;", "    extern s32 D_80083E98[];\n    s32 frame;")
        self.assertIn("frame", decls(text))


class StillStatements(unittest.TestCase):
    """The prologue must still END at the first statement: C89 is natural's model."""

    def test_a_declaration_below_the_first_statement_stays_invisible(self):
        text = AGGREGATE.replace("    camera_angles.a = 1;",
                                 "    camera_angles.a = 1;\n    register s32 third ASM_REG(\"$3\");")
        self.assertNotIn("third", decls(text))

    def test_a_wrapped_call_is_not_a_declaration(self):
        for line in ("    func_80024F3C(a,", "    foo(a, b);", "    *(s32 *)((u8 *)arg0 + 4) = 1;"):
            self.assertIsNone(N._DECL_START_RE.match(line), line)

    def test_a_declarator_spread_over_two_lines_still_reports_no_initialiser(self):
        """t66 reads `init=None` as `an initialiser natural could not spell`, and refuses on it."""
        text = FNPTR.replace("    s32 frame;", "    s32 frame =\n        3;")
        d = decls(text)["frame"]
        self.assertIsNone(d["init"])
        self.assertFalse(d["single"])
        self.assertEqual((d["line"], d["end"]), (4, 5))

    def test_an_aggregate_spread_over_lines_is_one_declaration(self):
        text = AGGREGATE.replace("    struct { u16 a, b, c; } camera_angles;",
                                 "    struct {\n        u16 a;\n        u16 b;\n    } camera_angles;")
        d = decls(text)
        self.assertIn("camera_angles", d)
        self.assertEqual((d["camera_angles"]["line"], d["camera_angles"]["end"]), (4, 7))
        self.assertIn("shadow_scale", d)
        # a brace pair is a block to natural, so the members land in the aggregate's own block and
        # never in the function body's declaration list
        self.assertEqual(d["a"]["block"], (4, 7))
        self.assertEqual(d["camera_angles"]["block"], fn(text).body)


class AttributeAndInitialiser(unittest.TestCase):
    """What a declaration natural cannot spell still has to report."""

    def test_the_attribute_spelling_of_the_table_keeps_its_own_name(self):
        text = LABEL_TABLE.replace("item_targets[7] = {", "item_targets[7] __attribute__((used)) = {")
        d = decls(text)
        self.assertIn("item_targets", d)
        self.assertNotIn("used", d)
        self.assertIn("texture_base", d)                   # and the run below it is still read

    def test_an_aggregate_reports_the_initialiser_it_carries(self):
        text = AGGREGATE.replace("} camera_angles;", "} camera_angles = {1, 2, 3};")
        self.assertIn("1, 2, 3", decls(text)["camera_angles"]["init"] or "")

    def test_a_static_table_reports_none_because_it_does_not_run_at_block_entry(self):
        self.assertIsNone(decls(LABEL_TABLE)["item_targets"]["init"])

    def test_a_wrapped_declarator_still_reports_none(self):
        text = FNPTR.replace("    s32 frame;", "    s32 frame =\n        3;")
        self.assertIsNone(decls(text)["frame"]["init"])

    def test_an_array_declarator_is_flagged_as_one(self):
        self.assertTrue(decls(LABEL_TABLE)["item_targets"]["arr"])
        self.assertFalse(decls(FNPTR)["update_actor"]["arr"])


ARM = '''#include "common.h"

void func_test(void *donor) {
    s32 owner_action;

    owner_action = *(s32 *)donor;
    if (owner_action == 1) {
#ifdef NON_MATCHING
        D_80010980[0] = 1;
#else
        u8 *room_page = (u8 *) 0x80010000;
        s32 room_index;

        room_index = 0;
        room_page[0x980 + room_index] = 1;
#endif
    }
}
'''


class MoreShapes(unittest.TestCase):

    def test_an_aggregate_whose_brace_opens_on_the_next_line(self):
        text = AGGREGATE.replace("    struct { u16 a, b, c; } camera_angles;",
                                 "  volatile struct\n  {\n    s32 sp10;\n    u16 sp18;\n  } sp;")
        d = decls(text)
        self.assertIn("sp", d)
        self.assertIn("shadow_scale", d)                   # the run below it is not hidden
        self.assertIn("effect_data", d)

    def test_the_slus_spelling_of_a_register_pin(self):
        text = FNPTR.replace("    s32 frame;",
                             "    register s32 special_type LOCAL_ASM_REG(\"$2\") = 0x38;\n    s32 frame;")
        d = decls(text)
        self.assertIn("special_type", d)
        self.assertTrue(d["special_type"]["pinned"])
        self.assertIn("frame", d)

    def test_a_pointer_to_an_array_does_not_stop_the_run(self):
        """`u16 (*points_base)[2] = points;` - spelled like a function pointer, declaring an array
        pointer (dungeon/func_818571BC, where it hid eleven declarations)."""
        text = FNPTR.replace("    s32 frame;", "    u16 (*points_base)[2] = D_80083160;\n    s32 frame;")
        d = decls(text)
        self.assertIn("points_base", d)
        self.assertIn("frame", d)

    def test_a_comma_list_carrying_an_initialiser_names_every_declarator(self):
        """`s32 notify_failure = 0, random_value;` - `VDECL_RE` spells it as ONE declarator whose
        initialiser is `0, random_value`, which loses the second name."""
        text = FNPTR.replace("    s32 frame;", "    s32 notify_failure = 0, random_value;\n    s32 frame;")
        d = decls(text)
        self.assertEqual(sorted(d), ["frame", "notify_failure", "random_value", "update_actor"])
        self.assertFalse(d["notify_failure"]["single"])

    def test_a_braced_initialiser_is_still_one_declarator(self):
        text = FNPTR.replace("    s32 frame;", "    s32 frame = 3;")
        self.assertEqual(decls(text)["frame"]["init"], "3")

    def test_a_function_scope_typedef_does_not_stop_the_run(self):
        """m2c writes one `typedef struct { ... } Local20;` per stack aggregate (the slus and
        dungeon families); it declares a type, not a local, and the locals stand below it."""
        text = FNPTR.replace("    s32 frame;",
                             "    typedef struct {\n        s16 unk0;\n        s32 unk4;\n    } Local20;\n"
                             "    Local20 sp20;\n    s32 frame;")
        d = decls(text)
        self.assertIn("sp20", d)
        self.assertIn("frame", d)
        self.assertNotIn("Local20", d)

    def test_a_declaration_opening_the_live_arm_is_read_over_the_dead_one(self):
        """The gate compiles the `#else` arm only, so the NON_MATCHING arm's statement does not end
        the block's declaration prologue."""
        d = decls(ARM)
        self.assertIn("room_page", d)
        self.assertIn("room_index", d)

    def test_a_declaration_in_the_dead_arm_is_not_read(self):
        text = ARM.replace("        D_80010980[0] = 1;", "        s32 unscored_local;")
        self.assertNotIn("unscored_local", decls(text))


class DeclNames(unittest.TestCase):

    def test_every_shape_the_fallback_has_to_name(self):
        self.assertEqual(N._decl_names("void (*handler)(s32 a, s32 b);"), ["handler"])
        self.assertEqual(N._decl_names("union { S_1 *p; s32 v; } effect_data;"), ["effect_data"])
        self.assertEqual(N._decl_names("static void *const keepalive[] = { &&L0, &&L1 };"), ["keepalive"])
        self.assertEqual(N._decl_names("u8 *a, *b, *c;"), ["a", "b", "c"])
        self.assertEqual(N._decl_names("s16 v[10][6][3];"), ["v"])
        self.assertEqual(N._decl_names("register s32 x ASM_REG(\"$4\");"), ["x"])
        self.assertEqual(N._decl_names("static void *const t[] __attribute__((used)) = { &&L0 };"), ["t"])
        self.assertEqual(N._decl_names("register s32 special_type LOCAL_ASM_REG(\"$2\") = 0x38;"), ["special_type"])
        self.assertEqual(N._decl_names("u16 (*points_base)[2] = points;"), ["points_base"])


if __name__ == "__main__":
    unittest.main()
