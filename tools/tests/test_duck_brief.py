"""Textual parts of tools/lanes/duck_brief.py: the note regex, both REPORT.md shapes, the
distance-sentence filter, the fall-together rule and the newest-record pick.  No compiles."""
import sys
import unittest
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/xform"))
sys.path.insert(0, str(ROOT / "tools/lanes"))
import duck_brief as D                                                   # noqa: E402


NOTE = ("UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; "
        "the source shape that makes it unnecessary has not been found")

TEXT = "\n".join([
    "void f(void) {",
    "    register s32 v ASM_REG(\"$19\") = x;   /* %s */" % NOTE,
    "    ASM_KEEP(node);   /* %s */" % NOTE,
    "    ASM_SCHED_BARRIER();",
    "#define M(a) \\",
    "    ASM_KEEP(a); \\",
    "    g(a)",
    "}",
])


class TestNote(unittest.TestCase):
    def test_trailing_note(self):
        self.assertEqual(D.note_of(TEXT, 2), NOTE)
        self.assertEqual(D.note_of(TEXT, 3), NOTE)

    def test_no_note(self):
        self.assertIsNone(D.note_of(TEXT, 4))

    def test_note_inside_define_keeps_backslash_out(self):
        t = "    ASM_KEEP(a);   /* held */ \\"
        self.assertEqual(D.note_of(t, 1), "held")

    def test_out_of_range(self):
        self.assertIsNone(D.note_of(TEXT, 999))
        self.assertIsNone(D.note_of(TEXT, 0))

    def test_whitespace_is_collapsed(self):
        self.assertEqual(D.note_of("x; /*  a   b  */", 1), "a b")


class TestVarOf(unittest.TestCase):
    def test_reg_site_takes_the_declared_name(self):
        site = ("reg", "ASM_REG", "19", 0, 1, 2, "s32 *entity_data")
        self.assertEqual(D.var_of(site), "entity_data")

    def test_stmt_site_takes_the_argument(self):
        site = ("stmt", "ASM_KEEP", "node", 0, 1, 3, "")
        self.assertEqual(D.var_of(site), "node")


