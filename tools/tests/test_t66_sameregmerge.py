"""T66: the same-hard-register merge fires on each of its four forms, refuses everything that would
change the program, and always returns a text with exactly one pin fewer and the same unscored arms.

Every test is textual (no compiler): the generator's contract is that it only deletes a declaration,
moves a declaration, and respells the uses of the variable it deleted - `vf` decides the rest.
"""
import collections
import contextlib
import os
import re
import sys
import unittest
from pathlib import Path
from unittest import mock

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from pin_census import sites_of, unscored_text
from xform import t66_sameregmerge as M

HEAD = '#include "common.h"\n\n'


def off(*switches):
    """One of the round-29 openings turned off (they default ON and are read per call)."""
    return mock.patch.dict(os.environ, {k: "0" for k in switches})


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


# the row-local value macro several slus rows define themselves (both parameters are values)
U16_DEF = '#define U16_AT(p, n) (*(u16 *)((u8 *)(p) + (n)))\n'


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
        # the clash is a refusal only with the round-31 default off: T66_TRY_INTERFERENCE ships 1 now
        with mock.patch.dict(os.environ, {"T66_TRY_INTERFERENCE": "0"}):
            self._overlapping_lifetimes()

    def _overlapping_lifetimes(self):
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

    def test_address_taken_through_a_cast(self):
        self.refuses(PLAIN.replace("    total = first;", "    func_80000000((s32 *) &first);"),
                     "address-taken")

    def test_binary_and_with_spaces_is_not_address_taken(self):
        # round 73 (T66_BINARY_AND): `(f(x) & v)` and `y & v` are the AND operator
        text = PLAIN.replace("    total += second;", "    total = (func_80000000(total) & second);")
        cands, skips = gen(text)
        self.assertNotIn("address-taken", skips)
        self.assertTrue(cands)
        text = PLAIN.replace("    total += second;", "    total = total & second;")
        self.assertTrue(gen(text)[0])
        with off("T66_BINARY_AND"):
            self.refuses(text, "address-taken")

    def test_narrow_type_in_the_cast_form(self):
        self.refuses(PLAIN.replace("register s32 first", "register u16 first"),
                     "type-mismatch-narrow")

    def test_macro_argument_with_the_opening_off(self):
        with off("T66_MACRO_ARGS"):
            self.refuses(PLAIN.replace("    total += second;", "    ASM_KEEP(second);"),
                         "in-macro-arg")

    def test_same_named_inner_scope_local(self):
        """Reopened by T66_SHADOW (round 30); with the opening off it is the round-29 refusal."""
        with off("T66_SHADOW"):
            self.refuses(SHADOWED, "shadowed-inner-local")

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
        with off("T66_RENAME_HOST"):
            out, skips = gen(text)
        self.assertEqual([l for l, _ in out], ["t66:hoist:rename+hoist:inner->later@$2"])
        self.assertEqual(skips["host-name-collision"], 1)


COLLIDE = HEAD + '''void func_test(s32 *arg0) {
    s32 total;
    s32 inner;
    s32 later;

    total = 0;
    {
        register s32 inner ASM_REG("$2") = 7;   /* UNRESOLVED C shape (pin) */
        total = inner;
    }
    {
        register s32 later ASM_REG("$2");   /* UNRESOLVED C shape (pin) */
        later = arg0[1];
        total += later;
    }
    inner = arg0[3];
    later = arg0[4];
    arg0[2] = total + inner + later;
}
'''

# m2c's own spelling of ONE retail variable declared four times: every copy is called `slot` and
# every copy is pinned to the same hard register (town/func_800B1544 has five of these).
SAMENAME = HEAD + '''void func_test(s32 *arg0) {
    s32 total;

    total = 0;
    {
        register s32 slot ASM_REG("$2");   /* UNRESOLVED C shape (pin) */
        slot = arg0[0];
        total = slot;
    }
    {
        register s32 slot ASM_REG("$2");   /* UNRESOLVED C shape (pin) */
        slot = arg0[1];
        total += slot;
    }
    {
        register s32 slot ASM_REG("$2");   /* UNRESOLVED C shape (pin) */
        slot = arg0[2];
        total += slot;
    }
    arg0[3] = total;
}
'''

KEPT = PLAIN.replace("    total += second;", "    ASM_KEEP(second);\n    total += second;")

# ------------------------------------------------------------------ round 30, the five openings

# (1) T66_DECL_RUN: the three shapes the declaration walk used to break on.  Every pin below the
# stopper was invisible before it - `decl-unparsed`, the largest refusal of the round-30 table.
LABEL_TABLE = HEAD + '''void func_test(u8 *arg0) {
    static void *const state_labels[] = { &&one, &&two };
    s32 total;
    register u8 *page ASM_REG("$7");   /* UNRESOLVED C shape (pin) */
    register s32 scaled ASM_REG("$7");   /* UNRESOLVED C shape (pin) */

    (void) state_labels;
    page = arg0 + 8;
    total = page[3];
    scaled = total * 4;
    arg0[scaled] = 0;
one:
two:
    return;
}
'''

ANON_STRUCT = HEAD + '''void func_test(s32 *arg0) {
    volatile struct {
        u16 a;
        u16 b;
    } camera_angles;
    s16 vertices[2][3][4];
    void *volatile perspective_out;
    s32 total;
    register s32 first ASM_REG("$3");   /* UNRESOLVED C shape (pin) */
    register s32 second ASM_REG("$3");   /* UNRESOLVED C shape (pin) */

    camera_angles.a = 1;
    vertices[0][0][0] = 2;
    perspective_out = arg0;
    first = arg0[0] + 1;
    total = first;
    second = arg0[1] + 2;
    total += second;
    arg0[2] = total;
}
'''

# (2) T66_ASM_OPERAND: the victim is named by a keep AND the pair needs the cast spelling.
ASMCAST = CASTED.replace("    arg0[scaled] = 0;", "    ASM_KEEP(scaled);\n    arg0[scaled] = 0;")

# (3) T66_INIT_PLACE: the victim carries an initialiser and a LATER declaration of the same run
# carries one too, so the demoted assignment has to cross it.
INITRUN = HEAD + '''void func_test(s32 *arg0) {
    s32 total;
    register s32 second ASM_REG("$3") = 7;   /* UNRESOLVED C shape (pin) */
    s32 later = 3;
    register s32 first ASM_REG("$3");   /* UNRESOLVED C shape (pin) */

    total = second + later;
    first = arg0[0];
    total += first;
    arg0[2] = total;
}
'''

# (4) T66_SHADOW: an inner block declares the victim's name again.
SHADOWED = PLAIN.replace("    second = arg0[1] + 2;", """    {
        s32 second;
        second = arg0[4];
        arg0[5] = second;
    }
    second = arg0[1] + 2;""")

# (5) T66_TRY_INTERFERENCE: two lifetimes that DO clash at the C level, on one hard register.
OVERLAP = HEAD + '''void func_test(s32 *arg0) {
    register s32 first ASM_REG("$3");   /* UNRESOLVED C shape (pin) */
    register s32 second ASM_REG("$3");   /* UNRESOLVED C shape (pin) */

    first = arg0[0];
    second = arg0[1];
    arg0[2] = first + second;
}
'''

