#!/usr/bin/env python3
"""Bounded single-intervention search with a five-row validation gate.

Discovery is from this input's executed compiler sites, never from solved text.
Each candidate is ONE schema-validated intervention. Trials run in a bounded,
nice'd pool, retain emitted assembly and raw linked-byte receipts, and rank raw
exact first. Missing/failed validation keeps every open-row result diagnostic.
"""
from __future__ import annotations
import argparse, collections, concurrent.futures, difflib, hashlib, itertools, json, re, shutil, time, os
from pathlib import Path
import kitlib, sncheck, pass_oracle
import alloc263_oracle as alloc_oracle
KNOWN=('800AED64','81844F2C','8028906C','818B6AFC','80D68308')
VERSION=4

def key(change):return json.dumps(change,sort_keys=True,separators=(',',':'))
def members(change):return pass_oracle.members(change)

def shape(patterns):
    """Pattern class of a combine attempt: pseudo numbers anonymised."""
    return re.sub(r'p\d+','p',json.dumps(patterns))

def word_regs(w):
    """(mask of register fields, [(field shift)]) for one MIPS I word; jumps have none."""
    op=w>>26
    if op in (2,3):return 0,[]
    if op==0:return 0x03fff800,[21,16,11]
    if op in (0x10,0x11,0x12,0x13):return 0x001ff800,[16,11]
    return 0x03ff0000,[21,16]

def wrong_registers(got,retail):
    """Hard registers whose fields differ where the aligned words differ ONLY in register fields."""
    ga=[int.from_bytes(got[i:i+4],'little') for i in range(0,len(got)-3,4)]
    ra=[int.from_bytes(retail[i:i+4],'little') for i in range(0,len(retail)-3,4)]
    wrong=collections.Counter();pairs=collections.Counter()
    for tag,i1,i2,j1,j2 in difflib.SequenceMatcher(None,ga,ra,autojunk=False).get_opcodes():
        if tag!='replace' or i2-i1!=j2-j1:continue
        for a,b in zip(ga[i1:i2],ra[j1:j2]):
            mask,fields=word_regs(a)
            if not fields or (a&~mask)!=(b&~mask) or word_regs(b)[0]!=mask:continue
            for sh in fields:
                x,y=(a>>sh)&31,(b>>sh)&31
                if x!=y:wrong[x]+=1;pairs[(x,y)]+=1
    return wrong,pairs

def focus_pseudos(observation,wrong,limit=32):
    """Pseudos coloured with a dominant wrong register (seen >= 2 times and within 5x of
    the most frequent one) in the aligned diff; global allocnos first, at most `limit`."""
    if not wrong:return set()
    top=max(wrong.values());regs={r for r,n in wrong.items() if n>=2 and n*5>=top}
    cands=sorted({(e['allocno']<0,e['pseudo']) for e in observation.get('events',[]) if e['kind']=='global-colour' and e['hardreg'] in regs})
    return {p for _,p in cands[:limit]}

