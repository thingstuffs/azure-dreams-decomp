"""Fail-closed ownership and native projection for compiler-owned switch data."""
import dataclasses,sys,tempfile,unittest,subprocess
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch
ROOT=Path(__file__).resolve().parents[2]
sys.path[:0]=[str(ROOT/'tools'),str(ROOT/'tools/gate')]
import overlay_switch_allocations as X
import overlay_native_allocations as Z
import overlay_scoped_fingerprint as F
from gate import overlay_module_gate as G

def manifest():
 return dict(key='test_switch',container='dungeon',allocation_model=X.MODEL,owned_data=[],review_inputs=['src/dungeon/owner.c'],recipe=dict(cfg='2.7.2-cdk-G0',row_asflags=''),data_members=[dict(id='dungeon/table',source='src/dungeon/table.c',symbol='D_80016000',foff=0x1000,vma=0x80016000,size=52)],members=[dict(id='dungeon/owner',source='src/dungeon/owner.c',function='func_80017000',foff=0x2000,vma=0x80017000,size=300),dict(id='dungeon/next',source='src/dungeon/next.c',function='func_8001712C',foff=0x212C,vma=0x8001712C,size=64)],allocations=[dict(section='.rodata',foff=0x1000,vma=0x80016000,size=52,link_alignment=4,slots=[dict(kind='switch_table',offset=0,size=52,owner='func_80017000',source='src/dungeon/owner.c')]),dict(section='.text.*',foff=0x2000,vma=0x80017000,size=364,link_alignment=4)],section_order=['.text.func_80017000','.rodata','.text.func_8001712C'])

class Ownership(unittest.TestCase):
 def test_complete_disjoint_table_and_text(self):
  m=manifest();X.validate(m);self.assertTrue(Z.enabled(m));self.assertEqual(Z.offset(m,0x2000,300),52)
 def test_registry_ownership_evidenced(self):
  X.validate_ownership(manifest(),{'dungeon/table':dict(row_kind='data',data_kind='jump_table',ownership_status='evidenced',owner='dungeon/owner')})
 def test_registry_foreign_or_unevidenced_owner_rejected(self):
  for field,value in [('row_kind','overlay'),('data_kind','literal'),('ownership_status','guessed'),('owner','dungeon/foreign')]:
   row=dict(row_kind='data',data_kind='jump_table',ownership_status='evidenced',owner='dungeon/owner');row[field]=value
   with self.subTest(field=field),self.assertRaises(ValueError):X.validate_ownership(manifest(),{'dungeon/table':row})
 def rejected(self,change):
  m=manifest();change(m)
  with self.assertRaises(ValueError):X.validate(m)
 def test_missing_data_owner(self):self.rejected(lambda m:m.update(data_members=[]))
 def test_foreign_switch_owner(self):self.rejected(lambda m:m['allocations'][0]['slots'][0].update(owner='foreign'))
 def test_foreign_owner_source(self):self.rejected(lambda m:m['allocations'][0]['slots'][0].update(source='src/other.c'))
 def test_unbound_owner_source(self):self.rejected(lambda m:m.update(review_inputs=[]))
 def test_literal_table_rejected(self):self.rejected(lambda m:m['allocations'][0]['slots'][0].update(kind='u32_words'))
 def test_partial_data_row(self):self.rejected(lambda m:m['data_members'][0].update(size=48))
 def test_function_gap(self):self.rejected(lambda m:m['members'][1].update(foff=0x2130,vma=0x80017130))
 def test_partial_code(self):self.rejected(lambda m:m['allocations'][1].update(size=360))
 def test_load_delta(self):self.rejected(lambda m:m['allocations'][0].update(vma=0x80016004))
 def test_extra_storage(self):self.rejected(lambda m:m['allocations'].append(dict(section='.data',foff=0x3000,vma=0x80018000,size=4,link_alignment=4)))
 def test_section_order(self):self.rejected(lambda m:m['section_order'].reverse())
 def test_mixed_prefix(self):self.rejected(lambda m:m.update(owned_data=[dict(kind='switch_table')]))
 def test_outside_proven_map(self):
  with self.assertRaises(ValueError):X.validate(manifest(),region=dict(foff_start='0x1000',foff_end='0x2100'))

@dataclasses.dataclass
class Segment:
 start:int
 end:int
 kind:str
 vram:int
 name:str='raw'
 match:object=None
 bytes_path:object=None
 index:int=0
 section:str='.ovlseg_0000'
 module_key:object=None
 @property
 def size(self):return self.end-self.start

class PromotedParameter(unittest.TestCase):
 def test_public_word_prototype_and_c89_short_definition_are_compatible(self):
  gcc=ROOT/'toolchain/compilers/gcc-2.7.2-cdk'
  with tempfile.TemporaryDirectory(dir=ROOT/'work') as td:
   td=Path(td);source=td/'parameter.c';source.write_text('typedef short s16; typedef int s32;\ns16 filter(s32);\ns16 filter(value) s16 value; { return value; }\n')
   result=subprocess.run([str(gcc/'gcc'),'-B'+str(gcc)+'/', '-S','-O2','-G0','-Werror',str(source),'-o',str(td/'parameter.s')],capture_output=True,text=True)
   self.assertEqual(result.returncode,0,result.stdout+result.stderr)

