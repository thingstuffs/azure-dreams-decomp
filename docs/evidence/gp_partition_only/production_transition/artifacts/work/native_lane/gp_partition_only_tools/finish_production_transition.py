#!/usr/bin/env python3
"""Install a reviewed fresh census proposal and verify final production state."""
from collections import Counter,defaultdict
import fcntl
import hashlib
import json
from pathlib import Path
import subprocess
import sys
import time
import dependency_import as D
import activate_transition as T
from fidelity import aspsx_diff as A
import aspsx_report as R
from row_db import edges_of
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[2]
RUN=HERE/'production_census'
PROPOSAL=HERE/'production_dependency_proposal'
ACTIVATION=HERE/'activation_runs/20260925T010431Z_625211_resumed3'
OUT=HERE/'production_completion.json'
if OUT.exists() or (HERE/'production_import_receipt.json').exists():
 raise ValueError('completion/import receipt already exists; inspect before resuming')
def save(path,value): path.write_text(json.dumps(value,indent=2)+'\n')
def run(args,name):
 with (HERE/name).open('w') as log:subprocess.run(args,cwd=ROOT,stdout=log,stderr=subprocess.STDOUT,check=True)
with (ROOT/'build_ovl/work/land.lock').open('a+') as lock:
 fcntl.flock(lock,fcntl.LOCK_EX|fcntl.LOCK_NB)
 inputs,by=D.load_run(RUN,fresh=True)
 activation=json.loads((ACTIVATION/'activation_receipt.json').read_text())
 assert activation['status']=='PASS_GATES_CENSUS_PENDING'
 def check_approval_bindings():
  targets=activation['applied_target_sha256']
  assert len(targets)==60
  assert all(D.sha(ROOT/name)==digest for name,digest in targets.items())
  assert targets['tools/row_db.py']==activation['validator_supplement']['installed_sha256']
  assert D.sha(ROOT/activation['validator_supplement']['test'])==activation['validator_supplement']['test_sha256']
  assert D.sha(ROOT/activation['test_fixture_supplement']['path'])==activation['test_fixture_supplement']['sha256']
  assert D.sha(ROOT/'tools/tests/test_slus_module_member_scope.py')==activation['alias_fixture_sha256']
  for key,name in {'full_proof_sha256':'retire_sink/final_combined_receipt.json',
                   'ownership_receipt_sha256':'retire_sink/final_ownership_receipt.json',
                   'overlay_gate_receipt_sha256':'retire_sink/overlay_gate/receipt.json',
                   'proof_input_pins_sha256':'retire_sink/final_source_pins.json'}.items():
   assert D.sha(HERE/name)==activation['candidate_evidence'][key]
 check_approval_bindings()
 assert activation['ownership']['modules']==33 and activation['ownership']['rows']==59
 assert activation['overlay_gate']['windows']==2175
 controls=json.loads((HERE/'production_controls/receipt.json').read_text())
 assert controls['status']=='PASS' and controls['passed']==60 and controls['skipped']==0
 assert controls['tool_fingerprint']==A.tool_fingerprint()==inputs['tool_fingerprint']
 previous=ROOT/'ledger/maspsx_dependence.jsonl'
 old_bytes=previous.read_bytes()
 old=D.unique(D.read_lines(previous),'id')
 proposal=json.loads((PROPOSAL/'receipt.json').read_text())
 assert proposal['status']=='FRESH_PRODUCTION_VALIDATED'
 assert proposal['previous_ledger_sha256']==hashlib.sha256(old_bytes).hexdigest()
 assert proposal['run_receipt_sha256']==D.sha(RUN/'receipt.json')
 new_bytes=(PROPOSAL/'maspsx_dependence.proposed.jsonl').read_bytes()
 assert D.sha(PROPOSAL/'maspsx_dependence.proposed.jsonl')==proposal['proposed_ledger_sha256']
 expected,removed=D.project(by,old,'docs/evidence/gp_partition_only/production_transition/README.md')
 assert D.read_lines(PROPOSAL/'maspsx_dependence.proposed.jsonl')==expected
 assert len(old)==189 and len(expected)==167 and len(removed)==22
 assert removed==json.loads((HERE/'dependency_projection/receipt.json').read_text())['removed']
 assert {r['id'] for r in expected if r['cause']!=old[r['id']]['cause']}=={'slus/code','slus/code2'}
 certs_before=T.check_certificates()
 # Compare every active object structurally; private-root file metadata may differ.
 edges=edges_of((ROOT/'build_slus/build.ninja').read_text())
 assert len(edges)==860
 fixture=HERE/'retire_sink/combined_final_fixture'
 object_hashes={}
 raw_object_differences=[]
 from objread import read_elf
 for edge in edges:
  live=ROOT/'build_slus'/edge['out']; private=fixture/'build_slus'/edge['out']
  left,right=read_elf(live.read_bytes()),read_elf(private.read_bytes())
  assert left==right and not left.unknown,edge['out']
  if live.read_bytes()!=private.read_bytes():raw_object_differences.append(edge['out'])
  object_hashes[edge['out']]=D.sha(live)
 save(HERE/'production_object_hashes.json',object_hashes)
 (HERE/'production_previous_dependence.jsonl').write_bytes(old_bytes)
 pending=previous.with_suffix('.jsonl.tmp')
 pending.write_bytes(new_bytes);pending.replace(previous)
 receipt={'status':'IMPORTED_REFRESH_PENDING','before_sha256':hashlib.sha256(old_bytes).hexdigest(),
          'after_sha256':D.sha(previous),'census_receipt_sha256':D.sha(RUN/'receipt.json'),
          'proposal_receipt_sha256':D.sha(PROPOSAL/'receipt.json'),'removed':removed,
          'before_dependencies':189,'after_dependencies':167,'added':[],
          'fresh_production_keys_validated':True,'private_keys_imported':False}
 save(HERE/'production_import_receipt.json',receipt)
 run([sys.executable,'tools/levels.py'],'production_levels.log')
 run([sys.executable,'tools/status.py'],'production_status.log')
 run([sys.executable,'tools/row_db.py','check'],'production_row_db.log')
 assert T.check_certificates()==certs_before
 registry=D.unique(D.read_lines(ROOT/'ledger/rows.jsonl'),'id')
 D.validate_fresh(inputs,by,registry)
 check_approval_bindings()
 assert D.sha(previous)==proposal['proposed_ledger_sha256']
 levels=D.unique(D.read_lines(ROOT/'ledger/levels.jsonl'),'id')
 assert set(levels)==set(registry)
 pilot={rid:levels[rid] for rid in ['slus/konami_runtime_w_8003C634','slus/konami_runtime_w_8003C758','slus/konami_runtime_w_8003C920']}
 assert [r['level'] for r in pilot.values()]==[5,4,5]
 containers=defaultdict(Counter)
 for rid,r in by.items():
  c=containers[r['container']];c['rows']+=1;c['genuine_common']+=bool(r['exact_versions'])
  c['dependencies']+=not bool(r['exact_versions']);c['masked_words']+=r['maspsx_retail']['masked']
  c['masked_rows']+=r['maspsx_retail']['masked']>0
 assert not any(r.get('n_gp_externs') for r in by.values())
 assert '_sink_call_separated_la' not in (ROOT/'tools/maspsx/maspsx/__init__.py').read_text()
 physical=[unit for r in by.values() for unit in R.physical_units(r)]
 assert not any('_sink_call_separated_la' in (r.get('fired') or {}) for r in [*by.values(),*physical])
 receipt.update(status='PASS',levels_sha256=D.sha(ROOT/'ledger/levels.jsonl'),status_sha256=D.sha(ROOT/'STATUS.md'),
                proof_inputs_unchanged=True,placement_certificates_unchanged=True)
 save(HERE/'production_import_receipt.json',receipt)
 summary={'rows':len(by),'genuine_common':sum(bool(r['exact_versions']) for r in by.values()),
          'dependencies':len(expected),'containers':dict(containers),
          'external_gp_rows':0,'sink_pass_present':False,
          'retail_scope_counts_differ':proposal['retail_scope_counts_differ'],
          'data_only_rows':proposal['data_only_rows_without_instruction_comparison'],
          'masked_words':sum(r['maspsx_retail']['masked'] for r in by.values()),
          'masked_rows':sum(r['maspsx_retail']['masked']>0 for r in by.values())}
 save(RUN/'report/summary.json',summary)
 result={'status':'PASS','completed_utc':time.strftime('%Y-%m-%dT%H:%M:%SZ',time.gmtime()),
 'owner_approval':'Explicit user approval on 2026-09-25: apply transition, run gates and wrap up.',
 'patch_sha256':'6fc7ead242d82bac80b18ccfce92e3d12a7e24fb6054a8099607383e0d095da8',
 'activation_receipt_sha256':D.sha(ACTIVATION/'activation_receipt.json'),
 'validator_supplement':activation['validator_supplement'],
 'slus_gate':activation['slus_gate'],'overlay_gate':activation['overlay_gate'],
 'tests':{'slus':166,'configure_slus':8,'assembler':418,'controls':60},
 'ownership':activation['ownership'],'placement_certificates':certs_before,
 'active_objects':860,'object_parsed_sections_symbols_relocations_equal_private_proof':True,
 'raw_object_differences':raw_object_differences,'object_hashes_sha256':D.sha(HERE/'production_object_hashes.json'),
 'census':summary,'census_receipt_sha256':D.sha(RUN/'receipt.json'),
 'import_receipt_sha256':D.sha(HERE/'production_import_receipt.json'),
 'pilot_levels':pilot,'levels_sha256':D.sha(ROOT/'ledger/levels.jsonl'),'status_sha256':D.sha(ROOT/'STATUS.md'),
 'row_database':'PASS','proof_inputs_unchanged':True,'fresh_tool_fingerprint':A.tool_fingerprint(),
 'main_coverage':'Three unregistered C gaps remain; evidence-backed fallback documented in main_kernel_coverage_audit.md and main_kernel_callers/REPORT.md.',
 'parked_movie_rows':22,'followups':['H28 source reconstructions','egcs proxy question','Remaining 167 assembler dependencies'],
 'script_sha256':D.sha(__file__)}
 save(OUT,result)
 print(json.dumps({'status':'PASS','receipt':str(OUT),'dependencies':167,'removed':22,'owners':33}),flush=True)
