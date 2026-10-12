"""Selective renewal protocol and actual preprocessor dependency admission."""
import contextlib
import importlib.util
import io
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

HERE = Path(__file__).resolve().parent
def load(name, path):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module

G = load('selective_lander', HERE.parent/'lanes/land_packages.py')
H = load('selective_batch_fixture', HERE/'test_certify_batch.py')
L = load('selective_land_fixture', HERE/'test_land_packages.py')
W = load('selective_dependencies', HERE.parent/'lanes/window_dependencies.py')


class SelectiveCertificateTests(unittest.TestCase):
    setUp = H.CertifyBatchTests.setUp
    argv = H.CertifyBatchTests.argv

    def reader(self, invalid=()):
        for key in 'abcd':
            p = self.root/'ledger/modules'/('overlay_'+key+'.json')
            rec = json.loads(p.read_text()); rec['valid'] = key not in invalid
            p.write_text(json.dumps(rec))
        (self.root/'tools/overlay_module_evidence.py').write_text('''import json
def module_status(root):
 out=[]
 for key in 'abcd':
  p=root/'ledger/modules'/('overlay_'+key+'.json');r=json.loads(p.read_text())
  out.append({'module':{'key':key},'valid':r['valid'],'reason':None if r['valid'] else 'inputs changed'})
 return out
''')
        p = self.root/'tools/fidelity/certify_overlay_module.py'
        p.write_text(p.read_text()+'''\np=Path('ledger/modules')/('overlay_'+a.key+'.json');r=json.loads(p.read_text());r['valid']=True;p.write_text(json.dumps(r))
''')

    def invoke(self, mode='--invalid-only', extra=()):
        return subprocess.run(self.argv()+[mode]+list(extra), capture_output=True, text=True, timeout=15)

    def test_valid_certificates_are_retained_byte_exact_without_producers(self):
        self.reader()
        before = {p:p.read_bytes() for p in (self.root/'ledger/modules').glob('*')}
        result = self.invoke()
        self.assertEqual(result.returncode, 0, result.stdout+result.stderr)
        self.assertFalse((self.root/'events.jsonl').exists())
        self.assertEqual(before, {p:p.read_bytes() for p in before})
        summary = json.loads((self.logs/'summary.json').read_text())
        self.assertEqual(summary['validated'], 4); self.assertEqual(summary['certificates'], [])

    def test_only_invalid_module_renews_with_its_own_reviewer(self):
        self.reader(('b',))
        result = self.invoke()
        self.assertEqual(result.returncode, 0, result.stdout+result.stderr)
        summary = json.loads((self.logs/'summary.json').read_text())
        self.assertEqual([c['module'] for c in summary['certificates']], ['b'])
        self.assertEqual(summary['certificates'][0]['reviewer'], 'reviewer-b')
        self.assertEqual(summary['retained'], ['a','c','d'])

    def test_legacy_wholesale_invalidation_renews_all(self):
        self.reader('abcd')
        result = self.invoke()
        self.assertEqual(result.returncode, 0, result.stdout+result.stderr)
        self.assertEqual(len(json.loads((self.logs/'summary.json').read_text())['certificates']), 4)

    def test_validate_only_refuses_invalid_without_launching_producers(self):
        self.reader(('c',))
        result = self.invoke('--validate-only')
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('invalid final certificates', result.stderr)
        self.assertFalse((self.root/'events.jsonl').exists())

    def test_final_validation_checks_retained_modules_too(self):
        self.reader(('b',))
        p = self.root/'tools/fidelity/certify_overlay_module.py'
        p.write_text(p.read_text()+"p=Path('ledger/modules/overlay_a.json');r=json.loads(p.read_text());r['valid']=False;p.write_text(json.dumps(r))\n")
        result = self.invoke()
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('invalid certificates after renewal', result.stderr)
        self.assertIn('"a"', result.stderr)

    def assert_reader_refusal(self, body, reason):
        self.reader()
        (self.root/'tools/overlay_module_evidence.py').write_text('def module_status(root):\n '+body+'\n')
        result = self.invoke()
        self.assertNotEqual(result.returncode, 0)
        self.assertIn(reason, result.stderr)
        self.assertFalse((self.root/'events.jsonl').exists())

    def test_reader_crash_names_its_refusal(self):
        self.assert_reader_refusal("raise ValueError('reader crashed')", 'reader crashed')

    def test_missing_reader_entry_names_its_refusal(self):
        self.assert_reader_refusal('return []', 'recorded certificate absent from module status')

    def test_duplicate_reader_entry_names_its_refusal_with_complete_roster(self):
        self.assert_reader_refusal("return [{'module':{'key':k},'valid':True,'reason':None} for k in 'abcda']", 'duplicate module status: a')

    def test_invalid_manifest_names_its_refusal_with_complete_roster(self):
        self.assert_reader_refusal("return [{'module':{'key':k},'valid':True,'reason':None} for k in 'abcd']+[{'module':{'key':'manifest'},'valid':False,'reason':'manifest invalid: fixture'}]", 'manifest invalid: fixture')

    def test_reader_accepted_transaction_edit_still_runs_its_producer(self):
        self.reader()
        before = G.certificate_evidence(self.root)
        p = self.root/'ledger/modules/overlay_b.json'
        p.write_text(p.read_text()+'\n')  # Semantically unchanged and reader-valid.
        after = G.certificate_evidence(self.root)
        forced = sorted(k for k in after if before.get(k) != after[k])
        self.assertEqual(forced, ['b'])
        result = self.invoke(extra=['--renew','b'])
        self.assertEqual(result.returncode, 0, result.stdout+result.stderr)
        summary = json.loads((self.logs/'summary.json').read_text())
        self.assertEqual(summary['invalid_before'], {})
        self.assertEqual([c['module'] for c in summary['certificates']], ['b'])
        self.assertEqual(summary['certificates'][0]['reviewer'], 'reviewer-b')

    def test_forced_valid_and_reader_invalid_sets_are_unioned(self):
        self.reader(('c',))
        result = self.invoke(extra=['--renew','b','--renew','b'])
        self.assertEqual(result.returncode, 0, result.stdout+result.stderr)
        summary = json.loads((self.logs/'summary.json').read_text())
        self.assertEqual([c['module'] for c in summary['certificates']], ['b','c'])
        self.assertEqual(summary['retained'], ['a','d'])

    def test_forced_unknown_key_refuses_before_any_producer(self):
        self.reader()
        result = self.invoke(extra=['--renew','unknown'])
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('forced renewal absent from certificate roster', result.stderr)
        self.assertFalse((self.root/'events.jsonl').exists())

    def test_validate_only_cannot_ignore_forced_renewal(self):
        self.reader()
        result = self.invoke('--validate-only', ['--renew','b'])
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('forced renewal conflicts with validate-only', result.stderr)
        self.assertFalse((self.root/'events.jsonl').exists())


