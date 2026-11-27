import json
from pathlib import Path
import subprocess
import tempfile
import unittest

from tools.lint import evidence_values


class EvidenceValueTests(unittest.TestCase):
    def test_value_shapes_are_found(self):
        # every value below is invented for the test
        bad = [
            'table bytes 71 72 73 74 75 76 are a frame list',
            'frame list 0x01 0x02 0x03 0x04',
            'three (dx,dy) pairs (7,8),(-7,8),(-7,0)',
            'defines it {9001,9002,9003}',
            'table bytes (IMG 0x1234) hold glyph 0x55',
            'the box is -21, -22, -23, 24',
            'table bytes 0x0777 are the argument',
            'the label reads "some invented words"',
            'table is held as 11/22/33/44 for the rows',
            'table bytes are x 0x11 y 0x22 w 0x33 h 0x44',
            'all eight bytes are 5a so one frame',
            'table bytes are three list pointers (0x80011111, 0x80022222, 0x80033333)',
            'eight word pointers 0x80011111 0x80022222 listed',
            'table bytes hold 0x1234 then',
        ]
        for text in bad:
            with self.subTest(text=text):
                self.assertTrue(evidence_values.findings(text))

    def test_words_offsets_sizes_and_symbol_addresses_pass(self):
        good = [
            'src/x/y.c: indexed by choice_index; 13 eight-byte entries; table at +0x3716 (values not quoted)',
            'table bytes (IMG 0x1234) are a direction table (values checked against the disc, not quoted)',
            'pointer table 0x800DCF0C..0x800DCF20 read by update_status_labels; s16 elements, 8 of them',
            'table bytes are three list pointers into the same bank (addresses not quoted)',
            'zero means nothing awarded yet; counter at +0x34 selects the word',
            'called from func_80174B20 and D_800DD148 at 0x80170874',
        ]
        for text in good:
            with self.subTest(text=text):
                self.assertEqual(evidence_values.findings(text), [])

    def test_only_added_rows_are_checked_and_text_is_not_echoed(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)

            def run(*args):
                subprocess.run(['git', '-C', temp, '-c', 'user.name=t', '-c', 'user.email=t@invalid', *args],
                               check=True, capture_output=True)
            (root / 'config').mkdir()
            (root / 'ledger').mkdir()
            old_tsv = '0x80000000\tfunc_80000000\told_row\tlist 1,2,3,4 kept from the base\n'
            (root / 'config/names.tsv').write_text(old_tsv)
            (root / 'ledger/names.jsonl').write_text('')
            run('init', '-q')
            run('add', '-A')
            run('commit', '-q', '-m', 'base')
            (root / 'config/names.tsv').write_text(
                old_tsv + '0x80000004\tfunc_80000004\tnew_row\ttable bytes 71 72 73 74 75 are a list\n'
                '0x80000008\tfunc_80000008\tclean_row\ttable bytes are a direction table (values not quoted)\n')
            (root / 'ledger/names.jsonl').write_text(
                json.dumps({'addr': '0x8', 'evidence': 'pairs (7,8),(-7,8)'}) + '\n'
                + json.dumps({'addr': '0xC', 'evidence': 'a table of eight s16 pairs'}) + '\n')
            problems = evidence_values.check(root, 'HEAD')
            self.assertEqual([p.split(':')[:2] for p in problems],
                             [['config/names.tsv', '2'], ['ledger/names.jsonl', '1']])
            self.assertNotIn('71 72', '\n'.join(problems))


if __name__ == '__main__':
    unittest.main()
