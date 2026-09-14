"""T61: erase a keep by reconstructing existing C work, joins and value roles.

Current-text only; no evidence/row lookup, flags or cell changes. Uses temporary
compiler assembly solely to rank; the supplied vf is the only score/acceptance.
The caller confines TMPDIR. No asm, volatile, fake dependency or one-trip shape.
"""
import collections
import os
from pathlib import Path
import sys

ROOT=next(p for p in Path(__file__).resolve().parents if (p/'tools/common.py').is_file())
sys.path.insert(0,str(ROOT/'tools'))
from common import sha_text
from pin_census import sites_of
from xform.sched_trace import compile_text, distance
try:                    # tools/xform/, where sweep.py imports it as xform.t61_naturalkeep
    from xform.keep_shapes import (admissible, erase_sites, var_of, local_shapes,
                                   natural_shapes, order_shapes)
except ModuleNotFoundError:   # the lane directory, where lane_eval.py puts the module's own dir on sys.path
    from keep_shapes import (admissible, erase_sites, var_of, local_shapes,
                             natural_shapes, order_shapes)

COMPILERS=int(os.getenv('T61_COMPILERS','384'))
VERIFIES=int(os.getenv('T61_VERIFY','8'))


def roundrobin(gens):
    pending=[iter(g) for g in gens]
    while pending:
        rest=[]
        for g in pending:
            try:
                yield next(g);rest.append(g)
            except StopIteration: pass
        pending=rest


def candidate_stream(text, base, site):
    pos=min(site[3],len(base));v=var_of(site);line=site[5]-1
    return roundrobin((local_shapes(base,pos,v),natural_shapes(base),order_shapes(base,line,v)))


class T:
    name='t61_naturalkeep';level=1;needs_verify=True

    @staticmethod
    def eligible(text,row,census):
        if not row.get('cfg'):return 'missing compiler recipe'
        if not any(s[1].startswith('ASM_KEEP') for s in sites_of(text)):return 'no keeps'
        return None

    @staticmethod
    def apply_verified(text,row,census,vf):
        pins=sites_of(text);keeps=[s for s in pins if s[1].startswith('ASM_KEEP')]
        info=dict(compiles=0,tried=0,compile_failures=0,generated={},screened={},failed_families={},sites=[],steps=[])
        seen={sha_text(text)};observed={};ranked=[]
        def observe(t):
            h=sha_text(t)
            if h not in observed:
                if info['compiles']>=COMPILERS:return None
                ob=compile_text(row,t);info['compiles']+=1
                if ob['error']:info['compile_failures']+=1
                observed[h]=ob['assembly']
            return observed[h]
        baseline=observe(text)
        if baseline is None:return None,dict(info,error='baseline compiler observation failed')
        def attempt(tag,t):
            family=tag.split(':')[0]
            info['generated'][family]=info['generated'].get(family,0)+1
            h=sha_text(t)
            if h in seen or not admissible(text,t) or len(sites_of(t))>=len(pins):return None
            seen.add(h)
            asm=observe(t)
            if asm is None:
                info['failed_families'][family]=info['failed_families'].get(family,0)+1
                return None
            info['screened'][family]=info['screened'].get(family,0)+1
            d=distance(baseline,asm)
            ranked.append((d,tag,t))
            if d==0 and info['tried']<VERIFIES:
                score=vf(t);info['tried']+=1
                if score.get('exact'):
                    info['steps']=[dict(tag=tag,assembly_distance=d,score=score)]
                    return t
            return None
        # All one-site erasures, then same-variable groups. Keep unrelated pins.
        bases=[];groups=collections.defaultdict(list)
        for s in keeps:
            if info['compiles']>=min(48,COMPILERS//4):break
            base=erase_sites(text,[s]);hit=attempt('erase:'+str(s[5]),base)
            if hit is not None:return hit,info
            asm=observed.get(sha_text(base))
            if asm is not None:
                d=distance(baseline,asm);bases.append((d,s,base))
                info['sites'].append(dict(line=s[5],macro=s[1],var=var_of(s),asm=d))
            groups[var_of(s)].append(s)
        for v,ss in groups.items():
            if len(ss)<2:continue
            b=erase_sites(text,ss);hit=attempt('erase-group:'+str(v),b)
            if hit is not None:return hit,info
            if observed.get(sha_text(b)) is not None:bases.append((distance(baseline,observed[sha_text(b)]),ss[0],b))
        bases.sort(key=lambda x:x[0])
        # The nearest four seeds get separate per-family streams. A small
        # improving second step can combine a branch/producer change with order.
        seeds=bases[:4]
        def stream(s,b):
            for tag,t in candidate_stream(text,b,s):yield tag,t,s
        first=list(stream(s,b) for _,s,b in seeds)
        until=min(COMPILERS-40,int(COMPILERS*.78))
        for tag,t,s in roundrobin(first):
            if info['compiles']>=until:break
            hit=attempt(tag,t)
            if hit is not None:return hit,info
        if seeds:
            best=sorted(ranked,key=lambda x:x[0])
            refined=[x for x in best if x[0]<seeds[0][0] and not x[1].startswith('erase')][:2]
            for d,prior,b in refined:
                s=seeds[0][1]
                for tag,t in candidate_stream(text,b,s):
                    if info['compiles']>=COMPILERS:break
                    hit=attempt(prior+' / '+tag,t)
                    if hit is not None:return hit,info
        # Assembly normalization is a heuristic. Spend the remaining verifier
        # allowance on distinct near candidates, including nonzero distances.
        for d,tag,t in sorted(ranked,key=lambda x:x[0]):
            if info['tried']>=VERIFIES:break
            if d==0:continue
            score=vf(t);info['tried']+=1
            if score.get('exact'):
                info['steps']=[dict(tag=tag,assembly_distance=d,score=score)]
                return t,info
        info['best']=[dict(asm=d,tag=tag) for d,tag,_ in sorted(ranked,key=lambda x:x[0])[:8]]
        return None,info
