"""Function staging respects inline home identity and proves no rows itself."""
import contextlib
import hashlib
import io
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'tools'))
import apply_names as N
import apply_names_batch as B
from source_layout import own_source

class LayoutStaging(unittest.TestCase):
    def setUp(self):
        self.temp=tempfile.TemporaryDirectory();self.addCleanup(self.temp.cleanup)
        self.root=r=Path(self.temp.name)
        for d in ('config','ledger','include','src/town/actor'):(r/d).mkdir(parents=True)
        self.names=r/'config/names.tsv';self.names.write_text('# aliases\n')
        self.journal=r/'ledger/names.jsonl'
        self.source=r/'src/town/actor/merged.c'
        first='int func_80000000(void) { return 1; }\n'
        second='/* func_80000000 */\nchar *label="func_80000000";\nint func_80000004(void) { return func_80000000(); }\n'
        self.source.write_text(first+second)
        self.rows=[dict(id='town/first',func='func_80000000',kind='overlay',container='town',c_path='first.c'),
                   dict(id='town/second',func='func_80000004',kind='overlay',container='town',c_path='second.c')]
        (r/'ledger/rows.jsonl').write_text(''.join(json.dumps(x)+'\n' for x in self.rows))
        (r/'ledger/layout.jsonl').write_text(''.join(json.dumps(dict(id=x['id'],path='src/town/actor/merged.c'))+'\n' for x in self.rows))
        self.index=r/'ledger/layout_inline.jsonl';offset=0;records=[]
        for i,(row,text) in enumerate(zip(self.rows,(first,second))):
            records.append(dict(tu_old='src/town/modules/merged.c',tu_new='src/town/actor/merged.c',
                member='src/town/'+row['c_path'],member_id=row['id'],manifest_key='test',order=i,
                offset=offset,bytes=len(text),inlined_bytes=len(text),source_sha256=hashlib.sha256(text.encode()).hexdigest(),original_includes=[]))
            offset+=len(text)
        self.index.write_text(''.join(json.dumps(x)+'\n' for x in records))
        self.proposal=r/'proposed.tsv';self.proposal.write_text('0x80000000\tfunc_80000000\tread_constant_one\tbody evidence\n')
        self.identity=r/'identity.json';self.identity.write_text(json.dumps({'read_constant_one':dict(row='town/first',symbol='func_80000000')}))

    def stage(self):
        argv=['apply_names.py',str(self.proposal),'--batch','--identity-map',str(self.identity),'--defer-verification']
        with patch.multiple(N,ROOT=self.root,NAMES=self.names,JOURNAL=self.journal,INCLUDE=self.root/'include'), \
             patch.object(N,'rows',return_value=self.rows),patch.object(N,'verify',side_effect=AssertionError('staging must not claim verification')), \
             patch.object(sys,'argv',argv),contextlib.redirect_stdout(io.StringIO()):
            return N.main()

    def protected(self):return {p:p.read_bytes() for p in (self.source,self.names,self.index)}

    def test_merged_member_and_second_replay(self):
        self.stage()
        first=own_source(self.rows[0],self.root)[0];second=own_source(self.rows[1],self.root)[0]
        self.assertIn('int read_constant_one(void)',first)
        self.assertIn('return read_constant_one()',second)
        self.assertIn('/* func_80000000 */',second)
        self.assertIn('"func_80000000"',second)
        self.assertEqual(json.loads(self.journal.read_text())['outcome'],'staged-unverified')
        before=self.protected();journal=self.journal.read_bytes();self.stage()
        self.assertEqual(self.protected(),before);self.assertEqual(self.journal.read_bytes(),journal)

    def test_identity_cannot_select_an_inline_sibling(self):
        self.identity.write_text(json.dumps({'read_constant_one':dict(row='town/second',symbol='func_80000000')}))
        before=self.protected()
        with self.assertRaisesRegex(ValueError,'current definition'):self.stage()
        self.assertEqual(self.protected(),before)

    def test_inline_write_failure_rolls_back_source_and_alias(self):
        original=Path.write_bytes;failed=False
        def reject(path,data):
            nonlocal failed
            if path==self.index and not failed:failed=True;raise OSError('metadata write failed')
            return original(path,data)
        before=self.protected()
        with patch.object(Path,'write_bytes',reject):
            with self.assertRaisesRegex(OSError,'metadata write failed'):self.stage()
        self.assertEqual(self.protected(),before)

if __name__=='__main__':unittest.main()
