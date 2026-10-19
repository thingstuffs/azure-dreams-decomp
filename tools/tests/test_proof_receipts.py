"""Portable proof boundaries, content drift and actual dependency discovery."""
import contextlib
import importlib.util
import io
import json
import os
from pathlib import Path
import shutil
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

TOOLS=Path(__file__).resolve().parents[1]
sys.path[:0]=[str(TOOLS/'lanes'),str(TOOLS),str(TOOLS/'gate')]
from lanes import proof_receipts as P
sys.modules['proof_receipts']=P
from gate import overlay_module_gate as G
import overlay_scoped_fingerprint as S


class ReceiptFixture(unittest.TestCase):
    def setUp(self):
        self.temp=tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR'));self.addCleanup(self.temp.cleanup)
        self.root=Path(self.temp.name);self.evidence=self.root/'evidence';self.evidence.mkdir()
        self.source=self.root/'src/a.c';self.source.parent.mkdir();self.source.write_text('canonical')
        self.binary=self.evidence/'window.bin';self.binary.write_bytes(b'retail')
        self.inputs=lambda *a:dict(source=P.sha(self.source),retail=dict(slice_sha256=P.sha(self.binary),start=0,end=6))
        self.patch=patch.object(P,'inputs',side_effect=self.inputs);self.patch.start();self.addCleanup(self.patch.stop)
        self.before=self.inputs()
        P.publish(self.evidence,'overlay-window','config/overlays/a.overlay.yaml',self.before,self.before,'MATCH')

    def test_round_trip_and_portable_location(self):
        self.assertEqual(P.verify(self.root,self.evidence)['inputs'],self.before)
        copy=self.root/'copy';shutil.copytree(self.evidence,copy)
        self.assertEqual(P.verify(self.root,copy)['inputs'],self.before)

    def test_changed_source_or_receipt_input_fails(self):
        self.source.write_text('different')
        with self.assertRaisesRegex(ValueError,'inputs changed'):P.verify(self.root,self.evidence)
        self.source.write_text('canonical')
        path=self.evidence/'proof-receipt.json';doc=json.loads(path.read_text());doc['inputs']['source']='fake';path.write_text(json.dumps(doc))
        with self.assertRaisesRegex(ValueError,'input record corrupt'):P.verify(self.root,self.evidence)

    def test_artifacts_identity_and_extra_artifact_fail_closed(self):
        with self.assertRaisesRegex(ValueError,'identity'):P.verify(self.root,self.evidence,expected_kind='overlay-module')
        self.binary.write_bytes(b'wrong!')
        with self.assertRaisesRegex(ValueError,'artifacts changed'):P.verify(self.root,self.evidence)
        self.binary.write_bytes(b'retail');(self.evidence/'extra').write_text('unsealed')
        with self.assertRaisesRegex(ValueError,'artifacts changed'):P.verify(self.root,self.evidence)

    def test_lane_proof_race_and_inexact_results_never_publish(self):
        for after,result in [(dict(changed=True),'MATCH'),(self.before,'NO MATCH')]:
            with self.assertRaises(ValueError):P.publish(self.evidence,'overlay-window','a',self.before,after,result)

    def test_symbolic_and_traversal_paths_refuse(self):
        with self.assertRaises(ValueError):P.private(self.root,'../escape')
        (self.root/'link').symlink_to(self.evidence,target_is_directory=True)
        with self.assertRaises(ValueError):P.private(self.root,'link/output')
        (self.evidence/'linked').symlink_to(self.source)
        with self.assertRaisesRegex(ValueError,'linked'):P.verify(self.root,self.evidence)

    def test_input_sweeps_rehash_after_mutation_even_with_restored_mtime(self):
        with P.input_snapshot():
            before=P.sha(self.source);stamp=self.source.stat()
            self.source.write_text('changed!!');os.utime(self.source,ns=(stamp.st_atime_ns,stamp.st_mtime_ns))
            self.assertNotEqual(before,P.sha(self.source))
        self.source.write_text('canonical')
        with P.input_snapshot():self.assertEqual(before,P.sha(self.source))

    def test_package_index_must_be_fully_sealed(self):
        doc=[dict(kind='overlay-window',target='config/overlays/a.overlay.yaml',directory='evidence')]
        (self.root/'proofs.json').write_text(json.dumps(doc))
        files=[self.root/'proofs.json',*self.evidence.rglob('*')]
        inventory={str(p.relative_to(self.root)):P.sha(p) for p in files if p.is_file()}
        seal=self.root/'package.sha256.json';seal.write_text(json.dumps(inventory))
        self.assertEqual(len(P.package_receipts(self.root)),1)
        self.binary.write_bytes(b'wrong!')
        with self.assertRaisesRegex(ValueError,'unsealed'):P.package_receipts(self.root)

    def test_diagnostics_cannot_be_relabelled_as_window(self):
        doc=json.loads((self.evidence/'proof-receipt.json').read_text());doc['kind']='row-score'
        (self.evidence/'proof-receipt.json').write_text(json.dumps(doc))
        with self.assertRaisesRegex(ValueError,'identity'):P.verify(self.root,self.evidence,expected_kind='overlay-window')


