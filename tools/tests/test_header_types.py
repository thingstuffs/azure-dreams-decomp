"""A compiler must reject an unused function/data contradiction across headers."""
import importlib.util
from pathlib import Path
import shutil
import tempfile
import unittest

TOOL = Path(__file__).resolve().parents[1] / 'lint/header_types.py'
spec = importlib.util.spec_from_file_location('header_types', TOOL)
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)


class HeaderTypesTest(unittest.TestCase):
    def test_unused_cross_header_kind_conflict(self):
        for compiler in ('gcc', 'clang'):
            if not shutil.which(compiler):
                continue
            with self.subTest(compiler=compiler), tempfile.TemporaryDirectory() as folder:
                root = Path(folder)
                (root / 'include').mkdir()
                owner = root / 'include/owner.h'
                data = root / 'include/data.h'
                owner.write_text('void callback(void);\n')
                data.write_text('extern int callback;\n')
                result = module.check(root, compiler, ['include/owner.h', 'include/data.h'])
                self.assertNotEqual(result['returncode'], 0)
                self.assertIn('callback', result['diagnostic'])
                data.write_text('extern int table[3];\n')
                self.assertEqual(module.check(root, compiler,
                                 ['include/owner.h', 'include/data.h'])['returncode'], 0)


if __name__ == '__main__':
    unittest.main()
