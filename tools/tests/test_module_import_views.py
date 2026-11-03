"""Module import inventories override name-encoded home addresses in both object legs."""
from pathlib import Path
import struct
import sys
import unittest
from unittest.mock import patch

ROOT=Path(__file__).resolve().parents[2]
sys.path[:0]=[str(ROOT/'tools'),str(ROOT/'tools/gate'),str(ROOT/'tools/fidelity')]
import aspsx_diff as A
import overlay_module_gate as G
from objread import Obj


def object_with_call(fmt, target):
    obj=Obj(fmt)
    obj.sections['.text']=struct.pack('<II',0x0C000000,0)
    obj.symbols={'caller':('.text',0,'func' if fmt=='elf' else 'global',8 if fmt=='elf' else None)}
    obj.relocs=[('.text',0,'26',('sym',target),0)]
    return obj


class ModuleImportViews(unittest.TestCase):
    def views(self, address, genuine='func_80001000'):
        module=dict(imports=[dict(symbol='func_80001000',kind='function',vma=address)])
        with patch.object(A,'read_elf',return_value=object_with_call('elf','func_80001000')):
            with patch.object(A,'read_lnk',return_value=object_with_call('lnk',genuine)):
                return G.module_object_views(module,b'elf',b'lnk',ROOT)

    def test_placed_import_uses_inventory_address_in_genuine_leg(self):
        _a,ma,ge=self.views(0x80002000)
        self.assertTrue(A.compare_units(ma,ge)['exact'])
        linked,masked=A.resolve_tokens(ge,'caller',0x80003000,{'func_80001000':0x80002000}.get,0x80080994)
        self.assertEqual(linked,[0x0C000800,0])
        self.assertEqual(masked,[])
        self.assertEqual(ge.tokens('caller')[0][2],('sym','func_80001000',0))

    def test_identity_import_keeps_existing_encoded_address_model(self):
        _a,_ma,ge=self.views(0x80001000)
        linked,masked=A.resolve_tokens(ge,'caller',0x80003000,{}.get,0x80080994)
        self.assertEqual(linked,[0x0C000400,0])
        self.assertEqual(masked,[])
        self.assertEqual(ge.tokens('caller')[0][2],('addr',None,0x80001000))

    def test_different_genuine_symbol_is_still_rejected(self):
        with self.assertRaisesRegex(ValueError,'symbolic whole-TU genuine mismatch'):
            self.views(0x80002000,'func_80002000')


if __name__=='__main__':
    unittest.main()
