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


if __name__ == "__main__":
    unittest.main()
