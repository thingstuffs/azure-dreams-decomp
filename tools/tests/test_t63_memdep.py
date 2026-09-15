"""T63: the access-spelling flips resolve offsets from the row's own declarations, never invent a
struct type, and leave the emitted address arithmetic alone.

The last test is the only one that compiles: it takes the microcompile fixture's shape A
(`p->a = v; return G;`), flips the member to the byte cast T63 would emit, and asserts that the two
listings hold the SAME multiset of register-anonymised instructions (identical address arithmetic and
identical operations) while the ORDER differs - which is the whole mechanism (sched.c's
MEM_IN_STRUCT_P exemption).  It is skipped when the stock 2.7.2 compiler is not present.
"""
import collections
import re
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from xform import t63_memdep as M
from xform.screen import compile_s, sdiff

ROW = {"id": "dungeon/test", "container": "dungeon", "cfg": "2.7.2", "kind": "overlay",
       "c_path": "overlays/dungeon/first_pass_matched/func_test.c"}

HEAD = '#include "common.h"\n\n'

TYPED = HEAD + (
    "typedef struct S_A {\n"
    "    u8 pad_00[0x10];\n"
    "    s32 unk_10;\n"
    "    union { s16 s; u16 u; } unk_14;\n"
    "    u8 pad_16[0x2];\n"
    "    void * unk_18;\n"
    "} S_A;\n\n"
    "typedef struct S_B {\n"
    "    u8 pad_00[0x4];\n"
    "    S_A inner;\n"
    "} S_B;\n\n"
    "extern s32 D_80010000;\n\n"
    "void func_test(void *obj, s32 v) {\n"
    "    ASM_KEEP(v);\n"
    "    ((S_A *)obj)->unk_10 = v;\n"
    "    ((S_A *)obj)->unk_14.s = 1;\n"
    "    D_80010000 = ((S_A *)obj)->unk_10;\n"
    "}\n")

CASTED = HEAD + (
    "typedef struct S_A {\n"
    "    u8 pad_00[0x10];\n"
    "    s32 unk_10;\n"
    "    union { s16 s; u16 u; } unk_14;\n"
    "} S_A;\n\n"
    "void func_test(void *obj, s32 v) {\n"
    "    ASM_KEEP(v);\n"
    "    (*(s32 *)((u8 *)obj + 0x10)) = v;\n"
    "    (*(s16 *)((u8 *)obj + 0x14)) = 1;\n"
    "}\n")


def flips(text):
    skips = collections.Counter()
    structs = M.visible_structs(text)
    got = {label: cand for label, cand, _ in M.all_flips(text, structs, skips)}
    return got, skips


class Layout(unittest.TestCase):
    def test_offsets_and_nested_union(self):
        st = M.parse_structs(TYPED)
        table = {p: (o, t.spelling) for p, o, t in M.leaves(st["S_A"], st)}
        self.assertEqual(table["unk_10"], (0x10, "s32"))
        self.assertEqual(table["unk_14.s"], (0x14, "s16"))
        self.assertEqual(table["unk_14.u"], (0x14, "u16"))
        self.assertEqual(table["unk_18"], (0x18, "void *"))
        self.assertNotIn("pad_00", table)              # a member of array type is never flipped

    def test_nested_struct_member_offsets_sum(self):
        st = M.parse_structs(TYPED)
        table = {p: o for p, o, t in M.leaves(st["S_B"], st)}
        self.assertEqual(table["inner.unk_10"], 0x14)
        self.assertEqual(table["inner.unk_14.u"], 0x18)

    def test_union_view_pads_like_the_records_headers(self):
        text = HEAD + (
            "typedef struct Rec_T {\n"
            "    union { struct { s32 v; } at00_s32; struct { u8 pad[0x2]; s16 v; } at02_s16;\n"
            "            struct { u8 pad[0x3]; u8 v; } at03_u8; } unk_00;\n"
            "    union { void ** as_ppv; void * as_pv; } unk_04;\n"
            "} Rec_T;\n")
        st = M.parse_structs(text)
        table = {p: (o, t.spelling) for p, o, t in M.leaves(st["Rec_T"], st)}
        self.assertEqual(table["unk_00.at00_s32.v"], (0, "s32"))
        self.assertEqual(table["unk_00.at02_s16.v"], (2, "s16"))
        self.assertEqual(table["unk_00.at03_u8.v"], (3, "u8"))
        self.assertEqual(table["unk_04.as_ppv"], (4, "void **"))

    def test_plain_struct_tag_keeps_its_keyword_in_the_cast(self):
        """`struct S *m` is not `S *m`: dropping the keyword emitted uncompilable casts."""
        text = HEAD + ("struct S_ptr { s32 unk_00; };\n"
                       "typedef struct S_H { u16 field0; u8 pad_02[0x6]; struct S_ptr *field8; } S_H;\n"
                       "void func_test(void *e) {\n"
                       "    ASM_KEEP(e);\n"
                       "    func_other(((S_H *)e)->field8);\n"
                       "}\n")
        st = M.parse_structs(text)
        table = {p: (o, t.spelling) for p, o, t in M.leaves(st["S_H"], st)}
        self.assertEqual(table["field8"], (8, "struct S_ptr *"))
        got, _ = flips(text)
        cand = next(v for k, v in got.items() if k.startswith("m2c:"))
        self.assertIn("(*(struct S_ptr **)((u8 *)e + 8))", cand)

    def test_bitfield_and_unknown_type_are_not_laid_out(self):
        bits = M.parse_structs("typedef struct BF { int a : 3; int b : 5; } BF;")
        self.assertFalse(bits["BF"]["ok"])
        self.assertEqual(bits["BF"]["why"], "bitfield")
        unk = M.parse_structs("typedef struct U { NoSuchType first; s32 second; } U;")
        self.assertFalse(unk["U"]["ok"])
        self.assertEqual(unk["U"]["why"], "unresolved-struct")


