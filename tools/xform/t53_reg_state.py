"""T53: register-pin rewrites screened against the current compiler's pass streams.

Current text only; no atlas/row-name lookup, flags, fake uses, added asm or volatile.
Default limits: 384 observations and 24 vf calls, overridable by T53_COMPILERS and
T53_VERIFY (one compiler at a time). State distance is a ranking heuristic; only
vf accepts a candidate. Lossy stream equality is deliberately not a hard filter.
Existing natural/T51/T37/T42 parsers supply complementary menus; T53 adds unfiltered
declaration-order trials, ordinary-local width trials, a known-page OR spelling,
family/site fairness and a two-rewrite state beam.

Built by the reg_astra lane (work/native_lane/reg_astra/REPORT.md, 2026-09-13) with reg_state.py.
Register pins split at combine into ops / wiring / late / order (a phase census): a pin changes which
producers survive, the data flow between them, the allocation, or the order. Frozen held-out result:
H1 (census rows by class) 2/50, both ops; H2 (population) 4/60 - six REG pins, no fences. Wins came
from combinations (a width change that worsens assembly distance but improves pass-stream distance,
then a fusion) and from selection among t37/t51 menus. The journal keeps the 12 nearest candidates.
VERIFY budget: every one of the first 13 wins (the lane's 7, the sweep's first 6) was accepted on its
FIRST vf call (an assembly-identical candidate); the closing round that scores non-identical candidates
never won, yet spent all 24 calls on 86% of misses, and verify serialises on a per-window lock. The
default is 3 (was the lane's 24).
A candidate's observation parses only its base's deciding pass, combine and greg - every pass metrics()
reads, so decisions are unchanged - because parsing all 13-16 dumps of a large function costs ~0.5 s of
pure Python per compile, and sweep.py's worker threads share one GIL (run it at about 8 workers).
"""
import collections
import itertools
import os
from pathlib import Path
import re
import sys

ROOT = next(p for p in Path(__file__).resolve().parents if (p / 'tools/common.py').is_file())
sys.path.insert(0, str(ROOT / 'tools'))
from common import sha_text
from pin_census import sites_of, unscored_text, asm_blocker
from pin_sites import erase_many
from xform import t51_sched_order as S
from xform import t37_localwidth as W
from xform import t42_sinkcopy as K
from xform import natural as N
from xform.reg_state import observe, comparison, metrics


def extra_candidates(text, var):
    """A type or declaration on another real local can control the target's allocation."""
    decl = S.declarations(text)
    bodies = [(a,b) for _,_,a,b in K.functions(text)]
    decl = {v:d for v,d in decl.items() if any(a < d['start'] < b for a,b in bodies)}
    masked = S.mask(text)
    names = sorted(decl, key=lambda v: (v != var, abs(decl[v]['start']-decl.get(var, decl[v])['start']),v))
    for v in names:
        d = decl[v]
        seg = masked[d['start']:d['end']]
        if 'ASM_' in seg or '=' in seg or 'volatile' in seg or 'const' in seg:
            continue
        ty = W.ALIAS.get(d['type'], d['type'])
        if ty in W.INT_TYPES:
            pat = W.decl_re(v)
            ds = list(pat.finditer(masked))
            if len(ds) == 1:
                a,b = ds[0].span('ty')
                for new in W.INT_TYPES:
                    if new != ty:
                        yield 'width:%s:%s>%s' % (v,ty,new), text[:a]+new+text[b:]
        # Reorder only contiguous uninitialized declaration lists. No expressions move.
        for u in names:
            e = decl[u]
            if e['start'] >= d['start'] or 'ASM_' in masked[e['start']:e['end']]:
                continue
            region = masked[e['start']:d['start']]
            if any(c in region for c in '{}#='):
                continue
            if any(line.strip() and not re.match(r'^\s*(?:register\s+)?(?:[A-Za-z_]\w*\s+)+(?:\*\s*)*[A-Za-z_]\w*\s*;',line)
                   for line in region.splitlines()):
                continue
            end = text.find('\n', d['end'])
            end = len(text) if end < 0 else end+1
            yield 'decl-swap:%s:%s' % (v,u), text[:e['start']]+text[d['start']:end]+text[e['start']:d['start']]+text[end:]


