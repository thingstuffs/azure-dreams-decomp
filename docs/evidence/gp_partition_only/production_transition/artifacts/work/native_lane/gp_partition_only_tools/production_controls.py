#!/usr/bin/env python3
"""Run all validation controls on production with isolated short ASPSX scratch."""
import contextlib
import hashlib
import json
import os
from pathlib import Path
import shutil
import sys
import tempfile
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[2]
for name in ('AZURE_MASPSX','AZURE_MASPSX_COMPANION','PYTHONPATH'):
 os.environ.pop(name,None)
sys.path[:0]=[str(ROOT/'tools'),str(ROOT/'tools/fidelity'),str(ROOT/'tools/build')]
import common
from fidelity import aspsx_diff as A
assert common.ROOT==A.ROOT==ROOT
out=HERE/'production_controls'
out.mkdir(exist_ok=False)
(out/'.ignore').write_text('*\n')
def sha(path):return hashlib.sha256(Path(path).read_bytes()).hexdigest()
before=A.tool_fingerprint()
objects={str(p.relative_to(ROOT)):sha(p) for p in (ROOT/'build_slus/build/src').glob('*.o')}
A.TMP=Path(tempfile.mkdtemp(prefix='pctrl_',dir='/tmp'))
A._SLUS=None
with (out/'controls.log').open('w') as log,contextlib.redirect_stdout(log):
 failures=A.run_controls({r['id']:r for r in common.rows()})
lines=(out/'controls.log').read_text().splitlines()
passed=sum(line.startswith('PASS  ') for line in lines)
failed=sum(line.startswith('FAIL  ') for line in lines)
skipped=sum(line.startswith('SKIP  ') for line in lines)
unchanged=objects=={str(p.relative_to(ROOT)):sha(p) for p in (ROOT/'build_slus/build/src').glob('*.o')}
assert A.tool_fingerprint()==before and unchanged
result={'status':'PASS' if not failures and passed==60 and failed==skipped==0 else 'FAIL',
 'passed':passed,'failed':failed,'skipped':skipped,'failures_returned':failures,
 'production_root':str(ROOT),'tool_fingerprint':before,'production_objects_unchanged':unchanged,
 'script_sha256':sha(__file__),'log_sha256':sha(out/'controls.log')}
(out/'receipt.json').write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps(result),flush=True)
if result['status']=='PASS':shutil.rmtree(A.TMP)
else:raise SystemExit(1)
