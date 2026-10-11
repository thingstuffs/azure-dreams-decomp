"""Strict carved data prefix boundaries: no fictional function or missing byte."""
import copy,importlib.util,sys,unittest,tempfile
from pathlib import Path
G=Path(__file__).resolve().parents[1]/'gate';sys.path.insert(0,str(G))
import overlay_native_rodata as N
import overlay_module_gate as M
class PrefixRows(unittest.TestCase):
 def module(self):
  return dict(membership_evidence='proof.json',data_members=[dict(foff=100,vma=1000,size=4)],members=[dict(foff=104,vma=1004,size=8,function='func_000003EC')],owned_data=[dict(section='.rodata',foff=100,vma=1000,size=4,kind='typed_function_pointer',symbol='entry',target='func_000003EC')])
 def test_separate_prefix_preserves_function_extent(self):N.validate_layout(self.module())
 def test_gap_rejected(self):
  m=self.module();m['members'][0]['foff']+=4
  with self.assertRaises(ValueError):N.validate_layout(m)
 def test_wrong_vma_rejected(self):
  m=self.module();m['members'][0]['vma']+=4
  with self.assertRaises(ValueError):N.validate_layout(m)
 def test_double_counted_body_offset_rejected(self):
  m=self.module();m['members'][0]['body_offset']=4
  with self.assertRaises(ValueError):N.validate_layout(m)
 def test_pointer_cannot_target_data(self):
  m=self.module();m['owned_data'][0]['target']='entry'
  with self.assertRaises(ValueError):N.validate_layout(m)
 def test_uncompiled_data_candidate_fails_before_build(self):
  m=self.module();m['data_members'][0]['source']='data.c'
  with tempfile.TemporaryDirectory() as d:
   with self.assertRaisesRegex(ValueError,'prefix data candidate'):
    M.build(m,Path(d)/'out',Path(d),{'data.c':str(Path(d)/'invalid.c')})
 def test_nonmember_candidate_fails_before_build(self):
  m=self.module();m['members'][0]['source']='function.c';m['data_members'][0]['source']='data.c'
  with tempfile.TemporaryDirectory() as d:
   with self.assertRaisesRegex(ValueError,'not a function member'):
    M.build(m,Path(d)/'out',Path(d),{'other.c':str(Path(d)/'invalid.c')})
if __name__=='__main__':unittest.main()
