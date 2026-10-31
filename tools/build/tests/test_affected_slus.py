"""Source-view provenance survives a seeded graph without disposable symlinks."""
import json
import os
from pathlib import Path
import shutil
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))
sys.path.insert(0, str(Path(__file__).resolve().parent))
from tools.build import affected as A
from test_affected import FakeTree, SHA, put


class SlusSourceViewTests(unittest.TestCase):
    OWNER = 'src/engine/menu/create_animated_selection_menu_owner.c'
    VIEW = 'build_slus/src/w_8004F5F4.c'
    FLAT = 'build_slus/layout_flat/slus/w_8004F5F4.c'
    RID = 'ab2faf73a4b429f5af433c11'

    def setUp(self):
        (ROOT / 'tmp').mkdir(exist_ok=True)
        self.tmp = Path(tempfile.mkdtemp(dir=ROOT / 'tmp'))
        self.root = self.tmp / 'candidate'
        FakeTree(self.root)
        put(self.root / self.OWNER, 'int create_owner(void) { return 1; }\n')
        put(self.root / 'include/engine/menu.h', 'int create_owner(void);\n')
        # Production recipe identity and command shape. SLUS has no `source` field.
        self.recipe = dict(command='tools/cc.sh src/w_8004F5F4.c build/src/w_8004F5F4.o 2.7.2-cdk "" ""',
                           output='build_slus/build/src/w_8004F5F4.o',
                           dependencies=[self.VIEW, 'build_slus/include/engine/menu.h'])
        self.add_slus(self.RID, self.recipe)
        self.origin = self.tmp / 'original'
        self.links = {
            self.VIEW: str(self.origin / self.FLAT),
            self.FLAT: str(self.origin / self.OWNER),
            'build_slus/include': str(self.origin / 'include'),
            'build_ovl/include': str(self.origin / 'include'),
            'build_ovl/src': str(self.origin / 'src'),
            'build_ovl/overlays/dungeon_engine/first_pass_matched': str(
                self.origin / 'build_ovl/layout_flat/dungeon'),
            'build_ovl/layout_flat/dungeon/owner.c': str(self.origin / self.OWNER),
        }
        self.configure()

    def tearDown(self):
        shutil.rmtree(self.tmp)

    def configure(self):
        put(self.root / 'build/.state/configure.json', dict(root=str(self.origin), links=self.links))

    def add_slus(self, rid, recipe):
        state = self.root / 'build/.state'
        put(state / ('slus-recipes/' + rid + '.json'), recipe)
        index = json.loads((state / 'index.json').read_text())
        index['slus_recipes'].append('build/.state/slus-recipes/' + rid + '.json')
        put(state / 'index.json', index)

    def scope(self, *names):
        return A.affected_set(self.root, names)

    def bind(self, name, target):
        path = self.root / name
        path.parent.mkdir(parents=True, exist_ok=True)
        if path.is_symlink():
            path.unlink()
        path.symlink_to(target)

    def test_batch5_source_reaches_slus_without_materialized_views(self):
        scope = self.scope(self.OWNER)
        self.assertEqual(scope['slus_recipes'], [self.RID])
        self.assertEqual(scope['own'][self.OWNER], [self.RID])
        self.assertEqual(scope['images'], ['slus/slus_bin'])
        self.assertEqual(scope['unconsumed'], [])
        self.assertFalse((self.root / self.VIEW).exists())  # set stays read-only

    def test_absent_include_directory_view_reaches_header(self):
        (self.root / 'build_slus/include').unlink()
        self.assertEqual(self.scope('include/engine/menu.h')['slus_recipes'], [self.RID])

    def test_relative_multihop_links_and_parent_components(self):
        self.links[self.VIEW] = '../layout_flat/slus/w_8004F5F4.c'
        self.links[self.FLAT] = '../../../' + self.OWNER
        self.configure()
        self.assertEqual(self.scope(self.OWNER)['slus_recipes'], [self.RID])

    def test_directory_symlink_is_resolved_before_dotdot(self):
        self.links['build_slus/alias'] = '../include/engine'
        self.configure()
        self.assertEqual(A.Graph(self.root).real('build_slus/alias/../x.h'), 'include/x.h')

    def test_seeded_absolute_links_to_original_root_are_rebased(self):
        self.bind(self.VIEW, self.origin / self.FLAT)
        self.assertEqual(self.scope(self.OWNER)['slus_recipes'], [self.RID])

    def test_live_symlinks_without_configure_receipt_still_work(self):
        (self.root / 'build/.state/configure.json').unlink()
        self.bind(self.VIEW, self.root / self.FLAT)
        self.bind(self.FLAT, self.root / self.OWNER)
        self.assertEqual(self.scope(self.OWNER)['slus_recipes'], [self.RID])

    def test_compile_source_is_indexed_without_a_dependency_entry(self):
        self.recipe['dependencies'] = []
        put(self.root / ('build/.state/slus-recipes/' + self.RID + '.json'), self.recipe)
        self.assertEqual(self.scope(self.OWNER)['slus_recipes'], [self.RID])

    def test_wrapper_include_dependency_in_another_view(self):
        wrapper = 'build_slus/src/collector.c'
        put(self.root / wrapper, '#include "../../build_ovl/src/engine/menu/create_animated_selection_menu_owner.c"\n')
        self.add_slus('wrapper', dict(command='tools/cc.sh src/collector.c build/collector.o 2.7.2 "" ""',
            output='build_slus/build/collector.o', dependencies=[wrapper, 'build_ovl/' + self.OWNER]))
        self.assertEqual(self.scope(self.OWNER)['slus_recipes'], [self.RID, 'wrapper'])

    def generated_pair(self, cycle=False):
        a, b = 'build_slus/build/outer.c', 'build_slus/build/inner.c'
        with (self.root / 'build/build.mk').open('a') as mk:
            mk.write('%s build_slus/build/outer.h &: %s\n\t@echo outer\n' % (a, b))
            mk.write('%s build_slus/build/inner.h &: %s %s\n\t@echo inner\n' % (b, self.VIEW, a if cycle else ''))
        self.add_slus('nested', dict(command='tools/cc.sh build/outer.c build/outer.o 2.7.2 "" ""',
            output='build_slus/build/outer.o', dependencies=[a]))

    def test_nested_generated_bodies_reach_original_source(self):
        self.generated_pair()
        self.assertEqual(self.scope(self.OWNER)['slus_recipes'], [self.RID, 'nested'])

    def test_generated_cycle_does_not_loop(self):
        self.generated_pair(cycle=True)
        self.assertIn('nested', self.scope(self.OWNER)['slus_recipes'])

    def test_nested_producers_render_in_dependency_order(self):
        self.generated_pair()
        graph = A.Graph(self.root)
        self.assertEqual([g['command'] for g in graph.render_groups(['nested'])],
                         ['echo inner', 'echo outer'])

    def test_cyclic_producers_are_refused_before_rendering(self):
        self.generated_pair(cycle=True)
        with self.assertRaisesRegex(ValueError, 'cyclic generated source'):
            A.Graph(self.root).render_groups(['nested'])

    def test_generated_parents_are_checked_for_foreign_views(self):
        self.generated_pair()
        put(self.origin / self.OWNER, (self.root / self.OWNER).read_text())
        self.bind(self.VIEW, self.origin / self.OWNER)
        graph = A.Graph(self.root)
        self.assertIn('another source', graph.view_problem(graph.recipes['nested']))

    def test_overlay_flat_gate_view_and_placement_owner(self):
        alias = 'build_ovl/overlays/dungeon_engine/first_pass_matched/owner.c'
        put(self.root / 'build/.state/recipes/projected.json', dict(
            source='build/.state/enumerate/member/owner.c', output='build/obj/projected.o',
            wrapper='build_ovl/tools/cc.sh', dependencies=[], projection=dict(owner=alias, home='dungeon/owner')))
        with (self.root / 'build/build.mk').open('a') as mk:
            mk.write('build/obj/projected.o: x\n\t@true\n')
        scope = self.scope(self.OWNER)
        self.assertEqual(scope['recipes'], ['projected'])
        self.assertIn('projected', scope['own'][self.OWNER])

    def test_external_target_with_similar_prefix_is_not_rebased(self):
        self.links['build_slus/external'] = str(self.origin) + '-other/include'
        self.configure()
        self.assertEqual(A.Graph(self.root).real('build_slus/external/x.h'),
                         str(self.origin) + '-other/include/x.h')

    def test_cyclic_source_view_is_an_error(self):
        self.links[self.VIEW] = str(self.origin / self.VIEW)
        self.configure()
        with self.assertRaisesRegex(ValueError, 'cyclic source view'):
            self.scope(self.OWNER)

    def test_prove_refuses_absent_views_before_compiling(self):
        report = A.prove(self.root, [self.OWNER], compile_tasks=lambda task: self.fail('absent compile'))
        self.assertEqual(report['verdict'], 'ERROR')
        self.assertIn('source view missing', report['error'])

    def test_prove_refuses_foreign_source_view_before_compiling(self):
        put(self.origin / self.OWNER, (self.root / self.OWNER).read_text())
        self.bind(self.VIEW, self.origin / self.OWNER)
        report = A.prove(self.root, [self.OWNER], compile_tasks=lambda task: self.fail('foreign compile'))
        self.assertEqual(report['verdict'], 'ERROR')
        self.assertIn('another source', report['error'])

    def test_prove_checks_compile_source_without_a_dependency_entry(self):
        self.recipe['dependencies'] = []
        put(self.root / ('build/.state/slus-recipes/' + self.RID + '.json'), self.recipe)
        report = A.prove(self.root, [self.OWNER], compile_tasks=lambda task: self.fail('absent compile'))
        self.assertEqual(report['verdict'], 'ERROR')
        self.assertIn(self.VIEW, report['error'])

    def test_retargeted_live_source_is_selected_then_refused(self):
        other = 'src/engine/menu/retargeted_owner.c'
        put(self.root / other, 'int other_owner(void) { return 2; }\n')
        self.bind(self.VIEW, self.root / other)
        scope = self.scope(other)
        self.assertEqual(scope['slus_recipes'], [self.RID])
        self.assertEqual(scope['own'][other], [self.RID])
        report = A.prove(self.root, [other], compile_tasks=lambda task: self.fail('retargeted compile'))
        self.assertEqual(report['verdict'], 'ERROR')
        self.assertIn('another source', report['error'])

    def test_changed_slus_object_reaches_image_and_identical_object_passes(self):
        self.bind(self.VIEW, self.root / self.OWNER)
        output = self.root / self.recipe['output']
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_bytes(b'old object')
        put(output.with_suffix('.proof.json'), dict(object_sha256=SHA(output.read_bytes()),
            inputs={n: SHA((self.root / n).read_bytes()) for n in self.recipe['dependencies']}))
        def compile_task(task):
            path = self.root / task['run'] / 'obj/test.o'
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(self.produced)
            return dict(object=str(path), seconds=0)
        self.produced = b'changed object'
        changed = A.prove(self.root, [self.OWNER], compile_tasks=compile_task)
        self.assertEqual(changed['verdict'], 'CHANGED')
        self.assertEqual(changed['images']['slus/slus_bin']['verdict'], 'CHANGED')
        self.produced = output.read_bytes()
        equal = A.prove(self.root, [self.OWNER], compile_tasks=compile_task)
        self.assertEqual(equal['verdict'], 'PASS')
        self.assertEqual(equal['images']['slus/slus_bin']['verdict'], 'PASS')


if __name__ == '__main__':
    unittest.main()