# T66_COMPOUND: a write `_is_kill` will not call a kill (the rhs reads the victim), and an
# assignment THROUGH the victim (`*v = e`), which is a read of it.
SELFREAD = HEAD + '''void func_test(u8 *arg0) {
    s32 total;
    register void *slot ASM_REG("$7");   /* UNRESOLVED C shape (pin) */
    register s32 scaled ASM_REG("$7");   /* UNRESOLVED C shape (pin) */

    slot = arg0;
    total = ((S_0 *)slot)->unk_00;
    slot = (u8 *)slot + 4;
    total += ((S_0 *)slot)->unk_04;
    scaled = total * 4;
    arg0[scaled] = 0;
}
'''

DEREF_WRITE = HEAD + '''void func_test(u32 *arg0) {
    s32 total;
    register u32 *link ASM_REG("$7");   /* UNRESOLVED C shape (pin) */
    register s32 scaled ASM_REG("$7");   /* UNRESOLVED C shape (pin) */

    link = arg0;
    *link = (*link & 0xF) | 0x10;
    total = 3;
    scaled = total * 4;
    arg0[scaled] = 0;
}
'''


class RenameHost(unittest.TestCase):
    """T66_RENAME_HOST: the merge retried with the surviving variable renamed."""

    def test_the_victims_name_is_preferred_when_it_is_free(self):
        text = HOISTED.replace("    s32 total;", "    s32 total;\n    s32 inner;")
        got = labels(text)
        self.assertIn("t66:hoist:rename+hoist:later->later@$2+vname", got)
        cand = only(text, "+vname")
        self.assertIn('    register s32 later ASM_REG("$2");', cand)
        self.assertIn("    s32 inner;\n", cand)          # the colliding local is untouched
        self.assertEqual(cand.count("ASM_REG"), 1)
        self.assertNotIn("inner =", cand)                # every use of the host was rewritten

    def test_a_fresh_name_when_the_victims_name_is_taken_too(self):
        """`inner` collides in the target block and `later` is not free either (the host's own
        mentions would capture it), so the surviving declaration becomes `inner_m` - type,
        register binding and initialiser kept."""
        got = labels(COLLIDE)
        self.assertIn("t66:hoist:rename+hoist_init:later->inner_m@$2+hostm", got)
        cand = only(COLLIDE, "rename+hoist_init:later->inner_m")
        self.assertIn('    register s32 inner_m ASM_REG("$2") = 7;', cand)
        self.assertIn("    inner_m = arg0[1];", cand)
        self.assertIn("    total += inner_m;", cand)
        self.assertIn("    inner = arg0[3];", cand)      # the unrelated locals keep their names
        self.assertIn("    later = arg0[4];", cand)
        self.assertIn("arg0[2] = total + inner + later;", cand)
        self.assertEqual(cand.count("ASM_REG"), 1)

    def test_a_colliding_host_that_is_itself_pinned_in_the_inner_block(self):
        """Three pinned declarations of ONE name on ONE register: merging two of them may not
        touch the third, and the pin count drops by exactly one."""
        pins = len(sites_of(SAMENAME))
        out, skips = gen(SAMENAME)
        self.assertTrue(out, dict(skips))
        third = '        register s32 slot ASM_REG("$2");   /* UNRESOLVED C shape (pin) */\n'
        for label, cand in out:
            self.assertIn("+hostm", label)
            self.assertEqual(len(sites_of(cand)), pins - 1, label)
            self.assertIn("slot_m", cand, label)
            self.assertEqual(cand.count(third), 1, label)   # exactly one untouched copy remains
            self.assertEqual(cand.count('ASM_REG("$2")'), 2, label)

    def test_a_name_already_in_the_function_is_never_taken(self):
        text = COLLIDE.replace("    s32 inner;", "    s32 inner;\n    s32 inner_m;")
        cand = only(text, "rename+hoist_init:later->inner_m2")
        self.assertIn('    register s32 inner_m2 ASM_REG("$2") = 7;', cand)
        self.assertIn("    s32 inner_m;\n", cand)

    def test_the_opening_only_fires_where_the_collision_blocks_the_merge(self):
        """A pair with no collision is spelled exactly as it was before the opening."""
        self.assertEqual([l for l in labels(HOISTED) if "+hostm" in l or "+vname" in l], [])
        self.assertEqual(labels(PLAIN),
                         ["t66:plain:rename:second->first@$3", "t66:plain:rename:first->second@$3"])

    def test_the_collision_count_and_the_reopened_count_add_up(self):
        text = HOISTED.replace("    s32 total;", "    s32 total;\n    s32 inner;")
        with off("T66_RENAME_HOST"):
            before = gen(text)[1]
        after = gen(text)[1]
        self.assertEqual(before["host-name-collision"], 1)
        self.assertEqual(after["host-name-collision"] + after["host-name-collision-reopened"],
                         before["host-name-collision"])


