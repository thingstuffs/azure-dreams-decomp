import sys
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools/lanes/lanekit'))
import kitlib


class NegateDependency(unittest.TestCase):
    def test_adjacent_forms(self):
        for text in ('b = -b; x - b;', 'b=-b; x = a - b;', 'b = - b;\nx -= b;',
                     'b=-b; /* fence */ x = a-b;'):
            with self.subTest(text=text):
                self.assertEqual(kitlib.fakedep_count(text), 1)
                self.assertTrue(any('fake dependency' in r for r in kitlib.admissible('x=a+b;', text, equal_pins=True)))

    def test_cleanup_allowed(self):
        self.assertEqual(kitlib.admissible('b=-b; x=a-b;', 'x=a+b;'), [])

    def test_unrelated_negation_is_not_flagged(self):
        for text in ('b=-b; x=a-c;', 'b=-b; f(); x=a-b;', 'b=-a; x=a-b;',
                     'obj.b=-obj.b; x=a-obj.b;', 'b=-b; x=b-a;',
                     '/* b=-b; x=a-b; */', 'puts("b=-b; x=a-b;");',
                     '#define NEG b=-b; x=a-b;\n', 'b=-b; x=a-b[0];'):
            with self.subTest(text=text):
                self.assertEqual(kitlib.fakedep_count(text), 0)

    def test_existing_patterns(self):
        for text in ('x=a+b-b;', 'x=a-b+b;', 'x=b^b;', 'x=a&m&m;', 'x=x;', 'x+=b;x-=b;'):
            self.assertEqual(kitlib.fakedep_count(text), 1, text)


if __name__ == '__main__':
    unittest.main()
