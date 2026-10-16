"""Recompute whole-body, entry, chain and import evidence independently."""
from twins import proof,references
from function_boundaries import entries,terminal_return

def audit(world,rows):
    results=[]
    for row in rows:
        donor=world.byid[row['template']];c=row['container'];o=row['foff'];n=row['size']
        assert donor['size']==n
        source=world.words(donor['container'],donor['foff'],n);target=world.words(c,o,n)
        assert proof(source,target)==row['relocation_proof'],('retail relocation drift',row['id'])
        ctx=row['link_context'];assert o+ctx['delta']==int(row['true_name'][5:],16)
        if row.get('bank_chain'):
            from entry_scope import bank_windows
            assert row.get('bank_family_authority')==bank_windows().get(row['window']) and row.get('bank_family_authority'),('chain lacks original bank-family authority',row['id'])
            chain=row['bank_chain'];po=chain['predecessor_foff']
            assert po+0x6000==o and chain['predecessor_size']==n
            assert proof(world.words(c,po,n),target)==chain['relocation_proof']
        else:
            ev=row['sdk_target_entry'];assert ev['foff']==o and ev['size']==n
            start=ev.get('survey_start',o);end=ev.get('survey_end',o+n)
            assert start<=o and o+n<=end
            previous=world.words(c,max(0,start-20),start-max(0,start-20))
            edges=[int(region[key],0) for region in world.base_regions[c] for key in ('foff_start','foff_end')] if 'survey_start' in ev else [ctx['start'],ctx['end']]
            boundary=entries(world.words(c,start,end-start),start,edges,previous).get(o)
            assert boundary==ev['entry_authorities'] and terminal_return(target)==ev['terminal_return_word']
        oldrefs=references(source)[0];newrefs=references(target)[0]
        for call in row['contracts']:
            word=(int(call['call_foff'],0)-o)//4
            old=int(call['source_callee'],0);new=int(call['encoded_callee'],0)
            assert oldrefs[word]['address']==old and newrefs[word]['address']==new
            contract=call['contract']
            if old in world.sdk.symbols:
                assert old==new and contract==world.sdk.get(old,donor)
            regenerated=world.target_contract_proof(c,new,ctx['start'],ctx['vram'],ctx['end']-ctx['start'],contract,old)
            assert regenerated==call['target_body_proof'],('target body proof drift',row['id'],hex(new))
        for address in row.get('function_address_contracts',[]):
            tc=address['target_context'];new=int(address['encoded_callee'],0);old=int(address['source_callee'],0)
            regenerated=world.target_contract_proof(c,new,tc['start'],tc['start']+tc['delta'],tc['end']-tc['start'],address['contract'],old)
            assert regenerated==address['target_body_proof']
        results.append(dict(id=row['id'],retail_relocations=len(row['relocation_proof']),calls=len(row['contracts']),static_addresses=len(row.get('function_address_contracts',[])),passed=True))
    return results
