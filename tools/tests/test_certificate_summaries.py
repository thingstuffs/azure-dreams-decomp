"""Portable summaries must preserve the full validator's authority boundary."""
import hashlib
import json
from pathlib import Path
import shutil
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import certificate_summaries as summaries


class CertificateSummaryTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.key = 'fixture'
        self.fingerprint = {'schema': 'fixture', 'sha256': 'a' * 64}
        self.cert = {'module': self.key, 'kind': 'overlay_module_placement',
                     'at': '2026-10-20T00:00:00Z', 'reviewer': 'fixture-reviewer',
                     'members': ['town/func_80000000'], 'fingerprint': self.fingerprint,
                     'proof_dir': 'work/private/module',
                     'windows': [{'config': 'config/overlays/fixture.overlay.yaml',
                                  'result': 'MATCH', 'file_start': 0, 'file_end': 4,
                                  'digest': 'b' * 64, 'proof_dir': 'work/private/window'}]}
        self.certificate, self.summary = summaries.paths(self.root, self.key)
        self.certificate.parent.mkdir(parents=True)
        self.write_certificate()
        for name in ('module', 'window'):
            out = self.root / 'work/private' / name
            out.mkdir(parents=True)
            (out / 'receipt.json').write_text('{"fixture":true}\n')
        self.authority = (self.cert, SimpleNamespace(fingerprint=lambda *_: self.fingerprint),
                          lambda *_: None)
        self.mock_authority = patch.object(summaries, 'authorities', return_value=self.authority)
        self.mock_authority.start()
        self.addCleanup(self.mock_authority.stop)

    def write_certificate(self):
        self.certificate.write_text(json.dumps(self.cert) + '\n')

    def export(self):
        return summaries.export_summary(self.root, self.key)

    def rewrite_summary(self, mutate):
        doc = json.loads(self.summary.read_text())
        mutate(doc)
        self.summary.write_text(json.dumps(doc))

    def test_fresh_checkout_reports_recorded_current_without_placement_grant(self):
        self.export()
        shutil.rmtree(self.root / 'work/private')
        state = summaries.summary_status(self.root, self.key)
        self.assertEqual(state, {'module': self.key, 'recorded': 'bound',
                                 'inputs': 'current', 'replayed_here': False})
        self.assertNotIn('valid', state)
        text = summaries.status_text(self.root)
        self.assertIn('1 inputs current', text)
        self.assertIn('do not change certificate placement or L4/L5', text)

    def test_export_calls_existing_validator(self):
        with patch.object(summaries, 'authorities', return_value=(self.cert, self.authority[1],
                          lambda *_: 'module artifact changed')):
            with self.assertRaisesRegex(ValueError, 'not current'):
                self.export()
        self.assertFalse(self.summary.exists())

    def test_missing_private_proof_cannot_be_invented(self):
        shutil.rmtree(self.root / 'work/private')
        with self.assertRaises(FileNotFoundError):
            self.export()
        self.assertFalse(self.summary.exists())

    def test_changed_certificate_invalidates_binding(self):
        self.export()
        self.cert['reviewer'] = 'another-reviewer'
        self.write_certificate()
        self.assertEqual(summaries.summary_status(self.root, self.key)['recorded'], 'invalid')

    def test_changed_source_fingerprint_is_stale(self):
        self.export()
        gate = SimpleNamespace(fingerprint=lambda *_: {'sha256': 'c' * 64})
        with patch.object(summaries, 'authorities', return_value=(self.cert, gate, lambda *_: None)):
            self.assertEqual(summaries.summary_status(self.root, self.key)['inputs'], 'changed')

    def test_missing_compiler_or_retail_is_unchecked(self):
        self.export()
        with patch.object(summaries, 'authorities', side_effect=FileNotFoundError('compiler')):
            self.assertEqual(summaries.summary_status(self.root, self.key),
                             {'module': self.key, 'recorded': 'bound',
                              'inputs': 'unavailable', 'replayed_here': False})

    def test_proof_inventory_reproducible_and_complete(self):
        before = summaries.proof_inventory(self.root, self.cert)
        self.assertEqual(before, summaries.proof_inventory(self.root, self.cert))
        self.assertEqual(before['files'], 2)
        (self.root / 'work/private/window/additional.log').write_text('extra')
        after = summaries.proof_inventory(self.root, self.cert)
        self.assertNotEqual(before['sha256'], after['sha256'])
        self.assertEqual(after['files'], 3)

    def test_proof_change_during_validation_refused(self):
        def validator(*_):
            (self.root / 'work/private/module/receipt.json').write_text('changed')
            return None
        with patch.object(summaries, 'authorities', return_value=(self.cert, self.authority[1], validator)):
            with self.assertRaisesRegex(ValueError, 'changed during export'):
                self.export()
        self.assertFalse(self.summary.exists())

    def test_symlink_and_escaping_proofs_refused(self):
        directory = self.root / 'work/private/module'
        (directory / 'linked.json').symlink_to(directory / 'receipt.json')
        with self.assertRaisesRegex(ValueError, 'linked'):
            self.export()
        for name in ('../outside', '/outside'):
            with self.assertRaises(ValueError):
                summaries.safe_path(self.root, name)

    def test_invalid_and_oversize_summaries_fail_closed(self):
        self.export()
        self.rewrite_summary(lambda d: d.update(module_result={'retail': 'MATCH'}))
        self.assertEqual(summaries.summary_status(self.root, self.key)['recorded'], 'invalid')
        self.summary.write_text(' ' * summaries.LIMIT)
        self.assertEqual(summaries.summary_status(self.root, self.key)['recorded'], 'invalid')
        self.summary.write_text('{broken')
        self.assertEqual(summaries.summary_status(self.root, self.key)['recorded'], 'invalid')

    def test_scope_changes_and_extra_fields_are_invalid(self):
        self.export()
        self.rewrite_summary(lambda d: d['windows'][0].update(file_end=8))
        self.assertEqual(summaries.summary_status(self.root, self.key)['recorded'], 'invalid')
        self.export()
        self.rewrite_summary(lambda d: d.update(retail_bytes='must never be copied'))
        self.assertEqual(summaries.summary_status(self.root, self.key)['recorded'], 'invalid')

    def test_absent_summary_does_not_load_build_tools(self):
        with patch.object(summaries, 'authorities', side_effect=AssertionError('should not import')):
            self.assertEqual(summaries.summary_status(self.root, self.key)['recorded'], 'absent')

    def test_summary_only_contains_fixed_metadata_and_hashes(self):
        self.export()
        data = self.summary.read_bytes()
        self.assertLess(len(data), summaries.LIMIT)
        self.assertNotIn(str(self.root).encode(), data)
        self.assertNotIn(b'fixture":true', data)
        doc = json.loads(data)
        self.assertEqual(set(doc), summaries.FIELDS)
        self.assertEqual(doc['certificate_sha256'], hashlib.sha256(self.certificate.read_bytes()).hexdigest())


if __name__ == '__main__':
    unittest.main()
