"""First-certificate issuing (certify_batch --issue) and the lander's row_db check; no real certification."""
import contextlib
import importlib.util
import io
import json
from pathlib import Path
import subprocess
import sys
import unittest
from test_certify_batch import CertifyBatchTests,HELPER

HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('issue_fast_front_fixtures',HERE/'test_land_fast_front.py')
F=importlib.util.module_from_spec(spec);spec.loader.exec_module(F)
spec=importlib.util.spec_from_file_location('issue_batch',HELPER)
B=importlib.util.module_from_spec(spec);spec.loader.exec_module(B)

GOOD={'membership':'reviewed','types':'reviewed','ownership':'reviewed'}

def manifest(root,**reviews):
    mods=[{'key':k,'review':v} for k,v in reviews.items()]
    (root/'config/overlays').mkdir(parents=True,exist_ok=True)
    (root/'config/overlays/modules.json').write_text(json.dumps({'modules':mods}))


class ReviewSelectionTests(unittest.TestCase):
    def test_review_complete_requires_named_reviewer_and_all_fields_reviewed(self):
        self.assertTrue(B.review_complete({'review':dict(GOOD,reviewer='rev')}))
        for review in (None,{},{'reviewer':'rev'},dict(GOOD),dict(GOOD,reviewer='pending'),dict(GOOD,reviewer=''),
                       dict(GOOD,reviewer='rev',types='pending'),dict(GOOD,reviewer='rev',ownership='')):
            self.assertFalse(B.review_complete({'review':review}),review)
        self.assertFalse(B.review_complete({}))


class IssueTests(unittest.TestCase):
    argv=CertifyBatchTests.argv

    def setUp(self):
        CertifyBatchTests.setUp(self)
        manifest(self.root,a=dict(GOOD,reviewer='reviewer-a'),new=dict(GOOD,reviewer='rev-new'),
                 half=dict(GOOD,reviewer='rev-half',types='pending'),none={})
        (self.root/'tools/fidelity/certify_overlay_module.py').write_text('''import argparse,json
from pathlib import Path
ap=argparse.ArgumentParser();ap.add_argument('key');ap.add_argument('--root');ap.add_argument('--reviewer');ap.add_argument('--window-workers');ap.add_argument('--gate-receipts');ap.add_argument('--transaction');a=ap.parse_args()
print(json.dumps({'reviewer':a.reviewer}),flush=True)
if a.key!='nowrite':Path('ledger/modules/overlay_'+a.key+'.json').write_text(json.dumps({'module':a.key,'reviewer':a.reviewer}))
''')

    def run_batch(self,*extra,mode='subprocess'):
        return subprocess.run(self.argv()+['--worker-mode',mode,*extra],capture_output=True,text=True,timeout=30)

    def test_uncertified_lists_ready_and_waiting(self):
        ready,waiting=B.uncertified(self.root)
        self.assertEqual(ready,{'new':'rev-new'});self.assertEqual(waiting,['half','none'])

    def test_issue_uses_manifest_reviewer_in_same_pool_and_keeps_roster(self):
        r=self.run_batch('--issue','new')
        self.assertEqual(r.returncode,0,r.stdout+r.stderr)
        summary=json.loads((self.logs/'summary.json').read_text())
        self.assertEqual(summary['issued'],['new']);self.assertEqual(len(summary['certificates']),5)
        self.assertEqual(json.loads((self.logs/'new.log').read_text())['reviewer'],'rev-new')
        self.assertEqual(json.loads((self.root/'ledger/modules/overlay_new.json').read_text())['reviewer'],'rev-new')
        self.assertEqual(json.loads((self.root/'ledger/modules/overlay_a.json').read_text())['reviewer'],'reviewer-a')

    def test_issue_in_persistent_process_workers(self):
        (self.root/'tools/fidelity/certify_overlay_module.py').write_text('''import json
from pathlib import Path
def certify(key,root,reviewer,gate_receipts=None,transaction=None,window_workers=1):
 path=Path('ledger/modules')/('overlay_'+key+'.json');path.write_text(json.dumps({'module':key,'reviewer':reviewer}))
 return {'module':key,'members':[],'windows':[]},path
''')
        r=self.run_batch('--issue','new',mode='process')
        self.assertEqual(r.returncode,0,r.stdout+r.stderr)
        self.assertEqual(json.loads((self.root/'ledger/modules/overlay_new.json').read_text())['reviewer'],'rev-new')
        self.assertEqual(json.loads((self.logs/'summary.json').read_text())['issued'],['new'])

    def test_refusals_launch_nothing(self):
        for key in ('half','none','absent','a'):
            r=self.run_batch('--issue',key)
            self.assertNotEqual(r.returncode,0,key)
        self.assertFalse((self.root/'ledger/modules/overlay_half.json').exists())
        self.assertFalse(self.logs.exists() and list(self.logs.glob('*.log')))

    def test_issue_conflicts_with_validate_only(self):
        r=self.run_batch('--validate-only','--issue','new');self.assertNotEqual(r.returncode,0)
        self.assertFalse((self.root/'ledger/modules/overlay_new.json').exists())

    def test_missing_certificate_after_producer_fails_closed(self):
        manifest(self.root,nowrite=dict(GOOD,reviewer='rev-x'),a=dict(GOOD,reviewer='reviewer-a'))
        r=self.run_batch('--issue','nowrite');self.assertNotEqual(r.returncode,0)


class RowDbCheckTests(F.FastFrontTests):
    def test_row_db_failure_stops_fast_front_with_its_output(self):
        self.screen()
        self.put('tools/row_db.py',"print('overlay: raw/x.c missing');print('2 problems');raise SystemExit(1)\n")
        self.git('add','.');self.git('commit','-qm','failing row_db')
        self.assertEqual(self.invoke(),1)
        events=[json.loads(s) for s in self.log.read_text().splitlines()]
        steps=[e['step'] for e in events if 'command' in e]
        self.assertEqual(steps[-1],'row-db-check')
        self.assertNotIn('fast-levels',steps)
        error=events[-1]['error']
        self.assertIn('row_db check failed',error);self.assertIn('raw/x.c missing',error);self.assertIn('2 problems',error)

    def test_row_db_pass_is_logged_and_runs_after_registry_index_graph(self):
        self.screen()
        self.put('tools/row_db.py',"print('row database OK')\n")
        self.git('add','.');self.git('commit','-qm','passing row_db')
        self.invoke()
        text=self.log.read_text()
        self.assertIn('ROW_DB_CHECK_PASS',text)
        steps=[json.loads(s)['step'] for s in text.splitlines() if '"command"' in s]
        self.assertLess(steps.index('graph'),steps.index('row-db-check'))
        self.assertLess(steps.index('row-db-check'),steps.index('fast-levels'))

if __name__=='__main__':unittest.main()
