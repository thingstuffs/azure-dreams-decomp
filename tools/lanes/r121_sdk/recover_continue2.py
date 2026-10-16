"""Continuation 2: fixed-point bank and contract recovery through production gates.

Discovery may use an admitted row's placement, but generated C and ABI contracts
always name the original matched BASE body. Thus chain depth cannot weaken the
complete unmasked relocation proof or create a new runtime contract.
"""
import argparse
import collections
import copy
import csv
import functools
import hashlib
import itertools
import json
import os
import re
import sys
from pathlib import Path

os.environ['TWINS_NO_PACKAGE'] = '1'
os.environ.setdefault('TWINS_WORKERS', '6')
sys.dont_write_bytecode = True
import twins
import single_plan
import recover_bank_anchors as transactions
from contracts import bind, declaration

L, R, BASE = twins.L, twins.R, twins.BASE
OUT = L / ('evidence/'+os.environ.get('TWINS_CONTINUATION','continue2'))
OUT.mkdir(exist_ok=True)
(OUT / '.ignore').write_text('*\n')


def admitted_rows():
    return [r for f in twins.load_families()
            for b in json.loads((L/'evidence'/f['id']/'result.json').read_text())['banks']
            if b['status'] == 'MATCH' for r in b['rows']]


@functools.lru_cache(maxsize=1)
def report_only_scope():
    path=twins.HOME_LANE/'evidence/continue2/report_only_scope.json'
    return json.loads(path.read_text())['spans'] if path.exists() else []


def report_only(c,o,n,item=None):
    item=str(item) if item is not None else os.environ.get('TWINS_CONTINUE3_ITEM')
    reopened_source=item in ('1','2') and any(span['container']==c and span['reason']=='source score not exact'
        and span['foff']<=o<span['foff']+span['size'] for span in report_only_scope())
    for span in report_only_scope():
        if span['container']!=c:continue
        if reopened_source and span['reason'] in ('source score not exact','nonrelocation word difference'):continue
        if item in ('1','2') and span['reason']=='source score not exact':continue
        if item=='2' and span['reason']=='nonrelocation word difference':continue
        if span['reason']=='census_no_whole_body_twin':
            if reopened_source:continue
            if span['foff']<o+n and o<span['foff']+span['size']:return True
        elif (o,n)==(span['foff'],span['size']):return True
    return False


def measure(label):
    """Run the requested tool, plus a census supplement for absent coverage ledger."""
    # Family workers share the class baseline. The cumulative owner measures
    # before/after once; repeating the whole hold-union census per private
    # family adds no admission evidence and only consumes shared-disk time.
    if os.environ.get('TWINS_FAMILIES'):return {}
    if label.endswith('_before') and (OUT/(label+'_remaining.json')).exists() and (OUT/(label+'_census_remaining.json')).exists():
        return json.loads((OUT/(label+'_census_remaining.json')).read_text())
    for suffix, root, fallback in [('', R, BASE), ('_census', OUT/'remaining_view', R)]:
        if suffix:
            root.mkdir(exist_ok=True)
            (root/'ledger').mkdir(exist_ok=True)
            if not (root/'config').exists():
                (root/'config').symlink_to(R/'config', target_is_directory=True)
            census = list(csv.DictReader((L/'refs/prev/twin_census.tsv').open(), delimiter='\t'))
            gaps = {(x['container'], int(x['foff'],0), int(x['bytes'])) for x in census
                    if x['classification'] == 'untyped_gap'}
            (root/'ledger/coverage_regions.jsonl').write_text(''.join(json.dumps(dict(
                container=c,foff=o,size=n,category='unported',active=True,
                evidence='refs/prev/twin_census.tsv'))+'\n' for c,o,n in sorted(gaps)))
        output = OUT / (label+suffix+'_remaining.json')
        p = twins.command([sys.executable,L/'scripts/remaining.py','--root',root,
            '--fallback-root',fallback,'--holds',L/'next.tsv','--json','--out',output],cwd=L)
        assert p.returncode == 0, p.stderr
    return json.loads((OUT/(label+'_census_remaining.json')).read_text())


@functools.lru_cache(maxsize=32768)
def regions(world, c, o, n):
    return [x for x in world.base_regions[c]
            if int(x['foff_start'],0)<=o and o+n<=int(x['foff_end'],0)
            and x.get('base_confidence') in ('proven','solved')]


def context(world, bank, o, n):
    hits=regions(world,bank['container'],o,n)
    if len(hits)!=1:
        raise ValueError('entry_no_unique_complete_existing_rowbase')
    rb=hits[0];delta=int(rb['delta'],0)
    # A text window may crop a valid callee from the same established bank.
    # Use the complete existing rowbase region for import proofs first.
    start,end=int(rb['foff_start'],0),int(rb['foff_end'],0)
    vram=start+delta;basis='existing-rowbase-region'
    return dict(start=start,end=end,vram=vram,delta=delta,region=rb['region'],basis=basis)


