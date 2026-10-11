"""Fresh gate receipt transfer tests; synthetic artifacts carry no byte authority."""
import json
import os
from pathlib import Path
import tempfile
import unittest
import sys
from unittest.mock import patch
REPO=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(REPO/'tools'))
from fidelity import certify_overlay_module as C
from build import gate_all as A

class FreshReceiptTests(unittest.TestCase):
    def setUp(self):
        self.temp=tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR',str(REPO/'tmp')));self.addCleanup(self.temp.cleanup)
        self.root=Path(self.temp.name);self.view=self.root/'build_ovl_gate';self.view.mkdir()
        (self.root/'ledger').mkdir();(self.view/'ledger').symlink_to(self.root/'ledger',target_is_directory=True)
        (self.root/'tools/build').mkdir(parents=True);(self.root/'tools/build/gate_all.py').write_text('gate tool')
        self.wn='config/overlays/demo.overlay.yaml';p=self.view/self.wn;p.parent.mkdir(parents=True)
        p.write_text('name: demo\nstandalone_build:\n  work_dir: work\n  window:\n    file_start: 0\n    file_end: 4\n')
        bd=self.view/'work/demo/build';(bd/'modules/native').mkdir(parents=True)
        (bd/'modules/native/receipt.json').write_text('{"genuine":{"result":"MATCH"}}')
        (bd/'modules/native/OUT.OBJ').write_bytes(b'synthetic genuine object')
        (bd/'demo.window.bin').write_bytes(b'demo');(bd.parent/'demo_manifest.json').write_text('{}')
        (bd/'modules.json').write_text('[{"module":"native"}]')
        self.directory=self.root/'receipts';self.directory.mkdir();self.token='fresh-transaction'
        digest=C.snapshot_gate_window(self.view,self.wn,self.directory,self.token,{'result':'MATCH','inputs_sha':'current'},['MATCH demo (4 bytes)'])
        self.index={'schema':1,'result':'PASS','transaction':self.token,'authority':str(self.root),'view':str(self.view),
                    'gate_tool_sha256':C.sha(self.root/'tools/build/gate_all.py'),'windows':{self.wn:digest}}
        self.write_index()
        ctx=patch.object(A,'inputs_sha',return_value='current');ctx.start();self.addCleanup(ctx.stop)

    def write_index(self):
        (self.directory/'index.json').write_text(json.dumps(self.index))

    def read(self):return C.fresh_window_source(self.view,self.wn,self.directory,self.token)

    def test_identical_fresh_window_reuses_complete_snapshot(self):
        snapshot=self.read();self.assertEqual((snapshot/'window.bin').read_bytes(),b'demo')
        self.assertEqual((snapshot/'gate.log').read_text(),'MATCH demo (4 bytes)\n')
        self.assertTrue((snapshot/'modules/native/OUT.OBJ').is_file())

    def test_cached_journal_only_or_unpublished_window_never_reuses(self):
        self.assertIsNone(C.fresh_window_source(self.view,self.wn,None,None))
        self.index['windows']={};self.write_index();self.assertIsNone(self.read())

    def test_changed_inputs_force_new_gate(self):
        with patch.object(A,'inputs_sha',return_value='changed'):self.assertIsNone(self.read())

    def test_other_transaction_failed_run_and_other_view_refused(self):
        for field,value in [('transaction','old'),('result','FAIL'),('view',str(self.root)),('authority','other')]:
            original=self.index[field];self.index[field]=value;self.write_index()
            with self.assertRaisesRegex(ValueError,'context'):self.read()
            self.index[field]=original

    def test_changed_gate_tool_refused(self):
        (self.root/'tools/build/gate_all.py').write_text('changed')
        with self.assertRaisesRegex(ValueError,'context'):self.read()

    def test_modified_object_blob_manifest_or_log_refused(self):
        snapshot=self.directory/'demo'
        for rel in ('modules/native/OUT.OBJ','window.bin','manifest.json','gate.log'):
            p=snapshot/rel;original=p.read_bytes();p.write_bytes(b'changed')
            with self.assertRaisesRegex(ValueError,'artifacts changed'):self.read()
            p.write_bytes(original)

    def test_receipt_edit_and_missing_file_refused(self):
        p=self.directory/'demo/receipt.json';p.write_text('{}')
        with self.assertRaisesRegex(ValueError,'receipt changed'):self.read()
        p.unlink()
        with self.assertRaises(OSError):self.read()

    def test_linked_artifact_refused(self):
        p=self.directory/'demo/window.bin';p.unlink();p.symlink_to(self.view/'work/demo/build/demo.window.bin')
        with self.assertRaisesRegex(ValueError,'linked'):self.read()

    def test_no_success_index_means_no_transferable_proof(self):
        (self.directory/'index.json').unlink()
        with self.assertRaises(OSError):self.read()

    def test_gate_does_not_publish_when_inputs_changed_while_compiling(self):
        with patch.object(A,'_RECEIPTS',self.directory),patch.object(A,'_TRANSACTION',self.token),patch.object(A,'B',self.view),\
             patch.object(A,'inputs_sha',side_effect=['before','after']),patch.object(A,'window_lock'),\
             patch.object(A,'window_modules',return_value={'demo.overlay.yaml':[{'key':'native'}]}),\
             patch.object(A,'worker_output',return_value=['MATCH demo (4 bytes)']),\
             patch('fidelity.certify_overlay_module.snapshot_gate_window') as publish:
            rec=A.run_window(self.view/self.wn,in_process=True)
        self.assertEqual(rec['result'],'ERROR');publish.assert_not_called()

    def test_nonmodule_windows_keep_the_original_single_hash_cost(self):
        with patch.object(A,'_RECEIPTS',self.directory),patch.object(A,'window_modules',return_value={}),\
             patch.object(A,'inputs_sha',return_value='current') as inputs,patch.object(A,'window_lock'),\
             patch.object(A,'worker_output',return_value=['MATCH demo (4 bytes)']),\
             patch('fidelity.certify_overlay_module.snapshot_gate_window') as publish:
            rec=A.run_window(self.view/self.wn,in_process=True)
        self.assertEqual(rec['result'],'MATCH');self.assertEqual(inputs.call_count,1);publish.assert_not_called()

if __name__=='__main__':unittest.main()
