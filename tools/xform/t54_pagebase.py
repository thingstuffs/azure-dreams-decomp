"""T54: preserve page-local identity while respelling its address producer.

Uses current text only. No new asm, volatile, globals containing values, flags,
fake dependencies, row lists, or oracle scores outside vf. A symbol denotes the
same absolute address under this project's D_ADDRESS link convention.
The external harness chooses TMPDIR; all tool writes are temporary.

Built by the page_astra lane (work/native_lane/page_astra/REPORT.md, 2026-09-13). A pinned integer page
(`base = (u8 *)0x800D0000; ASM_KEEP(base);`) hides a constant from gcc: without the keep, CSE's fold_rtx
folds page+offset into one constant address (FSF 2.7.2's find_best_addr validates the fold before any
address-cost comparison; 2.8.1 compares costs), and at CDK/2.8.x combine turns a page plus a positive
disjoint offset into an IOR, which MIPS rejects as an address, so a signed load stays lhu/sll/sra.
The repair keeps the local and rewrites only its DEFINITION as the page symbol
(`DungeonPage *level_page = (DungeonPage *)D_80080000;`), erasing one pin or the group of keeps.
t29_addrsym deletes the whole variable and substitutes every use, which changes allocation.
Frozen held-out: H1 (t29 "no candidate exact" rows) 1/40, H2 (other page-base rows) 5/30; development
17/204 rows, 25 pins. Cell switches keep the row's flags and follow pin_cells_land.py rules 1-2
(info["cfg"]); under sweep.py --processes they are journaled "deferred" for a threaded rerun.
"""
import collections
import os
from pathlib import Path
import re
import sys
ROOT=next(p for p in Path(__file__).resolve().parents if (p/'tools/common.py').is_file())
sys.path.insert(0,str(ROOT/'tools'))
from common import parse_cfg, sha_text
from pin_census import sites_of, unscored_text, arm_labels
from pin_sites import erase_many, fn_bounds, params_of
from xform import t29_addrsym as A
from xform.sched_trace import compile_text, distance
from xform.t53_reg_state import page_candidates


def masked(text):
    t=A.mask_comments(text)
    return ''.join(re.sub(r'[^\n]',' ',line) if lab in ('port','dead') else line
                   for line,lab in zip(t.splitlines(True),arm_labels(text)))


def definitions(text):
    t=masked(text)
    rx=re.compile(r'\b(?P<v>[A-Za-z_]\w*)\s*(?:ASM_REG\([^)]*\)\s*)?=\s*(?P<rhs>'+A.LIT+r')\s*;')
    return [dict(var=m['v'],value=int(m['a'],16),start=m.start('rhs'),end=m.end('rhs'),pos=m.start()) for m in rx.finditer(t)]


def pagevars(text):
    ds=definitions(text)
    names={d['var'] for d in ds}
    return sorted(v for v in names if any(re.search(r'\b'+re.escape(v)+r'\b',text[s[3]:s[4]]) for s in sites_of(text)))


def add_externs(t,ext):
    lines=t.splitlines(True)
    at=max((i for i,l in enumerate(lines) if l.startswith('#include')),default=-1)+1
    lines[at:at]=[x for x in sorted(ext) if x.strip() not in t]
    return ''.join(lines)


def edits_apply(t,edits):
    for a,b,s in sorted(edits,reverse=True):t=t[:a]+s+t[b:]
    return t


def declaration_type(text,d):
    decl=A.decls_of(text,d['var'])
    types={(ty,ptr) for ty,ptr,span in decl}
    if len(types)==1:
        ty,ptr=next(iter(types));return ty+' '+('*'*ptr)
    if types:return None
    t=masked(text);bounds=fn_bounds(t,d['pos'])
    if bounds:
        param=params_of(t,bounds[0]).get(d['var'])
        if param:
            ty,ptr=param
            # params_of intentionally drops the struct/union keyword.
            if re.search(r'\b(?:struct|union)\s+'+re.escape(ty)+r'\s*\*+\s*'+re.escape(d['var']),t[:bounds[0]]):
                return None
            return ty+(' *' if ptr else '')
    return None


def anchors(text,d,v):
    """A few addresses from actual local uses and already named objects."""
    out=[d['value']]
    decl=A.decls_of(text,v)
    scale=1
    if decl and decl[0][1]:scale=A.ELEMSIZE.get(decl[0][0],1) if decl[0][1]==1 else 4
    tail=masked(text)[d['end']:]
    for m in re.finditer(r'\b'+re.escape(v)+r'\s*(?:(?P<op>[-+])=?\s*(?P<k>0x[\da-fA-F]+|\d+)\b|\[\s*(?P<ix>-?0x[\da-fA-F]+|-?\d+)\s*\])',tail):
        k=int(m['ix'],0) if m['ix'] else int(m['k'],0)*(-1 if m['op']=='-' else 1)
        value=(d['value']+scale*k)&0xffffffff
        if -32768<=value-d['value']<=32767 and value not in out:out.append(value)
        if len(out)>=5:break
    named=sorted({int(x,16) for x in re.findall(r'\bD_([\da-fA-F]{8})\b',text)})
    for value in named:
        if -32768<=value-d['value']<=32767 and value not in out:out.append(value)
        if len(out)>=7:break
    return out


