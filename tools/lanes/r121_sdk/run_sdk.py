"""Decision 54 SDK recovery. One mutation runner; original production gates."""
import argparse,collections,copy,csv,functools,gzip,hashlib,json,os,re,subprocess,sys
from pathlib import Path
os.environ.update(TWINS_NO_PACKAGE='1',TWINS_CONTINUE3_ITEM='0',TWINS_WORKERS='4',TWINS_CONTINUATION='sdk')
import twins
from twins import L,R,save,sha,jl
import recover_continue2 as recovery
from function_boundaries import entries,terminal_return

STATE=L/'state/progress.json'

def load(path,default=None):
    return json.loads(path.read_text()) if path.exists() else copy.deepcopy(default)

def targets():
    grouped={};banks={};families=collections.defaultdict(set)
    for item in csv.DictReader((L/'sdk_targets.tsv').open(),delimiter='\t'):
        name=item['window'];container=item['family'].split('_')[0]
        if name not in banks:
            text=(R/'config/overlays'/name).read_text()
            def field(k):return int(re.search(r'\b'+k+r':\s*(0x[\da-fA-F]+)',text)[1],16)
            banks[name]=dict(window=name,container=container,start=field('file_start'),end=field('file_end'),vram=field('vram_start'),spans=[])
        families[item['family']].add(name)
        if not item['foff']:continue
        key=(container,int(item['foff'],0))
        record=grouped.setdefault(key,dict(container=container,foff=key[1],sizes=set(),windows=set(),families=set(),reasons=set()))
        record['sizes'].add(int(item['bytes']));record['windows'].add(name);record['families'].add(item['family']);record['reasons'].add(item['reason'])
    return grouped,banks,families

