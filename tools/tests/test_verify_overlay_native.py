import tempfile,unittest,sys
from pathlib import Path
from unittest.mock import patch
ROOT=Path(__file__).resolve().parents[2];sys.path.insert(0,str(ROOT/'tools'))
import verify_overlay_native as V
class NativeProofTests(unittest.TestCase):
 def setUp(self):
  self.t=tempfile.TemporaryDirectory();self.addCleanup(self.t.cleanup);self.r=Path(self.t.name)
  (self.r/'include').mkdir();(self.r/'src').mkdir();self.p=self.r/'src/member.c';self.p.write_text('int f(void){return 1;}')
  self.row=dict(id='town/member',kind='overlay',container='town',c_path='member.c')
  self.m=dict(key='test',members=[dict(id='town/member',source='src/member.c'),dict(id='town/other',source='src/other.c')])
  V._CACHE.clear()
 def run_proof(self,receipt=None,candidate=None):
  receipt=receipt or dict(gate={'result':'MATCH'},genuine={'result':'MATCH'},members=['town/member','town/other'])
  def build(m,out,view,subs):
   b=out/'module.bin';b.write_bytes(b'bytes');return receipt,b
  with patch.object(V.G,'load_modules',return_value=[self.m]),patch.object(V.G,'fingerprint',return_value={'sha256':'context'}),patch.object(V.G,'build',side_effect=build) as b:
   result=V.verify_member(self.row,candidate or self.p,self.r,self.r,self.r/'include')
   return result,b.call_count
 def test_complete_proof_is_exact(self):
  result,count=self.run_proof();self.assertTrue(result['exact']);self.assertEqual(count,1)
 def test_incomplete_genuine_proof_is_refused(self):
  with self.assertRaisesRegex(ValueError,'incomplete'):self.run_proof(dict(gate={'result':'MATCH'},genuine={'result':'NO MATCH'},members=['town/member']))
 def test_candidate_must_be_bound(self):
  p=self.r/'candidate.c';p.write_text('int f(void){return 2;}')
  with self.assertRaisesRegex(ValueError,'not bound'):self.run_proof(candidate=p)
 def test_foreign_headers_are_not_measured(self):
  with patch.object(V.G,'load_modules') as load:
   self.assertIsNone(V.verify_member(self.row,self.p,self.r,self.r,self.r/'other-include'));load.assert_not_called()
 def test_unowned_row_has_no_fallback(self):
  with patch.object(V.G,'load_modules',return_value=[]):self.assertIsNone(V.verify_member(self.row,self.p,self.r,self.r))
if __name__=='__main__':unittest.main()
