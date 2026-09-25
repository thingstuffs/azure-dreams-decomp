#!/usr/bin/env python3
"""Measure production after approved activation; leave import for root review."""
import fcntl
import json
from pathlib import Path
import subprocess
import sys
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[2]
activation=HERE/'activation_runs/20260925T010431Z_625211_resumed3/activation_receipt.json'
assert json.loads(activation.read_text())['status']=='PASS_GATES_CENSUS_PENDING'
with (ROOT/'build_ovl/work/land.lock').open('a+') as lock:
 fcntl.flock(lock,fcntl.LOCK_EX|fcntl.LOCK_NB)
 subprocess.run([sys.executable,str(HERE/'production_controls.py')],cwd=ROOT,check=True)
 subprocess.run([sys.executable,str(HERE/'census_runner.py'),'--fixture',str(ROOT),
                 '--output',str(HERE/'production_census'),'--workers','4'],cwd=ROOT,check=True)
 report=HERE/'production_census/report'
 report.mkdir()
 with (report/'tables.md').open('w') as log:
  subprocess.run([sys.executable,'tools/fidelity/aspsx_report.py','--journal',str(HERE/'production_census/journal.jsonl'),
                  '--out-dir',str(report)],cwd=ROOT,stdout=log,check=True)
 subprocess.run([sys.executable,str(HERE/'dependency_import.py'),'--run',str(HERE/'production_census'),
   '--output',str(HERE/'production_dependency_proposal'),'--fresh-production',
   '--source','docs/evidence/gp_partition_only/production_transition/README.md'],cwd=ROOT,check=True)
print('FRESH_PRODUCTION_CENSUS_AND_PROPOSAL_READY_FOR_REVIEW',flush=True)
