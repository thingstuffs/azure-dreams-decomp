"""Scoped configure must emit the same bytes as a fresh full enumeration."""
import contextlib
import io
import json
import os
from pathlib import Path
import subprocess
import tempfile
import types
import unittest
from unittest.mock import patch

from tools.build import mkbuild as B, content_cache
from tools.build.recipe_cache import RecipeCache, load


class ScopedConfigureTests(unittest.TestCase):
    def setUp(self):
        global M
        from gate import overlay_module_gate as M
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.state = self.root/'build/.state'
        for d in ('src', 'include', 'config', 'build_slus', 'build/.state'):
            (self.root/d).mkdir(parents=True, exist_ok=True)
        self.write('src/a.c', '#include "shared.h"\nint a;\n')
        self.write('src/b.c', '#include "shared.h"\nint b;\n')
        self.write('include/shared.h', '#include "leaf.h"\n')
        self.write('include/leaf.h', 'int leaf;\n')
        self.write('config/selection.json', '{"flag": "old"}')
        self.write('build_slus/build.ninja', '')
        self.calls = []

    def write(self, name, text):
        (self.root/name).write_text(text)

    def produce(self):
        """Small graph using the production checkpoint and closure paths."""
        selection = json.loads((self.root/'config/selection.json').read_text())
        commands, images = [], []
        for name in ('a', 'b'):
            def recipe():
                self.calls.append(name)
                return dict(source='src/'+name+'.c', flag=selection['flag'],
                            evidence=B.sha((self.root/'src'/ (name+'.c')).read_bytes()))
            spec = B.checkpoint('recipe:'+name, recipe)
            spec['dependencies'] = sorted(B.include_closure(M, self.root, [spec['source']]))
            key = B.sha(json.dumps(spec, sort_keys=True).encode())[:24]
            B.put(self.state/'recipes'/(key+'.json'), spec)
            B.put(self.state/'images'/(name+'.json'), dict(recipe=key))
            commands.append(B.rule(['obj/'+key], spec['dependencies'], 'cc '+spec['source']))
            images.append(name)
        B.put(self.state/'index.json', dict(inputs=['config/selection.json'], images=images))
        B.write(self.root/'build/build.mk', ''.join(commands))

    def generate(self, full=False):
        gate = types.SimpleNamespace(closure_snapshot=M.closure_snapshot)
        with patch.object(B, 'ROOT', self.root), patch.object(B, 'STATE', self.state), \
             patch.object(B, 'load_gate'), patch.object(B, '_generate', side_effect=self.produce), \
             patch.dict('sys.modules', overlay_module_gate=gate), contextlib.redirect_stdout(io.StringIO()):
            B.generate(full=full)

    def outputs(self):
        marker = json.loads((self.state/'configure.json').read_text())
        return {n: (self.root/n).read_bytes() for n in marker['outputs']
                if n != 'build/.state/configure-cache.json.gz'}

    def assert_full_equal(self):
        scoped = self.outputs()
        self.generate(full=True)
        self.assertEqual(scoped, self.outputs())

    def test_source_same_mtime_and_new_evidence_key_match_full(self):
        self.generate()
        self.calls.clear()
        p = self.root/'src/a.c'; st = p.stat()
        p.write_text(p.read_text()+'extern void stop(void);\n')
        os.utime(p, ns=(st.st_atime_ns, st.st_mtime_ns))
        self.generate()
        self.assertEqual(self.calls, ['a'])
        self.assert_full_equal()

    def test_header_closure_change_and_cycle_match_full(self):
        self.generate()
        self.calls.clear()
        self.write('include/shared.h', '#include "leaf.h"\n#include "shared.h"\n')
        self.generate()
        self.assertEqual(self.calls, [])
        self.assert_full_equal()

    def test_new_local_header_shadows_fallback_and_matches_full(self):
        self.generate()
        self.calls.clear()
        self.write('src/shared.h', 'int local;\n')
        self.generate()
        self.assertEqual(self.calls, ['a', 'b'])
        for p in (self.state/'recipes').glob('*.json'):
            if 'src/shared.h' in json.loads(p.read_text())['dependencies']:
                break
        else:
            self.fail('local include shadow was not discovered')
        self.assert_full_equal()

    def test_authority_edit_invalidates_all_records(self):
        self.generate(); self.calls.clear()
        self.write('config/selection.json', '{"flag": "new"}')
        self.generate()
        self.assertEqual(self.calls, ['a', 'b'])
        self.assert_full_equal()

    def test_sdk_availability_invalidates_the_unchanged_fast_path(self):
        self.generate(); self.calls.clear()
        for name in ('toolchain/genuine/bin/wibo', 'toolchain/genuine/psyq/psyq4.4/ASPSX.EXE'):
            p = self.root/name; p.parent.mkdir(parents=True, exist_ok=True); p.write_bytes(b'tool')
        self.generate()
        self.assertEqual(self.calls, ['a', 'b'])
        self.assert_full_equal()

    def test_missing_or_edited_generated_file_and_cache_force_full(self):
        self.generate()
        for name in ('build/build.mk', 'build/.state/configure-cache.json.gz', 'build/.state/images/a.json'):
            self.calls.clear()
            (self.root/name).write_bytes(b'tampered')
            self.generate()
            self.assertEqual(self.calls, ['a', 'b'])
            self.assert_full_equal()

    def test_symlink_and_environment_changes_force_full(self):
        self.generate(); self.calls.clear()
        p = self.root/'include/leaf.h'
        p.unlink(); p.symlink_to(self.root/'include/shared.h')
        self.generate()
        self.assertEqual(self.calls, ['a', 'b'])
        self.assert_full_equal()
        self.calls.clear()
        with patch.dict(os.environ, AZURE_SCOPED_TEST='changed'):
            self.generate()
        self.assertEqual(self.calls, ['a', 'b'])

    def test_owner_and_review_source_reads_are_record_dependencies(self):
        inputs = content_cache.hashes(self.root, content_cache.inventory(self.root, ('src', 'include', 'config')))
        cache = RecipeCache(self.root, inputs, {})
        def producer():
            return (self.root/'src/a.c').read_text() + (self.root/'src/b.c').read_text()
        original = cache.memo('projection', producer)
        saved_path = self.state/'cache.gz'; saved_path.write_bytes(cache.blob())
        self.write('src/b.c', 'int changed_owner;\n')
        changed = content_cache.hashes(self.root, inputs)
        next_cache = RecipeCache(self.root, changed, {}, load(saved_path))
        self.assertNotEqual(next_cache.memo('projection', producer), original)
        self.assertEqual(next_cache.misses, 1)

    def test_input_mutation_during_generation_cannot_publish_receipt(self):
        self.generate()
        marker = (self.state/'configure.json').read_bytes()
        self.write('src/a.c', 'int first_change;\n')
        original = self.produce
        def racing_producer():
            original()
            self.write('src/a.c', 'int second_change;\n')
        with patch.object(self, 'produce', side_effect=racing_producer):
            with self.assertRaisesRegex(ValueError, 'inputs changed during generation'):
                self.generate()
        self.assertEqual((self.state/'configure.json').read_bytes(), marker)

    def test_external_header_link_still_binds_its_logical_input(self):
        # Some configured include trees are links. Their bytes must remain a
        # dependency even when realpath lies outside the cache's root.
        nested = self.root/'nested'
        (nested/'include').mkdir(parents=True)
        header = self.root/'external.h'; header.write_text('int old;\n')
        (nested/'include/shared.h').symlink_to(header)
        before = content_cache.hashes(nested, ['include/shared.h'])
        cache = RecipeCache(nested, before, {})
        cache.memo('headers', lambda: ['include/shared.h'],
                   lambda found: [nested/n for n in found])
        saved = dict(guard=cache.guard, records=cache.records)
        header.write_text('int new;\n')
        next_cache = RecipeCache(nested, content_cache.hashes(nested, before), {}, saved)
        next_cache.memo('headers', lambda: ['include/shared.h'],
                        lambda found: [nested/n for n in found])
        self.assertEqual(next_cache.misses, 1)

    def test_review_and_optional_files_outside_inventory_are_bound(self):
        from gate_read_cache import observe
        (self.root/'reviews').mkdir()
        review = self.root/'reviews/review.json'; review.write_text('old review')
        optional = self.root/'reviews/optional.json'
        inputs = content_cache.hashes(self.root, ['src/a.c'])
        def producer():
            observe(optional)
            return review.read_text() + (optional.read_text() if optional.exists() else '')
        cache = RecipeCache(self.root, inputs, {})
        self.assertEqual(cache.memo('review', producer), 'old review')
        saved = dict(guard=cache.guard, records=cache.records)
        review.write_text('new review')
        cache = RecipeCache(self.root, inputs, {}, saved)
        self.assertEqual(cache.memo('review', producer), 'new review')
        self.assertEqual(cache.misses, 1)
        saved = dict(guard=cache.guard, records=cache.records)
        optional.write_text('new optional input')
        cache = RecipeCache(self.root, inputs, {}, saved)
        self.assertEqual(cache.memo('review', producer), 'new reviewnew optional input')
        self.assertEqual(cache.misses, 1)

    def test_undeclared_input_changed_after_record_is_rejected(self):
        (self.root/'reviews').mkdir()
        review = self.root/'reviews/input.json'; review.write_text('first')
        cache = RecipeCache(self.root, {}, {})
        cache.memo('review', lambda: review.read_text())
        self.assertTrue(cache.extra_unchanged())
        review.write_text('second')
        self.assertFalse(cache.extra_unchanged())

    def test_warm_fast_path_checks_undeclared_review_inputs(self):
        (self.root/'reviews').mkdir()
        review = self.root/'reviews/input.json'; review.write_text('first')
        original = self.produce
        def producer():
            original()
            value = B.checkpoint('review', lambda: review.read_text())
            B.put(self.state/'review.json', value)
        with patch.object(self, 'produce', side_effect=producer):
            self.generate(); self.calls.clear()
            st = review.stat(); review.write_text('second')
            os.utime(review, ns=(st.st_atime_ns, st.st_mtime_ns))
            self.generate()
            self.assertEqual(self.calls, [])
            self.assertEqual(json.loads((self.state/'review.json').read_text()), 'second')
            self.assert_full_equal()

    def test_cold_discovered_inputs_do_not_force_next_source_edit_full(self):
        (self.root/'vendor').mkdir()
        (self.root/'vendor/compiler').write_text('pinned compiler')
        original = self.produce
        def producer():
            original()
            B.put(self.state/'index.json', dict(inputs=['config/selection.json', 'vendor/compiler']))
        with patch.object(self, 'produce', side_effect=producer):
            self.generate(); self.calls.clear()
            self.write('src/a.c', '#include "shared.h"\nint changed;\n')
            self.generate()
            self.assertEqual(self.calls, ['a'])
            self.assert_full_equal()

    def test_new_header_during_generation_cannot_publish_receipt(self):
        self.generate()
        marker = (self.state/'configure.json').read_bytes()
        original = self.produce
        def producer():
            original()
            self.write('include/new_shadow.h', 'int late_header;\n')
        self.write('src/a.c', 'int changed;\n')
        with patch.object(self, 'produce', side_effect=producer):
            with self.assertRaisesRegex(ValueError, 'inventory changed during generation'):
                self.generate()
        self.assertEqual((self.state/'configure.json').read_bytes(), marker)

    def test_shared_recipe_codec_preserves_binding_types_and_image_order(self):
        value = dict(spec=dict(live=dict(base_names=['bank_a', 'bank_b'])),
                     plan=dict(rebind=dict(bindings={2:4, 100:8})),
                     artifacts={'build/.state/evidence/unit.txt':'bank_a\nbank_b\n'})
        images = dict(images=[['z', dict(units=[dict(rebind=dict(bindings={2:4,100:8}))])],
                              ['a', dict(units=[])]])
        cache = RecipeCache(self.root, {}, {})
        cache.records = {'row:a':dict(inputs={},value=value), 'row:b':dict(inputs={},value=value),
                         'images:layout':dict(inputs={},value=images)}
        path = self.state/'codec.gz'; path.write_bytes(cache.blob())
        decoded = load(path)
        self.assertEqual(decoded['records']['row:a']['value'], value)
        self.assertEqual(decoded['records']['row:b']['value'], value)
        self.assertEqual(decoded['records']['images:layout']['value'], images)
        self.assertEqual(json.dumps(decoded['records']['row:a']['value'], sort_keys=True),
                         json.dumps(value, sort_keys=True))


