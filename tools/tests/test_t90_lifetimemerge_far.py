"""T90: pair finding, the two disjointness tiers and the rewrite forms are textual; the listing
screen and `vf` are not exercised."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t90_lifetimemerge_far as M  # noqa: E402

FAR = '''#include "common.h"
s32 f(void *origin) {
    s32 result;
    s32 random_value;
    void *callback;
    void *effect;

    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        callback = &D_80024340;
        ASM_KEEP(callback);   /* UNRESOLVED C shape (pin) */
        ((S_0 *)effect)->unk_10 = callback;
        ((S_0 *)effect)->unk_04 = origin->unk_02;
        ((S_0 *)effect)->unk_06 = origin->unk_06;
        ((S_0 *)effect)->unk_08 = origin->unk_0A;
        func_8004491C(effect, &D_80045340);
        random_value = rand();
        result = random_value + 1;
        return result;
    }
    result = 0;
    return result;
}
'''

COUNTERS = '''#include "common.h"
void g(void *entity) {
    s32 actor_index;
    register s32 actors_left ASM_REG("$16");   /* UNRESOLVED C shape (pin) */
    void *slot_cursor;

    if (entity != NULL) {
        actor_index = 0;
        do {
            func_80047784(entity, actor_index);
            actor_index += 1;
        } while (actor_index < 2);
    }
    if ((*(u16 *)D_80013714) & 8) {
        actors_left = 1;
        slot_cursor = D_800E3D7C;
        do {
            func_800478E8(slot_cursor);
            actors_left -= 1;
            slot_cursor -= 4;
        } while (actors_left >= 0);
    }
}
'''

OVERLAP = '''#include "common.h"
void h(void *entity) {
    s32 first;
    s32 second;

    first = func_800644B8(1);
    ASM_KEEP(first);   /* UNRESOLVED C shape (pin) */
    second = func_800644B8(2);
    D_80020090 = first + second;
}
'''

INLOOP = '''#include "common.h"
void k(s32 n) {
    s32 early;
    s32 late;

    do {
        early = func_800644B8(n);
        ASM_KEEP(early);   /* UNRESOLVED C shape (pin) */
        D_80020090 = early;
        late = func_80064584(n);
        D_800200A8 = late;
        n--;
    } while (n >= 0);
}
'''


def labels(text):
    return [c[0] for c in M.candidates(text)]


def by_label(text):
    return dict((c[0], c[1]) for c in M.candidates(text))


class TestPairs(unittest.TestCase):
    def test_a_pointer_and_a_later_word_are_paired_across_eight_statements(self):
        self.assertIn("far-cast:callback->random_value@10", labels(FAR))

    def test_the_cast_form_casts_both_ways(self):
        cand = by_label(FAR)["far-cast:callback->random_value@10"]
        self.assertIn("random_value = (s32)(&D_80024340);", cand)
        self.assertIn("((S_0 *)effect)->unk_10 = (void *)random_value;", cand)

    def test_the_guest_declaration_goes(self):
        cand = by_label(FAR)["far-cast:callback->random_value@10"]
        self.assertNotIn("void *callback;", cand)
        self.assertIn("    s32 random_value;\n", cand)

    def test_the_statement_pin_is_left_for_the_erase_plan(self):
        cand = by_label(FAR)["far-cast:callback->random_value@10"]
        self.assertIn("ASM_KEEP(callback);", cand)

    def test_two_loop_counters_merge(self):
        self.assertIn("far-rename:actors_left->actor_index@15", labels(COUNTERS))

    def test_the_register_pinned_declaration_goes_with_the_merge(self):
        cand = by_label(COUNTERS)["far-rename:actors_left->actor_index@15"]
        self.assertNotIn("ASM_REG", cand)
        self.assertIn("        actor_index = 1;\n", cand)
        self.assertIn("        } while (actor_index >= 0);\n", cand)

    def test_the_pinned_guest_is_ranked_first(self):
        self.assertTrue(labels(COUNTERS)[0].startswith("far-rename:actors_left"), labels(COUNTERS))


class TestRefusals(unittest.TestCase):
    def test_overlapping_ranges_are_refused(self):
        self.assertEqual([x for x in labels(OVERLAP) if "first->second" in x or "second->first" in x], [])

    def test_a_common_loop_refuses_the_text_tier(self):
        import varset as V
        from collections import Counter
        vfn = V.functions(INLOOP, Counter())[0]
        # both ranges sit inside the one do-while, so the text tier never offers the pair even
        # though they do not overlap line by line (the CFG tier may still accept it, and does)
        self.assertFalse(M._text_disjoint(vfn, [6, 8], [9, 10]))
        self.assertEqual([x for x in labels(INLOOP) if x.startswith("text-")], [])

    def test_eligible_needs_pins(self):
        self.assertEqual(M.T.eligible("void f(void) {}\n", {}, {}), "no pins")

    def test_eligible_accepts_the_exemplar_shape(self):
        self.assertIsNone(M.T.eligible(FAR, {}, {}))

    def test_no_candidate_invents_a_pin(self):
        for _, cand, _, _ in M.candidates(FAR) + M.candidates(COUNTERS):
            self.assertLessEqual(cand.count("ASM_"), max(FAR.count("ASM_"), COUNTERS.count("ASM_")))


class TestDisjointHelper(unittest.TestCase):
    def test_text_disjoint_needs_separation(self):
        import varset as V
        from collections import Counter
        vfn = V.functions(OVERLAP, Counter())[0]
        self.assertFalse(M._text_disjoint(vfn, [5, 7], [6, 8]))
        self.assertTrue(M._text_disjoint(vfn, [5, 6], [7, 8]))


if __name__ == "__main__":
    unittest.main()
