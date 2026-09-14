"""T60: allocator-comment-guided search over natural C lifetimes and expressions.

Current text only, caller vf is the only score. No external row lookup. Temporary
compiler files are deleted. Default <=384 observations / <=8 vf calls. Exact
assembly is screened first. A beam retains candidates improving allocated operand
agreement or the observed peer input projection, as well as assembly distance.
Local quantity internals are explicitly unavailable in stock dumps.

Same-type disjoint local reuse extends HOST coverage; it is not a new allocator
mechanism. Established T51/natural menus provide complementary splits and moves.
"""
import collections
import itertools
import os
import re
from pathlib import Path
import sys

try:
    from .alloc_inputs import observe,diagnose,comparison,ROOT,hard_number
except ImportError:
    from alloc_inputs import observe,diagnose,comparison,ROOT,hard_number
sys.path.insert(0,str(ROOT/'tools'))
from common import sha_text
from pin_census import sites_of,unscored_text,asm_blocker
from pin_sites import erase_many
from xform import t51_sched_order as S
from xform import natural as N
from xform.t53_reg_state import extra_candidates,page_candidates
from xform import t42_sinkcopy as K


def reuse_candidates(text,focus=None):
    """Reuse exact-type locals in two disjoint, straight-line real lifetimes.

    Each lifetime starts with unconditional overwrite. Both variables have one
    declaration and all references inside the same compound block; reject address
    escape, macros, labels, directives and shadowing. No stores or uses are added.
    Both naming directions matter because expansion numbers follow declarations.
    """
    masked=S.mask(text);decl=S.declarations(masked);usable={}
    scopes={};stack=[]
    for i,c in enumerate(masked):
        if c=='{':stack.append(i)
        elif c=='}' and stack:scopes[stack.pop()]=i
    for v,d in decl.items():
        ds=masked[d['start']:d['end']]
        if any(x in ds for x in ('ASM_','volatile','const','=')):continue
        if not re.fullmatch(r'(?:s|u)(?:8|16|32)|(?:unsigned |signed )?(?:int|short|char|long)|[A-Za-z_]\w*\s*\*',d['type']):continue
        scope=next(((a,b) for a,b in sorted(scopes.items(),reverse=True) if a<d['start']<b),None)
        if scope is None:continue
        hits=list(re.finditer(r'\b'+re.escape(v)+r'\b',masked))
        uses=[m for m in hits if not d['start']<=m.start()<d['end']]
        if not uses or any(not scope[0]<m.start()<scope[1] for m in uses):continue
        if any(masked[max(0,m.start()-2):m.start()].endswith(('.', '->')) for m in uses):continue
        if re.search(r'&\s*\b'+re.escape(v)+r'\b',masked):continue
        if any('ASM_' in masked[masked.rfind('\n',0,m.start())+1:masked.find('\n',m.end())] for m in uses):continue
        a,b=uses[0].start(),uses[-1].end()
        line=masked[masked.rfind('\n',0,a)+1:masked.find(';',a)+1]
        assign=S.ASSIGN.match(line)
        if not assign or assign['lhs'].strip()!=v or re.search(r'\b'+re.escape(v)+r'\b',assign['rhs']):continue
        region=masked[a:b]
        if re.search(r'[{}#:]|\b(?:if|else|for|while|switch|goto|case|return|break|continue)\b',region):continue
        # Declarations must belong to this exact block, and no duplicate declaration.
        if len([m for m in hits if m.start()<a])!=1:continue
        usable[v]=(d,scope,uses,a,b)
    pairs=[]
    for v,u in itertools.combinations(usable,2):
        d,sp,uses,a,b=usable[v];e,sq,uuses,c,f=usable[u]
        if sp!=sq or re.sub(r'\s+','',d['type'])!=re.sub(r'\s+','',e['type']):continue
        if not (b<c or f<a):continue
        region=masked[min(a,c):max(b,f)]
        if re.search(r'[{}#:]|\b(?:if|else|for|while|switch|goto|case|return|break|continue)\b',region):continue
        pairs.append((0 if focus in (u,v) else 1,abs(a-c),v,u))
    for _,_,v,u in sorted(pairs):
        for host,guest in ((v,u),(u,v)):
            d,_,uses,_,_=usable[guest]
            # A declaration on its own line goes whole, with any trailing comment: a note describing
            # a variable that no longer exists must not be left behind, nor a blank line in its place.
            le=masked.find('\n',d['end']);le=len(text) if le<0 else le+1
            drop=(d['start'],le,'') if not masked[d['end']:le].strip() else (d['start'],d['end'],'')
            edits=[drop]+[(m.start(),m.end(),host) for m in uses]
            cand=text
            for a,b,t in sorted(edits,reverse=True):cand=cand[:a]+t+cand[b:]
            yield 'reuse:%s>%s'%(guest,host),cand


