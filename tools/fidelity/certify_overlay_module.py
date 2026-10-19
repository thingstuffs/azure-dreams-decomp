#!/usr/bin/env python3
"""Certify a reviewed overlay module in an exported, isolated build view.

The view must contain canonical src/, ledger/, config/, gate and fidelity tools.
After any source/tool patch, regenerate the view and graph and reissue proofs.
No historical l4_modules event is authority. Unsupported modules fail closed.
"""
import argparse,contextlib,fcntl,hashlib,json,os,shutil,sys,time
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
ROOT=Path(__file__).resolve().parents[2]
sys.path[:0]=[str(ROOT/'tools'),str(ROOT/'tools/gate')]
from overlay_module_gate import build,command,CONTAINERS,affected_windows,fingerprint,load_modules,sha
from overlay_module_evidence import certificate_reason

def artifact_inventory(directory):
 directory=Path(directory);result={}
 for p in sorted(directory.rglob('*')):
  if p.is_symlink():raise ValueError('linked fresh gate artifact')
  if p.is_file():result[p.relative_to(directory).as_posix()]=sha(p)
 return result

def snapshot_gate_window(view,wn,directory,transaction,record,lines):
 """Freeze a real gate's output under its window lock, before another clean."""
 import yaml
 directory=Path(directory);cfg=yaml.safe_load((view/wn).read_text());name=cfg['name']
 bd=view/cfg['standalone_build']['work_dir']/name/'build'
 if not (bd/'modules.json').is_file():return None  # no native-module projection to certify
 projections=json.loads((bd/'modules.json').read_text())
 if not projections:return None
 final=directory/name;tmp=directory/(name+'.tmp')
 if tmp.exists():shutil.rmtree(tmp)
 tmp.mkdir()
 try:
  (tmp/'gate.log').write_text('\n'.join(lines)+'\n')
  shutil.copy2(bd/(name+'.window.bin'),tmp/'window.bin')
  shutil.copy2(bd.parent/(name+'_manifest.json'),tmp/'manifest.json')
  shutil.copy2(bd/'modules.json',tmp/'modules.json')
  shutil.copytree(bd/'modules',tmp/'modules')
  rec={'schema':1,'transaction':transaction,'config':wn,'gate':record,
       'artifacts':artifact_inventory(tmp)}
  (tmp/'receipt.json').write_text(json.dumps(rec,sort_keys=True)+'\n')
  if final.exists():shutil.rmtree(final)
  tmp.rename(final)
  return sha(final/'receipt.json')
 except BaseException:
  if tmp.exists():shutil.rmtree(tmp)
  raise

def fresh_window_source(view,wn,directory,transaction):
 """A journal cache hit alone is never a transferable fresh proof."""
 if directory is None:return None
 directory=Path(directory);authority=(view/'ledger').resolve().parent
 index=json.loads((directory/'index.json').read_text())
 if (index.get('schema')!=1 or index.get('result')!='PASS' or index.get('transaction')!=transaction
     or index.get('authority')!=str(authority) or index.get('view')!=str(view.resolve())
     or index.get('gate_tool_sha256')!=sha(authority/'tools/build/gate_all.py')):
  raise ValueError('fresh gate receipt context differs')
 import yaml
 name=yaml.safe_load((view/wn).read_text())['name']
 expected=index['windows'].get(wn)
 if expected is None:return None
 snapshot=directory/name
 if snapshot.is_symlink() or not snapshot.resolve().is_relative_to(directory.resolve()):raise ValueError('fresh gate receipt path escapes')
 if sha(snapshot/'receipt.json')!=expected:raise ValueError('fresh gate receipt changed')
 rec=json.loads((snapshot/'receipt.json').read_text())
 if rec.get('schema')!=1 or rec.get('transaction')!=transaction or rec.get('config')!=wn or rec.get('gate',{}).get('result')!='MATCH':raise ValueError('fresh gate receipt identity differs')
 from build import gate_all as A
 with A.inputs_snapshot():current=A.inputs_sha(authority/wn)
 if rec['gate'].get('inputs_sha')!=current:return None
 actual=artifact_inventory(snapshot);actual.pop('receipt.json',None)
 if actual!=rec['artifacts']:raise ValueError('fresh gate artifacts changed')
 return snapshot

