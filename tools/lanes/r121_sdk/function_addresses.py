"""Body-backed declarations for static function values, without call assertions."""
import re
from contracts import bind,declaration


def derive(world,donor,bank,context,text,calls,oldrefs,newrefs,regions,source_contract):
    from twins import strip
    delta=bank['vram']-bank['start']
    if delta!=context['delta']:return text,[]
    bare=re.sub(r'^\s*#.*$','',strip(text),flags=re.M)
    direct={int(call['encoded_callee'],0) for call in calls}
    records=[];seen=set();c=bank['container']
    for word,ref in oldrefs.items():
        if ref['kind']!='absolute' or word not in newrefs or newrefs[word]['kind']!='absolute':continue
        old,new=ref['address'],newrefs[word]['address']
        name=f'func_{new:08X}'
        if old==new or new in direct or (old,new) in seen or not re.search(r'\b'+name+r'\b',bare):continue
        seen.add((old,new));off=new-delta
        if not bank['start']<=off<bank['end']:continue
        source=source_contract(old)
        # Address-only declarations require a source definition independently
        # resolvable from the frozen catalog. Direct-call inheritance remains
        # the separate, fully audited callee path.
        if not source or source.get('inherited_row'):continue
        try:expected=declaration(source,'callee')
        except ValueError:continue
        source_hit=getattr(world,'admitted_contracts',{}).get((c,off))
        definitions=[source_hit] if source_hit else []
        exact=[r for r in world.rows if r['container']==c and r.get('foff')==off]
        for hit in exact+[r for r,proof in world.twins_at(c,off)]:
            entries=world.byrow.get(hit['id'],[])
            if len(entries)==1:definitions.extend(entries)
        chosen=None
        for definition in definitions:
            try:
                if declaration(definition,'callee')!=expected:continue
            except ValueError:continue
            size=world.byid[definition['row']]['size']
            if off+size>bank['end']:continue
            matches=[r for r in regions if r.get('base_confidence') in ('proven','solved')
                and int(r['foff_start'],0)<=off and off+size<=int(r['foff_end'],0)
                and int(r['delta'],0)==delta]
            if len(matches)!=1:continue
            region=matches[0];start,end=int(region['foff_start'],0),int(region['foff_end'],0)
            contract=dict(definition,binding='matched-body-for-static-function-value',callee_foff=hex(off))
            proof=world.target_contract_proof(c,new,start,start+delta,end-start,contract,old)
            if not proof:continue
            # No alternate body of a different extent may escape the proved region.
            if off+proof['bytes']>end or off+proof['bytes']>bank['end']:continue
            chosen=dict(source_callee=hex(old),encoded_callee=hex(new),source_contract=source,
                contract=contract,target_body_proof=proof,target_context=dict(region=region['region'],
                    start=start,end=end,delta=delta),dynamic_call_assertions=0,
                reference_words=sorted(i for i,r in oldrefs.items() if r['kind']=='absolute'
                    and r['address']==old and i in newrefs and newrefs[i]['kind']=='absolute' and newrefs[i]['address']==new))
            break
        if not chosen:continue
        # The new local declaration owns this symbol. Shared headers retain
        # their original names and pointer-pointee identities.
        text=re.sub(r'^#define\s+func_'+f'{old:08X}'+r'\s+'+name+r'\s*\n','',text,flags=re.M)
        records.append(chosen)
    return bind(text,records),records
