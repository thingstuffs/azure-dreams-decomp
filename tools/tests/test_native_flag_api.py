"""Native flag-reader compatibility, with module side effects forbidden."""
import tempfile
import unittest
from pathlib import Path
import sys

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS / 'lint'))
import lint_build


class NativeFlagApiTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.port = Path(self.temporary.name) / 'port'
        self.root = Path(self.temporary.name) / 'game'
        (self.port / 'tools').mkdir(parents=True)

    def builder(self, text):
        (self.port / 'tools/build.py').write_text(text)

    def test_legacy_literal_keeps_include_order_and_warnings(self):
        self.builder("raise RuntimeError('builder must not execute')\n"
                     "CFLAGS = ['-m32', '-w', '-I'+str(PORT/'include'), '-I'+str(GEN/'include')]\n"
                     "CFLAGS += ['-fwrapv']\n")
        flags = lint_build.native_flags(self.port, self.root)
        self.assertEqual(flags[:3], ['-I'+str(self.port/'include'), '-I'+str(self.root/'include'), '-fwrapv'])
        self.assertNotIn('-w', flags)
        self.assertNotIn('-m32', flags)
        self.assertIn('-Wreturn-type', flags)

    def test_shared_api_skips_module_startup_and_uses_compiler_class(self):
        self.builder("raise RuntimeError('builder must not execute')\n"
                     "CFLAGS = native_units.cflags(PORT, GEN/'include', COMPILER_ID, ARGS.optimization, ARGS.sanitize, ARGS.coverage)\n")
        (self.port/'tools/native_units.py').write_text("raise RuntimeError('module startup must not execute')\n" + '''
def cflags(port, gen_include, compiler_id, optimization='1', sanitize=False, coverage=False):
    assert not sanitize and not coverage
    flags = ['-m32', '-w', '-O'+optimization, '-I'+str(Path(port)/'include'), '-I'+str(gen_include), '-fwrapv']
    if 'clang' in compiler_id.lower():
        flags += ['-Wno-error=incompatible-pointer-types']
    return flags
''')
        gcc = lint_build.native_flags(self.port, self.root, 'gcc fixture')
        clang = lint_build.native_flags(self.port, self.root, 'clang fixture')
        self.assertIn('-I'+str(self.root/'include'), gcc)
        self.assertNotIn('-I'+str(self.port/'gen/include'), gcc)
        self.assertIn('-Wno-error=incompatible-pointer-types', clang)
        self.assertNotIn('-Wno-error=incompatible-pointer-types', gcc)
        self.assertIn('-Wincompatible-pointer-types', clang)
        self.assertFalse(any(flag.startswith('-fsanitize') for flag in clang))

    def test_unknown_builder_expression_is_rejected(self):
        self.builder('CFLAGS = unknown_flags(PORT)\n')
        with self.assertRaisesRegex(ValueError, 'unsupported native CFLAGS'):
            lint_build.native_flags(self.port, self.root)

    def test_invalid_shared_api_result_is_rejected(self):
        self.builder('CFLAGS = native_units.cflags(PORT)\n')
        (self.port/'tools/native_units.py').write_text("def cflags(*args, **kwargs):\n    return 'not a flag list'\n")
        with self.assertRaisesRegex(ValueError, 'native builder must define'):
            lint_build.native_flags(self.port, self.root)


if __name__ == '__main__':
    unittest.main()