def adopt_window_module(m,source,dest,before):
 """Install the window gate's own module proof as the certificate's module proof directory.

 It must be a canonical whole-TU receipt for this module at the certificate's fingerprint, with no
 candidate substitution; certificate_reason then re-checks every artifact, replays the native
 rodata/trim proof and compares the bytes with retail, exactly as for a locally built proof."""
 source=Path(source);dest=Path(dest)
 if source.is_symlink() or any(p.is_symlink() for p in source.rglob('*')):raise ValueError('linked window module proof')
 r=json.loads((source/'receipt.json').read_text())
 if r.get('module')!=m['key'] or r.get('fingerprint')!=before or r.get('candidates')!={} or r.get('candidate_paths')!={}:
  raise ValueError('window module proof is not this module at this fingerprint')
 for name,h in r.get('artifacts',{}).items():
  if sha(source/name)!=h:raise ValueError('window module artifact changed: '+name)
 tmp=dest.with_name(dest.name+'.tmp')
 if tmp.exists():shutil.rmtree(tmp)
 shutil.copytree(source,tmp)
 if dest.exists():shutil.rmtree(dest)
 tmp.rename(dest)
 return r

@contextlib.contextmanager
def certification_window_lock(root,name):
 p=root/'work'/('cert-'+name+'.lock');p.parent.mkdir(parents=True,exist_ok=True)
 with p.open('a') as f:
  fcntl.flock(f,fcntl.LOCK_EX)
  try:yield
  finally:fcntl.flock(f,fcntl.LOCK_UN)

def home_projection(records,key):
 matches=[r for r in records if r.get('module')==key and not r.get('placement')]
 if len(matches)!=1:raise ValueError('window lacks unique native home projection: '+key)
 return matches[0]

def certify(key,root,reviewer,gate_receipts=None,transaction=None,window_workers=8):
 root=Path(root).absolute()
 import overlay_scoped_fingerprint as scoped
 if scoped.enabled(root):scoped.reject_environment()
 authority=(root/'ledger').resolve().parent;m=next(m for m in load_modules(root) if m['key']==key)
 import overlay_module_placements as MP
 placement_renewals=[s['placement']['key'] for s in MP.recorded_statuses(authority) if s['placement']['module']==key and not s['valid']]
 if placement_renewals and gate_receipts is None:raise ValueError('recorded module placements require fresh canonical gate receipts: '+str(placement_renewals))
 if m['review']['reviewer']!=reviewer or any(m['review'][k]!='reviewed' for k in ['membership','types','ownership']):raise ValueError('review incomplete')
 # Exported JSON must be exactly the canonical split ledger, including every neighbour.
 import yaml
 for wn in affected_windows(m,root):
  sb=yaml.safe_load((root/wn).read_text())['standalone_build']
  for g in [{'results':sb['split_results']},*sb['matched_sources']]:
   family=Path(g['results']).parts[1]
   expected=[json.loads(l) for l in (root/'ledger/splits'/f'{family}.jsonl').read_text().splitlines() if l.strip()]
   if json.loads((root/g['results']).read_text())!=expected:raise ValueError('exported split roster differs: '+g['results'])
 before=fingerprint(m,root);out=root/'work/module_proofs'/key;out.mkdir(parents=True,exist_ok=True)
 # With fresh gate receipts the module proof is the one the gate built for its windows (the same
 # build(), same fingerprint, copied into every certificate window as module/receipt.json);
 # building it again here only repeated that work. Without receipts: build as before.
 r=None if gate_receipts is not None else build(m,out/'module',root)[0];windows=[]
 def prove_window(wn):
  cfg=yaml.safe_load((root/wn).read_text());name=cfg['name'];sb=cfg['standalone_build'];win=out/'windows'/name;win.mkdir(parents=True,exist_ok=True)
  with certification_window_lock(root,name):
   fresh=fresh_window_source(root,wn,gate_receipts,transaction)
   if fresh:
    blob=fresh/'window.bin';manifest=fresh/'manifest.json';modules=fresh/'modules'
    shutil.copy2(fresh/'gate.log',win/'gate.log');records=json.loads((fresh/'modules.json').read_text())
   else:
    env=dict(os.environ,TMPDIR=str(root/'work'),PYTHONDONTWRITEBYTECODE='1')
    command([sys.executable,root/'tools/overlay_local_gate.py','--config',wn,'--clean'],root,env,win/'gate.log',timeout=1800)
    bd=root/sb['work_dir']/name/'build';blob=bd/(name+'.window.bin');manifest=bd.parent/(name+'_manifest.json');modules=bd/'modules'
    records=json.loads((bd/'modules.json').read_text())
   fs=sb['window']['file_start'];fe=sb['window']['file_end']
   with (root/'work/disc/containers'/CONTAINERS[m['container']]).open('rb') as f:f.seek(fs);ret=f.read(fe-fs)
   if blob.read_bytes()!=ret:raise ValueError('affected window mismatch')
   # The durable certificate format and every authoritative check are unchanged.
   shutil.copy2(blob,win/'window.bin');shutil.copy2(manifest,win/'manifest.json')
   pr=home_projection(records,key)
   (win/'projection.json').write_text(json.dumps(pr,indent=2)+'\n')
   shutil.copytree(modules/key,win/'module',dirs_exist_ok=True)
  print(json.dumps({'step':'certificate-window','module':key,'config':wn,'gate':'reused' if fresh else 'built'}),flush=True)
  result={'config':wn,'result':'MATCH','file_start':fs,'file_end':fe,'proof_dir':str(win.relative_to(authority)),'artifacts':{n:sha(win/n) for n in ['gate.log','window.bin','manifest.json','projection.json','module/receipt.json']}}
  if before.get('schema'):result['digest']=before['windows'][wn]['sha256']
  return result
 with ThreadPoolExecutor(max_workers=window_workers) as pool:
  windows=list(pool.map(prove_window,affected_windows(m,root)))
 if r is None:r=adopt_window_module(m,authority/windows[0]['proof_dir']/'module',out/'module',before)
 if before!=fingerprint(m,root):raise ValueError('inputs changed during full certification')
 cert={'schema':r['schema'],'kind':'overlay_module_placement','module':key,'members':r['members'],'at':time.strftime('%Y-%m-%dT%H:%M:%SZ',time.gmtime()),'reviewer':reviewer,'fingerprint':before,'proof_dir':str((out/'module').relative_to(authority)),'receipt_sha256':sha(out/'module/receipt.json'),'windows':windows}
 reason=certificate_reason(m,cert,authority)
 if reason:raise ValueError(reason)
 p=root/'ledger/modules'/('overlay_'+key+'.json');p.parent.mkdir(parents=True,exist_ok=True);tmp=p.with_suffix('.tmp');tmp.write_text(json.dumps(cert,indent=2)+'\n');tmp.replace(p)
 for placement in placement_renewals:
  MP.certify(placement,root,gate_receipts,transaction)
 return cert,p

