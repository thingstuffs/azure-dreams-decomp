#!/usr/bin/env python3
"""Map every scheduling / delay-slot residue to the C statements it moves between.

    python3 tools/lanes/sched_map.py OUT.jsonl SITES.tsv [SITES.tsv ...]      (the erase_census/phase lists)
    python3 tools/lanes/sched_map.py summary OUT.jsonl

For each site (row, site index, first differing pass, macro) the pinned text and the text with that one
site erased are compiled with `-g -da` at the row's own cell.  `-g` keeps gcc 2.x's source line notes in
every RTL dump - `(note N M K ("file.c") LINE)` - so each insn of the deciding pass's dump maps to the C
line whose note precedes it (the listing's byte distance changes under -g, the insn ORDER does not; the
plain-flag residue's opcode agreed with the -g pattern class on the sites checked in round 31).  The
insns whose relative order differs between the two dumps (the complement of the longest common
increasing subsequence) are the MOVED insns; each is reported with its RTL pattern head, its C line and
statement, the C lines of the insns it crossed, and what t51_sched_order's own tests say about moving
that statement over those: `stmt-not-simple` (a control line, a brace, a declaration, a multi-line
statement), `same-statement` (an intra-statement reorder), `depth-differs`, `dep-mem` (t51 never
reorders two memory statements), `dep-data`, or `independent` (t51 would offer the move).  A `.dbr` dump
wraps a filled delay slot in `(sequence [...])` with the insns indented: the parser accepts leading
whitespace so those count.

Round 31 read: a moved insn on the function's `{` / signature line is the PROLOGUE (the `$sp` adjust or a
callee-saved store, scheduled among the first statements by sched2 and into delay slots by dbr): 89 of
588 sites, one coherent class.  Of the 402 first-scheduler sites 312 move three or more insns, and a
single t51 statement move reached distance 0 on 0 of 60 `independent` sites: the body class is a region
reschedule, not a misplaced statement.  Output stays in the scratchpad or a lane's rows/ (~0.5 MB).
"""
import sys, json, re, collections, time
from multiprocessing import Pool
from pathlib import Path
ROOT = next(p for p in Path(__file__).resolve().parents if (p / 'tools/common.py').is_file())
sys.path.insert(0, str(ROOT / 'tools')); sys.path.insert(0, str(ROOT / 'tools/xform'))
from common import rows
from pin_census import sites_of
from pin_sites import erase_many
import phase_census as PC
from xform import t51_sched_order as T
R={r['id']:r for r in rows()}
INSN=re.compile(r'^\((note|insn|jump_insn|call_insn) (\d+) \d+ \d+ (?:\("[^"]*"\) (\d+)|(.*?))\)?$', re.M)
def order(dump):
    out=[]; line=None
    for m in re.finditer(r'^[ \t]*\((note|insn|jump_insn|call_insn) (\d+) -?\d+ -?\d+ (.*)$', dump, re.M):
        k,uid,rest=m.group(1),int(m.group(2)),m.group(3)
        if k=='note':
            mm=re.match(r'\("[^"]*"\) (\d+)\)', rest)
            if mm: line=int(mm.group(1))
            continue
        body=dump[m.end():m.end()+160].strip().split('\n')[0]
        cls=('call' if k=='call_insn' else 'jump' if k=='jump_insn' else
             'store' if re.match(r'\(set \(mem', rest+body) else
             'load' if '(mem' in (rest+body) else 'const' if 'const_int' in body and '(reg' not in body[body.find(')'):] else 'op')
        out.append((uid,line,cls,(rest+' '+body)[:110]))
    return out
def moved(a,b):
    """insns whose relative order differs: the minimal set to remove from a so that the rest is in b's order."""
    pa={u:i for i,(u,*_) in enumerate(a)}; pb={u:i for i,(u,*_) in enumerate(b)}
    common=[u for u,*_ in a if u in pb]
    # longest increasing subsequence of pb positions over common; the rest moved
    seq=[pb[u] for u in common]
    import bisect
    tails=[]; prev=[-1]*len(seq); idx=[]
    for i,x in enumerate(seq):
        j=bisect.bisect_left([seq[t] for t in tails], x)
        if j<len(tails): tails[j]=i
        else: tails.append(i)
        prev[i]=tails[j-1] if j>0 else -1
    keep=set(); k=tails[-1] if tails else -1
    while k!=-1: keep.add(k); k=prev[k]
    return [common[i] for i in range(len(common)) if i not in keep]
