"""Durability, selection controls, and exact-candidate staging for the atlas."""
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import pin_atlas as atlas
from pin_census import sites_of

SOURCE = 'void f(int x, int y, int z) {\n ASM_KEEP(x);\n ASM_KEEP(y);\n ASM_KEEP(z);\n}\n'


def single(total, lo, hi):
    return dict(status='ok', total=total, regions=[dict(t=[lo,hi],g=[lo,hi],op='r',got=['move a,b'],tgt=['move c,b'])])


class AtlasTests(unittest.TestCase):
    def test_uniform_sample_does_not_depend_on_overlap_ranking(self):
        ss = [single(i+1, i, i+3) for i in range(8)]
        first = atlas.pair_plan('row', ss, 4)
        changed = [single(i+1, 100*i, 100*i+1) for i in range(8)]
        second = atlas.pair_plan('row', changed, 4)
        uniform = lambda plan: [p['s'] for p in plan if 'uniform' in p['arms']]
        self.assertEqual(uniform(first), uniform(second))
        self.assertEqual(len(uniform(first)), 4)
        self.assertEqual(first, atlas.pair_plan('row', ss, 4))
        self.assertFalse(any('overlap' in p['arms'] for p in second))

    def test_failed_sites_excluded_and_unknown_ranges_not_overlap(self):
        ss = [single(2,0,2), dict(status='failed',total=None),dict(status='ok',total=3)]
        plan = atlas.pair_plan('row', ss, 10)
        self.assertEqual([p['s'] for p in plan], [[0,2]])
        self.assertEqual(plan[0]['arms'], ['uniform'])

    def test_late_regions_and_insertion_boundaries_are_used(self):
        a = single(5,0,1); a['regions'] += [dict(t=[i,i+1]) for i in range(30,60)]
        self.assertGreater(atlas.overlap(a,single(1,59,59)),0)
        self.assertEqual(atlas.overlap(single(1,0,1),single(1,1,2)),0)

    def test_measured_groups_bounded_and_do_not_duplicate_pairs(self):
        ss = [single(5,0,5)] * 3
        pairs = [dict(s=[0,1],status='ok',total=2),dict(s=[1,2],status='ok',total=2)]
        groups = atlas.group_plan(sites_of(SOURCE),ss,pairs,8)
        self.assertEqual(groups, [dict(s=[0,1,2],reason='strip')])

    def test_manifest_options_and_source_are_bound(self):
        m = dict(schema=1,rows=[dict(sha='a')],fingerprints={},options={'pairs':2},environment={})
        k = atlas.manifest_key(m)
        m['options']['pairs']=3
        self.assertNotEqual(k,atlas.manifest_key(m))
        m['options']['pairs']=2;m['rows'][0]['sha']='b'
        self.assertNotEqual(k,atlas.manifest_key(m))

    def setup_probe(self, directory):
        d = Path(directory); (d/'input.c').write_text(SOURCE)
        m = dict(key='frozen-key',environment={},options=dict(timeout=1,pairs_per_arm=2,max_groups=2))
        item = dict(row=dict(id='test/f',c_path='f.c'),sha=atlas.sha_text(SOURCE),input='input.c')
        return d,m,item,d/'rows/f'

    def fake_popen(self, calls):
        class Process:
            pid=123456789; returncode=0
            def __init__(self,cmd,**kwargs):
                calls.append(cmd)
                req=Path(cmd[cmd.index('--probe')+1]);data=json.loads(req.read_text())
                self.source=Path(data['source']).read_text()
                atlas.atomic_json(req.with_suffix('.result.json'),dict(status='ok',exact=True,total=0,regions=[]))
            def wait(self,timeout=None):return 0
        return Process

    def test_probe_cache_resume_and_candidate_source_preserved(self):
        with tempfile.TemporaryDirectory() as td:
            d,m,item,rd=self.setup_probe(td);calls=[]
            with patch.object(atlas.subprocess,'Popen',self.fake_popen(calls)):
                rec=atlas.measure(d,m,item,rd,[0,2])
                (rd/'candidates/0-2.c').unlink() # killed after the probe receipt, before candidate write
                again=atlas.measure(d,m,item,rd,[0,2])
            self.assertEqual(rec,again);self.assertEqual(len(calls),1)
            candidate=(rd/'candidates/0-2.c').read_text()
            self.assertEqual(len(sites_of(candidate)),1)
            self.assertIn('ASM_KEEP(y)',candidate)
            self.assertEqual((d/'input.c').read_text(),SOURCE)
            m['key']='other'
            with self.assertRaisesRegex(RuntimeError,'identity changed'):atlas.measure(d,m,item,rd,[0,2])

    def test_failed_probe_not_accepted_and_retry_is_explicit(self):
        with tempfile.TemporaryDirectory() as td:
            d,m,item,rd=self.setup_probe(td)
            key=atlas.digest([m['key'],item['row']['id'],[0]])
            atlas.atomic_json(rd/'probes/0.json',dict(key=key,status='failed',exact=False))
            with patch.object(atlas.subprocess,'Popen',side_effect=AssertionError('must not compile')):
                self.assertEqual(atlas.measure(d,m,item,rd,[0])['status'],'failed')
            calls=[]
            with patch.object(atlas.subprocess,'Popen',self.fake_popen(calls)):
                self.assertTrue(atlas.measure(d,m,item,rd,[0],retry_errors=True)['exact'])
            self.assertEqual(len(calls),1)

    def test_row_resume_uses_individual_probe_cache(self):
        with tempfile.TemporaryDirectory() as td:
            d,m,item,_=self.setup_probe(td); calls=[]
            with patch.object(atlas.subprocess,'Popen',self.fake_popen(calls)):
                first=atlas.row_job(d,m,item); count=len(calls)
                (d/'rows/test_f/result.json').unlink() # interruption before durable row summary
                second=atlas.row_job(d,m,item)
            self.assertEqual(len(calls),count)
            self.assertEqual(first['best_removal'],3)
            self.assertEqual(first['probes'],second['probes'])

if __name__ == '__main__': unittest.main()
