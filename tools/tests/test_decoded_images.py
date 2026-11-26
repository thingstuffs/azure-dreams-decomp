"""Decoded coordinates, complete-section proof and exact stream regression tests."""
import copy
import json
import os
from pathlib import Path
import random
import shutil
import struct
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
from tools.decoded import bindings, call_targets, import_ranges
from tools.decoded.lz import decode, encode
from tools import decoded_images as D
from tools.decoded.census import discover, signatures
from tools.decoded.genuine import linked_data


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


class BindingIdentityTests(unittest.TestCase):
    def setUp(self):
        self.image = dict(
            image='sample/menu', address=0x80016000, size=32,
            symbols={'read_message': 0x80016010, 'timer': 0x80030000},
            units=[dict(placement='caller', bindings={'home_entry': 0x80016000},
                        functions=[dict(name='caller_entry', address=0x80016008)]),
                   dict(placement='helper', functions=[dict(name='local_entry', symbol='home_entry',
                                                             address=0x80016000)]),
                   dict(functions=[dict(name='different_entry', address=0x80016004)])],
        )
        self.data = bytes(16) + b'sample text 0123'
        self.homes = {('timer', 0x80030000)}
        self.evidence = {('read_message', 0x80016010): (16, D.digest(b'sample text 0123'))}

    def test_binding_names_and_decoded_extent_agree(self):
        self.assertEqual(bindings.audit(self.image, self.homes, self.evidence, data=self.data),
                         {'global': 2, 'placement': 1, 'address_names': 0})

    def test_binding_to_a_different_export_fails(self):
        self.image['units'][0]['bindings']['home_entry'] = 0x80016004
        with self.assertRaisesRegex(ValueError, 'points to the decoded export different_entry'):
            bindings.audit(self.image, self.homes, self.evidence, data=self.data)

    def test_global_binding_to_a_different_address_fails(self):
        self.image['symbols']['timer'] += 4
        with self.assertRaisesRegex(ValueError, 'no binding identity for timer'):
            bindings.audit(self.image, self.homes, self.evidence, data=self.data)

    def test_imported_binding_digest_must_match(self):
        with self.assertRaisesRegex(ValueError, 'binding extent differs for read_message'):
            bindings.audit(self.image, self.homes, self.evidence, data=bytes(32))


    def test_short_binding_extent_has_no_digest(self):
        short = {('read_message', 0x80016010): (7, '-')}
        self.assertEqual(bindings.audit(self.image, self.homes, short, data=bytes(32)),
                         {'global': 2, 'placement': 1, 'address_names': 0})

    def test_short_binding_extent_with_a_digest_is_refused(self):
        with tempfile.TemporaryDirectory() as folder:
            path = Path(folder) / 'evidence.tsv'
            path.write_text('symbol\taddress\tsize\tsha256\nread_message\t0x80016010\t7\t' + ('f' * 64) + '\n')
            with self.assertRaisesRegex(ValueError, 'invalid decoded binding evidence'):
                bindings.read_evidence(path)


