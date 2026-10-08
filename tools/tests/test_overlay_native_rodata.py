"""Native module heads: real ELF relocations and adversarial bound receipts."""
import copy
import json
from pathlib import Path
import shutil
import struct
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / 'tools/gate'), str(ROOT / 'tools/fidelity')]
import overlay_native_rodata as N
import aspsx_diff as A

ASM = '''.rdata
.align 2
.globl native_entry
native_entry:
.word func_test
.text
.align 2
.globl func_test
.ent func_test
func_test:
.set noreorder
lui $2,%hi($L10)
addiu $2,$2,%lo($L10)
sll $4,$4,2
addu $2,$2,$4
lw $2,0($2)
nop
j $2
nop
.rdata
.align 3
$L10:
.word $L1
.word $L2
.word $L3
.word $L4
.word $L5
.text
$L1:
addiu $2,$0,1
$L2:
addiu $2,$0,2
$L3:
addiu $2,$0,3
$L4:
addiu $2,$0,4
$L5:
j $31
nop
.end func_test
.size func_test,.-func_test
'''


@unittest.skipUnless(shutil.which('mipsel-linux-gnu-as'), 'MIPS assembler required')
class NativeHeadTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.tmp = tempfile.TemporaryDirectory()
        cls.path = Path(cls.tmp.name)
        sectioned = ASM.replace('.text', '.section .text.func_test,"ax",@progbits')
        (cls.path / 'in.s').write_text(sectioned)
        subprocess.run(['mipsel-linux-gnu-as', '-EL', '-march=r3000', '-G0',
                        '-o', str(cls.path / 'in.o'), str(cls.path / 'in.s')], check=True)
        cls.raw = (cls.path / 'in.o').read_bytes()
        cls.trim_path = ROOT / 'tools/build/slus_rodata_trim.py'
        v = A.View(A.read_elf(cls.raw))
        size = v.funcs['func_test'][2]
        cls.module = {'key': 'native_test', 'membership_evidence': 'pending.json',
                      'members': [{'function': 'func_test', 'foff': 0x100,
                                   'vma': 0x80024000, 'size': size + 28, 'body_offset': 28}],
                      'owned_data': []}
        for offset, size, kind, rest in [
            (0, 4, 'typed_function_pointer', {'symbol': 'native_entry', 'target': 'func_test'}),
            (4, 4, 'alignment', {'alignment': 8}),
            (8, 20, 'switch_table', {'owner': 'func_test'}),
        ]:
            cls.module['owned_data'].append(dict(section='.rodata', foff=0x100 + offset,
                                                vma=0x80024000 + offset, size=size, kind=kind, **rest))

    @classmethod
    def tearDownClass(cls):
        cls.tmp.cleanup()

    def setUp(self):
        self.m = copy.deepcopy(self.module)
        self.obj, self.trim = N.prepare_object(self.m, self.raw, self.trim_path)
        self.view = A.View(A.read_elf(self.obj))
        self.artifacts = {'module.untrimmed.o': self.raw, 'module.o': self.obj, 'IN.S': ASM.encode()}

    def proof(self):
        return N.make_proof(self.m, self.raw, self.obj, self.view, self.view,
                            ASM, self.trim_path, self.artifacts)

    def test_native_table_head_accepted(self):
        N.validate_layout(self.m)
        proof = self.proof()
        self.assertEqual(proof['trim']['trimmed'], 4)
        self.assertEqual(len(proof['native']['relocations']), 6)
        N.verify_proof(self.m, proof, self.raw, self.obj, self.view, self.view,
                       ASM, self.trim_path, self.artifacts)

    def test_trim_without_receipt_refused(self):
        with self.assertRaisesRegex(ValueError, 'receipt missing'):
            N.verify_proof(self.m, None, self.raw, self.obj, self.view, self.view,
                           ASM, self.trim_path, self.artifacts)

    def elf_sections(self, raw):
        off = struct.unpack_from('<I', raw, 32)[0]
        ent, count, si = struct.unpack_from('<HHH', raw, 46)
        hs = [struct.unpack_from('<10I', raw, off + i * ent) for i in range(count)]
        strings = raw[hs[si][4]:hs[si][4] + hs[si][5]]
        names = [strings[h[0]:].split(b'\0', 1)[0].decode() for h in hs]
        return hs, names

    def test_trim_over_relocation_refused(self):
        raw = bytearray(self.raw)
        hs, names = self.elf_sections(raw)
        relocation = hs[names.index('.rel.rodata')]
        struct.pack_into('<I', raw, relocation[4], 28)
        with self.assertRaisesRegex(ValueError, 'relocation.*cut tail'):
            N.prepare_object(self.m, raw, self.trim_path)

    def test_table_relocation_outside_module_refused(self):
        raw = bytearray(self.obj)
        hs, names = self.elf_sections(raw)
        rodata = hs[names.index('.rodata')]
        struct.pack_into('<I', raw, rodata[4] + 8, 0x1000)
        view = A.View(A.read_elf(raw))
        with self.assertRaisesRegex(ValueError, 'outside its owning function'):
            N.validate_relocations(self.m, view)

    def test_symbol_at_trim_boundary_refused(self):
        raw = bytearray(self.raw)
        hs, names = self.elf_sections(raw)
        syms = hs[names.index('.symtab')]
        ri = names.index('.rodata')
        for pos in range(syms[4], syms[4] + syms[5], 16):
            name, value, size, info, other, section = struct.unpack_from('<IIIBBH', raw, pos)
            if section == ri and name:
                struct.pack_into('<IIIBBH', raw, pos, name, 28, 0, info, other, section)
                break
        else:
            self.fail('test fixture has no rodata symbol')
        with self.assertRaisesRegex(ValueError, 'symbol.*cut tail'):
            N.prepare_object(self.m, raw, self.trim_path)

    def test_nonzero_trim_refused(self):
        raw = bytearray(self.raw)
        hs, names = self.elf_sections(raw)
        raw[hs[names.index('.rodata')][4] + 28] = 1
        with self.assertRaisesRegex(ValueError, 'not zero padding'):
            N.prepare_object(self.m, raw, self.trim_path)

    def test_changed_receipt_refused(self):
        proof = self.proof()
        proof['artifacts']['module.untrimmed.o'] = '0' * 64
        with self.assertRaisesRegex(ValueError, 'unbound or changed'):
            N.verify_proof(self.m, proof, self.raw, self.obj, self.view, self.view,
                           ASM, self.trim_path, self.artifacts)

    def test_raw_numeric_table_refused(self):
        with self.assertRaisesRegex(ValueError, 'not emitted by its owner'):
            N.validate_switch_assembly(self.m, ASM.replace('.word $L1', '.word 2147631200'))

    def test_nonzero_alignment_refused(self):
        raw = bytearray(self.obj)
        hs, names = self.elf_sections(raw)
        raw[hs[names.index('.rodata')][4] + 4] = 1
        with self.assertRaisesRegex(ValueError, 'alignment is not zero'):
            N.validate_relocations(self.m, A.View(A.read_elf(raw)))

    def test_missing_table_dispatch_refused(self):
        with self.assertRaisesRegex(ValueError, 'own switch dispatch'):
            N.validate_switch_assembly(self.m, ASM.replace('%hi($L10)', '%hi(external)'))

    def test_extra_relocation_refused(self):
        self.view.rel[('.rodata', 4)] = ('32', ('fn', 'func_test', 0))
        self.view.obj.relocs.append(('.rodata', 4, '32', ('sym', 'func_test'), 0))
        with self.assertRaisesRegex(ValueError, 'inventory differs'):
            N.validate_relocations(self.m, self.view)

    def test_genuine_inventory_mismatch_refused(self):
        other = copy.deepcopy(self.view)
        other.rel[('.rodata', 8)] = ('32', ('fn', 'func_test', 0))
        with self.assertRaisesRegex(ValueError, 'genuine native relocation inventory differs'):
            N.make_proof(self.m, self.raw, self.obj, self.view, other,
                         ASM, self.trim_path, self.artifacts)


if __name__ == '__main__':
    unittest.main()
