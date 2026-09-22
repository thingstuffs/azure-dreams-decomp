"""T101: the type table, the cast rule and the rewrite are textual; the screen and `vf` are not."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t101_crossmerge as M  # noqa: E402
from pin_census import sites_of  # noqa: E402

# the shape of dungeon/func_80A1FBBC: a pointer that dies early, a narrow integer born later
PTR_INTO_NARROW = '''#include "common.h"
void f(void *spawned_object, void *position) {
    void *projectile_callback;
    u16 frames_left;

    projectile_callback = D_801741A4;
    ASM_KEEP(projectile_callback);
    ((S *)spawned_object)->unk_10 = projectile_callback;
    frames_left = ((S *)position)->unk_02;
    ((S *)spawned_object)->unk_20 = frames_left;
}
'''

# the shape of dungeon/func_800B8F90: a word into a narrow integer, no cast anywhere
WORD_INTO_NARROW = '''#include "common.h"
void g(void *entity, void *state) {
    u8 spawn_type;
    s32 selected_entity;

    spawn_type = ((S *)entity)->unk_04;
    ((S *)entity)->unk_08 = spawn_type;
    selected_entity = ((S *)state)->unk_10;
    ASM_KEEP(selected_entity);
    ((S *)state)->unk_10 = selected_entity & 0x7FFFFFFF;
}
'''

# the live ranges overlap: `held` is read after the second value is born
OVERLAP = '''#include "common.h"
void h(void *entity, void *state) {
    void *held;
    u16 count;

    held = ((S *)entity)->unk_04;
    ASM_KEEP(held);
    count = ((S *)state)->unk_02;
    ((S *)state)->unk_08 = count;
    ((S *)entity)->unk_0C = held;
}
'''


class TestTypes(unittest.TestCase):
    def test_merged_types_cover_both_roles(self):
        self.assertEqual(M.merged_types("void*", "u16")[:1], ["void*"])
        self.assertIn("u32", M.merged_types("void*", "u16"))
        self.assertNotIn("u16", M.merged_types("void*", "u16"))      # too narrow for a pointer
        self.assertNotIn("u8", M.merged_types("s32", "u8"))

    def test_same_type_is_not_this_generator(self):
        self.assertEqual(M.merged_types("s32", "s32"), [])
        self.assertEqual(M.merged_types("S *", "S *"), [])

    def test_unknown_type_refused(self):
        self.assertEqual(M.merged_types("Matrix", "s32"), [])

    def test_cast_rule(self):
        self.assertTrue(M._needs_cast("void*", "u32"))               # pointer-ness differs
        self.assertTrue(M._needs_cast("u8*", "Object*"))             # two pointer types
        self.assertFalse(M._needs_cast("u8", "s32"))                 # C converts at the assignment
        self.assertFalse(M._needs_cast("void*", "void*"))


class TestCandidates(unittest.TestCase):
    def test_pointer_into_narrow_widens_and_casts(self):
        self.assertIsNone(M.T.eligible(PTR_INTO_NARROW, {}, {}))
        labels = [l for l, _c, _w, _m in M.candidates(PTR_INTO_NARROW)]
        self.assertTrue(any("projectile_callback->frames_left" in l for l in labels), labels)
        cand = next(c for l, c, _w, _m in M.candidates(PTR_INTO_NARROW)
                    if l.startswith("u32:projectile_callback->frames_left"))
        # the surviving NAME is the one the statement pin holds, so `ASM_KEEP(projectile_callback)`
        # stays spelled as it was; only the storage and the casts move
        self.assertIn("u32 projectile_callback;", cand)
        self.assertIn("projectile_callback = (u32)D_801741A4;", cand)
        self.assertIn("(void *)projectile_callback", cand)
        self.assertNotIn("u16 frames_left;", cand)

    def test_the_orphaned_pin_is_the_candidate_s_must(self):
        must = next(m for l, _c, _w, m in M.candidates(PTR_INTO_NARROW)
                    if l.startswith("u32:projectile_callback->frames_left"))
        self.assertTrue(must)                                        # ASM_KEEP(projectile_callback)
        cand = next(c for l, c, _w, _m in M.candidates(PTR_INTO_NARROW)
                    if l.startswith("u32:projectile_callback->frames_left"))
        rs = sites_of(cand)
        self.assertEqual(M.plans(rs, must, (0, 0))[0],
                         [i for i, s in enumerate(rs) if s[5] in must])

    def test_word_into_narrow_retypes_without_casts(self):
        cand = next(c for l, c, _w, _m in M.candidates(WORD_INTO_NARROW)
                    if l.startswith("s32:selected_entity->spawn_type"))
        self.assertIn("s32 selected_entity;", cand)
        self.assertNotIn("u8 spawn_type;", cand)
        self.assertNotIn("(s32)selected_entity", cand)                # an integer role is never cast
        self.assertIn("selected_entity = ((S *)entity)->unk_04;", cand)

    def test_overlapping_ranges_refused(self):
        labels = [l for l, _c, _w, _m in M.candidates(OVERLAP)]
        self.assertFalse([l for l in labels if "held->count" in l], labels)


if __name__ == "__main__":
    unittest.main()