class WindowProjection(unittest.TestCase):
    def setUp(self):
        self.temp=tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR'));self.addCleanup(self.temp.cleanup)
        self.root=Path(self.temp.name)
        for n in ['config/overlays','ledger/splits','src/main','include','raw/main','work/disc/containers']:(self.root/n).mkdir(parents=True)
        (self.root/'src/main/a.c').write_text('#include "a.h"\nint a(void){return VALUE;}\n')
        (self.root/'include/a.h').write_text('#define VALUE 1\n')
        (self.root/'include/transitive.h').write_text('/* transitive */\n')
        (self.root/'work/disc/containers/MAIN_MAIN.BIN').write_bytes(bytes(range(64)))
        self.row=dict(id='main/a',kind='overlay',container='main',foff=0,size=16,c_path='a.c')
        self.split=dict(foff=0,size=16,func_vram='a',result='MATCH',config='2.7.2')
        self.write('ledger/rows.jsonl',[self.row]);self.write('ledger/splits/main.jsonl',[self.split])
        self.write('ledger/modules.jsonl',[])
        self.target='config/overlays/main_a.overlay.yaml'
        (self.root/self.target).write_text('''name: main_a
standalone_build:
  window: {file_start: 0, file_end: 16}
  split_results: overlays/main/overlay_first_pass_results.json
  matched_sources:
    - results: overlays/main/overlay_first_pass_results.json
      source_dir: overlays/main/first_pass_matched
''')
        for p in [patch.object(S,'parse_config_label',return_value=('2.7.2','-G0')),
                  patch.object(S,'identities',return_value={'compiler':'identity'}),
                  patch.object(P,'extra_tools',return_value={'verifier':'identity'}),
                  patch.object(P,'environment',return_value={'policy':1})]:
            p.start();self.addCleanup(p.stop)
        # This test uses the real old compiler -M over fixture sources, with
        # only the toolchain linked read-only to the supplied production tools.
        (self.root/'toolchain').symlink_to(TOOLS.parent/'toolchain',target_is_directory=True)

    def write(self,name,rows):
        (self.root/name).write_text(''.join(json.dumps(r)+'\n' for r in rows))

    def snapshot(self):
        with P.input_snapshot():return P.window_inputs(self.root,self.target)

    def test_actual_macro_transitive_include_and_unrelated_source(self):
        before=self.snapshot()
        self.assertIn('include/a.h',before['sources'])
        (self.root/'include/a.h').write_text('#include "transitive.h"\n#define VALUE 2\n')
        after=self.snapshot();self.assertNotEqual(before,after)
        self.assertIn('include/transitive.h',after['sources'])
        (self.root/'src/main/unrelated.c').write_text('does not compile')
        self.assertEqual(after,self.snapshot())

    def test_compiler_flags_ledgers_symbols_retail_and_header_namespace_bound(self):
        base=self.snapshot()
        (self.root/'config/names.tsv').write_text('a\tb')
        self.assertNotEqual(base,self.snapshot())
        (self.root/'config/names.tsv').unlink()
        self.split['config']='new-cell';self.write('ledger/splits/main.jsonl',[self.split])
        self.assertNotEqual(base,self.snapshot())
        self.split['config']='2.7.2';self.write('ledger/splits/main.jsonl',[self.split])
        (self.root/'include/new.h').write_text('shadow namespace addition')
        self.assertNotEqual(base,self.snapshot())
        (self.root/'include/new.h').unlink();(self.root/'work/disc/containers/MAIN_MAIN.BIN').write_bytes(b'X'*64)
        self.assertNotEqual(base,self.snapshot())

    def test_source_include_shadowing_is_discovered_again(self):
        before=self.snapshot();(self.root/'src/main/a.h').write_text('#define VALUE 3\n')
        after=self.snapshot();self.assertNotEqual(before,after)
        self.assertIn('src/main/a.h',after['sources'])

    def test_empty_placement_intent_does_not_change_an_existing_window_digest(self):
        before=self.snapshot()
        self.write_placements=[]
        (self.root/'config/overlays/module_placements.json').write_text(json.dumps(dict(schema='azure-clean.module-placements.v1',placements=[])))
        self.assertEqual(before,self.snapshot())

    def test_v4_family_census_and_absolute_symbols_are_real_production_dependencies(self):
        before=self.snapshot()
        for name in ('config/noreturn_syms.txt','config/sibcall_syms.txt','config/overlays/abs_syms.txt'):
            path=self.root/name
            path.write_text('first\n');first=self.snapshot()
            path.write_text('second\n');second=self.snapshot()
            self.assertNotEqual(before,first,name)
            self.assertNotEqual(first,second,name)
            path.unlink()
        (self.root/'config/noreturn_syms.town.txt').write_text('unrelated family\n')
        self.assertEqual(before,self.snapshot())

    def test_assembly_incbin_and_include_closure(self):
        (self.root/'src/main/a.s').write_text('.include "body.inc"\n.incbin "blob.bin"\n')
        (self.root/'src/main/body.inc').write_text('.word 0\n')
        (self.root/'src/main/blob.bin').write_bytes(b'\xff\xfe')
        deps=P.assembly_inputs(self.root,'src/main/a.s')
        self.assertEqual(set(deps),{'src/main/a.s','src/main/body.inc','src/main/blob.bin'})
        (self.root/'src/main/a.s').write_text('.include SYMBOL\n')
        with self.assertRaisesRegex(ValueError,'unmodelled'):P.assembly_inputs(self.root,'src/main/a.s')


