"""Recover original bank-family authority and independent SDK entry witnesses."""
import csv,re,functools
from twins import L,sha
from function_boundaries import entries,terminal_return

@functools.lru_cache(maxsize=1)
def bank_windows():
    report=L/'ref/twins2_REPORT.md'
    families={m[1]:int(m[2]) for m in re.finditer(r'^\| \d+ \| (\w+) \| (\d+) \|',report.read_text(),re.M)}
    out={};digest=sha(report)
    for row in csv.DictReader((L/'sdk_targets.tsv').open(),delimiter='\t'):
        if families.get(row['family'],0)>1:
            out[row['window']]=dict(family=row['family'],banks=families[row['family']],report='work/native_lane/r121_sdk/ref/twins2_REPORT.md',report_sha256=digest)
    return out

@functools.lru_cache(maxsize=1)
def saved_extents():
    return {(r['family'].split('_')[0],int(r['foff'],0),int(r['bytes']),r['window']) for r in csv.DictReader((L/'sdk_targets.tsv').open(),delimiter='\t') if r['foff']}

def qualify(world,row):
    if not row.get('bank_chain'):return False
    authority=bank_windows().get(row['window'])
    if authority:
        if row.get('bank_family_authority')==authority:return False
        row['bank_family_authority']=authority
        return True
    c,o,n=row['container'],row['foff'],row['size']
    assert (c,o,n,row['window']) in saved_extents(),('single-window chain has no exact saved SDK hold',row['id'])
    words=world.words(c,o,n);start=o;end=o+n
    previous=world.words(c,max(0,start-20),start-max(0,start-20))
    edges=[int(region[key],0) for region in world.base_regions[c] for key in ('foff_start','foff_end')]
    boundary=entries(words,start,edges,previous).get(o);tail=terminal_return(words)
    assert boundary and tail is not None,('single-window SDK entry lacks complete boundary evidence',row['id'])
    row['sdk_target_entry']=dict(input='work/native_lane/r121_sdk/sdk_targets.tsv',foff=o,size=n,scope_foff=o,scope_size=n,survey_start=start,survey_end=end,entry_authorities=boundary,terminal_return_word=tail)
    row['predecessor_body_witness']=row.pop('bank_chain')
    return True