@unittest.skipUnless(shutil.which('gcc'), 'host gcc needed for actual -M fixture')
class IncludeDependenciesTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR'))
        self.addCleanup(self.tmp.cleanup); self.root = Path(self.tmp.name).resolve()
        self.put('tools/gate/match.py', (HERE.parent/'gate/match.py').read_text())
        gcc = self.root/'toolchain/compilers/gcc-2.7.2/gcc'; gcc.parent.mkdir(parents=True)
        gcc.symlink_to(shutil.which('gcc'))
        self.put('src/demo/old.c', 'int old(void) { return 1; }\n')
        self.row = {'result':'MATCH','foff':0,'size':4,'func_vram':'old','config':'2.7.2 -ffreestanding'}
        self.write_window()
        self.baseline = W.window_recipes(self.root)

    def put(self, name, text):
        p = self.root/name; p.parent.mkdir(parents=True,exist_ok=True); p.write_text(text)

    def write_window(self):
        self.put('ledger/splits/demo.jsonl', json.dumps(self.row)+'\n')
        self.put('config/overlays/demo.overlay.yaml', 'standalone_build:\n  window: {file_start: 0, file_end: 4}\n  matched_sources:\n  - results: overlays/demo/overlay_first_pass_results.json\n    source_dir: overlays/demo/first_pass_matched\n')

    def reasons(self, before=(), baseline=None):
        return G.full_gate_reasons({'include/modules/new.h'}, {}, self.root, set(before), baseline or self.baseline)

    def test_new_module_private_header_does_not_force_all(self):
        self.put('include/modules/new.h', '#define NEW 2\n')
        self.put('src/demo/modules/new.c', '#include "modules/new.h"\nint added(void) { return NEW; }\n')
        self.assertEqual(self.reasons(), [])

    def test_old_row_folded_into_new_tu_is_not_an_existing_compile(self):
        self.put('include/modules/new.h', '#define NEW 2\n')
        self.put('src/demo/old.c', '#include "modules/new.h"\nint old(void) {return NEW;}\n')
        self.put('src/demo/modules/new.c', '#include "../old.c"\n')
        self.put('config/overlays/modules.json', json.dumps({'modules':[{
          'source':'src/demo/modules/new.c','headers':['include/modules/new.h'],
          'recipe':{'cfg':'2.7.2-cdk-G0'},'members':[{'source':'src/demo/old.c'}]}]}))
        self.assertEqual(self.reasons(), [])

    def test_existing_include_always_forces_all_even_when_unused(self):
        self.put('include/modules/new.h', '')
        self.assertEqual(self.reasons(['include/modules/new.h']), ['include/modules/new.h'])

    def test_macro_expanded_transitive_include_forces_all(self):
        self.put('include/modules/new.h', '#define V 1\n')
        self.put('include/wrapper.h', '#define HEADER "modules/new.h"\n#include HEADER\n')
        self.put('src/demo/old.c', '#include "wrapper.h"\nint old(void) { return V; }\n')
        self.assertEqual(self.reasons(), ['include/modules/new.h'])

    def test_changed_recipe_conditional_include_is_observed(self):
        self.put('include/modules/new.h', '#define V 1\n')
        self.put('src/demo/old.c', '#if TAKE\n#include "modules/new.h"\n#endif\nint old(void) {return 1;}\n')
        self.row['config'] = '2.7.2 -ffreestanding -DTAKE=1'; self.write_window()
        self.assertEqual(self.reasons(), ['include/modules/new.h'])

    def test_missing_include_forces_all_for_preprocessor_failure(self):
        self.put('include/modules/new.h', '')
        self.put('src/demo/old.c', '#include "absent.h"\n')
        self.assertIn('closure unavailable: CalledProcessError:', self.reasons()[0])

    def test_missing_compiler_forces_all_for_its_own_reason(self):
        self.put('include/modules/new.h', '')
        (self.root/'toolchain/compilers/gcc-2.7.2/gcc').unlink()
        reason = self.reasons()[0]
        self.assertIn('closure unavailable: FileNotFoundError:', reason)
        self.assertIn('toolchain/compilers/gcc-2.7.2/gcc', reason)

    def test_missing_source_forces_all_for_its_own_reason(self):
        self.put('include/modules/new.h', '')
        (self.root/'src/demo/old.c').unlink()
        self.assertIn('closure unavailable: ValueError: existing window source missing: src/demo/old.c', self.reasons()[0])

    def test_missing_baseline_forces_all_for_its_own_reason(self):
        self.put('include/modules/new.h', '')
        self.assertIn('baseline window recipes unavailable: fixture failure', self.reasons(baseline={'error':'fixture failure'})[0])

    def test_new_c_header_shadow_is_in_existing_preprocessor_closure(self):
        self.put('include/x.h', '#define V 1\n')
        self.put('include/modules/wrapper.h', '#include "x.h"\n')
        self.put('src/demo/old.c', '#include "modules/wrapper.h"\nint old(void) {return V;}\n')
        baseline = W.window_recipes(self.root)
        self.assertIn('include/x.h', W.dependency_closure(self.root, baseline))
        self.put('include/modules/x.h', '#define V 2\n')
        closure = W.dependency_closure(self.root, baseline)
        self.assertIn('include/modules/x.h', closure)
        self.assertNotIn('include/x.h', closure)
        self.assertEqual(G.full_gate_reasons({'include/modules/x.h'}, {}, self.root,
                         {'include/x.h','include/modules/wrapper.h'}, baseline), ['include/modules/x.h'])

    def test_tool_reason_skips_closure_even_with_new_include(self):
        with patch.object(G, 'dependency_closure', side_effect=AssertionError('closure must be skipped')):
            self.assertEqual(G.full_gate_reasons({'tools/build/mk_ovl_root.sh','include/modules/new.h'}, {},
                             self.root, set(), self.baseline), ['tools/build/mk_ovl_root.sh'])

    def test_gate_tools_plan_and_missing_context_keep_full_trigger(self):
        self.assertIn('tools/gate/change.py', G.full_gate_reasons({'tools/gate/change.py'}, {}))
        self.assertEqual(G.full_gate_reasons({'include/modules/new.h'}, {}), ['include/modules/new.h'])
        self.assertIn('plan gate_all=full', G.full_gate_reasons(set(), {'gate_all':'full'}))

    def test_generated_assembly_include_search_does_not_miss_shadow(self):
        self.put('include/modules/new.h', '.set V, 1\n')
        self.put('include/wrapper.inc', '.include "modules/new.h"\n')
        self.put('build_slus/asm/psyq/wrapper.inc', '.set V, 2\n')
        self.put('build_slus/asm/psyq/old.s', '.include "wrapper.inc"\n')
        self.row.update(source_kind='platform_asm',asm_path='asm/psyq/old.s')
        self.write_window()
        baseline = W.window_recipes(self.root)
        self.assertEqual(self.reasons(baseline=baseline), ['include/modules/new.h'])


