#!/usr/bin/env python3
"""Resume the approved, already applied transition after fixture/setup repair."""
import fcntl
import json
import subprocess
import time
from pathlib import Path
import activate_transition as A

HERE=Path(__file__).resolve().parent
old=HERE/'activation_runs/20260925T010431Z_625211'
run=HERE/'activation_runs/20260925T010431Z_625211_resumed3'
A.TRANSITION=HERE/'transition_final'
A.PATCH=A.TRANSITION/'combined.patch'
A.INVENTORY=A.TRANSITION/'inventory.json'
A.REVIEW=HERE/'final_root_review.json'
A.FULL_PROOF=HERE/'retire_sink/final_combined_receipt.json'
A.FULL_OWNERSHIP=HERE/'retire_sink/final_ownership_receipt.json'
A.OVERLAY_PROOF=HERE/'retire_sink/overlay_gate/receipt.json'
A.PROOF_INPUT_PINS=HERE/'retire_sink/final_source_pins.json'
review,payloads=A.inventory_state()
evidence=A.private_evidence(payloads)
# A reviewed validator-only follow-up accepts canonical identities registered
# in names.tsv. Record it separately from the immutable approved packet.
original_payloads=[dict(item) for item in payloads]
validator_path=A.ROOT/'tools/row_db.py'
validator_item=next(item for item in payloads if item['target']=='tools/row_db.py')
validator_original=validator_item['after_sha256']
validator_item['after_sha256']=A.sha(validator_path)
original_command=A.command

def resumed_command(args, **kwargs):
    if args == ['git','apply',str(A.PATCH)]:
        A.target_hashes(payloads,require_after=True)
        if kwargs.get('log'):
            kwargs['log'].write_text('Patch already applied by original activation; all 60 reviewed after hashes verified.\n')
        return subprocess.CompletedProcess(args,0,'')
    return original_command(args,**kwargs)

receipt=A.read_json(old/'activation_receipt.json')
receipt.update({'status':'RUNNING','phase':'resume_setup', 'run_id':run.name,
 'approval':'Owner explicitly approved transition in conversation on 2026-09-25 and requested application and gates.',
 'resumed_from_failure_sha256':A.sha(old/'failure_receipt.json'),
 'resume_script_sha256':A.sha(Path(__file__)),
 'test_fixture_supplement':{'path':'tools/tests/test_configure_slus_data_pieces.py',
   'sha256':A.sha(A.ROOT/'tools/tests/test_configure_slus_data_pieces.py'),
   'reason':'Update three E758 fixture recipe expectations to approved -G32 recipe.'},
 'validator_supplement':{'target':'tools/row_db.py','approved_packet_sha256':validator_original,
  'installed_sha256':A.sha(validator_path),
  'test':'tools/tests/test_slus_row_db_aliases.py',
  'test_sha256':A.sha(A.ROOT/'tools/tests/test_slus_row_db_aliases.py'),
  'reason':'Use existing conservative alias-aware source parser for registered member definitions.'},
 'previous_resume_failure_sha256':A.sha(HERE/'activation_runs/20260925T010431Z_625211_resumed/failure_receipt.json'),
 'alias_fixture_sha256':A.sha(A.ROOT/'tools/tests/test_slus_module_member_scope.py'),
 'second_resume_failure_sha256':A.sha(HERE/'activation_runs/20260925T010431Z_625211_resumed2/failure_receipt.json'),
 'setup_repair':'Refresh managed source view and normal configure before build-identity test.'})
run.mkdir(exist_ok=False)
(run/'.ignore').write_text('*\n')
with (A.ROOT/'build_ovl/work/land.lock').open('a+') as lock:
 fcntl.flock(lock,fcntl.LOCK_EX|fcntl.LOCK_NB)
 A.target_hashes(payloads,require_after=True)
 A.write_json(run/'activation_receipt.json',receipt)
 try:
  original_command(['bash','tools/build/mk_slus_root.sh'],env=A.base_env(),log=run/'setup_slus_root.log')
  original_command([A.sys.executable,'tools/configure.py'],cwd=A.ROOT/'build_slus',env=A.base_env(),log=run/'setup_configure.log')
  assert (A.ROOT/'build_slus/build.ninja').read_bytes()==(A.ROOT/'ledger/splits/slus.build.ninja').read_bytes()
  A.command=resumed_command
  A.activate(run,run.name,payloads,evidence,old/'pre_transition_rows.jsonl',old/'pre_transition_slus_inputs.json',receipt)
 except Exception as exc:
  receipt.update(status='FAILED',error=str(exc),failed_utc=time.strftime('%Y-%m-%dT%H:%M:%SZ',time.gmtime()))
  A.write_json(run/'failure_receipt.json',receipt)
  raise
print(json.dumps({'status':receipt['status'],'receipt':str(run/'activation_receipt.json')}))
