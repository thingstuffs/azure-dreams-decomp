#!/usr/bin/env python3
"""Recompile frozen plain-C probes, observe the real passes, and check every cookbook claim."""
from pathlib import Path
import hashlib, json, re, shutil, subprocess, sys
import compile as C
import setup
L=Path(__file__).resolve().parents[1]

def events(tag):
    return [json.loads(s) for s in (L/'tmp/build'/tag/'observe.jsonl').read_text().splitlines()]
def txt(tag,name):return (L/'tmp/build'/tag/name).read_text()
def pri(refs,length,size=1):return int(((refs.bit_length()-1)*refs/length)*10000*size)
def main():
    cases=json.loads((L/'cases.json').read_text())
    setup.main()
    expected=json.loads((L/'expected.json').read_text())
    assert json.loads((L/'evidence/input_hashes.json').read_text())==expected['compiler_inputs'],'compiler/source input drift'
    results={}
    for tag in cases:
        results[tag]=C.compile_one(L/'reproducers'/f'{tag}.c')
    subprocess.run([sys.executable,str(L/'tools/observe.py'),*cases],cwd=L,check=True)
    claims={}
    for a,b in [('sched_birth_a','sched_birth_b'),('sched_birth_live_a','sched_birth_live_b'),
                ('cse_copy_a','cse_copy_b'),('combine_split_a','combine_split_b')]:
        assert results[a]['text_sha256']==results[b]['text_sha256'],(a,b)
    for a,b in [('sched_const_a','sched_const_b'),('sched_luid_a','sched_luid_b'),('global_refs6','global_refs7')]:
        assert results[a]['text_sha256']!=results[b]['text_sha256'],(a,b)
    # Guard the read-only observer and the frozen linked byte proofs as well as their interpretations.
    for tag in cases:
        assert results[tag]['text_sha256']==expected['text_sha256'][tag],tag+' byte drift'
        ev=events(tag)
        assert ev[-1]=={'event':'end','exit_code':0}
        assert not any(x['event']=='error' for x in ev)
        pending=[]
        for e in ev:
            if e['event']=='birth_test':pending.append(e)
            elif e['event']=='birth_return':
                test=pending.pop()
                if 'reg' in test:
                    assert bool(e['value'])==(test['reload_completed']!=1 and test['live'] and test['sets']==1),test
    ba=[e for e in events('sched_birth_live_a') if e['event']=='birth_test' and e.get('reg')==82]
    bb=[e for e in events('sched_birth_live_b') if e['event']=='birth_test' and e.get('reg')==82]
    assert ba and bb and all(e['sets']==2 for e in ba) and all(e['sets']==1 for e in bb)
    assert '19 (2)' in txt('sched_birth_live_a','f.i.sched')
    assert '19 (7f000001)' in txt('sched_birth_live_b','f.i.sched')
    claims['sched1_birth']={'status':'PROVEN','multiset_pseudo':82,'a_sets':2,'b_sets':1,
                            'bound':'sched1 boost changes; final linked bytes remain identical in this pair'}
    assert 'now 21 16' in txt('sched_luid_a','f.i.sched')
    assert 'now 21 16' in txt('sched_luid_b','f.i.sched')
    claims['sched1_luid']={'status':'PROVEN','backward_first':21,'backward_second':16,
                          'bound':'priorities/classes tie; initial ready instructions are not boosted'}
    gt={}
    for tag in ['global_refs6','global_refs7']:
        tab={e['pseudo']:e for event in events(tag) if event['event']=='global_compare' for e in event['table']}
        gt[tag]={str(p):dict(e,priority=pri(e['refs'],e['length'],e['size'])) for p,e in tab.items()}
    assert gt['global_refs6']['81']['refs']==7 and gt['global_refs7']['81']['refs']==8
    assert gt['global_refs6']['80']['priority']>gt['global_refs6']['81']['priority']
    assert gt['global_refs7']['80']['priority']<gt['global_refs7']['81']['priority']
    assert '3 regs to allocate: 80 81 82' in txt('global_refs6','f.i.greg')
    assert '3 regs to allocate: 81 80 82' in txt('global_refs7','f.i.greg')
    depth=[e for e in events('global_loop_depth') if e['event']=='flow_reference']
    assert {e['depth'] for e in depth}>={1,2,3}
    assert all(e['after']-e['before']==e['depth'] for e in depth)
    claims['global_priority']={'status':'PROVEN','tables':gt,'flow_ref_depths':sorted({e['depth'] for e in depth}),
                              'bound':'7/8-reference controls have different real output writes; no byte-neutral lever claimed'}
    local={}
    for n,want in [(2,[1,0]),(3,[0,1,2]),(4,[1,0,2,3])]:
        e=[x for x in events('local_fixed'+str(n)) if x['event']=='local_request']
        assert e and all(x['next_qty']==n for x in e)
        order=[x['q'] for x in e if not x['suggested']]
        assert order==want
        table=e[0]['table']
        density=sorted(range(n),key=lambda q:(-pri(table[q]['refs'],table[q]['death']-table[q]['birth'],table[q]['size']),q))
        assert (order==density)==(n!=3)
        local[str(n)]={'order':order,'density_order':density,'table':table}
    claims['local_quantity_order']={'status':'PROVEN','controls':local,
                                   'bound':'three-quantity fixed-index sort bug; two quantities sort correctly'}
    cse=[e for e in events('cse_copy_a') if e['event']=='cse_equivalence' and e['new']==82 and e['old']==80]
    assert any(e['new_last']>e['block_end'] and e['new_last']>e['old_last'] and e['head_after']==82 for e in cse)
    assert any(e['new_last']<=e['block_end'] and e['head_after']==80 for e in cse)
    claims['cse_copy']={'status':'PROVEN','canonicalization':cse,
                       'bound':'cross-block promotion can be undone by a later CSE pass; final bytes equal direct-parameter control'}
    rr=[e for e in events('reload_live') if e['event']=='reload_simplify' and e['before']['code']==57 and e['after']['code']==52]
    assert rr and rr[0]['uid']==22 and rr[0]['after']['field0']==5
    assert '(mem/s:SI' in txt('reload_live','f.i.lreg') and '(reg/v:SI 5 a1)' in txt('reload_live','f.i.greg')
    no=[e for e in events('reload_reread') if e['event']=='reload_simplify' and e['before']['code']==57 and e['after']['code']==52]
    assert not no
    claims['reload_cse']={'status':'PROVEN','converted_uid':22,'copy_source_hard_reg':5,
                         'bound':'recorded value must still survive in a hard register; reload_reread control clobbers it'}
    ca=[e for e in events('combine_split_a') if e['event']=='combine_attempt' and e['success'] and e['i1']]
    assert ca and ca[0]['i1']==10 and ca[0]['i2']==11 and ca[0]['i3']==13
    assert ca[0]['before']['i2'][1]==ca[0]['after']['i2'][1]==['reg',83,0]
    cr=[e for e in events('combine_split_a') if e['event']=='combine_i2dest_referenced']
    assert cr and cr[0]['result']==0
    refused=[e for e in events('combine_split_or') if e['event']=='combine_attempt' and e['i1'] and e['success']]
    assert not refused
    claims['combine_i2dest']={'status':'PROVEN','accepted':ca[0],'referenced_test':cr[0],
                             'bound':'three-insn candidate, same-mode adjacent i2/i3, i2dest absent from newpat; +3 control refuses'}
    # Freeze evidence outside the exploratory build directory.
    frozen=L/'evidence/probes'
    for tag in cases:
        dst=frozen/tag;dst.mkdir(parents=True,exist_ok=True)
        for p in (L/'tmp/build'/tag).iterdir():
            if p.is_file():shutil.copy2(p,dst/p.name)
    record={'reviewer':'pending','recipe':['-O2','-G0','-msoft-float'],
            'probes':results,'claims':claims,'production_rows_changed':0,'modules_touched':[]}
    (L/'evidence/results.json').write_text(json.dumps(record,indent=2)+'\n')
    print('PASS: %d probes; 7 symptom claims across all 6 pass families.'%len(cases))
if __name__=='__main__':main()
