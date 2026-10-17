"""Reporting readers and link-list placements (docs/LINK_LISTS.md, LL0 REVIEW section 4).

A placement row carries `source_row` (its HOME row) and has no src/ or raw/ file of its own: the home's single TU is
linked at several addresses.  Synthetic fixture: one home row + two placements.  Each reader must count the TU once,
a placement must inherit the home's text facts (levels) and keep its own gate fact.  With no `source_row` anywhere
every reader is unchanged (checked against the live tree in the lane REPORT, not here).

    ./.venv/bin/python3 -m pytest tools/tests/test_readers_placement.py -q
"""
import collections
import contextlib
import io
import json
import os
import sys
import tempfile
import unittest
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path[:0] = [str(TOOLS), str(TOOLS / 'gate')]
import levels as L
import status as S
import census as C
import campaign_rows as CR
import decl_census as DC
import struct_census as SC

HOME_ID, P1_ID, P2_ID = "dungeon/func_80F8A664", "dungeon/func_80F90664", "dungeon/func_80F96664"
HOME_TEXT = '''#include "common.h"
#include "records/Rec_Foo.h"
typedef struct S_80F8A664_1 {
    u32 unk_0;
} S_80F8A664_1;  /* a0 in func_80F8A664 */
extern u32 D_80100000;
s32 func_80F8A664(s32 a0) {
    return a0 + 1;
}
'''
RAW_TEXT = HOME_TEXT.replace("a0 + 1", "a0 + 2")


def mkrow(rid, size=56, source_row=None, container="dungeon"):
    name = rid.split("/")[1]
    r = {"id": rid, "container": container, "func": name, "true_name": None, "defs": None, "kind": "overlay",
         "size": size, "c_path": name + ".c", "exists": source_row is None, "stock": True, "cfg": "2.7.2-cdk -G0 -O2",
         "foff": 0}
    if source_row:
        r["source_row"] = source_row
    return r


class Fixture(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR'))
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name).resolve()
        (self.root / "ledger").mkdir()
        for d in ("src", "raw"):
            (self.root / d / "dungeon").mkdir(parents=True)
        (self.root / "src/dungeon/func_80F8A664.c").write_text(HOME_TEXT)
        (self.root / "raw/dungeon/func_80F8A664.c").write_text(RAW_TEXT)
        self.rows = [mkrow(HOME_ID), mkrow(P1_ID, source_row=HOME_ID), mkrow(P2_ID, source_row=HOME_ID)]
        self.by = {r["id"]: r for r in self.rows}
        (self.root / "ledger/rows.jsonl").write_text("".join(json.dumps(r) + "\n" for r in self.rows))

    def patched(self, module, **attrs):
        saved = {k: getattr(module, k) for k in attrs}
        for k, v in attrs.items():
            setattr(module, k, v)
        self.addCleanup(lambda: [setattr(module, k, v) for k, v in saved.items()])


class Levels(Fixture):
    def setUp(self):
        super().setUp()
        L._CONTAINER_SYMS["dungeon"] = set()
        self.patched(L, raw_path=lambda r: self.root / "raw" / r["container"] / Path(r["c_path"]).name)

    def test_placement_reads_home_text_and_home_raw(self):
        er, text, raw = L.row_view(self.by[P1_ID], self.by, self.root)
        self.assertEqual(text, HOME_TEXT)
        self.assertEqual(raw, RAW_TEXT)               # not "": the placement has no raw of its own
        self.assertEqual((er["id"], er["size"]), (P1_ID, 56))   # its own identity
        self.assertEqual(er["func"], "func_80F8A664")           # the home's names key the text facts

    def test_plain_row_is_unchanged(self):
        r = self.by[HOME_ID]
        er, text, raw = L.row_view(r, self.by, self.root)
        self.assertIs(er, r)
        self.assertEqual((text, raw), (HOME_TEXT, RAW_TEXT))

    def test_inherits_home_facts_keeps_own_gate_fact(self):
        promoted = {HOME_ID, P1_ID}
        sweeps = {"l4_modules": {HOME_ID: {"module": "m"}}}      # only the home is in a certified module
        res = {}
        for rid in (HOME_ID, P1_ID, P2_ID):
            er, text, raw = L.row_view(self.by[rid], self.by, self.root)
            res[rid] = L.evaluate_row(er, text, raw, promoted, sweeps, {})
        for rid in (P1_ID, P2_ID):                                # text facts equal the home's
            for k in ("records", "pins_left", "m2c_field", "blocking", "tail_jumps"):
                self.assertEqual(res[rid][k], res[HOME_ID][k], k)
        self.assertEqual(res[HOME_ID]["records"], ["Rec_Foo"])
        self.assertNotIn("not_in_module", res[HOME_ID]["l4_residue"])
        self.assertIn("not_in_module", res[P1_ID]["l4_residue"])  # its own module fact
        self.assertEqual(res[HOME_ID]["level"], 5)                # promoted, text != raw, in a module
        self.assertEqual(res[P1_ID]["level"], 3)                  # own promotion, but not in a module itself
        self.assertEqual(res[P2_ID]["level"], 2)                  # not promoted: own fact, not the home's


    def test_unchanged_home_does_not_promote_its_placement(self):
        (self.root / "raw/dungeon/func_80F8A664.c").write_text(HOME_TEXT)      # home text == pinned raw: L2
        res = {}
        for rid in (HOME_ID, P1_ID):
            er, text, raw = L.row_view(self.by[rid], self.by, self.root)
            res[rid] = L.evaluate_row(er, text, raw, {HOME_ID, P1_ID}, {}, {})["level"]
        # raw_text "" (the placement has no raw) would read as text != raw_text and mis-score the placement at L3
        self.assertEqual(res, {HOME_ID: 2, P1_ID: 2})


    def test_placement_uses_home_fidelity_records(self):
        self.patched(L, _FID=({HOME_ID}, {HOME_ID: {"maspsx_pass"}}))   # only the home has fingerprint/dependence records
        for r in self.by.values():
            r["cfg"] = "2.6.3 -G0 -O2"                    # a cell that does not split: cell_imitation applies
        promoted, sweeps = {HOME_ID, P1_ID}, {"l4_modules": {HOME_ID: {}, P1_ID: {}}}
        res = {}
        for rid in (HOME_ID, P1_ID):
            er, text, raw = L.row_view(self.by[rid], self.by, self.root)
            res[rid] = L.evaluate_row(er, text, raw, promoted, sweeps, {})
        for rid in (HOME_ID, P1_ID):
            self.assertIn("cell_imitation", res[rid]["l4_residue"])
            self.assertIn("maspsx_pass", res[rid]["l4_residue"])
            self.assertEqual(res[rid]["level"], 3)        # blocked at L4 although in a module
        self.assertEqual(res[P1_ID]["l5_fidelity"], ["maspsx_pass"])


