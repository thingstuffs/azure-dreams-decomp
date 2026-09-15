"""T66: the same-hard-register merge fires on each of its four forms, refuses everything that would
change the program, and always returns a text with exactly one pin fewer and the same unscored arms.

Every test is textual (no compiler): the generator's contract is that it only deletes a declaration,
moves a declaration, and respells the uses of the variable it deleted - `vf` decides the rest.
"""
import collections
import re
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from pin_census import sites_of, unscored_text
from xform import t66_sameregmerge as M

HEAD = '#include "common.h"\n\n'


def gen(text):
    skips = collections.Counter()
    return M.sameregmerge_candidates(text, skips), skips


def labels(text):
    return [l for l, _ in gen(text)[0]]


def only(text, needle):
    """The one candidate whose label contains `needle`."""
    out = [c for l, c in gen(text)[0] if needle in l]
    assert len(out) == 1, "expected one %r candidate, got %d" % (needle, len(out))
    return out[0]


PLAIN = HEAD + '''void func_test(s32 *arg0) {
    s32 total;
    register s32 first ASM_REG("$3");   /* UNRESOLVED C shape (pin) */
    register s32 second ASM_REG("$3");   /* UNRESOLVED C shape (pin) */

    first = arg0[0] + 1;
    total = first;
    second = arg0[1] + 2;
    total += second;
    arg0[2] = total;
}
'''

CASTED = HEAD + '''void func_test(u8 *arg0) {
    s32 total;
    register u8 *page ASM_REG("$7");   /* UNRESOLVED C shape (pin) */
    register s32 scaled ASM_REG("$7");   /* UNRESOLVED C shape (pin) */

    page = arg0 + 8;
    total = page[3];
    scaled = total * 4;
    arg0[scaled] = 0;
}
'''

HOISTED = HEAD + '''void func_test(s32 *arg0) {
    s32 total;

    total = 0;
    {
        register s32 inner ASM_REG("$2");   /* UNRESOLVED C shape (pin) */
        inner = arg0[0];
        total = inner;
    }
    {
        register s32 later ASM_REG("$2");   /* UNRESOLVED C shape (pin) */
        later = arg0[1];
        total += later;
    }
    arg0[2] = total;
}
'''

TWOARM = HEAD + '''void func_test(s32 *arg0, s32 sel) {
    s32 total;

    total = 0;
    if (sel != 0) {
        register s32 lhs ASM_REG("$2") = arg0[0];   /* UNRESOLVED C shape (pin) */
        total = lhs;
    } else {
        register s32 rhs ASM_REG("$2") = arg0[1];   /* UNRESOLVED C shape (pin) */
        total = rhs + 1;
    }
    arg0[2] = total;
}
'''


