"""Focused checks for the public bridge ledger's literal-site contract."""
import json
from pathlib import Path
import tempfile
import unittest

from bridge_check import check_bridges


class BridgeCheckTests(unittest.TestCase):
    def test_open_cast_must_remain_in_its_function(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / 'src/test.c'
            source.parent.mkdir()
            source.write_text('void first(void *p) { use((u8 *)p); use((u8 *)p); }\n'
                              'void second(void *p) { use((u8 *)p); }\n')
            ledger = root / 'bridges.jsonl'
            row = dict(site_id='site-1', file='src/test.c', function='first',
                       cast_text='(u8 *)p', ordinal=2, reason='legacy byte access',
                       evidence='source read', status='open', retired_by='')
            ledger.write_text(json.dumps(row) + '\n')
            self.assertEqual(check_bridges(root, ledger)[1], [])
            source.write_text('void first(void *p) { use(p); }\n'
                              'void second(void *p) { use((u8 *)p); }\n')
            self.assertIn('cast absent in function', check_bridges(root, ledger)[1][0])
            row.update(status='retired', reason='Literal cast removed in source edit')
            ledger.write_text(json.dumps(row) + '\n')
            self.assertEqual(check_bridges(root, ledger)[1], [])

    def test_duplicate_site_ids_are_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            row = dict(site_id='site-1', file='src/test.c', function='first',
                       cast_text='(u8 *)p', ordinal=1, reason='historical only',
                       evidence='', status='retired', retired_by='')
            ledger = root / 'bridges.jsonl'
            ledger.write_text((json.dumps(row) + '\n') * 2)
            self.assertIn('duplicate', check_bridges(root, ledger)[1][0])
