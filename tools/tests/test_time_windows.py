import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import time
import unittest

HELPER = Path(__file__).resolve().parents[1] / 'lanes/time_windows.py'


class TimeWindowsTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR'))
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        (self.root / 'tools').mkdir()
        (self.root / 'config/overlays').mkdir(parents=True)
        self.configs = ['config/overlays/a.overlay.yaml', 'config/overlays/b.overlay.yaml']
        for config in self.configs:
            (self.root / config).write_text('name: ' + Path(config).stem + '\nstandalone_build: {work_dir: work}\n')
        self.gate("print('MATCH (4 bytes)')\n")

    def gate(self, text):
        (self.root / 'tools/overlay_local_gate.py').write_text(text)

    def run_helper(self, configs=None, workers=2, timeout=5):
        argv = [sys.executable, str(HELPER), '--root', str(self.root), '--workers', str(workers),
                '--timeout', str(timeout), '--log-dir', str(self.root / 'logs')]
        for config in configs or self.configs:
            argv.extend(['--config', config])
        return subprocess.run(argv, capture_output=True, text=True, start_new_session=True, timeout=15)

    def test_both_gates_require_match_and_preserve_clean_and_config_arguments(self):
        self.gate("import json, sys\nassert '--clean' in sys.argv\nprint(json.dumps(sys.argv))\nprint('MATCH (4 bytes)')\n")
        result = self.run_helper()
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        summary = json.loads((self.root / 'logs/summary.json').read_text())
        self.assertEqual([r['config'] for r in summary['windows']], self.configs)
        for row in summary['windows']:
            argv = json.loads(Path(row['log']).read_text().splitlines()[0])
            self.assertEqual(argv[argv.index('--config') + 1], row['config'])

    def test_gates_overlap_with_two_workers_and_serialize_with_one(self):
        self.gate("import json, sys, time\nfrom pathlib import Path\np=Path(sys.argv[sys.argv.index('--config')+1]).stem\nstart=time.monotonic()\ntime.sleep(.25)\nPath(p+'.interval').write_text(json.dumps([start,time.monotonic()]))\nprint('MATCH')\n")
        result = self.run_helper()
        self.assertEqual(result.returncode, 0, result.stderr)
        a, b = [json.loads((self.root / (Path(c).stem + '.interval')).read_text()) for c in self.configs]
        self.assertLess(max(a[0], b[0]), min(a[1], b[1]))
        result = self.run_helper(workers=1)
        self.assertEqual(result.returncode, 0, result.stderr)
        a, b = [json.loads((self.root / (Path(c).stem + '.interval')).read_text()) for c in self.configs]
        self.assertGreaterEqual(b[0], a[1])

    def test_zero_exit_without_match_refuses(self):
        self.gate("print('NO MATCH')\n")
        result = self.run_helper()
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('lacks MATCH', result.stderr)
        self.assertFalse((self.root / 'logs/summary.json').exists())

    def test_nonzero_exit_even_with_match_refuses(self):
        self.gate("print('MATCH')\nraise SystemExit(1)\n")
        result = self.run_helper()
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('timed window failed', result.stderr)

    def test_timeout_stops_gate_and_grandchild_before_rollback(self):
        self.gate("import subprocess, sys, time\nfrom pathlib import Path\np=subprocess.Popen([sys.executable,'-c','import time;time.sleep(30)'])\nPath('grandchild.pid').write_text(str(p.pid))\ntime.sleep(30)\n")
        result = self.run_helper(configs=self.configs[:1], timeout=1)
        self.assertNotEqual(result.returncode, 0)
        pid = (self.root / 'grandchild.pid').read_text()
        for _ in range(30):
            state = Path('/proc') / pid / 'status'
            if not state.exists() or '\nState:\tZ' in state.read_text():
                break
            time.sleep(.02)
        else:
            self.fail('compiler descendant still running')
        self.assertFalse((self.root / 'logs/summary.json').exists())

    def test_duplicate_and_nonproduction_configs_refuse_before_launch(self):
        for configs in [self.configs[:1] * 2, ['../config/overlays/a.overlay.yaml'], ['config/other.yaml']]:
            with self.subTest(configs=configs):
                result = self.run_helper(configs=configs)
                self.assertNotEqual(result.returncode, 0)
                self.assertNotIn('timing-window-start', result.stdout)

    def test_worker_budget_is_enforced(self):
        for workers in [0, 5]:
            result = self.run_helper(workers=workers)
            self.assertNotEqual(result.returncode, 0)
            self.assertIn('one to four workers', result.stderr)

    def test_different_configs_with_same_clean_directory_refuse(self):
        (self.root / self.configs[1]).write_text((self.root / self.configs[0]).read_text())
        result = self.run_helper()
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('overlaps', result.stderr)
        self.assertNotIn('timing-window-start', result.stdout)

    def test_nested_clean_directories_refuse_before_either_gate_launches(self):
        (self.root / self.configs[1]).write_text('name: child\nstandalone_build: {work_dir: work/a.overlay}\n')
        result = self.run_helper()
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('overlaps', result.stderr)
        self.assertNotIn('timing-window-start', result.stdout)


if __name__ == '__main__':
    unittest.main()
