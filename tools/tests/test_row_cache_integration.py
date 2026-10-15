"""Run real accounting entry points on a small changing tree, with fresh proof readers."""
import collections
import contextlib
import importlib.util
import io
import json
import os
from pathlib import Path
import shutil
import sys
import tempfile
import time
import unittest
from unittest.mock import patch

TOOLS=Path(__file__).resolve().parents[1]
sys.path[:0]=[str(TOOLS),str(TOOLS/'gate')]
import levels as L
import status as S
import census as C
import call_arity as A
import evidence
import overlay_module_evidence as O
import slus_module_evidence as U
import gen_src_index
import accounting_modules as M


class AccountingIntegration(unittest.TestCase):
    def setUp(self):
        self.tmp=tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR'))
        self.addCleanup(self.tmp.cleanup)
        self.root=Path(self.tmp.name);self.ledger=self.root/'ledger';self.ledger.mkdir()
        self.rows=[]
        for i in range(2):
            f='func_%08X'%(0x80010000+4*i);rid='main/'+f
            self.rows.append(dict(id=rid,container='main',func=f,stock=True,size=4,
                                  kind='overlay',cfg='2.7.2',c_path=f+'.c',defs=[f]))
            for folder,comment in [('src','/* cleaned */'),('raw','/* original */')]:
                p=self.root/folder/'main'/(f+'.c');p.parent.mkdir(parents=True,exist_ok=True)
                p.write_text('int '+f+'(void) { return 0; } '+comment+'\n')
        self.write('baseline.jsonl',[dict(id=r['id'],exact=True) for r in self.rows])
        self.write('promotions.jsonl',[dict(id=r['id'],outcome='landed') for r in self.rows])
        self.write('pin.json',dict(pin='test',commit='1234567890abcdef',extracted_at='fixed'))
        (self.root/'config').mkdir()
        (self.root/'config/decomp_audit_baseline.json').write_text('{"sites":{}}')
        for file in ['accounting_modules.py','row_cache.py','levels.py','status.py','common.py','pin_census.py','census.py','call_arity.py','gate/gen_noreturn_syms.py']:
            dest=self.root/'tools'/file;dest.parent.mkdir(parents=True,exist_ok=True)
            shutil.copy2(TOOLS/file,dest)
        self.placement={};self.context={}
        for obj, names in [(L,('_FID','_CONTAINER_SYMS')),
                           (C,('_SITES','_VOID_EXACT_TARGETS','_DECLARED_VOID')),
                           (A,('_NAMES','_DEFIDX'))]:
            for name in names:
                memo=patch.object(obj,name,getattr(obj,name));memo.start();self.addCleanup(memo.stop)
        patches=[patch.object(L,'ROOT',self.root),patch.object(L,'LEDGER',self.ledger),
                 patch.object(L,'rows',return_value=self.rows),patch.object(L,'raw_path',side_effect=lambda r:self.root/'raw'/r['container']/r['c_path']),
                 patch.object(S,'ROOT',self.root),patch.object(S,'LEDGER',self.ledger),patch.object(S,'rows',return_value=self.rows),
                 patch.object(C,'ROOT',self.root),patch.object(C,'LEDGER',self.ledger),
                 patch.object(A,'ROOT',self.root),patch.object(A,'rows',return_value=self.rows),
                 patch.object(M,'overlay_placements',side_effect=lambda root:dict(self.placement)),
                 patch.object(O,'source_contexts',side_effect=lambda:dict(self.context)),
                 patch.object(M,'overlay_statuses',return_value=[]),patch.object(U,'valid_placements',return_value={}),
                 patch.object(U,'module_status',return_value=[]),patch.object(evidence,'EV',self.ledger/'evidence'),
                 patch.object(evidence,'census',return_value=''),patch.object(gen_src_index,'main'),
                 patch.object(time,'gmtime',return_value=time.struct_time((2026,1,1,0,0,0,3,1,0)))]
        for item in patches:item.start();self.addCleanup(item.stop)

    def write(self,name,records):
        p=self.ledger/name;p.parent.mkdir(parents=True,exist_ok=True)
        p.write_text(json.dumps(records) if isinstance(records,dict) else ''.join(json.dumps(r)+'\n' for r in records))

    def reset_process_memos(self):
        # Emulate separate CLIs while retaining only the on-disk row cache.
        L._FID=None;L._CONTAINER_SYMS={}
        C._SITES=None;C._VOID_EXACT_TARGETS=None;C._DECLARED_VOID=None
        A._NAMES=None;A._DEFIDX=None

    def levels(self):
        self.reset_process_memos()
        with patch.object(L,'evaluate_row',wraps=L.evaluate_row) as evaluate,contextlib.redirect_stdout(io.StringIO()):L.main()
        return evaluate.call_count,(self.ledger/'levels.jsonl').read_bytes()

    def test_warm_rows_skip_evaluation_but_proof_reader_runs_every_time(self):
        count,cold=self.levels();self.assertEqual(count,2)
        count,warm=self.levels();self.assertEqual(count,0);self.assertEqual(cold,warm)
        self.assertEqual(M.overlay_placements.call_count,2)
        self.placement[self.rows[0]['id']]={'module':'proved','outcome':'applied'}
        count,placed=self.levels();self.assertEqual(count,1);self.assertNotEqual(cold,placed)
        self.placement.clear()
        count,invalidated=self.levels();self.assertEqual(count,1);self.assertEqual(cold,invalidated)

    def test_source_raw_ledger_config_and_shared_context_changes_invalidate_row(self):
        self.levels()
        rid=self.rows[0]['id']
        changes=[lambda:(self.root/'src'/(rid+'.c')).write_text('int func_80010000(void) { return 1; }'),
                 lambda:(self.root/'raw'/(rid+'.c')).write_text('int func_80010000(void) { return 1; }'),
                 lambda:self.write('promotions.jsonl',[dict(id=self.rows[1]['id'],outcome='landed')]),
                 lambda:self.write('split_audit.jsonl',[dict(id=rid,target='func_80000000',kind='intra')]),
                 lambda:self.rows[0].update(cfg='2.8.0'),
                 lambda:self.context.update({rid:'/* shared glue changed */'})]
        for change in changes:
            change();count,_=self.levels();self.assertEqual(count,1)
        (self.root/'config/decomp_audit_baseline.json').write_text(json.dumps({'sites':{'main/func_80010000':{'sites':['JT_KEEP_ORDER|x|']}}}))
        count,_=self.levels();self.assertEqual(count,1)

    def test_callee_signature_change_invalidates_unchanged_caller(self):
        (self.root/'src/main/func_80010000.c').write_text('void func_80010000(void) { func_80010004(1); }')
        (self.root/'src/main/func_80010004.c').write_text('void func_80010004(int value) { use(value); }')
        (self.root/'config/decomp_audit_baseline.json').write_text(json.dumps({'sites':{'main/func_80010000':{'sites':['PASSTHRU|func_80010004|']}}}))
        count,before=self.levels();self.assertEqual(count,2)
        self.assertEqual(self.levels()[0],0)
        (self.root/'src/main/func_80010004.c').write_text('void func_80010004(int value, int extra) { use(value); }')
        count,after=self.levels();self.assertEqual(count,2);self.assertNotEqual(before,after)

    def test_status_matches_cold_oracle_and_reuses_only_unchanged_facts(self):
        self.levels()
        def status(enabled):
            self.reset_process_memos()
            with patch.dict(os.environ,AZURE_ROW_CACHE=enabled),patch.object(S,'sites_of',wraps=S.sites_of) as sites,contextlib.redirect_stdout(io.StringIO()):S.main()
            return sites.call_count,(self.root/'STATUS.md').read_bytes()
        count,first=status('1');self.assertGreater(count,0)
        count,warm=status('1');self.assertEqual(count,0);self.assertEqual(first,warm)
        count,oracle=status('0');self.assertGreater(count,0);self.assertEqual(first,oracle)
        self.assertEqual(M.overlay_statuses.call_count,3)
        (self.root/'src/main/func_80010000.c').write_text('int func_80010000(void) { int temp_x=0; return temp_x; }')
        count,changed=status('1');self.assertGreater(count,0);self.assertNotEqual(first,changed)
        self.assertEqual(changed,status('0')[1])

if __name__=='__main__':unittest.main()
