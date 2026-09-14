"""Stock GCC 2.x allocator comments, with explicit observed/inferred boundaries.

No compiler instrumentation: local quantity priorities/suggestions are unavailable.
Flow statistics in lreg are newer than flow (scheduler and equivalence updates).
All compiler files live in one automatically deleted temporary directory.
"""
import collections
import difflib
import os
from pathlib import Path
import re
import subprocess
import sys
import tempfile

ROOT = next(p for p in Path(__file__).resolve().parents if (p/'tools/common.py').is_file())
sys.path.insert(0, str(ROOT/'tools'))
from common import parse_cfg
from xform.reg_state import features, comparison
from xform.sched_trace import normalize, distance

FIRST={'2.6.3':67,'2.7.2':68,'2.7.2-cdk':76,'2.8.0':76,'2.8.1':76}

PHASES = ('rtl','jump','cse','loop','cse2','flow','combine','regmove','sched','lreg','greg','sched2')
REG = re.compile(r'\(reg(?P<flags>/\w+)?:([A-Z0-9]+) (\d+)(?: [^)]+)?\)')
STAT = re.compile(r'^Register (\d+) used (\d+) times across (-?\d+) insns([^\n]*)',re.M)

def hard_number(arg):
    s=arg.strip('$"')
    aliases={'v0':2,'v1':3,'a0':4,'a1':5,'a2':6,'a3':7,'hi':64,'lo':65,'gp':28,'sp':29,'fp':30,'ra':31}
    return int(s) if s.isdigit() else aliases.get(s,-1)

def regclass(n):
    return 'argument' if 4 <= n <= 7 else 'return' if n in (2,3) else 'saved' if 16 <= n <= 23 else 'other'

def parse_comments(dumps,first=68):
    result={}
    # Function names prevent cross-function pseudo-number collisions.
    for phase,src in dumps.items():
        chunks=re.split(r'^;; Function (\S+)[^\n]*\n',src,flags=re.M)
        for k in range(1,len(chunks),2):
            name,s=chunks[k:k+2]
            f=result.setdefault(name,dict(first_pseudo=first,stats={},local={},global_order=[],conflicts={},preferences={},assigned={},copies=[],stat_phase=None))
            if phase in ('flow','sched','lreg'):
                stats={}
                for m in STAT.finditer(s):
                    n,refs,live=int(m[1]),int(m[2]),int(m[3]); tail=m[4]
                    def num(p,default):
                        z=re.search(p,tail);return int(z[1]) if z else default
                    stats[n]=dict(refs=refs,live=live,block=num(r'in block (\d+)',-1),deaths=num(r'dies in (\d+) places',1),calls=num(r'crosses (\d+) calls?',0),bytes=num(r'(\d+) bytes',4),regclass=tail.split('; pref ',1)[-1].split(';')[0] if '; pref ' in tail else ('restricted' if 'or none' in tail else 'default'))
                if stats:
                    f['stats']=stats;f['stat_phase']=phase
            if phase=='lreg':
                f['local']={int(n):int(h) for n,h in re.findall(r';; Register (\d+) in (\d+)\.',s)}
                # Potential copy suggestions, not actual qty_phys_* vectors.
                pats=features(s)['raw']
                for pat in pats:
                    if re.fullmatch(r'\(set \(reg[^)]*\) \(reg[^)]*\)\)',pat):
                        rr=[int(m[3]) for m in REG.finditer(pat)]
                        if len(rr)==2 and (rr[0]<first)!=(rr[1]<first):f['copies'].append(rr)
            if phase=='greg':
                order=re.search(r';; \d+ regs to allocate:([^\n]*)',s)
                if order:
                    f['global_order']=[int(x.split('+')[0]) for x in re.findall(r'\d+(?:\+\d+)*',re.sub(r'\(\d+\)','',order[1]))]
                for key in ('conflicts','preferences'):
                    f[key]={int(n):list(map(int,re.findall(r'\d+',v))) for n,v in re.findall(r';; (\d+) '+key+r':([^\n]*)',s)}
                disp=re.search(r';; Register dispositions:([\s\S]*?)(?:;; Hard regs used:|\Z)',s)
                if disp:f['assigned']={int(n):int(h) for n,h in re.findall(r'(\d+) in (\d+)',disp[1])}
    return result

