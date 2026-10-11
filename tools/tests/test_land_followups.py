"""Admission, concurrent bookkeeping and dependency-order regression tests."""
import contextlib
import importlib.util
import io
import json
from pathlib import Path
import unittest
from unittest.mock import patch

HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('followup_fixtures',HERE/'test_land_fast_front.py')
H=importlib.util.module_from_spec(spec);spec.loader.exec_module(H);G=H.G;P=H.P

class FollowupTests(unittest.TestCase):
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

    def test_preflight_reports_all_live_source_dirt_before_clone(self):
        self.screen();self.put('agent-result.c','agent output');self.put('ledger/agents/out/result.c','agent output')
        before=self.git('status','--porcelain=v1','-z')
        self.assertEqual(self.invoke(['--preflight']),1)
        event=json.loads(self.log.read_text().splitlines()[0])
        self.assertEqual(event['step'],'source-tree-dirt')
        self.assertIn('?? agent-result.c',event['refused'])
        self.assertTrue(any('ledger/agents/' in s for s in event['refused']))
        self.assertEqual(self.git('status','--porcelain=v1','-z'),before)
        self.assertFalse(list(self.base.glob('plan_preflight-*')))

    def test_declared_unstaged_bookkeeping_is_admitted_in_both_screens(self):
        self.screen();self.put('ledger/model_capacity.jsonl','initial bookkeeping\nappended\n')
        self.assertEqual(G.tree_dirt(self.root,self.plan)['refused'],[])
        self.assertEqual(self.invoke(['--preflight']),0)

    def test_append_growth_passes_fast_front_and_is_excluded_from_commit(self):
        self.screen();self.plan['reviewer']='fixture-reviewer';land=self.land();p=self.root/'ledger/model_capacity.jsonl'
        p.write_bytes(p.read_bytes()+b'pool append\n');G.check_bookkeeping(self.root,land.bookkeeping)
        self.put('src/demo/a.c','changed\n')
        with contextlib.redirect_stdout(io.StringIO()):land.commit()
        self.assertEqual(self.git('show','HEAD:ledger/model_capacity.jsonl'),b'initial bookkeeping\n')
        self.assertTrue(p.read_bytes().endswith(b'pool append\n'))

    def test_rewrite_truncation_and_removal_are_refused(self):
        self.screen();land=self.land();p=self.root/'ledger/model_capacity.jsonl'
        for data in (b'replaced\n',b'initial'):
            p.write_bytes(data)
            with self.assertRaisesRegex(G.Stop,'not a prefix'):G.check_bookkeeping(self.root,land.bookkeeping)
        p.unlink()
        with self.assertRaisesRegex(G.Stop,'removed'):G.check_bookkeeping(self.root,land.bookkeeping)

    def test_rollback_preserves_concurrent_bookkeeping_append(self):
        self.screen();land=self.land();store=self.base/'snapshot';store.mkdir()
        snap=G.Snapshot(self.root,store,bookkeeping=land.bookkeeping)
        p=self.root/'ledger/model_capacity.jsonl';p.write_bytes(p.read_bytes()+b'pool append\n')
        self.put('src/demo/a.c','changed\n')
        result=snap.restore()
        self.assertEqual((self.root/'src/demo/a.c').read_text(),'original\n')
        self.assertEqual(p.read_bytes(),b'initial bookkeeping\npool append\n')
        self.assertEqual(result['bookkeeping_appends_preserved'],['ledger/model_capacity.jsonl'])
        self.assertTrue(result['index_identical'])

    def test_bookkeeping_alias_is_refused(self):
        self.screen();p=self.root/'ledger/model_capacity.jsonl';p.unlink();p.symlink_to(self.root/'src/demo/a.c')
        with self.assertRaisesRegex(G.Stop,'symlink'):G.bookkeeping_paths(self.plan,self.root)

    def test_empty_existing_bookkeeping_may_grow_but_may_not_disappear(self):
        self.screen();p=self.root/'ledger/model_capacity.jsonl';p.write_bytes(b'')
        initial=G.bookkeeping_bytes(self.root,['ledger/model_capacity.jsonl'])
        p.write_bytes(b'first append\n');G.check_bookkeeping(self.root,initial)
        p.unlink()
        with self.assertRaisesRegex(G.Stop,'removed'):G.check_bookkeeping(self.root,initial)

    def test_default_workers_reserve_one_third_and_cap_at_sixteen(self):
        with patch.object(G.os,'sched_getaffinity',return_value=set(range(24))):self.assertEqual(G.worker_counts({}),(16,4,4))
        with patch.object(G.os,'sched_getaffinity',return_value={0}):self.assertEqual(G.worker_counts({}),(1,1,1))
        self.assertEqual(G.worker_counts({'workers':6,'certificate_workers':3}),(6,3,2))
        for bad in (0,-1,True,'16'):
            with self.assertRaisesRegex(G.Stop,'positive integer'):G.worker_counts({'workers':bad})

    def dependency(self,name,writes=(),reads=None,aliases=None):
        base=self.base/name;base.mkdir();entry=base/'apply.py';entry.write_text('pass')
        (base/'files.json').write_text(json.dumps([{'path':p,'before':'old','after':'new'} for p in writes]))
        (base/'manifest.json').write_text(json.dumps({'protected_inputs':reads or {},'protected_links':aliases or {}}))
        return {'entry':str(entry)}

    def test_reader_before_writer_is_allowed_and_reverse_has_order_hint(self):
        writer=self.dependency('writer',['config/overlays/dungeon.rowbase.jsonl'])
        reader=self.dependency('reader',reads={'config/overlays/dungeon.rowbase.jsonl':'old'})
        self.assertTrue(P.guard_collisions([reader,writer]))
        hints=P.ordering_hints([writer,reader]);self.assertEqual(hints['suggested_order'],[1,0])
        with self.assertRaisesRegex(P.G.Stop,'package-order hints'):P.guard_collisions([writer,reader])

    def test_two_readers_do_not_conflict(self):
        a=self.dependency('a',reads={'include/common.h':'old'});b=self.dependency('b',reads={'include/common.h':'old'})
        self.assertEqual(P.ordering_hints([a,b])['conflicts'],[]);P.guard_collisions([a,b])

    def test_proof_tool_alias_detects_target_writer(self):
        a=self.dependency('slus',['tools/build/configure.py'])
        b=self.dependency('headers',aliases={'tools/gate/configure.py':'../build/configure.py'})
        hint=P.ordering_hints([a,b]);self.assertEqual(hint['suggested_order'],[1,0])
        self.assertEqual(hint['conflicts'][0]['path'],'tools/build/configure.py')

    def test_dependency_cycle_requires_combining_and_reproving(self):
        a=self.dependency('a',['a'],{'b':'old'});b=self.dependency('b',['b'],{'a':'old'})
        hints=P.ordering_hints([a,b]);self.assertIsNone(hints['suggested_order']);self.assertEqual(hints['cycle'],[0,1])

    def test_record_applier_rowbase_write_is_named_even_without_file_guard(self):
        writer=self.dependency('bank');reader=self.dependency('data',reads={'config/overlays/dungeon.rowbase.jsonl':'old'})
        Path(writer['entry']).write_text("rbpath=path(root,'config/overlays/dungeon.rowbase.jsonl')\nif transactions:rbpath.write_text(text)\n")
        hints=P.ordering_hints([writer,reader]);self.assertEqual(hints['suggested_order'],[1,0])
        self.assertTrue(hints['conflicts'][0]['inferred']);P.guard_collisions([writer,reader])

    def test_indirect_slus_configure_write_names_proof_alias_dependency(self):
        writer=self.dependency('slus');reader=self.dependency('headers',aliases={'tools/gate/configure.py':'../build/configure.py'})
        Path(writer['entry']).write_text("if moves:(root/'tools/build/configure.py').write_text(config_text)\n")
        hints=P.ordering_hints([writer,reader]);self.assertEqual(hints['suggested_order'],[1,0])
        self.assertEqual(hints['conflicts'][0]['path'],'tools/build/configure.py')
        self.assertTrue(hints['conflicts'][0]['inferred'])

if __name__=='__main__':unittest.main()
