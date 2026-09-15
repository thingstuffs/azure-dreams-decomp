"""The pool table's classifiers, on synthetic records only: family (and its tie-break), the pin
bands and the --band parser, the register stratum, the alloc_probe knob class and the near band.
No tree, no traces, no compiler."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "lanes"))
import pools


class Family(unittest.TestCase):
    def test_macro_family(self):
        self.assertEqual(pools.macro_family("ASM_REG"), "REG")
        self.assertEqual(pools.macro_family("ASM_KEEP_NV"), "KEEP")
        self.assertEqual(pools.macro_family("ASM_KEEP4_NV"), "KEEP")
        self.assertEqual(pools.macro_family("ASM_SCHED_BARRIER"), "FENCE")
        self.assertEqual(pools.macro_family("ASM_MEM_BARRIER"), "FENCE")
        self.assertEqual(pools.macro_family("ASM_USE_NV"), "OTHER")
        self.assertEqual(pools.macro_family("ASM_TAILSLOT_PIN"), "OTHER")

    def test_counts_from_text(self):
        text = ('void f(void) {\n'
                '    register int a ASM_REG("$4");\n'
                '    ASM_KEEP(a);\n'
                '    ASM_KEEP_NV(a);\n'
                '    ASM_SCHED_BARRIER();\n'
                '    ASM_USE(a);\n'
                '}\n')
        self.assertEqual(pools.family_counts(text), {"REG": 1, "KEEP": 2, "FENCE": 1, "OTHER": 1})

    def test_dominant_and_ties(self):
        self.assertEqual(pools.dominant_family({"REG": 1, "KEEP": 5, "FENCE": 0, "OTHER": 0}), "KEEP")
        # equal counts: REG > KEEP > FENCE > OTHER
        self.assertEqual(pools.dominant_family({"REG": 2, "KEEP": 2, "FENCE": 2, "OTHER": 2}), "REG")
        self.assertEqual(pools.dominant_family({"REG": 0, "KEEP": 3, "FENCE": 3, "OTHER": 0}), "KEEP")
        self.assertEqual(pools.dominant_family({"REG": 0, "KEEP": 0, "FENCE": 1, "OTHER": 1}), "FENCE")


class Bands(unittest.TestCase):
    def test_band_edges(self):
        self.assertEqual([pools.band(n) for n in (1, 2, 3, 4, 8, 9, 20, 21, 97)],
                         ["1", "2-3", "2-3", "4-8", "4-8", "9-20", "9-20", "21+", "21+"])

    def test_parse_band(self):
        self.assertEqual(pools.parse_band("1-3"), (1, 3))
        self.assertEqual(pools.parse_band("4"), (4, 4))
        self.assertEqual(pools.parse_band("21+"), (21, float("inf")))

    def test_table_labels_parse_to_themselves(self):
        for label in pools.BANDS:
            lo, hi = pools.parse_band(label)
            for n in range(1, 40):
                self.assertEqual(lo <= n <= hi, pools.band(n) == label, (label, n))


class Stratum(unittest.TestCase):
    def test_first_match_wins(self):
        # global-hard-conflict is alloc1, call-clobber-exclusion alloc3: the earlier pack takes it
        self.assertEqual(pools.stratum_of({"global-hard-conflict", "call-clobber-exclusion"}), "alloc1")
        self.assertEqual(pools.stratum_of({"call-clobber-exclusion"}), "alloc3")
        self.assertEqual(pools.stratum_of({"global-scan-order-or-class"}), "alloc5")

    def test_no_reason_is_no_stratum(self):
        self.assertEqual(pools.stratum_of(set()), "no-stratum")
        self.assertEqual(pools.stratum_of({"global-competition-or-scan-unresolved"}), "no-stratum")

    def test_key_orders_packs_then_labels(self):
        order = sorted(["-", "alloc3", "no-stratum", "alloc1", "trace-stale"], key=pools.stratum_key)
        self.assertEqual(order, ["alloc1", "alloc3", "no-stratum", "trace-stale", "-"])


class MergeStrata(unittest.TestCase):
    """Both trace directories, in precedence order: the re-traces, then the alloc_astra population
    the alloc packs were cut from (the defect: the population was not read, so a row a pack had
    stratified printed as '-' = never traced)."""
    def merged(self):
        return pools.merge_strata([
            ("raw", {"a/f1": "alloc1", "a/f2": "no-stratum"}, {"a/f1", "a/f2", "a/f3"}),
            ("population", {"a/f1": "alloc3", "a/f4": "alloc2"}, {"a/f1", "a/f4", "a/f5"})])

    def test_first_directory_wins(self):
        out, src = self.merged()
        self.assertEqual(out["a/f1"], "alloc1")          # raw's reading, not the population's
        self.assertEqual(src["a/f1"], "raw")

    def test_population_fills_in_what_raw_never_traced(self):
        out, src = self.merged()
        self.assertEqual((out["a/f4"], src["a/f4"]), ("alloc2", "population"))

    def test_trace_stale_only_when_every_directory_dropped_it(self):
        out, src = self.merged()
        self.assertEqual(out["a/f3"], "trace-stale")     # a file in raw, stratified by neither
        self.assertEqual(out["a/f5"], "trace-stale")
        self.assertEqual(src["a/f3"], "dropped by both")

    def test_a_row_no_directory_has_is_absent(self):
        out, _ = self.merged()
        self.assertNotIn("a/f9", out)                    # the caller reads a missing row as '-'

    def test_a_row_stratified_in_one_is_never_trace_stale(self):
        # f2 has a file in raw only and IS stratified there: no-stratum, not trace-stale
        out, _ = self.merged()
        self.assertEqual(out["a/f2"], "no-stratum")


class Knobs(unittest.TestCase):
    def rep(self, *sites):
        return {"id": "dungeon/func_80000000", "sites": list(sites)}

    def test_precedence(self):
        one = {"status": "ok", "erased_distance": 5, "any_knob": True, "force_exact": True}
        force = {"status": "ok", "erased_distance": 5, "any_knob": False, "force_exact": True}
        none = {"status": "ok", "erased_distance": 5, "any_knob": False, "force_exact": False}
        plan = {"status": "no-knob-plan"}
        self.assertEqual(pools.knob_class(self.rep(force, one)), "one-knob")
        self.assertEqual(pools.knob_class(self.rep(none, force)), "force-only")
        self.assertEqual(pools.knob_class(self.rep(plan, none)), "no-knob-plan")
        self.assertEqual(pools.knob_class(self.rep(none)), "none")
        self.assertEqual(pools.knob_class(self.rep(plan)), "no-knob-plan")

    def test_inert_and_untrusted_sites_are_no_evidence(self):
        inert = {"status": "ok", "erased_distance": 0, "any_knob": True, "force_exact": True}
        untrusted = {"status": "untrusted", "any_knob": True}
        self.assertEqual(pools.knob_class(self.rep(inert, untrusted)), "none")
        self.assertEqual(pools.knob_class(self.rep()), "none")
        self.assertEqual(pools.knob_class(None), "none")


class Near(unittest.TestCase):
    def test_stale_when_the_text_moved(self):
        r = {"source_sha": "aaa", "groups": [{"d0": 2, "best": 2}]}
        self.assertEqual(pools.near_of(r, "bbb"), ("stale", None, False))

    def test_min_d0_and_improvement(self):
        r = {"source_sha": "aaa", "groups": [{"d0": 7, "best": 7}, {"d0": 3, "best": 1}]}
        self.assertEqual(pools.near_of(r, "aaa"), ("fresh", 3, True))
        r2 = {"source_sha": "aaa", "groups": [{"d0": 4, "best": 4}]}
        self.assertEqual(pools.near_of(r2, "aaa"), ("fresh", 4, False))

    def test_no_result_and_no_groups(self):
        self.assertEqual(pools.near_of(None, "aaa"), ("-", None, False))
        self.assertEqual(pools.near_of({"source_sha": "aaa", "groups": []}, "aaa"), ("fresh", None, False))


class NearMerged(unittest.TestCase):
    """Every tag's results for one row (oldest tag first): the newest FRESH result decides, so the
    default no longer shows one small tag's coverage as the whole tree's near band."""
    def cands(self):
        old = {"source_sha": "aaa", "groups": [{"d0": 3, "best": 1}]}          # fresh, older tag
        newer_stale = {"source_sha": "zzz", "groups": [{"d0": 1, "best": 1}]}  # a moved-text result
        return [(("2026-09-13T00:00:00Z", 1), "budget4x", old),
                (("2026-09-15T00:00:00Z", 2), "deep_pilot", newer_stale)]

    def test_a_stale_newer_result_never_hides_a_fresh_older_one(self):
        self.assertEqual(pools.near_merged(self.cands(), "aaa"), ("fresh", 3, True, "budget4x"))

    def test_newest_fresh_wins_and_improving_is_the_union(self):
        c = [(("2026-09-13T00:00:00Z", 1), "old", {"source_sha": "aaa", "groups": [{"d0": 6, "best": 2}]}),
             (("2026-09-15T00:00:00Z", 2), "new", {"source_sha": "aaa", "groups": [{"d0": 6, "best": 6}]})]
        self.assertEqual(pools.near_merged(c, "aaa"), ("fresh", 6, True, "new"))

    def test_nothing_fresh_is_stale_not_missing(self):
        state, d0, imp, tag = pools.near_merged(self.cands(), "bbb")
        self.assertEqual((state, d0, imp, tag), ("stale", None, False, "deep_pilot"))

    def test_no_result_at_all(self):
        self.assertEqual(pools.near_merged([], "aaa"), ("-", None, False, None))
        self.assertEqual(pools.near_merged(None, "aaa"), ("-", None, False, None))


def rec(rid, family, stratum, pins, served=(), d0=None, near=None):
    return {"id": rid, "container": rid.split("/")[0], "size": 100, "cfg": "2.7.2",
            "family": family, "counts": {}, "pins": pins, "band": pools.band(pins),
            "served": list(served), "stratum": stratum, "stratum_source": "raw", "knob": "-",
            "near": near or ("fresh" if d0 is not None else "-"), "d0": d0, "improving": False,
            "near_tag": None}


RECS = [rec("a/f1", "REG", "alloc5", 2, d0=3),
        rec("a/f2", "REG", "alloc5", 3, served=["alloc5"], d0=9),
        rec("a/f3", "REG", "alloc1", 12),
        rec("a/f4", "KEEP", "-", 1, d0=4)]


class Aggregation(unittest.TestCase):
    def test_agg_splits_the_search_and_near_counts_by_served(self):
        # unserved (rows, pins, searched, near), then served (rows, pins, searched, near)
        self.assertEqual(pools.agg(RECS), (3, 15, 2, 2, 1, 3, 1, 0))

    def test_a_near_served_row_is_never_counted_against_the_unserved_pool(self):
        # the defect: one served near row printed in a `near` column beside 16 unserved rows
        group = [rec("a/u1", "KEEP", "-", 1), rec("a/s1", "KEEP", "-", 1, served=["keeps1"], d0=2)]
        self.assertEqual(pools.agg(group), (1, 1, 0, 0, 1, 1, 1, 1))

    def test_unsearched_is_not_searched_and_far(self):
        # srch 0 says "never searched"; a fresh result with no group is searched but not near
        group = [rec("a/u1", "REG", "alloc1", 2), rec("a/u2", "REG", "alloc1", 2, near="fresh"),
                 rec("a/u3", "REG", "alloc1", 2, near="stale")]
        self.assertEqual(pools.agg(group), (3, 6, 1, 0, 0, 0, 0, 0))

    def test_row_listing_filters(self):
        out = pools.render_rows(RECS, "REG", "alloc5", "1-3", "unserved").splitlines()
        self.assertEqual([l.split()[0] for l in out], ["a/f1"])
        self.assertIn("pins=2", out[0])
        self.assertIn("d0=3", out[0])
        every = pools.render_rows(RECS, "REG", None, None, "all").splitlines()
        self.assertEqual([l.split()[0] for l in every], ["a/f1", "a/f2", "a/f3"])
        served = pools.render_rows(RECS, None, None, None, "served").splitlines()
        self.assertEqual([l.split()[0] for l in served], ["a/f2"])


if __name__ == "__main__":
    unittest.main()
