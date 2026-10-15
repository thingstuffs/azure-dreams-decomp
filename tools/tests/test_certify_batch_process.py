"""Persistent producer isolation and canonical validation parity in real processes."""
import json
import os
from pathlib import Path
import signal
import subprocess
import sys
import time
import unittest
from test_certify_batch import CertifyBatchTests


class PersistentCertificateTests(CertifyBatchTests):
    def setUp(self):
        super().setUp()
        (self.root/'tools/fidelity/certify_overlay_module.py').write_text('''import json,os,subprocess,sys,time
from pathlib import Path
COUNT=0
def certify(key,root,reviewer,gate_receipts=None,transaction=None,window_workers=1):
 global COUNT
 COUNT+=1
 Path(key+'.pid').write_text(str(os.getpid()))
 with Path('events.jsonl').open('a') as f:f.write(json.dumps({'key':key,'at':time.monotonic(),'delta':1})+'\\n')
 print(json.dumps({'key':key,'count':COUNT,'pid':os.getpid(),'reviewer':reviewer,'window_workers':window_workers,'receipts':str(gate_receipts),'transaction':transaction}),flush=True)
 if Path('fail').exists() and key=='a':time.sleep(.2);raise ValueError('producer refused a')
 if Path('slow').exists():
  p=subprocess.Popen([sys.executable,'-c','import time;time.sleep(60)']);Path(key+'.child.pid').write_text(str(p.pid));time.sleep(60)
 else:time.sleep(.3)
 with Path('events.jsonl').open('a') as f:f.write(json.dumps({'key':key,'at':time.monotonic(),'delta':-1})+'\\n')
 return {'module':key,'members':[],'windows':[]},Path('ledger/modules')/('overlay_'+key+'.json')
''')

    def test_deadline_does_not_wait_for_producer_thread_pool_cleanup(self):
        producer=self.root/'tools/fidelity/certify_overlay_module.py'
        producer.write_text(producer.read_text()+"""
from concurrent.futures import ThreadPoolExecutor
original=certify
def certify(*args,**kw):
 with ThreadPoolExecutor(max_workers=1) as pool:
  pending=pool.submit(time.sleep,60)
  return original(*args,**kw)
""")
        (self.root/'slow').touch()
        start=time.monotonic()
        result=subprocess.run(self.argv()+['--timeout','1'],capture_output=True,text=True,timeout=8)
        self.assertNotEqual(result.returncode,0)
        self.assertLess(time.monotonic()-start,5)
        time.sleep(.1);self.assert_children_stopped()

    def argv(self):
        return super().argv()+['--worker-mode','process']

    def test_parallel_jobs_keep_recorded_reviewers_and_separate_logs(self):
        receipts=self.base/'receipts'
        result=subprocess.run(self.argv()+['--gate-receipts',str(receipts),'--transaction','token'],capture_output=True,text=True,timeout=15)
        self.assertEqual(result.returncode,0,result.stdout+result.stderr)
        events=sorted([json.loads(l) for l in (self.root/'events.jsonl').read_text().splitlines()],key=lambda r:r['at'])
        active=maximum=0
        for event in events:active+=event['delta'];maximum=max(maximum,active)
        self.assertEqual((maximum,active),(2,0))
        records=[json.loads((self.logs/(key+'.log')).read_text().splitlines()[0]) for key in 'abcd']
        self.assertEqual(len({r['pid'] for r in records}),2)
        self.assertGreater(max(r['count'] for r in records),1)
        for r in records:
            self.assertEqual(r['reviewer'],'reviewer-'+r['key'])
            self.assertEqual(r['window_workers'],3)
            self.assertEqual(r['receipts'],str(receipts));self.assertEqual(r['transaction'],'token')
        self.assertEqual(json.loads((self.logs/'summary.json').read_text())['worker_mode'],'process')

    def receipt_fixture(self):
        directory=self.base/'receipts';(directory/'shared').mkdir(parents=True)
        (directory/'index.json').write_text(json.dumps({'windows':{'config/overlays/shared.overlay.yaml':'fixture'}}))
        (directory/'shared/receipt.json').write_text(json.dumps({'config':'config/overlays/shared.overlay.yaml'}))
        producer=self.root/'tools/fidelity/certify_overlay_module.py'
        producer.write_text(producer.read_text()+"""
import contextlib,fcntl
@contextlib.contextmanager
def certification_window_lock(root,name):
 with (root.parent/'shared-window.lock').open('a') as f:
  fcntl.flock(f,fcntl.LOCK_EX)
  try:yield
  finally:fcntl.flock(f,fcntl.LOCK_UN)
def fresh_window_source(root,wn,directory,transaction):
 if (root.parent/'bad-receipt').exists():raise ValueError('canonical receipt refused')
 return None if (root.parent/'stale-receipt').exists() else directory/'shared'
original=certify
def certify(key,root,reviewer,gate_receipts=None,transaction=None,window_workers=1):
 with certification_window_lock(root,'shared'):
  fresh=fresh_window_source(root,'config/overlays/shared.overlay.yaml',gate_receipts,transaction)
  with Path('critical.jsonl').open('a') as f:f.write(json.dumps({'at':time.monotonic(),'delta':1})+'\\n')
  try:return original(key,root,reviewer,gate_receipts,transaction,window_workers)
  finally:
   with Path('critical.jsonl').open('a') as f:f.write(json.dumps({'at':time.monotonic(),'delta':-1})+'\\n')
""")
        return directory

    def critical_maximum(self):
        active=maximum=0
        records=[json.loads(l) for l in (self.root/'critical.jsonl').read_text().splitlines()]
        for r in sorted(records,key=lambda r:r['at']):active+=r['delta'];maximum=max(maximum,active)
        self.assertEqual(active,0)
        return maximum

    def test_immutable_receipt_reads_do_not_serialize_producers(self):
        directory=self.receipt_fixture()
        result=subprocess.run(self.argv()+['--gate-receipts',str(directory),'--transaction','fixture'],capture_output=True,text=True,timeout=15)
        self.assertEqual(result.returncode,0,result.stdout+result.stderr)
        self.assertEqual(self.critical_maximum(),2)

    def test_stale_receipt_retries_before_fallback_with_canonical_lock(self):
        directory=self.receipt_fixture();(self.root/'stale-receipt').touch()
        result=subprocess.run(self.argv()+['--gate-receipts',str(directory),'--transaction','fixture'],capture_output=True,text=True,timeout=15)
        self.assertEqual(result.returncode,0,result.stdout+result.stderr)
        self.assertEqual(self.critical_maximum(),1)
        for key in 'abcd':self.assertIn('retrying with canonical window locks',(self.logs/(key+'.log')).read_text())

    def test_canonical_receipt_refusal_is_never_bypassed(self):
        directory=self.receipt_fixture();(self.root/'bad-receipt').touch()
        result=subprocess.run(self.argv()+['--gate-receipts',str(directory),'--transaction','fixture'],capture_output=True,text=True,timeout=15)
        self.assertNotEqual(result.returncode,0)
        self.assertFalse((self.root/'critical.jsonl').exists())
        self.assertTrue(any('canonical receipt refused' in p.read_text() for p in self.logs.glob('*.log')))


