"""apply_names --batch: a batch that fails verification leaves ledger/names.jsonl untouched."""
import contextlib
import io
import json
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
import apply_names as N  # noqa: E402
import verify_batch  # noqa: E402


class JournalAtomicity(unittest.TestCase):
    def setup(self, td):
        r = Path(td)
        for d in ['config', 'ledger', 'include', 'src/town']:
            (r / d).mkdir(parents=True)
        names = r / 'config/names.tsv'
        names.write_text('# aliases\n')
        source = r / 'src/town/home.c'
        source.write_text('int func_80000000(void){return 1;}\n')
        journal = r / 'ledger/names.jsonl'
        journal.write_text('{"addr":"0x1","old":"a","new":"b","outcome":"applied"}\n')
        proposal = r / 'p.tsv'
        proposal.write_text('0x80000000\tfunc_80000000\treadable\tevidence\n')
        identity = r / 'identity.json'
        identity.write_text(json.dumps({'func_80000000': {'row': 'town/home', 'symbol': 'func_80000000'}}))
        rows = [dict(id='town/home', func='func_80000000', container='town', c_path='home.c')]
        argv = ['apply_names.py', str(proposal), '--batch', '--identity-map', str(identity)]
        return r, names, source, journal, rows, argv

    def run_main(self, r, names, rows, argv, measure):
        err = io.StringIO()
        with patch.multiple(N, ROOT=r, NAMES=names, JOURNAL=r / 'ledger/names.jsonl', INCLUDE=r / 'include'), \
                patch.object(N, 'rows', return_value=rows), patch.object(sys, 'argv', argv), \
                patch.object(verify_batch, 'measure', measure), \
                patch.object(verify_batch, 'context', lambda root: {}), \
                contextlib.redirect_stdout(io.StringIO()), contextlib.redirect_stderr(err):
            try:
                N.main()
            finally:
                self.err = err.getvalue()

    def test_failed_verification_leaves_the_journal_untouched(self):
        with tempfile.TemporaryDirectory() as td:
            r, names, source, journal, rows, argv = self.setup(td)
            before = {p: p.read_bytes() for p in (names, source, journal)}
            fail = lambda rows_, workers, verify, root: iter([(rows_[0]['id'], {'exact': False, 'status': 'mismatch'})])
            with self.assertRaises(ValueError):
                self.run_main(r, names, rows, argv, fail)
            self.assertEqual(before, {p: p.read_bytes() for p in before})
            self.assertIn('names journal NOT written', self.err)
            self.assertEqual([p.name for p in r.glob('ledger/.*')], [], 'no temp file left behind')

    def test_exact_batch_journals_once_atomically(self):
        with tempfile.TemporaryDirectory() as td:
            r, names, source, journal, rows, argv = self.setup(td)
            ok = lambda rows_, workers, verify, root: iter([(rows_[0]['id'], {'exact': True})])
            self.run_main(r, names, rows, argv, ok)
            lines = journal.read_text().splitlines()
            self.assertEqual(len(lines), 2)
            self.assertEqual(json.loads(lines[1])['outcome'], 'applied')
            self.assertIn('int readable(void)', source.read_text())


if __name__ == '__main__':
    unittest.main()
