"""Safety boundaries for the fixed-record copy recognizer (no compiler)."""
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from aggregate_copy import analyze, candidates
from pin_census import unscored_text


HEAD = '#include "common.h"\n\ntypedef struct { s32 a; s32 b; s32 c; s32 d; } Words;\n'


def copy68(extra="", tail="    dst->a = src->a;\n"):
    return HEAD + """void f(s32 *base, s32 *record) {
    Words *src;
    Words *dst;
    Words *end;
    src = (Words *)(base + 0x32);
    dst = (Words *)(record + 0xD);
    end = (Words *)(base + 0x42);
loop_0: {
    s32 w0; s32 w1; s32 w2; s32 w3;
    w0 = src->a;
    w1 = src->b;
    w2 = src->c;
    w3 = src->d;
    dst->a = w0;
    dst->b = w1;
    dst->c = w2;
    dst->d = w3;
    %s
    src++;
    dst++;
} if (src != end) goto loop_0;
%s}
""" % (extra, tail)


class Recognizer(unittest.TestCase):
    def test_record68_extent_and_aligned_candidate(self):
        text = copy68("ASM_KEEP(src);")
        scan = analyze(text)
        self.assertEqual(len(scan.matches), 1)
        match = scan.matches[0]
        self.assertEqual((match.loop_bytes, match.tail_bytes, match.total_bytes), (64, 4, 68))
        cand = candidates(text)[0].text
        self.assertIn("u32 words[17]", cand)
        self.assertIn("*(CopyRecord68 *)dst = *(CopyRecord68 *)src;", cand)
        self.assertNotIn("ASM_KEEP", cand)

    def test_record68_real_global_alias_keeps_s32_pointer_stride(self):
        text = copy68("ASM_KEEP(src);").replace(
            "void f(s32 *base, s32 *record) {", "extern s32 D_80082A38[];\nvoid f(s32 *record) {\n    s32 *base;").replace(
            "    src = (Words *)(base + 0x32);", "    base = D_80082A38;\n    src = (Words *)(base + 0x32);")
        match = analyze(text).matches[0]
        self.assertEqual(match.loop_bytes, 64)

    def test_do_while_84_reuses_existing_record(self):
        text = ('#include "common.h"\n'
                'typedef struct { s32 words[21]; } Record84;\n'
                'typedef struct { s32 words[4]; } Copy16;\n'
                'void f(u8 *src, u8 *dst) {\n    u8 *end;\n    end = src + 0x50;\n'
                '    do {\n        *(Copy16 *)dst = *(Copy16 *)src;\n'
                '        src += 0x10;\n        dst += 0x10;\n    } while (src != end);\n'
                '    *(s32 *)dst = *(s32 *)src;\n    ASM_MEM_BARRIER();\n}\n')
        match = analyze(text).matches[0]
        self.assertEqual(match.total_bytes, 84)
        self.assertEqual(match.type_name, "Record84")
        self.assertIn("*(Record84 *)dst = *(Record84 *)src;", candidates(text)[0].text)

    def test_preserves_unscored_arm(self):
        base = copy68("ASM_KEEP(src);")
        text = base.replace("void f", "#ifdef NON_MATCHING\nvoid port(void) { use(); }\n#else\nvoid f")
        text = text.replace("\n}\n", "\n}\n#endif\n", 1)
        cand = candidates(text)[0].text
        self.assertEqual(unscored_text(cand), unscored_text(text))

    def test_unknown_extent_is_refused(self):
        text = copy68().replace("end = (Words *)(base + 0x42);", "end = get_end();")
        scan = analyze(text)
        self.assertEqual(scan.matches, [])
        self.assertTrue(scan.refusals["unknown-copy-extent"])

    def test_volatile_copy_is_refused(self):
        text = copy68().replace("Words *dst;", "volatile Words *dst;")
        scan = analyze(text)
        self.assertEqual(scan.matches, [])
        self.assertTrue(scan.refusals["volatile-copy"])

    def test_side_effect_in_loop_is_refused(self):
        text = copy68("observe(src);")
        scan = analyze(text)
        self.assertEqual(scan.matches, [])
        self.assertTrue(scan.refusals["copy-body-side-effect"])

    def test_disjoint_tail_is_refused_as_a_residual_cursor_use(self):
        text = copy68(tail="    dst->a = other->a;\n")
        scan = analyze(text)
        self.assertEqual(scan.matches, [])
        self.assertTrue(scan.refusals["residual-cursor-use"])

    def test_runtime_alignment_arms_are_refused(self):
        loop = """    end = src + 4;
    do { *dst = *src; src++; dst++; } while (src != end);
"""
        text = HEAD + "void f(Words *src, Words *dst) { Words *end; if (aligned) {\n" + loop + "    } else {\n" + loop + "    }}\n"
        scan = analyze(text)
        self.assertEqual(scan.matches, [])
        self.assertTrue(scan.refusals["parallel-copy-arms"])

    def test_residual_cursor_use_is_refused(self):
        text = copy68()[:-2] + "    consume(src);\n}\n"
        scan = analyze(text)
        self.assertEqual(scan.matches, [])
        self.assertTrue(scan.refusals["residual-cursor-use"])

    def test_copy_scratch_live_after_region_is_refused(self):
        text = copy68(tail="    use(w0);\n")
        scan = analyze(text)
        self.assertEqual(scan.matches, [])
        self.assertTrue(scan.refusals["uncertain-residual-copy-value"])

    def test_pointer_record_is_not_reused_as_a_mechanical_copy_type(self):
        text = copy68("ASM_KEEP(src);").replace(
            HEAD, HEAD + "typedef struct { void *words[17]; } PointerRecord68;\n")
        match = analyze(text).matches[0]
        self.assertIsNone(match.type_name)

    def test_conditional_or_competing_end_definition_is_refused(self):
        text = (HEAD + "void f(Words *src, Words *dst, s32 c) { Words *end;\n"
                "end = src + 4;\nif (c) { end = src + 8; }\n"
                "do { *dst++ = *src++; } while (src != end);\n}\n")
        scan = analyze(text)
        self.assertEqual(scan.matches, [])
        self.assertTrue(scan.refusals["ambiguous-copy-definition"])

    def test_proven_overlap_is_refused(self):
        text = (HEAD + "void f(Words *base) { Words *src; Words *dst; Words *end;\n"
                "src = base;\ndst = base + 1;\nend = src + 4;\n"
                "do { *dst++ = *src++; } while (src != end);\n}\n")
        scan = analyze(text)
        self.assertEqual(scan.matches, [])
        self.assertTrue(scan.refusals["overlapping-copy-range"])

    def test_cursor_address_escape_is_refused(self):
        text = copy68().replace("    end =", "    consume(&src);\n    end =")
        scan = analyze(text)
        self.assertEqual(scan.matches, [])
        self.assertTrue(scan.refusals["cursor-address-escapes"])

    def test_shadowed_volatile_cursor_is_refused(self):
        text = (HEAD + "void f(Words *input, Words *dst) { volatile Words *src; Words *end;\n"
                "src = input;\n{ Words *src; use(src); }\nend = (Words *)input + 4;\n"
                "do { *dst++ = *src++; } while (src != end);\n}\n")
        scan = analyze(text)
        self.assertEqual(scan.matches, [])
        self.assertTrue(scan.refusals["shadowed-copy-cursor"])

    def test_manual_loop_must_load_all_words_before_stores(self):
        text = copy68().replace(
            "    w0 = src->a;\n    w1 = src->b;\n    w2 = src->c;\n    w3 = src->d;\n    dst->a = w0;",
            "    w0 = src->a;\n    dst->a = w0;\n    w1 = src->b;\n    w2 = src->c;\n    w3 = src->d;")
        scan = analyze(text)
        self.assertEqual(scan.matches, [])
        self.assertTrue(scan.refusals["copy-events-not-load-then-store"])

    def test_copy_inside_preprocessor_macro_is_refused(self):
        text = (HEAD + "#define COPY_ALL() do { *dst++ = *src++; } while (src != end);\n"
                "void f(Words *src, Words *dst) { Words *end;\nend = src + 4;\nCOPY_ALL();\n}\n")
        scan = analyze(text)
        self.assertEqual(scan.matches, [])
        self.assertTrue(scan.refusals["preprocessor-copy-body"])

    def test_continued_line_comment_hides_following_physical_line(self):
        text = (HEAD + "void f(Words *src, Words *dst) { Words *end;\nend = src + 4;\n"
                "// disabled copy \\\n"
                "do { *dst++ = *src++; } while (src != end);\n}\n")
        self.assertEqual(analyze(text).matches, [])

    def test_cursor_update_before_copy_is_refused(self):
        text = (HEAD + "void f(Words *src, Words *dst) { Words *end;\nend = src + 4;\n"
                "do { src++; dst++; *dst = *src; } while (src != end);\n}\n")
        scan = analyze(text)
        self.assertEqual(scan.matches, [])
        self.assertTrue(scan.refusals["cursor-update-before-copy"])

    def test_under_aligned_typed_block_is_refused(self):
        text = ('#include "common.h"\ntypedef struct { u16 w[8]; } HalfBlock;\n'
                'void f(HalfBlock *src, HalfBlock *dst) { HalfBlock *end;\nend = src + 4;\n'
                'do { *dst++ = *src++; } while (src != end);\n}\n')
        scan = analyze(text)
        self.assertEqual(scan.matches, [])
        self.assertTrue(scan.refusals["under-aligned-copy-type"])

    def test_cursor_captured_by_source_macro_is_refused(self):
        text = (HEAD + "#define USE_CURSOR() consume(src)\n" +
                copy68().replace(HEAD, "").replace("\n}\n", "\n    USE_CURSOR();\n}\n"))
        scan = analyze(text)
        self.assertEqual(scan.matches, [])
        self.assertTrue(scan.refusals["cursor-captured-by-macro"])

    def test_late_or_port_only_record_type_is_not_reused(self):
        text = copy68() + "typedef struct { u32 words[17]; } Record68;\n"
        self.assertIsNone(analyze(text).matches[0].type_name)
        port = ("#ifdef NON_MATCHING\ntypedef struct { u32 words[17]; } PortRecord68;\n#endif\n" + copy68())
        self.assertIsNone(analyze(port).matches[0].type_name)

    def test_generated_type_follows_only_safe_top_level_include(self):
        text = ('/* #include "fake.h" */\n#include "common.h"\n#ifdef FEATURE\n#include "feature.h"\n#endif\n' +
                copy68().replace('#include "common.h"\n\n', ""))
        cand = candidates(text)[0].text
        typedef_at = cand.index("typedef struct {\n    u32 words[17]")
        self.assertGreater(typedef_at, cand.index('#include "common.h"'))
        self.assertLess(typedef_at, cand.index("#ifdef FEATURE"))

    def test_volatile_limit_object_is_refused(self):
        text = (HEAD + "void f(Words *src, Words *dst) { Words * volatile end;\nend = src + 4;\n"
                "do { *dst++ = *src++; } while (src != end);\n}\n")
        scan = analyze(text)
        self.assertEqual(scan.matches, [])
        self.assertTrue(scan.refusals["volatile-copy"])

    def test_else_definition_and_prefix_goto_are_refused(self):
        text = (HEAD + "void f(Words *src, Words *dst, Words *end, s32 c) {\n"
                "if (c) { use(); } else { end = src + 4; }\n"
                "do { *dst++ = *src++; } while (src != end);\n}\n")
        self.assertTrue(analyze(text).refusals["conditional-copy-definition"])
        jumped = (HEAD + "void f(Words *src, Words *dst, Words *end, s32 c) {\n"
                  "if (c) goto copy;\nend = src + 4;\ncopy:\n"
                  "do { *dst++ = *src++; } while (src != end);\n}\n")
        self.assertTrue(analyze(jumped).refusals["nonlocal-control-before-copy"])

    def test_outer_scratch_storage_is_refused(self):
        text = copy68().replace(
            "    s32 w0; s32 w1; s32 w2; s32 w3;\n", "")
        scan = analyze("s32 w0, w1, w2, w3;\n" + text)
        self.assertEqual(scan.matches, [])
        self.assertTrue(scan.refusals["nonlocal-copy-scratch"])

    def test_global_copy_cursors_are_refused(self):
        text = (HEAD + "Words *src; Words *dst;\n"
                "void f(void) { Words *end;\nend = src + 4;\n"
                "do { *dst = *src; src++; dst++; } while (src != end);\n}\n")
        scan = analyze(text)
        self.assertEqual(scan.matches, [])
        self.assertTrue(scan.refusals["shadowed-copy-cursor"])

    def test_conditional_extent_alias_is_refused(self):
        text = (HEAD + "void f(Words *input, Words *dst, s32 c) { Words *src; Words *end;\n"
                "if (c) { src = input; }\nend = src + 4;\n"
                "do { *dst++ = *src++; } while (src != end);\n}\n")
        scan = analyze(text)
        self.assertEqual(scan.matches, [])
        self.assertTrue(scan.refusals["conditional-copy-definition"])

    def test_postincrement_must_advance_one_full_block(self):
        text = (HEAD + "void f(u32 *src, u32 *dst) { u32 *end;\nend = src + 4;\n"
                "do { s32 w0; s32 w1; s32 w2; s32 w3;\n"
                "w0 = ((Words *)src)->a; w1 = ((Words *)src)->b;\n"
                "w2 = ((Words *)src)->c; w3 = ((Words *)src)->d;\n"
                "((Words *)dst)->a = w0; ((Words *)dst)->b = w1;\n"
                "((Words *)dst)->c = w2; ((Words *)dst)->d = w3;\n"
                "src++; dst++; } while (src != end);\n}\n")
        scan = analyze(text)
        self.assertEqual(scan.matches, [])
        self.assertTrue(scan.refusals["non-16-byte-cursor-step"])


if __name__ == "__main__":
    unittest.main()
