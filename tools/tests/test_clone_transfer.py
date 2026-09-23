"""Clone transfer: normalisation, the clone finder, the identifier map and the hunk replay are
textual and tested here; the listing screen and the byte scorer are not exercised."""
import os
import sys
import unittest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "lanes"))
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform"))
import clone_transfer as C  # noqa: E402

BASE = '''#include "common.h"

typedef struct S_8017086C_6 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_8017086C_6;   /* child in func_8017086C */

extern u8 D_80170B64[];
extern void func_80047784();

void func_8017086C(s16 arg0)
{
    s32 count;
    void *child;
    register s32 call_code ASM_REG("$5");   /* UNRESOLVED C shape (pin) */
    u32 elem_offset;

    child = D_80170B64;
    elem_offset = 8;
    while (count < ((S_8017086C_6 *)child)->unk_02) {
        ASM_KEEP(child);   /* UNRESOLVED C shape (pin) */
        call_code = 39;
        elem_offset += 48;
        count++;
        func_80047784(child, call_code, elem_offset);
    }
}
'''

# the exemplar's byte-exact rewrite: the pins and their carrier variables are gone and the
# update moved after the call
OUT = BASE.replace('    register s32 call_code ASM_REG("$5");   /* UNRESOLVED C shape (pin) */\n', "")
OUT = OUT.replace('        ASM_KEEP(child);   /* UNRESOLVED C shape (pin) */\n        call_code = 39;\n'
                  '        elem_offset += 48;\n        count++;\n'
                  '        func_80047784(child, call_code, elem_offset);\n',
                  '        count++;\n        func_80047784(child, 39, elem_offset);\n'
                  '        elem_offset += 48;\n')

# a clone: other addresses, other struct tag, other local spellings, one constant apart
SIB = (BASE.replace("8017086C", "8016A86C").replace("D_80170B64", "D_8016AB64")
       .replace("child", "node").replace("count", "n").replace("elem_offset", "step"))


class Normalise(unittest.TestCase):
    def test_sig_abstracts_names_numbers_strings(self):
        a = C.line_sig("    part_b->unk_2C = D_8017418C;")
        b = C.line_sig("    other->unk_2C = D_8016E18C;")
        self.assertEqual(a, b)
        self.assertEqual(a, ("I", "->", "I", "=", "I", ";"))
        # keywords, types and the pin macros keep their spelling
        self.assertEqual(C.line_sig("    register u32 color ASM_REG(\"$8\");"),
                         ("register", "u32", "I", "ASM_REG", "(", "S", ")", ";"))
        self.assertNotEqual(C.line_sig("s32 v;"), C.line_sig("u32 v;"))

    def test_comments_are_masked_in_place(self):
        m = C.mask_comments("a = b;   /* note */ c = d;")
        self.assertEqual(len(m), len("a = b;   /* note */ c = d;"))
        self.assertEqual([t[1] for t in C.tokens_of(m)], ["a", "=", "b", ";", "c", "=", "d", ";"])


class Finder(unittest.TestCase):
    def test_clone_scores_high_stranger_low(self):
        b, s = C.Doc("base", BASE), C.Doc("sib", SIB)
        self.assertGreater(C.similarity(b, s), 0.95)
        self.assertGreater(C.jaccard(b.shingles, s.shingles), 0.5)
        other = C.Doc("other", '#include "common.h"\nvoid f(void) { s32 i; for (i = 0; i < 4; i++) g(i); }\n')
        self.assertLess(C.similarity(b, other), 0.6)


class Map(unittest.TestCase):
    def setUp(self):
        self.b, self.s = C.Doc("base", BASE), C.Doc("sib", SIB)
        self.align = C.alignment(self.b, self.s)
        self.map, self.amb = C.identifier_map(self.b, self.s, self.align)

    def test_map_carries_names_and_addresses(self):
        self.assertEqual(self.map["D_80170B64"], "D_8016AB64")
        self.assertEqual(self.map["S_8017086C_6"], "S_8016A86C_6")
        self.assertEqual(self.map["child"], "node")
        self.assertEqual(self.map["elem_offset"], "step")
        self.assertEqual(self.map["func_80047784"], "func_80047784")   # a shared callee maps to itself
        self.assertEqual(self.amb, set())

    def test_port_line_substitutes_code_and_comments(self):
        self.assertEqual(C.port_line("    child = D_80170B64;", self.map, self.amb),
                         "    node = D_8016AB64;")
        self.assertIn("func_8016A86C", C.port_line("} S_8017086C_6;   /* child in func_8017086C */",
                                                   self.map, self.amb))

    def test_unmapped_address_refuses(self):
        with self.assertRaises(C.Refused):
            C.port_line("    x = D_DEADBEEF;", self.map, self.amb)
        with self.assertRaises(C.Refused):
            C.port_line("    x = child;", self.map, {"child"})
        # a plain name the map does not know is kept as it stands
        self.assertEqual(C.port_line("    x = 3;", self.map, self.amb), "    x = 3;")


