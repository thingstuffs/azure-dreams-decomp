"""target_census.py: masking, word classes and the per-name classification on synthetic evidence."""
import struct
import sys
from pathlib import Path
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import target_census as T  # noqa: E402


class FakeWorld:
    def __init__(self, blob=b'', clone=None):
        self.containers = {'main': blob}
        self._clone = clone

    def clone_of(self, cont, off):
        return self._clone


def row(image, target, evidence, nibble=''):
    return dict(caller_image=image, target=hex(target), evidence=evidence, nibble_fixed=nibble,
                caller_rows='', caller_vma='')


class Census(unittest.TestCase):
    def test_mask_keeps_struct_offsets(self):
        lui = 0x3C028001                    # lui v0, 0x8001
        lo = 0x8C420010                     # lw v0, 0x10(v0)   (%lo of the lui register)
        field = 0x8E0201F0                  # lw v0, 0x1F0(s0)  (struct offset: significant)
        jal = 0x0C000000 | 0x123456
        blob = struct.pack('<4I', lui, lo, field, jal)
        self.assertEqual(T.masked(blob, 0, 16), (0x3C020000, 0x8C420000, field, 0x0C000000))
        self.assertEqual(T.word_class(0x27BDFFE0), 'prologue')
        self.assertEqual(T.word_class(0x03E00008), 'jr_ra')

    def test_classes(self):
        w = FakeWorld()
        same = [dict(cls='start', scope='own_image', image='town/engine', symbol='func_80092320', kind='c',
                     rows=['town/func_80094BC0'], real=True)]
        self.assertEqual(T.classify(w, 'D_80092320', [row('town/engine', 0x80092320, same)], {})[0], 'C_SAME')
        copy = [dict(same[0], symbol='func_80097EC0')]
        self.assertEqual(T.classify(w, 'D_80098104', [row('town/engine', 0x80098104, copy)], {})[0], 'C_COPY')
        lib = [dict(cls='start', scope='slus', image='slus/slus_bin', symbol='RotTransSV',
                    object='build/asm/psyq/libgte/SMP_01_1.o', kind='library')]
        self.assertEqual(T.classify(w, 'func_80065320', [row('dungeon/engine', 0x80065320, lib)], {}),
                         ('LIB', 'RotTransSV (asm/psyq/libgte/SMP_01_1.o)'))
        region = [dict(cls='region', scope='main', image='main/main_bin', symbol='func_80019908', kind='c',
                       linked_at='0x80019908', off='0x269908', region='0x269000@0x80400000',
                       rows=['main/func_80019908'], real=True)]
        self.assertEqual(T.classify(w, 'func_80400908', [row('main/main_bin', 0x80400908, region)], {})[0],
                         'C_PLACEHOLDER')
        mid = [dict(cls='mid', scope='slus', symbol='func_8003CCB0', fdelta='0x268', object='x', wclass='insn')]
        got = T.classify(w, 'func_7003CF18', [row('dungeon/check_x', 0x8003CF18, mid, nibble='0x7003cf18')], {})
        self.assertEqual(got[0], 'FOREIGN_SLUS')
        self.assertIn('nibble corrected', got[1])

    def test_region_gap_function_start_is_missing(self):
        blob = bytearray(0x40)
        struct.pack_into('<I', blob, 0x20, 0x27BDFFD8)      # addiu sp, sp, -40
        w = FakeWorld(bytes(blob))
        gap = [dict(cls='region_gap', scope='main', off='0x20', region='0x0@0x80400000', label='x')]
        self.assertEqual(T.classify(w, 'func_80400020', [row('main/main_bin', 0x80400020, gap)], {})[0], 'MISSING')
        stub = bytearray(0x40)
        struct.pack_into('<3I', stub, 0x20, 0x240A00B0, 0x01400008, 0x2409005C)
        w = FakeWorld(bytes(stub))
        self.assertEqual(T.classify(w, 'func_80400020', [row('main/main_bin', 0x80400020, gap)], {}),
                         ('DEV_LIB', 'BIOS stub B(5Ch) at 0x80400020 off 0x20'))


if __name__ == '__main__':
    unittest.main()
