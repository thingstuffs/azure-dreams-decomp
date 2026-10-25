"""Decoded coordinates, complete-section proof and exact stream regression tests."""
import copy
import json
import os
from pathlib import Path
import random
import sys
import tempfile
import unittest
from unittest.mock import patch
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
from tools.decoded.lz import decode, encode
from tools import decoded_images as D
from tools.decoded.census import discover, signatures


class CodecTests(unittest.TestCase):
    def test_empty_and_literal_overlap_vectors(self):
        self.assertEqual(decode(bytes([1, 0, 0]), 0), (b'', 3))
        self.assertEqual(decode(bytes([10, 65, 0, 17, 0, 0]), 4), (b'AAAA', 6))
        self.assertEqual(encode(b'AAAA'), bytes([54, 65, 1, 0, 0]))

    def test_reference_and_input_bounds(self):
        for data, message in [(b'\0', 'truncated'), (bytes([1, 0, 17]), 'backward')]:
            with self.assertRaisesRegex(ValueError, message):
                decode(data, 4096)
        with self.assertRaisesRegex(ValueError, 'limit'):
            decode(bytes([10, 65, 0, 17, 0, 0]), 3)
        with self.assertRaisesRegex(ValueError, 'limit'):
            decode(b'\1\0\0', -1)

    def test_flags_lengths_history_and_dictionary_reset(self):
        rng = random.Random(1249)
        for size in (0, 1, 2, 3, 5, 8, 17, 18, 255, 256, 257, 4095, 4096, 8193):
            for data in (bytes(size), bytes(rng.randrange(256) for _ in range(size)),
                         (b'abcdefg' * ((size+6)//7))[:size]):
                packed = encode(data)
                self.assertEqual(decode(packed, size), (data, len(packed)))
        data = bytes(range(256)) + b'\0\1' + bytes(range(255, -1, -1))
        self.assertEqual(decode(encode(data), len(data))[0], data)

    def test_unaligned_second_stream_is_still_code(self):
        word = bytes.fromhex('0800e003e0ffbd270080000c')
        result = signatures(b'xx' + word * 4)
        self.assertEqual(result['phase'], 2)
        self.assertGreaterEqual(result['returns'], 3)

    def test_second_command_offset_is_relative_to_resource_base(self):
        import struct
        header = (struct.pack('<HHIhhhh', 5, 16, 36, 320, 256, 64, 128) +
                  struct.pack('<HHIhhhh', 5, 16, 36+0x4000, 320, 384, 64, 128) + b'\0'*4)
        starts, _ = discover(header + b'\0' * 0x8000)
        self.assertTrue(any(c.get('base') == 0 for c in starts[36+0x4000]))


class RegistryFixture(unittest.TestCase):
    """Temporary root holding the menu-cache registry and fixture sources (no tests of its own)."""
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(dir=ROOT/'build')
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.spec = json.loads((ROOT/'config/decoded/menu_cache.json').read_text())
        for unit in self.spec['units']:
            for key in ('source', 'header'):
                p = self.root / unit[key]
                p.parent.mkdir(parents=True, exist_ok=True)
                p.write_text('/* fixture */\n')
        (self.root/'config/decoded').mkdir(parents=True)
        state = self.root/'build/.state'
        state.mkdir(parents=True)
        (state/'recipes').mkdir()
        (state/'slus-recipes').mkdir()
        (state/'images').mkdir()
        (state/'index.json').write_text(json.dumps(dict(images=[])))
        self.write()

    def write(self):
        (self.root/'config/decoded/menu_cache.json').write_text(json.dumps(self.spec))


class RegistryTests(RegistryFixture):
    def test_rows_use_explicit_decoded_identity(self):
        rows = D.rows(self.root)
        self.assertEqual(len(rows), 15)
        self.assertTrue(all(r['coordinate_space'] == 'decoded' and r['id'].startswith('decoded/') for r in rows))
        self.assertTrue(all('foff' not in r for r in rows))

    def test_reject_overlap_and_physical_coordinate_confusion(self):
        first, second = self.spec['units'][0]['functions'][:2]
        second['address'] = first['address']
        self.write()
        with self.assertRaisesRegex(ValueError, 'overlapping'):
            D.manifests(self.root)
        second['address'] = '0x4a3014'
        self.write()
        with self.assertRaisesRegex(ValueError, 'outside'):
            D.manifests(self.root)

    def test_reject_path_escape_and_duplicate_unit(self):
        self.spec['units'][0]['source'] = '../outside.c'
        self.write()
        with self.assertRaisesRegex(ValueError, 'unsafe'):
            D.manifests(self.root)

    def test_no_cannot_silently_become_an_import(self):
        self.spec['units'] = []
        self.write()
        with self.assertRaisesRegex(ValueError, 'has no C'):
            D.manifests(self.root)

    def test_multi_command_offsets_cannot_impersonate_single_uploads(self):
        self.spec['streams'][0]['command'][2] = 36
        self.write()
        with self.assertRaisesRegex(ValueError, 'source command contract'):
            D.manifests(self.root)

    def test_duplicate_translation_unit_is_rejected(self):
        self.spec['units'].append(copy.deepcopy(self.spec['units'][0]))
        self.write()
        with self.assertRaisesRegex(ValueError, 'duplicate decoded translation unit'):
            D.manifests(self.root)

    def test_altered_source_command_fails_before_decoding(self):
        path = self.root / self.spec['streams'][0]['container']
        path.parent.mkdir(parents=True)
        with path.open('wb') as output:
            output.truncate(D.number(self.spec['streams'][0]['offset']) + 0x4000)
        with self.assertRaisesRegex(ValueError, 'command differs'):
            D.reproduce(self.root, self.spec)


@unittest.skipUnless(os.environ.get('AZURE_DECODED_RETAIL_TEST'), 'explicit private retail fixture required')
class RetailTests(unittest.TestCase):
    def test_whole_image_streams_container_and_tampered_artifact(self):
        proofs = D.build_all(ROOT)
        self.assertEqual(proofs[0]['decoded_c_text_bytes'], 1320)
        self.assertEqual(proofs[0]['compressed_stream_bytes'], 28662)
        self.assertEqual(proofs[0]['decoded_imported_bytes'], 58872)
        self.assertEqual((ROOT/'build/decoded/disc/DUNGEON/DUNGEON.BIN').read_bytes(),
                         (ROOT/'work/disc/containers/DUNGEON_DUNGEON.BIN').read_bytes())
        stream = proofs[0]['compressed_streams'][0]
        path = ROOT / stream['output']
        original = path.read_bytes()
        try:
            path.write_bytes(bytes([original[0]^1])+original[1:])
            with self.assertRaisesRegex(ValueError, 'artifact changed'):
                D.container_overlays(ROOT, proofs)
        finally:
            path.write_bytes(original)

    def test_complete_section_size_cannot_be_sliced(self):
        image = copy.deepcopy(D.manifests(ROOT)[0])
        image['units'][0]['functions'][0]['size'] -= 4
        with self.assertRaisesRegex(ValueError, 'complete decoded TU text extents'):
            D.build(ROOT, image)


if __name__ == '__main__':
    unittest.main()
