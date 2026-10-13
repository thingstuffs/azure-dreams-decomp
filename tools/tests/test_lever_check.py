"""Requirement fixtures: source evidence, owner exceptions, batch and lab staging."""
import importlib.util
import io
import json
from pathlib import Path
import tempfile
import unittest
from contextlib import redirect_stdout,redirect_stderr
import sys
ROOT=Path(__file__).resolve().parents[2]
KIT=ROOT/'tools/lanes/lanekit'
sys.path.insert(0,str(KIT))
import lever_check as L

class SourceFixtures(unittest.TestCase):
 def check(self,candidate,base='void f(void) {}'):
  return L.analyze(base,candidate,'fixture/f')
 def flags(self,result,severity='REFUSE-LIKELY'):
  return {f['code'] for f in result['flags'] if f['severity']==severity}
 def test_float_union_launder(self):
  r=self.check('void f(void *p) { union {void *pointer; float bits;} x; x.pointer=p; use(x.bits); }')
  self.assertIn('UNION-LAUNDER',self.flags(r));self.assertTrue(all(f['line']>0 and f['evidence'] for f in r['flags']))
 def test_whole_constructor_changes_the_active_union_member(self):
  r=self.check('typedef union {int integer; void *pointer;} Value; void f(void *p) { Value work; work.integer=3; use(work.integer); work=(Value){.pointer=p}; use(work.pointer); }','void f(void *p) {}')
  self.assertNotIn('UNION-LAUNDER',self.flags(r))
 def test_member_write_evaluates_rhs_before_changing_active_member(self):
  r=self.check('void f(void) { union {int integer; float floating;} value; value.integer=3; value.floating=value.integer; use(value.floating); }')
  self.assertNotIn('UNION-LAUNDER',self.flags(r))
 def test_repeated_constructor_readbacks_are_their_own_lever(self):
  r=self.check('typedef union {int integer; void *pointer;} Value; void f(void *p) { Value work; void *copy; int result; work=(Value){.pointer=p}; copy=work.pointer; use(copy); work=(Value){1}; result=work.integer; use(result); }','void f(void *p) {}')
  self.assertIn('UNION-CONSTRUCTOR-COPY',self.flags(r));self.assertNotIn('UNION-LAUNDER',self.flags(r))
 def test_existing_literal_is_info_when_the_carrier_changes(self):
  base='void f(void) { unsigned char *page=(unsigned char*)0x80010000;use(page[4]);page[8]=2; }'
  r=self.check('void f(void) { use(*(short*)0x80010000); }',base)
  self.assertNotIn('LITERAL-ADDRESS',self.flags(r));self.assertIn('LITERAL-ADDRESS',self.flags(r,'INFO'))
 def test_float_double_width_member(self):
  r=self.check('void f(void *p) { union {float bits; void *pointer; double width;} x={0}; use(x.pointer); }')
  self.assertIn('UNREAD-MEMBER',self.flags(r))
 def test_zero_one_member_union(self):
  r=self.check('void f(void) { union {int value;} x={0}; x.value=3; use(x.value); }')
  self.assertFalse(self.flags(r));self.assertFalse(self.flags(r,'REVIEW'));self.assertIn('ZERO-UNION',self.flags(r,'INFO'))
 def test_bare_one_member_union(self):
  r=self.check('void f(void) { union {int value;} x; x.value=3; use(x.value); }')
  self.assertIn('UNION-CARRIER',self.flags(r))
 def test_partial_write_dead_union(self):
  r=self.check('void f(void) { register union {int whole; struct {short low; short high;} half;} x; x.whole=read_timer(); x.half.high=4; use(x.half.high); }')
  self.assertIn('UNION-PARTIAL',self.flags(r))
 def test_single_use_copy_to_reused_host(self):
  r=self.check('void f(void) { int host; int copy; host=2; use(host); copy=value; host=copy; use(host); }')
  self.assertIn('STEERING-COPY',self.flags(r))
 def test_field_address_is_real_view(self):
  r=self.check('void f(void *output) { unsigned short *slot=&output->x; *slot=7; }','void f(void *output) {}')
  self.assertFalse(self.flags(r));self.assertFalse(self.flags(r,'REVIEW'))
 def test_byte_snapshot_into_halfword_is_real_typed_value(self):
  r=self.check('void f(void) { short coord; unsigned char sprite_u; coord=2;use(coord);sprite_u=*(unsigned char*)sprite;coord=sprite_u;use(coord); }')
  self.assertNotIn('STEERING-COPY',self.flags(r))
 def test_tagged_typedef_is_unused_despite_two_declaration_tokens(self):
  r=self.check('typedef struct Spare { int field; } Spare; void f(void) {}')
  self.assertIn('UNUSED-TYPEDEF',self.flags(r))
 def test_pointer_lvalue_reads_the_address(self):
  r=self.check('void f(void) { int *address; address=other; *(int*)address=4; }')
  self.assertNotIn('UNUSED-LOCAL',self.flags(r));self.assertNotIn('DEAD-VALUE',self.flags(r))
 def test_switch_case_values_not_dead_overwrites(self):
  r=self.check('void f(int condition) { int value; switch(condition) {case 1:value=2;break;default:value=3;break;}use(value); }','void f(int condition) {}')
  self.assertNotIn('DEAD-VALUE',self.flags(r))
 def test_pointer_integer_readback(self):
  r=self.check('void f(void *p) { int carrier=(int)p; use((void*)carrier); }','void f(void *p) {}')
  self.assertIn('POINTER-INT-LAUNDER',self.flags(r))
 def test_reused_integer_true_roles(self):
  r=self.check('void f(void *p) { int work; work=2; use(work); work=(int)p; use((void*)work); }','void f(void *p) {}')
  self.assertNotIn('POINTER-INT-LAUNDER',self.flags(r))
 def test_dead_overwrite(self):
  r=self.check('void f(void) { int value; value=3; value=4; use(value); }')
  self.assertIn('DEAD-VALUE',self.flags(r))
 def test_control_flow_overwrites_are_not_dead(self):
  r=self.check('void f(int cond) { int value; if(cond){value=3;}else{value=4;} use(value); }','void f(int cond) {}')
  self.assertNotIn('DEAD-VALUE',self.flags(r))
 def test_repeated_store(self):
  r=self.check('void f(void *p) { p->x=3; p->y=4; p->x=3; }','void f(void *p) { p->x=3; p->y=4; }')
  self.assertIn('REPEATED-STORE',self.flags(r))
 def test_store_overwritten_without_read(self):
  r=self.check('void f(void *p) { p->x=3; p->x=4; }','void f(void *p) { p->x=4; }')
  self.assertIn('DEAD-STORE',self.flags(r))
 def test_intervening_memory_read_prevents_dead_store_flag(self):
  r=self.check('void f(void *p) { p->x=3; int saved=p->x; p->x=4; use(saved); }','void f(void *p) {}')
  self.assertNotIn('DEAD-STORE',self.flags(r))
 def test_volatile_pointer_stores_not_assumed_dead(self):
  r=self.check('void f(void) { volatile int *p=address; *p=3; *p=4; }')
  self.assertNotIn('DEAD-STORE',self.flags(r))
 def test_repeated_volatile_pointer_stores_not_assumed_deleted(self):
  r=self.check('void f(void) { volatile int *p=address; *p=3; *p=3; }')
  self.assertNotIn('REPEATED-STORE',self.flags(r));self.assertNotIn('DEAD-STORE',self.flags(r))
 def test_discarded_arithmetic_value(self):
  r=self.check('void f(void) { x + y; }')
  self.assertIn('DISCARDED-VALUE',self.flags(r))
 def test_void_marker_is_not_a_fake_dependency(self):
  r=self.check('void f(int parameter) { (void)parameter; }','void f(int parameter) {}')
  self.assertNotIn('DISCARDED-VALUE',self.flags(r))
 def test_union_passed_whole_cannot_prove_unread_members(self):
  r=self.check('void f(void) { union {int integer; char bytes[4];} value; value.integer=3; consume(value); }')
  self.assertNotIn('UNREAD-MEMBER',self.flags(r));self.assertIn('UNION-SHAPE',self.flags(r,'REVIEW'))
 def test_self_assignment(self):
  r=self.check('void f(void *p) { p->x=p->x; }','void f(void *p) {}')
  self.assertIn('SELF-ASSIGN',self.flags(r))
 def test_read_then_writeback(self):
  r=self.check('void f(void *p) { int value=p->x; p->x=value; }','void f(void *p) {}')
  self.assertIn('READ-WRITEBACK',self.flags(r))
 def test_decision39_writeback_pending_receipt(self):
  r=self.check('void f(void *p) { /* decision 39: retail reads x */ p->x=p->x; }','void f(void *p) {}')
  self.assertNotIn('SELF-ASSIGN',self.flags(r));self.assertIn('SELF-ASSIGN',self.flags(r,'INFO'))
 def test_fake_cancel(self):
  for expr in ['x ^ x','x - x','x + y - y']:
   with self.subTest(expr=expr):
    r=self.check('void f(void) { int result; result='+expr+'; use(result); }')
    self.assertIn('FAKE-DEPENDENCY',self.flags(r))
 def test_cancelled_updates(self):
  r=self.check('void f(void) { int x=3; x+=y; x-=y; use(x); }')
  self.assertIn('CANCELLED-UPDATE',self.flags(r))
 def test_identical_arms(self):
  r=self.check('void f(int cond) { if(cond){use(3);}else{use(3);} }','void f(int cond) {}')
  self.assertIn('IDENTICAL-ARMS',self.flags(r))
 def test_distinct_arms_with_shared_store(self):
  r=self.check('void f(int cond) { if(cond){use(3);p->x=4;}else{use(5);p->x=4;} }','void f(int cond) {}')
  self.assertNotIn('IDENTICAL-ARMS',self.flags(r));self.assertNotIn('REPEATED-STORE',self.flags(r))
 def test_added_asm_and_volatile(self):
  r=self.check('void f(void) { volatile int *p; p=0; use(*p); __asm__("nop"); }')
  self.assertIn('ASM',self.flags(r));self.assertIn('VOLATILE',self.flags(r,'REVIEW'))
 def test_inherited_one_trip_info(self):
  base='void f(void) { do { use(1); } while(0); }'
  r=self.check(base.replace('use(1)','use(2)'),base)
  self.assertIn('ONE-TRIP',self.flags(r,'INFO'));self.assertNotIn('ONE-TRIP',self.flags(r,'REVIEW'))
 def test_new_one_trip(self):
  r=self.check('void f(void) { do { use(1); } while(0); }')
  self.assertIn('ONE-TRIP',self.flags(r,'REVIEW'))
 def test_unused_local_and_typedef(self):
  r=self.check('typedef int Leftover; void f(void) { int unused; int written=2; }')
  self.assertIn('UNUSED-LOCAL',self.flags(r));self.assertIn('UNUSED-TYPEDEF',self.flags(r))
 def test_used_to_unused_is_new_finding(self):
  r=self.check('void f(void) { int winding; }','void f(void) { int winding; use(winding); }')
  self.assertIn('UNUSED-LOCAL',self.flags(r))
 def test_shifted_old_dead_value_stays_info(self):
  code='void f(void) { int value; value=3;\nvalue=4;use(value); }'
  r=self.check(code.replace('value=4','\n\nvalue=4'),code)
  self.assertNotIn('DEAD-VALUE',self.flags(r));self.assertIn('DEAD-VALUE',self.flags(r,'INFO'))
 def test_unchanged_scaffold_info(self):
  code='void f(void) { __asm__("nop"); }'
  r=self.check(code,code);self.assertNotIn('ASM',self.flags(r));self.assertIn('ASM',self.flags(r,'INFO'))
 def test_retained_unused_leftover_still_refuses(self):
  code='void f(void) { int unused; }'
  r=self.check(code,code);self.assertIn('UNUSED-LOCAL',self.flags(r))
 def test_signature_context_no_fake_parameter_verdict(self):
  r=self.check('void f(void *p,int successor,int arg2) { use(p);use(successor); }','void f(void *p) { use(p); }')
  self.assertIn('NEEDS-CONTEXT',self.flags(r,'REVIEW'));self.assertIn('callback',r['flags'][-1]['message']);self.assertFalse(self.flags(r))
 def test_only_argument_names_change(self):
  r=self.check('void f(int actual) { use(actual); }','void f(int arg0) { use(arg0); }')
  self.assertNotIn('NEEDS-CONTEXT',self.flags(r,'REVIEW'))
 def test_integer_page_two_genuine_uses(self):
  r=self.check('void f(void) { unsigned char *page=(unsigned char*)0x80010000; use(page[4]); page[8]=2; }')
  self.assertIn('INTEGER-PAGE',self.flags(r,'INFO'));self.assertNotIn('LITERAL-ADDRESS',self.flags(r))
 def test_page_pointer_copies_do_not_count_as_genuine_uses(self):
  r=self.check('void f(void) { unsigned char *page=(unsigned char*)0x80010000; use(page[4]); void *copy=(void*)page; use(copy); }')
  self.assertIn('LITERAL-ADDRESS',self.flags(r))
 def test_page_two_cast_dereferences_count(self):
  r=self.check('void f(void) { unsigned char *page=(unsigned char*)0x80010000; use(*(short*)(page+4)); *(short*)(page+8)=2; }')
  self.assertIn('INTEGER-PAGE',self.flags(r,'INFO'));self.assertNotIn('LITERAL-ADDRESS',self.flags(r))
 def test_decision45_existing_one_arm_local_still_needs_proof(self):
  base='void f(void) { int leftover; use(leftover); }'
  candidate='void f(void) { int leftover; /* decision 45: retail reads timer */ if(timer){leftover=2;} }'
  r=self.check(candidate,base);self.assertNotIn('UNUSED-LOCAL',self.flags(r));self.assertIn('UNUSED-LOCAL',self.flags(r,'INFO'))
 def test_decision45_comment_does_not_hide_unrelated_leftover(self):
  base='void f(void) { int leftover; use(leftover); }'
  candidate='void f(void) { int leftover; /* decision 45 */ use(timer); }'
  r=self.check(candidate,base);self.assertIn('UNUSED-LOCAL',self.flags(r))
 def test_decision45_new_local_is_not_the_exception(self):
  r=self.check('void f(void) { int invented; /* decision 45 */ if(timer){invented=2;} }')
  self.assertIn('UNUSED-LOCAL',self.flags(r))
 def test_single_page_use(self):
  r=self.check('void f(void) { unsigned char *page=(unsigned char*)0x80010000; use(page[4]); }')
  self.assertIn('LITERAL-ADDRESS',self.flags(r))
 def test_mask_not_address(self):
  r=self.check('void f(void) { int mask=0x80000000; use(mask); }')
  self.assertNotIn('LITERAL-ADDRESS',self.flags(r))
 def test_symbol_replaced_by_literal(self):
  r=self.check('void f(void) { use(*(int*)0x80013714); }','extern int D_80013714; void f(void) { use(D_80013714); }')
  self.assertIn('LITERAL-ADDRESS',self.flags(r))
 def test_comments_strings_multiline_macros_not_code(self):
  code='#define OPEN(x) \\\n do { \\\n   (x); \\\n } while(0)\nvoid f(void) { /* asm volatile unused */ use("asm volatile"); }'
  r=self.check(code);self.assertFalse(self.flags(r));self.assertFalse(self.flags(r,'REVIEW'))
 def test_shadow_local(self):
  r=self.check('void f(void) { int x=3; { int x=4; use(x); } use(x); }')
  self.assertNotIn('UNUSED-LOCAL',self.flags(r))
 def test_call_arity_change_without_prototype_edit_needs_context(self):
  r=self.check('void f(void) { handler(1,2,3); }','void f(void) { handler(1); }')
  self.assertIn('NEEDS-CONTEXT',self.flags(r,'REVIEW'));self.assertFalse(self.flags(r))
 def test_nested_call_arity_ignores_commas_in_inner_call(self):
  r=self.check('void f(void) { handler(inner(1,2),3); }','void f(void) { handler(inner(4,5),6); }')
  self.assertNotIn('NEEDS-CONTEXT',self.flags(r,'REVIEW'))
 def test_attribute_on_definition_still_analyzed(self):
  r=self.check('void f(void) __attribute__((noreturn)) { int unused; }')
  self.assertIn('UNUSED-LOCAL',self.flags(r))
 def test_callback_field_is_not_a_typedef(self):
  r=self.check('typedef struct { void (*callback)(int); } Record; void f(Record *record) { record->callback(2); }')
  self.assertNotIn('UNUSED-TYPEDEF',self.flags(r))
 def test_unused_callback_typedef_and_variable(self):
  r=self.check('typedef void (*Handler)(int); void f(void) { void (*callback)(int); }')
  self.assertIn('UNUSED-TYPEDEF',self.flags(r));self.assertIn('UNUSED-LOCAL',self.flags(r))
 def test_bad_delimiters_fail_incomplete(self):
  with self.assertRaises(ValueError):self.check('void f(void) {')

