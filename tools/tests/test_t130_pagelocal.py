import sys, unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "xform"))
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

import t130_pagelocal as G
from pin_census import sites_of

HEAD = '#include "common.h"\nextern void use(void *, u8);\nextern u8 D_80170000[];\n'

RULE_A = HEAD + '''void f(s32 a, void *sp)
{
    u8 *tbl;
    if (a == 0) {
        tbl = (u8 *)0x80170000;
        ASM_KEEP(tbl);   /* UNRESOLVED C shape (pin): x */
        tbl += 0x4E44;
        use(sp, *(u8 *)(a + (u32)tbl));
        use(tbl, 1);
        return;
    }
    use(sp, 2);
}
'''

RULE_B = HEAD + '''void g(s32 a, void *sp)
{
    u8 *tbl;
    if (a == 0) {
        tbl = (u8 *)0x80170000;
        ASM_KEEP(tbl);   /* UNRESOLVED C shape (pin): x */
        tbl += 0x4E44;
        goto set_table;
    }
    tbl = D_80170000;
    if (a == 3) {
        return;
    }
set_table:
    use(sp, tbl[a]);
    use(tbl, 1);
}
'''


class Rules(unittest.TestCase):
    def test_run_found_with_address(self):
        r = G.runs(RULE_A)
        self.assertEqual(len(r), 1)
        self.assertEqual(r[0]["addr"], 0x80174E44)

    def test_rule_a_direct_symbol_and_erasure(self):
        r = G.runs(RULE_A)[0]
        new, why = G.build(RULE_A, r, "plain")
        self.assertIsNotNone(new, why)
        self.assertIn("D_80174E44", new)
        self.assertIn("extern u8 D_80174E44[];", new)
        self.assertNotIn("0x80170000", new)
        self.assertNotIn("ASM_KEEP", new)
        self.assertNotIn("u8 *tbl;", new)                     # the declaration went with the last use
        self.assertLess(len(sites_of(new)), len(sites_of(RULE_A)))

    def test_rule_a_fold_spelling(self):
        r = G.runs(RULE_A)[0]
        new, _ = G.build(RULE_A, r, "fold")
        self.assertIn("&D_80174E44[a]", new)

    def test_rule_b_tail_copied_in_place(self):
        r = G.runs(RULE_B)[0]
        new, why = G.build(RULE_B, r, "plain")
        self.assertIsNotNone(new, why)
        self.assertIn("use(sp, D_80174E44[a]);", new)
        self.assertIn("return;", new)
        self.assertNotIn("set_table:", new)                    # no goto left: the label goes, the tail stays
        self.assertEqual(new.count("use(tbl, 1);"), 1)         # original tail kept once
        self.assertNotIn("goto", new)
        self.assertNotIn("ASM_KEEP", new)

    def test_rule_b_label_removed_when_unreferenced(self):
        text = RULE_B.replace("    tbl = D_80170000;\n    if (a == 3) {\n        return;\n    }\nset_table:\n",
                              "    tbl = D_80170000;\nset_table:\n")
        r = G.runs(text)[0]
        # the goto is the only reference but the label is still reached by fall-through: it may go
        new, why = G.build(text, r, "plain")
        self.assertIsNotNone(new, why)
        self.assertNotIn("goto", new)

    def test_refuses_label_in_block(self):
        text = RULE_A.replace("        use(sp, *(u8 *)(a + (u32)tbl));\n", "here:\n        use(sp, *(u8 *)(a + (u32)tbl));\n")
        r = G.runs(text)
        new = G.build(text, r[0], "plain")[0] if r else None
        self.assertIsNone(new)

    def test_refuses_reassignment_in_block(self):
        text = RULE_A.replace("        use(tbl, 1);\n", "        tbl = D_80170000;\n        use(tbl, 1);\n")
        r = G.runs(text)[0]
        new, why = G.build(text, r, "plain")
        self.assertIsNone(new)
        self.assertIn("assigned again", why)

    def test_refuses_keep_with_other_args(self):
        text = RULE_A.replace("ASM_KEEP(tbl);", "ASM_KEEP2(tbl, a);")
        self.assertEqual(G.runs(text), [])

    def test_no_run_without_step(self):
        text = RULE_A.replace("        tbl += 0x4E44;\n", "")
        self.assertEqual(G.runs(text), [])

    def test_candidates_strictly_fewer_pins(self):
        c = G.candidates(RULE_A)
        self.assertTrue(c)
        for _label, t in c:
            self.assertLess(len(sites_of(t)), len(sites_of(RULE_A)))

    def test_unscored_arm_untouched(self):
        text = RULE_A.replace("        tbl = (u8 *)0x80170000;\n",
                              "#ifdef NON_MATCHING\n        tbl = D_80170000;\n#else\n        tbl = (u8 *)0x80170000;\n#endif\n")
        for _l, t in G.candidates(text):
            self.assertIn("tbl = D_80170000;", t)

    def test_macro_seed(self):
        text = RULE_A.replace('#include "common.h"\n', '#include "common.h"\n#define PG(sym, off) 0x80170000UL\n').replace(
            "tbl = (u8 *)0x80170000;", "tbl = (u8 *)PG(D_80174E44, 0x4E44);")
        r = G.runs(text)
        self.assertEqual(len(r), 1)
        self.assertEqual(r[0]["addr"], 0x80174E44)