def one(task):
    rid,sites=task; row=dict(R[rid]); row['cfg']=row['cfg']+' -g'
    text=(ROOT/'src'/(rid+'.c')).read_text(); allsites=sites_of(text)
    base=PC.compile_dumps(row,text)
    if base is None: return [dict(id=rid,err='base')]
    lines,recs=T.units(text); byline={r['line']+1:r for r in recs}
    out=[]
    for si,pas,macro in sites:
        if si>=len(allsites) or allsites[si][1]!=macro: out.append(dict(id=rid,site=si,err='stale')); continue
        s=allsites[si]; er=erase_many(text,[s],clean_notes=True)
        after=PC.compile_dumps(row,er)
        if after is None or pas not in base['dumps'] or pas not in after['dumps']: out.append(dict(id=rid,site=si,err='erased')); continue
        a=order(base['dumps'][pas]); b=order(after['dumps'][pas])
        # line numbers in the erased text: statement pins delete one line at s[5]; map back to the pinned text
        shift=(1 if s[0]=='stmt' else 0); pinline=s[5]
        def toorig(l): return None if l is None else (l+shift if (shift and l>=pinline) else l)
        mv=moved(a,b); la={u:(l,c) for u,l,c,_ in a}; lb={u:(l,c) for u,l,c,_ in b}; pat={u:pt for u,l,c,pt in a}
        rec=dict(id=rid,site=si,macro=macro,pas=pas,pinline=pinline,moved=[])
        pa={u:i for i,(u,*_) in enumerate(a)}; pb={u:i for i,(u,*_) in enumerate(b)}
        for u in mv[:3]:
            l1,c1=la[u]; i0,i1=pa[u],pb.get(u,pa[u])
            crossed=[x for x in a[min(i0,i1):max(i0,i1)+1] if x[0]!=u and x[0] in pb]
            cl=sorted({toorig(x[1]) for x in crossed if x[1] is not None}); ck=collections.Counter(x[2] for x in crossed)
            L1=toorig(l1); r1=byline.get(L1); why=[]
            if r1 is None: why.append('stmt-not-a-unit')
            elif not r1['simple']: why.append('stmt-not-simple')
            for L2 in cl:
                if L2==L1: why.append('same-statement'); continue
                r2=byline.get(L2)
                if r2 is None: why.append('crossed-not-a-unit'); continue
                if not r2['simple']: why.append('crossed-not-simple'); continue
                if r1 and r2 and r1['depth']!=r2['depth']: why.append('depth-differs'); continue
                if r1 and r2 and r1['arm']!=r2['arm']: why.append('arm-differs'); continue
                if r1 and not T.independent(r1['masked'],r2['masked']):
                    wa,ra,ma=T.access(r1['masked']); wb,rb,mb=T.access(r2['masked'])
                    why.append('dep-mem' if (ma and mb) and not (wa&(rb|wb) or wb&ra) else 'dep-data')
                else: why.append('independent')
            rec['moved'].append(dict(uid=u,cls=c1,line=L1,rtl=pat.get(u,''),stmt=(lines[L1-1].strip()[:80] if L1 and L1<=len(lines) else ''),crossed_lines=cl,crossed_kinds=dict(ck),dist=abs(i1-i0),why=why))
        out.append(rec)
    return out
def summary(path):
    recs=[json.loads(l) for l in open(path)]
    ok=[r for r in recs if 'err' not in r]; print('sites', len(recs), 'ok', len(ok), 'errors', dict(collections.Counter(r.get('err') for r in recs if 'err' in r)))
    lead=collections.Counter(); nm=collections.Counter()
    for r in ok:
        nm[(r['pas'], min(len(r['moved']),3))]+=1
        if r['moved']:
            ws=r['moved'][0]['why']; lead[(r['pas'], 'independent' if ws and all(w in ('independent','same-statement') for w in ws) else (ws[0] if ws else 'none'))]+=1
    print('moved insns per site (pass, count capped 3):', sorted(nm.items())); print('lead reason by pass:')
    for k,v in sorted(lead.items(), key=lambda kv:(kv[0][0],-kv[1])): print('  %-7s %-20s %4d'%(k[0],k[1],v))
def main():
    a=sys.argv[1:]
    if a and a[0]=='summary': return summary(a[1])
    out=Path(a[0]); lists=a[1:]
    tasks=collections.defaultdict(list)
    for name in lists:
        for l in open(name):
            if l.startswith('#'): continue
            rid,site,macro,npins,line,var,d0,fp,res=l.rstrip('\n').split('\t')
            tasks[rid].append((int(site),fp,macro))
    t0=time.time(); n=0
    with Pool(6) as p, open(out,'w') as f:
        for recs in p.imap_unordered(one, list(tasks.items()), chunksize=2):
            for r in recs: f.write(json.dumps(r)+'\n')
            f.flush(); n+=1
            if n%50==0: print(n,'rows',round(time.time()-t0),'s',flush=True)
    print('done',n,'rows',round(time.time()-t0),'s')

if __name__ == '__main__':
    main()
