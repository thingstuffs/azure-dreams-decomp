"""The catalogue pack builder's admission rule, on synthetic per-site records only: unexplained-near,
far, bucket a, the served guard, the closed-group guard and the stratum fold, --repack / --ignore-closed,
the census-stale drop, the ranking, the per-site cause suppression beyond the near band, the measured-
negative lookup, and that the brief carries the scaffolding list VERBATIM. No tree, no traces, no compiler."""
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "lanes"))
import build_catalog_lanes as B                                   # noqa: E402


def site(i, d0, level="L0", causes=(), macro="ASM_KEEP", cls="CHANGED", band="1-2"):
    return {"i": i, "macro": macro, "d0": d0, "n": 0, "cls": cls, "band": band,
            "level": level, "causes": list(causes)}


CAUSE = [{"cause": "addr_literal", "n": 9, "share": 0.5, "generator": "t29_addrsym / t54"}]
NOCLOSED = set()


class AdmissionRule(unittest.TestCase):
    def test_near_explained_is_bucket_a_and_refused(self):
        recs = [site(0, 2, "L1", CAUSE), site(1, 9)]
        b, refusal, _ = B.classify(recs, ["ASM_KEEP", "ASM_KEEP"], [], NOCLOSED, "KEEP", "-")
        self.assertIsNone(b)
        self.assertEqual(refusal, "bucket a")

    def test_near_covered_without_a_cause_is_not_explained(self):
        """level L1 but an empty causes list is NOT coverage: the rule asks for both."""
        recs = [site(0, 2, "L1", [])]
        b, refusal, _ = B.classify(recs, ["ASM_KEEP"], [], NOCLOSED, "OTHER", "-")
        self.assertEqual((b, refusal), ("near", None))

    def test_near_unexplained_is_admitted(self):
        recs = [site(0, 3, "L0", CAUSE), site(1, 2, "L0", CAUSE)]
        b, refusal, _ = B.classify(recs, ["ASM_KEEP", "ASM_KEEP"], [], NOCLOSED, "OTHER", "-")
        self.assertEqual((b, refusal), ("near", None))

    def test_a_covered_far_site_does_not_make_a_row_bucket_a(self):
        """Only the d0 <= 4 sites decide: an L2-covered site at d0 30 is noise by the round-33 control."""
        recs = [site(0, 3, "L0", CAUSE), site(1, 30, "L2", CAUSE)]
        b, refusal, _ = B.classify(recs, ["ASM_KEEP", "ASM_KEEP"], [], NOCLOSED, "OTHER", "-")
        self.assertEqual((b, refusal), ("near", None))

    def test_far_row(self):
        recs = [site(0, 5, "L2", CAUSE), site(1, 40)]
        b, refusal, _ = B.classify(recs, ["ASM_KEEP", "ASM_KEEP"], [], NOCLOSED, "OTHER", "-")
        self.assertEqual((b, refusal), ("far", None))

    def test_d0_exactly_four_is_near(self):
        b, _, _ = B.classify([site(0, 4)], ["ASM_KEEP"], [], NOCLOSED, "OTHER", "-")
        self.assertEqual(b, "near")
        b, _, _ = B.classify([site(0, 5)], ["ASM_KEEP"], [], NOCLOSED, "OTHER", "-")
        self.assertEqual(b, "far")

    def test_missing_d0_is_not_a_near_site(self):
        b, _, _ = B.classify([site(0, None)], ["ASM_KEEP"], [], NOCLOSED, "OTHER", "-")
        self.assertEqual(b, "far")


