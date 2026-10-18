#!/usr/bin/env python3
"""Validate complete masked twins whose GCC prelude precedes the prologue."""
import collections
import census as C

def detect(W,segs,H):
 out={0:[],1:[]};hits=[]
 for g in segs:
  s,t,frame,abi=g[:4]
  if frame!='framed' or not abi:continue
  for n in (1,2,3):
   a=s-n
   if a<0 or t-a<C.K:continue
   pre=W[a:s]
   if any(not C.valid(w) or C.is_branch(w) or set(C.regs_any(w)) & {26,27,29} or w>>26==16 or any(r not in {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,24,25} for r in C.regs_written(w)) for w in pre):continue
   h=C.whole_hash(W,a,t);folds=[f for f in (0,1) if h in H[f]]
   if not folds:continue
   for f in folds:out[f].append([a*4,s*4])
   hits.append([a*4,s*4,t*4,folds])
 return {f:C.merge(v) for f,v in out.items()},hits

def validate(L,B,rowmeta,prefix):
 folds=C.fold_ivs(rowmeta);tot=collections.Counter();per={}
 for c in C.CONTS:
  lc,bc=L[c],B[c];typed=C.merge([x for k in C.LEDGER_TYPED for x in lc.get(k,[])]);p=C.subtract(lc.get('c_row',[]),typed);ins=C.subtract(C.merge(lc.get('instance_proven',[])+lc.get('instance_partial',[])),typed+p);code=C.merge(p+ins)
  fmt=C.merge([x for k in C.FMT for x in bc['fmt'][k]]);ns=C.subtract(C.merge(typed+fmt),code);ne=C.subtract(bc['fmt']['entropy'],code+ns);f0,f1=folds.get(c,([],[]));f0=C.inter(f0,p);f1=C.inter(f1,p);fl=C.subtract(p,f0+f1);a,b=prefix[c][0],prefix[c][1];u=C.merge(a+b)
  d=dict(tp=C.size(C.inter(f0,b))+C.size(C.inter(f1,a))+C.size(C.inter(fl,u)),fp_struct=C.size(C.inter(ns,u)),fp_entropy=C.size(C.inter(ne,u)),ins=C.size(C.inter(ins,u)),candidate_bytes=C.size(u));per[c]=d;tot.update(d)
 den=tot['tp']+tot['fp_struct']+tot['fp_entropy'];return dict(schema='azure-clean.masked-prefix-validation.v1',rule='Complete masked C body >=48B; 4/8/12B caller-register-only prelude, no SP/branch/call/COP0; valid framed ABI suffix. Fold-crossed TP; union negatives. This is label-3 code evidence; differing non-relocation fields still prohibit C transfer.',minimum_precision=C.ADMIT_PRECISION,totals=dict(tot),per_container=per,precision=tot['tp']/den if den else None,admitted=bool(den and tot['tp']/den>=C.ADMIT_PRECISION))

