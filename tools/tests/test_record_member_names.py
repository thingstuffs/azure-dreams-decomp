import sys,unittest,tempfile
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2];sys.path.insert(0,str(ROOT/'tools'))
from record_member_names import rename_generated,load_names
class RecordNameTests(unittest.TestCase):
 def test_nested_views_and_accessor_roots_are_preserved(self):
  lines=['    union { struct { int unk_00; } view; int v; } unk_00;', '    int unk_04;']
  paths={(0,'int'):'unk_00.view.unk_00',(4,'int'):'unk_04'}
  after,access=rename_generated('Rec_Test',lines,paths,{'Rec_Test':{'unk_00':'position','unk_04':'state'}})
  self.assertEqual(after,['    union { struct { int unk_00; } view; int v; } position;','    int state;'])
  self.assertEqual(access[(0,'int')],'position.view.unk_00');self.assertEqual(access[(4,'int')],'state')
 def test_missing_named_offset_refuses_regeneration(self):
  with self.assertRaisesRegex(ValueError,'layout changed'):rename_generated('Rec_Test',['    int unk_04;'],{}, {'Rec_Test':{'unk_00':'position'}})
 def test_absent_table_preserves_generation(self):
  with tempfile.TemporaryDirectory() as td:self.assertEqual(load_names(td),{})
 def test_generator_consumes_names(self):
  import gen_records
  from unittest.mock import patch
  structs={'x':dict(layout={'0x0':'s32'},container='town',row='town/x',base='D_80000000',fn='func_80000000')}
  with patch('record_member_names.load_names',return_value={'Rec_D_80000000':{'unk_00':'state'}}):
   header,paths,_,_=gen_records.build('global:D_80000000',['x'],structs)
  self.assertIn('s32 state;',header);self.assertEqual(paths['x']['0x0'],'state')
if __name__=='__main__':unittest.main()