class MacroArgs(unittest.TestCase):
    """T66_MACRO_ARGS: a mention inside a macro argument is a use like any other."""

    def test_a_keep_on_the_victim_becomes_a_keep_on_the_host(self):
        pins = len(sites_of(KEPT))
        cand = only(KEPT, "rename:second->first")
        self.assertIn("    ASM_KEEP(first);\n", cand)
        self.assertNotIn("second", cand)
        self.assertEqual(len(sites_of(cand)), pins - 1)
        # the keep is still a keep, at the same point, and nothing else about it moved
        self.assertEqual(M._pin_key(cand)[("ASM_KEEP", "first", "")], 1)
        self.assertEqual(sum(1 for s in sites_of(cand) if s[1] == "ASM_KEEP"),
                         sum(1 for s in sites_of(KEPT) if s[1] == "ASM_KEEP"))

    def test_a_value_macro_argument_is_renamed(self):
        text = U16_DEF + PLAIN.replace("    total += second;",
                                       "    total += U16_AT(arg0, second);")
        cand = only(text, "rename:second->first")
        self.assertIn("    total += U16_AT(arg0, first);\n", cand)

    def test_a_cast_read_inside_a_macro_argument_is_parenthesised(self):
        text = U16_DEF + CASTED.replace("    arg0[scaled] = 0;",
                                        "    arg0[0] = U16_AT(arg0, scaled);")
        cand = only(text, "cast:scaled->page")
        self.assertIn("U16_AT(arg0, ((s32)page));", cand)

    def test_the_cast_form_refuses_an_asm_operand_with_the_opening_off(self):
        """`ASM_KEEP(var)` is `__asm__ __volatile__("" : "=r"(var) : "0"(var))`: `(s32)page` is not
        an lvalue there, so before T66_ASM_OPERAND the cast spelling of that pair had to go."""
        text = CASTED.replace("    arg0[scaled] = 0;", "    ASM_KEEP(scaled);")
        with off("T66_ASM_OPERAND"):
            out, skips = gen(text)
        # the direction that would CAST the keep's operand is gone; the other direction, which only
        # respells `page`, is untouched (the keep still names `scaled`, which survives)
        self.assertEqual([l for l, _ in out], ["t66:plain:cast:page->scaled@$7+macroarg"])
        self.assertEqual(skips["asm-operand-cast"], 1)
        self.assertIn("    ASM_KEEP(scaled);\n", out[0][1])

    def test_a_stringifying_macro_defined_by_the_row_is_refused(self):
        text = ('#define NAME_OF(x) #x\n'
                + PLAIN.replace("    total += second;", "    func_80000000(NAME_OF(second));"))
        out, skips = gen(text)
        self.assertEqual([l for l, _ in out], [])
        self.assertEqual(skips["in-macro-arg-stringify"], 2)

    def test_a_lowercase_stringifying_macro_is_refused_too(self):
        """`MACROARG_RE`'s uppercase shape decides the CLASS, but a name in the refuse set is looked
        for whatever its case: a row-local `#define name_of(x) #x` would otherwise be detected as a
        stringifier and then never consulted, and `name_of(V)` would be renamed."""
        text = ('#define name_of(x) #x\n'
                + PLAIN.replace("    total += second;", "    func_80000000(name_of(second));"))
        self.assertIn("name_of", M._stringify_macros(text))
        out, skips = gen(text)
        self.assertEqual([l for l, _ in out], [])
        self.assertEqual(skips["in-macro-arg-stringify"], 2)
        self.assertEqual(M._macros_at("    f(name_of(v));", 14, ("name_of",)), ["name_of"])
        self.assertEqual(M._macros_at("    f(name_of(v));", 14), [])

    def test_a_macro_that_passes_its_parameter_to_a_stringifier_is_refused(self):
        """`#define OUTER(y) INNER(y)` over `#define INNER(x) #x` stringifies y: `_hash_params`
        reads only the direct body, so the refuse set is closed to a fixpoint."""
        defs = [("INNER", ["x"], "#x"), ("OUTER", ["y"], "INNER(y)"),
                ("UNRELATED", ["z"], "INNER(3) + (z)")]
        self.assertEqual(sorted(M._close_stringify(defs, {"INNER"})), ["INNER", "OUTER"])
        text = ('#define INNER(x) #x\n#define OUTER(y) INNER(y)\n'
                + PLAIN.replace("    total += second;", "    func_80000000(OUTER(second));"))
        self.assertIn("OUTER", M._stringify_macros(text))
        self.assertEqual(gen(text)[1]["in-macro-arg-stringify"], 2)
        # over include/ today the closure adds nothing to the four direct stringifiers
        direct = (set(M.KNOWN_STRINGIFY) | set(M.NEVER_IN_MACRO)
                  | {n for n, p, b in M._header_defs() if M._hash_params(p, b)})
        self.assertEqual(set(M._header_stringify()) - direct, set())
        self.assertEqual(sorted(direct), ["ASM_LIVE_SIBCALL_PIN", "ASM_REG",
                                          "ASM_SHAPE_D_SIBCALL_PIN", "INCLUDE_ASM",
                                          "INCLUDE_RODATA"])

    def test_a_header_stringifier_is_refused_by_name(self):
        self.assertIn("ASM_LIVE_SIBCALL_PIN", M._stringify_macros(""))
        self.assertIn("INCLUDE_ASM", M._stringify_macros(""))
        text = PLAIN.replace("    total += second;", "    ASM_LIVE_SIBCALL_PIN(second, 4);")
        out, skips = gen(text)
        self.assertEqual([l for l, _ in out], [])
        self.assertEqual(skips["in-macro-arg-stringify"], 2)

    def test_a_literal_hash_in_an_asm_template_is_not_a_stringify(self):
        """`__asm__("#maspsx_pagebase_pin %0" : "+r"(var))` carries a `#` inside a STRING."""
        self.assertNotIn("ASM_PAGEBASE_PIN", M._stringify_macros(""))
        self.assertNotIn("ASM_TAILSLOT_PIN", M._stringify_macros(""))
        self.assertNotIn("ASM_KEEP", M._stringify_macros(""))
        self.assertEqual(M._hash_params(["var"], '__asm__("#maspsx_pin %0" : "+r"(var))'), [])
        self.assertEqual(M._hash_params(["imm"], '__asm__("#p " #imm)'), ["imm"])
        self.assertEqual(M._hash_params(["a", "b"], "x##a##b"), ["a", "b"])

    def test_the_asm_reg_binding_is_never_renamed(self):
        """A function whose local is called like a register: the merge may rewrite the DECLARED
        NAME and nothing inside `ASM_REG("...")`."""
        text = HEAD + '''void func_test(s32 *arg0) {
    s32 total;
    register s32 s0 ASM_REG("$s0");   /* UNRESOLVED C shape (pin) */
    register s32 s0b ASM_REG("$s0");   /* UNRESOLVED C shape (pin) */

    s0 = arg0[0];
    total = s0;
    s0b = arg0[1];
    total += s0b;
    arg0[2] = total;
}
'''
        out, skips = gen(text)
        self.assertTrue(out, dict(skips))
        for label, cand in out:
            self.assertEqual(cand.count('ASM_REG("$s0")'), 1, label)
            self.assertNotIn('ASM_REG("$s0b")', cand)
        self.assertIn("ASM_REG", M._stringify_macros(text))
        line = '    x = ASM_REG(v) + FOO(BAR(v));'
        self.assertEqual(M._macros_at(line, line.index("v)")), ["ASM_REG"])
        self.assertEqual(M._macros_at(line, line.rindex("v)")), ["FOO", "BAR"])

    def test_a_mention_inside_an_asm_reg_argument_is_refused(self):
        text = PLAIN.replace("    total += second;", "    total += ASM_REG(second);")
        out, skips = gen(text)
        self.assertEqual([l for l, _ in out], [])
        self.assertEqual(skips["in-asm-reg-binding"], 2)

    # ---------------- a macro parameter that is a NAME, not a value (round-29 review)

    def test_a_row_local_macro_whose_parameter_is_a_member_name_is_refused(self):
        """`#define ZONE_OF(F) (D_80024020[zone_id].F)` pastes its argument after a `.`: renaming
        the variable there would read a DIFFERENT MEMBER - a different offset, a different program.
        `#`/`##` cannot see this class, and it is in the tree (`CURRENT_ZONE`/`OLD_ZONE`/
        `CANDIDATE_ZONE` in src/town/func_8095563C.c)."""
        text = ('#define ZONE_OF(F) (D_80024020[zone_id].F)\n'
                + PLAIN.replace("    total += second;", "    total += ZONE_OF(second);"))
        out, skips = gen(text)
        self.assertEqual([l for l, _ in out], [])
        self.assertEqual(skips["in-macro-arg-nameparam"], 2)
        self.assertEqual(M._macro_table(text)["ZONE_OF"]["unsafe"], {0: "member"})

    def test_a_type_name_parameter_is_refused_slot_by_slot(self):
        """`M2C_FIELD(expr, type_ptr, offset)` is in include/ and 187 rows call it: slot 1 is a
        TYPE, slots 0 and 2 are values.  The refusal is per SLOT, not per macro."""
        self.assertEqual(M._header_table()["M2C_FIELD"]["unsafe"], {1: "cast-type"})
        bad = PLAIN.replace("    total += second;",
                            "    total += M2C_FIELD(arg0, second, 0x10);")
        out, skips = gen(bad)
        self.assertEqual([l for l, _ in out], [])
        self.assertEqual(skips["in-macro-arg-nameparam"], 2)
        good = PLAIN.replace("    total += second;",
                             "    total += M2C_FIELD(second, s32 *, 0x10);")
        cand = only(good, "rename:second->first")
        self.assertIn("    total += M2C_FIELD(first, s32 *, 0x10);\n", cand)

    def test_the_name_parameter_test_does_not_fire_on_a_value_macro(self):
        """The one-sided test may cost a candidate; it may not cost every mask macro in the tree.
        `((x) * 2)` and `((x) & 0xFF)` are arithmetic, not casts."""
        for name, params, body in (("U16_AT", ["p", "n"], "(*(u16 *)((u8 *)(p) + (n)))"),
                                   ("SCALE", ["a", "x"], "((a) + (x) * 2)"),
                                   ("LO", ["x"], "((x) & 0xFF)"),
                                   ("ASM_KEEP", ["var"],
                                    '__asm__ __volatile__("" : "=r"(var) : "0"(var))')):
            t = M._table_from([(name, params, body)])
            self.assertEqual(t[name]["unsafe"], {}, name)
        for n in ("ASM_KEEP", "ASM_KEEP_NV", "ASM_USE", "ASM_SET", "ASM_KEEP_DEP_NV"):
            self.assertEqual(M._header_table()[n]["unsafe"], {}, n)

    def test_a_parameter_passed_into_another_macros_name_slot_is_refused(self):
        """The closure is per PARAMETER: `WRAP(a, b)` handing `b` to `ZONE_OF` is a name too."""
        text = ('#define ZONE_OF(F) (D_80024020[zone_id].F)\n'
                '#define WRAP(a, b) ((a) + ZONE_OF(b))\n'
                + PLAIN.replace("    total += second;", "    total += WRAP(1, second);"))
        self.assertEqual(M._macro_table(text)["WRAP"]["unsafe"], {1: "via-ZONE_OF"})
        out, skips = gen(text)
        self.assertEqual([l for l, _ in out], [])
        self.assertEqual(skips["in-macro-arg-nameparam"], 2)
        # slot 0 of the same macro is still a value
        ok = ('#define ZONE_OF(F) (D_80024020[zone_id].F)\n'
              '#define WRAP(a, b) ((a) + ZONE_OF(b))\n'
              + PLAIN.replace("    total += second;", "    total += WRAP(second, y);"))
        self.assertIn("    total += WRAP(first, y);\n", only(ok, "rename:second->first"))

    def test_a_macro_this_module_cannot_see_the_body_of_is_refused(self):
        """Round 28 refused every macro argument wholesale, so refusing the ones whose body is out
        of reach is never worse than the baseline - and its parameter may be a member or a type."""
        text = PLAIN.replace("    total += second;", "    total += BODY_NAME(arg0, second);")
        out, skips = gen(text)
        self.assertEqual([l for l, _ in out], [])
        self.assertEqual(skips["in-macro-arg-unknown-macro"], 2)

    def test_a_call_with_more_arguments_than_the_definition_has_is_refused(self):
        text = U16_DEF + PLAIN.replace("    total += second;",
                                       "    total += U16_AT(arg0, 4, second);")
        out, skips = gen(text)
        self.assertEqual([l for l, _ in out], [])
        self.assertEqual(skips["in-macro-arg-argcount"], 2)

    # ---------------- a macro argument on a CONTINUATION line (round-29 review)

    def test_a_stringifiers_argument_on_a_continuation_line_is_refused(self):
        """The macro scan was per LINE until this review, so a line break hid the argument from
        every macro test: the token a `#` stringifies was renamed with nothing journalled."""
        one = ('#define NAME_OF(a, x) func_80000000(a, #x)\n'
               + PLAIN.replace("    total += second;", "    total += NAME_OF(arg0, second);"))
        cont = one.replace("NAME_OF(arg0, second);", "NAME_OF(arg0,\n        second);")
        for text in (one, cont):
            out, skips = gen(text)
            self.assertEqual([l for l, _ in out], [])
            self.assertEqual(skips["in-macro-arg-stringify"], 2)

    def test_a_cast_read_on_a_continuation_line_is_parenthesised(self):
        text = U16_DEF + CASTED.replace("    arg0[scaled] = 0;",
                                        "    arg0[0] = U16_AT(arg0,\n        scaled);")
        cand = only(text, "cast:scaled->page")
        self.assertIn("        ((s32)page));\n", cand)

    def test_a_value_argument_on_a_continuation_line_is_still_renamed(self):
        text = U16_DEF + PLAIN.replace("    total += second;",
                                       "    total += U16_AT(arg0,\n        second);")
        cand = only(text, "rename:second->first")
        self.assertIn("        first);\n", cand)

    def test_a_short_all_caps_macro_is_a_macro_call_too(self):
        """`U8(x)`/`S8(x)` are row-local macros two characters long: `MACROARG_RE`'s 3-character
        shape would not see them at all - no slot, no refusal, a silent rename."""
        text = ('#define U8(x) (*(u8 *)(x))\n#define AT(p, f) ((p).f)\n'
                + PLAIN.replace("    total += second;", "    total += AT(arg0, second);"))
        out, skips = gen(text)
        self.assertEqual([l for l, _ in out], [])
        self.assertEqual(skips["in-macro-arg-nameparam"], 2)
        line = "    total = U8(v) + XY(v);"
        self.assertEqual(M._macros_at(line, line.index("v)")), ["U8"])
        self.assertEqual(M._macros_at(line, line.rindex("v)")), ["XY"])

    def test_the_macro_index_spans_lines(self):
        ml = ["    x = U16_AT(arg0,", "        v) + FOO(w);"]
        idx = M._MacroIdx(ml, M._header_table())
        self.assertEqual(idx.at(1, ml[1].index("v")), [("U16_AT", 1)])
        self.assertEqual(idx.at(1, ml[1].index("w")), [("FOO", 0)])
        self.assertEqual(idx.at(0, ml[0].index("arg0")), [("U16_AT", 0)])

    def test_the_reopened_pairs_are_counted(self):
        with off("T66_MACRO_ARGS"):
            before = gen(KEPT)[1]
        after = gen(KEPT)[1]
        self.assertEqual(before["in-macro-arg"], 2)
        self.assertEqual(after["in-macro-arg"], 0)
        self.assertEqual(after["in-macro-arg-reopened"], 2)


