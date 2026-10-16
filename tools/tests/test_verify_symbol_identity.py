import tempfile,sys,unittest,shutil
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2];sys.path.insert(0,str(ROOT/'tools'))
from verify import normalise_definition
class SymbolIdentityTests(unittest.TestCase):
 def check(self,text,row,changed=True):
  with tempfile.TemporaryDirectory() as td:
   p=Path(td)/'source.c';p.write_text(text);q=normalise_definition(row,p);actual=q.read_text()
   self.assertEqual(p.read_text(),text)
   if changed:self.assertNotEqual(q,p);shutil.rmtree(q.parent)
   else:self.assertEqual(q,p)
   return actual
 def test_unproven_metadata_definition_gets_scorer_identity_only(self):
  row=dict(func='func_80000000',true_name='func_80000020',placement='unproven')
  s='/* func_80000020 */\nint func_80000020(void){char *s="func_80000020";return 1;}\n'
  actual=self.check(s,row);self.assertIn('int func_80000000(void)',actual);self.assertIn('/* func_80000020 */',actual);self.assertIn('"func_80000020"',actual)
 def test_unbound_body_token_is_a_temporary_identity(self):
  s='int FUNC_80000000_BODY(void){return 1;}\n';actual=self.check(s,dict(func='func_80000000',true_name='func_80000100'));self.assertIn('int func_80000000(void)',actual)
 def test_bound_macro_and_composite_prefix_are_preserved(self):
  s='#define FUNC_80000000_BODY func_80000020\nint FUNC_80000000_BODY(void){return 1;}\n';self.check(s,dict(func='func_80000000',true_name='func_80000020'),False)
  s='const int func_80000000=0;\nint func_80000020(void){return 1;}\n';self.check(s,dict(func='func_80000000',true_name='func_80000020',placement='unproven'),False)
if __name__=='__main__':unittest.main()
