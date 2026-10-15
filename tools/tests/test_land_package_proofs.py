"""No-git production handoff fixtures; real package subprocesses, mocked gates."""
import contextlib
import importlib.util
import io
import json
import os
from pathlib import Path
import shutil
import sys
import tempfile
import unittest
from unittest.mock import patch

TOOLS=Path(__file__).resolve().parents[1]
sys.path[:0]=[str(TOOLS/'lanes'),str(TOOLS)]
import package_proofs as P
spec=importlib.util.spec_from_file_location('proof_lander',TOOLS/'lanes/land_packages.py')
G=importlib.util.module_from_spec(spec);spec.loader.exec_module(G)


class PackageProofs(unittest.TestCase):
    def setUp(self):
        self.tmp=tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR'))
        self.addCleanup(self.tmp.cleanup)
        self.base=Path(self.tmp.name);self.root=self.base/'root';self.root.mkdir()
        self.package=self.base/'delivery';self.package.mkdir()
        (self.root/'src').mkdir();(self.root/'src/a.c').write_text('before')
        (self.root/'tools/lanes').mkdir(parents=True)
        shutil.copy2(TOOLS/'lanes/package_proofs.py',self.root/'tools/lanes/package_proofs.py')
        self.entry=self.package/'apply.py'
        self.entry.write_text('''import argparse,sys
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--root',type=Path);p.add_argument('--dry-run',action='store_true');p.add_argument('--live',action='store_true');a=p.parse_args()
r=a.root
# All guards precede any writes and any proof decision.
s=r/'src/a.c'
if s.read_text() not in ('before','after'):raise ValueError('source guard')
if a.dry_run:raise SystemExit(0)
s.write_text('after')
sys.path.insert(0,str(r/'tools/lanes'))
from package_proofs import run_proof
run_proof(r,Path(__file__).parent,'levels','ledger/levels.jsonl',[sys.executable,'-c',"from pathlib import Path;Path('proof-ran').write_text('yes')"])
''')
        self.plan=dict(packages=[dict(entry=str(self.entry))])
        self.log=self.base/'log.jsonl'
        self.land=G.Lander(self.root,self.plan,self.base,self.log,scratch=True)
        self.land.env['TMPDIR']=str(self.base/'tmp');(self.base/'tmp').mkdir()

    def mutate(self):
        with contextlib.redirect_stdout(io.StringIO()):self.land.mutate()

    def test_complete_transaction_defers_and_records_guarded_write(self):
        self.land.defer_package_proofs=True;self.mutate()
        self.assertEqual((self.root/'src/a.c').read_text(),'after')
        self.assertFalse((self.root/'proof-ran').exists())
        self.assertEqual(self.land.package_proofs,[dict(kind='levels',target='ledger/levels.jsonl',lane_receipts={})])
        self.assertIn('package-proof-policy',self.log.read_text())

    def test_preflight_preview_and_inherited_bare_env_retain_proof(self):
        with patch.dict(os.environ,{P.SKIP_ENV:'1',P.CONTEXT_ENV:'/invalid/context'}):
            self.land=G.Lander(self.root,self.plan,self.base,self.log,scratch=True)
        self.mutate()
        self.assertTrue((self.root/'proof-ran').is_file())
        self.assertEqual(self.land.package_proofs,[])

    def test_bad_guard_is_not_bypassed(self):
        self.land.defer_package_proofs=True;(self.root/'src/a.c').write_text('drift')
        with self.assertRaisesRegex(G.Stop,'dry-run failed'):self.mutate()
        self.assertEqual((self.root/'src/a.c').read_text(),'drift')

    def context(self):
        directory=self.base/'context';directory.mkdir()
        path=directory/'context.json'
        path.write_text(json.dumps(dict(schema=1,mode='production',root=str(self.root),package=str(self.package),
            entry=str(self.entry),entry_sha256=P.sha(self.entry),transaction='test')))
        (directory/'deferred.json').write_text(json.dumps(dict(context_sha256=P.sha(path),proofs=[])))
        return {P.SKIP_ENV:'1',P.CONTEXT_ENV:str(path)}

    def test_unknown_genuine_proof_and_bare_skip_are_not_deferred(self):
        with patch.dict(os.environ,{P.SKIP_ENV:'1'},clear=True):
            self.assertFalse(P.defer_proof(self.root,self.package,'levels','ledger/levels.jsonl'))
        with patch.dict(os.environ,self.context()):
            self.assertFalse(P.defer_proof(self.root,self.package,'slus-genuine','slus'))
            self.assertFalse(P.defer_proof(self.root,self.package,'levels','ledger/levels.jsonl',dry_run=True))
            with self.assertRaisesRegex(ValueError,'production config'):
                P.defer_proof(self.root,self.package,'overlay-window','work/fake.overlay.yaml')

    def test_standalone_canonical_receipt_reuses_and_stale_receipt_falls_back(self):
        import proof_receipts as R
        candidate=dict(kind='overlay-window',target='config/overlays/w.overlay.yaml',directory='proof')
        with patch.object(R,'package_receipts',return_value=[candidate]),patch.object(R,'verify',return_value={}), \
             patch.dict(os.environ,{},clear=True):
            self.assertTrue(P.defer_proof(self.root,self.package,candidate['kind'],candidate['target']))
            self.assertFalse(P.defer_proof(self.root,self.package,candidate['kind'],candidate['target'],dry_run=True))
        with patch.object(R,'package_receipts',return_value=[candidate]),patch.object(R,'verify',side_effect=ValueError('stale')), \
             patch.dict(os.environ,{},clear=True):
            self.assertFalse(P.defer_proof(self.root,self.package,candidate['kind'],candidate['target']))

    def test_production_helper_records_obligation_without_duplicate_receipt_hashing(self):
        import proof_receipts as R
        with patch.dict(os.environ,self.context()),patch.object(R,'package_receipts',side_effect=AssertionError('lander owns hashing')):
            self.assertTrue(P.defer_proof(self.root,self.package,'overlay-module','module'))

    def test_root_and_entry_drift_refuse_before_receipt(self):
        with patch.dict(os.environ,self.context()):
            with self.assertRaisesRegex(ValueError,'context differs'):
                P.defer_proof(self.base,self.package,'levels','ledger/levels.jsonl')
            self.entry.write_text('changed')
            with self.assertRaisesRegex(ValueError,'entry changed'):
                P.defer_proof(self.root,self.package,'levels','ledger/levels.jsonl')

    def test_lane_receipt_bytes_are_preserved_and_bound(self):
        score=self.package/'scores.json';score.write_text('{"lane":"exact"}')
        before=score.read_bytes()
        env=self.context()
        with patch.dict(os.environ,env):
            self.assertTrue(P.defer_proof(self.root,self.package,'overlay-module','module',['scores.json']))
        doc=json.loads((Path(env[P.CONTEXT_ENV]).parent/'deferred.json').read_text())
        self.assertEqual(doc['proofs'][0]['lane_receipts'],{'scores.json':P.sha(score)})
        self.assertEqual(before,score.read_bytes())

    def validation(self, fail=None, reasons=()):
        self.land.package_proofs=[dict(kind='overlay-window',target='config/overlays/w.overlay.yaml'),
                                  dict(kind='overlay-module',target='m')]
        self.land.before_certs={'m':'reviewer'};self.land.before_l5=0
        self.land.force_all=bool(reasons);self.land.gate_reasons=list(reasons)
        (self.root/'config/overlays').mkdir(parents=True)
        (self.root/'STATUS.md').write_text('')
        output=self.base/'pass.log';output.write_text('SLUS SHA-1 gate: MATCH\nrecipe identical to the pinned copy\nMATCH\n')
        calls={}
        def run(step,argv,**kw):
            calls[step]=argv
            if step==fail:raise G.Stop('injected proof failure')
            return output,0
        with patch.object(self.land,'run',side_effect=run),patch.object(self.land,'certificates',return_value={'m':'reviewer'}), \
             patch.object(G,'uncertified',return_value=({},[])),patch.object(G,'certificate_evidence',return_value={'m':{}}), \
             patch.object(self.land,'regenerate'),patch.object(self.land,'scrub'),contextlib.redirect_stdout(io.StringIO()):
            self.land.validate()
        return calls

    def test_discharge_requires_fresh_windows_and_forced_module_renewal(self):
        calls=self.validation()
        self.assertIn('--require-window',calls['gate-all'])
        self.assertIn('config/overlays/w.overlay.yaml',calls['gate-all'])
        self.assertIn('--renew',calls['certify-all']);self.assertIn('m',calls['certify-all'])
        self.assertIn('--validate-only',calls['certificate-final-validation'])
        self.assertIn('package-proofs-discharged',self.log.read_text())

    def test_scoped_certificates_remain_selective_after_global_tool_gate(self):
        (self.root/'config').mkdir(exist_ok=True)
        (self.root/'config/overlay_fingerprint_schema').write_text('overlay-module-scoped-v2\n')
        calls=self.validation(reasons=['tools/build/gate_all.py'])
        self.assertIn('--all',calls['gate-all'])
        self.assertIn('--invalid-only',calls['certify-all'])
        self.assertIn('--renew',calls['certify-all'])

    def test_failed_final_validation_never_discharges_obligations(self):
        with self.assertRaisesRegex(G.Stop,'proof failure'):self.validation('certificate-final-validation')
        self.assertFalse(self.log.exists() and 'package-proofs-discharged' in self.log.read_text())

    def test_later_package_invalidates_an_earlier_carried_window(self):
        import hashlib
        import proof_receipts as R
        # The receipt is exact for package 1's post-apply source. Package 2
        # changes the same input: only the final tree can authorize reuse.
        evidence=self.package/'proof';evidence.mkdir()
        (evidence/'window.bin').write_bytes(b'retail')
        expected=dict(source=hashlib.sha256(b'after').hexdigest(),retail=dict(slice_sha256=hashlib.sha256(b'retail').hexdigest(),start=0,end=6))
        R.publish(evidence,'overlay-window','config/overlays/w.overlay.yaml',expected,expected,'MATCH')
        (self.package/'proofs.json').write_text(json.dumps([dict(kind='overlay-window',target='config/overlays/w.overlay.yaml',directory='proof')]))
        seal={str(p.relative_to(self.package)):R.sha(p) for p in self.package.rglob('*') if p.is_file()}
        (self.package/'package.sha256.json').write_text(json.dumps(seal))
        second=self.base/'second';second.mkdir();entry=second/'apply.py'
        entry.write_text("import argparse\nfrom pathlib import Path\np=argparse.ArgumentParser();p.add_argument('--root',type=Path);p.add_argument('--dry-run',action='store_true');a=p.parse_args()\ns=a.root/'src/a.c'\nassert s.read_text()=='after'\nif not a.dry_run:s.write_text('after-second')\n")
        self.land.plan['packages'].append(dict(entry=str(entry)))
        self.land.defer_package_proofs=True
        def current(*args):return dict(expected,source=R.sha(self.root/'src/a.c'))
        with patch.object(R,'inputs',side_effect=current):
            self.mutate()
            self.assertEqual(len(self.land.carried_proofs),1)
            with self.assertRaisesRegex(ValueError,'inputs changed'):R.verify(self.root,evidence)
            calls=self.validation()
        self.assertNotIn('--carried-proofs',calls['gate-all'])
        self.assertIn('--require-window',calls['gate-all'])
        events=[json.loads(s) for s in self.log.read_text().splitlines()]
        self.assertTrue(any(e.get('step')=='package-carried-proof' and e.get('current') for e in events))
        self.assertTrue(any(e.get('step')=='carried-proof-final-tree' and e.get('result')=='REPROVE' for e in events))

    def test_post_commit_audit_queue_schema_error_is_logged_without_rollback(self):
        import audit_full
        self.land.plan.update(reviewer='reviewer',commit_message='fixture')
        self.land.bookkeeping={}
        def git(root,*args):return b'fixture-head\n' if args[0]=='rev-parse' else b''
        with patch.object(G,'git',side_effect=git),patch.object(audit_full,'record_landing',side_effect=KeyError('count')), \
             contextlib.redirect_stdout(io.StringIO()):self.land.commit()
        events=[json.loads(s) for s in self.log.read_text().splitlines()]
        self.assertTrue(any(e['step']=='COMMITTED' for e in events))
        self.assertTrue(any(e['step']=='async-audit-enqueue' and e.get('result')=='HOLD' for e in events))

    def test_global_gate_gaps_and_ordinary_source_remain_incremental(self):
        for name in ['config/names.tsv','config/slus_006.14.symbols.txt','tools/build/main_sdk_asm.py',
                     'tools/lanes/proof_receipts.py','tools/lanes/proof_scope.py','tools/build/cc.sh','tools/build/ccproc.py','tools/build/as.sh','tools/build/asproc.py']:
            with self.subTest(name=name):self.assertIn(name,G.full_gate_reasons({name},{}))
        self.assertEqual(G.full_gate_reasons({'src/town/a.c','src/shared/local.h','include/private.h','asm/sdk.s','config/overlays/main.as_flags.jsonl','tools/status.py','tools/row_cache.py'},{}),[])
        self.assertEqual(G.full_gate_reasons({'config/custom.txt'},{},baseline={'unhashed_inputs':['config/custom.txt']}),[])

if __name__=='__main__':unittest.main()