class DeclRun(unittest.TestCase):
    """T66_DECL_RUN: the declaration walk steps over three shapes instead of breaking on them."""

    def test_a_one_line_label_table_no_longer_hides_the_run(self):
        self.assertEqual(labels(LABEL_TABLE),
                         ["t66:plain:cast:scaled->page@$7", "t66:plain:cast:page->scaled@$7"])
        cand = only(LABEL_TABLE, "cast:scaled->page")
        self.assertIn("    page = (u8 *)(total * 4);\n", cand)
        # the table itself is untouched, and its name is still a name
        self.assertIn("    static void *const state_labels[] = { &&one, &&two };\n", cand)

    def test_the_attribute_spelling_of_the_table(self):
        """`_decl_names` takes the LAST identifier of a declarator, so the attribute has to be cut
        out first or the table registers `used` and loses its own name."""
        text = LABEL_TABLE.replace("state_labels[] = {",
                                   "state_labels[] __attribute__((used)) = {")
        self.assertEqual(len(labels(text)), 2)
        t = M.N._T(text)
        names = {d["name"] for ds in M._functions(t)[0].decls.values() for d in ds}
        self.assertIn("state_labels", names)
        self.assertNotIn("used", names)

    def test_a_stepped_over_declaration_reports_the_initialiser_it_carries(self):
        """`_init_place_refusal` walks the initialisers a demoted assignment crosses; a stepped-over
        declaration that carried one and reported None would be a crossing it never tested.  A
        `static` initialiser does not run at block entry, so that one stays None."""
        t = M.N._T(ANON_STRUCT.replace("    } camera_angles;", "    } camera_angles = {1, 2};"))
        by = {d["name"]: d for ds in M._functions(t)[0].decls.values() for d in ds}
        self.assertIn("1, 2", (by["camera_angles"]["init"] or ""))
        t2 = M.N._T(LABEL_TABLE)
        by2 = {d["name"]: d for ds in M._functions(t2)[0].decls.values() for d in ds}
        self.assertIsNone(by2["state_labels"]["init"])

    def test_the_reopened_pairs_are_counted(self):
        for text in (LABEL_TABLE, ANON_STRUCT):
            with off("T66_DECL_RUN"):
                before = gen(text)[1]
            after = gen(text)[1]
            self.assertEqual(before["decl-unparsed"], 0)      # natural parses these shapes itself since 2026-09-21
            self.assertEqual(after["decl-unparsed"], 0)
            self.assertEqual(after["decl-unparsed-reopened"], 0)

    def test_an_anonymous_struct_a_multidim_array_and_a_qualified_pointer(self):
        self.assertEqual(labels(ANON_STRUCT),
                         ["t66:plain:rename:second->first@$3", "t66:plain:rename:first->second@$3"])
        cand = only(ANON_STRUCT, "rename:second->first")
        self.assertIn("    } camera_angles;\n", cand)
        self.assertIn("    s16 vertices[2][3][4];\n", cand)
        self.assertIn("    void *volatile perspective_out;\n", cand)

    def test_the_stepped_over_names_are_registered_for_scope_resolution(self):
        """`_augment` may not parse these as mergeable declarations, but their NAMES have to be
        visible: a host whose name is one of them would otherwise be merged over."""
        for text in (LABEL_TABLE, ANON_STRUCT):
            t = M.N._T(text)
            F = M._functions(t)[0]
            names = {d["name"] for ds in F.decls.values() for d in ds}
            self.assertFalse(any(d["single"] and d["ty"] for ds in F.decls.values() for d in ds
                                 if d["name"] in ("state_labels", "camera_angles", "vertices",
                                                  "perspective_out")))
            self.assertTrue(names & {"state_labels", "camera_angles"})

    def test_the_walk_still_stops_at_the_first_statement(self):
        """The looser run may never read a statement as a declaration: a declaration BELOW the
        first statement is not C89 and must stay invisible."""
        text = ANON_STRUCT.replace("    camera_angles.a = 1;",
                                   "    camera_angles.a = 1;\n    register s32 third ASM_REG(\"$3\");")
        t = M.N._T(text)
        F = M._functions(t)[0]
        self.assertNotIn("third", {d["name"] for ds in F.decls.values() for d in ds})

    def test_an_aggregate_that_never_closes_breaks_the_run(self):
        text = ANON_STRUCT.replace("    } camera_angles;", "    } camera_angles")
        with self.assertRaises(AssertionError):
            only(text, "rename")

    def test_with_the_opening_off_every_declaration_below_is_hidden(self):
        for text in (LABEL_TABLE, ANON_STRUCT):
            with off("T66_DECL_RUN"):
                out, skips = gen(text)
            # 2026-09-21: natural's declaration parser now reads label tables and inline aggregates itself, so the
            # flag no longer hides anything for these shapes (the premise of the original assertion is gone)
            self.assertEqual(len(out), 2)
            self.assertEqual(skips["decl-unparsed"], 0)