def candidate(world, bank, donor, target, evidence=None, _context=None):
    c=bank['container'];n=donor['size']
    if report_only(c,target,n):raise ValueError('report_only_continue2_class4')
    incoming=getattr(world,'incoming_contracts',{}).get((c,target),[])
    if incoming:
        definitions=world.byrow.get(donor['id'],[])
        if len(definitions)!=1:raise ValueError('incoming ABI requires one complete matched definition')
        own=declaration(definitions[0],'callee')
        from prototype_variants import compatible
        if any(not compatible(call['contract'],definitions[0]) for call in incoming):
            raise ValueError('matched incoming calls require another complete donor prototype')
    ctx=_context or context(world,bank,target,n)
    if target<bank['start'] or target+n>bank['end']:
        raise ValueError('complete_body_exceeds_window')
    text,pr,mp=world.generate(donor,c,target,n,target+ctx['delta'])
    oldrefs=twins.references(world.words(donor['container'],donor['foff'],n))[0]
    newrefs=twins.references(world.words(c,target,n))[0]
    source_regions=regions(world,donor['container'],donor['foff'],n)
    true_name=donor.get('true_name')
    if true_name:source_vram=int(true_name[5:],16)
    elif len(source_regions)==1:
        source_vram=donor['foff']+int(source_regions[0]['delta'],0)
    else:
        definitions=world.byrow.get(donor['id'],[])
        if len(definitions)!=1:raise ValueError('donor_has_no_true_link_identity')
        name=definitions[0]['name']
        source_vram=int(name[5:],16) if re.fullmatch(r'func_[\dA-Fa-f]{8}',name) else world.alias.get(name)
        if source_vram is None:raise ValueError('donor_has_no_true_link_identity')
    calls=[];unresolved=[]
    for i,ref in oldrefs.items():
        if ref['kind']!='jal' and not (ref['kind']=='j' and not source_vram<=ref['address']<source_vram+n):
            continue
        old=ref['address'];new=newrefs[i]['address']
        contract=None
        if len(source_regions)==1:
            rb=source_regions[0];s=int(rb['foff_start'],0);e=int(rb['foff_end'],0)
            contract=world.contract(donor['container'],old,s,s+int(rb['delta'],0),e-s)
        if not contract:
            contract=single_plan.source_contract(world,donor['container'],old,donor)
        if old in world.sdk.symbols:
            contract=world.sdk.get(old,donor)
        # The actual encoded callee owns its ABI. An admitted target inherits
        # its complete matched donor's definition even when the source bank's
        # callee variant has no matched C body. Otherwise a complete target
        # retail twin supplies the same body-backed prototype directly.
        if ctx['vram']<=new<ctx['vram']+ctx['end']-ctx['start']:
            callee_foff=ctx['start']+new-ctx['vram']
            actual=getattr(world,'admitted_contracts',{}).get((c,callee_foff))
            if not actual:
                exact=[r for r in world.rows if r['container']==c and r.get('foff')==callee_foff]
                for hit in exact:
                    definitions=world.byrow.get(hit['id'],[])
                    if len(definitions)==1 and callee_foff+hit['size']<=ctx['end']:
                        actual=dict(definitions[0],binding='matched-definition-at-encoded-target-physical-row',callee_foff=hex(callee_foff));break
                hits=exact+[r for r,pr in world.twins_at(c,callee_foff)]
                for hit in hits:
                    if actual:break
                    definitions=world.byrow.get(hit['id'],[])
                    if len(definitions)!=1 or callee_foff+hit['size']>ctx['end']:continue
                    if twins.proof(world.words(hit['container'],hit['foff'],hit['size']),world.words(c,callee_foff,hit['size'])) is None:continue
                    if contract:
                        try:compatible=declaration(definitions[0],'callee')==declaration(contract,'callee')
                        except ValueError:compatible=False
                        if not compatible:continue
                    actual=dict(definitions[0],binding='complete-encoded-target-callee-retail-twin',callee_foff=hex(callee_foff));break
            if actual:
                if old==new and contract:
                    try:compatible=declaration(actual,'callee')==declaration(contract,'callee')
                    except ValueError:compatible=False
                    if not compatible:raise ValueError('unchanged local callee has conflicting body-backed prototypes')
                contract=copy.deepcopy(actual)
        selection=None;prototype=None
        if os.environ.get('TWINS_CONTINUE3_ITEM') in ('1','2') and len(source_regions)==1:
            from callsite_contracts import choose
            rb=source_regions[0];start=int(rb['foff_start'],0);end=int(rb['foff_end'],0)
            choice=choose(world,donor,old,new,(start,end,start+int(rb['delta'],0)),ctx,contract,c)
            if choice:contract,selection=choice
            from prototype_variants import get as prototype_variant
            choice=prototype_variant(world,donor,old,new,(start,end,start+int(rb['delta'],0)),ctx,contract,c)
            if choice:contract,prototype=choice;selection=None
        target_proof=world.target_contract_proof(c,new,ctx['start'],ctx['vram'],ctx['end']-ctx['start'],contract,old) if contract else None
        item=dict(call_foff=hex(target+i*4),source_callee=hex(old),encoded_callee=hex(new),contract=contract,target_body_proof=target_proof)
        if selection:item['callsite_contract_selection']=selection
        if prototype:item['prototype_variant_proof']=prototype
        if old in world.sdk.symbols and not world.sdk.get(old,donor):
            record=next(r for r in world.sdk.report if int(r['address'],0)==old)
            item['sdk_hold']=dict(symbols=record['names'],status=record['status'],evidence='records/continue3/sdk_contracts.json')
        calls.append(item)
        if not contract or not target_proof:unresolved.append(item)
    if unresolved:
        if _context is None and ctx['delta']==bank['vram']-bank['start']:
            alternate=dict(ctx,start=bank['start'],end=bank['end'],vram=bank['vram'],basis='window-correlated-rowbase')
            if (alternate['start'],alternate['end'])!=(ctx['start'],ctx['end']):
                return candidate(world,bank,donor,target,evidence,_context=alternate)
        error=ValueError('matched_callee_contracts_unresolved')
        error.details=unresolved
        raise error
    text=bind(text,calls)
    from function_addresses import derive as address_declarations
    text,address_contracts=address_declarations(world,donor,bank,ctx,text,calls,oldrefs,newrefs,
        world.base_regions[c],
        lambda address:single_plan.source_contract(world,donor['container'],address,donor))
    func=f'func_{target+0x7ffe0000:08X}'
    donor_key=hashlib.sha256(donor['id'].encode()).hexdigest()[:10]
    path=OUT/'candidates'/c/donor_key/(func+'.c');path.parent.mkdir(parents=True,exist_ok=True);path.write_text(text)
    row=dict(container=c,func=func,id=c+'/'+func,foff=target,size=n,
        true_name=f"func_{target+ctx['delta']:08X}",delta=ctx['delta'],cfg=donor['cfg'],
        cell=donor['cell'],flags=donor['flags'],kind='overlay',
        c_path=f'overlays/{c}/first_pass_matched/{func}.c',template=donor['id'],
        template_foff=donor['foff'],window=bank['window'],src=str(path.relative_to(L)),
        relocation_proof=pr,paired_addresses={hex(k):hex(v) for k,v in mp.items() if k!=v},
        contracts=calls,link_context=ctx)
    if evidence:row.update(evidence)
    if donor['id'] in world.definition_authorities:
        row['donor_definition_authority']=world.definition_authorities[donor['id']]
    if os.environ.get('TWINS_CONTINUE3_ITEM') is not None:
        row['continue3_item']=int(os.environ['TWINS_CONTINUE3_ITEM'])
        edits=getattr(world,'generation_evidence',{}).get((donor['id'],c,target))
        if edits:row['source_relocation_edits']=edits
        flow=getattr(world,'generation_flow',{}).get((donor['id'],c,target))
        if flow:row['flow_relocation_proof']=flow
    if address_contracts:row['function_address_contracts']=address_contracts
    from common import covering_windows
    from mirror_splits import plan as mirror_plan
    mirror=mirror_plan(R,row,{row['window']}|{w[0] for w in covering_windows(c,target,n)})
    if mirror:row['mirror_split_ledgers']=mirror
    return row


