"""Exercise the real batch/coherence input-stage protocol in disposable repos.

Compiler stand-ins deliberately test transaction control only; production byte
proofs are separate. No canonical checkout, fake function or gate is installed.
"""
import contextlib
import importlib.util
import io
import json
import os
from pathlib import Path
import shutil
import subprocess
import unittest
from unittest.mock import patch

HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('batch_fixture',HERE/'test_land_fast_front.py')
H=importlib.util.module_from_spec(spec);spec.loader.exec_module(H)
spec=importlib.util.spec_from_file_location('batch_stage',HERE.parent/'lanes/batch_inputs.py')
B=importlib.util.module_from_spec(spec);spec.loader.exec_module(B)

class BatchStageTests(unittest.TestCase):
    tearDown=H.FastFrontTests.tearDown
    git=H.FastFrontTests.git
    script=H.FastFrontTests.script
    invoke=H.FastFrontTests.invoke
    write_plan=H.FastFrontTests.write_plan
    screen=H.FastFrontTests.screen
    put=H.FastFrontTests.put
    land=H.FastFrontTests.land
    package=H.FastFrontTests.package

    def setUp(self):
        H.FastFrontTests.setUp(self)
        # Real coherence bash with only its verifier dependencies replaced in a
        # disposable repo. The tested bash keeps all refusal/complete-set checks.
        self.put('tools/lanes/land_coherence.sh',(HERE.parent/'lanes/land_coherence.sh').read_text())
        self.put('tools/build/build_slus.sh','#!/bin/bash\nset -e\necho MATCH\n')
        self.put('tools/build/mk_ovl_root.sh','#!/bin/bash\nset -e\necho view rebuilt\n')
        self.put('tools/common.py',"""import hashlib,json
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1];LEDGER=ROOT/'ledger'
def read_jsonl(p):return [json.loads(l) for l in p.read_text().splitlines() if l.strip()] if p.exists() else []
def rows():return read_jsonl(LEDGER/'rows.jsonl')
def clean_path(row):return ROOT/('src/'+row['id']+'.c')
def sha_text(s):return hashlib.sha256(s.encode()).hexdigest()
def parse_cfg(s):return s.split()[0],s.split()[1:]
def set_row_cfg(rid,cfg,note=''):
 rs=rows()
 for r in rs:
  if r['id']==rid:r['cfg']=cfg
 (LEDGER/'rows.jsonl').write_text(''.join(json.dumps(r)+'\\n' for r in rs))
""")
        self.put('tools/pin_census.py',"def sites_of(text):return []\ndef landing_refusal(*args,**kwargs):return None\n")
        self.put('tools/verify.py',"def verify(row,path,**kwargs):return {'exact':path.read_text()!='bad', 'status':'test stand-in'}\n")
        self.put('tools/apply_candidates.py',"""import argparse,json,sys
from pathlib import Path
sys.path.insert(0,'tools')
from common import rows,clean_path,sha_text,LEDGER
p=argparse.ArgumentParser();p.add_argument('dir');p.add_argument('--transform');p.add_argument('--workers');a=p.parse_args()
recs=[]
for r in rows():
 q=Path(a.dir)/(r['id']+'.c')
 if q.exists():
  text=q.read_text();clean_path(r).write_text(text);recs.append({'id':r['id'],'outcome':'applied'})
out=LEDGER/'sweeps'/(a.transform+'.jsonl');out.parent.mkdir(parents=True,exist_ok=True);out.write_text(''.join(json.dumps(r)+'\\n' for r in recs))
""")
        self.put('ledger/rows.jsonl',json.dumps({'id':'demo/a','cfg':'old','size':4})+'\n')
        self.put('ledger/recipe_trades.jsonl','')
        self.git('add','.');self.git('commit','-qm','synthetic batch control dependencies')
        self.lane=self.base/'lane';(self.lane/'out/demo').mkdir(parents=True)
        self.spec={'coherence':[{'tag':'test','lane':str(self.lane)}],'promotions':[]}
    def candidate(self,text='new',base=None):
        (self.lane/'cells.jsonl').write_text(json.dumps({'id':'demo/a','to':'new','coherence':'test stand-in'})+'\n')
        (self.lane/'out/demo/a.c').write_text(text)
        (self.lane/'out/demo/a.c.base_sha').write_text(base or H.G.digest(self.root/'src/demo/a.c'))
    def execute(self):
        with patch.dict(os.environ,TMPDIR=str(self.base)),contextlib.redirect_stdout(io.StringIO()):B.execute(self.root,self.base,self.spec)
    def test_complete_real_coherence_protocol_copies_only_verified_outputs(self):
        self.candidate();self.execute()
        self.assertEqual((self.root/'src/demo/a.c').read_text(),'new')
        self.assertEqual(H.G.records(self.root/'ledger/rows.jsonl')[0]['cfg'],'new')
        self.assertEqual(len(H.G.records(self.root/'ledger/recipe_trades.jsonl')),1)
        self.assertFalse((self.root/'build_ovl').exists())
        self.assertFalse(list(self.base.glob('batch-*')))
        self.assertFalse(list((self.root/'tmp').glob('batch-*')))
    def test_refused_candidate_keeps_outer_root_identical(self):
        self.candidate('bad');before=H.G.inventory(self.root,H.G.MANAGED)
        with self.assertRaises(subprocess.CalledProcessError):self.execute()
        self.assertEqual(H.G.inventory(self.root,H.G.MANAGED),before)
        self.assertFalse(list(self.base.glob('batch-*')))
    def test_stale_cell_is_incomplete_and_not_copied_back(self):
        self.candidate(base='0'*64);before=H.G.inventory(self.root,H.G.MANAGED)
        with self.assertRaises(subprocess.CalledProcessError):self.execute()
        self.assertEqual(H.G.inventory(self.root,H.G.MANAGED),before)
    def test_candidate_already_landed_is_idempotent(self):
        self.candidate('original\n');p=self.root/'ledger/rows.jsonl'
        p.write_text(json.dumps({'id':'demo/a','cfg':'new','size':4})+'\n')
        self.execute();self.assertEqual((self.root/'src/demo/a.c').read_text(),'original\n')
        self.assertEqual(H.G.records(self.root/'ledger/recipe_trades.jsonl'),[])

    def test_external_lane_directory_alias_is_read_only_and_usable(self):
        self.candidate();alias=self.base/'external-lane';alias.symlink_to(self.lane,target_is_directory=True)
        self.spec['coherence'][0]['lane']=str(alias)
        before=H.G.inventory(self.lane,['out','cells.jsonl']);self.execute()
        self.assertEqual((self.root/'src/demo/a.c').read_text(),'new')
        self.assertEqual(H.G.inventory(self.lane,['out','cells.jsonl']),before)

    def test_candidate_file_alias_escape_is_still_refused(self):
        self.candidate();p=self.lane/'out/demo/a.c';p.unlink();p.symlink_to(self.root/'src/demo/a.c')
        before=H.G.inventory(self.root,H.G.MANAGED)
        with self.assertRaisesRegex(B.G.Stop,'symlink'):self.execute()
        self.assertEqual(H.G.inventory(self.root,H.G.MANAGED),before)

if __name__=='__main__':unittest.main()
