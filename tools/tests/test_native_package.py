"""Native admission, whole-TU batching and guarded package fixtures. No live tree."""
import contextlib
import hashlib
import importlib.util
import io
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

TOOLS = Path(__file__).resolve().parents[1]
sys.path[:0] = [str(TOOLS/'lanes'), str(TOOLS/'lanes/lanekit'), str(TOOLS)]
import lane_admission as A
import native_member as N
import native_package as P
import native_package_apply as APPLY


def digest(text):
    return hashlib.sha256(text.encode()).hexdigest()


class Admission(unittest.TestCase):
    def check(self, cur, cand, **kw):
        with patch.object(A.land_admit, 'fidelity_counts', return_value=kw.pop('fidelity', (0,0))):
            return A.assess({'id':'dungeon/a'}, cand, cur, kw.pop('base',digest(cur)), 'lane', **kw)

    def test_stale_base_and_no_improvement_refused(self):
        self.assertFalse(self.check('goto done;', 'return;', base='0'*64)['accepted'])
        self.assertFalse(self.check('return;', 'return;')['accepted'])

    def test_existing_equal_pin_admission_reasons(self):
        for cur, cand in [('goto done;', 'return;'), ('volatile int x;', 'int x;'),
                          ('int temp_x;', 'int value;'), ('x=x;', ''), ('int x;', 'int  x;')]:
            with self.subTest(cur=cur):
                self.assertTrue(self.check(cur,cand)['accepted'])
        self.assertTrue(self.check('f(1);','f(1,2);',fidelity=(0,1))['accepted'])
        self.assertTrue(self.check('f(1);','f(2);',readable_lanes=['lane'])['accepted'])

    def test_growth_cannot_hide_behind_a_goto_win(self):
        for cand in ['volatile int x; return;', '__asm__("x"); return;',
                     'register int x asm("$4"); return;', 'ASM_USE(x); return;',
                     'x=x; return;', 'int temp_x; return;', 'do {} while (0); return;']:
            with self.subTest(cand=cand):
                self.assertFalse(self.check('goto done;',cand)['accepted'])
        self.assertFalse(self.check('goto done;','return;',fidelity=(1,0))['accepted'])

    def test_macro_volatile_is_counted_per_invocation(self):
        macro='#define SPAD(b,T,f) (((volatile T *)(b))->f)\n'
        out=self.check(macro+'SPAD(a,T,x); SPAD(a,T,y);',macro+'SPAD(a,T,x);')
        self.assertTrue(out['accepted']);self.assertIn('volatile',out['fell'])

    def test_pin_growth_and_owner_exceptions(self):
        self.assertFalse(self.check('', 'ASM_MOVE(x);')['accepted'])
        with patch.object(A, 'sites_of', side_effect=lambda s: [1] if s=='old' else []):
            self.assertFalse(self.check('old','do {} while (0);')['accepted'])
            self.assertTrue(self.check('old','do {} while (0);',onetrip_ok=['dungeon/a'])['accepted'])
            self.assertFalse(self.check('old','ODDITY_FENCE(x);')['accepted'])
            self.assertTrue(self.check('old','ODDITY_FENCE(x);',oddity_ok=['dungeon/a'])['accepted'])