def live_splits(world):
    stamps=getattr(world,'split_stamps',{})
    for c in world.B:
        path=R/f'ledger/splits/{c}.jsonl';stat=path.stat();stamp=(stat.st_mtime_ns,stat.st_size)
        if stamps.get(c)!=stamp:
            world.splits[c]=twins.jl(path);stamps[c]=stamp
            world.collision_cache={}
    world.split_stamps=stamps


def collision(world,c,o,n):
    cache=getattr(world,'collision_cache',None)
    if cache is None:cache=world.collision_cache={}
    key=(c,o,n)
    if key not in cache:cache[key]=[s for s in world.splits[c] if s['foff']<o+n and o<s['foff']+s['size']]
    return list(cache[key])


def transact(family, bank, rows, holds, phase, round_no, merge=True):
    """Use the unmodified runner and its rollback/merge protocol."""
    key=hashlib.sha256(json.dumps([(r['id'],r['template'],r['size'],twins.sha(L/r['src']),*([r['mirror_split_ledgers']] if r.get('mirror_split_ledgers') else [])) for r in rows],sort_keys=True).encode()).hexdigest()[:12]
    stub=copy.deepcopy(family)
    stub.update(id=f"{family['id']}__c2_{phase}_{key}",kind='single-window',banks=[bank])
    archive=OUT/'transactions'/stub['id']
    if merge and not (archive/'result.json').exists():
        # A bank/contract class can propose the identical source tuple. Reuse
        # only complete source-score failures; raw/window failures can depend
        # on cumulative ownership and are deliberately not shared here.
        for cached in (OUT/'transactions').glob(family['id']+'__c2_*_'+key+'/result.json'):
            result=json.loads(cached.read_text())
            rejected={(int(h['foff'],0),h['size']) for h in result.get('holds',[]) if h['reason']=='source score not exact'}
            if all(not b['rows'] and b['status']=='HOLD' for b in result['banks']) and rejected=={(r['foff'],r['size']) for r in rows}:
                added,conflicts=transactions.merge_family(family,stub,result);assert not added and not conflicts
                print('REUSE IDENTICAL SOURCE FAILURE',cached.parent.name,flush=True)
                return [],result
    if merge and (archive/'result.json').exists():
        result=json.loads((archive/'result.json').read_text())
        added,conflicts=transactions.merge_family(family,stub,result)
        assert not conflicts
        return added,result
    d=L/'evidence'/stub['id'];d.mkdir(exist_ok=True)
    original_plan=twins.plan
    def fixed_plan(f,w):
        assert f['id']==stub['id']
        twins.save(d/'plan.json',rows);twins.save(d/'holds.json',holds)
        return copy.deepcopy(rows)
    twins.plan=fixed_plan
    try:twins.run(stub,World_for_runner)
    finally:twins.plan=original_plan
    result=json.loads((d/'result.json').read_text())
    if merge:
        added,conflicts=transactions.merge_family(family,stub,result)
        assert not conflicts,conflicts
    else:
        added=[r for b in result['banks'] if b['status']=='MATCH' for r in b['rows']]
    archive.parent.mkdir(exist_ok=True)
    if archive.exists():
        import shutil
        shutil.copytree(d,archive,dirs_exist_ok=True);shutil.rmtree(d)
    else:d.rename(archive)
    return added,result


