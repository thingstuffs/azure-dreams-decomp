"""Context-oracle fixtures. No live tree, compiler, git, or game files are used."""
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
import unittest

P = Path(__file__).resolve().parents[1]/'lanes/lanekit/context_oracle.py'
SPEC = importlib.util.spec_from_file_location('context_oracle',P)
O = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = O
SPEC.loader.exec_module(O)

BASE = 0x80010000

def r(rs,rt,rd,fn,sh=0):
    return rs<<21 | rt<<16 | rd<<11 | sh<<6 | fn

def imm(op,rs,rt,k):
    return op<<26 | rs<<21 | rt<<16 | k&65535

def jal(addr):
    return 3<<26 | addr>>2&0x03ffffff

def ret():
    return [r(31,0,0,8),0]

class RetailFlow(unittest.TestCase):
    def test_delay_argument_and_entry_provenance(self):
        a=O.analyse([jal(BASE+0x400),r(0,6,18,33),r(0,18,6,33),r(8,0,31,9),0,*ret()],BASE)
        self.assertEqual(a['entry_reads']['a2'],[O.hx(BASE+4)])
        self.assertIn('entry:a2',a['calls'][1]['values'][2].origins)
        self.assertTrue(a['calls'][1]['values'][2].written)

    def test_jalr_target_sampled_before_delay(self):
        a=O.analyse([imm(15,0,8,0x8001),imm(13,8,8,0x1000),r(8,0,31,9),imm(9,0,8,0),*ret()],BASE)
        self.assertEqual(a['calls'][0]['target_value'].const,0x80011000)

    def test_prior_call_clobbers_arguments(self):
        a=O.analyse([jal(BASE+0x400),0,r(0,6,8,33),*ret()],BASE)
        self.assertNotIn('a2',a['entry_reads'])

    def test_load_delay_exposes_old_entry_register(self):
        a=O.analyse([imm(35,4,6,0),r(0,6,8,33),r(0,6,9,33),*ret()],BASE)
        self.assertEqual(a['entry_reads']['a2'],[O.hx(BASE+4)])

    def test_load_delay_reaches_call_after_slot(self):
        a=O.analyse([imm(33,4,6,2),jal(BASE+0x400),0,*ret()],BASE)
        self.assertEqual(a['calls'][0]['values'][2].width,'signed16-promoted')

    def test_stack_spill_restores_entry_after_call(self):
        a=O.analyse([imm(9,29,29,-32),imm(43,29,6,24),jal(BASE+0x400),0,
                     imm(35,29,6,24),0,jal(BASE+0x500),0,*ret()],BASE)
        self.assertIn('entry:a2',a['calls'][1]['values'][2].origins)

    def test_branch_arm_entry_read_is_visible(self):
        a=O.analyse([imm(4,4,0,3),0,imm(9,0,5,1),imm(4,0,0,1),0,r(0,5,8,33),*ret()],BASE)
        self.assertIn('a1',a['entry_reads'])
        self.assertTrue(a['converged'])

    def test_unreachable_read_ignored(self):
        a=O.analyse([*ret(),r(0,7,8,33)],BASE)
        self.assertNotIn('a3',a['entry_reads'])

    def test_v0_v1_read_before_definition(self):
        a=O.analyse([r(2,3,8,33),*ret()],BASE)
        self.assertEqual(set(a['entry_reads']),{'v0','v1'})

    def test_entry_read_in_own_write_counts(self):
        a=O.analyse([imm(9,5,5,1),*ret()],BASE)
        self.assertIn('a1',a['entry_reads'])

    def test_result_consumed_and_void_ignored_are_distinct(self):
        a=O.analyse([jal(BASE+0x400),0,r(2,0,16,33),jal(BASE+0x500),0,*ret()],BASE)
        self.assertTrue(a['calls'][0]['return_consumed'])
        self.assertFalse(a['calls'][1]['return_consumed'])

    def test_stack_fifth_argument(self):
        a=O.analyse([imm(9,29,29,-32),imm(9,0,8,7),imm(43,29,8,16),jal(BASE+0x400),0,*ret()],BASE)
        self.assertEqual(a['calls'][0]['stack_values'][16].const,7)

    def test_width_extension(self):
        a=O.analyse([imm(33,4,5,2),0,r(0,5,6,0,16),r(0,6,6,3,16),jal(BASE+0x400),0,*ret()],BASE)
        self.assertEqual(a['calls'][0]['values'][1].width,'signed16-promoted')
        self.assertEqual(a['calls'][0]['values'][2].width,'signed16-promoted')

    def test_unknown_opcode_is_coverage_gap(self):
        a=O.analyse([0xfc000000,*ret()],BASE)
        self.assertEqual(a['unknown_instructions'],[O.hx(BASE)])

    def test_prepared_unknown_value_survives_join(self):
        a=O.join(O.Val('x'),O.Val('y'))
        self.assertEqual(a.term,'?');self.assertTrue(a.prepared)
        b=O.join(a,O.Val('call-clobbered',prepared=False))
        self.assertFalse(b.prepared)

    def test_indirect_tail_dispatch_is_retained(self):
        a=O.analyse([r(8,0,0,8),r(0,6,5,33),*ret()],BASE)
        self.assertEqual(len(a['calls']),1);self.assertTrue(a['calls'][0]['tail_dispatch'])
        self.assertIn('entry:a2',a['calls'][0]['values'][1].origins)

    def test_external_direct_tail_dispatch_is_retained(self):
        a=O.analyse([2<<26 | (BASE+0x400)>>2&0x03ffffff,0],BASE)
        self.assertEqual(a['calls'][0]['target'],BASE+0x400)
        self.assertTrue(a['calls'][0]['tail_dispatch'])

    def test_paired_unaligned_load_seed_is_qualified(self):
        a=O.analyse([imm(34,4,6,3),imm(38,4,6,0),0,*ret()],BASE)
        self.assertIn('a2',a['entry_reads']);self.assertIn('a2',a['merge_seed_entry_reads'])

    def test_branch_into_second_load_is_not_qualified(self):
        a=O.analyse([imm(4,5,0,2),0,imm(34,4,6,3),imm(38,4,6,0),0,*ret()],BASE)
        self.assertNotIn('a2',a['merge_seed_entry_reads'])

    def test_unpaired_partial_load_keeps_old_origin(self):
        a=O.analyse([imm(34,4,6,3),0,jal(BASE+0x400),0,*ret()],BASE)
        self.assertIn('entry:a2',a['calls'][0]['values'][2].origins)

    def test_load_delay_consumer_prevents_seed_qualification(self):
        a=O.analyse([imm(34,4,6,3),imm(38,4,6,0),r(6,0,8,33),*ret()],BASE)
        self.assertNotIn('a2',a['merge_seed_entry_reads'])

