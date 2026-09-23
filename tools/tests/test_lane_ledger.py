"""The lane ledger's parsers and its incremental build, on synthetic lanes in a tempdir only."""
import hashlib
import json
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "lanes"))
import ledger


CODEX_HEADER = """Reading prompt from stdin...
OpenAI Codex v0.154.0
--------
workdir: <repo>
model: gpt-5.6-sol
provider: openai
approval: never
--------
user
model: this-is-the-prompt-not-the-header
"""


class ParseModel(unittest.TestCase):
    def test_header_line(self):
        self.assertEqual(ledger.parse_model(CODEX_HEADER), "gpt-5.6-sol")

    def test_stops_at_the_user_block(self):
        self.assertIsNone(ledger.parse_model("--------\nuser\nmodel: gpt-5.6-luna\n"))

    def test_absent(self):
        self.assertIsNone(ledger.parse_model("no header here\n"))

    def test_tier_of_model(self):
        self.assertEqual(ledger.tier_of_model("gpt-5.6-luna"), "luna")
        self.assertEqual(ledger.tier_of_model("gpt-6-astra"), "astra")
        self.assertIsNone(ledger.tier_of_model("gemini-3.8-flash-high"))
        self.assertIsNone(ledger.tier_of_model(None))

    def test_tier_of_model_gpt6_generation(self):
        self.assertEqual(ledger.tier_of_model("gpt-6-sol"), "sol6")
        self.assertEqual(ledger.tier_of_model("gpt-6-luna"), "luna6")
        self.assertEqual(ledger.tier_of_model("gpt-6-astra"), "astra")
        self.assertEqual(ledger.tier_of_model("gpt-5.6-sol"), "sol")

    def test_tier_of_model_claude(self):
        self.assertEqual(ledger.tier_of_model("claude-opus-5-5[1m]"), "opus")
        self.assertEqual(ledger.tier_of_model("claude-sonnet-5"), "sonnet")
        self.assertEqual(ledger.tier_of_model("gpt-5.6-luna"), "luna")

    def test_ansi_bold_header(self):
        # codex >= 0.154 wraps the header keys in ANSI bold
        self.assertEqual(ledger.parse_model("--------\n\x1b[1mmodel:\x1b[0m gpt-6-sol\n"), "gpt-6-sol")


class ParseTitle(unittest.TestCase):
    def test_tier_and_family(self):
        self.assertEqual(ledger.parse_title("# Lane: diagnosed register pins (luna), 12 rows"),
                         ("luna", "REG"))
        self.assertEqual(ledger.parse_title("# Lane: live scheduling fences (luna), 12 rows"),
                         ("luna", "FENCE"))
        self.assertEqual(ledger.parse_title("# Lane: label-as-call rows as honest C (opus), 8 rows"),
                         ("opus", "LAC"))

    def test_label_as_call_beats_keep(self):
        # a "lackeep" brief names both; LAC must win
        self.assertEqual(ledger.parse_title("# Lane: label-as-call rows whose keeps resist (sol)"),
                         ("sol", "LAC"))

    def test_gpt6_tiers_in_title(self):
        self.assertEqual(ledger.parse_title("# Lane: diagnosed register pins (sol6), 5 rows")[0], "sol6")
        self.assertEqual(ledger.parse_title("# Lane: diagnosed register pins (luna6), 5 rows")[0], "luna6")
        self.assertEqual(ledger.parse_title("# Lane: register pins (REG, sol6)")[0], "sol6")
        self.assertEqual(ledger.parse_title("# Lane: register pins (sol), 5 rows")[0], "sol")

    def test_no_tier_no_family(self):
        self.assertEqual(ledger.parse_title("# Native lane report"), (None, None))


class ParseStratum(unittest.TestCase):
    def test_single(self):
        self.assertEqual(ledger.parse_stratum("- stratum **alloc1**\n- stratum **alloc1**\n"), "alloc1")

    def test_mixed_is_joined_sorted(self):
        self.assertEqual(ledger.parse_stratum("stratum **alloc5**\nstratum **alloc2**\n"), "alloc2+alloc5")

    def test_none(self):
        self.assertIsNone(ledger.parse_stratum("# Rows\nno markers here\n"))


class ParseJournal(unittest.TestCase):
    def test_applied_deduped_and_refused_counted(self):
        text = "\n".join([
            json.dumps({"id": "town/a", "outcome": "applied"}),
            json.dumps({"id": "town/b", "outcome": "refused"}),
            json.dumps({"id": "town/a", "outcome": "applied"}),      # re-landed: one row
            json.dumps({"id": "town/c", "outcome": "applied"}),
            "",
            "{ not json",
            json.dumps({"id": "town/d"}),                            # no outcome: not a landing
        ])
        self.assertEqual(ledger.parse_journal(text), (["town/a", "town/c"], 1))

    def test_empty(self):
        self.assertEqual(ledger.parse_journal(""), ([], 0))


