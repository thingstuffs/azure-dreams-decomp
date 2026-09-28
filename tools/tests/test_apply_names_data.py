"""The data alias path runs entirely against a temporary source/config tree."""
import contextlib
import io
import json
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import apply_names as names  # noqa: E402


class DataNamesTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        for sub in ("config", "include", "ledger", "src/town"):
            (self.root / sub).mkdir(parents=True)
        self.table = self.root / "config/names.tsv"
        self.table.write_text("# aliases\n")
        self.journal = self.root / "ledger/names.jsonl"
        self.source = self.root / "src/town/func_80000000.c"
        self.source.write_text("extern int D_80001234;\nint func_80000000(void) { return D_80001234; }\n")
        self.proposed = self.root / "proposed.tsv"
        self.proposed.write_text("0x80001234\tD_80001234\treadableData\tevidence\n")
        self.row = {"id": "town/func_80000000", "container": "town",
                    "func": "func_80000000", "c_path": str(self.source)}

    def run_names(self, *args, verdict=True):
        verified = []

        def check(row, path, include_root=None):
            verified.append((row["id"], Path(path), include_root))
            return {"exact": verdict, "status": "ok", "total": 0 if verdict else 1}

        with mock.patch.object(names, "ROOT", self.root), \
             mock.patch.object(names, "NAMES", self.table), \
             mock.patch.object(names, "INCLUDE", self.root / "include"), \
             mock.patch.object(names, "JOURNAL", self.journal), \
             mock.patch.object(names, "rows", return_value=[self.row]), \
             mock.patch.object(names, "verify", side_effect=check), \
             mock.patch.object(sys, "argv", ["apply_names.py", str(self.proposed), "--data", *args]), \
             contextlib.redirect_stdout(io.StringIO()):
            names.main()
        return verified

    def test_data_alias_appends_without_rewrite(self):
        before = self.source.read_text()
        self.assertEqual(self.run_names(), [])
        self.assertIn("D_80001234\treadableData\tevidence", self.table.read_text())
        self.assertEqual(self.source.read_text(), before)

    def test_rewrite_verifies_each_touched_row(self):
        verified = self.run_names("--rewrite")
        self.assertEqual(verified, [(self.row["id"], self.source, self.root / "include")])
        self.assertIn("return readableData;", self.source.read_text())
        self.assertNotIn("D_80001234", self.source.read_text())

    def test_failed_verification_reverts_source_and_alias(self):
        before = self.source.read_text()
        self.run_names("--rewrite", verdict=False)
        self.assertEqual(self.source.read_text(), before)
        self.assertNotIn("readableData", self.table.read_text())
        self.assertEqual(json.loads(self.journal.read_text())["outcome"], "reverted")

    def test_collision_and_mismatched_address_are_refused(self):
        self.table.write_text("0x80005678\tD_80005678\treadableData\tfirst\n")
        self.run_names("--rewrite")
        self.assertEqual(len(self.table.read_text().splitlines()), 1)
        self.proposed.write_text("0x80005678\tD_80001234\totherData\tevidence\n")
        self.run_names("--rewrite")
        self.assertEqual(len(self.table.read_text().splitlines()), 1)
        self.assertIn("D_80001234", self.source.read_text())

    def test_identifier_used_in_source_is_refused(self):
        self.source.write_text("int alreadyUsed;\n" + self.source.read_text())
        self.proposed.write_text("0x80001234\tD_80001234\talreadyUsed\tevidence\n")
        self.assertEqual(self.run_names("--rewrite"), [])
        self.assertNotIn("alreadyUsed\tevidence", self.table.read_text())
        self.assertIn("D_80001234", self.source.read_text())


if __name__ == "__main__":
    unittest.main()
