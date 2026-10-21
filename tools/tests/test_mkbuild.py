"""Proof boundaries for the experimental make projection (no retail required)."""
import contextlib
import hashlib
import io
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest
from unittest.mock import patch

from tools.build import mkbuild as B


class NinjaProjectionTests(unittest.TestCase):
    def test_pinned_recipe_commands_are_ninjas_commands(self):
        if not shutil.which('ninja'):
            self.skipTest('ninja unavailable')
        root = Path(__file__).resolve().parents[2]
        source = root/'ledger/splits/slus.build.ninja'
        edges = B.ninja_edges(source.read_text())
        actual = json.loads(subprocess.check_output(
            ['ninja', '-f', str(source), '-t', 'compdb'], cwd=root))
        expected = [e['command'] for e in edges if e['rule'] != 'phony']
        self.assertEqual(expected, [a['command'] for a in actual])
        self.assertEqual(sum(e['rule']=='cc' for e in edges), 842)

    def test_implicit_dependencies_are_not_command_inputs(self):
        edges = B.ninja_edges('''suffix = .o
rule cc
  command = cc $in -o $out $flags
build a.o b.o: cc a.c | include.h || stamp
  flags = -G0
''')
        self.assertEqual(edges[0]['command'], 'cc a.c -o a.o b.o -G0')
        self.assertEqual(edges[0]['deps'], ['a.c', 'include.h', 'stamp'])

    def test_slus_fragments_become_one_script_without_changing_inputs(self):
        argv, fragments = B.one_script_command('ld -EL -T build/ordered.ld -T config/uf.txt -T config/us.txt -o image.elf a.o b.o')
        self.assertEqual(argv.count('-T'),1)
        self.assertEqual(argv[-4:],['-o','image.elf','a.o','b.o'])
        self.assertEqual(fragments,['build_slus/build/ordered.ld','build_slus/config/uf.txt','build_slus/config/us.txt'])

    def test_unknown_ninja_syntax_fails_closed(self):
        with self.assertRaises(ValueError):
            B.ninja_edges('include other.ninja\n')

    def test_grouped_outputs_and_shell_dollars_survive(self):
        text = B.rule(['a', 'b'], ['c'], 'echo "$value"')
        self.assertIn('a b &:', text)
        self.assertIn('"$$value"', text)
        with self.assertRaises(ValueError):
            B.rule(['a b'], [], 'true')


class CoverageTests(unittest.TestCase):
    def test_imports_exactly_fill_unowned_intervals(self):
        chunks = B.cover_image(100, 20, [dict(foff=104, size=8, origin='original_object')])
        self.assertEqual([(c['foff'],c['size'],c['origin']) for c in chunks],
                         [(100,4,'retail_import'),(104,8,'original_object'),(112,8,'retail_import')])
        self.assertEqual(sum(c['size'] for c in chunks), 20)

    def test_overlaps_and_out_of_extent_cannot_be_hidden_by_imports(self):
        for allocations in ([dict(foff=99,size=1)], [dict(foff=119,size=2)],
                            [dict(foff=100,size=8),dict(foff=107,size=8)],
                            [dict(foff=100,size=0)]):
            with self.subTest(allocations=allocations), self.assertRaises(ValueError):
                B.cover_image(100,20,allocations)


class CompileEvidenceTests(unittest.TestCase):
    def test_source_edit_refreshes_only_its_own_declarations(self):
        import types
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            state = root/'build/.state'
            state.mkdir(parents=True)
            source = root/'unit.c'
            source.write_text('new source declaration')
            spec = dict(source='unit.c', wrapper='cc.sh', output='build/obj/unit.o',
                        args=['2.7.2','-G0',''], env={},
                        declaration_context_sha256=B.sha(b'old source'),
                        live=dict(base_names=['frozen_bank_symbol']))
            path = root/'recipe.json'
            path.write_text(json.dumps(spec))
            captured = {}
            def command(argv, **kwargs):
                captured.update(kwargs['env'])
                Path(argv[2]).write_bytes(b'object')
            evidence = types.SimpleNamespace(candidate_noreturn_syms=lambda text: {'current_own_symbol'})
            with patch.object(B,'ROOT',root), patch.object(B,'STATE',state), patch.object(B,'run',side_effect=command), patch.object(B,'load_gate'), patch.dict('sys.modules',overlay_evidence=evidence), contextlib.redirect_stdout(io.StringIO()):
                B.compile_one(path)
            self.assertEqual(Path(captured['MASPSX_NORETURN_FILE']).read_text().splitlines(),
                             ['current_own_symbol','frozen_bank_symbol'])
            self.assertEqual((root/spec['output']).read_bytes(),b'object')

    def test_interval_selection_reuses_production_answer_and_detects_mutation(self):
        import types
        with tempfile.TemporaryDirectory() as td:
            path = Path(td)/'regions.jsonl'
            path.write_text('{"foff_start":10,"foff_end":20}\n')
            records = lambda p: tuple(json.loads(line) for line in Path(p).read_text().splitlines())
            cache = types.SimpleNamespace(read_records=records)
            calls = []
            def original(family, offset):
                calls.append(offset)
                return 100 if 10 <= offset < 20 else None
            gate = types.SimpleNamespace(cfg_path=lambda p:path, _rowbase_proven_delta=original)
            with patch.dict('sys.modules',gate_read_cache=cache):
                with B.immutable_selection(gate):
                    self.assertEqual(gate._rowbase_proven_delta('town',11),100)
                    self.assertEqual(gate._rowbase_proven_delta('town',19),100)
                    self.assertIsNone(gate._rowbase_proven_delta('town',20))
                self.assertEqual(calls,[10,20])
                with self.assertRaisesRegex(ValueError,'changed during generation'):
                    with B.immutable_selection(gate):
                        cache.read_records(path)
                        path.write_text('{}\n')


class CheckBoundaryTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.state = self.root/'build/.state'
        self.state.mkdir(parents=True)
        (self.root/'ledger').mkdir()
        (self.root/'ledger/rows.jsonl').write_text('')
        self.payloads = dict(main=b'main bytes', ovmovie=b'movie bytes', slus=b'executable')
        self.files = {}
        images = []
        for family, data in self.payloads.items():
            disc = self.root/'work/disc/extract'/family
            disc.parent.mkdir(parents=True, exist_ok=True)
            disc.write_bytes(data)
            self.files[family] = dict(disc_path=family, size=len(data), sha1=hashlib.sha1(data).hexdigest())
            output = 'build/'+family+'_'+family+'_bin.bin'
            (self.root/output).write_bytes(data)
            images.append(dict(image=family+'/'+family+'_bin', file=family, start=0, size=len(data), output=output))
        self.index = dict(files=self.files, images=images)
        self.save()
        fake_graph = type('FakeGraph', (), dict(files=self.files, documents=lambda self: {}))()
        for context in (patch.object(B,'ROOT',self.root), patch.object(B,'STATE',self.state),
                        patch.object(B,'Graph',return_value=fake_graph), patch.object(B,'selected_images',return_value=[])):
            context.start()
            self.addCleanup(context.stop)

    def save(self):
        (self.state/'index.json').write_text(json.dumps(self.index))

    def check(self):
        with contextlib.redirect_stdout(io.StringIO()):
            B.check()

    def test_all_images_and_executable_match(self):
        self.check()
        self.assertEqual(B.read(self.root/'build/check.json')['matched'],3)

    def test_edited_output_fails(self):
        (self.root/'build/main_main_bin.bin').write_bytes(b'bad')
        with self.assertRaisesRegex(ValueError,'retail mismatch'):
            self.check()

    def test_disc_identity_checked_before_comparing(self):
        (self.root/'work/disc/extract/main').write_bytes(b'wrong disc')
        with self.assertRaisesRegex(ValueError,'disc input identity'):
            self.check()

    def test_omitted_image_cannot_report_success(self):
        self.index['images'].pop()
        self.save()
        with self.assertRaisesRegex(ValueError,'complete image graph'):
            self.check()

    def test_changed_extent_cannot_report_success(self):
        self.index['images'][0]['size']-=1
        self.save()
        with self.assertRaisesRegex(ValueError,'extent differs'):
            self.check()


if __name__ == '__main__':
    unittest.main()

class Pass2CheckTests(unittest.TestCase):
    def test_first_difference_reports_content_and_truncation(self):
        self.assertEqual(B.first_difference(b'abX', b'abc'),2)
        self.assertEqual(B.first_difference(b'ab', b'abc'),2)
        self.assertIsNone(B.first_difference(b'abc',b'abc'))

    def test_missing_sdk_is_explicit_not_genuine(self):
        with tempfile.TemporaryDirectory() as td, patch.object(B,'ROOT',Path(td)):
            status=B.genuine_status()
            self.assertEqual(status['mode'],'maspsx_only')
            self.assertEqual(len(status['missing']),2)
            self.assertIn('--psyq',status['description'])

    def test_graph_cell_change_cannot_be_refreshed_away(self):
        import types
        with tempfile.TemporaryDirectory() as td:
            root=Path(td)
            for name in ('ledger/containers.jsonl','ledger/splits/slus.jsonl','ledger/instance_load_regions.jsonl'):
                p=root/name;p.parent.mkdir(parents=True,exist_ok=True);p.write_text('')
            (root/'config/overlays').mkdir(parents=True)
            (root/'config/overlays/modules.json').write_text('{"modules":[]}')
            graph=types.SimpleNamespace(manifest=dict(inputs={name:B.sha(b'') for name in ('ledger/containers.jsonl','ledger/splits/slus.jsonl','ledger/instance_load_regions.jsonl')}),
                tus={'town/row':dict(recipe_witness=dict(cfg='2.7.2'))},entries={})
            with patch.object(B,'ROOT',root),self.assertRaisesRegex(ValueError,'TU/cell disagrees'):
                B.attest_graph(graph,{'town/row':dict(cfg='2.8.1')})


