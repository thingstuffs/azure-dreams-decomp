"""Value definitions, pass history, source statements and observed scheduler LUIDs.

UIDs are tracked only WITHIN a compile. Each side resolves its own named pseudo
and call independently. Pass attribution is an observed transition, not a claim
about a particular internal optimizer routine. Source notes come from a -g twin:
its instruction listing must match, and each annotated UID+pattern must match.
"""
from __future__ import annotations
import difflib
import json
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import kitlib
import sncheck

PASSES=('rtl','jump','cse','loop','cse2','flow','combine','sched','lreg','greg','sched2','jump2','dbr')
HEAD=re.compile(r'^\((note|insn|jump_insn|call_insn|code_label|barrier)(?:[/:]\w+)*\s+(\d+)\s+[-\d]+\s+[-\d]+\s+',re.M)
SET=re.compile(r'\(set\s+\(reg(?:/\w+)*:\w+ (\d+)(?: \w+)?\)')
REG=re.compile(r'^\(reg(?:/\w+)*:\w+ (\d+)(?: \w+)?\)$')
CALL=re.compile(r'\(symbol_ref(?::\w+)? \("([^\"]+)"\)\)')
HARD_NAMES={'a0':4,'a1':5,'a2':6,'a3':7,'v0':2,'v1':3}

def records(dump):
    kitlib.add_paths(); from sched_trace import close_paren
    out=[];source=None
    for m in HEAD.finditer(dump):
        end=close_paren(dump,m.start())
        if end is None: continue
        raw=dump[m.start():end];pat=''
        if m[1]=='note':
            match=re.match(r'\(?"([^\"]+)"\)?\s+(\d+)\)',dump[m.end():end])
            if match: source={'file':match[1],'line':int(match[2])}
        elif dump[m.end():m.end()+1]=='(':
            stop=close_paren(dump,m.end());pat=re.sub(r'\s+',' ',dump[m.end():stop]) if stop else ''
        out.append({'uid':int(m[2]),'kind':m[1],'pattern':pat,'raw':raw,'source':dict(source) if source else None,'chain_rank':len(out)})
    return out

def defining_set(record,reg):
    """Return the SET source for this register; parallel/asm outputs are allowed."""
    kitlib.add_paths(); from sched_trace import close_paren
    pattern=record['pattern']
    for m in SET.finditer(pattern):
        if int(m[1])==reg:
            start=m.end()
            while start<len(pattern) and pattern[start].isspace(): start+=1
            end=close_paren(pattern,start)
            if end: return pattern[start:end]
    return None

def select_call(recs,spec=None,occurrence=1):
    calls=[r for r in recs if r['kind']=='call_insn']
    if spec:
        if re.fullmatch(r'u?\d+',str(spec)): calls=[r for r in calls if r['uid']==int(str(spec).lstrip('u'))]
        else: calls=[r for r in calls if spec in CALL.findall(r['pattern'])]
    if not 1<=occurrence<=len(calls): raise ValueError('call selection has %d matches, occurrence %d requested' % (len(calls),occurrence))
    return calls[occurrence-1]

def definitions(recs,reg,call=None):
    before=recs[:recs.index(call)] if call else recs
    hits=[]
    for r in reversed(before):
        if call and r['kind'] in ('code_label','jump_insn','call_insn'):
            break
        src=defining_set(r,reg)
        if src:
            # An a0=a0 argument USE-copy does not create a value.
            copy=REG.fullmatch(src)
            if not copy or int(copy[1])!=reg: hits.append(r)
            if call and hits: break
    return list(reversed(hits))

