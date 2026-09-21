"""tools/lanes/refresh_exemplars.py: which lane directories are read, how a candidate's base text is
recovered, which candidates count as exemplars, the per-row pick and the legacy carry-forward.  Fake
lane trees only - no git recovery, no compiles, no real census (the class lookup is stubbed)."""
import json
import shutil
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/lanes"))
import refresh_exemplars as R  # noqa: E402
from common import sha_text  # noqa: E402

BASE = '''#include "common.h"

void func_800A0000(s32 arg0) {
    s32 total;
    register s32 cursor ASM_REG("$19");

    cursor = arg0;
    ASM_KEEP(cursor);   /* UNRESOLVED C shape (pin) */
    total = cursor + 1;
    use(total);
}
'''

OUT = '''#include "common.h"

void func_800A0000(s32 arg0) {
    s32 total;
    register s32 cursor ASM_REG("$19");

    cursor = arg0;
    total = cursor + 1;
    use(total);
}
'''

ARMED = '''#include "common.h"

void func_800A0000(s32 arg0) {
#ifdef NON_MATCHING
    s32 cursor;
#else
    register s32 cursor ASM_REG("$19");
#endif
    cursor = arg0;
    ASM_KEEP(cursor);   /* UNRESOLVED C shape (pin) */
    use(cursor);
}
'''

ARM_FLATTENED = '''#include "common.h"

void func_800A0000(s32 arg0) {
    s32 cursor;
    cursor = arg0;
    use(cursor);
}
'''


def put(root, lane, kind, rid, text, sha=None):
    d = Path(root) / "work/native_lane" / lane / kind / rid.split("/")[0]
    d.mkdir(parents=True, exist_ok=True)
    p = d / (rid.split("/")[1] + ".c")
    p.write_text(text)
    if kind == "out":
        (d / (rid.split("/")[1] + ".c.base_sha")).write_text((sha or "") + "\n")
    return p