class Guards(unittest.TestCase):
    def test_served_row_refused_and_repack_lifts_it(self):
        recs = [site(0, 2)]
        b, refusal, detail = B.classify(recs, ["ASM_KEEP"], ["alloc7"], NOCLOSED, "OTHER", "-")
        self.assertEqual((b, refusal, detail), ("near", "served", "alloc7"))
        b, refusal, _ = B.classify(recs, ["ASM_KEEP"], ["alloc7"], NOCLOSED, "OTHER", "-", repack=True)
        self.assertEqual((b, refusal), ("near", None))

    def test_closed_group_refused_and_ignore_closed_lifts_it(self):
        recs = [site(0, 2)]
        closed = {("KEEP", "-"), ("REG", "alloc3")}
        b, refusal, detail = B.classify(recs, ["ASM_KEEP"], [], closed, "KEEP", "-")
        self.assertEqual((b, refusal, detail), ("near", "closed", "KEEP -"))
        b, refusal, _ = B.classify(recs, ["ASM_KEEP"], [], closed, "KEEP", "-", ignore_closed=True)
        self.assertEqual((b, refusal), ("near", None))

    def test_closed_uses_the_folded_stratum(self):
        """`trace-stale` and `no-stratum` are the same fact as `-`: no usable stratum."""
        closed = {("REG", "-")}
        reg = [site(0, 2, macro="ASM_REG")]
        for stratum in ("-", "no-stratum", "trace-stale", "anything-else"):
            b, refusal, _ = B.classify(reg, ["ASM_REG"], [], closed, "REG", stratum)
            self.assertEqual((b, refusal), ("near", "closed"), stratum)
        b, refusal, _ = B.classify(reg, ["ASM_REG"], [], closed, "REG", "alloc2")
        self.assertEqual((b, refusal), ("near", None))

    def test_closed_lookup_is_strict_to_the_printed_list(self):
        """(KEEP, alloc3) is not closed just because (REG, alloc3) is."""
        b, refusal, _ = B.classify([site(0, 2)], ["ASM_KEEP"], [], {("REG", "alloc3")}, "KEEP", "alloc3")
        self.assertEqual((b, refusal), ("near", None))

    def test_served_is_reported_before_closed(self):
        b, refusal, _ = B.classify([site(0, 2)], ["ASM_KEEP"], ["keep9"], {("KEEP", "-")}, "KEEP", "-")
        self.assertEqual(refusal, "served")

    def test_each_guard_is_priced_on_its_own_not_by_the_candidate_count(self):
        """Round 35 review: the CANDIDATE count is not the `--ignore-closed` pool - the served guard is
        still standing.  Lifting one guard admits only the rows THAT guard alone refuses."""
        def p(rid, pins, refusal, closed_group=False, in_band=True):
            return {"id": rid, "pins": pins, "refusal": refusal, "closed_group": closed_group,
                    "in_band": in_band, "bucket": "near"}
        sel = [p("a", 5, None), p("b", 4, "closed", closed_group=True),
               p("c", 3, "served"),                         # served only -> --repack admits it
               p("d", 9, "served", closed_group=True),      # served AND closed -> neither flag alone does
               p("e", 7, "closed", closed_group=True, in_band=False)]   # out of band -> stays refused
        ok = [sel[0]]
        self.assertEqual(B.would_admit(sel, ok, "closed"), (2, 9))      # a + b
        self.assertEqual(B.would_admit(sel, ok, "served"), (2, 8))      # a + c, never d
        self.assertEqual((len(sel), sum(x["pins"] for x in sel)), (5, 28))  # the candidate count differs

    def test_the_table_prints_the_counterfactual_for_every_guard_still_standing(self):
        sel = [{"id": "a", "pins": 5, "refusal": None, "closed_group": False, "in_band": True,
                "bucket": "near", "family": "KEEP", "folded": "-"},
               {"id": "b", "pins": 4, "refusal": "closed", "closed_group": True, "in_band": True,
                "bucket": "near", "family": "KEEP", "folded": "-"}]
        table, ok = B.dry_run_table(sel, "near", None)
        self.assertIn("lifting --ignore-closed  would admit   2 rows /    9 pins", table)
        self.assertIn("lifting --repack", table)
        self.assertEqual([r["id"] for r in ok], ["a"])
        # a guard already lifted is not priced again
        table, _ = B.dry_run_table(sel, "near", None, repack=True, ignore_closed=True)
        self.assertNotIn("lifting", table)

    def test_fold_stratum(self):
        self.assertEqual(B.fold_stratum("alloc1"), "alloc1")
        self.assertEqual(B.fold_stratum("alloc5"), "alloc5")
        self.assertEqual(B.fold_stratum("no-stratum"), "-")
        self.assertEqual(B.fold_stratum("trace-stale"), "-")
        self.assertEqual(B.fold_stratum("-"), "-")


class StaleCensus(unittest.TestCase):
    def test_a_row_that_lost_a_pin_is_dropped(self):
        recs = [site(0, 2), site(1, 2)]
        b, refusal, detail = B.classify(recs, ["ASM_KEEP"], [], NOCLOSED, "KEEP", "alloc1")
        self.assertIsNone(b)
        self.assertEqual(refusal, "census stale")
        self.assertIn("2 sites -> 1", detail)

    def test_a_row_whose_macro_moved_is_dropped(self):
        recs = [site(0, 2, macro="ASM_KEEP"), site(1, 2, macro="ASM_REG")]
        b, refusal, _ = B.classify(recs, ["ASM_REG", "ASM_KEEP"], [], NOCLOSED, "KEEP", "alloc1")
        self.assertEqual(refusal, "census stale")

    def test_a_row_with_no_pin_left(self):
        b, refusal, _ = B.classify([site(0, 2)], [], [], NOCLOSED, "KEEP", "alloc1")
        self.assertEqual((b, refusal), (None, "no pin left"))

    def test_aligned_row_passes(self):
        self.assertTrue(B.census_aligned([site(0, 1), site(1, 1, macro="ASM_REG")], ["ASM_KEEP", "ASM_REG"]))


