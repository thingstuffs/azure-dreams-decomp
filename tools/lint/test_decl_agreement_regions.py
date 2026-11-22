#!/usr/bin/env python3
"""Data declaration agreement keyed by load region: synthetic trees with an instance ledger and a link graph."""
import io
import json
import sys
import tempfile
import unittest
from contextlib import redirect_stdout
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import decl_agreement as D  # noqa: E402

# two scene images loaded over the same window, one effect slot elsewhere; foff -> loaded at base
INSTANCES = [
    dict(container='town', foff=0x2AB800, size=0x9800, base=0x80016000),
    dict(container='town', foff=0x2C0000, size=0x9800, base=0x80016000),
    dict(container='dungeon', foff=0x30000, size=0x6000, base=0x80024000),
]
IMAGE_A, IMAGE_B = 0x2AB900, 0x2C0100  # a code offset inside each scene image


class RegionTests(unittest.TestCase):
    def census(self, files, placements, instances=INSTANCES, views=()):
        """files {path: text}; placements {source path: [code offsets]} (all in the town container)."""
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'config/link_graph').mkdir(parents=True)
            (root / 'ledger').mkdir()
            (root / 'config/slus_006.14.symbols.txt').write_text('')
            (root / 'ledger/instance_load_regions.jsonl').write_text(
                ''.join(json.dumps(dict(schema='x', **i)) + '\n' for i in instances))
            tus = []
            for source, offsets in placements.items():
                for n, offset in enumerate(offsets):
                    container, offset = offset if isinstance(offset, tuple) else ('town', offset)
                    tus.append(dict(id=f'{container}/{Path(source).stem}_{n}', source=source,
                                    allocations=[dict(foff=offset, vma=0, size=4, section='.data')]))
            (root / 'config/link_graph/views.000.jsonl').write_text(''.join(
                json.dumps(dict(id=v, attributes=dict(foff=f, size=z, vma=b))) + '\n' for v, f, z, b in views))
            (root / 'config/link_graph/tus.000.jsonl').write_text(''.join(json.dumps(t) + '\n' for t in tus))
            for path, text in files.items():
                (root / path).parent.mkdir(parents=True, exist_ok=True)
                (root / path).write_text(text)
            with redirect_stdout(io.StringIO()):
                return D.data_census(root)[0]

    def test_reused_address_in_two_scene_images_is_two_objects(self):
        found = self.census({'src/town/a.c': 'extern u8 D_80016100[4];\n', 'src/town/b.c': 'extern int D_80016100;\n'},
                            {'src/town/a.c': [IMAGE_A], 'src/town/b.c': [IMAGE_B]})
        self.assertEqual(found, {})

    def test_same_image_two_types_is_a_disagreement_with_its_region(self):
        found = self.census({'src/town/a.c': 'extern u8 D_80016100[4];\n', 'src/town/c.c': 'extern int D_80016100;\n',
                             'src/town/b.c': 'extern short D_80016100;\n'},
                            {'src/town/a.c': [IMAGE_A], 'src/town/c.c': [IMAGE_A + 4], 'src/town/b.c': [IMAGE_B]})
        self.assertEqual(list(found), ['D_80016100@town/0x2ab800'])
        self.assertEqual(found['D_80016100@town/0x2ab800']['region'], 'town/0x2ab800')
        self.assertEqual(len(found['D_80016100@town/0x2ab800']['rows']), 2)

    def test_placed_copy_joins_every_image_it_is_built_in(self):
        found = self.census({'src/town/p.c': 'extern u8 D_80016100[4];\n', 'src/town/q.c': 'extern int D_80016100;\n'},
                            {'src/town/p.c': [IMAGE_A, IMAGE_B], 'src/town/q.c': [IMAGE_B]})
        self.assertEqual(list(found), ['D_80016100@town/0x2ab800+1'])

    def test_resident_alias_under_two_top_directories(self):
        files = {'src/town/a.c': 'extern u8 D_800814A0[4];\n', 'src/dungeon/b.c': 'extern int D_800814A0;\n'}
        found = self.census(files, {'src/town/a.c': [IMAGE_A], 'src/dungeon/b.c': [0x30100]})
        self.assertEqual(list(found), ['D_800814A0@resident'])
        agree = self.census({'src/town/a.c': 'extern int D_800814A0;\n', 'src/dungeon/b.c': 'extern s32 D_800814A0;\n'},
                            {'src/town/a.c': [IMAGE_A], 'src/dungeon/b.c': [0x30100]})
        self.assertEqual(agree, {})

    def test_check_blob_and_shared_bss_stay_one_object(self):
        # TOWN.BIN check images are built per function out of one blob; neither the blob objects (kuseg aliases
        # below every window) nor the bss above the engine (one object per program) belong to any one image
        files = {'src/town/a.c': 'extern u8 D_000045F8[4];\n', 'src/town/b.c': 'extern int D_000045F8;\n',
                 'src/town/c.c': 'extern u8 D_8014A000[8];\n', 'src/town/d.c': 'extern int D_8014A000[2];\n'}
        found = self.census(files, {'src/town/a.c': [0x834800], 'src/town/b.c': [0x834900],
                                    'src/town/c.c': [IMAGE_A], 'src/town/d.c': [IMAGE_B]})
        self.assertEqual(sorted(found), ['D_000045F8@resident', 'D_8014A000@program/town'])

    def test_kseg1_alias_folds_onto_the_image_address(self):
        found = self.census({'src/town/a.c': 'extern u8 D_A0016100[4];\n', 'src/town/c.c': 'extern int D_80016100;\n'},
                            {'src/town/a.c': [IMAGE_A], 'src/town/c.c': [IMAGE_A + 4]})
        self.assertEqual(found, {})  # different spelling is a different name; each is checked per region
        self.assertEqual(D.name_address('D_A0016100'), 0x80016100)
        self.assertEqual(D.name_address('D_000045F8'), 0x800045F8)

    def test_header_declaration_counts_only_where_it_is_included(self):
        files = {'include/town/h.h': 'extern u8 D_80016100[4];\n',
                 'src/town/a.c': '#include "town/h.h"\nextern int D_80016100;\n',
                 'src/town/b.c': 'extern short D_80016100;\n'}
        found = self.census(files, {'src/town/a.c': [IMAGE_A], 'src/town/b.c': [IMAGE_B]})
        self.assertEqual(list(found), ['D_80016100@town/0x2ab800'])
        self.assertEqual(len(found['D_80016100@town/0x2ab800']['rows']), 2)

    ENGINES = (('town/engine', 0xB000, 0x8B0A0, 0x80088760), ('dungeon/engine', 0xA3000, 0x5D8A0, 0x80088760))

    def test_engine_images_come_from_the_link_graph_views(self):
        # town and dungeon engines share 0x80088760 but are never loaded together
        files = {'src/town/a.c': 'extern u8 D_800892C8[4];\n', 'src/dungeon/b.c': 'extern int D_800892C8;\n',
                 'src/town/c.c': 'extern int D_800892C8;\n'}
        placements = {'src/town/a.c': [('town', 0xB100)], 'src/dungeon/b.c': [('dungeon', 0xA3100)],
                      'src/town/c.c': [('town', 0xB200)]}
        found = self.census(files, placements, views=self.ENGINES)
        self.assertEqual(list(found), ['D_800892C8@town/0xb000'])  # a vs c in the town engine; b is the dungeon's

    def test_program_not_one_global_bucket_above_the_executable(self):
        files = {'src/town/a.c': 'extern u8 D_800F8A4C[4];\n', 'src/dungeon/b.c': 'extern int D_800F8A4C;\n'}
        found = self.census(files, {'src/town/a.c': [('town', 0xB100)], 'src/dungeon/b.c': [('dungeon', 0x500000)]})
        self.assertEqual(found, {})  # no image covers it: the town's and the dungeon's own data
        below = self.census({'src/town/a.c': 'extern u8 D_80080AA0[4];\n', 'src/dungeon/b.c': 'extern int D_80080AA0;\n'},
                            {'src/town/a.c': [('town', 0xB100)], 'src/dungeon/b.c': [('dungeon', 0x500000)]})
        self.assertEqual(list(below), ['D_80080AA0@resident'])

    def test_engine_copy_units_join_the_town_engine_only(self):
        files = {'src/town/a.c': 'extern u8 D_80092698[4];\n', 'src/dungeon/level/townmap.c': 'extern int D_80092698;\n',
                 'src/dungeon/x.c': 'extern short D_80092698;\n'}
        placements = {'src/town/a.c': [('town', 0xB100)], 'src/dungeon/level/townmap.c': [('dungeon', 0xD100)],
                      'src/dungeon/x.c': [('dungeon', 0xD200)]}
        views = self.ENGINES + (('dungeon/bank_d0a0', 0xD0A0, 0x41000, 0x8008A800),)
        found = self.census(files, placements, views=views)
        self.assertEqual(list(found), ['D_80092698@town/0xb000'])  # the copy conflicts with town; x.c is d0a0's own

    def test_header_counts_only_for_includers_that_use_the_name(self):
        files = {'include/town/h.h': 'extern u8 D_80016100[4];\n',
                 'src/town/a.c': '#include "town/h.h"\n/* D_80016100 */\nvoid f(void) {}\n',
                 'src/town/b.c': '#include "town/h.h"\nextern int D_80016100;\n'}
        found = self.census(files, {'src/town/a.c': [IMAGE_A], 'src/town/b.c': [IMAGE_B]})
        self.assertEqual(list(found), ['D_80016100@town/0x2c0000'])
        found = self.census(files | {'src/town/a.c': '#include "town/h.h"\nvoid f(void) { D_80016100[0] = 1; }\n'},
                            {'src/town/a.c': [IMAGE_A], 'src/town/b.c': [IMAGE_B]})
        self.assertEqual(sorted(found), ['D_80016100@town/0x2c0000'])

    def test_named_symbols_stay_whole_tree(self):
        found = self.census({'src/town/a.c': 'extern u8 shared_table[4];\n', 'src/town/b.c': 'extern int shared_table;\n'},
                            {'src/town/a.c': [IMAGE_A], 'src/town/b.c': [IMAGE_B]})
        self.assertEqual(list(found), ['shared_table'])

    def test_without_the_instance_ledger_the_top_directory_key_remains(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'config').mkdir()
            (root / 'config/slus_006.14.symbols.txt').write_text('')
            for path, text in {'src/town/a.c': 'extern u8 D_80016100[4];\n',
                               'src/town/b.c': 'extern int D_80016100;\n',
                               'src/dungeon/c.c': 'extern short D_80016100;\n'}.items():
                (root / path).parent.mkdir(parents=True, exist_ok=True)
                (root / path).write_text(text)
            self.assertEqual(list(D.data_census(root)[0]), ['D_80016100@town'])

    def test_gate_line_and_list_carry_the_region(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            for sub in ('base', 'head'):
                (root / sub / 'src/town').mkdir(parents=True)
                (root / sub / 'src/town/a.c').write_text('extern u8 D_800814A0[4];\n')
            (root / 'head/src/town/b.c').write_text('extern int D_800814A0;\n')
            (root / 'head/ledger').mkdir()
            (root / 'head/ledger/instance_load_regions.jsonl').write_text(json.dumps(dict(schema='x', **INSTANCES[0])) + '\n')
            (root / 'head/config').mkdir()
            out = io.StringIO()
            with redirect_stdout(out):
                self.assertEqual(D.check_data(root / 'head', root / 'head', root / 'base'), 1)
            self.assertIn('DATA DISAGREEMENT D_800814A0@resident: incompatible type [region resident]', out.getvalue())
            header = (root / 'head/build/decl_data.tsv').read_text().splitlines()
            self.assertTrue(header[0].endswith('\ttype\tregion'))
            self.assertTrue(header[1].endswith('\tresident'))


if __name__ == '__main__':
    unittest.main()
