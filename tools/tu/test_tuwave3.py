"""Regression tests for registered assembler recipes and shared-file cohorts."""
import json
from pathlib import Path
from types import SimpleNamespace
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parent))
import tu_merge as M


class RegisteredFlagsTests(unittest.TestCase):
    def test_only_known_registered_treatments_are_accepted(self):
        self.assertEqual(M.member_asflags('--expand-div --preserve-return-delay'),
                         ['--expand-div', '--preserve-return-delay'])
        for flags in ('--anything', '--expand-div --expand-div', '--gnu-as-path=other'):
            with self.assertRaises(M.Refused):
                M.member_asflags(flags)

    def test_member_assembler_receives_the_registered_flags(self):
        calls=[]
        def run(argv, **kw):
            calls.append(argv)
            if '-S' in argv:
                Path(argv[-1]).write_text('assembly')
            return SimpleNamespace(returncode=0, stdout=b'processed', stderr=b'')
        with tempfile.TemporaryDirectory() as td, patch.object(M.subprocess, 'run', side_effect=run):
            root=Path(td)
            M.compile_obj(root, root/'source.c', '2.7.2-cdk-G0', root, 'member',
                          row_asflags='--preserve-return-delay')
        self.assertIn('--preserve-return-delay', calls[-1])
        self.assertNotIn('--preserve-return-delay', calls[0])

    def test_flag_removal_needs_equal_original_objects(self):
        with tempfile.TemporaryDirectory() as td:
            root=Path(td)
            (root/'spec.json').write_text(json.dumps(dict(recipe='2.7.2-cdk-G0',
                modules=[dict(key='new', source='src/new.c')])))
            ms=[dict(id='town/a', module='new', path='src/a.c', cfg='2.7.2-cdk-G0',
                     size=4, row_asflags='--expand-div')]
            (root/'members.json').write_text(json.dumps(ms))
            def compile(*args, **kw):
                return Path('old.o' if kw.get('row_asflags') else 'new.o'), ''
            def text(obj):
                return (b'old!' if obj.name=='old.o' else b'new!'), [], {}
            with patch.object(M, 'compile_obj', side_effect=compile), \
                 patch.object(M, 'text_and_relocs', side_effect=text):
                ok, proof=M.prove(root, root)
            self.assertFalse(ok)
            self.assertFalse(proof['new']['text_equal'])
            self.assertEqual(proof['new']['member_recipes'][0]['row_asflags'], '--expand-div')

    def test_reattribution_retires_flags_and_keeps_split_history(self):
        with tempfile.TemporaryDirectory() as td:
            root=Path(td);(root/'ledger/splits').mkdir(parents=True)
            split=dict(func_vram='func_80000000',result='MATCH',config='2.7.2-cdk-G0',
                       row_asflags='--expand-div')
            row=dict(id='town/func_80000000',cfg='2.7.2-cdk-G0',row_asflags='--expand-div')
            M.wjl(root/'ledger/splits/town.jsonl',[split]);M.wjl(root/'ledger/rows.jsonl',[row])
            (root/'config/overlays').mkdir(parents=True)
            M.wjl(root/'config/overlays/town.as_flags.jsonl',
                  [dict(func='func_80000000',as_flags='--expand-div',proof='original')])
            members=[dict(id=row['id'],cfg=row['cfg'],row_asflags=row['row_asflags'])]
            changed=M.reattribute(root,M.Freezer(root,root/'base'),'town',members,row['cfg'],'test')
            self.assertEqual(changed,[row['id']])
            self.assertEqual(M.jl(root/'ledger/rows.jsonl')[0]['row_asflags'], '')
            new=M.jl(root/'ledger/splits/town.jsonl')[0]
            self.assertEqual(new['row_asflags_was'],'--expand-div')
            self.assertNotIn('row_asflags',new)
            flag=M.jl(root/'config/overlays/town.as_flags.jsonl')[0]
            self.assertEqual(flag['as_flags'],'')
            self.assertEqual(flag['as_flags_was'],'--expand-div')
            self.assertEqual(flag['proof'],'original')
            self.assertEqual(new['tu_recipe_history'][0]['row_asflags'],'--expand-div')


