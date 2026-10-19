"""Data baselines must compare linked storage and fail closed on gate disagreement."""
import contextlib
import io
import dataclasses
import json
from pathlib import Path
import sys
import tempfile
import types
import unittest
from unittest.mock import patch
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import overlay_data_baseline as D
import verify as V

@dataclasses.dataclass(frozen=True)
class Match:
    source: Path
    source_kind: str = 'c'
    config: str = '2.7.2-G0'

class FakeGate:
    def __init__(self):
        self.split = dict(foff=8, size=4, func_vram='D_80000008')
        self.match = Match(Path('old.c'))
    def cfg_path(self, p): return Path(p)
    def load_yaml(self, p):
        return dict(name='dungeon_test',standalone_build=dict(window=dict(
            file_start=0,file_end=16,vram_start=0x80000000)))
    def parse_int(self, n, label): return int(n)
    def load_split_rows(self, sb, start, end): return [self.split]
    def load_matches(self, sb, start, end, family): return {(8,4):self.match},{}
    def build_segments(self, rows, matches, start, end, delta):
        return [types.SimpleNamespace(kind='c',match=matches[(8,4)])]

class StorageComparison(unittest.TestCase):
    def test_all_bytes_equal(self):
        r=D.word_comparison(bytes(range(12)),bytes(range(12)))
        self.assertTrue(r['exact']);self.assertEqual((r['total'],r['gen_words'],r['tgt_words']),(0,3,3))
    def test_relocation_word_diff(self):
        r=D.word_comparison(b'\x00\x40\x02\x80',b'\x04\x40\x02\x80')
        self.assertFalse(r['exact']);self.assertEqual((r['total'],r['class']),(1,'data-diff'))
    def test_zero_tail_not_equality(self):
        r=D.word_comparison(b'1234'+bytes(4),b'1234')
        self.assertFalse(r['exact']);self.assertEqual((r['indels'],r['class']),(1,'length-drift'))
    def test_partial_words_compare_every_byte(self):
        self.assertFalse(D.word_comparison(b'12345',b'123456')['exact'])

class RegisteredWindow(unittest.TestCase):
    def setUp(self):
        self.row=dict(kind='overlay',gate_config='config/overlays/dungeon_test.overlay.yaml',
                      foff=8,size=4,func='D_80000008',cfg='2.7.2-G0')
        self.gate=FakeGate()
    def test_uses_production_match_with_candidate_source(self):
        cfg,sb,family,seg=D._segment(self.row,Path('candidate.c'),self.gate)
        self.assertEqual((family,seg.match.source),('dungeon',Path('candidate.c')))
    def test_missing_window(self):
        self.row['gate_config']=None
        with self.assertRaisesRegex(ValueError,'production window'):D._segment(self.row,Path('x'),self.gate)
    def test_crosses_window_end(self):
        self.row['size']=12
        with self.assertRaisesRegex(ValueError,'wholly inside'):D._segment(self.row,Path('x'),self.gate)
    def test_wrong_identity(self):
        self.gate.split['func_vram']='D_8000000C'
        with self.assertRaisesRegex(ValueError,'geometry/identity'):D._segment(self.row,Path('x'),self.gate)
    def test_wrong_recipe(self):
        self.gate.match=dataclasses.replace(self.gate.match,config='2.6.3')
        with self.assertRaisesRegex(ValueError,'recipe'):D._segment(self.row,Path('x'),self.gate)
    def test_asm_row_cannot_claim_c_baseline(self):
        self.gate.match=dataclasses.replace(self.gate.match,source_kind='game_asm')
        with self.assertRaisesRegex(ValueError,'production C'):D._segment(self.row,Path('x'),self.gate)

class WorkerIsolation(unittest.TestCase):
    def test_worker_uses_explicit_view_in_fresh_interpreter(self):
        result=types.SimpleNamespace(returncode=0,stdout='{"exact":true,"total":0}',stderr='')
        with patch.object(D.subprocess,'run',return_value=result) as run:
            self.assertTrue(D.measure_object_row({},Path('x.c'),Path('view'))['exact'])
            self.assertIn('--view',run.call_args.args[0])
            self.assertEqual(run.call_args.kwargs['timeout'],900)
    def test_worker_drops_ambient_compiler_model_overrides(self):
        result=types.SimpleNamespace(returncode=0,stdout='{"exact":true}',stderr='')
        with patch.dict(D.os.environ,AZURE_MASPSX='other-model',AZURE_MASPSX_COMPANION='other-companion'),patch.object(D.subprocess,'run',return_value=result) as run:
            D.measure_object_row({},Path('x.c'),Path('view'))
            self.assertNotIn('AZURE_MASPSX',run.call_args.kwargs['env'])
            self.assertNotIn('AZURE_MASPSX_COMPANION',run.call_args.kwargs['env'])
    def test_malformed_worker_output_is_refused(self):
        result=types.SimpleNamespace(returncode=0,stdout='{}',stderr='')
        with patch.object(D.subprocess,'run',return_value=result):
            self.assertFalse(D.measure_object_row({},Path('x.c'),Path('view'))['exact'])
    def test_worker_compile_failure_is_refused(self):
        result=types.SimpleNamespace(returncode=1,stdout='',stderr='compile failed')
        with patch.object(D.subprocess,'run',return_value=result):
            self.assertFalse(D.measure_object_row({},Path('x.c'),Path('view'))['exact'])

