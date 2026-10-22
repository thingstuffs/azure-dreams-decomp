import unittest,tempfile,sys,json,contextlib,io
from pathlib import Path
from unittest.mock import patch
ROOT=Path(__file__).resolve().parents[2];sys.path.insert(0,str(ROOT/'tools'))
import apply_names as N
class BatchTests(unittest.TestCase):
 def test_unchanged_replay_preserves_alias_table_timestamp(self):
  with tempfile.TemporaryDirectory() as td:
   r=Path(td)
   for d in ['config','ledger','include','src/town']:(r/d).mkdir(parents=True)
   names=r/'config/names.tsv';names.write_text('0x80000000\tfunc_80000000\treadable\tevidence\n')
   source=r/'src/town/home.c';source.write_text('int readable(void){return 1;}\n')
   proposal=r/'p.tsv';proposal.write_text('0x80000000\tfunc_80000000\treadable\tevidence\n')
   identity=r/'identity.json';identity.write_text(json.dumps({'func_80000000':{'row':'town/home','symbol':'func_80000000'}}))
   rows=[dict(id='town/home',func='func_80000000',container='town',c_path='home.c')]
   before={p:(p.read_bytes(),p.stat().st_mtime_ns) for p in [names,source]}
   argv=['apply_names.py',str(proposal),'--batch','--defer-verification','--identity-map',str(identity)]
   with patch.multiple(N,ROOT=r,NAMES=names,JOURNAL=r/'ledger/names.jsonl',INCLUDE=r/'include'),patch.object(N,'rows',return_value=rows),patch.object(sys,'argv',argv),contextlib.redirect_stdout(io.StringIO()):N.main()
   self.assertEqual(before,{p:(p.read_bytes(),p.stat().st_mtime_ns) for p in before})
 def test_symbol_scope_preserves_a_reused_address_in_the_same_folder(self):
  with tempfile.TemporaryDirectory() as td:
   r=Path(td)
   for d in ['config','ledger','include/town','src/town']:(r/d).mkdir(parents=True)
   names=r/'config/names.tsv';names.write_text('# aliases\n')
   home=r/'src/town/a.c';home.write_text('int func_80000000(void){return 1;}\n')
   second=r/'src/town/b.c';second.write_text('int func_80000004(void){return 2;}\n')
   other=r/'src/town/other.c';other.write_text('int func_80000000(void); int caller(void){return func_80000000()+func_80000004();}\n')
   header=r/'include/town/api.h';header.write_text('int func_80000000(void);\n')
   proposal=r/'p.tsv';proposal.write_text('0x80000000\tfunc_80000000\tlocal_name\tlocal body\n0x80000004\tfunc_80000004\tbroad_name\tother body\n')
   scopes=r/'scopes.json';scopes.write_text(json.dumps({'func_80000000':['src/town/a.c','include/town/api.h']}))
   identity=r/'identity.json';identity.write_text(json.dumps({'func_80000000':{'row':'town/a','symbol':'func_80000000'}}))
   rows=[dict(id='town/a',func='func_80000000',container='town',c_path='a.c'),dict(id='town/b',func='func_80000004',container='town',c_path='b.c')]
   argv=['apply_names.py',str(proposal),'--batch','--defer-verification','--identity-map',str(identity),'--symbol-scope-map',str(scopes),'--path-prefix','src/town','--path-prefix','include/town']
   with patch.multiple(N,ROOT=r,NAMES=names,JOURNAL=r/'ledger/names.jsonl',INCLUDE=r/'include'),patch.object(N,'rows',return_value=rows),patch.object(sys,'argv',argv),contextlib.redirect_stdout(io.StringIO()):
    N.main()
    self.assertIn('int local_name(void)',home.read_text());self.assertIn('int local_name(void);',header.read_text())
    self.assertIn('return func_80000000()+broad_name();',other.read_text())
    before={p:p.read_bytes() for p in [names,home,second,other,header]}
    scopes.write_text(json.dumps({'func_80000000':['src/town/other.c']}))
    with self.assertRaisesRegex(ValueError,'scope excludes its definition'):N.main()
    self.assertEqual(before,{p:p.read_bytes() for p in before})
 def test_exact_existing_alias_normalizes_legacy_definition_in_merged_file(self):
  with tempfile.TemporaryDirectory() as td:
   r=Path(td)
   for d in ['config','ledger','include','src/town']:(r/d).mkdir(parents=True)
   names=r/'config/names.tsv';names.write_text('0x80000000\tfunc_80000000\treadable\tevidence\n')
   source=r/'src/town/merged.c';source.write_text('int sibling(void){return 2;}\nint func_80000000(void){return 1;}\n')
   proposal=r/'p.tsv';proposal.write_text('0x80000000\tfunc_80000000\treadable\tevidence\n')
   identity=r/'identity.json';identity.write_text(json.dumps({'func_80000000':{'row':'town/merged','symbol':'func_80000000'}}))
   rows=[dict(id='town/merged',func='func_80000000',container='town',c_path='merged.c')]
   before=names.read_bytes()
   argv=['apply_names.py',str(proposal),'--batch','--defer-verification','--identity-map',str(identity)]
   with patch.multiple(N,ROOT=r,NAMES=names,JOURNAL=r/'ledger/names.jsonl',INCLUDE=r/'include'),patch.object(N,'rows',return_value=rows),patch.object(sys,'argv',argv),contextlib.redirect_stdout(io.StringIO()):N.main()
   self.assertIn('int readable(void)',source.read_text())
   self.assertIn('int sibling(void){return 2;}',source.read_text())
   self.assertEqual(names.read_bytes(),before)
 def test_scoped_batch_keeps_legacy_callers_and_headers(self):
  with tempfile.TemporaryDirectory() as td:
   r=Path(td)
   for d in ['config','ledger','include/town','include/dungeon','src/town','src/dungeon']:(r/d).mkdir(parents=True)
   names=r/'config/names.tsv';names.write_text('# aliases\n')
   home=r/'src/town/home.c';home.write_text('int func_80000000(void){return 1;}\n')
   caller=r/'src/dungeon/caller.c';caller.write_text('int func_80000000(void); int caller(void){return func_80000000();}\n')
   header=r/'include/town/api.h';header.write_text('int func_80000000(void);\n')
   other=r/'include/dungeon/api.h';other.write_text(header.read_text())
   original={p:p.read_bytes() for p in [caller,other]}
   proposal=r/'p.tsv';proposal.write_text('0x80000000\tfunc_80000000\treadable\treturns one\n')
   rows=[dict(id='town/home',func='func_80000000',container='town',c_path='home.c')]
   argv=['apply_names.py',str(proposal),'--batch','--defer-verification','--path-prefix','src/town','--path-prefix','include/town']
   with patch.multiple(N,ROOT=r,NAMES=names,JOURNAL=r/'ledger/names.jsonl',INCLUDE=r/'include'),patch.object(N,'rows',return_value=rows),patch.object(sys,'argv',argv),contextlib.redirect_stdout(io.StringIO()):N.main()
   self.assertIn('readable',home.read_text());self.assertIn('readable',header.read_text())
   for p,t in original.items():self.assertEqual(p.read_bytes(),t)
   self.assertIn('func_80000000\treadable',names.read_text())
 def test_scope_rejects_escape_and_matches_path_components(self):
  r=Path('/repo');texts={r/'src/town/a.c':'a',r/'src/township/a.c':'b'}
  self.assertEqual(N.scoped_texts(texts,['src/town'],r),{r/'src/town/a.c':'a'})
  for prefix in ['../src','src/../include','/src/town','config']:
   with self.assertRaises(ValueError):N.scoped_texts(texts,[prefix],r)
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