class PlacedCallTests(unittest.TestCase):
    def test_same_address_in_another_load_image_must_have_the_same_callee(self):
        base, target = 0x80016000, 0x80045010
        caller = dict(name='placed', symbol='home_caller', address=base, size=4)
        image = dict(address=base, size=4, symbols={},
                     units=[dict(source='caller.c', placement='placed', functions=[caller],
                                 bindings={'callee': target})],
                     call_context=dict(engine='dungeon/engine', bank_calls={}, exceptions=[]),
                     import_layout=dict(holds='holds.tsv'), image='fixture/menu')
        obj = SimpleNamespace(relocs=[('.text.home_caller', 0, '26', ('sym', 'callee'), 0)])
        geometry = dict(vma=base, foff=0)
        row = dict(container='town', id='town/caller', foff=0)
        registry = SimpleNamespace(
            links=({'town/one': geometry, 'town/two': geometry},),
            ordinary_callers=lambda source, name: [(row, 'town/one'), (row, 'town/two')],
            menu_target=lambda context, name, address: 'callee',
            in_view=lambda view, address: 'callee',
        )
        data = struct.pack('<I', (3 << 26) | ((target >> 2) & 0x03ffffff))
        with tempfile.TemporaryDirectory(dir=ROOT/'build') as tmp, patch.object(
                call_targets, 'OrdinaryFunctions', return_value=registry):
            root = Path(tmp)
            (root/'holds.tsv').write_text('offset\tsize\treason\tfirst_difference\n')
            path = root/'work/disc/containers/TOWN_TOWN.BIN'
            path.parent.mkdir(parents=True)
            path.write_bytes(data)
            def check():
                return call_targets.audit(root, image, {'caller.c': obj}, {}, data, D.number)
            self.assertEqual(check(), (1, 2, 0))
            registry.ordinary_callers = lambda source, name: []
            with self.assertRaisesRegex(ValueError, 'no registered load image'):
                check()
            registry.ordinary_callers = lambda source, name: [(row, 'town/two')]
            registry.in_view = lambda view, address: 'other' if view == 'town/two' else 'callee'
            with self.assertRaisesRegex(ValueError, 'town/two.*found other'):
                check()


