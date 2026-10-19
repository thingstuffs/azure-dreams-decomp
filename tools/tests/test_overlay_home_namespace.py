"""Reproduce the home/copy namespace refusal; test the held consolidation fix."""
from pathlib import Path
from unittest.mock import patch
import json
import sys
import tempfile
import unittest

ROOT=Path(__file__).resolve().parents[2]
sys.path[:0]=[str(ROOT/'tools'),str(ROOT/'tools/gate'),str(ROOT/'tools/fidelity')]
import overlay_module_gate as G
import overlay_module_evidence as fixed_reader
import overlay_scoped_fingerprint as S
import certify_overlay_module as fixed_producer


class HomeNamespace(unittest.TestCase):
    def test_producer_selects_the_unique_home_after_copy_records(self):
        fixed=fixed_producer
        home=dict(module='unit',fingerprint='home');copy=dict(module='unit',placement='unit_dest',fingerprint='copy')
        self.assertEqual(fixed.home_projection([copy,home],'unit'),home)
        for records in ([copy],[home,home]):
            with self.assertRaisesRegex(ValueError,'unique native home'):
                fixed.home_projection(records,'unit')

    def test_reader_distinguishes_home_from_copies_in_the_same_window(self):
        fixed=fixed_reader
        with tempfile.TemporaryDirectory(dir=None) as td:
            root=Path(td)
            def write(name,value):
                path=root/name;path.parent.mkdir(parents=True,exist_ok=True);path.write_text(json.dumps(value)+'\n')
            m=dict(key='unit',members=[dict(id='dungeon/home',foff=0x100,size=8)],owned_data=[],review=dict(membership='reviewed',types='reviewed',ownership='reviewed',reviewer='fixture'))
            before=dict(schema='fixture',sha256='current',windows={'window.yaml':{'sha256':'digest'}})
            write('proof/module/receipt.json',dict(fingerprint=before));write('proof/window/module/receipt.json',dict(fingerprint=before))
            write('proof/window/projection.json',dict(module='unit',projected_rows=['dungeon/home'],fingerprint='current'))
            write('proof/window/manifest.json',dict(c_segments=[dict(module='unit',file_start='0x100',size=8,module_placement=None),
                                                               dict(module='unit',file_start='0x200',size=8,module_placement='unit_dest')]))
            write('window.yaml',dict(standalone_build=dict(window=dict(file_start=0x100,file_end=0x208))))
            (root/'proof/window/window.bin').write_bytes(bytes(0x108));(root/'proof/window/gate.log').write_text('MATCH\n')
            retail=root/'work/disc/containers'/G.CONTAINERS['dungeon'];retail.parent.mkdir(parents=True);retail.write_bytes(bytes(0x208));m['container']='dungeon'
            w=dict(config='window.yaml',digest='digest',result='MATCH',file_start=0x100,file_end=0x208,proof_dir='proof/window',artifacts={n:G.sha(root/'proof/window'/n) for n in ('gate.log','window.bin','manifest.json','projection.json','module/receipt.json')})
            cert=dict(schema=G.SCHEMA,kind='overlay_module_placement',module='unit',members=['dungeon/home'],reviewer='fixture',fingerprint=before,
                      proof_dir='proof/module',receipt_sha256=G.sha(root/'proof/module/receipt.json'),windows=[w])
            with patch.object(S,'enabled',return_value=True),patch.object(fixed,'fingerprint',return_value=before),patch.object(fixed,'affected_windows',return_value=['window.yaml']),patch.object(fixed,'receipt_reason',return_value=None):
                self.assertIsNone(fixed.certificate_reason(m,cert,root))
                manifest=json.loads((root/'proof/window/manifest.json').read_text())
                # The copy tag separates namespaces; it cannot replace a home
                # segment or hide an untagged extra segment from home accounting.
                for name,segments in (
                    ('copy_only',manifest['c_segments'][1:]),
                    ('copy_tag_removed',[dict(s,module_placement=None) for s in manifest['c_segments']]),
                    ('duplicate_home',[manifest['c_segments'][0]]*2+manifest['c_segments'][1:]),
                ):
                    with self.subTest(name=name):
                        write('proof/window/manifest.json',dict(c_segments=segments))
                        cert['windows'][0]['artifacts']['manifest.json']=G.sha(root/'proof/window/manifest.json')
                        self.assertEqual(fixed.certificate_reason(m,cert,root),'window segment provenance incomplete')


if __name__=='__main__':
    unittest.main()