class AsmOperand(unittest.TestCase):
    """T66_ASM_OPERAND: inside an `ASM_*` argument the operand is the register, so the name is bare."""

    def operands(self, text, macro):
        """[argument count] of every call of `macro` in `text`."""
        out = []
        for call in M._calls_in(M.N._T(text).mtext, (macro,)):
            if call[0] == macro:
                out.append(len(call[3]))
        return out

    def test_the_keeps_operand_is_the_bare_host_and_every_other_read_is_cast(self):
        pins = len(sites_of(ASMCAST))
        cand = only(ASMCAST, "cast:scaled->page")
        self.assertIn("    ASM_KEEP(page);\n", cand)
        self.assertIn("    arg0[(s32)page] = 0;\n", cand)
        self.assertNotIn("scaled", cand)
        self.assertEqual(len(sites_of(cand)), pins - 1)
        self.assertEqual(M._pin_key(cand)[("ASM_KEEP", "page", "")], 1)
        self.assertEqual(self.operands(cand, "ASM_KEEP"), self.operands(ASMCAST, "ASM_KEEP"))

    def test_a_later_slot_of_a_two_operand_pin(self):
        text = ASMCAST.replace("    ASM_KEEP(scaled);", "    ASM_KEEP_DEP_NV(total, scaled);")
        cand = only(text, "cast:scaled->page")
        self.assertIn("    ASM_KEEP_DEP_NV(total, page);\n", cand)
        self.assertEqual(self.operands(cand, "ASM_KEEP_DEP_NV"), [2])

    def test_a_non_asm_macro_on_the_same_row_still_gets_the_cast(self):
        text = U16_DEF + ASMCAST.replace("    arg0[scaled] = 0;",
                                         "    arg0[0] = U16_AT(arg0, scaled);")
        cand = only(text, "cast:scaled->page")
        self.assertIn("    ASM_KEEP(page);\n", cand)
        self.assertIn("U16_AT(arg0, ((s32)page));", cand)

    def test_an_asm_reg_binding_is_never_rewritten(self):
        """A local called `s0` beside a pin on `$s0`: the binding is a string, and `ASM_REG` is in
        `NEVER_IN_MACRO`, so a mention there refuses the pair rather than being renamed."""
        for label, cand in gen(ASMCAST)[0]:
            self.assertEqual(cand.count('ASM_REG("$7")'), 1, label)

    def test_the_reopened_pairs_are_counted(self):
        with off("T66_ASM_OPERAND"):
            before = gen(ASMCAST)[1]
        after = gen(ASMCAST)[1]
        self.assertEqual(before["asm-operand-cast"], 1)
        self.assertEqual(after["asm-operand-cast"], 0)
        self.assertEqual(after["asm-operand-cast-reopened"], 1)