class LexicalC(unittest.TestCase):
    def test_void_vs_unspecified(self):
        s=O.signatures('extern int f();\nvoid g(void) {}\nint h(int a, void *b) { return a; }')
        self.assertEqual([(x['name'],x['arity']) for x in s],[('f',None),('g',0),('h',2)])

    def test_nested_calls_comments_strings(self):
        t='extern int f(int, int);\nint g(void) { /* f(1) */ return f(h(1,2), (int[]){1,2}[0]); }'
        s=O.signatures(t); calls=O.c_calls(t,s)
        self.assertEqual([(c['callee'],c['arity']) for c in calls],[('f',2),('h',2)])

    def use_of(self,body,callee='f'):
        t='extern void f(void);\nvoid g(int a, int b, int x) { '+body+' }'
        calls=[c for c in O.c_calls(t,O.signatures(t)) if c['callee']==callee]
        self.assertEqual(len(calls),1,body)
        return calls[0]['use']

    def test_labels_are_not_value_uses(self):
        self.assertEqual(self.use_of('switch (a) { case 1: f(); break; }'),'ignored')
        self.assertEqual(self.use_of('switch (a) { case 1: case 2: f(); break; }'),'ignored')
        self.assertEqual(self.use_of('switch (a) { case (b ? 1 : 2): f(); }'),'ignored')
        self.assertEqual(self.use_of('switch (a) { default: f(); }'),'ignored')
        self.assertEqual(self.use_of('switch (a) { case 1: x = 2; break; default : f(); }'),'ignored')
        self.assertEqual(self.use_of('goto out; out: f();'),'ignored')
        self.assertEqual(self.use_of('if (a) { b = 1; } f();'),'ignored')

    def test_control_heads_are_not_value_uses(self):
        self.assertEqual(self.use_of('if (a) f();'),'ignored')
        self.assertEqual(self.use_of('if (a) b = 1; else f();'),'ignored')
        self.assertEqual(self.use_of('while (a) f();'),'ignored')
        self.assertEqual(self.use_of('for (a = 0; a < b; a++) f();'),'ignored')

    def test_value_uses_survive_labels_and_ternaries(self):
        self.assertEqual(self.use_of('x = f();'),'value')
        self.assertEqual(self.use_of('switch (a) { case 1: x = f(); }'),'value')
        self.assertEqual(self.use_of('switch (a) { case 1: return f(); }'),'value')
        self.assertEqual(self.use_of('x = a ? b : f();'),'value')
        self.assertEqual(self.use_of('a ? b : f();'),'value')
        self.assertEqual(self.use_of('return a ? b : f();'),'value')
        self.assertEqual(self.use_of('switch (a) { case 1: a ? b : f(); }'),'value')
        self.assertEqual(self.use_of('x = a ? (b ? 1 : 2) : f();'),'value')
        self.assertEqual(self.use_of('if (f()) b = 1;'),'value')
        self.assertEqual(self.use_of('(void) f();'),'ignored')

    def test_noreturn_attribute(self):
        s=O.signatures('extern void die(void) __attribute__((noreturn));\nvoid g(void) { die(); }')
        self.assertTrue(s[0]['noreturn'])
        self.assertEqual(len(O.c_calls('extern void die(void) __attribute__((noreturn));\nvoid g(void) { die(); }',s)),1)

    def test_variadic(self):
        s=O.signatures('int printf(const char *fmt, ...);')[0]
        self.assertEqual(s['arity'],1);self.assertTrue(s['variadic'])

