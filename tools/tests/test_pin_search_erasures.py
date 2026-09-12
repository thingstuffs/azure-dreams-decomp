"""Joint erasures must cross the greedy gap and still require byte verification."""
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]))
import pin_search_engine as engine
from pin_census import sites_of

SOURCE='void f(int a, int b, int c) {\n ASM_KEEP(a);\n\n\n\n\n ASM_KEEP(b);\n\n\n\n\n ASM_KEEP(c);\n}\n'

class ErasureTests(unittest.TestCase):
    def session(self,tmp,vf,**options):
        return engine.Session(dict(id='town/test',kind='overlay',c_path='test.c',cfg='2.7.2'),SOURCE,
                              'recipe',Path(tmp)/'cache.sqlite',dict(engine.DEFAULTS,**options),vf)

    def test_all_small_subsets_once_largest_first(self):
        live=[(None,'ASM_KEEP')]*8
        groups=list(engine.erasure_groups(live))
        self.assertEqual(len(groups),255);self.assertEqual(len(set(groups)),255)
        self.assertEqual(groups[0],tuple(range(8)))
        self.assertEqual(groups[-1],(7,))
        self.assertIn((0,7),groups)

    def test_joint_removal_without_single_or_near_pair_win(self):
        def cc(row,text):return ['same'] if len(sites_of(text)) in (0,3) else ['different']
        with tempfile.TemporaryDirectory() as tmp,patch.object(engine,'compile_s',side_effect=cc):
            s=self.session(tmp,lambda text:{'exact':not sites_of(text)})
            text,info=s.run('erasures')
            self.assertEqual(len(sites_of(text)),0)
            self.assertEqual(info['compiled'],2);self.assertEqual(info['tried'],1)
            self.assertEqual(info['steps'],['erase:0+1+2'])

    def test_screen_equality_alone_never_accepts(self):
        with tempfile.TemporaryDirectory() as tmp,patch.object(engine,'compile_s',return_value=['same']):
            s=self.session(tmp,lambda text:{'exact':False})
            text,info=s.run('erasures')
            self.assertEqual(text,SOURCE);self.assertEqual(info['tried'],7)

    def test_nonzero_screen_has_bounded_byte_fallback(self):
        with tempfile.TemporaryDirectory() as tmp,patch.object(engine,'compile_s',side_effect=lambda row,text:['same'] if text==SOURCE else ['different']):
            s=self.session(tmp,lambda text:{'exact':not sites_of(text)})
            text,info=s.run('erasures')
            self.assertEqual(len(sites_of(text)),0)
            self.assertEqual(info['fallback_tried'],1);self.assertEqual(info['fallback_wins'],1)

if __name__=='__main__':unittest.main()
