"""T64: the contract, the menu, and the guards that stand between a menu and `vf`.

The last test is the only one that compiles: it takes a two-web local, splits it with `varset`, and
asserts the split changes the cc1 listing (the whole point of the move is that the allocator sees two
values), while a rename of the same local does not.  It is skipped when the stock compiler is absent.
"""
import collections
import os
import re
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from pin_census import sites_of, unscored_text
from xform import t64_varset as M
from xform import varset as V
from xform.screen import compile_s, sdiff

ROW = {"id": "dungeon/test", "container": "dungeon", "cfg": "2.7.2", "kind": "overlay",
       "c_path": "overlays/dungeon/first_pass_matched/func_test.c"}

HEAD = '#include "common.h"\n\n'

PINNED = HEAD + (
    "void func_test(s32 arg, u8 *ptr)\n"
    "{\n"
    "    s32 b;\n"
    "    s32 c;\n"
    '    register u32 page ASM_REG("$2");\n'
    "    page = 0x800C0000;\n"
    "    ASM_KEEP(page);\n"
    "    b = page - 0x629C;\n"
    "    page = 0x80100000;\n"
    "    c = page - 0x75E4;\n"
    "    func_800A0000(b, c);\n"
    "}\n")


class Contract(unittest.TestCase):
    def test_class_shape(self):
        self.assertEqual(M.T.name, "t64_varset")
        self.assertEqual(M.T.level, 1)
        self.assertTrue(M.T.needs_verify)

    def test_eligible(self):
        self.assertIsNone(M.T.eligible(PINNED, ROW, {}))
        self.assertEqual(M.T.eligible(HEAD + "void f(void) {}\n", ROW, {}), "no live pins")
        bare = PINNED.replace('register u32 page ASM_REG("$2")', "u32 page") \
                     .replace("    ASM_KEEP(page);\n", "    ASM_SCHED_BARRIER();\n")
        self.assertEqual(M.T.eligible(bare, ROW, {}), "no register or keep pins")
        self.assertEqual(M.T.eligible(PINNED, {"id": "x"}, {}), "missing compiler recipe")

    def test_site_var(self):
        got = {s[1]: M.site_var(s) for s in sites_of(PINNED)}
        self.assertEqual(got, {"ASM_REG": "page", "ASM_KEEP": "page"})


class Guards(unittest.TestCase):
    def test_scaffolding_is_refused_whatever_menu_produced_it(self):
        sig = unscored_text(PINNED)
        n = len(sites_of(PINNED))
        for bad in ("    ASM_SCHED_BARRIER();\n", "    do { b = 1; } while (0);\n",
                    "    __asm__ volatile(\"\");\n", "    while (0) { b = 1; }\n"):
            cand = PINNED.replace("    ASM_KEEP(page);\n", bad)
            self.assertFalse(M.allowed(PINNED, cand, sig, n), bad)

    def test_a_qualifier_may_not_move_in_either_direction(self):
        sig = unscored_text(PINNED)
        n = len(sites_of(PINNED))
        dropped = PINNED.replace("    ASM_KEEP(page);\n", "").replace("s32 b;", "s32 b;")
        self.assertTrue(M.allowed(PINNED, dropped, sig, n))
        added = dropped.replace("    s32 b;", "    volatile s32 b;")
        self.assertFalse(M.allowed(PINNED, added, sig, n))
        withvol = PINNED.replace("    s32 b;", "    volatile s32 b;")
        lost = withvol.replace("    ASM_KEEP(page);\n", "").replace("volatile s32 b;", "s32 b;")
        self.assertFalse(M.allowed(withvol, lost, unscored_text(withvol), n))

    def test_a_candidate_must_lower_the_pin_count(self):
        sig = unscored_text(PINNED)
        n = len(sites_of(PINNED))
        self.assertFalse(M.allowed(PINNED, PINNED, sig, n))

    def test_unscored_arm_edits_are_refused(self):
        t = (HEAD + "void func_test(s32 arg)\n{\n    s32 b;\n    ASM_KEEP(arg);\n"
             "#ifdef NON_MATCHING\n    b = 1;\n#endif\n    b = arg;\n}\n")
        cand = t.replace("    ASM_KEEP(arg);\n", "").replace("    b = 1;", "    b = 2;")
        self.assertFalse(M.allowed(t, cand, unscored_text(t), len(sites_of(t))))


class Menu(unittest.TestCase):
    def test_varset_candidates_are_bounded_and_labelled(self):
        got = M.varset_candidates(PINNED)
        self.assertLessEqual(len(got), M.MENU_CAP)
        for label, cand in got:
            self.assertTrue(label.startswith("varset:"), label)
            self.assertNotEqual(cand, PINNED)

    def test_menu_carries_varset_and_the_established_families(self):
        from pin_sites import erase_many
        pins = sites_of(PINNED)
        base = erase_many(PINNED, [pins[0]], clean_notes=True)
        fams = {fam for fam, _, _ in M.menu(base, 6, "page", collections.Counter())}
        self.assertTrue(any(f.startswith("varset:") for f in fams), fams)
        self.assertTrue(any(f.startswith("t51:") for f in fams), fams)

    def test_menu_finds_the_split_once_the_register_pin_is_erased(self):
        from pin_sites import erase_many
        pins = sites_of(PINNED)
        reg = next(s for s in pins if s[1] == "ASM_REG")
        base = erase_many(PINNED, [reg], clean_notes=True)
        labels = [l for _, l, _ in M.menu(base, 6, "page", collections.Counter())]
        self.assertTrue(any(l.startswith("varset:split_def:page>") for l in labels), labels[:20])

    def test_map_line_follows_an_erasure(self):
        from pin_sites import erase_many
        pins = sites_of(PINNED)
        keep = next(s for s in pins if s[1] == "ASM_KEEP")
        base = erase_many(PINNED, [keep], clean_notes=True)
        moved = M.map_line(PINNED, base, keep[5] + 1)
        self.assertEqual(base.splitlines()[moved - 1].strip(), "b = page - 0x629C;")


class Compiled(unittest.TestCase):
    CC = ROOT / "toolchain/compilers/gcc-2.7.2"

    @unittest.skipUnless((ROOT / "toolchain/compilers/gcc-2.7.2/cc1").exists(),
                         "stock 2.7.2 is not present")
    def test_every_candidate_builds_and_a_rename_alone_is_a_no_op(self):
        """The screen rejects a broken candidate, but only after paying for it: a move that emits
        unbuildable C would burn the row's whole budget, so every move is checked against cc1 here.
        The rename control proves the edits themselves carry no code change."""
        from pin_sites import erase_many
        reg = next(s for s in sites_of(PINNED) if s[1] == "ASM_REG")
        base = erase_many(PINNED, [reg], clean_notes=True)
        ref = compile_s(ROW, base)
        self.assertIsNotNone(ref, "the erased baseline must build")
        renamed = re.sub(r"(?<![\w.])page\b", "pg", base)
        self.assertEqual(sdiff(ref, compile_s(ROW, renamed)), 0, "a rename is not a code change")
        got = V.candidates(base, "page")
        self.assertTrue(got)
        for label, cand in got:
            self.assertIsNotNone(compile_s(ROW, cand), label)


if __name__ == "__main__":
    unittest.main()
