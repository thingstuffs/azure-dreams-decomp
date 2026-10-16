"""Check immutable starting windows concurrently before more admissions.

Only intrinsic failures in an existing matched source or its fixed extent can
hold a caller. Other preflight failures remain eligible for the normal runner.
No source, split, rowbase, compiler recipe or gate is changed here.
"""
import concurrent.futures,hashlib,json,re,sys
from pathlib import Path
from twins import L,R,PY,command,save,jl
from run_sdk import targets
OUT=L/'evidence/preflight';OUT.mkdir(exist_ok=True)

def interface_guard():
    paths=sorted((R/'include').rglob('*.h'))+[R/p for p in ['config/names.tsv','tools/toolchain.lock.json','tools/common.py','tools/verify.py']]
    digest=hashlib.sha256()
    for path in paths:
        digest.update(str(path.relative_to(R)).encode());digest.update(path.read_bytes())
    return digest.hexdigest()

def main():
    import gzip
    rows=[json.loads(l) for l in gzip.open(L/'state/base_rows.json.gz','rt')]
    byid={r['id']:r for r in rows};_,banks,_=targets()
    extra=L/'evidence/planned_production_windows.json'
    if extra.exists():
        from common import window_map
        known={w[0]:dict(container=c,window=w[0]) for c,windows in window_map().items() for w in windows}
        for name in json.loads(extra.read_text())['windows']:
            banks.setdefault(name,known[name])
    guard=interface_guard()
    def check(name):
        path=OUT/(name+'.json')
        if path.exists():
            prior=json.loads(path.read_text())
            if prior.get('interface_guard')==guard and (not prior.get('source') or hashlib.sha256((R/prior['source']).read_bytes()).hexdigest()==prior['source_sha256']):return prior
        args=[PY,'tools/overlay_local_gate.py','--config','config/overlays/'+name,'--clean']
        p=command(args,cwd=R/'build_ovl',log=OUT/(name+'.log'),timeout=3600)
        good=p.returncode==0 and any(line.startswith('MATCH') for line in p.stdout.splitlines())
        text=p.stdout+'\n'+p.stderr;c=banks[name]['container']
        names=re.findall(r'\b(func_[0-9A-Fa-f]{8})\.c\b',text)
        row=byid.get(c+'/'+names[-1]) if names else None
        if not row:
            m=re.search(r'foff (0x[\da-fA-F]+)',text)
            hits=[r for r in rows if r['container']==c and m and r.get('foff')==int(m[1],0)]
            if len(hits)==1:row=hits[0]
        intrinsic=bool(row and (('undeclared' in text and 'first use' in text) or 'pre-linked bytes' in text))
        record=dict(window=name,ok=good,returncode=p.returncode,stdout=p.stdout[-1800:],stderr=p.stderr[-1800:],intrinsic_existing_failure=intrinsic,source=('src/'+row['id']+'.c') if row else None,source_sha256=hashlib.sha256((R/'src'/(row['id']+'.c')).read_bytes()).hexdigest() if row else None,interface_guard=guard)
        save(path,record)
        print('PREFLIGHT',name,'MATCH' if good else 'INTRINSIC EXISTING HOLD' if intrinsic else 'OTHER HOLD',flush=True)
        return record
    results=[]
    with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:
        for record in pool.map(check,sorted(banks)):
            results.append(record);save(OUT/'summary.json',dict(windows=results,complete=False))
    save(OUT/'summary.json',dict(windows=results,complete=True))
    print('PREFLIGHT COMPLETE',len(results),sum(r['ok'] for r in results),sum(r['intrinsic_existing_failure'] for r in results),flush=True)

if __name__=='__main__':main()
