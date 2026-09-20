"""T83: pair detection, the joint move and the refusals are textual; the screen and `vf` are not exercised."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t83_storeafterproducer as M  # noqa: E402

T = '''#include "common.h"
void f(S *effect, S *out)
{
    s32 red;
    s32 green;
    s32 scale;

    red = effect->unk_00 / effect->unk_34;
    ASM_MEM_BARRIER();
    green = effect->unk_01 / effect->unk_34;
    ASM_MEM_BARRIER();
    scale = effect->unk_02 * 2;
    effect->unk_32.unk_32_u = scale;
    effect->unk_04.bytes.unk_04 = red;
    effect->unk_04.bytes.unk_05 = green;
}
'''

CALLED = '''#include "common.h"
void g(S *effect)
{
    s32 red;

    red = effect->unk_00 / effect->unk_34;
    ASM_MEM_BARRIER();
    func_80024610(effect);
    effect->unk_04.bytes.unk_04 = red;
}
'''

NAMED = '''#include "common.h"
void g(S *effect)
{
    s32 red;

    red = effect->unk_00 / effect->unk_34;
    ASM_MEM_BARRIER();
    effect->unk_10 = red + 1;
    effect->unk_04.bytes.unk_04 = red;
}
'''

BASEWRITE = '''#include "common.h"
void g(S *effect, S *other)
{
    s32 red;

    red = other->unk_00 / other->unk_34;
    ASM_MEM_BARRIER();
    effect = other;
    effect->unk_04.bytes.unk_04 = red;
}
'''

CONTROL = '''#include "common.h"
void g(S *effect, s32 n)
{
    s32 red;

    red = effect->unk_00 / effect->unk_34;
    ASM_MEM_BARRIER();
    if (n) {
        effect->unk_10 = 1;
    }
    effect->unk_04.bytes.unk_04 = red;
}
'''

LOCALDEST = '''#include "common.h"
void g(S *effect, s32 n)
{
    s32 red;
    s32 copy;

    red = effect->unk_00 / effect->unk_34;
    ASM_MEM_BARRIER();
    effect->unk_10 = 1;
    copy = red;
}
'''


class Pairs(unittest.TestCase):
    def test_detects_both_pairs(self):
        ps = M.pairs(T)
        self.assertEqual([(p[2], p[3]) for p in ps],
                         [("red", "effect->unk_04.bytes.unk_04"), ("green", "effect->unk_04.bytes.unk_05")])
        lines = T.split("\n")
        for prod, store, v, _ in ps:
            self.assertIn(v + " =", lines[prod])                      # the producer, not a pin or a reload
            self.assertTrue(lines[store].rstrip().endswith("= %s;" % v))

    def test_member_write_does_not_block(self):
        # `effect->unk_32.unk_32_u = scale;` writes a MEMBER of the LHS base: the move stays admissible
        self.assertEqual(len(M.pairs(T)), 2)

    def test_joint_move_text(self):
        ps = M.pairs(T)
        lines = T.split("\n")
        moved = M.move(T, [(p[1], M.targets(T, p[0], p[1])[0]) for p in ps])
        out = moved.split("\n")
        self.assertEqual(out[out.index("    red = effect->unk_00 / effect->unk_34;") + 1],
                         "    effect->unk_04.bytes.unk_04 = red;")
        self.assertEqual(out[out.index("    green = effect->unk_01 / effect->unk_34;") + 1],
                         "    effect->unk_04.bytes.unk_05 = green;")
        self.assertEqual(len(out), len(lines))                        # lines moved, none added or lost
        self.assertEqual(sorted(out), sorted(lines))
        self.assertEqual(out[-3], "    effect->unk_32.unk_32_u = scale;")   # the stores left the tail

    def test_offsets(self):
        prod, store = M.pairs(T)[0][0], M.pairs(T)[0][1]
        ts = M.targets(T, prod, store)
        self.assertEqual(ts[0], prod)                                 # immediately after the producer
        self.assertEqual(len(ts), M.MAX_OFFSET + 1)                   # and one and two statements further down
        self.assertTrue(all(prod <= x < store for x in ts))
        self.assertNotIn("ASM_MEM_BARRIER", T.split("\n")[ts[1]])     # a pin line is not a statement


class Refusals(unittest.TestCase):
    def test_call_between(self):
        self.assertEqual(M.pairs(CALLED), [])

    def test_v_named_between(self):
        self.assertEqual(M.pairs(NAMED), [])

    def test_bare_write_to_lhs_base(self):
        self.assertEqual(M.pairs(BASEWRITE), [])

    def test_control_between(self):
        self.assertEqual(M.pairs(CONTROL), [])

    def test_local_destination_is_not_a_store(self):
        self.assertEqual(M.pairs(LOCALDEST), [])

    def test_eligible_reasons(self):
        self.assertIsNone(M.T.eligible(T, {}, {}))
        self.assertEqual(M.T.eligible(CALLED, {}, {}), "no producer/store pair")
        self.assertEqual(M.T.eligible(T.replace("    ASM_MEM_BARRIER();\n", "", 2), {}, {}), "no pins")


if __name__ == "__main__":
    unittest.main()
