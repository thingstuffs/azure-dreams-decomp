"""Detailed accounting results retain canonical reader metadata in spawn workers."""
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

TOOLS=Path(__file__).resolve().parents[1]

class DetailedStatuses(unittest.TestCase):
    def test_serial_parallel_success_failure_and_metadata_are_identical(self):
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as name:
            root=Path(name);(root/'tools').mkdir();(root/'ledger/modules').mkdir(parents=True)
            mods=[dict(key='b',members=[dict(id='town/b')],review={'reviewer':'bob'}),
                  dict(key='a',members=[dict(id='town/a')],review={'reviewer':'alice'})]
            (root/'modules.json').write_text(json.dumps(mods))
            (root/'tools/overlay_module_evidence.py').write_text('''import json
from pathlib import Path
def load_modules(root):return json.loads((root/'modules.json').read_text())
def certificate_reason(m,c,root):return c.get('reason')
def module_status(root):
 out=[]
 for m in load_modules(root):
  c=json.loads((root/'ledger/modules'/('overlay_'+m['key']+'.json')).read_text());reason=certificate_reason(m,c,root)
  out.append(dict(module=m,certificate=c,valid=reason is None,reason=reason))
 return out
''')
            for key,reason in [('a','artifact corrupted'),('b',None)]:
                (root/'ledger/modules'/('overlay_'+key+'.json')).write_text(json.dumps(dict(module=key,reason=reason,fingerprint={'sha256':key})))
            code="import sys,json;from pathlib import Path;sys.path.insert(0,sys.argv[1]);from certify_batch import _statuses;root=Path(sys.argv[2]);a=_statuses(root,1);b=_statuses(root,2,details=True);c=_statuses(root,2);assert a==b,(a,b);assert all(set(x)=={'module','reason','valid'} for x in c);print(json.dumps(b))"
            proc=subprocess.run([sys.executable,'-c',code,str(TOOLS/'lanes'),str(root)],capture_output=True,text=True,timeout=30,start_new_session=True)
            self.assertEqual(proc.returncode,0,proc.stdout+proc.stderr)
            result=json.loads(proc.stdout)
            self.assertEqual(result[0]['module'],mods[0]);self.assertTrue(result[0]['valid'])
            self.assertFalse(result[1]['valid']);self.assertEqual(result[1]['reason'],'artifact corrupted')

if __name__=='__main__':unittest.main()
