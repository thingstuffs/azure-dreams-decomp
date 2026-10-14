"""Separated objects refuse hidden bytes, mixed layouts and raw storage reuse."""
import copy,dataclasses,importlib.util,os,struct,sys,tempfile,unittest
from pathlib import Path
R=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(R/'tools/gate'))
import overlay_native_allocations as Z
@dataclasses.dataclass(frozen=True)
class Segment:
 index:int;kind:str;start:int;end:int;vram:int;section:str
 name:str|None=None;match:object=None;bytes_path:Path|None=None;module_key:str|None=None
class AllocationLayout(unittest.TestCase):
 def setUp(self):
  self.tmp=tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR',str(R/'work')));self.addCleanup(self.tmp.cleanup);self.root=Path(self.tmp.name)
  (self.root/'storage.c').write_text('static u32 words[1] = {0x40000001};\nstatic s32 *port = (s32 *)0x1F801080;\nstatic const char message[] = "ok";\n')
  self.m={'allocation_model':Z.MODEL,'key':'unit_object','owned_data':[],'review_inputs':['storage.c'],'members':[{'id':'unit/function','source':'function.c','function':'function','foff':0x100,'vma':0x80176900,'size':4}],
   'allocations':[{'section':'.rodata','foff':0,'vma':0x80176800,'size':3,'link_alignment':4,'slots':[{'symbol':'message','offset':0,'size':3,'kind':'typed_string','source':'storage.c'}]},
    {'section':'.text.*','foff':0x100,'vma':0x80176900,'size':4,'link_alignment':4},
    {'section':'.data','foff':0x200,'vma':0x80176a00,'size':8,'link_alignment':4,'slots':[{'symbol':'words','offset':0,'size':4,'kind':'u32_words','source':'storage.c'},{'symbol':'port','offset':4,'size':4,'kind':'device_pointer','source':'storage.c'}]}],
   'section_order':['.data','.rodata','.text.function']}
 def elf(self,data=None,rodata=b'ok\0\0'):
  data=struct.pack('<II',0x40000001,0x1f801080)+bytes(8) if data is None else data
  names=b'\0.data\0.rodata\0.shstrtab\0';blob=bytearray(52);blob[:7]=b'\x7fELF\x01\x01\x01'
  contents=[]
  for payload in [data,rodata,names]:contents.append((len(blob),len(payload)));blob.extend(payload)
  table=(len(blob)+3)&~3;blob.extend(bytes(table-len(blob)));headers=[(0,0,0,0,0,0,0,0,0,0),
   (1,1,3,0,*contents[0],0,0,16,0),(7,1,2,0,*contents[1],0,0,4,0),(15,3,0,0,*contents[2],0,0,1,0)]
  for h in headers:blob.extend(struct.pack('<10I',*h))
  struct.pack_into('<I',blob,32,table);struct.pack_into('<HHH',blob,46,40,4,3);return bytes(blob)
 def test_only_canonical_zero_end_padding_removed(self):
  blob=self.elf();cooked,p=Z.prepare(self.m,blob,self.root)
  self.assertEqual([(x['semantic_bytes'],x['padding_bytes']) for x in p],[(3,1),(8,8)])
  self.assertEqual(len(cooked),len(blob));self.assertEqual(Z.elf_headers(cooked)[2]['.data'][1][5],8)
 def test_nonzero_padding_refused(self):
  bad=struct.pack('<II',0x40000001,0x1f801080)+b'\1'+bytes(7)
  with self.assertRaisesRegex(ValueError,'end padding'):Z.prepare(self.m,self.elf(bad),self.root)
 def test_changed_semantic_word_refused(self):
  bad=struct.pack('<II',0x40000000,0x1f801080)+bytes(8)
  with self.assertRaisesRegex(ValueError,'literal storage'):Z.prepare(self.m,self.elf(bad),self.root)
 def test_gnu_extent_not_rounding_refused(self):
  bad=struct.pack('<II',0x40000001,0x1f801080)+bytes(24)
  with self.assertRaisesRegex(ValueError,'end padding'):Z.prepare(self.m,self.elf(bad),self.root)
 def test_mixed_prefix_and_separated_refused(self):
  m=copy.deepcopy(self.m);m['owned_data']=[{'size':4}]
  with self.assertRaisesRegex(ValueError,'mixed'):Z.validate(m,self.root)
 def test_slot_overlap_and_missing_coverage_refused(self):
  for offset in [0,8]:
   m=copy.deepcopy(self.m);m['allocations'][2]['slots'][1]['offset']=offset
   with self.assertRaisesRegex(ValueError,'slot order'):Z.validate(m,self.root)
 def test_unfingerprinted_storage_refused(self):
  m=copy.deepcopy(self.m);m['review_inputs']=[]
  with self.assertRaisesRegex(ValueError,'not fingerprinted'):Z.validate(m,self.root)
 def test_device_pointer_outside_hardware_refused(self):
  p=self.root/'storage.c';p.write_text(p.read_text().replace('0x1F801080','0x80176800'))
  with self.assertRaisesRegex(ValueError,'hardware registers'):Z.validate(self.m,self.root)
 def test_allocator_must_have_complete_natural_text(self):
  m=copy.deepcopy(self.m);m['allocations'][1]['size']=8
  with self.assertRaisesRegex(ValueError,'complete cohort'):Z.validate(m,self.root)
 def segments(self):return [Segment(0,'raw',0,0x100,0x80040000,'x',name='L_raw_000000'),Segment(1,'c',0x100,0x104,0x80040100,'y'),Segment(2,'raw',0x104,0x210,0x80040104,'z',name='L_raw_000104')]
 def test_owned_bytes_physically_project_and_raw_gaps_remain(self):
  segments=self.segments();blob=b'ok\0'+bytes(4)+struct.pack('<II',0x40000001,0x1f801080)
  pieces=Z.project_storage(self.m,segments,blob,self.root)
  self.assertEqual(pieces,[{'section':'.rodata','foff':0,'size':3},{'section':'.data','foff':0x200,'size':8}])
  owned=[s for s in segments if s.module_key]
  self.assertEqual([s.bytes_path.read_bytes() for s in owned],[b'ok\0',blob[-8:]])
  self.assertEqual([(s.start,s.end) for s in segments if s.kind=='raw'],[(3,0x100),(0x104,0x200),(0x208,0x210)])
  raw=[s for s in segments if s.kind=='raw'];self.assertEqual(len({s.name for s in raw}),len(raw))
  self.assertEqual(raw[-1].vram,0x80040208)
  self.assertEqual([s.index for s in segments],list(range(len(segments))))
 def test_storage_cannot_overwrite_registered_code(self):
  segments=self.segments();segments[0]=dataclasses.replace(segments[0],kind='c')
  with self.assertRaisesRegex(ValueError,'raw projection source'):Z.project_storage(self.m,segments,bytes(15),self.root)
 def test_literal_record_rejects_hidden_fields(self):
  (self.root/'record.c').write_text('struct Record { u32 a; u8 hidden[4]; }; static struct Record stamp = {1,2};')
  slot={'symbol':'stamp','size':8,'source':'record.c','kind':'u32_record'}
  with self.assertRaisesRegex(ValueError,'plain u32'):Z.slot_literal(slot,self.root)
if __name__=='__main__':unittest.main()