def cursor_candidates(text,v):
    """Use the actual array start as the cursor, through one guarded initial bias.

    The bias must be outside any loop; every later use must be dominated by that
    bias in its block. This leaves real loop increments intact.
    """
    t=masked(text); ds=[d for d in definitions(text) if d['var']==v]
    decs=A.decls_of(text,v)
    if len(ds)!=1 or len(decs)!=1:return
    if re.search(r'\bgoto\b|^\s*[A-Za-z_]\w*\s*:',t,re.M):return
    ty,ptr,_=decs[0]
    if ptr!=1 or ty not in A.ELEMSIZE:return
    d=ds[0]; V=re.escape(v); tail=t[d['end']:]
    m=re.search(r'\b'+V+r'\s*(?P<op>[-+])=\s*(?P<n>-?\s*(?:0x[0-9A-Fa-f]+|\d+))\s*;',tail)
    if not m:return
    start=d['end']+m.start(); end=d['end']+m.end()
    prior=t[d['end']:start]
    if re.search(r'\b(for|while|do|goto)\b|\b'+V+r'\s*(?:=(?!=)|[-+*/&|^]=|\+\+|--)|&\s*\b'+V+r'\b',prior):return
    # Locate the enclosing block of the bias, and require no cursor use after it.
    stack=[]
    for i,c in enumerate(t[:start]):
        if c=='{':stack.append(i)
        elif c=='}' and stack:stack.pop()
    if not stack:return
    depth=1;close=None
    for i in range(start,len(t)):
        depth+=(t[i]=='{')-(t[i]=='}')
        if depth==0:close=i;break
    if close is None or re.search(r'\b'+V+r'\b',t[close+1:]):return
    if any(s[3]>d['end'] and s[3]<end and re.search(r'\b'+V+r'\b',text[s[3]:s[4]]) for s in sites_of(text)):return
    k=int(m['n'].replace(' ',''),0)*(-1 if m['op']=='-' else 1)
    if not k:return
    value=(d['value']+k*A.ELEMSIZE[ty])&0xffffffff
    for symbolic in (True,False):
        ext=set()
        seed=A.sym_expr(text,value,ty+' *',ext) if symbolic else '('+ty+' *)0x%08X'%value
        edits=[(d['start'],d['end'],seed),(start,end,'')]
        for use in re.finditer(r'\b'+V+r'\b',t[d['end']:start]):
            a=d['end']+use.start();b=d['end']+use.end()
            edits.append((a,b,'('+v+(' - '+str(k) if k>0 else ' + '+str(-k))+')'))
        yield 'cursor-'+('symbol' if symbolic else 'literal')+':'+v,add_externs(edits_apply(text,edits),ext)


def source_candidates(text):
    """Yield local symbol producers, site-local erasures, and expansion controls."""
    signature=unscored_text(text); seen={sha_text(text)}
    def unique(tag,t):
        h=sha_text(t)
        if h in seen or unscored_text(t)!=signature:return []
        seen.add(h)
        return [(tag,t)]
    for v in pagevars(text):
        pins=[s for s in sites_of(text) if re.search(r'\b'+re.escape(v)+r'\b',text[s[3]:s[4]])]
        keeps=[s for s in pins if s[1] in ('ASM_KEEP','ASM_KEEP_NV')]
        groups=[]
        if len(keeps)>1:groups.append(('keeps',keeps))
        groups += [('site%d'%s[3],[s]) for s in keeps]
        if len(pins)>len(keeps):groups.append(('pins',pins))
        for group,drop in groups:
            t=erase_many(text,drop,clean_notes=True)
            yield from unique('erase:%s:%s'%(v,group),t)
            for tag,new in cursor_candidates(t,v):
                yield from unique(tag+':'+group,new)
            ds=[d for d in definitions(t) if d['var']==v]
            if not ds:continue
            ty=declaration_type(t,ds[0])
            if ty is None:continue
            for mode in ('pointer','integer'):
                # Rewrite each producer alone, and all producers using one address style.
                for index in list(range(len(ds)))+([-1] if len(ds)>1 else []):
                    chosen=ds if index<0 else [ds[index]]
                    choices=[anchors(t,d,v) for d in chosen]
                    for rank in range(max(map(len,choices),default=0)):
                        edits=[];ext=set()
                        for d,aa in zip(chosen,choices):
                            anchor=aa[min(rank,len(aa)-1)]; delta=d['value']-anchor
                            sym=A.sym_expr(t,anchor,'u8 *' if mode=='pointer' else None,ext)
                            if mode=='integer':sym='(u32)('+sym+')'
                            expr='('+sym+(' + '+str(delta) if delta>0 else ' - '+str(-delta) if delta<0 else '')+')'
                            edits.append((d['start'],d['end'],'('+ty.strip()+')'+expr))
                        new=add_externs(edits_apply(t,edits),ext)
                        yield from unique('anchor:%s:%s:%s:%d:%d'%(v,group,mode,index,rank),new)
            for tag,new in page_candidates(t,v):
                yield from unique(tag+':'+group,new)
        # Full operand substitution remains a useful control at stock FSF split cells.
        new,info=A.rewrite_var(text,v)
        if new is not None:yield from unique('final-symbol:'+v,new)


