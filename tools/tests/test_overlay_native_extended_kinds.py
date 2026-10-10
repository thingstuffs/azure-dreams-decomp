"""Strict native bank shapes, real ELF accounting and adversarial consumers."""
import copy
from pathlib import Path
import shutil
import struct
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT/'tools/gate'), str(ROOT/'tools/fidelity')]
import overlay_native_rodata as N
import aspsx_diff as A
import overlay_module_gate as G


class ShapeTests(unittest.TestCase):
    def test_rectangle_counts_and_domain(self):
        for count in (1, 2, 8):
            self.assertEqual(len(N.rectangle_bytes(dict(size=count*8, rectangles=[[832,256,96,88]]*count))), count*8)
        for count in (0, 3, 4, 7, 9):
            with self.assertRaises(ValueError):
                N.rectangle_bytes(dict(size=count*8, rectangles=[[0,0,1,1]]*count))
        for rect in ([1024,0,1,1], [0,512,1,1], [1000,0,25,1], [0,500,1,13], [0,0,0,1], [True,0,1,1]):
            with self.assertRaises(ValueError):
                N.rectangle_bytes(dict(size=8, rectangles=[rect]))
        with self.assertRaises(ValueError):
            N.rectangle_bytes(dict(size=16, rectangles=[[0,0,1,1]]))

    def test_signed_grid_is_complete_ordered_neighbourhood(self):
        pairs = [[x,y] for y in (-1,0,1) for x in (-1,0,1)]
        self.assertEqual(N.grid_bytes(dict(size=36,pairs=pairs))[:4], b'\xff\xff\xff\xff')
        for bad in (pairs[:-1], pairs[::-1], [[True,y] for _,y in pairs], [[2,y] for _,y in pairs]):
            with self.assertRaises(ValueError): N.grid_bytes(dict(size=36,pairs=bad))
        with self.assertRaises(ValueError): N.grid_bytes(dict(size=32,pairs=pairs))

    def test_parameter_layout_and_unsigned_domain(self):
        self.assertEqual(N.parameter_bytes(dict(size=12,values=[4096,3072,4096,6144,5120])), struct.pack('<5H',4096,3072,4096,6144,5120)+b'\0\0')
        for values in ([1]*4, [1]*6, [-1]*5, [65536]*5, [True]*5):
            with self.assertRaises(ValueError): N.parameter_bytes(dict(size=12,values=values))
        for size in (10, 16):
            with self.assertRaises(ValueError): N.parameter_bytes(dict(size=size,values=[1]*5))