class FlipDirections(unittest.TestCase):
    def test_member_to_cast(self):
        got, _ = flips(TYPED)
        cand = next(v for k, v in got.items() if k.startswith("m2c:") and "0x14" in k)
        self.assertIn("(*(s16 *)((u8 *)obj + 0x14)) = 1;", cand)
        self.assertNotIn("->unk_14.s = 1", cand)
        plain = next(v for k, v in got.items() if k.startswith("m2c:") and "0x10" in k)
        self.assertIn("(*(s32 *)((u8 *)obj + 0x10))", plain)

    def test_cast_to_member_prefers_a_visible_struct(self):
        got, _ = flips(CASTED)
        cand = next(v for k, v in got.items() if k.startswith("c2m:") and "unk_10" in k)
        self.assertIn("((S_A *)obj)->unk_10 = v;", cand)
        short = next(v for k, v in got.items() if k.startswith("c2m:") and "unk_14" in k)
        self.assertIn("((S_A *)obj)->unk_14.s = 1;", short)

    def test_round_trip_member_cast_member(self):
        got, _ = flips(TYPED)
        once = next(v for k, v in got.items() if k.startswith("m2c:") and "0x10" in k)
        back, _ = flips(once)
        again = next(v for k, v in back.items() if k.startswith("c2m:") and "unk_10" in k)
        self.assertIn("((S_A *)obj)->unk_10 = v;", again)

    def test_m2c_field_macro_is_recognised(self):
        text = HEAD + '#include "m2c_compat.h"\n' + (
            "typedef struct S_A { u8 pad_00[0x10]; s32 unk_10; } S_A;\n"
            "void func_test(void *obj, s32 v) {\n"
            "    ASM_KEEP(v);\n"
            "    M2C_FIELD(obj, s32 *, 0x10) = v;\n"
            "}\n")
        got, _ = flips(text)
        cand = next(v for k, v in got.items() if k.startswith("c2m:"))
        self.assertIn("((S_A *)obj)->unk_10 = v;", cand)
        self.assertNotIn("M2C_FIELD", cand.split("void func_test")[1])

    def test_cast_to_index_needs_no_struct_and_never_uses_index_zero(self):
        text = HEAD + ("void func_test(void *obj, s32 v) {\n"
                       "    ASM_KEEP(v);\n"
                       "    (*(s32 *)((u8 *)obj + 0xC)) = v;\n"
                       "    (*(s32 *)((u8 *)obj + 0)) = v;\n"
                       "}\n")
        got, skips = flips(text)
        self.assertIn("c2i:5:obj[3]", got)
        self.assertIn("((s32 *)obj)[3] = v;", got["c2i:5:obj[3]"])
        self.assertFalse([k for k in got if k.startswith("c2i:") and "[0]" in k])
        self.assertTrue(skips["no-struct-at-offset"] >= 2)

    def test_index_to_cast(self):
        text = HEAD + ("void func_test(void *obj, s32 v) {\n"
                       "    ASM_KEEP(v);\n"
                       "    ((s32 *)obj)[3] = v;\n"
                       "}\n")
        got, _ = flips(text)
        cand = next(v for k, v in got.items() if k.startswith("i2c:"))
        self.assertIn("(*(s32 *)((u8 *)obj + 0xC)) = v;", cand)

    def test_global_scalar_to_one_element_array_and_back(self):
        text = HEAD + ("extern s32 D_80010000;\n"
                       "void func_test(s32 v) {\n"
                       "    ASM_KEEP(v);\n"
                       "    D_80010000 = v;\n"
                       "}\n")
        got, _ = flips(text)
        cand = got["g2arr:D_80010000"]
        self.assertIn("extern s32 D_80010000[1];", cand)
        self.assertIn("D_80010000[0] = v;", cand)
        back, _ = flips(cand)
        self.assertIn("extern s32 D_80010000;", back["arr2g:D_80010000"])
        self.assertIn("D_80010000 = v;", back["arr2g:D_80010000"])

    def test_address_of_a_global_keeps_addressing_the_object(self):
        """`&G` must become `&G[0]`, and back: dropping or keeping the `&` wrongly changes the type."""
        scalar = HEAD + ("extern s32 D_80010000;\n"
                         "void func_test(void) {\n"
                         "    ASM_KEEP(D_80010000);\n"
                         "    func_other(&D_80010000, D_80010000);\n"
                         "}\n")
        cand = flips(scalar)[0]["g2arr:D_80010000"]
        self.assertIn("extern s32 D_80010000[1];", cand)
        self.assertIn("func_other(&D_80010000[0], D_80010000[0]);", cand)
        back = flips(cand)[0]["arr2g:D_80010000"]
        self.assertIn("extern s32 D_80010000;", back)
        self.assertIn("func_other(&D_80010000, D_80010000);", back)

    def test_global_array_element_to_cast(self):
        text = HEAD + ("extern s32 D_80010000[8];\n"
                       "void func_test(s32 v) {\n"
                       "    ASM_KEEP(v);\n"
                       "    D_80010000[2] = v;\n"
                       "}\n")
        got, _ = flips(text)
        cand = got["elem2cast:D_80010000[2]"]
        self.assertIn("(*(s32 *)((u8 *)D_80010000 + 8)) = v;", cand)
        # the declaration's own `[8]` is a dimension, not a subscript
        self.assertIn("extern s32 D_80010000[8];", cand)

    def test_a_dimension_of_eight_is_never_rewritten_as_a_subscript(self):
        text = HEAD + ("extern u8 D_80010000[8];\n"
                       "void func_test(u8 v) {\n"
                       "    ASM_KEEP(v);\n"
                       "    D_80010000[1] = v;\n"
                       "}\n")
        for label, cand, _ in M.all_flips(text):
            self.assertIn("extern u8 D_80010000[8];", cand, label)

    def test_group_flip_moves_every_access_of_one_base(self):
        got, _ = flips(TYPED)
        group = next(v for k, v in got.items() if k.startswith("group:m2c:base:obj"))
        self.assertNotIn("((S_A *)obj)->", group)
        self.assertEqual(group.count("(*(s32 *)((u8 *)obj + 0x10))"), 2)


