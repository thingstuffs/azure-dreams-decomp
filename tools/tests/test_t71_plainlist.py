"""T71's SECOND pattern list: a plain `v = <expr>;` sunk below a call (round 67's move E).

Textual only - the classic `sites_in` list must stay exactly what it was, and the new
`plain_sites_in` must refuse everything a call could change under it.
"""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t71_updateaftercall as M  # noqa: E402

# dungeon/func_80FB5398: the movable statement stands three statements above the call
FAR = '''#include "common.h"
void f(void *object, u8 *vertex_base, s32 camera_z) {
    u8 *vertex_bytes;
    s32 index_or_row;
    void *projection_ptr;

    index_or_row = 3;
    vertex_bytes = ((u8 *) vertex_base) + 24;
    projection.vertices = vertex_base;
    ASM_KEEP_MEM_NV(camera_z, projection);
    projection.count = 4;
    func_800DBA90(projection_ptr);
    ((S *)object)->unk_10 = vertex_bytes;
}
'''

# the right-hand side reads memory, so the call may change it under the move
MEMORY = '''#include "common.h"
void g(void *state, void *arg) {
    s32 coord_or_variant;

    coord_or_variant = (s16)((S *)state)->variant7E;
    func_800DBA90(arg);
    ((S *)arg)->unk_10 = coord_or_variant;
}
'''

# the call names the moved variable
NAMED = '''#include "common.h"
void h(void *arg) {
    s32 index;

    index = 1;
    func_800BCB04(arg, index);
    ((S *)arg)->unk_10 = index;
}
'''

# the classic list owns this call: the second list must not offer it again
CLASSIC = '''#include "common.h"
void k(void *arg, u8 *cursor) {
    s32 entry_index;

    entry_index = 1;
    cursor += 2;
    func_80024610(arg);
    ASM_KEEP(entry_index);
    ((S *)arg)->unk_10 = entry_index;
}
'''


class TestPlainList(unittest.TestCase):
    def test_far_statement_is_movable(self):
        sites = M.plain_sites_in(FAR)
        self.assertEqual(len(sites), 1)
        lines = FAR.split("\n")
        moved = [lines[k].strip() for k, _v in sites[0][2]]
        self.assertIn("vertex_bytes = ((u8 *) vertex_base) + 24;", moved)
        self.assertIn("index_or_row = 3;", moved)

    def test_memory_read_refused(self):
        self.assertEqual(M.plain_sites_in(MEMORY), [])

    def test_variable_named_by_the_call_refused(self):
        self.assertEqual(M.plain_sites_in(NAMED), [])

    def test_a_call_the_classic_list_owns_is_skipped(self):
        self.assertTrue(M.sites_in(CLASSIC))
        classic = {s[0] for s in M.sites_in(CLASSIC)}
        self.assertFalse([s for s in M.plain_sites_in(CLASSIC) if s[0] in classic])

    def test_the_classic_list_is_unchanged_by_the_second(self):
        # the second list never rewrites anything the classic list reports
        for text in (FAR, MEMORY, NAMED, CLASSIC):
            for s in M.plain_sites_in(text):
                self.assertNotIn(s[0], {c[0] for c in M.sites_in(text)})

    def test_rewrite_puts_the_statement_after_the_call(self):
        site = M.plain_sites_in(FAR)[0]
        new = M.rewrite(FAR, site, site[2])
        lines = [l.strip() for l in new.split("\n")]
        self.assertGreater(lines.index("vertex_bytes = ((u8 *) vertex_base) + 24;"),
                           lines.index("func_800DBA90(projection_ptr);"))

    def test_eligible_reaches_the_second_list(self):
        self.assertIsNone(M.T.eligible(FAR, {}, {}))
        self.assertEqual(M.T.eligible(NAMED.replace("func_800BCB04(arg, index);",
                                                    "func_800BCB04(arg, index);\n    ASM_KEEP(index);"),
                                      {}, {}), "no movable update before a call")


if __name__ == "__main__":
    unittest.main()
