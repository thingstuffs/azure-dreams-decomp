"""Typed message/rectangle shape, canonical directives and ELF rejection tests."""
import copy
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest
ROOT=Path(__file__).resolve().parents[2]
sys.path[:0]=[str(ROOT/'tools/gate'),str(ROOT/'tools/fidelity')]
import overlay_native_rodata as N
import aspsx_diff as A

class ShapeTests(unittest.TestCase):
    def test_typed_text_matches_encoded_message(self):
        text='Ｔｈｅｒｅ　ｗａｓ　ｎｏ　ｅｆｆｅｃｔ　ｏｎ　'
        a=dict(kind='typed_string',encoding='shift_jis',text=text,size=48)
        b=dict(kind='message_bytes',encoding='shift_jis',bytes=list(text.encode('shift_jis')),size=48)
        self.assertEqual(N.literal_bytes(a),N.literal_bytes(b))
        self.assertEqual(N.literal_bytes(a)[-2:],b'\0\0')
    def test_invalid_message_shape(self):
        good=dict(kind='message_bytes',encoding='shift_jis',bytes=[129,68],size=4)
        for changes in [dict(bytes=[]),dict(bytes=[0]),dict(bytes=[True]),dict(bytes=[256]),dict(bytes=[129]),dict(bytes=[1]),dict(size=8),dict(encoding='raw')]:
            with self.subTest(changes=changes),self.assertRaises(ValueError):N.literal_bytes(dict(good,**changes))
        for text in ['', '\0', '\n', '😀']:
            with self.subTest(text=text),self.assertRaises(ValueError):N.literal_bytes(dict(kind='typed_string',encoding='shift_jis',text=text,size=4))
    def test_invalid_rectangle_shape(self):
        good=[[832,320,64,64]]*8
        for rects in [good[:-1],[[832,320,0,64]]*8,[[1024,0,1,1]]*8,[[0,512,1,1]]*8,[[1000,0,25,1]]*8,[[0,500,1,13]]*8,[[True,0,1,1]]*8,[[0,0,1]]*8]:
            with self.subTest(rects=rects),self.assertRaises(ValueError):N.rectangle_bytes(dict(size=64,rectangles=rects))

