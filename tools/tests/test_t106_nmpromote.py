"""T106: arm detection, raw-asm spelling, the file-scope block drop and the NON_MATCHING arm's invariance are
textual; the screen and `vf` are not run."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t106_nmpromote as M  # noqa: E402
from pin_census import sites_of, unscored_text  # noqa: E402

ROW = '''#include "common.h"
extern s32 D_80025788;

#ifndef NON_MATCHING
register u8 *data_ptr ASM_REG("$2");   /* UNRESOLVED C shape (pin) */
#endif

void f(void *state) {
#ifndef NON_MATCHING
    data_ptr = (u8 *)0x80020000;
    data_ptr += 0x5788;
    ASM_MEM_BARRIER();
    *(u8 **)((u8 *)state + 0x34) = data_ptr;
#else
    s32 *state_data = &D_80025788;
    __asm__ __volatile__("" ::: "memory");
    *(s32 **)((u8 *)state + 0x34) = state_data;
#endif
}
'''

POSITIVE = '''#include "common.h"
extern s32 D_80025788;
void g(void *state) {
    s32 *p;
#ifdef NON_MATCHING
    p = &D_80025788;
#else
    p = (s32 *)0x80020000;
    ASM_KEEP(p);
    p = (s32 *)((u8 *)p + 0x5788);
#endif
    *(s32 **)state = p;
}
'''


class TestBlocks(unittest.TestCase):
    def test_the_file_scope_block_and_the_body_split_are_found(self):
        self.assertEqual([b[0] for b in M.blocks(ROW)], ["file", "body"])
        self.assertIsNone(M.T.eligible(ROW, None, {}))

    def test_the_ifdef_polarity_takes_the_else_arm_as_the_matching_one(self):
        (kind, a, b, nm), = M.blocks(POSITIVE)
        self.assertIn("ASM_KEEP(p);", POSITIVE[a:b])
        self.assertIn("p = &D_80025788;", nm)

    def test_unknown_raw_asm_refuses_the_block(self):
        self.assertIsNone(M.spell('    __asm__ __volatile__("nop");\n'))


class TestPromote(unittest.TestCase):
    def test_the_arm_is_promoted_with_its_barrier_spelled_as_the_pin(self):
        c = dict(M.candidates(ROW))["nm:1"]
        body = c[c.index("#ifndef NON_MATCHING\n    "):c.index("#else")]
        self.assertIn("    ASM_MEM_BARRIER();\n", body)
        self.assertNotIn("data_ptr", c)                         # the file-scope block went with it
        self.assertEqual(len(sites_of(c)), 1)
        self.assertEqual(unscored_text(c), unscored_text(ROW))  # the NON_MATCHING arm is untouched

    def test_a_block_still_named_elsewhere_stays(self):
        t = ROW.replace("void f(void *state) {", "void h(void) { data_ptr = 0; }\nvoid f(void *state) {")
        menu = M.candidates(t)
        self.assertNotIn("nm:1", dict(menu))                    # nothing to gain without the block
        for _l, c in menu:
            self.assertIn("data_ptr = 0;", c)
            self.assertIn("u8 *data_ptr", c)

    def test_the_positive_polarity_promotes_too(self):
        c = dict(M.candidates(POSITIVE))["nm:1"]
        self.assertEqual(c.count("p = &D_80025788;"), 2)
        self.assertEqual(sites_of(c), [])


if __name__ == "__main__":
    unittest.main()
