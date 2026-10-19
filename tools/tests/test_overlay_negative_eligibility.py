"""Excluded neighbours remain explicit fingerprint inputs without fabricated facts."""
import hashlib
import json
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'gate'))
import overlay_scoped_fingerprint as fingerprint


class NegativeEligibility(unittest.TestCase):
    def test_seed_record_binds_explicit_ineligibility(self):
        record = {'id': 'town/example', 'level': -1, 'reason': 'excluded'}
        self.assertEqual(fingerprint.row_eligibility({}, record), {'l3': False, 'pins': None, 'tail_jumps': None, 'residue': ['unleveled'], 'level': -1})

    def test_seed_level_change_invalidates_digest(self):
        def digest(record):
            return hashlib.sha256(json.dumps(fingerprint.row_eligibility({}, record), sort_keys=True).encode()).hexdigest()
        before = {'id': 'town/example', 'level': -1}
        after = dict(before, level=-2)
        self.assertNotEqual(digest(before), digest(after))

    def test_missing_record_remains_absent(self):
        self.assertIsNone(fingerprint.row_eligibility({}, None))

    def test_eligible_record_keeps_existing_projection(self):
        record = {'level': 3, 'pins_left': 0, 'tail_jumps': 0, 'l4_residue': ['not_in_module']}
        self.assertEqual(fingerprint.row_eligibility({}, record), {'l3': True, 'pins': 0, 'tail_jumps': 0, 'residue': []})

    def test_eligible_record_missing_measurements_is_refused(self):
        with self.assertRaises(KeyError):
            fingerprint.row_eligibility({}, {'level': 3})


if __name__ == '__main__':
    unittest.main()
