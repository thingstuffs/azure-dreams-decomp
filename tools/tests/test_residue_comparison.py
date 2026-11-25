"""Residue rows carry a byte-equality claim: it must be recorded, and it must be true when the containers exist."""
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'lint'))
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import ledger_integrity as LI  # noqa: E402
import placed_copies  # noqa: E402


def row(**kw):
    base = dict(container='dungeon', foff=8, size=16, category='stale_town_copy', compare_container='town',
                compare_foff=8, words=4, equal_words=4)
    base.update(kw)
    return base


class ResidueComparison(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.root = Path(self.tmp.name)
        directory = self.root / placed_copies.CONTAINER_DIR
        directory.mkdir(parents=True)
        # invented bytes: the two containers agree on 0..40 and differ afterwards
        shared = bytes((i * 7 + 3) & 0xFF for i in range(40))
        self.write('dungeon', shared + b'\x01' * 24)
        self.write('town', shared + b'\x02' * 24)
        self.write('main', bytes(64))
        self.write('ovmovie', bytes(64))

    def tearDown(self):
        self.tmp.cleanup()

    def write(self, name, data):
        (self.root / placed_copies.CONTAINER_DIR / placed_copies.CONTAINERS[name]).write_bytes(data)

    def check(self, *rows):
        return LI.residue_comparison_problems(self.root, regions=list(rows))

    def test_a_true_record_passes(self):
        rows, compared, problems = self.check(row())
        self.assertEqual((rows, compared, problems), (1, 1, []))

    def test_a_false_compare_fails(self):
        _, compared, problems = self.check(row(foff=32, compare_foff=32))
        self.assertEqual(compared, 1)
        self.assertEqual(len(problems), 1)
        self.assertIn('differs', problems[0])

    def test_a_record_without_comparison_fields_fails(self):
        for category in ('stale_town_copy', 'foreign_program_fragment'):
            bare = {'container': 'dungeon', 'foff': 8, 'size': 16, 'category': category}
            _, compared, problems = self.check(bare)
            self.assertEqual(compared, 0)
            self.assertEqual(len(problems), 1)
            self.assertIn('missing compare_container, compare_foff, words', problems[0])

    def test_equal_words_must_equal_words(self):
        _, _, problems = self.check(row(equal_words=3))
        self.assertEqual(len(problems), 1)

    def test_a_formatter_copy_compares_with_its_first_copy(self):
        first = row(category='formatter_remnant', compare_container='dungeon', compare_foff=0, foff=0, size=16)
        second = row(category='formatter_remnant', compare_container='dungeon', compare_foff=0, foff=24, size=16)
        _, _, problems = self.check(first, second)
        self.assertEqual(len(problems), 1)

    def test_a_revoked_row_is_not_checked(self):
        bad = row(foff=32, compare_foff=32)
        _, _, problems = self.check(bad, dict(bad, active=False))
        self.assertEqual(problems, [])

    def test_absent_containers_skip_the_comparison_but_not_the_fields(self):
        for name in placed_copies.CONTAINERS.values():
            (self.root / placed_copies.CONTAINER_DIR / name).unlink()
        notes = []
        rows, compared, problems = LI.residue_comparison_problems(self.root, notes, regions=[row(foff=32, compare_foff=32)])
        self.assertEqual((rows, compared, problems), (1, 0, []))
        self.assertEqual(notes, ['skipped: retail containers absent'])
        _, _, problems = LI.residue_comparison_problems(
            self.root, [], regions=[{'container': 'dungeon', 'foff': 8, 'size': 16, 'category': 'stale_town_copy'}])
        self.assertEqual(len(problems), 1)


if __name__ == '__main__':
    unittest.main()