class InitPlace(unittest.TestCase):
    """T66_INIT_PLACE: the demoted assignment may cross a declaration that carries an initialiser."""

    def test_the_assignment_lands_after_the_last_declaration_of_the_run(self):
        cand = only(INITRUN, "rename:second->first")
        self.assertIn('    register s32 first ASM_REG("$3");', cand)
        self.assertIn("    first = 7;\n", cand)
        self.assertIn("    s32 later = 3;\n", cand)
        self.assertLess(cand.index("s32 later = 3;"), cand.index("first = 7;"))
        self.assertEqual(cand.count("ASM_REG"), 1)

    def test_a_crossed_initialiser_that_reads_the_pair_is_refused(self):
        out, skips = gen(INITRUN.replace("    s32 later = 3;", "    s32 later = second;"))
        self.assertEqual([l for l, _ in out], ["t66:plain:rename:first->second@$3"])
        self.assertEqual(skips["init-place-crossed-init-reads-the-pair"], 2)

    def test_a_crossed_initialiser_that_calls_is_refused(self):
        out, skips = gen(INITRUN.replace("    s32 later = 3;",
                                         "    s32 later = func_80000000();"))
        self.assertEqual([l for l, _ in out], ["t66:plain:rename:first->second@$3"])
        self.assertEqual(skips["init-place-crossed-init-calls"], 2)

    def test_a_moved_initialiser_that_names_a_crossed_declaration_is_refused(self):
        out, skips = gen(INITRUN.replace('ASM_REG("$3") = 7', 'ASM_REG("$3") = later'))
        self.assertEqual(skips["init-place-moved-init-reads-a-crossed-declaration"], 2)

    def test_a_moved_initialiser_with_side_effects_is_refused(self):
        out, skips = gen(INITRUN.replace('ASM_REG("$3") = 7',
                                         'ASM_REG("$3") = func_80000000()'))
        self.assertEqual(skips["init-place-moved-init-has-side-effects"], 2)

    def test_the_reopened_pairs_are_counted(self):
        with off("T66_INIT_PLACE"):
            before = gen(INITRUN)[1]
        after = gen(INITRUN)[1]
        self.assertEqual(before["init-before-declarations"], 1)
        self.assertEqual(after["init-before-declarations"], 0)
        self.assertEqual(after["init-before-declarations-reopened"], 2)


class Shadow(unittest.TestCase):
    """T66_SHADOW: the capturing inner local is renamed first, then the merge as usual."""

    def test_the_inner_local_is_renamed_and_the_merge_proceeds(self):
        self.assertEqual(labels(SHADOWED), ["t66:plain:rename:second->first@$3+shadow",
                                            "t66:plain:rename:first->second@$3+shadow"])
        cand = only(SHADOWED, "rename:second->first")
        self.assertIn("        s32 second_s;\n", cand)
        self.assertIn("        second_s = arg0[4];\n", cand)
        self.assertIn("        arg0[5] = second_s;\n", cand)
        self.assertIn("    first = arg0[1] + 2;\n", cand)
        self.assertEqual(cand.count("ASM_REG"), 1)
        self.assertEqual(len(sites_of(cand)), len(sites_of(SHADOWED)) - 1)

    def test_a_pinned_inner_local_is_refused(self):
        text = SHADOWED.replace("        s32 second;",
                                '        register s32 second ASM_REG("$9");   /* pin */')
        out, skips = gen(text)
        self.assertEqual(out, [])
        self.assertEqual(skips["shadow-inner-refused"], 1)

    def test_an_inner_local_in_a_name_slot_is_refused(self):
        text = ('#define ZONE_OF(F) (D_80024020[zone_id].F)\n'
                + SHADOWED.replace("        arg0[5] = second;",
                                   "        arg0[5] = ZONE_OF(second);"))
        out, skips = gen(text)
        self.assertEqual(out, [])
        self.assertEqual(skips["shadow-inner-refused"], 1)

    def test_a_fresh_name_that_is_taken_is_not_reused(self):
        text = SHADOWED.replace("    s32 total;", "    s32 total;\n    s32 second_s;")
        cand = only(text, "rename:second->first")
        self.assertIn("        s32 second_s2;\n", cand)
        self.assertIn("    s32 second_s;\n", cand)

    def test_the_reopened_pairs_are_counted(self):
        with off("T66_SHADOW"):
            before = gen(SHADOWED)[1]
        after = gen(SHADOWED)[1]
        self.assertEqual(before["shadowed-inner-local"], 2)
        self.assertEqual(after["shadowed-inner-local"], 2)       # the first pass still refuses
        self.assertEqual(after["shadowed-inner-local-reopened"], 2)


class TryInterference(unittest.TestCase):
    """T66_TRY_INTERFERENCE: a C-level lifetime clash offered anyway, for `vf` to judge."""

    def on(self):
        return mock.patch.dict(os.environ, {"T66_TRY_INTERFERENCE": "1"})

    def test_on_by_default_since_round_31(self):
        out, skips = gen(OVERLAP)
        self.assertEqual(len(out), 2)
        self.assertEqual(skips["interference-reopened"], 2)

    def test_off_when_switched_off(self):
        with mock.patch.dict(os.environ, {"T66_TRY_INTERFERENCE": "0"}):
            out, skips = gen(OVERLAP)
        self.assertEqual(out, [])
        self.assertEqual(skips["interference"], 2)

    def test_on_the_pair_is_offered_and_the_clash_shape_is_journalled(self):
        with self.on():
            out, skips = gen(OVERLAP)
        self.assertEqual([l for l, _ in out],
                         ["t66:plain:rename:second->first@$3+interf-nested",
                          "t66:plain:rename:first->second@$3+interf-nested"])
        self.assertEqual(skips["interference"], 0)
        self.assertEqual(skips["interference-reopened"], 2)
        self.assertEqual(skips["interference-nested"], 2)
        self.assertEqual(len(sites_of(out[0][1])), len(sites_of(OVERLAP)) - 1)

    def test_a_loop_back_edge_is_still_its_own_refusal(self):
        text = HEAD + '''void func_test(s32 *arg0) {
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
'''
        with self.on():
            out, skips = gen(text)
        self.assertEqual(out, [])
        self.assertEqual(skips["loop-backedge"], 2)

    def test_a_clashing_pair_vf_refuses_is_a_miss(self):
        """`vf`'s byte verdict is the only acceptance: a refused candidate leaves the text alone
        and the row is a miss, exactly as for every other form."""
        seen = []

        def vf(cand):
            seen.append(cand)
            return {"exact": False}

        with self.on(), mock.patch.object(M, "compile_s", lambda row, text: ["x"]), \
                mock.patch.object(M, "sdiff", lambda a, b: 0):
            new, log = M.T.apply_verified(OVERLAP, {"cfg": "2.7.2"}, {}, vf)
        self.assertIsNone(new)
        self.assertEqual(log["steps"], [])
        self.assertEqual(log["candidates_n"], 2)
        self.assertEqual(log["tried"], 1)
        self.assertEqual(len(seen), 1)
        self.assertEqual(log["skips"]["interference-nested"], 2)

    def test_a_clashing_pair_vf_accepts_is_taken(self):
        with self.on(), mock.patch.object(M, "compile_s", lambda row, text: ["x"]), \
                mock.patch.object(M, "sdiff", lambda a, b: 0):
            new, log = M.T.apply_verified(OVERLAP, {"cfg": "2.7.2"}, {},
                                          lambda cand: {"exact": True})
        self.assertIsNotNone(new)
        self.assertEqual(len(sites_of(new)), len(sites_of(OVERLAP)) - 1)
        self.assertIn("+interf-nested", log["steps"][0])

    def test_clean_pairs_are_screened_before_clashing_ones(self):
        with self.on():
            ps = M.pairs_of(OVERLAP.replace("    arg0[2] = first + second;",
                                            "    arg0[2] = first + second;\n    arg0[3] = 0;"),
                            collections.Counter())
        self.assertEqual([bool(p.interf) for p in ps], sorted(bool(p.interf) for p in ps))


