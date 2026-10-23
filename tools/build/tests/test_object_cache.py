"""Cache portability, invalidation, atomic publication, integrity and LRU bounds."""
import json
import os
from pathlib import Path
import tempfile
import types
import unittest
from unittest.mock import patch

from tools.build import object_cache as C

_SAVED_ENV = {}


def setUpModule():
    # Tests assume default switches; a landing may export AZURE_* overrides.
    for key in [k for k in os.environ if k.startswith('AZURE_')]:
        _SAVED_ENV[key] = os.environ.pop(key)
    # Exercise the lane configuration (the launcher switches both on).
    os.environ['AZURE_OBJECT_CACHE'] = '1'
    os.environ['AZURE_COMPILE_LIMIT_ENABLED'] = '1'


def tearDownModule():
    os.environ.pop('AZURE_OBJECT_CACHE', None)
    os.environ.pop('AZURE_COMPILE_LIMIT_ENABLED', None)
    os.environ.update(_SAVED_ENV)

REAL_DEPENDENCY_INPUTS = C.dependency_inputs


class CacheTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)/'root'
        for directory in ('src', 'include', 'config', 'build/.state', 'toolchain'):
            (self.root/directory).mkdir(parents=True)
        for name, text in {'src/a.c': '#include "a.h"\nint a;\n', 'include/a.h': 'int b;\n',
                           'config/names.tsv': '', 'toolchain/cc1': 'compiler',
                           'build/.state/compiletools.list': '["build/tool.py"]',
                           'build/tool.py': 'tool closure'}.items():
            (self.root/name).write_text(text)
        self.recipe = self.root/'build/recipe.json'
        self.spec = dict(source='src/a.c', output='build/a.o', args=['2.7.2', '-O2'],
                         dependencies=['src/a.c', 'include/a.h', 'toolchain/cc1'])
        self.recipe.write_text(json.dumps(self.spec))
        self.directory = Path(self.temp.name)/'cache'
        self.addCleanup(patch.stopall)
        patch('tools.link.prepare.load_gate').start()
        patch.object(C, 'dependency_inputs', return_value=dict(files=[], preprocessed={})).start()
        patch.dict('sys.modules', overlay_module_gate=types.SimpleNamespace(
            closure=lambda root, starts: {'include/a.h', 'src/a.c'})).start()
        patch.dict(os.environ, AZURE_OBJECT_CACHE_DIR=str(self.directory),
                   AZURE_COMPILE_LIMIT_ENABLED='0', AZURE_OBJECT_VERIFY='0').start()

    def key(self, root=None):
        root = root or self.root
        return C.key_for(C.key_inputs(root, root/'build/recipe.json', self.spec))

    def test_default_cache_is_shared_by_live_lander_and_external_lane(self):
        with patch.dict(os.environ, {}, clear=True):
            live = C.cache_directory(Path('/repos/game'))
            with patch.object(Path, 'exists', return_value=True):
                lane = C.cache_directory(Path('/repos/azure-lanes/lane/root'))
            self.assertEqual(live, lane)

    def test_source_header_compiler_flags_and_tool_closure_invalidate(self):
        first = self.key()
        for name in ('src/a.c', 'include/a.h', 'toolchain/cc1', 'build/tool.py', 'config/names.tsv'):
            path = self.root/name
            before = path.read_bytes()
            path.write_bytes(before+b' changed')
            self.assertNotEqual(first, self.key(), name)
            path.write_bytes(before)
        self.spec['args'].append('-G0')
        self.assertNotEqual(first, self.key())

    def test_key_portable_across_roots_and_mtime_only_edits(self):
        import shutil
        other = Path(self.temp.name)/'other'
        shutil.copytree(self.root, other)
        os.utime(other/'src/a.c', (1, 1))
        self.assertEqual(self.key(), self.key(other))

    def test_volatile_macros_and_header_environment_bypass(self):
        (self.root/'include/a.h').write_text('char *p = __FILE__;')
        self.assertIsNone(C.key_inputs(self.root, self.recipe, self.spec))
        (self.root/'include/a.h').write_text('int a;')
        with patch.dict(os.environ, CPATH='untracked'):
            self.assertIsNone(C.key_inputs(self.root, self.recipe, self.spec))

    def test_maspsx_scalar_switches_bind_keys_and_manifest_hooks_bypass(self):
        first = self.key()
        with patch.dict(os.environ, MASPSX_GP_LIMIT_FROM_CC1='1'):
            self.assertNotEqual(first, self.key())
        with patch.dict(os.environ, MASPSX_SHAPE_D_MANIFEST='untracked.json'):
            self.assertIsNone(C.key_inputs(self.root, self.recipe, self.spec))

    def test_real_selected_compiler_binds_macro_selected_header_and_expansion(self):
        compiler = Path(C.__file__).resolve().parents[2]/'toolchain/compilers/gcc-2.7.2-cdk'
        if not compiler.exists():
            self.skipTest('pinned compiler unavailable')
        directory = self.root/'toolchain/compilers'
        directory.mkdir()
        (directory/'gcc-2.7.2-cdk').symlink_to(compiler, target_is_directory=True)
        (self.root/'src/a.c').write_text('#if PICK\n#define HEADER "one.h"\n#else\n#define HEADER "two.h"\n#endif\n#include HEADER\nint a = SELECTED;\n')
        (self.root/'include/one.h').write_text('#define SELECTED 1\n')
        (self.root/'include/two.h').write_text('#define SELECTED 2\n')
        spec = dict(self.spec, args=['2.7.2-cdk', '-DPICK=1'])
        before = REAL_DEPENDENCY_INPUTS(self.root, spec)
        self.assertIn('include/one.h', before['files'])
        self.assertNotIn('include/two.h', before['files'])
        (self.root/'include/one.h').write_text('#define SELECTED 3\n')
        self.assertNotEqual(before['preprocessed'], REAL_DEPENDENCY_INPUTS(self.root, spec)['preprocessed'])
        spec['args'][1] = '-DPICK=0'
        self.assertIn('include/two.h', REAL_DEPENDENCY_INPUTS(self.root, spec)['files'])

    def test_emitted_assembler_strings_and_recursive_binary_inputs(self):
        (self.root/'include/labels.inc').write_text('.include "include/nested.inc"\n')
        (self.root/'include/nested.inc').write_text('.incbin "include/blob.bin", 0, 1\n')
        (self.root/'include/blob.bin').write_bytes(b'payload')
        text = r'__asm__(".include \"" "include/labels.inc" "\"\n");'
        result = C.assembly_inputs(self.root, text, self.root)
        self.assertEqual(result, {'include/labels.inc', 'include/nested.inc', 'include/blob.bin'})
        self.assertIsNone(C.assembly_inputs(self.root, '.include unknown_macro\n', self.root))
        self.assertEqual(C.assembly_inputs(self.root, 'label: .include \"include/labels.inc\"\n', self.root), result)
        self.assertIsNone(C.assembly_inputs(self.root, '.altmacro\n', self.root))

    def test_stock_label_macros_are_cacheable_but_include_visibility_is_not(self):
        labels = Path(C.__file__).resolve().parents[2]/'include/labels.inc'
        (self.root/'include/labels.inc').write_bytes(labels.read_bytes())
        (self.root/'include/gte_macros.inc').write_text('')
        prefix = '.include "include/labels.inc"\n'
        self.assertEqual(C.assembly_inputs(self.root, prefix+'glabel target,local\n', self.root),
                         {'include/labels.inc', 'include/gte_macros.inc'})
        for call in ('glabel "file" include', 'glabel "file", include',
                     'glabel visibility=include,label="file"'):
            self.assertIsNone(C.assembly_inputs(self.root, prefix+call, self.root))

    def test_absent_native_defaults_bind_presence(self):
        self.spec.update(assembler='genuine_aspsx_verified', module={'container': 'main'})
        first = self.key()
        (self.root/'config/noreturn_syms.main.txt').write_text('symbol\n')
        self.assertNotEqual(first, self.key())
        (self.root/'config/noreturn_syms.main.txt').unlink()
        (self.root/'config/noreturn_syms.txt').write_text('global_symbol\n')
        self.assertNotEqual(first, self.key())

    def test_live_closure_added_header_changes_key(self):
        first = self.key()
        (self.root/'include/new.h').write_text('new input')
        with patch.dict('sys.modules', overlay_module_gate=types.SimpleNamespace(
                closure=lambda root, starts: {'include/new.h', 'include/a.h', 'src/a.c'})):
            self.assertNotEqual(first, self.key())

    def fixture(self, value=b'object'):
        output = self.root/'build/a.o'
        output.write_bytes(value)
        output.with_suffix('.proof.json').write_text('{}')
        inputs = {'source': 'digest'}
        key = C.key_for(inputs)
        outputs = C.artifacts(self.spec)
        C.publish(self.directory, key, inputs, self.root, outputs)
        return key, inputs, outputs

    def test_publish_restore_and_duplicate_publish_are_atomic(self):
        key, inputs, outputs = self.fixture()
        (self.root/'build/a.o').unlink()
        self.assertTrue(C.restore(self.directory, key, inputs, self.root, outputs))
        self.assertEqual((self.root/'build/a.o').read_bytes(), b'object')
        C.publish(self.directory, key, inputs, self.root, outputs)
        self.assertFalse(list(self.directory.glob('.publish-*')))
        self.assertEqual(len(list(self.directory.glob('[0-9a-f]'*64))), 1)

    def test_corruption_and_wrong_inputs_refused(self):
        key, inputs, outputs = self.fixture()
        with self.assertRaisesRegex(ValueError, 'manifest'):
            C.restore(self.directory, key, {}, self.root, outputs)
        (self.directory/key/'0').write_bytes(b'wrong')
        with self.assertRaisesRegex(ValueError, 'corrupt'):
            C.restore(self.directory, key, inputs, self.root, outputs)

    def test_lru_prune_respects_access_and_cap(self):
        first, inputs, outputs = self.fixture()
        other = dict(inputs, source='new')
        second = C.key_for(other)
        C.publish(self.directory, second, other, self.root, outputs)
        os.utime(self.directory/first/'manifest.json', (1, 1))
        os.utime(self.directory/second/'manifest.json', (2, 2))
        C.restore(self.directory, first, inputs, self.root, outputs)
        size = sum(p.stat().st_size for p in (self.directory/first).iterdir())
        result = C.prune(self.directory, size)
        self.assertEqual(result['removed'], 1)
        self.assertTrue((self.directory/first).exists())
        self.assertFalse((self.directory/second).exists())
        self.assertEqual(C.prune(self.directory, 0)['bytes'], 0)

    def test_verify_recompiles_hit_and_rejects_different_bytes(self):
        calls = []
        def build():
            calls.append(1)
            (self.root/'build/a.o').write_bytes(b'good')
            (self.root/'build/a.proof.json').write_text('{}')
        C.compile_recipe(self.root, self.recipe, build)
        C.compile_recipe(self.root, self.recipe, build)
        self.assertEqual(len(calls), 1)
        with patch.dict(os.environ, AZURE_OBJECT_VERIFY='100'):
            C.compile_recipe(self.root, self.recipe, build)
            self.assertEqual(len(calls), 2)
            def bad():
                build()
                (self.root/'build/a.o').write_bytes(b'bad')
            with self.assertRaisesRegex(ValueError, 'verification differs'):
                C.compile_recipe(self.root, self.recipe, bad)
        self.assertFalse(any(p.is_dir() for p in self.directory.iterdir()))

    def test_inputs_changed_during_compile_never_publish(self):
        def build():
            (self.root/'src/a.c').write_text('changed')
        with self.assertRaisesRegex(ValueError, 'inputs changed'):
            C.compile_recipe(self.root, self.recipe, build)
        self.assertFalse(any(p.is_dir() for p in self.directory.iterdir()))

    def test_slus_piece_side_outputs_are_bound(self):
        spec = dict(self.spec, command='python3 tools/slus_data_pieces.py')
        self.assertIn('build/a.unsplit.o', C.artifacts(spec))
        self.assertIn('build/a.data-pieces.json', C.artifacts(spec))


if __name__ == '__main__':
    unittest.main()