class Ranking(unittest.TestCase):
    def test_pins_descending_then_id(self):
        pool = [{"id": "b/x", "pins": 3}, {"id": "a/y", "pins": 9}, {"id": "a/x", "pins": 3}]
        self.assertEqual([p["id"] for p in sorted(pool, key=B.rank_key)], ["a/y", "a/x", "b/x"])


class Negatives(unittest.TestCase):
    def test_cause_kinds_map_to_the_measured_negatives(self):
        self.assertEqual(B.negatives_for([{"cause": "param_copy"}], "MOVED"), ["t69"])
        self.assertEqual(B.negatives_for([{"cause": "addr_literal+hoist"}], "CHANGED"), ["address"])
        self.assertEqual(B.negatives_for([{"cause": "adjacent_swap"}], "MOVED"), ["t51"])

    def test_class_negatives(self):
        self.assertEqual(B.negatives_for([], "RECOLOURED"), ["recoloured"])
        self.assertEqual(B.negatives_for([], "BOTH"), ["recoloured"])
        self.assertEqual(B.negatives_for([], "INVISIBLE"), ["invisible"])
        self.assertEqual(B.negatives_for([], "CHANGED"), [])

    def test_order_and_dedup(self):
        causes = [{"cause": "addr_literal"}, {"cause": "page_local"}, {"cause": "param_copy"}]
        self.assertEqual(B.negatives_for(causes, "RECOLOURED"), ["address", "t69", "recoloured"])

    def test_every_label_has_text(self):
        for label in set(B.CAUSE_NEGATIVE.values()) | set(B.CLASS_NEGATIVE.values()):
            self.assertIn(label, B.NEGATIVES)
            self.assertTrue(all(B.NEGATIVES[label]))


class Rendering(unittest.TestCase):
    """A site beyond the near band must carry NO cause (round 33's control), one inside it must."""
    SITE = ("keep", "ASM_KEEP", "v", 0, 0, 12, "")
    CENS = {"line": 12, "fp": {"shape": "-addiu +ori", "regs": [["$2", "$3"]]}}

    def test_near_site_prints_causes(self):
        out = "\n".join(B.render_site(site(0, 2, "L0", CAUSE), self.SITE, self.CENS, None))
        self.assertIn("addr_literal", out)
        self.assertIn("a compatible mechanism, not the move", out)
        self.assertIn("register pairs $2>$3", out)

    def test_far_site_prints_no_cause(self):
        out = "\n".join(B.render_site(site(0, 30, "L2", CAUSE), self.SITE, self.CENS, None))
        self.assertNotIn("addr_literal", out)
        self.assertIn("no cause", out)
        self.assertIn("beyond the near band", out)

    def test_journal_outcome_is_printed_when_the_split_has_it(self):
        split = {"journal": [["t29_addrsym", "refused"], ["t54_pagebase", "noop"]]}
        out = "\n".join(B.render_site(site(0, 2, "L0", CAUSE), self.SITE, self.CENS, split))
        self.assertIn("`t29_addrsym` refused", out)

    def test_journal_is_silent_without_a_split_record(self):
        out = "\n".join(B.render_site(site(0, 2, "L0", CAUSE), self.SITE, self.CENS, None))
        self.assertNotIn("journal", out)


class Brief(unittest.TestCase):
    def test_carries_the_scaffolding_list_verbatim(self):
        keep = (ROOT / "tools/lanes/keep_lane_brief.md").read_text()
        block = keep[keep.index("## Not allowed"):keep.index("## Tools, budget, output")].rstrip() + "\n"
        brief = (ROOT / "tools/lanes/catalog_lane_brief.md").read_text()
        self.assertIn(block, brief)

    def test_tier_and_tokens(self):
        brief = (ROOT / "tools/lanes/catalog_lane_brief.md").read_text()
        title = brief.splitlines()[0]
        self.assertIn("(sol", title)                       # ledger.parse_title reads the tier from here
        for token in ("@LANE@", "@NROWS@", "@ROOT@", "@HOME@", "@BUCKET@", "@RETRY@", "@NEAR@", "@FAR@"):
            self.assertIn(token, brief)
        for rule in ("never run git", "out/<container>/<name>.c", ".base_sha",
                     "at most 4 compiles", "unreachable class is a finding".lower()):
            self.assertIn(rule.lower(), brief.lower())

    def test_built_briefs_have_no_token_left(self):
        for lane in ("catalog_near1", "catalog_far1"):
            p = ROOT / "work/native_lane" / lane / "BRIEF.md"
            if p.exists():
                self.assertNotIn("@", p.read_text().replace("@anthropic", ""), lane)


if __name__ == "__main__":
    unittest.main()
