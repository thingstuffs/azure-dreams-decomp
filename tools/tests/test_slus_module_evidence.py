"""Module placement becomes unproved when any shared input or member proof changes."""
import copy
import hashlib
import json
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
from slus_module_context import fingerprint, modules
from slus_module_evidence import certificate_reason, digest, module_status


class ModuleCertificateTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        for path in ('config', 'src/slus', 'include', 'docs/evidence', 'ledger/splits', 'ledger/modules', 'baserom'):
            (self.root / path).mkdir(parents=True)
        module = {'name': 'sample', 'source': 'src/sample.c',
                  'members': [{'id': 'slus/a', 'source': 'src/a.c', 'functions': ['a']},
                              {'id': 'slus/b', 'source': 'src/b.c', 'functions': ['b']}],
                  'headers': ['include/shared.h'],
                  'recipe': {'ccver': '2.7.2-cdk', 'ccflags': '', 'asflags': ''},
                  'data': [], 'evidence': 'docs/evidence/sample.md'}
        (self.root / 'config/slus_modules.json').write_text(json.dumps({'version': 1, 'modules': [module]}))
        for file, text in {'src/slus/sample.c': '#include "a.c"\n#include "b.c"\n',
                           'src/slus/a.c': 'int a(void) { return 1; }\n',
                           'src/slus/b.c': 'int b(void) { return 2; }\n',
                           'include/shared.h': 'int a(void);\nint b(void);\n',
                           'docs/evidence/sample.md': 'Reviewed membership, names and types.\n',
                           'ledger/splits/slus.build.ninja': 'fixture recipe\n',
                           'baserom/slus_006.14': 'fixture retail bytes\n'}.items():
            (self.root / file).write_text(text)
        self.module = modules(self.root)[0]
        fp = fingerprint({'kind': 'slus', 'id': 'slus/a'}, self.root)
        self.cert = {'schema': 1, 'module': 'sample', 'members': ['slus/a', 'slus/b'],
                     'module_fingerprint': fp, 'tool_fingerprint': 'tool-v1',
                     'review': {'path': module['evidence'], 'sha256': digest(self.root / module['evidence']),
                                'reviewer': 'test reviewer'},
                     'gate': {'result': 'MATCH', 'recipe_sha256': digest(self.root / 'ledger/splits/slus.build.ninja')},
                     'image_sha1': hashlib.sha1((self.root / 'baserom/slus_006.14').read_bytes()).hexdigest(),
                     'rows': {rid: {'row': rid, 'status': 'ok', 'selfcheck': True, 'maspsx_exact': True,
                                    'funcs': 1, 'module_fingerprint': fp, 'module': 'sample', 'cfg': '2.7.2-cdk',
                                    'maspsx_retail': {'diff': 0, 'masked': 0, 'checked': 1},
                                    'genuine': {'2.79': {'exact': True, 'retail': [0, 0]}}}
                              for rid in ('slus/a', 'slus/b')}}

    def reason(self, cert=None, fp='tool-v1'):
        return certificate_reason(self.module, self.cert if cert is None else cert, self.root, fp)

    def test_complete_current_certificate_supplies_placement(self):
        self.assertIsNone(self.reason())
        path = self.root / 'ledger/modules/sample.json'
        path.write_text(json.dumps(self.cert))
        self.assertTrue(module_status(self.root, 'tool-v1')[0]['valid'])

    def test_source_header_review_recipe_and_retail_changes_invalidate(self):
        for file in ('src/slus/b.c', 'include/shared.h', 'docs/evidence/sample.md',
                     'ledger/splits/slus.build.ninja', 'baserom/slus_006.14'):
            path = self.root / file
            before = path.read_bytes()
            path.write_bytes(before + b'changed')
            self.assertIsNotNone(self.reason(), file)
            path.write_bytes(before)
        self.assertIsNotNone(self.reason(fp='tool-v2'))

    def test_missing_or_masked_sibling_proof_cannot_certify_module(self):
        cert = copy.deepcopy(self.cert)
        del cert['rows']['slus/b']
        self.assertIsNotNone(self.reason(cert))
        for side in ('maspsx_retail', 'genuine'):
            cert = copy.deepcopy(self.cert)
            if side == 'genuine':
                cert['rows']['slus/b'][side]['2.79']['retail'] = [0, 1]
            else:
                cert['rows']['slus/b'][side]['masked'] = 1
            self.assertIsNotNone(self.reason(cert))

    def test_missing_certificate_reports_unproved_without_crashing_status(self):
        state = module_status(self.root, 'tool-v1')[0]
        self.assertFalse(state['valid'])
        self.assertIn('unavailable', state['reason'])
        (self.root / 'ledger/modules/sample.json').write_text('[]\n')
        self.assertFalse(module_status(self.root, 'tool-v1')[0]['valid'])


if __name__ == '__main__':
    unittest.main()
