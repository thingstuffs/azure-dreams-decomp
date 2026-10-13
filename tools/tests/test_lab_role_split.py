import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest import mock

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools/lanes/lanekit'))
import role_split
import lab

SOURCE = 'void f(void) {\n    register s32 value ASM_REG("$8");\n    value = 1; /* value */\n    use(value);\n    value = 2;\n    use(value);\n}\n'
SPEC = {'symbol': 'value', 'roles': {'first': [3, 4], 'second': [5, 6]},
        'variants': {'first_only': {'first_value': ['first']},
                     'both': {'first_value': ['first'], 'second_value': ['second']}}}


class RoleSplits(unittest.TestCase):
    def test_partial_split_preserves_remaining_pin_and_comments(self):
        _, text, remaining = list(role_split.variants(SOURCE, SPEC))[0]
        self.assertIn('s32 first_value;', text)
        self.assertIn('register s32 value ASM_REG("$8");', text)
        self.assertIn('first_value = 1; /* value */', text)
        self.assertEqual(remaining, [5, 6])

    def test_complete_split_removes_original_declaration(self):
        _, text, remaining = list(role_split.variants(SOURCE, SPEC))[1]
        self.assertNotIn('ASM_REG', text)
        self.assertIn('s32 second_value;', text)
        self.assertEqual(remaining, [])

    def test_bad_line_overlap_name_and_declaration_refused(self):
        for mapping in ({'x': [100]}, {'x': [2]}, {'x': [3], 'y': [3]}, {'value': [3]},
                        {'return': [3]}, {'x': [True]}, {'x': []}, {'x': [1]}):
            with self.subTest(mapping=mapping), self.assertRaises(ValueError):
                role_split.split_roles(SOURCE, 'value', mapping)
        for text in ('int value = 0;\nvalue++;\n', 'int value;\nint value;\nvalue++;\n'):
            with self.assertRaises(ValueError):
                role_split.split_roles(text, 'value', {'x': [3]})

    def test_member_string_and_macro_mentions_are_not_roles(self):
        text = 'void f(void) {\n int value;\n p->value = 1;\n puts("value");\n#define X value\n value=2;\n}\n'
        for line in (3, 4, 5):
            with self.assertRaises(ValueError):
                role_split.split_roles(text, 'value', {'x': [line]})
        candidate, remaining = role_split.split_roles(text, 'value', {'x': [6]})
        self.assertEqual(remaining, [])
        self.assertIn('p->value', candidate)

    def test_cli_uses_lab_measurement_cap_score_and_staging_path(self):
        with tempfile.TemporaryDirectory() as td:
            spec = Path(td) / 'spec.json'
            spec.write_text(json.dumps(SPEC))
            fake = mock.Mock()
            fake.base, fake.start, fake.cfg, fake.count.return_value = SOURCE, None, None, 0
            with mock.patch.object(sys, 'argv', ['lab.py', 'row', '--role-split', str(spec), '--score']), mock.patch.object(lab, 'Lab', return_value=fake):
                lab.main()
            self.assertEqual(fake.test.call_count, 2)
            self.assertTrue(all(call.kwargs['score'] for call in fake.test.call_args_list))


if __name__ == '__main__':
    unittest.main()
