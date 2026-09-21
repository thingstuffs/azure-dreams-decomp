"""Textual tests for t86_symaddr: what it reads, what it offers and what it must never edit.

No compiler and no scorer here (that is the sweep's job): every assertion is about the text of a
candidate, in the t74/t77 style.
"""
import re, sys, unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/xform"))
from pin_census import sites_of, unscored_text
import t86_symaddr as M

PAGE = """\
#include "common.h"

extern u8 D_800E3DF0[];

void func_80001234(u8 *object)
{
    u8 *buffer_addr;
    s32 *record_table;

    buffer_addr = (u8 *)0x800E0000;
    ASM_KEEP(buffer_addr);
    record_table = (s32 *)(buffer_addr + 0x3DF0);
    record_table[0] = 0;
}
"""

ARMED = """\
#include "common.h"

void func_80005678(void *object, s16 entry_index)
{
    u8 *state_page;
    u16 *state;

#ifdef NON_MATCHING
    state_page = D_80083460 - 0x3460;
#else
    state_page = (u8 *)0x80080000;
#endif
    ASM_KEEP(state_page);
    state = (u16 *)(state_page + 0x3460);
    state[14] = entry_index;
}
"""

SCALED = """\
#include "common.h"

void func_80009ABC(void)
{
    s32 *slot;
    u8 *buffer_addr;

    buffer_addr = (u8 *)0x800E0000;
    ASM_KEEP(buffer_addr);
    slot = (s32 *)buffer_addr + 0x13;
    slot[0] = 0;
}
"""

PARAM = """\
#include "common.h"

void func_8000DEF0(u8 *page, s32 n)
{
    page = (u8 *)0x800A0000;
    ASM_KEEP(page);
    page += 0x77AC;
    *(s32 *)page = n;
}
"""


def labels(text):
    return [lab for lab, _t, _n, _l in M.menu(text)]


def text_of(text, want):
    for lab, t, _n, _l in M.menu(text):
        if lab == want:
            return t
    return None


class TestBases(unittest.TestCase):
    def test_literal_base_and_use(self):
        bs = M.bases(PAGE)
        self.assertEqual([b["var"] for b in bs], ["buffer_addr"])
        self.assertEqual(bs[0]["value"], 0x800E0000)
        us = M.uses(PAGE, bs[0])
        self.assertEqual([(u["kind"], u["lhs"], u["addr"]) for u in us],
                         [("deriv", "record_table", 0x800E3DF0)])

    def test_cast_outside_parens_scales(self):
        """`(s32 *)base + 0x13` steps four bytes; `(s32 *)(base + 0x13)` steps one."""
        b = M.bases(SCALED)[0]
        u = M.uses(SCALED, b)[0]
        self.assertEqual(u["addr"], 0x800E0000 + 4 * 0x13)

    def test_parameter_is_a_base(self):
        b = M.bases(PARAM)[0]
        self.assertEqual(b["var"], "page")
        u = M.uses(PARAM, b)[0]
        self.assertEqual((u["kind"], u["addr"]), ("bump", 0x800A77AC))

    def test_unpinned_base_is_not_offered(self):
        self.assertEqual(M.bases(PAGE.replace("    ASM_KEEP(buffer_addr);\n", "")), [])