class Forms(unittest.TestCase):

    def test_plain_rename(self):
        cand = only(PLAIN, "rename:second->first")
        self.assertNotIn("second", cand)
        self.assertIn("    first = arg0[1] + 2;\n", cand)
        self.assertIn("    total += first;\n", cand)
        self.assertEqual(cand.count('ASM_REG("$3")'), 1)

    def test_both_directions(self):
        got = labels(PLAIN)
        self.assertIn("t66:plain:rename:second->first@$3", got)
        self.assertIn("t66:plain:rename:first->second@$3", got)

    def test_cast_form(self):
        cand = only(CASTED, "cast:scaled->page")
        self.assertIn("page = (u8 *)(total * 4);", cand)
        self.assertIn("arg0[(s32)page] = 0;", cand)
        self.assertNotIn("scaled", cand)

    def test_cast_form_parenthesises_a_postfix_read(self):
        cand = only(CASTED, "cast:page->scaled")
        self.assertIn("scaled = (s32)(arg0 + 8);", cand)
        self.assertIn("total = ((u8 *)scaled)[3];", cand)

    def test_signed_unsigned_pair_is_merged_only_with_casts(self):
        """The cast-free `implicit` spelling was removed in the 2026-09-15 review: merging a u32
        into an s32 with no casts turns a logical shift into an arithmetic one."""
        text = PLAIN.replace("register s32 first", "register u32 first")
        got = [l for l in labels(text) if "->first" in l]
        self.assertEqual(got, ["t66:plain:cast:second->first@$3"])
        self.assertEqual([l for l in labels(text) if "implicit" in l], [])
        cand = only(text, "cast:second->first")
        self.assertIn("first = (u32)(arg0[1] + 2);", cand)
        self.assertIn("total += (s32)first;", cand)

    def test_the_cast_form_desugars_a_compound_assignment(self):
        """`v >>= 5;` is `v = (TV)(v >> 5);` written short - the form-(b) rewrite of it keeps the
        victim's signedness on the operand, which is what the removed `implicit` spelling lost."""
        text = HEAD + '''void func_test(s32 *arg0) {
    register s32 angle ASM_REG("$3");   /* UNRESOLVED C shape (pin) */
    register u32 slot ASM_REG("$3");   /* UNRESOLVED C shape (pin) */

    angle = arg0[0];
    arg0[1] = angle;
    slot = arg0[2];
    slot &= 0x60;
    slot >>= 5;
    arg0[3] = slot;
}
'''
        cand = only(text, "cast:slot->angle")
        self.assertIn("angle = (s32)(arg0[2]);", cand)
        self.assertIn("angle = (s32)(((u32)angle) & (0x60));", cand)
        self.assertIn("angle = (s32)(((u32)angle) >> (5));", cand)
        self.assertIn("arg0[3] = (u32)angle;", cand)
        self.assertNotIn("slot", cand)

    def test_the_cast_form_desugars_an_increment_statement(self):
        text = HEAD + '''void func_test(u8 *arg0) {
    register u8 *page ASM_REG("$7");   /* UNRESOLVED C shape (pin) */
    register s32 count ASM_REG("$7");   /* UNRESOLVED C shape (pin) */

    page = arg0 + 8;
    arg0[0] = page[1];
    count = 0;
    count++;
    arg0[2] = count;
}
'''
        cand = only(text, "cast:count->page")
        self.assertIn("page = (u8 *)(0);", cand)
        self.assertIn("page = (u8 *)(((s32)page) + 1);", cand)

    def test_hoist_moves_the_declaration_to_the_enclosing_block(self):
        cand = only(HOISTED, "hoist:later->inner")
        body = cand.splitlines()
        i = next(k for k, l in enumerate(body) if "ASM_REG" in l)
        self.assertIn("s32 total;", body[i - 1])          # with the other declarations
        self.assertNotIn("later", cand)
        self.assertEqual(cand.count("ASM_REG"), 1)

    def test_hoist_keeps_a_constant_initialiser_and_demotes_anything_else(self):
        text = HEAD + '''void func_test(s32 *arg0) {
    s32 total;

    total = 0;
    {
        register s16 *info ASM_REG("$7") = (s16 *)D_8008333C;   /* UNRESOLVED C shape (pin) */
        total = info[10];
    }
    {
        register s32 unit ASM_REG("$7") = 1;   /* UNRESOLVED C shape (pin) */
        total = unit << total;
    }
    arg0[0] = total;
}
'''
        kept = only(text, "cast+hoist_init:unit->info")
        self.assertIn('register s16 *info ASM_REG("$7") = (s16 *)D_8008333C;', kept)
        self.assertIn("info = (s16 *)(1);", kept)
        self.assertIn("total = (s32)info << total;", kept)
        moved = only(text, "cast+hoist:unit->info")
        self.assertIn('register s16 *info ASM_REG("$7");', moved)
        self.assertIn("info = (s16 *)D_8008333C;", moved)   # the initialiser stayed behind
        # a non-constant initialiser is never carried up
        loaded = text.replace("(s16 *)D_8008333C", "(s16 *)arg0[4]")
        self.assertEqual([l for l in labels(loaded) if "hoist_init" in l], [])

    def test_two_arm_form(self):
        got = labels(TWOARM)
        self.assertIn("t66:twoarm:rename+hoist:rhs->lhs@$2", got)
        cand = only(TWOARM, "rhs->lhs")
        self.assertIn("    register s32 lhs ASM_REG(\"$2\");", cand)
        self.assertIn("        lhs = arg0[0];", cand)       # each arm keeps its own assignment
        self.assertIn("        lhs = arg0[1];", cand)
        self.assertNotIn("rhs", cand)

    def test_two_case_arms(self):
        text = HEAD + '''void func_test(s32 *arg0, s32 sel) {
    s32 total;

    total = 0;
    switch (sel) {
    case 0:
        {
            register s32 lhs ASM_REG("$2");   /* UNRESOLVED C shape (pin) */
            lhs = arg0[0];
            total = lhs;
        }
        break;
    case 1:
        {
            register s32 rhs ASM_REG("$2");   /* UNRESOLVED C shape (pin) */
            rhs = arg0[1];
            total = rhs + 1;
        }
        break;
    }
    arg0[2] = total;
}
'''
        self.assertIn("t66:twoarm:rename+hoist:rhs->lhs@$2", labels(text))

    def test_m2c_names_both_copies_alike(self):
        text = HOISTED.replace("later", "inner")
        cand = only(text, "hoist:inner->inner")
        self.assertEqual(cand.count("ASM_REG"), 1)
        self.assertEqual(cand.count("inner = arg0["), 2)


