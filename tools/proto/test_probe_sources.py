import json
from pathlib import Path
import tempfile
import sys
import unittest

from tools.proto.probe_sources import diagnostic_keys


class NativeDiagnosticTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory(dir=Path(__file__).resolve().parents[2] / "build")
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        (self.root / 'a.c').write_text('void a(void) {\n    bar(foo(x));\n}\nvoid b(void) {\n    bar(foo(x));\n}\n')

    def errors(self, line, column=9):
        return diagnostic_keys(f'a.c:{line}:{column}: error: incompatible pointer type\n', self.root)

    def test_declaration_line_insertion_keeps_error_identity(self):
        before = self.errors(2)
        p = self.root / 'a.c'
        p.write_text('void extra(void);\n' + p.read_text())
        self.assertEqual(before, self.errors(3))

    def test_identical_messages_at_different_calls_do_not_cancel(self):
        self.assertTrue(self.errors(2, 13) - self.errors(2, 9))

    def test_identical_lines_in_different_functions_do_not_cancel(self):
        self.assertTrue(self.errors(5) - self.errors(2))

    def test_fatal_diagnostics_are_not_silently_dropped(self):
        errors = diagnostic_keys('a.c:1:1: fatal error: missing header\n', self.root)
        self.assertEqual(sum(errors.values()), 1)

    def test_root_paths_are_normalized(self):
        text = f'{self.root}/a.c:2:9: error: incompatible pointer type\n'
        self.assertEqual(diagnostic_keys(text, self.root), self.errors(2))
        self.assertEqual(json.loads(next(iter(self.errors(2))))[:2], ['a.c', 'a'])


if __name__ == '__main__':
    unittest.main()
