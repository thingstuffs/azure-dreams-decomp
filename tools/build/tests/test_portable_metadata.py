"""Canonical metadata preserves instructions and literal program strings."""
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

_SAVED_ENV = {}


def setUpModule():
    # Tests assume default switches; a landing may export AZURE_* overrides.
    for key in [k for k in os.environ if k.startswith('AZURE_')]:
        _SAVED_ENV[key] = os.environ.pop(key)


def tearDownModule():
    os.environ.update(_SAVED_ENV)



class MetadataTests(unittest.TestCase):
    def test_independent_roots_share_file_and_option_metadata_not_program_strings(self):
        origin = Path(__file__).resolve().parents[3]
        with tempfile.TemporaryDirectory() as td:
            roots = [Path(td)/name for name in ('first', 'second')]
            outputs, witnesses = [], []
            for root in roots:
                (root/'tools').mkdir(parents=True)
                (root/'config').mkdir()
                for name in ('ccproc.py', 'name_inputs.py'):
                    shutil.copyfile(origin/'tools/build'/name, root/'tools'/name)
                (root/'config/names.tsv').write_text('')
                trace = root/'trace.json'
                source = '\t.file 1 "'+str(root)+'/src/unit.c"\n# options: -I'+str(root)+'/include\n.ent unit\nunit:\njr $31\nnop\n.end unit\n.ascii "/literal/program/path"\n'
                result = subprocess.run([sys.executable, str(root/'tools/ccproc.py')], input=source,
                    capture_output=True, text=True, check=True, env=dict(os.environ,
                    CCPROC_CONFIG_ROOT=str(root), CCPROC_NAMES_TRACE=str(trace)))
                outputs.append(result.stdout)
                witnesses.append(json.loads(trace.read_text()))
                literal = '.ascii "'+str(root)+'/literal"\n'
                check = subprocess.run([sys.executable, str(root/'tools/ccproc.py')], input=literal,
                    capture_output=True, text=True, check=True, env=dict(os.environ,
                    CCPROC_CONFIG_ROOT=str(root)))
                self.assertIn(str(root)+'/literal', check.stdout)
            self.assertEqual(outputs[0], outputs[1])
            self.assertEqual(witnesses[0], witnesses[1])
            self.assertIn('.file 1 "src/unit.c"', outputs[0])
            self.assertIn('.ascii "/literal/program/path"', outputs[0])
            self.assertIn('jr $31\nnop', outputs[0])


if __name__ == '__main__':
    unittest.main()