class ImportRangeTests(unittest.TestCase):
    def setUp(self):
        base = 0x80016000
        self.image = dict(
            address=base, size=32,
            units=[dict(source='src/fixture.c',
                        functions=[dict(address=base + 8, size=4), dict(address=base + 16, size=4)],
                        data=[dict(section='.data', address=base + 24, size=4)])],
            symbols={'item_name': base},
            import_layout=dict(code=[8, 20], text_symbols=['item_name'],
                               text_tables=[dict(source='src/fixture.c', section='.data',
                                                 offset=0, count=1, stride=4, pointers=[0])]),
            import_classes=dict(code=4, text=8, alignment=4, data=4),
        )
        self.data = b'item\0' + bytes(19) + struct.pack('<I', base + 28) + b'ok\0\0'

    def test_derive_uses_string_references_and_keeps_an_aligned_zero_word_as_data(self):
        rows = import_ranges.derive(self.image, self.data, D.number)
        self.assertEqual([row[:3] for row in rows],
                         [(0, 5, 'text'), (5, 3, 'alignment'), (12, 4, 'code'),
                          (20, 4, 'data'), (28, 3, 'text'), (31, 1, 'alignment')])
        self.assertEqual(import_ranges.audit(self.image, rows, D.number, data=self.data),
                         self.image['import_classes'])

    def test_short_ranges_carry_no_digest(self):
        rows = import_ranges.derive(self.image, self.data, D.number)
        self.assertTrue(all(row[3] == '-' for row in rows))

    def test_short_range_with_a_digest_is_refused(self):
        with tempfile.TemporaryDirectory() as folder:
            path = Path(folder) / 'ranges.tsv'
            path.write_text('offset\tsize\tclass\tsha256\n0x0000\t5\ttext\t' + ('f' * 64) + '\n')
            with self.assertRaisesRegex(ValueError, 'invalid decoded import range'):
                import_ranges.read_table(path)

    def test_long_range_without_a_digest_is_refused(self):
        with tempfile.TemporaryDirectory() as folder:
            path = Path(folder) / 'ranges.tsv'
            path.write_text('offset\tsize\tclass\tsha256\n0x0000\t20\tdata\t-\n')
            with self.assertRaisesRegex(ValueError, 'invalid decoded import range'):
                import_ranges.read_table(path)

    def test_range_digest_drift_fails(self):
        base = 0x80016000
        image = dict(address=base, size=40, units=[dict(source='src/fixture.c', functions=[dict(address=base, size=4)], data=[])],
                     symbols={}, import_layout=dict(code=[0, 4], text_symbols=[], text_tables=[]),
                     import_classes=dict(code=0, text=0, alignment=0, data=36))
        data = bytes(range(1, 41))
        rows = import_ranges.derive(image, data, D.number)
        self.assertEqual(rows[-1][3], D.digest(data[4:]))
        updated = data[:10] + b'I' + data[11:]
        with self.assertRaisesRegex(ValueError, 'differs from the derived ranges'):
            import_ranges.audit(image, rows, D.number, data=updated)

    def test_short_text_extent_change_fails(self):
        rows = import_ranges.derive(self.image, self.data, D.number)
        updated = b'\0' + self.data[1:]
        with self.assertRaisesRegex(ValueError, 'differs from the derived ranges'):
            import_ranges.audit(self.image, rows, D.number, data=updated)

    def test_range_size_change_fails(self):
        rows = import_ranges.derive(self.image, self.data, D.number)
        rows[0] = (rows[0][0], rows[0][1] + 1) + rows[0][2:]
        with self.assertRaises(ValueError):
            import_ranges.audit(self.image, rows, D.number, data=self.data)

    def test_function_holds_cover_imported_code_and_bound_the_trial_difference(self):
        rows = import_ranges.derive(self.image, self.data, D.number)
        header = 'offset\tsize\treason\tfirst_difference\n'
        with tempfile.TemporaryDirectory(dir=ROOT/'build') as tmp:
            path = Path(tmp) / 'holds.tsv'
            path.write_text(header + '0x0c\t4\tThe return value differs.\t0x0c\n')
            self.assertEqual(import_ranges.audit_holds(path, self.image, rows, D.number), 1)
            path.write_text(header + '0x0c\t4\tThe return value differs.\t0x10\n')
            with self.assertRaisesRegex(ValueError, 'first difference outside'):
                import_ranges.audit_holds(path, self.image, rows, D.number)
            path.write_text(header)
            with self.assertRaisesRegex(ValueError, 'differ from imported'):
                import_ranges.audit_holds(path, self.image, rows, D.number)

    def test_text_requires_emitted_uses_and_a_relocated_pointer_in_each_table_slot(self):
        unit = self.image['units'][0]
        unit['functions'][0]['name'] = 'read_label'
        unit['functions'][1]['name'] = 'read_table'
        table = self.image['import_layout']['text_tables'][0]
        table.update(symbol='labels', bank='label_bank')
        self.image['symbols']['label_bank'] = self.image['address'] + 28
        data = bytearray(self.data)
        struct.pack_into('<I', data, 8, self.image['address'])
        struct.pack_into('<I', data, 16, self.image['address'] + 24)
        relocs = [('.text.read_label', 0, '32', ('sym', 'item_name'), 0),
                  ('.text.read_table', 0, 'LO16', ('sym', 'labels'), 0),
                  ('.data', 0, '32', ('sym', 'label_bank'), 0)]
        obj = SimpleNamespace(symbols={'labels': ('.data', 0, 'global', 0)}, relocs=relocs)
        def check():
            import_ranges.audit_references(self.image, {unit['source']: obj}, {}, data, D.number)
        check()
        struct.pack_into('<I', data, 16, 0)
        with self.assertRaisesRegex(ValueError, 'text relocation differs'):
            check()
        struct.pack_into('<I', data, 16, self.image['address'] + 24)
        self.image['symbols']['unused'] = self.image['address'] + 20
        self.image['import_layout']['text_symbols'].append('unused')
        with self.assertRaisesRegex(ValueError, 'lacks a compiled reference'):
            check()
        self.image['import_layout']['text_symbols'].pop()
        obj.relocs = relocs[:-1]
        with self.assertRaisesRegex(ValueError, 'lacks its linked text relocation'):
            check()
        obj.relocs = relocs
        struct.pack_into('<I', data, 8, self.image['address'] + 4)
        with self.assertRaisesRegex(ValueError, 'text relocation differs'):
            check()

    def test_short_decoded_stream_receipts_keep_only_the_extent(self):
        payload = b'abcd'
        packed = D.encode(payload)
        command = [5, 16, 20, 0, 0, 0, 0, 0]
        source = 'work/disc/containers/SAMPLE.BIN'
        stream = dict(container=source, offset=20, command=command, used=len(packed),
                      input_limit=len(packed), size=len(payload), source_sha256='-', decoded_sha256='-')
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            path = root / source
            path.parent.mkdir(parents=True)
            path.write_bytes(struct.pack('<HHIhhhhI', *command) + packed)
            data, (receipt,) = D.reproduce(root, dict(streams=[stream], size=len(payload), sha256='-'))
        self.assertEqual(data, payload)
        self.assertEqual((receipt['source_sha256'], receipt['decoded_sha256']), ('-', '-'))

    def test_short_extents_have_no_digest(self):
        rows = import_ranges.derive(self.image, self.data, D.number)
        self.assertTrue(all(row[3] == '-' for row in rows))
        self.assertEqual(D.extent_digest(bytes(15)), '-')
        self.assertEqual(D.extent_digest(bytes(16)), D.digest(bytes(16)))

    def test_range_missing_from_imports_fails(self):
        rows = import_ranges.derive(self.image, self.data, D.number)
        with self.assertRaisesRegex(ValueError, 'does not cover exactly'):
            import_ranges.audit(self.image, rows[:-1], D.number)


