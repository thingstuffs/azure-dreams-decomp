"""Transaction behavior tests using small real git repositories, no mock gates."""
import contextlib
import hashlib
import importlib.util
import io
import json
import os
from pathlib import Path
import subprocess
import tempfile
import unittest
from unittest.mock import patch

MODULE=Path(__file__).resolve().parents[1]/'lanes/land_packages.py'
spec=importlib.util.spec_from_file_location('lander',MODULE)
G=importlib.util.module_from_spec(spec);spec.loader.exec_module(G)

class LandPackagesTests(unittest.TestCase):
    def setUp(self):
        tmpdir=Path(os.environ.get('TMPDIR',str(Path(__file__).resolve().parents[2]/'tmp')));tmpdir.mkdir(parents=True,exist_ok=True)
        self.tmp=tempfile.TemporaryDirectory(dir=tmpdir)
        self.base=Path(self.tmp.name);self.root=self.base/'repo';self.root.mkdir()
        self.git('init','-q');self.git('config','user.name','Test');self.git('config','user.email','test@example.invalid')
        for p,data in {'.gitignore':'build_ovl*/\nbuild_slus/\nwork/\nledger/cache/\n',
          'src/demo/a.c':'original\n','ledger/model_capacity.jsonl':'initial bookkeeping\n',
          'ledger/levels.jsonl':'{"level":5}\n','ledger/splits/dungeon.jsonl':'{"id":"old","reviewer":null}\n',
          'config/noreturn_syms.town.txt':'census\n','config/overlays/existing.overlay.yaml':'file_start: 10\n',
          'tools/registry.py':'','STATUS.md':'before\n'}.items():
            q=self.root/p;q.parent.mkdir(parents=True,exist_ok=True);q.write_text(data)
        self.git('add','.');self.git('commit','-qm','initial')
        self.plan={'version':1,'reviewer':'pending','commit':False,'commit_message':'test'}
        self.log=self.base/'land.jsonl'
    def tearDown(self): self.tmp.cleanup()
    def git(self,*args):return subprocess.check_output(['git','-C',str(self.root),*args],stderr=subprocess.STDOUT,env=dict(os.environ,GIT_OPTIONAL_LOCKS='0'))
    def write_plan(self):
        p=self.base/'plan.json';p.write_text(json.dumps(self.plan));return p
    def invoke(self,extra=()):
        with contextlib.redirect_stdout(io.StringIO()),patch.object(G,'busy_processes',return_value=[]):
            return G.main(['--root',str(self.root),'--plan',str(self.write_plan()),'--scratch','--log',str(self.log),*extra])
    def script(self,body,name='package.py'):
        p=self.base/name;p.write_text(body);return p
    def test_dry_run_failure_restores_changes_new_ignored_files_and_bookkeeping(self):
        (self.root/'ledger/model_capacity.jsonl').write_text('uncommitted allowed bookkeeping\n')
        gen=self.root/'build_ovl_gate/work';gen.mkdir(parents=True);(gen/'old.bin').write_bytes(b'old cache')
        new='changed\n';h=lambda s:hashlib.sha256(s.encode()).hexdigest()
        edit=self.script("from pathlib import Path\np=Path('src/demo/a.c');p.write_text('changed\\n')\n",'edit.py')
        self.plan['scripts']=[{'argv':['python3',str(edit)],'files':{'src/demo/a.c':{'before':h('original\n'),'after':h(new)}}}]
        fail=self.script("import argparse\nfrom pathlib import Path\np=argparse.ArgumentParser();p.add_argument('--root');p.add_argument('--dry-run',action='store_true');a=p.parse_args();r=Path(a.root)\n(r/'tools/new').mkdir();(r/'tools/new/untracked.py').write_text('new')\n(r/'tools/new/ignored.o').write_bytes(b'ignored')\nraise SystemExit(9)\n")
        self.plan['packages']=[{'entry':str(fail),'live_flag':True}]
        before=self.git('status','--porcelain=v1','-z');index=(self.root/'.git/index').read_bytes()
        self.assertEqual(self.invoke(),1)
        self.assertEqual((self.root/'src/demo/a.c').read_text(),'original\n')
        self.assertFalse((self.root/'tools/new').exists())
        self.assertEqual((gen/'old.bin').read_bytes(),b'old cache')
        self.assertEqual((self.root/'ledger/model_capacity.jsonl').read_text(),'uncommitted allowed bookkeeping\n')
        self.assertEqual(before,self.git('status','--porcelain=v1','-z'))
        self.assertEqual(index,(self.root/'.git/index').read_bytes())
        stop=json.loads(self.log.read_text().splitlines()[-1]);self.assertEqual(stop['step'],'STOP');self.assertIsInstance(stop['rollback'],dict)
    def test_dirty_ledger_fails_before_mutation(self):
        (self.root/'ledger/splits/dungeon.jsonl').write_text('dirty\n')
        self.assertEqual(self.invoke(),1)
        self.assertEqual((self.root/'ledger/splits/dungeon.jsonl').read_text(),'dirty\n')
        self.assertIn('dirty tree',self.log.read_text())
    def test_staged_bookkeeping_fails(self):
        (self.root/'ledger/model_capacity.jsonl').write_text('new\n');self.git('add','ledger/model_capacity.jsonl')
        self.assertEqual(self.invoke(),1)
    def test_symlink_escape_rejected(self):
        (self.root/'src/escape').symlink_to(self.base,target_is_directory=True)
        with self.assertRaises(G.Stop):G.safe(self.root,'src/escape/out')
        with self.assertRaises(G.Stop):G.safe(self.root,'../out')
    def test_wrong_output_hash_rolls_back(self):
        edit=self.script("from pathlib import Path\nPath('src/demo/a.c').write_text('wrong')\n",'edit.py')
        self.plan['scripts']=[{'argv':['python3',str(edit)],'files':{'src/demo/a.c':{'before':G.digest(self.root/'src/demo/a.c'),'after':'0'*64}}}]
        self.assertEqual(self.invoke(),1);self.assertEqual((self.root/'src/demo/a.c').read_text(),'original\n')
        self.assertIn('after SHA256 mismatch',self.log.read_text())
    def test_new_lines_only_and_pending_reviewers(self):
        land=G.Lander(self.root,{**self.plan,'reviewer':'orchestrator'},self.base,self.log,scratch=True)
        land.preflight()
        p=self.root/'ledger/splits/dungeon.jsonl';p.write_text(p.read_text()+'{"id":"new-a","reviewer":null}\n{"id":"new-b","reviewer":"pending"}\n{"id":"new-c","reviewer":"reviewed-before"}\n')
        y=self.root/'config/overlays/new.overlay.yaml';y.write_text('file_start: 123\nfile_end: 234\nvram_start: 2147483648\n')
        land.normalise_review();rows=G.records(p)
        self.assertIsNone(rows[0]['reviewer']);self.assertEqual([r['reviewer'] for r in rows[1:]],['orchestrator','orchestrator','reviewed-before'])
        self.assertIn('0x7B',y.read_text());self.assertEqual((self.root/'config/overlays/existing.overlay.yaml').read_text(),'file_start: 10\n')
    def test_discovers_every_certificate_and_preserves_existing_reviewer(self):
        p=self.root/'ledger/modules';p.mkdir()
        for key in ['first','new-future-certificate']:(p/('overlay_'+key+'.json')).write_text(json.dumps({'module':key,'reviewer':'existing-reviewer'}))
        land=G.Lander(self.root,self.plan,self.base,self.log,scratch=True)
        self.assertEqual(land.certificates(),{'first':'existing-reviewer','new-future-certificate':'existing-reviewer'})
    def test_restore_preexisting_untracked_and_symlink(self):
        q=self.root/'docs';q.mkdir();(q/'untracked').write_text('preserve')
        (q/'link').symlink_to('untracked');store=self.base/'store';store.mkdir()
        snap=G.Snapshot(self.root,store);snap.quarantine()
        (q/'untracked').write_text('changed');(q/'link').unlink();(q/'added').write_text('new')
        result=snap.restore();self.assertTrue(result['status_identical']);self.assertEqual((q/'untracked').read_text(),'preserve');self.assertEqual(os.readlink(q/'link'),'untracked');self.assertFalse((q/'added').exists())
    def test_child_timeout_kills_before_rollback(self):
        land=G.Lander(self.root,self.plan,self.base,self.log,scratch=True)
        with contextlib.redirect_stdout(io.StringIO()),self.assertRaises(subprocess.TimeoutExpired):
            land.run('timeout',['python3','-c','import time;time.sleep(10)'],timeout=0.05)
        self.assertIsNone(land.child)
    def test_live_package_requires_explicit_contract(self):
        land=G.Lander(self.root,{**self.plan,'packages':[{'entry':'apply.py'}]},self.base,self.log,live=True)
        with patch.object(G,'LIVE',self.root),patch.object(G,'busy_processes',return_value=[]),self.assertRaisesRegex(G.Stop,'explicit --live'):
            land.preflight()
    def test_commit_excludes_generated_mirror_and_existing_bookkeeping(self):
        (self.root/'ledger/model_capacity.jsonl').write_text('pending bookkeeping\n')
        land=G.Lander(self.root,{**self.plan,'reviewer':'orchestrator'},self.base,self.log,scratch=True)
        with patch.object(G,'busy_processes',return_value=[]),contextlib.redirect_stdout(io.StringIO()):land.preflight()
        (self.root/'src/demo/new.c').write_text('land this\n')
        mirror=self.root/'overlays/demo';mirror.mkdir(parents=True);(mirror/'mirror.json').write_text('{}')
        with contextlib.redirect_stdout(io.StringIO()):land.commit()
        self.assertEqual(self.git('show','HEAD:src/demo/new.c'),b'land this\n')
        self.assertEqual(self.git('ls-files','overlays'),b'')
        self.assertEqual(self.git('show','HEAD:ledger/model_capacity.jsonl'),b'initial bookkeeping\n')
        self.assertEqual((self.root/'ledger/model_capacity.jsonl').read_text(),'pending bookkeeping\n')
    def test_non_production_window_rejected_even_when_gate_config_is_set(self):
        row={'id':'demo/a','foff':4,'size':8,'gate_config':'config/overlays/existing.overlay.yaml'}
        text=json.dumps(row)+'\n'
        (self.root/'tools/registry.py').write_text('from pathlib import Path\nPath("ledger/rows.jsonl").write_text('+repr(text)+')\n')
        (self.root/'tools/gen_src_index.py').write_text('')
        graph=self.root/'tools/gate';graph.mkdir();(graph/'overlay_module_gate.py').write_text('')
        (self.root/'config/overlays/existing.overlay.yaml').write_text('standalone_build:\n  window:\n    file_start: 0\n    file_end: 8\n')
        self.git('add','.');self.git('commit','-qm','test fixture')
        land=G.Lander(self.root,self.plan,self.base,self.log,scratch=True)
        with patch.object(G,'busy_processes',return_value=[]),contextlib.redirect_stdout(io.StringIO()):
            land.preflight()
            with self.assertRaisesRegex(G.Stop,'outside production window'):land.regenerate()
    def test_slus_rows_are_assigned_to_the_forced_image_gate(self):
        row={'id':'slus/code','container':'slus','kind':'slus','foff':None,'size':4,'gate_config':'build.ninja'}
        text=json.dumps(row)+'\n'
        (self.root/'tools/registry.py').write_text('from pathlib import Path\nPath("ledger/rows.jsonl").write_text('+repr(text)+')\n')
        (self.root/'tools/gen_src_index.py').write_text('')
        graph=self.root/'tools/gate';graph.mkdir();(graph/'overlay_module_gate.py').write_text('')
        self.git('add','.');self.git('commit','-qm','test fixture')
        land=G.Lander(self.root,self.plan,self.base,self.log,scratch=True)
        with patch.object(G,'busy_processes',return_value=[]),contextlib.redirect_stdout(io.StringIO()):
            land.preflight();land.regenerate()
    def test_patch_cannot_write_an_undeclared_path(self):
        patchfile=self.base/'bad.patch';patchfile.write_text('--- a/src/demo/a.c\n+++ b/src/demo/a.c\n@@ -1 +1 @@\n-original\n+new\n')
        land=G.Lander(self.root,{**self.plan,'patches':[{'file':str(patchfile),'files':{'STATUS.md':{'before':G.digest(self.root/'STATUS.md'),'after':'0'*64}}}]},self.base,self.log,scratch=True)
        with self.assertRaisesRegex(G.Stop,'patch headers differ'):land.mutate()
    def test_pending_cannot_commit(self):
        land=G.Lander(self.root,self.plan,self.base,self.log,scratch=True)
        with self.assertRaisesRegex(G.Stop,'pending reviewer'):land.commit()

if __name__=='__main__':unittest.main()
