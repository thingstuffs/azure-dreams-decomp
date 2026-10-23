"""Real flock contention across make jobservers and nested compile wrappers."""
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

from tools.build import compile_slots as S

_SAVED_ENV = {}


def setUpModule():
    # Tests assume default switches; a landing may export AZURE_* overrides.
    for key in [k for k in os.environ if k.startswith('AZURE_')]:
        _SAVED_ENV[key] = os.environ.pop(key)


def tearDownModule():
    os.environ.update(_SAVED_ENV)



class SlotTests(unittest.TestCase):
    def test_default_pool_ignores_per_root_tmpdir(self):
        with patch.dict(os.environ, {'TMPDIR': '/per-root/tmp'}, clear=True):
            self.assertEqual(S.slot_directory(), Path('/tmp')/('azure-compile-'+str(os.getuid())))

    def test_limit_validation(self):
        with patch.dict(os.environ, AZURE_COMPILE_LIMIT='0'):
            with self.assertRaises(ValueError):
                S.slot_count()

    def test_conflicting_pool_limit_refused(self):
        with tempfile.TemporaryDirectory() as td, patch.dict(os.environ,
                AZURE_COMPILE_SLOTS=td, AZURE_COMPILE_LIMIT='1'):
            with S.acquire():
                pass
            with patch.dict(os.environ, AZURE_COMPILE_LIMIT='2'):
                with self.assertRaisesRegex(ValueError, 'differs'):
                    with S.acquire():
                        pass

    def test_four_jobserver_lanes_bound_to_two_slots(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            log = root/'slots.jsonl'
            env = dict(os.environ, AZURE_COMPILE_SLOTS=td, AZURE_COMPILE_LIMIT='2',
                       AZURE_COMPILE_LOG=str(log), AZURE_COMPILE_LIMIT_ENABLED='1')
            wrapper = str(Path(S.__file__).resolve())
            makefile = root/'Makefile'
            makefile.write_text('all: a b c d\n.PHONY: all a b c d\na b c d:\n\t' +
                sys.executable+' '+wrapper+' -- '+sys.executable+' '+wrapper+
                ' -- '+sys.executable+' -c "import time; time.sleep(0.06)"\n')
            jobs = [subprocess.Popen(['make', '-j4', '-f', str(makefile)], cwd=root,
                    stdout=subprocess.PIPE, stderr=subprocess.PIPE, env=env) for _ in range(4)]
            try:
                for job in jobs:
                    stdout, stderr = job.communicate(timeout=20)
                    self.assertEqual(job.returncode, 0, stderr.decode())
                    self.assertNotIn(b'jobserver', stderr)
            finally:
                for job in jobs:
                    if job.poll() is None:
                        job.kill()
                    job.wait()
            events = [json.loads(line) for line in log.read_text().splitlines()]
            active, peak = 0, 0
            for event in events:
                active += 1 if event['event'] == 'acquire' else -1
                peak = max(peak, active)
                self.assertGreaterEqual(active, 0)
            self.assertEqual((len(events), peak, active), (32, 2, 0))
            self.assertGreater(max(e['waited'] for e in events), 0.05)

    def test_exception_releases_slot(self):
        with tempfile.TemporaryDirectory() as td, patch.dict(os.environ,
                AZURE_COMPILE_SLOTS=td, AZURE_COMPILE_LIMIT='1'):
            with self.assertRaisesRegex(RuntimeError, 'test'):
                with S.acquire():
                    raise RuntimeError('test')
            with S.acquire():
                pass


if __name__ == '__main__':
    unittest.main()
