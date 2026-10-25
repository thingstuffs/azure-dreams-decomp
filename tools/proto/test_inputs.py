"""A missing proposal map must never produce a successful empty proof."""
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class InputTests(unittest.TestCase):
    def test_missing_transaction_map_is_refused(self):
        self.refused('transaction.py', ['--manual', 'missing.tsv'], '--manual')

    def test_missing_source_plan_is_refused(self):
        self.refused('probe_sources.py', ['--scope', 'src/town', '--plan', 'missing.tsv'], '--plan')

    def test_missing_header_plan_is_refused(self):
        self.refused('probe_headers.py', ['--scope', 'include/town', '--plan', 'missing.tsv'], '--plan')

    def test_empty_transaction_cannot_issue_a_proof(self):
        with tempfile.TemporaryDirectory(dir=ROOT / 'build_ovl') as tmp:
            manual = Path(tmp) / 'empty.tsv'
            manual.write_text('file\tfunction\tbefore\tafter\tevidence\n')
            output = Path(tmp) / 'proof'
            result = subprocess.run([sys.executable, str(ROOT / 'tools/proto/transaction.py'),
                '--manual', str(manual), '--out', str(output)], cwd=tmp, text=True, capture_output=True)
            self.assertNotEqual(result.returncode, 0)
            self.assertIn('transaction has no manual or declaration edits', result.stderr)
            self.assertFalse((output / 'proof.jsonl').exists())

    def refused(self, script, flags, option):
        with tempfile.TemporaryDirectory(dir=ROOT / 'build_ovl') as tmp:
            output = Path(tmp) / 'proof'
            result = subprocess.run([sys.executable, str(ROOT / 'tools/proto' / script),
                *flags, '--out', str(output)], cwd=tmp, text=True, capture_output=True)
            self.assertNotEqual(result.returncode, 0)
            self.assertIn(option + ' must name an existing', result.stderr)
            self.assertFalse(output.exists())


if __name__ == '__main__':
    unittest.main()