class Skips(unittest.TestCase):
    def test_global_declared_in_an_include_is_skipped(self):
        head = HEAD + '#include "globals.h"\n'
        names = M._header_names(head)
        self.assertIn("D_800814C8", names)          # include/globals.h line 9
        text = head + ("extern int D_800814C8;\n"
                       "void func_test(s32 v) {\n"
                       "    ASM_KEEP(v);\n"
                       "    D_800814C8 = v;\n"
                       "}\n")
        got, skips = flips(text)
        self.assertFalse([k for k in got if k.startswith("g2arr:")])
        self.assertGreaterEqual(skips["global-in-include"], 1)

    def test_unresolvable_member_records_a_reason(self):
        text = HEAD + ("typedef struct S_A { u8 pad_00[0x10]; s32 unk_10; } S_A;\n"
                       "void func_test(void *obj, s32 v) {\n"
                       "    ASM_KEEP(v);\n"
                       "    ((S_A *)obj)->no_such_member = v;\n"
                       "}\n")
        got, skips = flips(text)
        self.assertFalse([k for k in got if k.startswith("m2c:")])
        self.assertEqual(skips["unresolved-member"], 1)

    def test_a_whole_struct_access_is_skipped_as_struct_typed(self):
        text = HEAD + ("typedef struct S_I { s32 a; s32 b; } S_I;\n"
                       "typedef struct S_O { u8 pad_00[0x4]; S_I sub; } S_O;\n"
                       "void func_test(void *obj, S_I v) {\n"
                       "    ASM_KEEP(v);\n"
                       "    ((S_O *)obj)->sub = v;\n"
                       "}\n")
        got, skips = flips(text)
        self.assertEqual(skips["struct-typed"], 1)
        self.assertFalse([k for k in got if k.startswith("m2c:")])

    def test_a_typedef_below_the_access_cannot_be_named(self):
        text = HEAD + ("void func_test(void *obj, s32 v) {\n"
                       "    ASM_KEEP(v);\n"
                       "    (*(s32 *)((u8 *)obj + 0x10)) = v;\n"
                       "}\n"
                       "typedef struct S_Late { u8 pad_00[0x10]; s32 unk_10; } S_Late;\n")
        got, skips = flips(text)
        self.assertGreaterEqual(skips["typedef-after-use"], 1)
        self.assertFalse([k for k in got if k.startswith("c2m:")])

    def test_variable_offset_and_array_member_are_skipped(self):
        text = HEAD + ("typedef struct S_A { u8 pad_00[0x10]; s32 unk_10[4]; } S_A;\n"
                       "void func_test(void *obj, s32 v, s32 i) {\n"
                       "    ASM_KEEP(v);\n"
                       "    (*(s32 *)((u8 *)obj + i)) = v;\n"
                       "    ((S_A *)obj)->unk_10[i] = v;\n"
                       "}\n")
        got, skips = flips(text)
        self.assertEqual(skips["variable-offset"], 1)
        self.assertEqual(skips["array-member"], 1)
        self.assertFalse(got)

    def test_address_of_and_port_arm_accesses_are_skipped(self):
        text = HEAD + ("typedef struct S_A { u8 pad_00[0x10]; s32 unk_10; } S_A;\n"
                       "void func_test(void *obj, s32 v) {\n"
                       "    ASM_KEEP(v);\n"
                       "    func_other(&((S_A *)obj)->unk_10);\n"
                       "#ifdef NON_MATCHING\n"
                       "    ((S_A *)obj)->unk_10 = v;\n"
                       "#endif\n"
                       "}\n")
        got, skips = flips(text)
        self.assertEqual(skips["address-of"], 1)
        self.assertEqual(skips["in-unscored-arm"], 1)
        self.assertFalse([k for k in got if k.startswith("m2c:")])

    def test_struct_local_is_only_flipped_when_its_address_is_already_taken(self):
        body = ("typedef struct S_A { s32 unk_00; s32 unk_04; } S_A;\n"
                "void func_test(s32 v) {\n"
                "    S_A local;\n"
                "    ASM_KEEP(v);\n"
                "    local.unk_04 = v;\n"
                "%s"
                "}\n")
        got, skips = flips(HEAD + body % "")
        self.assertEqual(skips["local-not-addressed"], 1)
        self.assertFalse([k for k in got if k.startswith("m2c:")])
        got, _ = flips(HEAD + body % "    func_other(&local);\n")
        cand = next(v for k, v in got.items() if k.startswith("m2c:"))
        self.assertIn("(*(s32 *)((u8 *)&local + 4)) = v;", cand)


