"""The two-pass object receipt is keyed to the complete physical move map."""
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
import layout_compile_identity as I


class SnapshotTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        self.tree = self.root / 'tree.tsv'
        self.tree.write_text('current_path\tproposed_path\n'
                             'src/slus/old.c\tsrc/engine/new.c\n')
        old = self.root / 'src/slus/old.c'
        old.parent.mkdir(parents=True)
        old.write_text('int f(void) { return 1; }\n')
        self.recipe = {'kind': 'row', 'container': 'slus', 'cell': '2.7.2',
                       'flags': [], 'asflags': [], 'row_id': 'slus/old'}

    def fake(self, root, rel, recipe):
        return {'source': rel, 'kind': recipe['kind'], 'recipe': recipe,
                'raw_sha256': 'raw', 'canonical_assembly_sha256': 'assembly',
                'canonical_object_sha256': 'object'}

    def test_snapshot_then_compare_after_move(self):
        receipt = self.root / 'receipt.jsonl'
        with patch.object(I, 'recipes', return_value=({'src/slus/old.c': self.recipe}, set())), \
             patch.object(I, 'capture_one', side_effect=self.fake):
            self.assertEqual(I.run(self.root, self.tree, snapshot=receipt)['physical_tus'], 1)
        with patch.object(I, 'recipes', return_value=({'src/slus/old.c': self.recipe}, set())):
            with self.assertRaisesRegex(ValueError, 'post-move physical TU'):
                I.run(self.root, self.tree, compare=receipt)
        (self.root / 'src/engine').mkdir()
        (self.root / 'src/slus/old.c').rename(self.root / 'src/engine/new.c')
        with patch.object(I, 'recipes', return_value=({'src/engine/new.c': self.recipe}, set())), \
             patch.object(I, 'capture_one', side_effect=self.fake):
            result = I.run(self.root, self.tree, compare=receipt)
        self.assertEqual(result['canonical_equal'], 1)
        self.assertEqual(result['raw_equal'], 1)
        self.assertEqual(json.loads(receipt.read_text())['old'], 'src/slus/old.c')

    def test_nonhome_member_refused(self):
        with patch.object(I, 'recipes', return_value=({}, {'src/slus/old.c'})):
            with self.assertRaisesRegex(ValueError, 'non-home native member'):
                I.run(self.root, self.tree, snapshot=self.root / 'receipt.jsonl')


if __name__ == '__main__':
    unittest.main()
