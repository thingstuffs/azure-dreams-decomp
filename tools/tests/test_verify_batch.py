import tempfile,unittest,sys
from pathlib import Path
from unittest.mock import patch
ROOT=Path(__file__).resolve().parents[2];sys.path.insert(0,str(ROOT/'tools'))
import verify_batch as V
from gate import overlay_module_gate as G
class CompleteBatchTests(unittest.TestCase):
 def case(self,omit=False):
  with tempfile.TemporaryDirectory() as td:
   root=Path(td);(root/'config/overlays').mkdir(parents=True);(root/'config/overlays/modules.json').write_text('{}')
   rows=[dict(id='town/'+n,kind='overlay',container='town',c_path=n+'.c') for n in ['a','b','c']]
   module=dict(key='native',members=[dict(id=r['id'],source='src/'+r['id']+'.c') for r in rows])
   def build(m,out,view):
    p=out/'module.bin';p.write_bytes(b'exact bytes')
    return dict(gate={'result':'MATCH'},genuine={'result':'MATCH'},members=[r['id'] for r in rows][:-1] if omit else [r['id'] for r in rows],fingerprint={'sha256':'bound'}),p
   with patch('verify.gate_root',return_value=root),patch.object(G,'load_modules',return_value=[module]),patch.object(G,'build',side_effect=build) as compiled:
    result=list(V.measure(rows,3,lambda *a,**k: self.fail('isolated verifier called'),root))
   self.assertEqual(compiled.call_count,1);self.assertEqual({r[0] for r in result},{r['id'] for r in rows})
   self.assertEqual([r[1]['exact'] for r in result],[not omit]*3)
 def test_one_complete_tu_proves_all_its_members(self):self.case()
 def test_missing_member_refuses_group_proof(self):self.case(omit=True)
 def test_context_invalidates_on_source_change(self):
  with tempfile.TemporaryDirectory() as td:
   root=Path(td);(root/'src/town').mkdir(parents=True);p=root/'src/town/a.c';p.write_text('int f(void){return 1;}')
   first=V.context(root);p.write_text('int f(void){return 2;}');self.assertNotEqual(first,V.context(root))
if __name__=='__main__':unittest.main()
