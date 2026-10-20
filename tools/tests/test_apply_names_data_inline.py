"""Data aliases preserve merged-TU member ranges and atomic staging."""
import contextlib
import hashlib
import io
import json
from pathlib import Path
import re
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import apply_names_data as D
from source_layout import _fragment

OLD = 'D_80000000'
NEW = 'runtime_control_word'

class InlineDataStaging(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        root = self.root = Path(self.temp.name)
        for name in ('src/slus', 'include', 'config', 'ledger'):
            (root / name).mkdir(parents=True, exist_ok=True)
        self.source = root / 'src/slus/merged.c'
        self.index = root / 'ledger/layout_inline.jsonl'
        first = '#include "shared/fragment.h"\nextern int D_80000000;\nint first(void) { return D_80000000; }\n'
        second = '#include "shared/fragment.h"\nint second(void) { return 2; }'
        prefix = '/* caf\u00e9: merged wrapper */\n'.encode()
        data = prefix
        records = []
        for order, piece in enumerate((first, second)):
            original = piece.replace('shared/fragment.h', 'fragment.h').encode()
            inlined = piece.encode() + (b'' if piece.endswith('\n') else b'\n')
            records.append(dict(tu_old='src/slus/old.c', tu_new='src/slus/merged.c',
                member=f'src/slus/member_{order}.c', member_id=f'slus/member_{order}',
                manifest_key='test', order=order, offset=len(data), bytes=len(original),
                inlined_bytes=len(inlined), source_sha256=hashlib.sha256(original).hexdigest(),
                original_includes=['fragment.h']))
            data += inlined
        self.source.write_bytes(data)
        self.records = records
        self.index.write_text(''.join(json.dumps(r, separators=(',', ':'))+'\n' for r in records))
        self.names = root / 'config/names.tsv'
        self.names.write_text('# aliases\n')
        self.journal = root / 'ledger/names.jsonl'
        self.journal.write_text('{"prior":true}\n')
        self.proposal = root / 'map.tsv'
        self.proposal.write_text('symbol\tcontainer\tnew_name\tevidence\tconsumers\n'
            + OLD+'\tslus/test\t'+NEW+'\ttyped control-word reader\t1\n')
        def read_names():
            return [line.split('\t') for line in self.names.read_text().splitlines()
                    if line and not line.startswith('#')]
        def append(path, record):
            with path.open('a') as f:
                f.write(json.dumps(record)+'\n')
        self.workflow = SimpleNamespace(ROOT=root, NAMES=self.names, JOURNAL=self.journal,
            DATA_NAME=re.compile(r'D_[0-9A-Fa-f]{8}'), read_names=read_names, append_jsonl=append)
        self.args = SimpleNamespace(tsv=self.proposal, only=None, limit=None,
            rewrite=True, defer_verification=True, dry_run=False, proof_log=None)

    def run_stage(self):
        with contextlib.redirect_stdout(io.StringIO()):
            return D.main(self.args, self.workflow)

    def snapshot(self):
        return {p: p.read_bytes() for p in (self.source, self.index, self.names, self.journal)}

    def test_same_members_after_different_length_name(self):
        original = self.source.read_bytes()
        plan = self.run_stage()
        records = [json.loads(line) for line in self.index.read_text().splitlines()]
        self.assertEqual(plan['status'], 'UNVERIFIED')
        self.assertEqual(plan['new_aliases'], 1)
        self.assertEqual(len(plan['metadata_files']), 1)
        self.assertEqual(len(plan['inline_rebases']), 2)
        current = self.source.read_bytes()
        self.assertEqual(current, original.replace(OLD.encode(), NEW.encode()))
        # The actual accounting reader must still return the same second
        # member even though the first member grew in bytes.
        self.assertEqual(_fragment(current, records[1]), _fragment(original, self.records[1]))
        self.assertNotEqual(records[1]['offset'], self.records[1]['offset'])
        self.assertEqual(records[1]['source_sha256'], self.records[1]['source_sha256'])
        first = _fragment(current, records[0]).replace(b'shared/fragment.h', b'fragment.h')
        self.assertEqual(hashlib.sha256(first).hexdigest(), records[0]['source_sha256'])
        for old, new in zip(self.records, records):
            for key in old.keys() - {'offset', 'inlined_bytes', 'bytes', 'source_sha256'}:
                self.assertEqual(old[key], new[key])

    def test_second_stage_is_idempotent(self):
        self.run_stage()
        before = self.snapshot()
        result = self.run_stage()
        self.assertEqual(result['new_aliases'], 0)
        self.assertEqual(result['files'], [])
        self.assertEqual(result['metadata_files'], [])
        self.assertEqual(self.snapshot(), before)

    def test_stale_original_hash_refuses_before_writes(self):
        self.records[0]['source_sha256'] = '0'*64
        self.index.write_text(''.join(json.dumps(r)+'\n' for r in self.records))
        before = self.snapshot()
        with self.assertRaisesRegex(ValueError, 'stale inline original hash'):
            self.run_stage()
        self.assertEqual(self.snapshot(), before)

    def test_stale_boundary_refuses_before_writes(self):
        self.records[0]['offset'] += 1
        self.index.write_text(''.join(json.dumps(r)+'\n' for r in self.records))
        before = self.snapshot()
        with self.assertRaisesRegex(ValueError, 'stale inline line boundary'):
            self.run_stage()
        self.assertEqual(self.snapshot(), before)

    def test_extra_fragment_edit_refuses(self):
        old = self.source.read_text()
        after = old.replace(OLD, NEW).replace('return 2', 'return 3')
        with self.assertRaisesRegex(ValueError, 'beyond the spelling map'):
            D.inline_plan(self.root, {self.source: old}, {self.source: after},
                re.compile(r'\b'+OLD+r'\b'), {OLD: NEW})

    def test_metadata_write_failure_rolls_back_whole_batch(self):
        before = self.snapshot()
        write = Path.write_bytes
        failed = False
        def reject_once(path, data):
            nonlocal failed
            if path == self.index and not failed:
                failed = True
                raise OSError('simulated metadata failure')
            return write(path, data)
        with patch.object(Path, 'write_bytes', reject_once):
            with self.assertRaisesRegex(OSError, 'simulated metadata failure'):
                self.run_stage()
        self.assertTrue(failed)
        self.assertEqual(self.snapshot(), before)

if __name__ == '__main__':
    unittest.main()