def chain_plan(world,family,bank,admitted):
    c=bank['container'];preceding=bank['start']-0x6000
    entries=[]
    for row in world.rows:
        if row['container']==c and preceding<=row.get('foff',-1)<bank['start'] and row['foff']+row['size']<=bank['start']:
            entries.append((row,row))
    for row in admitted:
        if row['container']==c and preceding<=row['foff']<bank['start'] and row['foff']+row['size']<=bank['start']:
            entries.append((row,world.byid[row['template']]))
    rows=[];holds=[];seen=set()
    for placement,donor in entries:
        o=placement['foff']+0x6000;n=placement['size']
        if (o,n) in seen or o+n>bank['end']:continue
        seen.add((o,n))
        if collision(world,c,o,n):continue
        try:
            intermediate=twins.proof(world.words(c,placement['foff'],n),world.words(c,o,n))
            flow=None
            if intermediate is None and os.environ.get('TWINS_FLOW_RELOCATIONS')=='1':
                from flow_relocations import prove
                source_vram=placement['foff']+placement['delta'] if 'delta' in placement else int(placement['true_name'][5:],16) if placement.get('true_name') else None
                if source_vram is None:
                    source_regions=regions(world,c,placement['foff'],n)
                    if len(source_regions)==1:source_vram=placement['foff']+int(source_regions[0]['delta'],0)
                ctx=context(world,bank,o,n)
                if source_vram is not None:
                    result=prove(world.words(c,placement['foff'],n),world.words(c,o,n),source_vram,o+ctx['delta'])
                    if result is not None:
                        intermediate=result[0]
                        flow=dict(source_vram=source_vram,target_vram=o+ctx['delta'],
                            reaching_pairs=[dict(word=i,source=result[1][i],target=result[2][i]) for i in sorted(set(result[1])&set(result[2]))])
            if intermediate is None:raise ValueError('nonrelocation word difference')
            ev=dict(bank_chain=dict(preceding_bank=preceding,predecessor=placement['id'],
                predecessor_foff=placement['foff'],predecessor_size=n,canonical_template=donor['id'],
                predecessor_source_sha256=placement.get('source_sha256'),relocation_proof=intermediate))
            if flow:ev['bank_chain']['flow_relocation_proof']=flow
            rows.append(candidate(world,bank,donor,o,ev))
        except (ValueError,KeyError) as e:
            holds.append(dict(window=bank['window'],foff=hex(o),size=n,template=donor['id'],reason=str(e),details=getattr(e,'details',None)))
    return rows,holds


def append_holds(family,holds):
    if not holds:return
    p=L/'evidence'/family['id']/'result.json';d=json.loads(p.read_text())
    transactions.unique_append(d.setdefault('holds',[]),holds);twins.save(p,d)


def inheritance(world,current):
    """Canonical body-backed prototypes inherited from fully admitted twins."""
    index={};incoming=collections.defaultdict(list)
    for row in current:
        for call in row.get('contracts',[]):
            target_proof=call.get('target_body_proof') or {}
            if target_proof.get('foff') and call.get('contract'):
                incoming[(row['container'],int(target_proof['foff'],0))].append(call)
        donor=world.byid[row['template']]
        donor_words=list(world.words(donor['container'],donor['foff'],donor['size']))
        for change in row.get('literal_replacements',[]):
            assert donor_words[change['word']]==int(change['before'],0)
            donor_words[change['word']]=int(change['after'],0)
        if twins.proof(donor_words,
                       world.words(row['container'],row['foff'],row['size'])) is None:
            from flow_relocations import prove
            ev=row.get('flow_relocation_proof')
            if not ev or prove(donor_words,
                world.words(row['container'],row['foff'],row['size']),ev['source_vram'],ev['target_vram']) is None:
                raise AssertionError('admitted callee body drift')
        definitions=world.byrow.get(donor['id'],[])
        if len(definitions)==1:
            index[(row['container'],row['foff'])]=dict(definitions[0],
                binding='prototype-inherited-from-admitted-complete-twin',
                inherited_row=row['id'],inherited_source_sha256=row['source_sha256'])
            if row.get('flow_relocation_proof'):
                index[(row['container'],row['foff'])].update(inherited_flow_relocation=row['flow_relocation_proof'],
                    inherited_container=row['container'],inherited_foff=row['foff'])
            if row.get('literal_replacements'):
                index[(row['container'],row['foff'])].update(inherited_literal_replacements=row['literal_replacements'],
                    inherited_container=row['container'],inherited_foff=row['foff'])
    world.admitted_contracts=index
    world.incoming_contracts=incoming
    original=world.contract
    def resolve(c,address,start,vram,extent):
        if vram<=address<vram+extent:
            inherited=index.get((c,start+address-vram))
            if inherited:return dict(inherited,callee_foff=hex(start+address-vram))
        return original(c,address,start,vram,extent)
    world.contract=resolve
    return len(index)


