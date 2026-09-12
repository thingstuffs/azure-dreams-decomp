#!/usr/bin/env python3
"""Measure screen recall on historical source pairs; independently verify every apparent miss."""
import collections
import json
import subprocess
import sys
import tempfile
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]))
from common import ROOT, rows
from xform.screen import compile_s,sdiff
from verify import verify

def main():
    lookup={str(Path('src')/r['container']/Path(r['c_path']).name):r for r in rows()}
    output=ROOT/'work/pin_recovery_20260912/screen_replay.json'
    pairs=[];misses=[];errors=[];by_cfg=collections.Counter()
    for commit in ['0ac280d6','ed54bf04','2d6b680e']:
        paths=subprocess.check_output(['git','diff-tree','--no-commit-id','--name-only','-r',commit,'--','src'],cwd=ROOT,text=True).splitlines()
        for path in paths:
            if path not in lookup: continue
            row=lookup[path]
            before=subprocess.check_output(['git','show',commit+'^:'+path],cwd=ROOT,text=True)
            after=subprocess.check_output(['git','show',commit+':'+path],cwd=ROOT,text=True)
            a,b=compile_s(row,before),compile_s(row,after);distance=sdiff(a,b)
            rec=dict(commit=commit,id=row['id'],cfg=row['cfg'],distance=distance)
            if distance is None:errors.append(rec)
            elif distance:
                with tempfile.TemporaryDirectory() as tmp:
                    p=Path(tmp)/Path(path).name
                    p.write_text(before); v0=verify(row,p,include_root=ROOT/'include')
                    p.write_text(after); v1=verify(row,p,include_root=ROOT/'include')
                rec['before_exact']=v0.get('exact');rec['after_exact']=v1.get('exact')
                rec['before_assembly']=a;rec['after_assembly']=b
                misses.append(rec)
            pairs.append({k:v for k,v in rec.items() if k not in ('before_assembly','after_assembly')});by_cfg[row['cfg']]+=1
    result=dict(pairs=len(pairs),by_cfg=dict(by_cfg),errors=errors,misses=misses,records=pairs)
    output.write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps({k:v for k,v in result.items() if k not in ('records','misses')},indent=2))
    print('misses',[(r['id'],r['distance'],r.get('before_exact'),r.get('after_exact')) for r in misses])

if __name__=='__main__':main()