class Compound(unittest.TestCase):
    """T66_COMPOUND: the writes and the deref reads the round-29 lookahead called compound."""

    def test_a_write_whose_right_hand_side_reads_the_victim(self):
        cand = only(SELFREAD, "cast:slot->scaled")
        self.assertIn("    scaled = (s32)((u8 *)(void *)scaled + 4);\n", cand)
        self.assertIn("    total = ((S_0 *)(void *)scaled)->unk_00;\n", cand)
        self.assertNotIn("slot", cand)

    def test_an_assignment_through_the_victim_is_a_read_of_it(self):
        cand = only(DEREF_WRITE, "cast:link->scaled")
        self.assertIn("    *(u32 *)scaled = (*(u32 *)scaled & 0xF) | 0x10;\n", cand)
        self.assertNotIn("link", cand)

    def test_a_write_in_a_braceless_if_body(self):
        """A plain assignment that may not execute is not a kill, so `_is_kill` refuses it - but it
        is still a write, and it has the ordinary spelling."""
        text = HEAD + '''void func_test(u8 *arg0) {
    s32 total;
    register s32 early ASM_REG("$7");   /* pin */
    register void *slot ASM_REG("$7");   /* pin */

    early = arg0[0];
    total = early;
    slot = arg0;
    if (total != 0)
        slot = arg0 + 12;
    total += ((S_0 *)slot)->unk_04;
    arg0[2] = total;
}
'''
        cand = only(text, "cast:slot->early")
        self.assertIn("        early = (s32)(arg0 + 12);\n", cand)
        self.assertIn("    early = (s32)(arg0);\n", cand)
        self.assertNotIn("slot", cand)
        with off("T66_COMPOUND"):
            self.assertEqual(gen(text)[1]["compound-assign-cast"], 1)

    def test_a_multi_line_assignment_keeps_its_own_refusal(self):
        text = SELFREAD.replace("    slot = (u8 *)slot + 4;",
                                "    slot = (u8 *)(arg0 +\n                  4);")
        out, skips = gen(text)
        self.assertEqual([l for l, _ in out], ["t66:plain:cast:scaled->slot@$7"])
        self.assertEqual(skips["write-multiline-cast"], 1)

    def test_a_write_whose_tail_mentions_the_victim(self):
        text = SELFREAD.replace("    slot = (u8 *)slot + 4;",
                                "    slot = arg0 + 4; ASM_KEEP(slot);")
        out, skips = gen(text)
        self.assertEqual(skips["write-tail-mentions-victim"], 1)
        self.assertNotIn("t66:plain:cast:slot->scaled@$7+macroarg", [l for l, _ in out])

    def test_a_real_compound_assignment_still_has_its_own_spelling(self):
        text = SELFREAD.replace("    scaled = total * 4;",
                                "    scaled = total;\n    scaled >>= 5;")
        cand = only(text, "cast:scaled->slot")
        self.assertIn("    slot = (void *)(((s32)slot) >> (5));\n", cand)

    def test_a_star_left_of_the_name_is_a_deref_only_when_it_is_unary(self):
        """`frame * div5_magic` is arithmetic, not a deref: reading only `endswith("*")` added a
        parenthesis to every multiplication (measured on `dungeon/func_807B0B3C`)."""
        for s, pos, want in (("*v = 1;", 1, True), ("a * v = 1;", 4, False),
                             ("x = *v;", 5, True), ("x = a*v;", 6, False),
                             ("**v = 1;", 2, True), ("x = f()*v;", 8, False),
                             ("x = arr[0]*v;", 11, False), ("x = v;", 4, False)):
            self.assertEqual(M._is_deref(s, pos), want, (s, pos))

    def test_a_multiplication_is_not_parenthesised(self):
        text = SELFREAD.replace("    total += ((S_0 *)slot)->unk_04;",
                                "    total += total * (s32)slot;")
        cand = only(text, "cast:slot->scaled")
        self.assertIn("    total += total * (s32)(void *)scaled;\n", cand)

    def test_with_the_opening_off_both_shapes_are_refused(self):
        for text in (SELFREAD, DEREF_WRITE):
            with off("T66_COMPOUND"):
                before = gen(text)
            self.assertEqual(len(before[0]), 1, [l for l, _ in before[0]])
            self.assertEqual(before[1]["compound-assign-cast"], 1)
            after = gen(text)[1]
            self.assertEqual(after["compound-assign-cast"], 0)
            self.assertEqual(after["compound-assign-cast-reopened"],
                             before[1]["compound-assign-cast"])


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


MEMBER_NAME = HEAD + '''void func_test(s32 *arg0) {
    s32 total;
    register s32 first ASM_REG("$3");   /* UNRESOLVED C shape (pin) */
    register s32 second ASM_REG("$3");   /* UNRESOLVED C shape (pin) */
    struct {
        s32 first_member;
        s32 second;
    } box;

    first = arg0[0] + 1;
    total = first;
    second = arg0[1] + 2;
    total += second;
    box.first_member = total;
    arg0[2] = total;
}
'''

CROSSED_SIDE_EFFECT = HEAD + '''void func_test(s32 *arg0, s32 idx) {
    s32 total;
    register s32 first ASM_REG("$3");   /* UNRESOLVED C shape (pin) */
    register s32 second ASM_REG("$3") = arg0[idx];   /* UNRESOLVED C shape (pin) */
    s32 tail = arg0[idx++];

    total = second;
    first = arg0[0] + 1;
    total += first;
    arg0[2] = total + tail;
}
'''