def contract_plan(world,family,bank):
    document=json.loads((L/'evidence'/family['id']/'result.json').read_text())
    proposals=[]
    for h in document['holds']:
        if h.get('window')==bank['window'] and h['reason']=='boundary_candidates_held':
            for failure in h.get('failures',[]):
                if failure['reason']=='matched_callee_contracts_unresolved':
                    proposals.append((int(h['foff'],0),failure['template']))
        if h.get('window')!=bank['window'] or h['reason'] not in ('matched_callee_contracts_unresolved','unresolved matched callee bodies'):
            continue
        name=h.get('template');target=h.get('target',h.get('foff'))
        if name and target:proposals.append((int(target,0),name))
    # Old aggregate holds occasionally omitted their donor; the census gives
    # an independently saved entry for exactly those records.
    for span in bank['spans']:
        if span.get('best_hit_foff') and span.get('best_matched_row'):
            proposals.append((int(span['best_hit_foff'],0),span['best_matched_row']))
    rows=[];holds=[];seen=set()
    for target,name in dict.fromkeys(proposals):
        donor=world.byid.get(name)
        if not donor:continue
        n=donor['size']
        if (target,n) in seen or collision(world,bank['container'],target,n):continue
        seen.add((target,n))
        matching=[s for s in bank['spans'] if s.get('best_hit_foff') and int(s['best_hit_foff'],0)==target
                  and s.get('best_matched_row')==name and int(s['foff'],0)<=target
                  and target+n<=int(s['foff'],0)+int(s['bytes'])]
        # Bank donor plans have an independent fixed offset placement. Generic
        # windows must retain the original complete census entry authority.
        layout=None;boundary=None
        if not matching:
            boundary=boundary_evidence(world,bank,target,n)
            if boundary is None:
                if family['kind']!='bank-family':continue
                donor_bank=family['banks'][0]['start']-0x6000
                if donor['container']!=bank['container'] or donor['foff']-donor_bank!=target-bank['start']:
                    continue
                if not donor_bank<=donor['foff'] or donor['foff']+n>donor_bank+bank['end']-bank['start']:
                    continue
                layout=dict(donor_bank=donor_bank,relative=target-bank['start'])
        try:
            row=candidate(world,bank,donor,target)
            region=regions(world,bank['container'],target,n)[0]
            if layout:row['bank_donor_recovery']=layout
            elif boundary:row['entry_validation']=boundary
            else:
                span=matching[0]
                row['entry_validation']=dict(census_span=dict(foff=span['foff'],size=int(span['bytes'])),
                    anchored_best_hit=hex(target),complete_extent=True,inside_window=True,placement_collision=False,
                    rowbase=dict(region=region['region'],foff_start=int(region['foff_start'],0),
                        foff_end=int(region['foff_end'],0),delta=int(region['delta'],0)))
            row['contract_round_recovery']=True
            rows.append(row)
        except (ValueError,KeyError) as e:
            holds.append(dict(window=bank['window'],foff=hex(target),size=n,template=name,
                reason=str(e),details=getattr(e,'details',None)))
    if os.environ.get('TWINS_CONTINUE3_ITEM')=='1':
        extra,failures=source_plan(world,family,bank)
        for row in extra:
            if not any(r['foff']<row['foff']+row['size'] and row['foff']<r['foff']+r['size'] for r in rows):rows.append(row)
        holds.extend(failures)
    return rows,holds


def source_attempts(family):
    paths=[OUT/'source_attempts'/(family['id']+'.json')]
    paths += [twins.HOME_LANE/'staging/workers'/f'w{i:02}'/'evidence/continue3/source_attempts'/(family['id']+'.json') for i in range(1,6)]
    return {tuple(key) for path in paths if path.exists() for key in json.loads(path.read_text())}


@functools.lru_cache(maxsize=1)
def frozen_source_table():
    return json.loads((twins.HOME_LANE/'evidence/continue2/near_twins/table.json').read_text())


def source_plan(world,family,bank):
    """Revisit frozen score holds with complete entry evidence, including re-anchors."""
    from function_boundaries import entries,terminal_return
    table=frozen_source_table()
    frozen=[r for r in table['rows'] if r['family']==family['id'] and r['hold_class']=='source score not exact'
            and (not r.get('window') or r['window']==bank['window'])]
    document=json.loads((L/'evidence'/family['id']/'result.json').read_text())
    for hold in document['holds']:
        if hold.get('window')!=bank['window'] or hold['reason']!='source score not exact':continue
        stub=hold.get('anchor_stub','');planpath=OUT/'transactions'/stub/'plan.json'
        if not stub or not planpath.exists():continue
        target=int(hold['foff'],0)
        for row in json.loads(planpath.read_text()):
            if row['foff']==target and row['size']==hold['size']:
                frozen.append(dict(foff=target,target=target,span_bytes=row['size'],best=dict(template=row['template'])))
    proposals=[];c=bank['container'];rb=twins.jl(BASE/f'config/overlays/{c}.rowbase.jsonl')
    edges=[int(r[key],0) for r in rb for key in ('foff_start','foff_end')]
    for item in frozen:
        target=item['target'];best=item.get('best') or {}
        if best.get('template'):proposals.append((target,best['template']))
        for donor,pr in sorted(world.twins_at(c,target),key=lambda x:-x[0]['size']):proposals.append((target,donor['id']))
        # Entries stay in the held span; their complete bodies use the real
        # containing census gap rather than a cropped failed-attempt size.
        containing=[span for span in bank['spans'] if int(span['foff'],0)<=target<int(span['foff'],0)+int(span['bytes'])]
        span=min(containing,key=lambda s:int(s['bytes'])) if containing else dict(foff=hex(item['foff']),bytes=item['span_bytes'])
        start=max(bank['start'],int(span['foff'],0));end=min(bank['end'],int(span['foff'],0)+int(span['bytes']))
        start=(start+3)&~3;end&=~3
        if end-start<8:continue
        previous=world.words(c,max(0,start-20),start-max(0,start-20))
        for address in entries(world.words(c,start,end-start),start,edges,previous):
            if not item['foff']<=address<item['foff']+item['span_bytes']:continue
            if collision(world,c,address,8):continue
            for donor,pr in sorted(world.twins_at(c,address),key=lambda x:-x[0]['size']):
                if address+donor['size']<=end:proposals.append((address,donor['id']))
    rows=[];holds=[];selected=[];seen=set()
    for target,name in dict.fromkeys(proposals):
        donor=world.byid.get(name)
        if not donor:continue
        n=donor['size'];key=(target,n)
        if key in seen or collision(world,c,target,n) or any(o<target+n and target<o+size for o,size in selected):continue
        ev=boundary_evidence(world,bank,target,n)
        if ev is None:
            holds.append(dict(window=bank['window'],foff=hex(target),size=n,template=name,reason='CONTINUE3 source retry lacks complete boundary/rowbase authority'));continue
        try:
            row=candidate(world,bank,donor,target,dict(entry_validation=ev,source_score_recovery=True))
            fingerprint=hashlib.sha256(twins.strip((L/row['src']).read_text()).encode()).hexdigest()
            row['source_fingerprint']=fingerprint
            if (c,target,n,fingerprint) in getattr(world,'source_attempted',set()):continue
            rows.append(row);selected.append(key);seen.add(key)
        except (ValueError,KeyError) as error:
            holds.append(dict(window=bank['window'],foff=hex(target),size=n,template=name,reason=str(error),details=getattr(error,'details',None)))
    return rows,holds


