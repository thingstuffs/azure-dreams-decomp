#!/usr/bin/env python3
"""Exercise provenance and coverage refusal cases on actual measured records."""
import copy
import json
from pathlib import Path
import dependency_import as D

HERE=Path(__file__).resolve().parent
run=HERE/'census_reconciled'
inputs,by=D.load_run(run)
registry=D.unique(D.read_lines(D.ROOT/'ledger/rows.jsonl'),'id')
old=D.unique(D.read_lines(D.ROOT/'ledger/maspsx_dependence.jsonl'),'id')
checks=[]

def rejects(name, fn, contains):
    try:
        fn()
    except ValueError as exc:
        assert contains in str(exc), (name,str(exc))
        checks.append({'check':name,'result':'REFUSED','reason':str(exc)})
    else:
        raise AssertionError('unsafe input was accepted: '+name)

records=list(by.values())
rejects('duplicate registered identity',lambda:D.validate_records(records+[records[0]],registry),'duplicate identity')
rejects('missing registered identity',lambda:D.validate_records(records[1:],registry),'cover exactly')
bad=copy.deepcopy(records);bad[0]['selfcheck']=False
rejects('failed trace self-check',lambda:D.validate_records(bad,registry),'incomplete pipeline/trace')
bad=copy.deepcopy(records);bad[0]['genuine'].pop('2.79')
rejects('missing genuine version',lambda:D.validate_records(bad,registry),'incomplete six-version')
rejects('private journal cannot be live evidence',lambda:D.load_run(run,fresh=True),'fresh production-root census')
bad=dict(by);rid=next(rid for rid in by if rid not in old);bad[rid]=dict(by[rid],exact_versions=[])
rejects('unreviewed new dependency',lambda:D.project(bad,old,'private-test'),'new dependent identities')
proposed,removed=D.project(by,old,'private-test')
assert len(proposed)==167 and len(removed)==22
for row in proposed:
    assert row['kinds']==old[row['id']]['kinds']
for rid in ['slus/code','slus/code2']:
    row=next(r for r in proposed if r['id']==rid)
    assert row['attribution_scope']=='physical-unit'
    assert len(row['dependent_physical_units'])==1
    assert row['dependent_physical_units'][0]['role']=='remainder'
checks.append({'check':'complete actual census projection','result':'PASS','before':189,'after':167,
               'removed':22,'new':0,'retained_kinds_unchanged':True,
               'collector_attribution_scoped_to_remainder':True})
receipt={'status':'PASS','script_sha256':D.sha(HERE/'dependency_import.py'),
         'journal_sha256':D.sha(run/'journal.jsonl'),
         'production_ledger_sha256':D.sha(D.ROOT/'ledger/maspsx_dependence.jsonl'),
         'checks':checks,'production_written':False,
         'limitation':'Fresh production acceptance is deferred until the approved transition and census exist.'}
(HERE/'dependency_projection/checks.json').write_text(json.dumps(receipt,indent=2)+'\n')
print(json.dumps(receipt,indent=2))