class Fingerprint(unittest.TestCase):
    def test_order_independent_but_size_sensitive(self):
        a = ledger.fingerprint([("base/c/a.c", 10), ("out/c/a.c", 9)])
        self.assertEqual(a, ledger.fingerprint([("out/c/a.c", 9), ("base/c/a.c", 10)]))
        self.assertNotEqual(a, ledger.fingerprint([("base/c/a.c", 11), ("out/c/a.c", 9)]))


PIN = 'void f(void) { ASM_SCHED_BARRIER(); ASM_SCHED_BARRIER(); }\n'
CLEAN = 'void f(void) { }\n'


def make_rows(root, ids):
    """The row db and nothing else: a row with no file under src/ has no tree witness."""
    p = root / "ledger" / "rows.jsonl"
    p.parent.mkdir(parents=True, exist_ok=True)
    p.write_text("".join(json.dumps({"id": rid, "container": rid.split("/")[0],
                                     "c_path": "overlays/x/%s.c" % rid.split("/")[1]}) + "\n"
                         for rid in ids))


def make_tree(root, rid, text):
    p = root / "src" / rid.split("/")[0] / (rid.split("/")[1] + ".c")
    p.parent.mkdir(parents=True, exist_ok=True)
    p.write_text(text)


def make_lane(root, name, served, exact, landed, brief=None, log=None, rows_md=None,
              out_text=None, base_sha=True):
    d = root / "work" / "native_lane" / name
    for rid in served:
        p = d / "base" / (rid + ".c")
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(PIN)
    for rid in exact:
        p = d / "out" / (rid + ".c")
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text((out_text or {}).get(rid, CLEAN))
        b = d / "base" / (rid + ".c")
        if base_sha:      # the runner stamps the sha256 of the base the output was made from
            (d / "out" / (rid + ".c.base_sha")).write_text(
                (hashlib.sha256(b.read_bytes()).hexdigest() if b.exists() else "de00" * 16) + "\n")
    d.mkdir(parents=True, exist_ok=True)
    (d / "PROMPT.txt").write_text("FIRST RULE\n")
    if brief:
        (d / "BRIEF.md").write_text(brief + "\n")
    if log:
        (d / "codex.log").write_text(log)
    if rows_md:
        (d / "rows.md").write_text(rows_md)
    j = root / "ledger" / "sweeps" / ("lane_%s.jsonl" % name)
    if landed is not None:
        j.parent.mkdir(parents=True, exist_ok=True)
        j.write_text("".join(json.dumps({"id": r, "outcome": "applied"}) + "\n" for r in landed))
    return d


