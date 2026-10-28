"""--ignore-local-labels accepts only label renumbering over equal objects."""
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / 'tools'), str(ROOT / 'tools/typing')]
import layout_compile_identity as L
import tu_identity as T


def record(raw='r', asm='a', obj='o', norm='n'):
    return {'source': 'src/x.c', 'raw_sha256': raw, 'canonical_assembly_sha256': asm,
            'canonical_object_sha256': obj, 'label_normalized_assembly_sha256': norm}


class LabelNormalizationTests(unittest.TestCase):
    def test_only_local_labels_are_renamed(self):
        stream = b'\tbeq\t$2,$0,$L12\n$L12:\n\tlw\t$2,%lo($L83)($2)\n\tjal\tfunc_L1\n\tli\t$L,1\n'
        self.assertEqual(L.normalize_local_labels(stream),
                         b'\tbeq\t$2,$0,$L\n$L:\n\tlw\t$2,%lo($L)($2)\n\tjal\tfunc_L1\n\tli\t$L,1\n')


class VerdictTests(unittest.TestCase):
    def test_exact_identity_is_accepted_without_the_flag(self):
        rec, ok = T.verdict(record(), record())
        self.assertTrue(ok)
        self.assertNotIn('label_only', rec)

    def test_label_only_needs_the_flag(self):
        before, after = record(), record(asm='a2')
        self.assertFalse(T.verdict(before, after)[1])
        rec, ok = T.verdict(before, after, ignore_local_labels=True)
        self.assertTrue(ok)
        self.assertTrue(rec['label_only'])

    def test_flag_still_requires_equal_objects(self):
        for after in (record(raw='r2', asm='a2'), record(obj='o2', asm='a2'),
                      record(asm='a2', norm='n2')):
            self.assertFalse(T.verdict(record(), after, ignore_local_labels=True)[1])

    def test_old_receipt_without_normalized_hash_is_refused(self):
        before = record()
        del before['label_normalized_assembly_sha256']
        rec, ok = T.verdict(before, record(asm='a2'), ignore_local_labels=True)
        self.assertFalse(ok)
        self.assertIn('retake the snapshot', rec['error'])


if __name__ == '__main__':
    unittest.main()
