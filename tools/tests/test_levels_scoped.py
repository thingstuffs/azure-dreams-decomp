"""The bank scope used for level accounting must agree with production compilation."""
import json,sys,tempfile,unittest
from pathlib import Path
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]))
import levels as L
from gate import gen_noreturn_syms as G

class ScopedLevelTests(unittest.TestCase):
    def test_real_returning_call_is_not_a_foreign_bank_tail(self):
        root=Path(__file__).resolve().parents[2]
        rows={r['id']:r for r in map(json.loads,(root/'ledger/rows.jsonl').read_text().splitlines())}
        r=rows['dungeon/func_81874F04'];text=(root/'src/dungeon/func_81874F04.c').read_text()
        self.assertIn('func_80024188',(root/'config/noreturn_syms.dungeon.txt').read_text())
        self.assertNotIn('func_80024188',G.scoped_census('dungeon',r['foff'],root=root)['names'])
        with patch.object(L,'ROOT',root):self.assertEqual(L.tail_jump_targets(r,text),[])
    def test_explicit_noreturn_survives_empty_scoped_census(self):
        r={'container':'dungeon','foff':0x1894f04}
        with patch.object(G,'scoped_census',return_value={'names':set()}):
            self.assertIn('func_80024188',L.tail_jump_targets(r,'extern void func_80024188(void) __attribute__((noreturn));\nvoid f(void) {\n    func_80024188();\n}'))
    def test_row_offset_and_root_pass_through(self):
        r={'container':'dungeon_engine','foff':0x1234}
        with patch.object(G,'scoped_census',return_value={'names':{'func_80024560'}}) as c:
            self.assertIn('func_80024560',L.row_tail_syms(r));c.assert_called_once_with('dungeon',0x1234,root=L.ROOT)
    def test_sibcalls_stay_family_scoped(self):
        with tempfile.TemporaryDirectory() as td:
            root=Path(td);(root/'config').mkdir();(root/'config/sibcall_syms.town.txt').write_text('func_80016060 # real tail\n')
            with patch.object(L,'ROOT',root),patch.object(G,'scoped_census',return_value={'names':set()}):
                self.assertEqual(L.row_tail_syms({'container':'town','foff':4}),{'func_80016060'})
    def test_nonbanked_and_synthetic_rows_keep_old_policy(self):
        for r in [{'container':'main','foff':4},{'container':'dungeon'}]:
            with patch.object(L,'container_tail_syms',return_value={'func_80001234'}) as c:
                self.assertEqual(L.row_tail_syms(r),{'func_80001234'});c.assert_called_once_with(r['container'])
if __name__=='__main__':unittest.main()