class Replay(unittest.TestCase):
    def test_hunks_skip_whitespace_only(self):
        lines = BASE.splitlines()
        self.assertEqual(C.hunks_of(lines, lines[:2] + [""] + lines[2:]), [])
        self.assertTrue(C.hunks_of(lines, OUT.splitlines()))

    def test_transfer_drops_the_siblings_pins(self):
        b, o, s = C.Doc("b", BASE), C.Doc("o", OUT), C.Doc("s", SIB)
        cands, hunks, mapping, amb = C.candidates_for(b, o, s)
        self.assertTrue(cands and cands[0][0])
        text = cands[0][0]
        self.assertNotIn("ASM_", text)                      # both pins gone
        self.assertIn("func_80047784(node, 39, step);", text)
        self.assertIn("D_8016AB64", text)                   # the sibling's own address
        self.assertNotIn("D_80170B64", text)
        self.assertNotIn("call_code", text)
        self.assertEqual(text.splitlines()[-1], "}")
        # the two edits sit within one context window, so they are one hunk here
        self.assertEqual(len(hunks), 1)
        self.assertEqual([c[1] for c in cands if c[0]], [{"hunks": [0], "ctx": 3}])

    def test_hunk_already_applied_is_named(self):
        b, o = C.Doc("b", BASE), C.Doc("o", OUT)
        # the sibling already carries the same rewrite: not a refusal to chase
        done = C.Doc("s", OUT.replace("8017086C", "8016A86C"))
        hunks = C.hunks_of(b.lines, o.lines)
        _, _, refusals = C.transfer(b, o, done, hunks, C.alignment(b, done),
                                    *C.identifier_map(b, done, C.alignment(b, done)),
                                    align_out=C.alignment(o, done))
        self.assertEqual([r[1] for r in refusals], ["already applied in the sibling"])

    def test_hunk_refused_when_context_does_not_align(self):
        b, o = C.Doc("b", BASE), C.Doc("o", OUT)
        # a sibling whose loop body is a different shape: the loop hunk has nowhere to land
        odd = SIB.replace("        count++;\n", "        n += 2;\n").replace(
            "    while (n < ((S_8016A86C_6 *)node)->unk_02) {", "    do {")
        s = C.Doc("s", odd)
        hunks = C.hunks_of(b.lines, o.lines)
        align = C.alignment(b, s)
        mapping, amb = C.identifier_map(b, s, align)
        text, applied, refusals = C.transfer(b, o, s, hunks, align, mapping, amb)
        self.assertTrue(refusals, "a hunk whose context is gone must be refused")
        self.assertIn("align", refusals[0][1])