class PrivateTypesTests(unittest.TestCase):
    def test_only_local_typedef_identifiers_change(self):
        source='typedef int (*Callback)(int);\n/* Callback */\nint f(Callback cb) { return cb(1); }\n'
        changed=M.rename_private_types(source,{'Callback':'ValueCallback'})
        self.assertIn('typedef int (*ValueCallback)(int);',changed)
        self.assertIn('f(ValueCallback cb)',changed)
        self.assertIn('/* Callback */',changed)
        with self.assertRaises(M.Refused):M.rename_private_types(source,{'f':'g'})
        with self.assertRaises(M.Refused):M.rename_private_types(source,{'Callback':'cb'})

    def test_proof_pages_preserve_every_record_and_stay_bounded(self):
        import tu_cohort as C
        facts=dict(sites=['town/a','town/b'],homes=['town/a','town/b'],
                   cohorts=[dict(image='town/i',detail='x'*40) for _ in range(30)],
                   holds=[dict(reason='partial',index=i) for i in range(20)])
        with tempfile.TemporaryDirectory() as td:
            path=Path(td)/'group.json';C.write_details(facts,path,limit=1000)
            summary=json.loads(path.read_text())
            rebuilt={k:[] for k in ('cohorts','holds')}
            for page in summary['pages']:
                p=path.parent/page['path']
                self.assertLessEqual(p.stat().st_size,1000)
                rebuilt[page['kind']]+=json.loads(p.read_text())
            self.assertEqual(rebuilt['cohorts'],facts['cohorts'])
            self.assertEqual(rebuilt['holds'],facts['holds'])


class PlacementCohortTests(unittest.TestCase):
    def test_two_complete_copies_in_one_image_keep_distinct_members(self):
        import tu_placements as P
        entries={}
        for suffix,base in [('',0x100),('_one',0x200),('_two',0x300)]:
            for i,h in enumerate(['a','b']):
                rid='town/'+h+suffix
                entries[rid]=dict(row=rid,home='town/'+h,image='town/image',
                                  foff=base+4*i,vma=0x80000000+base+4*i)
        cohorts=P.placement_cohorts(['town/a','town/b'],entries)
        self.assertEqual(len(cohorts),2)
        self.assertTrue(all(not missing for _,_,missing in cohorts))
        self.assertEqual([[e['row'] for e in es] for _,es,_ in cohorts],
                         [['town/a_one','town/b_one'],['town/a_two','town/b_two']])
        del entries['town/b_two']
        cohorts=P.placement_cohorts(['town/a','town/b'],entries)
        self.assertEqual(cohorts[1][2],['town/b'])


    def test_distinct_descriptor_keys_and_legacy_single_key(self):
        import tu_placements as P
        module=dict(key='new',container='town',recipe={},imports=[])
        image=dict(image='town/image',foff=0,vma=0x80000000)
        entries=[dict(home='town/a',row='town/a_one',foff=0x200)]
        args=(Path('.'),module,'town/home',{'town/image':image},(), 'town/image',entries)
        one,_,_=P.descriptor(*args,distinguish_cohort=True)
        entries[0]=dict(entries[0],row='town/a_two',foff=0x300)
        two,_,_=P.descriptor(*args,distinguish_cohort=True)
        legacy,_,_=P.descriptor(*args)
        self.assertNotEqual(one['key'],two['key'])
        self.assertEqual(legacy['key'],'new_image')


    def test_missing_first_member_is_a_fact_instead_of_a_status_crash(self):
        import test_tuwave2 as W
        fixture=W.DestinationTests()
        group,images,entries,rows=fixture.tables()
        group['member_rows']='town/unregistered;'+group['member_rows']
        groups,cohorts=fixture.status(group,images,entries,rows)
        self.assertEqual(groups[0]['mergeable_now'],'no')
        self.assertIn('unregistered member town/unregistered',groups[0]['missing_facts'])
        self.assertEqual(cohorts[0]['cohort_foff'],'')


class RowbaseConflictTests(unittest.TestCase):
    def test_row_attribution_failure_retains_the_conflicting_proven_region(self):
        import load_rowbase as R
        with tempfile.TemporaryDirectory() as td:
            root=Path(td)
            proof=dict(method='validated test loader',delta=0x80000000,foff=0,size=0x1000)
            (root/'load.jsonl').write_text(json.dumps(proof)+'\n')
            image=dict(container='town',foff=0,size=0x1000,vma=0x80000000,
                       load_evidence=dict(path='load.jsonl',record_sha256=R.rec_sha(proof)))
            split=dict(func_vram='func_80001010',true_name='func_80001010',
                       foff=0x100,size=4,result='MATCH')
            old=dict(region='old',foff_start='0x100',foff_end='0x104',
                     delta='0x80000F10',base_confidence='proven')
            result=R.assess(root,'town/image',{'town/image':image},[split],[old],{}, {})
            self.assertFalse(result['ok'])
            self.assertIn('L3:',result['reason'])
            self.assertEqual(result['overlapping_base_conflicts'][0]['region'],'old')
            self.assertEqual(result['overlapping_base_conflicts'][0]['base_confidence'],'proven')
            self.assertTrue(result['registered_base_conflicts'])