class ScanAndBuild(unittest.TestCase):
    def setUp(self):
        self._td = tempfile.TemporaryDirectory()
        self.root = Path(self._td.name)
        served_mod = sys.modules[ledger.served_mod.__name__]
        served_mod._CACHE.clear()
        make_lane(self.root, "alloc99", ["town/a", "town/b", "town/c", "town/d"], ["town/a", "town/b"],
                  ["town/a", "town/b"],
                  brief="# Lane: diagnosed register pins (luna), 4 rows", log=CODEX_HEADER,
                  rows_md="- stratum **alloc1**\n")
        make_lane(self.root, "honest99", [], ["town/e"], ["town/e"])   # no base/: served unknown
        make_lane(self.root, "fences99", ["town/f", "town/g"], [], None,
                  brief="# Lane: live scheduling fences (luna), 2 rows")  # no journal at all
        agy = make_lane(self.root, "alloc98", ["town/h"], [], [],
                        brief="# Lane: diagnosed register pins (luna), 1 rows")
        (agy / "agy.log").write_text("")     # the runner leaves it empty; the title still says luna
        (self.root / "work" / "native_lane" / "scratchpad").mkdir()
        (self.root / "work" / "native_lane" / "sw_pool.txt").write_text("not a lane\n")
        make_rows(self.root, ["town/a", "town/b", "town/c", "town/d", "town/e", "town/f", "town/g",
                              "town/h", "town/t1", "town/t2", "town/t3", "town/t4", "town/t5"])
        ledger._ROW_PATHS.clear()

    def tearDown(self):
        self._td.cleanup()
        sys.modules[ledger.served_mod.__name__]._CACHE.clear()
        ledger._ROW_PATHS.clear()

    def test_lane_dirs_skips_files_and_nonlanes(self):
        self.assertEqual([d.name for d in ledger.lane_dirs(self.root)],
                         ["alloc98", "alloc99", "fences99", "honest99"])

    def test_records(self):
        recs, reused = ledger.build(self.root)
        self.assertEqual(reused, 0)
        by = {r["lane"]: r for r in recs}
        a = by["alloc99"]
        self.assertEqual((a["tier"], a["model"], a["family"], a["stratum"]),
                         ("sol", "gpt-5.6-sol", "REG", "alloc1"))   # the log's tier beats the brief's
        self.assertEqual((a["served"], a["exact"], a["landed"], a["pins_removed"], a["rate"]),
                         (4, 2, 2, 4, 0.5))
        h = by["honest99"]
        self.assertFalse(h["served_known"])
        self.assertIsNone(h["rate"])
        self.assertEqual((h["landed"], h["pins_unknown_rows"], h["family"]), (1, 1, "LAC"))
        self.assertEqual(by["alloc98"]["tier"], "agy")   # the empty agy.log outranks the "(luna)" title
        self.assertIsNone(by["alloc98"]["model"])
        f = by["fences99"]
        self.assertEqual((f["journal"], f["landed"], f["served"], f["rate"], f["family"]),
                         (False, 0, 2, 0.0, "FENCE"))

    def test_build_is_incremental(self):
        ledger.build(self.root)
        sys.modules[ledger.served_mod.__name__]._CACHE.clear()
        recs, reused = ledger.build(self.root)
        self.assertEqual((len(recs), reused), (4, 4))
        (self.root / "work" / "native_lane" / "fences99" / "out" / "town").mkdir(parents=True)
        (self.root / "work" / "native_lane" / "fences99" / "out" / "town" / "f.c").write_text(CLEAN)
        sys.modules[ledger.served_mod.__name__]._CACHE.clear()
        recs, reused = ledger.build(self.root)
        self.assertEqual(reused, 3)
        self.assertEqual({r["lane"]: r["exact"] for r in recs}["fences99"], 1)

    def test_aggregate_and_closed(self):
        recs, _ = ledger.build(self.root)
        agg = ledger.aggregate(recs, ["family"])
        self.assertEqual(agg[("REG",)]["served"], 5)   # alloc99's 4 rows and alloc98's 1
        self.assertEqual(agg[("LAC",)], dict(lanes=1, nobase=1, served=0, served_landed=0,
                                             exact=1, landed=1, pins=0))
        self.assertEqual(ledger.closed(recs, 0.4, minserved=2),
                         [("FENCE", "-", 0.0, 2)])       # REG alloc1 paid 0.50 on 4, FENCE 0 on 2
        self.assertEqual(ledger.closed(recs, 0.6, minserved=2),   # alloc98's 1 row is under minserved
                         [("FENCE", "-", 0.0, 2), ("REG", "alloc1", 0.5, 4)])
        self.assertEqual(ledger.closed(recs, 0.6, minserved=20), [])   # too few rows to close anything

    def test_tables_render(self):
        recs, _ = ledger.build(self.root)
        self.assertIn("| alloc99 | sol | gpt-5.6-sol | REG | alloc1 | 4 | 2 | 2 | 4 | 0.50 |",
                      ledger.table(recs))
        self.assertIn("| honest99 | ? | - | LAC | - | ? |", ledger.table(recs))
        self.assertIn("**total**", ledger.by_table(recs, ["tier", "stratum"]))


