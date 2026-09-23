"""T113: arity sites, the truncation, the prototype rewrite and the pin plans are textual; the tree index is
injected, no screen, no `vf`."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t113_sibarity as M  # noqa: E402
from pin_census import sites_of  # noqa: E402

ROW = '''#include "common.h"
extern void func_800A4ACC(void *, s32, s32);

void f(void *entity, s32 requested) {
    s32 mode = requested;
    s32 raw = requested & 0xFF;

    if (mode == 0) {
        ASM_KEEP(mode);
        func_800A4ACC(entity, mode, raw);
    }
}
'''
IDX = {"func_800A4ACC": {1: "void *", 3: "void *, s32, s32"}}


class TestSites(unittest.TestCase):
    def test_a_call_above_a_sibling_arity_is_a_site(self):
        st = M.sites(ROW, IDX)
        self.assertEqual([(s["f"], len(s["args"]), s["arities"]) for s in st], [("func_800A4ACC", 3, [1])])

    def test_no_lower_arity_no_site(self):
        self.assertEqual(M.sites(ROW, {"func_800A4ACC": {3: "void *, s32, s32"}}), [])

    def test_a_same_file_call_with_fewer_arguments_attests_the_arity(self):
        t = ROW.replace("    }\n}", "    }\n    func_800A4ACC(entity);\n}")
        st = M.sites(t, {})
        self.assertEqual(st[0]["arities"], [1])


class TestRewrite(unittest.TestCase):
    def test_the_call_the_prototype_and_the_named_keep_change_together(self):
        c = dict(M.candidates(ROW, IDX))["func_800A4ACC@10:3->1:one:named"]
        self.assertIn("func_800A4ACC(entity);", c)
        self.assertIn("extern void func_800A4ACC(void *);", c)
        self.assertEqual(sites_of(c), [])


if __name__ == "__main__":
    unittest.main()