class GenuineDataTests(unittest.TestCase):
    def test_genuine_pointer_table_resolves_complete_data_words(self):
        section = '.rdata'
        view = SimpleNamespace(
            obj=SimpleNamespace(sections={section: bytes(8) + b'\x7f'}),
            rel={(section, 0): ('32', ('fn', 'entry', 4)),
                 (section, 4): ('32', ('sec', '.rodata', 8))},
        )
        anchors = {'.rodata': 0x80017000}
        resolver = {'entry': 0x80016400}.get
        self.assertEqual(linked_data(view, section, resolver, anchors),
                         struct.pack('<II', 0x80016404, 0x80017008) + b'\x7f')
        view.rel[(section, 0)] = ('32', ('sym', 'unbound', 0))
        with self.assertRaisesRegex(ValueError, 'unbound decoded data relocation'):
            linked_data(view, section, resolver, anchors)


class RegistryFixture(unittest.TestCase):
    """Temporary root holding the menu-cache registry and fixture sources (no tests of its own)."""
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(dir=ROOT/'build')
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.spec = json.loads((ROOT/'config/decoded/menu_cache.json').read_text())
        for unit in self.spec['units']:
            for key in ('source', 'header'):
                if key not in unit:
                    continue
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

    def pin_fixture_coverage(self):
        units = self.spec['units']
        functions = [function for unit in units for function in unit['functions']]
        text = sum(function['size'] for function in functions)
        data = sum(datum['size'] for unit in units for datum in unit.get('data', []))
        stream = sum(s['used'] for s in self.spec['streams']) if self.spec['proof_mode'] == 'recompress' else 0
        self.spec['coverage'].update(functions=len(functions), text_bytes=text, data_bytes=data,
                                     imported_bytes=self.spec['size'] - text - data,
                                     stream_bytes=stream)

    def write(self):
        spec = copy.deepcopy(self.spec)
        if spec['proof_mode'] == 'decoded-only':
            spec.pop('binding_evidence', None)
            spec.pop('import_layout', None)
        (self.root/'config/decoded/menu_cache.json').write_text(json.dumps(spec))


