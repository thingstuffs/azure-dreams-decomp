"""Whole-owner recipe switches, authoritative image checks and rollback guards."""
import hashlib
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch
ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / 'tools'), str(ROOT / 'tools/fidelity')]
import slus_recipe as S

class DisposableRoot(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name).resolve()

class OwnerFixture(DisposableRoot):
    """Small synthetic plural ownership graph; no checkout inputs are fixtures."""
    def setUp(self):
        super().setUp()
        for directory in ('config', 'ledger/splits', 'raw/slus', 'src/slus', 'tools/build'):
            (self.root / directory).mkdir(parents=True)
        recipe = dict(ccver='2.8.1', ccflags='', asflags='')
        owner_names = ['list_cursor_e0', 'cd_command_state', 'table_counters_b1b_b1c']
        owner_stems = ['w_80041134_owned', 'cd_command_state_owned', 'b1b_b1c_table_owned']
        parents = []
        for stem, addresses in [('code', [0x80030000, 0x80030010]),
                                ('code2', [0x80030100, 0x80030110, 0x80030120, 0x80030130])]:
            functions = ['func_%08X' % address for address in addresses]
            raw = ''.join('int %s(void) { return 1; }\n' % f for f in functions)
            (self.root / 'raw/slus' / (stem + '.c')).write_text(raw)
            parents.append(dict(id='slus/' + stem, source='src/' + stem + '.c',
                                raw_sha256=hashlib.sha256(raw.encode()).hexdigest(),
                                recipe=dict(recipe), functions=functions,
                                parts=[dict(module=owner, functions=[function])
                                       for owner, function in zip(owner_names, functions[:-1])]))
        modules = []
        for index, (name, stem) in enumerate(zip(owner_names, owner_stems)):
            module = dict(name=name, source='src/' + stem + '.c', recipe=dict(recipe),
                          headers=[], data=[], evidence='docs/evidence/fixture.md', members=[])
            if index == 0:
                module['members'] = [dict(id='slus/w_80041134', source='src/w_80041134.c',
                                          functions=['func_80030200'])]
            else:
                module['partition_only'] = True
            modules.append(module)
        (self.root / 'config/slus_modules.json').write_text(json.dumps(dict(version=1, modules=modules)))
        (self.root / 'config/slus_partitions.json').write_text(json.dumps(dict(version=1, parents=parents)))
        (self.root / 'config/names.tsv').write_text('')
        ordinary = ['code', 'code2', 'code5', 'code10', 'code13', 'code14']
        rows = [dict(id='slus/' + stem, kind='slus') for stem in ordinary + ['w_80041134']]
        (self.root / 'ledger/rows.jsonl').write_text(''.join(json.dumps(row) + '\n' for row in rows))
        def edge(stem):
            return dict(src='src/' + stem + '.c', out='build/src/' + stem + '.o', **recipe)
        logical = [edge(stem) for stem in ordinary + ['w_80041134']]
        (self.root / 'ledger/splits/slus.jsonl').write_text(''.join(json.dumps(e) + '\n' for e in logical))
        physical = [edge(stem) for stem in ordinary + owner_stems]
        ninja = ''.join('build {out}: cc {src}\n  ccver = {ccver}\n  ccflags = {ccflags}\n'
                        '  asflags = {asflags}\n\n'.format(**e) for e in physical)
        (self.root / 'ledger/splits/slus.build.ninja').write_text(ninja)
        (self.root / 'tools/build/configure.py').write_text('# disposable registered recipe fixture\n')
        (self.root / 'src/slus/code5.c').write_text('int fixture(void) { return 5; }\n')

class OwnerTests(OwnerFixture):
    def test_plural_code2_has_four_complete_physical_owners(self):
        owners = S.select(self.root, 'slus/code2')
        self.assertEqual({o['stem'] for o in owners},
            {'code2', 'w_80041134_owned', 'cd_command_state_owned', 'b1b_b1c_table_owned'})
        e0 = S.select(self.root, 'slus/w_80041134', 'w_80041134_owned')
        self.assertEqual(e0['contributors'], ['slus/code', 'slus/code2', 'slus/w_80041134'])
        self.assertIsNotNone(e0['module'])
    def test_row_cannot_select_another_owner(self):
        with self.assertRaisesRegex(ValueError, 'not an owner'):
            S.select(self.root, 'slus/code10', 'code13')
    def test_unknown_row_cannot_manufacture_a_tu(self):
        with self.assertRaisesRegex(ValueError, 'not a registered'):
            S.select(self.root, 'slus/invented')
    def test_target_refuses_late_cells_and_fitted_flags(self):
        for cfg in ('2.8.1', '2.95.2', '2.7.2-cdk -fno-schedule-insns', '2.7.2-cdk -G0 -G8'):
            with self.subTest(cfg=cfg), self.assertRaises(ValueError):
                S.target_recipe(cfg, {'asflags': ''})
        self.assertEqual(S.target_recipe('2.7.2-cdk -G0', {'asflags': '--expand-div'}),
            {'ccver': '2.7.2-cdk', 'ccflags': '-G0', 'asflags': '--expand-div'})
    def test_no_recipe_drift_outside_selected_owner(self):
        old = 'build build/src/a.o: cc src/a.c\n  ccver = 2.8.1\n  ccflags = \n\nbuild build/src/b.o: cc src/b.c\n  ccver = 2.8.1\n  ccflags = \n'
        new = old.replace('2.8.1', '2.7.2-cdk')
        self.assertTrue(S.recipe_diff_ok(old, new, {'a'}))
        self.assertFalse(S.recipe_diff_ok(old, new, {'a', 'b'}))

class ImageTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.root = Path(self.temp.name)
        for directory in ('ledger/splits','config','build_slus/build','baserom'):
            (self.root / directory).mkdir(parents=True)
        self.image = b'full retail image'
        self.pin = b'whole physical recipe'
        self.put('ledger/splits/slus.build.ninja', self.pin)
        self.put('build_slus/build.ninja', self.pin)
        self.put('config/slus_006.14.sha1', (hashlib.sha1(self.image).hexdigest() + ' build/slus_006.14\n').encode())
        self.put('baserom/slus_006.14', self.image)
        self.put('build_slus/build/slus_006.14', self.image)
        self.put('build_slus/build/slus_006.14.ok', b'')
        self.gate = {'result':'MATCH', 'recipe_vs_pinned':'identical', 'recipe_sha256':hashlib.sha256(self.pin).hexdigest()}
        self.save_gate()
    def tearDown(self): self.temp.cleanup()
    def put(self, name, data): (self.root / name).write_bytes(data)
    def save_gate(self): self.put('ledger/gate_slus.jsonl', (json.dumps(self.gate) + '\n').encode())
    def test_requires_a_new_gate_record(self):
        with self.assertRaisesRegex(ValueError, 'no fresh'):
            S.image_evidence(self.root, 1)
        self.assertEqual(S.image_evidence(self.root, 0)['image_sha1'], hashlib.sha1(self.image).hexdigest())
    def test_forged_match_cannot_hide_changed_image(self):
        self.put('build_slus/build/slus_006.14', b'wrong image')
        with self.assertRaisesRegex(ValueError, 'independent SHA-1'):
            S.image_evidence(self.root, 0)
    def test_recipe_changes_after_gate_are_rejected(self):
        self.put('ledger/splits/slus.build.ninja', b'new pin')
        with self.assertRaisesRegex(ValueError, 'did not MATCH'):
            S.image_evidence(self.root, 0)
    def test_no_match_or_unpinned_recipe_refused(self):
        for key, value in [('result', 'NO MATCH'), ('recipe_vs_pinned', 'DIFFERS')]:
            original = self.gate[key];self.gate[key] = value;self.save_gate()
            with self.assertRaisesRegex(ValueError, 'did not MATCH'):
                S.image_evidence(self.root, 0)
            self.gate[key] = original
    def test_stamp_must_follow_image(self):
        import os
        os.utime(self.root / 'build_slus/build/slus_006.14.ok', ns=(1, 1))
        with self.assertRaisesRegex(ValueError, 'newer than'):
            S.image_evidence(self.root, 0)

class ReferenceTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory();self.root = Path(self.temp.name)
        self.cache = self.root / 'ledger/cache/slus_tu';self.cache.mkdir(parents=True)
        self.obj = self.root / 'build_slus/build/src/a.o';self.obj.parent.mkdir(parents=True)
        self.obj.write_bytes(b'gated whole owner')
        (self.cache / 'a.o').write_bytes(self.obj.read_bytes())
        self.recipe = {'ccver':'2.7.2-cdk','ccflags':'','asflags':''}
        self.rec = {'inputs_sha256':'inputs','recipe':self.recipe,'object_sha256':S.sha_file(self.obj)}
        self.save()
    def tearDown(self): self.temp.cleanup()
    def save(self): (self.cache / 'a.json').write_text(json.dumps(self.rec))
    def check(self, fingerprint='inputs'):
        with patch.object(S,'reference_inputs',return_value=fingerprint), \
             patch.object(S,'select',return_value={'recipe':self.recipe}), \
             patch.object(S,'image_evidence',return_value={'gate':'unit mock only'}):
            return S.verify_reference(self.root,'a')
    def test_modified_contributor_or_header_invalidates_reference(self):
        with self.assertRaisesRegex(ValueError,'inputs are stale'):
            self.check('changed sibling/header')
    def test_modified_cached_object_is_rejected(self):
        (self.cache / 'a.o').write_bytes(b'corrupt data or instructions')
        with self.assertRaisesRegex(ValueError,'object differs'): self.check()
    def test_modified_built_object_is_rejected(self):
        self.obj.write_bytes(b'corrupt built object')
        with self.assertRaisesRegex(ValueError,'object differs'): self.check()
    def test_reference_accepts_the_complete_gated_object(self):
        self.assertEqual(self.check()['result'],'MATCH')

