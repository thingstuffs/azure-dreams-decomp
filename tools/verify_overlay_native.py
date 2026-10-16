"""Fallback proof for overlay members whose production unit is a complete module.

An isolated member may lack wrapper declarations or have a different inlining
context. Only the registered, reviewed complete TU can establish its bytes.
"""
import hashlib,threading,tempfile
from pathlib import Path
from gate import overlay_module_gate as G
_LOCKS={};_CACHE={};_LOCK=threading.Lock()

def verify_member(row,cfile,root,view,include_root=None):
 root=Path(root).resolve();view=Path(view).resolve();cfile=Path(cfile).resolve()
 if row.get('kind')!='overlay' or row.get('row_kind')=='data':return None
 if cfile==(root/'raw'/row['container']/Path(row['c_path']).name).resolve():return None
 if include_root is not None and Path(include_root).resolve()!=root/'include':return None
 modules=[m for m in G.load_modules(view) if any(a['id']==row['id'] for a in m['members'])]
 if not modules:return None
 if len(modules)!=1:raise ValueError('ambiguous native owner: '+row['id'])
 m=modules[0];member=next(a for a in m['members'] if a['id']==row['id'])
 with _LOCK:lock=_LOCKS.setdefault(m['key'],threading.Lock())
 with lock:
  before=G.fingerprint(m,view);candidate=hashlib.sha256(cfile.read_bytes()).hexdigest()
  substitutions=None if cfile==(view/member['source']).resolve() else {member['source']:str(cfile)}
  key=(str(view),m['key'],before['sha256'],(member['source'],candidate) if substitutions else None)
  if key not in _CACHE:
   with tempfile.TemporaryDirectory(prefix='overlay_native_verify_') as td:
    receipt,binary=G.build(m,Path(td),view,substitutions)
    if receipt.get('gate',{}).get('result')!='MATCH' or receipt.get('genuine',{}).get('result')!='MATCH' or row['id'] not in receipt.get('members',[]):raise ValueError('incomplete native member proof')
    if substitutions and receipt.get('candidates',{}).get(member['source'])!=candidate:raise ValueError('candidate is not bound by native proof')
    _CACHE[key]=dict(receipt=receipt,sha256=hashlib.sha256(Path(binary).read_bytes()).hexdigest())
  proof=_CACHE[key]
  if G.fingerprint(m,view)!=before or hashlib.sha256(cfile.read_bytes()).hexdigest()!=candidate:raise ValueError('native member inputs changed')
  return {'status':'ok','exact':True,'proof':'complete overlay TU: retail + genuine ASPSX 2.79','module':m['key'],'module_fingerprint':before['sha256'],'module_bytes_sha256':proof['sha256']}
