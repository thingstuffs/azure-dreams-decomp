"""Cache portability, invalidation, atomic publication, integrity and LRU bounds."""
import json
import multiprocessing
import os
from pathlib import Path
import tempfile
import types
import unittest
import subprocess
import sys
from unittest.mock import patch

from tools.build import object_cache as C, name_inputs as N


def locked_restore(directory, key, inputs, root, outputs, pipe):
    """A separate process must not see a partly published/restored variant."""
    pipe.send('started')
    entry = C.restore(directory, key, inputs, root, outputs)
    pipe.send(bool(entry))
    pipe.close()


def concurrent_publish(directory, key, inputs, root, outputs, pipe):
    pipe.send(C.publish(directory, key, inputs, root, outputs).name)
    pipe.close()

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
        self.directory = Path(self.temp.name)/'cache'/('v'+str(C.SCHEMA))
        self.directory.mkdir(parents=True)
        (self.directory/'bytes').write_text('0')
        self.addCleanup(patch.stopall)
        patch('tools.link.prepare.load_gate').start()
        patch.object(C, 'dependency_inputs', return_value=dict(files=[], preprocessed={})).start()
        patch.dict('sys.modules', overlay_module_gate=types.SimpleNamespace(
            closure=lambda root, starts: {'include/a.h', 'src/a.c'})).start()
        patch.dict(os.environ, AZURE_OBJECT_CACHE_DIR=str(self.directory.parent),
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

    def test_schema_namespace_isolates_older_prune_accounting(self):
        self.assertEqual(C.cache_directory(self.root), self.directory)
        (self.directory.parent/'bytes').write_text('999999')
        self.fixture()
        self.assertEqual((self.directory.parent/'bytes').read_text(), '999999')
        self.assertGreater(int((self.directory/'bytes').read_text()), 0)

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

    def test_unrelated_lint_and_typing_edits_preserve_key(self):
        first = self.key()
        for name in ('tools/lint/debt_check.py', 'tools/typing/abi_facts.py'):
            path = self.root/name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text('review tool changed')
            self.assertEqual(first, self.key(), name)

    def test_compile_driver_comment_preserves_key_but_code_edit_invalidates(self):
        path = self.root/'tools/build/mkbuild.py'
        path.parent.mkdir(parents=True)
        path.write_text('def compile_one():\n    return 1\n')
        (self.root/'build/.state/compiletools.list').write_text('["build/tool.py", "tools/build/mkbuild.py"]')
        first = self.key()
        path.write_text('# explanation\ndef compile_one():\n    return 1\n')
        self.assertEqual(first, self.key())
        path.write_text('def compile_one():\n    return 2\n')
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

    def test_real_unused_header_declaration_preserves_schema3_key(self):
        compiler = Path(C.__file__).resolve().parents[2]/'toolchain/compilers/gcc-2.7.2-cdk'
        if not compiler.exists():
            self.skipTest('pinned compiler unavailable')
        directory = self.root/'toolchain/compilers'
        directory.mkdir()
        (directory/'gcc-2.7.2-cdk').symlink_to(compiler, target_is_directory=True)
        (self.root/'src/a.c').write_text('#include "a.h"\nint f(void) { return 1; }\n')
        (self.root/'include/a.h').write_text('extern int unused(void);\n')
        self.spec['args'] = ['2.7.2-cdk', '-G0']
        with patch.object(C, 'dependency_inputs', side_effect=REAL_DEPENDENCY_INPUTS):
            first = C.key_inputs(self.root, self.recipe, self.spec)
            self.assertEqual(first['inputs']['include/a.h'], 'C-header-present')
            (self.root/'include/a.h').write_text('extern int another_unused(void);\n')
            second = C.key_inputs(self.root, self.recipe, self.spec)
            self.assertEqual(C.key_for(first), C.key_for(second))
            (self.root/'src/a.c').write_text('#include "a.h"\nint f(void) { return another_unused(); }\n')
            self.assertNotEqual(C.key_for(second), C.key_for(C.key_inputs(self.root, self.recipe, self.spec)))

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

    def native_compile(self):
        calls, build = self.traced_compile()
        self.spec.update(assembler='genuine_aspsx_verified', module=dict(
            container='main', allocations=[dict(slots=[dict(symbol='owned')])]))
        self.recipe.write_text(json.dumps(self.spec))
        return calls, build

    def test_native_reverse_alias_misses_bind_future_rows_and_allow_unused_edits(self):
        calls, build = self.native_compile()
        self.compile(build)
        first = self.key()
        before = C.table_snapshot(self.root, self.spec)
        table = self.root/'config/names.tsv'
        table.write_text('slus\tother\tunused\n')
        self.assertEqual(first, self.key())
        self.assertNotEqual(before, C.table_snapshot(self.root, self.spec))
        self.compile(build)
        self.assertEqual(len(calls), 1)
        self.assertEqual(N.read(self.root/self.spec['name_input'])['reverse'], {'owned': []})
        table.write_text('slus\tother\tunused\nslus\towned\tnewOwnedAlias\n')
        self.compile(build)
        self.assertEqual(len(calls), 2)
        self.assertEqual(N.read(self.root/self.spec['name_input'])['rows'], {})
        self.assertEqual(N.read(self.root/self.spec['name_input'])['reverse'], {'owned': ['newOwnedAlias']})

    def test_native_reverse_alias_projection_preserves_shadowed_raw_rows(self):
        calls, build = self.native_compile()
        table = self.root/'config/names.tsv'
        table.write_text('slus\towned\tshared\nslus\tother\tshared\n')
        names = N.table(table)
        self.compile(build)
        table.write_text('slus\tthird\tshared\nslus\tother\tshared\n')
        self.assertEqual(names, N.table(table))
        self.compile(build)
        self.assertEqual(len(calls), 2)

    def test_missing_native_reverse_evidence_never_publishes(self):
        _, build = self.native_compile()
        def incomplete():
            build()
            path = self.root/self.spec['name_input']
            value = N.read(path)
            del value['reverse']
            N.write(path, value)
        with self.assertRaisesRegex(ValueError, 'name witness'):
            self.compile(incomplete)
        self.assertEqual(C.entry_sizes(self.directory), [])

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

    def entry(self, key):
        return next((self.directory/key).iterdir())

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
        (self.entry(key)/'0').write_bytes(b'wrong')
        with self.assertRaisesRegex(ValueError, 'corrupt'):
            C.restore(self.directory, key, inputs, self.root, outputs)

    def test_lru_prune_respects_access_and_cap(self):
        first, inputs, outputs = self.fixture()
        other = dict(inputs, source='new')
        second = C.key_for(other)
        C.publish(self.directory, second, other, self.root, outputs)
        os.utime(self.entry(first)/'manifest.json', (1, 1))
        os.utime(self.entry(second)/'manifest.json', (2, 2))
        C.restore(self.directory, first, inputs, self.root, outputs)
        size = sum(p.stat().st_size for p in self.entry(first).iterdir())
        result = C.prune(self.directory, size)
        self.assertEqual(result['removed'], 1)
        self.assertTrue((self.directory/first).exists())
        self.assertFalse((self.directory/second).exists())
        self.assertEqual(C.prune(self.directory, 0)['bytes'], 0)

    def test_over_cap_prunes_to_low_watermark(self):
        first, inputs, outputs = self.fixture()
        size = sum(p.stat().st_size for p in self.entry(first).iterdir())
        with patch.object(C.subprocess, 'Popen') as spy:
            C.enforce_cap(self.directory, size)
            spy.assert_not_called()
            C.enforce_cap(self.directory, size-1)
            spy.assert_called_once()
            command = spy.call_args.args[0]
            self.assertEqual(command[-2:], ['--max-bytes', str((size-1)*3//4)])
            self.assertTrue(spy.call_args.kwargs['start_new_session'])

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

    def traced_compile(self, configs=False):
        self.spec['name_input'] = 'build/names.json'
        self.spec['dependencies'] += [self.spec['name_input'], 'config/names.tsv']
        if configs:
            self.spec['config_tables'] = dict(MASPSX_NORETURN_FILE='config/noreturn_syms.txt',
                                              MASPSX_SIBCALL_FILE='config/sibcall_syms.txt')
        self.recipe.write_text(json.dumps(self.spec))
        calls = []
        def build():
            calls.append(1)
            names = N.table(self.root/'config/names.tsv')
            value = N.witness(['.ent used\n', 'used:\n', 'jal missing\n', '.end used\n'], names,
                              N.evidence_at(self.root, self.spec.get('config_tables', {}).values()))
            if 'module' in self.spec:
                value['reverse'] = N.project_reverse(N.reverse_symbols(self.spec['module']), self.root)
            N.write(self.root/self.spec['name_input'], value)
            payload = [value['rows'], value['sets']]
            if 'reverse' in value:
                payload.append(value['reverse'])
            (self.root/'build/a.o').write_bytes(C.encode(payload))
            (self.root/'build/a.proof.json').write_text('{}')
        return calls, build

    def compile(self, build):
        C.compile_recipe(self.root, self.recipe, build)

    def test_names_unused_row_hits_used_row_misses_and_previous_variant_survives(self):
        calls, build = self.traced_compile()
        table = self.root/'config/names.tsv'
        table.write_text('slus\tfunc_80010000\tused\n')
        first = self.key()
        self.compile(build)
        original = (self.root/'build/a.o').read_bytes()
        table.write_text(table.read_text() + 'slus\tfunc_80020000\tunused\n')
        self.assertEqual(first, self.key())
        # A configure placeholder is not authority for what a cached TU read.
        N.write(self.root/self.spec['name_input'], dict(schema=1, tokens=[], rows={}, sets={}))
        self.compile(build)
        self.assertEqual(len(calls), 1)
        self.assertIn('used', N.read(self.root/self.spec['name_input'])['tokens'])
        table.write_text('slus\tfunc_80030000\tused\n')
        self.compile(build)
        self.assertEqual(len(calls), 2)
        self.assertNotEqual(original, (self.root/'build/a.o').read_bytes())
        self.assertEqual(len(list((self.directory/first).iterdir())), 2)
        table.write_text('slus\tfunc_80010000\tused\n')
        self.compile(build)
        self.assertEqual(len(calls), 2)
        self.assertEqual(original, (self.root/'build/a.o').read_bytes())
        table.write_text('')
        self.compile(build)
        self.assertEqual(len(calls), 3)

    def test_missing_name_becoming_a_mapping_must_miss(self):
        calls, build = self.traced_compile()
        self.compile(build)
        self.assertNotIn('missing', N.read(self.root/self.spec['name_input'])['rows'])
        (self.root/'config/names.tsv').write_text('slus\tfunc_80010000\tmissing\n')
        self.compile(build)
        self.assertEqual(len(calls), 2)

    def test_canonical_section_second_lookup_must_miss(self):
        calls, build = self.traced_compile()
        table = self.root/'config/names.tsv'
        table.write_text('slus\tfunc_80010000\tused\n')
        self.compile(build)
        self.assertIn('func_80010000', N.read(self.root/self.spec['name_input'])['tokens'])
        table.write_text(table.read_text() + 'slus\tfunc_80020000\tfunc_80010000\n')
        self.compile(build)
        self.assertEqual(len(calls), 2)

    def test_config_projection_binds_canonical_membership_and_absent_table(self):
        calls, build = self.traced_compile(configs=True)
        (self.root/'config/names.tsv').write_text('slus\tfunc_80010000\tused\n')
        self.compile(build)
        first = self.key()
        path = self.root/'config/noreturn_syms.txt'
        path.write_text('unrelated\n')
        self.assertEqual(first, self.key())
        self.compile(build)
        self.assertEqual(len(calls), 1)
        path.write_text('unrelated\nfunc_80010000\n')
        self.compile(build)
        self.assertEqual(len(calls), 2)
        path.write_text('unrelated\n')
        self.compile(build)
        self.assertEqual(len(calls), 2)
        (self.root/'config/sibcall_syms.txt').write_text('missing\n')
        self.compile(build)
        self.assertEqual(len(calls), 3)

    def test_corrupt_witness_manifest_and_blob_are_rejected(self):
        calls, build = self.traced_compile()
        self.compile(build)
        entry = self.entry(self.key())
        manifest = entry/'manifest.json'
        original = manifest.read_bytes()
        value = json.loads(original)
        value['name_witness']['tokens'] = []
        manifest.write_bytes(C.encode(value))
        with self.assertRaisesRegex(ValueError, 'manifest'):
            self.compile(build)
        manifest.write_bytes(original)
        index = C.artifacts(self.spec).index(self.spec['name_input'])
        (entry/str(index)).write_text('{}')
        with self.assertRaisesRegex(ValueError, 'corrupt.*witness'):
            self.compile(build)
        self.assertEqual(len(calls), 1)

    def test_missing_config_evidence_is_never_published(self):
        _, build = self.traced_compile(configs=True)
        def incomplete():
            build()
            value = N.read(self.root/self.spec['name_input'])
            value['sets'] = {}
            N.write(self.root/self.spec['name_input'], value)
        with self.assertRaisesRegex(ValueError, 'name witness'):
            self.compile(incomplete)
        self.assertEqual(C.entry_sizes(self.directory), [])

    def test_table_edit_during_compile_never_publishes(self):
        _, build = self.traced_compile()
        def changing():
            build()
            (self.root/'config/names.tsv').write_text('slus\tfunc_80010000\tmissing\n')
        with self.assertRaisesRegex(ValueError, 'inputs changed'):
            self.compile(changing)
        self.assertEqual(C.entry_sizes(self.directory), [])

    def test_verify_ignores_unused_edit_and_evicts_only_the_bad_variant(self):
        calls, build = self.traced_compile()
        self.compile(build)
        table = self.root/'config/names.tsv'
        table.write_text('slus\tfunc_80010000\tused\n')
        self.compile(build)
        table.write_text(table.read_text() + 'slus\tfunc_80020000\tunused\n')
        with patch.dict(os.environ, AZURE_OBJECT_VERIFY='100'):
            self.compile(build)
            self.assertEqual(len(calls), 3)
            def bad():
                build()
                (self.root/'build/a.o').write_bytes(b'wrong')
            with self.assertRaisesRegex(ValueError, 'verification differs'):
                self.compile(bad)
        self.assertEqual(len(list((self.directory/self.key()).iterdir())), 1)
        table.write_text('')
        self.compile(build)
        self.assertEqual(len(calls), 4)

    def test_restore_waits_for_process_lock(self):
        key, inputs, outputs = self.fixture()
        context = multiprocessing.get_context('spawn')
        parent, child = context.Pipe()
        with C.locked(self.directory):
            process = context.Process(target=locked_restore,
                                      args=(self.directory, key, inputs, self.root, outputs, child))
            process.start()
            self.assertTrue(parent.poll(5))
            self.assertEqual(parent.recv(), 'started')
            self.assertFalse(parent.poll(0.1))
        try:
            self.assertTrue(parent.poll(5))
            self.assertTrue(parent.recv())
        finally:
            process.join(5)
            if process.is_alive():
                process.terminate()
                process.join()
            parent.close()
            child.close()
        self.assertEqual(process.exitcode, 0)

    def test_prune_counts_each_variant_and_legacy_entries(self):
        _, build = self.traced_compile()
        self.compile(build)
        (self.root/'config/names.tsv').write_text('slus\tfunc_80010000\tused\n')
        self.compile(build)
        legacy = self.directory/('a'*64)
        legacy.mkdir()
        (legacy/'manifest.json').write_text('{}')
        (legacy/'0').write_bytes(b'legacy')
        self.assertEqual(len(C.entry_sizes(self.directory)), 3)
        self.assertEqual(C.prune(self.directory, 0)['removed'], 3)
        self.assertFalse((self.directory/self.key()).exists())

    def test_concurrent_publish_preserves_both_variants_and_deduplicates(self):
        import shutil
        _, build = self.traced_compile()
        build()
        inputs = C.key_inputs(self.root, self.recipe, self.spec)
        key, outputs = C.key_for(inputs), C.artifacts(self.spec)
        other = Path(self.temp.name)/'other'
        shutil.copytree(self.root, other)
        (other/'config/names.tsv').write_text('slus\tfunc_80010000\tused\n')
        witness = N.witness(['.ent used\n', 'used:\n', 'jal missing\n', '.end used\n'],
                            N.table(other/'config/names.tsv'))
        N.write(other/self.spec['name_input'], witness)
        (other/'build/a.o').write_bytes(C.encode([witness['rows'], witness['sets']]))
        context = multiprocessing.get_context('spawn')
        processes, pipes = [], []
        try:
            for root in (self.root, other, self.root):
                parent, child = context.Pipe()
                process = context.Process(target=concurrent_publish,
                    args=(self.directory, key, inputs, root, outputs, child))
                processes.append(process)
                pipes.append((parent, child))
                process.start()
            variants = []
            for process, (parent, _) in zip(processes, pipes):
                self.assertTrue(parent.poll(10))
                variants.append(parent.recv())
                process.join(10)
                self.assertEqual(process.exitcode, 0)
            self.assertEqual(len(set(variants)), 2)
            self.assertEqual(len(list((self.directory/key).iterdir())), 2)
            self.assertTrue(C.restore(self.directory, key, inputs, self.root, outputs))
            self.assertTrue(C.restore(self.directory, key, inputs, other, outputs))
            self.assertEqual((other/'build/a.o').read_bytes(), C.encode([witness['rows'], witness['sets']]))
            self.assertFalse(list(self.directory.glob('.publish-*')))
        finally:
            for process in processes:
                if process.is_alive():
                    process.terminate()
                process.join()
            for parent, child in pipes:
                parent.close()
                child.close()

    def test_table_read_as_assembler_data_still_binds_complete_bytes(self):
        self.traced_compile()
        with patch.object(C, 'dependency_inputs', return_value=dict(
                files=['config/names.tsv'], preprocessed={})):
            first = self.key()
            (self.root/'config/names.tsv').write_text('slus\tfunc_80010000\tunused\n')
            self.assertNotEqual(first, self.key())

    def test_native_reverse_witness_refresh_and_verify(self):
        path = self.root/'build/reverse.json'
        value = N.witness(['.ent used\n'], {})
        value['reverse'] = {'owned': []}
        N.write(path, value)
        N.verify(path, {}, self.root)
        table = self.root/'config/names.tsv'
        table.write_text('slus\towned\tnewOwnedAlias\n')
        with self.assertRaisesRegex(ValueError, 'reverse-name'):
            N.verify(path, N.table(table), self.root)
        N.refresh(path, N.table(table), self.root)
        self.assertEqual(N.verify(path, N.table(table), self.root)['reverse'], {'owned': ['newOwnedAlias']})

    def test_native_second_ccproc_pass_retains_section_lookups_and_checks_races(self):
        table = self.root/'config/names.tsv'
        table.write_text('slus\tfunc_80010000\tused\n')
        trace = self.root/'build/native.trace'
        ccproc = Path(C.__file__).with_name('ccproc.py')
        env = dict(os.environ, CCPROC_NAMES_TRACE=str(trace), CCPROC_CONFIG_ROOT=str(self.root),
                   CCPROC_CONFIG_TABLES='[]', CCPROC_NAMES_MERGE='1')
        command = [sys.executable, str(ccproc), '--names-tsv', str(table)]
        assembly = '.ent used\nused:\njr $31\nnop\n.end used\n'
        for flags in ([], ['--names-only']):
            subprocess.run(command+flags, input=assembly, text=True, capture_output=True, check=True, env=env)
        self.assertIn('func_80010000', N.read(trace)['tokens'])
        table.write_text('slus\tfunc_80020000\tused\n')
        result = subprocess.run(command+['--names-only'], input=assembly, text=True, capture_output=True, env=env)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('changed between traces', result.stderr)


if __name__ == '__main__':
    unittest.main()