class SharedCohortTests(unittest.TestCase):
    def fixture(self):
        import tu_cohort as C
        self.C=C
        rows={}
        entries={}
        for suffix,base in [('',0x100),('_copy',0x200),('_again',0x300)]:
            for i,name in enumerate(['a','b']):
                rid='town/'+name+suffix;home='town/'+name
                row=dict(id=rid,container='town',foff=base+i*4,size=4)
                if suffix:row['source_row']=home
                rows[rid]=row
                entries[rid]=dict(row=rid,home=home,image='town/image',foff=row['foff'],
                                  size=4,vma=0x80000000+row['foff'])
        regions={'town':[(0,0x1000,0x80000000,'proven','engine')]}
        return rows,entries,regions

    def test_complete_shared_sites_use_existing_definitions(self):
        rows,entries,regions=self.fixture()
        sites=['town/a_copy','town/b_copy']
        facts=self.C.plan(sites,{},entries,rows,regions)
        self.assertTrue(facts['geometry_complete'])
        self.assertEqual(len(facts['cohorts']),3)
        spec=dict(container='town',modules=[dict(members=sites)])
        normalized=self.C.home_spec(spec,facts)
        self.assertEqual(normalized['modules'][0]['members'],['town/a','town/b'])
        self.assertEqual(normalized['placement_sites'],sites)
        self.assertEqual(spec['modules'][0]['members'],sites)

    def test_partial_same_image_use_cannot_hide_in_another_copy(self):
        rows,entries,regions=self.fixture();del entries['town/b_again'];del rows['town/b_again']
        facts=self.C.plan(['town/a_copy','town/b_copy'],{},entries,rows,regions)
        self.assertFalse(facts['geometry_complete'])
        hold=next(h for h in facts['holds'] if h['reason']=='partial_cohort')
        self.assertEqual(hold['foff'],0x300)
        self.assertEqual(hold['missing'][0]['home'],'town/b')
        self.assertEqual(hold['missing'][0]['foff'],0x304)
        with self.assertRaises(ValueError):self.C.home_spec({},facts)

    def test_registry_only_copy_and_wrong_slot_are_explicit(self):
        rows,entries,regions=self.fixture();del entries['town/b_again']
        facts=self.C.plan(['town/a_copy','town/b_copy'],{},entries,rows,regions)
        self.assertIn('unindexed_use',[h['reason'] for h in facts['holds']])
        del rows['town/b_again']
        entries['town/other']=dict(entries['town/a_again'],row='town/other',home='town/other',foff=0x304)
        facts=self.C.plan(['town/a_copy','town/b_copy'],{},entries,rows,regions)
        miss=next(h for h in facts['holds'] if h['reason']=='partial_cohort')['missing'][0]
        self.assertEqual(miss['occupants'],['town/other'])

    def test_repeated_definition_and_missing_load_proof_refuse(self):
        rows,entries,regions=self.fixture()
        facts=self.C.plan(['town/a','town/a_copy'],{},entries,rows,regions)
        self.assertEqual(facts['holds'][0]['reason'],'repeated_definition')
        facts=self.C.plan(['town/a_copy','town/b_copy'],{},entries,rows,{})
        self.assertEqual({h['reason'] for h in facts['holds']},{'no_rowbase'})

    def test_scattered_homes_need_reviewed_rehome(self):
        rows,entries,regions=self.fixture()
        rows['town/b']['foff']=0x1040;entries['town/b']['foff']=0x1040
        facts=self.C.plan(['town/a_copy','town/b_copy'],{},entries,rows,regions)
        self.assertIn('home_relocation_required',[h['reason'] for h in facts['holds']])

    def test_source_row_cycles_do_not_become_new_definitions(self):
        rows,entries,regions=self.fixture();rows['town/a']['source_row']='town/a_copy'
        facts=self.C.plan(['town/a_copy','town/b_copy'],{},entries,rows,regions)
        self.assertEqual(facts['holds'][0]['reason'],'missing_home')


if __name__=='__main__':
    unittest.main()
