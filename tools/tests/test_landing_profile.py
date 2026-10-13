import json
import os
from pathlib import Path
import tempfile
import unittest

from tools.lanes import landing_profile as P


class LandingProfileTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR'))
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        self.log = self.root / 'sample.log'

    def write(self, events):
        self.log.write_text('\n'.join(json.dumps(e) for e in events) + '\n')
        return P.profile(self.log)

    def test_repeated_steps_accumulate_and_gate_diagnostic_is_not_double_counted(self):
        result = self.write([
            {'at': '2026-01-01T00:00:00Z', 'step': 'preflight'},
            {'step': 'registry', 'rc': 0, 'seconds': 2},
            {'step': 'registry', 'rc': 0, 'seconds': 3},
            {'step': 'gate-all', 'rc': 0, 'seconds': 10},
            {'step': 'gate-timing', 'mode': 'incremental', 'seconds': 10},
            {'at': '2026-01-01T00:00:20Z', 'step': 'COMMITTED', 'head': 'abc'}])
        self.assertEqual(result['command_seconds'], 15)
        self.assertEqual(result['unattributed_seconds'], 5)
        self.assertEqual(result['seconds_by_category']['regeneration'], 5)
        self.assertTrue(result['complete'])

    def test_partial_log_does_not_enter_success_statistics(self):
        result = self.write([{'step': 'gate-all', 'rc': 0, 'seconds': 2},
                             {'step': 'gate-timing', 'mode': 'full'}])
        self.assertFalse(result['complete'])
        self.assertEqual(result['terminal'], 'INCOMPLETE')
        self.assertNotIn('completed runs', P.markdown([result]))

    def test_rollback_bound_is_not_labeled_restore_time(self):
        result = self.write([
            {'step': 'preflight', 'at': '2026-01-01T00:00:00Z'},
            {'step': 'certificate-proof-preservation', 'at': '2026-01-01T00:00:06Z'},
            {'step': 'gate-all', 'rc': 1, 'seconds': 2, 'at': '2026-01-01T00:00:08Z'},
            {'step': 'STOP', 'rollback': {'status_identical': True}, 'at': '2026-01-01T00:00:13Z'}])
        self.assertEqual(result['interval_bounds_seconds'],
                         {'snapshot_plus_quarantine': 6, 'post_command_diagnostics_plus_restore': 5})
        self.assertFalse(result['complete'])

    def test_relocated_outputs_are_read_only_from_log_sibling(self):
        (self.root / 'gate.out').write_text('12 windows to gate (34 up to date), 4 workers\n')
        (self.root / 'cert.out').write_text(json.dumps({'result': 'PASS', 'certificates': [],
            'retained': ['a', 'b'], 'validated': 2, 'workers': 1}) + '\n')
        result = self.write([{'step': 'gate-all', 'command': ['gate'], 'output': '/abs/missing/gate.out'},
                             {'step': 'certify-all', 'command': ['cert'], 'output': '/abs/missing/cert.out'}])
        self.assertEqual(result['gate_windows'], {'built': 12, 'cached': 34, 'workers': 4})
        self.assertEqual(result['certificates']['renewed'], 0)
        self.assertEqual(result['certificates']['retained'], 2)

    def test_corrupt_json_is_visible_and_excludes_run_from_medians(self):
        self.log.write_text('{bad\n' + json.dumps({'step': 'COMMITTED'}) + '\n')
        result = P.profile(self.log)
        self.assertEqual(len(result['warnings']), 1)
        self.assertFalse(result['complete'])

    def test_invalid_duration_refuses(self):
        for value in [-1, float('nan'), True, '5']:
            with self.subTest(value=value), self.assertRaises(ValueError):
                self.write([{'step': 'gate-all', 'rc': 0, 'seconds': value}])

    def test_missing_output_is_unknown_not_zero_windows(self):
        result = self.write([{'step': 'gate-all', 'command': ['gate'], 'output': '/missing/log'}])
        self.assertIsNone(result['gate_windows'])


if __name__ == '__main__':
    unittest.main()
