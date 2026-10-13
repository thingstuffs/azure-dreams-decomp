"""Synthetic ABI and search checks; no canonical root, compiler or ledger reads."""
import io,json,os,re,runpy,struct,sys,tempfile,unittest
from pathlib import Path
from unittest import mock
ROOT=Path(__file__).resolve().parents[2];KIT=ROOT/'tools/lanes/lanekit';sys.path.insert(0,str(KIT))
import pass_oracle as P,oracle_search as S,source_refs as SR,attribute as AT,mutate_search as MS

class SchemaTests(unittest.TestCase):
    def test_every_kind_has_one_complete_schema(self):
        cases=[{'kind':'sched-priority','uid':2,'phase':'sched1','value':7},
               {'kind':'sched-birth','uid':2,'phase':'sched1','value':0},
               {'kind':'sched-luid','uid':2,'phase':'sched2','value':0},
               {'kind':'combine-veto','uids':[3,2,0]}, {'kind':'combine-crosses','uids':[3,2,1]},
               {'kind':'cse-copy-swap','uid':2},{'kind':'cse-substitution','uid':2,'occurrence':0},
               {'kind':'alias','uids':[3,2],'phase':'sched2','value':1},
               {'kind':'loop-hoist','uid':2},{'kind':'loop-biv','uid':2,'pseudo':80},
               {'kind':'keep-dead','uid':2},{'kind':'reload-equiv','uid':2,'occurrence':0},
               {'kind':'reload-cse','uid':2},{'kind':'reload-reuse','uid':2,'occurrence':0,'value':0},
               {'kind':'reload-noop','uid':2,'value':1},{'kind':'global-avoid','pseudo':81,'hardreg':4},
               {'kind':'reorg-fill','uid':2,'candidate_uid':3,'value':0},
               {'kind':'reorg-merge','uid':2,'thread_uid':3,'value':0},
               {'kind':'reorg-delete','uid':2,'value':0},
               {'kind':'jump-cross','uids':[2,3],'value':0},{'kind':'frame-offset','occurrence':0,'value':-4},
               {'kind':'cse-eqv-head','new':82,'old':81,'occurrence':0,'head':82}]
        self.assertEqual({c['kind'] for c in cases},set(P.KINDS))
        for c in cases:P.validate(c)
    def test_rejects_unknown_extra_or_missing_inputs(self):
        for c in ({'kind':'x'},{'kind':'alias','uids':[1,2],'phase':'sched2','value':2},
                  {'kind':'loop-hoist'},{'kind':'loop-hoist','uid':2,'pseudo':80},
                  {'kind':'combine-veto','uids':[1,1,0]},
                  {'kind':'sched-birth','uid':True,'phase':'sched1','value':0},
                  {'kind':'sched-priority','uid':1,'phase':'sched','value':3},
                  {'kind':'global-avoid','pseudo':81,'hardreg':70},{'kind':'global-avoid','pseudo':81},
                  {'kind':'reorg-fill','uid':1,'candidate_uid':2,'value':2},
                  {'kind':'jump-cross','uids':[1,1],'value':0},{'kind':'cse-eqv-head','new':1,'old':2,'head':0}):
            with self.assertRaises(ValueError):P.validate(c)
    def test_other_cells_fail_closed_before_preprocess(self):
        with self.assertRaises(ValueError),mock.patch.object(P.sncheck,'preprocess') as cpp:
            P.trace({'cfg':'2.95.2-G0','id':'x'},'void f(){}')
        cpp.assert_not_called()
    def test_grouped_context_guard_is_slus_specific(self):
        overlay={'cfg':'2.7.2-cdk-G0','id':'x','kind':'overlay'}
        slus={'cfg':'2.7.2-cdk-G0','id':'x','kind':'slus'}
        with mock.patch.object(P.kitlib,'module_fingerprint',return_value='fingerprint'),mock.patch.object(P.sncheck,'preprocess',side_effect=RuntimeError('reached preprocess')):
            with self.assertRaisesRegex(RuntimeError,'reached preprocess'):P.trace(overlay,'void f(){}')
            with self.assertRaisesRegex(ValueError,'grouped SLUS'):P.trace(slus,'void f(){}')
    def test_composite_schema(self):
        a={'kind':'combine-veto','uids':[3,2,0]};b={'kind':'alloc','pseudo':81,'input':{'kind':'refs-add','value':-2}}
        P.validate([a,b]);self.assertEqual(P.members([a,b]),[a,b]);self.assertEqual(P.members(a),[a])
        for bad in ([a],[a,a],[a,b,{'kind':'keep-dead','uid':2},{'kind':'keep-dead','uid':3},{'kind':'keep-dead','uid':4}],
                    [a,{'kind':'alloc','pseudo':81,'input':{'kind':'refs','value':0}}],[a,{'kind':'alloc','pseudo':81}]):
            with self.assertRaises(ValueError):P.validate(bad)
        self.assertEqual({P.family_of(c) for c in (a,b,{'kind':'global-avoid','pseudo':1,'hardreg':2},{'kind':'keep-dead','uid':1})},
                         {'combine','alloc','global','dead'})
    def test_aligned_distance_counts_an_insertion_once(self):
        w=lambda *xs:b''.join(struct.pack('<I',x) for x in xs)
        self.assertEqual(P.aligned_distance(w(1,2,3,4,5),w(1,2,3,4,5)),0)
        self.assertEqual(P.aligned_distance(w(1,2,9,3,4,5),w(1,2,3,4,5)),1)
        self.assertEqual(P.aligned_word_diff(w(1,2,9,3),w(1,2,3)),[
            {'generated_index':2,'retail_index':None,'generated_word':'0x00000009','retail_word':None}])
    def test_slus_object_without_text_fails_closed(self):
        with self.assertRaises(ValueError):P.slus_text({'.data':b'x'})
        self.assertEqual(P.slus_text({'.text':b'','.text.f':b'abcd'}),b'abcd')