def run_sources(apply):
    global World_for_runner
    world=World_for_runner=twins.World();world.twins_at=functools.lru_cache(maxsize=32768)(world.twins_at)
    inheritance(world,admitted_rows());measure('sources_before');reports=[]
    families=twins.load_families()
    if os.environ.get('TWINS_FAMILIES'):families=[f for f in families if f['id'] in os.environ['TWINS_FAMILIES'].split(',')]
    for family in families:
        attempts=OUT/'source_attempts'/(family['id']+'.json')
        world.source_attempted={tuple(x) for x in json.loads(attempts.read_text())} if attempts.exists() else set()
        for mode in ('basic','split-address','split-pointer'):
            os.environ['TWINS_ADDRESS_MODE']=mode
            for bank in family['banks']:
                for attempt in itertools.count(1):
                    live_splits(world);rows,holds=source_plan(world,family,bank)
                    item=dict(family=family['id'],window=bank['window'],mode=mode,attempt=attempt,planned_rows=len(rows),planned_bytes=sum(r['size'] for r in rows),admitted_rows=0,admitted_bytes=0)
                    if apply:
                        append_holds(family,holds)
                        if rows:
                            print('SOURCES RUN',family['id'],bank['window'],mode,attempt,len(rows),item['planned_bytes'],flush=True)
                            added,_=transact(family,bank,rows,holds,'sources',attempt)
                            item.update(admitted_rows=len(added),admitted_bytes=sum(r['size'] for r in added))
                            world.source_attempted.update((r['container'],r['foff'],r['size'],r['source_fingerprint']) for r in rows if r['id'] not in {a['id'] for a in added})
                            twins.save(attempts,sorted(world.source_attempted))
                    elif rows:print('SOURCES PLAN',family['id'],len(rows),item['planned_bytes'],flush=True)
                    reports.append(item);twins.save(OUT/'sources_progress.json',dict(apply=apply,banks=reports))
                    if not apply or not rows:break
    twins.save(OUT/'sources_progress.json',dict(apply=apply,banks=reports,complete=True))
    measure('sources_after');return reports


def run_contracts(apply):
    global World_for_runner
    before=measure('contracts_before');reports=[]
    families=twins.load_families()
    if os.environ.get('TWINS_FAMILIES'):families=[f for f in families if f['id'] in os.environ['TWINS_FAMILIES'].split(',')]
    for round_no in itertools.count(1):
        world=World_for_runner=twins.World()
        world.twins_at=functools.lru_cache(maxsize=32768)(world.twins_at)
        inherited=inheritance(world,admitted_rows());unlocked=[];planned_count=planned_bytes=0
        # Freeze the inheritance index for this round. A newly admitted callee
        # can only supply its body-backed prototype in the following round.
        for family in families:
            for bank in family['banks']:
                if os.environ.get('TWINS_CONTINUE3_ITEM')=='1':world.source_attempted=source_attempts(family)
                live_splits(world);rows,holds=contract_plan(world,family,bank)
                planned_count+=len(rows);planned_bytes+=sum(r['size'] for r in rows)
                if apply:
                    append_holds(family,holds)
                    if rows:
                        for row in rows:row['contract_admission_round']=round_no
                        print('CONTRACT RUN',round_no,family['id'],len(rows),sum(r['size'] for r in rows),flush=True)
                        added,result=transact(family,bank,rows,holds,'contracts',round_no);unlocked.extend(added)
                        if os.environ.get('TWINS_CONTINUE3_ITEM')=='1':
                            failed={(int(h['foff'],0),h['size']) for h in result.get('holds',[]) if h['reason']=='source score not exact'}
                            attempts=source_attempts(family)
                            attempts.update((r['container'],r['foff'],r['size'],hashlib.sha256(twins.strip((L/r['src']).read_text()).encode()).hexdigest()) for r in rows if (r['foff'],r['size']) in failed)
                            twins.save(OUT/'source_attempts'/(family['id']+'.json'),sorted(attempts))
                elif rows:print('CONTRACT PLAN',family['id'],len(rows),sum(r['size'] for r in rows),flush=True)
        record=dict(round=round_no,inherited_callee_bodies=inherited,planned_rows=planned_count,planned_bytes=planned_bytes,
            admitted_rows=len(unlocked),admitted_bytes=sum(r['size'] for r in unlocked))
        reports.append(record);twins.save(OUT/'contracts_progress.json',dict(rounds=reports,apply=apply))
        print('CONTRACT ROUND',record,flush=True)
        if not apply or not unlocked:break
    measure('contracts_after');return reports