class LanderValidationTests(unittest.TestCase):
    setUp = L.LandPackagesTests.setUp
    tearDown = L.LandPackagesTests.tearDown
    git = L.LandPackagesTests.git

    def land(self):
        land = G.Lander(self.root,self.plan,self.base,self.log,scratch=True)
        land.before_certs = {}; land.before_l5 = 1; land.force_all = False; land.gate_reasons = []
        land.before_certificate_evidence = G.certificate_evidence(self.root)
        land.env['TMPDIR'] = str(self.base)
        return land

    def test_invalid_only_and_final_all_validation_surround_accounting(self):
        land = self.land(); calls = []
        p = self.base/'proof.log'; p.write_text('SLUS SHA-1 gate: MATCH\nrecipe identical to the pinned copy\nMATCH\n')
        land.run = lambda step,argv,**kw: (calls.append((step,argv)) or (p,0.01))
        land.regenerate = lambda: calls.append(('regenerate',[]))
        land.scrub = lambda: calls.append(('scrub',[]))
        with contextlib.redirect_stdout(io.StringIO()): land.validate()
        self.assertIn('--invalid-only', dict(calls)['certify-all'])
        self.assertIn('--validate-only', dict(calls)['certificate-final-validation'])
        self.assertEqual([c[0] for c in calls][-3:], ['regenerate','scrub','certificate-final-validation'])

    def test_l5_drop_remains_a_refusal(self):
        land = self.land(); land.before_l5 = 2
        p = self.base/'proof.log'; p.write_text('SLUS SHA-1 gate: MATCH\nrecipe identical to the pinned copy\nMATCH\n')
        land.run = lambda *args,**kw: (p,0.01)
        with contextlib.redirect_stdout(io.StringIO()), self.assertRaisesRegex(G.Stop,'L5 dropped'):
            land.validate()

    def validation_calls(self, land):
        calls = []; p = self.base/'proof.log'
        p.write_text('SLUS SHA-1 gate: MATCH\nrecipe identical to the pinned copy\nMATCH\n')
        land.run = lambda step,argv,**kw: (calls.append((step,argv)) or (p,0.01))
        land.regenerate = lambda: None; land.scrub = lambda: None
        with contextlib.redirect_stdout(io.StringIO()): land.validate()
        return dict(calls)

    def test_non_include_gate_reasons_renew_all(self):
        for reason in ('tools/build/mk_ovl_root.sh','tools/build/gate_all.py','tools/row_db.py','tools/common.py',
                       'toolchain/other.dat','tools/maspsx/other.dat','tools/gate/unlisted.py','plan gate_all=full'):
            with self.subTest(reason=reason):
                land = self.land(); land.force_all = True; land.gate_reasons = [reason]
                calls = self.validation_calls(land)
                self.assertIn('--all', calls['gate-all'])
                self.assertNotIn('--invalid-only', calls['certify-all'])
                self.assertIn('--validate-only', calls['certificate-final-validation'])

    def test_header_or_closure_only_full_gates_keep_selective_renewal(self):
        for reasons in (['include/existing.h'], ['include dependency closure unavailable: fixture'],
                        ['include/existing.h','include dependency closure unavailable: fixture']):
            with self.subTest(reasons=reasons):
                land = self.land(); land.force_all = True; land.gate_reasons = reasons
                calls = self.validation_calls(land)
                self.assertIn('--all', calls['gate-all'])
                self.assertIn('--invalid-only', calls['certify-all'])

    def test_mixed_header_and_tool_reasons_renew_all(self):
        land = self.land(); land.force_all = True
        land.gate_reasons = ['include/existing.h','tools/common.py']
        self.assertNotIn('--invalid-only', self.validation_calls(land)['certify-all'])

    def test_new_certificate_is_forced_from_pretransaction_snapshot(self):
        snapshot = G.Snapshot(self.root,self.base/'snapshot'); snapshot.quarantine()
        land = self.land(); land.before_certificate_evidence = snapshot.certificate_evidence
        p = self.root/'ledger/modules/overlay_new.json'; p.parent.mkdir(parents=True)
        p.write_text(json.dumps({'module':'new','reviewer':'new-reviewer'}))
        calls = self.validation_calls(land)
        argv = calls['certify-all']
        self.assertEqual(argv[argv.index('--renew')+1], 'new')
        self.assertIn('--invalid-only', argv)

    def test_accepted_certificate_byte_edit_is_forced_from_snapshot(self):
        snapshot,base,other = self.snapshot_fixture(); snapshot.quarantine()
        land = self.land(); land.before_certs = {'fixture':'fixture-reviewer'}
        land.before_certificate_evidence = snapshot.certificate_evidence
        p = self.root/'ledger/modules/overlay_fixture.json'; p.write_text(p.read_text()+'\n')
        argv = self.validation_calls(land)['certify-all']
        self.assertEqual(argv[argv.index('--renew')+1], 'fixture')

    def test_changed_referenced_proof_forces_renewal_with_unchanged_certificate(self):
        snapshot,base,other = self.snapshot_fixture(); snapshot.quarantine()
        land = self.land(); land.before_certs = {'fixture':'fixture-reviewer'}
        land.before_certificate_evidence = snapshot.certificate_evidence
        (base/'windows/window/window.bin').write_bytes(b'package-supplied proof')
        argv = self.validation_calls(land)['certify-all']
        self.assertEqual(argv[argv.index('--renew')+1], 'fixture')

    def test_identical_copies_and_unreferenced_cache_do_not_force_renewal(self):
        snapshot,base,other = self.snapshot_fixture(); snapshot.quarantine()
        land = self.land(); land.before_certs = {'fixture':'fixture-reviewer'}
        land.before_certificate_evidence = snapshot.certificate_evidence
        other.write_bytes(b'new cache')
        argv = self.validation_calls(land)['certify-all']
        self.assertIn('--invalid-only', argv)
        self.assertNotIn('--renew', argv)

    def snapshot_fixture(self):
        cert = self.root/'ledger/modules/overlay_fixture.json'; cert.parent.mkdir(parents=True)
        cert.write_text(json.dumps({'module':'fixture','reviewer':'fixture-reviewer',
          'proof_dir':'build_ovl_gate/work/module_proofs/fixture/module',
          'windows':[{'proof_dir':'build_ovl_gate/work/module_proofs/fixture/windows/window'}]}))
        self.git('add','ledger/modules');self.git('commit','-qm','certificate fixture')
        base = self.root/'build_ovl_gate/work/module_proofs/fixture'
        for name in ('module/receipt.json','windows/window/window.bin'):
            p = base/name;p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(b'proof fixture')
        other = self.root/'build_ovl_gate/work/cache';other.write_bytes(b'cache fixture')
        snapshot = G.Snapshot(self.root,self.base/'snapshot')
        return snapshot,base,other

    def test_quarantine_preserves_only_referenced_proofs_and_rollback_originals(self):
        snapshot,base,other = self.snapshot_fixture()
        snapshot.quarantine()
        self.assertEqual(len(snapshot.proofs_copied),2)
        self.assertFalse(other.exists())
        p = base/'module/receipt.json';self.assertEqual(p.read_bytes(),b'proof fixture')
        p.write_bytes(b'changed during renewal')
        self.assertEqual((snapshot.saved['build_ovl_gate']/'work/module_proofs/fixture/module/receipt.json').read_bytes(),b'proof fixture')
        snapshot.restore()
        self.assertEqual(p.read_bytes(),b'proof fixture');self.assertEqual(other.read_bytes(),b'cache fixture')

    def test_quarantine_does_not_follow_aliased_proof_artifacts(self):
        snapshot,base,other = self.snapshot_fixture()
        p = base/'module/alias';p.symlink_to(self.root/'src/demo/a.c')
        snapshot.quarantine()
        self.assertNotIn('build_ovl_gate/work/module_proofs/fixture/module',snapshot.proofs_copied)
        self.assertFalse((base/'module').exists())
        snapshot.restore();self.assertTrue(p.is_symlink())

if __name__ == '__main__': unittest.main()