def enumerate_changes(observation, include_alloc=True, focus=()):
    """Deterministic space. Tier A (cheap, targeted): global-avoid and allocator inputs
    on focus pseudos (wrong colour in the aligned diff) and combine pattern classes
    (one veto at EVERY site of the same anonymised pattern, e.g. a fold the source
    repeats per block). Tier B: every family interleaved, as observed."""
    focus=set(focus);groups=collections.defaultdict(list)
    es=observation.get('events',[])
    combines=[e for e in es if e['kind']=='combine-veto' and e.get('success')]
    crossable={tuple(x['uids']) for x in es if x['kind']=='combine-crosses' and x['value']==0}
    combines.sort(key=lambda e:('zero_extend' not in str(e.get('patterns')) or 'ashiftrt' not in str(e.get('patterns')),e['uids']))
    classes=collections.defaultdict(list)
    for e in combines:
        if e['uids'] not in classes[shape(e['patterns'])]:classes[shape(e['patterns'])].append(e['uids'])
        for k in ('combine-crosses','combine-veto'):
            if k=='combine-crosses' and tuple(e['uids']) not in crossable:continue
            groups['combine'].append({'kind':k,'uids':e['uids']})
    for sh,sites in sorted(classes.items(),key=lambda kv:(-len(kv[1]),kv[0])):
        if 2<=len(sites)<=pass_oracle.MAX_COMPOSITE:
            groups['combine-class'].append([{'kind':'combine-veto','uids':u} for u in sites])
            if all(tuple(u) in crossable for u in sites):groups['combine-class'].append([{'kind':'combine-crosses','uids':u} for u in sites])
    for e in es:
        k=e['kind']
        if k=='sched-birth' and e['value']==1:
            groups['sched'].append({'kind':k,'uid':e['uid'],'phase':e['phase'],'value':0})
        elif k=='sched-priority':
            for v in (e['before']-1,e['before']+1,0):
                if v!=e['value']:groups['priority'].append({'kind':k,'uid':e['uid'],'phase':e['phase'],'value':v})
        elif k=='sched-luid':
            for v in (0,100000):
                if v!=e['value']:groups['luid'].append({'kind':k,'uid':e['uid'],'phase':e['phase'],'value':v})
        elif k=='cse-copy-swap':groups['cse'].append({'kind':k,'uid':e['uid']})
        elif k=='cse-substitution':groups['substitution'].append({'kind':k,'uid':e['uid'],'occurrence':e['occurrence']})
        elif k=='cse-eqv-head':
            for h in e.get('chain',[]):
                if h!=e['head']:groups['cse-head'].append({'kind':k,'new':e['new'],'old':e['old'],'occurrence':e['occurrence'],'head':h})
        elif k=='alias' and e['value']==0 and len(set(e['uids']))==2:groups['alias'].append({'kind':k,'uids':e['uids'],'phase':e['phase'],'value':1})
        elif k=='loop-hoist' and not e['done']:groups['loop'].append({'kind':k,'uid':e['uid']})
        elif k=='loop-biv' and e['pseudo'] is not None:groups['biv'].append({'kind':k,'uid':e['uid'],'pseudo':e['pseudo']})
        elif k=='keep-dead':groups['dead'].append({'kind':k,'uid':e['uid']})
        elif k=='reload-equiv':groups['reload'].append({'kind':k,'uid':e['uid'],'occurrence':e['occurrence']})
        elif k=='reload-cse' and 'mem(' in e.get('pattern',''):groups['reload-cse'].append({'kind':k,'uid':e['uid']})
        elif k=='reload-reuse' and e['value']:
            groups['reload-reuse'].append({'kind':k,'uid':e['uid'],'occurrence':e['occurrence'],'value':0})
        elif k=='reload-noop':groups['reload-noop'].append({'kind':k,'uid':e['uid'],'value':0 if e['value'] else 1})
        elif k=='reorg-fill':groups['reorg'].append({'kind':k,'uid':e['uid'],'candidate_uid':e['candidate_uid'],'value':0 if e['value'] else 1})
        elif k=='reorg-merge':groups['reorg-merge'].append({'kind':k,'uid':e['uid'],'thread_uid':e['thread_uid'],'value':0})
        elif k=='reorg-delete':groups['reorg-delete'].append({'kind':k,'uid':e['uid'],'value':0})
        elif k=='jump-cross' and (e['value'] or e.get('forceable')):
            groups['jump'].append({'kind':k,'uids':e['uids'],'value':0 if e['value'] else 1})
        elif k=='frame-offset':
            step=max(4,abs(e.get('size',0)))
            for delta in (-20,-step,-4,4,step,20):
                groups['frame'].append({'kind':k,'occurrence':e['occurrence'],'value':e['before']+delta})
        elif k=='global-colour' and e['allocno']>=0 and 0<=e['hardreg']<64:
            groups['global-focus' if e['pseudo'] in focus else 'global'].append({'kind':'global-avoid','pseudo':e['pseudo'],'hardreg':e['hardreg']})
    if include_alloc:
        stats=next((s['pseudos'] for s in observation.get('stats',[]) if s['stage']=='before-local'),[])
        for p in stats:
            if p['refs']<=0 or p['life']<=0:continue
            n=p['pseudo'];f='-focus' if n in focus else ''
            if p.get('block',-2)>=0:groups['alloc'+f].append({'kind':'alloc','pseudo':n,'input':{'kind':'global'}})
            for delta in (-1,1,-2,2,-4,4):
                if p['refs']+delta>0:groups['alloc-refs'+f].append({'kind':'alloc','pseudo':n,'input':{'kind':'refs-add','value':delta}})
            for v in (max(1,p['life']//2),p['life']+2,p['life']*2):
                if v!=p['life']:groups['alloc-life'+f].append({'kind':'alloc','pseudo':n,'input':{'kind':'live','value':v}})
            # qty inputs reach the local priority calculation; named pseudo
            # aliases are resolved by the real allocator, absent qtys invalid.
            for delta in (-1,1):
                if p['refs']+delta>0:groups['alloc-qty'+f].append({'kind':'alloc','pseudo':n,'input':{'kind':'qty-refs','value':p['refs']+delta}})
            for v in (p['life']+2,p['life']*2):groups['alloc-qtylife'+f].append({'kind':'alloc','pseudo':n,'input':{'kind':'qty-life','value':v}})
    # Interleave the established cheap decision families with the new families.
    # Keeping all sched/combine/cse candidates behind the (sometimes thousands of)
    # new tier-A sites starves historically validated interventions at small budgets.
    # This is one fair round-robin tier.  A second tier is not safe: any family
    # with thousands of observed sites can hide every member of the next tier
    # beyond a bounded search, including the five historical gate targets.
    tier_a=('cse','sched','combine-class','combine','alias','loop','biv','dead','reload','reload-cse',
            'reorg','reorg-delete','reorg-merge','jump','reload-reuse','reload-noop','frame','cse-head',
            'priority','substitution','luid','global-focus',
            'alloc-focus','alloc-refs-focus','alloc-life-focus','alloc-qty-focus','alloc-qtylife-focus',
            'global','alloc','alloc-refs','alloc-life','alloc-qty','alloc-qtylife')
    seen=set();out=[]
    def add(ch):
        if key(ch) in seen:return
        for c in members(ch):
            if c['kind']=='alloc':alloc_oracle.validate_change(c['input'])
        if isinstance(ch,list) or ch['kind']!='alloc':pass_oracle.validate(ch)
        seen.add(key(ch));out.append(ch)
    for tier in (tier_a,):
        its=[iter(groups[g]) for g in tier]
        for round_ in itertools.zip_longest(*its):
            for ch in round_:
                if ch is not None:add(ch)
    return out

def distance(rec):
    raw=rec.get('raw') or {}
    return raw.get('aligned_distance',10**9) if not rec.get('errors') else 10**9

def composites(trials,baseline,top=6,limit=40):
    """Pairs (and triples of the best three) of distinct single interventions that each
    moved the aligned distance below the baseline; flattened, de-duplicated, bounded."""
    good=[t for t in sorted(trials,key=distance) if distance(t)<baseline and not t.get('raw',{}).get('raw_equal')]
    picked=[];sites=set()
    for t in good:
        k=key(t['change'])
        if k in sites:continue
        sites.add(k);picked.append(t['change'])
        if len(picked)>=top:break
    out=[];seen=set()
    def flat(group):
        ms=[];ks=set()
        for g in group:
            for c in members(g):
                if key(c) not in ks:ks.add(key(c));ms.append(c)
        return ms
    for n in (2,3):
        for group in itertools.combinations(picked if n==2 else picked[:3],n):
            ms=flat(group)
            if not 2<=len(ms)<=pass_oracle.MAX_COMPOSITE:continue
            ms=sorted(ms,key=key)
            if key(ms) in seen:continue
            try:pass_oracle.validate(ms)
            except ValueError:continue
            seen.add(key(ms));out.append(ms)
    return out[:limit]

def rank(rec):
    raw=rec.get('raw')
    return (0 if raw and raw['raw_equal'] else 1,0 if raw and not rec.get('errors') else 1,distance(rec),
            len(members(rec['change'])),raw['word_mismatches'] if raw else 10**9,key(rec['change']))
def trusted_gate(gate):
    rs=gate.get('rows',[])
    return len(rs)==len(KNOWN) and {r['known'] for r in rs}==set(KNOWN) and all(r.get('rediscovered') is True for r in rs)

# Single allocator inputs use the prerequisite alloc_oracle where it is verified;
# other cells (2.7.2, 2.8.0: no alloc_oracle ABI) use pass_oracle's port of the same writes.
ALLOC_ORACLE_CELLS=('2.7.2-cdk','2.6.3')
def cell_of(row):
    kitlib.add_paths();from common import parse_cfg
    return parse_cfg(row['cfg'])[0]
KEEP_SMALL=('out.s','pass_trace.json','oracle_trace.json','pass_cfg.json','oracle_cfg.json','gdb.log','f.c')
def run_trial(row,text,ch,out,timeout):
    # Resumable: a finished (non-timeout) trial for the same change is reused. The
    # enclosing search() has already proven the signature (input/compiler/tools/budget).
    done=out/'trial.json'
    if done.is_file():
        try:old=json.loads(done.read_text())
        except ValueError:old=None
        if old and key(old.get('change'))==key(ch) and not any('Timeout' in e for e in old.get('errors',[])):
            return dict(old,resumed=True)
    start=time.monotonic();out.mkdir(parents=True,exist_ok=True)
    rec={'change':ch,'counterfactual':True,'stageable':False,'errors':[]}
    try:
        if isinstance(ch,dict) and ch['kind']=='alloc' and cell_of(row) in ALLOC_ORACLE_CELLS:
            trace=alloc_oracle.trace(row,text,str(ch['pseudo']),ch['input'],timeout,out/'compiler')
            rec['mutations']=trace['events'];rec['applied']=trace['applied']
        else:
            # No observation families: hooks come from the change kinds alone (fast).
            trace=pass_oracle.trace(row,text,ch,[],timeout,out/'compiler')
            rec['mutations']=trace['mutations'];rec['applied']=trace['applied']
            if isinstance(ch,list):rec['applied_changes']=trace.get('applied_changes',[])
        rec['errors']=trace['errors'];rec['compiler_sha256']=trace['cc1_sha256']
        if not trace['errors']:rec['raw']=pass_oracle.raw_bytes(row,text,trace['asm'],out/'raw')
    except Exception as e:rec['errors'].append(type(e).__name__+': '+str(e))
    rec['seconds']=round(time.monotonic()-start,3)
    if not rec.get('raw',{}).get('raw_equal'):
        # Pass dumps of non-exact trials are large and re-derivable: keep receipts only.
        comp=out/'compiler'
        if comp.is_dir():
            for f in comp.iterdir():
                if f.is_file() and f.name not in KEEP_SMALL:f.unlink()
        raw=out/'raw'
        if raw.is_dir():
            for f in raw.iterdir():
                if f.is_dir():shutil.rmtree(f,ignore_errors=True)
    (out/'trial.json').write_text(json.dumps(rec,indent=2)+'\n')
    return rec

def input_signature(row,text,trials,timeout,composite_budget=0,discovery_hook_cap=None):
    from common import parse_cfg
    cell,_=parse_cfg(row['cfg']);cc=kitlib.ROOT/'toolchain/compilers'/('gcc-'+cell)/'cc1'
    tool_hashes={n:hashlib.sha256(Path(__file__).with_name(n).read_bytes()).hexdigest() for n in ('oracle_search.py','pass_oracle.py','pass_oracle_gdb.py','alloc_oracle.py','alloc_oracle_gdb.py','alloc263_oracle.py')}
    return {'version':VERSION,'row':row['id'],'cfg':row['cfg'],'text_sha256':hashlib.sha256(text.encode()).hexdigest(),
            'compiler_sha256':hashlib.sha256(cc.read_bytes()).hexdigest(),'tools':tool_hashes,'trials':trials,'timeout':timeout,
            'composite_budget':composite_budget,'discovery_hook_cap':discovery_hook_cap}

def discover(row,text,out,timeout,hook_cap=None):
    # Each observer is independently calibrated against plain cc1. Splitting
    # families keeps overlapping debugger return breakpoints out of one run.
    groups=[list(group) for group in pass_oracle.DISCOVERY_GROUPS]
    merged={'events':[],'refs':[],'stats':[],'errors':[],'truncated':False,'discovery_errors':[],
            'hook_counts':{},'skipped_hooks':[],'skipped_sites':[]}
    first=None
    for families in groups:
        tag='_'.join(families);cache=out/(tag+'.observation.json')
        try:
            # Each finished observer (or its failure) is cached, so an interrupted
            # discovery resumes family by family inside the same signed search dir.
            if cache.is_file():
                r=json.loads(cache.read_text())
                if r.get('failed'):raise ValueError(r['failed'])
            else:
                try:r=pass_oracle.trace(row,text,families=families,timeout=timeout,keep=out/tag,hook_cap=hook_cap)
                except Exception as e:
                    out.mkdir(parents=True,exist_ok=True);cache.write_text(json.dumps({'failed':type(e).__name__+': '+str(e)}));raise
                out.mkdir(parents=True,exist_ok=True)
                cache.write_text(json.dumps({k:r.get(k,[] if k in ('events','refs','stats','errors','skipped_hooks','skipped_sites') else {} if k=='hook_counts' else False)
                                                  for k in ('events','refs','stats','errors','truncated','asm','cc1_sha256','hook_counts','skipped_hooks','skipped_sites')}))
            if r['errors']:raise ValueError('; '.join(r['errors']))
            if first is None:first=r;merged['asm']=r['asm'];merged['cc1_sha256']=r['cc1_sha256']
            elif sncheck.normalize(r['asm'])!=sncheck.normalize(first['asm']):raise ValueError('independent observer baselines disagree')
            merged['events'].extend(r['events']);merged['refs'].extend(r['refs']);merged['stats'].extend(r['stats'])
            for name,count in r.get('hook_counts',{}).items():merged['hook_counts'][name]=merged['hook_counts'].get(name,0)+count
            merged['skipped_hooks'].extend(dict(item,families=families) for item in r.get('skipped_hooks',[]))
            merged['skipped_sites'].extend(r.get('skipped_sites',[]))
            merged['truncated']|=r['truncated']
        except Exception as e:merged['discovery_errors'].append({'families':families,'error':type(e).__name__+': '+str(e)})
        finally:
            d=out/tag
            if d.is_dir():
                for f in d.iterdir():
                    if f.is_file() and f.suffix[1:] in kitlib.PASS_SUFFIX and tag!='refs':f.unlink()
    if first is None:raise ValueError('no calibrated family observation completed')
    merged['faithful']=True
    return merged

def extract_function_asm(asm,name):
    """Select one .ent/.end body from a native module compile."""
    lines=asm.splitlines();start=next((i for i,line in enumerate(lines) if re.match(r'^\s*\.ent\s+'+re.escape(name)+r'\s*$',line)),None)
    if start is None:return ''
    end=next((i for i in range(start+1,len(lines)) if re.match(r'^\s*\.end\s+'+re.escape(name)+r'\s*$',lines[i])),None)
    if end is None:return ''
    return '\t.text\n\t.align\t2\n\t.globl\t%s\n'%name+'\n'.join(lines[start:end+1])+'\n'

def pinned_control(row,text,timeout):
    """Compile pinned text, extracting/falling back after a native symbol rename."""
    start=time.monotonic();control=kitlib.dumps(row,text,want=set(),timeout=timeout);method='kitlib.dumps'
    ents=re.findall(r'^\s*\.ent\s+(\S+)',control.get('asm',''),re.M)
    if not control.get('error') and len(ents)>1:
        name=pass_oracle.function_name(text);selected=extract_function_asm(control['asm'],name)
        if selected:control={'asm':selected,'error':None};method='kitlib.dumps native function extraction'
    if control.get('error') or len(re.findall(r'^\s*\.ent\s+\S+',control.get('asm',''),re.M))!=1:
        traced=pass_oracle.trace(row,text,families=[],timeout=timeout)
        control={'asm':traced.get('asm',''),'error':'; '.join(traced.get('errors',[])) or None}
        method='pass_oracle uninjected fallback'
    return control,time.monotonic()-start,method

def run_batch(row,text,changes,out,offset,workers,timeout):
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as pool:
        futures={pool.submit(run_trial,row,text,ch,out/'trials'/('%04d'%(offset+i)),timeout):offset+i for i,ch in enumerate(changes)}
        return [dict(f.result(),index=futures[f]) for f in concurrent.futures.as_completed(futures)]

def search(row,text,out,trials=32,workers=4,timeout=30,resume=True,composite_budget=0,calibration_row=None,discovery_hook_cap=None):
    """Singles (tier A first), then bounded composites of improving singles.
    timeout is a floor: trial timeout = max(timeout, 25 x plain compile), discovery 40 x."""
    out=Path(out).resolve()
    if not out.is_relative_to(kitlib.lane_dir()):raise ValueError('search output must be lane-owned')
    out.mkdir(parents=True,exist_ok=True);(out/'.ignore').write_text('*\n')
    sig=input_signature(row,text,trials,timeout,composite_budget,discovery_hook_cap)
    # A trial cfg (row_at_cfg) is calibrated with the pinned text at the REGISTERED cfg:
    # the pinned text is exact only there; trials still compare with retail bytes.
    crow=calibration_row or row
    if crow is not row:sig['calibration_cfg']=crow['cfg']
    report=out/'report.json';state_p=out/'state.json'
    if resume and report.exists():
        old=json.loads(report.read_text())
        if old.get('signature')!=sig:raise ValueError('stale report: input, compiler, tools or budget changed; choose a new output')
        return old
    state=None
    if resume and state_p.exists():
        state=json.loads(state_p.read_text())
        if state.get('signature')!=sig:raise ValueError('stale partial search: input, compiler, tools or budget changed; choose a new output')
    (out/'input.c').write_text(text)
    rec={'row':row['id'],'cfg':row['cfg'],'signature':sig,'budget':trials,'composite_budget':composite_budget,'workers':workers,'timeout':timeout,
         'discovery_hook_cap':discovery_hook_cap,'trials':[],'exact_interventions':[],'reviewer':'pending','stageable':False,'errors':[],'routing_trusted':False}
    try:
        from common import parse_cfg
        cell,_=parse_cfg(row['cfg'])
        if cell not in pass_oracle.SUPPORTED:raise ValueError('pass discovery unverified for '+cell+'; allocation-only trace can still be run separately')
        STATE=('calibration','calibration_method','trial_timeout','discovery_timeout','baseline','wrong_registers','register_pairs','focus_pseudos',
               'enumerated','discovery_truncated','discovery_errors','discovery_hook_counts','discovery_skipped_hooks','discovery_skipped_sites')
        if state is not None and (out/'space.json').is_file():
            rec.update({k:state[k] for k in STATE});rec['resumed']=True
            space=json.loads((out/'space.json').read_text())
        else:
            control,plain,rec['calibration_method']=pinned_control(crow,kitlib.base_text(crow,kitlib.lane_dir()),max(timeout,120))
            if control.get('error'):raise ValueError('pinned control compile failed: '+str(control['error']))
            rec['calibration']=pass_oracle.raw_bytes(crow,kitlib.base_text(crow,kitlib.lane_dir()),control['asm'],out/'pinned_control')
            if not rec['calibration']['raw_equal']:raise ValueError('pinned raw-byte calibration failed')
            rec['trial_timeout']=round(max(timeout,25*plain),1);rec['discovery_timeout']=round(max(timeout,60*plain,240),1)
            obs=discover(row,text,out/'discovery',rec['discovery_timeout'],discovery_hook_cap)
            if obs['errors']:raise ValueError('discovery failed: '+'; '.join(obs['errors']))
            rec['baseline']=pass_oracle.raw_bytes(row,text,obs['asm'],out/'baseline_raw')
            wrong,pairs=wrong_registers((out/'baseline_raw/forced.bin').read_bytes(),(out/'baseline_raw/retail.bin').read_bytes())
            focus=focus_pseudos(obs,wrong)
            rec['wrong_registers']={str(k):v for k,v in sorted(wrong.items())};rec['register_pairs']=['%d->%d x%d'%(a,b,n) for (a,b),n in pairs.most_common(12)]
            rec['focus_pseudos']=sorted(focus)
            (out/'discovery.json').write_text(json.dumps(pass_oracle.compact(obs),indent=2)+'\n')
            space=enumerate_changes(obs,focus=focus);rec['enumerated']=len(space);rec['discovery_truncated']=obs['truncated'];rec['discovery_errors']=obs['discovery_errors']
            rec['discovery_hook_counts']=obs['hook_counts'];rec['discovery_skipped_hooks']=obs['skipped_hooks'];rec['discovery_skipped_sites']=obs['skipped_sites']
            (out/'space.json').write_text(json.dumps(space)+'\n')
            state_p.write_text(json.dumps(dict({k:rec[k] for k in STATE},signature=sig),indent=2)+'\n')
        if rec['baseline']['raw_equal']:
            rec['status']='input already raw-exact; no compiler change needed'
        else:
            rec['trials']=run_batch(row,text,space[:trials],out,0,workers,rec['trial_timeout'])
            if composite_budget and not any(t.get('raw',{}).get('raw_equal') for t in rec['trials']):
                combo=composites(rec['trials'],rec['baseline']['aligned_distance'],limit=composite_budget)
                rec['composites_enumerated']=len(combo)
                rec['trials']+=run_batch(row,text,combo,out,len(rec['trials']),workers,rec['trial_timeout'])
            rec['trials'].sort(key=rank)
            rec['exact_interventions']=[t['change'] for t in rec['trials'] if t.get('raw',{}).get('raw_equal') and not t['errors']]
            best=rec['trials'][0] if rec['trials'] else None
            if best and distance(best)<10**9:
                rawdir=out/'trials'/('%04d'%best['index'])/'raw';got=rawdir/'forced.bin';retail=rawdir/'retail.bin'
                rec['best']={'change':best['change'],'trial_index':best['index'],'aligned_distance':distance(best),
                             'aligned_word_diff':pass_oracle.aligned_word_diff(got.read_bytes(),retail.read_bytes()) if got.is_file() and retail.is_file() else []}
            else:rec['best']=None
            rec['status']='raw-exact interventions found' if rec['exact_interventions'] else 'none found within budget'
            if rec['discovery_errors']:rec['status']+='; some discovery families held'
            if rec['discovery_skipped_hooks']:rec['status']+='; discovery hook cap left reported tails unobserved'
    except Exception as e:
        rec['errors'].append(type(e).__name__+': '+str(e));rec['status']='held: calibration/discovery unsupported or failed'
    report.write_text(json.dumps(rec,indent=2)+'\n');(out/'report.md').write_text(render(rec))
    return rec

def render(r):
    out=[f"# Minimal compiler change: {r['row']}",f"Status: {r['status']}. Routing trusted: {r['routing_trusted']}.",
         'Input SHA-256: `'+r['signature']['text_sha256']+'`. Counterfactual, reviewer pending.',
         f"Enumerated {r.get('enumerated',0)}; ran {len(r['trials'])} trials (single budget {r['budget']}, composite budget {r.get('composite_budget',0)}); {len(r['exact_interventions'])} raw-exact.",
         f"Baseline aligned distance {(r.get('baseline') or {}).get('aligned_distance','?')}; wrong registers {r.get('wrong_registers',{})}; focus pseudos {r.get('focus_pseudos',[])}."]
    if r.get('discovery_skipped_hooks'):out.append('Discovery caps: `'+json.dumps(r['discovery_skipped_hooks'],sort_keys=True)+'`.')
    if r['errors']:out.extend(r['errors'])
    out+=['','| rank | intervention | size | raw exact | aligned distance | word mismatches | errors |','|---:|---|---:|---|---:|---:|---|']
    for i,t in enumerate(r['trials']):
        raw=t.get('raw',{});out.append('| %d | `%s` | %d | %s | %s | %s | %s |'%(i+1,key(t['change']),len(members(t['change'])),raw.get('raw_equal','unknown'),raw.get('aligned_distance','unknown'),raw.get('word_mismatches','unknown'),'; '.join(t['errors']).replace('|','/')[:300]))
    return '\n'.join(out)+'\n'

def summary_row(r):
    ex=sorted(r['exact_interventions'],key=lambda c:(len(members(c)),key(c)))
    return {'row':r['row'],'cfg':r.get('cfg'),'status':r['status'],'trials':len(r['trials']),'enumerated':r.get('enumerated',0),
            'baseline_aligned_distance':(r.get('baseline') or {}).get('aligned_distance'),'focus_pseudos':r.get('focus_pseudos',[]),
            'exact_interventions':ex,'smallest_exact_size':len(members(ex[0])) if ex else None,'best':r.get('best'),'errors':r['errors']}

def render_all(summary,trusted):
    md=['# Search all pinned rows','',f'Routing trusted: {trusted}. Counterfactual compiler interventions (raw linked bytes vs retail); reviewer pending.','',
        '| row | trials | baseline dist | exact-making interventions (smallest first) | best non-exact (dist) | status |','|---|---:|---:|---|---|---|']
    for r in summary:
        ex='; '.join('`'+key(c)+'`' for c in r['exact_interventions'][:4])+(' (+%d more)'%(len(r['exact_interventions'])-4) if len(r['exact_interventions'])>4 else '')
        best='`%s` (%s)'%(key(r['best']['change']),r['best']['aligned_distance']) if r.get('best') and not r['exact_interventions'] else ''
        md.append('| %s | %d | %s | %s | %s | %s |'%(r['row'],r['trials'],r.get('baseline_aligned_distance'),ex or 'none within budget',best,r['status'].replace('|','/')))
    return '\n'.join(md)+'\n'

def census():
    kitlib.add_paths();from common import rows,clean_path
    out=[]
    for row in rows():
        p=clean_path(row)
        if not p.is_file() or p.stat().st_size>4*1024*1024:continue
        text=p.read_text(errors='replace');sites=kitlib.sites(text)
        if sites:out.append({'row':row['id'],'cfg':row['cfg'],'pins':len(sites),'source':str(p.relative_to(kitlib.ROOT)),
                             'sha256':hashlib.sha256(text.encode()).hexdigest()})
    return sorted(out,key=lambda x:x['row'])

def main(argv=None):
    ap=argparse.ArgumentParser(description=__doc__)
    g=ap.add_mutually_exclusive_group(required=True);g.add_argument('--row');g.add_argument('--all',action='store_true');g.add_argument('--validate',type=Path)
    ap.add_argument('--text',default='erased');ap.add_argument('--out',required=True,type=Path)
    ap.add_argument('--trials',type=int,default=128);ap.add_argument('--composites',type=int,default=24,help='composite trials after singles (0 = off)');ap.add_argument('--workers',type=int,default=4);ap.add_argument('--timeout',type=float,default=30)
    ap.add_argument('--discovery-hook-cap',type=int,default=0,help='per-breakpoint cap during discovery; skipped tails are reported')
    ap.add_argument('--gate',type=Path);ap.add_argument('--cfg',help='--row only: trial cfg; calibration stays at the registered cfg');ap.add_argument('--diagnostic',action='store_true');ap.add_argument('--fresh',action='store_true')
    a=ap.parse_args(argv);lane=kitlib.bootstrap()
    os.nice(10)
    if not 1<=a.workers<=8 or not 1<=a.trials<=10000 or not 1<=a.timeout<=600 or not 0<=a.composites<=500 or not 0<=a.discovery_hook_cap<=100000:ap.error('workers 1..8, trials 1..10000, composites 0..500, timeout 1..600, discovery-hook-cap 0..100000 required')
    hook_cap=a.discovery_hook_cap or None
    out=a.out.resolve()
    if not out.is_relative_to(lane):ap.error('output must be lane-owned')
    out.mkdir(parents=True,exist_ok=True);(out/'.ignore').write_text('*\n')
    gate=json.loads(a.gate.read_text()) if a.gate else {};trusted=trusted_gate(gate)
    if a.all and not trusted and not a.diagnostic:ap.error('five-row gate incomplete; use --diagnostic for evidence only')
    if a.validate:
        entries=json.loads(a.validate.read_text());records=[]
        if {e['known'] for e in entries}!=set(KNOWN) or len(entries)!=len(KNOWN):ap.error('validation requires exactly the five known rows')
        for e in entries:
            row=kitlib.row_of(e['row']);spec=e.get('text','erased')
            if spec not in ('erased','pinned'):spec=str(a.validate.parent/spec)
            text=sncheck.input_text(spec,row,lane);r=search(row,text,out/e['known'],a.trials,a.workers,a.timeout,not a.fresh,a.composites,discovery_hook_cap=hook_cap)
            records.append({'known':e['known'],'row':row['id'],'rediscovered':bool(r['exact_interventions']),
                            'exact_interventions':r['exact_interventions'],'status':r['status'],'errors':r['errors'],'report':str(Path(e['known'])/'report.json')})
            print(e['known'],r['status'],flush=True)
        gate={'version':1,'rows':records,'reviewer':'pending'};gate['trusted']=trusted_gate(gate)
        (out/'validation.json').write_text(json.dumps(gate,indent=2)+'\n')
        (out/'validation.md').write_text('# Validation gate\n\nTrusted: '+str(gate['trusted'])+'\n\n'+ '\n'.join('- '+r['known']+': '+str(r['rediscovered'])+'; '+r['status'] for r in records)+'\n')
        return 0 if gate['trusted'] else 1
    entries=census() if a.all else [{'row':a.row}]
    (out/'census.json').write_text(json.dumps(entries,indent=2)+'\n');summary=[]
    for e in entries:
        row=kitlib.row_of(e['row']);text=sncheck.input_text(a.text,row,lane);crow=None
        if a.cfg and a.row:crow,row=row,kitlib.row_at_cfg(row,a.cfg)
        try:r=search(row,text,out/row['id'].replace('/','__'),a.trials,a.workers,a.timeout,not a.fresh,a.composites,crow,hook_cap)
        except ValueError as exc:
            print(row['id'],'held:',exc,flush=True);summary.append({'row':row['id'],'cfg':row['cfg'],'status':'held: '+str(exc),'trials':0,'exact_interventions':[],'errors':[str(exc)],'best':None});continue
        r['routing_trusted']=trusted;(out/row['id'].replace('/','__')/'report.json').write_text(json.dumps(r,indent=2)+'\n')
        (out/row['id'].replace('/','__')/'report.md').write_text(render(r))
        summary.append(summary_row(r))
        (out/'search_all.json').write_text(json.dumps({'routing_trusted':trusted,'rows':summary},indent=2)+'\n')
        print(row['id'],r['status'],flush=True)
    (out/'search_all.md').write_text(render_all(summary,trusted))
    return 0
if __name__=='__main__':raise SystemExit(main())
