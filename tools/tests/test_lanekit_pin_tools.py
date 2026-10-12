"""Pin-tool tests use synthetic inputs and mocked compilers, never a canonical checkout."""
import io,json,os,runpy,struct,sys,tempfile,unittest
from pathlib import Path
from unittest import mock
from contextlib import redirect_stdout
ROOT=Path(__file__).resolve().parents[2];KIT=ROOT/'tools/lanes/lanekit'
for p in (ROOT/'tools',ROOT/'tools/xform',ROOT/'tools/lanes',KIT):sys.path.insert(0,str(p))
import sncheck,alloc_oracle,value_luid,why,lab,kitlib

class SNTests(unittest.TestCase):
    def test_normalization_keeps_codegen_differences(self):
        a='.extern x\n\t.ent f\r\nf:\n\t.set noreorder\n\tli\t$4,12 # comment\n\t.end f\n'
        b='.text\n.ent  f\nf:\n.set noreorder\nli $4,12\n.end f\n'
        self.assertEqual(sncheck.normalize(a),sncheck.normalize(b))
        self.assertNotEqual(sncheck.normalize(a),sncheck.normalize(b.replace('12','13')))
        self.assertNotEqual(sncheck.normalize(a),sncheck.normalize(b.replace('noreorder','reorder')))
    def test_strings_and_generation(self):
        self.assertIn('.ascii "a#b  c"',sncheck.normalize('.ent f\n.ascii "a#b  c" # drop\n.end f'))
        self.assertEqual(sncheck.generation('2.7.2-cdk')[0],'4.1')
        self.assertEqual(sncheck.generation('2.8.0')[0],'4.4')
        self.assertEqual(sncheck.generation('2.8.1')[0],'4.4')
        self.assertEqual(sncheck.generation('2.95.2')[0],'4.6')
        with self.assertRaises(ValueError):sncheck.generation('2.7.2')
    def test_cpp_command_uses_registered_flags_and_local_cwd(self):
        with tempfile.TemporaryDirectory() as td:
            d=Path(td)
            with mock.patch('sncheck.subprocess.run',return_value=mock.Mock(returncode=0)) as run:
                _,flags,cmd=sncheck.preprocess({'cfg':'2.7.2-cdk-G0 -fno-delayed-branch'},'int f(){return 1;}',d)
            self.assertIn('-G0',flags);self.assertIn('-fno-delayed-branch',cmd)
            self.assertEqual(run.call_args.kwargs['cwd'],d)
            self.assertEqual((d/'f.c').read_text(),'int f(){return 1;}')

class OracleValidationTests(unittest.TestCase):
    def test_one_input_validation(self):
        for kind in ('refs','live','qty-refs','qty-life'):
            with self.assertRaises(ValueError):alloc_oracle.validate_change({'kind':kind,'value':0})
        for kind in ('local','qty-rank'):
            with self.assertRaises(ValueError):alloc_oracle.validate_change({'kind':kind,'value':-1})
        alloc_oracle.validate_change({'kind':'refs-add','value':2})
        alloc_oracle.validate_change({'kind':'global'})
    def test_pseudo_resolution_and_hard_register_refusal(self):
        with mock.patch('alloc_sim.decl_pseudos',return_value={'map':{'walker':81},'fname':'f'}):
            self.assertEqual(alloc_oracle.resolve_pseudo('', 'walker',76)[0],81)
            self.assertEqual(alloc_oracle.resolve_pseudo('', '369',76)[0],369)
            with self.assertRaises(ValueError):alloc_oracle.resolve_pseudo('', '4',76)
    def test_observed_oracle_target_beats_declaration_order(self):
        with mock.patch('alloc_sim.decl_pseudos',return_value={'map':{'walker':89},'fname':'f'}):
            self.assertEqual(alloc_oracle.resolve_pseudo('', 'walker',76,{'walker':90})[0],90)
            with self.assertRaises(ValueError):alloc_oracle.resolve_pseudo('', 'walker',76,{})
    def test_cli_refuses_multiple_interventions(self):
        with redirect_stdout(io.StringIO()),mock.patch('sys.stderr',io.StringIO()),self.assertRaises(SystemExit) as e:
            alloc_oracle.main(['row','erased','--pseudo','x','--refs','4','--qty-rank','0'])
        self.assertEqual(e.exception.code,2)