class MakeReceiptTests(unittest.TestCase):
    def test_changed_source_and_image_reject_levels_proof(self):
        from tools.build.make_evidence import checked_receipt
        with tempfile.TemporaryDirectory() as td:
            root=Path(td);(root/'build').mkdir()
            (root/'unit.c').write_bytes(b'source');(root/'build/image.bin').write_bytes(b'image')
            rec=dict(schema='azure-clean.make-check.v2',images=1,matched=1,results=[dict(result='MATCH')],
                inputs={'unit.c':B.sha(b'source')},outputs={'build/image.bin':B.sha(b'image')})
            (root/'build/check.json').write_text(json.dumps(rec))
            self.assertEqual(checked_receipt(root)['matched'],1)
            (root/'unit.c').write_bytes(b'changed')
            with self.assertRaisesRegex(ValueError,'stale make check proof'):checked_receipt(root)
            (root/'unit.c').write_bytes(b'source');(root/'build/image.bin').write_bytes(b'changed')
            with self.assertRaisesRegex(ValueError,'stale make check proof'):checked_receipt(root)

    def test_failed_or_empty_check_never_grants_a_level(self):
        from tools.build.make_evidence import checked_receipt
        with tempfile.TemporaryDirectory() as td:
            root=Path(td);(root/'build').mkdir()
            for rec in (dict(schema='azure-clean.make-check.v2',images=1,matched=0,results=[dict(result='DIFF')]),
                        dict(schema='azure-clean.make-check.v2',images=0,matched=0,results=[])):
                (root/'build/check.json').write_text(json.dumps(rec))
                with self.assertRaises(ValueError):checked_receipt(root)

class MakePlacementTests(unittest.TestCase):
    def test_checked_member_needs_consumed_shared_header_without_certificates(self):
        from tools.build import make_evidence as E
        with tempfile.TemporaryDirectory() as td:
            root=Path(td)
            for d in ('src','include/shared','config/overlays'):(root/d).mkdir(parents=True,exist_ok=True)
            (root/'include/shared/unit.h').write_text('extern void unit(void);\n')
            (root/'src/unit.c').write_text('#include "shared/unit.h"\nvoid unit(void) {}\n')
            m=dict(key='unit',source='src/unit.c',headers=['include/shared/unit.h'],members=[dict(id='town/unit')])
            (root/'config/overlays/modules.json').write_text(json.dumps(dict(modules=[m])))
            (root/'config/slus_modules.json').write_text('{"modules":[]}')
            with patch.object(E,'checked_receipt',return_value=dict(rows={'town/unit':['town/check_unit']})):
                result=E.placements(root)
                self.assertEqual(result['town/unit']['images'],['town/check_unit'])
                self.assertFalse((root/'ledger/modules').exists())
                (root/'src/unit.c').write_text('void unit(void) {}\n')
                self.assertEqual(E.placements(root),{})

class SlusPlacementViewTests(unittest.TestCase):
    def test_slus_module_uses_registered_build_view_paths(self):
        from tools.build import make_evidence as E
        with tempfile.TemporaryDirectory() as td:
            root=Path(td)
            for d in ('build_slus/src','include/shared','config/overlays'):(root/d).mkdir(parents=True,exist_ok=True)
            (root/'include/shared/unit.h').write_text('extern void unit(void);\n')
            (root/'build_slus/include').symlink_to(root/'include',target_is_directory=True)
            (root/'build_slus/src/owner.c').write_text('#include "shared/unit.h"\nvoid unit(void) {}\n')
            (root/'config/overlays/modules.json').write_text('{"modules":[]}')
            m=dict(name='unit',source='src/owner.c',headers=['include/shared/unit.h'],members=[dict(id='slus/unit')])
            (root/'config/slus_modules.json').write_text(json.dumps(dict(modules=[m])))
            with patch.object(E,'checked_receipt',return_value=dict(rows={'slus/unit':['slus/slus_bin']})):
                self.assertEqual(E.placements(root)['slus/unit']['module'],'unit')


class SlusAssemblyDependencyTests(unittest.TestCase):
    def test_shared_include_stamp_invalidates_slus_assembly(self):
        with tempfile.TemporaryDirectory() as td:
            root=Path(td);(root/'build_slus').mkdir()
            (root/'build_slus/build.ninja').write_text('rule as\n  command = as $in -o $out\nbuild build/asm/unit.o: as asm/unit.s\n')
            with patch.object(B,'ROOT',root):
                rules,count=B.slus_rules([])
            assembly=next(r for r in rules if r.startswith('build_slus/build/asm/unit.o:'))
            self.assertIn('build/.state/headers.ok',assembly.splitlines()[0])
            self.assertEqual(count,0)
