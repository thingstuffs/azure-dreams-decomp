#!/usr/bin/env python3
"""Observed loop-weighted reference contributions, with guarded source attribution.

Reads actual reg_n_refs deltas around the outermost flow mark_set_regs and
mark_used_regs calls. Recursion is aggregated, not double-counted. Reports the
unattributed residual against the allocator's observed total. A -g twin supplies
source notes only where UID AND RTL match and machine instructions are unchanged.
"""
import argparse,collections,json
from pathlib import Path
import kitlib,sncheck,pass_oracle,value_luid

def build(row,text,trace,source=True):
    src,note=value_luid.source_twin(row,text,dict(trace['dumps'],asm=trace['asm'])) if source else ({},'source disabled')
    flow={r['uid']:r for r in value_luid.records(trace['dumps'].get('flow',''))}
    by=collections.defaultdict(list)
    for hit in trace['refs']:
        rec=dict(hit);loc=src.get(('flow',hit['uid']))
        rec['source']=loc
        if loc and loc['file']=='f.c' and 0<loc['line']<=len(text.splitlines()):
            rec['statement']=text.splitlines()[loc['line']-1].strip()
        rec['pattern']=flow.get(hit['uid'],{}).get('pattern')
        by[hit['pseudo']].append(rec)
    stats=next((s['pseudos'] for s in trace['stats'] if s['stage']=='before-local'),[])
    out=[]
    for s in stats:
        refs=by[s['pseudo']];total=sum(x['weight'] for x in refs)
        out.append(dict(s,contributions=refs,mapped_weight=total,unattributed_weight=s['refs']-total,
                        source_weight=sum(x['weight'] for x in refs if x['source']),
                        priority=int((s['refs'].bit_length()-1)*s['refs']*10000/s['life']) if s['life']>0 else None))
    return {'row':row['id'],'cfg':row['cfg'],'source_evidence':note,'pseudos':out,
            'life_evidence':'actual reg_live_length after sched1, before local_alloc',
            'weights_evidence':'actual outer flow-call reg_n_refs deltas (includes set references)',
            'reviewer':'pending','counterfactual':False}

def query(view,pseudo,fewer=None,life=None):
    p=next((p for p in view['pseudos'] if p['pseudo']==pseudo),None)
    if p is None:raise ValueError('pseudo is not live at allocator entry')
    if fewer is not None and (type(fewer) is not int or not 0<fewer<p['refs']):raise ValueError('fewer-refs must leave a positive reference count')
    if life is not None and (type(life) is not int or life<=0):raise ValueError('life-at-least must be positive')
    grouped={}
    for c in p['contributions']:
        loc=c['source']
        if not loc:continue
        k=(loc['file'],loc['line'])
        g=grouped.setdefault(k,{'source':loc,'weight':0,'uids':[],'statement':c.get('statement')})
        g['weight']+=c['weight'];g['uids'].append(c['uid'])
    sites=sorted(grouped.values(),key=lambda s:(abs(s['weight']-(fewer or 1)),s['source']['line']))
    return {'pseudo':pseudo,'observed_refs':p['refs'],'observed_life':p['life'],
            'refs_goal':p['refs']-fewer if fewer is not None else None,'life_goal':life,
            'counted_source_sites':sites,
            'life_sites':[c for c in p['contributions'] if c['source']],
            'interpretation':'Weights are observed counted refs, including sets. Source sites identify carrier computations to re-express; a source edit must be recompiled. Life is the observed scheduler total, not a source-line span.'}

def render(r):
    out=[f"# Source refs: {r['row']}",r['source_evidence'],
         'Life is observed after sched1. Edit suggestions identify counted sites; a source edit still needs a fresh compile.',
         '| pseudo | refs | life | mapped weight | residual | source sites |',
         '|---|---:|---:|---:|---:|---|']
    for p in r['pseudos']:
        sites=', '.join('L%d (+%d)'%(c['source']['line'],c['weight']) for c in p['contributions'] if c['source']) or 'unknown'
        out.append('| p%d | %d | %d | %d | %d | %s |'%(p['pseudo'],p['refs'],p['life'],p['mapped_weight'],p['unattributed_weight'],sites))
    if 'query' in r:
        q=r['query'];out+=['', 'Requested p%d: refs %d -> %s; life %d -> at least %s.'%(q['pseudo'],q['observed_refs'],q['refs_goal'],q['observed_life'],q['life_goal']),q['interpretation']]
        for s in q['counted_source_sites']:out.append('L%d: weight %d, UIDs %s: %s'%(s['source']['line'],s['weight'],','.join(map(str,s['uids'])),s['statement'] or 'statement unknown'))
    return '\n'.join(out)+'\n'
def main(argv=None):
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('row');ap.add_argument('text');ap.add_argument('--out',required=True,type=Path)
    ap.add_argument('--no-source',action='store_true');ap.add_argument('--timeout',type=float,default=60)
    ap.add_argument('--pseudo',type=int);ap.add_argument('--fewer-refs',type=int);ap.add_argument('--life-at-least',type=int)
    a=ap.parse_args(argv);lane=kitlib.bootstrap();row=kitlib.row_of(a.row);text=sncheck.input_text(a.text,row,lane)
    a.out.mkdir(parents=True,exist_ok=True)
    t=pass_oracle.trace(row,text,families=['refs'],timeout=a.timeout,keep=a.out/'trace')
    if t['errors']:ap.exit(2,'; '.join(t['errors'])+'\n')
    r=build(row,text,t,not a.no_source)
    if a.fewer_refs is not None or a.life_at_least is not None:
        if a.pseudo is None:ap.error('reference/life goals need --pseudo NUMBER')
    if a.pseudo is not None:r['query']=query(r,a.pseudo,a.fewer_refs,a.life_at_least)
    (a.out/'refs.json').write_text(json.dumps(r,indent=2)+'\n');(a.out/'refs.md').write_text(render(r));print(render(r))
    return 0
if __name__=='__main__':raise SystemExit(main())