@unittest.skipUnless(shutil.which('mipsel-linux-gnu-as'),'MIPS assembler required')
class ObjectTests(unittest.TestCase):
    def setUp(self):
        self.tmp=tempfile.TemporaryDirectory();self.addCleanup(self.tmp.cleanup);self.path=Path(self.tmp.name)
        self.message=dict(section='.rodata',foff=0x104,vma=0x80024004,size=12,kind='typed_string',encoding='shift_jis',text='ABCDEFGH',symbol='message')
        self.rect=dict(section='.rodata',foff=0x110,vma=0x80024010,size=64,kind='rectangle_records',rectangles=[[832,320,64,64]]*8,symbol='rectangles')
        self.m=dict(key='kinds_test',membership_evidence='pending.json',members=[dict(function='func_test',foff=0x100,vma=0x80024000,size=88,body_offset=80)],owned_data=[dict(section='.rodata',foff=0x100,vma=0x80024000,size=4,kind='typed_function_pointer',symbol='entry',target='func_test'),self.message,self.rect])
        self.asm='.rdata\n.align 2\n.globl entry\nentry:\n.word func_test\n.globl message\nmessage:\n'+''.join('.byte %d\n'%v for v in N.literal_bytes(self.message))+'.globl rectangles\nrectangles:\n'+''.join('.half %d\n'%v for r in self.rect['rectangles'] for v in r)+'.text\n.globl func_test\n.ent func_test\nfunc_test:\nj $31\nnop\n.end func_test\n.size func_test,.-func_test\n'
        (self.path/'in.s').write_text(self.asm.replace('.text','.section .text.func_test,"ax",@progbits'))
        subprocess.run(['mipsel-linux-gnu-as','-EL','-march=r3000','-G0','-o',str(self.path/'in.o'),str(self.path/'in.s')],check=True)
        self.raw=(self.path/'in.o').read_bytes();self.view=A.View(A.read_elf(self.raw))
    def test_all_kinds_accepted(self):
        for kind in ['typed_string','message_bytes']:
            m=copy.deepcopy(self.m)
            if kind=='message_bytes':m['owned_data'][1]=dict(self.message,kind=kind,bytes=list(b'ABCDEFGH'));m['owned_data'][1].pop('text')
            N.validate_layout(m);N.validate_switch_assembly(m,self.asm);N.validate_relocations(m,self.view)
    def test_exact_bytes_and_zero_padding(self):
        for offset in [4,12,15,16,79]:
            v=copy.deepcopy(self.view);data=bytearray(v.obj.sections['.rodata']);data[offset]^=1;v.obj.sections['.rodata']=bytes(data)
            with self.subTest(offset=offset),self.assertRaisesRegex(ValueError,'object bytes differ'):N.validate_relocations(self.m,v)
    def test_directives_not_interchangeable(self):
        for asm in [self.asm.replace('.byte 65','.byte 66',1),self.asm.replace('.byte 65','.word 65',1),self.asm.replace('.half 832','.word 832',1),self.asm.replace('.byte 65','.space 1',1),self.asm.replace('.byte 65','.byte 256',1),self.asm.replace('.byte 65','.byte -1',1),self.asm.replace('.byte 65','extra:\n.byte 65',1).replace('.byte 66','interior:\n.byte 66',1),self.asm+'\n.rdata\n.byte 0\n']:
            with self.subTest(asm=asm),self.assertRaises(ValueError):N.validate_switch_assembly(self.m,asm)
    def test_symbol_bounds_and_unwanted_relocation(self):
        for symbol,pos in [('message',8),('rectangles',20),('interior',5)]:
            v=copy.deepcopy(self.view);v.obj.symbols[symbol]=('.rodata',pos,0)
            with self.subTest(symbol=symbol),self.assertRaisesRegex(ValueError,'symbol/bounds differ'):N.validate_relocations(self.m,v)
        for pos in [4,16]:
            v=copy.deepcopy(self.view);v.rel[('.rodata',pos)]=('32',('fn','func_test',0));v.obj.relocs.append(('.rodata',pos,'32',('sym','func_test'),0))
            with self.subTest(pos=pos),self.assertRaisesRegex(ValueError,'inventory differs'):N.validate_relocations(self.m,v)
    def test_duplicate_relocation_refused(self):
        v=copy.deepcopy(self.view);v.obj.relocs+=v.obj.relocs
        with self.assertRaisesRegex(ValueError,'duplicate'):N.validate_relocations(self.m,v)
    def test_unknown_blob_kind_refused(self):
        self.message['kind']='raw_bytes'
        with self.assertRaisesRegex(ValueError,'unsupported'):N.validate_layout(self.m)
    def test_genuine_and_receipt_binding(self):
        artifacts={'module.o':self.raw,'module.untrimmed.o':self.raw,'IN.S':self.asm.encode()}
        trim=ROOT/'tools/build/slus_rodata_trim.py'
        proof=N.make_proof(self.m,self.raw,self.raw,self.view,self.view,self.asm,trim,artifacts)
        changed=copy.deepcopy(self.m);changed['owned_data'][1]['text']='BBCDEFGH'
        with self.assertRaises(ValueError):N.verify_proof(changed,proof,self.raw,self.raw,self.view,self.view,self.asm,trim,artifacts)
        other=copy.deepcopy(self.view);data=bytearray(other.obj.sections['.rodata']);data[4]^=1;other.obj.sections['.rodata']=bytes(data)
        with self.assertRaises(ValueError):N.make_proof(self.m,self.raw,self.raw,self.view,other,self.asm,trim,artifacts)
if __name__=='__main__':unittest.main()
