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
    def test_reverted_tu_restores_baseline_extents(self):
        old = b'int f(void) { return 1; }\n'
        record = dict(member_id='town/f', tu_new='src/town/f.c', offset=0,
                      inlined_bytes=len(old), bytes=len(old), original_includes=[],
                      source_sha256=hashlib.sha256(old).hexdigest())
        stale = dict(record, offset=19, source_sha256='reverted experiment')
        baseline = (json.dumps(record) + '\n').encode()
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'ledger').mkdir()
            (root / 'src/town').mkdir(parents=True)
            (root / 'src/town/f.c').write_bytes(old)
            ledger = root / R.LEDGER
            ledger.write_text(json.dumps(stale) + '\n')
            def show(_root, _rev, rel):
                return baseline if rel == R.LEDGER else old
            args = ['refresh_layout_inline', '--root', str(root), '--base', 'pristine']
            with patch.object(R, 'git_show', side_effect=show), patch('sys.argv', args), contextlib.redirect_stdout(io.StringIO()):
                self.assertEqual(R.main(), 0)
                self.assertEqual(json.loads(ledger.read_text()), record)
                with patch('sys.argv', args + ['--check']):
                    self.assertEqual(R.main(), 0)

    def test_tu_renamed_after_its_function_is_refreshed_from_its_old_path(self):
        old = b'int f(void) { return 1; }\n'
        prefix = b'/* renamed callee declarations */\n'
        record = dict(member_id='town/f', tu_new='src/town/old_name.c', offset=0,
                      inlined_bytes=len(old), bytes=len(old), original_includes=[],
                      source_sha256=hashlib.sha256(old).hexdigest())
        baseline = (json.dumps(record) + '\n').encode()
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'ledger').mkdir()
            (root / 'src/town').mkdir(parents=True)
            (root / 'src/town/new_name.c').write_bytes(prefix + old)
            ledger = root / R.LEDGER
            ledger.write_text(json.dumps(dict(record, tu_new='src/town/new_name.c')) + '\n')

            def show(_root, _rev, rel):
                if rel == R.LEDGER:
                    return baseline
                if rel == 'src/town/old_name.c':
                    return old
                raise R.subprocess.CalledProcessError(128, 'git show')

            args = ['refresh_layout_inline', '--root', str(root), '--base', 'pristine']
            with patch.object(R, 'git_show', side_effect=show), patch('sys.argv', args), \
                    patch.object(R, 'history', return_value=[]), contextlib.redirect_stdout(io.StringIO()):
                self.assertEqual(R.main(), 0)
            out = json.loads(ledger.read_text())
            self.assertEqual(out['tu_new'], 'src/town/new_name.c')
            self.assertEqual(out['offset'], len(prefix))
            self.assertTrue(R.verifies(out, prefix + old))

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


def _git(root, *args):
    import subprocess
    return subprocess.run(['git', '-C', str(root), *args], check=True, capture_output=True, text=True).stdout.strip()


