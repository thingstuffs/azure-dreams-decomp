"""Exercise the resource table readers on invented executable and disc geometry."""

import struct
import unittest

from tools import scene_read_spans as reads
from tools.decoded.lz import encode


class SceneReadSpansTests(unittest.TestCase):
    def setUp(self):
        self.base = 0x8006c000
        self.program = bytearray(0x16800)
        self.program[:8] = b'PS-X EXE'
        struct.pack_into('<II', self.program, 0x18, self.base, 0x16000)
        self.volumes = {'town': (20, 100 * 2048), 'main': (200, 60 * 2048),
                        'dungeon': (400, 50 * 2048), 'ovmovie': (600, 80 * 2048)}
        self.records = []
        for group, (family, lba, shift, size) in enumerate([
                ('town', 20, 4, 8), ('dungeon', 400, 8, 4), ('main', 200, 2, 13)], 1):
            address = self.base + group * 8
            self.write(0x8006ce44 + 8 * group + 4, address)
            self.write(0x8006ce6c + 4 * group, 0)
            self.write(address, size << 23)
            self.write(address + 4, lba + shift)
            self.records.append(dict(category=reads.SCENE, group=group, container=family,
                                     foff=shift * 2048, size=size * 2048))
        self.write(0x80080c50, 36 << 23)
        self.write(0x80080c54, 604)
        self.records.append(dict(category=reads.MOVIE, group=0, container='ovmovie',
                                 foff=8192, size=36 * 2048))

    def write(self, address, value):
        struct.pack_into('<I', self.program, address - self.base + 0x800, value)

    def check(self):
        return reads.verify_records(self.records, self.program, self.volumes)

    def test_scene_table_refuses_a_shifted_extent_and_a_made_up_group(self):
        self.assertEqual(self.check()[reads.SCENE, 1], ('town', 8192, 16384))
        original = self.records[0]
        for mutation in ({'foff': 10240}, {'group': 4}):
            with self.subTest(mutation=mutation):
                self.records[0] = dict(original, **mutation)
                with self.assertRaisesRegex(ValueError, 'disagree with the executable'):
                    self.check()

    def test_movie_table_refuses_a_shorter_read_and_a_wrong_container(self):
        self.assertEqual(self.check()[reads.MOVIE, 0], ('ovmovie', 8192, 73728))
        original = self.records[-1]
        for mutation in ({'size': 35 * 2048}, {'container': 'town'}):
            with self.subTest(mutation=mutation):
                self.records[-1] = dict(original, **mutation)
                with self.assertRaisesRegex(ValueError, 'disagree with the executable'):
                    self.check()

    def test_mutated_descriptor_cannot_read_across_containers(self):
        self.write(self.base + 12, 119)
        with self.assertRaisesRegex(ValueError, 'outside a single disc container'):
            self.check()

    def test_scene_bulk_reads_in_pairs_then_uses_the_descriptor_tail(self):
        self.assertEqual(reads.scene_sector_count(0x200, 17), 17)
        self.assertEqual(reads.scene_sector_count(0x201, 17), 0x200 + 17)
        self.assertEqual(reads.scene_sector_count(0x401, 17), 0x400 + 17)

    def test_indexed_sprite_table_requires_real_extents_and_destination(self):
        for index, (family, lba) in enumerate([('dungeon', 403), ('town', 25), ('town', 35)]):
            entry = 0x80071210 + index * 8
            descriptor = self.base + 0x40 + index * 8
            self.write(entry, descriptor)
            self.write(entry + 4, 0x80176000)
            self.write(descriptor, (7 << 23) | 0x176000)
            self.write(descriptor + 4, lba)
            first, _ = self.volumes[family]
            self.records.append(dict(category=reads.INDEXED_SPRITES, group=index, container=family,
                                     foff=(lba - first) * 2048, size=7 * 2048))
        self.assertEqual(self.check()[reads.INDEXED_SPRITES, 2], ('town', 15 * 2048, 7 * 2048))
        original = self.records[-1]
        for change in ({'foff': original['foff'] + 2048}, {'group': 3}):
            with self.subTest(change=change):
                self.records[-1] = dict(original, **change)
                with self.assertRaisesRegex(ValueError, 'disagree with the executable'):
                    self.check()
        self.records[-1] = original
        self.write(0x80071214, 0x80178000)
        with self.assertRaisesRegex(ValueError, 'differs from its consumer'):
            self.check()

    def test_indexed_sprite_row_must_fit_the_read(self):
        payload = bytearray(1024)
        struct.pack_into('<ii', payload, 0x1c, 512, 16)
        reads.check_sprite_bundle_payload(payload)
        struct.pack_into('<ii', payload, 0x1c, 514, 16)
        with self.assertRaisesRegex(ValueError, 'upload row lies outside'):
            reads.check_sprite_bundle_payload(payload)

    def test_sound_tables_refuse_invented_ids_and_coordinates(self):
        tables = {
            reads.EFFECT_BANK: [i + part for i in range(0x8006e61c, 0x8006e6f4, 12) for part in (4, 8)],
            reads.SOUND_SET: list(range(0x8006e6f4, 0x8006e704, 4)),
            reads.SOUND_STREAM: list(range(0x8006e704, 0x8006e7b4, 4)),
        }
        for address in range(0x8006e61c, 0x8006e6f4, 12):
            self.write(address, 1)
        for category, entries in tables.items():
            with self.subTest(category=category):
                records = []
                for group, address in enumerate(entries):
                    descriptor = self.base + 0x200 + group * 8
                    destination = 0 if group % 2 == 0 else 0x30000
                    self.write(address, descriptor)
                    self.write(descriptor, (1 << 23) | destination)
                    self.write(descriptor + 4, 20 + group)
                    records.append(dict(category=category, group=group, container='town',
                                        foff=group * 2048, size=2048))
                self.records = records
                self.assertEqual(len(self.check()), len(entries))
                original = records[-1]
                for change in ({'group': len(entries)}, {'foff': len(entries) * 2048}):
                    records[-1] = dict(original, **change)
                    with self.assertRaisesRegex(ValueError, 'disagree with the executable'):
                        self.check()

    def test_town_texture_descriptors_bind_extent_and_upload_destination(self):
        self.records = []
        for group, descriptor in enumerate(range(0x80080bac, 0x80080c1c, 8)):
            self.write(descriptor, (1 << 23) | 0x20000)
            self.write(descriptor + 4, 20 + group)
            self.records.append(dict(category=reads.TOWN_TEXTURES, group=group, container='town',
                                     foff=group * 2048, size=2048))
        self.assertEqual(len(self.check()), 14)
        original = self.records[0]
        for change in ({'group': 14}, {'size': 4096}):
            self.records[0] = dict(original, **change)
            with self.assertRaisesRegex(ValueError, 'disagree with the executable'):
                self.check()
        self.records[0] = original
        self.write(0x80080bac, (1 << 23) | 0x26000)
        with self.assertRaisesRegex(ValueError, 'differs from its consumer'):
            self.check()

    def test_town_character_catalog_aliases_share_one_read(self):
        town = bytearray(0x60000)
        catalog = reads.TOWN_RESOURCE_CATALOG - reads.TOWN_ENGINE_DELTA
        descriptor = self.base + 0x800
        for slot in range(1, 14):
            struct.pack_into('<I', town, catalog + slot * 4, descriptor)
        self.write(descriptor, 4 << 23)
        self.write(descriptor + 4, 23)
        record = dict(category=reads.TOWN_CHARACTERS, group=1, container='town',
                      foff=3 * 2048, size=4 * 2048)
        verify = lambda rows: reads.verify_records(rows, self.program, self.volumes, town)
        self.assertEqual(verify([record]), {(reads.TOWN_CHARACTERS, 1): ('town', 6144, 8192)})
        for mutation in ({'group': 4}, {'size': 4096}):
            with self.assertRaisesRegex(ValueError, 'disagree with the executable'):
                verify([dict(record, **mutation)])
        self.write(descriptor, (4 << 23) | 0x20000)
        with self.assertRaisesRegex(ValueError, 'differs from its consumer'):
            verify([record])

    def test_floor_tracks_and_variants_resolve_only_consumed_descriptors(self):
        module = bytearray(reads.FLOOR_MODULE[1])
        module[reads.FLOOR_TRACKS:reads.FLOOR_TRACKS + 50] = bytes((0x29, 2, 1, 1, 0)) * 10
        descriptor = self.base + 0x100
        self.write(descriptor, 2 << 23)
        self.write(descriptor + 4, 407)
        for address in [0x8001f58c, *range(0x8001f594, 0x8001f5f4, 4), 0x8001f608]:
            struct.pack_into('<I', module, address - reads.FLOOR_MODULE_BASE, descriptor)
        layout = self.base + 0x200
        self.write(0x8006e7f0 + 0x29 * 4, layout)
        self.write(layout, descriptor)
        self.write(layout + 4, 2)
        records = [
            dict(category=category, group=group, container='dungeon', foff=offset * 2048, size=size * 2048)
            for category, group, offset, size in (
                (reads.FLOOR_IMAGES, 1, 7, 2),
                (reads.FLOOR_LAYOUTS, 1, 7, 2),
                (reads.FLOOR_CHUNKS, 0x52, 7, 2),
                (reads.FLOOR_CHUNKS, 0x53, 23, 16),
            )
        ]

        def verify(rows):
            return reads.verify_records(rows, self.program, self.volumes, floor_module=module)

        self.assertEqual(len(verify(records)), 4)
        for index, original in enumerate(records):
            for mutation in ({'group': 123}, {'foff': 0}):
                with self.subTest(record=original, mutation=mutation):
                    changed = records.copy()
                    changed[index] = dict(original, **mutation)
                    with self.assertRaisesRegex(ValueError, 'disagree with the executable'):
                        verify(changed)
        module[reads.FLOOR_TRACKS + 3] = 3
        with self.assertRaisesRegex(ValueError, 'floor track image index'):
            verify(records)

    def test_chunk_decoding_restarts_at_each_transfer_and_respects_the_total_limit(self):
        first = encode(b'sample floor')
        second = encode(b'another floor')
        data = first.ljust(reads.CHUNK_BYTES, b'\0') + second
        self.assertEqual(reads.check_chunk_payload(data, 30), 5)
        with self.assertRaisesRegex(ValueError, 'decoded size exceeds limit'):
            reads.check_chunk_payload(data, 23)
        with self.assertRaisesRegex(ValueError, 'truncated compressed stream'):
            reads.check_chunk_payload(data[:-1], 30)

    def test_town_map_reads_follow_the_variant_table_and_skip_special_kind(self):
        town = bytearray(0x60000)
        variants = reads.TOWN_MAP_VARIANTS[0] - reads.TOWN_ENGINE_DELTA
        town[variants:variants + 3 * 32:32] = bytes((0, 2, 0x29))
        catalog = reads.TOWN_CHUNK_TABLES[0]
        descriptor, layout = catalog, catalog + 8
        for kind in (0, 2):
            self.write(0x8006e7f0 + kind * 4, layout)
        struct.pack_into('<IIIH', town, catalog - reads.TOWN_ENGINE_DELTA, 16 << 23, 28, descriptor, 2)
        records = [dict(category=reads.TOWN_CHUNKS, group=group, container='town',
                        foff=(8 + group * 16) * 2048, size=16 * 2048) for group in (0, 1)]
        self.assertEqual(len(reads.verify_records(records, self.program, self.volumes, town)), 2)
        for mutation in ({'group': 4}, {'size': 8 * 2048}):
            with self.subTest(mutation=mutation):
                with self.assertRaisesRegex(ValueError, 'disagree with the executable'):
                    reads.verify_records([dict(records[0], **mutation), records[1]],
                                         self.program, self.volumes, town)
        self.write(0x8006e7f0 + 2 * 4, catalog - 4)
        with self.assertRaisesRegex(ValueError, 'outside its catalog'):
            reads.verify_records(records, self.program, self.volumes, town)

    def test_town_setup_binds_scratch_reads_from_both_loaded_images(self):
        town = bytearray(0x60000)
        records = []
        for group, (owner, address, family) in enumerate(reads.TOWN_SETUP_DESCRIPTORS):
            first, _ = self.volumes[family]
            if owner == 'town':
                struct.pack_into('<II', town, address - reads.TOWN_ENGINE_DELTA, 2 << 23, first + group)
            else:
                self.write(address, 2 << 23)
                self.write(address + 4, first + group)
            records.append(dict(category=reads.TOWN_SETUP, group=group, container=family,
                                foff=group * 2048, size=4096))
        self.assertEqual(len(reads.verify_records(records, self.program, self.volumes, town)), 6)
        for change in ({'group': 6}, {'size': 2048}):
            with self.subTest(change=change):
                with self.assertRaisesRegex(ValueError, 'disagree with the executable'):
                    reads.verify_records([dict(records[0], **change), *records[1:]],
                                         self.program, self.volumes, town)

    def test_default_scene_uses_the_resident_descriptor(self):
        self.write(0x800812f8, 4 << 23 | 0x16000)
        self.write(0x800812fc, 25)
        record = dict(category=reads.TOWN_DEFAULT_SCENE, group=0, container='town',
                      foff=5 * 2048, size=4 * 2048)
        self.records = [record]
        self.assertEqual(len(self.check()), 1)
        for change in ({'group': 1}, {'foff': 6 * 2048}):
            with self.subTest(change=change):
                self.records = [dict(record, **change)]
                with self.assertRaisesRegex(ValueError, 'disagree with the executable'):
                    self.check()

    def test_spawn_tables_stop_before_the_final_floor(self):
        self.volumes['dungeon'] = (0x3f5e, 60 * 2048)
        self.records = [dict(category=reads.FLOOR_SPAWNS, group=floor, container='dungeon',
                             foff=floor * 2048, size=2048) for floor in range(1, 40)]
        self.assertEqual(len(self.check()), 39)
        original = self.records[-1]
        for change in ({'group': 40, 'foff': 40 * 2048}, {'size': 4096}):
            with self.subTest(change=change):
                self.records[-1] = dict(original, **change)
                with self.assertRaisesRegex(ValueError, 'disagree with the executable'):
                    self.check()

    def test_floor_module_reads_keep_their_loaded_destination_and_extent(self):
        desc = struct.pack('<IIII', 5 << 23 | 0x16000, 402, 7 << 23 | 0x16000, 420)
        records = [
            dict(category=reads.FLOOR_MODULE_READ, group=group, container='dungeon',
                 foff=offset * 2048, size=size * 2048)
            for group, offset, size in [(0, 2, 5), (1, 20, 7)]
        ]
        self.assertEqual(len(reads.verify_records(
            records, self.program, self.volumes, floor_descriptors=desc)), 2)
        for change in ({'group': 2}, {'size': 4 * 2048}):
            with self.subTest(change=change):
                with self.assertRaisesRegex(ValueError, 'disagree with the executable'):
                    reads.verify_records([dict(records[0], **change), records[1]], self.program, self.volumes,
                                         floor_descriptors=desc)


if __name__ == '__main__':
    unittest.main()