@unittest.skipUnless(shutil.which('mipsel-linux-gnu-as'), 'MIPS assembler required')
class ObjectTests(unittest.TestCase):
    def fixture(self, kind, pointer_count=1):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        path = Path(self.tmp.name)
        if kind == 'grid_offsets':
            datum = dict(kind=kind,size=36,pairs=[[x,y] for y in (-1,0,1) for x in (-1,0,1)])
        elif kind == 'u16_parameter_record5':
            datum = dict(kind=kind,size=12,values=[4096,3072,4096,6144,5120])
        else:
            datum = dict(kind='rectangle_records',size=kind*8,rectangles=[[832,256,96,88]]*kind)
        start = pointer_count*4
        datum.update(section='.rodata',foff=0x100+start,vma=0x80024000+start,symbol='object',consumers=['func_test'])
        pointers = [dict(kind='typed_function_pointer',section='.rodata',foff=0x100+i*4,vma=0x80024000+i*4,size=4,symbol='entry'+str(i),target='func_test') for i in range(pointer_count)]
        packed = N.literal_bytes(datum)
        extent = 10 if kind == 'u16_parameter_record5' else len(packed)
        asm = '.rdata\n.align 2\n'+''.join('.globl entry%d\nentry%d:\n.word func_test\n'%(i,i) for i in range(pointer_count))
        asm += '.globl object\nobject:\n'+''.join('.half %d\n'%struct.unpack_from('<H',packed,i)[0] for i in range(0,extent,2))
        asm += '.align 2\n.text\n.globl func_test\n.ent func_test\nfunc_test:\nlui $2,%hi(object)\naddiu $2,$2,%lo(object)\nj $31\nnop\n.end func_test\n.size func_test,.-func_test\n'
        (path/'in.s').write_text(asm.replace('.text','.section .text.func_test,"ax",@progbits'))
        subprocess.run(['mipsel-linux-gnu-as','-EL','-march=r3000','-G0','-o',str(path/'in.o'),str(path/'in.s')],check=True)
        raw = (path/'in.o').read_bytes()
        prefix = start+datum['size']
        # Use a 16-aligned prefix with independently owned message bytes.
        # The production trim remains limited to its measured four-byte case.
        padding = -prefix % 16
        if padding:
            text = 'A'*(padding-1)
            if not text: raise AssertionError('word-sized padding expected')
            msg = dict(kind='typed_string',encoding='shift_jis',text=text,size=padding,symbol='message',section='.rodata',foff=0x100+prefix,vma=0x80024000+prefix)
            insert = '.globl message\nmessage:\n'+''.join('.byte %d\n'%v for v in N.literal_bytes(msg))
            asm = asm.replace('.align 2\n.text', '.align 2\n'+insert+'.text')
            asm=asm.replace('.word $L5\n', '.word $L5\n.word $L1\n.word $L2\n')
            (path/'in.s').write_text(asm.replace('.text','.section .text.func_test,"ax",@progbits'))
            subprocess.run(['mipsel-linux-gnu-as','-EL','-march=r3000','-G0','-o',str(path/'in.o'),str(path/'in.s')],check=True)
            raw = (path/'in.o').read_bytes()
            tail = [msg]
        else: tail=[]
        prefix += padding
        self.m = dict(key='extended_test',membership_evidence='pending.json',members=[dict(function='func_test',foff=0x100,vma=0x80024000,size=prefix+16,body_offset=prefix)],owned_data=pointers+[datum]+tail)
        self.asm, self.raw, self.view = asm, raw, A.View(A.read_elf(raw))
        self.datum = datum

    def validate(self):
        N.validate_layout(self.m)
        N.validate_switch_assembly(self.m,self.asm)
        return N.validate_relocations(self.m,self.view)

    def test_real_objects_and_second_complete_pointer(self):
        for kind in (1,2,'grid_offsets','u16_parameter_record5'):
            with self.subTest(kind=kind):
                self.fixture(kind,2)
                receipt = self.validate()
                self.assertEqual(len(receipt['relocations']),2)
                artifacts={'module.o':self.raw,'IN.S':self.asm.encode()}
                proof=N.make_proof(self.m,self.raw,self.raw,self.view,self.view,self.asm,ROOT/'tools/build/slus_rodata_trim.py',artifacts)
                N.verify_proof(self.m,proof,self.raw,self.raw,self.view,self.view,self.asm,ROOT/'tools/build/slus_rodata_trim.py',artifacts)

    def test_consumer_evidence_required_in_all_layers(self):
        self.fixture('grid_offsets')
        for consumers in (None,[],['external'],['func_test','func_test']):
            self.datum['consumers']=consumers
            with self.assertRaises(ValueError): N.validate_layout(self.m)
        self.datum['consumers']=['func_test']
        with self.assertRaisesRegex(ValueError,'consumer'):
            N.validate_switch_assembly(self.m,self.asm.replace('%lo(object)','%lo(external)'))
        self.view.rel={k:v for k,v in self.view.rel.items() if v[0]!='LO16'}
        with self.assertRaisesRegex(ValueError,'consumer'):
            N.validate_relocations(self.m,self.view)

    def test_object_bounds_padding_and_relocations(self):
        self.fixture('u16_parameter_record5',2)
        for offset in (8,18,19):
            view=copy.deepcopy(self.view)
            data=bytearray(view.obj.sections['.rodata']);data[offset]^=1
            view.obj.sections['.rodata']=bytes(data)
            with self.assertRaisesRegex(ValueError,'bytes differ'): N.validate_relocations(self.m,view)
        for pos in (9,18):
            view=copy.deepcopy(self.view);view.obj.symbols['interior']=('.rodata',pos,'global',0)
            with self.assertRaisesRegex(ValueError,'bounds'): N.validate_relocations(self.m,view)
        view=copy.deepcopy(self.view)
        view.rel[('.rodata',8)]=('32',('fn','func_test',0));view.obj.relocs.append(('.rodata',8,'32',('sym','func_test'),0))
        with self.assertRaisesRegex(ValueError,'inventory'): N.validate_relocations(self.m,view)
        with self.assertRaises(ValueError): N.validate_switch_assembly(self.m,self.asm.replace('.half 4096','.word 4096',1))

    def test_second_pointer_addend_external_and_duplicate_refused(self):
        self.fixture(1,2)
        self.m['owned_data'][1]['target']='external'
        with self.assertRaisesRegex(ValueError,'complete native member'): N.validate_layout(self.m)
        self.m['owned_data'][1]['target']='func_test'
        for target in (('fn','func_test',4), ('sym','external',0)):
            view=copy.deepcopy(self.view);view.rel[('.rodata',4)]=('32',target)
            with self.assertRaisesRegex(ValueError,'inventory'): N.validate_relocations(self.m,view)
        self.view.obj.relocs+=self.view.obj.relocs[:1]
        with self.assertRaisesRegex(ValueError,'duplicate'): N.validate_relocations(self.m,self.view)

    def test_final_parameter_minimal_implicit_padding(self):
        self.fixture('u16_parameter_record5',1)
        assembly=self.asm.replace('.align 2\n.text','.text')
        N.validate_switch_assembly(self.m,assembly)
        N.validate_relocations(self.m,self.view)
        for extra in ('.rdata\n.byte 0\n','.rdata\n.half 0\n'):
            with self.assertRaises(ValueError): N.validate_switch_assembly(self.m,assembly+extra)