class Projection(unittest.TestCase):
 def test_registered_data_context_is_replaced_by_native_switch(self):
  m=manifest()
  with tempfile.TemporaryDirectory(dir=ROOT/'work') as td:
   root=Path(td);out=root/'proof';out.mkdir();(out/'module.bin').write_bytes(b'T'*52+b'C'*364);(out/'receipt.json').write_text('{}')
   segs=[Segment(0x1000,0x1034,'c',0x80016000,match=SimpleNamespace(config=m['recipe']['cfg'],source=root/'src/dungeon/table.c'))]
   with patch.object(G,'load_modules',return_value=[m]),patch.object(G,'build',return_value=({'fingerprint':{'sha256':'test'}},out/'module.bin')):r=G.project_segments(segs,out,'dungeon_test',root)
   self.assertEqual(r[0]['projected_rows'],['dungeon/table']);self.assertEqual(segs[0].kind,'rowbase');self.assertEqual(segs[0].bytes_path.read_bytes(),b'T'*52)
 def test_foreign_data_source_or_recipe_rejected(self):
  m=manifest()
  for source,cfg in [('src/foreign.c',m['recipe']['cfg']),('src/dungeon/table.c','2.8.1-G0')]:
   with self.subTest(source=source,cfg=cfg),tempfile.TemporaryDirectory(dir=ROOT/'work') as td:
    root=Path(td);out=root/'proof';out.mkdir();(out/'module.bin').write_bytes(b'T'*52+b'C'*364);(out/'receipt.json').write_text('{}');segs=[Segment(0x1000,0x1034,'c',0x80016000,match=SimpleNamespace(config=cfg,source=root/source))]
    with patch.object(G,'load_modules',return_value=[m]),patch.object(G,'build',return_value=({'fingerprint':{'sha256':'test'}},out/'module.bin')),self.assertRaisesRegex(ValueError,'canonical switch-data'):G.project_segments(segs,out,'dungeon_test',root)
 def test_required_windows_follow_both_allocations_and_skip_gap(self):
  wins={name:dict(name='dungeon_'+name,standalone_build=dict(window=dict(file_start=lo,file_end=hi))) for name,lo,hi in [('table',0x1000,0x1034),('gap',0x1100,0x1200),('last',0x212C,0x216C)]}
  self.assertEqual(F.required_windows(manifest(),wins,G),['last','table'])
 def test_table_only_window_still_builds_complete_native_tu(self):
  m=manifest()
  with tempfile.TemporaryDirectory(dir=ROOT/'work') as td:
   root=Path(td);out=root/'proof';out.mkdir();(out/'module.bin').write_bytes(b'T'*52+b'C'*364);(out/'receipt.json').write_text('{}')
   segs=[Segment(0x1000,0x1034,'raw',0x80016000)]
   with patch.object(G,'load_modules',return_value=[m]),patch.object(G,'build',return_value=({'fingerprint':{'sha256':'test'}},out/'module.bin')) as build:receipts=G.project_segments(segs,out,'dungeon_test',root)
   build.assert_called_once();self.assertEqual(receipts[0]['projected_rows'],['dungeon/table']);self.assertEqual(segs[0].bytes_path.read_bytes(),b'T'*52)
 def test_native_table_replaces_raw_and_gap_stays_raw(self):
  m=manifest()
  with tempfile.TemporaryDirectory(dir=ROOT/'work') as td:
   root=Path(td);out=root/'proof';out.mkdir();blob=b'T'*52+b'C'*300+b'N'*64;(out/'module.bin').write_bytes(blob);(out/'receipt.json').write_text('{}')
   segs=[Segment(0x1000,0x2000,'raw',0x80016000)]
   for a in m['members']:segs.append(Segment(a['foff'],a['foff']+a['size'],'c',a['vma'],match=SimpleNamespace(config='2.7.2-cdk-G0',source=root/a['source'])))
   with patch.object(G,'load_modules',return_value=[m]),patch.object(G,'build',return_value=({'fingerprint':{'sha256':'test'}},out/'module.bin')):receipts=G.project_segments(segs,out,'dungeon_test',root)
   self.assertEqual(receipts[0]['projected_rows'],[a['id'] for a in G.all_members(m)])
   self.assertEqual([(s.start,s.end) for s in segs if s.kind=='raw'],[(0x1034,0x2000)])
   self.assertEqual([s.bytes_path.read_bytes() for s in segs if s.module_key],[b'T'*52,b'C'*300,b'N'*64])
 def test_partial_function_rejected(self):
  with patch.object(G,'load_modules',return_value=[manifest()]),self.assertRaisesRegex(ValueError,'partial'):G.project_segments([Segment(0x2004,0x212C,'c',0x80017004,match=True)],ROOT/'work','dungeon_test',ROOT)

if __name__=='__main__':unittest.main()