class Status(Fixture):
    def test_placed_shapes_counts_placement_bytes_not_files(self):
        pinned = lambda c: c["pin_total"] > 0
        curc = {HOME_ID: {"pin_total": 2}, P1_ID: None, P2_ID: None}
        placed = S.placed_shapes(pinned, curc, self.by)
        self.assertEqual([r["id"] for r in placed], [P1_ID, P2_ID])
        clean_files = [self.by[i] for i, c in curc.items() if c and pinned(c)]
        self.assertEqual(len(clean_files), 1)                     # the TU is one file
        self.assertEqual(sum(r["size"] for r in clean_files + placed), 3 * 56)

    def test_placed_shapes_follows_the_home_predicate(self):
        curc = {HOME_ID: {"pin_total": 0}, P1_ID: None, P2_ID: None}
        self.assertEqual(S.placed_shapes(lambda c: c["pin_total"] > 0, curc, self.by), [])
        self.assertEqual(len(S.placed_shapes(lambda c: c["pin_total"] == 0, curc, self.by)), 2)
        self.patched(S, PARKED_CONTAINERS={"dungeon"})            # parked containers stay excluded
        self.assertEqual(S.placed_shapes(lambda c: True, curc, self.by), [])


class Census(Fixture):
    def test_placement_is_censused_under_its_home(self):
        self.patched(C, raw_path=lambda r: self.root / "raw" / r["container"] / (r["c_path"]))
        self.patched(C, layout_row_path=lambda r, root: self.root / "src/dungeon/func_80F8A664.c")
        self.patched(C, live_audit=lambda r, t: {})
        home = C.census_one(self.by[HOME_ID], {})
        self.assertNotIn("missing", home)
        self.assertEqual(home["pin_total"], 0)
        p = C.census_one(self.by[P1_ID], {})
        self.assertEqual(p, {"id": P1_ID, "missing": True, "source_row": HOME_ID})


class Lists(Fixture):
    def run_main(self, module, argv, **attrs):
        self.patched(module, **attrs)
        saved = sys.argv
        sys.argv = ["x"] + argv
        self.addCleanup(lambda: setattr(sys, "argv", saved))
        with contextlib.redirect_stdout(io.StringIO()):
            module.main()

    def test_campaign_rows_never_lists_a_placement(self):
        (self.root / "ledger/levels.jsonl").write_text("")
        site = {"PASSTHRU_NO_ARGS": 1}
        self.run_main(CR, ["--out", "out"], ROOT=self.root, LEDGER=self.root / "ledger", rows=lambda: self.rows,
                      layout_row_path=lambda r, root: self.root / "src/dungeon/func_80F8A664.c",
                      live_audit=lambda r, t: site)
        self.assertEqual((self.root / "out/fidelity_rows_small.txt").read_text(), HOME_ID + "\n")

    def test_decl_census_reads_the_tu_once(self):
        self.run_main(DC, ["--container", "dungeon", "--out", "out"], ROOT=self.root, rows=lambda: self.rows,
                      layout_row_path=lambda r, root: self.root / "src/dungeon/func_80F8A664.c")
        doc = json.loads((self.root / "out/dungeon.json").read_text())
        self.assertEqual(doc["data"]["D_80100000"]["types"], {"u32": [HOME_ID]})
        self.assertEqual(doc["functions"]["func_80F8A664"]["definition"]["row"], HOME_ID)

    def test_struct_census_counts_a_tu_once(self):
        self.run_main(SC, [], LEDGER=self.root / "ledger", rows=lambda: self.rows,
                      layout_row_path=lambda r, root: self.root / "src/dungeon/func_80F8A664.c")
        doc = json.loads((self.root / "ledger/struct_census.json").read_text())
        self.assertEqual(doc["structs"], 1)


if __name__ == "__main__":
    unittest.main()