class Refusals(unittest.TestCase):

    def refuses(self, text, reason):
        out, skips = gen(text)
        self.assertEqual(out, [], "expected no candidate, got %r" % ([l for l, _ in out],))
        self.assertIn(reason, skips, dict(skips))

    def test_overlapping_lifetimes(self):
        self.refuses(HEAD + '''void func_test(s32 *arg0) {
    register s32 first ASM_REG("$3");   /* pin */
    register s32 second ASM_REG("$3");   /* pin */

    first = arg0[0];
    second = arg0[1];
    arg0[2] = first + second;
}
''', "interference")

    def test_live_around_a_loop_back_edge(self):
        self.refuses(HEAD + '''void func_test(s32 *arg0) {
    s32 i;
    register s32 base ASM_REG("$3");   /* pin */
    register s32 tmp ASM_REG("$3");   /* pin */

    base = arg0[0];
    i = 0;
    while (i < 4) {
        tmp = arg0[i] + base;
        arg0[i] = tmp;
        i += 1;
    }
    arg0[7] = 0;
}
''', "loop-backedge")

    def test_address_taken(self):
        self.refuses(PLAIN.replace("    total = first;", "    func_80000000(&first);"),
                     "address-taken")

    def test_narrow_type_in_the_cast_form(self):
        self.refuses(PLAIN.replace("register s32 first", "register u16 first"),
                     "type-mismatch-narrow")

    def test_macro_argument(self):
        self.refuses(PLAIN.replace("    total += second;", "    ASM_KEEP(second);"),
                     "in-macro-arg")

    def test_same_named_inner_scope_local(self):
        self.refuses(PLAIN.replace("    arg0[2] = total;", """    {
        s32 second;
        second = arg0[4];
        arg0[5] = second;
    }
    arg0[2] = total;"""), "shadowed-inner-local")

    def test_uses_inside_an_ifdef_arm(self):
        self.refuses(PLAIN.replace("    second = arg0[1] + 2;", """#ifdef NON_MATCHING
    second = arg0[9];
#else
    second = arg0[1] + 2;
#endif"""), "pp-guarded-mention")

    def test_a_port_fallback_declaration_beside_the_pin(self):
        """The real shape the 2026-09-15 review caught: `#ifdef __mips__` guards the pinned
        declaration and the `#else` arm re-declares the same name unpinned.  `arm_labels` calls
        every one of those lines `both`, so `unscored_text` is blind to an edit in the `#else`
        arm - `dungeon/func_81856800` landed `u8 *(u8 *)modulo_magic;` there.  The module's own
        region map has to refuse it."""
        text = HEAD + '''void func_test(s32 *arg0) {
    s32 total;
#ifdef __mips__
    register s32 first ASM_REG("$3");   /* UNRESOLVED C shape (pin) */
    register s32 second ASM_REG("$3");   /* UNRESOLVED C shape (pin) */
#else
    s32 first;
    s32 second;
#endif

    first = arg0[0] + 1;
    total = first;
    second = arg0[1] + 2;
    total += second;
    arg0[2] = total;
}
'''
        self.refuses(text, "pp-guarded-mention")

    def test_a_guarded_use_of_the_victim_is_refused(self):
        self.refuses(PLAIN.replace("    total += second;", """#ifdef __mips__
    total += second;
#else
    total += second + 1;
#endif"""), "pp-guarded-mention")

    def test_a_hoist_anchor_inside_a_guard_is_refused(self):
        """The block the declaration would move to ends its declaration run inside a region: the
        moved declaration would land under the `#ifdef` and only one build would see it."""
        text = HOISTED.replace("    s32 total;", """    s32 total;
#ifdef __mips__
    s32 scratch;
#endif""")
        out, skips = gen(text)
        self.assertEqual([l for l, _ in out], [])
        self.assertIn("pp-guarded-anchor", skips, dict(skips))

    def test_the_pp_signature_is_the_candidate_level_invariant(self):
        text = PLAIN.replace("    total = first;", """#ifdef __mips__
    total = first;
#endif""")
        sig = M._pp_sig(text)
        self.assertEqual(sig, ("#ifdef __mips__", "    total = first;", "#endif"))
        for _, cand in gen(text)[0]:
            self.assertEqual(M._pp_sig(cand), sig)

    def test_an_initialiser_is_never_hoisted_above_a_switchs_first_case(self):
        """`_insert_after` returns the `switch (...) {` line for a declaration-free switch body;
        control enters at a `case`, so an initialiser parked above the first one is jumped over and
        the merged variable is read uninitialised.  The BARE declaration there is still legal."""
        text = HEAD + '''void func_test(s32 *arg0, s32 sel) {
    s32 total;

    total = 0;
    switch (sel) {
    case 0:
        {
            register s32 lhs ASM_REG("$4") = 5;   /* UNRESOLVED C shape (pin) */
            total = lhs;
        }
        break;
    case 1:
        {
            register s32 rhs ASM_REG("$4") = 6;   /* UNRESOLVED C shape (pin) */
            total = rhs + 1;
        }
        break;
    }
    arg0[0] = total;
}
'''
        got = labels(text)
        # nothing lands an initialiser in the SWITCH BODY; the function-body target is reachable at
        # entry, so `hoistfn_init` stays
        self.assertEqual([l for l in got if "+hoist_init" in l], [])
        self.assertIn("t66:twoarm:rename+hoist:rhs->lhs@$4", got)
        self.assertIn("t66:twoarm:rename+hoistfn_init:rhs->lhs@$4", got)
        _, skips = gen(text)
        self.assertGreaterEqual(skips["unreachable-anchor"], 1)
        cand = [c for l, c in gen(text)[0] if l == "t66:twoarm:rename+hoist:rhs->lhs@$4"][0]
        self.assertIn('    switch (sel) {\n        register s32 lhs ASM_REG("$4");   /*', cand)
        self.assertIn("            lhs = 5;", cand)      # each arm keeps its own assignment
        self.assertIn("            lhs = 6;", cand)

    def test_decl_unparsed_is_counted_per_ordered_pair(self):
        """It used to be counted once per family MEMBER, putting it on a different scale from
        every other refusal in the same table."""
        text = PLAIN.replace("    s32 total;",
                             '    s32 total;\n    register s32 a, b ASM_REG("$3");   /* pin */')
        skips = gen(text)[1]
        # three members on $3, one of them unparsable: 3*2 - 2*1 = 4 ordered pairs lost
        self.assertEqual(skips["decl-unparsed"], 4)

    def test_a_struct_member_of_that_name_is_not_a_use(self):
        text = HEAD + '''void func_test(void *arg0) {
    register s32 first ASM_REG("$3");   /* pin */
    register s32 second ASM_REG("$3");   /* pin */

    first = ((S_A *)arg0)->second;
    ((S_A *)arg0)->first = first;
    second = ((S_A *)arg0)->first;
    ((S_A *)arg0)->second = second;
}
'''
        cand = only(text, "rename:second->first")
        self.assertIn("((S_A *)arg0)->second = first;", cand)
        self.assertIn("first = ((S_A *)arg0)->second;", cand)

    def test_a_different_hard_register_is_not_a_family(self):
        out, skips = gen(PLAIN.replace('second ASM_REG("$3")', 'second ASM_REG("$4")'))
        self.assertEqual(out, [])
        self.assertEqual(dict(skips), {})

    def test_a_host_name_that_means_something_else_there(self):
        # `inner` may not host: an unrelated local of that name already lives in the block the
        # declaration would move to.  The other direction is untouched by that.
        text = HOISTED.replace("    s32 total;", "    s32 total;\n    s32 inner;")
        out, skips = gen(text)
        self.assertEqual([l for l, _ in out], ["t66:hoist:rename+hoist:inner->later@$2"])
        self.assertEqual(skips["host-name-collision"], 1)