class PackageFixture(unittest.TestCase):
    def setUp(self):
        self.temp=tempfile.TemporaryDirectory();self.root=Path(self.temp.name)
        self.addCleanup(self.temp.cleanup)
        self.words=[0]*512;self.functions=[]

    def function(self,off,name,words,source,row=None,container='test'):
        self.words[off//4:off//4+len(words)]=words
        path=f'{name}.c';(self.root/path).write_text(source)
        self.functions.append({'row':row or 'test/'+name,'container':container,
                               'name':name,'address':BASE+off,'foff':off,
                               'size':len(words)*4,'source':path})

    def finish(self,extra=None):
        (self.root/'test.bin').write_bytes(struct.pack('<'+'I'*len(self.words),*self.words))
        doc={'images':[{'container':'test','file':'test.bin'}],'functions':self.functions,
             'mappings':[{'container':'test','start':0,'end':2048,'delta':BASE}]}
        doc.update(extra or {});p=self.root/'fixture.json';p.write_text(json.dumps(doc))
        return O.Oracle(self.root,p)

    def setup_callback(self):
        callback=BASE+0x100;registrar=BASE+0x200;table=BASE+0x600
        self.function(0x100,'func_80010100',ret(),'int func_80010100(void *p) { return 0; }')
        self.function(0x200,'func_80010200',[imm(15,0,8,0x8001),imm(43,8,5,0x600),*ret()],
                      'void func_80010200(void *p, int cb) {}')
        self.function(0x300,'func_80010300',[imm(15,0,5,0x8001),imm(13,5,5,0x100),jal(registrar),0,*ret()],
                      'void func_80010200(void *, int);\nvoid func_80010300(void) {func_80010200(0, 0x80010100);}')
        self.function(0x400,'func_80010400',[imm(15,0,8,0x8001),imm(35,8,25,0x600),
                      imm(9,0,4,1),imm(9,0,5,2),r(25,0,31,9),imm(9,0,6,3),*ret()],
                      'void func_80010400(void) { }')
        return callback,table

    def test_three_arg_registered_callback(self):
        callback,table=self.setup_callback();o=self.finish();f=o.resolve('test/func_80010100')[0]
        reach=o.reach(f)
        self.assertEqual(reach['inferred_true_signature']['callback_convention_arities'],[3])
        self.assertEqual(reach['registration_calls'][0]['classification'],'retail argument-to-slot store')
        self.assertEqual(reach['dispatch_contexts'][0]['dispatcher']['argument_registers']['a2']['value'],'0x00000003')

    def test_callback_in_a3_is_not_extra_argument_evidence(self):
        self.setup_callback()
        self.function(0x500,'func_80010500',[imm(15,0,8,0x8001),imm(35,8,7,0x600),
                      imm(9,0,4,1),imm(9,0,5,2),r(7,0,31,9),imm(9,0,6,3),*ret()],
                      'void func_80010500(void) {}')
        o=self.finish();reach=o.reach(o.resolve('test/func_80010100')[0])
        self.assertEqual(reach['inferred_true_signature']['callback_convention_arities'],[3])
        record=next(x for x in reach['dispatch_contexts'] if x['dispatcher']['caller']=='test/func_80010500')['dispatcher']
        self.assertEqual(record['argument_target_overlap'],'a3')

    def test_target_delay_overwrite_can_prepare_fourth_argument(self):
        self.setup_callback()
        self.function(0x500,'func_80010500',[imm(15,0,8,0x8001),imm(35,8,7,0x600),
                      imm(9,0,4,1),imm(9,0,5,2),imm(9,0,6,3),r(7,0,31,9),imm(9,0,7,4),*ret()],
                      'void func_80010500(void) {}')
        o=self.finish();reach=o.reach(o.resolve('test/func_80010100')[0])
        record=next(x for x in reach['dispatch_contexts'] if x['dispatcher']['caller']=='test/func_80010500')['dispatcher']
        self.assertIsNone(record['argument_target_overlap'])
        self.assertIn(4,reach['inferred_true_signature']['callback_convention_arities'])

    def test_data_word_table_dispatch_and_script_verification(self):
        callback,table=self.setup_callback();self.words[0x600//4]=callback
        o=self.finish({'script_tables':[{'container':'test','foff':0x600,'entries':[callback]}]})
        reach=o.reach(o.resolve('test/func_80010100')[0])
        self.assertEqual(len(reach['address_words']),1)
        self.assertTrue(reach['script_call_table_entries'][0]['retail_word_verified'])
        self.assertTrue(any('data table' in d['route'] for d in reach['dispatch_contexts']))

    def test_script_metadata_cannot_override_retail(self):
        callback,_=self.setup_callback()
        o=self.finish({'script_tables':[{'container':'test','foff':0x600,'entries':[callback]}]})
        self.assertFalse(o.reach(o.resolve('test/func_80010100')[0])['script_call_table_entries'][0]['retail_word_verified'])

    def test_cross_container_address_words(self):
        callback,_=self.setup_callback()
        (self.root/'other.bin').write_bytes(struct.pack('<II',callback,callback))
        o=self.finish({'images':[{'container':'test','file':'test.bin'},{'container':'other','file':'other.bin'}]})
        self.assertEqual(len(o.reach(o.resolve('test/func_80010100')[0])['address_words']),2)

    def test_four_vs_one_arity_and_unspecified_prototype(self):
        target=BASE+0x100
        self.function(0x100,'func_80010100',ret(),'int func_80010100(int angle) { return 0; }')
        self.function(0x200,'func_80010200',[imm(9,0,4,1),imm(9,0,5,2),imm(9,0,6,3),jal(target),imm(9,0,7,4),*ret()],
                      'int func_80010100();\nvoid func_80010200(void) { func_80010100(1,2,3,4); }')
        self.function(0x300,'func_80010300',[imm(9,0,4,1),jal(target),0,*ret()],
                      'int func_80010100(int);\nvoid func_80010300(void) { func_80010100(1); }')
        o=self.finish();report=o.callsites(o.resolve('test/func_80010100'))[0]
        self.assertEqual(report['observed_c_arities'],[1,4]);self.assertTrue(report['arity_disagreement'])
        flags=report['callsites'][0]['flags']
        self.assertIn('call_vs_definition_arity',flags)
        self.assertIn('unspecified_prototype_default_promotions',flags)

    def test_two_vs_three_definition(self):
        target=BASE+0x100
        self.function(0x100,'func_80010100',ret(),'int func_80010100(int a, int b, int c) { return 0; }')
        self.function(0x200,'func_80010200',[jal(target),0,*ret()],
                      'int func_80010100(int, int);\nvoid func_80010200(int a, int b) { func_80010100(a,b); }')
        o=self.finish();self.assertIn('call_vs_definition_arity',o.callsites(o.resolve('test/func_80010100'))[0]['callsites'][0]['flags'])

    def test_hidden_argument_and_xrefs(self):
        self.function(0x100,'func_80010100',[r(5,6,8,33),*ret()],
                      'int func_80010100(M2C_UNK a) { volatile int x; ASM_REG(int, y, "$a2"); return 0; }')
        o=self.finish();entry=o.entry(o.resolve('test/func_80010100')[0])
        self.assertEqual(entry['beyond_declared_params'],['a1','a2'])
        self.assertEqual(entry['cross_references']['argument_reg_pins'],['a2'])
        self.assertTrue(entry['cross_references']['volatile']);self.assertTrue(entry['cross_references']['m2c_unk_params'])

    def test_same_address_bank_candidates_are_retained(self):
        self.function(0x100,'func_80010100',ret(),'int func_80010100(void) { return 0; }')
        o=self.finish();o.add('other/func_80010100','test','func_80010100',BASE+0x100,0x100,8,'func_80010100.c')
        self.assertEqual(len(o.resolve('func_80010100')),2)
        self.assertIn('other/func_80010100',o.reach(o.resolve('test/func_80010100')[0])['ambiguity']['same_address_candidates'])

    def test_void_and_noreturn_conflicts(self):
        target=BASE+0x100
        self.function(0x100,'func_80010100',ret(),'void func_80010100(void) __attribute__((noreturn)) {}')
        self.function(0x200,'func_80010200',[jal(target),0,r(2,0,16,33),*ret()],
                      'int func_80010100(void);\nint func_80010200(void) { return func_80010100(); }')
        o=self.finish();flags=o.callsites(o.resolve('test/func_80010100'))[0]['callsites'][0]['flags']
        self.assertIn('void_definition_value_used',flags);self.assertIn('noreturn_definition_has_retail_continuation',flags)

    def test_include_closure_prototype(self):
        (self.root/'include').mkdir();(self.root/'include/proto.h').write_text('extern int func_80010100(int);')
        self.function(0x100,'func_80010100',ret(),'int func_80010100(int a) { return 0; }')
        self.function(0x200,'func_80010200',[jal(BASE+0x100),0,*ret()],
                      '#include "proto.h"\nvoid func_80010200(void) { func_80010100(1); }')
        o=self.finish();rec=o.callsites(o.resolve('test/func_80010100'))[0]['callsites'][0]
        self.assertEqual(rec['local_prototypes'][0]['arity'],1)

    def test_extern_void_matches_static_void(self):
        self.function(0x100,'func_80010100',ret(),'static void func_80010100(void) {}')
        self.function(0x200,'func_80010200',[jal(BASE+0x100),0,*ret()],
                      'extern void func_80010100(void);\nvoid func_80010200(void) { func_80010100(); }')
        o=self.finish();flags=o.callsites(o.resolve('test/func_80010100'))[0]['callsites'][0]['flags']
        self.assertNotIn('void_value_return_type_disagreement',flags)

    def test_void_pointer_is_a_value_return(self):
        self.function(0x100,'func_80010100',ret(),'void *func_80010100(void) { return 0; }')
        self.function(0x200,'func_80010200',[jal(BASE+0x100),0,r(2,0,16,33),*ret()],
                      'extern void *func_80010100(void);\nvoid *func_80010200(void) { return func_80010100(); }')
        o=self.finish();flags=o.callsites(o.resolve('test/func_80010100'))[0]['callsites'][0]['flags']
        self.assertNotIn('void_definition_value_used',flags)
        self.assertNotIn('void_value_return_type_disagreement',flags)

    def test_cli_and_csv_markdown_census(self):
        self.setup_callback();o=self.finish();census=o.census()
        self.assertIn('row,function,score',O.render_census(census,'csv'))
        self.assertIn('# Context census',O.render_census(census,'md'))
        result=subprocess.run([sys.executable,'-B',str(P),'--root',str(self.root),'--manifest',str(self.root/'fixture.json'),
                               'reach','test/func_80010100'],capture_output=True,text=True)
        self.assertEqual(result.returncode,0,result.stderr)
        self.assertEqual(json.loads(result.stdout)['results'][0]['inferred_true_signature']['callback_convention_arities'],[3])

    def test_census_includes_callback_convention_mismatch(self):
        self.setup_callback();o=self.finish();c=o.census()
        row=next(r for r in c['rows'] if r['row']=='test/func_80010100')
        self.assertIn('callback_convention_exceeds_declared_params',row['flags'])
        self.assertEqual(c['counts']['callback_convention_mismatch_rows'],1)

    def test_merge_seed_does_not_claim_hidden_parameter(self):
        self.function(0x100,'func_80010100',[imm(34,4,6,3),imm(38,4,6,0),0,*ret()],
                      'int func_80010100(void *p) { return 0; }')
        o=self.finish();e=o.entry(o.resolve('test/func_80010100')[0])
        self.assertIn('a2',e['reads_before_write']);self.assertNotIn('a2',e['beyond_declared_params'])

    def test_variadic_entry_reads_are_permitted(self):
        self.function(0x100,'func_80010100',[r(5,6,8,33),*ret()],
                      'int func_80010100(int fmt, ...) { return 0; }')
        o=self.finish();e=o.entry(o.resolve('test/func_80010100')[0])
        self.assertEqual(e['beyond_declared_params'],[]);self.assertEqual(e['parameter_layout'],'variadic')

    def test_wide_abi_layout_remains_unresolved(self):
        self.function(0x100,'func_80010100',[r(5,6,8,33),*ret()],
                      'int func_80010100(double x) { return 0; }')
        o=self.finish();e=o.entry(o.resolve('test/func_80010100')[0])
        self.assertEqual(e['beyond_declared_params'],[]);self.assertIn('wide_parameter_abi_layout_unresolved',e['flags'])

    def test_proven_rowbase_supersedes_synthetic_row_name(self):
        path=self.root/'work/disc/containers';path.mkdir(parents=True)
        data=bytearray(1024);struct.pack_into('<II',data,0x100,*ret())
        (path/'TOWN_TOWN.BIN').write_bytes(data)
        path=self.root/'src/town';path.mkdir(parents=True)
        (path/'func_90000000.c').write_text('int func_80010100(void) { return 0; }')
        path=self.root/'ledger';path.mkdir()
        (path/'rows.jsonl').write_text(json.dumps({'id':'town/func_90000000','func':'func_90000000','container':'town',
             'foff':256,'size':8,'c_path':'src/town/func_90000000.c'})+'\n')
        path=self.root/'config/overlays';path.mkdir(parents=True)
        (path/'town.rowbase.jsonl').write_text(json.dumps({'foff_start':256,'foff_end':264,
             'delta':BASE,'base_confidence':'proven'})+'\n')
        o=O.Oracle(self.root);f=o.resolve('town/func_90000000')[0]
        self.assertEqual(f['address'],BASE+256);self.assertEqual(f['name'],'func_80010100')
        self.assertEqual(f['signature']['arity'],0)

    def test_native_data_prefix_is_not_executed_as_entry_code(self):
        path=self.root/'work/disc/containers';path.mkdir(parents=True)
        data=bytearray(1024);struct.pack_into('<III',data,256,r(2,4,2,33),*ret())
        (path/'DUNGEON_DUNGEON.BIN').write_bytes(data)
        path=self.root/'src/dungeon';path.mkdir(parents=True)
        (path/'func_90000000.c').write_text('int func_80010104(void) { return 0; }')
        path=self.root/'ledger';path.mkdir()
        (path/'rows.jsonl').write_text(json.dumps({'id':'dungeon/func_90000000','func':'func_90000000','container':'dungeon',
             'foff':256,'size':12,'c_path':'src/dungeon/func_90000000.c'})+'\n')
        path=self.root/'config/overlays';path.mkdir(parents=True)
        (path/'modules.json').write_text(json.dumps({'modules':[{'members':[{
             'id':'dungeon/func_90000000','function':'func_80010104','source':'src/dungeon/func_90000000.c',
             'foff':256,'vma':BASE+256,'size':12,'body_offset':4}]}]}))
        o=O.Oracle(self.root);f=o.resolve('dungeon/func_90000000')[0]
        self.assertEqual(f['foff'],260);self.assertEqual(f['address'],BASE+260)
        self.assertEqual(f['signature']['arity'],0)
        self.assertNotIn('v0',o.entry(f)['reads_before_write'])

if __name__=='__main__':
    unittest.main()
