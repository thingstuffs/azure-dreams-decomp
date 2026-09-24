#!/usr/bin/env python3
"""Port candidates (round 77): pinned rows whose text is a NEAR clone (skeleton ratio >= 0.8) of a row some lane
already de-pinned, i.e. the rows a model PORT lane should get, with the exemplar lane named.

    python3 tools/lanes/port_candidates.py OUT.json      # prints (pins, row, exemplar, lane, pins removed, ratio, jaccard)

Why: clone_transfer.py / clone_wholeport.py port mechanically and refuse anything structurally different. Round 77's
Opus port lanes (r77_opus_p0a/p0b: the family-0 representative's solution given as base/out/REPORT paths in a
--question file) took 6 of 6 structurally-different siblings 59 -> 0 pins in ~6 minutes and ~150k tokens a lane,
against ~400k and ~45 minutes for a from-scratch lane.  Build a port lane: build_class_pack.py --rows ... then
kit_pack.py --question <file listing each row's exemplar base/out/REPORT paths>.
Skeleton = clone_wholeport.skel (identifiers -> I, numbers -> N); 6-gram Jaccard >= 0.5 prefilter, then difflib.
Rows already in an r77_* lane (base/ or out/) are excluded; edit USED_GLOB for later rounds.
"""
import sys, glob, json, difflib
from pathlib import Path
sys.path.insert(0,'tools/lanes'); sys.path.insert(0,'tools')
from clone_wholeport import toks, skel
USED_GLOB = 'work/native_lane/r77_*/*/*/*.c'
from common import rows, clean_path
from pin_census import sites_of
cur={}
for r in rows():
    p=clean_path(r)
    if r['container']=='ovmovie' or not p.exists(): continue
    t=p.read_text(errors='replace'); n=len(sites_of(t))
    if n: cur[r['id']]=(n, skel(toks(t)))
def sh(s,k=6): return {s[i:i+k] for i in range(len(s)-k+1)}
curs={k:sh(v[1]) for k,v in cur.items()}
ex={}
for o in glob.glob('work/native_lane/*/out/*/*.c'):
    o=Path(o); b=o.parents[2]/'base'/o.parent.name/o.name
    if not b.exists(): continue
    bt,ot=b.read_text(errors='replace'),o.read_text(errors='replace')
    d=len(sites_of(bt))-len(sites_of(ot))
    if d<=0: continue
    rid=o.parent.name+'/'+o.stem
    if rid not in ex or ex[rid][0]<d: ex[rid]=(d,o.parents[2].name,skel(toks(bt)))
used=set(f.split('/')[-2]+'/'+f.split('/')[-1][:-2] for f in glob.glob(USED_GLOB))
out=[]
for rid,(d,lane,s) in ex.items():
    es=sh(s)
    for sid,(n,ss) in cur.items():
        if sid==rid or sid in used: continue
        a=curs[sid]; j=len(es&a)/max(1,len(es|a))
        if j<0.5: continue
        r=difflib.SequenceMatcher(None,s,ss,autojunk=False).ratio()
        if r>=0.8: out.append((n,sid,rid,lane,d,round(r,3),round(j,2)))
best={}
for x in sorted(out,key=lambda x:(-x[5])):
    best.setdefault(x[1],x)
res=sorted(best.values(),key=lambda x:-x[0])
print(len(res),'pinned rows with a solved near-clone, pins',sum(x[0] for x in res))
for x in res: print(x)
json.dump(res,open(sys.argv[1],'w'))