class RegistryTests(RegistryFixture):
    def test_scope_includes_project_headers_outside_the_manifest(self):
        from tools.lanes.prove_scope import decoded_scope
        entry_header = self.root / self.spec['units'][0]['header']
        for path in ('include/town/fixture_transitive.h', 'src/dungeon/fixture_local.h'):
            with self.subTest(path=path):
                header = self.root / path
                header.parent.mkdir(parents=True, exist_ok=True)
                header.write_text('/* included by a decoded translation unit */\n')
                include = os.path.relpath(header, entry_header.parent)
                entry_header.write_text(f'#include "{include}"\n')
                selected, consumed = decoded_scope(self.root, {path})
                self.assertEqual(selected, [self.spec['image']])
                self.assertEqual(consumed, {path})


    def test_owned_sources_exclude_a_placement_only_home(self):
        from tools.headers.extern_bulk import decoded_sources
        own = self.spec['units'][0]
        placed = dict(source='src/town/fixture_home.c', compiler=own['compiler'],
                      flags=own['flags'], placement='fixture_copy', bindings={},
                      functions=[dict(name='fixture_copy', symbol='fixture_original',
                                      address='0x80016000', size=8)])
        (self.root / placed['source']).parent.mkdir(parents=True, exist_ok=True)
        (self.root / placed['source']).write_text('void fixture_original(void) {}\n')
        self.spec['units'] = [own, placed]
        self.pin_fixture_coverage()
        self.write()
        self.assertEqual(decoded_sources(self.root), {own['source']})


    def test_rows_use_explicit_decoded_identity(self):
        rows = D.rows(self.root)
        self.assertEqual(len(rows), sum(len(unit['functions']) for unit in self.spec['units']))
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

    def test_coverage_pin_detects_a_function_becoming_an_import(self):
        self.spec['units'][0]['functions'].pop()
        self.write()
        with self.assertRaisesRegex(ValueError, 'decoded coverage differs'):
            D.manifests(self.root)

    def test_recompression_requires_both_evidence_inputs(self):
        for key in ('import_layout', 'binding_evidence'):
            value = self.spec.pop(key)
            self.write()
            with self.assertRaisesRegex(ValueError, 'recompression requires ' + key):
                D.manifests(self.root)
            self.spec[key] = value

    def test_coverage_pin_is_required(self):
        del self.spec['coverage']
        self.write()
        with self.assertRaisesRegex(ValueError, 'decoded coverage differs'):
            D.manifests(self.root)

    def test_menu_cache_import_classes(self):
        image = D.manifests(self.root)[0]
        classes = image['import_classes']
        self.assertEqual(classes, dict(code=1156, text=1964, alignment=128, data=12))
        self.assertEqual(sum(classes.values()), image['coverage']['imported_bytes'])

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

    def test_genuine_assembler_recipe_accepts_only_unchecked_division(self):
        unit = self.spec['units'][0]
        unit['genuine_asflags'] = ['-0']
        self.write()
        self.assertEqual(D.manifests(self.root)[0]['units'][0]['genuine_asflags'], ['-0'])
        unit['genuine_asflags'] = ['-G8']
        self.write()
        with self.assertRaisesRegex(ValueError, 'genuine assembler recipe'):
            D.manifests(self.root)

    def test_placement_accepts_a_distinct_export_from_a_home_source(self):
        self.spec['units'] = self.spec['units'][:2]
        unit = copy.deepcopy(self.spec['units'][0])
        unit.pop('data', None)
        unit.update(placement='home_copy', bindings={'resident_call': '0x80045000'})
        unit['functions'] = [dict(name='home_copy_entry', symbol='func_800B5264',
                                  address='0x80016000', size=144)]
        self.spec['units'].append(unit)
        self.pin_fixture_coverage()
        self.write()
        row = D.rows(self.root)[-1]
        self.assertEqual((row['placement'], row['symbol']), ('home_copy', 'func_800B5264'))
        unit['bindings']['func_800B5264'] = '0x80016000'
        self.write()
        with self.assertRaisesRegex(ValueError, 'export also supplied'):
            D.manifests(self.root)

    def test_reject_owned_data_that_overlaps_text(self):
        unit = self.spec['units'][0]
        unit['data'] = [dict(section='.rodata', address=unit['functions'][0]['address'], size=8)]
        self.write()
        with self.assertRaisesRegex(ValueError, 'overlapping decoded extents'):
            D.manifests(self.root)

    def test_altered_source_command_fails_before_decoding(self):
        path = self.root / self.spec['streams'][0]['container']
        path.parent.mkdir(parents=True)
        with path.open('wb') as output:
            output.truncate(D.number(self.spec['streams'][0]['offset']) + 0x4000)
        with self.assertRaisesRegex(ValueError, 'command differs'):
            D.reproduce(self.root, self.spec)


