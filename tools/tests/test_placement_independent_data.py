"""Decision 35: real ELF inventories, linking, and regeneration invariants."""
import dataclasses
import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT/'tools'), str(ROOT/'tools/gate')]
import overlay_local_gate as G
import registry as R
import levels as L
import status as S

@unittest.skipUnless(shutil.which('mipsel-linux-gnu-as'), 'MIPS assembler required')
class ObjectChecks(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.d = Path(self.tmp.name)
        self.owner = {'id': 'town/D_test', 'rodata_size': 4}
        self.match = G.MatchEntry(start=0x100, size=4, func='D_test', source=self.d/'test.c',
                                  config='2.6.3-G0', source_group='test', link_vram=None)
        self.seg = G.Segment(index=0, kind='c', start=0x100, end=0x104,
                             vram=0x80200100, section='.ovlseg_0000', name='D_test', match=self.match)

    def obj(self, extra='', word='0x12345678'):
        src = self.d/'test.s'; obj = self.d/'test.o'
        src.write_text('.section .rodata\n.balign 4\n.globl D_test\nD_test:\n.word '+word+'\n'+extra)
        subprocess.run(['mipsel-linux-gnu-as','-EL','-march=r3000','-G0','-no-pad-sections',
                        '-o',str(obj),str(src)], check=True, capture_output=True)
        return obj

    def test_zero_relocation_links_at_linear_vram(self):
        obj = self.obj()
        self.assertEqual(G.rodata_link_base(obj,self.seg,self.owner), self.seg.vram)
        self.assertEqual(G.rodata_first_link(obj,self.seg,self.owner,0,[],self.d/'proof'),
                         bytes.fromhex('78563412'))
        self.assertIn('0x80200100', (self.d/'proof.ld').read_text())
        self.assertIsNone(self.seg.match.link_vram)

    def test_relocation_refused_even_with_defined_target(self):
        obj = self.obj(word='D_test')
        with self.assertRaisesRegex(SystemExit,'not in a proven rowbase region.*relocations'):
            G.rodata_link_base(obj,self.seg,self.owner)

    def test_undefined_without_relocation_refused(self):
        obj = self.obj('.globl missing\n')
        with self.assertRaisesRegex(SystemExit,'undefined symbols'):
            G.rodata_link_base(obj,self.seg,self.owner)

    def test_weak_undefined_without_relocation_refused(self):
        obj = self.obj('.globl missing\n')
        import struct
        raw = bytearray(obj.read_bytes())
        off = struct.unpack_from('<I', raw, 32)[0]
        stride, count = struct.unpack_from('<HH', raw, 46)
        for i in range(count):
            h = struct.unpack_from('<10I', raw, off + i * stride)
            if h[1] == 2:
                for pos in range(h[4] + 16, h[4] + h[5], 16):
                    if struct.unpack_from('<H', raw, pos + 14)[0] == 0:
                        raw[pos + 12] = 0x20
        obj.write_bytes(raw)
        with self.assertRaisesRegex(SystemExit,'undefined symbols'):
            G.rodata_link_base(obj,self.seg,self.owner)

    def test_nonempty_text_refused(self):
        obj = self.obj('.text\n.word 0\n')
        with self.assertRaisesRegex(SystemExit,'nonempty .text'):
            G.rodata_link_base(obj,self.seg,self.owner)

    def test_sectioned_text_refused(self):
        obj = self.obj('.section .text.fn,"ax",@progbits\n.word 0\n')
        with self.assertRaisesRegex(SystemExit,'nonempty .text'):
            G.rodata_link_base(obj,self.seg,self.owner)

    def test_nonallocated_relocation_refused(self):
        obj = self.obj('.section .debug_test\n.word D_test\n')
        with self.assertRaisesRegex(SystemExit,'relocations'):
            G.rodata_link_base(obj,self.seg,self.owner)

    def test_proven_region_path_unchanged(self):
        obj = self.obj(word='D_test')
        self.seg = dataclasses.replace(self.seg,match=dataclasses.replace(self.match,link_vram=0x80024000))
        self.assertEqual(G.rodata_link_base(obj,self.seg,self.owner),0x80024000)
        self.assertEqual(G.rodata_first_link(obj,self.seg,self.owner,0,[],self.d/'proof'),
                         bytes.fromhex('00400280'))

    def test_malformed_object_refused(self):
        obj = self.d/'bad.o'; obj.write_bytes(b'broken')
        with self.assertRaisesRegex(SystemExit,'not ELF32'):
            G.rodata_link_base(obj,self.seg,self.owner)

class RegistryAndLevels(unittest.TestCase):
    def data(self):
        return dict(id='town/D_test',container='town',func='D_test',kind='overlay',size=4,
                    cfg='2.6.3-G0',row_kind='data',placement='unproven',residue='stale-image')

    def test_registry_regeneration_preserves_fields(self):
        split = dict(func_vram='D_test',foff=256,size=4,result='MATCH',config='2.6.3-G0',
                     c_path='overlays/town/first_pass_matched/D_test.c',gate_config='test.yaml',
                     row_kind='data',placement='unproven',residue='stale-image',parent_id='main/test')
        with patch.object(R,'OVERLAYS',('town',)), patch.object(R,'read_jsonl',return_value=[split]):
            for _ in range(2):
                row = R.overlay_rows()[0]
                for key in ['row_kind','placement','residue','parent_id']:
                    self.assertEqual(row[key],split[key])

    def test_unproven_blocks_l4_even_with_module_certificate(self):
        r = self.data(); L._CONTAINER_SYMS['town'] = set()
        result = L.evaluate_row(r,'const unsigned x = 1;','old',{r['id']},
                                {'l4_modules':{r['id']:{}}},{})
        self.assertEqual(result['level'],3)
        self.assertIn('placement_unproven',result['l4_residue'])
        self.assertEqual(result['l5_fidelity'],[])
        self.assertEqual(result['pins_left'],0)
        r.pop('placement')
        self.assertEqual(L.evaluate_row(r,'const unsigned x = 1;','old',{r['id']},
                         {'l4_modules':{r['id']:{}}},{})['level'],5)

    def test_status_lists_unproven_storage_and_data_residue(self):
        out = S.placement_unproven_status([self.data()])
        self.assertIn('town/D_test',out)
        self.assertIn('stale-image residue DATA: 1 (4 B)',out)
        self.assertIn('excluded from L4',out)

    def test_retired_composite_ignored_in_historical_census_and_levels(self):
        records = [{'id': 'town/func_old'}, {'id': 'town/D_test'}]
        self.assertEqual(S.current_row_records(records, {'town/D_test'}), [records[1]])