class InputSnapshotTests(unittest.TestCase):
    def test_reuses_only_within_invocation_and_rereads_same_mtime_edit(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td); p = root/'input'; p.write_bytes(b'old')
            snapshot = content_cache.Snapshot(root)
            import hashlib
            with patch.object(hashlib, 'file_digest', wraps=hashlib.file_digest) as reads:
                first = snapshot.hashes(['input'])
                self.assertEqual(snapshot.hashes(['input']), first)
                self.assertEqual(reads.call_count, 1)
                st = p.stat(); p.write_bytes(b'new')
                os.utime(p, ns=(st.st_atime_ns, st.st_mtime_ns))
                self.assertNotEqual(snapshot.hashes(['input']), first)
                self.assertEqual(reads.call_count, 2)
                content_cache.Snapshot(root).hashes(['input'])
                self.assertEqual(reads.call_count, 3)

    def test_input_changed_while_reading_is_rejected(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td); p = root/'input'; p.write_bytes(b'old')
            import hashlib
            original = hashlib.file_digest
            def racing_read(*args):
                value = original(*args); p.write_bytes(b'new'); return value
            with patch.object(hashlib, 'file_digest', side_effect=racing_read):
                with self.assertRaisesRegex(ValueError, 'changed while hashing'):
                    content_cache.Snapshot(root).hashes(['input'])