class GDBInputTests(unittest.TestCase):
    """Execute the GDB helper with a synthetic i386 inferior; inspect its exact writes."""
    def setUp(self):
        self.temp=tempfile.TemporaryDirectory();self.cwd=os.getcwd();os.chdir(self.temp.name)
        self.data=bytearray(32768);self.writes=[]
        names=list(alloc_oracle.REQUIRED);self.addr={n:0x100+4*i for i,n in enumerate(names)}
        self.arr={n:0x1000+0x180*i for i,n in enumerate(names)}
        for n,a in self.addr.items():self.data[a:a+4]=struct.pack('<I',self.arr[n])
        self.set_scalar('max_regno',81);self.set_scalar('next_qty',4)
        self.set_vec('reg_n_refs',80,27);self.set_vec('reg_live_length',80,168);self.set_vec('reg_basic_block',80,2)
        self.data[self.arr['reg_n_deaths']+160:self.arr['reg_n_deaths']+162]=struct.pack('<h',1)
        self.data[self.arr['current_function_name']:self.arr['current_function_name']+160]=b'f\0'+b'\0'*158
        self.set_vec('reg_qty',80,1);self.set_vec('qty_birth',1,4);self.set_vec('qty_death',1,8);self.set_vec('qty_n_refs',1,2)
        owner=self
        class Inferior:
            def read_memory(self,a,n):return bytes(owner.data[a:a+n])
            def write_memory(self,a,b):owner.writes.append((a,bytes(b)));owner.data[a:a+len(b)]=b
        class BP:
            def __init__(self,*a,**kw):pass
        fake=mock.Mock();fake.selected_inferior.return_value=Inferior();fake.Breakpoint=BP;fake.FinishBreakpoint=BP
        fake.newest_frame.return_value=None;fake.parse_and_eval.return_value=0;self.fake=fake
        Path('oracle_cfg.json').write_text(json.dumps({'addresses':self.addr,'pseudo':80,'first':76,'function':'f','change':None}))
        with mock.patch.dict(sys.modules,{'gdb':fake}):self.ns=runpy.run_path(str(KIT/'alloc_oracle_gdb.py'))
        self.gl=self.ns['patch_reg'].__globals__
    def tearDown(self):os.chdir(self.cwd);self.temp.cleanup()
    def set_scalar(self,n,v):self.data[self.addr[n]:self.addr[n]+4]=struct.pack('<i',v)
    def set_vec(self,n,i,v):self.data[self.arr[n]+4*i:self.arr[n]+4*i+4]=struct.pack('<i',v)
    def test_refs_changes_one_slot_exactly_once(self):
        self.gl['change']={'kind':'refs-add','value':2};self.ns['patch_reg']();self.ns['patch_reg']()
        self.assertEqual(self.writes,[(self.arr['reg_n_refs']+320,struct.pack('<i',29))])
        self.assertEqual(len(self.ns['result']['events']),1)
    def test_global_and_local_touch_only_block(self):
        self.gl['change']={'kind':'global'};self.ns['patch_reg']()
        self.assertEqual(self.writes,[(self.arr['reg_basic_block']+320,struct.pack('<i',-2))])
        self.ns['result']['applied']=False;self.writes.clear();self.gl['change']={'kind':'local','value':2};self.ns['patch_reg']()
        self.assertEqual(self.writes,[(self.arr['reg_basic_block']+320,struct.pack('<i',2))])
    def test_qty_life_changes_only_death_at_right_block(self):
        self.gl['current_block']=2;self.gl['change']={'kind':'qty-life','value':2};self.ns['patch_qty']();self.ns['patch_qty']()
        self.assertEqual(self.writes,[(self.arr['qty_death']+4,struct.pack('<i',6))])
        self.assertEqual(self.ns['result']['events'][0]['life'],2)
    def test_qty_rank_changes_only_order_vector_once(self):
        order_addr=0x7000
        self.data[order_addr:order_addr+16]=struct.pack('<4i',0,1,2,3)
        self.gl['current_block']=2;self.gl['change']={'kind':'qty-rank','value':0}
        self.gl['arg']=lambda i:{0:order_addr,1:4,3:self.addr['qty_compare_1']}[i]
        self.gl['Finish']=lambda fn:fn()
        self.ns['sort_entry']();self.ns['sort_entry']()
        self.assertEqual(self.writes,[(order_addr,struct.pack('<4i',1,0,2,3))])
        self.assertEqual(self.ns['result']['events'][0]['after'],[1,0,2,3])
    def test_qty_refs_does_not_change_pseudo_refs(self):
        self.gl['current_block']=2;self.gl['change']={'kind':'qty-refs','value':5};self.ns['patch_qty']()
        self.assertEqual(self.writes,[(self.arr['qty_n_refs']+4,struct.pack('<i',5))])
        self.assertEqual(self.ns['get']('reg_n_refs',80),27)
    def test_other_block_cannot_patch_stale_qty(self):
        self.gl['current_block']=1;self.gl['change']={'kind':'qty-refs','value':5};self.ns['patch_qty']()
        self.assertEqual(self.writes,[])
    def test_local_with_multiple_deaths_fails_without_write(self):
        self.data[self.arr['reg_n_deaths']+160:self.arr['reg_n_deaths']+162]=struct.pack('<h',2)
        self.gl['change']={'kind':'local','value':2}
        with self.assertRaises(ValueError):self.ns['patch_reg']()
        self.assertEqual(self.writes,[])