class Qualifiers(unittest.TestCase):
    """A flip may never DROP or ADD `volatile`/`const`.

    The screen cannot catch it (cc1's listing is often byte-identical across the qualifier) and `vf`
    only checks retail bytes, so a landed row would silently lose a qualifier the record census
    recorded.  Shapes here follow the real corpus: include/records-style union views with
    `volatile` leaves, as in dungeon/func_80AD7000's S_80AD7000_2."""

    VOL = HEAD + (
        "typedef struct S_V {\n"
        "    s32 unk_00;\n"
        "    union { struct { s32 v; } at00_s32; struct { volatile u8 v; } at00u;\n"
        "            struct { u8 pad[0x1]; volatile u8 v; } at01; } unk_04;\n"
        "    const s32 unk_08;\n"
        "} S_V;\n\n"
        "void func_test(void *p, s32 v) {\n"
        "    ASM_KEEP(v);\n"
        "    ((S_V *)p)->unk_04.at00u.v = 1;\n"
        "}\n")

    def test_leaves_carry_the_member_qualifier(self):
        st = M.parse_structs(self.VOL)
        table = {p: (o, t.spelling) for p, o, t in M.leaves(st["S_V"], st)}
        self.assertEqual(table["unk_04.at00_s32.v"], (4, "s32"))
        self.assertEqual(table["unk_04.at00u.v"], (4, "volatile u8"))
        self.assertEqual(table["unk_04.at01.v"], (5, "volatile u8"))
        self.assertEqual(table["unk_08"], (8, "const s32"))

    def test_volatile_member_flips_to_a_volatile_cast(self):
        got, _ = flips(self.VOL)
        cand = next(v for k, v in got.items() if k.startswith("m2c:"))
        self.assertIn("(*(volatile u8 *)((u8 *)p + 4)) = 1;", cand)

    def test_a_qualified_aggregate_member_propagates_to_its_leaves(self):
        text = HEAD + (
            "typedef struct S_Q {\n"
            "    u8 pad_00[0x4];\n"
            "    volatile struct { s32 a; } sub;\n"
            "} S_Q;\n\n"
            "void func_test(void *p, s32 v) {\n"
            "    ASM_KEEP(v);\n"
            "    ((S_Q *)p)->sub.a = v;\n"
            "}\n")
        st = M.parse_structs(text)
        self.assertEqual({p: t.spelling for p, o, t in M.leaves(st["S_Q"], st)}["sub.a"],
                         "volatile s32")
        got, _ = flips(text)
        cand = next(v for k, v in got.items() if k.startswith("m2c:"))
        self.assertIn("(*(volatile s32 *)((u8 *)p + 4)) = v;", cand)

    def test_a_plain_cast_never_becomes_a_volatile_member(self):
        text = HEAD + (
            "typedef struct S_V { s32 unk_00; volatile s32 unk_04; } S_V;\n"
            "void func_test(void *p, s32 v) {\n"
            "    ASM_KEEP(v);\n"
            "    (*(s32 *)((u8 *)p + 4)) = v;\n"
            "}\n")
        got, skips = flips(text)
        self.assertFalse([k for k in got if k.startswith("c2m:")])
        self.assertGreaterEqual(skips["no-struct-at-offset"], 1)

    def test_a_volatile_cast_does_become_the_volatile_member(self):
        text = HEAD + (
            "typedef struct S_V { s32 unk_00; volatile s32 unk_04; } S_V;\n"
            "void func_test(void *p, s32 v) {\n"
            "    ASM_KEEP(v);\n"
            "    (*(volatile s32 *)((u8 *)p + 4)) = v;\n"
            "}\n")
        got, _ = flips(text)
        cand = next(v for k, v in got.items() if k.startswith("c2m:"))
        self.assertIn("((S_V *)p)->unk_04 = v;", cand)
        idx = next(v for k, v in got.items() if k.startswith("c2i:"))
        self.assertIn("((volatile s32 *)p)[1] = v;", idx)

    def test_m2c_field_macro_keeps_its_qualifier(self):
        text = HEAD + '#include "m2c_compat.h"\n' + (
            "typedef struct S_V { s32 unk_00; volatile u8 unk_04; } S_V;\n"
            "void func_test(void *p, u8 v) {\n"
            "    ASM_KEEP(v);\n"
            "    M2C_FIELD(p, volatile u8 *, 4) = v;\n"
            "}\n")
        got, _ = flips(text)
        cand = next(v for k, v in got.items() if k.startswith("c2m:"))
        self.assertIn("((S_V *)p)->unk_04 = v;", cand)
        self.assertNotIn("M2C_FIELD", cand.split("void func_test")[1])

    def test_a_volatile_global_array_element_casts_to_a_volatile_pointer(self):
        """dungeon/func_8008A31C's `extern volatile u8 D_800DD0C8[8];` shape."""
        text = HEAD + ("extern volatile u8 D_800DD0C8[8];\n"
                       "void func_test(u8 v) {\n"
                       "    ASM_KEEP(v);\n"
                       "    D_800DD0C8[2] = v;\n"
                       "}\n")
        got, _ = flips(text)
        cand = got["elem2cast:D_800DD0C8[2]"]
        self.assertIn("(*(volatile u8 *)((u8 *)D_800DD0C8 + 2)) = v;", cand)
        self.assertIn("extern volatile u8 D_800DD0C8[8];", cand)

    def test_a_volatile_global_scalar_keeps_its_qualifier_on_the_array_flip(self):
        text = HEAD + ("extern volatile s32 D_80012BCC;\n"
                       "void func_test(s32 v) {\n"
                       "    ASM_KEEP(v);\n"
                       "    D_80012BCC = v;\n"
                       "}\n")
        got, _ = flips(text)
        self.assertIn("extern volatile s32 D_80012BCC[1];", got["g2arr:D_80012BCC"])
        self.assertIn("D_80012BCC[0] = v;", got["g2arr:D_80012BCC"])

    def test_a_qualified_base_declaration_is_skipped(self):
        """`volatile S *p`: every member reached through p inherits the qualifier."""
        text = HEAD + (
            "typedef struct S_A { s32 unk_00; s32 unk_04; } S_A;\n"
            "void func_test(volatile S_A *p, s32 v) {\n"
            "    ASM_KEEP(v);\n"
            "    p->unk_04 = v;\n"
            "}\n")
        got, skips = flips(text)
        self.assertEqual(skips["qualified-base"], 1)
        self.assertFalse([k for k in got if k.startswith("m2c:")])

    def test_a_volatile_member_does_not_poison_a_base_of_the_same_name(self):
        """The declaration regexes also match inside a struct body: `struct { volatile u8 v; }`
        must not put `v` in the qualified-base set and silence an unrelated pointer called `v`."""
        text = HEAD + (
            "typedef struct S_V { s32 unk_00; struct { volatile u8 v; } unk_04; } S_V;\n"
            "void func_test(S_V *v, s32 x) {\n"
            "    ASM_KEEP(x);\n"
            "    v->unk_00 = x;\n"
            "}\n")
        structs = M.visible_structs(text)
        self.assertEqual(M.qualified_bases(M._strip_comments(text), structs), set())
        got, skips = flips(text)
        self.assertEqual(skips.get("qualified-base", 0), 0)
        cand = next(v for k, v in got.items() if k.startswith("m2c:"))
        self.assertIn("(*(s32 *)((u8 *)v + 0)) = x;", cand)

    def test_a_flip_preserves_the_resolved_type_of_the_access(self):
        """The invariant: re-resolving the flipped access must give back the SAME type spelling,
        qualifiers included.  A dropped or added `volatile` shows up here and nowhere else - the cc1
        listing can be byte-identical across it and `vf` only checks retail bytes."""
        for src in (self.VOL, TYPED, CASTED):
            structs = M.visible_structs(src)
            sk = collections.Counter()
            for a in M.find_accesses(src, structs, sk):
                for label, rep in M.flips_of(src, a, structs, sk):
                    cand = M._apply(src, [(a.start, a.end, rep)])
                    back = {(x.base, x.off): x.type.spelling for x in
                            M.find_accesses(cand, M.visible_structs(cand), collections.Counter())}
                    self.assertIn((a.base, a.off), back, label)
                    self.assertEqual(back[(a.base, a.off)], a.type.spelling, label)


