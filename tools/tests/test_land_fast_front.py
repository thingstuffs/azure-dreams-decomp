"""Small git fixtures for early screens; fixture tools do not prove retail bytes."""
import contextlib
import importlib.util
import io
import json
import os
from pathlib import Path
import shutil
import unittest
from unittest.mock import patch

HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('land_fixture_helpers',HERE/'test_land_packages.py')
H=importlib.util.module_from_spec(spec);spec.loader.exec_module(H)
G=H.G
spec=importlib.util.spec_from_file_location('package_preflight_fixture',HERE.parent/'lanes/package_preflight.py')
P=importlib.util.module_from_spec(spec);spec.loader.exec_module(P)

class FastFrontTests(unittest.TestCase):
    setUp=H.LandPackagesTests.setUp
    tearDown=H.LandPackagesTests.tearDown
    git=H.LandPackagesTests.git
    script=H.LandPackagesTests.script
    invoke=H.LandPackagesTests.invoke
    write_plan=H.LandPackagesTests.write_plan

    def screen(self, bad=False, status='clean\n'):
        row={'id':'dungeon/member','kind':'overlay','container':'dungeon','foff':0,'size':4,'gate_config':'config/overlays/existing.overlay.yaml'}
        self.put('ledger/rows.jsonl',json.dumps(row)+'\n')
        self.put('ledger/modules.jsonl','{"id":"dungeon/member","module":"fixture","confidence":"weak"}\n')
        self.put('ledger/levels.jsonl','{"id":"dungeon/member","level":3,"pins_left":0,"tail_jumps":0,"l4_residue":["not_in_module"]}\n')
        self.put('config/overlays/modules.json',json.dumps({'modules':[{'key':'fixture_module','membership_evidence':'docs/member.json','members':[{'id':'dungeon/member','foff':0,'size':4}]}]}))
        self.put('docs/member.json',json.dumps({'ledger_group':{'module':'fixture'},'members':['dungeon/member']}))
        self.put('config/overlays/existing.overlay.yaml','standalone_build:\n  window:\n    file_start: 0\n    file_end: 4\n')
        self.put('tools/registry.py','')
        self.put('tools/gen_src_index.py','')
        self.put('tools/lanes/land_packages.py','')
        self.put('tools/levels.py',"import json\nfrom pathlib import Path\np=Path('ledger/levels.jsonl');r=json.loads(p.read_text());r['level']="+('2' if bad else '3')+";p.write_text(json.dumps(r)+'\\n')\n")
        self.put('tools/gate/overlay_module_gate.py',"import json\nfrom pathlib import Path\nr=json.loads(Path('ledger/levels.jsonl').read_text())\nraise SystemExit(1 if r['level']<3 else 0)\n")
        self.put('tools/status.py',"from pathlib import Path\nPath('STATUS.md').write_text("+repr(status)+")\n")
        self.git('add','.');self.git('commit','-qm','screen fixtures')

    def put(self,rel,text):
        p=self.root/rel;p.parent.mkdir(parents=True,exist_ok=True);p.write_text(text)

    def land(self):
        land=G.Lander(self.root,self.plan,self.base,self.log,scratch=True)
        with patch.object(G,'busy_processes',return_value=[]),contextlib.redirect_stdout(io.StringIO()):land.preflight()
        return land

    def package(self, body='', live=True, refusal=True):
        base=self.base/'delivery';base.mkdir(exist_ok=True)
        source=base/'a.c';source.write_text('changed\n')
        (base/'files.json').write_text(json.dumps([{'file':'a.c','path':'src/demo/a.c','before':G.digest(self.root/'src/demo/a.c'),'after':G.digest(source)}]))
        (base/'package.sha256.json').write_text(json.dumps({'files.json':G.digest(base/'files.json')}))
        entry=base/'apply.py'
        entry.write_text("import argparse,os\nfrom pathlib import Path\na=argparse.ArgumentParser();a.add_argument('--root',required=True);a.add_argument('--dry-run',action='store_true');"+("a.add_argument('--live',action='store_true');" if live else '')+"v=a.parse_args();r=Path(v.root)\n"+("if not v.live and str(r)==os.environ.get('LAND_LIVE_ROOT'):raise SystemExit('Refusing canonical root without --live')\n" if refusal and live else '')+"if v.dry_run:raise SystemExit(0)\n"+"(r/'src/demo/a.c').write_text('changed\\n')\n"+body)
        return entry

    def test_combined_screen_stops_before_any_build_and_names_member(self):
        self.screen(bad=True)
        self.assertEqual(self.invoke(),1)
        events=[json.loads(s) for s in self.log.read_text().splitlines()]
        self.assertEqual([e['step'] for e in events if 'command' in e],['registry','index','graph','fast-levels','fast-graph'])
        self.assertIn('fixture_module member=dungeon/member L3/placement screen failed',events[-1]['error'])
        self.assertIsInstance(events[-1]['rollback'],dict)
        self.assertEqual(json.loads((self.root/'ledger/levels.jsonl').read_text())['level'],3)

    def test_status_home_path_fails_before_build(self):
        self.screen(status='bad '+('/'+'home/private')+'\n')
        self.assertEqual(self.invoke(),1)
        self.assertIn('scrub hook patterns',self.log.read_text())
        self.assertNotIn('SLUS-bootstrap',self.log.read_text())
        self.assertEqual((self.root/'STATUS.md').read_text(),'before\n')

    def test_scrub_hook_all_patterns_changed_and_new_candidates(self):
        self.screen();land=self.land()
        for pattern in G.SCRUB_PATTERNS:
            self.put('docs/new.md',pattern)
            with contextlib.redirect_stdout(io.StringIO()),self.assertRaisesRegex((G.Stop,P.G.Stop),'scrub hook'):land.scrub()
        self.put('docs/new.md','clean');self.put('src/demo/a.c',G.SCRUB_PATTERNS[0]);self.put('raw/test.bin',G.SCRUB_PATTERNS[1])
        with contextlib.redirect_stdout(io.StringIO()):land.scrub()

    def test_preflight_success_keeps_source_and_removes_worktree(self):
        self.screen();entry=self.package()
        self.plan['packages']=[{'entry':str(entry),'live_flag':True}]
        before=self.git('status','--porcelain=v1','-z');index=(self.root/'.git/index').read_bytes();head=self.git('rev-parse','HEAD')
        self.assertEqual(self.invoke(['--preflight']),0)
        self.assertEqual(before,self.git('status','--porcelain=v1','-z'));self.assertEqual(index,(self.root/'.git/index').read_bytes());self.assertEqual(head,self.git('rev-parse','HEAD'))
        self.assertEqual((self.root/'src/demo/a.c').read_text(),'original\n')
        self.assertFalse(list(self.base.glob('plan_preflight-*')))
        self.assertIn('PREFLIGHT_PASS',self.log.read_text());self.assertNotIn('SLUS-bootstrap',self.log.read_text())

    def test_preflight_failure_keeps_source_and_cleans(self):
        self.screen(bad=True)
        before=self.git('status','--porcelain=v1','-z');index=(self.root/'.git/index').read_bytes()
        self.assertEqual(self.invoke(['--preflight']),1)
        self.assertEqual(before,self.git('status','--porcelain=v1','-z'));self.assertEqual(index,(self.root/'.git/index').read_bytes())
        self.assertFalse(list(self.base.glob('plan_preflight-*')))

    def test_live_source_allowed_for_preflight_without_live_flag(self):
        self.screen()
        with patch.object(G,'LIVE',self.root):self.assertEqual(self.invoke(['--preflight']),0)

    def test_live_refusal_and_live_acceptance_contract(self):
        self.screen();entry=self.package();land=self.land()
        with contextlib.redirect_stdout(io.StringIO()):P.lint_contract(land,entry,[])
        self.assertIn('contract-refusal',self.log.read_text())
        self.assertEqual((self.root/'src/demo/a.c').read_text(),'original\n')

    def test_missing_live_flag_fails_contract(self):
        self.screen();entry=self.package(live=False);land=self.land()
        with contextlib.redirect_stdout(io.StringIO()),self.assertRaisesRegex((G.Stop,P.G.Stop),'missing contract flag'):P.lint_contract(land,entry,[])

    def test_refusal_that_also_rejects_live_is_not_pass(self):
        self.screen();entry=self.package();entry.write_text(entry.read_text().replace('if not v.live and str(r)==', 'if str(r)=='))
        land=self.land()
        with contextlib.redirect_stdout(io.StringIO()),self.assertRaisesRegex((G.Stop,P.G.Stop),'contract-live-dry-run failed'):P.lint_contract(land,entry,[])

    def test_missing_live_refusal_is_not_pass(self):
        self.screen();entry=self.package(refusal=False);land=self.land()
        with contextlib.redirect_stdout(io.StringIO()),self.assertRaisesRegex((G.Stop,P.G.Stop),'refusal without --live'):P.lint_contract(land,entry,[])

    def test_live_dry_run_mutation_is_not_pass(self):
        self.screen();entry=self.package();entry.write_text(entry.read_text().replace('if v.dry_run:raise SystemExit(0)',"if v.live:(r/'src/demo/a.c').write_text('bad dry run')\nif v.dry_run:raise SystemExit(0)"))
        land=self.land()
        with contextlib.redirect_stdout(io.StringIO()),self.assertRaisesRegex((G.Stop,P.G.Stop),'dry-run mutated'):P.lint_contract(land,entry,[])

    def test_flattened_path_rejected(self):
        self.screen();entry=self.package(body="# tools/overlay_module_gate.py\n")
        with self.assertRaisesRegex((G.Stop,P.G.Stop),'scratch-flattened'):P.lint_inventory(entry,self.root)

    def test_home_path_rejected_in_package(self):
        self.screen();entry=self.package(body='# '+('/'+'home/private')+'\n')
        with self.assertRaisesRegex((G.Stop,P.G.Stop),'home-directory'):P.lint_inventory(entry,self.root)

    def test_rebased_files_stale_outer_inventory_rejected(self):
        self.screen();entry=self.package();files=entry.parent/'files.json';files.write_text(files.read_text()+'\n')
        with self.assertRaisesRegex((G.Stop,P.G.Stop),'stale package.sha256.json: files.json'):P.lint_inventory(entry,self.root)

    def test_promotion_guard_collision_rejected(self):
        self.screen();entry=self.package();self.put('src/demo/a.c','later promotion\n')
        with self.assertRaisesRegex((G.Stop,P.G.Stop),'guard != HEAD: src/demo/a.c'):P.lint_inventory(entry,self.root)

    def test_review_edit_changes_existing_certificate_bound_input(self):
        self.screen();path=self.root/'config/overlays/modules.json';before=G.digest(path)
        doc=json.loads(path.read_text());doc['modules'][0]['review']={'reviewer':'pending'};path.write_text(json.dumps(doc))
        self.assertNotEqual(before,G.digest(path))
        # Real per-certificate fanout is measured by tools/measure.py in this lane.

    def test_confidence_in_membership_identity_names_missing_member(self):
        self.screen();land=self.land();self.put('docs/member.json',json.dumps({'ledger_group':{'module':'fixture','confidence':'weak'}}))
        self.put('ledger/modules.jsonl','{"id":"dungeon/member","module":"fixture","confidence":"strong"}\n')
        self.assertIn('fixture_module cohort members=dungeon/member',land.graph_diagnostics())

    def test_pending_queue_combined_failure_is_early(self):
        self.screen()
        # Only candidate + pending together lower the computed level.
        self.put('tools/levels.py',"import json\nfrom pathlib import Path\np=Path('ledger/levels.jsonl');r=json.loads(p.read_text());r['level']=2 if Path('docs/pending').exists() and Path('src/demo/a.c').read_text()=='changed\\n' else 3;p.write_text(json.dumps(r)+'\\n')\n")
        self.git('add','.');self.git('commit','-qm','combined fixture')
        entry=self.package()
        pending=self.root/'work/pending/apply.py';pending.parent.mkdir(parents=True)
        pending.write_text("import argparse\nfrom pathlib import Path\np=argparse.ArgumentParser();p.add_argument('--root');p.add_argument('--dry-run',action='store_true');p.add_argument('--live',action='store_true');a=p.parse_args()\nif not a.dry_run:(Path(a.root)/'docs/pending').write_text('pending')\n")
        queue=self.base/'queue.json';queue.write_text(json.dumps({'version':1,'packages':[{'entry':'work/pending/apply.py','live_flag':True}]}))
        before=self.git('status','--porcelain=v1','-z');index=(self.root/'.git/index').read_bytes()
        with patch.object(P.G,'busy_processes',return_value=[]),contextlib.redirect_stdout(io.StringIO()):
            rc=P.preflight(self.root,entry,[],queue,self.log)
        self.assertEqual(rc,1)
        self.assertIn('fixture_module member=dungeon/member',self.log.read_text())
        self.assertNotIn('SLUS-bootstrap',self.log.read_text());self.assertFalse(list(self.base.glob('package_preflight-*')))
        self.assertEqual(before,self.git('status','--porcelain=v1','-z'));self.assertEqual(index,(self.root/'.git/index').read_bytes())

    def test_pending_queue_rejects_missing_explicit_queue(self):
        self.screen()
        with self.assertRaisesRegex((G.Stop,P.G.Stop),'missing pending queue'):P.pending_packages(self.root,self.base/'missing.json')

if __name__=='__main__':unittest.main()