class GateCarriage(unittest.TestCase):
    def test_current_carried_window_avoids_build_and_stale_one_builds(self):
        spec=importlib.util.spec_from_file_location('carried_gate',TOOLS/'build/gate_all.py')
        gate=importlib.util.module_from_spec(spec);spec.loader.exec_module(gate)
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as td:
            root=Path(td);(root/'config/overlays').mkdir(parents=True)
            target='config/overlays/main_a.overlay.yaml';(root/target).write_text('name: main_a\n')
            index=root/'carried.json';index.write_text(json.dumps({target:str(root/'evidence')}))
            for stale in (False,True):
                journal=root/'gate.jsonl';journal.unlink(missing_ok=True)
                record=dict(window='main_a',result='MATCH',inputs_sha='strong',detail='')
                with patch.object(gate,'ROOT',root),patch.object(gate,'B',root),patch.object(gate,'JOURNAL',journal), \
                     patch.object(gate,'superseded',return_value=set()),patch.object(gate,'inputs_sha',return_value='strong'), \
                     patch.object(P,'verify',side_effect=ValueError('stale') if stale else None), \
                     patch.object(gate,'run_window',return_value=record) as build, \
                     patch.object(sys,'argv',['gate_all','--workers','1','--worker-mode','subprocess','--carried-proofs',str(index)]), \
                     contextlib.redirect_stdout(io.StringIO()):gate.main()
                self.assertEqual(build.call_count,int(stale))

if __name__=='__main__':unittest.main()


from tools.tests.test_gate_all_scoped_inputs import ScopedInputsFixture

class BankProjection(ScopedInputsFixture):
    def test_optimized_projection_equals_canonical_across_regions_and_isolated_offsets(self):
        G,S=P._authorities()
        cases=[[0x100],[0x110],[0x150],[0x300],[0x510],[0x600],[0x610],[0x110,0x300],[0x100,0x100]]
        with P.input_snapshot():
            for offsets in cases:
                self.assertEqual(P.bank_inputs(self.root,'dungeon',offsets,{},G),
                                 S.noreturn(self.root,'dungeon',offsets,{}, {},G),offsets)

    def test_raw_comment_change_refreshes_content_in_a_new_sweep(self):
        G,_=P._authorities()
        with P.input_snapshot():before=P.bank_inputs(self.root,'dungeon',[0x100],{},G)
        p=self.root/'raw/dungeon/func_00000110.c';p.write_text(p.read_text()+'/* comment */\n')
        with P.input_snapshot():after=P.bank_inputs(self.root,'dungeon',[0x100],{},G)
        self.assertEqual(before['semantic'],after['semantic'])
        self.assertNotEqual(before['frozen_sources'],after['frozen_sources'])


