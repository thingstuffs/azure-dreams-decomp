"""The cover list: which bytes of a linked image are compiled code, compiled data, assembly or retail import.

Built from tiny assembled objects, a hand-written linker map and fake chunk lists; no retail bytes.
"""
import shutil
import subprocess
import tempfile
import unittest
from pathlib import Path

from tools.build import cover as K
from tools.link.combined import object_metadata

AS = shutil.which('mipsel-linux-gnu-as')

OBJECT = """
.section .text.first,"ax"
.globl first
.type first,@function
first:
nop
nop
jr $31
nop
.size first,16
.section .text.noname,"ax"
.globl noname
noname:
nop
jr $31
nop
.section .text.short,"ax"
.globl short
.type short,@function
short:
nop
nop
nop
nop
.size short,8
.section .rodata
.globl table
table:
.word 1,2,3,4
"""

MAP = """Discarded input sections

 .text          0x00000000        0x0 u.o

Linker script and memory map

                0x80080994                        _gp = 0x80080994

.piece_0        0x80010000       0x10 load address 0x00000000
 imports.o(.import_0)
 .import_0      0x80010000       0x10 imports.o
                0x00000001                        ASSERT ((SIZEOF (.piece_0) == 0x10), source/import extent 0)

.piece_1        0x80010010       0x40 load address 0x00000010
 0.o(.text.*)
 .text.first
                0x80010010       0x10 0.o
                0x80010010                u0_first
 .text.noname   0x80010020        0xc 0.o
 .text.short    0x8001002c        0x10 0.o
 *fill*         0x8001003c        0x4
                0x00000001                        ASSERT ((SIZEOF (.piece_1) == 0x40), source/import extent 1)
"""


class MapTests(unittest.TestCase):
    def test_pieces_hold_their_input_sections_with_long_names_on_two_lines(self):
        pieces = K.piece_sections(MAP)
        self.assertEqual(pieces[0], [('.import_0', 0x80010000, 0x10, 'imports.o')])
        self.assertEqual([p[0] for p in pieces[1]], ['.text.first', '.text.noname', '.text.short'])
        self.assertEqual(pieces[1][0][1:3], (0x80010010, 0x10))

    def test_output_sections_with_a_load_address_for_the_executable(self):
        text = ('Linker script and memory map\n\n._800          0x8002d000    0x7f800 load address 0x00000800\n'
                ' build/src/a.o(.text.func_1)\n .text.func_80033AA8\n                0x8002d000       0x40 build/src/a.o\n')
        (row,) = K.map_sections(text, lambda name: name == '._800')
        self.assertEqual(row[:3], ('._800', 0x8002d000, 0x800))
        self.assertEqual(row[3:], ('.text.func_80033AA8', 0x8002d000, 0x40, 'build/src/a.o'))


@unittest.skipUnless(AS, 'MIPS binutils unavailable')
class ObjectTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.dir = Path(self.temp.name)
        (self.dir / 'u.s').write_text(OBJECT)
        subprocess.run([AS, '-EL', '-march=r3000', '-o', str(self.dir / 'u.o'), str(self.dir / 'u.s')], check=True)

    def test_only_a_text_section_with_a_function_symbol_of_its_size_is_code(self):
        metadata = object_metadata(self.dir / 'u.o')
        found = K.complete_function_sections(metadata)
        self.assertEqual(found, {'.text.first': 16})
        # the section without .type/.size, and the one whose symbol is shorter than the section, are data
        self.assertNotIn('.text.noname', found)
        self.assertNotIn('.text.short', found)
        self.assertEqual(K.complete_function_sections(None), {})

    def test_chunk_cover_puts_function_spans_in_code_and_the_rest_in_c_data(self):
        spec = dict(start=0x1000, size=0x50, vma=0x80010000, units=[dict(kind='c', recipe='r', rows=['a'])])
        chunks = [dict(foff=0x1000, size=0x10, origin='retail_import', object='imports.o', section='.import_0'),
                  dict(foff=0x1010, size=0x40, origin='original_object', object='build/.state/link/x/0.o',
                       vma=0x80010010, section='.text.*')]
        cover = K.image_cover(spec, chunks, lambda path: object_metadata(self.dir / 'u.o'), [], MAP)
        self.assertEqual(cover['schema'], 'closure.cover.v1')
        imp, comp = cover['chunks']
        self.assertEqual((imp['class'], imp['code']), ('import', []))
        self.assertEqual(comp['class'], 'c_data')
        self.assertEqual(comp['code'], [[0x1010, 0x10]])

    def test_assembled_units_are_assembly_and_a_table_is_c_data(self):
        spec = dict(start=0, size=0x40, vma=0x80010000, units=[dict(kind='platform_asm'), dict(kind='c')])
        chunks = [dict(foff=0, size=0x10, origin='original_object', object='x/0.o', vma=0x80010000, section='.text'),
                  dict(foff=0x10, size=0x30, origin='retail_import', object='imports.o', section='.import_1')]
        tables = [dict(foff=0x20, size=16, vma=0x80010020, unit=1)]
        cover = K.image_cover(spec, chunks, lambda path: None, tables, MAP)
        classes = [(c['class'], c['origin']) for c in cover['chunks']]
        self.assertEqual(classes, [('assembly', 'original_object'), ('import', 'retail_import'), ('c_data', 'noload_table')])

    def test_unreadable_object_is_fail_closed_data_only(self):
        spec = dict(start=0x1000, size=0x50, vma=0x80010000, units=[dict(kind='c')])
        chunks = [dict(foff=0x1010, size=0x40, origin='original_object', object='x/0.o', vma=0x80010010, section='.text.*')]
        (entry,) = K.image_cover(spec, chunks, lambda path: None, [], MAP)['chunks']
        self.assertEqual((entry['class'], entry['code']), ('c_data', []))

    def test_executable_cover_classes_inputs_by_path(self):
        text = ('Linker script and memory map\n\n._800          0x8002d000       0x80 load address 0x00000800\n'
                ' .text.func_1   0x8002d000       0x10 build/src/code.o\n'
                ' .text          0x8002d010       0x10 build/asm/psyq/libsn/SNMAIN.o\n'
                ' .text          0x8002d020       0x10 build/asm/main.o\n'
                ' .text          0x8002d030       0x10 build/lib/libc.o\n')
        metadata = {'sections': [('.text.func_1', 0x10)], 'symbol_records': [('func_1', '.text.func_1', 0, 0x10, 2)]}
        cover = K.slus_cover(text, {'._800'}, lambda path: metadata, 0x800)
        kinds = [(c['kind'], c['class'], c['foff'], c['code']) for c in cover['chunks']]
        self.assertEqual(kinds, [('c', 'c_data', 0x800, [[0x800, 0x10]]), ('sdk_assembly', 'assembly', 0x810, []),
                                 ('game_assembly', 'assembly', 0x820, []), ('imported', 'import', 0x830, [])])


if __name__ == '__main__':
    unittest.main()