class ReviewFixes(unittest.TestCase):
    """Round 30 review: three defects the adversarial reviewer demonstrated, and their refusals.

    All three fire whatever the openings are set to - the mechanisms predate round 30, and the
    openings only put a population in front of them."""

    # ---- defect 1: a mention that is another DECLARATION of the same name

    def test_a_member_of_the_same_name_is_never_renamed(self):
        """`s32 second;` inside `struct { ... } box;` is a `_occ` mention of the pin variable, and
        `F.resolve` cannot return a member it never registered - the rename rewrote a struct
        MEMBER, byte-neutrally, with nothing journalled."""
        out, skips = gen(MEMBER_NAME)
        self.assertEqual(out, [])
        self.assertEqual(skips["mention-in-declaration"], 2)
        for _, cand in gen(MEMBER_NAME)[0]:
            self.assertIn("        s32 second;\n", cand)

    def test_the_refusal_does_not_depend_on_an_opening(self):
        with off("T66_DECL_RUN", "T66_ASM_OPERAND", "T66_INIT_PLACE", "T66_SHADOW",
                 "T66_COMPOUND", "T66_MACRO_ARGS", "T66_RENAME_HOST"):
            out, skips = gen(MEMBER_NAME)
        self.assertEqual(out, [])
        self.assertEqual(skips["mention-in-declaration"], 2)

    def test_an_aggregate_whose_members_are_named_otherwise_still_merges(self):
        """The refusal is about the NAME, not about the shape: the round-30 opening's yield on the
        aggregate rows is untouched."""
        text = MEMBER_NAME.replace("        s32 second;\n", "        s32 second_member;\n")
        self.assertEqual(labels(text),
                         ["t66:plain:rename:second->first@$3", "t66:plain:rename:first->second@$3"])
        cand = only(text, "rename:second->first")
        self.assertIn("        s32 second_member;\n", cand)

    def test_an_aggregate_whose_declarator_the_walk_cannot_read_still_protects_its_members(self):
        """`_agg_spans` closes the aggregate by brace depth ALONE: `_agg_close` also demands that
        the closing line end in `;` before the walk may step over the declaration, and a declarator
        this module cannot read is a reason to refuse the rename, never a reason to expose the
        members to it."""
        text = MEMBER_NAME.replace("    } box;", "    } box\n      = {1, 2};")
        out, skips = gen(text)
        self.assertEqual(out, [])
        self.assertEqual(skips["mention-in-declaration"], 2)
        t = M.N._T(text)
        F = M._functions(t)[0]
        self.assertTrue(any(lo <= k <= hi for lo, hi in F.declspans
                            for k in [next(i for i, s in enumerate(F.ml)
                                           if s.strip() == "s32 second;")]))

    def test_an_inner_declaration_at_its_own_line_is_a_shadow_not_a_mention(self):
        """`resolve` needs `d["line"] < k`, so an inner local that is declared and never used
        resolved to the pin and had its DECLARATION renamed.  It is journalled as the shadow it
        is, and T66_SHADOW's retry reopens it."""
        text = PLAIN.replace("    arg0[2] = total;", "    {\n        s32 second;\n    }\n"
                                                    "    arg0[2] = total;")
        with off("T66_SHADOW"):
            out, skips = gen(text)
        self.assertEqual(out, [])
        self.assertEqual(skips["shadowed-inner-local"], 2)
        for _, cand in gen(text)[0]:
            self.assertNotIn("        s32 first;\n", cand)

    def test_the_shadow_retry_reaches_a_declaration_only_capture(self):
        text = PLAIN.replace("    arg0[2] = total;", "    {\n        s32 second;\n"
                                                    "        second = arg0[6];\n"
                                                    "        arg0[7] = second;\n    }\n"
                                                    "    arg0[2] = total;")
        cand = only(text, "rename:second->first")
        self.assertIn("        s32 second_s;\n", cand)
        self.assertEqual(gen(text)[1]["shadowed-inner-local-reopened"], 2)

    # ---- defect 2: a crossed initialiser with a side effect of its own

    def test_a_crossed_initialiser_with_a_side_effect_is_refused(self):
        """The demoted assignment now runs AFTER the crossed initialiser, so `arg0[idx]` would be
        read as `arg0[idx + 1]`."""
        out, skips = gen(CROSSED_SIDE_EFFECT)
        self.assertEqual([l for l in [x for x, _ in out] if "second->first" in l], [])
        self.assertEqual(skips["init-place-crossed-init-has-side-effects"], 2)

    def test_a_clean_crossing_still_moves(self):
        text = CROSSED_SIDE_EFFECT.replace("arg0[idx++]", "arg0[idx]")
        cand = only(text, "rename:second->first")
        self.assertIn("    first = arg0[idx];\n", cand)
        self.assertLess(cand.index("s32 tail ="), cand.index("first = arg0[idx];"))
        self.assertEqual(gen(text)[1]["init-before-declarations-reopened"], 2)

    def test_a_crossed_initialiser_the_parse_dropped_is_still_read(self):
        """`VDECL_RE` only spells a declarator that fits on ONE line, so a declarator spread over
        two reported `init=None` and the whole refusal was blind to the crossing."""
        text = CROSSED_SIDE_EFFECT.replace("    s32 tail = arg0[idx++];",
                                           "    s32 tail =\n        arg0[idx++];")
        t = M.N._T(text)
        by = {d["name"]: d for ds in M._functions(t)[0].decls.values() for d in ds}
        self.assertIsNone(by["tail"]["init"])
        self.assertIsNotNone(M._crossed_init(M._functions(t)[0], by["tail"]))
        out, skips = gen(text)
        self.assertEqual([l for l, _ in out if "second->first" in l], [])
        self.assertEqual(skips["init-place-crossed-init-has-side-effects"], 2)

    def test_a_static_initialiser_the_parse_dropped_is_not_a_crossing(self):
        """It does not run at block entry, so nothing the demoted assignment reads can move."""
        text = CROSSED_SIDE_EFFECT.replace("    s32 tail = arg0[idx++];",
                                           "    static s32 tail =\n        3;")
        t = M.N._T(text)
        by = {d["name"]: d for ds in M._functions(t)[0].decls.values() for d in ds}
        self.assertIsNone(by["tail"]["init"])
        self.assertIsNone(M._crossed_init(M._functions(t)[0], by["tail"]))

    # ---- defect 3: the victim inside a LARGER expression in an ASM_* argument

    def test_a_sub_expression_of_an_asm_argument_refuses_the_cast_form(self):
        """`ASM_KEEP_DEP_NV(total, scaled + 1)`: the operand is the whole argument, so the bare
        name would read `s32 + 1` as `u8 * + 1`."""
        text = ASMCAST.replace("    ASM_KEEP(scaled);", "    ASM_KEEP_DEP_NV(total, scaled + 1);")
        out, skips = gen(text)
        self.assertEqual([l for l, _ in out if "cast:scaled->page" in l], [])
        self.assertEqual(skips["asm-operand-cast-subexpr"], 1)
        self.assertEqual(skips["asm-operand-cast-reopened"], 0)
        for _, cand in out:
            self.assertNotIn("ASM_KEEP_DEP_NV(total, page + 1);", cand)

    def test_the_whole_argument_is_still_spelled_bare(self):
        pins = len(sites_of(ASMCAST))
        cand = only(ASMCAST, "cast:scaled->page")
        self.assertIn("    ASM_KEEP(page);\n", cand)
        self.assertEqual(len(sites_of(cand)), pins - 1)
        self.assertEqual(gen(ASMCAST)[1]["asm-operand-cast-subexpr"], 0)

    def test_an_argument_on_a_continuation_line_is_still_the_whole_argument(self):
        text = ASMCAST.replace("    ASM_KEEP(scaled);",
                               "    ASM_KEEP_DEP_NV(total,\n        scaled);")
        cand = only(text, "cast:scaled->page")
        self.assertIn("        page);\n", cand)
        self.assertEqual(gen(text)[1]["asm-operand-cast-subexpr"], 0)

    def test_the_rename_form_of_the_same_pair_is_untouched(self):
        """Only the cast spelling needs the operand argument; a same-type pair just respells the
        name the keep already carries."""
        text = PLAIN.replace("    total += second;",
                             "    ASM_KEEP_DEP_NV(total, second + 1);\n    total += second;")
        cand = only(text, "rename:second->first")
        self.assertIn("    ASM_KEEP_DEP_NV(total, first + 1);\n", cand)
        self.assertEqual(gen(text)[1]["asm-operand-cast-subexpr"], 0)


if __name__ == "__main__":
    unittest.main()
