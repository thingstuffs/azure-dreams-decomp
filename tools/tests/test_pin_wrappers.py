"""Owner ruling 2026-09-23 (docs/PIN_CAMPAIGN_CHARTER.md "Rulings 2026-09-23"): a pin inside a
function-like macro counts once per call of that macro in compiled code, not once per definition.
Synthetic text only."""
import sys, unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, hidden_asm, erase
from pin_sites import erase_many

HEAD = '#include "common.h"\n'
WRAP = ("#ifdef NON_MATCHING\n#define LOAD_X(v) ((v) = 1)\n#else\n"
        "#define LOAD_X(v) do { (v) = 0x80070000; ASM_KEEP(v); (v) -= 0x3328; } while (0)\n#endif\n")
BODY = "s32 f(s32 a) {\n    s32 v;\n%s    return v + a;\n}\n"

def src(calls, wrap=WRAP, extra=""):
    return HEAD + wrap + BODY % ("".join("    LOAD_X(v);\n" for _ in range(calls)) + extra)


class WrapperExpansion(unittest.TestCase):
    def test_counts_once_per_call(self):
        for n in (1, 2, 4):
            self.assertEqual(len(sites_of(src(n))), n)

    def test_uncalled_wrapper_is_not_a_pin(self):
        self.assertEqual(len(sites_of(src(0))), 0)

    def test_macro_kind_is_reported_for_expansions(self):
        self.assertEqual({s[1] for s in sites_of(src(3))}, {"ASM_KEEP"})

    def test_removing_calls_removes_sites(self):          # requirement (1)
        self.assertLess(len(sites_of(src(2))), len(sites_of(src(3))))

    def test_rewriting_the_body_pin_free_removes_every_expansion(self):   # requirement (1)
        clean = WRAP.replace(" ASM_KEEP(v);", "")
        self.assertEqual(len(sites_of(src(3, clean))), 0)

    def test_erasing_the_body_site_removes_all_expansions(self):
        t = src(3)
        body = [s for s in sites_of(t) if s[0] == "stmt"]
        self.assertEqual(len(body), 1)
        self.assertEqual(len(sites_of(erase(t, body[0]))), 0)
        self.assertEqual(len(sites_of(erase_many(t, sites_of(t), clean_notes=True))), 0)

    def test_expand_tuples_erase_nothing(self):
        t = src(3)
        for s in sites_of(t):
            if s[0] == "expand":
                self.assertEqual(erase(t, s), t)

    def test_body_without_semicolon_cannot_hide(self):    # requirement (2)
        w = "#define READ_ZERO(var) ASM_UNDEF(var)\n"
        t = HEAD + w + BODY % "    READ_ZERO(v);\n    READ_ZERO(v);\n"
        self.assertEqual(len(sites_of(t)), 2)

    def test_object_like_macro_cannot_hide(self):         # requirement (2)
        w = "#define KEEP_V do { ASM_KEEP(v); } while (0)\n"
        t = HEAD + w + BODY % "    KEEP_V;\n    KEEP_V;\n    KEEP_V;\n"
        self.assertEqual(len(sites_of(t)), 3)

    def test_nested_wrapper_cannot_hide(self):            # requirement (2)
        w = ("#define INNER(v) ASM_KEEP(v)\n"
             "#define OUTER(v) do { INNER(v); ASM_USE(v); } while (0)\n")
        t = HEAD + w + BODY % "    OUTER(v);\n    OUTER(v);\n"
        self.assertEqual(len(sites_of(t)), 4)

    def test_moving_pins_into_a_wrapper_does_not_reduce_the_count(self):   # requirement (2)
        inline = HEAD + BODY % "    ASM_KEEP(v);\n    ASM_KEEP(v);\n"
        wrapped = HEAD + "#define K(v) ASM_KEEP(v);\n" + BODY % "    K(v)\n    K(v)\n"
        self.assertEqual(len(sites_of(inline)), len(sites_of(wrapped)))

    def test_asm_named_wrapper_counts_its_body_pins_per_call(self):
        w = "#define ASM_KEEP2(a, b) do { ASM_KEEP(a); ASM_KEEP(b); } while (0)\n"
        t = HEAD + w + BODY % "    ASM_KEEP2(v, a);\n    ASM_KEEP2(v, a);\n"
        self.assertEqual(len(sites_of(t)), 4)
        one = HEAD + "#define ASM_CLOBBER_A0() ASM_CLOBBER(\"$4\")\n" + BODY % "    ASM_CLOBBER_A0();\n"
        self.assertEqual(len(sites_of(one)), 1)

    def test_local_raw_asm_pin_macro_unchanged(self):
        w = '#define ASM_KEEP(v) __asm__ __volatile__("" : "+r"(v))\n'
        t = HEAD + w + BODY % "    ASM_KEEP(v);\n    ASM_KEEP(v);\n"
        self.assertEqual(len(sites_of(t)), 2)

    def test_port_arm_calls_do_not_count(self):
        t = src(1, extra="#ifdef NON_MATCHING\n    LOAD_X(v);\n#endif\n")
        self.assertEqual(len(sites_of(t)), 1)

    def test_counted_wrappers_leave_hidden_asm(self):
        self.assertEqual(hidden_asm(src(3))["wrapper-call"], 0)
        raw = HEAD + '#define KEEPR(v) __asm__("" : "+r"(v))\n' + BODY % "    KEEPR(v);\n"
        self.assertEqual(hidden_asm(raw)["wrapper-call"], 1)
        self.assertEqual(len(sites_of(raw)), 0)


if __name__ == "__main__":
    unittest.main()
