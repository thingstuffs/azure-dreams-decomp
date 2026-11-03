import importlib.util
from pathlib import Path
import subprocess
import tempfile
import unittest

spec = importlib.util.spec_from_file_location('foreign_floor_tool', Path(__file__).with_name('foreign_imports.py'))
tool = importlib.util.module_from_spec(spec)
spec.loader.exec_module(tool)


class ForeignFloorShieldTests(unittest.TestCase):
    header = ('#ifndef IMPORTS_H\n#define IMPORTS_H\n#include "common.h"\n'
              's32 foreign_floor(s32); /* current callee (twin chain) */\n'
              's32 normal_import(s32);\n#endif\n')
    source = ('#include "common.h"\ns32 foreign_floor(s32, s32); /* Unprototyped: build arity */\n'
              's32 normal_import(s32);\ns32 caller(s32 a) { return foreign_floor(a, 9) + normal_import(a); }\n')

    def edited(self, disabled=('foreign_floor',)):
        found, scan = tool.local_sites(self.source, {'normal_import'})
        spans = [(start, end) for start, end, _n, _depth in found['normal_import']]
        return tool.edit_text(self.source, 'imports.h', spans, scan, disabled)

    def test_header_keeps_one_declaration_and_identity_comment(self):
        header = tool.shield_header(self.header, {'foreign_floor'})
        self.assertIn('s32 foreign_floor(s32); /* current callee (twin chain) */', header)
        self.assertEqual(header.count('s32 foreign_floor('), 1)
        self.assertIn('#ifndef AZ_FOREIGN_LOCAL_FOREIGN_FLOOR\n', header)
        self.assertEqual(tool.shield_header(header, {'foreign_floor'}), header)

    def test_local_floor_and_arity_survive(self):
        edited = self.edited()
        self.assertIn('s32 foreign_floor(s32, s32); /* Unprototyped: build arity */', edited)
        self.assertNotIn('s32 normal_import(s32);', edited)
        self.assertIn('#define AZ_FOREIGN_LOCAL_FOREIGN_FLOOR\n#include "imports.h"\n#undef AZ_FOREIGN_LOCAL_FOREIGN_FLOOR', edited)

    def test_other_callers_see_canonical_prototype(self):
        self.assertNotIn('AZ_FOREIGN_LOCAL_', self.edited(disabled=()))

    def test_missing_or_ambiguous_header_declaration_is_refused(self):
        with self.assertRaisesRegex(ValueError, 'one header declaration'):
            tool.shield_header(self.header, {'not_declared'})
        with self.assertRaisesRegex(ValueError, 'one header declaration'):
            tool.shield_header(self.header.replace('s32 normal_import(s32);', 's32 foreign_floor(s32);'), {'foreign_floor'})

    def test_shielded_import_preserves_object_with_conflicting_build_arity(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root/'common.h').write_text('#ifndef COMMON_H\n#define COMMON_H\ntypedef int s32;\n#endif\n')
            (root/'imports.h').write_text(tool.shield_header(self.header, {'foreign_floor'}))
            unit = root/'unit.c'
            unit.write_text(self.source)
            subprocess.run(['gcc', '-O2', '-fno-ident', '-c', str(unit), '-o', str(root/'before.o')], check=True, capture_output=True)
            unit.write_text(self.edited(disabled=()))
            refused = subprocess.run(['gcc', '-fsyntax-only', str(unit)], capture_output=True)
            self.assertNotEqual(refused.returncode, 0)
            unit.write_text(self.edited())
            subprocess.run(['gcc', '-O2', '-fno-ident', '-c', str(unit), '-o', str(root/'after.o')], check=True, capture_output=True)
            self.assertEqual((root/'before.o').read_bytes(), (root/'after.o').read_bytes())


if __name__ == '__main__':
    unittest.main()
