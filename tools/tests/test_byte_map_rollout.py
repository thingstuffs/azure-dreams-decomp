"""Conservative interval precedence: leftover status never erases recovered code."""
import sys
import json
import tempfile
from pathlib import Path
import unittest

sys.path.insert(0,str(Path(__file__).resolve().parents[1]))
import byte_map_rollout as R


def span(a,n,category,priority):
    return dict(foff=a,size=n,category=category,priority=priority,
                label='unknown' if category=='unresolved' else 'proven_code',evidence=category)


class ConservativePartition(unittest.TestCase):
    def test_recovered_code_in_dead_image_keeps_its_code_identity(self):
        out=R.partition(32,[span(0,32,'unresolved',0),span(4,24,'leftover',30),span(8,8,'c',90)])
        self.assertEqual([(s['foff'],s['size'],s['category']) for s in out],
                         [(0,4,'unresolved'),(4,4,'leftover'),(8,8,'c'),(16,12,'leftover'),(28,4,'unresolved')])

    def test_nested_expired_witnesses_cannot_leak_into_a_gap(self):
        out=R.partition(32,[span(0,32,'unresolved',0),span(0,16,'leftover',30),
                            span(4,4,'c',90),span(8,16,'placement',100)])
        self.assertEqual(sum(s['size'] for s in out),32)
        self.assertEqual(out[-1]['category'],'unresolved')
        self.assertEqual((out[-1]['foff'],out[-1]['size']),(24,8))

    def test_positive_witness_cannot_escape_physical_container(self):
        with self.assertRaisesRegex(ValueError,'outside physical file'):
            R.partition(16,[span(0,16,'unresolved',0),span(15,2,'c',90)])

    def test_overlapping_footprints_are_counted_once(self):
        self.assertEqual(R.union([(0,8),(4,12),(12,16),(32,40)]),[(0,16),(32,40)])


class CensusReplay(unittest.TestCase):
    def fixture(self, root, spans=None, counts=None):
        lane=root/'census'
        (lane/'spans').mkdir(parents=True)
        proof=root/'config/census'
        proof.mkdir(parents=True)
        (proof/'snapshot.json').write_text(json.dumps({'base':'B13'}))
        (proof/'rules.json').write_text(json.dumps({'rules':{
            'census:'+kind:{'kind':kind,'label':label} for kind,label in [
                ('T1_twin','strongly_code'),('noncode:decode','noncode_typing_pending'),
                ('unknown','unknown'),('a','unknown'),('b','unknown'),
                ('audit+noncode_confirmed','proven_data'),('guess','guessed_data')]}}))
        source=root/'reader.c'
        source.write_text('current registered reader\n')
        raw=spans or {'3 strongly_code':[[0,8,'T1_twin']],
                      '4 noncode_typing_pending':[[8,16,'noncode:decode']],
                      '6 unknown':[[16,20,'unknown']]}
        (lane/'spans/main.spans.json').write_text(json.dumps(raw))
        (lane/'census.json').write_text(json.dumps(dict(ledger_rev='B13',census=dict(main=dict(
            labels=counts or {'3 strongly_code':8,'4 noncode_typing_pending':8,'6 unknown':4})))))
        receipt=dict(base='B13',inputs={'reader.c':R.B.sha256(source)},outputs={},retail={'main':R.digest(b'x'*20)})
        (lane/'receipt.json').write_text(json.dumps(receipt))

    def test_terminal_noncode_and_shape_code_remain_distinct_from_unknown_and_c(self):
        with tempfile.TemporaryDirectory() as td:
            root=Path(td);self.fixture(root)
            physical,_=R.census_spans(root,dict(main=b'x'*20),root/'census')
            self.assertEqual([(s['label'],s['category']) for s in physical['main']],
                             [('strongly_code','strongly_code'),('noncode_typing_pending','data_asset'),('unknown','unresolved')])

    def test_stale_reader_is_rejected_before_classification(self):
        with tempfile.TemporaryDirectory() as td:
            root=Path(td);self.fixture(root)
            (root/'reader.c').write_text('changed\n')
            with self.assertRaisesRegex(ValueError,'input/output changed'):
                R.census_spans(root,dict(main=b'x'*20),root/'census')

    def test_overlap_cannot_hide_behind_matching_total_bytes(self):
        with tempfile.TemporaryDirectory() as td:
            root=Path(td);self.fixture(root,{'6 unknown':[[0,10,'a'],[8,18,'b']]},{'6 unknown':20})
            with self.assertRaisesRegex(ValueError,'gap or overlap'):
                R.census_spans(root,dict(main=b'x'*20),root/'census')

    def test_unsupported_class_is_rejected(self):
        with tempfile.TemporaryDirectory() as td:
            root=Path(td);self.fixture(root,{'7 guessed_data':[[0,20,'guess']]},{'7 guessed_data':20})
            with self.assertRaisesRegex(ValueError,'unsupported census class'):
                R.census_spans(root,dict(main=b'x'*20),root/'census')

    def test_census_data_gets_no_invented_c_type(self):
        with tempfile.TemporaryDirectory() as td:
            root=Path(td);self.fixture(root,{'4 proven_data':[[0,20,'audit+noncode_confirmed']]},{'4 proven_data':20})
            physical,_=R.census_spans(root,dict(main=b'x'*20),root/'census')
            entry=R.B.metadata(physical['main'][0])
            self.assertEqual(entry['kind'],'asset')
            self.assertNotIn('type',entry)
            self.assertEqual(entry['sha256'],R.digest(b'x'*20))


class DeveloperRecords(unittest.TestCase):
    def test_separator_is_not_counted_as_records_or_invented_padding(self):
        def record(name,value):
            return name+bytes(32-len(name))+value.to_bytes(4,'little')
        blob=record(b'first',123)+bytes(4)+record(b'second',456)
        proof=R.leftover_audit.symbol_tables(blob,0,len(blob))
        self.assertEqual(proof['records'],2)
        self.assertEqual([r['size'] for r in proof['regions']],[36,4,36])
        self.assertIn('no padding claim',proof['regions'][1]['format'])
        self.assertNotIn('first',json.dumps(proof))
        self.assertNotIn('second',json.dumps(proof))


if __name__=='__main__':unittest.main()