class CliTests(OwnerFixture):
    def test_canonical_root_requires_live_even_for_trial(self):
        import contextlib,io
        stderr = io.StringIO()
        with patch.object(S,'LIVE',self.root), patch.object(S,'ROOT',self.root), \
             contextlib.redirect_stderr(stderr), self.assertRaises(SystemExit) as error:
            S.main(['--root',str(self.root),'--tu','code10','--to','2.7.2-cdk','--dry-run'])
        self.assertEqual(error.exception.code,2)
        self.assertIn('canonical live root requires --live (including trials)', stderr.getvalue())
    def test_dry_run_leaves_registered_inputs_unchanged(self):
        import contextlib,io
        def inventory():
            return {p.relative_to(self.root).as_posix():p.read_bytes()
                    for p in self.root.rglob('*') if p.is_file()}
        before = inventory()
        with patch.object(S,'ROOT',self.root), contextlib.redirect_stdout(io.StringIO()):
            self.assertEqual(S.main(['--root',str(self.root),'--row','slus/code5','--tu','code5','--to','2.7.2-cdk','--dry-run']),0)
        self.assertEqual(before,inventory())

class RollbackTests(unittest.TestCase):
    def test_reference_failure_rolls_back_recipe_source_and_trade(self):
        with tempfile.TemporaryDirectory() as name:
            root = Path(name)
            for directory in ('src/slus', 'tools/build', 'config', 'ledger/splits', 'ledger/cache', 'build_slus'):
                (root / directory).mkdir(parents=True)
            (root / 'src/slus/a.c').write_text('void a(void) {}\n')
            (root / 'tools/build/configure.py').write_text('registered recipe\n')
            (root / 'src/slus/INDEX.md').write_text('original index\n')
            (root / 'ledger/recipe_trades.jsonl').write_text('existing trade\n')
            tu = dict(stem='a', source='src/a.c', contributors=['slus/a'], module=None, parent=None,
                      recipe={'ccver':'2.8.1', 'ccflags':'', 'asflags':''})
            target = S.target_recipe('2.7.2-cdk', tu['recipe'])
            def mutate(*args):
                (root / 'tools/build/configure.py').write_text('changed recipe\n')
                (root / 'ledger/splits/slus.jsonl').write_text('changed ledger\n')
                (root / 'src/slus/INDEX.md').write_text('trial index\n')
                (root / 'ledger/cache/slus_obj.json').write_text('changed reference\n')
                return 'old', 'new'
            with patch.object(S, 'select', return_value=tu), patch.object(S, 'run', return_value=0), \
                 patch.object(S, 'image_evidence', return_value={'gate':'mocked unit test only'}), \
                 patch.object(S, 'stage', side_effect=mutate), \
                 patch.object(S, 'rederive', side_effect=ValueError('reference refused')):
                result = S.execute(root, tu, target, root / 'proof', apply=True)
            self.assertEqual(result['result'], 'ERROR')
            self.assertFalse(result['applied'])
            self.assertEqual((root / 'tools/build/configure.py').read_text(), 'registered recipe\n')
            self.assertEqual((root / 'ledger/recipe_trades.jsonl').read_text(), 'existing trade\n')
            self.assertEqual((root / 'src/slus/INDEX.md').read_text(),'original index\n')
            self.assertFalse((root / 'ledger/splits/slus.jsonl').exists())
            self.assertFalse((root / 'ledger/cache/slus_obj.json').exists())
    def test_registered_reference_refresh_rolls_back_both_caches_on_failure(self):
        with tempfile.TemporaryDirectory() as name:
            root=Path(name)
            for path in ('ledger/cache/slus_tu','build_slus/build/src'):
                (root/path).mkdir(parents=True)
            original=root/'ledger/cache/slus_obj.json';original.write_text('original ordinary cache')
            tu={'stem':'a','contributors':['slus/a']}
            def fail(*args):
                original.write_text('partial refresh')
                (root/'ledger/cache/slus_tu/a.json').write_text('partial physical cache')
                raise ValueError('reference comparison rejected')
            with patch.object(S,'reference_inputs',return_value='stable'), patch.object(S,'run',return_value=0), \
                 patch.object(S,'image_evidence',return_value={'gate':'unit mock only'}), patch.object(S,'rederive',side_effect=fail):
                with self.assertRaisesRegex(ValueError,'comparison rejected'):
                    S.refresh_reference(root,tu,root/'proof')
            self.assertEqual(original.read_text(),'original ordinary cache')
            self.assertFalse((root/'ledger/cache/slus_tu/a.json').exists())

    def test_symlink_authoritative_inputs_cannot_be_mutated(self):
        with tempfile.TemporaryDirectory() as name:
            root = Path(name); target = root / 'target';target.write_text('read only')
            link = root / 'input';link.symlink_to(target)
            with self.assertRaisesRegex(ValueError, 'symlinked'):
                S.snapshot([link])
            self.assertEqual(target.read_text(), 'read only')

if __name__ == '__main__': unittest.main()