def configurations(row):
    cell,flags=parse_cfg(row['cfg'])
    result=[row['cfg']]
    for c in ('2.7.2-cdk','2.8.1','2.8.0','2.7.2','2.6.3'):
        cfg=c+(' '+ ' '.join(flags) if flags else '')
        if parse_cfg(cfg)!=parse_cfg(row['cfg']) and cfg not in result:result.append(cfg)
    return result


TIDY=[(re.compile(r'\)\((D_[0-9A-Fa-f]{8})\)'),r')\1'),                      # (T *)(D_X) -> (T *)D_X
      (re.compile(r'\(([^()]+)\)\(\(\1\)(D_[0-9A-Fa-f]{8})\)'),r'(\1)\2')]  # (T)((T)D_X) -> (T)D_X


def tidy_text(t):
    for rx,rep in TIDY:t=rx.sub(rep,t)
    return t


class T:
    name='t54_pagebase'; level=1; needs_verify=True
    @staticmethod
    def eligible(text,row,census):
        return None if pagevars(text) else 'no pinned address-literal variable'
    @staticmethod
    def apply_verified(text,row,census,vf):
        # A win is re-spelled without redundant parentheses and casts, kept only if still exact
        cand,info=T._search(text,row,census,vf)
        if cand is not None:
            tidy=tidy_text(cand)
            if tidy!=cand and vf(tidy,info.get('cfg')).get('exact'):
                cand=tidy;info['tidied']=True
        return cand,info
    @staticmethod
    def _search(text,row,census,vf):
        budget=int(os.getenv('T54_COMPILERS','384')); maxvf=int(os.getenv('T54_VERIFY','8'))
        menu=list(source_candidates(text)); n=0; nv=0; tested=set(); near=[]; assembly_best={}
        base=compile_text(row,text)['assembly'];n+=1
        if base is None:return None,{'refused':['baseline compiler error']}
        configs=configurations(row)
        # Fairness across configurations and candidate kinds, capped globally.
        targets=[(row['cfg'],base)]
        for cfg in configs[1:]:
            if n>=budget:break
            target=compile_text(dict(row,cfg=cfg),text)['assembly'];n+=1
            if target is not None and distance(base,target)<=6:targets.append((cfg,target))
        percell=max(1,(budget-n)//len(targets))
        grouped=collections.defaultdict(list)
        for item in menu:
            parts=item[0].split(':')
            grouped[tuple(parts[:2])].append(item)
        fair=[]
        while any(grouped.values()):
            for g in grouped.values():
                if g:fair.append(g.pop(0))
        for cfg,target in targets:
            rr=dict(row,cfg=cfg)
            for tag,cand in fair[:percell]:
                if n>=budget:break
                obs=compile_text(rr,cand);n+=1
                asm=obs['assembly'];dist=distance(target,asm)
                if asm is None:continue
                ps=sites_of(cand)
                markers=tuple((s[1],cand[s[3]:s[4]]) for s in ps if s[1] not in ('ASM_REG','ASM_KEEP','ASM_KEEP_NV'))
                akey=(cfg,tuple(asm),markers)
                prior=assembly_best.get(akey)
                if prior is None:
                    assembly_best[akey]=(len(near),len(ps))
                    near.append((dist,tag,cfg,cand))
                elif len(ps)<prior[1]:
                    near[prior[0]]=(dist,tag,cfg,cand)
                    assembly_best[akey]=(prior[0],len(ps))
        # Prefer assembly-identical and fewer-pin candidates. Small residual allowance
        # covers assembler expansion of la / zero low halves; vf remains decisive.
        near.sort(key=lambda q:(q[0],len(sites_of(q[3])),q[2]!=row['cfg']))
        admitted={row['cfg']:True}
        for dist,tag,cfg,cand in near:
            if nv>=maxvf:break
            key=(sha_text(cand),cfg)
            if key in tested:continue
            tested.add(key)
            if cfg!=row['cfg']:
                if cfg not in admitted:
                    nv+=1;admitted[cfg]=bool(vf(text,cfg).get('exact'))
                if not admitted[cfg] or nv>=maxvf:continue
            nv+=1;res=vf(cand,None if cfg==row['cfg'] else cfg)
            if not res.get('exact'):continue
            if cfg!=row['cfg']:
                if nv>=maxvf:continue
                nv+=1;old=vf(cand)
                if old.get('exact'):
                    return cand,{'label':tag,'compiles':n,'verifies':nv,'distance':dist}
            info={'label':tag,'compiles':n,'verifies':nv,'distance':dist}
            if cfg!=row['cfg']:info['cfg']=cfg
            return cand,info
        return None,{'compiles':n,'verifies':nv,'candidates':len(menu),'nearest':[{'distance':d,'label':t,'cfg':c} for d,t,c,_ in near[:12]]}