class SyntheticGDB(unittest.TestCase):
    def setUp(self):
        self.temp=tempfile.TemporaryDirectory();self.old=os.getcwd();os.chdir(self.temp.name)
        self.data=bytearray(65536);self.writes=[];self.registers={'esp':0x1000,'eax':0,'eip':0}
        owner=self
        class Inferior:
            def read_memory(self,a,n):return bytes(owner.data[a:a+n])
            def write_memory(self,a,b):owner.writes.append((a,bytes(b)));owner.data[a:a+len(b)]=b
        class BP:
            def __init__(self,*a,**k):pass
        def parse(s):return 0 if s=='$_exitcode' else self.registers[s[1:]]
        def execute(s,**k):
            if s.startswith('set $'):
                name,value=s[5:].split(' = ');self.registers[name]=int(value)
        fake=mock.Mock();fake.selected_inferior.return_value=Inferior();fake.parse_and_eval.side_effect=parse
        fake.execute.side_effect=execute;fake.Breakpoint=BP;fake.FinishBreakpoint=BP
        a={'rest_of_compilation':128,'reload_completed':256,'insn_priority':260,'insn_luid':264}
        Path('pass_cfg.json').write_text(json.dumps({'addresses':a,'sizes':{},'change':None,'families':[],'function':'f','max_events':10}))
        self.u(260,0x2000);self.u(264,0x3000)
        with mock.patch.dict(sys.modules,{'gdb':fake}):self.ns=runpy.run_path(str(KIT/'pass_oracle_gdb.py'))
        self.gl=self.ns['birth'].__globals__;self.gl['Finish']=lambda fn:fn()
    def tearDown(self):os.chdir(self.old);self.temp.cleanup()
    def u(self,a,v):self.data[a:a+4]=struct.pack('<I',v)
    def change(self,c):self.gl['CHANGES'][:]=c if isinstance(c,list) else [c]
    def test_birth_changes_only_matching_phase_uid(self):
        self.gl['sched_context'][:]=[65];self.registers['eax']=1
        self.change({'kind':'sched-birth','uid':64,'phase':'sched1','value':0});self.ns['birth']()
        self.assertEqual(self.registers['eax'],1);self.assertFalse(self.gl['R']['applied'])
        self.change({'kind':'sched-birth','uid':65,'phase':'sched1','value':0});self.ns['birth']()
        self.assertEqual(self.registers['eax'],0);self.assertEqual(self.writes,[])
        self.assertEqual(len(self.gl['R']['mutations']),1)
    def test_unchanged_birth_is_not_applied(self):
        self.gl['sched_context'][:]=[65];self.registers['eax']=0
        self.change({'kind':'sched-birth','uid':65,'phase':'sched1','value':0});self.ns['birth']()
        self.assertFalse(self.gl['R']['applied'])
    def test_alias_requires_unique_oriented_pair(self):
        self.gl['arg']=lambda i:[0x4000,0x4100][i];self.gl['mem_insns'].update({0x4000:{279},0x4100:{19}})
        self.u(256,1);self.change({'kind':'alias','uids':[19,279],'phase':'sched2','value':1})
        self.ns['dependence']();self.assertFalse(self.gl['R']['applied'])
        self.change({'kind':'alias','uids':[279,19],'phase':'sched2','value':1})
        self.ns['dependence']();self.assertEqual(self.registers['eax'],1)
        self.assertEqual(self.gl['R']['mutations'][0]['uids'],[279,19])
    def test_alias_ambiguous_memory_fails_closed(self):
        self.gl['arg']=lambda i:[0x4000,0x4100][i];self.gl['mem_insns'].update({0x4000:{279,277},0x4100:{19}})
        self.change({'kind':'alias','uids':[279,19],'phase':'sched1','value':1});self.ns['dependence']()
        self.assertFalse(self.gl['R']['applied']);self.assertEqual(self.registers['eax'],0)
    def test_sched_priority_changes_one_array_slot(self):
        insn=0x4000;self.u(insn+4,65);self.u(0x2000+4*65,9)
        self.gl['arg']=lambda i:insn;self.gl['brief']=lambda x:'set';self.gl['field']=lambda x,i:0
        self.change({'kind':'sched-priority','uid':65,'phase':'sched1','value':7});self.ns['adjust']()
        self.assertEqual(self.writes,[(0x2000+4*65,struct.pack('<i',7))])
        self.assertEqual(self.gl['sched_context'],[])
    def test_combine_veto_uses_exact_uid_tuple_and_cdecl_return(self):
        ps=[0x4000,0x4100,0];self.u(ps[0]+4,11);self.u(ps[1]+4,4);self.u(0x1000,0x9000)
        self.gl['arg']=lambda i:ps[i];self.gl['name']=lambda p:'note';self.change({'kind':'combine-veto','uids':[11,4,0]})
        self.ns['combine']();self.assertEqual(self.registers['eip'],0x9000)
        self.assertEqual(self.registers['esp'],0x1004);self.assertEqual(self.registers['eax'],0)
        self.assertEqual(self.writes,[])
    def test_loop_hoist_changes_only_done_bit(self):
        node=0x4000;insn=0x4100;self.u(node,insn);self.u(insn+4,538);self.u(node+20,215);self.u(node+28,5);self.u(node+44,0)
        self.gl['arg']=lambda i:node;self.change({'kind':'loop-hoist','uid':538});self.ns['hoist']()
        self.assertEqual(self.writes,[(node+28,struct.pack('<i',13))])
    def test_reload_equiv_veto_does_not_change_nonmatching_occurrence(self):
        insn=0x4000;self.u(insn+4,10);got=0x4100;self.u(got+4,18)
        self.gl['arg']=lambda i:[0,insn][i];self.gl['name']=lambda p:'reg';self.registers['eax']=got
        self.change({'kind':'reload-equiv','uid':10,'occurrence':1});self.ns['equiv']()
        self.assertEqual(self.registers['eax'],got);self.ns['equiv']();self.assertEqual(self.registers['eax'],0)

    def test_composite_vetoes_each_member_and_records_which_applied(self):
        ps=[0x4000,0x4100,0];self.u(ps[0]+4,11);self.u(ps[1]+4,4);self.u(0x1000,0x9000)
        self.gl['arg']=lambda i:ps[i];self.gl['name']=lambda p:'note'
        self.change([{'kind':'combine-veto','uids':[20,19,0]},{'kind':'combine-veto','uids':[11,4,0]}])
        self.ns['combine']();self.assertEqual(self.registers['eax'],0);self.assertEqual(self.gl['R']['applied_changes'],[1])
    def test_global_avoid_sets_one_conflict_bit(self):
        a=self.gl['A'];a.update({'max_regno':0x500,'reg_allocno':0x504,'max_allocno':0x508,'hard_reg_conflicts':0x50c})
        self.u(0x500,200);self.u(0x504,0x6000);self.u(0x508,5);self.u(0x50c,0x7000);self.u(0x6000+4*81,2)
        self.change({'kind':'global-avoid','pseudo':81,'hardreg':4});self.ns['global_avoid']()
        self.assertEqual(self.writes,[(0x7000+12*2,struct.pack('<I',16))]);self.assertTrue(self.gl['R']['applied'])
        self.writes.clear();self.u(0x6000+4*82,0xffffffff);self.change({'kind':'global-avoid','pseudo':82,'hardreg':4});self.ns['global_avoid']()
        self.assertEqual(self.writes,[]);self.assertIn('no global allocno',self.gl['R']['errors'][-1])
    def test_flow_facts_from_arrays_or_28_reg_info(self):
        a=self.gl['A'];a.update({'reg_n_refs':0x500,'reg_n_deaths':0x504,'reg_n_info':0x508})
        self.u(0x500,0x6000);self.u(0x504,0x6800);self.u(0x6000+4*90,7);self.data[0x6800+2*90:0x6800+2*90+2]=struct.pack('<h',3)
        self.assertEqual((self.ns['rget']('refs',90),self.ns['rget']('deaths',90)),(7,3))
        self.gl['RI']={'stride':40,'refs':16,'deaths':20,'live':24,'block':32};self.u(0x508,0x7000)
        self.u(0x7000+40*90+16,11);self.u(0x7000+40*90+20,2);self.u(0x7000+40*90+32,0xfffffffe)
        self.assertEqual((self.ns['rget']('refs',90),self.ns['rget']('deaths',90),self.ns['rget']('block',90)),(11,2,-2))
        self.ns['rput']('refs',90,9);self.assertEqual(self.writes[-1],(0x7000+40*90+16,struct.pack('<i',9)))
    def test_alloc_refs_write_inside_composite(self):
        a=self.gl['A'];a.update({'reg_n_refs':0x500});self.u(0x500,0x6000);self.u(0x6000+4*81,20)
        self.gl['AA'].update({'max_regno':0x520});self.u(0x520,200);self.gl['C']['first']=76
        self.change([{'kind':'alloc','pseudo':81,'input':{'kind':'refs-add','value':1}},{'kind':'keep-dead','uid':3}])
        self.ns['alloc_reg']();self.assertEqual(self.writes,[(0x6000+4*81,struct.pack('<i',21))])
        self.assertEqual(self.gl['R']['applied_changes'],[0])
    def test_reorg_fill_inverts_one_observed_pair(self):
        delay,cand=0x4000,0x4100;self.u(delay+4,23);self.u(cand+4,20)
        self.gl['arg']=lambda i:{0:delay,2:cand}[i];self.registers['eax']=1
        self.change({'kind':'reorg-fill','uid':23,'candidate_uid':20,'value':0});self.ns['reorg_eligible']()
        self.assertEqual(self.registers['eax'],0);self.assertEqual(self.gl['R']['mutations'][-1]['kind'],'reorg-fill')
    def test_reorg_null_thread_is_reported_without_rtx_dereference(self):
        delay=0x4000;self.u(delay+4,23);self.gl['arg']=lambda i:[delay,0][i];self.gl['F'].add('reorg')
        self.ns['reorg_merge']()
        self.assertEqual(self.gl['R']['errors'],[])
        self.assertEqual(self.gl['R']['skipped_sites'][-1]['hook'],'try_merge_delay_insns')
        self.assertIn('null',self.gl['R']['skipped_sites'][-1]['reason'])
    def test_hook_cap_disables_breakpoint_and_reports_unknown_tail(self):
        calls=[];self.gl['C']['hook_cap']=2;self.gl['active']=lambda:True
        hook=self.gl['Hook']('probe',lambda:calls.append(1),address=0x500)
        hook.stop();hook.stop();hook.stop()
        self.assertEqual(calls,[1,1]);self.assertFalse(hook.enabled)
        self.assertEqual(self.gl['R']['hook_counts']['probe'],3)
        self.assertEqual(self.gl['R']['skipped_hooks'][-1]['remaining_calls'],'unknown (breakpoint disabled)')
    def test_jump_cross_veto_clears_tail_outputs(self):
        e1,e2,p1,p2=0x4000,0x4100,0x4200,0x4204
        self.u(e1+4,33);self.u(e2+4,64);self.u(p1,0x4300);self.u(p2,0x4400);self.u(0x4300+4,31);self.u(0x4400+4,62)
        self.gl['arg']=lambda i:[e1,e2,2,p1,p2][i]
        self.change({'kind':'jump-cross','uids':[33,64],'value':0});self.ns['jump_cross']()
        self.assertEqual((struct.unpack('<I',self.data[p1:p1+4])[0],struct.unpack('<I',self.data[p2:p2+4])[0]),(0,0))
    def test_frame_offset_changes_preallocation_cursor(self):
        self.gl['A']['frame_offset']=0x500;self.u(0x500,0)
        self.u(0x1000+4,26);self.u(0x1000+8,4);self.u(0x1000+12,4)
        self.change({'kind':'frame-offset','occurrence':0,'value':-4});self.ns['frame_slot']()
        self.assertEqual(struct.unpack('<i',self.data[0x500:0x504])[0],-4)
    def test_cse_equivalence_head_relinks_chain(self):
        a=self.gl['A'];a.update({'reg_qty':0x500,'qty_first_reg':0x504,'qty_last_reg':0x508,
                                 'reg_next_eqv':0x50c,'reg_prev_eqv':0x510})
        for sym,base in [('reg_qty',0x6000),('qty_first_reg',0x7000),('qty_last_reg',0x7400),
                         ('reg_next_eqv',0x7800),('reg_prev_eqv',0x7c00)]:self.u(a[sym],base)
        self.u(0x6000+4*81,3);self.u(0x7000+4*3,81);self.u(0x7400+4*3,82)
        self.u(0x7800+4*81,82);self.u(0x7800+4*82,0xffffffff)
        self.u(0x7c00+4*81,0xffffffff);self.u(0x7c00+4*82,81)
        self.u(0x1000+4,82);self.u(0x1000+8,81)
        self.change({'kind':'cse-eqv-head','new':82,'old':81,'occurrence':0,'head':82});self.ns['cse_eqv']()
        self.assertEqual(struct.unpack('<i',self.data[0x7000+12:0x7000+16])[0],82)

