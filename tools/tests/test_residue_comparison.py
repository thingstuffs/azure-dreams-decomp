"""Test the recorded byte comparisons and compact bank witnesses."""
import hashlib
import json
import struct
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
        data = (self.root / placed_copies.CONTAINER_DIR / placed_copies.CONTAINERS['dungeon']).read_bytes()
        first = row(category='formatter_remnant', compare_container='dungeon', compare_foff=0, foff=0, size=16,
                    retail_sha256=hashlib.sha256(data[:16]).hexdigest())
        second = dict(first, foff=24, retail_sha256=hashlib.sha256(data[24:40]).hexdigest())
        _, _, problems = self.check(first, second)
        self.assertEqual(len(problems), 1)

    def test_formatter_identifier_requires_the_recorded_bytes(self):
        data = (self.root / placed_copies.CONTAINER_DIR / placed_copies.CONTAINERS['dungeon']).read_bytes()
        identifier = dict(category='formatter_build_string', container='dungeon', foff=8, size=16)
        self.assertIn('invalid retail_sha256', self.check(identifier)[2][0])
        identifier['retail_sha256'] = hashlib.sha256(data[8:24]).hexdigest()
        self.assertEqual(self.check(identifier), (1, 1, []))
        self.write('dungeon', data[:-57] + bytes(57))
        self.assertIn('differs from recorded retail_sha256', self.check(identifier)[2][0])

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


class HeadBankComparison(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.dungeon = self.root / placed_copies.CONTAINER_DIR / placed_copies.CONTAINERS['dungeon']
        self.dungeon.parent.mkdir(parents=True)
        self.slus = self.root / 'baserom/slus_006.14'
        self.slus.parent.mkdir()
        self.evidence = self.root / 'docs/evidence/older_dungeon_head_banks.json'
        self.ledger = self.root / 'ledger'
        self.evidence.parent.mkdir(parents=True)
        self.ledger.mkdir()
        base, target = 0x8010aa40, 0x80030008
        self.bank = bytearray(64)
        struct.pack_into('<I', self.bank, 0, base + 4)
        struct.pack_into('<I', self.bank, 12, (3 << 26) | ((base + 8) >> 2 & 0x3ffffff))
        struct.pack_into('<I', self.bank, 40, (3 << 26) | (target >> 2 & 0x3ffffff))
        self.dungeon.write_bytes(self.bank)
        exe = bytearray(0x820)
        exe[:8] = b'PS-X EXE'
        struct.pack_into('<I', exe, 0x18, target - 8)
        self.slus.write_bytes(exe)
        self.region = dict(container='dungeon', foff=4, size=60,
                           category='older_dungeon_head_bank', bank_foff=0, row='dungeon/func_HEAD',
                           evidence=self.evidence.relative_to(self.root).as_posix(),
                           retail_sha256=self.digest(self.bank[4:]))
        census = dict(
            resident=dict(row='slus/func_80030000', target=target, sha256=self.digest(exe[0x800:])),
            banks=[dict(foff=0, end=64, linked_base=base, entry_foff=4, helper_foff=8,
                        local_call_foff=12, resident_call_foff=40,
                        resident_sequence_sha256=self.digest(self.bank[16:48]))],
        )
        self.evidence.write_text(json.dumps(census))
        rows = [
            dict(container='dungeon', id='dungeon/func_HEAD', func='func_HEAD', foff=4, size=60),
            dict(container='slus', id='slus/func_80030000', func='func_80030000', foff=0x800, size=32),
        ]
        (self.ledger / 'rows.jsonl').write_text(''.join(json.dumps(row) + '\n' for row in rows))

    @staticmethod
    def digest(data):
        return hashlib.sha256(data).hexdigest()

    def check(self, notes=None):
        (self.ledger / 'coverage_regions.jsonl').write_text(json.dumps(self.region) + '\n')
        return LI.older_head_bank_problems(self.root, notes)

    def test_verified_incompatible_bank(self):
        self.assertEqual(self.check(), (1, 1, []))

    def test_changed_bank_witnesses_fail(self):
        for off, problem in [(0, 'entry pointer'), (12, 'call at +0xC'), (40, 'resident call sequence')]:
            with self.subTest(off=off):
                changed = self.bank[:]
                changed[off] ^= 1
                self.dungeon.write_bytes(changed)
                self.assertTrue(any(problem in entry for entry in self.check()[2]))

    def test_changed_resident_body_fails(self):
        exe = bytearray(self.slus.read_bytes())
        exe[-1] ^= 1
        self.slus.write_bytes(exe)
        self.assertIn('SLUS resident body differs', self.check()[2][0])

    def test_missing_retail_checks_structure(self):
        self.slus.unlink()
        notes = []
        self.assertEqual(self.check(notes), (1, 0, []))
        self.assertEqual(len(notes), 1)
        self.region['size'] -= 4
        self.assertIn('registered extent differs', self.check()[2][0])


if __name__ == '__main__':
    unittest.main()
