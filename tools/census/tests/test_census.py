"""Census precision, read identity, precedence and non-propagating recovery."""
import collections, copy, sys, unittest, json, hashlib, tempfile
from pathlib import Path
from unittest.mock import patch
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import census as C

class Census(unittest.TestCase):
    def test_neighbour_mixed_labels_and_return_protection(self):
        b=bytes(range(64))
        self.assertEqual(C.neighbour_choice(b,16,24,'4 proven_data','5 padding_leftover'),'4 noncode_typing_pending')
        self.assertEqual(C.neighbour_choice(b,16,24,'4 proven_data','4 proven_data'),'4 proven_data')
        self.assertIsNone(C.neighbour_choice(b,16,24,'1 proven_code','4 proven_data'))
        self.assertIsNone(C.neighbour_choice(b,16,32,'4 proven_data','4 proven_data'))
        ret=b[:16]+bytes.fromhex('0800e003')+b[20:]
        self.assertIsNone(C.neighbour_choice(ret,17,24,'4 proven_data','4 proven_data'))

    def test_neighbour_does_not_propagate_or_bridge_unknown(self):
        sp={'4 proven_data':[[0,8,'data'],[28,40,'data']],
            '6 unknown':[[8,16,'unknown'],[16,28,'unresolved:other']]}
        self.assertEqual(C.neighbour_candidates(bytes(range(40)),sp),[])

    def test_neighbour_removes_exact_original_unknown_once(self):
        l,b=self.inputs();sp={c:collections.defaultdict(list,{'4 proven_data':[[0,4,'data'],[12,16,'data']],'6 unknown':[[4,12,'unknown']]}) for c in C.CONTS}
        import tempfile
        with tempfile.TemporaryDirectory() as td:
            root=Path(td)
            for c in C.CONTS:
                p=root/C.FILES[c];p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(bytes(range(16)))
            lab={c:{} for c in C.CONTS};v={'admitted_labels':['4 proven_data']}
            out=C.apply_neighbours(lab,sp,v,root)
            for c in C.CONTS:
                self.assertEqual(lab[c]['labels'],{'4 proven_data':16})
                self.assertEqual(out[c]['bytes'],8)
                self.assertEqual(sp[c]['6 unknown'],[])

    def test_replayed_prefix_hashes_refuse_source_or_body_drift(self):
        import struct
        with tempfile.TemporaryDirectory() as td:
            root=Path(td);src=root/'src/main/func_80010000.c';src.parent.mkdir(parents=True);src.write_text('void func_80010000(void) {}')
            ledger=root/'ledger';ledger.mkdir();(ledger/'rows.jsonl').write_text(json.dumps({'id':'main/func_80010000','container':'main','func':'func_80010000','foff':0,'size':20})+'\n')
            body=struct.pack('<5I',0x3c028001,0x8c426000,0x27bdffe8,0x03e00008,0x27bd0018);b=body+bytes(12)+body+bytes(12);binary=root/C.FILES['main'];binary.parent.mkdir(parents=True);binary.write_bytes(b)
            rec={'container':'main','foff':32,'size':8,'complete_size':20,'donor':'main/func_80010000','source':'src/main/func_80010000.c','source_sha256':hashlib.sha256(src.read_bytes()).hexdigest(),'complete_bytes_sha256':hashlib.sha256(body).hexdigest(),'donor_bytes_sha256':hashlib.sha256(body).hexdigest(),'strict_replay':'MATCH','relocations':[]}
            records=root/'proof.jsonl';records.write_text(json.dumps(rec)+'\n');l,_=self.inputs();C.apply_replayed_code(l,root,root,[records]);self.assertEqual(l['main']['replayed_twin_prefix'],[[32,40]])
            src.write_text('changed')
            with self.assertRaises(AssertionError):C.apply_replayed_code(l,root,root,[records])
            src.write_text('void func_80010000(void) {}');binary.write_bytes(b[:32]+bytes(4)+b[36:])
            with self.assertRaises(AssertionError):C.apply_replayed_code(l,root,root,[records])

    def test_unrounded_gate(self):
        v={'detectors':{t:dict(tp=998996,fp_struct=1004,fp_entropy=0) for t in C.ADMIT}}
        self.assertEqual(C.admitted_tiers(v),[])
        for d in v['detectors'].values():d.update(tp=999000,fp_struct=1000)
        self.assertEqual(C.admitted_tiers(v),list(C.ADMIT))

    def test_complete_masked_prefix_requires_safe_prelude_and_whole_twin(self):
        from masked_prefix_probe import detect
        suffix=[0x27bdffe8,0xafbf0014]+[0]*8+[0x03e00008,0x27bd0018]
        words=[0x3c028001,0x8c426000]+suffix
        segs=[[2,len(words),'framed',True]]
        h=C.whole_hash(words,0,len(words));folds=({h},set())
        out,hits=detect(words,segs,folds)
        self.assertEqual(out,{0:[[0,8]],1:[]})
        self.assertEqual(hits,[[0,8,56,[0]]])
        self.assertEqual(detect(words,segs,(set(),set()))[1],[])
        self.assertEqual(detect(words,[[2,len(words),'framed',False]],folds)[1],[])
        for unsafe in [0x27bdfff8,0x3c1a8001,0x3c1b8001,0x0c000000,0x10000000,0x3c108001]:
            changed=[unsafe,words[1]]+suffix
            candidate=C.whole_hash(changed,0,len(changed))
            self.assertEqual(detect(changed,segs,({candidate},set()))[1],[],hex(unsafe))

    def test_isolated_entry_keeps_lane_detector_binding_after_gate_import_path(self):
        import subprocess,textwrap
        code=textwrap.dedent('''
            import runpy,sys
            from pathlib import Path
            lane=Path.cwd();sys.argv=['census.py','--help']
            try:runpy.run_path('census.py',run_name='__main__')
            except SystemExit as exc:assert exc.code==0
            sys.path.insert(0,str(lane.parents[1]/'tools'))
            import census,masked_prefix_probe
            assert census.HERE==lane and census.K==12
            assert masked_prefix_probe.C is census
        ''')
        result=subprocess.run([sys.executable,'-B','-I','-c',code],cwd=Path(__file__).resolve().parents[1],capture_output=True,text=True)
        self.assertEqual(result.returncode,0,result.stderr)

    def test_complete_masked_prefix_cross_fold_precision_gate_is_exact(self):
        from masked_prefix_probe import validate
        l,b=self.inputs();rows={c:[] for c in C.CONTS};iv={c:{0:[],1:[]} for c in C.CONTS}
        l['main']['c_row']=[[0,998996]];l['main']['data_row']=[[998996,1000000]]
        iv['main'][0]=[[0,1000000]]
        self.assertFalse(validate(l,b,rows,iv)['admitted'])
        l['main']['c_row']=[[0,999000]];l['main']['data_row']=[[999000,1000000]]
        self.assertTrue(validate(l,b,rows,iv)['admitted'])
        import zlib
        rid=next('main/fixture'+str(i) for i in range(10) if zlib.crc32(('main/fixture'+str(i)).encode()) & 1 == 0)
        rows['main']=[(0,999000,rid)]
        self.assertEqual(validate(l,b,rows,iv)['totals']['tp'],0)
        iv['main'][1]=iv['main'][0]
        self.assertEqual(validate(l,b,rows,iv)['totals']['tp'],999000)

    def test_complete_masked_prefix_preserves_precedence_and_requires_both_gates(self):
        base={'4 proven_data':[[0,4,'typed']],'6 unknown':[[4,12,'unknown']],'5 padding_leftover':[[12,16,'zero']]}
        for enabled,tiers,expected in [(False,['T1_twin'],0),(True,[],0),(True,['T1_twin'],6)]:
            l,b=self.inputs();sp={c:collections.defaultdict(list,copy.deepcopy(base)) for c in C.CONTS};lab={c:{'code_over_audit_data':{}} for c in C.CONTS}
            iv={c:{0:[[2,10]],1:[]} for c in C.CONTS}
            result=C.apply_masked_prefixes(lab,sp,l,iv,{'admitted':enabled},tiers)
            self.assertEqual(result['main']['bytes'],expected)
            self.assertEqual(sp['main']['4 proven_data'],base['4 proven_data'])
            self.assertEqual(sp['main']['5 padding_leftover'],base['5 padding_leftover'])
            self.assertEqual(sp['main']['6 unknown'],[[10,12,'unknown']] if expected else base['6 unknown'])

    def inputs(self):
        l={c:collections.defaultdict(list) for c in C.CONTS}
        b={c:dict(n=16,crit={},fmt={k:[] for k in C.FMT+['entropy','noncode_decode']},tier_kinds={},zero=[]) for c in C.CONTS}
        return l,b

    def test_pending_is_terminal_and_partial_stays_proven(self):
        l,b=self.inputs();C.G['root']=str(Path(__file__).resolve().parents[3]);C.G.pop('loaded_extents',None)
        for c in C.CONTS:b[c]['fmt']['entropy']=[[0,16]]
        l['main']['instance_partial']=[[0,16]]
        labels,spans=C.label(l,b,[])
        self.assertEqual(labels['main']['labels'],{'1 proven_code':16})
        for c in C.CONTS[1:]:self.assertEqual(labels[c]['labels'],{'4 noncode_typing_pending':16})

    def test_evidence_binary_is_read_once_and_tampering_is_refused(self):
        with tempfile.TemporaryDirectory() as td:
            root=Path(td);binary=root/C.FILES['main'];binary.parent.mkdir(parents=True);binary.write_bytes(bytes(range(16)))
            source=root/'source.c';source.write_text('int value;')
            rec=dict(container='main',foff=0,size=4,source='source.c',source_sha256=hashlib.sha256(source.read_bytes()).hexdigest(),bytes_sha256=hashlib.sha256(bytes(range(4))).hexdigest())
            records=root/'reads.jsonl';records.write_text(json.dumps(rec)+'\n'+json.dumps(rec)+'\n')
            original=Path.read_bytes;reads=[]
            def measured(p):
                if p==binary:reads.append(p)
                return original(p)
            l,b=self.inputs()
            with patch.object(Path,'read_bytes',measured):C.apply_read_evidence(l,root,root,[records])
            self.assertEqual(len(reads),1)
            source.write_text('int changed;')
            with self.assertRaises(AssertionError):C.apply_read_evidence(l,root,root,[records])

    def test_instruction_identity_is_a_hash_and_must_still_be_a_matched_load(self):
        import struct
        with tempfile.TemporaryDirectory() as td:
            root=Path(td);source=root/'source.c';source.write_text('synthetic matched reader')
            word=struct.pack('<I',0x8c220000)
            blob=word+bytes(4)+b'abcd'
            binary=root/C.FILES['main'];binary.parent.mkdir(parents=True);binary.write_bytes(blob)
            record=dict(container='main',foff=8,size=4,source='source.c',
                        source_sha256=hashlib.sha256(source.read_bytes()).hexdigest(),
                        bytes_sha256=hashlib.sha256(b'abcd').hexdigest(),read_foff=0,
                        read_sha256=hashlib.sha256(word).hexdigest())
            proof=root/'reads.jsonl'
            def apply(rec,matched=True):
                proof.write_text(json.dumps(rec)+'\n');layers,_=self.inputs()
                if matched:layers['main']['c_row']=[[0,4]]
                return C.apply_read_evidence(layers,root,root,[proof])
            self.assertEqual(apply(record)[0]['records'],1)
            with self.assertRaisesRegex(AssertionError,'instruction changed'):
                apply(dict(record,read_sha256='0'*64))
            with self.assertRaisesRegex(AssertionError,'outside matched C'):apply(record,False)
            arithmetic=struct.pack('<I',0x24420001)
            binary.write_bytes(arithmetic+blob[4:])
            with self.assertRaisesRegex(AssertionError,'instruction changed'):
                apply(dict(record,read_sha256=hashlib.sha256(arithmetic).hexdigest()))

    def test_shape_only_is_visible_and_gated(self):
        l,b=self.inputs();C.G['root']=str(Path(__file__).resolve().parents[3])
        for c in C.CONTS:b[c]['crit']['T4_shape_noref']=[[0,16]]
        labels,_=C.label(l,b,['T4_shape_noref'])
        self.assertEqual(labels['main']['labels'],{'3 strongly_code':16})
        self.assertEqual(labels['main']['kinds']['3 strongly_code'],{'strongly code (shape only):T4_shape_noref':16})
        labels,_=C.label(l,b,[])
        self.assertEqual(labels['main']['labels'],{'6 unknown':16})


if __name__=='__main__': unittest.main()