class TreeWitness(unittest.TestCase):
    """The second witness: an exact output that IS the row's text in the tree today landed, whether or
    not a lane journal recorded it (19 real lanes, 221 outputs, have no journal at all)."""

    def setUp(self):
        self._td = tempfile.TemporaryDirectory()
        self.root = Path(self._td.name)
        sys.modules[ledger.served_mod.__name__]._CACHE.clear()
        ledger._ROW_PATHS.clear()
        make_rows(self.root, ["town/t%d" % i for i in range(1, 8)])
        # t1 landed (out is the tree text, base was different); t2 is a no-op (out == base == tree);
        # t3 was never applied (the tree says something else).
        make_lane(self.root, "tree99", ["town/t1", "town/t2", "town/t3"],
                  ["town/t1", "town/t2", "town/t3"], None, out_text={"town/t2": PIN})
        make_tree(self.root, "town/t1", CLEAN)
        make_tree(self.root, "town/t2", PIN)
        make_tree(self.root, "town/t3", "void f(void) { g(); }\n")
        # no base/ kept: `.base_sha` still proves the output changed something
        make_lane(self.root, "nobase99", [], ["town/t4"], None)
        make_tree(self.root, "town/t4", CLEAN)
        # neither base/ nor .base_sha: nothing to compare against, so no credit
        make_lane(self.root, "nosha99", [], ["town/t5"], None, base_sha=False)
        make_tree(self.root, "town/t5", CLEAN)
        # t6 is claimed by jrn99's journal: dup99's identical output must not be counted a second time
        make_lane(self.root, "jrn99", ["town/t6"], ["town/t6"], ["town/t6"])
        make_lane(self.root, "dup99", ["town/t6"], ["town/t6"], None)
        make_tree(self.root, "town/t6", CLEAN)

    def tearDown(self):
        self._td.cleanup()
        sys.modules[ledger.served_mod.__name__]._CACHE.clear()
        ledger._ROW_PATHS.clear()

    def build(self):
        recs, _ = ledger.build(self.root)
        return {r["lane"]: r for r in recs}

    def test_tree_landing_and_the_no_op_guard(self):
        t = self.build()["tree99"]
        self.assertEqual((t["journal"], t["landed"], t["landed_journal"], t["landed_tree"]),
                         (False, 1, 0, 1))
        self.assertEqual((t["served"], t["rate"], t["pins_removed"]), (3, 0.3333, 2))

    def test_base_sha_carries_the_lanes_that_kept_no_base(self):
        by = self.build()
        self.assertEqual((by["nobase99"]["landed"], by["nobase99"]["pins_unknown_rows"]), (1, 1))
        self.assertIsNone(by["nobase99"]["rate"])          # served unknown: a landing, no rate
        self.assertEqual(by["nosha99"]["landed"], 0)       # no witness that the output changed anything

    def test_a_row_a_journal_claims_is_never_tree_credited_twice(self):
        by = self.build()
        self.assertEqual((by["jrn99"]["landed"], by["jrn99"]["landed_journal"]), (1, 1))
        self.assertEqual((by["dup99"]["landed"], by["dup99"]["landed_tree"]), (0, 0))

    def test_an_edit_to_the_tree_invalidates_the_cached_lane(self):
        self.assertEqual(self.build()["tree99"]["landed"], 1)
        recs, reused = ledger.build(self.root)
        self.assertEqual(reused, len(recs))
        make_tree(self.root, "town/t1", "void f(void) { h(); }\n")   # a later round edited it further
        recs, reused = ledger.build(self.root)
        by = {r["lane"]: r for r in recs}
        self.assertEqual(reused, len(recs) - 1)
        self.assertEqual(by["tree99"]["landed"], 0)


class CacheInvalidation(unittest.TestCase):
    """A fix to the tool's own tables or parsers must reach an existing ledger/lanes.jsonl."""

    def setUp(self):
        self._td = tempfile.TemporaryDirectory()
        self.root = Path(self._td.name)
        sys.modules[ledger.served_mod.__name__]._CACHE.clear()
        ledger._ROW_PATHS.clear()
        make_lane(self.root, "fences99", ["town/f", "town/g"], [], None,
                  brief="# Lane: live scheduling fences (luna), 2 rows")
        make_lane(self.root, "alloc99", ["town/a"], [], ["town/a"],
                  brief="# Lane: diagnosed register pins (luna), 1 rows")
        ledger.build(self.root)

    def tearDown(self):
        self._td.cleanup()
        sys.modules[ledger.served_mod.__name__]._CACHE.clear()
        ledger._ROW_PATHS.clear()

    def test_reuses_an_unchanged_tree(self):
        recs, reused = ledger.build(self.root)
        self.assertEqual((len(recs), reused), (2, 2))

    def test_a_corrected_family_table_rebuilds_by_itself(self):
        old = ledger.FAMILY_WORDS
        try:
            ledger.FAMILY_WORDS = [("scheduling fences", "ZZZFENCE")] + list(old)
            recs, reused = ledger.build(self.root)
        finally:
            ledger.FAMILY_WORDS = old
        self.assertEqual(reused, 0)
        self.assertEqual({r["lane"]: r["family"] for r in recs}["fences99"], "ZZZFENCE")
        self.assertEqual(ledger.build(self.root)[1], 0)   # and back again, with the table restored

    def test_force_rescans_everything(self):
        self.assertEqual(ledger.build(self.root, force=True)[1], 0)
        self.assertEqual(ledger.build(self.root)[1], 2)


if __name__ == "__main__":
    unittest.main()