class Companions(unittest.TestCase):
    def test_inline_temp(self):
        t = HEAD + '''void h(s32 a, u8 *p) {
    s32 idx;
    idx = (a + 0x100) >> 9;
    idx &= 7;
    p = (u8 *)&D_80174E44[idx];
    use(p, 0);
}
'''
        out = G.post_inline(t, "D_80174E44")
        self.assertIn("&D_80174E44[(((a + 0x100) >> 9) & 7)]", out)
        self.assertNotIn("idx &= 7", out)

    def test_inline_refused_when_temp_read_later(self):
        t = HEAD + '''void h(s32 a, u8 *p) {
    s32 idx;
    idx = a >> 9;
    p = (u8 *)&D_80174E44[idx];
    use(p, idx);
}
'''
        self.assertIsNone(G.post_inline(t, "D_80174E44"))

    def test_page_read_to_member(self):
        t = '#include "shared/game_work.h"\nextern u8 D_80080000[];\nextern u8 D_80174E44[];\n' \
            'void h(s32 a, u8 *p) {\n    p = (u8 *)D_80080000;\n    p = (u8 *)&D_80174E44[(*(s16 *)(p + 0x3228) + a)];\n}\n'
        out = G.post_page(t, "D_80174E44")
        self.assertIn("gameWork.view.viewAngle", out)
        self.assertNotIn("p = (u8 *)D_80080000;", out)

    def test_page_read_needs_header(self):
        t = 'extern u8 D_80080000[];\nextern u8 D_80174E44[];\n' \
            'void h(s32 a, u8 *p) {\n    p = (u8 *)D_80080000;\n    p = (u8 *)&D_80174E44[(*(s16 *)(p + 0x3228) + a)];\n}\n'
        self.assertIsNone(G.post_page(t, "D_80174E44"))


class Plugin(unittest.TestCase):
    def test_interface(self):
        self.assertEqual(G.T.name, "t130_pagelocal")
        self.assertTrue(G.T.needs_verify)
        self.assertIsNone(G.T.eligible(RULE_A, {}, None))
        self.assertIsNotNone(G.T.eligible("void f(void) { }\n", {}, None))
        self.assertIn("no staged", G.T.eligible(RULE_A.replace("tbl += 0x4E44;", ""), {}, None) or "")

    def test_apply_verified_first_exact_wins(self):
        calls = []

        def vf(c):
            calls.append(c)
            return {"exact": len(calls) == 2}
        new, info = G.T.apply_verified(RULE_A, {}, None, vf)
        self.assertIsNotNone(new)
        self.assertEqual(info["pins_in"], 1)
        self.assertEqual(info["pins_out"], 0)

    def test_apply_verified_refuses_when_nothing_exact(self):
        new, info = G.T.apply_verified(RULE_A, {}, None, lambda c: {"exact": False})
        self.assertIsNone(new)
        self.assertIn("refused", info)


if __name__ == "__main__":
    unittest.main(verbosity=1)