def observe(row,text,retain=None,full=False):
    cell,flags=parse_cfg(row['cfg']);cc=ROOT/'toolchain/compilers'/('gcc-'+cell)
    with tempfile.TemporaryDirectory(prefix='t60_') as td:
        d=Path(td);f=d/Path(row['c_path']).name;f.write_text(text)
        cmd=[str(cc/'gcc'),'-B'+str(cc)+'/', '-S','-O2',*flags,'-I'+str(ROOT/'include'),'-w','-da',f.name,'-o','f.s']
        try:p=subprocess.run(cmd,cwd=d,capture_output=True,text=True,timeout=float(os.getenv('T60_TIMEOUT','45')))
        except subprocess.TimeoutExpired:return dict(assembly=None,error='compiler-timeout',features={},state={},patterns={})
        if p.returncode or not (d/'f.s').is_file():return dict(assembly=None,error=(p.stderr or p.stdout)[-1000:],features={},state={},patterns={})
        want=PHASES if full else ('rtl','flow','combine','regmove','sched','lreg','greg')
        ds={p.suffix[1:]:p.read_text(errors='replace') for p in d.iterdir() if p.suffix[1:] in want}
        ds={p:ds[p] for p in PHASES if p in ds}
        asm=(d/'f.s').read_text(errors='replace')
        ff={p:features(s) for p,s in ds.items() if p in (PHASES if full else ('combine','sched','greg','regmove'))}
        patterns={}
        for phase in ('rtl','sched','lreg'):
            chunks=re.split(r'^;; Function (\S+)[^\n]*\n',ds.get(phase,''),flags=re.M)
            for k in range(1,len(chunks),2):patterns.setdefault(chunks[k],{})[phase]=features(chunks[k+1])['raw']
        ob=dict(assembly=normalize(asm),error=None,features=ff,state=parse_comments(ds,FIRST.get(cell,76)),patterns=patterns,cell=cell,passes=list(ds))
        if retain:
            dest=Path(retain);dest.mkdir(parents=True,exist_ok=True);(dest/'source.c').write_text(text);(dest/'assembly.s').write_text(asm)
            for phase,s in ds.items():(dest/('dump.'+phase)).write_text(s)
        return ob

def shape(p):return REG.sub(lambda m:'(reg:'+m[2]+')',p)

def aligned(a,b):
    aa=list(map(shape,a));bb=list(map(shape,b))
    if aa==bb:return list(zip(a,b)),True
    pairs=[]
    for block in difflib.SequenceMatcher(None,aa,bb,autojunk=False).get_matching_blocks():
        pairs.extend(zip(a[block.a:block.a+block.size],b[block.b:block.b+block.size]))
    return pairs,False

def correspondence(a,b):
    counts=collections.defaultdict(collections.Counter)
    pairs,equal=aligned(a,b)
    for pa,pb in pairs:
        for ra,rb in zip(REG.finditer(pa),REG.finditer(pb)):
            counts[int(rb[3])][int(ra[3])]+=1
    mapping={r:next(iter(c)) for r,c in counts.items() if len(c)==1}
    return mapping,pairs,equal

def owner(f,n):
    if n<f.get('first_pseudo',68):return 'hard'
    if n in f['local']:return 'local'
    if n in f['global_order']:return 'global'
    return 'unassigned-or-eliminated'

