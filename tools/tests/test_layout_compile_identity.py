"""The two-pass object receipt is keyed to the complete physical move map."""
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
import layout_compile_identity as I


class SnapshotTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        self.tree = self.root / 'tree.tsv'
        self.tree.write_text('current_path\tproposed_path\n'
                             'src/slus/old.c\tsrc/engine/new.c\n')
        old = self.root / 'src/slus/old.c'
        old.parent.mkdir(parents=True)
        old.write_text('int f(void) { return 1; }\n')
        self.recipe = {'kind': 'row', 'container': 'slus', 'cell': '2.7.2',
                       'flags': [], 'asflags': [], 'row_id': 'slus/old'}

    def fake(self, root, rel, recipe):
        return {'source': rel, 'kind': recipe['kind'], 'recipe': recipe,
                'raw_sha256': 'raw', 'canonical_assembly_sha256': 'assembly',
                'canonical_object_sha256': 'object'}

    def test_snapshot_then_compare_after_move(self):
        receipt = self.root / 'receipt.jsonl'
        with patch.object(I, 'recipes', return_value=({'src/slus/old.c': self.recipe}, set())), \
             patch.object(I, 'capture_one', side_effect=self.fake):
            self.assertEqual(I.run(self.root, self.tree, snapshot=receipt)['physical_tus'], 1)
        with patch.object(I, 'recipes', return_value=({'src/slus/old.c': self.recipe}, set())):
            with self.assertRaisesRegex(ValueError, 'post-move physical TU'):
                I.run(self.root, self.tree, compare=receipt)
        (self.root / 'src/engine').mkdir()
        (self.root / 'src/slus/old.c').rename(self.root / 'src/engine/new.c')
        with patch.object(I, 'recipes', return_value=({'src/engine/new.c': self.recipe}, set())), \
             patch.object(I, 'capture_one', side_effect=self.fake):
            result = I.run(self.root, self.tree, compare=receipt)
        self.assertEqual(result['canonical_equal'], 1)
        self.assertEqual(result['raw_equal'], 1)
        self.assertEqual(json.loads(receipt.read_text())['old'], 'src/slus/old.c')

    def test_nonhome_member_refused(self):
        with patch.object(I, 'recipes', return_value=({}, {'src/slus/old.c'})):
            with self.assertRaisesRegex(ValueError, 'non-home native member'):
                I.run(self.root, self.tree, snapshot=self.root / 'receipt.jsonl')



