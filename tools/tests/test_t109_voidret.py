"""T109: the void->pointer return rewrite, the copy rename and the inlined-helper caller form are textual;
the screen and `vf` are not run."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t109_voidret as M  # noqa: E402
from pin_census import sites_of  # noqa: E402

LEAF = '''#include "common.h"
void func_80028774(Block *dest);
void func_80028774(Block *dest) {
    register Block *dst ASM_REG("$2") = dest;

    ASM_KEEP(dst);
    dst[0] = D_80029550[0];
    dst[1] = D_80029550[1];
}
'''

HELPER = '''#include "common.h"
static __inline__ void set_handler(u8 *base) {
    register u8 *handler_base ASM_REG("$2") = base;

    ASM_KEEP(handler_base);
    ((S *)handler_base)->unk_10 = D_80022CD8;
}

void func_80022D60(s32 value) {
    u8 *base;

    base = func_80001000(value);
    set_handler(base);
}
'''


class TestDetect(unittest.TestCase):
    def test_a_void_function_with_a_kept_dollar2_copy_is_eligible(self):
        self.assertIsNone(M.T.eligible(LEAF, {}, {}))
        self.assertEqual([(x, s) for x, s, _t in M.copies(LEAF, *M.void_functions(LEAF)[0][2:4])],
                         [("dst", "dest")])

    def test_a_non_void_function_is_not_a_site(self):
        t = LEAF.replace("void func_80028774", "s32 func_80028774")
        self.assertEqual(M.void_functions(t), [])

    def test_a_void_pointer_function_is_not_void(self):
        t = LEAF.replace("void func_80028774", "void *func_80028774")
        self.assertEqual(M.void_functions(t), [])


class TestRewrite(unittest.TestCase):
    def test_the_copy_is_renamed_and_every_declaration_returns_the_pointer(self):
        c = dict(M.candidates(LEAF))["func_80028774:copy:dst<-dest:named:all"]
        self.assertEqual(sites_of(c), [])
        self.assertEqual(c.count("Block *func_80028774(Block *dest)"), 2)
        self.assertIn("    dest[1] = D_80029550[1];\n    return dest;\n}", c)
        self.assertNotIn("dst", c)

    def test_a_bare_return_returns_the_value_in_the_all_mode(self):
        t = LEAF.replace("    dst[1] = D_80029550[1];\n", "    if (dest == 0) {\n        return;\n    }\n    dst[1] = D_80029550[1];\n")
        c = dict(M.candidates(t))["func_80028774:copy:dst<-dest:named:all"]
        self.assertIn("return dest;\n    }", c)

    def test_the_caller_of_an_inlined_helper_returns_the_object(self):
        c = dict(M.candidates(HELPER))["func_80022D60:caller-set_handler:base"]
        self.assertIn("static __inline__ void set_handler(u8 *base)", c)
        self.assertIn("u8 *func_80022D60(s32 value)", c)
        self.assertIn("    set_handler(base);\n    return base;\n}", c)
        self.assertEqual(sites_of(c), [])


if __name__ == "__main__":
    unittest.main()
