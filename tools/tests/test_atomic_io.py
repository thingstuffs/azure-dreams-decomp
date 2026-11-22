"""atomic_io: the target is the old file or the new one, never a truncated mix."""
import os
import stat
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import atomic_io as A  # noqa: E402


class AtomicWrite(unittest.TestCase):
    def setUp(self):
        self.d = Path(tempfile.mkdtemp())
        self.addCleanup(__import__('shutil').rmtree, self.d, True)
        self.f = self.d / 'rows.jsonl'

    def leftovers(self):
        return sorted(p.name for p in self.d.iterdir() if p.name.endswith('.tmp'))

    def test_creates_and_replaces(self):
        A.write_text(self.f, 'a\n'); self.assertEqual(self.f.read_text(), 'a\n')
        A.write_text(self.f, 'b\n'); self.assertEqual(self.f.read_text(), 'b\n')
        A.write_bytes(self.f, b'\x00\xff'); self.assertEqual(self.f.read_bytes(), b'\x00\xff')
        self.assertEqual(self.leftovers(), [])

    def test_failure_keeps_old_content_and_removes_temp(self):
        self.f.write_text('old\n')
        with mock.patch('os.replace', side_effect=OSError('disk full')), self.assertRaises(OSError):
            A.write_text(self.f, 'new\n')
        self.assertEqual(self.f.read_text(), 'old\n'); self.assertEqual(self.leftovers(), [])

    def test_failure_while_writing_keeps_old_content(self):
        self.f.write_text('old\n')
        with mock.patch('os.fsync', side_effect=OSError('io')), self.assertRaises(OSError):
            A.write_text(self.f, 'new\n')
        self.assertEqual(self.f.read_text(), 'old\n'); self.assertEqual(self.leftovers(), [])

    def test_mode_preserved_and_symlink_followed(self):
        real = self.d / 'real.tsv'; real.write_text('x'); os.chmod(real, 0o640)
        link = self.d / 'names.tsv'; link.symlink_to(real)
        A.write_text(link, 'y')
        self.assertTrue(link.is_symlink()); self.assertEqual(real.read_text(), 'y')
        self.assertEqual(stat.S_IMODE(real.stat().st_mode), 0o640)

    def test_encoding_errors_passthrough(self):
        A.write_text(self.f, 'caf\udcff', errors='surrogateescape'); self.assertEqual(self.f.read_bytes(), b'caf\xff')


if __name__ == '__main__':
    unittest.main()
