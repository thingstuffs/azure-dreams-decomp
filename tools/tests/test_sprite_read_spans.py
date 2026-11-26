import struct
import unittest

from tools import sprite_read_spans as sprites


class SpriteReadTests(unittest.TestCase):
    def setUp(self):
        self.first_lba = 0x5000
        self.volume_size = 0x200000 * 2
        self.resource_id = 3
        start, size = sprites.transfer(self.resource_id, self.first_lba, self.volume_size)
        self.record = {"resource_id": self.resource_id, "foff": start, "size": size}
        self.executable = bytearray(0x800 + 0x20000)
        self.executable[:8] = b"PS-X EXE"
        struct.pack_into("<II", self.executable, 0x18, 0x8002D000, 0x20000)
        self.manifest = {
            "schema": "azure-clean.dungeon-sprite-reads.v1",
            "readers": sprites.reader_hashes(self.executable),
            "transfers": [self.record],
        }
        self.payload = bytearray(size)
        struct.pack_into("<III", self.payload, 0, 0x28, 1, 0x34)
        struct.pack_into("<III", self.payload, 0x28, 0x38, 11, 0x50)
        self.payload[sprites.METADATA_SECTORS * sprites.SECTOR] = 1
        self.payload[-1] = 2

    def verify(self):
        return sprites.verify_records(
            self.manifest, self.executable, self.first_lba, self.volume_size,
            lambda offset, size: self.payload)

    def test_pair(self):
        start = self.record["foff"]
        self.assertEqual(self.verify(), [(start, start + self.record["size"])])

    def test_rejects_made_up_extent(self):
        self.record["foff"] += sprites.SECTOR
        with self.assertRaisesRegex(ValueError, "coordinates differ"):
            self.verify()

    def test_rejects_change_to_reader(self):
        address, _ = sprites.READERS["build_sprite_metadata_read_descriptor"]
        self.executable[0x800 + address - 0x8002D000] ^= 1
        with self.assertRaisesRegex(ValueError, "reader proof differs"):
            self.verify()

    def test_rejects_outside_pointer(self):
        struct.pack_into("<I", self.payload, 0x28, len(self.payload))
        with self.assertRaisesRegex(ValueError, "pointer falls outside"):
            self.verify()

    def test_rejects_unproved_species_domain(self):
        self.record["resource_id"] = 57
        with self.assertRaisesRegex(ValueError, "outside the checked Dungeon species domain"):
            self.verify()

    def test_three_slot_species_checks_extended_metadata_and_image(self):
        self.first_lba = 0x4000
        start, size = sprites.transfer(56, self.first_lba, self.volume_size)
        self.record.update(resource_id=56, foff=start, size=size)
        metadata = sprites.METADATA_SECTORS * sprites.SECTOR
        self.payload[metadata:metadata] = bytes(2 * metadata)
        struct.pack_into("<I", self.payload, 0x28, 2 * metadata)
        self.assertEqual(self.verify(), [(start, start + size)])
        self.record["size"] = (26 + 17) * sprites.SECTOR
        with self.assertRaisesRegex(ValueError, "coordinates differ"):
            self.verify()
        self.record["size"] = size
        struct.pack_into("<I", self.payload, 0x28, 3 * metadata)
        with self.assertRaisesRegex(ValueError, "pointer falls outside"):
            self.verify()

    def test_town_requests_follow_the_catalog(self):
        town = bytearray(0x70000)
        at = sprites.TOWN_RESOURCE_CATALOG - sprites.TOWN_ENGINE_DELTA + 16 * 4
        struct.pack_into("<II", town, at, 58, 59)
        lba = 0x1B8D
        expected = sprites.town_transfers(town, lba)
        records = {"readers": sprites.town_reader_hashes(town), "transfers": expected}
        verify = lambda: sprites.verify_town_records(records, town, lba, lambda *_: self.payload)
        size = len(self.payload)
        self.assertEqual(verify(), [(0, size), (size, 2 * size)])
        original = expected[1]
        for change in ({"resource_id": 60}, {"foff": size + sprites.SECTOR}):
            with self.subTest(change=change):
                expected[1] = dict(original, **change)
                with self.assertRaisesRegex(ValueError, "differ from the Town engine catalog"):
                    verify()
        expected[1] = original
        struct.pack_into("<I", town, at + 4, 60)
        with self.assertRaisesRegex(ValueError, "differ from the Town engine catalog"):
            verify()

    def test_town_reservation_and_pending_reader_have_separate_digests(self):
        town = bytearray(0x70000)
        reserve = 0x8008B550 - sprites.TOWN_ENGINE_DELTA
        original = sprites.town_reader_hashes(town)
        town[reserve] = 1
        reservation_changed = sprites.town_reader_hashes(town)
        self.assertNotEqual(original["reserve_tw_mon_load"], reservation_changed["reserve_tw_mon_load"])
        self.assertEqual(original["process_pending_resource_load"],
                         reservation_changed["process_pending_resource_load"])
        town[reserve + 12] = 1
        pending_changed = sprites.town_reader_hashes(town)
        self.assertNotEqual(reservation_changed["reserve_tw_mon_load"], pending_changed["reserve_tw_mon_load"])
        self.assertNotEqual(reservation_changed["process_pending_resource_load"],
                            pending_changed["process_pending_resource_load"])


if __name__ == "__main__":
    unittest.main()