def main():
 ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('module');ap.add_argument('--root',required=True,type=Path);ap.add_argument('--reviewer',required=True)
 ap.add_argument('--portable-output',type=Path,help='freeze this successful canonical certificate and all consumed inputs for a reviewed package')
 ap.add_argument('--placement',help='certify an explicit complete-module link placement instead of the home')
 ap.add_argument('--scratch-output',type=Path,help='compute a review-pending placement proof; never L4 authority')
 ap.add_argument('--gate-receipts',type=Path);ap.add_argument('--transaction');ap.add_argument('--window-workers',type=int,default=8)
 args=ap.parse_args()
 if bool(args.gate_receipts)!=bool(args.transaction) or args.window_workers<1:ap.error('receipt directory/token must be supplied together; window workers must be positive')
 if args.placement:
  import overlay_module_placements as P
  if args.gate_receipts is None:ap.error('module placements require fresh gate receipts')
  descriptor=next(x for x in P.load(args.root) if x['key']==args.placement)
  if descriptor['module']!=args.module:ap.error('placement belongs to another module')
  if not args.scratch_output and descriptor['review']['reviewer']!=args.reviewer:ap.error('placement reviewer differs')
  c,p=P.certify(args.placement,args.root,args.gate_receipts,args.transaction,output=args.scratch_output,scratch=bool(args.scratch_output))
 else:
  if args.scratch_output:ap.error('--scratch-output requires --placement')
  c,p=certify(args.module,args.root,args.reviewer,args.gate_receipts,args.transaction,args.window_workers)
 if args.portable_output:
  authority=(args.root/'ledger').resolve().parent;sys.path.insert(0,str(authority/'tools/lanes'))
  from proof_receipts import export_module, export_placement
  if args.scratch_output:ap.error('scratch placements cannot be exported as production authority')
  if args.placement:export_placement(authority,args.placement,args.portable_output)
  else:export_module(authority,args.module,args.portable_output)
 print(json.dumps({'module':c['module'],'members':c['members'],'certificate':str(p),'windows':[w['config'] for w in c['windows']],'result':'CERTIFIED'},indent=2))
if __name__=='__main__':main()
