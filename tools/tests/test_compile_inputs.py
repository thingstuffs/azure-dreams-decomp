"""Name-table dependency boundaries and content-preserving generation."""
import contextlib
import importlib.util
import io
import json
import os
from pathlib import Path
import shlex
import shutil
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

from tools.build import mkbuild as B, name_inputs as N, compile_tools as T
from tools.build import export_gate_tools as X


class NameInputsTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.names = self.root/'names.tsv'
        self.state = self.root/'names.json'
        self.names.write_text('0x1\tfunc_1\treadable\tevidence\n')

    def test_default_config_rows_use_canonical_assembly_symbols(self):
        config = self.root/'config'; config.mkdir()
        path = config/'noreturn_syms.txt'; path.write_text('func_1\n')
        table = N.table(self.names)
        N.write(self.state, N.witness(['jal readable\n'], table,
            {'config/noreturn_syms.txt': N.symbols(path)}))
        self.assertEqual(N.read(self.state)['sets'], {'config/noreturn_syms.txt': ['func_1']})
        before = self.state.stat().st_mtime_ns
        path.write_text('func_1 # new evidence\nunused\n')
        N.refresh(self.state, table, self.root)
        self.assertEqual(before, self.state.stat().st_mtime_ns)
        path.write_text('unused\n')
        with self.assertRaisesRegex(ValueError, 'stale config-input'):
            N.verify(self.state, table, self.root)
        N.refresh(self.state, table, self.root)
        self.assertEqual(N.read(self.state)['sets'], {'config/noreturn_syms.txt': []})

    def test_absent_default_config_binds_future_symbol_rows(self):
        (self.root/'config').mkdir()
        path = self.root/'config/sibcall_syms.txt'
        table = N.table(self.names)
        N.write(self.state, N.witness(['jal readable\n'], table,
            {'config/sibcall_syms.txt': N.symbols(path)}))
        path.write_text('func_1\n')
        with self.assertRaisesRegex(ValueError, 'stale config-input'):
            N.verify(self.state, table, self.root)

    def test_lookup_misses_bind_future_rows_and_removals(self):
        N.write(self.state, N.witness(['jal later\n'], N.table(self.names)))
        before = self.state.read_bytes()
        self.names.write_text(self.names.read_text()+'0x2\tfunc_2\tlater\tproof\n')
        with self.assertRaisesRegex(ValueError, 'stale name-input'):
            N.verify(self.state, N.table(self.names))
        N.refresh(self.state, N.table(self.names))
        self.assertNotEqual(before, self.state.read_bytes())
        self.assertEqual(N.read(self.state)['rows'], {'later': 'func_2'})
        self.names.write_text('')
        with self.assertRaisesRegex(ValueError, 'stale name-input'):
            N.verify(self.state, N.table(self.names))

    def test_unrelated_rows_and_evidence_edits_preserve_mtime(self):
        N.write(self.state, N.witness(['jal readable\n'], N.table(self.names)))
        before = self.state.stat().st_mtime_ns
        self.names.write_text('0x3\tfunc_3\tunused\tx\n0x1\tfunc_1\treadable\tnew proof\n')
        N.refresh(self.state, N.table(self.names))
        self.assertEqual(before, self.state.stat().st_mtime_ns)

    def test_strings_are_opaque_but_word_boundaries_and_comments_match_ccproc(self):
        value = N.witness(['.ascii "readable"\n', '.asciz "readable"\n',
                           '.string "readable"\n', 'jal readable_suffix # readable\n'],
                          N.table(self.names))
        self.assertEqual(value['rows'], {'readable': 'func_1'})
        value = N.witness(['jal readable_suffix\n', '.ascii "readable"\n'], N.table(self.names))
        self.assertEqual(value['rows'], {})

    def test_effective_duplicate_precedence_matches_ccproc(self):
        self.names.write_text(self.names.read_text()+'0x2\tfunc_2\treadable\tnew\n')
        self.assertEqual(N.witness(['jal readable\n'], N.table(self.names))['rows'],
                         {'readable': 'func_2'})

    def test_invalid_identifier_is_refused_instead_of_underbinding(self):
        self.names.write_text('0x1\tfunc_1\tnot.an.identifier\tx\n')
        with self.assertRaisesRegex(ValueError, 'invalid name-table identifier'):
            N.table(self.names)

    def test_poisoned_dependency_is_detected_independently(self):
        N.write(self.state, N.witness(['jal readable\n'], N.table(self.names)))
        value = N.read(self.state)
        value['rows']['readable'] = 'func_WRONG'
        N.write(self.state, value)
        with self.assertRaisesRegex(ValueError, 'stale name-input'):
            N.verify(self.state, N.table(self.names))

    def test_corrupt_vocabulary_is_refused(self):
        self.state.write_text('{"schema":1,"tokens":["a","a"],"rows":{}}')
        with self.assertRaisesRegex(ValueError, 'invalid name-input'):
            N.refresh(self.state, {})

    def test_missing_table_binds_future_presence(self):
        self.names.unlink()
        N.write(self.state, N.witness(['jal readable\n'], N.table(self.names)))
        self.names.write_text('0x1\tfunc_1\treadable\tevidence\n')
        with self.assertRaisesRegex(ValueError, 'stale name-input'):
            N.verify(self.state, N.table(self.names))


class CcprocTraceTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        (self.root/'tools').mkdir()
        (self.root/'config').mkdir()
        shutil.copyfile(N.__file__, self.root/'tools/name_inputs.py')
        # Normal installed layout; the staged test runner supplies its draft.
        ccproc = Path(os.environ.get('FASTLAND3_TEST_CCPROC', str(B.ROOT/'tools/build/ccproc.py')))
        shutil.copyfile(ccproc, self.root/'tools/ccproc.py')
        self.names = self.root/'config/names.tsv'
        self.names.write_text('0x1\tfunc_1\treadable\tevidence\n')
        self.trace = self.root/'trace.json'

    def ccproc(self, text, *flags):
        result = subprocess.run([sys.executable, str(self.root/'tools/ccproc.py'), *flags],
            input=text, text=True, capture_output=True, check=True,
            env=dict(os.environ, CCPROC_NAMES_TRACE=str(self.trace)))
        return result.stdout

    def test_trace_does_not_change_canonicalized_output(self):
        text = '.ent readable\nreadable:\njal readable\n.ascii "readable"\n.end readable\n'
        output = self.ccproc(text)
        self.assertIn('.text.func_1', output)
        self.assertIn('jal func_1', output)
        self.assertIn('.ascii "readable"', output)
        self.assertEqual(N.read(self.trace)['rows'], {'readable': 'func_1'})

    def test_canonical_section_lookup_binds_a_later_alias_row(self):
        text = '.ent readable\nreadable:\n.end readable\n'
        self.ccproc(text)
        old = self.trace.read_bytes()
        self.names.write_text(self.names.read_text()+'0x2\tfunc_2\tfunc_1\tx\n')
        with self.assertRaisesRegex(ValueError, 'stale name-input'):
            N.verify(self.trace, N.table(self.names))
        self.assertIn('.text.func_2', self.ccproc(text))
        self.assertNotEqual(old, self.trace.read_bytes())

    def test_names_only_native_path_has_the_same_witness(self):
        self.assertEqual(self.ccproc('jal readable\n', '--names-only'), 'jal func_1\n')
        self.assertEqual(N.read(self.trace)['rows'], {'readable': 'func_1'})

    def test_pasted_identifier_is_seen_after_preprocessing(self):
        if not shutil.which('cc'):
            self.skipTest('host C preprocessor unavailable')
        source = '#define CAT(a,b) a ## b\nvoid CAT(read,able)(void) {}\n'
        cooked = subprocess.run(['cc', '-E', '-P', '-x', 'c', '-'], input=source,
                                text=True, capture_output=True, check=True).stdout
        self.ccproc(cooked, '--names-only')
        self.assertEqual(N.read(self.trace)['rows'], {'readable': 'func_1'})

    def test_runtime_trace_publishes_only_after_success(self):
        state = self.root/'state.json'
        with patch.object(B, 'ROOT', self.root):
            with B.name_trace(state) as trace:
                env_before = os.environ['CCPROC_NAMES_TRACE']
                self.ccproc('jal readable\n')
                # ccproc() uses its own named trace in this fixture.
                Path(trace).write_bytes(self.trace.read_bytes())
            self.assertEqual(N.verify(state, N.table(self.names))['rows'], {'readable': 'func_1'})
            before = state.read_bytes()
            with self.assertRaisesRegex(RuntimeError, 'compiler failure'):
                with B.name_trace(state):
                    raise RuntimeError('compiler failure')
            self.assertEqual(before, state.read_bytes())
        self.assertNotIn('CCPROC_NAMES_TRACE', os.environ)


