import importlib.util,json,sys,tempfile,unittest
from pathlib import Path
LANE=Path(__file__).resolve().parents[2]
spec=importlib.util.spec_from_file_location('instance_coverage',LANE/'tools/coverage.py'); C=importlib.util.module_from_spec(spec);spec.loader.exec_module(C)
sys.path.insert(0, str(LANE / 'tools'))
import status

def write(p,rs):p.parent.mkdir(parents=True,exist_ok=True);p.write_text(''.join(json.dumps(r)+'\n' for r in rs))
class CoverageTests(unittest.TestCase):
    def setUp(self):
        self.tmp=tempfile.TemporaryDirectory(dir=LANE/'tmp');self.root=Path(self.tmp.name);self.led=self.root/'ledger'
        write(self.led/'containers.jsonl',[{'container':'dungeon','bytes':100}])
        write(self.led/'rows.jsonl',[{'container':'dungeon','func':'func_A','foff':0,'size':20},{'container':'dungeon','func':'func_B','foff':10,'size':20},{'container':'dungeon','func':'D_A','foff':90,'size':10}])
        write(self.led/'instances.jsonl',[{'container':'dungeon','foff':20,'size':30,'result':'proven'},{'container':'dungeon','foff':40,'size':20,'result':'proven'},{'container':'dungeon','foff':60,'size':20,'result':'mismatch'}]*2)
        write(self.led/'coverage_regions.jsonl',[{'container':'dungeon','foff':0,'size':80,'category':'window'},{'container':'dungeon','foff':30,'size':40,'category':'estimated_code'},{'container':'dungeon','foff':70,'size':10,'category':'sdk_asm'},{'container':'dungeon','foff':80,'size':10,'category':'unported'}])
    def tearDown(self):self.tmp.cleanup()
    def report(self):return C.coverage(self.root)['containers']['dungeon']
    def test_unions_no_double_count_and_failed_proofs_do_not_cover(self):
        r=self.report()['whole_image'];self.assertEqual([r[k] for k in ['c_rows','proven_instances','estimated_code','sdk_asm','unported','data_excluded','unknown']],[30,30,10,10,10,10,0]);self.assertEqual(r['scope_bytes'],r['partition_bytes']);self.assertAlmostEqual(r['c_coverage_after_pct'],66.6667)
    def test_later_partial_supersedes_a_proven_attestation(self):
        write(self.led/'instances.jsonl',[{'row':'x','container':'dungeon','foff':30,'size':30,'result':'proven'},{'row':'x','container':'dungeon','foff':30,'size':30,'result':'partial'}]);self.assertEqual(self.report()['whole_image']['proven_instances'],0)
    def test_data_exclusion_wins_over_a_byte_exact_pattern(self):
        write(self.led/'coverage_regions.jsonl',[{'container':'dungeon','foff':30,'size':30,'category':'data_excluded'}]);r=self.report()['whole_image'];self.assertEqual(r['proven_instances'],0);self.assertEqual(r['data_excluded'],40)
    def test_append_only_classification_revocation(self):
        row={'container':'dungeon','foff':30,'size':30,'category':'data_excluded'};write(self.led/'coverage_regions.jsonl',[row,dict(row,active=False)]);self.assertEqual(self.report()['whole_image']['proven_instances'],30)
    def test_entry_exclusion_filters_a_candidate_not_overlapping_owners(self):
        write(self.led/'coverage_regions.jsonl',[{'container':'dungeon','foff':20,'size':30,'category':'instance_excluded'}]);self.assertEqual(self.report()['whole_image']['proven_instances'],20)
    def test_latest_physical_owner_decision_retires_an_older_template(self):
        write(self.led/'instances.jsonl',[{'row':'old','container':'dungeon','foff':30,'size':30,'result':'proven'},{'row':'new','container':'dungeon','foff':30,'size':30,'result':'partial'}]);self.assertEqual(self.report()['whole_image']['proven_instances'],0)
    def test_window_clips_extents(self):
        r=self.report()['windows'];self.assertEqual(r['scope_bytes'],80);self.assertEqual(r['unported'],0);self.assertEqual(r['data_excluded'],0)
    def test_unknown_is_visible_and_not_excluded_as_data(self):
        write(self.led/'coverage_regions.jsonl',[]);r=self.report();self.assertFalse(r['denominator_complete']);self.assertEqual(r['whole_image']['unknown'],30)
    def test_verified_residue_wins_over_compiled_rows_and_instances(self):
        write(self.led/'coverage_regions.jsonl', [
            {'container':'dungeon','foff':20,'size':25,'category':'stale_town_copy','compare_container':'town','compare_foff':20,'words':6,'equal_words':6},
        ])
        report = self.report()['whole_image']
        self.assertEqual(report['retail_residue'], 25)
        self.assertEqual(report['c_rows'], 20)
        self.assertEqual(report['proven_instances'], 15)
        self.assertEqual(report['partition_bytes'], 100)
    def test_status_excludes_residue_from_rows_instances_estimates_and_splits(self):
        (self.root / 'tools').mkdir()
        (self.root / 'tools/coverage.py').write_bytes((LANE / 'tools/coverage.py').read_bytes())
        residue = {'container': 'dungeon', 'foff': 20, 'size': 44, 'category': 'stale_town_copy'}
        revoked = dict(residue, foff=70, size=10)
        regions = C.records(self.led / 'coverage_regions.jsonl')
        write(self.led / 'coverage_regions.jsonl', regions + [residue, revoked, dict(revoked, active=False)])
        write(self.led / 'splits/dungeon.jsonl', [{'foff': 20, 'size': 44, 'result': 'CFAIL'}])
        report = self.report()['whole_image']
        tally = status.not_yet_c(self.root)['dungeon']
        self.assertEqual(tally, {'in_c': 20, 'copies': 0, 'split': 0, 'sdk': 10, 'unported': 10, 'heuristic': 6, 'older_head_bank': 0})
        self.assertEqual(sum(tally.values()), report['code_bytes_classified_or_estimated'])
        self.assertEqual(tally['in_c'], report['c_rows'])
    def test_status_keeps_an_explicit_unported_class_in_split_windows(self):
        (self.root / 'tools').mkdir()
        (self.root / 'tools/coverage.py').write_bytes((LANE / 'tools/coverage.py').read_bytes())
        write(self.led / 'coverage_regions.jsonl', [
            {'container': 'dungeon', 'foff': 0, 'size': 100, 'category': 'window'},
            {'container': 'dungeon', 'foff': 80, 'size': 10, 'category': 'unported'},
        ])
        write(self.led / 'splits/dungeon.jsonl', [
            {'foff': 76, 'size': 8, 'result': 'CFAIL'},
            {'foff': 84, 'size': 6, 'result': 'data'},
        ])
        report = self.report()['whole_image']
        tally = status.not_yet_c(self.root)['dungeon']
        self.assertEqual(tally['unported'], report['unported'])
        self.assertEqual(tally['split'], 4)

    def test_older_head_bank_is_reported_apart_from_game_c(self):
        (self.root / 'tools').mkdir()
        (self.root / 'tools/coverage.py').write_bytes((LANE / 'tools/coverage.py').read_bytes())
        write(self.led / 'coverage_regions.jsonl', [
            {'container': 'dungeon', 'foff': 0, 'size': 20, 'category': 'older_dungeon_head_bank'},
        ])
        report = self.report()['whole_image']
        tally = status.not_yet_c(self.root)['dungeon']
        self.assertEqual(report['retail_residue_by_class'], {'older_dungeon_head_bank': 20})
        self.assertEqual(tally['older_head_bank'], 20)
        self.assertEqual(tally['in_c'], report['c_rows'])
        self.assertEqual(tally['in_c'], 10)
    def test_out_of_file_proof_is_rejected(self):
        write(self.led/'instances.jsonl',[{'container':'dungeon','foff':99,'size':4,'result':'proven'}]);self.assertRaises(ValueError,self.report)
    def test_subtract_and_intersection_boundaries(self):
        self.assertEqual(C.subtract([[0,10],[20,30]],[[3,8],[8,22]]),[[0,3],[22,30]]);self.assertEqual(C.intersection([[0,10]],[[10,20]]),[])

    def test_compressed_stream_class_matches_manifest_and_keeps_code_coordinates_separate(self):
        write(self.led / 'containers.jsonl', [dict(container='dungeon', file='DUNGEON.BIN', bytes=100)])
        write(self.led / 'instances.jsonl', [])
        manifest = 'config/decoded/sample.json'
        path = self.root / manifest
        path.parent.mkdir(parents=True)
        sha = '1' * 64
        path.write_text(json.dumps(dict(
            image='dungeon/sample', proof_mode='recompress',
            streams=[dict(container='work/disc/containers/DUNGEON.BIN', offset='0x20', used=9,
                          source_sha256=sha)],
            coverage=dict(functions=2, text_bytes=16, data_bytes=4, imported_bytes=4, stream_bytes=9),
            import_classes=dict(code=4, text=0, alignment=0, data=0),
        )))
        row = dict(container='dungeon', foff=32, size=9, category='compressed_code_stream',
                   decoded_manifest=manifest, retail_sha256=sha)
        write(self.led / 'coverage_regions.jsonl', [row])
        report = C.coverage(self.root)
        image = report['containers']['dungeon']['whole_image']
        self.assertEqual((image['compressed_code_stream'], image['unknown'], image['c_rows']), (9, 51, 30))
        self.assertEqual(report['decoded_images']['dungeon/sample']['bytes_with_c'], 20)
        for changed in ({'retail_sha256': '2' * 64}, {'foff': 33}, {'size': 8},
                        {'decoded_manifest': 'config/decoded/other.json'}):
            write(self.led / 'coverage_regions.jsonl', [dict(row, **changed)])
            with self.subTest(changed=changed):
                with self.assertRaisesRegex(ValueError, 'differs from decoded manifest'):
                    C.coverage(self.root)

if __name__=='__main__':unittest.main()
