import struct
import tempfile
import unittest
from pathlib import Path

from tools import physical_census as census
from tools import monster_bank_loads


class PhysicalCensusTests(unittest.TestCase):
    def test_spawn_tables_contribute_to_declared_bytes(self):
        report = {'dungeon': {'classes': {'dungeon_floor_spawn_table_read': 2048}}}
        self.assertEqual(census.headline(report),
                         '0 bytes with C, 0 bytes with a checked class, '
                         '2,048 bytes with a declared class, 0 bytes unclassed')

    def test_summary_rejects_changed_classes_even_when_file_total_is_equal(self):
        report = {'town': dict(file_bytes=24, classes={'c_text': 8, 'unclassed': 16},
                               c_placement_bytes=0)}
        with tempfile.TemporaryDirectory() as temporary:
            summary = Path(temporary) / 'coverage.tsv'
            summary.write_text(census.table(report))
            census.check_summary(report, summary)
            report['town']['classes']['c_text'] += 4
            report['town']['classes']['unclassed'] -= 4
            with self.assertRaisesRegex(ValueError, 'class totals differ'):
                census.check_summary(report, summary)

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
        data[start:start+4] = (0x80170804).to_bytes(4, 'little')
        loader = dict(foff=0, size=16, sha256=monster_bank_loads.digest(data[:16]))
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
        for entry in (0, 0x80176800):
            data[start:start+4] = entry.to_bytes(4, 'little')
            forged = dict(slot, bank_sha256=monster_bank_loads.digest(data[start:end]))
            with self.assertRaisesRegex(ValueError, 'outside its load window'):
                check(dict(record, slot_load=forged), data, loader)

    def test_monster_bank_entry_word_must_be_an_aligned_window_address(self):
        lba = 0x4340
        start = (lba - 0x3016) * 0x800
        end = start + monster_bank_loads.BANK_BYTES
        loader = dict(foff=0, size=16, sha256=monster_bank_loads.digest(bytes(16)))
        for word in (17, 0x80170800 + 2, 0x80170800 + monster_bank_loads.BANK_BYTES, 0):
            with self.subTest(word=word):
                data = bytearray(end)
                data[start:start+4] = word.to_bytes(4, 'little')
                data[:16] = bytes(16)
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
        retail = bytes(start) + (0x80170804).to_bytes(4, 'little') + bytes(end-start-4)
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

    def test_registered_bank_needs_the_named_entry_at_the_disc_pointer(self):
        _, base, start = monster_bank_loads.normal_geometry(1, 0)
        end = start + monster_bank_loads.BANK_BYTES
        data = bytearray(end)
        struct.pack_into('<I', data, start, base + 12)
        row = dict(row='dungeon/func_fixture', vma=base + 8, foff=start + 8, body_offset=4)
        view = dict(foff=start, vma=base, entries=[row])
        views = {f'dungeon/bank_{start:x}': view}
        record = dict(resource_id=1, slot=0, entry=row['row'])
        check = monster_bank_loads.registered_interval
        self.assertEqual(check(record, data, views), (start, end))
        with self.assertRaisesRegex(ValueError, 'missing from its production view'):
            check(dict(record, entry='dungeon/func_different'), data, views)
        with self.assertRaisesRegex(ValueError, 'lacks its expected production view'):
            check(dict(record, slot=1), data, views)
        struct.pack_into('<I', data, start, base + 16)
        with self.assertRaisesRegex(ValueError, 'pointer differs from its production entry'):
            check(record, data, views)

    def test_placement_loader_checks_both_input_files(self):
        files = {monster_bank_loads.DISC_FILE: bytes(16), 'SLUS_006.14': bytes([2, 3, 5, 7]) + bytes(12)}
        words = [dict(foff='0x0', word={'$retail': dict(file=file, offset=0, length=4,
                                                       sha256=monster_bank_loads.digest(data))})
                 for file, data in files.items()]
        receipt = dict(schema='azure-clean.resource-loader-static.v1', source=monster_bank_loads.LOADER,
                       iso=dict(path=monster_bank_loads.DISC_FILE, lba=0x3016, size=16),
                       iso_directory_record_verified=True, words=words)
        check = monster_bank_loads.check_placement_loader
        check(receipt, *files.values(), dict(foff=0, size=4))
        with self.assertRaisesRegex(ValueError, 'sha256 mismatch'):
            check(receipt, files[monster_bank_loads.DISC_FILE], bytes(16), dict(foff=0, size=4))

    def test_fixed_monster_bank_binds_its_pointer_to_a_registered_body(self):
        lba, base, sectors = monster_bank_loads.EXCEPTIONAL_BANKS[49]
        start = (lba - monster_bank_loads.DISC_LBA) * 2048
        end = start + sectors * 2048
        data = bytearray(end)
        struct.pack_into('<I', data, start, base + 16)
        entry = dict(kind='overlay', container='dungeon', exists=True, c_path='fixture.c',
                     foff=start + 16, size=12, true_name=f'func_{base + 16:08X}')
        registry = {'dungeon/func_fixture': entry}
        record = dict(resource_id=49, entry='dungeon/func_fixture')
        check = monster_bank_loads.exceptional_interval
        self.assertEqual(check(record, data, registry), (start, end))
        with self.assertRaisesRegex(ValueError, 'does not select a fixed monster bank'):
            check(dict(record, resource_id=48), data, registry)
        with self.assertRaisesRegex(ValueError, 'pointer differs from its registered C entry'):
            check(dict(record, entry='dungeon/func_other'), data, registry)
        entry['foff'] += 4
        with self.assertRaisesRegex(ValueError, 'pointer differs from its registered C entry'):
            check(record, data, registry)
