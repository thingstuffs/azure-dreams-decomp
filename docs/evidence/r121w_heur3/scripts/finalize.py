from pathlib import Path
import collections,csv,hashlib,json,re,shutil,subprocess,sys,datetime
LANE=Path(__file__).resolve().parents[1];ROOT=LANE.parents[2]
sys.path.insert(0,str(ROOT/'tools'))
import common,coverage as cv,status,verify
from stage import freeze,append,EVIDENCE

def digest(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def dump(p,x):p.parent.mkdir(parents=True,exist_ok=True);p.write_text(json.dumps(x,indent=1)+'\n')
def table(path,rows,fields):
 with path.open('w') as f:
  w=csv.DictWriter(f,fields,delimiter='\t',lineterminator='\n');w.writeheader();w.writerows(rows)
def civ(rows,c):return cv.merge([cv.extent(r) for r in rows if r['container']==c and r.get('foff') is not None and (r.get('func') or '').startswith('func_')])
def count(a,b,ivs):return cv.size(cv.intersection([[a,b]],ivs))

def negative():
 rows={r['id']:r for r in common.rows()};p=json.loads((LANE/'evidence/staged.json').read_text())[0];src=ROOT/p['clean_source'];text=src.read_text();assert '0x1C,' in text
 q=LANE/'scratch/negative_control.c';q.write_text(text.replace('0x1C,','0x1D,',1));r=verify.verify_overlay(rows[p['id']],q,include_root=ROOT/'include')
 assert not r.get('exact') and r.get('total',0)>0,r
 dump(LANE/'evidence/negative_control.json',dict(id=p['id'],change='slot argument 28 -> 29',original_source_sha256=digest(src),control_source_sha256=digest(q),measurement=r,passed=True))
 print('one-word semantic negative control rejected',r['total'])

def audit_prefixes():
 B=(ROOT/'work/disc/containers/DUNGEON_DUNGEON.BIN').read_bytes();import struct
 out=[]
 for i in range(7):
  a=0xd07074+i*0x6000;v=0x80170874-i*0x6000;start=a-8;end=a+1144;body=B[start:end];w=struct.unpack('<'+'I'*(len(body)//4),body)
  assert w[0]>>26==15 and w[1]>>26==35 and w[2]>>16==0x27bd
  assert w[-2]==0x03e00008
  out.append(dict(container='dungeon',detector_foff=hex(a),detector_size=1144,complete_start_candidate=hex(start),complete_size_candidate=1152,candidate_vma=hex(v-8),prefix_bytes=8,body_sha256=hashlib.sha256(body).hexdigest(),status='HOLD',reason='load-before-prologue prefix precedes detector start; complete C, entry and production placement proof still required'))
 dump(LANE/'evidence/large_entry_audit.json',out)
 print('large complete-start candidates',len(out))

def facts():
 ps=json.loads((LANE/'evidence/staged.json').read_text());scores={s['id']:s for s in json.loads((LANE/'evidence/scores.json').read_text())};now=datetime.datetime.now(datetime.timezone.utc).isoformat()
 assert len(ps)==len(scores) and all(scores[p['id']]['source']['exact'] for p in ps)
 if (LANE/'evidence/facts_appended.json').exists():return
 for p in ps:
  for ledger,kind in [('baseline','raw'),('promotions','source'),('reverify','source')]:
   s=scores[p['id']][kind];path=p['raw_source'] if kind=='raw' else p['clean_source'];h=digest(ROOT/path)
   r=dict(s,id=p['id'],row=p['id'],event_id='r121w_heur3:'+ledger+':'+p['id'],at=now,lane='r121w_heur3',reviewer='pending',cfg=p['cfg'],source=path,source_sha=h,src_sha=h,candidate_sha256=h,evidence=EVIDENCE,source_kind='raw-generated-first-pass' if kind=='raw' else 'new-clean-C')
   if ledger=='promotions':r.update(outcome='landed',method='native-ELF-and-canonical-row-score-and-scoped-production-window')
   append('ledger/'+ledger+'.jsonl',r)
 dump(LANE/'evidence/facts_appended.json',dict(rows=len(ps),at=now))
 table(LANE/'levels_seed_needed.tsv',[dict(id=p['id'],source=p['clean_source'],source_exact=True,raw_exact=scores[p['id']]['raw']['exact'],reason='new C; integration must derive levels under its ordinary policy') for p in ps],['id','source','source_exact','raw_exact','reason'])

def measure():
 ps=json.loads((LANE/'evidence/staged.json').read_text());now=common.rows();base=[json.loads(s) for s in (LANE/'scratch/preimage/ledger/rows.jsonl').read_text().splitlines() if s];before={c:civ(base,c) for c in ['main','town','dungeon','ovmovie']};after={c:civ(now,c) for c in before};new={c:cv.subtract(after[c],before[c]) for c in before}
 assert sum(cv.size(v) for v in new.values())==sum(p['size'] for p in ps)==3520
 sdk={c:[] for c in before};latest={}
 for r in common.read_jsonl(ROOT/'ledger/coverage_regions.jsonl'):latest[(r['container'],r['foff'],r['size'],r['category'])]=r
 for r in latest.values():
  if r['category']=='sdk_asm' and r.get('active',True):sdk[r['container']].append(cv.extent(r))
 inv=list(csv.DictReader((LANE/'inventory.tsv').open(),delimiter='\t'));results=[];holds=[]
 input_rows=[]
 for i,r in enumerate(inv):input_rows.append(dict(queue=r['queue'],item=str(i+1),container=r['container'],foff=r['foff'],size=int(r['size']),prior_reason='heuristic shape; no complete C owner' if r['queue']=='status_estimated_code' else 'historical split without C'))
 for fn in ['holds2','handoff_code','next']:
  for i,r in enumerate(csv.DictReader((LANE/f'refs/{fn}.tsv').open(),delimiter='\t')):
   input_rows.append(dict(queue=fn,item=str(i+1),container=r['container'],foff=r.get('foff',''),size=int(r.get('bytes',r.get('size',0))),prior_reason=r.get('reason',r.get('donor_review',r.get('status',''))),prior_status=r.get('status',''),evidence=r.get('evidence','')))
 native=json.loads((LANE/'evidence/native_replay.json').read_text());known_reasons={(r['container'],int(r['foff'],0),r['size']):r['reason'] for r in native}
 for q in input_rows:
  c=q['container'];n=q['size'];a=int(q['foff'],0) if q['foff'] else None;b=a+n if a is not None else None
  terminal=q['queue']=='next' and 'terminal' in q.get('prior_status','')
  if a is None or c not in before or terminal:
   bc=ac=lb=0;held=0 if terminal else n;status_='TERMINAL_NONCODE_TYPING_PENDING' if terminal else 'HOLD';classification='inherited_noncode_typing_pending' if terminal else 'unresolved';remaining=[[a,b]] if a is not None and held else []
  else:
   bc=count(a,b,before[c]);ac=count(a,b,new[c]);rem=cv.subtract([[a,b]],after[c]);lb=cv.size(cv.intersection(rem,sdk[c]));remaining=cv.subtract(rem,sdk[c]);held=cv.size(remaining)
   status_='DELIVERED_NEW_C' if ac==n else 'PARTIAL_NEW_C' if ac else 'ALREADY_C' if bc==n else 'SDK_LIBRARY' if lb==n else 'HOLD' if held else 'CLASSIFIED'
   classification='compiled_C' if ac==n or bc==n else 'inherited_SDK_library_code' if lb==n else 'mixed_C_and_unresolved' if ac or bc else 'unresolved_code_or_entry'
  reason=q['prior_reason']
  if a is not None and (c,a,n) in known_reasons and held:reason=known_reasons[c,a,n]
  if q['queue']=='handoff_code' and c=='dungeon' and a is not None and any(a==0xd07074+i*0x6000 for i in range(7)):reason='detector omits 8-byte load prefix; complete 1152-byte function C and placement proof needed'
  if q['queue']=='handoff_code' and c=='town' and a==0x5c70c8:reason='84-byte clean candidate is exact; true-address name already belongs to another scene function'
  r=dict(queue=q['queue'],item=q['item'],container=c,foff=q['foff'],size=n,base_C=bc,added_C=ac,SDK_library=lb,held=held,noncode=n if terminal else 0,status=status_,classification=classification,reason=reason,evidence='docs/evidence/r121w_heur3/receipts.json' if ac else q.get('evidence',''))
  results.append(r)
  for lo,hi in remaining:
   holds.append(dict(queue=q['queue'],item=q['item'],container=c,foff=hex(lo),size=hi-lo,reason=reason,next_action='reconstruct complete natural C and preserve genuine first pass' if 'relocation' in reason else 'supply independent entry/base, complete donor or bounded reader evidence',evidence=q.get('evidence','')))
 # SLUS's old bucket is 204 bytes of startup plus three non-code 8-byte blobs.
 for a,n,classification,reason in [(0x101f8,204,'startup_assembly','SLUS startup main: ordinary C and complete linked-EXE proof not recovered'),(0x37e80,8,'inherited_data','MSC00 SDK member header words; existing bin split'),(0x39788,8,'inherited_padding','zero alignment after RotMatrixZ; existing bin split'),(0x3d608,8,'inherited_data','SDK member header; existing bin split')]:
  results.append(dict(queue='status_slus_other',item=hex(a),container='slus',foff=hex(a),size=n,base_C=0,added_C=0,SDK_library=0,held=n if classification=='startup_assembly' else 0,noncode=0 if classification=='startup_assembly' else n,status='HOLD' if classification=='startup_assembly' else 'INHERITED_NONCODE',classification=classification,reason=reason,evidence='config/slus_006.14.yaml'))
  if classification=='startup_assembly':holds.append(dict(queue='status_slus_other',item=hex(a),container='slus',foff=hex(a),size=n,reason=reason,next_action='recover startup C at unchanged SLUS recipe and require full executable link/SHA1 proof',evidence='config/slus_006.14.yaml'))
 fields=['queue','item','container','foff','size','base_C','added_C','SDK_library','noncode','held','status','classification','reason','evidence']
 assert all(r['base_C']+r['added_C']+r['SDK_library']+r['noncode']+r['held']==r['size'] for r in results), 'measurement partition failure'
 table(LANE/'measure.tsv',[r for r in results if r['queue'].startswith('status_')],fields);table(LANE/'results.tsv',results,fields);table(LANE/'holds.tsv',holds,['queue','item','container','foff','size','reason','next_action','evidence'])
 stats={q:dict(items=sum(r['queue']==q for r in results),added_C=sum(r['added_C'] for r in results if r['queue']==q),held=sum(r['held'] for r in results if r['queue']==q)) for q in sorted({r['queue'] for r in results})}
 dump(LANE/'evidence/queue_summary.json',stats)
 dump(LANE/'evidence/status_after.json',status.not_yet_c(ROOT))
 large=LANE/'scratch/donor_leads.json';leads=json.loads(large.read_text())
 dump(LANE/'evidence/discovery_summary.json',dict(full_receipt='scratch/donor_leads.json',full_receipt_bytes=large.stat().st_size,full_receipt_sha256=digest(large),hits=len(leads),unique_sites=len({(r['container'],r['foff'],r['size']) for r in leads}),native_sites=len(native),native_holds=dict(collections.Counter(r['reason'] for r in native)),discovery_masks_grant_no_admission=True))
 print('queue totals (overlapping queues must not be added)',stats)

if __name__=='__main__':
 if sys.argv[1]=='negative':negative()
 elif sys.argv[1]=='prefixes':audit_prefixes()
 elif sys.argv[1]=='facts':facts()
 elif sys.argv[1]=='measure':measure()
