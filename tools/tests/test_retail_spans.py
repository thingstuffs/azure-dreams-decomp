"""Checked disc references preserve SLUS callers and reject stale retail bytes."""
import copy
import hashlib
import json
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'build'))
from retail_spans import RetailReader, load_json
import slus_modules


class RetailSpansTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        self.raw = bytes(range(16))
        (self.root / 'baserom').mkdir()
        (self.root / 'baserom/slus_006.14').write_bytes(self.raw)
        self.marker = {'$retail': {'file': 'SLUS_006.14', 'offset': 4, 'length': 4,
                                 'sha256': hashlib.sha256(self.raw[4:8]).hexdigest()}, 'format': 'hex'}

    def test_nested_materialization_preserves_plain_json(self):
        doc = {'bytes': self.marker, 'plain': [17, 'text', {'sha256': 'a' * 64}]}
        with RetailReader(self.root) as reader:
            self.assertEqual(reader.materialize(doc),
                             {'bytes': '04050607', 'plain': doc['plain']})

    def test_word_format_preserves_case_and_padding(self):
        marker = copy.deepcopy(self.marker)
        marker['format'] = {'kind': 'int_hex', 'prefix': '0x', 'width': 8, 'uppercase': True}
        with RetailReader(self.root) as reader:
            self.assertEqual(reader.materialize(marker), '0x07060504')
            marker['format'] = 'u32le_list'
            self.assertEqual(reader.materialize(marker), [0x07060504])

    def test_scalar_word_and_observation_digest(self):
        marker = dict(self.marker, format='u32le')
        observation = {'$observation': {'length': 48, 'sha256': 'a' * 64,
                                        'description': 'Mutable emulator state.'}}
        with RetailReader(self.root) as reader:
            self.assertEqual(reader.materialize(marker), 0x07060504)
            self.assertEqual(reader.materialize(dict(marker, format='u8_list')), [4, 5, 6, 7])
            uppercase = copy.deepcopy(marker)
            uppercase['$retail'].update(offset=10, sha256=hashlib.sha256(self.raw[10:14]).hexdigest())
            uppercase['format'] = 'hex_upper'
            self.assertEqual(reader.materialize(uppercase), '0A0B0C0D')
            self.assertEqual(reader.materialize(observation), observation)
            short = copy.deepcopy(marker)
            short['$retail'].update(length=2, sha256=hashlib.sha256(self.raw[4:6]).hexdigest())
            with self.assertRaisesRegex(ValueError, 'four bytes'):
                reader.materialize(short)

    def test_hash_and_length_are_required(self):
        with RetailReader(self.root) as reader:
            for mutation in ({'sha256': '0' * 64}, {'offset': 14}, {'length': True},
                             {'offset': -1}, {'file': '../SLUS_006.14'}):
                span = dict(self.marker['$retail'], **mutation)
                with self.subTest(mutation=mutation), self.assertRaises(ValueError):
                    reader.read(span)

    def test_extracted_corruption_is_not_hidden_by_disc_fallback(self):
        (self.root / 'baserom/slus_006.14').write_bytes(bytes(16))
        with RetailReader(self.root) as reader, self.assertRaisesRegex(ValueError, 'sha256 mismatch'):
            reader.materialize(self.marker)

    def test_unknown_marker_fields_and_format_fail(self):
        with RetailReader(self.root) as reader:
            for marker in (dict(self.marker, extra=True), dict(self.marker, format='base64')):
                with self.assertRaises(ValueError):
                    reader.materialize(marker)

    def test_build_view_resolves_authority_manifest(self):
        (self.root / 'config').mkdir()
        manifest = self.root / 'config/slus_modules.json'
        module = {'name': 'example', 'source': 'src/example.c',
                  'members': [{'id': 'slus/example_row', 'source': 'src/example_row.c',
                               'functions': ['example']}], 'headers': [],
                  'recipe': {'ccver': '2.7.2', 'ccflags': '', 'asflags': ''},
                  'data': [{'symbol': 'table', 'asset': 'assets/0.bin', 'offset': 4,
                            'size': 4, 'vram': 0x80010004, 'bytes': self.marker, 'section': '.rodata'}],
                  'evidence': 'docs/evidence/example.md'}
        manifest.write_text(json.dumps({'version': 1, 'modules': [module]}))
        (self.root / 'view/config').mkdir(parents=True)
        alias = self.root / 'view/config/slus_modules.json'
        alias.symlink_to(manifest)
        result = slus_modules.load_manifest(alias)
        self.assertEqual(result[0]['data'][0]['bytes'], '04050607')
        (self.root / 'baserom/slus_006.14').write_bytes(bytes(16))
        with self.assertRaises(slus_modules.ModuleError):
            slus_modules.load_manifest(alias)


if __name__ == '__main__':
    unittest.main()