class CompileToolClosureTests(unittest.TestCase):
    def test_lazy_imports_follow_called_functions_and_skip_other_commands(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root/'entry.py').write_text('import worker\nworker.compile()\n')
            (root/'worker.py').write_text('def compile():\n import live\ndef report():\n import reporting\n')
            (root/'live.py').write_text('')
            (root/'reporting.py').write_text('')
            self.assertEqual(T.closure(root, ('entry.py',)), ['entry.py', 'live.py', 'worker.py'])

    def test_import_closure_includes_package_initializers_and_new_imports(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root/'tools/build').mkdir(parents=True)
            (root/'tools/build/entry.py').write_text('from package.sub import value\n')
            (root/'package').mkdir()
            (root/'package/__init__.py').write_text('import other\n')
            (root/'package/sub.py').write_text('value = 1\n')
            (root/'other.py').write_text('')
            (root/'tools/build/test_unrelated.py').write_text('raise RuntimeError\n')
            expected = ['other.py', 'package/__init__.py', 'package/sub.py', 'tools/build/entry.py']
            self.assertEqual(T.closure(root, ('tools/build/entry.py',)), expected)
            (root/'other.py').write_text('from package import added\n')
            (root/'package/added.py').write_text('')
            self.assertIn('package/added.py', T.closure(root, ('tools/build/entry.py',)))

    def test_importing_a_test_fails_closed(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root/'tools/build').mkdir(parents=True)
            (root/'tools/build/entry.py').write_text('import test_accident\n')
            (root/'tools/build/test_accident.py').write_text('')
            with self.assertRaisesRegex(ValueError, 'imports a test'):
                T.closure(root, ('tools/build/entry.py',))

    def test_production_closure_contains_no_name_table_or_test_files(self):
        result = T.inputs(B.ROOT)
        self.assertNotIn('config/names.tsv', result)
        self.assertIn('tools/build/ccproc.py', result)
        self.assertIn('build_ovl/tools/ccproc.py', result)
        self.assertIn('toolchain/maspsx/maspsx.py', result)
        self.assertFalse(any('tests' in Path(n).parts or Path(n).name.startswith('test_') for n in result))
        self.assertNotIn('tools/fidelity/aspsx_report.py', result)
        self.assertNotIn('tools/fidelity/certify_overlay_module.py', result)
        self.assertNotIn('tools/build/gate_all.py', result)
        self.assertNotIn('tools/build/export_gate_tools.py', result)

    def test_unregistered_runtime_import_fails_closed(self):
        import types
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            state = root/'build/.state'; state.mkdir(parents=True)
            (root/'tools').mkdir()
            path = root/'tools/hidden.py'; path.write_text('')
            (state/'compiletools.list').write_text('[]')
            with patch.object(B, 'ROOT', root), patch.object(B, 'STATE', state), \
                 patch.object(B, 'COMPILE_IMPORTS', set()), \
                 patch.dict(sys.modules, _hidden_compile_dependency=types.SimpleNamespace(__file__=str(path))):
                with self.assertRaisesRegex(ValueError, 'compile import missing'):
                    B.compiler_imports()

    def test_unregistered_view_import_fails_closed(self):
        import types
        with tempfile.TemporaryDirectory() as td:
            root = Path(td); state = root/'build/.state'; state.mkdir(parents=True)
            path = root/'build_ovl/tools/injected.py'; path.parent.mkdir(parents=True)
            path.write_text('')
            (state/'compiletools.list').write_text('[]')
            with patch.object(B, 'ROOT', root), patch.object(B, 'STATE', state), \
                 patch.object(B, 'COMPILE_IMPORTS', {str(path)}):
                with self.assertRaisesRegex(ValueError, 'compile import missing'):
                    B.compiler_imports()


