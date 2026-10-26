"""Symbolic tables reject numeric payloads, foreign owners and partial relocations."""
import copy,sys,tempfile,unittest
from pathlib import Path
from types import SimpleNamespace
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'tools/gate'))
import overlay_symbolic_allocations as P
import overlay_native_allocations as Z

class SymbolicOwnership(unittest.TestCase):
 def setUp(self):
  self.temp=tempfile.TemporaryDirectory(dir=ROOT/'work');self.addCleanup(self.temp.cleanup);self.root=Path(self.temp.name)
  (self.root/'owner.h').write_text('typedef void (*Callback)(void *state, void *position, void *render);\n')
  (self.root/'owner.c').write_text('Callback callbacks[2] = { first, second };\n')
  self.slot=dict(kind='function_pointers',symbol='callbacks',offset=0,size=8,source='owner.c',type='Callback',declaration='owner.h',targets=['first','second'],owner='town/first')
  self.a=dict(section='.data',foff=0x200,vma=0x80010200,size=8,link_alignment=4,slots=[self.slot])
  self.m=dict(container='town',allocation_model=P.MODEL,source='owner.c',members=[dict(id='town/first',function='first',source='owner.c',foff=0x100,vma=0x80010100,size=4)],data_members=[dict(id='town/table',source='owner.c',symbol='callbacks',foff=0x200,vma=0x80010200,size=8)],imports=[dict(symbol='second',kind='function',vma=0x80010300)],allocations=[dict(section='.text.*',foff=0x100,vma=0x80010100,size=4,link_alignment=4),self.a],owned_data=[],headers=['owner.h'],review_inputs=['owner.c'],section_order=['.text.first','.data'])
  self.rows={'town/table':dict(row_kind='data',data_kind='function_table',ownership_status='evidenced',owner='town/first'),'town/first':dict(func='first',true_name='first',container='town',foff=0x100),'town/second':dict(func='second',true_name='second',container='town',foff=0x300)}
 def test_complete_symbolic_table(self):Z.validate(self.m,self.root);P.validate_ownership(self.m,self.rows)
 def test_numeric_or_arithmetic_initializer_rejected(self):
  for body in ['0x80010100, second','first+4, second','first, 0','first']:
   with self.subTest(body=body):
    (self.root/'owner.c').write_text('Callback callbacks[2] = {'+body+'};')
    with self.assertRaises(ValueError):Z.validate(self.m,self.root)
 def test_non_function_typedef_rejected(self):
  (self.root/'owner.h').write_text('typedef unsigned int Callback;')
  with self.assertRaisesRegex(ValueError,'typed callback'):Z.validate(self.m,self.root)
 def test_foreign_or_unevidenced_table_rejected(self):
  for field,value in [('row_kind','code'),('data_kind','literal'),('owner','town/other'),('ownership_status','guessed')]:
   rows=copy.deepcopy(self.rows);rows['town/table'][field]=value
   with self.subTest(field=field),self.assertRaises(ValueError):P.validate_ownership(self.m,rows)
 def test_data_target_or_function_interior_rejected(self):
  for change in ['data','missing']:
   rows=copy.deepcopy(self.rows)
   if change=='data':rows['town/second']['row_kind']='data'
   else:del rows['town/second']
   with self.subTest(change=change),self.assertRaisesRegex(ValueError,'code entry'):P.validate_ownership(self.m,rows)
 def test_same_virtual_address_in_another_overlay_is_not_ownership(self):
  for field,value in [('container','dungeon'),('foff',0x700)]:
   rows=copy.deepcopy(self.rows);rows['town/second'][field]=value
   with self.subTest(field=field),self.assertRaisesRegex(ValueError,'this load map'):P.validate_ownership(self.m,rows)
 def test_partial_allocation_rejected(self):
  self.m['data_members'][0]['size']=4
  with self.assertRaisesRegex(ValueError,'extent/owner'):Z.validate(self.m,self.root)
 def test_unfingerprinted_source_rejected(self):
  self.m['review_inputs']=[]
  with self.assertRaisesRegex(ValueError,'not fingerprinted'):Z.validate(self.m,self.root)
 def view(self,tokens=None,relocs=None):
  tokens=tokens if tokens is not None else [(0,'32',('fn','first',0)),(0,'32',('sym','second',0))]
  relocs=relocs if relocs is not None else [('.data',0,'32',('sym','first'),0),('.data',4,'32',('sym','second'),0)]
  return SimpleNamespace(funcs={},obj=SimpleNamespace(sections={'.data':bytes(8)},relocs=relocs),tokens=lambda name:tokens)
 def test_complete_function_relocations(self):self.assertEqual(len(P.check_view(self.m,self.a,self.view())),2)
 def test_missing_extra_wrong_target_and_addend_rejected(self):
  wrong=[(0,'32',('fn','first',4)),(0,'32',('sym','second',0))]
  for v in [self.view(relocs=[]),self.view(relocs=[('.data',0,'32',('sym','first'),0)]*2),self.view(tokens=wrong),self.view(tokens=[(0,'32',('sym','second',0))]*2),self.view(tokens=[(1,None,None)]*2)]:
   with self.assertRaises(ValueError):P.check_view(self.m,self.a,v)
 def test_unresolved_relocation_rejected(self):
  a=SimpleNamespace(resolve_tokens=lambda *args,**kwargs:([0,0],[1]))
  with self.assertRaisesRegex(ValueError,'unresolved'):P.resolve_storage(self.m,self.view(),self.a,{},a)

