"""Refreshing an older baseline must preserve later TU installs and retirements."""
import contextlib
import hashlib
import io
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

from tools.typing import refresh_layout_inline as R


class RefreshRosterTests(unittest.TestCase):
    def test_preserves_new_records_and_skips_retired_records(self):
        old = b'int f(void) { return 1; }\n'
        prefix = b'/* shared declarations */\n'
        record = dict(member_id='town/f', tu_new='src/town/f.c', offset=0,
                      inlined_bytes=len(old), bytes=len(old), original_includes=[],
                      source_sha256=hashlib.sha256(old).hexdigest())
        retired = dict(record, member_id='town/retired', tu_new='src/town/retired.c')
        added = dict(record, member_id='town/new', tu_new='src/town/new.c')
        baseline = ''.join(json.dumps(r) + '\n' for r in [record, retired]).encode()
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'ledger').mkdir()
            (root / 'src/town').mkdir(parents=True)
            (root / 'src/town/f.c').write_bytes(prefix + old)
            ledger = root / R.LEDGER
            ledger.write_text(''.join(json.dumps(r) + '\n' for r in [record, added]))

            def show(_root, _rev, rel):
                return baseline if rel == R.LEDGER else old

            args = ['refresh_layout_inline', '--root', str(root), '--base', 'pristine']
            with patch.object(R, 'git_show', side_effect=show), patch('sys.argv', args), contextlib.redirect_stdout(io.StringIO()):
                self.assertEqual(R.main(), 0)
                records = [json.loads(line) for line in ledger.read_text().splitlines()]
                self.assertEqual(records[0]['offset'], len(prefix))
                self.assertEqual(records[1], added)
                first = ledger.read_bytes()
                self.assertEqual(R.main(), 0)
                self.assertEqual(ledger.read_bytes(), first)
                with patch('sys.argv', args + ['--check']):
                    self.assertEqual(R.main(), 0)


if __name__ == '__main__':
    unittest.main()
