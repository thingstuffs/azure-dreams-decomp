"""Fresh complete overlay-module certificates, never unchecked sweep events."""
import hashlib,json,sys,subprocess
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'tools/gate'))
from overlay_module_gate import SCHEMA,CONTAINERS,affected_windows,fingerprint,graph,load_modules,local,sha,closure,payload_spec

def proof_path(root,name):
 p=local(root,name)
 if not p.resolve().is_relative_to(root.resolve()):raise ValueError('proof path escapes root')
 return p

def receipt_reason(m,r,root,proof_dir):
 ids=[a['id'] for a in m['members']];funcs=[a['function'] for a in m['members']];n=sum(a['size'] for a in m['members']);first=m['members'][0]
 if r.get('schema')!=SCHEMA or r.get('module')!=m['key'] or r.get('members')!=ids or r.get('candidates')!={}:return 'not canonical complete TU'
 ph=r.get('physical',{});payload=ph.get('payload',[])
 if (ph.get('compile_edges')!=1 or ph.get('functions')!=funcs or ph.get('owned_data')!=m['owned_data'] or ph.get('imports')!=m['imports']
  or [(s['name'],s['size']) for s in payload]!=payload_spec(m)):return 'incomplete function/data accounting'
 gate=r.get('gate',{});ge=r.get('genuine',{})
 if any(gate.get(k)!=v for k,v in {'result':'MATCH','bytes':n,'foff':first['foff'],'vma':first['vma'],'masked':0,'raw_substitution_bytes':0}.items()):return 'incomplete retail module proof'
 if any(ge.get(k)!=v for k,v in {'result':'MATCH','version':'2.79','whole_tu':True,'bytes':n,'masked':0}.items()):return 'incomplete genuine proof'
 expected={'module.s','sectioned.s','module.o','module.ld','module.elf','module.bin','retail.bin','IN.S','OUT.OBJ','genuine.bin'}
 if set(r.get('artifacts',{}))!=expected:return 'missing module artifacts'
 for name,h in r['artifacts'].items():
  if sha(proof_path(root,str(Path(proof_dir)/name)))!=h:return 'module artifact changed: '+name
 with (root/'work/disc/containers'/CONTAINERS[m['container']]).open('rb') as f:f.seek(first['foff']);ret=f.read(n)
 digest=hashlib.sha256(ret).hexdigest()
 if len(ret)!=n or gate.get('rebuilt_sha256')!=digest or gate.get('retail_sha256')!=digest or ge.get('sha256')!=digest:return 'resolved module proof differs from retail'
 for name in ['module.bin','retail.bin','genuine.bin']:
  if r['artifacts'][name]!=digest:return 'binary artifact differs from retail'
 return None

def certificate_reason(m,cert,root=ROOT):
 root=Path(root).absolute()
 if any(m['review'].get(k)!='reviewed' for k in ['membership','types','ownership']) or not m['review'].get('reviewer'):return 'membership/type/ownership review incomplete'
 if cert.get('schema')!=SCHEMA or cert.get('kind')!='overlay_module_placement' or cert.get('module')!=m['key'] or cert.get('members')!=[a['id'] for a in m['members']]:return 'wrong certificate identity'
 if json.loads((root/'ledger/splits/overlay_modules.build.json').read_text())!=graph(root):return 'physical graph differs from registry/cohorts'
 current=fingerprint(m,root)
 if cert.get('fingerprint')!=current:return 'source/recipe/graph/tool/review/window inputs changed'
 if not cert.get('reviewer') or cert.get('reviewer')!=m['review']['reviewer']:return 'reviewer differs'
 p=proof_path(root,cert['proof_dir'])
 r=json.loads((p/'receipt.json').read_text())
 if sha(p/'receipt.json')!=cert['receipt_sha256'] or r.get('fingerprint')!=current:return 'module receipt changed or stale'
 reason=receipt_reason(m,r,root,cert['proof_dir'])
 if reason:return reason
 expected=affected_windows(m,root);ws=cert.get('windows',[])
 if [w['config'] for w in ws]!=expected:return 'not every affected production window was gated'
 import yaml
 for w in ws:
  y=yaml.safe_load((root/w['config']).read_text());sb=y['standalone_build'];fs=sb['window']['file_start'];fe=sb['window']['file_end'];wp=proof_path(root,w['proof_dir'])
  if w.get('result')!='MATCH' or w.get('file_start')!=fs or w.get('file_end')!=fe:return 'window scope differs'
  if set(w['artifacts'])!={'gate.log','window.bin','manifest.json','projection.json','module/receipt.json'}:return 'incomplete window artifact inventory'
  for name,h in w['artifacts'].items():
   if sha(proof_path(root,str(Path(w['proof_dir'])/name)))!=h:return 'window artifact changed'
  data=(wp/'window.bin').read_bytes()
  with (root/'work/disc/containers'/CONTAINERS[m['container']]).open('rb') as f:f.seek(fs);ret=f.read(fe-fs)
  if data!=ret or len(data)!=fe-fs:return 'window does not equal retail'
  projection=json.loads((wp/'projection.json').read_text());manifest=json.loads((wp/'manifest.json').read_text())
  selected=[a for a in m['members'] if fs<a['foff']+a['size'] and a['foff']<fe]
  if projection.get('projected_rows')!=[a['id'] for a in selected] or projection.get('fingerprint')!=current['sha256']:return 'window module projection incomplete or stale'
  wr=json.loads((wp/'module/receipt.json').read_text())
  if wr.get('fingerprint')!=current:return 'window module build stale'
  reason=receipt_reason(m,wr,root,str(Path(w['proof_dir'])/'module'))
  if reason:return reason
  segs=[s for s in manifest['c_segments'] if s.get('module')==m['key']]
  if [(int(s['file_start'],0),s['size']) for s in segs]!=[(a['foff'],a['size']) for a in selected]:return 'window segment provenance incomplete'
 return None

def module_status(root=ROOT):
 root=Path(root).absolute()
 try:mods=load_modules(root)
 except (OSError,ValueError,KeyError,TypeError) as e:return [{'module':{'key':'manifest','members':[]},'valid':False,'reason':str(e)}]
 out=[]
 for m in mods:
  cert=None
  try:
   cert=json.loads((root/'ledger/modules'/('overlay_'+m['key']+'.json')).read_text());reason=certificate_reason(m,cert,root)
  except (OSError,ValueError,KeyError,TypeError,AttributeError,IndexError,subprocess.SubprocessError) as e:reason='certificate missing/invalid: '+str(e)
  out.append({'module':m,'certificate':cert,'valid':reason is None,'reason':reason})
 return out

def valid_placements(root=ROOT):
 return {a['id']:{'outcome':'applied','module':e['module']['key'],'module_fingerprint':e['certificate']['fingerprint']['sha256']} for e in module_status(root) if e['valid'] for a in e['module']['members']}


def source_contexts(root=ROOT):
 """Expose shared source to the existing preprocessor-free ladder scans.

 Generic common/m2c macro headers were already present before grouping. New
 module headers, glue and local includes must not hide pins or tail declarations.
 Sibling bodies retain their own logical row checks.
 """
 root=Path(root).absolute();out={}
 base=closure(root,['include/common.h','include/m2c_compat.h'])
 for m in load_modules(root):
  member_sources={a['source'] for a in m['members']}
  names=closure(root,[m['source'],*m['headers']])-base-member_sources
  context='\n'.join((root/name).read_text() for name in sorted(names))
  for a in m['members']:out[a['id']]=context
 return out