def page_candidates(text, focus_var):
    """Known aligned byte-pointer base plus disjoint bits can be spelled as bitwise OR.

    This changes an actual address producer. Require one constant definition,
    no compound updates/address escape, and a byte pointer (unscaled addition).
    """
    masked=S.mask(text)
    bodies=[(a,b) for _,_,a,b in K.functions(text)]
    for v,d in S.declarations(text).items():
        if not any(a<d['start']<b for a,b in bodies): continue
        if d['type'].replace(' ','') not in ('u8*','s8*','char*','unsignedchar*'): continue
        V=re.escape(v)
        writes=list(re.finditer(r'\b'+V+r'\s*(?:=(?!=)|[-+*/%&|^]=|\+\+|--)',masked))
        if len(writes)!=1 or re.search(r'&\s*\b'+V+r'\b|(?:\+\+|--)\s*\b'+V+r'\b',masked):continue
        assign=re.match(r'\b'+V+r'\s*=\s*(?:\([^;()]+\)\s*)?(0x[0-9A-Fa-f]+)\s*;',masked[writes[0].start():])
        if not assign:continue
        base=int(assign[1],16)
        hits=list(re.finditer(r'\b'+V+r'\s*\+\s*(0x[0-9A-Fa-f]+|\d+)\b',masked))
        def focused(m):
            start=masked.rfind('\n',0,m.start())+1;end=masked.find('\n',m.end())
            return (0 if focus_var and re.search(r'\b'+re.escape(focus_var)+r'\b',masked[start:end]) else 1,m.start())
        for m in sorted(hits,key=focused):
            literal=m[1]
            offset=int(literal,16 if literal.lower().startswith('0x') else 8 if len(literal)>1 and literal.startswith('0') else 10)
            if offset==0 or base & offset or base+offset>0xffffffff:continue
            replacement='(('+d['type']+')((u32)'+v+' | '+m[1]+'))'
            yield 'page-or:%s:%d'%(v,masked.count('\n',0,m.start())+1),text[:m.start()]+replacement+text[m.end():]


def menu(text, line, var, cls):
    groups = collections.defaultdict(list)
    for tag,cand in S.candidates(text,line,var):
        groups[tag.split(':')[0]].append((tag,cand))
    for gen in N.ALLOC_LEVERS + (N.splitcursor_candidates,):
        for tag,cand in gen(text):
            groups[tag.split(':')[0]].append((tag,cand))
    for tag,cand in extra_candidates(text,var):
        groups[tag.split(':')[0]].append((tag,cand))
    for tag,cand in page_candidates(text,var):
        groups['page-or'].append((tag,cand))
    # Sinking requires a retained pin to identify the copy, but may free another pin too.
    for tag,cand in K.candidates(text):
        groups['sinkcopy'].append((tag,cand))
    preferred = {
        'ops': ['page-or','fuse','width','single-set','splitcursor','unhost','hostwide','move','commute'],
        'wiring': ['single-set','splitcursor','hostwide','unhost','width','fuse','move'],
        'late': ['hostwide','unhost','single-set','decl-swap','splitcursor','width','move'],
        'order': ['move','fuse','single-set','commute','hostwide'],
    }.get(cls,[])
    keys = preferred + sorted(set(groups)-set(preferred))
    # Round robin so a large type/order family cannot consume a site's whole allowance.
    seen = set()
    for level in itertools.count():
        any_left = False
        for key in keys:
            if level >= len(groups[key]):
                continue
            any_left = True
            tag,cand = groups[key][level]
            h = sha_text(cand)
            if h not in seen:
                seen.add(h)
                yield tag,cand
        if not any_left:
            break


def state_rank(m):
    val = lambda k: m[k] if m[k] is not None else 1000000
    return (sum(val(k) != 0 for k in ('p','combine','greg_raw')),
            val('combine') + val('greg_raw'), val('p'), m['asm'])