class PointerlessTests(unittest.TestCase):
    def test_pointerless_prefix_preserves_switch_ownership(self):
        from test_overlay_native_rodata import ASM
        with tempfile.TemporaryDirectory() as temp:
            path=Path(temp)
            asm=ASM.replace('.rdata\n.align 2\n.globl native_entry\nnative_entry:\n.word func_test\n','',1)
            asm=asm.replace('.word $L5\n', '.word $L5\n.word $L1\n.word $L2\n')
            (path/'in.s').write_text(asm.replace('.text','.section .text.func_test,"ax",@progbits'))
            subprocess.run(['mipsel-linux-gnu-as','-EL','-march=r3000','-G0','-o',str(path/'in.o'),str(path/'in.s')],check=True)
            raw=(path/'in.o').read_bytes();view=A.View(A.read_elf(raw));size=view.funcs['func_test'][2]
            m=dict(key='pointerless_test',membership_evidence='pending.json',members=[dict(function='func_test',foff=0x100,vma=0x80024000,size=size+28,body_offset=28)],owned_data=[dict(kind='switch_table',section='.rodata',foff=0x100,vma=0x80024000,size=28,owner='func_test')])
            N.validate_layout(m);N.validate_switch_assembly(m,asm)
            cooked,_=N.prepare_object(m,raw,ROOT/'tools/build/slus_rodata_trim.py')
            N.validate_relocations(m,A.View(A.read_elf(cooked)))
            # A pointerless switch creates rodata after its owner's text section.
            # Do not sort the section inventory or hide any text/data payload.
            (path/'cooked.o').write_bytes(cooked)
            payload=[(s['name'],s['size']) for s in G.sections(path/'cooked.o')
                     if s['flags'] & 2 and s['size'] and s['name'] not in G.META]
            self.assertEqual(payload,G.payload_spec(m))
            self.assertEqual(payload,[('.text.func_test',size),('.rodata',28)])
            ld=path/'module.ld'
            ld.write_text('SECTIONS { .module 0x80024000 : { '+G.link_inputs(m,path/'cooked.o')+' } /DISCARD/ : { *(.reginfo) *(.MIPS.abiflags) *(.pdr) } }')
            subprocess.run(['mipsel-linux-gnu-ld','-EL','-T',str(ld),'-o',str(path/'module.elf'),str(path/'cooked.o')],check=True)
            linked=A.read_elf((path/'module.elf').read_bytes())
            self.assertEqual(linked.symbols['func_test'][1],0x80024000+28)
            self.assertEqual(len(linked.sections['.module']),size+28)
            for owner in ('external',None):
                m['owned_data'][0]['owner']=owner
                with self.assertRaises(ValueError): N.validate_layout(m)
            m['owned_data'][0]['owner']='func_test'
            with self.assertRaises(ValueError): N.validate_switch_assembly(m,asm.replace('%lo($L10)','%lo(external)'))
            with self.assertRaises(ValueError): N.validate_switch_assembly(m,asm.replace('.word $L1','.word 1234'))


if __name__ == '__main__': unittest.main()