def transitions(dumps,uid):
    """Stable UID/pattern history: classify only what adjacent dump snapshots prove."""
    hist=[];previous=None
    for phase in PASSES:
        if phase not in dumps: continue
        chain=records(dumps[phase]);hit=next((r for r in chain if r['uid']==uid and r['kind'] in ('insn','jump_insn','call_insn')),None)
        if hit:
            if previous is None:
                event='present in initial RTL' if phase=='rtl' else 'first observed at '+phase
            elif hit['pattern']!=previous['pattern']:
                event={'cse':'cse substitution/rewrite','cse2':'cse2 substitution/rewrite','combine':'combine merge/rewrite',
                       'loop':'loop.c substitution/rewrite'}.get(phase,phase+' pattern rewrite')
            else: event='survives'
            # Relative order of surviving insns, not ranks shifted by deletions.
            prev_phase=hist[-1]['pass'] if hist else None
            if previous and prev_phase:
                old=records(dumps[prev_phase]); old_order=[r['uid'] for r in old if r['kind'] in ('insn','jump_insn','call_insn')]
                new_order=[r['uid'] for r in chain if r['kind'] in ('insn','jump_insn','call_insn')]
                common=set(old_order)&set(new_order);o=[u for u in old_order if u in common];n=[u for u in new_order if u in common]
                if uid in common and o.index(uid)!=n.index(uid): event+='; relative chain order moved at '+phase
            hist.append({'pass':phase,'uid':uid,'pattern':hit['pattern'],'chain_rank':hit['chain_rank'],'event':event});previous=hit
        elif previous:
            hist.append({'pass':phase,'uid':uid,'event':'removed or UID replaced at '+phase,'pattern':None});previous=None
    return hist

def source_twin(row,text,dumps,timeout=120):
    """Read -g line notes; never call unmatched debug UIDs production source lines."""
    with tempfile.TemporaryDirectory(prefix='luid_source_') as td:
        d=Path(td);cc,flags,_=sncheck.preprocess(row,text,d)
        run=subprocess.run([str(cc/'cc1'),'in.i','-quiet','-O2',*flags,'-w','-g','-da','-o','debug.s'],cwd=d,capture_output=True,text=True,timeout=timeout)
        if run.returncode: return {},'source-note compile failed: '+run.stderr[-500:]
        def machine(s):
            return [re.sub(r'\s+',' ',l.split('#')[0].strip()) for l in s.splitlines()
                    if re.match(r'^\s+[a-z][a-z0-9]*\s',l) and l.split('#')[0].strip()]
        if machine(dumps['asm'])!=machine((d/'debug.s').read_text()): return {},'source-note twin changes instructions; no source attribution'
        sources={}
        for f in d.iterdir():
            phase=f.suffix[1:]
            if phase not in dumps: continue
            twin_dump=f.read_text(errors='replace')
            if dumps.get('_function'):twin_dump=function_dumps({phase:twin_dump},dumps['_function'])[phase]
            debug={r['uid']:r for r in records(twin_dump)}
            for r in records(dumps[phase]):
                twin=debug.get(r['uid'])
                if twin and twin['pattern']==r['pattern'] and twin['source']:
                    sources[(phase,r['uid'])]=twin['source']
        return sources,'instruction-identical -g twin; source assigned only to matching UID+pattern'

def main_function_name(row,text,first):
    import alloc_sim
    dp=alloc_sim.decl_pseudos(text,first)
    if dp: return dp['fname']
    names=[f[0] for f in alloc_sim.functions(text)]
    for token in (row.get('true_name'),row.get('func')):
        if token in names:return token
    raise ValueError('cannot select the row function among helpers; use a single-function candidate')

def function_dumps(dumps,name):
    out=dict(dumps)
    for phase in PASSES:
        src=dumps.get(phase)
        if not src:continue
        heads=list(re.finditer(r'^;; Function (\S+)',src,re.M))
        for i,m in enumerate(heads):
            if m[1]==name:
                out[phase]=src[m.start():heads[i+1].start() if i+1<len(heads) else len(src)]
                break
    out['_function']=name
    return out

