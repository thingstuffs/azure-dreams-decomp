"""The probe stays bounded and never promotes an exact candidate."""
import tempfile
import unittest
from pathlib import Path
from unittest import mock
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import aggregate_copy_probe as P


ROW = {"id": "town/test", "cfg": "2.7.2-cdk-G0", "cell": "2.7.2-cdk",
       "flags": "-G0", "c_path": "overlays/town/test.c", "container": "town"}


class ProbeBoundaries(unittest.TestCase):
    def manifest(self, source, cells=None):
        return {"schema": 1, "rows": [{"id": "town/test", "source": str(source),
                                         "cells": cells or [ROW["cfg"]]}]}

    def test_requires_recorded_recipe_explicitly(self):
        with tempfile.TemporaryDirectory(dir=ROOT) as td:
            source = Path(td) / "a.c"; source.write_text("void f(void) {}\n")
            with self.assertRaisesRegex(ValueError, "recorded recipe"):
                P.validate_manifest(self.manifest(source, ["2.8.1-G0"]), {ROW["id"]: ROW})

    def test_five_row_bound_is_checked_before_verification(self):
        with tempfile.TemporaryDirectory(dir=ROOT) as td:
            source = Path(td) / "a.c"; source.write_text("void f(void) {}\n")
            m = {"schema": 1, "rows": [{"id": "r%d" % i, "source": str(source),
                                           "cells": [ROW["cfg"]]} for i in range(6)]}
            with self.assertRaisesRegex(ValueError, "1..5"):
                P.validate_manifest(m, {})

    def test_exact_candidate_remains_unreviewed_and_unpromoted(self):
        source_text = ('#include "common.h"\n'
                       'typedef struct { s32 w[4]; } Block;\n'
                       'void f(Block *src, Block *dst) {\nBlock *end = src + 1;\n'
                       'do { *dst++ = *src++; } while (src != end);\n}\n')
        with tempfile.TemporaryDirectory(dir=ROOT) as td:
            root = Path(td); source = root / "base.c"; source.write_text(source_text)
            live = root / "live.c"; live.write_text(source_text)
            def fake_verify(row, path, include_root=None):
                candidate = "do {" not in Path(path).read_text()
                return {"exact": candidate, "status": "ok", "total": 0 if candidate else 1}
            with mock.patch.object(P, "clean_path", return_value=live):
                report = P.probe(self.manifest(source), root / "lane", {ROW["id"]: ROW}, fake_verify)
            cand = report["rows"][0]["candidates"][0]
            self.assertTrue(cand["scores"][ROW["cfg"]]["exact"])
            self.assertEqual(cand["review_state"], "unreviewed")
            self.assertTrue(cand["review_required"])
            self.assertEqual(cand["promotion"], "not_performed")
            self.assertEqual(report["promotion"], "not_performed")
            self.assertTrue(report["rows"][0]["live_source_matches_input"])
            self.assertFalse(report["rows"][0]["promotion_eligible"])

    def test_existing_output_lane_is_refused(self):
        with tempfile.TemporaryDirectory(dir=ROOT) as td:
            root = Path(td); source = root / "a.c"; source.write_text("void f(void) {}\n")
            with self.assertRaisesRegex(ValueError, "must not already exist"):
                P.probe(self.manifest(source), root, {ROW["id"]: ROW}, lambda *a, **k: {})

    def test_cell_switch_control_requires_exact_recorded_baseline(self):
        source_text = ('#include "common.h"\n'
                       'typedef struct { s32 w[4]; } Block;\n'
                       'void f(Block *src, Block *dst) {\nBlock *end = src + 1;\n'
                       'do { *dst++ = *src++; } while (src != end);\n}\n')
        alternate = "2.8.1-G0"
        with tempfile.TemporaryDirectory(dir=ROOT) as td:
            root = Path(td); source = root / "base.c"; source.write_text(source_text)
            live = root / "live.c"; live.write_text(source_text)

            def fake_verify(row, path, include_root=None):
                candidate = "do {" not in Path(path).read_text()
                exact = row["cfg"] == alternate or candidate
                if row["cfg"] == ROW["cfg"] and not candidate:
                    exact = False
                if row["cfg"] == ROW["cfg"] and candidate:
                    exact = False
                return {"exact": exact, "status": "ok", "total": 0 if exact else 1}

            with mock.patch.object(P, "clean_path", return_value=live):
                report = P.probe(self.manifest(source, [ROW["cfg"], alternate]),
                                 root / "lane", {ROW["id"]: ROW}, fake_verify)
            controls = report["rows"][0]["candidates"][0]["byte_controls"]
            self.assertTrue(controls[alternate]["baseline_exact_at_selected_cell"])
            self.assertTrue(controls[alternate]["candidate_exact_at_selected_cell"])
            self.assertFalse(controls[alternate]["standard_cell_switch_controls_pass"])


if __name__ == "__main__":
    unittest.main()
