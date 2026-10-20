"""Real subprocess concurrency, reviewer preservation, timeout and cancellation."""
import importlib.util
import json
import os
from pathlib import Path
import signal
import subprocess
import sys
import tempfile
import time
import unittest

REPO=Path(__file__).resolve().parents[2];HELPER=REPO/'tools/lanes/certify_batch.py'

class CertifyBatchTests(unittest.TestCase):
    def setUp(self):
        (REPO/'tmp').mkdir(exist_ok=True);self.temp=tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR',str(REPO/'tmp')));self.addCleanup(self.temp.cleanup)
        self.base=Path(self.temp.name);self.root=self.base/'repo';(self.root/'ledger/modules').mkdir(parents=True)
        (self.root/'tools/fidelity').mkdir(parents=True)
        for key in ('a','b','c','d'):
            (self.root/'ledger/modules'/('overlay_'+key+'.json')).write_text(json.dumps({'module':key,'reviewer':'reviewer-'+key}))
        (self.root/'tools/fidelity/certify_overlay_module.py').write_text('''import argparse,json,os,subprocess,sys,time
from pathlib import Path
ap=argparse.ArgumentParser();ap.add_argument('key');ap.add_argument('--root');ap.add_argument('--reviewer');ap.add_argument('--window-workers');ap.add_argument('--gate-receipts');ap.add_argument('--transaction');a=ap.parse_args()
Path(a.key+'.pid').write_text(str(os.getpid()))
print(json.dumps({'reviewer':a.reviewer,'window_workers':a.window_workers,'transaction':a.transaction}),flush=True)
with Path('events.jsonl').open('a') as f:f.write(json.dumps({'key':a.key,'at':time.monotonic(),'delta':1})+'\\n')
if Path('fail').exists() and a.key=='a':time.sleep(.2);raise SystemExit(7)
if Path('slow').exists():
 p=subprocess.Popen([sys.executable,'-c','import time;time.sleep(60)']);Path(a.key+'.child.pid').write_text(str(p.pid));time.sleep(60)
else:time.sleep(.3)
with Path('events.jsonl').open('a') as f:f.write(json.dumps({'key':a.key,'at':time.monotonic(),'delta':-1})+'\\n')
''')
        self.logs=self.base/'logs'

    def argv(self):
        return [sys.executable,str(HELPER),'--root',str(self.root),'--workers','2','--window-workers','3','--log-dir',str(self.logs)]

    def test_parallel_jobs_keep_recorded_reviewers_and_separate_logs(self):
        result=subprocess.run(self.argv()+['--gate-receipts',str(self.base/'receipts'),'--transaction','token'],capture_output=True,text=True,timeout=15)
        self.assertEqual(result.returncode,0,result.stdout+result.stderr)
        events=sorted([json.loads(l) for l in (self.root/'events.jsonl').read_text().splitlines()],key=lambda r:r['at'])
        active=maximum=0
        for event in events:active+=event['delta'];maximum=max(maximum,active)
        self.assertEqual(maximum,2);self.assertEqual(active,0)
        summary=json.loads((self.logs/'summary.json').read_text());self.assertEqual(len(summary['certificates']),4)
        for key in 'abcd':
            rec=json.loads((self.logs/(key+'.log')).read_text());self.assertEqual(rec['reviewer'],'reviewer-'+key)
            self.assertEqual(rec['window_workers'],'3');self.assertEqual(rec['transaction'],'token')

    def test_invalid_from_plan_renews_exactly_the_planned_keys_without_revalidating(self):
        # the temp root has no certificate reader: any roster validation here would fail
        plan=self.base/'certplan.json';plan.write_text(json.dumps({'renew':['b','d'],'issue':[],'windows':[]}))
        result=subprocess.run(self.argv()+['--invalid-only','--no-final-validation','--invalid-from',str(plan)],capture_output=True,text=True,timeout=15)
        self.assertEqual(result.returncode,0,result.stdout+result.stderr)
        summary=json.loads((self.logs/'summary.json').read_text())
        self.assertEqual([c['module'] for c in summary['certificates']],['b','d']);self.assertEqual(summary['retained'],['a','c'])
        plan.write_text(json.dumps({'renew':['zz'],'issue':[],'windows':[]}))
        result=subprocess.run(self.argv()+['--invalid-only','--invalid-from',str(plan)],capture_output=True,text=True,timeout=15)
        self.assertNotEqual(result.returncode,0)
        result=subprocess.run(self.argv()+['--invalid-from',str(plan)],capture_output=True,text=True,timeout=15)
        self.assertNotEqual(result.returncode,0)

    def assert_children_stopped(self):
        for p in self.root.glob('*.pid'):
            value=p.read_text()
            if not value:continue  # cancelled between opening the marker and writing its PID
            pid=int(value);stat=Path('/proc')/str(pid)/'stat'
            if stat.exists():self.assertIn(stat.read_text().split(') ',1)[1].split()[0],('Z','X'))

    def test_failure_stops_entire_compiler_group(self):
        (self.root/'fail').touch();(self.root/'slow').touch()
        result=subprocess.run(self.argv(),capture_output=True,text=True,timeout=15)
        self.assertNotEqual(result.returncode,0);time.sleep(.1);self.assert_children_stopped()
        self.assertFalse((self.logs/'summary.json').exists())

    def test_module_timeout_stops_entire_compiler_group(self):
        (self.root/'slow').touch()
        result=subprocess.run(self.argv()+['--timeout','1'],capture_output=True,text=True,timeout=15)
        self.assertNotEqual(result.returncode,0);time.sleep(.1);self.assert_children_stopped()

    def test_lander_signal_can_cancel_all_helper_descendants(self):
        (self.root/'slow').touch()
        p=subprocess.Popen(self.argv(),stdout=subprocess.PIPE,stderr=subprocess.PIPE,start_new_session=True)
        try:
            deadline=time.monotonic()+5
            while not list(self.root.glob('*.child.pid')) and time.monotonic()<deadline:time.sleep(.02)
            self.assertTrue(list(self.root.glob('*.child.pid')))
            os.killpg(p.pid,signal.SIGTERM);p.communicate(timeout=5);time.sleep(.1);self.assert_children_stopped()
        finally:
            if p.poll() is None:os.killpg(p.pid,signal.SIGKILL);p.communicate()

if __name__=='__main__':unittest.main()