class ValueTests(unittest.TestCase):
    A='(insn 10 0 20 (set (reg:SI 4 a0) (reg:SI 80)) -1 (nil) (nil))\n'
    B='(insn 10 0 20 (set (reg:SI 4 a0) (const_int 12)) -1 (nil) (nil))\n'
    C='(call_insn 20 10 0 (call (mem:SI (symbol_ref:SI ("g"))) (const_int 0)) -1 (nil) (nil))\n'
    def test_cse_substitution_and_combine_attribution(self):
        ds={'rtl':self.A+self.C,'cse':self.B+self.C,'combine':self.B+self.C}
        hist=value_luid.transitions(ds,10)
        self.assertIn('cse substitution',hist[1]['event']);self.assertEqual(hist[2]['event'],'survives')
        hist=value_luid.transitions({'rtl':self.A,'cse':self.A,'combine':self.B},10)
        self.assertIn('combine merge',hist[-1]['event'])
    def test_self_copy_is_not_a_definition_and_label_stops_search(self):
        s=self.B+'(insn 11 10 20 (set (reg:SI 4 a0) (reg:SI 4 a0)) -1 (nil) (nil))\n'+self.C
        recs=value_luid.records(s);call=value_luid.select_call(recs,'g')
        self.assertEqual(value_luid.definitions(recs,4,call)[0]['uid'],10)
        s=self.B+'(code_label 12 10 20 7 "")\n'+self.C; recs=value_luid.records(s)
        self.assertEqual(value_luid.definitions(recs,4,value_luid.select_call(recs,'g')),[])
    def test_source_notes_and_named_pseudo_def(self):
        recs=value_luid.records('(note 1 0 10 ("f.c") 42)\n'+self.B)
        self.assertEqual(recs[1]['source'],{'file':'f.c','line':42})
        self.assertEqual(value_luid.definitions(recs,4)[0]['uid'],10)
    def test_named_pinned_value_resolves_to_hard_register(self):
        ds={'asm':'', 'sched':self.B+self.C, 'rtl':self.B+self.C}
        with mock.patch('alloc_sim.decl_pseudos',return_value={'map':{'sound':80},'fname':'f'}):
            view=value_luid.value_view({'cfg':'2.7.2-cdk-G0'},'register int sound ASM_REG("$4");',ds,'sound','g',source=False,observe=False)
        self.assertEqual(view['register'],4);self.assertEqual(view['definitions'][0]['uid'],10)
    def test_eliminated_named_pseudo_shows_removal_history(self):
        rtl=self.B.replace('4 a0','80')
        ds={'asm':'','rtl':rtl+self.C,'cse':self.C,'sched':self.C}
        with mock.patch('alloc_sim.decl_pseudos',return_value={'map':{'sound':80},'fname':'f'}):
            view=value_luid.value_view({'cfg':'2.7.2-cdk-G0'},'int sound;',ds,'sound',source=False,observe=False)
        self.assertTrue(view['eliminated_pseudo'])
        self.assertTrue(any('removed' in h['event'] for h in view['definitions'][0]['history']))
    def test_observed_decl_handles_union_and_binding_transition(self):
        observation={'declarations':[{'decl_address':1,'name':'sound','register':90},
                                      {'decl_address':1,'name':'sound','register':4},
                                      {'decl_address':2,'name':'other','register':91}]}
        mapping,ambiguous=value_luid.declaration_registers(observation)
        self.assertEqual(mapping['sound'],4);self.assertFalse(ambiguous)
        observation['declarations'].append({'decl_address':3,'name':'sound','register':92})
        mapping,ambiguous=value_luid.declaration_registers(observation)
        self.assertNotIn('sound',mapping);self.assertIn('sound',ambiguous)
    def test_observed_name_overrides_declaration_order_estimate(self):
        rtl=self.B.replace('4 a0','90')
        ds={'asm':'','rtl':rtl+self.C,'sched':rtl+self.C}
        observed={'blocks':[],'errors':[],'declarations':[{'decl_address':1,'name':'sound','register':90}]}
        with mock.patch('alloc_sim.decl_pseudos',return_value={'map':{'sound':89},'fname':'f'}),mock.patch('value_luid.observe_luids',return_value=observed):
            view=value_luid.value_view({'cfg':'2.7.2-cdk-G0'},'int sound;',ds,'sound',source=False)
        self.assertEqual(view['register'],90);self.assertEqual(view['resolution_evidence'],'observed DECL_RTL in cc1')
    def test_reference_with_helper_selects_row_function(self):
        with mock.patch('alloc_sim.decl_pseudos',return_value=None),mock.patch('alloc_sim.functions',return_value=[('helper',None),('f',None)]):
            self.assertEqual(value_luid.main_function_name({'true_name':'f'},'',76),'f')
            with self.assertRaises(ValueError):value_luid.main_function_name({'true_name':'missing'},'',76)
    def test_helper_dump_uid_collision_is_scoped(self):
        ds={'rtl':';; Function helper\n'+self.A+';; Function f\n'+self.B,'asm':'all functions'}
        selected=value_luid.function_dumps(ds,'f')
        self.assertNotIn('helper',selected['rtl']);self.assertIn('const_int 12',selected['rtl'])
        self.assertEqual(selected['asm'],'all functions')
    def test_block_uid_without_priority_and_uid_not_order(self):
        blocks=[{'n':2,'from':10,'to':20,'prio':{10:(1,1)},'ticks':[]}]
        self.assertEqual(why.resolve_block(blocks,'20')[0]['n'],2)
        self.assertEqual(why.resolve_block(blocks,'u300',chain=[{'uid':10},{'uid':300},{'uid':20}])[0]['n'],2)
        self.assertEqual(why.resolve_block(blocks,'b2')[0]['n'],2)