class DispatchAndAppend(unittest.TestCase):
    def test_data_only_preserves_existing_non_exact_text_baseline(self):
        row=dict(id='dungeon/func_80000008',kind='overlay',row_kind='text',
                 exists=True,stock=True,container='dungeon',src_sha='source',
                 gate_config='config/overlays/dungeon_test.overlay.yaml')
        with tempfile.TemporaryDirectory() as td:
            ledger=Path(td)
            before=json.dumps(dict(id=row['id'],exact=False,total=1))+'\n'
            (ledger/'baseline.jsonl').write_text(before)
            with patch.object(V,'rows',return_value=[row]),patch.object(V,'LEDGER',ledger),patch.object(V,'CACHE',ledger/'cache'),patch.object(V,'read_baseline_slus',return_value={}),patch.object(V,'verify_overlay') as score,patch.object(V,'gate_fallback') as gate,patch.object(sys,'argv',['verify.py','--baseline','--data-only','--workers','1']),contextlib.redirect_stdout(io.StringIO()):
                with self.assertRaises(SystemExit):V.main()
            score.assert_not_called();gate.assert_not_called()
            self.assertEqual((ledger/'baseline.jsonl').read_text(),before)

    def test_baseline_cli_does_not_rescore_archived_source(self):
        row=dict(id='dungeon/D_80000008',kind='overlay',row_kind='data',
                 exists=True,stock=True,container='dungeon',src_sha='stale-registry')
        with tempfile.TemporaryDirectory() as td:
            ledger=Path(td)
            with patch.object(V,'rows',return_value=[row]),patch.object(V,'verify_data') as score,patch.object(V,'LEDGER',ledger),patch.object(sys,'argv',['verify.py','--baseline','--data-only','--workers','1']),contextlib.redirect_stdout(io.StringIO()):
                with self.assertRaises(SystemExit):V.main()
            score.assert_not_called()
            self.assertFalse((ledger/'baseline.jsonl').exists())

    def test_data_never_instruction_scored(self):
        row=dict(kind='overlay',row_kind='data')
        with patch.object(V,'verify_data',return_value=dict(exact=True)) as data,patch.object(V,'verify_overlay') as text:
            self.assertTrue(V.verify(row,Path('x.c'))['exact'])
            data.assert_called_once();text.assert_not_called()
    def test_failed_link_is_non_exact(self):
        with patch.object(D,'_measure',side_effect=SystemExit('unresolved relocation')):
            rec=D.verify_object_row({},Path('x.c'),Path('view'))
        self.assertFalse(rec['exact']);self.assertEqual(rec['status'],'failed')
    def test_failed_rebaseline_never_appends(self):
        row=dict(id='dungeon/D_80000008',kind='overlay',stock=True,row_kind='data')
        with patch.object(V,'rows',return_value=[row]),patch.object(V,'raw_path',return_value=Path('raw.c')),patch.object(V,'gate_root',return_value=Path('view')),patch.object(D,'measure_object_row',return_value=dict(exact=False)),patch.object(V,'append_jsonl') as app:
            rec=V.rebaseline_overlay_objects([row['id']])[0]
            self.assertEqual(rec['outcome'],'refused');app.assert_not_called()
    def test_dry_run_does_not_append(self):
        row=dict(id='dungeon/D_80000008',kind='overlay',stock=True,row_kind='data')
        with patch.object(V,'rows',return_value=[row]),patch.object(V,'raw_path',return_value=Path('raw.c')),patch.object(V,'gate_root',return_value=Path('view')),patch.object(D,'measure_object_row',return_value=dict(exact=True)),patch.object(V,'append_jsonl') as app:
            self.assertEqual(V.rebaseline_overlay_objects([row['id']],True)[0]['outcome'],'dry-run');app.assert_not_called()
    def test_only_exact_measurements_append(self):
        row=dict(id='dungeon/D_80000008',kind='overlay',stock=True,row_kind='data')
        with patch.object(V,'rows',return_value=[row]),patch.object(V,'raw_path',return_value=Path('raw.c')),patch.object(V,'gate_root',return_value=Path('view')),patch.object(D,'measure_object_row',return_value=dict(exact=True,gen_words=1)),patch.object(V,'append_jsonl') as app:
            self.assertEqual(V.rebaseline_overlay_objects([row['id']])[0]['outcome'],'rebaselined')
            self.assertEqual(app.call_count,1);self.assertEqual(app.call_args.args[1]['baseline_source'],'pinned-raw')

if __name__=='__main__':unittest.main()