class TestPairPlan(unittest.TestCase):
    def _sites(self, n, macro="ASM_KEEP"):
        return [("stmt", macro, "v%d" % i, 0, 1, i, "") for i in range(n)]

    def test_every_pair_while_within_the_bound(self):
        for n in (2, 3, 4, 5, 6):
            plan, possible = D.pair_plan(self._sites(n))
            self.assertEqual(possible, n * (n - 1) // 2)
            self.assertEqual(len(plan), possible, n)
            self.assertLessEqual(len(plan), D.MAX_PAIRS)

    def test_large_rows_are_capped_and_prefer_related_pins(self):
        sites = self._sites(7)
        sites[5] = ("reg", "ASM_REG", "19", 0, 1, 5, "s32 v0")      # same variable as site 0
        plan, possible = D.pair_plan(sites)
        self.assertEqual(possible, 21)
        self.assertEqual(len(plan), D.PAIR_CAP_LARGE)
        self.assertIn((0, 5), plan)


class TestFallTogether(unittest.TestCase):
    def test_pair_no_larger_than_either_falls_together(self):
        self.assertTrue(D.fall_together(6, 10, 8))
        self.assertTrue(D.fall_together(8, 8, 12))
        self.assertTrue(D.fall_together(0, 4, 4))

    def test_pair_larger_than_a_single_is_independent(self):
        self.assertFalse(D.fall_together(20, 10, 8))
        self.assertFalse(D.fall_together(9, 8, 12))

    def test_a_missing_measurement_is_not_a_claim(self):
        self.assertIsNone(D.fall_together(None, 3, 4))
        self.assertIsNone(D.fall_together(3, None, 4))


HEADED = """# r59_sol_large5 results

## Per-row evidence

### `dungeon/func_80D66164`

- **Result:** Improved but not exact; `u16_raw_height` reduced listing distance 28 -> 20 and independently scored 10 substitutions, 0 indels.
- **Change:** Type `raw_height` as `u16` instead of pinned `u32`.
- **Mechanism:** The source type represents the field's true width.

### `dungeon/func_80E0D2E8`

- **Result:** something else entirely.
"""

BULLETS = """# r59_sol_mid4 report

## Per-row results

- `dungeon/func_8008D084` - **MATCH**, verified total=0.
- `dungeon/func_80A9D4E8` - **NO EXACT**; best candidate, scorer `total=6` (`subs=4`), listing distance 10. Change: move `x/y` into a post-call nested scope. Mechanism: declaration order improves the colours. Measured directions: erased variants stayed at 16; delayed stores worsened to 20; reversed post-call declarations reached 10.
- `dungeon/func_80E0D894` - **MATCH**.

## General rules
"""


class TestReportSection(unittest.TestCase):
    def test_headed_section(self):
        sec = D.report_section(HEADED, "dungeon/func_80D66164")
        self.assertTrue(sec.startswith("### `dungeon/func_80D66164`"))
        self.assertIn("28 -> 20", sec)
        self.assertNotIn("func_80E0D2E8", sec)

    def test_bullet_section(self):
        sec = D.report_section(BULLETS, "dungeon/func_80A9D4E8")
        self.assertIn("listing distance 10", sec)
        self.assertNotIn("func_8008D084", sec)
        self.assertNotIn("func_80E0D894", sec)

    def test_bare_address_in_a_clone_family_heading(self):
        notes = ("## Item-target family (dungeon/func_80A9D4E8, 80DBBFC8, 810318E4) - BOUNDED\n"
                 "- volatile s8 loads: distance 8. `(s32)` cast: 8.\n"
                 "## Raw-height family\n- other\n")
        sec = D.report_section(notes, "dungeon/func_80DBBFC8")
        self.assertIn("distance 8", sec)
        self.assertNotIn("Raw-height", sec)

    def test_row_not_mentioned(self):
        self.assertEqual(D.report_section(BULLETS, "town/func_DEADBEEF"), "")


class TestDistanceSentences(unittest.TestCase):
    def test_quotes_measurements_not_prose(self):
        q = D.distance_sentences(D.report_section(BULLETS, "dungeon/func_80A9D4E8"), limit=6)
        self.assertTrue(any("listing distance 10" in s for s in q))
        self.assertTrue(any("reached 10" in s for s in q))
        self.assertFalse(any(s.startswith("Mechanism:") for s in q))

    def test_limit_is_honoured(self):
        q = D.distance_sentences(D.report_section(HEADED, "dungeon/func_80D66164"), limit=1)
        self.assertEqual(len(q), 1)
        self.assertIn("28 -> 20", q[0])


class TestNewest(unittest.TestCase):
    def test_newest_by_timestamp(self):
        recs = [{"at": "2026-09-10T00:00:00Z", "outcome": "refused"},
                {"at": "2026-09-20T00:00:00Z", "outcome": "applied"}]
        self.assertEqual(D.newest(recs)["outcome"], "applied")
        self.assertIsNone(D.newest([]))

    def test_missing_timestamps_do_not_crash(self):
        self.assertIsNotNone(D.newest([{"outcome": "miss"}, {"at": "2026-01-01", "outcome": "x"}]))


class TestHypothesis(unittest.TestCase):
    def test_callee_saved_register_names_the_allocation_order(self):
        site = ("reg", "ASM_REG", "19", 0, 1, 2, "s32 v")
        h, gens = D.hypothesis(site, {"cls": "RECOLOURED"})
        self.assertIn("callee-saved", h)
        self.assertIn("t85_allocorder", gens)

    def test_mem_barrier_is_the_cse_mechanism(self):
        site = ("stmt", "ASM_MEM_BARRIER", "", 0, 1, 2, "")
        h, gens = D.hypothesis(site, {"cls": "CHANGED"})
        self.assertIn("cse", h)
        self.assertEqual(gens, ["t83_storeafterproducer"])

    def test_invisible_residue_is_the_assembler_side_class(self):
        site = ("stmt", "ASM_KEEP", "x", 0, 1, 2, "")
        h, gens = D.hypothesis(site, {"cls": "INVISIBLE"})
        self.assertIn("cannot see this pin", h)
        self.assertEqual(gens, [])

    def test_nobuild_is_reported_as_unmeasured(self):
        site = ("stmt", "ASM_KEEP", "x", 0, 1, 2, "")
        h, gens = D.hypothesis(site, {"cls": "NOBUILD"})
        self.assertTrue(h.startswith("unknown"))
        self.assertIn("does not compile", h)

    def test_unknown_when_nothing_matches(self):
        site = ("stmt", "ASM_SOMETHING_NEW", "x", 0, 1, 2, "")
        h, gens = D.hypothesis(site, {"cls": "CHANGED"})
        self.assertTrue(h.startswith("unknown"))
        self.assertEqual(gens, [])

    def test_a_changed_residue_on_a_register_pin_is_not_called_pure_colour(self):
        site = ("reg", "ASM_REG", "3", 0, 1, 2, "u32 raw_height")
        h, _ = D.hypothesis(site, {"cls": "CHANGED"})
        self.assertIn("CHANGES the opcodes", h)


class TestNeededLines(unittest.TestCase):
    def _m(self, ds, pairs, joint):
        return {"singles": [{"fp": {"d": d}} for d in ds], "pairs": pairs,
                "pairs_shown": len(pairs), "pairs_possible": len(pairs)}

    def test_single_pin_says_nothing_falls_with_it(self):
        site = ("stmt", "ASM_KEEP", "n", 0, 1, 2, "")
        out = D.needed_lines([site], self._m([16], [], {"d": 16}),
                             [D.hypothesis(site, {"cls": "BOTH"})], {"d": 16})
        self.assertTrue(any("nothing has to fall with it" in x for x in out))

    def test_all_pins_fall_together_when_the_joint_residue_is_smallest(self):
        sites = [("stmt", "ASM_MEM_BARRIER", "", 0, 1, i, "") for i in range(2)]
        hyps = [D.hypothesis(s, {"cls": "CHANGED"}) for s in sites]
        out = D.needed_lines(sites, self._m([10, 12], [(0, 1, 4)], {"d": 4}), hyps, {"d": 4})
        self.assertTrue(any("must fall together" in x for x in out))

    def test_independent_pins_are_said_to_be_independent(self):
        sites = [("stmt", "ASM_KEEP", "a", 0, 1, 1, ""), ("stmt", "ASM_KEEP", "b", 0, 1, 2, "")]
        hyps = [D.hypothesis(s, {"cls": "MOVED"}) for s in sites]
        out = D.needed_lines(sites, self._m([4, 4], [(0, 1, 30)], {"d": 30}), hyps, {"d": 30})
        self.assertTrue(any("No measured pair falls together" in x for x in out))


if __name__ == "__main__":
    unittest.main()
