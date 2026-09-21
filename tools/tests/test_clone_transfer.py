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


if __name__ == "__main__":
    unittest.main()