class ViewBinding(unittest.TestCase):
    def test_stale_tools_rosters_and_source_facades_cannot_produce_current_receipts(self):
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as td:
            root=Path(td)/'root';view=Path(td)/'view';root.mkdir();view.mkdir()
            for name in ('src/main','include','ledger/splits','config/overlays','toolchain','.venv','tools/gate','tools/build','tools/fidelity'):(root/name).mkdir(parents=True)
            for name in ('src','include','ledger','config/overlays','toolchain','.venv'):
                q=view/name;q.parent.mkdir(parents=True,exist_ok=True);q.symlink_to(root/name,target_is_directory=True)
            for name in ('tools/gate/gate.py','tools/overlay_module_evidence.py','tools/build/slus_rodata_trim.py',
                         'tools/fidelity/aspsx_diff.py','tools/fidelity/objread.py','tools/fidelity/certify_overlay_module.py'):
                (root/name).write_text('canonical')
                rel='tools/gate.py' if name=='tools/gate/gate.py' else name
                q=view/rel;q.parent.mkdir(parents=True,exist_ok=True);q.write_text('canonical')
            (root/'config/names.tsv').write_text('names');(view/'config/names.tsv').symlink_to(root/'config/names.tsv')
            (root/'build_slus/asm').mkdir(parents=True);(view/'asm').symlink_to(root/'build_slus/asm',target_is_directory=True)
            (root/'work/disc/containers').mkdir(parents=True);(root/'work/disc/containers/MAIN_MAIN.BIN').write_bytes(b'retail')
            (view/'work/s3_splat').mkdir(parents=True);(view/'work/s3_splat/extract').symlink_to(root/'work/disc/containers',target_is_directory=True)
            target='config/overlays/main_a.overlay.yaml'
            (root/target).write_text('name: main_a\noptions: {target_path: work/s3_splat/extract/MAIN_MAIN.BIN}\nstandalone_build:\n  split_results: overlays/main/overlay_first_pass_results.json\n  matched_sources:\n    - results: overlays/main/overlay_first_pass_results.json\n      source_dir: overlays/main/first_pass_matched\n')
            (root/'ledger/splits/main.jsonl').write_text('{"foff":0}\n')
            table=view/'overlays/main/overlay_first_pass_results.json';table.parent.mkdir(parents=True);table.write_text('[{"foff":0}]')
            facade=table.parent/'first_pass_matched';facade.symlink_to(root/'src/main',target_is_directory=True)
            self.assertTrue(P.validate_view(root,view,target))
            (view/'tools/gate.py').write_text('stale')
            with self.assertRaisesRegex(ValueError,'stale exported gate tool'):P.validate_view(root,view,target)
            (view/'tools/gate.py').write_text('canonical');table.write_text('[]')
            with self.assertRaisesRegex(ValueError,'split roster differs'):P.validate_view(root,view,target)
            table.write_text('[{"foff":0}]');facade.unlink();facade.mkdir()
            with self.assertRaisesRegex(ValueError,'source facade differs'):P.validate_view(root,view,target)


class UnsupportedCInputs(unittest.TestCase):
    def test_inline_file_macros_and_clock_inputs_fail_closed(self):
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as td:
            root=Path(td);p=root/'a.c'
            for text in ['INCLUDE_ASM("asm",name);','__asm__(".incbin \\"blob.bin\\"");',
                         'const char *date=__DATE__;','#define ALIAS INCLUDE_ASM\nALIAS("asm",name);']:
                p.write_text(text)
                with self.assertRaises(ValueError):P.c_input_policy(root,['a.c'])
            p.write_text('int a(void){return 1;} /* INCLUDE_ASM is unsupported */\n')
            P.c_input_policy(root,['a.c'])
