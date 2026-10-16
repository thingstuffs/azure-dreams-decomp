"""Pin evidence survives whole-file layout moves and historical HEAD paths."""
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import pin_evidence as evidence
from source_layout import row_relative, flat_relative

class MovedEvidenceTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        self.row = {"id":"town/func_1", "container":"town", "c_path":"raw/func_1.c"}
        (self.root / "ledger").mkdir()
        (self.root / "ledger/rows.jsonl").write_text(json.dumps(self.row) + "\n")
        self.rel = "src/town/module/func_1.c"
        (self.root / "ledger/layout.jsonl").write_text(json.dumps({"id":self.row["id"], "path":self.rel}) + "\n")
        self.path = self.root / self.rel
        self.path.parent.mkdir(parents=True)
        self.path.write_text("current evidence\n")
        self.patch = patch.object(evidence, "ROOT", self.root)
        self.patch.start()
        self.addCleanup(self.patch.stop)

    def read(self, text):
        return evidence._text_at(row_relative(self.row, self.root), evidence.sha_text(text), flat_relative(self.row))

    def test_current_moved_source_needs_no_git_lookup(self):
        with patch.object(evidence.subprocess, "run") as git:
            self.assertEqual(self.read("current evidence\n"), "current evidence\n")
            git.assert_not_called()

    def test_old_evidence_can_still_use_flat_head_path(self):
        old = "historical evidence\n"
        def show(argv, **kwargs):
            return subprocess.CompletedProcess(argv, 0 if argv[-1] == "HEAD:src/town/func_1.c" else 128,
                                               old if argv[-1] == "HEAD:src/town/func_1.c" else "", "")
        with patch.object(evidence.subprocess, "run", side_effect=show):
            self.assertEqual(self.read(old), old)

    def test_unrelated_head_text_is_never_adopted(self):
        with patch.object(evidence.subprocess, "run", return_value=subprocess.CompletedProcess([], 0, "wrong text", "")):
            self.assertIsNone(self.read("missing evidence\n"))

if __name__ == "__main__":
    unittest.main()
