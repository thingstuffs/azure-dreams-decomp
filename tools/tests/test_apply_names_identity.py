"""Explicit function identities cannot redirect a rename through stale metadata."""
import contextlib,io,json,sys,tempfile,unittest
from pathlib import Path
from unittest.mock import patch
ROOT=Path(__file__).resolve().parents[2];sys.path.insert(0,str(ROOT/'tools'))
import apply_names as N
class IdentityTests(unittest.TestCase):
 def run_case(self,symbol='func_80000000',merged=False):
  with tempfile.TemporaryDirectory() as td:
   r=Path(td)
   for d in ['config','ledger','include','src/town','src/dungeon']:(r/d).mkdir(parents=True)
   names=r/'config/names.tsv';names.write_text('# aliases\n');journal=r/'ledger/names.jsonl'
   source=r/'src/town/func_80000000.c';source.write_text('int func_80000000(void) { return 1; }\n')
   other=r/'src/dungeon/func_80000000.c';other.write_text('int func_80001100(void) { return 2; }\n')
   proposal=r/'proposal.tsv';proposal.write_text('0x80000000\tfunc_80000000\treadableName\tknowledge/test\n')
   identity=r/'identity.json';identity.write_text(json.dumps({'func_80000000':{'row':'town/func_80000000','symbol':symbol}}))
   if merged:
    moved=r/'src/town/merged.c';source.rename(moved);source=moved
    (r/'ledger/layout.jsonl').write_text(json.dumps(dict(id='town/func_80000000',path='src/town/merged.c'))+'\n')
   rows=[dict(id='town/func_80000000',container='town',c_path=str(r/'src/town/func_80000000.c'),func='func_80000000',true_name='func_80002200'),dict(id='dungeon/func_80000000',container='dungeon',c_path=str(other),func='func_80000000',true_name='func_80001100')]
   if merged:(r/'ledger/rows.jsonl').write_text(''.join(json.dumps(x)+'\n' for x in rows))
   checked=[]
   def verify(row,p,include_root=None):checked.append(row['id']);return {'exact':True}
   with patch.multiple(N,ROOT=r,NAMES=names,JOURNAL=journal,INCLUDE=r/'include'),patch.object(N,'rows',return_value=rows),patch.object(N,'verify',side_effect=verify),patch.object(sys,'argv',['apply_names.py',str(proposal),'--identity-map',str(identity)]),contextlib.redirect_stdout(io.StringIO()):
    if symbol!='func_80000000':
     with self.assertRaisesRegex(ValueError,'current C definition'):N.main()
     self.assertEqual(source.read_text(),'int func_80000000(void) { return 1; }\n');self.assertEqual(names.read_text(),'# aliases\n');return
    N.main()
   self.assertEqual(checked,['town/func_80000000']);self.assertIn('readableName',source.read_text());self.assertIn('func_80001100',other.read_text())
   self.assertIn('0x80000000\tfunc_80000000\treadableName',names.read_text());self.assertEqual(json.loads(journal.read_text())['identity_row'],'town/func_80000000')
 def test_actual_definition_wins_with_explicit_identity(self):self.run_case()
 def test_merged_definition_uses_layout_path(self):self.run_case(merged=True)
 def test_merged_stale_symbol_is_refused(self):self.run_case('func_80002200',merged=True)
 def test_stale_metadata_symbol_is_refused(self):self.run_case('func_80002200')
 def test_invalid_symbol_is_refused(self):self.run_case('../escape')
if __name__=='__main__':unittest.main()