def priority(s):
    refs=s.get('refs',0);live=s.get('live',0)
    return int((refs.bit_length()-1)*refs*max(1,(s.get('bytes',4)+3)//4)*10000/live) if refs>0 and live>0 else None

def diagnose(target,cand,hard=None):
    changes=collections.Counter(); detail=[]; bound=[]; alloc_diff=0;operands=0;peer_count=0;missing=0;unknown_edges=0
    for fn,bs in cand['state'].items():
        if fn not in target['state']:continue
        ts=target['state'][fn];ap=target['patterns'].get(fn,{});bp=cand['patterns'].get(fn,{})
        phase='sched' if ap.get('sched') and bp.get('sched') else 'lreg'
        mp,pairs,equal=correspondence(ap.get(phase,[]),bp.get(phase,[]))
        # Source binding correspondence uses user-variable flags, before CSE when possible.
        if hard is not None:
            anchor=phase
            rp=pairs;bc=collections.Counter()
            for pa,pb in rp:
                for ra,rb in zip(REG.finditer(pa),REG.finditer(pb)):
                    if int(ra[3])==hard and 'v' in (ra['flags'] or '') and int(rb[3])>=bs.get('first_pseudo',68):bc[int(rb[3])]+=1
            if not bc:
                anchor='rtl'
                rp,_=aligned(ap.get('rtl',[]),bp.get('rtl',[]))
                for pa,pb in rp:
                    for ra,rb in zip(REG.finditer(pa),REG.finditer(pb)):
                        if int(ra[3])==hard and 'v' in (ra['flags'] or '') and int(rb[3])>=bs.get('first_pseudo',68) and 'v' in (rb['flags'] or ''):bc[int(rb[3])]+=1
            for r,n in bc.most_common():
                st=bs['stats'].get(r,{})
                bound.append(dict(function=fn,pseudo=r,anchor=anchor,evidence_occurrences=n,owner=owner(bs,r),assigned=bs['assigned'].get(r),stats=st,global_priority_proxy=priority(st),hard_conflict=hard in bs['conflicts'].get(r,[]),preference=hard in bs['preferences'].get(r,[]),potential_copies=[x for x in bs['copies'] if r in x]))
        for pa,pb in pairs:
            for ra,rb in zip(REG.finditer(pa),REG.finditer(pb)):
                x,y=int(ra[3]),int(rb[3]);xx=ts['assigned'].get(x,x);yy=bs['assigned'].get(y,y)
                alloc_diff+=xx!=yy;operands+=1
        for r,t in mp.items():
            if r<bs.get('first_pseudo',68) or t<ts.get('first_pseudo',68):continue
            if r not in bs['stats'] or t not in ts['stats']:missing+=1;continue
            peer_count+=1;a=ts['stats'][t];b=bs['stats'][r];diff=[]
            if owner(ts,t)!=owner(bs,r):diff.append('membership')
            if any(a.get(k)!=b.get(k) for k in ('refs','live','bytes')):diff.append('priority_inputs')
            if a.get('calls')!=b.get('calls'):diff.append('call_crossing')
            if a.get('deaths')!=b.get('deaths') or a.get('block')!=b.get('block'):diff.append('local_eligibility_inputs')
            if ts['preferences'].get(t,[])!=bs['preferences'].get(r,[]):diff.append('global_preferences')
            mapped=set(n if n<bs.get('first_pseudo',68) else mp[n] for n in bs['conflicts'].get(r,[]) if n!=r and (n<bs.get('first_pseudo',68) or n in mp))
            known_target=set(mp.values())
            expected=set(n for n in ts['conflicts'].get(t,[]) if n!=t and (n<ts.get('first_pseudo',68) or n in known_target))
            unknown_edges += sum(n>=bs.get('first_pseudo',68) and n not in mp for n in bs['conflicts'].get(r,[]) if n!=r)
            unknown_edges += sum(n>=ts.get('first_pseudo',68) and n not in known_target for n in ts['conflicts'].get(t,[]) if n!=t)
            if mapped!=expected:diff.append('conflicts')
            if r!=t:diff.append('numbering')
            changes.update(diff)
            if diff:detail.append(dict(function=fn,pinned=t,erased=r,changes=diff,before=a,after=b,owners=[owner(ts,t),owner(bs,r)]))
    input_distance=sum(v for k,v in changes.items() if k!='numbering')
    return dict(asm=distance(target['assembly'],cand['assembly']),allocation_operand_distance=alloc_diff,aligned_operands=operands,peer_input_distance=input_distance,peer_compared=peer_count,peer_missing=missing,conflict_unmapped_edges=unknown_edges,changes=dict(changes),bound=bound,details=detail)
