"""T78: run detection, element parsing, contiguity and the refusals are textual; the screen and `vf` are not
exercised (the exemplar rows are checked with tools/lanes/gen_drive.py)."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t78_aggcopy as M  # noqa: E402
from t29_addrsym import mask_comments  # noqa: E402

HEAD = '''#include "common.h"

typedef long long s64_local;

typedef struct DungeonSource {
    s32 word[6];
} DungeonSource;
'''

ARROW = HEAD + '''
void f(DungeonSource *arg1, DungeonSource *dst)
{
    s32 copy0;
    s32 copy1;
    s32 copy2;
    s32 copy3;

    copy0 = arg1->word[0];
    copy1 = arg1->word[1];
    copy2 = arg1->word[2];
    copy3 = arg1->word[3];
    dst->word[0] = copy0;
    dst->word[1] = copy1;
    dst->word[2] = copy2;
    dst->word[3] = copy3;
    copy0 = arg1->word[4];
    copy1 = arg1->word[5];
    dst->word[4] = copy0;
    dst->word[5] = copy1;
}
'''

DEREF = HEAD + '''
void g(void *src, void *out)
{
    s64_local part_xy;
    s32 part_z;
    s32 part_3;
    s32 part_4;
    s32 part_5;

    part_xy = (*(s64_local *)((u8 *)((void *)src) + 0));
    part_z = (*(s32 *)((u8 *)((void *)src) + 8));
    part_3 = (*(s32 *)((u8 *)((void *)src) + 0xC));
    (*(s64_local *)((u8 *)((void *)out) + 0)) = part_xy;
    (*(s32 *)((u8 *)((void *)out) + 8)) = part_z;
    (*(s32 *)((u8 *)((void *)out) + 0xC)) = part_3;
    part_4 = (*(s32 *)((u8 *)((void *)src) + 0x10));
    part_5 = (*(s32 *)((u8 *)((void *)src) + 0x14));
    (*(s32 *)((u8 *)((void *)out) + 0x10)) = part_4;
    (*(s32 *)((u8 *)((void *)out) + 0x14)) = part_5;
}
'''

AT_MACRO = HEAD + '''
void h(void *src, void *out)
{
    s32 w0;
    s32 w1;
    s32 w2;

    w0 = S32_AT(src, 0x20);
    w1 = S32_AT(src, 0x24);
    w2 = S32_AT(src, 0x28);
    S32_AT(out, 0x20) = w0;
    S32_AT(out, 0x24) = w1;
    S32_AT(out, 0x28) = w2;
}
'''


def body(stmts, decls="    s32 w0;\n    s32 w1;\n    s32 w2;\n"):
    return HEAD + "\nvoid k(void *src, void *out)\n{\n" + decls + "\n" + stmts + "}\n"


ROW = "    w0 = *(s32 *)((u8 *)src + 0);\n    w1 = *(s32 *)((u8 *)src + 4);\n    w2 = *(s32 *)((u8 *)src + 8);\n"
STO = "    *(s32 *)((u8 *)out + 0) = w0;\n    *(s32 *)((u8 *)out + 4) = w1;\n    *(s32 *)((u8 *)out + 8) = w2;\n"


class Memref(unittest.TestCase):
    def test_spellings(self):
        big = {"s64_local"}
        self.assertEqual(M.memref("arg1->word[3]", 4, big), ("arg1", 12, 4))
        self.assertEqual(M.memref("((S *)output)->unk_0C", 4, big), ("output", 12, 4))
        self.assertEqual(M.memref("((S *)output)->unk_04.at00.v", 4, big), ("output", 4, 4))
        self.assertEqual(M.memref("(*(s64_local *)((u8 *)((void *)p) + 0))", 4, big), ("p", 0, 8))
        self.assertEqual(M.memref("*(s32 *)((u8 *)src + 0xC)", 4, big), ("src", 12, 4))
        self.assertEqual(M.memref("S32_AT(base, 0x10)", 4, big), ("base", 16, 4))
        self.assertEqual(M.memref("p->field", 4, big), ("p", None, 4))       # offset unknown, still a reference

    def test_not_a_memref(self):
        self.assertIsNone(M.memref("obj", 4, set()))
        self.assertIsNone(M.memref("a + b", 4, set()))
        self.assertIsNone(M.memref("func(x)", 4, set()))

    def test_sizes(self):
        self.assertEqual(M.big_types(HEAD), {"long long", "unsigned long long", "s64", "u64", "s64_local"})
        self.assertEqual(M.type_size("s64_local", M.big_types(HEAD)), 8)
        self.assertEqual(M.type_size("u16", set()), 2)
        self.assertEqual(M.struct_size(HEAD, "DungeonSource", set()), 24)


class Runs(unittest.TestCase):
    def one(self, text):
        rs = M.runs(text)
        self.assertEqual(len(rs), 1, [r["src"] for r in rs])
        return rs[0]

    def test_arrow_run(self):
        r = self.one(ARROW)
        self.assertEqual((r["src"], r["dst"], r["size"]), ("arg1", "dst", 24))
        self.assertEqual(r["src_off"], 0)
        self.assertEqual(r["temps"], ["copy0", "copy1", "copy2", "copy3"])     # copy0/copy1 are reused
        self.assertEqual(sorted(t for t, _ in r["drop"]), ["copy0", "copy1", "copy2", "copy3"])
        forms = M.forms(ARROW, r, mask_comments(ARROW).split("\n"))
        self.assertEqual(forms[0][1], "*dst = *arg1;")                        # both sides one named struct
        self.assertEqual(forms[0][2], None)                                   # no typedef needed
        self.assertIn("*(Copy24 *)dst = *(Copy24 *)arg1;", [f[1] for f in forms])

    def test_mixed_width_deref_run(self):
        r = self.one(DEREF)
        self.assertEqual((r["src"], r["dst"], r["size"]), ("src", "out", 24))
        self.assertEqual([p[1][2] for p in r["pairs"]], [8, 4, 4, 4, 4])       # the 8-byte part tiles offset 0-7
        self.assertEqual(M.forms(DEREF, r, mask_comments(DEREF).split("\n"))[0][1],
                         "*(Copy24 *)out = *(Copy24 *)src;")

    def test_at_macro_and_offset_base(self):
        r = self.one(AT_MACRO)
        self.assertEqual((r["src_off"], r["dst_off"], r["size"]), (0x20, 0x20, 12))
        self.assertEqual(M.forms(AT_MACRO, r, mask_comments(AT_MACRO).split("\n"))[0][1],
                         "*(Copy12 *)((u8 *)out + 0x20) = *(Copy12 *)((u8 *)src + 0x20);")

    def test_rewrite_drops_declarations(self):
        r = self.one(ARROW)
        new, nblock = M.rewrite(ARROW, r, "*dst = *arg1;", None, "first")
        self.assertEqual(nblock, 1)
        self.assertNotIn("s32 copy0;", new)
        self.assertNotIn("copy3 = arg1->word[3];", new)
        self.assertIn("    *dst = *arg1;", new)


class Refusals(unittest.TestCase):
    def test_offsets_must_match(self):
        bad = body(ROW + "    *(s32 *)((u8 *)out + 0) = w0;\n    *(s32 *)((u8 *)out + 8) = w1;\n"
                         "    *(s32 *)((u8 *)out + 0xC) = w2;\n")
        self.assertEqual(M.runs(bad), [])

    def test_gap_in_offsets(self):
        gap = body("    w0 = *(s32 *)((u8 *)src + 0);\n    w1 = *(s32 *)((u8 *)src + 4);\n"
                   "    w2 = *(s32 *)((u8 *)src + 0xC);\n" + STO.replace("+ 8)", "+ 0xC)"))
        self.assertEqual(M.runs(gap), [])

    def test_same_base_is_not_a_copy(self):
        self.assertEqual(M.runs(body(ROW + STO.replace("out", "src"))), [])

    def test_too_short(self):
        short = body("    w0 = *(s32 *)((u8 *)src + 0);\n    w1 = *(s32 *)((u8 *)src + 4);\n"
                     "    *(s32 *)((u8 *)out + 0) = w0;\n    *(s32 *)((u8 *)out + 4) = w1;\n")
        self.assertEqual(M.runs(short), [])

    def test_foreign_statement_naming_a_temp_refuses(self):
        mid = ROW + "    w0 = w0 + 1;\n" + STO
        self.assertEqual(M.runs(body(mid)), [])

    def test_foreign_statement_breaks_the_run_when_it_is_a_block(self):
        mid = ROW + "    if (src != 0) {\n        w0 = 0;\n    }\n" + STO
        self.assertEqual(M.runs(body(mid)), [])

    def test_temp_read_after_the_run_keeps_its_load(self):
        after = body(ROW + STO + "    *(s32 *)((u8 *)out + 0x10) = w0 + 1;\n")
        r = M.runs(after)[0]
        self.assertEqual([t for t, _ in r["keep"]], ["w0"])               # still live: its declaration stays
        self.assertEqual(sorted(t for t, _ in r["drop"]), ["w1", "w2"])
        new, nblock = M.rewrite(after, r, "*(Copy12 *)out = *(Copy12 *)src;", None, "last")
        self.assertEqual(nblock, 2)
        self.assertIn("    w0 = *(s32 *)((u8 *)src + 0);", new)           # the surviving value is reloaded
        self.assertNotIn("w1 = ", new)
        self.assertLess(new.index("w0 = *(s32 *)"), new.index("*(Copy12 *)out"))

    def test_temp_rewritten_after_the_run_is_fine(self):
        after = body(ROW + STO + "    w0 = 3;\n    *(s32 *)((u8 *)out + 0x10) = w0;\n")
        self.assertEqual(len(M.runs(after)), 1)

    def test_preprocessor_arm_is_never_touched(self):
        arm = body("#ifndef NON_MATCHING\n" + ROW + STO + "#endif\n")
        self.assertEqual(M.runs(arm), [])

    def test_eligible_needs_a_pin(self):
        self.assertEqual(M.T.eligible(ARROW, {}, {}), "no pins")
        pinned = ARROW.replace("    s32 copy2;", '    register s32 copy2 ASM_REG("$5");')
        self.assertIsNone(M.T.eligible(pinned, {}, {}))
        self.assertEqual(M.T.eligible(pinned.replace("copy0 = arg1->word[0];", "copy0 = 0;"), {}, {}),
                         "no scalarized copy run")


class Typedefs(unittest.TestCase):
    def test_existing_typedef_is_reused(self):
        t = '#include "common.h"\n\ntypedef struct { s32 words[6]; } Copy24;\n'
        self.assertEqual(M.typedef_name(t, 24), ("Copy24", False))

    def test_wrong_size_typedef_gets_another_name(self):
        t = '#include "common.h"\n\ntypedef struct { s32 words[4]; } Copy24;\n'
        self.assertEqual(M.typedef_name(t, 24), ("AggCopy24", True))

    def test_insert_goes_after_the_includes(self):
        t = '#include "common.h"\n#include "records/x.h"\n\nvoid f(void);\n'
        out = M.insert_typedef(t, "Copy24", 24).split("\n")
        self.assertEqual(out[2], "")
        self.assertEqual(out[3], "typedef struct { s32 word[6]; } Copy24;")


# ------------------------------------------------------------- the page-based unaligned form (round 62)

PAGE_HEAD = '''#include "common.h"

typedef struct { u8 b[12]; } __attribute__((packed)) Chunk12;
typedef struct { u8 b[8]; } __attribute__((packed)) Chunk8;
typedef struct { Chunk12 first; Chunk12 second; Chunk8 third; } __attribute__((packed)) Chunk32;
typedef struct { s32 w[8]; } Wide32;

extern Chunk32 D_80024028[];
'''

MEMBERS = PAGE_HEAD + '''
void f(void)
{
    Chunk32 offsets;
    u8 *table_page;
    register Chunk32 *offset_source ASM_REG("$6");

    table_page = (u8 *)0x80020000;
    ASM_KEEP(table_page);
    offset_source = (Chunk32 *)(table_page + 0x4028);
    ASM_KEEP(offset_source);
    offsets.first = offset_source->first;
    offsets.second = offset_source->second;
    offsets.third = offset_source->third;
    ASM_KEEP(table_page);
    use(&offsets);
}
'''

CASTS = PAGE_HEAD + '''
void f(void)
{
    Chunk32 points;
    u8 *copy_page;
    u8 *copy_source;

    copy_page = (u8 *)0x80020000;
    ASM_KEEP(copy_page);
    copy_source = copy_page;
    copy_source += 0x4054;
    *(Chunk12 *)&points = *(Chunk12 *)copy_source;
    *(Chunk12 *)((u8 *)&points + 12) = *(Chunk12 *)(copy_source + 12);
    *(Chunk8 *)((u8 *)&points + 24) = *(Chunk8 *)(copy_source + 24);
    ASM_KEEP(copy_page);
}
'''

MEMCPYS = PAGE_HEAD + '''
void f(u8 *dst)
{
    u8 *copy_page;
    u8 *copy_source;

    copy_page = (u8 *)0x80170000;
    ASM_KEEP(copy_page);
    copy_source = (u8 *)(copy_page - 0x57A8);
    ASM_KEEP(copy_source);
    memcpy(dst, copy_source, 12);
    memcpy(dst + 12, copy_source + 12, 12);
    ASM_KEEP(copy_page);
}
'''


class PageRuns(unittest.TestCase):
    def one(self, text):
        rs = M.page_runs(text)
        self.assertEqual(len(rs), 1, [r["addr"] for r in rs])
        return rs[0]

    def test_member_chunks_are_one_run(self):
        r = self.one(MEMBERS)
        self.assertEqual((r["addr"], r["size"], len(r["copies"])), (0x80024028, 32, 3))
        self.assertEqual((r["srcvar"], r["pagevar"], r["dst"]), ("offset_source", "table_page", "&offsets"))

    def test_cast_chunks_and_a_plus_equals_offset(self):
        r = self.one(CASTS)
        self.assertEqual((r["addr"], r["size"]), (0x80024054, 32))
        self.assertEqual(r["dst"], "&points")

    def test_memcpy_chunks_and_a_negative_offset(self):
        r = self.one(MEMCPYS)
        self.assertEqual((r["addr"], r["size"]), (0x8016A858, 24))
        self.assertEqual(r["dst"], "dst")

    def test_a_gap_between_the_chunks_is_refused(self):
        self.assertEqual(M.page_runs(CASTS.replace("+ 24", "+ 28")), [])

    def test_two_destinations_are_refused(self):
        self.assertEqual(M.page_runs(MEMBERS.replace("offsets.second", "other.second")), [])

    def test_a_plain_pointer_is_not_a_page_run(self):
        self.assertEqual(M.page_runs(MEMBERS.replace("(u8 *)0x80020000", "arg")), [])


class PageForms(unittest.TestCase):
    def test_the_symbol_is_the_page_plus_the_offset(self):
        self.assertEqual(M.sym_names(MEMBERS, 0x80024028), [("&D_80024028", None), ("D_80024028", None)])
        self.assertEqual(M.sym_names(MEMBERS, 0x80024054),
                         [("D_80024054", "extern u8 D_80024054[];")])

    def test_only_an_unaligned_type_of_the_right_size_is_offered(self):
        big = M.big_types(MEMBERS)
        self.assertEqual(M.agg_forms(MEMBERS, 32, big),
                         [("Chunk32", None), ("AggU32", "typedef struct { u8 b[32]; } AggU32;")])
        self.assertEqual(M.talign(MEMBERS, "Wide32", big), 4)
        self.assertEqual(M.talign(MEMBERS, "Chunk32", big), 1)

    def test_the_run_becomes_one_assignment_from_the_symbol(self):
        r = M.page_runs(MEMBERS)[0]
        forms = M.page_forms(MEMBERS, r, M.big_types(MEMBERS))
        # the object's own declared type comes first, the anonymous cast form after it
        self.assertEqual(forms[0][1], ["*(Chunk32 *)&offsets = D_80024028[0];"])
        self.assertIn(["*(Chunk32 *)&offsets = *(Chunk32 *)&D_80024028;"], [f[1] for f in forms])
        self.assertEqual(forms[0][2], [])

    def test_a_computed_destination_is_parenthesised(self):
        self.assertEqual(M.paren_addr("(u8 *)effect + 0x98"), "((u8 *)effect + 0x98)")
        self.assertEqual(M.paren_addr("&points"), "&points")
        self.assertEqual(M.paren_addr("dst"), "dst")

    def test_a_scalar_symbol_is_only_spelled_with_an_ampersand(self):
        t = MEMBERS.replace("extern Chunk32 D_80024028[];", "extern Chunk32 D_80024028;")
        self.assertEqual(M.sym_names(t, 0x80024028), [("&D_80024028", None)])
        self.assertEqual(M.sym_decl(t, "D_80024028"), ("Chunk32", False))
        self.assertEqual(M.sym_decl(MEMBERS, "D_80024028"), ("Chunk32", True))

    def test_the_rewrite_drops_the_dead_page_declarations_and_their_pins(self):
        r = M.page_runs(MEMBERS)[0]
        _, stmts, decls = M.page_forms(MEMBERS, r, M.big_types(MEMBERS))[0]
        out, line = M.page_rewrite(MEMBERS, r, stmts, decls, False)
        self.assertIn(stmts[0], out)
        self.assertNotIn("table_page = (u8 *)0x80020000;", out)   # the page constant joins the run
        self.assertNotIn("offset_source", out)                    # dead, with its ASM_REG declaration
        self.assertEqual(out.count("ASM_KEEP("), 0)               # the trailing keep is the run's own
        self.assertEqual(out.split("\n")[line - 1].strip(), stmts[0])

    def test_keep_pins_leaves_the_windows_pins_for_the_erase_plans(self):
        r = M.page_runs(MEMBERS)[0]
        _, stmts, decls = M.page_forms(MEMBERS, r, M.big_types(MEMBERS))[0]
        out, _ = M.page_rewrite(MEMBERS, r, stmts, decls, True)
        self.assertEqual(out.count("ASM_KEEP("), 3)


class PageEligible(unittest.TestCase):
    def test_a_page_run_alone_makes_a_row_eligible(self):
        self.assertIsNone(M.T.eligible(MEMBERS, {}, {}))

    def test_no_run_of_either_kind_is_refused(self):
        self.assertEqual(M.T.eligible(PAGE_HEAD + "\nvoid f(void) { s32 a; a = 1; ASM_KEEP(a); }\n", {}, {}),
                         "no scalarized copy run")


# ------------------------------------------------------------- the joint / staged forms (round 64)

STAGED = PAGE_HEAD + '''extern Chunk12 D_80026180[];

void f(Task *task)
{
    register u8 *copy_page ASM_REG("$2");
    register u8 *copy_source ASM_REG("$6");

    spawn_a(task);
    do {  copy_page = (u8 *)0x80020000;  ASM_KEEP(copy_page);  copy_source = copy_page + (0x6180);  ASM_KEEP(copy_source);  *(Chunk12 *)(task->data) = *(Chunk12 *)copy_source;  ASM_KEEP(copy_page);  } while (0);
    spawn_b(task);
    do {  copy_page = (u8 *)0x80020000;  ASM_KEEP(copy_page);  copy_source = copy_page + (0x6180);  ASM_KEEP(copy_source);  *(Chunk12 *)(task->data) = *(Chunk12 *)copy_source;  ASM_KEEP(copy_page);  } while (0);
}
'''

REBASE = PAGE_HEAD + '''
void f(Task *task)
{
    register u8 *copy_page ASM_REG("$2");
    u8 *copy_source;

    copy_page = (u8 *)0x80020000;
    ASM_KEEP(copy_page);
    copy_source = copy_page;
    copy_source += 0x6198;
    ASM_KEEP(copy_source);
    *(Chunk12 *)task->data = *(Chunk12 *)copy_source;
    copy_page += 0x6198;
    *(Chunk12 *)(task->data + 12) = *(Chunk12 *)(copy_page + 12);
    ASM_KEEP(copy_page);
}
'''


class Staged(unittest.TestCase):
    def test_a_one_line_do_while_block_is_unfolded_and_folded_back(self):
        folded, folds = M.unfold(STAGED)
        self.assertEqual(len(folds), 2)
        self.assertIn("    copy_source = copy_page + (0x6180);", folded)
        self.assertNotIn("do {", folded)
        self.assertEqual(M.refold(folded, folds), STAGED)          # nothing rewritten: nothing reformatted

    def test_the_unfolded_blocks_are_two_page_runs(self):
        folded, _ = M.unfold(STAGED)
        rs = M.page_runs(folded)
        self.assertEqual([(r["addr"], r["size"]) for r in rs], [(0x80026180, 12), (0x80026180, 12)])
        self.assertEqual(rs[0]["dst"], "task->data")               # `->` is not a subtraction
        self.assertEqual(M.run_sig(rs[0]), M.run_sig(rs[1]))       # screened once, applied to both

    def test_a_parenthesised_offset_is_read(self):
        self.assertEqual(M.pbase_off("copy_page + (0x6180)"), ("copy_page", 0x6180))
        self.assertEqual(M.pbase_off("task->data"), ("task->data", 0))

    def test_both_runs_are_rewritten_together_and_the_rest_is_refolded(self):
        folded, folds = M.unfold(STAGED)
        rs, big = M.page_runs(folded), M.big_types(folded)
        jobs = [(r, v[2], v[1], False, v[3]) for r, v in
                ((r, M.page_variants(folded, r, big)[0]) for r in rs)]
        out = M.refold(M.page_apply(folded, jobs), folds)
        self.assertEqual(out.count("ASM_KEEP("), 0)                # both blocks' keeps fell
        self.assertNotIn("copy_source", out)                       # dead in BOTH runs: declaration dropped
        self.assertEqual(out.count("= D_80026180[0];"), 2)

    def test_one_run_rewritten_leaves_the_other_block_folded(self):
        folded, folds = M.unfold(STAGED)
        rs, big = M.page_runs(folded), M.big_types(folded)
        label, decls, stmts, sub = M.page_variants(folded, rs[0], big)[0]
        out = M.refold(M.page_apply(folded, [(rs[0], stmts, decls, False, sub)]), folds)
        self.assertEqual(out.count("do {"), 1)                     # the untouched block is put back
        self.assertIn("copy_source", out)                          # still used by the second block


class Rebase(unittest.TestCase):
    def test_the_transfer_with_a_moved_page_base_is_one_run(self):
        r = M.page_runs(REBASE)[0]
        self.assertEqual((r["addr"], r["size"], len(r["copies"])), (0x80026198, 24, 2))
        self.assertIsNotNone(r["rebase"])

    def test_the_split_form_names_the_object_and_keeps_the_two_chunks(self):
        r = M.page_runs(REBASE)[0]
        labels = [l for l, _, _, _ in M.page_variants(REBASE, r, M.big_types(REBASE))]
        self.assertTrue(labels[0].startswith("split_"), labels)
        sub = M.split_sub(r, "&D_80026198")
        stmts = [s for v in sub.values() if v for s in v]
        self.assertIn("*(Chunk12 *)task->data = *(Chunk12 *)&D_80026198;", stmts)
        self.assertIn("copy_page = (u8 *)&D_80026198;", stmts)
        self.assertIn(None, sub.values())                          # the second chunk is left alone

    def test_the_split_rewrite_drops_the_page_constant_and_the_keeps(self):
        r = M.page_runs(REBASE)[0]
        label, decls, stmts, sub = M.page_variants(REBASE, r, M.big_types(REBASE))[0]
        out = M.page_apply(REBASE, [(r, stmts, decls, False, sub)])
        self.assertNotIn("0x80020000", out)
        self.assertNotIn("copy_source", out)
        self.assertEqual(out.count("ASM_KEEP("), 0)
        self.assertIn("*(Chunk12 *)(task->data + 12) = *(Chunk12 *)(copy_page + 12);", out)

    def test_a_rebase_to_another_object_ends_the_run(self):
        rs = M.page_runs(REBASE.replace("copy_page += 0x6198;", "copy_page += 0x7000;"))
        self.assertEqual([(r["size"], r["rebase"]) for r in rs], [(12, None)])   # only the first chunk


if __name__ == "__main__":
    unittest.main()
