"""T105: the two hoist forms, their refusals and the pin plans are textual; the screen and `vf` are not run."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t105_headhoist as M  # noqa: E402
from pin_census import sites_of, unscored_text  # noqa: E402

DUP = '''#include "common.h"
void f(u8 *obj, s32 idx, u8 **out) {
    register u8 *entry ASM_REG("$3");
    u8 *page;

    if ((s16)idx != 0) {
        entry = obj + 0x20;
        ASM_KEEP(entry);
        out[0] = entry;
        goto tail;
    }
    entry = obj + 0x20;
    out[1] = entry;
tail:
    out[2] = 0;
}
'''

SPEC = '''#include "common.h"
void g(void *root, s32 flags) {
    s16 held;

    if (root != NULL) {
        held = flags;
        ASM_USE_NV(held);
        func_80000000(root, (s16)held);
    }
}
'''


class TestSites(unittest.TestCase):
    def test_the_duplicated_head_is_a_dup_site(self):
        self.assertEqual([(s["kind"], s["name"]) for s in M.sites(DUP)], [("dup", "entry")])

    def test_a_value_only_the_arm_reads_is_a_spec_site(self):
        self.assertEqual([(s["kind"], s["name"]) for s in M.sites(SPEC)], [("spec", "held")])

    def test_a_dereference_is_never_hoisted(self):
        t = SPEC.replace("held = flags;", "held = *(s16 *)root;")
        self.assertEqual(M.sites(t), [])

    def test_a_call_is_never_hoisted(self):
        t = SPEC.replace("held = flags;", "held = func_80000004(flags);")
        self.assertEqual(M.sites(t), [])

    def test_a_value_read_after_the_if_is_not_speculated(self):
        t = SPEC.replace("    }\n}", "    }\n    func_80000008(held);\n}")
        self.assertEqual(M.sites(t), [])

    def test_a_dup_needs_the_arm_to_jump_away(self):
        t = DUP.replace("        goto tail;\n", "")
        self.assertNotIn("dup", [s["kind"] for s in M.sites(t)])

    def test_the_condition_may_not_read_the_name(self):
        t = SPEC.replace("if (root != NULL)", "if (held != 0)")
        self.assertEqual(M.sites(t), [])


class TestRewrite(unittest.TestCase):
    def test_dup_keeps_one_copy_above_the_if_and_erases_the_named_pins(self):
        c = dict(M.candidates(DUP))["dup:entry@6:named"]
        self.assertEqual(c.count("entry = obj + 0x20;"), 1)
        self.assertLess(c.index("entry = obj + 0x20;"), c.index("if ((s16)idx != 0)"))
        self.assertEqual(sites_of(c), [])
        self.assertIn("    u8 *entry;", c)

    def test_spec_moves_the_copy_and_keeps_its_use(self):
        c = dict(M.candidates(SPEC))["spec:held@5:named"]
        self.assertIn("    held = flags;\n    if (root != NULL) {", c)
        self.assertIn("func_80000000(root, (s16)held);", c)
        self.assertEqual(unscored_text(c), unscored_text(SPEC))


if __name__ == "__main__":
    unittest.main()