class RepositoryFixtures(unittest.TestCase):
 def setUp(self):
  self.temp=tempfile.TemporaryDirectory();self.root=Path(self.temp.name)
  for sub in ['ledger','include','src/test','out/test']: (self.root/sub).mkdir(parents=True)
  self.row={'id':'test/f','container':'test','func':'f','true_name':None,'c_path':'src/test/f.c','gate_config':'bank'}
  (self.root/'ledger/rows.jsonl').write_text(json.dumps(self.row)+'\n')
  (self.root/'src/test/f.c').write_text('void f(void) {}')
  self.repo=L.Repository(self.root)
 def tearDown(self):self.temp.cleanup()
 def test_header_order(self):
  (self.root/'include/common.h').write_text('typedef int s32;')
  (self.root/'include/compat.h').write_text('typedef s32 Unknown;')
  good='#include "common.h"\n#include "compat.h"\nvoid f(void) {}'
  bad='#include "compat.h"\n#include "common.h"\nvoid f(void) {}'
  self.assertFalse(self.repo.include_findings(L.Source(good)));self.assertEqual(self.repo.include_findings(L.Source(bad))[0]['code'],'HEADER-ORDER')
 def test_named_struct_tag_does_not_require_a_typedef(self):
  src=L.Source('struct Record; void f(struct Record *record) { use(record); }')
  self.assertFalse(self.repo.include_findings(src))
 def test_missing_type(self):
  r=L.analyze('void f(void) {}','extern MissingRecord *get(void);void f(void) {}','test/f',self.repo,self.row)
  self.assertTrue(any(f['code']=='MISSING-TYPE' and f['severity']=='REFUSE-LIKELY' for f in r['flags']))
 def test_named_symbol_literal_without_D_prefix(self):
  (self.root/'config').mkdir();(self.root/'config/slus_006.14.symbols.txt').write_text('named_flags = 0x80013714;')
  r=L.analyze('void f(void) {}','void f(void) { use(*(int*)0x80013714); }','test/f',self.repo,self.row)
  self.assertTrue(any(f['code']=='LITERAL-ADDRESS' and 'named_flags' in f['message'] for f in r['flags']))
 def test_selected_overlay_symbol_table_only(self):
  (self.root/'config').mkdir();(self.root/'config/bank.yaml').write_text('symbol_addrs_path: config/bank.symbols.txt\n')
  (self.root/'config/bank.symbols.txt').write_text('bank_record = 0x80024814;')
  row={**self.row,'gate_config':'config/bank.yaml'}
  r=L.analyze('void f(void) {}','void f(void) { use(*(int*)0x80024814); }','test/f',self.repo,row)
  self.assertTrue(any(f['code']=='LITERAL-ADDRESS' and 'bank_record' in f['message'] for f in r['flags']))
 def test_registered_return_conflict(self):
  target={**self.row,'id':'test/get','func':'get','c_path':'src/test/get.c'}
  (self.root/'ledger/rows.jsonl').write_text(json.dumps(self.row)+'\n'+json.dumps(target)+'\n')
  (self.root/'src/test/get.c').write_text('int get(void) { return 1; }')
  r=L.analyze('int get(void);void f(void) {}','short get(void);void f(void) {}','test/f',self.repo,self.row)
  self.assertTrue(any(f['code']=='DECLARATION-CONFLICT' for f in r['flags']))
 def cli(self,*argv):
  output=io.StringIO()
  with redirect_stdout(output),redirect_stderr(output):rc=L.main([*argv,'--root',str(self.root)])
  return rc,output.getvalue()
 def test_single_mode_advisory_exit_zero(self):
  p=self.root/'cand.c';p.write_text('void f(void) { int unused; }')
  rc,out=self.cli('test/f',str(p));self.assertEqual(rc,0);self.assertIn('REFUSE-LIKELY',out)
 def test_batch_refuse_exit_one(self):
  (self.root/'out/test/f.c').write_text('void f(void) { int unused; }')
  rc,out=self.cli('--check',str(self.root/'out'),'--json');self.assertEqual(rc,1);self.assertEqual(json.loads(out)['reports'][0]['counts']['REFUSE-LIKELY'],1)
 def test_batch_clean_exit_zero(self):
  (self.root/'out/test/f.c').write_text('void f(void) { use(3); }')
  rc,_=self.cli('--check',str(self.root/'out'));self.assertEqual(rc,0)
 def test_batch_unknown_row_incomplete_exit_two(self):
  (self.root/'out/test/unknown.c').write_text('void f(void) {}')
  rc,_=self.cli('--check',str(self.root/'out'));self.assertEqual(rc,2)
 def test_batch_empty_refuses_incomplete(self):
  rc,_=self.cli('--check',str(self.root/'out'));self.assertEqual(rc,2)
 def test_stale_guard_is_visible(self):
  p=self.root/'out/test/f.c';p.write_text('void f(void) {}');p.with_name('f.c.base_sha').write_text('bad')
  rc,out=self.cli('--check',str(self.root/'out'));self.assertEqual(rc,2);self.assertIn('NEEDS-REBASE',out)
 def test_stage_advisory_no_block_on_flag(self):
  output=[];r=L.stage_advisory(self.row,'void f(void) {}','void f(void) { int unused; }',out=output.append,root=self.root)
  self.assertTrue(r['advisory']);self.assertIn('staging remains allowed',output[0])
 def test_internal_analysis_error_remains_advisory(self):
  from unittest.mock import patch
  output=[]
  with patch.object(L,'analyze',side_effect=RuntimeError('fixture internal error')):
   r=L.stage_advisory(self.row,'void f(void) {}','void f(void) {}',out=output.append,root=self.root)
  self.assertIn('error',r);self.assertIn('staging remains allowed',output[0])
 def test_cli_internal_error_returns_incomplete_not_clear(self):
  from unittest.mock import patch
  p=self.root/'cand.c';p.write_text('void f(void) {}')
  with patch.object(L,'analyze',side_effect=RuntimeError('fixture internal error')):
   rc,out=self.cli('test/f',str(p),'--json')
  self.assertEqual(rc,2);self.assertEqual(len(json.loads(out)['errors']),1)
 def test_stage_advisory_no_block_on_parse_error(self):
  output=[];r=L.stage_advisory(self.row,'void f(void) {}','void f(void) {',out=output.append,root=self.root)
  self.assertIn('error',r);self.assertIn('staging remains allowed',output[0])

@unittest.skipUnless((ROOT/'tools/common.py').is_file(),'installed lab integration requires the full scratch checkout')
class LabIntegration(unittest.TestCase):
 def test_refuse_likely_advisory_does_not_block_stage_file(self):
  from unittest.mock import patch
  import lab
  with tempfile.TemporaryDirectory() as directory:
   lane=Path(directory);basepath=lane/'base.c';base='void f(void) {}';candidate='void f(void) { int unused; }'
   basepath.write_text(base);output=io.StringIO()
   row={'id':'test/f','container':'test','c_path':'src/test/f.c'}
   with patch.object(lab.kitlib,'admissible',return_value=[]),redirect_stdout(output):
    staged=lab.stage_file(lane,row,basepath,base,candidate)
   self.assertEqual(staged,'out/test/f.c');self.assertEqual((lane/staged).read_text(),candidate)
   self.assertIn('REFUSE-LIKELY',output.getvalue());self.assertIn('staging remains allowed',output.getvalue())

if __name__=='__main__':unittest.main()