@unittest.skipUnless(shutil.which('make'), 'GNU Make unavailable')
class NameMakeTests(unittest.TestCase):
    def test_only_consumers_rebuild_for_added_changed_and_unused_name_rows(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td); state = root/'build/.state'
            (root/'tools').mkdir(); (root/'config').mkdir(); (root/'src').mkdir()
            state.mkdir(parents=True)
            ccproc = Path(os.environ.get('FASTLAND3_TEST_CCPROC', str(B.ROOT/'tools/build/ccproc.py')))
            shutil.copyfile(ccproc, root/'tools/ccproc.py')
            shutil.copyfile(N.__file__, root/'tools/name_inputs.py')
            wrapper = root/'tools/cc.sh'
            wrapper.write_text('#!/bin/sh\npython3 tools/ccproc.py < "$1" > "$2"\n')
            wrapper.chmod(0o755)
            (root/'src/a.c').write_text('.ent later\nlater:\njal later\n.end later\n')
            (root/'src/b.c').write_text('.ent other\nother:\n.end other\n')
            names = root/'config/names.tsv'; names.write_text('')
            repo = B.ROOT
            # Load the implementation under test in each make child, including
            # a staged implementation when this test is run before installation.
            driver = (
                'import importlib.util,sys; from pathlib import Path; '
                'sys.path.insert(0,' + repr(str(repo)) + '); import tools.build; '
                'files=' + repr([(n, str(m.__file__)) for n, m in
                    [('name_inputs', N), ('compile_tools', T), ('mkbuild', B)]]) + '; '
                '\nfor n,p in files:\n'
                ' s=importlib.util.spec_from_file_location("tools.build."+n,p); '
                'm=importlib.util.module_from_spec(s); sys.modules[s.name]=m; '
                'setattr(tools.build,n,m); s.loader.exec_module(m)\n'
                'm.ROOT=Path.cwd(); m.STATE=m.ROOT/"build/.state"; m.compile_one(sys.argv[1])')
            driver_path = root/'compile-driver.py'
            driver_path.write_text(driver)
            with patch.object(B, 'ROOT', root), patch.object(B, 'STATE', state):
                specs = []
                for name in ('a', 'b'):
                    output = 'build/obj/'+name+'.o'
                    name_input = B.name_dependency(output, {})
                    path = state/'recipes'/(name+'.json')
                    spec = dict(source='src/'+name+'.c', wrapper='tools/cc.sh', args=[], env={},
                                output=output, name_input=name_input,
                                dependencies=['src/'+name+'.c', B.rel(path), name_input])
                    B.put(path, spec); specs.append((path, spec))
                rules = ''.join(B.rule([s['output']], s['dependencies'],
                    shlex.join([sys.executable, str(driver_path), str(p)])) for p, s in specs)
                B.write(root/'Makefile', 'all: build/obj/a.o build/obj/b.o\n'+rules)

                def make():
                    return subprocess.run(['make', '--no-print-directory'], cwd=root,
                        text=True, capture_output=True, check=True).stdout

                def refresh():
                    for _, spec in specs:
                        B.name_dependency(spec['output'], N.table(names))

                self.assertEqual(make().count('CC '), 2)
                old_b = (root/'build/obj/b.o').stat().st_mtime_ns
                names.write_text('0x1\tfunc_1\tunused\tx\n')
                refresh()
                self.assertNotIn('CC ', make())
                names.write_text(names.read_text()+'0x2\tfunc_2\tlater\tx\n')
                refresh()
                self.assertEqual(make().count('CC '), 1)
                self.assertIn('jal func_2', (root/'build/obj/a.o').read_text())
                self.assertEqual(old_b, (root/'build/obj/b.o').stat().st_mtime_ns)
                names.write_text(names.read_text().replace('func_2', 'func_3'))
                refresh()
                self.assertEqual(make().count('CC '), 1)
                self.assertIn('jal func_3', (root/'build/obj/a.o').read_text())
                self.assertEqual(old_b, (root/'build/obj/b.o').stat().st_mtime_ns)


