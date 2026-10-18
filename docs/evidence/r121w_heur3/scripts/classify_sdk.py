from pathlib import Path
import hashlib,json,sys
from stage import ROOT,LANE,freeze,write,append

def main():
 if (LANE/'evidence/sdk_reconciliation.json').exists():raise SystemExit('SDK classification already reconciled')
 regions=[('main',0x2717c8,104),('main',0x2718a0,136),('main',0x271958,108),('ovmovie',0x163c,48),('ovmovie',0x166c,832)]
 files={'main':'MAIN_MAIN.BIN','ovmovie':'OVMOVIE.BIN'};proof=[]
 for c,a,n in regions:
  p=ROOT/'work/disc/containers'/files[c]
  with p.open('rb') as f:f.seek(a);b=f.read(n)
  rec=dict(schema='azure-clean.coverage-region.v1',container=c,foff=a,size=n,category='sdk_asm',active=True,evidence='docs/evidence/r121_remnants.sdk.json',basis='Reconcile existing complete Sony SDK member identification from coverage_residue into the reporting interval ledger; no new C or assembly admission',retail_sha256=hashlib.sha256(b).hexdigest(),lane='r121w_heur3')
  append('ledger/coverage_regions.jsonl',rec);proof.append(rec)
 p=ROOT/'tools/status.py';s=p.read_text();old='raw = inter(subtract(ss, C + data_all + cop), win)';new='''# An evidenced SDK interval remains library code when a historical split
        # view also names it. C and proven copies still have higher priority.
        raw = inter(subtract(ss, C + data_all + cop + cats["sdk_asm"]), win)'''
 assert s.count(old)==1
 write('tools/status.py',s.replace(old,new).replace('for k in ("unported", "sdk_asm", "estimated_code"):', 'for k in ("sdk_asm", "unported", "estimated_code"):'))
 p=ROOT/'tools/tests/test_status_states.py';s=p.read_text();marker="        self.assertEqual(res, {'town': dict(in_c=64, copies=32, split=32, sdk=16, unported=0, heuristic=8)})   # the 32 B estimate under the copy is not counted twice"
 addition='''
        # Independent SDK evidence takes precedence over a historical raw
        # split. Existing compiled C keeps priority over an SDK label.
        import json
        with (self.root / 'ledger/coverage_regions.jsonl').open('a') as f:
            for event in [dict(container='town', foff=96, size=16, category='sdk_asm'),
                          dict(container='town', foff=0, size=16, category='sdk_asm'),
                          dict(container='town', foff=96, size=16, category='unported')]:
                f.write(json.dumps(event) + '\\n')
        self.assertEqual(S.not_yet_c(self.root),
                         {'town': dict(in_c=64, copies=32, split=16, sdk=32, unported=0, heuristic=8)})
'''
 assert marker in s
 write('tools/tests/test_status_states.py',s.replace(marker,marker+addition))
 (LANE/'evidence/sdk_reconciliation.json').write_text(json.dumps(dict(inherited_evidence='docs/evidence/r121_remnants.sdk.json',events=proof,library_bytes_reconciled=1396,new_library_evidence_bytes=0,new_C_bytes=0),indent=1)+'\n')
 print('existing SDK classification reconciled; no C credit',sum(x['size'] for x in proof))
if __name__=='__main__':main()