def boundary_evidence(world,bank,target,n):
    """Reprove a saved boundary caller before a later callee-contract round."""
    from function_boundaries import entries,terminal_return
    c=bank['container'];tail=terminal_return(world.words(c,target,n))
    hits=regions(world,c,target,n)
    if tail is None or len(hits)!=1:return None
    rb=hits[0]
    all_regions=twins.jl(BASE/f'config/overlays/{c}.rowbase.jsonl')
    edges=[int(r[key],0) for r in all_regions for key in ('foff_start','foff_end')]
    for span in bank['spans']:
        start=(max(bank['start'],int(span['foff'],0))+3)&~3
        end=min(bank['end'],int(span['foff'],0)+int(span['bytes']))&~3
        if not start<=target or target+n>end:continue
        previous=world.words(c,max(0,start-20),start-max(0,start-20))
        authority=entries(world.words(c,start,end-start),start,edges,previous).get(target)
        if not authority:continue
        return dict(kind='function-boundary',complete_target_body=True,placement_collision=False,
            census_gap=dict(foff=int(span['foff'],0),size=int(span['bytes'])),
            rowbase=dict(region=rb['region'],foff_start=int(rb['foff_start'],0),
                foff_end=int(rb['foff_end'],0),delta=int(rb['delta'],0)),
            boundary=dict(foff=target,authorities=authority,terminal_return_word=tail,survey_start=start,survey_end=end))
    return None


def boundary_plan(world,family,bank):
    from function_boundaries import entries,terminal_return
    c=bank['container'];rows=[];holds=[];occupied=[]
    rb=twins.jl(BASE/f'config/overlays/{c}.rowbase.jsonl')
    edges=[int(r['foff_start'],0) for r in rb]+[int(r['foff_end'],0) for r in rb]
    for span in bank['spans']:
        start=max(bank['start'],int(span['foff'],0));end=min(bank['end'],int(span['foff'],0)+int(span['bytes']))
        start=(start+3)&~3;end&=~3
        if end-start<8:continue
        words=world.words(c,start,end-start)
        previous=world.words(c,max(0,start-20),start-max(0,start-20))
        boundaries=entries(words,start,edges,previous)
        for target,authority in sorted(boundaries.items()):
            if target+8>end or collision(world,c,target,8):continue
            twins_at=world.twins_at(c,target)
            if not twins_at:continue
            failures=[]
            for donor,pr in sorted(twins_at,key=lambda x:(x[0]['container']!=c,-x[0]['size'],x[0]['id'])):
                n=donor['size']
                if target+n>end or collision(world,c,target,n):continue
                if any(o<target+n and target<o+size for o,size in occupied):continue
                tail=terminal_return(world.words(c,target,n))
                if tail is None:continue
                try:
                    row=candidate(world,bank,donor,target)
                    region=regions(world,c,target,n)[0]
                    row['entry_validation']=dict(kind='function-boundary',complete_target_body=True,
                        placement_collision=False,census_gap=dict(foff=int(span['foff'],0),size=int(span['bytes'])),
                        rowbase=dict(region=region['region'],foff_start=int(region['foff_start'],0),
                            foff_end=int(region['foff_end'],0),delta=int(region['delta'],0)),
                        boundary=dict(foff=target,authorities=authority,terminal_return_word=tail,
                            survey_start=start,survey_end=end))
                    rows.append(row);occupied.append((target,n));break
                except (ValueError,KeyError) as e:
                    failures.append(dict(template=donor['id'],reason=str(e),details=getattr(e,'details',None)))
            else:
                if failures:holds.append(dict(window=bank['window'],foff=hex(target),size=8,
                    reason='boundary_candidates_held',failures=failures[:8]))
    return rows,holds


def run_boundaries(apply):
    global World_for_runner
    world=World_for_runner=twins.World();world.twins_at=functools.lru_cache(maxsize=32768)(world.twins_at)
    inheritance(world,admitted_rows());measure('boundaries_before');reports=[]
    families=twins.load_families()
    if os.environ.get('TWINS_FAMILIES'):families=[f for f in families if f['id'] in os.environ['TWINS_FAMILIES'].split(',')]
    for family in families:
        for bank in family['banks']:
            live_splits(world);rows,holds=boundary_plan(world,family,bank)
            item=dict(family=family['id'],window=bank['window'],planned_rows=len(rows),
                planned_bytes=sum(r['size'] for r in rows),admitted_rows=0,admitted_bytes=0)
            if apply:
                append_holds(family,holds)
                if rows:
                    print('BOUNDARY RUN',family['id'],bank['window'],len(rows),item['planned_bytes'],flush=True)
                    added,_=transact(family,bank,rows,holds,'boundaries',1)
                    item.update(admitted_rows=len(added),admitted_bytes=sum(r['size'] for r in added))
            elif rows:print('BOUNDARY PLAN',family['id'],len(rows),item['planned_bytes'],flush=True)
            reports.append(item);twins.save(OUT/'boundaries_progress.json',dict(apply=apply,banks=reports))
    twins.save(OUT/'boundaries_progress.json',dict(apply=apply,banks=reports,complete=True))
    measure('boundaries_after');return reports


