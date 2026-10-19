"""Object identity excludes only GCC source-file records."""
import sys
from pathlib import Path
import unittest
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
from layout_identity import canonical


class IdentityTest(unittest.TestCase):
    def test_file_directives_only(self):
        before = b'\t.file\t1 "old.c"\n\t.text\n\t.file\t2 "member.c"\nlabel:\n\tnop\n'
        after = b'\t.file\t1 "new.c"\n\t.text\nlabel:\n\tnop\n'
        self.assertEqual(canonical(before), canonical(after))
        self.assertNotEqual(canonical(before), canonical(after.replace(b'nop', b'jr $ra')))


if __name__ == '__main__':
    unittest.main()