@unittest.skipUnless(shutil.which('mipsel-linux-gnu-as'), 'MIPS binutils required')
class PlacementLinkTests(RegistryFixture):
    def test_complete_export_can_be_linked_twice_with_private_bindings(self):
        unit = self.spec['units'][0]
        unit.pop('data', None)
        unit.update(placement='first', bindings={'resident_call': '0x80045100',
                                                'resident_data': '0x80078020'})
        unit['functions'] = [dict(name='first_copy', symbol='home_call',
                                  address='0x80016000', size=16)]
        second = copy.deepcopy(unit)
        second.update(placement='second', bindings={'resident_call': '0x80045200',
                                                    'resident_data': '0x80068120'})
        second['functions'][0].update(name='second_copy', address='0x80016010')
        stream = dict(self.spec['streams'][0], size=32)
        self.spec.update(units=[unit, second], streams=[stream], size=32, proof_mode='decoded-only')
        self.pin_fixture_coverage()
        self.write()
        (image,) = D.manifests(self.root)
        work = self.root/'build/decoded/dungeon/menu_cache'
        work.mkdir(parents=True)
        source = work/'home.s'
        source.write_text('''
.set noreorder
.section .text.home_call,"ax",@progbits
.globl home_call
home_call:
    jal resident_call
    nop
    lui $2,%hi(resident_data)
    addiu $2,$2,%lo(resident_data)
.section .text.other_function,"ax",@progbits
    jal unregistered
    nop
.section .rodata,"a",@progbits
    .word 1
''')
        obj = work/'unit_0.o'
        D.run(self.root, ['mipsel-linux-gnu-as', '-EL', '-march=r3000', '-o', str(obj), str(source)])
        expected = struct.pack('<8I', 0x0C011440, 0, 0x3C028008, 0x24428020,
                               0x0C011480, 0, 0x3C028007, 0x24428120)
        with patch.object(D, 'reproduce', return_value=(expected, [])):
            proof = D.build(self.root, image, compile_units=False)
            self.assertEqual(proof['decoded_c_text_bytes'], len(expected))
            self.assertEqual(proof['decoded_imported_bytes'], 0)
            image['units'][1]['bindings']['resident_call'] = '0x80045204'
            with self.assertRaisesRegex(ValueError, 'decoded image C differs'):
                D.build(self.root, image, compile_units=False)
            del image['units'][1]['bindings']['resident_call']
            with self.assertRaisesRegex(ValueError, 'undefined reference'):
                D.build(self.root, image, compile_units=False)

    def test_link_and_compare_exact_owned_read_only_data(self):
        unit = self.spec['units'][0]
        unit['functions'] = [dict(name='home_call', address='0x80016004', size=8)]
        unit['data'] = [dict(section='.rodata', address='0x80016000', size=4)]
        self.spec.update(units=[unit], streams=[dict(self.spec['streams'][0], size=12, decoded_sha256='-')],
                         size=12, sha256='-', proof_mode='decoded-only')
        self.pin_fixture_coverage()
        self.write()
        (image,) = D.manifests(self.root)
        work = self.root/'build/decoded/dungeon/menu_cache'
        work.mkdir(parents=True)
        source = work/'home.s'
        source.write_text('''
.set noreorder
.section .text.home_call,"ax",@progbits
.globl home_call
home_call:
    jr $31
    nop
.section .rodata,"a",@progbits
    .word 7
''')
        D.run(self.root, ['mipsel-linux-gnu-as', '-EL', '-march=r3000', '-o', str(work/'unit_0.o'), str(source)])
        expected = struct.pack('<3I', 7, 0x03E00008, 0)
        with patch.object(D, 'reproduce', return_value=(expected, [])):
            proof = D.build(self.root, image, compile_units=False)
            self.assertEqual(proof['decoded_c_data_bytes'], 4)
            self.assertEqual(proof['decoded_imported_bytes'], 0)
        with patch.object(D, 'reproduce', return_value=(struct.pack('<3I', 8, 0x03E00008, 0), [])):
            with self.assertRaisesRegex(ValueError, 'decoded image C differs.*rodata'):
                D.build(self.root, image, compile_units=False)

    def test_owned_data_can_end_before_an_unaligned_import(self):
        unit = self.spec['units'][0]
        unit['functions'] = [dict(name='home_call', address='0x80016004', size=8)]
        unit['data'] = [dict(section='.rodata', address='0x80016000', size=1, trim_end_padding=True)]
        self.spec.update(units=[unit], streams=[dict(self.spec['streams'][0], size=12, decoded_sha256='-')],
                         size=12, sha256='-', proof_mode='decoded-only')
        self.pin_fixture_coverage()
        self.write()
        (image,) = D.manifests(self.root)
        work = self.root/'build/decoded/dungeon/menu_cache'
        work.mkdir(parents=True)
        source = work/'home.s'
        source.write_text('''
.set noreorder
.section .text.home_call,"ax",@progbits
.globl home_call
home_call:
    jr $31
    nop
.section .rodata,"a",@progbits
    .balign 4
    .byte 7
''')
        D.run(self.root, ['mipsel-linux-gnu-as', '-EL', '-march=r3000', '-o', str(work/'unit_0.o'), str(source)])
        expected = struct.pack('<4B2I', 7, 8, 9, 10, 0x03E00008, 0)
        with patch.object(D, 'reproduce', return_value=(expected, [])):
            proof = D.build(self.root, image, compile_units=False)
            self.assertEqual(proof['decoded_c_data_bytes'], 1)
            self.assertEqual(proof['decoded_imported_bytes'], 3)
            del image['units'][0]['data'][0]['trim_end_padding']
            with self.assertRaisesRegex(ValueError, 'mismatched decoded TU data'):
                D.build(self.root, image, compile_units=False)