class Contract(unittest.TestCase):

    def test_every_candidate_drops_exactly_one_pin_and_no_unscored_text(self):
        for name, text in (("plain", PLAIN), ("cast", CASTED), ("hoist", HOISTED),
                           ("twoarm", TWOARM)):
            pins = len(sites_of(text))
            for label, cand in gen(text)[0]:
                self.assertEqual(len(sites_of(cand)), pins - 1, "%s: %s" % (name, label))
                self.assertEqual(unscored_text(cand), unscored_text(text), label)
                self.assertNotIn("__asm__", cand)
                self.assertNotIn("volatile", cand)
                self.assertNotIn("while (0)", cand)

    def test_the_menu_is_bounded_and_nearest_first(self):
        text = PLAIN
        out = M.sameregmerge_candidates(text, cap=1)
        self.assertEqual(len(out), 1)
        skips = collections.Counter()
        ps = M.pairs_of(text, skips)
        self.assertEqual([p.dist for p in ps], sorted(p.dist for p in ps))

    def test_eligible(self):
        row = {"cfg": "2.7.2"}
        self.assertIsNone(M.T.eligible(PLAIN, row, {}))
        self.assertEqual(M.T.eligible(PLAIN.replace('second ASM_REG("$3")',
                                                    'second ASM_REG("$4")'), row, {}),
                         "no same-register pin family")
        self.assertEqual(M.T.eligible(PLAIN, {}, {}), "missing compiler recipe")