def observe_luids(row,text,timeout=180):
    """Exact numbers from sched.c, rather than an insn-only approximation of LUID."""
    kitlib.add_paths();from common import parse_cfg
    import alloc_sim,prefs_gdb
    cell,_=parse_cfg(row['cfg'])
    if cell not in ('2.7.2-cdk','2.8.0','2.8.1'): return {'blocks':[],'errors':['exact LUID observer requires cdk/2.8.x i386 cc1']}
    try:fname=main_function_name(row,text,alloc_sim.FIRST[cell])
    except ValueError as e:return {'blocks':[],'errors':[str(e)]}
    with tempfile.TemporaryDirectory(prefix='luid_gdb_') as td:
        d=Path(td);cc,flags,_=sncheck.preprocess(row,text,d);a=prefs_gdb.symbols(cc/'cc1')
        if not all(n in a for n in ('sched_analyze','insn_luid','reload_completed','current_function_name','expand_decl','make_decl_rtl','assign_parms','tree_code_name','rtx_name','current_function_decl')): return {'blocks':[],'errors':['missing scheduler symbols']}
        (d/'luid_cfg.json').write_text(json.dumps({'addresses':a,'function':fname}))
        shutil.copy2(Path(__file__).with_name('value_luid_gdb.py'),d/'trace.py')
        (d/'trace.gdb').write_text('set pagination off\nset confirm off\nset debuginfod enabled off\nset startup-with-shell off\nsource trace.py\n')
        run=subprocess.run(['gdb','--batch','--nx','-x','trace.gdb','--args',str(cc/'cc1'),'in.i','-quiet','-O2',*flags,'-w','-da','-o','out.s'],cwd=d,capture_output=True,text=True,timeout=timeout)
        if not (d/'luid_trace.json').exists(): return {'blocks':[],'errors':['GDB failed: '+(run.stdout+run.stderr)[-500:]]}
        res=json.loads((d/'luid_trace.json').read_text());res['function']=fname
        if run.returncode or res.get('inferior_exit')!=0: res['errors'].append('LUID observer compiler failed')
        return res

def declaration_registers(observation):
    """Latest DECL_RTL per tree node, then reject genuinely shadowed names.

    A register declaration initially has a pseudo, then make_decl_rtl can bind
    that SAME node to a hard reg. That transition is not a shadowed declaration.
    """
    nodes={}
    for i,decl in enumerate(observation.get('declarations',[])):
        nodes[decl.get('decl_uid',decl.get('decl_address',i))]=decl
    names={}
    for decl in nodes.values():names.setdefault(decl['name'],set()).add(decl['register'])
    return {name:next(iter(regs)) for name,regs in names.items() if len(regs)==1}, {name for name,regs in names.items() if len(regs)>1}

