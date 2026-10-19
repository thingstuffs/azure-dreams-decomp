"""Whole-tree layout transactions, including inlining and consumer rebasing."""
import json
from pathlib import Path
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
import guarded_package as P
import layout_apply as A
import source_layout as L


class TreeApplyTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name) / 'root'
        self.root.mkdir()
        self.tree = Path(self.tmp.name) / 'tree.tsv'
        self.headers = Path(self.tmp.name) / 'headers.tsv'
        self.inline = Path(self.tmp.name) / 'inline.tsv'
        self.write('ledger/rows.jsonl', json.dumps({'id': 'slus/member', 'container': 'slus',
                                                   'c_path': 'src/member.c'}) + '\n')
        self.write('src/slus/member.c', '#include "shared.h"\nint member(void) { return 1; }\n')
        self.write('src/slus/group.c', '#include "shared.h"\n#include "member.c"\n')
        self.write('src/slus/consumer.c', '#include "group.c"\n')
        self.write('include/shared.h', 'int member(void);\n')
        self.write('config/overlays/modules.json', '{"source":"src/slus/group.c","headers":["include/shared.h"]}\n')
        self.write('config/slus_modules.json', '{"headers":["include/shared.h"]}\n')
        self.write('ledger/splits/slus.build.ninja', 'build foo: cc src/group.c | include/shared.h\n')
        self.tree.write_text('current_path\tproposed_path\n'
                             'src/slus/group.c\tsrc/engine/audio/group.c\n')
        self.headers.write_text('current_path\tproposed_path\tdisposition\n'
                                'include/shared.h\tinclude/engine/audio/shared.h\tmove proposed\n')
        self.inline.write_text('tu_current\tinclude_line\tinclude_token\tmember_source\t'
                               'member_id\tmanifest_key\tmember_order\tcondition_depth\thold\n'
                               'src/slus/group.c\t2\tmember.c\tsrc/slus/member.c\t'
                               'slus/member\tgroup\t1\t0\t\n')

    def write(self, rel, content):
        p = self.root / rel
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(content)

    def test_check_apply_reapply_and_reverse(self):
        before = (self.root / 'src/slus/group.c').read_bytes()
        changes, report = A.plan(self.root, self.tree, headers=self.headers, inline=self.inline)
        self.assertEqual(report['reverse_map']['src/engine/audio/group.c'], 'src/slus/group.c')
        self.assertEqual((self.root / 'src/slus/group.c').read_bytes(), before)
        self.assertEqual(report['inline_members'], 1)
        package = Path(self.tmp.name) / 'package'
        P.export(package, self.root, changes)
        P.apply(package, self.root, live=True)
        new = self.root / 'src/engine/audio/group.c'
        self.assertIn('int member(void) { return 1; }', new.read_text())
        self.assertIn('#include "engine/audio/shared.h"', new.read_text())
        self.assertFalse((self.root / 'src/slus/member.c').exists())
        self.assertEqual(L.row_relative('slus/member', self.root), 'src/engine/audio/group.c')
        self.assertIn('#include "../engine/audio/group.c"',
                      (self.root / 'src/slus/consumer.c').read_text())
        self.assertEqual(L.validate(self.root), 1)
        self.assertIn('include/engine/audio/shared.h', (self.root / 'config/slus_modules.json').read_text())
        self.assertIn('include/engine/audio/shared.h',
                      (self.root / 'ledger/splits/slus.build.ninja').read_text())
        projection = L.materialize_flat(self.root / 'projection', self.root)
        self.assertEqual((projection / 'slus/group.c').read_bytes(), new.read_bytes())
        self.assertEqual(len((self.root / 'ledger/layout_inline.jsonl').read_text().splitlines()), 1)
        more, again = A.plan(self.root, self.tree, headers=self.headers, inline=self.inline)
        self.assertEqual(again['moves'], {})
        self.assertEqual(more, {})

    def test_swap_is_atomic_and_metadata_does_not_cascade(self):
        self.write('src/slus/second.c', 'int second(void) { return 2; }\n')
        self.tree.write_text('current_path\tproposed_path\n'
                             'src/slus/group.c\tsrc/slus/second.c\n'
                             'src/slus/second.c\tsrc/slus/group.c\n')
        changes, report = A.plan(self.root, self.tree)
        self.assertEqual(report['moves']['src/slus/group.c'], 'src/slus/second.c')
        self.assertIn(b'int second(void)', changes['src/slus/group.c'])
        self.assertIn(b'#include "member.c"', changes['src/slus/second.c'])
        self.assertIn(b'src/slus/second.c', changes['config/overlays/modules.json'])

    def test_relink_copy_is_skipped(self):
        self.write('src/slus/group.c', '/* Relink of matched slus/member */\n')
        changes, report = A.plan(self.root, self.tree)
        self.assertEqual(report['moves'], {})
        self.assertEqual(report['skipped_nonhome']['src/slus/group.c'],
                         'non-home relink or placement copy')
        self.assertEqual(changes, {})

    def test_collision_and_path_macro_refuse(self):
        self.write('src/engine/audio/group.c', 'occupied\n')
        with self.assertRaisesRegex(ValueError, 'destination exists'):
            A.plan(self.root, self.tree)
        (self.root / 'src/engine/audio/group.c').unlink()
        self.write('src/slus/group.c', 'char *name = __FILE__;\n')
        with self.assertRaisesRegex(ValueError, 'path/line macro'):
            A.plan(self.root, self.tree)


if __name__ == '__main__':
    unittest.main()