class ParallelValidationTests(CertifyBatchTests):
    # Reuse only the fixture and argv; the inherited tests retain coverage of
    # the unchanged subprocess mode in their original class.
    def reader(self):
        (self.root/'tools/overlay_module_evidence.py').write_text('''import json,time
import yaml
from pathlib import Path
def load_modules(root):
 if (root/'bad-manifest').exists():raise ValueError('fixture manifest')
 return [{'key':key} for key in 'abcd']
def certificate_reason(m,cert,root):
 time.sleep(.1)
 if cert.get('crash'):raise ValueError('fixture proof')
 return None if cert.get('valid') else 'fixture stale'
def module_status(root):
 try:mods=load_modules(root)
 except (OSError,ValueError,KeyError,TypeError,NameError,yaml.YAMLError) as e:return [{'module':{'key':'manifest','members':[]},'valid':False,'reason':'manifest invalid: '+type(e).__name__+': '+str(e)}]
 out=[]
 for m in mods:
  cert=None
  try:
   cert=json.loads((root/'ledger/modules'/('overlay_'+m['key']+'.json')).read_text());reason=certificate_reason(m,cert,root)
  except (OSError,ValueError,KeyError,TypeError,AttributeError,IndexError,NameError,yaml.YAMLError) as e:reason='certificate missing/invalid: '+type(e).__name__+': '+str(e)
  out.append({'module':m,'certificate':cert,'valid':reason is None,'reason':reason})
 return out
''')
        for key in 'abcd':
            p=self.root/'ledger/modules'/('overlay_'+key+'.json');r=json.loads(p.read_text());r['valid']=True;p.write_text(json.dumps(r))

    def validate(self,workers):
        argv=self.argv();argv[argv.index('--workers')+1]=str(workers)
        return subprocess.run(argv+['--validate-only'],capture_output=True,text=True,timeout=15)

    def test_parallel_validation_matches_serial_for_good_and_bad_proofs(self):
        self.reader()
        before={p:p.read_bytes() for p in (self.root/'ledger/modules').glob('*')}
        self.assertEqual(self.validate(1).returncode,0)
        self.assertEqual(self.validate(2).returncode,0)
        self.assertEqual(before,{p:p.read_bytes() for p in before})
        for change in ({'valid':False},{'crash':True}):
            p=self.root/'ledger/modules/overlay_b.json';r=json.loads(before[p]);r.update(change);p.write_text(json.dumps(r))
            serial=self.validate(1);parallel=self.validate(2)
            self.assertNotEqual(parallel.returncode,0)
            self.assertEqual(serial.stderr,parallel.stderr)
        self.assertFalse((self.root/'events.jsonl').exists())

    def test_parallel_validation_preserves_manifest_refusal(self):
        self.reader();(self.root/'bad-manifest').touch()
        serial=self.validate(1);parallel=self.validate(2)
        self.assertNotEqual(parallel.returncode,0);self.assertEqual(serial.stderr,parallel.stderr)
        self.assertIn('manifest invalid: ValueError: fixture manifest',parallel.stderr)

    def test_terminating_validator_stops_workers_and_descendants(self):
        self.reader()
        reader=self.root/'tools/overlay_module_evidence.py'
        reader.write_text(reader.read_text()+"""
import subprocess,sys
def certificate_reason(m,cert,root):
 child=subprocess.Popen([sys.executable,'-c','import time;time.sleep(60)'])
 (root/(m['key']+'.child.pid')).write_text(str(child.pid))
 (root/(m['key']+'.pid')).write_text(str(os.getpid()))
 time.sleep(60)
import os
""")
        p=subprocess.Popen(self.argv()+['--validate-only'],stdout=subprocess.PIPE,stderr=subprocess.PIPE,start_new_session=True)
        try:
            deadline=time.monotonic()+5
            while not list(self.root.glob('*.child.pid')) and time.monotonic()<deadline:time.sleep(.02)
            self.assertTrue(list(self.root.glob('*.child.pid')))
            p.terminate();p.communicate(timeout=5);time.sleep(.1)
            self.assertNotEqual(p.returncode,0);self.assert_children_stopped()
        finally:
            if p.poll() is None:os.killpg(p.pid,signal.SIGKILL);p.communicate()
            else:
                try:os.killpg(p.pid,signal.SIGKILL)
                except ProcessLookupError:pass

    def test_parallel_validation_reports_missing_certificate(self):
        self.reader();(self.root/'ledger/modules/overlay_c.json').unlink()
        # A missing unrecorded proof is still a status, but only the recorded
        # roster is required by certify_batch, exactly as in the serial reader.
        self.assertEqual(self.validate(1).returncode,0)
        self.assertEqual(self.validate(2).returncode,0)


if __name__=='__main__':unittest.main()