class ScopedBootstrapTests(unittest.TestCase):
    def test_source_read_set_contains_canonical_symlink_target(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            for d in ('src', 'config/overlays'):
                (root/d).mkdir(parents=True, exist_ok=True)
            (root/'src/review.c').write_text('int storage;')
            (root/'src/alias.c').symlink_to(root/'src/review.c')
            (root/'config/overlays/modules.json').write_text(json.dumps(dict(modules=[dict(review_inputs=['src/alias.c'])])))
            (root/'config/slus_modules.json').write_text('{"modules":[]}')
            with patch.object(B, 'ROOT', root):
                names = B.bootstrap_source_inputs()
            self.assertIn('src/alias.c', names)
            self.assertIn('src/review.c', names)

    def test_source_only_reuses_views_but_sensitive_and_authority_edits_do_not(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td); state = root/'build/.state'
            for d in ('src', 'config', 'build_slus/build', 'build/.state'):
                (root/d).mkdir(parents=True, exist_ok=True)
            ordinary = root/'src/a.c'; ordinary.write_text('int a;')
            sensitive = root/'src/review.c'; sensitive.write_text('int reviewed;')
            (root/'config/authority.json').write_text('{}')
            calls = []
            def views():
                calls.append(1)
                (root/'build_slus/build.ninja').write_text('constant recipes')
                (root/'build_slus/build/slus_006.14.ld').write_text('constant layout')
            with patch.object(B, 'ROOT', root), patch.object(B, 'STATE', state), \
                 patch.object(B, '_bootstrap', side_effect=views), \
                 patch.object(B, 'bootstrap_source_inputs', return_value=['src/review.c']), \
                 contextlib.redirect_stdout(io.StringIO()):
                B.bootstrap()
                ordinary.write_text('int changed;')
                B.bootstrap(); self.assertEqual(len(calls), 1)
                st = sensitive.stat(); sensitive.write_text('int changed_review;')
                os.utime(sensitive, ns=(st.st_atime_ns, st.st_mtime_ns))
                B.bootstrap(); self.assertEqual(len(calls), 2)
                (root/'config/authority.json').write_text('{"changed":true}')
                B.bootstrap(); self.assertEqual(len(calls), 3)
                (root/'src/new.h').write_text('int new;')
                B.bootstrap(); self.assertEqual(len(calls), 4)
                ordinary.write_text('int again;')
                (root/'build_slus/build.ninja').write_text('corrupt output')
                B.bootstrap(); self.assertEqual(len(calls), 5)


@unittest.skipUnless(os.environ.get('AZURE_MAKE_SCOPED_EQUIVALENCE') == '1',
                     'opt-in production full-enumeration comparison')
class ProductionEqualityTests(unittest.TestCase):
    def test_current_projection_is_byte_identical_to_full_regeneration(self):
        root = Path(__file__).resolve().parents[2]
        env = dict(os.environ)
        # The opt-in test selector is not a production configuration input.
        # Passing it through would invalidate the scoped result before testing it.
        env.pop('AZURE_MAKE_SCOPED_EQUIVALENCE', None)
        subprocess.run(['python3', 'tools/build/mkbuild.py', 'generate'], cwd=root, env=env, check=True)
        marker = json.loads((root/'build/.state/configure.json').read_text())
        expected = {n: d for n, d in marker['outputs'].items()
                    if n != 'build/.state/configure-cache.json.gz'}
        subprocess.run(['python3', 'tools/build/mkbuild.py', 'generate', 'full'], cwd=root, env=env, check=True)
        after = json.loads((root/'build/.state/configure.json').read_text())
        actual = {n: d for n, d in after['outputs'].items()
                  if n != 'build/.state/configure-cache.json.gz'}
        self.assertEqual(expected, actual)
        self.assertEqual(expected, content_cache.hashes(root, expected))


if __name__ == '__main__':
    unittest.main()
