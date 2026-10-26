"""Separating prefix rows preserves historical code and native object ownership."""
import copy,json,sys,tempfile,unittest
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'tools/gate'))
import overlay_prefix_ownership as Q
class PrefixSeparation(unittest.TestCase):
 def setUp(self):
  self.tmp=tempfile.TemporaryDirectory(dir=ROOT/'work');self.addCleanup(self.tmp.cleanup);self.root=Path(self.tmp.name)
  self.before=dict(id='dungeon/first',source='owner.c',function='first',foff=0x100,vma=0x80010100,size=28,body_offset=12)
  first=dict(self.before,foff=0x10c,vma=0x8001010c,size=16);first.pop('body_offset')
  self.m=dict(key='owner',prefix_provenance='prefix.json',review_inputs=['prefix.json'],membership_evidence='membership.json',members=[first],data_members=[dict(id='dungeon/pointer',foff=0x100,vma=0x80010100),dict(id='dungeon/switch',foff=0x104,vma=0x80010104)],owned_data=[dict(kind='typed_function_pointer',target='first',size=4),dict(kind='switch_table',owner='first',size=8)])
  self.proof=dict(schema='native-prefix-separation-v1',module='owner',membership_evidence='membership.json',original_member=self.before,basis=['Unchanged whole native owner.'])
  self.rows={n:dict(row_kind='data',data_kind='native_prefix',ownership_status='evidenced',owner='dungeon/first') for n in ['dungeon/pointer','dungeon/switch']}
  self.write()
 def write(self):(self.root/'prefix.json').write_text(json.dumps(self.proof))
 def test_complete_separation(self):Q.validate(self.m,self.rows,self.root)
 def test_shifted_or_shortened_code_rejected(self):
  for field in ['foff','vma','size']:
   m=copy.deepcopy(self.m);m['members'][0][field]+=4
   with self.subTest(field=field),self.assertRaisesRegex(ValueError,'complete code body'):Q.validate(m,self.rows,self.root)
 def test_foreign_data_owners_and_missing_records_rejected(self):
  rows=copy.deepcopy(self.rows);rows['dungeon/pointer']['owner']='dungeon/other'
  with self.assertRaisesRegex(ValueError,'registry owner'):Q.validate(self.m,rows,self.root)
  self.m['data_members'].pop()
  with self.assertRaisesRegex(ValueError,'record count'):Q.validate(self.m,self.rows,self.root)
 def test_unfingerprinted_or_changed_provenance_rejected(self):
  self.m['review_inputs']=[]
  with self.assertRaisesRegex(ValueError,'provenance'):Q.validate(self.m,self.rows,self.root)
 def test_prefix_cannot_create_a_different_historical_code_identity(self):
  self.proof['original_member']['id']='dungeon/other';self.write()
  with self.assertRaisesRegex(ValueError,'complete code body'):Q.validate(self.m,self.rows,self.root)
if __name__=='__main__':unittest.main()