def menu(text,line,var,only_reuse=False):
    groups=collections.defaultdict(list)
    for tag,c in reuse_candidates(text,var):groups['reuse'].append((tag,c))
    if not only_reuse:
        for tag,c in S.candidates(text,line,var):groups[tag.split(':')[0]].append((tag,c))
        for gen in N.ALLOC_LEVERS:
            for tag,c in gen(text):groups[tag.split(':')[0]].append((tag,c))
        for tag,c in extra_candidates(text,var):groups[tag.split(':')[0]].append((tag,c))
        for tag,c in page_candidates(text,var):groups['page-or'].append((tag,c))
        for tag,c in K.candidates(text):groups['sinkcopy'].append((tag,c))
    order=['reuse','single-set','hostwide','unhost','move','fuse','decl-swap','commute','width','page-or','sinkcopy']
    order += sorted(set(groups)-set(order))
    # Eight reuse trials get an early chance; then round-robin all families.
    yield from groups['reuse'][:8];groups['reuse']=groups['reuse'][8:]
    for batch in itertools.zip_longest(*(groups[k] for k in order)):
        for item in batch:
            if item:yield item


def allowed(original,candidate,signature,npins):
    if unscored_text(candidate)!=signature or len(sites_of(candidate))>=npins:return False
    # Do not add forbidden constructs, including via imported menus.
    for pat in (r'\bASM_\w+',r'\b__asm__\b',r'\bvolatile\b',r'\bdo\s*\{',r'\bwhile\s*\(\s*0\s*\)',r'\bfor\s*\([^;]*;\s*0\s*;',r'\bif\s*\(\s*1\s*\)',r'\(\s*\{'):
        if len(re.findall(pat,candidate))>len(re.findall(pat,original)):return False
    return True


class T:
    name='t60_alloc_inputs'
    level=1
    needs_verify=True
    @staticmethod
    def eligible(text,row,census):
        return 'no register pins' if not any(s[1]=='ASM_REG' for s in sites_of(text)) else asm_blocker(text) or (None if row.get('cfg') else 'missing cfg')
    @classmethod
    def apply_verified(cls,text,row,census,vf):
        budget=max(1,int(os.getenv('T60_COMPILERS','384')));vb=max(1,int(os.getenv('T60_VERIFY','8')))
        pins=sites_of(text);sig=unscored_text(text);log=dict(compiler_budget=budget,vf_budget=vb,compiles=0,tried=0,compile_failures=0,sites=[],candidates=[],steps=[])
        seen=set();records=[]
        def ob(c):
            if log['compiles']>=budget:return None
            log['compiles']+=1;a=observe(row,c)
            if a['error']:log['compile_failures']+=1;return None
            return a
        target=ob(text)
        if not target:return None,dict(log,error='target compile failed')
        def trial(c,site,tag,hard,depth=0):
            h=sha_text(c)
            if h in seen or not allowed(text,c,sig,len(pins)):return None,None
            seen.add(h);a=ob(c)
            if a is None:return None,None
            diag=diagnose(target,a,hard)
            r={k:diag[k] for k in ('asm','allocation_operand_distance','peer_input_distance','peer_compared','changes','bound')}
            r.update(site=site,tag=tag,depth=depth)
            if depth==0:
                cmp=comparison(target,a);r.update(cls=cmp['cls'],first=cmp['first'])
            records.append(r)
            if r['asm']==0 and log['tried']<vb:
                log['tried']+=1;s=vf(c);r['vf']={k:s.get(k) for k in ('exact','total','status')}
                if s.get('exact') is True:log['steps'].append('erase:%d/%s'%(site,tag));return c,r
            return False,r
        def finish(c):
            log['candidates_n']=len(records);log['candidates']=sorted([r for r in records if r['depth']],key=lambda r:(r['asm'],r['allocation_operand_distance'],r['tag']))[:16]
            log['pins_out']=len(sites_of(c)) if c else len(pins)
            return c,log
        bases=[]
        for i,s in [(i,s) for i,s in enumerate(pins) if s[1]=='ASM_REG'][:24]:
            c=erase_many(text,[s],clean_notes=True);hard=hard_number(s[2]);hit,r=trial(c,i,'erase',hard)
            if hit:return finish(hit)
            if r:
                log['sites'].append(r);bases.append(dict(text=c,site=i,hard=hard,line=s[5]-1,var=s[6].split()[-1].lstrip('*'),rec=r))
        bases.sort(key=lambda b:(b['rec']['asm'],b['site']))
        bases=bases[:8]
        for ix,b in enumerate(bases):
            allowance=(budget-log['compiles'])//(len(bases)-ix);limit=log['compiles']+allowance;beam=[]
            for tag,c in menu(b['text'],b['line'],b['var'],os.getenv('T60_REUSE_ONLY')=='1'):
                if log['compiles']>=limit-max(0,allowance//4):break
                hit,r=trial(c,b['site'],tag,b['hard'],1)
                if hit:return finish(hit)
                if r:beam.append((c,r))
            # Retain distinct diagnostic and assembly improvements, never require equality.
            seeds=[]
            for key in ('allocation_operand_distance','peer_input_distance','asm'):
                ordered=sorted(beam,key=lambda x:(x[1][key],x[1]['asm'],x[1]['tag']))
                if ordered and ordered[0][1][key]<b['rec'][key] and all(ordered[0][0]!=x[0] for x in seeds):seeds.append(ordered[0])
            for j,(seed,sr) in enumerate(seeds):
                end=log['compiles']+max(0,(limit-log['compiles'])//(len(seeds)-j))
                for tag,c in menu(seed,b['line'],b['var'],os.getenv('T60_REUSE_ONLY')=='1'):
                    if log['compiles']>=end:break
                    hit,r=trial(c,b['site'],sr['tag']+' / '+tag,b['hard'],2)
                    if hit:return finish(hit)
        return finish(None)