class WindowAfterErasure(unittest.TestCase):
    """erase_many DELETES lines, so the pin's line number in the un-erased text is stale."""

    def test_map_line_follows_a_deleted_line(self):
        old = "a\nb\nc\nd\ne\n"
        new = "a\nc\nd\ne\n"                    # line 2 deleted
        self.assertEqual(M.map_line(old, new, 1), 1)
        self.assertEqual(M.map_line(old, new, 3), 2)
        self.assertEqual(M.map_line(old, new, 5), 4)
        self.assertEqual(M.map_line(old, new, 2), 2)   # the deleted line maps to what now sits there
        self.assertEqual(M.map_line(old, old, 4), 4)

    def test_map_line_on_a_real_erasure_plan(self):
        from pin_sites import erase_many
        text = (HEAD + "typedef struct S_A { s32 unk_00; s32 unk_04; } S_A;\n"
                "void func_test(void *obj, s32 v) {\n"
                "    ASM_KEEP(v);\n"
                "    ASM_KEEP(v);\n"
                + "    func_other(v);\n" * 6
                + "    ((S_A *)obj)->unk_04 = v;\n}\n")
        plans = M.erasure_plans(text)
        label, chosen, anchor = next(p for p in plans if p[0].startswith("pins"))
        base = erase_many(text, chosen, clean_notes=True)
        removed = len(text.splitlines()) - len(base.splitlines())
        self.assertGreaterEqual(removed, 2)
        acc = M.find_accesses(base)
        self.assertEqual(len(acc), 1)
        banchor = M.map_line(text, base, anchor)
        # the access is inside the window once the anchor is mapped, outside it if it is not
        self.assertLessEqual(abs(acc[0].line - banchor), M.WINDOW)
        self.assertGreater(abs(acc[0].line - anchor), 0)

    def test_the_search_uses_the_erased_texts_own_window(self):
        """Two pins on consecutive lines, the only access 8 lines below the SECOND: reachable only
        when the window is re-centred on the erased text."""
        text = (HEAD + "typedef struct S_A { s32 unk_00; s32 unk_04; } S_A;\n"
                "void func_test(void *obj, s32 v) {\n"
                "    ASM_KEEP(v);\n"
                "    ASM_KEEP(v);\n"
                + "    func_other(v);\n" * 8
                + "    ((S_A *)obj)->unk_04 = v;\n}\n")
        seen = []

        def vf(cand, cfg=None):
            seen.append(cand)
            return {"exact": True}
        real = M.compile_s
        M.compile_s = lambda row, t: ["ref"]
        try:
            new, log = M.T.apply_verified(text, ROW, {}, vf)
        finally:
            M.compile_s = real
        self.assertIsNotNone(new)
        self.assertIn("(*(s32 *)((u8 *)obj + 4))", new)


