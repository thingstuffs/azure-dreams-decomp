import hashlib
import json
from pathlib import Path
import tempfile
import unittest

from tools import retail_text_imports as text


class RetailTextImportTests(unittest.TestCase):
    def test_coverage_record_requires_matching_link_binding_extern_and_disc(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            payload = b'mint tea\0\0\0\0'
            window = payload + bytes(16 - len(payload))
            digest = hashlib.sha256(window).hexdigest()
            disc = root/text.RETAIL['town']
            link = root/'config/link/town/text_4.json'
            ledger = root/'ledger/coverage_regions.jsonl'
            header = root/'include/town/data.h'
            for path in (disc, link, ledger, header):
                path.parent.mkdir(parents=True, exist_ok=True)
            disc.write_bytes(bytes(4) + window)
            record = dict(container='town', foff=4, size=len(payload), category=text.CATEGORY,
                          vma=0x80016004, symbol='drink_label', canonical='D_80016004',
                          header=header.relative_to(root).as_posix(), c_type='u8', elements=len(payload),
                          link_list=link.relative_to(root).as_posix(), retail_sha256=digest, hash_size=len(window))
            ledger.write_text(json.dumps(record) + '\n')
            entry = dict(kind='data', foff=4, size=len(payload), type=text.linklist.RETAIL_TEXT,
                         extractor='container-slice-v1', evidence='Invented text',
                         symbols={'D_80016004': 0x80016004}, sha256=digest, hash_size=len(window))
            image = dict(schema=text.linklist.MAP_SCHEMA, image='town/text_4', container='town', foff=4,
                         vma=0x80016004, size=len(payload), entries=[entry],
                         census={'proven_data': len(payload)})
            link.write_text(json.dumps(image))
            names = root/'config/names.tsv'
            names.write_text('0x80016004\tD_80016004\tdrink_label\tInvented text\n')
            header.write_text(f'extern const u8 drink_label[{len(payload)}];\n')
            self.assertEqual(text.check(root), (1, 1, []))
            for offset in (4, 4 + len(payload)):
                with self.subTest(offset=offset):
                    changed = bytearray(bytes(4) + window)
                    changed[offset] ^= 1
                    disc.write_bytes(changed)
                    count, compared, problems = text.check(root)
                    self.assertEqual((count, compared), (1, 1))
                    self.assertEqual(len(problems), 1)
                    self.assertIn('retail bytes differ from recorded hash', problems[0])
            disc.write_bytes(bytes(4) + window)
            owners = root/'config/overlays/town.rodata_owners.jsonl'
            owners.parent.mkdir(parents=True)
            owners.write_text(json.dumps({'foff': 4}) + '\n')
            self.assertIn('compiled rodata owner', text.check(root)[2][0])
            owners.unlink()
            names.write_text('0x80016008\tD_80016008\tdrink_label\tWrong binding\n')
            header.write_text(f'extern const u8 other_label[{len(payload)}];\n')
            disc.write_bytes(b'\0' * 16)
            count, compared, problems = text.check(root)
            self.assertEqual((count, compared, len(problems)), (1, 1, 3))

    def test_native_short_text_is_bound_to_the_adjacent_allocation(self):
        first, companion = b'Transit timetable', b'\0\0\0\0'

        def allocation(foff, payload, symbol, authenticated):
            return dict(kind=text.overlay_native_rodata.IMPORTED_TEXT, section='.rodata', symbol=symbol,
                        source_symbol=symbol, foff=foff, vma=0x80030000 + foff, size=len(payload),
                        sha256=hashlib.sha256(authenticated).hexdigest())

        module = dict(owned_data=[allocation(0, first, 'guide', first),
                                  allocation(len(first), companion, 'end', first + companion)])
        read = text.overlay_native_rodata.read_text_imports
        with tempfile.TemporaryDirectory() as temporary:
            disc = Path(temporary) / 'disc'
            disc.write_bytes(first + companion)
            self.assertEqual(read(module, disc)[len(first)], ('end', companion))
            changed = bytearray(first + companion)
            changed[-1] ^= 1
            disc.write_bytes(changed)
            with self.assertRaisesRegex(ValueError, 'native text hash differs for end'):
                read(module, disc)
