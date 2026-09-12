"""Regression checks for lost work, false-negative screening and publication failures."""
import json
import contextlib
import os
import select
import signal
import subprocess
import sys
import tempfile
import unittest
import time
from pathlib import Path
from unittest.mock import patch
from types import SimpleNamespace

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import pin_search as controller
import pin_search_engine as engine
from xform import screen
from xform.t15_shapes import fold_load_candidates
from xform.loop_test_increment import loop_test_increment_candidates
from build.gate_all import gate_current

PINNED = 'void f(int x) {\n    ASM_KEEP(x);\n}\n'
FREE = 'void f(int x) {\n}\n'

class SearchTests(unittest.TestCase):
    def test_fence_objective_is_componentwise_and_strict(self):
        self.assertTrue(engine.improves_fence('do { x++; } while (0);', 'x++;'))
        self.assertFalse(engine.improves_fence('x++;', 'x++;'))

    def test_loop_increment_rewrite_rejects_unsafe_forms(self):
        template = 'int f(void) {\n int i=0;\n int j=0;\n do {\n%s\n } while (i < 3);\n return i;\n}\n'
        safe = template % '  i++;\n  j++;'
        self.assertTrue(loop_test_increment_candidates(safe))
        cases = [template % body for body in (
            '  if (j)\n   i++;', '  if (j) {\n   i++;\n  }',
            '  continue;\n  i++;', '  i++;\n  j += i;',
            '  use(&i);\n  i++;', '  i++;\n  use(&j);',
            '  i++;\n  i += 1;', '  i++;\n  j += step;',
            '  again:\n  i++;')]
        cases += [safe.replace('int i=0;', ty+' i=0;') for ty in
                  ('volatile int', 'static int', 'opaque_integer', 'int *')]
        cases += [safe.replace('int j=0;', 'volatile int j=0;'),
                  safe.replace('while (i < 3)', 'while (i < i)')]
        for src in cases:
            with self.subTest(source=src):self.assertEqual(loop_test_increment_candidates(src), [])

    def test_loop_increment_rewrite_positive_source_preserving(self):
        src='int f(void) {\n int i=0;\n char *cursor;\n do {\n  *cursor = 0;\n  i++; /* counter */\n  cursor += 4;\n } while (i < 3);\n return i;\n}\n'
        got=loop_test_increment_candidates(src)
        self.assertEqual(len(got),1)
        self.assertIn('} while (++i < 3);',got[0][1])
        self.assertIn('/* counter */',got[0][1])
        self.assertIn('cursor += 4;',got[0][1])

    def test_fold_load_removes_declaration_before_substituting_read(self):
        source='int f(int *p) {\n    register int value;\n    value = *p;\n    return value + 1; /* value stays in this comment */\n}\n'
        candidates=fold_load_candidates(source)
        self.assertEqual(len(candidates),1)
        result=candidates[0][1]
        self.assertNotIn('register int',result)
        self.assertIn('return (*p) + 1;',result)
        self.assertIn('/* value stays in this comment */',result)
        subprocess.run(['gcc','-fsyntax-only','-x','c','-'],input=result,text=True,check=True,capture_output=True)

    def test_fold_load_refuses_reassigned_escaped_or_conditional_temporary(self):
        for body in ('    value = 1;\n    return value;\n',
                     '    return value++;\n','    return &value;\n',
                     '    return p->value;\n','    return g(value);\n',
                     '    return p ? value : 0;\n','    return p && value;\n',
                     '    value += 1;\n','    return value + value;\n',
                     '    g();\n    return value;\n'):
            source='int f(int *p) {\n    int value;\n    value = *p;\n'+body+'}\n'
            with self.subTest(body=body):self.assertEqual(fold_load_candidates(source),[])

    def test_changed_budget_and_recipe_change_run_key(self):
        m = dict(rows=[{"source_sha":"a","row":{"cfg":"2.7.2"}}], fingerprints={"recipe":"r","search":"s"},
                 options={"screens":10}, environment={}, modes=["targeted"])
        key = controller.run_key(m)
        m["options"]["screens"] = 20
        self.assertNotEqual(key, controller.run_key(m))
        key = controller.run_key(m); m["fingerprints"]["search"] = "new"
        self.assertNotEqual(key, controller.run_key(m))
        key = controller.run_key(m); m["rows"][0]["row"]["cfg"] = "2.8.1"
        self.assertNotEqual(key, controller.run_key(m))

    def test_legacy_and_transient_results_are_not_resume_hits(self):
        self.assertFalse(controller.reusable({"outcome":"noop"}, "new"))
        self.assertFalse(controller.reusable(dict(run_key="new",outcome="noop",stop_reason="reference-build-error"), "new"))
        self.assertTrue(controller.reusable(dict(run_key="new",outcome="noop",stop_reason="screen-budget"), "new"))

    def test_atomic_completion_survives_parent_not_receiving_result(self):
        with tempfile.TemporaryDirectory() as tmp:
            p=Path(tmp)/"result.json";controller.atomic_json(p,{"outcome":"candidate","candidate_sha":"123"})
            self.assertEqual(json.loads(p.read_text())["candidate_sha"], "123")
            self.assertEqual(len(list(Path(tmp).iterdir())),1)

    def test_timeout_is_retryable_not_negative_assembly(self):
        with patch.object(screen.subprocess,"run",side_effect=subprocess.TimeoutExpired("cc1",30)):
            with self.assertRaises(subprocess.TimeoutExpired): screen._run(["cc1"])

    def test_rank_keeps_exploration(self):
        c=[("other:a","a"),("host:a","b"),("unhost:a","c"),("narrow:a","d"),("other:b","e")]
        out=engine.ranked_menu(c,"allocation")
        self.assertEqual(set(out),set(c));self.assertEqual(out[0][0],"host:a")
        self.assertEqual(out[3][0],"other:a")

    def test_diversity_preserves_different_c_states(self):
        c=[(2,"a","erase+host:a"),(2,"b","erase+host:b"),(3,"c","erase+narrow:a")]
        self.assertEqual([x[1] for x in engine.diverse(c,2)],["a","c"])
        self.assertEqual(engine.diverse(c,0),[])

    def test_mechanisms(self):
        self.assertEqual(engine.mechanism(["move $2,$3"],["move $4,$3"]),"allocation")
        self.assertEqual(engine.mechanism(["sw $31,0($29)","move $2,$4"],["move $2,$4","sw $31,0($29)"]),"scheduling")

    def session(self, tmp, verify, **opts):
        return engine.Session({"id":"town/test","cfg":"2.7.2","c_path":"test.c","kind":"overlay"},
                              PINNED,"recipe",Path(tmp)/"cache.sqlite",dict(engine.DEFAULTS,**opts),verify)

    def test_nonzero_screen_candidate_can_be_exact(self):
        def asm(row,text):
            return ["sw $31,0($29)","move $2,$4"] if "ASM_KEEP" in text else ["move $2,$4","sw $31,0($29)"]
        with tempfile.TemporaryDirectory() as tmp, patch.object(engine,"compile_s",asm), \
                patch.object(engine.old,"groups",side_effect=lambda text,row: [(0,)] if "ASM_KEEP" in text else []),patch.object(engine.old.T15,"_menu",return_value=[]):
            s=self.session(tmp,lambda text:{"exact":True})
            text,info=s.run("targeted")
            self.assertNotIn("ASM_KEEP",text);self.assertEqual(info["fallback_wins"],1)

    def test_nonzero_candidate_still_needs_verifier(self):
        with tempfile.TemporaryDirectory() as tmp, patch.object(engine,"compile_s",lambda row,t:["a"] if "ASM_KEEP" in t else ["b"]), \
                patch.object(engine.old,"groups",side_effect=lambda text,row: [(0,)] if "ASM_KEEP" in text else []),patch.object(engine.old.T15,"_menu",return_value=[]):
            s=self.session(tmp,lambda text:{"exact":False})
            text,info=s.run("targeted");self.assertEqual(text,PINNED);self.assertGreater(info["fallback_tried"],0)

    def test_cache_reused_only_with_same_recipe_and_row(self):
        with tempfile.TemporaryDirectory() as tmp, patch.object(engine,"compile_s",return_value=["move $2,$4"]) as compile_mock:
            s=self.session(tmp,lambda t:{"exact":False});s.compile(s.row,PINNED);s.db.close()
            s=self.session(tmp,lambda t:{"exact":False});s.compile(s.row,PINNED)
            self.assertEqual(compile_mock.call_count,1)
            s.recipe="changed";s.compile(s.row,PINNED);s.db.close()
            self.assertEqual(compile_mock.call_count,2)

    def test_compiler_failure_is_not_persisted(self):
        with tempfile.TemporaryDirectory() as tmp, patch.object(engine,"compile_s",return_value=None) as compile_mock:
            s=self.session(tmp,lambda t:{"exact":False});s.compile(s.row,PINNED);s.compile(s.row,PINNED);s.db.close()
            self.assertEqual(compile_mock.call_count,2)

    def test_generated_timeout_preserves_win_and_is_not_cached(self):
        def compile_text(row,text):
            if text==PINNED:return ['ref']
            raise subprocess.TimeoutExpired(['cc1'],30)
        with tempfile.TemporaryDirectory() as tmp,patch.object(engine,'compile_s',side_effect=compile_text) as cc:
            s=self.session(tmp,lambda t:{'exact':True})
            s.verify(FREE)
            text,info=s.run('targeted')
            self.assertEqual(text,FREE)
            self.assertEqual(info['stop_reason'],'compiler-timeout')
            self.assertEqual(info['compile_timeouts'],1)
            self.assertFalse(s.timeout['reference'])
            self.assertEqual(s.timeout['source_sha'],controller.sha_text(s.timeout['text']))
            s=self.session(tmp,lambda t:{'exact':False})
            with self.assertRaises(engine.Limit):s.compile(s.row,FREE)
            s.db.close()
            self.assertEqual(cc.call_count,3)

    def test_reference_timeout_remains_retryable(self):
        with tempfile.TemporaryDirectory() as tmp,patch.object(engine,'compile_s',side_effect=subprocess.TimeoutExpired(['cc1'],30)):
            s=self.session(tmp,lambda t:{'exact':False})
            with self.assertRaises(subprocess.TimeoutExpired):s.run('targeted')
            self.assertTrue(s.timeout['reference'])

    def test_budget_stop_is_explicit(self):
        with tempfile.TemporaryDirectory() as tmp:
            s=self.session(tmp,lambda t:{"exact":False},screens=0)
            text,info=s.run("targeted");self.assertEqual(info["stop_reason"],"screen-budget")

    def test_cannot_trade_pin_for_fake_dependency_or_fence(self):
        self.assertFalse(engine.improves(PINNED,FREE+'x = (e) + a;\nx -= a;\n'))
        self.assertFalse(engine.improves(PINNED,FREE+'do { x++; } while (0);\n'))
        self.assertTrue(engine.improves(PINNED,FREE))

    def test_gate_failure_and_staleness_propagate(self):
        self.assertFalse(gate_current({"result":"NO MATCH","inputs_sha":"s"},"s"))
        self.assertFalse(gate_current({"result":"MATCH","inputs_sha":"old"},"s"))
        self.assertFalse(gate_current(None,"s"))
        self.assertTrue(gate_current({"result":"MATCH","inputs_sha":"s"},"s"))

    def test_rollback_restores_only_the_owned_transaction(self):
        with tempfile.TemporaryDirectory() as tmp:
            root=Path(tmp);(root/'a.c').write_text('candidate');(root/'backup.c').write_text('original')
            files=[dict(path='a.c',backup='backup.c',before_sha=controller.sha_text('original'),after_sha=controller.sha_text('candidate'))]
            controller.restore_publication(files,root,root)
            self.assertEqual((root/'a.c').read_text(),'original')
            (root/'a.c').write_text('user edit')
            with self.assertRaises(RuntimeError):controller.restore_publication(files,root,root)
            self.assertEqual((root/'a.c').read_text(),'user edit')

    def test_success_checkpoint_precedes_row_completion(self):
        with tempfile.TemporaryDirectory() as tmp:
            saved=[]
            s=self.session(tmp,lambda t:{'exact':True});s.on_win=saved.append
            self.assertTrue(s.verify(FREE)['exact']);self.assertEqual(saved,[FREE]);s.db.close()

    def test_row_identity_survives_other_rows_changing(self):
        item=dict(row={'id':'town/a','cfg':'2.7.2'},source_sha='source')
        m=dict(rows=[item],fingerprints={'recipe':'r','search':'s'},options={'screens':10},environment={},run_key='run1')
        key=controller.job_key(m,item,'baseline')
        m['rows'].append(dict(row={'id':'town/b'},source_sha='other'));m['run_key']='run2'
        self.assertEqual(key,controller.job_key(m,item,'baseline'))
        self.assertNotEqual(key,controller.job_key(m,item,'targeted'))
        m['options']['screens']=20
        self.assertNotEqual(key,controller.job_key(m,item,'baseline'))

    def test_worker_exits_when_its_controller_is_killed(self):
        # This kills only the small isolated parent created here, never a campaign process.
        code='''import os,sys,time
from pathlib import Path
sys.path.insert(0,sys.argv[1])
from pin_search import initialize_worker
parent=os.getpid();pid=os.fork()
if pid==0:
    initialize_worker(parent)
    Path(sys.argv[2]).write_text(str(os.getpid()))
    time.sleep(30)
else:
    while not Path(sys.argv[2]).exists():time.sleep(.01)
    print(pid,flush=True)
    time.sleep(30)
'''
        with tempfile.TemporaryDirectory() as tmp:
            parent=subprocess.Popen([sys.executable,'-c',code,str(Path(controller.__file__).parent),tmp+'/ready'],stdout=subprocess.PIPE,text=True)
            child=None
            try:
                ready,_,_=select.select([parent.stdout],[],[],3)
                self.assertTrue(ready,'isolated worker did not start')
                child=int(parent.stdout.readline());parent.kill();parent.wait(timeout=3)
                end=time.monotonic()+3
                while time.monotonic()<end:
                    stat=Path('/proc')/str(child)/'stat'
                    if not stat.exists() or stat.read_text().rsplit(') ',1)[1].split()[0]=='Z':break
                    time.sleep(.02)
                else:self.fail('orphan worker survived its controller')
            finally:
                if parent.poll() is None:parent.kill();parent.wait()
                parent.stdout.close()
                if child:
                    try:os.kill(child,signal.SIGTERM)
                    except ProcessLookupError:pass

    def test_publication_gate_failure_rolls_back_then_can_retry(self):
        with tempfile.TemporaryDirectory() as tmp,contextlib.ExitStack() as stack:
            root=Path(tmp);d=root/'run';d.mkdir();source=root/'src.c';source.write_text(PINNED)
            (d/'candidate.c').write_text(FREE)
            item=dict(row={'id':'town/test','c_path':'src.c'},source_sha=controller.sha_text(PINNED))
            failed=dict(row={'id':'town/failed'},source_sha='failed-source')
            m=dict(tag='case',rows=[item,failed],modes=['baseline'],run_key='r',options={},fingerprints={'recipe':'p','search':'s'})
            controller.atomic_json(controller.result_path(d,'baseline','town/failed'),
                dict(run_key='r',outcome='error',stop_reason='error',reason='timeout'))
            controller.atomic_json(controller.result_path(d,'baseline','town/test'),
                dict(run_key='r',outcome='candidate',stop_reason='complete',candidate='candidate.c',candidate_sha=controller.sha_text(FREE)))
            stack.enter_context(patch.object(controller,'ROOT',root))
            stack.enter_context(patch.object(controller,'safe_tag',return_value=d))
            stack.enter_context(patch.object(controller,'load_manifest',return_value=m))
            stack.enter_context(patch.object(controller,'clean_path',return_value=source))
            stack.enter_context(patch('pin_census.landing_refusal',return_value=None))
            stack.enter_context(patch('verify.verify',return_value={'exact':True}))
            run=stack.enter_context(patch.object(controller.subprocess,'run'))
            run.side_effect=subprocess.CalledProcessError(1,['gate'])
            args=SimpleNamespace(tag='case',mode='baseline',workers=1,defer=['town/failed'])
            with self.assertRaises(subprocess.CalledProcessError):controller.publish(args)
            self.assertEqual(source.read_text(),PINNED)
            self.assertEqual(json.loads((d/'publication.json').read_text())['phase'],'rolled-back')
            run.side_effect=None
            controller.publish(args)
            self.assertEqual(source.read_text(),FREE)
            self.assertEqual(json.loads((d/'publication.json').read_text())['phase'],'complete')
            self.assertTrue((root/'ledger/pin_runs/case.json').exists())
            proof=json.loads((root/'ledger/pin_runs/case.json').read_text())
            self.assertEqual(proof['deferred'][0]['id'],'town/failed')

    def test_reusing_timeout_stop_copies_validated_evidence(self):
        with tempfile.TemporaryDirectory() as tmp,patch.object(controller,'BASE',Path(tmp)):
            base=Path(tmp);origin=base/'old';target=base/'new';origin.mkdir();target.mkdir()
            item=dict(row={'id':'town/test'},source_sha='s')
            m=dict(run_key='new',fingerprints={},options={},environment={})
            key=controller.job_key(m,item,'baseline')
            record=dict(job_key=key,run_key='old',outcome='noop',stop_reason='compiler-timeout',
                        timeout=dict(source='timeouts/variant.c',source_sha=controller.sha_text(FREE)))
            controller.atomic_text(origin/'timeouts/variant.c',FREE)
            controller.atomic_json(base/'completed'/(key+'.json'),dict(directory='old',result=record))
            self.assertTrue(controller.reuse_completed(target,m,item,'baseline'))
            self.assertEqual((target/'timeouts/variant.c').read_text(),FREE)
            (origin/'timeouts/variant.c').write_text('changed')
            self.assertFalse(controller.reuse_completed(target,m,item,'baseline'))

    def test_publication_deferral_is_explicit_and_preserves_error(self):
        with tempfile.TemporaryDirectory() as tmp:
            d=Path(tmp)
            m=dict(run_key='r',modes=['baseline'],rows=[
                dict(row={'id':i},source_sha='s') for i in ('good','failed')])
            good=controller.result_path(d,'baseline','good')
            bad=controller.result_path(d,'baseline','failed')
            controller.atomic_json(good,dict(run_key='r',outcome='candidate',stop_reason='complete'))
            controller.atomic_json(bad,dict(run_key='r',outcome='error',stop_reason='error',reason='timeout'))
            original=bad.read_bytes()
            with self.assertRaises(RuntimeError):controller.publication_results(d,m,'baseline',[])
            accepted,deferred=controller.publication_results(d,m,'baseline',['failed'])
            self.assertEqual([x['row']['id'] for x,r in accepted],['good'])
            self.assertEqual(deferred[0]['id'],'failed')
            self.assertEqual(deferred[0]['reason'],'timeout')
            self.assertEqual(bad.read_bytes(),original)
            for ids in (['good','failed'],['failed','unknown']):
                with self.assertRaises(RuntimeError):controller.publication_results(d,m,'baseline',ids)
            controller.atomic_json(bad,dict(run_key='stale',outcome='error'))
            with self.assertRaises(RuntimeError):controller.publication_results(d,m,'baseline',['failed'])

    def test_publication_recipe_check_allows_only_search_changes(self):
        with tempfile.TemporaryDirectory() as tmp,patch.object(controller,'fingerprints') as fp:
            d=Path(tmp)
            m=dict(rows=[],fingerprints={'recipe':'r','search':'old'},options={},environment={},modes=['baseline'])
            m['run_key']=controller.run_key(m);controller.atomic_json(d/'manifest.json',m)
            fp.return_value={'recipe':'r','search':'new'}
            self.assertEqual(controller.load_manifest(d,check='recipe'),m)
            with self.assertRaises(RuntimeError):controller.load_manifest(d)
            fp.return_value={'recipe':'changed','search':'new'}
            with self.assertRaises(RuntimeError):controller.load_manifest(d,check='recipe')

if __name__=="__main__":unittest.main()