class TidyTests(unittest.TestCase):
    ROW={'id':'dungeon/f','container':'dungeon','func':'f','c_path':'src/dungeon/f.c','cfg':'2.7.2-cdk-G0','kind':'overlay'}
    BASE='void f(){int x; ASM_KEEP(x); g(x);}\n';CAND='/* readable */\n'+BASE
    def run_tidy(self,cand,exact=True):
        with tempfile.TemporaryDirectory() as td:
            p=Path(td)/'f.c';p.write_text(self.BASE)
            with mock.patch('kitlib.score_at',return_value={'exact':exact,'total':0 if exact else 1,'status':'ok'}) as score,redirect_stdout(io.StringIO()):
                r=lab.stage_tidy(self.ROW,cand,'tidy',td,p,self.BASE)
            copied=Path(td)/'out/dungeon/f.c'
            return r,score.call_args,copied.read_text() if copied.exists() else None,(Path(td)/'cells.jsonl').exists()
    def test_exact_equal_pins_registered_cfg_no_recipe_record(self):
        r,call,copied,cells=self.run_tidy(self.CAND)
        self.assertEqual(r['status'],'exact');self.assertEqual(copied,self.CAND);self.assertFalse(cells)
        self.assertEqual(call.args[0]['cfg'],self.ROW['cfg']);self.assertEqual(r['pins'],r['pins_before'])
    def test_nonexact_and_pin_growth_and_reduction_refused(self):
        self.assertIn('refused',self.run_tidy(self.CAND,False)[0])
        for cand in (self.CAND.replace('ASM_KEEP(x);',''),self.CAND.replace('g(x);','ASM_KEEP(x); g(x);')):
            r,call,copied,_=self.run_tidy(cand)
            self.assertIn('refused',r);self.assertIsNone(call);self.assertIsNone(copied)
    def test_added_volatile_refused_without_score(self):
        r,call,copied,_=self.run_tidy(self.CAND.replace('int x','volatile int x'))
        self.assertIn('refused',r);self.assertIsNone(call)

if __name__=='__main__':unittest.main()
