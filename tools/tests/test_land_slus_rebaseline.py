"""Exercise admission and rollback using disposable instrumented build tools."""
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

TOOLS = Path(__file__).resolve().parents[1]


class RebaselineScriptTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR'))
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        self.old = 'volatile int x; ASM_USE(x);\n'
        self.new = 'int x; ASM_USE(x);\n'
        for p, text in {
            'src/slus/demo.c': self.old,
            'candidate.c': self.new,
            'ledger/cache/slus_obj.json': '{"slus/demo":{"old":true},"slus/other":{"keep":true}}',
            'ledger/cache/slus_dis/demo.txt': 'old disassembly\n',
            'ledger/levels.jsonl': 'old levels\n',
            'STATUS.md': 'old status\n',
            'ledger/splits/slus.build.ninja': 'pinned recipe\n',
            'build_slus/build.ninja': 'pinned recipe\n',
            'tools/common.py': "from pathlib import Path\nROOT=Path(__file__).resolve().parents[1]\ndef rows(): return [{'id':'slus/demo'}]\ndef clean_path(r): return ROOT/'src/slus/demo.c'\n",
            'tools/pin_census.py': "import re\ndef sites_of(t):return [('x','ASM_USE') for _ in re.findall(r'ASM_USE\\(',t)]\ndef landing_refusal(new,cur,*a,**kw):return 'port refusal' if 'REFUSE' in new else None\n",
            'tools/levels.py': "from pathlib import Path\ndef live_fidelity_sites(*a):return []\nif __name__=='__main__':\n Path('ledger/levels.jsonl').write_text('new levels')\n if Path('mode').read_text()=='levels':raise SystemExit(9)\n",
            'tools/status.py': "from pathlib import Path\nPath('STATUS.md').write_text('new status')\nif Path('mode').read_text()=='status':raise SystemExit(9)\n",
            'tools/verify.py': "import json,sys\nfrom pathlib import Path\nmode=Path('mode').read_text()\nif '--rebaseline-slus' in sys.argv:\n Path('ledger/cache/slus_obj.json').write_text('{\"rebaselined\":true}')\n Path('ledger/cache/slus_dis/demo.txt').write_text('new disassembly')\n if mode=='rebaseline':raise SystemExit(9)\nelse:\n print(json.dumps({'exact':mode!='verify','err':'\\\"exact\\\": true'}))\n",
            'tools/build/build_slus.sh': "#!/bin/bash\nset -eu\necho run >> build_calls\nmode=$(cat mode)\n[ \"$mode\" != build ] || exit 9\npython3 - <<'PY'\nimport json\nfrom pathlib import Path\nm=Path('mode').read_text()\nr={'result':'NO MATCH' if m=='gate' else 'MATCH','recipe_vs_pinned':'DIFFERS' if m=='pinned' else 'identical'}\nwith Path('ledger/gate_slus.jsonl').open('a') as f:f.write(json.dumps(r)+'\\n')\nif m=='recipe':Path('build_slus/build.ninja').write_text('wrong recipe')\nPY\n",
        }.items():
            self.put(p, text)
        self.put('mode', 'success')
        self.put('candidate.c.base_sha', hashlib.sha256(self.old.encode()).hexdigest())
        self.put('tools/lanes/land_slus_rebaseline.sh', (TOOLS/'lanes/land_slus_rebaseline.sh').read_text())
        self.put('tools/land_admit.py', (TOOLS/'land_admit.py').read_text())

    def put(self, name, text):
        p = self.root/name; p.parent.mkdir(parents=True, exist_ok=True); p.write_text(text)

    def invoke(self, equal=True):
        args = ['bash', str(self.root/'tools/lanes/land_slus_rebaseline.sh')]
        if equal:
            args.append('--equal-pins')
        return subprocess.run(args+['slus/demo', str(self.root/'candidate.c'), 'test'],
                              cwd=self.root, capture_output=True, text=True, timeout=15,
                              env=dict(os.environ, TMPDIR=str(self.root), PYTHONDONTWRITEBYTECODE='1'))

    def test_default_mode_still_requires_fewer_asm_pins(self):
        r = self.invoke(False)
        self.assertNotEqual(r.returncode, 0); self.assertIn('pins did not fall', r.stdout)
        self.assertFalse((self.root/'build_calls').exists())
        self.put('candidate.c', 'int x;\n')
        r = self.invoke(False)
        self.assertEqual(r.returncode, 0, r.stdout+r.stderr); self.assertIn('LANDED', r.stdout)

    def test_equal_mode_rejects_stale_growth_no_reduction_and_changed_pins(self):
        for candidate, base, expected in [
            (self.new, '0'*64, 'stale'),
            ('goto done; ASM_USE(x);\n', None, 'grew'),
            (self.old.replace('x;', 'x ;'), None, 'fell []'),
            ('int x;\n', None, 'unchanged pins'),
            (self.new+'REFUSE', None, 'port refusal'),
        ]:
            with self.subTest(expected=expected):
                self.put('candidate.c', candidate)
                self.put('candidate.c.base_sha', base or hashlib.sha256(self.old.encode()).hexdigest())
                r = self.invoke()
                self.assertNotEqual(r.returncode, 0, r.stdout+r.stderr)
                self.assertIn(expected, r.stdout)
                self.assertEqual((self.root/'src/slus/demo.c').read_text(), self.old)
                self.assertFalse((self.root/'build_calls').exists())

    def test_equal_mode_requires_full_gate_rebaseline_and_exact(self):
        r = self.invoke()
        self.assertEqual(r.returncode, 0, r.stdout+r.stderr)
        self.assertIn('LANDED', r.stdout)
        self.assertEqual((self.root/'src/slus/demo.c').read_text(), self.new)
        receipt = json.loads((self.root/'ledger/slus_rebaseline_landings.jsonl').read_text())
        self.assertTrue(receipt['equal_pins'])

    def test_every_proof_and_accounting_failure_restores_persistent_inputs(self):
        paths = ['src/slus/demo.c', 'ledger/cache/slus_obj.json',
                 'ledger/cache/slus_dis/demo.txt', 'ledger/levels.jsonl', 'STATUS.md']
        before = {name:(self.root/name).read_bytes() for name in paths}
        for mode in ['build', 'gate', 'pinned', 'recipe', 'rebaseline', 'verify', 'levels', 'status']:
            with self.subTest(mode=mode):
                self.put('mode', mode)
                self.put('build_slus/build.ninja', 'pinned recipe\n')
                (self.root/'build_calls').unlink(missing_ok=True)
                r = self.invoke()
                self.assertNotEqual(r.returncode, 0, r.stdout+r.stderr)
                self.assertIn('REVERTED', r.stdout+r.stderr)
                self.assertEqual(before, {name:(self.root/name).read_bytes() for name in paths})
                self.assertFalse((self.root/'ledger/slus_rebaseline_landings.jsonl').exists())
                self.assertEqual((self.root/'build_calls').read_text().splitlines(), ['run', 'run'])

    def test_failure_restores_absence_of_a_previously_missing_reference(self):
        (self.root/'ledger/cache/slus_obj.json').unlink()
        (self.root/'ledger/cache/slus_dis/demo.txt').unlink()
        self.put('mode', 'verify')
        r = self.invoke()
        self.assertNotEqual(r.returncode, 0, r.stdout+r.stderr)
        self.assertFalse((self.root/'ledger/cache/slus_obj.json').exists())
        self.assertFalse((self.root/'ledger/cache/slus_dis/demo.txt').exists())


if __name__ == '__main__':
    unittest.main()
