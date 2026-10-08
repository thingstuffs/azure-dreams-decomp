#!/usr/bin/env python3
"""Certify a reviewed overlay module in an exported, isolated build view.

The view must contain canonical src/, ledger/, config/, gate and fidelity tools.
After any source/tool patch, regenerate the view and graph and reissue proofs.
No historical l4_modules event is authority. Unsupported modules fail closed.
"""
import argparse,json,os,shutil,sys,time
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
sys.path[:0]=[str(ROOT/'tools'),str(ROOT/'tools/gate')]
from overlay_module_gate import build,command,CONTAINERS,affected_windows,fingerprint,load_modules,sha
from overlay_module_evidence import certificate_reason

def certify(key,root,reviewer):
 root=Path(root).absolute();authority=(root/'ledger').resolve().parent;m=next(m for m in load_modules(root) if m['key']==key)
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
 r,_=build(m,out/'module',root);windows=[]
 for wn in affected_windows(m,root):
  cfg=yaml.safe_load((root/wn).read_text());name=cfg['name'];sb=cfg['standalone_build'];win=out/'windows'/name;win.mkdir(parents=True,exist_ok=True)
  env=dict(os.environ,TMPDIR=str(root/'work'),PYTHONDONTWRITEBYTECODE='1')
  command([sys.executable,root/'tools/overlay_local_gate.py','--config',wn,'--clean'],root,env,win/'gate.log',timeout=1800)  # a whole window gate (town_scene ~282 s idle); the 300 s default guards single tools
  bd=root/sb['work_dir']/name/'build';blob=bd/(name+'.window.bin');fs=sb['window']['file_start'];fe=sb['window']['file_end']
  with (root/'work/disc/containers'/CONTAINERS[m['container']]).open('rb') as f:f.seek(fs);ret=f.read(fe-fs)
  if blob.read_bytes()!=ret:raise ValueError('affected window mismatch')
  # Snapshot artifacts out of the gate's --clean area, making the certificate durable.
  shutil.copy2(blob,win/'window.bin');shutil.copy2(bd.parent/(name+'_manifest.json'),win/'manifest.json')
  records=json.loads((bd/'modules.json').read_text());pr=next(x for x in records if x['module']==key)
  (win/'projection.json').write_text(json.dumps(pr,indent=2)+'\n')
  shutil.copytree(bd/'modules'/key,win/'module',dirs_exist_ok=True)
  windows.append({'config':wn,'result':'MATCH','file_start':fs,'file_end':fe,'proof_dir':str(win.relative_to(authority)),'artifacts':{n:sha(win/n) for n in ['gate.log','window.bin','manifest.json','projection.json','module/receipt.json']}})
 if before!=fingerprint(m,root):raise ValueError('inputs changed during full certification')
 cert={'schema':r['schema'],'kind':'overlay_module_placement','module':key,'members':r['members'],'at':time.strftime('%Y-%m-%dT%H:%M:%SZ',time.gmtime()),'reviewer':reviewer,'fingerprint':before,'proof_dir':str((out/'module').relative_to(authority)),'receipt_sha256':sha(out/'module/receipt.json'),'windows':windows}
 reason=certificate_reason(m,cert,authority)
 if reason:raise ValueError(reason)
 p=root/'ledger/modules'/('overlay_'+key+'.json');p.parent.mkdir(parents=True,exist_ok=True);tmp=p.with_suffix('.tmp');tmp.write_text(json.dumps(cert,indent=2)+'\n');tmp.replace(p)
 return cert,p

def main():
 ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('module');ap.add_argument('--root',required=True,type=Path);ap.add_argument('--reviewer',required=True);args=ap.parse_args();c,p=certify(args.module,args.root,args.reviewer);print(json.dumps({'module':c['module'],'members':c['members'],'certificate':str(p),'windows':[w['config'] for w in c['windows']],'result':'CERTIFIED'},indent=2))
if __name__=='__main__':main()