class Fixture(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR'))
        self.base = Path(self.temp.name); self.root = self.base/'tree'; self.root.mkdir()
        self.lane = self.root/'work/native_lane/test'; self.lane.mkdir(parents=True)
        self.m = dict(key='fixture_module', container='dungeon', source='src/dungeon/modules/tu.c',
            headers=['include/m.h'], review_inputs=[], imports=[], owned_data=[dict(size=4)],
            members=[dict(id='dungeon/a', source='src/dungeon/a.c',function='fa',foff=0,vma=0x1000,size=8,body_offset=4),
                     dict(id='dungeon/b', source='src/dungeon/b.c',function='fb',foff=8,vma=0x1008,size=4,body_offset=0)])
        self.rows=[dict(id=a['id'],kind='overlay',cfg='2.7.2-cdk-G0') for a in self.m['members']]
        for rel, data in {'src/dungeon/a.c':'int fa(){goto done; done:return 0;}\n',
            'src/dungeon/b.c':'int fb(){goto done; done:return 0;}\n',
            'src/dungeon/modules/tu.c':'#include "../a.c"\n#include "../b.c"\n',
            'include/m.h':'', 'config/overlays/modules.json':json.dumps(dict(modules=[self.m])),
            'work/disc/containers/test.bin':'HEADAAAABBBB'}.items():self.write(rel,data)
        self.addCleanup(self.temp.cleanup)
        for patcher in [patch.object(N.kitlib,'ROOT',self.root), patch.object(P,'ROOT',self.root)]:
            patcher.start();self.addCleanup(patcher.stop)

    def write(self, rel, data):
        p=self.root/rel;p.parent.mkdir(parents=True,exist_ok=True);p.write_text(data);return p

    def stage(self, rid='a', cand=None):
        cur=(self.root/f'src/dungeon/{rid}.c').read_text()
        cand=cand or cur.replace('goto done; done:', '')
        self.write(f'work/native_lane/test/out/dungeon/{rid}.c',cand)
        self.write(f'work/native_lane/test/out/dungeon/{rid}.c.base_sha',digest(cur))

    def authority(self):
        return SimpleNamespace(CONTAINERS={'dungeon':'test.bin'}, all_members=lambda m:m['members'],
            module_first=lambda m:dict(foff=0,vma=0x1000),module_size=lambda m:12)

    def measure(self, data=b'HEADAAAABBBB', placed=None, texts=None, fingerprints=None):
        placed=placed or dict(fa=(0x1004,4),fb=(0x1008,4));texts=texts or dict.fromkeys([r['id'] for r in self.rows],'candidate')
        metrics=lambda a,b:dict(exact=a==b,total=sum(x!=y for x,y in zip(a,b)),subs=0,indels=0)
        with patch.object(N,'membership',return_value=self.m),patch.object(N,'gate',return_value=self.authority()), \
             patch.object(N,'fingerprint',side_effect=fingerprints or ['stable','stable']), \
             patch.object(N.kitlib,'bootstrap',return_value=self.lane), \
             patch.object(N,'byte_stats',side_effect=metrics), \
             patch.object(N,'compile_object',return_value=(data,placed,{})) as compile:
            (self.lane/'tmp').mkdir(exist_ok=True)
            result=N.score_batch([r for r in self.rows if r['id'] in texts],texts,self.m)
            self.assertEqual(compile.call_count,1)
            self.assertEqual(compile.call_args.kwargs['texts'],texts)
            return result

    def test_batch_one_compile_and_every_byte_checked(self):
        result=self.measure();self.assertTrue(result['exact']);self.assertEqual(result['module_bytes'],12)
        self.assertEqual(result['selected_members'],['dungeon/a','dungeon/b'])

    def test_selected_exact_sibling_broken_refused(self):
        result=self.measure(b'HEADAAAAFAIL',texts={'dungeon/a':'candidate'})
        self.assertTrue(result['selected_exact']);self.assertFalse(result['exact'])
        self.assertEqual([r['id'] for r in result['other_members_changed']],['dungeon/b'])

    def test_owned_data_extent_and_addresses_fail_closed(self):
        self.assertFalse(self.measure(b'FAILAAAABBBB')['exact'])
        self.assertFalse(self.measure(b'HEADAAAABBBBTAIL')['exact'])
        self.assertFalse(self.measure(placed=dict(fa=(0x1004,4),fb=(0x1009,4)))['exact'])
        with self.assertRaisesRegex(RuntimeError,'context changed'):
            self.measure(fingerprints=['before','after'])

    def test_one_member_wrapper_retains_aggregate_verdict(self):
        batch=self.measure(b'HEADAAAAFAIL',texts={'dungeon/a':'candidate'})
        with patch.object(N,'_score_batch',return_value=batch):
            result=N.score(self.rows[0],'candidate',self.m)
        self.assertFalse(result['exact']);self.assertTrue(result['member_exact'])
        self.assertEqual(result['kind'],'NATIVE_MEMBER_DIAGNOSTIC')

    def test_batch_rejects_duplicates_foreign_cfg_and_modules(self):
        with self.assertRaises(ValueError):N.score_batch([self.rows[0]]*2,{'dungeon/a':'candidate'})
        with patch.object(N,'membership',side_effect=[self.m,{**self.m,'key':'other'}]),self.assertRaises(ValueError):
            N.score_batch(self.rows,dict.fromkeys([r['id'] for r in self.rows],'candidate'))
        with patch.object(N,'gate',return_value=SimpleNamespace(load_modules=lambda root:[self.m])):
            self.m['recipe']={'cfg':'2.7.2-cdk-G0'}
            with self.assertRaisesRegex(ValueError,'recipe differs'):
                N.membership({**self.rows[0],'cfg':'2.8.0'})
            self.write('config/overlay_modules_disabled','')
            self.assertIsNone(N.membership(self.rows[0]))

    def test_physical_tu_replaces_all_members_once(self):
        ca=self.base/'a.c';cb=self.base/'b.c';ca.write_text('candidate a');cb.write_text('candidate b')
        texts={'src/dungeon/a.c':ca,'src/dungeon/b.c':cb}
        source=N.source_text_many(self.m,texts)
        self.assertIn(str(ca),source);self.assertIn(str(cb),source)
        self.write(self.m['source'],'#include "../a.c"\n#include "../a.c"\n')
        with self.assertRaisesRegex(ValueError,'exactly once'):N.source_text_many(self.m,texts)
        with self.assertRaisesRegex(ValueError,'function members'):N.source_text_many(self.m,{'src/data.c':ca})

    def test_tu_escape_refused(self):
        ca=self.base/'a.c';ca.write_text('candidate')
        (self.root/'src/dungeon/b.c').unlink();(self.root/'src/dungeon/b.c').symlink_to(ca)
        with self.assertRaisesRegex(ValueError,'escapes root'):
            N.source_text_many(self.m,{'src/dungeon/a.c':ca})

    def prepare_package(self):
        self.stage('a');self.stage('b')
        self.write('ledger/modules/overlay_fixture_module.json',json.dumps(dict(module='fixture_module',reviewer='existing-reviewer')))
        win='config/overlays/fixture.overlay.yaml';self.write(win,'standalone_build: {}\n')
        gate=SimpleNamespace(all_members=lambda m:m['members'],closure=lambda root,starts:set(starts),
                             affected_windows=lambda m,root:[win])
        score=dict(exact=True,module_exact=True,owned_data_exact=True,other_members_changed=[],selected_members=['dungeon/a','dungeon/b'])
        context=({r['id']:r for r in self.rows},{})
        patchers=[patch.object(A,'context',return_value=context),patch.object(A.land_admit,'fidelity_counts',return_value=(0,0)),
            patch.object(N,'membership',return_value=self.m),patch.object(N,'gate',return_value=gate),
            patch.object(N,'fingerprint',return_value='stable'),patch.object(N,'score_batch',return_value=score),
            patch.object(N.kitlib,'bootstrap',return_value=self.lane),patch.object(P.subprocess,'check_output',return_value='HEAD\n')]
        for p in patchers:p.start();self.addCleanup(p.stop)
        self.score_mock = N.score_batch
        self.write('tools/lanes/native_package_apply.py', (TOOLS/'lanes/native_package_apply.py').read_text())
        return self.score_mock

    def test_generated_batch_is_one_source_only_package_and_renewal_plan(self):
        score=self.prepare_package()
        with contextlib.redirect_stdout(io.StringIO()):self.assertEqual(P.generate([self.lane],self.lane),0)
        self.assertEqual(score.call_count,1)
        files=json.loads((self.lane/'delivery/files.json').read_text());self.assertEqual(len(files),2)
        self.assertTrue(all(r['path'].startswith('src/') for r in files))
        m=json.loads((self.lane/'delivery/manifest.json').read_text());self.assertEqual(m['certificates_requiring_renewal'],['fixture_module'])
        self.assertEqual(m['reviewer'],'pending');self.assertEqual(m['production_windows'],['config/overlays/fixture.overlay.yaml'])
        plan=json.loads((self.lane/'plan.json').read_text());self.assertEqual(len(plan['packages']),1)
        self.assertEqual(plan['reviewer'],'pending');self.assertTrue(plan['isolated'])
        self.assertFalse(plan['allow_census_change']);self.assertNotIn('scripts',plan)

    def test_carried_proof_artifacts_remain_sealed_without_rewriting_machine_paths(self):
        self.prepare_package();proof_root=self.base/'post-apply';proof_root.mkdir()
        for rid in ('a','b'):
            p=proof_root/f'src/dungeon/{rid}.c';p.parent.mkdir(parents=True,exist_ok=True)
            p.write_bytes((self.lane/f'out/dungeon/{rid}.c').read_bytes())
        import proof_receipts as R
        def export(root,key,directory):
            directory.mkdir(parents=True);(directory/'proof-receipt.json').write_text('{}')
            (directory/'module.s').write_text('.file "'+chr(47)+'home/lane/module.c"')
        with patch.object(R,'export_module',side_effect=export),contextlib.redirect_stdout(io.StringIO()):
            P.generate([self.lane],self.lane,proof_root)
        package=self.lane/'delivery';index=json.loads((package/'proofs.json').read_text())
        directory=index[0]['directory'];self.assertTrue(directory.startswith('diagnostics/portable_proofs/'))
        sealed=json.loads((package/'package.sha256.json').read_text())
        self.assertIn(directory+'/module.s',sealed);self.assertIn('proofs.json',sealed)
        # The generic package lint permits sealed diagnostic origins, while
        # the proof reader independently validates these immutable artifacts.
        import package_preflight
        result=package_preflight.lint_inventory(package/'apply.py',self.root)
        self.assertEqual(result['sources'],2)

    def test_duplicate_native_rows_across_lanes_refused(self):
        self.prepare_package();other=self.root/'work/native_lane/other';other.mkdir()
        import shutil
        shutil.copytree(self.lane/'out',other/'out')
        with self.assertRaisesRegex(ValueError,'duplicate staged'):P.collect([self.lane,other])

    def test_raw_membership_does_not_fall_back_when_disabled(self):
        self.prepare_package()
        with patch.object(N,'membership',return_value=None),self.assertRaisesRegex(ValueError,'unavailable'):
            P.collect([self.lane])
        self.assertFalse((self.lane/'delivery').exists())

    def test_bad_batch_never_emits_a_delivery(self):
        self.prepare_package()
        with patch.object(N,'score_batch',return_value=dict(exact=False)),self.assertRaisesRegex(ValueError,'TU refused'):
            P.generate([self.lane],self.lane)
        self.assertFalse((self.lane/'delivery').exists());self.assertFalse((self.lane/'plan.json').exists())

    def test_admission_skip_and_empty_ordinary_fallback(self):
        self.prepare_package();self.write('work/native_lane/test/out/dungeon/a.c.base_sha','bad')
        groups,rejected,ordinary,seen=P.collect([self.lane]);self.assertEqual(len(groups['fixture_module']['rows']),1)
        self.assertEqual(rejected[0]['reason'],'stale base');self.assertTrue(seen)
        with patch.object(P,'collect',return_value=({},[],['ordinary'],False)):
            self.assertEqual(P.generate([self.lane],self.lane),3)

    def test_applier_contract_integrity_and_all_guards_before_write(self):
        self.prepare_package()
        with contextlib.redirect_stdout(io.StringIO()):P.generate([self.lane],self.lane)
        delivery=self.lane/'delivery'
        with patch.object(APPLY,'P',delivery),patch.object(APPLY,'CANONICAL',self.root), \
             patch.dict(os.environ,{'LAND_LIVE_ROOT':str(self.root)}):
            with self.assertRaisesRegex(ValueError,'without --live'):APPLY.apply(self.root,dry_run=True)
            # Fingerprints are fixture measurements; the test supplies the authority result.
            from gate import overlay_module_gate as G
            with patch.object(G,'load_modules',return_value=[self.m]),patch.object(G,'fingerprint',return_value={'sha256':'stable'}):
                before=(self.root/'src/dungeon/a.c').read_bytes()
                with contextlib.redirect_stdout(io.StringIO()):APPLY.apply(self.root,dry_run=True,live=True)
                self.assertEqual(before,(self.root/'src/dungeon/a.c').read_bytes())
                self.write('src/dungeon/b.c','drift')
                with self.assertRaisesRegex(ValueError,'source guard'):APPLY.apply(self.root,live=True)
                self.assertEqual(before,(self.root/'src/dungeon/a.c').read_bytes())
                self.write('src/dungeon/b.c','int fb(){goto done; done:return 0;}\n')
                with contextlib.redirect_stdout(io.StringIO()):APPLY.apply(self.root,live=True);APPLY.apply(self.root,live=True)
                self.assertNotIn('goto',(self.root/'src/dungeon/a.c').read_text())
                (delivery/'sources/src/dungeon/a.c').write_text('tamper')
                with self.assertRaisesRegex(ValueError,'integrity'):APPLY.apply(self.root,live=True)

    def test_path_guards(self):
        with self.assertRaises(ValueError):P.safe(self.root,'../escape')
        (self.root/'escape').symlink_to(self.base,target_is_directory=True)
        with self.assertRaises(ValueError):APPLY.local(self.root,'escape/file')


class ShellRoute(unittest.TestCase):
    def test_native_fallback_exits_before_apply_candidates_or_cascade(self):
        # Execute the real shell with a tiny script fixture and a native package stub.
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as td:
            root=Path(td);lanes=root/'tools/lanes';lanes.mkdir(parents=True)
            (lanes/'land_lanes.sh').write_text((TOOLS/'lanes/land_lanes.sh').read_text())
            (lanes/'native_package.py').write_text('from pathlib import Path\nPath("native-routed").touch()\nraise SystemExit(0)\n')
            result=subprocess.run(['bash',str(lanes/'land_lanes.sh'),'tag','fixture'],cwd=root,
                env=dict(os.environ,LAND_ISOLATED='1',LAND_BUSY_CMD='false',TMPDIR=td),capture_output=True,text=True)
            self.assertEqual(result.returncode,0,result.stderr)
            self.assertTrue((root/'native-routed').exists());self.assertIn('NATIVE_PACKAGE_READY',result.stdout)
            self.assertNotIn('cascade:',result.stdout)

    def test_native_refusal_cannot_reach_ordinary_path(self):
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as td:
            root=Path(td);lanes=root/'tools/lanes';lanes.mkdir(parents=True)
            (lanes/'land_lanes.sh').write_text((TOOLS/'lanes/land_lanes.sh').read_text())
            (lanes/'native_package.py').write_text('raise SystemExit(1)\n')
            result=subprocess.run(['bash',str(lanes/'land_lanes.sh'),'tag','fixture'],cwd=root,
                env=dict(os.environ,LAND_ISOLATED='1',LAND_BUSY_CMD='false',TMPDIR=td),capture_output=True,text=True)
            self.assertEqual(result.returncode,1);self.assertNotIn('cascade:',result.stdout)


class WindowBoundaries(unittest.TestCase):
    def test_window_cutting_through_member_never_builds_or_projects_raw_bytes(self):
        gate = N.gate()
        member = dict(id='dungeon/fixture', source='src/dungeon/fixture.c',
                      function='fixture', foff=0x200, vma=0x80010200, size=0x100)
        module = dict(key='fixture', container='dungeon', members=[member])
        partial = SimpleNamespace(start=0x240, end=0x300, size=0xC0,
                                  kind='c', match=SimpleNamespace())
        with patch.object(gate, 'load_modules', return_value=[module]), \
             patch.object(gate, 'build') as build:
            with self.assertRaisesRegex(ValueError, 'partial'):
                gate.project_segments([partial], Path('unused'),
                                      'dungeon_fixture', root=Path.cwd())
            build.assert_not_called()


if __name__ == '__main__':
    unittest.main()