class ReplayV2(unittest.TestCase):
    """Round 76: the code-line anchored aligner (v2) replays hunks v1 refused."""

    def test_v2_reproduces_v1_on_a_plain_clone(self):
        b, o, s = C.Doc("b", BASE), C.Doc("o", OUT), C.Doc("s", SIB)
        cands, hunks, mapping, amb = C.candidates_v2(b, o, s)
        texts = [c[0] for c in cands if c[0]]
        self.assertTrue(texts)
        self.assertIn("func_80047784(node, 39, step);", texts[0])
        self.assertNotIn("ASM_", texts[0])
        self.assertIn("D_8016AB64", texts[0])

    def test_sibling_only_comment_and_blank_lines_do_not_break_context(self):
        # the sibling carries a landed comment and a blank line inside the hunk's context window:
        # v1 finds the context not contiguous, v2 does not see comment-only lines at all
        odd = SIB.replace("        n++;\n", "        /* counts the parts */\n\n        n++;\n")
        b, o, s = C.Doc("b", BASE), C.Doc("o", OUT), C.Doc("s", odd)
        v1, _, _, _ = C.candidates_for(b, o, s)
        self.assertFalse([c for c in v1 if c[0] and "ASM_KEEP" not in c[0]])
        v2, _, _, _ = C.candidates_v2(b, o, s)
        good = [c[0] for c in v2 if c[0] and "ASM_" not in c[0]]
        self.assertTrue(good)
        self.assertIn("func_80047784(node, 39, step);", good[0])

    def test_sibling_only_code_line_elsewhere_and_distant_pins_split(self):
        # two pins far apart: bare-run hunks let each one go alone
        base = BASE.replace("    child = D_80170B64;\n",
                            "    child = D_80170B64;\n    ASM_USE(child);\n")
        out = OUT.replace("    child = D_80170B64;\n", "    child = D_80170B64;\n")
        b, o = C.Doc("b", base), C.Doc("o", out)
        hunks = C.hunks_v2(b, o)
        self.assertGreaterEqual(len([h for h in hunks if h["ctx"] == 0]), 2)
        # a sibling that already lost the first pin some other way: only the loop hunk remains
        sib = SIB.replace("    node = D_8016AB64;\n", "    node = D_8016AB64;\n    s32 extra_decl_line;\n")
        cands, _, _, _ = C.candidates_v2(b, o, C.Doc("s", sib))
        self.assertTrue([c for c in cands if c[0] and "ASM_KEEP" not in c[0]])

    def test_globally_ambiguous_number_does_not_refuse(self):
        # 39 is 39 in the loop but the sibling's other '39' became 40: v1 marks 39 ambiguous
        base = BASE.replace("    elem_offset = 8;", "    elem_offset = 39;")
        out = OUT.replace("    elem_offset = 8;", "    elem_offset = 39;")
        sib = SIB.replace("    step = 8;", "    step = 40;")
        b, o, s = C.Doc("b", base), C.Doc("o", out), C.Doc("s", sib)
        mapping, amb = C.identifier_map_v2(b, s, C.code_index(b), C.code_index(s),
                                           C.code_alignment(b, s, C.code_index(b), C.code_index(s)))
        self.assertNotIn("39", amb)
        cands, _, _, _ = C.candidates_v2(b, o, s)
        good = [c[0] for c in cands if c[0] and "ASM_" not in c[0]]
        self.assertTrue(good)
        self.assertIn("func_80047784(node, 39, step);", good[0])   # the loop's own 39, read locally

    def test_already_applied_is_named_v2(self):
        b, o = C.Doc("b", BASE), C.Doc("o", OUT)
        done = C.Doc("s", OUT.replace("8017086C", "8016A86C"))
        cands, _, _, _ = C.candidates_v2(b, o, done)
        self.assertFalse([c for c in cands if c[0]])
        self.assertIn("already applied in the sibling", [r[1] for c in cands for r in c[2]])

    def test_unmapped_address_still_refuses(self):
        # the exemplar's out names an address the sibling never mentions: refused, never guessed
        out = OUT.replace("func_80047784(child, 39, elem_offset);", "func_80047784(child, D_80179999, elem_offset);")
        b, o, s = C.Doc("b", BASE), C.Doc("o", out), C.Doc("s", SIB)
        cands, _, _, _ = C.candidates_v2(b, o, s)
        for text, _, _ in cands:
            if text:
                self.assertNotIn("D_80179999", text)

    def test_family_transplant_ports_a_donor_members_text(self):
        # the donor is a less-pinned family member (the exemplar's OUT, in yet another overlay);
        # its text, rewritten to the sibling's names, replays as an ordinary exemplar
        donor = C.Doc("d", OUT.replace("8017086C", "80EE5000").replace("D_80170B64", "D_80EE5B64")
                      .replace("child", "elem"))
        s = C.Doc("s", SIB)
        b, o = C.transplant_exemplar(donor, s)
        self.assertEqual(b.text, s.text)
        self.assertIn("D_8016AB64", o.text)
        self.assertNotIn("D_80EE5B64", o.text)
        cands, _, _, _ = C.candidates_v2(b, o, s)
        good = [c[0] for c in cands if c[0] and "ASM_" not in c[0]]
        self.assertTrue(good)
        self.assertIn("func_80047784(node, 39, step);", good[0])

    def test_scaffold_grew_mirrors_the_landing_rule(self):
        cur = "    x = 1;\n    ASM_KEEP(x);   /* while (0) in a comment */\n"
        self.assertEqual(C.scaffold_grew(cur, cur), [])
        self.assertEqual(C.scaffold_grew(cur + "    do { } while (0);\n", cur), ["while(0)"])
        self.assertEqual(C.scaffold_grew("    x = 1;\n", cur), [])
        self.assertEqual(C.scaffold_grew(cur.replace("ASM_KEEP(x)", "ASM_KEEP_NV(x)"), cur), ["ASM_KEEP_NV"])

    def test_both_dedupes(self):
        b, o, s = C.Doc("b", BASE), C.Doc("o", OUT), C.Doc("s", SIB)
        cands, nh, _, _ = C.candidates_with(b, o, s, "both")
        texts = [c[0] for c in cands if c[0]]
        self.assertEqual(len(texts), len(set(texts)))
        self.assertEqual(cands[0][1]["aligner"], "v2")


if __name__ == "__main__":
    unittest.main()
