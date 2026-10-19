"""Extractor and window safety for linker-owned words; all fixtures synthetic."""
import dataclasses
import hashlib
import json
from pathlib import Path
import sys
import shutil
import struct
import subprocess
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'gate'))
import linklist as L
import linklist_data as D
from byte_map_format import write, read_parts


@dataclasses.dataclass(frozen=True)
class Segment:
    index: int = 0
    kind: str = 'raw'
    start: int = 0
    end: int = 12
    vram: int = 0x80001000
    section: str = '.old'
    name: str = 'raw'
    bytes_path: Path | None = None


class LinkDataTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.blob = b'abcdefghijkl'
        self.container = self.root / 'container'
        self.container.write_bytes(self.blob)
        self.entry = dict(kind='data', foff=4, size=4, type='synthetic word',
                          evidence='census:ledger:linklist_data', extractor='container-slice-v1',
                          sha256=hashlib.sha256(self.blob[4:8]).hexdigest(),
                          symbols={'D_80002004': '0x80002004'})
        self.doc = dict(schema=L.MAP_SCHEMA, image='dungeon/word_4', container='dungeon',
                        foff=4, size=4, vma=0x80002004, entries=[self.entry],
                        census={'proven_data': 4})
        self.path = self.root / 'config/link/dungeon/word_4.json'
        self.path.parent.mkdir(parents=True)
        self.save()

    def save(self):
        self.path.write_text(json.dumps(self.doc))

    def test_verified_slice_and_failed_publish_preserves_output(self):
        target = self.root/'result'
        D.extract_slice(self.container, self.entry, target)
        self.assertEqual(target.read_bytes(), b'efgh')
        self.container.write_bytes(b'bad container')
        with self.assertRaisesRegex(ValueError, 'SHA-256'):
            D.extract_slice(self.container, self.entry, target)
        self.assertEqual(target.read_bytes(), b'efgh')
        self.assertFalse(list(self.root.glob('.word-*')))

    def test_projection_preserves_every_byte_and_symbol_binding(self):
        segments = [Segment()]
        receipt = D.project_segments(segments, self.container, self.root/'build', self.root, 'dungeon', 0, 12)
        self.assertEqual([(s.kind,s.start,s.end) for s in segments], [('raw',0,4),('link_data',4,8),('raw',8,12)])
        self.assertEqual(len({s.section for s in segments}), 3)
        self.assertEqual(segments[1].bytes_path.read_bytes(), b'efgh')
        self.assertEqual(receipt['symbols'], {'D_80002004':0x80002004})
        self.assertEqual(D.window_files(self.root,'dungeon',0,4), [])
        self.assertEqual(D.window_files(self.root,'dungeon',0,8), ['config/link/dungeon/word_4.json'])
        with self.assertRaisesRegex(ValueError,'cuts'):
            D.window_files(self.root,'dungeon',0,6)

    def test_refuses_compiled_or_module_overlap(self):
        for kind in ('c', 'asm', 'rowbase', 'module'):
            with self.subTest(kind=kind), self.assertRaisesRegex(ValueError, 'overlaps'):
                D.project_segments([Segment(kind=kind)], self.container, self.root/'build', self.root, 'dungeon',0,12)

    def test_bad_schema_and_wrong_symbol_base_fail_closed(self):
        for change in ({'extractor':'unknown'}, {'sha256':'bad'}, {'symbols':{}},
                       {'symbols':{'readable_name':'0x80002004'}},
                       {'symbols':{'D_80002008':'0x80002008'}}):
            with self.subTest(change=change), self.assertRaises(ValueError):
                L.validate_image(dict(self.doc, entries=[dict(self.entry, **change)]))
        for key in ('sha256','symbols','extractor'):
            e = dict(self.entry); del e[key]
            with self.assertRaises(ValueError): L.validate_image(dict(self.doc,entries=[e]))

    def test_duplicate_ownership_is_rejected(self):
        other = dict(self.doc, image='dungeon/word_copy')
        self.path.with_name('word_copy.json').write_text(json.dumps(other))
        with self.assertRaisesRegex(ValueError,'listed twice'):
            D.entries(self.root,'dungeon')

    @unittest.skipUnless(shutil.which('mipsel-linux-gnu-as'), 'MIPS binutils unavailable')
    def test_symbol_binding_survives_an_actual_link(self):
        import overlay_local_gate as gate
        assembly, obj, script, elf, binary = [self.root/n for n in ('fixture.s','fixture.o','fixture.ld','fixture.elf','fixture.bin')]
        assembly.write_text('.section .fixture,"a",@progbits\n.word D_80002004\n')
        subprocess.run(['mipsel-linux-gnu-as','-EL','-o',str(obj),str(assembly)],check=True,capture_output=True)
        symbols = self.root/'symbols'
        D.write_symbols(dict(symbols={'D_80002004':0x80002004}), symbols)
        gate.write_linker_script([Segment(section='.fixture')], [obj], 0, [symbols], script)
        subprocess.run(['mipsel-linux-gnu-ld','-EL','-T',str(script),'-o',str(elf),str(obj)],check=True,capture_output=True)
        subprocess.run(['mipsel-linux-gnu-objcopy','-O','binary',str(elf),str(binary)],check=True,capture_output=True)
        self.assertEqual(binary.read_bytes(),struct.pack('<I',0x80002004))

    def test_compact_map_retains_extraction_and_symbols(self):
        doc = dict(self.doc, census=L._totals(self.doc['census']))
        paths = write(self.root/'public', doc)
        self.assertEqual(read_parts(paths), doc)


if __name__ == '__main__': unittest.main()