def excluded():
    grouped=collections.defaultdict(set)
    for item in csv.DictReader((L/'ref/continue3_records/initial_next.tsv').open(),delimiter='\t'):
        if item['foff'] and item['reason'].startswith(('nonrelocation word difference','source score not exact')):
            grouped[item['family'].split('_')[0]].add((int(item['foff'],0),int(item['bytes']),item['reason']))
    return {c:sorted(spans) for c,spans in grouped.items()}

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('action',choices=['plan','apply','publish']);ap.add_argument('--limit-windows',type=int);args=ap.parse_args()
    state=load(STATE,dict(rounds=[],transactions=[],holds={},status='IN PROGRESS'))
    if args.action=='publish':publish(state);return
    world=twins.World();world.twins_at=functools.lru_cache(maxsize=32768)(world.twins_at)
    print('SDK WORLD',len(world.rows),'frozen donors',flush=True)
    from test_decision54 import world_checks
    world_checks(world)
    preflight=load(L/'evidence/preflight/summary.json',dict(windows=[]))
    from preflight_windows import interface_guard
    guard=interface_guard()
    latest={g['window']:True for t in state['transactions'] for b in load(L/t['result'])['banks'] if b['status']=='MATCH' for g in b.get('gates',[]) if g['ok']}
    def immutable_failure(record):
        if not record.get('intrinsic_existing_failure') or record.get('interface_guard')!=guard or latest.get(record['window']) is True:return False
        if sha(R/record['source'])!=record['source_sha256']:return False
        if 'pre-linked bytes' in record['stdout']+record['stderr']:
            row=world.byid.get(record['source'].removeprefix('src/').removesuffix('.c'))
            if not row:return False
            regions=[r for r in world.base_regions[row['container']] if int(r['foff_start'],0)<=row['foff'] and row['foff']+row['size']<=int(r['foff_end'],0)]
            # Solved regions still receive their normal promotion attempt;
            # a starting synthetic-base failure cannot rule that out.
            return len(regions)==1 and regions[0].get('base_confidence')=='proven'
        return True
    blocked_windows={r['window']:r for r in preflight['windows'] if immutable_failure(r)}
    grouped,banks,families=targets();blocked=excluded()
    from entry_scope import bank_windows
    bank_authorities=bank_windows()
    weights=collections.Counter()
    for item in grouped.values():
        for family in item['families']:weights[family]+=max(item['sizes'])
    def bank_order(pair):
        name,bank=pair
        owners=[family for family,names in families.items() if name in names]
        owner=min(owners,key=lambda family:(-weights[family],family))
        return (-weights[owner],owner,bank['start'],name)
    save(L/'evidence/sdk_contracts.json',dict(symbols=world.sdk.report,authorities=world.sdk.authorities))
    save(L/'evidence/excluded_overlap_scope.json',blocked)
    def exclusion(c,o,n,*unused,**kwargs):return any(s<o+n and o<s+size for s,size,reason in blocked.get(c,[]))
    recovery.report_only=exclusion
    recovery.World_for_runner=world
    done_rows=[]
    for t in state['transactions']:
        result=load(L/t['result'])
        done_rows.extend(r for b in result['banks'] for r in b['rows'])
        # A new source-score failure belongs to twins2 after its first normal
        # attempt. Do not grind alternative C or repeat that compiler attempt.
        for hold in result.get('holds',[]):
            if hold.get('foff') and hold['reason']=='source score not exact':
                container=result['banks'][0]['window'].split('_')[0]
                blocked.setdefault(container,[]).append((int(hold['foff'],0),hold['size'],'source score not exact'))
    # The runner requires only this queue inventory; admission always uses our
    # fixed, already-proved plan rather than its historical family discovery.
    save(L/'evidence/families.json',[])
    calls=0
    for round_no in range(len(state['rounds'])+1,100):
        before=sum(r['rows'] for r in state['rounds']);bytes_before=sum(r['bytes'] for r in state['rounds'])
        state['status']='IN PROGRESS'
        recovery.inheritance(world,done_rows)
        plans=[];state['holds']={};needed_windows=set()
        for name,bank in sorted(banks.items(),key=bank_order):
            recovery.live_splits(world);c=bank['container'];proposals=collections.defaultdict(list)
            if name in blocked_windows:
                blocker=blocked_windows[name]
                for (container,o),item in grouped.items():
                    if container==c and name in item['windows']:
                        state['holds'][c+':'+hex(o)]=dict(container=c,foff=o,size=max(item['sizes']),window=name,reason='existing matched source/extent blocks production window',production_blocker=blocker)
                plans.append(dict(window=name,rows=0,bytes=0,holds=1,preflight_existing_failure=True))
                continue
            entry_scopes={}
            for (container,o),item in grouped.items():
                if container!=c or name not in item['windows']:continue
                # Aggregate contract holds are gap spans, often containing
                # many complete functions. Rebuild their saved entry survey;
                # a span's byte count is not a required function size.
                start=max(bank['start'],o);end=min(bank['end'],o+max(item['sizes']))
                start=(start+3)&~3;end&=~3
                if end-start<8:continue
                previous=world.words(c,max(0,start-20),start-max(0,start-20))
                edges=[int(region[key],0) for region in world.base_regions[c] for key in ('foff_start','foff_end')]
                boundaries=entries(world.words(c,start,end-start),start,edges,previous)
                found=False
                for entry,authority in sorted(boundaries.items()):
                    for donor,pr in world.twins_at(c,entry):
                        if entry+donor['size']>end:continue
                        if terminal_return(world.words(c,entry,donor['size'])) is None:continue
                        proposals[entry].append((donor,None));found=True
                        if entry not in entry_scopes or end>entry_scopes[entry]['survey_end']:
                            entry_scopes[entry]=dict(scope_foff=o,scope_size=max(item['sizes']),survey_start=start,survey_end=end,entry_authorities=authority)
                if not found and not recovery.collision(world,c,o,max(item['sizes'])):
                    state['holds'][c+':'+hex(o)]=dict(container=c,foff=o,size=max(item['sizes']),window=name,reason='no complete matched relocation twin at saved offset')
            # Explicit preceding-bank holds authorize bank-chain propagation
            # within these supplied windows. Each link retains a BASE donor.
            is_bank=name in bank_authorities
            if is_bank:
                preceding=bank['start']-0x6000
                placements=[(r,r) for r in world.rows if r['container']==c and preceding<=r.get('foff',-1)<bank['start'] and r['foff']+r['size']<=bank['start']]
                placements += [(r,world.byid[r['template']]) for r in done_rows if r['container']==c and preceding<=r['foff']<bank['start'] and r['foff']+r['size']<=bank['start']]
                for placement,donor in placements:
                    o=placement['foff']+0x6000;n=donor['size']
                    if n<8 or donor.get('row_kind')=='data':continue
                    if o+n>bank['end']:continue
                    pr=twins.proof(world.words(c,placement['foff'],n),world.words(c,o,n))
                    if pr is None:continue
                    proposals[o].append((donor,dict(preceding_bank=preceding,predecessor=placement['id'],predecessor_foff=placement['foff'],predecessor_size=n,canonical_template=donor['id'],predecessor_source_sha256=placement.get('source_sha256'),relocation_proof=pr)))
            rows=[];holds=[];occupied=[]
            for o,options in sorted(proposals.items()):
                options=sorted(options,key=lambda opt:(opt[1] is None,opt[0]['container']!=c,abs(opt[0]['foff']-(o-0x6000)),-opt[0]['size'],opt[0]['id']))
                seen=set();failures=[]
                for donor,chain in options:
                    n=donor['size']
                    if donor['id'] in seen:continue
                    seen.add(donor['id'])
                    if recovery.collision(world,c,o,n):continue
                    if any(s<o+n and o<s+z for s,z in occupied):continue
                    if exclusion(c,o,n):
                        failures.append(dict(template=donor['id'],reason='overlaps twins2 source-score/nonrelocation scope'));break
                    try:
                        if chain is None:
                            tail=terminal_return(world.words(c,o,n))
                            ctx=recovery.context(world,bank,o,n)
                            authority=entry_scopes.get(o,{}).get('entry_authorities')
                            if not authority or tail is None:raise ValueError('saved target lacks independent complete entry/terminal boundary')
                        row=recovery.candidate(world,bank,donor,o)
                        from common import covering_windows
                        required={name}|{w[0] for w in covering_windows(c,o,n)}
                        needed_windows.update(required)
                        unavailable=sorted(required & blocked_windows.keys())
                        if unavailable:raise ValueError('existing matched source/extent blocks covering production window: '+unavailable[0])
                        if chain:
                            row['bank_chain']=chain
                            row['bank_family_authority']=bank_authorities[name]
                        else:row['sdk_target_entry']=dict(input='work/native_lane/r121_sdk/sdk_targets.tsv',foff=o,size=n,**entry_scopes[o],terminal_return_word=tail)
                        rows.append(row);occupied.append((o,n));break
                    except (ValueError,KeyError) as error:
                        failures.append(dict(template=donor['id'],reason=str(error),details=getattr(error,'details',None)))
                if failures and not any(r['foff']==o for r in rows):
                    h=dict(container=c,foff=o,size=options[0][0]['size'],window=name,reason=failures[0]['reason'],failures=failures)
                    holds.append(h);state['holds'][c+':'+hex(o)]=h
            plans.append(dict(window=name,rows=len(rows),bytes=sum(r['size'] for r in rows),holds=len(holds)))
            if rows:
                print('SDK PLAN',round_no,name,len(rows),sum(r['size'] for r in rows),flush=True)
                if args.action=='apply':
                    key=hashlib.sha256(json.dumps([(r['id'],r['template'],sha(L/r['src'])) for r in rows]).encode()).hexdigest()[:12]
                    transaction=f'sdk_r1_{bank["container"]}_{bank["start"]:x}_{key}'
                    d=L/'evidence'/transaction;d.mkdir(exist_ok=True)
                    result_path=d/'result.json'
                    if not result_path.exists():
                        stub=dict(id=transaction,kind='single-window',banks=[bank]);original=twins.plan
                        def fixed(*unused):
                            save(d/'plan.json',rows);save(d/'holds.json',holds);return copy.deepcopy(rows)
                        twins.plan=fixed
                        try:twins.run(stub,world)
                        finally:twins.plan=original
                    result=load(result_path)
                    admitted=[r for b in result['banks'] for r in b['rows']]
                    old_ids={r['id'] for r in done_rows}
                    done_rows.extend(r for r in admitted if r['id'] not in old_ids)
                    if not any(t['result']==str(result_path.relative_to(L)) for t in state['transactions']):state['transactions'].append(dict(round=round_no,result=str(result_path.relative_to(L))))
                    for h in result['holds']:
                        if h.get('foff'):
                            o2=int(str(h['foff']),0);state['holds'][c+':'+hex(o2)]=dict(h,container=c,foff=o2)
                    for b in result['banks']:
                        if b['status']=='HOLD' and b.get('reason'):
                            for row in rows:
                                if row['id'] not in {r['id'] for r in admitted} and c+':'+hex(row['foff']) not in state['holds']:
                                    state['holds'][c+':'+hex(row['foff'])]=dict(container=c,foff=row['foff'],size=row['size'],window=name,reason=b['reason'])
                    save(STATE,state);calls+=1
                    print('SDK ADMITTED',len(admitted),sum(r['size'] for r in admitted),flush=True)
                    if calls%4==0:
                        publish(state,world)
                    if (L/'state/STOP_AFTER_TRANSACTION').exists():
                        state['status']='PARTIAL';save(STATE,state);publish(state,world);return
                    if args.limit_windows and calls>=args.limit_windows:
                        state['status']='PARTIAL';save(STATE,state);publish(state,world);return
        save(L/'evidence'/f'round{round_no}_plans.json',plans)
        save(L/'evidence/planned_production_windows.json',dict(windows=sorted(needed_windows)))
        record=dict(round=round_no,rows=len(done_rows)-before,bytes=sum(r['size'] for r in done_rows)-bytes_before,planned_rows=sum(p['rows'] for p in plans))
        if args.action=='plan':
            print('SDK PLAN SUMMARY',record,'required windows',len(needed_windows),flush=True);return
        state['rounds'].append(record);save(STATE,state)
        print('SDK ROUND',record,flush=True)
        publish(state,world)
        if not record['rows']:
            state['status']='FIXED POINT';save(STATE,state);publish(state,world);return


def publish(state,world=None):
    # Imported lazily so the mutation runner and packaging stay sequential.
    from publish_sdk import publish
    publish(state,world)

if __name__=='__main__':main()
