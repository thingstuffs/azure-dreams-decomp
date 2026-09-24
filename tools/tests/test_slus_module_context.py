"""Grouped row edits compile real sibling/data context and invalidate shared evidence."""
import json
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import slus_module_context as C
from row_db import slus_edges
from fidelity.slus_iso import SlusView


class ModuleContextTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        for p in ('config', 'src/slus', 'raw/slus', 'include', 'scratch'):
            (self.root / p).mkdir(parents=True)
        self.module = {
            'name': 'sample', 'source': 'src/sample.c',
            'members': [{'id': 'slus/a', 'source': 'src/a.c', 'functions': ['a']},
                        {'id': 'slus/b', 'source': 'src/b.c', 'functions': ['b']}],
            'headers': ['include/shared.h'],
            'recipe': {'ccver': '2.7.2-cdk', 'ccflags': '', 'asflags': ''},
            'data': [], 'evidence': 'docs/evidence/sample.md'}
        (self.root / 'config/slus_modules.json').write_text(json.dumps({'version': 1, 'modules': [self.module]}))
        (self.root / 'include/shared.h').write_text('extern int count;\nint a(void);\nint b(void);\n')
        (self.root / 'src/slus/sample.c').write_text('#include "shared.h"\nint count = 4;\n#include "a.c"\n#include "b.c"\n')
        (self.root / 'src/slus/a.c').write_text('int a(void) { return count + 1; }\n')
        (self.root / 'src/slus/b.c').write_text('int b(void) { return a(); }\n')
        self.row = {'id': 'slus/a', 'kind': 'slus', 'c_path': 'src/a.c'}

    @unittest.skipUnless(shutil.which('cc'), 'host compiler unavailable')
    def test_candidate_uses_actual_definition_and_sibling(self):
        candidate = self.root / 'scratch/candidate.c'
        candidate.write_text('int a(void) { return count + 3; }\n')
        wrapper = C.compilation_source(self.row, candidate, self.root / 'scratch', root=self.root)
        main = self.root / 'scratch/main.c'
        main.write_text('#include "shared.h"\nint main(void) { return b() != 7; }\n')
        exe = self.root / 'scratch/program'
        subprocess.run(['cc', '-I', str(self.root / 'include'), str(wrapper), str(main), '-o', str(exe)], check=True)
        self.assertEqual(subprocess.run([str(exe)]).returncode, 0)
        self.assertIn('count + 1', (self.root / 'src/slus/a.c').read_text())

    def test_all_shared_inputs_invalidate_both_rows(self):
        sibling = dict(self.row, id='slus/b', c_path='src/b.c')
        for path in C.input_paths(self.module, self.root):
            before = C.fingerprint(self.row, self.root)
            self.assertEqual(before, C.fingerprint(sibling, self.root))
            path.write_text(path.read_text() + '\n/* changed */\n')
            self.assertNotEqual(before, C.fingerprint(self.row, self.root))
            self.assertEqual(C.fingerprint(self.row, self.root), C.fingerprint(sibling, self.root))

    def test_historical_raw_source_stays_standalone(self):
        raw = self.root / 'raw/slus/a.c'
        raw.write_text('int a(void) { return 0; }\n')
        self.assertEqual(C.compilation_source(self.row, raw, self.root / 'scratch', self.root), raw)

    def test_missing_reordered_or_undeclared_includes_refused(self):
        source = self.root / 'src/slus/sample.c'
        for text in ('#include "a.c"\n', '#include "b.c"\n#include "a.c"\n', '#include "extra.c"\n'):
            source.write_text(text)
            with self.assertRaises(ValueError):
                C.compilation_source(self.row, self.root / 'src/slus/a.c', self.root / 'scratch', self.root)

    def test_logical_rows_survive_one_physical_edge(self):
        ninja = 'build build/src/sample.o: cc src/sample.c\n  ccver = 2.7.2-cdk\n  ccflags = \n  asflags = \n'
        edges = slus_edges(ninja, self.root)
        self.assertEqual([e['src'] for e in edges], ['src/a.c', 'src/b.c'])
        self.assertEqual([e['out'] for e in edges], ['build/src/a.o', 'build/src/b.o'])

    def test_individual_recipe_move_refused(self):
        with self.assertRaisesRegex(ValueError, 'verify all members together'):
            C.require_individual_recipe(self.row, self.root)

    def test_recipe_lander_refuses_before_verification_or_writes(self):
        from fidelity.land_recipe_move import Lander
        import common
        lane = self.root / 'lane'
        candidate = lane / 'out/slus/a.c'
        candidate.parent.mkdir(parents=True)
        original = (self.root / 'src/slus/a.c').read_text()
        candidate.write_text(original)
        candidate.with_name('a.c.base_sha').write_text(common.sha_text(original))
        (lane / 'cells.jsonl').write_text(json.dumps({'id': 'slus/a', 'to': '2.8.1'}) + '\n')
        row = dict(self.row, container='slus', cfg='2.7.2-cdk')
        def unexpected(_):
            self.fail('grouped recipe reached individual verification')
        logs = []
        lander = Lander(self.root, 'test', lane, verify_slus=unexpected, log=lambda *s: logs.append(str(s)))
        with patch.object(common, 'rows', return_value=[row]):
            self.assertEqual(lander.plan(), [])
        self.assertTrue(any('skip grouped recipe move' in s for s in logs))
        self.assertEqual((self.root / 'src/slus/a.c').read_text(), original)

    def test_conflicting_and_incomplete_recipe_trials_refused_before_build(self):
        view = object.__new__(SlusView)
        view.modules = [self.module]
        self.assertIn('conflicting', view.gate({'a': (None, '2.8.1', ''), 'b': (None, '2.7.2-cdk', '')})['detail'])
        self.assertIn('every member', view.gate({'a': (None, '2.8.1', '')})['detail'])


if __name__ == '__main__':
    unittest.main()
