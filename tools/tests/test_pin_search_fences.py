"""Fence-mode durability and publication contracts, independent of compiler availability."""
import contextlib
import json
import sys
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import pin_search as controller
import pin_search_engine as engine
from xform import t20_fencefree as t20

BEFORE = 'void f(void) {\n    do { x++; } while (0);\n    do { y++; } while (0);\n}\n'
AFTER = BEFORE.replace('do { x++; } while (0);', 'x++;')
ROW = dict(id='town/test', c_path='src.c', kind='overlay', cfg='2.7.2', stock=True, exists=True, container='town')

class FenceTests(unittest.TestCase):
    def session(self, tmp, verify, **options):
        return engine.Session(ROW, BEFORE, 'recipe', Path(tmp)/'cache.sqlite',
                              dict(engine.DEFAULTS, objective='fences', **options), verify)

    def test_policy_does_not_trade_debt_and_old_default_stays_strict(self):
        self.assertTrue(engine.improvement_policy({'objective':'fences'})(BEFORE, AFTER))
        self.assertFalse(engine.improvement_policy({})(BEFORE, AFTER))
        self.assertFalse(engine.improves_fence(BEFORE, AFTER+'ASM_KEEP(x);\n'))
        self.assertFalse(engine.improves_fence(BEFORE, AFTER+'x = (e) + a;\nx -= a;\n'))
        self.assertFalse(engine.improves_fence(BEFORE, BEFORE))
        m=dict(rows=[], fingerprints={}, environment={}, modes=['fences'], options={'objective':'pins'})
        key=controller.run_key(m);m['options']['objective']='fences'
        self.assertNotEqual(key, controller.run_key(m))

    def test_real_t20_stops_at_verify_budget_and_counts_partial_fence_win(self):
        with tempfile.TemporaryDirectory() as tmp, patch.object(t20.T, '_menu', return_value=[]):
            saved=[];s=self.session(tmp, lambda text: {'exact':True}, verifies=1);s.on_win=saved.append
            text,info=s.run('fences')
            self.assertEqual(len(saved),1)
            self.assertEqual(info['fences_in']-info['fences_out'],1)
            self.assertEqual(info['pins_in'],0)
            self.assertEqual(info['tried'],1)
            self.assertEqual(info['stop_reason'],'verify-budget')
            self.assertTrue(engine.improves_fence(BEFORE,text))

    def test_limit_keeps_verified_checkpoint_and_restores_t20_globals(self):
        previous={k:getattr(t20,k) for k in ('BUDGET','FENCE_BUDGET','ROUNDS','NEAR','PIN_PASS')}
        menu=t20.T._menu
        def search(text,row,census,vf):
            self.assertTrue(vf(AFTER)['exact'])
            raise engine.Limit('cpu-budget')
        with tempfile.TemporaryDirectory() as tmp, patch.object(t20.T,'apply_verified',side_effect=search):
            saved=[];s=self.session(tmp,lambda text:{'exact':True});s.on_win=saved.append
            text,info=s.run('fences')
            self.assertEqual(text,AFTER);self.assertEqual(saved,[AFTER])
            self.assertEqual(info['stop_reason'],'cpu-budget')
            self.assertEqual(info['fences_out'],1)
        self.assertEqual(previous,{k:getattr(t20,k) for k in previous})
        self.assertIs(t20.T._menu,menu)

    def test_worker_reverifies_and_retains_fence_only_recovered_checkpoint(self):
        with tempfile.TemporaryDirectory() as tmp, contextlib.ExitStack() as stack:
            root=Path(tmp);d=root/'run';d.mkdir();(d/'input.c').write_text(BEFORE);(d/'saved.c').write_text(AFTER)
            item=dict(row=ROW,source_sha=controller.sha_text(BEFORE),input='input.c')
            m=dict(run_key='r',options=dict(engine.DEFAULTS,objective='fences'),environment={},fingerprints={'recipe':'r'},rows=[item])
            controller.atomic_json(d/'progress/fences/town_test.json',dict(run_key='r',candidate='saved.c',candidate_sha=controller.sha_text(AFTER)))
            stack.enter_context(patch.object(controller,'BASE',root))
            stack.enter_context(patch.object(controller,'configure'))
            stack.enter_context(patch('verify.verify',return_value={'exact':True}))
            stack.enter_context(patch('pin_census.landing_refusal',return_value=None))
            def resume(session):
                self.assertEqual(session.best,AFTER)
                raise engine.Limit('cpu-budget')
            stack.enter_context(patch.object(engine.Session,'fences',resume))
            result=controller.worker((str(d),m,item,'fences'))
            self.assertEqual(result['outcome'],'candidate')
            self.assertEqual(result['fences_in']-result['fences_out'],1)
            self.assertEqual((d/result['candidate']).read_text(),AFTER)
            with patch('builtins.print'):
                controller.summarize(d,dict(m,tag='run',modes=['fences']))
            self.assertEqual(json.loads((d/'summary.json').read_text())['modes']['fences']['fences_removed'],1)

    def test_prepare_selects_scored_fences_without_pins(self):
        with tempfile.TemporaryDirectory() as tmp,contextlib.ExitStack() as stack:
            root=Path(tmp);source=root/'src.c';source.write_text(BEFORE)
            stack.enter_context(patch.object(controller,'safe_tag',return_value=root/'run'))
            stack.enter_context(patch.object(controller,'rows',return_value=[ROW]))
            stack.enter_context(patch.object(controller,'clean_path',return_value=source))
            stack.enter_context(patch.object(controller,'fingerprints',return_value={}))
            args=SimpleNamespace(tag='run',mode='fences',pilot=False,ids=None,sample=0,seed=1,screens=10,verifies=2,cpu_seconds=1)
            with patch('builtins.print'):controller.prepare(args)
            m=json.loads((root/'run/manifest.json').read_text())
            self.assertEqual(len(m['rows']),1);self.assertEqual(m['options']['objective'],'fences')
            source.write_text('#if 0\n'+BEFORE+'#endif\n')
            args.tag='dead'
            with patch.object(controller,'safe_tag',return_value=root/'dead'),patch('builtins.print'):controller.prepare(args)
            self.assertEqual(json.loads((root/'dead/manifest.json').read_text())['rows'],[])

    def test_publication_uses_same_fence_objective(self):
        with tempfile.TemporaryDirectory() as tmp,contextlib.ExitStack() as stack:
            root=Path(tmp);d=root/'run';d.mkdir();source=root/'src.c';source.write_text(BEFORE);(d/'candidate.c').write_text(AFTER)
            item=dict(row=ROW,source_sha=controller.sha_text(BEFORE))
            m=dict(tag='case',rows=[item],modes=['fences'],run_key='r',options={'objective':'fences'},fingerprints={'recipe':'p','search':'s'})
            controller.atomic_json(controller.result_path(d,'fences',ROW['id']),dict(run_key='r',outcome='candidate',stop_reason='complete',candidate='candidate.c',candidate_sha=controller.sha_text(AFTER)))
            for name,value in [('ROOT',root),('safe_tag',lambda tag:d),('load_manifest',lambda *a,**kw:m),('clean_path',lambda row:source)]:
                stack.enter_context(patch.object(controller,name,value))
            stack.enter_context(patch('pin_census.landing_refusal',return_value=None))
            stack.enter_context(patch('verify.verify',return_value={'exact':True}))
            stack.enter_context(patch.object(controller.subprocess,'run'))
            with patch('builtins.print'):controller.publish(SimpleNamespace(tag='case',mode='fences',workers=1,defer=[]))
            self.assertEqual(source.read_text(),AFTER)
            self.assertEqual(json.loads((d/'publication.json').read_text())['phase'],'complete')

if __name__=='__main__':unittest.main()
