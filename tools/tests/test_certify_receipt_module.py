"""Receipt-bound certification: the module proof is the gate's own, never rebuilt when receipts exist."""
import json
import os
from pathlib import Path
import shutil
import sys
import tempfile
import unittest
from unittest.mock import patch
REPO = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(REPO/'tools'), str(REPO/'tools/lanes')]
from fidelity import certify_overlay_module as C
import certify_batch as B

FP = {'schema': 'test', 'sha256': 'f'*64, 'windows': {'config/overlays/demo.overlay.yaml': {'sha256': 'w'*64}}}


def write_module_proof(directory, key='native', fingerprint=FP, candidates=None):
    directory.mkdir(parents=True, exist_ok=True)
    (directory/'OUT.OBJ').write_bytes(b'genuine object'); (directory/'module.bin').write_bytes(b'demo')
    receipt = {'schema': 'overlay-module-native-v4', 'module': key, 'members': ['dungeon/func_1'], 'fingerprint': fingerprint,
               'candidates': candidates or {}, 'candidate_paths': {k: '/x' for k in (candidates or {})},
               'artifacts': {n: C.sha(directory/n) for n in ('OUT.OBJ', 'module.bin')}}
    (directory/'receipt.json').write_text(json.dumps(receipt, indent=2) + '\n')
    return receipt


class AdoptTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')); self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name); self.m = {'key': 'native'}
        self.source = self.root/'win/module'; write_module_proof(self.source)
        self.dest = self.root/'module_proofs/native/module'

    def test_installs_the_gate_module_proof_replacing_stale_output(self):
        self.dest.mkdir(parents=True); (self.dest/'stale.o').write_bytes(b'old')
        r = C.adopt_window_module(self.m, self.source, self.dest, FP)
        self.assertEqual(r['module'], 'native'); self.assertFalse((self.dest/'stale.o').exists())
        self.assertEqual((self.dest/'receipt.json').read_bytes(), (self.source/'receipt.json').read_bytes())

    def test_refuses_other_module_fingerprint_or_candidate(self):
        for kw in ({'key': 'other'}, {'fingerprint': {**FP, 'sha256': '0'*64}}, {'candidates': {'src/x.c': 'h'}}):
            shutil.rmtree(self.source); write_module_proof(self.source, **kw)
            with self.assertRaisesRegex(ValueError, 'not this module'):
                C.adopt_window_module(self.m, self.source, self.dest, FP)

    def test_refuses_changed_artifact_and_links(self):
        (self.source/'OUT.OBJ').write_bytes(b'tampered')
        with self.assertRaisesRegex(ValueError, 'artifact changed'):
            C.adopt_window_module(self.m, self.source, self.dest, FP)
        (self.source/'OUT.OBJ').unlink(); (self.source/'OUT.OBJ').symlink_to(self.source/'module.bin')
        with self.assertRaisesRegex(ValueError, 'linked'):
            C.adopt_window_module(self.m, self.source, self.dest, FP)


