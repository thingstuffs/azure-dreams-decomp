"""Verify an immutable batch, measuring each native complete TU only once."""
from pathlib import Path
import concurrent.futures,hashlib,json,os,tempfile,time
from common import ROOT,clean_path

def context(root=ROOT):
 root=Path(root);paths=set()
 for group in ['src','include','config']:
  paths.update(p for p in (root/group).rglob('*') if p.is_file() and p.suffix in {'.c','.h','.tsv','.yaml','.txt','.json','.jsonl','.py','.sh'})
 for name in ['ledger/rows.jsonl','ledger/cache/slus_obj.json','ledger/splits/overlay_modules.build.json','ledger/splits/slus.build.ninja','tools/verify.py','tools/verify_overlay_native.py','tools/build/ccproc.py','tools/gate/match.py','tools/gate/cc.sh','tools/gate/overlay_module_gate.py','tools/gate/overlay_scoped_fingerprint.py','tools/maspsx/maspsx.py']:
  p=root/name
  if p.is_file():paths.add(p)
 paths.update(p for p in (root/'work/disc/containers').glob('*.BIN') if p.is_file())
 hashes={str(p.relative_to(root)):hashlib.sha256(p.read_bytes()).hexdigest() for p in sorted(paths)}
 return hashlib.sha256(json.dumps(hashes,sort_keys=True).encode()).hexdigest()

def measure(rs,workers,verify,root=ROOT):
 """Each yielded (id, result) is covered by an ordinary row or a complete-TU proof."""
 from gate import overlay_module_gate as G
 from verify import gate_root
 root=Path(root);by_id={r['id']:r for r in rs};modules=G.load_modules(gate_root(False)) if (root/'config/overlays/modules.json').is_file() else [];owners={a['id']:m for m in modules for a in m['members']}
 jobs=[];groups={}
 for row in rs:
  if row['id'] in owners and row.get('kind')=='overlay' and row.get('row_kind')!='data':groups.setdefault(owners[row['id']]['key'],[]).append(row)
  else:jobs.append(('row',[row],None))
 jobs.extend(('module',rows,owners[rows[0]['id']]) for rows in groups.values())
 def one(job):
  kind,rows,module=job
  if kind=='row':
   row=rows[0];return [(row['id'],verify(row,root/'src'/row['container']/Path(row['c_path']).name,include_root=root/'include'))]
  return native_job(module,rows,gate_root(False))
 # CPU-heavy native fingerprint validation uses separate interpreters; no
 # validation is memoized or skipped. Ordinary row compilers remain threaded.
 import contextlib,multiprocessing
 with contextlib.ExitStack() as stack:
  ordinary=stack.enter_context(concurrent.futures.ThreadPoolExecutor(max_workers=workers))
  native=ordinary
  if root.resolve()==ROOT.resolve() and groups:
   native=stack.enter_context(concurrent.futures.ProcessPoolExecutor(max_workers=min(4,workers),mp_context=multiprocessing.get_context('spawn')))
  futures=[]
  for j in jobs:
   if j[0]=='module' and native is not ordinary:futures.append(native.submit(native_job,j[2],j[1],gate_root(False)))
   else:futures.append(ordinary.submit(one,j))
  for f in concurrent.futures.as_completed(futures):yield from f.result()

def native_job(module,rows,view):
 from gate import overlay_module_gate as G
 t0=time.time()
 try:
  with tempfile.TemporaryDirectory(prefix='batch_native_') as td:
   try:receipt,blob=G.build(module,Path(td),Path(view))
   except (OSError,ValueError,RuntimeError) as exc:
    diagnostic=Path(td)/'compile.log'
    detail=diagnostic.read_text(errors='replace')[-2400:] if diagnostic.exists() else ''
    raise ValueError(str(exc)+' '+detail) from exc
   if receipt['gate']['result']!='MATCH' or receipt['genuine']['result']!='MATCH':raise ValueError('incomplete complete-TU proof')
   digest=hashlib.sha256(Path(blob).read_bytes()).hexdigest()
   measured=set(receipt['members'])
   if any(row['id'] not in measured for row in rows):raise ValueError('row omitted by complete-TU proof')
   result=dict(status='ok',exact=True,proof='complete overlay TU: retail + genuine ASPSX 2.79',module=module['key'],module_fingerprint=receipt['fingerprint']['sha256'],module_bytes_sha256=digest,secs=round(time.time()-t0,2))
  return [(row['id'],dict(result)) for row in rows]
 except (OSError,ValueError,RuntimeError) as exc:return [(r['id'],dict(status='failed',exact=False,err='complete TU: '+str(exc)[-800:])) for r in rows]
