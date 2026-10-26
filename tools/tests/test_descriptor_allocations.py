"""Mixed descriptors require complete typed records and symbolic pointer slots."""
import copy,json,sys,tempfile,unittest
from pathlib import Path
from types import SimpleNamespace
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'tools/gate'))
import overlay_descriptor_allocations as D
import overlay_symbolic_allocations as P

class DescriptorOwnership(unittest.TestCase):
 def setUp(self):
  self.temp=tempfile.TemporaryDirectory(dir=ROOT/'work');self.addCleanup(self.temp.cleanup);self.root=Path(self.temp.name)
  (self.root/'owner.h').write_text('typedef s32 (*Predicate)(void *, s32); typedef void *(*Text)(void *, s32, s32); typedef u8 *Data; typedef struct { Predicate predicate; Text text; Data value; s16 flag; s16 reserved; } Choice;')
  (self.root/'owner.c').write_text('Choice choices[1] = { { first, second, text_data, 13, 0 } };')
  self.slot=dict(kind='typed_records',symbol='choices',offset=0,size=16,source='owner.c',type='Choice',declaration='owner.h',owner='town/first',stride=16,records=[['first','second','text_data',13,0]],bounds='bounds.json',fields=[dict(name=n,type=t,kind=k,offset=o) for n,t,k,o in [('predicate','Predicate','function',0),('text','Text','function',4),('value','Data','data',8),('flag','s16','scalar',12),('reserved','s16','scalar',14)]])
  (self.root/'bounds.json').write_text(json.dumps(dict(symbol='choices',stride=16,count=1,size=16,basis=['complete record'],consumers=['consumer.c'],references=[0x100])))
  self.a=dict(section='.data',foff=0x200,vma=0x80010200,size=16,link_alignment=4,slots=[self.slot])
  self.m=dict(container='town',allocation_model=P.MODEL,source='owner.c',members=[dict(id='town/first',function='first',source='owner.c',foff=0x100,vma=0x80010100,size=4)],data_members=[dict(id='town/table',source='owner.c',symbol='choices',foff=0x200,vma=0x80010200,size=16)],imports=[dict(symbol='second',kind='function',vma=0x80010300),dict(symbol='text_data',kind='data',vma=0x80010400)],allocations=[self.a],owned_data=[],headers=['owner.h'],review_inputs=['owner.c','bounds.json','consumer.c'])
 def test_whole_typed_record(self):D.validate(self.slot,self.m,self.root);self.assertEqual(D.source_words(self.slot,self.root)[12:],b'\r\0\0\0')
 def test_pointer_literals_casts_arithmetic_and_partial_records_rejected(self):
  for body in ['0x80010100, second, text_data, 13, 0','first+4, second, text_data, 13, 0','(Predicate)first, second, text_data, 13, 0','first, second, text_data, 13']:
   (self.root/'owner.c').write_text('Choice choices[1] = { {'+body+'} };')
   with self.subTest(body=body),self.assertRaises(ValueError):D.source_words(self.slot,self.root)
 def test_changed_layout_scalar_or_bounds_rejected(self):
  for change in ['field','scalar','bound']:
   slot=copy.deepcopy(self.slot)
   if change=='field':slot['fields'][3]['offset']=10
   elif change=='scalar':slot['records'][0][3]=65536
   else:slot['size']=12
   with self.subTest(change=change),self.assertRaises(ValueError):D.validate(slot,self.m,self.root)
 def test_scalar_only_blob_cannot_claim_descriptor_ownership(self):
  slot=copy.deepcopy(self.slot)
  for field in slot['fields'][:3]:field.update(type='u32',kind='scalar')
  slot['records'][0][:3]=[0x80010100,0x80010300,0x80010400]
  with self.assertRaisesRegex(ValueError,'callback field'):D.validate(slot,self.m)
 def test_code_and_data_imports_cannot_be_interchanged(self):
  self.m['imports'][0]['kind']='data'
  with self.assertRaisesRegex(ValueError,'typed import'):D.validate(self.slot,self.m)
 def test_real_typedef_and_consumer_evidence_required(self):
  for change in ['header','consumer']:
   if change=='header':(self.root/'owner.h').write_text((self.root/'owner.h').read_text().replace('typedef s32 (*Predicate)(void *, s32);','typedef u32 Predicate;'))
   else:self.m['review_inputs'].remove('consumer.c')
   with self.subTest(change=change),self.assertRaises(ValueError):D.validate(self.slot,self.m,self.root)
 def view(self,scalar=13,relocs=None):
  ptrs=[('.data',i*4,'32',('sym',n),0) for i,n in enumerate(['first','second','text_data'])]
  tokens=[(0,'32',('fn','first',0)),(0,'32',('sym','second',0)),(0,'32',('sym','text_data',0)),(scalar,None,None)]
  return SimpleNamespace(funcs={},obj=SimpleNamespace(sections={'.data':bytes(16)},relocs=ptrs if relocs is None else relocs),tokens=lambda name:tokens)
 def test_full_pointer_and_scalar_inventory(self):self.assertEqual(len(P.check_view(self.m,self.a,self.view())),4)
 def test_missing_relocations_and_scalar_drift_rejected(self):
  for view in [self.view(14),self.view(relocs=[])]:
   with self.assertRaises(ValueError):P.check_view(self.m,self.a,view)
if __name__=='__main__':unittest.main()
