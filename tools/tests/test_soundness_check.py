"""Regression checks for soundness ratchet safety, using real 32-bit LTO."""
import copy
import importlib.util
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

HERE = Path(__file__).resolve().parents[1] / 'lint'
sys.path.insert(0, str(HERE))
import soundness_check as S

class SoundnessTest(unittest.TestCase):
    def summary(self):
        return dict(schema=2, compiler='gcc', mode='lto', flags=['-m32'], unit_digest='x',
                    units=2, limited=False, failures=0, identities=[['a.c','f','-Wodr','x']],
                    identity_counts=[['a.c','f','-Wodr','x',1]])

    def test_substitution_is_regression_even_at_equal_count(self):
        old=self.summary(); new=copy.deepcopy(old)
        new['identities'][0][-1]='different'
        self.assertTrue(S.compare(new, old))

    def test_partial_failed_and_changed_census_refused(self):
        for key,value in [('limited',True),('failures',1),('unit_digest','other'),('compiler','clang')]:
            old=self.summary(); new=copy.deepcopy(old); new[key]=value
            self.assertTrue(S.compare(new,old), key)

    def test_reduction_passes(self):
        old=self.summary(); new=copy.deepcopy(old); new['identities']=[]
        new['identity_counts']=[]
        self.assertEqual(S.compare(new,old),[])

    def test_repeated_existing_diagnostic_is_regression(self):
        old=self.summary(); new=copy.deepcopy(old)
        new['identity_counts'][0][-1]=2
        self.assertIn('additional diagnostic occurrences: a.c | f | -Wodr | x', S.compare(new,old))

    def test_failures_cannot_be_hidden_by_identical_warning_set(self):
        old=self.summary(); new=copy.deepcopy(old); new['failures']=1
        self.assertIn('a complete census and zero failed commands are required', S.compare(new,old))

    def test_clang_context_keeps_identical_warnings_in_distinct_functions(self):
        with tempfile.TemporaryDirectory() as d:
            p=Path(d); (p/'src').mkdir()
            (p/'src/a.c').write_text('int first(void) { return 1; }\n/* } */\nint second(void) { return 2; }\n')
            rows=[dict(file='src/a.c', line=n, function='<global>', warning='-Wcast-function-type-strict', message='same') for n in (1,3)]
            for row in rows: S.locate_function(p,row)
            self.assertEqual([r['function'] for r in rows],['first','second'])
            self.assertNotEqual(S.identity(rows[0]),S.identity(rows[1]))

    def test_real_lto_detects_cross_unit_arity(self):
        with tempfile.TemporaryDirectory() as d:
            p=Path(d)
            (p/'a.c').write_text('int callee(int x, int y) { return x+y; }\n')
            (p/'b.c').write_text('extern int callee(int); int caller(void) { return callee(1); }\n')
            for n in ('a','b'):
                subprocess.run(['gcc','-m32','-flto','-c',str(p/(n+'.c')),'-o',str(p/(n+'.o'))],check=True,capture_output=True)
            r=subprocess.run(['gcc','-m32','-flto','-Wlto-type-mismatch','-nostdlib','-r',
                '-flinker-output=nolto-rel',str(p/'a.o'),str(p/'b.o'),'-o',str(p/'all.o')],capture_output=True,text=True)
            self.assertEqual(r.returncode,0,r.stderr)
            self.assertIn('-Wlto-type-mismatch',r.stderr)

if __name__=='__main__': unittest.main()
