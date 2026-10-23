"""Reused runtime function addresses retain independent overlay identities."""
import contextlib
import io
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import apply_names as N


class FunctionBankTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        for d in ('config', 'ledger', 'src/dungeon', 'include/dungeon'):
            (self.root/d).mkdir(parents=True)
        self.a, self.b = [self.root/('src/dungeon/'+n+'.c') for n in ('a','b')]
        self.h = self.root/'include/dungeon/effects.h'
        self.a.write_text('/* func_80024020 */\nvoid func_80024020(void) {}\n'
                          'char *label="func_80024020";\n')
        self.b.write_text('void func_80024020(void) { return; }\n')
        self.h.write_text('void func_80024020(void);\n')
        self.table = self.root/'config/names.tsv'
        self.table.write_text('0x80024020\tfunc_80024020\tprior_bank\tprior evidence\n')
        self.tsv, self.scopes, self.ids = [self.root/n for n in ('names.tsv','scopes.json','ids.json')]
        self.tsv.write_text('0x80024020\tfunc_80024020\tfirst_bank\tfirst evidence\n'
                            '0x80024020\tfunc_80024020\tsecond_bank\tsecond evidence\n')
        self.scope_data = {'first_bank':['src/dungeon/a.c','include/dungeon/effects.h'],
                           'second_bank':['src/dungeon/b.c']}
        self.scopes.write_text(json.dumps(self.scope_data))
        self.identity_data = {n:dict(row='dungeon/'+f,symbol='func_80024020')
                              for n,f in [('first_bank','a'),('second_bank','b')]}
        self.ids.write_text(json.dumps(self.identity_data))
        self.rows = [dict(id='dungeon/'+n, container='dungeon', func='func_80024020',
                          c_path=str(p)) for n,p in [('a',self.a),('b',self.b)]]

    def run_names(self, *extra, scope_option='--symbol-scope-map'):
        argv = ['apply_names.py',str(self.tsv),'--batch','--defer-verification',
                '--identity-map',str(self.ids),scope_option,str(self.scopes),*extra]
        with patch.multiple(N,ROOT=self.root,NAMES=self.table,JOURNAL=self.root/'ledger/names.jsonl'), \
             patch.object(N,'rows',return_value=self.rows), \
             patch('apply_names_functions_scoped.own_source',side_effect=lambda r,*_: (Path(r['c_path']).read_text(),None)), \
             patch('apply_names_functions_scoped.consumer_paths',return_value=set()), \
             patch('apply_names_functions_scoped.row_ids_for_paths',return_value=set()), \
             patch.object(sys,'argv',argv),contextlib.redirect_stdout(io.StringIO()):
            return N.main()

    def snapshot(self):
        return {p:p.read_bytes() for p in (self.a,self.b,self.h,self.table)}

    def test_independent_bank_definitions_and_prototype_replay(self):
        self.run_names()
        after = self.snapshot()
        self.run_names(scope_option='--scope-map')
        self.assertEqual(after,self.snapshot())
        self.assertIn('void first_bank(void)',self.a.read_text())
        self.assertIn('/* func_80024020 */',self.a.read_text())
        self.assertIn('"func_80024020"',self.a.read_text())
        self.assertIn('void second_bank(void)',self.b.read_text())
        self.assertEqual(self.h.read_text(),'void first_bank(void);\n')
        self.assertEqual(self.table.read_text().count('\tfunc_80024020\t'),3)
        self.assertIn('\tprior_bank\t',self.table.read_text())

    def test_ccproc_canonicalizes_both_names_to_original_address(self):
        self.run_names()
        ccproc=Path(N.__file__).parent/'build/ccproc.py'
        for name in ('prior_bank','first_bank','second_bank'):
            result=subprocess.run([sys.executable,str(ccproc),'--names-tsv',str(self.table)],
                input=f'\t.ent {name}\n{name}:\n\tjal {name}\n\t.end {name}\n',
                capture_output=True,text=True,check=True)
            self.assertIn('.section .text.func_80024020',result.stdout)
            self.assertIn('jal func_80024020',result.stdout)
            self.assertNotIn(name,result.stdout)

    def test_overlap_and_missing_scope_fail_before_writes_even_with_limit(self):
        for data in ({}, {'first_bank':['src/dungeon/a.c'], 'second_bank':['src/dungeon/a.c']}):
            self.scopes.write_text(json.dumps(data))
            before=self.snapshot()
            with self.assertRaises(ValueError):self.run_names('--limit','1')
            self.assertEqual(before,self.snapshot())

    def test_limit_keeps_other_bank_and_existing_alias(self):
        before=self.b.read_bytes()
        self.run_names('--limit','1')
        self.assertEqual(self.b.read_bytes(),before)
        self.assertNotIn('\tsecond_bank\t',self.table.read_text())
        self.run_names()
        self.assertIn('second_bank',self.b.read_text())

    def test_overlapping_valid_definition_scopes_refuse(self):
        self.scopes.write_text(json.dumps({**self.scope_data,
            'second_bank':['src/dungeon/a.c','src/dungeon/b.c']}))
        before=self.snapshot()
        with self.assertRaisesRegex(ValueError,'overlapping bank scopes'):
            self.run_names('--limit','1')
        self.assertEqual(before,self.snapshot())

    def test_stale_row_metadata_does_not_substitute_for_a_definition(self):
        self.a.write_text('void unrelated(void) {}\n')
        before=self.snapshot()
        with self.assertRaisesRegex(ValueError,'current definition'):
            self.run_names()
        self.assertEqual(before,self.snapshot())

    def test_definition_identity_is_mandatory_and_cannot_redirect(self):
        for data in ({}, {'first_bank':dict(row='dungeon/a',symbol='func_80024024')},
                     {**self.identity_data,'first_bank':dict(row='dungeon/b',symbol='func_80024020')}):
            self.ids.write_text(json.dumps(data))
            before=self.snapshot()
            with self.assertRaises(ValueError):self.run_names()
            self.assertEqual(before,self.snapshot())

    def test_unsafe_unknown_and_empty_paths_refuse(self):
        for paths in ([],['../src/a.c'],['/src/a.c'],['src/dungeon/missing.c'],['src//dungeon/a.c']):
            self.scopes.write_text(json.dumps({**self.scope_data,'first_bank':paths}))
            before=self.snapshot()
            with self.assertRaises(ValueError):self.run_names()
            self.assertEqual(before,self.snapshot())

    def test_collision_refuses_atomically(self):
        self.b.write_text(self.b.read_text()+'int first_bank;\n')
        before=self.snapshot()
        with self.assertRaisesRegex(ValueError,'collision'):self.run_names()
        self.assertEqual(before,self.snapshot())

    def test_failed_receipt_write_rolls_back_sources_aliases_and_journal(self):
        before=self.snapshot()
        with self.assertRaises(OSError):
            self.run_names('--proof-log',str(self.root/'missing/receipt.json'))
        self.assertEqual(before,self.snapshot())
        self.assertFalse((self.root/'ledger/names.jsonl').exists())

    def test_receipt_records_each_bank_without_arbitrary_global_map(self):
        proof=self.root/'proof.json'
        self.run_names('--proof-log',str(proof))
        rec=json.loads(proof.read_text())
        self.assertEqual(rec['status'],'UNVERIFIED')
        self.assertIsNone(rec['map'])
        self.assertEqual(rec['aliases'],{'first_bank':'func_80024020','second_bank':'func_80024020'})
        self.assertEqual(rec['scopes'],self.scope_data)


if __name__ == '__main__':
    unittest.main()