class Menu(unittest.TestCase):
    def test_menu_is_bounded_and_nearest_pin_first(self):
        lines = ["#include \"common.h\"",
                 "typedef struct S_A { s32 unk_00; s32 unk_04; s32 unk_08; } S_A;",
                 "void func_test(void *obj, s32 v) {"]
        for i in range(60):
            lines.append("    ((S_A *)obj)->unk_%02X = v;" % (4 * (i % 3)))
        lines.insert(40, "    ASM_KEEP(v);")
        text = "\n".join(lines) + "\n}\n"
        menu = M.memdep_candidates(text)
        self.assertLessEqual(len(menu), M.MENU_CAP)
        self.assertTrue(all(isinstance(x, tuple) and len(x) == 2 for x in menu))
        self.assertTrue(all(l.startswith("memdep:") for l, _ in menu))
        self.assertEqual(len({c for _, c in menu}), len(menu))
        first_line = int(menu[0][0].split(":")[2])
        self.assertLessEqual(abs(first_line - 41), 2)

    def test_menu_on_a_pin_free_text_still_yields_flips(self):
        text = TYPED.replace("    ASM_KEEP(v);\n", "")
        self.assertTrue(M.memdep_candidates(text))

    def test_no_scaffolding_is_ever_emitted(self):
        for src in (TYPED, CASTED):
            for label, cand, _ in M.all_flips(src):
                extra = cand.replace(src, "")
                for bad in ("__asm__", "do {", "while (0)", "for (;0;)", "#pragma",
                            "__attribute__"):
                    self.assertNotIn(bad, cand, "%s emitted %s" % (label, bad))
                self.assertEqual(cand.count("ASM_"), src.count("ASM_"))
                # `volatile` is not scaffolding but a type qualifier: a flip must neither introduce
                # one nor lose one, so the count is conserved rather than forbidden.
                self.assertEqual(cand.count("volatile"), src.count("volatile"), label)
                self.assertEqual(cand.count("const"), src.count("const"), label)


