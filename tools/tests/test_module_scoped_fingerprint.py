"""Module certificates must become stale when their frozen compile evidence changes."""
import json
import sys
from pathlib import Path
from unittest.mock import patch
from test_gate_all_scoped_inputs import ScopedInputsFixture, C

REPO=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(REPO/'tools/gate'))
import overlay_module_gate as M


class ModuleScopedFingerprint(ScopedInputsFixture):
    def setUp(self):
        super().setUp()
        self.module={'key':'unit_module','container':'dungeon',
            'source':'src/dungeon/module.c','headers':['include/unit.h'],
            'members':[{'foff':0x100,'size':16,'source':'src/dungeon/func_00000100.c'}],
            'review_inputs':['review.txt'],'imports':[]}
        (self.root/'include').mkdir()
        for n in ['include/unit.h','include/labels.inc','review.txt','src/dungeon/module.c',
                  'config/names.tsv','config/noreturn_syms.dungeon.txt','config/sibcall_syms.dungeon.txt']:
            (self.root/n).write_text('')
        (self.root/'config/overlays/modules.json').write_text('{}')
        (self.root/'ledger/splits/overlay_modules.build.json').write_text('{}')
        (self.root/'work/disc/containers').mkdir(parents=True)
        (self.root/'work/disc/containers/DUNGEON_DUNGEON.BIN').write_bytes(bytes(0x600))
        # Toolchain identities are orthogonal to this hermetic regression. The
        # SHA of real temp-root source/config paths remains fully exercised.
        sha=M.sha
        def identity(p):
            p=Path(p)
            return sha(p) if p.is_file() else 'test-tool-identity'
        ctx=patch.object(M,'sha',side_effect=identity);ctx.start();self.addCleanup(ctx.stop)
        ctx=patch.object(M.shutil,'which',return_value='/test/tool');ctx.start();self.addCleanup(ctx.stop)
        ctx=patch.object(M,'affected_windows',return_value=['config/overlays/dungeon_a.overlay.yaml'])
        ctx.start();self.addCleanup(ctx.stop)
        # Supply enough fields for neighbouring row compiler identities.
        for r in self.reg:r['cell']='2.7.2-cdk'
        self.write('ledger/rows.jsonl',self.reg)
        y=self.windows['dungeon_a']
        y.write_text(y.read_text()+'  split_results: overlays/dungeon/overlay_first_pass_results.json\n')

    def fp(self,windows=False):return M.fingerprint(self.module,self.root,windows=windows)

    def test_raw_edit_inside_member_region_stales_certificate(self):
        before=self.fp()
        (self.root/'raw/dungeon/func_00000110.c').write_text(self.decl('replacement'))
        after=self.fp()
        self.assertNotEqual(before['sha256'],after['sha256'])
        self.assertEqual(before['inputs'],after['inputs'])
        self.assertNotEqual(before['bank_noreturn'],after['bank_noreturn'])

    def test_other_region_raw_edit_leaves_certificate_current(self):
        before=self.fp()
        (self.root/'raw/dungeon/func_00000310.c').write_text(self.decl('replacement'))
        self.assertEqual(before,self.fp())

    def test_rowbase_edit_stales_certificate(self):
        before=self.fp()
        self.regions[0]['foff_start']='0x110'
        self.write('config/overlays/dungeon.rowbase.jsonl',self.regions)
        self.assertNotEqual(before['sha256'],self.fp()['sha256'])

    def test_family_exclusion_stales_certificate(self):
        before=self.fp()
        self.write(C.FALSE_MEMBERS_PATH,[{'schema':C.FALSE_MEMBER_SCHEMA,'family':'dungeon',
                   'func':'dungeon_110','proof':'test evidence'}])
        after=self.fp()
        self.assertNotEqual(before['sha256'],after['sha256'])
        self.assertNotEqual(before['bank_noreturn'],after['bank_noreturn'])

    def test_default_fingerprint_covers_neighbor_region_when_window_crosses_banks(self):
        y=self.windows['dungeon_a']
        y.write_text(y.read_text().replace('file_end: 0x110','file_end: 0x400'))
        before=self.fp(windows=True)
        (self.root/'raw/dungeon/func_00000310.c').write_text(self.decl('replacement'))
        self.assertNotEqual(before['sha256'],self.fp(windows=True)['sha256'])
        self.assertEqual(len(before['bank_noreturn']['scopes']),2)

    def test_unmapped_member_keeps_only_own_frozen_source(self):
        self.module['members']=[{'foff':0x500,'size':16,'source':'src/dungeon/func_00000500.c'}]
        before=self.fp()
        (self.root/'raw/dungeon/func_00000510.c').write_text(self.decl('replacement'))
        self.assertEqual(before,self.fp())
        (self.root/'raw/dungeon/func_00000500.c').write_text(self.decl('replacement'))
        self.assertNotEqual(before['sha256'],self.fp()['sha256'])

    def test_fingerprint_is_unchanged_by_receipt_json_round_trip(self):
        fp=self.fp()
        self.assertEqual(fp,json.loads(json.dumps(fp)))

    def test_window_receipt_verification_accepts_round_trip_and_rejects_raw_change(self):
        receipt=self.root/'receipt.json'
        receipt.write_text(json.dumps({'fingerprint':self.fp(windows=True),'candidates':{}}))
        projection={'module':self.module['key'],'receipt':str(receipt),
                    'receipt_sha256':M.sha(receipt)}
        with patch.object(M,'load_modules',return_value=[self.module]):
            M.verify_window_modules([projection],self.root)
            (self.root/'raw/dungeon/func_00000110.c').write_text(self.decl('replacement'))
            with self.assertRaisesRegex(ValueError,'inputs changed'):
                M.verify_window_modules([projection],self.root)

    def test_engine_only_neighbor_without_registry_row_is_bound(self):
        y=self.windows['dungeon_a']
        y.write_text(y.read_text().replace('file_end: 0x110','file_end: 0x610')+
                     '  matched_sources:\n    - results: overlays/dungeon_engine/overlay_first_pass_results.json\n')
        self.write('ledger/splits/dungeon_engine.jsonl',[{'foff':0x600,'size':16,
                     'c_path':'unregistered_engine.c','result':'MATCH'}])
        p=self.root/'raw/dungeon/unregistered_engine.c'
        p.write_text(self.decl('engine_neighbor'))
        before=self.fp(windows=True)
        p.write_text(self.decl('engine_neighbor_replaced'))
        self.assertNotEqual(before['sha256'],self.fp(windows=True)['sha256'])