def value_view(row,text,dumps,token,call=None,occurrence=1,phase='sched',source=True,observe=True):
    kitlib.add_paths(); import alloc_sim
    from common import parse_cfg
    cell,_=parse_cfg(row['cfg']);first=alloc_sim.FIRST[cell];dp=alloc_sim.decl_pseudos(text,first)
    mapping=(dp or {}).get('map',{})
    # A named register variable is already a HARD reg, not decl_pseudos' placeholder.
    mapping=dict(mapping)
    for name, hard in re.findall(r'\b(\w+)\s+ASM_REG\(\s*"\$?(\w+)"\s*\)',text):
        actual=int(hard) if hard.isdigit() else {n.lstrip('$'):i for i,n in enumerate(alloc_sim.GPR)}.get(hard)
        if actual is not None: mapping[name]=actual
    luids=observe_luids(row,text) if observe else {'blocks':[],'errors':['observer disabled']}
    resolution='explicit register' if token.lstrip('$').isdigit() or token.lstrip('$') in HARD_NAMES else 'declaration-order estimate (observer unavailable)'
    observed,ambiguous=declaration_registers(luids)
    if token in ambiguous: raise ValueError('ambiguous shadowed declaration '+token+'; select a numeric pseudo')
    if token in observed:
        actual=observed[token]
        if actual is None: raise ValueError('named declaration is in memory, not a register: '+token)
        mapping[token]=actual;resolution='observed DECL_RTL in cc1'
    t=token.lstrip('$');reg=int(t) if t.isdigit() else HARD_NAMES.get(t,mapping.get(t))
    if observe and resolution.startswith('declaration-order'):
        raise ValueError('named declaration was not observed by cc1; use a numeric pseudo or inspect the GDB error: '+token)
    if reg is None: raise ValueError('no named pseudo or argument register '+token)
    if luids.get('function'): dumps=function_dumps(dumps,luids['function'])
    if phase not in dumps: raise ValueError('missing .'+phase+' dump')
    recs=records(dumps[phase]);chosen=None
    if call or reg in (4,5,6,7):
        if call: chosen=select_call(recs,call,occurrence)
        else:
            calls=[r for r in recs if r['kind']=='call_insn' and definitions(recs,reg,r)]
            if not 1<=occurrence<=len(calls): raise ValueError('no call in a straight-line block with a definition of '+token)
            chosen=calls[occurrence-1]
    defs=definitions(recs,reg,chosen)
    eliminated=False
    if not defs and reg>=first and 'rtl' in dumps:
        defs=definitions(records(dumps['rtl']),reg)
        eliminated=bool(defs)
    srcs,note=source_twin(row,text,dumps) if source else ({},'source notes disabled')
    out={'token':token,'register':reg,'resolution_evidence':resolution,'phase':phase,'call':{'uid':chosen['uid'],'pattern':chosen['pattern']} if chosen else None,
         'definitions':[],'eliminated_pseudo':eliminated,'source_evidence':note,'luid_errors':luids['errors']}
    # Dynamic boost is read from actual ready-list priorities, separate from source attribution.
    import sched_trace
    blocks=sched_trace.block_traces(dumps[phase]) if phase in ('sched','sched2') else []
    for r in defs:
        uid=r['uid'];history=transitions(dumps,uid)
        src=next((srcs.get((h['pass'],uid)) for h in history if srcs.get((h['pass'],uid))),None)
        if src and 1<=src['line']<=len(text.splitlines()): src=dict(src,statement=text.splitlines()[src['line']-1].strip())
        hit=next(((b,x) for b in luids['blocks'] if b['phase']==phase for x in b['insns'] if x['uid']==uid),None)
        boost=any(prio & 0x7f000000 for b in blocks for tick in b['ticks'] for u,prio in tick['ready'] if u==uid) if phase=='sched' else False
        out['definitions'].append({'uid':uid,'pattern':r['pattern'],'source':src,'history':history,
             'luid':hit[1]['luid'] if hit else None,'luid_block':{'from':hit[0]['from'],'to':hit[0]['to']} if hit else None,
             'scheduler_boost_observed':boost})
    if not defs: out['unresolved']='no unique definition in this straight-line block; inspect predecessors or select a named pseudo'
    return out

def render(view,label):
    out=['# value-LUID '+label+': '+view['token']+' -> reg '+str(view['register'])]
    out.append('register resolution: '+view.get('resolution_evidence','unknown'))
    if view['call']: out.append('call uid %d: %s' % (view['call']['uid'],view['call']['pattern']))
    out.append('source evidence: '+view['source_evidence'])
    if view['luid_errors']: out.append('LUID observation unavailable: '+'; '.join(view['luid_errors']))
    if view.get('unresolved'): out.append(view['unresolved'])
    if view.get('eliminated_pseudo'): out.append('pseudo has no surviving definition at '+view['phase']+'; showing initial RTL definitions and their removal history')
    for d in view['definitions']:
        out.append('DEFINE uid %d, LUID %s, block %s: %s' % (d['uid'],d['luid'] if d['luid'] is not None else '?',d['luid_block'],d['pattern']))
        s=d['source'];out.append('source L%d: %s' % (s['line'],s.get('statement','')) if s else 'source statement unknown (no matching source note)')
        for h in d['history']:
            if h['event']!='survives': out.append('  '+h['pass']+': '+h['event']+(' | '+h['pattern'] if h['pattern'] else ''))
        if d['scheduler_boost_observed']: out.append('  sched: birthing boost observed on ready list (LAUNCH priority)')
    return out
