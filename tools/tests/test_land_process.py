"""Early validation, test confinement, incremental gates, isolation and batches.

Small real git repositories exercise the actual transaction and subprocess
paths. Synthetic build scripts test orchestration, never claim retail proof.
"""
import contextlib
import importlib.util
import io
import json
import os
import shlex
from pathlib import Path
import subprocess
import unittest
from unittest.mock import patch

HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('process_fixture',HERE/'test_land_fast_front.py')
H=importlib.util.module_from_spec(spec);spec.loader.exec_module(H)
G,P=H.G,H.P

class ProcessTests(unittest.TestCase):
    setUp=H.FastFrontTests.setUp
    tearDown=H.FastFrontTests.tearDown
    git=H.FastFrontTests.git
    script=H.FastFrontTests.script
    invoke=H.FastFrontTests.invoke
    write_plan=H.FastFrontTests.write_plan
    screen=H.FastFrontTests.screen
    put=H.FastFrontTests.put
    land=H.FastFrontTests.land
    package=H.FastFrontTests.package

    def test_load_rejects_empty_unit_modules_before_a_package_runs(self):
        self.plan['unit_modules']=[]
        marker=self.base/'ran'
        entry=self.script('from pathlib import Path\nPath('+repr(str(marker))+').write_text("bad")')
        self.plan['packages']=[{'entry':str(entry)}]
        with self.assertRaisesRegex(G.Stop,'non-empty dotted'):G.load_plan(self.write_plan())
        self.assertFalse(marker.exists())

    def test_load_rejects_undotted_module(self):
        self.plan['unit_modules']=['test_x']
        with self.assertRaisesRegex(G.Stop,'invalid dotted'):G.load_plan(self.write_plan())

    def test_load_rejects_missing_entry(self):
        self.plan['packages']=[{'entry':'does-not-exist.py'}]
        with self.assertRaisesRegex(G.Stop,'entry missing'):G.load_plan(self.write_plan())

    def test_load_rejects_empty_review_keys(self):
        entry=self.script('pass','review_modules.py')
        self.plan['reviews']=[{'entry':str(entry),'keys':[]}]
        with self.assertRaisesRegex(G.Stop,'review keys'):G.load_plan(self.write_plan())

    def test_review_missing_roster_key_stops_before_review_command(self):
        self.screen()
        entry=self.script('raise RuntimeError("must not run")','review_modules.py')
        self.plan['reviews']=[{'entry':str(entry),'keys':['unknown']}]
        with self.assertRaisesRegex(G.Stop,'review keys missing'):G.load_plan(self.write_plan(),self.root)

    def test_review_dry_run_mismatch_fails_preflight(self):
        self.screen()
        entry=self.script('raise SystemExit("review shape mismatches")','review_modules.py')
        self.plan['reviews']=[{'entry':str(entry),'keys':['fixture_module']}]
        self.assertEqual(self.invoke(['--preflight']),1)
        self.assertIn('review-0-dry-run failed',self.log.read_text())
        self.assertNotIn('SLUS-bootstrap',self.log.read_text())

    def test_wrong_recorded_reviewer_fails_before_build(self):
        self.screen()
        self.plan['reviews']=[{'entry':str(self.script("import argparse,json\nfrom pathlib import Path\np=argparse.ArgumentParser();p.add_argument('--root');p.add_argument('--dry-run',action='store_true');p.add_argument('keys',nargs='+');a=p.parse_args()\nif not a.dry_run:\n q=Path(a.root)/'config/overlays/modules.json';d=json.loads(q.read_text());d['modules'][0]['review']={'reviewer':'wrong'};q.write_text(json.dumps(d))\n",'review.py')),'keys':['fixture_module']}]
        self.assertEqual(self.invoke(['--preflight']),1)
        self.assertIn('review-script reviewer mismatch',self.log.read_text())

    def test_sibling_import_works_for_dotted_and_discovery(self):
        self.screen()
        self.put('tools/tests/sibling.py','VALUE=42\n')
        self.put('tools/tests/test_fixture.py','import unittest\nfrom sibling import VALUE\nclass Sibling(unittest.TestCase):\n def test_value(self):self.assertEqual(VALUE,42)\n')
        self.git('add','.');self.git('commit','-qm','sibling fixture')
        self.assertEqual(self.invoke(['--preflight']),0)
        self.assertIn('unit-dotted',self.log.read_text())
        self.assertIn('unit-discover-test_fixture.py',self.log.read_text())

    def test_failing_unit_is_early_and_worktree_is_removed(self):
        self.screen()
        self.put('tools/tests/test_fixture.py','import unittest\nclass Failure(unittest.TestCase):\n def test_bad(self):self.fail("lane-test-failed")\n')
        self.git('add','.');self.git('commit','-qm','failure fixture')
        self.assertEqual(self.invoke(['--preflight']),1)
        self.assertNotIn('registry',self.log.read_text())
        self.assertFalse(list(self.base.glob('plan_preflight-*')))

    def test_canonical_open_refused_even_if_test_catches_error(self):
        self.screen()
        private=self.base/'canonical';private.mkdir();target=private/'source';target.write_text('original')
        body='import unittest\nfrom pathlib import Path\nclass Access(unittest.TestCase):\n def test_access(self):\n  try:Path('+repr(str(target))+').write_text("bad")\n  except PermissionError:pass\n'
        self.put('tools/tests/test_fixture.py',body)
        self.git('add','.');self.git('commit','-qm','access fixture')
        with patch.object(G,'LIVE',private):self.assertEqual(self.invoke(['--preflight']),1)
        self.assertEqual(target.read_text(),'original')
        self.assertIn('test touched canonical root',self.log.read_text())

    def test_canonical_subprocess_refused(self):
        self.screen()
        private=self.base/'canonical';private.mkdir()
        self.put('tools/tests/test_fixture.py','import unittest,subprocess\nclass Access(unittest.TestCase):\n def test_access(self):subprocess.run(["git","-C",'+repr(str(private))+',"status"])\n')
        self.git('add','.');self.git('commit','-qm','subprocess fixture')
        with patch.object(G,'LIVE',private):self.assertEqual(self.invoke(['--preflight']),1)
        guard=list(self.base.glob('land.guard/attempts.jsonl'))
        self.assertTrue(guard)
        self.assertIn('subprocess.Popen',guard[0].read_text())

    def test_new_installed_lane_tests_are_selected(self):
        self.screen();entry=self.package()
        f=entry.parent/'files.json';recs=json.loads(f.read_text())
        recs.append({'path':'tools/tests/test_lane_change.py','file':'unused','before':None,'after':'0'*64});f.write_text(json.dumps(recs))
        spec=P.package_tests([{'entry':str(entry)}],self.root)
        self.assertIn('test_lane_change.py',spec['discover_patterns'])

    def test_two_queue_guards_conflict_even_with_equal_hashes(self):
        self.screen();one=self.package();two=self.base/'second';two.mkdir()
        (two/'files.json').write_bytes((one.parent/'files.json').read_bytes());(two/'apply.py').write_text('pass')
        with self.assertRaisesRegex(P.G.Stop,'guard the same file: src/demo/a.c'):
            P.guard_collisions([{'entry':str(one)},{'entry':str(two/'apply.py')}])

    def test_protected_input_read_dependency_conflicts(self):
        self.screen();one=self.package();two=self.base/'second';two.mkdir()
        (two/'manifest.json').write_text(json.dumps({'protected_inputs':{'src/demo/a.c':'0'*64}}))
        with self.assertRaisesRegex(P.G.Stop,'guard the same file'):
            P.guard_collisions([{'entry':str(one)},{'entry':str(two/'apply.py')}])

    def test_rebase_during_screen_changes_bound_package_state(self):
        self.screen();entry=self.package();items=[{'entry':str(entry)}]
        before=P.package_state(items)
        (entry.parent/'a.c').write_text('new submission')
        self.assertNotEqual(P.package_state(items),before)

    def test_append_only_ledger_does_not_collide_without_full_guard(self):
        one=self.base/'one';two=self.base/'two';one.mkdir();two.mkdir()
        for path in (one,two):(path/'manifest.json').write_text(json.dumps({'records':['ledger/splits/dungeon.jsonl']}))
        self.assertEqual(P.guard_collisions([{'entry':str(one/'apply.py')},{'entry':str(two/'apply.py')}]),{})

    def test_raw_rowbase_unrelated_tool_use_incremental(self):
        self.assertEqual(G.full_gate_reasons({'raw/dungeon/a.c','config/overlays/dungeon.rowbase.jsonl','tools/lanes/land_packages.py'},self.plan),[])

    def test_gate_fingerprint_and_forced_plan_use_full(self):
        paths={'tools/gate/overlay_module_gate.py','tools/fidelity/aspsx_diff.py','tools/build/gate_all.py','tools/build/slus_rodata_trim.py','include/native.h'}
        self.assertEqual(set(G.full_gate_reasons(paths,self.plan)),paths)
        self.assertIn('plan gate_all=full',G.full_gate_reasons([],{**self.plan,'gate_all':'full'}))

    def test_isolated_snapshot_never_renames_or_removes_build_ovl(self):
        view=self.root/'build_ovl/work';view.mkdir(parents=True);input_=view/'scorer';input_.write_bytes(b'active')
        inode=input_.stat().st_ino
        store=self.base/'snapshot';store.mkdir()
        snap=G.Snapshot(self.root,store,isolated=True);snap.quarantine()
        self.assertEqual(input_.stat().st_ino,inode)
        (self.root/'src/demo/a.c').write_text('bad')
        snap.restore();self.assertEqual(input_.stat().st_ino,inode)

    def fake_proc(self,pid,cwd,args='codex exec task',fds=()):
        proc=self.base/'proc'/str(pid);proc.mkdir(parents=True)
        (proc/'stat').write_text(str(pid)+' (fake) S 1 0 0')
        (proc/'cwd').symlink_to(cwd,target_is_directory=True)
        argv=shlex.split(args) if isinstance(args,str) else args
        (proc/'cmdline').write_bytes(b'\0'.join(os.fsencode(a) for a in argv)+b'\0')
        (proc/'environ').write_bytes(b'')
        (proc/'fd').mkdir()
        for n,path in enumerate(fds):(proc/'fd'/str(n)).symlink_to(path)
        return proc

    def test_isolated_lane_needs_paths_not_receipt_and_avoids_active_view(self):
        lane=self.root/'work/native_lane/lane';scratch=lane/'b';scratch.mkdir(parents=True)
        proc=self.fake_proc(os.getpid(),lane)
        self.assertTrue(G.isolated_lane(proc,self.root,proc_root=self.base/'proc'))
        (lane/'isolation.json').write_text(json.dumps({'version':1,'pid':os.getpid(),'roots':['work/native_lane/lane/b']}))
        # Real proc scan finds self cwd outside this synthetic checkout; no child uses the checkout.
        self.assertTrue(G.isolated_lane(proc,self.root,proc_root=self.base/'proc'))
        (proc/'cmdline').write_bytes(b'codex\0exec\0'+os.fsencode(self.root/'build_ovl')+b'\0')
        self.assertFalse(G.isolated_lane(proc,self.root,proc_root=self.base/'proc'))

    def test_receipt_does_not_exempt_codex_launched_at_repo_root(self):
        lane=self.root/'work/native_lane/lane';(lane/'b').mkdir(parents=True)
        proc=self.fake_proc(424242,self.root,'codex exec -o work/native_lane/lane/last_message.txt')
        (lane/'isolation.json').write_text(json.dumps({'version':1,'pid':424242,'roots':['work/native_lane/lane/b']}))
        self.assertFalse(G.isolated_lane(proc,self.root,proc_root=self.base/'proc'))
        (lane/'isolation.json').write_text(json.dumps({'version':1,'pid':42,'roots':['work/native_lane/lane/b']}))
        self.assertFalse(G.isolated_lane(proc,self.root,proc_root=self.base/'proc'))

    def test_shared_scorer_fd_overrides_an_isolation_receipt(self):
        lane=self.root/'work/native_lane/lane';(lane/'b').mkdir(parents=True)
        proc=self.fake_proc(424242,lane,fds=[self.root/'build_ovl/work/result'])
        (lane/'isolation.json').write_text(json.dumps({'version':1,'pid':424242,'roots':['work/native_lane/lane/b']}))
        self.assertFalse(G.isolated_lane(proc,self.root,proc_root=self.base/'proc'))

    def test_busy_scan_skips_a_scoped_lane_and_its_private_gate(self):
        lane=self.root/'work/native_lane/lane';(lane/'b').mkdir(parents=True)
        parent=self.fake_proc(424242,lane,'codex exec -o last_message.txt')
        gate=lane/'b/tools/build/gate_all.py';gate.parent.mkdir(parents=True);gate.write_text('pass\n')
        child=self.fake_proc(424243,lane/'b','python3 tools/build/gate_all.py')
        (child/'stat').write_text('424243 (fake) S 424242 0 0')
        (lane/'isolation.json').write_text(json.dumps({'version':1,'pid':424242,'roots':['work/native_lane/lane/b']}))
        self.assertEqual(G.busy_processes(self.root,False,True,self.base/'proc'),[])
        (child/'fd/3').symlink_to(self.root/'build_ovl/work/scorer')
        self.assertEqual({r['pid'] for r in G.busy_processes(self.root,False,True,self.base/'proc')},{424242,424243})

    def test_lane_pid_and_brief_cannot_exempt_a_canonical_cwd(self):
        lane=self.root/'work/native_lane/lane';lane.mkdir(parents=True)
        proc=self.fake_proc(424242,self.root,'codex exec -o work/native_lane/lane/last_message.txt')
        (lane/'lane.pid').write_text('424242\n')
        (lane/'BRIEF.md').write_text('work ONLY there. Prove everything in a lane-owned scratch tree.')
        self.assertFalse(G.isolated_lane(proc,self.root,proc_root=self.base/'proc'))
        (lane/'lane.pid').write_text('41\n')
        self.assertFalse(G.isolated_lane(proc,self.root,proc_root=self.base/'proc'))

    def test_brief_without_private_proof_contract_stays_busy(self):
        lane=self.root/'work/native_lane/lane';lane.mkdir(parents=True)
        proc=self.fake_proc(424242,self.root,'codex exec -o work/native_lane/lane/last_message.txt')
        (lane/'lane.pid').write_text('424242\n');(lane/'BRIEF.md').write_text('work ONLY there')
        self.assertFalse(G.isolated_lane(proc,self.root,proc_root=self.base/'proc'))

    def test_batch_spec_rejects_missing_inputs_at_load(self):
        self.plan['coherence']=[{'tag':'round','lane':'missing'}]
        with self.assertRaisesRegex(G.Stop,'coherence requires'):G.load_plan(self.write_plan())
        self.plan.pop('coherence');self.plan['promotions']=[{'id':'demo/a','body':'missing','before':'0'*64}]
        with self.assertRaisesRegex(G.Stop,'promotion body missing'):G.load_plan(self.write_plan())

    def test_batch_and_packages_rollback_in_one_snapshot(self):
        self.screen();entry=self.package()
        self.plan['packages']=[{'entry':str(entry),'live_flag':True}]
        self.plan['promotions']=[{'id':'demo/a','body':str(entry.parent/'a.c'),'before':'0'*64}]
        self.put('tools/lanes/batch_inputs.py','from pathlib import Path\nPath("src/demo/a.c").write_text("partial batch")\nraise SystemExit("batch mismatch")\n')
        self.git('add','.');self.git('commit','-qm','batch failure fixture')
        before=self.git('status','--porcelain=v1','-z')
        self.assertEqual(self.invoke(),1)
        self.assertEqual((self.root/'src/demo/a.c').read_text(),'original\n')
        self.assertEqual(self.git('status','--porcelain=v1','-z'),before)
        self.assertIn('batch-inputs failed',self.log.read_text())

    def test_certification_uses_each_recorded_reviewer(self):
        certs=self.root/'ledger/modules';certs.mkdir()
        for key,reviewer in [('one','first'),('two','second')]:
            (certs/('overlay_'+key+'.json')).write_text(json.dumps({'module':key,'reviewer':reviewer}))
        self.git('add','.');self.git('commit','-qm','certificate fixture')
        land=self.land();land.before_certs=land.certificates();land.force_all=False;land.gate_reasons=[];land.before_l5=0
        land.env['TMPDIR']=str(self.base)
        calls=[]
        def run(step,argv,**kwargs):
            calls.append((step,argv));log=self.base/(step+'.log')
            log.write_text('SLUS SHA-1 gate: MATCH\nrecipe identical to the pinned copy\nMATCH\n');return log,0.01
        with patch.object(land,'run',side_effect=run),patch.object(land,'regenerate'),patch.object(land,'scrub'),contextlib.redirect_stdout(io.StringIO()):land.validate()
        cert_calls=[argv for step,argv in calls if step.startswith('certify-')]
        self.assertEqual(len(cert_calls),1)
        self.assertIn('tools/lanes/certify_batch.py',cert_calls[0])
        self.assertEqual(land.certificates(),{'one':'first','two':'second'})
        self.assertIn('--gate-receipts',cert_calls[0])
        self.assertEqual(sum(step=='gate-all' for step,_ in calls),1)
        self.assertNotIn('--all',next(argv for step,argv in calls if step=='gate-all'))

if __name__=='__main__':unittest.main()