class Base(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.mkdtemp()
        self.lanes = Path(self.tmp) / "work/native_lane"
        self.lanes.mkdir(parents=True)
        self._cls, self._rows = R.census_classes, R.rows
        R.census_classes = lambda path=R.CENSUS: ({"dungeon/func_800A0000": {"CHANGED|5-8|-lw +lw"}},
                                                  {"dungeon/func_800A0000": {"CHANGED|5-8"}})
        R.rows = lambda: [{"id": "dungeon/func_800A0000", "cfg": "2.7.2-cdk-G0"}]

    def tearDown(self):
        R.census_classes, R.rows = self._cls, self._rows
        shutil.rmtree(self.tmp, ignore_errors=True)

    def build(self, **kw):
        kw.setdefault("use_git", False)
        kw.setdefault("verbose", False)
        return R.build(root=self.lanes, **kw)


class TestLaneScan(Base):
    def test_only_r5_r6_lanes(self):
        for n in ("r59_sol_mid", "r68_t95_runjoint", "r4_old", "sched_astra", "notes"):
            (self.lanes / n).mkdir()
        self.assertEqual(R.lane_names(self.lanes), ["r59_sol_mid", "r68_t95_runjoint"])


class TestRecords(Base):
    def test_model_lane_record(self):
        put(self.tmp, "r68_sol_a", "base", "dungeon/func_800A0000", BASE)
        put(self.tmp, "r68_sol_a", "out", "dungeon/func_800A0000", OUT, sha_text(BASE))
        (self.lanes / "r68_sol_a/REPORT.md").write_text(
            "# report\n\n### dungeon/func_800A0000\n\nResult: MATCH (exact: true, 0 subs).\n"
            "The keep went away when the cursor lifetime merged with total. More prose.\n")
        scored, stats = self.build()
        self.assertEqual(stats["kept"], 1)
        rec = scored[0][0]
        self.assertEqual(rec["id"], "dungeon/func_800A0000")
        self.assertEqual(rec["pins"], [2, 1])
        self.assertEqual(rec["cfg"], "2.7.2-cdk-G0")
        self.assertEqual(rec["classes"], ["CHANGED|5-8|-lw +lw"])
        self.assertEqual(rec["L0"], ["CHANGED|5-8"])
        self.assertEqual(rec["lane"], "r68_sol_a")
        self.assertTrue(rec["diff"].startswith("@@"))
        self.assertIn("ASM_KEEP", rec["diff"])
        # the scoring verdict is skipped: the move sentence is the one that says what changed
        self.assertTrue(rec["move"].startswith("The keep went away"), rec["move"])

    def test_generator_lane_base_from_a_sibling_and_move_from_the_journal(self):
        put(self.tmp, "r68_sol_a", "base", "dungeon/func_800A0000", BASE)      # the sibling holding the text
        put(self.tmp, "r68_t95_runjoint", "out", "dungeon/func_800A0000", OUT, sha_text(BASE))
        (self.lanes / "r68_t95_runjoint/journal.jsonl").write_text(json.dumps(
            {"id": "dungeon/func_800A0000", "in_sha": sha_text(BASE), "outcome": "exact",
             "label": "run5@114"}) + "\n")
        scored, stats = self.build()
        self.assertEqual(stats["kept"], 1)
        self.assertEqual(scored[0][0]["move"], "run5@114")
        self.assertEqual(scored[0][0]["lane"], "r68_t95_runjoint")

    def test_journal_key_precedence(self):
        put(self.tmp, "r68_sol_a", "base", "dungeon/func_800A0000", BASE)
        put(self.tmp, "r68_t89_x", "out", "dungeon/func_800A0000", OUT, sha_text(BASE))
        (self.lanes / "r68_t89_x/journal.jsonl").write_text(json.dumps(
            {"id": "dungeon/func_800A0000", "in_sha": sha_text(BASE), "outcome": "exact",
             "move": "split:a>b@1", "step": "cast/first", "label": "l"}) + "\n")
        self.assertEqual(self.build()[0][0][0]["move"], "split:a>b@1")

    def test_unrecoverable_base_is_counted_not_guessed(self):
        put(self.tmp, "r68_t89_x", "out", "dungeon/func_800A0000", OUT, "deadbeef")
        scored, stats = self.build()
        self.assertEqual((stats["kept"], stats["no_base"]), (0, 1))


class TestLegitimacy(Base):
    def _one(self, base, out):
        put(self.tmp, "r68_sol_a", "base", "dungeon/func_800A0000", base)
        put(self.tmp, "r68_sol_a", "out", "dungeon/func_800A0000", out, sha_text(base))
        return self.build()[1]

    def test_no_pins_removed_is_not_an_exemplar(self):
        self.assertEqual(self._one(BASE, BASE.replace("total = cursor + 1;", "total = 1 + cursor;"))["not_better"], 1)

    def test_grown_scaffolding_is_refused(self):
        grown = OUT.replace("s32 total;", "volatile s32 total;")
        self.assertEqual(self._one(BASE, grown)["grew"], 1)

    def test_flattened_non_matching_arm_is_refused(self):
        st = self._one(ARMED, ARM_FLATTENED)
        self.assertEqual((st["arm_edit"], st["kept"]), (1, 0))


class TestPickAndCarry(Base):
    def test_largest_pin_drop_wins(self):
        recs = [({"id": "a", "pins": [5, 4]}, (1, 10)), ({"id": "a", "pins": [5, 1]}, (4, 1)),
                ({"id": "b", "pins": [2, 1]}, (1, 1))]
        best = R.pick_best(recs)
        self.assertEqual([r["pins"] for r in best], [[5, 1], [2, 1]])

    def test_newer_lane_breaks_the_tie(self):
        recs = [({"id": "a", "lane": "old"}, (1, 10)), ({"id": "a", "lane": "new"}, (1, 20))]
        self.assertEqual(R.pick_best(recs)[0]["lane"], "new")

    def test_hand_maintained_records_are_carried_not_dropped(self):
        fresh = [{"id": "a"}]
        old = [{"id": "a", "diff": "x"}, {"id": "zz", "diff": "y"}]
        carried = R.carry_legacy(fresh, old)
        self.assertEqual([r["id"] for r in carried], ["zz"])
        self.assertEqual(carried[0]["lane"], "legacy")
        self.assertEqual(carried[0]["move"], "")

    def test_a_rejected_rebuild_record_is_not_reinstated(self):
        # written by an earlier rebuild from r55_switch; this run refused that candidate (a recipe
        # switch), so the row must not come back through the carry-forward
        old = [{"id": "zz", "diff": "y", "lane": "r55_switch", "move": ""}]
        self.assertEqual(R.carry_legacy([], old), [])


class TestDiff(Base):
    def test_long_diff_is_capped_with_a_note(self):
        a = "\n".join("line %d" % i for i in range(2000))
        b = "\n".join("LINE %d" % i for i in range(2000))
        d = R.make_diff(a, b, max_lines=20)
        self.assertEqual(len(d.splitlines()), 21)
        self.assertIn("more diff lines", d.splitlines()[-1])


if __name__ == "__main__":
    unittest.main()
