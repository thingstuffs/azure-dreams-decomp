import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parent))
import tu_slots as S


class SlotTests(unittest.TestCase):
    def fixture(self):
        # Two identical instruction forms with different linked low immediates.
        home = bytes.fromhex('3412023c0800e003')
        other = bytes.fromhex('7856023c0800e003')
        row = dict(container='town', foff=0, size=len(home), cfg='cell')
        masks = [(0, 'R_MIPS_HI16')]
        shape = dict(row, home='town/a', home_sha256=S.sha(home),
                     masked_sha256=S.sha(S.masked(home, masks)), relocations=masks)
        return row, shape, home + other

    def test_linked_immediates_are_masked_but_opcodes_are_not(self):
        row, shape, blob = self.fixture()
        result = S.check_slot(shape, row, blob, 8)
        self.assertEqual(result['state'], 'masked_text_equal')
        changed = blob[:10] + b'\x03' + blob[11:]
        result = S.check_slot(shape, row, changed, 8)
        self.assertEqual(result['state'], 'text_conflict')
        self.assertEqual(result['first_difference'], 2)

    def test_jump_opcode_and_nonrelocated_words_stay_visible(self):
        masks = [(0, 'R_MIPS_26')]
        self.assertEqual(S.masked(bytes.fromhex('0000000c'), masks),
                         S.masked(bytes.fromhex('ffffff0f'), masks))
        self.assertNotEqual(S.masked(bytes.fromhex('0000000c'), masks),
                            S.masked(bytes.fromhex('00000008'), masks))

    def test_unsupported_or_overlapping_masks_refuse(self):
        for masks in [[(0, 'unknown')], [(1, 'R_MIPS_32')], [(-4, 'R_MIPS_32')],
                      [(8, 'R_MIPS_32')], [(0, 'R_MIPS_32'), (0, 'R_MIPS_LO16')],
                      [(True, 'R_MIPS_32')]]:
            with self.assertRaises(ValueError):
                S.masked(b'\0' * 8, masks)

    def test_stale_home_and_changed_geometry_refuse(self):
        row, shape, blob = self.fixture()
        with self.assertRaisesRegex(ValueError, 'home bytes changed'):
            S.check_slot(shape, row, b'x' + blob[1:], 8)
        with self.assertRaisesRegex(ValueError, 'registry geometry changed'):
            S.check_slot(shape, dict(row, size=4), blob, 8)
        shape['masked_sha256'] = 'changed'
        with self.assertRaisesRegex(ValueError, 'fingerprint changed'):
            S.check_slot(shape, row, blob, 8)

    def test_equal_bytes_beyond_view_are_not_a_match(self):
        row, shape, blob = self.fixture()
        self.assertEqual(S.check_slot(shape, row, blob, 8, dict(foff=0, size=8))['state'], 'outside_view')
        self.assertEqual(S.check_slot(shape, row, blob, 9)['state'], 'outside_container')
        self.assertEqual(S.check_slot(shape, row, blob, -1)['state'], 'outside_container')

    def test_extraction_requires_complete_original_text_and_records_other_allocations(self):
        row, _, blob = self.fixture()
        sections = {'.text.func_a': [blob[:8], [(0, 'R_MIPS_HI16', 'D_80000000')], 'PROGBITS'],
                    '.rodata': [b'xxxx', [], 'PROGBITS']}
        with tempfile.TemporaryDirectory() as td:
            obj = Path(td) / 'object.o'
            obj.write_bytes(b'object identity')
            with patch.object(S.CP, '_sections', return_value=sections):
                record = S.extract('town/a', row, obj, blob)
                self.assertEqual(record['other_sections'], {'.rodata': 4})
                self.assertIn('all allocations still require proof', record['authority'])
                with self.assertRaises(ValueError):
                    S.extract('town/a', dict(row, size=4), obj, blob)
            sections['.text.func_a'][0] = b'xxxxxxxx'
            with patch.object(S.CP, '_sections', return_value=sections), self.assertRaises(ValueError):
                S.extract('town/a', row, obj, blob)

    def test_equal_registered_sibling_in_another_view_is_exposed_without_admission(self):
        row, shape, blob = self.fixture()
        rows = {'town/a': dict(row, id='town/a'), 'town/b': dict(row, id='town/b', foff=8)}
        geometry = dict(sites=['town/a', 'town/b'], homes=['town/a', 'town/b'], holds=[], cohorts=[
            dict(state='partial', image='town/view', foff=8, delta=0,
                 missing=[dict(home='town/a', foff=8)])])
        with patch.object(S.C, 'plan', return_value=geometry):
            summaries, details = S.audit([dict(group_id='G', member_rows='town/a;town/b')],
                {'town/a': shape}, rows, {'town/view': dict(container='town', foff=0, size=16)}, {}, {}, lambda _: blob)
        self.assertEqual(summaries[0]['masked_text_equal'], 1)
        item = details[0]['cohorts'][0]['checks'][0]
        self.assertEqual(item['registered_rows'], ['town/b'])
        self.assertEqual(item['same_home_rows'], [])
        self.assertEqual(item['other_home_rows'][0]['home'], 'town/b')
        self.assertNotIn('geometry_complete', details[0])
        self.assertIn('no installation proof', details[0]['authority'])
        # Exercise the paged manifest contract with real audit output.
        details[0]['cohorts'] *= 20
        with tempfile.TemporaryDirectory() as td:
            path = Path(td) / 'group.json'
            S.C.write_details(details[0], path, limit=1000)
            manifest = json.loads(path.read_text())
            recovered = []
            for page in manifest['pages']:
                self.assertLessEqual((path.parent / page['path']).stat().st_size, 1000)
                if page['kind'] == 'cohorts':
                    recovered += json.loads((path.parent / page['path']).read_text())
            self.assertEqual(recovered, details[0]['cohorts'])


if __name__ == '__main__':
    unittest.main()
