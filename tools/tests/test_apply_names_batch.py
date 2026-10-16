import unittest,tempfile,sys,json,contextlib,io
from pathlib import Path
from unittest.mock import patch
ROOT=Path(__file__).resolve().parents[2];sys.path.insert(0,str(ROOT/'tools'))
import apply_names as N
class BatchTests(unittest.TestCase):
 def case(self,bad=False,dry=False):
  with tempfile.TemporaryDirectory() as td:
   r=Path(td)
   for d in ['config','ledger','include','src/town/modules','src/dungeon']:(r/d).mkdir(parents=True)
   table=r/'config/names.tsv';table.write_text('# aliases\n');journal=r/'ledger/names.jsonl'
   h=r/'include/api.h';h.write_text('int func_80000000(void);\n')
   a=r/'src/town/a.c';a.write_text('#include "api.h"\nint func_80000000(void){return 1;}\n')
   b=r/'src/town/b.c';b.write_text('#include "api.h"\nint func_80000004(void){return func_80000000();}\n')
   wrapper=r/'src/town/modules/test.c';wrapper.write_text('#include "../func_80000000.c"\nint (*p)(void)=func_80000000;\n')
   proposal=r/'p.tsv';proposal.write_text('0x80000000\tfunc_80000000\tfirstName\tknowledge/a\n0x80000004\tfunc_80000004\tsecondName\tknowledge/b\n')
   rows=[dict(id='town/a',func='func_80000000',container='town',c_path='a.c'),dict(id='town/b',func='func_80000004',container='town',c_path='b.c')]
   originals={p:p.read_bytes() for p in [table,h,a,b,wrapper]};checked=[]
   def verify(row,path,include_root=None):checked.append(row['id']);return {'exact':not bad,'status':'ok'}
   argv=['apply_names.py',str(proposal),'--batch']+(['--dry-run'] if dry else [])
   with patch.multiple(N,ROOT=r,NAMES=table,JOURNAL=journal,INCLUDE=r/'include'),patch.object(N,'rows',return_value=rows),patch.object(N,'verify',side_effect=verify),patch.object(sys,'argv',argv),contextlib.redirect_stdout(io.StringIO()):
    if bad:
     with self.assertRaisesRegex(ValueError,'not exact'):N.main()
    else:N.main()
   if bad or dry:
    for p,t in originals.items():self.assertEqual(p.read_bytes(),t)
   else:
    self.assertEqual(sorted(checked),['town/a','town/b']);self.assertIn('firstName',h.read_text());self.assertIn('secondName',b.read_text())
    self.assertIn('#include "../func_80000000.c"',wrapper.read_text());self.assertIn('=firstName;',wrapper.read_text())
    self.assertEqual(len([l for l in journal.read_text().splitlines() if json.loads(l)['outcome']=='applied']),2)
 def test_comments_and_string_anchors_are_preserved_in_headers(self):
  from apply_names_batch import rewrite
  import re
  source='/* func_80000000 */\nchar *label="func_80000000";\nint func_80000000(void);\n'
  result=rewrite(source,re.compile(r'\bfunc_80000000\b'),{'func_80000000':'readable'},True)
  self.assertEqual(result,'/* func_80000000 */\nchar *label="func_80000000";\nint readable(void);\n')
 def test_complete_batch_and_stable_include_stems(self):self.case()
 def test_one_failed_row_rolls_back_the_whole_batch(self):self.case(bad=True)
 def test_dry_run_writes_nothing(self):self.case(dry=True)
if __name__=='__main__':unittest.main()