class T:
    name = 't53_reg_state'
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text,row,census):
        if not any(s[1] == 'ASM_REG' for s in sites_of(text)):
            return 'no live register pins'
        return asm_blocker(text) or (None if row.get('cfg') else 'missing compiler recipe')

    @staticmethod
    def apply_verified(text,row,census,vf):
        new, log = T._search(text,row,census,vf)
        # A row observes up to 384 candidates: the journal keeps the 12 nearest by assembly distance
        cands = log.get('candidates') or []
        log['candidates_n'] = len(cands)
        log['candidates'] = sorted(cands, key=lambda r: (r['asm'], r['tag']))[:12]
        return new, log

    @staticmethod
    def _search(text,row,census,vf):
        budget = max(1,int(os.getenv('T53_COMPILERS','384')))
        vbudget = max(1,int(os.getenv('T53_VERIFY','3')))
        pins, usig = sites_of(text), unscored_text(text)
        log = dict(pins_in=len(pins), compiler_budget=budget, vf_budget=vbudget,
                   compiles=0,tried=0,compile_failures=0,sites=[],candidates=[],steps=[])
        observations, scores = {}, {}
        def ob(c, phases=None):
            h = sha_text(c)
            if h not in observations:
                if log['compiles'] >= budget: return None
                log['compiles'] += 1
                observations[h] = observe(row,c,phases=phases)
                if observations[h]['assembly'] is None: log['compile_failures'] += 1
            return observations[h]
        def valid(c):
            return len(sites_of(c)) < len(pins) and unscored_text(c) == usig
        def score(c,rec):
            h = sha_text(c)
            if h not in scores:
                if log['tried'] >= vbudget: return False
                log['tried'] += 1
                scores[h] = vf(c)
            rec['vf'] = {k:scores[h].get(k) for k in ('exact','total','status')}
            return scores[h].get('exact') is True
        target = ob(text)
        if target is None or target['assembly'] is None:
            return None,dict(log,error='baseline compiler failure')
        bases, pool, seen = [], [], {sha_text(text)}
        # Observe all up to 16 REG sites, then keep six nearest with class diversity.
        for i,s in [(i,s) for i,s in enumerate(pins) if s[1]=='ASM_REG'][:16]:
            c = erase_many(text,[s],clean_notes=True)
            if not valid(c): continue
            a = ob(c)
            if a is None or a['assembly'] is None: continue
            diag = comparison(target,a)
            phase = diag['first']['abs'] or 'greg'
            m = metrics(target,a,phase)
            var = s[6].split()[-1].lstrip('*')
            rec = dict(site=i,tag='erase',cls=diag['cls'],first=diag['first'],**m)
            log['sites'].append(rec)
            bases.append(dict(c=c,site=i,line=s[5]-1,var=var,cls=diag['cls'],phase=phase,m=m))
            pool.append((c,rec));seen.add(sha_text(c))
            if m['asm']==0 and score(c,rec):
                log['steps'].append('erase:%d'%i)
                return c,dict(log,pins_out=len(sites_of(c)))
        ordered = sorted(bases,key=lambda b:(b['m']['asm'],b['site']))
        chosen=[]
        for cls in ('ops','wiring','late','order'):
            hit=next((b for b in ordered if b['cls']==cls),None)
            if hit is not None: chosen.append(hit)
        chosen += [b for b in ordered if b not in chosen][:max(0,6-len(chosen))]
        chosen.sort(key=lambda b:(b['m']['asm'],b['site']))
        for bi,b in enumerate(chosen):
            cphases=(b['phase'],'combine','greg')     # all metrics() reads of a candidate
            allowance=max(0,(budget-log['compiles'])//(len(chosen)-bi))
            used=0
            tested=[]
            for tag,c in menu(b['c'],b['line'],b['var'],b['cls']):
                if used >= max(1,allowance*3//4): break
                h=sha_text(c)
                if h in seen or not valid(c): continue
                seen.add(h);a=ob(c,cphases);used+=1
                if a is None: break
                if a['assembly'] is None: continue
                m=metrics(target,a,b['phase'])
                observations.pop(h,None)
                rec=dict(site=b['site'],cls=b['cls'],tag=tag,depth=1,**m)
                log['candidates'].append(rec);pool.append((c,rec));tested.append((c,rec))
                if m['asm']==0 and score(c,rec):
                    log['steps'].append('erase:%d/%s'%(b['site'],tag))
                    return c,dict(log,pins_out=len(sites_of(c)))
            # Two different ranking paths, only strict improvements over the erased base.
            beam=[]
            for key in (lambda x:state_rank(x[1]),lambda x:(x[1]['asm'],state_rank(x[1]))):
                if not tested: continue
                c,rec=min(tested,key=key)
                if (rec['asm'] < b['m']['asm'] or state_rank(rec) < state_rank(b['m'])) and c not in [x[0] for x in beam]:
                    beam.append((c,rec))
            for seed,seedrec in beam:
                limit=max(1,(allowance-used)//max(1,len(beam)))
                n=0
                for tag,c in menu(seed,b['line'],b['var'],b['cls']):
                    if used >= allowance or n>=limit: break
                    h=sha_text(c)
                    if h in seen or not valid(c): continue
                    seen.add(h);a=ob(c,cphases);used+=1;n+=1
                    if a is None: break
                    if a['assembly'] is None: continue
                    rec=dict(site=b['site'],cls=b['cls'],tag=seedrec['tag']+' / '+tag,depth=2,
                             **metrics(target,a,b['phase']))
                    observations.pop(h,None)
                    log['candidates'].append(rec);pool.append((c,rec))
                    if rec['asm']==0 and score(c,rec):
                        log['steps'].append('erase:%d/%s'%(b['site'],rec['tag']))
                        return c,dict(log,pins_out=len(sites_of(c)))
        # Compare/retain both screens. Interleave equal-sized rankings under one vf budget.
        state=sorted(pool,key=lambda x:(state_rank(x[1]),x[1]['tag']))
        assembly=sorted(pool,key=lambda x:(x[1]['asm'],x[1]['tag']))
        for st,ass in itertools.zip_longest(state,assembly):
            for item in (ass,st):
                if item is None: continue
                c,rec=item
                if sha_text(c) in scores: continue
                if log['tried'] >= vbudget: break
                if score(c,rec):
                    log['steps'].append('erase:%d/%s'%(rec['site'],rec['tag']))
                    return c,dict(log,pins_out=len(sites_of(c)))
            if log['tried'] >= vbudget: break
        return None,dict(log,pins_out=len(pins))
