"""T89: web finding, the four declaration placements and the arity note are textual; the listing
screen and `vf` are not exercised."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t89_lifetimesplit as M  # noqa: E402

LOOPS = '''#include "common.h"
void f(void *parent_state) {
    Element *element;
    void *object;
    void *render_data;
    s32 column;

    column = 2;
    do {
        object = func_8003FD64(1, D_80083498);
        element = (u8 *)object + 0x20;
        element->unk_14 = column;
        column--;
    } while (column >= 0);

    column = 2;
    do {
        object = func_8003FD64(1, D_80083498);
        if (object != NULL) {
            render_data = &D_80053A88;
            ASM_KEEP(render_data);   /* UNRESOLVED C shape (pin) */
            element = (u8 *)object + 0x20;
            func_8004491C(object, render_data);
            element->unk_04 = parent_state;
        }
        column--;
    } while (column >= 0);
}
'''

PARAM = '''#include "common.h"
void *g(s32 arg0, s32 arg3)
{
    void *object;
    register s32 saved_arg3 ASM_REG("$18");   /* UNRESOLVED C shape (pin) */
    void *motion;

    saved_arg3 = arg3;
    object = func_8003FD64(0x112, D_80083498);
    if (object != 0) {
        motion = (*(void * *)((u8 *)object + 8));
        motion->unk_0A = saved_arg3;
        arg3 = (s32)(*(void * *)((u8 *)object + 0xC));
        (*(u8 *)((u8 *)((void *)arg3) + 0x25)) = arg0;
        (*(u8 *)((u8 *)((void *)arg3) + 0x24)) = arg0;
    }
    return object;
}
'''

DEADSLOT = '''#include "common.h"
void h(s32 angle) {
    s32 magnitude;
    s32 value;

    value = func_800644B8(angle);
    ASM_KEEP(value);   /* UNRESOLVED C shape (pin) */
    D_80020090 = value << 5;
    value = func_80064584(angle);
    D_800200A8 = value << 5;
}
'''

LOOPCARRIED = '''#include "common.h"
void k(s32 n) {
    s32 total;

    total = 0;
    ASM_KEEP(total);   /* UNRESOLVED C shape (pin) */
    do {
        total = total + n;
        n--;
    } while (n >= 0);
    D_80020090 = total;
}
'''

NOPIN = LOOPS.replace("        ASM_KEEP(render_data);   /* UNRESOLVED C shape (pin) */\n", "")

ARITY = '''#include "common.h"
extern s32 func_80064584(s32 value, s32 other);
extern s32 func_800644B8(s32 value);
void m(s32 angle, s32 y) {
    s32 first;

    first = func_80064584(angle, y);
    ASM_KEEP(first);   /* UNRESOLVED C shape (pin) */
    D_80020090 = first;
    first = func_800644B8(angle);
    D_800200A8 = first;
}
'''


def labels(text):
    return [c[0] for c in M.candidates(text)]


class TestWebs(unittest.TestCase):
    def test_second_loop_range_is_split(self):
        ls = labels(LOOPS)
        self.assertTrue([x for x in ls if x.startswith("split:element>element_2@")], ls)

    def test_all_three_placements_are_offered(self):
        tags = {x.rsplit(":", 1)[1] for x in labels(LOOPS) if x.startswith("split:element")}
        self.assertEqual(tags, {"afterdecl", "inblock", "declend"})

    def test_inblock_declares_at_the_top_of_the_enclosing_block(self):
        cand = dict((c[0], c[1]) for c in M.candidates(LOOPS))["split:element>element_2@22:inblock"]
        lines = [x.strip() for x in cand.splitlines()]
        i = lines.index("Element *element_2;")
        self.assertEqual(lines[i - 1], "if (object != NULL) {")

    def test_the_first_range_keeps_the_name(self):
        cand = dict((c[0], c[1]) for c in M.candidates(LOOPS))["split:element>element_2@22:afterdecl"]
        self.assertIn("        element = (u8 *)object + 0x20;\n", cand)
        self.assertIn("            element_2 = (u8 *)object + 0x20;\n", cand)

    def test_parameter_second_range_is_split(self):
        ls = labels(PARAM)
        self.assertTrue([x for x in ls if x.startswith("split:arg3>arg3_2@")], ls)

    def test_parameter_entry_range_is_never_renamed(self):
        for lab, cand, _, _ in M.candidates(PARAM):
            if lab.startswith("split:arg3"):
                self.assertIn("    saved_arg3 = arg3;\n", cand)
                self.assertIn("arg3_2 = (s32)(*(void * *)((u8 *)object + 0xC));", cand)

    def test_parameter_declaration_is_built_from_its_type(self):
        cand = dict((c[0], c[1]) for c in M.candidates(PARAM))["split:arg3>arg3_2@13:declend"]
        self.assertIn("    s32 arg3_2;\n", cand)

    def test_dead_local_offers_a_declaration_slot(self):
        ls = labels(DEADSLOT)
        self.assertIn("split:value>magnitude@9:deadslot:magnitude", ls)
        cand = dict((c[0], c[1]) for c in M.candidates(DEADSLOT))["split:value>magnitude@9:deadslot:magnitude"]
        self.assertIn("    magnitude = func_80064584(angle);\n", cand)
        self.assertEqual(cand.count("s32 magnitude;"), 1)

    def test_loop_carried_value_is_one_range(self):
        self.assertEqual([x for x in labels(LOOPCARRIED) if x.startswith("split:total")], [])


class TestGuards(unittest.TestCase):
    def test_a_pin_free_function_is_refused(self):
        self.assertEqual(labels(NOPIN), [])

    def test_eligible_needs_pins(self):
        self.assertEqual(M.T.eligible("void f(void) {}\n", {}, {}), "no pins")

    def test_eligible_accepts_the_exemplar_shape(self):
        self.assertIsNone(M.T.eligible(LOOPS, {}, {}))

    def test_no_candidate_keeps_a_pin_whose_text_changed(self):
        for _, cand, _, _ in M.candidates(LOOPS):
            self.assertIn("ASM_KEEP(render_data);", cand)


class TestArityNote(unittest.TestCase):
    def test_a_two_parameter_prototype_called_with_a_local_is_named(self):
        self.assertEqual(M.arity_review(ARITY), ["func_80064584/2"])

    def test_a_row_without_such_a_call_says_nothing(self):
        self.assertEqual(M.arity_review(LOOPS), [])


if __name__ == "__main__":
    unittest.main()