class ProductionFlagsTest(unittest.TestCase):
    """capture_one proves the objects the build links: each linked recipe's cell, cc and maspsx flags."""

    def table(self):
        def r(rid, asflags, rows, cell='2.6.3', flags=('-G0',), module=False):
            return dict(id=rid, cell=cell, flags=list(flags), asflags=list(asflags), rows=rows, module=module)
        return {'src/town/devkit/a.c': [r('other', [], ['town/func_808B95EC']),
                                        r('home', ['--aspsx-version=2.40'], ['town/func_8087FFD0']),
                                        r('same', [], ['town/func_808C0000'])],
                'src/town/m.c': [r('row_copy', [], ['town/func_1']),
                                 dict(r('mod', ['--expand-div'], [], module=True),
                                      evidence={'MASPSX_NORETURN_FILE': 'build/.state/evidence/bank.txt'})]}

    def test_primary_is_the_recipe_placing_the_proof_row(self):
        recipe = {'kind': 'row', 'container': 'town', 'cell': '2.6.3', 'flags': ['-G0'],
                  'asflags': ['--aspsx-version=2.40'], 'row_id': 'town/func_8087FFD0'}
        with patch.object(I, 'production_recipes', return_value=self.table()):
            compiles = I.production_compiles(self.root, 'src/town/devkit/a.c', recipe)
        self.assertEqual([(c['id'], c['ids'], c['asflags']) for c in compiles],
                         [('home', ['home'], ['--aspsx-version=2.40']), ('other', ['other', 'same'], [])])

    def test_module_recipe_and_fallbacks(self):
        module = {'kind': 'overlay_module', 'container': 'town', 'cell': '2.7.2', 'flags': [], 'asflags': []}
        with patch.object(I, 'production_recipes', return_value=self.table()):
            compiles = I.production_compiles(self.root, 'src/town/m.c', module)
            self.assertEqual([(c['id'], c['evidence']) for c in compiles],
                             [('mod', {'MASPSX_NORETURN_FILE': 'build/.state/evidence/bank.txt'})])
            # A source the build does not link keeps the proof map's registry recipe.
            fallback = I.production_compiles(self.root, 'src/town/unlinked.c', module)
        self.assertEqual(fallback, [dict(id=None, ids=[], cell='2.7.2', flags=[], asflags=[], evidence={})])
        with patch.object(I, 'production_recipes', return_value=None):          # no generated build graph
            self.assertEqual(I.production_compiles(self.root, 'src/town/m.c', module)[0]['id'], None)

    def test_capture_assembles_with_each_compile_flags(self):
        import layout_identity
        source = self.root / 'src/town/devkit/a.c'
        source.parent.mkdir(parents=True)
        source.write_text('int f(void) { return 1; }\n')
        recipe = {'kind': 'row', 'container': 'town', 'cell': '2.6.3', 'flags': ['-G0'],
                  'asflags': ['--aspsx-version=2.40'], 'row_id': 'town/func_8087FFD0'}
        seen = []

        def fake_run(argv, **kwargs):
            seen.append(argv)
            out = Path(argv[argv.index('-o') + 1])
            flags = [a for a in argv if a.startswith('--') and a not in
                     ('--aspsx-version=2.79', '--dont-force-G0', '--run-assembler')
                     and not a.startswith('--gnu-as-path')]
            out.write_bytes(('object ' + ' '.join(flags)).encode())
            return subprocess.CompletedProcess(argv, 0, b'', b'')

        def fake_command(args, **kwargs):      # gcc -S writes its output; ccproc returns the stream
            args = list(map(str, args))
            if '-S' in args:
                Path(args[args.index('-o') + 1]).write_text('.text\n')
            return b'.text\n'

        with patch.object(I, 'production_recipes', return_value=self.table()), \
             patch.object(I, 'command', side_effect=fake_command), \
             patch.object(layout_identity.subprocess, 'run', side_effect=fake_run):
            res = I.capture_one(self.root, 'src/town/devkit/a.c', recipe)
        self.assertEqual([a[a.index('-G8') + 1:a.index('-o')] for a in seen],
                         [['--aspsx-version=2.40'], [], ['--aspsx-version=2.40']])   # home, other, canonical
        self.assertEqual(res['raw_sha256'], I.digest(b'object --aspsx-version=2.40'))
        self.assertEqual(res['variant_raw_sha256'], {'home': I.digest(b'object --aspsx-version=2.40'),
                                                     'other': I.digest(b'object '), 'same': I.digest(b'object ')})

    def test_reassemble_uses_recipe_evidence_tables(self):
        import layout_identity
        seen = {}

        def fake_run(argv, **kwargs):
            seen.update(kwargs['env'])
            Path(argv[argv.index('-o') + 1]).write_bytes(b'o')
            return subprocess.CompletedProcess(argv, 0, b'', b'')

        with patch.object(layout_identity.subprocess, 'run', side_effect=fake_run):
            layout_identity.reassemble(self.root, b'', self.root, 'dungeon', ['--expand-div'],
                                       {'MASPSX_NORETURN_FILE': 'build/.state/evidence/bank.txt'})
        self.assertEqual(seen['MASPSX_NORETURN_FILE'], str(self.root / 'build/.state/evidence/bank.txt'))
        self.assertEqual(seen['MASPSX_SIBCALL_FILE'], str(self.root / 'config/sibcall_syms.dungeon.txt'))

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)


if __name__ == '__main__':
    unittest.main()
