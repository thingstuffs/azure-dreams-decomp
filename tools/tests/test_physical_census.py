import struct
import tempfile
import unittest

from tools import physical_census as census
from tools import monster_bank_loads


class PhysicalCensusTests(unittest.TestCase):
    def test_overlap_in_copy_views_counts_once(self):
        owned, unclassed = census.partition(24, {
            'c_text': [[4, 16], [8, 16]], 'c_data': [[16, 20]],
            'proven_c_copy': [[12, 16]], 'verified_asset': [[16, 24]],
            'imported_retail_text': [[0, 4]],
        })
        self.assertEqual(owned['c_text'], [[4, 16]])
        self.assertEqual(owned['c_data'], [[16, 20]])
        self.assertEqual(owned['verified_asset'], [[20, 24]])
        self.assertEqual(owned['proven_c_copy'], [])
        self.assertEqual(unclassed, [])

    def test_splits_module_data_and_alignment_out_of_c_text(self):
        rows = [dict(container='dungeon', func='func_example', foff=0, size=24)]
        records = [
            dict(kind='typed_function_pointer', foff=0, size=4),
            dict(kind='alignment', foff=4, size=4),
        ]
        self.assertEqual(census.C.overlay_c_ranges(rows, 'dungeon', {'dungeon': records}),
                         ([[8, 24]], [[0, 4]], [[4, 8]]))

    def test_link_map_binds_load_bounds_and_wrapped_input_sections(self):
        executable = bytearray(0x820)
        executable[:8] = b'PS-X EXE'
        struct.pack_into('<II', executable, 0x18, 0x8002d000, 0x20)
        linker_map = '''
 .text 0x0 0x100 build/src/discarded.o
Linker script and memory map
._800 0x8002d000 0x20 load address 0x800
 .text.sample_identifier
               0x8002d000 0x08 build/src/a.o
 .data         0x8002d008 0x08 build/src/b.o
 .rodata       0x8002d010 0x10 build/module_assets/z.o
'''
        spans = census.slus_spans(linker_map, executable)
        self.assertEqual(spans['c_text'], [[0x800, 0x808]])
        self.assertEqual(spans['c_data'], [[0x808, 0x810]])
        with self.assertRaisesRegex(ValueError, 'bounds'):
            census.slus_spans(linker_map.replace('address 0x800', 'address 0x804'), executable)
        with self.assertRaisesRegex(ValueError, 'overlap'):
            census.slus_spans(linker_map.replace('0x8002d008', '0x8002d004'), executable)


    def test_monster_bank_class_checks_loader_geometry_and_payload(self):
        lba = 0x4340
        start = (lba - 0x3016) * 0x800
        end = start + monster_bank_loads.BANK_BYTES
        data = bytearray(end)
        data[start:start+4] = (0x80170800 + 8).to_bytes(4, 'little')
        loader = dict(foff=0, size=4, sha256=monster_bank_loads.digest(data[:4]))
        slot = dict(resource_id=1, slot=0, sectors=12, lba=lba, destination=0x80170800,
                    file_start=start, file_end=end, delta=0x80170800-start, disc_container_equal=True,
                    bank_sha256=monster_bank_loads.digest(data[start:end]))
        record = dict(schema='r121m.slot-loader-authentication.v1', loader=loader,
                      iso_extent=dict(path='DUNGEON/DUNGEON.BIN', size=len(data), lba=0x3016),
                      iso_record_verified=True, slot_load=slot)
        check = monster_bank_loads.transfer_interval
        self.assertEqual(check(record, data, loader), (start, end))
        with self.assertRaisesRegex(ValueError, 'loader formula'):
            check(dict(record, slot_load=dict(slot, file_end=end-1)), data, loader)
        data[start+8] ^= 1
        with self.assertRaisesRegex(ValueError, 'disc bytes'):
            check(record, data, loader)

    def test_monster_bank_entry_word_must_be_an_aligned_window_address(self):
        lba = 0x4340
        start = (lba - 0x3016) * 0x800
        end = start + monster_bank_loads.BANK_BYTES
        loader = dict(foff=0, size=4, sha256=monster_bank_loads.digest(bytes(4)))
        for word in (17, 0x80170800 + 2, 0x80170800 + monster_bank_loads.BANK_BYTES, 0):
            with self.subTest(word=word):
                data = bytearray(end)
                data[start:start+4] = word.to_bytes(4, 'little')
                data[:4] = bytes(4)
                slot = dict(resource_id=1, slot=0, sectors=12, lba=lba, destination=0x80170800,
                            file_start=start, file_end=end, delta=0x80170800-start,
                            disc_container_equal=True,
                            bank_sha256=monster_bank_loads.digest(data[start:end]))
                record = dict(schema='r121m.slot-loader-authentication.v1', loader=loader,
                              iso_extent=dict(path='DUNGEON/DUNGEON.BIN', size=len(data), lba=0x3016),
                              iso_record_verified=True, slot_load=slot)
                with self.assertRaisesRegex(ValueError, 'entry points outside'):
                    monster_bank_loads.transfer_interval(record, data, loader)

    def test_missing_manifest_is_an_error(self):
        with tempfile.TemporaryDirectory() as folder:
            with self.assertRaisesRegex(ValueError, 'manifest is missing'):
                monster_bank_loads.intervals(folder, bytes(4), bytes(4))

    def test_placement_receipt_checks_transfer_identity(self):
        lba, start = 0x4340, (0x4340 - 0x3016) * 0x800
        end = start + monster_bank_loads.BANK_BYTES
        retail = bytearray(end)
        retail[start:start+4] = (0x80170800 + 8).to_bytes(4, 'little')
        retail = bytes(retail)
        historical_hash = 'a' * 64
        placement = dict(resource_id=1, slot=0, lba=lba, sectors=12, destination=0x80170800,
                         file_start=start, file_end=end, delta=0x80170800-start,
                         disc_container_equal=True, all_sector_payloads_equal=True,
                         loaded_bank_sha256=monster_bank_loads.digest(retail[start:end]),
                         loader_receipt=monster_bank_loads.LOADER_RECEIPT,
                         loader_receipt_sha256=historical_hash, runtime_observed=False,
                         status='PROVEN_STATIC_TRANSFER')
        check = monster_bank_loads.placement_interval
        self.assertEqual(check(placement, retail, (1, 0), historical_hash), (start, end))
        with self.assertRaisesRegex(ValueError, 'different transfer'):
            check(placement, retail, (1, 1), historical_hash)
        with self.assertRaisesRegex(ValueError, 'loader provenance'):
            check(placement, retail, (1, 0), 'b' * 64)

    def test_placement_loader_checks_both_input_files(self):
        files = {monster_bank_loads.DISC_FILE: bytes(4), 'SLUS_006.14': bytes([2, 3, 5, 7])}
        words = [dict(foff='0x0', word={'$retail': dict(file=file, offset=0, length=4,
                                                       sha256=monster_bank_loads.digest(data))})
                 for file, data in files.items()]
        receipt = dict(schema='azure-clean.resource-loader-static.v1', source=monster_bank_loads.LOADER,
                       iso=dict(path=monster_bank_loads.DISC_FILE, lba=0x3016, size=4),
                       iso_directory_record_verified=True, words=words)
        check = monster_bank_loads.check_placement_loader
        check(receipt, *files.values(), dict(foff=0, size=4))
        with self.assertRaisesRegex(ValueError, 'differs from disc'):
            check(receipt, files[monster_bank_loads.DISC_FILE], bytes(4), dict(foff=0, size=4))