class SearchLoop(unittest.TestCase):
    """The erase-flip-screen-verify plumbing, with the compiler stubbed out."""

    def run_with(self, screen, pred, text=TYPED):
        stub = {"calls": 0, "texts": []}

        def vf(cand, cfg=None):
            stub["calls"] += 1
            stub["texts"].append(cand)
            return {"exact": bool(pred(cand))}

        real = M.compile_s
        M.compile_s = lambda row, t: screen(t)
        try:
            return M.T.apply_verified(text, ROW, {}, vf) + (stub,)
        finally:
            M.compile_s = real

    def test_a_distance_zero_flip_is_verified_and_kept(self):
        target = "(*(s32 *)((u8 *)obj + 0x10)) = v;"

        def screen(t):
            return ["ref"] if ("ASM_KEEP" in t or target in t) else ["ref", "other"]
        new, log, stub = self.run_with(screen, lambda t: target in t)
        self.assertIsNotNone(new)
        self.assertIn(target, new)
        self.assertNotIn("ASM_KEEP", new)
        self.assertEqual(log["pins_out"], log["pins_in"] - 1)
        self.assertEqual(stub["calls"], 1)
        self.assertTrue(log["steps"][0].startswith("pin0+m2c:"))
        self.assertTrue(log["erasures"] and log["erasures"][0]["d0"] > 0)

    def test_the_search_restarts_after_a_win(self):
        """The 3-fence win on town/func_8080E994 needed three successive flips on one text."""
        text = (HEAD + "typedef struct S_A { s32 unk_00; s32 unk_04; } S_A;\n"
                + "void func_test(void *obj, s32 v) {\n"
                + "    ASM_KEEP(v);\n    ((S_A *)obj)->unk_00 = v;\n"
                + "    func_other(v);\n" * 12
                + "    ASM_KEEP(v);\n    ((S_A *)obj)->unk_04 = v;\n}\n")
        new, log, stub = self.run_with(lambda t: ["ref"], lambda t: True, text)
        self.assertIsNotNone(new)
        self.assertEqual(len(log["steps"]), 2)
        self.assertEqual(log["pins_out"], 0)
        self.assertNotIn("ASM_KEEP", new)

    def test_a_failed_verify_is_not_retried_on_an_identical_listing(self):
        new, log, stub = self.run_with(lambda t: ["ref"], lambda t: False)
        self.assertIsNone(new)
        self.assertEqual(stub["calls"], 1)
        self.assertGreaterEqual(log["skips"].get("same-listing-as-a-failed-verify", 0), 1)

    def test_no_candidate_at_distance_zero_spends_no_verify(self):
        new, log, stub = self.run_with(lambda t: ["ref"] if "ASM_KEEP" in t else ["a", "b"],
                                       lambda t: True)
        self.assertIsNone(new)
        self.assertEqual(stub["calls"], 0)
        self.assertGreater(log["screened"], 0)
        self.assertEqual(log["tried"], 0)

    def test_budgets_are_honoured(self):
        os_env = M.os.environ
        os_env["T63_SCREENS"] = "3"
        try:
            new, log, stub = self.run_with(lambda t: ["a"] if "ASM_KEEP" in t else ["b"],
                                           lambda t: True)
        finally:
            del os_env["T63_SCREENS"]
        self.assertIsNone(new)
        self.assertEqual(log["screened"], 3)
        self.assertGreaterEqual(log["skips"].get("budget", 0), 1)

    def test_a_build_error_is_counted_not_raised(self):
        new, log, stub = self.run_with(lambda t: ["ref"] if "ASM_KEEP" in t else None,
                                       lambda t: True)
        self.assertIsNone(new)
        self.assertGreater(log["compile_failures"], 0)
        self.assertEqual(log["skips"].get("compile-fail"), log["compile_failures"])


