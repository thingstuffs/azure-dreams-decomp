import copy
import sys
import unittest
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parent))
from module_member_rekey import review,member_callers

class Rules:
    @staticmethod
    def callee_home(tables,address):return tables[2]['callee']
    @staticmethod
    def caller_images(tables,container,offset):return sorted(tables[0])
    @staticmethod
    def _binding(tables,entry,address):return entry['bindings'].get(address,address)

class MemberRekey(unittest.TestCase):
    def setup(self):
        pair=dict(link='func_8095013C>func_800161EC')
        callee=dict(row='callee',home='callee',container='town',foff=0x113C,vma=0x8095013C)
        entry=dict(row='caller_copy',home='caller',image='load',container='town',foff=0x15F8,bindings={0x800161EC:0x8001613C})
        tables=({'load':dict(container='town',foff=0x1000,size=0x1000,vma=0x80016000)},None,{'callee':callee},None)
        return pair,entry,tables
    def test_home_instance_uses_production_vma_and_keeps_old_key(self):
        pair,entry,tables=self.setup();before=copy.deepcopy(entry)
        change=review(pair,entry,tables,Rules)
        self.assertEqual(change['after'],'0x8001613C');self.assertEqual(change['before'],'0x8095013C')
        self.assertEqual(entry,before)
    def test_unique_copy_also_qualifies(self):
        pair,entry,tables=self.setup();tables[2]['callee']['foff']=0x3000
        tables[2]['copy']=dict(tables[2]['callee'],row='copy',foff=0x113C,vma=0x8001613C)
        self.assertEqual(review(pair,entry,tables,Rules)['after'],'0x8001613C')
    def test_ambiguous_family_is_held(self):
        pair,entry,tables=self.setup();tables[2]['copy']=dict(tables[2]['callee'],row='copy',foff=0x1200)
        with self.assertRaisesRegex(ValueError,'2 callee instances'):review(pair,entry,tables,Rules)
    def test_wrong_old_binding_is_held(self):
        pair,entry,tables=self.setup();entry['bindings'][0x800161EC]=0x80016200
        with self.assertRaisesRegex(ValueError,'old member import misses'):review(pair,entry,tables,Rules)
    def test_disagreeing_load_views_are_held(self):
        pair,entry,tables=self.setup();tables[0]['other']=dict(tables[0]['load'],vma=0x80017000)
        with self.assertRaises(ValueError):review(pair,entry,tables,Rules)
    def test_only_the_importing_member_is_reviewed(self):
        pair=dict(file='src/module.c',old='old',new='real')
        module=dict(members=[dict(source='src/module.c',function='func_80001000',id='town/func_80901000'),dict(source='src/module.c',function='func_80002000',id='town/func_80902000')])
        text='void first(void) { real(); }\nvoid second(void) { other(); }\n'
        self.assertEqual(member_callers(text,pair,module,{'first':'func_80901000','second':'func_80902000'}),{'town/func_80901000'})
    def test_old_spelling_also_selects_member_before_application(self):
        pair=dict(file='src/module.c',old='old',new='real')
        module=dict(members=[dict(source='src/module.c',function='func_80001000',id='town/func_80901000')])
        self.assertEqual(member_callers('void first(void) { old(); }',pair,module,{'first':'func_80001000'}),{'town/func_80901000'})
    def test_static_helper_use_requires_review(self):
        pair=dict(file='src/module.c',old='old',new='real')
        with self.assertRaisesRegex(ValueError,'non-member helper'):
            member_callers('static void helper(void) { real(); }',pair,dict(members=[]),{})
    def test_existing_correct_binding_is_unchanged(self):
        pair,entry,tables=self.setup();entry['bindings'][0x8095013C]=0x8001613C
        self.assertIsNone(review(pair,entry,tables,Rules))

if __name__=='__main__':unittest.main()