class SearchTests(unittest.TestCase):
    def test_gate_requires_all_five_successes_without_duplicates(self):
        rows=[{'known':n,'rediscovered':True} for n in S.KNOWN];self.assertTrue(S.trusted_gate({'rows':rows}))
        self.assertFalse(S.trusted_gate({'rows':rows[:-1]}));rows[-1]['rediscovered']=False
        self.assertFalse(S.trusted_gate({'rows':rows}));rows[-1]={'known':S.KNOWN[0],'rediscovered':True}
        self.assertFalse(S.trusted_gate({'rows':rows}))
    def test_listing_identity_cannot_be_ranked_exact(self):
        listing={'change':{'kind':'loop-hoist','uid':1},'listing_identical':True}
        exact={'change':{'kind':'loop-hoist','uid':2},'raw':{'raw_equal':True,'word_mismatches':0}}
        self.assertLess(S.rank(exact),S.rank(listing))
    def test_space_uses_only_observed_successful_merges(self):
        obs={'events':[{'kind':'combine-veto','uids':[3,2,0],'success':False,'patterns':[]},
                       {'kind':'combine-veto','uids':[5,4,0],'success':True,'patterns':[]},
                       {'kind':'combine-crosses','uids':[5,4,0],'value':0}]}
        space=S.enumerate_changes(obs)
        self.assertEqual([c['uids'] for c in space],[[5,4,0],[5,4,0]])
        self.assertEqual(len({S.key(c) for c in space}),len(space))
    def test_family_interleaving_does_not_starve_rare_sites(self):
        obs={'events':[{'kind':'sched-birth','uid':i,'phase':'sched1','value':1} for i in range(1,100)]+
                      [{'kind':'loop-hoist','uid':150,'done':False},{'kind':'cse-copy-swap','uid':151}]}
        space=S.enumerate_changes(obs)
        self.assertEqual(space[0]['kind'],'cse-copy-swap');self.assertIn('loop-hoist',[c['kind'] for c in space[:3]])
    def test_invalid_trial_has_no_raw_receipt(self):
        with tempfile.TemporaryDirectory() as td,mock.patch.object(P,'trace',side_effect=ValueError('unsupported')):
            r=S.run_trial({'id':'x'},'void f(){}',{'kind':'loop-hoist','uid':1},Path(td),1)
        self.assertNotIn('raw',r);self.assertIn('unsupported',r['errors'][0])

    def test_combine_class_is_one_composite_ahead_of_singles(self):
        pat=lambda p:['set(p104,ashiftrt(p%d,16))'%p,'set(p%d,ashift(p104,16))'%p,'set(p104,zero_extend(mem(p127)))']
        obs={'events':[{'kind':'combine-veto','uids':[11,10,9],'success':True,'patterns':pat(357)},
                       {'kind':'combine-veto','uids':[21,20,19],'success':True,'patterns':pat(358)},
                       {'kind':'combine-veto','uids':[31,30,0],'success':True,'patterns':['set(p1,p2)','set(p2,p3)','nil']}]}
        self.assertEqual(S.shape(pat(357)),S.shape(pat(358)))
        space=S.enumerate_changes(obs)
        self.assertEqual(space[0],[{'kind':'combine-veto','uids':[11,10,9]},{'kind':'combine-veto','uids':[21,20,19]}])
        self.assertEqual(len([c for c in space if isinstance(c,list)]),1)
    def test_new_families_are_enumerated_only_from_observed_sites(self):
        obs={'events':[{'kind':'reorg-fill','uid':10,'candidate_uid':11,'value':True},
                       {'kind':'reorg-merge','uid':12,'thread_uid':13,'value':True},
                       {'kind':'reorg-delete','uid':14,'value':True},
                       {'kind':'jump-cross','uids':[20,21],'value':True,'forceable':False},
                       {'kind':'reload-reuse','uid':30,'occurrence':0,'value':True},
                       {'kind':'reload-noop','uid':31,'value':False},
                       {'kind':'frame-offset','occurrence':0,'before':-16,'size':4},
                       {'kind':'cse-eqv-head','new':82,'old':81,'occurrence':0,'head':81,'chain':[81,82]}]}
        space=S.enumerate_changes(obs,include_alloc=False);keys={S.key(c) for c in space}
        for change in ({'kind':'reorg-fill','uid':10,'candidate_uid':11,'value':0},
                       {'kind':'reorg-merge','uid':12,'thread_uid':13,'value':0},
                       {'kind':'reorg-delete','uid':14,'value':0},
                       {'kind':'jump-cross','uids':[20,21],'value':0},
                       {'kind':'reload-reuse','uid':30,'occurrence':0,'value':0},
                       {'kind':'reload-noop','uid':31,'value':1},
                       {'kind':'cse-eqv-head','new':82,'old':81,'occurrence':0,'head':82}):self.assertIn(S.key(change),keys)
    def test_wrong_registers_reads_register_only_differences(self):
        enc=lambda rs,rt,rd:struct.pack('<I',(rs<<21)|(rt<<16)|(rd<<11)|0x21)
        got=enc(4,0,2)+enc(5,0,3)+struct.pack('<I',0x08000010);ret=enc(5,0,2)+enc(5,0,3)+struct.pack('<I',0x08000010)
        wrong,pairs=S.wrong_registers(got,ret);self.assertEqual(dict(wrong),{4:1});self.assertEqual(dict(pairs),{(4,5):1})
        obs={'events':[{'kind':'global-colour','pseudo':81,'allocno':1,'hardreg':4},{'kind':'global-colour','pseudo':90,'allocno':-1,'hardreg':2}]}
        self.assertEqual(S.focus_pseudos(obs,{4:3,2:1}),{81})
        space=S.enumerate_changes(dict(obs,stats=[{'stage':'before-local','pseudos':[{'pseudo':81,'refs':5,'life':9,'block':-2},{'pseudo':90,'refs':2,'life':3,'block':4}]}]),focus={81})
        self.assertEqual(space[0],{'kind':'global-avoid','pseudo':81,'hardreg':4})
        self.assertTrue(all(c.get('pseudo')==81 for c in space[:5]))
    def test_composites_pair_only_improving_distinct_singles(self):
        t=lambda ch,d,err=():{'change':ch,'errors':list(err),'raw':{'raw_equal':d==0,'aligned_distance':d}}
        a={'kind':'keep-dead','uid':1};b={'kind':'keep-dead','uid':2};c={'kind':'keep-dead','uid':3};d={'kind':'keep-dead','uid':4}
        cls=[{'kind':'combine-veto','uids':[5,4,0]},{'kind':'combine-veto','uids':[7,6,0]}]
        combos=S.composites([t(a,5),t(b,6),t(c,9),t(d,4,['boom']),t(cls,3)],baseline=8)
        keys={S.key(x) for x in combos}
        self.assertIn(S.key(sorted([a,b],key=S.key)),keys);self.assertNotIn(S.key(sorted([a,c],key=S.key)),keys)
        self.assertTrue(all(2<=len(x)<=P.MAX_COMPOSITE for x in combos))
        self.assertTrue(any(len(x)==3 for x in combos))
    def test_finished_trial_is_reused_on_resume(self):
        ch={'kind':'loop-hoist','uid':1}
        with tempfile.TemporaryDirectory() as td:
            Path(td,'trial.json').write_text(json.dumps({'change':ch,'errors':[],'raw':{'raw_equal':True}}))
            with mock.patch.object(P,'trace') as tr:r=S.run_trial({'id':'x'},'void f(){}',ch,Path(td),1)
            tr.assert_not_called();self.assertTrue(r['resumed'])
            Path(td,'trial.json').write_text(json.dumps({'change':ch,'errors':['TimeoutExpired: x']}))
            with mock.patch.object(P,'trace',side_effect=ValueError('again')):r=S.run_trial({'id':'x'},'void f(){}',ch,Path(td),1)
            self.assertIn('again',r['errors'][0])

