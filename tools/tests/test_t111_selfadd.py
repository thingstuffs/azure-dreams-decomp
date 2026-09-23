"""T111: the self-referential split, the in-place add and the joint form are textual; no screen, no `vf`."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t111_selfadd as M  # noqa: E402
from pin_census import sites_of  # noqa: E402

SPLIT = '''#include "common.h"
void f(void *object) {
    S_1 *result;

    result = (u8 *)object + 0x20;
    ASM_KEEP(result);
    ((S_0 *)object)->unk_10 = D_8017103C;
    result->unk_13 = 42;
}
'''

INPLACE = '''#include "common.h"
void g(u16 *room_header) {
    u8 *data;

    data = (u8 *)(room_header + 4);
    ASM_KEEP_NV(room_header);
    func_80001000(data);
    room_header = (u16 *)data;
    data = (u8 *)(room_header + 4);
    ASM_KEEP_NV(data);
    func_80001000(data);
}
'''


class TestSites(unittest.TestCase):
    def test_an_offset_pointer_kept_at_once_is_a_site(self):
        st = M.sites(SPLIT)
        self.assertEqual([(s["name"], s["base"], s["type"]) for s in st], [("result", "object", "S_1 *")])

    def test_no_keep_no_site(self):
        self.assertEqual(M.sites(SPLIT.replace("    ASM_KEEP(result);\n", "")), [])

    def test_a_non_literal_offset_is_not_a_site(self):
        self.assertEqual(M.sites(SPLIT.replace("+ 0x20", "+ k")), [])


class TestRewrite(unittest.TestCase):
    def test_split_reads_the_destination_in_its_own_source(self):
        c = dict(M.candidates(SPLIT))["result@5:split:keep"]
        self.assertIn("    result = object;\n    result = (S_1 *)((u8 *)result + 0x20);\n", c)
        self.assertEqual(sites_of(c), [])

    def test_joint_inplace_rewrites_both_sites_and_erases_both_keeps(self):
        c = dict(M.candidates(INPLACE))["joint:inplace:keep"]
        self.assertEqual(c.count("room_header += 4;\n    data = (u8 *)room_header;"), 2)
        self.assertEqual(sites_of(c), [])


if __name__ == "__main__":
    unittest.main()