class Codegen(unittest.TestCase):
    """The flip must be a pure spelling change: same instructions, different order."""

    def setUp(self):
        if not (ROOT / "toolchain/compilers/gcc-2.7.2/cc1").is_file():
            self.skipTest("stock gcc 2.7.2 is not present")

    def test_member_and_cast_spellings_share_one_instruction_multiset(self):
        fixture = (ROOT / "tools/fixtures/memdep/memdep.c").read_text()
        head = "typedef unsigned char u8;\n" + fixture.split("/* A:")[0]
        member = head + "int fA(S *p, int v) { p->a = v; return G; }\n"
        access = M.find_accesses(member)
        self.assertEqual(len(access), 1)
        label, rep = M.flips_of(member, access[0], M.visible_structs(member), collections.Counter())[0]
        self.assertTrue(label.startswith("m2c:"))
        cast = M._apply(member, [(access[0].start, access[0].end, rep)])
        self.assertIn("(*(int *)((u8 *)p + 0))", cast)
        a, b = compile_s(ROW, member), compile_s(ROW, cast)
        self.assertIsNotNone(a)
        self.assertIsNotNone(b)
        anon = lambda ls: [re.sub(r"\$\w+", "$R", s) for s in ls]
        self.assertEqual(collections.Counter(anon(a)), collections.Counter(anon(b)),
                         "the flip changed the operations, not only their order")
        self.assertNotEqual(a, b, "the flip moved nothing: the fixture shape A no longer applies")
        self.assertGreater(sdiff(a, b), 0)


if __name__ == "__main__":
    unittest.main()