@unittest.skipUnless(os.environ.get('AZURE_DECODED_RETAIL_TEST'), 'explicit private retail fixture required')
class RetailTests(unittest.TestCase):
    def test_whole_image_streams_container_and_tampered_artifact(self):
        proofs = D.build_all(ROOT)
        proof = next(record for record in proofs if record['image'] == 'dungeon/menu_cache')
        self.assertEqual(len(proof['functions']), 426)
        self.assertEqual(proof['decoded_c_text_bytes'], 56012)
        self.assertEqual(proof['decoded_c_data_bytes'], 920)
        self.assertEqual(proof['compressed_stream_bytes'], 28662)
        self.assertEqual(proof['decoded_imported_bytes'], 3260)
        self.assertEqual((ROOT/'build/decoded/disc/DUNGEON/DUNGEON.BIN').read_bytes(),
                         (ROOT/'work/disc/containers/DUNGEON_DUNGEON.BIN').read_bytes())
        stream = proof['compressed_streams'][0]
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
        image['proof_mode'] = 'decoded-only'
        image.pop('import_layout')
        image['units'][0]['functions'][0]['size'] -= 4
        with self.assertRaisesRegex(ValueError, 'complete decoded TU text extents'):
            D.build(ROOT, image)


if __name__ == '__main__':
    unittest.main()