class TestMenu(unittest.TestCase):
    def test_position_axis(self):
        labs = labels(PAGE)
        self.assertIn("buffer_addr:inplace@12", labs)
        self.assertIn("buffer_addr:move@def", labs)
        self.assertIn("buffer_addr:defsym", labs)

    def test_symbol_named_at_the_definitions_place(self):
        t = text_of(ARMED, "state_page:move@def")
        self.assertIsNotNone(t)
        self.assertIn("state = (u16 *)D_80083460;", t)
        self.assertNotIn("0x80080000", t)                       # the definition took the symbol's slot
        self.assertNotIn("state_page + 0x3460", t)

    def test_local_kept_in_place(self):
        t = text_of(PAGE, "buffer_addr:inplace@12")
        self.assertIn("buffer_addr = (u8 *)0x800E0000;", t)     # the local stays
        self.assertIn("record_table = (s32 *)D_800E3DF0;", t)   # the value is written at the use

    def test_definition_respelt_keeps_the_local(self):
        t = text_of(PAGE, "buffer_addr:defsym")
        self.assertIn("extern u8 D_800E0000[];", t)
        self.assertIn("buffer_addr = D_800E0000;", t)
        self.assertIn("record_table = (s32 *)(buffer_addr + 0x3DF0);", t)

    def test_declared_extern_is_not_redeclared(self):
        t = text_of(PAGE, "buffer_addr:inplace@12")
        self.assertEqual(t.count("extern u8 D_800E3DF0[];"), 1)

    def test_bump_becomes_the_symbol(self):
        t = text_of(PARAM, "page:inplace@7")
        self.assertIn("page = D_800A77AC;", t)

    def test_no_candidate_edits_an_unscored_arm(self):
        for t in (PAGE, ARMED, SCALED, PARAM):
            for lab, new, _n, _l in M.menu(t):
                self.assertEqual(unscored_text(new), unscored_text(t), lab)

    def test_no_candidate_adds_a_pin_or_a_macro(self):
        for t in (PAGE, ARMED, SCALED, PARAM):
            for lab, new, _n, _l in M.menu(t):
                self.assertLessEqual(len(sites_of(new)), len(sites_of(t)), lab)
                self.assertNotIn("__asm__", new)
                self.assertEqual(new.count("NON_MATCHING"), t.count("NON_MATCHING"), lab)


class TestPlansAndCells(unittest.TestCase):
    def test_plans_are_window_then_singles_then_all(self):
        t = text_of(PAGE, "buffer_addr:inplace@12")
        tags = [tag for tag, _g in M.pin_plans(t, ["buffer_addr", "record_table"], [11])]
        self.assertTrue(tags and tags[0].startswith("one"))     # one window pin: no joint plan
        for _tag, group in M.pin_plans(t, ["buffer_addr"], [11]):
            self.assertTrue(group)

    def test_split_cells(self):
        for cfg in ("2.7.2-cdk", "2.7.2-cdk-G0", "2.8.1-G0", "2.95.2-G0", "2.91.66-G0"):
            self.assertTrue(M.splits(cfg), cfg)
        for cfg in ("2.7.2", "2.7.2-G0", "2.6.3-G0", "2.8.1-G0 -mno-split-addresses"):
            self.assertFalse(M.splits(cfg), cfg)

    def test_cdk_recipe_keeps_the_rows_flags(self):
        self.assertEqual(M.cdk_cfg("2.7.2-G0"), "2.7.2-cdk-G0")
        self.assertEqual(M.cdk_cfg("2.6.3"), "2.7.2-cdk")
        self.assertEqual(M.cdk_cfg("2.7.2-G0 -fno-schedule-insns"), "2.7.2-cdk-G0 -fno-schedule-insns")

    def test_at_cfg_moves_cell_and_flags_together(self):
        r = M.at_cfg({"cfg": "2.7.2-G0", "cell": "2.7.2", "flags": "-G0"}, "2.7.2-cdk-G0 -fno-strength-reduce")
        self.assertEqual((r["cell"], r["flags"]), ("2.7.2-cdk", "-G0 -fno-strength-reduce"))

    def test_la_prescreen_is_relative(self):
        self.assertEqual(M.la_count(["la $2,D_1", "lui $3,1", "la $4,D_2"]), 2)


class TestEligible(unittest.TestCase):
    def test_eligible_rows(self):
        for t in (PAGE, ARMED, SCALED, PARAM):
            self.assertIsNone(M.T.eligible(t, {"cfg": "2.7.2-G0"}, {}))

    def test_refusals(self):
        self.assertEqual(M.T.eligible("void f(void) {}\n", {"cfg": "2.7.2"}, {}), "no pins")
        no_base = PAGE.replace("buffer_addr = (u8 *)0x800E0000;", "buffer_addr = object;")
        self.assertIsNotNone(M.T.eligible(no_base, {"cfg": "2.7.2"}, {}))


if __name__ == "__main__":
    unittest.main()
