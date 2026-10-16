"""Uniform native recipe admission binds the actual compiler and complete flag order."""
import importlib.util,sys,unittest,os,tempfile
from pathlib import Path
R=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(R/'tools/gate'))
spec=importlib.util.spec_from_file_location('recipe_selection_gate',R/'tools/gate/overlay_module_gate.py')
G=importlib.util.module_from_spec(spec);sys.modules[spec.name]=G;spec.loader.exec_module(G)
class NativeRecipeSelection(unittest.TestCase):
 def test_ovmovie_noreturn_content_and_absence_bound(self):
  import overlay_scoped_fingerprint as F
  with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR',str(R/'work'))) as td:
   root=Path(td);p=root/'config/noreturn_syms.ovmovie.txt';p.parent.mkdir(parents=True)
   missing=F.noreturn(root,'ovmovie',[],{},[],G)
   p.write_text('func_80177838\n');present=F.noreturn(root,'ovmovie',[],{},[],G)
   p.write_text('func_80177844\n');changed=F.noreturn(root,'ovmovie',[],{},[],G)
   self.assertNotEqual(missing,present);self.assertNotEqual(present,changed)
   p.unlink();self.assertEqual(missing,F.noreturn(root,'ovmovie',[],{},[],G))
 def test_ordinary_compilers(self):
  self.assertEqual(G.module_compiler({'recipe':{'cfg':'2.7.2-cdk-G0','row_asflags':''}}),'2.7.2-cdk')
  self.assertEqual(G.module_compiler({'recipe':{'cfg':'2.7.2-G0','row_asflags':''}}),'2.7.2')
 def test_uniform_o1_uses_recorded_override_order(self):
  m={'recipe':{'cfg':'2.7.2-cdk-G0 -O1','row_asflags':''}}
  self.assertEqual(G.module_compiler(m),'2.7.2-cdk')
  self.assertEqual(G.module_cflags(m),['-O2','-G0','-O1'])
  for cfg in ['2.7.2-cdk-G0','2.7.2-G0']:
   self.assertEqual(G.module_cflags({'recipe':{'cfg':cfg,'row_asflags':''}}),['-O2','-G0'])
 def test_flags_and_extra_keys_refused(self):
  recipes=[{'cfg':'2.7.2-cdk-G0 -O1','row_asflags':'-0'},{'cfg':'2.7.2-cdk-G0 -O1 -fno-gcse','row_asflags':''},{'cfg':'2.7.2','row_asflags':''},{'cfg':'2.7.2-G0 -fno-schedule-insns','row_asflags':''},{'cfg':'2.8.1-G0','row_asflags':''},{'cfg':'2.7.2-G0','row_asflags':'--expand-div'},{'cfg':'2.7.2-G0','row_asflags':'','extra':True}]
  for recipe in recipes:
   with self.subTest(recipe=recipe),self.assertRaisesRegex(ValueError,'unsupported recipe'):G.module_compiler({'recipe':recipe})
 def test_stock_projection_never_accepts_cdk_spelling(self):
  m={'recipe':{'cfg':'2.7.2-G0','row_asflags':''}}
  self.assertEqual(m['recipe']['cfg'].replace('-G0',' -G0'),'2.7.2 -G0')
  self.assertNotEqual(m['recipe']['cfg'].replace('-G0',' -G0'),'2.7.2-cdk -G0')
if __name__=='__main__':unittest.main()