class RefTests(unittest.TestCase):
    def test_residual_is_visible_and_sources_never_guessed(self):
        t={'dumps':{'flow':''},'asm':'','refs':[{'uid':10,'pseudo':80,'weight':2,'role':'use'}],
           'stats':[{'stage':'before-local','pseudos':[{'pseudo':80,'refs':3,'life':42}]}]}
        r=SR.build({'id':'x','cfg':'cell'},'int f(){}',t,False);p=r['pseudos'][0]
        self.assertEqual(p['unattributed_weight'],1);self.assertIsNone(p['contributions'][0]['source'])
        self.assertEqual(p['source_weight'],0);self.assertIn('residual',SR.render(r))

class AttributionAndMutationTests(unittest.TestCase):
    def test_asm_word_map_expands_li_and_keeps_uid(self):
        asm='\tli\t$2,1  # 10 movsi\n\tli\t$3,0x12345678  # 11 movsi\n\taddu\t$2,$2,$3  # 12 addsi\n'
        rows,coverage=AT.asm_word_map(asm,4)
        self.assertEqual([r['uid'] for r in rows],[10,11,11,12]);self.assertEqual(coverage['binary_words'],4)
    def test_mutation_text_extractor_ignores_labels(self):
        value=[('label','int f(void)\n{\n return 1;\n}\n'),{'text':'void g(void)\n{\n}\n'}]
        self.assertEqual(len(list(MS._text_values(value))),2)