class GeneratedContentTests(unittest.TestCase):
    def test_inline_provenance_binds_only_its_selected_row_and_refuses_ambiguity(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td); state = root/'build/.state'
            rows = {'town/a': [dict(member_id='town/a', offset=10)],
                    'town/b': [dict(member_id='town/b', offset=20)]}
            with patch.object(B, 'ROOT', root), patch.object(B, 'STATE', state):
                name = B.projection_dependency('town/a', 'a', rows)
                path = root/name; before = path.stat().st_mtime_ns
                rows['town/b'][0]['offset'] = 30
                B.projection_dependency('town/a', 'a', rows)
                self.assertEqual(before, path.stat().st_mtime_ns)
                self.assertEqual(B.read(path), rows['town/a'])
                rows['town/a'].append(dict(member_id='town/a', offset=40))
                with self.assertRaisesRegex(ValueError, 'unique inline provenance'):
                    B.projection_dependency('town/a', 'a', rows)
                self.assertEqual(B.read(path), [dict(member_id='town/a', offset=10)])

    def test_self_served_evidence_preserves_mtime(self):
        from tools.gate import overlay_evidence as E
        with tempfile.TemporaryDirectory() as td:
            with patch.object(E, 'candidate_noreturn_syms', return_value={'own'}), \
                 patch.object(E, 'evidence_env', return_value={}), \
                 patch.object(E, 'family_for', return_value='main'), \
                 patch.object(E, 'load_noreturn_file', return_value=set()):
                first = E.evidence_env_with_candidate('main', 'candidate', td)
                path = Path(first['MASPSX_NORETURN_FILE'])
                before = path.stat().st_mtime_ns
                self.assertEqual(first, E.evidence_env_with_candidate('main', 'candidate', td))
                self.assertEqual(before, path.stat().st_mtime_ns)

    def test_exported_rows_preserve_mtime(self):
        from tools import row_db
        import types
        with tempfile.TemporaryDirectory() as td:
            root = Path(td); splits = root/'splits'; splits.mkdir()
            (splits/'town.jsonl').write_text('{"func":"f"}\n')
            with patch.object(row_db, 'SPLITS', splits), patch.object(row_db, 'CONTAINERS', ('town',)), \
                 contextlib.redirect_stdout(io.StringIO()):
                args = types.SimpleNamespace(root=root/'view')
                row_db.cmd_export(args)
                path = root/'view/overlays/town/overlay_first_pass_results.json'
                before = path.stat().st_mtime_ns
                row_db.cmd_export(args)
                self.assertEqual(before, path.stat().st_mtime_ns)

    def test_generated_content_imports_work_in_isolation(self):
        result = subprocess.run([sys.executable, '-m', 'unittest',
            __name__ + '.GeneratedContentTests.test_self_served_evidence_preserves_mtime',
            __name__ + '.GeneratedContentTests.test_exported_rows_preserve_mtime'],
            cwd=Path(__file__).resolve().parents[2], capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

    def test_link_product_acknowledges_its_published_name_witness(self):
        import types
        with tempfile.TemporaryDirectory() as td:
            root = Path(td); state = root/'build/.state'; state.mkdir(parents=True)
            (root/'config').mkdir(); (root/'config/names.tsv').write_text('0x1\tfunc_1\treadable\tx\n')
            spec = dict(tag='test', output='build/image.bin', name_input='build/.state/names.json')
            path = state/'image.json'
            gate = types.SimpleNamespace(renamed_symbols=lambda: {})
            with patch.object(B, 'ROOT', root), patch.object(B, 'STATE', state):
                B.put(path, spec)
                def link(_):
                    gate.renamed_symbols().get('readable')
                    (root/spec['output']).write_bytes(b'image')
                    B.put(state/'origins/test.json', {})
                with patch.object(B, 'load_gate', return_value=gate), patch.object(B, '_image_one', side_effect=link):
                    B.image_one(path)
                self.assertEqual(N.read(root/spec['name_input'])['rows'], {'readable': 'func_1'})
                self.assertGreaterEqual((root/spec['output']).stat().st_mtime_ns,
                                        (root/spec['name_input']).stat().st_mtime_ns)
                before = (root/spec['name_input']).stat().st_mtime_ns
                N.refresh(root/spec['name_input'], N.table(root/'config/names.tsv'), root)
                self.assertEqual(before, (root/spec['name_input']).stat().st_mtime_ns)

    def test_recipes_evidence_images_and_fragments_keep_identical_mtimes(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            with patch.object(B, 'ROOT', root):
                for name in ('build/.state/recipes/a.json', 'build/.state/images/a.json',
                             'build/.state/evidence/a.txt', 'build/build.mk'):
                    path = root/name
                    B.write(path, 'same bytes\n')
                    before = path.stat().st_mtime_ns
                    B.write(path, 'same bytes\n')
                    self.assertEqual(before, path.stat().st_mtime_ns, name)
                    B.write(path, 'changed bytes\n')
                    self.assertEqual(path.read_text(), 'changed bytes\n')


class SlusManifestInputsTests(unittest.TestCase):
    def test_fresh_slus_compile_creates_directories_and_binds_local_defaults(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td); state = root/'build/.state'; state.mkdir(parents=True)
            view = root/'build_slus'
            for directory in ('src', 'tools', 'config'):
                (view/directory).mkdir(parents=True)
            (root/'config').mkdir()
            (root/'config/names.tsv').write_text('0x1\tfunc_1\treadable\tx\n')
            (root/'config/noreturn_syms.txt').write_text('func_1\n')
            (root/'config/sibcall_syms.txt').write_text('')
            (view/'config/names.tsv').symlink_to(root/'config/names.tsv')
            ccproc = Path(os.environ.get('FASTLAND3_TEST_CCPROC', str(B.ROOT/'tools/build/ccproc.py')))
            shutil.copyfile(ccproc, view/'tools/ccproc.py')
            shutil.copyfile(N.__file__, view/'tools/name_inputs.py')
            wrapper = view/'tools/cc.sh'
            wrapper.write_text('#!/bin/sh\npython3 tools/ccproc.py < "$1" > "$2"\n')
            wrapper.chmod(0o755)
            (view/'src/a.c').write_text('.ent readable\nreadable:\njal readable\n.end readable\n')
            with patch.object(B, 'ROOT', root), patch.object(B, 'STATE', state), \
                 contextlib.redirect_stdout(io.StringIO()):
                output = 'build_slus/build/src/a.o'
                name_input = B.name_dependency(output, N.table(root/'config/names.tsv'))
                spec = dict(command='tools/cc.sh src/a.c build/src/a.o', output=output,
                    name_input=name_input, dependencies=['build_slus/src/a.c', name_input],
                    config_tables=dict(MASPSX_NORETURN_FILE='config/noreturn_syms.txt',
                                       MASPSX_SIBCALL_FILE='config/sibcall_syms.txt'))
                path = state/'recipe.json'; B.put(path, spec)
                B.slus_compile_one(path)
                value = N.verify(root/name_input, N.table(root/'config/names.tsv'), root)
                self.assertEqual(value['sets']['config/noreturn_syms.txt'], ['func_1'])
                self.assertIn('jal func_1', (root/output).read_text())
                self.assertGreaterEqual((root/output).stat().st_mtime_ns,
                                        (root/name_input).stat().st_mtime_ns)
                proof = B.read((root/output).with_suffix('.proof.json'))
                self.assertEqual(proof['inputs'], B.hash_inputs(spec['dependencies']))

    def test_unrelated_manifest_rows_do_not_dirty_a_compile(self):
        import types
        with tempfile.TemporaryDirectory() as td:
            root = Path(td); state = root/'build/.state'; state.mkdir(parents=True)
            (root/'build_slus/config').mkdir(parents=True)
            (root/'config').mkdir()
            (root/'build_slus/build.ninja').write_text(
                'rule cc\n  command = tools/cc.sh $in $out $ccver "" "" && '
                'python3 tools/slus_rodata_trim.py --manifest config/slus_modules.json --module a --object $out\n'
                'build build/src/a.o: cc src/a.c | config/slus_modules.json\n  ccver = 2.7.2\n')
            manifest = root/'build_slus/config/slus_modules.json'
            doc = dict(version=1, modules=[dict(name='a', source='src/a.c', value=1),
                                           dict(name='b', source='src/b.c', value=2)])
            manifest.write_text(json.dumps(doc))
            with patch.object(B, 'ROOT', root), patch.object(B, 'STATE', state), \
                 patch.object(B, 'GENERATION_WRITES', set()), \
                 patch.object(B, 'include_closure', return_value=[]), \
                 patch.dict(sys.modules, overlay_module_gate=types.SimpleNamespace()):
                B.slus_rules([])
                recipe_path = next((state/'slus-recipes').glob('*.json'))
                recipe = B.read(recipe_path)
                self.assertNotIn('build_slus/config/slus_modules.json', recipe['dependencies'])
                subset = next((root/'build_slus/config/generated').glob('make_module_*.json'))
                self.assertEqual(B.read(subset)['modules'], [doc['modules'][0]])
                self.assertIn(str(subset.relative_to(root/'build_slus')), recipe['command'])
                before = {p: p.stat().st_mtime_ns for p in (recipe_path, subset)}
                doc['modules'][1]['value'] = 3; manifest.write_text(json.dumps(doc))
                B.slus_rules([])
                self.assertEqual(before, {p: p.stat().st_mtime_ns for p in before})


class GateToolExportTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.view = self.root/'build_ovl'
        files = ('tools/gate/a.py', 'tools/gate/obsolete.py', 'tools/gate/overlay_func_compare.py',
                 'tools/build/cc.sh', 'tools/build/slus_rodata_trim.py', 'tools/build/name_inputs.py',
                 'tools/overlay_module_evidence.py', 'tools/fidelity/aspsx_diff.py',
                 'tools/fidelity/objread.py', 'tools/fidelity/certify_overlay_module.py',
                 'tools/learnings/note.md')
        for name in files:
            path = self.root/name; path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text('same bytes\n')
        (self.root/'tools/gate/cc.sh').symlink_to('../build/cc.sh')
        (self.root/'tools/build/cc.sh').chmod(0o755)
        (self.root/'tools/gate/empty').mkdir()

    def snapshots(self):
        return {p.relative_to(self.view).as_posix(): (p.read_bytes(), p.stat().st_mtime_ns)
                for p in self.view.rglob('*') if p.is_file()}

    def test_repeat_export_preserves_all_tool_and_helper_mtimes(self):
        X.export(self.root, self.view)
        X.verify(self.root, self.view)
        before = self.snapshots()
        self.assertEqual(X.export(self.root, self.view)['written'], 0)
        self.assertEqual(before, self.snapshots())
        self.assertIn('work/g3/overlay_func_compare.py', before)
        helper = self.view/'tools/name_inputs.py'
        self.assertEqual(helper.read_bytes(), (self.root/'tools/build/name_inputs.py').read_bytes())
        self.assertFalse(helper.is_symlink())
        self.assertEqual(X.inputs(self.root)[0][Path('tools/name_inputs.py')],
                         self.root/'tools/build/name_inputs.py')
        self.assertTrue((self.view/'tools/empty').is_dir())
        self.assertFalse((self.view/'tools/cc.sh').is_symlink())
        self.assertEqual((self.view/'tools/cc.sh').stat().st_mode & 0o777, 0o755)

    def test_cached_output_cannot_bless_a_tool_different_from_its_authority(self):
        X.export(self.root, self.view)
        path = self.view/'tools/a.py'
        path.write_text('wrong cached compiler helper\n')
        with self.assertRaisesRegex(ValueError, 'stale exported tool'):
            X.verify(self.root, self.view)
        self.assertEqual(path.read_text(), 'wrong cached compiler helper\n')
        self.assertEqual(X.export(self.root, self.view)['written'], 1)
        X.verify(self.root, self.view)

    def test_unexpected_python_file_is_refused_but_runtime_bytecode_is_ignored(self):
        X.export(self.root, self.view)
        cache = self.view/'tools/__pycache__'; cache.mkdir()
        (cache/'a.cpython.pyc').write_bytes(b'cache')
        X.verify(self.root, self.view)
        (self.view/'tools/injected.py').write_text('wrong helper\n')
        with self.assertRaisesRegex(ValueError, 'unexpected exported tool'):
            X.verify(self.root, self.view)

    def test_changed_file_updates_and_retired_file_is_removed(self):
        X.export(self.root, self.view)
        before = self.snapshots()
        (self.root/'tools/gate/a.py').write_text('changed bytes\n')
        (self.root/'tools/gate/obsolete.py').unlink()
        result = X.export(self.root, self.view)
        after = self.snapshots()
        self.assertEqual(result['written'], 1)
        self.assertEqual(result['removed'], 1)
        self.assertNotIn('tools/obsolete.py', after)
        for name, value in after.items():
            if name != 'tools/a.py':
                self.assertEqual(before[name], value)

    def test_destination_directory_symlink_is_refused(self):
        self.view.mkdir()
        (self.view/'tools').symlink_to(self.root/'tools', target_is_directory=True)
        with self.assertRaisesRegex(ValueError, 'directory is a symlink'):
            X.export(self.root, self.view)
        self.assertEqual((self.root/'tools/gate/a.py').read_text(), 'same bytes\n')


if __name__ == '__main__':
    unittest.main()