class CertifyPathTests(unittest.TestCase):
    """certify() with receipts never calls build(); without receipts it still does."""
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')); self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        (self.root/'ledger/splits').mkdir(parents=True); (self.root/'ledger/splits/demo.jsonl').write_text('')
        (self.root/'overlays/demo').mkdir(parents=True); (self.root/'overlays/demo/overlay_first_pass_results.json').write_text('[]')
        self.wn = 'config/overlays/demo.overlay.yaml'; p = self.root/self.wn; p.parent.mkdir(parents=True)
        p.write_text('name: demo\nstandalone_build:\n  work_dir: work\n  split_results: overlays/demo/overlay_first_pass_results.json\n'
                     '  matched_sources: []\n  window:\n    file_start: 0\n    file_end: 4\n')
        (self.root/'work/disc/containers').mkdir(parents=True); (self.root/'work/disc/containers/DUNGEON_DUNGEON.BIN').write_bytes(b'demo')
        self.m = {'key': 'native', 'container': 'dungeon',
                  'review': {'reviewer': 'r', 'membership': 'reviewed', 'types': 'reviewed', 'ownership': 'reviewed'}}
        # the fresh gate snapshot fresh_window_source would hand back
        self.snapshot = self.root/'receipts/demo'
        (self.snapshot).mkdir(parents=True); (self.snapshot/'window.bin').write_bytes(b'demo')
        (self.snapshot/'manifest.json').write_text('{}'); (self.snapshot/'gate.log').write_text('MATCH\n')
        (self.snapshot/'modules.json').write_text(json.dumps([{'module': 'native', 'fingerprint': FP['sha256']}]))
        self.gate_receipt = write_module_proof(self.snapshot/'modules/native')
        for name, value in [('load_modules', [self.m]), ('affected_windows', lambda m, root: [self.wn]),
                            ('fingerprint', lambda m, root: FP), ('certificate_reason', lambda m, cert, root: None)]:
            ctx = patch.object(C, name, value if callable(value) else (lambda v: (lambda root: v))(value)); ctx.start(); self.addCleanup(ctx.stop)

    def certify(self, receipts):
        with patch.object(C, 'fresh_window_source', lambda *a: self.snapshot if receipts else None):
            return C.certify('native', self.root, 'r', self.root/'receipts' if receipts else None, 'tx' if receipts else None, 1)

    def test_receipts_bind_the_gate_module_proof_without_building(self):
        def no_build(*a, **k): raise AssertionError('build() must not run when gate receipts are supplied')
        with patch.object(C, 'build', no_build):
            cert, path = self.certify(True)
        proof = self.root/cert['proof_dir']
        self.assertEqual(cert['receipt_sha256'], C.sha(self.snapshot/'modules/native/receipt.json'))
        self.assertEqual((proof/'OUT.OBJ').read_bytes(), b'genuine object')
        self.assertEqual(cert['members'], self.gate_receipt['members']); self.assertEqual(cert['fingerprint'], FP)
        self.assertEqual(json.loads(path.read_text())['windows'][0]['config'], self.wn)

    def test_without_receipts_the_module_is_built(self):
        calls = []
        def build(m, out, root):
            calls.append(out); return write_module_proof(Path(out)), None
        bd = self.root/'work/demo/build'; shutil.copytree(self.snapshot/'modules', bd/'modules')
        (bd/'demo.window.bin').write_bytes(b'demo'); (bd/'modules.json').write_text((self.snapshot/'modules.json').read_text())
        (bd.parent/'demo_manifest.json').write_text('{}')
        with patch.object(C, 'build', build), patch.object(C, 'command', lambda args, cwd, env, log, **k: Path(log).write_text('MATCH\n')):
            cert, _ = self.certify(False)
        self.assertEqual(len(calls), 1); self.assertEqual(cert['proof_dir'], 'work/module_proofs/native/module')


class BatchFinalValidationTests(unittest.TestCase):
    def run_renew(self, **kw):
        temp = tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')); self.addCleanup(temp.cleanup)
        calls = []
        with patch.object(B, 'jobs', return_value={'a': 'r'}), \
             patch.object(B, 'invalid_certificates', side_effect=lambda *a: calls.append(a) or {}):
            summary = B.renew(Path(temp.name), 1, 1, Path(temp.name)/'logs', invalid_only=True, **kw)
        return calls, summary

    def test_final_validation_runs_by_default(self):
        calls, summary = self.run_renew()
        self.assertEqual(len(calls), 2); self.assertTrue(summary['final_validation'])

    def test_no_final_validation_skips_only_the_repeat(self):
        calls, summary = self.run_renew(final_validation=False)
        self.assertEqual(len(calls), 1); self.assertFalse(summary['final_validation'])


if __name__ == '__main__':
    unittest.main()
