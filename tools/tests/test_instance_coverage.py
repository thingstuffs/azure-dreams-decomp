import importlib.util,json,tempfile,unittest
from pathlib import Path
LANE=Path(__file__).resolve().parents[2]
spec=importlib.util.spec_from_file_location('instance_coverage',LANE/'tools/coverage.py'); C=importlib.util.module_from_spec(spec);spec.loader.exec_module(C)
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
    def test_out_of_file_proof_is_rejected(self):
        write(self.led/'instances.jsonl',[{'container':'dungeon','foff':99,'size':4,'result':'proven'}]);self.assertRaises(ValueError,self.report)
    def test_subtract_and_intersection_boundaries(self):
        self.assertEqual(C.subtract([[0,10],[20,30]],[[3,8],[8,22]]),[[0,3],[22,30]]);self.assertEqual(C.intersection([[0,10]],[[10,20]]),[])
if __name__=='__main__':unittest.main()
