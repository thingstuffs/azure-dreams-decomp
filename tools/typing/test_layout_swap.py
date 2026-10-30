"""Text-level pieces of the layout family swap: typedef removal, token renames, includes, member retype."""
from pathlib import Path
import tempfile
import unittest

from tools.typing import layout_swap as S


class TypedefSpanTests(unittest.TestCase):
    def test_removes_struct_typedef_with_trailing_comment(self):
        text = ('#include "common.h"\n\ntypedef struct S_80001234_0 {\n    u8 pad_00[0x8];\n    s32 unk_08;\n'
                '} S_80001234_0;   /* arg0 in f */\n\nvoid f(S_80001234_0 *p);\n')
        a, b = S.typedef_span(text, 'S_80001234_0')
        self.assertEqual(text[:a] + text[b:], '#include "common.h"\n\n\nvoid f(S_80001234_0 *p);\n')

    def test_nested_union_member_and_alias_typedef(self):
        text = 'typedef struct S_8000ABCD_1 {\n    union { s16 s; u16 u; } unk_00;\n} S_8000ABCD_1;\n'
        self.assertEqual(S.typedef_span(text, 'S_8000ABCD_1'), (0, len(text)))
        alias = 'x;\ntypedef ObjectFlags S_8000ABCD_2_pre;\ny;\n'
        a, b = S.typedef_span(alias, 'S_8000ABCD_2_pre')
        self.assertEqual(alias[:a] + alias[b:], 'x;\ny;\n')


class RenameTests(unittest.TestCase):
    def test_renames_tokens_not_comments_or_longer_names(self):
        text = '/* S_8000_0 view */ struct S_8000_0 *a = (S_8000_0 *)b; S_8000_01 c; "S_8000_0";\n'
        out = S.rename_tokens(text, 'S_8000_0', 'Thing')
        self.assertEqual(out, '/* S_8000_0 view */ Thing *a = (Thing *)b; S_8000_01 c; "S_8000_0";\n')

    def test_add_include_after_last_include(self):
        text = '#include "common.h"\n#include "town/scene.h"\n\nint x;\n'
        out = S.add_include(text, 'shared/town_root.h')
        self.assertEqual(out, '#include "common.h"\n#include "town/scene.h"\n#include "shared/town_root.h"\n\nint x;\n')
        self.assertEqual(S.add_include(out, 'shared/town_root.h'), out)


class RetypeFieldTests(unittest.TestCase):
    def test_retypes_one_pointer_member(self):
        header = ('typedef struct Root {\n    /* 0x1C */ void *position; /* viewed as Position */\n'
                  '    /* 0x20 */ void *services;\n} Root;\n')
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'include/shared').mkdir(parents=True)
            (root / 'include/shared/root.h').write_text(header)
            spec = {'header': 'shared/root.h', 'struct': 'Root', 'field': 'position', 'type': 'Position *'}
            S.retype_field(root, spec)
            out = (root / 'include/shared/root.h').read_text()
        self.assertIn('/* 0x1C */ Position *position; /* viewed as Position */', out)
        self.assertIn('void *services;', out)
        self.assertEqual(spec['old_type'], 'void *')


class PlanSelectionTests(unittest.TestCase):
    def test_disjoint_plans_skip_nested_and_overlapping_edits(self):
        a = {'file': 'f.c', 'edits': [(0, 5, 'x'), (10, 12, 'y')]}
        nested = {'file': 'f.c', 'edits': [(20, 30, 'p'), (22, 25, 'q')]}
        overlap = {'file': 'f.c', 'edits': [(11, 14, 'z')]}
        other = {'file': 'g.c', 'edits': [(0, 5, 'x')]}
        self.assertEqual(S.disjoint_plans([a, nested, overlap, other]), [a, other])


if __name__ == '__main__':
    unittest.main()