class SharedDataLayout(unittest.TestCase):
 def test_only_evidenced_data_can_share_its_code_owner_source(self):
  import json
  import source_layout as L
  with tempfile.TemporaryDirectory(dir=ROOT/'work') as td:
   root=Path(td);(root/'ledger').mkdir();(root/'src/town').mkdir(parents=True);(root/'src/town/owner.c').write_text('void owner(void) {}\n')
   rows=[dict(id='town/code',container='town',c_path='code.c'),dict(id='town/data',container='town',c_path='data.c',row_kind='data',data_kind='function_table',ownership_status='evidenced',owner='town/code')]
   layout=[dict(id=r['id'],path='src/town/owner.c') for r in rows]
   def write():
    (root/'ledger/rows.jsonl').write_text(''.join(json.dumps(r)+'\n' for r in rows));(root/'ledger/layout.jsonl').write_text(''.join(json.dumps(r)+'\n' for r in layout))
   for kind in ('function_table','descriptor_table','native_prefix'):
    rows[1]['data_kind']=kind
    write();self.assertEqual(L.mapping(root)['town/data'],'src/town/owner.c');self.assertEqual(L.validate(root),2)
   rows[1]['ownership_status']='guessed';write()
   with self.assertRaisesRegex(ValueError,'two rows'):L.mapping(root)

class MatchSelection(unittest.TestCase):
 def test_data_row_requires_one_complete_native_owner(self):
  from unittest.mock import patch
  import overlay_module_gate as G
  member=dict(id='town/table',foff=0x200,size=8,symbol='D_80010200')
  m=dict(allocation_model=P.MODEL,data_members=[member])
  row=dict(func_vram='table',foff=0x200,size=8,true_name='D_80010200')
  with patch.object(G,'load_modules',return_value=[m]):self.assertEqual(P.data_member(ROOT,'town',row),(m,member))
  for mods in [[],[m,m]]:
   with patch.object(G,'load_modules',return_value=mods),self.assertRaisesRegex(ValueError,'one complete'):P.data_member(ROOT,'town',row)
  row['size']=4
  with patch.object(G,'load_modules',return_value=[m]),self.assertRaisesRegex(ValueError,'extent/identity'):P.data_member(ROOT,'town',row)

if __name__=='__main__':unittest.main()