class LaneBatchTests(unittest.TestCase):
    """A lane commits batch 1's sources without the refreshed ledger, then refreshes batch 2 against that commit
    (the r137w_rtwl5_dungeon batch 2 KeyError).  Real git repository; no mocks."""

    PREFIX = b'/* merged */\n'
    M1 = b'int f(void) {\n    return 1;\n}\n'
    M2 = b'#include "a.h"\nint g(void) {\n    return 2;\n}\n'

    def records(self, tu, m1, m2, prefix=PREFIX):
        r1 = dict(member_id='town/f', tu_new=tu, offset=len(prefix), inlined_bytes=len(m1), bytes=len(m1),
                  original_includes=[], source_sha256=hashlib.sha256(m1).hexdigest())
        restored = m2.replace(b'"a.h"', b'"old/a.h"')
        r2 = dict(member_id='town/g', tu_new=tu, offset=len(prefix) + len(m1), inlined_bytes=len(m2),
                  bytes=len(restored), original_includes=['old/a.h'], source_sha256=hashlib.sha256(restored).hexdigest())
        return [r1, r2]

    def setUp(self):
        self.td = tempfile.TemporaryDirectory()
        self.root = root = Path(self.td.name)
        _git(root, 'init', '-q')
        _git(root, 'config', 'user.email', 'lane')
        _git(root, 'config', 'user.name', 'lane')
        (root / 'ledger').mkdir()
        (root / 'src/town').mkdir(parents=True)
        self.tus = ['src/town/one.c', 'src/town/two.c']
        recs = []
        for tu in self.tus:
            (root / tu).write_bytes(self.PREFIX + self.M1 + self.M2)
            recs += self.records(tu, self.M1, self.M2)
        self.write_ledger(recs)
        _git(root, 'add', '-A')
        _git(root, 'commit', '-qm', 'base')
        self.base = _git(root, 'rev-parse', 'HEAD')

    def tearDown(self):
        self.td.cleanup()

    def write_ledger(self, recs):
        (self.root / R.LEDGER).write_text(''.join(json.dumps(r, separators=(',', ':')) + '\n' for r in recs))

    def ledger(self):
        return [json.loads(line) for line in (self.root / R.LEDGER).read_text().splitlines()]

    def run_refresh(self, base, *extra):
        args = ['refresh_layout_inline', '--root', str(self.root), '--base', base, *extra]
        out = io.StringIO()
        with patch('sys.argv', args), contextlib.redirect_stdout(out), contextlib.redirect_stderr(out):
            code = R.main()
        return code, out.getvalue()

    def assert_fresh(self):
        for r in self.ledger():
            text = (self.root / r['tu_new']).read_bytes()
            self.assertTrue(R.verifies(r, text), r)

    def test_batch_committed_without_ledger(self):
        root = self.root
        # batch 1: both TUs edited inside f, ledger refreshed, only src committed
        m1b = b'int f(void) {\n    int x = 1;\n    return x;\n}\n'
        for tu in self.tus:
            (root / tu).write_bytes(self.PREFIX + m1b + self.M2)
        self.assertEqual(self.run_refresh(self.base)[0], 0)
        self.assert_fresh()
        _git(root, 'add', 'src')
        _git(root, 'commit', '-qm', 'batch 1 (sources only)')
        batch1 = _git(root, 'rev-parse', 'HEAD')
        self.assertEqual(R.stale_records(root, batch1), {(m, tu) for tu in self.tus for m in ('town/f', 'town/g')})
        # batch 2 edits one.c again (the stale extent used to raise KeyError here); two.c is untouched
        m1c = b'int f(void) {\n    int x = 1;\n    x += 2;\n    return x;\n}\n'
        (root / self.tus[0]).write_bytes(self.PREFIX + m1c + self.M2)
        code, out = self.run_refresh(batch1)
        self.assertEqual(code, 0, out)
        self.assertIn('healed', out)
        self.assert_fresh()
        one = [r for r in self.ledger() if r['tu_new'] == self.tus[0]]
        self.assertEqual((one[0]['inlined_bytes'], one[1]['offset']), (len(m1c), len(self.PREFIX) + len(m1c)))
        two = [r for r in self.ledger() if r['tu_new'] == self.tus[1]]
        self.assertEqual(two[1]['offset'], len(self.PREFIX) + len(m1b))   # batch-1 refresh kept, not reverted
        self.assertEqual(self.run_refresh(batch1, '--check')[0], 0)
        # affected.py: two.c's records differ from batch 1's committed ledger only as a repair
        import importlib.util
        spec = importlib.util.spec_from_file_location('affected', Path(R.__file__).resolve().parents[1] / 'build/affected.py')
        A = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(A)
        self.assertEqual(A.layout_inline_healed(root, batch1, [self.tus[1]]), [self.tus[1]])
        # ... but not when the text changed or the committed record was already right
        self.assertEqual(A.layout_inline_healed(root, self.base, [self.tus[1]]), [])

    def test_unverifiable_records_fail_clearly(self):
        bad = self.ledger()
        for r in bad:
            r['source_sha256'] = '0' * 64
        self.write_ledger(bad)
        _git(self.root, 'commit', '-qam', 'hand-edited ledger')
        (self.root / self.tus[0]).write_bytes(b'/* x */\n' + self.PREFIX + self.M1 + self.M2)
        code, out = self.run_refresh(_git(self.root, 'rev-parse', 'HEAD'))
        self.assertEqual(code, 2)
        self.assertIn('no ledger record set verifies', out)
        self.assertIn(self.tus[0], out)


if __name__ == '__main__':
    unittest.main()