class DiscoveryAndCellTests(unittest.TestCase):
    def test_native_symbol_control_falls_back_to_uninjected_oracle(self):
        fast={'asm':'','error':None};fallback={'asm':'.ent true_name\ntrue_name:\n.end true_name\n','errors':[]}
        with mock.patch.object(S.kitlib,'dumps',return_value=fast),mock.patch.object(P,'trace',return_value=fallback) as trace:
            control,elapsed,method=S.pinned_control({'id':'x'},'void true_name(){}',1)
        self.assertIn('.ent true_name',control['asm']);self.assertIn('fallback',method);self.assertGreaterEqual(elapsed,0)
        trace.assert_called_once_with({'id':'x'},'void true_name(){}',families=[],timeout=1)
    def test_native_module_control_extracts_true_function_without_oracle(self):
        module='.text\n.ent first\nfirst:\n.end first\n.ent true_name\ntrue_name:\n.end true_name\n'
        with mock.patch.object(S.kitlib,'dumps',return_value={'asm':module,'error':None}),mock.patch.object(P,'function_name',return_value='true_name'),mock.patch.object(P,'trace') as trace:
            control,_,method=S.pinned_control({'id':'x'},'void true_name(){}',1)
        self.assertEqual(re.findall(r'^\s*\.ent\s+(\S+)',control['asm'],re.M),['true_name'])
        self.assertIn('extraction',method);trace.assert_not_called()
    def test_pass_oracle_full_discovery_splits_calibrated_groups(self):
        calls=[]
        def trace(row,text,**kw):
            calls.append(kw['families']);fam=kw['families'][0]
            return {'events':[{'kind':fam}],'refs':[],'stats':[],'errors':[],'truncated':False,'mutations':[],
                    'missing_hooks':[],'skipped_hooks':[],'skipped_sites':[],'hook_counts':{fam:2},'commands':[],
                    'dumps':{},'asm':'.ent f\nli $2,1\n.end f','cc1_sha256':'abc','input_sha256':'def','faithful':True}
        with mock.patch.object(P,'trace',side_effect=trace):
            r=P.discover_trace({'id':'x','cfg':'cell'},'int f(){}',P.FAMILIES,1)
        self.assertEqual(calls,[list(group) for group in P.DISCOVERY_GROUPS])
        self.assertEqual(len(r['family_runs']),len(P.DISCOVERY_GROUPS));self.assertFalse(r['truncated'])
        self.assertEqual(r['hook_counts']['sched'],2)
    def test_independent_discovery_keeps_other_families_after_timeout(self):
        def trace(row,text,**kw):
            fam=kw['families']
            if fam==['combine']:raise TimeoutError('slow family')
            return {'events':[{'kind':fam[0]}],'refs':[],'stats':[],'errors':[],'truncated':False,
                    'asm':'.ent f\nf:\nli $2,1\n.end f','cc1_sha256':'abc'}
        with tempfile.TemporaryDirectory() as td,mock.patch.object(P,'trace',side_effect=trace):
            r=S.discover({'id':'x'},'int f(){}',Path(td),1)
        self.assertTrue(r['faithful']);self.assertEqual(len(r['discovery_errors']),1)
        self.assertEqual(len(r['events']),9);self.assertEqual(r['discovery_errors'][0]['families'],['combine'])
    def test_divergent_observer_is_excluded(self):
        counter=[0]
        def trace(row,text,**kw):
            counter[0]+=1
            return {'events':[],'refs':[],'stats':[],'errors':[],'truncated':False,
                    'asm':'.ent f\nli $2,%d\n.end f'%counter[0],'cc1_sha256':'abc'}
        with tempfile.TemporaryDirectory() as td,mock.patch.object(P,'trace',side_effect=trace):
            r=S.discover({'id':'x'},'int f(){}',Path(td),1)
        self.assertEqual(len(r['discovery_errors']),9)
    def test_discovery_resumes_family_by_family(self):
        calls=[]
        def trace(row,text,**kw):
            calls.append(kw['families'])
            if kw['families']==['dead'] or kw['families']==['loop','dead','reload']:raise TimeoutError('slow')
            return {'events':[{'kind':kw['families'][0]}],'refs':[],'stats':[],'errors':[],'truncated':False,
                    'asm':'.ent f\nli $2,1\n.end f','cc1_sha256':'abc'}
        with tempfile.TemporaryDirectory() as td:
            with mock.patch.object(P,'trace',side_effect=trace):a=S.discover({'id':'x'},'int f(){}',Path(td),1)
            n=len(calls)
            with mock.patch.object(P,'trace',side_effect=trace):b=S.discover({'id':'x'},'int f(){}',Path(td),1)
        self.assertEqual(len(calls),n);self.assertEqual(a['events'],b['events']);self.assertEqual(len(b['discovery_errors']),1)
    def test_263_rejects_names_and_multiple_input_fields(self):
        import alloc263_oracle as A
        with self.assertRaises(ValueError):A.trace({'cfg':'2.6.3-G0'},'void f(){}','state')
        with self.assertRaises(ValueError):A.validate_change({'kind':'refs','value':14,'life':34})
        A.validate_change({'kind':'refs','value':14})
    def test_timeout_kills_group_before_reaping(self):
        import subprocess
        proc=mock.Mock(pid=123,returncode=-9)
        proc.communicate.side_effect=[subprocess.TimeoutExpired(['gdb'],1),('out','err')]
        with mock.patch.object(P.subprocess,'Popen',return_value=proc) as popen,mock.patch.object(P.os,'killpg') as kill:
            with self.assertRaises(subprocess.TimeoutExpired) as e:P.run_bounded(['gdb'],Path('.'),1)
        self.assertTrue(popen.call_args.kwargs['start_new_session']);kill.assert_called_once_with(123,P.signal.SIGKILL)
        self.assertEqual(e.exception.stdout,'out');self.assertEqual(proc.communicate.call_count,2)

class RefQueryTests(unittest.TestCase):
    def test_goal_uses_observed_weights_and_preserves_live_total(self):
        view={'pseudos':[{'pseudo':369,'refs':27,'life':168,'contributions':[
            {'uid':194,'weight':3,'source':{'file':'f.c','line':269},'statement':'mesh = cells[index];'},
            {'uid':1041,'weight':3,'source':{'file':'f.c','line':366},'statement':'index++;'},
            {'uid':1041,'weight':3,'source':{'file':'f.c','line':366},'statement':'index++;'}]}]}
        q=SR.query(view,369,3,180)
        self.assertEqual(q['refs_goal'],24);self.assertEqual(q['life_goal'],180)
        self.assertEqual(q['counted_source_sites'][0]['source']['line'],269)
        self.assertEqual(q['counted_source_sites'][1]['weight'],6)
        self.assertEqual(q['observed_life'],168)
    def test_dead_pseudo_and_nonpositive_goals_refused(self):
        view={'pseudos':[{'pseudo':80,'refs':3,'life':42,'contributions':[]}]}
        for args in [(81,None,None),(80,3,None),(80,0,None),(80,None,0)]:
            with self.assertRaises(ValueError):SR.query(view,*args)

if __name__=='__main__':unittest.main()
