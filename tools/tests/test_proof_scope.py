"""Unsupported external/location inputs cannot reuse a v1 gate journal."""
import json,os,sys,tempfile,unittest
from pathlib import Path
from unittest.mock import patch
sys.path[:0]=[str(Path(__file__).resolve().parents[1]/'lanes'),str(Path(__file__).resolve().parents[1])]
import proof_scope as P
import overlay_scoped_fingerprint as S

class Scope(unittest.TestCase):
    def test_path_sensitive_sources_and_headers_fail_closed(self):
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as td:
            root=Path(td);(root/'src/main').mkdir(parents=True);(root/'include').mkdir()
            path=root/'src/main/a.c';path.write_text('const char *p=__FILE__;')
            with self.assertRaisesRegex(ValueError,'path-sensitive C'):P.check(root)
            path.write_text('int a(void){return 1;}')
            private=root/'src/main/local.h';private.write_text('#define F __FILE__')
            with self.assertRaisesRegex(ValueError,'path-sensitive C'):P.check(root)
            private.unlink();(root/'include/a.h').write_text('#define F __BASE_FILE__')
            with self.assertRaisesRegex(ValueError,'path-sensitive header'):P.check(root)

    def test_custom_include_profile_and_time_recipe_inputs_require_adapter(self):
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as td:
            root=Path(td);(root/'ledger/splits').mkdir(parents=True)
            (root/'ledger/splits/main.jsonl').write_text(json.dumps(dict(result='MATCH',config='test'))+'\n')
            for flags in ['-I.','-include custom.h','-fbranch-probabilities','-fprofile-use','-DVALUE=__TIME__']:
                with patch.object(S,'parse_config_label',return_value=('2.7.2',flags)),self.assertRaisesRegex(ValueError,'requires a proof adapter'):P.check(root)
            with patch.object(S,'parse_config_label',return_value=('2.7.2','-G0 -fno-schedule-insns')):
                self.assertEqual(P.check(root)['result'],'PASS')