def run_replacements(apply):
    global World_for_runner
    import replacement_runner
    from split_replace import is_data
    world=World_for_runner=twins.World();world.twins_at=functools.lru_cache(maxsize=32768)(world.twins_at)
    inheritance(world,admitted_rows());measure('replace_before')
    families=twins.load_families();classified=collections.Counter();holds=[];seen=set();reports=[]
    # Quantify the requested historical collision class independently of the
    # raw-segment survey. Already matched C and data never become replaceable.
    live_splits(world)
    for family in families:
        document=json.loads((L/'evidence'/family['id']/'result.json').read_text())
        c=family['banks'][0]['container']
        for hold in document['holds']:
            if hold['reason']!='existing split extent: no overlapping append':continue
            key=(c,int(hold['foff'],0),hold['size'])
            if key in seen:continue
            seen.add(key)
            owners=collision(world,c,key[1],key[2])
            if any(is_data(s) for s in owners):kind='data-segment-protected'
            elif any(s.get('result')=='MATCH' for s in owners):kind='already-matched-C-protected'
            elif owners:kind='raw-asm-code-segment'
            else:kind='historical-overlap-no-longer-present'
            classified[kind]+=1
            reports.append(dict(container=c,foff=key[1],size=key[2],classification=kind,owners=owners))
    raw_segments=[(c,s) for c,ss in world.splits.items() for s in ss
                  if not is_data(s) and s.get('result')!='MATCH']
    surveyed=[]
    for c,segment in raw_segments:
        possible=[(f,b) for f in families for b in f['banks'] if b['container']==c
                  and b['start']<=segment['foff'] and segment['foff']+segment['size']<=b['end']]
        item=dict(container=c,segment=segment,candidate_rows=0,admitted_rows=0)
        owners=collision(world,c,segment['foff'],segment['size'])
        if any(owner!=segment for owner in owners):
            item['hold']='raw extent has overlapping split ownership; replacement refused'
            surveyed.append(item);continue
        if not possible:
            item['hold']='raw split has no ranked covering production window';surveyed.append(item);continue
        family,bank=min(possible,key=lambda pair:pair[1]['end']-pair[1]['start'])
        rows=[];pos=segment['foff'];end=pos+segment['size']
        while pos<end:
            found=False
            for donor,proof in sorted(world.twins_at(c,pos),key=lambda x:-x[0]['size']):
                if pos+donor['size']>end:continue
                try:
                    row=candidate(world,bank,donor,pos)
                    region=regions(world,c,pos,donor['size'])[0]
                    row['entry_validation']=dict(kind='split-replacement',complete_target_body=True,
                        placement_collision=False,replaced_segment=segment,
                        rowbase=dict(region=region['region'],foff_start=int(region['foff_start'],0),
                            foff_end=int(region['foff_end'],0),delta=int(region['delta'],0)))
                    rows.append(row);pos+=row['size'];found=True;break
                except (ValueError,KeyError):continue
            if not found:break
        item['candidate_rows']=len(rows)
        if pos!=end:
            item['hold']='no complete exact-C donor tiling of the existing raw extent'
        elif apply:
            def unmerged(*args):return transact(*args,merge=False)
            try:
                added,result,receipt=replacement_runner.run(family,bank,segment,rows,world,unmerged)
                if added:
                    stub=dict(id=result['family'],banks=[bank])
                    merged,conflicts=transactions.merge_family(family,stub,result);assert not conflicts
                    item['admitted_rows']=len(merged);item['receipt']=receipt
                else:item['hold']='normal source/raw/window gate refused replacement'
            except (ValueError,RuntimeError) as error:item['hold']=str(error)
        surveyed.append(item)
        print('REPLACEMENT',c,hex(segment['foff']),item.get('hold',item['admitted_rows']),flush=True)
    summary=dict(apply=apply,collision_classification=dict(classified),collision_spans=reports,
        raw_segments=surveyed,admitted_rows=sum(x['admitted_rows'] for x in surveyed))
    twins.save(OUT/'replace_progress.json',summary);measure('replace_after')
    print('REPLACEMENT SUMMARY',dict(classified),summary['admitted_rows'],flush=True)
    return summary


def run_chain(apply):
    global World_for_runner
    world=World_for_runner=twins.World();families=[f for f in twins.load_families() if f['kind']=='bank-family']
    if os.environ.get('TWINS_FAMILIES'):families=[f for f in families if f['id'] in os.environ['TWINS_FAMILIES'].split(',')]
    world.twins_at=functools.lru_cache(maxsize=32768)(world.twins_at)
    before=measure('chain_before');reports=[]
    # Admission from a previous bank is visible only after its full transaction.
    for round_no in itertools.count(1):
        unlocked=[];planned_count=planned_bytes=0
        current=admitted_rows()
        inheritance(world,current)
        for family in families:
            for bank in sorted(family['banks'],key=lambda b:b['start']):
                live_splits(world)
                rows,holds=chain_plan(world,family,bank,current)
                planned_count+=len(rows);planned_bytes+=sum(r['size'] for r in rows)
                if apply:
                    append_holds(family,holds)
                    if rows:
                        print('CHAIN RUN',family['id'],bank['window'],len(rows),sum(r['size'] for r in rows),flush=True)
                        added,_=transact(family,bank,rows,holds,'chain',round_no)
                        unlocked.extend(added)
                        current.extend(added)
                elif rows:print('CHAIN PLAN',family['id'],bank['window'],len(rows),sum(r['size'] for r in rows),flush=True)
        record=dict(round=round_no,planned_rows=planned_count,planned_bytes=planned_bytes,
            admitted_rows=len(unlocked),admitted_bytes=sum(r['size'] for r in unlocked))
        reports.append(record);twins.save(OUT/'chain_progress.json',dict(rounds=reports,apply=apply))
        print('CHAIN ROUND',record,flush=True)
        if not apply or not unlocked:break
    measure('chain_after')
    return reports


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('phase',choices=['chain','contracts','boundaries','replace','sources','measure'])
    parser.add_argument('--apply',action='store_true')
    args=parser.parse_args()
    if args.phase=='chain' and os.environ.get('TWINS_CONTINUE3_ITEM')=='1' and not os.environ.get('TWINS_FAMILIES'):
        from continue3_rowbases import run as recover_rowbases
        recover_rowbases(args.apply)
    if args.phase=='measure':print(json.dumps(measure('current'),indent=1))
    elif args.phase=='chain':run_chain(args.apply)
    elif args.phase=='contracts':run_contracts(args.apply)
    elif args.phase=='boundaries':run_boundaries(args.apply)
    elif args.phase=='sources':run_sources(args.apply)
    else:run_replacements(args.apply)


if __name__=='__main__':main()