class Cfg(unittest.TestCase):
    """The statement-level control-flow graph the disjointness test is decided on."""

    def flow(self, text):
        from xform import natural as Nat
        from xform.t51_sched_order import units
        t = Nat._T(text)
        F = M._functions(t)[0]
        _, recs = units(text)
        return F, M.Flow(F, recs)

    def test_goto_edges_and_back_edges(self):
        text = HEAD + '''void func_test(s32 *arg0) {
    s32 i;

    i = 0;
top:
    i += 1;
    if (i < 4) {
        goto top;
    }
    arg0[0] = i;
}
'''
        F, flow = self.flow(text)
        top = flow.labels["top"]
        goto = next(k for k in flow.nodes if "goto top" in F.ml[k])
        self.assertEqual(flow.succ[goto], {top})

    def test_a_computed_goto_reaches_every_label(self):
        text = HEAD + '''void func_test(s32 *arg0) {
    goto *D_80000000[arg0[0]];
one:
    arg0[1] = 1;
    return;
two:
    arg0[2] = 2;
}
'''
        F, flow = self.flow(text)
        k = next(k for k in flow.nodes if "goto *" in F.ml[k])
        self.assertEqual(flow.succ[k], set(flow.labels.values()))
        self.assertEqual(len(flow.labels), 2)

    def test_an_unclassifiable_statement_reaches_everything_later(self):
        text = HEAD + '''void func_test(s32 *arg0) {
    s32 i;

    i = 0;
    if (i)
        goto nowhere;
    arg0[0] = i;
    arg0[1] = i;
}
'''
        F, flow = self.flow(text)
        k = next(k for k in flow.nodes if "goto nowhere" in F.ml[k])
        self.assertIn(k, flow.unknown)
        self.assertEqual(flow.succ[k], {x for x in flow.nodes if x > k})


if __name__ == "__main__":
    unittest.main()
